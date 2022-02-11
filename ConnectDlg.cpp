// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UCCPrint.h"
#include "resource.h"
#include "ConnectDlg.h"
#include "ODBCAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// one time init
	m_nOpenType = CRecordset::dynaset;
	m_sDataSource = _T("");
	bWithSubReport = FALSE;
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
	DDX_Control(pDX, IDC_LST_DATA, m_lstData);
	DDX_Control(pDX, IDC_COMBO_COLUMN, m_colList);
	DDX_Control(pDX, IDC_SQLLIST, m_sqlList);
	DDX_Control(pDX, IDC_SQLEDIT, m_sqlEdit);
	DDX_Control(pDX, IDC_DSNCOMBO, m_dsnCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_BN_CLICKED(IDC_RADIODYNASET, OnRadiodynaset)
	ON_BN_CLICKED(IDC_RADIOSNAPSHOT, OnRadiosnapshot)
	ON_CBN_SELCHANGE(IDC_DSNCOMBO, OnSelchangeDsncombo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_CBN_SELCHANGE(IDC_SQLLIST, OnSelchangeSqllist)
	ON_BN_CLICKED(IDC_BROWSEBUTTON, OnBrowsebutton)
	ON_CBN_SELCHANGE(IDC_COMBO_COLUMN, OnSelchangeComboColumn)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, OnButtonExecute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers

void CConnectDlg::InitCombo(const CString &strDNS) 
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

	if(table == NULL)
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
}

BOOL BDGetDataSourceNames(HANDLE &henv, CString &sDSN)
{   
	UCHAR szDSN[SQL_MAX_DSN_LENGTH+1];
	UCHAR sDescription[255];
	SWORD wDirection = SQL_FETCH_FIRST;         
	SWORD wLenDSN, wLenDesc;	
	
	if (henv == NULL)
	{
		SQLAllocEnv(&henv);
	} else
	{
		wDirection = SQL_FETCH_NEXT;         
	}
	
	if (SQLDataSources(henv, wDirection, szDSN, sizeof(szDSN), &wLenDSN, sDescription, sizeof(sDescription),
		&wLenDesc) == SQL_SUCCESS)
	{
		sDSN = szDSN;
		return TRUE;
	} else
	{                   
		SQLFreeEnv(henv);
		return FALSE;
	};
}

void CConnectDlg::InitDataSources()
{
	HANDLE henv = NULL;
	CString strDSN;   
	int index;
	
	CString sDefault = AfxGetApp()->GetProfileString(_T("Database"),_T("Default"));
	
	m_dsnCombo.ResetContent();
	
	// Load the list of data sources into the combo box
	
	while (BDGetDataSourceNames(henv, strDSN))//, theApp.m_sUser, theApp.m_sPassword))
	{   
		CString sDSN = strDSN;
		
		index = m_dsnCombo.AddString(strDSN);
		m_dsnCombo.SetItemData(index, 0);
		
		if (sDSN.CompareNoCase(sDefault) == 0) 
			m_dsnCombo.SetCurSel(index);
		
		// If the data source is the default data source name specified then
		// select automatically
		
		if (sDSN.CompareNoCase(m_sDataSource) == 0) 
		{
			m_dsnCombo.SetCurSel(index);         
			OnOK();
		}
		
	}   
	
	if (m_dsnCombo.GetCurSel() == CB_ERR)
	{
		m_dsnCombo.SetCurSel(m_dsnCombo.GetCount()-1);   
	}

	m_dsnCombo.SetCurSel(-1);   
}

BOOL CConnectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitDataSources();

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

	m_dsnCombo.SetWindowText(m_strDSN);
	m_sqlEdit.SetWindowText(m_strSQL);
	
	if(!theApp.m_strDsn.IsEmpty())
	{
		m_dsnCombo.SelectString(-1, theApp.m_strDsn);
	}
	

	int pos = m_dsnCombo.GetCurSel();
	if(-1 != pos)
	{
		m_dsnCombo.GetLBText(pos,m_strDSN);
		InitCombo(theApp.m_strDsn);
	}

	if(bWithSubReport)
	{
		GetDlgItem(IDC_DSNCOMBO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BROWSEBUTTON)->EnableWindow(FALSE);
	}

	LONG lStyle = m_lstData.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT;
	m_lstData.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);
	
	m_lstData.SetColumnWidth(0, LVSCW_AUTOSIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnectDlg::OnRadiodynaset() 
{
	// TODO: Add your control notification handler code here
	m_nOpenType = CRecordset::dynaset;
}

void CConnectDlg::OnRadiosnapshot() 
{
	// TODO: Add your control notification handler code here
	m_nOpenType = CRecordset::snapshot;
}

BOOL FOCheck(CDatabase *pDb,HSTMT &hstmt,RETCODE nRetCode)
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

BOOL FOVerifySQL(CDatabase *pDb,CString szSQL,CString &szError)
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
	if (!FOCheck(pDb,hstmt,nRetCode))
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
	if (!FOCheck(pDb,hstmt,nRetCode))
	{
		CDBException e(nRetCode);
		e.BuildErrorString(pDb, hstmt);
		szError = e.m_strError;

		return FALSE;
	}
	return TRUE;
}

void CConnectDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_dsnCombo.GetWindowText(m_strDSN);
	m_sqlEdit.GetWindowText(m_strSQL);
	if(m_strDSN.IsEmpty())
	{
		m_dsnCombo.SetFocus();
		return;
	}

	if(m_strSQL.IsEmpty())
	{
		m_sqlEdit.SetFocus();
		return;
	}

	CString szSQL,szError;
	szSQL =   m_strSQL;
	CFOODBCAccess dbnew;
	dbnew.Connect(m_strDSN);
	
	if(!FOVerifySQL(dbnew.GetCDatabase(),szSQL,szError)) 
	{ 
		//Give Error Message
		AfxMessageBox(_T("The SQL syntax is not correct, please check it and try again!"), MB_OK|MB_ICONINFORMATION);
		m_sqlEdit.SetFocus();
		return;
	}

	theApp.m_strDsn = m_strDSN;

	CDialog::OnOK();
}

void CConnectDlg::OnSelchangeDsncombo() 
{
	// TODO: Add your control notification handler code here

	int pos = m_dsnCombo.GetCurSel();
	if(-1 != pos)
	{
		m_dsnCombo.GetLBText(pos,m_strDSN);
		InitCombo(m_strDSN);
	}

	m_sqlEdit.SetWindowText(_T(""));
}

void CConnectDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	CString strX;
	if(m_pOdbc->ImportFile(strX, this->m_hWnd)) 
	{
		InitCombo(strX);
	}	
	
	m_strDSN = strX;
	
	if(!m_strDSN.IsEmpty())
	{
		CStringArray *strArray = &((CUCCPrintApp*)AfxGetApp())->m_arrStrDsn;
		strArray->Add(m_strDSN);
		m_dsnCombo.SetCurSel(m_dsnCombo.AddString(m_strDSN));
	}
}

void CConnectDlg::OnSelchangeSqllist() 
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
			dbnew.Connect(m_strDSN);
			
			dbnew.QueryOpenColumns(strText);
			CFOColumns* table;
			dbnew.GetColumns(table);
			
			m_colList.ResetContent();

			CString sqlString;
			//Loop through to add them to the combo box:
			for(int h = 0; h < table->GetRecordCount(); h++)
			{
				sqlString.Format(_T("%s"),table->m_strColumnName);
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

void CConnectDlg::OnBrowsebutton() 
{
	// TODO: Add your control notification handler code here
	
	if(FOP_SUCCESS == m_pOdbc->Browse(this->m_hWnd)) 
	{
	}
	m_strDSN = *m_pOdbc->GetConnectString();
	if(!m_strDSN.IsEmpty()) 
	{
		CStringArray *strArray = &((CUCCPrintApp*)AfxGetApp())->m_arrStrDsn;
		strArray->Add(m_strDSN);
		m_dsnCombo.SetCurSel(m_dsnCombo.AddString(m_strDSN));

		InitCombo(m_strDSN);
	}
}

void CConnectDlg::OnSelchangeComboColumn() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO_COLUMN);
	int nCur = pBox->GetCurSel();
	if(nCur >= 0)
	{
		CString strObjName;
		pBox->GetLBText(nCur,strObjName);
		
		m_sqlEdit.ReplaceSel(_T(" [") + strObjName + _T("],"), TRUE);
	}
	
}

void CConnectDlg::ExecuteSql()
{
	ResetDataListControl();
	
	m_dsnCombo.GetWindowText(m_strDSN);
	m_sqlEdit.GetWindowText(m_strSQL);
	if(m_strDSN.IsEmpty())
	{
		m_dsnCombo.SetFocus();
		return;
	}
	
	if(m_strSQL.IsEmpty())
	{
		m_sqlEdit.SetFocus();
		return;
	}

	if (UpdateData()
		&& !m_strDSN.IsEmpty())
	{
		CClientDC dc(this);
		
		try
		{
			CODBCDynamic odbcDynamic(m_strDSN, _T(""), _T(""));
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
		}
		catch (CUserException* pe)
		{
			pe->ReportError();
			pe->Delete();
		}
	}
}

void CConnectDlg::ResetDataListControl()
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

void CConnectDlg::OnButtonExecute() 
{
	// TODO: Add your control notification handler code here
	ExecuteSql();
}
