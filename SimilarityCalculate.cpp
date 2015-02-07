// SimilarityCalculate.cpp: implementation of the CSimilarityCalculate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBIRSystem.h"
#include "SimilarityCalculate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimilarityCalculate::CSimilarityCalculate()
{

}

CSimilarityCalculate::~CSimilarityCalculate()
{

}

bool CSimilarityCalculate::CalculateSimilarity(double *pdSimilarityMatrix, unsigned int iImageTotalNumber, CString sFeaturePath, int iFeatureDimension)
{
	
	if (iImageTotalNumber<=0)  return false;
	if(sFeaturePath.GetAt(sFeaturePath.GetLength()-1)!='\\')
		sFeaturePath=sFeaturePath+"\\";   

	unsigned int i,j;  
	CFile cFeatureFile;
	bool bError=false;  //no error

	//create the memory
	double **pdFeature=new double*[iImageTotalNumber];
	for(i=0;i<iImageTotalNumber;i++)
		pdFeature[i]=new double[iFeatureDimension];

	//read the feature
	for(i=0;i<iImageTotalNumber;i++)
	{
		CString sFeatureFileName;
		sFeatureFileName.Format("%s%d",sFeatureFileName,i);
		sFeaturePath=sFeaturePath+sFeatureFileName;  //get the full path
		if(cFeatureFile.Open(sFeaturePath,CFile::modeRead)==false)  //error
		{	
			bError=true;
			break;
		}
		
	}

	//delete the memory
	for(i=0;i<iImageTotalNumber;i++)
		delete[] pdFeature[i];
	delete []pdFeature;

	return true;
}
