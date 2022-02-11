// FOPNewAutoFontSizeShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FOPNewAutoFontSizeShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CFOPNewAutoFontSizeShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CFOPNewAutoFontSizeShape, CFORectShape, 0)
CFOPNewAutoFontSizeShape::CFOPNewAutoFontSizeShape()
{
	SetType(MY_AUTO_SIZE_TYPE);
	SetPolyObject(FALSE);
	SetRotateProtect(FALSE);
}

CFOPNewAutoFontSizeShape::CFOPNewAutoFontSizeShape(const CFOPNewAutoFontSizeShape& src)
{
	*this = src;
}

CFOPNewAutoFontSizeShape::~CFOPNewAutoFontSizeShape()
{

}

/////////////////////////////////////////////////////////////////////////////
// CFOPNewAutoFontSizeShape diagnostics

#ifdef _DEBUG
void CFOPNewAutoFontSizeShape::AssertValid() const
{
	CFORectShape::AssertValid();
}

void CFOPNewAutoFontSizeShape::Dump(CDumpContext& dc) const
{
	CFORectShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CFOPNewAutoFontSizeShape::Create(CRect &rcPos,CString strCaption)
{
	CFORectShape::Create(rcPos,strCaption);

	// FODO: Add your own code here.

}

void CFOPNewAutoFontSizeShape::Serialize(CArchive& ar)
{
	CFORectShape::Serialize(ar);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.

	}
	else
	{
		//FODO:Add your own code here.

	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CFOPNewAutoFontSizeShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CFOPNewAutoFontSizeShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CFOPNewAutoFontSizeShape::OpenDocument(LPCTSTR lpszPathName)
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

BOOL CFOPNewAutoFontSizeShape::SaveDocument(LPCTSTR lpszPathName)
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

CFOPNewAutoFontSizeShape& CFOPNewAutoFontSizeShape::operator=(const CFOPNewAutoFontSizeShape& src)
{
	(*(CFORectShape*)this) = src;
	return (*this);
}

CFODrawShape* CFOPNewAutoFontSizeShape::Copy() const
{
	return (new CFOPNewAutoFontSizeShape(*this));
}

void CFOPNewAutoFontSizeShape::PrepareDC(CDC* pDC)
{
	CFORectShape::PrepareDC(pDC);

	//FODO:Add your own code below.
	
}

void CFOPNewAutoFontSizeShape::OnDrawTrackCustom(CDC *pDC)
{
	CFORectShape::OnDrawTrackCustom(pDC);

	// Add your own code here.

}

void CFOPNewAutoFontSizeShape::OnDrawShadow(CDC *pDC)
{
	CFORectShape::OnDrawShadow(pDC);
	
	//FODO:Add your own code below.
	
}

void CFOPNewAutoFontSizeShape::OnDrawFlat(CDC *pDC)
{
	CFODrawShape::OnDrawFlat(pDC);

	//FODO:Add your own code below.
	
}

void CFOPNewAutoFontSizeShape::OnDraw3d(CDC *pDC)
{
	CFODrawShape::OnDraw3d(pDC);

	//FODO:Add your own code below.
	FillPoly(pDC,m_lpShapePoints, m_nCompPtCount,GetBkColor(),
		GetPatternColor(),GetBrushType());

	CString strCaption = GetObjectCaption();
	CRect rect = GetSnapRect();
	HFONT oldFont = NULL;
	
	//create the font needed
//	if(cell->IsPropertySet(UGCELL_FONT_SET))
//		oldFont = (HFONT) ::SelectObject(dc->m_hDC, (HFONT)(cell->GetFont()->m_hObject));
	
	HFONT newFont = NULL;
	
//	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
//	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif
	
//	if(cell->IsPropertySet(UGCELL_TEXT_SET))
	{
		int oldLeft = rect.left;
//		rect->left += (int) (m_ctrl->m_GI->m_margin * fScale);
		newFont = CreateAutoSizeFont(pDC->m_hDC,rect,strCaption);
		if (NULL != oldFont)
			oldFont = (HFONT) ::SelectObject(pDC->m_hDC, newFont);
		else
			pDC->SelectObject(newFont);
		//cell->ClearPropertySetFlag(UGCELL_FONT_SET);
		rect.left = oldLeft;
	}
	
	//draw the text in using the default drawing routine
	DrawText(pDC, strCaption, rect, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
//	pDC->DrawText(string,-1,tempRect,format );(dc,rect,0,col,row,cell,selected,current);
	
	if( NULL != oldFont ) SelectObject(pDC->m_hDC, oldFont);
	if( NULL != newFont ) DeleteObject(newFont);
	
}

void CFOPNewAutoFontSizeShape::ClearDC(CDC* pDC)
{
	CFORectShape::ClearDC(pDC);

	//FODO:Add your own code below.

}

void CFOPNewAutoFontSizeShape::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFORectShape::OnLButtonDown(nFlags,point);
	
	//FODO:Add your own code below.

}

void CFOPNewAutoFontSizeShape::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CFORectShape::OnLButtonUp(nFlags,point);

	//FODO:Add your own code below.

}

void CFOPNewAutoFontSizeShape::GeometryUpdated(CFOArea* pRgn)
{
	CFORectShape::GeometryUpdated(pRgn);

	//FODO:Add your own code below.

}

HFONT CFOPNewAutoFontSizeShape::CreateAutoSizeFont(HDC hdc, RECT *rect,LPCTSTR string)
{
	CString strFace = GetFaceName();
	HFONT	font;
	int		Height = 1;
	int		Width = rect->right - rect->left;

	CString str(string);
//	int nLen = str.GetLength();
	int nW = 0;//(int)((rect->right - rect->left) / (float)nLen);
	
	SIZE	size;
	float   ratio;
	TEXTMETRIC tm;
	TCHAR	fontFace[60];
	int		rt;
	int saveID = SaveDC(hdc);
	
	GetTextFace(hdc,60,fontFace);
	GetTextMetrics(hdc,&tm);
	
	Height = Width/(int)_tcslen(string);
	if(Height < 1)
		Height = 1;
	Height = Height + Height/2;
	
	font =  ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
	SelectObject(hdc,font);
	
	GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);
	ratio = (float)size.cy/(float)size.cx;
	Height = (int)((float)Width*ratio);
	rt = RestoreDC(hdc,saveID);
	rt = DeleteObject(font);
	font = ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
	SelectObject(hdc,font);
	GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);
	
	if (Width >size.cx)
	{
		while (Width > size.cx && Height < 500)
		{
			rt = RestoreDC(hdc,saveID);
			rt = DeleteObject(font);
			Height++;
			font = ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
			SelectObject(hdc,font);
			GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);
			
		}
		rt = RestoreDC(hdc,saveID);
		rt = DeleteObject(font);
		Height--;
		if(Height > 0)
			font = ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
		
	}
	else if (Width < size.cx)
	{
		while (Width < size.cx  && Height > 1)
		{
			rt = RestoreDC(hdc,saveID);
			rt = DeleteObject(font);
			Height--;
			font = ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
			SelectObject(hdc,font);
			GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);
			if(Height<1)
				break;
		}
		
		rt = RestoreDC(hdc,saveID);
		rt = DeleteObject(font);
		Height--;
		if(Height < 1)
			Height = 1;
		font = ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
	}
	if (Height >(rect->bottom - rect->top))
	{
		Height = rect->bottom - rect->top;
		if(Height <2)
			Height = 2;
		rt = RestoreDC(hdc,saveID);
		rt = DeleteObject(font);
		font = ::CreateFont(Height, nW, 0, 0, 600, 0,0,0,0,0,0,0,0,strFace);
	}
	
	rt = RestoreDC(hdc,saveID);
	
	return font;
}
