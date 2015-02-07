// DialogImageInformation.cpp : implementation file
//

#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogImageInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogImageInformation dialog


CDialogImageInformation::CDialogImageInformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImageInformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogImageInformation)
	m_sBitCount = _T("");
	m_sHeight = _T("");
	m_sPathName = _T("");
	m_sWidth = _T("");
	//}}AFX_DATA_INIT
}


void CDialogImageInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogImageInformation)
	DDX_Text(pDX, IDC_BITCOUNT, m_sBitCount);
	DDX_Text(pDX, IDC_HEIGHT, m_sHeight);
	DDX_Text(pDX, IDC_PATHNAME, m_sPathName);
	DDX_Text(pDX, IDC_WIDTH, m_sWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogImageInformation, CDialog)
	//{{AFX_MSG_MAP(CDialogImageInformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogImageInformation message handlers

