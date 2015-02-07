 // DialogImageBase.cpp : implementation file
//

#include "stdafx.h"
#include "SBIRSystem.h"
#include "DialogImageBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogImageBase dialog


CDialogImageBase::CDialogImageBase(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImageBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogImageBase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogImageBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogImageBase)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogImageBase, CDialog)
	//{{AFX_MSG_MAP(CDialogImageBase)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogImageBase message handlers
