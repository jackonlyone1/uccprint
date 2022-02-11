// UCCPrint.h : main header file for the UCCPRINT application
//

#if !defined(AFX_UCCPRINT_H__C4D81BB2_6795_450D_8CE4_EB7ED81AA069__INCLUDED_)
#define AFX_UCCPRINT_H__C4D81BB2_6795_450D_8CE4_EB7ED81AA069__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ConnectDlg.h"
#include "registry.h"
#define REG_EDITPAD_IDE     _T ("Software\\UCanCode Software\\UCCPrint\\IDE")

/////////////////////////////////////////////////////////////////////////////
// CUCCPrintApp:
// See UCCPrint.cpp for the implementation of this class
//

typedef struct tagFO_STATE
{
	CString			strState1;		 // X Scale value.
	CString		strState2;		 // Y Scale value
} FOSTATE;

struct Fl_ODBC_Field
{
	CString		m_strColumn;
	int			m_nIndex;
    long		m_columnLength;
    long		m_columnType;
    long		m_columnPrecision;
};


 
//===========================================================================
// Summary:
//      To use a CTKOptions object, just call the constructor.
//      T K Options
//===========================================================================

class CTKOptions
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// T K Options, Constructs a CTKOptions object.
	//		Returns A  value.
	CTKOptions();
	
 
	// Page Caption, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
    CString		m_strPageCaption;
 
	// Page Fill Type, This member specify short object.  
	short		m_nPageFillType;
 
	// Page B K Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crPageBKColor;
 
	// Page Pattern Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crPagePatternColor;
 
	// Page Page B K Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crPagePageBKColor;
	
 
	// Object Name, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strObjectName;
 
	// Object Caption, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
    CString		m_strObjectCaption;
 
	// Object Flat3 D, Specify A Boolean value.  
	bool		m_bObjectFlat3D;
 
	// Object Fill Type, This member specify short object.  
	short		m_nObjectFillType;
 
	// Object B K Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crObjectBKColor;
 
	// Object Pattern Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crObjectPatternColor;
 
	// Object Tool Tip, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strObjectToolTip;
 
	// Text Name, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strTextName;
 
	// Text Size, This member specify short object.  
	short		m_nTextSize;
 
	// Text Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crTextColor;
 
	// Text Blod, Specify A Boolean value.  
	bool	m_bTextBlod;
 
	// Text Italic, Specify A Boolean value.  
	bool	m_bTextItalic;
 
	// Text Under Line, Specify A Boolean value.  
	bool	m_bTextUnderLine;
 
	// Border Line Width, This member specify short object.  
	short	m_nBorderLineWidth;
 
	// Border Line Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crBorderLineColor;
 
	// Border Line Type, This member specify short object.  
	short	m_nBorderLineType;
 
	// Line Start Arrow, This member specify short object.  
	short	m_nLineStartArrow;
 
	// Line End Arrow, This member specify short object.  
	short	m_nLineEndArrow;
 
	// Position Left, This member specify double object.  
	double	m_fPositionLeft;
 
	// Position Right, This member specify double object.  
	double	m_fPositionRight;
 
	// Position Width, This member specify double object.  
	double	m_fPositionWidth;
 
	// Position Height, This member specify double object.  
	double	m_fPositionHeight;
 
	// Position Rotate, This member specify The float keyword designates a 32-bit floating-point number.  
	float	m_fPositionRotate;
 
	// Shadow Visual, Specify A Boolean value.  
	bool	m_bShadowVisual;
 
	// Shadow Type, This member specify short object.  
	short	m_nShadowType;
 
	// Shadow B K Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crShadowBKColor;
 
	// Shadow Pattern Color, This member sets A 32-bit value used as a color value.  
	COLORREF	m_crShadowPatternColor;
 
	// Shadow X Offset, This member specify short object.  
	short	m_nShadowXOffset;
 
	// Shadow Y Offset, This member specify short object.  
	short	m_nShadowYOffset;
 
	// Resize Protect, Specify A Boolean value.  
	bool	m_bResizeProtect;
 
	// Delete Protect, Specify A Boolean value.  
	bool	m_bDeleteProtect;
 
	// Rotate Protect, Specify A Boolean value.  
	bool	m_bRotateProtect;
 
	// Tab Order Protect, Specify A Boolean value.  
	bool	m_bTabOrderProtect;
 
	// Select Protect, Specify A Boolean value.  
	bool	m_bSelectProtect;
 
	// Move Protect, Specify A Boolean value.  
	bool	m_bMoveProtect;
 
	// Print Protect, Specify A Boolean value.  
	bool	m_bPrintProtect;
 
	// Copy Protect, Specify A Boolean value.  
	bool	m_bCopyProtect;
 
	// Aspect Ratio, Specify A Boolean value.  
	bool	m_bAspectRatio;
 
	// X Position Protect, Specify A Boolean value.  
	bool	m_bXPosProtect;
 
	// Y Position Protect, Specify A Boolean value.  
	bool	m_bYPosProtect;
 
	// Width Protect, Specify A Boolean value.  
	bool	m_bWidthProtect;
 
	// Height Protect, Specify A Boolean value.  
	bool	m_bHeightProtect;
};

 
//===========================================================================
// Summary:
//     The CUCCPrintApp class derived from CWinApp
//      U C C Print Application
//===========================================================================

class CUCCPrintApp : public CWinApp
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// U C C Print Application, Constructs a CUCCPrintApp object.
	//		Returns A  value.
	CUCCPrintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUCCPrintApp)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Instance, Override to perform Windows instance initialization, such as creating your window objects.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL InitInstance();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Exit Instance, Override to clean up when your application terminates.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a int type value.
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

 
	// Current Document Template, This member maintains a pointer to the object CMultiDocTemplate.  
	CMultiDocTemplate* pCurDocTemplate;

 
	// m_hConnect, This member specify BDHANDLE object.  
	BDHANDLE m_hConnect;   
 
	// Data Source, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sDataSource;
 
	// m_sUser, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sUser;
 
	// m_sPassword, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sPassword;
 
	// m_sHost, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_sHost;
	
 
	// m_strSql, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strSql;		
 
	// m_strDsn, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString		m_strDsn;

 
	// Open Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int			m_nOpenType;

 
	// Print View, This member sets TRUE if it is right.  
	BOOL	m_bPrintView;
 
	// m_Options, This member specify CTKOptions object.  
	CTKOptions	m_Options;
 
	// String Dsn, The member supports arrays of CString objects.  
	CStringArray  m_arrStrDsn;		// read from registry
	
 
	// m_connDlg, This member specify CConnectDlg object.  
	CConnectDlg	  m_connDlg;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Directory Exists, None Description.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		Path---Path, Specifies A CString type value.
	BOOL DirectoryExists(const CString& Path);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Make Directory, None Description.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pcszDirectory---pcszDirectory, Specifies A CString type value.
	BOOL MakeDirectory(const CString& pcszDirectory);
 
	// Default Connect Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_nDefaultConnectType;
	
	CArray <Fl_ODBC_Field, Fl_ODBC_Field> m_TableInfo;
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Login, None Description.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL Login();
 
	// This member specify E-XD++ CFOPODBCDataSource object.  
	CFOPODBCDataSource	m_odbc;
public:
 
	// Open Template, This member sets TRUE if it is right.  
	BOOL bOpenTemplate;
 
	// Template File, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strTemplateFile;
 
	// Template Folder, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strTemplateFolder;

 
	// Open File Now, This member sets TRUE if it is right.  
	BOOL bOpenFileNow;
 
	// Current Path, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strCurPath;
 
	// m_hModule, This member specify HMODULE object.  
	HMODULE m_hModule;

 
	// Current Open Mode, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int nCurOpenMode;
 
	// Current Sel, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int nCurSel;

 
	// The member supports arrays of CString objects.  
	CStringArray m_dbcols;
	//
 
	// Back Image File, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strBackImageFile;

	// Saving keys.
 
	// m_bGrid, This member sets TRUE if it is right.  
	BOOL	m_bGrid;
 
	// Free Form Drawing, This member sets TRUE if it is right.  
	BOOL	m_bFreeFormDrawing;
 
	// m_bGuide, This member sets TRUE if it is right.  
	BOOL	m_bGuide;
 
	// Grid Snap, This member sets TRUE if it is right.  
	BOOL	m_bGridSnap;
 
	// New Snap, This member sets TRUE if it is right.  
	BOOL	m_bNewSnap;
 
	// m_bMargin, This member sets TRUE if it is right.  
	BOOL	m_bMargin;
 
	// Show Ports, This member sets TRUE if it is right.  
	BOOL	m_bShowPorts;
 
	// Drawing From Center, This member sets TRUE if it is right.  
	BOOL	m_bDrawingFromCenter;
 
	// Glue To Shape, This member sets TRUE if it is right.  
	BOOL	m_bGlueToShape;
 
	// Glue To Spot, This member sets TRUE if it is right.  
	BOOL	m_bGlueToSpot;
	
 
	// Snap To Help Line, This member sets TRUE if it is right.  
	BOOL	m_bSnapToHelpLine;
 
	// Snap To Intersect, This member sets TRUE if it is right.  
	BOOL	m_bSnapToIntersect;
 
	// List Bar, This member sets TRUE if it is right.  
	BOOL	m_bListBar;
 
	// m_bRuler, This member sets TRUE if it is right.  
	BOOL	m_bRuler;
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Save Setting, Saves the specify data to a file..

	void DoSaveSetting();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Load Setting, Loads the specify data from a file.

	void DoLoadSetting();

// Implementation
	//{{AFX_MSG(CUCCPrintApp)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Application About, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAppAbout();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Open Template, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOpenTemplate();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On New From Blannk, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNewFromBlannk();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Fo Import Dbsource, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFoImportDbsource();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Bt Hj View, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnBtHjView();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Page Option, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnPageOption();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

extern CUCCPrintApp theApp;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCCPRINT_H__C4D81BB2_6795_450D_8CE4_EB7ED81AA069__INCLUDED_)
