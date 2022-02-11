// MBEventEditDlg6.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "MBEventEditDlg.h"
#include "mainfrm.h"
#include "UCCPrintDoc.h"
#include "UCCPrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MBEventEditDlg2 dialog


MBEventEditDlg2::MBEventEditDlg2(CWnd* pParent /*=NULL*/)
: CDialog(MBEventEditDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(MBEventEditDlg2)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strPageName = "";
}


void MBEventEditDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MBEventEditDlg2)
	DDX_Control(pDX, IDC_MB_PAGE_LIST, m_ItemList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MBEventEditDlg2, CDialog)
//{{AFX_MSG_MAP(MBEventEditDlg2)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MBEventEditDlg2 message handlers
void MBEventEditDlg2::InitListBox()
{
	m_ItemList.ResetContent();
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	CUCCPrintDoc *pDoc = (CUCCPrintDoc *)pParent->GetActiveFrame()->GetActiveDocument();
	int nCount = pDoc->m_pModelManager->GetTabCount();
	for (int i = 0; i < nCount; i++)
	{
		CFOTabPageModel &pObj = pDoc->m_pModelManager->GetTab(i);
		CString strAdd;
		strAdd = pObj.m_strCaption;
		m_ItemList.AddString(strAdd);
	}
	
}

BOOL MBEventEditDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitListBox();
	m_ItemList.SelectString(-1,strPageName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void MBEventEditDlg2::OnOK() 
{
	// TODO: Add extra validation here
	int nCur = m_ItemList.GetCurSel();
	if(nCur >= 0)
	{
		m_ItemList.GetText(nCur,strPageName);
	}
	CDialog::OnOK();
}
