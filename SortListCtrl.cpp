#include "stdafx.h"
#include "SortListCtrl.h"
#include "UCCPrintDoc.h"
#include "UCCPrintView.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");


struct ItemData
{
public:
	ItemData() : arrpsz( NULL ), dwData( NULL ) {}
	
	LPTSTR* arrpsz;
	DWORD dwData;
	
private:
	// ban copying.
	ItemData( const ItemData& );
	ItemData& operator=( const ItemData& );
};


CSortListCtrl::CSortListCtrl()
{
}


CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CFOBaseGridListCtrl)
//{{AFX_MSG_MAP(CSortListCtrl)
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
ON_NOTIFY_REFLECT(NM_CLICK, OnDblclkList1)
ON_WM_MEASUREITEM_REFLECT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrl message handlers

void CSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	pNMHDR;
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	const int iColumn = pNMListView->iSubItem;
	
	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
//	Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );
	
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	if(pParent->IsWindowVisible())
	{
		CUCCPrintView *pView = (CUCCPrintView *)FOGetActiveView();
		if(pParent->m_wndTableBar.m_TreeCtrl.GetItemCount() <= 0)
		{
			if(pView != NULL)
			{
				pParent->m_wndTableBar.InitShapes(pView->GetCurrentModel());
			}
		}
		
	}

	*pResult = 0;
}

void CSortListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	LOGFONT lf;
	GetFont()->GetLogFont( &lf );
	
	CClientDC cdc(this);
	TEXTMETRIC tm;
	cdc.GetTextMetrics(&tm);
	
	if( lf.lfHeight < 0 )
	{
		lpMeasureItemStruct->itemHeight = tm.tmHeight+40;
	}
	else
	{
		lpMeasureItemStruct->itemHeight = tm.tmHeight+40;
	}
	
	//CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSortListCtrl::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW*   pNMListView   =   (NM_LISTVIEW*)pNMHDR;  
	
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	
	if (pNMListView->iItem != -1)   
	{   
		// 		CString str;
		// 		str.Format(_T("%d"), pNMListView->iItem);
		// 		AfxMessageBox(str);
//		m_pCurRecord = (CFoRecordInfo*)m_ctrlList.GetItemData(pNMListView->iItem);
		CFODrawShape *pData = (CFODrawShape*)GetItemData(pNMListView->iItem);
		
		CUCCPrintView *pView = (CUCCPrintView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->SelectNewShape(pData);
			pView->SetLogCenter(pData->GetSnapRect().CenterPoint());
		}
	}
	else
	{
		if(pParent->IsWindowVisible())
		{
			CUCCPrintView *pView = (CUCCPrintView *)FOGetActiveView();
			if(pParent->m_wndTableBar.m_TreeCtrl.GetItemCount() <= 0)
			{
				if(pView != NULL)
				{
					pParent->m_wndTableBar.InitShapes(pView->GetCurrentModel());
				}
			}
			
		}
		
//		m_pCurRecord = NULL;;
	}
	
	*pResult = 0;

}

CNewDBSortListCtrl::CNewDBSortListCtrl()
: m_iNumColumns( 0 )
, m_iSortColumn( -1 )
, m_bSortAscending( TRUE )
{
}


CNewDBSortListCtrl::~CNewDBSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CNewDBSortListCtrl, CListCtrl)
//{{AFX_MSG_MAP(CNewDBSortListCtrl)
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDBSortListCtrl message handlers

#undef SubclassWindow
void CNewDBSortListCtrl::PreSubclassWindow()
{
	// the list control must have the report style.
	ASSERT( GetStyle() & LVS_REPORT );
	
	CListCtrl::PreSubclassWindow();
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
}


BOOL CNewDBSortListCtrl::SetHeadings( UINT uiStringID )
{
	CString strHeadings;
	VERIFY( strHeadings.LoadString( uiStringID ) );
	return SetHeadings( strHeadings );
}


// the heading text is in the format column 1 text,column 1 width;column 2 text,column 3 width;etc.
BOOL CNewDBSortListCtrl::SetHeadings( const CString& strHeadings )
{
	int iStart = 0;
	
	for( ;; )
	{
		const int iComma = strHeadings.Find( _T(','), iStart );
		
		if( iComma == -1 )
			break;
		
		const CString strHeading = strHeadings.Mid( iStart, iComma - iStart );
		
		iStart = iComma + 1;
		
		int iSemiColon = strHeadings.Find( _T(';'), iStart );
		
		if( iSemiColon == -1 )
			iSemiColon = strHeadings.GetLength();
		
		const int iWidth = atoi( strHeadings.Mid( iStart, iSemiColon - iStart ) );
		
		iStart = iSemiColon + 1;
		
		if( InsertColumn( m_iNumColumns++, strHeading, LVCFMT_LEFT, iWidth ) == -1 )
			return FALSE;
	}
	
	return TRUE;
}

BOOL CNewDBSortListCtrl::SetHeadings(CStringArray &arrString)
{	
	CString strHeading = _T("");
	for (int i=0; i<arrString.GetSize(); i++)
	{
		strHeading = arrString.GetAt(i);
		
		if (InsertColumn( m_iNumColumns++, strHeading, LVCFMT_LEFT, 80) == -1 )
			return FALSE;
	}
	
	return TRUE;
}

int CNewDBSortListCtrl::AddItem( LPCTSTR pszText, ... )
{
	const int iIndex = InsertItem( GetItemCount(), pszText );
	
	LPTSTR* arrpsz = new LPTSTR[ m_iNumColumns ];
	arrpsz[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	(void)lstrcpy( arrpsz[ 0 ], pszText );
	
	va_list list;
	va_start( list, pszText );
	
	for( int iColumn = 1; iColumn < m_iNumColumns; iColumn++ )
	{
		pszText = va_arg( list, LPCTSTR );
		ASSERT_VALID_STRING( pszText );
		VERIFY( CListCtrl::SetItem( iIndex, iColumn, LVIF_TEXT, pszText, 0, 0, 0, 0 ) );
		
		arrpsz[ iColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		(void)lstrcpy( arrpsz[ iColumn ], pszText );
	}
	
	va_end( list );
	
	VERIFY( SetTextArray( iIndex, arrpsz ) );
	
	return iIndex;
}

int CNewDBSortListCtrl::AddItem(CStringArray &arrString)
{
	if (arrString.GetSize()<m_iNumColumns)
		return 0;
	
	CString strTemp = arrString.GetAt(0);
	const int iIndex = InsertItem( GetItemCount(), strTemp);
	
	LPTSTR* arrpsz = new LPTSTR[ m_iNumColumns ];
	arrpsz[0] = new TCHAR[lstrlen(strTemp.GetBuffer(strTemp.GetLength())) + 1];
	strTemp.ReleaseBuffer();
	(void)lstrcpy( arrpsz[0], strTemp.GetBuffer(strTemp.GetLength()));
	strTemp.ReleaseBuffer();
	
	for( int iColumn = 1; iColumn < m_iNumColumns; iColumn++ )
	{
		strTemp = arrString.GetAt(iColumn);
		VERIFY(CListCtrl::SetItem( iIndex, iColumn, LVIF_TEXT, arrString.GetAt(iColumn), 0, 0, 0, 0 ) );
		
		arrpsz[iColumn] = new TCHAR[lstrlen(strTemp.GetBuffer(strTemp.GetLength())) + 1];
		strTemp.ReleaseBuffer();
		(void)lstrcpy(arrpsz[iColumn], strTemp.GetBuffer(strTemp.GetLength()));
		strTemp.ReleaseBuffer();
	}
	
	VERIFY( SetTextArray( iIndex, arrpsz ) );
	
	return iIndex;
}

void CNewDBSortListCtrl::FreeItemMemory( const int iItem )
{
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( iItem ) );
	
	LPTSTR* arrpsz = pid->arrpsz;
	
	for( int i = 0; i < m_iNumColumns; i++ )
		delete[] arrpsz[ i ];
	
	delete[] arrpsz;
	delete pid;
	
	VERIFY( CListCtrl::SetItemData( iItem, NULL ) );
}


BOOL CNewDBSortListCtrl::DeleteItem( int iItem )
{
	FreeItemMemory( iItem );
	return CListCtrl::DeleteItem( iItem );
}


BOOL CNewDBSortListCtrl::DeleteAllItems()
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeItemMemory( iItem );
	
	return CListCtrl::DeleteAllItems();
}

bool IsNumber( LPCTSTR pszText )
{
	ASSERT_VALID_STRING(pszText);
	int iDotCount=0;
	for(int i=0;i<lstrlen(pszText);i++){
		if(!_istdigit(pszText[i])){
			if(pszText[i]!='.')
				return false;
			iDotCount++;
			if(iDotCount>1)return false;
		}
	}
	return true;
}

int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
{
	ASSERT_VALID_STRING(pszNumber1);
	ASSERT_VALID_STRING(pszNumber2);
	
	const double fNumber1=atof(pszNumber1);
	const double fNumber2=atof(pszNumber2);
	
	if(fNumber1<fNumber2)
		return -1;
	else if(fNumber1>fNumber2)
		return 1;
	return 0;
}

bool IsDate( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );
	
	// format should be 99/99/9999.
	
	if( lstrlen( pszText ) != 10 )
		return false;
	
	return _istdigit(pszText[0])
		&& _istdigit(pszText[1])
		&& pszText[2]==_T('-')
		&& _istdigit( pszText[ 3 ] )
		&& _istdigit( pszText[ 4 ] )
		&& pszText[5]==_T('-')
		&& _istdigit( pszText[ 6 ] )
		&& _istdigit( pszText[ 7 ] )
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}


int DateCompare( const CString& strDate1, const CString& strDate2 )
{
	const int iYear1=atoi(strDate1.Mid(6, 4));
	const int iYear2=atoi(strDate2.Mid(6, 4));
	
	if(iYear1<iYear2)
		return -1;
	else if(iYear1>iYear2)
		return 1;
	
	const int iMonth1=atoi(strDate1.Mid(3, 2));
	const int iMonth2=atoi(strDate2.Mid(3, 2));
	
	if(iMonth1<iMonth2)
		return -1;  
	else if(iMonth1>iMonth2)
		return 1;
	
	const int iDay1=atoi(strDate1.Mid(0, 2));
	const int iDay2=atoi(strDate2.Mid(0, 2));
	
	if(iDay1<iDay2)
		return -1;
	else if(iDay1>iDay2)
		return 1;
	
	return 0;
}


int CALLBACK CNewDBSortListCtrl::CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	CNewDBSortListCtrl* pListCtrl = reinterpret_cast<CNewDBSortListCtrl*>( lParamData );
	ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CListCtrl ) ) );
	
	ItemData* pid1 = reinterpret_cast<ItemData*>( lParam1 );
	ItemData* pid2 = reinterpret_cast<ItemData*>( lParam2 );
	
	ASSERT( pid1 );
	ASSERT( pid2 );
	
	LPCTSTR pszText1 = pid1->arrpsz[ pListCtrl->m_iSortColumn ];
	LPCTSTR pszText2 = pid2->arrpsz[ pListCtrl->m_iSortColumn ];
	
	ASSERT_VALID_STRING( pszText1 );
	ASSERT_VALID_STRING( pszText2 );
	
	if(IsNumber(pszText1))
		return pListCtrl->m_bSortAscending ? NumberCompare( pszText1, pszText2 ) : NumberCompare( pszText2, pszText1 );
	else if(IsDate(pszText1))
		return pListCtrl->m_bSortAscending ? DateCompare( pszText1, pszText2 ) : DateCompare( pszText2, pszText1 );
	else
		// text.
		return pListCtrl->m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
}


void CNewDBSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;
	
	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
	Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );
	
	*pResult = 0;
}


void CNewDBSortListCtrl::Sort( int iColumn, BOOL bAscending )
{
	m_iSortColumn = iColumn;
	m_bSortAscending = bAscending;
	
	// show the appropriate arrow in the header control.
	m_ctlHeader.SetSortArrow( m_iSortColumn, m_bSortAscending );
	
	VERIFY( SortItems( CompareFunction, reinterpret_cast<DWORD>( this ) ) );
}


void CNewDBSortListCtrl::LoadColumnInfo()
{
	// you must call this after setting the column headings.
	ASSERT( m_iNumColumns > 0 );
	
	CString strKey;
	strKey.Format( _T("%d"), GetDlgCtrlID() );
	
	UINT nBytes = 0;
	BYTE* buf = NULL;
	if( AfxGetApp()->GetProfileBinary( g_pszSection, strKey, &buf, &nBytes ) )
	{
		if( nBytes > 0 )
		{
			CMemFile memFile( buf, nBytes );
			CArchive ar( &memFile, CArchive::load );
			m_ctlHeader.Serialize( ar );
			ar.Close();
			
			m_ctlHeader.Invalidate();
		}
		
		delete[] buf;
	}
}


void CNewDBSortListCtrl::SaveColumnInfo()
{
	ASSERT( m_iNumColumns > 0 );
	
	CString strKey;
	strKey.Format( _T("%d"), GetDlgCtrlID() );
	
	CMemFile memFile;
	
	CArchive ar( &memFile, CArchive::store );
	m_ctlHeader.Serialize( ar );
	ar.Close();
	
	DWORD dwLen = memFile.GetLength();
	BYTE* buf = memFile.Detach();	
	
	VERIFY( AfxGetApp()->WriteProfileBinary( g_pszSection, strKey, buf, dwLen ) );
	
	free( buf );
}


void CNewDBSortListCtrl::OnDestroy() 
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeItemMemory( iItem );
	
	CListCtrl::OnDestroy();
}


BOOL CNewDBSortListCtrl::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
	if( !CListCtrl::SetItemText( nItem, nSubItem, lpszText ) )
		return FALSE;
	
	LPTSTR* arrpsz = GetTextArray( nItem );
	LPTSTR pszText = arrpsz[ nSubItem ];
	delete[] pszText;
	pszText = new TCHAR[ lstrlen( lpszText ) + 1 ];
	(void)lstrcpy( pszText, lpszText );
	arrpsz[ nSubItem ] = pszText;
	
	return TRUE;
}


BOOL CNewDBSortListCtrl::SetItemData( int nItem, DWORD dwData )
{
	if( nItem >= GetItemCount() )
		return FALSE;
	
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	pid->dwData = dwData;
	
	return TRUE;
}


DWORD CNewDBSortListCtrl::GetItemData( int nItem ) const
{
	ASSERT( nItem < GetItemCount() );
	
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	return pid->dwData;
}


BOOL CNewDBSortListCtrl::SetTextArray( int iItem, LPTSTR* arrpsz )
{
	ASSERT( CListCtrl::GetItemData( iItem ) == NULL );
	ItemData* pid = new ItemData;
	pid->arrpsz = arrpsz;
	return CListCtrl::SetItemData( iItem, reinterpret_cast<DWORD>( pid ) );
}


LPTSTR* CNewDBSortListCtrl::GetTextArray( int iItem ) const
{
	ASSERT( iItem < GetItemCount() );
	
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( iItem ) );
	return pid->arrpsz;
}
