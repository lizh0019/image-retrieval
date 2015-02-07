// DialogDisplayImage.cpp : implementation file
//

#include "stdafx.h"
#include "VQRetrieve.h"
#include "DialogDisplayImage.h"
#include "DialogImageInformation.h"

#include "jpeg.h"
#include <io.h> 
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogDisplayImage dialog


CDialogDisplayImage::CDialogDisplayImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDisplayImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogDisplayImage)
		// NOTE: the ClassWizard will add member initialization here
		//}}AFX_DATA_INIT
	sizex=50;
	sizey=50;
	m_bCanMove=false;    //No move
}


void CDialogDisplayImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDisplayImage)
	DDX_Control(pDX, IDC_BIGIMAGE, m_cBigDisplayImage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDisplayImage, CDialog)
	//{{AFX_MSG_MAP(CDialogDisplayImage)
	ON_WM_PAINT()
	ON_COMMAND(ID_SAVECHOOSEIMAGE, OnSavechooseimage)
	ON_COMMAND(ID_BUTTONLEFT, OnButtonleft)
	ON_COMMAND(ID_BUTTONRITHT, OnButtonritht)
	ON_COMMAND(ID_BUTTONUP, OnButtonup)
	ON_COMMAND(ID_BUTTONDOWN, OnButtondown)
	ON_COMMAND(ID_MOVE, OnMyMove)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_IMAGEINFORMATION, OnImageinformation)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_WM_DESTROY()
	ON_COMMAND(ID_IMAGE_HHIST, OnImageHhist)
	ON_COMMAND(ID_IMAGE_GHIST, OnImageGhist)
	ON_COMMAND(ID_IMAGE_BHIST, OnImageBhist)
	ON_COMMAND(ID_IMAGE_RHIST, OnImageRhist)
	ON_COMMAND(ID_IMAGE_SHIST, OnImageShist)
	ON_COMMAND(ID_IMAGE_VHIST, OnImageVhist)
	ON_COMMAND(ID_IMAGE_YHIST, OnImageYhist)
	ON_COMMAND(ID_IMAGE_CbHIST, OnImageCbHIST)
	ON_COMMAND(ID_IMAGE_CrHIST, OnImageCrHIST)
	ON_COMMAND(ID_IMAGE_Y1HIST, OnImageY1hist)
	ON_COMMAND(ID_IMAGE_IHIST, OnImageIhist)
	ON_COMMAND(ID_IMAGE_QHIST, OnImageQhist)
	ON_COMMAND(ID_IMAGE_H1HIST, OnImageH1hist)
	ON_COMMAND(ID_IMAGE_CHIST, OnImageChist)
	ON_COMMAND(ID_IMAGE_V1HIST, OnImageV1hist)
	ON_COMMAND(ID_IMAGE_LHIST, OnImageLhist)
	ON_COMMAND(ID_IMAGE_AHIST, OnImageAhist)
	ON_COMMAND(ID_IMAGE_B1HIST, OnImageB1hist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogDisplayImage message handlers
int CDialogDisplayImage::DisplayJpegFile(char m_sFileName[MAX_PATH])
{
    unsigned int x,y;
	long int fh;
	unsigned char *m_cImageBytes;
	unsigned long int linebytes;
	CFile file;
	CJpeg jpg;
	CString temp;
	BYTE *p1,*p2,*p3;
	JPEG_IMAGE_INFO info;
	HGLOBAL Imagehg;
    LPBITMAPFILEHEADER bitfile;
    LPBITMAPINFOHEADER bitinfo;
	if(jpg.open(m_sFileName,IDCT_INT))
	{ 
	  jpg.getImageInfo(&info);
	  temp=m_CurrentDirectory;
	  temp=temp+"\\tempretri1.bmp";
	  fh=_open(temp,_O_BINARY|_O_WRONLY|_O_CREAT|_O_TRUNC,_S_IREAD|_S_IWRITE);
	  if(fh==-1)
		  { 
	        jpg.close();
			return -1;
		  }
		  if(info.comNum==3)
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfoc;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfoc+sizeof(BITMAPFILEHEADER));
            bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
		    linebytes=(info.imgWidth*24+31)/32*4;
		    bitfile->bfSize=info.imgHeight*linebytes+54;
		    bitinfo->biSizeImage=info.imgHeight*info.imgWidth;
		    p1=info.image[0];
		    p2=info.image[1];
		    p3=info.image[2];
		    Imagehg=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          //MessageBox(NULL,"No enough memory!","Temporary File Save",MB_ICONSTOP|MB_OK);//Display Info
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
            memcpy(m_cImageBytes,m_StandardBmpInfoc,54);
			for(y=0;y<info.imgHeight;y++)
			{
	          p1=info.image[0]+y*info.bufWidth;
			  p2=info.image[1]+y*info.bufWidth;
			  p3=info.image[2]+y*info.bufWidth;
			  for(x=0;x<linebytes/3;x++)
			  {
			    if(x<info.imgWidth)
				{
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3]=*p3++;
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3+1]=*p2++;
				  m_cImageBytes[54+(info.imgHeight-y-1)*linebytes+x*3+2]=*p1++;
				}
			  }
			}
		  }
		  else
		  {
		    bitfile=(LPBITMAPFILEHEADER)m_StandardBmpInfo;
            bitinfo=(LPBITMAPINFOHEADER)(m_StandardBmpInfo+sizeof(BITMAPFILEHEADER));
		    bitinfo->biHeight=info.imgHeight;
            bitinfo->biWidth=info.imgWidth;
			linebytes=(info.imgWidth+3)/4*4;
		    bitfile->bfSize=info.imgHeight*linebytes+1078;
		    bitinfo->biSizeImage=info.imgHeight*info.imgWidth;
		    Imagehg=GlobalAlloc(GMEM_FIXED,bitfile->bfSize);//Apply the required memory
            ////If memory is not enough, return directly
            if(Imagehg==NULL)
			{
              _close(fh); //Close the file
	          //MessageBox(NULL,"No enough memory!","Temporary File Save",MB_ICONSTOP|MB_OK);//Display Info
	          jpg.close();
			  return -2;
			}
            m_cImageBytes=(unsigned char *)Imagehg;//Give the memory pointer to the file data pointer
            memcpy(m_cImageBytes,m_StandardBmpInfo,1078);
			p1=info.image[0];
			for(y=0;y<info.imgHeight;y++)
			{
			  memcpy(m_cImageBytes+1078+(info.imgHeight-y-1)*linebytes,p1,linebytes);
			  p1=p1+info.bufWidth;
			}
		  }
		  if(_write(fh,m_cImageBytes,bitfile->bfSize)!=(int)bitfile->bfSize)
		  {
			//MessageBox(NULL,"File save error","Error!", MB_ICONSTOP|MB_OK);
			_close(fh);
			GlobalFree(Imagehg);
            jpg.close();
			return -2;
		  }
		  _close(fh);
		  GlobalFree(Imagehg);
		  jpg.close();
		  return 0;
	}
	return -1;
}

void CDialogDisplayImage::initialize()
{
	CString temp;
	
	m_cBigDisplayImage.MoveWindow(sizex,sizey,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	if(m_cFeatureVector.m_bType==0)
	Image=(HBITMAP)::LoadImage(NULL,m_cFeatureVector.m_sOriginalFileName,IMAGE_BITMAP,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,\
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
	else
	{
	   temp=m_CurrentDirectory;
	   if(QueryorRetrieval==0)
	     temp=temp+"\\tempquery.bmp";
	   else
	   {
		   DisplayJpegFile(m_cFeatureVector.m_sOriginalFileName);
		   temp=temp+"\\tempretri1.bmp";
	   }
	   Image=(HBITMAP)::LoadImage(NULL,temp,IMAGE_BITMAP,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,\
	   LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}
	m_cBigDisplayImage.SetBitmap(Image);
	UpdateData(FALSE);
}

int CDialogDisplayImage::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DoModal();
}

BOOL CDialogDisplayImage::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	lpszWindowName=m_cFeatureVector.m_sOriginalFileName;
//	initialize();
	return CDialog::Create(IDD, pParentWnd);
}

BOOL CDialogDisplayImage::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
    cs.cx=1024;
	cs.cy=768;
	cs.x=0;
	cs.y=0;
	return CDialog::PreCreateWindow(cs);
}

void CDialogDisplayImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}
///save the Image
void CDialogDisplayImage::OnSavechooseimage() 
{
	// TODO: Add your command handler code here
	CFile myfile;
	char BASED_CODE szFilter[]="Bitmap Files(*.bmp)|*.bmp|JPG Files(*.jpg)|*.jpg|JPG Files(*.jpeg)|*.jpeg|Text files(*.txt)|*.txt||";
	CFileDialog m_ldFile(FALSE,"*.bmp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(m_ldFile.DoModal()==IDOK)
	{
		if(myfile.Open(m_cFeatureVector.m_sOriginalFileName,CFile::modeRead,NULL)==NULL)
		{
			MessageBox("We can't save the file","Save Error",MB_OK||MB_ICONSTOP);
			return;
		}
	    long int ImageSize=myfile.GetLength();
	    HGLOBAL hReadData;
	    unsigned char *pReadData;
	    hReadData=GlobalAlloc(GMEM_FIXED,ImageSize);
	    if(hReadData==NULL)
		{
		  MessageBox("Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		  return;
		}
	    pReadData=(unsigned char*)hReadData;
	    myfile.Read(pReadData,ImageSize);
	    myfile.Close();
	    if(myfile.Open(m_ldFile.GetPathName(),CFile::modeCreate|CFile::modeReadWrite ,NULL)==NULL)
		{
		  GlobalFree(hReadData);
		  MessageBox("We can't save the file","Save Error",MB_OK||MB_ICONSTOP);
		  return;
		}
	    myfile.Write(hReadData,ImageSize);
	    myfile.Close();
	    GlobalFree(hReadData);
	} 
}

void CDialogDisplayImage::OnButtonleft() 
{
	// TODO: Add your command handler code here
	if(sizex<=0)return;
	sizex-=20;
	m_cBigDisplayImage.MoveWindow(sizex,sizey,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
}

void CDialogDisplayImage::OnButtonritht() 
{
	// TODO: Add your command handler code here
	if(sizex>=1024)return;
	sizex+=20;
    m_cBigDisplayImage.MoveWindow(sizex,sizey,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
}

void CDialogDisplayImage::OnButtonup() 
{
	// TODO: Add your command handler code here
	if(sizey<=0)return;
	sizey-=20;
    m_cBigDisplayImage.MoveWindow(sizex,sizey,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
}

void CDialogDisplayImage::OnButtondown() 
{
	// TODO: Add your command handler code here
	if(sizey>=768)return;
	sizey+=20;
    m_cBigDisplayImage.MoveWindow(sizex,sizey,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
}

void CDialogDisplayImage::OnMyMove() 
{
	// TODO: Add your command handler code here
	m_bCanMove=true;	
}

void CDialogDisplayImage::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnMouseMove(nFlags, point);
	if(m_bCanMove==true)
	{
		sizex=(int)(point.x-m_cFeatureVector.m_lImageWidth/2.0);  //The midpoint
		sizey=(int)(point.y-m_cFeatureVector.m_lImageHeight/2.0);
		m_cBigDisplayImage.MoveWindow(sizex,sizey,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	}
}

void CDialogDisplayImage::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
    m_bCanMove=true;
}

void CDialogDisplayImage::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnRButtonDown(nFlags, point);
	m_bCanMove=false;
}

void CDialogDisplayImage::MyOnCancel()
{
    OnCancel();
}

void CDialogDisplayImage::OnImageinformation() 
{
	// TODO: Add your command handler code here
	CDialogImageInformation imageinformation;
	imageinformation.m_sBitCount.Format("%s%d",imageinformation.m_sBitCount,m_cFeatureVector.m_bBitCount);
	imageinformation.m_sHeight.Format("%s%d",imageinformation.m_sHeight,m_cFeatureVector.m_lImageHeight);
	imageinformation.m_sWidth.Format("%s%d",imageinformation.m_sWidth,m_cFeatureVector.m_lImageWidth);
	imageinformation.m_sPathName=m_cFeatureVector.m_sOriginalFileName;
	imageinformation.DoModal();
}

BOOL CDialogDisplayImage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowPos(NULL,0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN),0);
	// TODO: Add extra initialization here
	initialize();
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	HGLOBAL Imagehg;
	Imagehg=GlobalAlloc(GMEM_FIXED,m_cFeatureVector.m_lImageHeight*m_cFeatureVector.m_lImageWidth*num*9);
	if(Imagehg==NULL)
	{
	  MessageBox("Sorry,memory not enough","Error",MB_OK|MB_ICONSTOP);
	  CDialog::OnOK();
	}
	image_byte=(BYTE *)Imagehg;//Give the memory pointer to the file data pointer
	image_double=(double *)(image_byte+m_cFeatureVector.m_lImageHeight*m_cFeatureVector.m_lImageWidth*num);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogDisplayImage::OnExit() 
{
	// TODO: Add your command handler code here
	OnCancel();
}

void CDialogDisplayImage::OnDestroy() 
{
	::DeleteObject(Image);
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
}



void CDialogDisplayImage::OnImageGhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	b.calculate_histogram(rgbimage,histogram,8,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,1,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Green-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Green-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;

}

void CDialogDisplayImage::OnImageBhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	double *data1= new double[BINNUM];
	int num;
	
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	b.calculate_histogram(rgbimage,histogram,8,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,0,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	{
	  data[i]=(double)histogram[i];
	  data1[i]=(double)histogram[i];
	}
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=data1;
	c.m_DataY=a.m_dDataY;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Blue-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Blue-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
	delete []data1;
}

void CDialogDisplayImage::OnImageRhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	b.calculate_histogram(rgbimage,histogram,8,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,2,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Red-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Red-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}
void CDialogDisplayImage::OnImageHhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no hue information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	//Get the HSV data image_double from
    //RGB data rgbimage
	//m_cFeatureVector.m_bBitCount,
    b.rgb2hsv(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,2,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  //a.cdf.m_bHowtoGetMinMax[0]=0;
	  //a.cdf.m_dMinMaxInput[0]=
	  strcpy(a.cdf.m_sTitles[0],"Hue-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Hue-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}

void CDialogDisplayImage::OnImageShist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no saturation information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	//Get the HSV data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    b.rgb2hsv(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,1,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Saturation-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Saturation-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}

void CDialogDisplayImage::OnImageVhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	//Get the HSV data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    b.rgb2hsv(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,0,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Value-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Value-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}

void CDialogDisplayImage::OnImageYhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
    //Get the YCbCr data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    b.rgb2YCbCr(rgbimage,image_byte,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
    b.calculate_histogram(image_byte,histogram,8,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,2,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Y-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Y-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;	
}

void CDialogDisplayImage::OnImageCbHIST() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no Cb information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	//Get the YCbCr data data image_double from
    //RGB data rgbimage
	//m_cFeatureVector.m_bBitCount,
    b.rgb2YCbCr(rgbimage,image_byte,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
    b.calculate_histogram(image_byte,histogram,8,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,1,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Cb-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Cb-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;		
}

void CDialogDisplayImage::OnImageCrHIST() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no Cr information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	//Get the YCbCr data image_double from
    //RGB data rgbimage
	//m_cFeatureVector.m_bBitCount
    b.rgb2YCbCr(rgbimage,image_byte,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
    b.calculate_histogram(image_byte,histogram,8,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,0,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Cr-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Cr-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;		
}

void CDialogDisplayImage::OnImageY1hist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	//Get the YIQ data image_double from
    //RGB data rgbimage
	//m_cFeatureVector.m_bBitCount,
    b.rgb2YIQ(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,2,BINNUM,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Y(IQ)-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Y-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}

void CDialogDisplayImage::OnImageIhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no I information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	//Get the YIQ data image_double from
    //RGB data rgbimage
	//m_cFeatureVector.m_bBitCount,
    b.rgb2YIQ(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	double hmax=0.596;
	double hmin=-0.596;
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,1,BINNUM,false,&hmax,&hmin,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"I-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 I-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}

void CDialogDisplayImage::OnImageQhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no Q information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
    DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	double hmax=0.523;
	double hmin=-0.523;
	//Get the YIQ data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    b.rgb2YIQ(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,0,BINNUM,false,&hmax,&hmin,false);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"Q-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 Q-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;
}

void CDialogDisplayImage::OnImageH1hist() 
{
	// TODO: Add your command handler code here
	
}

void CDialogDisplayImage::OnImageChist() 
{
	// TODO: Add your command handler code here
	
}

void CDialogDisplayImage::OnImageV1hist() 
{
	// TODO: Add your command handler code here
	
}

void CDialogDisplayImage::OnImageLhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	double hmax=0.523;
	double hmin=-0.523;
	//Get the Lab data image_double from
    //RGB data rgbimage
	//m_cFeatureVector.m_bBitCount,
    b.rgb2Lab(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,2,BINNUM,false,&hmax,&hmin,true);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"L-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 L-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;	
}

void CDialogDisplayImage::OnImageAhist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no a information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
	DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	double hmax=0.596;
	double hmin=-0.596;
	//Get the Lab data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    b.rgb2Lab(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,1,BINNUM,false,&hmax,&hmin,true);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"a-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 a-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;		
}

void CDialogDisplayImage::OnImageB1hist() 
{
	// TODO: Add your command handler code here
	CRetrieveMethod b;
	CDialogDrawCurve a;
	CDrawCurve c;
	int num;
	if(m_cFeatureVector.m_bBitCount==24)num=3;
	else num=1;
	if(num==1)
	{
	  MessageBox("Sorry, for Gray-scale image,no b information!", "Info", MB_OK|MB_ICONINFORMATION);
	  return;
	}
    DWORD histogram[BINNUM];
	double *data= new double[BINNUM];
	double hmax=0.523;
	double hmin=-0.523;
	//Get the Lab data image_double from
    //RGB data rgbimage
	//,m_cFeatureVector.m_bBitCount
    b.rgb2Lab(rgbimage,image_double,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight);
	b.calculate_histogram(image_double,histogram,m_cFeatureVector.m_lImageWidth,m_cFeatureVector.m_lImageHeight,num,0,BINNUM,false,&hmax,&hmin,true);
	a.m_lNumberofSamples=BINNUM;
	a.m_bSampleDimensions=1;
	for(int i=0;i<BINNUM;i++)
	  data[i]=(double)histogram[i];
	a.m_dDataX=data;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=NULL;
	c.m_DataY=NULL;
	c.m_Dimension=1;
	c.m_Length=BINNUM;
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy(a.cdf.m_sTitles[0],"b-Component Histogram");
	  strcpy(a.cdf.m_sTitles[1],"Fig.1 b-Component Histogram");
	  strcpy(a.cdf.m_sTitles[2],"Bins");
	  strcpy(a.cdf.m_sTitles[3],"Number of Pixels");
	  a.DoModal();
	}
	delete []data;	
}
