// SVRichEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "SVRichEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVRichEditDlg dialog

CSVRichEditDlg::CSVRichEditDlg(const CString &strRtf)
	: CDialog(CSVRichEditDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CSVRichEditDlg)
	m_bPrintBorder = FALSE;
	//}}AFX_DATA_INIT
	m_strRtf = strRtf;
}
 
void CSVRichEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSVRichEditDlg)
	DDX_Control(pDX, IDC_CHECK_PRINT_BORDER, m_check);
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Check(pDX, IDC_CHECK_PRINT_BORDER, m_bPrintBorder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSVRichEditDlg, CDialog)
	//{{AFX_MSG_MAP(CSVRichEditDlg)
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVRichEditDlg message handlers

BOOL CSVRichEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	SetIcon(AfxGetApp()->LoadIcon(IDI_HOK_DATA_BIND), TRUE);
	
	// TODO: Add extra initialization here
	CRect rect;
	GetDlgItem(IDC_SV_RICHEDIT_CONTROL)->GetWindowRect( rect );
	ScreenToClient(rect);
	m_rtf.Create( WS_TABSTOP | WS_CHILD | WS_VISIBLE, rect, this, 100, TRUE );
	m_rtf.SetRTF(m_strRtf);
	m_rtf.ShowToolbar(TRUE);
	m_rtf.ShowRuler(TRUE);

	CRect   rcworkarea;   
	SystemParametersInfo(SPI_GETWORKAREA, 0, (LPVOID)&rcworkarea, 0);
	rcworkarea.DeflateRect(rcworkarea.Width()/6, rcworkarea.Height()/6);
	MoveWindow(rcworkarea);
	CenterWindow(NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSVRichEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	m_strRtf = m_rtf.GetRTF();
	
	CDialog::OnOK();
}

void CSVRichEditDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	// Move or resize controls
	if( m_rtf.m_hWnd )
	{
		CRect rcCancel;
		m_Cancel.GetWindowRect(rcCancel);
		ScreenToClient(rcCancel);

		int right = cy-(rcCancel.Height()+ 5);
		m_Cancel.SetWindowPos(NULL, cx - rcCancel.Width() - 5, right, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

		CRect rcOk;
		m_Ok.GetWindowRect(rcOk);
		ScreenToClient(rcOk);

		right = cy-(rcOk.Height()+5);
		m_Ok.SetWindowPos(NULL, cx - rcCancel.Width() - 5 - rcOk.Width() - 8, right, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

		m_check.SetWindowPos(NULL, 5, right, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		m_rtf.SetWindowPos(NULL, 5, 5, cx-5*2, cy-10-(rcOk.Height()+10), SWP_NOZORDER);

		Invalidate();
	}	
}


BOOL CSVRichEditDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_DESTROY || pMsg->message == WM_CLOSE)
	{
		OnOK();
		return TRUE;
	}
	
	if (pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int) pMsg->wParam;
		if(nVirtKey == VK_ESCAPE)
		{
			OnOK();
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSVRichEditDlg::OnSysCommand(UINT nID, LONG lParam)
{
	// set status bar as appropriate
	
	// don't interfere with system commands if not in help mode
	if(nID == 61536)
	{
		OnOK();
		return;
	}
	CWnd::OnSysCommand(nID, lParam);
}
