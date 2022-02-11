// DBSubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "DBSubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBSubDlg dialog


CDBSubDlg::CDBSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBSubDlg)
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	m_strField = _T("");
}


void CDBSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBSubDlg)
	DDX_Text(pDX, IDC_EDIT_INDEX, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBSubDlg, CDialog)
	//{{AFX_MSG_MAP(CDBSubDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBSubDlg message handlers

BOOL CDBSubDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO_DB);
	// TODO: Add extra initialization here
	int nSize = m_DBFileds->GetSize();
	for(int x = 0; x < nSize; x++)
	{
		pBox->AddString(m_DBFileds->GetAt(x));
	}
	if(!m_strField.IsEmpty())
		pBox->SelectString(-1, m_strField);
	else
	{
		if(nSize > 0)
			pBox->SetCurSel(0);
	}

	GetDlgItem(IDC_EDIT_INDEX)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBSubDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(m_strTitle.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_INDEX)->SetFocus();
		return;
	}

	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO_DB);
	int nCur = pBox->GetCurSel();
	if(nCur != CB_ERR)
	{
		pBox->GetLBText(nCur, m_strField);
	}
	else
	{
		pBox->SetFocus();
		return;
	}

	
	CDialog::OnOK();
}
