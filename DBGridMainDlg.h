#if !defined(AFX_DBGRIDMAINDLG_H__19E13287_E7C5_4743_82D1_568914FE689C__INCLUDED_)
#define AFX_DBGRIDMAINDLG_H__19E13287_E7C5_4743_82D1_568914FE689C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBGridMainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBGridMainDlg dialog
#include "DbPrintGridShape.h"

 
//===========================================================================
// Summary:
//     The CDBGridMainDlg class derived from CDialog
//      D B Grid Main Dialog
//===========================================================================

class CDBGridMainDlg : public CDialog
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// D B Grid Main Dialog, Constructs a CDBGridMainDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CDBGridMainDlg(CWnd* pParent = NULL);   // standard constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// C D B Grid Main Dialog, Destructor of class CDBGridMainDlg
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CDBGridMainDlg();
	// Dialog Data
	//{{AFX_DATA(CDBGridMainDlg)
	enum { IDD = IDD_HMI_MENU_MAIN };
 
	// List Workspaces, This member specify CListCtrl object.  
	CListCtrl	m_ctrlListWorkspaces;
 
	// Button Up, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonUp;
 
	// Button Down, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonDown;
 
	// Button Remove, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonRemove;
 
	// Button Remove All, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonRemoveAll;
 
	// Button Project, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_ButtonProject;
 
	// Grid Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nGridType;
 
	// Horizontal Grid, This member sets TRUE if it is right.  
	BOOL	m_bHorzGrid;
 
	// Vertical Grid, This member sets TRUE if it is right.  
	BOOL	m_bVertGrid;
 
	// m_nStart, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nStart;
 
	// m_nTotal, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nTotal;
	//}}AFX_DATA
 
	// Image List, This member is a collection of same-sized images.  
	CImageList		m_ImageList;
	
 
	// strSql, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strSql;
	CString strSubLink;
	CArray<FODB_COLS,FODB_COLS> *arStates;	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Project, Adds an object to the specify list.
	// Parameters:
	//		nState---nState, Specifies A CString type value.  
	//		strState---strState, Specifies A CString type value.
	void AddProject		( const CString&	nState, const CString&	strState);	
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load Profile, Call this function to read a specified number of bytes from the archive.

	void LoadProfile();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Move Item, None Description.
	// Parameters:
	//		a_iSrc---a_iSrc, Specifies A integer value.  
	//		a_iDst---a_iDst, Specifies A integer value.
	void MoveItem		(int a_iSrc, int	a_iDst);
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get All Index, Returns the specified value.
	// Parameters:
	//		&m_Array---&m_Array, Specifies A CString type value.
	void GetAllIndex(CStringArray &m_Array);
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Generate State Text, None Description.
	//		Returns a CString type value.
	CString GenerateStateText();
 
	// D B Fileds, The member supports arrays of CString objects.  
	CStringArray m_DBFileds;
	
 
	// m_wndColor, This member specify FOPDropDownColorPickerButton object.  
	FOPDropDownColorPickerButton	m_wndColor;
	// Pattern color.
 
	// m_crValue, This member sets A 32-bit value used as a color value.  
	COLORREF m_crValue;

 
	// m_wndGrid, This member specify FOPDropDownColorPickerButton object.  
	FOPDropDownColorPickerButton	m_wndGrid;
	// Pattern color.
 
	// m_crGrid, This member sets A 32-bit value used as a color value.  
	COLORREF m_crGrid;

 
	// Tool Box, This member sets TRUE if it is right.  
	BOOL bToolBox;
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBGridMainDlg)
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
	//{{AFX_MSG(CDBGridMainDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Add Project, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAddProject();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Remove Project, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnRemoveProject();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Move Up, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMoveUp();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Move Down, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMoveDown();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Get Minimize Maximize Information, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		lpMMI---M M I, A pointer to the MINMAXINFO FAR or NULL if the call failed.
	afx_msg void OnGetMinMaxInfo		(MINMAXINFO FAR* lpMMI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Double click Workspacelist, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnDblclkWorkspacelist(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On O K, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnOK();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Button Removeall, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnButtonRemoveall();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Button Db, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnButtonDb();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGRIDMAINDLG_H__19E13287_E7C5_4743_82D1_568914FE689C__INCLUDED_)
