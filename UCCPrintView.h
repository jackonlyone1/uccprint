// UCCPrintView.h : interface of the CUCCPrintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCCPRINTVIEW_H__D3C90EF9_B833_460C_BE7D_1F97A04DCF03__INCLUDED_)
#define AFX_UCCPRINTVIEW_H__D3C90EF9_B833_460C_BE7D_1F97A04DCF03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SvPrintPageInfo
{
	BOOL bNeedDrawMulti;
	int nTotalPage;// bNeedDrawMulti = FALSE
	int nPerPage;
};
typedef CList<SvPrintPageInfo*, SvPrintPageInfo*> CSvPrintPageInfo;

class CUCCPrintDoc;
class CExtTabModel;
 
//===========================================================================
// Summary:
//     The CUCCPrintView class derived from CFOTabPageView
//      U C C Print View
//===========================================================================

class CUCCPrintView : public CFOTabPageView
{
protected: // create from serialization only
	
	//-----------------------------------------------------------------------
	// Summary:
	// U C C Print View, Constructs a CUCCPrintView object.
	//		Returns A  value.
	CUCCPrintView();
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CUCCPrintView---U C C Print View, Specifies A integer value.
	DECLARE_DYNCREATE(CUCCPrintView)

// Attributes
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Document, Returns the specified value.
	//		Returns a int type value.
	CUCCPrintDoc* GetDocument();

public:

	// Do model change.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Change Model, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pModel---*pModel, A pointer to the CFODataModel  or NULL if the call failed.
	virtual void	DoChangeModel(
		// Pointer of model.
		CFODataModel *pModel);

	// Do update ruler.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Update Ruler, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoUpdateRuler();

	// When zoom sacle changed to call this function.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Zoom Scale Changing, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoZoomScaleChanging();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unique D B Name, Returns the specified value.
	//		Returns a CString type value.  
	// Parameters:
	//		*m_ShapeSet---Shape Set, A pointer to the CFODrawShapeSet  or NULL if the call failed.  
	//		&strStart---&strStart, Specifies A CString type value.
	CString GetUniqueDBName(CFODrawShapeSet *m_ShapeSet, const CString &strStart);
	
	// Get ole data object
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Ole Data Object, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape ,or NULL if the call failed  
	// Parameters:
	//		pData---pData, A pointer to the COleDataObject or NULL if the call failed.
	virtual CFODrawShape *GetOleDataObject(COleDataObject* pData);


	// Select All shapes on the canvas.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Select Multiple Type Shpaes, Call this function to select the given item.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShapeSet---Shape Set, A pointer to the CFODrawShapeSet  or NULL if the call failed.  
	//		&nShapeType---Shape Type, Specifies A integer value.
	virtual void	SelectMultiTypeShpaes(CFODrawShapeSet *pShapeSet, const int &nShapeType);

	// Select All shapes on the canvas.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Select All Fields Shpaes, Call this function to select the given item.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShapeSet---Shape Set, A pointer to the CFODrawShapeSet  or NULL if the call failed.
	virtual void	SelectAllFieldsShpaes(CFODrawShapeSet *pShapeSet);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Page Clip_ Begin, None Description.
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pModel---pModel, A pointer to the CExtTabModel or NULL if the call failed.
	void PageClip_Begin(CDC* pDC, CExtTabModel* pModel);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Page Clip_ End, None Description.
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pModel---pModel, A pointer to the CExtTabModel or NULL if the call failed.
	void PageClip_End(CDC* pDC, CExtTabModel* pModel);

	//
	
	//-----------------------------------------------------------------------
	// Summary:
	// Select New Shape, Call this function to select the given item.
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	void SelectNewShape(CFODrawShape *pShape);

	// Override this method to handle the selection change.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Selection Changed, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&bWithAction---With Action, Specifies A Boolean value.
	virtual void	DoSelectionChanged(const BOOL &bWithAction = FALSE);

	// Update cells.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Update Cells, Call this member function to update the object.

	void UpdateCells();

	// Add shape to selection list.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add To Selection, Adds an object to the specify list.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	virtual void AddToSelection(
		// Pointer of shape.
		CFODrawShape *pShape
		);

	// Remove shape to selection list.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Remove From Selection, Call this function to remove a specify value from the specify object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	virtual void RemoveFromSelection(
		// Pointer of shape.
		CFODrawShape *pShape
		);

	// Remove all shapes from the selection list.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Remove All From Selection, Call this function to remove a specify value from the specify object.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void RemoveAllFromSelection();

	// Create context menu.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Context Menu, You construct a CUCCPrintView object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CMenu,or NULL if the call failed
	virtual CMenu* CreateContextMenu();

	// Init layers combobox.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Layers Combo Box, Call InitLayersComboBox after creating a new object.

	void InitLayersComboBox();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Fill Cell, Do a event. 
	// Parameters:
	//		&strText---&strText, Specifies A CString type value.
	void DoFillCell(const CString &strText, const BOOL &bWithExt = TRUE);

	// Layers changed.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Layers Changed, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		lHint---lHint, Specifies A lparam value.
	virtual void DoLayersChanged(
		// Hint value.
		LPARAM lHint);
	
	// Do drawing the additional items.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Draw D B Name, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&strDBName---D B Name, Specifies A CString type value.  
	//		&ptStart---&ptStart, Specifies A CPoint type value.
	virtual void DoDrawDBName(CDC *pDC,const CString &strDBName, const CPoint &ptStart);

 
	// Show Clipping Line, This member sets TRUE if it is right.  
	BOOL	m_bShowClippingLine;
 
	// Corner Radius, This member specify double object.  
	double	m_dCornerRadius;
 
	// Panel Shape Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nPanelShapeType;
 
	// Print Order, This member sets TRUE if it is right.  
	BOOL	m_nPrintOrder;
public:
	
	// Obtain the default virtual origin.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Canvas Orgin Offset, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CSize type value.
	virtual CSize GetCanvasOrginOffset() const;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Layer, Returns the specified value.
	//		Returns a UINT type value.
	UINT GetLayer();

	// Show shape Event setting dialog.
	// pShape -- pointer of the shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Show Event Property Dialog, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	virtual void DoShowEventPropDlg(CFODrawShape *pShape);

	// Do generate the init additional items.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Generate Initial Items, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	virtual void DoGenInitItems(CFODrawShape *pShape);
	
	// Do something when click on the items.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do When Click Additional, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoWhenClickAddi();

	// Get all sub report's total pages.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get All Child Pages, Returns the specified value.
	//		Returns a int type value.
	int GetAllSubPages();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUCCPrintView)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Create Window, Called before the creation of the Windows window attached to this CWnd object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		cs---Specifies a CREATESTRUCT& cs object.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Drop, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pDataObject---Data Object, A pointer to the COleDataObject or NULL if the call failed.  
	//		dropEffect---dropEffect, Specifies a DROPEFFECT dropEffect object.  
	//		point---Specifies A CPoint type value.
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Prepare D C, Called before the OnDraw member function is called for screen display or the OnPrint member function is called for printing or print preview.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Update, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnInitialUpdate(); // called first time after construct
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Prepare Printing, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Begin Printing, Called when a print job begins; override to allocate graphics device interface (GDI) resources.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On End Printing, Called when a print job ends; override to deallocate GDI resources.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Print, Called to print or preview a page of the document.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update, Called to notify a view that its document has been modified.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pSender---pSender, A pointer to the CView or NULL if the call failed.  
	//		lHint---lHint, Specifies A lparam value.  
	//		pHint---pHint, A pointer to the CObject or NULL if the call failed.
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Activate View, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		bActivate---bActivate, Specifies A Boolean value.  
	//		pActivateView---Activate View, A pointer to the CView or NULL if the call failed.  
	//		pDeactiveView---Deactive View, A pointer to the CView or NULL if the call failed.
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C U C C Print View, Destructor of class CUCCPrintView
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CUCCPrintView();
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
	// Do print single model.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Print One Page, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		*pModel---*pModel, A pointer to the CFOTabPageModel  or NULL if the call failed.  
	//		&nIndex---&nIndex, Specifies A integer value.  
	//		&bPreview---&bPreview, Specifies A Boolean value.  
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	virtual void DoPrintOnePage(CDC *pDC,CFOTabPageModel *pModel,const int &nIndex,
		BOOL &bPreview, CPrintInfo* pInfo);
	
	// Draw single model
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sv Draw Single Model Print Objects, None Description.
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		*pModel---*pModel, A pointer to the CFOTabPageModel  or NULL if the call failed.  
	//		&rcPrintPage---Print Page, Specifies A CRect type value.  
	//		pInfo---pInfo, A pointer to the CPrintInfo or NULL if the call failed.
	void SvDrawSingleModelPrintObjects(CDC *pDC,CFOTabPageModel *pModel,const CRect &rcPrintPage, CPrintInfo* pInfo);
	
	// Calc the total print pages.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sv Calculate Total Print Pages, None Description.

	void SvCalcTotalPrintPages();
		
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUCCPrintView)
	afx_msg void OnFilePrintPreview();
	afx_msg void OnViewDesignmode();
	afx_msg void OnUpdateViewDesignmode(CCmdUI* pCmdUI);
	afx_msg void OnViewRunmode();
	afx_msg void OnUpdateViewRunmode(CCmdUI* pCmdUI);
	afx_msg void OnFontScaleChange();
	afx_msg void OnFontFaceChange();
	afx_msg void OnFontSizeChange();
	afx_msg void OnLayerChange();
	afx_msg void OnFontBulleted();
	afx_msg void OnUpdateFontBulleted(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFontColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineWidth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineType(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFillColor(CCmdUI* pCmdUI);
	afx_msg void OnFontColor();
	afx_msg void OnLineColor();
	afx_msg void OnLineType();
	afx_msg void OnLineWidth();
	afx_msg void OnFillColor();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateFontFacename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFontTypesize(CCmdUI* pCmdUI);
	afx_msg void OnDrawButton();
	afx_msg void OnUpdateDrawButton(CCmdUI* pCmdUI);
	afx_msg void OnDrawCheckbox();
	afx_msg void OnUpdateDrawCheckbox(CCmdUI* pCmdUI);
	afx_msg void OnDrawCombobox();
	afx_msg void OnUpdateDrawCombobox(CCmdUI* pCmdUI);
	afx_msg void OnDrawEdit();
	afx_msg void OnUpdateDrawEdit(CCmdUI* pCmdUI);
	afx_msg void OnDrawEditwithbutton();
	afx_msg void OnUpdateDrawEditwithbutton(CCmdUI* pCmdUI);
	afx_msg void OnDrawGroupbox();
	afx_msg void OnUpdateDrawGroupbox(CCmdUI* pCmdUI);
	afx_msg void OnDrawProgress();
	afx_msg void OnUpdateDrawProgress(CCmdUI* pCmdUI);
	afx_msg void OnDrawRadio();
	afx_msg void OnUpdateDrawRadio(CCmdUI* pCmdUI);
	afx_msg void OnDrawRect();
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
	afx_msg void OnDrawRoundbutton();
	afx_msg void OnUpdateDrawRoundbutton(CCmdUI* pCmdUI);
	afx_msg void OnDrawSeparater();
	afx_msg void OnUpdateDrawSeparater(CCmdUI* pCmdUI);
	afx_msg void OnDrawSlider();
	afx_msg void OnUpdateDrawSlider(CCmdUI* pCmdUI);
	afx_msg void OnDrawSpinedit();
	afx_msg void OnUpdateDrawSpinedit(CCmdUI* pCmdUI);
	afx_msg void OnDrawMaskedit();
	afx_msg void OnUpdateDrawMaskedit(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorderFull();
	afx_msg void OnUpdateFormatBorderFull(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorderNone();
	afx_msg void OnUpdateFormatBorderNone(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorderLeft();
	afx_msg void OnUpdateFormatBorderLeft(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorderTop();
	afx_msg void OnUpdateFormatBorderTop(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorderRight();
	afx_msg void OnUpdateFormatBorderRight(CCmdUI* pCmdUI);
	afx_msg void OnFormatBorderBottom();
	afx_msg void OnUpdateFormatBorderBottom(CCmdUI* pCmdUI);
	afx_msg void OnListProp();
	afx_msg void OnUpdateListProp(CCmdUI* pCmdUI);
	afx_msg void OnDrawListbox();
	afx_msg void OnUpdateDrawListbox(CCmdUI* pCmdUI);
	afx_msg void OnDrawPasswordedit();
	afx_msg void OnUpdateDrawPasswordedit(CCmdUI* pCmdUI);
	afx_msg void OnDrawMcombobox();
	afx_msg void OnUpdateDrawMcombobox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLayers(CCmdUI* pCmdUI);
	afx_msg void OnDrawDatechoose();
	afx_msg void OnUpdateDrawDatechoose(CCmdUI* pCmdUI);
	afx_msg void OnDrawMenuedit();
	afx_msg void OnUpdateDrawMenuedit(CCmdUI* pCmdUI);
	afx_msg void OnViewRuler();
	afx_msg void OnUpdateViewRuler(CCmdUI* pCmdUI);
	afx_msg void OnDrawAutofont();
	afx_msg void OnUpdateDrawAutofont(CCmdUI* pCmdUI);
	afx_msg void OnDrawNumber();
	afx_msg void OnUpdateDrawNumber(CCmdUI* pCmdUI);
	afx_msg void OnFoDrawNewgrid();
	afx_msg void OnUpdateFoDrawNewgrid(CCmdUI* pCmdUI);
	afx_msg void OnInsertObjects();
	afx_msg void OnUpdateInsertObjects(CCmdUI* pCmdUI);
	afx_msg void OnDrawCalc();
	afx_msg void OnUpdateDrawCalc(CCmdUI* pCmdUI);
	afx_msg void OnSetDbName();
	afx_msg void OnUpdateSetDbName(CCmdUI* pCmdUI);
	afx_msg void OnDrawBarcode();
	afx_msg void OnFoUserProp();
	afx_msg void OnUpdateFoUserProp(CCmdUI* pCmdUI);
	afx_msg void OnFoDrawBox();
	afx_msg void OnUpdateFoDrawBox(CCmdUI* pCmdUI);
	afx_msg void OnViewDbname();
	afx_msg void OnUpdateViewDbname(CCmdUI* pCmdUI);
	afx_msg void OnSelectAllText();
	afx_msg void OnUpdateSelectAllText(CCmdUI* pCmdUI);
	afx_msg void OnSleectAllFields();
	afx_msg void OnUpdateSleectAllFields(CCmdUI* pCmdUI);
	afx_msg void OnLockAllLabels();
	afx_msg void OnUpdateLockAllLabels(CCmdUI* pCmdUI);
	afx_msg void OnLockAllFields();
	afx_msg void OnUpdateLockAllFields(CCmdUI* pCmdUI);
	afx_msg void OnOffsetCanvas();
	afx_msg void OnUpdateOffsetCanvas(CCmdUI* pCmdUI);
	afx_msg void OnAutoSizeText();
	afx_msg void OnUpdateAutoSizeText(CCmdUI* pCmdUI);
	afx_msg void OnDrawImageBox();
	afx_msg void OnUpdateDrawImageBox(CCmdUI* pCmdUI);
	afx_msg void OnChangeBinding();
	afx_msg void OnUpdateChangeBinding(CCmdUI* pCmdUI);
	afx_msg void OnDrawPicBox();
	afx_msg void OnUpdateDrawPicBox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawBarcode(CCmdUI* pCmdUI);
	afx_msg void OnDrawSubReport();
	afx_msg void OnUpdateDrawSubReport(CCmdUI* pCmdUI);
	afx_msg void OnOnlyPrintOne();
	afx_msg void OnUpdateOnlyPrintOne(CCmdUI* pCmdUI);
	afx_msg void OnDrawSymbol();
	afx_msg void OnUpdateDrawSymbol(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnDrawChart();
	afx_msg void OnUpdateDrawChart(CCmdUI* pCmdUI);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Fo Event Properties, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFoEventProperties();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Fo Event Properties, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateFoEventProperties(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On None Text Color, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNoneTextColor();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Auto Text Color, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAutoTextColor();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Text Color Change, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnTextColorChange();
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// On None Line Color, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNoneLineColor();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Auto Line Color, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAutoLineColor();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Line Color Change, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnLineColorChange();
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// On None Fill Color, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNoneFillColor();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Auto Fill Color, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAutoFillColor();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Fill Color Change, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFillColorChange();
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// On None Line Width, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNoneLineWidth();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Line Width Change, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnLineWidthChange();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Line Type Change, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnLineTypeChange();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Undo Redo O K, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns A 32-bit signed integer.  
	// Parameters:
	//		wParam---wParam, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		lParam---lParam, Specifies A 32-bit signed integer.
	afx_msg LONG OnUndoRedoOK(UINT wParam, LONG lParam);
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
		
protected:
 
	// m_ftField, The CFont class encapsulates a Windows graphics device interface (GDI) font and provides member functions for manipulating the font.  
	CFont m_ftField;
 
	// Batch Print, This member sets TRUE if it is right.  
	BOOL m_bBatchPrint;
	
 
	// Sv Print Page Information, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	SvPrintPageInfo m_SvPrintPageInfo;
	
 
	// Horizontal Print Offset, This member specify double object.  
	double m_nHorzPrintOffset;
 
	// Vertical Print Offset, This member specify double object.  
	double m_nVertPrintOffset;
	
 
	// Horizontal Gap, This member specify double object.  
	double m_nHorzGap;
 
	// Vertical Gap, This member specify double object.  
	double m_nVertGap;
 
	// Only Print One, This member sets TRUE if it is right.  
	BOOL m_bOnlyPrintOne;
};

#ifndef _DEBUG  // debug version in UCCPrintView.cpp
inline CUCCPrintDoc* CUCCPrintView::GetDocument()
{ return (CUCCPrintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCCPRINTVIEW_H__D3C90EF9_B833_460C_BE7D_1F97A04DCF03__INCLUDED_)
