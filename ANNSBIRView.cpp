// ANNSBIRView.cpp : implementation of the CANNSBIRView class
//

#include "stdafx.h"
#include "ANNSBIR.h"

#include "ANNSBIRDoc.h"
#include "ANNSBIRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRView

IMPLEMENT_DYNCREATE(CANNSBIRView, CFormView)

BEGIN_MESSAGE_MAP(CANNSBIRView, CFormView)
	//{{AFX_MSG_MAP(CANNSBIRView)
	ON_BN_CLICKED(IDC_OPENSAMPLE, OnOpenSample)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRView construction/destruction

CANNSBIRView::CANNSBIRView()
	: CFormView(CANNSBIRView::IDD)
{
	//{{AFX_DATA_INIT(CANNSBIRView)
	m_retrievalname1 = _T("");
	m_retrievalname10 = _T("");
	m_retrievalname11 = _T("");
	m_retrievalname12 = _T("");
	m_retrievalname13 = _T("");
	m_retrievalname14 = _T("");

	m_retrievalname2 = _T("");
	m_retrievalname3 = _T("");
	m_retrievalname4 = _T("");
	m_retrievalname5 = _T("");
	m_retrievalname6 = _T("");
	m_retrievalname7 = _T("");
	m_retrievalname8 = _T("");
	m_retrievalname9 = _T("");

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
	m_savedvqfeaturefile = _T("");	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CANNSBIRView::~CANNSBIRView()
{
}

void CANNSBIRView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVqRetrieveView)
	DDX_Control(pDX, ID_SAMPLE, m_cSampleImage);
	DDX_Text(pDX, IDC_EDIT_SAMPLE, m_queryinfo);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME1, m_retrievalname1);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME10, m_retrievalname10);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME11, m_retrievalname11);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME12, m_retrievalname12);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME13, m_retrievalname13);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME14, m_retrievalname14);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME2, m_retrievalname2);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME3, m_retrievalname3);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME4, m_retrievalname4);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME5, m_retrievalname5);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME6, m_retrievalname6);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME7, m_retrievalname7);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME8, m_retrievalname8);
	DDX_Text(pDX, IDC_EDIT_RETRIEVALNAME9, m_retrievalname9);
	DDX_Control(pDX, IDC_STATICRETRIEVAL9, m_RetrievalImage9);
	DDX_Control(pDX, IDC_STATICRETRIEVAL8, m_RetrievalImage8);
	DDX_Control(pDX, IDC_STATICRETRIEVAL7, m_RetrievalImage7);
	DDX_Control(pDX, IDC_STATICRETRIEVAL6, m_RetrievalImage6);
	DDX_Control(pDX, IDC_STATICRETRIEVAL5, m_RetrievalImage5);
	DDX_Control(pDX, IDC_STATICRETRIEVAL4, m_RetrievalImage4);
	DDX_Control(pDX, IDC_STATICRETRIEVAL3, m_RetrievalImage3);
	DDX_Control(pDX, IDC_STATICRETRIEVAL2, m_RetrievalImage2);
	DDX_Control(pDX, IDC_STATICRETRIEVAL14, m_RetrievalImage14);
	DDX_Control(pDX, IDC_STATICRETRIEVAL13, m_RetrievalImage13);
	DDX_Control(pDX, IDC_STATICRETRIEVAL12, m_RetrievalImage12);
	DDX_Control(pDX, IDC_STATICRETRIEVAL11, m_RetrievalImage11);
	DDX_Control(pDX, IDC_STATICRETRIEVAL10, m_RetrievalImage10);
	DDX_Control(pDX, IDC_STATICRETRIEVAL1, m_RetrievalImage1);
	//{{AFX_DATA_MAP(CANNSBIRView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CANNSBIRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CANNSBIRView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRView printing

BOOL CANNSBIRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CANNSBIRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CANNSBIRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CANNSBIRView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRView diagnostics

#ifdef _DEBUG
void CANNSBIRView::AssertValid() const
{
	CFormView::AssertValid();
}

void CANNSBIRView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CANNSBIRDoc* CANNSBIRView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CANNSBIRDoc)));
	return (CANNSBIRDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRView message handlers



void CANNSBIRView::OnOpenSample() 
{
	// TODO: Add your control notification handler code here
	CANNSBIRDoc *pDoc;
	pDoc=(CANNSBIRDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	
	ifopen=false;

	char BASED_CODE szFilter[]="";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
    
	if(m_ldFile.DoModal()!=IDOK)
		return;
	else 
	{
       	m_SampleImagePath=m_ldFile.GetPathName();
		//load for display
		if(!this->m_cSampleImage.LoadImage(m_SampleImagePath))
		{
			AfxMessageBox("Sample Image Error",MB_OK);
			return;
		}
	  
		m_cSampleImage.SetBitmap(NULL);
	    pDoc->UpdateAllViews(NULL);
		
		if(m_pict.Load((LPCTSTR)m_SampleImagePath)==NULL)
		{
		  	AfxMessageBox("Sample Image Error",MB_OK);
			return;
		}
		//get the file name 
		if(ReadQueryImage(m_SampleImagePath,&m_vQueryFeatureVector)==0)
		{
		  ifopen=true;
		  m_PrintImagePath=m_SampleImagePath;
		}
	}
	
}
int CANNSBIRView::ReadQueryImage(CString ImagePathName, PFEATUREVECTOR FeatureVector)
{
  return 0;
}
