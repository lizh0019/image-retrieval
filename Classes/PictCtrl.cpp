////////////////////////////////////////////////////////////////
// MSDN Magazine -- October 2001
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0 for Windows 98 and probably Windows 2000 too.
// Set tabsize = 3 in your editor.
//
#include "StdAfx.h"
//#include "/include/PictCtrl.h"
//#include "../include/PictCtrl.h"
#include "PictCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////
// CPictureCtrl is like a static bitmap, but displays any kind of
// image -- BMP, JPG, or GIF.
//
IMPLEMENT_DYNAMIC(CPictureCtrl, CStaticLink)
BEGIN_MESSAGE_MAP(CPictureCtrl, CStaticLink)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CPictureCtrl::CPictureCtrl(BOOL bAutoLoadImage)
	: m_bAutoLoadImage(bAutoLoadImage)
{
	this->m_bGetRect=false;
	m_bPaint=false;
	m_sImagePathName="";
}

CPictureCtrl::~CPictureCtrl()
{
}

//////////////////
// Created: load picture with same ID as me, if there is one. In theory, this
// should not be required because PreSubclassWindow is called whether the
// control is created directly or subclassed from a dialog--but for some odd
// reason unbeknowst to me, GetDlgCtrlID always returns 0 in OnCreate. Go
// figure.
//
int CPictureCtrl::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CStaticLink::OnCreate(lpcs)!=0)
		return -1;
	int nID = GetDlgCtrlID();
	if (m_bAutoLoadImage && nID > 0 && !m_pict) {
		LoadImage(nID);
	}
	return 0;
}

//////////////////
// Subclassed: load picture with same ID as me, if there is one.
//
void CPictureCtrl::PreSubclassWindow()
{
	int nID = GetDlgCtrlID();
	if (m_bAutoLoadImage && nID > 0 && !m_pict) {
		LoadImage(nID);
	}
	CString s;
	SetNoLink(!s.LoadString(GetDlgCtrlID()));
}

//////////////////
// Paint the picture -- override static stuff and do my own thing.
// Call CPicture to to the work. 
//
void CPictureCtrl::OnPaint()
{
	CPaintDC dc(this);
	if(m_bPaint==true&&m_bGetRect==false&&m_pict)  //have the image and not the rect
	{
	this->m_RightRect=this->GetRightRect();  //get the suitable rect
	m_bGetRect=true;
	}
	if (m_bPaint==true&&m_pict) {
		m_pict.Render(&dc, m_RightRect);
	}
}

//////////////////
// If picture is smaller than client area, paint extra with background color.
// 
/*
BOOL CPictureCtrl::OnEraseBkgnd(CDC* pDC)
{
	// get client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	CRect rc = rcClient;

	// get image rectangle
	CRect rcImage(CPoint(0,0), m_pict.GetImageSize());

	// create clipping region
	CRgn clipRgn;
	clipRgn.CreateRectRgnIndirect(&rcClient);
	pDC->SelectClipRgn(&clipRgn);
	pDC->ExcludeClipRect(&rcImage);

	CBrush *pBrush =
		CBrush::FromHandle((HBRUSH)GetWindowLong(m_hWnd, GCL_HBRBACKGROUND));
	pDC->FillRect(&rcClient, pBrush);
	pDC->SelectClipRgn(NULL);

	return TRUE;
}

*/
CRect CPictureCtrl::GetRightRect()
{
		int suitwidth,suitheight;   //suitable width and height
		CRect rcClient,rcDevice;
		GetClientRect(&rcClient);  //device
		CRect rcImage(CPoint(0,0),m_pict.GetImageSize());  //image size
		suitwidth=this->SuitableWidth(rcImage.right,rcImage.bottom,rcClient.right,rcClient.bottom);
		suitheight=this->SuitableHeight(rcImage.right,rcImage.bottom,rcClient.right,rcClient.bottom);
		rcDevice.left=(rcClient.right-suitwidth)/2;
		rcDevice.right=(rcClient.right+suitwidth)/2;
		rcDevice.top=(rcClient.bottom-suitheight)/2;
		rcDevice.bottom=(rcClient.bottom+suitheight)/2;
		return rcDevice;   //��ʾ��rect
		this->m_bGetRect=true;
		this->Invalidate();
}
///������DisplayWidth��DisplayHeigth����������ʾ��Width��Heigth����ͼ��ĺ��ʵĿ�
int CPictureCtrl::SuitableWidth(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
 return (int)(Width*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));

}
///������DisplayWidth��DisplayHeigth����������ʾ��Width��Heigth����ͼ��ĺ��ʵĸ�
int CPictureCtrl::SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth)
{
return (int)(Heigth*min((double)DisplayWidth/Width,(double)DisplayHeigth/Heigth));
}

void CPictureCtrl::DisEnableDisplay()
{
//	return(this->OnEraseBkgnd(this->GetDC()));
	m_bPaint=false;
	
}

CString CPictureCtrl::GetImagePathName()
{
 return this->m_sImagePathName;
}
