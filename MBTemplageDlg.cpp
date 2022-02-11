// MBTemplageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "MBTemplageDlg.h"
#include <afxpriv.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString XD::g_GetExePath()
{
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	return strPathX;
}

CString XD::g_CreatePath(const CString &strPath)
{
	CString strTemp = g_GetExePath() + _T("\\");
	strTemp += strPath;
	_tmkdir(strTemp.GetBuffer(strTemp.GetLength()));
	strTemp.ReleaseBuffer();

	return strTemp + _T("\\");
}

CString XD::g_GetXMLPath(const CString &strFileName)
{
	return g_GetExePath() + _T("\\") + strFileName;
}

CString XD::g_GetDBPath(const CString &strFileName)
{
	return g_CreatePath(_T("Databases")) + strFileName;
}

CString XD::g_GetBitmapPath(const CString &strFileName)
{
	return g_CreatePath(_T("TemplateTab")) + strFileName + _T(".bmp");
}

CString XD::g_GetShapePath(const CString &strFileName)
{
	return g_CreatePath(_T("Shapes")) + strFileName;
}

CString XD::g_GetTemplatePath(const CString &strFolder, const CString &strTemplate)
{
	return g_CreatePath(_T("Template")) + strFolder + _T("\\") + strTemplate + _T(".utp");
}

CString XD::g_GetComponentsPath(const CString &strFileName)
{
	return g_CreatePath(_T("Components")) + strFileName + _T(".sid");
}

CString XD::g_GetTemplateFolder()
{
	return g_CreatePath(_T("Template"));
}

CString XD::g_GetSampleFolder()
{
	return g_CreatePath(_T("Samples"));
}

CString XD::g_GetComponentsFolder()
{
	return g_CreatePath(_T("Components"));
}

CString XD::g_GetHelpFile()
{
	return g_GetExePath() + _T("\\Documentation\\help.chm");
}


/////////////////////////////////////////////////////////////////////////////
// CExtTemplateWnd

CExtTemplateWnd::CExtTemplateWnd()
{
	EnableEditProp(FALSE);
}

CExtTemplateWnd::~CExtTemplateWnd()
{
}

BEGIN_MESSAGE_MAP(CExtTemplateWnd, CFOTemplateWnd)
	//{{AFX_MSG_MAP(CExtTemplateWnd)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
	
void CExtTemplateWnd::SetParentDlg(CMBTemplageDlg *pDlg)
{
	ASSERT(pDlg);
	m_pDlg = pDlg;
}

BOOL CExtTemplateWnd::PreTranslateMessage(MSG* pMsg)
{
	// If the field is a multi-line edit, don't worry about it
	
	if (pMsg->wParam == VK_RETURN)
	{
		return m_pDlg->OpenTemplace();
	}
	
	return CFOTemplateWnd::PreTranslateMessage(pMsg);
}

void CExtTemplateWnd::DoClickOnItem(CFOModelBoxItem* pPage)
{
	m_pDlg->m_strTempFile = pPage->GetLinkFileName();
}

/////////////////////////////////////////////////////////////////////////////
// CExtTemplateWnd message handlers

void CExtTemplateWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CFOTemplateWnd::OnLButtonDblClk(nFlags, point);

	CFOModelBoxItem *pHit = HitTest(point);
	if( pHit == NULL ) return;
	
	m_pDlg->m_strTempFile = pHit->GetLinkFileName();
	m_pDlg->OpenTemplace();
}

/////////////////////////////////////////////////////////////////////////////
// CMBTemplageDlg dialog

/////////////////////////////////////////////////////////////////////////////
// CMBTemplageDlg dialog
#define XD_TEMPLATE_DLG_PAGE_ID 1233
CMBTemplageDlg::CMBTemplageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMBTemplageDlg::IDD, pParent), m_strTempFile(_T(""))
{
	//{{AFX_DATA_INIT(CMBTemplageDlg)
	//}}AFX_DATA_INIT
	m_bHasInit = FALSE;
}


void CMBTemplageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMBTemplageDlg)
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BUTTON_TEMPLATE, m_ButtonOther);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_ButtonOpen);
	//}}AFX_DATA_MAP
}

 
BEGIN_MESSAGE_MAP(CMBTemplageDlg, CDialog)
	//{{AFX_MSG_MAP(CMBTemplageDlg)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnOpenDocument)
	ON_BN_CLICKED(IDC_BUTTON_TEMPLATE, OnSvTempDownload)
	ON_WM_SIZE()
	ON_WM_SIZING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMBTemplageDlg message handlers
#define TAB_ID 1232
#define TAB_PAGE1_ID 1233
#define TAB_PAGE2_ID 1234
#define TAB_PAGE3_ID 1235
#define TAB_PAGE4_ID 1236

BOOL CMBTemplageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ButtonOpen.SetBitmap(IDB_BITMAP_OPEN);
	m_ButtonOpen.SetBtnCursor(IDC_FO_HAND);
	m_ButtonOther.SetBitmap(IDB_BITMAP_OTHER);
	m_ButtonOther.SetBtnCursor(IDC_FO_HAND);
	m_ButtonCancel.SetBtnCursor(IDC_FO_HAND);

	// TODO: Add extra initialization here
	CRect theRect;
	GetDlgItem(IDC_XD_TP_DLG_TABPOS)->GetWindowRect( &theRect );
	ScreenToClient(&theRect);	
	
	// Create tab control at first.
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | FOP_TS_ALIGN_LEFT | WS_TABSTOP;
	m_wndTab.Create(this, dwStyle);
	m_wndTab.SetWindowPos(&wndTop,theRect.left,theRect.top,theRect.Width(),theRect.Height(),SWP_SHOWWINDOW);

	// Empty rectangle.
	theRect.SetRectEmpty();

	AddInfoToTab();

	m_wndTab.ActivateTab(0);
	m_wndTab.GetTabControl()->SetTabPageIconSize(16);
	m_wndTab.SetTabTotalHeightOrWidth(100);
//	m_wndTab.SetDrawFlatBorder(TRUE);
	m_wndTab.SetDrawMoneyMode(TRUE);
	m_wndTab.GetTabControl()->SetActiveTabBkColor(RGB(192,192,255));
	m_wndTab.GetTabControl()->SetInActiveTabBkColor(RGB(255,192,0));
	m_wndTab.UpdateWindow();

	m_bHasInit = TRUE;
	
	UpdateData(FALSE);
	
	CRect rc;
	GetClientRect(rc);
	OnSize(0, rc.Width(), rc.Height());
	Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMBTemplageDlg::AddInfoToTab()
{
	CFileFind ff;
	BOOL res = ff.FindFile(XD::g_GetTemplateFolder() + _T("\\*.*"));

	int nCount = 0;
	int i = -1;
	while(res)
	{
		res = ff.FindNextFile();
 		if(!(ff.IsDirectory() && !ff.IsDots())) 
			continue;
		
		CExtTemplateWnd *pPage = new CExtTemplateWnd;

		m_arrWndPage.Add(pPage);
		nCount ++;

		// Create page.
		i++;
		pPage->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_EX_CLIENTEDGE, CRect(0, 0, 0, 0), &m_wndTab, XD_TEMPLATE_DLG_PAGE_ID+i);
		pPage->SetParentDlg(this);
		
 		m_wndTab.AddTab(pPage, ff.GetFileTitle());
		m_wndTab.SetTabPageIcon(i, IDR_UCCPRITYPE, CSize(32,32));
		
 		CFileFind fItem;
		BOOL resItem = fItem.FindFile(ff.GetFilePath() + _T("\\*.utp"));
		while (resItem)
		{// AddItem
			resItem = fItem.FindNextFile();
 			if (!fItem.IsDirectory() && !fItem.IsDots())
			{
 				CString strPath = fItem.GetFilePath();
				CString strTitle = fItem.GetFileTitle();
				
				CFOModelBoxItem *pItem = pPage->AddNewItem();
				pItem->SetCaption(strTitle);
				pItem->SetLinkFileName(strPath);
			}
		}
	}
	
 	if (nCount == 0)
	{
		CExtTemplateWnd *pPage = new CExtTemplateWnd;	
		m_arrWndPage.Add(pPage);
		i++;
		pPage->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_EX_CLIENTEDGE, CRect(0, 0, 0, 0), &m_wndTab, XD_TEMPLATE_DLG_PAGE_ID+i);
		pPage->SetParentDlg(this);
		
 		m_wndTab.AddTab(pPage, _T("Empty"));
		m_wndTab.SetTabPageIcon(i, IDR_UCCPRITYPE, CSize(32,32));
	}
}

BOOL CMBTemplageDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	for (;m_arrWndPage.GetSize();)
	{
		delete (CExtTemplateWnd*)m_arrWndPage.GetAt(0);
		m_arrWndPage.RemoveAt(0);
	}
	m_arrWndPage.RemoveAll();
	
	//	m_pBrSolid->DeleteObject();
	//	_SafeDeletePtr(m_pBrSolid);
	
	return CDialog::DestroyWindow();
}

BOOL FOPFileExist3(CString strFilePath)
{
	CFileStatus fs;
	return CFile::GetStatus(strFilePath, fs);
}

BOOL CMBTemplageDlg::OpenTemplace()
{
	if(!m_strTempFile.IsEmpty() && FOPFileExist3(m_strTempFile))
	{
		CDialog::OnOK();
		return TRUE;
	}
	else
	{
		m_wndTab.SetFocus();
		return FALSE;
	}
}

void CMBTemplageDlg::OnOpenDocument() 
{
	// TODO: Add your control notification handler code here
	if(OpenTemplace())
	{
		
	}
}	

BOOL CMBTemplageDlg::PreTranslateMessage(MSG* pMsg)
{
	// If the field is a multi-line edit, don't worry about it
	
	if (pMsg->wParam == VK_RETURN)
	{
		if(!m_strTempFile.IsEmpty() && FOPFileExist3(m_strTempFile))
		{
			CDialog::OnOK();
		}
		else
		{
			return FALSE;
		}
	}
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CMBTemplageDlg::OnSvTempDownload() 
{
	// TODO: Add your control notification handler code here
	m_strTempFile = _T("");
//	CreateThread( NULL, 0, CreateThreadFunc, 0, 0, 0 );//2

	
}

void CMBTemplageDlg::OnSize(UINT nType, int cx, int cy)
{
	nType;	// unused	
	if(m_bHasInit) 
	{
		int dx = LOWORD(GetDialogBaseUnits());
		int dy = HIWORD(GetDialogBaseUnits());
		int nButtonWidth = 15*dx;
		int nButtonHeight = 3*dy/2;
		
		CWnd *pwndOkBtn = GetDlgItem(IDC_BUTTON_OPEN);
		CWnd *pwndGotoBtn = GetDlgItem(IDCANCEL);
		CWnd *pwndPropBtn = GetDlgItem(IDC_BUTTON_TEMPLATE);
		CWnd *pwndDelBtn = GetDlgItem(IDC_STATIC_DE1);
		CWnd *pwndEditBtn = GetDlgItem(IDC_STATIC_DE2);

		pwndOkBtn->SetWindowPos(0, cx-dx/3-nButtonWidth, dy/10, nButtonWidth, nButtonHeight, SWP_NOZORDER);
		pwndGotoBtn->SetWindowPos(0, cx-dx/3-nButtonWidth, nButtonHeight+2*dy/10, nButtonWidth, nButtonHeight, SWP_NOZORDER);
		pwndPropBtn->SetWindowPos(0, cx-dx/3-nButtonWidth, 2*nButtonHeight+3*dy/10, nButtonWidth, nButtonHeight, SWP_NOZORDER);
		pwndDelBtn->SetWindowPos(0, cx-dx/3-nButtonWidth, 3*nButtonHeight+4*dy/10, nButtonWidth, 12*nButtonHeight, SWP_NOZORDER);
		pwndEditBtn->SetWindowPos(0, cx-dx/3-nButtonWidth + 4, 4*nButtonHeight+5*dy/10, nButtonWidth - 8, 10*nButtonHeight, SWP_NOZORDER);
			
		m_wndTab.SetWindowPos(0, dx/3, dy/4, cx-dx-nButtonWidth, cy-dy/2, SWP_NOZORDER);
		
	}
}

void CMBTemplageDlg::OnSizing(UINT nSide, LPRECT lpRect)
{
	int dx = LOWORD(GetDialogBaseUnits());
	int dy = HIWORD(GetDialogBaseUnits());
	
	int nMinWidth = 30*dx;
	int nMinHeight = 10*dy;
	
	if(lpRect->right - lpRect->left < nMinWidth)
	{
		if(nSide == WMSZ_LEFT || nSide == WMSZ_TOPLEFT || nSide == WMSZ_BOTTOMLEFT)
			lpRect->left = lpRect->right - nMinWidth;
		else
			lpRect->right = lpRect->left + nMinWidth;
	}
	
	if(lpRect->bottom - lpRect->top < nMinHeight) 
	{
		if(nSide == WMSZ_TOP || nSide == WMSZ_TOPLEFT || nSide == WMSZ_TOPRIGHT)
			lpRect->top = lpRect->bottom - nMinHeight;
		else
			lpRect->bottom = lpRect->top + nMinHeight;
	}
}
