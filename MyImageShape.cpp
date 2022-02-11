// MyImageShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyImageShape.h"
#include <afxpriv.h>
#include "UCCPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// CMyImageShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMyImageShape, CFOImageShape, 0)
CMyImageShape::CMyImageShape()
{
	SetType(MY_IMAGE_TYPE);
	SetBkColor(RGB(187,224,227));
	SetPolyObject(TRUE);
	SetMultiLine(TRUE);
	SetNullPen(TRUE);
	SetLineWidth(1);
	SetBrushType(0);
	SetLineColor(RGB(128,128,145));
	SetWithLabelShow( FALSE );
//	m_bWithLabelEditing = FALSE;
	SetTransparentValue(100);
	SetTabOrderProtect(TRUE);
	m_imgFontName.Create(IDB_BITMAP_PIC, 20, 1, RGB(255,255,255));

}

CMyImageShape::CMyImageShape(const CMyImageShape& src)
{
	m_imgFontName.Create(IDB_BITMAP_PIC, 20, 1, RGB(255,255,255));
	SetPolyObject(TRUE);
	*this = src;
}

CMyImageShape::~CMyImageShape()
{

}

/////////////////////////////////////////////////////////////////////////////
// CMyImageShape diagnostics

#ifdef _DEBUG
void CMyImageShape::AssertValid() const
{
	CFOImageShape::AssertValid();
}

void CMyImageShape::Dump(CDumpContext& dc) const
{
	CFOImageShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
CRect CMyImageShape::DoInitImagePos(int nImageWidth,int nImageHeight)
{
	if(m_rectPosition.IsRectEmpty() || 
		(m_rectPosition.Width() == 0) || 
		(m_rectPosition.Height() == 0))
	{
		CRect rcTemp = CRect(m_rectPosition.left,
			m_rectPosition.top,
			m_rectPosition.left+nImageWidth,
			m_rectPosition.top +nImageHeight);
		
		rcTemp.NormalizeRect();
		return rcTemp;
	}
	else
	{
		return m_rectPosition;
	}
}


BOOL CMyImageShape::DoStartShowEdit(CFOPCanvasCore* pView, CPoint ptCursorSP)
{
	pView;
	ptCursorSP;
    CString strFilter;
	strFilter.LoadString(IDS_FO_IMAGE_EXTENSION);
	
	CString title;
	title.LoadString(IDS_FO_OPEN_FILE_TITLE);
	CFileDialog dlgFile (TRUE,NULL,NULL,OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,strFilter,AfxGetMainWnd());
	if(dlgFile.DoModal() == IDOK)
	{
		if (dlgFile.GetFileExt().CompareNoCase(_T("wmf")) == 0)
		{
			return FALSE;
		}
		else if(dlgFile.GetFileExt().CompareNoCase(_T("emf")) == 0)
		{
			return FALSE;
		}
		else
		{
			CString strFileName = dlgFile.GetPathName();
			CString filename(strFileName);
			CString ext(CFODrawHelper::FindExtension(filename));
			ext.MakeLower();
			if (ext == _T(""))
			{
				return FALSE;
			}
			
			FO_IMAGETYPE type = CFODrawHelper::FindType(ext);

			BOOL bLoad = LoadImage(strFileName,type);

			if(!bLoad)
			{
				return FALSE;
			}
			int nAngle = GetRotateAngle();
			CFOBitmap *pTempImage = m_pImagePtr->GetBitmap();
			m_DrawImage.m_nAngle = nAngle;
			m_DrawImage.RebuildImage(pTempImage);

			return FALSE;
		}
	}
	return FALSE;
}

void CMyImageShape::Create(CRect &rcPos,CString strCaption)
{
	CFOImageShape::Create(rcPos,strCaption);

	CreateDefaultPort(0.5,0.5);
	
}

void CMyImageShape::Serialize(CArchive& ar)
{
	CFODrawPortsShape::Serialize(ar);
	m_ImageData.RemoveData();
	if(ar.IsStoring())
	{
		ar << m_nImageType;
		BOOL bSave = FALSE;
		if(m_pImagePtr != NULL)
		{
			bSave = TRUE;
		}
		ar << bSave;
		if(bSave)
		{
			m_pImagePtr->Serialize(ar);
		}

		ar << m_bImageTransparent;
		ar << m_crImageTransparent;
	}
	else
	{
		int nTemp;
		ar >> nTemp;
		m_nImageType = nTemp;

		BOOL bSave;
		ar >> bSave;

		m_bGif					= FALSE;

		if(bSave)
		{
			CFODrawImage *pImage = NULL;
			switch(m_nImageType)
			{
			case FO_IMAGE_BMP: // Load bitmap file.
				{
					pImage = new CFODrawImage();
					
				}
				break;
				
			case FO_IMAGE_ICO: // Load icon file
				{
					pImage = new CFODrawImage();
					
				}
				break;
				
			case FO_IMAGE_PCX: // Load pcx file.
				{
					pImage = new CFODrawImagePCX();
					
				}
				break;
				
			case FO_IMAGE_JPG: // Load jpeg file.
				{
					pImage = new CFODrawImageJPEG();
					
				}
				break;
				
			case FO_IMAGE_PNG: // Load png file.
				{
					pImage = new CFODrawImagePNG();
				}
				break;
				
			case FO_IMAGE_GIF: // Load GIF file.
				{
					pImage = new CFODrawImageGIF();
					m_bGif					= TRUE;
				}
				break;
				
			case FO_IMAGE_TGA: // Load TGA file.
				{
					pImage = new CFODrawImageTGA();
				}
				break;
				
			case FO_IMAGE_MNG: // Load Mng file.
				{
					pImage = new CFODrawImageMNG();
					
				}
				break;
				
			default: // Load bitmap file or icon file.
				{
					pImage = new CFODrawImage();
				}
				break;
			}
			pImage->Serialize(ar);
			//		ar >> pImage;
			
			CFODrawImageData pPointer = pImage;
			
			m_pImagePtr = m_ImageData.FindImage(pPointer);
		}

		ar >> m_bImageTransparent;
		ar >> m_crImageTransparent;

		if(m_pImagePtrOrMask != NULL)
		{
			delete m_pImagePtrOrMask;
			m_pImagePtrOrMask = NULL;
		}
		if(m_pImagePtrAndMask != NULL)
		{
			delete m_pImagePtrAndMask;
			m_pImagePtrAndMask = NULL;
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CMyImageShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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
void CMyImageShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}
BOOL CMyImageShape::OpenDocument(LPCTSTR lpszPathName)
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
BOOL CMyImageShape::SaveDocument(LPCTSTR lpszPathName)
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


CMyImageShape& CMyImageShape::operator=(const CMyImageShape& src)
{
	(*(CFOImageShape*)this) = src;
	return (*this);
}

CFODrawShape* CMyImageShape::Copy() const
{
	return (new CMyImageShape(*this));
}

void CMyImageShape::PrepareDC(CDC* pDC)
{
	CFOImageShape::PrepareDC(pDC);
	//FODO:Add your own code below.
	
}

void CMyImageShape::OnDraw(CDC *pDC)
{
	CFOImageShape::OnDraw(pDC);
}

void CMyImageShape::OnDrawTrackCustom(CDC *pDC)
{
	CFOImageShape::OnDrawTrackCustom(pDC);
	// Add your own code here.
}

void CMyImageShape::OnDrawFlat(CDC *pDC)
{
	CFOImageShape::OnDrawFlat(pDC);

	BOOL bDraw = FALSE;
	if(m_pImagePtr != NULL)
	{
		if(m_pImagePtr->GetBitmap()->IsValidate())
		{
			bDraw = TRUE;
		}
	}

	if(!bDraw)
	{
		CRect rc = GetSnapRect();
		m_imgFontName.Draw(pDC, 0, CPoint(rc.left+2, rc.top+2),ILD_TRANSPARENT);
	}

	/*CRect rcTemp;
	rcTemp = CRect(m_lpShapePoints[0],m_lpShapePoints[2]);
	rcTemp.NormalizeRect();

	CString strText = GetObjectCaption();
	CRect rcNew = rcTemp;
	rcNew.InflateRect(2000,2000,2000,2000);
	CSize sizeText = GetTextSize(pDC,rcNew,strText);

	rcTemp.bottom -= sizeText.cy;
	DoDrawImage(pDC,rcTemp);

	CRect rcText;
	rcText = rcTemp;
	rcText.top = rcTemp.bottom;
	rcText.bottom = rcText.top + sizeText.cy;
	pDC->Rectangle(&rcText);
	if (m_pEdit != NULL)
	{
		if(m_bWithLabelEditing)
		{
			OnDrawTextAndEdit(pDC,rcText,FALSE);
		}
	}
	else
	{
		DrawText(pDC,GetObjectCaption(),&rcText,GetDrawFormatType());
	}*/

	//FODO:Add your own code below.
}

CSize CMyImageShape::GetTextSize(CDC* pDC,CRect rcPos,CString strText)
{
	CSize sizeText(0,0);
	
	CFont* pFont = NULL;
	CFont* pPrevFont = NULL;
	
	{
		pFont = GetFont();
		pPrevFont = (CFont*) pDC->SelectObject(pFont);
	}
	
	CStringArray setBreaks;
	CreateTextArray(pDC,strText,rcPos,setBreaks);
	
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	
	for (int nBreak = 0; nBreak < setBreaks.GetSize(); nBreak++)
	{
		CString strLine = setBreaks.GetAt(nBreak);
		CSize sizeLine(0,0);
		
		if (strLine.GetLength() > 0)
		{
			sizeLine = pDC->GetTextExtent(strLine);
		}
		else
		{
			sizeLine.cx = 1;
			sizeLine.cy = tm.tmHeight;
		}
		
		sizeText.cx = FORMMAX(sizeText.cx, sizeLine.cx);
		sizeText.cy += sizeLine.cy;
	}
	
	pDC->SelectObject(pPrevFont);
	
	return sizeText;
}


UINT CMyImageShape::GetDrawFormatType()
{
	UINT nTextHorz = GetTextHorzAlignment();
	UINT nTextVert = GetTextVertAlignment();
	UINT nAlign;
	if(IsMultiLine())
	{
		nAlign = DT_WORDBREAK;
		switch(nTextHorz)
		{
		case TextLeft: 
			{
				nAlign |= DT_LEFT;
			}
			break;
		case TextMiddle: 
			{
				nAlign |= DT_CENTER;
			}
			break;
		case TextRight:
			{
				nAlign |= DT_RIGHT;
			}
			break;
			
		}
	}
	else
	{
		nAlign = DT_SINGLELINE;
		switch(nTextHorz)
		{
		case TextLeft: 
			{
				nAlign |= DT_LEFT;
			}
			break;
		case TextMiddle: 
			{
				nAlign |= DT_CENTER;
			}
			break;
		case TextRight:
			{
				nAlign |= DT_RIGHT;
			}
			break;
			
		}
		
		switch(nTextVert)
		{
		case TextTop: 
			{
				nAlign |= DT_TOP;
			}
			break;
		case TextCenter: 
			{
				nAlign |= DT_VCENTER;
			}
			break;
		case TextBottom:
			{
				nAlign |= DT_BOTTOM;
			}
			break;
			
		}
	}
	return nAlign;
}

int CMyImageShape::CreateTextArray(CDC* pDC, CString strText,CRect rcBox,CStringArray& arLines)
{
	return CFODrawShape::CreateTextArray(pDC,strText,rcBox,arLines);
}

void CMyImageShape::OnDrawShadow(CDC *pDC)
{
	FillShadowPoly(pDC,m_lpShapePoints, m_nCompPtCount);
}

void CMyImageShape::OnDraw3d(CDC *pDC)
{
	CFOImageShape::OnDraw3d(pDC);

	BOOL bDraw = FALSE;
	if(m_pImagePtr != NULL)
	{
		if(m_pImagePtr->GetBitmap()->IsValidate())
		{
			bDraw = TRUE;
		}
	}

	if(!bDraw)
	{
		CRect rc = GetSnapRect();
		m_imgFontName.Draw(pDC, 0, CPoint(rc.left+2, rc.top+2),ILD_TRANSPARENT);
	}

	/*CRect rcTemp;
	rcTemp = CRect(m_lpShapePoints[0],m_lpShapePoints[2]);
	rcTemp.NormalizeRect();

	CString strText = GetObjectCaption();
	CRect rcNew = rcTemp;
	rcNew.InflateRect(2000,2000,2000,2000);
	CSize sizeText = GetTextSize(pDC,rcNew,strText);

	rcTemp.bottom -= sizeText.cy;
	DoDrawImage(pDC,rcTemp);

	CRect rcText;
	rcText = rcTemp;
	rcText.top = rcTemp.bottom;
	rcText.bottom = rcText.top + sizeText.cy;
	pDC->Rectangle(&rcText);

	if (m_pEdit != NULL)
	{
		if(m_bWithLabelEditing)
		{
			OnDrawTextAndEdit(pDC,rcText,FALSE);
		}
	}
	else
	{
		DrawText(pDC,GetObjectCaption(),&rcText,GetDrawFormatType());
	}*/
}

void CMyImageShape::ClearDC(CDC* pDC)
{
	CFOImageShape::ClearDC(pDC);
	//FODO:Add your own code below.
}

void CMyImageShape::RotateShape(double nAngle, float fOriginX, float fOriginY)
{
	CFOImageShape::RotateShape(nAngle,fOriginX,fOriginY);
}

void CMyImageShape::RotateTrackShape(double nAngle, float fOriginX, float fOriginY)
{
	CFOImageShape::RotateTrackShape(nAngle,fOriginX,fOriginY);
}


void CMyImageShape::GeometryUpdated(CFOArea* pRgn)
{
	if (m_lpShapePoints && pRgn)
	{
		pRgn->BuildPolygonArea(m_lpShapePoints, m_nCompPtCount);
		m_rectPosition = pRgn->GetBoundingRect();
	}
}
