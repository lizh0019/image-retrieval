// DialogLoadImage.cpp : implementation file
//

#include "stdafx.h"
#include "SBIRSystem.h"
#include "DialogLoadImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogLoadImage dialog


CDialogLoadImage::CDialogLoadImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLoadImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogLoadImage)
	m_bRandomChecked = FALSE;
	m_iCurentNumber=0;
	m_iTotalImageNumber=0;
	m_sImagePath="";
	//}}AFX_DATA_INIT
}

BOOL CDialogLoadImage::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	this->SetWindowPos(NULL,0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN),0);
	// TODO: Add extra initialization here
	CString temp;
	temp=this->m_sImagePath+"0.jpg";
	this->m_cControlLoadImage.LoadImage(temp);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDialogLoadImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogLoadImage)
	DDX_Control(pDX, IDC_BROWSEIMAGE, m_cControlLoadImage);
	DDX_Check(pDX, IDC_CHECK1, m_bRandomChecked);
	DDX_Text(pDX, IDC_EDIT2, m_iCurentNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogLoadImage, CDialog)
	//{{AFX_MSG_MAP(CDialogLoadImage)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_CUURETN, OnButtonDisplayCuuretn)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogLoadImage message handlers

CString CDialogLoadImage::GetFilePathName()
{
	CString temp;
	char sTemp[30];
	itoa(this->m_iCurentNumber,sTemp,10);
	temp=this->m_sImagePath;
	temp=temp+sTemp;
	temp=temp+".jpg";
	return temp;
}

void CDialogLoadImage::OnButtonDisplayCuuretn() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(true);
	if (this->m_iCurentNumber>this->m_iTotalImageNumber) 
	{
		MessageBox("Too large");
	}
	//load
	this->m_cControlLoadImage.DisEnableDisplay();
	this->m_cControlLoadImage.LoadImage(this->GetFilePathName());
	
	UpdateData(false);
	Invalidate();
	
}

void CDialogLoadImage::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(true);
	if (this->m_iCurentNumber>=this->m_iTotalImageNumber)
	{
		MessageBox("End");
		return ;
		
	}

//next one
	if(this->m_bRandomChecked==TRUE)
	{
		srand(clock());
		this->m_iCurentNumber=rand()%this->m_iTotalImageNumber;
	}
	else
		this->m_iCurentNumber++;
	//display
	//load
//	this->m_cControlLoadImage.DisEnableDisplay();
	this->m_cControlLoadImage.LoadImage(this->GetFilePathName());
	UpdateData(false);
	Invalidate();	
}
