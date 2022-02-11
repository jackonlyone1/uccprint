// FOEFHyperLinkShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FOEFHyperLinkShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CFOEFHyperLinkShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CFOEFHyperLinkShape, CFOPEFormBaseShape, VERSIONABLE_SCHEMA | 1)
CFOEFHyperLinkShape::CFOEFHyperLinkShape()
{
	SetType(MY_EXT_HYPERLINK);
	SetTransparent(TRUE);
	SetBrushType(0);
	ShowFontProp(TRUE);
	SetTabOrderProtect(FALSE);
	m_bShowLabelAtFirst = TRUE;
	SetTextHorzAlignment(TextLeft);
	SetTextVertAlignment(TextTop);
	SetFontColor(RGB(0, 0, 238));
	SetMultiLine(FALSE);
	SetUnderline(TRUE);
	SetPolyObject(TRUE);
	SetNullPen(TRUE);

	m_bNeedCreate		= TRUE;
	SetAutoTextSize(	TRUE );
	SetShowLabelAtFirst(TRUE);
	m_bWithTextWrap		= TRUE;

	m_pBorderPen	= NULL;
	SetNeedForDB(TRUE);
}

CFOEFHyperLinkShape::CFOEFHyperLinkShape(const CFOEFHyperLinkShape& src)
{
	m_pBorderPen	= NULL;
	m_bNeedCreate		= TRUE;
	m_bShowLabelAtFirst = TRUE;
	SetAutoTextSize(	TRUE );
	SetShowLabelAtFirst(TRUE);
	m_bWithTextWrap		= TRUE;
	SetPolyObject(TRUE);
	*this		= src;
}

CFOEFHyperLinkShape::~CFOEFHyperLinkShape()
{

}

/////////////////////////////////////////////////////////////////////////////
// CFOEFHyperLinkShape diagnostics

#ifdef _DEBUG
void CFOEFHyperLinkShape::AssertValid() const
{
	CFOPEFormBaseShape::AssertValid();
}

void CFOEFHyperLinkShape::Dump(CDumpContext& dc) const
{
	CFOPEFormBaseShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

void CFOEFHyperLinkShape::Create(CRect &rcPos,CString strCaption)
{
	AllocMemory(4);

	m_lpShapePoints[0] = CPoint(rcPos.left,  rcPos.top);
	m_lpShapePoints[1] = CPoint(rcPos.right, rcPos.top);
	m_lpShapePoints[2] = CPoint(rcPos.right, rcPos.bottom);
	m_lpShapePoints[3] = CPoint(rcPos.left,  rcPos.bottom);
	CFODrawPortsShape::Create(rcPos,strCaption);
	
}

void CFOEFHyperLinkShape::Serialize(CArchive& ar)
{
	CFOPEFormBaseShape::Serialize(ar);
	if(ar.IsStoring())
	{
	}
	else
	{
		//FODO:Add your own code here.
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFOEFHyperLinkShape serialization
CFile* CFOEFHyperLinkShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CFOEFHyperLinkShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CFOEFHyperLinkShape::OpenDocument(LPCTSTR lpszPathName)
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

BOOL CFOEFHyperLinkShape::SaveDocument(LPCTSTR lpszPathName)
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

// Method define

CFOEFHyperLinkShape& CFOEFHyperLinkShape::operator=(const CFOEFHyperLinkShape& src)
{
	(*(CFOPEFormBaseShape*)this) = src;
	m_pBorderPen	= NULL;
	return (*this);
}

// Create copy ot shape
CFODrawShape* CFOEFHyperLinkShape::Copy() const
{
	return (new CFOEFHyperLinkShape(*this));
}

void CFOEFHyperLinkShape::PrepareDC(CDC* pDC)
{
	CFOPEFormBaseShape::PrepareDC(pDC);
	//FODO:Add your own code below.
	
}

void CFOEFHyperLinkShape::DoClickEvent(int nSel)
{
	nSel;

}

void CFOEFHyperLinkShape::OnDrawShadow(CDC *pDC)
{
	pDC;
	return;
}

void CFOEFHyperLinkShape::OnDraw(CDC *pDC)
{
	CFOPEFormBaseShape::OnDraw(pDC);
}

void CFOEFHyperLinkShape::OnDrawFlat(CDC *pDC)
{
	CFOPEFormBaseShape::OnDrawFlat(pDC);

	{
		if(GetShadow() && (GetShadowBrushType() == 0))
		{
			UINT nAlign = GetDrawFormatType();
			if (m_pEdit == NULL)
			{
				COLORREF crText;
				if(GetShadowBrushType() != 2)
				{
					crText = (COLORREF)GetShadowColor();
				}
				else 
				{
					crText = (COLORREF)GetShadowPatternColor();
				}
				
				CRect rcPos = GetSnapRect();
				rcPos.NormalizeRect();
				
				CPoint ptOffset = CPoint(GetShadowOffsetX(),GetShadowOffsetY());
				rcPos.OffsetRect(ptOffset);
				DoDrawText(pDC,GetObjectCaption(),rcPos,nAlign,crText,FALSE);
			}
		}
	}
}

void CFOEFHyperLinkShape::OnDraw3d(CDC *pDC)
{
	CFOPEFormBaseShape::OnDraw3d(pDC);

	{
		if(GetShadow() && (GetShadowBrushType() == 0))
		{
			UINT nAlign = GetDrawFormatType();
			if (m_pEdit == NULL)
			{
				COLORREF crText;
				if(GetShadowBrushType() != 2)
				{
					crText = (COLORREF)GetShadowColor();
				}
				else 
				{
					crText = (COLORREF)GetShadowPatternColor();
				}
				
				CRect rcPos = GetSnapRect();
				rcPos.NormalizeRect();
				
				CPoint ptOffset = CPoint(GetShadowOffsetX(),GetShadowOffsetY());
				rcPos.OffsetRect(ptOffset);
				DoDrawText(pDC,GetObjectCaption(),rcPos,nAlign,crText,FALSE);
			}
		}
	}
}


void CFOEFHyperLinkShape::ClearDC(CDC* pDC)
{
	CFOPEFormBaseShape::ClearDC(pDC);
	//FODO:Add your own code below.
}

void CFOEFHyperLinkShape::OnTextEditProperties()
{
	CFODrawShape::OnTextEditProperties();
	if(m_pMainView != NULL)
	{
		CClientDC dc((CWnd *)m_pMainView);
		AdjustTextBoxSize(&dc);
	}
}

void CFOEFHyperLinkShape::GeometryUpdated(CFOArea* pArea)
{
	if (m_lpShapePoints && pArea)
	{
		pArea->BuildPolygonArea(m_lpShapePoints, m_nCompPtCount);

		m_rectPosition = pArea->GetBoundingRect();
	}
}

void CFOEFHyperLinkShape::GetFontMetrics(CDC* pDC, int& dxWidth, int& dyHeight)
{
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	dyHeight = tm.tmHeight + tm.tmExternalLeading;
	dxWidth  = (tm.tmPitchAndFamily & 1 ? 3 : 2) * tm.tmAveCharWidth / 2;
}

void CFOEFHyperLinkShape::OnCancelMode()
{
}

void CFOEFHyperLinkShape::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CFOPEFormBaseShape::OnLButtonDblClk(nFlags,point);
}

void CFOEFHyperLinkShape::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFOPEFormBaseShape::OnLButtonDown(nFlags,point);
}

void CFOEFHyperLinkShape::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CFOPEFormBaseShape::OnRButtonDown(nFlags,point);
	
}
void CFOEFHyperLinkShape::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	nChar; 
	nRepCnt; 
	nFlags; 
	
}

void CFOEFHyperLinkShape::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CFOPEFormBaseShape::OnLButtonUp(nFlags,point);
}

void CFOEFHyperLinkShape::OnMouseMove(UINT nFlags, CPoint point) 
{
	nFlags;
	CRect rc = GetSnapRect();
	if(rc.PtInRect(point))
	{
		SetFontColor(::GetSysColor(COLOR_HIGHLIGHT));
		UpdateControl();
	}

	//CFOPEFormBaseShape::OnMouseMove(nFlags,point);
}

void CFOEFHyperLinkShape::OnMouseLeave(UINT nFlags, CPoint point)
{
	point;
	nFlags;
	SetFontColor(RGB(0, 0, 238));
	UpdateControl();
}

void CFOEFHyperLinkShape::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CFOPEFormBaseShape::OnRButtonDblClk(nFlags,point);
}


void CFOEFHyperLinkShape::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CFOPEFormBaseShape::OnRButtonUp(nFlags,point); 
}

void CFOEFHyperLinkShape::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	nRepCnt;
	nFlags;
	if (nChar == 32)
	{
		UpdateControl();
	}

}

BOOL CFOEFHyperLinkShape::OnAction(WPARAM, LPARAM)
{
	return FALSE;
}

void CFOEFHyperLinkShape::OnKillFocus(CWnd* pNewWnd) 
{
	pNewWnd;
	
}

void CFOEFHyperLinkShape::OnSetFocus(CWnd* pOldWnd) 
{
	pOldWnd;
	
}

BOOL CFOEFHyperLinkShape::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	return CFOPEFormBaseShape::OnSetCursor(pWnd,nHitTest,message);
}

void CFOEFHyperLinkShape::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	nRepCnt;
	nFlags;
	if (nChar == 32)
	{
		if(GetParentWnd() != NULL)
		{		
			CFOPCanvasCore *pView = static_cast<CFOPCanvasCore *>(GetParentWnd());
			pView->DoButtonClickEvent(this, (int)0);
		}
		UpdateControl();
	}
}

void CFOEFHyperLinkShape::CaptureMouse(BOOL bCapture)
{
	if(bCapture)
	{
		m_pParent->CanvasWnd()->SetCapture();
	}
	else
	{
		ReleaseCapture();
	}
}

void CFOEFHyperLinkShape::DrawEdit(CDC* pDC,CRect rcX)
{
	rcX;
	pDC;
}

BOOL CFOEFHyperLinkShape::DoStartEdit(CFOPCanvasCore* pView, CPoint ptCursorSP)
{
	ptCursorSP;
	ASSERT(pView != NULL);
	m_pParentView = pView;

	return FALSE;
}

void CFOEFHyperLinkShape::GetCurrentEditText(CString& strResult)
{
	strResult = GetCurrentText();
}

void CFOEFHyperLinkShape::SetCurrentEditText(const CString& str)
{
	SetCurrentText(str);
}

CString CFOEFHyperLinkShape::GetCurrentText()
{
	return m_strCurValue;
}

void CFOEFHyperLinkShape::SetCurrentText(const CString& str)
{
	m_strCurValue = str;

	if(GetParentWnd() != NULL)
	{		
		CFOPCanvasCore *pView = static_cast<CFOPCanvasCore *>(GetParentWnd());
		pView->DoEditTextChangeEvent(this, str);
	}
}

BOOL CFOEFHyperLinkShape::GetRotateSpotLocation(CPoint &ptHandle)
{
	return CFODrawPortsShape::GetRotateSpotLocation(ptHandle);
}
