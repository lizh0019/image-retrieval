// VqRetrieveDoc.h : interface of the CVqRetrieveDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VQRETRIEVEDOC_H__30E441BB_EA19_4C0F_8BCA_17AAB7F61EC7__INCLUDED_)
#define AFX_VQRETRIEVEDOC_H__30E441BB_EA19_4C0F_8BCA_17AAB7F61EC7__INCLUDED_
#include "CRetrieveMethod.h"
#include "DialogDisplayImage.h"
#include "DialogFeedback.h"
#include "jpeg.h"

// These six header files are for "_open", "_read" and "_write" functions 
//and string functions
#include <io.h> 
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVqRetrieveDoc : public CDocument
{
protected: // create from serialization only
	CVqRetrieveDoc();
	DECLARE_DYNCREATE(CVqRetrieveDoc)

// Attributes
public:

  // Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVqRetrieveDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//+++++++++For whole system+++++++
	//current directory
	char m_CurrentDirectory[_MAX_PATH];
	//The file headers for 24bits and 256gray-scale image
	unsigned char m_StandardBmpInfo[1078];//256gray
	unsigned char m_StandardBmpInfoc[54];//24bits
    //The initial successful flag
	bool Success;
    CRetrieveMethod MyRetrieveMethod;
    
	//++++++++For query menu++++++++++++
	//The global memory for query image
	HGLOBAL Imagehg,ImageFeature;	
    unsigned char *m_QueryImageFile;//Query image File
	BYTE *m_bQueryImageData;//RGB data for query image
	bool m_bQueryFileChanged;
	//Temp query image path
	CString m_sQueryImageFilePathName;
	//The query image info(including size,features and so on)
	FEATUREVECTOR m_vQueryFeatureVector;
	FEATUREVECTOR m_vQueryFeatureVectors[10];
	bool m_bFileOpened;//Query image opened?
    bool m_bQueryImageFeature;//Query image Feature computed?
	bool m_bQueryImageNormalized; ///Query image Feature Normalized
	int m_printflag;//which images to be print
	//Read Query image
	int ReadQueryImage(CString ImagePathName,PFEATUREVECTOR FeatureVector);
	void DestroyQueryMemory();
	
	
	//+++++++++for database menu++++++++++++++
	CString m_sDatabasePath; //The main path of the image database
	long int m_totalnum;//The total number of images
	long int m_validnum;//The  number of valid images
	///Get the number of possible images in the path
	bool GetApproximateImagesNumber(CString sPath,long int *number);
	////Judge if the files in ImagePathName can be opened
	bool IsImageValid(CString ImagePathName);
	////Get the number of 24bits or 8bits bmp and jpg images
	bool GetValidImagesNumber(CString sPath,long int *number);///
    bool m_bDatabaseOpened;//Database opened?
	bool m_bDatabaseChanged;//If the database path is changed?
	FEATUREFILEINFO m_ffi;//The Database feature file header info
	LPFEATUREVECTOR m_lpDFeatureVector; //Database Feature vectors pointer
	LPCOMPONENTINFO m_lpDComponentInfo;//Database Each dimension's mean and variance
	DWORD *m_dwNumberinCluster;
	WORD *m_wIndex;
	double *m_dCodeword;
	HGLOBAL m_hDFeatureVector;  //handle for database feature vectors
	void InitialFeatureFileInfo();//Intialize the database feature file header
	void DestroyDatabaseMemory(); ///Delete Database memory
	bool CreateDatabaseMemory();////Create memory for database
	bool FeatureVectorExtract(CString sPath); ///Compute the feature vectors for sPath
	bool m_bDatabaseFeatureComputing;//Database feature computing?
	bool m_bDatabaseFeatureInterrupted;//Database feature computation interrupted?
	bool m_bDatabaseFeatureComputed;//Database feature computation finished?
	long int m_extractednum;//The number of images extracted
	int m_clusters;//the number of clusters for feature space
	int ReadDatabaseImageandComputeFeatureVector(CString ImagePathName,PFEATUREVECTOR FeatureVector);
	int TotalFeatureVectorComputation(BYTE *ImageBytes,PFEATUREVECTOR FeatureVector,FEATUREFILEINFO m_Ffi);
	bool m_bDatabaseFeatureNormalized;//Database feature normalized? 
	long int m_normalizednum;//The number of images segmented
	CODEBOOKFILEHEADER m_cfh;//The header for codebook
	INDEXFILEHEADER m_ifh;//The header for index
	int m_clusteringbased;//The feature clustering based
	bool m_bDatabaseClustered;//Database feature space clustered?
	bool m_bFeatureFileSaved;//feature file saved
	bool m_bCodebookFileSaved;//codebook saved
	bool m_bIndexFileSaved;//index file saved
	CString m_savedfeaturefile;
    CString m_savedcodebookfile;
	CString m_savedindexfile;
	
	//+++++++++For Retrieval menu+++++++++
	long int m_validnum_r;//The  number of valid images
	bool m_bFeatureFileOpened;//Feature file opened?
	CString m_sRetrievePath;//CString	m_db10; the path
	bool m_bCodebookFileOpened;//Codebook file opened?
	bool m_bIndexFileOpened;//Index file opened?
	int m_iSimpleFeedBackMethod;//Simple Feedback methods.
	int m_iRetrieveMethod;//The retrieval methods
	int oldmethod;//The old method
	bool m_bRetrieving;//Is retrieving?
	bool m_bRetrieveInterrupt;//Is Interrupted?
	bool m_bRetrieved;//Is finished?
	FEATUREFILEINFO m_ffi_fromfile;//The Read feature file header info
	CODEBOOKFILEHEADER m_cfh_fromfile;//The header for codebook
	INDEXFILEHEADER m_ifh_fromfile;//The header for index
	LPFEATUREVECTOR m_lpRFeatureVector; //Read-file's Feature vectors pointer
	LPCOMPONENTINFO m_lpRComponentInfo;//Read-file's Each dimension's mean and variance
	WORD *m_wIndex_r;  //The index memory
	double *m_dCodeword_r;//the codebook memopry
	HGLOBAL m_hRFeatureVector,m_hResult;  //handle for read feature vectors
	LPRETRIEVEDRESULT RetrievedResult;//The index of retrieved result
	DWORD *SearchIndexList;
	HGLOBAL hsil;
	void DestroyRetrievalMemory();///Delete Retrieval memory
    CString m_everinterrupted;
	CString	m_readfeaturename;
	CString	m_readbookname;
	CString	m_readindexname;
	CString m_basedonnormalized;
	int	m_clustersused;
	long m_retrievednum;
	int FullSearchRetrieveMethod();
	int UpdatingFullSearchRetrieveMethod();
    int EKNNSRetrieveMethod();
    int IEKNNSURetrieveMethod();
    int IEKNNSBRetrieveMethod();
	CString m_sCostAllTime;
	CString m_sRetrieveTime;  //Retrieval time
	bool m_bSorted;  //The flag of sorted database
	clock_t time1,time2; // 
	double timecost;
	float weights[11];//for memory feedback
	int m_T1,m_T2;//for memory feedback
	int m_Iterations;//for memory feedback
	int processedpages;
		
	//+++++++++++++++for Feedback+++++++++++++
	bool m_bFeedBack;                    //是否处于反馈中
	CDialogFeedback MyDialogRetrieveBack;   // 反馈界面
	
	//+++++++++++++++for display+++++++++++++++++
	bool m_bRetrieveDisplay;   //If can display results
	int m_page_setting;//The user setted page info
	int m_page_setting_saved;//The latest setted page info
	int m_displaypage;  //The apge to be displayed
	unsigned char m_uDisplayNumber;  //Display image number for current page 0-16
	void DisplayPage(int page); //prepare for displaying current page
	FEATUREVECTOR m_cDisplayFeatureVector[16]; //The feature vectors for display
	double m_dDisplayFileDistance[16];     //The distances of displayed images
	FEATUREVECTOR GetDisplayFeatureVector(unsigned char i);
	CString GetDisplayFileName(unsigned char i);
	float GetDistance(unsigned char i);
	CDialogDisplayImage myDisplayImage;   ///显示的界面
	virtual ~CVqRetrieveDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CString lastpathname,lastpathname1,lastpathname2;
// Generated message map functions
protected:
	//{{AFX_MSG(CVqRetrieveDoc)
	afx_msg void OnQueryFeaturecompute();
	afx_msg void OnQueryFeaturenormalization();
	afx_msg void OnPrintQuery();
	afx_msg void OnPrintPagewithquery();
	afx_msg void OnPrintPagenoquery();
	afx_msg void OnDatabasePath();      
	afx_msg void OnRetrieveFeaturefile();
	afx_msg void OnRetrieveNormal();
	afx_msg void OnRetrieveVqonlynnc();
	afx_msg void OnRetrieveVqonlyknncs();
	afx_msg void OnRetrieveVqallclusters();
	afx_msg void OnRetrieveBest();
	afx_msg void OnStaticquery();
	afx_msg void OnStaticretrieval10();
	afx_msg void OnStaticretrieval11();
	afx_msg void OnStaticretrieval12();
	afx_msg void OnStaticretrieval13();
	afx_msg void OnStaticretrieval14();
	afx_msg void OnStaticretrieval15();
	afx_msg void OnStaticretrieval16();
	afx_msg void OnStaticretrieval2();
	afx_msg void OnStaticretrieval3();
	afx_msg void OnStaticretrieval4();
	afx_msg void OnStaticretrieval5();
	afx_msg void OnStaticretrieval6();
	afx_msg void OnStaticretrieval7();
	afx_msg void OnStaticretrieval8();
	afx_msg void OnStaticretrieval9();
	afx_msg void OnChangeasquery();
	afx_msg void OnUpdateQueryFeaturecompute(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQueryFeaturenormalization(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrintQuery(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrintPagewithquery(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrintPagenoquery(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabasePath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRetrieveFeaturefile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRetrieveNormal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRetrieveVqonlynnc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRetrieveVqonlyknncs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRetrieveVqallclusters(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeedback(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpFinder(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppAbout(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseFeatureselection();
	afx_msg void OnUpdateDatabaseFeatureselection(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveFeatureselected();
	afx_msg void OnUpdateRetrieveFeatureselected(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseFeaturecompute();
	afx_msg void OnUpdateDatabaseFeaturecompute(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseStop();
	afx_msg void OnUpdateDatabaseStop(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseCodewordssave();
	afx_msg void OnUpdateDatabaseCodewordssave(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseFeaturenormalization();
	afx_msg void OnUpdateDatabaseFeaturenormalization(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseFeaturesave();
	afx_msg void OnUpdateDatabaseFeaturesave(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseIndexsave();
	afx_msg void OnUpdateDatabaseIndexsave(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveClusteringbook();
	afx_msg void OnUpdateRetrieveClusteringbook(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveFeedbacknomemory();
	afx_msg void OnUpdateRetrieveFeedbacknomemory(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveFeedbackwithmemory();
	afx_msg void OnUpdateRetrieveFeedbackwithmemory(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveStart();
	afx_msg void OnUpdateRetrieveStart(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveStop();
	afx_msg void OnUpdateRetrieveStop(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveIndex();
	afx_msg void OnUpdateRetrieveIndex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRetrieveBest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisplayFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisplayLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisplayPrevious(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisplayNext(CCmdUI* pCmdUI);
	afx_msg void OnEvaluationPrecisionwithtime();
	afx_msg void OnUpdateEvaluationPrecisionwithtime(CCmdUI* pCmdUI);
	afx_msg void OnEvaluationRecallwithtime();
	afx_msg void OnUpdateEvaluationRecallwithtime(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme1();
	afx_msg void OnUpdateFeedbackScheme1(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme2();
	afx_msg void OnUpdateFeedbackScheme2(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme3();
	afx_msg void OnUpdateFeedbackScheme3(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme4();
	afx_msg void OnUpdateFeedbackScheme4(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme5();
	afx_msg void OnUpdateFeedbackScheme5(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme6();
	afx_msg void OnUpdateFeedbackScheme6(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme7();
	afx_msg void OnUpdateFeedbackScheme7(CCmdUI* pCmdUI);
	afx_msg void OnFeedbackScheme8();
	afx_msg void OnUpdateFeedbackScheme8(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseNfeaturespacevq();
	afx_msg void OnDatabaseOfeaturespacevq();
	afx_msg void OnUpdateDatabaseNfeaturespacevq(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseOfeaturespacevq(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveUpdatingfs();
	afx_msg void OnUpdateRetrieveUpdatingfs(CCmdUI* pCmdUI);
	afx_msg void OnDisplayFirst();
	afx_msg void OnDisplayLast();
	afx_msg void OnDisplayPrevious();
	afx_msg void OnDisplayNext();
	afx_msg void OnDoubleclickedRegionQuery();
	afx_msg void OnDoubleclickedRegionRetrieval1();
	afx_msg void OnDoubleclickedRegionRetrieval10();
	afx_msg void OnDoubleclickedRegionRetrieval11();
	afx_msg void OnDoubleclickedRegionRetrieval12();
	afx_msg void OnDoubleclickedRegionRetrieval13();
	afx_msg void OnDoubleclickedRegionRetrieval14();
	afx_msg void OnDoubleclickedRegionRetrieval15();
	afx_msg void OnDoubleclickedRegionRetrieval16();
	afx_msg void OnDoubleclickedRegionRetrieval2();
	afx_msg void OnDoubleclickedRegionRetrieval3();
	afx_msg void OnDoubleclickedRegionRetrieval4();
	afx_msg void OnDoubleclickedRegionRetrieval5();
	afx_msg void OnDoubleclickedRegionRetrieval6();
	afx_msg void OnDoubleclickedRegionRetrieval7();
	afx_msg void OnDoubleclickedRegionRetrieval8();
	afx_msg void OnDoubleclickedRegionRetrieval9();
	afx_msg void OnStaticretrieval1();
	afx_msg void OnRetrieveSorting();
	afx_msg void OnUpdateRetrieveSorting(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages1();
	afx_msg void OnUpdateRetrievePages1(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages10();
	afx_msg void OnUpdateRetrievePages10(CCmdUI* pCmdUI);
	afx_msg void OnRETRIEVEPAGES1AND1Image();
	afx_msg void OnUpdateRETRIEVEPAGES1AND1Image(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages2();
	afx_msg void OnUpdateRetrievePages2(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages3();
	afx_msg void OnUpdateRetrievePages3(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages4();
	afx_msg void OnUpdateRetrievePages4(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages5();
	afx_msg void OnUpdateRetrievePages5(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages6();
	afx_msg void OnUpdateRetrievePages6(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages7();
	afx_msg void OnUpdateRetrievePages7(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages8();
	afx_msg void OnUpdateRetrievePages8(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePages9();
	afx_msg void OnUpdateRetrievePages9(CCmdUI* pCmdUI);
	afx_msg void OnRetrievePagesall();
	afx_msg void OnUpdateRetrievePagesall(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveIeknnsback();
	afx_msg void OnUpdateRetrieveIeknnsback(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveIeknnsuser();
	afx_msg void OnUpdateRetrieveIeknnsuser(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveEknns();
	afx_msg void OnUpdateRetrieveEknns(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	MSG Mymsg;
    void QueryStatusIntial();
	void DatabaseStatusInitial();
	void RetrievalStatusIntial();
    void OpenStandardBMPHeader();
	void FeatureVectorCopy(PFEATUREVECTOR FeatureVectorA,PFEATUREVECTOR FeatureVectorB,int style);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VQRETRIEVEDOC_H__30E441BB_EA19_4C0F_8BCA_17AAB7F61EC7__INCLUDED_)
////////
//////////////////////////////////////////////////////////////////////////
//this is a ceshiban 1
