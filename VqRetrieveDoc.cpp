// VqRetrieveDoc.cpp : implementation of the CVqRetrieveDoc class
//
#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogDisplayImage.h"
#include "VqRetrieveDoc.h"
#include "DialogDatabase.h"
#include "DialogFeatureSelection.h"
#include "DialogFeedbakWithMemory.h"
#include "DialogEvaluation.h"
#include "SourceDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveDoc

IMPLEMENT_DYNCREATE(CVqRetrieveDoc, CDocument)

BEGIN_MESSAGE_MAP(CVqRetrieveDoc, CDocument)
	//{{AFX_MSG_MAP(CVqRetrieveDoc)
	ON_COMMAND(ID_QUERY_FEATURECOMPUTE, OnQueryFeaturecompute)
	ON_COMMAND(ID_QUERY_FEATURENORMALIZATION, OnQueryFeaturenormalization)
	ON_COMMAND(ID_PRINT_QUERY, OnPrintQuery)
	ON_COMMAND(ID_PRINT_PAGEWITHQUERY, OnPrintPagewithquery)
	ON_COMMAND(ID_PRINT_PAGENOQUERY, OnPrintPagenoquery)
	ON_COMMAND(ID_DATABASE_PATH, OnDatabasePath)
	ON_COMMAND(ID_RETRIEVE_FEATUREFILE, OnRetrieveFeaturefile)
	ON_COMMAND(ID_RETRIEVE_NORMAL, OnRetrieveNormal)
	ON_COMMAND(ID_RETRIEVE_VQONLYNNC, OnRetrieveVqonlynnc)
	ON_COMMAND(ID_RETRIEVE_VQONLYKNNCS, OnRetrieveVqonlyknncs)
	ON_COMMAND(ID_RETRIEVE_VQALLCLUSTERS, OnRetrieveVqallclusters)
	ON_BN_CLICKED(IDC_STATICQUERY, OnStaticquery)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL10, OnStaticretrieval10)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL11, OnStaticretrieval11)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL12, OnStaticretrieval12)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL13, OnStaticretrieval13)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL14, OnStaticretrieval14)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL15, OnStaticretrieval15)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL16, OnStaticretrieval16)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL2, OnStaticretrieval2)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL3, OnStaticretrieval3)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL4, OnStaticretrieval4)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL5, OnStaticretrieval5)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL6, OnStaticretrieval6)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL7, OnStaticretrieval7)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL8, OnStaticretrieval8)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL9, OnStaticretrieval9)
	ON_COMMAND(ID_CHANGEASQUERY, OnChangeasquery)
	ON_UPDATE_COMMAND_UI(ID_QUERY_FEATURECOMPUTE, OnUpdateQueryFeaturecompute)
	ON_UPDATE_COMMAND_UI(ID_QUERY_FEATURENORMALIZATION, OnUpdateQueryFeaturenormalization)
	ON_UPDATE_COMMAND_UI(ID_PRINT_QUERY, OnUpdatePrintQuery)
	ON_UPDATE_COMMAND_UI(ID_PRINT_PAGEWITHQUERY, OnUpdatePrintPagewithquery)
	ON_UPDATE_COMMAND_UI(ID_PRINT_PAGENOQUERY, OnUpdatePrintPagenoquery)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_PATH, OnUpdateDatabasePath)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_FEATUREFILE, OnUpdateRetrieveFeaturefile)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_NORMAL, OnUpdateRetrieveNormal)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_VQONLYNNC, OnUpdateRetrieveVqonlynnc)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_VQONLYKNNCS, OnUpdateRetrieveVqonlyknncs)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_VQALLCLUSTERS, OnUpdateRetrieveVqallclusters)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_UPDATE_COMMAND_UI(ID_HELP, OnUpdateHelp)
	ON_UPDATE_COMMAND_UI(ID_HELP_FINDER, OnUpdateHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_APP_ABOUT, OnUpdateAppAbout)
	ON_COMMAND(ID_DATABASE_FEATURESELECTION, OnDatabaseFeatureselection)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_FEATURESELECTION, OnUpdateDatabaseFeatureselection)
	ON_COMMAND(ID_RETRIEVE_FEATURESELECTED, OnRetrieveFeatureselected)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_FEATURESELECTED, OnUpdateRetrieveFeatureselected)
	ON_COMMAND(ID_DATABASE_FEATURECOMPUTE, OnDatabaseFeaturecompute)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_FEATURECOMPUTE, OnUpdateDatabaseFeaturecompute)
	ON_COMMAND(ID_DATABASE_STOP, OnDatabaseStop)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_STOP, OnUpdateDatabaseStop)
	ON_COMMAND(ID_DATABASE_CODEWORDSSAVE, OnDatabaseCodewordssave)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_CODEWORDSSAVE, OnUpdateDatabaseCodewordssave)
	ON_COMMAND(ID_DATABASE_FEATURENORMALIZATION, OnDatabaseFeaturenormalization)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_FEATURENORMALIZATION, OnUpdateDatabaseFeaturenormalization)
	ON_COMMAND(ID_DATABASE_FEATURESAVE, OnDatabaseFeaturesave)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_FEATURESAVE, OnUpdateDatabaseFeaturesave)
	ON_COMMAND(ID_DATABASE_VQFEATURESAVE, OnDatabaseVQFeaturesave)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_VQFEATURESAVE, OnUpdateDatabaseVQFeaturesave)
	ON_COMMAND(ID_RETRIEVE_CLUSTERINGBOOK, OnRetrieveClusteringbook)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_CLUSTERINGBOOK, OnUpdateRetrieveClusteringbook)
	ON_COMMAND(ID_RETRIEVE_FEEDBACKNOMEMORY, OnRetrieveFeedbacknomemory)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_FEEDBACKNOMEMORY, OnUpdateRetrieveFeedbacknomemory)
	ON_COMMAND(ID_RETRIEVE_FEEDBACKWITHMEMORY, OnRetrieveFeedbackwithmemory)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_FEEDBACKWITHMEMORY, OnUpdateRetrieveFeedbackwithmemory)
	ON_COMMAND(ID_RETRIEVE_START, OnRetrieveStart)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_START, OnUpdateRetrieveStart)
	ON_COMMAND(ID_RETRIEVE_STOP, OnRetrieveStop)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_STOP, OnUpdateRetrieveStop)
	ON_COMMAND(ID_RETRIEVE_VQFEATUREFILE, OnRetrieveVQFeatureFile)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_VQFEATUREFILE, OnUpdateRetrieveVQFeatureFile)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_FIRST, OnUpdateDisplayFirst)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_LAST, OnUpdateDisplayLast)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_PREVIOUS, OnUpdateDisplayPrevious)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_NEXT, OnUpdateDisplayNext)
	ON_COMMAND(ID_FEEDBACK_SCHEME1, OnFeedbackScheme1)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME1, OnUpdateFeedbackScheme1)
	ON_COMMAND(ID_FEEDBACK_SCHEME2, OnFeedbackScheme2)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME2, OnUpdateFeedbackScheme2)
	ON_COMMAND(ID_FEEDBACK_SCHEME3, OnFeedbackScheme3)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME3, OnUpdateFeedbackScheme3)
	ON_COMMAND(ID_FEEDBACK_SCHEME4, OnFeedbackScheme4)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME4, OnUpdateFeedbackScheme4)
	ON_COMMAND(ID_FEEDBACK_SCHEME5, OnFeedbackScheme5)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME5, OnUpdateFeedbackScheme5)
	ON_COMMAND(ID_FEEDBACK_SCHEME6, OnFeedbackScheme6)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME6, OnUpdateFeedbackScheme6)
	ON_COMMAND(ID_FEEDBACK_SCHEME7, OnFeedbackScheme7)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME7, OnUpdateFeedbackScheme7)
	ON_COMMAND(ID_FEEDBACK_SCHEME8, OnFeedbackScheme8)
	ON_UPDATE_COMMAND_UI(ID_FEEDBACK_SCHEME8, OnUpdateFeedbackScheme8)
	ON_COMMAND(ID_DATABASE_NFEATURESPACEVQ, OnDatabaseNfeaturespacevq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_NFEATURESPACEVQ, OnUpdateDatabaseNfeaturespacevq)
	ON_COMMAND(ID_RETRIEVE_UPDATINGFS, OnRetrieveUpdatingfs)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_UPDATINGFS, OnUpdateRetrieveUpdatingfs)
	ON_COMMAND(ID_DISPLAY_FIRST, OnDisplayFirst)
	ON_COMMAND(ID_DISPLAY_LAST, OnDisplayLast)
	ON_COMMAND(ID_DISPLAY_PREVIOUS, OnDisplayPrevious)
	ON_COMMAND(ID_DISPLAY_NEXT, OnDisplayNext)
	ON_BN_DOUBLECLICKED(IDC_REGION_QUERY, OnDoubleclickedRegionQuery)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL1, OnDoubleclickedRegionRetrieval1)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL10, OnDoubleclickedRegionRetrieval10)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL11, OnDoubleclickedRegionRetrieval11)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL12, OnDoubleclickedRegionRetrieval12)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL13, OnDoubleclickedRegionRetrieval13)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL14, OnDoubleclickedRegionRetrieval14)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL15, OnDoubleclickedRegionRetrieval15)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL16, OnDoubleclickedRegionRetrieval16)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL2, OnDoubleclickedRegionRetrieval2)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL3, OnDoubleclickedRegionRetrieval3)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL4, OnDoubleclickedRegionRetrieval4)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL5, OnDoubleclickedRegionRetrieval5)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL6, OnDoubleclickedRegionRetrieval6)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL7, OnDoubleclickedRegionRetrieval7)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL8, OnDoubleclickedRegionRetrieval8)
	ON_BN_DOUBLECLICKED(IDC_REGION_RETRIEVAL9, OnDoubleclickedRegionRetrieval9)
	ON_BN_CLICKED(IDC_STATICRETRIEVAL1, OnStaticretrieval1)
	ON_COMMAND(ID_RETRIEVE_PAGES1, OnRetrievePages1)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES1, OnUpdateRetrievePages1)
	ON_COMMAND(ID_RETRIEVE_PAGES10, OnRetrievePages10)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES10, OnUpdateRetrievePages10)
	ON_COMMAND(ID_RETRIEVE_PAGES1AND1Image, OnRETRIEVEPAGES1AND1Image)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES1AND1Image, OnUpdateRETRIEVEPAGES1AND1Image)
	ON_COMMAND(ID_RETRIEVE_PAGES2, OnRetrievePages2)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES2, OnUpdateRetrievePages2)
	ON_COMMAND(ID_RETRIEVE_PAGES3, OnRetrievePages3)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES3, OnUpdateRetrievePages3)
	ON_COMMAND(ID_RETRIEVE_PAGES4, OnRetrievePages4)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES4, OnUpdateRetrievePages4)
	ON_COMMAND(ID_RETRIEVE_PAGES5, OnRetrievePages5)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES5, OnUpdateRetrievePages5)
	ON_COMMAND(ID_RETRIEVE_PAGES6, OnRetrievePages6)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES6, OnUpdateRetrievePages6)
	ON_COMMAND(ID_RETRIEVE_PAGES7, OnRetrievePages7)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES7, OnUpdateRetrievePages7)
	ON_COMMAND(ID_RETRIEVE_PAGES8, OnRetrievePages8)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES8, OnUpdateRetrievePages8)
	ON_COMMAND(ID_RETRIEVE_PAGES9, OnRetrievePages9)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES9, OnUpdateRetrievePages9)
	ON_COMMAND(ID_RETRIEVE_PAGESALL, OnRetrievePagesall)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGESALL, OnUpdateRetrievePagesall)
	ON_COMMAND(ID_RETRIEVE_IEKNNSBACK, OnRetrieveIeknnsback)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_IEKNNSBACK, OnUpdateRetrieveIeknnsback)
	ON_COMMAND(ID_RETRIEVE_IEKNNSUSER, OnRetrieveIeknnsuser)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_IEKNNSUSER, OnUpdateRetrieveIeknnsuser)
	ON_COMMAND(ID_RETRIEVE_EKNNS, OnRetrieveEknns)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_EKNNS, OnUpdateRetrieveEknns)
	ON_COMMAND(ID_RETRIEVE_IEEKNNSBACK, OnRetrieveIeeknnsback)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_IEEKNNSBACK, OnUpdateRetrieveIeeknnsback)
	ON_COMMAND(ID_RETRIEVE_IEEKNNSUSER, OnRetrieveIeeknnsuser)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_IEEKNNSUSER, OnUpdateRetrieveIeeknnsuser)
	ON_COMMAND(ID_RETRIEVE_EEKNNS, OnRetrieveEeknns)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_EEKNNS, OnUpdateRetrieveEeknns)
	ON_COMMAND(ID_EVALUATION, OnEvaluation)
	ON_UPDATE_COMMAND_UI(ID_EVALUATION, OnUpdateEvaluation)
	ON_COMMAND(ID_DATABASE_SORTING, OnDatabaseSorting)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_SORTING, OnUpdateDatabaseSorting)
	ON_COMMAND(ID_DATABASE_CLUSTERSORTING, OnDatabaseClustersorting)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_CLUSTERSORTING, OnUpdateDatabaseClustersorting)
	ON_COMMAND(ID_RETRIEVE_PAGES15, OnRetrievePages15)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES15, OnUpdateRetrievePages15)
	ON_COMMAND(ID_RETRIEVE_PAGES20, OnRetrievePages20)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES20, OnUpdateRetrievePages20)
	ON_COMMAND(ID_RETRIEVE_PAGES25, OnRetrievePages25)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_PAGES25, OnUpdateRetrievePages25)
	ON_COMMAND(ID_RETRIEVE_IEEEKNNSBACK, OnRetrieveIeeeknnsback)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_IEEEKNNSBACK, OnUpdateRetrieveIeeeknnsback)
	ON_COMMAND(ID_RETRIEVE_IEEEKNNSUSER, OnRetrieveIeeeknnsuser)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_IEEEKNNSUSER, OnUpdateRetrieveIeeeknnsuser)
	ON_COMMAND(ID_RETRIEVE_EEEKNNS, OnRetrieveEeeknns)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_EEEKNNS, OnUpdateRetrieveEeeknns)
	ON_COMMAND(ID_DATABASE_READFROMFILE, OnDatabaseReadfromfile)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_READFROMFILE, OnUpdateDatabaseReadfromfile)
	ON_COMMAND(ID_DATABASE_CODEBOOKFORDCTVQ, OnDatabaseCodebookfordctvq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_CODEBOOKFORDCTVQ, OnUpdateDatabaseCodebookfordctvq)
	ON_COMMAND(ID_DATABASE_CODEBOOKFORMRVQ, OnDatabaseCodebookformrvq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_CODEBOOKFORMRVQ, OnUpdateDatabaseCodebookformrvq)
	ON_COMMAND(ID_DATABASE_CODEBOOKFORMSVQ, OnDatabaseCodebookformsvq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_CODEBOOKFORMSVQ, OnUpdateDatabaseCodebookformsvq)
	ON_COMMAND(ID_DATABASE_CODEBOOKFORVQ, OnDatabaseCodebookforvq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_CODEBOOKFORVQ, OnUpdateDatabaseCodebookforvq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveDoc construction/destruction

CVqRetrieveDoc::CVqRetrieveDoc()
{
	//+++++++++For Query menu+++++++++
	m_printflag=0;//Default to print query image
	QueryStatusIntial();
	//+++++++++for Database menu+++++++++
	DatabaseStatusInitial();
	InitialFeatureFileInfo();
	//for retrieve menu
	RetrievalStatusIntial();
	//for system
	GetCurrentDirectory(_MAX_PATH,m_CurrentDirectory);
	OpenStandardBMPHeader();


	//////=====Inital Variables for Design======/////////////  	
    //The design image number is set to be 0;
	m_DesignImagesNumber=0;
	//The image filenames set to be null string
	int i;
	for(i=0;i<16;i++)
	{
	  strcpy(m_DesignFileNames[i],"");
	}
	

	
	
	//The default design MSE 
//	cbdi.MSE=0.0;
	//The default design PSNR 
//	cbdi.PSNR=0.0;
	//The default design time
//	cbdi.Time=0.0;
	//The default design iteration 
//	cbdi.Iterations=0;

//	m_FeatureMask=1;
//	m_FeatureWeights[0]=100;
//	m_FeatureWeights[1]=0;
//	m_FeatureWeights[2]=0;
//	m_FeatureWeights[3]=0;
//	m_FeatureWeights[4]=0;
//	m_FeatureWeights[5]=0;
//	m_FeatureWeights[6]=0;
//	m_FeatureWeights[7]=0;
}

CVqRetrieveDoc::~CVqRetrieveDoc()
{
   DestroyDatabaseMemory(); ///Destroy database memory
   DestroyRetrievalMemory(); ///Destroy retrieval memory
   DestroyQueryMemory();//Destroy Query memory

}

BOOL CVqRetrieveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()||Success==FALSE)
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveDoc serialization

void CVqRetrieveDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

//The Overloaded function Open Query image
BOOL CVqRetrieveDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
 	 //If retrieving and computing, remain last query image
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
		return false;
	//If we fail to open file, remain last query image
	if(!CDocument::OnOpenDocument(lpszPathName)) 
 	{	
 		UpdateAllViews(NULL);
 		MessageBox(NULL,"We Cannot Open the File You Choose!","Error",MB_ICONSTOP|MB_OK);
 		return FALSE;
 	}
 	//If the same image is opened, just jump over
	if(m_sQueryImageFilePathName==lpszPathName) 
 		return false;
	//the initial status
 	QueryStatusIntial();
	if(ReadQueryImage((CString)lpszPathName,&m_vQueryFeatureVector)<0)   //If file open error
 	{
 		UpdateAllViews(NULL);
 		MessageBox(NULL,"We Cann't open or deal with the File You Choose!","Error",MB_OK|MB_ICONSTOP);
 		return false;
 	}
	m_bFileOpened=true;
	m_bQueryFileChanged=true;
 	m_sQueryImageFilePathName=lpszPathName;//Get the valid new query image filename
    UpdateAllViews(NULL);
    return true;//Open success	
}

BOOL CVqRetrieveDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)return false;	
	if((m_bFeatureFileSaved==false&&m_bDatabaseFeatureNormalized==true)||(m_bCodebookFileSaved==false&&m_bDatabaseClustered==true)||(m_bVQFeatureFileSaved==false&&m_bDatabaseClustered==true))
	{
      if(::AfxMessageBox("The database related file hasn't been saved up to now, do you want to save the related file,OK?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	  {
	    if(m_bFeatureFileSaved==false)
		{
		  OnDatabaseFeaturesave();
		  m_bFeatureFileSaved=true;
		}
		if(m_bCodebookFileSaved==false)
		{
		  OnDatabaseCodewordssave();
		  m_bCodebookFileSaved=true;
		}
		if(m_bVQFeatureFileSaved==false)
		{
		  OnDatabaseVQFeaturesave();
		  m_bVQFeatureFileSaved=true;
		}
		return false;
	  } 
	}
	return CDocument::CanCloseFrame(pFrame);
}

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveDoc diagnostics

#ifdef _DEBUG
void CVqRetrieveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVqRetrieveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveDoc commands
void CVqRetrieveDoc::OnQueryFeaturecompute() 
{
	// TODO: Add your command handler code here
	//If feature has been computed ask if continue?
	if(m_bQueryImageFeature==true&&::AfxMessageBox("The query image hasn't been changed, do you want to recompute the feature file,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
	  return;
    if(m_ffi_fromfile.m_bWithFeature1_OF==TRUE)
	{
	    if(OpenCodeBooks()!=0)return;
	}
	if(m_ffi_fromfile.m_bWithFeature2_OF==TRUE)
	{
	    if(OpenCodeBooks0()!=0)return;
	}
	if(m_ffi_fromfile.m_bWithFeature3_OF==TRUE)
	{
	    if(OpenCodeBooks1()!=0)return;
	}
	if(m_ffi_fromfile.m_bWithFeature4_OF==TRUE)
	{
	    if(OpenCodeBooks2()!=0)return;
	}
	m_bRetrieveDisplay=false;  //Clear the previous retrieval results display flag
 	//m_bFeedBack=false;         //Clear the feedback flag
	m_bRetrieveInterrupt=false;//
	m_bRetrieving=false;//
	m_bRetrieved=false;//	
	m_bQueryImageFeature=false;
	m_Iterations=0;//The simple feedback iterations	
	UpdateAllViews(NULL);
    ImageFeature=NULL;
	ImageFeature=GlobalAlloc(GMEM_FIXED,m_ffi_fromfile.m_wTotalDimensions*sizeof(double)*22);
	if(ImageFeature==NULL)
	{
	  MessageBox(NULL,"Memory not enough","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_vQueryFeatureVector.m_dOriginalFeature=(double *)ImageFeature;
	m_vQueryFeatureVector.m_dNormalizedFeature=m_vQueryFeatureVector.m_dOriginalFeature+m_ffi_fromfile.m_wTotalDimensions;
	int i;
	for(i=0;i<10;i++)
	  m_vQueryFeatureVectors[i].m_dOriginalFeature=m_vQueryFeatureVector.m_dNormalizedFeature+m_ffi_fromfile.m_wTotalDimensions*(i+1);
	for(i=0;i<10;i++)
	  m_vQueryFeatureVectors[i].m_dNormalizedFeature=m_vQueryFeatureVectors[9].m_dOriginalFeature+m_ffi_fromfile.m_wTotalDimensions*(i+1);
	BeginWaitCursor();
	if(TotalFeatureVectorComputation(m_bQueryImageData,&m_vQueryFeatureVector,m_ffi_fromfile)!=0)
	{
		MessageBox(NULL,"Query Feature Computation Error","Error",MB_OK|MB_ICONINFORMATION); //extraction now
	}
	m_bQueryImageFeature=true;
	UpdateAllViews(NULL);
	EndWaitCursor();
}

void CVqRetrieveDoc::OnQueryFeaturenormalization() 
{
	// TODO: Add your command handler code here
	if(m_bQueryImageNormalized==true&&::AfxMessageBox("The Query image hasn't been changed, do you want to renormalizing the feature vector,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
	return;
	WORD dimensions[8];
    dimensions[0]=m_ffi_fromfile.m_wDimension_CF;
	dimensions[1]=m_ffi_fromfile.m_wDimension_IF;
	dimensions[2]=m_ffi_fromfile.m_wDimension_TF;
	dimensions[3]=m_ffi_fromfile.m_wDimension_SF;
	if(m_ffi_fromfile.m_bWithFeature1_OF==TRUE)
	  dimensions[4]=OtherDim[0];
	else
	  dimensions[4]=0;
	if(m_ffi_fromfile.m_bWithFeature2_OF==TRUE)
	  dimensions[5]=OtherDim[1];
	else
	  dimensions[5]=0;
	if(m_ffi_fromfile.m_bWithFeature3_OF==TRUE)
	  dimensions[6]=OtherDim[2];
	else
	  dimensions[6]=0;
	if(m_ffi_fromfile.m_bWithFeature4_OF==TRUE)
	  dimensions[7]=OtherDim[3];
    else
	  dimensions[7]=0;	
 	m_bRetrieveDisplay=false;  //Clear the previous retrieval results display flag
 	//m_bFeedBack=false;         //Clear the feedback flag
	m_bRetrieveInterrupt=false;//
	m_bRetrieving=false;//
	m_bRetrieved=false;//
	UpdateAllViews(NULL);
	BeginWaitCursor();
	m_bQueryImageNormalized=false;
    memcpy(m_vQueryFeatureVector.m_dNormalizedFeature,m_vQueryFeatureVector.m_dOriginalFeature,m_ffi_fromfile.m_wTotalDimensions*sizeof(double));
	if(MyRetrieveMethod.QueryFeatureNormalization(&m_vQueryFeatureVector,m_ffi_fromfile.m_wTotalDimensions,dimensions,m_ffi_fromfile.m_wWeights,m_lpRComponentInfo)<0)
	{
	  MessageBox(NULL,"Query Feature Vector Normalization Error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_bQueryImageNormalized=true;
	FeatureVectorCopy(&m_vQueryFeatureVectors[0],&m_vQueryFeatureVector,1);
	UpdateAllViews(NULL);
	EndWaitCursor();
}

void CVqRetrieveDoc::OnPrintQuery() 
{
	// TODO: Add your command handler code here
	m_printflag=0;
}
void CVqRetrieveDoc::OnPrintPagewithquery() 
{
	// TODO: Add your command handler code here
	m_printflag=1;	
}
void CVqRetrieveDoc::OnPrintPagenoquery() 
{
	// TODO: Add your command handler code here
	m_printflag=2;
}


//Select Database Path,judge the total number of images
//Judge the valid number of 8/24bits bmp/jpg images
void CVqRetrieveDoc::OnDatabasePath() 
{
	// TODO: Add your command handler code here
	CDialogDatabase myDialogDatabase;//Create Database Dialog
	myDialogDatabase.m_sPath=m_sDatabasePath;//The old directory
	if(myDialogDatabase.DoModal()!=IDOK)//If the path selection cancled
	{
		m_bDatabaseChanged=false;//no changed, remain the old path
		return;
	}
	if(m_sDatabasePath==myDialogDatabase.m_sPath)//If the path isn't changed
	{
	    m_bDatabaseChanged=false;//no changed, remain the old path
	    return;
	}
	DatabaseStatusInitial();
	m_sDatabasePath=myDialogDatabase.m_sPath;
	BeginWaitCursor();
	//Get the image number by file ext
	//If overflowed
	if(GetApproximateImagesNumber(m_sDatabasePath,&m_totalnum)==false)
	{
	  m_totalnum=0;
	  MessageBox(NULL,"The number of images has overflowed in the selected path!","Error",MB_OK|MB_ICONSTOP);
	  m_sDatabasePath="No image database is selected!";
	  UpdateAllViews(NULL);
	  EndWaitCursor();
	  return;
	}
	//If there are no images
	if(m_totalnum==0)
	{
	  m_sDatabasePath="No image database is selected!";
	  MessageBox(NULL,"No image is in the selected path!","Error",MB_OK|MB_ICONSTOP);
	  UpdateAllViews(NULL);
	  EndWaitCursor();
	  return;
	}
	///Obtain the exact image number
	if(GetValidImagesNumber(m_sDatabasePath,&m_validnum)==false)
	{
	  m_validnum=MAX_IMAGE_NUMBER;
	  MessageBox(NULL,"The number of images in the selected path is larger than 500000, this sytem can only deal with first 500000 images!","Information",MB_OK|MB_ICONINFORMATION);
	  UpdateAllViews(NULL);
	  EndWaitCursor();
	  return;
	}
	if(m_validnum==0)//If No valid images
	{
	  m_sDatabasePath="No image database is selected!";
	  MessageBox(NULL,"No valid image is in the selected path!","Error!",MB_OK|MB_ICONSTOP);
	  UpdateAllViews(NULL);
	  EndWaitCursor();
	  return;
	}
	m_bDatabaseOpened=true;
	m_bDatabaseChanged=true;
	UpdateAllViews(NULL);
	EndWaitCursor();
}
void CVqRetrieveDoc::OnDatabaseFeatureselection() 
{
	// TODO: Add your command handler code here
	CDialogFeatureSelection dfs;
	dfs.ffi=m_ffi;
	dfs.readonly=FALSE;
	if(dfs.DoModal()==IDOK)m_ffi=dfs.ffi;
	else return;
    m_extractednum=0;
	m_normalizednum=0;
	m_clusters=10;
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedvqfeaturefile="No vq feature file saved";
	m_bDatabaseFeatureComputed=false;	
	m_bDatabaseFeatureComputing=false;	
	m_bDatabaseFeatureInterrupted=false;
	m_bDatabaseFeatureNormalized=false;	
	m_bDatabaseClustered=false;
	m_bFeatureFileSaved=false;
	m_bCodebookFileSaved=false;
	m_bVQFeatureFileSaved=false;
	m_featuresorted=FALSE;
	m_clustersorted=FALSE;
	DestroyDatabaseMemory();
	CreateDatabaseMemory();
}

void CVqRetrieveDoc::OnDatabaseCodebookfordctvq() 
{
	// TODO: Add your command handler code here
 	
	//String For MessageBox
	char temp[_MAX_PATH+100];
	//File handle
    int fh;
	//File block for each image
	unsigned long int blk;
	//Total Length for all selected images for design
	unsigned long int totallen;
	//The counters for For(;;)
	int ii;
	int component;
	unsigned long int i,j,k,l,m;
	//The number of selected images
	unsigned short int num;
	//The number of total image vectors
	unsigned long int blocks;
	//The number of blocks in each image
	unsigned long int eachblocks,blockstemp;
	//the image width and height
	int imagewidth,imageheight;
	//The blocks in horizotal and the blocks in vertical of an image
	unsigned short int wbs,hbs;
	int BOOKSIZE1,BOOKSIZE2;
	//The memory handle
	HGLOBAL hMem;
    //The memory pointer for each image
	unsigned char *ImageY,*ImageCb,*ImageCr;	
	
	//The vectornumbers in each cluster during the design process
	unsigned long int *VectorNumber1,*VectorNumber2,*VectorNumber3,*VectorNumber4;
    //The index in codebook for each input image vetor
	unsigned short int *DesignCodeIndex1,*DesignCodeIndex2,*DesignCodeIndex3,*DesignCodeIndex4;
	
	unsigned char INBLOCK[BLOCKHEIGHT][BLOCKWIDTH],*INBLOCK1[BLOCKHEIGHT];
	char *file[16];
 	double OUTDCT[BLOCKHEIGHT][BLOCKWIDTH];
	double DCT1D[VECTORDIMENSION],*OUTDCT1[BLOCKHEIGHT];
	double a,b,c;
	unsigned short int d;
	//set the dlg's owner window as CDCTVQWMView
    //initialize the dialog parameters
    for(ii=0;ii<16;ii++)
 	  file[ii]=&m_DesignFileNames[ii][0];
 	CSourceDlg dlg(NULL,m_DesignImagesNumber,file,m_sDatabasePath);
 	
 	//achieve the dialog parameters
 	if(dlg.DoModal()==IDOK)
 	{
 	  m_DesignImagesNumber=dlg.m_Number;
      for(ii=0;ii<dlg.m_Number;ii++)
 	  strcpy(m_DesignFileNames[ii],dlg.m_FileNames[ii]);
 	}
    num=m_DesignImagesNumber;
	
	
	//If no image are selected,then return
	if(num==0)
	{
	   MessageBox(NULL,"No training images opened","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	}
    
	/////////Get the total no. blocks ///////
	blocks=0;
	totallen=0;//the total length of the images for one component
	for(i=0;i<num;i++)
	{
	   blk=GetImageBlocks(m_DesignFileNames[i],BLOCKWIDTH,BLOCKHEIGHT,&totallen);
       if(blk<=0)
	   {
	     sprintf(temp,"Cannot open file[%s] or read error or format error!",m_DesignFileNames[i]);
	     MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		 return;
	   }
	   else
	     blocks+=blk;
	}

	
/////////Get the blocks and total length of selected training images ends///////
    
//*********************************************************//	
//+++++++++++++++For Y Cb Cr components+++++++++++++++++++++++++++//
//*********************************************************//
//*********************************************************//
//*********************************************************//
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook design for Y component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=BOOKSIZEY1;
		  BOOKSIZE2=BOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cb component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=BOOKSIZECb1;
		  BOOKSIZE2=BOOKSIZECb2;
	  }
	  if(component==0)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cr component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=BOOKSIZECr1;
		  BOOKSIZE2=BOOKSIZECr2;
	  }
	  //The pointer array to save several opened raw images for design using vectors
      unsigned char (*TrainImageVectors)[VECTORDIMENSION];
	  TrainImageVectors=new unsigned char[blocks][VECTORDIMENSION];
	  if(TrainImageVectors==NULL)
	  {
	    MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	    return;
	  }
	  float *TrainImageVectors1;  //for DC value scalr qyuantization
	  TrainImageVectors1=new float[blocks];
	  if(TrainImageVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  float (*TrainImageVectors2)[DIMENSION1];
	  TrainImageVectors2=new float[blocks][DIMENSION1];
	  if(TrainImageVectors2==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  float (*TrainImageVectors3)[DIMENSION2];
	  TrainImageVectors3=new float[blocks][DIMENSION2];
	  if(TrainImageVectors3==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] TrainImageVectors2;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  float *TrainImageVectors4;////for AC energy value scalr qyuantization
	  TrainImageVectors4=new float[blocks];
	  if(TrainImageVectors4==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] TrainImageVectors2;
	   delete [] TrainImageVectors3;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  //The pointer array for generated codevectors by codebook design
	  float *DesignCodeVectors1;
	  DesignCodeVectors1=new float[BOOKSIZE0];
	  if(DesignCodeVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] TrainImageVectors2;
	   delete [] TrainImageVectors3;
	   delete [] TrainImageVectors4;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  float (*DesignCodeVectors2)[DIMENSION1];
	  DesignCodeVectors2=new float[BOOKSIZE1][DIMENSION1];
	  if(DesignCodeVectors2==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] TrainImageVectors2;
	   delete [] TrainImageVectors3;
	   delete [] TrainImageVectors4;
	   delete [] DesignCodeVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  float (*DesignCodeVectors3)[DIMENSION2];
	  DesignCodeVectors3=new float[BOOKSIZE2][DIMENSION2];
	  if(DesignCodeVectors3==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] TrainImageVectors2;
	   delete [] TrainImageVectors3;
	   delete [] TrainImageVectors4;
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  float *DesignCodeVectors4;
	  DesignCodeVectors4=new float[BOOKSIZE3];
	  if(DesignCodeVectors4==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] TrainImageVectors2;
	   delete [] TrainImageVectors3;
	   delete [] TrainImageVectors4;
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
      BeginWaitCursor();
	  /////////Apply memory and allocate them for variables begins/////////////////
	  hMem=NULL;
	  i=MAXIMAGESIZE  //Each image Y component
	  +MAXIMAGESIZE  //Each image Cb component
	  +MAXIMAGESIZE  //Each image Cr component
	  +sizeof(unsigned short int)*blocks*4  //DesignCodeIndex1/2/3/4
	  +(BOOKSIZE0+BOOKSIZE1+BOOKSIZE2+BOOKSIZE3)*sizeof(unsigned long int); //VectorNumber 1/2/3/4
	  hMem=GlobalAlloc(GMEM_FIXED,i);
	  if(hMem==NULL)
	  {
	    sprintf(temp,"Sorry, memory is not enough%fMBytes",(double)i/1024.0/1024.0);
	    MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
	    delete [] TrainImageVectors;
	    delete [] TrainImageVectors1;
	    delete [] TrainImageVectors2;
	    delete [] TrainImageVectors3;
	    delete [] TrainImageVectors4;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
   	    delete [] DesignCodeVectors4;
	    return;
	  }
	  VectorNumber1=(unsigned long int *)hMem;
	  VectorNumber2=VectorNumber1+BOOKSIZE0;
      VectorNumber3=VectorNumber2+BOOKSIZE1;
	  VectorNumber4=VectorNumber3+BOOKSIZE2;
      DesignCodeIndex1=(unsigned short int *)(VectorNumber4+BOOKSIZE3);
	  DesignCodeIndex2=DesignCodeIndex1+blocks;
	  DesignCodeIndex3=DesignCodeIndex2+blocks;
	  DesignCodeIndex4=DesignCodeIndex3+blocks;
	  ImageY=(unsigned char *)(DesignCodeIndex4+blocks);
	  ImageCb=ImageY+MAXIMAGESIZE;
	  ImageCr=ImageCb+MAXIMAGESIZE;
      /////////Apply memory and allocate them for variables begins/////////////////
      long int linebytes;
	  //////////////////Read The image Data Begins///////////////////
	  blockstemp=0;
      for(i=0;i<num;i++)
	  {
	    ii=GetImageYCbCrComponent(m_DesignFileNames[i],ImageY,ImageCb,ImageCr,&imagewidth,&imageheight);
	    if(ii<0)
		{ 
		  sprintf(temp,"Sorry, File[%s] read or format Error",m_DesignFileNames[i]);
	      MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		  GlobalFree(hMem);
	      delete [] TrainImageVectors;
	      delete [] TrainImageVectors1;
	      delete [] TrainImageVectors2;
	      delete [] TrainImageVectors3;
	      delete [] TrainImageVectors4;
	      delete [] DesignCodeVectors1;
	      delete [] DesignCodeVectors2;
	      delete [] DesignCodeVectors3;
   	      delete [] DesignCodeVectors4;
   	      return;
		}
		wbs=imagewidth/BLOCKWIDTH;
		hbs=imageheight/BLOCKHEIGHT;
		eachblocks=wbs*hbs;
		linebytes=(imagewidth+3)/4*4;
		//block the source image
	    for(l=0;l<hbs;l++)
		{
		  for(k=0;k<wbs;k++)
		  {
	        for(j=0;j<BLOCKHEIGHT;j++)		
			{
			  for(m=0;m<BLOCKWIDTH;m++)		  
			  {
	            if(component==2)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*BLOCKWIDTH]=ImageY[m+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*linebytes];
				if(component==1)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*BLOCKWIDTH]=ImageCb[m+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*linebytes];
				if(component==0)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*BLOCKWIDTH]=ImageCr[m+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*linebytes];
			  }
			} 
		  }
		}
	    blockstemp+=eachblocks;
	  }
      //////////////////Read The image Data ends///////////////////	

      /////////////////Start desin with specified methods begins///////////
	  	  
	  for(i=0;i<BLOCKHEIGHT;i++)
	  {
		INBLOCK1[i]=INBLOCK[i];
		OUTDCT1[i]=OUTDCT[i];
	  }
	  for(i=0;i<blocks;i++)
	  {
	    for(k=0;k<BLOCKHEIGHT;k++)
		{
		  for(j=0;j<BLOCKWIDTH;j++)
		    INBLOCK[k][j]=TrainImageVectors[i][k*BLOCKWIDTH+j];
		}
	    MyRetrieveMethod.DCT(INBLOCK1,OUTDCT1,BLOCKHEIGHT,BLOCKWIDTH);
	    MyRetrieveMethod.DCT2To1Or1To2(OUTDCT1,DCT1D,BLOCKHEIGHT,BLOCKWIDTH,0);
	    
		TrainImageVectors1[i]=(float)DCT1D[0];
		for(k=POSITION1;k<POSITION2;k++)
		  TrainImageVectors2[i][k-POSITION1]=(float)DCT1D[k];
	    for(k=POSITION2;k<POSITION2+DIMENSION2;k++)
		  TrainImageVectors3[i][k-POSITION2]=(float)DCT1D[k];
		c=0.0;
		for(k=POSITION2+DIMENSION2;k<VECTORDIMENSION;k++)
          c+=DCT1D[k]*DCT1D[k];
		TrainImageVectors4[i]=(float)sqrt(c/(double)(VECTORDIMENSION-POSITION2-DIMENSION2));
	  }
	  MyRetrieveMethod.DCTVQScalarCodebookDesign(blocks,BOOKSIZE0,0.000001,TrainImageVectors1,DesignCodeVectors1,DesignCodeIndex1,VectorNumber1,&a,&b,&c,&d);
	  MyRetrieveMethod.DCTVQLBGCodebookDesign(blocks,BOOKSIZE1,DIMENSION1,0.000001,TrainImageVectors2,DesignCodeVectors2,DesignCodeIndex2,VectorNumber2,&a,&b,&c,&d);
      MyRetrieveMethod.DCTVQLBGCodebookDesign(blocks,BOOKSIZE2,DIMENSION2,0.000001,TrainImageVectors3,DesignCodeVectors3,DesignCodeIndex3,VectorNumber3,&a,&b,&c,&d);
	  MyRetrieveMethod.DCTVQScalarCodebookDesign(blocks,BOOKSIZE3,0.000001,TrainImageVectors4,DesignCodeVectors4,DesignCodeIndex4,VectorNumber4,&a,&b,&c,&d);
      /////////////////Start Design with specified methods ends///////////
   
      /////////////////Save the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComY.bk";
      else if(component==1)
	    temp1+="\\ComCb.bk";
      else
	    temp1+="\\ComCr.bk";
      fh=_open(temp1,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open or create File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Save",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
	    delete [] TrainImageVectors1;
	    delete [] TrainImageVectors2;
	    delete [] TrainImageVectors3;
	    delete [] TrainImageVectors4;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
   	    delete [] DesignCodeVectors4;
   	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      bfh.PixelBits=8;
      bfh.Parts=4;
      bfh.CodeBookSize[0]=BOOKSIZE0;
      bfh.CodeBookSize[1]=BOOKSIZE1;
      bfh.CodeBookSize[2]=BOOKSIZE2;
      bfh.CodeBookSize[3]=BOOKSIZE3;
      bfh.CodewordBytes[0]=4;
      bfh.CodewordBytes[1]=4;
      bfh.CodewordBytes[2]=4;
      bfh.CodewordBytes[3]=4;
      bfh.ImageBlockWidth=BLOCKWIDTH;
      bfh.ImageBlockHeight=BLOCKHEIGHT;
      bfh.CodewordDimension[0]=1;
      bfh.CodewordDimension[1]=DIMENSION1;
      bfh.CodewordDimension[2]=DIMENSION2;
      bfh.CodewordDimension[3]=1;
      if(_write(fh,&bfh,sizeof(bfh))==-1)
	  {
	    MessageBox(NULL,"Save error","File Save",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
	    delete [] TrainImageVectors1;
	    delete [] TrainImageVectors2;
	    delete [] TrainImageVectors3;
	    delete [] TrainImageVectors4;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
   	    delete [] DesignCodeVectors4;
   	    return;
	  }
      _lseek(fh,100,SEEK_SET);
      _write(fh,DesignCodeVectors1,(unsigned long int)BOOKSIZE0*sizeof(float));
      _write(fh,&DesignCodeVectors2[0][0],DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float));
      _write(fh,&DesignCodeVectors3[0][0],DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float));
      _write(fh,DesignCodeVectors4,(unsigned long int)BOOKSIZE3*sizeof(float));
      //close the file 
      _close(fh);
     /////////////////Save the codebook ends///////////
     //Free the memory
     GlobalFree(hMem);
	 EndWaitCursor();
	 delete [] TrainImageVectors;
	 delete [] TrainImageVectors1;
	 delete [] TrainImageVectors2;
	 delete [] TrainImageVectors3;
	 delete [] TrainImageVectors4;
	 delete [] DesignCodeVectors1;
	 delete [] DesignCodeVectors2;
	 delete [] DesignCodeVectors3;
   	 delete [] DesignCodeVectors4;
   }
   
   for(i=0;i<num;i++)
   OnEncodingTest(m_DesignFileNames[i]);
}

void CVqRetrieveDoc::OnDatabaseCodebookforvq() 
{
	// TODO: Add your command handler code here
	//String For MessageBox
	char temp[_MAX_PATH+100];
	//File handle
    int fh;
	//File block for each image
	unsigned long int blk;
	//Total Length for all selected images for design
	unsigned long int totallen;
	//The counters for For(;;)
	int ii;
	int component;
	char *file[16];
	unsigned long int i,j,k,l,m;
	//The number of selected images
	unsigned short int num;
	//The number of total image vectors
	unsigned long int blocks;
	//The number of blocks in each image
	unsigned long int eachblocks,blockstemp;
	//the image width and height
	int imagewidth,imageheight;
	//The blocks in horizotal and the blocks in vertical of an image
	unsigned short int wbs,hbs;
	int BOOKSIZE1;
	//The memory handle
	HGLOBAL hMem;
    //The memory pointer for each image
	unsigned char *ImageY,*ImageCb,*ImageCr;	
	
	//The vectornumbers in each cluster during the design process
	unsigned long int *VectorNumber1;
    //The index in codebook for each input image vetor
	unsigned short int *DesignCodeIndex1;
	
	double a,b,c;
	unsigned short int d;
	//set the dlg's owner window as CDCTVQWMView
    //initialize the dialog parameters
    for(ii=0;ii<16;ii++)
 	  file[ii]=&m_DesignFileNames[ii][0];
 	CSourceDlg dlg(NULL,m_DesignImagesNumber,file,m_sDatabasePath);
 	
 	//achieve the dialog parameters
 	if(dlg.DoModal()==IDOK)
 	{
 	  m_DesignImagesNumber=dlg.m_Number;
      for(ii=0;ii<dlg.m_Number;ii++)
 	  strcpy(m_DesignFileNames[ii],dlg.m_FileNames[ii]);
 	}
    num=m_DesignImagesNumber;
	
	
	//If no image are selected,then return
	if(num==0)
	{
	   MessageBox(NULL,"No training images opened","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	}
    
	/////////Get the total no. blocks ///////
	blocks=0;
	totallen=0;//the total length of the images for one component
	for(i=0;i<num;i++)
	{
	   blk=GetImageBlocks(m_DesignFileNames[i],VQBLOCKWIDTH,VQBLOCKHEIGHT,&totallen);
       if(blk<=0)
	   {
	     sprintf(temp,"Cannot open file[%s] or read error or format error!",m_DesignFileNames[i]);
	     MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		 return;
	   }
	   else
	     blocks+=blk;
	}

	
/////////Get the blocks and total length of selected training images ends///////
    
//*********************************************************//	
//+++++++++++++++For Y Cb Cr components+++++++++++++++++++++++++++//
//*********************************************************//
//*********************************************************//
//*********************************************************//
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook design for Y component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZEY;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cb component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECb;
	  }
	  if(component==0)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cr component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECr;
	  }
	  //The pointer array to save several opened raw images for design using vectors
      unsigned char (*TrainImageVectors)[VQDIMENSION];
	  TrainImageVectors=new unsigned char[blocks][VQDIMENSION];
	  if(TrainImageVectors==NULL)
	  {
	    MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	    return;
	  }
	  //The pointer array for generated codevectors by codebook design
	  unsigned char (*DesignCodeVectors1)[VQDIMENSION];
	  DesignCodeVectors1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(DesignCodeVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  BeginWaitCursor();
	  /////////Apply memory and allocate them for variables begins/////////////////
	  hMem=NULL;
	  i=MAXIMAGESIZE  //Each image Y component
	  +MAXIMAGESIZE  //Each image Cb component
	  +MAXIMAGESIZE  //Each image Cr component
	  +sizeof(unsigned short int)*blocks  //DesignCodeIndex1
	  +(BOOKSIZE1)*sizeof(unsigned long int); //VectorNumber 1
	  hMem=GlobalAlloc(GMEM_FIXED,i);
	  if(hMem==NULL)
	  {
	    sprintf(temp,"Sorry, memory is not enough%fMBytes",(double)i/1024.0/1024.0);
	    MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
	    delete [] TrainImageVectors;
	    delete [] DesignCodeVectors1;
	    return;
	  }
	  VectorNumber1=(unsigned long int *)hMem;
	  DesignCodeIndex1=(unsigned short int *)(VectorNumber1+BOOKSIZE1);
	  ImageY=(unsigned char *)(DesignCodeIndex1+blocks);
	  ImageCb=ImageY+MAXIMAGESIZE;
	  ImageCr=ImageCb+MAXIMAGESIZE;
      /////////Apply memory and allocate them for variables begins/////////////////
      long int linebytes;
	  //////////////////Read The image Data Begins///////////////////
	  blockstemp=0;
      for(i=0;i<num;i++)
	  {
	    ii=GetImageYCbCrComponent(m_DesignFileNames[i],ImageY,ImageCb,ImageCr,&imagewidth,&imageheight);
	    if(ii<0)
		{ 
		  sprintf(temp,"Sorry, File[%s] read or format Error",m_DesignFileNames[i]);
	      MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		  GlobalFree(hMem);
	      delete [] TrainImageVectors;
	      delete [] DesignCodeVectors1;
	      return;
		}
		wbs=imagewidth/VQBLOCKWIDTH;
		hbs=imageheight/VQBLOCKHEIGHT;
		eachblocks=wbs*hbs;
		linebytes=(imagewidth+3)/4*4;
		//block the source image
	    for(l=0;l<hbs;l++)
		{
		  for(k=0;k<wbs;k++)
		  {
	        for(j=0;j<VQBLOCKHEIGHT;j++)		
			{
			  for(m=0;m<VQBLOCKWIDTH;m++)		  
			  {
	            if(component==2)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageY[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
				if(component==1)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageCb[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
				if(component==0)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageCr[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  }
			} 
		  }
		}
	    blockstemp+=eachblocks;
	  }
      //////////////////Read The image Data ends///////////////////	

      /////////////////Start desin with specified methods begins///////////
	  MyRetrieveMethod.VQLBGCodebookDesign(blocks,BOOKSIZE1,VQDIMENSION,0.000001,TrainImageVectors,DesignCodeVectors1,DesignCodeIndex1,VectorNumber1,&a,&b,&c,&d);
      /////////////////Start Design with specified methods ends///////////
   
      /////////////////Save the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbVQ.bk";
      else
	    temp1+="\\ComCrVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open or create File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Save",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
	    delete [] DesignCodeVectors1;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      bfh.PixelBits=8;
      bfh.Parts=1;
      bfh.CodeBookSize[0]=BOOKSIZE1;
      bfh.CodewordBytes[0]=4;
      bfh.ImageBlockWidth=VQBLOCKWIDTH;
      bfh.ImageBlockHeight=VQBLOCKHEIGHT;
      bfh.CodewordDimension[0]=VQDIMENSION;
      if(_write(fh,&bfh,sizeof(bfh))==-1)
	  {
	    MessageBox(NULL,"Save error","File Save",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
	    delete [] DesignCodeVectors1;
	    return;
	  }
      _lseek(fh,100,SEEK_SET);
      _write(fh,&DesignCodeVectors1[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char));
      //close the file 
      _close(fh);
     /////////////////Save the codebook ends///////////
     //Free the memory
     GlobalFree(hMem);
	 EndWaitCursor();
	 delete [] TrainImageVectors;
	 delete [] DesignCodeVectors1;
   }
   for(i=0;i<num;i++)
   OnEncodingTest0(m_DesignFileNames[i]);
	
}

void CVqRetrieveDoc::OnDatabaseCodebookformsvq() 
{
	// TODO: Add your command handler code here
	//String For MessageBox
	char temp[_MAX_PATH+100];
	//File handle
    int fh;
	//File block for each image
	unsigned long int blk;
	//Total Length for all selected images for design
	unsigned long int totallen;
	//The counters for For(;;)
	int ii;
	int component;
	unsigned long int i,j,k,l,m;
	//The number of selected images
	unsigned short int num;
	//The number of total image vectors
	unsigned long int blocks;
	//The number of blocks in each image
	unsigned long int eachblocks,blockstemp;
	//the image width and height
	int imagewidth,imageheight;
	//The blocks in horizotal and the blocks in vertical of an image
	unsigned short int wbs,hbs;
	int BOOKSIZE1,BOOKSIZE2;
	//The memory handle
	HGLOBAL hMem;
    //The memory pointer for each image
	unsigned char *ImageY,*ImageCb,*ImageCr;	
	
	//The vectornumbers in each cluster during the design process
	unsigned long int *VectorNumber1,*VectorNumber2;
    //The index in codebook for each input image vetor
	unsigned short int *DesignCodeIndex1,*DesignCodeIndex2;
	
	char *file[16];
 	double a,b,c;
	unsigned short int d;
	//set the dlg's owner window as CDCTVQWMView
    //initialize the dialog parameters
    for(ii=0;ii<16;ii++)
 	  file[ii]=&m_DesignFileNames[ii][0];
 	CSourceDlg dlg(NULL,m_DesignImagesNumber,file,m_sDatabasePath);
 	
 	//achieve the dialog parameters
 	if(dlg.DoModal()==IDOK)
 	{
 	  m_DesignImagesNumber=dlg.m_Number;
      for(ii=0;ii<dlg.m_Number;ii++)
 	  strcpy(m_DesignFileNames[ii],dlg.m_FileNames[ii]);
 	}
    num=m_DesignImagesNumber;
	
	
	//If no image are selected,then return
	if(num==0)
	{
	   MessageBox(NULL,"No training images opened","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	}
    
	/////////Get the total no. blocks ///////
	blocks=0;
	totallen=0;//the total length of the images for one component
	for(i=0;i<num;i++)
	{
	   blk=GetImageBlocks(m_DesignFileNames[i],VQBLOCKWIDTH,VQBLOCKHEIGHT,&totallen);
       if(blk<=0)
	   {
	     sprintf(temp,"Cannot open file[%s] or read error or format error!",m_DesignFileNames[i]);
	     MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		 return;
	   }
	   else
	     blocks+=blk;
	}

	
/////////Get the blocks and total length of selected training images ends///////
    
//*********************************************************//	
//+++++++++++++++For Y Cb Cr components+++++++++++++++++++++++++++//
//*********************************************************//
//*********************************************************//
//*********************************************************//
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook design for Y component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZEY1;
		  BOOKSIZE2=VQBOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cb component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECb1;
		  BOOKSIZE2=VQBOOKSIZECb2;
	  }
	  if(component==0)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cr component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECr1;
		  BOOKSIZE2=VQBOOKSIZECr2;
	  }
	  //The pointer array to save several opened raw images for design using vectors
      unsigned char (*TrainImageVectors)[VQDIMENSION];
	  TrainImageVectors=new unsigned char[blocks][VQDIMENSION];
	  if(TrainImageVectors==NULL)
	  {
	    MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	    return;
	  }
	  short int (*TrainImageVectors1)[VQDIMENSION];  //for error vector quantization
	  TrainImageVectors1=new short int[blocks][VQDIMENSION];
	  if(TrainImageVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  //The pointer array for generated codevectors by codebook design
	  unsigned char (*DesignCodeVectors1)[VQDIMENSION];
	  DesignCodeVectors1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(DesignCodeVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  short int (*DesignCodeVectors2)[VQDIMENSION];
	  DesignCodeVectors2=new short int[BOOKSIZE2][VQDIMENSION];
	  if(DesignCodeVectors2==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors1;
	   delete [] DesignCodeVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  BeginWaitCursor();
	  /////////Apply memory and allocate them for variables begins/////////////////
	  hMem=NULL;
	  i=MAXIMAGESIZE  //Each image Y component
	  +MAXIMAGESIZE  //Each image Cb component
	  +MAXIMAGESIZE  //Each image Cr component
	  +sizeof(unsigned short int)*blocks*2  //DesignCodeIndex1/2
	  +(BOOKSIZE1+BOOKSIZE2)*sizeof(unsigned long int); //VectorNumber 1/2/
	  hMem=GlobalAlloc(GMEM_FIXED,i);
	  if(hMem==NULL)
	  {
	    sprintf(temp,"Sorry, memory is not enough%fMBytes",(double)i/1024.0/1024.0);
	    MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
	    delete [] TrainImageVectors;
	    delete [] TrainImageVectors1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    return;
	  }
	  VectorNumber1=(unsigned long int *)hMem;
	  VectorNumber2=VectorNumber1+BOOKSIZE1;
      DesignCodeIndex1=(unsigned short int *)(VectorNumber2+BOOKSIZE2);
	  DesignCodeIndex2=DesignCodeIndex1+blocks;
	  ImageY=(unsigned char *)(DesignCodeIndex2+blocks);
	  ImageCb=ImageY+MAXIMAGESIZE;
	  ImageCr=ImageCb+MAXIMAGESIZE;
      /////////Apply memory and allocate them for variables begins/////////////////
      long int linebytes;
	  //////////////////Read The image Data Begins///////////////////
	  blockstemp=0;
      for(i=0;i<num;i++)
	  {
	    ii=GetImageYCbCrComponent(m_DesignFileNames[i],ImageY,ImageCb,ImageCr,&imagewidth,&imageheight);
	    if(ii<0)
		{ 
		  sprintf(temp,"Sorry, File[%s] read or format Error",m_DesignFileNames[i]);
	      MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		  GlobalFree(hMem);
	      delete [] TrainImageVectors;
	      delete [] TrainImageVectors1;
	      delete [] DesignCodeVectors1;
	      delete [] DesignCodeVectors2;
	      return;
		}
		wbs=imagewidth/VQBLOCKWIDTH;
		hbs=imageheight/VQBLOCKHEIGHT;
		eachblocks=wbs*hbs;
		linebytes=(imagewidth+3)/4*4;
		//block the source image
	    for(l=0;l<hbs;l++)
		{
		  for(k=0;k<wbs;k++)
		  {
	        for(j=0;j<VQBLOCKHEIGHT;j++)		
			{
			  for(m=0;m<VQBLOCKWIDTH;m++)		  
			  {
	            if(component==2)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageY[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
				if(component==1)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageCb[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
				if(component==0)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageCr[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  }
			} 
		  }
		}
	    blockstemp+=eachblocks;
	  }
      //////////////////Read The image Data ends///////////////////	

      /////////////////Start desin with specified methods begins///////////
      MyRetrieveMethod.TwoStageVQ256GrayImageCodebookDesign(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,0.000001,TrainImageVectors,TrainImageVectors1,DesignCodeVectors1,DesignCodeVectors2,DesignCodeIndex1,DesignCodeIndex2,VectorNumber1,VectorNumber2,&a,&b,&c,&d);
	  
	  /////////////////Save the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYMSVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbMSVQ.bk";
      else
	    temp1+="\\ComCrMSVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open or create File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Save",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
	    delete [] TrainImageVectors1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      bfh.PixelBits=8;
      bfh.Parts=2;
      bfh.CodeBookSize[0]=BOOKSIZE1;
      bfh.CodeBookSize[1]=BOOKSIZE2;
      bfh.CodewordBytes[0]=1;
      bfh.CodewordBytes[1]=2;
      bfh.ImageBlockWidth=VQBLOCKWIDTH;
      bfh.ImageBlockHeight=VQBLOCKHEIGHT;
      bfh.CodewordDimension[0]=VQDIMENSION;
      bfh.CodewordDimension[1]=VQDIMENSION;
      if(_write(fh,&bfh,sizeof(bfh))==-1)
	  {
	    MessageBox(NULL,"Save error","File Save",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
	    delete [] TrainImageVectors1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    return;
	  }
      _lseek(fh,100,SEEK_SET);
      _write(fh,&DesignCodeVectors1[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char));
      _write(fh,&DesignCodeVectors2[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int));
      //close the file 
      _close(fh);
     /////////////////Save the codebook ends///////////
     //Free the memory
     GlobalFree(hMem);
	 EndWaitCursor();
	 delete [] TrainImageVectors;
	 delete [] TrainImageVectors1;
	 delete [] DesignCodeVectors1;
	 delete [] DesignCodeVectors2;
   }
   for(i=0;i<num;i++)
   OnEncodingTest1(m_DesignFileNames[i]);
}

void CVqRetrieveDoc::OnDatabaseCodebookformrvq() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	//String For MessageBox
	char temp[_MAX_PATH+100];
	//File handle
    int fh;
	//File block for each image
	unsigned long int blk;
	//Total Length for all selected images for design
	unsigned long int totallen;
	//The counters for For(;;)
	int ii;
	int component;
	unsigned long int i,j,k,l,m;
	//The number of selected images
	unsigned short int num;
	//The number of total image vectors
	unsigned long int blocks;
	//The number of blocks in each image
	unsigned long int eachblocks,blockstemp;
	//the image width and height
	int imagewidth,imageheight;
	//The blocks in horizotal and the blocks in vertical of an image
	unsigned short int wbs,hbs;
	int BOOKSIZE1,BOOKSIZE2;
	//The memory handle
	HGLOBAL hMem;
    //The memory pointer for each image
	unsigned char *ImageY,*ImageCb,*ImageCr;	
	
	//The vectornumbers in each cluster during the design process
	unsigned long int *VectorNumber1,*VectorNumber2;
    //The index in codebook for each input image vetor
	unsigned short int *DesignCodeIndex1,*DesignCodeIndex2;
	
	char *file[16];
 	double a,b,c;
	unsigned short int d;
	//set the dlg's owner window as CDCTVQWMView
    //initialize the dialog parameters
    for(ii=0;ii<16;ii++)
 	  file[ii]=&m_DesignFileNames[ii][0];
 	CSourceDlg dlg(NULL,m_DesignImagesNumber,file,m_sDatabasePath);
 	
 	//achieve the dialog parameters
 	if(dlg.DoModal()==IDOK)
 	{
 	  m_DesignImagesNumber=dlg.m_Number;
      for(ii=0;ii<dlg.m_Number;ii++)
 	  strcpy(m_DesignFileNames[ii],dlg.m_FileNames[ii]);
 	}
    num=m_DesignImagesNumber;
	
	
	//If no image are selected,then return
	if(num==0)
	{
	   MessageBox(NULL,"No training images opened","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	}
    
	/////////Get the total no. blocks ///////
	blocks=0;
	totallen=0;//the total length of the images for one component
	for(i=0;i<num;i++)
	{
	   blk=GetImageBlocks(m_DesignFileNames[i],VQBLOCKWIDTH,VQBLOCKHEIGHT,&totallen);
       if(blk<=0)
	   {
	     sprintf(temp,"Cannot open file[%s] or read error or format error!",m_DesignFileNames[i]);
	     MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		 return;
	   }
	   else
	     blocks+=blk;
	}

	
/////////Get the blocks and total length of selected training images ends///////
    
//*********************************************************//	
//+++++++++++++++For Y Cb Cr components+++++++++++++++++++++++++++//
//*********************************************************//
//*********************************************************//
//*********************************************************//
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook design for Y component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZEYM;
		  BOOKSIZE2=VQBOOKSIZEYR;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cb component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECbM;
		  BOOKSIZE2=VQBOOKSIZECbR;
	  }
	  if(component==0)
	  {
		  MessageBox(NULL,"Now, The codebook design for Cr component begins","Codebook Design",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECrM;
		  BOOKSIZE2=VQBOOKSIZECrR;
	  }
	  //The pointer array to save several opened raw images for design using vectors
      unsigned char (*TrainImageVectors)[VQDIMENSION];
	  TrainImageVectors=new unsigned char[blocks][VQDIMENSION];
	  if(TrainImageVectors==NULL)
	  {
	    MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	    return;
	  }
	  unsigned char *TrainImageVectors0;
	  TrainImageVectors0=new unsigned char[blocks];
	  if(TrainImageVectors0==NULL)
	  {
	    delete [] TrainImageVectors;
		MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	    return;
	  }
	  short int (*TrainImageVectors1)[VQDIMENSION];  //for error vector quantization
	  TrainImageVectors1=new short int[blocks][VQDIMENSION];
	  if(TrainImageVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors0;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  //The pointer array for generated codevectors by codebook design
	  unsigned char (*DesignCodeVectors1)[VQDIMENSION];
	  DesignCodeVectors1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(DesignCodeVectors1==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors0;
	   delete [] TrainImageVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  short int (*DesignCodeVectors2)[VQDIMENSION];
	  DesignCodeVectors2=new short int[BOOKSIZE2][VQDIMENSION];
	  if(DesignCodeVectors2==NULL)
	  {
	   delete [] TrainImageVectors;
	   delete [] TrainImageVectors0;
	   delete [] TrainImageVectors1;
	   delete [] DesignCodeVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  BeginWaitCursor();
	  /////////Apply memory and allocate them for variables begins/////////////////
	  hMem=NULL;
	  i=MAXIMAGESIZE  //Each image Y component
	  +MAXIMAGESIZE  //Each image Cb component
	  +MAXIMAGESIZE  //Each image Cr component
	  +sizeof(unsigned short int)*blocks*2  //DesignCodeIndex1/2
	  +(BOOKSIZE1+BOOKSIZE2)*sizeof(unsigned long int); //VectorNumber 1/2/
	  hMem=GlobalAlloc(GMEM_FIXED,i);
	  if(hMem==NULL)
	  {
	    sprintf(temp,"Sorry, memory is not enough%fMBytes",(double)i/1024.0/1024.0);
	    MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
	    delete [] TrainImageVectors;
		delete [] TrainImageVectors0;
	    delete [] TrainImageVectors1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    return;
	  }
	  VectorNumber1=(unsigned long int *)hMem;
	  VectorNumber2=VectorNumber1+BOOKSIZE1;
      DesignCodeIndex1=(unsigned short int *)(VectorNumber2+BOOKSIZE2);
	  DesignCodeIndex2=DesignCodeIndex1+blocks;
	  ImageY=(unsigned char *)(DesignCodeIndex2+blocks);
	  ImageCb=ImageY+MAXIMAGESIZE;
	  ImageCr=ImageCb+MAXIMAGESIZE;
      /////////Apply memory and allocate them for variables begins/////////////////
      long int linebytes;
	  //////////////////Read The image Data Begins///////////////////
	  blockstemp=0;
      for(i=0;i<num;i++)
	  {
	    ii=GetImageYCbCrComponent(m_DesignFileNames[i],ImageY,ImageCb,ImageCr,&imagewidth,&imageheight);
	    if(ii<0)
		{ 
		  sprintf(temp,"Sorry, File[%s] read or format Error",m_DesignFileNames[i]);
	      MessageBox(NULL,temp,"Codebook Design",MB_ICONSTOP|MB_OK);
		  GlobalFree(hMem);
	      delete [] TrainImageVectors;
		  delete [] TrainImageVectors0;
	      delete [] TrainImageVectors1;
	      delete [] DesignCodeVectors1;
	      delete [] DesignCodeVectors2;
	      return;
		}
		wbs=imagewidth/VQBLOCKWIDTH;
		hbs=imageheight/VQBLOCKHEIGHT;
		eachblocks=wbs*hbs;
		linebytes=(imagewidth+3)/4*4;
		//block the source image
	    for(l=0;l<hbs;l++)
		{
		  for(k=0;k<wbs;k++)
		  {
	        for(j=0;j<VQBLOCKHEIGHT;j++)		
			{
			  for(m=0;m<VQBLOCKWIDTH;m++)		  
			  {
	            if(component==2)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageY[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
				if(component==1)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageCb[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
				if(component==0)
				  TrainImageVectors[blockstemp+k+l*wbs][m+j*VQBLOCKWIDTH]=ImageCr[m+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  }
			} 
		  }
		}
	    blockstemp+=eachblocks;
	  }
      //////////////////Read The image Data ends///////////////////	

      /////////////////Start desin with specified methods begins///////////
      MyRetrieveMethod.MeanRemovedVQ256GrayImageCodebookDesign(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,0.000001,TrainImageVectors,TrainImageVectors0,TrainImageVectors1,DesignCodeVectors1,DesignCodeVectors2,DesignCodeIndex1,DesignCodeIndex2,VectorNumber1,VectorNumber2,&a,&b,&c,&d);
	  
	  /////////////////Save the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYMRVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbMRVQ.bk";
      else
	    temp1+="\\ComCrMRVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open or create File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Save",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
		delete [] TrainImageVectors0;
	    delete [] TrainImageVectors1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      bfh.PixelBits=8;
      bfh.Parts=2;
      bfh.CodeBookSize[0]=BOOKSIZE1;
      bfh.CodeBookSize[1]=BOOKSIZE2;
      bfh.CodewordBytes[0]=1;
      bfh.CodewordBytes[1]=2;
      bfh.ImageBlockWidth=VQBLOCKWIDTH;
      bfh.ImageBlockHeight=VQBLOCKHEIGHT;
      bfh.CodewordDimension[0]=VQDIMENSION;
      bfh.CodewordDimension[1]=VQDIMENSION;
      if(_write(fh,&bfh,sizeof(bfh))==-1)
	  {
	    MessageBox(NULL,"Save error","File Save",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    GlobalFree(hMem);
	    delete [] TrainImageVectors;
		delete [] TrainImageVectors0;
	    delete [] TrainImageVectors1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    return;
	  }
      _lseek(fh,100,SEEK_SET);
      _write(fh,&DesignCodeVectors1[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char));
      _write(fh,&DesignCodeVectors2[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int));
      //close the file 
      _close(fh);
     /////////////////Save the codebook ends///////////
     //Free the memory
     GlobalFree(hMem);
	 EndWaitCursor();
	 delete [] TrainImageVectors;
	 delete [] TrainImageVectors0;
	 delete [] TrainImageVectors1;
	 delete [] DesignCodeVectors1;
	 delete [] DesignCodeVectors2;
   }
   for(i=0;i<num;i++)
   OnEncodingTest2(m_DesignFileNames[i]);
}


//To compute the database feature
void CVqRetrieveDoc::OnDatabaseFeaturecompute() 
{
	// TODO: Add your command handler code here
	//If feature has been computed ask if continue?
	if(m_bDatabaseFeatureComputed==true&&::AfxMessageBox("The database path hasn't been changed, do you want to recompute the feature file,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	if(m_ffi.m_bWithFeature1_OF==TRUE)
	{
	    if(OpenCodeBooks()!=0)return;
	}
	if(m_ffi.m_bWithFeature2_OF==TRUE)
	{
	    if(OpenCodeBooks0()!=0)return;
	}
	if(m_ffi.m_bWithFeature3_OF==TRUE)
	{
	    if(OpenCodeBooks1()!=0)return;
	}
	if(m_ffi.m_bWithFeature4_OF==TRUE)
	{
	    if(OpenCodeBooks2()!=0)return;
	}
	DestroyDatabaseMemory();//delete memory
	if(CreateDatabaseMemory()==false)return;//recreate memory
	m_extractednum=0;//no image computed
	m_normalizednum=0;//no feature normalized
	m_clusters=10;//the number of clusters
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedvqfeaturefile="No vq feature file saved";
	m_bDatabaseFeatureComputed=false;//not computed
	m_bDatabaseFeatureComputing=true;//computing now
	m_bDatabaseFeatureInterrupted=false;//not interrupted
	m_bDatabaseFeatureNormalized=false;	//not normalized
	m_bDatabaseClustered=false;//not clustered
	m_bFeatureFileSaved=false;//not file saved
	m_bCodebookFileSaved=false;//
	m_bVQFeatureFileSaved=false;//
	m_featuresorted=FALSE;//not sorted
    m_clustersorted=FALSE;//cluster not sorted
	
	UpdateAllViews(NULL);
	if(FeatureVectorExtract(m_sDatabasePath)==false)
	{
		MessageBox(NULL,"Feature Computation Interrupted","Information",MB_OK|MB_ICONINFORMATION);//extraction now
	}
	m_bDatabaseFeatureComputing=false;//not computing
	m_bDatabaseFeatureComputed=true;//finish compute
	UpdateAllViews(NULL);
}

//Interrupt the feature computing
void CVqRetrieveDoc::OnDatabaseStop() 
{
	// TODO: Add your command handler code here
	m_bDatabaseFeatureInterrupted=true;
	m_bDatabaseFeatureComputing=false;
	if(m_extractednum==m_validnum)m_bDatabaseFeatureInterrupted=false;
	m_ffi.m_bEverInterrupted=m_bDatabaseFeatureInterrupted;
}

void CVqRetrieveDoc::OnDatabaseFeaturenormalization() 
{
	// TODO: Add your command handler code here
	int i;
	if(m_bDatabaseFeatureNormalized==true&&::AfxMessageBox("The database path hasn't been changed, do you want to renormalizing the feature vectors,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	if(m_extractednum==0)
	{
	  MessageBox(NULL,"No Feature Vectors can be normalized","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_normalizednum=0;//no feature normalized
	m_clusters=10;//the number of clusters
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedvqfeaturefile="No vq feature file saved";
	m_bDatabaseFeatureNormalized=false;	//not normalized
	m_bDatabaseClustered=false;//not clustered
	m_bFeatureFileSaved=false;//not file saved
	m_bCodebookFileSaved=false;//
	m_bVQFeatureFileSaved=false;//
	m_featuresorted=FALSE;
	UpdateAllViews(NULL);
	BeginWaitCursor();
	WORD dimensions[8];
    dimensions[0]=m_ffi.m_wDimension_CF;
	dimensions[1]=m_ffi.m_wDimension_IF;
	dimensions[2]=m_ffi.m_wDimension_TF;
	dimensions[3]=m_ffi.m_wDimension_SF;
	if(m_ffi.m_bWithFeature1_OF==TRUE)
	  dimensions[4]=OtherDim[0];
	else
	  dimensions[4]=0;
	if(m_ffi.m_bWithFeature2_OF==TRUE)
	  dimensions[5]=OtherDim[1];
	else
	  dimensions[5]=0;
	if(m_ffi.m_bWithFeature3_OF==TRUE)
	  dimensions[6]=OtherDim[2];
	else
	  dimensions[6]=0;
	if(m_ffi.m_bWithFeature4_OF==TRUE)
	  dimensions[7]=OtherDim[3];
    else
	  dimensions[7]=0;
	
    for(i=0;i<m_extractednum;i++)
	  memcpy(m_lpDFeatureVector[i].m_dNormalizedFeature,m_lpDFeatureVector[i].m_dOriginalFeature,m_ffi.m_wTotalDimensions*sizeof(double));
	if(MyRetrieveMethod.FeatureDatabaseNormalizationandWeighting(m_lpDFeatureVector,m_extractednum,m_ffi.m_wTotalDimensions,dimensions,m_ffi.m_wWeights,m_lpDComponentInfo)<0)
	{
	  MessageBox(NULL,"Feature Vectors Normalization Error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_normalizednum=m_extractednum;
	m_bDatabaseFeatureNormalized=true;
	//++++++++++++++For standard database confirmation++++++++++++++++
    CFile fh;
	CFileException cfe;
	CString a,c,d;
	char b[20];
	strcpy(b,"");
	a=m_sDatabasePath;
	a+="Standard.txt";
	m_standard=FALSE;
	m_classes=0;
	m_imageineachclass=0;
	//classes: 10,20,25,40,50,80,100,200
	if(fh.Open(a,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	    fh.Read(b,18);
		b[18]='\0';
		a=b;
		if(a.Left(9)=="standard_")
		{
		  c=a.Right(9);
		  if(c.Left(4)=="10 _"||c.Left(4)=="20 _"||c.Left(4)=="25 _"||c.Left(4)=="40 _"||c.Left(4)=="50 _"||c.Left(4)=="80 _"||c.Left(4)=="100_"||c.Left(4)=="200_"||c.Left(4)=="250_"||c.Left(4)=="400_"||c.Left(4)=="500_")
		  {
		    d=a.Right(5);
			if(d.Left(5)=="100 _"||d.Left(5)=="200 _"||d.Left(5)=="250 _"||d.Left(5)=="400 _"||d.Left(5)=="500 _"||d.Left(5)=="800 _"||d.Left(5)=="1000_")
			{
			  if(c.Left(4)=="10 _")
			  	 m_classes=10;
			  else if(c.Left(4)=="20 _")
			     m_classes=20;
			  else if(c.Left(4)=="25 _")
				 m_classes=25;
			  else if(c.Left(4)=="40 _")
				 m_classes=40;
			  else if(c.Left(4)=="50 _")
				 m_classes=50;
			  else if(c.Left(4)=="80 _")
				 m_classes=80;
			  else if(c.Left(4)=="100_")
				 m_classes=100;
			  else if(c.Left(4)=="200_")
				 m_classes=200;
              else if(c.Left(4)=="250_")
				 m_classes=250;
              else if(c.Left(4)=="400_")
				 m_classes=400;
              else if(c.Left(4)=="500_")
				 m_classes=500;

			  if(d.Left(5)=="100 _")
			     m_imageineachclass=100;
			  if(d.Left(5)=="200 _")
			     m_imageineachclass=200;
			  if(d.Left(5)=="250 _")
			     m_imageineachclass=250;
			  if(d.Left(5)=="400 _")
			     m_imageineachclass=400;
			  else if(d.Left(5)=="500 _")
				 m_imageineachclass=500;
			  else if(d.Left(5)=="800 _")
			     m_imageineachclass=800;
			  else if(d.Left(5)=="1000_")
			     m_imageineachclass=1000;
			  m_standard=TRUE;
			}
		  }
		}
		fh.Close();
	}
	UpdateAllViews(NULL);
	EndWaitCursor();
}

void CVqRetrieveDoc::OnDatabaseSorting() 
{
	// TODO: Add your command handler code here
	BeginWaitCursor();
	MyRetrieveMethod.SortingByAverage(m_lpDFeatureVector,m_normalizednum);
	m_featuresorted=TRUE;
	m_clustersorted=FALSE;
	EndWaitCursor();
}

void CVqRetrieveDoc::OnDatabaseFeaturesave() 
{
	// TODO: Add your command handler code here
	CFile fdbfile;
	CFileException cfe;
	CString DataBaseFileName;
    int i;
	char BASED_CODE szFilter[]="Feature DataBase Files(*.fdb)|*.fdb|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(FALSE,"fdb",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="Save Feature File";
	if(m_ldFile.DoModal()!=IDOK)return;
	m_bFeatureFileSaved=false;
	DataBaseFileName=m_ldFile.GetPathName();
	m_savedfeaturefile=m_ldFile.GetFileName();
	while(m_ldFile.GetFileName().GetLength()<7)
	{
	  MessageBox(NULL,"Please input filename with more than 3 Characters","Information", MB_OK|MB_ICONINFORMATION);
	  if(m_ldFile.DoModal()!=IDOK)return;
	  m_bFeatureFileSaved=false;
	  DataBaseFileName=m_ldFile.GetPathName();
	}
	if(!fdbfile.Open(DataBaseFileName,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary,&cfe))
	{
	  m_savedfeaturefile="No feature file saved";
	  MessageBox(NULL,"Cannot create this file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	
	//write the m_ffi
	m_ffi.m_dwFileSize=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi.m_wTotalDimensions)*m_normalizednum+600+sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions;
	m_ffi.m_bEverInterrupted=m_bDatabaseFeatureInterrupted;
	m_ffi.m_bNextFile=FALSE;
	m_ffi.m_bSorted=m_featuresorted;
	m_ffi.m_bStandard=m_standard;
	m_ffi.m_wClasses=m_classes;
	m_ffi.m_wImageInEachClass=m_imageineachclass;
	m_ffi.m_bClustered=FALSE;
	m_ffi.m_wCodewordNumber=0;
    strcpy(m_ffi.m_sCodebookFileNameLast8,"boknone");	
	CString str;
	str=DataBaseFileName;
	strcpy(m_ffi.m_sThisFileNameLast8,str.Right(7));
	strcpy(m_ffi.m_sNextFileNameLast8,"fdbnone");
	m_ffi.m_dwFileNumber=m_normalizednum;
	strcpy(m_ffi.m_sPath,m_sDatabasePath);
    fdbfile.Write(&m_ffi,sizeof(FEATUREFILEINFO));
    fdbfile.Seek(600,CFile::begin);
    //Write the Featurevectors
	fdbfile.Write(m_lpDFeatureVector,sizeof(FEATUREVECTOR)*m_normalizednum);
	for(i=0;i<m_normalizednum;i++)
	{
	  fdbfile.Write(m_lpDFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi.m_wTotalDimensions);
	}
	for(i=0;i<m_normalizednum;i++)
	{
	  fdbfile.Write(m_lpDFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi.m_wTotalDimensions);
	}
	fdbfile.Write(m_lpDComponentInfo,sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions);
    if(m_ffi.m_dwFileSize!=fdbfile.GetLength())
	{
	  m_savedfeaturefile="No feature file saved";
	  fdbfile.Close();
	  MessageBox(NULL,"File saved error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	fdbfile.Close();
	m_bFeatureFileSaved=true;
	UpdateAllViews(NULL);
}

void CVqRetrieveDoc::OnDatabaseReadfromfile() 
{
	// TODO: Add your command handler code here
	DWORD a1;
	long int i;
	CFile fdbfile;
	CFileException cfe;
	CString DataBaseFileName,str;
	
	char BASED_CODE szFilter1[]="Feature DataBase Files(*.fdb)|*.fdb|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open Database File";
	if(m_ldFile.DoModal()!=IDOK)return;
	DataBaseFileName=m_ldFile.GetPathName();
	if(lastpathname0==DataBaseFileName)return;
	
	m_normalizednum=0;//no feature normalized
	m_clusters=10;//the number of clusters
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedvqfeaturefile="No vq feature file saved";
	m_bDatabaseFeatureNormalized=false;	//not normalized
	m_bDatabaseClustered=false;//not clustered
	m_bFeatureFileSaved=false;//not file saved
	m_bCodebookFileSaved=false;//
	m_bVQFeatureFileSaved=false;//
	m_featuresorted=FALSE;
	UpdateAllViews(NULL);
	
	BeginWaitCursor();
	if(!fdbfile.Open(DataBaseFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox(NULL,"Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_ffi
    if(fdbfile.Read(&m_ffi,sizeof(FEATUREFILEINFO))!=sizeof(FEATUREFILEINFO))
	{
	   fdbfile.Close();
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	if(m_ffi.m_wTotalDimensions<=0||m_ffi.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_ffi.m_wStructSize!=sizeof(FEATUREFILEINFO)||m_ffi.m_wOffBytes!=600\
	||strcmp(m_ffi.m_sThisFileNameLast8,DataBaseFileName.Right(7))!=0\
    ||m_ffi.m_bFeatureTypes<1||m_ffi.m_bFeatureTypes>7\
	||m_ffi.m_dwFileNumber<1||m_ffi.m_dwFileNumber>MAX_IMAGE_NUMBER||m_ffi.m_bClustered==TRUE)
	{
	  m_normalizednum=0;
	  fdbfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_normalizednum=m_ffi.m_dwFileNumber;
	a1=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi.m_wTotalDimensions)*m_normalizednum+600+sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions;
    if(a1!=fdbfile.GetLength()||m_ffi.m_dwFileSize!=a1)
	{
	  m_normalizednum=0;
	  fdbfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	
	m_hDFeatureVector=NULL;
	//reapply memory
    m_hDFeatureVector=GlobalAlloc(GMEM_FIXED,
	m_normalizednum*(sizeof(FEATUREVECTOR)+m_ffi.m_wTotalDimensions*2*sizeof(double))
	+m_ffi.m_wTotalDimensions*2*sizeof(double)
	+((m_ffi.m_wTotalDimensions+2)*sizeof(double)+sizeof(DWORD))*MAX_CODEBOOK_SIZE
	+sizeof(WORD)*m_normalizednum);
	
	if(m_hDFeatureVector==NULL)
	{
		fdbfile.Close();
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return;
	}
	///The address of m_lpRFeatureVectors
	m_lpDFeatureVector=(LPFEATUREVECTOR)m_hDFeatureVector;
	fdbfile.Seek(600,CFile::begin);

	//read the featurevectors
	if(fdbfile.Read(m_lpDFeatureVector,sizeof(FEATUREVECTOR)*m_normalizednum)!=sizeof(FEATUREVECTOR)*m_normalizednum)
	{
	    fdbfile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	//the memory for detail features
	for(i=0;i<m_normalizednum;i++)
	  m_lpDFeatureVector[i].m_dOriginalFeature=(double *)((char *)m_hDFeatureVector+m_normalizednum*sizeof(FEATUREVECTOR))+i*m_ffi.m_wTotalDimensions;
	for(i=0;i<m_normalizednum;i++)
	  m_lpDFeatureVector[i].m_dNormalizedFeature=m_lpDFeatureVector[0].m_dOriginalFeature+(i+m_normalizednum)*m_ffi.m_wTotalDimensions;
	m_wIndex=(WORD *)(m_lpDFeatureVector[0].m_dNormalizedFeature+m_normalizednum*m_ffi.m_wTotalDimensions);
	m_dwNumberinCluster=(DWORD *)(m_wIndex+m_normalizednum);
	m_dCodeword=(double *)(m_dwNumberinCluster+MAX_CODEBOOK_SIZE);
	///The address of m_lpDComponentInfo
	m_lpDComponentInfo=(LPCOMPONENTINFO)(m_dCodeword+(m_ffi.m_wTotalDimensions+2)*MAX_CODEBOOK_SIZE);
	
	//Read the detail Featurevectors
	for(i=0;i<m_normalizednum;i++)
	{
	  if(fdbfile.Read(m_lpDFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi.m_wTotalDimensions)!=sizeof(double)*m_ffi.m_wTotalDimensions)
	  {
	    fdbfile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	for(i=0;i<m_normalizednum;i++)
	{
	  if(fdbfile.Read(m_lpDFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi.m_wTotalDimensions)!=sizeof(double)*m_ffi.m_wTotalDimensions)
	  {
	    fdbfile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	//Read the Component Info
	if(fdbfile.Read(m_lpDComponentInfo,sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions)!=sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions)
	{
	   fdbfile.Close();
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	fdbfile.Close();
	lastpathname0=DataBaseFileName;
    m_sDatabasePath=m_ffi.m_sPath;
	if(m_ffi.m_bSorted==TRUE)
	{
		m_featuresorted=true;
		MessageBox(NULL,"The database opened is a sorted unclustered database","Info",MB_OK);
	}
	else
	{
		m_featuresorted=false;
		MessageBox(NULL,"The database opened is a unsorted unclustered database","Info",MB_OK);
	}
	m_bDatabaseFeatureNormalized=true;
   	UpdateAllViews(NULL);
	//++++++++++++++For standard database confirmation++++++++++++++++
    CFile fh;
//	CFileException cfe;
	CString a,c,d;
	char b[20];
	strcpy(b,"");
	a=m_sDatabasePath;
	a+="Standard.txt";
	m_standard=FALSE;
	m_classes=0;
	m_imageineachclass=0;
	//classes: 10,20,25,40,50,80,100,200
	if(fh.Open(a,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	    fh.Read(b,18);
		b[18]='\0';
		a=b;
		if(a.Left(9)=="standard_")
		{
		  c=a.Right(9);
		  if(c.Left(4)=="10 _"||c.Left(4)=="20 _"||c.Left(4)=="25 _"||c.Left(4)=="40 _"||c.Left(4)=="50 _"||c.Left(4)=="80 _"||c.Left(4)=="100_"||c.Left(4)=="200_"||c.Left(4)=="250_"||c.Left(4)=="400_"||c.Left(4)=="500_")
		  {
		    d=a.Right(5);
			if(d.Left(5)=="100 _"||d.Left(5)=="200 _"||d.Left(5)=="250 _"||d.Left(5)=="400 _"||d.Left(5)=="500 _"||d.Left(5)=="800 _"||d.Left(5)=="1000_")
			{
			  if(c.Left(4)=="10 _")
			  	 m_classes=10;
			  else if(c.Left(4)=="20 _")
			     m_classes=20;
			  else if(c.Left(4)=="25 _")
				 m_classes=25;
			  else if(c.Left(4)=="40 _")
				 m_classes=40;
			  else if(c.Left(4)=="50 _")
				 m_classes=50;
			  else if(c.Left(4)=="80 _")
				 m_classes=80;
			  else if(c.Left(4)=="100_")
				 m_classes=100;
			  else if(c.Left(4)=="200_")
				 m_classes=200;
              else if(c.Left(4)=="250_")
				 m_classes=250;
              else if(c.Left(4)=="400_")
				 m_classes=400;
              else if(c.Left(4)=="500_")
				 m_classes=500;

			  if(d.Left(5)=="100 _")
			     m_imageineachclass=100;
			  if(d.Left(5)=="200 _")
			     m_imageineachclass=200;
			  if(d.Left(5)=="250 _")
			     m_imageineachclass=250;
			  if(d.Left(5)=="400 _")
			     m_imageineachclass=400;
			  else if(d.Left(5)=="500 _")
				 m_imageineachclass=500;
			  else if(d.Left(5)=="800 _")
			     m_imageineachclass=800;
			  else if(d.Left(5)=="1000_")
			     m_imageineachclass=1000;
			  m_standard=TRUE;
			}
		  }
		}
		fh.Close();
	}
    EndWaitCursor();

}

void CVqRetrieveDoc::OnDatabaseNfeaturespacevq() 
{
	// TODO: Add your command handler code here
	if(m_bDatabaseClustered==true&&::AfxMessageBox("The database path hasn't been changed, do you want to reclustering the feature vectors,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	m_savedcodebookfile="No codebook file saved";
	m_savedvqfeaturefile="No vq feature file saved";
	m_bDatabaseClustered=false;//not clustered
	m_bCodebookFileSaved=false;//
	m_bVQFeatureFileSaved=false;//
	UpdateAllViews(NULL);
	BeginWaitCursor();
	WORD Iterations; 
	double Time,PSNR,MSE;
	if(MyRetrieveMethod.LBGCodebookDesign(m_normalizednum,m_clusters,m_ffi.m_wTotalDimensions,0.00001,m_lpDFeatureVector[0].m_dNormalizedFeature,m_dCodeword,m_wIndex,m_dwNumberinCluster,&MSE,&PSNR,&Time,&Iterations)<0)
	{
		MessageBox(NULL,"Parameter Error","Error",MB_OK|MB_ICONSTOP);
		return;
	}
    m_bDatabaseClustered=true;
	UpdateAllViews(NULL);
	EndWaitCursor();
}

void CVqRetrieveDoc::OnUpdateDatabaseReadfromfile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


void CVqRetrieveDoc::OnDatabaseClustersorting() 
{
	// TODO: Add your command handler code here
	BeginWaitCursor();
	MyRetrieveMethod.ClusterSortingByAverage(m_lpDFeatureVector,m_dCodeword,m_wIndex,m_normalizednum,m_clusters);
	m_clustersorted=true;
	m_featuresorted=false;
	EndWaitCursor();
}

void CVqRetrieveDoc::OnDatabaseCodewordssave() 
{
	// TODO: Add your command handler code here
    CFile bokfile;
	CFileException cfe;
	CString CodebookFileName;
	char BASED_CODE szFilter[]="Codebook Files(*.bok)|*.bok|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(FALSE,"bok",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="Save Codebook File";
	if(m_ldFile.DoModal()!=IDOK)return;
	m_bCodebookFileSaved=false;
	CodebookFileName=m_ldFile.GetPathName();
	m_savedcodebookfile=m_ldFile.GetFileName();
	while(m_ldFile.GetFileName().GetLength()<7)
	{
	  MessageBox(NULL,"Please input filename with more than 3 Characters","Information", MB_OK|MB_ICONINFORMATION);
	  if(m_ldFile.DoModal()!=IDOK)return;
	  m_bCodebookFileSaved=false;
	  CodebookFileName=m_ldFile.GetPathName();
	  m_savedcodebookfile=m_ldFile.GetFileName();
	}
	if(!bokfile.Open(CodebookFileName,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary,&cfe))
	{
	  m_savedcodebookfile="No codebook file saved";
	  MessageBox(NULL,"Cannot create this file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	//write the m_cfh
	m_cfh.m_bFeatureTypes=m_ffi.m_bFeatureTypes;
	m_cfh.m_bNormalization=0; //reserved to be 0
	m_cfh.m_bWithColor=m_ffi.m_bWithColor;
	m_cfh.m_bWithRTInvariant=m_ffi.m_bWithRTInvariant;
	m_cfh.m_bWithTexture=m_ffi.m_bWithTexture;
	m_cfh.m_bWithShape=m_ffi.m_bWithShape;
	m_cfh.m_bWithOthers=m_ffi.m_bWithOthers;
	m_cfh.m_dwFileSize=128+sizeof(double)*(m_ffi.m_wTotalDimensions+2)*m_clusters;
	m_cfh.m_dwTrainingVectorNumber=m_normalizednum;
	m_cfh.m_wCodewordNumber=m_clusters;
	m_cfh.m_wDimension_CF=m_ffi.m_wDimension_CF;
	m_cfh.m_wDimension_IF=m_ffi.m_wDimension_IF;
	m_cfh.m_wDimension_OF=m_ffi.m_wDimension_OF;
	m_cfh.m_wDimension_SF=m_ffi.m_wDimension_SF;
	m_cfh.m_wDimension_TF=m_ffi.m_wDimension_TF;
	m_cfh.m_wOffBytes=128;
	m_cfh.m_wStructSize=sizeof(CODEBOOKFILEHEADER);
	m_cfh.m_wTotalDimensions=m_ffi.m_wTotalDimensions;
	CString str;
	str=CodebookFileName;
	strcpy(m_cfh.m_sThisFileNameLast8,str.Right(7));
    bokfile.Write(&m_cfh,sizeof(CODEBOOKFILEHEADER));
    bokfile.Seek(128,CFile::begin);
    //Write the Codeword
	bokfile.Write(m_dCodeword,m_cfh.m_dwFileSize-128);
    if(m_cfh.m_dwFileSize!=bokfile.GetLength())
	{
	  bokfile.Close();
	  MessageBox(NULL,"File saved error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	bokfile.Close();
	m_bCodebookFileSaved=true;
	UpdateAllViews(NULL);
}

void CVqRetrieveDoc::OnDatabaseVQFeaturesave() 
{
	// TODO: Add your command handler code here
	CFile vqffile;
	FEATUREFILEINFO vqffi;
	CString str;
	CFileException cfe;
	CString VQFeatureFileName;
	long int j,l;
    int p;
	DWORD *ind=new DWORD[m_normalizednum];
	char BASED_CODE szFilter[]="VQ Feature Files(*.vqf)|*.vqf|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(FALSE,"vqf",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="Save VQ Feature File";
	if(m_ldFile.DoModal()!=IDOK)return;
	m_bVQFeatureFileSaved=false;
    VQFeatureFileName=m_ldFile.GetPathName();
	m_savedvqfeaturefile=m_ldFile.GetFileName();
	while(m_ldFile.GetFileName().GetLength()<7)
	{
	  MessageBox(NULL,"Please input filename with more than 3 Characters","Information", MB_OK|MB_ICONINFORMATION);
	  if(m_ldFile.DoModal()!=IDOK)return;
	  m_bVQFeatureFileSaved=false;
	  VQFeatureFileName=m_ldFile.GetPathName();
	  m_savedvqfeaturefile=m_ldFile.GetFileName();
	}
	if(!vqffile.Open(VQFeatureFileName,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary,&cfe))
	{
	  m_savedvqfeaturefile="No vq feature file saved";
	  MessageBox(NULL,"Cannot create this file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
    
	//+++++++++++get vqffi
	memcpy(&vqffi,&m_ffi,sizeof(FEATUREFILEINFO));//copy from m_ffi
    //modify info
	vqffi.m_dwFileSize=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi.m_wTotalDimensions)*m_normalizednum+600+sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions+m_clusters*sizeof(DWORD);
	vqffi.m_bEverInterrupted=m_bDatabaseFeatureInterrupted;
	vqffi.m_bNextFile=FALSE;
	vqffi.m_bStandard=m_standard;
	vqffi.m_wClasses=m_classes;
	vqffi.m_wImageInEachClass=m_imageineachclass;
	vqffi.m_bSorted=m_clustersorted;
	vqffi.m_bClustered=TRUE;
	vqffi.m_wCodewordNumber=m_clusters;
    strcpy(vqffi.m_sCodebookFileNameLast8,m_cfh.m_sThisFileNameLast8);
	str=VQFeatureFileName;
	strcpy(vqffi.m_sThisFileNameLast8,str.Right(7));
	strcpy(vqffi.m_sNextFileNameLast8,"vqfnone");
	vqffi.m_dwFileNumber=m_normalizednum;
	strcpy(vqffi.m_sPath,m_sDatabasePath);
  
	//++++++++++++write the vqffi
	vqffile.Write(&vqffi,sizeof(FEATUREFILEINFO));

    vqffile.Seek(600,CFile::begin);

    //++++++++++++++Write the vector number in each cluster
	vqffile.Write(m_dwNumberinCluster,sizeof(DWORD)*m_clusters);
	
    //Write the Featurevectors
    for(p=0;p<m_clusters;p++)
	{
	   l=0;
	   for(j=0;j<m_normalizednum;j++)
	   {
	     if(m_wIndex[j]==p)
		 {
	       ind[l]=j;
		   l++;
		 }
	   }
	   for(j=0;j<l;j++)
	     vqffile.Write(&m_lpDFeatureVector[ind[j]],sizeof(FEATUREVECTOR));
	}

    for(p=0;p<m_clusters;p++)
	{
	   l=0;
	   for(j=0;j<m_normalizednum;j++)
	   {
	     if(m_wIndex[j]==p)
		 {
	        ind[l]=j;
			l++;
		 }
	   }
	   for(j=0;j<l;j++)
	  vqffile.Write(m_lpDFeatureVector[ind[j]].m_dOriginalFeature,sizeof(double)*m_ffi.m_wTotalDimensions);
	}

	for(p=0;p<m_clusters;p++)
	{
	   l=0;
	   for(j=0;j<m_normalizednum;j++)
	   {
	     if(m_wIndex[j]==p)
		 {
	        ind[l]=j;
			 l++;
		 }
	   }
	   for(j=0;j<l;j++)
		   vqffile.Write(m_lpDFeatureVector[ind[j]].m_dNormalizedFeature,sizeof(double)*m_ffi.m_wTotalDimensions);
	}
	
	//write componentInfo
	vqffile.Write(m_lpDComponentInfo,sizeof(COMPONENTINFO)*m_ffi.m_wTotalDimensions);
	delete [] ind;
    if(vqffi.m_dwFileSize!=vqffile.GetLength())
	{
	  m_savedfeaturefile="No vq feature file saved";
	  vqffile.Close();
	  MessageBox(NULL,"File saved error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	vqffile.Close();
	m_bVQFeatureFileSaved=true;
	UpdateAllViews(NULL);
}

void CVqRetrieveDoc::OnRetrieveFeaturefile() 
{
	// TODO: Add your command handler code here
	DWORD a;
	long int i;
	CFile fdbfile;
	CFileException cfe;
	CString DataBaseFileName,str;
	
	char BASED_CODE szFilter1[]="Feature DataBase Files(*.fdb)|*.fdb|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open Database File";
	if(m_ldFile.DoModal()!=IDOK)return;
	DataBaseFileName=m_ldFile.GetPathName();
	if(lastpathname==DataBaseFileName)return;
	RetrievalStatusIntial();
	if(!fdbfile.Open(DataBaseFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox(NULL,"Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_ffi_fromfile
    if(fdbfile.Read(&m_ffi_fromfile,sizeof(FEATUREFILEINFO))!=sizeof(FEATUREFILEINFO))
	{
	   fdbfile.Close();
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	if(m_ffi_fromfile.m_wTotalDimensions<=0||m_ffi_fromfile.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_ffi_fromfile.m_wStructSize!=sizeof(FEATUREFILEINFO)||m_ffi_fromfile.m_wOffBytes!=600\
	||strcmp(m_ffi_fromfile.m_sThisFileNameLast8,DataBaseFileName.Right(7))!=0\
    ||m_ffi_fromfile.m_bFeatureTypes<1||m_ffi_fromfile.m_bFeatureTypes>7\
	||m_ffi_fromfile.m_dwFileNumber<1||m_ffi_fromfile.m_dwFileNumber>MAX_IMAGE_NUMBER||m_ffi_fromfile.m_bClustered==TRUE)
	{
	  m_validnum_r=0;
	  fdbfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_validnum_r=m_ffi_fromfile.m_dwFileNumber;
	a=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)*m_validnum_r+600+sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions;
    if(a!=fdbfile.GetLength()||m_ffi_fromfile.m_dwFileSize!=a)
	{
	  m_validnum_r=0;
	  fdbfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	//apply memory
    //m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,m_validnum_r*(sizeof(FEATUREVECTOR)+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double))+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double));
    m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,
	m_validnum_r*(sizeof(FEATUREVECTOR)+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double))
	+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double)
	+((m_ffi_fromfile.m_wTotalDimensions+2)*sizeof(double)+sizeof(DWORD))*MAX_CODEBOOK_SIZE
	+sizeof(WORD)*m_validnum_r);
	
	if(m_hRFeatureVector==NULL)
	{
		fdbfile.Close();
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return;
	}
	///The address of m_lpRFeatureVectors
	m_lpRFeatureVector=(LPFEATUREVECTOR)m_hRFeatureVector;
	fdbfile.Seek(600,CFile::begin);

	//read the featurevectors
	if(fdbfile.Read(m_lpRFeatureVector,sizeof(FEATUREVECTOR)*m_validnum_r)!=sizeof(FEATUREVECTOR)*m_validnum_r)
	{
	    fdbfile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	//the memory for detail features
	for(i=0;i<m_validnum_r;i++)
	  m_lpRFeatureVector[i].m_dOriginalFeature=(double *)((char *)m_hRFeatureVector+m_validnum_r*sizeof(FEATUREVECTOR))+i*m_ffi_fromfile.m_wTotalDimensions;
	for(i=0;i<m_validnum_r;i++)
	  m_lpRFeatureVector[i].m_dNormalizedFeature=m_lpRFeatureVector[0].m_dOriginalFeature+(i+m_validnum_r)*m_ffi_fromfile.m_wTotalDimensions;
	m_lpRComponentInfo=(LPCOMPONENTINFO)(m_lpRFeatureVector[0].m_dNormalizedFeature+m_validnum_r*m_ffi_fromfile.m_wTotalDimensions);
	//Read the detail Featurevectors
	for(i=0;i<m_validnum_r;i++)
	{
	  if(fdbfile.Read(m_lpRFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
	  {
	    fdbfile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	for(i=0;i<m_validnum_r;i++)
	{
	  if(fdbfile.Read(m_lpRFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
	  {
	    fdbfile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	//Read the Component Info
	if(fdbfile.Read(m_lpRComponentInfo,sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)
	{
	   fdbfile.Close();
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	fdbfile.Close();
	lastpathname=DataBaseFileName;
	m_readfeaturename=m_ldFile.GetFileName();
    m_sRetrievePath=m_ffi_fromfile.m_sPath;
	m_featuredimension=m_ffi_fromfile.m_wTotalDimensions;
	if(m_ffi_fromfile.m_bEverInterrupted==TRUE)
	  m_everinterrupted="TRUE";
	else
	  m_everinterrupted="FALSE";
	m_bFeatureFileOpened=true;
	if(m_ffi_fromfile.m_bSorted==TRUE)
	{
		m_bSorted=true;
		MessageBox(NULL,"The database opened is a sorted unclustered database","Info",MB_OK);
	}
	else
	{
		m_bSorted=false;
		MessageBox(NULL,"The database opened is a unsorted unclustered database","Info",MB_OK);
	}
   	UpdateAllViews(NULL);
}

void CVqRetrieveDoc::OnRetrieveFeatureselected() 
{
	// TODO: Add your command handler code here
	CDialogFeatureSelection dfs;
	dfs.ffi=m_ffi_fromfile;
	dfs.readonly=TRUE;
	dfs.DoModal();
}

void CVqRetrieveDoc::OnRetrieveVQFeatureFile() 
{
	// TODO: Add your command handler code here
	DWORD a;
	long int i;
	CFile vqffile;
	CFileException cfe;
	CString VQFeatureFileName,str;
	
	char BASED_CODE szFilter1[]="VQ Feature DataBase Files(*.vqf)|*.vqf|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open VQ Feature File";
	if(m_ldFile.DoModal()!=IDOK)return;
	VQFeatureFileName=m_ldFile.GetPathName();
	if(lastpathname1==VQFeatureFileName)return;
	RetrievalStatusIntial();
	if(!vqffile.Open(VQFeatureFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox(NULL,"Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_ffi_fromfile
    if(vqffile.Read(&m_ffi_fromfile,sizeof(FEATUREFILEINFO))!=sizeof(FEATUREFILEINFO))
	{
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	if(m_ffi_fromfile.m_wTotalDimensions<=0||m_ffi_fromfile.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_ffi_fromfile.m_wStructSize!=sizeof(FEATUREFILEINFO)||m_ffi_fromfile.m_wOffBytes!=600\
	||strcmp(m_ffi_fromfile.m_sThisFileNameLast8,VQFeatureFileName.Right(7))!=0\
    ||m_ffi_fromfile.m_bFeatureTypes<1||m_ffi_fromfile.m_bFeatureTypes>7\
	||m_ffi_fromfile.m_dwFileNumber<1||m_ffi_fromfile.m_dwFileNumber>MAX_IMAGE_NUMBER||m_ffi_fromfile.m_bClustered==FALSE)
	{
	  m_validnum_r=0;
	  vqffile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_validnum_r=m_ffi_fromfile.m_dwFileNumber;
	a=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)*m_validnum_r+600+sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD);
    if(a!=vqffile.GetLength()||m_ffi_fromfile.m_dwFileSize!=a)
	{
	  m_validnum_r=0;
	  vqffile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	//apply memory
    m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,m_validnum_r*(sizeof(FEATUREVECTOR)+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double))+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double)+(m_ffi_fromfile.m_wTotalDimensions+2)*sizeof(double)*m_ffi_fromfile.m_wCodewordNumber+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD));
	if(m_hRFeatureVector==NULL)
	{
		vqffile.Close();
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return;
	}
	///The address of m_lpRFeatureVectors
	m_lpRFeatureVector=(LPFEATUREVECTOR)m_hRFeatureVector;
	vqffile.Seek(600+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD),CFile::begin);

	//read the featurevectors
	if(vqffile.Read(m_lpRFeatureVector,sizeof(FEATUREVECTOR)*m_validnum_r)!=sizeof(FEATUREVECTOR)*m_validnum_r)
	{
	    vqffile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	//the memory for detail features
	for(i=0;i<m_validnum_r;i++)
	  m_lpRFeatureVector[i].m_dOriginalFeature=(double *)((char *)m_hRFeatureVector+m_validnum_r*sizeof(FEATUREVECTOR))+i*m_ffi_fromfile.m_wTotalDimensions;
	for(i=0;i<m_validnum_r;i++)
	  m_lpRFeatureVector[i].m_dNormalizedFeature=m_lpRFeatureVector[0].m_dOriginalFeature+(i+m_validnum_r)*m_ffi_fromfile.m_wTotalDimensions;
	m_dwNuminEachCluster_r=(DWORD *)(m_lpRFeatureVector[0].m_dNormalizedFeature+m_validnum_r*m_ffi_fromfile.m_wTotalDimensions);
	m_dCodeword_r=(double *)(m_dwNuminEachCluster_r+m_ffi_fromfile.m_wCodewordNumber);
	///The address of m_lpRComponentInfo
	m_lpRComponentInfo=(LPCOMPONENTINFO)(m_dCodeword_r+(m_ffi_fromfile.m_wTotalDimensions+2)*m_ffi_fromfile.m_wCodewordNumber);
   
	//Read the numineachcluster
	vqffile.Seek(600,CFile::begin);
    if(vqffile.Read(m_dwNuminEachCluster_r,m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD))!=m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD))
	{
	    vqffile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	vqffile.Seek(600+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD)+sizeof(FEATUREVECTOR)*m_validnum_r,CFile::begin);
	
	//Read the detail Featurevectors
	for(i=0;i<m_validnum_r;i++)
	{
	  if(vqffile.Read(m_lpRFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
	  {
	    vqffile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	for(i=0;i<m_validnum_r;i++)
	{
	  if(vqffile.Read(m_lpRFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
	  {
	    vqffile.Close();
		MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	//Read the Component Info
	if(vqffile.Read(m_lpRComponentInfo,sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)
	{
	   vqffile.Close();
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	vqffile.Close();
	lastpathname1=VQFeatureFileName;
	m_readfeaturename=m_ldFile.GetFileName();
    m_sRetrievePath=m_ffi_fromfile.m_sPath;
	m_featuredimension=m_ffi_fromfile.m_wTotalDimensions;
	if(m_ffi_fromfile.m_bEverInterrupted==TRUE)
	  m_everinterrupted="TRUE";
	else
	  m_everinterrupted="FALSE";
	m_bFeatureFileOpened=true;
	if(m_ffi_fromfile.m_bSorted==TRUE)
	{
		m_bSorted=true;
		MessageBox(NULL,"The database opened is a sorted clustered database","Info",MB_OK);
	}
	else
	{
		m_bSorted=false;
		MessageBox(NULL,"The database opened is a unsorted clustered database","Info",MB_OK);
	}
   	UpdateAllViews(NULL);
}
void CVqRetrieveDoc::OnRetrieveClusteringbook() 
{
	// TODO: Add your command handler code here
	DWORD a;
	CFile bokfile;
	CFileException cfe;
	CString CodebookFileName,str;
	
	char BASED_CODE szFilter1[]="Codebook Files(*.bok)|*.bok|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open Codebook File";
	if(m_ldFile.DoModal()!=IDOK)return;
	CodebookFileName=m_ldFile.GetPathName();
	if(lastpathname2==CodebookFileName)return;
	m_bCodebookFileOpened=false;
	m_bFeatureFileOpened=false;
	m_bRetrieving=false;  //No retrieving
	m_bRetrieveDisplay=false;    //No retrieval results
    m_iRetrieveMethod=0;
	m_iSimpleFeedBackMethod=0;
	m_bQueryImageNormalized=false;
	m_readbookname="No codebook file opened";
	lastpathname1="";
	lastpathname2="";
	m_basedonnormalized=true;
	m_clustersused=0;
	m_retrievednum=0;
	if(!bokfile.Open(CodebookFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox(NULL,"Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_cfh_fromfile
    if(bokfile.Read(&m_cfh_fromfile,sizeof(CODEBOOKFILEHEADER))!=sizeof(CODEBOOKFILEHEADER))
	{
	  bokfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	
	if(m_cfh_fromfile.m_wTotalDimensions<=0||m_cfh_fromfile.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_cfh_fromfile.m_wStructSize!=sizeof(CODEBOOKFILEHEADER)||m_cfh_fromfile.m_wOffBytes!=128\
	||strcmp(m_cfh_fromfile.m_sThisFileNameLast8,CodebookFileName.Right(7))!=0\
    ||m_cfh_fromfile.m_bFeatureTypes<1||m_cfh_fromfile.m_bFeatureTypes>7\
	||m_cfh_fromfile.m_dwTrainingVectorNumber<1||m_cfh_fromfile.m_dwTrainingVectorNumber>MAX_IMAGE_NUMBER\
	||m_cfh_fromfile.m_wCodewordNumber>m_cfh_fromfile.m_dwTrainingVectorNumber\
	||m_cfh_fromfile.m_wCodewordNumber>MAX_CODEBOOK_SIZE||m_cfh_fromfile.m_wCodewordNumber<1\
	||m_cfh_fromfile.m_wCodewordNumber!=m_ffi_fromfile.m_wCodewordNumber\
	||strcmp(m_cfh_fromfile.m_sThisFileNameLast8,m_ffi_fromfile.m_sCodebookFileNameLast8)!=0)
	{
	  bokfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the codebook file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_clustersused=m_cfh_fromfile.m_wCodewordNumber;
	a=sizeof(double)*(m_cfh_fromfile.m_wTotalDimensions+2)*m_clustersused+128;
    if(a!=bokfile.GetLength()||m_cfh_fromfile.m_dwFileSize!=a)
	{
	  m_clustersused=0;
	  bokfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	bokfile.Seek(128,CFile::begin);

	//read the codewords
	if(bokfile.Read(m_dCodeword_r,sizeof(double)*(m_cfh_fromfile.m_wTotalDimensions+2)*m_clustersused)!=sizeof(double)*(m_cfh_fromfile.m_wTotalDimensions+2)*m_clustersused)
	{
	    m_clustersused=0;
	    bokfile.Close();
	    UpdateAllViews(NULL);
	    MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	bokfile.Close();
	lastpathname2=CodebookFileName;
	m_readbookname=m_ldFile.GetFileName();
	if(m_cfh_fromfile.m_bNormalization==0)
	  m_basedonnormalized="TRUE";
	else
	  m_basedonnormalized="FALSE";
    m_bCodebookFileOpened=true;
	m_bFeatureFileOpened=true;
	UpdateAllViews(NULL);
}

void CVqRetrieveDoc::OnRetrieveNormal() 
{
	// TODO: Add your command handler code here
	m_iRetrieveMethod=0;  ///The method 0
}

void CVqRetrieveDoc::OnRetrieveUpdatingfs() 
{
	// TODO: Add your command handler code here
	m_iRetrieveMethod=1;  ///The method 1	
}

void CVqRetrieveDoc::OnRetrieveEknns() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=2;  ///The method 2
}
void CVqRetrieveDoc::OnRetrieveIeknnsuser() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=3;  ///The method 3
	
}

void CVqRetrieveDoc::OnRetrieveIeknnsback() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=4;  ///The method 4
}
void CVqRetrieveDoc::OnRetrieveEeknns() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=5;  ///The method 5
	
}

void CVqRetrieveDoc::OnRetrieveIeeknnsuser() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=6;  ///The method 6
}

void CVqRetrieveDoc::OnRetrieveIeeknnsback() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=7;  ///The method 7
}

void CVqRetrieveDoc::OnRetrieveEeeknns() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=8;  ///The method 8	
}
void CVqRetrieveDoc::OnRetrieveIeeeknnsuser() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=9;  ///The method 9	
}

void CVqRetrieveDoc::OnRetrieveIeeeknnsback() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if(m_bSorted==false||m_ffi_fromfile.m_bClustered==TRUE)return;
	m_iRetrieveMethod=10;  ///The method 10	
}

void CVqRetrieveDoc::OnRetrieveVqonlynnc() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false)return;
	if(m_bCodebookFileOpened==false||m_bFeatureFileOpened==false||(m_bFeatureFileOpened==true&&m_ffi_fromfile.m_bClustered==FALSE))return;
	m_iRetrieveMethod=11;  ///The method 11
}

void CVqRetrieveDoc::OnRetrieveVqonlyknncs() 
{
	// TODO: Add your command handler code here
    if(m_bSorted==false)return;
	if(m_bCodebookFileOpened==false||m_bFeatureFileOpened==false||(m_bFeatureFileOpened==true&&m_ffi_fromfile.m_bClustered==FALSE))return;
	m_iRetrieveMethod=12;  ///The method 12
}

void CVqRetrieveDoc::OnRetrieveVqallclusters() 
{
	// TODO: Add your command handler code here
    if(m_bSorted==false)return;
	if(m_bCodebookFileOpened==false||m_bFeatureFileOpened==false||(m_bFeatureFileOpened==true&&m_ffi_fromfile.m_bClustered==FALSE))return;
	m_iRetrieveMethod=13;  ///The method 13
}

void CVqRetrieveDoc::OnRetrieveFeedbacknomemory() 
{
	// TODO: Add your command handler code here
	m_iSimpleFeedBackMethod=0;
}
void CVqRetrieveDoc::OnRetrieveFeedbackwithmemory() 
{
	// TODO: Add your command handler code here
	if(m_iSimpleFeedBackMethod==0)m_Iterations=0;
	m_iSimpleFeedBackMethod=1;
	CDialogFeedbakWithMemory fbm;
	fbm.m_T1=m_T1;
	fbm.m_T2=m_T2;
	if(fbm.DoModal()==IDOK)
	{
       m_T1=fbm.m_T1;
	   m_T2=fbm.m_T2;
	   fbm.ComputeMemoryWeights(weights);
	}
}
void CVqRetrieveDoc::OnRetrievePages1() 
{
	// TODO: Add your command handler code here
	m_page_setting=1;//The number of returned pages  1
}
void CVqRetrieveDoc::OnRetrievePages10() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<10)return;
	m_page_setting=10;
}

void CVqRetrieveDoc::OnRetrievePages15() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<15)return;
	m_page_setting=15;	
}
void CVqRetrieveDoc::OnRetrievePages20() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<20)return;
	m_page_setting=20;	
}
void CVqRetrieveDoc::OnRetrievePages25() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<25)return;
	m_page_setting=25;
}

void CVqRetrieveDoc::OnRETRIEVEPAGES1AND1Image() 
{
	// TODO: Add your command handler code here
	m_page_setting=0;
}
void CVqRetrieveDoc::OnRetrievePages2() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<2)return;
	m_page_setting=2;//The number of returned pages  1
}
void CVqRetrieveDoc::OnRetrievePages3() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<3)return;
	m_page_setting=3;
}
void CVqRetrieveDoc::OnRetrievePages4() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<4)return;
	m_page_setting=4;
}
void CVqRetrieveDoc::OnRetrievePages5() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<5)return;
	m_page_setting=5;
}
void CVqRetrieveDoc::OnRetrievePages6() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<6)return;
	m_page_setting=6;
}
void CVqRetrieveDoc::OnRetrievePages7() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<7)return;
	m_page_setting=7;
}
void CVqRetrieveDoc::OnRetrievePages8() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<8)return;
	m_page_setting=8;
}
void CVqRetrieveDoc::OnRetrievePages9() 
{
	// TODO: Add your command handler code here
	if((m_ffi_fromfile.m_dwFileNumber-1)/16+1<9)return;
	m_page_setting=9;
}void CVqRetrieveDoc::OnRetrievePagesall() 
{
	// TODO: Add your command handler code here
	m_page_setting=-1;
}
void CVqRetrieveDoc::OnRetrieveStart() 
{
	// TODO: Add your command handler code here
	if(m_bQueryFileChanged==false&&m_bRetrieved==true&&oldmethod==m_iRetrieveMethod&&::AfxMessageBox("The database path, query image and the retrieval method haven't been changed, do you want to restart the same retrieval process,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)return;
	m_hResult=NULL;
	m_hResult=GlobalAlloc(GMEM_FIXED,sizeof(RETRIEVEDRESULT)*m_ffi_fromfile.m_dwFileNumber);
	if(m_hResult==NULL)
	{
	  MessageBox(NULL,"Memory not enough","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	RetrievedResult=(LPRETRIEVEDRESULT)m_hResult;
	oldmethod=m_iRetrieveMethod;
	m_bRetrieveInterrupt=false;
	m_bRetrieved=false;
	m_bRetrieving=true;
	m_bRetrieveDisplay=false;     ///Retrieval success?
	m_displaypage=0;
	m_page_setting_saved=m_page_setting;
	m_retrievednum=0;
	UpdateAllViews(NULL);
	int a=0;
	if(SearchIndexList!=NULL)
	{
	    GlobalFree(SearchIndexList);
		SearchIndexList=NULL;
	}
	if(m_iRetrieveMethod>2&&m_iRetrieveMethod<11&&m_iRetrieveMethod!=5&&m_iRetrieveMethod!=8)
	{
	    hsil=GlobalAlloc(GMEM_FIXED, sizeof(DWORD)*m_validnum_r);
		if(hsil==NULL)
		{
	       MessageBox(NULL,"Memory not enough","Error",MB_OK|MB_ICONSTOP);
		   GlobalFree(m_hResult);
	       return;
		}
		SearchIndexList=(DWORD *)hsil;
		for(int l=0;l<m_validnum_r;l++)SearchIndexList[l]=l;
	}
	time1=clock();
	switch(m_iRetrieveMethod)
	 {
        case 0://Normal full search retrieval
	 	  BeginWaitCursor();
		  a=FullSearchRetrieveMethod();
		  time2=clock();
		  timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 1://Updating
	 	  a=UpdatingFullSearchRetrieveMethod();
		  time2=clock();
		  timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		break;
	    case 2://EKNNS
	 	  BeginWaitCursor();
		  EKNNSRetrieveMethod();
		  time2=clock();
	      //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 3://IEKNNS Search User
		  BeginWaitCursor();
		  IEKNNSURetrieveMethod();
		  processedpages=1;
		  time2=clock();
	      //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 4://IEKNNS Search Back
	 	  IEKNNSBRetrieveMethod();
		  time2=clock();
		  //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  GlobalFree(SearchIndexList);
		  SearchIndexList=NULL;
		break;
	    case 5://EEKNNS
	 	  BeginWaitCursor();
		  EEKNNSRetrieveMethod();
		  time2=clock();
	      //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 6://IEEKNNS Search User
		  BeginWaitCursor();
		  IEEKNNSURetrieveMethod();
		  processedpages=1;
		  time2=clock();
	      //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 7://IEEKNNS Search Back
	 	  IEEKNNSBRetrieveMethod();
		  time2=clock();
		  //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  GlobalFree(SearchIndexList);
		  SearchIndexList=NULL;
		break;
	    case 8://EEEKNNS
	 	  BeginWaitCursor();
		  EEEKNNSRetrieveMethod();
		  time2=clock();
	      //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 9://IEEEKNNS Search User
		  BeginWaitCursor();
		  IEEEKNNSURetrieveMethod();
		  processedpages=1;
		  time2=clock();
	      //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 10://IEEEKNNS Search Back
	 	  IEEEKNNSBRetrieveMethod();
		  time2=clock();
		  //if(m_validnum_r<=1000)
			// timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  //else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  GlobalFree(SearchIndexList);
		  SearchIndexList=NULL;
		break;
	    case 11://EEENNSinVQNN Search
	 	  BeginWaitCursor();
		  EEEKNNSinVQNNRetrieveMethod();
		  time2=clock();
	      timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
	    break;
	    case 12://EEENNSinVQKNN Search
	 	  BeginWaitCursor();
		  UpdatingEEEKNNSinVQKNNRetrieveMethod();
		  time2=clock();
	      timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		  break;
	    case 13://EEENNSinAllVQ Search
	 	  BeginWaitCursor();
		  UpdatingEEEKNNSinAllVQRetrieveMethod();
		  time2=clock();
	      timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    default:
	    break;
	}
	if(a==1)
	{
		MessageBox(NULL,"Retrieval Process Interrupted","Information",MB_OK|MB_ICONINFORMATION);//extraction now
	}
	m_sCostAllTime.Empty();
	m_sCostAllTime.Format("%s%f",m_sCostAllTime,timecost);
	m_bRetrieved=true;     ///Retrieval success
	m_bRetrieving=false;
	m_bQueryFileChanged=false;
	DisplayPage(m_displaypage);
}
void CVqRetrieveDoc::OnRetrieveStop() 
{
	// TODO: Add your command handler code here
	m_bRetrieveInterrupt=true;
	m_bRetrieving=false;
	if(m_retrievednum==m_validnum_r)m_bRetrieveInterrupt=false;
}
void CVqRetrieveDoc::OnDisplayFirst() 
{
	// TODO: Add your command handler code here
	m_displaypage=0;
	DisplayPage(m_displaypage);
}

void CVqRetrieveDoc::OnDisplayLast() 
{
	// TODO: Add your command handler code here
	//
	if(m_page_setting_saved>0)
	  m_displaypage=m_page_setting_saved-1;
	else if(m_page_setting_saved==0)
	  m_displaypage=0;
	else
	{
	  if(m_retrievednum%16==0)
	    m_displaypage=m_retrievednum/16-1;
	  else
	    m_displaypage=m_retrievednum/16;
	}
	DisplayPage(m_displaypage);
}

void CVqRetrieveDoc::OnDisplayPrevious() 
{
	// TODO: Add your command handler code here
	if(m_displaypage<=0)return;
	m_displaypage=m_displaypage-1;
	DisplayPage(m_displaypage);
}

void CVqRetrieveDoc::OnDisplayNext() 
{
	// TODO: Add your command handler code here
	double timeused=0.0;
	if(m_page_setting_saved>0)
	  if(m_displaypage>=m_page_setting_saved-1)return;
	else if(m_page_setting_saved==0)
	  if(m_displaypage>=0)return;
	else
	{
	  if(m_retrievednum%16==0)
	  {
	    if(m_displaypage>=m_retrievednum/16-1)return;
	  }
	  else
	  {
	    if(m_displaypage>=m_retrievednum/16)return;
	  }
	}
	if(oldmethod==3)
	{
	  if((m_page_setting_saved>0&&processedpages==m_displaypage+1&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r&&processedpages==m_displaypage+1))
	  {
	    int a;
		a=0;
        if(m_validnum_r-m_retrievednum>=16)
	     a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	    else
	     a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused,TRUE,SearchIndexList);
	    if(a==0)
		{
		  m_displaypage=m_displaypage+1;
		  m_sRetrieveTime.Empty();
          m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
          DisplayPage(m_displaypage);
          processedpages+=1;
		  return;
		}
	  }
   }
   if(oldmethod==6)
   {
	  if((m_page_setting_saved>0&&processedpages==m_displaypage+1&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r&&processedpages==m_displaypage+1))
	  {
	    int a;
		a=0;
        if(m_validnum_r-m_retrievednum>=16)
	     a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	    else
	     a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused,TRUE,SearchIndexList);
	    if(a==0)
		{
		  m_displaypage=m_displaypage+1;
		  m_sRetrieveTime.Empty();
          m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
          DisplayPage(m_displaypage);
          processedpages+=1;
		  return;
		}
	  }
   }
   if(oldmethod==9)
   {
	  if((m_page_setting_saved>0&&processedpages==m_displaypage+1&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r&&processedpages==m_displaypage+1))
	  {
	    int a;
		a=0;
        if(m_validnum_r-m_retrievednum>=16)
	     a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	    else
	     a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused,TRUE,SearchIndexList);
	    if(a==0)
		{
		  m_displaypage=m_displaypage+1;
		  m_sRetrieveTime.Empty();
          m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
          DisplayPage(m_displaypage);
          processedpages+=1;
		  return;
		}
	  }
   }
   m_displaypage=m_displaypage+1;
   DisplayPage(m_displaypage);
}

void CVqRetrieveDoc::OnFeedbackScheme1() 
{
	// TODO: Add your command handler code here
	
}

void CVqRetrieveDoc::OnFeedbackScheme2() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnFeedbackScheme3() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnFeedbackScheme4() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnFeedbackScheme5() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnFeedbackScheme6() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnFeedbackScheme7() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnFeedbackScheme8() 
{
	// TODO: Add your command handler code here
	
}

void CVqRetrieveDoc::OnEvaluation() 
{
	// TODO: Add your command handler code here
	CDialogEvaluation de;
	de.DoModal();
}


//Display the large query image
void CVqRetrieveDoc::OnStaticquery() 
{
	// TODO: Add your control notification handler code here
	if(m_bFileOpened==false||m_bRetrieving==true)return;
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_vQueryFeatureVector,0);
	myDisplayImage.QueryorRetrieval=0;
	myDisplayImage.rgbimage=m_bQueryImageData;
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();
}
void CVqRetrieveDoc::OnDoubleclickedRegionQuery() 
{
	// TODO: Add your control notification handler code here
    if(m_bFileOpened==false||m_bRetrieving==true)return;
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_vQueryFeatureVector,0);
	myDisplayImage.QueryorRetrieval=0;
	myDisplayImage.rgbimage=m_bQueryImageData;
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	OnChangeasquery();
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval1() 
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<1-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
    memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[1-1],0);
    memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	OnChangeasquery();
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval10() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval11() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval12() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval13() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval14() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval15() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval16() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval2() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval3() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval4() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval5() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval6() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval7() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval8() 
{
	// TODO: Add your control notification handler code here
	
}

void CVqRetrieveDoc::OnDoubleclickedRegionRetrieval9() 
{
	// TODO: Add your control notification handler code here
	
}

//Display the large rerevieved image 1
void CVqRetrieveDoc::OnStaticretrieval1() 
{
 	// TODO: Add your control notification handler code here
 	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<1-1||m_bRetrieving==true)return;
 	myDisplayImage.QueryorRetrieval=1;
     memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
 	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
 	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[1-1],0);
    memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
 	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 2
void CVqRetrieveDoc::OnStaticretrieval2() 
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<2-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[2-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 3
void CVqRetrieveDoc::OnStaticretrieval3() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<3-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[3-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 4
void CVqRetrieveDoc::OnStaticretrieval4() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<4-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[4-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 5
void CVqRetrieveDoc::OnStaticretrieval5() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<5-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[5-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 6
void CVqRetrieveDoc::OnStaticretrieval6() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<6-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[6-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 7
void CVqRetrieveDoc::OnStaticretrieval7() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<7-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[7-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 8
void CVqRetrieveDoc::OnStaticretrieval8() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
    if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<8-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[8-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 9
void CVqRetrieveDoc::OnStaticretrieval9() 
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<9-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[9-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}
//Display the large rerevieved image 10

void CVqRetrieveDoc::OnStaticretrieval10() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<10-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[10-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 11
void CVqRetrieveDoc::OnStaticretrieval11() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<11-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[11-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 12
void CVqRetrieveDoc::OnStaticretrieval12() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<12-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[12-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 13
void CVqRetrieveDoc::OnStaticretrieval13() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<13-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[13-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 14
void CVqRetrieveDoc::OnStaticretrieval14() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<14-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[14-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 15
void CVqRetrieveDoc::OnStaticretrieval15() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<15-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[15-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

//Display the large rerevieved image 16
void CVqRetrieveDoc::OnStaticretrieval16() //显示各个检索图像
{
	// TODO: Add your control notification handler code here
	if(m_bRetrieveDisplay==false||m_uDisplayNumber-1<16-1||m_bRetrieving==true)return;
	myDisplayImage.QueryorRetrieval=1;
	memcpy(myDisplayImage.m_StandardBmpInfoc,m_StandardBmpInfoc,54);
	memcpy(myDisplayImage.m_StandardBmpInfo,m_StandardBmpInfo,1078);
	FeatureVectorCopy(&myDisplayImage.m_cFeatureVector,&m_cDisplayFeatureVector[16-1],0);
	memcpy(myDisplayImage.m_CurrentDirectory,m_CurrentDirectory,_MAX_PATH);
	myDisplayImage.DoModal();	
}

void CVqRetrieveDoc::OnChangeasquery() 
{
	// TODO: Add your command handler code here
	int i,j;
	double sum,sum1;
	AfxGetApp()->OpenDocumentFile(myDisplayImage.m_cFeatureVector.m_sOriginalFileName);
	AfxGetApp()->AddToRecentFileList(myDisplayImage.m_cFeatureVector.m_sOriginalFileName);
	myDisplayImage.MyOnCancel();
	if(m_bFeatureFileOpened==false)return;
	m_bQueryImageFeature=true;
	m_bQueryImageNormalized=true;
	//m_bFeedBack=false;
	//retrieve again using the new query
	//get current feature vector
	
	FeatureVectorCopy(&m_vQueryFeatureVector,&myDisplayImage.m_cFeatureVector,1);
	//For memory based feedback
	if(m_iSimpleFeedBackMethod==1)
	{ 
	  m_Iterations=m_Iterations+1;
	  if(m_Iterations>m_T2-1)m_Iterations=m_T2-1;
	  //Get the sequence of memory feature vectors
	  for(i=m_Iterations;i>=1;i--)
	  	FeatureVectorCopy(&m_vQueryFeatureVectors[i],&m_vQueryFeatureVectors[i-1],1);
	  FeatureVectorCopy(&m_vQueryFeatureVectors[0],&m_vQueryFeatureVector,1);
	  
	  //Calculate the new query vector based on the past max 10 vectors
	  for(j=0;j<m_ffi_fromfile.m_wTotalDimensions;j++)
	  {
		 sum=0.0;
		 sum1=0.0;
		 for(i=0;i<=m_Iterations;i++)
		 {
	       sum+=weights[i];
		   sum1+=m_vQueryFeatureVectors[i].m_dOriginalFeature[j]*weights[i];
		 }
		 m_vQueryFeatureVector.m_dOriginalFeature[j]=sum1/sum;
		 sum=0.0;
		 sum1=0.0;
		 for(i=0;i<=m_Iterations;i++)
		 {
	       sum+=weights[i];
		   sum1+=m_vQueryFeatureVectors[i].m_dNormalizedFeature[j]*weights[i];
		 }
		 m_vQueryFeatureVector.m_dNormalizedFeature[j]=sum1/sum;
	  }
	}
	OnRetrieveStart();
}

/*
void CVqRetrieveDoc::OnFeedback() 
{
	// TODO: Add your command handler code here
	if (m_bFileOpened==false)///文件未打开
	{
		MessageBox(NULL,"Please open the key Image first!","Error",MB_OK);
			return;
	}
	if (m_bFeatureFileOpened==false) ///文件库未打开
	{
			MessageBox(NULL,"Please open the Image_data_base first!","Error",MB_OK);
			return;

	}
	if (m_bRetrieveDisplay==false)
	{
			MessageBox(NULL,"Please Retrieve the DataBase first!","Error",MB_OK);
			return;

	}
		  //初始化
		MyDialogRetrieveBack.m_iCanBeBack=m_uDisplayNumber;
		MyDialogRetrieveBack.m_iChooseOperation=0; ///默认反馈
		MyDialogRetrieveBack.m_fCurrent=100;
		MyDialogRetrieveBack.m_sCurrent.Empty();
		MyDialogRetrieveBack.m_fedit1=0;
		MyDialogRetrieveBack.m_fedit2=0;
		MyDialogRetrieveBack.m_fedit3=0;
		MyDialogRetrieveBack.m_fedit4=0;
		MyDialogRetrieveBack.m_fedit5=0;
		MyDialogRetrieveBack.m_fedit6=0;
		MyDialogRetrieveBack.m_fedit7=0;
		MyDialogRetrieveBack.m_fedit8=0;
		MyDialogRetrieveBack.m_fedit9=0;
		MyDialogRetrieveBack.m_fedit10=0;
		MyDialogRetrieveBack.m_fedit11=0;
		MyDialogRetrieveBack.m_fedit12=0;
		MyDialogRetrieveBack.m_fedit13=0;
		MyDialogRetrieveBack.m_fedit14=0;
		MyDialogRetrieveBack.m_fedit15=0;
		MyDialogRetrieveBack.m_fedit16=0;
		MyDialogRetrieveBack.m_bChanged=FALSE;
		MyDialogRetrieveBack.m_sCurrent.Format("%s%f",MyDialogRetrieveBack.m_sCurrent,MyDialogRetrieveBack.m_fCurrent);
	  if(MyDialogRetrieveBack.DoModal()==IDOK)
	  {
			if (MyDialogRetrieveBack.m_iChooseOperation==0)
			{
				  for(int i=0;i<m_iCurrentFeatureDimension;i++ )///计算反馈图像
							    m_vQueryFeatureVector.m_dFileNormalizedFeature[i]=0.01*(
								    m_vQueryFeatureVector.m_dFileNormalizedFeature[i]*MyDialogRetrieveBack.m_fCurrent+
									MyDialogRetrieveBack.m_fedit1*m_cDisplayFeatureVector[0].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit2*m_cDisplayFeatureVector[1].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit3*m_cDisplayFeatureVector[2].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit4*m_cDisplayFeatureVector[3].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit5*m_cDisplayFeatureVector[4].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit6*m_cDisplayFeatureVector[5].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit7*m_cDisplayFeatureVector[6].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit8*m_cDisplayFeatureVector[7].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit9*m_cDisplayFeatureVector[8].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit10*m_cDisplayFeatureVector[9].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit11*m_cDisplayFeatureVector[10].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit12*m_cDisplayFeatureVector[11].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit13*m_cDisplayFeatureVector[12].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit14*m_cDisplayFeatureVector[13].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit15*m_cDisplayFeatureVector[14].m_dFileNormalizedFeature[i]+
									MyDialogRetrieveBack.m_fedit16*m_cDisplayFeatureVector[15].m_dFileNormalizedFeature[i]
									);
	
				  m_bFeedBack=TRUE;  /////当前在反馈
			}
			else if(MyDialogRetrieveBack.m_iChooseOperation==1)
			{
				MyRetrieveMethod.QueryImageNormalization(&m_vQueryFeatureVector,m_iCurrentFeatureDimension,m_pDNormalizeEquVarible,m_pDNormalizeAveVarible);
				m_bFeedBack=false;  /////当前恢复						 
			}
	  m_bRetrieveDisplay=false;      ///////需要从新检索
	  UpdateAllViews(NULL);
	  }
	  UpdateAllViews(NULL);
}*/





/*
///Stop the retrieval and choosing
void CVqRetrieveDoc::OnStop() 
{
	// TODO: Add your command handler code here
	if(m_bChoosing==true)m_bChoosing=false;
	else if(m_bRetrieving==true)
	{
	  m_bRetrieveInterrupt=true;
	  m_bRetrieving=false;
	}
}*/


//Retrieving and feature computing, no exit
void CVqRetrieveDoc::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(true);
}

//Retrieving and feature computing, no Help
void CVqRetrieveDoc::OnUpdateHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(true);	
}

//Retrieving and feature computing, no Helpfinder
void CVqRetrieveDoc::OnUpdateHelpFinder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(true);	
}

//Retrieving and feature computing, no AppAbout
void CVqRetrieveDoc::OnUpdateAppAbout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(true);		
}

//Even retrieving and feature computing, also allow to set printflag
void CVqRetrieveDoc::OnUpdatePrintQuery(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_printflag==0)
       pCmdUI->SetCheck(1);
	else
       pCmdUI->SetCheck(0);		
}

//Even retrieving and feature computing, also allow to set printflag
void CVqRetrieveDoc::OnUpdatePrintPagewithquery(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_printflag==1)
       pCmdUI->SetCheck(1);
	else
       pCmdUI->SetCheck(0);		
}

//Even retrieving and feature computing, also allow to set printflag
void CVqRetrieveDoc::OnUpdatePrintPagenoquery(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_printflag==2)
       pCmdUI->SetCheck(1);
	else
       pCmdUI->SetCheck(0);		
}

//Retrieving and feature computing, no print
//printflag=0 only query image,judge m_bFileOpened
//printflag=1 results with query image, judge m_bFileOpened and m_bRetrieveDisplay
//printflag=2 results without query image,judge m_bFileOpened and m_bRetrieveDisplay
void CVqRetrieveDoc::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
		pCmdUI->Enable(false);
    else 
	{
	  if((m_printflag==0&&m_bFileOpened==true)||((m_printflag==1||m_printflag==2)&&m_bFileOpened==true&&m_bRetrieveDisplay==true))
        pCmdUI->Enable(true);
	  else
        pCmdUI->Enable(false);	
	}
}

//Retrieving and feature computing, no print preview
//printflag=0 only query image,judge m_bFileOpened
//printflag=1 results with query image, judge m_bFileOpened and m_bRetrieveDisplay
//printflag=2 results without query image,judge m_bFileOpened and m_bRetrieveDisplay
void CVqRetrieveDoc::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
		pCmdUI->Enable(false);
    else 
	{
	  if((m_printflag==0&&m_bFileOpened==true)||((m_printflag==1||m_printflag==2)&&m_bFileOpened==true&&m_bRetrieveDisplay==true))
       pCmdUI->Enable(true);
	  else
       pCmdUI->Enable(false);	
	}
}

//Retrieving and feature computing, no printsetup
//printflag=0 only query image,judge m_bFileOpened
//printflag=1 results with query image, judge m_bFileOpened and m_bRetrieveDisplay
//printflag=2 results without query image,judge m_bFileOpened and m_bRetrieveDisplay
void CVqRetrieveDoc::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
		pCmdUI->Enable(false);
    else 
	{
	  if((m_printflag==0&&m_bFileOpened==true)||((m_printflag==1||m_printflag==2)&&m_bFileOpened==true&&m_bRetrieveDisplay==true))
       pCmdUI->Enable(true);
	  else
       pCmdUI->Enable(false);	
	}
}

//Retrieving and feature computing,no feature computation
//no query file,no computation
//no feature file,no computation
void CVqRetrieveDoc::OnUpdateQueryFeaturecompute(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
		pCmdUI->Enable(false);
    else 
	  pCmdUI->Enable(m_bFileOpened&&m_bFeatureFileOpened);
}

//Retrieving and feature computing,no feature computation
//no feature, no computation
void CVqRetrieveDoc::OnUpdateQueryFeaturenormalization(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
		pCmdUI->Enable(false);
    else 
	{
	  pCmdUI->Enable(m_bQueryImageFeature);
	}
}

//When retrieve or featurecompute, disable path selection
void CVqRetrieveDoc::OnUpdateDatabasePath(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
	else
      pCmdUI->Enable(true);
}

//When retrieve or featurecompute, disable feature selection
void CVqRetrieveDoc::OnUpdateDatabaseFeatureselection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(true);	
}
void CVqRetrieveDoc::OnUpdateDatabaseCodebookfordctvq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true||m_ffi.m_bWithFeature1_OF==FALSE)
       pCmdUI->Enable(false);
	else
	   pCmdUI->Enable(m_bDatabaseOpened);
}
void CVqRetrieveDoc::OnUpdateDatabaseCodebookforvq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true||m_ffi.m_bWithFeature2_OF==FALSE)
       pCmdUI->Enable(false);
	else
	   pCmdUI->Enable(m_bDatabaseOpened);
	
}

void CVqRetrieveDoc::OnUpdateDatabaseCodebookformsvq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true||m_ffi.m_bWithFeature3_OF==FALSE)
       pCmdUI->Enable(false);
	else
	   pCmdUI->Enable(m_bDatabaseOpened);
	
}

void CVqRetrieveDoc::OnUpdateDatabaseCodebookformrvq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true||m_ffi.m_bWithFeature4_OF==FALSE)
       pCmdUI->Enable(false);
	else
	   pCmdUI->Enable(m_bDatabaseOpened);	
}


//When retrieve or featurecompute, disable feature selection
//When no database opened disable
void CVqRetrieveDoc::OnUpdateDatabaseFeaturecompute(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
      pCmdUI->Enable(false);
	else
	{
	  pCmdUI->Enable(m_bDatabaseOpened);
	}
}

//When retrieve or !featurecompute, disable stop
void CVqRetrieveDoc::OnUpdateDatabaseStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bDatabaseFeatureComputing);	
}
//When retrieve or featurecompute, disable normalization
//When no database feature computed disable
void CVqRetrieveDoc::OnUpdateDatabaseFeaturenormalization(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bDatabaseFeatureComputed);
}

void CVqRetrieveDoc::OnUpdateDatabaseSorting(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bDatabaseFeatureNormalized);
}

//When retrieve or featurecompute, disable clustering
//When no database feature normalized disable
void CVqRetrieveDoc::OnUpdateDatabaseNfeaturespacevq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
        pCmdUI->Enable(false);
 	else
        pCmdUI->Enable(m_bDatabaseFeatureNormalized);
}

void CVqRetrieveDoc::OnUpdateDatabaseClustersorting(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
        pCmdUI->Enable(false);
 	else
        pCmdUI->Enable(m_bDatabaseClustered);
}

void CVqRetrieveDoc::OnUpdateDatabaseFeaturesave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bDatabaseFeatureNormalized);
}

//When retrieve or featurecompute, disable filesave
//When no database feature clustered disable
void CVqRetrieveDoc::OnUpdateDatabaseCodewordssave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bDatabaseClustered);
}

//When retrieve or featurecompute, disable filesave
//When no database feature clustered disable
void CVqRetrieveDoc::OnUpdateDatabaseVQFeaturesave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bCodebookFileSaved);
}

//When retrieve or featurecompute, disable open feature file
void CVqRetrieveDoc::OnUpdateRetrieveFeaturefile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true);  	
}

//When retrieve or featurecompute, disable feature file view
//when no feature file opened,also disable
void CVqRetrieveDoc::OnUpdateRetrieveFeatureselected(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(m_bFeatureFileOpened); 
}

//When retrieve or featurecompute, disable feature file view
//when no feature file opened,also disable
void CVqRetrieveDoc::OnUpdateRetrieveClusteringbook(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(m_bFeatureFileOpened&&m_ffi_fromfile.m_bClustered); 
}

//When retrieve or featurecompute, disable feature file view
//when no codebook file opened,also disable
void CVqRetrieveDoc::OnUpdateRetrieveVQFeatureFile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
}

//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==0)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}

//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveUpdatingfs(CCmdUI* pCmdUI) 
{
 	// TODO: Add your command update UI handler code here
 	if(m_bRetrieving==true)
 	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(true); 
    if(m_iRetrieveMethod==1)
	  pCmdUI->SetCheck(true);
    else
 	  pCmdUI->SetCheck(false);
}
//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveEknns(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==2)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
	
}
//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveIeknnsuser(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==3)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
	
}

//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveIeknnsback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==4)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);

}
void CVqRetrieveDoc::OnUpdateRetrieveEeknns(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==5)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}
void CVqRetrieveDoc::OnUpdateRetrieveIeeknnsuser(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==6)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
	
}

void CVqRetrieveDoc::OnUpdateRetrieveIeeknnsback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==7)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);

}

void CVqRetrieveDoc::OnUpdateRetrieveEeeknns(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==8)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);	
}
void CVqRetrieveDoc::OnUpdateRetrieveIeeeknnsuser(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==9)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
	
}
void CVqRetrieveDoc::OnUpdateRetrieveIeeeknnsback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==10)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}

//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveVqonlynnc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==11)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}

//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveVqonlyknncs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==12)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}
//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveVqallclusters(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iRetrieveMethod==13)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}
void CVqRetrieveDoc::OnUpdateRetrievePages1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==1)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CVqRetrieveDoc::OnUpdateRetrievePages10(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==10)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);	
	
}


void CVqRetrieveDoc::OnUpdateRETRIEVEPAGES1AND1Image(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==0)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);	
	
}


void CVqRetrieveDoc::OnUpdateRetrievePages2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==2)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);	
}


void CVqRetrieveDoc::OnUpdateRetrievePages3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==3)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);	
	
}


void CVqRetrieveDoc::OnUpdateRetrievePages4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==4)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);	
	
}


void CVqRetrieveDoc::OnUpdateRetrievePages5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==5)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CVqRetrieveDoc::OnUpdateRetrievePages6(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==6)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);
}


void CVqRetrieveDoc::OnUpdateRetrievePages7(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==7)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);
}


void CVqRetrieveDoc::OnUpdateRetrievePages8(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==8)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}



void CVqRetrieveDoc::OnUpdateRetrievePages9(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==9)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);
}

void CVqRetrieveDoc::OnUpdateRetrievePages15(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==15)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);	
}


void CVqRetrieveDoc::OnUpdateRetrievePages20(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==20)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);
}


void CVqRetrieveDoc::OnUpdateRetrievePages25(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==25)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);

}


void CVqRetrieveDoc::OnUpdateRetrievePagesall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bFeatureFileOpened); 
	if(m_page_setting==-1)
	  pCmdUI->SetCheck(true);
	else
	  pCmdUI->SetCheck(false);
}

void CVqRetrieveDoc::OnUpdateRetrieveStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_iRetrieveMethod>1&&m_bSorted==false)//If no sorted
	{
		pCmdUI->Enable(false);
		return;
	}
	if(m_iRetrieveMethod>10)
	{
      if((m_bFeatureFileOpened==true)&&(m_bCodebookFileOpened==true)&&(m_bDatabaseFeatureComputing==false)&&(m_bRetrieving==false)&&(m_bQueryImageNormalized==true))
        pCmdUI->Enable(true);
      else
	    pCmdUI->Enable(false);  
	}
	else
	{
      if((m_bFeatureFileOpened==true)&&(m_bDatabaseFeatureComputing==false)&&(m_bRetrieving==false)&&(m_bQueryImageNormalized==true))
        pCmdUI->Enable(true);
      else
	    pCmdUI->Enable(false);  
	}
}
void CVqRetrieveDoc::OnUpdateRetrieveFeedbacknomemory(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iSimpleFeedBackMethod==0)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}


void CVqRetrieveDoc::OnUpdateRetrieveFeedbackwithmemory(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(true); 
   if(m_iSimpleFeedBackMethod==1)
	  pCmdUI->SetCheck(true);
   else
	  pCmdUI->SetCheck(false);
}

void CVqRetrieveDoc::OnUpdateRetrieveStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(m_bRetrieving);  	
	
}
void CVqRetrieveDoc::OnUpdateDisplayFirst(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
   {
      if(m_displaypage==0)
		   pCmdUI->Enable(false); 
	  else
		  pCmdUI->Enable(m_bRetrieveDisplay);
   }
}

void CVqRetrieveDoc::OnUpdateDisplayLast(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
   {
     if((oldmethod==3||oldmethod==6||oldmethod==9)&&((m_page_setting_saved>0&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r)))
	 {
	   pCmdUI->Enable(false);
	 }
     else
	 {
	  if(m_page_setting_saved>0)
	  {
	    if(m_displaypage==m_page_setting_saved-1)
          pCmdUI->Enable(false); 
		else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
	  }
	  else if(m_page_setting_saved==0)
	  {
	    if(m_displaypage==0)
          pCmdUI->Enable(false); 
		else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
	  }
	  else
	  {
	    if(m_retrievednum%16==0)
		{
	     if(m_displaypage==m_retrievednum/16-1)
		   pCmdUI->Enable(false); 
		 else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
		}
	    else
		{
	     if(m_displaypage==m_retrievednum/16)
		   pCmdUI->Enable(false); 
		 else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
		}
	  }
	 }
   }
}

void CVqRetrieveDoc::OnUpdateDisplayPrevious(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
   {
      if(m_displaypage==0)
		  pCmdUI->Enable(false); 
	  else
		  pCmdUI->Enable(m_bRetrieveDisplay);
   }
}

void CVqRetrieveDoc::OnUpdateDisplayNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
   {
     if((oldmethod==3||oldmethod==6||oldmethod==9)&&((m_page_setting_saved>0&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r)))
	 {
	   pCmdUI->Enable(true);
	 }
	 else
	 {
	  if(m_page_setting_saved>0)
	  {
	    if(m_displaypage==m_page_setting_saved-1)
          pCmdUI->Enable(false); 
		else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
	  }
	  else if(m_page_setting_saved==0)
	  {
	    if(m_displaypage==0)
          pCmdUI->Enable(false); 
		else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
	  }
	  else
	  {
		if(m_retrievednum%16==0)
		{
	     if(m_displaypage==m_retrievednum/16-1)
		   pCmdUI->Enable(false); 
		 else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
		}
	    else
		{
	     if(m_displaypage==m_retrievednum/16)
		   pCmdUI->Enable(false); 
		 else
		  pCmdUI->Enable(m_bRetrieveDisplay); 
		}
	  }
	 }
   }
}


void CVqRetrieveDoc::OnUpdateEvaluation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 	if(m_bDatabaseFeatureComputing==true||m_bRetrieving==true)
 	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(true);  	
}

void CVqRetrieveDoc::OnUpdateFeedbackScheme1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false); 
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme6(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme7(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}


void CVqRetrieveDoc::OnUpdateFeedbackScheme8(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bFileOpened&&m_bFeatureFileOpened&&m_bRetrieveDisplay&&m_bRetrieving==false)
	  pCmdUI->Enable(true);
	else
	  pCmdUI->Enable(false);  
}

void CVqRetrieveDoc::InitialFeatureFileInfo()
{
  m_ffi.m_wStructSize=sizeof(FEATUREFILEINFO);
  //The file size(to be computed)
  m_ffi.m_dwFileSize=0;
  strcpy(m_ffi.m_sPath,"");
  //The last 8 letters of this file name
  strcpy(m_ffi.m_sThisFileNameLast8,"000.fdb");
  m_ffi.m_bEverInterrupted=FALSE;
  //The offset of first image's feature
  m_ffi.m_wOffBytes=600;
  //The number of image files(to be counted)
  m_ffi.m_dwFileNumber=0;
  //If need nextfile to save the feature database
  m_ffi.m_bNextFile=FALSE;
  //The nextfile name
  strcpy(m_ffi.m_sNextFileNameLast8,"fdbnone");
  //The number of feature types
  m_ffi.m_bFeatureTypes=1;//default only color feature
  //The total dimensions of features 
  m_ffi.m_wTotalDimensions=192;//default 64bin HSV color hist
  //With colors?
  m_ffi.m_bWithColor=TRUE;
  //With Invariant?
  m_ffi.m_bWithRTInvariant=FALSE;
  //With Texture?
  m_ffi.m_bWithTexture=FALSE;
  //With Shape?
  m_ffi.m_bWithShape=FALSE;
  //With Others?
  m_ffi.m_bWithOthers=FALSE;
  //++++++++++For colors++++++++
  m_ffi.m_bColorSpace_CF=1;//The color space HSV
  m_ffi.m_bDescription_CF=0;//The description style of ColorHist
  m_ffi.m_bBins_CF=1;//The bin selection 1 of CF
  m_ffi.m_wDimension_CF=192;//The dimension of CF
  
  //+++++++++++For Invarint++++++  
  m_ffi.m_bColorSpace_IF=1;//The color space HSV
  m_ffi.m_bPoints_IF=0; //The Points selection style for RT-Inva.
  m_ffi.m_bAngles_IF=7; //The Angles selection style for RT-Inva.
  m_ffi.m_bBins_IF=1;//The bin selection 2 of CF
  m_ffi.m_bDescription_IF=1;//The description style of RT-Inva.
  m_ffi.m_wDimension_IF=0;//The dimension of IF
  
  //++++++++++For Texture++++++++
  m_ffi.m_bColorSpace_TF=6;//The Color Space  only gray
  m_ffi.m_bDescription_TF=10;//The description style
  m_ffi.m_wDimension_TF=0;//The dimension of TF
  m_ffi.m_bCoocurrence_TF=0;//The par of Coocurrence
  //++++++++++For Shape++++++++
  m_ffi.m_bColorSpace_SF=6;//The Color Space
  m_ffi.m_bDescription_SF=4;//The description style
  m_ffi.m_wDimension_SF=0;//The dimension of TF
  //++++++++++For Other++++++++
  m_ffi.m_bWithFeature1_OF=FALSE;//With the feature1 of OF
  m_ffi.m_bWithFeature2_OF=FALSE;//With the feature2 of OF
  m_ffi.m_bWithFeature3_OF=FALSE;//With the feature3 of OF
  m_ffi.m_bWithFeature4_OF=FALSE;//With the feature4 of OF
  strcpy(m_ffi.m_sFeature1_OF,"DCT-VQ Based Features");
  strcpy(m_ffi.m_sFeature2_OF,"VQ Based Features");
  strcpy(m_ffi.m_sFeature3_OF,"MSVQ Based Features");
  strcpy(m_ffi.m_sFeature4_OF,"MRVQ Based Features");
  m_ffi.m_wDimension_OF=0;
  m_ffi.m_wWeights[0]=100;
  m_ffi.m_wWeights[1]=0;
  m_ffi.m_wWeights[2]=0;
  m_ffi.m_wWeights[3]=0;
  m_ffi.m_wWeights[4]=0;
  m_ffi.m_wWeights[5]=0;
  m_ffi.m_wWeights[6]=0;
  m_ffi.m_wWeights[7]=0;
}

//Compute all feature vectors for the valid images in sPath
//
bool CVqRetrieveDoc::FeatureVectorExtract(CString sPath)
{	
    CString str;
	CFileFind file;
	BOOL bContinueNumber;
	
	///Retrieval Interrupted
	if(m_bDatabaseFeatureInterrupted==true)return false;	
	
	//If all the selected images have been computed
	//Then the process can be finished
	if(m_extractednum==m_validnum)return true;
			
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.bmp";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber=file.FindNextFile();
		if(!file.IsDirectory()&&!file.IsDots())
		{	
			//If all the selected images have been computed
			//Then the process can be finished
			if(m_extractednum==m_validnum)return true;
			
			//Retrieve current image
			if(ReadDatabaseImageandComputeFeatureVector(file.GetFilePath(),m_lpDFeatureVector+m_extractednum)==0)
			{
			  //If Interrupted
			  if(m_bDatabaseFeatureInterrupted==true)return false;  
			  
			  ///After compute feature vectors for 5 images
			  //then response the user interrupt
			  if(m_extractednum>0&&m_extractednum%5==0)
			  {
				::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
			    ::TranslateMessage(&Mymsg);  ////Translate Message
			    ::DispatchMessage(&Mymsg);///Response
			  }
			  
			  ///every 25 images update
			  if(m_extractednum>0&&m_extractednum%25==0)
			  	UpdateAllViews(NULL);
			  m_extractednum++;
			}
			else
			{
			   CString a;
			   a="Feature Extraction Error for Image"+file.GetFilePath();
			   MessageBox(NULL,a,"Error",MB_OK|MB_ICONSTOP);
			}
		}
	}
	//end of while
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.jpg";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber=file.FindNextFile();
		if(!file.IsDirectory()&&!file.IsDots())
		{	
			//If all the selected images have been computed
			//Then the process can be finished
			if(m_extractednum==m_validnum)return true;
			
			//Compute Current image's feature
			if(ReadDatabaseImageandComputeFeatureVector(file.GetFilePath(),m_lpDFeatureVector+m_extractednum)==0) //
			{
			  //If Interrupted
			  if(m_bDatabaseFeatureInterrupted==true)return false;
			  ///After compute feature vectors for 5 images, then response the user interrupt
			  if(m_extractednum>0&&m_extractednum%5==0)
			  {
				::PeekMessage(&Mymsg, NULL, 0, 0, PM_REMOVE); ///Get message
			    ::TranslateMessage(&Mymsg);  ////Translate Message
			    ::DispatchMessage(&Mymsg);///Response
			  }
              ///every 25 images update
			  if(m_extractednum>0&&m_extractednum%25==0)
			  	UpdateAllViews(NULL);
			  m_extractednum++;
			}
			else
			{
			   CString a;
			   a="Feature Extraction Error for Image"+file.GetFilePath();
			   MessageBox(NULL,a,"Error",MB_OK|MB_ICONSTOP);
			}
		}
	}

    ///For sub-directory
	file.Close();
	str.Empty();
	str=sPath;
	if(str.Right(1)!="\\")str+="\\";
	str+= "*.*";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		///Computation Interrupted
	    if(m_bDatabaseFeatureInterrupted==true)return false;	
	    bContinueNumber = file.FindNextFile();
		if(file.IsDots())continue;
		else if(file.IsDirectory())
		{	
			if(FeatureVectorExtract(file.GetFilePath())==false)return false;
			
			//If all the selected images have been computed
	        //Then the process can be finished
			if(m_extractednum==m_validnum)return true;
		}
	}
	//end of while
    return true;
}


///Release all memory for database
void CVqRetrieveDoc::DestroyDatabaseMemory()
{
	if(m_hDFeatureVector!=NULL)
	{
		GlobalFree(m_hDFeatureVector);
		m_hDFeatureVector=NULL;
	}
}

///Release all memory for retrieval
void CVqRetrieveDoc::DestroyRetrievalMemory()
{
	if(m_hRFeatureVector!=NULL)
	{
	  GlobalFree(m_hRFeatureVector);
	  m_hRFeatureVector=NULL;
	}
	if(m_hResult!=NULL)
	{
	  GlobalFree(m_hResult);
	  m_hResult=NULL;
	}
	//if(SearchIndexList!=NULL)delete [] SearchIndexList;
}

void CVqRetrieveDoc::DestroyQueryMemory()
{
	if(Imagehg!=NULL)
	{
	  GlobalFree(Imagehg);
	  Imagehg=NULL;
	}
	if(ImageFeature!=NULL)
	{
	  GlobalFree(ImageFeature);
	  ImageFeature=NULL;
	}
}

//得到显示图像和关键图的距离,字符输出
float CVqRetrieveDoc::GetDistance(unsigned char i)
{
	float a;
	if(i>16||i<0)
	  a=-1;
	else
	  a=(float)m_dDisplayFileDistance[i];
	return a;
}
///Get the image name
CString CVqRetrieveDoc::GetDisplayFileName(unsigned char i)
{
	CFile myfile;
	CString filename;
	PFEATUREVECTOR FeatureVectorvar=(m_cDisplayFeatureVector+i);
	if(myfile.Open(FeatureVectorvar->m_sOriginalFileName,CFile::modeRead,NULL)==NULL)
	{
	  return "";
	}
	//filename=myfile.GetFileName();
	filename=FeatureVectorvar->m_sOriginalFileName;
	filename.Delete(0,m_sRetrievePath.GetLength());
	myfile.Close();
	return filename;        //返回该图像的文件名
}

///获得显示检索图像的特征矢量结构体
FEATUREVECTOR CVqRetrieveDoc::GetDisplayFeatureVector(unsigned char i)
{
	return m_cDisplayFeatureVector[i];
}
int CVqRetrieveDoc::ReadQueryImage(CString ImagePathName,PFEATUREVECTOR FeatureVector)
{
	unsigned int x,y;
	int type=-1;
	int iBitCount;
	int PaletteNumber;  //PaletteNumber
	long int fh;
	LONG ImageWidth;
	LONG ImageHeight;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	DWORD m_ibfbts,m_iImageSize;
	JPEG_IMAGE_INFO info;
	LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	
	//open new query image
	if(file.Open(ImagePathName,CFile::modeRead,NULL)==NULL)return -1;
	m_iImageSize=file.GetLength();//get the query image size
	Imagehg=NULL;//Clear the old Query image memory
	Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//apply new query image memory
	if(Imagehg==NULL)
	{
	  file.Close();
	  return -2;
	}
	m_QueryImageFile=(unsigned char *)Imagehg;
	m_bQueryImageData=(BYTE *)(m_QueryImageFile+m_iImageSize);
	if(file.Read(m_QueryImageFile,m_iImageSize)!=m_iImageSize)
	{
	  file.Close();
	  GlobalFree(Imagehg);
	  return -2;
	}
	file.Close();//close the file
	bitfile=(LPBITMAPFILEHEADER)m_QueryImageFile;
	bitinfo=(LPBITMAPINFOHEADER)(m_QueryImageFile+sizeof(BITMAPFILEHEADER));
	m_ibfbts=bitfile->bfOffBits;
    ImageWidth=bitinfo->biWidth;
	ImageHeight=bitinfo->biHeight;
	iBitCount=bitinfo->biBitCount;
	type=0;
	if(bitfile->bfType!=0x4d42)
	{
        GlobalFree(Imagehg);//Free the memory
		
		//Reopen the file
		if(jpg.open(ImagePathName,IDCT_INT))
		{ 
		  jpg.getImageInfo(&info);
		  temp=m_CurrentDirectory;
		  temp=temp+"\\tempquery.bmp";
		  fh=_open(temp,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
		  if(fh==-1)
		  { 
	        jpg.close();
			return -1;
		  }
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
		    linebytes=(info.imgWidth*24+31)/32*4;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
			bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
			m_iImageSize=bitfile->bfSize;
		    Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
			////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          jpg.close();
			  return -2;
			}
            m_QueryImageFile=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
			m_bQueryImageData=(BYTE *)(m_QueryImageFile+m_iImageSize);
	        memcpy(m_QueryImageFile,m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_QueryImageFile[54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_QueryImageFile[54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_QueryImageFile[54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
		    linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    m_iImageSize=bitfile->bfSize;
		    Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          jpg.close();
			  return -2;
			}
            m_QueryImageFile=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
			m_bQueryImageData=(BYTE *)(m_QueryImageFile+m_iImageSize);
	        memcpy(m_QueryImageFile,m_StandardBmpInfo,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_QueryImageFile+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  if(_write(fh,m_QueryImageFile,m_iImageSize)!=(int)m_iImageSize)
		  {
		    _close(fh);
		    GlobalFree(Imagehg);
            jpg.close();
		    return -2;
		  }
		  _close(fh);
		  jpg.close();
		  type=1;
  	    }
		else
 		   return -3;
	}
	
    ////If the image is a 256-gray/24bits image or not
	if(bitinfo->biBitCount!=8&&bitinfo->biBitCount!=24)
	{
	  GlobalFree(Imagehg);//Free the memory
	  return -3;
	}
	////If the image is compressed or not
	if(bitinfo->biCompression!=0)
	{
      GlobalFree(Imagehg);//Free the memory
	  return -3;
	}
	if(bitinfo->biBitCount==24)//No palette
 	  PaletteNumber=0;
	else if (bitinfo->biClrUsed==0) 
	  PaletteNumber=(int)pow(2,bitinfo->biBitCount);
	else
	  PaletteNumber=bitinfo->biClrUsed;
    
	///Check Palette
	if(m_ibfbts!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PaletteNumber*sizeof(RGBQUAD)))
	{
	  GlobalFree(Imagehg);//Free the memory
	  return -3;
	}
    //File size judgement
	switch(iBitCount)
	{
	   case 24:
		 if(m_iImageSize-m_ibfbts-WIDTHBYTES(24*ImageWidth)*ImageHeight<0) 
		 {
			GlobalFree(Imagehg);//Free the memory
			return -3;
		 }
		 break;
	   case 8:
		 if (m_iImageSize-m_ibfbts-SAVEWIDTH(ImageWidth)*ImageHeight<0) 
		 {
			GlobalFree(Imagehg);//Free the memory
			return -3;
		}
		break;
	   default:
		 GlobalFree(Imagehg);//Free the memory
		 return -3;
		break;
	} 
   strcpy(FeatureVector->m_sOriginalFileName,ImagePathName);///The filename
   FeatureVector->m_bType=type;
   FeatureVector->m_bBitCount=iBitCount;  ///The bits
   FeatureVector->m_lImageWidth=ImageWidth;    //The width
   FeatureVector->m_lImageHeight=ImageHeight;  ///The height
   //Get the RGB data from m_QueryImageFile
   MyRetrieveMethod.get_data_from_24or8bits_bmp_file(m_QueryImageFile,m_bQueryImageData,iBitCount,ImageWidth,ImageHeight);
   ///end of Read Query Image
   return 0;
}

//Return Value 0: normal;
//-1: file open error;-2 memory error;
//-3: type error, -4 feature computation error
int CVqRetrieveDoc::ReadDatabaseImageandComputeFeatureVector(CString ImagePathName,PFEATUREVECTOR FeatureVector)
{
	unsigned int x,y;
	int type=-1;
	int iBitCount;
	int PaletteNumber;  //PaletteNumber
	//long int fh;
	LONG ImageWidth;
	LONG ImageHeight;
	unsigned long int linebytes;
	unsigned char *m_cImageBytes;
	BYTE *pOriginalImageByteData; ///Image Data Memory
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	DWORD m_ibfbts,m_iImageSize;
	JPEG_IMAGE_INFO info;
	HGLOBAL tempImagehg;
    LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	//Image open failed
	if(file.Open(ImagePathName,CFile::modeRead,NULL)==NULL)return -1; 
	m_iImageSize=file.GetLength();
	tempImagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);
	if(tempImagehg==NULL)
	{
	  file.Close();
	  return -2;
	}
	m_cImageBytes=(unsigned char *)tempImagehg;
	pOriginalImageByteData=(BYTE *)(m_cImageBytes+m_iImageSize);
	if(file.Read(m_cImageBytes,m_iImageSize)!=m_iImageSize)
	{
	  file.Close();
	  GlobalFree(tempImagehg);
	  return -2;
	}
	file.Close();//close the file

	bitfile=(LPBITMAPFILEHEADER)m_cImageBytes;
	bitinfo=(LPBITMAPINFOHEADER)(m_cImageBytes+sizeof(BITMAPFILEHEADER));
	m_ibfbts=bitfile->bfOffBits;
    ImageWidth=bitinfo->biWidth;
	ImageHeight=bitinfo->biHeight;
	iBitCount=bitinfo->biBitCount;
	type=0;
	if(bitfile->bfType!=0x4d42)
	{
        GlobalFree(tempImagehg);//Free the memory
		//Reopen the file
		if(jpg.open(ImagePathName,IDCT_INT))
		{ 
		  jpg.getImageInfo(&info);
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
		    linebytes=(info.imgWidth*24+31)/32*4;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
			bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
			m_iImageSize=bitfile->bfSize;
		    tempImagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
            ////If memory is not enough, return directly
            if(tempImagehg==NULL)
			{
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)tempImagehg;//Give the memory pointer to the file data pointer
            pOriginalImageByteData=(BYTE *)(m_cImageBytes+m_iImageSize);
			//memcpy(m_cImageBytes,m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
		    linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    m_iImageSize=bitfile->bfSize;
		    tempImagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
            ////If memory is not enough, return directly
            if(tempImagehg==NULL)
			{
              jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)tempImagehg;//Give the memory pointer to the file data pointer
            pOriginalImageByteData=(BYTE *)(m_cImageBytes+m_iImageSize);
			//memcpy(m_cImageBytes,m_StandardBmpInfo,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_cImageBytes+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  jpg.close();
		  type=1;
  	    }
		else
 		   return -3;
	}

    ////If the image is a 256-gray/24bits image or not
	if(bitinfo->biBitCount!=8&&bitinfo->biBitCount!=24)
	{
	  GlobalFree(tempImagehg);//Free the memory
	  return -3;
	}
	////If the image is compressed or not
	if(bitinfo->biCompression!=0)
	{
      GlobalFree(tempImagehg);//Free the memory
	  return -3;
	}
	if(bitinfo->biBitCount==24)//No palette
 	  PaletteNumber=0;
	else if (bitinfo->biClrUsed==0) 
	  PaletteNumber=(int)pow(2,bitinfo->biBitCount);
	else
	  PaletteNumber=bitinfo->biClrUsed;
    
	///Check Palette
	if(m_ibfbts!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PaletteNumber*sizeof(RGBQUAD)))
	{
	  GlobalFree(tempImagehg);//Free the memory
	  return -3;
	}
    //File size judgement
	switch(iBitCount)
	{
	   case 24:
		 if(m_iImageSize-m_ibfbts-WIDTHBYTES(24*ImageWidth)*ImageHeight<0) 
		 {
			GlobalFree(tempImagehg);//Free the memory
			return -3;
		 }
		 break;
	   case 8:
		 if (m_iImageSize-m_ibfbts-SAVEWIDTH(ImageWidth)*ImageHeight<0) 
		 {
			GlobalFree(tempImagehg);//Free the memory
			return -3;
		}
		break;
	   default:
		 GlobalFree(tempImagehg);//Free the memory
		 return -3;
		break;
	}
   //Get the RGB data from m_QueryImageFile
   MyRetrieveMethod.get_data_from_24or8bits_bmp_file(m_cImageBytes,pOriginalImageByteData,iBitCount,ImageWidth,ImageHeight);
   FeatureVector->m_bType=type; //image type  0, bmp; 1 jpg
   FeatureVector->m_bBitCount=iBitCount;  ///The bits
   FeatureVector->m_lImageWidth=ImageWidth;    //The width
   FeatureVector->m_lImageHeight=ImageHeight;  ///The height
   FeatureVector->m_wDimensions=m_ffi.m_wTotalDimensions;// the feature dimension
   strcpy(FeatureVector->m_sOriginalFileName,ImagePathName);///The image filename
   //Compute the features
   if(TotalFeatureVectorComputation(pOriginalImageByteData,FeatureVector,m_ffi)!=0)
   {
	  GlobalFree(tempImagehg);
	  return -4;
   }
   ///end ,Clear the tempImagehg
   GlobalFree(tempImagehg);
   ///end of read Image and computing feature
   return 0;
}

//input  rgb Image; FeatureVector Infomation
//output FeatureVector OriginalFeatrue
//return value 0:normal <0 method error 1 dimension error
int CVqRetrieveDoc::TotalFeatureVectorComputation(BYTE *ImageBytes,PFEATUREVECTOR FeatureVector,FEATUREFILEINFO m_Ffi)
{
    WORD i;
	WORD dimensionused;
	DWORD points;
	int returned;
	returned=0;
	dimensionused=0;
	//Initializing the feature vector
	for(i=0;i<m_Ffi.m_wTotalDimensions;i++)
	{
	  FeatureVector->m_dOriginalFeature[i]=0;
	}
	//color features
	if(m_Ffi.m_bWithColor==TRUE)
	{
        returned+=MyRetrieveMethod.compute_color_histogram_feature_vector(ImageBytes,
			FeatureVector->m_dOriginalFeature+dimensionused,false,
			m_Ffi.m_bDescription_CF,m_Ffi.m_bColorSpace_CF,Bins[m_Ffi.m_bBins_CF],
			FeatureVector->m_bBitCount,FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight);
		if(m_Ffi.m_bColorSpace_CF<6||m_Ffi.m_bColorSpace_CF>12)
		  dimensionused=3*Bins[m_Ffi.m_bBins_CF];
		else
		  dimensionused=Bins[m_Ffi.m_bBins_CF];
	}
	//Invariant features
	if(m_Ffi.m_bWithRTInvariant==TRUE)
	{
	    if(m_Ffi.m_bPoints_IF<4)
		  points=FeatureVector->m_lImageWidth*FeatureVector->m_lImageHeight/(1<<m_Ffi.m_bPoints_IF);
		else
          points=1000*(1<<(m_Ffi.m_bPoints_IF-4));
		returned+=MyRetrieveMethod.compute_haar_integral_invariant_feature_vector(ImageBytes,
			FeatureVector->m_dOriginalFeature+dimensionused,points,Angles[m_Ffi.m_bAngles_IF],
			false,m_Ffi.m_bDescription_IF,m_Ffi.m_bColorSpace_IF,Bins[m_Ffi.m_bBins_IF],
			FeatureVector->m_bBitCount,FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight);
		if(m_Ffi.m_bDescription_IF==0)
		 {
		   if(m_Ffi.m_bColorSpace_IF<6||m_Ffi.m_bColorSpace_IF>12)
		     dimensionused+=3;
		   else
		     dimensionused+=1;
		 }
		 else
		 {
		   if(m_Ffi.m_bColorSpace_IF<6||m_Ffi.m_bColorSpace_IF>12)
		    dimensionused+=3*Bins[m_Ffi.m_bBins_IF];
		   else
		    dimensionused+=Bins[m_Ffi.m_bBins_IF];
		 }
	}
	
	
	//Texture feature
	if(m_Ffi.m_bWithTexture==TRUE)
	{
	   returned+=MyRetrieveMethod.compute_texture_feature_vector(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,
		  m_Ffi.m_bDescription_TF,m_Ffi.m_bColorSpace_TF,m_Ffi.m_bCoocurrence_TF,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,m_Ffi.m_wDimension_TF,&dimensionused);
	}
	
	//Shape feature
	if(m_Ffi.m_bWithShape==TRUE)
	{
	   returned+=MyRetrieveMethod.compute_shape_feature_vector(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,
		  m_Ffi.m_bDescription_SF,m_Ffi.m_bColorSpace_SF,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,m_Ffi.m_wDimension_SF,&dimensionused);
	}
	
	//Other features
	if(m_Ffi.m_bWithOthers==TRUE)
	{
	  if(m_Ffi.m_bWithFeature1_OF==TRUE)
	  {
	     returned+=MyRetrieveMethod.compute_other_feature_vector1(ImageBytes,
		  CodeBookY1,CodeBookY2,CodeBookY3,CodeBookY4,
		  CodeBookCb1,CodeBookCb2,CodeBookCb3,CodeBookCb4,
		  CodeBookCr1,CodeBookCr2,CodeBookCr3,CodeBookCr4,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	  if(m_Ffi.m_bWithFeature2_OF==TRUE)
	  {
	     returned+=MyRetrieveMethod.compute_other_feature_vector2(ImageBytes,
		  VQCodeBookY,VQCodeBookCb,VQCodeBookCr,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	  if(m_Ffi.m_bWithFeature3_OF==TRUE)
	  {
	     returned+=MyRetrieveMethod.compute_other_feature_vector3(ImageBytes,
		  VQCodeBookY1,VQCodeBookY2,
		  VQCodeBookCb1,VQCodeBookCb2,
		  VQCodeBookCr1,VQCodeBookCr2,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	  if(m_Ffi.m_bWithFeature4_OF==TRUE)
	  {
	    returned+=MyRetrieveMethod.compute_other_feature_vector4(ImageBytes,
		  VQCodeBookYM,VQCodeBookYR,
		  VQCodeBookCbM,VQCodeBookCbR,
		  VQCodeBookCrM,VQCodeBookCrR,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	}
	
	if(dimensionused!=m_Ffi.m_wTotalDimensions)return 1;
	return returned;
}

//To judge if the selected file can be used as a query image
bool CVqRetrieveDoc::IsImageValid(CString ImagePathName)
{
	CFile file;
	//CJpeg jpg;
	BITMAPFILEHEADER Retrievebitfile;
    BITMAPINFOHEADER Retrievebitinfo;
	CString ext=ImagePathName.Right(3);
	////Check If the image is a 256-gray/24bits image or not
	if(ext=="bmp")
	{
	  //Image open failed
	  if(file.Open(ImagePathName,CFile::modeRead,NULL)==NULL)return false; 
	  if(file.Read(&Retrievebitfile,sizeof(BITMAPFILEHEADER))!=sizeof(BITMAPFILEHEADER))
	  {
	    file.Close();
	    return false;
	  }
	  if(file.Read(&Retrievebitinfo,sizeof(BITMAPINFOHEADER))!=sizeof(BITMAPINFOHEADER))
	  {
	    file.Close();
	    return false;
	  }
	  file.Close();
	  if(Retrievebitfile.bfType!=0x4d42)return false;
	  if(Retrievebitinfo.biBitCount!=8&&Retrievebitinfo.biBitCount!=24)return false;
	  ////Check If the image is compressed or not
      if(Retrievebitinfo.biCompression!=0)return false;
	  return true;
	}
	else if(ext=="jpg")
	{
	  //if(jpg.open(ImagePathName,IDCT_INT))jpg.close();
	  //else  return false;
	  return true;
	}
	return true;
}

//Creat database memory for feature vectors and their mean and variance values
bool CVqRetrieveDoc::CreateDatabaseMemory()
{
	long int i;
	m_hDFeatureVector=GlobalAlloc(GMEM_FIXED,
	m_validnum*(sizeof(FEATUREVECTOR)+m_ffi.m_wTotalDimensions*2*sizeof(double))
	+m_ffi.m_wTotalDimensions*2*sizeof(double)
	+((m_ffi.m_wTotalDimensions+2)*sizeof(double)
	+sizeof(DWORD))*MAX_CODEBOOK_SIZE
	+sizeof(WORD)*m_validnum);
	if(m_hDFeatureVector==NULL)
	{
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return false;
	}
	///The address of m_lpDFeatureVectors
	m_lpDFeatureVector=(LPFEATUREVECTOR)m_hDFeatureVector;
	for(i=0;i<m_validnum;i++)
	{
	  m_lpDFeatureVector[i].m_dOriginalFeature=(double *)((char *)m_hDFeatureVector+m_validnum*sizeof(FEATUREVECTOR))
	  +i*m_ffi.m_wTotalDimensions;
	}
	for(i=0;i<m_validnum;i++)
	{
	  m_lpDFeatureVector[i].m_dNormalizedFeature=m_lpDFeatureVector[0].m_dOriginalFeature
	  +(i+m_validnum)*m_ffi.m_wTotalDimensions;
	}
	m_wIndex=(WORD *)(m_lpDFeatureVector[0].m_dNormalizedFeature+m_validnum*m_ffi.m_wTotalDimensions);
	m_dwNumberinCluster=(DWORD *)(m_wIndex+m_validnum);
	m_dCodeword=(double *)(m_dwNumberinCluster+MAX_CODEBOOK_SIZE);
	///The address of m_lpDComponentInfo
	m_lpDComponentInfo=(LPCOMPONENTINFO)(m_dCodeword+(m_ffi.m_wTotalDimensions+2)*MAX_CODEBOOK_SIZE);
	return true;	
}

////Get the Exact Valid images numer. 
bool CVqRetrieveDoc::GetValidImagesNumber(CString sPath, long int *number)
{
	//The variable to sum the valid image numbers
	//long int ImageNumberChoose=0;
	CFileFind file;
	CString str;
	BOOL bContinueNumber;
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.bmp";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
        ///Continue Checking
		bContinueNumber=file.FindNextFile();
		if(!file.IsDirectory()&&!file.IsDots())
		{	
		    //Judge if the file can be opened?
			if(IsImageValid(file.GetFilePath())==TRUE)
			{
		      *number=*number+1;
		      if(*number>=MAX_IMAGE_NUMBER)return false;
			}
		}
	}
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.jpg";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
        ///Continue Checking
		bContinueNumber=file.FindNextFile();
		if(!file.IsDirectory()&&!file.IsDots())
		{	
		    //Judge if the file can be opened?
			if(IsImageValid(file.GetFilePath())==TRUE)
			{
		      *number=*number+1;
		      if(*number>=MAX_IMAGE_NUMBER)return false;
			}
		}
	}
    //Checking the sub directories	
	file.Close();
	str.Empty();
	str=sPath;
	if(str.Right(1)!="\\")str+="\\";
	str+="*.*";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber=file.FindNextFile();
		if(file.IsDots())continue;
		else if(file.IsDirectory())
		{
			GetValidImagesNumber(file.GetFilePath(),number);
		    if(*number>=MAX_IMAGE_NUMBER)return false;
		}
	}
	return true;
}

///Get the approximate image number
bool CVqRetrieveDoc::GetApproximateImagesNumber(CString sPath,long int *number)
{
	//For the root directory
	CFileFind file;
	CString str;
	str=sPath;
	BOOL bContinueNumber;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.bmp";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
	  bContinueNumber=file.FindNextFile();
	  if(!file.IsDirectory()&&!file.IsDots())
	  {
		*number=*number+1;
		if(*number<0)return false;
	  }
	}
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.jpg";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
	  bContinueNumber=file.FindNextFile();
	  if(!file.IsDirectory()&&!file.IsDots())
	  {
		*number=*number+1;
	    if(*number<0)return false;
	  }
	}
    
	//For sub-directory	
	file.Close();
	str.Empty();
	str=sPath;
	if(str.Right(1)!="\\")str+="\\";
	str+="*.*";
	bContinueNumber=file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber=file.FindNextFile();
		if (file.IsDots()) continue;
		else if(file.IsDirectory())
		{
			GetApproximateImagesNumber(file.GetFilePath(),number);
			if(*number<0)return false;
		}
	}
	return true;
}
void CVqRetrieveDoc::QueryStatusIntial()
{
    m_bFileOpened=false;//The Query image is not opened
	m_bQueryFileChanged=false;//The query file is not changed
	m_bQueryImageNormalized=false;//The query feature is not normalized
	m_bQueryImageFeature=false;  //The Feature of Query image hasn't been computed
	m_bRetrieveDisplay=false;  //Clear the previous retrieval results display flag
 	//m_bFeedBack=false;         //Clear the feedback flag
	m_bRetrieveInterrupt=false;//
	m_bRetrieving=false;//
	m_bRetrieved=false;//
}

void CVqRetrieveDoc::DatabaseStatusInitial()
{
    m_totalnum=0;
	m_validnum=0;
	m_extractednum=0;
	m_normalizednum=0;
	m_clusters=10;
	m_sDatabasePath="No image database is selected!";//No datbase path is selected
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedvqfeaturefile="No vq feature file saved";
	m_bDatabaseOpened=false;
	m_bDatabaseChanged=false;
	m_bDatabaseFeatureComputed=false;	
	m_bDatabaseFeatureComputing=false;	
	m_bDatabaseFeatureInterrupted=false;
	m_bDatabaseFeatureNormalized=false;	
	m_bDatabaseClustered=false;
	m_bFeatureFileSaved=false;
	m_bCodebookFileSaved=false;
	m_bVQFeatureFileSaved=false;
	m_standard=FALSE;
	m_classes=0;
	m_imageineachclass=0;
	m_featuresorted=FALSE;
	DestroyDatabaseMemory();
}

void CVqRetrieveDoc::DisplayPage(int page)
{
  int i,num;
  if(m_page_setting_saved==0)
    num=1;
  else
    num=16;
  m_uDisplayNumber=0;
  for(i=0;i<num;i++)
  {
    if(page*16+i>=m_retrievednum)break;
	m_uDisplayNumber++;
	FeatureVectorCopy(&m_cDisplayFeatureVector[i],&m_lpRFeatureVector[RetrievedResult[page*16+i].m_dwImageIndex],0);
	m_dDisplayFileDistance[i]=RetrievedResult[page*16+i].m_fDistance;
  }
  m_bRetrieveDisplay=true;
  UpdateAllViews(NULL);
}

void CVqRetrieveDoc::RetrievalStatusIntial()
{
	m_displaypage=0; //The first page
	m_page_setting=1;//The number of returned pages  1
	m_page_setting_saved=1;//The number of returned pages  1
	m_validnum_r=0;
	m_sRetrievePath="No feature path is opened";
	m_bFeatureFileOpened=false;
	m_bCodebookFileOpened=false;
    m_bSorted=false;
	m_bRetrieving=false;  //No retrieving
	m_bRetrieveInterrupt=false;  //No retrieving interrupted
	m_bRetrieveDisplay=false;    //No retrieval results
    m_iRetrieveMethod=0;
	m_iSimpleFeedBackMethod=0;
	m_bQueryImageFeature=false;
	m_bQueryImageNormalized=false;
	m_everinterrupted="Unknown";
	m_readfeaturename="No feature file opened";
	m_readbookname="No codebook file opened";
	m_featuredimension=0;
	lastpathname="";
	lastpathname1="";
	lastpathname2="";
	m_basedonnormalized="Unknown";
	m_clustersused=0;
	m_retrievednum=0;
	oldmethod=-1;
	m_T1=4;
	m_T2=8;
	int i;
	for(i=0;i<=4;i++)
	  weights[i]=1.0;
	for(i=5;i<=8;i++)
	  weights[i]=(float)(1.0-1.0/4.0*(i-4));
	weights[9]=0.0;
	weights[10]=0.0;
	m_Iterations=0;
	DestroyRetrievalMemory();
}
void CVqRetrieveDoc::OpenStandardBMPHeader()
{
	Success=TRUE;
    long int fh;
    LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
    //open the standard file
	fh=_open("standard.dat",_O_RDONLY|_O_BINARY);
	if(fh==-1)
	{
		MessageBox(NULL,"[standard.dat] no found or error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
	}
    //Read file
    if(_read(fh,m_StandardBmpInfo,1078)==-1)
    {
	  _close(fh);   
      MessageBox(NULL,"[standard.dat] read error!","Initial",MB_ICONSTOP|MB_OK);
	  Success=FALSE;
	  return;
    }
    _close(fh);   
    //Read Infomation
	bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
    bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
    //Judge the information of the standard file
	if(bitfile->bfType!=0x4d42||bitfile->bfOffBits!=1078||bitinfo->biBitCount!=8||bitinfo->biCompression!=0)
	{
		MessageBox(NULL,"[standard.dat] format error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
	}

	fh=_open("standardc.dat",_O_RDONLY|_O_BINARY);
	if(fh==-1)
	{
		MessageBox(NULL,"[standardc.dat] no found or error!","Initial",MB_ICONSTOP|MB_OK);
		Success=FALSE;
		return;
	}
    //Read file
    if(_read(fh,m_StandardBmpInfoc,54)==-1)
    {
	  _close(fh);   
      MessageBox(NULL,"[standardc.dat] read fail!","Initial",MB_ICONSTOP|MB_OK);
	  Success=FALSE;
	  return;
    }
    _close(fh);   
    //Read Infomation
	bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
    bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
    //Judge the information of the standard file
	if(bitfile->bfType!=0x4d42||bitfile->bfOffBits!=54||bitinfo->biBitCount!=24||bitinfo->biCompression!=0)
	{
		MessageBox(NULL,"[standardc.dat] format error!","Initial",MB_ICONSTOP|MB_OK);
        Success=FALSE;
		return;
	}
}

int CVqRetrieveDoc::FullSearchRetrieveMethod()
{
  double timeused=0.0;
  int a;
  a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::UpdatingFullSearchRetrieveMethod()
{
   double timeused=0.0;
   int a=0;
   while(m_validnum_r>m_retrievednum)
   {
	 if(m_bRetrieveInterrupt==true)return 1;
	 if(m_validnum_r-m_retrievednum>=16)
		 a+=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused);
	 else
		 a+=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused);
	 DisplayPage(m_displaypage);
	 ::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 ::TranslateMessage(&Mymsg);  ////Translate Message
	 ::DispatchMessage(&Mymsg);///Response
   }
   return a;
}

int CVqRetrieveDoc::EKNNSRetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_page_setting_saved==-1||m_page_setting_saved*16>m_validnum_r)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.ENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first K=p*16 images
    a=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_page_setting_saved*16,RetrievedResult,&timeused,FALSE,NULL);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::EEKNNSRetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_page_setting_saved==-1||m_page_setting_saved*16>m_validnum_r)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.EENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first K=p*16 images
    a=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_page_setting_saved*16,RetrievedResult,&timeused,FALSE,NULL);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::EEEKNNSRetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_page_setting_saved==-1||m_page_setting_saved*16>m_validnum_r)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.EEENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first K=p*16 images
    a=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_page_setting_saved*16,RetrievedResult,&timeused,FALSE,NULL);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::IEKNNSURetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_validnum_r<16)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.ENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first 16 images
	a=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::IEEKNNSURetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_validnum_r<16)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.EENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first 16 images
	a=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::IEEEKNNSURetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_validnum_r<16)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.EEENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first 16 images
	a=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::IEKNNSBRetrieveMethod()
{
   double timeused=0.0;
   int a=0,i;
   if(m_validnum_r<16)//all
     a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
   else if(m_page_setting_saved==0)//the first one
   {
	   a=MyRetrieveMethod.ENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	   m_retrievednum=1;
   }
   else if(m_page_setting_saved==-1||m_page_setting_saved*16>=m_validnum_r)
   {
     a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
     DisplayPage(m_displaypage);
     //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 //::TranslateMessage(&Mymsg);  ////Translate Message
	 //::DispatchMessage(&Mymsg);///Response
	 while(m_validnum_r>m_retrievednum)
	 {
       //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	   //::TranslateMessage(&Mymsg);  ////Translate Message
	   //::DispatchMessage(&Mymsg);///Response
	   //if(m_bRetrieveInterrupt==true)return 1;
	   if(m_validnum_r-m_retrievednum>=16)
	     a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	   else
	     a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused,TRUE,SearchIndexList);
	 }
   }
   else
   {
     a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	 DisplayPage(m_displaypage);
     //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 //::TranslateMessage(&Mymsg);  ////Translate Message
	 //::DispatchMessage(&Mymsg);///Response
	 for(i=0;i<m_page_setting_saved-1;i++)
	   a+=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
   }
   m_sRetrieveTime.Empty();
   m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
   return a;
}
int CVqRetrieveDoc::IEEKNNSBRetrieveMethod()
{
   double timeused=0.0;
   int a=0,i;
   if(m_validnum_r<16)//all
     a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
   else if(m_page_setting_saved==0)//the first one
   { 
	  a=MyRetrieveMethod.EENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
   }
   else if(m_page_setting_saved==-1||m_page_setting_saved*16>=m_validnum_r)
   {
     a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
     DisplayPage(m_displaypage);
     //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 //::TranslateMessage(&Mymsg);  ////Translate Message
	 //::DispatchMessage(&Mymsg);///Response
	 while(m_validnum_r>m_retrievednum)
	 {
       //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	   //::TranslateMessage(&Mymsg);  ////Translate Message
	   //::DispatchMessage(&Mymsg);///Response
	   //if(m_bRetrieveInterrupt==true)return 1;
	   if(m_validnum_r-m_retrievednum>=16)
	     a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	   else
	     a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused,TRUE,SearchIndexList);
	 }
   }
   else
   {
     a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	 DisplayPage(m_displaypage);
     //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 //::TranslateMessage(&Mymsg);  ////Translate Message
	 //::DispatchMessage(&Mymsg);///Response
	 for(i=0;i<m_page_setting_saved-1;i++)
	   a+=MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
   }
   m_sRetrieveTime.Empty();
   m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
   return a;
}

int CVqRetrieveDoc::IEEEKNNSBRetrieveMethod()
{
   double timeused=0.0;
   int a=0,i;
   if(m_validnum_r<16)//all
     a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
   else if(m_page_setting_saved==0)//the first one
   { 
	  a=MyRetrieveMethod.EEENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
   }
   else if(m_page_setting_saved==-1||m_page_setting_saved*16>=m_validnum_r)
   {
     a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
     DisplayPage(m_displaypage);
     //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 //::TranslateMessage(&Mymsg);  ////Translate Message
	 //::DispatchMessage(&Mymsg);///Response
	 while(m_validnum_r>m_retrievednum)
	 {
       //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	   //::TranslateMessage(&Mymsg);  ////Translate Message
	   //::DispatchMessage(&Mymsg);///Response
	   //if(m_bRetrieveInterrupt==true)return 1;
	   if(m_validnum_r-m_retrievednum>=16)
	     a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	   else
	     a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r-m_retrievednum,RetrievedResult,&timeused,TRUE,SearchIndexList);
	 }
   }
   else
   {
     a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
	 DisplayPage(m_displaypage);
     //::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	 //::TranslateMessage(&Mymsg);  ////Translate Message
	 //::DispatchMessage(&Mymsg);///Response
	 for(i=0;i<m_page_setting_saved-1;i++)
	   a+=MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
   }
   m_sRetrieveTime.Empty();
   m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
   return a;
}

int CVqRetrieveDoc::EEEKNNSinVQNNRetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_page_setting_saved==-1||m_page_setting_saved*16>m_validnum_r)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	a=MyRetrieveMethod.EEENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	m_retrievednum=1;
  }
  else//the first K=p*16 images
    a=MyRetrieveMethod.EEEKNNSinVQNNRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,m_clustersused,&m_retrievednum,m_page_setting_saved*16,m_dCodeword_r,m_dwNuminEachCluster_r,RetrievedResult,&timeused);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::InsertingEEEKNNS(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD dimension,DWORD firstposi,DWORD lastsize,DWORD InsertVectorNum,DWORD clustersize,LPRETRIEVEDRESULT RetrievedResult)
{
  DWORD p;//The index of least mean distance candidate
  int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
  int m,n,w;//for the loop 
  double dsqrt,dsqrtv;//sqrt sqrtv distance for vector[K-1]
  double dtmp=0.0,pds;  ///temp double varaiable
  double mmax,mmin,vmax,vmin;
  LONG low,high;//The lower and higher limits to be searched
  BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
  DWORD itmp;
  DWORD I=clustersize;
  DWORD K=lastsize+InsertVectorNum;
  if(InsertVectorNum<=0||InsertVectorNum>clustersize)return -1;
  double mx=QueryImageFeatureVector.m_dNAverage;
  double vx=QueryImageFeatureVector.m_dNVariance;
  
  double *dmin= new double [K];//distance for K vectors
  if(dmin==NULL)return -1;
  DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
  if(index==NULL)
  {
    delete [] dmin;
	return -1;
  }
  
  //+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
  i=0;
  j=clustersize-1;
  if(mx<=(lpFeatureVector+firstposi+i)->m_dNAverage)p=i;
  //If smaller than the maximum mean
  else if(mx>=(lpFeatureVector+firstposi+j)->m_dNAverage)p=j;
  else
  {
    while(j-i>1)
	{
      p=(i+j)/2;
      if(mx<=(lpFeatureVector+firstposi+p)->m_dNAverage)
	  j=p;
      else 
	  i=p;
      if(fabs(mx-(lpFeatureVector+firstposi+j)->m_dNAverage)>=fabs(mx-(lpFeatureVector+firstposi+i)->m_dNAverage))
	   p=i;
      else
	   p=j;
	}
  }
  //++++++++++Get the lower and upper limits+++++++++
  if(InsertVectorNum%2==0)
  {
    low=p-(InsertVectorNum/2);
    high=p+(InsertVectorNum/2)-1;
  }
  else
  {
    low=p-(InsertVectorNum-1)/2;
    high=p+(InsertVectorNum-1)/2;
  }
  if(low<0)//if lower than 0
  {
    low=0;
    high=InsertVectorNum-1;
    flagdown=TRUE;
  }
  if(high>(LONG)(I-1))//if larger than the list length
  {
    low=I-InsertVectorNum;
    high=I-1;
    flagup=TRUE;
  }
  ///If InsertVectorNum==I then no up and down search is performed
  if(InsertVectorNum==I)
  {
    flagup=TRUE;
	flagdown=TRUE;
  }
  
  //copy the dmin from previous results
  for(i=0;i<(int)lastsize;i++)
  {
    dmin[i]=RetrievedResult[i].m_fDistance;
	index[i]=RetrievedResult[i].m_dwImageIndex;
  }
  
  
  //++++++++++++++calculate the InsertVectorNum distances+++++++++++
  for(i=low;i<=high;i++)
  {
    dmin[i-low+lastsize]=0.0;
    index[i-low+lastsize]=i+firstposi;// get the index[i] 
    for(k=0;k<dimension;k++)
	{
	  dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-(lpFeatureVector+firstposi+i)->m_dNormalizedFeature[k];
	  dmin[i-low+lastsize]+=dtmp*dtmp;
	}
  }
  
  ///Sorting in the ascending order
  //Bubble sort for current computed K distances
  for(m=1;m<(int)K;m++)
  {
    for(n=0;n<(int)K-m;n++)
	{
	  if(dmin[n]>dmin[n+1])///
	  {
	      dtmp=dmin[n];
		  dmin[n]=dmin[n+1];
		  dmin[n+1]=dtmp;
		  itmp=index[n];
		  index[n]=index[n+1];
		  index[n+1]=itmp;
		  itmp=RetrievedResult[n].m_dwImageIndex;
		  RetrievedResult[n].m_dwImageIndex=RetrievedResult[n+1].m_dwImageIndex;
		  RetrievedResult[n+1].m_dwImageIndex=itmp;
          dtmp=RetrievedResult[n].m_fDistance;
		  RetrievedResult[n].m_fDistance=RetrievedResult[n+1].m_fDistance;
		  RetrievedResult[n+1].m_fDistance=(float)dtmp;
	  }
	}
  }
  //Initial Setting before searching
  //The start point is j=min{p-low+1,high-p+1}
  j=p-low+1;
  if(j>(int)(high-p+1))j=high-p+1;
  if(low==0)j=high-p+1;
  if(high==(LONG)I-1)j=p-low+1;
  //Get the sqrt sqrtv distance for vector[K-1]
  dsqrt=sqrt(dmin[K-1]/dimension);
  dsqrtv=sqrt(dmin[K-1]);
  //The mmax and mmin
  mmax=mx+dsqrt;
  mmin=mx-dsqrt;
  //The vmax and vmin
  vmax=vx+dsqrtv;
  vmin=vx-dsqrtv;
  for(w=0;w<(int)(I-InsertVectorNum+2);w++)
  {
      //The terminate flags
	  if(flagup==TRUE&&flagdown==TRUE)break;
      ////If we need search in the low direction
	  if(flagdown==FALSE)
	  {
	    if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		else if((int)p-j<low)
		{
		    if((lpFeatureVector+p-j+firstposi)->m_dNAverage<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if((lpFeatureVector+p-j+firstposi)->m_dNVariance>vmin&&(lpFeatureVector+p-j+firstposi)->m_dNVariance<vmax)
			{
              dtmp=((lpFeatureVector+p-j+firstposi)->m_dNVariance-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-(lpFeatureVector+p-j+firstposi)->m_dNAverage);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
				 ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-(lpFeatureVector+firstposi+p-j)->m_dNormalizedFeature[k];
			      pds+=dtmp*dtmp;
			      if(pds>=dmin[K-1])break;
				}
			    if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
				{
			      //initial pds as the dmin[K-1]
			      index[K-1]=firstposi+p-j;
                  dmin[K-1]=pds;
			      for(m=K-1;m>=1;m--)//insearting
				  {
			        if(dmin[m]<dmin[m-1])
					{
				      dtmp=dmin[m];
				      dmin[m]=dmin[m-1];
				      dmin[m-1]=dtmp;
				      itmp=index[m];
				      index[m]=index[m-1];
				      index[m-1]=itmp;
					}
				    else
				      break;
				  }
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }   
			}
		}
	  }
      ////If we need search in the low direction
	  if(flagup==FALSE)
	  {
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else if((int)p+j>high)
		  {
		    if((lpFeatureVector+p+j+firstposi)->m_dNAverage>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if((lpFeatureVector+p+j+firstposi)->m_dNVariance>vmin&&(lpFeatureVector+p+j+firstposi)->m_dNVariance<vmax)
			{
              dtmp=((lpFeatureVector+p+j+firstposi)->m_dNVariance-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-(lpFeatureVector+p+j+firstposi)->m_dNAverage);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			   	 dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-(lpFeatureVector+firstposi+p+j)->m_dNormalizedFeature[k];
			     pds+=dtmp*dtmp;
			     if(pds>=dmin[K-1])break;
				}
			    if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
				{
			      //initial pds as the dmin[K-1]
			      index[K-1]=firstposi+p+j;
                  dmin[K-1]=pds;
			      for(m=K-1;m>=1;m--)//insearting
				  {
			        if(dmin[m]<dmin[m-1])
					{
				      dtmp=dmin[m];
				      dmin[m]=dmin[m-1];
				      dmin[m-1]=dtmp;
				      itmp=index[m];
				      index[m]=index[m-1];
				      index[m-1]=itmp;
					}
				    else
				     break;
				  }
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		  }
	  }
	  j=j+1;
   }
   for(n=0;n<(int)K;n++)
   {
    RetrievedResult[n].m_fDistance=(float)dmin[n];
    RetrievedResult[n].m_dwImageIndex=index[n];
   }
   delete []dmin;
   delete []index;
   return 0;
}

int CVqRetrieveDoc::UpdatingEEEKNNS(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD dimension,DWORD firstposi,DWORD VectorNumberTobeSearched,DWORD clustersize,LPRETRIEVEDRESULT RetrievedResult)
{
  DWORD p;//The index of least mean distance candidate
  int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
  int m,n,w;//for the loop 
  double dsqrt,dsqrtv;//sqrt sqrtv distance for vector[K-1]
  double dtmp=0.0,pds;  ///temp double varaiable
  double mmax,mmin,vmax,vmin;
  BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
  DWORD itmp;
  DWORD I=clustersize;
  DWORD K=VectorNumberTobeSearched;
  
  double mx=QueryImageFeatureVector.m_dNAverage;
  double vx=QueryImageFeatureVector.m_dNVariance;
  
  double *dmin= new double [K];//distance for K vectors
  if(dmin==NULL)return -1;
  DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
  if(index==NULL)
  {
    delete [] dmin;
	return -1;
  }
  
  //+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
  i=0;
  j=clustersize-1;
  if(mx<=(lpFeatureVector+firstposi+i)->m_dNAverage)p=i;
  //If smaller than the maximum mean
  else if(mx>=(lpFeatureVector+firstposi+j)->m_dNAverage)p=j;
  else
  {
    while(j-i>1)
	{
      p=(i+j)/2;
      if(mx<=(lpFeatureVector+firstposi+p)->m_dNAverage)
	   j=p;
      else 
	   i=p;
      if(fabs(mx-(lpFeatureVector+firstposi+j)->m_dNAverage)>=fabs(mx-(lpFeatureVector+firstposi+i)->m_dNAverage))
	   p=i;
      else
	   p=j;
	}
  }

  //copy the dmin/index from previous results
  for(i=0;i<(int)K;i++)
  {
    dmin[i]=RetrievedResult[i].m_fDistance;
	index[i]=RetrievedResult[i].m_dwImageIndex;
  }
  
  //Initial Setting before searching
  //The start point is j=0
  j=0;
  //Get the sqrt sqrtv distance for vector[K-1]
  dsqrt=sqrt(dmin[K-1]/dimension);
  dsqrtv=sqrt(dmin[K-1]);
  //The mmax and mmin
  mmax=mx+dsqrt;
  mmin=mx-dsqrt;
  //The vmax and vmin
  vmax=vx+dsqrtv;
  vmin=vx-dsqrtv;
  for(w=0;w<(int)I;w++)
  {
      //The terminate flags
	  if(flagup==TRUE&&flagdown==TRUE)break;
      ////If we need search in the low direction
	  if(flagdown==FALSE)
	  {
	    if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		else
		{
		    if((lpFeatureVector+p-j+firstposi)->m_dNAverage<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if((lpFeatureVector+p-j+firstposi)->m_dNVariance>vmin&&(lpFeatureVector+p-j+firstposi)->m_dNVariance<vmax)
			{
              dtmp=((lpFeatureVector+p-j+firstposi)->m_dNVariance-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-(lpFeatureVector+p-j+firstposi)->m_dNAverage);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
				 ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-(lpFeatureVector+firstposi+p-j)->m_dNormalizedFeature[k];
			      pds+=dtmp*dtmp;
			      if(pds>=dmin[K-1])break;
				}
			    if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
				{
			      //initial pds as the dmin[K-1]
			      index[K-1]=firstposi+p-j;
                  dmin[K-1]=pds;
			      for(m=K-1;m>=1;m--)//insearting
				  {
			        if(dmin[m]<dmin[m-1])
					{
				      dtmp=dmin[m];
				      dmin[m]=dmin[m-1];
				      dmin[m-1]=dtmp;
				      itmp=index[m];
				      index[m]=index[m-1];
				      index[m-1]=itmp;
					}
				    else
				      break;
				  }
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }   
			}
		}
	  }
	  ////If we need search in the low direction
	  if(j!=0&&flagup==FALSE)
	  {
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else
		  {
		    if((lpFeatureVector+p+j+firstposi)->m_dNAverage>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if((lpFeatureVector+p+j+firstposi)->m_dNVariance>vmin&&(lpFeatureVector+p+j+firstposi)->m_dNVariance<vmax)
			{
              dtmp=((lpFeatureVector+p+j+firstposi)->m_dNVariance-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-(lpFeatureVector+p+j+firstposi)->m_dNAverage);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			   	 dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-(lpFeatureVector+firstposi+p+j)->m_dNormalizedFeature[k];
			     pds+=dtmp*dtmp;
			     if(pds>=dmin[K-1])break;
				}
			    if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
				{
			      //initial pds as the dmin[K-1]
			      index[K-1]=firstposi+p+j;
                  dmin[K-1]=pds;
			      for(m=K-1;m>=1;m--)//insearting
				  {
			        if(dmin[m]<dmin[m-1])
					{
				      dtmp=dmin[m];
				      dmin[m]=dmin[m-1];
				      dmin[m-1]=dtmp;
				      itmp=index[m];
				      index[m]=index[m-1];
				      index[m-1]=itmp;
					}
				    else
				     break;
				  }
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		  }
	  }
	  j=j+1;
   }
   for(n=0;n<(int)K;n++)
   {
    RetrievedResult[n].m_fDistance=(float)dmin[n];
    RetrievedResult[n].m_dwImageIndex=index[n];
   }
   delete []dmin;
   delete []index;
   return 0;
}


int CVqRetrieveDoc::UpdatingEEEKNNSinVQKNNRetrieval(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i,j,k,sum,posi,sum2,sum3,number,check,l;
  int SIZE=booksize/2;
  PRETRIEVEDRESULT p=new RETRIEVEDRESULT[SIZE];
  RETRIEVEDRESULT p1;
  if(p==NULL)return -2;
  //Judge the parameter
   if(booksize>1024||booksize<5)return -1;
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>TotalVectorNumber||VectorNumberTobeSearched<1)return -3;//Larger than 50% of the whole database
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  
  //get the initial time
  time1=clock();
  
  //find the best K codewords of the query image K=SIZE
  MyRetrieveMethod.EEEKNNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,
  QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
  codeword,booksize,SIZE,VectorDimension,p);

  //get the clusters which just have enough vectors to be searched
  sum=0;
  for(i=0;i<SIZE;i++)
  {
    sum+=numincluster[p[i].m_dwImageIndex];
	if(sum>=(int)VectorNumberTobeSearched)break;
  }
  if(sum<=(int)VectorNumberTobeSearched)VectorNumberTobeSearched=sum;
  posi=i;
  sum3=0;
  for(i=0;i<posi;i++)
  {
    sum2=0;
    for(j=0;j<(int)p[i].m_dwImageIndex;j++)
	{
	  sum2+=numincluster[j];
	}
    MyRetrieveMethod.FullSearchMethod(QueryImageFeatureVector.m_dNormalizedFeature,
		(lpFeatureVector+sum2)->m_dNormalizedFeature,
		numincluster[p[i].m_dwImageIndex],
		VectorDimension,
		RetrievedResult+sum3);
	for(l=0;l<(int)numincluster[p[i].m_dwImageIndex];l++)
	{
	  RetrievedResult[sum3+l].m_dwImageIndex+=sum2;
	}
    if(sum3>0)
	{
      for(number=sum3;number<(int)(sum3+numincluster[p[i].m_dwImageIndex]);number++)
	  {
	    for(check=0;check<(int)(sum3+numincluster[p[i].m_dwImageIndex]);check++)
		{
		  if(RetrievedResult[number].m_fDistance<RetrievedResult[check].m_fDistance)
		  {
		    p1=RetrievedResult[check];
			RetrievedResult[check]=RetrievedResult[number];
			for(l=number;l>=check+2;l--)
			  RetrievedResult[l]=RetrievedResult[l-1];
			RetrievedResult[check+1]=p1;
		    break;
		  }
		}
	  }
	}
	sum3+=numincluster[p[i].m_dwImageIndex];
    DisplayPage(m_displaypage);
    ::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	::TranslateMessage(&Mymsg);  ////Translate Message
	::DispatchMessage(&Mymsg);///Response
  }
  long int RetrievedNumber1=0;
  double RetrieveTime1=0;
  //search the left with EEEKNNS method
  for(i=posi;i<SIZE;i++)
  {
    sum2=0;
    for(j=0;j<(int)p[i].m_dwImageIndex;j++)
	{
	  sum2+=numincluster[j];
	}
	if(i==posi)
	{
      if(posi==0)
	  {
		k=MyRetrieveMethod.EEEKNNSRetrieveMethod(QueryImageFeatureVector,lpFeatureVector+sum2,VectorDimension,numincluster[p[i].m_dwImageIndex],&RetrievedNumber1,VectorNumberTobeSearched,RetrievedResult,&RetrieveTime1,FALSE,NULL);
	    for(l=0;l<(int)numincluster[p[i].m_dwImageIndex];l++)
		{
	      RetrievedResult[l].m_dwImageIndex+=sum2;
		}
	  }
      else
	    k=InsertingEEEKNNS(QueryImageFeatureVector,lpFeatureVector,VectorDimension,sum2,sum3,VectorNumberTobeSearched-sum3,numincluster[p[i].m_dwImageIndex],RetrievedResult);
	}
	else
	{
	  k+=UpdatingEEEKNNS(QueryImageFeatureVector,lpFeatureVector,VectorDimension,sum2,VectorNumberTobeSearched,numincluster[p[i].m_dwImageIndex],RetrievedResult);
	}
    sum3+=numincluster[p[i].m_dwImageIndex];
  }
  //get the finished time
  time2=clock();
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  delete []p;
  return k;
}


int CVqRetrieveDoc::UpdatingEEEKNNSinVQKNNRetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_page_setting_saved==-1||m_page_setting_saved*16>m_validnum_r)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.EEENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first K=p*16 images
    a=UpdatingEEEKNNSinVQKNNRetrieval(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,m_clustersused,&m_retrievednum,m_page_setting_saved*16,m_dCodeword_r,m_dwNuminEachCluster_r,RetrievedResult,&timeused);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;
}

int CVqRetrieveDoc::UpdatingEEEKNNSinAllVQRetrieval(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i,j,k,sum,posi,sum2,sum3,number,check,l;
  PRETRIEVEDRESULT p=new RETRIEVEDRESULT[booksize];
  RETRIEVEDRESULT p1;
  if(p==NULL)return -2;
  //Judge the parameter
  if(booksize>1024||booksize<5)return -1;
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>TotalVectorNumber||VectorNumberTobeSearched<1)return -3;//Larger than 50% of the whole database
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  
  //get the initial time
  time1=clock();
  
  MyRetrieveMethod.FullSearchMethod2(QueryImageFeatureVector.m_dNormalizedFeature,codeword,booksize,VectorDimension,p);
  //get the clusters which just have enough vectors to be searched
  sum=0;
  for(i=0;i<booksize;i++)
  {
    sum+=numincluster[p[i].m_dwImageIndex];
	if(sum>=(int)VectorNumberTobeSearched)break;
  }
  if(sum<=(int)VectorNumberTobeSearched)VectorNumberTobeSearched=sum;
  posi=i;
  sum3=0;
  for(i=0;i<posi;i++)
  {
    sum2=0;
    for(j=0;j<(int)p[i].m_dwImageIndex;j++)
	{
	  sum2+=numincluster[j];
	}
    MyRetrieveMethod.FullSearchMethod(QueryImageFeatureVector.m_dNormalizedFeature,
		(lpFeatureVector+sum2)->m_dNormalizedFeature,
		numincluster[p[i].m_dwImageIndex],
		VectorDimension,
		RetrievedResult+sum3);
	for(l=0;l<(int)numincluster[p[i].m_dwImageIndex];l++)
	{
	  RetrievedResult[sum3+l].m_dwImageIndex+=sum2;
	}
    if(sum3>0)
	{
      for(number=sum3;number<(int)(sum3+numincluster[p[i].m_dwImageIndex]);number++)
	  {
	    for(check=0;check<(int)(sum3+numincluster[p[i].m_dwImageIndex]);check++)
		{
		  if(RetrievedResult[number].m_fDistance<RetrievedResult[check].m_fDistance)
		  {
		    p1=RetrievedResult[check];
			RetrievedResult[check]=RetrievedResult[number];
			for(l=number;l>=check+2;l--)
			  RetrievedResult[l]=RetrievedResult[l-1];
			RetrievedResult[check+1]=p1;
		    break;
		  }
		}
	  }
	}
	sum3+=numincluster[p[i].m_dwImageIndex];
    DisplayPage(m_displaypage);
    ::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE); ///Get message
	::TranslateMessage(&Mymsg);  ////Translate Message
	::DispatchMessage(&Mymsg);///Response
  }
  long int RetrievedNumber1=0;
  double RetrieveTime1=0;
  //search the left with EEEKNNS method
  for(i=posi;i<booksize;i++)
  {
    sum2=0;
    for(j=0;j<(int)p[i].m_dwImageIndex;j++)
	{
	  sum2+=numincluster[j];
	}
	if(i==posi)
	{
      if(posi==0)
	  {
		k=MyRetrieveMethod.EEEKNNSRetrieveMethod(QueryImageFeatureVector,lpFeatureVector+sum2,VectorDimension,numincluster[p[i].m_dwImageIndex],&RetrievedNumber1,VectorNumberTobeSearched,RetrievedResult,&RetrieveTime1,FALSE,NULL);
	    for(l=0;l<(int)numincluster[p[i].m_dwImageIndex];l++)
		{
	      RetrievedResult[l].m_dwImageIndex+=sum2;
		}
	  }
      else
	    k=InsertingEEEKNNS(QueryImageFeatureVector,lpFeatureVector,VectorDimension,sum2,sum3,VectorNumberTobeSearched-sum3,numincluster[p[i].m_dwImageIndex],RetrievedResult);
	}
	else
	{
	  k+=UpdatingEEEKNNS(QueryImageFeatureVector,lpFeatureVector,VectorDimension,sum2,VectorNumberTobeSearched,numincluster[p[i].m_dwImageIndex],RetrievedResult);
	}
    sum3+=numincluster[p[i].m_dwImageIndex];
  }
  //get the finished time
  time2=clock();
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  delete []p;
  return k;
}

int CVqRetrieveDoc::UpdatingEEEKNNSinAllVQRetrieveMethod()
{
  double timeused=0.0;
  int a;
  if(m_page_setting_saved==-1||m_page_setting_saved*16>m_validnum_r)//all
    a=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else if(m_page_setting_saved==0)//the first one
  {
	  a=MyRetrieveMethod.EEENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,RetrievedResult,&timeused);
	  m_retrievednum=1;
  }
  else//the first K=p*16 images
    a=UpdatingEEEKNNSinAllVQRetrieval(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,m_clustersused,&m_retrievednum,m_page_setting_saved*16,m_dCodeword_r,m_dwNuminEachCluster_r,RetrievedResult,&timeused);
  m_sRetrieveTime.Empty();
  m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timeused);
  return a;

}

void CVqRetrieveDoc::FeatureVectorCopy(PFEATUREVECTOR FeatureVectorA,PFEATUREVECTOR FeatureVectorB,int style)
{
  FeatureVectorA->m_bBitCount=FeatureVectorB->m_bBitCount;
  FeatureVectorA->m_bType=FeatureVectorB->m_bType;
  FeatureVectorA->m_dNAverage=FeatureVectorB->m_dNAverage;
  if(style==0)
  {
	FeatureVectorA->m_dNormalizedFeature=FeatureVectorB->m_dNormalizedFeature;
    FeatureVectorA->m_dOriginalFeature=FeatureVectorB->m_dOriginalFeature;
  }
  else
  {
    memcpy(FeatureVectorA->m_dNormalizedFeature,FeatureVectorB->m_dNormalizedFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions);
	memcpy(FeatureVectorA->m_dOriginalFeature,FeatureVectorB->m_dOriginalFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions);
  }
  FeatureVectorA->m_dNVariance=FeatureVectorB->m_dNVariance;
  FeatureVectorA->m_dOAverage=FeatureVectorB->m_dOAverage;
  FeatureVectorA->m_dOVariance=FeatureVectorB->m_dOVariance;
  FeatureVectorA->m_lImageHeight=FeatureVectorB->m_lImageHeight;
  FeatureVectorA->m_lImageWidth=FeatureVectorB->m_lImageWidth;
  strcpy(FeatureVectorA->m_sOriginalFileName,FeatureVectorB->m_sOriginalFileName);
  FeatureVectorA->m_wDimensions=FeatureVectorB->m_wDimensions;
}

int CVqRetrieveDoc::GetImageBlocks(char m_sFileName[MAX_PATH],int blockwidth,int blockheight,unsigned long int *total)
{
	CFile file;
	int a,b;
	int blocks;
	CJpeg jpg;
	DWORD m_iImageSize;
	JPEG_IMAGE_INFO info;
	BITMAPFILEHEADER bitfile;
    BITMAPINFOHEADER bitinfo;
	//if(blockwidth!=BLOCKWIDTH&&blockheight!=BLOCKHEIGHT)return -4;
	//Image open failed
	if(file.Open(m_sFileName,CFile::modeRead,NULL)==NULL)return -1; 
	m_iImageSize=file.GetLength();
	if(file.Read(&bitfile,sizeof(BITMAPFILEHEADER))!=sizeof(BITMAPFILEHEADER))
	{
	  file.Close();
	  return -2;
	}
	if(file.Read(&bitinfo,sizeof(BITMAPINFOHEADER))!=sizeof(BITMAPINFOHEADER))
	{
	  file.Close();
	  return -2;
	}
	file.Close();//close the file
    
	if(bitfile.bfType!=0x4d42)
	{
        //Reopen the file
		if(jpg.open(m_sFileName,IDCT_INT))
		{  
	       jpg.getImageInfo(&info);
	       if(info.comNum==3)
		   {
	           if(info.imgHeight>MAXWIDTHORHEIGHT||info.imgHeight<MINWIDTHORHEIGHT||info.imgWidth<MINWIDTHORHEIGHT||info.imgWidth>MAXWIDTHORHEIGHT)
			   {
				 jpg.close();
			     return -3;
			   }
			   jpg.close();
			   a=info.imgWidth/blockwidth;
	           b=info.imgHeight/blockheight;
	           blocks=a*b;
			   total+=info.imgWidth*info.imgHeight;
			   return blocks;
		   }
	       else
		   {
	          jpg.close();
			  return -4;
		   }
	       
		}
		else
 		   return -4;
	}
    ////If the image is a 24bits image or not
	if(bitinfo.biBitCount!=24)
	  return -4;
	////If the image is compressed or not
	if(bitinfo.biCompression!=0)
	  return -4;
	///Check Palette
	if(bitfile.bfOffBits!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)))
	  return -4;
	//File size judgement
	if(m_iImageSize-bitfile.bfOffBits-WIDTHBYTES(24*bitinfo.biWidth)*bitinfo.biHeight<0) 
	  return -4;
	if(bitinfo.biWidth>MAXWIDTHORHEIGHT||bitinfo.biWidth<MINWIDTHORHEIGHT||bitinfo.biHeight<MINWIDTHORHEIGHT||bitinfo.biHeight>MAXWIDTHORHEIGHT)return -3;
	a=bitinfo.biWidth/blockwidth;
	b=bitinfo.biHeight/blockheight;
	blocks=a*b;
	total+=bitinfo.biWidth*bitinfo.biHeight;
    ///end of read Image and computing feature
    return blocks;
}

int CVqRetrieveDoc::GetImageYCbCrComponent(CString ImagePathName,unsigned char *Y,unsigned char *Cb,unsigned char *Cr,int *width,int *height)
{
	if(Y==NULL||Cb==NULL||Cr==NULL)return -4;
	if(ImagePathName=="")return -4;
	unsigned int x,y;
	int type=-1;
	int iBitCount;
	int PaletteNumber;  //PaletteNumber
	LONG ImageWidth;
	LONG ImageHeight;
	unsigned char *m_ImageFile;
	unsigned char *m_bImageData;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	DWORD m_ibfbts,m_iImageSize;
	JPEG_IMAGE_INFO info;
	LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	HGLOBAL hg;
	//open new image
	if(file.Open(ImagePathName,CFile::modeRead,NULL)==NULL)return -1;
	m_iImageSize=file.GetLength();//get the image size
	hg=NULL;//Clear the old image memory
	hg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//apply new image memory
	if(hg==NULL)
	{
	  file.Close();
	  return -2;
	}
	m_ImageFile=(unsigned char *)hg;
	m_bImageData=(BYTE *)(m_ImageFile+m_iImageSize);
	if(file.Read(m_ImageFile,m_iImageSize)!=m_iImageSize)
	{
	  file.Close();
	  GlobalFree(Imagehg);
	  return -2;
	}
	file.Close();//close the file
	bitfile=(LPBITMAPFILEHEADER)m_ImageFile;
	bitinfo=(LPBITMAPINFOHEADER)(m_ImageFile+sizeof(BITMAPFILEHEADER));
	m_ibfbts=bitfile->bfOffBits;
    ImageWidth=bitinfo->biWidth;
	ImageHeight=bitinfo->biHeight;
	iBitCount=bitinfo->biBitCount;
	if(bitfile->bfType!=0x4d42)
	{
        GlobalFree(Imagehg);//Free the memory
		
		//Reopen the file
		if(jpg.open(ImagePathName,IDCT_INT))
		{ 
		  jpg.getImageInfo(&info);
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			ImageWidth=bitinfo->biWidth;
	        ImageHeight=bitinfo->biHeight;
		    linebytes=(info.imgWidth*24+31)/32*4;
			m_ibfbts=bitfile->bfOffBits;
			iBitCount=bitinfo->biBitCount;
			bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
			m_iImageSize=bitfile->bfSize;
		    Imagehg=GlobalAlloc(GMEM_FIXED,m_iImageSize*2);//Apply the required memory
			////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              jpg.close();
			  return -2;
			}
            m_ImageFile=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
			m_bImageData=(BYTE *)(m_ImageFile+m_iImageSize);
	        memcpy(m_ImageFile,m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_ImageFile[54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_ImageFile[54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_ImageFile[54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
            return -3;
		  }
		  jpg.close();
  	    }
		else
 		   return -3;
	}
	
    ////If the image is a 256-gray/24bits image or not
	if(bitinfo->biBitCount!=8&&bitinfo->biBitCount!=24)
	{
	  GlobalFree(Imagehg);//Free the memory
	  return -3;
	}
	////If the image is compressed or not
	if(bitinfo->biCompression!=0)
	{
      GlobalFree(Imagehg);//Free the memory
	  return -3;
	}
	if(bitinfo->biBitCount==24)//No palette
 	  PaletteNumber=0;
	else if (bitinfo->biClrUsed==0) 
	  PaletteNumber=(int)pow(2,bitinfo->biBitCount);
	else
	  PaletteNumber=bitinfo->biClrUsed;
    
	///Check Palette
	if(m_ibfbts!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PaletteNumber*sizeof(RGBQUAD)))
	{
	  GlobalFree(Imagehg);//Free the memory
	  return -3;
	}
    //File size judgement
	switch(iBitCount)
	{
	   case 24:
		 if(m_iImageSize-m_ibfbts-WIDTHBYTES(24*ImageWidth)*ImageHeight<0) 
		 {
			GlobalFree(Imagehg);//Free the memory
			return -3;
		 }
		 break;
	   case 8:
		 if (m_iImageSize-m_ibfbts-SAVEWIDTH(ImageWidth)*ImageHeight<0) 
		 {
			GlobalFree(Imagehg);//Free the memory
			return -3;
		}
		break;
	   default:
		 GlobalFree(Imagehg);//Free the memory
		 return -3;
		break;
	} 
   //Get the RGB data from m_ImageFile
   MyRetrieveMethod.get_data_from_24or8bits_bmp_file(m_ImageFile,m_bImageData,iBitCount,ImageWidth,ImageHeight);
   MyRetrieveMethod.rgb2YCbCr(m_bImageData,m_ImageFile,ImageWidth,ImageHeight);
   *width=ImageWidth;
   *height=ImageHeight;
   
   long int i,j,pp,qq,linebytes1;
   linebytes1=(ImageWidth+3)/4*4;  //for gray scale image
   for(i=0;i<ImageHeight;i++)
   {
     for(j=0;j<ImageWidth;j++)
	 {
	     pp=i*linebytes1+j;
		 qq=j*3+i*3*ImageWidth;
		 Y[pp]=m_ImageFile[qq+2];
	     Cb[pp]=m_ImageFile[qq+1];
	     Cr[pp]=m_ImageFile[qq];
	 }
   }
   
   ///end of Read Image
   return 0;
}


void CVqRetrieveDoc::OnEncodingTest(char m_sFileName[MAX_PATH])
{
    // TODO: Add your command handler code here
	long int fh;
    CImageShow cis;
	//The memory handle
	HGLOBAL hMem;
	//The temp string
    char temp[256];
    //The blocks and counters
	long int blocks;
    long int i,j,k,l;
	long int linebytes;
	unsigned long int totallen;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	unsigned char *ImageYD,*ImageCbD,*ImageCrD;
	//The width and height
	int width,height;
	//The number of blocks in width and height
	unsigned short int wb,hb;
    double c;
	//The pointer for Encode image vectors
	unsigned char *SourceVector[MAXENCODEVECTORS];
	float *DCTSourceVector[MAXENCODEVECTORS];
	float *SourceVector1;
	float *SourceVector2[MAXENCODEVECTORS];
	float *SourceVector3[MAXENCODEVECTORS];
	float *SourceVector4;
	 
	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1,*EncodeCodeIndex2,*EncodeCodeIndex3,*EncodeCodeIndex4;
	
	//The pointer array for generated codevectors by codebook design
	float *DesignCodeVectors1;
	float (*DesignCodeVectors2)[DIMENSION1];
	float (*DesignCodeVectors3)[DIMENSION2];
	float *DesignCodeVectors4;
	float *Code1;
	float (*Code2)[DIMENSION1];
	float (*Code3)[DIMENSION2];
	float *Code4;
	unsigned char *m_DisplayImageBytes[5];
    int BOOKSIZE1, BOOKSIZE2;
    unsigned char INBLOCK[BLOCKHEIGHT][BLOCKWIDTH],*INBLOCK1[BLOCKHEIGHT];
	double OUTDCT[BLOCKHEIGHT][BLOCKWIDTH],DCT1D[VECTORDIMENSION],*OUTDCT1[BLOCKHEIGHT];
	
	
	//mem for test display images
	HGLOBAL testmem=NULL;
    testmem=GlobalAlloc(GMEM_FIXED, 2*(MAXIMAGESIZE+1078)+3*(MAXIMAGESIZE*3+54));
	if(testmem==NULL) 
	{
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);		
	   return;
	}
	m_DisplayImageBytes[0]=(unsigned char *)testmem;
	m_DisplayImageBytes[1]=m_DisplayImageBytes[0]+MAXIMAGESIZE+1078;
    m_DisplayImageBytes[2]=m_DisplayImageBytes[1]+MAXIMAGESIZE+1078;
	m_DisplayImageBytes[3]=m_DisplayImageBytes[2]+MAXIMAGESIZE*3+54;
	m_DisplayImageBytes[4]=m_DisplayImageBytes[3]+MAXIMAGESIZE*3+54;
   
    blocks=GetImageBlocks(m_sFileName,BLOCKWIDTH,BLOCKHEIGHT,&totallen);
    //Apply memory
	hMem=NULL;
	fh=6*MAXIMAGESIZE  //Y Cb Cr YD CbD CrD
	// SourceVector   DCTSourceVector          SourceVector1                 SourceVector2  SourceVector3 SourceVector4
	+blocks*(2*sizeof(float)+VECTORDIMENSION+VECTORDIMENSION*sizeof(float)+sizeof(float)*DIMENSION1+sizeof(float)*DIMENSION2)
	+4*blocks*sizeof(unsigned short int); //EncodeIndex1/2/3/4
	hMem=GlobalAlloc(GMEM_FIXED,fh);
	if(hMem==NULL)
	{
	    sprintf(temp,"Sorry,Memory not enough%fMBytes",(double)(MAXIMAGESIZE)/1024.0/1024.0);
	    MessageBox(NULL,temp,"Encoding",MB_ICONSTOP|MB_OK);
		GlobalFree(testmem);
	    return;
	}
	//Alloc the memory
 	for(i=0;i<blocks;i++)
	  SourceVector[i]=(unsigned char *)hMem+i*VECTORDIMENSION;
	for(i=0;i<blocks;i++)
	  DCTSourceVector[i]=(float *)((unsigned char *)hMem+blocks*VECTORDIMENSION)+i*VECTORDIMENSION;
	SourceVector1=DCTSourceVector[0]+blocks*VECTORDIMENSION;
	for(i=0;i<blocks;i++)
	  SourceVector2[i]=SourceVector1+i*DIMENSION1+blocks;
	for(i=0;i<blocks;i++)
	  SourceVector3[i]=SourceVector2[0]+i*DIMENSION2+blocks*DIMENSION1;
	SourceVector4=SourceVector3[0]+blocks*DIMENSION2;
	
	EncodeCodeIndex1=(unsigned short int *)(SourceVector4+blocks);
    EncodeCodeIndex2=EncodeCodeIndex1+blocks;
	EncodeCodeIndex3=EncodeCodeIndex2+blocks;
	EncodeCodeIndex4=EncodeCodeIndex3+blocks;
    ImageY=(unsigned char *)(EncodeCodeIndex4+blocks);
	ImageCb=ImageY+MAXIMAGESIZE;
	ImageCr=ImageCb+MAXIMAGESIZE;
	ImageYD=ImageCr+MAXIMAGESIZE;
	ImageCbD=ImageYD+MAXIMAGESIZE;
	ImageCrD=ImageCbD+MAXIMAGESIZE;
    
	GetImageYCbCrComponent(m_sFileName,ImageY,ImageCb,ImageCr,&width,&height);
	GetImageYCbCrComponent(m_sFileName,ImageYD,ImageCbD,ImageCrD,&width,&height);
    hb=height/BLOCKHEIGHT;
    wb=width/BLOCKWIDTH;
	
	sprintf(temp,"Now, The encoding testing for file [%s] begins",m_sFileName);
	MessageBox(NULL,temp,"Encoding Testing",MB_OK|MB_ICONINFORMATION);

	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Y component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=BOOKSIZEY1;
		  BOOKSIZE2=BOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Cb component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=BOOKSIZECb1;
		  BOOKSIZE2=BOOKSIZECb2;
	  }
	  if(component==0)
      {  
		  MessageBox(NULL,"Now, The codebook testing for Cr component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=BOOKSIZECr1;
		  BOOKSIZE2=BOOKSIZECr2;
	  }
	  DesignCodeVectors1=new float[BOOKSIZE0];
	  if(DesignCodeVectors1==NULL)
	  {
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  DesignCodeVectors2=new float[BOOKSIZE1][DIMENSION1];
	  if(DesignCodeVectors2==NULL)
	  {
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   delete [] DesignCodeVectors1;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  DesignCodeVectors3=new float[BOOKSIZE2][DIMENSION2];
	  if(DesignCodeVectors3==NULL)
	  {
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  DesignCodeVectors4=new float[BOOKSIZE3];
	  if(DesignCodeVectors4==NULL)
	  {
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  Code1=new float[BOOKSIZE0];
	  if(Code1==NULL)
	  {
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   delete [] DesignCodeVectors4;
	   GlobalFree(testmem);
  	   GlobalFree(hMem);
       MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  Code2=new float[BOOKSIZE1][DIMENSION1];
	  if(Code2==NULL)
	  {
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   delete [] DesignCodeVectors4;
	   delete [] Code1;
	   GlobalFree(testmem);
  	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  Code3=new float[BOOKSIZE2][DIMENSION2];
	  if(Code3==NULL)
	  {
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   delete [] DesignCodeVectors4;
	   delete [] Code1;
	   delete [] Code2;
	   GlobalFree(testmem);
  	   GlobalFree(hMem);
       MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  Code4=new float[BOOKSIZE3];
	  if(Code4==NULL)
	  {
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   delete [] DesignCodeVectors4;
	   delete [] Code1;
	   delete [] Code2;
	   delete [] Code3;
	   GlobalFree(testmem);
  	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  BeginWaitCursor();
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComY.bk";
      else if(component==1)
	    temp1+="\\ComCb.bk";
      else
	    temp1+="\\ComCr.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
		testmem=NULL;
		GlobalFree(testmem);
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		GlobalFree(testmem);
	    GlobalFree(hMem);
		delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
	    return;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=4||bfh.CodeBookSize[0]!=BOOKSIZE0||bfh.CodeBookSize[1]!=BOOKSIZE1||bfh.CodeBookSize[2]!=BOOKSIZE2||bfh.CodeBookSize[3]!=BOOKSIZE3||bfh.CodewordBytes[0]!=4||bfh.CodewordBytes[1]!=4||bfh.CodewordBytes[2]!=4||bfh.CodewordBytes[3]!=4||bfh.ImageBlockWidth!=8||bfh.ImageBlockHeight!=8||bfh.CodewordDimension[0]!=1||bfh.CodewordDimension[1]!=DIMENSION1||bfh.CodewordDimension[2]!=DIMENSION2||bfh.CodewordDimension[3]!=1)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
	    return;
	  }
	  _lseek(fh,100,SEEK_SET);
      if(_read(fh,DesignCodeVectors1,(unsigned long int)BOOKSIZE0*sizeof(float))!=(int)((unsigned long int)BOOKSIZE0*sizeof(float)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
	    return;
	  }
	  if(_read(fh,&DesignCodeVectors2[0][0],DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float))!=(int)(DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] DesignCodeVectors3;
	   delete [] DesignCodeVectors4;
	   delete [] Code1;
	   delete [] Code2;
	   delete [] Code3;
       delete [] Code4;
	   GlobalFree(testmem);
		GlobalFree(hMem);
        return;
	  }
	  if(_read(fh,&DesignCodeVectors3[0][0],DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float))!=(int)(DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
	    return;
	  }
	  if(_read(fh,DesignCodeVectors4,(unsigned long int)BOOKSIZE3*sizeof(float))!=(int)((unsigned long int)BOOKSIZE3*sizeof(float)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
	    GlobalFree(testmem);
		GlobalFree(hMem);
        return;
	  }
	  //close the file 
      _close(fh);
	  linebytes=(width+3)/4*4;
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<BLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<BLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*BLOCKWIDTH]=ImageY[i+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*linebytes];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*BLOCKWIDTH]=ImageCb[i+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*linebytes];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*BLOCKWIDTH]=ImageCr[i+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*linebytes];
			} 
		  }
		}
	  }
	  
	  //Encode Start
      memcpy(Code1,DesignCodeVectors1,sizeof(float)*BOOKSIZE0);
	  memcpy(&Code2[0][0],&DesignCodeVectors2[0][0],sizeof(float)*BOOKSIZE1*DIMENSION1);
	  memcpy(&Code3[0][0],&DesignCodeVectors3[0][0],sizeof(float)*BOOKSIZE2*DIMENSION2);
	  memcpy(Code4,DesignCodeVectors4,sizeof(float)*BOOKSIZE3);
	  for(i=0;i<BLOCKHEIGHT;i++)
	  { 
		INBLOCK1[i]=INBLOCK[i];
		OUTDCT1[i]=OUTDCT[i];
	  } 
	  for(i=0;i<blocks;i++)
	  {
	    for(k=0;k<BLOCKHEIGHT;k++)
		{
	      for(j=0;j<BLOCKWIDTH;j++)
	      INBLOCK1[k][j]=SourceVector[i][k*BLOCKWIDTH+j];
		}
	    MyRetrieveMethod.DCT(INBLOCK1,OUTDCT1,BLOCKHEIGHT,BLOCKWIDTH);
	    MyRetrieveMethod.DCT2To1Or1To2(OUTDCT1,DCT1D,BLOCKHEIGHT,BLOCKWIDTH,0);
	    for(k=0;k<VECTORDIMENSION;k++)
		  DCTSourceVector[i][k]=(float)DCT1D[k];
        SourceVector1[i]=(float)DCT1D[0];
		for(k=POSITION1;k<POSITION2;k++)
		  SourceVector2[i][k-POSITION1]=(float)DCT1D[k];
		for(k=POSITION2;k<POSITION2+DIMENSION2;k++)
		 SourceVector3[i][k-POSITION2]=(float)DCT1D[k];
        c=0.0;
		for(k=POSITION2+DIMENSION2;k<VECTORDIMENSION;k++)
          c+=DCT1D[k]*DCT1D[k];
		SourceVector4[i]=(float)sqrt(c/(double)(VECTORDIMENSION-POSITION2-DIMENSION2));
	  }
	  double ttt;
	  //encoding
	  i=MyRetrieveMethod.FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE0,SourceVector1,Code1,EncodeCodeIndex1,&ttt);
	  i=MyRetrieveMethod.FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE1,DIMENSION1,SourceVector2,Code2,EncodeCodeIndex2,&ttt);
	  i=MyRetrieveMethod.FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE2,DIMENSION2,SourceVector3,Code3,EncodeCodeIndex3,&ttt);
	  i=MyRetrieveMethod.FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE3,SourceVector4,Code4,EncodeCodeIndex4,&ttt);
	  if(i!=0)
	  {
        MessageBox(NULL,"Parameters error","Encoding",MB_ICONSTOP|MB_OK);
        GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] DesignCodeVectors3;
	    delete [] DesignCodeVectors4;
	    delete [] Code1;
	    delete [] Code2;
	    delete [] Code3;
        delete [] Code4;
        return;
	  }
      memcpy(DesignCodeVectors1,Code1,BOOKSIZE0*sizeof(float));
      memcpy(&DesignCodeVectors2[0][0],&Code2[0][0],BOOKSIZE1*DIMENSION1*sizeof(float));
      memcpy(&DesignCodeVectors3[0][0],&Code3[0][0],BOOKSIZE2*DIMENSION2*sizeof(float));
      memcpy(DesignCodeVectors4,Code4,BOOKSIZE3*sizeof(float));

	  if(component==2)
         MyRetrieveMethod.DCTVQ256GrayImageDecode(blocks,BOOKSIZE0,BOOKSIZE1,BOOKSIZE2,BLOCKWIDTH,BLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,EncodeCodeIndex3,DCTSourceVector,DesignCodeVectors1,DesignCodeVectors2,DesignCodeVectors3,ImageYD,component);
	  if(component==1)
         MyRetrieveMethod.DCTVQ256GrayImageDecode(blocks,BOOKSIZE0,BOOKSIZE1,BOOKSIZE2,BLOCKWIDTH,BLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,EncodeCodeIndex3,DCTSourceVector,DesignCodeVectors1,DesignCodeVectors2,DesignCodeVectors3,ImageCbD,component);
	  if(component==0)
         MyRetrieveMethod.DCTVQ256GrayImageDecode(blocks,BOOKSIZE0,BOOKSIZE1,BOOKSIZE2,BLOCKWIDTH,BLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,EncodeCodeIndex3,DCTSourceVector,DesignCodeVectors1,DesignCodeVectors2,DesignCodeVectors3,ImageCrD,component);
	  
	  ////Change to bmp style to display starts//////////
      LPBITMAPFILEHEADER bitfile;
      LPBITMAPINFOHEADER bitinfo;
      bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
      bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
      linebytes=(width+3)/4*4;
	  bitfile->bfSize=linebytes*height+1078;
      bitinfo->biHeight=height;
      bitinfo->biWidth=width;
	  bitinfo->biSizeImage=linebytes*height;
	  
      
	  //Copy the 256 gray bmp image header information
      memcpy(m_DisplayImageBytes[0],m_StandardBmpInfo,1078);
      memcpy(m_DisplayImageBytes[1],m_StandardBmpInfo,1078);
	  for(i=0;i<height;i++)
      {
		if(component==2)
		{
 		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageY+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageYD+(height-i-1)*linebytes,linebytes);
		}
		if(component==1)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCb+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCbD+(height-i-1)*linebytes,linebytes);
		}
		if(component==0)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCr+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCrD+(height-i-1)*linebytes,linebytes);
		}
	  }
      ////Change to bmp style to display ends//////////
	  cis.width=width;
	  cis.height=height;
	  cis.showcom=component;
	  cis.file=m_sFileName;
	  if(component==2)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
	  else if(component==1)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
	  else
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
	  cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[0];
	  cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[1];
      cis.DoModal();
	  EndWaitCursor();
   }

   MessageBox(NULL,"Now, Show the color images, original and reconstructed","Codebook Testing",MB_OK|MB_ICONINFORMATION);
   LPBITMAPFILEHEADER bitfile;
   LPBITMAPINFOHEADER bitinfo;
   bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
   bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
   linebytes=(width*24+31)/32*4;
   long int linebytes1;
   linebytes1=(width+3)/4*4;
   bitfile->bfSize=linebytes*height+54;
   bitinfo->biHeight=height;
   bitinfo->biWidth=width;
   bitinfo->biSizeImage=linebytes*height;
   memcpy(m_DisplayImageBytes[4],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[2],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[3],m_StandardBmpInfoc,54);
   int pp,qq;
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCr[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCb[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageY[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[2],width,height);
   
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCrD[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCbD[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageYD[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[3],width,height);
   cis.width=width;
   cis.height=height;
   cis.showcom=3;
   cis.file=m_sFileName;
   cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
   cis.m_psnr/=3.0;
   cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[2];
   cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[3];
   cis.DoModal();

   delete [] DesignCodeVectors1;
   delete [] DesignCodeVectors2;
   delete [] DesignCodeVectors3;
   delete [] DesignCodeVectors4;
   delete [] Code1;
   delete [] Code2;
   delete [] Code3;
   delete [] Code4;
   GlobalFree(testmem);
   GlobalFree(hMem);
}


void CVqRetrieveDoc::OnEncodingTest0(char m_sFileName[MAX_PATH])
{
    // TODO: Add your command handler code here
	long int fh;
    CImageShow cis;
	//The memory handle
	HGLOBAL hMem;
	//The temp string
    char temp[256];
    //The blocks and counters
	long int blocks;
    long int i,j,k,l;
	long int linebytes;
	unsigned long int totallen;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	unsigned char *ImageYD,*ImageCbD,*ImageCrD;
	//The width and height
	int width,height;
	//The number of blocks in width and height
	unsigned short int wb,hb;
	//The pointer for Encode image vectors
	unsigned char *SourceVector[MAXENCODEVECTORS];
	 
	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1;
	
	//The pointer array for generated codevectors by codebook design
	unsigned char (*DesignCodeVectors1)[VQDIMENSION];
	unsigned char (*Code1)[VQDIMENSION];
	unsigned char *m_DisplayImageBytes[5];
    int BOOKSIZE1;
    
	//mem for test display images
	HGLOBAL testmem=NULL;
    testmem=GlobalAlloc(GMEM_FIXED, 2*(MAXIMAGESIZE+1078)+3*(MAXIMAGESIZE*3+54));
	if(testmem==NULL) 
	{
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);		
	   return;
	}
	m_DisplayImageBytes[0]=(unsigned char *)testmem;
	m_DisplayImageBytes[1]=m_DisplayImageBytes[0]+MAXIMAGESIZE+1078;
    m_DisplayImageBytes[2]=m_DisplayImageBytes[1]+MAXIMAGESIZE+1078;
	m_DisplayImageBytes[3]=m_DisplayImageBytes[2]+MAXIMAGESIZE*3+54;
	m_DisplayImageBytes[4]=m_DisplayImageBytes[3]+MAXIMAGESIZE*3+54;
   
    blocks=GetImageBlocks(m_sFileName,VQBLOCKWIDTH,VQBLOCKHEIGHT,&totallen);
    //Apply memory
	hMem=NULL;
	fh=6*MAXIMAGESIZE  //Y Cb Cr YD CbD CrD
	// SourceVector   
	+blocks*VQDIMENSION
	+blocks*sizeof(unsigned short int); //EncodeIndex1
	hMem=GlobalAlloc(GMEM_FIXED,fh);
	if(hMem==NULL)
	{
	    sprintf(temp,"Sorry,Memory not enough%fMBytes",(double)(MAXIMAGESIZE)/1024.0/1024.0);
	    MessageBox(NULL,temp,"Encoding",MB_ICONSTOP|MB_OK);
		GlobalFree(testmem);
	    return;
	}
	//Alloc the memory
 	for(i=0;i<blocks;i++)
	  SourceVector[i]=(unsigned char *)hMem+i*VQDIMENSION;
	
	EncodeCodeIndex1=(unsigned short int *)(SourceVector[0]+blocks*VQDIMENSION);
    ImageY=(unsigned char *)(EncodeCodeIndex1+blocks);
	ImageCb=ImageY+MAXIMAGESIZE;
	ImageCr=ImageCb+MAXIMAGESIZE;
	ImageYD=ImageCr+MAXIMAGESIZE;
	ImageCbD=ImageYD+MAXIMAGESIZE;
	ImageCrD=ImageCbD+MAXIMAGESIZE;
    
	GetImageYCbCrComponent(m_sFileName,ImageY,ImageCb,ImageCr,&width,&height);
	hb=height/VQBLOCKHEIGHT;
    wb=width/VQBLOCKWIDTH;
	
	sprintf(temp,"Now, The encoding testing for file [%s] begins",m_sFileName);
	MessageBox(NULL,temp,"Encoding Testing",MB_OK|MB_ICONINFORMATION);

	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Y component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZEY;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Cb component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECb;
	  }
	  if(component==0)
      {  
		  MessageBox(NULL,"Now, The codebook testing for Cr component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECr;
	  }
	  DesignCodeVectors1=new unsigned char [BOOKSIZE1][VQDIMENSION];
	  if(DesignCodeVectors1==NULL)
	  {
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  Code1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(Code1==NULL)
	  {
	   delete [] DesignCodeVectors1;
	   GlobalFree(testmem);
  	   GlobalFree(hMem);
       MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  BeginWaitCursor();
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbVQ.bk";
      else
	    temp1+="\\ComCrVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
		testmem=NULL;
		GlobalFree(testmem);
	    delete [] DesignCodeVectors1;
	    delete [] Code1;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		GlobalFree(testmem);
	    GlobalFree(hMem);
		delete [] DesignCodeVectors1;
	    delete [] Code1;
	    return;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=1||bfh.CodeBookSize[0]!=BOOKSIZE1||bfh.CodewordBytes[0]!=4||bfh.ImageBlockWidth!=4||bfh.ImageBlockHeight!=4||bfh.CodewordDimension[0]!=VQDIMENSION)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] Code1;
	    return;
	  }
	  _lseek(fh,100,SEEK_SET);
      if(_read(fh,&DesignCodeVectors1[0][0],(unsigned long int)BOOKSIZE1*sizeof(unsigned char)*VQDIMENSION)!=(int)((unsigned long int)BOOKSIZE1*sizeof(unsigned char)*VQDIMENSION))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] Code1;
	    return;
	  }
	  //close the file 
      _close(fh);
	  linebytes=(width+3)/4*4;
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<VQBLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<VQBLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageY[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCb[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCr[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			} 
		  }
		}
	  }
	  
	  //Encode Start
      memcpy(&Code1[0][0],&DesignCodeVectors1[0][0],sizeof(unsigned char)*BOOKSIZE1*VQDIMENSION);
	  double ttt;
	  //encoding
	  i=MyRetrieveMethod.FSVQ256GrayImageEncode(blocks,BOOKSIZE1,VQDIMENSION,SourceVector,Code1,EncodeCodeIndex1,&ttt);
	  if(i!=0)
	  {
        MessageBox(NULL,"Parameters error","Encoding",MB_ICONSTOP|MB_OK);
        GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] DesignCodeVectors1;
	    delete [] Code1;
	    return;
	  }
      memcpy(&DesignCodeVectors1[0][0],&Code1[0][0],BOOKSIZE1*VQDIMENSION*sizeof(unsigned char));
      
	  if(component==2)
         MyRetrieveMethod.VQ256GrayImageDecode(blocks,BOOKSIZE1,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,DesignCodeVectors1,ImageYD,component);
	  if(component==1)
         MyRetrieveMethod.VQ256GrayImageDecode(blocks,BOOKSIZE1,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,DesignCodeVectors1,ImageCbD,component);
	  if(component==0)
         MyRetrieveMethod.VQ256GrayImageDecode(blocks,BOOKSIZE1,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,DesignCodeVectors1,ImageCrD,component);
	  
	  ////Change to bmp style to display starts//////////
      LPBITMAPFILEHEADER bitfile;
      LPBITMAPINFOHEADER bitinfo;
      bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
      bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
      linebytes=(width+3)/4*4;
	  bitfile->bfSize=linebytes*height+1078;
      bitinfo->biHeight=height;
      bitinfo->biWidth=width;
	  bitinfo->biSizeImage=linebytes*height;
	  
      
	  //Copy the 256 gray bmp image header information
      memcpy(m_DisplayImageBytes[0],m_StandardBmpInfo,1078);
      memcpy(m_DisplayImageBytes[1],m_StandardBmpInfo,1078);
	  for(i=0;i<height;i++)
      {
		if(component==2)
		{
 		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageY+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageYD+(height-i-1)*linebytes,linebytes);
		}
		if(component==1)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCb+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCbD+(height-i-1)*linebytes,linebytes);
		}
		if(component==0)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCr+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCrD+(height-i-1)*linebytes,linebytes);
		}
	  }
      ////Change to bmp style to display ends//////////
	  cis.width=width;
	  cis.height=height;
	  cis.showcom=component;
	  cis.file=m_sFileName;
	  if(component==2)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
	  else if(component==1)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
	  else
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
	  cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[0];
	  cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[1];
      cis.DoModal();
	  EndWaitCursor();
   }

   MessageBox(NULL,"Now, Show the color images, original and reconstructed","Codebook Testing",MB_OK|MB_ICONINFORMATION);
   LPBITMAPFILEHEADER bitfile;
   LPBITMAPINFOHEADER bitinfo;
   bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
   bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
   linebytes=(width*24+31)/32*4;
   long int linebytes1;
   linebytes1=(width+3)/4*4;
   bitfile->bfSize=linebytes*height+54;
   bitinfo->biHeight=height;
   bitinfo->biWidth=width;
   bitinfo->biSizeImage=linebytes*height;
   memcpy(m_DisplayImageBytes[4],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[2],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[3],m_StandardBmpInfoc,54);
   int pp,qq;
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCr[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCb[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageY[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[2],width,height);
   
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCrD[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCbD[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageYD[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[3],width,height);
   cis.width=width;
   cis.height=height;
   cis.showcom=3;
   cis.file=m_sFileName;
   cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
   cis.m_psnr/=3.0;
   cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[2];
   cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[3];
   cis.DoModal();

   delete [] DesignCodeVectors1;
   delete [] Code1;
   GlobalFree(testmem);
   GlobalFree(hMem);
}

void CVqRetrieveDoc::OnEncodingTest1(char m_sFileName[MAX_PATH])
{
    // TODO: Add your command handler code here
	long int fh;
    CImageShow cis;
	//The memory handle
	HGLOBAL hMem;
	//The temp string
    char temp[256];
    //The blocks and counters
	long int blocks;
    long int i,j,k,l;
	long int linebytes;
	unsigned long int totallen;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	unsigned char *ImageYD,*ImageCbD,*ImageCrD;
	//The width and height
	int width,height;
	//The number of blocks in width and height
	unsigned short int wb,hb;
	//The pointer for Encode image vectors
	

	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1,*EncodeCodeIndex2;
	unsigned char *m_DisplayImageBytes[5];
	
	//The pointer array for generated codevectors by codebook design
	int BOOKSIZE1, BOOKSIZE2;
    
	
	//mem for test display images
	HGLOBAL testmem=NULL;
    testmem=GlobalAlloc(GMEM_FIXED, 2*(MAXIMAGESIZE+1078)+3*(MAXIMAGESIZE*3+54));
	if(testmem==NULL) 
	{
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);		
	   return;
	}
	m_DisplayImageBytes[0]=(unsigned char *)testmem;
	m_DisplayImageBytes[1]=m_DisplayImageBytes[0]+MAXIMAGESIZE+1078;
    m_DisplayImageBytes[2]=m_DisplayImageBytes[1]+MAXIMAGESIZE+1078;
	m_DisplayImageBytes[3]=m_DisplayImageBytes[2]+MAXIMAGESIZE*3+54;
	m_DisplayImageBytes[4]=m_DisplayImageBytes[3]+MAXIMAGESIZE*3+54;
   
    blocks=GetImageBlocks(m_sFileName,VQBLOCKWIDTH,VQBLOCKHEIGHT,&totallen);
    unsigned char (*SourceVector)[VQDIMENSION];
	SourceVector=new unsigned char[blocks][VQDIMENSION];
	if(SourceVector==NULL)
	{
	  GlobalFree(testmem);
	  MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	  return;
	}
	short int (*SourceVector1)[VQDIMENSION];  //for error vector quantization
	SourceVector1=new short int[blocks][VQDIMENSION];
	if(SourceVector1==NULL)
	{
	  delete [] SourceVector;
	  GlobalFree(testmem);
	  MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	  return;
	}

    //Apply memory
	hMem=NULL;
	fh=6*MAXIMAGESIZE  //Y Cb Cr YD CbD CrD
	+2*blocks*sizeof(unsigned short int); //EncodeIndex1/2
	hMem=GlobalAlloc(GMEM_FIXED,fh);
	if(hMem==NULL)
	{
	    sprintf(temp,"Sorry,Memory not enough%fMBytes",(double)(MAXIMAGESIZE)/1024.0/1024.0);
	    MessageBox(NULL,temp,"Encoding",MB_ICONSTOP|MB_OK);
		GlobalFree(testmem);
		delete [] SourceVector;
	    delete [] SourceVector1;
	    return;
	}
	//Alloc the memory
 	EncodeCodeIndex1=(unsigned short int *)hMem;
    EncodeCodeIndex2=EncodeCodeIndex1+blocks;
	ImageY=(unsigned char *)(EncodeCodeIndex2+blocks);
	ImageCb=ImageY+MAXIMAGESIZE;
	ImageCr=ImageCb+MAXIMAGESIZE;
	ImageYD=ImageCr+MAXIMAGESIZE;
	ImageCbD=ImageYD+MAXIMAGESIZE;
	ImageCrD=ImageCbD+MAXIMAGESIZE;
    
	GetImageYCbCrComponent(m_sFileName,ImageY,ImageCb,ImageCr,&width,&height);
	
    hb=height/VQBLOCKHEIGHT;
    wb=width/VQBLOCKWIDTH;
	
	sprintf(temp,"Now, The encoding testing for file [%s] begins",m_sFileName);
	MessageBox(NULL,temp,"Encoding Testing",MB_OK|MB_ICONINFORMATION);

	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Y component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZEY1;
		  BOOKSIZE2=VQBOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Cb component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECb1;
		  BOOKSIZE2=VQBOOKSIZECb2;
	  }
	  if(component==0)
      {  
		  MessageBox(NULL,"Now, The codebook testing for Cr component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECr1;
		  BOOKSIZE2=VQBOOKSIZECr2;
	  }
	  //The pointer array for generated codevectors by codebook design
	  unsigned char (*DesignCodeVectors1)[VQDIMENSION];
	  DesignCodeVectors1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(DesignCodeVectors1==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector1;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  short int (*DesignCodeVectors2)[VQDIMENSION];
	  DesignCodeVectors2=new short int[BOOKSIZE2][VQDIMENSION];
	  if(DesignCodeVectors2==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector1;
	   delete [] DesignCodeVectors1;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }	 
	  unsigned char (*Code1)[VQDIMENSION];
	  Code1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(Code1==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector1;
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  short int (*Code2)[VQDIMENSION];
	  Code2=new short int[BOOKSIZE2][VQDIMENSION];
	  if(Code2==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector1;
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] Code1;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }	 
	  BeginWaitCursor();
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYMSVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbMSVQ.bk";
      else
	    temp1+="\\ComCrMSVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
		testmem=NULL;
		GlobalFree(testmem);
	    delete [] SourceVector;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		GlobalFree(testmem);
	    GlobalFree(hMem);
        delete [] SourceVector;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=2||bfh.CodeBookSize[0]!=BOOKSIZE1||bfh.CodeBookSize[1]!=BOOKSIZE2||bfh.CodewordBytes[0]!=1||bfh.CodewordBytes[1]!=2||bfh.ImageBlockWidth!=4||bfh.ImageBlockHeight!=4||bfh.CodewordDimension[0]!=VQDIMENSION||bfh.CodewordDimension[1]!=VQDIMENSION)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] SourceVector;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
	  _lseek(fh,100,SEEK_SET);
      if(_read(fh,&DesignCodeVectors1[0][0],(unsigned long int)BOOKSIZE1*VQDIMENSION*sizeof(unsigned char))!=(int)((unsigned long int)BOOKSIZE1*VQDIMENSION*sizeof(unsigned char)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] SourceVector;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
	  if(_read(fh,&DesignCodeVectors2[0][0],(unsigned long int)BOOKSIZE2*VQDIMENSION*sizeof(short int))!=(int)((unsigned long int)BOOKSIZE2*VQDIMENSION*sizeof(short int)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		delete [] SourceVector;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    GlobalFree(testmem);
		GlobalFree(hMem);
        return;
	  }
	  //close the file 
      _close(fh);
	  linebytes=(width+3)/4*4;
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<VQBLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<VQBLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageY[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCb[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCr[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			} 
		  }
		}
	  }
	  
	  //Encode Start
      memcpy(&Code1[0][0],&DesignCodeVectors1[0][0],sizeof(unsigned char)*BOOKSIZE1*VQDIMENSION);
	  memcpy(&Code2[0][0],&DesignCodeVectors2[0][0],sizeof(short int)*BOOKSIZE2*VQDIMENSION);
      //encoding
	  i=MyRetrieveMethod.TwoStageVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector1,Code1,Code2,EncodeCodeIndex1,EncodeCodeIndex2);
	  if(i!=0)
	  {
        MessageBox(NULL,"Parameters error","Encoding",MB_ICONSTOP|MB_OK);
        GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] SourceVector;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
      memcpy(&DesignCodeVectors1[0][0],&Code1[0][0],BOOKSIZE1*VQDIMENSION*sizeof(unsigned char));
      memcpy(&DesignCodeVectors2[0][0],&Code2[0][0],BOOKSIZE2*VQDIMENSION*sizeof(short int));
            
	  if(component==2)
         MyRetrieveMethod.TwoStageVQ256GrayImageDecode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,DesignCodeVectors1,DesignCodeVectors2,ImageYD,component);
	  if(component==1)
         MyRetrieveMethod.TwoStageVQ256GrayImageDecode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,DesignCodeVectors1,DesignCodeVectors2,ImageCbD,component);
	  if(component==0)
         MyRetrieveMethod.TwoStageVQ256GrayImageDecode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,DesignCodeVectors1,DesignCodeVectors2,ImageCrD,component);
	  
	  ////Change to bmp style to display starts//////////
      LPBITMAPFILEHEADER bitfile;
      LPBITMAPINFOHEADER bitinfo;
      bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
      bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
      linebytes=(width+3)/4*4;
	  bitfile->bfSize=linebytes*height+1078;
      bitinfo->biHeight=height;
      bitinfo->biWidth=width;
	  bitinfo->biSizeImage=linebytes*height;
	  
      
	  //Copy the 256 gray bmp image header information
      memcpy(m_DisplayImageBytes[0],m_StandardBmpInfo,1078);
      memcpy(m_DisplayImageBytes[1],m_StandardBmpInfo,1078);
	  for(i=0;i<height;i++)
      {
		if(component==2)
		{
 		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageY+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageYD+(height-i-1)*linebytes,linebytes);
		}
		if(component==1)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCb+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCbD+(height-i-1)*linebytes,linebytes);
		}
		if(component==0)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCr+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCrD+(height-i-1)*linebytes,linebytes);
		}
	  }
      ////Change to bmp style to display ends//////////
	  cis.width=width;
	  cis.height=height;
	  cis.showcom=component;
	  cis.file=m_sFileName;
	  if(component==2)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
	  else if(component==1)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
	  else
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
	  cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[0];
	  cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[1];
      cis.DoModal();
	  EndWaitCursor();
	  delete [] DesignCodeVectors1;
      delete [] DesignCodeVectors2;
      delete [] Code1;
      delete [] Code2;
   }

   MessageBox(NULL,"Now, Show the color images, original and reconstructed","Codebook Testing",MB_OK|MB_ICONINFORMATION);
   LPBITMAPFILEHEADER bitfile;
   LPBITMAPINFOHEADER bitinfo;
   bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
   bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
   linebytes=(width*24+31)/32*4;
   long int linebytes1;
   linebytes1=(width+3)/4*4;
   bitfile->bfSize=linebytes*height+54;
   bitinfo->biHeight=height;
   bitinfo->biWidth=width;
   bitinfo->biSizeImage=linebytes*height;
   memcpy(m_DisplayImageBytes[4],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[2],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[3],m_StandardBmpInfoc,54);
   int pp,qq;
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCr[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCb[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageY[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[2],width,height);
   
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCrD[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCbD[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageYD[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[3],width,height);
   cis.width=width;
   cis.height=height;
   cis.showcom=3;
   cis.file=m_sFileName;
   cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
   cis.m_psnr/=3.0;
   cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[2];
   cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[3];
   cis.DoModal();

   delete [] SourceVector;
   delete [] SourceVector1;
   GlobalFree(testmem);
   GlobalFree(hMem);
}

void CVqRetrieveDoc::OnEncodingTest2(char m_sFileName[MAX_PATH])
{
    // TODO: Add your command handler code here
// TODO: Add your command handler code here
	long int fh;
    CImageShow cis;
	//The memory handle
	HGLOBAL hMem;
	//The temp string
    char temp[256];
    //The blocks and counters
	long int blocks;
    long int i,j,k,l;
	long int linebytes;
	unsigned long int totallen;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	unsigned char *ImageYD,*ImageCbD,*ImageCrD;
	//The width and height
	int width,height;
	//The number of blocks in width and height
	unsigned short int wb,hb;
	//The pointer for Encode image vectors
	

	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1,*EncodeCodeIndex2;
	unsigned char *m_DisplayImageBytes[5];
	
	//The pointer array for generated codevectors by codebook design
	int BOOKSIZE1, BOOKSIZE2;
    
	
	//mem for test display images
	HGLOBAL testmem=NULL;
    testmem=GlobalAlloc(GMEM_FIXED, 2*(MAXIMAGESIZE+1078)+3*(MAXIMAGESIZE*3+54));
	if(testmem==NULL) 
	{
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Testing",MB_ICONSTOP|MB_OK);		
	   return;
	}
	m_DisplayImageBytes[0]=(unsigned char *)testmem;
	m_DisplayImageBytes[1]=m_DisplayImageBytes[0]+MAXIMAGESIZE+1078;
    m_DisplayImageBytes[2]=m_DisplayImageBytes[1]+MAXIMAGESIZE+1078;
	m_DisplayImageBytes[3]=m_DisplayImageBytes[2]+MAXIMAGESIZE*3+54;
	m_DisplayImageBytes[4]=m_DisplayImageBytes[3]+MAXIMAGESIZE*3+54;
   
    blocks=GetImageBlocks(m_sFileName,VQBLOCKWIDTH,VQBLOCKHEIGHT,&totallen);
    unsigned char (*SourceVector)[VQDIMENSION];
	SourceVector=new unsigned char[blocks][VQDIMENSION];
	if(SourceVector==NULL)
	{
	  GlobalFree(testmem);
	  MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	  return;
	}
	unsigned char *SourceVector0;  //for error vector quantization
	SourceVector0=new unsigned char[blocks];
	if(SourceVector0==NULL)
	{
	  delete [] SourceVector;
	  GlobalFree(testmem);
	  MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	  return;
	}
    
	short int (*SourceVector1)[VQDIMENSION];  //for error vector quantization
	SourceVector1=new short int[blocks][VQDIMENSION];
	if(SourceVector1==NULL)
	{
	  delete [] SourceVector;
	  delete [] SourceVector0;
	  GlobalFree(testmem);
	  MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	  return;
	}

    //Apply memory
	hMem=NULL;
	fh=6*MAXIMAGESIZE  //Y Cb Cr YD CbD CrD
	+2*blocks*sizeof(unsigned short int); //EncodeIndex1/2
	hMem=GlobalAlloc(GMEM_FIXED,fh);
	if(hMem==NULL)
	{
	    sprintf(temp,"Sorry,Memory not enough%fMBytes",(double)(MAXIMAGESIZE)/1024.0/1024.0);
	    MessageBox(NULL,temp,"Encoding",MB_ICONSTOP|MB_OK);
		GlobalFree(testmem);
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    return;
	}
	//Alloc the memory
 	EncodeCodeIndex1=(unsigned short int *)hMem;
    EncodeCodeIndex2=EncodeCodeIndex1+blocks;
	ImageY=(unsigned char *)(EncodeCodeIndex2+blocks);
	ImageCb=ImageY+MAXIMAGESIZE;
	ImageCr=ImageCb+MAXIMAGESIZE;
	ImageYD=ImageCr+MAXIMAGESIZE;
	ImageCbD=ImageYD+MAXIMAGESIZE;
	ImageCrD=ImageCbD+MAXIMAGESIZE;
    
	GetImageYCbCrComponent(m_sFileName,ImageY,ImageCb,ImageCr,&width,&height);
	
    hb=height/VQBLOCKHEIGHT;
    wb=width/VQBLOCKWIDTH;
	
	sprintf(temp,"Now, The encoding testing for file [%s] begins",m_sFileName);
	MessageBox(NULL,temp,"Encoding Testing",MB_OK|MB_ICONINFORMATION);

	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Y component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZEYM;
		  BOOKSIZE2=VQBOOKSIZEYR;
	  }
	  if(component==1)
	  {
		  MessageBox(NULL,"Now, The codebook testing for Cb component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECbM;
		  BOOKSIZE2=VQBOOKSIZECbR;
	  }
	  if(component==0)
      {  
		  MessageBox(NULL,"Now, The codebook testing for Cr component begins","Codebook Testing",MB_OK|MB_ICONINFORMATION);
		  BOOKSIZE1=VQBOOKSIZECrM;
		  BOOKSIZE2=VQBOOKSIZECrR;
	  }
	  //The pointer array for generated codevectors by codebook design
	  unsigned char (*DesignCodeVectors1)[VQDIMENSION];
	  DesignCodeVectors1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(DesignCodeVectors1==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector0;
	   delete [] SourceVector1;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  short int (*DesignCodeVectors2)[VQDIMENSION];
	  DesignCodeVectors2=new short int[BOOKSIZE2][VQDIMENSION];
	  if(DesignCodeVectors2==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector0;
	   delete [] SourceVector1;
	   delete [] DesignCodeVectors1;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }	 
	  unsigned char (*Code1)[VQDIMENSION];
	  Code1=new unsigned char[BOOKSIZE1][VQDIMENSION];
	  if(Code1==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector0;
	   delete [] SourceVector1;
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }
	  short int (*Code2)[VQDIMENSION];
	  Code2=new short int[BOOKSIZE2][VQDIMENSION];
	  if(Code2==NULL)
	  {
	   delete [] SourceVector;
	   delete [] SourceVector0;
	   delete [] SourceVector1;
	   delete [] DesignCodeVectors1;
	   delete [] DesignCodeVectors2;
	   delete [] Code1;
	   GlobalFree(testmem);
	   GlobalFree(hMem);
	   MessageBox(NULL,"Sorry, memory not enough","Codebook Design",MB_ICONSTOP|MB_OK);
	   return;
	  }	 
	  BeginWaitCursor();
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYMRVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbMRVQ.bk";
      else
	    temp1+="\\ComCrMRVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    GlobalFree(hMem);
		testmem=NULL;
		GlobalFree(testmem);
	    delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		GlobalFree(testmem);
	    GlobalFree(hMem);
        delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=2||bfh.CodeBookSize[0]!=BOOKSIZE1||bfh.CodeBookSize[1]!=BOOKSIZE2||bfh.CodewordBytes[0]!=1||bfh.CodewordBytes[1]!=2||bfh.ImageBlockWidth!=4||bfh.ImageBlockHeight!=4||bfh.CodewordDimension[0]!=VQDIMENSION||bfh.CodewordDimension[1]!=VQDIMENSION)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
	  _lseek(fh,100,SEEK_SET);
      if(_read(fh,&DesignCodeVectors1[0][0],(unsigned long int)BOOKSIZE1*VQDIMENSION*sizeof(unsigned char))!=(int)((unsigned long int)BOOKSIZE1*VQDIMENSION*sizeof(unsigned char)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    testmem=NULL;
		GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
	  if(_read(fh,&DesignCodeVectors2[0][0],(unsigned long int)BOOKSIZE2*VQDIMENSION*sizeof(short int))!=(int)((unsigned long int)BOOKSIZE2*VQDIMENSION*sizeof(short int)))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    GlobalFree(testmem);
		GlobalFree(hMem);
        return;
	  }
	  //close the file 
      _close(fh);
	  linebytes=(width+3)/4*4;
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<VQBLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<VQBLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageY[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCb[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCr[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*linebytes];
			} 
		  }
		}
	  }
	  
	  //Encode Start
      memcpy(&Code1[0][0],&DesignCodeVectors1[0][0],sizeof(unsigned char)*BOOKSIZE1*VQDIMENSION);
	  memcpy(&Code2[0][0],&DesignCodeVectors2[0][0],sizeof(short int)*BOOKSIZE2*VQDIMENSION);
      //encoding
	  i=MyRetrieveMethod.MeanRemovedVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector0,SourceVector1,Code1,Code2,EncodeCodeIndex1,EncodeCodeIndex2);
	  if(i!=0)
	  {
        MessageBox(NULL,"Parameters error","Encoding",MB_ICONSTOP|MB_OK);
        GlobalFree(hMem);
		GlobalFree(testmem);
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    delete [] DesignCodeVectors1;
	    delete [] DesignCodeVectors2;
	    delete [] Code1;
		delete [] Code2;
	    return;
	  }
      memcpy(&DesignCodeVectors1[0][0],&Code1[0][0],BOOKSIZE1*VQDIMENSION*sizeof(unsigned char));
      memcpy(&DesignCodeVectors2[0][0],&Code2[0][0],BOOKSIZE2*VQDIMENSION*sizeof(short int));
            
	  if(component==2)
         MyRetrieveMethod.MeanRemovedVQ256GrayImageDecode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,DesignCodeVectors1,DesignCodeVectors2,ImageYD,component);
	  if(component==1)
         MyRetrieveMethod.MeanRemovedVQ256GrayImageDecode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,DesignCodeVectors1,DesignCodeVectors2,ImageCbD,component);
	  if(component==0)
         MyRetrieveMethod.MeanRemovedVQ256GrayImageDecode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,width,EncodeCodeIndex1,EncodeCodeIndex2,DesignCodeVectors1,DesignCodeVectors2,ImageCrD,component);
	  
	  ////Change to bmp style to display starts//////////
      LPBITMAPFILEHEADER bitfile;
      LPBITMAPINFOHEADER bitinfo;
      bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
      bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
      linebytes=(width+3)/4*4;
	  bitfile->bfSize=linebytes*height+1078;
      bitinfo->biHeight=height;
      bitinfo->biWidth=width;
	  bitinfo->biSizeImage=linebytes*height;
	  
      
	  //Copy the 256 gray bmp image header information
      memcpy(m_DisplayImageBytes[0],m_StandardBmpInfo,1078);
      memcpy(m_DisplayImageBytes[1],m_StandardBmpInfo,1078);
	  for(i=0;i<height;i++)
      {
		if(component==2)
		{
 		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageY+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageYD+(height-i-1)*linebytes,linebytes);
		}
		if(component==1)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCb+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCbD+(height-i-1)*linebytes,linebytes);
		}
		if(component==0)
		{
		  memcpy(m_DisplayImageBytes[0]+1078+i*linebytes,ImageCr+(height-i-1)*linebytes,linebytes);
		  memcpy(m_DisplayImageBytes[1]+1078+i*linebytes,ImageCrD+(height-i-1)*linebytes,linebytes);
		}
	  }
      ////Change to bmp style to display ends//////////
	  cis.width=width;
	  cis.height=height;
	  cis.showcom=component;
	  cis.file=m_sFileName;
	  if(component==2)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
	  else if(component==1)
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
	  else
	    cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
	  cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[0];
	  cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[1];
      cis.DoModal();
	  EndWaitCursor();
	  delete [] DesignCodeVectors1;
      delete [] DesignCodeVectors2;
      delete [] Code1;
      delete [] Code2;
   }

   MessageBox(NULL,"Now, Show the color images, original and reconstructed","Codebook Testing",MB_OK|MB_ICONINFORMATION);
   LPBITMAPFILEHEADER bitfile;
   LPBITMAPINFOHEADER bitinfo;
   bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
   bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
   linebytes=(width*24+31)/32*4;
   long int linebytes1;
   linebytes1=(width+3)/4*4;
   bitfile->bfSize=linebytes*height+54;
   bitinfo->biHeight=height;
   bitinfo->biWidth=width;
   bitinfo->biSizeImage=linebytes*height;
   memcpy(m_DisplayImageBytes[4],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[2],m_StandardBmpInfoc,54);
   memcpy(m_DisplayImageBytes[3],m_StandardBmpInfoc,54);
   int pp,qq;
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCr[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCb[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageY[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[2],width,height);
   
   for(i=0;i<height;i++)
   {
 	 for(j=0;j<width;j++)
	 {
	     pp=3*j+i*linebytes;
	     qq=(height-i-1)*linebytes1+j;
	     m_DisplayImageBytes[4][54+pp]=ImageCrD[qq];
	     m_DisplayImageBytes[4][54+pp+1]=ImageCbD[qq];
	     m_DisplayImageBytes[4][54+pp+2]=ImageYD[qq];
	 }
   }
   MyRetrieveMethod.YCbCr2rgb_other(m_DisplayImageBytes[4],m_DisplayImageBytes[3],width,height);
   cis.width=width;
   cis.height=height;
   cis.showcom=3;
   cis.file=m_sFileName;
   cis.m_psnr=(float)MyRetrieveMethod.ComputePSNR(ImageY,ImageYD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCb,ImageCbD,width,height);
   cis.m_psnr+=(float)MyRetrieveMethod.ComputePSNR(ImageCr,ImageCrD,width,height);
   cis.m_psnr/=3.0;
   cis.m_DisplayImageBytes[0]=m_DisplayImageBytes[2];
   cis.m_DisplayImageBytes[1]=m_DisplayImageBytes[3];
   cis.DoModal();

   delete [] SourceVector;
   delete [] SourceVector0;
   delete [] SourceVector1;
   GlobalFree(testmem);
   GlobalFree(hMem);
}


int CVqRetrieveDoc::OpenCodeBooks()
{
    // TODO: Add your command handler code here
	long int fh;
    //The temp string
	int component;
    char temp[256];
	//The pointer array for generated codevectors by codebook design
	int BOOKSIZE1, BOOKSIZE2;
    
	//Apply memory
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=BOOKSIZEY1;
		  BOOKSIZE2=BOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=BOOKSIZECb1;
		  BOOKSIZE2=BOOKSIZECb2;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=BOOKSIZECr1;
		  BOOKSIZE2=BOOKSIZECr2;
	  }
	  
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComY.bk";
      else if(component==1)
	    temp1+="\\ComCb.bk";
      else
	    temp1+="\\ComCr.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    return -1;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		return -2;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=4||bfh.CodeBookSize[0]!=BOOKSIZE0||bfh.CodeBookSize[1]!=BOOKSIZE1||bfh.CodeBookSize[2]!=BOOKSIZE2||bfh.CodeBookSize[3]!=BOOKSIZE3||bfh.CodewordBytes[0]!=4||bfh.CodewordBytes[1]!=4||bfh.CodewordBytes[2]!=4||bfh.CodewordBytes[3]!=4||bfh.ImageBlockWidth!=8||bfh.ImageBlockHeight!=8||bfh.CodewordDimension[0]!=1||bfh.CodewordDimension[1]!=DIMENSION1||bfh.CodewordDimension[2]!=DIMENSION2||bfh.CodewordDimension[3]!=1)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    return -2;
	  }
	  _lseek(fh,100,SEEK_SET);
	  if(component==2)
	  {
        if(_read(fh,CodeBookY1,(unsigned long int)BOOKSIZE0*sizeof(float))!=(int)((unsigned long int)BOOKSIZE0*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	    if(_read(fh,&CodeBookY2[0][0],DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float))!=(int)(DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&CodeBookY3[0][0],DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float))!=(int)(DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	    if(_read(fh,CodeBookY4,(unsigned long int)BOOKSIZE3*sizeof(float))!=(int)((unsigned long int)BOOKSIZE3*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==1)
	  {
        if(_read(fh,CodeBookCb1,(unsigned long int)BOOKSIZE0*sizeof(float))!=(int)((unsigned long int)BOOKSIZE0*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	    if(_read(fh,&CodeBookCb2[0][0],DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float))!=(int)(DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
        if(_read(fh,&CodeBookCb3[0][0],DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float))!=(int)(DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	    if(_read(fh,CodeBookCb4,(unsigned long int)BOOKSIZE3*sizeof(float))!=(int)((unsigned long int)BOOKSIZE3*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==0)
	  {
        if(_read(fh,CodeBookCr1,(unsigned long int)BOOKSIZE0*sizeof(float))!=(int)((unsigned long int)BOOKSIZE0*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
        if(_read(fh,&CodeBookCr2[0][0],DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float))!=(int)(DIMENSION1*(unsigned long int)BOOKSIZE1*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	    if(_read(fh,&CodeBookCr3[0][0],DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float))!=(int)(DIMENSION2*(unsigned long int)BOOKSIZE2*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	    if(_read(fh,CodeBookCr4,(unsigned long int)BOOKSIZE3*sizeof(float))!=(int)((unsigned long int)BOOKSIZE3*sizeof(float)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  //close the file 
      _close(fh);
	}
    return 0;
}

int CVqRetrieveDoc::OpenCodeBooks0()
{
    // TODO: Add your command handler code here
	long int fh;
    //The temp string
	int component;
    char temp[256];
	//The pointer array for generated codevectors by codebook design
	int BOOKSIZE1;
    
	//Apply memory
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=VQBOOKSIZEY;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=VQBOOKSIZECb;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=VQBOOKSIZECr;
	  }
	  
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbVQ.bk";
      else
	    temp1+="\\ComCrVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    return -1;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		return -2;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=1||bfh.CodeBookSize[0]!=BOOKSIZE1||bfh.CodewordBytes[0]!=4||bfh.ImageBlockWidth!=4||bfh.ImageBlockHeight!=4||bfh.CodewordDimension[0]!=VQDIMENSION)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    return -2;
	  }
	  _lseek(fh,100,SEEK_SET);
	  if(component==2)
	  {
        if(_read(fh,&VQCodeBookY[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==1)
	  {
        if(_read(fh,&VQCodeBookCb[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==0)
	  {
        if(_read(fh,&VQCodeBookCr[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  //close the file 
      _close(fh);
	}
    return 0;
}

int CVqRetrieveDoc::OpenCodeBooks1()
{
    // TODO: Add your command handler code here
	long int fh;
    //The temp string
	int component;
    char temp[256];
	//The pointer array for generated codevectors by codebook design
	int BOOKSIZE1, BOOKSIZE2;
    
	//Apply memory
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=VQBOOKSIZEY1;
		  BOOKSIZE2=VQBOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=VQBOOKSIZECb1;
		  BOOKSIZE2=VQBOOKSIZECb2;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=VQBOOKSIZECr1;
		  BOOKSIZE2=VQBOOKSIZECr2;
	  }
	  
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYMSVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbMSVQ.bk";
      else
	    temp1+="\\ComCrMSVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    return -1;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		return -2;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=2||bfh.CodeBookSize[0]!=BOOKSIZE1||bfh.CodeBookSize[1]!=BOOKSIZE2||bfh.CodewordBytes[0]!=1||bfh.CodewordBytes[1]!=2||bfh.ImageBlockWidth!=4||bfh.ImageBlockHeight!=4||bfh.CodewordDimension[0]!=VQDIMENSION||bfh.CodewordDimension[1]!=VQDIMENSION)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    return -2;
	  }
	  _lseek(fh,100,SEEK_SET);
	  if(component==2)
	  {
        if(_read(fh,&VQCodeBookY1[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&VQCodeBookY2[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==1)
	  {
        if(_read(fh,&VQCodeBookCb1[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&VQCodeBookCb2[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==0)
	  {
        if(_read(fh,&VQCodeBookCr1[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&VQCodeBookCr2[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  //close the file 
      _close(fh);
	}
    return 0;
}

int CVqRetrieveDoc::OpenCodeBooks2()
{
    // TODO: Add your command handler code here
	long int fh;
    //The temp string
	int component;
    char temp[256];
	//The pointer array for generated codevectors by codebook design
	int BOOKSIZE1, BOOKSIZE2;
    
	//Apply memory
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=VQBOOKSIZEYM;
		  BOOKSIZE2=VQBOOKSIZEYR;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=VQBOOKSIZECbM;
		  BOOKSIZE2=VQBOOKSIZECbR;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=VQBOOKSIZECrM;
		  BOOKSIZE2=VQBOOKSIZECrR;
	  }
	  
	  /////////////////Read the codebook begins///////////
      //Open the file in WriteOnly Mode
	  CString temp1;
	  temp1=m_CurrentDirectory;
	  if(component==2)
	    temp1+="\\ComYMRVQ.bk";
      else if(component==1)
	    temp1+="\\ComCbMRVQ.bk";
      else
	    temp1+="\\ComCrMRVQ.bk";
      fh=_open(temp1,_O_BINARY|_O_RDONLY,_S_IREAD|_S_IWRITE);
      //If the file cannot be opened or created,return directly
      if(fh==-1)
	  {
	    sprintf(temp,"Sorry! Cannot open File[%s]",temp1);
	    MessageBox(NULL,temp,"Codebook Read",MB_ICONSTOP|MB_OK);
	    return -1;
	  }
      /////Save current information into the structure ends///////
      //Save file
      if(_read(fh,&bfh,sizeof(bfh))!=sizeof(bfh))
	  {
	    MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
		return -2;
	  }
	  if(bfh.PixelBits!=8||bfh.Parts!=2||bfh.CodeBookSize[0]!=BOOKSIZE1||bfh.CodeBookSize[1]!=BOOKSIZE2||bfh.CodewordBytes[0]!=1||bfh.CodewordBytes[1]!=2||bfh.ImageBlockWidth!=4||bfh.ImageBlockHeight!=4||bfh.CodewordDimension[0]!=VQDIMENSION||bfh.CodewordDimension[1]!=VQDIMENSION)
	  {
	    MessageBox(NULL,"Format error","Codebook File Read",MB_ICONSTOP|MB_OK);
	    _close(fh);
	    return -2;
	  }
	  _lseek(fh,100,SEEK_SET);
	  if(component==2)
	  {
        if(_read(fh,&VQCodeBookYM[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&VQCodeBookYR[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==1)
	  {
        if(_read(fh,&VQCodeBookCbM[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&VQCodeBookCbR[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  if(component==0)
	  {
        if(_read(fh,&VQCodeBookCrM[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE1*sizeof(unsigned char)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
		if(_read(fh,&VQCodeBookCrR[0][0],VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int))!=(int)(VQDIMENSION*(unsigned long int)BOOKSIZE2*sizeof(short int)))
		{
	      MessageBox(NULL,"Read error","Codebook File Read",MB_ICONSTOP|MB_OK);
	      _close(fh);
		  return -2;
		}
	  }
	  //close the file 
      _close(fh);
	}
    return 0;
}







