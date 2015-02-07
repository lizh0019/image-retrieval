// SimilarityCalculate.h: interface for the CSimilarityCalculate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMILARITYCALCULATE_H__14BE183E_7407_45DA_A35B_AA17AE249EC9__INCLUDED_)
#define AFX_SIMILARITYCALCULATE_H__14BE183E_7407_45DA_A35B_AA17AE249EC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************/
/*  function:		calculation the similarity if the feature has 
 *   
 *
 *   
 *	author:	jinhaijun
 *	email :	jinhaiju@dsp.hit.cn
 *  version:1	                                                                 */
/************************************************************************/
class CSimilarityCalculate  
{
public:
	
/************************************************************************/
/*  function:
 *	calculate the similarity of the feature in the path:sFeaturePath,save the similarity matrix in pdSimilarity,
 *	in the sFeaturePath ,there are iImageTotalNumber   
 *	paraments:	
 *	pdSimilarityMatrix:iImageTotalNumber*iImageTotalNumber,
 *	iImageTotalNumber:	the number of the feature
 *	sFeaturePath:		the feature path
 *	iFeatureDimension:	the dimension of the feature
/************************************************************************/

	bool CalculateSimilarity(double *pdSimilarityMatrix,unsigned int iImageTotalNumber,CString sFeaturePath,int iFeatureDimension);
	CSimilarityCalculate();	
	virtual ~CSimilarityCalculate();

	

};

#endif // !defined(AFX_SIMILARITYCALCULATE_H__14BE183E_7407_45DA_A35B_AA17AE249EC9__INCLUDED_)
