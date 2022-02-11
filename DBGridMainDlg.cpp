// DBGridMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "DBGridMainDlg.h"
#include "DBSubDlg.h"
#include "DBSubConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBGridMainDlg dialog


CDBGridMainDlg::CDBGridMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBGridMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBGridMainDlg)
	m_nGridType = 0;
	m_bHorzGrid = FALSE;
	m_bVertGrid = FALSE;
	m_nStart = 0;
	m_nTotal = 0;
	//}}AFX_DATA_INIT
	bToolBox = FALSE;
	strSql = _T("");
	m_crValue = RGB(192,192,192);
	m_crGrid = RGB(0,0,0);
	strSubLink = _T("");
}


CDBGridMainDlg::~CDBGridMainDlg()
{
	gfxData.FreeObjectCache();
	m_DBFileds.RemoveAll();
}

void CDBGridMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBGridMainDlg)
	DDX_Control(pDX, IDC_WORKSPACELIST, m_ctrlListWorkspaces);
	DDX_Control(pDX, IDC_MOVE_UP, m_ButtonUp);
	DDX_Control(pDX, IDC_MOVE_DOWN, m_ButtonDown);
	DDX_Control(pDX, IDC_REMOVE_PROJECT, m_ButtonRemove);
	DDX_Control(pDX, IDC_BUTTON_REMOVEALL, m_ButtonRemoveAll);
	DDX_Control(pDX, IDC_ADD_PROJECT, m_ButtonProject);
	DDX_Radio(pDX, IDC_RADIO_GRID_SOLID, m_nGridType);
	DDX_Check(pDX, IDC_CHECK_HORZ, m_bHorzGrid);
	DDX_Check(pDX, IDC_CHECK_VERT, m_bVertGrid);
	DDX_Text(pDX, IDC_EDIT_START, m_nStart);
	DDV_MinMaxInt(pDX, m_nStart, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_nTotal);
	DDV_MinMaxInt(pDX, m_nTotal, -1, 1000);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_wndColor);
	DDX_ColorDropDown(pDX, IDC_BUTTON_COLOR, m_crValue);

	DDX_Control(pDX, IDC_BUTTON_GRID_COLOR, m_wndGrid);
	DDX_ColorDropDown(pDX, IDC_BUTTON_GRID_COLOR, m_crGrid);
}


BEGIN_MESSAGE_MAP(CDBGridMainDlg, CDialog)
	//{{AFX_MSG_MAP(CDBGridMainDlg)
	ON_BN_CLICKED(IDC_ADD_PROJECT, OnAddProject)
	ON_BN_CLICKED(IDC_REMOVE_PROJECT, OnRemoveProject)
	ON_BN_CLICKED(IDC_MOVE_UP, OnMoveUp)
	ON_BN_CLICKED(IDC_MOVE_DOWN, OnMoveDown)
	ON_WM_GETMINMAXINFO	()
	ON_NOTIFY(NM_DBLCLK, IDC_WORKSPACELIST, OnDblclkWorkspacelist)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, OnButtonRemoveall)
	ON_BN_CLICKED(IDC_BUTTON_DB, OnButtonDb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBGridMainDlg message handlers

void CDBGridMainDlg::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI ) 
{
	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 280;
	
	//
	//	CALL BASE CLASS' IMPLEMENTATION
	//
	CDialog ::OnGetMinMaxInfo(lpMMI);
}

BOOL CDBGridMainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_wndColor.GetDrawImpl().SetHeaderBarState(FOPDrawControlPanel::NoHeaderBar);

	m_wndGrid.GetDrawImpl().SetHeaderBarState(FOPDrawControlPanel::NoHeaderBar);

	// TODO: Add extra initialization here
	HICON hIcon = ::AfxGetApp()->LoadIcon( IDR_UCCPRITYPE );
	m_ButtonUp.SetBitmap(IDB_MB_BITMAP_MOVE_UP);
	m_ButtonUp.SetBtnCursor(IDC_FO_HAND);
	m_ButtonDown.SetBitmap(IDB_MB_BITMAP_MOVE_DOWN);
	m_ButtonDown.SetBtnCursor(IDC_FO_HAND);
	
	m_ButtonRemove.SetBitmap(IDB_MB_BITMAP_REMOVE);
	m_ButtonRemove.SetBtnCursor(IDC_FO_HAND);
	m_ButtonRemoveAll.SetBitmap(IDB_MB_BITMAP_REMOVE);
	m_ButtonRemoveAll.SetBtnCursor(IDC_FO_HAND);
	
	m_ButtonProject.SetBitmap(IDB_MB_BITMAP_NEW_CHART);
	m_ButtonProject.SetBtnCursor(IDC_FO_HAND);

	GetDlgItem(IDC_BUTTON_DB)->SetFont(&gfxData.fontBold);

	this->m_ImageList.Create(16, 16, ILC_COLOR, 1, 1);
	this->m_ImageList.SetBkColor(::GetSysColor(COLOR_WINDOW));
	this->m_ImageList.Add(hIcon);

	if(!bToolBox)
	{
//		GetDlgItem(IDC_EDIT_STATE_TEXT)->EnableWindow(FALSE);
	}
	//
	//	ATTACH IMAGE LIST OT LIST CONTROL
	//
	this->m_ctrlListWorkspaces.SetImageList(&m_ImageList, LVSIL_SMALL);

	//
	//	SETUP LIST CONTROL'S COLUMNS
	//
	CString strHeader;
	int		iColumn	= 0 ;
	
	{
		strHeader = _T("Colume Name");
		this->m_ctrlListWorkspaces.InsertColumn( iColumn, strHeader, LVCFMT_LEFT, 100, iColumn );

		iColumn ++;
		strHeader = _T("DB Field Name");
		this->m_ctrlListWorkspaces.InsertColumn( iColumn, strHeader, LVCFMT_LEFT, 280, iColumn );
	}
	
	//
	//	MODIFY STYLE
	//
	this->m_ctrlListWorkspaces.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	
	//
	//	LOAD PROFILE
	//
	this->LoadProfile();
	int nCount = m_ctrlListWorkspaces.GetItemCount();
	if(nCount > 0)
		m_ctrlListWorkspaces.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);

	//
	//	SET THE FOCUS TO THE LIST CONTROL (neccessary in order to have the control re-display its selection)
	//
	this->m_ctrlListWorkspaces.SetFocus();

	if(!strSql.IsEmpty() && !theApp.m_strDsn.IsEmpty())
	{
		CWaitCursor myWaitCursor;
		CFOPODBCDataSource	m_odbc;
		if(FOP_SUCCESS != m_odbc.Open(theApp.m_strDsn, strSql, 0, 0, 0, NULL, NULL))
		{
			return TRUE;
		}
		
		m_DBFileds.RemoveAll();
		int nTotal = m_odbc.GetNumCols();
		int x= 0;
		for(x= 0; x < nTotal; x++)
		{
			CString strCol;
			m_odbc.GetColName(x, &strCol);
			m_DBFileds.Add(strCol);
		}
		

	}

	if(m_DBFileds.GetSize() <= 0)
	{
		GetDlgItem(IDC_ADD_PROJECT)->EnableWindow(FALSE);
	}
	
//	OnButtonGen();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBGridMainDlg::LoadProfile()
{
	//
	//	RESET LIST
	//
	this->m_ctrlListWorkspaces.DeleteAllItems();

	//
	//	READ PROJECTS
	//
	for ( int x = 0; x < arStates->GetSize(); x++ )
	{
		FODB_COLS state = arStates->GetAt(x);
		//
		//	ADD PROJECT
		//
		this->AddProject( state.strTitle, state.strDBFiled);
	}
}

void CDBGridMainDlg::AddProject( const CString&	nState, const CString&	strState)
{
	CString strTT;
	strTT = nState;
	//
	//	INSET ITEM
	//
	int iItem		= m_ctrlListWorkspaces.InsertItem(m_ctrlListWorkspaces.GetItemCount(), strTT );
	
	this->m_ctrlListWorkspaces.SetItemText(iItem, 1,strState );
}

void CDBGridMainDlg::OnAddProject() 
{
	// TODO: Add your control notification handler code here
	CDBSubDlg dlg;
	dlg.m_DBFileds = &m_DBFileds;
	if(dlg.DoModal() == IDOK)
	{
		AddProject(dlg.m_strTitle, dlg.m_strField);
//		OnButtonGen();
	}
	
}

void CDBGridMainDlg::OnRemoveProject() 
{
	// TODO: Add your control notification handler code here
	//
	//	SINCE WE GET ITEMS IN RANDOM ORDER WE HAVE TO RECURSE UNTIL NO MORE ITEM IS SELECTED
	//
	
	
	POSITION pos = this->m_ctrlListWorkspaces.GetFirstSelectedItemPosition();
	
	if ( NULL != pos )
	{
		//
		//	GET NEXT SELECTED ITEM'S INDEX
		//
		int iItem = this->m_ctrlListWorkspaces.GetNextSelectedItem( pos );
//		if(AfxMessageBox(ID_HMI_MSG22, MB_ICONINFORMATION | MB_YESNO) == IDYES)
		{
			//
			//	REMOVE THAT ITEM
			//
			this->m_ctrlListWorkspaces.DeleteItem( iItem );
			
			//
			//	RECURSE
			//
//			this->OnRemoveProject();
		}
	}
//	OnButtonGen();
}

void CDBGridMainDlg::OnMoveUp() 
{
	//
	//	SETUP VARS
	//
	int	iPredecessor = 0;
	int	iItem		 = 0;

	//
	//	ENUMERATE SELECTED ITEMS
	//
	POSITION pos = this->m_ctrlListWorkspaces.GetFirstSelectedItemPosition();

	while ( NULL != pos )
	{
		//
		//	GET NEXT SELECTED ITEM'S INDEX
		//
		iItem = this->m_ctrlListWorkspaces.GetNextSelectedItem( pos );

		//
		//	CHECK WHETHER WE CAN MOVE THAT ITEM
		//
		if ( iItem > iPredecessor )
		{
			//
			//	MOVE THAT ITEM
			//
			this->MoveItem( iItem, iItem - 1 );

			//
			//	KEEP ANY FOLLOWING ITEM FROM REPLACING THIS ITEM
			//
			iPredecessor = iItem;
		}
		else
		{
			//
			//	THIS ITEM COULD NOT BE MOVED
			//
			++iPredecessor;
		}
	}

	//
	//	ENSURE THAT OUR SELECTION IS VISIBLE
	//
	pos = this->m_ctrlListWorkspaces.GetFirstSelectedItemPosition();

	if ( NULL != pos )
	{
		//
		//	GET FIRST SELECTED ITEM'S POSITION
		//
		iItem = this->m_ctrlListWorkspaces.GetNextSelectedItem( pos );

		//
		//	ENSURE THAT ITEMS's VISIBILITY
		//
		this->m_ctrlListWorkspaces.EnsureVisible( iItem, FALSE );
	}

	//
	//	SET THE FOCUS BACK TO THE LIST CONTROL (neccessary in order to have the control re-display its selection)
	//
	this->m_ctrlListWorkspaces.SetFocus();

//	OnButtonGen();
}

void CDBGridMainDlg::OnMoveDown() 
{
	//
	//	GATHER SELECTED INDICES (for we must process them in reverse order)
	//
	CArray< int, int >	arrSelected	;
	POSITION			pos			= this->m_ctrlListWorkspaces.GetFirstSelectedItemPosition();

	if ( NULL == pos )
	{
		return;	// avoid messing around with GetUpperBound()
	}

	while ( NULL != pos )
	{
		//
		//	GET NEXT SELECTED ITEM'S INDEX
		//
		arrSelected.Add( this->m_ctrlListWorkspaces.GetNextSelectedItem( pos ) );
	}

	//
	//	NOW, PROCESS THE ITEMS
	//
	int iSuccessor  = this->m_ctrlListWorkspaces.GetItemCount() - 1;
	int iItem		= iSuccessor;
	int iSelected	= 0;

	for ( iSelected = arrSelected.GetUpperBound(); iSelected >= 0; iSelected-- )
	{
		//
		//	GET ITEM INDEX
		//
		iItem = arrSelected[ iSelected ];

		//
		//	CHECK WHETHER WE CAN MOVE THE ITEM
		//
		if ( iItem < iSuccessor )
		{
			//
			//	MOVE THAT ITEM
			//
			this->MoveItem( iItem, iItem + 1 );

			//
			//	PREVENT THAT ITEM FROM BEING OVERRIDEEN
			//
			iSuccessor = iItem;
		}
		else
		{
			//
			//	COULD NOT MOVE THAT ITEM
			//
			--iSuccessor;
		}
	}

	//
	//	ENSURE THAT OUR SELECTION IS VISIBLE
	//
	pos	= this->m_ctrlListWorkspaces.GetFirstSelectedItemPosition();

	while ( NULL != pos )
	{
		//
		//	GET LAST SELECTED ITEM'S POSITION
		//
		iItem = this->m_ctrlListWorkspaces.GetNextSelectedItem( pos );
	}

	//
	//	ENSURE THAT ITEMS's VISIBILITY
	//
	this->m_ctrlListWorkspaces.EnsureVisible( iItem, FALSE );

	//
	//	SET THE FOCUS BACK TO THE LIST CONTROL (neccessary in order to have the control re-display its selection)
	//
	this->m_ctrlListWorkspaces.SetFocus();

//	OnButtonGen();
}

void CDBGridMainDlg::MoveItem( int a_iSrc, int a_iDst )
{
	//
	//	CHECK VALIDITY
	//
	if ( a_iSrc <  0										 )	return;
	if ( a_iDst <  0										 )	return;
	if ( a_iSrc >= this->m_ctrlListWorkspaces.GetItemCount() )	return;
	if ( a_iDst >= this->m_ctrlListWorkspaces.GetItemCount() )	return;
	
	//
	//	SETUP VARS
	//
	CString	strSwap	 ;
	CString	strTemp	 ;
	int		iSubItem = 1;
	
	//
	//	SWAP TEXTs
	//
	{
		//
		//	STORE DESTINATION IN SWAP MEM
		//
		strSwap = this->m_ctrlListWorkspaces.GetItemText( a_iDst, iSubItem );
		
		//
		//	COPY SOURCE TO DESTINATION
		//
		strTemp = this->m_ctrlListWorkspaces.GetItemText( a_iSrc, iSubItem );
		this->m_ctrlListWorkspaces.SetItemText( a_iDst, iSubItem, strTemp);
		
		strTemp.ReleaseBuffer();
		
		//
		//	COPY SWAP TO SOURCE
		//
		this->m_ctrlListWorkspaces.SetItemText( a_iSrc, iSubItem, strSwap);
		
		strSwap.ReleaseBuffer();
	}
	
	//
	//	SWAP ITEM STATES
	//
	UINT uiSrc = this->m_ctrlListWorkspaces.GetItemState( a_iSrc, (UINT) -1 );
	UINT uiDst = this->m_ctrlListWorkspaces.GetItemState( a_iDst, (UINT) -1 );
	
	this->m_ctrlListWorkspaces.SetItemState( a_iSrc, uiDst, (UINT) -1 );
	this->m_ctrlListWorkspaces.SetItemState( a_iDst, uiSrc, (UINT) -1 );
}

void CDBGridMainDlg::GetAllIndex(CStringArray &m_Array)
{
	int		iProjects			= this->m_ctrlListWorkspaces.GetItemCount();
	for ( int x = 0; x < iProjects; x++ )
	{
		CString strIndex;
		strIndex = this->m_ctrlListWorkspaces.GetItemText( x, 0);

		if(!strIndex.IsEmpty())
		{
			m_Array.Add(strIndex);
		}
		

	}
}

CString CDBGridMainDlg::GenerateStateText()
{
	arStates->RemoveAll();
	int		iProjects			= this->m_ctrlListWorkspaces.GetItemCount();
	for ( int x = 0; x < iProjects; x++ )
	{
		CString strIndex;
		strIndex = this->m_ctrlListWorkspaces.GetItemText( x, 0);

		CString strState;
		strState = this->m_ctrlListWorkspaces.GetItemText( x, 1);
		
		
		FODB_COLS db;
		db.strTitle = strIndex;
		db.strDBFiled = strState;

		arStates->Add(db);
		
	}

	CString strReturn = _T("");
	return strReturn;
}

void CDBGridMainDlg::OnDblclkWorkspacelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;
	// TODO: Add your control notification handler code here
	int nItemIndex = -1;
	// if there's an element selected in the listbox
	if ( (m_ctrlListWorkspaces. GetNextItem ( -1, LVNI_SELECTED ) ) != -1 ) 
	{
		while ( ( nItemIndex = m_ctrlListWorkspaces.GetNextItem ( nItemIndex, LVNI_SELECTED ) ) != -1 )
		{
			CString strIndex;
			strIndex = this->m_ctrlListWorkspaces.GetItemText( nItemIndex, 0);

			CString strState;
			strState = this->m_ctrlListWorkspaces.GetItemText( nItemIndex, 1);

			{
				{
					CDBSubDlg dlg;
					dlg.m_DBFileds = &m_DBFileds;
					dlg.m_strTitle = strIndex;
					dlg.m_strField = strState;
					if(dlg.DoModal() == IDOK)
					{
		
						this->m_ctrlListWorkspaces.SetItemText( nItemIndex, 0, dlg.m_strTitle);
						this->m_ctrlListWorkspaces.SetItemText( nItemIndex, 1, dlg.m_strField);
					}
				}
			}
		}
//		OnButtonGen();
	}
	*pResult = 0;
}

void CDBGridMainDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	GenerateStateText();
	CDialog::OnOK();
}

void CDBGridMainDlg::OnButtonRemoveall() 
{
	// TODO: Add your control notification handler code here
//	if(AfxMessageBox(ID_HMI_MSG23, MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		//
		//	LOAD PROFILE
		//
		this->m_ctrlListWorkspaces.DeleteAllItems();
		
//		GetDlgItem(IDC_EDIT_STATE_TEXT)->SetWindowText(m_strState);
//		OnButtonGen();
	}
}

void CDBGridMainDlg::OnButtonDb() 
{
	// TODO: Add your control notification handler code here
	CDBSubConnectDlg dlg;
	dlg.m_strSQL = strSql;
	dlg.strSub = strSubLink;
	CFOPODBCDataSource	m_odbc;
	dlg.m_pOdbc = &m_odbc;
	if(IDCANCEL == dlg.DoModal())
		return;
	
	if(strSql != dlg.m_strSQL)
	{
		OnButtonRemoveall();

		strSql = dlg.m_strSQL;
		strSubLink = dlg.strSub;
		CWaitCursor myWaitCursor;
		
		if(FOP_SUCCESS != m_odbc.Open(theApp.m_strDsn, dlg.m_strSQL, 0, dlg.m_nOpenType, 0, NULL, NULL))
			return;
		
		m_DBFileds.RemoveAll();
		int nTotal = m_odbc.GetNumCols();
		int x= 0;
		for(x= 0; x < nTotal; x++)
		{
			CString strCol;
			m_odbc.GetColName(x, &strCol);
			m_DBFileds.Add(strCol);
			AddProject(strCol, strCol);
		}
	}

	if(m_DBFileds.GetSize() <= 0)
	{
		GetDlgItem(IDC_ADD_PROJECT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_ADD_PROJECT)->EnableWindow(TRUE);
	}
}
