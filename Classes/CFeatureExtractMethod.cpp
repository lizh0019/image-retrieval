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

//计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：charactervq
//characterfirst:为特征矢量结构体的存入的第一个的编号，characternumber:该算法提取参数的个数
///本算法中,characternumber必须等于7
bool CFeatureExtractMethod::CharacterVqDistillMethod_1_7(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int characternumber)
{
	if (characternumber!=7) 
	{
		MessageBox(NULL,"CharacterDistill Number error","error!",MB_OK);
		return false;
	}
////add your word here
/////注意：计算一个特征量，iCharacterNumbercheck＋＋；
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
					regionnumberright=datawidth*dataheigth-regionnumberleft;///右计数器计算得出
					if (regionnumberright==0)  //排除异常
					{
						regionnumberright=1;
					}
						if (regionnumberleft==0)//排除异常
					{
						regionnumberleft=1;
					}
					regiondata2=(regiontotallleft/regionnumberleft+regiontotalright/regionnumberright)/2.0;////计算公式
					if((unsigned char)regiondata2==(unsigned char)regiondata1)///结束
						break;
					else 
						regiondata1=regiondata2;

		}
	pdFeature[0]=regiondata2/255.0; ///归一化
	
///参数2
	pdFeature[1]=(double)regionnumberleft/(regionnumberleft+regionnumberright);
////end of 颜色
	///颜色参数的个数

//////说明：参数3，4，5是纹理中的不变量，他们是在共生矩阵中提取的
////参数3:
///统计共生矩阵
	double (*texturematrix)[256]=new double[256][256];  ///共生矩阵x
	double (*texturematriy)[256]=new double[256][256];  ///共生矩阵x
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
	pdFeature[2]=(Con1+Con2)/2/255.0/255.0;             //提取反差变量
	pdFeature[3]=(Asm1+Asm2)/2;              ///提取能量变量
	pdFeature[4]=-(Ent1+Ent2)/2;              ///提取熵变量
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
		for(int k=0; k<datawidth; k++)
		{ 
		  M_00+=*(pdata + l*datawidth + k);
		  M_01+=*(pdata + l*datawidth + k)*l;
          M_10+=*(pdata + l*datawidth + k)*k;	
		}
	//重心坐标 
		m_00=M_10/M_00;//横坐标
		n_00=M_01/M_00;//纵坐标
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
	    ///二阶不变矩保存
	  	pdFeature[5]=(pow((u_20-u_02),2.0)+4*u_11*u_11);  ////保存 
		///一阶不变矩保存
		pdFeature[6]=(u_20+u_02);
	return true;
}

///方法2:计算基于颜色的三个的三个中心矩
//计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：charactervq
//characterfirst:为特征矢量结构体的存入的第一个的编号，characternumber:该算法提取参数的个数
///本算法中,characternumber必须等于3
bool CFeatureExtractMethod::CharacterVqDistillMethod_2_3(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int iFeatureNumber)
{
	if (iFeatureNumber!=3) 
	{
		MessageBox(NULL,"CharacterDistill Number error","error!",MB_OK);
		return false;
	}
////add your word here
//////////////////////////////////////////////////////////////////////////
	////////参数1：///像素均值
	int width,height;           //高宽
	long int length=dataheigth*datawidth;
	int i;			///变量
	double M1=0,M2=0,M3=0;         ///三阶矩
	double *pihistogram=new double[256];
	//
	for(i=0;i<256;i++)
	{
		pihistogram[i]=0;
	}
	for(height=0;height<dataheigth;height++)  ///统计直方图
		for(width=0;width<datawidth;width++)
			pihistogram[(unsigned char)(*(pdata+height*datawidth+width))]=pihistogram[(unsigned char)(*(pdata+height*datawidth+width))]+1;
	for(i=0;i<256;i++)
	{
		pihistogram[i]=pihistogram[i]/length;  //归一化
		M1=M1+pihistogram[i]*i;   
	}
			
	for(i=0;i<256;i++)     ///直方图方差
		M2=M2+pow(pihistogram[i]-1/256.0,2);
	for(i=0;i<256;i++)
		M3=M3+pow( pihistogram[i]-1/256.0,3);
	M3=pow(fabs(M3),double(1.0/3.0));
	pdFeature[0]=M1;
	pdFeature[1]=M2;
	pdFeature[2]=M3;
//////////////////////////////////////////////////////////////////////////
///end of 计算
///delete the memory
	delete[]pihistogram;
	return true;
}
///提取参数，三阶矩
bool CFeatureExtractMethod::CharacterVqDistillMethod_3_1(unsigned char *pdata, int datawidth, int dataheigth, double *pdFeature, int iFeatureNumber)
{
	if (iFeatureNumber!=1) 
	{
		MessageBox(NULL,"CharacterDistill Number error","error!",MB_OK);
		return false;
	}
////add your word here
//////////////////////////////////////////////////////////////////////////
	double M_00=0.0,M_01=0.0,M_10=0.0,M_12=0.0,M_30=0.0,M_03=0.0;//P+Q阶矩
    double U_00=0.0,U_21=0,U_12=0.0,U_30=0.0,U_03=0.0;//P+Q阶中心矩
	double m_00,n_00;//重心坐标
	double u_00,u_12,u_21,u_30,u_03;//归一化的P+Q阶中心矩
	///计算范例图的各阶矩
 unsigned 	 char * pBits = pdata;
	for(int l=0; l<dataheigth; l++)
		for(int k=0; k<datawidth; k++)
		{ 
		  M_00+=*(pBits + l*datawidth + k);
		  M_01+=*(pBits + l*datawidth + k)*l;
          M_10+=*(pBits + l*datawidth + k)*k;	
		}
	//重心坐标 
		m_00=M_10/M_00;//横坐标
		n_00=M_01/M_00;//纵坐标
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