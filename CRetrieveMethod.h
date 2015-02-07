// CRetrieveMethod.h: interface for the CCRetrieveMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRETRIEVEMETHOD_H__7D3135B1_07BA_4BE6_BE2B_84FA11D0E040__INCLUDED_)
#define AFX_CRETRIEVEMETHOD_H__7D3135B1_07BA_4BE6_BE2B_84FA11D0E040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <list>
//using namespace std ;
//typedef list<int> LISTDWORD;
//#include <iostream>


#define MAX_FEATUREVECTOR_DIMENSION 500
#define MAX_IMAGE_NUMBER 500000
#define MAX_CODEBOOK_SIZE 1024
#define MAX_HISTOGRAM_BIN 128

#define PI 3.14159265358979324

//For color space transform
#define WHITE_X 0.950456
#define WHITE_Y 1.0
#define WHITE_Z 1.088754

//For Haar invariant feature
static WORD Angles[23]={2,3,4,5,6,8,9,10,12,15,18,20,24,30,36,40,45,60,72,90,120,180,360};
//for histogram
static WORD Bins[4]={128,64,32,16};
//for texture feature
static WORD TextureDim[15]={3,5,10,14,1,3,3,10,21,21,24,20,20,10,10};
//for shape feature
static WORD ShapeDim[11]={20,36,72,3,4,7,10,40,43,76,82};
//for other feature
static WORD OtherDim[4]={10,15,20,25};
//for image reading
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define SAVEWIDTH(mywidth)  (mywidth+3)/4*4

//sizeof(FEATUREFILEINFO)=512;
typedef struct tagFeatureFileInfoStruct
{
     //The struct size
	 WORD m_wStructSize;//=512 bytes
	 //The file size
	 DWORD m_dwFileSize;
	 //The retrieval path
	 char m_sPath[MAX_PATH];
	 //The last 8 letters of this file name
	 char m_sThisFileNameLast8[8];
	 BOOL m_bEverInterrupted; //If ever interrupted in feature computing
	 //The offset of first image's feature
	 WORD m_wOffBytes;//=600
	 //The number of image files
	 DWORD m_dwFileNumber;
	 //If need nextfile to save the feature database
	 BOOL m_bNextFile;
	 //The nextfile name
	 char m_sNextFileNameLast8[8];
	 //The number of feature types
	 BYTE m_bFeatureTypes;
	 //The total dimensions of features
	 WORD m_wTotalDimensions;
	 
	 //With colors?
	 BOOL m_bWithColor;
	 //With RT Invariant?
	 BOOL m_bWithRTInvariant;
     //With Texture?
	 BOOL m_bWithTexture;
	 //With Shape?
	 BOOL m_bWithShape;
	 //With Others?
	 BOOL m_bWithOthers;
	 
	 //++++++++++For colors++++++++
	 BYTE m_bColorSpace_CF;//The color space of CF
	 BYTE m_bDescription_CF;//The description style of CF
     BYTE m_bBins_CF;//The bin selection of CF
	 WORD m_wDimension_CF;//The dimension of CF
	 
	 //+++++++++++For Invarint++++++
	 BYTE m_bColorSpace_IF;//The color space of IF
	 BYTE m_bPoints_IF; //The Points selection style for RT-Inva.
     BYTE m_bAngles_IF; //The Angles selection style for RT-Inva.
	 BYTE m_bBins_IF;//The bin selection 2 of IF
     BYTE m_bDescription_IF;//The description style of RT-Inva.
	 WORD m_wDimension_IF;//The dimension of CF
	 
	 //++++++++++For Texture++++++++
	 BYTE m_bColorSpace_TF;//The Color Space
     BYTE m_bDescription_TF;//The description style
	 WORD m_wDimension_TF;//The dimension of TF
     BYTE m_bCoocurrence_TF;//The par of Coocurrence
	 
	 //++++++++++For Shape++++++++
	 BYTE m_bColorSpace_SF;//The Color Space
     BYTE m_bDescription_SF;//The description style
	 WORD m_wDimension_SF;//The dimension of TF
     
	 //++++++++++For Other++++++++
     BOOL m_bWithFeature1_OF;//With other feature 1 of OF
	 BOOL m_bWithFeature2_OF;//With other feature 2 of OF
	 BOOL m_bWithFeature3_OF;//With other feature 3 of OF
	 BOOL m_bWithFeature4_OF;//With other feature 4 of OF
	 char m_sFeature1_OF[32];//Name of Feature 1
	 char m_sFeature2_OF[32];//Name of Feature 2
	 char m_sFeature3_OF[32];//Name of Feature 3
	 char m_sFeature4_OF[32];//Name of Feature 4
	 WORD m_wDimension_OF;//The dimension of OF
     WORD m_wWeights[8];
}FEATUREFILEINFO,*PFEATUREFILEINFO;

typedef struct tagCodebookStruct
{
     //The struct size
	 WORD m_wStructSize;//=68 bytes
	 //The file size
	 DWORD m_dwFileSize;
	 //The last 8 letters of this file name
	 char m_sThisFileNameLast8[8];
	 //The offset of first codeword
	 WORD m_wOffBytes;//=128
	 //The number of Training Vectors
	 DWORD m_dwTrainingVectorNumber;
	 //The number of codewords
	 WORD m_wCodewordNumber;
	 //Normalized?
	 BOOL m_bNormalization;
	 //The number of feature types in each vector
	 BYTE m_bFeatureTypes;
	 //The total dimension of each vector
	 WORD m_wTotalDimensions;
	 //With colors?
	 BOOL m_bWithColor;
	 BOOL m_bWithRTInvariant;//With RT Invariant?
	 //With Texture?
	 BOOL m_bWithTexture;
	 //With Shape?
	 BOOL m_bWithShape;
	 //With Others?
	 BOOL m_bWithOthers;
	 
	 WORD m_wDimension_CF;//The dimension of CF
	 WORD m_wDimension_IF;//The dimension of CF
	 WORD m_wDimension_TF;//The dimension of TF
	 WORD m_wDimension_SF;//The dimension of TF
	 WORD m_wDimension_OF;//The dimension of OF
}CODEBOOKFILEHEADER,*PCODEBOOKFILEHEADER;

typedef struct tagIndexStruct
{
     //The struct size
	 WORD m_wStructSize;//=36 bytes
	 //The file size
	 DWORD m_dwFileSize;
	 //The last 8 letters of this file name
	 char m_sThisFileNameLast8[8];
     //The codebook file name
	 char m_sCodebookFileNameLast8[8];
	 //The offset of first index
	 WORD m_wOffBytes;//=64
	 //The number of Indices
	 DWORD m_dwIndexNumber;
	 //The number of Codewords
	 WORD m_wCodewordNumber;
	 //Bytes Per index
	 WORD m_wBytesPerIndex;
}INDEXFILEHEADER,*PINDEXFILEHEADER;

//The structure for each dimension's mean and variance
//max size 500-D
typedef struct tagComponentStruct
{
   double m_dMean;
   double m_dVariance;
}COMPONENTINFO,FAR *LPCOMPONENTINFO,*PCOMPONENTINFO;

//size of FEATUREVECTOR 320
//Max Featurevectors' size(500-D)    =(320+500*8*2=8320)*500000=4,160,000,000
//Max Feature File size=   4,160,000,000+600+2*8*500=4,160,008,600<0xFFFFFFFF=4,294,967,295
typedef struct tagFeatureStruct
{
     char m_sOriginalFileName[MAX_PATH];//Original File name
 	 BYTE m_bType;//For bmp: 0; For Jpg: 1
     BYTE m_bBitCount;//Color bit
	 LONG m_lImageWidth;//Image width
	 LONG m_lImageHeight;//Image Height
 	 WORD m_wDimensions;//The feature vector dimension
	 double m_dOAverage; //Original vector average
	 double m_dOVariance;//Original vector Variance
	 double m_dNAverage; //Normalized vector average
	 double m_dNVariance;//Normalized vector Variance
	 double *m_dOriginalFeature; //Original feature vectors
	 double *m_dNormalizedFeature; //Normalized feature vectors
}FEATUREVECTOR,FAR *LPFEATUREVECTOR,*PFEATUREVECTOR;

typedef struct tagRetrievedResultStruct
{
   DWORD m_dwImageIndex;
   float m_fDistance;
}RETRIEVEDRESULT,FAR *LPRETRIEVEDRESULT,*PRETRIEVEDRESULT;



class CRetrieveMethod  
{
   public:

   //++++++obtain image data from bmp-type file+++++++++++
   //Get the one-dimenaional array of image's RGB Data
   //(24 bits) or Gray-level Data(8 bits) 
   // from the whole image file in BMP-type
   void get_data_from_24or8bits_bmp_file(BYTE *bmpimagefile,BYTE *imagedata,WORD bits,LONG width,LONG height);
  
//++++++++++++Image color space mapping functions++++++++++
   //(for 8bits image, view r=g=b=gray)
   void g2rgb(BYTE *gray_image_byte,BYTE *rgb_image_byte,LONG width,LONG height);
   //For whole 24bits image from rgb to hsv 
   void rgb2hsv(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to hcv 
   void rgb2hcv(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to Lab 
   void rgb2Lab(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to YCbCr 
   void rgb2YCbCr(BYTE *image_byte,BYTE *image_outbyte,LONG width,LONG height);
   void rgb2YCbCr(BYTE *image_byte,double *image_outbyte,LONG width,LONG height);
   //For whole image from rgb to YIQ 
   void rgb2YIQ(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to I1I2I3 
   void rgb2I1I2I3(BYTE *image_byte,double *image_double,LONG width,LONG height);   
   //For whole 24bits image from rgb to I1'I2'I3'
   void rgb2I1_I2_I3(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to L1 L2 L3
   void rgb2L1L2L3(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to CIE XYZ
   void rgb2XYZ(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to CIE YUV
   void rgb2YUV(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to CIE xyY
   void rgb2xyY(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to CIE U'V'W'
   void rgb2UVW(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to RGBY
   void rgb2RGBY(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to YES
   void rgb2YES(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to hls
   void rgb2hls(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to hsi
   void rgb2hsi(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to hsi
   void rgb2hsb(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //For whole 24bits image from rgb to Luv
   void rgb2Luv(BYTE *image_byte,double *image_double,LONG width,LONG height);
   //the Color space transform main function
   void ColorSpaceTransfer(BYTE *rgb_or_gimage,BYTE *rgb_image_byte,WORD bits,BYTE colorspace,double *image_double,LONG width,LONG height,double *max,double *min);
  
//+++++++++++++++++++++++++++++++The Color Features++++++++++++++++++++++++++++++++++++
   //Calculate the histogram for different kind of image data
   //(only for gray-level image or one component of the RGB/HSV/Lab... image)
   int calculate_histogram(BYTE *image,DWORD *histogram,WORD bits,LONG width,LONG height,int chnum,int whichch,WORD bins,bool smooth);
   int calculate_histogram(WORD *image,DWORD *histogram,WORD bits,LONG width,LONG height,int chnum,int whichch,DWORD bins,bool smooth);
   //here max=1,min=0
   int calculate_histogram(double *image,DWORD *histogram,LONG width,LONG height,int chnum,int whichch,WORD bins,bool smooth);
   //with max min inpit
   int calculate_histogram(double *image,DWORD *histogram,LONG width,LONG height,int chnum,int whichch,WORD bins,bool smooth,double *max,double *min,bool automaxmin);
   //The main function to compute the color histogram from rgb-style or gray-level image
   int compute_color_histogram_feature_vector(BYTE *rgb_or_gimage,double *hist_feature,bool smooth,BYTE description,BYTE colorspace,WORD bins,WORD bits,LONG width,LONG height);
//++++++++++++++++++++++++++++++The Color Features End+++++++++++++++++++++++++++++++++++++

  
//++++++++++++++++++++++++++++++++Invariant Features+++++++++++++++++++++++++++++++++++
   void get_bilinear_interpolated_function_value(double *inputimage,double *returnvalue,BYTE whichch,WORD angle,LONG shiftx,LONG shifty,LONG width,LONG height);
   int get_medium_image_for_haar_invariant_feature(double *inputimage,double *outputimage,DWORD points,WORD angles,BYTE whichch,LONG width,LONG height,double min,double max);
   //The main function to compute the haar-integral feature from rgb-style or gray-level image
   //f(M)=sqrt(M(4,0)M(0,8))
   int compute_haar_integral_invariant_feature_vector(BYTE *rgb_or_gimage,double *haar_integral_feature,DWORD points,WORD angles,bool smooth,BYTE description,BYTE colorspace,WORD bins,WORD bits,LONG width,LONG height);
//++++++++++++++++++++++++++++++Invariant Features End+++++++++++++++++++++++++++++++++++++
   

//+++++++++++++++++++++++++++++++++The Texture Features+++++++++++++++++++++++++++++++++++++
   //compute the histogram moment from double-style 24bits image
   int compute_64bin_histogram_moments_feature_vector(double *image_double,double *histmoment_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_coocurency_matrix_based_feature_vector(double *image_double,double *coocmatrix_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_CCD_texture_feature_vector(double *image_double,double *ccd_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_texture_energy_feature_vector(double *image_double,double *energy_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_RDC_texture_feature_vector(double *image_double,double *rdc_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_DFT_spectrum_texture_feature_vector(double *image_double,double *dft_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_DWT_spectrum_texture_feature_vector(double *image_double,double *dwt_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_MPEG_spectrum_texture_feature_vector(double *image_double,double *mpeg_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   int compute_structural_texture_feature_vector(double *image_double,double *structural_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   //The main function to compute the texture vector
   int compute_texture_feature_vector(BYTE *rgb_or_gimage,double *texture_feature,BYTE description,BYTE colorspace,BYTE Coocurrence,WORD bits,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
//+++++++++++++++++++++++++++++++++The Texture Features End+++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++The Shape Features+++++++++++++++++++++++++++++++++++++
   //compute 1D DFT shape from byte-styled or double-valued 24bits image
   int compute_1D_DFT_shape_feature_vector(double *image_double,double *dft_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   //compute edge information from byte-styled or double-valued 24bits image
   int compute_edge_directional_histogram_feature_vector(double *image_double,double *edh_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   //Compute F E S information from byte-styled or double-valued 24bits image
   int compute_FES_shape_feature_vector(double *image_double,double *fes_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);   
   //++compute the hu moment from byte-styled or double-valued 24bits image
   int compute_hu_moment_feature_vector(double *image_double,double *hu_moments_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
   //++compute the hu monents from a double image
   void compute_hu_moments(double *image_byte,double *moments,int whichch,LONG width,LONG height,int dimension);
   //Compute distortion based shape
   int compute_distortion_shape_feature_vector(double *image_double,double *distortion_feature,BYTE colorspace,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);   
   //The main function of shape feature vector computation
   int compute_shape_feature_vector(BYTE *rgb_or_gimage,double *shape_feature,BYTE description,BYTE colorspace,WORD bits,LONG width,LONG height,WORD thisdimension,WORD *dimensionused);
//+++++++++++++++++++++++++++++++++The Shape Features Ends+++++++++++++++++++++++++++++++++++++
   
//+++++++++++++++++++++++++++++++++The Other Features+++++++++++++++++++++++++++++++++++++
   int compute_other_feature_vector1(BYTE *rgb_or_gimage,double *other_feature1,WORD bits,LONG width,LONG height,WORD *dimensionused);
   int compute_other_feature_vector2(BYTE *rgb_or_gimage,double *other_feature2,WORD bits,LONG width,LONG height,WORD *dimensionused);
   int compute_other_feature_vector3(BYTE *rgb_or_gimage,double *other_feature3,WORD bits,LONG width,LONG height,WORD *dimensionused);
   int compute_other_feature_vector4(BYTE *rgb_or_gimage,double *other_feature4,WORD bits,LONG width,LONG height,WORD *dimensionused);
//+++++++++++++++++++++++++++++++++The Other Features Ends+++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++Feature Normalization, weighting and classification++++++++++++++++++++++
   /////FeatureVector: Feature Vectors to be normalized, VectorNumber: The number of Vectors, VectorDimension: The dimension of each vector
   ///lpComponentInfo: Output the Component info including means and variances of each dimension
   int FeatureDatabaseNormalizationandWeighting(LPFEATUREVECTOR lpFeatureVector,DWORD VectorNumber,WORD VectorDimension,WORD *Dimensions,WORD *Weights,LPCOMPONENTINFO lpComponentInfo);
   //QueryImageFeatureVector, FeatureDimension
   ///lpComponentInfo: Input the Component info including means and variances of each dimension
   int QueryFeatureNormalization(PFEATUREVECTOR QueryImageFeatureVector,WORD VectorDimension,WORD *Dimensions,WORD *Weights,LPCOMPONENTINFO lpComponentInfo);
   //LBG algorithm for double data clustering
   int LBGCodebookDesign(DWORD VectorNumber,WORD BookSize,WORD VectorDimension,double e,double *TrainVector,double *CodeVector,WORD *Index,DWORD *NumberinCluster,double *MSE,double *PSNR,double *Time,WORD *Iterations);

//+++++++++++++++++++++++++++Feature Normalization, weighting and classification Ends++++++++++++++++++++++

   
//++++++++++++++++++++++++++++++++Retrieval method++++++++++++++++++++++++++
   //Full search Retrieval
   int FullSearchRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime);
   ///Sorting lpFeatureVector in ascending order based on normalized mean values
   void SortingByAverage(LPFEATUREVECTOR lpFeatureVector,DWORD VectorNumber);

   int EKNNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime,BOOL iteratived,DWORD *searchindexlist);
   DWORD GetInitialLeastMeanDistanceIndex( FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector, DWORD RemainedMeanListLength,BOOL iteratived,DWORD *searchindexlist);
   int ENNSRetrieveMethod(FEATUREVECTOR QueryImageFeatureVector,LPFEATUREVECTOR lpFeatureVector,WORD VectorDimension,DWORD TotalVectorNumber,long int *RetrievedNumber,DWORD VectorNumberTobeSearched,LPRETRIEVEDRESULT RetrievedResult,double *RetrieveTime);
   
   //矢量检索，方法2:快速检索最相似的一幅图像
   ///pFeatureVector图像库矢量结构体指针，iCurrentFeature:检索矢量的数量，
   //iRetrieveImageNumber图像库图像数目， QueryImageFeatureVector :关键图像的结构
   //pOutFeatureVector：输出结构体的头指针，maxOutNumber＝1输出图像的最多数目,*pOutImageNumber:输出图像的数目的地址
   //pDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
   bool RetrieveKeyVqMethod_2AccelerateBestOne(LPFEATUREVECTOR lpFeatureVector,int iCurrentFeature, long int iRetrieveImageNumber,FEATUREVECTOR QueryImageFeatureVector, PFEATUREVECTOR pOutFeatureVector, unsigned char maxOutNumber,unsigned char *pOutImageNumber, double *pOutDistance, CString *RetrieveTime);
   //矢量检索，方法3：对矢量的某一维分量进行检索：vector维分量
   ///直接的检索矢量，对图像的矢量进行检索
   ///pFeatureVector图像库矢量结构体指针，iCurrentFeature:检索矢量的数量，
   //iRetrieveImageNumber图像库图像数目， QueryImageFeatureVector :关键图像的结构
   //pOutFeatureVector：输出结构体的头指针，maxOutNumber输出图像的最多数目,*pOutImageNumber:输出图像的数目的地址
   //pDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
   ///int vector:分量值0～iCurrentFeature-1
   bool RetrieveKeyVqMethod_3Single(LPFEATUREVECTOR lpFeatureVector,int iCurrentFeature, long int iRetrieveImageNumber,FEATUREVECTOR QueryImageFeatureVector, PFEATUREVECTOR pOutFeatureVector, unsigned char maxOutNumber,unsigned char *pOutImageNumber, double *pOutDistance, CString *RetrieveTime,int vector);
   //矢量检索，方法4:快速检索最相似的前16幅图像
   ///pFeatureVector图像库矢量结构体指针，iCurrentFeature:检索矢量的数量，
   //iRetrieveImageNumber图像库图像数目， QueryImageFeatureVector :关键图像的结构
   //pOutFeatureVector：输出结构体的头指针，maxOutNumber＝16输出图像的最多数目,*pOutImageNumber:输出图像的数目的地址
   //pDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
   //bool RetrieveKeyVqMethod_4AccelerateBest16(LPFEATUREVECTOR lpFeatureVector,int iCurrentFeature, long int iRetrieveImageNumber,FEATUREVECTOR QueryImageFeatureVector, PFEATUREVECTOR pOutFeatureVector, unsigned char maxOutNumber,unsigned char *pOutImageNumber, double *pOutDistance, CString *RetrieveTime);

   ///第一种参数提取算法：其中，参数提取的数目必须为7
   //计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：FeatureVector
   //Featurefirst:为特征矢量结构体的存入的第一个的编号，Featurenumber:该算法提取参数的个数
   bool FeatureVectorExtractMethod_1_7(unsigned char *pdata, int datawidth, int dataheigth, double *OrgFeature, int Featurefirst, int Featurenumber);
   
   ///方法2:计算基于颜色的三个的三个中心矩
   //计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：FeatureVector
   //Featurefirst:为特征矢量结构体的存入的第一个的编号，Featurenumber:该算法提取参数的个数
   ///本算法中,Featurenumber必须等于3
   bool FeatureVectorExtractMethod_2_3(unsigned char *pdata, int datawidth, int dataheigth, double *OrgFeature, int Featurefirst, int Featurenumber);
   //提取一个距：三阶距
   bool FeatureVectorExtractMethod_3_1(unsigned char *pdata, int datawidth, int dataheigth, double *OrgFeature, int Featurefirst, int Featurenumber);

   CRetrieveMethod();
   virtual ~CRetrieveMethod();
private:
   //For each pixel from rgb to hsv (for 24bits image pixel)
   void rgb2hsv_component(BYTE *rgb,double *hsv);
   //For each pixel from rgb to hvc (for 24bits image pixel)
   void rgb2hcv_component(BYTE *rgb,double *hcv);
   //For each pixel from rgb to lab (for 24bits image pixel)
   void rgb2XYZ_component(BYTE *rgb,double *XYZ);
   //For each pixel from rgb to lab (for 24bits image pixel)
   void rgb2Lab_component(BYTE *rgb,double *Lab);
   //For each pixel from rgb to Ycbcr (for 24bits image pixel)
   void rgb2YCbCr_component(BYTE *rgb,BYTE *YCbCr);
   void rgb2YCbCr_component(BYTE *rgb,double *YCbCr);
   //For each pixel from rgb to YIQ (for 24bits image pixel)
   void rgb2YIQ_component(BYTE *rgb,double *YIQ);
   //For each pixel from rgb to I1I2I3 (for 24bits image pixel)
   void rgb2I1I2I3_component(BYTE *rgb,double *I1I2I3);   
   //For each pixel from rgb to I1'I2'I3' (for 24bits image pixel)
   void rgb2I1_I2_I3_component(BYTE *rgb,double *I1_I2_I3);
   //For each pixel from rgb to L1L2L3 (for 24bits image pixel)
   void rgb2L1L2L3_component(BYTE *rgb,double *L1L2L3);
   //For each pixel from rgb to YUV (for 24bits image pixel)
   void rgb2YUV_component(BYTE *rgb,double *YUV);
   //For each pixel from rgb to xyY (for 24bits image pixel)
   void rgb2xyY_component(BYTE *rgb,double *xyY);
   //For each pixel from rgb to UVW (for 24bits image pixel)
   void rgb2UVW_component(BYTE *rgb,double *UVW);
   //For each pixel from rgb to RGBY (for 24bits image pixel)
   void rgb2RGBY_component(BYTE *rgb,double *RGBY);
   //For each pixel from rgb to YES (for 24bits image pixel)
   void rgb2YES_component(BYTE *rgb,double *YES);
   //For each pixel from rgb to hls (for 24bits image pixel)
   void rgb2hls_component(BYTE *rgb,double *hls);
   //For each pixel from rgb to hsi (for 24bits image pixel)
   void rgb2hsi_component(BYTE *rgb,double *hsi);
   //For each pixel from rgb to hsb (for 24bits image pixel)
   void rgb2hsb_component(BYTE *rgb,double *hsb);
   //For each pixel from rgb to Luv (for 24bits image pixel)
   void rgb2Luv_component(BYTE *rgb,double *Luv);
   //For Mpq of Hu moments
   double calculate_mpq(BYTE *image_byte,LONG width,LONG height,int p, int q, int whichch);
   double calculate_mpq(double *image_double,LONG width,LONG height,int p, int q, int whichch);
   //For Upq of Hu moments
   double calculate_upq(BYTE *image_byte,LONG width,LONG height,int p, int q, double avg_x, double avg_y,int whichch);
   double calculate_upq(double *image_double,LONG width,LONG height,int p, int q, double avg_x, double avg_y,int whichch);
   //compute the interpolation results from four neighbor values
   double calculate_bilinear_interpolation_value(double *value,double x,double y);
};
#endif // !defined(AFX_CRETRIEVEMETHOD_H__7D3135B1_07BA_4BE6_BE2B_84FA11D0E040__INCLUDED_)
