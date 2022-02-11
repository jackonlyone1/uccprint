// CanvasOffsetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "CanvasOffsetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCanvasOffsetDlg dialog


CCanvasOffsetDlg::CCanvasOffsetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCanvasOffsetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCanvasOffsetDlg)
	m_xValue = 0.0;
	m_yValue = 0.0;
	//}}AFX_DATA_INIT
	m_pModel = NULL;
}


void CCanvasOffsetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCanvasOffsetDlg)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_yValue);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_xValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCanvasOffsetDlg, CDialog)
	//{{AFX_MSG_MAP(CCanvasOffsetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCanvasOffsetDlg message handlers

BOOL CCanvasOffsetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	m_pModel->TakeUnitStr(str);
	GetDlgItem(IDC_UNIT0)->SetWindowText(str);
	GetDlgItem(IDC_UNIT1)->SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCanvasOffsetDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}
