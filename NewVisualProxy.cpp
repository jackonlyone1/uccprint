// NewVisualProxy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NewVisualProxy.h"
#include "resource.h"
#include "UCCPrintDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CNewVisualProxy, CFOPVisualProxy)

CNewVisualProxy::CNewVisualProxy()
{

}

CNewVisualProxy::~CNewVisualProxy()
{

}

/////////////////////////////////////////////////////////////////////////////
// CNewVisualProxy diagnostics

#ifdef _DEBUG
void CNewVisualProxy::AssertValid() const
{
	CObject::AssertValid();
}

void CNewVisualProxy::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

CString CNewVisualProxy::GenerateDimText(int nLength)
{
	CString strReturn;
	strReturn.Format(_T("%u Pixel"),nLength);
	return strReturn;
}

BOOL FOPFileExist2(CString strFilePath)
{
	CFileStatus fs;
	return CFile::GetStatus(strFilePath, fs);
}

void CNewVisualProxy::DoGenAddiToolTips(CString &strGen, const UINT &nType)
{
	if(nType == 31056)
	{
		strGen = _T("Connect &Database Field Name...");
	}
	else if(nType == 31057)
	{
		strGen = _T("Event Setting...");
	}
	else if(nType == 31058)
	{
		strGen = _T("BarCode Setting...");
	}
	else
	{
		CFOPVisualProxy::DoGenAddiToolTips(strGen,nType);
	}
}

void CNewVisualProxy::DoDrawAddiWithType(CDC *pDC,const CRect &rcPos,const UINT &nType)
{
	if(nType == 1102)
	{
		HICON hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_BARCODE), IMAGE_ICON, 16, 16, 0);
		DrawIconEx(pDC->m_hDC, rcPos.left, rcPos.top, hIcon, 16, 16, 0, NULL, DI_NORMAL);
		DestroyIcon(hIcon);
	}
	else
	{
		CFOPVisualProxy::DoDrawAddiWithType(pDC,rcPos,nType);
	}
}

BOOL CNewVisualProxy::GetBitmap(const CString &strFile,CFOBitmap &bmp, int cx, int cy,COLORREF crBack)
{
	
	if(strFile == "BITMAP_350_200")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_350_200);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "BITMAP_8700_5080_MM")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_8700_5080_MM);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "400_200_IN_LABEL")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_400_200_IN_LABEL);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "LABEL_100_34_MM")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_LABEL_100_34_MM);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "262_100_IN_LABEL")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_262_100_IN_LABEL);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "590_463_BACK_IN")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_DVD_590_463_BACK_IN);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "CD_118_118_MM")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_CD_118_118_MM);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(!strFile.IsEmpty() && FOPFileExist2(strFile))
	{
		CMBFileObj m_Obj;
		m_Obj.OpenTemplateDoc(strFile);
		bmp.Backup(m_Obj.m_pBitmap);
	}
	
	
	cx;
	cy;
	crBack;
	
	return TRUE;
}

void CNewVisualProxy::GenerateDefaultPorts(CArray<FOP_PortScale,FOP_PortScale>* mpSpot,const int &nShapeType)
{
	nShapeType;
	mpSpot->RemoveAll();
	{
		mpSpot->SetSize(0);
	}
	
}

void CNewVisualProxy::DoInitDefaultProp(CArray<FOP_CUST_PROP,FOP_CUST_PROP> &mpProp)
{
	// Do not call mpProp.RemoveAll();
	// Port width
	FOP_CUST_PROP m_Rrop1;
	m_Rrop1.nPropId = P_ID_DBNAME_CHANGED;
	m_Rrop1.valDefault.m_nValueType = V_BOOL;
	m_Rrop1.valDefault.m_bValue = FALSE;
	mpProp.Add(m_Rrop1);

	FOP_CUST_PROP m_Rrop;
	m_Rrop.nPropId = P_ID_CONNECT_FIELD;
	m_Rrop.valDefault.m_nValueType = V_STRING;
	m_Rrop.valDefault.m_strValue = _T("");
	mpProp.Add(m_Rrop);

	FOP_CUST_PROP m_Rrop2;
	m_Rrop2.nPropId = P_ID_DBNAME_CORRECTED;
	m_Rrop2.valDefault.m_nValueType = V_BOOL;
	m_Rrop2.valDefault.m_bValue = FALSE;
	mpProp.Add(m_Rrop2);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CNewVisualProxy2, CFOPGDIPlusProxy)

CNewVisualProxy2::CNewVisualProxy2()
{
	
}

CNewVisualProxy2::~CNewVisualProxy2()
{
	
}

/////////////////////////////////////////////////////////////////////////////
// CNewVisualProxy2 diagnostics

#ifdef _DEBUG
void CNewVisualProxy2::AssertValid() const
{
	CObject::AssertValid();
}

void CNewVisualProxy2::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

CString CNewVisualProxy2::GenerateDimText(int nLength)
{
	CString strReturn;
	strReturn.Format(_T("%u Pixel"),nLength);
	return strReturn;
}

void CNewVisualProxy2::DoDrawAddiWithType(CDC *pDC,const CRect &rcPos,const UINT &nType)
{
	if(nType == 1102)
	{
		HICON hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_BARCODE), IMAGE_ICON, 16, 16, 0);
		DrawIconEx(pDC->m_hDC, rcPos.left, rcPos.top, hIcon, 16, 16, 0, NULL, DI_NORMAL);
		DestroyIcon(hIcon);
	}
	else
	{
		CFOPGDIPlusProxy::DoDrawAddiWithType(pDC,rcPos,nType);
	}
}

void CNewVisualProxy2::DoGenAddiToolTips(CString &strGen, const UINT &nType)
{
	if(nType == 31056)
	{
		strGen = _T("Change Database Field Name...");
	}
	else if(nType == 31057)
	{
		strGen = _T("Event Setting...");
	}
	else if(nType == 31058)
	{
		strGen = _T("BarCode Setting...");
	}
	else
	{
		CFOPGDIPlusProxy::DoGenAddiToolTips(strGen,nType);
	}
}

BOOL CNewVisualProxy2::GetBitmap(const CString &strFile,CFOBitmap &bmp, int cx, int cy,COLORREF crBack)
{
	if(strFile == "BITMAP_350_200")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_350_200);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "BITMAP_8700_5080_MM")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_8700_5080_MM);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "400_200_IN_LABEL")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_400_200_IN_LABEL);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "LABEL_100_34_MM")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_LABEL_100_34_MM);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "262_100_IN_LABEL")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_262_100_IN_LABEL);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "590_463_BACK_IN")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_DVD_590_463_BACK_IN);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(strFile == "CD_118_118_MM")
	{
		CClientDC dc(AfxGetMainWnd());
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_CD_118_118_MM);
		bmp.MakeNewBitmap(&dc,&bitmap);
	}
	else if(!strFile.IsEmpty() && FOPFileExist2(strFile))
	{
		CMBFileObj m_Obj;
		m_Obj.OpenTemplateDoc(strFile);
		bmp.Backup(m_Obj.m_pBitmap);
	}
	
	cx;
	cy;
	crBack;
	
	return TRUE;
}

void CNewVisualProxy2::DoInitDefaultProp(CArray<FOP_CUST_PROP,FOP_CUST_PROP> &mpProp)
{
	// Do not call mpProp.RemoveAll();
	// Port width
	FOP_CUST_PROP m_Rrop1;
	m_Rrop1.nPropId = P_ID_DBNAME_CHANGED;
	m_Rrop1.valDefault.m_nValueType = V_BOOL;
	m_Rrop1.valDefault.m_bValue = FALSE;
	mpProp.Add(m_Rrop1);

	FOP_CUST_PROP m_Rrop;
	m_Rrop.nPropId = P_ID_CONNECT_FIELD;
	m_Rrop.valDefault.m_nValueType = V_STRING;
	m_Rrop.valDefault.m_strValue = _T("");
	mpProp.Add(m_Rrop);

	FOP_CUST_PROP m_Rrop2;
	m_Rrop2.nPropId = P_ID_DBNAME_CORRECTED;
	m_Rrop2.valDefault.m_nValueType = V_BOOL;
	m_Rrop2.valDefault.m_bValue = FALSE;
	mpProp.Add(m_Rrop2);
}

void CNewVisualProxy2::GenerateDefaultPorts(CArray<FOP_PortScale,FOP_PortScale>* mpSpot,const int &nShapeType)
{
	nShapeType;
	mpSpot->RemoveAll();
	{
		mpSpot->SetSize(0);
	}
	
}
