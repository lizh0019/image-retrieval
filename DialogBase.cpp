// DialogBase.cpp : implementation file
//

#include "stdafx.h"
#include "SBIRSystem.h"
#include "DialogBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogBase dialog


CDialogBase::CDialogBase(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogBase)
	m_sPathName = _T("");
	//}}AFX_DATA_INIT
	this->imagebasechoose=-1;
}


void CDialogBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogBase)
	DDX_CBString(pDX, IDC_PATH, m_sPathName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogBase, CDialog)
	//{{AFX_MSG_MAP(CDialogBase)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_CREAT, OnButtonCreat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogBase message handlers

void CDialogBase::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	char BASED_CODE szFilter[]="DataBase Files(*.ibh)|*.ibh|All Files(*.*)|*.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(m_ldFile.DoModal()!=IDOK)
	{	
		imagebasechoose=0;
		return;
	}
	this->sLoadImageBaseFile=m_ldFile.GetPathName();
	this->m_sPathName=sLoadImageBaseFile;
	while ((m_sPathName.GetAt(m_sPathName.GetLength()-1)!='\\'))
	{
		this->m_sPathName.Delete(m_sPathName.GetLength()-1);		
	}		
	if(m_sPathName.GetAt(m_sPathName.GetLength()-1)=='\\')
		this->m_sPathName.Delete(m_sPathName.GetLength()-1);
	imagebasechoose=1;   //load
	UpdateData(false);
}

void CDialogBase::OnButtonCreat() 
{
	// TODO: Add your control notification handler code here
		CString str;
		BROWSEINFO bi;
		char name[MAX_PATH];
		ZeroMemory(&bi,sizeof(BROWSEINFO));
		bi.hwndOwner=GetSafeHwnd();
		bi.pszDisplayName=name;
		bi.lpszTitle="Select Folder to Save the imagebase:";
		LPITEMIDLIST idl=SHBrowseForFolder(&bi);
		if(idl==NULL)
		{
			imagebasechoose=0;
			return;
		}
		SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
		str.ReleaseBuffer();
		if(str.GetAt(str.GetLength()-1)=='\\')
			str.Delete(str.GetLength()-1);
		this->m_sPathName=str;
	//succeed
		imagebasechoose=2;
		UpdateData(false);
}


bool CDialogBase::GetImageBaseFolder()
{
		CString str;
		BROWSEINFO bi;
		char name[MAX_PATH];
		ZeroMemory(&bi,sizeof(BROWSEINFO));
		bi.hwndOwner=GetSafeHwnd();
		bi.pszDisplayName=name;
		bi.lpszTitle="Select Images Added into the base:";
		LPITEMIDLIST idl=SHBrowseForFolder(&bi);
		if(idl==NULL)
		{
	
			return false ;
		}
		SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
		str.ReleaseBuffer();
		if(str.GetAt(str.GetLength()-1)=='\\')
			str.Delete(str.GetLength()-1);
		this->m_sPathName=str;
	//succeed
		return true;
}
