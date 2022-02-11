/********************************************************************/
// FOPBarcodeShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <afxpriv.h>
#include "fores.h"
#include "FODrawHelper.h"
#include "FOScaleUint.h"
#include "UCCPrint.h"

#include "FOPBarCodeShape.h"
#include "FOPBarcodeGenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CFOPBarcodeShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CFOPBarcodeShape, CFOEditBoxShape, VERSIONABLE_SCHEMA | 1)
CFOPBarcodeShape::CFOPBarcodeShape()
{
	SetType(FOP_COMP_BARCODE);
	SetBkColor(fo_DefaultFillColor);
	SetPolyObject(FALSE);
	SetRotateProtect(TRUE);

	SetTabOrderProtect(TRUE);
	SetMultiLine(FALSE);
	SetNeedForDB(TRUE);
	SetNullPen(TRUE);

	SetFlat(TRUE);
	SetTextHorzAlignment(TextMiddle);

//	SetNeedForDB(SV_FIELD_VAR_EDITCTRL);

//////////////////////////////////////////////////////////////////////////	
	m_bFixModule = FALSE;
	m_fModule = 2.0f;
	m_nPadding = 10;
	m_bShowText = true;
	m_bCheckSum = false;
	m_fWideNarrowRatio = 2.0f;
	m_symbology = SVEAN13;
	m_Orientation = SVOriNormal;
	
	m_barcodeAlign = StringAlignmentCenter;
	m_strFormat.SetAlignment(StringAlignmentCenter);
	m_strFormat.SetLineAlignment(StringAlignmentCenter);
	
	m_pBarcode = NULL;
	m_pBarcode = Create(m_symbology);
	bPrintMode = FALSE;
}

CFOPBarcodeShape::CFOPBarcodeShape(const CFOPBarcodeShape& src)
{
	m_bFixModule = FALSE;
	m_fModule = 2.0f;
	m_nPadding = 10;
	m_bShowText = true;
	m_bCheckSum = false;
	m_fWideNarrowRatio = 2.0f;
	m_symbology = SVEAN13;
	m_Orientation = SVOriNormal;
	
	m_barcodeAlign = StringAlignmentCenter;
	m_strFormat.SetAlignment(StringAlignmentCenter);
	m_strFormat.SetLineAlignment(StringAlignmentCenter);
	
	m_pBarcode = NULL;
	bPrintMode = FALSE;
	SetPolyObject(FALSE);
	*this = src;
}

CFOPBarcodeShape::~CFOPBarcodeShape()
{
	_SafeDeletePtr(m_pBarcode);
}

/////////////////////////////////////////////////////////////////////////////
// CFOPBarcodeShape diagnostics

#ifdef _DEBUG
void CFOPBarcodeShape::AssertValid() const
{
	CFOEditBoxShape::AssertValid();
}

void CFOPBarcodeShape::Dump(CDumpContext& dc) const
{
	CFOEditBoxShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

void CFOPBarcodeShape::Create(CRect &rcPos, CString strCaption)
{	
	if (m_symbology<SVCodabar || m_symbology>SVEAN128)
		m_symbology = SVEAN13;

	m_pBarcode = Create(m_symbology);
	strCaption = m_pBarcode->GetDefaultValue();

	AllocMemory(4);
	m_lpShapePoints[0] = CPoint(rcPos.left,  rcPos.top);
	m_lpShapePoints[1] = CPoint(rcPos.right, rcPos.top);
	m_lpShapePoints[2] = CPoint(rcPos.right, rcPos.bottom);
	m_lpShapePoints[3] = CPoint(rcPos.left,  rcPos.bottom);
	SetObjectCaption(strCaption);
	CFOEditBoxShape::Create(rcPos,strCaption);

	UpdateComp();
}

void CFOPBarcodeShape::Serialize(CArchive& ar)
{
	CFOEditBoxShape::Serialize(ar);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.
		ar << (UINT)m_symbology;
		ar << (UINT)m_barcodeAlign;
		ar << (UINT)m_bFixModule;
		ar << m_fModule;
		ar << m_nPadding;
		ar << (UINT)m_bShowText;
		ar << (UINT)m_bCheckSum;
		ar << m_fWideNarrowRatio;
		ar << (UINT)m_Orientation;

	}
	else
	{
		//FODO:Add your own code here.
		UINT nTemp = 0;
		ar >> nTemp;
		m_symbology = (SVBarCodeSymbology)nTemp;
		ar >> nTemp;
		m_barcodeAlign = (StringAlignment)nTemp;
		ar >> nTemp;
		m_bFixModule = (0 != nTemp);
		ar >> m_fModule;
		ar >> m_nPadding;
		ar >> nTemp;
		m_bShowText = (0 != nTemp);
		ar >> nTemp;
		m_bCheckSum = (0 != nTemp);
		ar >> m_fWideNarrowRatio;
		ar >> nTemp;
		m_Orientation = (FOPBarCodeOrientation)nTemp;

		Create(m_symbology);	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFOPBarcodeShape serialization
CFile* CFOPBarcodeShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
								 CFileException* pError)
{
	CMirrorFile* pFile = new CMirrorFile;
	ASSERT(pFile != NULL);
	if (!pFile->Open(lpszFileName, nOpenFlags, pError))
	{
		delete pFile;
		pFile = NULL;
	}
	return pFile;
}

void CFOPBarcodeShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CFOPBarcodeShape::OpenDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
			Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

BOOL CFOPBarcodeShape::SaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	
	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
	return TRUE;        // success
}

CFODrawShape* CFOPBarcodeShape::DoConvertToPathObj(CDC *pDC,const BOOL &bBezier)
{
	BOOL bFill = TRUE;
	FOPSimpleCompositePolygon aSimplePoly;
	GetPathSimplePolygon(aSimplePoly);
	CFODrawShape* pRet = ConvertToPathShape(pDC,aSimplePoly, bFill, bBezier);
	return pRet;
}

CFOPBarcodeShape& CFOPBarcodeShape::operator=(const CFOPBarcodeShape& src)
{
	(*(CFOEditBoxShape*)this) = src;

	m_symbology		= src.m_symbology;
	m_barcodeAlign	= src.m_barcodeAlign;
	m_bFixModule	= src.m_bFixModule;
	m_fModule		= src.m_fModule;
	m_nPadding		= src.m_nPadding;
	m_bShowText		= src.m_bShowText;
	m_bCheckSum		= src.m_bCheckSum;
	m_fWideNarrowRatio = src.m_fWideNarrowRatio;
	m_Orientation	= src.m_Orientation;

	Create(m_symbology);
	
	return (*this);
}

CFODrawShape* CFOPBarcodeShape::Copy() const
{
	return (new CFOPBarcodeShape(*this));
}

void CFOPBarcodeShape::PrepareDC(CDC* pDC)
{
	CFOEditBoxShape::PrepareDC(pDC);
	//FODO:Add your own code below.
}

void CFOPBarcodeShape::OnDrawTrackCustom(CDC *pDC)
{
	CFOEditBoxShape::OnDrawTrackCustom(pDC);
	// Add your own code here.
}

void CFOPBarcodeShape::OnDrawFlat(CDC *pDC)
{
	CFOEditBoxShape::OnDrawFlat(pDC);
	
	//FODO:Add your own code below.
	if(pDC->IsPrinting())
	{
		bPrintMode = TRUE;
	}
	else
	{
		bPrintMode = FALSE;
	}
	
	CRect rc = GetDrawRect();
	rc.DeflateRect(2, 2);
	rc.NormalizeRect();
	RectF rcf = RectF((float)rc.left, (float)rc.top, (float)rc.Width(), (float)rc.Height());

	int nSaveDC = pDC->SaveDC();
	COLORREF crFont = pDC->SetTextColor(GetFontColor());
	m_pBarcode->DrawContent(pDC, rcf, this);
	pDC->SetTextColor(crFont);
	
	pDC->RestoreDC(nSaveDC);
}

void CFOPBarcodeShape::OnDrawShadow(CDC *pDC)
{
//	UNUSED_ALWAYS(pDC);
	FillShadowPoly(pDC, m_lpShapePoints, m_nCompPtCount);
}

void CFOPBarcodeShape::OnDraw3d(CDC *pDC)
{
	CFOEditBoxShape::OnDraw3d(pDC);
	//FODO:Add your own code below.

	if(pDC->IsPrinting())
	{
		bPrintMode = TRUE;
	}
	else
	{
		bPrintMode = FALSE;
	}
	
	CRect rc = GetDrawRect();
	rc.DeflateRect(2, 2);
	rc.NormalizeRect();
	RectF rcf = RectF((float)rc.left, (float)rc.top, (float)rc.Width(), (float)rc.Height());
	
//	Graphics graphics(pDC->m_hDC);
//	graphics.SetPageUnit(UnitPixel); // Must be set for printing
//	if (TRUE == pDC->IsPrinting())
//		graphics.SetSmoothingMode(SmoothingModeHighQuality);
//	else
//		graphics.SetSmoothingMode(HokGdiPlusG::m_smoothingHighSpeed);

	int nSaveDC = pDC->SaveDC();
	COLORREF crFont = pDC->SetTextColor(GetFontColor());
	m_pBarcode->DrawContent(pDC, rcf, this);
	pDC->SetTextColor(crFont);

	pDC->RestoreDC(nSaveDC);
}

void CFOPBarcodeShape::OnDrawText(CDC *pDC)
{
	//FODO:Add your own code below.
//	UINT nAlign = GetDrawFormatType();
	
	CRect rcPos = GetDrawRect();
	rcPos.NormalizeRect();
	CRect rcEdit = rcPos;
	rcEdit.top += 2;
	rcEdit.left += 2;
	
	if (m_pControlBox != NULL)
	{
		rcEdit.right -= 2;
		DrawEdit(pDC,rcEdit);
	}
	else
	{ 
		rcEdit.left += 3;
		rcEdit.right -= 3;
		rcEdit.bottom -= 2;
//		COLORREF crColor = GetFontColor();
//		
//		CString strLabel = GenEditingLabel();
//		DoDrawTextExt(pDC,strLabel,&rcEdit,crColor,nAlign);
	}
}
  
void CFOPBarcodeShape::ClearDC(CDC* pDC)
{
	CFOEditBoxShape::ClearDC(pDC);
	//FODO:Add your own code below.
}

void CFOPBarcodeShape::OnTextEditProperties()
{
	CFOEditBoxShape::OnTextEditProperties();
}

void CFOPBarcodeShape::RotateShape(double nAngle, double dOriginX, double dOriginY)
{
	CFOEditBoxShape::RotateShape(nAngle,dOriginX,dOriginY);
}

void CFOPBarcodeShape::RotateTrackShape(double nAngle, double dOriginX, double dOriginY)
{
	CFOEditBoxShape::RotateTrackShape(nAngle,dOriginX,dOriginY);
}

void CFOPBarcodeShape::GeometryUpdated(CFOArea* pArea)
{
	if (m_lpShapePoints && pArea)
	{
		pArea->BuildPolygonArea(m_lpShapePoints, m_nCompPtCount);
		m_rectPosition = pArea->GetBoundingRect();
	}
}

void CFOPBarcodeShape::SetCurrentEditText(const CString& str)
{
	CString strTemp = m_pBarcode->FormatText(str);

//	
//	CString strBegin = GetModel()->GetExpressBegin();
//	CString strEnd = GetModel()->GetExpressEnd();
//	if (str.GetLength() > 0 && CString(str[0]) == strBegin && CString(str[str.GetLength()-1]) == strEnd)
//		strTemp = str;

	CFOEditBoxShape::SetCurrentEditText(strTemp);
}

// Method define
void CFOPBarcodeShape::GetNormalSpotLocation(CFOPHandleList& lstHandle)
{
	CFODrawShape::GetNormalSpotLocation(lstHandle);
}

//////////////////////////////////////////////////////////////////////////
void CFOPBarcodeShape::SetBarcode(const CString& str)
{
	SetCurrentText(str);
}

CString CFOPBarcodeShape::GetBarcode()
{
	CString strTemp = GetCurrentText();

	if (_T("") == strTemp)
		strTemp = m_pBarcode->GetDefaultValue();

	return strTemp;
}

bool CFOPBarcodeShape::GetCalcCheckSum()
{
	m_bCheckSum = (NULL != m_pBarcode) ? m_pBarcode->GetCalcCheckSum(): false;

	return m_bCheckSum;
} 

void CFOPBarcodeShape::SetCalcCheckSum(const bool &value)
{
	(NULL != m_pBarcode) ? m_pBarcode->SetCalcCheckSum(value): value;
	GetCalcCheckSum();
}

float CFOPBarcodeShape::GetWideNarrowRatio()
{
//	m_fWideNarrowRatio = (NULL != m_pBarcode) ? m_pBarcode->GetWideNarrowRatio(): 2.0f;
	
	return m_fWideNarrowRatio;
} 

void CFOPBarcodeShape::SetWideNarrowRatio(const float &value)
{
//	(NULL != m_pBarcode) ? m_pBarcode->SetWideNarrowRatio(value): value;
//	GetWideNarrowRatio();
}

FOPBarCodeGeneratorBase* CFOPBarcodeShape::Create(const SVBarCodeSymbology &symbology)
{
	_SafeDeletePtr(m_pBarcode);
	switch(symbology) {
	case SVCodabar:
		{
			FOPCodabarGenerator *pCodebar = new FOPCodabarGenerator;
			m_pBarcode = pCodebar;
			
			SetBarcode(_T("0123456789"));
			SetWideNarrowRatio(2.5);
			pCodebar->SetStartStopSymbols(BN);
		}
		break;
	case SVIndustrial2of5:
		m_pBarcode = new FOPIndustrial2of5Generator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		SetWideNarrowRatio(3.0);
		break;
	case SVInterleaved2of5:
		m_pBarcode = new FOPInterleaved2of5Generator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		SetWideNarrowRatio(3.0);
		break;
	case SVCode39:
		m_pBarcode = new FOPCode39Generator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		SetWideNarrowRatio(2.5);
		break;
	case SVCode39Extended:
		m_pBarcode = new FOPCode39ExtendedGenerator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		SetWideNarrowRatio(2.5);
		break;
	case SVCode93:
		m_pBarcode = new FOPCode93Generator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		break;
	case SVCode93Extended:
		m_pBarcode = new FOPCode93ExtendedGenerator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		break;
	case SVCode128:
		{//	
			FOPCode128Generator* pCode128 = new FOPCode128Generator;
			pCode128->SetCharSet(SVCharsetAuto);
			m_pBarcode = pCode128;
		}
		break;
	case SVCode128A:
		{
			FOPCode128Generator* pCode128 = new FOPCode128Generator;
			pCode128->SetCharSet(SVCharsetA);
			m_pBarcode = pCode128;
		}
		break;
	case SVCode128B:
		{
			FOPCode128Generator* pCode128 = new FOPCode128Generator;
			pCode128->SetCharSet(SVCharsetB);
			m_pBarcode = pCode128;
		}
		break;
	case SVCode128C:
		{//	
			FOPCode128Generator* pCode128 = new FOPCode128Generator;
			pCode128->SetCharSet(SVCharsetC);
			m_pBarcode = pCode128;
		}
		break;
	case SVEAN128:
		{
			FOPEAN128Generator *pEan128 = new FOPEAN128Generator;
			pEan128->SetCharSet(SVCharsetAuto);
			m_pBarcode = pEan128;
			
			SetBarcode(_T("2100000144000000918388"));
		}
		break;
	case SVCode11:
		m_pBarcode = new FOPCode11Generator;

		SetBarcode(_T("0123456789"));
		break;
	case SVMSI:
		{
			FOPCodeMSIGenerator* pMSI = new FOPCodeMSIGenerator;
			m_pBarcode = pMSI;
			
			SetBarcode(_T("0123456789"));
			pMSI->SetCheckSum(SVSumModulo10);
		}
		break;
	case SVPostNet:
		m_pBarcode = new FOPPostNetGenerator;
		
		SetBarcode(_T("01234567"));
		break;
	case SVEAN13:
		m_pBarcode = new FOPEAN13Generator;
		
		SetBarcode(_T("062325400001"));
		break;
	case SVUPCA:
		m_pBarcode = new FOPUPCAGenerator;
		
		SetBarcode(_T("001234567890"));
		break;
	case SVEAN8:
		m_pBarcode = new FOPEAN8Generator;
		
		SetBarcode(_T("0123456"));
		break;
	case SVUPCSupp2:
		m_pBarcode = new FOPUPCSupplemental2Generator;
		
		SetBarcode(_T("01"));
		break;
	case SVUPCSupp5:
		m_pBarcode = new FOPUPCSupplemental5Generator;
		break;
	case SVUPCE0:
		m_pBarcode = new FOPUPCE0Generator;
		
		SetBarcode(_T("4210000526"));
		break;
	case SVUPCE1:
		m_pBarcode = new FOPUPCE1Generator;
		
		SetBarcode(_T("4210000526"));
		break;
	case SVMatrix2of5:
		m_pBarcode = new FOPMatrix2of5Generator;
		
		SetBarcode(_T("0123456789"));
		SetCalcCheckSum(false);
		SetWideNarrowRatio(3.0);
		break;
	default:
		ASSERT(FALSE);
	}

	return m_pBarcode;
}

int CFOPBarcodeShape::GetSymbologyCount()
{
	return sizeof(gBarcodeName)/sizeof(gBarcodeName[0]);
}

CString CFOPBarcodeShape::GetSymbologyName(const int &nIndex)
{
	if (nIndex>-1 && nIndex<sizeof(gBarcodeName)/sizeof(gBarcodeName[0]))
		return gBarcodeName[nIndex].m_strName;
	return _T("");
}

SVBarCodeName CFOPBarcodeShape::GetSymbology(const int &nIndex)
{
	return gBarcodeName[nIndex];
}

CString CFOPBarcodeShape::GetSymbologyDsc(const SVBarCodeSymbology &symbology)
{
	int nCount = sizeof(gBarcodeName)/sizeof(gBarcodeName[0]);
	for (int i = 0; i<nCount; i++) {
		if (symbology == gBarcodeName[i].m_symbology)
			return gBarcodeName[i].m_strName;
	}
	return _T("");
}

CString CFOPBarcodeShape::GetTestBarCode(const SVBarCodeSymbology &symbology)
{
	if (m_pBarcode != NULL)
	{
		return m_pBarcode->GetDefaultValue();
	}
	return _T("");
}
