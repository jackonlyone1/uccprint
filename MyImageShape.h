#if !defined(FO_MYIMAGESHAPE_H__D5C3C5F3_4055_11D6_A556_525400EA266C__INCLUDED_)
#define AFC_MYIMAGESHAPE_H__D5C3C5F3_4055_11D6_A556_525400EA266C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author Name.
//------------------------------------------------------


#include "FOImageShape.h"
#define MY_IMAGE_TYPE   FO_COMP_CUSTOM + 2

 
//===========================================================================
// Summary:
//     The CMyImageShape class derived from CFOImageShape
//      My Image Shape
//===========================================================================

class CMyImageShape : public CFOImageShape  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CMyImageShape---My Image Shape, Specifies a CMyImageShape object.
	DECLARE_SERIAL(CMyImageShape);
public:

	// constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// My Image Shape, Constructs a CMyImageShape object.
	//		Returns A  value.
	CMyImageShape();

	// Copy constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// My Image Shape, Constructs a CMyImageShape object.
	//		Returns A  value.  
	// Parameters:
	//		src---Specifies a const CMyImageShape& src object.
	CMyImageShape(const CMyImageShape& src);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C My Image Shape, Destructor of class CMyImageShape
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CMyImageShape();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CMyImageShape object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		strCaption---strCaption, Specifies A CString type value.
	// Creates the button shape from a CRect object.
	virtual void Create(CRect &rcPos,CString strCaption = "");

	// Init image position.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Image Position, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CRect type value.  
	// Parameters:
	//		nImageWidth---Image Width, Specifies A integer value.  
	//		nImageHeight---Image Height, Specifies A integer value.
	virtual CRect DoInitImagePos(int nImageWidth,int nImageHeight);

	// Calc text line array.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Text Array, You construct a CMyImageShape object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a int type value.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		strText---strText, Specifies A CString type value.  
	//		rcBox---rcBox, Specifies A CRect type value.  
	//		arLines---arLines, Specifies A CString type value.
	virtual int CreateTextArray(CDC* pDC, CString strText,CRect rcBox,CStringArray& arLines);

	// Get text box size.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Text Size, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CSize type value.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		rcPos---rcPos, Specifies A CRect type value.  
	//		strText---strText, Specifies A CString type value.
	virtual CSize GetTextSize(CDC* pDC,CRect rcPos,CString strText);

	// Get format type.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Draw Format Type, Returns the specified value.
	//		Returns a UINT type value.
	UINT GetDrawFormatType();

	// call this method to put the text object into edit in place mode
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Start Show Edit, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pView---pView, A pointer to the CFOPCanvasCore or NULL if the call failed.  
	//		ptCursorSP---Cursor S P, Specifies A CPoint type value.
	virtual BOOL DoStartShowEdit(CFOPCanvasCore* pView, CPoint ptCursorSP);
    
public:

	// Assignment operator.
	
	//-----------------------------------------------------------------------
	// Summary:
	// None Description.
	//		Returns A CMyImageShape& value.  
	// Parameters:
	//		src---Specifies a const CMyImageShape& src object.
	CMyImageShape& operator=(const CMyImageShape& src);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed
	// Creates a copy of this shape.
	virtual CFODrawShape* Copy() const;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Geometry Updated, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pRgn---pRgn, A pointer to the CFOArea or NULL if the call failed.
	virtual void GeometryUpdated(CFOArea* pRgn);

	// Rotate shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Rotate Shape, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nAngle---nAngle, Specifies a double nAngle object.  
	//		fOX---O X, Specifies A float value.  
	//		fOY---O Y, Specifies A float value.
	virtual void RotateShape(double nAngle, float fOX, float fOY);

	// Rotate shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Rotate Track Shape, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nAngle---nAngle, Specifies a double nAngle object.  
	//		fOX---O X, Specifies A float value.  
	//		fOY---O Y, Specifies A float value.
	virtual void RotateTrackShape(double nAngle, float fOX, float fOY);

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

	// Draws the truely shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw(CDC *pDC);

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

public:
	// Crrent font image list.
 
	// Font Name, This member is a collection of same-sized images.  
	CImageList m_imgFontName;	

};


#endif // !defined(AFC_MYIMAGESHAPE_H__D5C3C5F3_4055_11D6_A556_525400EA266C__INCLUDED_)
