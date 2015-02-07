// DialogParamentSet.cpp : implementation file
//

#include "stdafx.h"
#include "SBIRSystem.h"
#include "DialogParamentSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogParamentSet dialog


CDialogParamentSet::CDialogParamentSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogParamentSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogParamentSet)
	m_dParamentRR = 0.0;
	m_dParamentSI = 0.0;
	m_dParamentSU = 0.0;
	m_bStudying = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogParamentSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogParamentSet)
	DDX_Text(pDX, IDC_EDIT1, m_dParamentRR);
	DDV_MinMaxDouble(pDX, m_dParamentRR, 0., 1.);
	DDX_Text(pDX, IDC_EDIT2, m_dParamentSI);
	DDV_MinMaxDouble(pDX, m_dParamentSI, 0., 1.);
	DDX_Text(pDX, IDC_EDIT3, m_dParamentSU);
	DDV_MinMaxDouble(pDX, m_dParamentSU, 0., 1.);
	DDX_Check(pDX, IDC_CHECK1, m_bStudying);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogParamentSet, CDialog)
	//{{AFX_MSG_MAP(CDialogParamentSet)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogParamentSet message handlers

void CDialogParamentSet::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}
