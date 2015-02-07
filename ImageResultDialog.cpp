// ImageResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SBIRSystem.h"
#include "ImageResultDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageResultDialog dialog


CImageResultDialog::CImageResultDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CImageResultDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageResultDialog)
	m_sHeight = _T("");
	m_sWidth = _T("");
	//}}AFX_DATA_INIT
	m_iImageID=-1;
	this->m_sImageFullPath="";
	m_bRetrievalChanged=0;
}

BOOL CImageResultDialog:: OnInitDialog()
{
	CDialog::OnInitDialog();
//	this->SetWindowPos(NULL,0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN),0);
	// TODO: Add extra initialization here

	this->m_cResultImage.LoadImage(this->m_sImageFullPath);

	this->m_sHeight.Format("%i%s",m_cResultImage.GetImageSize().cy,m_sHeight);
	this->m_sWidth.Format("%i%s",m_cResultImage.GetImageSize().cx,m_sWidth);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
}
void CImageResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageResultDialog)
	DDX_Control(pDX, IDC_RESULTIMAGE_ORGINAL, m_cResultImage);
	DDX_Text(pDX, IDC_STATIC_HEIGHT, m_sHeight);
	DDX_Text(pDX, IDC_STATIC_WIDTH, m_sWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageResultDialog, CDialog)
	//{{AFX_MSG_MAP(CImageResultDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_RETRIEVAL_CHANGE, OnButtonRetrievalChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageResultDialog message handlers

void CImageResultDialog::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	char BASED_CODE szFilter[]="Image(*.jpg)|*.jpg|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(m_ldFile.DoModal()!=IDOK)
	{	
		return;
	}
	CString m_sSaveFilePath=m_ldFile.GetPathName();
	if (m_sSaveFilePath.Find('.',0)<0)
	{
		m_sSaveFilePath+=".jpg";
	}
	if(::CopyFile(this->m_sImageFullPath,m_sSaveFilePath,false)==false)
	{
		MessageBox("Save File error!");
	}
}


void CImageResultDialog::OnButtonRetrievalChange() 
{
	// TODO: Add your control notification handler code here
	this->m_bRetrievalChanged=1;
	OnOK();
}
