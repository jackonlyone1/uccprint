/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jorge Lodos
// All rights reserved
//
// Distribute and use freely, except:
// 1. Don't alter or remove this notice.
// 2. Mark the changes you made
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    lodos@cigb.edu.cu
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBSTATIC_H__40E4BDE3_BD3A_11D1_89F4_0000E81D3D27__INCLUDED_)
#define AFX_DIBSTATIC_H__40E4BDE3_BD3A_11D1_89F4_0000E81D3D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DIBStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDIBStatic window
#include "dib.h"

 
//===========================================================================
// Summary:
//     The CDIBStatic class derived from CStatic
//      D I B Static
//===========================================================================

class CDIBStatic : public CStatic
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// D I B Static, Constructs a CDIBStatic object.
	//		Returns A  value.
	CDIBStatic();

// Attributes
public:
 
	// D I B, This member specify CDib object.  
	CDib m_DIB;

public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Valid Dib, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL IsValidDib() const { return (m_DIB.IsValid()); }

// Operations
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load Dib, Call this function to read a specified number of bytes from the archive.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	BOOL LoadDib(LPCTSTR lpszFileName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load Dib, Call this function to read a specified number of bytes from the archive.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		file---Specifies a CFile& file object.
	BOOL LoadDib(CFile& file);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Update Dib, Call this member function to update the object.

	void UpdateDib();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Remove Dib, Call this function to remove a specify value from the specify object.

	void RemoveDib() { m_DIB.Invalidate(); UpdateDib(); }
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Realize Palette, Do a event. 
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		bForceBackGround---Force Back Ground, Specifies A Boolean value.
	BOOL DoRealizePalette(BOOL bForceBackGround);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C D I B Static, Destructor of class CDIBStatic
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CDIBStatic();

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear Dib, Remove the specify data from the list.

	void ClearDib();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Paint Dib, None Description.
	// Parameters:
	//		bDibValid---Dib Valid, Specifies A Boolean value.
	void PaintDib(BOOL bDibValid);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDIBStatic)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Ctl Color, None Description.
	//		Returns A afx_msg HBRUSH value.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		nCtlColor---Ctl Color, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Query New Palette, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns TRUE on success; FALSE otherwise.
	afx_msg BOOL OnQueryNewPalette();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Palette Changed, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pFocusWnd---Focus Window, A pointer to the CWnd or NULL if the call failed.
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG

	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBSTATIC_H__40E4BDE3_BD3A_11D1_89F4_0000E81D3D27__INCLUDED_)
