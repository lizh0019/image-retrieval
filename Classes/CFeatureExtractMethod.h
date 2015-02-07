// CFeatureExtractMethod.h: interface for the CCRetrieveMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRETRIEVEMETHOD_H__7D3135B1_07BA_4BE6_BE2B_84FA11D0E040__INCLUDED_)
#define AFX_CRETRIEVEMETHOD_H__7D3135B1_07BA_4BE6_BE2B_84FA11D0E040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************/
/*			Function: this class  is calculate the feature of maxtrix
 *          
 *   author	 : jinhaijun	email:jinhaijun@dsp.hit.edu.cn
 *	 version : version 2
 *	 data	 : 2005,5,16~
 *                                                                     */
/************************************************************************/
class CFeatureExtractMethod  
{
public:

///��һ�ֲ�����ȡ�㷨�����У�������ȡ����Ŀ����Ϊ7,from pFeature[0] to pFeature[6]
//����ߣ�dataheigth��datawidth
bool CharacterVqDistillMethod_1_7(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int characternumber);
bool CharacterVqDistillMethod_2_3(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int characternumber);
//��ȡһ���ࣺ���׾�
bool CharacterVqDistillMethod_3_1(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int characternumber);
	CFeatureExtractMethod();
	virtual ~CFeatureExtractMethod();

};

#endif // !defined(AFX_CRETRIEVEMETHOD_H__7D3135B1_07BA_4BE6_BE2B_84FA11D0E040__INCLUDED_)


