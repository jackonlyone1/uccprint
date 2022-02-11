#if !defined(FO_FOEFHYPERLINKSHAPE_H__BD042E29_8909_41C7_84F0_C866F1935C1F__INCLUDED_)
#define FO_FOEFHYPERLINKSHAPE_H__BD042E29_8909_41C7_84F0_C866F1935C1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////////////
// CFOEFHyperLinkShape

#define MY_EXT_HYPERLINK	FO_COMP_CUSTOM + 201

 
//===========================================================================
// Summary:
//     The CFOEFHyperLinkShape class derived from CFOPEFormBaseShape
//      F O E F Hyper Link Shape
//===========================================================================

class CFOEFHyperLinkShape : public CFOPEFormBaseShape  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CFOEFHyperLinkShape---F O E F Hyper Link Shape, Specifies a E-XD++ CFOEFHyperLinkShape object.
	DECLARE_SERIAL(CFOEFHyperLinkShape);
public:

	// constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O E F Hyper Link Shape, Constructs a CFOEFHyperLinkShape object.
	//		Returns A  value.
	CFOEFHyperLinkShape();

	// Copy constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O E F Hyper Link Shape, Constructs a CFOEFHyperLinkShape object.
	//		Returns A  value.  
	// Parameters:
	//		src---Specifies a const CFOEFHyperLinkShape& src object.
	CFOEFHyperLinkShape(const CFOEFHyperLinkShape& src);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C F O E F Hyper Link Shape, Destructor of class CFOEFHyperLinkShape
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CFOEFHyperLinkShape();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CFOEFHyperLinkShape object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		strCaption---strCaption, Specifies A CString type value.
	// Create the check box shape from a CRect object.
	// rcPos -- position of shape.
	// strCaption -- caption of shape.
	virtual void Create(CRect &rcPos,CString strCaption = _T(""));

public:

	// Assignment operator.
	
	//-----------------------------------------------------------------------
	// Summary:
	// None Description.
	//		Returns A E-XD++ CFOEFHyperLinkShape& value.  
	// Parameters:
	//		src---Specifies a const CFOEFHyperLinkShape& src object.
	CFOEFHyperLinkShape& operator=(const CFOEFHyperLinkShape& src);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed
	// Creates a copy of this shape.
	virtual CFODrawShape* Copy() const;

    // Generate Shape Area
	
	//-----------------------------------------------------------------------
	// Summary:
	// Geometry Updated, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pArea---pArea, A pointer to the CFOArea or NULL if the call failed.
	virtual void GeometryUpdated(CFOArea* pArea);


public:

	// Do check Event.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Click Event, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nSel---nSel, Specifies A integer value.
	virtual void DoClickEvent(int nSel);

	// override this method to return the text which
	// is displayed in the current shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Current Text, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.
	virtual CString GetCurrentText();
		
	// override this method to set the text as it should
	// be displayed in the current shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Current Text, Sets a specify value to current class CFOEFHyperLinkShape
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		str---Specifies A CString type value.
	virtual void SetCurrentText(const CString& str);

	// override this method to return the text which
	// is displayed in the current shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Current Edit Text, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		strResult---strResult, Specifies A CString type value.
	virtual void GetCurrentEditText(CString& strResult);
	
	// override this method to set the text as it should
	// be displayed in the current shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Current Edit Text, Sets a specify value to current class CFOEFHyperLinkShape
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		str---Specifies A CString type value.
	virtual void SetCurrentEditText(const CString& str);

	// Get rotate handle location.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Rotate Spot Location, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&ptHandle---&ptHandle, Specifies A CPoint type value.
	virtual BOOL GetRotateSpotLocation(CPoint &ptHandle);

public:

	// Capture the mouse.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Capture Mouse, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		bCapture---bCapture, Specifies A Boolean value.
	virtual void CaptureMouse(BOOL bCapture);

public:
	// WM_CHAR message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Char, Handle WM_CHAR message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nRepCnt---Rep Cnt, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	// WM_LBUTTONDOWN message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Down, Called when the user presses the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonDown(UINT nFlags, CPoint point); 

	// WM_LBUTTONDBLCLK message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Double click Clk, Called when the user double-clicks the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);

	// WM_LBUTTONUP message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Up, Called when the user releases the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonUp(UINT nFlags, CPoint point);

	// WM_RBUTTONDOWN message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On R Button Down, Called when the user presses the right mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnRButtonDown(UINT nFlags, CPoint point); 

	// WM_RBUTTONDBLCLK message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On R Button Double click Clk, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnRButtonDblClk(UINT nFlags, CPoint point);

	// WM_RBUTTONUP message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On R Button Up, Called when the user releases the right mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnRButtonUp(UINT nFlags, CPoint point);

	// WM_MOUSEMOVE message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mouse Move, Called when the mouse cursor moves.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnMouseMove(UINT nFlags, CPoint point);

	// WM_MOUSEMOVE message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mouse Leave, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnMouseLeave(UINT nFlags, CPoint point);

	// WM_KEYDOWN message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Key Down, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nRepCnt---Rep Cnt, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	// WM_KEYUP message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Key Up, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nRepCnt---Rep Cnt, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	// WM_SETCURSOT message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Set Cursor, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pWnd---pWnd, A pointer to the CWnd or NULL if the call failed.  
	//		nHitTest---Hit Test, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		message---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	// WM_COMMAND message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Action, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		wParam---wParam, Provides additional information used in processing the message. The parameter value depends on the message.  
	//		lParam---lParam, Specifies A lparam value.
	virtual BOOL OnAction(WPARAM wParam, LPARAM lParam);

	// WM_KILLFOCUS message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Kill Focus, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pNewWnd---New Window, A pointer to the CWnd or NULL if the call failed.
	virtual void OnKillFocus(CWnd* pNewWnd);

	//	WM_SETFOCUS message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Set Focus, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pOldWnd---Old Window, A pointer to the CWnd or NULL if the call failed.
	virtual  void OnSetFocus(CWnd* pOldWnd);

	// Cancel mode.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Cancel Mode, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnCancelMode();

// Get font metrics.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Font Metrics, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		dxWidth---dxWidth, Specifies A integer value.  
	//		dyHeight---dyHeight, Specifies A integer value.
	virtual void GetFontMetrics(CDC* pDC, int& dxWidth, int& dyHeight);

public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	// Serializes the data.
	virtual void Serialize(CArchive &ar);
	
	// Save document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);

	// Open document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);
	
	// Get file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);
	
	// Release file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Release File, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pFile---pFile, A pointer to the CFile or NULL if the call failed.  
	//		bAbort---bAbort, Specifies A Boolean value.
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);

public:

	// Draw flat status.

	// Creates GDI objects and sets up the device context for drawing. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// Prepare D C, Creates GDI objects and sets up the device context for drawing.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void PrepareDC(CDC* pDC);

	// Draws the flat status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Flat, Draws the flat status of the shape.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawFlat(CDC *pDC);

	// Draws shadow of shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Shadow, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawShadow(CDC *pDC);

	// Draws the 3D status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw3d, Draws the 3d status of the shape.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw3d(CDC *pDC);

	// Frees GDI objects and restores the state of the device context.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear D C, Remove the specify data from the list.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void ClearDC(CDC* pDC);
	// Implementation

	// Draws the truely shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw(CDC *pDC);

	// Draw edit.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Draw Edit, Draws current object to the specify device.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		rcEdit---rcEdit, Specifies A CRect type value.
	virtual void DrawEdit(CDC* pDC,CRect rcEdit);

	// call this method to put the text object into edit in place mode
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Start Edit, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pView---pView, A pointer to the CFOPCanvasCore or NULL if the call failed.  
	//		ptCursorSP---Cursor S P, Specifies A CPoint type value.
	virtual BOOL DoStartEdit(CFOPCanvasCore* pView, CPoint ptCursorSP);
    
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

	// Set the properties of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Text Edit Properties, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnTextEditProperties();

protected:

	// Border pen.
 
	// Border Pen, The CPen class encapsulates a Windows graphics device interface (GDI) pen.  
	CPen *			m_pBorderPen;

};


#endif // !defined(FO_FOEFHYPERLINKSHAPE_H__BD042E29_8909_41C7_84F0_C866F1935C1F__INCLUDED_)
