// CFeatureExtractMethod.cpp: implementation of the CCRetrieveMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CFeatureExtractMethod.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFeatureExtractMethod::CFeatureExtractMethod()
{

}

CFeatureExtractMethod::~CFeatureExtractMethod()
{

}

//����ߣ�dataheigth��datawidth�׵�ַΪ*pdata������ʸ�����ڽṹ���У�charactervq
//characterfirst:Ϊ����ʸ���ṹ��Ĵ���ĵ�һ���ı�ţ�characternumber:���㷨��ȡ�����ĸ���
///���㷨��,characternumber�������7
bool CFeatureExtractMethod::CharacterVqDistillMethod_1_7(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int characternumber)
{
	if (characternumber!=7) 
	{
		MessageBox(NULL,"CharacterDistill Number error","error!",MB_OK);
		return false;
	}
////add your word here
/////ע�⣺����һ����������iCharacterNumbercheck������
//////////////////////////////////////////////////////////////////////////
	////////����1�������ֵ
	//////�㷨��������ʼֵ�������ط�Ϊ�����֣�������Ե����ģ����ĵľ�ֵ��Ϊ�µ���ֵ����
	//////////ǰһ�ε������ֵ�Ƚϣ�����ͬ�����
	/////////�������ֵ���Ƶ�������
	////˵��������1��2����ɫ�еĲ����������������ֵ��������ȡ������
		int i,j;
		double regiondata1=128,regiondata2=128;         ///�����ֵ��ֵ
		int Max=1000;                                     ///�������Ĵ���
		int regionnumberleft=0,regionnumberright=0;           ////��������ļ���ֵ
		long double regiontotallleft=0,regiontotalright=0;         ////����������ܺ�
		long int count;     //������
	
		for(count=0;count<Max;count++)   ////ִ�д���
		{
			regionnumberleft=0;
			regionnumberright=0;  
			regiontotallleft=0;
			regiontotalright=0;
				for(i=0; i<dataheigth; i++)
					for(j=0; j<datawidth; j++)
					{
						if(*(pdata + i*datawidth + j)<=(unsigned char)regiondata2)
						{
							regionnumberleft++;       ////���������һ
							regiontotallleft=regiontotallleft+(*(pdata + i*datawidth + j));//�ܺͼ�һ

						}
						else 
							regiontotalright=regiontotalright+(*(pdata + i*datawidth + j));
					}
					regionnumberright=datawidth*dataheigth-regionnumberleft;///�Ҽ���������ó�
					if (regionnumberright==0)  //�ų��쳣
					{
						regionnumberright=1;
					}
						if (regionnumberleft==0)//�ų��쳣
					{
						regionnumberleft=1;
					}
					regiondata2=(regiontotallleft/regionnumberleft+regiontotalright/regionnumberright)/2.0;////���㹫ʽ
					if((unsigned char)regiondata2==(unsigned char)regiondata1)///����
						break;
					else 
						regiondata1=regiondata2;

		}
	pdFeature[0]=regiondata2/255.0; ///��һ��
	
///����2
	pdFeature[1]=(double)regionnumberleft/(regionnumberleft+regionnumberright);
////end of ��ɫ
	///��ɫ�����ĸ���

//////˵��������3��4��5�������еĲ��������������ڹ�����������ȡ��
////����3:
///ͳ�ƹ�������
	double (*texturematrix)[256]=new double[256][256];  ///��������x
	double (*texturematriy)[256]=new double[256][256];  ///��������x
	for(i=0; i<256; i++)
			for(j=0; j<256; j++)
			{
				texturematrix[i][j]=0;
				texturematriy[i][j]=0;

			}
	for(i=1; i<dataheigth-1; i++)
		for(j=1; j<datawidth-1; j++)
				{
					texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j-1)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j-1)]+1;
					texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j+1)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + i*datawidth + j+1)]+1;
					texturematriy[*(pdata + i*datawidth + j)][*(pdata + (i-1)*datawidth + j)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + (i-1)*datawidth + j)]+1;
					texturematriy[*(pdata + i*datawidth + j)][*(pdata + (i+1)*datawidth + j)]=texturematrix[*(pdata + i*datawidth + j)][*(pdata + (i+1)*datawidth + j)]+1;
									
				}
	

///////����3��������Խ��ߵĹ��Ծأ�Con
/////////�ص㣺���ڴ��������ڹ��������Ԫ�ؽϼ��������Խ��߸�������ʱ��h-k)�����ز��С��
//			  ��Ӧ��CONֵҲ��С���෴������ϸ��������Ӧ��CONֵ�ϴ�
////////����4���������Ƕ��׾أ�Asm
////////�ص㣺 ����һ�ֶ�ͼ��Ҷȷֲ��Ķ����������������Ԫ�طֲ��ϼ��������Խ���ʱ��
//		  	 ��Ӧ��ASMֵ�ϴ󣬷�֮��ASMֵ��С��
////////����5����
/////////�ص㣺�����������Ԫ�������ҽϷ�ɢʱ��ENTֵ�ϴ󣻷�֮���������Ԫ�ؽϼ���ʱ��
//      	  ENTֵ��С��
		unsigned long int MaxNumber=dataheigth*datawidth;////��һ������
		unsigned long double Ent1=0,Ent2=0;					////�ر���Ent1ˮƽ��Ent2
		unsigned long double Asm1=0,Asm2=0;           ///��������
	    unsigned long double Con1=0,Con2=0;        ///�������
		for(i=0; i<256; i++)
			for(j=0; j<256; j++)
			{
				long double varible1=texturematrix[i][j]/MaxNumber;  //�򻯼���ı���,/////��һ����������
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
	pdFeature[2]=(Con1+Con2)/2/255.0/255.0;             //��ȡ�������
	pdFeature[3]=(Asm1+Asm2)/2;              ///��ȡ��������
	pdFeature[4]=-(Ent1+Ent2)/2;              ///��ȡ�ر���
	delete[] texturematrix;
	delete[] texturematriy;


//////����3��4��5��ȡ����	
////end of ����
///��������ĸ���

	
////����6,7��ȡ����״������
///////���׾غ�һ�׾�
/////�ص㣺���Ƕ�ͼ���һ�ֵ�һ��ͳ����ʽ�����ļ���Ҫ�õ�ͼ��������е�������ص����ص㣬
////	��һ������ͼ����F��X��,������ֶ�������ֻ��XYƽ���ϵ����޸��㲻Ϊ�㣬�����֤������
////////���׾ش��ڡ�
	  	//����ͼ��ĸ��׾ص�����
	double M_00=0.0,M_01=0.0,M_10=0.0,M_11=0.0,M_20=0.0,M_02=0.0;//P+Q�׾�
    double U_00=0.0,U_11=0.0,U_20=0.0,U_02=0.0;//P+Q�����ľ�
	double m_00,n_00;//��������
	double u_00,u_11,u_20,u_02;//��һ����P+Q�����ľ�
 	///���㷶��ͼ�ĸ��׾�
	for(int l=0; l<dataheigth; l++)
		for(int k=0; k<datawidth; k++)
		{ 
		  M_00+=*(pdata + l*datawidth + k);
		  M_01+=*(pdata + l*datawidth + k)*l;
          M_10+=*(pdata + l*datawidth + k)*k;	
		}
	//�������� 
		m_00=M_10/M_00;//������
		n_00=M_01/M_00;//������
	    U_00=M_00;
	for(j=0; j<dataheigth; j++)
		for(i=0; i<datawidth; i++)
	   {
		 U_02+=(j-n_00)*(j-n_00)*(*(pdata + j*datawidth + i));
		 U_20+=(i-m_00)*(i-m_00)*(*(pdata + j*datawidth + i));
		 U_11+=(i-m_00)*(j-n_00)*(*(pdata + j*datawidth + i));
	   }
		u_00=U_00;
		u_02=U_02/pow(u_00,2.0);
		u_11=U_11/pow(u_00,2.0);
		u_20=U_20/pow(u_00,2.0);
	    ///���ײ���ر���
	  	pdFeature[5]=(pow((u_20-u_02),2.0)+4*u_11*u_11);  ////���� 
		///һ�ײ���ر���
		pdFeature[6]=(u_20+u_02);
	return true;
}

///����2:���������ɫ���������������ľ�
//����ߣ�dataheigth��datawidth�׵�ַΪ*pdata������ʸ�����ڽṹ���У�charactervq
//characterfirst:Ϊ����ʸ���ṹ��Ĵ���ĵ�һ���ı�ţ�characternumber:���㷨��ȡ�����ĸ���
///���㷨��,characternumber�������3
bool CFeatureExtractMethod::CharacterVqDistillMethod_2_3(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int iFeatureNumber)
{
	if (iFeatureNumber!=3) 
	{
		MessageBox(NULL,"CharacterDistill Number error","error!",MB_OK);
		return false;
	}
////add your word here
//////////////////////////////////////////////////////////////////////////
	////////����1��///���ؾ�ֵ
	int width,height;           //�߿�
	long int length=dataheigth*datawidth;
	int i;			///����
	double M1=0,M2=0,M3=0;         ///���׾�
	double *pihistogram=new double[256];
	//
	for(i=0;i<256;i++)
	{
		pihistogram[i]=0;
	}
	for(height=0;height<dataheigth;height++)  ///ͳ��ֱ��ͼ
		for(width=0;width<datawidth;width++)
			pihistogram[(unsigned char)(*(pdata+height*datawidth+width))]=pihistogram[(unsigned char)(*(pdata+height*datawidth+width))]+1;
	for(i=0;i<256;i++)
	{
		pihistogram[i]=pihistogram[i]/length;  //��һ��
		M1=M1+pihistogram[i]*i;   
	}
			
	for(i=0;i<256;i++)     ///ֱ��ͼ����
		M2=M2+pow(pihistogram[i]-1/256.0,2);
	for(i=0;i<256;i++)
		M3=M3+pow( pihistogram[i]-1/256.0,3);
	M3=pow(fabs(M3),double(1.0/3.0));
	pdFeature[0]=M1;
	pdFeature[1]=M2;
	pdFeature[2]=M3;
//////////////////////////////////////////////////////////////////////////
///end of ����
///delete the memory
	delete[]pihistogram;
	return true;
}
///��ȡ���������׾�
bool CFeatureExtractMethod::CharacterVqDistillMethod_3_1(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int iFeatureNumber)
{
	if (iFeatureNumber!=1) 
	{
		MessageBox(NULL,"CharacterDistill Number error","error!",MB_OK);
		return false;
	}
////add your word here
//////////////////////////////////////////////////////////////////////////
	double M_00=0.0,M_01=0.0,M_10=0.0,M_12=0.0,M_30=0.0,M_03=0.0;//P+Q�׾�
    double U_00=0.0,U_21=0,U_12=0.0,U_30=0.0,U_03=0.0;//P+Q�����ľ�
	double m_00,n_00;//��������
	double u_00,u_12,u_21,u_30,u_03;//��һ����P+Q�����ľ�
	///���㷶��ͼ�ĸ��׾�
 unsigned 	 char * pBits = pdata;
	for(int l=0; l<dataheigth; l++)
		for(int k=0; k<datawidth; k++)
		{ 
		  M_00+=*(pBits + l*datawidth + k);
		  M_01+=*(pBits + l*datawidth + k)*l;
          M_10+=*(pBits + l*datawidth + k)*k;	
		}
	//�������� 
		m_00=M_10/M_00;//������
		n_00=M_01/M_00;//������
	    U_00=M_00;
	for(int j=0; j<dataheigth; j++)
	   for(int i=0; i<datawidth; i++)
	   {
		    
			U_12+=(i-m_00)*(j-n_00)*(j-n_00)*(*(pBits + j*datawidth + i));
			U_21+=(i-m_00)*(i-m_00)*(j-n_00)*(*(pBits + j*datawidth + i));
			U_30+=(i-m_00)*(i-m_00)*(i-m_00)*(*(pBits + j*datawidth + i));
			U_03+=(j-n_00)*(j-n_00)*(j-n_00)*(*(pBits + j*datawidth + i));
     	    
	   }
	    u_00=U_00;
		u_12=U_12/pow(u_00,2.5);
		u_21=U_21/pow(u_00,2.5);
		u_03=U_03/pow(u_00,2.5);
		u_30=U_30/pow(u_00,2.5);
	pdFeature[0]=pow((u_30-3*u_12),2.0)+pow((3*u_21-u_03),2.0);
	//end
	return true;
}