// TableBar.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "TableBar.h"
#include "UCCPrintDoc.h"
#include "UCCPrintView.h"
#include "NewVisualProxy.h"
#include "MyListItemObj.h"
#include "DbPrintGridShape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl

CMyTabCtrl::CMyTabCtrl()
{
}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CFOTabCtrl)
//{{AFX_MSG_MAP(CMyTabCtrl)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers

/////////////////////////////////////////////////////////////////////////////
// CExtListBar

CDBSortListCtrl::CDBSortListCtrl()
{
}


CDBSortListCtrl::~CDBSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CDBSortListCtrl, CFOBaseGridListCtrl)
//{{AFX_MSG_MAP(CDBSortListCtrl)
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
ON_NOTIFY_REFLECT(NM_CLICK, OnDblclkList1)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBSortListCtrl message handlers

void CDBSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	pNMHDR;
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	const int iColumn = pNMListView->iSubItem;
	
	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
	//	Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );
#if 0
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	if(pParent->IsWindowVisible())
	{
		CEFormDesignerView *pView = (CEFormDesignerView *)FOGetActiveView();
		if(pParent->m_wndTableBar.m_TreeCtrl.GetItemCount() <= 0)
		{
			if(pView != NULL)
			{
				pParent->m_wndTableBar.InitShapes(pView->GetCurrentModel());
			}
		}
		
	}
#endif	
	*pResult = 0;
}


void CDBSortListCtrl::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;

	// TODO: Add your control notification handler code here
	NM_LISTVIEW*   pNMListView   =   (NM_LISTVIEW*)pNMHDR;  
#if 1
	if (pNMListView->iItem != -1)   
	{   
		// 		CString str;
		// 		str.Format(_T("%d"), pNMListView->iItem);
		// 		AfxMessageBox(str);
		//		m_pCurRecord = (CFoRecordInfo*)m_ctrlList.GetItemData(pNMListView->iItem);
		CString strText;
		strText = GetItemText(pNMListView->iItem, 0);
		
		CUCCPrintView *pView = (CUCCPrintView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->DoFillCell(strText);
			
		}
	}

#endif	
	*pResult = 0;
	
}

CFODropSource* CDBSortListCtrl::CreateDropSource()
{
	return new CFODropSource();
}

void CDBSortListCtrl::DoOleDragAndDrop(CFOToolBoxItem* pItem)
{
	ASSERT(pItem != NULL);
	CSharedFile file;
	CArchive ar(&file, CArchive::store);
	ar.Flush();
	pItem->SerializeOleData(ar);
	ar.Close();
	
	// Add our data to the data source under our own custom diagram clipboard
	// data type.
	COleDataSource dataSource;
	dataSource.CacheGlobalData(CFOToolBoxPageWnd::m_cfDragDraw, file.Detach());
	
	// Perform OLE drag and drop
	DROPEFFECT dropEffect = DROPEFFECT_NONE;
	
	CFODropSource* pDropSource = CreateDropSource();
	CRect rClient;//
	GetClientRect(&rClient);
	if(pDropSource != NULL)
	{
		dropEffect = dataSource.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE | DROPEFFECT_SCROLL,
			NULL, pDropSource);
	}
	
	delete pDropSource;
}

void CDBSortListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFOBaseGridListCtrl::OnLButtonDown(nFlags, point);
	// TODO: Add your message handler code here and/or call default
	if( GetFocus() != this )
	{
		SetFocus();
	}

//	ClientToDoc(point);
//	SelectedItem(point);
	
	CFrameWnd *pParent = NULL;
	CWnd *pWnd = (CWnd *)AfxGetMainWnd();
	if(pWnd != NULL)
	{
		if(pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
		{
			pParent = static_cast<CFrameWnd *>(AfxGetMainWnd());
			ASSERT_VALID(pParent);
		}
	}

	if(GetSelectedCount() != 1)
	{
		return;
	}
	int nItemIndex = -1;
	CString strCol;
	// if there's an element selected in the listbox
	if ( ( GetNextItem ( -1, LVNI_SELECTED ) ) != -1 ) 
	{
		while ( ( nItemIndex = GetNextItem ( nItemIndex, LVNI_SELECTED ) ) != -1 )
		{
			strCol = GetItemText(nItemIndex, 0);
			SelectItem(nItemIndex);
		}
	}
	
//	CFOToolBoxItem *pHitItem = (CFOToolBoxItem *)GetSelected();
	if(!strCol.IsEmpty() && (nFlags & MK_LBUTTON))
	{
		BOOL bDragging = FALSE;
		HCURSOR hCur = GetCursor();

		if (::GetCapture() == NULL)
		{
			SetCapture();
			ASSERT(this == GetCapture());
			UpdateWindow();

			AfxLockTempMaps();
			for (;;)
			{
				MSG msg;
				VERIFY(::GetMessage(&msg, NULL, 0, 0));

				if (CWnd::GetCapture() != this)
					break;

				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					{
						CPoint pt(msg.lParam);
						if(!strCol.IsEmpty() && (nFlags & MK_LBUTTON))
						{
						//	if(IsOleSupport())
							{
								if(pParent != NULL)
								{
									CFODrawView* pView = (CFODrawView*)(pParent->GetActiveFrame()->GetActiveView());
									if(pView != NULL && pView->IsKindOf(RUNTIME_CLASS(CFODrawView)))
									{
										pView->CanvasWnd()->SendMessage(WM_FO_RESETSLECTCOMPONET_STATE,(WPARAM)1);
									}
								}
								
								CFOToolBoxItem *pItem = new  CFOToolBoxItem;
								pItem->LoadIconID(IDI_FILE_ICON);
								pItem->SetCaption(strCol);
								pItem->SetType(3000);
							
								// do OLE drag and drop
								DoOleDragAndDrop(pItem);

								delete pItem;
							}
						}
						
					}
					break;

				case WM_KEYDOWN:
					if (msg.wParam != VK_ESCAPE)
						break;

				case WM_SETCURSOR:
					::SetCursor(hCur);
					break;

				case WM_LBUTTONUP:
					{
						ReleaseCapture();
					}

					goto ExitLoop;

				default:
					DispatchMessage(&msg);
					break;
				}
			}

		ExitLoop:
			ReleaseCapture();
			AfxUnlockTempMaps(FALSE);
			if (bDragging)
			{
				Invalidate();
			}
		}
	}
	
}

void CDBSortListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFOBaseGridListCtrl::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CTableBar

CTableBar::CTableBar()
{
	m_pView = NULL;
	pOldSelect = NULL;
	nOldSelectCount = 0;
}

CTableBar::~CTableBar()
{
	POSITION pos = m_Shapes.GetHeadPosition();
	while(pos != NULL)
		delete m_Shapes.GetNext(pos);
	m_Shapes.RemoveAll();
}


#define ID_TREE 2093
#define ID_COL  2094

BEGIN_MESSAGE_MAP(CTableBar, CFOPControlBar)
	//{{AFX_MSG_MAP(CTableBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(LVN_ITEMCHANGED, ID_TREE, OnItemchangedContextList)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(FOPM_PROPERTY_CHANGED,   OnPropertyChanged)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTableBar message handlers

void CTableBar::SelectItem(CFODrawShape *pShape)
{
	if(pShape == NULL)
	{
		return;
	}
	
	int nCount = m_TreeCtrl.GetItemCount();
	for(int x = 0; x < nCount; x++)
	{
		CFODrawShape *pObj = (CFODrawShape *)m_TreeCtrl.GetItemData(x);
		if(pObj == pShape)
		{
			m_TreeCtrl.SetItemState(x,  LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
			m_TreeCtrl.EnsureVisible(x, FALSE);
		}
	}
}

int CTableBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFOPControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	LoadFromFile();	

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | FOP_TS_ALIGN_BOTTOM | WS_TABSTOP;
	m_wndTab.Create(this, dwStyle);
	
	dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_AUTOARRANGE;
	if (!m_TreeCtrl.Create(dwStyle, CRect(0,0,0,0), &m_wndTab, ID_TREE))
		return -1;      // failed to create tree control
	
	VERIFY(m_ContextImageSmall.Create(IDB_MB_IMAGES_SMALL,16,2,RGB(255,0,255)));
	m_ContextImageSmall.SetBkColor(GetSysColor(COLOR_WINDOW));
	// ... Associate the image lists with the context list
	m_TreeCtrl.SetImageList(&m_ContextImageSmall, LVSIL_SMALL);

	DWORD dwExStyle = WS_EX_CLIENTEDGE | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_TreeCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));
	
	CString strText;
	strText = _T("Name");
	m_TreeCtrl.InsertColumn ( 0, strText, LVCFMT_CENTER, 80 );
	
	strText = _T("DB Name");
	m_TreeCtrl.InsertColumn ( 1, strText, LVCFMT_CENTER, 80 );
	
	strText = _T("DB Type");
	m_TreeCtrl.InsertColumn ( 2, strText, LVCFMT_LEFT, 80 );
	
	m_TreeCtrl.ShowWindow(SW_SHOW);

	m_wndTab.AddTab(&m_TreeCtrl,"Var");
	m_wndTab.SetTabPageIcon(0,IDR_MAINFRAME);

	dwStyle = WS_BORDER | WS_CHILD | LVS_REPORT | LVS_SINGLESEL;
	if (!m_ColCtrl.Create(dwStyle, CRect(0,0,0,0), &m_wndTab, ID_COL))
		return -1;      // failed to create tree control
	
	// ... Associate the image lists with the context list
	m_ColCtrl.SetImageList(&m_ContextImageSmall, LVSIL_SMALL);
	
	dwExStyle = WS_EX_CLIENTEDGE | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_ColCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));
	
	strText = _T("Database Columns <Drag and Drop>");
	m_ColCtrl.InsertColumn ( 0, strText, LVCFMT_CENTER, 200 );
	
	m_ColCtrl.ShowWindow(SW_SHOW);
	
	m_wndTab.AddTab(&m_ColCtrl,"DB");
	m_wndTab.SetTabPageIcon(1,IDR_MAINFRAME);

	m_wndTool.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,100,100), &m_wndTab,1222);
	
	m_wndTool.EnableHeaderCtrl(TRUE, _T("Property"), _T("Value"));
	m_wndTool.EnableDescriptionArea();
	m_wndTool.SetVSDotNetLook();
	m_wndTab.AddTab(&m_wndTool,"Prop");
	m_wndTab.SetTabPageIcon(2,IDR_MAINFRAME);
	

	m_wndToolBox.Create(WS_CHILD|WS_VISIBLE|WS_EX_CLIENTEDGE,CRect(0,0,100,100),&m_wndTab,1338);
	if(m_Shapes.GetCount() <= 0)
	{
		m_wndToolBox.AddPage("New");
		m_wndToolBox.ActivatePage(0);
	}
	else
	{
		POSITION pos = m_Shapes.GetHeadPosition();
		while(pos != NULL)
		{
			CFOListItemObj *pObj = (CFOListItemObj *)m_Shapes.GetNext(pos);
			CString strPathX = AfxGetApp()->m_pszHelpFilePath;
			strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
			CString strOtherFile;
			strOtherFile = strPathX+"\\Shapes\\";
			strOtherFile += pObj->strFileName;
			CString strTemp = pObj->strFileName;
			strTemp = strTemp.Left(strTemp.GetLength() -4);
			m_wndToolBox.AddPage(strTemp);
			m_wndToolBox.GetToolBoxWnd()->LoadResFile(strOtherFile);
		}
		m_wndToolBox.ActivatePage(0);
	}

	m_wndTab.AddTab(&m_wndToolBox,_T("Symbol"));
	m_wndTab.SetTabPageIcon(3,IDR_MAINFRAME);

	InitProperty();

//	m_wndTab.ActivateTab(0);

	m_wndTab.SetTabTotalHeightOrWidth(25);
	m_wndTab.GetTabControl()->SetFlatBorderLineColor(RGB(128,128,255));
	m_wndTab.SetDrawFlatBorder(TRUE);
	m_wndTab.SetDrawMoneyMode(TRUE);
	m_wndTab.GetTabControl()->SetTabBkColor(gfxData.m_XPGradientDark);
	m_wndTab.GetTabControl()->SetActiveTabBkColor(gfxData.m_XPGradientLight);
	m_wndTab.GetTabControl()->SetInActiveTabBkColor(gfxData.m_crXPSelectBackColor);
	m_wndTab.UpdateWindow();

	m_wndTab.UpdateWindow();
	m_wndTab.ActivateTab(1);
	m_wndTab.ActivateTab(2);
	m_wndTab.ActivateTab(3);
	m_wndTab.ActivateTab(0);

	return 0;
}

CFOListItemObj *CTableBar::FindObjByID(int nIndex)
{
	POSITION pos = m_Shapes.GetHeadPosition();
	while(pos != NULL)
	{
		CFOListItemObj *pObj = (CFOListItemObj *)m_Shapes.GetNext(pos);
		if(pObj->nID == nIndex)
		{
			return pObj;
		}
	}
	return NULL;
}

void CTableBar::LoadFromFile()
{
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strOtherFile;
	strOtherFile = strPathX+"\\Shapes\\index.dat";
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
				CString strTitle;
				CString strFile;
				strTitle = strTemp.Left(strTemp.ReverseFind('#'));
				strFile = strTemp.Right(strTemp.GetLength() - strTitle.GetLength() -1);
				if((!strTitle.IsEmpty()) && (!strFile.IsEmpty()))
				{
					CFOListItemObj *pObj = new CFOListItemObj;
					pObj->strTitle = strTitle;
					pObj->strFileName = strFile;
					pObj->nID = nNumber;
					m_Shapes.AddTail(pObj);
					nNumber ++;
				}
			}	
		}
		m_File.Close();
	}
}

BOOL CTableBar::FindDBName(CFODrawShapeSet *m_ShapeSet, const CString &strFind)
{
	int nTotal = 0;
	CFODrawShape* pComp = NULL;
	int xy = 0;
	for(xy = 0; xy < m_ShapeSet->GetCount(); xy ++)
	{
		pComp = (CFODrawShape* )m_ShapeSet->GetObject(xy);
		if(strFind == pComp->GetDBVarName())
		{
			nTotal ++;
		}
	}

	if(nTotal > 1)
	{
		return TRUE;
	}
	
	return FALSE;
}

CString CTableBar::GetUniqueDBName(CFODrawShapeSet *m_ShapeList, const CString &strStart)
{
	int xnumber = 1;
	CString strText = strStart;
	CFODrawShape* pComp = NULL;
	CString strName;
	strName.Format(_T("%s%u"), strText, xnumber );
 	int xy = 0;
	for(xy = 0; xy < m_ShapeList->GetCount(); xy ++)
	{
		pComp = (CFODrawShape* )m_ShapeList->GetObject(xy);
		if(strName == pComp->GetDBVarName())
		{
			xnumber++;
			strName.Format(_T("%s%u"), strStart, xnumber );
			xy = 0;
		}
	}
	
	return strName;
}

void CTableBar::InitShapes(CFODataModel *pDataModel)
{
	if(pDataModel == NULL)
	{
		return;
	}
	m_TreeCtrl.DeleteAllItems();
	CString strSpace = _T("                  ");
	CString strMe;
	CString strNeed = _T("");

	CFODrawShapeList m_List;
	pDataModel->SearchForAllEFormShapes(m_List);

	CFODrawShapeSet m_ShapeSet;
	POSITION posx = m_List.GetHeadPosition();
	while(posx != NULL)
	{
		m_ShapeSet.AddTail((CFODrawShape *)m_List.GetNext(posx));
	}
	
	int x = 0;
	CFODrawShape *pObject = NULL;
	POSITION pos = m_List.GetTailPosition();
	while (pos != NULL) 
	{
		pObject = (CFODrawShape*)(m_List.GetPrev(pos));

		strMe = pObject->GetObjectName();
		
		CString strTotal;
		strTotal = strMe;
		int nItem = m_TreeCtrl.InsertItem(x, strTotal, 2);

		BOOL bChanged = FALSE;
		pObject->GetPropBoolValue(bChanged, P_ID_DBNAME_CHANGED);

		BOOL bCorrected = FALSE;
		pObject->GetPropBoolValue(bCorrected, P_ID_DBNAME_CORRECTED);

		CString strDB = pObject->GetDBVarName();
		
// 		if(!bCorrected)
// 		{
// 			if(strDB.IsEmpty())
// 			{
// //				if(FindDBName(&m_ShapeSet, strDB))
// 				if(pObject->IsKindOf(RUNTIME_CLASS(CFOPRichEditShape)))
// 				{
// 					CFOPRichEditShape *pRich = static_cast<CFOPRichEditShape *>(pObject);
// 					strDB = pObject->GetObjectName();
// 					strDB = GetUniqueDBName(&m_ShapeSet, strDB);
// 					strDB = _T("[txt") + strDB + _T("]");
// 					CString str = strDB;
// 					str = _T("{\\rtf1\\ansi\\ansicpg936\\deff0\\deflang1033\\deflangfe2052{\\fonttbl{\\f0\\fmodern\\fprq6\\fcharset134 \\'cb\\'ce\\'cc\\'e5;}}{\\*\\generator Msftedit 5.41.15.1507;}\\viewkind4\\uc1\\pard\\lang2052\\f0\\fs20 ") + strDB + _T("\\par}");
// 					if(!HAS_BASE(pObject, CDbPrintGridShape))
// 						pObject->SetDBVarName(str);
// 					pRich->SetCurrentText(str);
// 					pObject->PutPropBoolValue(P_ID_DBNAME_CORRECTED, TRUE);
// 					pObject->UpdateControl();
// 					
// 				}
// 				else
// 				{
// 					strDB = pObject->GetObjectName();
// 					strDB = GetUniqueDBName(&m_ShapeSet, strDB);
// 					strDB = _T("[txt") + strDB + _T("]");
// 					if(!HAS_BASE(pObject, CDbPrintGridShape))
// 						pObject->SetDBVarName(strDB);
// 					if((pObject->GetType() != 651) && pObject->IsKindOf(RUNTIME_CLASS(CFOPEFormBaseShape)))
// 					{
// 						CFOPEFormBaseShape *pForm = static_cast<CFOPEFormBaseShape *>(pObject);
// 						pForm->SetCurrentText(strDB);
// 					}
// 					pObject->PutPropBoolValue(P_ID_DBNAME_CORRECTED, TRUE);
// 					pObject->UpdateControl();
// 				}
// 			}
// 		}
		
		m_TreeCtrl.SetItemText ( x, 1, strDB );
		m_TreeCtrl.SetItemText ( x, 2, _T("Text") );
		
		m_TreeCtrl.SetItemData(nItem, (DWORD) pObject);
		x++;
	}
	
	//	m_TreeCtrl.Expand(hRoot,TVE_EXPAND);
//	m_TreeCtrl.ShowWindow(SW_SHOW);
}

void CTableBar::OnSize(UINT nType, int cx, int cy) 
{
	CFOPControlBar::OnSize(nType, cx, cy);
	if( m_wndTab.GetSafeHwnd() != NULL )
	{
		CRect r;
		GetFullRect(r);
		m_wndTab.SetWindowPos( NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER|SWP_NOACTIVATE );
	}
}

BOOL CTableBar::OnEraseBkgnd( CDC* pDC )
{
	CFOPControlBar::OnEraseBkgnd(pDC);
	return TRUE;
}

void CTableBar::DeleteAll()
{
	m_ColCtrl.DeleteAllItems();
	theApp.m_dbcols.RemoveAll();
}

void CTableBar::AddColumn(const CString &strColName, const int &nImage)
{
	m_ColCtrl.InsertItem(m_ColCtrl.GetItemCount(), strColName, nImage);
}

void CTableBar::OnItemchangedContextList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(m_TreeCtrl.GetSelectedCount()>1)
	{
		return;
	}
	int nItemIndex = -1;
	// if there's an element selected in the listbox
	if ( (m_TreeCtrl. GetNextItem ( -1, LVNI_SELECTED ) ) != -1 ) 
	{
		while ( ( nItemIndex = m_TreeCtrl.GetNextItem ( nItemIndex, LVNI_SELECTED ) ) != -1 )
		{
			CFODrawShape *pData = (CFODrawShape*)m_TreeCtrl.GetItemData(nItemIndex);
			
			CUCCPrintView *pView = (CUCCPrintView *)FOGetActiveView();
			if(pView != NULL)
			{
				pView->SelectNewShape(pData);
			}
		}
	}
	
	*pResult = 0;
}

void CTableBar::InitProperty()
{
	CFOPProp* pGroupTemp = NULL;
	
	pGroupTemp = new CFOPProp(_T("Canvas"));
	
	pGroupTemp->AddSubItem(new CFOPProp(_T("Caption"),(_variant_t)(theApp.m_Options.m_strPageCaption), _T("Set Page Caption"), idPageCaption));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Fill Type"),(_variant_t)(theApp.m_Options.m_nPageFillType), _T("Set Fill Type"), idPageFillType));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Back Color"), theApp.m_Options.m_crPageBKColor, NULL, _T("Set Fill Back Color"), idPageBKColor));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Pattern Color"), theApp.m_Options.m_crPagePatternColor, NULL, _T("Set Fill Pattern Color"), idPagePatternColor));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Page Back Color"), theApp.m_Options.m_crPagePageBKColor, NULL, _T("Set Page Back Color"), idPagePageBKColor));
	
	m_wndTool.AddProperty(pGroupTemp);
	
	pGroupTemp = new CFOPProp(_T("Shape's Basic"));

	pGroupTemp->AddSubItem(new CFOPProp(_T("Name"),(_variant_t)(theApp.m_Options.m_strObjectName), _T("Set Object Name"), idObjectName));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Caption"),(_variant_t)(theApp.m_Options.m_strObjectCaption), _T("Set Object Caption"), idObjectCaption));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Flat Border"),(_variant_t)(theApp.m_Options.m_bObjectFlat3D), _T("Set Object 3D Look"), idObjectFlat3D));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Fill Type"),(_variant_t)(theApp.m_Options.m_nObjectFillType), _T("Set Fill Type"), idObjectFillType));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Back Color"), theApp.m_Options.m_crObjectBKColor, NULL, _T("Set Fill Back Color"), idObjectBKColor));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Pattern Color"), theApp.m_Options.m_crObjectPatternColor, NULL, _T("Set Fill Pattern Color"), idObjectPatternColor));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Tool Tips"),(_variant_t)(theApp.m_Options.m_strObjectToolTip), _T("Set Object Tool Tips"), idObjectToolTip));
	
	m_wndTool.AddProperty(pGroupTemp);
	
	//	Start Text Property
	pGroupTemp = new CFOPProp(_T("Shape's Font"));
	
	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);
	
	pGroupTemp->AddSubItem(new CFOPFontProp(_T("Font Name"), lf, CF_EFFECTS|CF_SCREENFONTS, _T("Specifies the default font for the dialog"), idTextName));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Size"),(_variant_t)(theApp.m_Options.m_nTextSize), _T("Set Text Size"), idTextSize));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Color"), theApp.m_Options.m_crTextColor, NULL, _T("Set Font Color"), idTextColor));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Bold"),(_variant_t)(theApp.m_Options.m_bTextBlod), _T("Set Text Bold"), idTextBlod));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Italic"),(_variant_t)(theApp.m_Options.m_bTextItalic), _T("Set Text Italic"), idTextItalic));
	pGroupTemp->AddSubItem(new CFOPProp(_T("UnderLine"),(_variant_t)(theApp.m_Options.m_bTextUnderLine), _T("Set Text UnderLine"), idTextUnderLine));

	pGroupTemp->Expand(TRUE);
	m_wndTool.AddProperty(pGroupTemp);
	//	End Text Property

	//	Start Line Property
	pGroupTemp = new CFOPProp(_T("Shape's Line"));
	
	pGroupTemp->AddSubItem(new CFOPLineWidthProp(_T("Width"), theApp.m_Options.m_nBorderLineWidth, _T("Set Line Width"), idBorderLineWidth));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Color"), theApp.m_Options.m_crBorderLineColor, NULL, _T("Set Line Color"), idBorderLineColor));
	pGroupTemp->AddSubItem(new CFOPLineTypeProp(_T("Type"), theApp.m_Options.m_nBorderLineType, _T("Set Line Type"), idBorderLineType));
	pGroupTemp->AddSubItem(new CFOPArrowProp(_T("Start Arrow"), theApp.m_Options.m_nLineStartArrow, _T("Set Line Start Arrow Type"), idLineStartArrow));
	pGroupTemp->AddSubItem(new CFOPArrowProp(_T("End Arrow"), theApp.m_Options.m_nLineEndArrow, _T("Set Line End Arrow Type"), idLineEndArrow));
	
	pGroupTemp->Expand(TRUE);
	m_wndTool.AddProperty(pGroupTemp);
	//	End Line Property
	
	//	Start position Size
	pGroupTemp = new CFOPProp(_T("Shape's Position"));
	
	pGroupTemp->AddSubItem(new CFOPProp(_T("Left"),(_variant_t)(theApp.m_Options.m_fPositionLeft), _T("Set Shape Left Position"), idPositionLeft));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Right"),(_variant_t)(theApp.m_Options.m_fPositionRight), _T("Set Shape RightLeft Position"), idPositionRight));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Width"),(_variant_t)(theApp.m_Options.m_fPositionWidth), _T("Set Shape Width"), idPositionWidth));
	pGroupTemp->AddSubItem(new CFOPProp(_T("height"),(_variant_t)(theApp.m_Options.m_fPositionHeight), _T("Set Shape Height"), idPositionHeight));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Rotate"),(_variant_t)(theApp.m_Options.m_fPositionRotate), _T("Set Shape Rotate"), idPositionRotate));
	
	pGroupTemp->Expand(TRUE);
	m_wndTool.AddProperty(pGroupTemp);
	//	End position Size
	
	//	Start Shadow
	pGroupTemp = new CFOPProp(_T("Shape's Shadow"));
	
	pGroupTemp->AddSubItem(new CFOPProp(_T("Visual"), (_variant_t)(theApp.m_Options.m_bShadowVisual), _T("Show Shadow"), idShadowVisual));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Type"), theApp.m_Options.m_nShadowType, _T("Set Shape Shadow Type"), idShadowType));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Back Color"), theApp.m_Options.m_crShadowBKColor, NULL, _T("Set Shadow Color"), idShadowBKColor));
	pGroupTemp->AddSubItem(new CFOPColorProp(_T("Pattern Color"), theApp.m_Options.m_crShadowPatternColor, NULL, _T("Set Shadow Color"), idShadowPatternColor));
	pGroupTemp->AddSubItem(new CFOPProp(_T("X Offet"),(_variant_t)(theApp.m_Options.m_nShadowXOffset), _T("Set Shape Shadow X Offset"), idShadowXOffset));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Y Offet"),(_variant_t)(theApp.m_Options.m_nShadowYOffset), _T("Set Shape Shadow Y Offset"), idShadowYOffset));

	pGroupTemp->Expand(TRUE);
	m_wndTool.AddProperty(pGroupTemp);
	//	End Shadow
	
	//	Start Shadow
	pGroupTemp = new CFOPProp(_T("Shape's Protection"));
	
	pGroupTemp->AddSubItem(new CFOPProp(_T("Resize Protect"),	(_variant_t)(theApp.m_Options.m_bResizeProtect), _T("Is width and height locked."), idResizeProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Delete Protect"),	(_variant_t)(theApp.m_Options.m_bDeleteProtect), _T("Is deleting protect,if it is true,you can not deleting the shape."), idDeleteProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Rotate Protect"),	(_variant_t)(theApp.m_Options.m_bRotateProtect), _T("Is rotating protect,if it is true,you cann't rotating it."), idRotateProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Tab Order"),		(_variant_t)(theApp.m_Options.m_bTabOrderProtect), _T("Is It tab order protect,this method is a temp property,not used currently."), idTabOrderProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Select Protect"),	(_variant_t)(theApp.m_Options.m_bSelectProtect), _T("Is select protect,if it is true,you cann't select it on the canvas."), idSelectProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Move Protect"),	(_variant_t)(theApp.m_Options.m_bMoveProtect), _T("Is moving protect,if it is true,you cann't moving it."), idMoveProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Print Protect"),	(_variant_t)(theApp.m_Options.m_bPrintProtect), _T("Is printing protect,if it is true,you cann't printing it."), idPrintProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Copy Protectt"),	(_variant_t)(theApp.m_Options.m_bCopyProtect), _T("Is copying protect,if it is true,you can not copying it."), idCopyProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Aspect Ratio"),	(_variant_t)(theApp.m_Options.m_bAspectRatio), _T("Is aspect ratio,if it is true,the shape will be resize with aspect ratio mode."), idAspectRatio));
	pGroupTemp->AddSubItem(new CFOPProp(_T("X Position"),		(_variant_t)(theApp.m_Options.m_bXPosProtect), _T("Is X position protect,if it is true,the shape will be resize with X position mode."), idXPosProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Y Position"),		(_variant_t)(theApp.m_Options.m_bYPosProtect), _T("Is Y position protect,if it is true,the shape will be resize with Y position mode."), idYPosProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Width Protect"),	(_variant_t)(theApp.m_Options.m_bWidthProtect), _T("Is Width protect,if it is true,the shape will be resize."), idWidthProtect));
	pGroupTemp->AddSubItem(new CFOPProp(_T("Height Protect"),	(_variant_t)(theApp.m_Options.m_bHeightProtect), _T("Is Height protect,if it is true,the shape will be resize."), idHeightProtect));

	pGroupTemp->Expand(TRUE);
	m_wndTool.AddProperty(pGroupTemp);
	//	End Shadow
}

void CTableBar::UpdateProperty(CUCCPrintView* pView, const BOOL &bWithAction)
{
	if(NULL == m_wndTool.GetSafeHwnd())
		return;

	CUCCPrintView* pViewTemp =(CUCCPrintView*)FOGetActiveView();
	if(NULL == pViewTemp)
		return;

	CFODataModel* pModel = pViewTemp->GetCurrentModel();
	if(NULL == pModel)
		return;

	BOOL bDoNotUpdate = FALSE;
	BOOL bDoNotUpdateCanvas = FALSE;
	CFODrawShape *pShape = NULL;
	int nCurTotal = pView->GetSelectShapes()->GetCount();
	if(nCurTotal > 0)
	{
		pShape = pView->GetCurrentSelectShape();
	}

	if(nCurTotal == 1)
	{
		if(pShape == pOldSelect && nOldSelectCount == 1)
		{
			bDoNotUpdate = TRUE;
		}
	}

	if(nCurTotal == 0)
	{
		bDoNotUpdate = TRUE;
	}

	if(nCurTotal == 0 && nOldSelectCount == 0)
	{
		bDoNotUpdateCanvas = TRUE;
	}

	BOOL bRedrawDrawCanvas = TRUE;
	if(pOldSelect != NULL && pShape == pOldSelect && nOldSelectCount == 1)
	{
		bRedrawDrawCanvas = FALSE;
	}

	nOldSelectCount = nCurTotal;
	pOldSelect = pShape;

	CFOPProp* pPropTemp = NULL;
	if(!bDoNotUpdateCanvas && bRedrawDrawCanvas)
	{
		theApp.m_Options.m_strPageCaption = pModel->GetObjectCaption();
		theApp.m_Options.m_nPageFillType =(short)pModel->GetBrushType();
		theApp.m_Options.m_crPageBKColor = pModel->GetBkColor();
		theApp.m_Options.m_crPagePatternColor = pModel->GetPatternColor();
		theApp.m_Options.m_crPagePageBKColor = pModel->GetPageBkColor();
		
		
		pPropTemp = m_wndTool.FindItemByData(idPageCaption);
		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_strPageCaption));
		pPropTemp = m_wndTool.FindItemByData(idPageFillType);
		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_nPageFillType));
		pPropTemp = m_wndTool.FindItemByData(idPageBKColor);
		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crPageBKColor));
		pPropTemp = m_wndTool.FindItemByData(idPagePatternColor);
		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crPagePatternColor));
		pPropTemp = m_wndTool.FindItemByData(idPagePageBKColor);
		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crPagePageBKColor));
		if(bDoNotUpdate && !bWithAction)
		{
			pPropTemp = m_wndTool.FindItemByData(idObjectName);
			if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(_T("")));
			pPropTemp = m_wndTool.FindItemByData(idObjectCaption);
			if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(_T("")));

			m_wndTool.UpdateGrid();
			return;
		}
	}
	
	if(NULL == pView)
	{
		m_wndTool.UpdateGrid();
		return;
	}

	m_pView = pView;
	pModel = m_pView->GetCurrentModel();

	if(NULL == pModel || FALSE == pModel->IsDesignMode())
		return;

	if(bDoNotUpdate && !bWithAction)
	{
		return;
	}

	if(pShape == NULL)
	{
		return;
	}
//	Use the First Shape.

	theApp.m_Options.m_strObjectName = pShape->GetObjectName();
	theApp.m_Options.m_strObjectCaption = pShape->GetObjectCaption();
	theApp.m_Options.m_bObjectFlat3D = TRUE == pShape->IsFlat();
	theApp.m_Options.m_nObjectFillType =(short)pShape->GetBrushType();
	theApp.m_Options.m_crObjectBKColor = pShape->GetBkColor();
	theApp.m_Options.m_crObjectPatternColor = pShape->GetPatternColor();
	theApp.m_Options.m_strObjectToolTip = pShape->GetToolTip();
	
	theApp.m_Options.m_strTextName = pShape->GetFaceName();
	theApp.m_Options.m_nTextSize =(short)pShape->GetPointSize();
	theApp.m_Options.m_crTextColor = pShape->GetFontColor();
	theApp.m_Options.m_bTextBlod = pShape->GetWeight() > 600;
	theApp.m_Options.m_bTextItalic = pShape->GetItalic() == TRUE;
	theApp.m_Options.m_bTextUnderLine = pShape->GetUnderline() == TRUE;
	
	theApp.m_Options.m_nBorderLineWidth =(short)pShape->GetLineWidth();
	theApp.m_Options.m_crBorderLineColor = pShape->GetLineColor();
	theApp.m_Options.m_nBorderLineType =(short)pShape->GetPenStyle();
	theApp.m_Options.m_nLineStartArrow =(short)pShape->GetStartArrowType();
	theApp.m_Options.m_nLineEndArrow =(short)pShape->GetEndArrowType();
	
	CRect rcSnapSize = m_pView->GetTotalSelectSnapRect();		
	pModel->ConvertMapLogTo(pModel->GetUIUnit(), theApp.m_Options.m_fPositionLeft, FALSE);
	pModel->ConvertMapLogTo(pModel->GetUIUnit(), theApp.m_Options.m_fPositionRight, TRUE);
	pModel->ConvertMapLogTo(pModel->GetUIUnit(), theApp.m_Options.m_fPositionWidth, FALSE);
	pModel->ConvertMapLogTo(pModel->GetUIUnit(), theApp.m_Options.m_fPositionHeight, TRUE);
	
	theApp.m_Options.m_fPositionLeft =(double)rcSnapSize.left;
	theApp.m_Options.m_fPositionRight =(double)rcSnapSize.top;
	theApp.m_Options.m_fPositionWidth =(double)rcSnapSize.Width();	
	theApp.m_Options.m_fPositionHeight =(double)rcSnapSize.Height();
	theApp.m_Options.m_fPositionRotate = pShape->GetRotateAngle()/10.0f;
	
	theApp.m_Options.m_bShadowVisual = TRUE == pShape->GetShadow();
	theApp.m_Options.m_nShadowType =(short)pShape->GetShadowBrushType();
	theApp.m_Options.m_crShadowBKColor = pShape->GetShadowColor();
	theApp.m_Options.m_crShadowPatternColor = pShape->GetShadowPatternColor();
	theApp.m_Options.m_nShadowXOffset =(short)pShape->GetShadowOffsetX();
	theApp.m_Options.m_nShadowYOffset =(short)pShape->GetShadowOffsetY();
	
	theApp.m_Options.m_bResizeProtect = TRUE == pShape->IsResizeProtect();
	theApp.m_Options.m_bDeleteProtect = TRUE == pShape->IsDeleteProtect();
	theApp.m_Options.m_bRotateProtect = TRUE == pShape->IsRotateProtect();
	theApp.m_Options.m_bTabOrderProtect = TRUE == pShape->IsTabOrderProtect();
	theApp.m_Options.m_bSelectProtect = TRUE == pShape->IsSelectProtect();
	theApp.m_Options.m_bMoveProtect = TRUE == pShape->IsMoveProtect();
	theApp.m_Options.m_bPrintProtect = TRUE == pShape->IsPrintProtect();
	theApp.m_Options.m_bCopyProtect = TRUE == pShape->IsCopyProtect();
	theApp.m_Options.m_bAspectRatio = TRUE == pShape->IsAspectRatio();
	theApp.m_Options.m_bXPosProtect = TRUE == pShape->IsXPosProtect();
	theApp.m_Options.m_bYPosProtect = TRUE == pShape->IsYPosProtect();
	theApp.m_Options.m_bWidthProtect = TRUE == pShape->IsWidthProtect();
	theApp.m_Options.m_bHeightProtect = TRUE == pShape->IsHeightProtect();

	pPropTemp = m_wndTool.FindItemByData(idObjectName);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_strObjectName));
	pPropTemp = m_wndTool.FindItemByData(idObjectCaption);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_strObjectCaption));
	pPropTemp = m_wndTool.FindItemByData(idObjectFlat3D);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bObjectFlat3D));
	pPropTemp = m_wndTool.FindItemByData(idObjectFillType);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_nObjectFillType));
	pPropTemp = m_wndTool.FindItemByData(idObjectBKColor);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crObjectBKColor));
	pPropTemp = m_wndTool.FindItemByData(idObjectPatternColor);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crObjectPatternColor));
	pPropTemp = m_wndTool.FindItemByData(idObjectToolTip);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_strObjectToolTip));

	pPropTemp = m_wndTool.FindItemByData(idTextName);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_strTextName));
	pPropTemp = m_wndTool.FindItemByData(idTextSize);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_nTextSize));
	pPropTemp = m_wndTool.FindItemByData(idTextColor);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crTextColor));
	pPropTemp = m_wndTool.FindItemByData(idTextBlod);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bTextBlod));
	pPropTemp = m_wndTool.FindItemByData(idTextItalic);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bTextItalic));
	pPropTemp = m_wndTool.FindItemByData(idTextUnderLine);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bTextUnderLine));

	if(TRUE != pShape->IsNullPen())
	{
 		pPropTemp = m_wndTool.FindItemByData(idBorderLineWidth);
 		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_nBorderLineWidth));
		
	}
	else
	{
		pPropTemp = m_wndTool.FindItemByData(idBorderLineWidth);
 		if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)0));
	}

	pPropTemp = m_wndTool.FindItemByData(idBorderLineColor);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crBorderLineColor));
	pPropTemp = m_wndTool.FindItemByData(idBorderLineType);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_nBorderLineType));
	pPropTemp = m_wndTool.FindItemByData(idLineStartArrow);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_nLineStartArrow));
	pPropTemp = m_wndTool.FindItemByData(idLineEndArrow);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_nLineEndArrow));

	pPropTemp = m_wndTool.FindItemByData(idPositionLeft);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_fPositionLeft));
	pPropTemp = m_wndTool.FindItemByData(idPositionRight);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_fPositionRight));
	pPropTemp = m_wndTool.FindItemByData(idPositionWidth);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_fPositionWidth));
	pPropTemp = m_wndTool.FindItemByData(idPositionHeight);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_fPositionHeight));
	pPropTemp = m_wndTool.FindItemByData(idPositionRotate);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_fPositionRotate));

	pPropTemp = m_wndTool.FindItemByData(idShadowVisual);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bShadowVisual));
	pPropTemp = m_wndTool.FindItemByData(idShadowType);
	if(NULL != pPropTemp) pPropTemp->UpdateValue(theApp.m_Options.m_nShadowType);
	pPropTemp = m_wndTool.FindItemByData(idShadowBKColor);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crShadowBKColor));
	pPropTemp = m_wndTool.FindItemByData(idShadowPatternColor);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)((long)theApp.m_Options.m_crShadowPatternColor));
	pPropTemp = m_wndTool.FindItemByData(idShadowXOffset);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_nShadowXOffset));
	pPropTemp = m_wndTool.FindItemByData(idShadowYOffset);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_nShadowYOffset));

	pPropTemp = m_wndTool.FindItemByData(idResizeProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bResizeProtect));
	pPropTemp = m_wndTool.FindItemByData(idDeleteProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bDeleteProtect));
	pPropTemp = m_wndTool.FindItemByData(idRotateProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bRotateProtect));
	pPropTemp = m_wndTool.FindItemByData(idTabOrderProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bTabOrderProtect));
	pPropTemp = m_wndTool.FindItemByData(idSelectProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bSelectProtect));
	pPropTemp = m_wndTool.FindItemByData(idMoveProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bMoveProtect));
	pPropTemp = m_wndTool.FindItemByData(idPrintProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bPrintProtect));
	pPropTemp = m_wndTool.FindItemByData(idCopyProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bCopyProtect));
	pPropTemp = m_wndTool.FindItemByData(idAspectRatio);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bAspectRatio));
	pPropTemp = m_wndTool.FindItemByData(idXPosProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bXPosProtect));
	pPropTemp = m_wndTool.FindItemByData(idYPosProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bYPosProtect));
	pPropTemp = m_wndTool.FindItemByData(idWidthProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bWidthProtect));
	pPropTemp = m_wndTool.FindItemByData(idHeightProtect);
	if(NULL != pPropTemp) pPropTemp->UpdateValue((_variant_t)(theApp.m_Options.m_bHeightProtect));

	m_wndTool.UpdateGrid();
}

LRESULT CTableBar::OnPropertyChanged(WPARAM,LPARAM lParam)
{
	CFOPProp* pProp =(CFOPProp*) lParam;
	ASSERT(pProp);

	CUCCPrintView *pViewTemp =(CUCCPrintView*)FOGetActiveView();
	if(NULL == pViewTemp)
		return 0;
	
	CFODataModel* pModel = pViewTemp->GetCurrentModel();
	if(NULL == pModel)
		return 0;
	
	CFOMultiModelPropAction* pModelAction = pModel->GetModelPropAction();
	switch((int) pProp->GetData())
	{
	case idPageCaption:
		pModelAction->AddString((LPCTSTR)(_bstr_t)pProp->GetValue(), M_ID_CAPTION);
		break;
	case idPageFillType:
		pModelAction->AddInt((short)pProp->GetValue(), M_ID_BURSHTYPE);
		break;
	case idPageBKColor:
		pModelAction->AddColor((long)pProp->GetValue(),M_ID_BK_COLOR);
		break;
	case idPagePatternColor:
		pModelAction->AddColor((long)pProp->GetValue(),M_ID_PATTERNCOLOR);
		break;
	case idPagePageBKColor:
		pModelAction->AddColor((long)pProp->GetValue(),M_ID_PAGE_BK_COLOR);
		break;
	}
	
	if(pModelAction->GetActionList()->GetCount() > 0)
	{
		pModel->Do(pModelAction, TRUE);
		pModel->SetModifiedFlag();
	}
	else
	{
		delete pModelAction;
		pModelAction = NULL;
	}

	if(NULL == m_pView)
		return 0;

	pModel = m_pView->GetCurrentModel();
	if(NULL == pModel)
		return 0;

	CFODrawShapeList* pShapeList = m_pView->GetSelectShapes();
	if(pShapeList->GetCount() < 1)
		return 0;

	CFOMultiShapePropAction* pAction = pModel->GetShapesPropAction();
	CRect rc = m_pView->GetTotalSelectSnapRect();

	switch((int) pProp->GetData())
	{
	case idObjectName:
		pAction->AddShapesString(*pShapeList,(LPCTSTR)(_bstr_t)pProp->GetValue(), P_ID_NAME);
		break;
	case idObjectCaption:
		pAction->AddShapesString(*pShapeList,(LPCTSTR)(_bstr_t)pProp->GetValue(), P_ID_CAPTION);
		break;
	case idObjectFlat3D:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_FLAT);
		break;
	case idObjectFillType:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_BURSHTYPE);
		break;
	case idObjectBKColor:
		pAction->AddShapesColor(*pShapeList,(long)pProp->GetValue(), P_ID_BK_COLOR);
		break;
	case idObjectPatternColor:
		pAction->AddShapesColor(*pShapeList,(long)pProp->GetValue(), P_ID_PATTERNCOLOR);
		break;
	case idObjectToolTip:
		pAction->AddShapesString(*pShapeList,(LPCTSTR)(_bstr_t)pProp->GetValue(), P_ID_TOOPTIP);
		break;
		//
	case idTextName:
		pAction->AddShapesString(*pShapeList,(LPCTSTR)(_bstr_t)pProp->GetValue(), P_ID_FONT_FACENAME);
		break;
	case idTextSize:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_FONT_POINTSIZE);
		break;
	case idTextColor:
		pAction->AddShapesColor(*pShapeList,(long)pProp->GetValue(), P_ID_FONT_COLOR);
		break;
	case idTextBlod:
		if((bool)pProp->GetValue() == true)
			pAction->AddShapesInt(*pShapeList, 700, P_ID_FONT_WEIGHT);
		else
			pAction->AddShapesInt(*pShapeList, 500, P_ID_FONT_WEIGHT);
		break;
	case idTextItalic:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_FONT_ITALIC);
		break;
	case idTextUnderLine:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_FONT_UNDERLINE);
		break;
		//
	case idBorderLineWidth:
		if((short)pProp->GetValue() == 0)
		{
			pAction->AddShapesBool(*pShapeList, TRUE, P_ID_NULL_PEN);
			pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_LINE_WIDTH);
		}
		else
		{
			pAction->AddShapesBool(*pShapeList, FALSE,P_ID_NULL_PEN);
			pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_LINE_WIDTH);
		}
		break;
	case idBorderLineColor:
		pAction->AddShapesColor(*pShapeList,(long)pProp->GetValue(), P_ID_LINE_COLOR);
		break;
	case idBorderLineType:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_PEN_STYLE);
		break;
	case idLineStartArrow:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_STARTARROW);
		break;
	case idLineEndArrow:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_ENDARROW);
		break;
		//
	case idPositionLeft:
		{
			double dOffsetL =(double)pProp->GetValue();
	//		pModel->ConvertToMapLog(pModel->GetUIUnit(), dOffsetL, FALSE);
			
			m_pView->DoMoveAction(pShapeList,(int)dOffsetL - rc.left, 0);					
			return 0;
		}
		break;
	case idPositionRight:
		{
			double dOffsetT =(double)pProp->GetValue();
		//	pModel->ConvertToMapLog(pModel->GetUIUnit(), dOffsetT, TRUE);
			
			m_pView->DoMoveAction(pShapeList, 0,(int)dOffsetT - rc.top);					
			return 0;
		}
		break;
	case idPositionWidth:
		{
			double dOffsetW =(double)pProp->GetValue();					
		//	pModel->ConvertToMapLog(pModel->GetUIUnit(), dOffsetW, FALSE);
			
			m_pView->DoResizeShapesActionEx(pShapeList, dOffsetW/(double)rc.Width(), 1.0, SideLeft);					
			return 0;
		}
		break;
	case idPositionHeight:
		{
			double dOffsetH =(double)pProp->GetValue();
		//	pModel->ConvertToMapLog(pModel->GetUIUnit(), dOffsetH, TRUE);
			
			m_pView->DoResizeShapesActionEx(pShapeList, 1.0, dOffsetH/(double)rc.Height(), TopMiddle);				
			return 0;
		}
		break;
	case idPositionRotate:
		{
			double dRotate =(double)pProp->GetValue();
			
			POSITION pos = pShapeList->GetHeadPosition();
			while(pos)
			{
				CFODrawShape* pShape = pShapeList->GetNext(pos);
				int nAngle = pShape->GetRotateAngle();
				int nRotate = int(dRotate*10) - nAngle;
				if(0 == nRotate) continue;
				
				CFODrawShapeList listTemp;
				listTemp.AddTail(pShape);
				m_pView->DoRotateShapesAction(&listTemp, nRotate);
			}
			
			return 0;
		}
		break;
		//	Shadow Property
	case idShadowVisual:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_SHADOW);
		break;
	case idShadowType:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_SHADOW_BRUSHTYPE);
		break;
	case idShadowBKColor:
		pAction->AddShapesColor(*pShapeList,(long)pProp->GetValue(), P_ID_SHADOW_COLOR);
		break;
	case idShadowPatternColor:
		pAction->AddShapesColor(*pShapeList,(long)pProp->GetValue(), P_ID_SHADOW_PATTERN_COLOR);
		break;
	case idShadowXOffset:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_SHADOW_OFFSETX);
		break;
	case idShadowYOffset:
		pAction->AddShapesInt(*pShapeList,(short)pProp->GetValue(), P_ID_SHADOW_OFFSETY);
		break;
		//
	case idResizeProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_RESIZEPROTECT);
		break;
	case idDeleteProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_DELETEPROTECT);
		break;
	case idRotateProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_ROTATEPROTECT);
		break;
	case idTabOrderProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_TABORDERPROTECT);
		break;
	case idSelectProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_SELECTPROTECT);
		break;
	case idMoveProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_MOVEPROTECT);
		break;
	case idPrintProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_PRINTPROTECT);
		break;
	case idCopyProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_COPYPROTECT);
		break;
	case idAspectRatio:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_ASPECTRATIO);
		break;
	case idXPosProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_XPOSPROTECT);
		break;
	case idYPosProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_YPOSPROTECT);
		break;
	case idWidthProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_WIDTHPROTECT);
		break;
	case idHeightProtect:
		pAction->AddShapesBool(*pShapeList,(bool)pProp->GetValue(), P_ID_HEIGHTPROTECT);
		break;
	}

	if(pAction->GetActionList()->GetCount() > 0)
	{
		pModel->Do(pAction, TRUE);
		pModel->SetModifiedFlag();
	}
	else
	{
		delete pAction;
	}
	

	return 0;      
}
