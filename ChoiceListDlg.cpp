// ChoiceListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "ChoiceListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoiceListDlg dialog


CChoiceListDlg::CChoiceListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoiceListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChoiceListDlg)
	m_strList = _T("");
	//}}AFX_DATA_INIT
	m_bModify = FALSE;
}


void CChoiceListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoiceListDlg)
	DDX_Text(pDX, IDC_EDIT_CHOICELIST, m_strList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoiceListDlg, CDialog)
	//{{AFX_MSG_MAP(CChoiceListDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoiceListDlg message handlers

BOOL CChoiceListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoiceListDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(m_strList != m_strOldList)
	{
		m_bModify = TRUE;
	}

	CDialog::OnOK();
}
