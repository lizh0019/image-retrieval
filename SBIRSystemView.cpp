// SBIRSystemView.cpp : implementation of the CSBIRSystemView class
//

#include "stdafx.h"
#include "SBIRSystem.h"

#include "SBIRSystemDoc.h"
#include "SBIRSystemView.h"
#include "DialogBase.h"
#include "DialogParamentSet.h"
#include "DialogLoadImage.h"
#include "ImageResultDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemView

IMPLEMENT_DYNCREATE(CSBIRSystemView, CFormView)

BEGIN_MESSAGE_MAP(CSBIRSystemView, CFormView)
//{{AFX_MSG_MAP(CSBIRSystemView)
ON_BN_CLICKED(IDC_BUTTON_OPENSAMPLE, OnButtonOpensample)
ON_BN_CLICKED(IDC_BUTTON_IMAGEDATABASE, OnButtonImagedatabase)
ON_BN_CLICKED(IDC_BUTTON_RETRIEVAL, OnButtonRetrieval)
ON_BN_CLICKED(IDC_BUTTON_NEXTPAGE, OnButtonNextpage)
ON_BN_CLICKED(IDC_BUTTON_PREPAGE, OnButtonPrepage)
ON_BN_CLICKED(IDC_BUTTON_HOMEPAGE, OnButtonHomepage)
ON_EN_CHANGE(IDC_THRESHOLD, OnChangeThreshold)
ON_BN_CLICKED(IDC_BUTTON_RELEVANCEFEEDBACK, OnButtonRelevancefeedback)
ON_BN_CLICKED(IDC_BUTTON_PARAMETER, OnButtonParameter)
ON_COMMAND(IDC_GETINFORMATINO, OnGetinformatino)
ON_COMMAND(IDC_RETRIEVAL_METHOD_TEST, OnRetrievalMethodTest)
	ON_COMMAND(IDC_INITIAL_SEMANTICANNOTION, OnInitialSemanticannotion)
	ON_COMMAND(ID_OPEN_ANNOTION, OnOpenAnnotion)
	ON_LBN_DBLCLK(IDC_LIST_ANNOTION, OnDblclkListAnnotion)
	ON_COMMAND(ID_CLOSE_ANNOTION, OnCloseAnnotion)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ANNOTION, OnUpdateOpenAnnotion)
	ON_UPDATE_COMMAND_UI(ID_CLOSE_ANNOTION, OnUpdateCloseAnnotion)
	ON_UPDATE_COMMAND_UI(IDC_INITIAL_SEMANTICANNOTION, OnUpdateInitialSemanticannotion)
	ON_BN_CLICKED(IDC_RESULTE1, OnResulte1)
	ON_BN_CLICKED(IDC_RESULTE2, OnResulte2)
	ON_BN_CLICKED(IDC_RESULTE10, OnResulte10)
	ON_BN_CLICKED(IDC_RESULTE11, OnResulte11)
	ON_BN_CLICKED(IDC_RESULTE12, OnResulte12)
	ON_BN_CLICKED(IDC_RESULTE3, OnResulte3)
	ON_BN_CLICKED(IDC_RESULTE4, OnResulte4)
	ON_BN_CLICKED(IDC_RESULTE5, OnResulte5)
	ON_BN_CLICKED(IDC_RESULTE6, OnResulte6)
	ON_BN_CLICKED(IDC_RESULTE7, OnResulte7)
	ON_BN_CLICKED(IDC_RESULTE8, OnResulte8)
	ON_BN_CLICKED(IDC_RESULTE9, OnResulte9)
	ON_EN_CHANGE(IDC_EDIT_KEYWORD_RETRIEVIED, OnChangeEditKeywordRetrievied)
	ON_BN_CLICKED(IDC_BUTTON_KEYWORDRETRIEVAL, OnButtonKeywordretrieval)
	ON_LBN_DBLCLK(IDC_LIST_KEYWORDRETRIEVIED, OnDblclkListKeywordretrievied)
	//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemView construction/destruction

CSBIRSystemView::CSBIRSystemView()
: CFormView(CSBIRSystemView::IDD)
{
	//{{AFX_DATA_INIT(CSBIRSystemView)
	m_iRelevance_1 = -1;
	m_iRelevance_2 = -1;
	m_iRelevance_3 = -1;
	m_iRelevance_4 = -1;
	m_iRelevance_5 = -1;
	m_iRelevance_6 = -1;
	m_iRelevance_7 = -1;
	m_iRelevance_8 = -1;
	m_iRelevance_9 = -1;
	m_iRelevance_10 = -1;
	m_iRelevance_11 = -1;
	m_iRelevance_12 = -1;
	m_sSimilarity_1 = _T("");
	m_sSimilarity_10 = _T("");
	m_sSimilarity_11 = _T("");
	m_sSimilarity_12 = _T("");
	m_sSimilarity_2 = _T("");
	m_sSimilarity_3 = _T("");
	m_sSimilarity_4 = _T("");
	m_sSimilarity_5 = _T("");
	m_sSimilarity_6 = _T("");
	m_sSimilarity_7 = _T("");
	m_sSimilarity_8 = _T("");
	m_sSimilarity_9 = _T("");	
	m_dThreshold = 0.75;
	m_sNumberImageDataBase = _T("");
	m_sSampleID = _T("");
	m_sNumberResult = _T("");
	m_sImagePath = _T("");
	m_sStudyTimes = _T("");
	m_sTotalPage = _T("");
	m_sCurrentPage = _T("");
	m_dRecall = 0.0;
	m_dPrecise = 0.0;
	m_sFeedbackTimes = _T("");
	m_sImageOrAnnotion = _T("图像ID：");
	m_sKeyWord = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	//initilaze the point 
	
	m_pCPictureCtrl[0]=&m_cRetrievalResult1;
	m_pCPictureCtrl[1]=&m_cRetrievalResult2;
	m_pCPictureCtrl[2]=&m_cRetrievalResult3;
	m_pCPictureCtrl[3]=&m_cRetrievalResult4;
	m_pCPictureCtrl[4]=&m_cRetrievalResult5;
	m_pCPictureCtrl[5]=&m_cRetrievalResult6;
	m_pCPictureCtrl[6]=&m_cRetrievalResult7;
	m_pCPictureCtrl[7]=&m_cRetrievalResult8;
	m_pCPictureCtrl[8]=&m_cRetrievalResult9;
	m_pCPictureCtrl[9]=&m_cRetrievalResult10;
	m_pCPictureCtrl[10]=&m_cRetrievalResult11;
	m_pCPictureCtrl[11]=&m_cRetrievalResult12;
	
	m_piRelevance[0]=&m_iRelevance_1;
	m_piRelevance[1]=&m_iRelevance_2;
	m_piRelevance[2]=&m_iRelevance_3;
	m_piRelevance[3]=&m_iRelevance_4;
	m_piRelevance[4]=&m_iRelevance_5;
	m_piRelevance[5]=&m_iRelevance_6;
	m_piRelevance[6]=&m_iRelevance_7;
	m_piRelevance[7]=&m_iRelevance_8;
	m_piRelevance[8]=&m_iRelevance_9;
	m_piRelevance[9]=&m_iRelevance_10;
	m_piRelevance[10]=&m_iRelevance_11;
	m_piRelevance[11]=&m_iRelevance_12;
	
	//
	m_psSimilarity[0]=&m_sSimilarity_1;
	m_psSimilarity[1]=&m_sSimilarity_2;
	m_psSimilarity[2]=&m_sSimilarity_3;
	m_psSimilarity[3]=&m_sSimilarity_4;
	m_psSimilarity[4]=&m_sSimilarity_5;
	m_psSimilarity[5]=&m_sSimilarity_6;
	m_psSimilarity[6]=&m_sSimilarity_7;
	m_psSimilarity[7]=&m_sSimilarity_8;
	m_psSimilarity[8]=&m_sSimilarity_9;
	m_psSimilarity[9]=&m_sSimilarity_10;
	m_psSimilarity[10]=&m_sSimilarity_11;
	m_psSimilarity[11]=&m_sSimilarity_12;
	m_bIntilization=false;
	m_bCanFeedback=false;
	m_bAnnotionOpened=false;
	m_iCurrentAnnotionIndex=-1;

}

CSBIRSystemView::~CSBIRSystemView()
{
}

void CSBIRSystemView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSBIRSystemView)
	DDX_Control(pDX, IDC_BUTTON_PARAMETER, m_cParamentSet);
	DDX_Control(pDX, IDC_EDIT_KEYWORD_RETRIEVIED, m_cKeyWordInput);
	DDX_Control(pDX, IDC_BUTTON_KEYWORDRETRIEVAL, m_cButtonRetrievalKeyWord);
	DDX_Control(pDX, IDC_LIST_KEYWORDRETRIEVIED, m_cListBoxKeyWordRetrievied);
	DDX_Control(pDX, IDC_BUTTON_OPENSAMPLE, m_cOpenSampleImage);
	DDX_Control(pDX, IDC_LIST_ANNOTION, m_cRelevantAnnotionList);
	DDX_Control(pDX, IDC_BUTTON_RELEVANCEFEEDBACK, m_cFeedbackControl);
	DDX_Control(pDX, IDC_RADIO1, m_CRadio1);
	DDX_Control(pDX, IDC_BUTTON_RETRIEVAL, m_cShouldRetrieval);
	DDX_Control(pDX, IDC_BUTTON_HOMEPAGE, m_cHomePage);
	DDX_Control(pDX, IDC_BUTTON_PREPAGE, m_cPrePage);
	DDX_Control(pDX, IDC_BUTTON_NEXTPAGE, m_cNextPage);
	DDX_Control(pDX, IDC_RESULTE9, m_cRetrievalResult9);
	DDX_Control(pDX, IDC_RESULTE8, m_cRetrievalResult8);
	DDX_Control(pDX, IDC_RESULTE7, m_cRetrievalResult7);
	DDX_Control(pDX, IDC_RESULTE6, m_cRetrievalResult6);
	DDX_Control(pDX, IDC_RESULTE5, m_cRetrievalResult5);
	DDX_Control(pDX, IDC_RESULTE4, m_cRetrievalResult4);
	DDX_Control(pDX, IDC_RESULTE3, m_cRetrievalResult3);
	DDX_Control(pDX, IDC_RESULTE2, m_cRetrievalResult2);
	DDX_Control(pDX, IDC_RESULTE12, m_cRetrievalResult12);
	DDX_Control(pDX, IDC_RESULTE11, m_cRetrievalResult11);
	DDX_Control(pDX, IDC_RESULTE10, m_cRetrievalResult10);
	DDX_Control(pDX, IDC_RESULTE1, m_cRetrievalResult1);
	DDX_Control(pDX, IDC_SAMPLEIMAGE_PICTURE, m_cSampleImage);
	DDX_Radio(pDX, IDC_RADIO1, m_iRelevance_1);
	DDX_Radio(pDX, IDC_RADIO4, m_iRelevance_2);
	DDX_Radio(pDX, IDC_RADIO7, m_iRelevance_3);
	DDX_Radio(pDX, IDC_RADIO10, m_iRelevance_4);
	DDX_Radio(pDX, IDC_RADIO13, m_iRelevance_5);
	DDX_Radio(pDX, IDC_RADIO16, m_iRelevance_6);
	DDX_Radio(pDX, IDC_RADIO19, m_iRelevance_7);
	DDX_Radio(pDX, IDC_RADIO22, m_iRelevance_8);
	DDX_Radio(pDX, IDC_RADIO25, m_iRelevance_9);
	DDX_Radio(pDX, IDC_RADIO28, m_iRelevance_10);
	DDX_Radio(pDX, IDC_RADIO31, m_iRelevance_11);
	DDX_Radio(pDX, IDC_RADIO34, m_iRelevance_12);
	DDX_Text(pDX, IDC_DATA_SIMILARITY, m_sSimilarity_1);
	DDX_Text(pDX, IDC_DATA_SIMILARITY10, m_sSimilarity_10);
	DDX_Text(pDX, IDC_DATA_SIMILARITY11, m_sSimilarity_11);
	DDX_Text(pDX, IDC_DATA_SIMILARITY12, m_sSimilarity_12);
	DDX_Text(pDX, IDC_DATA_SIMILARITY2, m_sSimilarity_2);
	DDX_Text(pDX, IDC_DATA_SIMILARITY3, m_sSimilarity_3);
	DDX_Text(pDX, IDC_DATA_SIMILARITY4, m_sSimilarity_4);
	DDX_Text(pDX, IDC_DATA_SIMILARITY5, m_sSimilarity_5);
	DDX_Text(pDX, IDC_DATA_SIMILARITY6, m_sSimilarity_6);
	DDX_Text(pDX, IDC_DATA_SIMILARITY7, m_sSimilarity_7);
	DDX_Text(pDX, IDC_DATA_SIMILARITY8, m_sSimilarity_8);
	DDX_Text(pDX, IDC_DATA_SIMILARITY9, m_sSimilarity_9);
	DDX_Text(pDX, IDC_THRESHOLD, m_dThreshold);
	DDV_MinMaxDouble(pDX, m_dThreshold, 0., 1.);
	DDX_Text(pDX, IDC_DATA_IMAGEDATABASESIZE, m_sNumberImageDataBase);
	DDX_Text(pDX, IDC_DATA_SAMPLEID, m_sSampleID);
	DDX_Text(pDX, IDC_DATA_RESULTNUMBER, m_sNumberResult);
	DDX_Text(pDX, IDC_DATA_IMAGERETRIEVALTIME, m_sImagePath);
	DDX_Text(pDX, IDC_DATA_STUDY_TIMES, m_sStudyTimes);
	DDX_Text(pDX, IDC_DATA_TOTALPAGES, m_sTotalPage);
	DDX_Text(pDX, IDC_DATA_CURRENTPAGE, m_sCurrentPage);
	DDX_Text(pDX, IDC_RECALL, m_dRecall);
	DDX_Text(pDX, IDC_PRECISE, m_dPrecise);
	DDX_Text(pDX, IDC_DATA_FEEDBACKTIME, m_sFeedbackTimes);
	DDX_Text(pDX, IDC_STATIC_CURRENT_STATE, m_sImageOrAnnotion);
	DDX_Text(pDX, IDC_EDIT_KEYWORD_RETRIEVIED, m_sKeyWord);
	//}}AFX_DATA_MAP
}

BOOL CSBIRSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CFormView::PreCreateWindow(cs);
}

void CSBIRSystemView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
}

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemView printing

BOOL CSBIRSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSBIRSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSBIRSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSBIRSystemView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemView diagnostics

#ifdef _DEBUG
void CSBIRSystemView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSBIRSystemView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSBIRSystemDoc* CSBIRSystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSBIRSystemDoc)));
	return (CSBIRSystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
//open the sample image
void CSBIRSystemView::OnButtonOpensample() 
{
	// TODO: Add your control notification handler code here
	int iNumber=this->m_cRetrievalControl.GetIntNumberImageDataBase();
	if (iNumber<=0)
	{
		return ;
	}
	CDialogLoadImage ImageLoad;
	ImageLoad.m_iTotalImageNumber=iNumber;
	ImageLoad.m_iCurentNumber=0;
	ImageLoad.m_sImagePath=this->m_cRetrievalControl.GetImageBasePath()+"\\image\\";

//	char BASED_CODE szFilter[]="DataBase Files(*.jpg)|*.jpg|All Files(*.*)|*.*||";
//	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(ImageLoad.DoModal()!=IDOK)
	{	
		return;
	}
	//load for display
	if(!this->m_cSampleImage.LoadImage(ImageLoad.GetFilePathName()))
	{
		AfxMessageBox("Sample Image Error",MB_OK);
		m_cSampleImage.LoadImage(m_sSampleImageFullName);
		return;
	}
	
	//get the file name 
	this->m_sSampleImageFullName=ImageLoad.GetFilePathName();
	m_cRetrievalControl.SetSampleID(m_sSampleImageFullName);	
	m_bCanFeedback=false;
	this->m_cListBoxKeyWordRetrievied.ResetContent();
	this->m_cRelevantAnnotionList.ResetContent();
	this->DisplayResult();

	
}


//load or creat a imagebase
void CSBIRSystemView::OnButtonImagedatabase() 
{
	// TODO: Add your control notification handler code here
	CDialogBase dialogbase;
	CString Path;  //the path
	int choose;   //the choose
	
	if(dialogbase.DoModal()!=IDOK)		return;
	
	Path=dialogbase.m_sPathName;  //get the path
	choose=dialogbase.imagebasechoose;  //get the choose
	
	//start
	BeginWaitCursor();
	m_bCanFeedback=false;
	//	this->UpdateWindow();
	switch(choose) 
	{
	case 1://choose a base exist
		if (m_cImageBasemanage.LoadImageBase(Path)==false) 
		{
			MessageBox("Load Image Base error","System information",MB_OK);
			return ;
		}
		choose=-1;
		break;
	case 2://creat a new base
		if (m_cImageBasemanage.CreatImageBase(Path)==false)
		{
			MessageBox("Creat error,file exist or read error!","System information",MB_OK);
			return ;
		}
		choose=-1;
		break;
	default:
		return;
		break;
	}
	//end,get the path
	m_sImageBasePath=Path;	
	this->m_bAnnotionOpened=false;
	this->m_cListBoxKeyWordRetrievied.ResetContent();
	this->m_cRelevantAnnotionList.ResetContent();	
	//read the path
	m_cRetrievalControl.ReadImageBase(m_sImageBasePath);
	EndWaitCursor();
	this->DisplayResult();
	
}
//button for retrieval
void CSBIRSystemView::OnButtonRetrieval() 
{
	//get the par
	
	this->UpdateData(true);
	BeginWaitCursor();
	if(m_cRetrievalControl.Retrieval(this->m_dThreshold)==true)
		this->m_bCanFeedback=true;  //retrieval
	else m_bCanFeedback=false;

	//end retrieval 
	//begin relevant annotion
	int iNumberRelevantAnnotion=MAX_NUMBERANNOTION_RELEVANT;
	if (this->m_bAnnotionOpened==true)
	{
		this->m_cRelevantAnnotionList.ResetContent();
		iNumberRelevantAnnotion=m_cRetrievalControl.GetRelevantAnnotionID(this->m_iRelevantAnnotionIDs,iNumberRelevantAnnotion,0);
		for(int i=0;i<iNumberRelevantAnnotion;i++)
		{
			char temp[100];
			if(this->m_cRetrievalControl.GetRelevantAnnotionText(temp,100,this->m_iRelevantAnnotionIDs[i])==true)			
			this->m_cRelevantAnnotionList.AddString(temp);
		}
	}
	EndWaitCursor();
	//display
	this->DisplayResult();  //display
	
}
//display the retrieval results
void CSBIRSystemView::DisplayResult()
{
	//display the images on  pannel
	//this->m_cRetrievalControl.DisplayOnPictureStruct(*m_pCPictureCtrl,*this->m_piRelevance,*this->m_psSimilarity,i);
	BeginWaitCursor();
	m_cRetrievalControl.DisplayCurrentPage(m_pCPictureCtrl,this->m_piRelevance,this->m_psSimilarity);	
	this->UpdateDisplay();
	EndWaitCursor();
	
}


//display the next page
void CSBIRSystemView::OnButtonNextpage() 
{
	// TODO: Add your control notification handler code here
	
	this->updateRelevanceData();
	if(m_cRetrievalControl.SetNexToBeCurrentPage()==false) 
	{
		return;
	}
	DisplayResult();
}
//button for pre page
void CSBIRSystemView::OnButtonPrepage() 
{
	// TODO: Add your control notification handler code here
	this->updateRelevanceData();
	if (m_cRetrievalControl.SetPreToBeCurrentPage()==false) return ;
	DisplayResult();
}
//button for home page
void CSBIRSystemView::OnButtonHomepage() 
{
	// TODO: Add your control notification handler code here	
	this->updateRelevanceData();
	if (m_cRetrievalControl.SetFirstToCurrentPage()==false) return ;
	DisplayResult();
}
//updata the display
void CSBIRSystemView::UpdateDisplay()
{
	//update the "information"
	this->m_sImagePath=this->m_cRetrievalControl.GetImageBasePath();
	this->m_sSampleID=m_cRetrievalControl.GetRetrievalIDThis();
	this->m_sNumberImageDataBase=m_cRetrievalControl.GetNumberImageDataBase();
	this->m_sNumberResult=m_cRetrievalControl.GetNumberResult();
	int iRetrievalType=this->m_cRetrievalControl.GetRetrievalTypeThis();
	this->m_sSampleID=this->m_cRetrievalControl.GetRetrievalIDThis();
	m_sImageOrAnnotion.Empty();
	if (0==iRetrievalType)
	{		
		this->m_sImageOrAnnotion="图像ID:";
	}
	else
		this->m_sImageOrAnnotion="检索语义";
	
	
	//updata the result information
	this->m_cHomePage.EnableWindow(false);
	this->m_cPrePage.EnableWindow(false);
	this->m_cNextPage.EnableWindow(false);
	this->m_sCurrentPage.Empty();
	this->m_sCurrentPage.Format("%s%d",m_sCurrentPage,m_cRetrievalControl.GetCurrentPage());
	this->m_sTotalPage.Empty();
	this->m_sTotalPage.Format("%s%d",m_sTotalPage,m_cRetrievalControl.GetTotalPage());
	this->m_sFeedbackTimes.Empty();
	this->m_sFeedbackTimes=m_cRetrievalControl.GetFeedbackTimes();
	
	//update the "control"
	this->m_cOpenSampleImage.EnableWindow(this->m_cRetrievalControl.IsKnowledgeValid());
	this->m_cButtonRetrievalKeyWord.EnableWindow(this->m_sKeyWord!=""&&this->m_cRetrievalControl.IsKnowledgeValid()==true&&this->m_bAnnotionOpened==true);
	this->m_cKeyWordInput.EnableWindow(this->m_cRetrievalControl.IsKnowledgeValid()==true&&this->m_bAnnotionOpened==true);
	this->m_cFeedbackControl.EnableWindow(this->m_bCanFeedback);
	this->m_cParamentSet.EnableWindow(this->m_cRetrievalControl.IsKnowledgeValid()==true);

//	m_cFeedbackControl.SetDlgItemText(13,"Feedback");
	this->m_cShouldRetrieval.EnableWindow(m_cRetrievalControl.IsNeedRetrieval());
	this->m_sStudyTimes=m_cRetrievalControl.GetStudtyTimes();
	
	//update the retrieval result
	if(m_cRetrievalControl.GetNumberResult()!="")
	{
		if(m_cRetrievalControl.GetCurrentPage()>0)
		{
			this->m_cHomePage.EnableWindow(true);
			this->m_cPrePage.EnableWindow(true);
		}
		if (m_cRetrievalControl.GetCurrentPage()<m_cRetrievalControl.GetTotalPage()-1)		
			this->m_cNextPage.EnableWindow(true);
		
	}
	this->m_dRecall=m_cRetrievalControl.GetRecall();
	this->m_dPrecise=m_cRetrievalControl.GetPrecise();

	//updedata the relevant annotion

/*
		if (this->m_bAnnotionOpened==true)
		{
			for(int i=0;i<3;i++)
			{
				char temp[100];
				if(this->m_cRetrievalControl.GetRelevantAnnotionText(temp,100,this->m_iAnnotionID[i])==true)			
				this->m_cRelevantAnnotionList.AddString(temp);
			}
		}*/
	
	
	//out put the paraments
	this->UpdateData(false);
	
	//output the retrieval results
	Invalidate();
	
	
}
//initilization
void CSBIRSystemView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bIntilization==false)
	{
		UpdateDisplay();
		m_bIntilization=true;
	}
	
	
}
//if change the threshold
void CSBIRSystemView::OnChangeThreshold() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
}

//update the relevance of the data
void CSBIRSystemView::updateRelevanceData()
{
	UpdateData(true);	
	m_cRetrievalControl.SetRelevanceCurrentPageResult(this->m_piRelevance);
}

void CSBIRSystemView::OnButtonRelevancefeedback() 
{
	// TODO: Add your control notification handler code here
	//update
	updateRelevanceData();	
	BeginWaitCursor();
	if(m_cRetrievalControl.RelevanceFeedback(this->m_dThreshold)==FALSE)	
		MessageBox("Please check some relevant ones!","system error",MB_OK);
	
	//begin relevant annotion
	int iNumberRelevantAnnotion=MAX_NUMBERANNOTION_RELEVANT;
	if (this->m_bAnnotionOpened==true)
	{
		this->m_cRelevantAnnotionList.ResetContent();
		iNumberRelevantAnnotion=m_cRetrievalControl.GetRelevantAnnotionID(this->m_iRelevantAnnotionIDs,iNumberRelevantAnnotion,0);
		for(int i=0;i<iNumberRelevantAnnotion;i++)
		{
			char temp[100];
			if(this->m_cRetrievalControl.GetRelevantAnnotionText(temp,100,this->m_iRelevantAnnotionIDs[i])==true)			
			this->m_cRelevantAnnotionList.AddString(temp);
		}
	}
	//end relevant annotion
	EndWaitCursor();
	
	//display
	this->DisplayResult();  //display
}

void CSBIRSystemView::OnButtonParameter() 
{
	// TODO: Add your control notification handler code here
	CDialogParamentSet cParamentSet;
	this->m_cRetrievalControl.GetFeedbackParament(cParamentSet.m_dParamentRR,cParamentSet.m_dParamentSI,cParamentSet.m_dParamentSU,(bool &)(cParamentSet.m_bStudying));
	if(cParamentSet.DoModal()==false) return;
	this->m_cRetrievalControl.SetFeedbackParament(cParamentSet.m_dParamentRR,cParamentSet.m_dParamentSI,cParamentSet.m_dParamentSU,cParamentSet.m_bStudying);
	
	
}
//test 
//for the experiment 1, the output file is "exmperiment.txt"
/************************************************************************/
/* this test is test the retrieval result,
*the test image is 4,9 ,14,19,... 999 total there are 200 image
* the threshold is 0.4, 0.42,,, 1    ,total 31 thresholds                                                                 */
/************************************************************************/
void CSBIRSystemView::OnGetinformatino() 
{
	return ;
	// TODO: Add your command handler code here
	//threshold=0.4:0.02:1
	//i=4:5:999
	double dThreshold=0.4;
	const double dThresholdIncrease=0.02;
	
	unsigned int iTestID=4;  //9+5*n
	const int iIDIncrease=5;
	const unsigned int IIMAGENUMBER=1000;
	
	double dRecall=0,dRecallAverage=0;
	double dPrecise=0,dPreciseAverage=0;
	
	CFile fTestOut;
	CString OutFileName="experiment1.txt";  //out file	
	CString sTempData;
	
	if(fTestOut.Open(OutFileName,CFile::modeCreate|CFile::modeReadWrite)==false) return;
	//
	int i,j=0;
	double di;
	
	//write the head
	fTestOut.SeekToEnd();
	fTestOut.Write("This is experiment 1,test the retrieval method!",sizeof("This is experiment 1,test the retrieval method!"));
	BeginWaitCursor();
	for(di=dThreshold;di<=1;di=di+dThresholdIncrease)
	{
		//write the threshold
		fTestOut.SeekToEnd();
		fTestOut.Write("\n\\\\\\\\\\\\\\\\\\\\\\\\n",sizeof("\n\\\\\\\\\\\\\\\\\\\\\\\\n"));
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,di);
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.Write("\n",sizeof("\n"));
		dPreciseAverage=0;
		dRecallAverage=0;
		j=0;
		
		for(i=iTestID;i<IIMAGENUMBER;i=i+iIDIncrease)
		{
			//retrieval
			m_cRetrievalControl.SetSampleID(i);
			if(this->m_cRetrievalControl.Retrieval(di)==false){ fTestOut.Close(); return;}
			dRecall=m_cRetrievalControl.GetRecall();
			dPrecise=m_cRetrievalControl.GetPrecise();
			dRecallAverage=dRecallAverage+dRecall;
			dPreciseAverage=dPreciseAverage+dPrecise;
			j++;		
			
		} //end of one threshold
		//the threshold ,the average
		//write the average of this threshold
		dRecallAverage=dRecallAverage/j;
		dPreciseAverage=dPreciseAverage/j;
		fTestOut.SeekToEnd();
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,dRecallAverage);
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.Write("\t",sizeof("\t"));
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,dPreciseAverage);
		fTestOut.Write(sTempData,sizeof(double));
		
		
		
	}  //end for di
	fTestOut.Close();
	//here we want our system can achieve the experiment 1 and 3 once
	EndWaitCursor();
	this->OnRetrievalMethodTest();
}

//the experiment 2 is test the relevance feedback
//we maybe need ask some person do for us

/************************************************************************/
/*      
*   this is experiment 3 ,it was use to test the retrieval method of lays                                                          
*   the test image is :4:5:999,total 200
*   the threshold is 0.4:0.02:1 total 31 thresholds
/************************************************************************/
//test
//for the experiment 3, the output file is "exmperiment_3.txt"/

void CSBIRSystemView::OnRetrievalMethodTest() 
{
	return;
	//threshold=0.5:0.05:1
	//i=9:10:999
	double dThreshold=0.4;
	const double dThresholdIncrease=0.02;
	
	unsigned int iTestID=4;  //4+5*n
	const int iIDIncrease=5;
	const unsigned int IIMAGENUMBER=1000;
	
	double dRecall=0,dRecallAverage=0;
	double dPrecise=0,dPreciseAverage=0;
	
	CFile fTestOut;
	CString OutFileName="experiment3.txt";  //out file
	CString sTempData;
	
	if(fTestOut.Open(OutFileName,CFile::modeCreate|CFile::modeReadWrite)==false) return;
	//
	int i=0,j=0,iLayConsidered=0;
	int iTotalLayTestNumber=0;
	double di;
	clock_t timestart,timeend;
	
	//write the head
	fTestOut.SeekToEnd();
	fTestOut.Write("This is experiment 3,test the retrieval method!",sizeof("This is experiment 3,test the retrieval method!"));
	
	//begin test
	BeginWaitCursor();
	for(iLayConsidered=1;iLayConsidered<=5;iLayConsidered++)
	{
		this->m_cRetrievalControl.SetTestLay(iLayConsidered);
		//write the head
		fTestOut.SeekToEnd();
		fTestOut.Write("Lays test!",sizeof("Lays test!"));
		iTotalLayTestNumber=0;
		timestart=clock();
		for(di=dThreshold;di<=1;di=di+dThresholdIncrease)
		{
			//write the threshold
			fTestOut.SeekToEnd();
			fTestOut.Write("\n\\\\\\\\\\\\\\\\\\\\\\\\n",sizeof("\n\\\\\\\\\\\\\\\\\\\\\\\\n"));
			sTempData.Empty();
			sTempData.Format("%s%f",sTempData,di);
			fTestOut.SeekToEnd();
			fTestOut.Write(sTempData,sizeof(double));
			fTestOut.SeekToEnd();
			fTestOut.Write("\n",sizeof("\n"));
			dPreciseAverage=0;
			dRecallAverage=0;
			j=0;
			
			for(i=iTestID;i<IIMAGENUMBER;i=i+iIDIncrease)
			{
				//retrieval
				m_cRetrievalControl.SetSampleID(i);
				if(this->m_cRetrievalControl.Retrieval(di)==false){ fTestOut.Close(); return;}
				dRecall=m_cRetrievalControl.GetRecall();
				dPrecise=m_cRetrievalControl.GetPrecise();
				dRecallAverage=dRecallAverage+dRecall;
				dPreciseAverage=dPreciseAverage+dPrecise;
				iTotalLayTestNumber++;
				j++;
				
			} //end of one threshold
			//the threshold ,the average
			//write the average of this threshold
			dRecallAverage=dRecallAverage/j;
			dPreciseAverage=dPreciseAverage/j;
			fTestOut.SeekToEnd();
			sTempData.Empty();
			sTempData.Format("%s%f",sTempData,dRecallAverage);
			fTestOut.Write(sTempData,sizeof(double));
			fTestOut.SeekToEnd();
			fTestOut.Write("\t",sizeof("\t"));
			sTempData.Empty();
			sTempData.Format("%s%f",sTempData,dPreciseAverage);
			fTestOut.SeekToEnd();
			fTestOut.Write(sTempData,sizeof(double));			
		}  //end for di
		timeend=clock();
		sTempData.Empty();
		sTempData.Format("%s%f",sTempData,(double)(timeend-timestart)/iTotalLayTestNumber/1000.0);
		fTestOut.SeekToEnd();
		fTestOut.Write(sTempData,sizeof(double));
		fTestOut.SeekToEnd();
		fTestOut.Write("\t\n",sizeof("\t\n"));
		
	} //end of iLayConsidered
	fTestOut.Close();
	EndWaitCursor();
	MessageBox("Experiment 3 is end");
}
/************************************************************************/
/* test for read annotion                                                                     */
void CSBIRSystemView::OnInitialSemanticannotion() 
{
	// TODO: Add your command handler code here
	BOOL bSucceed=FALSE;
	if(AfxMessageBox("Are you sure to Rebuild the initial Semantic annotion,link and matrix",MB_OKCANCEL)!=IDOK)
	{
		return ;
	}
	bSucceed=this->m_cRetrievalControl.WriteAnnotionFile(this->m_sImageBasePath);

	if (bSucceed==FALSE) 
	{
		MessageBox("writeAnnotion");
		return;
	}
	//write the link
	bSucceed=this->m_cRetrievalControl.WriteInitalLinkFile();
	if (bSucceed==FALSE) 
	{
		MessageBox("writeLink");
		return;
	}
	bSucceed=this->m_cRetrievalControl.WriteInitalMatrixFile();
	if (bSucceed==FALSE) 
	{
		MessageBox("writeSemanticMatrix");
		return;
	}
}

void CSBIRSystemView::OnOpenAnnotion() 
{
	// TODO: Add your command handler code here
	//succeed
	BOOL bSucceed=FALSE;
	this->m_cRetrievalControl.SetAnnotion(false);
	this->m_bAnnotionOpened=false;
	if (this->m_cRetrievalControl.ReadAnnotionLinkFile()==true&&this->m_cRetrievalControl.ReadAnnotionMatrixFile()==true) 
	{
		
		this->m_cRetrievalControl.SetAnnotion(true);
		this->m_bAnnotionOpened=true;
		this->UpdateDisplay();
		return ;
	}
	//create
	
	if(AfxMessageBox("Are you sure to Rebuild the initial Semantic annotion,link and matrix",MB_OKCANCEL)!=IDOK)
	{
		this->UpdateDisplay();
		return ;
	}
	bSucceed=this->m_cRetrievalControl.WriteAnnotionFile(this->m_sImageBasePath);
	
	if (bSucceed==FALSE) 
	{
		this->UpdateDisplay();
		MessageBox("writeAnnotion");
		return;
	}
	//write the link
	bSucceed=this->m_cRetrievalControl.WriteInitalLinkFile();
	if (bSucceed==FALSE) 
	{
		this->UpdateDisplay();
		MessageBox("writeLink");
		
		return;
	}
	bSucceed=this->m_cRetrievalControl.WriteInitalMatrixFile();
	if (bSucceed==FALSE) 
	{
		this->UpdateDisplay();
		MessageBox("writeSemanticMatrix");
		return;
	}
	//reload it again
	if (this->m_cRetrievalControl.ReadAnnotionLinkFile()==true||this->m_cRetrievalControl.ReadAnnotionMatrixFile()==true) 
	{		
		this->m_cRetrievalControl.SetAnnotion(true);
		this->m_bAnnotionOpened=true;
		this->UpdateDisplay();
		return ;
	}
	else
	{
		this->UpdateDisplay();
		MessageBox("Create error");
		return;
	}
	return ;
}

void CSBIRSystemView::OnDblclkListAnnotion() 
{
	// TODO: Add your control notification handler code here
	//MessageBox("hello");
	this->UpdateData(true);
	BeginWaitCursor();
	this->m_iCurrentAnnotionIndex=this->m_cRelevantAnnotionList.GetCaretIndex();
	if(this->m_cRetrievalControl.RetrievalByAnnotionIndex(this->m_iRelevantAnnotionIDs[this->m_iCurrentAnnotionIndex],this->m_dThreshold)==false)
	{
		m_bCanFeedback=false;	
		MessageBox("error");
	}

	else
		this->m_bCanFeedback=true;  //retrieval
	//end retrieval 
//begin relevant annotion
	int iNumberRelevantAnnotion=MAX_NUMBERANNOTION_RELEVANT;
	if (this->m_bAnnotionOpened==true)
	{
		this->m_cRelevantAnnotionList.ResetContent();
		iNumberRelevantAnnotion=m_cRetrievalControl.GetRelevantAnnotionID(this->m_iRelevantAnnotionIDs,iNumberRelevantAnnotion,0);
		for(int i=0;i<iNumberRelevantAnnotion;i++)
		{
			char temp[100];
			if(this->m_cRetrievalControl.GetRelevantAnnotionText(temp,100,this->m_iRelevantAnnotionIDs[i])==true)			
			this->m_cRelevantAnnotionList.AddString(temp);
		}
	}
	//end relevant annotion
	EndWaitCursor();
	
	//display
	this->DisplayResult();  //display
	
}

void CSBIRSystemView::OnCloseAnnotion() 
{
	// TODO: Add your command handler code here
	this->m_bAnnotionOpened=false;
	this->m_cListBoxKeyWordRetrievied.ResetContent();
	this->m_cRelevantAnnotionList.ResetContent();
	this->m_sKeyWord.Empty();
}

void CSBIRSystemView::OnUpdateOpenAnnotion(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_bAnnotionOpened==false&&this->m_cRetrievalControl.IsKnowledgeValid()==true);
	
}

void CSBIRSystemView::OnUpdateCloseAnnotion(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(this->m_bAnnotionOpened==true);	
}

void CSBIRSystemView::OnUpdateInitialSemanticannotion(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(this->m_cRetrievalControl.IsKnowledgeValid()==true);
	//here we didn't display it
		pCmdUI->Enable(false);
}

void CSBIRSystemView::OnResulte1() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult1);	
}

void CSBIRSystemView::OnResulte2() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult2);		
}

void CSBIRSystemView::OnResulte10() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult10);		
}

void CSBIRSystemView::OnResulte11() 
{
	// TODO: Add your control notification handler code here
		this->Display(this->m_cRetrievalResult11);	
}

void CSBIRSystemView::OnResulte12() 
{
	// TODO: Add your control notification handler code here
		this->Display(this->m_cRetrievalResult12);		
}

void CSBIRSystemView::OnResulte3() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult3);	
}

void CSBIRSystemView::OnResulte4() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult4);	
}

void CSBIRSystemView::OnResulte5() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult5);		
}

void CSBIRSystemView::OnResulte6() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult6);	
}

void CSBIRSystemView::OnResulte7() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult7);		
}

void CSBIRSystemView::OnResulte8() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult8);		
}

void CSBIRSystemView::OnResulte9() 
{
	// TODO: Add your control notification handler code here
	this->Display(this->m_cRetrievalResult9);	
}
/************************************************************************/
/* update the display of the button: retrieval keyword                                                                     */
/************************************************************************/
void CSBIRSystemView::OnChangeEditKeywordRetrievied() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);
	this->m_cButtonRetrievalKeyWord.EnableWindow(this->m_sKeyWord!=""&&this->m_cRetrievalControl.IsKnowledgeValid()==true&&this->m_bAnnotionOpened==true);
}
/************************************************************************/
/* Display the information and control of the result of PictureCtrl                                                                     */
/************************************************************************/
void CSBIRSystemView::Display(CPictureCtrl &PictureCtrl)
{
	CImageResultDialog cImageResult;
	cImageResult.m_sImageFullPath=PictureCtrl.GetImagePathName();
	if (cImageResult.m_sImageFullPath=="")
	{
		return ;	
	}
	cImageResult.DoModal();	
	//should retrieval it
	if (cImageResult.m_bRetrievalChanged==TRUE)
	{
		this->m_cSampleImage.LoadImage(cImageResult.m_sImageFullPath);
		this->m_cRetrievalControl.SetSampleID(cImageResult.m_sImageFullPath);
		this->OnButtonRetrieval();
	}
}

void CSBIRSystemView::OnButtonKeywordretrieval() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	this->m_cListBoxKeyWordRetrievied.ResetContent();
	int iMaxNumberRetrievalAnnotion=sizeof(m_piRetrievalAnnotionIDS);

	iMaxNumberRetrievalAnnotion=this->m_cRetrievalControl.RetrievalByKeyWord(m_piRetrievalAnnotionIDS,iMaxNumberRetrievalAnnotion,this->m_sKeyWord);
	if(iMaxNumberRetrievalAnnotion<=0) 
	{
			MessageBox("文字搜索能力有限，请更改其他检索方式或者更换检索词","系统提示");
			return;
	}
	for(int i=0;i<iMaxNumberRetrievalAnnotion;i++)
	{
		char temp[100];
		this->m_cRetrievalControl.GetRelevantAnnotionText(temp,100,m_piRetrievalAnnotionIDS[i]);			
		
		//itoa(this->m_iAnnotionID[i],temp,10);
		//temp.Format(("%i%s",this->m_iAnnotionID[i],temp));
		this->m_cListBoxKeyWordRetrievied.AddString(temp);
	}
}

void CSBIRSystemView::OnDblclkListKeywordretrievied() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(true);
	BeginWaitCursor();
	this->m_iCurrentAnnotionIndex=this->m_cListBoxKeyWordRetrievied.GetCaretIndex();
	if(this->m_cRetrievalControl.RetrievalByAnnotionIndex(this->m_piRetrievalAnnotionIDS[this->m_iCurrentAnnotionIndex],this->m_dThreshold)==false)
	{
		m_bCanFeedback=false;	
		MessageBox("error");
	}

	else
		this->m_bCanFeedback=true;  //retrieval
	//end retrieval 
//begin relevant annotion
	int iNumberRelevantAnnotion=MAX_NUMBERANNOTION_RELEVANT;
	if (this->m_bAnnotionOpened==true)
	{
		this->m_cRelevantAnnotionList.ResetContent();
		iNumberRelevantAnnotion=m_cRetrievalControl.GetRelevantAnnotionID(this->m_iRelevantAnnotionIDs,iNumberRelevantAnnotion,0);
		for(int i=0;i<iNumberRelevantAnnotion;i++)
		{
			char temp[100];
			if(this->m_cRetrievalControl.GetRelevantAnnotionText(temp,100,this->m_iRelevantAnnotionIDs[i])==true)			
			this->m_cRelevantAnnotionList.AddString(temp);
		}
	}
	//end relevant annotion
	EndWaitCursor();
	
	//display
	this->DisplayResult();  //display
}
