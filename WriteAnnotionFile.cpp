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
	//花,花丛
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="花,花丛";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1130; 
	iIDLabed[iNumberIDLabed++]=1132; 
	iIDLabed[iNumberIDLabed++]=1139; 
	iIDLabed[iNumberIDLabed++]=1160; 
	iIDLabed[iNumberIDLabed++]=616; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label  


	//树，树木
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="树，树木";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1136; 
	iIDLabed[iNumberIDLabed++]=1137; 
	iIDLabed[iNumberIDLabed++]=1145; 
	iIDLabed[iNumberIDLabed++]=1175; 
	iIDLabed[iNumberIDLabed++]=759; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label  

	//路，道路
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="路，道路";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1013; 
	iIDLabed[iNumberIDLabed++]=1011; 
	iIDLabed[iNumberIDLabed++]=1067; 
	iIDLabed[iNumberIDLabed++]=1041; 
	iIDLabed[iNumberIDLabed++]=2507; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//草坪
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="草坪";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1143; 
	iIDLabed[iNumberIDLabed++]=1146; 
	iIDLabed[iNumberIDLabed++]=1151; 
	iIDLabed[iNumberIDLabed++]=1159; 
	iIDLabed[iNumberIDLabed++]=1011; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//树叶，花瓣
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="树叶，花瓣";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1008; 
	iIDLabed[iNumberIDLabed++]=1026; 
	iIDLabed[iNumberIDLabed++]=1030; 
	iIDLabed[iNumberIDLabed++]=1087; 
	iIDLabed[iNumberIDLabed++]=1106; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//房子，住宅，家庭
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="房子，住宅，家庭";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1012; 
	iIDLabed[iNumberIDLabed++]=1049; 
	iIDLabed[iNumberIDLabed++]=2891; 
	iIDLabed[iNumberIDLabed++]=1146; 
	iIDLabed[iNumberIDLabed++]=2853; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//户内，室内
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="户内，室内";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1754; 
	iIDLabed[iNumberIDLabed++]=1756; 
	iIDLabed[iNumberIDLabed++]=3121; 
	iIDLabed[iNumberIDLabed++]=3334; 
	iIDLabed[iNumberIDLabed++]=1755; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//山，山脉
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="山，山脉";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1752; 
	iIDLabed[iNumberIDLabed++]=1912; 
	iIDLabed[iNumberIDLabed++]=1780; 
	iIDLabed[iNumberIDLabed++]=1850; 
	iIDLabed[iNumberIDLabed++]=2192; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//云，天空
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="云，天空";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2069; 
	iIDLabed[iNumberIDLabed++]=2099; 
	iIDLabed[iNumberIDLabed++]=2207; 
	iIDLabed[iNumberIDLabed++]=2574; 
	iIDLabed[iNumberIDLabed++]=3008; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//冰河
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="冰河";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2989; 
	iIDLabed[iNumberIDLabed++]=2996; 
	iIDLabed[iNumberIDLabed++]=1356; 
	iIDLabed[iNumberIDLabed++]=1504; 
	iIDLabed[iNumberIDLabed++]=3030; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//雪
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="雪";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1299; 
	iIDLabed[iNumberIDLabed++]=1236; 
	iIDLabed[iNumberIDLabed++]=1208; 
	iIDLabed[iNumberIDLabed++]=3055; 
	iIDLabed[iNumberIDLabed++]=3030; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//水
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="水";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1298; 
	iIDLabed[iNumberIDLabed++]=1309; 
	iIDLabed[iNumberIDLabed++]=1351; 
	iIDLabed[iNumberIDLabed++]=1436; 
	iIDLabed[iNumberIDLabed++]=1671; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label



	//草
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="草";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2037; 
	iIDLabed[iNumberIDLabed++]=2105; 
	iIDLabed[iNumberIDLabed++]=2152; 
	iIDLabed[iNumberIDLabed++]=2535; 
	iIDLabed[iNumberIDLabed++]=2932; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label	

	//天，天空
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="天，天空";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2915; 
	iIDLabed[iNumberIDLabed++]=3010; 
	iIDLabed[iNumberIDLabed++]=1272; 
	iIDLabed[iNumberIDLabed++]=1631; 
	iIDLabed[iNumberIDLabed++]=1274; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label		
	//水，河，江
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="水，河，江";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1277; 
	iIDLabed[iNumberIDLabed++]=2011; 
	iIDLabed[iNumberIDLabed++]=2097; 
	iIDLabed[iNumberIDLabed++]=2244; 
	iIDLabed[iNumberIDLabed++]=1279; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label	

	//冰山
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="冰山";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1319; 
	iIDLabed[iNumberIDLabed++]=1334; 
	iIDLabed[iNumberIDLabed++]=1335; 
	iIDLabed[iNumberIDLabed++]=1324; 
	iIDLabed[iNumberIDLabed++]=1325; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//漂浮
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="漂浮";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1388; 
	iIDLabed[iNumberIDLabed++]=1395; 
	iIDLabed[iNumberIDLabed++]=1389; 
	iIDLabed[iNumberIDLabed++]=1390; 
	iIDLabed[iNumberIDLabed++]=1394; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//水獭, 水獭皮
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="水獭, 水獭皮";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1397; 
	iIDLabed[iNumberIDLabed++]=1398; 
	iIDLabed[iNumberIDLabed++]=1399; 
	iIDLabed[iNumberIDLabed++]=1401; 
	iIDLabed[iNumberIDLabed++]=1410; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//岩石
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="岩石";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1426; 
	iIDLabed[iNumberIDLabed++]=1428; 
	iIDLabed[iNumberIDLabed++]=1458; 
	iIDLabed[iNumberIDLabed++]=1476; 
	iIDLabed[iNumberIDLabed++]=2164; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//鸟，鸟类
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="鸟，鸟类";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2153; 
	iIDLabed[iNumberIDLabed++]=1490; 
	iIDLabed[iNumberIDLabed++]=2428; 
	iIDLabed[iNumberIDLabed++]=1612; 
	iIDLabed[iNumberIDLabed++]=2657; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//植物，种植
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="植物，种植";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1720; 
	iIDLabed[iNumberIDLabed++]=1748; 
	iIDLabed[iNumberIDLabed++]=2000; 
	iIDLabed[iNumberIDLabed++]=2362; 
	iIDLabed[iNumberIDLabed++]=3015; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//雪山
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="雪山";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=839; 
	iIDLabed[iNumberIDLabed++]=3038; 
	iIDLabed[iNumberIDLabed++]=809; 
	iIDLabed[iNumberIDLabed++]=1243; 
	iIDLabed[iNumberIDLabed++]=2332; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//公园
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="公园";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1088; 
	iIDLabed[iNumberIDLabed++]=1083; 
	iIDLabed[iNumberIDLabed++]=1096; 
	iIDLabed[iNumberIDLabed++]=1095; 
	iIDLabed[iNumberIDLabed++]=1099; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//人
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="人";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2456; 
	iIDLabed[iNumberIDLabed++]=2744; 
	iIDLabed[iNumberIDLabed++]=3191; 
	iIDLabed[iNumberIDLabed++]=3334; 
	iIDLabed[iNumberIDLabed++]=1063; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//飞机
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="飞机";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1165; 
	iIDLabed[iNumberIDLabed++]=1171; 
	iIDLabed[iNumberIDLabed++]=2702; 
	iIDLabed[iNumberIDLabed++]=2746; 
	iIDLabed[iNumberIDLabed++]=2868; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//钓鱼，垂钓
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="钓鱼，垂钓";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2881; 
	iIDLabed[iNumberIDLabed++]=2892; 
	iIDLabed[iNumberIDLabed++]=2456; 
	iIDLabed[iNumberIDLabed++]=2723; 
	iIDLabed[iNumberIDLabed++]=2873; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//反射，倒影
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="反射，倒影";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2873; 
	iIDLabed[iNumberIDLabed++]=1670; 
	iIDLabed[iNumberIDLabed++]=2900; 
	iIDLabed[iNumberIDLabed++]=2910; 
	iIDLabed[iNumberIDLabed++]=1256; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//船，小船，艇
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="船，小船，艇";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2326; 
	iIDLabed[iNumberIDLabed++]=2339; 
	iIDLabed[iNumberIDLabed++]=3279; 
	iIDLabed[iNumberIDLabed++]=2585; 
	iIDLabed[iNumberIDLabed++]=1258; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//海港，港口
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="海港，港口";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1287; 
	iIDLabed[iNumberIDLabed++]=2332; 
	iIDLabed[iNumberIDLabed++]=2804; 
	iIDLabed[iNumberIDLabed++]=2897; 
	iIDLabed[iNumberIDLabed++]=1288; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//母牛，大型母兽
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="母牛，大型母兽";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1219; 
	iIDLabed[iNumberIDLabed++]=1222; 
	iIDLabed[iNumberIDLabed++]=1215; 
	iIDLabed[iNumberIDLabed++]=1221; 
	iIDLabed[iNumberIDLabed++]=1216; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//冰，冰块
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="冰，冰块";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1318; 
	iIDLabed[iNumberIDLabed++]=1340; 
	iIDLabed[iNumberIDLabed++]=1518; 
	iIDLabed[iNumberIDLabed++]=3019; 
	iIDLabed[iNumberIDLabed++]=1228; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//鸭子
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="鸭子";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1196; 
	iIDLabed[iNumberIDLabed++]=1198; 
	iIDLabed[iNumberIDLabed++]=1194; 
	iIDLabed[iNumberIDLabed++]=1195; 
	iIDLabed[iNumberIDLabed++]=1199; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//湖，湖水
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="湖，湖水";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1753; 
	iIDLabed[iNumberIDLabed++]=1784; 
	iIDLabed[iNumberIDLabed++]=1816; 
	iIDLabed[iNumberIDLabed++]=3054; 
	iIDLabed[iNumberIDLabed++]=1251; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//飞溅，溅起，水花
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="飞溅，溅起，水花";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1343; 
	iIDLabed[iNumberIDLabed++]=1355; 
	iIDLabed[iNumberIDLabed++]=1438; 
	iIDLabed[iNumberIDLabed++]=2738; 
	iIDLabed[iNumberIDLabed++]=2922; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//汽车
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="汽车";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2296; 
	iIDLabed[iNumberIDLabed++]=2927; 
	iIDLabed[iNumberIDLabed++]=1943; 
	iIDLabed[iNumberIDLabed++]=1164; 
	iIDLabed[iNumberIDLabed++]=2022; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//壁画
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="壁画";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2042; 
	iIDLabed[iNumberIDLabed++]=2049; 
	iIDLabed[iNumberIDLabed++]=2045; 
	iIDLabed[iNumberIDLabed++]=2048; 
	iIDLabed[iNumberIDLabed++]=2044; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//驼鹿，动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="驼鹿，动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2077; 
	iIDLabed[iNumberIDLabed++]=2064; 
	iIDLabed[iNumberIDLabed++]=2419; 
	iIDLabed[iNumberIDLabed++]=2057; 
	iIDLabed[iNumberIDLabed++]=2058; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2063; 
	iIDLabed[iNumberIDLabed++]=2121; 
	iIDLabed[iNumberIDLabed++]=2139; 
	iIDLabed[iNumberIDLabed++]=1307; 
	iIDLabed[iNumberIDLabed++]=2052; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//海滩，海滨
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="海滩，海滨";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2587; 
	iIDLabed[iNumberIDLabed++]=2839; 
	iIDLabed[iNumberIDLabed++]=2580; 
	iIDLabed[iNumberIDLabed++]=135; 
	iIDLabed[iNumberIDLabed++]=148; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//海洋，大海
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="海洋，大海";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2600; 
	iIDLabed[iNumberIDLabed++]=2621; 
	iIDLabed[iNumberIDLabed++]=2666; 
	iIDLabed[iNumberIDLabed++]=3071; 
	iIDLabed[iNumberIDLabed++]=3269; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//瀑布
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="瀑布";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1681; 
	iIDLabed[iNumberIDLabed++]=1702; 
	iIDLabed[iNumberIDLabed++]=2307; 
	iIDLabed[iNumberIDLabed++]=3056; 
	iIDLabed[iNumberIDLabed++]=1430; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//秃头鹰，动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="秃头鹰，动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1457; 
	iIDLabed[iNumberIDLabed++]=1472; 
	iIDLabed[iNumberIDLabed++]=1424; 
	iIDLabed[iNumberIDLabed++]=1425; 
	iIDLabed[iNumberIDLabed++]=1462; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//鲸，动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="鲸，动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1453; 
	iIDLabed[iNumberIDLabed++]=1446; 
	iIDLabed[iNumberIDLabed++]=1447; 
	iIDLabed[iNumberIDLabed++]=1448; 
	iIDLabed[iNumberIDLabed++]=1449; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//海豹,动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="海豹,动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1542; 
	iIDLabed[iNumberIDLabed++]=1376; 
	iIDLabed[iNumberIDLabed++]=1526; 
	iIDLabed[iNumberIDLabed++]=1379; 
	iIDLabed[iNumberIDLabed++]=1530; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//陆地
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="陆地";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2120; 
	iIDLabed[iNumberIDLabed++]=2125; 
	iIDLabed[iNumberIDLabed++]=2144; 
	iIDLabed[iNumberIDLabed++]=2190; 
	iIDLabed[iNumberIDLabed++]=2140; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//熊，动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="熊，动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2126; 
	iIDLabed[iNumberIDLabed++]=2143; 
	iIDLabed[iNumberIDLabed++]=2171; 
	iIDLabed[iNumberIDLabed++]=2129; 
	iIDLabed[iNumberIDLabed++]=2141; 
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//羊
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="羊";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2179; 
	iIDLabed[iNumberIDLabed++]=2184; 
	iIDLabed[iNumberIDLabed++]=3355; 
	iIDLabed[iNumberIDLabed++]=2182; 
	iIDLabed[iNumberIDLabed++]=3357; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//希腊，古希腊
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="希腊，古希腊";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3269; 
	iIDLabed[iNumberIDLabed++]=3288; 
	iIDLabed[iNumberIDLabed++]=3294; 
	iIDLabed[iNumberIDLabed++]=3312; 
	iIDLabed[iNumberIDLabed++]=3298;	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//建筑
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="建筑";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3325; 
	iIDLabed[iNumberIDLabed++]=3085; 
	iIDLabed[iNumberIDLabed++]=3122; 
	iIDLabed[iNumberIDLabed++]=239; 
	iIDLabed[iNumberIDLabed++]=278; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//教堂
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="教堂";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3131; 
	iIDLabed[iNumberIDLabed++]=3293; 
	iIDLabed[iNumberIDLabed++]=3111; 
	iIDLabed[iNumberIDLabed++]=3140; 
	iIDLabed[iNumberIDLabed++]=3294; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label

	//废墟, 遗迹
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="废墟, 遗迹";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3287; 
	iIDLabed[iNumberIDLabed++]=3296; 
	iIDLabed[iNumberIDLabed++]=3289; 
	iIDLabed[iNumberIDLabed++]=3299; 
	iIDLabed[iNumberIDLabed++]=288; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//猫，动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="猫，动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3322; 
	iIDLabed[iNumberIDLabed++]=3337; 
	iIDLabed[iNumberIDLabed++]=3332; 
	iIDLabed[iNumberIDLabed++]=3326; 
	iIDLabed[iNumberIDLabed++]=3329; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//著名建筑
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="著名建筑";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3350; 
	iIDLabed[iNumberIDLabed++]=3351; 
	iIDLabed[iNumberIDLabed++]=3287; 
	iIDLabed[iNumberIDLabed++]=3304; 
	iIDLabed[iNumberIDLabed++]=3321; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//庙, 寺, 神殿, 教堂
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="庙, 寺, 神殿, 教堂";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3289; 
	iIDLabed[iNumberIDLabed++]=3302; 
	iIDLabed[iNumberIDLabed++]=206; 
	iIDLabed[iNumberIDLabed++]=231; 
	iIDLabed[iNumberIDLabed++]=244; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//焰火，烟花
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="焰火，烟花";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3192; 
	iIDLabed[iNumberIDLabed++]=3239; 
	iIDLabed[iNumberIDLabed++]=3259; 
	iIDLabed[iNumberIDLabed++]=3196; 
	iIDLabed[iNumberIDLabed++]=3227; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//夕阳，太阳
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="夕阳，太阳";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3080; 
	iIDLabed[iNumberIDLabed++]=3113; 
	iIDLabed[iNumberIDLabed++]=3062; 
	iIDLabed[iNumberIDLabed++]=3080; 
	iIDLabed[iNumberIDLabed++]=3100; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//塔, 城堡
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="塔, 城堡";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3101; 
	iIDLabed[iNumberIDLabed++]=3098; 
	iIDLabed[iNumberIDLabed++]=3105; 
	iIDLabed[iNumberIDLabed++]=3103; 
	iIDLabed[iNumberIDLabed++]=3104; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//渔民
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="渔民";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2762; 
	iIDLabed[iNumberIDLabed++]=2766; 
	iIDLabed[iNumberIDLabed++]=2767; 
	iIDLabed[iNumberIDLabed++]=2722; 
	iIDLabed[iNumberIDLabed++]=2729; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	
	//海狮
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="海狮";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=1388; 
	iIDLabed[iNumberIDLabed++]=1390; 
	iIDLabed[iNumberIDLabed++]=1392; 
	iIDLabed[iNumberIDLabed++]=1393; 
	iIDLabed[iNumberIDLabed++]=1395; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//管道
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="管道";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=2012; 
	iIDLabed[iNumberIDLabed++]=2013; 
	iIDLabed[iNumberIDLabed++]=2014; 
	iIDLabed[iNumberIDLabed++]=2015; 
//	iIDLabed[iNumberIDLabed++]=2729; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//窗户
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="窗户";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3131; 
	iIDLabed[iNumberIDLabed++]=3140; 
	iIDLabed[iNumberIDLabed++]=1754; 
	iIDLabed[iNumberIDLabed++]=3113; 
	iIDLabed[iNumberIDLabed++]=3135; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//守卫, 警卫
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="守卫, 警卫";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=3308; 
	iIDLabed[iNumberIDLabed++]=3309; 
	iIDLabed[iNumberIDLabed++]=3310; 
	iIDLabed[iNumberIDLabed++]=3311; 
	iIDLabed[iNumberIDLabed++]=3312; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//非洲人，非洲建筑
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="非洲人，非洲建筑";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=16; 
	iIDLabed[iNumberIDLabed++]=46; 
	iIDLabed[iNumberIDLabed++]=59; 
	iIDLabed[iNumberIDLabed++]=72; 
	iIDLabed[iNumberIDLabed++]=81; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//海滩，风景，旅游
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="海滩，风景，旅游";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=129; 
	iIDLabed[iNumberIDLabed++]=146; 
	iIDLabed[iNumberIDLabed++]=119; 
	iIDLabed[iNumberIDLabed++]=169; 
	iIDLabed[iNumberIDLabed++]=187; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//公交车
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="公交车";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=308; 
	iIDLabed[iNumberIDLabed++]=316; 
	iIDLabed[iNumberIDLabed++]=359; 
	iIDLabed[iNumberIDLabed++]=389; 
	iIDLabed[iNumberIDLabed++]=344; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//恐龙
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="恐龙";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=459; 
	iIDLabed[iNumberIDLabed++]=468; 
	iIDLabed[iNumberIDLabed++]=418; 
	iIDLabed[iNumberIDLabed++]=455; 
	iIDLabed[iNumberIDLabed++]=479; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//大象
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="大象";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=504; 
	iIDLabed[iNumberIDLabed++]=521; 
	iIDLabed[iNumberIDLabed++]=536; 
	iIDLabed[iNumberIDLabed++]=579; 
	iIDLabed[iNumberIDLabed++]=582; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//玫瑰，花
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="玫瑰，花";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=602; 
	iIDLabed[iNumberIDLabed++]=613; 
	iIDLabed[iNumberIDLabed++]=622; 
	iIDLabed[iNumberIDLabed++]=645; 
	iIDLabed[iNumberIDLabed++]=689; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//马,动物
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="马，动物";  //
	int iNumberIDLabed=0;    //5
	iIDLabed[iNumberIDLabed++]=713; 
	iIDLabed[iNumberIDLabed++]=732; 
	iIDLabed[iNumberIDLabed++]=789; 
	iIDLabed[iNumberIDLabed++]=742; 
	iIDLabed[iNumberIDLabed++]=769; 	
	this->WriteLabelToTheEndFile(cSemanticAnnotionFile,sLabelString,iIDLabed,iNumberIDLabed);	
	iNumberAnnotion++;
	}//end of one label
	//食物，饮食
	{
	int iIDLabed[MAX_NUMBER_LABELONONEANNOTION];
	CString sLabelString="食物，饮食";  //
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