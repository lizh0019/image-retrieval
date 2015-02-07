// CRetrieveMethod.cpp: implementation of the CCRetrieveMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VqRetrieve.h"
#include "CRetrieveMethod.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRetrieveMethod::CRetrieveMethod()
{

}

CRetrieveMethod::~CRetrieveMethod()
{

}

/*****************************************
        *
        *   Public function: get_data_from_24or8bits_bmp_file(...
        *
		*  Get the one-dimenaional array of image's RGB Data
        * (24 bits) or Gray-level Data(8 bits) 
        * from the whole image file in BMP-type
        *  input: -bmpimagefile,the whole bmp-typed image file data
        *  output: -imagedata, the 1-D array of RGB or Gray Data
        * -width,the width of the bmp image
        * -height,the height of the bmp image 
        * -bits, 8 or 24
******************************************/
void CRetrieveMethod::get_data_from_24or8bits_bmp_file(BYTE *bmpimagefile,BYTE *imagedata,WORD bits,LONG width,LONG height)
{
  LONG i,p,q,linebytes;
  
  //The errors
  if(imagedata==NULL||bmpimagefile==NULL)return;
  if(height<=0||width<=0)return;
  
  //Get the bytes for each image line
  if(bits==24)//for 24bits color image
    linebytes=(width*24+31)/32*4;
  else if(bits==8)//for gray image
	linebytes=(width+3)/4*4;
  else
	return;
  
  //Copy the data for each image line
  for(i=0;i<height;i++)
  {
	if(bits==24)//for 24bits bmp image
	{
	  p=(i*width)*3;
      q=54+(height-i-1)*linebytes;
	  memcpy(imagedata+p,bmpimagefile+q,3*width);
	}
	else if(bits==8)//for gray bmp image
	{
      p=i*width;
	  q=1078+(height-i-1)*linebytes;
	  memcpy(imagedata+p,bmpimagefile+q,width);
	}
  }
}

/*****************************************
        *
        *   Public function: g2rgb(...
        *
        *   
        *  Convert the whole input gray image from 8 bits image
		*  to r=g=b 24bits image
		*  input: -gray_image_byte: 8 bits gray-level image(G(0-255) G G G...)
		*  -height: the height of the image
        *  -width: the width of the image
        *  output: -rgb_image_byte: 24bits RGB-style image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
******************************************/
void CRetrieveMethod::g2rgb(BYTE *gray_image_byte,BYTE *rgb_image_byte,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      p=i*width+j;
	  rgb_image_byte[p+p+p]=gray_image_byte[p];
	  rgb_image_byte[p+p+p+1]=gray_image_byte[p];
	  rgb_image_byte[p+p+p+2]=gray_image_byte[p];
	}
  }
}

/*****************************************
        *
        *   Public function: rgb2hsv(...
        *
        *   
        *  Convert the whole input image from rgb to hsv 
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: HSV image 
		*  (V(0-1) S(0-1) H(0-1) V S H V S H...)
        //Hint: H has be changed from (0-360) to (0-1)
******************************************/
void CRetrieveMethod::rgb2hsv(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	p=0;
	for(j=0;j<width;j++)
	{
      p=(i*width+j)*3;
      rgb2hsv_component(image_byte+p,image_double+p);
	}
	p=0;
  }
}
/*****************************************
        *
        *   Public function: rgb2hcv(...
        *
        *   
        *  Convert the whole input image from rgb to hcv
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: HCV image 
		*  (related to 24bits RGB image)
		*  (V C H V C H V C H...)
******************************************/
void CRetrieveMethod::rgb2hcv(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
		p=(i*width+j)*3;
        rgb2hcv_component(image_byte+p,image_double+p);
	}
  }
}

/*****************************************
        *
        *   Public function: rgb2Lab(...
        *
        *   
        *  Convert the whole input image from rgb to Lab
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: Lab image 
		*  (related to 24bits RGB image)
		*  (b a L b a L b a L...)
******************************************/
void CRetrieveMethod::rgb2Lab(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
		p=(i*width+j)*3;
        rgb2Lab_component(image_byte+p,image_double+p);
	}
  }

}
/*****************************************
        *
        *   Public function: rgb2YCbCr(...
        *
        *   
        *  Convert the whole input image from rgb to YCbCr
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: YCbCr image 
		*  (related to 24bits RGB image)
		*  (Cr(16-240) Cb(16-240) Y(16-235) Cr Cb Y Cr Cb Y...)
******************************************/
void CRetrieveMethod::rgb2YCbCr(BYTE *image_byte,BYTE *image_outbyte,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2YCbCr_component(image_byte+p,image_outbyte+p);
	}
  }

}
/*****************************************
        *
        *   Public function: rgb2YCbCr(...
        *
        *   
        *  Convert the whole input image from rgb to YCbCr
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: YCbCr image 
		*  (related to 24bits RGB image)
		*  (Cr(16-240) Cb(16-240) Y(16-235) Cr Cb Y Cr Cb Y...)/255.0
******************************************/
void CRetrieveMethod::rgb2YCbCr(BYTE *image_byte,double *image_outbyte,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2YCbCr_component(image_byte+p,image_outbyte+p);
	}
  }

}
/*****************************************
        *
        *   Public function: rgb2YIQ(...
        *
        *   
        *  Convert the whole input image from rgb to YIQ
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: HCV image 
		*  (related to 24bits RGB image)
		*  (Q I Y Q I Y Q I Y...)
        //Y(0-1) I(-0.596 - 0.596)  Q(-0.523-  0.523)
******************************************/
void CRetrieveMethod::rgb2YIQ(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
		p=(i*width+j)*3;
        rgb2YIQ_component(image_byte+p,image_double+p);
	}
  }
}

/*****************************************
        *
        *   Public function: rgb2I1I2I3(...
        *
        *   
        *  Convert the whole input image from rgb to I1I2I3
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: I1I2I3 image 
		*  (related to 24bits RGB image)
		*  (I3 I2 I1 I3 I2 I1 I3 I2 I1...)
        //I1(0-1) I2(-0.5 +0.5)  I3(-0.5  +0.5)
******************************************/
void CRetrieveMethod::rgb2I1I2I3(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
        p=(i*width+j)*3;
        rgb2I1I2I3_component(image_byte+p,image_double+p);
	}
  }
}

/*****************************************
        *
        *   Public function: rgb2I1_I2_I3(...
        *
        *   
        *  Convert the whole input image from rgb to I1'I2'I3'
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: I1'I2'I3' image 
		*  (related to 24bits RGB image)
		*  (I3' I2' I1' I3' I2' I1' I3' I2' I1'...)
        //I1'(0-1) I2'(-1 +1)  I3'(-1  +1)
******************************************/
void CRetrieveMethod::rgb2I1_I2_I3(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2I1_I2_I3_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2L1L2L3(...
        *
        *   
        *  Convert the whole input image from rgb to L1l2l3
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: l1l2L3 image 
		*  (related to 24bits RGB image)
		*  (L3 L2 L1 L3 L2 L1 L3 L2 L1...)
        
******************************************/
void CRetrieveMethod::rgb2L1L2L3(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2L1L2L3_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2XYZ(...
        *
        *   
        *  Convert the whole input image from rgb to XYZ
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: XYZ image 
		*  (related to 24bits RGB image)
		*  (Z Y X Z Y X Z Y X...)
        
******************************************/
void CRetrieveMethod::rgb2XYZ(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2XYZ_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2xyY(...
        *
        *   
        *  Convert the whole input image from rgb to xyY
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: xyY image 
		*  (related to 24bits RGB image)
		*  (Y y x Y y x Y y x...)
        
******************************************/
void CRetrieveMethod::rgb2xyY(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2xyY_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2UVW(...
        *
        *   
        *  Convert the whole input image from rgb to UVW
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: UVW image 
		*  (related to 24bits RGB image)
		*  (W V U W V U W V U...)
        
******************************************/
void CRetrieveMethod::rgb2UVW(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2UVW_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2YUV(...
        *
        *   
        *  Convert the whole input image from rgb to YUV
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: YUV image 
		*  (related to 24bits RGB image)
		*  (V U Y V U Y V U Y...)
        
******************************************/
void CRetrieveMethod::rgb2YUV(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2YUV_component(image_byte+p,image_double+p);
	}
  }
}

/*****************************************
        *
        *   Public function: rgb2RGBY(...
        *
        *   
        *  Convert the whole input image from rgb to RGBY
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: I1I2I3 image 
		*  (related to 24bits RGB image)
		*  (BY GY RY BY GY RY BY GY RY ...)
        //RY (0-1) GY (-1 +1) BY(-1  +1)
******************************************/
void CRetrieveMethod::rgb2RGBY(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
		p=(i*width+j)*3;
        rgb2RGBY_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2hls(...
        *
        *   
        *  Convert the whole input image from rgb to hls
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: hls image 
		*  (related to 24bits RGB image)
		*  (s l h s l h s l h...)
        
******************************************/
void CRetrieveMethod::rgb2hls(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2hls_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2hsi(...
        *
        *   
        *  Convert the whole input image from rgb to hsi
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: hsi image 
		*  (related to 24bits RGB image)
		*  (i s h i s h i s h...)
        
******************************************/
void CRetrieveMethod::rgb2hsi(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2hsi_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2hsb(...
        *
        *   
        *  Convert the whole input image from rgb to hsb
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: hsb image 
		*  (related to 24bits RGB image)
		*  (b s h b s h b s h...)
        
******************************************/
void CRetrieveMethod::rgb2hsb(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2hsb_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2Luv(...
        *
        *   
        *  Convert the whole input image from rgb to Luv
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: Luv image 
		*  (related to 24bits RGB image)
		*  (v u L v u L v u L...)
        
******************************************/
void CRetrieveMethod::rgb2Luv(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2Luv_component(image_byte+p,image_double+p);
	}
  }
}
/*****************************************
        *
        *   Public function: rgb2YES(...
        *
        *   
        *  Convert the whole input image from rgb to YES
        *  input: -image_byte: 24bits RGB-style BMP image in a
		*  1-D array (B(0-255) G(0-255) R(0-255) B G R...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: YES image 
		*  (related to 24bits RGB image)
		*  (S E Y S E Y S E Y...)
        //Y: 0- 1  E: -0.5- +0.5 S: -0.5- +0.5
******************************************/
void CRetrieveMethod::rgb2YES(BYTE *image_byte,double *image_double,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2YES_component(image_byte+p,image_double+p);
	}
  }
}

/*****************************************
        *
        *   Public function: compute_color_histogram_feature_vector(...
        *
        *   
   //input: -rgbimage(The rgb-style image)
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-bits, 8 or 24
   //-description 0 hist  1 a-hist
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   //-bins, number of bins used for histogram
   //output: hist_feature, dimension is bins or bins*3, each dimension value is normalized: 0.0-1.0
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //>0 method error
******************************************/
int CRetrieveMethod::compute_color_histogram_feature_vector(BYTE *rgb_or_gimage,double *hist_feature,bool smooth, BYTE description,BYTE colorspace,WORD bins,WORD bits,LONG width,LONG height)
{
	if(rgb_or_gimage==NULL||hist_feature==NULL)return -1;//memory error
	if(description!=0&&description!=1)return -2;//hist or accum_hist
	if(colorspace<0||colorspace>25)return -2;//color space type error
	//bins setting error
	if(bins!=MAX_HISTOGRAM_BIN&&bins!=MAX_HISTOGRAM_BIN/2&&bins!=MAX_HISTOGRAM_BIN/4&&bins!=MAX_HISTOGRAM_BIN/8)return -2;
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<100||width>2000)return -2;
	//height error
	if(height<100||height>2000)return -2;
	
	//temp double image
	double *image_double=new double[width*height*3]; 
	if(image_double==NULL)return -1;//memory error
	
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_double;
		return -1;//memory error
	}
	double max[3],min[3];
	WORD i,j;
	for(i=0;i<3;i++)
	{
	  max[i]=1.0;
	  min[i]=0.0;
	}
	ColorSpaceTransfer(rgb_or_gimage,rgb_image_byte,bits,colorspace,image_double,width,height,max,min);
	delete [] rgb_image_byte;

	DWORD sum;
	int a;
	// histograms for three color component
	DWORD hist[3*MAX_HISTOGRAM_BIN];
	//The inital return value
	a=0;
	switch(colorspace)
	{
	    case 6://Y  0-255 /255.0
		case 7://H  0-1
		case 10://R  0-255/255.0
			a=calculate_histogram(image_double,hist,width,height,3,2,bins,smooth);
			break;
	    case 8://S  0-1
	    case 11://G  0-255/ 255.0
			a=calculate_histogram(image_double,hist,width,height,3,1,bins,smooth);
			break;
		case 9://V  0-1
		case 12://B  0-255/ 255.0
			a=calculate_histogram(image_double,hist,width,height,3,0,bins,smooth);
			break;
		default:
		    for(i=0;i<3;i++)
	          a+=calculate_histogram(image_double,hist+i*bins,width,height,3,i,bins,smooth,max+i,min+i,false);
	   	break;	
	}

	if(colorspace<=5||colorspace>12)
	{
	   if(description==1)
	   {
	     for(j=0;j<3;j++)
		 {
	       sum=0;
	       for(i=0;i<bins;i++)
		   {
 		      sum=sum+hist[i+j*bins];
		      hist_feature[i+j*bins]=(double)sum/(double)width/(double)height;
		   }
		 }
	   }
	   else
	   {
	     for(i=0;i<bins*3;i++)
	 	   hist_feature[i]=(double)hist[i]/(double)width/(double)height;
	   }
	}
	else
	{
	  if(description==1)
	  {
	    sum=0;
	    for(i=0;i<bins;i++)
		{
 		  sum=sum+hist[i];
		  hist_feature[i]=(double)sum/(double)width/(double)height;
		}
	  }
	  else
	  {
	    for(i=0;i<bins;i++)
	 	  hist_feature[i]=(double)hist[i]/(double)width/(double)height;	
	  }
	}
	delete [] image_double;
	return a;
}


/*****************************************
        *
        *   Public function: compute_haar_integral_invariant_feature_vector(...
        *
        *   
   //input: -rgbimage(The rgb-style image)
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-bits, 8 or 24
   //-points, the number of translated pixels
   //-angles, the number of angles
   //-description 0 global 1 hist 2 a-hist
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   //(if bits=8 only Y-Gray)
   //-bins, number of bins used for histogram
   //output: haar_integral_feature, dimension is 1,3, bins or bins*3, each dimension value is normalized: 0.0-1.0
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //>0 method error
******************************************/
int CRetrieveMethod::compute_haar_integral_invariant_feature_vector(BYTE *rgb_or_gimage,double *haar_integral_feature,DWORD points,WORD angles,bool smooth,BYTE description,BYTE colorspace,WORD bins,WORD bits,LONG width,LONG height)
{
	if(rgb_or_gimage==NULL||haar_integral_feature==NULL)return -1;//memory error
	if(description!=0&&description!=1&&description!=2)return -2;//global, hist or accum_hist
	if(colorspace<0||colorspace>25)return -2;//color space type error
	//bins setting error
	if(bins!=MAX_HISTOGRAM_BIN&&bins!=MAX_HISTOGRAM_BIN/2&&bins!=MAX_HISTOGRAM_BIN/4&&bins!=MAX_HISTOGRAM_BIN/8)return -2;
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<100||width>2000)return -2;
	//height error
	if(height<100||height>2000)return -2;
	//points error
	if(points!=(DWORD)(width*height)&&points!=(DWORD)(width*height/2)&&points!=(DWORD)(width*height/4)&&points!=(DWORD)(width*height/8)&&points!=1000&&points!=2000&&points!=4000)return -2;
	//angles error
	int a,j;
	a=0;
	for(j=0;j<23;j++)
	{
	   if(angles==Angles[j])a=1;
	}
	if(a==0)return -2;
    
	//temp double image
	double *image_double=new double[width*height*3]; 
	if(image_double==NULL)return -1;//memory error
	//temp byte image
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_double;
		return -1;//memory error
	}
	int i;
	double sum1,max[3],min[3];
	for(i=0;i<3;i++)
	{
	  max[i]=1.0;
	  min[i]=0.0;
	}
	//color space convert
	ColorSpaceTransfer(rgb_or_gimage,rgb_image_byte,bits,colorspace,image_double,width,height,max,min);
	delete [] rgb_image_byte;
	
	double *image_medium=new double[points*angles*3];
	if(image_medium==NULL)
	{
	    delete [] image_double;
		return -1;//memory error
	}
	DWORD sum,hist[3*MAX_HISTOGRAM_BIN];// histograms for three color component

	//Get the medium image
	a=0;
	if(colorspace<=5||colorspace>12)
	{
	  for(j=0;j<3;j++)
	   a+=get_medium_image_for_haar_invariant_feature(image_double,image_medium+j*points*angles,points,angles,j,width,height,max[i],min[i]);
	}
	else if(colorspace==6||colorspace==7||colorspace==10)
	  a+=get_medium_image_for_haar_invariant_feature(image_double,image_medium,points,angles,2,width,height,max[2],min[2]);
	else if(colorspace==8||colorspace==11)
	  a+=get_medium_image_for_haar_invariant_feature(image_double,image_medium,points,angles,1,width,height,max[1],min[1]);
	else if(colorspace==9||colorspace==12)
      a+=get_medium_image_for_haar_invariant_feature(image_double,image_medium,points,angles,0,width,height,max[0],min[0]);
    
	//get the histogram
	if(description!=0)
	{
	   if(colorspace<=5||colorspace>12)
	   {
	     for(j=0;j<3;j++)
	       a+=calculate_histogram(image_medium,hist+j*bins,points,angles,3,j,bins,smooth);
	   }
	   else if(colorspace==6||colorspace==7||colorspace==10)
	     a+=calculate_histogram(image_medium,hist,points,angles,1,0,bins,smooth);
	   else if(colorspace==8||colorspace==11)
	     a+=calculate_histogram(image_medium,hist,points,angles,1,0,bins,smooth);
	   else if(colorspace==9||colorspace==12)
         a+=calculate_histogram(image_medium,hist,points,angles,1,0,bins,smooth);
	}

    if(colorspace<=5||colorspace>12)
	{
	   if(description==2)
	   {
	     for(j=0;j<3;j++)
		 {
	      sum=0;
	      for(i=0;i<bins;i++)
		  {
 		    sum=sum+hist[i+j*bins];
		    haar_integral_feature[i+j*bins]=(double)sum/(double)width/(double)height;
		  }
		 }
	   }
	   else if(description==1)
	   {
	     for(i=0;i<bins*3;i++)
	 	   haar_integral_feature[i]=(double)hist[i]/(double)width/(double)height;	
	   }
	   else
	   {
	     for(i=0;i<3;i++)
		 {
		   sum1=0.0;
		   for(j=0;j<(int)(points*angles);j++)
		   {
 		    sum1=sum1+image_medium[j+i*points*angles];
		    haar_integral_feature[i]=sum1/(double)points/(double)angles;
		   }
		 }
	   }
	}
	else
	{
	  if(description==2)
	  {
	    sum=0;
	    for(i=0;i<bins;i++)
		{
 		  sum=sum+hist[i];
		  haar_integral_feature[i]=(double)sum/(double)width/(double)height;
		}
	  }
	  else if(description==1)
	  {
	    for(i=0;i<bins;i++)
	 	  haar_integral_feature[i]=(double)hist[i]/(double)width/(double)height;	
	  }
	  else
	  {
	    sum1=0.0;
	    for(j=0;j<(int)(points*angles);j++)
		{
 		  sum1=sum1+image_medium[j];
		  haar_integral_feature[0]=sum1/(double)points/(double)angles;
		}
	  }
	}
	delete [] image_double;
	delete [] image_medium;
	return a;
}


/*****************************************
        *
        *   Public function: get_medium_image_for_haar_invariant_feature(...
        *
        *   f(M)=sqrt(M(4,0)*M(0,8)
   //input: -inputimage(The double-style image)
   //-width,the width of the input image
   //-height,the height of the input image 
   //-whichch, 0,1 or 2
   //-points, the number of translated pixels
   //-angles, the number of angles
   //output: -outputimage, the output medium image
   //return 0 success
   //return 1 error
******************************************/
int CRetrieveMethod::get_medium_image_for_haar_invariant_feature(double *inputimage,double *outputimage,DWORD points,WORD angles,BYTE whichch,LONG width,LONG height,double min,double max)
{
   	LONG shiftx,shifty;
	if(inputimage==NULL||outputimage==NULL)return 1;
	if(points!=(DWORD)(width*height)&&points!=(DWORD)(width*height/2)&&points!=(DWORD)(width*height/4)&&points!=(DWORD)(width*height/8)&&points!=1000&&points!=2000&&points!=4000)return 1;
	if(whichch!=0&&whichch!=1&&whichch!=2)return 1;
	int i,j,a=0;
	for(j=0;j<23;j++)
	{
	  if(angles==Angles[j])a=1;
	}
	if(a==0)return 1;
	//width error
	if(width<100||width>2000)return 1;
	//height error
	if(height<100||height>2000)return 1;
	LONG length,n;
	length=width*height;
	//normalized to be -1.0  to 1.0
	if(max!=1&&min!=0)
	{
	  for(j=0;j<length;j++)
		inputimage[j]=(inputimage[j*3+whichch]-min)/(max-min);
	}

	//srand((unsigned)time(NULL));
	for(j=0;j<(int)points;j++)
	{
	   if(points==(DWORD)(length))
	   {
		 for(i=0;i<angles;i++)
	       get_bilinear_interpolated_function_value(inputimage,outputimage+j*angles+i,whichch,(360/angles)*i,j%width,j/width,width,height);	
	   }
	   else if(points==(DWORD)(length/2))
	   {
		 for(i=0;i<angles;i++)
	       get_bilinear_interpolated_function_value(inputimage,outputimage+j*angles+i,whichch,(360/angles)*i,(j*2)%width,(j*2)/height,width,height);	
	   }
	   else if(points==(DWORD)(length/4))
	   {
		 for(i=0;i<angles;i++)
	       get_bilinear_interpolated_function_value(inputimage,outputimage+j*angles+i,whichch,(360/angles)*i,(j*2)%width,(j*4)/height,width,height);	
	   }
	   else if(points==(DWORD)(length/8))
	   {
		 for(i=0;i<angles;i++)
	       get_bilinear_interpolated_function_value(inputimage,outputimage+j*angles+i,whichch,(360/angles)*i,(j*8)%width,(j*8)/width,width,height);	
	   }
	   else
	   {
	      //shiftx=(LONG)((double)rand()/(double)RAND_MAX*(width-1));
		  //shifty=(LONG)((double)rand()/(double)RAND_MAX*(height-1));
		  n=j*(length/points);
	      shiftx=(LONG)(n%width);
		  shifty=(LONG)(n/height);
	      for(i=0;i<angles;i++)
		  	get_bilinear_interpolated_function_value(inputimage,outputimage+j*angles+i,whichch,(360/angles)*i,shiftx,shifty,width,height);
	   }
	}
    return 0;
}

void CRetrieveMethod::get_bilinear_interpolated_function_value(double *inputimage,double *returnvalue,BYTE whichch,WORD angle,LONG shiftx,LONG shifty,LONG width,LONG height)
{
   int i;
   double newposix,newposiy,x,y;
   double value[4];
   LONG posix[4],posiy[4];
   
   //for M(4,0)
   newposix=4*cos(angle)+shiftx;
   newposiy=shifty-4*sin(angle);
   while(newposix>width-1)newposix-=width;
   while(newposiy>height-1)newposiy-=height;
   while(newposix<0)newposix+=width;
   while(newposiy<0)newposiy+=height;
   x=newposix-(double)((LONG)newposix);
   y=newposiy-(double)((LONG)newposiy);
   posix[0]=(LONG)newposix;
   posix[1]=(LONG)newposix+1;
   while(posix[0]<0)posix[0]+=width;
   while(posix[0]>width-1)posix[0]-=width;
   while(posix[1]<0)posix[1]+=width;
   while(posix[1]>width-1)posix[1]-=width;
   posix[2]=posix[0];
   posix[3]=posix[1];

   posiy[0]=(LONG)newposiy;
   posiy[2]=(LONG)newposiy+1;
   while(posiy[0]<0)posiy[0]+=height;
   while(posiy[0]>height-1)posiy[0]-=height;
   while(posiy[2]<0)posiy[2]+=height;
   while(posiy[2]>height-1)posiy[2]-=height;
   posiy[1]=posiy[0];
   posiy[3]=posiy[2];
   for(i=0;i<4;i++)
     value[i]=inputimage[(posix[i]+posiy[i]*width)*3+whichch];
   returnvalue[0]=calculate_bilinear_interpolation_value(value,x,y);
   
   //for M(0,8)
   newposix=8*sin(angle)+shiftx;
   newposiy=shifty+8*cos(angle);
   while(newposix>width-1)newposix-=width;
   while(newposiy>height-1)newposiy-=height;
   while(newposix<0)newposix+=width;
   while(newposiy<0)newposiy+=height;
   x=newposix-(double)((LONG)newposix);
   y=newposiy-(double)((LONG)newposiy);
   posix[0]=(LONG)newposix;
   posix[1]=(LONG)newposix+1;
   while(posix[0]<0)posix[0]+=width;
   while(posix[0]>width-1)posix[0]-=width;
   while(posix[1]<0)posix[1]+=width;
   while(posix[1]>width-1)posix[1]-=width;
   posix[2]=posix[0];
   posix[3]=posix[1];

   posiy[0]=(LONG)newposiy;
   posiy[2]=(LONG)newposiy+1;
   while(posiy[0]<0)posiy[0]+=height;
   while(posiy[0]>height-1)posiy[0]-=height;
   while(posiy[2]<0)posiy[2]+=height;
   while(posiy[2]>height-1)posiy[2]-=height;
   posiy[1]=posiy[0];
   posiy[3]=posiy[2];
   for(i=0;i<4;i++)
     value[i]=inputimage[(posix[i]+posiy[i]*width)*3+whichch];
   returnvalue[0]*=calculate_bilinear_interpolation_value(value,x,y);
   returnvalue[0]=sqrt(returnvalue[0]);
}

double CRetrieveMethod::calculate_bilinear_interpolation_value(double *value,double x,double y)
{
   double mvalue1,mvalue2,returnvalue;
   mvalue1=value[0]*(1.0-x)+value[1]*x;
   mvalue2=value[2]*(1.0-x)+value[3]*x;
   returnvalue=mvalue1*(1.0-y)+mvalue2*y;
   return returnvalue;
}

/*****************************************
        *
        *   Public function: compute_texture_feature_vector(...
        *
        *   
   //input: -rgb_or_gimage(The rgb-style image or gray-level image)
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-bits, 8 or 24
   //-description 
0.64Bin Histogram Moment(3/Color)
1.Coocurency Matrix(5/Color)
2.Coocurency Matrix(10/Color)
3.Coocurency Matrix(14/Color)
4.Texture Energy
5.Contrast+Coarseness+Directionality
6.Repetitiveness+Directionality+Complexity
7. (0+4+5+6) 
8. (0+3+4+5)
9. (0+3+4+6)
10. (0+3+4+5+6)
11.DFT Spectrum
12.DWT Spectrum
13.MPEG Spectrum
14.Structural
  //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: texture_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //1 method error
******************************************/
int CRetrieveMethod::compute_texture_feature_vector(BYTE *rgb_or_gimage,double *texture_feature,BYTE description,BYTE colorspace,BYTE Coocurrence,WORD bits,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
	if(rgb_or_gimage==NULL||texture_feature==NULL)return -1;//memory error
	if(description<0||description>10)return -2;//hist or accum_hist
	if(colorspace<0||colorspace>25)return -2;//color space type error
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<100||width>2000)return -2;
	//height error
	if(height<100||height>2000)return -2;
	//temp double image
	double *image_double=new double[width*height*3]; 
	if(image_double==NULL)return -1;//memory error
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_double;
		return -1;//memory error
	}
	double max[3],min[3];
	int i;
	WORD CheckThisDimension,TmpDimension;
	int a=0;
	for(i=0;i<3;i++)
	{
	  max[i]=1.0;
	  min[i]=0.0;
	}
	ColorSpaceTransfer(rgb_or_gimage,rgb_image_byte,bits,colorspace,image_double,width,height,max,min);
	delete [] rgb_image_byte;
	CheckThisDimension=0;
	switch(description)
	{
	  case 0://64Bin Histogram Moment(3/Color)
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_64bin_histogram_moments_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 1://Coocurency Matrix(5/Color)
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=5;
		else
		  CheckThisDimension=15;
		a=compute_coocurency_matrix_based_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 2://Coocurency Matrix(10/Color)
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=10;
		else
		  CheckThisDimension=30;
		a=compute_coocurency_matrix_based_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 3://Coocurency Matrix(15/Color)
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=15;
		else
		  CheckThisDimension=45;
		a=compute_coocurency_matrix_based_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 4://Texture Energy
		if(colorspace>=6&&colorspace<=12)
		   CheckThisDimension=1;
		else
		   CheckThisDimension=3;
		a=compute_texture_energy_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 5://Contrast+Coarseness+Directionality
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_CCD_texture_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 6://Repetitiveness+Directionality+Complexity
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_RDC_texture_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 7://(0+4+5+6) 
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_64bin_histogram_moments_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		if(colorspace>=6&&colorspace<=12)
		   TmpDimension=1;
		else
		   TmpDimension=3;
		a=compute_texture_energy_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=3;
		else
		  TmpDimension=9;
		a=compute_CCD_texture_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=3;
		else
		  TmpDimension=9;
		a=compute_RDC_texture_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
	  case 8://(0+3+4+5)
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_64bin_histogram_moments_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=15;
		else
		  TmpDimension=45;
		a=compute_coocurency_matrix_based_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
		if(colorspace>=6&&colorspace<=12)
		   TmpDimension=1;
		else
		   TmpDimension=3;
		a=compute_texture_energy_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=3;
		else
		  TmpDimension=9;
		a=compute_CCD_texture_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
	  case 9://(0+3+4+6)
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_64bin_histogram_moments_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=15;
		else
		  TmpDimension=45;
		a=compute_coocurency_matrix_based_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
		if(colorspace>=6&&colorspace<=12)
		   TmpDimension=1;
		else
		   TmpDimension=3;
		a=compute_texture_energy_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=3;
		else
		  TmpDimension=9;
		a=compute_RDC_texture_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
        break;
	  case 10://(0+3+4+5+6)
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_64bin_histogram_moments_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=15;
		else
		  TmpDimension=45;
		a=compute_coocurency_matrix_based_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
		if(colorspace>=6&&colorspace<=12)
		   TmpDimension=1;
		else
		   TmpDimension=3;
		a=compute_texture_energy_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=3;
		else
		  TmpDimension=9;
		a=compute_CCD_texture_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=3;
		else
		  TmpDimension=9;
		a=compute_RDC_texture_feature_vector(image_double,texture_feature,colorspace,width,height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
	  case 11://DFT Spectrum
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_DFT_spectrum_texture_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		  break;
	  case 12://DWT Spectrum
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_DWT_spectrum_texture_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		  break;
	  case 13://MPEG Spectrum
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_MPEG_spectrum_texture_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		  break;
	  case 14://Structural
	   if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_structural_texture_feature_vector(image_double,texture_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		  break;
	  default:
		break;
	}
    delete [] image_double;
    if(CheckThisDimension!=thisdimension)a=-2;
	return a;
}

/*****************************************
        *
        *   Public function: compute_64bin_histogram_moments_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: histmoment_feature
   //return 0 success
   //return 1 method error
   
******************************************/
int CRetrieveMethod::compute_64bin_histogram_moments_feature_vector(double *image_double,double *histmoment_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  	int i,j,a=0;
	double mean, tmp,tmp1;
	double max[3],min[3];
    DWORD hist[192];
	for(i=0;i<3;i++)
	{
		max[i]=1.0;
	    min[i]=0.0;
	}
	switch(colorspace)
	{
	    case 2://HCV  ???????????
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 3://Lab  L:0-100  a,b -120- 120
			max[0]=120;max[1]=120;max[2]=100;min[0]=-120;min[1]=-120;min[2]=0;
			break;
		case 5://YIQ  Y 0-1 I -0.596-0.596  Q -0.523-0.523
			max[0]=0.523;max[1]=0.596;max[2]=1.0;min[0]=-0.523;min[1]=-0.596;min[2]=0;
			break;
		case 6://Y  0-255 /255.0
		case 7://H  0-1
		case 10://R  0-255/255.0
			if(calculate_histogram(image_double,hist,width,height,3,2,64,false)!=0)
			 a=1;
			break;
	    case 8://S  0-1
	    case 11://G  0-255/ 255.0
			if(calculate_histogram(image_double,hist,width,height,3,1,64,false)!=0)
			 a=1;
			break;
		case 9://V  0-1
		case 12://B  0-255/ 255.0
			if(calculate_histogram(image_double,hist,width,height,3,0,64,false)!=0)
			  a=1;
			break;
		case 13://I1I2I3  I1 0-1  I2 -0.5-0.5 I3 -0.5-+0.5
			max[0]=0.5;max[1]=0.5;max[2]=1.0;min[0]=-0.5;min[1]=-0.5;min[2]=0;
			break;
		case 14://I1'I2'I3'(Bimbo,1999),
			max[0]=1.0;max[1]=1.0;max[2]=1.0;min[0]=-1.0;min[1]=-1.0;min[2]=0.0;
			break;
		case 15://L1L2L3(Gevers,1999)
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 16://CIE_XYZ
		    max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 17://CIE_YUV
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 18://CIE_xyY
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 19://CIE_U'V'W'
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 20://RGB_Y
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 21://YES(Saber,1998)
			max[0]=0.5;max[1]=0.5;max[2]=1.0;min[0]=-0.5;min[1]=-0.5;min[2]=0;
			break;
		case 22://HLS
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 23://HSI
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 24://HSB
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		case 25://CIE_Luv
			max[0];max[1];max[2];min[0];min[1];min[2];
			break;
		default:
			break;	
	}
	if(colorspace<=5||colorspace>12)
	{
	        for(i=0;i<3;i++)
			{
			  if(calculate_histogram(image_double,hist+i*64,width,height,3,i,64,false,max+i,min+i,false)!=0)
			    a=1;
			  mean=0.0;
		      for(j=0;j<64;j++)
		        mean+=j*hist[i*64+j]/(double)width/(double)height;
		      mean/=64.0;
	          histmoment_feature[i*3]=0.0;
		      histmoment_feature[i*3+1]=0.0;
		      histmoment_feature[i*3+2]=0.0;
		      for(j=0;j<64;j++)
			  {
		         tmp1=j/64.0-mean;
			     tmp=tmp1*tmp1;
			     tmp=tmp*hist[i*64+j]/(double)width/(double)height;
			     histmoment_feature[i*3]+=tmp;
			     tmp=tmp*tmp1;
			     histmoment_feature[i*3+1]+=tmp;
			     tmp=tmp*tmp1;
			     histmoment_feature[i*3+2]+=tmp;
			  }
			}
	}
	else
    {
   	      mean=0.0;
		  for(j=0;j<64;j++)
		     mean+=j*hist[j]/(double)width/(double)height;
		  mean/=64.0;
	      histmoment_feature[0]=0.0;
		  histmoment_feature[1]=0.0;
		  histmoment_feature[2]=0.0;
		  for(j=0;j<64;j++)
		  {
		     tmp1=j/64.0-mean;
			 tmp=tmp1*tmp1;
			 tmp=tmp*hist[j]/(double)width/(double)height;
			 histmoment_feature[0]+=tmp;
			 tmp=tmp*tmp1;
			 histmoment_feature[1]+=tmp;
			 tmp=tmp*tmp1;
			 histmoment_feature[2]+=tmp;
		  }
   }
	*dimensionused+=thisdimension;
    return a;
}

/*****************************************
        *
        *   Public function: compute_coocurency_matrix_based_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: coocmatrix_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_coocurency_matrix_based_feature_vector(double *image_double,double *coocmatrix_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_CCD_texture_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: ccd_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_CCD_texture_feature_vector(double *image_double,double *ccd_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_texture_energy_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: energy_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_texture_energy_feature_vector(double *image_double,double *energy_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_RDC_texture_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: rdc_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_RDC_texture_feature_vector(double *image_double,double *rdc_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_DFT_spectrum_texture_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
    //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: dft_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_DFT_spectrum_texture_feature_vector(double *image_double,double *dft_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_DWT_spectrum_texture_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: dwt_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_DWT_spectrum_texture_feature_vector(double *image_double,double *dwt_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_MPEG_spectrum_texture_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: mpeg_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_MPEG_spectrum_texture_feature_vector(double *image_double,double *mpeg_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}

/*****************************************
        *
        *   Public function: compute_structural_texture_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: structural_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_structural_texture_feature_vector(double *image_double,double *structural_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}

/*****************************************
        *
        *   Public function: compute_shape_feature_vector(...
        *
        *   
   //input: -rgb_or_gimage(The rgb-style image or gray-level image)
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-bits, 8 or 24
   //-description 
       0. 1-D DFT   
       1. Edge Directional Histogram (36-BIN)
       2. Edge Directional Histogram (72-BIN)
       3. Form Factor+Eccentricity+Sphericity
       4. Regional Moment (4-D)
       5. Regional Moment (7-D)
       6. Distorsion Based
       7. (1+4)
       8. (1+5)
       9. (2+4)
       10. (2+5)
  //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: shape_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   ////-3 method error
******************************************/
int CRetrieveMethod::compute_shape_feature_vector(BYTE *rgb_or_gimage,double *shape_feature,BYTE description,BYTE colorspace,WORD bits,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
	if(rgb_or_gimage==NULL||shape_feature==NULL)return -1;//memory error
	if(description<0||description>10)return -2;//hist or accum_hist
	if(colorspace<0||colorspace>25)return -2;//color space type error
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<100||width>2000)return -2;
	//height error
	if(height<100||height>2000)return -2;
	double max[3],min[3];
	//temp double image
	double *image_double=new double[width*height*3]; 
	if(image_double==NULL)return -1;//memory error
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_double;
		return -1;//memory error
	}
	ColorSpaceTransfer(rgb_or_gimage,rgb_image_byte,bits,colorspace,image_double,width,height,max,min);
	delete [] rgb_image_byte;
	int i;
	WORD CheckThisDimension,TmpDimension;
	int a=0;
	for(i=0;i<3;i++)
	{
	  max[i]=1.0;
	  min[i]=0.0;
	}
	CheckThisDimension=0;
	switch(description)
	{
	  case 0://1-D DFT
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=20;
		else
		  CheckThisDimension=60;
		a=compute_1D_DFT_shape_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 1:
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=36;
		else
		  CheckThisDimension=108;
		a=compute_edge_directional_histogram_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 2://
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=72;
		else
		  CheckThisDimension=216;
		a=compute_edge_directional_histogram_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 3://
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=3;
		else
		  CheckThisDimension=9;
		a=compute_FES_shape_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 4://4-D moment/color
		if(colorspace>=6&&colorspace<=12)
		   CheckThisDimension=4;
		else
		   CheckThisDimension=12;
		a=compute_hu_moment_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 5://7-D moment/color
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=7;
		else
		  CheckThisDimension=21;
		a=compute_hu_moment_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 6://distortion
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=10;
		else
		  CheckThisDimension=30;
		a=compute_distortion_shape_feature_vector(image_double,shape_feature,colorspace,width,height,CheckThisDimension,dimensionused);
		break;
	  case 7://36bin EDH + 4-D moment/color
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=36;
		else
		  CheckThisDimension=108;
		a=compute_edge_directional_histogram_feature_vector(image_double,shape_feature,colorspace,width, height,CheckThisDimension,dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=4;
		else
		  TmpDimension=12;
		a=compute_hu_moment_feature_vector(image_double,shape_feature,colorspace, width, height,TmpDimension,dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
	  case 8://36bin EDH + 7-D moment/color
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=36;
		else
		  CheckThisDimension=108;
		a=compute_edge_directional_histogram_feature_vector(image_double,shape_feature,colorspace,width, height,CheckThisDimension, dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=7;
		else
		  TmpDimension=21;
		a=compute_hu_moment_feature_vector(image_double,shape_feature,colorspace,width, height,TmpDimension, dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
	  case 9://72bin EDH + 4-D moment/color
		if(colorspace>=6&&colorspace<=12)
		CheckThisDimension=72;
		else
		CheckThisDimension=216;
		a=compute_edge_directional_histogram_feature_vector(image_double,shape_feature,colorspace,width, height,CheckThisDimension, dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=4;
		else
		  TmpDimension=12;
		a=compute_hu_moment_feature_vector(image_double,shape_feature,colorspace,width, height,TmpDimension, dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
	  case 10://72bin EDH + 7-D moment/color
		if(colorspace>=6&&colorspace<=12)
		  CheckThisDimension=72;
		else
		  CheckThisDimension=216;
		a=compute_edge_directional_histogram_feature_vector(image_double,shape_feature,colorspace,width, height,CheckThisDimension, dimensionused);
		if(colorspace>=6&&colorspace<=12)
		  TmpDimension=7;
		else
		  TmpDimension=21;
		a=compute_hu_moment_feature_vector(image_double,shape_feature,colorspace,width, height,TmpDimension, dimensionused);
		CheckThisDimension+=TmpDimension;
		break;
	  default:
		break;
	}
    delete [] image_double;
    if(CheckThisDimension!=thisdimension)a=-2;
	return a;
}

/*****************************************
        *
        *   Public function: compute_1D_DFT_shape_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: 1ddft_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_1D_DFT_shape_feature_vector(double *image_double,double *ddft_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_FES_shape_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
  //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: fes_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_FES_shape_feature_vector(double *image_double,double *fes_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}
/*****************************************
        *
        *   Public function: compute_edge_directional_histogram_feature_vector(...
        *
        *   
  //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: edh_feature, dimension is bins or bins*3, each dimension value is normalized: 0.0-1.0
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_edge_directional_histogram_feature_vector(double *image_double,double *edh_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
    int a=0;
    *dimensionused+=thisdimension;
    return 0;
}

/*****************************************
        *
        *   Public function: compute_hu_moment_feature_vector(...
        *
        *   
   //input: -image_double
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: hu_moments_feature
   //return 0 success
   //return -3 parameter error
******************************************/
int CRetrieveMethod::compute_hu_moment_feature_vector(double *image_double,double *hu_moments_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
	int i;
	int dimension=0;
	if(thisdimension%7==0)dimension=7;
	else if(thisdimension%4==0)dimension=4;
	if(dimension==0)return -3;
	switch(colorspace)
	{
	    case 6://Y  0-255 /255.0
		  compute_hu_moments(image_double,hu_moments_feature,2,width,height,dimension);
		  break;
		case 7://H  0-1
		case 8://S  0-1
		case 9://V  0-1
		  compute_hu_moments(image_double,hu_moments_feature,9-colorspace,width,height,dimension);
		  break;
		case 10://R  0-255/255.0
		case 11://G  0-255/255.0
		case 12://B  0-255/255.0
		  compute_hu_moments(image_double,hu_moments_feature,12-colorspace,width,height,dimension);
		  break;
		default:
		  for(i=0;i<3;i++)
			compute_hu_moments(image_double,hu_moments_feature+i*dimension,i,width,height,dimension);
		  break;	
	}
	 *dimensionused+=thisdimension;
    return 0;
}


/*****************************************
        *
        *   Public function: ColorSpaceTransfer(...
        *
        *   
   //input: -rgb_or_gimage
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-bits, 8,24
  //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   //output: 
   -image_double
   -max
   -min
******************************************/
void CRetrieveMethod::ColorSpaceTransfer(BYTE *rgb_or_gimage,BYTE *rgb_image_byte,WORD bits,BYTE colorspace, double *image_double,LONG width,LONG height,double *max,double *min)
{
	int i;
	if(bits==8)
	  g2rgb(rgb_or_gimage,rgb_image_byte,width,height);
	else
	  memcpy(rgb_image_byte,rgb_or_gimage,width*height*3);
    switch(colorspace)
	{
	    case 0://RGB
		case 10://R
		case 11://G
		case 12://B
		  for(i=0;i<height*width*3;i++)
		     image_double[i]=(double)rgb_image_byte[i]/255.0;	 
		  break;
	    case 1://HSV, all components range  0-1
		case 7://H
		case 8://S
		case 9://V
		  rgb2hsv(rgb_image_byte,image_double,width,height);
		  break;
		case 2://HCV  ???????????
		  rgb2hcv(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 3://Lab  L:0-100  a,b -120- 120
		  rgb2Lab(rgb_image_byte,image_double,width,height);
		  max[0]=120;max[1]=120;max[2]=100;min[0]=-120;min[1]=-120;min[2]=0;
		  break;
		case 4://YCbCr  Y 0-255  Cb16-240  Cr 16-235   /255.0
		case 6://Y  0-255
		  rgb2YCbCr(rgb_image_byte,image_double,width,height);
		  break;
		case 5://YIQ  Y 0-1 I -0.596-0.596  Q -0.523-0.523
		  rgb2YIQ(rgb_image_byte,image_double,width,height);
		  max[0]=0.523;max[1]=0.596;max[2]=1.0;min[0]=-0.523;min[1]=-0.596;min[2]=0;
		  break;
		case 13://I1I2I3  I1 0-1  I2 -0.5-0.5 I3 -0.5-+0.5
		  rgb2I1I2I3(rgb_image_byte,image_double,width,height);
  		  max[0]=0.5;max[1]=0.5;max[2]=1.0;min[0]=-0.5;min[1]=-0.5;min[2]=0;
		  break;
		case 14://I1'I2'I3'(Bimbo,1999),
		  rgb2I1_I2_I3(rgb_image_byte,image_double,width,height);
		  max[0]=1.0;max[1]=1.0;max[2]=1.0;min[0]=-1.0;min[1]=-1.0;min[2]=0.0;
		  break;
		case 15://L1L2L3(Gevers,1999)
		  rgb2L1L2L3(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 16://CIE_XYZ
		  rgb2XYZ(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 17://CIE_YUV
		  rgb2YUV(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 18://CIE_xyY
		  rgb2xyY(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 19://CIE_U'V'W'
		  rgb2UVW(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 20://RGB_Y
		  rgb2RGBY(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 21://YES(Saber,1998)
		  rgb2YES(rgb_image_byte,image_double,width,height);
		  max[0]=0.5;max[1]=0.5;max[2]=1.0;min[0]=-0.5;min[1]=-0.5;min[2]=0;
		  break;
		case 22://HLS
		  rgb2hls(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 23://HSI
		  rgb2hsi(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 24://HSB
		  rgb2hsb(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		case 25://CIE_Luv
		  rgb2Luv(rgb_image_byte,image_double,width,height);
		  max[0];max[1];max[2];min[0];min[1];min[2];
		  break;
		default:
		  break;
	}
}

//Compute hu moments for byte-style images;
void CRetrieveMethod::compute_hu_moments(double *image_double,double *moments,int whichch,LONG width,LONG height,int dimension)
{
	double u00,u002,u003;// p+q central moments
	double m00,m01,m10;//p+q moments
	double avg_x,avg_y;//central coordernates

	//calculate m00,m01,m10 for avg_x and avg_y computation
	m00=calculate_mpq(image_double,width,height,0,0,whichch);
	m10=calculate_mpq(image_double,width,height,1,0,whichch);
	m01=calculate_mpq(image_double,width,height,0,1,whichch);

	//compute central positions: avg_x and avg_y
	avg_x=m10/m00;
	avg_y=m01/m00;
	
	//compute zero central moments, i.e., the mean value of pixels
	u00=calculate_upq(image_double,width,height,0,0,avg_x,avg_y,whichch);
	u002=u00*u00;
	u003=pow(u00,2.5);
	
	//calcute normalized p+q=2 central moments[0] [1]
 	double u20,n20,u02,n02,u11,n11;
	u20=calculate_upq(image_double,width,height,2,0,avg_x,avg_y,whichch);
	u02=calculate_upq(image_double,width,height,0,2,avg_x,avg_y,whichch);
	u11=calculate_upq(image_double,width,height,1,1,avg_x,avg_y,whichch);
	n20=u20/u002;
	n02=u02/u002;
	n11=u11/u002;
	
	//calculate the final moments moments[0] [1]
	moments[0]=n20+n02;
	moments[1]=(n20-n02)*(n20-n02)+4.0*n11*n11;
	
	//calcute normalized p+q=3 central moments
	double u30,n30,u12,n12,u21,n21,u03,n03;
	u30=calculate_upq(image_double,width,height,3,0,avg_x,avg_y,whichch);
	u12=calculate_upq(image_double,width,height,1,2,avg_x,avg_y,whichch);
	u21=calculate_upq(image_double,width,height,2,1,avg_x,avg_y,whichch);
	u03=calculate_upq(image_double,width,height,0,3,avg_x,avg_y,whichch);
	n30=u30/u003;
	n12=u12/u003;
	n21=u21/u003;
	n03=u03/u003;
	//calculate the final moments [2] [3] [4] [5] [6]
	moments[2]=(n30-3.0*n12)*(n30-3.0*n12)+(3.0*n21-n03)*(3.0*n21-n03);
	moments[3]=(n30+n12)*(n30+n12)+(n21+n03)*(n21+n03);
	if(dimension==7)
	{
 	  moments[4]=(n30-3*n12)*(n30+n12)*((n30+n12)*(n30+n12)-3*(n21+n03)*(n21+n03))\
		  +(3*n21-n03)*(n21+n03)*(3*(n30+n12)*(n30+n12)-(n21+n03)*(n21+n03));
	  moments[5]=(n20-n02)*((n30+n12)*(n30+n12)-(n21+n03)*(n21+n03))+4*n11*(n30+n12)*(n21+n03);
	  moments[6]=(3*n21-n03)*(n30+n12)*((n30+n12)*(n30+n12)-3*(n21+n03)*(n21+n03))+(3*n12-n30)*(n21+n03)*(3*(n30+n12)*(n30+n12)-(n21+n03)*(n21+n03));
	}
}
//caculate mpq: image_double p+q order moment
double CRetrieveMethod::calculate_mpq(double *image_double,LONG width,LONG height,int p, int q,int whichch)
{
	int i,j;// temp int for loop, i for height and j for width
	//whichch: used to distinguish three components
	double mpq=0;
	double xPowP;	//x powered by p
	double yPowQ;	//y powered by q
	//calculate mpq:
	for(j=0;j<width;j++)
	{
	   if(p==0)
		   xPowP=1.0;
	   else
		   xPowP=pow((double)j,p);
	  for(i=0;i<height;i++)
	  {
		 if(q==0)
		   yPowQ=1.0;
	    else
		   yPowQ=pow((double)i,q);
		mpq+=xPowP*yPowQ*image_double[i*width*3+j*3+whichch];
	  }
	}
	return mpq;
}

//calculate upq 
double CRetrieveMethod::calculate_upq(double *image_double,LONG width,LONG height,int p, int q, double avg_x, double avg_y,int whichch)
{
	int i,j;// temp int for loop, i for height and j for width
	//whichch: used to distinguish three components
	double upq=0;
	double xPowP;//x powered by p
	double yPowQ;//y powered by q
	//calculate upq:
    for(j=0;j<width;j++)
	{
	   if(p==0)
		   xPowP=1.0;
	   else
		   xPowP=pow(((double)j-avg_x),p);
	   for(i=0;i<height;i++)
	   {
	  	 if(q==0)
			 yPowQ=1.0;
		 else
			 yPowQ=pow(((double)i-avg_y),q);
		 upq+=xPowP*yPowQ*image_double[i*width*3+j*3+whichch];
	   }
	}
	return upq;
}
/*****************************************
        *
        *   Public function: compute_distortion_shape_feature_vector(...
        *
        *   
   //input: -rgbimage(The rgb-style image)
   //-width,the width of the bmp image
   //-height,the height of the bmp image 
   //-colorspace: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
   RGB,HSV,HCV(Munsell),CIE_Lab,YCbCr,YIQ,Y_Gray,H,S,V,R,G,B,I1I2I3(Otha,1980),I1'I2'I3'(Bimbo,1999),
   //15,16,17,18,19,20,21,22,23,24,25
   L1L2L3(Gevers,1999),CIE_XYZ,CIE_YUV,CIE_xyY,CIE_U'V'W',RGB_Y,YES(Saber,1998),HLS,HSI,HSB,CIE_Luv
   -thisdimension: the dimension of this vector
   -dimensionused: the total dimension used up to now
   //-bins, number of bins used for histogram
   //output: distortion_feature
   //return 0 success
   //return -1 memory error
   //-2 parameter error
   //-3 method error
******************************************/
int CRetrieveMethod::compute_distortion_shape_feature_vector(double *image_double,double *distortion_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused)
{
  *dimensionused+=thisdimension;
  return 0;
}

int CRetrieveMethod::compute_other_feature_vector1(BYTE *rgb_or_gimage,double *other_feature1,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	*dimensionused+=OtherDim[0];
	return 0;
}
int CRetrieveMethod::compute_other_feature_vector2(BYTE *rgb_or_gimage,double *other_feature2,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	*dimensionused+=OtherDim[1];
	return 0;
}
int CRetrieveMethod::compute_other_feature_vector3(BYTE *rgb_or_gimage,double *other_feature3,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	*dimensionused+=OtherDim[2];
	return 0;
}
int CRetrieveMethod::compute_other_feature_vector4(BYTE *rgb_or_gimage,double *other_feature4,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	*dimensionused+=OtherDim[3];
	return 0;
}

/*****************************************
        *
        *   Private function: rgb2hsv_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to hsv[0]: V; hsv[1]:S; hsv[2]:H
//Hint: H has be changed from (0-360) to (0-1)
******************************************/
void CRetrieveMethod::rgb2hsv_component(BYTE *rgb,double *hsv)
{   
  //h=[0,360]/360.0, s = [0,1], i = [0,1]
  //if s==0, then h = 0 (undefined)

  double min,max,delta;
  double r,g,b;
  b=(double)rgb[0];
  g=(double)rgb[1];
  r=(double)rgb[2];
  min=(r<g)?r:g;
  if(min>b)min=b;
  max=(r>g)?r:g;
  if(max<b)max=b;
  hsv[0]=max/255.0;// V Component
  delta=max-min;
  if(max!=0)  // !(r=g=b=0)
	hsv[1]=delta/max;
  else //r=g=b=0  Component H=S=0
  {                                     		
    hsv[1]=0.0;                                  
    hsv[2]=0.0;
    return;
  }
  if(delta==0)
  {
    hsv[2]=0.0;
	return;
  }
  if(r==max)//between yellow & magenta
	hsv[2]=(g-b)/delta;	     
  else if(g==max)//between cyan & yellow
	hsv[2]=2.0+(b-r)/delta;
  else//between magenta & cyan
	hsv[2]=4.0+(r-g)/delta;
  hsv[2]/=6.0;
  if(hsv[2]<0.0)hsv[2]+=1.0;	
}


/*****************************************
        *
        *   Private function: rgb2hcv_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to hcv[0]: V; hcv[1]:C; hcv[2]:H
//Hint: H has be changed from (0-360) to (0-1)
******************************************/
void CRetrieveMethod::rgb2hcv_component(BYTE *rgb,double *hcv)
{
/*	image = double(image);
	double a1=0.620,a2=0.178,a3=0.204;
	double b1=0.299,b2=0.587,b3=0.144;
	double c1=0,c2=0.056,c3=0.942;
	double x,y,z;
	x=a1*rgb[2]+a2*rgb[1]+a3*rgb[0];
	y=b1*rgb[2]+b2*rgb[1]+b3*rgb[0];
    z=c1*rgb[2]+c2*rgb[1]+c3*rgb[0];
    double H1,H2,H3,M1,M2,M3,H_,S1,S2;
    H1 = 11.6*((nthroot(x/x0,3)-nthroot(y/y0,3)));
    H2 = 11.6*((nthroot(y/y0,3)-nthroot(z/z0,3)));
    H3 = 11.6*nthroot(y/y0,3)-1.6;
    M1 = H1;
    M2 = 0.4*H2;
    M3 = 0.23*H3;
    H_ = atan(M2/M1);
    S1 = M1*(8.88+0.966*cos(H_));
    S2 = M2*(8.025+2.558*sin(H_));
    HCV[2]=atan2(S2,S1);
    HCV[1]=11.6*nthroot(y/y0,3)-1.6;
    HCV[0]=sqrt(S1*S1+S2*S2);*/
}

/*****************************************
        *
        *   Private function: rgb2XYZ_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to XYZ[0]: Z; XYZ[1]:Y; XYZ[2]:X
******************************************/
void CRetrieveMethod::rgb2XYZ_component(BYTE *rgb,double *XYZ)
{
  double rn=((double)rgb[2])/255.0;
  double gn=((double)rgb[1])/255.0;
  double bn=((double)rgb[0])/255.0;
  XYZ[2]=0.412453*rn+0.357580*gn+0.180423*bn;
  XYZ[1]=0.212671*rn+0.715160*gn+0.072169*bn;
  XYZ[0]=0.019334*rn+0.119193*gn+0.950227*bn;
}
/*****************************************
        *
        *   Private function: rgb2Lab_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to Lab[0]: b; Lab[1]:a; Lab[2]:L
//RGB values are in the range from 0 to 255
//CIE-Lab values range as follows: 
//L lies between 0 and 100, and a and b lie between 
//-120 and 120. 
//The white point for CIE-Lab space is fixed at 
//(0.9642, 1, 0.8249), which is the D65 standard.
******************************************/
void CRetrieveMethod::rgb2Lab_component(BYTE *rgb,double *Lab)
{
  double fx,fy,fz;
  double xyz[3];
  // we do need XYZ 
  rgb2XYZ_component(rgb,xyz);
  fx=xyz[2]/WHITE_X;
  fy=xyz[1]/WHITE_Y;
  fz=xyz[0]/WHITE_Z;

  //L 
  if(fy>0.008856)
    Lab[2]=116.0*pow(fy,1.0/3.0)-16.0;
  else
    Lab[2]=903.3*fy;
  
  //a 
  if(fx>0.008856)
    Lab[1]=pow(fx,0.33333333);
  else
    Lab[1]=(7.787*fx)+16/116.0;
  if(fy>0.008856)
    Lab[1]=Lab[1]-pow(fy,1.0/3.0);
  else
    Lab[1]=Lab[1]-((7.787*fy)+16/116.0);
  Lab[1]=Lab[1]*500.0;

  //b 
  if(fy>0.008856)
    Lab[0]=pow(fy,1.0/3.0);
  else
    Lab[0]=(7.787*fy)+16.0/116.0;
  if(fz>0.008856)
    Lab[0]=Lab[0]-pow(fz,1.0/3.0);
  else
    Lab[0]=Lab[0]-((7.787*fz)+16/116.0);
  Lab[0]=Lab[0]*200.0;
}

/*****************************************
        *
        *   Private function: rgb2YCbCr_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to YCbCr[0]: Cr; YCbCr[1]:Cb; YCbCr[2]:Y
//Y(16-235)  Cb(16-240)  Cr(16-240)
//OK
******************************************/
void CRetrieveMethod::rgb2YCbCr_component(BYTE *rgb,BYTE *YCbCr)
{
  /*YCbCr[2]=0.299*rgb[2]+0.587*rgb[1]+0.114*rgb[0];
  YCbCr[1]=-0.169*rgb[2]-0.331*rgb[1]+0.500*rgb[0]; 
  YCbCr[0]=0.500*rgb[2]-0.419*rgb[1]-0.081*rgb[0];*/
  double rn,gn,bn;
  double a,b,c;
  rn=((double)rgb[2])/255.0;
  gn=((double)rgb[1])/255.0;
  bn=((double)rgb[0])/255.0;
  a=65.481*rn+128.553*gn+24.966*bn+16.0;
  b=-37.797*rn-74.2030*gn+112.00*bn+128.0;
  c=112.000*rn-93.7860*gn-18.214*bn+128.0;
  YCbCr[2]=(BYTE)(a+0.5);
  YCbCr[1]=(BYTE)(b+0.5);
  YCbCr[0]=(BYTE)(c+0.5);
}
/*****************************************
        *
        *   overloaded Private function: rgb2YCbCr_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to YCbCr[0]: Cr; YCbCr[1]:Cb; YCbCr[2]:Y
//Y(16-235)  Cb(16-240)  Cr(16-240)/255
//OK
******************************************/
void CRetrieveMethod::rgb2YCbCr_component(BYTE *rgb,double *YCbCr)
{
  /*YCbCr[2]=0.299*rgb[2]+0.587*rgb[1]+0.114*rgb[0];
  YCbCr[1]=-0.169*rgb[2]-0.331*rgb[1]+0.500*rgb[0]; 
  YCbCr[0]=0.500*rgb[2]-0.419*rgb[1]-0.081*rgb[0];*/
  double rn,gn,bn;
  double a,b,c;
  rn=((double)rgb[2])/255.0;
  gn=((double)rgb[1])/255.0;
  bn=((double)rgb[0])/255.0;
  a=65.481*rn+128.553*gn+24.966*bn+16.0;
  b=-37.797*rn-74.2030*gn+112.00*bn+128.0;
  c=112.000*rn-93.7860*gn-18.214*bn+128.0;
  YCbCr[2]=(double)((BYTE)(a+0.5))/255.0;
  YCbCr[1]=(double)((BYTE)(b+0.5))/255.0;
  YCbCr[0]=(double)((BYTE)(c+0.5))/255.0;
}

/*****************************************
        *
        *   Private function: rgb2YIQ_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to YIQ[0]: Q; YIQ[1]:I; YIQ[2]:Y
//Y(0-1) I(-0.596 - 0.596)  Q(-0.523-  0.523)
******************************************/
void CRetrieveMethod::rgb2YIQ_component(BYTE *rgb,double *YIQ)
{
  double rn,gn,bn;
  rn=((double)rgb[2])/255.0;
  gn=((double)rgb[1])/255.0;
  bn=((double)rgb[0])/255.0;
  YIQ[2]=0.299*rn+0.587*gn+0.114*bn;
  YIQ[1]=0.596*rn-0.274*gn-0.322*bn; 
  YIQ[0]=0.211*rn-0.523*gn+0.312*bn;
}

/*****************************************
        *
        *   Private function: rgb2I1I2I3_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to I1I2I3[0]: I3; I1I2I3[1]:I2; I1I2I3[2]:I1
//I1 0-1  I2  -0.5-+0.5  I3 -0.5-+0.5
******************************************/
void CRetrieveMethod::rgb2I1I2I3_component(BYTE *rgb,double *I1I2I3)
{
  double rn,gn,bn;
  rn=((double)rgb[2])/255.0;
  gn=((double)rgb[1])/255.0;
  bn=((double)rgb[0])/255.0;
  I1I2I3[2]=(rn+gn+bn)/3.0;
  I1I2I3[1]=(rn-bn)/2.0;
  I1I2I3[0]=(gn+gn-rn-bn)/4.0;
}

/*****************************************
        *
        *   Private function: rgb2I1_I2_I3_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to I1_I2_I3[0]: I3'; I1_I2_I3[1]:I2'; I1_I2_I3[2]:I1'
//I1' 0-1  I2'  -1-+1  I3' -1-+1
******************************************/
void CRetrieveMethod::rgb2I1_I2_I3_component(BYTE *rgb,double *I1_I2_I3)
{
  double rn,gn,bn;
  rn=((double)rgb[2])/255.0;
  gn=((double)rgb[1])/255.0;
  bn=((double)rgb[0])/255.0;
  I1_I2_I3[2]=(rn+gn+bn)/3.0;
  I1_I2_I3[1]=rn-bn;
  I1_I2_I3[0]=(gn+gn-rn-bn)/2.0;
}
/*****************************************
        *
        *   Private function: rgb2L1L2L3_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to L1L2L3[0]: L3; L1L2L3[1]:L2; L1L2L3[2]:L1

******************************************/  
void CRetrieveMethod::rgb2L1L2L3_component(BYTE *rgb,double *L1L2L3)
{

}
/*****************************************
        *
        *   Private function: rgb2YUV_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to YUV[0]: V; YUV[1]: U; YUV[2]: Y
//Y: -0.70- +0.70  U: -0.41- +0.41  V: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2YUV_component(BYTE *rgb,double *YUV)
{
  double rn, gn, bn;

  rn = rgb[2] / 255.0;
  gn = rgb[1] / 255.0;
  bn = rgb[0] / 255.0;

  YUV[2] = (rn + 2*gn + bn) / 4.0;
  YUV[1] = (rn - gn) / 2.0;
  YUV[0] = (bn - gn) / 2.0;
}
/*****************************************
        *
        *   Private function: rgb2xyY_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to xyY[0]: Y; xyY[1]:y; xyY[2]:x
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2xyY_component(BYTE *rgb,double *xyY)
{
  double denom,XYZ[3];
  rgb2XYZ_component(rgb,XYZ);
  denom = XYZ[2] + XYZ[1] + XYZ[0];

  xyY[0] = rgb[2]*0.2126/255.0 + rgb[1]*0.7152/255.0 + rgb[0]*0.0722/255.0;

  if (denom > 0){
    xyY[2] = XYZ[2] / denom;
    xyY[1] = XYZ[1] / denom;
  }
  else
  {
    xyY[2] = 0;
    xyY[1] = 0;
  }
}
/*****************************************
        *
        *   Private function: rgb2UVW_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to UVW[0]: W; UVW[1]:V; UVW[2]:U
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2UVW_component(BYTE *rgb,double *UVW)
{
  double XYZ[3];
  double denom;
  rgb2XYZ_component(rgb,XYZ);
  denom = XYZ[2] + 15.0 * XYZ[1] + 3.0 * XYZ[0];
  if(denom>0)
  {
    UVW[2] = 4.0 * XYZ[2] / denom;
    UVW[1] = 9.0 * XYZ[1] / denom;
    UVW[0] = (-3.0*XYZ[2] + 6.0*XYZ[1] + 3.0*XYZ[0]) / denom;
  }
  else{
    UVW[2] = 4.0;
    UVW[1] = 9.0;
    UVW[0] = 3.0;
  }
}
/*****************************************
        *
        *   Private function: rgb2RGBY_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to Red/Green/Blue - Yellow, RGBY[0]: BY; RGBY[1]:GY; RGBY[2]:RY
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2RGBY_component(BYTE *rgb,double *RGBY)
{
  double rn, gn, bn;
  rn = rgb[2] / 255.0;
  gn = rgb[1] / 255.0;
  bn = rgb[0] / 255.0;
  RGBY[2] =  0.70*rn - 0.59*gn - 0.11*bn;
  RGBY[1] = -0.30*rn + 0.41*gn - 0.11*bn;
  RGBY[0] = -0.30*rn - 0.59*gn + 0.89*bn;
}
/*****************************************
        *
        *   Private function: rgb2YES_component(...
        *
/*** E. Saber, A. M. Telkap, PRL, vol 19, pp. 669-680, 1998 **
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to YES[0]: S; YES[1]:E; YES[2]:Y
//Y: 0- 1  E: -0.5- +0.5 S: -0.5- +0.5
******************************************/
void CRetrieveMethod::rgb2YES_component(BYTE *rgb,double *YES)
{
  double rn, gn, bn;
  rn = rgb[2] / 255.0;
  gn = rgb[1] / 255.0;
  bn = rgb[0] / 255.0;
  YES[2] = rn*0.253 + gn*0.684 + bn*0.063;
  YES[1] = rn*0.5   - gn*0.5;
  YES[0] = rn*0.25  + gn*0.25  - bn*0.5;
}
/*****************************************
        *
        *   Private function: rgb2hls_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to hls[0]: s; hls[1]:l; hls[2]:h
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2hls_component(BYTE *rgb,double *hls)
{
}
/*****************************************
        *
        *   Private function: rgb2hsi_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to hsi[0]: i; hsi[1]:s; hsi[2]:h
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2hsi_component(BYTE *rgb,double *hsi)
{

}
/*****************************************
        *
        *   Private function: rgb2hsb_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to hsb[0]: b; hsb[1]:s; hsb[2]:h
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2hsb_component(BYTE *rgb,double *hsb)
{

}
/*****************************************
        *
        *   Private function: rgb2Luv_component(...
        *
//Three values rgb[0]: B; rgb[1]:G; rgb[2]:R
//converted to Luv[0]: v; Luv[1]:u; Luv[2]:l
//RY: -0.70- +0.70  GY: -0.41- +0.41  BY: -0.89- +0.89
******************************************/
void CRetrieveMethod::rgb2Luv_component(BYTE *rgb,double *Luv)
{
//  double unprime, vnprime, wnprime
	double XYZ[3];     
//  double uprime, vprime, wprime;
  double fx, fy;
  rgb2XYZ_component(rgb,XYZ);
  fx = XYZ[2] / WHITE_X;
  fy = XYZ[1] / WHITE_Y;
  if ( fy > 0.008856 )
    Luv[2] = 116.0 * pow(fy, 0.33333333) - 16.0;
  else
    Luv[2] = 903.3 * fy;
//  xyz2uvwprime(WHITE_X, WHITE_Y, WHITE_Z, &unprime, &vnprime, &wnprime);
//  xyz2uvwprime(XYZ, &uprime, &vprime, &wprime);
//  Luv[1] = Luv[2] * 13.0 * (uprime - unprime);
 // Luv[0] = Luv[2] * 13.0 * (vprime - vnprime);
}


/*****************************************
        *
        *   Public function: calculate_histogram(...
        *
        *   This function calculates the histogram for different kind of image data
        *   (only for gray-level image or one component of the RGB/HSV image)
        *   If smoothing, it uses a simple moving average scheme where each point in the histogram
        *   is replaced by the average of itself and the two points on either side of it.
	    *   input 
		    -image: The input image in a one-dimensional array (0.0-1.0 HSV or 0-256 8bits RGB or 0-4096 12bits RGB)
			-chunm: The number of channels : 1, for gray-level image   3, for RGB and HSV image
			-whichch: The color component the output histogram based(0: B/V, 1: G/S, 2: R/H)
			-width: the width of image
            -height: the height of image
			-bins: the number of bins (not larger than 256 for 8 bits and 4096 for 12bits and float)
			-smooth: the variable to denote if smoothing the histogram or not
            -bits: for BYTE *image =1,2,4,8  if=1,2,4, bins is fixed=2,4,16; 
            if=8, bins can be set by users<=256;
            for WORD *image=12,16, if=12 bins<=4096 if=16 bins<=65536
            for float *image bits no use, bins<=65536
       *	output
		    -histogram: the output one-dimensioanl array with each sample 
		    being the number of pixels in a bin.
		*   return
		    1, error
			0, success
******************************************/
int CRetrieveMethod::calculate_histogram(BYTE *image,DWORD *histogram,WORD bits,LONG width,LONG height,int chnum,int whichch,WORD bins,bool smooth)
{
   LONG i,length;
   WORD j;
   //the number of image pixels
   length=height*width;
   if(bits==1)bins=2;
   else if(bits==2)bins=4;
   else if(bits==4)bins=16;
   else if(bits!=8) return 1;
   
   //judge if the variables are in the normal ranges
   if(length<=0||bins<=0||bins>256||width<=0||height<=0)return 1;
   if(whichch!=0&&whichch!=1&&whichch!=2)return 1;
   if(chnum!=1&&chnum!=3)return 1;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)histogram[j]=0;
   if(bins==1)
   {
     histogram[0]=length;
	 return 0;
   }
   if(bits==1||bits==2||bits==4||bins==256)
   {
	 for(i=0;i<length;i++)
	 {
	   if(chnum==1)
	     j=image[i];
	   else
	     j=image[i+i+i+whichch];
	   //let the j be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   histogram[j]=histogram[j]+1;
	 }
   }
   else
   {
     //get the histogram 
     for(i=0;i<length;i++)
	 {
	   if(chnum==1)
	     j=(WORD)((double)(image[i])*(double)(bins-1)/255.0+0.5);
	   else
	     j=(WORD)((double)(image[i+i+i+whichch])*(double)(bins-1)/255.0+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   histogram[j]=histogram[j]+1;
	 }
   }
   //smooth the histogram
   if(smooth==true)
   {
     DWORD *new_hist=new DWORD[bins];
     for(j=0;j<bins;j++)new_hist[j]=0;
     new_hist[0]=(histogram[0]+histogram[1])/2;
     new_hist[bins-1]=(histogram[bins-1]+histogram[bins-2])/2;
     for(j=1;j<bins-1;j++)
      new_hist[j]=(histogram[j-1]+histogram[j]+histogram[j+1])/3;
     for(j=0;j<bins;j++)histogram[j]=new_hist[j];
     delete []new_hist;
   }
   return 0;
}
int CRetrieveMethod::calculate_histogram(WORD *image,DWORD *histogram,WORD bits,LONG width,LONG height,int chnum,int whichch,DWORD bins,bool smooth)
{
   LONG i,length;
   DWORD j;
   double space;
   //the number of image pixels
   length=height*width;
   if(bits==12)
   //judge if the variables are in the normal ranges
   {
	 if(length<=0||bins<=0||bins>4096||width<=0||height<=0)return 1;
   }
   else if(bits==16)
   {
     if(length<=0||bins<=0||bins>65536||width<=0||height<=0)return 1;
   }
   else return 1;
   if(whichch!=0&&whichch!=1&&whichch!=2)return 1;
   if(chnum!=1&&chnum!=3)return 1;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)histogram[j]=0;
   if(bins==1)
   {
     histogram[0]=length;
	 return 0;
   }
   if((bits==16&&bins==65536)||(bits==12&&bins==4096))
   {
	 for(i=0;i<length;i++)
	 {
	   if(chnum==1)
	     j=image[i];
	   else
	     j=image[i+i+i+whichch];
	   //let the j be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   histogram[j]=histogram[j]+1;
	 }
   }
   else
   {
     //get the interval between two bins
	 if(bits==12)
       space=4095.0/(double)(bins-1);
     else if(bits==16)
       space=65535.0/(double)(bins-1);
     //get the histogram 
     for(i=0;i<length;i++)
	 {
	   if(chnum==1)
	     j=(DWORD)((double)(image[i])/space+0.5);
	   else
	     j=(DWORD)((double)(image[i+i+i+whichch])/space+0.5);
	   //let the j be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   histogram[j]=histogram[j]+1;
	 }
   }
   //smooth the histogram
   if(smooth==true)
   {
     DWORD *new_hist=new DWORD[bins];
     for(j=0;j<bins;j++)new_hist[j]=0;
     new_hist[0]=(histogram[0]+histogram[1])/2;
     new_hist[bins-1]=(histogram[bins-1]+histogram[bins-2])/2;
     for(j=1;j<bins-1;j++)
      new_hist[j]=(histogram[j-1]+histogram[j]+histogram[j+1])/3;
     for(j=0;j<bins;j++)histogram[j]=new_hist[j];
     delete []new_hist;
   }
   return 0;
}

int CRetrieveMethod::calculate_histogram(double *image,DWORD *histogram,LONG width,LONG height,int chnum,int whichch,WORD bins,bool smooth)
{
   LONG i,length;
   WORD j;
   //the number of image pixels
   length=height*width;
   
   //judge if the variables are in the normal ranges
   if(length<=0||bins<=0||bins>4096||width<=0||height<=0)return 1;
   if(whichch!=0&&whichch!=1&&whichch!=2)return 1;
   if(chnum!=1&&chnum!=3)return 1;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)histogram[j]=0;
   if(bins==1)
   {
     histogram[0]=length;
	 return 0;
   }
   //get the histogram 
   for(i=0;i<length;i++)
   {
	 if(chnum==1)
	   j=(WORD)(image[i]*(double)(bins-1)+0.5);
	 else
	   j=(WORD)(image[i+i+i+whichch]*(double)(bins-1)+0.5);
	 if(j>bins-1)j=bins-1;
	 histogram[j]=histogram[j]+1;
   }

   //smooth the histogram
   if(smooth==true)
   {
     DWORD *new_hist=new DWORD[bins];
     for(j=0;j<bins;j++)new_hist[j]=0;
     new_hist[0]=(histogram[0]+histogram[1])/2;
     new_hist[bins-1]=(histogram[bins-1]+histogram[bins-2])/2;
     for(j=1;j<bins-1;j++)
      new_hist[j]=(histogram[j-1]+histogram[j]+histogram[j+1])/3;
     for(j=0;j<bins;j++)histogram[j]=new_hist[j];
     delete []new_hist;
   }
   return 0;
}
//with max min
int CRetrieveMethod::calculate_histogram(double *image,DWORD *histogram,LONG width,LONG height,int chnum,int whichch,WORD bins,bool smooth,double *max,double *min,bool automaxmin)
{
   LONG i,length;
   WORD j;
   double space;
   //the number of image pixels
   length=height*width;
   
   //judge if the variables are in the normal ranges
   if(length<=0||bins<=0||bins>4096||width<=0||height<=0)return 1;
   if(whichch!=0&&whichch!=1&&whichch!=2)return 1;
   if(chnum!=1&&chnum!=3)return 1;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)histogram[j]=0;
   if(bins==1)
   {
     histogram[0]=length;
	 return 0;
   }
   //get the max and min values
   if(automaxmin==true)
   {
     if(chnum==1)
	   *max=image[0];
	 else
	   *max=image[whichch];
     for(i=1;i<length;i++)
	 {
	   if(chnum==1)
	   {
		   if(*max<image[i])*max=image[i];
	   }
	   else
	   {
	   	   if(*max<image[i+i+i+whichch])*max=image[i+i+i+whichch];
	   }
	 }
	 if(chnum==1)
	   *min=image[0];
	 else
	   *min=image[whichch];
     for(i=1;i<length;i++)
	 {
	   if(chnum==1)
	   {
		   if(*min>image[i])
			   *min=image[i];
	   }
	   else
	   {
	   	   if(*min>image[i+i+i+whichch])
			   *min=image[i+i+i+whichch];
	   }
	 }
   }
   space=((*max)-(*min))/(double)(bins-1);

   //get the histogram 
   for(i=0;i<length;i++)
   {
	 if(chnum==1)
	   j=(WORD)((image[i]-(*min))/space+0.5);
	 else
	   j=(WORD)((image[i+i+i+whichch]-(*min))/space+0.5);
	 if(j>bins-1)j=bins-1;
	 histogram[j]=histogram[j]+1;
   }

   //smooth the histogram
   if(smooth==true)
   {
     DWORD *new_hist=new DWORD[bins];
     for(j=0;j<bins;j++)new_hist[j]=0;
        new_hist[0]=(histogram[0]+histogram[1])/2;
     new_hist[bins-1]=(histogram[bins-1]+histogram[bins-2])/2;
     for(j=1;j<bins-1;j++)
       new_hist[j]=(histogram[j-1]+histogram[j]+histogram[j+1])/3;
     for(j=0;j<bins;j++)histogram[j]=new_hist[j];
     delete []new_hist;
   }
   return 0;
}
/* ends calculate_histogram */ 


/*****************************************
        *
        *   Public function: FeatureDataBaseNormalization(...
        *
        *   This function is used for Feature Normalization
        *   
	    *   input 
		    -lpFeatureVector: the Feature Vectors including images' info and input features
			-VectorNumber: The number of Vectors
			-FeatureDimension: The dimension of each vector
			-Dimensions: The dimension for each kind of feature
			-Weights: The weighting factors for each kind of feature
       *	output
		    -FeatureVector: the Feature Vectors including images' info and output normalized features
		    -lpComponentInfo:the Component info including means and variances of each dimenaion
******************************************/
int CRetrieveMethod::FeatureDatabaseNormalizationandWeighting(LPFEATUREVECTOR lpFeatureVector,DWORD VectorNumber,WORD VectorDimension,WORD *Dimensions,WORD *Weights,LPCOMPONENTINFO lpComponentInfo)
{
	  long double Datatotal=0; ////The temp variable for each dimension
	  int i;
	  WORD dimension,p;          ///The variable for number of dimension
	  DWORD vectors,k;           ///The variable for number of vectors
	  if(lpFeatureVector==NULL)return -1;
	  if(VectorDimension<=0||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -2;
	  if(VectorNumber<=0||VectorNumber>MAX_IMAGE_NUMBER)return -3;
	  p=0;
	  for(i=0;i<8;i++)
	  {
	    p+=Dimensions[i];
	  }
	  if(p!=VectorDimension)return -2;

	  ////Calculate mean and variance for each dimension, and normalization
	  for(dimension=0;dimension<VectorDimension;dimension++) 
	  {
		Datatotal=0.0;
		for(vectors=0;vectors<VectorNumber;vectors++)///sum over all number of vectors of the same dimension
		  Datatotal+=lpFeatureVector[vectors].m_dOriginalFeature[dimension];
		lpComponentInfo[dimension].m_dMean=Datatotal/(double)VectorNumber;  ///The average of unnormalized current dimension
		Datatotal=0.0; ///
		for(vectors=0;vectors<VectorNumber;vectors++)
		  Datatotal+=pow(lpFeatureVector[vectors].m_dOriginalFeature[dimension]-lpComponentInfo[dimension].m_dMean,2.0);
		if(VectorNumber>1)
		{
		   lpComponentInfo[dimension].m_dVariance=sqrt(Datatotal/(VectorNumber-1));
		   if(lpComponentInfo[dimension].m_dVariance>=0.0000000000001)
		   {
		     for(vectors=0;vectors<VectorNumber;vectors++)  
			 {
		       lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=(lpFeatureVector[vectors].m_dOriginalFeature[dimension]\
		       -lpComponentInfo[dimension].m_dMean)/lpComponentInfo[dimension].m_dVariance/3.0;
		       if(lpFeatureVector[vectors].m_dNormalizedFeature[dimension]<-1.0)
		  	     lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=-1.0;
		       else if(lpFeatureVector[vectors].m_dNormalizedFeature[dimension]>1.0)
		  	     lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=1.0;
			 }
	      }
		  else
		  {
		    if(fabs(lpComponentInfo[dimension].m_dMean)<0.0000000000001)
			{
			  for(vectors=0;vectors<VectorNumber;vectors++)  
			    lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=0.0;
			}
			else
			{
			  for(vectors=0;vectors<VectorNumber;vectors++)  
			  {
				if(fabs((lpFeatureVector[vectors].m_dOriginalFeature[dimension]-lpComponentInfo[dimension].m_dMean)/lpComponentInfo[dimension].m_dMean)<0.01)
				{
		          lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=0.0;
				}
				else
				{
	              if(fabs(lpFeatureVector[vectors].m_dOriginalFeature[dimension])<1)
			        lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=lpFeatureVector[vectors].m_dOriginalFeature[dimension];
	              else if (lpFeatureVector[vectors].m_dOriginalFeature[dimension]<-1)
	                lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=-1;
	              else 
	                lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=1;
				}
			  }
			}
		  }
		}
		else
		{
		  lpComponentInfo[dimension].m_dVariance=0.0;
		  lpFeatureVector[vectors].m_dNormalizedFeature[dimension]=lpFeatureVector[vectors].m_dOriginalFeature[dimension];
		}
	  }
	  
	  //Weighting process
	  for(vectors=0;vectors<VectorNumber;vectors++)  
	  {
        p=0;
	    for(i=0;i<8;i++)
		{
		   if(Dimensions[i]>0)
		   {
		      for(k=0;k<Dimensions[i];k++)
			     lpFeatureVector[vectors].m_dNormalizedFeature[k+p]*=sqrt((double)Weights[i]/100.0/Dimensions[i]);
		   }
		   p+=Dimensions[i];
		}
	  }
	  
	  ///Average and variance Computation for each original vector
	  for(vectors=0;vectors<VectorNumber;vectors++)   ////The mean and variance for each vector
	  {
	     Datatotal=0.0;
		 for(dimension=0;dimension<VectorDimension;dimension++)
			Datatotal+=lpFeatureVector[vectors].m_dOriginalFeature[dimension];
		 lpFeatureVector[vectors].m_dOAverage=Datatotal/(double)VectorDimension;
		 Datatotal=0.0; ///
		 for(dimension=0;dimension<VectorDimension;dimension++)
		   Datatotal+=pow(lpFeatureVector[vectors].m_dOriginalFeature[dimension]-lpFeatureVector[vectors].m_dOAverage,2.0);
		 lpFeatureVector[vectors].m_dOVariance=sqrt(Datatotal/VectorDimension);
	  }
	  ///Average and variance Computation for each normalized vector
	  for(vectors=0;vectors<VectorNumber;vectors++)   ////各个适量的均值
	  {
	     Datatotal=0.0;
		 for(dimension=0;dimension<VectorDimension;dimension++)
		   Datatotal+=lpFeatureVector[vectors].m_dNormalizedFeature[dimension];
		 lpFeatureVector[vectors].m_dNAverage=Datatotal/VectorDimension;
		 Datatotal=0.0; ///
		 for(dimension=0;dimension<VectorDimension;dimension++)
		   Datatotal+=pow(lpFeatureVector[vectors].m_dNormalizedFeature[dimension]-lpFeatureVector[vectors].m_dNAverage,2.0);
		 lpFeatureVector[vectors].m_dNVariance=sqrt(Datatotal/VectorDimension);
	  }
	  return 0;
}

/*****************************************
        *
        *   Public function: LBGCodebookDesign(...
        *
        *   This function is used for Codebook Design
        *   
	    *   input 
            //VectorNumber : stands for the number of traning vectors, 
            //         it should be smaller than MAXSOURCESZIE
            //BookSize: stands for the number of codewords
            //         it should be smaller than MAXBOOKSZIE
            //         and blocks should be larger than booksize
            //VectorDimension: stands for the dimension of DCT coefficient block
            //         the vector dimension should be smaller than 64
            //e:  stands for the distortion threshold 
            //         e should be larger than 0
            // TrainVector: 
            //         stands for the training vectors
		*   output
            //  CodeVector: 
            //         stands for the codewords(two-dimensional array)
            // Index[MAX_IMAGE_NUMBER]: each element stands for 
            //                       the index for a trainning vector
            // NumberinCluster[MAX_CODEBOOK_SIZE]: each element stands for 
            //                     the number of training vectors 
            //                     that close to a codeword
            // *MSE:  the pointer to the variable MSE which 
            //        stands for the mean squared error
            // *PSNR: the pointer to the variable PSNR which 
            //        stands for peak signal-noise ratio
			//*Iterations: The number of iterations
			//*Time: The CPU time
       * return 0: normal
           // return -1: BookSize set error
           // return -2: VectorNumber set error
           // return -3: VectorDimension set error
           // return -4: e set error
           //The codebook design method
****************************************************/
int CRetrieveMethod::LBGCodebookDesign(DWORD VectorNumber,WORD BookSize,WORD VectorDimension,double e,double *TrainVector,double *CodeVector,WORD *Index,DWORD *NumberinCluster,double *MSE,double *PSNR,double *Time,WORD *Iterations)
{
   DWORD i,l;
   WORD j,k;
   double d0,d1,d,min,dd[MAX_FEATUREVECTOR_DIMENSION],par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   if(BookSize>MAX_CODEBOOK_SIZE)return -1;
   if(VectorNumber<BookSize||VectorNumber>MAX_IMAGE_NUMBER)return -2;
   if(VectorDimension>MAX_FEATUREVECTOR_DIMENSION||VectorDimension<=0)return -3;
   if(e<=0) return -4;   
   
   //Initial codevector Using random number generator
   par=(double)(VectorNumber-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<BookSize;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector+i*VectorDimension,TrainVector+l*VectorDimension,VectorDimension);
   }
   d0=9.99e+60;   
   *Iterations=0;
   ltime1=clock();
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<BookSize;j++)
	   NumberinCluster[j]=0;
	 for(i=0;i<VectorNumber;i++)
	 {
	    Index[i]=0;
		min=0.0;
        for(k=0;k<VectorDimension;k++)
		{   
          min=min+((double)TrainVector[i*VectorDimension+k]-(double)CodeVector[k])*((double)TrainVector[i*VectorDimension+k]-(double)CodeVector[k]);
		}
		for(j=1;j<BookSize;j++)
		{
		  d=0.0;
		  for(k=0;k<VectorDimension;k++)
		  {			  
		    d=d+((double)TrainVector[i*VectorDimension+k]-(double)CodeVector[j*VectorDimension+k])*((double)TrainVector[i*VectorDimension+k]-(double)CodeVector[j*VectorDimension+k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    Index[i]=j;
		  }
		}
	    NumberinCluster[Index[i]]=NumberinCluster[Index[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*Iterations)++;
	 d0=d1;
	 for(j=0;j<BookSize;j++)
	 {
	    if(NumberinCluster[j]!=0)
		{
		  for(k=0;k<VectorDimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<VectorNumber;l++)
		  {
		    if(Index[l]==j)
			{
			  for(k=0;k<VectorDimension;k++)
			  {
		        dd[k]=dd[k]+(double)TrainVector[l*VectorDimension+k];
			  }
			}
		  }
		  for(k=0;k<VectorDimension;k++)
		  {
		    CodeVector[j*VectorDimension+k]=(float)(dd[k]/(double)NumberinCluster[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector+j*VectorDimension,TrainVector+l*VectorDimension,VectorDimension);
		}
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)VectorDimension*(double)VectorNumber);
   *MSE=d1/(double)VectorDimension/(double)VectorNumber;
   return 0;
}

//Arrange the feature vectors in ascending order of the normalized mean values
void CRetrieveMethod::SortingByAverage(LPFEATUREVECTOR lpFeatureVector,DWORD VectorNumber)
{
	DWORD i,j;
	DWORD index; //
	FEATUREVECTOR temp;
	for(i=0;i<VectorNumber-1;i++)
	{
		index=i;
		for(j=i+1;j<VectorNumber;j++)
		{
			if(lpFeatureVector[index].m_dNAverage>lpFeatureVector[j].m_dNAverage) 
			{
				index=j;
			}  //end of for j,get the index
		}
		if(index==i)  //Minimal 
		{
		  continue;//next i
		}
		temp=lpFeatureVector[i];
		lpFeatureVector[i]=lpFeatureVector[index];
		lpFeatureVector[index]=temp;
	}
}

//计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：FeatureVector
//Featurefirst:为特征矢量结构体的存入的第一个的编号，Featurenumber:该算法提取参数的个数
///本算法中,Featurenumber必须等于7
bool CRetrieveMethod::FeatureVectorExtractMethod_1_7(unsigned char *pdata, int datawidth, int dataheigth,double *OrgFeature,int Featurefirst, int Featurenumber)
{
	if(Featurenumber!=7) 
	{
		MessageBox(NULL,"FeatureExtract Number error","Error!",MB_OK);
		return false;
	}
////add your word here
/////注意：计算一个特征量，iFeatureNumbercheck＋＋；
//////////////////////////////////////////////////////////////////////////
	////////参数1：最佳域值
	//////算法：给定初始值，将像素分为两部分，计算个自的中心，中心的均值作为新的域值，与
	//////////前一次的最佳域值比较，若相同则结束
	/////////并用最大值限制迭代次数
	////说明：参数1，2是颜色中的不变量，是在最佳域值方法中提取出来的
	int i,j;
	double regiondata1=128,regiondata2=128;         ///最佳域值初值
	int Max=1000;                                     ///迭代最多的次数
	int regionnumberleft=0,regionnumberright=0;           ////两个区域的计数值
	long double regiontotallleft=0,regiontotalright=0;         ////两个区域的总和
	long int count;     //计数器
	for(count=0;count<Max;count++)   ////执行次数
	{
		regionnumberleft=0;
		regionnumberright=0;  
		regiontotallleft=0;
		regiontotalright=0;
		for(i=0; i<dataheigth; i++)
		{
 		  for(j=0; j<datawidth; j++)
		  {
			if(*(pdata + i*datawidth + j)<=(unsigned char)regiondata2)
			{
			  regionnumberleft++;       ////左计数器加一
			  regiontotallleft=regiontotallleft+(*(pdata + i*datawidth + j));//总和加一
			}
			else 
			  regiontotalright=regiontotalright+(*(pdata + i*datawidth + j));
		  }
		}
		regionnumberright=datawidth*dataheigth-regionnumberleft;///右计数器计算得出
		if(regionnumberright==0)  //排除异常
		{
		  regionnumberright=1;
		}
		if(regionnumberleft==0)//排除异常
		{
		  regionnumberleft=1;
		}
		regiondata2=(regiontotallleft/regionnumberleft+regiontotalright/regionnumberright)/2.0;////计算公式
		if((unsigned char)regiondata2==(unsigned char)regiondata1)///结束
		  break;
		else 
		  regiondata1=regiondata2;
	}
	OrgFeature[Featurefirst+0]=regiondata2/255.0; ///归一化
///参数2
	OrgFeature[Featurefirst+1]=(double)regionnumberleft/(regionnumberleft+regionnumberright);
////end of 颜色
	///颜色参数的个数

//////说明：参数3，4，5是纹理中的不变量，他们是在共生矩阵中提取的
////参数3:
///统计共生矩阵
	double (*texturematrix)[256]=new double[256][256];  ///共生矩阵x
	double (*texturematriy)[256]=new double[256][256];  ///共生矩阵x
	for(i=0; i<256; i++)
	{
		for(j=0; j<256; j++)
		{
			texturematrix[i][j]=0;
			texturematriy[i][j]=0;
		}
	}
	for(i=1; i<dataheigth-1; i++)
	{
		for(j=1; j<datawidth-1; j++)
		{
			texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j-1)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j-1)]+1;
			texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j+1)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j+1)]+1;
			texturematriy[*(pdata + i*datawidth + j)][*(pdata + (i-1)*datawidth + j)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + (i-1)*datawidth + j)]+1;
			texturematriy[*(pdata + i*datawidth + j)][*(pdata + (i+1)*datawidth + j)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + (i+1)*datawidth + j)]+1;
		}
	}

///////参数3：反差（主对角线的惯性矩）Con
/////////特点：对于粗纹理由于共生矩阵的元素较集中于主对角线附近，此时（h-k)（像素差）较小，
//			  相应的CON值也较小，相反，对于细纹理，则相应的CON值较大。
////////参数4：能量（角二阶矩）Asm
////////特点： 这是一种对图像灰度分布的度量，当共生矩阵的元素分布较集中与主对角线时，
//		  	 相应的ASM值较大，反之，ASM值较小。
////////参数5：熵
/////////特点：当共生矩阵的元素相差不大且较分散时，ENT值较大；反之，生矩阵的元素较集中时，
//      	  ENT值较小。
	unsigned long int MaxNumber=dataheigth*datawidth;////归一化参数
	unsigned long double Ent1=0,Ent2=0;					////熵变量Ent1水平，Ent2
	unsigned long double Asm1=0,Asm2=0;           ///能量变量
    unsigned long double Con1=0,Con2=0;        ///反差变量
	for(i=0; i<256; i++)
	{
	   for(j=0; j<256; j++)
	   {
	 	 long double varible1=texturematrix[i][j]/MaxNumber;  //简化计算的变量,/////归一化共生矩阵
		 long double varible2=texturematriy[i][j]/MaxNumber;
		 Con1=Con1+(i-j)*(i-j)*varible1;
		 Con2=Con2+(i-j)*(i-j)*varible2;
		 Asm1=Asm1+varible1*varible1;
		 Asm2=Asm2+varible2*varible2;
		 if(varible1!=0)
			Ent1=Ent1+varible1*log(varible1);
		 if(varible2!=0)
			Ent2=Ent2+varible2*log(varible2);				
	   }
	}
	OrgFeature[Featurefirst+2]=(Con1+Con2)/2/255.0/255.0;             //提取反差变量
	OrgFeature[Featurefirst+3]=(Asm1+Asm2)/2;              ///提取能量变量
	OrgFeature[Featurefirst+4]=-(Ent1+Ent2)/2;              ///提取熵变量
	delete[] texturematrix;
	delete[] texturematriy;
//////参数3，4，5提取结束	
////end of 纹理
///纹理参数的个数

	
////参数6,7提取：形状不变量
///////二阶矩和一阶矩
/////特点：矩是对图像的一种的一种统计形式，他的计算要用到图像或区域中的所有相关的像素点，
////	对一个数字图像函数F（X）,如果他分段连续且只在XY平面上的有限个点不为零，则可以证明他的
////////各阶矩存在。
	  	//范例图像的各阶矩的声明
	double M_00=0.0,M_01=0.0,M_10=0.0,M_11=0.0,M_20=0.0,M_02=0.0;//P+Q阶矩
    double U_00=0.0,U_11=0.0,U_20=0.0,U_02=0.0;//P+Q阶中心矩
	double m_00,n_00;//重心坐标
	double u_00,u_11,u_20,u_02;//归一化的P+Q阶中心矩
 	///计算范例图的各阶矩
	for(int l=0; l<dataheigth; l++)
	{
		for(int k=0; k<datawidth; k++)
		{ 
		  M_00+=*(pdata + l*datawidth + k);
		  M_01+=*(pdata + l*datawidth + k)*l;
          M_10+=*(pdata + l*datawidth + k)*k;	
		}
	}
	//重心坐标 
	m_00=M_10/M_00;//横坐标
	n_00=M_01/M_00;//纵坐标
	U_00=M_00;
	for(j=0; j<dataheigth; j++)
	{
	   for(i=0; i<datawidth; i++)
	   {
		 U_02+=(j-n_00)*(j-n_00)*(*(pdata + j*datawidth + i));
		 U_20+=(i-m_00)*(i-m_00)*(*(pdata + j*datawidth + i));
		 U_11+=(i-m_00)*(j-n_00)*(*(pdata + j*datawidth + i));
	   }
	}
	u_00=U_00;
	u_02=U_02/pow(u_00,2.0);
	u_11=U_11/pow(u_00,2.0);
	u_20=U_20/pow(u_00,2.0);
	///二阶不变矩保存
	OrgFeature[Featurefirst+5]=(pow((u_20-u_02),2.0)+4*u_11*u_11);  ////保存 
	///一阶不变矩保存
	OrgFeature[Featurefirst+6]=(u_20+u_02);
	return true;
}


/**************************************

        *   Public function: FullSearchRetrieveMethod(...
        *
        *   This function is used to full search based retrieval
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			-RetrievedNumber, Current retrieved number of images
			-VectorNumberTobeSearched, the number of vectors to be compared this time
		    output
			-RetrievedNumber, retrieved number of images up to now
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time
			return
			0: normal
			-1:parameter error
			-2: memory error
			-3:Retrieved number overflow
**************************************/
int CRetrieveMethod::FullSearchRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
	clock_t time1,time2;
	DWORD number,check,l;
	WORD dimension;
	double e,tem;
	RETRIEVEDRESULT p;

	//Judge the parameter
	if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
	if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
	if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
	if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
    if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
	//get the initial time
	time1=clock();
	
	//Compute the distance between query image and each database image to be compared
	for(number=0;number<VectorNumberTobeSearched;number++)
	{
	  tem=0.0;
	  for(dimension=0;dimension<VectorDimension;dimension++)
	  {
	    e=QueryImageFeatureVector.m_dNormalizedFeature[dimension]\
		-lpFeatureVector[number+(*RetrievedNumber)].m_dNormalizedFeature[dimension];
		tem+=e*e;
	  }
	  RetrievedResult[number+(*RetrievedNumber)].m_fDistance=(float)tem;
	  RetrievedResult[number+(*RetrievedNumber)].m_dwImageIndex=number+(*RetrievedNumber);
	}

	//Bubble sort for current computed distances
	for(number=1;number<VectorNumberTobeSearched;number++)
	{
	  for(check=0;check<VectorNumberTobeSearched-number;check++)
	  {
	    if(RetrievedResult[check+(*RetrievedNumber)].m_fDistance>RetrievedResult[check+(*RetrievedNumber)+1].m_fDistance)
		{
		  p=RetrievedResult[check+(*RetrievedNumber)];
		  RetrievedResult[check+(*RetrievedNumber)]=RetrievedResult[check+(*RetrievedNumber)+1];
		  RetrievedResult[check+(*RetrievedNumber)+1]=p;
		}
	  }
	}
    
	//Insert current sorted computed distances into the last sorted distances
	if(*RetrievedNumber!=0)
	{
	  for(number=0;number<VectorNumberTobeSearched;number++)
	  {
	    for(check=0;check<number+(*RetrievedNumber);check++)
		{
		  if(RetrievedResult[number+(*RetrievedNumber)].m_fDistance<RetrievedResult[check].m_fDistance)
		  {
		    p=RetrievedResult[check];
			RetrievedResult[check]=RetrievedResult[number+(*RetrievedNumber)];
			for(l=(*RetrievedNumber)+number;l>=check+2;l--)
			  RetrievedResult[l]=RetrievedResult[l-1];
			RetrievedResult[check+1]=p;
		    break;
		  }
		}
	  }
	}
	//get the finished time
	time2=clock();
	//sum the retrieved vectors
	(*RetrievedNumber)+=VectorNumberTobeSearched;
	//sum the retrieved time
	(*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
//////////////////////////////////////////////////////////////////////////
 	return 0;
}


/**************************************
        *   Public function: EKNNSRetrieveKeyMethod(...
        *
        *   This function is used to EKNNS algorithm based retrieval only the first page
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			-RetrievedNumber, Current retrieved number of images
			-VectorNumberTobeSearched, the number of vectors to be compared this time
		    -RetrieveList, the current index list
			output
			-RetrievedNumber, retrieved number of images up to now
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time up to now?
			-RetrieveList, the remaining index list
			return
			0: normal
			-1: parameter error
			-2: memory error
			-3: Retrieved number overflow
**************************************/
int CRetrieveMethod::EKNNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime, BOOL iteratived,DWORD *searchindexlist)
{

  clock_t time1,time2; ///Define the time variable
	
	//Judge the parameter
  if(iteratived==TRUE&&searchindexlist==NULL)return -1;
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>160||VectorNumberTobeSearched<1)return -3;//Larger than 10 pages
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  DWORD K=VectorNumberTobeSearched;
  double mx=QueryImageFeatureVector.m_dNAverage;
  DWORD I=TotalVectorNumber-(*RetrievedNumber);
  double *dmin= new double [K];//distance for K vectors
  if(dmin==NULL)return -1;
  DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
  if(index==NULL)
  {
	delete [] dmin;
	return -1;
  }
  
  DWORD p;//The index of least mean distance candidate
  int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
  int m,n,w;//for the loop 
  double dsqrt;//sqrt distance for vector[K-1]
  double dtmp=0.0,pds;  ///temp double varaiable
  double mmax,mmin;
  LONG low,high;//The lower and higher limits to be searched
  BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
  DWORD itmp;
  //get the initial time
  time1=clock();
  int pp=1;
  if(TotalVectorNumber<=1000)pp=5;
  for(int yy=0;yy<pp;yy++)
  {
	flagup=FALSE;
	flagdown=FALSE;
	//Get the initial matching index p in the current mean list
	p=GetInitialLeastMeanDistanceIndex(QueryImageFeatureVector,lpFeatureVector,TotalVectorNumber-(*RetrievedNumber),iteratived,searchindexlist);

	//Get the lower and upper limits
	if(K%2==0)
	{
	  low=p-(K/2);
	  high=p+(K/2)-1;
	}
	else
	{
	  low=p-(K-1)/2;
	  high=p+(K-1)/2;
	}

    if(low<0)//if lower than 0
	{
	  low=0;
	  high=K-1;
	  flagdown=TRUE;
	}

	if(high>(LONG)(I-1))//if larger than the list length
	{
	  low=I-K;
	  high=I-1;
	  flagup=TRUE;
	}

///If the images to be searched are the remained images
//for the last time, then no up and down search is performed
	if(K+(*RetrievedNumber)==TotalVectorNumber)
	{
	  flagup=TRUE;    /////
	  flagdown=TRUE;
	}
    
	//calculate the K distances
    if(iteratived==FALSE)
	{
	  for(i=low;i<=high;i++)
	  {
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   for(k=0;k<VectorDimension;k++)
	   {
		 dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-lpFeatureVector[i].m_dNormalizedFeature[k];
	     dmin[i-low]+=dtmp*dtmp;
	   }
	  }
	}
	else
	{
	  for(i=low;i<=high;i++)
	  {
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   for(k=0;k<VectorDimension;k++)
	   {
		 dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-lpFeatureVector[searchindexlist[i]].m_dNormalizedFeature[k];
	     dmin[i-low]+=dtmp*dtmp;
	   }
	  }
	}
	
	///Sorting in the ascending order
	//Bubble sort for current computed K distances
	for(m=1;m<(int)K;m++)
	{
	  for(n=0;n<(int)K-m;n++)
	  {
	    if(dmin[n]>dmin[n+1])///
		{
		  dtmp=dmin[n];
		  dmin[n]=dmin[n+1];
		  dmin[n+1]=dtmp;
		  itmp=index[n];
		  index[n]=index[n+1];
		  index[n+1]=itmp;
		}
	  }
	}
    

	//Initial Setting before searching
	//The start point is j=min{p-low+1,high-p+1}
	j=p-low+1;
	if(j>(int)(high-p+1))j=high-p+1;
    if(low==0)j=high-p+1;
	if(high==(LONG)I-1)j=p-low+1;
	//Get the sqrt distance for vector[K-1]
	dsqrt=sqrt(dmin[K-1]/VectorDimension);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
    if(iteratived==FALSE)
	{
	  for(w=0;w<(int)(I-K+2);w++)
	  {
        //The terminate flags
	    if(flagup==TRUE&&flagdown==TRUE)break;
        ////If we need search in the low direction
	    if(flagdown==FALSE)
		{
		  if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		  else if((int)p-j<low)
		  {
		    if(lpFeatureVector[p-j].m_dNAverage<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  for(k=0;k<VectorDimension;k++)
			  {
			    dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-lpFeatureVector[p-j].m_dNormalizedFeature[k];
			    pds+=dtmp*dtmp;
			    if(pds>=dmin[K-1])break;
			  }
			  if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
			  {
			    //initial pds as the dmin[K-1]
			    index[K-1]=p-j;
                dmin[K-1]=pds;
			    for(m=K-1;m>=1;m--)//insearting
				{
			      if(dmin[m]<dmin[m-1])
				  {
				    dtmp=dmin[m];
				    dmin[m]=dmin[m-1];
				    dmin[m-1]=dtmp;
				    itmp=index[m];
				    index[m]=index[m-1];
				    index[m-1]=itmp;
				  }
				  else
				    break;
				}
			    //update the mmax mmin
			    //The new dsqrt
			    dsqrt=sqrt(dmin[K-1]/VectorDimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
		}
        ////If we need search in the low direction
	    if(flagup==FALSE)
		{
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else if((int)p+j>high)
		  {
		    if(lpFeatureVector[p+j].m_dNAverage>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  for(k=0;k<VectorDimension;k++)
			  {
			   	 dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-lpFeatureVector[p+j].m_dNormalizedFeature[k];
			     pds+=dtmp*dtmp;
			     if(pds>=dmin[K-1])break;
			  }
			  if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
			  {
			    //initial pds as the dmin[K-1]
			    index[K-1]=p+j;
                dmin[K-1]=pds;
			    for(m=K-1;m>=1;m--)//insearting
				{
			      if(dmin[m]<dmin[m-1])
				  {
				    dtmp=dmin[m];
				    dmin[m]=dmin[m-1];
				    dmin[m-1]=dtmp;
				    itmp=index[m];
				    index[m]=index[m-1];
				    index[m-1]=itmp;
				  }
				  else
				   break;
				}
			    //update the mmax mmin
			    //The new dsqrt
			    dsqrt=sqrt(dmin[K-1]/VectorDimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
		}
	    j=j+1;
	  }
    }
	else
	{
	  for(w=0;w<(int)(I-K+2);w++)
	  {
        //The terminate flags
	    if(flagup==TRUE&&flagdown==TRUE)break;
        ////If we need search in the low direction
	    if(flagdown==FALSE)
		{
		  if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		  else
		  {
		    if(lpFeatureVector[searchindexlist[p-j]].m_dNAverage<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if((int)p-j<low)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  for(k=0;k<VectorDimension;k++)
			  {
				 dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-lpFeatureVector[searchindexlist[p-j]].m_dNormalizedFeature[k];
			     pds+=dtmp*dtmp;
			     if(pds>=dmin[K-1])break;
			  }
			  if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
			  {
			    //initial pds as the dmin[K-1]
			    index[K-1]=p-j;
                dmin[K-1]=pds;
			    for(m=K-1;m>=1;m--)//insearting
				{
			      if(dmin[m]<dmin[m-1])
				  {
				    dtmp=dmin[m];
				    dmin[m]=dmin[m-1];
				    dmin[m-1]=dtmp;
				    itmp=index[m];
				    index[m]=index[m-1];
				    index[m-1]=itmp;
				  }
				  else
				    break;
				}
			    //update the mmax mmin
			    //The new dsqrt
			    dsqrt=sqrt(dmin[K-1]/VectorDimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
		}
        ////If we need search in the upper direction
	    if(flagup==FALSE)
		{
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else if((int)p+j>high)
		  {
		    if(lpFeatureVector[searchindexlist[p+j]].m_dNAverage>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  for(k=0;k<VectorDimension;k++)
			  {
			    dtmp=QueryImageFeatureVector.m_dNormalizedFeature[k]-lpFeatureVector[searchindexlist[p+j]].m_dNormalizedFeature[k];
			    pds+=dtmp*dtmp;
			    if(pds>=dmin[K-1])break;
			  }
			  if(pds<dmin[K-1])// If it is less than dmin[K-1], updating the dmin[i]
			  {
			    //initial pds as the dmin[K-1]
			    index[K-1]=p+j;
                dmin[K-1]=pds;
			    for(m=K-1;m>=1;m--)//insearting
				{
			      if(dmin[m]<dmin[m-1])
				  {
				    dtmp=dmin[m];
				    dmin[m]=dmin[m-1];
				    dmin[m-1]=dtmp;
				    itmp=index[m];
				    index[m]=index[m-1];
				    index[m-1]=itmp;
				  }
				  else
				    break;
				}
			    //update the mmax mmin
			    //The new dsqrt
			    dsqrt=sqrt(dmin[K-1]/VectorDimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
		}
	    j=j+1;
	  }
	}
  }
  //get the finished time
  time2=clock();
  
  if(iteratived==FALSE)
  {
   for(n=0;n<(int)VectorNumberTobeSearched;n++)
   {
     RetrievedResult[n+(*RetrievedNumber)].m_fDistance=(float)dmin[n];
     RetrievedResult[n+(*RetrievedNumber)].m_dwImageIndex=index[n];
   }
  }
  else
  {
    for(n=0;n<(int)VectorNumberTobeSearched;n++)
	{
	  RetrievedResult[n+(*RetrievedNumber)].m_fDistance=(float)dmin[n];
	  RetrievedResult[n+(*RetrievedNumber)].m_dwImageIndex=searchindexlist[index[n]];
	}
  }
  //updating the searchindexlist if it is iteratived based
  if(iteratived==TRUE)
  {
    for(m=1;m<(int)K;m++)
	{
	  for(n=0;n<(int)K-m;n++)
	  {
	    if(index[n]<index[n+1])///
		{
		  itmp=index[n];
		  index[n]=index[n+1];
		  index[n+1]=itmp;
		}
	  }
	}
	for(m=0;m<(int)K;m++)
	{
	  for(n=(int)index[m];n<(int)I-m-1;n++)
	  {
		searchindexlist[n]=searchindexlist[n+1];
	  }
	}
  }
  //get the finished time
  time2=clock();
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0/pp;
  //////////////////////////////////////////////////////////////////////////
  delete []dmin;
  delete []index;
  return 0;
}

//// function GetInitialLeastMeanDistanceIndex : ///
//// using bisecting method to find the index (in the remained list) of the initial vector with 
//least mean distance from that of the query vector ////
//// based on their means ////
//input -QueryImageFeatureVector  we only use its m_dNAverage
//input -lpFeatureVector  we only use its m_dNAverage[]
//input -RemainedMeanListLength  the remained mean list length
//input -searchindexlist the current version of whole mean list, only first RemainedMeanListLength mean indecise s are valid
//return the index 
DWORD CRetrieveMethod::GetInitialLeastMeanDistanceIndex(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,DWORD RemainedMeanListLength,BOOL iteratived,DWORD *searchindexlist)
{
	DWORD p;
	DWORD I=RemainedMeanListLength;
    double mx=QueryImageFeatureVector.m_dNAverage;
	//The low
	DWORD i=0;
	//The upper
	DWORD j=I-1;
	if(iteratived==FALSE)
	{
	  //If smaller than the minimum mean
	  if(mx<=lpFeatureVector[i].m_dNAverage)return i;
	  //If smaller than the maximum mean
	  if(mx>=lpFeatureVector[j].m_dNAverage)return j;
	  while(j-i>1)
	  {
	    p=(i+j)/2;
	    if(mx<=lpFeatureVector[p].m_dNAverage)
		  j=p;
	    else 
		  i=p;
	    if(fabs(mx-lpFeatureVector[j].m_dNAverage)>=fabs(mx-lpFeatureVector[i].m_dNAverage))
		  p=i;
	    else
		  p=j;
	  }	
	}
	else
	{
	  //If smaller than the minimum mean
	  if(mx<=lpFeatureVector[searchindexlist[i]].m_dNAverage)return i;
	  //If smaller than the maximum mean
	  if(mx>=lpFeatureVector[searchindexlist[j]].m_dNAverage)return j;
	  while(j-i>1)
	  {
	    p=(i+j)/2;
	    if(mx<=lpFeatureVector[searchindexlist[p]].m_dNAverage)
		  j=p;
	    else 
		  i=p;
	    if(fabs(mx-lpFeatureVector[searchindexlist[j]].m_dNAverage)>=fabs(mx-lpFeatureVector[searchindexlist[i]].m_dNAverage))
		  p=i;
	    else
		  p=j;
	  }
	}
	return p;
}

/**************************************
        *   Public function: ENNSRetrieveMethod(...
        *
        *   This function is used to EKNNS algorithm based retrieval only the first page
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			-RetrievedNumber, Current retrieved number of images
			-VectorNumberTobeSearched, the number of vectors to be compared this time
		    -RetrieveList, the current index list
			output
			-RetrievedNumber, retrieved number of images up to now
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time up to now?
			-RetrieveList, the remaining index list
			return
			0: normal
			-1: parameter error
			-2: memory error
			-3: Retrieved number overflow
**************************************/
//矢量检索，方法2:快速检索最相似的一幅图像
///pFeatureVector图像库矢量结构体指针，iCurrentFeature:检索矢量的数量，
//iRetrieveImageNumber图像库图像数目， QueryImageFeatureVector :关键图像的结构
//pOutFeatureVector：输出结构体的头指针，maxOutNumber＝1输出图像的最多数目,*pOutImageNumber:输出图像的数目的地址
//pDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
int CRetrieveMethod::ENNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
//(LPFEATUREVECTOR lpFeatureVector,int iCurrentFeature, long int iRetrieveImageNumber,FEATUREVECTOR QueryImageFeatureVector, PFEATUREVECTOR pOutFeatureVector, unsigned char maxOutNumber,unsigned char *pOutImageNumber, double *pOutDistance, CString *RetrieveTime)
{
	///下面我们采用快速检索
////我们的矢量是按照均值排序的，而且，均值在矢量的最后一维分量上,从小到大的排序
////1.找和关键图的矢量最接近的矢量均值
////采用二分法

/*FEATUREVECTOR testvq;
testvq.m_dNormalizedFeature;
	clock_t time1,time2;       ///定义时间变量 
	double timecost;
	time1=clock();
	int min=0,max=iRetrieveImageNumber;////二分法中的前后两个数
	int iFindNumber;
	int i,j;
	while(1)
	  {
   //如果关键图的均值比中间的小
		  if (QueryImageFeatureVector.m_dNAverage<(lpFeatureVector+(min+max)/2)->m_dNAverage)
		  {
				max=(min+max)/2;
		  }
		  else
				min=(min+max)/2;
   //上下限相等后相差一个单位，结束我们取均值较小的那个
		  if (min==max||(min==(max-1)))
		  {
				double distance1=0;
				double distance2=0;
				for(i=0;i<iCurrentFeature;i++)
					  distance1=distance1+pow(QueryImageFeatureVector.m_dNormalizedFeature[i]-(lpFeatureVector+min)->m_dNormalizedFeature[i],2.0);
					  distance2=distance2+pow(QueryImageFeatureVector.m_dNormalizedFeature[i]-(lpFeatureVector+max)->m_dNormalizedFeature[i],2.0);
				if(distance1<distance2)
				  iFindNumber=min;
				else 
					  iFindNumber=max;
				break;
		  }
	  }

///找到最接近的那个，我们开始对它的附近检索
///具体的算法参考《矢量量化编码算法及应用研究》，陆哲明，2001，1
/////这里给出程序
	double dDistanceCurrent=0,dDistanceMin=0;//当前的距离
	int index=iFindNumber;              ///检索结果的索引
	for(i=0;i<iCurrentFeature;i++)
		  dDistanceCurrent=dDistanceCurrent+pow(QueryImageFeatureVector.m_dNormalizedFeature[i]-(lpFeatureVector+iFindNumber)->m_dNormalizedFeature[i],2.0);
	dDistanceMin=dDistanceCurrent;   ///初始值
	double mmin=QueryImageFeatureVector.m_dNAverage-sqrt(dDistanceCurrent/iCurrentFeature);  ///快速检索的上下限
	double mmax=QueryImageFeatureVector.m_dNAverage+sqrt(dDistanceCurrent/iCurrentFeature);            ///快速检索的上下限
	////检索开始
	 BOOL flagup=FALSE,flagdown=FALSE;         ///上下检索标志是否继续标志
	 double distancevarible=0;      ///变量
	 if (dDistanceCurrent==0)
	 {
		   flagup=true;
		   flagdown=true;
	 }
for(i=0;i<iRetrieveImageNumber;i++)
{
////如果向上检索还需进行
 if(flagup==TRUE&&flagdown==TRUE)  
	  break;
 if(flagup==FALSE)
	  {
		if((iFindNumber-i)<0||(lpFeatureVector+iFindNumber-i)->m_dNAverage<mmin)       ///如果向上不能再检索
		{
			  flagup=TRUE;         
		}
		else
		{
      ///计算距离
			  distancevarible=0;
			  for(j=0;j<iCurrentFeature;j++)
					distancevarible=distancevarible+pow(QueryImageFeatureVector.m_dNormalizedFeature[j]-(lpFeatureVector+iFindNumber-i)->m_dNormalizedFeature[j],2.0);
			  if (distancevarible<dDistanceCurrent)
			  {
				  index=iFindNumber-i;
				  dDistanceCurrent=distancevarible;
			  }
			 
		}
			   
	  }
 if(flagdown==FALSE)
	  {
			if((iFindNumber+i)>=iRetrieveImageNumber||(lpFeatureVector+iFindNumber+i)->m_dNAverage>mmax)       ///如果向上不能再检索
		{
			  flagdown=TRUE;         
		}
		else
		{
      ///计算距离
			  distancevarible=0;
			  distancevarible=0;
			  for(j=0;j<iCurrentFeature;j++)
					distancevarible=distancevarible+pow(QueryImageFeatureVector.m_dNormalizedFeature[j]-(lpFeatureVector+iFindNumber+i)->m_dNormalizedFeature[j],2.0);
			  if (distancevarible<dDistanceCurrent)
			  {
				  index=iFindNumber+i;
				  dDistanceCurrent=distancevarible;
			  }
			 
		}
	  }
	  if(dDistanceCurrent==dDistanceMin)
			continue;
	   dDistanceMin=dDistanceCurrent;
	  if(flagup==FALSE)
	  	mmin=QueryImageFeatureVector.m_dNAverage-sqrt(dDistanceMin/iCurrentFeature);  ///快速检索的上下限
	  if (flagdown==FALSE) 
	    mmax=QueryImageFeatureVector.m_dNAverage+sqrt(dDistanceMin/iCurrentFeature);

}
///事后处理
	time2=clock();
	timecost=(double)(time2-time1)/CLOCKS_PER_SEC;
	RetrieveTime->Empty();
	RetrieveTime->Format("%s%f",*RetrieveTime,timecost); 
///为显示文件名作准备，
	*pOutImageNumber=1;
*(pOutDistance+0)=dDistanceCurrent;
*(pOutFeatureVector+0)=*(lpFeatureVector+index);*/
//////////////////////////////////////////////////////////////////////////
 	return true;
	
}
//矢量检索，方法3：对矢量的某一维分量进行检索：vector维分量
///直接的检索矢量，对图像的矢量进行检索
///lpFeatureVector图像库矢量结构体指针，iCurrentFeature:检索矢量的数量，
//iRetrieveImageNumber图像库图像数目， QueryImageFeatureVector :关键图像的结构
//pOutFeatureVector：输出结构体的头指针，maxOutNumber输出图像的最多数目,*pOutImageNumber:输出图像的数目的地址
//pDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
///int vector:分量值0～iCurrentFeature-1
//0～100
bool CRetrieveMethod::RetrieveKeyVqMethod_3Single(LPFEATUREVECTOR lpFeatureVector,int iCurrentFeature, long int iRetrieveImageNumber,FEATUREVECTOR QueryImageFeatureVector, PFEATUREVECTOR pOutFeatureVector, unsigned char maxOutNumber,unsigned char *pOutImageNumber, double *pOutDistance, CString *RetrieveTime,int vector)
{
	if (vector>iCurrentFeature-1)
	{
		MessageBox(NULL,"this vector is not exist!","error",MB_OK);
		return false;
	}
	double *pDistance=new double[iRetrieveImageNumber];//开辟内存空间保存距离数据
	///开辟内存，载入颜色几何均值
	////初始化////
	clock_t time1,time2;       ///定义时间变量 
	double timecost;
	time1=clock();
	for(long int number=0;number<iRetrieveImageNumber;number++)
		pDistance[number]=pow((QueryImageFeatureVector.m_dNormalizedFeature[vector]-(lpFeatureVector+number)->m_dNormalizedFeature[vector]),2); ///第k种检索方式  
	
///到现在为止,pDistance[]保存了各个图象和关键图的颜色距离,绝对值
///排序,按着从小到大排序
//基本方法,找到最小的欧式距离后,将它所对应的图象路径给显示数组,然后将赋值256
//由于归一化后的图象的欧式距离不可能为256,故在找下一个图象时不会重复
			int sign=0;            ///做最相似图象的标号
			for(int displaynumber=0;displaynumber<maxOutNumber;displaynumber++)//16个显示图象
			{
				if(displaynumber>iRetrieveImageNumber-1)        //如果图像数目不够，退出
					{
					
						displaynumber=iRetrieveImageNumber;
						break;
					}	
					for(int check=0;check<iRetrieveImageNumber;check++)
					{
						if(pDistance[sign]>pDistance[check])  //要最小的
						{
							sign=check;
						}
					}
					FEATUREVECTOR* pFeatureVectorvar;  //临时
					pFeatureVectorvar=(FEATUREVECTOR*)(pOutFeatureVector+displaynumber);
					*pFeatureVectorvar=*(lpFeatureVector+sign);///save the PathName for display
					*(pOutDistance+displaynumber)=pDistance[sign];
					pDistance[sign]=100*9;             //给最大值100 个食量*9

		}
///事后处理
	delete[] pDistance;               //释放保存欧式距离内存
	time2=clock();
	timecost=(double)(time2-time1)/CLOCKS_PER_SEC;
	RetrieveTime->Empty();
	RetrieveTime->Format("%s%f",*RetrieveTime,timecost); 
///为显示文件名作准备，
	*pOutImageNumber=maxOutNumber;
	for(displaynumber=0;displaynumber<maxOutNumber;displaynumber++)//16个显示图象
		  {
			if(displaynumber>iRetrieveImageNumber-1)        //如果图像数目不够，退出
			{
				  *pOutImageNumber=(unsigned char)iRetrieveImageNumber;
				 break;
			  }
		  }
//////////////////////////////////////////////////////////////////////////

	return true;
}


/*****************************************
        *
        *   Public function: QueryFeatureNormalization(...
        *
        *   This function is used to Normalize Query Feature Vector
        *   
	    *   input 
		    -QueryImageFeatureVector: Query image feature vector including images' info and input features
			-FeatureDimension: The dimension of each vector
            -Dimensions: The dimension for each kind of feature
			-Weights: The weighting factors for each kind of feature
		*	output
		    -QueryImageFeatureVector: the Feature Vectors including images' info and output normalized features
******************************************/
int CRetrieveMethod::QueryFeatureNormalization(PFEATUREVECTOR QueryImageFeatureVector,WORD VectorDimension,WORD *Dimensions, WORD *Weights,LPCOMPONENTINFO lpComponentInfo)
{
   if(QueryImageFeatureVector==NULL)return -1;
   if(VectorDimension<=0||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -2;
   const double mindata=1e-15;
   WORD p,k;
   double Datatotal=0;
   int i;
   p=0;
   for(i=0;i<8;i++)
   {
	 p+=Dimensions[i];
   }
   if(p!=VectorDimension)return -2;
   for(i=0;i<VectorDimension;i++)
   {
	 if(lpComponentInfo[i].m_dVariance<0.0000000000001)
	 {
	   if(fabs(lpComponentInfo[i].m_dMean)<0.0000000000001)
		   QueryImageFeatureVector->m_dNormalizedFeature[i]=0.0;
	   else
	   {
		 if(fabs((QueryImageFeatureVector->m_dOriginalFeature[i]-lpComponentInfo[i].m_dMean)/lpComponentInfo[i].m_dMean)<0.01)
		   QueryImageFeatureVector->m_dNormalizedFeature[i]=0.0;
	     else
		 {
	       if(fabs(QueryImageFeatureVector->m_dOriginalFeature[i])<1)
			 QueryImageFeatureVector->m_dNormalizedFeature[i]=QueryImageFeatureVector->m_dOriginalFeature[i];
	       else if (QueryImageFeatureVector->m_dOriginalFeature[i]<-1)
	         QueryImageFeatureVector->m_dNormalizedFeature[i]=-1;
	       else 
	         QueryImageFeatureVector->m_dNormalizedFeature[i]=1;
		}
	   }
	 }
	 else
	 {
	   QueryImageFeatureVector->m_dNormalizedFeature[i]=(QueryImageFeatureVector->m_dOriginalFeature[i]-lpComponentInfo[i].m_dMean)/lpComponentInfo[i].m_dVariance/3.0;
	   if(QueryImageFeatureVector->m_dNormalizedFeature[i]<-1.0)
	     QueryImageFeatureVector->m_dNormalizedFeature[i]=-1.0;
	   else if(QueryImageFeatureVector->m_dNormalizedFeature[i]>1.0)
	     QueryImageFeatureVector->m_dNormalizedFeature[i]=1.0;
	 }
   }
   //Weighting process
   p=0;
   for(i=0;i<8;i++)
   {
     if(Dimensions[i]>0)
	 {
	    for(k=0;k<Dimensions[i];k++)
	       QueryImageFeatureVector->m_dNormalizedFeature[k+p]*=sqrt(Weights[i]/100.0/Dimensions[i]);
	 }
	 p+=Dimensions[i];
   }
   ///Output Original Mean/variance and Normalized Mean/variance
   for(i=0;i<VectorDimension;i++)
	  Datatotal=Datatotal+QueryImageFeatureVector->m_dOriginalFeature[i];
   QueryImageFeatureVector->m_dOAverage=Datatotal/VectorDimension;
   Datatotal=0.0; ///
   for(i=0;i<VectorDimension;i++)
     Datatotal+=pow(QueryImageFeatureVector->m_dOriginalFeature[i]-QueryImageFeatureVector->m_dOAverage,2.0);
   QueryImageFeatureVector->m_dOVariance=sqrt(Datatotal/VectorDimension);
   
   Datatotal=0.0;
   for(i=0;i<VectorDimension;i++)
	  Datatotal=Datatotal+QueryImageFeatureVector->m_dNormalizedFeature[i];
   QueryImageFeatureVector->m_dNAverage=Datatotal/VectorDimension;
   Datatotal=0.0; ///
   for(i=0;i<VectorDimension;i++)
     Datatotal+=pow(QueryImageFeatureVector->m_dNormalizedFeature[i]-QueryImageFeatureVector->m_dNAverage,2.0);
   QueryImageFeatureVector->m_dNVariance=sqrt(Datatotal/VectorDimension);
   return 0;
}

///方法2:计算基于颜色的三个的三个中心矩
//计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：FeatureVector
//Featurefirst:为特征矢量结构体的存入的第一个的编号，Featurenumber:该算法提取参数的个数
///本算法中,Featurenumber必须等于3
bool CRetrieveMethod::FeatureVectorExtractMethod_2_3(unsigned char *pdata, int datawidth, int dataheigth, double *OrgFeature, int Featurefirst, int Featurenumber)
{
	if(Featurenumber!=3) 
	{
		MessageBox(NULL,"FeatureExtract Number error","error!",MB_OK);
		return false;
	}
////add your word here
//////////////////////////////////////////////////////////////////////////
	////////Par 1：//The average
	int width,height;           
	long int length=dataheigth*datawidth;
	int i;			
	double M1=0,M2=0,M3=0;
	double *pihistogram=new double[256];
	for(i=0;i<256;i++)
	{
		pihistogram[i]=0;
	}
	for(height=0;height<dataheigth;height++)  ///Get the Histogram
		for(width=0;width<datawidth;width++)
			pihistogram[(unsigned char)(*(pdata+height*datawidth+width))]=pihistogram[(unsigned char)(*(pdata+height*datawidth+width))]+1;
	for(i=0;i<256;i++)
	{
		pihistogram[i]=pihistogram[i]/length;  //Normalization
		M1=M1+pihistogram[i]*i;   
	}
			
	for(i=0;i<256;i++) ///The variance of Histogram
		M2=M2+pow(pihistogram[i]-1/256.0,2);
	for(i=0;i<256;i++)
		M3=M3+pow( pihistogram[i]-1/256.0,3);
	M3=pow(fabs(M3),double(1.0/3.0));
	OrgFeature[Featurefirst+0]=M1;
	OrgFeature[Featurefirst+1]=M2;
	OrgFeature[Featurefirst+2]=M3;
//////////////////////////////////////////////////////////////////////////
///end of computation
///delete the memory
	delete[]pihistogram;
	return true;
}

///The third moment computation
bool CRetrieveMethod::FeatureVectorExtractMethod_3_1(unsigned char *pdata, int datawidth, int dataheigth, double *OrgFeature, int Featurefirst, int Featurenumber)
{
	if(Featurenumber!=1) 
	{
		MessageBox(NULL,"FeatureExtract Number error","error!",MB_OK);
		return false;
	}
////add your word here
//////////////////////////////////////////////////////////////////////////
	double M_00=0.0,M_01=0.0,M_10=0.0,M_12=0.0,M_30=0.0,M_03=0.0;//P+Q
    double U_00=0.0,U_21=0,U_12=0.0,U_30=0.0,U_03=0.0;//P+Q order
	double m_00,n_00;//The centure 
	double u_00,u_12,u_21,u_30,u_03;//Normalized P+Q order moment

    unsigned char * pBits = pdata;
	for(int l=0; l<dataheigth; l++)
	{
		for(int k=0; k<datawidth; k++)
		{ 
		  M_00+=*(pBits + l*datawidth + k);
		  M_01+=*(pBits + l*datawidth + k)*l;
          M_10+=*(pBits + l*datawidth + k)*k;	
		}
	}

	m_00=M_10/M_00;
	n_00=M_01/M_00;
	U_00=M_00;
	for(int j=0; j<dataheigth; j++)
	{
	   for(int i=0; i<datawidth; i++)
	   {
		    
			U_12+=(i-m_00)*(j-n_00)*(j-n_00)*(*(pBits + j*datawidth + i));
			U_21+=(i-m_00)*(i-m_00)*(j-n_00)*(*(pBits + j*datawidth + i));
			U_30+=(i-m_00)*(i-m_00)*(i-m_00)*(*(pBits + j*datawidth + i));
			U_03+=(j-n_00)*(j-n_00)*(j-n_00)*(*(pBits + j*datawidth + i));
	   }
	}
	u_00=U_00;
	u_12=U_12/pow(u_00,2.5);
	u_21=U_21/pow(u_00,2.5);
	u_03=U_03/pow(u_00,2.5);
	u_30=U_30/pow(u_00,2.5);
	OrgFeature[Featurefirst+0]=pow((u_30-3*u_12),2.0)+pow((3*u_21-u_03),2.0);
	return true;
}