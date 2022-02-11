// UCCPrintDoc.h : interface of the CUCCPrintDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCCPRINTDOC_H__A8DE6E47_296F_47A9_B8F2_45E9AC1FB869__INCLUDED_)
#define AFX_UCCPRINTDOC_H__A8DE6E47_296F_47A9_B8F2_45E9AC1FB869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//E-XD++ Library add lines.
#include "ExtTabModelManager.h"	

typedef struct tagFOPEMailFileDesc
{
	CString strMail;
	CString strSubject;
	CString strBody;	
    CStringArray arrFile;
}FOPEMailFileDesc;

 
//===========================================================================
// Summary:
//     The CMBFileObj class derived from CObject
//      M B File Object
//===========================================================================

class CMBFileObj : public CObject
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CMBFileObj---M B File Object, Specifies a CMBFileObj object.
	DECLARE_SERIAL(CMBFileObj);
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// M B File Object, Constructs a CMBFileObj object.
	//		Returns A  value.
	CMBFileObj();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C M B File Object, Destructor of class CMBFileObj
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CMBFileObj();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear All, Remove the specify data from the list.

	void ClearAll();
public:
	
	// Serializes the data.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize Template, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	virtual void SerializeTemplate(CArchive &ar);
	
	// Serializes the data.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize Template2, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	virtual void SerializeTemplate2(CArchive &ar);
	
	// Save document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Template Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveTemplateDoc(LPCTSTR lpszPathName);
	
	// Open document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Template Document, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenTemplateDoc(LPCTSTR lpszPathName);
	
	// Open document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Template Document With Data, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenTemplateDocWithData(LPCTSTR lpszPathName);
	
	// Get file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Temp File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *GetTempFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);
	
	// Release file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Release Temp File, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pFile---pFile, A pointer to the CFile or NULL if the call failed.  
	//		bAbort---bAbort, Specifies A Boolean value.
	virtual void ReleaseTempFile(CFile* pFile, BOOL bAbort);
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Generate First Page Bitmap, None Description.

	void GenFirstPageBitmap();
	
public:
 
	// Model Manager, This member maintains a pointer to the object CExtTabModelManager.  
	CExtTabModelManager *pModelManager;
 
	// m_pBitmap, This member maintains a pointer to the object CFOBitmap.  
	CFOBitmap			*m_pBitmap;
};

 
//===========================================================================
// Summary:
//     The CUCCPrintDoc class derived from COleDocument
//      U C C Print Document
//===========================================================================

class CUCCPrintDoc : public COleDocument
{
protected: // create from serialization only
	
	//-----------------------------------------------------------------------
	// Summary:
	// U C C Print Document, Constructs a CUCCPrintDoc object.
	//		Returns A  value.
	CUCCPrintDoc();
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CUCCPrintDoc---U C C Print Document, Specifies A integer value.
	DECLARE_DYNCREATE(CUCCPrintDoc)

// Attributes
public:

	//E-XD++ Library add lines.
 
	// Model Manager, This member maintains a pointer to the object CExtTabModelManager.  
	CExtTabModelManager *m_pModelManager;
 
	// New Document, This member sets TRUE if it is right.  
	BOOL bNewDocument;
 
	// Open Document, This member sets TRUE if it is right.  
	BOOL bOpenDocument;
// Operations
public:

 
	// strFile, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strFile;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUCCPrintDoc)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// On New Document, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnNewDocument();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		ar---Specifies a CArchive& ar object.
	virtual void Serialize(CArchive& ar);
	//E-XD++ Library add lines.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Delete Contents, Deletes the given object.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DeleteContents();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Modified Flag, Sets a specify value to current class CUCCPrintDoc
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		bModified---bModified, Specifies A Boolean value.
	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Modified, Determines if the given value is correct or exist.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL IsModified();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Save Document, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Open Document, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C U C C Print Document, Destructor of class CUCCPrintDoc
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CUCCPrintDoc();
#ifdef _DEBUG
	
	//-----------------------------------------------------------------------
	// Summary:
	// Assert Valid, Assert performs a validity check on this object by checking its internal state.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void AssertValid() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Dump, Dumps the contents of your object to a CDumpContext object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		dc---Specifies a CDumpContext& dc object.
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Send Mapi, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		&mailDesc---&mailDesc, Specifies a const FOPEMailFileDesc &mailDesc object.
	void OnSendMapi(const FOPEMailFileDesc &mailDesc);

// Generated message map functions
protected:
	//{{AFX_MSG(CUCCPrintDoc)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On File Save As Template, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFileSaveAsTemplate();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mail To, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMailTo();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCCPRINTDOC_H__A8DE6E47_296F_47A9_B8F2_45E9AC1FB869__INCLUDED_)
