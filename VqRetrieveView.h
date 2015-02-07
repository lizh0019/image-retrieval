// VqRetrieveView.h : interface of the CVqRetrieveView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VQRETRIEVEVIEW_H__1DA28C88_0929_40E7_8C55_A8388337059F__INCLUDED_)
#define AFX_VQRETRIEVEVIEW_H__1DA28C88_0929_40E7_8C55_A8388337059F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVqRetrieveView : public CFormView
{
protected: // create from serialization only
	CVqRetrieveView();
	DECLARE_DYNCREATE(CVqRetrieveView)

public:
	//{{AFX_DATA(CVqRetrieveView)
	enum { IDD = IDD_VQRETRIEVE_FORM };
	CStatic	m_RetrievalImage9;
	CStatic	m_RetrievalImage8;
	CStatic	m_RetrievalImage7;
	CStatic	m_RetrievalImage6;
	CStatic	m_RetrievalImage5;
	CStatic	m_RetrievalImage4;
	CStatic	m_RetrievalImage3;
	CStatic	m_RetrievalImage2;
	CStatic	m_RetrievalImage16;
	CStatic	m_RetrievalImage15;
	CStatic	m_RetrievalImage14;
	CStatic	m_RetrievalImage13;
	CStatic	m_RetrievalImage12;
	CStatic	m_RetrievalImage11;
	CStatic	m_RetrievalImage10;
	CStatic	m_RetrievalImage1;
	CStatic	m_QueryImage;
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
	float	m_dis1;
	float	m_dis10;
	float	m_dis11;
	float	m_dis12;
	float	m_dis13;
	float	m_dis14;
	float	m_dis15;
	float	m_dis16;
	float	m_dis2;
	float	m_dis3;
	float	m_dis4;
	float	m_dis5;
	float	m_dis6;
	float	m_dis7;
	float	m_dis8;
	float	m_dis9;
	CString	m_db;
	CString	m_queryinfo;
	long	m_totalnum;
	long	m_validnum;
	long	m_extractednum;
	long	m_normalizednum;
	int		m_clusters;
	CString	m_savedfeaturefile;
	CString	m_savedcodebookfile;
	CString	m_savedindexfile;
	CString	m_db10;
	long	m_vectornumber;
	CString	m_readfeaturename;
	CString	m_readbookname;
	CString	m_readindexname;
	int		m_clustersused;
	long	m_retrievednum;
	CString	m_everinterrupted;
	CString	m_basedonnormalized;
	int		m_page;
	CString	m_status;
	CString	m_feedbackinfo;
	CString	m_otherinfo;
	//}}AFX_DATA

// Attributes
public:
	CVqRetrieveDoc* GetDocument();
	HGLOBAL Imageh[16];	
    unsigned char *m_RetrievalImageFile[16];//Retrieval image File
	void DisplayRetrieval();
    void PrintRetrieval(CDC* pDC, CPrintInfo* pInfo,int upordown);
	void PrintQuery(CDC* pDC, CPrintInfo* pInfo);
	int GetRetrievalImageFile(char m_sFileName[MAX_PATH],int type,int num);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVqRetrieveView)
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
	virtual ~CVqRetrieveView();
	int DisplayJpegFile(char m_sFileName[MAX_PATH],int num,int displayWidth,int displayHeight);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVqRetrieveView)
	afx_msg void OnKillfocusEditDb6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_bFileLost;
	int moved;
	unsigned char DisplayNumber;
	int SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth);
	int SuitableWidth(int Width,int Heigth,int DisplayWidth,int DisplayHeigth);
	void FeatureComputingRelatedWindowShow(int nCmdShow);
	void MoveToPositions();
	void DisplayInitialParameters();
};

#ifndef _DEBUG  // debug version in VqRetrieveView.cpp
inline CVqRetrieveDoc* CVqRetrieveView::GetDocument()
   { return (CVqRetrieveDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VQRETRIEVEVIEW_H__1DA28C88_0929_40E7_8C55_A8388337059F__INCLUDED_)
