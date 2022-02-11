#if !defined(AFX_FODECIMALEDIT_H__887565D1_E511_44AB_BB78_7E04DD718FB1__INCLUDED_)
#define AFX_FODECIMALEDIT_H__887565D1_E511_44AB_BB78_7E04DD718FB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FODecimalEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFODecimalEdit window
#include <stdlib.h>
#include <stdio.h>

 
//===========================================================================
// Summary:
//     The CFODecimalEdit class derived from CEdit
//      F O Decimal Edit
//===========================================================================

class CFODecimalEdit : public CEdit
{
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O Decimal Edit, Constructs a CFODecimalEdit object.
	//		Returns A  value.
	CFODecimalEdit();

// Attributes
private:
 
	// m_dInit, This member specify double object.  
	double  m_dInit;
 
	// m_strUnit, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strUnit;
 
	// m_dStep, This member specify double object.  
	double  m_dStep;
 
	// m_dMin, This member specify double object.  
	double  m_dMin;
 
	// m_dMax, This member specify double object.  
	double  m_dMax;

public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial, Call Initial after creating a new object.
	// Parameters:
	//		&dNum---&dNum, Specifies a double &dNum object.  
	//		dStep---dStep, Specifies a double dStep = 1.0 object.  
	//		strUnit---strUnit, Specifies A CString type value.
	void Initial(double &dNum, double dStep = 1.0, CString strUnit = _T(""))
	{
		m_dStep = dStep;
		m_strUnit = strUnit;
		dNum = (dNum<m_dMin)? m_dMin:dNum;
		dNum = (dNum>m_dMax)? m_dMax:dNum;

		CString str;
		str.Format(_T("%0.3f"), dNum);
		str.TrimRight(_T("0"));
		str.TrimRight(_T("."));
		SetWindowText(str+m_strUnit); 
	}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Decimal, Sets a specify value to current class CFODecimalEdit
	// Parameters:
	//		&dNum---&dNum, Specifies a double &dNum object.
	void SetDecimal(double &dNum)
	{
		dNum = (dNum<m_dMin)? m_dMin:dNum;
		dNum = (dNum>m_dMax)? m_dMax:dNum;
	
		CString str;
		str.Format(_T("%0.3f"), dNum);
		str.TrimRight(_T("0"));
		str.TrimRight(_T("."));
		SetWindowText(str+m_strUnit); 
	}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Decimal, Returns the specified value.
	//		Returns A double value.
	double GetDecimal()
	{
		CString str;
		GetWindowText(str);
		str = str.Left(str.GetLength() - m_strUnit.GetLength());
		
#ifdef _UNICODE
		char astring[20];
		WideCharToMultiByte (CP_ACP, 0, str, -1, astring, 20, NULL, NULL);
		double dRet = (double)atof(astring);
#else
		double dRet = (double)atof(str);
#endif
		return dRet;
	}
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Deltapos, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMUpDown---N M Up Down, A pointer to the NM_UPDOWN or NULL if the call failed.
	void OnDeltapos(NM_UPDOWN* pNMUpDown)
	{
		CString str;
		GetWindowText(str);
		str = str.Left(str.GetLength() - m_strUnit.GetLength());

#ifdef _UNICODE
		char astring[20];
		WideCharToMultiByte (CP_ACP, 0, str, -1, astring, 20, NULL, NULL);
		double dNum = (double)atof(astring);
#else
		double dNum = (double)atof(str);
#endif
		dNum = dNum - pNMUpDown->iDelta * m_dStep;
		dNum = (dNum<m_dMin)? m_dMin:dNum;
		dNum = (dNum>m_dMax)? m_dMax:dNum;

		str.Format(_T("%0.3f"), dNum);
		str.TrimRight(_T("0"));
		str.TrimRight(_T("."));
		SetWindowText(str+m_strUnit); 
	}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Unit, Sets a specify value to current class CFODecimalEdit
	// Parameters:
	//		&strUnit---&strUnit, Specifies A CString type value.
	void SetUnit(CString &strUnit) { m_strUnit = strUnit; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unit, Returns the specified value.
	//		Returns a CString type value.
	CString GetUnit() { return m_strUnit; }

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Step, Sets a specify value to current class CFODecimalEdit
	// Parameters:
	//		dStep---dStep, Specifies a double dStep object.
	void SetStep(double dStep) { m_dStep = dStep; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Step, Returns the specified value.
	//		Returns A double value.
	double GetStep() {return m_dInit; }

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Range, Sets a specify value to current class CFODecimalEdit
	// Parameters:
	//		&dMin---&dMin, Specifies a double &dMin object.  
	//		&dMax---&dMax, Specifies a double &dMax object.
	void SetRange(double &dMin, double &dMax) { m_dMin = dMin; m_dMax = dMax; }

	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Validate Char, Do a event. 
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	BOOL DoValidateChar(UINT nChar);

// Operations
public:
 
	// m_nPrecision, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_nPrecision;
 
	// Neg Values, This member sets TRUE if it is right.  
	BOOL m_bNegValues;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFODecimalEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C F O Decimal Edit, Destructor of class CFODecimalEdit
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CFODecimalEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFODecimalEdit)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Char, Handle WM_CHAR message.
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nRepCnt---Rep Cnt, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Kill Focus, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNewWnd---New Window, A pointer to the CWnd or NULL if the call failed.
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FODECIMALEDIT_H__887565D1_E511_44AB_BB78_7E04DD718FB1__INCLUDED_)
