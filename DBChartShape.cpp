// DBChartShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DBChartShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CDBChartShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBChartShape, CFOPChartShape, 0)
CDBChartShape::CDBChartShape()
{
	SetType(DB_CHART_SHAPE);
	m_strSQL = _T("");
	SetWithLabelEditing(FALSE);
	SetBrushType(1);
	strBackup = _T("");
	m_crColColor = RGB(238,242,247);
	m_bHorzGrid = TRUE;
	m_bVertGrid = TRUE;
	m_nStartRecord = 0;
	m_nMaxRecords = 4;
}

CDBChartShape::CDBChartShape(const CDBChartShape& src)
{
	*this = src;
}

CDBChartShape::~CDBChartShape()
{

}

/////////////////////////////////////////////////////////////////////////////
// CDBChartShape diagnostics

#ifdef _DEBUG
void CDBChartShape::AssertValid() const
{
	CFOPChartShape::AssertValid();
}

void CDBChartShape::Dump(CDumpContext& dc) const
{
	CFOPChartShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CDBChartShape::Serialize(CArchive& ar)
{
	CFOPChartShape::Serialize(ar);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.
		ar << m_nStartRecord;
		ar << m_nMaxRecords;
		
		ar << m_crColColor;
		ar << m_strSQL;
		ar << m_bHorzGrid;
		ar << m_bVertGrid;
		int nSize = m_ColNames.GetSize();
		ar << nSize;
		for(int x = 0; x < nSize; x++)
		{
			FODB_COLS db = m_ColNames.GetAt(x);
			ar << db.strTitle;
			ar << db.strDBFiled;
		}
		
	}
	else
	{
		//FODO:Add your own code here.
		ar >> m_nStartRecord;
		ar >> m_nMaxRecords;
		
		
		ar >> m_crColColor;
		ar >> m_strSQL;
		
		ar >> m_bHorzGrid;
		ar >> m_bVertGrid;
		
		m_ColNames.RemoveAll();
		int nSize;
		ar >> nSize;
		for(int x = 0; x < nSize; x++)
		{
			FODB_COLS db;
			ar >> db.strTitle;
			ar >> db.strDBFiled;
			m_ColNames.Add(db);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CDBChartShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
								 CFileException* pError)
{
	CMirrorFile* pFile = new CMirrorFile;
	ASSERT(pFile != NULL);
	if (!pFile->Open(lpszFileName, nOpenFlags, pError))
	{
		delete pFile;
		pFile = NULL;
	}
	return pFile;
}

void CDBChartShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CDBChartShape::OpenDocument(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
			Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
		return TRUE;
}

BOOL CDBChartShape::SaveDocument(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	
	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
		return TRUE;        // success
}

CDBChartShape& CDBChartShape::operator=(const CDBChartShape& src)
{
	(*(CFOPChartShape*)this) = src;
	m_nStartRecord = src.m_nStartRecord;
	m_nMaxRecords = src.m_nMaxRecords;
	
	m_strSQL = src.m_strSQL;
	m_crColColor = src.m_crColColor;
	m_bHorzGrid = src.m_bHorzGrid;
	m_bVertGrid = src.m_bVertGrid;
	m_ColNames.RemoveAll();
	int nSize = src.m_ColNames.GetSize();
	for(int x = 0; x < nSize; x++)
	{
		FODB_COLS db = src.m_ColNames.GetAt(x);
		m_ColNames.Add(db);
	}
	return (*this);
}

CFODrawShape* CDBChartShape::Copy() const
{
	return (new CDBChartShape(*this));
}

void CDBChartShape::DoFillData()
{
}

void CDBChartShape::PrepareDC(CDC* pDC)
{
	CFOPChartShape::PrepareDC(pDC);

	//FODO:Add your own code below.
	
}

void CDBChartShape::OnDrawTrackCustom(CDC *pDC)
{
	CFOPChartShape::OnDrawTrackCustom(pDC);

	// Add your own code here.

}

void CDBChartShape::OnDrawShadow(CDC *pDC)
{
	CFOPChartShape::OnDrawShadow(pDC);
	
	//FODO:Add your own code below.
	
}

void CDBChartShape::OnDrawFlat(CDC *pDC)
{
	CFOPChartShape::OnDrawFlat(pDC);

	//FODO:Add your own code below.
	
}

void CDBChartShape::OnDraw3d(CDC *pDC)
{
	CFOPChartShape::OnDraw3d(pDC);

	//FODO:Add your own code below.

}

void CDBChartShape::ClearDC(CDC* pDC)
{
	CFOPChartShape::ClearDC(pDC);

	//FODO:Add your own code below.

}

void CDBChartShape::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFOPChartShape::OnLButtonDown(nFlags,point);
	
	//FODO:Add your own code below.

}

void CDBChartShape::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CFOPChartShape::OnLButtonUp(nFlags,point);

	//FODO:Add your own code below.

}

void CDBChartShape::GeometryUpdated(CFOArea* pRgn)
{
	CFOPChartShape::GeometryUpdated(pRgn);

	//FODO:Add your own code below.

}
