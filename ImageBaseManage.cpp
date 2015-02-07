       // ImageBaseManage.cpp: implementation of the CImageBaseManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBIRSystem.h"
#include "ImageBaseManage.h"
#include "DialogBase.h"

#include <direct.h>  //direct.h

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageBaseManage::CImageBaseManage()
{
	m_sFolder[0]="\\image\\";//folder
	m_sFolder[1]="\\feature\\";//folder
	m_sFolder[2]="\\knowledge\\";//folder
	m_sHeadFile="\\databasehead.ibh";  //headfilename
	m_sKnowlegeFile="knowlege.k";
	m_iVersion=VERSION_IMAGEBASE_1;
	m_bImageBaseValid=FALSE;
	m_iNumberTotalImage=0;
	m_sBasePathName="";
	m_dParament_a=0.2;   //the change of the similarity
	m_dParament_b=0.06;   //the change of the similarity and dis
	m_dParament_c=0.01;	 //the change of the images that not choosed
	this->m_iNumberDimensionFeature=CUURENT_FEATURE;  

}

CImageBaseManage::~CImageBaseManage()
{

}

//creat a new imagebase
bool CImageBaseManage::CreatImageBase(CString sPathName)
{
	CString ImageAddedPathName;		//
	this->m_bImageBaseValid=false;
	this->m_sBasePathName=sPathName;
	this->m_iNumberRelevance=0;
	this->m_iNumberTotalImage=0;

	//creat dir
	CString ImageBaseFileName=this->m_sBasePathName+this->m_sFolder[0];
	CString FeatureBaseFileName=this->m_sBasePathName+this->m_sFolder[1];
	CString KnowledgeBaseFileName=this->m_sBasePathName+this->m_sFolder[2];

	//make dir
	if(_mkdir(ImageBaseFileName.GetBuffer(0))!=0) return false;  //error
	if(_mkdir(FeatureBaseFileName.GetBuffer(0))!=0) return false;  //error
	if(_mkdir(KnowledgeBaseFileName.GetBuffer(0))!=0) return false;  //error

	//select the folder of images
	CDialogBase diagbase;
	if (diagbase.GetImageBaseFolder()==false) return false;
	ImageAddedPathName=diagbase.m_sPathName;//get the pathname

	
	//succeed
	//add the images and the features of them
	if(this->AddImages(ImageAddedPathName)==false) return false;

	//calculate the knowledge
	if(this->CalculateAndSaveAllImageKnowledge()==false) return false;
	//succeed
	//write the head
	m_stImageHeadFile.m_sFileType[0]='i';
	m_stImageHeadFile.m_sFileType[1]='b';
	m_stImageHeadFile.m_sFileType[2]='h';
	m_stImageHeadFile.m_dParament_a=this->m_dParament_a;
	m_stImageHeadFile.m_dParament_b=this->m_dParament_b;
	m_stImageHeadFile.m_dParament_c=this->m_dParament_c;
	m_stImageHeadFile.m_iNumberDimensionFeature=this->m_iNumberDimensionFeature;
	m_stImageHeadFile.m_iNumberRelevance=0;
	m_stImageHeadFile.m_iNumberTotalImage=this->m_iNumberTotalImage;
	m_stImageHeadFile.m_iVerson=VERSION_IMAGEBASE_1;  //VERSION

		//Open the file
	if(WriteHeadFile(this->m_sBasePathName,m_stImageHeadFile)==false) return false;
	//end
	m_bImageBaseValid=true;


return true;
}

  //load the path of the imagebase
bool CImageBaseManage::LoadImageBase(CString sPathName)
{
	if (this->ReadImageHeadFile(sPathName)==false) return false; //read the headfile
	
	return true;
	
}

//add one image into the base
bool CImageBaseManage::AddOneImage(CString filename)
{

	if(CalculateSaveFeature(this->m_iNumberTotalImage,filename)==false)
		return false;
	
	//Save the image file into the imagebase
	if(this->CopyImageToBase(this->m_iNumberTotalImage,filename)==false) 
		return false;

	//succeed
	this->m_iNumberTotalImage++;
		return true;

}
//add many images
bool CImageBaseManage::AddImages(CString folder)
{
	//in order to make it easy, here we only choose jpg image ,if wanted ,we can change
	this->AddFileType(folder,1); //add jpg file
		return true;

}
//caculate the feature of sPathName and Save in imagebase
bool CImageBaseManage::CalculateSaveFeature(unsigned int imageID,CString sPathName)
{
	FEATUREVECTOR stImageFeature;
	CString sFeatureID;
	CString sImageBaseFeatureName=this->m_sBasePathName+this->m_sFolder[1];	

	sFeatureID.Format("%s%d",sFeatureID,this->m_iNumberTotalImage);
	sFeatureID=sFeatureID+".fea";//feature
	sImageBaseFeatureName=sImageBaseFeatureName+sFeatureID;

	//calcuate the feature of sFullPathName and save in struct
	stImageFeature.m_iID =this->m_iNumberTotalImage;
	if(CalculateFileFeature(sPathName,stImageFeature)==false) return false;

	CFile FeatureFile;
	if(FeatureFile.Open(sImageBaseFeatureName,CFile::modeCreate|CFile::modeWrite)==false) return false;
	FeatureFile.Write(&stImageFeature,sizeof(stImageFeature));
	FeatureFile.Close();

	//end 
	return true;
}



//caculate the feature of the images
bool CImageBaseManage::CalculateAndSaveAllImageKnowledge()
{
	//invalid
	if(this->m_iNumberTotalImage<=0)	return false;

	//create the memory
	CFile cKnowledgeFile;
	double *pdSimilarityMatrix=new double[m_iNumberTotalImage*m_iNumberTotalImage];
	CString sKnowledgeFullPathName=this->m_sBasePathName+this->m_sFolder[2];
	CString sFeaturePath=this->m_sBasePathName+this->m_sFolder[1];	

	//get the knowledge file path
	sKnowledgeFullPathName=sKnowledgeFullPathName+this->m_sKnowlegeFile;
	if(this->CalculateSimilarity(pdSimilarityMatrix,this->m_iNumberTotalImage,sFeaturePath,this->m_iNumberDimensionFeature)==false)
	{
		delete []pdSimilarityMatrix;
		return false;
	}

	//save the file
	CFile cWriteFile;
	if(cWriteFile.Open(sKnowledgeFullPathName,CFile::modeReadWrite|CFile::modeCreate)==false)
	{
		delete []pdSimilarityMatrix;
		return false;
	}

	cWriteFile.SeekToBegin();
	cWriteFile.WriteHuge(pdSimilarityMatrix,sizeof(double)*m_iNumberTotalImage*m_iNumberTotalImage);
	cWriteFile.Close();
	delete []pdSimilarityMatrix;	
	return true;

}
bool CImageBaseManage::ReadImageHeadFile(CString sPathName)
{
	CString FullFileName=sPathName+m_sHeadFile;
	CFile ReadFile;

	//
	this->m_bImageBaseValid=false;

	//Open the file
	if(ReadFile.Open(FullFileName,CFile::modeRead)==false)
		return false;

	//read the head
	if(ReadFile.Read(&this->m_stImageHeadFile,sizeof(m_stImageHeadFile))!=sizeof(m_stImageHeadFile) )
			return false;
	if (m_stImageHeadFile.m_sFileType[0]!='i'||
		m_stImageHeadFile.m_sFileType[1]!='b'||
		m_stImageHeadFile.m_sFileType[2]!='h') return false;

	//version
	if (m_stImageHeadFile.m_iVerson!=VERSION_IMAGEBASE_1) 
	{
		AfxMessageBox("Version is wrong!",MB_OK);
		return false;
	}
	//succeed 
	m_bImageBaseValid=true;


	//close the file
	ReadFile.Close();
return true;
}

	 

bool CImageBaseManage::AddFileType(CString folder,int type)
{
	//检索文件夹文件
	CString str = folder;
    if(str.Right(1) != "\\")
	   str += "\\";

	//type
	switch(type) {
	case 1:
		str += "*.jpg";
		break;
	default:
		return false;
	}

	//find the file and added it
	CFileFind file;
	BOOL bContinueNumber = file.FindFile(str);
	while(bContinueNumber)
	{


		bContinueNumber = file.FindNextFile();
		if(!file.IsDirectory() && !file.IsDots())
		{	
		this->AddOneImage(file.GetFilePath());
		}

	}
	return true;
}


//copy the image into the base
bool CImageBaseManage::CopyImageToBase(unsigned int iID, CString filename)
{
	CFile imagefile;
	long int FileLength;
	char *pTempory;
	CString fileID;
	CString ImageBaseFileName=this->m_sBasePathName+this->m_sFolder[0];

	fileID.Format("%s%d",fileID,this->m_iNumberTotalImage);
	fileID=fileID+".jpg";
	ImageBaseFileName=ImageBaseFileName+fileID;

	if(imagefile.Open(filename,CFile::modeRead)==false) return false;

	FileLength=imagefile.GetLength();
	pTempory=new char[FileLength];
	imagefile.Read(pTempory,FileLength);
	imagefile.Close();

	if(imagefile.Open(ImageBaseFileName,CFile::modeCreate|CFile::modeWrite)==false) 
	{
		delete[]pTempory;
		return false;
	}
	imagefile.Write(pTempory,FileLength);
	imagefile.Close();
	
	//end
	delete[] pTempory;
	return true;
}

bool CImageBaseManage::CalculateFileFeature(CString sFullPathName, FEATUREVECTOR &stImageFeature)
{
	CJpeg JegImage;
	JPEG_IMAGE_INFO JegInfo;
	int iImageHeight,iImageWidth;
	long int iImageLength;
	byte *pcImageR,*pcImageG,*pcImageB;  //r,g ,b
//	float *pfImageH,*pfImageS,*pfImageV;//h,s,v
	int iNumberFeature=0; 
	
	if(JegImage.open(sFullPathName,IDCT_INT)==false) return false;

	JegImage.getImageInfo(&JegInfo);

	//get the paraments
	iImageWidth=JegInfo.imgWidth;
	iImageHeight=JegInfo.imgHeight;
	iImageLength=iImageWidth*iImageHeight;

	//get the points
	pcImageR=JegInfo.image[0];
	pcImageG=JegInfo.image[1];
	pcImageB=JegInfo.image[2];
//	pfImageH=ImageLoad.GetImageH();
//	pfImageS=ImageLoad.GetImageS();
//	pfImageV=ImageLoad.GetImageV();

//////////////////////////////////////////////////////////////////////////	
//if calculate and save one feature ,you should increase the NumberFeature
//the point is up,and the width and height are up.
//please put the feature in the stuct of stImageFeature
	//calculate the feature of the images

	//Get the feature of the R 
	//the first method 7 
	if(m_cRetMethod.CharacterVqDistillMethod_1_7(pcImageR,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],7)==false)
		return false;
	iNumberFeature=iNumberFeature+7;  //7
	
	//the second method 3 
	if(m_cRetMethod.CharacterVqDistillMethod_2_3(pcImageR,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],3)==false)
		return false;
	iNumberFeature=iNumberFeature+3; //7+3

	//the second method 3 
	if(m_cRetMethod.CharacterVqDistillMethod_3_1(pcImageR,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],1)==false)
		return false;
	iNumberFeature=iNumberFeature+1; //7+3+1


	//Get the feature of the G 
	//the first method 7 
	if(m_cRetMethod.CharacterVqDistillMethod_1_7(pcImageG,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],7)==false)
		return false;
	iNumberFeature=iNumberFeature+7;  //7
	
	//the second method 3 
	if(m_cRetMethod.CharacterVqDistillMethod_2_3(pcImageG,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],3)==false)
		return false;
	iNumberFeature=iNumberFeature+3; //7+3

	//the second method 3 
	if(m_cRetMethod.CharacterVqDistillMethod_3_1(pcImageG,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],1)==false)
		return false;
	iNumberFeature=iNumberFeature+1; //7+3+1

	//Get the feature of the B 
	//the first method 7 
	if(m_cRetMethod.CharacterVqDistillMethod_1_7(pcImageB,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],7)==false)
		return false;
	iNumberFeature=iNumberFeature+7;  //7
	
	//the second method 3 
	if(m_cRetMethod.CharacterVqDistillMethod_2_3(pcImageB,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],3)==false)
		return false;
	iNumberFeature=iNumberFeature+3; //7+3

	//the second method 3 
	if(m_cRetMethod.CharacterVqDistillMethod_3_1(pcImageB,iImageWidth,iImageHeight,&stImageFeature.m_dFileOriginalCharacter[iNumberFeature],1)==false)
		return false;
	iNumberFeature=iNumberFeature+1; //7+3+1

	
	//end of calculate the feature
//////////////////////////////////////////////////////////////////////////
	if (iNumberFeature!=CUURENT_FEATURE)
	{
		MessageBox(NULL,"the dimension of feature is error!","system information",MB_OK);
		return false;
	}
	stImageFeature.m_iImageHeight=iImageHeight;
	stImageFeature.m_iImageWidth=iImageWidth;


	return true;
}


bool CImageBaseManage::CalculateSimilarity(double *pdSimilarityMatrix, unsigned int iImageTotalNumber, CString sFeaturePath, int iFeatureDimension)
{
	
	if (iImageTotalNumber<=0)  return false;
	if(sFeaturePath.GetAt(sFeaturePath.GetLength()-1)!='\\')
		sFeaturePath=sFeaturePath+"\\";   

	unsigned int i,j;  
	CFile cFeatureFile;
//	FEATUREVECTOR stFeatureVector;
	bool bRight=true;  //no error

	//create the memory
	double **pdFeature=new double*[iImageTotalNumber];
	for(i=0;i<iImageTotalNumber;i++)
		pdFeature[i]=new double[iFeatureDimension];

	//read the feature
	for(i=0;i<iImageTotalNumber;i++)
	{
		CString sFeatureFullPathName;
		sFeatureFullPathName.Format("%s%d",sFeatureFullPathName,i);
		sFeatureFullPathName=sFeaturePath+sFeatureFullPathName;  //get the full path
		sFeatureFullPathName=sFeatureFullPathName+".fea";
		//open
		if(cFeatureFile.Open(sFeatureFullPathName,CFile::modeRead)==false)  //error
		{	
			bRight=FALSE;
			break;
		}
	
		//read
		if(cFeatureFile.Read(&m_stFeatureVector,sizeof(m_stFeatureVector))!=sizeof(m_stFeatureVector))
		{	
			bRight=false;
			break;
		}
	
		//close
		cFeatureFile.Close();
		
		//copy the feature
		for(j=0;j<iFeatureDimension;j++)
			pdFeature[i][j]=m_stFeatureVector.m_dFileOriginalCharacter[j];
	}
	//no error,we can calculate the similarity
	if(bRight==true)
	{
		//here we use the distance of two vector of algorithm 2
		bRight=this->CalculateSimilarity_Algorithm_2(pdSimilarityMatrix,pdFeature,iImageTotalNumber,iFeatureDimension);
	}

	//delete the memory
	for(i=0;i<iImageTotalNumber;i++)
		delete[] pdFeature[i];
	delete []pdFeature;

	//return 
	return bRight;

}
//pdSimilarityMatrix is iImageTotalNumber*iImageTotalNumber
//pdFeature is iImageTotalNumber*iFeatureDimension
bool CImageBaseManage::CalculateSimilarity_Algorithm_1(double *pdSimilarityMatrix,double **pdFeature,unsigned int iImageTotalNumber,int iFeatureDimension)
{
	unsigned int  i,j,k;

	for(i=0;i<iImageTotalNumber;i++)
			for(j=0;j<iImageTotalNumber;j++)
			{
				double dVaribleTotal1=0,dVaribleTotal2=0;				
				//
				for(k=0;k<iFeatureDimension;k++)
				{
					dVaribleTotal1=dVaribleTotal1+min(pdFeature[i][k],pdFeature[j][k]);
					dVaribleTotal2=dVaribleTotal2+(pdFeature[i][k]+pdFeature[j][k])/2.0;
				}

				pdSimilarityMatrix[i*iImageTotalNumber+j]=dVaribleTotal1/dVaribleTotal2;//					
			}
	return true;
}

bool CImageBaseManage::WriteHeadFile(CString sPathName, IMAGEHEADFILE stImageHeadFile)
{
	CString FullHeadFileName=sPathName+m_sHeadFile;
	CFile HeadFile;
	if(HeadFile.Open(FullHeadFileName,CFile::modeCreate|CFile::modeWrite)==false) return false;
	HeadFile.Write(&stImageHeadFile,sizeof(stImageHeadFile));
	//close the file
	HeadFile.Close();
	return true;
}


bool CImageBaseManage::CalculateSimilarity_Algorithm_2(double *pdSimilarityMatrix, double **pdFeature, unsigned int iImageTotalNumber, int iFeatureDimension)
{
	unsigned int  i,j,k;

	for(i=0;i<iImageTotalNumber;i++)
			for(j=0;j<iImageTotalNumber;j++)
			{
				double dVaribleTotal1=0,dVaribleTotal2=0;				
				//
				for(k=0;k<iFeatureDimension;k++)
				{
					dVaribleTotal1=dVaribleTotal1+min(pdFeature[i][k],pdFeature[j][k])/max((pdFeature[i][k]+pdFeature[j][k])/2.0,MIN_DATA);
				//	dVaribleTotal2=dVaribleTotal2+;
				}

				pdSimilarityMatrix[i*iImageTotalNumber+j]=dVaribleTotal1/iFeatureDimension;//					
			}
	return true;
}
