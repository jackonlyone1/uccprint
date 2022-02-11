// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1C605608_36B9_42E9_AE14_909A2C94C90F__INCLUDED_)
#define AFX_STDAFX_H__1C605608_36B9_42E9_AE14_909A2C94C90F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if _MSC_VER < 1500
	#define WINVER				0x0400
	#if _MSC_VER >= 1300
		#define _WIN32_WINNT	0x0400
	#endif
#endif

#include <ucctargetver.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

typedef HANDLE BDHANDLE;

#pragma warning (disable : 4018)
#pragma warning (disable : 4100)

#include <afxdb.h>          // Database extensions
#include <afxtempl.h>
#include <afxpriv.h>         //Print preview

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>

#include "fo.h"

// zhj
#include "GdiplusH.h"
// zhj

#pragma warning (disable : 4018)
#pragma warning (disable : 4100)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif// !defined(AFX_STDAFX_H__B5A11857_F96A_11DD_A440_525400EA266C__INCLUDED_)
