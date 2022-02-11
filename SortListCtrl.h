#ifndef SORTLISTCTRL_H
#define SORTLISTCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef SORTHEADERCTRL_H
	#include "SortHeaderCtrl.h"
#endif	// SORTHEADERCTRL_H

#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG


 
//===========================================================================
// Summary:
//     The CSortListCtrl class derived from CFOBaseGridListCtrl
//      Sort List 
//===========================================================================

class CSortListCtrl : public CFOBaseGridListCtrl
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sort List , Constructs a CSortListCtrl object.
	//		Returns A  value.
	CSortListCtrl();

// Attributes
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Sort List , Destructor of class CSortListCtrl
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CSortListCtrl();

	//{{AFX_MSG(CSortListCtrl)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Column Click, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Double click List1, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//message map functions On Measure Item
	
	//-----------------------------------------------------------------------
	// Summary:
	// Measure Item, None Description.
	// Parameters:
	//		lpMeasureItemStruct---Measure Item Struct, Specifies a LPMEASUREITEMSTRUCT lpMeasureItemStruct object.
	afx_msg void	MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

 
//===========================================================================
// Summary:
//     The CNewDBSortListCtrl class derived from CListCtrl
//      New D B Sort List 
//===========================================================================

class CNewDBSortListCtrl : public CListCtrl
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New D B Sort List , Constructs a CNewDBSortListCtrl object.
	//		Returns A  value.
	CNewDBSortListCtrl();
	
	// Attributes
public:
	
	// Operations
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Headings, Sets a specify value to current class CNewDBSortListCtrl
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		uiStringID---String I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	BOOL SetHeadings( UINT uiStringID );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Headings, Sets a specify value to current class CNewDBSortListCtrl
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		strHeadings---strHeadings, Specifies A CString type value.
	BOOL SetHeadings( const CString& strHeadings );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Headings, Sets a specify value to current class CNewDBSortListCtrl
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&arrString---&arrString, Specifies A CString type value.
	BOOL SetHeadings(CStringArray &arrString);
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Item, Adds an object to the specify list.
	//		Returns a int type value.  
	// Parameters:
	//		pszText---pszText, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		...---Specifies a ... object.
	int AddItem( LPCTSTR pszText, ... );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Item, Adds an object to the specify list.
	//		Returns a int type value.  
	// Parameters:
	//		&arrString---&arrString, Specifies A CString type value.
	int AddItem(CStringArray &arrString);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Delete Item, Deletes the given object.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		iItem---iItem, Specifies A integer value.
	BOOL DeleteItem( int iItem );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Delete All Items, Deletes the given object.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL DeleteAllItems();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load Column Information, Call this function to read a specified number of bytes from the archive.

	void LoadColumnInfo();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Column Information, Call this function to save the specify data to a file.

	void SaveColumnInfo();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Item Text, Sets a specify value to current class CNewDBSortListCtrl
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		nItem---nItem, Specifies A integer value.  
	//		nSubItem---Child Item, Specifies A integer value.  
	//		lpszText---lpszText, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sort, None Description.
	// Parameters:
	//		iColumn---iColumn, Specifies A integer value.  
	//		bAscending---bAscending, Specifies A Boolean value.
	void Sort( int iColumn, BOOL bAscending );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Item Data, Sets a specify value to current class CNewDBSortListCtrl
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		nItem---nItem, Specifies A integer value.  
	//		dwData---dwData, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.
	BOOL SetItemData(int nItem, DWORD dwData);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Item Data, Returns the specified value.
	//		Returns A 32-bit unsigned integer or the address of a segment and its associated offset.  
	// Parameters:
	//		nItem---nItem, Specifies A integer value.
	DWORD GetItemData(int nItem) const;
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewDBSortListCtrl)
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Subclass Window, None Description.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C New D B Sort List , Destructor of class CNewDBSortListCtrl
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CNewDBSortListCtrl();
	
	// Generated message map functions
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Compare Function, None Description.
	// This member function is a static function.
	//		Returns a int type value.  
	// Parameters:
	//		lParam1---lParam1, Specifies A lparam value.  
	//		lParam2---lParam2, Specifies A lparam value.  
	//		lParamData---Parameter Data, Specifies A lparam value.
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	
	//-----------------------------------------------------------------------
	// Summary:
	// Free Item Memory, None Description.
	// Parameters:
	//		iItem---iItem, Specifies A integer value.
	void FreeItemMemory( const int iItem );
	BOOL CNewDBSortListCtrl::SetTextArray( int iItem, LPTSTR* arrpsz );
	LPTSTR* CNewDBSortListCtrl::GetTextArray( int iItem ) const;
	
 
	// m_ctlHeader, This member specify CSortHeaderCtrl object.  
	CSortHeaderCtrl m_ctlHeader;
	
 
	// Num Columns, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_iNumColumns;
 
	// Sort Column, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_iSortColumn;
 
	// Sort Ascending, This member sets TRUE if it is right.  
	BOOL m_bSortAscending;
	
	//{{AFX_MSG(CNewDBSortListCtrl)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Column Click, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // SORTLISTCTRL_H
