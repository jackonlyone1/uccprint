// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "MainFrm.h"
#include "AppLookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
const int wmCombo = RegisterWindowMessage(_T("WM_CFOPTOOLBARWNDNOTIFY"));

IMPLEMENT_DYNAMIC(CMainFrame, CFOPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFOPMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_VIEW_DRAWBAR, OnViewDrawbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAWBAR, OnUpdateViewDrawbar)
	ON_COMMAND(ID_VIEW_FORMATBAR, OnViewFormatbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORMATBAR, OnUpdateViewFormatbar)
	ON_WM_CREATE()
	ON_COMMAND(ID_W_C_H1, OnWCH1)
	ON_COMMAND(ID_VIEW_FONTBAR, OnViewFontbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTBAR, OnUpdateViewFontbar)
	ON_COMMAND(ID_VIEW_CONTROLBAR, OnViewControlbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONTROLBAR, OnUpdateViewControlbar)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullscreen)
	ON_COMMAND(ID_DROP_MENU, OnDropMenu)
	ON_UPDATE_COMMAND_UI(ID_LAYERS, OnUpdateLayers)
	ON_COMMAND(ID_LOOK_STANDARD, OnLookStandard)
	ON_UPDATE_COMMAND_UI(ID_LOOK_STANDARD, OnUpdateLookStandard)
	ON_COMMAND(ID_LOOK_XP, OnLookXp)
	ON_UPDATE_COMMAND_UI(ID_LOOK_XP, OnUpdateLookXp)
	ON_COMMAND(ID_APP_DRAWING, OnAppDrawing)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(wmCombo , OnToolBarInit)
	ON_MESSAGE(WM_FO_UNDOREDO, OnUndoRedoOK)
	ON_REGISTERED_MESSAGE(FOP_WM_VIEWVALID, OnViewValidMsg)
	ON_REGISTERED_MESSAGE(FOP_WM_VIEWINVALID, OnViewInValidMsg)
	ON_REGISTERED_MESSAGE(FOP_WM_SHAPECHANGED,   OnShapeChangedMsg)
	ON_REGISTERED_MESSAGE(FOP_WM_VIEW_UPDATE,   OnCanvasChangedMsg)
	ON_MESSAGE(WM_FO_SETPARAMS, OnTableSelectOK)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_FO_INDEX_MOUSEPOS,
	ID_FO_INDEX_WIDTH,
	ID_FO_INDEX_HEIGHT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	pFontNameBox = NULL;
	pFontSizeBox = NULL;
	pScaleBox = NULL;
	m_crSaveFontColor = RGB(0,0,0);
	m_crSaveLineColor = RGB(0,0,0);
	m_crSaveFillColor = RGB(255,255,255);

	m_nSaveLineWidth = 1;
	m_nSaveLineType = 1;

	ShowMenuImage();
}

CMainFrame::~CMainFrame()
{
	m_UndoString.RemoveAll();
	m_RedoString.RemoveAll();
}

int CMainFrame::OnCreate(LPCREATESTRUCT LPCREATESTRUCT)
{
	if (CFOPMDIFrameWnd::OnCreate(LPCREATESTRUCT) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.ChangeToDropUndoListPickerButton(ID_EDIT_UNDO,ID_UNDODROPARROW,&m_UndoString,BS_OWNERDRAWN|BS_DROPARROWHORZ,TRUE,FALSE);
	m_wndToolBar.ChangeToDropUndoListPickerButton(ID_EDIT_REDO,ID_DROPARROW,&m_RedoString,BS_OWNERDRAWN|BS_DROPARROWHORZ,FALSE,FALSE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	
	// Create draw toolbar.
	if (!m_wndDrawToolBar.CreateEx(this) ||
		!m_wndDrawToolBar.LoadToolBar(IDR_DRAWCOMPBAR_NEW1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	// Create format toolbar.
	if (!m_wndFormatToolBar.CreateEx(this) ||
		!m_wndFormatToolBar.LoadToolBar(IDR_NEW_FORMAT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Create align toolbar.
	if (!m_wndAlignToolBar.CreateEx(this) ||
		!m_wndAlignToolBar.LoadToolBar(IDR_FO_256_FORMAT_ALIGN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndFontBar.CreateEx(this) ||
		!m_wndFontBar.LoadToolBar(IDR_FONT_BAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndPanBar.Create(this, _T("Pan Window"), WS_CHILD|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC|CBRS_FLOAT_MULTI, 
		CBRS_FOP_DEFAULT|CBRS_FOP_BDSP, 20002))
	{
		TRACE(_T("Failed to create List Bar\n"));
		return -1;
	}

	// Create toolbox
	if (!m_wndTableBar.Create(this, _T("ToolBox Bar"), WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC, 
		CBRS_FOP_DEFAULT|CBRS_FOP_BDSP, 1212))
	{
		TRACE(_T("Failed to create List Bar\n"));
		return -1;
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable

	SetMenuImageRes(IDR_MAINFRAME);
	SetMenuImageRes(IDR_FO_256_FORMAT_ALIGN);
	SetMenuImageRes(IDR_NEW_FORMAT);
	SetMenuImageRes(IDR_FO_SHAPESBAR);
	SetMenuImageRes(IDR_FO_256_DRAWBAR);
	SetMenuImageRes(IDR_FO_256_EDITBAR);
	SetMenuImageRes(IDR_TOOLBAR_TEMP1);

	// looks a little bit better...
	m_wndToolBar.SetWindowText(_T("File"));
	m_wndAlignToolBar.SetWindowText(_T("Align"));
	m_wndFormatToolBar.SetWindowText(_T("Format"));
	m_wndDrawToolBar.SetWindowText(_T("Draw"));
	m_wndFontBar.SetWindowText(_T("Font"));
	m_wndTableBar.EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	m_wndDrawToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFormatToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndAlignToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFontBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPanBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	FOPComboBoxData data;
	data.nComboID = IDC_COMBO_ZOOMVALUE;
	data.dwComboStyle = (UINT)CBS_DROPDOWN|WS_VSCROLL|CBS_HASSTRINGS|CBS_OWNERDRAWVARIABLE;
	data.nDefaultWidth = 60;
	data.nMinSize = 40;
	data.nHeight = 200;
	m_wndFormatToolBar.ChangeToComboButton(ID_ZOOM_VALUE,data);

	m_wndToolBar.ChangeToDropTablePickerButton(ID_FO_DRAW_TABLE_SHAPE,ID_FO_DRAWTABLE_ARROW,
		BS_OWNERDRAWN|BS_DROPARROWHORZ,FALSE);

	data.nComboID = IDC_COMBO_FONTNAME;
	data.dwComboStyle = (UINT)CBS_DROPDOWN|WS_VSCROLL|CBS_HASSTRINGS|CBS_SORT|CBS_OWNERDRAWVARIABLE;
	data.nDefaultWidth = 150;
	data.nMinSize = 40;
	data.nHeight = 450;
	m_wndFontBar.ChangeToFontFaceComboButton(ID_FONT_FACENAME,data);

	data.nComboID = IDC_COMBO_LAYER;
	data.dwComboStyle = (UINT)CBS_DROPDOWN|WS_VSCROLL|CBS_HASSTRINGS|CBS_SORT|CBS_OWNERDRAWVARIABLE;
	data.nDefaultWidth = 85;
	data.nMinSize = 40;
	data.nHeight = 250;
//	m_wndFormatToolBar.ChangeToLayerComboButton(ID_LAYERS,data);

	data.nComboID = IDC_COMBO_FONTSIZE;
	data.dwComboStyle = (UINT)CBS_DROPDOWN|WS_VSCROLL|CBS_HASSTRINGS|CBS_OWNERDRAWVARIABLE;
	data.nDefaultWidth = 40;
	data.nMinSize = 40;
	data.nHeight = 350;
	m_wndFontBar.ChangeToComboButton(ID_FONT_TYPESIZE,data);

	// Add drop arrow button on the toolbar.
	m_wndFontBar.ChangeToDropColorPickerButton(ID_FONT_COLOR,ID_FONT_ARROW0,16,FALSE);

	// Add drop arrow button on the toolbar.
	m_wndFontBar.ChangeToDropColorPickerButton(ID_LINE_COLOR,ID_LINE_ARROW0,16,FALSE);

	// Add drop arrow button on the toolbar.
	m_wndFontBar.ChangeToDropColorPickerButton(ID_FILL_COLOR,ID_FILL_ARROW0,16,FALSE);

	// Add drop arrow button on the toolbar.
	m_wndFontBar.ChangeToDropLineWidthPickerButton(ID_LINE_WIDTH,ID_LINE_WIDTH_ARROW0,16,FALSE);

	// Add drop arrow button on the toolbar.
	m_wndFontBar.ChangeToDropLineTypePickerButton(ID_LINE_TYPE,ID_LINE_TYPE_ARROW0,16,FALSE);

	// Add drop down menu on the toolbar.
	m_wndFontBar.ChangeToDropMenuButton(ID_DROP_MENU,IDR_NEW_MENU,0);
	m_wndToolBar.ChangeToDropMenuButton(ID_FILE_NEW,IDR_NEW_MENU,1);

	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndDrawToolBar,AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_wndAlignToolBar,AFX_IDW_DOCKBAR_BOTTOM);
	DockControlBar(&m_wndFormatToolBar,AFX_IDW_DOCKBAR_TOP);
	DockControlBar(&m_wndFontBar,AFX_IDW_DOCKBAR_TOP);
	DockControlBarLeftOf(&m_wndFormatToolBar,&m_wndToolBar);
	DockControlBarEx(&m_wndPanBar, AFX_IDW_DOCKBAR_RIGHT, 0.50, 120);
	DockControlBarEx(&m_wndTableBar, AFX_IDW_DOCKBAR_RIGHT, 50, 220);

	return 0;
}

static int nFontSizes[] = 
	{8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72,80,88,96,128,168,272,405,524,624};

void CMainFrame::InitFontSizes(CComboBox *pBox)
{
	// Clear the combobox.
	pBox->ResetContent();
	TCHAR buf[10];
	for (int i = 0; i < 25; i++)
	{
		wsprintf(buf, _T("%d"), nFontSizes[i]);
		pBox->AddString(buf);
	}
}

void CMainFrame::InitFonts(CComboBox *pBox)
{
	// Clear the combobox.
	pBox->ResetContent();
	
	HDC hDC  = ::GetDC(m_hWnd);
	::EnumFonts( hDC, NULL, (FONTENUMPROC)EnumFontProc, (LPARAM)pBox );//Enumerate
	::ReleaseDC(m_hWnd, hDC);
}

BOOL CALLBACK CMainFrame::EnumFontProc(LPLOGFONT lpLogFont, LPTEXTMETRIC lpTextMetric, short nFontType, LPHANDLE lpData)
{
	UNUSED_ALWAYS( lpTextMetric );
	
	if((nFontType == TRUETYPE_FONTTYPE) && (lpLogFont->lfCharSet != SYMBOL_CHARSET))
	{
		CComboBox* pListBox = (CComboBox*)lpData;
		ASSERT(pListBox);
		
		int nIndex = pListBox->AddString(lpLogFont->lfFaceName);
		pListBox->SetItemData( nIndex, (DWORD)nFontType );
	}
	else
	{
		CComboBox* pListBox = (CComboBox*)lpData;
		ASSERT(pListBox);
		
		int nIndex = pListBox->AddString(lpLogFont->lfFaceName);
		pListBox->SetItemData( nIndex, (DWORD)nFontType );
	}
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//E-XD++ Library add lines.
	int DesktopWidth  = GetSystemMetrics(SM_CXSCREEN);
	int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);

	// Just Make It Small So We Will Not Feel a "Blink"
	CRect MainWindow_Rect(0,0, DesktopWidth, DesktopHeight); // First Opening Screen

	cs.x = (DesktopWidth - MainWindow_Rect.right)/2;
	cs.y = (DesktopHeight - MainWindow_Rect.bottom)/2;

    cs.cx = MainWindow_Rect.right;
	cs.cy = MainWindow_Rect.bottom;

	if( !CFOPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREAFOAPPWIZARDRUCT cs
	//E-XD++ Library add lines.
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFOPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFOPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//E-XD++ Library add lines.
void CMainFrame::OnViewDrawbar() 
{
	// TODO: Add your command handler code here
	BOOL bVisible = m_wndDrawToolBar.IsWindowVisible();
	if(bVisible)
	{
		ShowControlBar(&m_wndDrawToolBar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_wndDrawToolBar,TRUE,FALSE);
	}
}

void CMainFrame::OnUpdateViewDrawbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_wndDrawToolBar.IsWindowVisible());
}
//E-XD++ Library add lines.
void CMainFrame::OnViewFormatbar() 
{
	// TODO: Add your command handler code here
	BOOL bVisible = m_wndFormatToolBar.IsWindowVisible();
	if(bVisible)
	{
		ShowControlBar(&m_wndFormatToolBar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_wndFormatToolBar,TRUE,FALSE);
	}
}

void CMainFrame::OnUpdateViewFormatbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_wndFormatToolBar.IsWindowVisible());
}

LONG CMainFrame::OnUndoRedoOK(UINT wParam, LONG lParam)
{
	CView* pView = FOGetActiveView();
	if(pView != NULL)
	{
		pView->PostMessage(WM_FO_UNDOREDO,wParam,lParam);
	}
	
	return 0L;
}


LONG CMainFrame::OnToolBarInit(UINT wParam , LONG lParam)
{
	HWND hWnd		 = HWND(lParam);
	UINT nNotifyCode = HIWORD(wParam);
	UINT nIDCtl		 = LOWORD(wParam);
	ASSERT(::IsWindow(hWnd));

	CWnd * pWnd = CWnd::FromHandle(hWnd);
	CComboBox * pCombo;

	switch(nIDCtl)
	{
	case IDC_COMBO_FONTNAME:
		{
			ASSERT_KINDOF(CComboBox , pWnd);
			pCombo = (CComboBox *) pWnd;
			pFontNameBox = pCombo;
			switch(nNotifyCode)
			{
			case FOP_INIT_COMBO:
				{
//					InitFonts(pCombo);
					pCombo->SetCurSel(0);
				}
				break;
			}
		}
		break;

	case IDC_COMBO_LAYER:
		{
			ASSERT_KINDOF(CComboBox , pWnd);
			pCombo = (CComboBox *) pWnd;
			pLayerBox = pCombo;
		}
		break;

	case IDC_COMBO_FONTSIZE:
		{
			ASSERT_KINDOF(CComboBox , pWnd);
			pCombo = (CComboBox *) pWnd;
			pFontSizeBox = pCombo;
			switch(nNotifyCode)
			{
			case FOP_INIT_COMBO:
				{
					InitFontSizes(pCombo);
					pCombo->SetCurSel(0);
				}
				break;
			}
		}
		break;

	case IDC_COMBO_ZOOMVALUE:
		{
			ASSERT_KINDOF(CComboBox , pWnd);
			pCombo = (CComboBox *) pWnd;
			pScaleBox = pCombo;
			switch(nNotifyCode)
			{
			case FOP_INIT_COMBO:
				{
					pCombo->AddString(_T("10"));
					pCombo->AddString(_T("20"));
					pCombo->AddString(_T("40"));
					pCombo->AddString(_T("80"));
					pCombo->AddString(_T("100"));
					pCombo->AddString(_T("200"));
					pCombo->AddString(_T("300"));
					pCombo->AddString(_T("400"));
					pCombo->AddString(_T("600"));
					pCombo->AddString(_T("800"));
					pCombo->AddString(_T("Width"));
					pCombo->AddString(_T("Height"));
					pCombo->AddString(_T("Whole"));
					pCombo->AddString(_T("Select Shapes"));
					pCombo->SelectString(-1,_T("100"));
				}
				break;
			}
		}
		break;
	}

	return 0;
}


void CMainFrame::LaunchURL(CString sURL)
{
	ShellExecute(NULL, 
				_T("open"), 
				sURL, 
				NULL,NULL, 
				SW_SHOW);
}

void CMainFrame::OnWCH1() 
{
	// TODO: Add your command handler code here
	LaunchURL("http://www.ucancode.net/");
}

void CMainFrame::OnViewFontbar() 
{
	// TODO: Add your command handler code here
	BOOL bVisible = m_wndFontBar.IsWindowVisible();
	if(bVisible)
	{
		ShowControlBar(&m_wndFontBar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_wndFontBar,TRUE,FALSE);
	}
}

void CMainFrame::OnUpdateViewFontbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_wndFontBar.IsWindowVisible());
}

void CMainFrame::OnViewControlbar() 
{
	// TODO: Add your command handler code here
	BOOL bVisible = m_wndTableBar.IsWindowVisible();
	if(bVisible)
	{
		ShowControlBar(&m_wndTableBar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_wndTableBar,TRUE,FALSE);
	}
}

void CMainFrame::OnUpdateViewControlbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_wndTableBar.IsWindowVisible());
}

void CMainFrame::OnViewFullscreen() 
{
	// TODO: Add your command handler code here
	ShowFullScreen();
}

void CMainFrame::OnUpdateViewFullscreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(IsFullScreen());
}

void CMainFrame::OnDropMenu() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateLayers(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CView *pView = NULL;
    CMDIChildWnd* pChild = (CMDIChildWnd*)MDIGetActive();
    if (pChild != NULL)
        pView = pChild->GetActiveView();

    if(pView != NULL)
    {
        pCmdUI->Enable(TRUE);
    }
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnLookStandard() 
{
	// TODO: Add your command handler code here
	FOEnableXPStyle(FALSE);
	CPtrList & list = m_listControlBars;
	POSITION pos = list.GetHeadPosition();
	while(pos != NULL)
	{
		CControlBar * pBar = (CControlBar *) list.GetNext(pos);
		pBar->Invalidate();
	}
}

void CMainFrame::OnUpdateLookStandard(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!gfxData.m_bXPMode);
}

void CMainFrame::OnLookXp() 
{
	// TODO: Add your command handler code here
	FOEnableXPStyle(TRUE);
	CPtrList & list = m_listControlBars;
	POSITION pos = list.GetHeadPosition();
	while(pos != NULL)
	{
		CControlBar * pBar = (CControlBar *) list.GetNext(pos);
		pBar->Invalidate();
	}
}

void CMainFrame::OnUpdateLookXp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(gfxData.m_bXPMode);
}

LRESULT CMainFrame::OnViewValidMsg (WPARAM wparam, LPARAM lp)
{
	lp;
	CFODrawView* pView = (CFODrawView*) wparam;
	
	m_wndPanBar.SetActiveView(pView);

	return 1;
}

LRESULT CMainFrame::OnViewInValidMsg (WPARAM wparam, LPARAM lp)
{
	CFODrawView* ActiveView = (CFODrawView*) wparam;
	CFODrawView* DeactiveView = (CFODrawView*) lp;

	// VERY important change, handling the case when switch to othe app.
	if(ActiveView == DeactiveView) 
		return 1;

	if (m_wndPanBar.GetActiveView()==DeactiveView)
	  m_wndPanBar.SetActiveView(NULL);

	return 1;
}

LRESULT CMainFrame::OnShapeChangedMsg(WPARAM wP,LPARAM /*lP*/)
{
	wP;
	m_wndPanBar.UpdateWnd(FALSE);
	return TRUE;
}

LRESULT CMainFrame::OnCanvasChangedMsg(WPARAM wP,LPARAM lP)
{
	wP;
	int nLong = (int)lP;
	if(nLong == 100)
	{
		m_wndPanBar.UpdateWnd(TRUE);
		m_wndPanBar.RedrawWindow();
	}
	else if(nLong == 200)
	{
		m_wndPanBar.UpdateWnd(FALSE);
		m_wndPanBar.UpdateZoomScale();
	}
	else
	{
		m_wndPanBar.UpdateWnd(FALSE);
	}
	return TRUE;
}

void CMainFrame::OnAppDrawing() 
{
	// TODO: Add your command handler code here
	// Set application general look:
	CAppLookDlg dlg (TRUE);
	dlg.DoModal ();

}

LONG CMainFrame::OnTableSelectOK(UINT wParam, LONG lParam)
{
	CView* pView = FOGetActiveView();
	if(pView != NULL)
	{
		pView->PostMessage(WM_FO_SETPARAMS,wParam,lParam);
	}
	
	return 0L;
}

void CMainFrame::UpdatePropertyGrid(CUCCPrintView* pView,const BOOL &bWithAction)
{
	m_wndTableBar.UpdateProperty(pView, bWithAction);
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	int            NumOfFiles = 0 ; 
	TCHAR lpszFile [MAX_PATH];
    CString FileType;
	NumOfFiles = DragQueryFile (hDropInfo, 0xffffffff, NULL, 0) ; 
    if (NumOfFiles > 0) 
	{
		for(int i = 0; i < NumOfFiles; i++)
		{
			if(DragQueryFile (hDropInfo, i, lpszFile, sizeof (lpszFile)))
			{
				FileType = lpszFile;
				FileType = FileType.Right(4);
				FileType.MakeUpper();
				if( FileType == _T(".UCP"))
				{
					((CUCCPrintApp *)AfxGetApp())->OpenDocumentFile(lpszFile);
				}
				else if(FileType == _T(".UTP"))
				{
					CString strPathX = AfxGetApp()->m_pszHelpFilePath;
					strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
					CString strMainPath;
					strMainPath = strPathX+_T("\\Template\\");
					
					theApp.bOpenTemplate = TRUE;
					theApp.strTemplateFile = CString(lpszFile);
					theApp.strTemplateFolder = strMainPath;
					theApp.pCurDocTemplate->OpenDocumentFile(NULL);
				}
				
			} 
		}
	}
	DragFinish (hDropInfo);
}
