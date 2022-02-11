// SVImageControl.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include <afxpriv.h>

#include "SVImageControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// if(pEdit->IsKindOf(RUNTIME_CLASS(CSVImageControl)))
// {
// 	CSVImageControl *pImage = static_cast<CSVImageControl *>(pEdit);
// 	pImage->SetRealSize(this->m_bRealSize);
// 	pImage->SetTextHorzAlignment(this->m_nImageHorz);
// 	pImage->SetTextVertAlignment(this->m_nImageVert);
// 	pImage->SetColorOffset(this->m_nColorOffset);
// 	pImage->SetTransparentColor(this->GetColor());
// 	pImage->SetTransparent(this->m_bTransparent);
// 	pImage->SetRotateFlip((RotateFlipType)this->m_nRotate);
// 	pImage->SetAlpha(this->m_nAlpha);
// }

//////////////////////////////////////////////////////////////////////
// CSVImageControl Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CSVImageControl, CFOEditBoxShape, 0)
CSVImageControl::CSVImageControl()
{
	SetType(SV_COMP_IMAGE_CONTROL);
	SetBkColor(RGB(187,224,227));
	SetPolyObject(TRUE);
	SetMultiLine(TRUE);
	SetNullPen(TRUE);
	SetLineWidth(1);
	SetBrushType(0);
	SetFlat(TRUE);
	
	SetLineColor(RGB(128,128,145));
	SetWithLabelShow(FALSE);
	SetWithLabelEditing(FALSE);
	SetShowLabelAtFirst(FALSE);
	SetTextVertAlignment(TextCenter);
	SetTextHorzAlignment(TextMiddle);

	SetTabOrderProtect(FALSE);

 	m_imgFontName.Create(IDB_BITMAP_PIC, 20, 1, RGB(255,255,255));  
	CBitmap bm;
	bm.LoadBitmap(IDB_MB_COMP_TYPE);
	m_imgFontName.Add(&bm, RGB(255, 255, 255));

	m_pBitmapPlus = NULL;

	m_bRealSize = 1;
	m_bTransparent = FALSE;
	m_nColorOffset = 1;
	m_crTransparent = RGB(0, 0, 0);
	m_RotateFlip = RotateNoneFlipNone;

	m_dImageH = 0;
	m_dImageW = 0;
	m_nVertRes = 96.0f;
	m_nHoriRes = 96.0f;	
	
	m_nAlpha = 100;
	for (int i=0; i<5; i++)
	{
		for (int j=0; j<5; j++)
		{
			if (i == j) m_CM.m[i][j] = 1;
			else m_CM.m[i][j] = 0;
		}
	}

	m_strOldImagePath = _T("");
	m_strSerialsPath = _T("");
}

CSVImageControl::CSVImageControl(const CSVImageControl& src)
{
 	m_imgFontName.Create(IDB_BITMAP_PIC, 20, 1, RGB(255,255,255));  
	CBitmap bm;
	bm.LoadBitmap(IDB_MB_COMP_TYPE);
	m_imgFontName.Add(&bm, RGB(255, 255, 255));

	SetPolyObject(TRUE);
	*this = src;

	m_pBitmapPlus = NULL;

	m_dImageH = 0;
	m_dImageW = 0;
	m_nVertRes = 96.0f;
	m_nHoriRes = 96.0f;	

	m_bRealSize = src.m_bRealSize;
	m_bTransparent = src.m_bTransparent;
	m_nColorOffset = src.m_nColorOffset;
	m_crTransparent = src.m_crTransparent;
	m_RotateFlip = src.m_RotateFlip;
	
	m_nAlpha = src.m_nAlpha;
	for (int i=0; i<5; i++)
	{
		for (int j=0; j<5; j++)
		{
			if (i == j) m_CM.m[i][j] = 1;
			else m_CM.m[i][j] = 0;
		}
	}

	m_strOldImagePath = _T("");
	m_strSerialsPath = _T("");
}

CSVImageControl::~CSVImageControl()
{
	_SafeDeletePtr(m_pBitmapPlus);
}

/////////////////////////////////////////////////////////////////////////////
// CSVImageControl diagnostics

#ifdef _DEBUG
void CSVImageControl::AssertValid() const
{
	CFOEditBoxShape::AssertValid();
}

void CSVImageControl::Dump(CDumpContext& dc) const
{
	CFOEditBoxShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
CRect CSVImageControl::DoInitImagePos(int nImageWidth,int nImageHeight)
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

BOOL CSVImageControl::DoStartShowEdit(CFOPCanvasCore* pView, CPoint ptCursorSP)
{
	pView;
	ptCursorSP;

	CGdiplusFileOpenDialog openDlg;
	if (IDOK == openDlg.DoModal())
	{
		SetCurrentText(openDlg.GetPathName());
		return TRUE;
	}

	return FALSE;
}

void CSVImageControl::Create(CRect &rcPos,CString strCaption)
{
	CFOEditBoxShape::Create(rcPos,strCaption);

	CreateDefaultPort(0.5,0.5);
}

void CSVImageControl::Serialize(CArchive& ar)
{
	CFOEditBoxShape::Serialize(ar);
	m_strSerialsPath = ar.m_strFileName;

	if (ar.IsStoring())
	{
		if (m_pBitmapPlus == NULL)
		{
			ar << DWORD(0); 
		}
		else
		{
			ar << DWORD(1); 

			IStream *pstm = NULL;
			HGLOBAL m_hMem = GlobalAlloc(GMEM_MOVEABLE, 0);
			CreateStreamOnHGlobal(m_hMem, TRUE, &pstm);

			GUID clsid, clsidOut;
			m_pBitmapPlus->GetRawFormat(&clsid);
			if (CheckClsid(&clsid, &clsidOut) == FALSE) {
				GetCodecClsid(L"image/jpeg", &clsidOut);
			}

			Status stat = m_pBitmapPlus->Save(pstm, &clsidOut, NULL);
			if (stat != Ok || pstm == NULL )
			{
				DWORD wTemp = 0;
				LPBYTE lpData = NULL;
				ar << wTemp; 
				ar.Write(lpData, wTemp);
			}
			else
			{
				LARGE_INTEGER liBeggining = { 0 };
				pstm->Seek(liBeggining, STREAM_SEEK_SET, NULL);

				DWORD wTemp = GlobalSize(m_hMem);
				LPBYTE lpData = (LPBYTE)GlobalLock(m_hMem);
				ar << wTemp; 
				ar.Write(lpData, wTemp);
			}
			pstm->Release();
			GlobalUnlock(m_hMem);
		}

		ar << m_bRealSize;
		ar << m_bTransparent;
		ar << m_nColorOffset;
		ar << m_crTransparent;
		ar << (int)m_RotateFlip;
		ar << m_nAlpha;
	}
	else
	{
		_SafeDeletePtr(m_pBitmapPlus);

		DWORD wTemp = 0;
		ar >> wTemp; 
		if (wTemp == 0)
		{
			m_pBitmapPlus = NULL;
			m_dImageH = 0;
			m_dImageW = 0;
			m_nVertRes = 96.0f;
			m_nHoriRes = 96.0f;	
		}
		else
		{
			ar >> wTemp; 
			HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, wTemp);
			BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
			ar.Read(pmem, wTemp);

			IStream *pstm=NULL;
			CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);
			if (pstm != NULL)
			{
				m_pBitmapPlus = Bitmap::FromStream(pstm, FALSE);
				pstm->Release();
			}

			GlobalUnlock(m_hMem);

			if (NULL != m_pBitmapPlus)
			{
				m_dImageH = (REAL)m_pBitmapPlus->GetHeight();
				m_dImageW = (REAL)m_pBitmapPlus->GetWidth();
				m_nVertRes = m_pBitmapPlus->GetVerticalResolution();
				m_nHoriRes = m_pBitmapPlus->GetHorizontalResolution();
			}
			else
			{
				m_dImageH = 0;
				m_dImageW = 0;
				m_nVertRes = 96.0f;
				m_nHoriRes = 96.0f;	
			}
		}

		ar >> m_bRealSize;
		ar >> m_bTransparent;
		ar >> m_nColorOffset;
		ar >> m_crTransparent;

		int nTemp = 0;
		ar >> nTemp;
		m_RotateFlip = (RotateFlipType)nTemp;

		ar >> m_nAlpha;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CSVImageControl::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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
void CSVImageControl::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}
BOOL CSVImageControl::OpenDocument(LPCTSTR lpszPathName)
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

BOOL CSVImageControl::SaveDocument(LPCTSTR lpszPathName)
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

CSVImageControl& CSVImageControl::operator=(const CSVImageControl& src)
{
	(*(CFOEditBoxShape*)this) = src;
	if (NULL != src.m_pBitmapPlus)
	{
		m_pBitmapPlus = src.m_pBitmapPlus->Clone(0, 0, src.m_pBitmapPlus->GetWidth(), 
			src.m_pBitmapPlus->GetHeight(), src.m_pBitmapPlus->GetPixelFormat());

		if (NULL != m_pBitmapPlus)
		{
			m_dImageH = (REAL)m_pBitmapPlus->GetHeight();
			m_dImageW = (REAL)m_pBitmapPlus->GetWidth();
			m_nVertRes = m_pBitmapPlus->GetVerticalResolution();
			m_nHoriRes = m_pBitmapPlus->GetHorizontalResolution();		
		}
		else
		{
			m_dImageH = 0;
			m_dImageW = 0;
			m_nVertRes = 96.0f;
			m_nHoriRes = 96.0f;	
		}
	}
	else
	{
		m_pBitmapPlus = NULL;
		m_dImageH = 0;
		m_dImageW = 0;
		m_nVertRes = 96.0f;
		m_nHoriRes = 96.0f;	
	}
	return (*this);
}

CFODrawShape* CSVImageControl::Copy() const
{
	return (new CSVImageControl(*this));
}

void CSVImageControl::PrepareDC(CDC* pDC)
{
	CFOEditBoxShape::PrepareDC(pDC);
	//FODO:Add your own code below.
}

void CSVImageControl::OnDraw(CDC *pDC)
{
	CFOEditBoxShape::OnDraw(pDC);
}

void CSVImageControl::OnDrawTrackCustom(CDC *pDC)
{
	CFOEditBoxShape::OnDrawTrackCustom(pDC);
	// Add your own code here.
}

void CSVImageControl::OnDrawFlat(CDC *pDC)
{
	CFOEditBoxShape::OnDrawFlat(pDC);
	EncodeImageFile();
	DrawImage(pDC);
}

int CSVImageControl::CreateTextArray(CDC* pDC, CString strText,CRect rcBox,CStringArray& arLines)
{
	return CFODrawShape::CreateTextArray(pDC,strText,rcBox,arLines);
}

void CSVImageControl::OnDrawShadow(CDC *pDC)
{
	FillShadowPoly(pDC,m_lpShapePoints, m_nCompPtCount);
}

void CSVImageControl::OnDraw3d(CDC *pDC)
{
	CFOEditBoxShape::OnDraw3d(pDC);
	EncodeImageFile();
	DrawImage(pDC);
}

void CSVImageControl::DrawImage(CDC *pDC)
{
	FOPRect rcSnap = GetSnapRect();
	if (m_pBitmapPlus == NULL || 0 == m_dImageW || 0 == m_dImageH)
	{
		if (FALSE == pDC->IsPrinting()) 
		{
			pDC->Draw3dRect(rcSnap, RGB(0,0,0), RGB(0,0,0));

			CPen mypen(PS_SOLID, 1, RGB(0,0,0));
			CPen *pOld = (CPen *)pDC->SelectObject(&mypen);
			pDC->MoveTo(rcSnap.TopLeft());
			pDC->LineTo(rcSnap.BottomRight());
			pDC->MoveTo(rcSnap.TopRight());
			pDC->LineTo(rcSnap.BottomLeft());

			pDC->SelectObject(pOld);
			mypen.DeleteObject();

			m_imgFontName.Draw(pDC, 0, CPoint(rcSnap.left+2, rcSnap.top+2), ILD_TRANSPARENT);
			
		}

		return;
	}

	if (FALSE == IsNullPen()) 
	{
		int nHalfLine = (int)(GetLineWidth()+1)/2;
		rcSnap.DeflateRect(nHalfLine, nHalfLine);
	}

	if (RotateNoneFlipNone != m_RotateFlip) 
	{
		m_pBitmapPlus->RotateFlip(m_RotateFlip);
	}

 	Graphics graphics(pDC->m_hDC);
	graphics.SetPageUnit(UnitPixel); // Must be set for printing
	if (TRUE == pDC->IsPrinting())
	{
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		graphics.SetCompositingQuality(CompositingQualityHighQuality);
		graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	}
	else
	{
		graphics.SetSmoothingMode(SmoothingModeHighSpeed);
		graphics.SetCompositingQuality(CompositingQualityHighSpeed);
		graphics.SetInterpolationMode(InterpolationModeLowQuality);
	}

	RectF rcDest((REAL)rcSnap.left, (REAL)rcSnap.top, (REAL)rcSnap.Width(), (REAL)rcSnap.Height());
	RectF rcImag(0, 0, m_dImageW, m_dImageH);
 	if (1 == m_RotateFlip || 3 == m_RotateFlip) {
		rcImag = RectF(0, 0, m_dImageH, m_dImageW);
	}

	if (0 == m_bRealSize)
	{ 
 		if (m_RotateFlip == 1 || m_RotateFlip == 3) {
			REAL rTemp = m_dImageH;
			m_dImageH = m_dImageW;
			m_dImageW = rTemp;
		}

		REAL dW = m_dImageW*96.0f/m_nHoriRes;
		REAL dH = m_dImageH*96.0f/m_nVertRes;
		
		REAL nSpaceW = ((REAL)rcSnap.Width() -dW)/2.0f;
		REAL nSpaceH = ((REAL)rcSnap.Height()-dH)/2.0f;
		
		if (nSpaceW >= 0)
		{
			rcDest.X = (REAL)rcSnap.left +nSpaceW;
			rcDest.Width = dW;
		}
		else
		{
			rcImag.X = -nSpaceW;
			rcImag.Width = rcDest.Width*m_nHoriRes/96.0f;
		}
		
		if (nSpaceH >= 0)
		{
			rcDest.Y = (REAL)rcSnap.top + nSpaceH;
			rcDest.Height = dH;
		}
		else
		{
			rcImag.Y = -nSpaceH;
			rcImag.Height = rcDest.Height*m_nVertRes/96.0f;
		}

 		if (m_RotateFlip == 1 || m_RotateFlip == 3) {
			REAL rTemp = m_dImageH;
			m_dImageH = m_dImageW;
			m_dImageW = rTemp;
		}
	}
	else if (1 == m_bRealSize)
	{ 
		REAL dDraw = REAL(rcSnap.Width())/REAL(rcSnap.Height());
		REAL dImage = m_dImageW/m_dImageH;
		if (m_RotateFlip == 1 || m_RotateFlip == 3) {
			dImage = m_dImageH/m_dImageW;
		}
		
		if (dDraw>dImage)
		{
			rcDest.X = rcSnap.left + (rcSnap.Width()-rcSnap.Height()*dImage)/2.0f;
			rcDest.Y = (REAL)rcSnap.top;
			rcDest.Width = rcSnap.Height()*dImage;
			rcDest.Height = (REAL)rcSnap.Height();
		}
		else
		{
			rcDest.X = (REAL)rcSnap.left;
			rcDest.Y = rcSnap.top + (rcSnap.Height()-rcSnap.Width()/dImage)/2.0f;
			rcDest.Width = (REAL)rcSnap.Width();
			rcDest.Height = rcSnap.Width()/dImage;
		}
	}
	else if (2 == m_bRealSize)
	{ 
		rcDest = RectF((REAL)rcSnap.left, (REAL)rcSnap.top, (REAL)rcSnap.Width(), (REAL)rcSnap.Height());
	}
	else
	{//	Tile
		rcDest = RectF((REAL)rcSnap.left, (REAL)rcSnap.top, (REAL)rcSnap.Width(), (REAL)rcSnap.Height());
		TextureBrush *pBrTexture = new TextureBrush(m_pBitmapPlus);
		graphics.FillRectangle(pBrTexture, rcDest);
		_SafeDeletePtr(pBrTexture);
		
 		if (RotateNoneFlipNone != m_RotateFlip) {
			m_pBitmapPlus->RotateFlip(RotateFlipType(4-m_RotateFlip));
		}
		return;
	}

 	ImageAttributes m_imAtt;
	if (TRUE == m_bTransparent)
	{
		m_imAtt.Reset();
		m_imAtt.ClearColorKey();
		
		int nR = GetRValue(m_crTransparent)-m_nColorOffset<0? 0:GetRValue(m_crTransparent)-m_nColorOffset;
		int nG = GetGValue(m_crTransparent)-m_nColorOffset<0? 0:GetGValue(m_crTransparent)-m_nColorOffset;
		int nB = GetBValue(m_crTransparent)-m_nColorOffset<0? 0:GetBValue(m_crTransparent)-m_nColorOffset;
		Color crLow((BYTE)nR, (BYTE)nG, (BYTE)nB);
		
		nR = GetRValue(m_crTransparent)+m_nColorOffset>255? 255:GetRValue(m_crTransparent)+m_nColorOffset;
		nG = GetGValue(m_crTransparent)+m_nColorOffset>255? 255:GetGValue(m_crTransparent)+m_nColorOffset;
		nB = GetBValue(m_crTransparent)+m_nColorOffset>255? 255:GetBValue(m_crTransparent)+m_nColorOffset;
		Color crHigh((BYTE)nR, (BYTE)nG, (BYTE)nB);
		
		m_imAtt.SetColorKey(crLow, crHigh);
	}

 	if (m_nAlpha<1) m_nAlpha=100;
	if (m_nAlpha>100) m_nAlpha=100;
	m_CM.m[3][3] = float(m_nAlpha)/100.0f;
	m_imAtt.SetColorMatrix(&m_CM);

 	REAL nXOffset = 0, nYOffset = 0;
	UINT iVert = GetTextVertAlignment();
	UINT iHorz = GetTextHorzAlignment();
	if (TextLeft == iHorz) {
		nXOffset = rcSnap.left - rcDest.GetLeft();
	} else if(TextRight == iHorz) {
		nXOffset = rcSnap.right - rcDest.GetRight();
	}
	if (TextTop == iVert) {
		nYOffset = rcSnap.top - rcDest.GetTop();
	} else if(TextBottom == iVert) {
		nYOffset = rcSnap.bottom - rcDest.GetBottom();
	}
	rcDest.Offset(nXOffset, nYOffset);

 	Region oldClipping; graphics.GetClip(&oldClipping);
	Region newClip(rcDest); graphics.SetClip(&newClip);
	graphics.DrawImage(m_pBitmapPlus, rcDest, rcImag.X, rcImag.Y, rcImag.Width, rcImag.Height, UnitPixel, &m_imAtt);	
	graphics.ResetClip();
	
 	if (RotateNoneFlipNone != m_RotateFlip) {
		m_pBitmapPlus->RotateFlip(RotateFlipType(4-m_RotateFlip));
	}
}

void CSVImageControl::ClearDC(CDC* pDC)
{
	CFOEditBoxShape::ClearDC(pDC);
}

void CSVImageControl::RotateShape(int nAngle, float fOriginX, float fOriginY)
{
	CFOEditBoxShape::RotateShape(nAngle,fOriginX,fOriginY);
}

void CSVImageControl::RotateTrackShape(int nAngle, float fOriginX, float fOriginY)
{
	CFOEditBoxShape::RotateTrackShape(nAngle,fOriginX,fOriginY);
}

void CSVImageControl::GeometryUpdated(CFOArea* pRgn)
{
	if (m_lpShapePoints && pRgn)
	{
		pRgn->BuildPolygonArea(m_lpShapePoints, m_nCompPtCount);
		m_rectPosition = pRgn->GetBoundingRect();
	}
}

void CSVImageControl::GetCurrentText(CString& strResult)
{
	CString str = CFOEditBoxShape::GetCurrentText();
	strResult = str;
}

void CSVImageControl::SetCurrentText(const CString& str)
{
	CFOEditBoxShape::SetCurrentText(str);
}

void CSVImageControl::EncodeImageFile()
{
	CString strlabel = GenEditingLabel();
	if (strlabel == m_strOldImagePath) {
		return;
	} else {
		m_strOldImagePath = strlabel;
	}

	_SafeDeletePtr(m_pBitmapPlus);
	if (strlabel == _T(""))
	{
		m_dImageH = 0;
		m_dImageW = 0;
		m_nVertRes = 96.0f;
		m_nHoriRes = 96.0f;	
	}
	else
	{
		CString strTemp = CheckCurrentImage(strlabel);

	#ifndef _UNICODE
		USES_CONVERSION;
		m_pBitmapPlus = Bitmap::FromFile(A2W(strTemp));
	#else
		m_pBitmapPlus = Bitmap::FromFile(strTemp);
	#endif

		if (NULL != m_pBitmapPlus)
		{
			m_dImageH = (REAL)m_pBitmapPlus->GetHeight();
			m_dImageW = (REAL)m_pBitmapPlus->GetWidth();
			m_nVertRes = m_pBitmapPlus->GetVerticalResolution();
			m_nHoriRes = m_pBitmapPlus->GetHorizontalResolution();		
		}
		else
		{
			m_dImageH = 0;
			m_dImageW = 0;
			m_nVertRes = 96.0f;
			m_nHoriRes = 96.0f;	
		}
	}
}

BOOL CSVImageControl::GetCodecClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	GetImageEncodersSize(&num, &size);
	if (size == 0) return FALSE;  // Failure

	ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL) return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return TRUE;
		}    
	}

// for
	free(pImageCodecInfo);
	return FALSE;  // Failure
}

BOOL CSVImageControl::CheckClsid(CLSID* pClsid, GUID *clsidOut)
{
	BOOL bFild = FALSE;
	
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return bFild;  // Failure

	ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return bFild;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (pImageCodecInfo[j].FormatID == *pClsid )
		{
			*clsidOut = pImageCodecInfo[j].Clsid;
			bFild = TRUE;  // Success
			break;
		}    
	} // for
	free(pImageCodecInfo);
	return bFild;  // Failure
}

void CSVImageControl::OnDrawText(CDC *pDC)
{
	//FODO:Add your own code below.
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
}

CString CSVImageControl::CheckCurrentImage(const CString &strImageName)
{
	if (_T("") == strImageName) {
		return _T("");
	}

 	CFileStatus rStatus;
	if (TRUE == CFile::GetStatus(strImageName, rStatus)) {
		return strImageName;
	}

	CString strName = strImageName.Right(strImageName.GetLength()-strImageName.ReverseFind('\\')-1);
	if (_T("") == strName) {
		strName = strImageName;
	}

 //	CHokRegeditManager regedit;
	CString strImagePath = _T("");//regedit.GetProfileString(gsv_strProfile, gsv_strGraphicPath, XD::g_GetGraphicsFolder());
	if (strImagePath.GetLength()>0 && '\\' != strImagePath[strImagePath.GetLength()-1]) {
		strImagePath = strImagePath + _T("\\");
	}

	CString strRetFileName = strImagePath + strName;
	if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
		return strRetFileName;
	}

 	if (_T("") != m_strSerialsPath)
	{
 		CString strPath = m_strSerialsPath.Left(m_strSerialsPath.ReverseFind('\\'));

 		strRetFileName = strPath+_T("\\")+strName;
		if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
			return strRetFileName;
		}

 		strRetFileName = strPath+_T("\\Image\\")+strName;
		if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
			return strRetFileName;
		}

 		strRetFileName = strPath+_T("\\Images\\")+strName;
		if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
			return strRetFileName;
		}

 		strRetFileName = strPath+_T("\\Picture\\")+strName;
		if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
			return strRetFileName;
		}

 		strRetFileName = strPath+_T("\\Image\\")+strName;
		if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
			return strRetFileName;
		}

 		strRetFileName = strPath+_T("\\Photo\\")+strName;
		if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
			return strRetFileName;
		}
	}

 	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	strRetFileName = strPathX + strName;
	if (TRUE == CFile::GetStatus(strRetFileName, rStatus)) {
		return strRetFileName;
	}

	return _T("");
}


/////////////////////////////////////////////////////////////////////////////
// CGdiplusFileDialog

IMPLEMENT_DYNAMIC(CGdiplusFileDialog, CFileDialog)

/******************************************************************************
Function: CGdiplusFileDialog::CGdiplusFileDialog
Purpose:  Constructor
******************************************************************************/
CGdiplusFileDialog::CGdiplusFileDialog(BOOL bOpenFileDialog, 
                                       LPCTSTR lpszFileName, 
                                       DWORD dwFlags,
                                       CWnd* pParentWnd)
									   : CFileDialog(bOpenFileDialog, 
									   NULL, 
									   lpszFileName, 
									   dwFlags, 
									   NULL, 
									   pParentWnd)
{
}
/******************************************************************************
Function: CGdiplusFileDialog::DoModal
Purpose:  Override CFileDialog::DoModal 
******************************************************************************/
int CGdiplusFileDialog::DoModal()
{
	// make a little test to see if GDI+ is initialized
	Bitmap bitmap(1, 1);
	if(GdiplusNotInitialized == bitmap.GetLastStatus())
	{
		TRACE(_T("GDI+ not initialized\n Please, call GdiplusStartup in InitInstance of application to initialize GDI+"));
		return IDCANCEL;
	}
	
	// FillCodecInfoArray and ConstructMFCStyleFilter are pure virtual
	// functions and are overriden in derived classes for specific implementation
	FillCodecInfoArray();
	ConstructMFCStyleFilter();
	
	TranslateFilter();
	return CFileDialog::DoModal(); // call base class function and return
}
/******************************************************************************
Function: CGdiplusFileDialog::TranslateFilter
Purpose:  "Translate" MFC CFileDialog style filter in
into OPENFILENAME structure style filter 
******************************************************************************/
void CGdiplusFileDialog::TranslateFilter()
{
	// Note: the code below is adapted from MFC implementation of CFileDialog
	// Translate filter into commdlg format (lots of \0)
	if(!m_strFilter.IsEmpty())
	{
		LPTSTR pch = m_strFilter.GetBuffer(0); // modify the buffer in place
		// MFC delimits with '|' not '\0'
		while ((pch = _tcschr(pch, '|')) != NULL)
			*pch++ = '\0';
		m_ofn.lpstrFilter = m_strFilter;
		// do not call ReleaseBuffer() since the string contains '\0' characters
	}
}

BEGIN_MESSAGE_MAP(CGdiplusFileDialog, CFileDialog)
//{{AFX_MSG_MAP(CGdiplusFileDialog)
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/******************************************************************************
Function: CGdiplusFileDialog::OnDestroy
Purpose:  WM_DESTROY message hadler
Remarks:  After calling base class function, free dynamic allocated memory
******************************************************************************/
void CGdiplusFileDialog::OnDestroy() 
{
	CFileDialog::OnDestroy();
	
	// clean the garbage
	const int nSize = m_arrCodecInfo.GetSize();
	for(int nIndex = 0; nIndex < nSize; nIndex++)
	{
		CGdiplusCodecInfo* pcodecInfo = m_arrCodecInfo.GetAt(nIndex);
		delete pcodecInfo;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CGdiplusFileOpenDialog

IMPLEMENT_DYNAMIC(CGdiplusFileOpenDialog, CGdiplusFileDialog)

/******************************************************************************
Function: CGdiplusFileOpenDialog::CGdiplusFileOpenDialog
Purpose:  Constructor
******************************************************************************/
CGdiplusFileOpenDialog::CGdiplusFileOpenDialog(LPCTSTR lpszFileName /*=NULL*/, 
                                               DWORD dwFlags /*=OFN_HIDEREADONLY*/,
                                               CWnd* pParentWnd /*=NULL*/)
											   : CGdiplusFileDialog(TRUE, // Open dialog 
											   lpszFileName, 
											   dwFlags,
											   pParentWnd)
{
}

/******************************************************************************
Function: CGdiplusFileOpenDialog::FillCodecInfoArray
Purpose:  Get info for GDI+ supported decoders further used 
to construct Open file dialog filter
Remarks:  Call GetImageDecoders to get information 
about the available image decoders.
******************************************************************************/
void CGdiplusFileOpenDialog::FillCodecInfoArray()
{
	// get decoders info
	
	UINT  nDecCount = 0;  // number of image decoders
	UINT  nDecSize  = 0;  // size of the image decoder array in bytes
	
	ImageCodecInfo* pImageCodecInfo = NULL;
	
	
	GetImageDecodersSize(&nDecCount, &nDecSize);
	pImageCodecInfo = (ImageCodecInfo*) malloc(nDecSize);
	GetImageDecoders(nDecCount, nDecSize, pImageCodecInfo);
	
	m_arrCodecInfo.SetSize(nDecCount);
	for(UINT nIndex = 0; nIndex < nDecCount; nIndex++)
	{
		CGdiplusCodecInfo* pcodecInfo = 
			new CGdiplusCodecInfo(pImageCodecInfo[nIndex].FormatDescription,
			pImageCodecInfo[nIndex].FilenameExtension,
			pImageCodecInfo[nIndex].Clsid);
		
		m_arrCodecInfo.SetAt(nIndex, pcodecInfo);
	}
	free(pImageCodecInfo);
}
/******************************************************************************
Function: CGdiplusFileOpenDialog::ConstructMFCStyleFilter 
Purpose:  Constructs "MFC style" filter (using '|' as separator)
Remarks:  An "All GDI+ supported" item is added to filter 
******************************************************************************/
void CGdiplusFileOpenDialog::ConstructMFCStyleFilter()
{
	const UINT nSize = m_arrCodecInfo.GetSize();
	CString strFilterItem, strFilter;
	CString strAllSupported = _T("All Supported Files|");
	for(UINT nIndex = 0; nIndex < nSize; nIndex++)
	{
		CGdiplusCodecInfo* pCodecInfo = m_arrCodecInfo.ElementAt(nIndex);
		strFilterItem.Format(_T("%s files(%s)|%s|"),
			pCodecInfo->GetFormat(),
			pCodecInfo->GetExtensions(),
			pCodecInfo->GetExtensions());
		strFilter += strFilterItem;
		strAllSupported += pCodecInfo->GetExtensions();
		if(nIndex < nSize - 1)
		{
			strAllSupported += _T(";");
		}
	}
	// Prepend "All GDI+ supported" to filter
	m_strFilter.Format(_T("%s|%s|"), strAllSupported, strFilter);
}

BEGIN_MESSAGE_MAP(CGdiplusFileOpenDialog, CGdiplusFileDialog)
//{{AFX_MSG_MAP(CGdiplusFileOpenDialog)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/******************************************************************************
Function: CGdiplusCodecInfo::CGdiplusCodecInfo
Purpose:  Constructor
******************************************************************************/
CGdiplusCodecInfo::CGdiplusCodecInfo(LPCWSTR wcsFormat, 
                                     LPCWSTR wcsExtensions, 
                                     const CLSID& clsid)
{
	ConvertCopy(m_strFormat, wcsFormat);
	ConvertCopy(m_strExtensions, wcsExtensions);
	
	m_strExtensions.MakeLower();
	
	memcpy(&m_clsid, &clsid, sizeof(CLSID));
	
	const int nPos = m_strExtensions.Find(_T(';'));
	if(-1 != nPos)
	{
		m_strDefExt = m_strExtensions.Left(nPos);
	}
	else
	{
		m_strDefExt = m_strExtensions;
	}
	m_strDefExt.Remove(_T('*'));
	m_strDefExt.Remove(_T('.'));
}

/******************************************************************************
Function: CGdiplusCodecInfo::FindExtension
Purpose:  Returns true if given extension is found in "used extensions:
string (m_strExtensions)
Remarks:  Called in CGdiplusFileSaveAsDialog::OnFileNameOK
to decide if "File Name" field contains a valid extension
******************************************************************************/
bool CGdiplusCodecInfo::FindExtension(LPCTSTR pszExt)
{
	bool bFound = false;
	
	LPCTSTR const pszDelimit = _T(";");
	CString strExt;
	strExt.Format(_T("*.%s"), pszExt);
	
	const int nLength = 1 + m_strExtensions.GetLength();
	LPTSTR pszBuffer = m_strExtensions.GetBuffer(nLength);
	
	LPTSTR pszToken = _tcstok(pszBuffer, pszDelimit);
	while(NULL != pszToken)
	{
		if(! strExt.CompareNoCase(pszToken))
		{
			bFound = true;
			break;
		}
		pszToken = _tcstok(NULL, pszDelimit);
	}
	m_strExtensions.ReleaseBuffer();
	
	return bFound;
}

/******************************************************************************
Function: CGdiplusCodecInfo::ConvertCopy
Purpose:  Convert if needed wide characters input 
string and copy it into dstination
******************************************************************************/
void CGdiplusCodecInfo::ConvertCopy(CString& str, LPCWSTR wcs)
{
#ifdef UNICODE
	str = wcs;
#else
	size_t size = 1 + wcslen(wcs);
	wcstombs(str.GetBuffer(size), wcs, size);
	str.ReleaseBuffer();
#endif // UNICODE
}
