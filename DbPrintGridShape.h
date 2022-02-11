#if !defined(FO_DBPRINTGRIDSHAPE_H__EF87A1A3_1B3B_4E3A_B74A_0742B4235208__INCLUDED_)
#define FO_DBPRINTGRIDSHAPE_H__EF87A1A3_1B3B_4E3A_B74A_0742B4235208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author.
//------------------------------------------------------

#define DB_PRINT_GRID_SHAPE		777
#define DB_TABLE_SHAPE			778
#include "afxdb.h"
#include <afxtempl.h>

typedef struct tagDB_COLS
{
	CString		strTitle;
	CString		strDBFiled;
} FODB_COLS;

 
//===========================================================================
// Summary:
//     The CDBVariantEx class derived from CDBVariant
//      D B Variant Ex
//===========================================================================

class CDBVariantEx : public CDBVariant
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get String Value, Returns the specified value.
	// Parameters:
	//		lpsz---Specifies A 32-bit pointer to a character string.
	void GetStringValue(LPSTR lpsz);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get String Value, Returns the specified value.
	// Parameters:
	//		rstrValue---rstrValue, Specifies A CString type value.
	void GetStringValue(CString& rstrValue);
};

class CODBCDynamic;
 
//===========================================================================
// Summary:
//      To use a CODBCTypeInfo object, just call the constructor.
//      O D B C Type Information
//===========================================================================

class CODBCTypeInfo
{                           
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// O D B C Type Information, Constructs a CODBCTypeInfo object.
	//		Returns A  value.  
	// Parameters:
	//		lpszDSN---D S N, Specifies a LPCSTR lpszDSN object.
	CODBCTypeInfo(LPCSTR lpszDSN);
	
	//-----------------------------------------------------------------------
	// Summary:
	// C O D B C Type Information, Destructor of class CODBCTypeInfo
	//		Returns A  value.
	~CODBCTypeInfo();
	
protected:
 
	// O D B C Dynamic, This member maintains a pointer to the object CODBCDynamic.  
	CODBCDynamic* m_pODBCDynamic;
	
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Type Information, Returns the specified value.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		iDataType---Data Type, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		rpMapDataAttrNameToDataAttrVal---Map Data Attr Name To Data Attr Value, A pointer to the CMapStringToOb or NULL if the call failed.
	BOOL GetTypeInfo(UINT iDataType, CMapStringToOb*& rpMapDataAttrNameToDataAttrVal);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Type Information, Returns the specified value.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		iDataType---Data Type, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		lpszColName---Column Name, Specifies a LPCSTR lpszColName object.  
	//		ppvarValue---ppvarValue, A pointer to the CDBVariantEx* or NULL if the call failed.
	BOOL GetTypeInfo(UINT iDataType, LPCSTR lpszColName, CDBVariantEx** ppvarValue);
public:
 
	// Data Type To Data Attr Map, This member specify CMapWordToOb object.  
	CMapWordToOb m_mapDataTypeToDataAttrMap;
};


typedef CTypedPtrMap<CMapStringToPtr, CString /* column name */, CDBVariantEx* /* value */> CODBCRecord;
typedef CTypedPtrArray<CObArray, CODBCRecord*> CODBCRecordArray;

 
//===========================================================================
// Summary:
//      To use a CODBCDynamic object, just call the constructor.
//      O D B C Dynamic
//===========================================================================

class CODBCDynamic
{                           
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// O D B C Dynamic, Constructs a CODBCDynamic object.
	//		Returns A  value.  
	// Parameters:
	//		lpszDSN---D S N, Specifies a LPCSTR lpszDSN object.  
	//		lpszUser---lpszUser, Specifies a LPCSTR lpszUser = NULL object.  
	//		lpszPassword---lpszPassword, Specifies a LPCSTR lpszPassword = NULL object.  
	//		henv---Specifies a SQLHENV henv = NULL object.  
	//		hdbc---Specifies a SQLHDBC hdbc = NULL object.
	CODBCDynamic(LPCSTR lpszDSN, 
		LPCSTR lpszUser = NULL, LPCSTR lpszPassword = NULL, 
		SQLHENV henv = NULL, SQLHDBC hdbc = NULL);
	// throws CUserException
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// C O D B C Dynamic, Destructor of class CODBCDynamic
	//		Returns A  value.
	~CODBCDynamic();
	
public:
	enum
	{
		errorSqlAllocHandleHenv = 50000,
			errorSqlSetEnvAttr = 50001,
			errorSqlAllocHandleHdbc = 50002,
			errorSqlConnect = 50003,
			errorUnknownCause = 5004
	};
	
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clean Out Record Array, None Description.

	void CleanOutRecordArray();
	
protected:
 
	// This member specify SQLHENV object.  
	SQLHENV m_henv;
 
	// This member specify SQLHDBC object.  
	SQLHDBC m_hdbc;
 
	// Is Connected, This member sets TRUE if it is right.  
	BOOL m_bIsConnected;
	
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get H D B C, Returns the specified value.
	//		Returns A SQLHDBC value.
	SQLHDBC GetHDBC ()
	{
		return m_hdbc;
	}
	
public:
 
	// O D B C Record Array, This member specify CODBCRecordArray object.  
	CODBCRecordArray m_ODBCRecordArray;
	
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Field Type From S Q L Type, Returns the specified value.
	//		Returns A short value.  
	// Parameters:
	//		nSQLType---S Q L Type, Specifies a short nSQLType object.
	short GetFieldTypeFromSQLType(short nSQLType);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Data Buffer, Returns the specified value.
	//		Returns a pointer to the object void,or NULL if the call failed  
	// Parameters:
	//		pvarValue---pvarValue, A pointer to the CDBVariantEx or NULL if the call failed.  
	//		nFieldType---Field Type, Specifies a short nFieldType object.  
	//		pnLen---pnLen, A pointer to the int or NULL if the call failed.  
	//		nSQLType---S Q L Type, Specifies a short nSQLType object.  
	//		nPrecision---nPrecision, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.
	void* GetDataBuffer(CDBVariantEx* pvarValue, short nFieldType, int* pnLen, short nSQLType, UDWORD nPrecision);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Data, Returns the specified value.
	//		Returns A 32-bit signed integer.  
	// Parameters:
	//		hstmt---Specifies a SQLHSTMT hstmt object.  
	//		nFieldIndex---Field Index, Specifies a short nFieldIndex object.  
	//		nFieldType---Field Type, Specifies a short nFieldType object.  
	//		pvData---pvData, Specifies a LPVOID pvData object.  
	//		nLen---nLen, Specifies A integer value.  
	//		nSQLType---S Q L Type, Specifies a short nSQLType object.
	long GetData(SQLHSTMT hstmt, short nFieldIndex, short nFieldType, LPVOID pvData, int nLen, short nSQLType);
	
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Execute S Q L, None Description.
	//		Returns A 32-bit signed integer.  
	// Parameters:
	//		lpszSQL---S Q L, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	long ExecuteSQL(LPCTSTR lpszSQL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Fetch Data, None Description.
	//		Returns A 32-bit signed integer.  
	// Parameters:
	//		hstmt---Specifies a HSTMT hstmt object.
	long FetchData(HSTMT hstmt);
};

 
//===========================================================================
// Summary:
//     The CDbPrintGridShape class derived from CFOPNewGridShape
//      Db Print Grid Shape
//===========================================================================

class CDbPrintGridShape : public CFOPNewGridShape  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CDbPrintGridShape---Db Print Grid Shape, Specifies A integer value.
	DECLARE_SERIAL(CDbPrintGridShape);
public:

	// constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// Db Print Grid Shape, Constructs a CDbPrintGridShape object.
	//		Returns A  value.
	CDbPrintGridShape();

	// Copy constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Db Print Grid Shape, Constructs a CDbPrintGridShape object.
	//		Returns A  value.  
	// Parameters:
	//		src---Specifies A integer value.
	CDbPrintGridShape(const CDbPrintGridShape& src);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Db Print Grid Shape, Destructor of class CDbPrintGridShape
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CDbPrintGridShape();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CDbPrintGridShape object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		strCaption---strCaption, Specifies A CString type value.
	// Creates the button shape from a CRect object.
	virtual void Create(CRect &rcPos,CString strCaption = _T(""));

public:

	// Assignment operator.
	
	//-----------------------------------------------------------------------
	// Summary:
	// None Description.
	//		Returns a int type value.  
	// Parameters:
	//		src---Specifies A integer value.
	CDbPrintGridShape& operator=(const CDbPrintGridShape& src);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed
	// Creates a copy of this shape.
	virtual CFODrawShape* Copy() const;

	//Generate Shape Area
	
	//-----------------------------------------------------------------------
	// Summary:
	// Geometry Updated, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pRgn---pRgn, A pointer to the CFOArea or NULL if the call failed.
	virtual void GeometryUpdated(CFOArea* pRgn);

	// Hit text grid
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test Grid, Hit test on this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object FOPGridCell ,or NULL if the call failed  
	// Parameters:
	//		pt---Specifies A CPoint type value.  
	//		nElement---nElement, Specifies a FOPGridViewElement & nElement object.  
	//		nSubElement---Child Element, Specifies a FOPGridViewElement & nSubElement object.  
	//		nIndex---nIndex, Specifies A integer value.  
	//		nExIndex---Ex Index, Specifies A integer value.  
	//		&bDblClk---Double click Clk, Specifies A Boolean value.
    virtual FOPGridCell *HitTestGrid(CPoint pt,
        FOPGridViewElement & nElement,
        FOPGridViewElement & nSubElement,
        int & nIndex,
        int & nExIndex,const BOOL &bDblClk = FALSE);
    
	// Do init data of the grid shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Grid Data, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoInitGridData();

	// Calc all printing pages:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Calculate All Pages, None Description.
	//		Returns a int type value.
	int CalcAllPages();

	// Get all print pages.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get All Print Pages, Returns the specified value.
	//		Returns a int type value.
	int GetAllPrintPages();
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Maximize Print Rows, Returns the specified value.
	//		Returns a int type value.
	int GetMaxPrintRows();

public:
	// Hit text grid
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test Cell, Hit test on this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object FOPGridCell ,or NULL if the call failed  
	// Parameters:
	//		&ptHit---&ptHit, Specifies A CPoint type value.
    virtual FOPGridCell *HitTestCell(const CPoint &ptHit);
    
	// WM_LBUTTONDOWN message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Down, Called when the user presses the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonDown(UINT nFlags, CPoint point); 

	// WM_LBUTTONUP message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Up, Called when the user releases the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonUp(UINT nFlags, CPoint point);

	// Do calc rectangles
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Calculate Rects, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
    virtual void DoCalcRects();
    
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	// Serializes the data.
	virtual void Serialize(CArchive &ar);
	
	// Save document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);

	// Open document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);
	
	// Get file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);
	
	// Release file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Release File, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pFile---pFile, A pointer to the CFile or NULL if the call failed.  
	//		bAbort---bAbort, Specifies A Boolean value.
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);

public:

	//Draw flat status.
	// Do draw columns
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw Columns, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		rDC---D C, Specifies a CDC & rDC object.
    virtual void DoDrawColumns(CDC & rDC);

	// Draws custom tracker.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Track Custom, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawTrackCustom(CDC *pDC);

	// Creates GDI objects and sets up the device context for drawing. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// Prepare D C, Creates GDI objects and sets up the device context for drawing.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void PrepareDC(CDC* pDC);

	// Draws the flat status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Flat, Draws the flat status of the shape.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawFlat(CDC *pDC);

	// Draws shadow of shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Shadow, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawShadow(CDC *pDC);

	// Draws the 3D status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw3d, Draws the 3d status of the shape.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw3d(CDC *pDC);

	// Frees GDI objects and restores the state of the device context.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear D C, Remove the specify data from the list.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void ClearDC(CDC* pDC);
	// Implementation

	// Do draw grid
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		rDC---D C, Specifies a CDC & rDC object.
    virtual void DoDraw(CDC & rDC);

	// Do draw client
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw Client, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		rDC---D C, Specifies a CDC & rDC object.
    virtual void DoDrawClient(CDC & rDC);
    
	// Do draw column cell
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw Column Cell, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		rDC---D C, Specifies a CDC & rDC object.  
	//		index---Specifies A integer value.  
	//		rcDeviceBounds---Device Bounds, Specifies A CRect type value.  
	//		btnState---btnState, Specifies a FOPGridButtonStates btnState object.  
	//		element---Specifies a FOPGridViewElement element = FOP_GRID_ELEMENT_NONE object.
    virtual void DoDrawColumnCell(CDC & rDC,
        int index,
        CRect rcDeviceBounds,
        FOPGridButtonStates btnState,
        FOPGridViewElement element = FOP_GRID_ELEMENT_NONE);
    
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Fill Data, Do a event. 
	// Parameters:
	//		nOffset---nOffset, Specifies A integer value.
	void DoFillData(int nOffset);

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

public:
	//
 
	// S Q L, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strSQL;

 
	// strBackup, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strBackup;

 
	// Column Color, This member sets A 32-bit value used as a color value.  
	COLORREF m_crColColor;


 
	// Start Record, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_nStartRecord;
 
	// Maximize Records, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_nMaxRecords;

 
	// Horizontal Grid, This member sets TRUE if it is right.  
	BOOL m_bHorzGrid;
 
	// Vertical Grid, This member sets TRUE if it is right.  
	BOOL m_bVertGrid;
	// 
	CArray<FODB_COLS,FODB_COLS> m_ColNames;
};


#endif // !defined(FO_DBPRINTGRIDSHAPE_H__EF87A1A3_1B3B_4E3A_B74A_0742B4235208__INCLUDED_)
