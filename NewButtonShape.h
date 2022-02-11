#if !defined(FO_NEWBUTTONSHAPE_H__1BDB3125_A4EA_4CAF_AD19_2AA1381C3CF5__INCLUDED_)
#define FO_NEWBUTTONSHAPE_H__1BDB3125_A4EA_4CAF_AD19_2AA1381C3CF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author Name.
//------------------------------------------------------

#define NEW_SHAPE_BUTTON	FO_COMP_CUSTOM + 1

 
//===========================================================================
// Summary:
//     The CNewButtonShape class derived from CFOButtonShape
//      New Button Shape
//===========================================================================

class CNewButtonShape : public CFOButtonShape  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CNewButtonShape---New Button Shape, Specifies a CNewButtonShape object.
	DECLARE_SERIAL(CNewButtonShape);
public:

	// constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Button Shape, Constructs a CNewButtonShape object.
	//		Returns A  value.
	CNewButtonShape();

	// Copy constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Button Shape, Constructs a CNewButtonShape object.
	//		Returns A  value.  
	// Parameters:
	//		src---Specifies a const CNewButtonShape& src object.
	CNewButtonShape(const CNewButtonShape& src);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C New Button Shape, Destructor of class CNewButtonShape
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CNewButtonShape();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CNewButtonShape object in two steps. First call the constructor, then call Create, which creates the object.
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
	//		Returns A CNewButtonShape& value.  
	// Parameters:
	//		src---Specifies a const CNewButtonShape& src object.
	CNewButtonShape& operator=(const CNewButtonShape& src);

	
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

	// Draws the Select status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Face, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		rcTotal---rcTotal, Specifies A CRect type value.
	virtual void OnDrawFace(CDC *pDC,CRect rcTotal);

public:
	
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


#endif // !defined(FO_NEWBUTTONSHAPE_H__1BDB3125_A4EA_4CAF_AD19_2AA1381C3CF5__INCLUDED_)
