#if !defined(FO_DBCHARTSHAPE_H__524D925F_791C_4ED9_8F4D_5213F379B4B1__INCLUDED_)
#define FO_DBCHARTSHAPE_H__524D925F_791C_4ED9_8F4D_5213F379B4B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author.
//------------------------------------------------------
#include "DbPrintGridShape.h"

#define DB_CHART_SHAPE FO_COMP_CUSTOM + 102

class CDBChartShape : public CFOPChartShape  
{
protected:
	DECLARE_SERIAL(CDBChartShape);
public:

	// constructor
	CDBChartShape();

	// Copy constructor.
	CDBChartShape(const CDBChartShape& src);

	// Destructor.
	virtual ~CDBChartShape();

	
public:

	// Assignment operator.
	CDBChartShape& operator=(const CDBChartShape& src);

	// Creates a copy of this shape.
	virtual CFODrawShape* Copy() const;

	//Generate Shape Area
	virtual void GeometryUpdated(CFOArea* pRgn);

public:
	
	// WM_LBUTTONDOWN message.
	virtual void OnLButtonDown(UINT nFlags, CPoint point); 

	// WM_LBUTTONUP message.
	virtual void OnLButtonUp(UINT nFlags, CPoint point);

public:
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Fill Data, Do a event. 
	// Parameters:
	//		nOffset---nOffset, Specifies A integer value.
	void DoFillData();

public:

	// Serializes the data.
	virtual void Serialize(CArchive &ar);
	
	// Save document.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);

	// Open document.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);
	
	// Get file.
	CFile *GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);
	
	// Release file.
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);

public:

	//Draw flat status.

	// Draws custom tracker.
	virtual void OnDrawTrackCustom(CDC *pDC);

	// Creates GDI objects and sets up the device context for drawing. 
	virtual void PrepareDC(CDC* pDC);

	// Draws the flat status of the shape.
	virtual void OnDrawFlat(CDC *pDC);

	// Draws shadow of shape.
	virtual void OnDrawShadow(CDC *pDC);

	// Draws the 3D status of the shape.
	virtual void OnDraw3d(CDC *pDC);

	// Frees GDI objects and restores the state of the device context.
	virtual void ClearDC(CDC* pDC);
	// Implementation

public:

#ifdef _DEBUG
	virtual void AssertValid() const;
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


#endif // !defined(FO_DBCHARTSHAPE_H__524D925F_791C_4ED9_8F4D_5213F379B4B1__INCLUDED_)
