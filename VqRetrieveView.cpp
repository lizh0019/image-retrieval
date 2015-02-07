// VqRetrieveView.cpp : implementation of the CVqRetrieveView class
//

#include "stdafx.h"
#include "VqRetrieve.h"

#include "VqRetrieveDoc.h"
#include "VqRetrieveView.h"
#include "DialogDisplayImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveView

IMPLEMENT_DYNCREATE(CVqRetrieveView, CFormView)

BEGIN_MESSAGE_MAP(CVqRetrieveView, CFormView)
	//{{AFX_MSG_MAP(CVqRetrieveView)
	ON_EN_KILLFOCUS(IDC_EDIT_DB6, OnKillfocusEditDb6)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveView construction/destruction

CVqRetrieveView::CVqRetrieveView()
	: CFormView(CVqRetrieveView::IDD)
{
	//{{AFX_DATA_INIT(CVqRetrieveView)
	m_retrievalname1 = _T("");
	m_retrievalname10 = _T("");
	m_retrievalname11 = _T("");
	m_retrievalname12 = _T("");
	m_retrievalname13 = _T("");
	m_retrievalname14 = _T("");
	m_retrievalname15 = _T("");
	m_retrievalname16 = _T("");
	m_retrievalname2 = _T("");
	m_retrievalname3 = _T("");
	m_retrievalname4 = _T("");
	m_retrievalname5 = _T("");
	m_retrievalname6 = _T("");
	m_retrievalname7 = _T("");
	m_retrievalname8 = _T("");
	m_retrievalname9 = _T("");
	m_dis1 = -1.0f;
	m_dis10 = -1.0f;
	m_dis11 = -1.0f;
	m_dis12 = -1.0f;
	m_dis13 = -1.0f;
	m_dis14 = -1.0f;
	m_dis15 = -1.0f;
	m_dis16 = -1.0f;
	m_dis2 = -1.0f;
	m_dis3 = -1.0f;
	m_dis4 = -1.0f;
	m_dis5 = -1.0f;
	m_dis6 = -1.0f;
	m_dis7 = -1.0f;
	m_dis8 = -1.0f;
	m_dis9 = -1.0f;
	m_db = _T("");
	m_queryinfo = _T("");
	m_totalnum = 0;
	m_validnum = 0;
	m_extractednum = 0;
	m_normalizednum = 0;
	m_clusters = 0;
	m_savedfeaturefile = _T("");
	m_savedcodebookfile = _T("");
	m_db10 = _T("");
	m_vectornumber = 0;
	m_readfeaturename = _T("");
	m_readbookname = _T("");
	m_clustersused = 0;
	m_retrievednum = 0;
	m_everinterrupted = _T("");
	m_basedonnormalized = _T("");
	m_page = 0;
	m_status = _T("");
	m_feedbackinfo = _T("");
	m_otherinfo = _T("");
	m_featuredimension = 0;
	m_savedvqfeaturefile = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	moved=0;
//	Window
	m_bFileLost=false;      ///No image lost
	//SetWindowPos(NULL,0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN),0);
}

CVqRetrieveView::~CVqRetrieveView()
{
	for(int i=0;i<16;i++)
	{
	  if(Imageh[i]!=NULL)
	  {
		GlobalFree(Imageh[i]);
		Imageh[i]=NULL;
	  }
	}
}

void CVqRetrieveView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVqRetrieveView)
	DDX_Control(pDX, IDC_STATICRETRIEVAL9, m_RetrievalImage9);
	DDX_Control(pDX, IDC_STATICRETRIEVAL8, m_RetrievalImage8);
	DDX_Control(pDX, IDC_STATICRETRIEVAL7, m_RetrievalImage7);
	DDX_Control(pDX, IDC_STATICRETRIEVAL6, m_RetrievalImage6);
	DDX_Control(pDX, IDC_STATICRETRIEVAL5, m_RetrievalImage5);
	DDX_Control(pDX, IDC_STATICRETRIEVAL4, m_RetrievalImage4);
	DDX_Control(pDX, IDC_STATICRETRIEVAL3, m_RetrievalImage3);
	DDX_Control(pDX, IDC_STATICRETRIEVAL2, m_RetrievalImage2);
	DDX_Control(pDX, IDC_STATICRETRIEVAL16, m_RetrievalImage16);
	DDX_Control(pDX, IDC_STATICRETRIEVAL15, m_RetrievalImage15);
	DDX_Control(pDX, IDC_STATICRETRIEVAL14, m_RetrievalImage14);
	DDX_Control(pDX, IDC_STATICRETRIEVAL13, m_RetrievalImage13);
	DDX_Control(pDX, IDC_STATICRETRIEVAL12, m_RetrievalImage12);
	DDX_Control(pDX, IDC_STATICRETRIEVAL11, m_RetrievalImage11);
	DDX_Control(pDX, IDC_STATICRETRIEVAL10, m_RetrievalImage10);
	DDX_Control(pDX, IDC_STATICRETRIEVAL1, m_RetrievalImage1);
	DDX_Control(pDX, IDC_STATICQUERY, m_QueryImage);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME1, m_retrievalname1);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME10, m_retrievalname10);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME11, m_retrievalname11);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME12, m_retrievalname12);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME13, m_retrievalname13);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME14, m_retrievalname14);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME15, m_retrievalname15);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME16, m_retrievalname16);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME2, m_retrievalname2);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME3, m_retrievalname3);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME4, m_retrievalname4);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME5, m_retrievalname5);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME6, m_retrievalname6);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME7, m_retrievalname7);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME8, m_retrievalname8);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME9, m_retrievalname9);
	DDX_Text(pDX, IDC_EDIT_DIS1, m_dis1);
	DDX_Text(pDX, IDC_EDIT_DIS10, m_dis10);
	DDX_Text(pDX, IDC_EDIT_DIS11, m_dis11);
	DDX_Text(pDX, IDC_EDIT_DIS12, m_dis12);
	DDX_Text(pDX, IDC_EDIT_DIS13, m_dis13);
	DDX_Text(pDX, IDC_EDIT_DIS14, m_dis14);
	DDX_Text(pDX, IDC_EDIT_DIS15, m_dis15);
	DDX_Text(pDX, IDC_EDIT_DIS16, m_dis16);
	DDX_Text(pDX, IDC_EDIT_DIS2, m_dis2);
	DDX_Text(pDX, IDC_EDIT_DIS3, m_dis3);
	DDX_Text(pDX, IDC_EDIT_DIS4, m_dis4);
	DDX_Text(pDX, IDC_EDIT_DIS5, m_dis5);
	DDX_Text(pDX, IDC_EDIT_DIS6, m_dis6);
	DDX_Text(pDX, IDC_EDIT_DIS7, m_dis7);
	DDX_Text(pDX, IDC_EDIT_DIS8, m_dis8);
	DDX_Text(pDX, IDC_EDIT_DIS9, m_dis9);
	DDX_Text(pDX, IDC_EDIT_DB, m_db);
	DDX_Text(pDX, IDC_EDIT_QUERYINFO, m_queryinfo);
	DDX_Text(pDX, IDC_EDIT_DB2, m_totalnum);
	DDX_Text(pDX, IDC_EDIT_DB3, m_validnum);
	DDX_Text(pDX, IDC_EDIT_DB4, m_extractednum);
	DDX_Text(pDX, IDC_EDIT_DB5, m_normalizednum);
	DDX_Text(pDX, IDC_EDIT_DB6, m_clusters);
	DDX_Text(pDX, IDC_EDIT_DB7, m_savedfeaturefile);
	DDX_Text(pDX, IDC_EDIT_DB8, m_savedcodebookfile);
	DDX_Text(pDX, IDC_EDIT_DB10, m_db10);
	DDX_Text(pDX, IDC_EDIT_DB11, m_vectornumber);
	DDX_Text(pDX, IDC_EDIT_DB13, m_readfeaturename);
	DDX_Text(pDX, IDC_EDIT_DB14, m_readbookname);
	DDX_Text(pDX, IDC_EDIT_DB17, m_clustersused);
	DDX_Text(pDX, IDC_EDIT_DB18, m_retrievednum);
	DDX_Text(pDX, IDC_EDIT_DB12, m_everinterrupted);
	DDX_Text(pDX, IDC_EDIT_DB16, m_basedonnormalized);
	DDX_Text(pDX, IDC_EDIT_DB19, m_page);
	DDX_Text(pDX, IDC_EDIT_DB20, m_status);
	DDX_Text(pDX, IDC_EDIT_DB21, m_feedbackinfo);
	DDX_Text(pDX, IDC_EDIT_DB22, m_otherinfo);
	DDX_Text(pDX, IDC_EDIT_DB15, m_featuredimension);
	DDX_Text(pDX, IDC_EDIT_DB9, m_savedvqfeaturefile);
	//}}AFX_DATA_MAP
}

BOOL CVqRetrieveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CVqRetrieveView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if(moved==0)
	{
	  GetParentFrame()->RecalcLayout();
	  ResizeParentToFit();
	  MoveToPositions();
	  moved=1;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveView printing

BOOL CVqRetrieveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage(1);
	pInfo->SetMinPage(1);
	return DoPreparePrinting(pInfo);
}

void CVqRetrieveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVqRetrieveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVqRetrieveView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add customized printing code here
////////////////////My code begins to print///////////////////////
	CVqRetrieveDoc* pDoc = GetDocument();//Get pDoc
	ASSERT_VALID(pDoc);//Make pDoc valid
    ////Set text mode and color and mapmode
    pDC->SetTextAlign(TA_CENTER);//Left mode
    pDC->SetTextColor(RGB(0,0,0));//Block text
    pDC->SetMapMode(1);//Mode 1
    double a,b,a0,b0;//The ratio for width and height
	int left,top,width,height;//The variables for print position
 	int i,p;
	POINT point;//The position for display information
	CString Title,tt;
	FEATUREVECTOR displayvqfile;
	char temp[256];//Temporary memory for string
	a0=(double)pInfo->m_rectDraw.right/50.0;
	b0=(double)pInfo->m_rectDraw.bottom/64.0;
    Title="Query Image: ";
    Title+=pDoc->m_vQueryFeatureVector.m_sOriginalFileName;//Get the document title
    ////Get the ratio in width and height directions
    a=10*a0;
    a=a/(double)pDoc->m_vQueryFeatureVector.m_lImageWidth;
    b=10*b0;
    b=b/(double)pDoc->m_vQueryFeatureVector.m_lImageHeight;
    if(a>b)a=b;//Select the smaller one as the common ratio
    ////Calculate the position and size for printing the original image
    left=(int)((double)pInfo->m_rectDraw.right/2.0)-(int)(a/2.0*(double)pDoc->m_vQueryFeatureVector.m_lImageWidth);
    top=(int)(b0*2.0);
    width=(int)(a*(double)pDoc->m_vQueryFeatureVector.m_lImageWidth);
    height=(int)(a*(double)pDoc->m_vQueryFeatureVector.m_lImageHeight);
    ////Compute the position to display the information of the original image
    point.x=(int)((double)pInfo->m_rectDraw.right/2.0);
    point.y=top;
    top=top+(int)(b0);
	//with query
	if(pDoc->m_printflag<2)
	{
	  pDC->TextOut(point.x,point.y,Title);//Print the information for original image
	  ////Print the original image
	  if(pDoc->m_vQueryFeatureVector.m_bBitCount==8)
	    ::StretchDIBits(pDC->m_hDC,left,top,width,height,0,0,pDoc->m_vQueryFeatureVector.m_lImageWidth,pDoc->m_vQueryFeatureVector.m_lImageHeight,pDoc->m_QueryImageFile+1078,(BITMAPINFO *)(pDoc->m_QueryImageFile+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	  else
	    ::StretchDIBits(pDC->m_hDC,left,top,width,height,0,0,pDoc->m_vQueryFeatureVector.m_lImageWidth,pDoc->m_vQueryFeatureVector.m_lImageHeight,pDoc->m_QueryImageFile+54,(BITMAPINFO *)(pDoc->m_QueryImageFile+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	}
	//with results
	if(pDoc->m_printflag>0)
	{
      Title="Retrieval results of";//Get the document title
      top+=(int)(b0*10.0);
	  Title+=" path [";
	  Title+=m_db10;
	  sprintf(temp,"],Page No.%d",m_page);
	  Title+=temp;
	  point.x=(int)((double)pInfo->m_rectDraw.right/2.0);
	  point.y=top;
	  top+=(int)b0;
	  pDC->TextOut(point.x,point.y,Title);//Print the information for original image
	  if(pDoc->m_iSimpleFeedBackMethod==0)
      Title="Memoryless feedback used";//
	  else
      {
		  Title="Memory feedback used";
	      sprintf(temp,"; Memory depth=%d; Current memory buf=%d",pDoc->m_T2,pDoc->m_Iterations+1);
	      Title+=temp;
	  }
	  point.x=(int)((double)pInfo->m_rectDraw.right/2.0);
	  point.y=top;
	  top+=(int)b0;
	  p=top;
	  pDC->TextOut(point.x,point.y,Title);//Print the information for original image
	  left=(int)(a0*2.0);
	  for(i=0;i<DisplayNumber;i++)
	  {
	    left=(int)(a0*2.0)+(int)(a0*12.0*(int)(i%4));
		top=p+(int)(b0*12.0*(int)(i/4));
		displayvqfile=pDoc->GetDisplayFeatureVector(i);
	    a=10.0*a0/(double)displayvqfile.m_lImageWidth;
	    b=10.0*b0/(double)displayvqfile.m_lImageHeight;
	    if(a>b)a=b;//Select the smaller one as the common ratio
	    width=(int)(a*(double)displayvqfile.m_lImageWidth);
	    height=(int)(a*(double)displayvqfile.m_lImageHeight);
	    if(pDoc->GetDisplayFileName(i)=="")
		{
			Title="File Lost";
			pDC->MoveTo(left,top);
			pDC->LineTo(left+width,top+height);
			pDC->MoveTo(left+width,top);
			pDC->LineTo(left,top+height);
		}
	    else
		{
		  Imageh[i]=NULL;
		  GetRetrievalImageFile(displayvqfile.m_sOriginalFileName,displayvqfile.m_bType,i);
          if(displayvqfile.m_bBitCount==8)
	       ::StretchDIBits(pDC->m_hDC,left,top,width,height,0,0,displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,m_RetrievalImageFile[i]+1078,(BITMAPINFO *)(m_RetrievalImageFile[i]+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	      else
	       ::StretchDIBits(pDC->m_hDC,left,top,width,height,0,0,displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,m_RetrievalImageFile[i]+54,(BITMAPINFO *)(m_RetrievalImageFile[i]+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
		  Title=pDoc->GetDisplayFileName(i);
		}
		point.x=left+(int)(a0*5.0);
        point.y=top+(int)(b0*10.0);
	    pDC->TextOut(point.x,point.y,Title);//Print the information for original image
		point.y=top+(int)(b0*11.0);
		sprintf(temp,"Dis=%.4f",pDoc->GetDistance(i));
		Title=temp;
	    pDC->TextOut(point.x,point.y,Title);//Print the information for original image
	  }
	}
	////Call the ondraw function of base class not this class
	CView::OnDraw(pDC);	
////////////////////My code ends to print///////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveView diagnostics

#ifdef _DEBUG
void CVqRetrieveView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVqRetrieveView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVqRetrieveDoc* CVqRetrieveView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVqRetrieveDoc)));
	return (CVqRetrieveDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveView message handlers

void CVqRetrieveView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CVqRetrieveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int displayWidth;
	int displayHeight;
	char str[80];
	CString temp;
	HBITMAP QueryImage;
    
	//When feature computing, hide some controls
	if(pDoc->m_bDatabaseFeatureComputing==true)
	  FeatureComputingRelatedWindowShow(SW_HIDE);
	else
	  FeatureComputingRelatedWindowShow(SW_SHOW);
	
	//after clustering, disable the m_cluster input
	if(pDoc->m_bDatabaseClustered==true)
	  GetDlgItem(IDC_EDIT_DB6)->EnableWindow(false);
	else
	  GetDlgItem(IDC_EDIT_DB6)->EnableWindow(true);
	/////Display the inital parameters
    DisplayInitialParameters();

	//draw the Query image//
    if(pDoc->m_bFileOpened==true)
	{
	   displayWidth=SuitableWidth(pDoc->m_vQueryFeatureVector.m_lImageWidth,pDoc->m_vQueryFeatureVector.m_lImageHeight,300,175);
	   displayHeight=SuitableHeight(pDoc->m_vQueryFeatureVector.m_lImageWidth,pDoc->m_vQueryFeatureVector.m_lImageHeight,300,175);
	   m_queryinfo="Query image filename:"+pDoc->m_sQueryImageFilePathName;
	   if(pDoc->m_vQueryFeatureVector.m_bType==0)
	   {
		  QueryImage=(HBITMAP)::LoadImage(NULL,pDoc->m_sQueryImageFilePathName,IMAGE_BITMAP,displayWidth,displayHeight,\
		  LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
		  m_QueryImage.SetBitmap(QueryImage);
		  ::DeleteObject(QueryImage);
	   } 
	   else if(pDoc->m_vQueryFeatureVector.m_bType==1)
	   {
		  temp=pDoc->m_CurrentDirectory;
		  temp=temp+"\\tempquery.bmp";
	      QueryImage=(HBITMAP)::LoadImage(NULL,temp,IMAGE_BITMAP,displayWidth,displayHeight,\
		  LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
		  m_QueryImage.SetBitmap(QueryImage);
		  ::DeleteObject(QueryImage);
	   }
	}
	
	//Display the retrieval results
    if(pDoc->m_bRetrieveDisplay==true) //If there are retrieved images
	{    
	  //Display the page info and retrieval images
	  DisplayNumber=pDoc->m_uDisplayNumber;
	  m_page=pDoc->m_displaypage+1;
	  DisplayRetrieval();
	  
	  //Display the status
      if(pDoc->m_bRetrieving==true)  ///Retrieving
	  	m_status="Retrieving...";
	  else if (pDoc->m_bRetrieveInterrupt==true)////Interrupted
	  	m_status="Retrieval Interrupted";  // Status
	  else//Retrieval Successfully Ended
		m_status="Retrieval Success";  // Status
      //if some images are lost
      if(m_bFileLost==true)
    	m_status+="; However,in this page some retrieved images cann't be opened";  // Error
      //Display feedback info
	  if(pDoc->m_iSimpleFeedBackMethod==0)
        m_feedbackinfo="Memoryless feedback method used";
	  else
	  {
	    sprintf(str,"Memory feedback used, memory length= %d, current memory buf=%d",pDoc->m_T2,pDoc->m_Iterations+1);
		m_feedbackinfo=str;
	  }
	  
	  //Display other info
	  sprintf(str,"Last retrieval method is the %d st method",pDoc->m_iRetrieveMethod+1);
	  m_otherinfo=str;
	  m_otherinfo+="; Retrieval Time:"+pDoc->m_sCostAllTime+"us";  ///All Time
	  m_otherinfo+="; Arithmetic Time:"+pDoc->m_sRetrieveTime+"us";  // Algorithm Time	
	}		 
	//Update the parameters
    UpdateData(false);
}


//Display The retrieval results
void CVqRetrieveView::DisplayRetrieval()
{
	CVqRetrieveDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	HBITMAP RetrievalImage;
	FEATUREVECTOR displayvqfile;
	int displayWidth;
    int displayHeight;
	if(DisplayNumber>=1)
	{
		m_dis1=pDoc->GetDistance(0);
		m_retrievalname1=pDoc->GetDisplayFileName(0);
		if(m_retrievalname1=="")
		{
			m_retrievalname1="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(0);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
          displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage1.SetBitmap(RetrievalImage);
			//((CButton *)GetDlgItem(IDC_BUTTON_RETRIEVAL1))->SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		  	  DisplayJpegFile(displayvqfile.m_sOriginalFileName,1,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=2)
	{
		m_dis2=pDoc->GetDistance(1);
		m_retrievalname2=pDoc->GetDisplayFileName(1);
		if(m_retrievalname2=="")
		{
			m_retrievalname2="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(1);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage2.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,2,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=3)
	{
		m_dis3=pDoc->GetDistance(2);
		m_retrievalname3=pDoc->GetDisplayFileName(2);
		if(m_retrievalname3=="")
		{
			m_retrievalname3="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(2);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage3.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		   DisplayJpegFile(displayvqfile.m_sOriginalFileName,3,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=4)
	{
		m_dis4=pDoc->GetDistance(3);
		m_retrievalname4=pDoc->GetDisplayFileName(3);
		if(m_retrievalname4=="")
		{
			m_retrievalname4="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(3);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage4.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,4,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=5)
	{
		m_dis5=pDoc->GetDistance(4);
		m_retrievalname5=pDoc->GetDisplayFileName(4);
		if(m_retrievalname5=="")
		{
			m_retrievalname5="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(4);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage5.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,5,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=6)
	{
		m_dis6=pDoc->GetDistance(5);
		m_retrievalname6=pDoc->GetDisplayFileName(5);
		if(m_retrievalname6=="")
		{
			m_retrievalname6="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(5);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage6.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,6,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=7)
	{
		m_dis7=pDoc->GetDistance(6);
		m_retrievalname7=pDoc->GetDisplayFileName(6);
		if(m_retrievalname7=="")
		{
			m_retrievalname7="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(6);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage7.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,7,displayWidth,displayHeight);
		}

	}
	if(DisplayNumber>=8)
	{
		m_dis8=pDoc->GetDistance(7);
		m_retrievalname8=pDoc->GetDisplayFileName(7);
		if(m_retrievalname8=="")
		{
			m_retrievalname8="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(7);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage8.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,8,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=9)
	{
		m_dis9=pDoc->GetDistance(8);
		m_retrievalname9=pDoc->GetDisplayFileName(8);
		if(m_retrievalname9=="")
		{
			m_retrievalname9="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(8);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage9.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,9,displayWidth,displayHeight);
		}
	}
	if(DisplayNumber>=10)
	{
		m_dis10=pDoc->GetDistance(9);
		m_retrievalname10=pDoc->GetDisplayFileName(9);
		if(m_retrievalname10=="")
		{
			m_retrievalname10="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		   displayvqfile=pDoc->GetDisplayFeatureVector(9);
		   displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	       displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		   if(displayvqfile.m_bType==0)
		   {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage10.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		   }
           else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,10,displayWidth,displayHeight);
		}
	}
	if (DisplayNumber>=11)
	{
		m_dis11=pDoc->GetDistance(10);
		m_retrievalname11=pDoc->GetDisplayFileName(10);
		if(m_retrievalname11=="")
		{
			m_retrievalname11="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		   displayvqfile=pDoc->GetDisplayFeatureVector(10);
		   displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	       displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		   if(displayvqfile.m_bType==0)
		   {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage11.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		   }
		   else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,11,displayWidth,displayHeight);
		}
	}
	if (DisplayNumber>=12)
	{
		m_dis12=pDoc->GetDistance(11);
		m_retrievalname12=pDoc->GetDisplayFileName(11);
		if(m_retrievalname12=="")
		{
			m_retrievalname12="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		  displayvqfile=pDoc->GetDisplayFeatureVector(11);
		  displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	      displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		  if(displayvqfile.m_bType==0)
		  {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage12.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		  }
		  else
		   DisplayJpegFile(displayvqfile.m_sOriginalFileName,12,displayWidth,displayHeight);
		}
	}
	if (DisplayNumber>=13)
	{
		m_dis13=pDoc->GetDistance(12);
		m_retrievalname13=pDoc->GetDisplayFileName(12);
		if(m_retrievalname13=="")
		{
			m_retrievalname13="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		   displayvqfile=pDoc->GetDisplayFeatureVector(12);
		   displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	       displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
	       if(displayvqfile.m_bType==0)
		   {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage13.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		   }
		   else
		     DisplayJpegFile(displayvqfile.m_sOriginalFileName,13,displayWidth,displayHeight);
		}
	}			
	if (DisplayNumber>=14)
	{
		m_dis14=pDoc->GetDistance(13);
		m_retrievalname14=pDoc->GetDisplayFileName(13);
		if(m_retrievalname14=="")
		{
			m_retrievalname14="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		   displayvqfile=pDoc->GetDisplayFeatureVector(13);
		   displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
           displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		   if(displayvqfile.m_bType==0)
		   {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage14.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		   }
		   else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,14,displayWidth,displayHeight);
		}
	}
    if (DisplayNumber>=15)											
	{
		m_dis15=pDoc->GetDistance(14);
		m_retrievalname15=pDoc->GetDisplayFileName(14);
		if(m_retrievalname15=="")
		{
			m_retrievalname15="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		   displayvqfile=pDoc->GetDisplayFeatureVector(14);
		   displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	       displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		   if(displayvqfile.m_bType==0)
		   {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage15.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		   }
		   else
		     DisplayJpegFile(displayvqfile.m_sOriginalFileName,15,displayWidth,displayHeight);
		}
	}
	if (DisplayNumber>=16)
	{
		m_dis16=pDoc->GetDistance(15);
		m_retrievalname16=pDoc->GetDisplayFileName(15);
		if(m_retrievalname16=="")
		{
			m_retrievalname16="This image is lost";
			m_bFileLost=true;
		}
		else
		{
		   displayvqfile=pDoc->GetDisplayFeatureVector(15);
		   displayWidth=SuitableWidth(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);
	       displayHeight=SuitableHeight(displayvqfile.m_lImageWidth,displayvqfile.m_lImageHeight,120,120);			
		   if(displayvqfile.m_bType==0)
		   {
			RetrievalImage=(HBITMAP)::LoadImage(NULL,displayvqfile.m_sOriginalFileName,IMAGE_BITMAP,displayWidth,displayHeight,\
		    LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_RetrievalImage16.SetBitmap(RetrievalImage);
		    ::DeleteObject(RetrievalImage);
		   }
		   else
		    DisplayJpegFile(displayvqfile.m_sOriginalFileName,16,displayWidth,displayHeight);
		}
	}
}
int CVqRetrieveView::GetRetrievalImageFile(char m_sOriginalFileName[MAX_PATH],int type,int num)
{
    CVqRetrieveDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	unsigned int x,y;
	long int fh;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	JPEG_IMAGE_INFO info;
	LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	if(type==0)
	{
	  fh=_open(m_sOriginalFileName,_O_BINARY|_O_RDONLY);
	  if(fh==-1)return -1;
	  Imageh[num]=GlobalAlloc(GMEM_FIXED,_filelength(fh));//Apply the required memory
	  if(Imageh[num]==NULL)return -2;
	  if(_read(fh,m_RetrievalImageFile[num],_filelength(fh))!=_filelength(fh))
	  {
	    _close(fh);
	    return -2;
	  }
	  _close(fh);	  
	}
	else
	{
	   if(jpg.open(m_sOriginalFileName,IDCT_INT))
	   {  
		  jpg.getImageInfo(&info);
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)pDoc->m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(pDoc->m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
		    linebytes=(info.imgWidth*24+31)/32*4;
		    bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
		    Imageh[num]=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imageh[num]==NULL)
			{
	          jpg.close();
			  return -2;
			}
            m_RetrievalImageFile[num]=(unsigned char *)Imageh[num];//Give the memory pointer to the file data pointer
            memcpy(m_RetrievalImageFile[num],pDoc->m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_RetrievalImageFile[num][54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_RetrievalImageFile[num][54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_RetrievalImageFile[num][54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
		    bitfile=(LPBITMAPFILEHEADER)pDoc->m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(pDoc->m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    Imageh[num]=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imageh[num]==NULL)
			{
            //  _close(fh); //Close the file
	          //MessageBox(NULL,"No enough memory!","Temporary File Save",MB_ICONSTOP|MB_OK);//Display Info
	          jpg.close();
			  return -2;
			}
            m_RetrievalImageFile[num]=(unsigned char *)Imageh[num];//Give the memory pointer to the file data pointer
            memcpy(m_RetrievalImageFile[num],pDoc->m_StandardBmpInfoc,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_RetrievalImageFile[num]+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  jpg.close();
	   }
	}
	return 0;

}

int CVqRetrieveView::DisplayJpegFile(char m_sOriginalFileName[MAX_PATH],int num,int displayWidth,int displayHeight)
{
    CVqRetrieveDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	HBITMAP RetrievalImage;
	unsigned int x,y;
	long int fh;
	unsigned char *m_cImageBytes;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	JPEG_IMAGE_INFO info;
	HGLOBAL Imagehg;
    LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	if(jpg.open(m_sOriginalFileName,IDCT_INT))
	{ 
		  jpg.getImageInfo(&info);
		  temp=pDoc->m_CurrentDirectory;
		  temp=temp+"\\tempretri.bmp";
	      fh=_open(temp,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
		  if(fh==-1)
		  { 
	        jpg.close();
			return -1;
		  }
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)pDoc->m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(pDoc->m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
		    linebytes=(info.imgWidth*24+31)/32*4;
		    bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
		    Imagehg=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
            memcpy(m_cImageBytes,pDoc->m_StandardBmpInfoc,54);
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
		    bitfile=(LPBITMAPFILEHEADER)pDoc->m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(pDoc->m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*linebytes;
		    Imagehg=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          //MessageBox(NULL,"No enough memory!","Temporary File Save",MB_ICONSTOP|MB_OK);//Display Info
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
            memcpy(m_cImageBytes,pDoc->m_StandardBmpInfo,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_cImageBytes+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  if(_write(fh,m_cImageBytes,bitfile->bfSize)!=(int)bitfile->bfSize)
		  {
			//MessageBox(NULL,"File save error","Error!", MB_ICONSTOP|MB_OK);
			_close(fh);
			GlobalFree(Imagehg);
            jpg.close();
			return -2;
		  }
		  _close(fh);
		  GlobalFree(Imagehg);
		  jpg.close();
	}
	RetrievalImage=(HBITMAP)::LoadImage(NULL,temp,IMAGE_BITMAP,displayWidth,displayHeight,\
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
	switch(num)
	{
		  case 1:
			m_RetrievalImage1.SetBitmap(RetrievalImage);
			//((CButton *)GetDlgItem(IDC_BUTTON_RETRIEVAL1))->SetBitmap(RetrievalImage);
		  break;
		  case 2:
			m_RetrievalImage2.SetBitmap(RetrievalImage);
		  break;
		  case 3:
			m_RetrievalImage3.SetBitmap(RetrievalImage);
		  break;
		  case 4:
			m_RetrievalImage4.SetBitmap(RetrievalImage);
		  break;
		  case 5:
			m_RetrievalImage5.SetBitmap(RetrievalImage);
		  break;
		  case 6:
			m_RetrievalImage6.SetBitmap(RetrievalImage);
		  break;
		  case 7:
			m_RetrievalImage7.SetBitmap(RetrievalImage);
		  break;
		  case 8:
			m_RetrievalImage8.SetBitmap(RetrievalImage);
		  break;
		  case 9:
			m_RetrievalImage9.SetBitmap(RetrievalImage);
		  break;
		  case 10:
			m_RetrievalImage10.SetBitmap(RetrievalImage);
		  break;
		  case 11:
			m_RetrievalImage11.SetBitmap(RetrievalImage);
		  break;
		  case 12:
			m_RetrievalImage12.SetBitmap(RetrievalImage);
		  break;
		  case 13:
			m_RetrievalImage13.SetBitmap(RetrievalImage);
		  break;
		  case 14:
			m_RetrievalImage14.SetBitmap(RetrievalImage);
		  break;
		  case 15:
			m_RetrievalImage15.SetBitmap(RetrievalImage);
		  break;
		  case 16:
			m_RetrievalImage16.SetBitmap(RetrievalImage);
		  break;
		  default:
		  break;
	}
	::DeleteObject(RetrievalImage);
	return 0;
}

//Print The query
void CVqRetrieveView::PrintQuery(CDC* pDC, CPrintInfo* pInfo)
{
	  CVqRetrieveDoc *pDoc = GetDocument();
	  ASSERT_VALID(pDoc);
      double a,b;//The ratio for width and height
	  int left,top,width,height;//The variables for print position
 	  POINT point;//The position for display information
	  CString Title;
	  Title="Query Image: ";
	  Title+=pDoc->m_vQueryFeatureVector.m_sOriginalFileName;//Get the document title
  	  ////Get the ratio in width and height directions
	  a=(double)pInfo->m_rectDraw.right/5.0*4.0;
	  a=a/(double)pDoc->m_vQueryFeatureVector.m_lImageWidth;
	  b=(double)pInfo->m_rectDraw.bottom/40.0*17.0;
	  b=b/(double)pDoc->m_vQueryFeatureVector.m_lImageHeight;
	  if(a>b)a=b;//Select the smaller one as the common ratio
 	  ////Calculate the position and size for printing the original image
	  left=(int)((double)pInfo->m_rectDraw.right/2.0)-(int)(a/2.0*(double)pDoc->m_vQueryFeatureVector.m_lImageWidth);
	  top=pInfo->m_rectDraw.bottom/20;
	  width=(int)(a*(double)pDoc->m_vQueryFeatureVector.m_lImageWidth);
	  height=(int)(a*(double)pDoc->m_vQueryFeatureVector.m_lImageHeight);
	  ////Compute the position to display the information of the original image
	  point.x=left;
	  point.y=top-200;
	  pDC->TextOut(point.x,point.y,Title);//Print the information for original image
	  ////Print the original image
	  if(pDoc->m_vQueryFeatureVector.m_bBitCount==8)
	    ::StretchDIBits(pDC->m_hDC,left,top,width,height,0,0,pDoc->m_vQueryFeatureVector.m_lImageWidth,pDoc->m_vQueryFeatureVector.m_lImageHeight,pDoc->m_QueryImageFile+1078,(BITMAPINFO *)(pDoc->m_QueryImageFile+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	  else
	    ::StretchDIBits(pDC->m_hDC,left,top,width,height,0,0,pDoc->m_vQueryFeatureVector.m_lImageWidth,pDoc->m_vQueryFeatureVector.m_lImageHeight,pDoc->m_QueryImageFile+54,(BITMAPINFO *)(pDoc->m_QueryImageFile+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
}
//Print The retrieval results
void CVqRetrieveView::PrintRetrieval(CDC* pDC, CPrintInfo* pInfo,int upordown)
{
	CVqRetrieveDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	

}

void CVqRetrieveView::FeatureComputingRelatedWindowShow(int nCmdShow)
{
      m_QueryImage.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_QUERY)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_QUERYREGION)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DATABASEREGION)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_RETRIEVALREGION)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_RESULTREGION)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_QUERYINFO)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_RESULTREGION)->ShowWindow(nCmdShow);
	  m_RetrievalImage1.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL1)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME1)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS1)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS1)->ShowWindow(nCmdShow);
	  m_RetrievalImage2.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL2)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME2)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS2)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS2)->ShowWindow(nCmdShow);
	  m_RetrievalImage3.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL3)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME3)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS3)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS3)->ShowWindow(nCmdShow);
	  m_RetrievalImage4.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL4)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME4)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS4)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS4)->ShowWindow(nCmdShow);
	  m_RetrievalImage5.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL5)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME5)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS5)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS5)->ShowWindow(nCmdShow);
	  m_RetrievalImage6.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL6)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME6)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS6)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS6)->ShowWindow(nCmdShow);
	  m_RetrievalImage7.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL7)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME7)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS7)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS7)->ShowWindow(nCmdShow);
	  m_RetrievalImage8.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL8)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME8)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS8)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS8)->ShowWindow(nCmdShow);
	  m_RetrievalImage9.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL9)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME9)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS9)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS9)->ShowWindow(nCmdShow);
	  m_RetrievalImage10.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL10)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME10)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS10)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS10)->ShowWindow(nCmdShow);
	  m_RetrievalImage11.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL11)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME11)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS11)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS11)->ShowWindow(nCmdShow);
	  m_RetrievalImage12.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL12)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME12)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS12)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS12)->ShowWindow(nCmdShow);
	  m_RetrievalImage13.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL13)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME13)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS13)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS13)->ShowWindow(nCmdShow);
	  m_RetrievalImage14.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL14)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME14)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS14)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS14)->ShowWindow(nCmdShow);
	  m_RetrievalImage15.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL15)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME15)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS15)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS15)->ShowWindow(nCmdShow);
	  m_RetrievalImage16.ShowWindow(nCmdShow);
	  GetDlgItem(IDC_REGION_RETRIEVAL16)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME16)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DIS16)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DIS16)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB2)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB3)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB5)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB6)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB7)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB8)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB9)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB10)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB11)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB12)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB13)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB14)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB15)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB16)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB17)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB18)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB19)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB20)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB21)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_STATIC_DB22)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB2)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB3)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB5)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB6)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB7)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB8)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB9)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB10)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB11)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB12)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB13)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB14)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB15)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB16)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB17)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB18)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB19)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB20)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB21)->ShowWindow(nCmdShow);
	  GetDlgItem(IDC_EDIT_DB22)->ShowWindow(nCmdShow);
}

void CVqRetrieveView::MoveToPositions()
{
      m_QueryImage.MoveWindow(20,20,300,175);
	  GetDlgItem(IDC_REGION_QUERY)->MoveWindow(20,14,300,181);
	  GetDlgItem(IDC_STATIC_QUERYREGION)->MoveWindow(10,0,320,260);
	  GetDlgItem(IDC_STATIC_DATABASEREGION)->MoveWindow(340,0,320,260);
	  GetDlgItem(IDC_STATIC_RETRIEVALREGION)->MoveWindow(670,0,320,260);
	  GetDlgItem(IDC_STATIC_RESULTREGION)->MoveWindow(10,260,980,395);
	  GetDlgItem(IDC_EDIT_QUERYINFO)->MoveWindow(20,195,300,60);
	  m_RetrievalImage1.MoveWindow(15+0*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL1)->MoveWindow(15+0*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME1)->MoveWindow(15+0*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS1)->MoveWindow(15+0*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS1)->MoveWindow(15+0*121+40,128+1*180+145,80,25);
	  m_RetrievalImage2.MoveWindow(15+1*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL2)->MoveWindow(15+1*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME2)->MoveWindow(15+1*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS2)->MoveWindow(15+1*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS2)->MoveWindow(15+1*121+40,128+1*180+145,80,25);
	  m_RetrievalImage3.MoveWindow(15+2*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL3)->MoveWindow(15+2*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME3)->MoveWindow(15+2*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS3)->MoveWindow(15+2*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS3)->MoveWindow(15+2*121+40,128+1*180+145,80,25);
	  m_RetrievalImage4.MoveWindow(15+3*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL4)->MoveWindow(15+3*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME4)->MoveWindow(15+3*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS4)->MoveWindow(15+3*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS4)->MoveWindow(15+3*121+40,128+1*180+145,80,25);
	  m_RetrievalImage5.MoveWindow(15+4*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL5)->MoveWindow(15+4*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME5)->MoveWindow(15+4*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS5)->MoveWindow(15+4*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS5)->MoveWindow(15+4*121+40,128+1*180+145,80,25);
	  m_RetrievalImage6.MoveWindow(15+5*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL6)->MoveWindow(15+5*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME6)->MoveWindow(15+5*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS6)->MoveWindow(15+5*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS6)->MoveWindow(15+5*121+40,128+1*180+145,80,25);
	  m_RetrievalImage7.MoveWindow(15+6*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL7)->MoveWindow(15+6*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME7)->MoveWindow(15+6*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS7)->MoveWindow(15+6*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS7)->MoveWindow(15+6*121+40,128+1*180+145,80,25);
	  m_RetrievalImage8.MoveWindow(15+7*121,128+1*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL8)->MoveWindow(15+7*121,122+1*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME8)->MoveWindow(15+7*121,128+1*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS8)->MoveWindow(15+7*121,128+1*180+147,40,25);
	  GetDlgItem(IDC_EDIT_DIS8)->MoveWindow(15+7*121+40,128+1*180+145,80,25);
	  m_RetrievalImage9.MoveWindow(15+0*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL9)->MoveWindow(15+0*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME9)->MoveWindow(15+0*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS9)->MoveWindow(15+0*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS9)->MoveWindow(15+0*121+48,120+2*180+145,72,25);
	  m_RetrievalImage10.MoveWindow(15+1*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL10)->MoveWindow(15+1*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME10)->MoveWindow(15+1*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS10)->MoveWindow(15+1*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS10)->MoveWindow(15+1*121+48,120+2*180+145,72,25);
	  m_RetrievalImage11.MoveWindow(15+2*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL11)->MoveWindow(15+2*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME11)->MoveWindow(15+2*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS11)->MoveWindow(15+2*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS11)->MoveWindow(15+2*121+48,120+2*180+145,72,25);
	  m_RetrievalImage12.MoveWindow(15+3*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL12)->MoveWindow(15+3*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME12)->MoveWindow(15+3*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS12)->MoveWindow(15+3*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS12)->MoveWindow(15+3*121+48,120+2*180+145,72,25);
	  m_RetrievalImage13.MoveWindow(15+4*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL13)->MoveWindow(15+4*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME13)->MoveWindow(15+4*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS13)->MoveWindow(15+4*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS13)->MoveWindow(15+4*121+48,120+2*180+145,72,25);
	  m_RetrievalImage14.MoveWindow(15+5*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL14)->MoveWindow(15+5*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME14)->MoveWindow(15+5*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS14)->MoveWindow(15+5*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS14)->MoveWindow(15+5*121+48,120+2*180+145,72,25);
	  m_RetrievalImage15.MoveWindow(15+6*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL15)->MoveWindow(15+6*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME15)->MoveWindow(15+6*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS15)->MoveWindow(15+6*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS15)->MoveWindow(15+6*121+48,120+2*180+145,72,25);
	  m_RetrievalImage16.MoveWindow(15+7*121,120+2*180,120,120);
	  GetDlgItem(IDC_REGION_RETRIEVAL16)->MoveWindow(15+7*121,114+2*180,120,126);
	  GetDlgItem(IDC_EDIT_RETRIEVALNAME16)->MoveWindow(15+7*121,120+2*180+120,120,25);
	  GetDlgItem(IDC_STATIC_DIS16)->MoveWindow(15+7*121,120+2*180+150,48,25);
	  GetDlgItem(IDC_EDIT_DIS16)->MoveWindow(15+7*121+48,120+2*180+145,72,25);
	  GetDlgItem(IDC_STATIC_DB)->MoveWindow(350,20,150,25);
	  GetDlgItem(IDC_STATIC_DB2)->MoveWindow(350,46,180,25);
	  GetDlgItem(IDC_STATIC_DB3)->MoveWindow(350,72,180,25);
	  GetDlgItem(IDC_STATIC_DB4)->MoveWindow(350,98,180,25);
	  GetDlgItem(IDC_STATIC_DB5)->MoveWindow(350,124,180,25);
	  GetDlgItem(IDC_STATIC_DB6)->MoveWindow(350,150,180,25);
	  GetDlgItem(IDC_STATIC_DB7)->MoveWindow(350,176,180,25);
	  GetDlgItem(IDC_STATIC_DB8)->MoveWindow(350,202,180,25);
	  GetDlgItem(IDC_STATIC_DB9)->MoveWindow(350,228,180,25);
	  GetDlgItem(IDC_EDIT_DB)->MoveWindow(500,20,150,25);
	  GetDlgItem(IDC_EDIT_DB2)->MoveWindow(530,47,120,25);
	  GetDlgItem(IDC_EDIT_DB3)->MoveWindow(530,72,120,25);
	  GetDlgItem(IDC_EDIT_DB4)->MoveWindow(530,98,120,25);
	  GetDlgItem(IDC_EDIT_DB5)->MoveWindow(530,124,120,25);
	  GetDlgItem(IDC_EDIT_DB6)->MoveWindow(530,150,120,25);
	  GetDlgItem(IDC_EDIT_DB7)->MoveWindow(530,176,120,25);
	  GetDlgItem(IDC_EDIT_DB8)->MoveWindow(530,202,120,25);
	  GetDlgItem(IDC_EDIT_DB9)->MoveWindow(530,228,120,25);
	  GetDlgItem(IDC_STATIC_DB10)->MoveWindow(680,20,150,25);
	  GetDlgItem(IDC_STATIC_DB11)->MoveWindow(680,46,180,25);
	  GetDlgItem(IDC_STATIC_DB12)->MoveWindow(680,72,180,25);
	  GetDlgItem(IDC_STATIC_DB13)->MoveWindow(680,98,180,25);
	  GetDlgItem(IDC_STATIC_DB14)->MoveWindow(680,124,180,25);
	  GetDlgItem(IDC_STATIC_DB15)->MoveWindow(680,150,180,25);
	  GetDlgItem(IDC_STATIC_DB16)->MoveWindow(680,176,180,25);
	  GetDlgItem(IDC_STATIC_DB17)->MoveWindow(680,202,180,25);
	  GetDlgItem(IDC_STATIC_DB18)->MoveWindow(680,228,180,25);
	  GetDlgItem(IDC_EDIT_DB10)->MoveWindow(830,20,150,25);
	  GetDlgItem(IDC_EDIT_DB11)->MoveWindow(860,47,120,25);
	  GetDlgItem(IDC_EDIT_DB12)->MoveWindow(860,72,120,25);
	  GetDlgItem(IDC_EDIT_DB13)->MoveWindow(860,98,120,25);
	  GetDlgItem(IDC_EDIT_DB14)->MoveWindow(860,124,120,25);
	  GetDlgItem(IDC_EDIT_DB15)->MoveWindow(860,150,120,25);
	  GetDlgItem(IDC_EDIT_DB16)->MoveWindow(860,176,120,25);
	  GetDlgItem(IDC_EDIT_DB17)->MoveWindow(860,202,120,25);
	  GetDlgItem(IDC_EDIT_DB18)->MoveWindow(860,228,120,25);
	  GetDlgItem(IDC_STATIC_DB19)->MoveWindow(20,98+1*180,100,25);
	  GetDlgItem(IDC_EDIT_DB19)->MoveWindow(120,98+1*180,80,25);
	  GetDlgItem(IDC_STATIC_DB20)->MoveWindow(200,98+1*180,100,25);
	  GetDlgItem(IDC_EDIT_DB20)->MoveWindow(300,98+1*180,150,25);
	  GetDlgItem(IDC_STATIC_DB21)->MoveWindow(450,98+1*180,100,25);
	  GetDlgItem(IDC_EDIT_DB21)->MoveWindow(550,98+1*180,150,25);
	  GetDlgItem(IDC_STATIC_DB22)->MoveWindow(700,98+1*180,80,25);
	  GetDlgItem(IDC_EDIT_DB22)->MoveWindow(780,98+1*180,200,25);
	  

}

///Return the suitable dispaly width
int CVqRetrieveView::SuitableWidth(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
   return (int)(Width*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}

///Return the suitable dispaly height
int CVqRetrieveView::SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
  return (int)(Heigth*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}

void CVqRetrieveView::OnKillfocusEditDb6() 
{
	// TODO: Add your control notification handler code here
    CVqRetrieveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData(true);
	if(m_clusters<5)m_clusters=5;
	if(m_clusters>1024)m_clusters=1024;
	pDoc->m_clusters=m_clusters;
	UpdateData(false);
}

void CVqRetrieveView::DisplayInitialParameters()
{
	CVqRetrieveDoc* pDoc = GetDocument();//Get pDoc
	ASSERT_VALID(pDoc);//Make pDoc valid
	//For query image
	m_QueryImage.SetBitmap(NULL);
	m_queryinfo="No query image opened!";
	
	//The database parameters
	m_totalnum=pDoc->m_totalnum;
	m_validnum=pDoc->m_validnum;
	m_extractednum=pDoc->m_extractednum;
	m_normalizednum=pDoc->m_normalizednum;
	m_clusters=pDoc->m_clusters;
	m_savedfeaturefile=pDoc->m_savedfeaturefile;
	m_savedcodebookfile=pDoc->m_savedcodebookfile;
	m_savedvqfeaturefile=pDoc->m_savedvqfeaturefile;
    m_db=pDoc->m_sDatabasePath;///Database Directory

	//The retrieval parameters
    m_db10=pDoc->m_sRetrievePath;//Retrieval Directory
	m_vectornumber=pDoc->m_validnum_r;
	m_everinterrupted=pDoc->m_everinterrupted;
	m_readfeaturename=pDoc->m_readfeaturename;
	m_readbookname=pDoc->m_readbookname;
	m_featuredimension=pDoc->m_featuredimension;
	m_basedonnormalized=pDoc->m_basedonnormalized;
	m_clustersused=pDoc->m_clustersused;
	m_retrievednum=pDoc->m_retrievednum;

	//The result initial parameters
    m_bFileLost=false;  //Default: No image is lost
	m_page=0;  //None page
	m_otherinfo=""; //none info
	m_feedbackinfo="";
	m_status="";// none status
    m_RetrievalImage1.SetBitmap(NULL);
    m_retrievalname1="None!";
	m_RetrievalImage2.SetBitmap(NULL);
	m_retrievalname2="None!";
	m_RetrievalImage3.SetBitmap(NULL);
	m_retrievalname3="None!";
	m_RetrievalImage4.SetBitmap(NULL);
	m_retrievalname4="None!";
	m_RetrievalImage5.SetBitmap(NULL);
	m_retrievalname5="None!";
	m_RetrievalImage6.SetBitmap(NULL);
	m_retrievalname6="None!";
	m_RetrievalImage7.SetBitmap(NULL);
	m_retrievalname7="None!";
	m_RetrievalImage8.SetBitmap(NULL);
	m_retrievalname8="None!";
	m_RetrievalImage9.SetBitmap(NULL);
	m_retrievalname9="None!";
	m_RetrievalImage10.SetBitmap(NULL);
	m_retrievalname10="None!";
	m_RetrievalImage11.SetBitmap(NULL);
	m_retrievalname11="None!";
	m_RetrievalImage12.SetBitmap(NULL);
	m_retrievalname12="None!";
	m_RetrievalImage13.SetBitmap(NULL);
	m_retrievalname13="None!";
	m_RetrievalImage14.SetBitmap(NULL);
	m_retrievalname14="None!";
	m_RetrievalImage15.SetBitmap(NULL);
	m_retrievalname15="None!";
	m_RetrievalImage16.SetBitmap(NULL);
	m_retrievalname16="None!";
	m_dis1=-1;
    m_dis2=-1;
	m_dis3=-1;
	m_dis4=-1;
	m_dis5=-1;
	m_dis6=-1;
	m_dis7=-1;
	m_dis8=-1;
    m_dis9=-1;
	m_dis10=-1;
	m_dis11=-1;
	m_dis12=-1;
	m_dis13=-1;
	m_dis14=-1;
	m_dis15=-1;
	m_dis16=-1;	
}

