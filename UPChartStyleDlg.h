#if !defined(AFX_UPCHARTSTYLEDLG_H__2DB319F0_0D72_42D2_A03B_47BFD2360E19__INCLUDED_)
#define AFX_UPCHARTSTYLEDLG_H__2DB319F0_0D72_42D2_A03B_47BFD2360E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UPChartStyleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUPChartStyleDlg dialog

class CUPChartStyleDlg : public CDialog
{
// Construction
public:
	CUPChartStyleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUPChartStyleDlg)
	enum { IDD = IDD_DIALOG_CHART };
	int		m_nStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUPChartStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUPChartStyleDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeListChart();
	afx_msg void OnDblclkListChart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPCHARTSTYLEDLG_H__2DB319F0_0D72_42D2_A03B_47BFD2360E19__INCLUDED_)
