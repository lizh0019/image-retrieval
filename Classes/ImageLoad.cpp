// ImageLoad.cpp: implementation of the CImageLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageLoad.h"
#include "math.h"
CImageLoad::CImageLoad()
{
	this->m_bLoadSuccess=false;
	this->m_yB=NULL;
	this->m_yG=NULL;
	this->m_yR=NULL;
	this->m_fH=NULL;
	this->m_fS=NULL;
	this->m_fV=NULL;
}

CImageLoad::~CImageLoad()
{
this->deleteMemory();
}
//Load image by dialog 
bool CImageLoad::LoadImageDialog()
{

	this->deleteMemory();  //delete the memory if needed
	char BASED_CODE szFilter[]="Jpg Files(*.jpg)|*.jpg|Bmp Files(*.bmp)|*.bmp|Gif Files(*.gif)|*.gif|Png Files(*.Png)|*.gif|All Support Files(*.bmp,*.jpg,*.gif,*.png)|*.bmp;*.jpg;*.gif;*.png.*||";
	CFileDialog m_ldFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
		if(m_ldFile.DoModal()!=IDOK)
	{	
			return false;
	}

	this->m_sFileName=m_ldFile.GetPathName();
	return (this->LoadImage(m_sFileName));
}

///delete all memory
void CImageLoad::deleteMemory()
{
//	if (this->m_bLoadSuccess) {
	delete[]this->m_yB;  
	delete[]this->m_yG;
	delete[]this->m_yR;
	delete[]this->m_fH;
	delete[]this->m_fS;
	delete[]this->m_fV;
	this->m_yB=NULL;
	this->m_yG=NULL;
	this->m_yR=NULL;
	this->m_fH=NULL;
	this->m_fS=NULL;
	this->m_fV=NULL;
//	delete[]this->m_yGray;
	this->m_bLoadSuccess=false;
//}

}
//get the gray of GRB 
void CImageLoad::RGBToGray(byte *r, byte *g, byte *b, byte *gray, int height, int width)
{
int size=width*height;  //width and height
for(int i=0;i<size;i++)
		*(gray+i)=(*(r+i)+*(g+i)+*(b+i))/3;
}
//read error or not
BOOL CImageLoad::IsSucceed()
{
return this->m_bLoadSuccess;
}

byte* CImageLoad::GetPixel_R()
{
return this->m_yR;
}
byte* CImageLoad::GetPixel_G()
{
return this->m_yG;
}
byte* CImageLoad::GetPixel_B()
{
return this->m_yB;
}
int CImageLoad::GetWidth()
{
	return this->m_iImageWidth;
}
int CImageLoad::GetHeight()
{
	return this->m_iImageHeight;
}



void CImageLoad::CloseImage()
{
this->deleteMemory();
this->m_bLoadSuccess=false;
}


bool CImageLoad::RGBToHSI(byte *r, byte *g, byte *b, float *h, float *s, float *v, int heigth, int width)
{

if (heigth<0||width<0) {
	return false;
}
int varible;
for(varible=0;varible<width*heigth;varible++)
	{
		v[varible]=(float)max(max(r[varible],g[varible]),b[varible])/255.0;
		if (max(max(r[varible],g[varible]),b[varible])==0) 			s[varible]=0;
		else	    s[varible]=1-((float)(min(min(r[varible],g[varible]),b[varible]))/max(max(r[varible],g[varible]),b[varible]));
		if (s[varible]==0) 			h[varible]=0;
		else
		{
			h[varible]=acosf((float)(2*r[varible]-g[varible]-b[varible])/(2*sqrt((r[varible]-g[varible])*(r[varible]-g[varible])+(r[varible]-b[varible])*(g[varible]-b[varible]))))/(2*PI);
			if (b[varible]>g[varible]) h[varible]=1.0-h[varible];//B>g	
		}
	}
	
return true;
}

float * CImageLoad::GetImageH()
{
return this->m_fH;
}
float * CImageLoad::GetImageS()
{
return this->m_fS;
}
float * CImageLoad::GetImageV()
{
return this->m_fV;
}

bool CImageLoad::LoadImage(CString filename)
{
CImage image;
if(!image.ReadFile(filename))   //load error
	{
		this->m_bLoadSuccess=false;
		return false;
	}
else

	this->m_iImageWidth=image.GetWidth();
	this->m_iImageHeight=image.GetHeight();
	long int imagesize=m_iImageWidth*m_iImageHeight;
	this->deleteMemory();
	m_fH=new float [imagesize];
	m_fS=new float [imagesize];
	m_fV=new float [imagesize];
	this->m_yR=new byte[imagesize];
	this->m_yG=new byte[imagesize];
	this->m_yB=new byte[imagesize];
	if (image.GetAllRGB((BYTE *)m_yR,(BYTE *)m_yG,(BYTE *)m_yB,m_iImageHeight,m_iImageWidth)==false) 	return false;   //read error
	this->m_bLoadSuccess=TRUE;
//	if (this->RGBToHSI(m_yR,m_yG,m_yB,this->m_fH,m_fS,m_fV,m_iImageHeight,m_iImageWidth)==false)  return false;
	return TRUE;
}
