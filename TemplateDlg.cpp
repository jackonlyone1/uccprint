// TemplateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "TemplateDlg.h"
#include "MBTemplageDlg.h"
#include "StartPageDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemplateDlg dialog


/////////////////////////////////////////////////////////////////////////////
// CTemplateDlg dialog

CTemplateDlg::CTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTemplateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTemplateDlg)
	//}}AFX_DATA_INIT
}


void CTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateDlg)
	DDX_Control(pDX, IDOK, m_ButtonCancel);
	DDX_Control(pDX, IDC_BUTTON_TEMPLATE, m_ButtonOther);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_ButtonOpen);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_ButtonNew);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTemplateDlg, CDialog)
	//{{AFX_MSG_MAP(CTemplateDlg)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_TEMPLATE, OnButtonTemplate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateDlg message handlers
#define TAB_ID 1232
#define TAB_PAGE1_ID 1233
#define TAB_PAGE2_ID 1234
#define TAB_PAGE3_ID 1235
#define TAB_PAGE4_ID 1236

BOOL CTemplateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ButtonNew.SetBitmap(IDB_BITMAP_NEW);
	m_ButtonNew.SetBtnCursor(IDC_FO_HAND);
	m_ButtonOpen.SetBitmap(IDB_BITMAP_OPEN);
	m_ButtonOpen.SetBtnCursor(IDC_FO_HAND);
	m_ButtonOther.SetBitmap(IDB_BITMAP_OTHER);
	m_ButtonOther.SetBtnCursor(IDC_FO_HAND);
	m_ButtonCancel.SetBtnCursor(IDC_FO_HAND);

	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strMainPath;
	strMainPath = strPathX+_T("\\Template\\");

	if(!theApp.DirectoryExists(strMainPath))
	{
		theApp.MakeDirectory(strMainPath);
	}
	// TODO: Add extra initialization here
	CRect theRect;
	GetDlgItem(IDC_TABPOS)->GetWindowRect( &theRect );
	ScreenToClient(&theRect);	
	
	// Create tab control at first.
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | FOP_TS_ALIGN_TOP | WS_TABSTOP;
	m_wndTab.Create(this, dwStyle);
	m_wndTab.SetWindowPos(&wndTop,theRect.left,theRect.top,theRect.Width(),theRect.Height(),SWP_SHOWWINDOW);

	// Empty rectangle.
	theRect.SetRectEmpty();

	CFOModelBoxItem *pItem = NULL;

	// Create first page.
	m_wndPage1.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_EX_CLIENTEDGE,theRect,&m_wndTab,TAB_PAGE1_ID);	
	m_wndTab.AddTab(&m_wndPage1,_T("Business Cards"));
	m_wndTab.SetTabPageIcon(0,IDI_FILE_ICON,CSize(32,32));
	pItem = m_wndPage1.AddNewItem();
	pItem->SetLinkFileName("BITMAP_350_200");
	pItem = m_wndPage1.AddNewItem();
	pItem->SetLinkFileName("BITMAP_8700_5080_MM");
	m_wndPage1.SetBkColor(RGB(231,231,231));
	m_wndPage1.m_pDlg = this;


	// Create the second page.
	m_wndPage2.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_EX_CLIENTEDGE,theRect,&m_wndTab,TAB_PAGE2_ID);	
	m_wndTab.AddTab(&m_wndPage2,_T("Labels"));
	m_wndTab.SetTabPageIcon(1,IDI_FILE_ICON,CSize(32,32));
	pItem = m_wndPage2.AddNewItem();
	pItem->SetLinkFileName("400_200_IN_LABEL");
	pItem = m_wndPage2.AddNewItem();
	pItem->SetLinkFileName("LABEL_100_34_MM");
	pItem = m_wndPage2.AddNewItem();
	pItem->SetLinkFileName("262_100_IN_LABEL");
	m_wndPage2.SetBkColor(RGB(192,192,255));
	m_wndPage2.m_pDlg = this;

	// Create the third page.
	m_wndPage3.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_EX_CLIENTEDGE,theRect,&m_wndTab,TAB_PAGE3_ID);
	m_wndTab.AddTab(&m_wndPage3,_T("CD/DVD"));
	m_wndTab.SetTabPageIcon(2,IDI_FILE_ICON,CSize(32,32));
	pItem = m_wndPage3.AddNewItem();
	pItem->SetLinkFileName("590_463_BACK_IN");
	pItem = m_wndPage3.AddNewItem();
	pItem->SetLinkFileName("CD_118_118_MM");
	m_wndPage3.SetBkColor(RGB(255,254,248));
	m_wndPage3.m_pDlg = this;

	m_wndTab.ActivateTab(0);

	m_wndTab.ActivateTab(0);
	m_wndTab.GetTabControl()->SetTabPageIconSize(16);
	m_wndTab.SetTabTotalHeightOrWidth(40);
//	m_wndTab.SetDrawFlatBorder(TRUE);
	m_wndTab.SetDrawMoneyMode(TRUE);
	m_wndTab.SetDrawMark(FALSE);
	m_wndTab.GetTabControl()->SetInflating(TRUE);
//	m_wndTab.GetTabControl()->SetActiveTabBkColor(RGB(192,192,255));
//	m_wndTab.GetTabControl()->SetInActiveTabBkColor(RGB(255,254,248));
	m_wndTab.UpdateWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTemplateDlg::OnDoNew()
{
	OnButtonNew();
}

void CTemplateDlg::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	theApp.nCurOpenMode = 100;
	
	CStartPageDlg dlg;
	dlg.DoModal();

	CConnectDlg *cnnDlg = &((CUCCPrintApp*)AfxGetApp())->m_connDlg;
	
	// TODO: Add your specialized creation code here
	cnnDlg->m_pOdbc = &theApp.m_odbc;
	if(IDCANCEL == cnnDlg->DoModal())
		return;
	
	CWaitCursor myWaitCursor;
	
	if(FOP_SUCCESS != theApp.m_odbc.Open(cnnDlg->m_strDSN, cnnDlg->m_strSQL, 0, cnnDlg->m_nOpenType, 0, NULL, NULL))
		return;
	
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	
	pParent->m_wndTableBar.DeleteAll();
	theApp.m_dbcols.RemoveAll();
	int nTotal = theApp.m_odbc.GetNumCols();
	int x= 0;
	for(x= 0; x < nTotal; x++)
	{
		CString strCol;
		theApp.m_odbc.GetColName(x, &strCol);
		theApp.m_dbcols.Add(strCol);
		pParent->m_wndTableBar.AddColumn(strCol, 3);
	}

	pParent->m_wndTableBar.AddColumn(_T("xdtTime"), 1);
	pParent->m_wndTableBar.AddColumn(_T("xdtDate"), 0);

	pParent->m_wndTableBar.m_wndTab.ActivateTab(1);
}

void CTemplateDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	theApp.nCurOpenMode = 101;
	CString fileOpenFilter =
		_T("UCCPrint Files (*.ucp)|*.ucp|All Files (*.*)|*.*||");
	CString defaultOpenFilter = _T("ucp");
	
	CFileDialog fileDialog(TRUE,
		defaultOpenFilter,
		NULL,
		OFN_FILEMUSTEXIST |
		OFN_HIDEREADONLY |
		OFN_SHAREAWARE |
		OFN_EXPLORER,
		fileOpenFilter);
	
	TCHAR moduleFileName[255];
	
	// Get the full path of the executable.
	::GetModuleFileName(NULL,
		moduleFileName,
		255);
	
	CString databaseDirectory = moduleFileName;
	
	for (int i = 0; i < 5; i++)	
	{
		int index = databaseDirectory.ReverseFind(_T('\\'));
		
		if (index != -1)
		{
			databaseDirectory = databaseDirectory.Left(index);
		}
	}
	
	fileDialog.m_ofn.lpstrInitialDir = databaseDirectory;
	
	if (fileDialog.DoModal() == IDOK)
	{
		theApp.OpenDocumentFile(fileDialog.GetPathName());
	}

	
}

void CTemplateDlg::OnButtonTemplate() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	theApp.nCurOpenMode = 102;
	CMBTemplageDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CString strPathX = AfxGetApp()->m_pszHelpFilePath;
		strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
		CString strMainPath;
		strMainPath = strPathX+_T("\\Template\\");
		
		theApp.bOpenTemplate = TRUE;
		theApp.strTemplateFile = dlg.m_strTempFile;
		theApp.strTemplateFolder = strMainPath;
		theApp.pCurDocTemplate->OpenDocumentFile(NULL);
	}
	
}

void CTemplateDlg::OnOK() 
{
	// TODO: Add extra validation here
	theApp.nCurOpenMode = 103;
	CDialog::OnOK();
}
