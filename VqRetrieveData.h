// VqRetrieveData.h: interface for the VqRetrieveData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VQRETRIEVEDATA_H__CCBEBD8C_F116_4F9A_BD53_68831A32F693__INCLUDED_)
#define AFX_VQRETRIEVEDATA_H__CCBEBD8C_F116_4F9A_BD53_68831A32F693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAX_FILE_NAME 255      //最常的文件名
#define  MAX_CHARACTER 100      ///矢量的最常长度
typedef struct tagCHARACTERVQ
 {
        char m_sFileName[MAX_FILE_NAME];  ///文件名
        double m_dFileStandCharacter[MAX_CHARACTER]; //归一化矢量
		double m_dAverage;                          ///归一化矢量的均值
		double m_dFileOriginalCharacter[MAX_CHARACTER]; //原始矢量
        WORD m_uBitCount;///图像的位数
		int m_iImageWidth;        //图像的高
		int m_iImageHeigth;    ////图像的宽
  } CHARACTERVQ, FAR *LPCHARACTERVQ, *PCHARACTERVQ;

class VqRetrieveData  
{
public:
	bool RetrieveMethod(CHARACTERVQ KeyBmpCharacterVq,int i);
//矢量检索，方法1
///直接的检索矢量，对图像的矢量进行检索
///pCharacterVq图像库矢量结构体指针，iCurrentCharacter:检索矢量的数量，
//iRetrieveBmpNumber图像库图像数目， KeybmpCharactervq :关键图像的结构
//pOutCharactervq：输出结构体的头指针，maxOutNumber输出图像的最多数目，
//pDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
	bool RetrieveKeyVqMethod1(CHARACTERVQ *pCharacterVq,int iCurrentCharacter,long int  iRetrieveBmpNumber,CHARACTERVQ KeybmpCharactervq,CHARACTERVQ*pOutCharactervq,unsigned char  maxOutNumber,double *pOutDistance,CString RetrieveTime);
	CHARACTERVQ GetRetrieveDisCharacterVq(unsigned char number);/////获得检索结果number图像的结构体
//	CHARACTERVQ GetRetrieveDisCharacterVq(unsigned char number);/////获得检索结果number图像的结构体
	CString GetRetrieveTime();     ///获得检索时间
	CString GetRetrieveDistance(int number);//获得检索结果number图像与关键图的距离
	CString GetBmpDisplayFileName(unsigned char number);////获得检索结果number图像的文件名
	unsigned char GetRetrieveDisplayBmpNumber();  //获得检索图像的数量
	BOOL IsMemoryEnough(); ///判断内存是否足够，如果内存不足，就调用DestroyMemory()删除内存，
	CString GetPathName(); ///获得文件库的路径名
	bool DestroyMemory();     ///删除内存
///计算图像BmpFilePathName的特征量，存在CharacterVq
	bool CharacterBmp(CString BmpFilePathName,CHARACTERVQ *CharacterVq);
///判断filePathName文件是否可选
	bool ChooseBmp(CString filePathName);         //是否可选
	VqRetrieveData(CString sPath);   ///构造函数
	virtual ~VqRetrieveData();//析构函数
private:
	
////标准化矢量数据，得到原始矢量的标准化参数和标准化后的数据，以及均值
	bool StandCharacter(CHARACTERVQ *charactervq,long int numberbmp,int characternumber,double *pstandequvarible,double *pstandaverage);
//计算高：dataheigth，datawidth首地址为*pdata的特征矢量存在结构体中：charactervq
	bool CharacterVq(unsigned char *pdata,CHARACTERVQ *charactervq,int datawidth,int dataheigth);
//将8位图像的颜色提取出来，p8data:图像数据区首地址，palttledata：颜色表首地址，palttlenumber颜色表的的数量，width图像的宽，height：图像的高，poutdata：输出图像数据的首地址
	bool Transform8(unsigned char *p8data,unsigned char *poutdata,RGBQUAD *palttledata,int palttlenumber,int  width,int height);
//将24位图像的颜色提取出来，p24data:图像数据区首地址，width图像的宽,height：图像的高，poutdata：输出图像数据的首地址
	void Transform24(unsigned char *p24data,unsigned char *poutdata,int  width,int height);
//提取文件夹sPath中所有的图像的特征
	bool CharacterDistill(CString sPath);  ///检索sPath文件夹中图像文件特征，包含子文件夹
///读取矢量数据文件
	bool ReadCharacterFile(CString sPath);   //读特征矢量数据文件
////计算文件夹sPath包括其子文件夹的图像的数目
	long int ChooseBmpValueable(CString sPath);     ///选择图像的数目
	CString m_sPath;  //文件库的路径名
	bool m_bMemoryEnough;            ///开辟内存是否成功的标志
	int m_iCurrentCharacterNumber; ///当前的特征矢量的数量
	long int m_iCurrentFileNumber;         ///当前的文件总的数目
	unsigned char m_uColorCharacterNumber;        //颜色特征的数目
	unsigned char m_utextureCharacterNumber;        //纹理特征的数目
	unsigned char m_ufigureCharacterNumber;        //形状的特征数目
	double *m_pStandEquVarible;                //标准化参数的指针
	HGLOBAL m_hStandEquVaible;             //标准化参数的句柄
	double *m_pStandAveVarible;                //标准化参数的指针
	HGLOBAL m_hStandAveVaible;             //标准化参数的句柄
	CHARACTERVQ *m_pCharacterVq;                //特征矢量参数的指针
	HGLOBAL m_hCharacterVq;             //特征矢量的句柄
	int m_iAddFileNumber;               ///添加的文件数目
	double m_dPercent;                 //没有标准化的图像占总图像的百分比
	bool m_bCharacterDistill;           ///特征提取是否成功
	CString m_sDisplayFile[16];            ///显示的16幅图像的文件名
	unsigned char m_uDisplayNumber;           //显示图像的数目0-16
	double m_dDisplayFileDistance[16];         //显示图像和关键图像的距离
	CHARACTERVQ m_cCharacterVq[16];                //检索结果16个结构体
	long int m_ibmpvarible;       ///选择的的图像数目,用于检验最后检索的图像是否与开辟内存相符
	bool m_bRetrieve;  ///是否检索成功或是否经过检索，每次检索，需给出检索结果图像名和检索可显示的图像数目
	CString m_sRetrieveTime;         //检索时间

	

};


#endif // !defined(AFX_VQRETRIEVEDATA_H__CCBEBD8C_F116_4F9A_BD53_68831A32F693__INCLUDED_)
