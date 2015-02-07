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
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        rgb2hsv_component(image_byte+p,image_double+p);
	}
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
        *   Public function: YCbC2rgbr(...
        *
        *   
        *  Convert the whole input image from rgb to YCbCr
        *  input: -image_byte: 24bits YCbCr-style BMP image in a
		*  1-D array (Cr(16-240) Cb(16-240) Y(16-235) Cr Cb Y...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: YCbCr image 
		*  (related to 24bits RGB image)
		*  (B(0-255) G(0-255) R(0-255) B G R B G R...)
******************************************/
void CRetrieveMethod::YCbCr2rgb(BYTE *image_byte,BYTE *image_outbyte,LONG width,LONG height)
{
  LONG i,j,p;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=(i*width+j)*3;
        YCbCr2rgb_component(image_byte+p,image_outbyte+p);
	}
  }

}

/*****************************************
        *
        *   Public function: YCbC2rgbr_other(...
        *
        *   
        *  Convert the whole input image from rgb to YCbCr
        *  input: -image_byte: 24bits YCbCr-style BMP image in a
		*  1-D array (Cr(16-240) Cb(16-240) Y(16-235) Cr Cb Y...) 
        *  -height: the height of the image
        *  -width: the width of the image
        *  output: -image_double: YCbCr image 
		*  (related to 24bits RGB image)
		*  (B(0-255) G(0-255) R(0-255) B G R B G R...)
******************************************/
void CRetrieveMethod::YCbCr2rgb_other(BYTE *image_byte,BYTE *image_outbyte,LONG width,LONG height)
{
  LONG i,j,p;
  long int linebytes;
  linebytes=(width*24+31)/32*4;
  for(i=0;i<height;i++)
  {
	for(j=0;j<width;j++)
	{
      	p=54+i*linebytes+j*3;
        YCbCr2rgb_component(image_byte+p,image_outbyte+p);
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
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	
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
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
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
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return 1;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return 1;
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
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
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
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
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
//    if(rgb_or_gimage==NULL||hist_feature==NULL)return -1;//memory error
//	if(description!=0&&description!=1)return -2;//hist or accum_hist
	if(colorspace<0||colorspace>25)return -2;//color space type error
	//bins setting error
//	if(bins!=MAX_HISTOGRAM_BIN&&bins!=MAX_HISTOGRAM_BIN/2&&bins!=MAX_HISTOGRAM_BIN/4&&bins!=MAX_HISTOGRAM_BIN/8)return -2;
	//bits error
//	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	*dimensionused+=thisdimension;
    return 0;
}

int CRetrieveMethod::compute_other_feature_vector1(BYTE *rgb_or_gimage,float *CodeBookY1,float (*CodeBookY2)[DIMENSION1],float (*CodeBookY3)[DIMENSION2],float *CodeBookY4,float *CodeBookCb1,float (*CodeBookCb2)[DIMENSION1],float (*CodeBookCb3)[DIMENSION2],float *CodeBookCb4,float *CodeBookCr1,float (*CodeBookCr2)[DIMENSION1],float (*CodeBookCr3)[DIMENSION2],float *CodeBookCr4,double *other_feature1,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	if(rgb_or_gimage==NULL||other_feature1==NULL)return -1;//memory error
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	if(CodeBookY1==NULL||CodeBookY2==NULL||CodeBookY3==NULL||CodeBookY4==NULL||CodeBookCb1==NULL||CodeBookCb2==NULL||CodeBookCb3==NULL||CodeBookCb4==NULL||CodeBookCr1==NULL||CodeBookCr2==NULL||CodeBookCr3==NULL||CodeBookCr4==NULL)return -1;
	
	//The memory handle
	HGLOBAL hMem;
	//The blocks and counters
	long int blocks;
    long int i,j,k,l;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	//The number of blocks in width and height
	unsigned short int wb,hb;

	//The pointer for Encode image vectors
	unsigned char *SourceVector[MAXENCODEVECTORS];
	float *DCTSourceVector[MAXENCODEVECTORS];
	float *SourceVector1;
	float *SourceVector2[MAXENCODEVECTORS];
	float *SourceVector3[MAXENCODEVECTORS];
	float *SourceVector4;
	 
	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1,*EncodeCodeIndex2,*EncodeCodeIndex3,*EncodeCodeIndex4;
	
	//The pointer array for generated codevectors by codebook design
    int BOOKSIZE1, BOOKSIZE2;
    unsigned char INBLOCK[BLOCKHEIGHT][BLOCKWIDTH],*INBLOCK1[BLOCKHEIGHT];
	double OUTDCT[BLOCKHEIGHT][BLOCKWIDTH],DCT1D[VECTORDIMENSION],*OUTDCT1[BLOCKHEIGHT];
	
	
	//temp double image
	unsigned char *image_byte=new unsigned char[width*height*3]; 
	if(image_byte==NULL)return -1;//memory error
	
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_byte;
		return -1;//memory error
	}
	if(bits==8)
	  g2rgb(rgb_or_gimage,rgb_image_byte,width,height);
	else
	  memcpy(rgb_image_byte,rgb_or_gimage,width*height*3);
    rgb2YCbCr(rgb_image_byte,image_byte,width,height);
	delete [] rgb_image_byte;
	
	hb=height/BLOCKHEIGHT;
    wb=width/BLOCKWIDTH;
	blocks=hb*wb;

    //Apply memory
	hMem=NULL;
	i=3*width*height  //Y Cb Cr
	// SourceVector   DCTSourceVector          SourceVector1                 SourceVector2/3/4
	+blocks*(2*sizeof(float)+VECTORDIMENSION+VECTORDIMENSION*sizeof(float)+sizeof(float)*DIMENSION1+sizeof(float)*DIMENSION2)
	+4*blocks*sizeof(unsigned short int); //EncodeIndex1/2/3/4
	
	hMem=GlobalAlloc(GMEM_FIXED,i);
	if(hMem==NULL)
	{
	    delete [] image_byte;
	    return -1;
	}
	//Alloc the memory
 	for(i=0;i<blocks;i++)
	  SourceVector[i]=(unsigned char *)hMem+i*VECTORDIMENSION;
	for(i=0;i<blocks;i++)
	  DCTSourceVector[i]=(float *)((unsigned char *)hMem+blocks*VECTORDIMENSION)+i*VECTORDIMENSION;
	SourceVector1=DCTSourceVector[0]+blocks*VECTORDIMENSION;
	for(i=0;i<blocks;i++)
	  SourceVector2[i]=SourceVector1+i*DIMENSION1+blocks;
	for(i=0;i<blocks;i++)
	  SourceVector3[i]=SourceVector2[0]+i*DIMENSION2+blocks*DIMENSION1;
	SourceVector4=SourceVector3[0]+blocks*DIMENSION2;
	EncodeCodeIndex1=(unsigned short int *)(SourceVector4+blocks);
    EncodeCodeIndex2=EncodeCodeIndex1+blocks;
    EncodeCodeIndex3=EncodeCodeIndex2+blocks;
    EncodeCodeIndex4=EncodeCodeIndex3+blocks;
    ImageY=(unsigned char *)(EncodeCodeIndex4+blocks);
	ImageCb=ImageY+width*height;
	ImageCr=ImageCb+width*height;
    long int pp,qq;
    double ttt;
    for(i=0;i<height;i++)
    {
      for(j=0;j<width;j++)
	  {
	     pp=i*width+j;
		 qq=j*3+i*3*width;
		 ImageY[pp]=image_byte[qq+2];
	     ImageCb[pp]=image_byte[qq+1];
	     ImageCr[pp]=image_byte[qq];
	  }
    }
	int posi=0;
	double c;
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=BOOKSIZEY1;
		  BOOKSIZE2=BOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=BOOKSIZECb1;
		  BOOKSIZE2=BOOKSIZECb2;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=BOOKSIZECr1;
		  BOOKSIZE2=BOOKSIZECr2;
	  }
	  
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<BLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<BLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*BLOCKWIDTH]=ImageY[i+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*width];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*BLOCKWIDTH]=ImageCb[i+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*width];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*BLOCKWIDTH]=ImageCr[i+k*BLOCKWIDTH+(j+l*BLOCKHEIGHT)*width];
			} 
		  }
		}
	  }
	  
	  //Encode Start
      for(i=0;i<BLOCKHEIGHT;i++)
	  { 
		INBLOCK1[i]=INBLOCK[i];
		OUTDCT1[i]=OUTDCT[i];
	  } 
	  for(i=0;i<blocks;i++)
	  {
	    for(k=0;k<BLOCKHEIGHT;k++)
		{
	      for(j=0;j<BLOCKWIDTH;j++)
	      INBLOCK1[k][j]=SourceVector[i][k*BLOCKWIDTH+j];
		}
	    DCT(INBLOCK1,OUTDCT1,BLOCKHEIGHT,BLOCKWIDTH);
	    DCT2To1Or1To2(OUTDCT1,DCT1D,BLOCKHEIGHT,BLOCKWIDTH,0);
	    for(k=0;k<VECTORDIMENSION;k++)
		  DCTSourceVector[i][k]=(float)DCT1D[k];
		SourceVector1[i]=(float)DCT1D[0];
		for(k=POSITION1;k<POSITION2;k++)
		  SourceVector2[i][k-POSITION1]=(float)DCT1D[k];
		for(k=POSITION2;k<POSITION2+DIMENSION2;k++)
		 SourceVector3[i][k-POSITION2]=(float)DCT1D[k];
		c=0.0;
		for(k=POSITION2+DIMENSION2;k<VECTORDIMENSION;k++)
		{
		  c+=DCT1D[k]*DCT1D[k];
		}
		SourceVector4[i]=(float)sqrt(c/(double)(VECTORDIMENSION-POSITION2-DIMENSION2));
	  }
	  
	  //encoding
 	  if(component==2)
      {
		i=FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE0,SourceVector1,CodeBookY1,EncodeCodeIndex1,&ttt);
	    i+=FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE1,DIMENSION1,SourceVector2,CodeBookY2,EncodeCodeIndex2,&ttt);
		i+=FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE2,DIMENSION2,SourceVector3,CodeBookY3,EncodeCodeIndex3,&ttt);
	    i+=FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE3,SourceVector4,CodeBookY4,EncodeCodeIndex4,&ttt);
	  }
	  if(component==1)
      {
		i=FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE0,SourceVector1,CodeBookCb1,EncodeCodeIndex1,&ttt);
	    i+=FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE1,DIMENSION1,SourceVector2,CodeBookCb2,EncodeCodeIndex2,&ttt);
		i+=FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE2,DIMENSION2,SourceVector3,CodeBookCb3,EncodeCodeIndex3,&ttt);
	    i+=FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE3,SourceVector4,CodeBookCb4,EncodeCodeIndex4,&ttt);
	  }
	  if(component==0)
      {
		i=FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE0,SourceVector1,CodeBookCr1,EncodeCodeIndex1,&ttt);
	    i+=FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE1,DIMENSION1,SourceVector2,CodeBookCr2,EncodeCodeIndex2,&ttt);
		i+=FSDCTVQ256GrayImageEncode(blocks,BOOKSIZE2,DIMENSION2,SourceVector3,CodeBookCr3,EncodeCodeIndex3,&ttt);
	    i+=FSDCTVQScalar256GrayImageEncode(blocks,BOOKSIZE3,SourceVector4,CodeBookCr4,EncodeCodeIndex4,&ttt);
	  }
      calculate_histogram_int(EncodeCodeIndex1,other_feature1+posi,blocks,32,0,BOOKSIZE0-1);
      posi+=16;
      calculate_histogram_int(EncodeCodeIndex2,other_feature1+posi,blocks,32,0,BOOKSIZE1-1);
      posi+=16;
      calculate_histogram_int(EncodeCodeIndex3,other_feature1+posi,blocks,32,0,BOOKSIZE2-1);
      posi+=16;
      calculate_histogram_int(EncodeCodeIndex4,other_feature1+posi,blocks,32,0,BOOKSIZE3-1);
      posi+=16;
      if(i!=0)
	  {
        GlobalFree(hMem);
		delete [] image_byte;
		return -1;
	  }
   }
   GlobalFree(hMem);
   delete [] image_byte;
   
   *dimensionused+=OtherDim[0];
   return 0;
}
int CRetrieveMethod::calculate_histogram_int(unsigned short int *input,double *output,int len,int bins,unsigned short int min,unsigned short int max)
{
   LONG i;
   WORD j;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)output[j]=0.0;
   if(bins==1)
   {
	 output[0]=1.0;
	 return 0;
   }
   else
   {
     //get the histogram 
     for(i=0;i<len;i++)
	 {
	   j=(WORD)((double)(input[i]-min)*(double)(bins-1)/(double)(max-min)+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   output[j]=output[j]+1.0;
	 }
   }
   for(i=0;i<bins;i++)
     output[i]/=(double)len;
   return 0;
}

int CRetrieveMethod::calculate_histogram_char(unsigned char *input,double *output,int len,int bins,unsigned char min,unsigned char max)
{
   LONG i;
   WORD j;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)output[j]=0.0;
   if(bins==1)
   {
	 output[0]=1.0;
	 return 0;
   }
   else
   {
     //get the histogram 
     for(i=0;i<len;i++)
	 {
	   j=(WORD)((double)(input[i]-min)*(double)(bins-1)/(double)(max-min)+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   output[j]=output[j]+1.0;
	 }
   }
   for(i=0;i<bins;i++)
     output[i]/=(double)len;
   return 0;
}

int CRetrieveMethod::compute_other_feature_vector2(BYTE *rgb_or_gimage,unsigned char (*CodeBookY)[VQDIMENSION],unsigned char (*CodeBookCb)[VQDIMENSION],unsigned char (*CodeBookCr)[VQDIMENSION],double *other_feature2,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	if(rgb_or_gimage==NULL||other_feature2==NULL)return -1;//memory error
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	if(CodeBookY==NULL||CodeBookCb==NULL||CodeBookCr==NULL)return -1;
	
	//The memory handle
	HGLOBAL hMem;
	//The blocks and counters
	long int blocks;
    long int i,j,k,l;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	//The number of blocks in width and height
	unsigned short int wb,hb;
	
	//The pointer for Encode image vectors
	unsigned char *SourceVector[VQMAXENCODEVECTORS];
		 
	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1;
	
	//The pointer array for generated codevectors by codebook design
    int BOOKSIZE1;
   	
	//temp double image
	unsigned char *image_byte=new unsigned char[width*height*3]; 
	if(image_byte==NULL)return -1;//memory error
	
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_byte;
		return -1;//memory error
	}
	if(bits==8)
	  g2rgb(rgb_or_gimage,rgb_image_byte,width,height);
	else
	  memcpy(rgb_image_byte,rgb_or_gimage,width*height*3);
    rgb2YCbCr(rgb_image_byte,image_byte,width,height);
	delete [] rgb_image_byte;
	
	hb=height/VQBLOCKHEIGHT;
    wb=width/VQBLOCKWIDTH;
	blocks=hb*wb;

    //Apply memory
	hMem=NULL;
	i=3*width*height  //Y Cb Cr
	// SourceVector
	+blocks*VQDIMENSION*sizeof(unsigned char)
	+blocks*sizeof(unsigned short int); //EncodeIndex1
	
	hMem=GlobalAlloc(GMEM_FIXED,i);
	if(hMem==NULL)
	{
	    delete [] image_byte;
	    return -1;
	}
	//Alloc the memory
 	for(i=0;i<blocks;i++)
	  SourceVector[i]=(unsigned char *)hMem+i*VQDIMENSION;
	EncodeCodeIndex1=(unsigned short int *)(SourceVector[0]+blocks*VQDIMENSION);
    ImageY=(unsigned char *)(EncodeCodeIndex1+blocks);
	ImageCb=ImageY+width*height;
	ImageCr=ImageCb+width*height;
    long int pp,qq;
    double ttt;
    for(i=0;i<height;i++)
    {
      for(j=0;j<width;j++)
	  {
	     pp=i*width+j;
		 qq=j*3+i*3*width;
		 ImageY[pp]=image_byte[qq+2];
	     ImageCb[pp]=image_byte[qq+1];
	     ImageCr[pp]=image_byte[qq];
	  }
    }
	int posi=0;
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  	  BOOKSIZE1=VQBOOKSIZEY;
	  if(component==1)
	  	  BOOKSIZE1=VQBOOKSIZECb;
	  if(component==0)
          BOOKSIZE1=VQBOOKSIZECr;
	  
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<VQBLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<VQBLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageY[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCb[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCr[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			} 
		  }
		}
	  }
	  
	  //Encode Start
      
 	  if(component==2)
      {
		i=FSVQ256GrayImageEncode(blocks,BOOKSIZE1,VQDIMENSION,SourceVector,CodeBookY,EncodeCodeIndex1,&ttt);
	  }
	  if(component==1)
      {
		i=FSVQ256GrayImageEncode(blocks,BOOKSIZE1,VQDIMENSION,SourceVector,CodeBookCb,EncodeCodeIndex1,&ttt);
	  }
	  if(component==0)
      {
		i=FSVQ256GrayImageEncode(blocks,BOOKSIZE1,VQDIMENSION,SourceVector,CodeBookCr,EncodeCodeIndex1,&ttt);
	  }
      calculate_histogram_int(EncodeCodeIndex1,other_feature2+posi,blocks,64,0,BOOKSIZE1-1);
	  posi+=64;
      if(i!=0)
	  {
        GlobalFree(hMem);
		delete [] image_byte;
		return -1;
	  }
   }
   GlobalFree(hMem);
   delete [] image_byte;
   
   *dimensionused+=OtherDim[1];
   return 0;
}


int CRetrieveMethod::compute_other_feature_vector3(BYTE *rgb_or_gimage,unsigned char (*CodeBookY1)[VQDIMENSION],short int (*CodeBookY2)[VQDIMENSION],unsigned char (*CodeBookCb1)[VQDIMENSION],short int (*CodeBookCb2)[VQDIMENSION],unsigned char (*CodeBookCr1)[VQDIMENSION],short int (*CodeBookCr2)[VQDIMENSION],double *other_feature3,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	if(rgb_or_gimage==NULL||other_feature3==NULL)return -1;//memory error
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	if(CodeBookY1==NULL||CodeBookY2==NULL||CodeBookCb1==NULL||CodeBookCb2==NULL||CodeBookCr1==NULL||CodeBookCr2==NULL)return -1;
	//The memory handle
	HGLOBAL hMem;
	//The blocks and counters
	long int blocks;
    long int i,j,k,l;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	//The number of blocks in width and height
	unsigned short int wb,hb;

		
	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1,*EncodeCodeIndex2;
	
	//The pointer array for generated codevectors by codebook design
    int BOOKSIZE1, BOOKSIZE2;
   	
	//temp double image
	unsigned char *image_byte=new unsigned char[width*height*3]; 
	if(image_byte==NULL)return -1;//memory error
	
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_byte;
		return -1;//memory error
	}
	if(bits==8)
	  g2rgb(rgb_or_gimage,rgb_image_byte,width,height);
	else
	  memcpy(rgb_image_byte,rgb_or_gimage,width*height*3);
    rgb2YCbCr(rgb_image_byte,image_byte,width,height);
	delete [] rgb_image_byte;
	
	hb=height/VQBLOCKHEIGHT;
    wb=width/VQBLOCKWIDTH;
	blocks=hb*wb;

    //Apply memory
	hMem=NULL;
	i=3*width*height  //Y Cb Cr
	+2*blocks*sizeof(unsigned short int); //EncodeIndex1/2
	
	
	unsigned char (*SourceVector)[VQDIMENSION];
	SourceVector=new unsigned char[blocks][VQDIMENSION];
	if(SourceVector==NULL)
	{
		delete [] image_byte;
		return -1;
	}
	
	short int (*SourceVector1)[VQDIMENSION];  //for error vector quantization
	SourceVector1=new short int[blocks][VQDIMENSION];
	if(SourceVector1==NULL)
	{
	  delete [] image_byte;
	  delete [] SourceVector;
	  return -1;
	}
	hMem=GlobalAlloc(GMEM_FIXED,i);
	if(hMem==NULL)
	{
	    delete [] image_byte;
		delete [] SourceVector;
	    delete [] SourceVector1;
	    return -1;
	}
	//Alloc the memory
 	EncodeCodeIndex1=(unsigned short int *)hMem;
    EncodeCodeIndex2=EncodeCodeIndex1+blocks;
    ImageY=(unsigned char *)(EncodeCodeIndex2+blocks);
	ImageCb=ImageY+width*height;
	ImageCr=ImageCb+width*height;
    long int pp,qq;
    for(i=0;i<height;i++)
    {
      for(j=0;j<width;j++)
	  {
	     pp=i*width+j;
		 qq=j*3+i*3*width;
		 ImageY[pp]=image_byte[qq+2];
	     ImageCb[pp]=image_byte[qq+1];
	     ImageCr[pp]=image_byte[qq];
	  }
    }
	int posi=0;
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=VQBOOKSIZEY1;
		  BOOKSIZE2=VQBOOKSIZEY2;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=VQBOOKSIZECb1;
		  BOOKSIZE2=VQBOOKSIZECb2;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=VQBOOKSIZECr1;
		  BOOKSIZE2=VQBOOKSIZECr2;
	  }
	  
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<VQBLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<VQBLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageY[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCb[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCr[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			} 
		  }
		}
	  }
	  
	  //Encode Start
	  //encoding
 	  if(component==2)
      {
		i=TwoStageVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector1,CodeBookY1,CodeBookY2,EncodeCodeIndex1,EncodeCodeIndex2);
	  }
	  if(component==1)
      {
		i=TwoStageVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector1,CodeBookCb1,CodeBookCb2,EncodeCodeIndex1,EncodeCodeIndex2);
	  }
	  if(component==0)
      {
		i=TwoStageVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector1,CodeBookCr1,CodeBookCr2,EncodeCodeIndex1,EncodeCodeIndex2);
	  }
      calculate_histogram_int(EncodeCodeIndex1,other_feature3+posi,blocks,BOOKSIZE1,0,BOOKSIZE1-1);
	  posi+=BOOKSIZE1;
      calculate_histogram_int(EncodeCodeIndex2,other_feature3+posi,blocks,BOOKSIZE2,0,BOOKSIZE2-1);
	  posi+=BOOKSIZE2;
      if(i!=0)
	  {
        GlobalFree(hMem);
		delete [] image_byte;
		delete [] SourceVector;
	    delete [] SourceVector1;
		return -1;
	  }
   }
   GlobalFree(hMem);
   delete [] image_byte;
   delete [] SourceVector;
   delete [] SourceVector1;
   *dimensionused+=OtherDim[2];
   return 0;
}

int CRetrieveMethod::compute_other_feature_vector4(BYTE *rgb_or_gimage,unsigned char (*CodeBookY1)[VQDIMENSION],short int (*CodeBookY2)[VQDIMENSION],unsigned char (*CodeBookCb1)[VQDIMENSION],short int (*CodeBookCb2)[VQDIMENSION],unsigned char (*CodeBookCr1)[VQDIMENSION],short int (*CodeBookCr2)[VQDIMENSION],double *other_feature4,WORD bits,LONG width,LONG height,WORD *dimensionused)
{
	if(rgb_or_gimage==NULL||other_feature4==NULL)return -1;//memory error
	//bits error
	if(bits!=8&&bits!=24)return -2;
	//width error
	if(width<50||width>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	//height error
	if(height<50||height>MAX_IMAGE_WIDTHORHEIGHT)return -2;
	if(CodeBookY1==NULL||CodeBookY2==NULL||CodeBookCb1==NULL||CodeBookCb2==NULL||CodeBookCr1==NULL||CodeBookCr2==NULL)return -1;
	//The memory handle
	HGLOBAL hMem;
	//The blocks and counters
	long int blocks;
    long int i,j,k,l;
	int component;
    //The memory pointer for each component image
	unsigned char *ImageY,*ImageCb,*ImageCr;
	//The number of blocks in width and height
	unsigned short int wb,hb;

		
	//The index in codebook for each input image vetor to be encoded of two stages
	unsigned short int *EncodeCodeIndex1,*EncodeCodeIndex2;
	
	//The pointer array for generated codevectors by codebook design
    int BOOKSIZE1, BOOKSIZE2;
   	
	//temp double image
	unsigned char *image_byte=new unsigned char[width*height*3]; 
	if(image_byte==NULL)return -1;//memory error
	
	BYTE *rgb_image_byte=new BYTE[width*height*3]; 
	if(rgb_image_byte==NULL)
	{
		delete [] image_byte;
		return -1;//memory error
	}
	if(bits==8)
	  g2rgb(rgb_or_gimage,rgb_image_byte,width,height);
	else
	  memcpy(rgb_image_byte,rgb_or_gimage,width*height*3);
    rgb2YCbCr(rgb_image_byte,image_byte,width,height);
	delete [] rgb_image_byte;
	
	hb=height/VQBLOCKHEIGHT;
    wb=width/VQBLOCKWIDTH;
	blocks=hb*wb;

    //Apply memory
	hMem=NULL;
	i=3*width*height  //Y Cb Cr
	+2*blocks*sizeof(unsigned short int); //EncodeIndex1/2
	
	
	unsigned char (*SourceVector)[VQDIMENSION];
	SourceVector=new unsigned char[blocks][VQDIMENSION];
	if(SourceVector==NULL)
	{
		delete [] image_byte;
		return -1;
	}
	
	unsigned char *SourceVector0;
	SourceVector0=new unsigned char[blocks];
	if(SourceVector0==NULL)
	{
		delete [] image_byte;
		delete [] SourceVector;
		return -1;
	}
	short int (*SourceVector1)[VQDIMENSION];  //for error vector quantization
	SourceVector1=new short int[blocks][VQDIMENSION];
	if(SourceVector1==NULL)
	{
	  delete [] image_byte;
	  delete [] SourceVector;
	  delete [] SourceVector0;
	  return -1;
	}
	hMem=GlobalAlloc(GMEM_FIXED,i);
	if(hMem==NULL)
	{
	    delete [] image_byte;
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
	    return -1;
	}
	//Alloc the memory
 	EncodeCodeIndex1=(unsigned short int *)hMem;
    EncodeCodeIndex2=EncodeCodeIndex1+blocks;
    ImageY=(unsigned char *)(EncodeCodeIndex2+blocks);
	ImageCb=ImageY+width*height;
	ImageCr=ImageCb+width*height;
    long int pp,qq;
    for(i=0;i<height;i++)
    {
      for(j=0;j<width;j++)
	  {
	     pp=i*width+j;
		 qq=j*3+i*3*width;
		 ImageY[pp]=image_byte[qq+2];
	     ImageCb[pp]=image_byte[qq+1];
	     ImageCr[pp]=image_byte[qq];
	  }
    }
	int posi=0;
	for(component=2;component>=0;component--)
	{
	  if(component==2)
	  {
		  BOOKSIZE1=VQBOOKSIZEYM;
		  BOOKSIZE2=VQBOOKSIZEYR;
	  }
	  if(component==1)
	  {
		  BOOKSIZE1=VQBOOKSIZECbM;
		  BOOKSIZE2=VQBOOKSIZECbR;
	  }
	  if(component==0)
      {  
		  BOOKSIZE1=VQBOOKSIZECrM;
		  BOOKSIZE2=VQBOOKSIZECrR;
	  }
	  
	  //block the source image
	  for(l=0;l<hb;l++)
	  {
        for(k=0;k<wb;k++)
		{
	  	  for(j=0;j<VQBLOCKHEIGHT;j++)		
		  {
		    for(i=0;i<VQBLOCKWIDTH;i++)		  
			{
	          if(component==2)
				SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageY[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			  else if(component==1)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCb[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			  else if(component==0)
			    SourceVector[k+l*wb][i+j*VQBLOCKWIDTH]=ImageCr[i+k*VQBLOCKWIDTH+(j+l*VQBLOCKHEIGHT)*width];
			} 
		  }
		}
	  }
	  
	  //Encode Start
	  //encoding
 	  if(component==2)
      {
		i=MeanRemovedVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector0,SourceVector1,CodeBookY1,CodeBookY2,EncodeCodeIndex1,EncodeCodeIndex2);
	  }
	  if(component==1)
      {
		i=MeanRemovedVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector0,SourceVector1,CodeBookCb1,CodeBookCb2,EncodeCodeIndex1,EncodeCodeIndex2);
	  }
	  if(component==0)
      {
		i=MeanRemovedVQ256GrayImageEncode(blocks,BOOKSIZE1,BOOKSIZE2,VQBLOCKWIDTH,VQBLOCKHEIGHT,SourceVector,SourceVector0,SourceVector1,CodeBookCr1,CodeBookCr2,EncodeCodeIndex1,EncodeCodeIndex2);
	  }
      calculate_histogram_int(EncodeCodeIndex1,other_feature4+posi,blocks,BOOKSIZE1,0,BOOKSIZE1-1);
	  posi+=BOOKSIZE1;
      calculate_histogram_int(EncodeCodeIndex2,other_feature4+posi,blocks,BOOKSIZE2,0,BOOKSIZE2-1);
	  posi+=BOOKSIZE2;
      if(i!=0)
	  {
        GlobalFree(hMem);
		delete [] image_byte;
		delete [] SourceVector;
		delete [] SourceVector0;
	    delete [] SourceVector1;
		return -1;
	  }
   }
   GlobalFree(hMem);
   delete [] image_byte;
   delete [] SourceVector;
   delete [] SourceVector0;
   delete [] SourceVector1;
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
        *   Private function: rgb2YCbCr_component(...
        *
//Three values YCbCr[0]: Cr; YCbCr[1]:Cb; YCbCr[2]:Y
//converted to rgb[0]: B; rgb[1]:G; rgb[2]:R
//R(0-255)  G(0-255)  Cr(0-255)
//OK
******************************************/
void CRetrieveMethod::YCbCr2rgb_component(BYTE *YCbCr,BYTE *rgb)
{
  double rn,gn,bn;
  BYTE Y,Cb,Cr;
  Y=YCbCr[2];
  Cb=YCbCr[1];
  Cr=YCbCr[0];
  rn=1.164*(Y-16)+1.596*(Cr-128.0);
  gn=1.164*(Y-16)-0.392*(Cb-128.0)+0.813*(Cr-128.0);
  bn=1.164*(Y-16)+2.017*(Cb-128.0);
  if(rn>255)rn=255;
  if(rn<0)rn=0;
  if(gn>255)gn=255;
  if(gn<0)gn=0;
  if(bn>255)bn=255;
  if(bn<0)bn=0;
  rgb[2]=(unsigned char)rn;
  rgb[1]=(unsigned char)gn;
  rgb[0]=(unsigned char)bn;
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
   double d0,d1,d,min,dd[MAX_FEATUREVECTOR_DIMENSION],par,temtem,tem;
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
 	 memcpy(CodeVector+i*(VectorDimension+2),TrainVector+l*VectorDimension,VectorDimension*sizeof(double));
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
		    d=d+((double)TrainVector[i*VectorDimension+k]-(double)CodeVector[j*(VectorDimension+2)+k])*((double)TrainVector[i*VectorDimension+k]-(double)CodeVector[j*(VectorDimension+2)+k]);
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
	 //Get the new codebook
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
		    CodeVector[j*(VectorDimension+2)+k]=(float)(dd[k]/(double)NumberinCluster[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector+j*(VectorDimension+2),TrainVector+l*VectorDimension,VectorDimension*sizeof(double));
		}

		//Compute the mean and variance of the codeoword
	    tem=0.0;
	    for(k=0;k<VectorDimension;k++)
		{
	 	  tem+=(double)CodeVector[j*(VectorDimension+2)+k];
		}
	    CodeVector[j*(VectorDimension+2)+VectorDimension]=tem/(double)VectorDimension;
	    
		temtem=0.0;
	    for(k=0;k<VectorDimension;k++)
		{ 
	 	  tem=(double)CodeVector[j*(VectorDimension+2)+k]-CodeVector[j*(VectorDimension+2)+VectorDimension];
		  temtem+=tem*tem;
		}
	    temtem/=(double)VectorDimension;
	    CodeVector[j*(VectorDimension+2)+VectorDimension+1]=sqrt(min);
	 }

	 //codebook sorted by mean of codeword
	 double tt[MAX_FEATUREVECTOR_DIMENSION+2];
	 DWORD index;
	 for(i=0;i<(DWORD)(BookSize-1);i++)
	 {
	   index=i;
	   for(l=i+1;l<BookSize;l++)
	   {
	     if(CodeVector[index*(VectorDimension+2)+VectorDimension]>CodeVector[l*(VectorDimension+2)+VectorDimension])
		 {
			index=l;
		 } //end of for j,get the index  
	   }
	   if(index==i)
	   {
	     continue;
	   }
	   memcpy(tt,CodeVector+i*(VectorDimension+2),(VectorDimension+2)*sizeof(double));
	   memcpy(CodeVector+i*(VectorDimension+2),CodeVector+index*(VectorDimension+2),(VectorDimension+2)*sizeof(double));
	   memcpy(CodeVector+index*(VectorDimension+2),tt,(VectorDimension+2)*sizeof(double));
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

///Sorting lpFeatureVector in each cluster in ascending order based on normalized mean values
void CRetrieveMethod::ClusterSortingByAverage(LPFEATUREVECTOR m_lpFeatureVector,double *Codeword,WORD *Index,DWORD VectorNumber,WORD Booksize)
{
    DWORD i,j,p,l;
	DWORD index; //
	DWORD *ind=new DWORD[VectorNumber];
	FEATUREVECTOR temp;
	for(p=0;p<Booksize;p++)
	{
	  l=0;
	  for(i=0;i<VectorNumber;i++)
	  {
		if(Index[i]==p)
		{
		  ind[l]=i;
		  l++;
		}
	  }
      if(l<2)continue;
	  for(i=0;i<l-1;i++)
	  {
	    index=i;
		for(j=i+1;j<l;j++)
		{
			if(m_lpFeatureVector[ind[index]].m_dNAverage>m_lpFeatureVector[ind[j]].m_dNAverage) 
			{
				index=j;
			}  //end of for j,get the index
		}
		if(index==i)  //Minimal 
		{
		  continue;//next i
		}
		temp=m_lpFeatureVector[ind[i]];
		m_lpFeatureVector[ind[i]]=m_lpFeatureVector[ind[index]];
		m_lpFeatureVector[ind[index]]=temp;
	  }
	}
	delete [] ind;
}

/*
     Some  private Basic General Fast Algorithms
	 //FullSearch
	 //ENNS
	 //EKNNS
	 //EENNS
	 //EEKNNS
	 //EEENNS
	 //EEEKNNS
*/
//FullSearch, the distances are sorted
void CRetrieveMethod::FullSearchMethod(double *query,double *database,DWORD databasesize,WORD dimension, RETRIEVEDRESULT *result)
{
	DWORD number,check;
	WORD dim;
	double e,tem;
	RETRIEVEDRESULT p;
    //+++++++++++Compute the distance between
	//+++++++++++query image and each database
	//+++++++++++vector to be compared
	for(number=0;number<databasesize;number++)
	{
	  tem=0.0;
	  for(dim=0;dim<dimension;dim++)
	  {
	    e=query[dim]-database[number*dimension+dim];
		tem+=e*e;
	  }
	  result[number].m_fDistance=(float)tem;
	  result[number].m_dwImageIndex=number;
	}

	//+++++++++++++Bubble sort for current computed distances
	for(number=1;number<databasesize;number++)
	{
	  for(check=0;check<databasesize-number;check++)
	  {
	    if(result[check].m_fDistance>result[check+1].m_fDistance)
		{
		  p=result[check];
		  result[check]=result[check+1];
		  result[check+1]=p;
		}
	  }
	}
}

//FullSearch2, the distances are sorted
void CRetrieveMethod::FullSearchMethod2(double *query,double *database,DWORD databasesize,WORD dimension, RETRIEVEDRESULT *result)
{
	DWORD number,check;
	WORD dim;
	double e,tem;
	RETRIEVEDRESULT p;
    //+++++++++++Compute the distance between
	//+++++++++++query image and each database
	//+++++++++++vector to be compared
	for(number=0;number<databasesize;number++)
	{
	  tem=0.0;
	  for(dim=0;dim<dimension;dim++)
	  {
	    e=query[dim]-database[number*(dimension+2)+dim];
		tem+=e*e;
	  }
	  result[number].m_fDistance=(float)tem;
	  result[number].m_dwImageIndex=number;
	}

	//+++++++++++++Bubble sort for current computed distances
	for(number=1;number<databasesize;number++)
	{
	  for(check=0;check<databasesize-number;check++)
	  {
	    if(result[check].m_fDistance>result[check+1].m_fDistance)
		{
		  p=result[check];
		  result[check]=result[check+1];
		  result[check+1]=p;
		}
	  }
	}
}

//ENNS, the best one
void CRetrieveMethod::ENNSMethod(double *query,double querymean, double *database,double *means,DWORD databasesize,WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int j,k;//j for the main loop, k for dimension
    int w;//for the loop 
    double dsqrt;//sqrt distance for vector[p]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin;
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD I=databasesize;
	double dmin;
    DWORD index,itmp;
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
	//++++++++++++++calculate the distance for p+++++++++++
    dmin=0.0;
	index=p;//
	itmp=p*dimension;
	for(k=0;k<dimension;k++)
	{
	 dtmp=query[k]-database[itmp+k];
	 dmin+=dtmp*dtmp;
	}
	//Get the sqrt distance for vector[p]
	dsqrt=sqrt(dmin/dimension);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	j=0;
    for(w=0;w<(int)I;w++)
	{
      //The terminate flags
	  if(flagup==TRUE&&flagdown==TRUE)break;
      ////If we need search in the low direction
	  if(flagdown==FALSE)
	  {
	    if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		else
		{
		    if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p-j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			    dtmp=query[k]-database[itmp+k];
			    pds+=dtmp*dtmp;
			    if(pds>=dmin)break;
			  }
			  if(pds<dmin)// If it is less than dmin, updating the dmin
			  {
			    //initial pds as the dmin
			    index=p-j;
                dmin=pds;
			    //update the mmax mmin
			    //The new dsqrt
			    dsqrt=sqrt(dmin/dimension);
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
		  else
		  {
		    if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p+j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			   	 dtmp=query[k]-database[itmp+k];
			     pds+=dtmp*dtmp;
			     if(pds>=dmin)break;
			  }
			  if(pds<dmin)// If it is less than dmin, updating the dmin
			  {
			    //initial pds as the dmin
			    index=p+j;
                dmin=pds;
			    //update the mmax mmin
			    //The new dsqrt
			    dsqrt=sqrt(dmin/dimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
	  }
	  j=j+1;
	}
    result->m_fDistance=(float)dmin;
    result->m_dwImageIndex=index;
}

//EENNS,the best one
void CRetrieveMethod::EENNSMethod(double *query,double querymean,double queryvariance, double *database,double *means,double *variances,DWORD databasesize,WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int j,k;//j for the main loop, k for dimension
    int w;//for the loop 
    double dsqrt,dsqrtv;//sqrt distances for vector[p]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD I=databasesize;
	double dmin;
    DWORD index,itmp;
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
	//++++++++++++++calculate the distance for p+++++++++++
    dmin=0.0;
	index=p;//
	itmp=p*dimension;
	for(k=0;k<dimension;k++)
	{
	 dtmp=query[k]-database[itmp+k];
	 dmin+=dtmp*dtmp;
	}
	//Get the sqrt and sqrtv distance for vector[p]
	dsqrt=sqrt(dmin/dimension);
	dsqrtv=sqrt(dmin);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
    j=0;
    for(w=0;w<(int)I;w++)
	{
      //The terminate flags
	  if(flagup==TRUE&&flagdown==TRUE)break;
      ////If we need search in the low direction
	  if(flagdown==FALSE)
	  {
	    if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		else
		{
		    if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(variances[p-j]>vmin&&variances[p-j]<vmax)
			{
			  ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p-j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			    dtmp=query[k]-database[itmp+k];
			    pds+=dtmp*dtmp;
			    if(pds>=dmin)break;
			  }
			  if(pds<dmin)// If it is less than dmin, updating the dmin
			  {
			    //initial pds as the dmin
			    index=p-j;
                dmin=pds;
			    //update the mmax mmin vmax vmin
			    //The new dsqrt and dsqrtv
			    dsqrt=sqrt(dmin/dimension);
	            dsqrtv=sqrt(dmin);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
				//The new vmax and vmin
	            vmax=vx+dsqrtv;
	            vmin=vx-dsqrtv;
			  }   
			}
		}
	  }
      ////If we need search in the low direction
	  if(flagup==FALSE)
	  {
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else
		  {
		    if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(variances[p+j]>vmin&&variances[p+j]<vmax)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p+j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			   	 dtmp=query[k]-database[itmp+k];
			     pds+=dtmp*dtmp;
			     if(pds>=dmin)break;
			  }
			  if(pds<dmin)// If it is less than dmin, updating the dmin
			  {
			    //pds as the dmin
			    index=p+j;
                dmin=pds;
			    //update the mmax mmin vmax vmin
			    //The new dsqrt and dsqrtv
			    dsqrt=sqrt(dmin/dimension);
	            dsqrtv=sqrt(dmin);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
				//The new vmax and vmin
	            vmax=vx+dsqrtv;
	            vmin=vx-dsqrtv;
			  }   
			}
		  }
	  }
	  j=j+1;
	}
    result->m_fDistance=(float)dmin;
    result->m_dwImageIndex=index;
}

//EEENNS,the best one
void CRetrieveMethod::EEENNSMethod(double *query,double querymean,double queryvariance, double *database,double *means,double *variances,DWORD databasesize,WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int j,k;//j for the main loop, k for dimension
    int w;//for the loop 
    double dsqrt,dsqrtv;//sqrt distances for vector[p]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD I=databasesize;
	double dmin;
    DWORD index,itmp;
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
	//++++++++++++++calculate the distance for p+++++++++++
    dmin=0.0;
	index=p;//
	itmp=p*dimension;
	for(k=0;k<dimension;k++)
	{
	 dtmp=query[k]-database[itmp+k];
	 dmin+=dtmp*dtmp;
	}
	//Get the sqrt and sqrtv distance for vector[p]
	dsqrt=sqrt(dmin/dimension);
	dsqrtv=sqrt(dmin);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
    j=0;
    for(w=0;w<(int)I;w++)
	{
      //The terminate flags
	  if(flagup==TRUE&&flagdown==TRUE)break;
      ////If we need search in the low direction
	  if(flagdown==FALSE)
	  {
	    if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		else
		{
		    if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(variances[p-j]>vmin&&variances[p-j]<vmax)
			{
			  dtmp=(variances[p-j]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-means[p-j]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin)
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
				itmp=(p-j)*dimension;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=query[k]-database[itmp+k];
			      pds+=dtmp*dtmp;
			      if(pds>=dmin)break;
				}
			    if(pds<dmin)// If it is less than dmin, updating the dmin
				{
			      //initial pds as the dmin
			      index=p-j;
                  dmin=pds;
			      //update the mmax mmin vmax vmin
			      //The new dsqrt and dsqrtv
			      dsqrt=sqrt(dmin/dimension);
	              dsqrtv=sqrt(dmin);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The new vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		}
	  }
      ////If we need search in the low direction
	  if(flagup==FALSE)
	  {
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else
		  {
		    if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(variances[p+j]>vmin&&variances[p+j]<vmax)
			{
              dtmp=(variances[p+j]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-means[p+j]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin)
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
				itmp=(p+j)*dimension;
			    for(k=0;k<dimension;k++)
				{
			   	   dtmp=query[k]-database[itmp+k];
			       pds+=dtmp*dtmp;
			       if(pds>=dmin)break;
				}
			    if(pds<dmin)// If it is less than dmin, updating the dmin
				{
			      //pds as the dmin
			      index=p+j;
                  dmin=pds;
			      //update the mmax mmin vmax vmin
			      //The new dsqrt and dsqrtv
			      dsqrt=sqrt(dmin/dimension);
	              dsqrtv=sqrt(dmin);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The new vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		  }
	  }
	  j=j+1;
	}
    result->m_fDistance=(float)dmin;
    result->m_dwImageIndex=index;
}

//EEENNS,the best one
//another version
void CRetrieveMethod::EEENNSMethod(double *query,double querymean,double queryvariance, double *database,DWORD databasesize,WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int j,k;//j for the main loop, k for dimension
    int w;//for the loop 
    double dsqrt,dsqrtv;//sqrt distances for vector[p]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD I=databasesize;
	double dmin;
    DWORD index,itemp;
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=database[ii*(dimension+2)+dimension])p=ii;
    //If smaller than the maximum mean
    else if(mx>=database[jj*(dimension+2)+dimension])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=database[p*(dimension+2)+dimension])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-database[jj*(dimension+2)+dimension])>=fabs(mx-database[ii*(dimension+2)+dimension]))
	      p=ii;
        else
	      p=jj;
	  }
	}
	//++++++++++++++calculate the distance for p+++++++++++
    dmin=0.0;
	index=p;//
	itemp=p*(dimension+2);
	for(k=0;k<dimension;k++)
	{
	 dtmp=query[k]-database[itemp+k];
	 dmin+=dtmp*dtmp;
	}
	//Get the sqrt and sqrtv distance for vector[p]
	dsqrt=sqrt(dmin/dimension);
	dsqrtv=sqrt(dmin);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
    j=0;
    for(w=0;w<(int)I;w++)
	{
      //The terminate flags
	  if(flagup==TRUE&&flagdown==TRUE)break;
      ////If we need search in the low direction
	  if(flagdown==FALSE)
	  {
	    if(p<(DWORD)j)flagdown=TRUE;//The flag set when no search in this direction
		else
		{
		    itemp=(p-j)*(dimension+2);
			if(database[itemp+dimension]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(database[itemp+dimension+1]>vmin&&database[itemp+dimension+1]<vmax)
			{
			  dtmp=(database[itemp+dimension+1]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-database[itemp+dimension]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin)
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=query[k]-database[itemp+k];
			      pds+=dtmp*dtmp;
			      if(pds>=dmin)break;
				}
			    if(pds<dmin)// If it is less than dmin, updating the dmin
				{
			      //initial pds as the dmin
			      index=p-j;
                  dmin=pds;
			      //update the mmax mmin vmax vmin
			      //The new dsqrt and dsqrtv
			      dsqrt=sqrt(dmin/dimension);
	              dsqrtv=sqrt(dmin);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The new vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		}
	  }
      ////If we need search in the low direction
	  if(flagup==FALSE)
	  {
		  if(p+j>=I)flagup=TRUE;//The flag set when no search in this direction
		  else
		  {
		    itemp=(p+j)*(dimension+2);
			if(database[itemp+dimension]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(database[itemp+dimension+1]>vmin&&database[itemp+dimension+1]<vmax)
			{
              dtmp=(database[itemp+dimension+1]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-database[itemp+dimension]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin)
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			   	   dtmp=query[k]-database[itemp+k];
			       pds+=dtmp*dtmp;
			       if(pds>=dmin)break;
				}
			    if(pds<dmin)// If it is less than dmin, updating the dmin
				{
			      //pds as the dmin
			      index=p+j;
                  dmin=pds;
			      //update the mmax mmin vmax vmin
			      //The new dsqrt and dsqrtv
			      dsqrt=sqrt(dmin/dimension);
	              dsqrtv=sqrt(dmin);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The new vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		  }
	  }
	  j=j+1;
	}
    result->m_fDistance=(float)dmin;
    result->m_dwImageIndex=index;
}
//EKNNS,the best K ones
int CRetrieveMethod::EKNNSMethod(double *query,double querymean, double *database,double *means,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt;//sqrt distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    DWORD I=databasesize;
	DWORD K;
	//If K is bigger than the total number of vectors
	if(I<value_K)
	  K=I;
	else
	  K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   itmp=i*dimension;
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[itmp+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	dsqrt=sqrt(dmin[K-1]/dimension);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
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
		    if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p-j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			    dtmp=query[k]-database[itmp+k];
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
			    dsqrt=sqrt(dmin[K-1]/dimension);
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
		    if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p+j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			   	 dtmp=query[k]-database[itmp+k];
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
			    dsqrt=sqrt(dmin[K-1]/dimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
	  }
	  j=j+1;
	}
    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=index[n];
    }
    delete []dmin;
    delete []index;
    return 0;
}

//EEKNNS,the best K ones
int CRetrieveMethod::EEKNNSMethod(double *query,double querymean,double queryvariance, double *database,double *means,double *variances,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt,dsqrtv;//sqrt sqrtv distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    DWORD I=databasesize;
	DWORD K;
	//If K is bigger than the total number of vectors
	if(I<value_K)
	  K=I;
	else
	  K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i]
	   itmp=i*dimension;
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[itmp+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	//Get the sqrt sqrtv distance for vector[K-1]
	dsqrt=sqrt(dmin[K-1]/dimension);
	dsqrtv=sqrt(dmin[K-1]);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
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
		    if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(variances[p-j]>vmin&&variances[p-j]<vmax)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p-j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			    dtmp=query[k]-database[itmp+k];
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
			    //update the mmax mmin vmax vmin
			    //The new dsqrt dsqrtv
			    dsqrt=sqrt(dmin[K-1]/dimension);
				dsqrtv=sqrt(dmin[K-1]);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
				//The vmax and vmin
	            vmax=vx+dsqrtv;
	            vmin=vx-dsqrtv;
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
		    if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(variances[p+j]>vmin&&variances[p+j]<vmax)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=(p+j)*dimension;
			  for(k=0;k<dimension;k++)
			  {
			   	 dtmp=query[k]-database[itmp+k];
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
			    //update the mmax mmin vmax vmin
			    //The new dsqrt dsqrtv
			    dsqrt=sqrt(dmin[K-1]/dimension);
				dsqrtv=sqrt(dmin[K-1]);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
				//The vmax and vmin
	            vmax=vx+dsqrtv;
	            vmin=vx-dsqrtv;
			  }   
			}
		  }
	  }
	  j=j+1;
	}
    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=index[n];
    }
    delete []dmin;
    delete []index;
    return 0;
}

//EEEKNNS,the best K ones
int CRetrieveMethod::EEEKNNSMethod(double *query,double querymean,double queryvariance, double *database,double *means,double *variances,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt,dsqrtv;//sqrt sqrtv distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    DWORD I=databasesize;
	DWORD K;
	//If K is bigger than the total number of vectors
	if(I<value_K)
	  K=I;
	else
	  K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[i*dimension+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	//Get the sqrt sqrtv distance for vector[K-1]
	dsqrt=sqrt(dmin[K-1]/dimension);
	dsqrtv=sqrt(dmin[K-1]);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
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
		    if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(variances[p-j]>vmin&&variances[p-j]<vmax)
			{
              dtmp=(variances[p-j]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-means[p-j]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
				 ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=query[k]-database[(p-j)*dimension+k];
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
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
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
		    if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(variances[p+j]>vmin&&variances[p+j]<vmax)
			{
              dtmp=(variances[p+j]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-means[p+j]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			   	 dtmp=query[k]-database[(p+j)*dimension+k];
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
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		  }
	  }
	  j=j+1;
	}
    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=index[n];
    }
    delete []dmin;
    delete []index;
    return 0;
}

//EEEKNNS,the best K ones
//another version
int CRetrieveMethod::EEEKNNSMethod(double *query,double querymean,double queryvariance, double *database,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt,dsqrtv;//sqrt sqrtv distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    DWORD I=databasesize;
	DWORD K;
	//If K is bigger than the total number of vectors
	if(I<value_K)
	  K=I;
	else
	  K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    
	//+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    if(mx<=database[ii*(dimension+2)+dimension])p=ii;
    //If smaller than the maximum mean
    else if(mx>=database[jj*(dimension+2)+dimension])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        if(mx<=database[p*(dimension+2)+dimension])
	      jj=p;
        else 
	      ii=p;
        if(fabs(mx-database[jj*(dimension+2)+dimension])>=fabs(mx-database[ii*(dimension+2)+dimension]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   itmp=i*(dimension+2);
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[itmp+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	//Get the sqrt sqrtv distance for vector[K-1]
	dsqrt=sqrt(dmin[K-1]/dimension);
	dsqrtv=sqrt(dmin[K-1]);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
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
		    itmp=(p-j)*(dimension+2);
			if(database[itmp+dimension]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(database[itmp+dimension+1]>vmin&&database[itmp+dimension+1]<vmax)
			{
              dtmp=(database[itmp+dimension+1]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-database[itmp+dimension]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
				 ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=query[k]-database[itmp+k];
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
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
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
		    itmp=(p+j)*(dimension+2);
			if(database[itmp+dimension]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(database[itmp+dimension+1]>vmin&&database[itmp+dimension+1]<vmax)
			{
              dtmp=(database[itmp+dimension+1]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-database[itmp+dimension]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
			    for(k=0;k<dimension;k++)
				{
			   	 dtmp=query[k]-database[itmp+k];
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
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }
			}
		  }
	  }
	  j=j+1;
	}
    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=index[n];
    }
    delete []dmin;
    delete []index;
    return 0;
}


//EKNNSForIterative,the best K ones
int CRetrieveMethod::EKNNSMethodForIterative(double *query,double querymean, double *database,double *means,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result,DWORD *searchindexlist)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt;//sqrt distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    flagup=FALSE;
    flagdown=FALSE;
    DWORD I=databasesize;
    DWORD K;
	//If value_K is bigger than the total number of vectors
	if(I<value_K) K=I;
	else K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    //+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    //if(mx<=means[searchindexlist[ii]])p=ii;
	if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    //else if(mx>=means[searchindexlist[jj]])p=jj;
	else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        //if(mx<=means[searchindexlist[p]])
		if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        //if(fabs(mx-means[searchindexlist[jj]])>=fabs(mx-means[searchindexlist[ii]]))
		if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   itmp=searchindexlist[i]*dimension;
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[itmp+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	dsqrt=sqrt(dmin[K-1]/dimension);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
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
		    //if(means[searchindexlist[p-j]]<=mmin) //The flag set when special condition is satisfied
			if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if((int)p-j<low)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=searchindexlist[(p-j)]*dimension;
			  for(k=0;k<dimension;k++)
			  {
			    dtmp=query[k]-database[itmp+k];
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
			    dsqrt=sqrt(dmin[K-1]/dimension);
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
		    //if(means[searchindexlist[p+j]]>=mmax) //The flag set when special condition is satisfied
			if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=searchindexlist[(p+j)]*dimension;
			  for(k=0;k<dimension;k++)
			  {
			   	 dtmp=query[k]-database[itmp+k];
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
			    dsqrt=sqrt(dmin[K-1]/dimension);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
			  }   
			}
		  }
	  }
	  j=j+1;
	}

    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=searchindexlist[index[n]];
    }

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
    delete []dmin;
    delete []index;
    return 0;
}
//EEKNNSMethodForIterative
int CRetrieveMethod::EEKNNSMethodForIterative(double *query,double querymean,double queryvariance, double *database,double *means,double *variances,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result,DWORD *searchindexlist)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt, dsqrtv;//sqrt sqrtv distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    DWORD I=databasesize;
    DWORD K;
	//If value_K is bigger than the total number of vectors
	if(I<value_K) K=I;
	else K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    //+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    //if(mx<=means[searchindexlist[ii]])p=ii;
	if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    //else if(mx>=means[searchindexlist[jj]])p=jj;
	else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        //if(mx<=means[searchindexlist[p]])
		if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        //if(fabs(mx-means[searchindexlist[jj]])>=fabs(mx-means[searchindexlist[ii]]))
		if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   itmp=searchindexlist[i]*dimension;
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[itmp+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	//Get the sqrt sqrtv distance for vector[K-1]
	dsqrt=sqrt(dmin[K-1]/dimension);
	dsqrtv=sqrt(dmin[K-1]);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
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
		    //if(means[searchindexlist[p-j]]<=mmin) //The flag set when special condition is satisfied
			if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(variances[p-j]>vmin&&variances[p-j]<vmax)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=searchindexlist[(p-j)]*dimension;
			  for(k=0;k<dimension;k++)
			  {
			    dtmp=query[k]-database[itmp+k];
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
			    //update the mmax mmin vmax vmin
			    //The new dsqrt dsqrtv
			    dsqrt=sqrt(dmin[K-1]/dimension);
				dsqrtv=sqrt(dmin[K-1]);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
				//The vmax and vmin
	            vmax=vx+dsqrtv;
	            vmin=vx-dsqrtv;
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
		    //if(means[searchindexlist[p+j]]>=mmax) //The flag set when special condition is satisfied
			if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(variances[p+j]>vmin&&variances[p+j]<vmax)
			{
              ///Computing the distance by PDS
			  pds=0.0;
			  itmp=searchindexlist[(p+j)]*dimension;
			  for(k=0;k<dimension;k++)
			  {
			   	 dtmp=query[k]-database[itmp+k];
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
			    //update the mmax mmin vmax vmin
			    //The new dsqrt dsqrtv
			    dsqrt=sqrt(dmin[K-1]/dimension);
				dsqrtv=sqrt(dmin[K-1]);
	            //The new mmax and mmin
	            mmax=mx+dsqrt;
	            mmin=mx-dsqrt;
				//The vmax and vmin
	            vmax=vx+dsqrtv;
	            vmin=vx-dsqrtv;
			  }   
			}
		  }
	  }
	  j=j+1;
	}

    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=searchindexlist[index[n]];
    }

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
    delete []dmin;
    delete []index;
    return 0;
}

//EEEKNNSMethodForIterative
int CRetrieveMethod::EEEKNNSMethodForIterative(double *query,double querymean,double queryvariance, double *database,double *means,double *variances,DWORD databasesize,DWORD value_K, WORD dimension,RETRIEVEDRESULT *result,DWORD *searchindexlist)
{
    DWORD p;//The index of least mean distance candidate
    int i,j,k;//i for index[i] and dmin[i]  //j for the main loop, k for dimension
    int m,n,w;//for the loop 
    double dsqrt, dsqrtv;//sqrt sqrtv distance for vector[K-1]
    double dtmp=0.0,pds;  ///temp double varaiable
    double mmax,mmin,vmax,vmin;
    LONG low,high;//The lower and higher limits to be searched
    BOOL flagup=FALSE,flagdown=FALSE;//If stop in the two search directions
    DWORD itmp;
    DWORD I=databasesize;
    DWORD K;
	//If value_K is bigger than the total number of vectors
	if(I<value_K) K=I;
	else K=value_K;
	
	double *dmin= new double [K];//distance for K vectors
    if(dmin==NULL)return -1;
    DWORD *index= new DWORD [K]; //Indices For K vectors in the current search list
    if(index==NULL)
	{
	  delete [] dmin;
	  return -1;
	}
    //+++++++++++++Get the initial matching index p in the current mean list+++++++++++++++
    double mx=querymean;
	double vx=queryvariance;
    //The low
    DWORD ii=0;
    //The upper
    DWORD jj=I-1;
    //If smaller than the minimum mean
    //if(mx<=means[searchindexlist[ii]])p=ii;
	if(mx<=means[ii])p=ii;
    //If smaller than the maximum mean
    //else if(mx>=means[searchindexlist[jj]])p=jj;
	else if(mx>=means[jj])p=jj;
    else
	{
      while(jj-ii>1)
	  {
        p=(ii+jj)/2;
        //if(mx<=means[searchindexlist[p]])
		if(mx<=means[p])
	      jj=p;
        else 
	      ii=p;
        //if(fabs(mx-means[searchindexlist[jj]])>=fabs(mx-means[searchindexlist[ii]]))
		if(fabs(mx-means[jj])>=fabs(mx-means[ii]))
	      p=ii;
        else
	      p=jj;
	  }
	}
    //++++++++++Get the lower and upper limits+++++++++
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
    
	///If K==I then no up and down search is performed
	if(K==I)
	{
	  flagup=TRUE;
	  flagdown=TRUE;
	}

	//++++++++++++++calculate the K distances+++++++++++
    for(i=low;i<=high;i++)
	{
	   dmin[i-low]=0.0;
	   index[i-low]=i;// get the index[i] 
	   itmp=searchindexlist[i]*dimension;
	   for(k=0;k<dimension;k++)
	   {
		 dtmp=query[k]-database[itmp+k];
	     dmin[i-low]+=dtmp*dtmp;
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
	//Get the sqrt sqrtv distance for vector[K-1]
	dsqrt=sqrt(dmin[K-1]/dimension);
	dsqrtv=sqrt(dmin[K-1]);
	//The mmax and mmin
	mmax=mx+dsqrt;
	mmin=mx-dsqrt;
	//The vmax and vmin
	vmax=vx+dsqrtv;
	vmin=vx-dsqrtv;
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
		    //if(means[searchindexlist[p-j]]<=mmin) //The flag set when special condition is satisfied
			if(means[p-j]<=mmin) //The flag set when special condition is satisfied
		     flagdown=TRUE;
		    else if(variances[p-j]>vmin&&variances[p-j]<vmax)
			{
              dtmp=(variances[p-j]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-means[p-j]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
				itmp=searchindexlist[(p-j)]*dimension;
			    for(k=0;k<dimension;k++)
				{
			      dtmp=query[k]-database[itmp+k];
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
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
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
		    //if(means[searchindexlist[p+j]]>=mmax) //The flag set when special condition is satisfied
			if(means[p+j]>=mmax) //The flag set when special condition is satisfied
		      flagup=TRUE;
		    else if(variances[p+j]>vmin&&variances[p+j]<vmax)
			{
              dtmp=(variances[p+j]-vx);
			  dtmp=dtmp*dtmp;
			  pds=(mx-means[p+j]);
			  pds=pds*pds*dimension;
			  pds+=dtmp;
			  if(pds<dmin[K-1])
			  {
			    ///Computing the distance by PDS
			    pds=0.0;
				itmp=searchindexlist[(p+j)]*dimension;
			    for(k=0;k<dimension;k++)
				{
			   	 dtmp=query[k]-database[itmp+k];
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
			      //update the mmax mmin vmax vmin
			      //The new dsqrt dsqrtv
			      dsqrt=sqrt(dmin[K-1]/dimension);
				  dsqrtv=sqrt(dmin[K-1]);
	              //The new mmax and mmin
	              mmax=mx+dsqrt;
	              mmin=mx-dsqrt;
				  //The vmax and vmin
	              vmax=vx+dsqrtv;
	              vmin=vx-dsqrtv;
				}
			  }   
			}
		  }
	  }
	  j=j+1;
	}

    for(n=0;n<(int)K;n++)
	{
     result[n].m_fDistance=(float)dmin[n];
     result[n].m_dwImageIndex=searchindexlist[index[n]];
    }

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
    delete []dmin;
    delete []index;
    return 0;
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
	//and Bubble sort for current computed distances
	FullSearchMethod(QueryImageFeatureVector.m_dNormalizedFeature,
	(lpFeatureVector+(*RetrievedNumber))->m_dNormalizedFeature,
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
    for(number=0;number<VectorNumberTobeSearched;number++)
	  RetrievedResult[number+(*RetrievedNumber)].m_dwImageIndex+=(*RetrievedNumber);
    
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

int CRetrieveMethod::FullSearchRetrieveMethod2(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
	clock_t time1,time2;
	DWORD number,check,l;
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
	//and Bubble sort for current computed distances
	FullSearchMethod2(QueryImageFeatureVector.m_dNormalizedFeature,
	(lpFeatureVector+(*RetrievedNumber))->m_dNormalizedFeature,
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
    for(number=0;number<VectorNumberTobeSearched;number++)
	  RetrievedResult[number+(*RetrievedNumber)].m_dwImageIndex+=(*RetrievedNumber);
    
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
  int i,k;
	
  //Judge the parameter
  if(iteratived==TRUE&&searchindexlist==NULL)return -1;
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>TotalVectorNumber||VectorNumberTobeSearched<1)return -3;//Larger than 50% of the whole database
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  
  double *means=new double [TotalVectorNumber-(*RetrievedNumber)];
  if(means==NULL) return -2;
  
  //get the initial time
  time1=clock();
  
  //Perform the EKNNS
  if(iteratived==FALSE)
  {
    for(i=0;i<(int)(TotalVectorNumber-(*RetrievedNumber));i++)
      means[i]=lpFeatureVector[i].m_dNAverage;
	k=EKNNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,
	lpFeatureVector->m_dNormalizedFeature,means,TotalVectorNumber-(*RetrievedNumber),
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
  }
  else
  {
	for(i=0;i<(int)(TotalVectorNumber-(*RetrievedNumber));i++)
	  means[i]=lpFeatureVector[searchindexlist[i]].m_dNAverage;
    k=EKNNSMethodForIterative(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,
	lpFeatureVector->m_dNormalizedFeature,means,TotalVectorNumber-(*RetrievedNumber),
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber),searchindexlist);
  }
  
  //get the finished time
  time2=clock();
  
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  
  delete []means;
  return k;
}


/**************************************
        *   Public function: EEKNNSRetrieveKeyMethod(...
        *
        *   This function is used to EEKNNS algorithm based retrieval only the first page
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
int CRetrieveMethod::EEKNNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime, BOOL iteratived,DWORD *searchindexlist)
{
  clock_t time1,time2; ///Define the time variable
  int i,k;
	
  //Judge the parameter
  if(iteratived==TRUE&&searchindexlist==NULL)return -1;
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>TotalVectorNumber||VectorNumberTobeSearched<1)return -3;//Larger than 50% of the whole database
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  
  double *means=new double [TotalVectorNumber-(*RetrievedNumber)];
  if(means==NULL) return -2;
  
  double *variances=new double [TotalVectorNumber-(*RetrievedNumber)];
  if(variances==NULL)
  {
	 delete [] means;
	 return -2;
  }
  //get the initial time
  time1=clock();
  
  //Perform the EEKNNS
  if(iteratived==FALSE)
  {
    for(i=0;i<(int)(TotalVectorNumber-(*RetrievedNumber));i++)
	{
		means[i]=lpFeatureVector[i].m_dNAverage;
		variances[i]=lpFeatureVector[i].m_dNVariance;
	}
	k=EEKNNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
	lpFeatureVector->m_dNormalizedFeature,means,variances,TotalVectorNumber-(*RetrievedNumber),
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
  }
  else
  {
	for(i=0;i<(int)(TotalVectorNumber-(*RetrievedNumber));i++)
	{
		means[i]=lpFeatureVector[searchindexlist[i]].m_dNAverage;
		variances[i]=lpFeatureVector[searchindexlist[i]].m_dNVariance;
	}
    k=EEKNNSMethodForIterative(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
	lpFeatureVector->m_dNormalizedFeature,means,variances,TotalVectorNumber-(*RetrievedNumber),
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber),searchindexlist);
  }
  
  //get the finished time
  time2=clock();
  
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  
  delete []means;
  delete []variances;
  return k;
}

/**************************************
        *   Public function: EEEKNNSRetrieveKeyMethod(...
        *
        *   This function is used to EEEKNNS algorithm based retrieval only the first page
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
int CRetrieveMethod::EEEKNNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime, BOOL iteratived,DWORD *searchindexlist)
{
  clock_t time1,time2; ///Define the time variable
  int i,k;
	
  //Judge the parameter
  if(iteratived==TRUE&&searchindexlist==NULL)return -1;
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>TotalVectorNumber||VectorNumberTobeSearched<1)return -3;//Larger than 50% of the whole database
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  
  double *means=new double [TotalVectorNumber-(*RetrievedNumber)];
  if(means==NULL) return -2;
  
  double *variances=new double [TotalVectorNumber-(*RetrievedNumber)];
  if(variances==NULL)
  {
	 delete [] means;
	 return -2;
  }
  //get the initial time
  time1=clock();
  
  //Perform the EEEKNNS
  if(iteratived==FALSE)
  {
    for(i=0;i<(int)(TotalVectorNumber-(*RetrievedNumber));i++)
	{
		means[i]=lpFeatureVector[i].m_dNAverage;
		variances[i]=lpFeatureVector[i].m_dNVariance;
	}
	k=EEEKNNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
	lpFeatureVector->m_dNormalizedFeature,means,variances,TotalVectorNumber-(*RetrievedNumber),
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
  }
  else
  {
	for(i=0;i<(int)(TotalVectorNumber-(*RetrievedNumber));i++)
	{
		means[i]=lpFeatureVector[searchindexlist[i]].m_dNAverage;
		variances[i]=lpFeatureVector[searchindexlist[i]].m_dNVariance;
	}
    k=EEEKNNSMethodForIterative(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
	lpFeatureVector->m_dNormalizedFeature,means,variances,TotalVectorNumber-(*RetrievedNumber),
	VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber),searchindexlist);
  }
  
  //get the finished time
  time2=clock();
  
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  
  delete []means;
  delete []variances;
  return k;
}

/**************************************
        *   Public function: EEEKNNSinVQNNRetrieveKeyMethod(...
        *
        *   This function is used to EEEKNNS algorithm based retrieval only in VQ nearest cluster
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			-RetrievedNumber, Current retrieved number of images
			-VectorNumberTobeSearched, the number of vectors to be compared this time
		    -codeword, with mean and variances
			-booksize, the size of codebook
			-numincluster
			output
			-RetrievedNumber, retrieved number of images up to now
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time up to now?
			return
			0: normal
			-1: parameter error
			-2: memory error
			-3: Retrieved number overflow
**************************************/

int CRetrieveMethod::EEEKNNSinVQNNRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,WORD booksize,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,double *codeword,DWORD *numincluster,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i,k,sum;
  RETRIEVEDRESULT p;
  //Judge the parameter
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  if((*RetrievedNumber)>=(long int)TotalVectorNumber)return -3;
  if(VectorNumberTobeSearched>TotalVectorNumber||VectorNumberTobeSearched<1)return -3;//Larger than 50% of the whole database
  if(VectorNumberTobeSearched+(*RetrievedNumber)>TotalVectorNumber)return -3;
  
  //get the initial time
  time1=clock();
  //find the best-match codeword of the query image
  EEENNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,codeword,booksize,VectorDimension,&p);
  //get the position of the first vector in this cluster
  sum=0;
  for(i=0;i<(int)p.m_dwImageIndex;i++)
  {
	sum+=numincluster[i];
  }
  
  //if the vector number is less than to be searched
  if(numincluster[p.m_dwImageIndex]<=VectorNumberTobeSearched)
  {
    VectorNumberTobeSearched=numincluster[p.m_dwImageIndex];
	FullSearchMethod(QueryImageFeatureVector.m_dNormalizedFeature,(lpFeatureVector+sum)->m_dNormalizedFeature,VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
  }
  else
  {
    double *means=new double [numincluster[p.m_dwImageIndex]];
    if(means==NULL) return -2;
    double *variances=new double [numincluster[p.m_dwImageIndex]];
    if(variances==NULL)
	{
	 delete [] means;
	 return -2;
	}
    //Perform the EEEKNNS
    for(i=0;i<(int)numincluster[p.m_dwImageIndex];i++)
	{
	  means[i]=lpFeatureVector[sum+i].m_dNAverage;
	  variances[i]=lpFeatureVector[sum+i].m_dNVariance;
	}
    k=EEEKNNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
    (lpFeatureVector+sum)->m_dNormalizedFeature,means,variances,numincluster[p.m_dwImageIndex],
    VectorNumberTobeSearched,VectorDimension,RetrievedResult+(*RetrievedNumber));
	delete []means;
    delete []variances;
  }
  for(i=0;i<(int)VectorNumberTobeSearched;i++)
  {
     RetrievedResult[(*RetrievedNumber)+i].m_dwImageIndex+=sum;
  }
  //get the finished time
  time2=clock();
  //sum the retrieved vectors
  (*RetrievedNumber)+=VectorNumberTobeSearched;
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  return k;
}


/**************************************
        *   Public function: ENNSRetrieveMethod(...
        *
        *   This function is used to ENNS algorithm based retrieval only the first image 
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			output
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time
			return
			0: normal
			-1: parameter error
			-2: memory error
**************************************/
int CRetrieveMethod::ENNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i;
  //Judge the parameter
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  double *means=new double [TotalVectorNumber];
  if(means==NULL)return -2;
  //get the initial time
  time1=clock();
  
  //means initialization
  for(i=0;i<(int)TotalVectorNumber;i++)
    means[i]=lpFeatureVector[i].m_dNAverage;
  
  //ENNS method
  ENNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,
  QueryImageFeatureVector.m_dNAverage,
  lpFeatureVector->m_dNormalizedFeature,
  means,TotalVectorNumber,
  VectorDimension,RetrievedResult);
  
  //get the finished time
  time2=clock();
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  
  delete []means;
  return 0;
}

/**************************************
        *   Public function: EENNSRetrieveMethod(...
        *
        *   This function is used to EENNS algorithm based retrieval only the first image 
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			output
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time
			return
			0: normal
			-1: parameter error
			-2: memory error
**************************************/
int CRetrieveMethod::EENNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i;
  //Judge the parameter
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  double *means=new double [TotalVectorNumber];
  if(means==NULL)return -2;
  double *variances=new double [TotalVectorNumber];
  if(variances==NULL)
  {
	delete []means;
	return -2;
  }
  //get the initial time
  time1=clock();
  
  //means initialization
  for(i=0;i<(int)TotalVectorNumber;i++)
  {
	  means[i]=lpFeatureVector[i].m_dNAverage;
  	  variances[i]=lpFeatureVector[i].m_dNVariance;
  }
  
  //EENNS method
  EENNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,
  QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
  lpFeatureVector->m_dNormalizedFeature,
  means,variances,TotalVectorNumber,
  VectorDimension,RetrievedResult);
  
  //get the finished time
  time2=clock();
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  
  delete []means;
  delete []variances;
  return 0;
}

/**************************************
        *   Public function: EEENNSRetrieveMethod(...
        *
        *   This function is used to EEENNS algorithm based retrieval only the first image 
        *   
	    *   input
		    -QueryImageFeatureVector  The query image feature vector
			-lpFeatureVector  The database feature vectors
            -VectorDimension, The dimension of feature vector
			-TotalVectorNumber,The total number of vectors to be compared
			output
			-RetrievedResult, the retrieval results
			-RetrieveTime, the retrieval time
			return
			0: normal
			-1: parameter error
			-2: memory error
**************************************/
int CRetrieveMethod::EEENNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime)
{
  clock_t time1,time2; ///Define the time variable
  int i;
  //Judge the parameter
  if(TotalVectorNumber<1||TotalVectorNumber>MAX_IMAGE_NUMBER)return -1;
  if(VectorDimension<1||VectorDimension>MAX_FEATUREVECTOR_DIMENSION)return -1;
  if(lpFeatureVector==NULL||RetrievedResult==NULL)return -2;
  double *means=new double [TotalVectorNumber];
  if(means==NULL)return -2;
  //get the initial time
  time1=clock();
  
  double *variances=new double [TotalVectorNumber];
  if(variances==NULL)
  {
	delete []means;
	return -2;
  }
  //get the initial time
  time1=clock();
  
  //means initialization
  for(i=0;i<(int)TotalVectorNumber;i++)
  {
	  means[i]=lpFeatureVector[i].m_dNAverage;
  	  variances[i]=lpFeatureVector[i].m_dNVariance;
  }
  
  //EEENNS method
  EEENNSMethod(QueryImageFeatureVector.m_dNormalizedFeature,
  QueryImageFeatureVector.m_dNAverage,QueryImageFeatureVector.m_dNVariance,
  lpFeatureVector->m_dNormalizedFeature,
  means,variances,TotalVectorNumber,
  VectorDimension,RetrievedResult);
  
  //get the finished time
  time2=clock();
  //sum the retrieved time
  (*RetrieveTime)+=(double)(time2-time1)/CLOCKS_PER_SEC*1000000.0;
  
  delete []means;
  delete []variances;
  return 0;
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

/////////////////////////////////////////////////////////////////////////////////
///////////The Program of DCT and the IDCT in Unsigned Char Format//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//The Define of DCT--Discrete Cosine Transform
//F(k1,k2)=DCT(f(n1,n2))=c1[k1]c2[k2]∑(i=0:1:N1-1)∑(j=0:1:N2-1)f(i,j)
//						*cos(((2*n1+1)/(2*N1))*PI*k1)*cos(((2*n2+1)/(2*N2))*PI*k2)
//c1[i]=sqrt(1/N1)	if i==0; c1[i]=sqrt(2/N1)	if i!=0; 
//c2[i]=sqrt(1/N2)	if i==0; c2[j]=sqrt(2/N2)	if i!=0; 
void CRetrieveMethod::DCT(unsigned char *OriginalImageBlock[BLOCKHEIGHT],double *DCTBlock[BLOCKHEIGHT],int blockheight,int blockwidth)	//input[0]	the row pointer of the input matrix
{
	int i;                        //Define the repeating variable
	int timerow,timecolumn;		  //Define the input interative variable(Time Domain)
	int	frerow,frecolumn;		  //Define the output interative variable(Frequency Domain)
	double row[BLOCKHEIGHT];	  //Define the parameter of the first parameter
	double column[BLOCKWIDTH]; //Define the parameter of the second parameter
	double temp;	              //Define the temporary variable 
	double temp1;	              //Define the first temporary variable 
	double temp2;	              //Define the second temporary variable 
	
	//Initiaize the transform parameters
	row[0]=sqrt(1.0/blockheight);
	column[0]=sqrt(1.0/blockwidth);	
	for(i=1;i<blockheight;i++)
	{
	  row[i]=sqrt(2.0/blockheight);
	}
	for(i=1;i<blockwidth;i++)
	{
	  column[i]=sqrt(2.0/blockwidth);
	}
	
	//Calculate the DCT of blockheight*blockwidth points 
	for(frerow=0;frerow<blockheight;frerow++)
	{
		for(frecolumn=0;frecolumn<blockwidth;frecolumn++)
		{
			//Calculate the DCT for one point 
			temp1=0.0;
			for(timerow=0;timerow<blockheight;timerow++)
			{
				temp2=0;
				for(timecolumn=0;timecolumn<blockwidth;timecolumn++)
				{
					temp=(2.0*timecolumn+1.0)/(2.0*blockwidth)*frecolumn*PI;
					temp2=temp2+OriginalImageBlock[timerow][timecolumn]*cos(temp);
				}
				temp=(2.0*timerow+1.0)/(2.0*blockheight)*frerow*PI;
				temp1=temp1+temp2*cos(temp);
			}
			DCTBlock[frerow][frecolumn]=temp1*row[frerow]*column[frecolumn];
		}
	}
}

//IDCT(F(k1,k2))=(1/N1)*(1/N2)∑(k1=0:1:N1-1)∑(k2=0:1:N2-1)c1[k1]c2[k2]*F(k1,k2)
//			*cos(((2*n1+1)/(2*N1))*PI*k1)*cos(((2*n2+1)/(2*N2))*PI*k2)
//c1[i]=sqrt(1/N1)	if i==0; c1[i]=sqrt(2/N1)	if i!=0; 
//c2[i]=sqrt(1/N2)	if i==0; c2[j]=sqrt(2/N2)	if i!=0; 
void CRetrieveMethod::IDCT(double *DCTBlock[BLOCKHEIGHT],unsigned char *ReconstructedImageBlock[BLOCKHEIGHT],int blockheight,int blockwidth)	//input[0]	the row pointer of the input matrix
{
	int i;                        //Define the repeating variable
	int	frerow,frecolumn;		  //Define the input interative variable(Frequency Domain)
	int timerow,timecolumn;		  //Define the output interative variable(Time Domain)
	double row[BLOCKHEIGHT];	  //Define the parameter of the first parameter
	double column[BLOCKWIDTH]; //Define the parameter of the second parameter
	double temp;	              //Define the temporary variable 
	double temp1;	              //Define the first temporary variable 
	double temp2;	              //Define the second temporary variable 

	//Initiaize the transform parameters
	row[0]=sqrt(1.0/blockheight);
	column[0]=sqrt(1.0/blockwidth);	
	for(i=1;i<blockheight;i++)
	{
	  row[i]=sqrt(2.0/blockheight);
	}
	for(i=1;i<blockwidth;i++)
	{
	  column[i]=sqrt(2.0/blockwidth);
	}
    //Calculate the IDCT of blockheight*blockwidth points 
	for(timerow=0;timerow<blockheight;timerow++)
	{
		for(timecolumn=0;timecolumn<blockwidth;timecolumn++)
		{
			//Calculate the IDCT of one point
			temp1=0.0;
			for(frerow=0;frerow<blockheight;frerow++)
			{
				temp2=0.0;
				for(frecolumn=0;frecolumn<blockwidth;frecolumn++)
				{
					temp=(2.0*timecolumn+1.0)/(2.0*blockwidth)*frecolumn*PI;
					temp2=temp2+DCTBlock[frerow][frecolumn]*cos(temp)*column[frecolumn];
				}
				temp=(2.0*timerow+1.0)/(2.0*blockheight)*frerow*PI;				
				temp1=temp1+temp2*cos(temp)*row[frerow];
			}
			//The Rounding Operation (To The Nearest Integer Number)
			if(temp1>=254.5)
			{
				ReconstructedImageBlock[timerow][timecolumn]=255;
			}
			else 
			{
				if(temp1<0.5)
				{
				  ReconstructedImageBlock[timerow][timecolumn]=0;
				}
				else
				{
				  ReconstructedImageBlock[timerow][timecolumn]=(unsigned char)(temp1+0.5);
				}
			}
		}
	}
}
void CRetrieveMethod::DCT2To1Or1To2(double *DCT2[BLOCKHEIGHT],double *DCT1,int blockheight,int blockwidth,int flag)
{
  int i,length;
  int x,y;
  length=blockwidth*blockheight;
  x=0;
  y=0;
  for(i=0;i<length;i++) 
  {
	  if(flag==0)
	  DCT1[i]=DCT2[x][y];
	  else
	  DCT2[x][y]=DCT1[i];
	  if(x==0)
	  {
		  if(y==0)
		  {
			  y=y+1;
		  }
		  else
		  {
			  if(y%2==0)
			  {
				  y=y+1;
			  }
			  else
			  {
				  x=x+1;
				  y=y-1;
			  }
		  }
	  }
	  else
	  {
		  if(x==7)
		  {
			  if(y!=7)
			  {
			  	  if(y%2==0)
				  {
					  y=y+1;
				  }
				  else
				  {
					  x=x-1;
					  y=y+1;
				  }
			  }
		  }
		  else
		  {
			  if(y==0)
			  {
				  if(x%2==0)
				  {
					  x=x-1;
					  y=y+1;
				  }
				  else
				  {
					  x=x+1;
				  }
			  }
			  else
			  {
				  if (y==7)
				  {
					  if(x%2==0)
					  {
						  x=x+1;
						  y=y-1;
					  }
					  else
					  {
						  x=x+1;
					  }
				  }
				  else
				  {
					  if((x+y)%2==0)
					  {
						  x=x-1;
						  y=y+1;
					  }
					  else
					  {
						  x=x+1;
						  y=y-1;
					  }
				  }

			  }
		  }
	  }
  }
}

short int CRetrieveMethod::FSDCTVQ256GrayImageEncode(unsigned long int blocks,unsigned short int booksize,unsigned short int dimension,float *SourceVector[MAXENCODEVECTORS],float (*CodeVector)[DIMENSION1],unsigned short int *index,double *Time)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//blockwidth: stands for the width of the image block
//blockheight: stands for the height of the image block
//         the vector dimension=blockwidth*blockheight
//         the vector dimension should be smaller than 64
// SourceVector[MAXENCODEVECTORS][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXENCODEVECTORS]: each element stands for 
//                       the index for a trainning vector
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
{
   unsigned long int i;
   unsigned short int j,k;
   double d1,d,min;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   if(booksize>MAXBOOKSIZE)return -1;
   if(blocks>MAXENCODEVECTORS)return -2;
   if(dimension>VECTORDIMENSION||dimension<=0)return -3;
   
   ltime1=clock();
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     index[i]=0;
  	 min=0.0;
     for(k=0;k<dimension;k++)
	 {   
       min=min+((double)SourceVector[i][k]-(double)CodeVector[0][k])*((double)SourceVector[i][k]-(double)CodeVector[0][k]);
	 } 
	 for(j=1;j<booksize;j++)
	 {
	   d=0.0;
       for(k=0;k<dimension;k++)
	   {  
         d=d+((double)SourceVector[i][k]-(double)CodeVector[j][k])*((double)SourceVector[i][k]-(double)CodeVector[j][k]);
	   }
	   if(d<min)
	   {
	     min=d;
	     index[i]=(unsigned short int)j;
	   }
	 }
	 d1=d1+min;
   }
   ltime2=clock();
   *Time+=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   return 0;
}

short int CRetrieveMethod::FSVQ256GrayImageEncode(unsigned long int blocks,unsigned short int booksize,unsigned short int dimension,unsigned char *SourceVector[VQMAXENCODEVECTORS],unsigned char (*CodeVector)[VQDIMENSION],unsigned short int *index,double *Time)
{
   unsigned long int i;
   unsigned short int j,k;
   double d1,d,min;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   if(booksize>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
   if(dimension>VQDIMENSION||dimension<=0)return -3;
   
   ltime1=clock();
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     index[i]=0;
  	 min=0.0;
     for(k=0;k<dimension;k++)
	 {   
       min=min+((double)SourceVector[i][k]-(double)CodeVector[0][k])*((double)SourceVector[i][k]-(double)CodeVector[0][k]);
	 } 
	 for(j=1;j<booksize;j++)
	 {
	   d=0.0;
       for(k=0;k<dimension;k++)
	   {  
         d=d+((double)SourceVector[i][k]-(double)CodeVector[j][k])*((double)SourceVector[i][k]-(double)CodeVector[j][k]);
	   }
	   if(d<min)
	   {
	     min=d;
	     index[i]=(unsigned short int)j;
	   }
	 }
	 d1=d1+min;
   }
   ltime2=clock();
   *Time+=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   return 0;

}



short int CRetrieveMethod::FSDCTVQScalar256GrayImageEncode(unsigned long int blocks,unsigned short int booksize,float *SourceVector,float *CodeVector,unsigned short int *index,double *Time)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//blockwidth: stands for the width of the image block
//blockheight: stands for the height of the image block
//         the vector dimension=blockwidth*blockheight
//         the vector dimension should be smaller than 64
// SourceVector[MAXENCODEVECTORS][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXENCODEVECTORS]: each element stands for 
//                       the index for a trainning vector
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
{
   unsigned long int i;
   unsigned short int j;
   double d1,d,min;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   if(booksize>MAXBOOKSIZE)return -1;
   if(blocks>MAXENCODEVECTORS)return -2;
      
   ltime1=clock();
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     index[i]=0;
  	 min=((double)SourceVector[i]-(double)CodeVector[0])*((double)SourceVector[i]-(double)CodeVector[0]);
	 for(j=1;j<booksize;j++)
	 {
	   d=((double)SourceVector[i]-(double)CodeVector[j])*((double)SourceVector[i]-(double)CodeVector[j]);
	   if(d<min)
	   {
	     min=d;
	     index[i]=(unsigned short int)j;
	   }
	 }
	 d1=d1+min;
   }
   ltime2=clock();
   *Time+=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   return 0;
}

short int CRetrieveMethod::FSVQScalar256GrayImageEncode(unsigned long int blocks,unsigned short int booksize,unsigned char *SourceVector,unsigned char *CodeVector,unsigned short int *index,double *Time)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//blockwidth: stands for the width of the image block
//blockheight: stands for the height of the image block
//         the vector dimension=blockwidth*blockheight
//         the vector dimension should be smaller than 64
// SourceVector[MAXENCODEVECTORS][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXENCODEVECTORS]: each element stands for 
//                       the index for a trainning vector
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
{
   unsigned long int i;
   unsigned short int j;
   double d1,d,min;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   if(booksize>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
      
   ltime1=clock();
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     index[i]=0;
  	 min=((double)SourceVector[i]-(double)CodeVector[0])*((double)SourceVector[i]-(double)CodeVector[0]);
	 for(j=1;j<booksize;j++)
	 {
	   d=((double)SourceVector[i]-(double)CodeVector[j])*((double)SourceVector[i]-(double)CodeVector[j]);
	   if(d<min)
	   {
	     min=d;
	     index[i]=(unsigned short int)j;
	   }
	 }
	 d1=d1+min;
   }
   ltime2=clock();
   *Time+=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   return 0;
}


short int CRetrieveMethod::FSDCTVQ256GrayImageEncode(unsigned long int blocks,unsigned short int booksize,unsigned short int dimension,float *SourceVector[MAXENCODEVECTORS],float (*CodeVector)[DIMENSION2],unsigned short int *index,double *Time)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//blockwidth: stands for the width of the image block
//blockheight: stands for the height of the image block
//         the vector dimension=blockwidth*blockheight
//         the vector dimension should be smaller than 64
// SourceVector[MAXENCODEVECTORS][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXENCODEVECTORS]: each element stands for 
//                       the index for a trainning vector
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
{
   unsigned long int i;
   unsigned short int j,k;
   double d1,d,min;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   if(booksize>MAXBOOKSIZE)return -1;
   if(blocks>MAXENCODEVECTORS)return -2;
   if(dimension>VECTORDIMENSION||dimension<=0)return -3;
   
   ltime1=clock();
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     index[i]=0;
  	 min=0.0;
     for(k=0;k<dimension;k++)
	 {   
       min=min+((double)SourceVector[i][k]-(double)CodeVector[0][k])*((double)SourceVector[i][k]-(double)CodeVector[0][k]);
	 } 
	 for(j=1;j<booksize;j++)
	 {
	   d=0.0;
       for(k=0;k<dimension;k++)
	   {  
         d=d+((double)SourceVector[i][k]-(double)CodeVector[j][k])*((double)SourceVector[i][k]-(double)CodeVector[j][k]);
	   }
	   if(d<min)
	   {
	     min=d;
	     index[i]=(unsigned short int)j;
	   }
	 }
	 d1=d1+min;
   }
   ltime2=clock();
   *Time+=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   return 0;
}

short int CRetrieveMethod::DCTVQ256GrayImageDecode(unsigned long int blocks,unsigned short int booksize0,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,unsigned short int width,unsigned short int *index1,unsigned short int *index2,unsigned short int *index3,float *DCTSourceVector[MAXENCODEVECTORS],float *CodeVector1,float (*CodeVector2)[DIMENSION1],float (*CodeVector3)[DIMENSION2],unsigned char *pixel,int component)
{
   unsigned long int i,j,k,l;
   unsigned short int dimension,height;
   unsigned short int la,lb,ba,bb;
   double DCT1D[VECTORDIMENSION],DCTBlock[BLOCKHEIGHT][BLOCKWIDTH];
   unsigned char IDCTBlock[BLOCKHEIGHT][BLOCKWIDTH];
   double *DCTBlock1[BLOCKHEIGHT];
   unsigned char *IDCTBlock1[BLOCKHEIGHT];
   dimension=blockwidth*blockheight;
   if(booksize0<16||booksize0>MAXBOOKSIZE||booksize1<16||booksize1>MAXBOOKSIZE||booksize2<16||booksize2>MAXBOOKSIZE)return -1;
   if(blocks>MAXENCODEVECTORS)return -2;
   if(dimension>VECTORDIMENSION)return -3;

   ba=blockwidth;
   bb=blockheight;
   height=(unsigned short int)(blocks*(unsigned long int)dimension/(unsigned long)width);
   la=width/ba;
   lb=height/bb;
   for(i=0;i<bb;i++)
   {
	 DCTBlock1[i]=DCTBlock[i];
	 IDCTBlock1[i]=IDCTBlock[i];
   }
   for(l=0;l<lb;l++)
   {
	 for(k=0;k<la;k++)
	 {
	   for(i=0;i<dimension;i++)
	     DCT1D[i]=DCTSourceVector[l*la+k][i];
	   DCT1D[0]=CodeVector1[index1[k+l*la]];
	   for(i=0;i<DIMENSION1;i++)
		 DCT1D[i+POSITION1]=CodeVector2[index2[k+l*la]][i];
	   for(i=0;i<DIMENSION2;i++)
		DCT1D[i+POSITION2]=CodeVector3[index3[k+l*la]][i];
	   //for(i=20;i<64;i++)
		//DCT1D[i]=0.0;
       DCT2To1Or1To2(DCTBlock1,DCT1D,bb,ba,1);
	   IDCT(DCTBlock1,IDCTBlock1,bb,ba);
	   long int linebytes;
	   linebytes=(width+3)/4*4;
	   for(j=0;j<bb;j++)
	   {
	     for(i=0;i<ba;i++)
		 {
		   if(component==0)
		   {
		     if(IDCTBlock1[j][i]<16)IDCTBlock1[j][i]=16;
		     if(IDCTBlock1[j][i]>240)IDCTBlock1[j][i]=240;
		   }
		   else if(component==1)
		   {
		     if(IDCTBlock1[j][i]<16)IDCTBlock1[j][i]=16;
		     if(IDCTBlock1[j][i]>240)IDCTBlock1[j][i]=240;
		   }
		   else if(component==2)
		   {
		     if(IDCTBlock1[j][i]<16)IDCTBlock1[j][i]=16;
		     if(IDCTBlock1[j][i]>235)IDCTBlock1[j][i]=235;
		   }
		   else
		   {
		     if(IDCTBlock1[j][i]<0)IDCTBlock1[j][i]=0;
		     if(IDCTBlock1[j][i]>255)IDCTBlock1[j][i]=255;
		   }
		   
		   pixel[i+k*ba+(j+l*bb)*linebytes]=(unsigned char)IDCTBlock1[j][i];
		 }
	   }
	 }
   }
   return 0;
}

short int CRetrieveMethod::VQ256GrayImageDecode(unsigned long int blocks,unsigned short int booksize,unsigned short int blockwidth,unsigned short int blockheight,unsigned short int width,unsigned short int *index,unsigned char (*CodeVector)[VQDIMENSION],unsigned char *pixel,int component)
{
   unsigned long int i,j,k,l;
   unsigned short int dimension,height;
   unsigned short int la,lb,ba,bb;
   unsigned char Block[VQBLOCKHEIGHT][VQBLOCKWIDTH],bit[VQDIMENSION];
   
   dimension=blockwidth*blockheight;
   if(booksize<64||booksize>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
   if(dimension>VQDIMENSION)return -3;

   ba=blockwidth;
   bb=blockheight;
   height=(unsigned short int)(blocks*(unsigned long int)dimension/(unsigned long)width);
   la=width/ba;
   lb=height/bb;
   for(l=0;l<lb;l++)
   {
	 for(k=0;k<la;k++)
	 {
	   for(i=0;i<VQDIMENSION;i++)
		bit[i]=CodeVector[index[k+l*la]][i];
	   long int linebytes;
	   linebytes=(width+3)/4*4;
	   for(j=0;j<bb;j++)
	   {
	     for(i=0;i<ba;i++)
		 {
		   Block[j][i]=bit[i+j*ba];
		   if(component==0)
		   {
		     if(Block[j][i]<16)Block[j][i]=16;
		     if(Block[j][i]>240)Block[j][i]=240;
		   }
		   else if(component==1)
		   {
		     if(Block[j][i]<16)Block[j][i]=16;
		     if(Block[j][i]>240)Block[j][i]=240;
		   }
		   else if(component==2)
		   {
		     if(Block[j][i]<16)Block[j][i]=16;
		     if(Block[j][i]>235)Block[j][i]=235;
		   }
		   else
		   {
		     if(Block[j][i]<0)Block[j][i]=0;
		     if(Block[j][i]>255)Block[j][i]=255;
		   }
		   pixel[i+k*ba+(j+l*bb)*linebytes]=(unsigned char)Block[j][i];
		 }
	   }
	 }
   }
   return 0;
}

////The Design Methods implemetation begins////
short int CRetrieveMethod::DCTVQLBGCodebookDesign(unsigned long int blocks,unsigned short int booksize,unsigned short int dimension,double e,float (*TrainVector)[DIMENSION1],float (*CodeVector)[DIMENSION1],unsigned short int *index,unsigned long int *number,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//dimension: stands for the dimension of DCT coefficient block
//         the vector dimension should be smaller than 64
//e:  stands for the distortion threshold 
//         e should be larger than 0
// TrainVector[MAXSOURCESIZE][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXSOURCESIZE]: each element stands for 
//                       the index for a trainning vector
// number[MAXBOOKSIZE]: each element stands for 
//                     the number of training vectors 
//                     that close to a codeword
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
// return -4: e set error
{
   int i,l;
   unsigned short int j,k;

   double d0,d1,d,min,dd[DIMENSION1],par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   float tt[DIMENSION1];
   double ms[MAXBOOKSIZE],ttt;
   int iindex; 
   if(booksize>MAXBOOKSIZE||booksize<16)return -1;
   if(blocks<booksize||blocks>MAXINPUTVECTORS)return -2;
   if(dimension>DIMENSION1||dimension<=0)return -3;
   if(e<=0) return -4;   
   
   //Initial codevector Using random number generator
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector[i],TrainVector[l],DIMENSION1*sizeof(float));
   }
   d0=9.99e+60;   
   *iterations=0;
   ltime1=clock();
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize;j++)
	   number[j]=0;
	 for(i=0;i<(int)blocks;i++)
	 {
	    index[i]=0;
		min=0.0;
        for(k=0;k<dimension;k++)
		{   
          min=min+((double)TrainVector[i][k]-(double)CodeVector[0][k])*((double)TrainVector[i][k]-(double)CodeVector[0][k]);
		}
		for(j=1;j<booksize;j++)
		{
		  d=0.0;
		  for(k=0;k<dimension;k++)
		  {			  
		    d=d+((double)TrainVector[i][k]-(double)CodeVector[j][k])*((double)TrainVector[i][k]-(double)CodeVector[j][k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    index[i]=j;
		  }
		}
	    number[index[i]]=number[index[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize;j++)
	 {
	    if(number[j]!=0)
		{
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<(int)blocks;l++)
		  {
		    if(index[l]==j)
			{
			  for(k=0;k<dimension;k++)
			  {
		        dd[k]=dd[k]+(double)TrainVector[l][k];
			  }
			}
		  }
		  for(k=0;k<dimension;k++)
		  {
		    CodeVector[j][k]=(float)(dd[k]/(double)number[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector[j],TrainVector[l],DIMENSION1*sizeof(float));
		}
	 }

	 //codebook sorted by mean of codeword
	 
	 for(i=0;i<booksize;i++)
	 {
	   ms[i]=0.0;
	   for(j=0;j<DIMENSION1;j++)
	   {
	     ms[i]+=CodeVector[i][j];
	   }
	 }
	 for(i=0;i<(int)(booksize-1);i++)
	 {
	   iindex=i;
	   for(l=i+1;l<booksize;l++)
	   {
	     if(ms[iindex]>ms[l])
		 {
			iindex=l;
		 } //end of for j,get the index  
	   }
	   if(iindex==i)
	   {
	     continue;
	   }
	   ttt=ms[i];
	   ms[i]=ms[iindex];
	   ms[iindex]=ttt;
	   memcpy(tt,CodeVector[i],DIMENSION1*sizeof(float));
	   memcpy(CodeVector[i],CodeVector[iindex],DIMENSION1*sizeof(float));
	   memcpy(CodeVector[iindex],tt,DIMENSION1*sizeof(float));
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)dimension*(double)blocks);
   *MSE=d1/(double)dimension/(double)blocks;
   return 0;
}


////The Design Methods implemetation begins////
short int CRetrieveMethod::DCTVQLBGCodebookDesign(unsigned long int blocks,unsigned short int booksize,unsigned short int dimension,double e,float (*TrainVector)[DIMENSION2],float (*CodeVector)[DIMENSION2],unsigned short int *index,unsigned long int *number,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//dimension: stands for the dimension of DCT coefficient block
//         the vector dimension should be smaller than 64
//e:  stands for the distortion threshold 
//         e should be larger than 0
// TrainVector[MAXSOURCESIZE][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXSOURCESIZE]: each element stands for 
//                       the index for a trainning vector
// number[MAXBOOKSIZE]: each element stands for 
//                     the number of training vectors 
//                     that close to a codeword
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
// return -4: e set error
{
   int i,l;
   unsigned short int j,k;

   double d0,d1,d,min,dd[DIMENSION2],par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   float tt[DIMENSION2];
   double ms[MAXBOOKSIZE],ttt;
   int iindex; 
     
   if(booksize>MAXBOOKSIZE)return -1;
   if(blocks<booksize||blocks>MAXINPUTVECTORS)return -2;
   if(dimension>DIMENSION2||dimension<=0)return -3;
   if(e<=0) return -4;   
   
   //Initial codevector Using random number generator
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector[i],TrainVector[l],DIMENSION2*sizeof(float));
   }
   d0=9.99e+60;   
   *iterations=0;
   ltime1=clock();
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize;j++)
	   number[j]=0;
	 for(i=0;i<(int)blocks;i++)
	 {
	    index[i]=0;
		min=0.0;
        for(k=0;k<dimension;k++)
		{   
          min=min+((double)TrainVector[i][k]-(double)CodeVector[0][k])*((double)TrainVector[i][k]-(double)CodeVector[0][k]);
		}
		for(j=1;j<booksize;j++)
		{
		  d=0.0;
		  for(k=0;k<dimension;k++)
		  {			  
		    d=d+((double)TrainVector[i][k]-(double)CodeVector[j][k])*((double)TrainVector[i][k]-(double)CodeVector[j][k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    index[i]=j;
		  }
		}
	    number[index[i]]=number[index[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize;j++)
	 {
	    if(number[j]!=0)
		{
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<(int)blocks;l++)
		  {
		    if(index[l]==j)
			{
			  for(k=0;k<dimension;k++)
			  {
		        dd[k]=dd[k]+(double)TrainVector[l][k];
			  }
			}
		  }
		  for(k=0;k<dimension;k++)
		  {
		    CodeVector[j][k]=(float)(dd[k]/(double)number[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector[j],TrainVector[l],DIMENSION2*sizeof(float));
		}
	 }
	 for(i=0;i<booksize;i++)
	 {
	   ms[i]=0.0;
	   for(j=0;j<DIMENSION2;j++)
	   {
	     ms[i]+=CodeVector[i][j];
	   }
	 }
	 for(i=0;i<(int)(booksize-1);i++)
	 {
	   iindex=i;
	   for(l=i+1;l<booksize;l++)
	   {
	     if(ms[iindex]>ms[l])
		 {
			iindex=l;
		 } //end of for j,get the index  
	   }
	   if(iindex==i)
	   {
	     continue;
	   }
	   ttt=ms[i];
	   ms[i]=ms[iindex];
	   ms[iindex]=ttt;
	   memcpy(tt,CodeVector[i],DIMENSION2*sizeof(float));
	   memcpy(CodeVector[i],CodeVector[iindex],DIMENSION2*sizeof(float));
	   memcpy(CodeVector[iindex],tt,DIMENSION2*sizeof(float));
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)dimension*(double)blocks);
   *MSE=d1/(double)dimension/(double)blocks;
   return 0;
}


////The Design Methods implemetation begins////
short int CRetrieveMethod::VQLBGCodebookDesign(unsigned long int blocks,unsigned short int booksize,unsigned short int dimension,double e,unsigned char (*TrainVector)[VQDIMENSION],unsigned char (*CodeVector)[VQDIMENSION],unsigned short int *index,unsigned long int *number,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//dimension: stands for the dimension of DCT coefficient block
//         the vector dimension should be smaller than 64
//e:  stands for the distortion threshold 
//         e should be larger than 0
// TrainVector[MAXSOURCESIZE][blockwidth*blockheight]: 
//         stands for the training vectors(two-dimensional array)
// CodeVector[MAXBOOKSIZE][blockwidth*blockheight]: 
//         stands for the codewords(two-dimensional array)
// index[MAXSOURCESIZE]: each element stands for 
//                       the index for a trainning vector
// number[MAXBOOKSIZE]: each element stands for 
//                     the number of training vectors 
//                     that close to a codeword
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
// return -4: e set error
{
   int i,l;
   unsigned short int j,k;

   double d0,d1,d,min,dd[VQDIMENSION],par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   unsigned char tt[VQDIMENSION];
   double ms[MAXBOOKSIZE],ttt;
   int iindex; 
   if(booksize>MAXBOOKSIZE||booksize<16)return -1;
   if(blocks<booksize||blocks>VQMAXINPUTVECTORS)return -2;
   if(dimension>VQDIMENSION||dimension<=0)return -3;
   if(e<=0) return -4;   
   
   //Initial codevector Using random number generator
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector[i],TrainVector[l],VQDIMENSION*sizeof(unsigned char));
   }
   d0=9.99e+60;   
   *iterations=0;
   ltime1=clock();
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize;j++)
	   number[j]=0;
	 for(i=0;i<(int)blocks;i++)
	 {
	    index[i]=0;
		min=0.0;
        for(k=0;k<dimension;k++)
		{   
          min=min+((double)TrainVector[i][k]-(double)CodeVector[0][k])*((double)TrainVector[i][k]-(double)CodeVector[0][k]);
		}
		for(j=1;j<booksize;j++)
		{
		  d=0.0;
		  for(k=0;k<dimension;k++)
		  {			  
		    d=d+((double)TrainVector[i][k]-(double)CodeVector[j][k])*((double)TrainVector[i][k]-(double)CodeVector[j][k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    index[i]=j;
		  }
		}
	    number[index[i]]=number[index[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize;j++)
	 {
	    if(number[j]!=0)
		{
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<(int)blocks;l++)
		  {
		    if(index[l]==j)
			{
			  for(k=0;k<dimension;k++)
			  {
		        dd[k]=dd[k]+(double)TrainVector[l][k];
			  }
			}
		  }
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=dd[k]/(double)number[j];
			if(dd[k]>255)dd[k]=255;
			if(dd[k]<0)dd[k]=0;
			CodeVector[j][k]=(unsigned char)dd[k];
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector[j],TrainVector[l],VQDIMENSION*sizeof(unsigned char));
		}
	 }

	 //codebook sorted by mean of codeword
	 
	 for(i=0;i<booksize;i++)
	 {
	   ms[i]=0.0;
	   for(j=0;j<VQDIMENSION;j++)
	   {
	     ms[i]+=CodeVector[i][j];
	   }
	 }
	 for(i=0;i<(int)(booksize-1);i++)
	 {
	   iindex=i;
	   for(l=i+1;l<booksize;l++)
	   {
	     if(ms[iindex]>ms[l])
		 {
			iindex=l;
		 } //end of for j,get the index  
	   }
	   if(iindex==i)
	   {
	     continue;
	   }
	   ttt=ms[i];
	   ms[i]=ms[iindex];
	   ms[iindex]=ttt;
	   memcpy(tt,CodeVector[i],VQDIMENSION*sizeof(unsigned char));
	   memcpy(CodeVector[i],CodeVector[iindex],VQDIMENSION*sizeof(unsigned char));
	   memcpy(CodeVector[iindex],tt,VQDIMENSION*sizeof(unsigned char));
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)dimension*(double)blocks);
   *MSE=d1/(double)dimension/(double)blocks;
   return 0;
}

short int CRetrieveMethod::TwoStageVQ256GrayImageCodebookDesign(unsigned long int blocks,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,double e,unsigned char (*TrainVector)[VQDIMENSION],short int (*ErrorTrainVector)[VQDIMENSION],unsigned char (*CodeVector1)[VQDIMENSION],short int (*CodeVector2)[VQDIMENSION],unsigned short int *index1,unsigned short int *index2,unsigned long int *number1,unsigned long int *number2,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
{
   unsigned long int i,l;
   unsigned short int j;
   unsigned short int k;
   unsigned short int dimension;
   double d0,d1,d,min,dd[64],par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   dimension=blockwidth*blockheight;
   if(booksize1<4||booksize2<4||booksize1>MAXBOOKSIZE||booksize2>MAXBOOKSIZE)return -1;
   if(blocks<booksize1||blocks<booksize2||blocks>VQMAXINPUTVECTORS)return -2;
   if(dimension>VQDIMENSION||dimension<=0)return -3;
   if(e<=0) return -4;   
   
   //Initial the iteration times and get the start time
   *iterations=0;
   ltime1=clock();
   
   //The first stage
   //Initial codevector Using random number generator
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize1;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector1[i],TrainVector[l],dimension);
   }
   d0=9.99e+60;   
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize1;j++)
	   number1[j]=0;
	 for(i=0;i<blocks;i++)
	 {
	    index1[i]=0;
		min=0.0;
        for(k=0;k<dimension;k++)
		{   
          min=min+((double)TrainVector[i][k]-(double)CodeVector1[0][k])*((double)TrainVector[i][k]-(double)CodeVector1[0][k]);
		}
		for(j=1;j<booksize1;j++)
		{
		  d=0.0;
		  for(k=0;k<dimension;k++)
		  {			  
		    d=d+((double)TrainVector[i][k]-(double)CodeVector1[j][k])*((double)TrainVector[i][k]-(double)CodeVector1[j][k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    index1[i]=j;
		  }
		}
	    number1[index1[i]]=number1[index1[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize1;j++)
	 {
	    if(number1[j]!=0)
		{
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<blocks;l++)
		  {
		    if(index1[l]==j)
			{
			  for(k=0;k<dimension;k++)
			  {
		        dd[k]=dd[k]+(double)TrainVector[l][k];
			  }
			}
		  }
		  for(k=0;k<dimension;k++)
		  {
		    CodeVector1[j][k]=(unsigned char)(dd[k]/(double)number1[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector1[j],TrainVector[l],dimension);
		}
	 }
   }
   
   //The second stage
   for(i=0;i<blocks;i++)
   { 
	 for(k=0;k<dimension;k++)
	 {   
       ErrorTrainVector[i][k]=(short int)TrainVector[i][k]-(short int)CodeVector1[index1[i]][k];
	 }
   }
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize2;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector2[i],ErrorTrainVector[l],2*dimension);
   }
   d0=9.99e+60;   
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize2;j++)
	   number2[j]=0;
	 for(i=0;i<blocks;i++)
	 {
	    index2[i]=0;
		min=0.0;
        for(k=0;k<dimension;k++)
		{   
          min=min+((double)ErrorTrainVector[i][k]-(double)CodeVector2[0][k])*((double)ErrorTrainVector[i][k]-(double)CodeVector2[0][k]);
		}
		for(j=1;j<booksize2;j++)
		{
		  d=0.0;
		  for(k=0;k<dimension;k++)
		  {			  
		    d=d+((double)ErrorTrainVector[i][k]-(double)CodeVector2[j][k])*((double)ErrorTrainVector[i][k]-(double)CodeVector2[j][k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    index2[i]=j;
		  }
		}
	    number2[index2[i]]=number2[index2[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize2;j++)
	 {
	    if(number2[j]!=0)
		{
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<blocks;l++)
		  {
		    if(index2[l]==j)
			{
			  for(k=0;k<dimension;k++)
			  {
		        dd[k]=dd[k]+(double)ErrorTrainVector[l][k];
			  }
			}
		  }
		  for(k=0;k<dimension;k++)
		  {
		    CodeVector2[j][k]=(short int)(dd[k]/(double)number2[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector2[j],ErrorTrainVector[l],2*dimension);
		}
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)dimension*(double)blocks);
   *MSE=d1/(double)dimension/(double)blocks;
   return 0;
}


////The Design Methods implemetation begins////
short int CRetrieveMethod::DCTVQScalarCodebookDesign(unsigned long int blocks,unsigned short int booksize,double e,float *TrainVector,float *CodeVector,unsigned short int *index,unsigned long int *number,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//dimension: stands for the dimension of DCT coefficient block
//         the vector dimension should be smaller than 64
//e:  stands for the distortion threshold 
//         e should be larger than 0
// TrainVector[MAXSOURCESIZE]: 
//         stands for the training scalars
// CodeVector[MAXBOOKSIZE]: 
//         stands for the codewords
// index[MAXSOURCESIZE]: each element stands for 
//                       the index for a trainning vector
// number[MAXBOOKSIZE]: each element stands for 
//                     the number of training vectors 
//                     that close to a codeword
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
// return -4: e set error
{
   int i,l;
   unsigned short int j;

   double d0,d1,d,min,dd,par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   float tt;
   int iindex; 
   if(booksize>MAXBOOKSIZE||booksize<16)return -1;
   if(blocks<booksize||blocks>MAXINPUTVECTORS)return -2;
   if(e<=0) return -4;   
   
   //Initial codevector Using random number generator
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector+i,TrainVector+l,sizeof(float));
   }
   d0=9.99e+60;   
   *iterations=0;
   ltime1=clock();
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize;j++)
	   number[j]=0;
	 for(i=0;i<(int)blocks;i++)
	 {
	    index[i]=0;
		min=((double)TrainVector[i]-(double)CodeVector[0])*((double)TrainVector[i]-(double)CodeVector[0]);
		for(j=1;j<booksize;j++)
		{
		  d=((double)TrainVector[i]-(double)CodeVector[j])*((double)TrainVector[i]-(double)CodeVector[j]);
		  if(d<min)
		  {
		    min=d;
		    index[i]=j;
		  }
		}
	    number[index[i]]=number[index[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize;j++)
	 {
	    if(number[j]!=0)
		{
		  dd=0.0;
		  for(l=0;l<(int)blocks;l++)
		  {
		    if(index[l]==j)
			  dd=dd+(double)TrainVector[l];
		  }
		  CodeVector[j]=(float)(dd/(double)number[j]);
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector+j,TrainVector+l,sizeof(float));
		}
	 }

	 //codebook sorted by mean of codeword
	 
	 for(i=0;i<(int)(booksize-1);i++)
	 {
	   iindex=i;
	   for(l=i+1;l<booksize;l++)
	   {
	     if(CodeVector[iindex]>CodeVector[l])
		 {
			iindex=l;
		 } //end of for j,get the index  
	   }
	   if(iindex==i)
	   {
	     continue;
	   }
	   tt=CodeVector[i];
	   CodeVector[i]=CodeVector[iindex];
	   CodeVector[iindex]=tt;
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)blocks);
   *MSE=d1/(double)blocks;
   return 0;
}

////The Design Methods implemetation begins////
short int CRetrieveMethod::VQScalarCodebookDesign(unsigned long int blocks,unsigned short int booksize,double e,unsigned char *TrainVector,unsigned char *CodeVector,unsigned short int *index,unsigned long int *number,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
//blocks : stands for the number of traning vectors, 
//         it should be smaller than MAXSOURCESZIE
//booksize: stands for the number of codewords
//         it should be smaller than MAXBOOKSZIE
//         and blocks should be larger than booksize
//dimension: stands for the dimension of DCT coefficient block
//         the vector dimension should be smaller than 64
//e:  stands for the distortion threshold 
//         e should be larger than 0
// TrainVector[MAXSOURCESIZE]: 
//         stands for the training scalars
// CodeVector[MAXBOOKSIZE]: 
//         stands for the codewords
// index[MAXSOURCESIZE]: each element stands for 
//                       the index for a trainning vector
// number[MAXBOOKSIZE]: each element stands for 
//                     the number of training vectors 
//                     that close to a codeword
// *MSE:  the pointer to the variable MSE which 
//        stands for the mean squared error
// *PSNR: the pointer to the variable PSNR which 
//        stands for peak signal-noise ratio
// return 0: normal
// return -1: booksize set error
// return -2: blocks set error
// return -3: blockwidth and blockheight set error
// return -4: e set error
{
   int i,l;
   unsigned short int j;

   double d0,d1,d,min,dd,par;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   unsigned char tt;
   int iindex; 
   if(booksize>MAXBOOKSIZE||booksize<16)return -1;
   if(blocks<booksize||blocks>VQMAXINPUTVECTORS)return -2;
   if(e<=0) return -4;   
   
   //Initial codevector Using random number generator
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector+i,TrainVector+l,sizeof(unsigned char));
   }
   d0=9.99e+60;   
   *iterations=0;
   ltime1=clock();
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize;j++)
	   number[j]=0;
	 for(i=0;i<(int)blocks;i++)
	 {
	    index[i]=0;
		min=((double)TrainVector[i]-(double)CodeVector[0])*((double)TrainVector[i]-(double)CodeVector[0]);
		for(j=1;j<booksize;j++)
		{
		  d=((double)TrainVector[i]-(double)CodeVector[j])*((double)TrainVector[i]-(double)CodeVector[j]);
		  if(d<min)
		  {
		    min=d;
		    index[i]=j;
		  }
		}
	    number[index[i]]=number[index[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize;j++)
	 {
	    if(number[j]!=0)
		{
		  dd=0.0;
		  for(l=0;l<(int)blocks;l++)
		  {
		    if(index[l]==j)
			  dd=dd+(double)TrainVector[l];
		  }
		  CodeVector[j]=(unsigned char)(dd/(double)number[j]);
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector+j,TrainVector+l,sizeof(unsigned char));
		}
	 }

	 //codebook sorted by mean of codeword
	 
	 for(i=0;i<(int)(booksize-1);i++)
	 {
	   iindex=i;
	   for(l=i+1;l<booksize;l++)
	   {
	     if(CodeVector[iindex]>CodeVector[l])
		 {
			iindex=l;
		 } //end of for j,get the index  
	   }
	   if(iindex==i)
	   {
	     continue;
	   }
	   tt=CodeVector[i];
	   CodeVector[i]=CodeVector[iindex];
	   CodeVector[iindex]=tt;
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)blocks);
   *MSE=d1/(double)blocks;
   return 0;
}

////The Encode Methods and Decode implemetation begins////
//The function for twostage VQ search encode method
short int CRetrieveMethod::TwoStageVQ256GrayImageEncode(unsigned long int blocks,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,unsigned char (*SourceVector)[VQDIMENSION],short int (*ErrorSourceVector)[VQDIMENSION],unsigned char (*CodeVector1)[VQDIMENSION],short int (*CodeVector2)[VQDIMENSION],unsigned short int *index1,unsigned short int *index2)
{
   unsigned long int i;
   unsigned short int k,dimension;
   unsigned short int j;
   double d1,d,min;
   
   dimension=blockwidth*blockheight;
   if(booksize1<4||booksize2<4||booksize1>MAXBOOKSIZE||booksize2>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
   if(dimension>VQDIMENSION||dimension<=0)return -3;
   d1=0.0;
   //First Stage
   for(i=0;i<blocks;i++)
   {
     index1[i]=0;
  	 min=0.0;
     for(k=0;k<dimension;k++)
	 {   
       min=min+((double)SourceVector[i][k]-(double)CodeVector1[0][k])*((double)SourceVector[i][k]-(double)CodeVector1[0][k]);
	 }
	 for(j=1;j<booksize1;j++)
	 {
	   d=0.0;
       for(k=0;k<dimension;k++)
	   {  
         d=d+((double)SourceVector[i][k]-(double)CodeVector1[j][k])*((double)SourceVector[i][k]-(double)CodeVector1[j][k]);
	   }
	   if(d<min)
	   {
	     min=d;
	     index1[i]=(unsigned char)j;
	   }
	 }
	 d1=d1+min;
   }
//Second Stage
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     for(k=0;k<dimension;k++)
	 {   
       ErrorSourceVector[i][k]=SourceVector[i][k]-CodeVector1[index1[i]][k];
	 }
     index2[i]=0;
  	 min=0.0;
     for(k=0;k<dimension;k++)
	 {   
       min=min+((double)ErrorSourceVector[i][k]-(double)CodeVector2[0][k])*((double)ErrorSourceVector[i][k]-(double)CodeVector2[0][k]);
	 }
	 for(j=1;j<booksize2;j++)
	 {
	   d=0.0;
       for(k=0;k<dimension;k++)
	   {  
         d=d+((double)ErrorSourceVector[i][k]-(double)CodeVector2[j][k])*((double)ErrorSourceVector[i][k]-(double)CodeVector2[j][k]);
	   }
	   if(d<min)
	   {
	     min=d;
	     index2[i]=(unsigned char)j;
	   }
	 }
	 d1=d1+min;
   }

   return 0;
}
//The function for decode
short int CRetrieveMethod::TwoStageVQ256GrayImageDecode(unsigned long int blocks,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,unsigned short int width,unsigned short int *index1,unsigned short int *index2,unsigned char (*CodeVector1)[VQDIMENSION],short int (*CodeVector2)[VQDIMENSION],unsigned char *pixel,int component)
{
   unsigned long int i,j,k,l;
   unsigned short int dimension,height;
   unsigned short int la,lb,ba,bb;
   short int a;

   dimension=blockwidth*blockheight;
   if(booksize1<4||booksize1>MAXBOOKSIZE||booksize2<4||booksize2>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
   if(dimension>VQDIMENSION)return -3;

   ba=blockwidth;
   bb=blockheight;
   height=(unsigned short int)(blocks*(unsigned long int)dimension/(unsigned long)width);
   la=width/ba;
   lb=height/bb;
   for(l=0;l<lb;l++)
   {
	 for(k=0;k<la;k++)
	 {
	   for(j=0;j<bb;j++)
	   {
	      for(i=0;i<ba;i++)
		  {
	        a=CodeVector1[index1[k+l*la]][i+j*ba]+CodeVector2[index2[k+l*la]][i+j*ba];
			if(component==0)
			{
		     if(a<16)a=16;
		     if(a>240)a=240;
			}
		    else if(component==1)
			{
		     if(a<16)a=16;
		     if(a>240)a=240;
			}
		    else if(component==2)
			{
		     if(a<16)a=16;
		     if(a>235)a=235;
			}
		    else
			{
		     if(a<0)a=0;
		     if(a>255)a=255;
			}
			pixel[i+k*ba+(j+l*bb)*width]=(unsigned char)a;

		  }
	   }
	 }
   }
   return 0;
}


short int CRetrieveMethod::MeanRemovedVQ256GrayImageCodebookDesign(unsigned long int blocks,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,double e,unsigned char (*TrainVector)[VQDIMENSION],unsigned char *Means,short int (*ErrorTrainVector)[VQDIMENSION],unsigned char (*CodeVector1)[VQDIMENSION],short int (*CodeVector2)[VQDIMENSION],unsigned short int *index1,unsigned short int *index2,unsigned long int *number1,unsigned long int *number2,double *MSE,double *PSNR,double *Time,unsigned short int *iterations)
{
   unsigned long int i,l;
   unsigned short int j;
   unsigned short int k;
   double d0,d1,d,min,dd[64],par;
   unsigned short int dimension;
   //Define starttime and finishtime
   clock_t ltime1,ltime2;      
   //compute the dimension
   dimension=blockwidth*blockheight;
   
   //judge the booksizes and blocks and dimensions and error threshold
   if(booksize1<4||booksize2<4||booksize1>MAXBOOKSIZE||booksize2>MAXBOOKSIZE)return -1;
   if(blocks<booksize1||blocks<booksize2||blocks>VQMAXINPUTVECTORS)return -2;
   if(dimension>VQDIMENSION||dimension<=0)return -3;
   if(e<=0) return -4;   
   
   //Initial the iteration times and get the start time
   *iterations=0;
   ltime1=clock();
   
   //The mean codebook generation//////////////////
   //The randomize parameter
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   
   //compute the means
   for(i=0;i<blocks;i++)
   {
     d0=0.0;
	 for(j=0;j<dimension;j++)
	   d0=d0+TrainVector[i][j];
	 d0=d0/(double)dimension;
	 if(d0>255)d0=255;
	 if(d0<0)d0=0;
	 Means[i]=(unsigned char)d0;
   }
   
   //Initial mean codevector Using random number generator
   for(i=0;i<booksize1;i++)
   {
     l=(int)((double)rand()*par);
	 for(j=0;j<dimension;j++)
 	   CodeVector1[i][j]=Means[l];
   }

   d0=9.99e+60;   
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize1;j++)
	   number1[j]=0;
	 for(i=0;i<blocks;i++)
	 {
	    index1[i]=0;
		min=fabs((double)Means[i]-(double)CodeVector1[0][0]);
		for(j=1;j<booksize1;j++)
		{
		  d=fabs((double)Means[i]-(double)CodeVector1[j][0]);
		  if(d<min)
		  {
		    min=d;
		    index1[i]=j;
		  }
		}
		number1[index1[i]]=number1[index1[i]]+1;
	    d1=d1+min;
	 }
     if((d0-d1)/d1<=e)break;
     (*iterations)++;
     d0=d1;
     for(j=0;j<booksize1;j++)
	 { 
       if(number1[j]!=0)
	   {
	     for(k=0;k<dimension;k++)
		 {
	       dd[k]=0.0;
		 }
	     for(l=0;l<blocks;l++)
		 { 
	       if(index1[l]==j)
		   {
		     for(k=0;k<dimension;k++)
			 { 
		       dd[k]=dd[k]+(double)Means[l];
			 }
		   }
		 }
	     for(k=0;k<dimension;k++)
		 { 
	       CodeVector1[j][k]=(unsigned char)(dd[k]/(double)number1[j]);
		 }
	   }
	   else
	   {
	     l=(int)((double)rand()*par);
         for(k=0;k<dimension;k++)
 	       CodeVector1[j][k]=Means[l];
	   }
	 }
   }
   
   //The residual codebook generation//////////////////
   for(i=0;i<blocks;i++)
   { 
	 for(k=0;k<dimension;k++)
	 {   
       ErrorTrainVector[i][k]=(short int)TrainVector[i][k]-(short int)CodeVector1[index1[i]][k];
	 }
   }
   par=(double)(blocks-1)/(double)0x7fff;
   srand((unsigned)time(NULL));
   for(i=0;i<booksize2;i++)
   {
     l=(int)((double)rand()*par);
 	 memcpy(CodeVector2[i],ErrorTrainVector[l],2*dimension);
   }
   d0=9.99e+60;   
   for(;;)
   {  
     d1=0.0;
 	 for(j=0;j<booksize2;j++)
	   number2[j]=0;
	 for(i=0;i<blocks;i++)
	 {
	    index2[i]=0;
		min=0.0;
        for(k=0;k<dimension;k++)
		{   
          min=min+((double)ErrorTrainVector[i][k]-(double)CodeVector2[0][k])*((double)ErrorTrainVector[i][k]-(double)CodeVector2[0][k]);
		}
		for(j=1;j<booksize2;j++)
		{
		  d=0.0;
		  for(k=0;k<dimension;k++)
		  {			  
		    d=d+((double)ErrorTrainVector[i][k]-(double)CodeVector2[j][k])*((double)ErrorTrainVector[i][k]-(double)CodeVector2[j][k]);
		    if(d>=min)break;
		  }
		  if(d<min)
		  {
		    min=d;
		    index2[i]=j;
		  }
		}
	    number2[index2[i]]=number2[index2[i]]+1;
		d1=d1+min;
	 }
	 if((d0-d1)/d1<=e)break;
	 (*iterations)++;
	 d0=d1;
	 for(j=0;j<booksize2;j++)
	 {
	    if(number2[j]!=0)
		{
		  for(k=0;k<dimension;k++)
		  {
		    dd[k]=0.0;
		  }
		  for(l=0;l<blocks;l++)
		  {
		    if(index2[l]==j)
			{
			  for(k=0;k<dimension;k++)
			  {
		        dd[k]=dd[k]+(double)ErrorTrainVector[l][k];
			  }
			}
		  }
		  for(k=0;k<dimension;k++)
		  {
		    CodeVector2[j][k]=(short int)(dd[k]/(double)number2[j]);
		  }
		}
		else
		{
		  l=(int)((double)rand()*par);
          memcpy(CodeVector2[j],ErrorTrainVector[l],2*dimension);
		}
	 }
   }
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     for(j=0;j<dimension;j++)
	 {
	   d1=d1+((double)TrainVector[i][j]-CodeVector1[index1[i]][j]-CodeVector2[index2[i]][j])*((double)TrainVector[i][j]-CodeVector1[index1[i]][j]-CodeVector2[index2[i]][j]);
	 }
   }
   ltime2=clock();
   *Time=double(ltime2-ltime1)/CLOCKS_PER_SEC;
   *PSNR=10*log10(255.0*255.0/d1*(double)dimension*(double)blocks);
   *MSE=d1/(double)dimension/(double)blocks;
   return 0;
}
////The Design Methods implemetation ends////

short int CRetrieveMethod::MeanRemovedVQ256GrayImageEncode(unsigned long int blocks,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,unsigned char (*SourceVector)[VQDIMENSION],unsigned char *Means,short int (*ErrorSourceVector)[VQDIMENSION],unsigned char (*CodeVector1)[VQDIMENSION],short int (*CodeVector2)[VQDIMENSION],unsigned short int*index1,unsigned short int *index2)
{
   unsigned long int i;
   unsigned short int k,dimension;
   unsigned short int j;
   double d1,d,min;

   dimension=blockwidth*blockheight;
   if(booksize1<4||booksize2<4||booksize1>MAXBOOKSIZE||booksize2>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
   if(dimension>VQDIMENSION||dimension<=0)return -3;
   for(i=0;i<blocks;i++)
   {
     d1=0.0;
	 for(j=0;j<dimension;j++)
	 d1=d1+SourceVector[i][j];
	 d1=d1/(double)dimension;
	 if(d1>255)d1=255;
	 if(d1<0)d1=0;
	 Means[i]=(unsigned char)d1;
   }
   
 
   d1=0.0;
   //First Stage
   for(i=0;i<blocks;i++)
   {
     index1[i]=0;
  	 min=fabs((double)Means[i]-(double)CodeVector1[0][0]);
	 for(j=1;j<booksize1;j++)
	 {
	   d=fabs((double)Means[i]-(double)CodeVector1[j][0]);
	   if(d<min)
	   {
	     min=d;
	     index1[i]=(unsigned char)j;
	   }
	 }
	 d1=d1+min;
   }
//Second Stage
   d1=0.0;
   for(i=0;i<blocks;i++)
   {
     for(k=0;k<dimension;k++)
	 {   
       ErrorSourceVector[i][k]=SourceVector[i][k]-CodeVector1[index1[i]][k];
	 }
     index2[i]=0;
  	 min=0.0;
     for(k=0;k<dimension;k++)
	 {   
       min=min+((double)ErrorSourceVector[i][k]-(double)CodeVector2[0][k])*((double)ErrorSourceVector[i][k]-(double)CodeVector2[0][k]);
	 }
	 for(j=1;j<booksize2;j++)
	 {
	   d=0.0;
       for(k=0;k<dimension;k++)
	   {  
         d=d+((double)ErrorSourceVector[i][k]-(double)CodeVector2[j][k])*((double)ErrorSourceVector[i][k]-(double)CodeVector2[j][k]);
	   }
	   if(d<min)
	   {
	     min=d;
	     index2[i]=(unsigned char)j;
	   }
	 }
	 d1=d1+min;
   }
  
   return 0;
}
short int CRetrieveMethod::MeanRemovedVQ256GrayImageDecode(unsigned long int blocks,unsigned short int booksize1,unsigned short int booksize2,unsigned short int blockwidth,unsigned short int blockheight,unsigned short int width,unsigned short int *index1,unsigned short int *index2,unsigned char (*CodeVector1)[VQDIMENSION],short int (*CodeVector2)[VQDIMENSION],unsigned char *pixel,int component)
{
   unsigned long int i,j,k,l;
   unsigned short int dimension,height;
   unsigned short int la,lb,ba,bb;
   short int a;

   dimension=blockwidth*blockheight;
   if(booksize1<4||booksize1>MAXBOOKSIZE||booksize2<4||booksize2>MAXBOOKSIZE)return -1;
   if(blocks>VQMAXENCODEVECTORS)return -2;
   if(dimension>VQDIMENSION)return -3;

   ba=blockwidth;
   bb=blockheight;
   height=(unsigned short int)(blocks*(unsigned long int)dimension/(unsigned long)width);
   la=width/ba;
   lb=height/bb;
   for(l=0;l<lb;l++)
   {
	 for(k=0;k<la;k++)
	 {
	   for(j=0;j<bb;j++)
	   {
	      for(i=0;i<ba;i++)
		  {
	        a=CodeVector1[index1[k+l*la]][i+j*ba]+CodeVector2[index2[k+l*la]][i+j*ba];
			if(component==0)
			{
		     if(a<16)a=16;
		     if(a>240)a=240;
			}
		    else if(component==1)
			{
		     if(a<16)a=16;
		     if(a>240)a=240;
			}
		    else if(component==2)
			{
		     if(a<16)a=16;
		     if(a>235)a=235;
			}
		    else
			{
		     if(a<0)a=0;
		     if(a>255)a=255;
			}
			pixel[i+k*ba+(j+l*bb)*width]=(unsigned char)a;
		  }
	   }
	 }
   }
   return 0;
}

double CRetrieveMethod::ComputePSNR(unsigned char *Original,unsigned char *Result,long int width,long int height)
{
	int i,j;
	double d,d1,MSE,PSNR;
	d=0;
	long int linebytes;
	linebytes=(width+3)/4*4;
    for(i=0;i<height;i++)
    {
     for(j=0;j<width;j++)
     {
       d1=(double)Original[i*linebytes+j]-(double)Result[i*linebytes+j];
	   d=d+d1*d1;
	 } 
	}
   MSE=d/(double)width/(double)height;
   if(MSE!=0.0)
     PSNR=10*log10(255.0*255.0/d*(double)width*(double)height);
   else
     PSNR=-1.0;
   return PSNR;
}

