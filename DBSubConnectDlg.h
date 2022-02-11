#if !defined(AFX_DBSUBCONNECTDLG_H__F61EE20F_E39E_49E7_B243_EFBF73FF932C__INCLUDED_)
#define AFX_DBSUBCONNECTDLG_H__F61EE20F_E39E_49E7_B243_EFBF73FF932C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBSubConnectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBSubConnectDlg dialog

#include "FOPODBCDataSource.h"
#include "resource.h"
#include "DbPrintGridShape.h"

/////////////////////////////////////////////////////////////////////////////
// CDBSubConnectDlg dialog

 
//===========================================================================
// Summary:
//     The CDBSubConnectDlg class derived from CDialog
//      D B Child Connect Dialog
//===========================================================================

class CDBSubConnectDlg : public CDialog
{
	// Construction
public:
 
	// m_pOdbc, This member maintains a pointer to the object CFOPODBCDataSource.  
	CFOPODBCDataSource	*m_pOdbc;		 // ODBC datasource
	
 
	// S Q L, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strSQL;
	
 
	// Open Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int	 m_nOpenType;		// CRecordset::snapshot, dynaset
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// D B Child Connect Dialog, Constructs a CDBSubConnectDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CDBSubConnectDlg(CWnd* pParent = NULL);   // standard constructor
	
 
	// S Q L Array, The member supports arrays of CString objects.  
	CStringArray	m_strSQLArray;
	// Dialog Data
	//{{AFX_DATA(CDBSubConnectDlg)
	enum { IDD = IDD_SUB_CONNECT };
 
	// m_lstData, This member specify CListCtrl object.  
	CListCtrl	m_lstData;
 
	// m_colList, This member specify CComboBox object.  
	CComboBox	m_colList;
 
	// m_sqlList, This member specify CComboBox object.  
	CComboBox	m_sqlList;
 
	// m_sqlEdit, This member specify CEdit object.  
	CEdit	m_sqlEdit;
	//}}AFX_DATA
 
	// Data Source, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sDataSource;
	
 
	CString strSub;

	// With Child Report, This member sets TRUE if it is right.  
	BOOL bWithSubReport;
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Combo, Call InitCombo after creating a new object.
	// Parameters:
	//		&strDNS---D N S, Specifies A CString type value.
	void InitCombo(const CString &strDNS);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Execute Sql, None Description.

	void ExecuteSql();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Reset Data List , Called this function to empty a previously initialized CDBSubConnectDlg object.

	void ResetDataListControl();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBSubConnectDlg)
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
	//{{AFX_MSG(CDBSubConnectDlg)
	
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
	// On Select change Sqllist, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSelchangeSqllist();
	
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
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBSUBCONNECTDLG_H__F61EE20F_E39E_49E7_B243_EFBF73FF932C__INCLUDED_)
