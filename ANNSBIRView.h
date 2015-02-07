// ANNSBIRView.h : interface of the CANNSBIRView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANNSBIRVIEW_H__334F7A9F_C424_419D_9D36_81D881FAE6EE__INCLUDED_)
#define AFX_ANNSBIRVIEW_H__334F7A9F_C424_419D_9D36_81D881FAE6EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Classes\PictCtrl.h"
#include "LIB\CIMAGE.H"	// Added by ClassView
//#include "ImageBaseManage.h"

typedef struct tagFeatureStruct
{
     CString m_sOriginalFileName;//Original File name
 	 BYTE m_bType;//For bmp: 0; For Jpg: 1
     BYTE m_bBitCount;//Color bit
	 LONG m_lImageWidth;//Image width
	 LONG m_lImageHeight;//Image Height
	 LONG m_lBufferWidth;//Image width in Buffer
	 LONG m_lBufferHeight;//Image Height in Buffer
 	 WORD m_wDimensions;//The feature vector dimension
	 double m_dOAverage; //Original vector average
	 double m_dOVariance;//Original vector Variance
	 double m_dNAverage; //Normalized vector average
	 double m_dNVariance;//Normalized vector Variance
	 double *m_dOriginalFeature; //Original feature vectors
	 double *m_dNormalizedFeature; //Normalized feature vectors
}FEATUREVECTOR,FAR *LPFEATUREVECTOR,*PFEATUREVECTOR;

class CANNSBIRView : public CFormView
{
protected: // create from serialization only
	CANNSBIRView();
	DECLARE_DYNCREATE(CANNSBIRView)
protected:
	bool m_bIntilization;
	CPictureCtrl *m_pCPictureCtrl[12];//12 images per page
	int *m_piRelevance[12];
	CString *m_psSimilarity[12];
	int m_iRelevantAnnotionIDs[10];        //the most relevant annotion is 10
//	int m_iNumberCurrent
	int m_piRetrievalAnnotionIDS[10];  //the most relevant annotion is 10

public:
	BOOL ifopen;
	CString m_SampleImagePath;  //Query Image Path
	CString m_PrintImagePath;   //To Be Printed Image Path
	CString m_DisplayImagePath; //Display Image Path
	FEATUREVECTOR m_vQueryFeatureVector;

	//{{AFX_DATA(CANNSBIRView)
	enum{ IDD = IDD_ANNSBIR_FORM };
	CPictureCtrl	m_RetrievalImage9;
	CPictureCtrl	m_RetrievalImage8;
	CPictureCtrl	m_RetrievalImage7;
	CPictureCtrl	m_RetrievalImage6;
	CPictureCtrl	m_RetrievalImage5;
	CPictureCtrl	m_RetrievalImage4;
	CPictureCtrl	m_RetrievalImage3;
	CPictureCtrl	m_RetrievalImage2;
	CPictureCtrl	m_RetrievalImage14;
	CPictureCtrl	m_RetrievalImage13;
	CPictureCtrl    m_RetrievalImage12;
	CPictureCtrl	m_RetrievalImage11;
	CPictureCtrl	m_RetrievalImage10;
	CPictureCtrl	m_RetrievalImage1;  
//	CStatic	m_cSampleImage;
	
	CString	m_retrievalname1;
	CString	m_retrievalname10;
	CString	m_retrievalname11;
	CString	m_retrievalname12;
	CString	m_retrievalname13;
	CString	m_retrievalname14;
	CString	m_retrievalname15;
	CString	m_retrievalname16;
	CString	m_retrievalname2;
	CString	m_retrievalname3;
	CString	m_retrievalname4;
	CString	m_retrievalname5;
	CString	m_retrievalname6;
	CString	m_retrievalname7;
	CString	m_retrievalname8;
	CString	m_retrievalname9;
	
	CString	m_db;
	CString	m_queryinfo;
	long	m_totalnum;
	long	m_validnum;
	long	m_extractednum;
	long	m_normalizednum;
	int		m_clusters;
	CString	m_savedfeaturefile;
	CString	m_savedcodebookfile;
	CString	m_db10;
	long	m_vectornumber;
	CString	m_readfeaturename;
	CString	m_readbookname;
	int		m_clustersused;
	long	m_retrievednum;
	CString	m_everinterrupted;
	CString	m_basedonnormalized;
	int		m_page;
	CString	m_status;
	CString	m_feedbackinfo;
	CString	m_otherinfo;
	int		m_featuredimension;
	CString	m_savedvqfeaturefile;
	////////////////////////////////////// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CANNSBIRDoc* GetDocument();

// Operations
public:
	CPicture m_pict; //Query Image 
    int m_iCurrentAnnotionIndex;
	bool m_bAnnotionOpened;
	bool m_bCanFeedback;
	CString m_sSampleImageFullName;
	CString m_sImageBasePath;
	CPictureCtrl	m_cSampleImage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANNSBIRView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int curr_Pg;
	CString file_name [12];
	int ShowPage(int Pg_Num, CString Folder_Path, int count);
	int ReadQueryImage(CString ImagePathName, PFEATUREVECTOR FeatureVector);

	virtual ~CANNSBIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CANNSBIRView)
	afx_msg void OnOpenSample();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ANNSBIRView.cpp
inline CANNSBIRDoc* CANNSBIRView::GetDocument()
   { return (CANNSBIRDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANNSBIRVIEW_H__334F7A9F_C424_419D_9D36_81D881FAE6EE__INCLUDED_)
