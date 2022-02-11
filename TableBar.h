#if !defined(AFX_TABLEBAR_H__432237DD_75B1_4E05_AC55_E7E1D036303A__INCLUDED_)
#define AFX_TABLEBAR_H__432237DD_75B1_4E05_AC55_E7E1D036303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl window
#include "SortListCtrl.h"
#include "FOPPropList.h"

 
//===========================================================================
// Summary:
//     The CDBSortListCtrl class derived from CFOBaseGridListCtrl
//      D B Sort List 
//===========================================================================

class CDBSortListCtrl : public CFOBaseGridListCtrl
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// D B Sort List , Constructs a CDBSortListCtrl object.
	//		Returns A  value.
	CDBSortListCtrl();
	
	// Attributes
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBSortListCtrl)
	//}}AFX_VIRTUAL
	
	// Do ole drag and drop.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Ole Drag And Drop, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pItem---pItem, A pointer to the CFOToolBoxItem or NULL if the call failed.
	virtual void DoOleDragAndDrop(CFOToolBoxItem* pItem);
	
	// Get drop source.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Drop Source, You construct a CDBSortListCtrl object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODropSource,or NULL if the call failed
	virtual CFODropSource* CreateDropSource();
	
	// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C D B Sort List , Destructor of class CDBSortListCtrl
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CDBSortListCtrl();
	
	//{{AFX_MSG(CDBSortListCtrl)
	
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
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Down, Called when the user presses the left mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Up, Called when the user releases the left mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};


 
//===========================================================================
// Summary:
//     The CMyTabCtrl class derived from CFOTabCtrl
//      My Tab 
//===========================================================================

class CMyTabCtrl : public CFOTabCtrl
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// My Tab , Constructs a CMyTabCtrl object.
	//		Returns A  value.
	CMyTabCtrl();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabCtrl)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C My Tab , Destructor of class CMyTabCtrl
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CMyTabCtrl();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class CUCCPrintView;
/////////////////////////////////////////////////////////////////////////////
// CTableBar
 
//===========================================================================
// Summary:
//     The CTableBar class derived from CFOPControlBar
//      Table Bar
//===========================================================================

class CTableBar : public CFOPControlBar
{

	// Construction
public:
	// constructor
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Table Bar, Constructs a CTableBar object.
	//		Returns A  value.
	CTableBar();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Property, Call InitProperty after creating a new object.

	void InitProperty();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Update Property, Call this member function to update the object.
	// Parameters:
	//		pView---pView, A pointer to the CUCCPrintView or NULL if the call failed.  
	//		&bWithAction---With Action, Specifies A Boolean value.
	void UpdateProperty(CUCCPrintView* pView, const BOOL &bWithAction = FALSE);
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Property State, Sets a specify value to current class CTableBar

	void SetPropState ();
	
	enum
	{
		idPageCaption = 1,
			idPageFillType,
			idPageBKColor,
			idPagePatternColor,
			idPagePageBKColor,
			idObjectName,
			idObjectCaption,
			idObjectFlat3D,
			idObjectFillType,
			idObjectBKColor,
			idObjectPatternColor,
			idObjectToolTip,
			idTextName,
			idTextSize,
			idTextColor,
			idTextBlod,
			idTextItalic,
			idTextUnderLine,
			idBorderLineWidth,
			idBorderLineColor,
			idBorderLineType,
			idLineStartArrow,
			idLineEndArrow,
			idPositionLeft,
			idPositionRight,
			idPositionWidth,
			idPositionHeight,
			idPositionRotate,
			idShadowVisual,
			idShadowType,
			idShadowBKColor,
			idShadowPatternColor,
			idShadowXOffset,
			idShadowYOffset,
			idResizeProtect,
			idDeleteProtect,
			idRotateProtect,
			idTabOrderProtect,
			idSelectProtect,
			idMoveProtect,
			idPrintProtect,
			idCopyProtect,
			idAspectRatio,
			idXPosProtect,
			idYPosProtect,
			idWidthProtect,
			idHeightProtect,
	};
	
 
	// m_Shapes, This member specify E-XD++ CFOListItemObjList object.  
	CFOListItemObjList m_Shapes;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load From File, Call this function to read a specified number of bytes from the archive.

	void LoadFromFile();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Object By I D, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns a pointer to the object CFOListItemObj ,or NULL if the call failed  
	// Parameters:
	//		nIndex---nIndex, Specifies A integer value.
	CFOListItemObj *FindObjByID(int nIndex);

 
	// Tool Box, This member specify E-XD++ CFOMultiToolBoxWnd object.  
	CFOMultiToolBoxWnd m_wndToolBox;

	// Toolbox wnd.
 
	// m_wndTool, This member specify E-XD++ CFOPPropList object.  
	CFOPPropList m_wndTool;
	
 
	// m_wndTab, This member specify E-XD++ CFOTabCtrl object.  
	CFOTabCtrl m_wndTab;
 
	// Tree , This member specify CSortListCtrl object.  
	CSortListCtrl m_TreeCtrl;
 
	// Column , This member specify CDBSortListCtrl object.  
	CDBSortListCtrl m_ColCtrl;

 
	// Context Image Small, This member is a collection of same-sized images.  
	CImageList m_ContextImageSmall;

	// Init shapes.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Shapes, Call InitShapes after creating a new object.
	// Parameters:
	//		*pDataModel---Data Model, A pointer to the CFODataModel  or NULL if the call failed.
	void InitShapes(CFODataModel *pDataModel);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unique D B Name, Returns the specified value.
	//		Returns a CString type value.  
	// Parameters:
	//		*m_ShapeSet---Shape Set, A pointer to the CFODrawShapeSet  or NULL if the call failed.  
	//		&strStart---&strStart, Specifies A CString type value.
	CString GetUniqueDBName(CFODrawShapeSet *m_ShapeSet, const CString &strStart);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Find D B Name, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		*m_ShapeSet---Shape Set, A pointer to the CFODrawShapeSet  or NULL if the call failed.  
	//		&strFind---&strFind, Specifies A CString type value.
	BOOL FindDBName(CFODrawShapeSet *m_ShapeSet, const CString &strFind);

	// Add select columns.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Column, Adds an object to the specify list.
	// Parameters:
	//		&strColName---Column Name, Specifies A CString type value.  
	//		&nImage---&nImage, Specifies A integer value.
	void AddColumn(const CString &strColName, const int &nImage = 1);

	// Delete all items.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Delete All, Deletes the given object.

	void DeleteAll();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Select Item, Call this function to select the given item.
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	void SelectItem(CFODrawShape *pShape);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableBar)
	//}}AFX_VIRTUAL
protected:
 
	// m_pView, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	CUCCPrintView* m_pView;
 
	// Old Select, This member maintains a pointer to the object CFODrawShape.  
	CFODrawShape *pOldSelect;
 
	// Old Select Count, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int nOldSelectCount;
// Implementation
public:

	// destructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Table Bar, Destructor of class CTableBar
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CTableBar();

	// Generated message map functions
protected:

	//{{AFX_MSG(CTableBar)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create, Called as a part of window creation.
	//		Returns a int type value.  
	// Parameters:
	//		lpCreateStruct---Create Struct, Specifies a LPCREATESTRUCT lpCreateStruct object.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Size, Called after the size of CWnd has changed.
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		cx---Specifies A integer value.  
	//		cy---Specifies A integer value.
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Erase Background, Called when the window background needs erasing.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Itemchanged Context List, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnItemchangedContextList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Property Changed, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns A 32-bit value returned from a window procedure or callback function.  
	// Parameters:
	//		WPARAM---P A R A M, Provides additional information used in processing the message. The parameter value depends on the message.  
	//		LPARAM---P A R A M, Specifies A lparam value.
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEBAR_H__432237DD_75B1_4E05_AC55_E7E1D036303A__INCLUDED_)
