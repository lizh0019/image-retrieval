// RetrievalControl.cpp: implementation of the CRetrievalControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBIRSystem.h"
#include "RetrievalControl.h"
#include <VECTOR>
#include "math.h"
#define IMAGE_ASSOCIATION_COFF 0.5
#define ANNOTION_ASSOCATION_COFF 0.5
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRetrievalControl::CRetrievalControl()
{
	m_bStudying=true;
	m_bShouldRetrievalAgain=false;
	this->m_bKnowledgeVaild=false;
	this->m_bSampleImageInvalid=false;
	m_bResultValid=false;
	this->m_iNumberResultImages=0;
	this->m_iNumberStudyTimes=0;
	this->m_iNumberTotalImage=0;
	this->m_iSampleImageID=-1;
	m_iNumberRetrievalLay=3;   //three lays
	m_dParament_a=0.2;   //the change of the similarity
	m_dParament_b=0.06;   //the change of the similarity and dis
	m_dParament_c=0.01;	 //the change of the images that not choosed
	m_dThreshold=0.8;   //
	m_sKnowlegeFile="knowlege.k";
	m_sFolder[0]="\\image\\";//folder
	m_sFolder[1]="\\feature\\";//folder
	m_sFolder[2]="\\knowledge\\";//folder
	m_sHeadFile="\\databasehead.ibh";  //headfilename
	this->m_sBasePathName="";
	m_sSampleImageFullName="";

	//for display
	m_iCurrentPage=0;
	m_iTotalPage=0;

	//for relevance
	m_iMaxNumberRelevance=0;
	piTotalImageID=NULL;   //set it null
	m_bFeedback=false;
	m_bConsiderNegative=true;  //we don't consider the negative ones
	
	m_iTestLay=3;
	m_iFeedbackTimes=0;
	this->stSemanticAnnotion=NULL;
	m_bAnnotionOpened=false;

	memset(m_stSemanticAnnotionRelevant,0,sizeof(SEMANTICANNOTION)*MAX_NUMBERANNOTION);
	m_stRetrievalSampleUp.iRetrievalType=-1;  //no exist
	m_stRetrievalSampleThis.iRetrievalType=-1;  //no exist

}

CRetrievalControl::~CRetrievalControl()
{

	//studying
	delete[] piTotalImageID;
	delete[] stSemanticAnnotion;	
	if(m_bStudying)
	SaveImageBase(this->m_sBasePathName);
}

bool CRetrievalControl::Retrieval(double dThreshold)
{
	if (dThreshold<MIN_THESHOLD) dThreshold=MIN_THESHOLD;
	if (dThreshold>MAX_THESHOLD)	dThreshold=MAX_THESHOLD;
	//should retrieval
	if (m_bShouldRetrievalAgain==false) return false;  //sample or base error

	//it is true or should be true		
	this->m_dThreshold=dThreshold;  //get the threshold	
	memcpy(&this->m_stRetrievalSampleUp,&this->m_stRetrievalSampleThis,sizeof(RETRIEVALSAMPLE));
	this->m_stRetrievalSampleThis.iRetrievalType=0;
	this->m_stRetrievalSampleThis.iRetrievalSampleID=this->m_iSampleImageID;
	//if this system has RF,and now can learn,we should learn the information
	//learn: we has rf,and  the system can learn
	if(this->m_bStudying)
	{
		this->MemoryLearning();
	}

	//for we update the image matrix ,and make a new retrieval,so
	//we should clear the RF paraments
	this->m_cPostiveImageInformation.SetMatrixColNumber(0);
	this->m_vNegativeImageInformation.empty();
	delete[] this->piTotalImageID;
	this->piTotalImageID=NULL;
	m_bFeedback=false;  //clear it
	this->m_iFeedbackTimes=0;  //set it to be zero
	return(this->RetrievalFromMatrix(this->m_cImageBaseKnowledgeMatrix,this->m_cRetrievalInformation,this->m_iSampleImageID,this->m_dThreshold));
	
}

bool CRetrievalControl::SetSampleID(CString sSampeleImageFullPathName)
{
	this->m_sSampleImageFullName=sSampeleImageFullPathName;
	
	CString SampleImagePath=sSampeleImageFullPathName;
	CString SampleFileName=sSampeleImageFullPathName;
	unsigned int iID=0;
	int ibit=0;
	int i;

	//get the path of sample image
	if (SampleImagePath=="")	
	{
		InitilizeReadSampleError();
		return false;

	}
	while ((SampleImagePath.GetAt(SampleImagePath.GetLength()-1)!='\\'))
	{
		SampleImagePath.Delete(SampleImagePath.GetLength()-1);		
	}

	//whether the same path
	if(SampleImagePath!=this->m_sBasePathName+m_sFolder[0])
	{
		InitilizeReadSampleError();	
		return false;
	}
	
//if same,set the id
	//delete the ".jpg"
	for(i=0;i<4;i++)
		SampleFileName.Delete(SampleFileName.GetLength()-1);
	//get the id
	while ((SampleFileName.GetAt(SampleFileName.GetLength()-1)!='\\'))
	{
		if(AddHighBit(SampleFileName.GetAt(SampleFileName.GetLength()-1),iID,ibit)==false)
		{
		InitilizeReadSampleError();
		return false;
		}
		ibit++;
		SampleFileName.Delete(SampleFileName.GetLength()-1);		
	}
	
/*
	if(this->m_iSampleImageID==iID)  //the same id
		m_bShouldRetrievalAgain=true;  //not retrieval again;	
	else 
		m_bShouldRetrievalAgain=true;  //should retrieval again;*/

	this->m_iSampleImageID=iID;  //set the id
	this->m_bSampleImageInvalid=true;
	this->m_iCurrentPage=0;
	this->m_iNumberResultImages=0;
	this->m_iTotalPage=0;
	this->m_bShouldRetrievalAgain=true;
	return true;
}



bool CRetrievalControl::ReadImageBase(CString sImageBasePath)
{
	this->m_sBasePathName=sImageBasePath;
	CString FullFileName=sImageBasePath+m_sHeadFile;
	CFile ReadFile;
	//

	//Open the file
	if(ReadFile.Open(FullFileName,CFile::modeRead)==false)
	{
		this->InitilizeReadBaseError();
		return false;
	}

	//read the head
	if(ReadFile.Read(&this->m_stImageHeadFile,sizeof(m_stImageHeadFile))!=sizeof(m_stImageHeadFile) )
			return false;
	if (m_stImageHeadFile.m_sFileType[0]!='i'||
		m_stImageHeadFile.m_sFileType[1]!='b'||
		m_stImageHeadFile.m_sFileType[2]!='h') 
	{
		this->InitilizeReadBaseError();
		return false;
	}

	//succeed 
	//close the file
	ReadFile.Close();

	//get the paraments
	this->m_iNumberTotalImage=m_stImageHeadFile.m_iNumberTotalImage;
	this->m_iNumberStudyTimes=m_stImageHeadFile.m_iNumberRelevance;
	this->m_dParament_a=m_stImageHeadFile.m_dParament_a;
	this->m_dParament_b=m_stImageHeadFile.m_dParament_b;
	this->m_dParament_c=m_stImageHeadFile.m_dParament_c;

	//read knowledge file
	if(ReadKnowledgeFile(sImageBasePath)==false) 
	{
		this->InitilizeReadBaseError();
		return false;
	}
	this->m_bKnowledgeVaild=true; 
	//reset the sample image ID
	return (this->SetSampleID(this->m_sSampleImageFullName));  
	
}

bool CRetrievalControl::ReadKnowledgeFile(CString &sPathName)
{
	//create the memory
	CFile cKnowledgeFile;
	CString sKnowledgeFullPathName=this->m_sBasePathName+this->m_sFolder[2];

	//get the knowledge file path
	sKnowledgeFullPathName=sKnowledgeFullPathName+this->m_sKnowlegeFile; 
//	m_cImageBaseKnowledgeMatrix.InitializeMatrixData(0.0,this->m_iNumberTotalImage,m_iNumberTotalImage);
	return (this->m_cImageBaseKnowledgeMatrix.LoadDataFromDoubleFile(sKnowledgeFullPathName,m_iNumberTotalImage,m_iNumberTotalImage));
}

bool CRetrievalControl::RetrievalFromMatrix(CMatrix &cImageBaseKnowledgeMatrix,CMatrix &cResultInformation,unsigned int iSampleImageID,double dThreshold)
{
	//assert the row and col is right
	if(this->m_iNumberTotalImage!=cImageBaseKnowledgeMatrix.GetMatrixColNumber()||
		this->m_iNumberTotalImage!=cImageBaseKnowledgeMatrix.GetMatrixRowNumber())
	{
		this->m_iNumberResultImages=0;
		return false;
	}

	switch(this->m_iNumberRetrievalLay) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		RetrievalFromMatrix_3Lays(cImageBaseKnowledgeMatrix,cResultInformation, iSampleImageID, dThreshold);
	default:
		break;
	}
	
	//get the result number
	this->m_iNumberResultImages=this->m_cRetrievalInformation.GetMatrixColNumber();
	this->m_iTotalPage=(m_iNumberResultImages+NUMBER_IMAGE_PERPAGE-1)/NUMBER_IMAGE_PERPAGE;
	this->m_cRetrievalInformation.ReListByRow_Decrease(1);   //list by similarity
	this->m_iCurrentPage=0;  //reset the current page
	return true;
}

bool CRetrievalControl::AddHighBit(char cHighBit, unsigned int &iID,int iBit)
{
	//get the bit of iID

	int iHighNumber;

	//get the high bit
	switch(cHighBit) {
	case '0':
		iHighNumber=0;
		break;
	case '1':
		iHighNumber=1;
		break;
	case '2':
		iHighNumber=2;
		break;
	case '3':
		iHighNumber=3;
		break;
	case '4':
		iHighNumber=4;
		break;
	case '5':
		iHighNumber=5;
		break;
	case '6':
		iHighNumber=6;
		break;
	case '7':
		iHighNumber=7;
		break;
	case '8':
		iHighNumber=8;
		break;
	case '9':
		iHighNumber=9;
		break;

	default:
		return false;
	}
	iID=iID+iHighNumber*pow(10,iBit);
	return true;
}

//retrieval for 3 lays
void CRetrievalControl::RetrievalFromMatrix_3Lays(CMatrix &cImageBaseKnowledgeMatrix, CMatrix &cResultInformation, unsigned int iSampleImageID, double dThreshold)
{
	
	vector<int> viIDList;  //ID list
	CMatrix cResultLay_0(2,1),cResultLay_1(2,0),cResultLay_2(2,0),cResultLay_3(2,0);  //three lays,row :2,col: not sure
	//for test
	CMatrix cResultLay_4(2,0),cResultLay_5(2,0);
	//end of for test
	TMatrix pMatrixLayInformation;

	int i;
	int iNumberImageOnLay;

	viIDList.resize(this->m_iNumberTotalImage);
	for(i=0;i<m_iNumberTotalImage;i++)
		viIDList[i]=i;

	
	cResultLay_0.SetMatrixData(iSampleImageID,0,0);
	cResultLay_0.SetMatrixData(1.00,1,0);
	viIDList[iSampleImageID]=-1;  //make it impossible
	if(this->m_iTestLay>=1)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_0, cResultLay_1, viIDList, dThreshold);
	if(this->m_iTestLay>=2)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_1, cResultLay_2, viIDList, dThreshold);
	if(this->m_iTestLay>=3)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_2, cResultLay_3, viIDList, dThreshold);
	if(this->m_iTestLay>=4)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_3, cResultLay_4, viIDList, dThreshold);
	if(this->m_iTestLay>=5)
	RetrievalFromUpLayMatrix(cImageBaseKnowledgeMatrix, cResultLay_4, cResultLay_5, viIDList, dThreshold);


	cResultInformation.InitializeMatrixData(0.0,3,0);//Initialize the matrix

	//add the lay0
	iNumberImageOnLay=cResultLay_0.GetMatrixColNumber();
	pMatrixLayInformation=cResultLay_0.GetMatrixPoint();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(0);//initilize it to 1,//it is itself,so relevance
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay1
	pMatrixLayInformation=cResultLay_1.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_1.GetMatrixColNumber();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay2
	pMatrixLayInformation=cResultLay_2.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_2.GetMatrixColNumber();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay3
	pMatrixLayInformation=cResultLay_3.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_3.GetMatrixColNumber();

	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);  //initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}

		//add the lay4
	pMatrixLayInformation=cResultLay_4.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_4.GetMatrixColNumber();

	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);  //initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay5
	pMatrixLayInformation=cResultLay_5.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_5.GetMatrixColNumber();

	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);  //initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
}
//retrieval from the up lays
void CRetrievalControl::RetrievalFromUpLayMatrix(CMatrix &cImageBaseKnowledgeMatrix, CMatrix &cUpResultLay, CMatrix &cThisResultLay, vector<int> &viIDList, double dThreshold)
{
	
//	TMatrix pImageBaseKnoledgeMatrix=cImageBaseKnowledgeMatrix.GetMatrixPoint();
//	TMatrix *pResultInformation=cResultInformation.GetMatrixPoint();
	int iUpNumberLay=cUpResultLay.GetMatrixColNumber();//the number
	int i,j,iTempUpID;
	double dTempleUpSimilarity,dTempleThisSimilarity;
	//test
//	double *pdTempMatrixMemory=new double [cImageBaseKnowledgeMatrix.GetMatrixColNumber()*cImageBaseKnowledgeMatrix.GetMatrixRowData()];
	
	
	for(i=0;i<iUpNumberLay;i++)  //find
	{
		//temp up id
		iTempUpID=cUpResultLay.GetMatirxData_uint(0,i);
		dTempleUpSimilarity=cUpResultLay.GetMatirxData_double(1,i);
		for(j=0;j<this->m_iNumberTotalImage;j++)  //all
		{			
			//temp similarity
			dTempleThisSimilarity=dTempleUpSimilarity*(cImageBaseKnowledgeMatrix.GetMatirxData_double(iTempUpID,j));
			//
			if (viIDList[j]>=0&&dTempleThisSimilarity>=dThreshold)
				{
					cThisResultLay.AddOneCol();  ///add one col
					cThisResultLay.SetMatrixData(j,0,cThisResultLay.GetMatrixColNumber()-1);				
					cThisResultLay.SetMatrixData(dTempleThisSimilarity,1,cThisResultLay.GetMatrixColNumber()-1);
					viIDList[j]=-1;  //make it impossible
				}
		}
	}

}

//display the image
bool CRetrievalControl::DisplayCurrentPage(CPictureCtrl *pclPictureCtrl[],int *piRelevance[],CString *psSimilarity[])
{
	int iDisplayStart=this->m_iCurrentPage*NUMBER_IMAGE_PERPAGE;
	int iDisplayEnd=(this->m_iCurrentPage+1)*NUMBER_IMAGE_PERPAGE;
	int i;
	if(m_iCurrentPage>m_iTotalPage) 
	{
		m_iCurrentPage=0;		
		return false;  //can't display
	}	

	//no image base
	if(this->m_bKnowledgeVaild==false) return false;
	
	//display one by one
	CString fileID;
	CString ImageBaseFileName=this->m_sBasePathName+this->m_sFolder[0];
	for(i=iDisplayStart;i<iDisplayEnd;i++)
	{
		if (i>=this->m_iNumberResultImages)
		{
			pclPictureCtrl[i-iDisplayStart]->DisEnableDisplay();  //
			pclPictureCtrl[i-iDisplayStart]->LoadImage("");
			psSimilarity[i-iDisplayStart]->Empty();
			*piRelevance[i-iDisplayStart]=-1; 
			continue;
		}
		fileID.Empty();
		fileID.Format("%s%d",fileID,(int)m_cRetrievalInformation.GetMatrixPoint()[0][i]);
		fileID=fileID+".jpg";
		fileID=ImageBaseFileName+fileID;

		if((pclPictureCtrl[i-iDisplayStart]->LoadImage(fileID))==false) return false;  //load image

		//Initialize the simliarity
		psSimilarity[i-iDisplayStart]->Empty();
		psSimilarity[i-iDisplayStart]->Format("%s%f",*psSimilarity[i-iDisplayStart],m_cRetrievalInformation.GetMatrixPoint()[1][i]);

		//Initialize the relevance

		*piRelevance[i-iDisplayStart]=(int)m_cRetrievalInformation.GetMatrixPoint()[2][i];  //
	}
		return true;
	
	
}

bool CRetrievalControl::SetNexToBeCurrentPage()
{
	//0,1
	if (this->m_iTotalPage==0) { return false;	}
	if (this->m_iCurrentPage>=this->m_iTotalPage-1)	return false;

	m_iCurrentPage++;
	return true;
}

bool CRetrievalControl::SetPreToBeCurrentPage()
{
	if (this->m_iCurrentPage<=0)	return false;

	m_iCurrentPage--;
	return true;
}

bool CRetrievalControl::SetFirstToCurrentPage()
{
	if (this->m_iCurrentPage==0)	return false;
	m_iCurrentPage=0;
	return true;
}
//get the path
CString CRetrievalControl::GetImageBasePath()
{
	return this->m_sBasePathName;
}

//get the sample id
CString CRetrievalControl::GetSampleID()
{
	CString temp;
	if (this->m_iSampleImageID==-1) 
	{
		temp.Empty();
		return temp;
	}
	temp.Format("%s%d",temp,m_iSampleImageID);
	return temp;
}

CString CRetrievalControl::GetNumberImageDataBase()
{
	CString temp;
	if (this->m_iNumberTotalImage==0) 
	{
		temp.Empty();
		return temp;
	}
	temp.Format("%s%d",temp,m_iNumberTotalImage);
	return temp;
}

int CRetrievalControl::GetIntNumberImageDataBase()
{
	return m_iNumberTotalImage;
}

CString CRetrievalControl::GetNumberResult()
{
	CString temp;
	if (this->m_iNumberResultImages==0) 
	{
		temp.Empty();
		return temp;
	}
	temp.Format("%s%d",temp,m_iNumberResultImages);
	return temp;
}

unsigned int CRetrievalControl::GetTotalPage()
{
	return this->m_iTotalPage;

}

unsigned int CRetrievalControl::GetCurrentPage()
{
	return this->m_iCurrentPage;

}

//if read sample error,we should initize the paraments
void CRetrievalControl::InitilizeReadSampleError()
{
	this->m_bSampleImageInvalid=false;
	m_bShouldRetrievalAgain=false;  //error
	this->m_iSampleImageID=-1;
	this->m_cRetrievalInformation.InitializeMatrixData(0.0,3,0);//Initialize
	this->m_cPostiveImageInformation.InitializeMatrixData(0.0,3,0);////Initialize
	this->m_iNumberResultImages=0;	
	this->m_iTotalPage=0;
	this->m_iCurrentPage=0;
	m_iMaxNumberRelevance=0;
}

//if read base error,we should initize the paraments
void CRetrievalControl::InitilizeReadBaseError()
{
	m_sBasePathName="";
	this->m_bKnowledgeVaild=false;
	m_bShouldRetrievalAgain=false;  //error
	this->m_iSampleImageID=-1;  //base error so the sample id also error
	this->m_cRetrievalInformation.InitializeMatrixData(0.0,3,0);//Initialize
	this->m_iNumberResultImages=0;	
	this->m_iTotalPage=0;
	this->m_iCurrentPage=0;
	this->m_iNumberStudyTimes=0;
	this->m_iNumberTotalImage=0;
	m_iMaxNumberRelevance=0;
	m_iNumberStudyTimes=0;
}

bool CRetrievalControl::IsNeedRetrieval()
{
return this->m_bShouldRetrievalAgain;
}
bool CRetrievalControl::IsKnowledgeValid()
{
return this->m_bKnowledgeVaild;
}

/************************************************************************/
/* set the relevance information to the matrix: m_cRetrievalInformation                                                                     */
/************************************************************************/
bool CRetrievalControl::SetRelevanceCurrentPageResult(int *piRelevance[])
{
	//get the real list number
	int iStartNumber=this->m_iCurrentPage*NUMBER_IMAGE_PERPAGE;
	int iEndNumber=(this->m_iCurrentPage+1)*NUMBER_IMAGE_PERPAGE;
	if(this->m_cRetrievalInformation.GetMatrixColNumber()==0) return false;

	for(int i=iStartNumber;i<iEndNumber;i++)
	{
		if (i>this->m_cRetrievalInformation.GetMatrixColNumber()-1)//out of the result
		{
			//set the feedback
			this->m_iMaxNumberRelevance=this->m_cRetrievalInformation.GetMatrixColNumber()-1;
			return false;
		}
		m_iMaxNumberRelevance=i;  //set the feedback 
		this->m_cRetrievalInformation.SetMatrixData((double)(*piRelevance[i-iStartNumber]),2,i);
	}
	return true;
}

bool CRetrievalControl::UpdateMatrixbyRelevance()
{
	unsigned int i,j;
	unsigned int iIDi,iIDj;
	//m_dParament_a:0-0		sim=sim+m_dParament_a*(1-sim) 0.5
	//m_dParament_b:0-1		sim=sim-m_dParament_b*(sim-0) 0.3 
	//m_dParament_c:0-2		sim=sim-m_dParament_c*(sim-0) 0.2
	//here the parament m_dParament_c not used here
//	double dTempleRelevance1,dTempleRelevance2;
	double dTempeSimilarity;
	//start update,0,1,2,3.....11-1
	unsigned int iTempPostiveNumber,iTempNegativeNumber;
	iTempPostiveNumber=this->m_cPostiveImageInformation.GetMatrixColNumber();
	iTempNegativeNumber=this->m_vNegativeImageInformation.size();
	for(i=0;i<iTempPostiveNumber;i++)
	{
		
		//PP
		//increase the similarity of positive and postive
		iIDi=m_cPostiveImageInformation.GetMatirxData_uint(0,i); //get the id
		for(j=i+1;j<iTempPostiveNumber;j++)
		{
			iIDj=m_cPostiveImageInformation.GetMatirxData_uint(0,j); //get the id
			
			//get the similarity
			dTempeSimilarity=m_cImageBaseKnowledgeMatrix.GetMatirxData_double(iIDi,iIDj);
			dTempeSimilarity=min(1.0,dTempeSimilarity+m_dParament_a*(1-dTempeSimilarity));
			m_cImageBaseKnowledgeMatrix.SetMatrixData(dTempeSimilarity,iIDi,iIDj);
			m_cImageBaseKnowledgeMatrix.SetMatrixData(dTempeSimilarity,iIDj,iIDi);
		}
		
		//PN
		//decrease the similarity of positive and negative
		for(j=0;j<iTempNegativeNumber;j++)
		{
			
			iIDj=m_vNegativeImageInformation[j]; //get the id
			
			//get the similarity
			dTempeSimilarity=m_cImageBaseKnowledgeMatrix.GetMatirxData_double(iIDi,iIDj);
			dTempeSimilarity=max(0.0,dTempeSimilarity-m_dParament_b*(dTempeSimilarity-0));
			m_cImageBaseKnowledgeMatrix.SetMatrixData(dTempeSimilarity,iIDi,iIDj);
			m_cImageBaseKnowledgeMatrix.SetMatrixData(dTempeSimilarity,iIDj,iIDi);
		}
		
		
	}	
	//end
	
	return true;
	
}



bool CRetrievalControl::SaveKnowledge(CString sPathName)
{
	bool bSucceed=false;
	CString sKnowledgeFullPathName=this->m_sBasePathName+this->m_sFolder[2];

	//get the knowledge file path
//	sKnowledgeFullPathName=sKnowledgeFullPathName+this->m_sKnowlegeFile; 
	bSucceed=this->m_cImageBaseKnowledgeMatrix.SaveDataDoubleToFile(sKnowledgeFullPathName+this->m_sKnowlegeFile);
	bSucceed=bSucceed&&this->m_cSemanticLink.SaveDataDoubleToFile(sKnowledgeFullPathName+"SemanticLink.l");
	bSucceed=bSucceed&&this->m_cSemanticMatrix.SaveDataDoubleToFile(sKnowledgeFullPathName+"SemanticMatrix.m");
	return bSucceed;
}

bool CRetrievalControl::SaveImageBase(CString sPath)
{
	this->m_sBasePathName=sPath;
	CString FullFileName=sPath+m_sHeadFile;
	CFile ReadFile;
	//

	//Open the file
	if(ReadFile.Open(FullFileName,CFile::modeReadWrite)==false)
	{
		return false;
	}

	//change the head
	this->m_stImageHeadFile.m_dParament_a=this->m_dParament_a;
	m_stImageHeadFile.m_dParament_b=m_dParament_b;
	m_stImageHeadFile.m_dParament_c=m_dParament_c;
	m_stImageHeadFile.m_iNumberRelevance=this->m_iNumberStudyTimes;
	m_stImageHeadFile.m_iNumberTotalImage=this->m_iNumberTotalImage;

	ReadFile.Write(&this->m_stImageHeadFile,sizeof(m_stImageHeadFile));

	//succeed 
	//close the file
	ReadFile.Close();
	return SaveKnowledge(this->m_sBasePathName);

}

//get the study times
CString CRetrievalControl::GetStudtyTimes()
{
	CString temp;
	temp.Format("%s%d",temp,this->m_iNumberStudyTimes);
	return temp;
}

void CRetrievalControl::GetFeedbackParament(double &dparamentRR, double &dparamentRI, double &dparamentRU,bool &bStudying)
{
	//get the paraments
	dparamentRR=this->m_dParament_a;
	dparamentRI=this->m_dParament_b;
	dparamentRU=this->m_dParament_c;
	bStudying=this->m_bStudying;
}

void CRetrievalControl::SetFeedbackParament(double dparamentRR, double dparamentRI, double dparamentRU,bool bStudying)
{
	this->m_dParament_a=dparamentRR;
	this->m_dParament_b=dparamentRI;
	this->m_dParament_c=dparamentRU;
	this->m_bStudying=bStudying;
}
//NumberTotal/100
//one class number is 100
double CRetrievalControl::GetRecall()
{
int i,iClass;
unsigned int nCol;
unsigned int NumberTotal=0;
if (nCol=this->m_cRetrievalInformation.GetMatrixColNumber(),nCol==0)	return -1;

//get the class
	iClass=this->m_iSampleImageID/100;
	for(i=0;i<nCol;i++)
		if(m_cRetrievalInformation.GetMatirxData_uint(0,i)/100==iClass)
			NumberTotal++;

//delete itself
	if (NumberTotal>=1)  NumberTotal--;
	return ((double)NumberTotal/(100.0-1));


}
//NumberTotal/nCol
double CRetrievalControl::GetPrecise()
{
int i,iClass;
unsigned int nCol;
unsigned int NumberTotal=0;
if (nCol=this->m_cRetrievalInformation.GetMatrixColNumber(),nCol==0)	return -1;

//get the class
	iClass=this->m_iSampleImageID/100;
	for(i=0;i<nCol;i++)
		if(m_cRetrievalInformation.GetMatirxData_uint(0,i)/100==iClass)
			NumberTotal++;
		//delete itself
	if (NumberTotal>=1)  NumberTotal--;
	//if only itself was retrieved
	if (nCol==1)   return 1;

	return ((double)NumberTotal/(nCol-1));
}

/************************************************************************/
/* function 
* pararments:
*return:   
*other:                                                                 */
/************************************************************************/
BOOL CRetrievalControl::RelevanceFeedback(double dThreashold)
{
   int i,j;
   int iTotalRetrievalResult=this->m_cRetrievalInformation.GetMatrixColNumber();  //number of all result
   double dTempSimilarity=0;  //temporary total similarity
   double dTempNegSimilarity=0;  //temporary total similarity of negatives
   int iTemTotalPositive=0;   //temporary total positive ones
   int iTemTotalNegative=0;   //temporary total negative ones
   //clear the positive,because we shall put them
  // this->m_vNegativeImageInformation.empty();
   this->m_cPostiveImageInformation.SetMatrixColNumber(0);  //clear the id
   
   	//for the first time to allocate the memory of the images' ID,the second rf ,we need not changed it
   if(piTotalImageID==NULL) 
   {
	   piTotalImageID=new int[this->m_iNumberTotalImage];    // all images' id
	   if(piTotalImageID==NULL) return false;
	   //set the id
	   for(i=0;i<this->m_iNumberTotalImage;i++)
		   piTotalImageID[i]=i;    //set the id is the sort number ,[0] is 0
	   this->m_iFeedbackTimes=0;
   }
   //assert no error
   if (iTotalRetrievalResult<=0||this->m_iNumberTotalImage<=1) return false;
   
   //assert the thread
   	if (dThreashold<MIN_THESHOLD) dThreashold=MIN_THESHOLD;
	if (dThreashold>MAX_THESHOLD)	dThreashold=MAX_THESHOLD;
	this->m_dThreshold=dThreashold;



   //reset the positive and negative image
   
   for(i=0;i<iTotalRetrievalResult;i++)
   {
	   if (0==this->m_cRetrievalInformation.GetMatirxData_double(2,i) )  //0 row:id,1row:simlarity 2row:relevance ,0,1,2
	   {
		   //copy the postive data of retrieval results to the end of matrix of positve:m_cPostiveImageInformation
		   this->m_cPostiveImageInformation.AddOneCol(this->m_cRetrievalInformation.GetMatirxData_double(0,i));			
		   this->m_cPostiveImageInformation.SetMatrixData(this->m_cRetrievalInformation.GetMatirxData_double(1,i),1,this->m_cPostiveImageInformation.GetMatrixColNumber()-1);
		   this->m_cPostiveImageInformation.SetMatrixData(this->m_cRetrievalInformation.GetMatirxData_double(2,i),2,this->m_cPostiveImageInformation.GetMatrixColNumber()-1);

		   piTotalImageID[this->m_cRetrievalInformation.GetMatirxData_uint(0,i)]=-1;  //set it invalid
	   }
	   else if (2==this->m_cRetrievalInformation.GetMatirxData_double(2,i))  //2 is negative
	   {
		   //for the negative ones,we only need remember their IDs
		   this->m_vNegativeImageInformation.push_back(this->m_cRetrievalInformation.GetMatirxData_uint(0,i));
		   piTotalImageID[this->m_cRetrievalInformation.GetMatirxData_uint(0,i)]=-2;  //set it invalid
	   }
   }
   //get the positive ones and number of negative ones
   iTemTotalPositive=this->m_cPostiveImageInformation.GetMatrixColNumber();
   iTemTotalNegative=this->m_vNegativeImageInformation.size();

   if (iTemTotalPositive==0)//not exist similar
   {
	   return false;
   }
  //clear the retrieval result ,because we shall retrieval it again 
	this->m_cRetrievalInformation.SetMatrixColNumber(iTemTotalPositive);

	//copy the positve images' id into the retrieval images
	for(i=0;i<iTemTotalPositive;i++)
	{
		this->m_cRetrievalInformation.SetMatrixData(this->m_cPostiveImageInformation.GetMatirxData_double(0,i),0,i);			
		this->m_cRetrievalInformation.SetMatrixData(this->m_cPostiveImageInformation.GetMatirxData_double(1,i),1,i);
		this->m_cRetrievalInformation.SetMatrixData(this->m_cPostiveImageInformation.GetMatirxData_double(2,i),2,i);
	} 

   //feedback retrieval in the other's image ids

	for(i=0;i<this->m_iNumberTotalImage;i++)
	{
		//negative,we shall not retrieval in the RF
		if (piTotalImageID[i]==-2)	continue;   //not need to retrieval,piTotalImageID[i] is i or -1 or -2
		//postive
		if (piTotalImageID[i]==-1)
		{
			//reset the postive images' id for we maybe change it to be not postive
			//we may be retrieval it in the RF, for example, we changed it to be negative
			//but this time ,we do not need to retrieve it
			piTotalImageID[i]=i;  
			continue;
		}
		dTempSimilarity=0.0;   //clear it 

		//caculate the average similarity of one image to the postive ones
		//we also could consider the negative ones ,for example we should need one
		//image similarity to the postive ones and far away from the negative ones
		for(j=0;j<iTemTotalPositive;j++)
			dTempSimilarity+=this->m_cImageBaseKnowledgeMatrix.GetMatirxData_double(this->m_cPostiveImageInformation.GetMatirxData_uint(0,j),i);

		//caculate the average of sim
		dTempSimilarity=dTempSimilarity/iTemTotalPositive;

		//add its ID to the retrieval result or not?
		if (dTempSimilarity<this->m_dThreshold)  //not need to consider it
			continue; 
		//we need to consider it 
		//but if the system consider the negative ones ,we also need 		
		if(this->m_bConsiderNegative==true&&iTemTotalNegative>0)
		{
			dTempNegSimilarity=0;
			for(j=0;j<iTemTotalNegative;j++)
				dTempNegSimilarity+=this->m_cImageBaseKnowledgeMatrix.GetMatirxData_double(this->m_vNegativeImageInformation[j],i);
			//caculate the average
			dTempNegSimilarity=dTempNegSimilarity/iTemTotalNegative;

			//if the average of the similarity of negative is large than m_dThreshold ,we delete it
			if (dTempNegSimilarity>this->m_dThreshold)  
				continue;
		}

		//here we can add it 		
		//add the image (ID:i) to the retrieval result
		this->m_cRetrievalInformation.AddOneCol(i);  //the ID is i			
		//set the similarity:the average sim
		this->m_cRetrievalInformation.SetMatrixData(dTempSimilarity,1,m_cRetrievalInformation.GetMatrixColNumber()-1);
		//set the relevant 1; unlable
		this->m_cRetrievalInformation.SetMatrixData(1,2,m_cRetrievalInformation.GetMatrixColNumber()-1);
		
	}
	m_bFeedback=true;
	//end of feedback retrieval in the other's image ids
 	//get the result number
	this->m_iNumberResultImages=this->m_cRetrievalInformation.GetMatrixColNumber();
	this->m_iTotalPage=(m_iNumberResultImages+NUMBER_IMAGE_PERPAGE-1)/NUMBER_IMAGE_PERPAGE;
	this->m_cRetrievalInformation.ReListByRow_Decrease(1);   //list by similarity
	this->m_iCurrentPage=0;  //reset the current page
	this->m_iFeedbackTimes++;  //feedback times add one
	return true;
   
}

//for test
void CRetrievalControl::SetTestLay(int i)
{
	if (i<1) i=1;
	if(i>5) i=5;
	this->m_iTestLay=i;
}
//for test
bool CRetrievalControl::SetSampleID(unsigned int iID)
{
	this->m_iSampleImageID=iID;
	this->m_bSampleImageInvalid=true;
	return true;
	
}

CString CRetrievalControl::GetFeedbackTimes()
{
	CString temp;
	temp.Format("%s%d",temp,this->m_iFeedbackTimes);
	return temp;
}


//set the annotion
void CRetrievalControl::SetAnnotion(bool bOpened)
{
 this->m_bAnnotionOpened=bOpened;	
}

/************************************************************************/
/* Function GetRelevantAnnotion 
 *type:0 -0 1-0 ,type=0
 *     0-1   1-1 ,type=1
 *iRelevance[] :all relevant annotion ids
 *  iNUmberAnnotion:the number of relevant annotion    
 * return the number of the relevant annotion                                                                 */
/************************************************************************/
int CRetrievalControl::GetRelevantAnnotionID(int iRelevantAnnotionID[],int iNumberAnnotion,int iType)
{
	//assert the retrieval results is valid
	if (iNumberAnnotion<=0||iNumberAnnotion>NUMBERANNOTION)	iNumberAnnotion=NUMBERANNOTION;
	if (m_iNumberResultImages<=0) return 0;  //no results
	int iNumberCaculateAnnotionImage=min(m_iNumberResultImages,MAX_NUMBERIMAGE_ANNOTION);
	
	CMatrix	cRelevantAnnotion(2,NUMBERANNOTION);
	int i,j;
	double dTotalRelevant;	
	
	int iTypeThis=this->m_stRetrievalSampleThis.iRetrievalType;
	int iSampleID=this->m_stRetrievalSampleThis.iRetrievalSampleID;

	//relevant by type 1
	if (iTypeThis==1) iType =1;
	//by type 0
	else iType=0;
	
	for(i=0;i<NUMBERANNOTION;i++)
	{
		dTotalRelevant=0;
		for(j=0;j<iNumberCaculateAnnotionImage;j++)
		{
			dTotalRelevant+=this->m_cSemanticLink.GetMatirxData_double(i,this->m_cRetrievalInformation.GetMatirxData_uint(0,j));
		}
		dTotalRelevant=dTotalRelevant/iNumberCaculateAnnotionImage;
		switch(iType) {
		case 0:  //default considering it
			break;
		case 1:  //should changed considered the annotion matrix
			dTotalRelevant=IMAGE_ASSOCIATION_COFF*dTotalRelevant+ANNOTION_ASSOCATION_COFF*this->m_cSemanticMatrix.GetMatirxData_double(iSampleID,i);
			break;
		default:
			break;
		}	
		cRelevantAnnotion.SetMatrixData(i,0,i);
		cRelevantAnnotion.SetMatrixData(dTotalRelevant,1,i);
	}//end get the relevant annotion
	cRelevantAnnotion.ReListByRow_Decrease(1);
	//end sort
	for(i=0;i<iNumberAnnotion;i++)
		iRelevantAnnotionID[i]=cRelevantAnnotion.GetMatirxData_uint(0,i);	
	return iNumberAnnotion;
	
}
/************************************************************************/
/* return real annotion                                                                     */
/************************************************************************/
bool CRetrievalControl::GetRelevantAnnotionText(char *pRelevantAnnotionText,int iMaxLength,int iOneRelevantAnnotionID)
{
	SEMANTICANNOTION stTempSemantic;
	CFile TempFile;
	CString sPathName=m_sBasePathName+"\\knowledge\\";
	if (iOneRelevantAnnotionID<0||iOneRelevantAnnotionID>=NUMBERANNOTION) 
	{
		memset(pRelevantAnnotionText,0,iMaxLength);
		return false;
	}
	

	//get the knowledge file path
	sPathName=sPathName+"SemanticAnnotion.a";
	if(TempFile.Open(sPathName,CFile::modeRead)==false) return false;
	TempFile.Seek(iOneRelevantAnnotionID*sizeof(SEMANTICANNOTION),CFile::begin);
	TempFile.Read((void *)(&stTempSemantic),sizeof(SEMANTICANNOTION));
	memcpy(pRelevantAnnotionText,stTempSemantic.sSemanticAnnotion,sizeof(stTempSemantic.sSemanticAnnotion));

	TempFile.Close();
		
//	if (SemanticMatrix.SaveDataDoubleToFile(sInitalSemanticMatrixFullPathName)==false) return false
	return true;


}

bool CRetrievalControl::RetrievalByAnnotionIndex(int iAnnotionIndex, double dThreshold)
{
	if (dThreshold<MIN_THESHOLD) dThreshold=MIN_THESHOLD;
	if (dThreshold>MAX_THESHOLD)	dThreshold=MAX_THESHOLD;
	//should retrieval
//	if (m_bShouldRetrievalAgain==false) return false;  //sample or base error

	//it is true or should be true		
	this->m_dThreshold=dThreshold;  //get the threshold	
	//if this system has RF,and now can learn,we should learn the information
	//learn: we has rf,and  the system can learn
	//another retrieval
	memcpy(&this->m_stRetrievalSampleUp,&this->m_stRetrievalSampleThis,sizeof(RETRIEVALSAMPLE));
	this->m_stRetrievalSampleThis.iRetrievalType=1;
	this->m_stRetrievalSampleThis.iRetrievalSampleID=iAnnotionIndex;
	//if this system has RF,and now can learn,we should learn the information
	//learn: we has rf,and  the system can learn
	if(this->m_bStudying)
	{
		this->MemoryLearning();
	}

	//for we update the image matrix ,and make a new retrieval,so
	//we should clear the RF paraments
	this->m_cPostiveImageInformation.SetMatrixColNumber(0);
	this->m_vNegativeImageInformation.empty();
	delete[] this->piTotalImageID;
	this->piTotalImageID=NULL;
	m_bFeedback=false;  //clear it
	this->m_iFeedbackTimes=0;  //set it to be zero
	return(this->RetrievalFromSemanticLink(this->m_cSemanticLink,this->m_cRetrievalInformation,iAnnotionIndex,this->m_dThreshold));
	
	
	return true;
}
//CMatrix cImageBaseKnowledgeMatrix,CMatrix &cResultInformation,unsigned int iSampleImageID,double dThreshold
bool CRetrievalControl::RetrievalFromSemanticLink(CMatrix &cSemanticLink,CMatrix &cResultInformation,int iSampleAnnotionID,double dThreshold)
{
	if(this->m_iNumberTotalImage!=cSemanticLink.GetMatrixColNumber())
	{
		this->m_iNumberResultImages=0;
		return false;
	}
	this->m_dThreshold=dThreshold;
	vector<int> viIDList;  //ID list
	CMatrix cResultLay_0(2,0),cResultLay_1(2,0),cResultLay_2(2,0),cResultLay_3(2,0);  //three lays,row :2,col: not sure
	TMatrix pMatrixLayInformation;
	double dTempleThisSimilarity;

	int i;
	int iNumberImageOnLay;

	viIDList.resize(this->m_iNumberTotalImage);
	for(i=0;i<m_iNumberTotalImage;i++)
		viIDList[i]=i;
 //the annotion is larger than T
	for(i=0;i<m_iNumberTotalImage;i++)
	{
		dTempleThisSimilarity=this->m_cSemanticLink.GetMatirxData_double(iSampleAnnotionID,i);
		if (dTempleThisSimilarity>=m_dThreshold)
		{
			cResultLay_0.AddOneCol();  ///add one col
			cResultLay_0.SetMatrixData(i,0,cResultLay_0.GetMatrixColNumber()-1);				
			cResultLay_0.SetMatrixData(dTempleThisSimilarity,1,cResultLay_0.GetMatrixColNumber()-1);
			viIDList[i]=-1;  //make it impossible
		}
	}
	//retrival from the ImageKnowledgeMatrix
	//0->1
	RetrievalFromUpLayMatrix(this->m_cImageBaseKnowledgeMatrix, cResultLay_0, cResultLay_1, viIDList, dThreshold);
	//1->2
	RetrievalFromUpLayMatrix(m_cImageBaseKnowledgeMatrix, cResultLay_1, cResultLay_2, viIDList, dThreshold);
	cResultInformation.InitializeMatrixData(0.0,3,0);//Initialize the matrix

	//add the lay0
	iNumberImageOnLay=cResultLay_0.GetMatrixColNumber();
	pMatrixLayInformation=cResultLay_0.GetMatrixPoint();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1,//it is itself,so relevance
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay1
	pMatrixLayInformation=cResultLay_1.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_1.GetMatrixColNumber();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
		//add the lay2
	pMatrixLayInformation=cResultLay_2.GetMatrixPoint();
	iNumberImageOnLay=cResultLay_2.GetMatrixColNumber();
	for(i=0;i<iNumberImageOnLay;i++)
	{
		cResultInformation.AddOneCol(1);//initilize it to 1
		cResultInformation.SetMatrixData(pMatrixLayInformation[0][i],0,cResultInformation.GetMatrixColNumber()-1);
		cResultInformation.SetMatrixData(pMatrixLayInformation[1][i],1,cResultInformation.GetMatrixColNumber()-1);
	//	cResultInformation.SetMatrixData(1,2,cResultInformation.GetMatrixColNumber()-1);
	}
	
	//get the result number
	this->m_iNumberResultImages=this->m_cRetrievalInformation.GetMatrixColNumber();
	this->m_iTotalPage=(m_iNumberResultImages+NUMBER_IMAGE_PERPAGE-1)/NUMBER_IMAGE_PERPAGE;
	this->m_cRetrievalInformation.ReListByRow_Decrease(1);   //list by similarity
	this->m_iCurrentPage=0;  //reset the current page

	return true;
}
/************************************************************************/
/* learning the information                                                                     */
/************************************************************************/
bool CRetrievalControl::MemoryLearning()
{
#define  LINKINCREASE 0.12
#define  LINKDECREASE 0.01
	int i,j;
	double dTempLink;
	int iUpID,iThisID;

	//update the fuzzy relvevant semantic matrix
	if (this->m_bFeedback==true) 
	{
		this->UpdateMatrixbyRelevance();  //all update the knowledge
	}
	
	
	//0 1
	if (this->m_stRetrievalSampleUp.iRetrievalType==0&&this->m_stRetrievalSampleThis.iRetrievalType==1&&m_bFeedback==true) //0 ,1 
	{
		//update the link between the positive,negative images and this annotion
		for(i=0;i<this->m_cPostiveImageInformation.GetMatrixColNumber();i++)  //positive image
		{
			for(j=0;j<this->m_stRetrievalSampleThis.iRetrievalSampleID;j++)  //all negative annotion
			{
				dTempLink=this->m_cSemanticLink.GetMatirxData_double(j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
				dTempLink-=(dTempLink)*LINKDECREASE;
				this->m_cSemanticLink.SetMatrixData(dTempLink,j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			}
			//one postive annotion
			dTempLink=this->m_cSemanticLink.GetMatirxData_double(this->m_stRetrievalSampleThis.iRetrievalSampleID,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
			dTempLink+=(1-dTempLink)*LINKINCREASE;
			this->m_cSemanticLink.SetMatrixData(dTempLink,this->m_stRetrievalSampleThis.iRetrievalSampleID,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			//negative annotin
			for(j=this->m_stRetrievalSampleThis.iRetrievalSampleID+1;j<NUMBERANNOTION;j++)
			{
				dTempLink=this->m_cSemanticLink.GetMatirxData_double(j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
				dTempLink-=(dTempLink)*LINKDECREASE;
				this->m_cSemanticLink.SetMatrixData(dTempLink,j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			}

			
		}
		for(i=0;i<this->m_vNegativeImageInformation.size();i++)  //negative image
		{
			//one postive annotion
			dTempLink=this->m_cSemanticLink.GetMatirxData_double(this->m_stRetrievalSampleThis.iRetrievalSampleID,m_vNegativeImageInformation[i]);
			dTempLink-=(dTempLink)*LINKDECREASE;
			this->m_cSemanticLink.SetMatrixData(dTempLink,this->m_stRetrievalSampleThis.iRetrievalSampleID,m_vNegativeImageInformation[i]);
		}
	this->m_iNumberStudyTimes++;
	
	}  //0 1
	//1 0 and feedback
	else if (this->m_stRetrievalSampleUp.iRetrievalType==1&&this->m_stRetrievalSampleThis.iRetrievalType==0&&this->m_bFeedback==true) //0 ,1 
	{
		//update the link between the postive,negative images and the up annotion
		for(i=0;i<this->m_cPostiveImageInformation.GetMatrixColNumber();i++)  //positive image
		{
			for(j=0;j<this->m_stRetrievalSampleUp.iRetrievalSampleID;j++)  //all negative annotion
			{
				dTempLink=this->m_cSemanticLink.GetMatirxData_double(j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
				dTempLink-=(dTempLink)*LINKDECREASE;
				this->m_cSemanticLink.SetMatrixData(dTempLink,j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			}
			//one postive annotion
			dTempLink=this->m_cSemanticLink.GetMatirxData_double(this->m_stRetrievalSampleUp.iRetrievalSampleID,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
			dTempLink+=(1-dTempLink)*LINKINCREASE;
			this->m_cSemanticLink.SetMatrixData(dTempLink,this->m_stRetrievalSampleUp.iRetrievalSampleID,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			//negative annotion
			for(j=this->m_stRetrievalSampleUp.iRetrievalSampleID+1;j<NUMBERANNOTION;j++)
			{
				dTempLink=this->m_cSemanticLink.GetMatirxData_double(j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
				dTempLink-=(dTempLink)*LINKDECREASE;
				this->m_cSemanticLink.SetMatrixData(dTempLink,j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			}
			
		}
		for(i=0;i<this->m_vNegativeImageInformation.size();i++)  //negative image
		{
			//one postive annotion
			dTempLink=this->m_cSemanticLink.GetMatirxData_double(this->m_stRetrievalSampleUp.iRetrievalSampleID,m_vNegativeImageInformation[i]);
			dTempLink-=(dTempLink)*LINKDECREASE;
			this->m_cSemanticLink.SetMatrixData(dTempLink,this->m_stRetrievalSampleUp.iRetrievalSampleID,m_vNegativeImageInformation[i]);
		}

	this->m_iNumberStudyTimes++;
	}  //1 0
	//1 1
	else  if (this->m_stRetrievalSampleUp.iRetrievalType==1&&this->m_stRetrievalSampleThis.iRetrievalType==1)//1 1
	{
		//update the link between the postive,negative images and the up annotion
		for(i=0;i<this->m_cPostiveImageInformation.GetMatrixColNumber();i++)  //positive image
		{
			for(j=0;j<this->m_stRetrievalSampleUp.iRetrievalSampleID;j++)  //all negative annotion
			{
				dTempLink=this->m_cSemanticLink.GetMatirxData_double(j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
				dTempLink-=(dTempLink)*LINKDECREASE;
				this->m_cSemanticLink.SetMatrixData(dTempLink,j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			}
			//one postive annotion
			dTempLink=this->m_cSemanticLink.GetMatirxData_double(this->m_stRetrievalSampleUp.iRetrievalSampleID,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
			dTempLink+=(1-dTempLink)*LINKINCREASE;
			this->m_cSemanticLink.SetMatrixData(dTempLink,this->m_stRetrievalSampleUp.iRetrievalSampleID,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			//negative annotion
			for(j=this->m_stRetrievalSampleUp.iRetrievalSampleID+1;j<NUMBERANNOTION;j++)
			{
				dTempLink=this->m_cSemanticLink.GetMatirxData_double(j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));		
				dTempLink-=(dTempLink)*LINKDECREASE;
				this->m_cSemanticLink.SetMatrixData(dTempLink,j,m_cPostiveImageInformation.GetMatirxData_uint(0,i));
			}
			
		}
		for(i=0;i<this->m_vNegativeImageInformation.size();i++)  //negative image
		{
			//one postive annotion
			dTempLink=this->m_cSemanticLink.GetMatirxData_double(this->m_stRetrievalSampleUp.iRetrievalSampleID,m_vNegativeImageInformation[i]);
			dTempLink-=(dTempLink)*LINKDECREASE;
			this->m_cSemanticLink.SetMatrixData(dTempLink,this->m_stRetrievalSampleUp.iRetrievalSampleID,m_vNegativeImageInformation[i]);
		}

		//update the annotion matrix,increase the up annotion and this annotion ,decrease the up annotion and the others
		//get the idS
		iUpID=this->m_stRetrievalSampleUp.iRetrievalSampleID;
		iThisID=this->m_stRetrievalSampleThis.iRetrievalSampleID;
		for(i=0;i<NUMBERANNOTION;i++)
		{
			if (i==iUpID)  continue;  //itself
			else if (i==iThisID)  //relevant
			{
				dTempLink=this->m_cSemanticMatrix.GetMatirxData_double(iUpID,i);
				dTempLink+=(1-dTempLink)*LINKINCREASE;
				m_cSemanticMatrix.SetMatrixData(dTempLink,iUpID,i);
				m_cSemanticMatrix.SetMatrixData(dTempLink,i,iUpID);
			}
			else  //irrelevant
			{
				dTempLink=this->m_cSemanticMatrix.GetMatirxData_double(iUpID,i);
				dTempLink-=(dTempLink)*LINKDECREASE;
				m_cSemanticMatrix.SetMatrixData(dTempLink,iUpID,i);
				m_cSemanticMatrix.SetMatrixData(dTempLink,i,iUpID);
			}
		}
		this->m_iNumberStudyTimes++;	
	}
	else  if (this->m_stRetrievalSampleUp.iRetrievalType==0&&this->m_stRetrievalSampleThis.iRetrievalType==0&&this->m_bFeedback)//1 1
	{
		//the default retrieval should have feedback
		this->m_iNumberStudyTimes++;	
	}
	this->m_bFeedback=false;
	return true;
	
}
/************************************************************************/
/* return the number of the IDs of the annotions                                                                     */
/************************************************************************/
int CRetrievalControl::RetrievalByKeyWord(int *piRelevantKeywordID,int iMaxNumberResults,CString sKeyWord)
{
	SEMANTICANNOTION stTempSemantic;
	CString sTempAnnotion;
	CFile TempFile;
	CString sPathName=m_sBasePathName+"\\knowledge\\";
	int i,j;
	int iFindOneWordNumber;
	int iNumberReturns;
	CMatrix	cRelevantAnnotion(2,0);	
	CString sTempKeyWord;
	if (iMaxNumberResults<=0)
	{
		return 0;
	}	
	//get the knowledge file path
	sPathName=sPathName+"SemanticAnnotion.a";
	if(TempFile.Open(sPathName,CFile::modeRead)==false) return -1;

	//one by one
	for(i=0;i<NUMBERANNOTION;i++)
	{
		//initial
		iFindOneWordNumber=0;
		TempFile.Seek(i*sizeof(SEMANTICANNOTION),CFile::begin);
		TempFile.Read((void *)(&stTempSemantic),sizeof(SEMANTICANNOTION));	
		sTempAnnotion=stTempSemantic.sSemanticAnnotion;
		//find the word
		sTempKeyWord.Empty();
		sTempKeyWord=sKeyWord;
		for(j=2;j<=strlen(sKeyWord);j=j+2)
		{
			CString tempchar=sTempKeyWord.Left(j);						
			if(sTempAnnotion.Find(tempchar,0)>=0) 
				iFindOneWordNumber++;
			sTempKeyWord.Delete(0,2);
		}//end of find
		//add it
		if (iFindOneWordNumber!=0)
		{
			cRelevantAnnotion.AddOneCol(i);
			cRelevantAnnotion.SetMatrixData(iFindOneWordNumber,1,cRelevantAnnotion.GetMatrixColNumber()-1);
		}
	}//end of all
	
	if (cRelevantAnnotion.GetMatrixColNumber()==0) return 0;  //no find
	
	cRelevantAnnotion.ReListByRow_Decrease(1);  //resort by  similarity
	//the return number
	iNumberReturns=min(iMaxNumberResults,cRelevantAnnotion.GetMatrixColNumber());
	for(i=0;i<iNumberReturns;i++)
	{
		piRelevantKeywordID[i]=cRelevantAnnotion.GetMatirxData_uint(0,i);
	}
	
	TempFile.Close();
	return iNumberReturns;

}
//write file //knowledge//SemanticLink.l
BOOL CRetrievalControl::WriteInitalLinkFile()
{

	CFile cInitalLinkFile;
	CString sInitalLinkFullPathName=m_sBasePathName+"\\knowledge\\";
	int i,j,k;
	float fTotalSimlarity;
	

	//get the knowledge file path
	sInitalLinkFullPathName=sInitalLinkFullPathName+"SemanticLink.l";
	CMatrix SemanticLink(NUMBERANNOTION,this->m_iNumberTotalImage);
	//caculate the initial linknet
	
	for(i=0;i<NUMBERANNOTION;i++)// i row
	{
		for(k=0;k<stSemanticAnnotion[i].iNumberLabel;k++)  ///set the annotation 1
		{
			SemanticLink.SetMatrixData(1.0,i,stSemanticAnnotion[i].iIDLabeled[k]);
		}
		for(j=0;j<m_iNumberTotalImage;j++)  //j col
		{
			fTotalSimlarity=0;
			for(k=0;k<stSemanticAnnotion[i].iNumberLabel;k++)  //total
				fTotalSimlarity+=m_cImageBaseKnowledgeMatrix.GetMatirxData_double(stSemanticAnnotion[i].iIDLabeled[k],j);
			fTotalSimlarity=fTotalSimlarity/stSemanticAnnotion[i].iNumberLabel;
			fTotalSimlarity=max(fTotalSimlarity,SemanticLink.GetMatirxData_double(i,j));
			SemanticLink.SetMatrixData(fTotalSimlarity,i,j);
			
		}
	}
	if (SemanticLink.SaveDataDoubleToFile(sInitalLinkFullPathName)==false) return false;
//	cInitalLinkFile.Write(SemanticLink,sizeof(float)*NUMBERANNOTION*m_iNumberTotalImage);
//	cInitalLinkFile.Close();
//	return true;
	delete[] stSemanticAnnotion;
	stSemanticAnnotion=NULL;
	return true;
}

//write the intitial semantic matrix //knowledge//SemanticMatrix.m
//write the semantic Matrix, 
BOOL CRetrievalControl::WriteInitalMatrixFile()
{
	CFile cInitalLinkFile;
	CString sInitalSemanticMatrixFullPathName=m_sBasePathName+"\\knowledge\\";


	//get the knowledge file path
	sInitalSemanticMatrixFullPathName=sInitalSemanticMatrixFullPathName+"SemanticMatrix.m";
	CMatrix SemanticMatrix(NUMBERANNOTION,NUMBERANNOTION);  //all 0.00001
	for(int i=0;i<NUMBERANNOTION;i++)
		SemanticMatrix.SetMatrixData(1.0,i,i);  //set the relevant itself 1
	//caculate the initial linknet	
	
	if (SemanticMatrix.SaveDataDoubleToFile(sInitalSemanticMatrixFullPathName)==false) return false;
	return true;
}
//read the annotion->image linke file
bool CRetrievalControl::ReadAnnotionLinkFile()
{
	//create the memory
//	CFile cLinkFile;
	CString sLinkFileFullPathName=this->m_sBasePathName+this->m_sFolder[2];

	//get the knowledge file path
	sLinkFileFullPathName=sLinkFileFullPathName+"SemanticLink.l"; 
//	this->m_cSemanticLink.InitializeMatrixData(0.0,NUMBERANNOTION,m_iNumberTotalImage);
	return (this->m_cSemanticLink.LoadDataFromDoubleFile(sLinkFileFullPathName,NUMBERANNOTION,m_iNumberTotalImage));
}
//read the annotion->image linke file
bool CRetrievalControl::ReadAnnotionMatrixFile()
{
	//create the memory
//	CFile cAnnotionMatrixFile;
	CString sAnnotionMatrixFileFileFullPathName=this->m_sBasePathName+this->m_sFolder[2];

	//get the knowledge file path
	sAnnotionMatrixFileFileFullPathName=sAnnotionMatrixFileFileFullPathName+"SemanticMatrix.m"; 
//	this->m_cSemanticMatrix.InitializeMatrixData(0.0,NUMBERANNOTION,NUMBERANNOTION);
	return (this->m_cSemanticMatrix.LoadDataFromDoubleFile(sAnnotionMatrixFileFileFullPathName,NUMBERANNOTION,NUMBERANNOTION));
}
bool CRetrievalControl::WriteLabelToTheEndFile(CFile &writefile, CString sLabelString, int *piIDLabeld, int iNumberIDLabed)
{
	//get the min of the label
	iNumberIDLabed=min(iNumberIDLabed,MAX_NUMBER_LABELONONEANNOTION);	
	int iSize=strlen(sLabelString.GetBuffer(0));
	iSize=min(iSize,MAX_NUMBER_CHARONEANNOTION-1);  //get the min of the char

	SEMANTICANNOTION stSemanticAnnotionWrite;
	memset(&stSemanticAnnotionWrite,0,sizeof(SEMANTICANNOTION));
	stSemanticAnnotionWrite.iNumberLabel=iNumberIDLabed;
	memcpy(stSemanticAnnotionWrite.sSemanticAnnotion,sLabelString.GetBuffer(0),iSize);
	for(int i=0;i<iNumberIDLabed;i++)
		stSemanticAnnotionWrite.iIDLabeled[i]=piIDLabeld[i];

	writefile.SeekToEnd();
	writefile.Write(&stSemanticAnnotionWrite,sizeof(SEMANTICANNOTION));	
	return true;
}

int CRetrievalControl::GetRetrievalTypeThis()
{
	return this->m_stRetrievalSampleThis.iRetrievalType;
}

CString CRetrievalControl::GetRetrievalIDThis()
{

	CString temp;
	int iType=this->m_stRetrievalSampleThis.iRetrievalType;
	if (0==iType) //image 
	{
	if (this->m_stRetrievalSampleThis.iRetrievalSampleID>=0) 
	{
		temp.Empty();
		temp.Format("%s%d",temp,m_iSampleImageID);
		return temp;
	}
	}
	else  //annotaion
	 
	{
		char tempchar[100];
		if(this->GetRelevantAnnotionText(tempchar,100,m_stRetrievalSampleThis.iRetrievalSampleID)==false)
			memset(tempchar,0,100);
		else
			temp=tempchar;		

	}
	
	return temp;
//	return 
}
