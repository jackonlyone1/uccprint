#if !defined(AFX_SVIMAGECONTROL_H__15103B52_8ECB_46BE_ACE9_4B7ECF8FDD5D__INCLUDED_)
#define AFX_SVIMAGECONTROL_H__15103B52_8ECB_46BE_ACE9_4B7ECF8FDD5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SVImageControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSVImageControl window

#define SV_COMP_IMAGE_CONTROL 752

/////////////////////////////////////////////////////////////////////////////
// CGdiplusFileDialog dialog

 
//===========================================================================
// Summary:
//      To use a CGdiplusCodecInfo object, just call the constructor.
//      Gdiplus Codec Information
//===========================================================================

class CGdiplusCodecInfo  
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Gdiplus Codec Information, Constructs a CGdiplusCodecInfo object.
	//		Returns A  value.  
	// Parameters:
	//		wcsFormat---wcsFormat, Specifies a LPCWSTR wcsFormat object.  
	//		wcsExtensions---wcsExtensions, Specifies a LPCWSTR wcsExtensions object.  
	//		clsid---Specifies a const CLSID& clsid object.
	CGdiplusCodecInfo(LPCWSTR wcsFormat, 
		LPCWSTR wcsExtensions,
		const CLSID& clsid);
	
	// Attributes
protected:
 
	// m_strFormat, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strFormat;     // name of the file format (e.g. "JPEG").
 
	// m_strExtensions, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strExtensions; // used extensions (e.g. "*.JPG;*.JPEG;*.JPE;*.JFIF").
 
	// Default Extend, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strDefExt;     // extension to be used in Save As as default (e.g. "JPG").
 
	// This member specify CLSID object.  
	CLSID   m_clsid;         // codec identifier
	
	// Operations
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Format, Returns the specified value.
	//		Returns a CString type value.
	CString GetFormat() const {return m_strFormat;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Extensions, Returns the specified value.
	//		Returns a CString type value.
	CString GetExtensions() const {return m_strExtensions;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Default Extend, Returns the specified value.
	//		Returns A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	LPCTSTR GetDefExt() const {return m_strDefExt;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get C L S I D, Returns the specified value.
	//		Returns A CLSID value.
	CLSID   GetCLSID() const {return m_clsid;}
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Extension, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns A Boolean value.  
	// Parameters:
	//		pszExt---pszExt, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	bool FindExtension(LPCTSTR pszExt);
	
	// Implementation
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Convert Copy, None Description.
	// Parameters:
	//		str---Specifies A CString type value.  
	//		wcs---Specifies a LPCWSTR wcs object.
	void ConvertCopy(CString& str, LPCWSTR wcs);
	
};

 
//===========================================================================
// Summary:
//     The CGdiplusFileDialog class derived from CFileDialog
//      Gdiplus File Dialog
//===========================================================================

class CGdiplusFileDialog : public CFileDialog
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N A M I C, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CGdiplusFileDialog---Gdiplus File Dialog, Specifies a CGdiplusFileDialog object.
	DECLARE_DYNAMIC(CGdiplusFileDialog)
		
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Gdiplus File Dialog, Constructs a CGdiplusFileDialog object.
	//		Returns A  value.  
	// Parameters:
	//		bOpenFileDialog---Open File Dialog, Specifies A Boolean value.  
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		dwFlags---dwFlags, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.  
	//		pParentWnd---Parent Window, A pointer to the CWnd or NULL if the call failed.
	CGdiplusFileDialog(BOOL bOpenFileDialog, 
		LPCTSTR lpszFileName, 
		DWORD dwFlags,
		CWnd* pParentWnd);
	
	// Attributes
protected:
	CTypedPtrArray<CPtrArray, CGdiplusCodecInfo*> m_arrCodecInfo;
	
	// Operations
public:
	
	// Overides
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Fill Codec Information Array, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		)---Specifies a ) = 0 object.
	virtual void FillCodecInfoArray() = 0;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Construct M F C Style Filter, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		)---Specifies a ) = 0 object.
	virtual void ConstructMFCStyleFilter() = 0;
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Modal, Calls a modal dialog box and returns when done.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a int type value.
	virtual int DoModal();
	
	// Implementation
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Translate Filter, None Description.

	void TranslateFilter();
	
	//{{AFX_MSG(CGdiplusFileDialog)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGdiplusFileOpenDialog dialog

 
//===========================================================================
// Summary:
//     The CGdiplusFileOpenDialog class derived from CGdiplusFileDialog
//      Gdiplus File Open Dialog
//===========================================================================

class CGdiplusFileOpenDialog : public CGdiplusFileDialog
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N A M I C, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CGdiplusFileOpenDialog---Gdiplus File Open Dialog, Specifies a CGdiplusFileOpenDialog object.
	DECLARE_DYNAMIC(CGdiplusFileOpenDialog)
		
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Gdiplus File Open Dialog, Constructs a CGdiplusFileOpenDialog object.
	//		Returns A  value.  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		dwFlags---dwFlags, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.  
	//		pParentWnd---Parent Window, A pointer to the CWnd or NULL if the call failed.
	CGdiplusFileOpenDialog(LPCTSTR lpszFileName = NULL, 
		DWORD dwFlags = OFN_HIDEREADONLY,
		CWnd* pParentWnd = NULL);
	// Attributes
protected:
	
	// Operations
public:
	
	// Overrides
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Fill Codec Information Array, None Description.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void FillCodecInfoArray();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Construct M F C Style Filter, None Description.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void ConstructMFCStyleFilter();
	
	// Implementation
protected:
	//{{AFX_MSG(CGdiplusFileOpenDialog)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

class CFOEditBoxShape;
 
//===========================================================================
// Summary:
//     The CSVImageControl class derived from CFOEditBoxShape
//      S V Image 
//===========================================================================

class CSVImageControl : public CFOEditBoxShape  
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CSVImageControl---S V Image , Specifies a CSVImageControl object.
	DECLARE_SERIAL(CSVImageControl);
public:
	// constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// S V Image , Constructs a CSVImageControl object.
	//		Returns A  value.
	CSVImageControl();

	// Copy constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// S V Image , Constructs a CSVImageControl object.
	//		Returns A  value.  
	// Parameters:
	//		src---Specifies a const CSVImageControl& src object.
	CSVImageControl(const CSVImageControl& src);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C S V Image , Destructor of class CSVImageControl
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CSVImageControl();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CSVImageControl object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		strCaption---strCaption, Specifies A CString type value.
	// Creates the button shape from a CRect object.
	virtual void Create(CRect &rcPos,CString strCaption = "");

	// Init image position.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Image Position, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CRect type value.  
	// Parameters:
	//		nImageWidth---Image Width, Specifies A integer value.  
	//		nImageHeight---Image Height, Specifies A integer value.
	virtual CRect DoInitImagePos(int nImageWidth,int nImageHeight);

	// Calc text line array.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Text Array, You construct a CSVImageControl object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a int type value.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		strText---strText, Specifies A CString type value.  
	//		rcBox---rcBox, Specifies A CRect type value.  
	//		arLines---arLines, Specifies A CString type value.
	virtual int CreateTextArray(CDC* pDC, CString strText,CRect rcBox,CStringArray& arLines);

	// call this method to put the text object into edit in place mode
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Start Show Edit, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pView---pView, A pointer to the CFOPCanvasCore or NULL if the call failed.  
	//		ptCursorSP---Cursor S P, Specifies A CPoint type value.
	virtual BOOL DoStartShowEdit(CFOPCanvasCore* pView, CPoint ptCursorSP);
    
public:
	// Assignment operator.
	
	//-----------------------------------------------------------------------
	// Summary:
	// None Description.
	//		Returns A CSVImageControl& value.  
	// Parameters:
	//		src---Specifies a const CSVImageControl& src object.
	CSVImageControl& operator=(const CSVImageControl& src);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed
	// Creates a copy of this shape.
	virtual CFODrawShape* Copy() const;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Geometry Updated, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pRgn---pRgn, A pointer to the CFOArea or NULL if the call failed.
	virtual void GeometryUpdated(CFOArea* pRgn);

	// Rotate shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Rotate Shape, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nAngle---nAngle, Specifies A integer value.  
	//		fOX---O X, Specifies A float value.  
	//		fOY---O Y, Specifies A float value.
	virtual void RotateShape(int nAngle, float fOX, float fOY);

	// Rotate shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Rotate Track Shape, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nAngle---nAngle, Specifies A integer value.  
	//		fOX---O X, Specifies A float value.  
	//		fOY---O Y, Specifies A float value.
	virtual void RotateTrackShape(int nAngle, float fOX, float fOY);

	// override this method to return the text which
	// is displayed in the current shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Current Text, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		strResult---strResult, Specifies A CString type value.
	virtual void GetCurrentText(CString& strResult);
		
	// override this method to set the text as it should
	// be displayed in the current shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Current Text, Sets a specify value to current class CSVImageControl
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		str---Specifies A CString type value.
	virtual void SetCurrentText(const CString& str);

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
	// Draws custom tracker.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Track Custom, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawTrackCustom(CDC *pDC);

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

	// Draws the truely shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw(CDC *pDC);
	
	// Draws the Text status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Text, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawText(CDC *pDC);

	// Frees GDI objects and restores the state of the device context.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear D C, Remove the specify data from the list.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void ClearDC(CDC* pDC);
	// Implementation

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
	// Crrent font image list.
 
	// Font Name, This member is a collection of same-sized images.  
	CImageList m_imgFontName;	
 
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Codec Clsid, Returns the specified value.
	// This member function is a static function.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		format---A pointer to the const WCHAR or NULL if the call failed.  
	//		pClsid---pClsid, A pointer to the CLSID or NULL if the call failed.
	static BOOL GetCodecClsid(const WCHAR* format, CLSID* pClsid);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Check Clsid, None Description.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pClsid---pClsid, A pointer to the CLSID or NULL if the call failed.  
	//		*clsidOut---*clsidOut, A pointer to the GUID  or NULL if the call failed.
	BOOL CheckClsid(CLSID* pClsid, GUID *clsidOut);
 
	// Bitmap Plus, This member maintains a pointer to the object Bitmap.  
	Bitmap *m_pBitmapPlus;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Real Size, Returns the specified value.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL GetRealSize() {return m_bRealSize;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Real Size, Sets a specify value to current class CSVImageControl
	// Parameters:
	//		&bRealSize---Real Size, Specifies A Boolean value.
	void SetRealSize(const BOOL &bRealSize) {m_bRealSize = bRealSize;}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Transparent Color, Returns the specified value.
	//		Returns A 32-bit value used as a color value.
	COLORREF GetTransparentColor() {return m_crTransparent;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Transparent Color, Sets a specify value to current class CSVImageControl
	// Parameters:
	//		&cr---Specifies A 32-bit value used as a color value.
	void SetTransparentColor(const COLORREF &cr) {m_crTransparent = cr;}
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Color Offset, Returns the specified value.
	//		Returns a int type value.
	int GetColorOffset() {return m_nColorOffset;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Color Offset, Sets a specify value to current class CSVImageControl
	// Parameters:
	//		&nColorOffset---Color Offset, Specifies A integer value.
	void SetColorOffset(const int &nColorOffset) {m_nColorOffset = nColorOffset;}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Transparent, Returns the specified value.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL GetTransparent() {return m_bTransparent;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Transparent, Sets a specify value to current class CSVImageControl
	// Parameters:
	//		&bTransparent---&bTransparent, Specifies A Boolean value.
	void SetTransparent(const BOOL &bTransparent) {m_bTransparent = bTransparent;}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Rotate Flip, Returns the specified value.
	//		Returns A RotateFlipType value.
	RotateFlipType GetRotateFlip() {return m_RotateFlip;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Rotate Flip, Sets a specify value to current class CSVImageControl
	// Parameters:
	//		&rotateFlip---&rotateFlip, Specifies a const RotateFlipType &rotateFlip object.
	void SetRotateFlip(const RotateFlipType &rotateFlip) {m_RotateFlip = rotateFlip;}
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Alpha, Returns the specified value.
	//		Returns A 32-bit signed integer.
	long GetAlpha() {return m_nAlpha;}
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Alpha, Sets a specify value to current class CSVImageControl
	// Parameters:
	//		&nAlpha---&nAlpha, Specifies A 32-bit signed integer.
	void SetAlpha(const long &nAlpha) {m_nAlpha = nAlpha;}

private:
 
	// Real Size, This member sets TRUE if it is right.  
	BOOL m_bRealSize;

 
	// m_bTransparent, This member sets TRUE if it is right.  
	BOOL m_bTransparent;
 
	// Color Offset, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int  m_nColorOffset;
 
	// m_crTransparent, This member sets A 32-bit value used as a color value.  
	COLORREF m_crTransparent;

 
	// Rotate Flip, This member specify RotateFlipType object.  
	RotateFlipType m_RotateFlip;
	
 
	// m_nAlpha, Specify a A 32-bit signed integer.  
	long m_nAlpha;
 
	// C M, This member specify ColorMatrix object.  
	ColorMatrix m_CM;
 
	// Image H, This member specify REAL object.  
	REAL m_dImageH;
 
	// Image W, This member specify REAL object.  
	REAL m_dImageW;
	
 
	// Vertical Res, This member specify REAL object.  
	REAL m_nVertRes;
 
	// Hori Res, This member specify REAL object.  
	REAL m_nHoriRes;
	
private:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Draw Image, Draws current object to the specify device.
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	void DrawImage(CDC *pDC);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Encode Image File, None Description.

	void EncodeImageFile();
 
	// Old Image Path, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strOldImagePath;
	
 
	// Serials Path, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strSerialsPath;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Check Current Image, None Description.
	//		Returns a CString type value.  
	// Parameters:
	//		&strImageName---Image Name, Specifies A CString type value.
	CString CheckCurrentImage(const CString &strImageName);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVIMAGECONTROL_H__15103B52_8ECB_46BE_ACE9_4B7ECF8FDD5D__INCLUDED_)
