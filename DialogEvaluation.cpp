// DialogEvaluation.cpp : implementation file
//

#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogEvaluation.h"

#include <io.h> 
#include <fcntl.h>
#include  <sys/types.h>
#include  <sys/stat.h> 
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int oldquery;
CString lastpathname1;
CString lastpathname2;
static WORD QUERYEACHCLASS[10]={1,2,5,10,20,50,100,200,250,400};
static WORD MINRETURN[15]={1,2,3,4,5,6,7,8,9,10,12,15,16,18,20};
static WORD MAXRETURN[29]={10,16,20,30,32,40,48,50,60,64,70,80,90,96,100,192,200,288,300,400,496,500,592,600,688,700,800,992,1000};
static WORD STEP[21]={1,2,3,4,5,6,7,8,9,10,12,15,16,18,20,32,40,50,64,80,100};
static WORD CLUSTERS[27]={1,2,3,4,5,6,7,8,9,10,16,20,32,40,50,64,80,100,128,200,250,256,400,500,800,1000,1024};


/////////////////////////////////////////////////////////////////////////////
// CDialogEvaluation dialog


CDialogEvaluation::CDialogEvaluation(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogEvaluation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogEvaluation)
	m_dbpath = _T("");
	m_bSorted = _T("");
	m_everinterrupted = _T("");
	m_validnum_r = 0;
	m_featuredimension = 0;
	m_clustered = _T("");
	m_clustersused = 0;
	m_standard = _T("");
	m_numineachclass = 0;
	m_classes = 0;
	m_dim1 = 0;
	m_dim2 = 0;
	m_dim3 = 0;
	m_dim4 = 0;
	m_dim5 = 0;
	m_bkpath = _T("");
	m_infonum = _T("");
	m_max = -1;
	m_method = -1;
	m_min = -1;
	m_cluster = -1;
	m_query = -1;
	m_step = -1;
	m_testinfo = _T("");
	//}}AFX_DATA_INIT
}


void CDialogEvaluation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogEvaluation)
	DDX_Control(pDX, IDC_RESULT_LIST, m_resultlist);
	DDX_Text(pDX, IDC_DBPATH, m_dbpath);
	DDX_Text(pDX, IDC_EDIT_SORTED, m_bSorted);
	DDX_Text(pDX, IDC_EDIT_IMAGENUMBER, m_validnum_r);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONTOTAL, m_featuredimension);
	DDX_Text(pDX, IDC_EDIT_CLUSTERED, m_clustered);
	DDX_Text(pDX, IDC_EDIT_CLUSTERS, m_clustersused);
	DDX_Text(pDX, IDC_EDIT_STANDARD, m_standard);
	DDX_Text(pDX, IDC_EDIT_IMAGEEACHCLASS, m_numineachclass);
	DDX_Text(pDX, IDC_EDIT_CLASSES, m_classes);
	DDX_Text(pDX, IDC_EDIT_DIMENSION1, m_dim1);
	DDX_Text(pDX, IDC_EDIT_DIMENSION2, m_dim2);
	DDX_Text(pDX, IDC_EDIT_DIMENSION3, m_dim3);
	DDX_Text(pDX, IDC_EDIT_DIMENSION4, m_dim4);
	DDX_Text(pDX, IDC_EDIT_DIMENSION5, m_dim5);
	DDX_Text(pDX, IDC_BKPATH, m_bkpath);
	DDX_Text(pDX, IDC_NUMINCLUSTER, m_infonum);
	DDX_CBIndex(pDX, IDC_MAX, m_max);
	DDX_CBIndex(pDX, IDC_METHOD, m_method);
	DDX_CBIndex(pDX, IDC_MIN, m_min);
	DDX_CBIndex(pDX, IDC_NUMCLUSTERTOSEARCH, m_cluster);
	DDX_CBIndex(pDX, IDC_QUERIES, m_query);
	DDX_CBIndex(pDX, IDC_STEP, m_step);
	DDX_Text(pDX, IDC_TESTINFODISPLAY, m_testinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogEvaluation, CDialog)
	//{{AFX_MSG_MAP(CDialogEvaluation)
	ON_BN_CLICKED(IDC_OPEN_DATABASE, OnOpenDatabase)
	ON_BN_CLICKED(IDC_OPEN_CODEBOOK, OnOpenCodebook)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_RESULTSAVE, OnResultsave)
	ON_BN_CLICKED(IDC_STARTTEST, OnStarttest)
	ON_BN_CLICKED(IDC_RANDOMQUERY, OnRandomquery)
	ON_BN_CLICKED(IDC_DRAWPR, OnDrawpr)
	ON_BN_CLICKED(IDC_DRAWTIME, OnDrawtime)
	ON_CBN_SELCHANGE(IDC_QUERIES, OnSelchangeQueries)
	ON_CBN_SELCHANGE(IDC_METHOD, OnSelchangeMethod)
	ON_CBN_SELCHANGE(IDC_MAX, OnSelchangeMax)
	ON_CBN_SELCHANGE(IDC_MIN, OnSelchangeMin)
	ON_CBN_SELCHANGE(IDC_NUMCLUSTERTOSEARCH, OnSelchangeNumclustertosearch)
	ON_CBN_SELCHANGE(IDC_STEP, OnSelchangeStep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEvaluation message handlers
void CDialogEvaluation::OpenFeatureDatabasefile(CString DataBaseFileName) 
{
	// TODO: Add your command handler code here
	DWORD a;
	long int i;
	CFile fdbfile;
	CFileException cfe;
	CString str;
	databaseSize=0;
	featureDimension=0;
	m_bFeatureFileOpened=false;
	if(!fdbfile.Open(DataBaseFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox("Cannot Open the database file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_ffi_fromfile
    if(fdbfile.Read(&m_ffi_fromfile,sizeof(FEATUREFILEINFO))!=sizeof(FEATUREFILEINFO))
	{
	   MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	if(m_ffi_fromfile.m_wTotalDimensions<=0||m_ffi_fromfile.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_ffi_fromfile.m_wStructSize!=sizeof(FEATUREFILEINFO)||m_ffi_fromfile.m_wOffBytes!=600\
	||strcmp(m_ffi_fromfile.m_sThisFileNameLast8,DataBaseFileName.Right(7))!=0\
    ||m_ffi_fromfile.m_bFeatureTypes<1||m_ffi_fromfile.m_bFeatureTypes>7\
	||m_ffi_fromfile.m_dwFileNumber<1||m_ffi_fromfile.m_dwFileNumber>MAX_IMAGE_NUMBER)
	{
	  fdbfile.Close();
	  MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	databaseSize=m_ffi_fromfile.m_dwFileNumber;
	featureDimension=m_ffi_fromfile.m_wTotalDimensions;
	a=(sizeof(FEATUREVECTOR)+2*sizeof(double)*featureDimension)*databaseSize+600+sizeof(COMPONENTINFO)*featureDimension;
    if(a!=fdbfile.GetLength()||m_ffi_fromfile.m_dwFileSize!=a)
	{
	  fdbfile.Close();
	  MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	//apply memory
    m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,databaseSize*featureDimension*sizeof(double)+databaseSize*2*sizeof(double));
	if(m_hRFeatureVector==NULL)
	{
        MessageBox("Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return;
	}
	///The address of database
	database=(double *)m_hRFeatureVector;
	means=database+databaseSize*featureDimension;
	variances=means+databaseSize;
	for(i=0;i<(long int)databaseSize;i++)
	{
		fdbfile.Seek(600+(i+1)*sizeof(FEATUREVECTOR)-4*sizeof(double),CFile::begin);
		if(fdbfile.Read(means+i,sizeof(double))!=sizeof(double))
		{
	      MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	      return;
		}
		if(fdbfile.Read(variances+i,sizeof(double))!=sizeof(double))
		{
	      MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	      return;
		}
	}
	fdbfile.Seek(600+sizeof(FEATUREVECTOR)*databaseSize+databaseSize*featureDimension*sizeof(double),CFile::begin);
	//Read the detail Featurevectors
	if(fdbfile.Read(database,sizeof(double)*databaseSize*featureDimension)!=sizeof(double)*databaseSize*featureDimension)
	{
	    MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	    return;
	}
	fdbfile.Close();
	m_bFeatureFileOpened=true;
}

void CDialogEvaluation::OnOpenDatabase() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your command handler code here
	DWORD a;
	long int i;
	CFile featurefile;
	CFileException cfe;
	CString FeatureFileName,str;
	m_dbpath="none";
	char BASED_CODE szFilter1[]="Feature DataBase Files(*.fdb)|*.fdb|VQ Feature DataBase Files(*.vqf)|*.vqf|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open Feature File";
	if(m_ldFile.DoModal()!=IDOK)return;
	FeatureFileName=m_ldFile.GetPathName();
	if(m_bFeatureFileOpened==true&&lastpathname1==FeatureFileName)return;
	InitialStatus();
	if(!featurefile.Open(FeatureFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox("Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	//read the m_ffi_fromfile
    if(featurefile.Read(&m_ffi_fromfile,sizeof(FEATUREFILEINFO))!=sizeof(FEATUREFILEINFO))
	{
	   featurefile.Close();
	   MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	
	if(m_ffi_fromfile.m_wTotalDimensions<=0||m_ffi_fromfile.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION\
	||m_ffi_fromfile.m_wStructSize!=sizeof(FEATUREFILEINFO)||m_ffi_fromfile.m_wOffBytes!=600\
	||strcmp(m_ffi_fromfile.m_sThisFileNameLast8,FeatureFileName.Right(7))!=0\
    ||m_ffi_fromfile.m_bFeatureTypes<1||m_ffi_fromfile.m_bFeatureTypes>7\
	||m_ffi_fromfile.m_dwFileNumber<1||m_ffi_fromfile.m_dwFileNumber>MAX_IMAGE_NUMBER)
	{
	  featurefile.Close();
	  MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  InitialStatus();
	  return;
	}
	m_validnum_r=m_ffi_fromfile.m_dwFileNumber;
	if(m_ffi_fromfile.m_bClustered==FALSE)
	{
       a=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)*m_validnum_r+600+sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions;
       if(a!=featurefile.GetLength()||m_ffi_fromfile.m_dwFileSize!=a)
	   {
	     featurefile.Close();
         MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
		 InitialStatus();
	     return;
	   }
	   //apply memory
	   m_hRFeatureVector=NULL;
       m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,m_validnum_r*(sizeof(FEATUREVECTOR)+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double))+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double));
	   if(m_hRFeatureVector==NULL)
	   {
		  MessageBox("Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		  InitialStatus();
	      return;
	   }
	   ///The address of m_lpRFeatureVectors
 	   m_lpRFeatureVector=(LPFEATUREVECTOR)m_hRFeatureVector;
	   featurefile.Seek(600,CFile::begin);
	   //read the featurevectors
	   if(featurefile.Read(m_lpRFeatureVector,sizeof(FEATUREVECTOR)*m_validnum_r)!=sizeof(FEATUREVECTOR)*m_validnum_r)
	   {
	      MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
		  InitialStatus();
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
	      if(featurefile.Read(m_lpRFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
		  {
	         featurefile.Close();
			 MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
			 InitialStatus();
	         return;
		  }
	   }
	   for(i=0;i<m_validnum_r;i++)
	   {
	      if(featurefile.Read(m_lpRFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
		  {
	        featurefile.Close();
			MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
			InitialStatus();
	        return;
		  }
	   }
	   //Read the Component Info
	   if(featurefile.Read(m_lpRComponentInfo,sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)
	   {
	      featurefile.Close();
		  MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
		  InitialStatus();
	      return;
	   }
	}
	else
	{
       a=(sizeof(FEATUREVECTOR)+2*sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)*m_validnum_r+600+sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD);
       if(a!=featurefile.GetLength()||m_ffi_fromfile.m_dwFileSize!=a)
	   {
	     featurefile.Close();
         MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
		 InitialStatus();
		 return;
	   }
	   m_hRFeatureVector=GlobalAlloc(GMEM_FIXED,m_validnum_r*(sizeof(FEATUREVECTOR)+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double))+m_ffi_fromfile.m_wTotalDimensions*2*sizeof(double)+(m_ffi_fromfile.m_wTotalDimensions+2)*sizeof(double)*m_ffi_fromfile.m_wCodewordNumber+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD));
	   if(m_hRFeatureVector==NULL)
	   {
		   featurefile.Close();
		   MessageBox("Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		   InitialStatus();
		   return;
	   }
	   ///The address of m_lpRFeatureVectors
	   m_lpRFeatureVector=(LPFEATUREVECTOR)m_hRFeatureVector;
	   featurefile.Seek(600+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD),CFile::begin);
	   //read the featurevectors
	   if(featurefile.Read(m_lpRFeatureVector,sizeof(FEATUREVECTOR)*m_validnum_r)!=sizeof(FEATUREVECTOR)*m_validnum_r)
	   {
	      featurefile.Close();
		  MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
	      InitialStatus();
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
	    featurefile.Seek(600,CFile::begin);
        if(featurefile.Read(m_dwNuminEachCluster_r,m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD))!=m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD))
		{
	       featurefile.Close();
		   MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
		   InitialStatus();
	       return;
		}
	    featurefile.Seek(600+m_ffi_fromfile.m_wCodewordNumber*sizeof(DWORD)+sizeof(FEATUREVECTOR)*m_validnum_r,CFile::begin);
		//Read the detail Featurevectors
	    for(i=0;i<m_validnum_r;i++)
		{
	      if(featurefile.Read(m_lpRFeatureVector[i].m_dOriginalFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
		  {
	        featurefile.Close();
			MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
            InitialStatus();
	        return;
		  }
		}
	    for(i=0;i<m_validnum_r;i++)
		{
	       if(featurefile.Read(m_lpRFeatureVector[i].m_dNormalizedFeature,sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(double)*m_ffi_fromfile.m_wTotalDimensions)
		   {
	          featurefile.Close();
			  MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
			  InitialStatus();
	          return;
		   }
		}
	    //Read the Component Info
	    if(featurefile.Read(m_lpRComponentInfo,sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)!=sizeof(COMPONENTINFO)*m_ffi_fromfile.m_wTotalDimensions)
		{
	       featurefile.Close();
		   MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
		   InitialStatus();
	       return;
		}
	}
	featurefile.Close();
	lastpathname1=FeatureFileName;
	m_readfeaturename=m_ldFile.GetFileName();
    m_sRetrievePath=m_ffi_fromfile.m_sPath;
	m_featuredimension=m_ffi_fromfile.m_wTotalDimensions;
	m_bFeatureFileOpened=true;
	if(m_ffi_fromfile.m_bSorted==TRUE)
		m_bSorted="TRUE";
	else
		m_bSorted="FALSE";
	if(m_ffi_fromfile.m_bStandard==TRUE)
		m_standard="TRUE";
	else
	{
		m_standard="FALSE";
		MessageBox("The feature file is based on an nonstandard image database","Information",MB_ICONINFORMATION|MB_OK);
		m_bFeatureFileOpened=false;
	}
    if(m_ffi_fromfile.m_bClustered==TRUE)
		m_clustered="TRUE";
	else
		m_clustered="FALSE";
	m_dbpath=FeatureFileName;
	m_dim1=m_ffi_fromfile.m_wDimension_CF;
	m_dim2=m_ffi_fromfile.m_wDimension_IF;
	m_dim3=m_ffi_fromfile.m_wDimension_TF;
	m_dim4=m_ffi_fromfile.m_wDimension_SF;
	m_dim5=m_ffi_fromfile.m_wDimension_OF;
	m_numineachclass=m_ffi_fromfile.m_wImageInEachClass;//Each class image number
    m_classes=m_ffi_fromfile.m_wClasses;//Number of classes
	if(m_ffi_fromfile.m_bEverInterrupted==TRUE)
	{
	  MessageBox("The feature file is an interrupted file","Information",MB_ICONINFORMATION|MB_OK);
      m_bFeatureFileOpened=false;
	}
	memcpy(&m_trh.m_ffi,&m_ffi_fromfile,sizeof(FEATUREFILEINFO));
	m_trh.m_bMethodNum=0;
	if(m_bFeatureFileOpened==true)
	    EnableWindows(TRUE);
	else
	{
		UpdateData(FALSE);
		return;
	}
	if(m_ffi_fromfile.m_bClustered==FALSE)
	{
	  m_min=12;
	  for(i=0;i<29;i=i++)
	  {
	    //if(MAXRETURN[i]==(m_numineachclass/16)*16)break;
		if(MAXRETURN[i]>=m_numineachclass*m_classes)break;
	  }
	  m_max=i;
	  if(m_ffi_fromfile.m_bSorted==false)
	  {
		  m_method=0;
		  GetDlgItem(IDC_METHOD)->EnableWindow(FALSE);
	  }
	  else
	  {
	      m_method=1;
		  GetDlgItem(IDC_METHOD)->EnableWindow(TRUE);
	  }
	  m_query=2;
	  m_step=12;
	  m_cluster=-1;
	  
	}
	else
	{
		m_min=12;
	    for(i=0;i<29;i=i++)
		{
	      //if(MAXRETURN[i]==(m_numineachclass/16)*16)break;
		  if(MAXRETURN[i]>=m_numineachclass*m_classes)break;
		}
	    m_max=i;
	    m_method=0;
	    m_query=2;
	    m_step=12;
        m_cluster=-1;
		GetDlgItem( IDC_METHOD)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_NUMCLUSTERTOSEARCH)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

BOOL CDialogEvaluation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  MoveWindow(0,0,780,700);
  CenterWindow(NULL);
  
  GetDlgItem( IDC_STATIC_DATABASEFILE)->MoveWindow(5,5,480,235);
  GetDlgItem( IDC_OPEN_DATABASE)->MoveWindow(15,25,50,25);
  GetDlgItem( IDC_STATIC_TESTFEATUREFILE)->MoveWindow(90,25,120,25);
  GetDlgItem( IDC_DBPATH)->MoveWindow(230,25,250,25);
  GetDlgItem( IDC_STATIC_STANDARD)->MoveWindow(15,60,150,25);
  GetDlgItem( IDC_EDIT_STANDARD)->MoveWindow(170,60,70,25);
  GetDlgItem( IDC_STATIC_SORTED)->MoveWindow(250,60,150,25);
  GetDlgItem( IDC_EDIT_SORTED)->MoveWindow(410,60,70,25);
  GetDlgItem( IDC_STATIC_CLUSTERED)->MoveWindow(15,90,150,30);
  GetDlgItem( IDC_EDIT_CLUSTERED)->MoveWindow(170,90,70,25);
  GetDlgItem( IDC_STATIC_CLASSES)->MoveWindow(250,90,150,30);
  GetDlgItem( IDC_EDIT_CLASSES)->MoveWindow(410,90,70,25);
  GetDlgItem( IDC_STATIC_IMAGESINCLASS)->MoveWindow(15,120,150,25);
  GetDlgItem( IDC_EDIT_IMAGEEACHCLASS)->MoveWindow(170,120,70,25);
  GetDlgItem( IDC_STATIC_TOTALIMAGENUMBER)->MoveWindow(250,120,150,25);
  GetDlgItem( IDC_EDIT_IMAGENUMBER)->MoveWindow(410,120,70,25);
  GetDlgItem( IDC_STATIC_VECTORDIMENSION5)->MoveWindow(15,150,150,25);
  GetDlgItem( IDC_STATIC_VECTORDIMENSION)->MoveWindow(250,150,150,25);
  GetDlgItem( IDC_STATIC_VECTORDIMENSION1)->MoveWindow(15,180,160,25);
  GetDlgItem( IDC_STATIC_VECTORDIMENSION2)->MoveWindow(250,180,150,25);
  GetDlgItem( IDC_STATIC_VECTORDIMENSION3)->MoveWindow(15,210,150,25);
  GetDlgItem( IDC_STATIC_VECTORDIMENSION4)->MoveWindow(250,210,150,25);
  GetDlgItem( IDC_EDIT_DIMENSIONTOTAL)->MoveWindow(170,150,70,25);
  GetDlgItem( IDC_EDIT_DIMENSION1)->MoveWindow(410,150,70,25);
  GetDlgItem( IDC_EDIT_DIMENSION2)->MoveWindow(170,180,70,25);
  GetDlgItem( IDC_EDIT_DIMENSION3)->MoveWindow(410,180,70,25);
  GetDlgItem( IDC_EDIT_DIMENSION4)->MoveWindow(170,210,70,25);
  GetDlgItem( IDC_EDIT_DIMENSION5)->MoveWindow(410,210,70,25);

  GetDlgItem( IDC_STATIC_CODEBOOK)->MoveWindow(5,250,760,120);
  GetDlgItem( IDC_OPEN_CODEBOOK)->MoveWindow(15,275,50,25);
  GetDlgItem( IDC_STATIC_TESTCODEBOOK)->MoveWindow(90,275,140,25);
  GetDlgItem( IDC_BKPATH)->MoveWindow(240,275,240,25);
  GetDlgItem( IDC_STATIC_CLUSTERS)->MoveWindow(520,275,130,25);
  GetDlgItem( IDC_EDIT_CLUSTERS)->MoveWindow(650,275,70,25);
  GetDlgItem( IDC_STATIC_CLUSTERNUMBERS)->MoveWindow(15,320,180,25);
  GetDlgItem( IDC_NUMINCLUSTER)->MoveWindow(240,310,500,50);
  
  GetDlgItem( IDC_STATIC_TESTCONDITION)->MoveWindow(490,5,275,235);
  GetDlgItem( IDC_STATIC_METHOD)->MoveWindow(500,28,160,25);
  GetDlgItem( IDC_STATIC_QUERIES)->MoveWindow(500,66,180,25);
  GetDlgItem( IDC_STATIC_MINRETURN)->MoveWindow(500,99,160,25);
  GetDlgItem( IDC_STATIC_MAXRETURN)->MoveWindow(500,132,160,25);
  GetDlgItem( IDC_STATIC_STEP)->MoveWindow(500,165,160,25);
  GetDlgItem( IDC_STATIC_NUMCLUSTERSEARCH)->MoveWindow(500,198,160,25);
  GetDlgItem( IDC_METHOD)->MoveWindow(675,28,80,80);
  GetDlgItem( IDC_QUERIES)->MoveWindow(675,66,80,80);
  GetDlgItem( IDC_MIN)->MoveWindow(675,99,80,80);
  GetDlgItem( IDC_MAX)->MoveWindow(675,132,80,80);
  GetDlgItem( IDC_STEP)->MoveWindow(675,165,80,80);
  GetDlgItem( IDC_NUMCLUSTERTOSEARCH)->MoveWindow(675,198,80,80);

  GetDlgItem( IDC_STATIC_TESTING)->MoveWindow(5,380,760,230);
  GetDlgItem( IDC_RANDOMQUERY)->MoveWindow(15,395,180,25);
  GetDlgItem( IDC_STATIC_TESTINFO)->MoveWindow(320,395,200,25);
  GetDlgItem( IDC_TESTINFODISPLAY)->MoveWindow(200,415,500,40);
  GetDlgItem( IDC_STARTTEST)->MoveWindow(15,425,80,25);
  GetDlgItem( IDC_STATIC_RESULTDISPLAYSTYLE)->MoveWindow(15,455,380,25);
  GetDlgItem( IDC_RESULT_LIST)->MoveWindow(15,485,700,60);
  GetDlgItem( IDC_STATIC_RESULTDISPLAYSTYLE2)->MoveWindow(15,545,380,25);
  GetDlgItem( IDC_CLEAR)->MoveWindow(60,575,90,25);
  GetDlgItem( IDC_RESULTSAVE)->MoveWindow(260,575,90,25);
  GetDlgItem( IDC_DRAWPR)->MoveWindow(460,575,90,25);
  GetDlgItem( IDC_DRAWTIME)->MoveWindow(660,575,90,25);
  GetDlgItem( IDOK)->MoveWindow(400,623,90,25);

	InitialStatus();
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogEvaluation::InitialStatus()
{
    EnableWindows(FALSE);
	m_sRetrievePath="";

	m_clustered="Unknown";
	m_standard="Unknown";
	m_bSorted="Unknown";
	m_readfeaturename="No feature file opened";
	m_readbookname="No codebook file opened";
	m_dbpath="No feature file opened";
	m_bkpath="No book file opened";
	m_dim1=0;
	m_dim2=0;
	m_dim3=0;
	m_dim4=0;
	m_dim5=0;
	m_featuredimension=0;
	m_validnum_r=0;
	m_classes=0;
	m_numineachclass=0;
	m_bCodebookFileOpened=false;
	m_bFeatureFileOpened=false;
	m_clustersused=0;
	QueryGenerated=false;
	tested=false;
    m_infonum="";
	m_min=-1;
	m_max=-1;
	m_method=-1;
	m_query=-1;
	m_step=-1;
	m_cluster=-1;
	m_trh.m_bMethodNum=0;
	UpdateData(FALSE);
}

void CDialogEvaluation::OnCancel() 
{
	// TODO: Add extra cleanup here
	GlobalFree(m_hRFeatureVector);
	GlobalFree(m_hTestReports);
	CDialog::OnCancel();
}

void CDialogEvaluation::OnOK() 
{
	// TODO: Add extra validation here
	GlobalFree(m_hRFeatureVector);
	GlobalFree(m_hTestReports);
	CDialog::OnOK();
}

void CDialogEvaluation::OnOpenCodebook() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your command handler code here
	DWORD a;
	int i;
	CFile bokfile;
	CFileException cfe;
	CString CodebookFileName,str;
	if(m_bFeatureFileOpened==false||m_ffi_fromfile.m_bClustered==false)
	{
	  MessageBox("Please open a correct vqf file first","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	char BASED_CODE szFilter1[]="Codebook Files(*.bok)|*.bok|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_READONLY,szFilter1);
	m_ldFile.m_ofn.lpstrTitle="Open Codebook File";
	if(m_ldFile.DoModal()!=IDOK)return;
	CodebookFileName=m_ldFile.GetPathName();
	if(m_bFeatureFileOpened==true&&m_bCodebookFileOpened==true&&lastpathname2==CodebookFileName)return;

	//initialization
	m_bCodebookFileOpened=false;
	m_readbookname="No codebook file opened";
	lastpathname1="";
	lastpathname2="";
	m_clustersused=0;
	m_readbookname="No codebook file opened";
	m_bkpath="No book file opened";
	m_infonum="";
	QueryGenerated=false;
	tested=false;
	m_min=12;
    for(i=0;i<29;i=i++)
	{
      //if(MAXRETURN[i]==(m_numineachclass/16)*16)break;
	  if(MAXRETURN[i]>=m_numineachclass*m_classes)break;
	}
    m_max=i;
    m_method=0;
    m_query=2;
    m_step=12;
    m_cluster=-1;
	GetDlgItem( IDC_METHOD)->EnableWindow(FALSE);
	UpdateData(FALSE);

	if(!bokfile.Open(CodebookFileName,CFile::modeRead|CFile::typeBinary,&cfe))
	{
	   MessageBox("Cannot Open the file","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	//read the m_cfh_fromfile
    if(bokfile.Read(&m_cfh_fromfile,sizeof(CODEBOOKFILEHEADER))!=sizeof(CODEBOOKFILEHEADER))
	{
	  bokfile.Close();
	  MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
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
	  MessageBox("Error in reading the codebook file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_clustersused=m_cfh_fromfile.m_wCodewordNumber;
	a=sizeof(double)*(m_cfh_fromfile.m_wTotalDimensions+2)*m_clustersused+128;
    if(a!=bokfile.GetLength()||m_cfh_fromfile.m_dwFileSize!=a)
	{
	  m_clustersused=0;
	  bokfile.Close();
	  MessageBox("Error in reading the file","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	bokfile.Seek(128,CFile::begin);

	//read the codewords
	if(bokfile.Read(m_dCodeword_r,sizeof(double)*(m_cfh_fromfile.m_wTotalDimensions+2)*m_clustersused)!=sizeof(double)*(m_cfh_fromfile.m_wTotalDimensions+2)*m_clustersused)
	{
	    m_clustersused=0;
	    bokfile.Close();
	    MessageBox("Read the file error","Error",MB_OK|MB_ICONSTOP);
	    return;
	}
	bokfile.Close();
	lastpathname2=CodebookFileName;
	m_readbookname=m_ldFile.GetFileName();
	m_bkpath=CodebookFileName;
	m_bCodebookFileOpened=true;
	//m_bFeatureFileOpened=true;
	CString temp;
	char tt[100];
	temp="";
	for(i=0;i<m_clustersused;i++)
	{
		sprintf(tt,"num[%d]=%d; ",i,m_dwNuminEachCluster_r[i]);
		temp+=tt;
	}
	m_infonum=temp;

	m_min=12;
	for(i=0;i<29;i=i++)
	{
	  //if(MAXRETURN[i]==(m_numineachclass/16)*16)break;
	  if(MAXRETURN[i]>=m_numineachclass*m_classes)break;
	}
	m_max=i;
	if(m_ffi_fromfile.m_bSorted==false)
	   m_method=0;
	else
		m_method=7;
	m_query=2;
	m_step=12;
	for(i=0;i<27;i++)
	{
	  if(CLUSTERS[i]>m_clustersused)break;
	}
	m_cluster=i-1;
	if(m_ffi_fromfile.m_bSorted==TRUE)
	{
	   GetDlgItem(IDC_METHOD)->EnableWindow(TRUE);
	   GetDlgItem(IDC_NUMCLUSTERTOSEARCH)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_METHOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUMCLUSTERTOSEARCH)->EnableWindow(FALSE);
	}
	memcpy(&m_trh.m_cfh,&m_cfh_fromfile,sizeof(CODEBOOKFILEHEADER));
	memcpy(m_trh.m_dwCluserSize,m_dwNuminEachCluster_r,sizeof(DWORD)*m_clustersused);
	m_trh.m_bMethodNum=0;
	UpdateData(FALSE);
}
void CDialogEvaluation::EnableWindows2(BOOL b)
{
  GetDlgItem( IDC_OPEN_DATABASE)->EnableWindow(b);
  GetDlgItem( IDC_DBPATH)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_STANDARD)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_SORTED)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_CLUSTERED)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_CLASSES)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_IMAGEEACHCLASS)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_IMAGENUMBER)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_DIMENSIONTOTAL)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_DIMENSION1)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_DIMENSION2)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_DIMENSION3)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_DIMENSION4)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_DIMENSION5)->EnableWindow(b);
  GetDlgItem( IDC_OPEN_CODEBOOK)->EnableWindow(b);
  GetDlgItem( IDC_BKPATH)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_CLUSTERS)->EnableWindow(b);
  GetDlgItem( IDC_NUMINCLUSTER)->EnableWindow(b);
  //GetDlgItem( IDC_METHOD)->EnableWindow(b);
  GetDlgItem( IDC_QUERIES)->EnableWindow(b);
  GetDlgItem( IDC_MIN)->EnableWindow(b);
  GetDlgItem( IDC_MAX)->EnableWindow(b);
  GetDlgItem( IDC_STEP)->EnableWindow(b);
  //GetDlgItem( IDC_NUMCLUSTERTOSEARCH)->EnableWindow(b);
  GetDlgItem( IDC_RANDOMQUERY)->EnableWindow(b);
  //GetDlgItem( IDC_TESTINFODISPLAY)->EnableWindow(b);
  //GetDlgItem( IDC_STARTTEST)->EnableWindow(b);
  //GetDlgItem( IDC_RESULT_LIST)->EnableWindow(b);
  //GetDlgItem( IDC_CLEAR)->EnableWindow(b);
  //GetDlgItem( IDC_RESULTSAVE)->EnableWindow(b);
  //GetDlgItem( IDC_DRAWPR)->EnableWindow(b);
  //GetDlgItem( IDC_DRAWTIME)->EnableWindow(b);
}

void CDialogEvaluation::EnableWindows(BOOL b)
{
  GetDlgItem( IDC_OPEN_CODEBOOK)->EnableWindow(b);
  GetDlgItem( IDC_BKPATH)->EnableWindow(b);
  GetDlgItem( IDC_EDIT_CLUSTERS)->EnableWindow(b);
  GetDlgItem( IDC_NUMINCLUSTER)->EnableWindow(b);
  GetDlgItem( IDC_METHOD)->EnableWindow(b);
  GetDlgItem( IDC_QUERIES)->EnableWindow(b);
  GetDlgItem( IDC_MIN)->EnableWindow(b);
  GetDlgItem( IDC_MAX)->EnableWindow(b);
  GetDlgItem( IDC_STEP)->EnableWindow(b);
  GetDlgItem( IDC_NUMCLUSTERTOSEARCH)->EnableWindow(b);
  GetDlgItem( IDC_RANDOMQUERY)->EnableWindow(b);
  GetDlgItem( IDC_TESTINFODISPLAY)->EnableWindow(b);
  GetDlgItem( IDC_STARTTEST)->EnableWindow(b);
  GetDlgItem( IDC_RESULT_LIST)->EnableWindow(b);
  GetDlgItem( IDC_CLEAR)->EnableWindow(b);
  GetDlgItem( IDC_RESULTSAVE)->EnableWindow(b);
  GetDlgItem( IDC_DRAWPR)->EnableWindow(b);
  GetDlgItem( IDC_DRAWTIME)->EnableWindow(b);
}

void CDialogEvaluation::OnClear() 
{
	// TODO: Add your control notification handler code here
    EnableWindows2(TRUE);
    QueryGenerated=false;
	tested=false;
	m_resultlist.ResetContent();
	m_trh.m_bMethodNum=0;
	m_testinfo="";
	UpdateData(FALSE);
}

void CDialogEvaluation::OnResultsave() 
{
	// TODO: Add your control notification handler code here
	if(tested==false||m_tps==NULL)
	{
	  MessageBox("No Result to Save, Please press test button","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	// TODO: Add your command handler code here
	CFile resultfile;
	int hh;
	CFileException cfe;
	CString ResultFileName;
	char BASED_CODE szFilter[]="Result Text Files(*.txt)|*.txt|Result Binary Files(*.rst)|*.rst|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(FALSE,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	m_ldFile.m_ofn.lpstrTitle="Save Feature File";
	if(m_ldFile.DoModal()!=IDOK)return;
	m_bResultFileSaved=false;
	ResultFileName=m_ldFile.GetPathName();
	m_savedresultfile=m_ldFile.GetFileName();
	while(m_ldFile.GetFileName().GetLength()<7)
	{
	  MessageBox("Please input filename with more than 3 Characters","Information", MB_OK|MB_ICONINFORMATION);
	  if(m_ldFile.DoModal()!=IDOK)return;
	  m_bResultFileSaved=false;
	  ResultFileName=m_ldFile.GetPathName();
	}
	if(m_ldFile.GetFileExt()!="txt")
	{
	  if(!resultfile.Open(ResultFileName,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary,&cfe))
	  {
	    m_savedresultfile="No result file saved";
	    MessageBox("Cannot create this file","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	  //write the m_trh
	  resultfile.Write(&m_trh,sizeof(TESTREPORTSHEADER));
      resultfile.Seek(m_trh.m_dwOffset,CFile::begin);
      //Write the Results
	  resultfile.Write(m_tps,sizeof(TESTPOINTS)*m_trh.m_dwTotalPointsNum);
	  if(m_trh.m_dwFileSize!=resultfile.GetLength())
	  {
	    m_savedresultfile="No feature file saved";
	    resultfile.Close();
	    MessageBox("File saved error","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	  resultfile.Close();
	}
	else
	{
	  hh=_open(ResultFileName,_O_WRONLY | _O_CREAT|_O_TEXT, _S_IREAD |_S_IWRITE );
	  if(hh==-1)
	  {
	    m_savedresultfile="No result file saved";
	    MessageBox("Cannot create this file","Error",MB_OK|MB_ICONSTOP);
	    return;
	  }
	  int m,i,j,l,steps,eachstepnum,ReturnVectors,w;
	  CString temp;
	  char tt[200];
	  steps=(m_trh.m_wMax-m_trh.m_wMin)/m_trh.m_wStep+1;
      eachstepnum=m_trh.m_wQueriesEachClass*m_trh.m_ffi.m_wClasses;
	  for(m=0;m<m_trh.m_bMethodNum;m++)
	  {
	    temp="+++++++++Begin of test for algorithm [";
		temp+=m_trh.m_cMethodName[m];
		temp+="]++++++++++++\n\n\n";
		if(_write(hh,temp,temp.GetLength())== -1)
		{
		     _close(hh);
		    return;
		}
	    temp="[Query No.] [Class No.] [Num of Re. Images] [Time] [Precision] [Recall]\n\n";
		if(_write(hh,temp,temp.GetLength())== -1)
		{
		     _close(hh);
		    return;
		}
	    for(i=0;i<steps;i++)
		{  
	      ReturnVectors=(WORD)(i*m_trh.m_wStep+m_trh.m_wMin);
	      for(j=0;j<eachstepnum;j++)
		  {
			w=m*(eachstepnum*steps+steps)+eachstepnum*i+j;
	   	    temp="";
            sprintf(tt,"[%d],",m_tps[w].m_lQueryName);
		    temp+=tt;
		    sprintf(tt,"[%d],",j/m_trh.m_wQueriesEachClass);
		    temp+=tt;
		    sprintf(tt,"[%d],",ReturnVectors);
		    temp+=tt;
		    sprintf(tt,"[%8f],",m_tps[w].m_fTime);
		    temp+=tt;
		    sprintf(tt,"[%8f],",m_tps[w].m_fPrecision);
		    temp+=tt;
			sprintf(tt,"[%8f]\n",m_tps[w].m_fRecall);
		    temp+=tt;
		    
		    if(_write(hh,temp,temp.GetLength())== -1)
			{
		      _close(hh);
		      return;
			}
		  }
		}
		temp="\nAverage: [Num of Re. Images] [Time] [Precision] [Recall]\n\n";
		if(_write(hh,temp,temp.GetLength())== -1)
		{
		     _close(hh);
		    return;
		}
	    for(l=0;l<steps;l++)
		{
		 w=m*(eachstepnum*steps+steps)+eachstepnum*steps+l;
	     ReturnVectors=(WORD)(l*m_trh.m_wStep+m_trh.m_wMin);
		 temp="";
         sprintf(tt,"[%d],",m_tps[w].m_lQueryName);
		 temp+=tt;
		 sprintf(tt,"[%d],",ReturnVectors);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fTime);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fPrecision);
		 temp+=tt;
		 sprintf(tt,"[%8f]\n",m_tps[w].m_fRecall);
		 temp+=tt;
		 if(_write(hh,temp,temp.GetLength())== -1)
		 {
		   _close(hh);
		   return;
		 }
		}
		temp="\n+++++++++End of test for algorithm [";
		temp+=m_trh.m_cMethodName[m];
		temp+="]++++++++++++\n\n\n";
		if(_write(hh,temp,temp.GetLength())== -1)
		{
		   _close(hh);
		   return;
		}
	  }
	  _close(hh);
	}
	m_bResultFileSaved=true;
	UpdateData(FALSE);
}

void CDialogEvaluation::OnStarttest() 
{
	// TODO: Add your control notification handler code here
	if(QueryGenerated==false)
	{
	   MessageBox("Please generate random queries first", "Information",MB_ICONINFORMATION|MB_OK);
	   return;
	}
	if(m_trh.m_bMethodNum>=10)
	{
		MessageBox("There are more than ten cases tested. Please save file and clear the test", "Information",MB_ICONINFORMATION|MB_OK);
	   return;
	}
	
	int i,j,l;
	CString temp;
	char tt[200];
//	clock_t time1,time2;
	HGLOBAL m_hResult,hsil;  
	LPRETRIEVEDRESULT RetrievedResult;//The index of retrieved result
	DWORD *SearchIndexList;//for iterative methods
	WORD ReturnVectors;
	double tmprecall,tmpprecision;
	long int m_retrievednum;
	double timeused,tmptime;
	
	int steps,points_all,query_all,query_step,query_class,w;
	steps=(MAXRETURN[m_max]-MINRETURN[m_min])/STEP[m_step]+1;//the number of steps
	query_class=QUERYEACHCLASS[m_query];//query each class
    query_step=query_class*m_classes;//query each step
	query_all=query_step*steps;//query each method
	points_all=query_all+steps;//all points including average points each method
	
	GetMethodName(m_trh.m_bMethodNum);//Save the testing method name
	m_testinfo+="Current Test Algorthm: ";//display current tested method
	m_testinfo+=m_trh.m_cMethodName[m_trh.m_bMethodNum];
	m_testinfo+="; ";
	EnableWindows2(FALSE);//Disable the setting options
	
	//save some of m_trh struct information
	m_trh.m_wStructSize=sizeof(TESTREPORTSHEADER);//struct size
    m_trh.m_wQueriesEachClass=query_class;//query each class
    m_trh.m_wMin=MINRETURN[m_min];//min
    m_trh.m_wMax=MAXRETURN[m_max];//max
    m_trh.m_wStep=STEP[m_step];//step size
    m_trh.m_dwTotalPointsNum=(DWORD)(points_all*(m_trh.m_bMethodNum+1));//Total points number
    m_trh.m_dwOffset=sizeof(TESTREPORTSHEADER);//the offsets of the real data
	m_trh.m_dwFileSize=m_trh.m_dwOffset+m_trh.m_dwTotalPointsNum*sizeof(TESTPOINTS);//total File size

	//memory for retrieval results
    m_hResult=NULL;
	m_hResult=GlobalAlloc(GMEM_FIXED,sizeof(RETRIEVEDRESULT)*m_validnum_r);
	if(m_hResult==NULL)
	{
	   MessageBox("Memory not enough","Error",MB_OK|MB_ICONSTOP);
	   return;
	}
	RetrievedResult=(LPRETRIEVEDRESULT)m_hResult;

	//memory for searchlist
	hsil=GlobalAlloc(GMEM_FIXED,sizeof(DWORD)*m_validnum_r);
	if(hsil==NULL)
	{
	   MessageBox("Memory not enough","Error",MB_OK|MB_ICONSTOP);
	   GlobalFree(m_hResult);
	   return;
	}
	SearchIndexList=(DWORD *)hsil;
	
	//loop of steps
	for(i=0;i<steps;i++)
	{
	   ReturnVectors=(WORD)(i*STEP[m_step]+MINRETURN[m_min]);
	   //time1=clock();//the inital time for average
	   tmprecall=0.0;//the tmprecall for average
       tmpprecision=0.0;//The tmpprecision for average
	   tmptime=0.0;
	   //loop of all query
	   for(j=0;j<query_step;j++)
	   {
	   	 //initial retrievednum
		 m_retrievednum=0;
		 //initial timeused
		 timeused=0.0;
		 //initial searchindexlist
	     for(l=0;l<m_validnum_r;l++)SearchIndexList[l]=l;
		 //Get query feature vector, the same for all steps and all methods
		 memcpy(&m_vQueryFeatureVector,m_lpRFeatureVector+m_tps[j].m_lQueryNo,sizeof(FEATUREVECTOR));
         //perform algorithm
		 switch(m_method)
		 {
            case 0://FS
	          MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
              break;
            case 1://EKNNS
			  MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,ReturnVectors,RetrievedResult,&timeused,FALSE,NULL);
	          break;
			case 2://IEKNNSB
			  MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,MINRETURN[m_min],RetrievedResult,&timeused,TRUE,SearchIndexList);
	          for(l=0;l<i;l++)
	            MyRetrieveMethod.EKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,STEP[m_step],RetrievedResult,&timeused,TRUE,SearchIndexList);
	          break;
			case 3://EEKNNS
	          MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,ReturnVectors,RetrievedResult,&timeused,FALSE,NULL);
			  break;
			case 4://IEEKNNSB
	          MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,MINRETURN[m_min],RetrievedResult,&timeused,TRUE,SearchIndexList);
	          for(l=0;l<i;l++)
	            MyRetrieveMethod.EEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,STEP[m_step],RetrievedResult,&timeused,TRUE,SearchIndexList);
			  break;
	        case 5://EEEKNNS
	          MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,ReturnVectors,RetrievedResult,&timeused,FALSE,NULL);
			  break;
			case 6://IEEEKNNSB
	          MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,MINRETURN[m_min],RetrievedResult,&timeused,TRUE,SearchIndexList);
	          for(l=0;l<i;l++)
	            MyRetrieveMethod.EEEKNNSRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,STEP[m_step],RetrievedResult,&timeused,TRUE,SearchIndexList);
			  break;
			case 7://UEEEKNNSinAllVQ
			  if(CLUSTERS[m_cluster]==1)
				MyRetrieveMethod.EEEKNNSinVQNNRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,m_clustersused,&m_retrievednum,ReturnVectors,m_dCodeword_r,m_dwNuminEachCluster_r,RetrievedResult,&timeused);
			  else if(CLUSTERS[m_cluster]==m_clustersused)
				UpdatingEEEKNNSinAllVQRetrieval(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,m_clustersused,&m_retrievednum,ReturnVectors,m_dCodeword_r,m_dwNuminEachCluster_r,RetrievedResult,&timeused);
			  else
                UpdatingEEEKNNSinVQKNNRetrieval(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,m_clustersused,&m_retrievednum,ReturnVectors,m_dCodeword_r,m_dwNuminEachCluster_r,CLUSTERS[m_cluster],RetrievedResult,&timeused);
	          break;
			default:
			  MyRetrieveMethod.FullSearchRetrieveMethod(m_vQueryFeatureVector,m_lpRFeatureVector,m_ffi_fromfile.m_wTotalDimensions,m_validnum_r,&m_retrievednum,m_validnum_r,RetrievedResult,&timeused);
              break;
		 }
		 //the index of the points for all methods
		 w=m_trh.m_bMethodNum*points_all+query_step*i+j;
		 //get the recall and precision
		 ComputeRecallandPrecision(RetrievedResult,j/query_class,ReturnVectors,m_numineachclass,&m_tps[w].m_fRecall,&m_tps[w].m_fPrecision);
		 //get the time
		 m_tps[w].m_fTime=(float)(timeused/1000.0);
		 
		 //accumulate
		 tmprecall+=m_tps[w].m_fRecall;
	     tmpprecision+=m_tps[w].m_fPrecision;
		 tmptime+=timeused/1000.0;
		 
		 //display in list
		 temp="";
         sprintf(tt,"[%d],",m_tps[w].m_lQueryName);
		 temp+=tt;
		 sprintf(tt,"[%d],",j/query_class);
		 temp+=tt;
		 sprintf(tt,"[%d],",ReturnVectors);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fTime);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fPrecision);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fRecall);
		 temp+=tt;
		 m_resultlist.AddString(temp);
	   }
	   //time2=clock();
	   w=m_trh.m_bMethodNum*points_all+query_all+i;
	  // m_tps[w].m_fTime=(float)((double)(time2-time1)/CLOCKS_PER_SEC/query_step*1000.0);
	   m_tps[w].m_fTime=(float)(tmptime/query_step);
	   m_tps[w].m_fRecall=(float)(tmprecall/query_step);
	   m_tps[w].m_fPrecision=(float)(tmpprecision/query_step);	 
	}
	for(l=0;l<steps;l++)
	{
	     ReturnVectors=(WORD)(l*STEP[m_step]+MINRETURN[m_min]);
		 w=m_trh.m_bMethodNum*points_all+query_all+l;
		 temp="";
         sprintf(tt,"[%d],",m_tps[w].m_lQueryName);
		 temp+=tt;
		 sprintf(tt,"[%d],",ReturnVectors);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fTime);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fPrecision);
		 temp+=tt;
		 sprintf(tt,"[%8f],",m_tps[w].m_fRecall);
		 temp+=tt;
	     m_resultlist.AddString(temp);
	}
	tested=true;
	m_trh.m_bMethodNum+=1;
	GlobalFree(m_hResult);
	GlobalFree(hsil);
	UpdateData(FALSE);
}

void CDialogEvaluation::OnRandomquery() 
{
	// TODO: Add your control notification handler code here
    int i,j,k,a,p,p1,l,m,w;
	int steps,points_all,query_all,query_step,query_class;
	CString temp,temp1,temp2;
	char tt[10];
	double par=(double)(m_numineachclass-1)/(double)0x7fff;//the par for random
	GetDlgItem(IDC_QUERIES)->EnableWindow(FALSE);//disable query number setting
	steps=(MAXRETURN[m_max]-MINRETURN[m_min])/STEP[m_step]+1;//the number of steps
	query_class=QUERYEACHCLASS[m_query];//query each class
    query_step=query_class*m_classes;//query each step
	query_all=query_step*steps;//query each method
	points_all=query_all+steps;//all points including average points each method
	m_hTestReports=NULL;//apply testreports memory for at most 10 test methods
	m_hTestReports=GlobalAlloc(GMEM_FIXED,sizeof(TESTPOINTS)*points_all*10);
	if(m_hTestReports==NULL)
	{
	  MessageBox("Memory not enough","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	m_tps=(LPTESTPOINTS)m_hTestReports;
	
	//class loop
	for(j=0;j<m_classes;j++)
	{
		//seeds for each class
		srand((unsigned)time(NULL));
		//loop in each class
		for(i=0;i<query_class;i++)
		{
		    //generate different random numbers in current class
			//i.e. in interval [j*m_numineachclass,(j+1)*m_numineachclass-1]
		   a=j*m_numineachclass+(int)((double)rand()*par);
		   //a=j*m_numineachclass+19+20*i;
		   //change into string
		   sprintf(tt,"%d",a);
		   //Compare with image names in database to get the query no. and name
		   for(k=0;k<m_validnum_r;k++)
		   {
		     temp=m_lpRFeatureVector[k].m_sOriginalFileName;
			 p1=temp.ReverseFind('\\');
			 temp1=temp.Mid(p1+1);//cut name
			 p=temp1.ReverseFind('.');
			 temp2=temp1.Left(p);//cut name
			 if(strcmp(temp2,tt)==0)break;//compare string to get k
		   }
		   //for all methods, max num of methods is 10
		   for(m=0;m<10;m++)
		   { 
			  w=m*points_all+(i+j*query_class);
			  for(l=0;l<steps;l++)
			  {
			    m_tps[w+l*query_step].m_lQueryNo=k;
			    m_tps[w+l*query_step].m_lQueryName=a;
			    m_tps[w+l*query_step].m_wReturnImages=l*STEP[m_step]+MINRETURN[m_min];			 
			  }
		   }
		}
	}
	//for average, all algorithms, the number of return images
	for(m=0;m<10;m++)
	{ 
	  w=m*points_all+query_all;
	  for(l=0;l<steps;l++)
	  {
	    m_tps[w+l].m_lQueryNo=-1;
	    m_tps[w+l].m_lQueryName=-1;
	    m_tps[w+l].m_wReturnImages=l*STEP[m_step]+MINRETURN[m_min];
	  }
	}
	QueryGenerated=true;
}


void CDialogEvaluation::OnDrawpr() 
{
  	// TODO: Add your control notification handler code here
	if(tested==false)
	{
	  MessageBox("No Result to Draw, Please press test button","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	CDialogDrawCurve a;
	CDrawCurve c;
	int steps,l,eachstepnum,w;
	steps=(m_trh.m_wMax-m_trh.m_wMin)/m_trh.m_wStep+1;
    eachstepnum=m_trh.m_wQueriesEachClass*m_trh.m_ffi.m_wClasses;
	//DWORD histogram[BINNUM];
	double *data1= new double[steps];
	double *data2= new double[steps];
	//double hmax=0.523;
	//double hmin=-0.523;
	//Get the YIQ data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    a.m_lNumberofSamples=steps;
	a.m_bSampleDimensions=2;
	//for(int i=0;i<steps;i++)
	  //data[i]=(double)histogram[i];
	int m;
	m=0;
 	for(l=0;l<steps;l++)
	{
		 w=m*(eachstepnum*steps+steps)+eachstepnum*steps+l;
		 data1[l]=m_tps[w].m_fPrecision;
		 data2[l]=m_tps[w].m_fRecall;
	     //ReturnVectors=(WORD)(l*m_trh.m_wStep+m_trh.m_wMin);
		 //temp="";
         //sprintf(tt,"[%d],",m_tps[w].m_lQueryName);
		 //temp+=tt;
		// sprintf(tt,"[%d],",ReturnVectors);
		 //temp+=tt;
		// sprintf(tt,"[%8f],",m_tps[w].m_fTime);
		 //temp+=tt;
		// sprintf(tt,"[%8f],",m_tps[w].m_fPrecision);
		 //temp+=tt;
		 //sprintf(tt,"[%8f]\n",m_tps[w].m_fRecall);
		// temp+=tt;
		 
	}


	a.m_dDataX=data2;
	a.m_dDataY=data1;
	c.m_DataX=a.m_dDataX;
	c.m_DataY=a.m_dDataY;
	//a.m_dDataY=NULL;
	//c.m_DataY=NULL;
	c.m_Dimension=2;
	c.m_Length=steps;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"P-R Performance Comparison");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 P-R Curve Comparison");
	  strcpy(a.cdf.m_sTitles[2],"Precision");
	  strcpy(a.cdf.m_sTitles[3],"Recall");
	  a.DoModal();
	}
	delete []data1;
	delete []data2;
}

void CDialogEvaluation::OnDrawtime() 
{
	// TODO: Add your control notification handler code here
	if(tested==false)
	{
	  MessageBox("No Result to Draw, Please press test button","Error",MB_OK|MB_ICONSTOP);
	  return;
	}
	CDialogDrawCurve a;
	CDrawCurve c;
	int steps,l,eachstepnum,w;
	steps=(m_trh.m_wMax-m_trh.m_wMin)/m_trh.m_wStep+1;
    eachstepnum=m_trh.m_wQueriesEachClass*m_trh.m_ffi.m_wClasses;
	//DWORD histogram[BINNUM];
	double *data= new double[steps];
	//double hmax=0.523;
	//double hmin=-0.523;
	//Get the YIQ data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    a.m_lNumberofSamples=steps;
	a.m_bSampleDimensions=1;
	//for(int i=0;i<steps;i++)
	  //data[i]=(double)histogram[i];
	int m;
	m=0;
 	for(l=0;l<steps;l++)
	{
		 w=m*(eachstepnum*steps+steps)+eachstepnum*steps+l;
		 data[l]=m_tps[w].m_fTime;
	     //ReturnVectors=(WORD)(l*m_trh.m_wStep+m_trh.m_wMin);
		 //temp="";
         //sprintf(tt,"[%d],",m_tps[w].m_lQueryName);
		 //temp+=tt;
		// sprintf(tt,"[%d],",ReturnVectors);
		 //temp+=tt;
		// sprintf(tt,"[%8f],",m_tps[w].m_fTime);
		 //temp+=tt;
		// sprintf(tt,"[%8f],",m_tps[w].m_fPrecision);
		 //temp+=tt;
		 //sprintf(tt,"[%8f]\n",m_tps[w].m_fRecall);
		// temp+=tt;
		 
	}


	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=steps;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Time Performance Comparison");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Time Performance Comparison");
	  strcpy(a.cdf.m_sTitles[2],"Returned Images");
	  strcpy(a.cdf.m_sTitles[3],"Required Time(ms)");
	  a.DoModal();
	}
	delete []data;
}

void CDialogEvaluation::OnSelchangeQueries() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(QUERYEACHCLASS[m_query]>m_numineachclass)
	{
	  m_query=oldquery;
	  UpdateData(FALSE);
	  MessageBox("The number of queries in each class can not be larger than the number of images in each class","Information",MB_ICONINFORMATION|MB_OK);
	}
	else
	{
	   if(m_query!=oldquery)QueryGenerated=false;
	   oldquery=m_query;	
	}
}

void CDialogEvaluation::OnSelchangeMethod() 
{
	// TODO: Add your control notification handler code here
	if(m_bFeatureFileOpened==false)
	{
	   MessageBox("Sorry, please open feature file first","Error",MB_OK|MB_ICONSTOP);
	   m_method=-1;
	   UpdateData(FALSE);
	   return;
	}
	if(m_ffi_fromfile.m_bSorted==false)
	{
	   MessageBox("Nonsorted feature file, only for FS method","Error",MB_OK|MB_ICONSTOP);
	   m_method=0;
	   UpdateData(FALSE);
	   return;
	}
	if(m_bCodebookFileOpened==TRUE&&m_ffi_fromfile.m_bSorted==TRUE)
	{
	  UpdateData(TRUE);
	  if(m_method!=0&&m_method!=7)
	  {
	    MessageBox("Clustered sorted feature file, only for FS and UEEEKNNS method","Error",MB_OK|MB_ICONSTOP);
	    if(m_method<4)m_method=0;
		else
		{
			m_method=7;
			CheckforUEEEKNNSinVQKNN();
		}
		UpdateData(FALSE);
	  }
	  return;
	}
	if(m_bCodebookFileOpened==FALSE&&m_ffi_fromfile.m_bClustered==TRUE&&m_ffi_fromfile.m_bSorted==TRUE)
	{
	  MessageBox("Clustered without codebook info, only for FS method","Error",MB_OK|MB_ICONSTOP);
	  m_method=0;
	  UpdateData(FALSE);
	  return;
	}
	if(m_bCodebookFileOpened==FALSE&&m_ffi_fromfile.m_bClustered==FALSE&&m_ffi_fromfile.m_bSorted==TRUE)
	{
	  UpdateData(TRUE);
	  if(m_method==7)
	  {
	    MessageBox("Unclustered sorted feature only for FS and KNNS related methods","Error",MB_OK|MB_ICONSTOP);
	    if(m_method==7)m_method=6;
	    UpdateData(FALSE);
	  }
	  return;
	}
	if(m_method==7)
	CheckforUEEEKNNSinVQKNN();
}

void CDialogEvaluation::OnSelchangeMax() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	if(MAXRETURN[m_max]>m_numineachclass)
	{
		for(i=0;i<29;i++)
		{ 
	       //if(MAXRETURN[i]>m_numineachclass)break;
		   if(MAXRETURN[i]>=m_numineachclass*m_classes)break;
		}
	   m_max=i-1;
	   UpdateData(FALSE);
	}
	if(MINRETURN[m_min]>MAXRETURN[m_max])
	{
	  for(i=0;i<15;i++)
	  {  
	   if(MINRETURN[i]>MAXRETURN[m_max])break;
	  }
	  m_min=i-1;
	  UpdateData(FALSE);
	}
	if(STEP[m_step]>MAXRETURN[m_max])
    {
	  for(i=0;i<27;i++)
	  {   
	   if(STEP[i]>MAXRETURN[m_max])break;
	  }
	  m_step=i-1;
      UpdateData(FALSE);
    }
	if(m_method==7)
	CheckforUEEEKNNSinVQKNN();
}
void CDialogEvaluation::OnSelchangeMin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	if(MINRETURN[m_min]>MAXRETURN[m_max])
	{
	  for(i=0;i<15;i++)
	  {  
	   if(MINRETURN[i]>MAXRETURN[m_max])break;
	  }
	  m_min=i-1;
	  UpdateData(FALSE);
	}
	if(m_method==7)
	CheckforUEEEKNNSinVQKNN();
}

void CDialogEvaluation::OnSelchangeNumclustertosearch() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	int i;
	if(CLUSTERS[m_cluster]>m_clustersused)
	{
	  for(i=0;i<27;i++)
	  {   
	   if(CLUSTERS[i]>m_clustersused)break;
	  }
	  m_cluster=i-1;
     UpdateData(FALSE);
	}
	if(m_method==7)
	CheckforUEEEKNNSinVQKNN();
}

void CDialogEvaluation::OnSelchangeStep() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	int i;
	if(STEP[m_step]>MAXRETURN[m_max])
	{
	  for(i=0;i<27;i++)
	  {   
	   if(STEP[i]>MAXRETURN[m_max])break;
	  }
	  m_step=i-1;
      UpdateData(FALSE);
	}	
}
void CDialogEvaluation::ComputeRecallandPrecision(LPRETRIEVEDRESULT RetrievedResult,int queryclassnum,int returnnum,int numinclass,float *recall,float *precision)
{
  int i,p,p1,sum;
  CString temp,temp1,temp2;
  char tt[10],tt1[10];
  int t,t1;
  sum=0;

  //get string for query class
  //for example 0-99      100-199  200-299
  //0-399  400-799  800-
  sprintf(tt,"%d",queryclassnum*numinclass);
  t=queryclassnum*numinclass;
  sprintf(tt1,"%d",queryclassnum*numinclass+numinclass-1);
  t1=queryclassnum*numinclass+numinclass-1;
  for(i=0;i<returnnum;i++)
  {
    temp=m_lpRFeatureVector[RetrievedResult[i].m_dwImageIndex].m_sOriginalFileName;
	p1=temp.ReverseFind('\\');
    temp1=temp.Mid(p1+1);
	p=temp1.ReverseFind('.');
	temp2=temp1.Left(p);
	p1=atoi(temp2);
	if(p1>=t&&p1<=t1)sum=sum+1;
  }
  *recall=(float)((double)sum/(double)numinclass);
  *precision=(float)((double)sum/(double)returnnum);
}

void CDialogEvaluation::CheckforUEEEKNNSinVQKNN()
{
   DWORD *num=new DWORD[m_clustersused];
   DWORD sum;
   int i,j,k;
   DWORD p;
   for(i=0;i<m_clustersused;i++)
   {
     num[i]=m_dwNuminEachCluster_r[i];
   }
   for(j=1;j<m_clustersused;j++)
	{
	  for(k=0;k<m_clustersused-j;k++)
	  {
	    if(num[k]>num[k+1])
		{
		  p=num[k];
		  num[k]=num[k+1];
		  num[k+1]=p;
		}
	  }
	}
   sum=0;
   for(i=0;i<CLUSTERS[m_cluster];i++)
   {
     sum+=num[i];
   }
   //if(MAXRETURN[m_max]>sum||MAXRETURN[m_max]>m_numineachclass)
   if(MAXRETURN[m_max]>sum||MAXRETURN[i]>m_numineachclass*m_classes)
   {
   	 for(i=0;i<29;i++)
	 {  
	   //if(MAXRETURN[i]>m_numineachclass||MAXRETURN[i]>sum)break;
	   if(MAXRETURN[i]>m_numineachclass*m_classes||MAXRETURN[i]>sum)break;
	 } 
	 m_max=i-1;
	 UpdateData(FALSE);
   }
   if(MINRETURN[m_min]>MAXRETURN[m_max])
   {
		for(i=0;i<15;i++)
		{   
	       if(MINRETURN[i]>MAXRETURN[m_max])break;
		}
	   m_min=i-1;
	   UpdateData(FALSE);
   }	
   if(STEP[m_step]>MAXRETURN[m_max])
   {
	  for(i=0;i<27;i++)
	  {   
	   if(STEP[i]>MAXRETURN[m_max])break;
	  }
	  m_step=i-1;
      UpdateData(FALSE);
   }
   delete []num;
}
void CDialogEvaluation::GetMethodName(WORD Num)
{
    if(Num>10)return;
	switch(m_method)
	{
	  case 0:
		strcpy(m_trh.m_cMethodName[Num],"FullSearch_____");
        break;
      case 1:
		strcpy(m_trh.m_cMethodName[Num],"EKNNS__________");
        break;
      case 2:
		strcpy(m_trh.m_cMethodName[Num],"IEKNNSB________");
        break;
      case 3:
		strcpy(m_trh.m_cMethodName[Num],"EEKNNS_________");
        break;
      case 4:
		strcpy(m_trh.m_cMethodName[Num],"IEEKNNSB_______");
        break;
      case 5:
		strcpy(m_trh.m_cMethodName[Num],"EEEKNNS________");
        break;
      case 6:
		strcpy(m_trh.m_cMethodName[Num],"IEEEKNNSB______");
        break;
      case 7:
		  char temp[30];
		  sprintf(temp,"%4d",CLUSTERS[m_cluster]);
		  strcpy(m_trh.m_cMethodName[Num],"UEEEKNNSVQA");
		  strcat(m_trh.m_cMethodName[Num],temp);
        break;
      default:
        break;
	}
}
int CDialogEvaluation::InsertingEEEKNNS(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD dimension,DWORD firstposi,DWORD lastsize,DWORD InsertVectorNum,DWORD clustersize,LPRETRIEVEDRESULT RetrievedResult)
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

int CDialogEvaluation::UpdatingEEEKNNS(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD dimension,DWORD firstposi,DWORD VectorNumberTobeSearched,DWORD clustersize,LPRETRIEVEDRESULT RetrievedResult)
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

int CDialogEvaluation::UpdatingEEEKNNSinVQKNNRetrieval(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,WORD m_clusterstosearch,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i,j,k,sum,posi,sum2,sum3,number,check,l;
  int SIZE=m_clusterstosearch;
  if(SIZE>booksize)SIZE=booksize;
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
int CDialogEvaluation::UpdatingEEEKNNSinAllVQRetrieval(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
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
