//write file //knowledge/SemanticAnnotion.a 
//annotion 
#include "stdafx.h"
#include "SBIRSystem.h"
#include "RetrievalControl.h"
#include <VECTOR>
#include "math.h"
#define IMAGE_ASSOCIATION_COFF 0.5
#define ANNOTION_ASSOCATION_COFF 0.5
/************************************************************************/
/* we take this file out of the RetrievalControl.cpp    
 * for the reason that it is too large                                                                 */
/************************************************************************/
BOOL CRetrievalControl::WriteAnnotionFile(CString DatabasePathName)  //imagebase path
{
	
	delete[] stSemanticAnnotion;
	stSemanticAnnotion=NULL;
	stSemanticAnnotion=new SEMANTICANNOTION[NUMBERANNOTION];
		//write the file //knowledge//semanticannotion.a
	CFile cSemanticAnnotionFile;
	CString sSemanticAnnotionFullPathName=DatabasePathName+"\\knowledge\\";
	int iNumberAnnotion=0;  //compare the number with the NUMBERANNOTION
	//get the knowledge file path
	sSemanticAnnotionFullPathName=sSemanticAnnotionFullPathName+"SemanticAnnotion.a";
	//remove the file
	remove(sSemanticAnnotionFullPathName);
	if(cSemanticAnnotionFile.Open(sSemanticAnnotionFullPathName,CFile::modeCreate|CFile::modeReadWrite)==FALSE)
	{		
		return false;
	}
	//begin to write
	//��,����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��,����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1130; 
	iIDLabed[iNumberIDLabed++]=1132; 
	iIDLabed[iNumberIDLabed++]=1139; 
	iIDLabed[iNumberIDLabed++]=1160; 
	iIDLabed[iNumberIDLabed++]=616; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label  


	//������ľ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="������ľ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1136; 
	iIDLabed[iNumberIDLabed++]=1137; 
	iIDLabed[iNumberIDLabed++]=1145; 
	iIDLabed[iNumberIDLabed++]=1175; 
	iIDLabed[iNumberIDLabed++]=759; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label  

	//·����·
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="·����·";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1013; 
	iIDLabed[iNumberIDLabed++]=1011; 
	iIDLabed[iNumberIDLabed++]=1067; 
	iIDLabed[iNumberIDLabed++]=1041; 
	iIDLabed[iNumberIDLabed++]=2507; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//��ƺ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��ƺ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1143; 
	iIDLabed[iNumberIDLabed++]=1146; 
	iIDLabed[iNumberIDLabed++]=1151; 
	iIDLabed[iNumberIDLabed++]=1159; 
	iIDLabed[iNumberIDLabed++]=1011; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//��Ҷ������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��Ҷ������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1008; 
	iIDLabed[iNumberIDLabed++]=1026; 
	iIDLabed[iNumberIDLabed++]=1030; 
	iIDLabed[iNumberIDLabed++]=1087; 
	iIDLabed[iNumberIDLabed++]=1106; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//���ӣ�סլ����ͥ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="���ӣ�סլ����ͥ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1012; 
	iIDLabed[iNumberIDLabed++]=1049; 
	iIDLabed[iNumberIDLabed++]=2891; 
	iIDLabed[iNumberIDLabed++]=1146; 
	iIDLabed[iNumberIDLabed++]=2853; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//���ڣ�����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="���ڣ�����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1754; 
	iIDLabed[iNumberIDLabed++]=1756; 
	iIDLabed[iNumberIDLabed++]=3121; 
	iIDLabed[iNumberIDLabed++]=3334; 
	iIDLabed[iNumberIDLabed++]=1755; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//ɽ��ɽ��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ɽ��ɽ��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1752; 
	iIDLabed[iNumberIDLabed++]=1912; 
	iIDLabed[iNumberIDLabed++]=1780; 
	iIDLabed[iNumberIDLabed++]=1850; 
	iIDLabed[iNumberIDLabed++]=2192; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//�ƣ����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ƣ����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2069; 
	iIDLabed[iNumberIDLabed++]=2099; 
	iIDLabed[iNumberIDLabed++]=2207; 
	iIDLabed[iNumberIDLabed++]=2574; 
	iIDLabed[iNumberIDLabed++]=3008; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2989; 
	iIDLabed[iNumberIDLabed++]=2996; 
	iIDLabed[iNumberIDLabed++]=1356; 
	iIDLabed[iNumberIDLabed++]=1504; 
	iIDLabed[iNumberIDLabed++]=3030; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//ѩ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ѩ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1299; 
	iIDLabed[iNumberIDLabed++]=1236; 
	iIDLabed[iNumberIDLabed++]=1208; 
	iIDLabed[iNumberIDLabed++]=3055; 
	iIDLabed[iNumberIDLabed++]=3030; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//ˮ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ˮ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1298; 
	iIDLabed[iNumberIDLabed++]=1309; 
	iIDLabed[iNumberIDLabed++]=1351; 
	iIDLabed[iNumberIDLabed++]=1436; 
	iIDLabed[iNumberIDLabed++]=1671; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label



	//��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2037; 
	iIDLabed[iNumberIDLabed++]=2105; 
	iIDLabed[iNumberIDLabed++]=2152; 
	iIDLabed[iNumberIDLabed++]=2535; 
	iIDLabed[iNumberIDLabed++]=2932; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label	

	//�죬���
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�죬���";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2915; 
	iIDLabed[iNumberIDLabed++]=3010; 
	iIDLabed[iNumberIDLabed++]=1272; 
	iIDLabed[iNumberIDLabed++]=1631; 
	iIDLabed[iNumberIDLabed++]=1274; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label		
	//ˮ���ӣ���
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ˮ���ӣ���";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1277; 
	iIDLabed[iNumberIDLabed++]=2011; 
	iIDLabed[iNumberIDLabed++]=2097; 
	iIDLabed[iNumberIDLabed++]=2244; 
	iIDLabed[iNumberIDLabed++]=1279; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label	

	//��ɽ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��ɽ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1319; 
	iIDLabed[iNumberIDLabed++]=1334; 
	iIDLabed[iNumberIDLabed++]=1335; 
	iIDLabed[iNumberIDLabed++]=1324; 
	iIDLabed[iNumberIDLabed++]=1325; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//Ư��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="Ư��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1388; 
	iIDLabed[iNumberIDLabed++]=1395; 
	iIDLabed[iNumberIDLabed++]=1389; 
	iIDLabed[iNumberIDLabed++]=1390; 
	iIDLabed[iNumberIDLabed++]=1394; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ˮ̡, ˮ̡Ƥ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ˮ̡, ˮ̡Ƥ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1397; 
	iIDLabed[iNumberIDLabed++]=1398; 
	iIDLabed[iNumberIDLabed++]=1399; 
	iIDLabed[iNumberIDLabed++]=1401; 
	iIDLabed[iNumberIDLabed++]=1410; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��ʯ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��ʯ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1426; 
	iIDLabed[iNumberIDLabed++]=1428; 
	iIDLabed[iNumberIDLabed++]=1458; 
	iIDLabed[iNumberIDLabed++]=1476; 
	iIDLabed[iNumberIDLabed++]=2164; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2153; 
	iIDLabed[iNumberIDLabed++]=1490; 
	iIDLabed[iNumberIDLabed++]=2428; 
	iIDLabed[iNumberIDLabed++]=1612; 
	iIDLabed[iNumberIDLabed++]=2657; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ֲ���ֲ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ֲ���ֲ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1720; 
	iIDLabed[iNumberIDLabed++]=1748; 
	iIDLabed[iNumberIDLabed++]=2000; 
	iIDLabed[iNumberIDLabed++]=2362; 
	iIDLabed[iNumberIDLabed++]=3015; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ѩɽ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ѩɽ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=839; 
	iIDLabed[iNumberIDLabed++]=3038; 
	iIDLabed[iNumberIDLabed++]=809; 
	iIDLabed[iNumberIDLabed++]=1243; 
	iIDLabed[iNumberIDLabed++]=2332; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��԰
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��԰";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1088; 
	iIDLabed[iNumberIDLabed++]=1083; 
	iIDLabed[iNumberIDLabed++]=1096; 
	iIDLabed[iNumberIDLabed++]=1095; 
	iIDLabed[iNumberIDLabed++]=1099; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2456; 
	iIDLabed[iNumberIDLabed++]=2744; 
	iIDLabed[iNumberIDLabed++]=3191; 
	iIDLabed[iNumberIDLabed++]=3334; 
	iIDLabed[iNumberIDLabed++]=1063; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//�ɻ�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ɻ�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1165; 
	iIDLabed[iNumberIDLabed++]=1171; 
	iIDLabed[iNumberIDLabed++]=2702; 
	iIDLabed[iNumberIDLabed++]=2746; 
	iIDLabed[iNumberIDLabed++]=2868; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//���㣬����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="���㣬����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2881; 
	iIDLabed[iNumberIDLabed++]=2892; 
	iIDLabed[iNumberIDLabed++]=2456; 
	iIDLabed[iNumberIDLabed++]=2723; 
	iIDLabed[iNumberIDLabed++]=2873; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//���䣬��Ӱ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="���䣬��Ӱ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2873; 
	iIDLabed[iNumberIDLabed++]=1670; 
	iIDLabed[iNumberIDLabed++]=2900; 
	iIDLabed[iNumberIDLabed++]=2910; 
	iIDLabed[iNumberIDLabed++]=1256; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����С����ͧ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����С����ͧ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2326; 
	iIDLabed[iNumberIDLabed++]=2339; 
	iIDLabed[iNumberIDLabed++]=3279; 
	iIDLabed[iNumberIDLabed++]=2585; 
	iIDLabed[iNumberIDLabed++]=1258; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//���ۣ��ۿ�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="���ۣ��ۿ�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1287; 
	iIDLabed[iNumberIDLabed++]=2332; 
	iIDLabed[iNumberIDLabed++]=2804; 
	iIDLabed[iNumberIDLabed++]=2897; 
	iIDLabed[iNumberIDLabed++]=1288; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ĸţ������ĸ��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ĸţ������ĸ��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1219; 
	iIDLabed[iNumberIDLabed++]=1222; 
	iIDLabed[iNumberIDLabed++]=1215; 
	iIDLabed[iNumberIDLabed++]=1221; 
	iIDLabed[iNumberIDLabed++]=1216; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1318; 
	iIDLabed[iNumberIDLabed++]=1340; 
	iIDLabed[iNumberIDLabed++]=1518; 
	iIDLabed[iNumberIDLabed++]=3019; 
	iIDLabed[iNumberIDLabed++]=1228; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//Ѽ��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="Ѽ��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1196; 
	iIDLabed[iNumberIDLabed++]=1198; 
	iIDLabed[iNumberIDLabed++]=1194; 
	iIDLabed[iNumberIDLabed++]=1195; 
	iIDLabed[iNumberIDLabed++]=1199; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//������ˮ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="������ˮ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1753; 
	iIDLabed[iNumberIDLabed++]=1784; 
	iIDLabed[iNumberIDLabed++]=1816; 
	iIDLabed[iNumberIDLabed++]=3054; 
	iIDLabed[iNumberIDLabed++]=1251; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//�ɽ�������ˮ��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ɽ�������ˮ��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1343; 
	iIDLabed[iNumberIDLabed++]=1355; 
	iIDLabed[iNumberIDLabed++]=1438; 
	iIDLabed[iNumberIDLabed++]=2738; 
	iIDLabed[iNumberIDLabed++]=2922; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2296; 
	iIDLabed[iNumberIDLabed++]=2927; 
	iIDLabed[iNumberIDLabed++]=1943; 
	iIDLabed[iNumberIDLabed++]=1164; 
	iIDLabed[iNumberIDLabed++]=2022; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//�ڻ�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ڻ�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2042; 
	iIDLabed[iNumberIDLabed++]=2049; 
	iIDLabed[iNumberIDLabed++]=2045; 
	iIDLabed[iNumberIDLabed++]=2048; 
	iIDLabed[iNumberIDLabed++]=2044; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//��¹������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��¹������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2077; 
	iIDLabed[iNumberIDLabed++]=2064; 
	iIDLabed[iNumberIDLabed++]=2419; 
	iIDLabed[iNumberIDLabed++]=2057; 
	iIDLabed[iNumberIDLabed++]=2058; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2063; 
	iIDLabed[iNumberIDLabed++]=2121; 
	iIDLabed[iNumberIDLabed++]=2139; 
	iIDLabed[iNumberIDLabed++]=1307; 
	iIDLabed[iNumberIDLabed++]=2052; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��̲������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��̲������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2587; 
	iIDLabed[iNumberIDLabed++]=2839; 
	iIDLabed[iNumberIDLabed++]=2580; 
	iIDLabed[iNumberIDLabed++]=135; 
	iIDLabed[iNumberIDLabed++]=148; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//���󣬴�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="���󣬴�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2600; 
	iIDLabed[iNumberIDLabed++]=2621; 
	iIDLabed[iNumberIDLabed++]=2666; 
	iIDLabed[iNumberIDLabed++]=3071; 
	iIDLabed[iNumberIDLabed++]=3269; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//�ٲ�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ٲ�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1681; 
	iIDLabed[iNumberIDLabed++]=1702; 
	iIDLabed[iNumberIDLabed++]=2307; 
	iIDLabed[iNumberIDLabed++]=3056; 
	iIDLabed[iNumberIDLabed++]=1430; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ͺͷӥ������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ͺͷӥ������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1457; 
	iIDLabed[iNumberIDLabed++]=1472; 
	iIDLabed[iNumberIDLabed++]=1424; 
	iIDLabed[iNumberIDLabed++]=1425; 
	iIDLabed[iNumberIDLabed++]=1462; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1453; 
	iIDLabed[iNumberIDLabed++]=1446; 
	iIDLabed[iNumberIDLabed++]=1447; 
	iIDLabed[iNumberIDLabed++]=1448; 
	iIDLabed[iNumberIDLabed++]=1449; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����,����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����,����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1542; 
	iIDLabed[iNumberIDLabed++]=1376; 
	iIDLabed[iNumberIDLabed++]=1526; 
	iIDLabed[iNumberIDLabed++]=1379; 
	iIDLabed[iNumberIDLabed++]=1530; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//½��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="½��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2120; 
	iIDLabed[iNumberIDLabed++]=2125; 
	iIDLabed[iNumberIDLabed++]=2144; 
	iIDLabed[iNumberIDLabed++]=2190; 
	iIDLabed[iNumberIDLabed++]=2140; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//�ܣ�����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ܣ�����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2126; 
	iIDLabed[iNumberIDLabed++]=2143; 
	iIDLabed[iNumberIDLabed++]=2171; 
	iIDLabed[iNumberIDLabed++]=2129; 
	iIDLabed[iNumberIDLabed++]=2141; 
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2179; 
	iIDLabed[iNumberIDLabed++]=2184; 
	iIDLabed[iNumberIDLabed++]=3355; 
	iIDLabed[iNumberIDLabed++]=2182; 
	iIDLabed[iNumberIDLabed++]=3357; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ϣ������ϣ��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ϣ������ϣ��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3269; 
	iIDLabed[iNumberIDLabed++]=3288; 
	iIDLabed[iNumberIDLabed++]=3294; 
	iIDLabed[iNumberIDLabed++]=3312; 
	iIDLabed[iNumberIDLabed++]=3298;	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3325; 
	iIDLabed[iNumberIDLabed++]=3085; 
	iIDLabed[iNumberIDLabed++]=3122; 
	iIDLabed[iNumberIDLabed++]=239; 
	iIDLabed[iNumberIDLabed++]=278; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3131; 
	iIDLabed[iNumberIDLabed++]=3293; 
	iIDLabed[iNumberIDLabed++]=3111; 
	iIDLabed[iNumberIDLabed++]=3140; 
	iIDLabed[iNumberIDLabed++]=3294; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//����, �ż�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����, �ż�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3287; 
	iIDLabed[iNumberIDLabed++]=3296; 
	iIDLabed[iNumberIDLabed++]=3289; 
	iIDLabed[iNumberIDLabed++]=3299; 
	iIDLabed[iNumberIDLabed++]=288; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//è������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="è������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3322; 
	iIDLabed[iNumberIDLabed++]=3337; 
	iIDLabed[iNumberIDLabed++]=3332; 
	iIDLabed[iNumberIDLabed++]=3326; 
	iIDLabed[iNumberIDLabed++]=3329; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3350; 
	iIDLabed[iNumberIDLabed++]=3351; 
	iIDLabed[iNumberIDLabed++]=3287; 
	iIDLabed[iNumberIDLabed++]=3304; 
	iIDLabed[iNumberIDLabed++]=3321; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��, ��, ���, ����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��, ��, ���, ����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3289; 
	iIDLabed[iNumberIDLabed++]=3302; 
	iIDLabed[iNumberIDLabed++]=206; 
	iIDLabed[iNumberIDLabed++]=231; 
	iIDLabed[iNumberIDLabed++]=244; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����̻�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����̻�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3192; 
	iIDLabed[iNumberIDLabed++]=3239; 
	iIDLabed[iNumberIDLabed++]=3259; 
	iIDLabed[iNumberIDLabed++]=3196; 
	iIDLabed[iNumberIDLabed++]=3227; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//Ϧ����̫��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="Ϧ����̫��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3080; 
	iIDLabed[iNumberIDLabed++]=3113; 
	iIDLabed[iNumberIDLabed++]=3062; 
	iIDLabed[iNumberIDLabed++]=3080; 
	iIDLabed[iNumberIDLabed++]=3100; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��, �Ǳ�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��, �Ǳ�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3101; 
	iIDLabed[iNumberIDLabed++]=3098; 
	iIDLabed[iNumberIDLabed++]=3105; 
	iIDLabed[iNumberIDLabed++]=3103; 
	iIDLabed[iNumberIDLabed++]=3104; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2762; 
	iIDLabed[iNumberIDLabed++]=2766; 
	iIDLabed[iNumberIDLabed++]=2767; 
	iIDLabed[iNumberIDLabed++]=2722; 
	iIDLabed[iNumberIDLabed++]=2729; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//��ʨ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��ʨ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1388; 
	iIDLabed[iNumberIDLabed++]=1390; 
	iIDLabed[iNumberIDLabed++]=1392; 
	iIDLabed[iNumberIDLabed++]=1393; 
	iIDLabed[iNumberIDLabed++]=1395; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//�ܵ�
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�ܵ�";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2012; 
	iIDLabed[iNumberIDLabed++]=2013; 
	iIDLabed[iNumberIDLabed++]=2014; 
	iIDLabed[iNumberIDLabed++]=2015; 
//	iIDLabed[iNumberIDLabed++]=2729; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3131; 
	iIDLabed[iNumberIDLabed++]=3140; 
	iIDLabed[iNumberIDLabed++]=1754; 
	iIDLabed[iNumberIDLabed++]=3113; 
	iIDLabed[iNumberIDLabed++]=3135; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����, ����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����, ����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3308; 
	iIDLabed[iNumberIDLabed++]=3309; 
	iIDLabed[iNumberIDLabed++]=3310; 
	iIDLabed[iNumberIDLabed++]=3311; 
	iIDLabed[iNumberIDLabed++]=3312; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//�����ˣ����޽���
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="�����ˣ����޽���";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=16; 
	iIDLabed[iNumberIDLabed++]=46; 
	iIDLabed[iNumberIDLabed++]=59; 
	iIDLabed[iNumberIDLabed++]=72; 
	iIDLabed[iNumberIDLabed++]=81; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��̲���羰������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="��̲���羰������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=129; 
	iIDLabed[iNumberIDLabed++]=146; 
	iIDLabed[iNumberIDLabed++]=119; 
	iIDLabed[iNumberIDLabed++]=169; 
	iIDLabed[iNumberIDLabed++]=187; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//������
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=308; 
	iIDLabed[iNumberIDLabed++]=316; 
	iIDLabed[iNumberIDLabed++]=359; 
	iIDLabed[iNumberIDLabed++]=389; 
	iIDLabed[iNumberIDLabed++]=344; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=459; 
	iIDLabed[iNumberIDLabed++]=468; 
	iIDLabed[iNumberIDLabed++]=418; 
	iIDLabed[iNumberIDLabed++]=455; 
	iIDLabed[iNumberIDLabed++]=479; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="����";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=504; 
	iIDLabed[iNumberIDLabed++]=521; 
	iIDLabed[iNumberIDLabed++]=536; 
	iIDLabed[iNumberIDLabed++]=579; 
	iIDLabed[iNumberIDLabed++]=582; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//õ�壬��
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="õ�壬��";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=602; 
	iIDLabed[iNumberIDLabed++]=613; 
	iIDLabed[iNumberIDLabed++]=622; 
	iIDLabed[iNumberIDLabed++]=645; 
	iIDLabed[iNumberIDLabed++]=689; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//��,����
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="������";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=713; 
	iIDLabed[iNumberIDLabed++]=732; 
	iIDLabed[iNumberIDLabed++]=789; 
	iIDLabed[iNumberIDLabed++]=742; 
	iIDLabed[iNumberIDLabed++]=769; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//ʳ���ʳ
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="ʳ���ʳ";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=901; 
	iIDLabed[iNumberIDLabed++]=945; 
	iIDLabed[iNumberIDLabed++]=926; 
	iIDLabed[iNumberIDLabed++]=987; 
	iIDLabed[iNumberIDLabed++]=962; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label		

	//error
	if (iNumberAnnotion!=NUMBERANNOTION) 
	{
		MessageBox(NULL,"Error of the Annotion!","System informaiont",MB_OK);	
		return false;
	}
	cSemanticAnnotionFile.Close();	
	//reopen it 
	if(cSemanticAnnotionFile.Open(sSemanticAnnotionFullPathName,CFile::modeReadWrite)==FALSE) return false;
	
	if(cSemanticAnnotionFile.Read(stSemanticAnnotion,NUMBERANNOTION*sizeof(SEMANTICANNOTION))!=NUMBERANNOTION*sizeof(SEMANTICANNOTION)) return false;
	
	cSemanticAnnotionFile.Close();
	return true;
}