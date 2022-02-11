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
#if !defined(AFX_FOSPLASHWND_H__9195BCA4_F1F0_436E_8E19_8B05D7BDBF6B__INCLUDED_)
#define AFX_FOSPLASHWND_H__9195BCA4_F1F0_436E_8E19_8B05D7BDBF6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FOSplashWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFOSplashWnd window

 
//===========================================================================
// Summary:
//     The CFOSplashWnd class derived from CWnd
//      F O Splash Window
//===========================================================================

class CFOSplashWnd : public CWnd
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O Splash Window, Constructs a CFOSplashWnd object.
	//		Returns A  value.  
	// Parameters:
	//		nNewBitmapID---New Bitmap I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nNewDuration---New Duration, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	CFOSplashWnd(UINT nNewBitmapID, 
			     UINT nNewDuration = 2500);


	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CFOSplashWnd object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pParentWnd---Parent Window, A pointer to the CWnd or NULL if the call failed.  
	//		dwStyle---dwStyle, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.  
	//		dwExStyle---Ex Style, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.
	virtual BOOL Create(CWnd* pParentWnd = NULL, 
						DWORD dwStyle = WS_POPUP|WS_VISIBLE, 
						DWORD dwExStyle = NULL);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Palette, Sets a specify value to current class CFOSplashWnd
	//		Returns a pointer to the object CPalette,or NULL if the call failed  
	// Parameters:
	//		pPalette---pPalette, A pointer to the CPalette or NULL if the call failed.
	CPalette* SetPalette(CPalette* pPalette);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFOSplashWnd)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Translate Message, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pMsg---pMsg, A pointer to the MSG or NULL if the call failed.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Post Nc Destroy, None Description.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C F O Splash Window, Destructor of class CFOSplashWnd
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CFOSplashWnd();

protected:

	// Generated message map functions
	//{{AFX_MSG(CFOSplashWnd)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Paint, Called to repaint a portion of the window.

	afx_msg void OnPaint();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Palette Changed, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pFocusWnd---Focus Window, A pointer to the CWnd or NULL if the call failed.
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Query New Palette, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns TRUE on success; FALSE otherwise.
	afx_msg BOOL OnQueryNewPalette();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Timer, Called after each interval specified in SetTimer.
	// Parameters:
	//		nIDEvent---I D Event, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg void OnTimer(UINT nIDEvent);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Close, Called as a signal that CWnd should be closed.

	afx_msg void OnClose();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
protected:
 
	// Image Height, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nImageHeight;
 
	// Image Width, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nImageWidth;
 
	// Bitmap I D, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT	m_nBitmapID;
 
	// Par Window, This member specify HWND object.  
	HWND	m_hParWnd;
 
	// Timer I D, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT	m_nTimerID;
 
	// m_strTitle, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strTitle;
 
	// m_Image, This member specify E-XD++ CFOBitmap object.  
	CFOBitmap	m_Image;
 
	// m_nWait, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT	m_nWait;
 
	// Show Title, This member sets TRUE if it is right.  
	BOOL	m_bShowTitle;
 
	// m_pPalette, This member maintains a pointer to the object CPalette.  
	CPalette*	m_pPalette;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOSPLASHWND_H__9195BCA4_F1F0_436E_8E19_8B05D7BDBF6B__INCLUDED_)
