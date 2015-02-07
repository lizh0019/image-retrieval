#if !defined(AFX_DIALOGEVALUATION_H__7FAC2CF8_B370_4B4F_9CAB_2D7214376FFC__INCLUDED_)
#define AFX_DIALOGEVALUATION_H__7FAC2CF8_B370_4B4F_9CAB_2D7214376FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEvaluation.h : header file
//
#include "CRetrieveMethod.h"
#include "DialogDrawCurve.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogEvaluation dialog
typedef struct tagTestReportsFileInfoStruct
{
   WORD m_wStructSize;
   FEATUREFILEINFO m_ffi;
   CODEBOOKFILEHEADER m_cfh;
   DWORD m_dwCluserSize[1024];
   BYTE m_bMethodNum;
   char m_cMethodName[10][16];
   WORD m_wQueriesEachClass;
   WORD m_wMin;
   WORD m_wMax;
   WORD m_wStep;
   DWORD m_dwTotalPointsNum;
   DWORD m_dwFileSize;
   DWORD m_dwOffset;
}TESTREPORTSHEADER,FAR *LPTESTREPORTSHEADER,*PTESTREPORTSHEADER;

typedef struct tagTestPointsStruct
{
    LONG m_lQueryNo;//if -1, denote average
	LONG m_lQueryName;//the real name,if -1 denote average
    WORD m_wReturnImages;
	float m_fTime; //in ms
	float m_fPrecision;
	float m_fRecall;
}TESTPOINTS,FAR *LPTESTPOINTS,*PTESTPOINTS;

class CDialogEvaluation : public CDialog
{
// Construction
public:
	CDialogEvaluation(CWnd* pParent = NULL);   // standard constructor
	CRetrieveMethod MyRetrieveMethod;
	FEATUREVECTOR m_vQueryFeatureVector;
	TESTREPORTSHEADER m_trh;
	LPTESTPOINTS m_tps;
	FEATUREFILEINFO m_ffi_fromfile;
	HGLOBAL m_hRFeatureVector,m_hTestReports;//handle for read feature vectors and Testpoints
	DWORD databaseSize;
	WORD featureDimension;
	double *database;
	double *means;
	double *variances;
	bool m_bFeatureFileOpened;
	bool m_bCodebookFileOpened;//Codebook file opened?
	bool m_bResultFileSaved;
	CString	m_savedresultfile;
	WORD *m_wIndex_r;
	CString m_sRetrievePath;
	CString m_readfeaturename;
	CString	m_readbookname;
	CODEBOOKFILEHEADER m_cfh_fromfile;//The header for codebook
	LPFEATUREVECTOR m_lpRFeatureVector; //Read-file's Feature vectors pointer
	LPCOMPONENTINFO m_lpRComponentInfo;//Read-file's Each dimension's mean and variance
	DWORD *m_dwNuminEachCluster_r;  //The number of vectors in each cluster
	double *m_dCodeword_r;//the codebook memopry
	double largeIntegerToDouble(LARGE_INTEGER i);
    void OpenFeatureDatabasefile(CString DataBaseFileName);
	void InitialStatus();
	void EnableWindows(BOOL b);
	void EnableWindows2(BOOL b);
	void CheckforUEEEKNNSinVQKNN();
	void GetMethodName(WORD Num);
	void ComputeRecallandPrecision(LPRETRIEVEDRESULT RetrievedResult,int queryclassnum,int returnnum,int numinclass,float *recall,float *precision);
	bool QueryGenerated;
	bool tested;
	int InsertingEEEKNNS(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD dimension,DWORD firstposi,DWORD lastsize,DWORD InsertVectorNum,DWORD clustersize,LPRETRIEVEDRESULT RetrievedResult);
	int UpdatingEEEKNNS(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD dimension,DWORD firstposi,DWORD VectorNumberTobeSearched,DWORD clustersize,LPRETRIEVEDRESULT RetrievedResult);
	int UpdatingEEEKNNSinVQKNNRetrieval(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,WORD m_clusterstosearch,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime);
	int UpdatingEEEKNNSinAllVQRetrieval(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime);
// Dialog Data
	//{{AFX_DATA(CDialogEvaluation)
	enum { IDD = IDD_DIALOG_EVALUATION };
	CListBox	m_resultlist;
	CString	m_dbpath;
	CString	m_bSorted;
	CString	m_everinterrupted;
	int		m_validnum_r;
	int		m_featuredimension;
	CString	m_clustered;
	int		m_clustersused;
	CString	m_standard;
	int		m_numineachclass;
	int		m_classes;
	int		m_dim1;
	int		m_dim2;
	int		m_dim3;
	int		m_dim4;
	int		m_dim5;
	CString	m_bkpath;
	CString	m_infonum;
	int		m_max;
	int		m_method;
	int		m_min;
	int		m_cluster;
	int		m_query;
	int		m_step;
	CString	m_testinfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEvaluation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogEvaluation)
	afx_msg void OnOpenDatabase();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnOpenCodebook();
	afx_msg void OnClear();
	afx_msg void OnResultsave();
	afx_msg void OnStarttest();
	afx_msg void OnRandomquery();
	afx_msg void OnDrawpr();
	afx_msg void OnDrawtime();
	afx_msg void OnSelchangeQueries();
	afx_msg void OnSelchangeMethod();
	afx_msg void OnSelchangeMax();
	afx_msg void OnSelchangeMin();
	afx_msg void OnSelchangeNumclustertosearch();
	afx_msg void OnSelchangeStep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEVALUATION_H__7FAC2CF8_B370_4B4F_9CAB_2D7214376FFC__INCLUDED_)
