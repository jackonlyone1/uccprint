// FOPBoxShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FOPBoxShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CFOPBoxShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CFOPBoxShape, CFOTrapezoidShape, 0)
CFOPBoxShape::CFOPBoxShape()
{
	SetType(MY_BOX_TYPE);
}

CFOPBoxShape::CFOPBoxShape(const CFOPBoxShape& src)
{
	*this = src;
}

CFOPBoxShape::~CFOPBoxShape()
{

}

/////////////////////////////////////////////////////////////////////////////
// CFOPBoxShape diagnostics

#ifdef _DEBUG
void CFOPBoxShape::AssertValid() const
{
	CFOTrapezoidShape::AssertValid();
}

void CFOPBoxShape::Dump(CDumpContext& dc) const
{
	CFOTrapezoidShape::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

void CFOPBoxShape::Create(CRect &rcPos,CString strCaption)
{
	AllocMemory(5);
	CPoint ptCenter = rcPos.CenterPoint();
	m_lpShapePoints[0]=CPoint(rcPos.left,rcPos.top);
	m_lpShapePoints[1]=CPoint(rcPos.right,rcPos.top);
	m_lpShapePoints[2]=CPoint(rcPos.right,rcPos.bottom);
	m_lpShapePoints[3]=CPoint(rcPos.left,rcPos.bottom);
	m_lpShapePoints[4]=CPoint(rcPos.left,rcPos.top);
	
	SetObjectCaption(strCaption);
	
	m_ptSaveAnchor = m_ptAnchor = CPoint((rcPos.left+(rcPos.right-rcPos.left)/4),rcPos.bottom);
	
	CFODrawPortsShape::Create(rcPos,strCaption);
	
	BuildAllDefaultPorts();
	UpdateComp();
}

void CFOPBoxShape::Serialize(CArchive& ar)
{
	CFOTrapezoidShape::Serialize(ar);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.

	}
	else
	{
		//FODO:Add your own code here.

	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CFOPBoxShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CFOPBoxShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CFOPBoxShape::OpenDocument(LPCTSTR lpszPathName)
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

BOOL CFOPBoxShape::SaveDocument(LPCTSTR lpszPathName)
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


CFOPBoxShape& CFOPBoxShape::operator=(const CFOPBoxShape& src)
{
	(*(CFOTrapezoidShape*)this) = src;
	return (*this);
}

CFODrawShape* CFOPBoxShape::Copy() const
{
	return (new CFOPBoxShape(*this));
}

void CFOPBoxShape::PrepareDC(CDC* pDC)
{
	CFOTrapezoidShape::PrepareDC(pDC);

	//FODO:Add your own code below.
	
}

void CFOPBoxShape::GetPathSimplePolygon(FOPSimpleCompositePolygon& rPoly) const
{
	CFOTrapezoidShape::GetPathSimplePolygon(rPoly);

}

void CFOPBoxShape::OnDrawTrackCustom(CDC *pDC)
{
	CFOTrapezoidShape::OnDrawTrackCustom(pDC);

	// Add your own code here.
	CFOMatrix* pMat = GetValidateMatrix();
	FOPPoint pt1 = CPoint(m_lpShapeTrackPoints[0]);
	pMat->ChangeValueBack(pt1);

	FOPPoint pt2 = CPoint(m_lpShapeTrackPoints[1]);
	pMat->ChangeValueBack(pt2);

	CPoint pt3 = CPoint(m_lpShapeTrackPoints[2]);
	pMat->ChangeValueBack(pt3);

	CPoint pt4 = CPoint(m_lpShapeTrackPoints[3]);
	pMat->ChangeValueBack(pt4);
	
	CRect rcSave = CFODrawHelper::GetBoundRect(m_lpSavePoints, 4);
	CPoint ptControl = m_ptTrackAnchor;
	pMat->ChangeValueBack(ptControl);
	
	int nWidth = ptControl.x - pt1.x;
	if(nWidth <= 4)
	{
		nWidth = rcSave.Width();
	}	
	
	CPoint ptFirst, ptSecond;
	CPoint ptTemp1, ptTemp2;
	
	ptFirst = ptControl;
	ptSecond = ptControl;
	ptSecond.y = pt1.y;
	
	ptTemp1 = ptFirst;
	ptTemp2 = ptSecond;
	while(ptFirst.x < pt2.x)
	{		
		ptTemp1 = ptFirst;
		ptTemp2 = ptSecond;
		
		pMat->ChangeValue(ptTemp1);
		pMat->ChangeValue(ptTemp2);
		
		pDC->MoveTo(ptTemp1);
		pDC->LineTo(ptTemp2);
		
		ptFirst.x += nWidth;
		ptSecond.x += nWidth;
	}

}

void CFOPBoxShape::DoDrawVisioOrderLine(CDC *pDC)
{
	CFOTrapezoidShape::DoDrawVisioOrderLine(pDC);

	//FODO:Add your own code below.
	
}

void CFOPBoxShape::OnDrawFlat(CDC *pDC)
{
	CFODrawPortsShape::OnDrawFlat(pDC);

	FillPoly(pDC,m_lpShapePoints, m_nCompPtCount,GetBkColor(),GetPatternColor(),GetBrushType());
	
	//FODO:Add your own code below.
	
	FOPPoint pt1 = FOPPoint(m_lpSavePoints[0]);
	FOPPoint pt2 = FOPPoint(m_lpSavePoints[1]);
	FOPPoint pt3 = FOPPoint(m_lpSavePoints[2]);
	FOPPoint pt4 = FOPPoint(m_lpSavePoints[3]);
	
	CRect rcSave = CFODrawHelper::GetBoundRect(m_lpSavePoints, 4);
	FOPPoint ptControl = m_ptSaveAnchor;
	
	int nWidth = ptControl.x - pt1.x;
	if(nWidth <= 4)
	{
		nWidth = rcSave.Width();
	}
	
	CFOMatrix* pMat = GetValidateMatrix();
	
	CPoint ptFirst, ptSecond;
	CPoint ptTemp1, ptTemp2;
	
	ptFirst = ptControl;
	ptSecond = ptControl;
	ptSecond.y = pt1.y;
	
	ptTemp1 = ptFirst;
	ptTemp2 = ptSecond;
	while(ptFirst.x < pt2.x)
	{		
		ptTemp1 = ptFirst;
		ptTemp2 = ptSecond;
		
		pMat->ChangeValue(ptTemp1);
		pMat->ChangeValue(ptTemp2);
		
		pDC->MoveTo(ptTemp1);
		pDC->LineTo(ptTemp2);
		
		ptFirst.x += nWidth;
		ptSecond.x += nWidth;
	}
}

BOOL CFOPBoxShape::OffsetAnchorPoint(CPoint ptOffset)
{
	FOPPoint ptNew;
	CFOMatrix* pMat = GetMatrixData();
	
	if (pMat)
	{
		int nSaveY = m_ptSaveAnchor.y;
		ptNew = FOPPoint(m_ptSaveAnchor);
		pMat->ChangeValue(ptNew);
		ptNew += ptOffset;
		
		FOPPoint pt1 = m_lpSavePoints[0];
		FOPPoint pt2 = m_lpSavePoints[1];

		int nCenter = (int)((pt1.x + pt2.x) / 2);
		
		CPoint ptBack = ptNew;
		pMat->ChangeValueBack(ptBack);
		if(ptBack.x <= pt1.x)
		{
			ptBack.x = pt1.x;
		}
		
		if(ptBack.x >= nCenter)
		{
			ptBack.x = nCenter;
		}

		int nWidth = ptBack.x - pt1.x;
		if(nWidth <= 4)
		{
			nWidth = abs(pt2.x - pt1.x);
		}

		CPoint ptFirst = ptBack;
		int nTotal = 1;
		while(ptFirst.x < pt2.x)
		{		
			ptFirst.x += nWidth;
			nTotal ++;
		}

		double nNewWidth = (double)(pt2.x - pt1.x) / (double)nTotal;
		if(nNewWidth < 0)
		{
			nNewWidth = -nNewWidth;
		}

		m_ptSaveAnchor.x = pt1.x + CFODrawHelper::RoundValue(nNewWidth);
		m_ptSaveAnchor.y = nSaveY;

	}
	else
	{
//		int nOffset = ptOffset.x;

		m_ptSaveAnchor.x = m_ptSaveAnchor.x + ptOffset.x;
	}

	ValidatePoints();
	
	UpdateComp();

	return TRUE;
}

BOOL CFOPBoxShape::TrackOffsetAnchorPoint(CPoint ptOffset)
{
	FOPPoint ptNew;
	m_TrackMat = CFOMatrix(*GetValidateMatrix());
	
	ptNew = FOPPoint(m_ptSaveAnchor);
	m_TrackMat.ChangeValue(ptNew);
	ptNew += ptOffset;

	FOPPoint pt1 = m_lpSavePoints[0];
	FOPPoint pt2 = m_lpSavePoints[1];
	
	int nCenter = (int)((pt1.x + pt2.x) / 2);

	CPoint ptBack = ptNew;
	m_TrackMat.ChangeValueBack(ptBack);
	if(ptBack.x <= pt1.x)
	{
		ptBack.x = pt1.x;
	}
	
	if(ptBack.x >= nCenter)
	{
		ptBack.x = nCenter;
	}

	int nWidth = ptBack.x - pt1.x;
	if(nWidth <= 4)
	{
		nWidth = abs(pt2.x - pt1.x);
	}
	
	CPoint ptFirst = ptBack;
	int nTotal = 1;
	while(ptFirst.x < pt2.x)
	{		
		ptFirst.x += nWidth;
		nTotal ++;
	}
	
	double nNewWidth = (double)(pt2.x - pt1.x) / (double)nTotal;
	if(nNewWidth < 0)
	{
		nNewWidth = -nNewWidth;
	}
	ptBack.x = pt1.x + CFODrawHelper::RoundValue(nNewWidth);
	
	m_TrackMat.ChangeValue(ptBack);
	m_ptTrackAnchor = ptBack;
	
	return TRUE;
}

void CFOPBoxShape::OnDrawShadow(CDC *pDC)
{
	CFOTrapezoidShape::OnDrawShadow(pDC);

	//FODO:Add your own code below.

// Example code:
//	FillShadowPoly(pDC,m_lpShapePoints, m_nCompPtCount);
}

void CFOPBoxShape::OnDraw3d(CDC *pDC)
{
	CFODrawPortsShape::OnDraw3d(pDC);
	FillPoly(pDC,m_lpShapePoints, m_nCompPtCount,GetBkColor(),GetPatternColor(),GetBrushType());
	
	//FODO:Add your own code below.

	FOPPoint pt1 = FOPPoint(m_lpSavePoints[0]);
	FOPPoint pt2 = FOPPoint(m_lpSavePoints[1]);
	FOPPoint pt3 = FOPPoint(m_lpSavePoints[2]);
	FOPPoint pt4 = FOPPoint(m_lpSavePoints[3]);
	
	CRect rcSave = CFODrawHelper::GetBoundRect(m_lpSavePoints, 4);
	FOPPoint ptControl = m_ptSaveAnchor;

	int nWidth = ptControl.x - pt1.x;
	if(nWidth <= 4)
	{
		nWidth = rcSave.Width();
	}

	CFOMatrix* pMat = GetValidateMatrix();

	CPoint ptFirst, ptSecond;
	CPoint ptTemp1, ptTemp2;

	ptFirst = ptControl;
	ptSecond = ptControl;
	ptSecond.y = pt1.y;

	ptTemp1 = ptFirst;
	ptTemp2 = ptSecond;
	while(ptFirst.x < pt2.x)
	{		
		ptTemp1 = ptFirst;
		ptTemp2 = ptSecond;

		pMat->ChangeValue(ptTemp1);
		pMat->ChangeValue(ptTemp2);

		pDC->MoveTo(ptTemp1);
		pDC->LineTo(ptTemp2);

		ptFirst.x += nWidth;
		ptSecond.x += nWidth;
	}
}

void CFOPBoxShape::ClearDC(CDC* pDC)
{
	CFOTrapezoidShape::ClearDC(pDC);

	//FODO:Add your own code below.

}

void CFOPBoxShape::GeometryUpdated(CFOArea* pRgn)
{
	CFOTrapezoidShape::GeometryUpdated(pRgn);
}
