 // VqRetrieveData.cpp: implementation of the VqRetrieveData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VqRetrieve.h"
#include "VqRetrieveData.h"
#include "math.h"
#define VECTOR_5 10000000
#define VECTOR_6 1000

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define SAVEWIDTH(mywidth)  (mywidth+3)/4*4              ////存储的宽

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
///构造函数
VqRetrieveData::VqRetrieveData(CString sPath)
{
	m_bRetrieve=0;///初始值为没有检索,或没有检索成功,他控制是否显示,接口函数为IsDisplay();//是否可以显示
	m_iCurrentCharacterNumber=7;  ///当前的特征量为7个
	m_bCharacterDistill=TRUE;   ///检索标志为true，出现问题，将它设置为FALSE
	m_ibmpvarible=0;     //检索为0,在图像特征计算中使用
	this->m_iCurrentFileNumber=0;   //当前的所有图像为0
	m_hCharacterVq=NULL;       //内存指向为空
	m_hStandEquVaible=NULL;	
	m_hStandAveVaible=NULL;	
	this->m_bMemoryEnough=true;       ///初始内存值为足够
	this->m_sPath=sPath;     ///得到图像库路径
   if(this->ReadCharacterFile(this->m_sPath)==TRUE) ///读文件
   {
	   return;
   }
  	this->m_iCurrentFileNumber=this->ChooseBmpValueable(this->m_sPath);///得到图像的数目
//开辟内存	1:特征量结构体
	m_hCharacterVq=GlobalAlloc(GMEM_FIXED,m_iCurrentFileNumber*sizeof(CHARACTERVQ));
	if(m_hCharacterVq==NULL)
	{
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		this->m_bMemoryEnough=FALSE;
		return;
	}
//开辟内存2:方差
	m_hStandEquVaible=GlobalAlloc(GMEM_FIXED,this->m_iCurrentFileNumber*sizeof(double));
	if(m_hStandEquVaible==NULL)
	{
		GlobalFree(m_hCharacterVq);
		m_hCharacterVq=NULL;
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		this->m_bMemoryEnough=FALSE;
		return;
	}
//开辟内存3：均值
	m_hStandAveVaible=GlobalAlloc(GMEM_FIXED,this->m_iCurrentFileNumber*sizeof(double));
	if(m_hStandAveVaible==NULL)
	{
		GlobalFree(m_hCharacterVq);
		m_hCharacterVq=NULL;
		GlobalFree(m_hStandEquVaible);
		m_hStandEquVaible=NULL;
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		this->m_bMemoryEnough=FALSE;
		return;
	}
///得到三个内存的首地址
	this->m_pCharacterVq=(CHARACTERVQ*)m_hCharacterVq;   //指针
	this->m_pStandEquVarible=(double*)m_hStandEquVaible;
	this->m_pStandAveVarible=(double*)m_hStandAveVaible;
	m_ibmpvarible=0;     //恢复初始值,在检索图像之前应该将m_ibmpvarible为0
	if(this->CharacterDistill(this->m_sPath)==FALSE)   ///提取m_sPath路径下所有文件的特征矢量
	{
		MessageBox(NULL,"CharacterDistill Fail!","Error!", MB_ICONSTOP|MB_OK);
		this->m_bCharacterDistill=false;
		this->DestroyMemory();  //删除所有内存
		return;
	}
	else
		m_bCharacterDistill=true;   //提取成功
///标准化,在标准化中,我们计算特征量的均值,方差,将标准化后的系数保存,标准化参数也保存,矢量均值
	this->StandCharacter(this->m_pCharacterVq,this->m_iCurrentFileNumber,this->m_iCurrentCharacterNumber,this->m_pStandEquVarible,this->m_pStandAveVarible);


	

}

VqRetrieveData::~VqRetrieveData()
{

}
///释放所有内存变量
bool VqRetrieveData::DestroyMemory()
{
	if(m_hCharacterVq!=NULL)
	{
		GlobalFree(m_hCharacterVq);
		m_hCharacterVq=NULL;
	}
	if(m_hStandEquVaible!=NULL)
	{
		GlobalFree(m_hStandEquVaible);
		m_hStandEquVaible=NULL;
	}
	if(m_hStandAveVaible==NULL)
	{
		GlobalFree(m_hStandAveVaible);
		m_hStandAveVaible=NULL;
	}
return true;
}
///获得该类的路径名
CString VqRetrieveData::GetPathName()
{
return this->m_sPath;
}
///内存是否足够
BOOL VqRetrieveData::IsMemoryEnough()
{
	return this->m_bMemoryEnough;      

}



long int VqRetrieveData::ChooseBmpValueable(CString sPath)
{
	//检索文件夹文件
	long int bmpNumberChoose=0;       ///选择的的图像数目
	CString str = sPath;
    if(str.Right(1) != "\\")
	   str += "\\";
	str += "*.bmp";
	CFileFind file;
	BOOL bContinueNumber = file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber = file.FindNextFile();
		if(!file.IsDirectory() && !file.IsDots())
		{	
		//判断是否可以打开,即是否为bmp_256图像
			if(this->ChooseBmp(file.GetFilePath())==TRUE)
				bmpNumberChoose++;                              //如果可以打开,则存储该保留该文件名
		}

	}
//检索子文件夹	
	file.Close();
	str.Empty();
	str=sPath;
	if(str.Right(1) != "\\")
	   str += "\\";
	str += "*.*";
	bContinueNumber = file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber = file.FindNextFile();
		if (file.IsDots()) continue;
		else if(file.IsDirectory())
		{	
		//判断是否可以打开,即是否为bmp_256图像
			bmpNumberChoose=bmpNumberChoose+this->ChooseBmpValueable(file.GetFilePath());                              //如果可以打开,则存储该保留该文件名		}
		}
	}

	return bmpNumberChoose;
}

bool VqRetrieveData::ChooseBmp(CString filePathName)
{
	CFile file;
	LPBITMAPFILEHEADER Retrievebitfile;
    LPBITMAPINFOHEADER Retrievebitinfo;
	if(file.Open(filePathName,CFile::modeRead,NULL)==NULL)
		      return false; ///////////打开文件失败
	int m_iRetrieveImageSize=file.GetLength();
	HGLOBAL Retrievehg=GlobalAlloc(GMEM_FIXED,m_iRetrieveImageSize);
	if(Retrievehg==NULL)
		{
		  MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		  file.Close();
		  return FALSE;
		}
	unsigned char *m_cRetrieveImageBytes=(unsigned char *)Retrievehg;
	file.Read(m_cRetrieveImageBytes,m_iRetrieveImageSize);
	Retrievebitfile=(LPBITMAPFILEHEADER)m_cRetrieveImageBytes;
	DWORD m_iRetrievebfbts=Retrievebitfile->bfOffBits;
    Retrievebitinfo=(LPBITMAPINFOHEADER)(m_cRetrieveImageBytes+sizeof(BITMAPFILEHEADER));
	 if(Retrievebitfile->bfType!=0x4d42)
		{
//	      MessageBox(NULL,"对不起！文件不是Bmp文件!","文件打开",MB_ICONSTOP|MB_OK);//Display the info		 
          GlobalFree(Retrievehg);//Free the memory
		   file.Close();
	      return FALSE;
		}
        ////If the image is a 256-gray image or not
       if(Retrievebitinfo->biBitCount!=8&&Retrievebitinfo->biBitCount!=24)
		{
//	     MessageBox(NULL,"对不起！文件[%s]不是256灰度(或256色)图象!","文件打开",MB_ICONSTOP|MB_OK);//Display the info		   
   	     GlobalFree(Retrievehg);//Free the memory
		  file.Close();
	     return FALSE;
		}
	  
       ////If the image is compressed or not
	       if(Retrievebitinfo->biCompression!=0)
	  {
//	    MessageBox(NULL,"对不起！文件是压缩图象!","文件打开",MB_ICONSTOP|MB_OK);//Display the info		  
   	    GlobalFree(Retrievehg);//Free the memory
		 file.Close();
	    return FALSE;
	  }
	 int PaltteNumber;///得到图像的调色板数目
	if(Retrievebitinfo->biBitCount==24)//没有调色板
		  {
		  PaltteNumber=0;

		  }
	 else if (Retrievebitinfo->biClrUsed==0) 
	{	   
		  PaltteNumber=(int)pow(2,Retrievebitinfo->biBitCount);
	}
	else
	  PaltteNumber=Retrievebitinfo->biClrUsed;
///调色板检验
	if(m_iRetrievebfbts!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PaltteNumber*sizeof(RGBQUAD)))
		  {
			file.Close();
		    return  false;
		  }

    GlobalFree(Retrievehg);//  only test whethe it can be opened ,Free the memory
	file.Close();
	return TRUE;
}
//读特征数据文件，没有编辑，默认读不到
bool VqRetrieveData::ReadCharacterFile(CString sPath)
{

	return false;             //读文件失败
}
///计算sPath内的所有bmp文件的特征矢量，迭代检索
bool VqRetrieveData::CharacterDistill(CString sPath)
{	

	if(this->m_bCharacterDistill==FALSE)  ///检索失败
		return false;
	if(this->m_ibmpvarible>this->m_iCurrentFileNumber)
		return false;			///图像数目不符，检索失败
	CString str = sPath;
    if(str.Right(1) != "\\")
	   str += "\\";
	str += "*.bmp";
	CFileFind file;
	BOOL bContinueNumber = file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber = file.FindNextFile();
		if(!file.IsDirectory() && !file.IsDots())
		{	
		//判断是否可以打开,即是否为bmp_256图像
			if(this->ChooseBmp(file.GetFilePath())==TRUE) //可以大开
			{
					if(CharacterBmp(file.GetFilePath(),this->m_pCharacterVq+this->m_ibmpvarible)==false)//特征提取
					{
						this->m_bCharacterDistill=FALSE;
						return false;  //失败
					}
						
					this->m_ibmpvarible++;                              //如果可以打开,则存储该保留该文件名
			}
		}
	}//end of while
///自文件夹图像特征提取
	file.Close();
	str.Empty();
	str=sPath;
	if(str.Right(1) != "\\")
	   str += "\\";
	str += "*.*";
	bContinueNumber = file.FindFile(str);
	while(bContinueNumber)
	{
		bContinueNumber = file.FindNextFile();
		if (file.IsDots()) continue;
		else if(file.IsDirectory())
		{	
			if(CharacterDistill(file.GetFilePath())==false)///提取子文件夹的图像矢量数据
			{
				this->m_bCharacterDistill=FALSE; //失败
				return false;  //失败			
			}                             //如果可以打开,则存储该保留该文件名		}
		}
	}//end of while
return true;         //返回
}
///将24为图像的亮度提取出来
void VqRetrieveData::Transform24(unsigned char *p24data, unsigned char *poutdata, int width, int height)
{

		 unsigned int lLineBytes = WIDTHBYTES(width * 24);
  	    for(int l=0;l<height;l++) //纵坐标
		  for(int k=0;k<width;k++) //横坐标
		{ 
		   double B=*(p24data+lLineBytes*l+3*k);
		   double G=*(p24data+lLineBytes*l+3*k+1);
		   double R=*(p24data+lLineBytes*l+3*k+2);
		  //转换为YUV颜色模型，计算Y分量
		  *(poutdata+width*l+k)=(unsigned char)((9798*R+19235*G+3735*B)/32768.0);
	   	}	
}
///将8为图像的亮度提取出来
bool VqRetrieveData::Transform8(unsigned char *p8data, unsigned char *poutdata,RGBQUAD *palttledata,int palttlenumber, int width, int height)
{
///取得图像的原始亮度
		unsigned char blue,green,red;   ///
		for(int i=0;i<height;i++)
		  for(int j=0;j<width;j++)
		  {
			if(*(p8data+i*SAVEWIDTH(width)+j)>palttlenumber-1) 
				return false;
			blue=palttledata[*(p8data+i*SAVEWIDTH(width)+j)].rgbBlue;
			green=palttledata[*(p8data+i*SAVEWIDTH(width)+j)].rgbGreen;
			red=palttledata[*(p8data+i*SAVEWIDTH(width)+j)].rgbRed;
/////不需要，行为4的被数
		  *(poutdata+i*width+j)=(unsigned char)((9798*red+19235*green+3735*blue)/32768.0);
		  }
	  return true;
}

///提取图像BmpFilePathName的特征向量，放到CharacterVq中，成功则返回，提取的矢量数据应该是
///当前的矢量的维数this->m_iCurrentCharacterNumber
bool VqRetrieveData::CharacterBmp(CString BmpFilePathName, CHARACTERVQ *CharacterVq)
{
	CFile file;    //文件名
	LPBITMAPFILEHEADER Retrievebitfile; ///文件头
    LPBITMAPINFOHEADER Retrievebitinfo;  //信息头
	int ImageLength;        ///图像的大小
    int PaltteNumber;///得到图像的调色板数目
	DWORD ImageBfts;        ///图像数据区的偏移
	WORD iBmpBitCount;                  ///图像的位数8,24
	int ImageWidth;                //图像的宽
	int ImageHeight;				//图像的高
	int ImageRealDataWidth;        //图像数据的真高ImageRealDataWidth＝ImageRealWidthEnd－ImageRealHeightBegin＋1；
	int ImageRealDataHeight;	//图像数据的真宽
	int ImageRealHeightBegin;                   //图像的实际高的开始，这是考虑到图像可能出现黑白边
	int ImageRealWidthBegin;                    ///图像的有效的宽开始
	int ImageRealHeightEnd;                  ///图像的有效的高结束
	int ImageRealWidthEnd;                    ///图像的有效的宽结束
	unsigned char *pOriginalImageByteHead;       ///图像头的指针
	HGLOBAL hOriginalImageByteHead;               //图像内存的句柄1
	unsigned char *pOriginalImageByteData;       ///图像数据区
	HGLOBAL hOriginalImageByteData;               //图像数据区内存句柄2，该内存是将原始图像变换后的内存,没有考虑边缘
	unsigned char *pRealImageByteData;       ///图像有效的数据区
	HGLOBAL hRealImageByteData;               //图像有效的数据区内存3，原始数据不一定是，该数据是用来计算特征的
	int i,j;  ///循环变量

///读取图像的数据
	if(file.Open(BmpFilePathName,CFile::modeRead,NULL)==NULL)
		 return false; ///////////打开文件失败
	ImageLength=file.GetLength();
	hOriginalImageByteHead=GlobalAlloc(GMEM_FIXED,ImageLength);
	if(hOriginalImageByteHead==NULL)
		{
		  MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		  file.Close();
		  return FALSE;
		}
	pOriginalImageByteHead=(unsigned char *)hOriginalImageByteHead;  //得到内存的首地址
	file.Read(pOriginalImageByteHead,ImageLength);  ///读完数据
	file.Close();
	Retrievebitfile=(LPBITMAPFILEHEADER)pOriginalImageByteHead;
	ImageBfts=Retrievebitfile->bfOffBits;
    Retrievebitinfo=(LPBITMAPINFOHEADER)(pOriginalImageByteHead+sizeof(BITMAPFILEHEADER));
	iBmpBitCount=Retrievebitinfo->biBitCount;  //得到图像的位数
	ImageWidth=Retrievebitinfo->biWidth;  //
	ImageHeight=Retrievebitinfo->biHeight;
//开辟内存保存图像数据，我们需要的，但没有考虑到边缘效应
	hOriginalImageByteData=GlobalAlloc(GMEM_FIXED,ImageWidth*ImageHeight);
	if (hOriginalImageByteData==NULL)
	{
		GlobalFree(hOriginalImageByteHead);  //释放原始图像内存
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return FALSE;
	}
	pOriginalImageByteData=(unsigned char*)hOriginalImageByteData;
//获得图像的颜色表大小
	if(iBmpBitCount==24)//没有调色板,得到调色板的数目
		  PaltteNumber=0;
	else if (Retrievebitinfo->biClrUsed==0)   //有调色板，但是默认,得到调色板的数目
	{	   
		  PaltteNumber=(int)pow(2,Retrievebitinfo->biBitCount);
	}
		else                    //非默认,得到调色板的数目
		 PaltteNumber=Retrievebitinfo->biClrUsed;
//////转换,将图像数据转换成我们需要的数据，即真实的图像数据，而且是亮度值
switch(iBmpBitCount)
{
case 24://24位图像
	{
	
	Transform24(pOriginalImageByteHead+ImageBfts,pOriginalImageByteData,ImageWidth,ImageHeight);
	}///end of case 24
	break;
case 8:   //8
	{	
		Transform8(pOriginalImageByteHead+ImageBfts,pOriginalImageByteData,(RGBQUAD*)(pOriginalImageByteHead+sizeof(LPBITMAPFILEHEADER)+sizeof(LPBITMAPINFOHEADER)),PaltteNumber,ImageWidth,ImageHeight);
	}//end of case 8
	break;
default:
	{
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		GlobalFree(hOriginalImageByteHead);  //释放原始图像内存
		return false;
	}
}
///end of switch,转换结束，释放原始图像内存
GlobalFree(hOriginalImageByteHead);///////删除内存1
///begin 计算实际的边缘
///	计算图像实际的各个参数
////由于图像的边缘可能是纯白的或纯黑的，我们要消除它们的影响,得到图像有效得到高宽
//1	ImageRealHeightBegin
	long int realTotal;
	for(i=0; i<ImageHeight; i++)
	{
		  realTotal=0;
		  for(j=0; j<ImageWidth; j++)
		  {
				realTotal=realTotal+*(pOriginalImageByteData + i*ImageWidth + j);
		  }
	   if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //不是黑色或白色
		  {
				ImageRealHeightBegin=i;          //实际的高度
				break;
			  }
		}
//2	ImageRealHeightEnd
		for(i=ImageHeight-1; i>=0; i--)
		{
			  realTotal=0;
			  for(j=0; j<ImageWidth; j++)
			  {
					realTotal=realTotal+*(pOriginalImageByteData + i*ImageWidth + j);
			  }
			  if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //不是黑色或白色
			  {
					ImageRealHeightEnd=i;          //实际的高度
					break;
			  }
		}					
//3	ImageRealWidthBegin
		for(j=0; j<ImageWidth; j++)
		{
			  realTotal=0;
			  for(i=0; i<ImageHeight; i++)
			  {
					realTotal=realTotal+*(pOriginalImageByteData + i*ImageWidth + j);
			  }
			  if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //不是黑色或白色
			  {
					ImageRealWidthBegin=j;          //实际的高度
					break;
			  }
		}	
//4	ImageRealWidthEnd
		for(j=ImageWidth-1; j>=0; j--)
		{
			  realTotal=0;
			  for(i=0; i<ImageHeight; i++)
			  {
					realTotal=realTotal+*(pOriginalImageByteData + i*ImageWidth + j);
			  }
			  if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //不是黑色或白色
			  {
					ImageRealWidthEnd=j;          //实际的高度
					break;
			  }
		}
///end of 计算图像实际的边缘参数ImageRealHeightEnd,ImageRealHeightBegin,ImageRealWidthEnd,ImageRealWidthBegin
////开辟适当的内存来保存有效数据并删除上面的数据
	ImageRealDataWidth=ImageRealWidthEnd-ImageRealWidthBegin+1;   ///图像的有效数据的宽
	ImageRealDataHeight=ImageRealHeightEnd-ImageRealHeightBegin+1;   ///图像的有效数据的宽
	hRealImageByteData=GlobalAlloc(GMEM_FIXED,ImageRealDataWidth*ImageRealDataHeight);
	if(hRealImageByteData==NULL)
	{
		GlobalFree(hOriginalImageByteData);
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return false;
	}
	pRealImageByteData=(unsigned char*)hRealImageByteData; //得到首地址
	for(i=0;i<ImageRealDataHeight;i++)  //拷贝有效数据
		for(j=0;j<ImageRealDataWidth;j++)
			*(pRealImageByteData+i*ImageRealDataWidth+j)=*(pOriginalImageByteData+(i+ImageRealHeightBegin)*ImageWidth+j+ImageRealWidthBegin);			
	GlobalFree(hOriginalImageByteData); ///删除内存2
///////完成拷贝，有效数据的首地址pRealImageByteData，高ImageRealDataWidth，宽ImageRealDataHeight
////句柄：hRealImageByteData有待删除
 if (this->CharacterVq(pRealImageByteData,CharacterVq,ImageRealDataWidth,ImageRealDataHeight)==false)
 {
	 	GlobalFree(hRealImageByteData); ///删除内存3
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return false;

 }
 memcpy(CharacterVq->m_sFileName,BmpFilePathName,MAX_FILE_NAME);///获得文件名
 CharacterVq->m_uBitCount=iBmpBitCount;  ///得到图像的位数
CharacterVq->m_iImageWidth=ImageWidth;    //得到宽
CharacterVq->m_iImageHeigth=ImageHeight;  ///得到高
 /*
char *data;
data=(char*)CharacterVq->m_sFileName;
CString p;
p=data;
/////处理，归一化，均值等
*/
///end of 函数
//正常返回
	GlobalFree(hRealImageByteData); ///删除内存3
///end of read bmp
	return true;
}

////提取首地址为pdata，宽为datawidth，高为dataheight,的特征量，输出到*charactervq
///返回true，提取成功，否则，失败
bool VqRetrieveData::CharacterVq(unsigned char *pdata, CHARACTERVQ *charactervq, int datawidth, int dataheigth)
{
	int iCharacterNumbercheck=0;          //特征矢量维数的检验,计算一个矢量，加一，最后应该等与m_iCurrentCharacterNumber
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
					regiondata2=(regiontotallleft/regionnumberleft+regiontotalright/regionnumberright)/2.0;////计算公式
					if((unsigned char)regiondata2==(unsigned char)regiondata1)///结束
						break;
					else 
						regiondata1=regiondata2;

		}
	charactervq->m_dFileOriginalCharacter[0]=regiondata2/255.0; ///归一化
	iCharacterNumbercheck++;
	

///参数2
	charactervq->m_dFileOriginalCharacter[1]=(double)regionnumberleft/(regionnumberleft+regionnumberright);
	iCharacterNumbercheck++;
////end of 颜色
	///颜色参数的个数
//	this->m_uColorCharacterNumber=iCharacterNumbercheck;


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
	charactervq->m_dFileOriginalCharacter[2]=(Con1+Con2)/2/255.0/255.0;             //提取反差变量
	iCharacterNumbercheck++;
	charactervq->m_dFileOriginalCharacter[3]=(Asm1+Asm2)/2;              ///提取能量变量
	iCharacterNumbercheck++;
	charactervq->m_dFileOriginalCharacter[4]=-(Ent1+Ent2)/2;              ///提取熵变量
	iCharacterNumbercheck++;
	delete[] texturematrix;
	delete[] texturematriy;


//////参数3，4，5提取结束	
////end of 纹理
///纹理参数的个数
//	this->m_utextureCharacterNumber=iCharacterNumbercheck-this->m_uColorCharacterNumber;

	
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
	  	charactervq->m_dFileOriginalCharacter[5]=(pow((u_20-u_02),2.0)+4*u_11*u_11)*VECTOR_5;  ////保存 
		iCharacterNumbercheck++;
		///一阶不变矩保存
		charactervq->m_dFileOriginalCharacter[6]=(u_20+u_02)*VECTOR_6;
		iCharacterNumbercheck++;
///end of 形状
 //形状参数的个数
//		this->m_ufigureCharacterNumber=iCharacterNumbercheck-this->m_uColorCharacterNumber-this->m_utextureCharacterNumber;
//////////////////////////////////////////////////////////////////////////
iCharacterNumbercheck=7;
///end of the charactervq distill
/*	if (iCharacterNumbercheck!=this->m_iCurrentCharacterNumber)
	{
		MessageBox(NULL,"CharacterNumber not right","error",MB_ICONSTOP|MB_OK);
		return false;
	}
	*/
	return true;
}
////标准化参数
/////charactervq:待归一化的结构；numberbmp=图像的数目；characternumber：矢量的维数
///pstandequvarible:输出标准差的首地址，pstandaverage：输出均值的首地址
bool VqRetrieveData::StandCharacter(CHARACTERVQ *charactervq, long numberbmp, int characternumber,double *pstandequvarible,double *pstandaverage)
{ 
	
	  long double Datatotal=0;  /////同一类的参数的和
	  long int number;     ///循环计数，矢量维数
	  double Average,squareDifference;  ////均值和方差
	  for(number=0;number<characternumber;number++)   ////各个维数矢量
	  {
			Datatotal=0;   ///初始化
			for(long int i=0;i<numberbmp;i++)   ///图像的数目
			{
				  Datatotal=Datatotal+(charactervq+i)->m_dFileOriginalCharacter[number];
			}
			Average=Datatotal/numberbmp;     ///均值
			Datatotal=0;   ///初始化
			for(i=0;i<numberbmp;i++)
			{
				  Datatotal=Datatotal+pow((charactervq+i)->m_dFileOriginalCharacter[number]-Average,2.0);
			}
			squareDifference=sqrt(Datatotal/numberbmp);
			*(pstandequvarible+number)=squareDifference;///////均方差输出
			*(pstandaverage+number)=Average;///均值输出
			for(i=0;i<numberbmp;i++)  ///得到归一化参数
			{
				  (charactervq+i)->m_dFileStandCharacter[number]=((charactervq+i)->m_dFileOriginalCharacter[number]-Average)/(*(pstandequvarible+number));
				  if(fabs((charactervq+i)->m_dFileStandCharacter[number])<=3.0)  //限制范围
						continue;
				  else if ((charactervq+i)->m_dFileStandCharacter[number]<-3)
				  {
						(charactervq+i)->m_dFileStandCharacter[number]=-3;
				  }
				  else 
				  {
						(charactervq+i)->m_dFileStandCharacter[number]=3;
				  }
			}
	  }
///计算均值
	   for(number=0;number<numberbmp;number++)   ////各个适量的均值
	   {
	    	Datatotal=0;
		    for(int i=0;i<characternumber;i++)
				Datatotal=Datatotal+(charactervq+number)->m_dFileStandCharacter[number];
		   (charactervq+number)->m_dAverage=Datatotal/characternumber;

	   }
return true;

}
///获得可以显示图像的数目，如果返回255，则表示出错，返回0－15正确
unsigned char VqRetrieveData::GetRetrieveDisplayBmpNumber()
{
	if(this->m_bRetrieve==false)
		return 255;        ///检索失败
	return this->m_uDisplayNumber;  ///0_15

}
////获得第number个可以显示图像的文件名
CString VqRetrieveData::GetBmpDisplayFileName(unsigned char number)
{
	if (number<0||number>15||number>this->m_uDisplayNumber)     ///越界
	{
		MessageBox(NULL,"You overLoad the bmp","erro!",MB_OK);
		return "";
	}
	return this->m_sDisplayFile[number];        //返回该图像的文件名

}
////获得检索的距离
///number=0_15,返回－1：错误
CString VqRetrieveData::GetRetrieveDistance(int number)
{
	if (number<0||number>15||number>this->m_uDisplayNumber)     ///越界
	{
		MessageBox(NULL,"The distance has not be caculate!","error!",MB_OK);
		return "";
	}
	CString sRetrieveDistance;
	sRetrieveDistance.Format("%s%d",sRetrieveDistance,m_dDisplayFileDistance[number]);
	return sRetrieveDistance;  //return the distance
}
//对外接口，访问检索时间
CString VqRetrieveData::GetRetrieveTime()
{
	if (this->m_bRetrieve==false)
	{
		MessageBox(NULL,"You didn't Retrieve before!","error",MB_OK);
		return "";
	}
	return this->m_sRetrieveTime;

}
//获得检索结果中0－15中的检索特征结构体
CHARACTERVQ VqRetrieveData::GetRetrieveDisCharacterVq(unsigned char number)
{
	if (this->m_bRetrieve==false)
	{
		MessageBox(NULL,"You didn't Retrieve before!","error",MB_OK);
	}
	if (number<0||number>15||number>this->m_uDisplayNumber)     ///越界
	{
		MessageBox(NULL,"You overLoad the bmpName","erro!",MB_OK);
	}
	return this->m_cCharacterVq[number];
}

///直接的检索矢量，对图像的矢量进行检索
///pCharacterVq图像库矢量结构体指针，iCurrentCharacter:检索矢量的数量，
//iRetrieveBmpNumber图像库图像数目， KeybmpCharactervq :关键图像的结构
//pOutCharactervq：输出结构体的头指针，maxOutNumber输出图像的最多数目，
//pOutDistance检索图像和关键图像的距离输出的头指针，RetrieveTime检索时间
bool VqRetrieveData::RetrieveKeyVqMethod1(CHARACTERVQ *pCharacterVq,int iCurrentCharacter, long int iRetrieveBmpNumber,CHARACTERVQ KeybmpCharactervq, CHARACTERVQ *pOutCharactervq, unsigned char maxOutNumber, double *pOutDistance, CString RetrieveTime)
{

	int vector=iCurrentCharacter;  //特征量未计算完
	double *pDistance=new double[iRetrieveBmpNumber];//开辟内存空间保存距离数据
	///开辟内存，载入颜色几何均值
	////初始化////
	clock_t time1,time2;       ///定义时间变量 
	double timecost;
	time1=clock();
			for(long int number=0;number<iRetrieveBmpNumber;number++)
	{
				pDistance[number]=0;             ///初始值为0
				for(int vectornumber=0;vectornumber<vector;vectornumber++)
					pDistance[number]=pDistance[number]+pow((KeybmpCharactervq.m_dFileStandCharacter[vectornumber]-(pCharacterVq+number)->m_dFileStandCharacter[vectornumber]),2); ///第k种检索方式

	}
///到现在为止,pDistance[]保存了各个图象和关键图的颜色距离,绝对值
///排序,按着从小到大排序
//基本方法,找到最小的欧式距离后,将它所对应的图象路径给显示数组,然后将赋值256
//由于归一化后的图象的欧式距离不可能为256,故在找下一个图象时不会重复
/*			int sign=0;            ///做最相似图象的标号
			for(int displaynumber=0;displaynumber<maxOutNumber;displaynumber++)//16个显示图象
			{
				if(displaynumber>m_iOverSign-1)        //如果图像数目不够，退出
					{
						m_iDisplayNumber=m_iOverSign;
						break;
					}	
					for(int check=0;check<m_iOverSign;check++)
					{
						if(pDistance[sign]>pDistance[check])  //要最小的
						{
							sign=check;
						}
					}
					CString DisplayDistance;///为显示参数的临时变量
					m_sRetrieveBmp[displaynumber].Empty();
					m_sRetrieveBmp[displaynumber]=this->m_cPathName[sign];///save the PathName for display
					for(int i=0;i<VECTOR;i++)///保存最近的矢量
	  				this->m_dRetrieveImageDisplayCharacter[displaynumber][i]=this->m_dRetrieveImageCharacter[sign*VECTOR+i];
				    DisplayDistance.Format("%s%f",DisplayDistance,pDistance[sign]);///保存图像的相似程度
					m_sDistance[displaynumber]=DisplayDistance;					///保存图像的相似程度
					pDistance[sign]=OVER;             //给最大值

		}
///事后处理

	delete[] pDistance;               //释放保存欧式距离内存
	time2=clock();
	  timecost=(double)(time2-time1)/CLOCKS_PER_SEC;
	  this->m_sRetrieveTime.Empty();
	  this->m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timecost);
 
///为显示文件名作准备，显示文件名为：m_sDisplayFileName
	
	for(displaynumber=0;displaynumber<16;displaynumber++)//16个显示图象
		  {
		  if(displaynumber>m_iOverSign-1)        //如果图像数目不够，退出
				break;
		  CFile filedisplay;
		  filedisplay.Open(m_sRetrieveBmp[displaynumber],CFile::modeRead,NULL);
		  m_sDisplayFileName[displaynumber]=filedisplay.GetFileName();
		//		  filedisplay.Close();		  
		  }

//////////////////////////////////////////////////////////////////////////
	this->m_bRetrieve=TRUE;              //检索结束,置标志位
	 EndWaitCursor();
     UpdateAllViews(NULL);
	 */
	return true;
}
///检索与KeyBmpCharacterVq匹配的图像，方法i
bool VqRetrieveData::RetrieveMethod(CHARACTERVQ KeyBmpCharacterVq,int i)
{
	switch(i)
	 {
case 1:
	{
		RetrieveKeyVqMethod1(this->m_pCharacterVq,this->m_iCurrentCharacterNumber, this->m_iCurrentFileNumber,KeyBmpCharacterVq, this->m_cCharacterVq, 16, this->m_dDisplayFileDistance, this->m_sRetrieveTime);
		break;
	}
case 2:
	break;
default:
	break;
		}
	return true;
}
