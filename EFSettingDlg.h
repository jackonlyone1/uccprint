#if !defined(AFX_EFSETTINGDLG_H__7B09B42C_DE63_4BBF_A32C_E0BA9E6D3A8D__INCLUDED_)
#define AFX_EFSETTINGDLG_H__7B09B42C_DE63_4BBF_A32C_E0BA9E6D3A8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EFSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEFSettingDlg dialog

 
//===========================================================================
// Summary:
//     The CEFSettingDlg class derived from CDialog
//      E F Setting Dialog
//===========================================================================

class CEFSettingDlg : public CDialog
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E F Setting Dialog, Constructs a CEFSettingDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CEFSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEFSettingDlg)
	enum { IDD = IDD_DIALOG_DB_NAME };
 
	// D B Name, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strDBName;
 
	// m_bHoriz, This member sets TRUE if it is right.  
	BOOL	m_bHoriz;
 
	// At Right, This member sets TRUE if it is right.  
	BOOL	m_bAtRight;
 
	// D B, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strDB;
 
	// Print Border, This member sets TRUE if it is right.  
	BOOL	m_bPrintBorder;
	//}}AFX_DATA
 
	// Object Name, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strObjName;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial List Box, Call InitListBox after creating a new object.

	void InitListBox();

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEFSettingDlg)
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Data Exchange, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDX---D X, A pointer to the CDataExchange or NULL if the call failed.
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEFSettingDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On O K, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnOK();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFSETTINGDLG_H__7B09B42C_DE63_4BBF_A32C_E0BA9E6D3A8D__INCLUDED_)
