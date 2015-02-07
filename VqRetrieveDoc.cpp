// VqRetrieveDoc.cpp : implementation of the CVqRetrieveDoc class
//
#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogDisplayImage.h"
#include "VqRetrieveDoc.h"
#include "DialogDatabase.h"
#include "DialogFeatureSelection.h"
#include "DialogFeedbakWithMemory.h"
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
	ON_COMMAND(ID_DATABASE_INDEXSAVE, OnDatabaseIndexsave)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_INDEXSAVE, OnUpdateDatabaseIndexsave)
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
	ON_COMMAND(ID_RETRIEVE_INDEX, OnRetrieveIndex)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_INDEX, OnUpdateRetrieveIndex)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_FIRST, OnUpdateDisplayFirst)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_LAST, OnUpdateDisplayLast)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_PREVIOUS, OnUpdateDisplayPrevious)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_NEXT, OnUpdateDisplayNext)
	ON_COMMAND(ID_EVALUATION_PRECISIONWITHTIME, OnEvaluationPrecisionwithtime)
	ON_UPDATE_COMMAND_UI(ID_EVALUATION_PRECISIONWITHTIME, OnUpdateEvaluationPrecisionwithtime)
	ON_COMMAND(ID_EVALUATION_RECALLWITHTIME, OnEvaluationRecallwithtime)
	ON_UPDATE_COMMAND_UI(ID_EVALUATION_RECALLWITHTIME, OnUpdateEvaluationRecallwithtime)
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
	ON_COMMAND(ID_DATABASE_OFEATURESPACEVQ, OnDatabaseOfeaturespacevq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_NFEATURESPACEVQ, OnUpdateDatabaseNfeaturespacevq)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_OFEATURESPACEVQ, OnUpdateDatabaseOfeaturespacevq)
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
	ON_COMMAND(ID_RETRIEVE_SORTING, OnRetrieveSorting)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_SORTING, OnUpdateRetrieveSorting)
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
	if((m_bFeatureFileSaved==false&&m_bDatabaseFeatureNormalized==true)||(m_bCodebookFileSaved==false&&m_bDatabaseClustered==true)||(m_bIndexFileSaved==false&&m_bDatabaseClustered==true))
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
		if(m_bIndexFileSaved==false)
		{
		  OnDatabaseIndexsave();
		  m_bIndexFileSaved=true;
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
    m_bRetrieveDisplay=false;  //Clear the previous retrieval results display flag
 	//m_bFeedBack=false;         //Clear the feedback flag
	//m_bOrglist=false;
	m_bRetrieveInterrupt=false;//
	m_bRetrieving=false;//
	m_bRetrieved=false;//	m_bOrglist=false;
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
	//m_bOrglist=false;
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
	m_clusteringbased=0;
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedindexfile="No index file saved";
	m_bDatabaseFeatureComputed=false;	
	m_bDatabaseFeatureComputing=false;	
	m_bDatabaseFeatureInterrupted=false;
	m_bDatabaseFeatureNormalized=false;	
	m_bDatabaseClustered=false;
	m_bFeatureFileSaved=false;
	m_bCodebookFileSaved=false;
	m_bIndexFileSaved=false;
	//m_bOrglist=false;
	DestroyDatabaseMemory();
	CreateDatabaseMemory();
}

//To compute the database feature
void CVqRetrieveDoc::OnDatabaseFeaturecompute() 
{
	// TODO: Add your command handler code here
	//If feature has been computed ask if continue?
	if(m_bDatabaseFeatureComputed==true&&::AfxMessageBox("The database path hasn't been changed, do you want to recompute the feature file,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	DestroyDatabaseMemory();//delete memory
	if(CreateDatabaseMemory()==false)return;//recreate memory
	m_extractednum=0;//no image computed
	m_normalizednum=0;//no feature normalized
	m_clusters=10;//the number of clusters
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedindexfile="No index file saved";
	m_bDatabaseFeatureComputed=false;//not computed
	m_bDatabaseFeatureComputing=true;//computing now
	m_bDatabaseFeatureInterrupted=false;//not interrupted
	m_bDatabaseFeatureNormalized=false;	//not normalized
	m_bDatabaseClustered=false;//not clustered
	m_bFeatureFileSaved=false;//not file saved
	m_bCodebookFileSaved=false;//
	m_bIndexFileSaved=false;//
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
	m_savedindexfile="No index file saved";
	m_bDatabaseFeatureNormalized=false;	//not normalized
	m_bDatabaseClustered=false;//not clustered
	m_bFeatureFileSaved=false;//not file saved
	m_bCodebookFileSaved=false;//
	m_bIndexFileSaved=false;//
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
/*	static int a=0;
	if(a==0)
	  MyRetrieveMethod.SortingByAverage(m_lpDFeatureVector,m_normalizednum);
	a=1;*/
	UpdateAllViews(NULL);
	EndWaitCursor();
}


void CVqRetrieveDoc::OnDatabaseNfeaturespacevq() 
{
	// TODO: Add your command handler code here
	
	if(m_bDatabaseClustered==true&&::AfxMessageBox("The database path hasn't been changed, do you want to reclustering the feature vectors,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	m_savedcodebookfile="No codebook file saved";
	m_savedindexfile="No index file saved";
	m_bDatabaseClustered=false;//not clustered
	m_bCodebookFileSaved=false;//
	m_bIndexFileSaved=false;//
	UpdateAllViews(NULL);
	BeginWaitCursor();
	WORD Iterations; 
	double Time,PSNR,MSE;
	if(MyRetrieveMethod.LBGCodebookDesign(m_normalizednum,m_clusters,m_ffi.m_wTotalDimensions,0.00001,m_lpDFeatureVector[0].m_dNormalizedFeature,m_dCodeword,m_wIndex,m_dwNumberinCluster,&MSE,&PSNR,&Time,&Iterations)<0)
	{
		MessageBox(NULL,"Parameter Error","Error",MB_OK|MB_ICONSTOP);
		return;
	}
    m_clusteringbased=0;
	m_bDatabaseClustered=true;
	UpdateAllViews(NULL);
	EndWaitCursor();
}

void CVqRetrieveDoc::OnDatabaseOfeaturespacevq() 
{
	// TODO: Add your command handler code here
	if(m_bDatabaseClustered==true&&::AfxMessageBox("The database path hasn't been changed, do you want to reclustering the feature vectors,OK?",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	m_savedcodebookfile="No codebook file saved";
	m_savedindexfile="No index file saved";
	m_bDatabaseClustered=false;//not clustered
	m_bCodebookFileSaved=false;//
	m_bIndexFileSaved=false;//
	UpdateAllViews(NULL);
	BeginWaitCursor();
    WORD Iterations; 
	double Time,PSNR,MSE;
	if(MyRetrieveMethod.LBGCodebookDesign(m_normalizednum,m_clusters,m_ffi.m_wTotalDimensions,0.00001,m_lpDFeatureVector[0].m_dOriginalFeature,m_dCodeword,m_wIndex,m_dwNumberinCluster,&MSE,&PSNR,&Time,&Iterations)<0)
	{
		MessageBox(NULL,"Parameter Error","Error",MB_OK|MB_ICONSTOP);
		return;
	}
    m_clusteringbased=1;
	m_bDatabaseClustered=true;
	UpdateAllViews(NULL);
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
	CString str;
	str=DataBaseFileName;
	strcpy(m_ffi.m_sThisFileNameLast8,str.Right(7));
	strcpy(m_ffi.m_sNextFileNameLast8,"fdbnone");
	m_ffi.m_dwFileNumber=m_normalizednum;
	strcpy(m_ffi.m_sPath,m_sDatabasePath);
    fdbfile.Write(&m_ffi,sizeof(FEATUREFILEINFO));
    fdbfile.Seek(600,CFile::begin);
    //Write the Featurevectors
	//fdbfile.Write(m_lpDFeatureVector,m_ffi.m_dwFileSize-600);
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
	m_cfh.m_bNormalization=m_clusteringbased;
	m_cfh.m_bWithColor=m_ffi.m_bWithColor;
	m_cfh.m_bWithRTInvariant=m_ffi.m_bWithRTInvariant;
	m_cfh.m_bWithTexture=m_ffi.m_bWithTexture;
	m_cfh.m_bWithShape=m_ffi.m_bWithShape;
	m_cfh.m_bWithOthers=m_ffi.m_bWithOthers;
	m_cfh.m_dwFileSize=128+sizeof(double)*m_ffi.m_wTotalDimensions*m_clusters;
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
    //Write the Featurevectors
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

void CVqRetrieveDoc::OnDatabaseIndexsave() 
{
	// TODO: Add your command handler code here
	CFile indfile;
	CString str;
	CFileException cfe;
	CString IndexFileName;
	char BASED_CODE szFilter[]="Index Files(*.ind)|*.ind|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(FALSE,"ind",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="Save Index File";
	if(m_ldFile.DoModal()!=IDOK)return;
	m_bIndexFileSaved=false;
    IndexFileName=m_ldFile.GetPathName();
	m_savedindexfile=m_ldFile.GetFileName();
	while(m_ldFile.GetFileName().GetLength()<7)
	{
	  MessageBox(NULL,"Please input filename with more than 3 Characters","Information", MB_OK|MB_ICONINFORMATION);
	  if(m_ldFile.DoModal()!=IDOK)return;
	  m_bIndexFileSaved=false;
	  IndexFileName=m_ldFile.GetPathName();
	  m_savedindexfile=m_ldFile.GetFileName();
	}
	if(!indfile.Open(IndexFileName,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary,&cfe))
	{
	  m_savedindexfile="No index file saved";
	  MessageBox(NULL,"Cannot create this file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	//write the m_ifh
	m_ifh.m_dwFileSize=64+2*m_normalizednum;
	m_ifh.m_dwIndexNumber=m_normalizednum;
	strcpy(m_ifh.m_sCodebookFileNameLast8,m_cfh.m_sThisFileNameLast8);
	m_ifh.m_wBytesPerIndex=2;
	m_ifh.m_wCodewordNumber=m_clusters;
	m_ifh.m_wOffBytes=64;
	m_ifh.m_wStructSize=sizeof(INDEXFILEHEADER);
	str=IndexFileName;
	strcpy(m_ifh.m_sThisFileNameLast8,str.Right(7));
    indfile.Write(&m_ifh,sizeof(INDEXFILEHEADER));
    indfile.Seek(64,CFile::begin);
    //Write the Featurevectors
	indfile.Write(m_wIndex,m_ifh.m_dwFileSize-64);
    if(m_ifh.m_dwFileSize!=indfile.GetLength())
	{
	  indfile.Close();
	  m_savedindexfile="No index file saved";
	  MessageBox(NULL,"File saved error","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	indfile.Close();
	m_bIndexFileSaved=true;
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
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	if(m_ffi_fromfile.m_wTotalDimensions<=0||m_ffi_fromfile.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_ffi_fromfile.m_wStructSize!=sizeof(FEATUREFILEINFO)||m_ffi_fromfile.m_wOffBytes!=600\
	||strcmp(m_ffi_fromfile.m_sThisFileNameLast8,DataBaseFileName.Right(7))!=0\
    ||m_ffi_fromfile.m_bFeatureTypes<1||m_ffi_fromfile.m_bFeatureTypes>7\
	||m_ffi_fromfile.m_dwFileNumber<1||m_ffi_fromfile.m_dwFileNumber>MAX_IMAGE_NUMBER)
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
    m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,m_validnum_r*(sizeof(FEATUREVECTOR)+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double))+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double)+m_ffi.m_wTotalDimensions*sizeof(double)*MAX_CODEBOOK_SIZE+sizeof(WORD)*m_validnum_r);
	if(m_hRFeatureVector==NULL)
	{
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return;
	}
	///The address of m_lpRFeatureVectors
	m_lpRFeatureVector=(LPFEATUREVECTOR)m_hRFeatureVector;
	fdbfile.Seek(600,CFile::begin);

	//read the featurevectors
	if(fdbfile.Read(m_lpRFeatureVector,sizeof(FEATUREVECTOR)*m_validnum_r)!=sizeof(FEATUREVECTOR)*m_validnum_r)
	{
	    MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	//the memory for detail features
	for(i=0;i<m_validnum_r;i++)
	  m_lpRFeatureVector[i].m_dOriginalFeature=(double *)((char *)m_hRFeatureVector+m_validnum_r*sizeof(FEATUREVECTOR))+i*m_ffi_fromfile.m_wTotalDimensions;
	for(i=0;i<m_validnum_r;i++)
	  m_lpRFeatureVector[i].m_dNormalizedFeature=m_lpRFeatureVector[0].m_dOriginalFeature+(i+m_validnum_r)*m_ffi_fromfile.m_wTotalDimensions;
	m_wIndex_r=(WORD *)(m_lpRFeatureVector[0].m_dNormalizedFeature+m_validnum_r*m_ffi_fromfile.m_wTotalDimensions);
	m_dCodeword_r=(double *)(m_wIndex_r+m_validnum_r);
	///The address of m_lpRComponentInfo
	m_lpRComponentInfo=(LPCOMPONENTINFO)(m_dCodeword_r+MAX_CODEBOOK_SIZE);
	//Read the detail Featurevectors
	for(i=0;i<m_validnum_r;i++)
	{
	  if(fdbfile.Read(m_lpRFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
	  {
	    MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	for(i=0;i<m_validnum_r;i++)
	{
	  if(fdbfile.Read(m_lpRFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
	  {
	    MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	}
	//Read the Component Info
	if(fdbfile.Read(m_lpRComponentInfo,sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)
	{
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	fdbfile.Close();
	lastpathname=DataBaseFileName;
	m_readfeaturename=m_ldFile.GetFileName();
    m_sRetrievePath=m_ffi_fromfile.m_sPath;
	if(m_ffi_fromfile.m_bEverInterrupted==TRUE)
	  m_everinterrupted="TRUE";
	else
	  m_everinterrupted="FALSE";
	m_bFeatureFileOpened=true;
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

void CVqRetrieveDoc::OnRetrieveSorting() 
{
	// TODO: Add your command handler code here
   BeginWaitCursor();
   MyRetrieveMethod.SortingByAverage(m_lpRFeatureVector,m_validnum_r);
   EndWaitCursor();	
   m_bSorted=true;
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
	if(lastpathname1==CodebookFileName)return;
	m_bCodebookFileOpened=false;
	m_bIndexFileOpened=false;
	m_bRetrieving=false;  //No retrieving
	//m_bRetrievingInterrupted=false;  //No retrieving interrupted
	m_bRetrieveDisplay=false;    //No retrieval results
    m_iRetrieveMethod=0;
	m_iSimpleFeedBackMethod=0;
	m_bQueryImageNormalized=false;
	m_readbookname="No codebook file opened";
	m_readindexname="No index file opened";
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
	||m_cfh_fromfile.m_wCodewordNumber>MAX_CODEBOOK_SIZE||m_cfh_fromfile.m_wCodewordNumber<1)
	{
	  bokfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_clustersused=m_cfh_fromfile.m_wCodewordNumber;
	a=sizeof(double)*m_cfh_fromfile.m_wTotalDimensions*m_clustersused+128;
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
	if(bokfile.Read(m_dCodeword_r,sizeof(double)*m_cfh_fromfile.m_wTotalDimensions*m_clustersused)!=sizeof(double)*m_cfh_fromfile.m_wTotalDimensions*m_clustersused)
	{
	    m_clustersused=0;
	    bokfile.Close();
	    UpdateAllViews(NULL);
	    MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}

	bokfile.Close();
	lastpathname1=CodebookFileName;
	m_readbookname=m_ldFile.GetFileName();
	if(m_cfh_fromfile.m_bNormalization==0)
	  m_basedonnormalized="TRUE";
	else
	  m_basedonnormalized="FALSE";
    m_bCodebookFileOpened=true;
	UpdateAllViews(NULL);
}
void CVqRetrieveDoc::OnRetrieveIndex() 
{
	// TODO: Add your command handler code here
	DWORD a;
	CFile indfile;
	CFileException cfe;
	CString IndexFileName;
	char BASED_CODE szFilter1[]="Index Files(*.ind)|*.ind|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open Index File";
	if(m_ldFile.DoModal()!=IDOK)return;
	IndexFileName=m_ldFile.GetPathName();
	if(lastpathname2==IndexFileName)return;
	m_bIndexFileOpened=false;
	m_bRetrieving=false;  //No retrieving
	//m_bRetrievingInterrupted=false;  //No retrieving interrupted
	m_bRetrieveDisplay=false;    //No retrieval results
    m_iRetrieveMethod=0;
	m_iSimpleFeedBackMethod=0;
	m_bQueryImageNormalized=false;
	m_readindexname="No index file opened";
	lastpathname2="";
	m_retrievednum=0;
	if(!indfile.Open(IndexFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox(NULL,"Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_cfh_fromfile
    if(indfile.Read(&m_ifh_fromfile,sizeof(INDEXFILEHEADER))!=sizeof(INDEXFILEHEADER))
	{
	   MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	if(m_ifh_fromfile.m_dwIndexNumber!=(DWORD)m_validnum_r||m_ifh_fromfile.m_wBytesPerIndex!=2\
	||m_ifh_fromfile.m_wStructSize!=sizeof(INDEXFILEHEADER)||m_ifh_fromfile.m_wOffBytes!=64\
	||strcmp(m_ifh_fromfile.m_sThisFileNameLast8,IndexFileName.Right(7))!=0\
    ||strcmp(m_cfh_fromfile.m_sThisFileNameLast8,m_ifh_fromfile.m_sCodebookFileNameLast8)!=0\
	||m_cfh_fromfile.m_wCodewordNumber!=m_ifh_fromfile.m_wCodewordNumber)
	{
	  indfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	a=2*m_validnum_r+64;
    if(a!=indfile.GetLength()||m_ifh_fromfile.m_dwFileSize!=a)
	{
	  indfile.Close();
	  UpdateAllViews(NULL);
	  MessageBox(NULL,"Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	indfile.Seek(64,CFile::begin);

	//read the featurevectors
	if(indfile.Read(m_wIndex_r,2*m_ifh_fromfile.m_dwIndexNumber)!=2*m_ifh_fromfile.m_dwIndexNumber)
	{
	    indfile.Close();
	    UpdateAllViews(NULL);
	    MessageBox(NULL,"Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}
	indfile.Close();
	lastpathname2=IndexFileName;
	m_readindexname=m_ldFile.GetFileName();
	m_bIndexFileOpened=true;
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
	if(m_bSorted==false)return;
	m_iRetrieveMethod=2;  ///The method 2
}
void CVqRetrieveDoc::OnRetrieveIeknnsuser() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false)return;
	m_iRetrieveMethod=3;  ///The method 3
	
}

void CVqRetrieveDoc::OnRetrieveIeknnsback() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false)return;
	m_iRetrieveMethod=4;  ///The method 4
}

void CVqRetrieveDoc::OnRetrieveVqonlynnc() 
{
	// TODO: Add your command handler code here
	if(m_bSorted==false)return;
	if(m_bCodebookFileOpened==false||m_bIndexFileOpened==false)return;
	m_iRetrieveMethod=5;  ///The method 5
}

void CVqRetrieveDoc::OnRetrieveVqonlyknncs() 
{
	// TODO: Add your command handler code here
    if(m_bSorted==false)return;
	if(m_bCodebookFileOpened==false||m_bIndexFileOpened==false)return;
	m_iRetrieveMethod=6;  ///The method 6
}

void CVqRetrieveDoc::OnRetrieveVqallclusters() 
{
	// TODO: Add your command handler code here
    if(m_bSorted==false)return;
	if(m_bCodebookFileOpened==false||m_bIndexFileOpened==false)return;
	m_iRetrieveMethod=7;  ///The method 7
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
	if(m_iRetrieveMethod>2)
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
	      if(m_validnum_r<=1000)
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 3://IEKNNS Search User
		  BeginWaitCursor();
		  IEKNNSURetrieveMethod();
		  processedpages=1;
		  time2=clock();
	      if(m_validnum_r<=1000)
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  EndWaitCursor();
		break;
	    case 4://IEKNNS Search Back
	 	  IEKNNSBRetrieveMethod();
		  time2=clock();
		  if(m_validnum_r<=1000)
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/5.0;
		  else
			 timecost=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
		  GlobalFree(SearchIndexList);
		  SearchIndexList=NULL;
		break;
	    case 5://IEKNNS Search Background
	 	  //MyRetrieveMethod.RetrieveKeyVqMethod_1Nomal(m_lpDFeatureVector,m_iCurrentFeatureDimension, m_iImageRetrieved, m_vQueryFeatureVector, m_cDisplayFeatureVector,16,&m_uDisplayNumber,m_dDisplayFileDistance, &m_sRetrieveTime);
	    break;
	    case 6://Vector retrieval
	 	  //MyRetrieveMethod.RetrieveKeyVqMethod_1Nomal(m_lpDFeatureVector,m_iCurrentFeatureDimension, m_iImageRetrieved, m_vQueryFeatureVector, m_cDisplayFeatureVector,16,&m_uDisplayNumber,m_dDisplayFileDistance, &m_sRetrieveTime);
	    break;
	    case 7://Vector retrieval
	 	  //MyRetrieveMethod.RetrieveKeyVqMethod_1Nomal(m_lpDFeatureVector,m_iCurrentFeatureDimension, m_iImageRetrieved, m_vQueryFeatureVector, m_cDisplayFeatureVector,16,&m_uDisplayNumber,m_dDisplayFileDistance, &m_sRetrieveTime);
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
	  if((m_page_setting_saved>0&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r))
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
void CVqRetrieveDoc::OnEvaluationPrecisionwithtime() 
{
	// TODO: Add your command handler code here
	
}
void CVqRetrieveDoc::OnEvaluationRecallwithtime() 
{
	// TODO: Add your command handler code here
	
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

//When retrieve or featurecompute, disable feature selection
//When no database opened disable
void CVqRetrieveDoc::OnUpdateDatabaseFeaturecompute(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
       pCmdUI->Enable(false);
	else
       pCmdUI->Enable(m_bDatabaseOpened);		
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

//When retrieve or featurecompute, disable clustering
//When no database feature normalized disable
void CVqRetrieveDoc::OnUpdateDatabaseNfeaturespacevq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
        pCmdUI->Enable(false);
 	else
        pCmdUI->Enable(m_bDatabaseFeatureNormalized);
	if(m_clusteringbased==0)
        pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);
}
//When retrieve or featurecompute, disable clustering
//When no database feature normalized disable
void CVqRetrieveDoc::OnUpdateDatabaseOfeaturespacevq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 	if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
        pCmdUI->Enable(false);
 	else
        pCmdUI->Enable(m_bDatabaseFeatureNormalized);
	if(m_clusteringbased==1)
        pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);	
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
void CVqRetrieveDoc::OnUpdateDatabaseIndexsave(CCmdUI* pCmdUI) 
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
      pCmdUI->Enable(m_bFeatureFileOpened); 
}

//When retrieve or featurecompute, disable feature file view
//when no codebook file opened,also disable
void CVqRetrieveDoc::OnUpdateRetrieveIndex(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(m_bCodebookFileOpened); 
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


//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveVqonlynnc(CCmdUI* pCmdUI) 
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

//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveVqonlyknncs(CCmdUI* pCmdUI) 
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
//When retrieve, disable retrieval method selection
void CVqRetrieveDoc::OnUpdateRetrieveVqallclusters(CCmdUI* pCmdUI) 
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
	if(m_iRetrieveMethod>2&&m_bSorted==false)//If no sorted
	{
		pCmdUI->Enable(false);
		return;
	}
	if(m_iRetrieveMethod>4)
	{
      if((m_bFeatureFileOpened==true)&&(m_bCodebookFileOpened==true)&&(m_bIndexFileOpened==true)&&(m_bDatabaseFeatureComputing==false)&&(m_bRetrieving==false)&&(m_bQueryImageNormalized==true))
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
void CVqRetrieveDoc::OnUpdateRetrieveSorting(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bRetrieving==true||m_bDatabaseFeatureComputing==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(m_bFeatureFileOpened); 
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
     if(oldmethod==3&&((m_page_setting_saved>0&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r)))
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
     if(oldmethod==3&&((m_page_setting_saved>0&&processedpages<m_page_setting_saved)||(m_page_setting_saved<0&&m_retrievednum<m_validnum_r)))
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


void CVqRetrieveDoc::OnUpdateEvaluationPrecisionwithtime(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   if(m_bDatabaseFeatureComputing==true||m_bRetrieving==true)
	  pCmdUI->Enable(false);
   else
      pCmdUI->Enable(m_bRetrieved); 
}


void CVqRetrieveDoc::OnUpdateEvaluationRecallwithtime(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bDatabaseFeatureComputing==true||m_bRetrieving==true)
	  pCmdUI->Enable(false);
    else
      pCmdUI->Enable(m_bRetrieved);  	
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
  strcpy(m_ffi.m_sFeature1_OF,"Input Name!(<32 Chars)");
  strcpy(m_ffi.m_sFeature2_OF,"Input Name!(<32 Chars)");
  strcpy(m_ffi.m_sFeature3_OF,"Input Name!(<32 Chars)");
  strcpy(m_ffi.m_sFeature4_OF,"Input Name!(<32 Chars)");
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
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.jpeg";
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
		    bitinfo->biSizeImage=info.imgHeight*info.imgWidth;
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
		    bitinfo->biSizeImage=info.imgHeight*info.imgWidth;
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
		    bitinfo->biSizeImage=info.imgHeight*info.imgWidth;
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
		    bitinfo->biSizeImage=info.imgHeight*info.imgWidth;
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
        returned=MyRetrieveMethod.compute_color_histogram_feature_vector(ImageBytes,
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
		returned=MyRetrieveMethod.compute_haar_integral_invariant_feature_vector(ImageBytes,
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
	   returned=MyRetrieveMethod.compute_texture_feature_vector(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,
		  m_Ffi.m_bDescription_TF,m_Ffi.m_bColorSpace_TF,m_Ffi.m_bCoocurrence_TF,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,m_Ffi.m_wDimension_TF,&dimensionused);
	}
	
	//Shape feature
	if(m_Ffi.m_bWithShape==TRUE)
	{
	   returned=MyRetrieveMethod.compute_shape_feature_vector(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,
		  m_Ffi.m_bDescription_SF,m_Ffi.m_bColorSpace_SF,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,m_Ffi.m_wDimension_SF,&dimensionused);
	}
	
	//Other features
	if(m_Ffi.m_bWithOthers==TRUE)
	{
	  if(m_Ffi.m_bWithFeature1_OF==TRUE)
	  {
	     returned=MyRetrieveMethod.compute_other_feature_vector1(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	  if(m_Ffi.m_bWithFeature2_OF==TRUE)
	  {
	     returned=MyRetrieveMethod.compute_other_feature_vector2(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	  if(m_Ffi.m_bWithFeature3_OF==TRUE)
	  {
	     returned=MyRetrieveMethod.compute_other_feature_vector3(ImageBytes,
		  FeatureVector->m_dOriginalFeature+dimensionused,FeatureVector->m_bBitCount,
		  FeatureVector->m_lImageWidth,FeatureVector->m_lImageHeight,&dimensionused);
	  }
	  if(m_Ffi.m_bWithFeature4_OF==TRUE)
	  {
	    returned=MyRetrieveMethod.compute_other_feature_vector4(ImageBytes,
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
	else if(ext=="jpg" || ext=='jpeg')
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
	m_hDFeatureVector=GlobalAlloc(GMEM_FIXED,m_validnum*(sizeof(FEATUREVECTOR)+m_ffi.m_wTotalDimensions*2*sizeof(double))+m_ffi.m_wTotalDimensions*2*sizeof(double)+(m_ffi.m_wTotalDimensions*sizeof(double)+sizeof(DWORD))*MAX_CODEBOOK_SIZE+sizeof(WORD)*m_validnum);
	if(m_hDFeatureVector==NULL)
	{
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return false;
	}
	
	///The address of m_lpDFeatureVectors
	m_lpDFeatureVector=(LPFEATUREVECTOR)m_hDFeatureVector;
	for(i=0;i<m_validnum;i++)
	{
	  m_lpDFeatureVector[i].m_dOriginalFeature=(double *)((char *)m_hDFeatureVector+m_validnum*sizeof(FEATUREVECTOR))+i*m_ffi.m_wTotalDimensions;
	}
	for(i=0;i<m_validnum;i++)
	{
	  m_lpDFeatureVector[i].m_dNormalizedFeature=m_lpDFeatureVector[0].m_dOriginalFeature+(i+m_validnum)*m_ffi.m_wTotalDimensions;
	}
	m_wIndex=(WORD *)(m_lpDFeatureVector[0].m_dNormalizedFeature+m_validnum*m_ffi.m_wTotalDimensions);
	m_dwNumberinCluster=(DWORD *)(m_wIndex+m_validnum);
	m_dCodeword=(double *)(m_dwNumberinCluster+MAX_CODEBOOK_SIZE);
	///The address of m_lpDComponentInfo
	m_lpDComponentInfo=(LPCOMPONENTINFO)(m_dCodeword+MAX_CODEBOOK_SIZE);
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
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.jpeg";
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
	str=sPath;
    if(str.Right(1)!="\\")str+="\\";
	str+="*.jpeg";
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
	m_clusteringbased=0;
	m_sDatabasePath="No image database is selected!";//No datbase path is selected
	m_savedfeaturefile="No feature file saved";
	m_savedcodebookfile="No codebook file saved";
	m_savedindexfile="No index file saved";
	m_bDatabaseOpened=false;
	m_bDatabaseChanged=false;
	m_bDatabaseFeatureComputed=false;	
	m_bDatabaseFeatureComputing=false;	
	m_bDatabaseFeatureInterrupted=false;
	m_bDatabaseFeatureNormalized=false;	
	m_bDatabaseClustered=false;
	m_bFeatureFileSaved=false;
	m_bCodebookFileSaved=false;
	m_bIndexFileSaved=false;
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
	m_bIndexFileOpened=false;
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
	m_readindexname="No index file opened";
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
		 a+=MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused);
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
	a=MyRetrieveMethod.ENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else//the first K=p*16 images
    a=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_page_setting_saved*16,RetrievedResult,&timeused,FALSE,NULL);
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
	a=MyRetrieveMethod.ENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
  else//the first 16 images
	a=MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,16,RetrievedResult,&timeused,TRUE,SearchIndexList);
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
	 a=MyRetrieveMethod.ENNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
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







