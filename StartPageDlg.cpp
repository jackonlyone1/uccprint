// StartPageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "StartPageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartPageDlg dialog


CStartPageDlg::CStartPageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartPageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartPageDlg)
	m_bLoad = FALSE;
	//}}AFX_DATA_INIT
}


void CStartPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartPageDlg)
	DDX_Check(pDX, IDC_CHECK_LOAD, m_bLoad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartPageDlg, CDialog)
	//{{AFX_MSG_MAP(CStartPageDlg)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_CHECK_LOAD, OnCheckLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartPageDlg message handlers

void CStartPageDlg::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
    CString strFilter;
	strFilter.LoadString(IDS_FO_IMAGE_EXTENSION);
	
	CString title;
	title.LoadString(IDS_FO_OPEN_FILE_TITLE);
	CFileDialog dlgFile (TRUE,NULL,NULL,OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,strFilter,this);
	if(dlgFile.DoModal() == IDOK)
	{
		theApp.strBackImageFile = dlgFile.GetPathName();
		GetDlgItem(IDC_EDIT_IMAGE)->SetWindowText(theApp.strBackImageFile);
	}
}

void CStartPageDlg::OnCheckLoad() 
{
	// TODO: Add your control notification handler code here
	m_bLoad = !m_bLoad;
	GetDlgItem(IDC_EDIT_IMAGE)->EnableWindow(m_bLoad);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(m_bLoad);
}

BOOL CStartPageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_IMAGE)->EnableWindow(m_bLoad);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(m_bLoad);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
