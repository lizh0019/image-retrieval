// DialogFeedbakWithMemory.cpp : implementation file
//

#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogFeedbakWithMemory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFeedbakWithMemory dialog


CDialogFeedbakWithMemory::CDialogFeedbakWithMemory(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFeedbakWithMemory::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFeedbakWithMemory)
	m_T1 = 0;
	m_T2 = 0;
	m_weights = _T("");
	//}}AFX_DATA_INIT
}


void CDialogFeedbakWithMemory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFeedbakWithMemory)
	DDX_Text(pDX, IDC_EDIT_T1, m_T1);
	DDV_MinMaxInt(pDX, m_T1, 0, 9);
	DDX_Text(pDX, IDC_EDIT_T2, m_T2);
	DDV_MinMaxInt(pDX, m_T2, 1, 10);
	DDX_Text(pDX, IDC_EDIT_WEIGHTS, m_weights);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFeedbakWithMemory, CDialog)
	//{{AFX_MSG_MAP(CDialogFeedbakWithMemory)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_T1, OnKillfocusEditT1)
	ON_EN_KILLFOCUS(IDC_EDIT_T2, OnKillfocusEditT2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFeedbakWithMemory message handlers

BOOL CDialogFeedbakWithMemory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(0,0,350,400);
	CenterWindow(NULL);
	((CWnd *)GetDlgItem(IDC_STATIC_T1))->MoveWindow(20,200,40,25);	
	((CWnd *)GetDlgItem(IDC_EDIT_T1))->MoveWindow(60,200,60,25);	
	((CWnd *)GetDlgItem(IDC_STATIC_T2))->MoveWindow(180,200,40,25);	
	((CWnd *)GetDlgItem(IDC_EDIT_T2))->MoveWindow(220,200,60,25);	
	((CWnd *)GetDlgItem(IDC_STATIC_WEIGHTS))->MoveWindow(20,250,100,25);	
	((CWnd *)GetDlgItem(IDC_EDIT_WEIGHTS))->MoveWindow(20,240,300,80);	
	((CWnd *)GetDlgItem(IDOK))->MoveWindow(70,330,80,30);	
	((CWnd *)GetDlgItem(IDCANCEL))->MoveWindow(170,330,80,30);	
	
	int i;
    float weights[11];
	char tt[100];
	ComputeMemoryWeights(weights);
	m_weights="";
	for(i=0;i<m_T2;i++)
	{
	  sprintf(tt,"w[%d]=%.4f; ",i,weights[i]);
	  m_weights+=tt;
	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogFeedbakWithMemory::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CPen pen,pen1,pen2,*oldpen;
	pen.CreatePen(0,1,RGB(0,0,255));
	pen1.CreatePen(0,1,RGB(0,0,0));
	pen2.CreatePen(1,0,RGB(0,255,255));
	dc.SetTextColor(RGB(255,0,0));
	dc.SetBkMode(TRANSPARENT);
	oldpen=dc.SelectObject(&pen);
    dc.MoveTo(20,120);
	dc.LineTo(20,20);
	dc.MoveTo(20,20);
	dc.LineTo(17,23);
	dc.MoveTo(20,20);
	dc.LineTo(23,23);
	dc.MoveTo(20,120);
	dc.LineTo(320,120);
	dc.MoveTo(320,120);
	dc.LineTo(317,117);
	dc.MoveTo(320,120);
	dc.LineTo(317,123);
	dc.SelectObject(&pen1);
	dc.MoveTo(20,60);
	dc.LineTo(180,60);
	dc.MoveTo(180,60);
	dc.LineTo(280,120);
	dc.SelectObject(&pen2);
	dc.MoveTo(180,60);
	dc.LineTo(180,120);
	dc.SelectObject(oldpen);

	dc.TextOut(25,20,"W");
	dc.TextOut(325,120,"t");
	dc.TextOut(180,125,"T1");
	dc.TextOut(280,125,"T2");
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDialogFeedbakWithMemory::ComputeMemoryWeights(float *weights)
{
   int i;
   double sum=0.0;
   for(i=m_T2;i<=10;i++)//>=T2
    weights[i]=0.0;
   for(i=0;i<=m_T1;i++)//<=T1
	 weights[i]=1.0;
   for(i=m_T1+1;i<m_T2;i++)//>T1  <T2
     weights[i]=(float)(1.0-1.0/(m_T2-m_T1)*(i-m_T1));
   for(i=0;i<m_T2;i++)//Sum 
    sum+=weights[i];
   for(i=0;i<m_T2;i++)//normalized
    weights[i]=(float)(weights[i]/sum);
}

void CDialogFeedbakWithMemory::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(true);	
	if(m_T1>m_T2)m_T2=m_T1;
	
    float weights[11];
	char tt[100];
	int i;
	ComputeMemoryWeights(weights);
	m_weights="";
	for(i=0;i<m_T2;i++)
	{
	  sprintf(tt,"w[%d]=%.4f; ",i,weights[i]);
	  m_weights+=tt;
	}
	UpdateData(false);	
	CDialog::OnOK();
}

void CDialogFeedbakWithMemory::OnKillfocusEditT1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);	
	if(m_T1>m_T2)m_T2=m_T1;
	
	float weights[11];
	char tt[100];
	int i;
	ComputeMemoryWeights(weights);
	m_weights="";
	for(i=0;i<m_T2;i++)
	{
	  sprintf(tt,"w[%d]=%.4f; ",i,weights[i]);
	  m_weights+=tt;
	}
	UpdateData(false);	
}

void CDialogFeedbakWithMemory::OnKillfocusEditT2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);	
	if(m_T1>m_T2)m_T2=m_T1;
	
	float weights[11];
	char tt[100];
	int i;
	ComputeMemoryWeights(weights);
	m_weights="";
	for(i=0;i<m_T2;i++)
	{
	  sprintf(tt,"w[%d]=%.4f; ",i,weights[i]);
	  m_weights+=tt;
	}
	UpdateData(false);	
}
