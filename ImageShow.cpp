// ImageShow.cpp : implementation file
//

#include "stdafx.h"
#include "VqRetrieve.h"
#include "ImageShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageShow dialog


CImageShow::CImageShow(CWnd* pParent /*=NULL*/)
	: CDialog(CImageShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageShow)
	m_comp = _T("");
	m_psnr = 0.0f;
	m_width = 0;
	m_height = 0;
	m_path = _T("");
	//}}AFX_DATA_INIT
}


void CImageShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageShow)
	DDX_Text(pDX, IDC_EDIT_COMP, m_comp);
	DDX_Text(pDX, IDC_EDIT_PSNR, m_psnr);
	DDX_Text(pDX, IDC_EDIT_IMWIDTH, m_width);
	DDX_Text(pDX, IDC_EDIT_IMHEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_path);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageShow, CDialog)
	//{{AFX_MSG_MAP(CImageShow)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageShow message handlers

BOOL CImageShow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(showcom==2)m_comp="Y";
	else if(showcom==1)m_comp="Cb";
	else if(showcom==0)m_comp="Cr";
	else m_comp="24bits";
    m_width=width;
	m_height=height;
	m_path=file;
	MoveWindow(0,0,1024,768);
	CenterWindow(NULL);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageShow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int a, b;
	// TODO: Add your message handler code here
	a=SuitableWidth(width,height,500,500);
	b=SuitableHeight(width,height,500,500);
	if(showcom<3)
	{
	 ::StretchDIBits(dc.m_hDC,20,20,a,b,0,0,width,height,m_DisplayImageBytes[0]+1078,(BITMAPINFO *)(m_DisplayImageBytes[0]+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	 ::StretchDIBits(dc.m_hDC,40+a,20,a,b,0,0,width,height,m_DisplayImageBytes[1]+1078,(BITMAPINFO *)(m_DisplayImageBytes[1]+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	}
	else
	{
	 ::StretchDIBits(dc.m_hDC,20,20,a,b,0,0,width,height,m_DisplayImageBytes[0]+54,(BITMAPINFO *)(m_DisplayImageBytes[0]+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	 ::StretchDIBits(dc.m_hDC,40+a,20,a,b,0,0,width,height,m_DisplayImageBytes[1]+54,(BITMAPINFO *)(m_DisplayImageBytes[1]+sizeof(BITMAPFILEHEADER)),DIB_RGB_COLORS,SRCCOPY);
	 GetDlgItem(IDC_STATIC_PSNR)->SetWindowText("PSNR(Ave)");
	}
	GetDlgItem(IDC_STATIC_ORIGINAL)->MoveWindow(a/2,b+40,180,30);
	GetDlgItem(IDC_STATIC_DECODE)->MoveWindow(3*a/2,b+40,180,30);
	GetDlgItem(IDC_STATIC_FILE)->MoveWindow(50,b+80,180,30);
	GetDlgItem(IDC_EDIT_FILEPATH)->MoveWindow(250,b+80,420,30);
	GetDlgItem(IDC_STATIC_IMAGEWIDTH)->MoveWindow(50,b+120,150,30);
	GetDlgItem(IDC_EDIT_IMWIDTH)->MoveWindow(250,b+120,120,30);
	GetDlgItem(IDC_STATIC_IMAGEHEIGHT)->MoveWindow(400,b+120,150,30);
	GetDlgItem(IDC_EDIT_IMHEIGHT)->MoveWindow(550,b+120,120,30);
	GetDlgItem(IDC_STATIC_COMPO)->MoveWindow(50,b+160,150,30);
	GetDlgItem(IDC_EDIT_COMP)->MoveWindow(250,b+160,120,30);
	GetDlgItem(IDC_STATIC_PSNR)->MoveWindow(400,b+160,150,30);
	GetDlgItem(IDC_EDIT_PSNR)->MoveWindow(550,b+160,120,30);
	GetDlgItem(IDOK)->MoveWindow(490,700,80,30);
	// Do not call CDialog::OnPaint() for painting messages
}
///Return the suitable dispaly width
int CImageShow::SuitableWidth(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
   return (int)(Width*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}

///Return the suitable dispaly height
int CImageShow::SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
  return (int)(Heigth*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}
