// FODecimalEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FODecimalEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFODecimalEdit

CFODecimalEdit::CFODecimalEdit()
 : m_dInit(0.0) , m_strUnit(_T("")) , m_dStep(1.1)
 , m_dMin(0.0) , m_dMax(10000.0)

{
}

CFODecimalEdit::~CFODecimalEdit()
{
}

BEGIN_MESSAGE_MAP(CFODecimalEdit, CEdit)
	//{{AFX_MSG_MAP(CFODecimalEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFODecimalEdit message handlers
void CFODecimalEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call 
	int oldpos=LOWORD(GetSel());
	CString str;
	GetWindowText(str);

	if ((nChar>='0' && nChar<='9') || (VK_BACK == nChar))
	{	
		if (0 == oldpos && '0' == nChar) return;

		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if ( nChar == VK_DELETE )
	{
		int nIndex = str.Find('.');
		if (nIndex == -1)
		{// We Can't Find.
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			CString str;
			GetWindowText(str);

			if (0 == str.Find('.'))
			{
				SetWindowText(_T("0") + str);
				SetSel(2, 2);
			}
		}
		else if (0 == nIndex)
		{
			SetWindowText(_T("0") + str);
		}
	}
}

void CFODecimalEdit::OnKillFocus(CWnd* pNewWnd) 
{
	// TODO: Add your message handler code here
	CString str;
	GetWindowText(str);

	if (-1 == str.Find(m_strUnit))
	{// Can't Find Unit or Unit is Destory.		
#ifdef _UNICODE
		char astring[20];
		WideCharToMultiByte (CP_ACP, 0, str, -1, astring, 20, NULL, NULL);
		double dNum = (double)atof(astring);
#else
		double dNum = (double)atof(str);
#endif
		dNum = (dNum<m_dMin)? m_dMin:dNum;
		dNum = (dNum>m_dMax)? m_dMax:dNum;
		str.Format(_T("%f"), dNum);
		str.TrimRight(_T("0"));
		str.TrimRight(_T("."));
		SetWindowText(str+m_strUnit); 
	}
	
	CEdit::OnKillFocus(pNewWnd);
}
