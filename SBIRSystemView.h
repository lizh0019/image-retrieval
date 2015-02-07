// SBIRSystemView.h : interface of the CSBIRSystemView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SBIRSYSTEMVIEW_H__48B5165E_239E_49B8_9F92_047F98940B12__INCLUDED_)
#define AFX_SBIRSYSTEMVIEW_H__48B5165E_239E_49B8_9F92_047F98940B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Classes\PictCtrl.h"
#include "LIB\CIMAGE.H"	// Added by ClassView
#include "ImageBaseManage.h"
#include "RetrievalControl.h"
#define MAX_NUMBERANNOTION_RELEVANT 10    ////the most relevant annotion is 10
#define  MAX_NUMBERANNOTION_RETRIEVAL 10	//the most relevant annotion is 10
class CSBIRSystemView : public CFormView
{
protected: // create from serialization only
	CSBIRSystemView();
	DECLARE_DYNCREATE(CSBIRSystemView)
protected:
	bool m_bIntilization;
	CPictureCtrl *m_pCPictureCtrl[12];//12 images per page
	int *m_piRelevance[12];
	CString *m_psSimilarity[12];
	int m_iRelevantAnnotionIDs[10];        //the most relevant annotion is 10
//	int m_iNumberCurrent
	int m_piRetrievalAnnotionIDS[10];  //the most relevant annotion is 10

public:
	//{{AFX_DATA(CSBIRSystemView)
	enum { IDD = IDD_SBIRSYSTEM_FORM };
	CButton	m_cParamentSet;
	CEdit	m_cKeyWordInput;
	CButton	m_cButtonRetrievalKeyWord;
	CListBox	m_cListBoxKeyWordRetrievied;
	CButton	m_cOpenSampleImage;
	CListBox	m_cRelevantAnnotionList;
	CButton	m_cFeedbackControl;
	CButton	m_CRadio1;
	CButton	m_cShouldRetrieval;
	CButton	m_cHomePage;
	CButton	m_cPrePage;
	CButton	m_cNextPage;
	CPictureCtrl	m_cRetrievalResult9;
	CPictureCtrl	m_cRetrievalResult8;
	CPictureCtrl	m_cRetrievalResult7;
	CPictureCtrl	m_cRetrievalResult6;
	CPictureCtrl	m_cRetrievalResult5;
	CPictureCtrl	m_cRetrievalResult4;
	CPictureCtrl	m_cRetrievalResult3;
	CPictureCtrl	m_cRetrievalResult2;
	CPictureCtrl	m_cRetrievalResult12;
	CPictureCtrl	m_cRetrievalResult11;
	CPictureCtrl	m_cRetrievalResult10;
	CPictureCtrl	m_cRetrievalResult1;  
	CPictureCtrl	m_cSampleImage;  //the key image
	int		m_iRelevance_1;
	int		m_iRelevance_2;
	int		m_iRelevance_3;
	int		m_iRelevance_4;
	int		m_iRelevance_5;
	int		m_iRelevance_6;
	int		m_iRelevance_7;
	int		m_iRelevance_8;
	int		m_iRelevance_9;
	int		m_iRelevance_10;
	int		m_iRelevance_11;
	int		m_iRelevance_12;
	CString	m_sSimilarity_1;
	CString	m_sSimilarity_10;
	CString	m_sSimilarity_11;
	CString	m_sSimilarity_12;
	CString	m_sSimilarity_2;
	CString	m_sSimilarity_3;
	CString	m_sSimilarity_4;
	CString	m_sSimilarity_5;
	CString	m_sSimilarity_6;
	CString	m_sSimilarity_7;
	CString	m_sSimilarity_8;
	CString	m_sSimilarity_9;
	double	m_dThreshold;
	CString	m_sNumberImageDataBase;
	CString	m_sSampleID;
	CString	m_sNumberResult;
	CString	m_sImagePath;
	CString	m_sStudyTimes;
	CString	m_sTotalPage;
	CString	m_sCurrentPage;
	double	m_dRecall;
	double	m_dPrecise;
	CString	m_sFeedbackTimes;
	CString	m_sImageOrAnnotion;
	CString	m_sKeyWord;
	//}}AFX_DATA

// Attributes
public:
	CSBIRSystemDoc* GetDocument();

protected:
	CImageBaseManage m_cImageBasemanage;
// Operations
public:
	int m_iCurrentAnnotionIndex;
	bool m_bAnnotionOpened;
	bool m_bCanFeedback;
	CString m_sSampleImageFullName;
	CString m_sImageBasePath;
	CRetrievalControl m_cRetrievalControl;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSBIRSystemView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Display(CPictureCtrl &PictureCtrl);
	void UpdateDisplay();
	virtual ~CSBIRSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void updateRelevanceData();
	void DisplayResult();
	//{{AFX_MSG(CSBIRSystemView)
	afx_msg void OnButtonOpensample();
	afx_msg void OnButtonImagedatabase();
	afx_msg void OnButtonRetrieval();
	afx_msg void OnButtonNextpage();
	afx_msg void OnButtonPrepage();
	afx_msg void OnButtonHomepage();
	afx_msg void OnChangeThreshold();
	afx_msg void OnButtonRelevancefeedback();
	afx_msg void OnButtonParameter();
	afx_msg void OnGetinformatino();
	afx_msg void OnRetrievalMethodTest();
	afx_msg void OnInitialSemanticannotion();
	afx_msg void OnOpenAnnotion();
	afx_msg void OnDblclkListAnnotion();
	afx_msg void OnCloseAnnotion();
	afx_msg void OnUpdateOpenAnnotion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCloseAnnotion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInitialSemanticannotion(CCmdUI* pCmdUI);
	afx_msg void OnResulte1();
	afx_msg void OnResulte2();
	afx_msg void OnResulte10();
	afx_msg void OnResulte11();
	afx_msg void OnResulte12();
	afx_msg void OnResulte3();
	afx_msg void OnResulte4();
	afx_msg void OnResulte5();
	afx_msg void OnResulte6();
	afx_msg void OnResulte7();
	afx_msg void OnResulte8();
	afx_msg void OnResulte9();
	afx_msg void OnChangeEditKeywordRetrievied();
	afx_msg void OnButtonKeywordretrieval();
	afx_msg void OnDblclkListKeywordretrievied();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SBIRSystemView.cpp
inline CSBIRSystemDoc* CSBIRSystemView::GetDocument()
   { return (CSBIRSystemDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SBIRSYSTEMVIEW_H__48B5165E_239E_49B8_9F92_047F98940B12__INCLUDED_)
