// UCCPrint.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "UCCPrint.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "UCCPrintDoc.h"
#include "UCCPrintView.h"
#include "FOHyperLink.h"
#include "FOSplashWnd.h"
#include "FOPGDIPlusProxy.h"
#include "AppLookDlg.h"
#include "MBTemplageDlg.h"
#include "NewVisualProxy.h"
#include "MBTemplageDlg.h"
#include "TemplateDlg.h"
#include "DBRecordDlg.h"
#include "OptionDlg.h"
#include <io.h>
#include <direct.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTKOptions::CTKOptions()
{
    m_strPageCaption = _T("");
	m_nPageFillType = 0;
	m_crPageBKColor = RGB(0, 0, 0);
    m_crPagePatternColor = RGB(255, 255, 255);
	m_crPagePageBKColor = RGB(255, 255, 255);
	m_strObjectName = _T("");
    m_strObjectCaption = _T("");
	m_bObjectFlat3D = false;
	m_nObjectFillType = 0;
	m_crObjectBKColor = RGB(0, 0, 0);
    m_crObjectPatternColor = RGB(255, 255, 255);
    m_strObjectToolTip = _T("");
    m_strTextName = _T("");
    m_nTextSize = 1;
    m_crTextColor = RGB(255, 255, 255);
	m_bTextBlod = false;
	m_bTextItalic = false;
	m_bTextUnderLine = false;
	m_nBorderLineWidth = 1;
	m_crBorderLineColor = RGB(255, 255, 255);
	m_nBorderLineType = 1;
	m_nLineStartArrow = 1;
	m_nLineEndArrow = 1;
	m_fPositionLeft = 0.0f;
	m_fPositionRight = 0.0f;
	m_fPositionWidth = 0.0f;
	m_fPositionHeight = 0.0f;
	m_fPositionRotate = 0.0f;
	m_bShadowVisual = false;
	m_nShadowType = 1;
	m_crShadowBKColor = RGB(0, 0, 0);
	m_crShadowPatternColor = RGB(255, 255, 255);
	m_nShadowXOffset = 4;
	m_nShadowYOffset = 4;
	m_bResizeProtect = false;
	m_bDeleteProtect = false;
	m_bRotateProtect = false;
	m_bTabOrderProtect = false;
	m_bSelectProtect = false;
	m_bMoveProtect = false;
	m_bPrintProtect = false;
	m_bCopyProtect = false;
	m_bAspectRatio = false;
	m_bXPosProtect = false;
	m_bYPosProtect = false;
	m_bWidthProtect = false;
	m_bHeightProtect = false;
}

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintApp

BEGIN_MESSAGE_MAP(CUCCPrintApp, CWinApp)
	//{{AFX_MSG_MAP(CUCCPrintApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_OPEN_TEMPLATE, OnOpenTemplate)
	ON_COMMAND(ID_NEW_FROM_BLANNK, OnNewFromBlannk)
	ON_COMMAND(ID_FO_IMPORT_DBSOURCE, OnFoImportDbsource)
	ON_COMMAND(ID_BT_HJ_VIEW, OnBtHjView)
	ON_COMMAND(ID_PAGE_OPTION, OnPageOption)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintApp construction

CUCCPrintApp::CUCCPrintApp()
{
	bOpenTemplate = FALSE;
	strTemplateFile = "";
	strTemplateFolder = "";
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	pCurDocTemplate = NULL;
	bOpenFileNow = FALSE;
	strCurPath = "";
	m_hModule = NULL;
	nCurOpenMode = -1;
	strBackImageFile = _T("");
	nCurSel = -1;
	m_hConnect = (HANDLE)-1;
	m_strDsn = _T("");
	m_nDefaultConnectType = 0;
	m_bPrintView = FALSE;
	m_strSql = _T("");
	m_nOpenType = 0;

	m_bGrid = TRUE;
	m_bFreeFormDrawing = FALSE;
	m_bGuide = TRUE;
	m_bGridSnap = TRUE;
	m_bNewSnap = TRUE;
	m_bMargin = TRUE;
	m_bShowPorts = TRUE;
	m_bDrawingFromCenter = FALSE;
	m_bGlueToShape = TRUE;
	m_bGlueToSpot = TRUE;
	
	m_bSnapToHelpLine = TRUE;
	m_bSnapToIntersect = TRUE;
	m_bListBar = TRUE;
	m_bRuler = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUCCPrintApp object

CUCCPrintApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintApp initialization

BOOL FOPSetDir(const TCHAR* pcszDir)
{         
#if defined( WIN32 )
	return SetCurrentDirectory(pcszDir);
#else   
	if (pcszDir != NULL && *pcszDir != '\0')
	{
		return _chdrive(_totupper(*pcszDir) - 'A' + 1) == 0 &&
			chdir(pcszDir) == 0;
	}               
	
	return FALSE;
#endif
}

static BOOL NEAR PASCAL FO_SetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue) 
{ 
	if (::RegSetValue(HKEY_CLASSES_ROOT, lpszKey, REG_SZ, lpszValue,
		lstrlen(lpszValue)) != ERROR_SUCCESS)
	{
		TRACE1("Warning: registration database update failed for key'%Fs'\n", lpszKey);
		return FALSE;
	}
	
	return TRUE;
	
} 

BOOL FO_WriteRegStringCreateValue(HKEY MainKey, LPCTSTR SubPath, LPTSTR SectionName,TCHAR *KeyName)
{
	DWORD dwErrorCode;
	HKEY hKey;
	DWORD dwDisposition;
	
	dwErrorCode = RegCreateKeyEx(MainKey,
		SubPath,
		0,
		_T(""),
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL, //Security
		&hKey,
		&dwDisposition );
	if (dwErrorCode != ERROR_SUCCESS) goto end;
	
	if(!KeyName) goto end;
	dwErrorCode = RegSetValueEx(hKey, SectionName, NULL, REG_SZ, 
		(LPBYTE)KeyName, _tcslen(KeyName)*sizeof(TCHAR));
	
end:
	if (hKey) RegCloseKey(hKey);
	if (dwErrorCode == ERROR_SUCCESS) 
	       return TRUE;
	else
		return FALSE;
}

BOOL CUCCPrintApp::InitInstance()
{
	// E-XD++ Library Add line.
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	AfxOleInit();

	AfxInitRichEdit();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
//	gfxData.m_bOldPortVisible = TRUE;
	gfxData.InitGUIType(GUI_BLUE);
	
	//E-XD++ Library add lines.
	FOInit(RUNTIME_CLASS(CNewVisualProxy2));
	DoLoadSetting();
	gfxData.m_bWithStyle = FALSE;
	gfxData.m_bEnableTableLabelEditingByClick = FALSE;
//	FOSetUnitOfRuler(RULER_MM);
//	gfxData.m_strDefFontName = _T("Arial");
//	gfxData.m_nDefShapeHeight = 21;
	gfxData.fo_bWithLinkFeature = FALSE;

	// Enable xp mode.
	FOEnableXPStyle(TRUE);

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	SetRegistryKey(_T("ucancode\\UCCPrint"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

//	SetRegistryBase(_T("Settings"));
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	pCurDocTemplate = new CMultiDocTemplate(
		IDR_UCCPRITYPE,
		RUNTIME_CLASS(CUCCPrintDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CUCCPrintView));
	AddDocTemplate(pCurDocTemplate);

	HKEY	hKey;
	unsigned long enm = 0;
	TCHAR   buf[256];
	DWORD	len = 255;
	
	if(ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE, 
		_T("SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources"), &hKey)) {
		while(ERROR_NO_MORE_ITEMS != RegEnumValue(hKey, enm, buf, &len, NULL, NULL, NULL, NULL)) {
			m_arrStrDsn.Add(buf);
			len = 255;
			enm++;
		}
	}
	RegCloseKey(hKey);
	
	if(ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, 
		_T("SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources"), &hKey)) {
		while(ERROR_NO_MORE_ITEMS != RegEnumValue(hKey, enm, buf, &len, NULL, NULL, NULL, NULL)) {
			m_arrStrDsn.Add(buf);
			len = 255;
			enm++;
		}
	}
	RegCloseKey(hKey);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

//	SetClassLong(m_pMainWnd->m_hWnd, GCL_HICON, (LONG)LoadIcon(IDR_MAINFRAME));
	
	m_pMainWnd = pMainFrame;
	DragAcceptFiles(pMainFrame->m_hWnd,TRUE);
	// The main window has been initialized, so show and update it.

	BOOL bNeed = TRUE;
	if (m_lpCmdLine[0] == '\0')
	{
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();
		bNeed = FALSE;
		CString strPathX = AfxGetApp()->m_pszHelpFilePath;
		strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
		FOPSetDir(strPathX);
		
		CTemplateDlg dlg;
		if(dlg.DoModal() != IDOK)
		{
			pCurDocTemplate->OpenDocumentFile(NULL);
			
		}
		else
		{
			if(theApp.nCurOpenMode == 103)
			{
				pCurDocTemplate->OpenDocumentFile(NULL);
			}
			else if(theApp.nCurOpenMode == 100)
			{
				pCurDocTemplate->OpenDocumentFile(NULL);
			}
		}
	}
	else
	{

		CString FileType;
		FileType = _T(m_lpCmdLine);
		if(FileType.Left(1) == _T("\""))
			FileType = FileType.Right(FileType.GetLength() -1);
		
		if(FileType.Right(1) == _T("\""))
			FileType = FileType.Left(FileType.GetLength() -1);

		FileType.MakeUpper();
		CString strFile = FileType;
		FileType = FileType.Right(4);
		if(FileType == _T(".UTP"))
		{
			
			CString strPathX = AfxGetApp()->m_pszHelpFilePath;
			strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
			CString strMainPath;
			strMainPath = strPathX+_T("\\Template\\");
			
			bOpenTemplate = TRUE;
			strTemplateFile = strFile;
			strTemplateFolder = strMainPath;
			pCurDocTemplate->OpenDocumentFile(NULL);

		}
		else
		{
			CString strPathX = m_lpCmdLine;
			strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
			FOPSetDir(strPathX);

			AfxMessageBox(m_lpCmdLine);
	
			OpenDocumentFile(m_lpCmdLine);
		}
		
	}
	
	EnableShellOpen( );

	CString      strFileTypeId;
	pCurDocTemplate->GetDocString(strFileTypeId,CDocTemplate::regFileTypeId);
	FO_SetRegKey(_T(".ucp"), strFileTypeId);
	FO_SetRegKey(_T(".utp"), strFileTypeId);
	
	TCHAR pathname[512];
	TCHAR _pathname[512];
	TCHAR sname[512];
	TCHAR tmppath[512];
	::GetModuleFileName(m_hInstance, pathname, 512);
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	
	_tsplitpath( pathname, drive, dir, fname, ext );
	_tcscpy(sname,fname);
	_tcscat(sname,ext);
	
	_tcscpy(_pathname,_T("\""));
	_tcscat(_pathname,pathname);
	_tcscat(_pathname,_T("\" \"%1\""));
	OutputDebugString(_pathname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,strFileTypeId + _T("\\shell\\open\\command"),NULL,_pathname);
	
	_tcscpy( tmppath , _T(".ucp\\OpenWithList\\"));_tcscat( tmppath ,sname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,tmppath,NULL,NULL);

	_tcscpy( tmppath , _T(".utp\\OpenWithList\\"));_tcscat( tmppath ,sname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,tmppath,NULL,NULL);

	_tcscpy(pathname,_T("Applications\\"));
	_tcscat(pathname,sname);
	_tcscat(pathname,_T("\\shell\\open\\command"));
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,pathname ,NULL,_pathname);
	
	if(bNeed)
	{
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();

	}

	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strMainPath;
	strMainPath = strPathX+_T("\\Template\\");
	
	if(!theApp.DirectoryExists(strMainPath))
	{
		theApp.MakeDirectory(strMainPath);
	}
	// Set application general look:
//	CAppLookDlg dlg (TRUE);
//	dlg.DoModal ();

	// Show Splash Window
	CFOSplashWnd* pSplash = new CFOSplashWnd(IDB_SPLASH, 3500);
	pSplash->Create();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	CFOHyperLink m_Home;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_HOMEPAGE, m_Home);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CUCCPrintApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Home.SetColors(RGB(0,0,255), RGB(0,0,255), RGB(51,102,153) );
	m_Home.SetURL(_T("http://www.ucancode.net"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("To learn more about our other products,visit:http://www.ucancode.net"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CAboutDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HKEY hKey1;
	LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Microsoft\\Shared Tools\\MSInfo"),0L,KEY_ALL_ACCESS,&hKey1);
	if (res == ERROR_SUCCESS)
	{
		DWORD bufsize = _MAX_PATH;
		char msinfo[_MAX_PATH];

		res = RegQueryValueEx(hKey1,_T("Path"),0L,0,(LPBYTE)msinfo,(LPDWORD)&bufsize);
		RegCloseKey(hKey1);
		if (res == ERROR_SUCCESS) WinExec(msinfo, SW_SHOW);
	}
}
// 
// void CUCCPrintApp::OnTemplateSample1() 
// {
// 	// TODO: Add your command handler code here
// 	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
// 	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
// 	CString strMainPath;
// 	strMainPath = strPathX+ _T("\\Template\\");
// 	
// 	bOpenTemplate = TRUE;
// 	strTemplateFile = strMainPath + _T("expense.utp");
// 	strTemplateFolder = strMainPath;
// 
// 	pCurDocTemplate->OpenDocumentFile(NULL);
// }
// 
// void CUCCPrintApp::OnTemplateSample2() 
// {
// 	// TODO: Add your command handler code here
// 	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
// 	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
// 	CString strMainPath;
// 	strMainPath = strPathX+_T("\\Template\\");
// 	
// 	bOpenTemplate = TRUE;
// 	strTemplateFile = strMainPath + _T("Invoice.utp");
// 	strTemplateFolder = strMainPath;
// 
// 	pCurDocTemplate->OpenDocumentFile(NULL);
// }

void CUCCPrintApp::OnOpenTemplate() 
{
	// TODO: Add your command handler code here
	CMBTemplageDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CString strPathX = AfxGetApp()->m_pszHelpFilePath;
		strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
		CString strMainPath;
		strMainPath = strPathX+_T("\\Template\\");

		bOpenTemplate = TRUE;
		strTemplateFile = dlg.m_strTempFile;
		strTemplateFolder = strMainPath;
		pCurDocTemplate->OpenDocumentFile(NULL);
	}
}

BOOL CUCCPrintApp::DirectoryExists(const CString& Path)
{
#ifdef WIN32
	DWORD dwRetVal = GetFileAttributes( Path );
	if ( dwRetVal == 0xFFFFFFFF )
		return FALSE;
	
	else if (dwRetVal & FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;
	
	return FALSE;
#else
	CFileStatus FileStatus;
	
	if (CFile::GetStatus(Path, FileStatus) == TRUE  &&
		FileStatus.m_attribute & directory)
	{
		return TRUE;
	}
	else if (FileSystemExists(GetFullPathName(Path)))
	{
		return TRUE;
	}
	
	return FALSE;
#endif
}

BOOL CUCCPrintApp::MakeDirectory(const CString& pcszDirectory)
{
	static TCHAR cSlash = _T('\\');
	
	BOOL bRetVal = FALSE;
	
	const int nLength = _tcslen( pcszDirectory ) + 1;
	LPTSTR pszDirectoryPath = (LPTSTR)malloc( nLength * sizeof( TCHAR ) );
	if( pszDirectoryPath )
	{
		
		LPCTSTR pcszNextDirectory = pcszDirectory;
		
		if( nLength > 2 && *pcszNextDirectory == cSlash && *(pcszNextDirectory+1) == cSlash )
		{
			pcszNextDirectory += 2;
			while( *pcszNextDirectory && *pcszNextDirectory != cSlash )	pcszNextDirectory++;
			pcszNextDirectory++;
			while( *pcszNextDirectory && *pcszNextDirectory != cSlash )	pcszNextDirectory++;
			_tcsncpy( pszDirectoryPath, pcszDirectory, pcszNextDirectory - pcszDirectory );
			pszDirectoryPath[ pcszNextDirectory - pcszDirectory ] = '\000';
		}
		
		bRetVal = TRUE;
		
		do
		{
			if( *pcszNextDirectory )
				pcszNextDirectory++;
			
			while( *pcszNextDirectory && *pcszNextDirectory != cSlash )
				pcszNextDirectory++;
			
			_tcsncpy( pszDirectoryPath, pcszDirectory, pcszNextDirectory - pcszDirectory );
			pszDirectoryPath[ pcszNextDirectory - pcszDirectory ] = '\000';
			
			if( _taccess( pszDirectoryPath, 0 ) )
			{
				if( !CreateDirectory( pszDirectoryPath, NULL ) )
				{
					bRetVal = FALSE;
					break;
				}
			}
		}
		while( *pcszNextDirectory );
		
		free( pszDirectoryPath );
		pszDirectoryPath = NULL;
	}
	return bRetVal;
}

int CUCCPrintApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	DoSaveSetting();
	return CWinApp::ExitInstance();
}

void CUCCPrintApp::OnNewFromBlannk() 
{
	// TODO: Add your command handler code here
	CTemplateDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(theApp.nCurOpenMode == 100)
		{
			pCurDocTemplate->OpenDocumentFile(NULL);
		}
	}
}

void CUCCPrintApp::OnFoImportDbsource() 
{
	// TODO: Add your command handler code here
	CConnectDlg *cnnDlg = &((CUCCPrintApp*)AfxGetApp())->m_connDlg;
	
	// TODO: Add your specialized creation code here
	cnnDlg->m_pOdbc = &m_odbc;
	if(IDCANCEL == cnnDlg->DoModal())
		return;
	
	CWaitCursor myWaitCursor;
	
	if(FOP_SUCCESS != m_odbc.Open(cnnDlg->m_strDSN, cnnDlg->m_strSQL, 0, cnnDlg->m_nOpenType, 0, NULL, NULL))
		return;
	
	m_strSql = cnnDlg->m_strSQL;
	m_nOpenType = cnnDlg->m_nOpenType;
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	theApp.m_dbcols.RemoveAll();
	pParent->m_wndTableBar.DeleteAll();
	int nTotal = m_odbc.GetNumCols();
	int x= 0;
	for(x= 0; x < nTotal; x++)
	{
		CString strCol;
		m_odbc.GetColName(x, &strCol);
		m_dbcols.Add(strCol);
		pParent->m_wndTableBar.AddColumn(strCol, 3);
	}
	pParent->m_wndTableBar.AddColumn(_T("xdtTime"), 1);
	pParent->m_wndTableBar.AddColumn(_T("xdtDate"), 0);
	pParent->m_wndTableBar.m_wndTab.ActivateTab(1);
}

void CUCCPrintApp::OnBtHjView() 
{
	// TODO: Add your command handler code here
	CDBRecordDlg dlg;
	dlg.DoModal();
}

void CUCCPrintApp::OnPageOption() 
{
	// TODO: Add your command handler code here
	COptionDlg dlg;
	dlg.m_nConnectType = m_nDefaultConnectType;
	if(dlg.DoModal() == IDOK)
	{
		m_nDefaultConnectType = dlg.m_nConnectType;
	}
}

void CUCCPrintApp::DoSaveSetting()
{
	CReg reg;
	if (reg.Create (HKEY_CURRENT_USER, REG_EDITPAD_IDE, KEY_WRITE))
    {
		DWORD dTest = 1;
		reg.SaveNumber( _T ("nTest0"), (DWORD)dTest);
		reg.SaveNumber( _T ("nSetVal0"), (DWORD)m_bGrid);
		reg.SaveNumber( _T ("nSetVal1"), (DWORD)m_bFreeFormDrawing);
		reg.SaveNumber( _T ("nSetVal2"), (DWORD)m_bGuide);
		reg.SaveNumber( _T ("nSetVal3"), (DWORD)m_bGridSnap);
		reg.SaveNumber( _T ("nSetVal4"), (DWORD)m_bNewSnap);
		reg.SaveNumber( _T ("nSetVal5"), (DWORD)m_bMargin);
		reg.SaveNumber( _T ("nSetVal6"), (DWORD)m_bShowPorts);
		reg.SaveNumber( _T ("nSetVal7"), (DWORD)m_bDrawingFromCenter);
		reg.SaveNumber( _T ("nSetVal8"), (DWORD)m_bGlueToShape);
		reg.SaveNumber( _T ("nSetVal9"), (DWORD)m_bGlueToSpot);



		reg.SaveNumber( _T ("nSetVal10"), (DWORD)gfxData.m_bExpandEditBoxCenter);
		reg.SaveNumber( _T ("nSetVal11"), (DWORD)gfxData.m_bFullFeaturePort);
		reg.SaveNumber( _T ("nSetVal12"), (DWORD)gfxData.m_bWithSnap);
		
		reg.SaveNumber( _T ("nSetVal13"), (DWORD)gfxData.m_bWithStyle);
		reg.SaveNumber( _T ("nSetVal14"), (DWORD)gfxData.m_bWithPortIndexShow);
		reg.SaveNumber( _T ("nSetVal15"), (DWORD)gfxData.m_bWithPinNumberShow);
//		reg.SaveNumber( _T ("nSetVal16"), (DWORD)gfxData.m_bfoWithPort);

		reg.SaveNumber( _T ("nSetVal17"), (DWORD)gfxData.m_nDefPortHeight);
		reg.SaveNumber( _T ("nSetVal18"), (DWORD)gfxData.m_nDefPortWidth);
		reg.SaveNumber( _T ("nSetVal19"), (DWORD)gfxData.m_nDefPortType);
		reg.SaveNumber( _T ("nSetVal20"), (DWORD)gfxData.m_nDefPortSide);
		reg.SaveNumber( _T ("nSetVal21"), (DWORD)gfxData.m_bUseDefaultPort);
		reg.SaveNumber( _T ("nSetVal22"), (DWORD)gfxData.m_nDefShapeHeight);

		reg.SaveNumber( _T ("nSetVal23"), (DWORD)m_bSnapToHelpLine);
		reg.SaveNumber( _T ("nSetVal24"), (DWORD)m_bSnapToIntersect);
		reg.SaveNumber( _T ("nSetVal25"), (DWORD)gfxData.m_bWithSnap);
		reg.SaveNumber( _T ("nSetVal26"), (DWORD)m_bListBar);
		reg.SaveNumber( _T ("nSetVal27"), (DWORD)m_bRuler);

		
    }
	reg.Close ();

}

void CUCCPrintApp::DoLoadSetting()
{
	DWORD dTest = 0;
	CReg reg;
	if (reg.Create (HKEY_CURRENT_USER, REG_EDITPAD_IDE, KEY_READ))
	{
		reg.LoadNumber( _T ("nTest0"), &dTest);
		if(dTest == 1)
		{
			DWORD nTemp =1;
			reg.LoadNumber( _T ("nSetVal0"), &nTemp);
			if(nTemp == 1)
			{
				m_bGrid = TRUE;
			}
			else
			{
				m_bGrid = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal1"), &nTemp);
			if(nTemp == 1)
			{
				m_bFreeFormDrawing = TRUE;
			}
			else
			{
				m_bFreeFormDrawing = FALSE;
			}
			
			reg.LoadNumber( _T ("nSetVal2"), &nTemp);
			if(nTemp == 1)
			{
				m_bGuide = TRUE;
			}
			else
			{
				m_bGuide = FALSE;
			}
			
			reg.LoadNumber( _T ("nSetVal3"), &nTemp);
			if(nTemp == 1)
			{
				m_bGridSnap = TRUE;
			}
			else
			{
				m_bGridSnap = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal4"), &nTemp);
			if(nTemp == 1)
			{
				m_bNewSnap = TRUE;
			}
			else
			{
				m_bNewSnap = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal5"), &nTemp);
			if(nTemp == 1)
			{
				m_bMargin = TRUE;
			}
			else
			{
				m_bMargin = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal6"), &nTemp);
			if(nTemp == 1)
			{
				m_bShowPorts = TRUE;
			}
			else
			{
				m_bShowPorts = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal7"), &nTemp);
			if(nTemp == 1)
			{
				m_bDrawingFromCenter = TRUE;
			}
			else
			{
				m_bDrawingFromCenter = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal8"), &nTemp);
			if(nTemp == 1)
			{
				m_bGlueToShape = TRUE;
			}
			else
			{
				m_bGlueToShape = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal9"), &nTemp);
			if(nTemp == 1)
			{
				m_bGlueToSpot = TRUE;
			}
			else
			{
				m_bGlueToSpot = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal10"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bExpandEditBoxCenter = TRUE;
			}
			else
			{
				gfxData.m_bExpandEditBoxCenter = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal11"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bFullFeaturePort = TRUE;
			}
			else
			{
				gfxData.m_bFullFeaturePort = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal12"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithSnap = TRUE;
			}
			else
			{
				gfxData.m_bWithSnap = FALSE;
			}
			
			reg.LoadNumber( _T ("nSetVal13"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithStyle = TRUE;
			}
			else
			{
				gfxData.m_bWithStyle = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal14"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithPortIndexShow = TRUE;
			}
			else
			{
				gfxData.m_bWithPortIndexShow = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal15"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithPinNumberShow = TRUE;
			}
			else
			{
				gfxData.m_bWithPinNumberShow = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal16"), &nTemp);
			if(nTemp == 1)
			{
//				gfxData.m_bfoWithPort = TRUE;
			}
			else
			{
		//		gfxData.m_bfoWithPort = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal17"), &nTemp);
			gfxData.m_nDefPortHeight = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal18"), &nTemp);
			gfxData.m_nDefPortWidth = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal19"), &nTemp);
			gfxData.m_nDefPortType = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal20"), &nTemp);
			gfxData.m_nDefPortSide = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal21"), &nTemp);
			gfxData.m_bUseDefaultPort = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal22"), &nTemp);
			gfxData.m_nDefShapeHeight = (int)nTemp;


			reg.LoadNumber( _T ("nSetVal23"), &nTemp);
			if(nTemp == 1)
			{
				m_bSnapToHelpLine = TRUE;
			}
			else
			{
				m_bSnapToHelpLine = FALSE;
			}

			reg.LoadNumber( _T ("nSetVal24"), &nTemp);
			if(nTemp == 1)
			{
				m_bSnapToIntersect = TRUE;
			}
			else
			{
				m_bSnapToIntersect = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal25"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithSnap = TRUE;
			}
			else
			{
				gfxData.m_bWithSnap = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal26"), &nTemp);
			if(nTemp == 1)
			{
				m_bListBar = TRUE;
			}
			else
			{
				m_bListBar = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal27"), &nTemp);
			if(nTemp == 1)
			{
				m_bRuler = TRUE;
			}
			else
			{
				m_bRuler = FALSE;
			}

		}
		
    }
	reg.Close ();

	if(dTest == 0)
	{
		DoSaveSetting();
	}
}
