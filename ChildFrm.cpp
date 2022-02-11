// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "UCCPrint.h"

//E-XD++ Library add lines.
#include "UCCPrintDoc.h"
#include "UCCPrintView.h"
#include "ChildFrm.h"
#include "fores.h"
#include "MBEventEditDlg6.h"
#include "ExtTabModelManager.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CFOPMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CFOPMDIChildWnd)
//{{AFX_MSG_MAP(CChildFrame)
ON_WM_CREATE()
ON_COMMAND(ID_FO_ADD_NEWPAGE, OnFoAddNewpage)
ON_COMMAND(ID_FO_REMOVE_PAGE, OnFoRemovePage)
ON_COMMAND(ID_MOVE_PREVIOUS, OnMovePrevious)
ON_UPDATE_COMMAND_UI(ID_MOVE_PREVIOUS, OnUpdateMovePrevious)
ON_COMMAND(ID_MOVE_NEXT, OnMoveNext)
ON_UPDATE_COMMAND_UI(ID_MOVE_NEXT, OnUpdateMoveNext)
ON_COMMAND(ID_MB_CREATEPAGE_COPY, OnMbCreatepageCopy)
ON_UPDATE_COMMAND_UI(ID_MB_CREATEPAGE_COPY, OnUpdateMbCreatepageCopy)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREAFOAPPWIZARDRUCT cs

	if( !CFOPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
//E-XD++ Library add lines.
	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CFOPMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CFOPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
//E-XD++ add lines.
int CChildFrame::OnCreate(LPCREATESTRUCT LPCREATESTRUCT) 
{
	if (CFOPMDIChildWnd::OnCreate(LPCREATESTRUCT) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	
	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	//	nCmdShow = SW_SHOWMAXIMIZED;
	CFOPMDIChildWnd::ActivateFrame(nCmdShow);
	CUCCPrintDoc* pDoc = (CUCCPrintDoc*) GetActiveDocument();
	
	if(pDoc->bNewDocument)
	{
		if(theApp.bOpenTemplate)
		{
			CString strOtherFile;
			strOtherFile = theApp.strTemplateFile;
			if(LoadTemplateFile(strOtherFile))
			{
			}
			theApp.bOpenTemplate = FALSE;
			pDoc->bNewDocument = FALSE;
		}
		else
		{
			pDoc->bNewDocument = FALSE;
		}
	}
	else if(pDoc->bOpenDocument)
	{
		pDoc->bOpenDocument = FALSE;

		int nCount = pDoc->m_pModelManager->GetTabCount();
		if(nCount < 2)
		{
			return;
		}
		
		CFOTabPageModel *pModel = (CFOTabPageModel *)pDoc->m_pModelManager->m_arTabs[1];
		
		CFOTabPageView *pView = (CFOTabPageView *)m_wndTab.GetTabControl()->GetTab(0).GetWnd();
		pView->SetTabModel(pModel);
		m_wndTab.GetTabControl()->GetTab(0).SetTabModel(pModel);
		pView->SendMessage(0x0364);
		
		for(int x = 2;x < pDoc->m_pModelManager->GetTabCount(); x++)
		{
			CFOTabPageModel *pModel = (CFOTabPageModel *)pDoc->m_pModelManager->m_arTabs[x];
			if(pModel != NULL)
			{
				m_wndTab.InsertPage(pModel,NULL);
			}
		}
		
		pDoc->m_pModelManager->DeleteTab2(0);
		m_wndTab.SetActiveTab(0);
		
	}
}

BOOL FOFileExists(CString strFilePath)
{
	CFileStatus fs;
	return CFile::GetStatus(strFilePath, fs);
}

BOOL CChildFrame::LoadTemplateFile(const CString &strFile)
{
	CWaitCursor curWait;
	CUCCPrintDoc* pDoc = (CUCCPrintDoc*)GetActiveDocument();
	if (pDoc == NULL) return FALSE;
	
	if (!FOFileExists(strFile))
	{
		AfxMessageBox(_T("Sorry! the template file doesn't exist,please check!"));
		return FALSE;
	}
 
	CMBFileObj m_Obj;
	if(!m_Obj.OpenTemplateDocWithData(strFile))
	{
		AfxMessageBox(_T("Failed to open image file!"));
		return FALSE;
	}
	
	int nCount = m_Obj.pModelManager->GetTabCount();
	int nTotal = pDoc->m_pModelManager->GetTabCount();
	if(nCount < nTotal)
	{
		for(int x = 0; x < nCount; x++)
		{
			CFOTabPageModel *pModel = (CFOTabPageModel *)m_Obj.pModelManager->m_arTabs[x];
			CFOTabPageView *pWnd = (CFOTabPageView *)m_wndTab.GetTabControl()->GetTab(x).GetWnd();
			pModel->SetDataManager(m_Obj.pModelManager);
			pWnd->SetTabModel(pModel);
			
			m_wndTab.GetTabControl()->GetTab(x).SetTabModel(pModel);
			pWnd->SendMessage(0x0364);
			pWnd->FOPInvalidate();
		}
		
//		int nRemain = nTotal - nCount;
		for(int y = nCount; y < nTotal; y++)
		{
			m_wndTab.RemoveTab(y, FALSE);
			pDoc->m_pModelManager->DeleteTab2(y);
		}
		
		delete pDoc->m_pModelManager;
		pDoc->m_pModelManager = m_Obj.pModelManager;
		
		m_wndTab.SetModelManager(pDoc->m_pModelManager);
		m_wndTab.SetActiveTab(0);
	}
	else
	{
		for(int x = 0; x < nTotal; x++)
		{
			CFOTabPageModel *pModel = (CFOTabPageModel *)m_Obj.pModelManager->m_arTabs[x];
			CFOTabPageView *pWnd = (CFOTabPageView *)m_wndTab.GetTabControl()->GetTab(x).GetWnd();
			pModel->SetDataManager(m_Obj.pModelManager);
			pWnd->SetTabModel(pModel);
			
			m_wndTab.GetTabControl()->GetTab(x).SetTabModel(pModel);
			pWnd->SendMessage(0x0364);
			pWnd->FOPInvalidate();
		}
		
//		int nRemain = nCount - nTotal;
		for(int y = nTotal; y < nCount; y++)
		{
			CFOTabPageModel *pModel = (CFOTabPageModel *)m_Obj.pModelManager->m_arTabs[y];
			m_wndTab.InsertPage(pModel, NULL);
			CFOTabPageView *pWnd = (CFOTabPageView *)m_wndTab.GetTabControl()->GetTab(y).GetWnd();
			pModel->SetDataManager(m_Obj.pModelManager);
			pWnd->SetTabModel(pModel);
			m_wndTab.GetTabControl()->GetTab(y).SetTabModel(pModel);
			pWnd->SendMessage(0x0364);
			pWnd->FOPInvalidate();
		}
		
		delete pDoc->m_pModelManager;
		pDoc->m_pModelManager = m_Obj.pModelManager;
		
		m_wndTab.SetModelManager(pDoc->m_pModelManager);
		m_wndTab.SetActiveTab(0);
	}

	return TRUE;
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	lpcs;
	// TODO: Add your specialized code here and/or call the base class
	pContext->m_pNewViewClass = RUNTIME_CLASS(CUCCPrintView);

	// creates the tab window
	CUCCPrintDoc* pDoc = (CUCCPrintDoc*) pContext->m_pCurrentDoc;
	CFOTabPageModel *pModel = (CFOTabPageModel *)pDoc->m_pModelManager->InsertTab();
	VERIFY(m_wndTab.Create(this,pDoc->m_pModelManager,pContext));
	// next sheets
	m_wndTab.InsertPage(pModel,pContext);

	return TRUE;
}

void CChildFrame::OnFoAddNewpage() 
{
	// TODO: Add your command handler code here
	CUCCPrintDoc* pDoc = (CUCCPrintDoc*)GetActiveDocument();
	CFOTabPageModel *pModel = (CFOTabPageModel *)pDoc->m_pModelManager->InsertTab();
	m_wndTab.InsertPage(pModel,NULL);
}

void CChildFrame::OnFoRemovePage() 
{
	// TODO: Add your command handler code here
	CUCCPrintDoc* pDoc = (CUCCPrintDoc*) GetActiveDocument();
	int nCurrentTab = m_wndTab.GetTabControl()->m_nSelect;
	if(m_wndTab.RemoveTab(nCurrentTab))
	{
		pDoc->m_pModelManager->DeleteTab(nCurrentTab);
	}
}

void CChildFrame::OnMovePrevious() 
{
	// TODO: Add your command handler code here
	int nCurrentTab = m_wndTab.GetTabControl()->m_nSelect;
	if(nCurrentTab -1 >= 0)
	{
		m_wndTab.SetActiveTab(nCurrentTab -1);
	}
	else
	{
		m_wndTab.SetActiveTab(0);
	}
}

void CChildFrame::OnUpdateMovePrevious(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int nCurrentTab = m_wndTab.GetTabControl()->m_nSelect;
	int nCount = m_wndTab.GetTabControl()->GetTabCount();
	if(nCount == 1)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(nCurrentTab != 0);
	}
}

void CChildFrame::OnMoveNext() 
{
	// TODO: Add your command handler code here
	int nCurrentTab = m_wndTab.GetTabControl()->m_nSelect;
	int nCount = m_wndTab.GetTabControl()->GetTabCount();
	if(nCurrentTab +1 < nCount)
	{
		m_wndTab.SetActiveTab(nCurrentTab +1);
	}
	else
	{
		m_wndTab.SetActiveTab(nCount-1);
	}
}

void CChildFrame::OnUpdateMoveNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int nCurrentTab = m_wndTab.GetTabControl()->m_nSelect;
	int nCount = m_wndTab.GetTabControl()->GetTabCount();
	if(nCount == 1)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(nCurrentTab < (nCount-1));
	}
}

void CChildFrame::OnMbCreatepageCopy() 
{
	// TODO: Add your command handler code here
	CUCCPrintDoc* pDoc = (CUCCPrintDoc*)GetActiveDocument();
	CUCCPrintView* pView = (CUCCPrintView*)GetActiveView();
	// TODO: Add your command handler code here
	CString strCurPage;
	strCurPage = "";
	if(pView != NULL)
	{
		CExtTabModel *pModel = (CExtTabModel *)pView->GetCurrentModel();
		strCurPage = pModel->m_strCaption;
	}
	CMBEventEditDlg6 dlg;
	dlg.strPageName = strCurPage;
	if(dlg.DoModal() == IDOK)
	{
		CString strName = dlg.strPageName;
		if(!strName.IsEmpty())
		{
			CFOTabPageModel *pModel = (CFOTabPageModel *)pDoc->m_pModelManager->FindModel(strName);
			if(pModel != NULL)
			{
				CFODrawShapeSet *pList = pModel->GetFormObjects();
				pModel->ResetLinkNames(*pList);

				pModel->EndEditingBack();

				CFOTabPageModel *pNewModel = (CFOTabPageModel *)pModel->Copy();
				pNewModel->RestoreAllConnections();
				CFOTabPageModel *pModelX = (CFOTabPageModel *)pDoc->m_pModelManager->InsertTab(pNewModel);
				pModelX->m_strCaption = pDoc->m_pModelManager->GetUniquePageCaption();
				m_wndTab.InsertPage(pModelX,NULL);
			}
		}
	}
}

void CChildFrame::OnUpdateMbCreatepageCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI;
}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFOPMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	if(pParent->IsWindowVisible())
	{
		CView *pView = (CView *)FOGetActiveView();
		if(pView != NULL)
		{
			if(pView->IsKindOf(RUNTIME_CLASS(CUCCPrintView)))
				//		if(pParent->m_wndTableBar.m_TreeCtrl.GetItemCount() <= 0)
			{
				CUCCPrintView *pDrawView = static_cast<CUCCPrintView *>(pView);
				
				if(pDrawView->GetCurrentModel() != NULL)
					pParent->m_wndTableBar.InitShapes(pDrawView->GetCurrentModel());
			}
		}
		
	}
}
