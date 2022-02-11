#if !defined(AFX_OPTIONDLG_H__E74960C5_3722_41F4_9687_57AD0694765A__INCLUDED_)
#define AFX_OPTIONDLG_H__E74960C5_3722_41F4_9687_57AD0694765A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog

 
//===========================================================================
// Summary:
//     The COptionDlg class derived from CDialog
//      Option Dialog
//===========================================================================

class COptionDlg : public CDialog
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Option Dialog, Constructs a COptionDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	COptionDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_DIALOG_SETTING };
 
	// Connect Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nConnectType;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionDlg)
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
	//{{AFX_MSG(COptionDlg)
	// Generated message map functions
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONDLG_H__E74960C5_3722_41F4_9687_57AD0694765A__INCLUDED_)
