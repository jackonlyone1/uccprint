// ExtTabModelManager.cpp: implementation of the CExtTabModelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UCCPrint.h"
#include "ExtTabModelManager.h"
#include <afxpriv.h>
#include "DbPrintGridShape.h"
#include "DBChartShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CExtTabModelManager construction/destruction

IMPLEMENT_SERIAL(CExtTabModelManager, CFOTabModelManager, 0)
CExtTabModelManager::CExtTabModelManager()
{
	//FOTO:Add you code here.
	m_nTotalRecord = 0;
	m_nRecordPostion = -1;
}

CExtTabModelManager::~CExtTabModelManager()
{
	//FOTO:Add you code here.
	listAllFormShapes.RemoveAll();
}

void CExtTabModelManager::Serialize(CArchive& ar)
{
	CFOTabModelManager::Serialize(ar);
	if(ar.IsStoring())
	{
		//FOTO:Add you code here.

	}
	else
	{
		//FOTO:Add you code here.

	}
}

CFOTabPageModel* CExtTabModelManager::InsertTabExt2(CFOTabPageModel* pInfo)
{
	ASSERT(pInfo != NULL);
	pInfo->SetDataManager(this);
	if (m_nCurrent == -1)
	{
		m_arTabs.SetAtGrow(m_nTabs, pInfo);
	}
	else
	{
		m_arTabs.InsertAt(m_nCurrent, pInfo, 1);
	}
	m_nTabs++;
	
	SetModifiedFlag();
	
	return pInfo;
}

/////////////////////////////////////////////////////////////////////////////
// Serialization
CFile* CExtTabModelManager::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
							 CFileException* pError)
{
	CMirrorFile* pFile = new CMirrorFile;
	ASSERT(pFile != NULL);
	if (!pFile->Open(lpszFileName, nOpenFlags, pError))
	{
		delete pFile;
		pFile = NULL;
	}
	return pFile;
}

void CExtTabModelManager::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CExtTabModelManager::OpenDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
			Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
	return TRUE;
}

BOOL CExtTabModelManager::SaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
	return TRUE;        // success
}

/////////////////////////////////////////////////////////////////////////////
// CExtTabModelManager diagnostics

#ifdef _DEBUG
void CExtTabModelManager::AssertValid() const
{
	CFOTabModelManager::AssertValid();
}

void CExtTabModelManager::Dump(CDumpContext& dc) const
{
	CFOTabModelManager::Dump(dc);
}
#endif //_DEBUG


CFOTabPageModel* CExtTabModelManager::InsertTab(CString szLabel)
{
	if(szLabel.IsEmpty())
	{
		szLabel = GetUniquePageCaption();
	}

	CExtTabModel* pInfo = new CExtTabModel;
	pInfo->SetDataManager(this);
	pInfo->m_strCaption = szLabel;
	
	if (m_nCurrent == -1)
	{
		m_arTabs.SetAtGrow(m_nTabs, pInfo);
	}
	else
	{
		m_arTabs.InsertAt(m_nCurrent, pInfo, 1);
	}
	m_nTabs++;

	SetModifiedFlag();
	
	NotifyObserver(0,STATIC_DOWNCAST(CObject,(CObject*)pInfo));

	return pInfo;
}

CFOTabPageModel* CExtTabModelManager::InsertTab(CFOTabPageModel* pInfo)
{
	ASSERT(pInfo != NULL);
	if(pInfo->m_strCaption.IsEmpty())
	{
		pInfo->m_strCaption = GetUniquePageCaption();
	}

	pInfo->SetDataManager(this);

	if (m_nCurrent == -1)
	{
		m_arTabs.SetAtGrow(m_nTabs, pInfo);
	}
	else
	{
		m_arTabs.InsertAt(m_nCurrent, pInfo, 1);
	}
	m_nTabs++;

	SetModifiedFlag();

	NotifyObserver(0,STATIC_DOWNCAST(CObject,(CObject*)pInfo));

	return pInfo;
}

void CExtTabModelManager::SaveTableData(CFOPTableShape *pTable)
{
	int nRows = pTable->GetRows();
	int nCols = pTable->GetColumns();
	
	for (int row = 0; row < nRows; row ++)
	{
		for (int col = 0; col < nCols; col ++)
		{
			CFOPTableCell* cellx = pTable->cell(row,col);
			cellx->m_strSave = cellx->GetChoiceText();
//			cellx->SetChoiceText(cellx->m_strSave);
		}
	}
}

void CExtTabModelManager::RestoreTableData(CFOPTableShape *pTable)
{
	int nRows = pTable->GetRows();
	int nCols = pTable->GetColumns();
	
	for (int row = 0; row < nRows; row ++)
	{
		for (int col = 0; col < nCols; col ++)
		{
			CFOPTableCell* cellx = pTable->cell(row,col);
			cellx->SetChoiceText(cellx->m_strSave);
		}
	}
}

void CExtTabModelManager::RestoreTableData2(CFOPTableShape *pTable)
{
	int nRows = pTable->GetRows();
	int nCols = pTable->GetColumns();
	
	for (int row = 0; row < nRows; row ++)
	{
		for (int col = 0; col < nCols; col ++)
		{
			CFOPTableCell* cellx = pTable->cell(row,col);
			cellx->SetObjectCaption(cellx->m_strSave);
		}
	}
}

void CExtTabModelManager::SaveTableData(FOXNewTableShape *pTable)
{
	int nRows = pTable->GetRows();
	int nCols = pTable->GetColumns();
	
	for (int row = 0; row < nRows; row ++)
	{
		for (int col = 0; col < nCols; col ++)
		{
			CFOPNewTableCell* cellx = pTable->cell(row,col);
			cellx->m_strSave = cellx->GetChoiceText();
			//			cellx->SetChoiceText(cellx->m_strSave);
		}
	}
}

void CExtTabModelManager::RestoreTableData(FOXNewTableShape *pTable)
{
	int nRows = pTable->GetRows();
	int nCols = pTable->GetColumns();
	
	for (int row = 0; row < nRows; row ++)
	{
		for (int col = 0; col < nCols; col ++)
		{
			CFOPNewTableCell* cellx = pTable->cell(row,col);
			cellx->SetChoiceText(cellx->m_strSave);
		}
	}
}

void CExtTabModelManager::RestoreTableData2(FOXNewTableShape *pTable)
{
	int nRows = pTable->GetRows();
	int nCols = pTable->GetColumns();
	
	for (int row = 0; row < nRows; row ++)
	{
		for (int col = 0; col < nCols; col ++)
		{
			CFOPNewTableCell* cellx = pTable->cell(row,col);
			cellx->SetObjectCaption(cellx->m_strSave);
		}
	}
}

void CExtTabModelManager::DoBackDBName()
{
	CFODrawShape *pDBShape = NULL;
	POSITION pos = listAllFormShapes.GetHeadPosition();
	while (pos != NULL) 
	{
		pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
		pDBShape->SetKeyId3(pDBShape->GetDBVarName());
	}
}

void CExtTabModelManager::ResetAllEFormShapes()
{
	CFODrawShape *pDBShape = NULL;
	POSITION pos = listAllFormShapes.GetHeadPosition();
	while (pos != NULL) 
	{
		pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
		if(!HAS_BASE(pDBShape, CDbPrintGridShape))
			pDBShape->SetDBVarName(pDBShape->GetKeyId3());
	}
}

void CExtTabModelManager::ResetAllEFormShapes2()
{
	CFODrawShape *pDBShape = NULL;
	POSITION pos = listAllFormShapes.GetHeadPosition();
	while (pos != NULL) 
	{
		pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
		if(!HAS_BASE(pDBShape, CDbPrintGridShape))
		{
			pDBShape->SetDBVarName(pDBShape->GetKeyId3());
		}

		if((pDBShape->GetType() != 651) && pDBShape->IsKindOf(RUNTIME_CLASS(CFOPEFormBaseShape)))
		{
			CFOPEFormBaseShape *pForm = static_cast<CFOPEFormBaseShape *>(pDBShape);
			pForm->SetCurrentText(pDBShape->GetKeyId3());
		}

		if(HAS_BASE(pDBShape, CFOPRichEditShape))
		{
			CFOPRichEditShape *pSub = (CFOPRichEditShape *)(pDBShape);
			pSub->ResetAllText();
		}

		if(HAS_BASE(pDBShape, CFOPTableShape))
		{
			CFOPTableShape *pTable = (CFOPTableShape *)(pDBShape);
			RestoreTableData2(pTable);
		}

		if(HAS_BASE(pDBShape, FOXNewTableShape))
		{
			FOXNewTableShape *pTable = (FOXNewTableShape *)(pDBShape);
			RestoreTableData2(pTable);
		}
	}
}

void CExtTabModelManager::SearchForAllEFormShapes()
{
	listAllFormShapes.RemoveAll();
	CFODrawShapeList m_List;
	for (int i = 0; i<m_arTabs.GetSize(); i++)
	{
		CExtTabModel *pTabPageModel = (CExtTabModel*)m_arTabs.GetAt(i);
		ASSERT(pTabPageModel);

		//		pTabPageModel->SearchForAllEFormShapes(m_List);
		pTabPageModel->SearchForEFormShapeEX(m_List);
		
	}

	CFODrawShape *pDBShape = NULL;
	POSITION pos = m_List.GetHeadPosition();
	while (pos != NULL) 
	{
		pDBShape = (CFODrawShape*)(m_List.GetNext(pos));
		listAllFormShapes.AddTail(pDBShape);
	}
}

CString XComputeCurrentTime()
{
	COleDateTime m_Time = COleDateTime::GetCurrentTime();
	CString strTemp;
	strTemp.Format(_T("%u:%u:%u"),m_Time.GetHour(),m_Time.GetMinute(),m_Time.GetSecond());
	return strTemp;
}

void XFOPFormatCOleDateTime(CString& strData, COleDateTime DateTime, int len)
{
	len;
	if(DateTime.GetStatus() != 0)
	{
		return;
	}
	int nYear = DateTime.GetYear();
	int nMonth = DateTime.GetMonth();
	int nDay = DateTime.GetDay();
	CString strYear;
	CString strMonth;
	CString strDay;
	strDay.Format(_T("%u"),nDay);
	strMonth.Format(_T("%u"),nMonth);
	strYear.Format(_T("%u"),nYear);
	if(strMonth.GetLength() <=1)
	{
		strMonth = _T("0") +strMonth;
	}
	if(strDay.GetLength() <=1)
	{
		strDay = _T("0")+strDay;
	}
	strData = _T("");
	if (DateTime.m_dt == 0) 
		return;
	strData.Format(_T("%s/%s/%u"),strMonth,strDay,nYear);
}

CString CExtTabModelManager::GetExpressValue(const CString &strExpName)
{
	COleDateTime m_Time = COleDateTime::GetCurrentTime();
	CString strData;
	XFOPFormatCOleDateTime(strData, m_Time, 0);
	CString strTime = XComputeCurrentTime();
	int nTotal = theApp.m_odbc.GetNumCols();   
	for (int i=0; i<nTotal; i++)
	{
		CString strCol;
		theApp.m_odbc.GetColName(i, &strCol);
		
		if(strExpName.CompareNoCase(strCol) == 0)
		{
			CString strCell;
			theApp.m_odbc.GetCell(i, m_nRecordPostion, strCell);
			
			return strCell;
		}
		else if(strExpName.CompareNoCase(_T("xdtDate")) == 0)
		{
			return strData;
		}
		else if(strExpName.CompareNoCase(_T("xdtTime")) == 0)
		{
			return strTime;
		}
	}
	
	return _T("");

}

void CExtTabModelManager::BeginPrint()
{
	m_nRecordPostion = -1;

	m_mapLabel2Record.RemoveAll();
	m_mapIndex2Offset.RemoveAll();
}

void CExtTabModelManager::EndPrint()
{
	m_nRecordPostion = -1;

	m_mapLabel2Record.RemoveAll();
	m_mapIndex2Offset.RemoveAll();
}

//	
int CExtTabModelManager::GetPrintCount()
{
	int nPageCount = 1;
	CFODrawShape* pDBShape = NULL;
	POSITION pos = listAllFormShapes.GetHeadPosition();
	while (pos != NULL) 
	{
		pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
		if(HAS_BASE(pDBShape, CDbPrintGridShape)) 
		{
			
			CDbPrintGridShape *pSub = (CDbPrintGridShape *)(pDBShape);
			nPageCount = max(nPageCount, pSub->CalcAllPages());
		}
	}

	return nPageCount;
}

//	
int CExtTabModelManager::GetPrintPageCount()
{
	int nPageCount = 1;
	CFODrawShape* pDBShape = NULL;
	POSITION pos = listAllFormShapes.GetHeadPosition();
	while (pos != NULL) 
	{
		pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
		if(HAS_BASE(pDBShape, CDbPrintGridShape)) 
		{
			
			CDbPrintGridShape *pSub = (CDbPrintGridShape *)(pDBShape);
			nPageCount = max(nPageCount, pSub->GetAllPrintPages());
		}
	}
	
	return nPageCount;
}

//	
//	
BOOL CExtTabModelManager::FillInFieldPrint(int nLabelIndex)
{
//////////////////////////////////////////////////////////////////////////
//
	int nRedordIndex = 0;
	BOOL nNeedAddNew = FALSE;
	if (FALSE == m_mapLabel2Record.Lookup(nLabelIndex, nRedordIndex))
	{//
		nNeedAddNew = TRUE;
		//	
		if (FALSE == m_mapLabel2Record.Lookup(nLabelIndex-1, nRedordIndex)) {
			nRedordIndex = 0;
		} else {//	
			nRedordIndex ++;
		}
	}
//////////////////////////////////////////////////////////////////////////
	int nIndex = nRedordIndex;
//////////////////////////////////////////////////////////////////////////

	if (nIndex < 0) {
		nIndex = 0;
	}

	int nCount = m_nTotalRecord;
	if( nCount<= 0) {
		return TRUE;
	}

	BOOL bReturn = TRUE;
	if (nIndex >= nCount) {
		bReturn = FALSE;
	}
	if (nIndex >= nCount) {
		nIndex = nCount-1;
	}

	DoBackDBName();

	FOP_REPLACE_SET theSet;
	theSet.bLastWordMayNotHavePunct=FALSE;
	theSet.bStrict=FALSE;
	
	theSet.bCheckOnlyWords=FALSE;
	
	theSet.bLastWordMayNotHavePunct=FALSE;
	
	theSet.bCaseSensetive=FALSE;
	theSet.bOverWriteFile=FALSE;
	theSet.bReplaceLFWithCRLF=FALSE;
	theSet.bReplaceCRLFWithLF=FALSE;
	
	CFOPRelaceText theR(theSet); //call the parametrized constructor to send the options

	COleDateTime m_Time = COleDateTime::GetCurrentTime();
	CString strData;
	XFOPFormatCOleDateTime(strData, m_Time, 0);

	CString strTime = XComputeCurrentTime();

//
	{
		CFODrawShape* pDBShape = NULL;
		POSITION pos = listAllFormShapes.GetHeadPosition();
		while (pos != NULL) 
		{
			pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
			
			if(HAS_BASE(pDBShape, CDbPrintGridShape))
			{
				CDbPrintGridShape *pSub = (CDbPrintGridShape *)(pDBShape);
				pSub->strBackup = pSub->m_strSQL;
			}
			else if(HAS_BASE(pDBShape, CDBChartShape))
			{
				CDBChartShape *pSub = (CDBChartShape *)(pDBShape);
				pSub->strBackup = pSub->m_strSQL;
			}
			else if(HAS_BASE(pDBShape, CFOPRichEditShape))
			{
				CFOPRichEditShape *pSub = (CFOPRichEditShape *)(pDBShape);
				pSub->strBackup = pSub->GetCurrentText();
			}
			else if(HAS_BASE(pDBShape, CFOPTableShape))
			{
				CFOPTableShape *pTable = (CFOPTableShape *)(pDBShape);
				SaveTableData(pTable);
			}
			else if(HAS_BASE(pDBShape, FOXNewTableShape))
			{
				FOXNewTableShape *pTable = (FOXNewTableShape *)(pDBShape);
				SaveTableData(pTable);
			}

		}
	//	RichEdit 
		pos = listAllFormShapes.GetHeadPosition();
		while (pos != NULL) 
		{
			pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
			
			if(HAS_BASE(pDBShape, CFOPRichEditShape))
			{
				CFOPRichEditShape *pSub = (CFOPRichEditShape *)(pDBShape);
				pSub->ResetAllText();
				pSub->ChangeExpressValue();
			}
			
		}
	}

//	
	TCHAR *pCharStop = NULL;
	m_nRecordPostion = nRedordIndex;
	theApp.m_odbc.GotoRecord(nRedordIndex);
	
	int nTotal = theApp.m_odbc.GetNumCols();   
	for (int i=0; i<nTotal; i++)
	{
		CString strCol;
		theApp.m_odbc.GetColName(i, &strCol);

		CFODrawShape* pDBShape = NULL;
		POSITION pos = listAllFormShapes.GetHeadPosition();
		while (pos != NULL) 
		{
			pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));

			if(!HAS_BASE(pDBShape, CFOPRichEditShape))
			{
				if(HAS_BASE(pDBShape, CFOPTableShape))
				{
					CFOPTableShape *pTable = (CFOPTableShape *)(pDBShape);
					int nRows = pTable->GetRows();
					int nCols = pTable->GetColumns();
					
					for (int row = 0; row < nRows; row ++)
					{
						for (int col = 0; col < nCols; col ++)
						{
							CFOPTableCell* cellx = pTable->cell(row,col);
							CString strDBName = cellx->GetChoiceText();
							if(!strDBName.IsEmpty())
							{
								CString strCell;
								theApp.m_odbc.GetCell(i, nIndex, strCell);
								
								//	theR.SetFileName(sFilePath);
								theR.SetReplacementString(strCell);
								theR.SetSearchString(strCol);
								strDBName = theR.Process(strDBName);
								
								theR.SetReplacementString(strData);
								theR.SetSearchString(_T("xdtDate"));
								strDBName = theR.Process(strDBName);
								
								theR.SetReplacementString(strTime);
								theR.SetSearchString(_T("xdtTime"));
								strDBName = theR.Process(strDBName);
								
								cellx->SetObjectCaption(strDBName);
								cellx->SetChoiceText(strDBName);
							}
							
						}
					}
					
				}
				else if(HAS_BASE(pDBShape, FOXNewTableShape))
				{
					FOXNewTableShape *pTable = (FOXNewTableShape *)(pDBShape);
					int nRows = pTable->GetRows();
					int nCols = pTable->GetColumns();
					
					for (int row = 0; row < nRows; row ++)
					{
						for (int col = 0; col < nCols; col ++)
						{
							CFOPNewTableCell* cellx = pTable->cell(row,col);
							CString strDBName = cellx->GetChoiceText();
							if(!strDBName.IsEmpty())
							{
								CString strCell;
								theApp.m_odbc.GetCell(i, nIndex, strCell);
								
								//	theR.SetFileName(sFilePath);
								theR.SetReplacementString(strCell);
								theR.SetSearchString(strCol);
								strDBName = theR.Process(strDBName);
								
								theR.SetReplacementString(strData);
								theR.SetSearchString(_T("xdtDate"));
								strDBName = theR.Process(strDBName);
								
								theR.SetReplacementString(strTime);
								theR.SetSearchString(_T("xdtTime"));
								strDBName = theR.Process(strDBName);
								
								cellx->SetObjectCaption(strDBName);
								cellx->SetChoiceText(strDBName);
							}
							
						}
					}
				}
				else if(!HAS_BASE(pDBShape, CDbPrintGridShape))
				{
					CString strDBName = pDBShape->GetDBVarName();
					if(!strDBName.IsEmpty())
					{
						CString strCell;
						theApp.m_odbc.GetCell(i, nIndex, strCell);
						
						//	theR.SetFileName(sFilePath);
						theR.SetReplacementString(strCell);
						theR.SetSearchString(strCol);
						strDBName = theR.Process(strDBName);
						
						theR.SetReplacementString(strData);
						theR.SetSearchString(_T("xdtDate"));
						strDBName = theR.Process(strDBName);
						
						theR.SetReplacementString(strTime);
						theR.SetSearchString(_T("xdtTime"));
						strDBName = theR.Process(strDBName);
						
						if(HAS_BASE(pDBShape, CFOPEFormBaseShape))
						{
							CFOPEFormBaseShape *pForm = static_cast<CFOPEFormBaseShape *>(pDBShape);
							pForm->SetCurrentText(strDBName);
						}
						else
						{
							float value = (float)_tcstod(strDBName.GetBuffer(strDBName.GetLength()), &pCharStop);
							
							pDBShape->SetCurrentValue(value);
						}
						pDBShape->SetDBVarName(strDBName);
					}
					
				}
				else
				{
//					CDbPrintGridShape *pSub = (CDbPrintGridShape *)(pDBShape);
// 					CString strSql = pSub->m_strSQL;
// 					strSql.TrimLeft();
// 					strSql.TrimRight();
// 					if(!strSql.IsEmpty())
// 					{
// 						CString strCell;
// 						theApp.m_odbc.GetCell(i, nIndex, strCell);
// 						theR.SetReplacementString(strCell);
// 						theR.SetSearchString(_T("$") + strCol + _T("$"));
// 						pSub->m_strSQL = theR.Process(strSql);
// 					}
				}
			}
		}
	}

//	
	{
		CFODrawShape* pDBShape = NULL;
		POSITION pos = listAllFormShapes.GetHeadPosition();
		while (pos != NULL) 
		{
			pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
			if(HAS_BASE(pDBShape, CDbPrintGridShape)) 
			{
				
				CDbPrintGridShape *pSub = (CDbPrintGridShape *)(pDBShape);
				CString strSql = pSub->m_strSQL;
				int nStart = strSql.Find(_T("$"));
				int nEnd = strSql.ReverseFind('$');
				CString strField = strSql.Mid(nStart+1, nEnd-nStart-1);
				CString strReplace = strSql.Mid(nStart, nEnd-nStart+1);
				CString strValue = GetExpressValue(strField);
				if (-1 != nStart && -1 != nEnd) {
					strSql.Replace(strReplace, strValue);
				}
				pSub->m_strSQL = strSql;
			}
		}
	}

//	
//////////////////////////////////////////////////////////////////////////
	if (TRUE == nNeedAddNew)
	{
		int nPrintCount = GetPrintCount();
		for (int i=0; i<nPrintCount; i++)
		{
			m_mapLabel2Record[nLabelIndex + i] = nRedordIndex;
			m_mapIndex2Offset[nLabelIndex + i] = i;
		}
	}
	
	//
	int nRecordOffset = 0;
	if (FALSE == m_mapLabel2Record.Lookup(nLabelIndex, nRedordIndex)) {
		ASSERT(FALSE);
	}
	if (FALSE == m_mapIndex2Offset.Lookup(nLabelIndex, nRecordOffset)) {
		ASSERT(FALSE);
	}
//////////////////////////////////////////////////////////////////////////

	{
		CFODrawShape* pDBShape = NULL;
		POSITION pos = listAllFormShapes.GetHeadPosition();
		while (pos != NULL) 
		{
			pDBShape = (CFODrawShape*)(listAllFormShapes.GetNext(pos));
			
			if(HAS_BASE(pDBShape, CDbPrintGridShape))
			{
				CDbPrintGridShape *pSub = (CDbPrintGridShape *)(pDBShape);
				pSub->DoFillData(nRecordOffset);
				pSub->m_strSQL = pSub->strBackup;
			}
			else if(HAS_BASE(pDBShape, CDBChartShape))
			{
				CDBChartShape *pSub = (CDBChartShape *)(pDBShape);
				pSub->DoFillData();
				pSub->m_strSQL = pSub->strBackup;
			}
			else if(HAS_BASE(pDBShape, CFOPRichEditShape))
			{
				CFOPRichEditShape *pSub = (CFOPRichEditShape *)(pDBShape);
				pSub->SetCurrentText(pSub->strBackup);
				pSub->SetWindowText(pSub->strBackup);
				
			}
			else if(HAS_BASE(pDBShape, CFOPTableShape))
			{
				CFOPTableShape *pTable = (CFOPTableShape *)(pDBShape);
				RestoreTableData(pTable);
			}
			else if(HAS_BASE(pDBShape, FOXNewTableShape))
			{
				FOXNewTableShape *pTable = (FOXNewTableShape *)(pDBShape);
				RestoreTableData(pTable);
			}
		}
	}

//
	ResetAllEFormShapes();

	return bReturn;
}
