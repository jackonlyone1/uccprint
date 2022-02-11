#if !defined(AFX_MBTEMPLATEPAGE0_H__DCFC4913_1A9B_11D6_A51E_525400EA266C__INCLUDED_)
#define AFX_MBTEMPLATEPAGE0_H__DCFC4913_1A9B_11D6_A51E_525400EA266C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MBTemplatePage0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMBTemplatePage0 dialog
#include "MBTemplateFileObj.h"
#include "DIBStatic.h"

 
//===========================================================================
// Summary:
//     The CMBTemplatePage0 class derived from CDialog
//      M B Template Page0
//===========================================================================

class CMBTemplatePage0 : public CDialog
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// M B Template Page0, Constructs a CMBTemplatePage0 object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CMBTemplatePage0(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMBTemplatePage0)
	enum { IDD = IDD_MB_NEW_TEMPLATE_PAGE0 };
 
	// m_listItem, This member specify CListCtrl object.  
	CListCtrl	m_listItem;
	//}}AFX_DATA
 
	// m_btnMax, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_btnMax;
 
	// m_btnMin, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_btnMin;
 
	// m_btnLie, This member specify E-XD++ CFOImageButton object.  
	CFOImageButton	m_btnLie;

 
	// Template File, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strTemplateFile;
 
	// Template Folder, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strTemplateFolder;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Value, Returns the specified value.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL GetValue();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial List  Cols, Call InitListCtrlCols after creating a new object.

	void InitListCtrlCols();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Insert Items, Inserts a child object at the given index..

	void InsertItems();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Image List, Call InitImageList after creating a new object.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL InitImageList();

	CImageList	m_cImageListNormal, m_cImageListSmall, m_cImageListState;
	
 
	// D I B Static , This member specify CDIBStatic object.  
	CDIBStatic m_DIBStaticCtrl;
	// Attributes
public:
	// Attributes
 
	// m_Components, This member specify CMBTemplateFileObjList object.  
	CMBTemplateFileObjList m_Components;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load From File, Call this function to read a specified number of bytes from the archive.

	void LoadFromFile();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Object By I D, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns a pointer to the object CMBTemplateFileObj ,or NULL if the call failed  
	// Parameters:
	//		nIndex---nIndex, Specifies A integer value.
	CMBTemplateFileObj *FindObjByID(int nIndex);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMBTemplatePage0)
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Data Exchange, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDX---D X, A pointer to the CDataExchange or NULL if the call failed.
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMBTemplatePage0)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Click Mb List, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnClickMbList(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Double click Mb List, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnDblclkMbList(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mb Maximize Button, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMbMaxButton();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mb Minimize Button, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMbMinButton();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mb Lie Button, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMbLieButton();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy();
	
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
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Rclick Mb List, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnRclickMbList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBTEMPLATEPAGE0_H__DCFC4913_1A9B_11D6_A51E_525400EA266C__INCLUDED_)
