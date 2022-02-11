// ExtTabModel.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ExtTabModel.h"
#include "MyImageShape.h"
#include "FOEFHyperLinkShape.h"
#include "NewButtonShape.h"
#include "FOPNewAutoFontSizeShape.h"
#include "FOPBarcodeShape.h"
#include "FOPBoxShape.h"
#include "NewVisualProxy.h"
#include "SVImageControl.h"
#include "DbPrintGridShape.h"
#include "ExtTabModelManager.h"
#include "DBChartShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtTabModel construction/destruction

IMPLEMENT_SERIAL(CExtTabModel, CFOTabPageModel, 0)

CExtTabModel::CExtTabModel()
{
	//FOTO:Add you code here.
	EnableSnapDynGrid(FALSE);
	EnableSnapAidLine(FALSE);
	EnableSnapToIntersectPoint(FALSE);
//	EnableSnapToPageBoder(FALSE);
	EnableSnapToControlHandle(FALSE);
	SetAllowHoleLink(FALSE);
	SetUIUnit(FUNIT_INCHES);
	DoInitData();
}

CExtTabModel::CExtTabModel(const CExtTabModel& source)
{
	*this			= source;
}

CExtTabModel::~CExtTabModel()
{
	//FOTO:Add you code here.

}

CFODataModel* CExtTabModel::Copy() const
{
	return (new CExtTabModel(*this));
}

void ChangeShape(CFODrawShape* pShapeItem)
{
	if(pShapeItem->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)))
	{
		CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pShapeItem);
		POSITION pos = pComp->GetCompList()->GetHeadPosition();
		while(pos != NULL)
		{
			CFODrawShape *pShape = (CFODrawShape *)pComp->GetCompList()->GetNext(pos);
			if(pShape->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)))
			{	
				ChangeShape(pShape);
			}
			else
			{
				pShape->PutPropBoolValue(P_ID_DBNAME_CORRECTED, FALSE);
			}
		}
	}
	else
	{
		pShapeItem->PutPropBoolValue(P_ID_DBNAME_CORRECTED, FALSE);
	}
}

void CExtTabModel::SearchForEFormShape(CFOCompositeShape *pComp, CFODrawShapeList &listShapes)
{
	if(pComp->GetCompCount() <= 0)
	{
		return;
	}
	
	POSITION postail = pComp->GetCompList()->GetHeadPosition();
	while(postail != NULL)
	{
		CFODrawShape *pShape = (CFODrawShape *)pComp->GetCompList()->GetNext(postail);
		if(HAS_BASE(pShape, CFOCompositeShape))
		{
			CFOCompositeShape *pTemp = static_cast<CFOCompositeShape *>(pShape);
			SearchForEFormShape(pTemp, listShapes);
		}
		else if(pShape->IsNeedForDB())
		{
			listShapes.AddTail(pShape);
		}

	}
	
}

void CExtTabModel::SearchForEFormShapeEX(CFODrawShapeList &listShapes)
{
	CFODrawShapeList pTabOrderList;
	GetTabOrderShapes(&pTabOrderList);
	
	int nSize = pTabOrderList.GetCount();
	for (int i=0; i<nSize; i++)
	{
		CFODrawShape* pShape = FindShapeWithTabOrder(pTabOrderList, i + 1);
		if(pShape != NULL)
		{
			if(HAS_BASE(pShape, CFOCompositeShape))
			{
				CFOCompositeShape *pTemp = static_cast<CFOCompositeShape *>(pShape);
				SearchForEFormShape(pTemp, listShapes);
			}
			else if(pShape->IsNeedForDB())
			{
				listShapes.AddTail(pShape);
			}
		
			if(HAS_BASE(pShape, CFOPTableShape))
			{
				CFOPTableShape *pTable = (CFOPTableShape *)(pShape);
				int nRows = pTable->GetRows();
				int nCols = pTable->GetColumns();
				
				for (int row = 0; row < nRows; row ++)
				{
					for (int col = 0; col < nCols; col ++)
					{
						CFOPTableCell* cellx = pTable->cell(row,col);
						cellx->SetChoiceText(cellx->GetObjectCaption());
						cellx->m_strSave = cellx->GetObjectCaption();
					}
				}
			}
			else if(HAS_BASE(pShape, FOXNewTableShape))
			{
				FOXNewTableShape *pTable = (FOXNewTableShape *)(pShape);
				int nRows = pTable->GetRows();
				int nCols = pTable->GetColumns();
				
				for (int row = 0; row < nRows; row ++)
				{
					for (int col = 0; col < nCols; col ++)
					{
						CFOPNewTableCell* cellx = pTable->cell(row,col);
						cellx->SetChoiceText(cellx->GetObjectCaption());
						cellx->m_strSave = cellx->GetObjectCaption();
					}
				}
			}
		}
		
		
	}
}

BOOL CExtTabModel::AddShape(CFODrawShape* pShapeItem)
{
	BOOL bReturn = CFODataModel::AddShape(pShapeItem);
//	ChangeShape(pShapeItem);
	return bReturn;
}

BOOL CExtTabModel::AddShapes(const CFODrawShapeList& lstShapes)
{
	BOOL bReturn = CFODataModel::AddShapes(lstShapes);
// 	POSITION pos = lstShapes.GetHeadPosition();
// 	while(pos != NULL)
// 	{
// 		CFODrawShape *pShape = (CFODrawShape *)lstShapes.GetNext(pos);
// 		if(pShape->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)))
// 		{	
// 			ChangeShape(pShape);
// 		}
// 		else
// 		{
// 			pShape->PutPropBoolValue(P_ID_DBNAME_CORRECTED, FALSE);
// 		}
// 	}
	return bReturn;
}

void CExtTabModel::DoInitData()
{
	CFOTabPageModel::DoInitData();

	//FOTO:Add you code here.

//	ChangePositionWithPages(1,1);
//	SetLockWithPages(TRUE);
	SetPointLimitWithPage(TRUE);

}

void CExtTabModel::DoInitCreateShape(CFODrawShape *pShape)
{
	CFODataModel::DoInitCreateShape(pShape);
	
	if(pShape != NULL)
	{
		if(!HAS_BASE(pShape, CFOButtonShape) && 
			!HAS_BASE(pShape, CFOHyLinkShape) &&
			!HAS_BASE(pShape, CFORoundButtonShape)
			)
		{
			pShape->SetFlat(TRUE);
			pShape->SetTabOrderProtect(FALSE);
		}

//		if(HAS_BASE(pShape, CFOSliderMeterEllipticalShape))
		{
			pShape->SetNeedForDB(TRUE);
		}

// 		if(pShape->IsNeedForDB() && !HAS_BASE(pShape, CDbPrintGridShape) && 
// 			!HAS_BASE(pShape, CFOPBarcodeShape))
// 		{
// 			CFOPShapeDefaultStyle m_CurStyle = *gfxDefStyleData.GetCurDefStyle();
// 			pShape->SetLineColor(m_CurStyle.GetLineColor());
// 			pShape->SetLineWidth(m_CurStyle.GetLineWidth());
// 			pShape->SetBkColor(m_CurStyle.GetBkColor());
// 			pShape->SetFontColor(m_CurStyle.GetFontColor());
// 			pShape->SetPatternColor(m_CurStyle.GetPatternColor());
// 			pShape->SetShadowColor(m_CurStyle.GetShadowColor());
// 			pShape->SetShadow(m_CurStyle.GetShadow());
// 			pShape->SetBrushType(m_CurStyle.GetBrushType());
// 			pShape->SetFaceName(m_CurStyle.GetFaceName());
// 			pShape->SetPointSize(m_CurStyle.GetPointSize());
// 			pShape->SetMultiLine(FALSE);
// 			pShape->AdjustTextBoxSize(NULL);
// 		}
	}
}

void CExtTabModel::NotifyObserver(LPARAM lHint, CObject*pHint)
{
	CFOTabPageModel::NotifyObserver(lHint,pHint);

	//FOTO:Add you code here.

}

void CExtTabModel::UpdateTitle()
{
	CFOTabPageModel::UpdateTitle();

//	if(m_pOwner == NULL)
//	{
//		return;
//	}
//
//	if(m_pOwner->GetSafeHwnd() != NULL)
//	{
//		if(m_pOwner ->IsKindOf(RUNTIME_CLASS(CFODrawView)))
//		{
//			CFODrawView *pView = (CFODrawView *) m_pOwner;
//			CDocument *m_pDocument = (CDocument *)pView->GetDocument();
//			if(m_pDocument != NULL)
//			{
//				if (m_strTitleOrg.IsEmpty() && !m_pDocument->GetTitle().IsEmpty())
//					m_strTitleOrg = m_pDocument->GetTitle();
//				
//				if (!m_strTitleOrg.IsEmpty())
//				{
//					TCHAR szStr[256+_MAX_PATH];
//					_tcscpy(szStr, m_strTitleOrg);
//					if (IsDirty())
//					{
//						if(m_strTitleOrg.Find(_T("*"))<0)
//						{
//							lstrcat(szStr, _T(" *"));
//						}
//					}
//					if (m_pDocument->GetTitle() != szStr)
//					{
//						m_pDocument->SetTitle(szStr);
//						m_pDocument->UpdateFrameCounts();
//					}
//				}
//			}
//		}
//	}
}

void CExtTabModel::DoActionChange(const CFOBaseAction* pAction)
{
	CFOTabPageModel::DoActionChange(pAction);
	
	// FODO:Add your own specify code here.

}

CString CExtTabModel::CreateBaseName(UINT nType)
{
	switch(nType)
	{
	case MY_IMAGE_TYPE:
		{
			return _T("ImageBox");
		}
		break;

	case FOP_COMP_BARCODE:
		{
			return _T("Barcode");
		}
		break;

	default:
		{
			return CFOTabPageModel::CreateBaseName(nType);
		}
		break;
	}

}

CString CExtTabModel::CreateBaseCaption(UINT nType)
{
	switch(nType)
	{
	case MY_IMAGE_TYPE:
		{
			return _T("Image Box");
		}
		break;

	default:
		{
			return CFOTabPageModel::CreateBaseCaption(nType);
		}
		break;
	}

}

CString CExtTabModel::GetUniqueName(UINT nType)
{
	return CFOTabPageModel::GetUniqueName(nType);
}

CString CExtTabModel::GetUniqueCaption(UINT nType)
{

	return CFOTabPageModel::GetUniqueCaption(nType);
}

BOOL CExtTabModel::IsShapeEffect(CFODrawShape* pShape)
{
	if(HAS_BASE(pShape,CFOEFHyperLinkShape)
		
		)
	{
		return FALSE;
	}
	
	return CFODataModel::IsShapeEffect(pShape);
}

CFODrawShape *CExtTabModel::DoCreateShapeByType(UINT m_drawshape,
														CRect &rcCreate,
														CString strFileName,
														CFOToolBoxItem *pCurItem)
{
	pCurItem;
	CFODrawShape *pReturn = NULL;
	CString strCaption;
	CString strName;
	strCaption = "";
	strName = "";
	CPoint ptTrack = rcCreate.TopLeft();
	if(m_drawshape != FO_COMP_NONE)
	{
		CRect rc(rcCreate);
		rc.NormalizeRect();
		if(rc.IsRectEmpty()||(rc.Width()<=10 && rc.Height()<20))
		{
			switch(m_drawshape)
			{
			case SV_COMP_IMAGE_CONTROL:	//	CSVImageControl
				{
					rc = CRect(ptTrack.x-96,ptTrack.y-96,ptTrack.x+96,ptTrack.y+96);
				}
				break;

			case NEW_SHAPE_BUTTON:
				{
					rc = CRect(ptTrack.x-50,ptTrack.y-15,ptTrack.x+50,ptTrack.y+15);
					
				}
				break;

			case MY_EXT_HYPERLINK:
				{
					rc = CRect(ptTrack.x-85,ptTrack.y-12,ptTrack.x+85,ptTrack.y+12);
						
				}
				break;

			case MY_IMAGE_TYPE:
				{
					rc = CRect(ptTrack.x-85,ptTrack.y-90,ptTrack.x+85,ptTrack.y+90);
				}
				break;
			case MY_AUTO_SIZE_TYPE:
				{
					rc = CRect(ptTrack.x-85,ptTrack.y-15,ptTrack.x+85,ptTrack.y+15);
				}
				break;
			case FOP_COMP_BARCODE:
				{
					rc = CRect(ptTrack.x-95,ptTrack.y-60,ptTrack.x+95,ptTrack.y+60);
				}
				break;

			case MY_BOX_TYPE:
				{
					rc = CRect(ptTrack.x-100,ptTrack.y-100,ptTrack.x+100,ptTrack.y+100);
				}
				break;

			case DB_PRINT_GRID_SHAPE:
				{
					rc = CRect(ptTrack.x-150,ptTrack.y-100,ptTrack.x+150,ptTrack.y+100);
				}
				break;

			default:
				{
				}
				break;
			}
		}

		switch(m_drawshape)
		{
		case DB_PRINT_GRID_SHAPE:
			{
				pReturn = new CDbPrintGridShape;
				pReturn->AddRef();
				pReturn->Create(rc,_T(""));
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		case SV_COMP_IMAGE_CONTROL:
			{
				pReturn = new CSVImageControl;
				pReturn->AddRef();
				pReturn->Create(rc,_T(""));
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		case NEW_SHAPE_BUTTON:
			{
				pReturn = new CNewButtonShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = _T("Button");
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		case MY_EXT_HYPERLINK:
			{
				pReturn = new CFOEFHyperLinkShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = _T("http://www.ucancode.net");
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		case FOP_COMP_BARCODE:
			{
				pReturn = new CFOPBarcodeShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		case MY_IMAGE_TYPE:
			{
				pReturn = new CMyImageShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		case MY_AUTO_SIZE_TYPE:
			{
				pReturn = new CFOPNewAutoFontSizeShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;	

		case MY_BOX_TYPE:
			{
				pReturn = new CFOPBoxShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;		

		default:
			{
				pReturn = CFOTabPageModel::DoCreateShapeByType(m_drawshape,rcCreate,strFileName);
			}
			break;
		}
	}
	return pReturn;
}


void  CExtTabModel::OffsetCanvas2(const CPoint &ptOffset)
{
	CFODrawShape *pShape = NULL;
	int xy = 0;
	for(xy = 0; xy < m_ShapeList.Count(); xy ++)
	{
		pShape = (CFODrawShape *)m_ShapeList.GetObject(xy);
		
		pShape->OffsetAllPoints(ptOffset);
	}
	
	m_pDrawBackComp->OffsetCanvas(ptOffset);
	
//	m_rectPosition.OffsetRect(ptOffset);
}

CFOCompositeShape *CExtTabModel::DoCreateCompositeShapeByType(UINT m_drawshape,
																  CRect &rcCreate,
																  CArray<FOPORTVALUE,FOPORTVALUE> *arInitPorts,
																  CString strFileName,
																  UINT nResID,
																  CFOToolBoxItem *pCurItem)
{
	CFOCompositeShape *pReturn = CFOTabPageModel::DoCreateCompositeShapeByType(m_drawshape,
															rcCreate,
															arInitPorts,
															strFileName,
															nResID,
															pCurItem);
	// FODO: Add your own specify code here.

	return pReturn;
}


void CExtTabModel::SetModifiedFlag(BOOL b)
{
	CFOTabPageModel::SetModifiedFlag(b);
	
	//FOTO:Add you code here.

}

BOOL CExtTabModel::IsModified()
{

	//FOTO:Add you code here.

	return CFOTabPageModel::IsModified();
}

void CExtTabModel::Serialize(CArchive& ar)
{
	CFOTabPageModel::Serialize(ar);
	if(ar.IsStoring())
	{
		//FOTO:Add you code here.

	}
	else
	{
		//FOTO:Add you code here.

	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CExtTabModel::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CExtTabModel::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CExtTabModel::OpenDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	strCurOpenFormFile = CString(lpszPathName);
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

BOOL CExtTabModel::SaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	strCurOpenFormFile = CString(lpszPathName);
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

void CExtTabModel::OnDrawShape(CDC *pDC,const CRect &rcView)
{
	CFOTabPageModel::OnDrawShape(pDC,rcView);
	//FOTO:Add you code here.

}

void CExtTabModel::OnDrawBack(CDC *pDC,const CRect &rcClip)
{
	CFOTabPageModel::OnDrawBack(pDC,rcClip);
	//FOTO:Add you code here.

}


/////////////////////////////////////////////////////////////////////////////
// CExtTabModel diagnostics

#ifdef _DEBUG
void CExtTabModel::AssertValid() const
{
	CFOTabPageModel::AssertValid();
}

void CExtTabModel::Dump(CDumpContext& dc) const
{
	CFOTabPageModel::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////
//The followings are customizable.Change/add to suit your needs
TCHAR szPrecedeChars[]= _T(" ,.;:!?\r\n"); //This string defines what TCHARacters constitute a valid preceding TCHARacter(the one preceding a word)
TCHAR szFollowingChars[]=_T(" ,.;:!?\r\n"); //This string defines what can constitutes a valid set of TCHARacters which can follow a word. This is the string defining a 'lax'(NOT Strict) grammer document
TCHAR szStrictPrecedeChars[]=_T(" \r\n");
TCHAR szValidPunctuation[]=_T(",.:;!?\"\r\n"); //Did I miss anything
//////////////////////////////////////////////////////////////////////

CFOPRelaceText::CFOPRelaceText()
{
	//Initialize things to default values
	m_bStrict=FALSE;
	m_bCheckOnlyWords=FALSE;
	m_bLastWordMayNotHavePunct=FALSE; 
	m_sSearchString=_T("AppWizard"); //Just a default parameter
	m_sReplacementString=_T("");
	m_sTempSearchString=_T("");//To be filled up incrase of case insensetive searches
	m_bStrainFound=FALSE;
	m_bSearchIsFinished=TRUE;
	m_bCaseSensetive=TRUE;
	m_bOverWriteFile=FALSE;
	m_bReplaceLFWithCRLF=FALSE;
}

CFOPRelaceText::CFOPRelaceText(FOP_REPLACE_SET boolSet)
{
	//Initialize options with 'boolSet' values
	m_bStrict=boolSet.bStrict;
	if(m_bStrict)
		m_bCheckOnlyWords=TRUE;//If bStrict is TRUE, bCheckOnlyWords is automatically to be TRUE(guess why )
	else 
		m_bCheckOnlyWords=boolSet.bCheckOnlyWords;

	m_bLastWordMayNotHavePunct=boolSet.bLastWordMayNotHavePunct; 
	m_sSearchString=_T("AppWizard"); //Just a default parameter
	m_sReplacementString=_T("");
	m_sTempSearchString=_T("");//To be filled up incase of case insensetive searches
	m_bStrainFound=FALSE;
	m_bSearchIsFinished=TRUE;
	m_bCaseSensetive=boolSet.bCaseSensetive;
	m_bOverWriteFile=boolSet.bOverWriteFile;
	m_bReplaceLFWithCRLF=boolSet.bReplaceLFWithCRLF;
	m_bReplaceCRLFWithLF=boolSet.bReplaceCRLFWithLF;
}

CFOPRelaceText::~CFOPRelaceText()
{

}

BOOL CFOPRelaceText::IsCharBelongingToSet(TCHAR cCharToTest, TCHAR *szSetValues)
{
	/*
	Function to test of cCharToTest exists in szSetValues.
	This INCLUDES the terminating NULL string, since a word can ALSO be followed/preceded by a NULL
	*/
	for(int i=0; i<= lstrlen((LPCTSTR)(szSetValues)); i++) //We want to compare the NULL too.
	{
		if(szSetValues[i]==cCharToTest) 
			return TRUE;
	}

	return FALSE;
}

BOOL CFOPRelaceText::SetSearchString(const TCHAR *szSearchString)
{
	//Sets the m_sSearchString value
	if(lstrcmp(szSearchString,_T(""))==0) 
		AfxMessageBox(("Search string was empty!\nWill be using default search string \""+m_sSearchString+"\".")); //perhaps a 'throw' would have been better ?
	else 
		m_sSearchString=szSearchString;

	m_sSearchString = _T("[") + m_sSearchString + _T("]");
	return TRUE;
}

BOOL CFOPRelaceText::SetReplacementString(const TCHAR *szReplacementString)
{
	//Sets the m_sReplacementString value
	m_sReplacementString=szReplacementString;
	return TRUE;
}

CString CFOPRelaceText::Process(const CString &strInput)
{
	//Does the processing, and returns the number of matches found
	CString m_sReadFromFile,sWriteToFile,m_sTempSearchString,m_sTempReadFromFile;
	m_sReadFromFile = strInput;
	// m_sReadFromFile -- 
	// sWriteToFile -- 
	CString strReturn = _T("");
	if(m_bReplaceLFWithCRLF) 
		m_sReadFromFile.Replace(_T("\n"),_T("\r\n")); //Replaces ALL LF from current file to CR\LF. This will also make the file properly laid out and readble in simple text editors like Notepad.

	if(m_bReplaceCRLFWithLF)
		m_sSearchString.Replace(_T("\r\n"),_T("\n")); //Replaces ALL CR\LF to LF. This lets the user search files which represents a new line with a single 0x0A rather than the correct 0x0A & 0X0D pair, without changing the filesize of the processed file due to lone LFs being changed to CR/LF as done in above option.

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Well, sReadFromFile now contains the WHOLE file contents !
	This eats up RAM , but drastically improves program performance.
	Any suggestions ?(If you are thinking of CreateFileMapping,MapViewOfFile.. etc, please send it in code ;) - They are a real pain-in-the-you-know-what !
	*/

	/*
	Currently, when we are making case insensetive searches, we are copying the WHOLE file which was in m_sReadFromFile to m_sTempReadFromFile, but converting 
	it fully to uppercase. The same for sSearchString.

	This actually means that during case insensetive searches, we are effectively using DOUBLE the memory than the same, but case sensetive search
	*/
	DWORD dwMatches=0, dwCleanStrainPos=0, dwReadFileLen=m_sReadFromFile.GetLength(),dwStrainLen=m_sSearchString.GetLength();
	
	if(!m_bCaseSensetive) 
	{
		//We convert both 'Temp' strings to uppercase if it's a case insensetive search
		m_sTempSearchString=m_sSearchString;
		m_sTempReadFromFile=m_sReadFromFile;
		m_sTempSearchString.MakeUpper();
		m_sTempReadFromFile.MakeUpper();
		dwCleanStrainPos= m_sTempReadFromFile.Find(m_sTempSearchString);		
	}
	else
	{
		dwCleanStrainPos=m_sReadFromFile.Find(m_sSearchString);
	}

	if(dwCleanStrainPos!=-1)
	{
		m_bStrainFound=TRUE;
		m_bSearchIsFinished=!m_bStrainFound;
	}
	else 
	{
		m_bStrainFound=FALSE;
	}

	/*
	A word is identified as: [details moved to article]
	*/
	while(m_bStrainFound&&(!m_bSearchIsFinished))
	{
		//Search string found.Now check if user asked us to change substrings or only words
		dwReadFileLen=m_sReadFromFile.GetLength();
		dwMatches++;
		///////////////////////////////////////////
		sWriteToFile=m_sReadFromFile.Left(dwCleanStrainPos);
		if(m_bCheckOnlyWords)
		{
			DWORD dwFollowPos=(sWriteToFile.GetLength()+m_sSearchString.GetLength());

			TCHAR cFollow=NULL;
			if(dwFollowPos < (DWORD)m_sReadFromFile.GetLength())
				cFollow=m_sReadFromFile.GetAt(dwFollowPos); //if the check within if() was NOT there, we could end up doing a out of bounds operation !

			TCHAR cPrecededBy=m_sReadFromFile.GetAt(dwCleanStrainPos-1);
			if(!m_bStrict)
			{
				//If we are NOT to be strict with grammer
				if(IsCharBelongingToSet(cPrecededBy,szPrecedeChars))
				{
					if(!IsCharBelongingToSet(cFollow,szFollowingChars)) 
						sWriteToFile+=m_sReadFromFile.Mid(dwCleanStrainPos,m_sSearchString.GetLength());
					else 
						sWriteToFile+=m_sReplacementString;// Match found, let's put in the replacement string
					//We will leave out m_sSearchString ONLY if cFollow was NOT among szFollowingChars,thus NOT qualifying it as  a word
					//Hey, we where ONLY asked to replace WORDS, not substrings, so give him the data back!
				}
				else 
				{
					sWriteToFile+=m_sReadFromFile.Mid(dwCleanStrainPos,m_sSearchString.GetLength());
				}
			}
			else
			{
				//Grammer layout is strict - those strings NOT in confirmation will be excluded/ignored
				if(IsCharBelongingToSet(cPrecededBy,szStrictPrecedeChars))
				{
					if(IsCharBelongingToSet(cFollow,szFollowingChars))
					{
						//So far, so good, now if cFollow was a punctuation but NOT a NULL(which makes m_sSearchString here the LAST word) OR a blank/space, let's see if a space or a newline or a NULL follows
						if(((dwFollowPos+1)< (DWORD)m_sReadFromFile.GetLength())&&(cFollow!=_T(' '))) 
							cFollow=m_sReadFromFile.GetAt(dwFollowPos+1);//Let's get the next TCHARacter into cFollow if it was not a space (all punctuations EXCEPT the space should be followed by a space)

						if(IsCharBelongingToSet(cFollow,szValidPunctuation)&&(cFollow!= _T(' '))) 
						{
							if((!m_bLastWordMayNotHavePunct)&&(cFollow==NULL)) 
								sWriteToFile+=m_sReadFromFile.Mid(dwCleanStrainPos,m_sSearchString.GetLength());//Match was found,but with the last word lacking a punctuation(probably a period), and the user wanted us to ignore this, so we don't put in the replacement string.
							else 
								sWriteToFile+=m_sReplacementString; //Correctly formatted word found, replace it
						}
						else 
						{
							if(cFollow==' ') 
								sWriteToFile+=m_sReplacementString;//Correctly formatted word found, replace it
							else 
								sWriteToFile+=m_sReadFromFile.Mid(dwCleanStrainPos,m_sSearchString.GetLength());//cFollow was not in szValidPunctuation
						}
					}
					else
					{
						sWriteToFile+=m_sReadFromFile.Mid(dwCleanStrainPos,m_sSearchString.GetLength());//cFollow was not in szFollowingChars
					}
				}
				else 
				{
					sWriteToFile+=m_sReadFromFile.Mid(dwCleanStrainPos,m_sSearchString.GetLength());//cPrecededBy was not in szStrictPrecedeChars
				}
			}
		}
		else
		{
			sWriteToFile+=m_sReplacementString; //We are checking not only words but substrings too, so we replace every match
		}

		dwCleanStrainPos=dwReadFileLen-(dwCleanStrainPos+dwStrainLen);
		m_sReadFromFile=m_sReadFromFile.Right(dwCleanStrainPos);//Dynamically reducing the memory usage.Writing 'Clean' stream to disk and removing from RAM the portion written to disc.
		if(!m_bCaseSensetive) 
		{
			m_sTempReadFromFile=m_sTempReadFromFile.Right(dwCleanStrainPos);//Dynamically reducing the memory usage.Writing 'Clean' stream to disk and removing from RAM the portion written to disc.
		}

		if(m_bStrainFound) 
		{
			// sWriteToFile --
			strReturn += sWriteToFile;
			
		}
		//Check for more occurences
		if(((!m_bCaseSensetive)&&((dwCleanStrainPos=m_sTempReadFromFile.Find(m_sTempSearchString))==-1))||((m_bCaseSensetive)&&((dwCleanStrainPos=m_sReadFromFile.Find(m_sSearchString))==-1))) 
			m_bSearchIsFinished=TRUE; //No more occurences found [Glad someone was patient enough to go till here from the if.. :) ]
	}
	//End of while(m_bStrainFound)

	/////////Write out rest of file which did not contain m_sSearchString at all
	if(m_bStrainFound)
	{
		dwCleanStrainPos=dwReadFileLen-(dwCleanStrainPos+dwStrainLen);
	}
	else 
	{
		dwCleanStrainPos=0;
	}
	
	if(!m_sReadFromFile.IsEmpty())
	{
		sWriteToFile=m_sReadFromFile.Right(dwCleanStrainPos);
		if(m_bStrainFound) 
		{
			strReturn += sWriteToFile;
		}
	}
	
	if(strReturn.IsEmpty())
	{
		return m_sReadFromFile;
	}
	return strReturn;
}

CDBChartShape *CExtTabModel::AddNewChart(CFOPChartData* pMemData, const FOPRect & rcPos,  const FOP_CHART_STYLE &nChartStyle)
{
	if(pMemData == NULL)
	{
		return NULL;
	}
	
	if(rcPos.IsEmpty())
	{
		return NULL;
	}
	
	CDBChartShape *pReturn = new CDBChartShape;
	pReturn->AddRef();
    pReturn->Create(*pMemData,nChartStyle,rcPos,TRUE);
	if(pReturn != NULL)
	{
		AddShape(pReturn);
		pReturn->Release();
	}
	SetModifiedFlag(TRUE);
	
	return pReturn;
	
}

CString CExtTabModel::GetExpressValue(const CString &strExpress)
{
	CExtTabModelManager *pMgr = (CExtTabModelManager *)m_pDataManager;
	ASSERT(pMgr);
	
	return pMgr->GetExpressValue(strExpress);
}
