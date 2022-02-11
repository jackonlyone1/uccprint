#if !defined(AFX_CONNECTDLG_H__B20EBE9C_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
#define AFX_CONNECTDLG_H__B20EBE9C_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConnectDlg.h : header file
//

#include "FOPODBCDataSource.h"
#include "resource.h"
#include "DbPrintGridShape.h"

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog

 
//===========================================================================
// Summary:
//     The CConnectDlg class derived from CDialog
//      Connect Dialog
//===========================================================================

class CConnectDlg : public CDialog
{
// Construction
public:
 
	// m_pOdbc, This member maintains a pointer to the object CFOPODBCDataSource.  
	CFOPODBCDataSource	*m_pOdbc;		 // ODBC datasource

 
	// S Q L, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strSQL;
 
	// D S N, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strDSN;	// may be a DSN or a connectstring

 
	// Open Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int	 m_nOpenType;		// CRecordset::snapshot, dynaset

	
	//-----------------------------------------------------------------------
	// Summary:
	// Connect Dialog, Constructs a CConnectDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CConnectDlg(CWnd* pParent = NULL);   // standard constructor

 
	// S Q L Array, The member supports arrays of CString objects.  
	CStringArray	m_strSQLArray;
// Dialog Data
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_CONNECTDLG };
 
	// m_lstData, This member specify CListCtrl object.  
	CListCtrl	m_lstData;
 
	// m_colList, This member specify CComboBox object.  
	CComboBox	m_colList;
 
	// m_sqlList, This member specify CComboBox object.  
	CComboBox	m_sqlList;
 
	// m_sqlEdit, This member specify CEdit object.  
	CEdit	m_sqlEdit;
 
	// m_dsnCombo, This member specify CComboBox object.  
	CComboBox	m_dsnCombo;
	//}}AFX_DATA
 
	// Data Source, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sDataSource;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Data Sources, Call InitDataSources after creating a new object.

	void InitDataSources();

 
	// With Child Report, This member sets TRUE if it is right.  
	BOOL bWithSubReport;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Execute Sql, None Description.

	void ExecuteSql();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Reset Data List , Called this function to empty a previously initialized CConnectDlg object.

	void ResetDataListControl();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Combo, Call InitCombo after creating a new object.
	// Parameters:
	//		&strDNS---D N S, Specifies A CString type value.
	void InitCombo(const CString &strDNS);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDlg)
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
	//{{AFX_MSG(CConnectDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Radiodynaset, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnRadiodynaset();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Radiosnapshot, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnRadiosnapshot();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On O K, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnOK();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Select change Dsncombo, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSelchangeDsncombo();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Button1, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnButton1();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Select change Sqllist, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSelchangeSqllist();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Browsebutton, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnBrowsebutton();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Select change Combo Column, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSelchangeComboColumn();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Button Execute, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnButtonExecute();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDLG_H__B20EBE9C_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
