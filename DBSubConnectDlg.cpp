// DBSubConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uccprint.h"
#include "DBSubConnectDlg.h"

#include "ODBCAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBSubConnectDlg dialog


CDBSubConnectDlg::CDBSubConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBSubConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBSubConnectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// one time init
	m_nOpenType = CRecordset::dynaset;
	m_sDataSource = _T("");
	bWithSubReport = FALSE;

	strSub = _T("");
}


void CDBSubConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBSubConnectDlg)
	DDX_Control(pDX, IDC_LST_DATA, m_lstData);
	DDX_Control(pDX, IDC_COMBO_COLUMN, m_colList);
	DDX_Control(pDX, IDC_SQLLIST, m_sqlList);
	DDX_Control(pDX, IDC_SQLEDIT, m_sqlEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBSubConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CDBSubConnectDlg)
	ON_BN_CLICKED(IDC_RADIODYNASET, OnRadiodynaset)
	ON_BN_CLICKED(IDC_RADIOSNAPSHOT, OnRadiosnapshot)
	ON_CBN_SELCHANGE(IDC_SQLLIST, OnSelchangeSqllist)
	ON_CBN_SELCHANGE(IDC_COMBO_COLUMN, OnSelchangeComboColumn)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, OnButtonExecute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBSubConnectDlg message handlers

void CDBSubConnectDlg::InitCombo(const CString &strDNS) 
{
	// empty the array of SQL statements

	m_strSQLArray.RemoveAll();
	m_sqlList.ResetContent();
	m_colList.ResetContent();

	if(strDNS.IsEmpty())
	{
		return;
	}

	CFOODBCAccess dbnew;
	dbnew.Connect(strDNS);
	
	dbnew.QueryOpenTables();
	CFOTables* table = NULL;
	dbnew.GetTables(table);
	if(strDNS.IsEmpty())
	{
		return;
	}
	
	CString sqlString;
	//Loop through to add them to the combo box:
	for(int h = 0; h < table->GetRecordCount(); h++)
	{
		sqlString.Format(_T("%s"),table->m_strTableName);
		m_strSQLArray.Add(sqlString);
		m_sqlList.AddString(sqlString);
		//Move to the next table name:
		table->MoveNext();
	}
	
	CComboBox *pBox2 = (CComboBox *)GetDlgItem(IDC_COMBO_DB_MAIN);
	for(int x = 0; x < theApp.m_dbcols.GetSize(); x++)
	{
		sqlString.Format(_T("$%s$"),theApp.m_dbcols.GetAt(x));
		pBox2->AddString(sqlString);
	}
	
	pBox2->AddString(_T("xdtTime"));
	pBox2->AddString(_T("xdtDate"));

}

BOOL CDBSubConnectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CButton *cbSnapshot = (CButton *) GetDlgItem(IDC_RADIOSNAPSHOT);
	CButton *cbDynaset = (CButton *) GetDlgItem(IDC_RADIODYNASET);

	if(m_nOpenType == CRecordset::snapshot) 
	{
		cbDynaset->SetCheck(0);
		cbSnapshot->SetCheck(1);
	}
	else 
	{
		cbDynaset->SetCheck(1);
		cbSnapshot->SetCheck(0);
	}		

	m_sqlEdit.SetWindowText(m_strSQL);
	

	{
		InitCombo(theApp.m_strDsn);
	}

	if(bWithSubReport)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BROWSEBUTTON)->EnableWindow(FALSE);
	}

	LONG lStyle = m_lstData.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT;
	m_lstData.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);
	
	m_lstData.SetColumnWidth(0, LVSCW_AUTOSIZE);

	if(!strSub.IsEmpty())
	{
		CStringArray m_States;
		FOStringToStringArray(strSub, _T(","), m_States);
		if(m_States.GetSize() == 2)
		{
			CString str1 = m_States.GetAt(0);
			CString str2 = m_States.GetAt(1);
			GetDlgItem(IDC_COMBO_COLUMN)->SetWindowText(str1);
			GetDlgItem(IDC_COMBO_DB_MAIN)->SetWindowText(str2);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBSubConnectDlg::ExecuteSql()
{
	ResetDataListControl();
	
	m_sqlEdit.GetWindowText(m_strSQL);
	
	if(m_strSQL.IsEmpty())
	{
		m_sqlEdit.SetFocus();
		return;
	}

	if (UpdateData()
		&& !theApp.m_strDsn.IsEmpty())
	{
		CClientDC dc(this);
		
		try
		{
			CODBCDynamic odbcDynamic(theApp.m_strDsn, _T(""), _T(""));
			odbcDynamic.ExecuteSQL(m_strSQL);
			
			CODBCRecordArray* pODBCRecordArray = &odbcDynamic.m_ODBCRecordArray;
			
			for (int iRecord = 0; iRecord < pODBCRecordArray->GetSize(); iRecord++)
			{
				POSITION pos;
				CString strColName;
				CDBVariantEx* pvarValue;
				char szValue[255];
				
				int iCol = 0;
				CODBCRecord* pODBCRecord = (*pODBCRecordArray)[iRecord];
				for (pos = pODBCRecord->GetStartPosition(); pos != NULL;)
				{
					pODBCRecord->GetNextAssoc(pos, strColName, pvarValue);
					
					if (0 == iRecord)
					{
						CSize size = dc.GetTextExtent(strColName.GetBuffer(strColName.GetLength()));
						m_lstData.InsertColumn(iCol, strColName, LVCFMT_LEFT, size.cx + 30, iCol);
					}
					
					if (pvarValue)
					{
						pvarValue->GetStringValue(szValue);
						if (0 < strlen(szValue))
						{
							if (0 == iCol)
							{
								iRecord = m_lstData.InsertItem(iRecord, szValue, iCol);
							}
							else
							{
								m_lstData.SetItemText(iRecord, iCol, szValue);
							}
							
							iCol++;
						}
					}
				}
			}

			CString strTitle;
			strTitle.Format(_T("Total: %u"), pODBCRecordArray->GetSize());
			SetWindowText(strTitle);

		}
		catch (CUserException* pe)
		{
			pe->ReportError();
			pe->Delete();
		}
	}
}

void CDBSubConnectDlg::ResetDataListControl()
{
	m_lstData.DeleteAllItems();
	int iNbrOfColumns = 0;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_lstData.GetDlgItem(0);
	if (pHeader)
	{
		iNbrOfColumns = pHeader->GetItemCount();
	}

	for (int i = iNbrOfColumns; i >= 0; i--)
	{
		m_lstData.DeleteColumn(i);
	}
}

void CDBSubConnectDlg::OnRadiodynaset() 
{
	// TODO: Add your control notification handler code here
	m_nOpenType = CRecordset::dynaset;
}

void CDBSubConnectDlg::OnRadiosnapshot() 
{
	// TODO: Add your control notification handler code here
	m_nOpenType = CRecordset::snapshot;
}

BOOL FOCheck2(CDatabase *pDb,HSTMT &hstmt,RETCODE nRetCode)
{
	switch (nRetCode)
	{
	case SQL_SUCCESS_WITH_INFO:
#ifdef _DEBUG
		if (afxTraceFlags & traceDatabase)
		{
			CDBException e(nRetCode);
			TRACE0("Warning: ODBC Success With Info, ");
			e.BuildErrorString(pDb, hstmt);
		}
#endif
		
		// Fall through
		
	case SQL_SUCCESS:
	case SQL_NO_DATA_FOUND:
	case SQL_NEED_DATA:
		return TRUE;
	}
	
	return FALSE;
}

BOOL FOVerifySQL2(CDatabase *pDb,CString szSQL,CString &szError)
{
	USES_CONVERSION;
	szSQL.TrimLeft();
	szSQL.TrimRight();
	if(szSQL.IsEmpty())
		return TRUE;
	HSTMT hstmt = SQL_NULL_HSTMT;
	ASSERT(pDb->IsOpen()); 
	RETCODE	nRetCode;
	AFX_SQL_SYNC(::SQLAllocStmt(pDb->m_hdbc, &hstmt));
	if (!FOCheck2(pDb,hstmt,nRetCode))
	{
		CDBException e(nRetCode);
		e.BuildErrorString(pDb, hstmt);
		szError = 
			e.m_strError; 
//#ifdef _DEBUG 
//		if (afxTraceFlags & traceDatabase)
//			TRACE0(e.m_strError);
//#endif
	}
	pDb->OnSetOptions(hstmt);
	
	AFX_ODBC_CALL(::SQLPrepare(hstmt,
		(UCHAR*)T2A(szSQL.GetBuffer(szSQL.GetLength())), SQL_NTS));
	szSQL.ReleaseBuffer();
	if (!FOCheck2(pDb,hstmt,nRetCode))
	{
		CDBException e(nRetCode);
		e.BuildErrorString(pDb, hstmt);
		szError = e.m_strError;

		return FALSE;
	}
	return TRUE;
}

void CDBSubConnectDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_sqlEdit.GetWindowText(m_strSQL);

	if(m_strSQL.IsEmpty())
	{
		m_sqlEdit.SetFocus();
		return;
	}

	CString szSQL,szError;
	szSQL =   m_strSQL;
	CFOODBCAccess dbnew;
	dbnew.Connect(theApp.m_strDsn);
	
	if(!FOVerifySQL2(dbnew.GetCDatabase(),szSQL,szError)) 
	{ 
		//Give Error Message
		AfxMessageBox(_T("The SQL syntax is not correct, please check it and try again!"), MB_OK|MB_ICONINFORMATION);
		m_sqlEdit.SetFocus();
		return;
	}

	CString str1;
	CString str2;
	GetDlgItem(IDC_COMBO_COLUMN)->GetWindowText(str1);
	GetDlgItem(IDC_COMBO_DB_MAIN)->GetWindowText(str2);

	if(!str1.IsEmpty() && !str2.IsEmpty())
	{
		CStringArray m_Files;
		m_Files.Add(str1);
		m_Files.Add(str2);
		
		CString strState;
		FOStringArrayToString(m_Files, _T(","), strState);
		
		strSub = strState;
	}
	else
	{
		strSub = _T("");
	}
	
	CDialog::OnOK();
}

void CDBSubConnectDlg::OnSelchangeSqllist() 
{
	// TODO: Add your control notification handler code here

	int pos = m_sqlList.GetCurSel();
	if(-1 != pos)
	{
		CString strText;
		strText = m_strSQL;
		m_sqlList.GetLBText(pos,strText);
		if(!strText.IsEmpty())
		{
			CFOODBCAccess dbnew;
			dbnew.Connect(theApp.m_strDsn);
			
			dbnew.QueryOpenColumns(strText);
			CFOColumns* table;
			dbnew.GetColumns(table);
			
			m_colList.ResetContent();

			CString sqlString;
			//Loop through to add them to the combo box:
			for(int h = 0; h < table->GetRecordCount(); h++)
			{
				sqlString.Format(_T("[%s]"),table->m_strColumnName);
				m_strSQLArray.Add(sqlString);
				m_colList.AddString(sqlString);
				//Move to the next table name:
				table->MoveNext();
			}
		}

		CString sqlString;
		sqlString.Format(_T("Select * FROM [%s]"),strText);
		m_strSQL = sqlString;
		
		m_sqlEdit.SetWindowText(m_strSQL);
	}
	
}
// 
// void CDBSubConnectDlg::OnBrowsebutton() 
// {
// 	// TODO: Add your control notification handler code here
// 	
// 	if(FOP_SUCCESS == m_pOdbc->Browse(this->m_hWnd)) 
// 	{
// 	}
// 	m_strDSN = *m_pOdbc->GetConnectString();
// 	if(!m_strDSN.IsEmpty()) 
// 	{
// 		CStringArray *strArray = &((CUCCPrintApp*)AfxGetApp())->m_arrStrDsn;
// 		strArray->Add(m_strDSN);
// 		m_dsnCombo.SetCurSel(m_dsnCombo.AddString(m_strDSN));
// 
// 		InitCombo(m_strDSN);
// 	}
// }

void CDBSubConnectDlg::OnSelchangeComboColumn() 
{
	// TODO: Add your control notification handler code here
}

void CDBSubConnectDlg::OnButtonExecute() 
{
	// TODO: Add your control notification handler code here
	ExecuteSql();		
}
