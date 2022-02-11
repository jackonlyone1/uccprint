//////////////////////////////////////////////////////////////////////
/*****************************************************************/
// This file is a part of the E-XD++ MFC Extention Class.
// 2001-201? ucancode.net Software, All Rights Reserved.
// This is only define for UCanCode Software E-XD++ Library.
//
// UCanCode SOFTWARE GRANTS TO YOU (ONE SOFTWARE PROGRAMMER) THE
// LIMITED RIGHT TO USE THIS SOFTWARE ON A SINGLE COMPUTER.  
//  THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE 
// THE PROPERTY OF UCanCode SOFTWARE AND ARE NOT TO BE RE-DISTRIBUTED
// BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN CONSENT OF 
// UCanCode SOFTWARE.
//
// You can contact us.
// Support@ucancode.net
// http://www.ucancode.net
/********************************************************************/
// FOSplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "FOSplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFOSplashWnd

static CString strStore;

CFOSplashWnd::CFOSplashWnd(UINT nNewBitmapID, 
						   UINT nNewDuration /* = 2500 */)
{

	m_pPalette			= NULL;
	m_hParWnd			= NULL;
	m_bShowTitle		= FALSE;

	m_nBitmapID			= nNewBitmapID;
	m_nWait				= nNewDuration;
}

CFOSplashWnd::~CFOSplashWnd()
{
}

BOOL CFOSplashWnd::Create(CWnd* pParentWnd, 
						  DWORD dwStyle, 
						  DWORD dwExStyle)
{
	ASSERT(!(dwExStyle & WS_EX_TOOLWINDOW));
	dwExStyle &= ~WS_EX_TOOLWINDOW;

	if(pParentWnd)
		ASSERT_VALID(pParentWnd);

	ASSERT(!((dwStyle & WS_POPUP) && (dwStyle & WS_CHILD)));
	HWND hWndParent = NULL;

	if(pParentWnd)
	{
		hWndParent = pParentWnd->GetSafeHwnd();
	}
	else if(AfxGetMainWnd())
	{
		hWndParent = AfxGetMainWnd()->GetSafeHwnd();
	}
	else if(!m_bShowTitle)
	{
		strStore = "CFOSplashWndParent";
		m_hParWnd = ::CreateWindowEx(WS_EX_TOOLWINDOW, 
												 AfxRegisterWndClass(CS_CLASSDC), 
												 strStore, 
												 WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

		hWndParent = m_hParWnd;
		dwExStyle |= WS_EX_TOPMOST;
	}

	CBitmap bitmap;
	HANDLE hBitmap = ::LoadImage(AfxFindResourceHandle((LPCTSTR)(m_nBitmapID & 0xffff),RT_BITMAP),
		MAKEINTRESOURCE(m_nBitmapID), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION);

	ASSERT (hBitmap != NULL);
	bitmap.Attach(hBitmap);
	
	BITMAP bm;
	VERIFY(bitmap.GetBitmap(&bm));

	m_nImageHeight = bm.bmHeight;
	m_nImageWidth = bm.bmWidth;

    int nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    int nTop  = (nScreenHeight - m_nImageHeight) / 2;
    int nLeft = (nScreenWidth - m_nImageWidth) / 2;

	CString strWindowTitle;
	if(m_bShowTitle)
	{
		dwExStyle |= WS_EX_APPWINDOW;
		strWindowTitle = m_strTitle;
	}
	else
	{
		strStore = "CFOSplashWnd";
		strWindowTitle = strStore;
	}

	BOOL bRetVal = CWnd::CreateEx(dwExStyle, AfxRegisterWndClass(CS_CLASSDC), strWindowTitle,
		                          dwStyle, nLeft, nTop, m_nImageWidth, m_nImageHeight, hWndParent, NULL );
    ASSERT(bRetVal != FALSE);

	CDC* pDC = GetWindowDC();
	ASSERT(pDC);
	m_Image.MakeNewBitmap(pDC, &bitmap);
	if(pDC)
	{
		ReleaseDC(pDC);
	}

	SetPalette(m_Image.m_hPalette);

	SetTimer(m_nTimerID, 3000, NULL);

	if(dwStyle & WS_VISIBLE)
	{
		ShowWindow(SW_SHOW);
		UpdateWindow();
	}

    return bRetVal;
}

BEGIN_MESSAGE_MAP(CFOSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CFOSplashWnd)
	ON_WM_PAINT()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFOSplashWnd message handlers
void CFOSplashWnd::OnPaint() 
{
	CPaintDC dc(this);

	CPalette *pOldPalette = NULL;

	if (m_Image.m_hPalette)
	{
		pOldPalette = dc.SelectPalette(m_Image.m_hPalette, TRUE);
		dc.RealizePalette();
	} 

	m_Image.Stretch(&dc,
				0,
				0,
				m_nImageWidth,
				m_nImageHeight,
				0,0,
				m_nImageWidth,
				m_nImageHeight,
				SRCCOPY);

	if (m_Image.m_hPalette) 
	{
		dc.SelectPalette(pOldPalette, TRUE);
	}
}

BOOL CFOSplashWnd::PreTranslateMessage(MSG* pMsg) 
{
    ASSERT(pMsg != NULL);
    
    if ((pMsg->message == WM_KEYDOWN ||
		 pMsg->message == WM_SYSKEYDOWN ||
		 pMsg->message == WM_LBUTTONDOWN ||
		 pMsg->message == WM_RBUTTONDOWN ||
		 pMsg->message == WM_MBUTTONDOWN ||
		 pMsg->message == WM_NCLBUTTONDOWN ||
		 pMsg->message == WM_NCRBUTTONDOWN ||
		 pMsg->message == WM_NCMBUTTONDOWN))
	{
		PostMessage(WM_CLOSE);
		return 1;
    }    
    return CWnd::PreTranslateMessage(pMsg);
}

void CFOSplashWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if ((pFocusWnd == this ) || IsChild(pFocusWnd))
		return;
	
	OnQueryNewPalette();
}

BOOL CFOSplashWnd::OnQueryNewPalette() 
{
	if (m_pPalette == NULL)
		return FALSE;

	ASSERT(::IsWindow(m_hWnd));
	{
		CClientDC dc(this);
		CPalette* pOldPalette = dc.SelectPalette(m_pPalette,
			GetCurrentMessage()->message == WM_PALETTECHANGED);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;
	}
	
	Invalidate();
	
	return TRUE;
}

CPalette* CFOSplashWnd::SetPalette(CPalette* pPalette)
{
	CPalette* pOldPalette = m_pPalette;
	m_pPalette = pPalette;
	OnQueryNewPalette();
	return pOldPalette;
}

void CFOSplashWnd::OnTimer(UINT nIDEvent) 
{
    if (nIDEvent == m_nTimerID)
		PostMessage(WM_CLOSE);
}

void CFOSplashWnd::OnClose()
{
	KillTimer(m_nTimerID);

	if(m_hParWnd)
	{
		::PostMessage(m_hParWnd, WM_CLOSE, 0, 0);
	}

	CWnd::OnClose();
}

void CFOSplashWnd::PostNcDestroy() 
{
	delete this;
}
