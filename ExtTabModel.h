#if !defined(FO_EXTTABMODEL_H__AEC0777D_A0DB_4ABA_88AD_1D0440F4B50B__INCLUDED_)
#define AFC_EXTTABMODEL_H__AEC0777D_A0DB_4ABA_88AD_1D0440F4B50B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author Name.
//------------------------------------------------------

 
//===========================================================================
// Summary:
//     The CExtTabModel class derived from CFOTabPageModel
//      Extend Tab Model
//===========================================================================

class CDBChartShape;
class CExtTabModel : public CFOTabPageModel
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CExtTabModel---Extend Tab Model, Specifies a CExtTabModel object.
	DECLARE_SERIAL(CExtTabModel);

public:
	// Constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Tab Model, Constructs a CExtTabModel object.
	//		Returns A  value.
	CExtTabModel();

	// Copy constructor. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Tab Model, Constructs a CExtTabModel object.
	//		Returns A  value.  
	// Parameters:
	//		source---Specifies a const CExtTabModel& source object.
	CExtTabModel(const CExtTabModel& source);

	// Deconstructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Extend Tab Model, Destructor of class CExtTabModel
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CExtTabModel();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODataModel,or NULL if the call failed
	// Create a duplicate copy of this object. 
	virtual CFODataModel* Copy() const;

public:

	// Shapes that doesn't effect with style.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Shape Effect, Determines if the given value is correct or exist.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pShape---pShape, A pointer to the CFODrawShape or NULL if the call failed.
	virtual BOOL			IsShapeEffect(CFODrawShape* pShape);

	// Init model data.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Data, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoInitData();

	// Set modified flag.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Modified Flag, Sets a specify value to current class CExtTabModel
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		bModified---bModified, Specifies A Boolean value.
	virtual void SetModifiedFlag(BOOL bModified = TRUE);

	// Is modified.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Modified, Determines if the given value is correct or exist.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL IsModified();

	// Notify observer wnd.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Notify Observer, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		lHint---lHint, Specifies A lparam value.  
	//		CObject*pHint---Object*p Hint, A pointer to the CObject or NULL if the call failed.
	virtual void NotifyObserver(LPARAM lHint, CObject*pHint = NULL);

	// Update Title
	
	//-----------------------------------------------------------------------
	// Summary:
	// Update Title, Call this member function to update the object.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void UpdateTitle();

	// Do action change.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Action Change, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pAction---pAction, A pointer to the const CFOBaseAction or NULL if the call failed.
	virtual void DoActionChange(const CFOBaseAction* pAction);

	// Do create a new shape.
	// m_drawshape -- Shape Type id start from FO_COMP_CUSTOM
	// rcCreate -- init position of shape.
	// strFileName -- if being image shape,this is the image file name.
	// pCurItem -- if being drag and drop from toolbox,this is the pointer of current toolbox item.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Create Shape By Type, Do create a new shape,override this method to add your own custom shape creating.See sample UserDefine shows.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape ,or NULL if the call failed  
	// Parameters:
	//		m_drawshape---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		&rcCreate---&rcCreate, Specifies A CRect type value.  
	//		strFileName---File Name, Specifies A CString type value.  
	//		*pCurItem---Current Item, A pointer to the CFOToolBoxItem  or NULL if the call failed.
	virtual CFODrawShape *DoCreateShapeByType(UINT m_drawshape,CRect &rcCreate,CString strFileName = _T(""),CFOToolBoxItem *pCurItem = NULL);

	// Do create a new shape shape.
	// m_drawshape -- Shape Type id start from FO_COMP_CUSTOM
	// rcCreate -- init position of shape.
	// strFileName -- if being image shape,this is the image file name.
	// pCurItem -- if being drag and drop from toolbox,this is the pointer of current toolbox item.
	virtual CFOCompositeShape *DoCreateCompositeShapeByType(UINT m_drawshape,CRect &rcCreate,
		CArray<FOPORTVALUE,FOPORTVALUE> *arInitPorts,
		CString strFileName = _T(""),
		UINT nResID = 0,
		CFOToolBoxItem *pCurItem = NULL);

	// Offset the full canvas.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Offset Canvas2, None Description.
	// Parameters:
	//		&ptOffset---&ptOffset, Specifies A CPoint type value.
	void OffsetCanvas2(const CPoint &ptOffset);

	// Draw shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Shape, Draw all the shapes on the canvas to device.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcView---&rcView, Specifies A CRect type value.
	virtual void OnDrawShape(CDC *pDC,const CRect &rcView);

	// Draw Back ground.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Back, Draw the background of this canvas.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcClip---&rcClip, Specifies A CRect type value.
	virtual void OnDrawBack(CDC *pDC,const CRect &rcClip);

	// Get Unique Name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unique Name, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString GetUniqueName(UINT nType);

	// Get Unique Caption
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unique Caption, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString GetUniqueCaption(UINT nType);

	// Add new chart shape.
	// Memory data.
	// For example:
	// 		CFOPChartData* pMemChart = new CFOPChartData(5, 4);
	// 		
	// 		pMemChart->SetMainTitle(_T("Main Title"));
	// 		pMemChart->SetSubTitle(_T("Child Title"));
	// 		pMemChart->SetXAxisTitle(_T("X axis title"));
	// 		pMemChart->SetYAxisTitle(_T("Y axis title"));
	// 		pMemChart->SetZAxisTitle(_T("Z axis title"));
	// 		
	// 		for( short nCol = 0; nCol < 5; nCol++ )
	// 		{
	// 			pMemChart->SetColText( nCol, pMemChart->GetDefaultColumnText( nCol ));
	// 			
	// 			for( short nRow = 0; nRow < 4; nRow++ )
	// 			{
	// 				pMemChart->SetData( nCol, nRow, fDefaultArrX[ nRow ][ nCol ] );
	// 				pMemChart->SetRowText( nRow, pMemChart->GetDefaultRowText( nRow ));
	// 			}
	// 		}
	CDBChartShape *AddNewChart(CFOPChartData* pMemData, const FOPRect & rcPos, const FOP_CHART_STYLE &nChartStyle = FOP_CHSTYLE_2D_BAR);

	// Get base shape name.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Base Name, You construct a CExtTabModel object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString CreateBaseName(UINT nType);

	// Get base shape caption.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Base Caption, You construct a CExtTabModel object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString CreateBaseCaption(UINT nType);

	// Call before create shape new shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Create Shape, Call before create shape new shape,this method will be called after each new shape is created, You can override this method to do something before shape created.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	virtual void DoInitCreateShape(CFODrawShape *pShape);

	// Add new shape
	// pShape -- the pointer of new shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Shape, Adds an object to the specify list.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pShape---pShape, A pointer to the CFODrawShape or NULL if the call failed.
	virtual BOOL			AddShape(CFODrawShape* pShape);
	
	// Add new shapes to canvas.
	// list -- list of shapes.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Shapes, Adds an object to the specify list.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		list---Specifies a const CFODrawShapeList& list object.
	virtual BOOL			AddShapes(const CFODrawShapeList& list);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Search For E Form Shape E X, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&listShapes---&listShapes, Specifies a E-XD++ CFODrawShapeList &listShapes object.
	virtual void SearchForEFormShapeEX(CFODrawShapeList &listShapes);

	// Search in composite shape for all e-form shapes.
	// pComp -- Composite shape.
	// listShapes -- list of shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Search For E Form Shape, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pComp---*pComp, A pointer to the CFOCompositeShape  or NULL if the call failed.  
	//		&listShapes---&listShapes, Specifies a E-XD++ CFODrawShapeList &listShapes object.
	virtual void SearchForEFormShape(CFOCompositeShape *pComp, CFODrawShapeList &listShapes);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Express Value, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		&strExpress---&strExpress, Specifies A CString type value.
	virtual CString GetExpressValue(const CString &strExpress);
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	// Serialize data to file.
	virtual void Serialize(CArchive &ar);

	// Save Document to a specify file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);

	// Open Document from a specify file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);

	// Get the pointer of File.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *		 GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);

	// Release File from memory.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Release File, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pFile---pFile, A pointer to the CFile or NULL if the call failed.  
	//		bAbort---bAbort, Specifies A Boolean value.
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);


// Implementation
public:

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

};

//Structure to interface with corresponding BOOLs in CFOPRelaceText, will replace with <bitset> soon
struct FOP_REPLACE_SET{
	BOOL bStrict,bCheckOnlyWords,bLastWordMayNotHavePunct,bCaseSensetive,bOverWriteFile,bReplaceLFWithCRLF,bReplaceCRLFWithLF;
};


 
//===========================================================================
// Summary:
//      To use a CFOPRelaceText object, just call the constructor.
//      F O P Relace Text
//===========================================================================

class CFOPRelaceText  
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Process, Call the Process member function to translate a caught exception.
	//		Returns a CString type value.  
	// Parameters:
	//		&strInput---&strInput, Specifies A CString type value.
	CString Process(const CString &strInput); //Initiates start of processing, and returns the number of matches found
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Replacement String, Sets a specify value to current class CFOPRelaceText
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		*szReplacementString---Replacement String, A pointer to the const TCHAR  or NULL if the call failed.
	BOOL SetReplacementString(const TCHAR *szReplacementString);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Search String, Sets a specify value to current class CFOPRelaceText
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		*szSearchString---Search String, A pointer to the const TCHAR  or NULL if the call failed.
	BOOL SetSearchString(const TCHAR *szSearchString);
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O P Relace Text, Constructs a CFOPRelaceText object.
	//		Returns A  value.
	CFOPRelaceText();
	CFOPRelaceText::CFOPRelaceText(FOP_REPLACE_SET boolSet);
	
	//-----------------------------------------------------------------------
	// Summary:
	// C F O P Relace Text, Destructor of class CFOPRelaceText
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CFOPRelaceText();
	
private:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Char Belonging To Set, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		cCharToTest---Char To Test, Specifies a TCHAR cCharToTest object.  
	//		*szSetValues---Set Values, A pointer to the TCHAR  or NULL if the call failed.
	BOOL IsCharBelongingToSet(TCHAR cCharToTest,TCHAR *szSetValues);
 
	// Replace C R L F With L F, This member sets TRUE if it is right.  
	BOOL m_bReplaceCRLFWithLF;
 
	// Replace L F With C R L F, This member sets TRUE if it is right.  
	BOOL m_bReplaceLFWithCRLF;
 
	// Last Word May Not Have Punct, This member sets TRUE if it is right.  
	BOOL m_bLastWordMayNotHavePunct;
 
	// Check Only Words, This member sets TRUE if it is right.  
	BOOL m_bCheckOnlyWords;
 
	// m_bStrict, This member sets TRUE if it is right.  
	BOOL m_bStrict;
 
	// Strain Found, This member sets TRUE if it is right.  
	BOOL m_bStrainFound;
 
	// Search Is Finished, This member sets TRUE if it is right.  
	BOOL m_bSearchIsFinished;
 
	// Case Sensetive, This member sets TRUE if it is right.  
	BOOL m_bCaseSensetive;
 
	// Over Write File, This member sets TRUE if it is right.  
	BOOL m_bOverWriteFile;
 
	// Search String, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sSearchString;
 
	// Replacement String, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sReplacementString;
 
	// Temp Search String, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sTempSearchString;
};


#endif // !defined(AFC_EXTTABMODEL_H__AEC0777D_A0DB_4ABA_88AD_1D0440F4B50B__INCLUDED_)
