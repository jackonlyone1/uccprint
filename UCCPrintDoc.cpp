// UCCPrintDoc.cpp : implementation of the CUCCPrintDoc class
//

#include "stdafx.h"
#include "UCCPrint.h"

#include "UCCPrintDoc.h"
#include "mapi.h"
#include <afxpriv.h>
#include "SVSaveAsTemplateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintDoc

IMPLEMENT_DYNCREATE(CUCCPrintDoc, COleDocument)

BEGIN_MESSAGE_MAP(CUCCPrintDoc, COleDocument)
	//{{AFX_MSG_MAP(CUCCPrintDoc)
	ON_COMMAND(ID_FILE_SAVE_AS_TEMPLATE, OnFileSaveAsTemplate)
	ON_COMMAND(ID_MAIL_TO, OnMailTo)
	//}}AFX_MSG_MAP
#ifdef OLE_CLIENT_SUPPORT	
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintDoc construction/destruction

CUCCPrintDoc::CUCCPrintDoc()
{
	// TODO: add one-time construction code here
	//E-XD++ Library add lines.
	m_pModelManager = new CExtTabModelManager;
	bNewDocument = FALSE;
	bOpenDocument = FALSE;
	// Use OLE compound files
//	EnableCompoundFile();
	
	EnableConnections();
	
	EnableAutomation();
	strFile = _T("");
	AfxOleLockApp();
}

CUCCPrintDoc::~CUCCPrintDoc()
{
	//E-XD++ Library add lines.
	AfxOleUnlockApp();
	if(m_pModelManager != NULL)
	{
		delete m_pModelManager;
	}
}

BOOL CUCCPrintDoc::OnNewDocument()
{
	bNewDocument = TRUE;

	if (!COleDocument::OnNewDocument())
		return FALSE;

	strFile = _T("");
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUCCPrintDoc serialization

void CUCCPrintDoc::Serialize(CArchive& ar)
{
	//E-XD++ Library add lines.
	
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int nVersion = 1;
		ar << nVersion;

		ar << theApp.m_strDsn;
		ar << theApp.m_strSql;
		ar << theApp.m_nOpenType;
		m_pModelManager->Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		int nVersion;
		ar >> nVersion;
	
		CString strD;
		ar >> strD;

		if(theApp.m_strDsn.IsEmpty())
		{
			theApp.m_strDsn = strD;
		}

		ar >> theApp.m_strSql;
		ar >> theApp.m_nOpenType;
		m_pModelManager->Serialize(ar);
	}
}



//E-XD++ Library add lines.
void CUCCPrintDoc::SetModifiedFlag(BOOL b)
{
	// Do nothing
	m_pModelManager->SetModifiedFlag(b);
}

//added override
BOOL CUCCPrintDoc::IsModified()
{
	return m_pModelManager->IsModified();
}

void CUCCPrintDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COleDocument::DeleteContents();
	m_pModelManager->ResetContent();
}


BOOL CUCCPrintDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	bOpenDocument = TRUE;
	if (!COleDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	strFile = CString(lpszPathName);

	return TRUE;
}

BOOL CUCCPrintDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if (COleDocument::OnSaveDocument(lpszPathName))
	{
		SetModifiedFlag(FALSE);
		return TRUE;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CUCCPrintDoc diagnostics

#ifdef _DEBUG
void CUCCPrintDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CUCCPrintDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintDoc commands

void CUCCPrintDoc::OnFileSaveAsTemplate() 
{
	// TODO: Add your command handler code here
	CSVSaveAsTemplateDlg dlg;
	if (IDOK == dlg.DoModal())
	{
//		OnSaveDocument(dlg.m_strPath);
		CMBFileObj m_Obj;
		m_Obj.pModelManager = m_pModelManager;
		m_Obj.SaveTemplateDoc(dlg.m_strPath);
	}
}

void CUCCPrintDoc::OnMailTo() 
{
	// TODO: Add your command handler code here
	FOPEMailFileDesc mailDesc;
	mailDesc.strMail = _T("support@ucancode.net");
	mailDesc.strSubject = _T("Add you Subject Here!");
	mailDesc.strBody = _T("Add you Mail Body Here!");
	
	int nID = AfxMessageBox(_T("Before send email with this document, you need to save it to a file at first.\nDo you need to save it now?"), MB_YESNO|MB_ICONINFORMATION);
	if(nID == IDYES)
	{
		CString strType = _T("UCCPrint Files (*.ucp)|*.ucp||");
		CFileDialog fileDlg(FALSE, _T("UCCPrint Files"), _T("*.ucp"), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, strType, NULL);
		if (IDOK != fileDlg.DoModal())
			return;
		
		CString strFileName = fileDlg.GetPathName();
		if (TRUE == OnSaveDocument(strFileName))
		{
			mailDesc.arrFile.Add(strFileName);
			OnSendMapi(mailDesc);
		}
	}
}

void CUCCPrintDoc::OnSendMapi(const FOPEMailFileDesc &mailDesc) 
{
	HMODULE hMod = LoadLibrary(_T("MAPI32.DLL"));

	if (hMod == NULL)
	{
		AfxMessageBox(_T("Load Mail API file failed!"), MB_OK|MB_ICONINFORMATION);
		return;
	}

	ULONG (PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
	(FARPROC&)lpfnSendMail = GetProcAddress(hMod, "MAPISendMail");

	if (lpfnSendMail == NULL)
	{
		AfxMessageBox(_T("OPen Mail function file failed!"), MB_OK|MB_ICONINFORMATION);
		return;
	}

	int nFileCount = mailDesc.arrFile.GetSize();

	MapiFileDesc* pFileDesc = (MapiFileDesc*)malloc(sizeof(MapiFileDesc) * nFileCount);
	memset(pFileDesc, 0, sizeof(MapiFileDesc)*nFileCount);

	TCHAR* pTchPath = (TCHAR*)malloc(MAX_PATH*nFileCount);

	for(int i = 0;i < nFileCount;i++)
	{
		TCHAR* p = pTchPath + MAX_PATH * i;

		CString szText = mailDesc.arrFile.GetAt(i);
		_tcscpy(p, szText);

		(pFileDesc + i)->nPosition = (ULONG)-1;
#ifdef _UNICODE
		USES_CONVERSION; 
		(pFileDesc + i)->lpszPathName = W2A(p);
		(pFileDesc + i)->lpszFileName = W2A(p);
#else
		(pFileDesc + i)->lpszPathName = p;
		(pFileDesc + i)->lpszFileName = p;
#endif // _UNICODE
	}

	CString strMail = mailDesc.strMail;
	if (strMail == _T(""))
		strMail = _T("support@ucancode.net");

	MapiRecipDesc recip;
	memset(&recip, 0, sizeof(MapiRecipDesc));
	recip.ulRecipClass = MAPI_TO;
#ifdef _UNICODE
	USES_CONVERSION; 
	recip.lpszAddress = W2A(strMail);
#else
	recip.lpszAddress = (LPSTR)strMail.GetBuffer(strMail.GetLength());
#endif // _UNICODE

	CString strSubject = mailDesc.strSubject;
	CString strBody = mailDesc.strBody;

	MapiMessage message;
	memset(&message, 0, sizeof(message));
	message.nFileCount	= nFileCount;			
	message.lpFiles		= pFileDesc;			
	message.nRecipCount = 1;					
	message.lpRecips 	= &recip;		
#ifdef _UNICODE
	message.lpszSubject	= W2A(strSubject);
	message.lpszNoteText= W2A(strBody);
#else
	message.lpszSubject	= (LPSTR)strSubject.GetBuffer(strSubject.GetLength());
	message.lpszNoteText= (LPSTR)strBody.GetBuffer(strBody.GetLength());
#endif // _UNICODE

	CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, NULL);

	int nError = lpfnSendMail(0, 0, &message, MAPI_LOGON_UI|MAPI_DIALOG, 0);

	switch (nError)
	{
	case MAPI_E_AMBIGUOUS_RECIPIENT:
		AfxMessageBox(_T("A recipient matched more than one of the recipient descriptor structures and MAPI_DIALOG was not set. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_ATTACHMENT_NOT_FOUND:
		AfxMessageBox(_T("The specified attachment was not found. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_ATTACHMENT_OPEN_FAILURE:
		AfxMessageBox(_T("The specified attachment could not be opened. No message was sent. "), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_FAILURE:
		AfxMessageBox(_T("One or more unspecified errors occurred. No message was sent. "), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_INSUFFICIENT_MEMORY:
		AfxMessageBox(_T("There was insufficient memory to proceed. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_LOGIN_FAILURE:
		AfxMessageBox(_T("There was no default logon, and the user failed to log on successfully when the logon dialog box was displayed. No message was sent. "), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_TEXT_TOO_LARGE:
		AfxMessageBox(_T("The text in the message was too large. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_TOO_MANY_FILES:
		AfxMessageBox(_T("There were too many file attachments. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_TOO_MANY_RECIPIENTS:
		AfxMessageBox(_T("There were too many recipients. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_UNKNOWN_RECIPIENT:
		AfxMessageBox(_T("A recipient did not appear in the address list. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case MAPI_E_USER_ABORT:
		AfxMessageBox(_T("The user canceled the process. No message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	case SUCCESS_SUCCESS:
		AfxMessageBox(_T("The call succeeded and the message was sent."), MB_OK|MB_ICONINFORMATION);
		break;
	}

	pParentWnd->SetActiveWindow();

	free(pFileDesc);
	free(pTchPath);
	FreeLibrary(hMod);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMBFileObj, CObject, 0)
CMBFileObj::CMBFileObj()
{
	pModelManager = NULL;
	m_pBitmap = NULL;
}

CMBFileObj::~CMBFileObj()
{
	if(pModelManager != NULL)
	{
		pModelManager = NULL;
	}

	if(m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
}

void CMBFileObj::ClearAll()
{
	if(pModelManager != NULL)
	{
		pModelManager = NULL;
	}
	
	if(m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
}

void CMBFileObj::GenFirstPageBitmap()
{
	CExtTabModel*	pPage = (CExtTabModel*)pModelManager->GetTabPtr(0);
	FOPRect rcSnap = pPage->GetPagePosition();
    int nLarge = rcSnap.Width();
	if(rcSnap.Height() > nLarge)
	{
		nLarge = rcSnap.Height();
	}

	int cx, cy;
	cx = cy = 196;
	if(rcSnap.Height() > rcSnap.Width())
	{
		cy = 196;
		cx = (int)(196.0 * rcSnap.Width()/ (float)rcSnap.Height());
	}
	else
	{
		cx = 196;
		cy = (int)(196 * rcSnap.Height()/ (float)rcSnap.Width());
	}
	
    CBitmap bmp;
	pPage->GetBitmap(bmp,cx,cy);
	
	CClientDC dc(AfxGetMainWnd());
	
	if(m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

	m_pBitmap = new CFOBitmap;
	m_pBitmap->MakeNewBitmap(&dc,&bmp);
}

void CMBFileObj::SerializeTemplate(CArchive& ar)
{
//	CFODrawShape::SerializeTemplate(ar);
	
	if(ar.IsStoring())
	{
		ASSERT(pModelManager != NULL);
		//FODO:Add your own code here.
		GenFirstPageBitmap();
		m_pBitmap->Serialize(ar);
		pModelManager->Serialize(ar);
	}
	else
	{
		//FODO:Add your own code here.

		if(m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		
		m_pBitmap = new CFOBitmap;
		m_pBitmap->Serialize(ar);
	}
}

void CMBFileObj::SerializeTemplate2(CArchive& ar)
{
	//	CFODrawShape::SerializeTemplate(ar);
//	ASSERT(pModelManager != NULL);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.
		m_pBitmap->Serialize(ar);
		pModelManager->Serialize(ar);
	}
	else
	{
		//FODO:Add your own code here.
		
		if(m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		
		m_pBitmap = new CFOBitmap;
		m_pBitmap->Serialize(ar);

		if(pModelManager != NULL)
		{
			pModelManager = NULL;
		}
		
		pModelManager = new CExtTabModelManager;
		pModelManager->Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFOCloseBezierShape serialization
CFile* CMBFileObj::GetTempFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CMBFileObj::ReleaseTempFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CMBFileObj::OpenTemplateDoc(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = GetTempFile(lpszPathName,
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
		loadArchive.m_pDocument = FOGetActiveDocument();
		if (pFile->GetLength() != 0)
			SerializeTemplate(loadArchive);     // load me
		loadArchive.Close();
		ReleaseTempFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseTempFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
	return TRUE;
}

BOOL CMBFileObj::OpenTemplateDocWithData(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = GetTempFile(lpszPathName,
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
		loadArchive.m_pDocument = FOGetActiveDocument();
		if (pFile->GetLength() != 0)
			SerializeTemplate2(loadArchive);     // load me
		loadArchive.Close();
		ReleaseTempFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseTempFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
		return TRUE;
}

BOOL CMBFileObj::SaveTemplateDoc(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetTempFile(lpszPathName, CFile::modeCreate |
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
		SerializeTemplate(saveArchive);     // save me
		saveArchive.Close();
		ReleaseTempFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseTempFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;        // success
}
