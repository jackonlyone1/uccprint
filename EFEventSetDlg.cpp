// EFEventSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "EFEventSetDlg.h"
#include "MBEventEditDlg.h"
#include "MBEventEditDlg7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEFEventSetDlg dialog


CEFEventSetDlg::CEFEventSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEFEventSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEFEventSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	nCursorType		= 0;
	nEventType		= 1;
	strEventString	= _T("");
	m_strToolTip = _T("");
	
	m_bModify = FALSE;
}


void CEFEventSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEFEventSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_FO_EDIT_TOOLTIP, m_strToolTip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEFEventSetDlg, CDialog)
	//{{AFX_MSG_MAP(CEFEventSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_EVENT, OnSelchangeComboEvent)
	ON_BN_CLICKED(IDC_FO_CURSOR_RADIO1, OnFoCursorRadio1)
	ON_BN_CLICKED(IDC_FO_CURSOR_RADIO2, OnFoCursorRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEFEventSetDlg message handlers

void CEFEventSetDlg::OnButtonSelect() 
{
	// TODO: Add your control notification handler code here
	switch(nEventType)
	{
	case 4: // Open file.
		{
			CString title;
			title.LoadString(IDS_FO_OPEN_FILE_TITLE);
			CFileDialog dlgFile (TRUE,NULL,NULL,OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,_T("Open Files(*.*)|*.*||"),this);
			if(dlgFile.DoModal() == IDOK)
			{
				strEventString = dlgFile.GetPathName();
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(strEventString);
			}
		}
		break;
	case 5:
		{
			CString title;
			title.LoadString(IDS_FO_OPEN_FILE_TITLE);
			CFileDialog dlgFile (TRUE,NULL,NULL,OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,_T("Exe Files(*.exe)|*.exe|All Files(*.*)|*.*||"),this);
			if(dlgFile.DoModal() == IDOK)
			{
				strEventString = dlgFile.GetPathName();
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(strEventString);
			}
		}
		break;
	case 8:
		{
			MBEventEditDlg2 dlg;
			dlg.strPageName = strEventString;
			if(dlg.DoModal() == IDOK)
			{
				strEventString = dlg.strPageName;
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(strEventString);
			}
		}
		break;
	case 13:
		{
			CMBEventEditDlg7 dlg;
			dlg.strObjName = strEventString;
			if(dlg.DoModal() == IDOK)
			{
				strEventString = dlg.strObjName;
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(strEventString);
			}
		}
		break;
	case 14:
		{
			CMBEventEditDlg7 dlg;
			dlg.strObjName = strEventString;
			if(dlg.DoModal() == IDOK)
			{
				strEventString = dlg.strObjName;
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(strEventString);
			}
		}
		break;
	}
}

BOOL CEFEventSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	{

		UINT nType = 1;
		CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_FO_CURSOR_COMBO);
		CString strAdd = _T("HANDLE");
		int nItem = pBox->AddString(strAdd);
		pBox->SetItemData(nItem,(UINT)nType);
		
		strAdd = _T("CROSS");
		nType = 2;
		nItem = pBox->AddString(strAdd);
		pBox->SetItemData(nItem,(UINT)nType);
		
		strAdd = _T("HANDLE1");
		nType = 3;
		nItem = pBox->AddString(strAdd);
		pBox->SetItemData(nItem,(UINT)nType);
		
		strAdd = _T("ROUND");
		nType = 4;
		nItem = pBox->AddString(strAdd);
		pBox->SetItemData(nItem,(UINT)nType);

		if(nCursorType == 0)
		{
			CheckRadioButton(IDC_FO_CURSOR_RADIO1,IDC_FO_CURSOR_RADIO2,IDC_FO_CURSOR_RADIO1);
			pBox->EnableWindow(FALSE);
			pBox->SetCurSel(0);
		}
		else
		{
			CheckRadioButton(IDC_FO_CURSOR_RADIO1,IDC_FO_CURSOR_RADIO2,IDC_FO_CURSOR_RADIO2);
			pBox->SetCurSel(nCursorType -1);
		}
	}

	GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(strEventString);

	UINT nType = 1;
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO_EVENT);
	CString strAdd = _T("None");
	int nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);
	
	strAdd = _T("Send Email...");
	nType = 2;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Open URL...");
	nType = 3;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Open file...");
	nType = 4;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Execute file...");
	nType = 5;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Save file and send it with email");
	nType = 6;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Print Document");
	nType = 7;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Jump to page...");
	nType = 8;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("First page");
	nType = 9;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Last page");
	nType = 10;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Page previous");
	nType = 11;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Page Next");
	nType = 12;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Hide object...");
	nType = 13;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);


	strAdd = _T("Show object...");
	nType = 14;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Reset all fields");
	nType = 15;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Submit record");
	nType = 16;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Export data to image");
	nType = 17;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	strAdd = _T("Refresh");
	nType = 18;
	nItem = pBox->AddString(strAdd);
	pBox->SetItemData(nItem,(UINT)nType);

	pBox->SetCurSel(nEventType - 1);

	if(nEventType == 1 ||
		nEventType == 6 ||
		nEventType == 7 ||
		nEventType == 9 ||
		nEventType == 10 ||
		nEventType == 11 ||
		nEventType == 12 ||
		nEventType == 15 ||
		nEventType == 16 ||
		nEventType == 17 ||
		nEventType == 18
		)
	{
		GetDlgItem(IDC_EDIT_EVENT_PARAM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(FALSE);
	}
	else
	{
		switch(nEventType)
		{
		case 2:
		case 3:
			{
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(FALSE);
			}
			break;
			
		case 4:
		case 5:
		case 8:
		case 13:
		case 14:
			{
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(TRUE);
			}
			break;
		}
		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEFEventSetDlg::OnFoCursorRadio1() 
{
	// TODO: Add your control notification handler code here
	nCursorType = 0;
	GetDlgItem(IDC_FO_CURSOR_COMBO)->EnableWindow(FALSE);
}

void CEFEventSetDlg::OnFoCursorRadio2() 
{
	// TODO: Add your control notification handler code here
	nCursorType = 1;
	GetDlgItem(IDC_FO_CURSOR_COMBO)->EnableWindow(TRUE);
}

void CEFEventSetDlg::OnSelchangeComboEvent() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO_EVENT);
	int nCur = pBox->GetCurSel();

	int nOldEventType = nEventType;
	nEventType = (UINT)pBox->GetItemData(nCur);

	if(nOldEventType != nEventType)
	{
		GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetWindowText(_T(""));
	}

	if(nEventType == 1 ||
		nEventType == 6 ||
		nEventType == 7 ||
		nEventType == 9 ||
		nEventType == 10 ||
		nEventType == 11 ||
		nEventType == 12 ||
		nEventType == 15 ||
		nEventType == 16 ||
		nEventType == 17 ||
		nEventType == 18
		)
	{
		GetDlgItem(IDC_EDIT_EVENT_PARAM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(FALSE);
	}
	else
	{
		switch(nEventType)
		{
		case 2:
		case 3:
			{
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(FALSE);
			}
			break;

		case 4:
		case 5:
		case 8:
		case 13:
		case 14:
			{
				GetDlgItem(IDC_EDIT_EVENT_PARAM)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(TRUE);
			}
			break;
		}
	}
}


void CEFEventSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	GetDlgItem(IDC_EDIT_EVENT_PARAM)->GetWindowText(strEventString);
	GetDlgItem(IDC_FO_EDIT_TOOLTIP)->GetWindowText(m_strToolTip);
	{
		CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO_EVENT);
		int nCur = pBox->GetCurSel();
		nEventType = (UINT)pBox->GetItemData(nCur);
	}
	
	if(nEventType == 1 ||
		nEventType == 6 ||
		nEventType == 7 ||
		nEventType == 9 ||
		nEventType == 10 ||
		nEventType == 11 ||
		nEventType == 12 ||
		nEventType == 15 ||
		nEventType == 16 ||
		nEventType == 17 ||
		nEventType == 18
		)
	{
		
	}
	else
	{
		if(strEventString.IsEmpty())
		{
			AfxMessageBox(IDS_FO_HYLINK_MSG);
			GetDlgItem(IDC_EDIT_EVENT_PARAM)->SetFocus();
			return;
		}
	}
	
	if(nCursorType != 0)
	{
		CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_FO_CURSOR_COMBO);
		int nCur = pBox->GetCurSel();
		nCursorType = (UINT)pBox->GetItemData(nCur);
	}
	
	if(nOldEventType != nEventType ||
		strOldEventString != strEventString ||
		nOldCursorType != nCursorType ||
		m_strToolTip != m_strOldToolTip)
	{
		m_bModify = TRUE;
	}
	
	CDialog::OnOK();
}
