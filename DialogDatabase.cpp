// DialogDatabase.cpp : implementation file
//

#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogDatabase dialog


CDialogDatabase::CDialogDatabase(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDatabase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogDatabase)
	m_sPath = _T("");
	//}}AFX_DATA_INIT
}


void CDialogDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDatabase)
	DDX_Text(pDX, IDC_EDIT_PATH, m_sPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDatabase, CDialog)
	//{{AFX_MSG_MAP(CDialogDatabase)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogDatabase message handlers


////Load the base dialog Path
void CDialogDatabase::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;
	bi.lpszTitle="Select Folder";
//	bi.ulFlags=BIF_USENEWUI;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	this->m_sPath=str;
	if(str.GetAt(str.GetLength()-1)!='\\')
	this->m_sPath+="\\";
	UpdateData(FALSE);
}

