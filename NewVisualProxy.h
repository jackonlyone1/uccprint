#if !defined(FO_NEWVISUALPROXY_H__C4F5BA8E_D795_41AD_851D_FB8B93DE7AFD__INCLUDED_)
#define AFC_NEWVISUALPROXY_H__C4F5BA8E_D795_41AD_851D_FB8B93DE7AFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: ucancode.net Software.
//------------------------------------------------------
#include "FOPVisualProxy.h"
#include "FOPGDIPlusProxy.h"

///////////////////////////////////////////////////////////////
// CNewVisualProxy

#define P_ID_CONNECT_FIELD  FO_CUSTOM_PROP_ID + 102
#define P_ID_DBNAME_CHANGED	FO_CUSTOM_PROP_ID + 103
#define P_ID_DBNAME_CORRECTED FO_CUSTOM_PROP_ID + 104

 
//===========================================================================
// Summary:
//     The CNewVisualProxy class derived from CFOPVisualProxy
//      New Visual Proxy
//===========================================================================

class CNewVisualProxy : public CFOPVisualProxy  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CNewVisualProxy---New Visual Proxy, Specifies a CNewVisualProxy object.
	DECLARE_DYNCREATE(CNewVisualProxy);
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Visual Proxy, Constructs a CNewVisualProxy object.
	//		Returns A  value.
	CNewVisualProxy();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C New Visual Proxy, Destructor of class CNewVisualProxy
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CNewVisualProxy();
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

	// Generate dimension text.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Generate Dimension Text, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nLength---nLength, Specifies A integer value.
	virtual CString GenerateDimText(int nLength);

	// Drawing selection additional type.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw Additional With Type, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		&nType---&nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void DoDrawAddiWithType(CDC *pDC,const CRect &rcPos,const UINT &nType);

	// Convert current file to bitmap.
	// strFile -- file name.
	// bmp -- output bitmap handle.
	// cx -- width of the output bitmap.
	// cy -- height of the output bitmap.
	// crBack -- back color of the output bitmap.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Bitmap, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&strFile---&strFile, Specifies A CString type value.  
	//		&bmp---Specifies a E-XD++ CFOBitmap &bmp object.  
	//		cx---Specifies A integer value.  
	//		cy---Specifies A integer value.  
	//		crBack---crBack, Specifies A 32-bit value used as a color value.  
	//		255---Specifies a 255 object.  
	//		255)---Specifies a 255) object.
	virtual BOOL GetBitmap(const CString &strFile,CFOBitmap &bmp, int cx, int cy,COLORREF crBack = RGB(255,255,255));

	// Init default property values.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Default Property, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		CArray<FOP_CUST_PROP---Array< F O P_ C U S T_ P R O P, Specifies A array.  
	//		&mpProp---&mpProp, Specifies a FOP_CUST_PROP> &mpProp object.
	virtual void DoInitDefaultProp(CArray<FOP_CUST_PROP,FOP_CUST_PROP> &mpProp);

	// Do generate the tooltip text of additional icons.
	// strGen -- tooltip text that generated.
	// nType -- icon type ID.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Generate Additional Tool Tips, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&strGen---&strGen, Specifies A CString type value.  
	//		&nType---&nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void DoGenAddiToolTips(CString &strGen, const UINT &nType);

	// Generate the ports scales value of the CFODrawPortsShape
	// mpSpot -- list of the default ports
	
	//-----------------------------------------------------------------------
	// Summary:
	// Generate Default Ports, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		CArray<FOP_PortScale---Array< F O P_ Port Scale, Specifies A array.  
	//		mpSpot---mpSpot, A pointer to the FOP_PortScale> or NULL if the call failed.  
	//		&nShapeType---Shape Type, Specifies A integer value.
	virtual void GenerateDefaultPorts(CArray<FOP_PortScale,FOP_PortScale>* mpSpot,const int &nShapeType);

};

///////////////////////////////////////////////////////////////
// CNewVisualProxy2

 
//===========================================================================
// Summary:
//     The CNewVisualProxy2 class derived from CFOPGDIPlusProxy
//      New Visual Proxy2
//===========================================================================

class CNewVisualProxy2 : public CFOPGDIPlusProxy  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CNewVisualProxy2---New Visual Proxy2, Specifies a CNewVisualProxy2 object.
	DECLARE_DYNCREATE(CNewVisualProxy2);
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Visual Proxy2, Constructs a CNewVisualProxy2 object.
	//		Returns A  value.
	CNewVisualProxy2();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C New Visual Proxy2, Destructor of class CNewVisualProxy2
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CNewVisualProxy2();
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
	
	// Generate dimension text.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Generate Dimension Text, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nLength---nLength, Specifies A integer value.
	virtual CString GenerateDimText(int nLength);
	
	// Drawing selection additional type.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw Additional With Type, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		&nType---&nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void DoDrawAddiWithType(CDC *pDC,const CRect &rcPos,const UINT &nType);
	
	// Convert current file to bitmap.
	// strFile -- file name.
	// bmp -- output bitmap handle.
	// cx -- width of the output bitmap.
	// cy -- height of the output bitmap.
	// crBack -- back color of the output bitmap.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Bitmap, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&strFile---&strFile, Specifies A CString type value.  
	//		&bmp---Specifies a E-XD++ CFOBitmap &bmp object.  
	//		cx---Specifies A integer value.  
	//		cy---Specifies A integer value.  
	//		crBack---crBack, Specifies A 32-bit value used as a color value.  
	//		255---Specifies a 255 object.  
	//		255)---Specifies a 255) object.
	virtual BOOL GetBitmap(const CString &strFile,CFOBitmap &bmp, int cx, int cy,COLORREF crBack = RGB(255,255,255));

	// Init default property values.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Default Property, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		CArray<FOP_CUST_PROP---Array< F O P_ C U S T_ P R O P, Specifies A array.  
	//		&mpProp---&mpProp, Specifies a FOP_CUST_PROP> &mpProp object.
	virtual void DoInitDefaultProp(CArray<FOP_CUST_PROP,FOP_CUST_PROP> &mpProp);

	// Do generate the tooltip text of additional icons.
	// strGen -- tooltip text that generated.
	// nType -- icon type ID.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Generate Additional Tool Tips, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&strGen---&strGen, Specifies A CString type value.  
	//		&nType---&nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void DoGenAddiToolTips(CString &strGen, const UINT &nType);

	// Generate the ports scales value of the CFODrawPortsShape
	// mpSpot -- list of the default ports
	
	//-----------------------------------------------------------------------
	// Summary:
	// Generate Default Ports, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		CArray<FOP_PortScale---Array< F O P_ Port Scale, Specifies A array.  
	//		mpSpot---mpSpot, A pointer to the FOP_PortScale> or NULL if the call failed.  
	//		&nShapeType---Shape Type, Specifies A integer value.
	virtual void GenerateDefaultPorts(CArray<FOP_PortScale,FOP_PortScale>* mpSpot,const int &nShapeType);

};

#endif // !defined(AFC_NEWVISUALPROXY_H__C4F5BA8E_D795_41AD_851D_FB8B93DE7AFD__INCLUDED_)
