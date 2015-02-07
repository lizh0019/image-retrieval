// ImageBaseManage.h: interface for the CImageBaseManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEBASEMANAGE_H__BDF171CB_38DD_48BF_AB89_7196B807AB02__INCLUDED_)
#define AFX_IMAGEBASEMANAGE_H__BDF171CB_38DD_48BF_AB89_7196B807AB02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************/
/*			Function: this class  is managing the image base
 *          the imagebase includes three folder and one head file
 *   folder 1: images,the ID is from 0~number-1
 *	 folder 2: features of the images in folder 1
 *	 foler  3: knowledges of semantic
 *   headfile: a file that include the information 
 *   author	 : jinhaijun	email:jinhaijun@dsp.hit.edu.cn
 *	 version : version 2
 *	 data	 : 2005,5,29~
 *  class added:CImageLoad CFeatureExtractMethod,CDialogBase,CMatrix
 * description:it can add jpg image only, others are not available now
 *                                                                     */
/************************************************************************/
//#include "Classes\ImageLoad.h"
#include "Classes/cjpeg.h"
#include "Classes/CFeatureExtractMethod.h"
#include "Classes/Matrix.h"
#define MAX_FEATURE 200   
#define VERSION_IMAGEBASE_1 2
#define CUURENT_FEATURE 33
#define  MIN_DATA 0.00001



#ifndef __IMAGEBASE_STRUECT
#define __IMAGEBASE_STRUECT
typedef struct tagIMAGEHEADFILE
 {
		char m_sFileType[3];
		unsigned int m_iNumberTotalImage;  //the total of the images		
		int m_iNumberDimensionFeature;
		int m_iNumberRelevance;
		double m_dParament_a;
		double m_dParament_b;
		double m_dParament_c;    //three paraments
		int m_iVerson;
		
  } IMAGEHEADFILE, FAR *LPIMAGEHEADFILE, *PIMAGEHEADFILE;

// feature vector, one file of feature
typedef struct tagFEATUREVECOTR
 {
        unsigned int m_iID;  ///ID of the image
		double m_dFileOriginalCharacter[MAX_FEATURE]; //the original features
		int m_iImageWidth;        //the height of the image
		int m_iImageHeight;    ////the height of the image
  } FEATUREVECTOR, FAR *LPFEATUREVECTOR, *PFEATUREVECTOR;	
/*
//knowledge file, one file head of knowledge,after it is the similarity[m_iNumberTotalImage]
typedef struct tagKNOWLEDGEFILE
 {
        unsigned int m_iID;  ///ID of the image
		unsigned int m_iNumberTotalImage;  //the total of the images		
  } KNOWLEDGEFILE, FAR *LPKNOWLEDGEFILE, *PKNOWLEDGEFILE;
*/
#endif

class CImageBaseManage  
{
public:
	CImageBaseManage();
	virtual ~CImageBaseManage();
public:  //function
//	bool WriteKnowledgeFile(CString sPathName,CMatrix CMatrixKnowledge);


	//it create the head file ,and the feature file ,save the jpg,and knowledge file
	bool CreatImageBase(CString sPathName);  //creat a new imagebase
	bool LoadImageBase (CString sPathName);   //load the   of the imagebase

protected://paraments		

	unsigned int m_iNumberTotalImage;   ///the total number of image number
	bool m_bImageBaseValid;           //the symbol of the valid of the image
	CString m_sBasePathName;         //Image base path name
	CString m_sBaseHeadFileName;     //head file name
	int m_iNumberDimensionFeature;			//the dimension of the feature
	int m_iNumberRelevance;			//the times of relevance
	CString m_sFolder[3];//folder
	CString m_sHeadFile;
	CString m_sKnowlegeFile;
	int m_iVersion;             //the version
	double m_dParament_a,m_dParament_b,m_dParament_c;    //three paraments
	IMAGEHEADFILE m_stImageHeadFile;
	//KNOWLEDGEFILE m_stKnowledgeFile;
	FEATUREVECTOR m_stFeatureVector;
	CFeatureExtractMethod m_cRetMethod;   //image feature distill method

protected:
	bool CalculateSimilarity_Algorithm_2(double *pdSimilarityMatrix,double **pdFeature,unsigned int iImageTotalNumber,int iFeatureDimension);
	bool CalculateFileFeature(CString sFullPathName,FEATUREVECTOR &stImageFeature);
	//copy one image:filename into our imagebase
	bool CopyImageToBase(unsigned int iID,CString filename);
	//add images included in folder into our base, its type is jpg
	bool AddFileType(CString folder,int type);
	//caculate the feature of the image(the ID is imageID) and save the feature
	//into the path
	bool CalculateSaveFeature(unsigned int imageID,CString sPathName);
	bool CalculateAndSaveAllImageKnowledge();//caculate the feature of the images
	bool ReadImageHeadFile(CString sPathName);
	bool AddOneImage(CString filename);   //add one image into the base
	bool AddImages(CString folder);//add many images
	bool WriteHeadFile(CString sPathName,IMAGEHEADFILE stImageHeadFile);
/************************************************************************/
/*  function:
 *	calculate the similarity of the feature in the path:sFeaturePath,save the similarity matrix in pdSimilarity,
 *	in the sFeaturePath ,there are iImageTotalNumber   
 *	algorithm:1
 *	paraments:	
 *	pdSimilarityMatrix:iImageTotalNumber*iImageTotalNumber,
 *	iImageTotalNumber:	the number of the feature
 *	sFeaturePath:		the feature path
 *	iFeatureDimension:	the dimension of the feature
/************************************************************************/
	bool CalculateSimilarity(double *pdSimilarityMatrix,unsigned int iImageTotalNumber,CString sFeaturePath,int iFeatureDimension);
	bool CalculateSimilarity_Algorithm_1(double *pdSimilarityMatrix,double **pdFeature,unsigned int iImageTotalNumber,int iFeatureDimension);
	 
	
	


};

#endif // !defined(AFX_IMAGEBASEMANAGE_H__BDF171CB_38DD_48BF_AB89_7196B807AB02__INCLUDED_)
