// VqRetrieveData.h: interface for the VqRetrieveData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VQRETRIEVEDATA_H__CCBEBD8C_F116_4F9A_BD53_68831A32F693__INCLUDED_)
#define AFX_VQRETRIEVEDATA_H__CCBEBD8C_F116_4F9A_BD53_68831A32F693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAX_FILE_NAME 255      //����ļ���
#define  MAX_CHARACTER 100      ///ʸ���������
typedef struct tagCHARACTERVQ
 {
        char m_sFileName[MAX_FILE_NAME];  ///�ļ���
        double m_dFileStandCharacter[MAX_CHARACTER]; //��һ��ʸ��
		double m_dAverage;                          ///��һ��ʸ���ľ�ֵ
		double m_dFileOriginalCharacter[MAX_CHARACTER]; //ԭʼʸ��
        WORD m_uBitCount;///ͼ���λ��
		int m_iImageWidth;        //ͼ��ĸ�
		int m_iImageHeigth;    ////ͼ��Ŀ�
  } CHARACTERVQ, FAR *LPCHARACTERVQ, *PCHARACTERVQ;

class VqRetrieveData  
{
public:
	bool RetrieveMethod(CHARACTERVQ KeyBmpCharacterVq,int i);
//ʸ������������1
///ֱ�ӵļ���ʸ������ͼ���ʸ�����м���
///pCharacterVqͼ���ʸ���ṹ��ָ�룬iCurrentCharacter:����ʸ����������
//iRetrieveBmpNumberͼ���ͼ����Ŀ�� KeybmpCharactervq :�ؼ�ͼ��Ľṹ
//pOutCharactervq������ṹ���ͷָ�룬maxOutNumber���ͼ��������Ŀ��
//pDistance����ͼ��͹ؼ�ͼ��ľ��������ͷָ�룬RetrieveTime����ʱ��
	bool RetrieveKeyVqMethod1(CHARACTERVQ *pCharacterVq,int iCurrentCharacter,long int  iRetrieveBmpNumber,CHARACTERVQ KeybmpCharactervq,CHARACTERVQ*pOutCharactervq,unsigned char  maxOutNumber,double *pOutDistance,CString RetrieveTime);
	CHARACTERVQ GetRetrieveDisCharacterVq(unsigned char number);/////��ü������numberͼ��Ľṹ��
//	CHARACTERVQ GetRetrieveDisCharacterVq(unsigned char number);/////��ü������numberͼ��Ľṹ��
	CString GetRetrieveTime();     ///��ü���ʱ��
	CString GetRetrieveDistance(int number);//��ü������numberͼ����ؼ�ͼ�ľ���
	CString GetBmpDisplayFileName(unsigned char number);////��ü������numberͼ����ļ���
	unsigned char GetRetrieveDisplayBmpNumber();  //��ü���ͼ�������
	BOOL IsMemoryEnough(); ///�ж��ڴ��Ƿ��㹻������ڴ治�㣬�͵���DestroyMemory()ɾ���ڴ棬
	CString GetPathName(); ///����ļ����·����
	bool DestroyMemory();     ///ɾ���ڴ�
///����ͼ��BmpFilePathName��������������CharacterVq
	bool CharacterBmp(CString BmpFilePathName,CHARACTERVQ *CharacterVq);
///�ж�filePathName�ļ��Ƿ��ѡ
	bool ChooseBmp(CString filePathName);         //�Ƿ��ѡ
	VqRetrieveData(CString sPath);   ///���캯��
	virtual ~VqRetrieveData();//��������
private:
	
////��׼��ʸ�����ݣ��õ�ԭʼʸ���ı�׼�������ͱ�׼��������ݣ��Լ���ֵ
	bool StandCharacter(CHARACTERVQ *charactervq,long int numberbmp,int characternumber,double *pstandequvarible,double *pstandaverage);
//����ߣ�dataheigth��datawidth�׵�ַΪ*pdata������ʸ�����ڽṹ���У�charactervq
	bool CharacterVq(unsigned char *pdata,CHARACTERVQ *charactervq,int datawidth,int dataheigth);
//��8λͼ�����ɫ��ȡ������p8data:ͼ���������׵�ַ��palttledata����ɫ���׵�ַ��palttlenumber��ɫ��ĵ�������widthͼ��Ŀ�height��ͼ��ĸߣ�poutdata�����ͼ�����ݵ��׵�ַ
	bool Transform8(unsigned char *p8data,unsigned char *poutdata,RGBQUAD *palttledata,int palttlenumber,int  width,int height);
//��24λͼ�����ɫ��ȡ������p24data:ͼ���������׵�ַ��widthͼ��Ŀ�,height��ͼ��ĸߣ�poutdata�����ͼ�����ݵ��׵�ַ
	void Transform24(unsigned char *p24data,unsigned char *poutdata,int  width,int height);
//��ȡ�ļ���sPath�����е�ͼ�������
	bool CharacterDistill(CString sPath);  ///����sPath�ļ�����ͼ���ļ��������������ļ���
///��ȡʸ�������ļ�
	bool ReadCharacterFile(CString sPath);   //������ʸ�������ļ�
////�����ļ���sPath���������ļ��е�ͼ�����Ŀ
	long int ChooseBmpValueable(CString sPath);     ///ѡ��ͼ�����Ŀ
	CString m_sPath;  //�ļ����·����
	bool m_bMemoryEnough;            ///�����ڴ��Ƿ�ɹ��ı�־
	int m_iCurrentCharacterNumber; ///��ǰ������ʸ��������
	long int m_iCurrentFileNumber;         ///��ǰ���ļ��ܵ���Ŀ
	unsigned char m_uColorCharacterNumber;        //��ɫ��������Ŀ
	unsigned char m_utextureCharacterNumber;        //������������Ŀ
	unsigned char m_ufigureCharacterNumber;        //��״��������Ŀ
	double *m_pStandEquVarible;                //��׼��������ָ��
	HGLOBAL m_hStandEquVaible;             //��׼�������ľ��
	double *m_pStandAveVarible;                //��׼��������ָ��
	HGLOBAL m_hStandAveVaible;             //��׼�������ľ��
	CHARACTERVQ *m_pCharacterVq;                //����ʸ��������ָ��
	HGLOBAL m_hCharacterVq;             //����ʸ���ľ��
	int m_iAddFileNumber;               ///��ӵ��ļ���Ŀ
	double m_dPercent;                 //û�б�׼����ͼ��ռ��ͼ��İٷֱ�
	bool m_bCharacterDistill;           ///������ȡ�Ƿ�ɹ�
	CString m_sDisplayFile[16];            ///��ʾ��16��ͼ����ļ���
	unsigned char m_uDisplayNumber;           //��ʾͼ�����Ŀ0-16
	double m_dDisplayFileDistance[16];         //��ʾͼ��͹ؼ�ͼ��ľ���
	CHARACTERVQ m_cCharacterVq[16];                //�������16���ṹ��
	long int m_ibmpvarible;       ///ѡ��ĵ�ͼ����Ŀ,���ڼ�����������ͼ���Ƿ��뿪���ڴ����
	bool m_bRetrieve;  ///�Ƿ�����ɹ����Ƿ񾭹�������ÿ�μ�����������������ͼ�����ͼ�������ʾ��ͼ����Ŀ
	CString m_sRetrieveTime;         //����ʱ��

	

};


#endif // !defined(AFX_VQRETRIEVEDATA_H__CCBEBD8C_F116_4F9A_BD53_68831A32F693__INCLUDED_)
