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

// dib.h

#ifndef _INC_DIB
#define _INC_DIB

/* DIB constants */
#define PALVERSION   0x300

/* Dib Header Marker - used in writing DIBs to files */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

/* DIB Macros*/
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

 
//===========================================================================
// Summary:
//     The CDib class derived from CObject
//      Dib
//===========================================================================

class CDib : public CObject
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N A M I C, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CDib---Dib, Specifies a CDib object.
	DECLARE_DYNAMIC(CDib)

// Constructors
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Dib, Constructs a CDib object.
	//		Returns A  value.
	CDib();

// Attributes
protected:
 
	// m_pBits, This member sets An 8-bit integer that is not signed.  
	LPBYTE m_pBits;
 
	// B M I, This member specify LPBITMAPINFO object.  
	LPBITMAPINFO m_pBMI;
public:	
 
	// m_pPalette, This member maintains a pointer to the object CPalette.  
	CPalette* m_pPalette;

public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Width, None Description.
	//		Returns A 32-bit unsigned integer or the address of a segment and its associated offset.
	DWORD Width()     const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Height, None Description.
	//		Returns A 32-bit unsigned integer or the address of a segment and its associated offset.
	DWORD Height()    const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Num Colors, None Description.
	//		Returns A 16-bit unsigned integer.
	WORD  NumColors() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Valid, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL  IsValid()   const { return (m_pBMI != NULL); }

// Operations
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Paint, None Description.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		HDC---D C, Specifies a HDC object.  
	//		LPRECT---P R E C T, Specifies a LPRECT object.  
	//		LPRECT---P R E C T, Specifies a LPRECT object.
	BOOL  Paint(HDC, LPRECT, LPRECT) const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy To Handle, Create a duplicate copy of this object.
	//		Returns A HGLOBAL value.
	HGLOBAL CopyToHandle()           const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save, Call this function to save the specify data to a file.
	//		Returns A 32-bit unsigned integer or the address of a segment and its associated offset.  
	// Parameters:
	//		file---Specifies a CFile& file object.
	DWORD Save(CFile& file)          const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Read, Call this function to read the specify data from an archive.
	//		Returns A 32-bit unsigned integer or the address of a segment and its associated offset.  
	// Parameters:
	//		file---Specifies a CFile& file object.
	DWORD Read(CFile& file);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Read From Handle, Call this function to read the specify data from an archive.
	//		Returns A 32-bit unsigned integer or the address of a segment and its associated offset.  
	// Parameters:
	//		hGlobal---hGlobal, Specifies a HGLOBAL hGlobal object.
	DWORD ReadFromHandle(HGLOBAL hGlobal);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Invalidate, Invalidates the specify area of object. 

	void Invalidate() { Free(); }

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		ar---Specifies a CArchive& ar object.
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Dib, Destructor of class CDib
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CDib();

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Palette, You construct a CDib object in two steps. First call the constructor, then call Create, which creates the object.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL  CreatePalette();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Palette Size, None Description.
	//		Returns A 16-bit unsigned integer.
	WORD  PaletteSize() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Free, None Description.

	void Free();

public:
#ifdef _DEBUG
	
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
	// None Description.
	//		Returns A CDib& operator value.  
	// Parameters:
	//		dib---Specifies a CDib& dib object.
	CDib& operator = (CDib& dib);
};

#endif //!_INC_DIB
