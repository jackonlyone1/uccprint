#if !defined(AFX_MBTEMPLAGEDLG_H__DCFC4914_1A9B_11D6_A51E_525400EA266C__INCLUDED_)
#define AFX_MBTEMPLAGEDLG_H__DCFC4914_1A9B_11D6_A51E_525400EA266C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MBTemplageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMBTemplageDlg dialog

class CExtTemplateWnd;

/////////////////////////////////////////////////////////////////////////////
// CMBTemplageDlg dialog

namespace XD
{
	CString g_GetExePath();

	CString g_CreatePath(const CString &strPath);

	CString g_GetDBPath(const CString &strFileName);
	CString g_GetXMLPath(const CString &strFileName);
	CString g_GetBitmapPath(const CString &strFileName);
	CString g_GetShapePath(const CString &strFileName);
	CString g_GetTemplatePath(const CString &strFolder, const CString &strTemplate);
	CString g_GetTemplateFolder();
	CString g_GetSampleFolder();
	CString g_GetComponentsFolder();
	CString g_GetComponentsPath(const CString &strFileName);
	CString g_GetHelpFile();

}// XD

class CMBTemplageDlg;
 
//===========================================================================
// Summary:
//     The CExtTemplateWnd class derived from CFOTemplateWnd
//      Extend Template Window
//===========================================================================

class CExtTemplateWnd : public CFOTemplateWnd
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Template Window, Constructs a CExtTemplateWnd object.
	//		Returns A  value.
	CExtTemplateWnd();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Extend Template Window, Destructor of class CExtTemplateWnd
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CExtTemplateWnd();

// Attributes
public:
	// Do something when click on the item.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Click On Item, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pPage---pPage, A pointer to the CFOModelBoxItem or NULL if the call failed.
	virtual void DoClickOnItem(CFOModelBoxItem* pPage);

	// Set Parent
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Parent Dialog, Sets a specify value to current class CExtTemplateWnd
	// Parameters:
	//		*pDlg---*pDlg, A pointer to the CMBTemplageDlg  or NULL if the call failed.
	void SetParentDlg(CMBTemplageDlg *pDlg);

// Operations
private:
 
	// m_pDlg, This member maintains a pointer to the object CMBTemplageDlg.  
	CMBTemplageDlg *m_pDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtTemplateWnd)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Translate Message, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pMsg---pMsg, A pointer to the MSG or NULL if the call failed.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtTemplateWnd)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Double click Clk, Called when the user double-clicks the left mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

 
//===========================================================================
// Summary:
//     The CMBTemplageDlg class derived from CDialog
//      M B Templage Dialog
//===========================================================================

class CMBTemplageDlg : public CDialog
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// M B Templage Dialog, Constructs a CMBTemplageDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CMBTemplageDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CMBTemplageDlg)
	enum { IDD = IDD_SV_TEMLATE_DLG };
 
	// Button Cancel, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonCancel;
 
	// Button Other, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonOther;
 
	// Button Open, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonOpen;
	//}}AFX_DATA
 
	// m_wndTab, This member specify E-XD++ CFOTabCtrl object.  
	CFOTabCtrl m_wndTab;
 
	// Window Page, This member specify CPtrArray object.  
	CPtrArray m_arrWndPage;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Information To Tab, Adds an object to the specify list.

	void AddInfoToTab();

 
	// Temp File, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strTempFile;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Templace, None Description.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL OpenTemplace();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMBTemplageDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Destroy Window, Call this function to destroy an existing object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL DestroyWindow();
	
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
	// Do Data Exchange, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDX---D X, A pointer to the CDataExchange or NULL if the call failed.
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	
	//Has it intialize
 
	// Has Initial, This member sets TRUE if it is right.  
	BOOL m_bHasInit;
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CMBTemplageDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Open Document, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOpenDocument();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Sv Temp Download, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSvTempDownload();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Size, Called after the size of CWnd has changed.
	// Parameters:
	//		UINT---I N T, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		cx---Specifies A integer value.  
	//		cy---Specifies A integer value.
	afx_msg void OnSize(UINT /*nType*/, int cx, int cy);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Sizing, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		nSide---nSide, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		lpRect---lpRect, Specifies a LPRECT lpRect object.
	afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBTEMPLAGEDLG_H__DCFC4914_1A9B_11D6_A51E_525400EA266C__INCLUDED_)
