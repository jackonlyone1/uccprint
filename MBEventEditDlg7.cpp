// MBEventEditDlg7.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "MBEventEditDlg7.h"
#include "mainfrm.h"
#include "UCCPrintDoc.h"
#include "UCCPrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMBEventEditDlg7 dialog


CMBEventEditDlg7::CMBEventEditDlg7(CWnd* pParent /*=NULL*/)
: CDialog(CMBEventEditDlg7::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMBEventEditDlg7)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strObjName = "";
}


void CMBEventEditDlg7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMBEventEditDlg7)
	DDX_Control(pDX, IDC_MB_PAGE_LIST, m_ItemList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMBEventEditDlg7, CDialog)
//{{AFX_MSG_MAP(CMBEventEditDlg7)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMBEventEditDlg7 message handlers
void CMBEventEditDlg7::InitListBox()
{
	m_ItemList.ResetContent();
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	CUCCPrintView *pView = (CUCCPrintView *)pParent->GetActiveFrame()->GetActiveView();
	for(int x = 0; x < pView->GetTabModel()->GetShapes()->GetCount(); x++)
	{
		CFODrawShape *pObj = (CFODrawShape *)pView->GetTabModel()->GetShapes()->GetObject(x);
		CString title;
		title = pObj->GetObjectName();
		m_ItemList.AddString(title);
	}
}

BOOL CMBEventEditDlg7::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitListBox();
	m_ItemList.SelectString(-1,strObjName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMBEventEditDlg7::OnOK() 
{
	// TODO: Add extra validation here
	int nCur = m_ItemList.GetCurSel();
	if(nCur >= 0)
	{
		m_ItemList.GetText(nCur,strObjName);
	}
	CDialog::OnOK();
}

