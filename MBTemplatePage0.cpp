// MBTemplatePage0.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "MBTemplatePage0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMBTemplatePage0 dialog


CMBTemplatePage0::CMBTemplatePage0(CWnd* pParent /*=NULL*/)
	: CDialog(CMBTemplatePage0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMBTemplatePage0)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strTemplateFile = "";
	strTemplateFolder = "";
}


void CMBTemplatePage0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMBTemplatePage0)
	DDX_Control(pDX, IDC_MB_LIST, m_listItem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMBTemplatePage0, CDialog)
	//{{AFX_MSG_MAP(CMBTemplatePage0)
	ON_NOTIFY(NM_CLICK, IDC_MB_LIST, OnClickMbList)
	ON_NOTIFY(NM_DBLCLK, IDC_MB_LIST, OnDblclkMbList)
	ON_BN_CLICKED(IDC_MB_MAX_BUTTON, OnMbMaxButton)
	ON_BN_CLICKED(IDC_MB_MIN_BUTTON, OnMbMinButton)
	ON_BN_CLICKED(IDC_MB_LIE_BUTTON, OnMbLieButton)
	ON_WM_DESTROY()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_NOTIFY(NM_RCLICK, IDC_MB_LIST, OnRclickMbList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMBTemplatePage0 message handlers

BOOL CMBTemplatePage0::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnMax.SubclassControl(IDC_MB_MAX_BUTTON, this);
	m_btnMax.SetBitmap(IDB_MB_BITMAP_MAX);
	m_btnMin.SubclassControl(IDC_MB_MIN_BUTTON, this);
	m_btnMin.SetBitmap(IDB_MB_BITMAP_MIN);
	m_btnLie.SubclassControl(IDC_MB_LIE_BUTTON, this);
	m_btnLie.SetBitmap(IDB_MB_BITMAP_LIE);

	m_DIBStaticCtrl.SubclassDlgItem(IDC_MB_PREVIEW, this);

	DWORD dwStyle = m_listItem.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_listItem.SetExtendedStyle(dwStyle);

	LoadFromFile();
	// Setup the column headings
	InitListCtrlCols();

	// Create the image list that is attached to the list control
	InitImageList();

	// Insert the default dummy items
	InsertItems();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
/*
	InitImageList

	Create the image list that is associated with the list control.  Then 
	attach the list of images to the control so that we can add items with
	images.
	
	Params
		None

	Returns 
		BOOL	Image list created and attached?
*/
/////////////////////////////////////////////////////////////////////////////
BOOL CMBTemplatePage0::InitImageList()
{
	// Create 256 color image lists
	HIMAGELIST hList = ImageList_Create(32,32, ILC_COLOR8 |ILC_MASK , 8, 1);
	m_cImageListNormal.Attach(hList);

	hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_cImageListSmall.Attach(hList);


	// Load the large icons
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_MB_IMAGES_NORMAL);
	m_cImageListNormal.Add(&cBmp, RGB(255,0, 255));
	cBmp.DeleteObject();

	// Load the small icons
	cBmp.LoadBitmap(IDB_MB_IMAGES_SMALL);
	m_cImageListSmall.Add(&cBmp, RGB(255,0, 255));

	// Attach them
	m_listItem.SetImageList(&m_cImageListNormal, LVSIL_NORMAL);
	m_listItem.SetImageList(&m_cImageListSmall, LVSIL_SMALL);

	return TRUE;

}

CString FOGetFileName(const CString& PathAndFileName)
{
	CString FileName = PathAndFileName;
	
	int nIndex = FileName.ReverseFind(_T('\\'));
	int nIndex2 = FileName.ReverseFind(_T('/'));
	if(nIndex2 > nIndex) nIndex = nIndex2;
	if(nIndex >= 0)
	{
		FileName = FileName.Right(FileName.GetLength() - nIndex - 1);
	}
	
	return FileName;
}

CString FOGetExtension(const CString& PathAndFileName)
{
	CString FileName = FOGetFileName(PathAndFileName);
	int nIndex = FileName.ReverseFind(_T('.'));
	CString strExt;
	
	if (nIndex >= 0 && nIndex < (FileName.GetLength() - 1))
		strExt = FileName.Right(FileName.GetLength() - nIndex - 1);
	else
		strExt.Empty();
	
	return strExt;
}

CString FOGetBaseFileName(const CString& PathAndFileName)
{
	CString FileName = FOGetFileName(PathAndFileName);
	CString Ext = FOGetExtension(FileName);
	
	if (FileName.Find(_T('.')) != -1)
		return FileName.Left(FileName.GetLength() - Ext.GetLength() - 1);
	else
		return FileName;
}

void CMBTemplatePage0::InsertItems()
{
	// Delete the current contents
	m_listItem.DeleteAllItems();
	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;
	CString strItem;
	int i =0;
	POSITION pos = m_Components.GetHeadPosition();
	while(pos != NULL)
	{
		CMBTemplateFileObj *pObj = (CMBTemplateFileObj *)m_Components.GetNext(pos);
		lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
		strItem.Format(_T("%s"),FOGetBaseFileName(pObj->strFileName));
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		lvi.iImage = 2;		// There are 8 images in the image list
		m_listItem.InsertItem(&lvi);

		strItem.Format(_T("%s"),pObj->strDescri);
		// Set subitem 1
		lvi.iSubItem =1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		m_listItem.SetItem(&lvi);
		m_listItem.SetItemData(i,(DWORD)pObj);
		i++;
		
	}
}

void CMBTemplatePage0::InitListCtrlCols()
{
	// Insert some columns
	CRect rect;
	m_listItem.GetClientRect(&rect);
	int nColInterval = rect.Width()/3;

	m_listItem.InsertColumn(0, _T("Template Name"), LVCFMT_LEFT, nColInterval);
	m_listItem.InsertColumn(1, _T("Description"), LVCFMT_LEFT, nColInterval*2);

}

void CMBTemplatePage0::OnClickMbList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;
	// TODO: Add your control notification handler code here
	int iSelIndex = m_listItem.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strOtherFile;
	strOtherFile = strPathX+"\\Template\\";
	if (iSelIndex == -1)
	{
		return;
	}
	CMBTemplateFileObj *pObj = (CMBTemplateFileObj *)m_listItem.GetItemData(iSelIndex);
	if(pObj != NULL)
	{
		m_DIBStaticCtrl.RemoveDib();
		CString strBaseName = FOGetBaseFileName(pObj->strFileName);
		CString strImage = strOtherFile +strBaseName +".bmp";
		m_DIBStaticCtrl.LoadDib(strImage);
		GetDlgItem(IDC_MB_MSG)->SetWindowText(pObj->strDescri);
	}
	*pResult = 0;
}

void CMBTemplatePage0::OnDblclkMbList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;
	// TODO: Add your control notification handler code here
	int iSelIndex = m_listItem.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strOtherFile;
	strOtherFile = strPathX+"\\Template\\";
	if (iSelIndex == -1)
	{
		return;
	}
	CMBTemplateFileObj *pObj = (CMBTemplateFileObj *)m_listItem.GetItemData(iSelIndex);
	if(pObj != NULL)
	{
		m_DIBStaticCtrl.RemoveDib();
		CString strBaseName = FOGetBaseFileName(pObj->strFileName);
		CString strImage = strOtherFile +strBaseName +".bmp";
		m_DIBStaticCtrl.LoadDib(strImage);
		GetDlgItem(IDC_MB_MSG)->SetWindowText(pObj->strDescri);
	}
	*pResult = 0;
}

void CMBTemplatePage0::OnMbMaxButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listItem.SetRedraw(FALSE);
	m_DIBStaticCtrl.RemoveDib();
	// Remove whatever style is there currently
	m_listItem.ModifyStyle(LVS_ICON | LVS_LIST | LVS_REPORT | LVS_SMALLICON ,0);
	m_listItem.ModifyStyle(0, LVS_ICON);
	// Fill the list control
	InsertItems();

	m_listItem.SetRedraw(TRUE);
}

void CMBTemplatePage0::OnMbMinButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listItem.SetRedraw(FALSE);
	m_DIBStaticCtrl.RemoveDib();
	// Remove whatever style is there currently
	m_listItem.ModifyStyle(LVS_ICON | LVS_LIST | LVS_REPORT | LVS_SMALLICON ,0);
	m_listItem.ModifyStyle(0, LVS_LIST);
	// Fill the list control
	InsertItems();

	m_listItem.SetRedraw(TRUE);
}

void CMBTemplatePage0::OnMbLieButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listItem.SetRedraw(FALSE);
	m_DIBStaticCtrl.RemoveDib();
	// Remove whatever style is there currently
	m_listItem.ModifyStyle(LVS_ICON | LVS_LIST | LVS_REPORT | LVS_SMALLICON ,0);
	m_listItem.ModifyStyle(0, LVS_REPORT);
	// Fill the list control
	InsertItems();

	m_listItem.SetRedraw(TRUE);
}

void CMBTemplatePage0::OnDestroy() 
{
	POSITION pos = m_Components.GetHeadPosition();
	while(pos != NULL)
		delete m_Components.GetNext(pos);
	m_Components.RemoveAll();
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	
}

CMBTemplateFileObj *CMBTemplatePage0::FindObjByID(int nIndex)
{
	POSITION pos = m_Components.GetHeadPosition();
	while(pos != NULL)
	{
		CMBTemplateFileObj *pObj = (CMBTemplateFileObj *)m_Components.GetNext(pos);
		if(pObj->nID == nIndex)
		{
			return pObj;
		}
	}
	return NULL;
}

BOOL CMBTemplatePage0::OnQueryNewPalette() 
{
	m_DIBStaticCtrl.SendMessage(WM_QUERYNEWPALETTE);	// redo the palette if necessary
	return CDialog::OnQueryNewPalette();
}

void CMBTemplatePage0::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	m_DIBStaticCtrl.SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->GetSafeHwnd());	// redo the palette if necessary
}

BOOL CMBTemplatePage0::GetValue()
{
	UpdateData();
	int iSelIndex = m_listItem.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
	
	if (iSelIndex == -1)
	{
		AfxMessageBox(_T("Please select a template at first!"),MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	CMBTemplateFileObj *pObj = (CMBTemplateFileObj *)m_listItem.GetItemData(iSelIndex);
	if(pObj != NULL)
	{
		strTemplateFile = pObj->strFileName;
		strTemplateFolder = pObj->strSubFolder;
		if(strTemplateFile.IsEmpty())
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CMBTemplatePage0::LoadFromFile()
{
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strOtherFile;
	strOtherFile = strPathX+"\\Template\\Template.dat";
	CStdioFile m_File;
	if(m_File.Open(strOtherFile,CFile::modeRead | CFile::typeText))
	{
		CString strTemp;
		int nNumber = 100;
		while (m_File.ReadString(strTemp))
		{
			
			strTemp.TrimLeft();
			strTemp.TrimRight();
			if(!strTemp.IsEmpty())
			{
				CString strDescri;
				CString strFile;
				CString strFolder;
				strFile = strTemp.Left(strTemp.ReverseFind('#'));
				strDescri = strTemp.Right(strTemp.GetLength() - strFile.GetLength() -1);
				strTemp = strDescri;
				strFolder = strTemp.Left(strTemp.ReverseFind('@'));
				strDescri = strTemp.Right(strTemp.GetLength() - strFolder.GetLength() -1);
				if((!strFolder.IsEmpty()) && (!strFile.IsEmpty()))
				{
					CMBTemplateFileObj *pObj = new CMBTemplateFileObj;
					pObj->strDescri = strDescri;
					pObj->strFileName = strFile;
					pObj->strSubFolder = strFolder;
					pObj->nID = nNumber;
					m_Components.AddTail(pObj);
					nNumber ++;
				}
			}	
		}
		m_File.Close();
	}
}


void CMBTemplatePage0::OnRclickMbList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	pNMHDR;
	int iSelIndex = m_listItem.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strOtherFile;
	strOtherFile = strPathX+"\\Template\\";
	if (iSelIndex == -1)
	{
		return;
	}
	CMBTemplateFileObj *pObj = (CMBTemplateFileObj *)m_listItem.GetItemData(iSelIndex);
	if(pObj != NULL)
	{
		m_DIBStaticCtrl.RemoveDib();
		CString strBaseName = FOGetBaseFileName(pObj->strFileName);
		CString strImage = strOtherFile +strBaseName +".bmp";
		m_DIBStaticCtrl.LoadDib(strImage);
		GetDlgItem(IDC_MB_MSG)->SetWindowText(pObj->strDescri);
	}
	*pResult = 0;
}
