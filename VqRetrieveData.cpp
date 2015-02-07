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
#define SAVEWIDTH(mywidth)  (mywidth+3)/4*4              ////�洢�Ŀ�

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
///���캯��
VqRetrieveData::VqRetrieveData(CString sPath)
{
	m_bRetrieve=0;///��ʼֵΪû�м���,��û�м����ɹ�,�������Ƿ���ʾ,�ӿں���ΪIsDisplay();//�Ƿ������ʾ
	m_iCurrentCharacterNumber=7;  ///��ǰ��������Ϊ7��
	m_bCharacterDistill=TRUE;   ///������־Ϊtrue���������⣬��������ΪFALSE
	m_ibmpvarible=0;     //����Ϊ0,��ͼ������������ʹ��
	this->m_iCurrentFileNumber=0;   //��ǰ������ͼ��Ϊ0
	m_hCharacterVq=NULL;       //�ڴ�ָ��Ϊ��
	m_hStandEquVaible=NULL;	
	m_hStandAveVaible=NULL;	
	this->m_bMemoryEnough=true;       ///��ʼ�ڴ�ֵΪ�㹻
	this->m_sPath=sPath;     ///�õ�ͼ���·��
   if(this->ReadCharacterFile(this->m_sPath)==TRUE) ///���ļ�
   {
	   return;
   }
  	this->m_iCurrentFileNumber=this->ChooseBmpValueable(this->m_sPath);///�õ�ͼ�����Ŀ
//�����ڴ�	1:�������ṹ��
	m_hCharacterVq=GlobalAlloc(GMEM_FIXED,m_iCurrentFileNumber*sizeof(CHARACTERVQ));
	if(m_hCharacterVq==NULL)
	{
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		this->m_bMemoryEnough=FALSE;
		return;
	}
//�����ڴ�2:����
	m_hStandEquVaible=GlobalAlloc(GMEM_FIXED,this->m_iCurrentFileNumber*sizeof(double));
	if(m_hStandEquVaible==NULL)
	{
		GlobalFree(m_hCharacterVq);
		m_hCharacterVq=NULL;
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		this->m_bMemoryEnough=FALSE;
		return;
	}
//�����ڴ�3����ֵ
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
///�õ������ڴ���׵�ַ
	this->m_pCharacterVq=(CHARACTERVQ*)m_hCharacterVq;   //ָ��
	this->m_pStandEquVarible=(double*)m_hStandEquVaible;
	this->m_pStandAveVarible=(double*)m_hStandAveVaible;
	m_ibmpvarible=0;     //�ָ���ʼֵ,�ڼ���ͼ��֮ǰӦ�ý�m_ibmpvaribleΪ0
	if(this->CharacterDistill(this->m_sPath)==FALSE)   ///��ȡm_sPath·���������ļ�������ʸ��
	{
		MessageBox(NULL,"CharacterDistill Fail!","Error!", MB_ICONSTOP|MB_OK);
		this->m_bCharacterDistill=false;
		this->DestroyMemory();  //ɾ�������ڴ�
		return;
	}
	else
		m_bCharacterDistill=true;   //��ȡ�ɹ�
///��׼��,�ڱ�׼����,���Ǽ����������ľ�ֵ,����,����׼�����ϵ������,��׼������Ҳ����,ʸ����ֵ
	this->StandCharacter(this->m_pCharacterVq,this->m_iCurrentFileNumber,this->m_iCurrentCharacterNumber,this->m_pStandEquVarible,this->m_pStandAveVarible);


	

}

VqRetrieveData::~VqRetrieveData()
{

}
///�ͷ������ڴ����
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
///��ø����·����
CString VqRetrieveData::GetPathName()
{
return this->m_sPath;
}
///�ڴ��Ƿ��㹻
BOOL VqRetrieveData::IsMemoryEnough()
{
	return this->m_bMemoryEnough;      

}



long int VqRetrieveData::ChooseBmpValueable(CString sPath)
{
	//�����ļ����ļ�
	long int bmpNumberChoose=0;       ///ѡ��ĵ�ͼ����Ŀ
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
		//�ж��Ƿ���Դ�,���Ƿ�Ϊbmp_256ͼ��
			if(this->ChooseBmp(file.GetFilePath())==TRUE)
				bmpNumberChoose++;                              //������Դ�,��洢�ñ������ļ���
		}

	}
//�������ļ���	
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
		//�ж��Ƿ���Դ�,���Ƿ�Ϊbmp_256ͼ��
			bmpNumberChoose=bmpNumberChoose+this->ChooseBmpValueable(file.GetFilePath());                              //������Դ�,��洢�ñ������ļ���		}
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
		      return false; ///////////���ļ�ʧ��
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
//	      MessageBox(NULL,"�Բ����ļ�����Bmp�ļ�!","�ļ���",MB_ICONSTOP|MB_OK);//Display the info		 
          GlobalFree(Retrievehg);//Free the memory
		   file.Close();
	      return FALSE;
		}
        ////If the image is a 256-gray image or not
       if(Retrievebitinfo->biBitCount!=8&&Retrievebitinfo->biBitCount!=24)
		{
//	     MessageBox(NULL,"�Բ����ļ�[%s]����256�Ҷ�(��256ɫ)ͼ��!","�ļ���",MB_ICONSTOP|MB_OK);//Display the info		   
   	     GlobalFree(Retrievehg);//Free the memory
		  file.Close();
	     return FALSE;
		}
	  
       ////If the image is compressed or not
	       if(Retrievebitinfo->biCompression!=0)
	  {
//	    MessageBox(NULL,"�Բ����ļ���ѹ��ͼ��!","�ļ���",MB_ICONSTOP|MB_OK);//Display the info		  
   	    GlobalFree(Retrievehg);//Free the memory
		 file.Close();
	    return FALSE;
	  }
	 int PaltteNumber;///�õ�ͼ��ĵ�ɫ����Ŀ
	if(Retrievebitinfo->biBitCount==24)//û�е�ɫ��
		  {
		  PaltteNumber=0;

		  }
	 else if (Retrievebitinfo->biClrUsed==0) 
	{	   
		  PaltteNumber=(int)pow(2,Retrievebitinfo->biBitCount);
	}
	else
	  PaltteNumber=Retrievebitinfo->biClrUsed;
///��ɫ�����
	if(m_iRetrievebfbts!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PaltteNumber*sizeof(RGBQUAD)))
		  {
			file.Close();
		    return  false;
		  }

    GlobalFree(Retrievehg);//  only test whethe it can be opened ,Free the memory
	file.Close();
	return TRUE;
}
//�����������ļ���û�б༭��Ĭ�϶�����
bool VqRetrieveData::ReadCharacterFile(CString sPath)
{

	return false;             //���ļ�ʧ��
}
///����sPath�ڵ�����bmp�ļ�������ʸ������������
bool VqRetrieveData::CharacterDistill(CString sPath)
{	

	if(this->m_bCharacterDistill==FALSE)  ///����ʧ��
		return false;
	if(this->m_ibmpvarible>this->m_iCurrentFileNumber)
		return false;			///ͼ����Ŀ����������ʧ��
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
		//�ж��Ƿ���Դ�,���Ƿ�Ϊbmp_256ͼ��
			if(this->ChooseBmp(file.GetFilePath())==TRUE) //���Դ�
			{
					if(CharacterBmp(file.GetFilePath(),this->m_pCharacterVq+this->m_ibmpvarible)==false)//������ȡ
					{
						this->m_bCharacterDistill=FALSE;
						return false;  //ʧ��
					}
						
					this->m_ibmpvarible++;                              //������Դ�,��洢�ñ������ļ���
			}
		}
	}//end of while
///���ļ���ͼ��������ȡ
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
			if(CharacterDistill(file.GetFilePath())==false)///��ȡ���ļ��е�ͼ��ʸ������
			{
				this->m_bCharacterDistill=FALSE; //ʧ��
				return false;  //ʧ��			
			}                             //������Դ�,��洢�ñ������ļ���		}
		}
	}//end of while
return true;         //����
}
///��24Ϊͼ���������ȡ����
void VqRetrieveData::Transform24(unsigned char *p24data, unsigned char *poutdata, int width, int height)
{

		 unsigned int lLineBytes = WIDTHBYTES(width * 24);
  	    for(int l=0;l<height;l++) //������
		  for(int k=0;k<width;k++) //������
		{ 
		   double B=*(p24data+lLineBytes*l+3*k);
		   double G=*(p24data+lLineBytes*l+3*k+1);
		   double R=*(p24data+lLineBytes*l+3*k+2);
		  //ת��ΪYUV��ɫģ�ͣ�����Y����
		  *(poutdata+width*l+k)=(unsigned char)((9798*R+19235*G+3735*B)/32768.0);
	   	}	
}
///��8Ϊͼ���������ȡ����
bool VqRetrieveData::Transform8(unsigned char *p8data, unsigned char *poutdata,RGBQUAD *palttledata,int palttlenumber, int width, int height)
{
///ȡ��ͼ���ԭʼ����
		unsigned char blue,green,red;   ///
		for(int i=0;i<height;i++)
		  for(int j=0;j<width;j++)
		  {
			if(*(p8data+i*SAVEWIDTH(width)+j)>palttlenumber-1) 
				return false;
			blue=palttledata[*(p8data+i*SAVEWIDTH(width)+j)].rgbBlue;
			green=palttledata[*(p8data+i*SAVEWIDTH(width)+j)].rgbGreen;
			red=palttledata[*(p8data+i*SAVEWIDTH(width)+j)].rgbRed;
/////����Ҫ����Ϊ4�ı���
		  *(poutdata+i*width+j)=(unsigned char)((9798*red+19235*green+3735*blue)/32768.0);
		  }
	  return true;
}

///��ȡͼ��BmpFilePathName�������������ŵ�CharacterVq�У��ɹ��򷵻أ���ȡ��ʸ������Ӧ����
///��ǰ��ʸ����ά��this->m_iCurrentCharacterNumber
bool VqRetrieveData::CharacterBmp(CString BmpFilePathName, CHARACTERVQ *CharacterVq)
{
	CFile file;    //�ļ���
	LPBITMAPFILEHEADER Retrievebitfile; ///�ļ�ͷ
    LPBITMAPINFOHEADER Retrievebitinfo;  //��Ϣͷ
	int ImageLength;        ///ͼ��Ĵ�С
    int PaltteNumber;///�õ�ͼ��ĵ�ɫ����Ŀ
	DWORD ImageBfts;        ///ͼ����������ƫ��
	WORD iBmpBitCount;                  ///ͼ���λ��8,24
	int ImageWidth;                //ͼ��Ŀ�
	int ImageHeight;				//ͼ��ĸ�
	int ImageRealDataWidth;        //ͼ�����ݵ����ImageRealDataWidth��ImageRealWidthEnd��ImageRealHeightBegin��1��
	int ImageRealDataHeight;	//ͼ�����ݵ����
	int ImageRealHeightBegin;                   //ͼ���ʵ�ʸߵĿ�ʼ�����ǿ��ǵ�ͼ����ܳ��ֺڰױ�
	int ImageRealWidthBegin;                    ///ͼ�����Ч�Ŀ�ʼ
	int ImageRealHeightEnd;                  ///ͼ�����Ч�ĸ߽���
	int ImageRealWidthEnd;                    ///ͼ�����Ч�Ŀ����
	unsigned char *pOriginalImageByteHead;       ///ͼ��ͷ��ָ��
	HGLOBAL hOriginalImageByteHead;               //ͼ���ڴ�ľ��1
	unsigned char *pOriginalImageByteData;       ///ͼ��������
	HGLOBAL hOriginalImageByteData;               //ͼ���������ڴ���2�����ڴ��ǽ�ԭʼͼ��任����ڴ�,û�п��Ǳ�Ե
	unsigned char *pRealImageByteData;       ///ͼ����Ч��������
	HGLOBAL hRealImageByteData;               //ͼ����Ч���������ڴ�3��ԭʼ���ݲ�һ���ǣ�����������������������
	int i,j;  ///ѭ������

///��ȡͼ�������
	if(file.Open(BmpFilePathName,CFile::modeRead,NULL)==NULL)
		 return false; ///////////���ļ�ʧ��
	ImageLength=file.GetLength();
	hOriginalImageByteHead=GlobalAlloc(GMEM_FIXED,ImageLength);
	if(hOriginalImageByteHead==NULL)
		{
		  MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		  file.Close();
		  return FALSE;
		}
	pOriginalImageByteHead=(unsigned char *)hOriginalImageByteHead;  //�õ��ڴ���׵�ַ
	file.Read(pOriginalImageByteHead,ImageLength);  ///��������
	file.Close();
	Retrievebitfile=(LPBITMAPFILEHEADER)pOriginalImageByteHead;
	ImageBfts=Retrievebitfile->bfOffBits;
    Retrievebitinfo=(LPBITMAPINFOHEADER)(pOriginalImageByteHead+sizeof(BITMAPFILEHEADER));
	iBmpBitCount=Retrievebitinfo->biBitCount;  //�õ�ͼ���λ��
	ImageWidth=Retrievebitinfo->biWidth;  //
	ImageHeight=Retrievebitinfo->biHeight;
//�����ڴ汣��ͼ�����ݣ�������Ҫ�ģ���û�п��ǵ���ԵЧӦ
	hOriginalImageByteData=GlobalAlloc(GMEM_FIXED,ImageWidth*ImageHeight);
	if (hOriginalImageByteData==NULL)
	{
		GlobalFree(hOriginalImageByteHead);  //�ͷ�ԭʼͼ���ڴ�
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return FALSE;
	}
	pOriginalImageByteData=(unsigned char*)hOriginalImageByteData;
//���ͼ�����ɫ���С
	if(iBmpBitCount==24)//û�е�ɫ��,�õ���ɫ�����Ŀ
		  PaltteNumber=0;
	else if (Retrievebitinfo->biClrUsed==0)   //�е�ɫ�壬����Ĭ��,�õ���ɫ�����Ŀ
	{	   
		  PaltteNumber=(int)pow(2,Retrievebitinfo->biBitCount);
	}
		else                    //��Ĭ��,�õ���ɫ�����Ŀ
		 PaltteNumber=Retrievebitinfo->biClrUsed;
//////ת��,��ͼ������ת����������Ҫ�����ݣ�����ʵ��ͼ�����ݣ�����������ֵ
switch(iBmpBitCount)
{
case 24://24λͼ��
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
		GlobalFree(hOriginalImageByteHead);  //�ͷ�ԭʼͼ���ڴ�
		return false;
	}
}
///end of switch,ת���������ͷ�ԭʼͼ���ڴ�
GlobalFree(hOriginalImageByteHead);///////ɾ���ڴ�1
///begin ����ʵ�ʵı�Ե
///	����ͼ��ʵ�ʵĸ�������
////����ͼ��ı�Ե�����Ǵ��׵Ļ򴿺ڵģ�����Ҫ�������ǵ�Ӱ��,�õ�ͼ����Ч�õ��߿�
//1	ImageRealHeightBegin
	long int realTotal;
	for(i=0; i<ImageHeight; i++)
	{
		  realTotal=0;
		  for(j=0; j<ImageWidth; j++)
		  {
				realTotal=realTotal+*(pOriginalImageByteData + i*ImageWidth + j);
		  }
	   if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //���Ǻ�ɫ���ɫ
		  {
				ImageRealHeightBegin=i;          //ʵ�ʵĸ߶�
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
			  if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //���Ǻ�ɫ���ɫ
			  {
					ImageRealHeightEnd=i;          //ʵ�ʵĸ߶�
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
			  if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //���Ǻ�ɫ���ɫ
			  {
					ImageRealWidthBegin=j;          //ʵ�ʵĸ߶�
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
			  if ((realTotal==0||realTotal==ImageWidth*255)==FALSE) //���Ǻ�ɫ���ɫ
			  {
					ImageRealWidthEnd=j;          //ʵ�ʵĸ߶�
					break;
			  }
		}
///end of ����ͼ��ʵ�ʵı�Ե����ImageRealHeightEnd,ImageRealHeightBegin,ImageRealWidthEnd,ImageRealWidthBegin
////�����ʵ����ڴ���������Ч���ݲ�ɾ�����������
	ImageRealDataWidth=ImageRealWidthEnd-ImageRealWidthBegin+1;   ///ͼ�����Ч���ݵĿ�
	ImageRealDataHeight=ImageRealHeightEnd-ImageRealHeightBegin+1;   ///ͼ�����Ч���ݵĿ�
	hRealImageByteData=GlobalAlloc(GMEM_FIXED,ImageRealDataWidth*ImageRealDataHeight);
	if(hRealImageByteData==NULL)
	{
		GlobalFree(hOriginalImageByteData);
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return false;
	}
	pRealImageByteData=(unsigned char*)hRealImageByteData; //�õ��׵�ַ
	for(i=0;i<ImageRealDataHeight;i++)  //������Ч����
		for(j=0;j<ImageRealDataWidth;j++)
			*(pRealImageByteData+i*ImageRealDataWidth+j)=*(pOriginalImageByteData+(i+ImageRealHeightBegin)*ImageWidth+j+ImageRealWidthBegin);			
	GlobalFree(hOriginalImageByteData); ///ɾ���ڴ�2
///////��ɿ�������Ч���ݵ��׵�ַpRealImageByteData����ImageRealDataWidth����ImageRealDataHeight
////�����hRealImageByteData�д�ɾ��
 if (this->CharacterVq(pRealImageByteData,CharacterVq,ImageRealDataWidth,ImageRealDataHeight)==false)
 {
	 	GlobalFree(hRealImageByteData); ///ɾ���ڴ�3
		MessageBox(NULL,"Memory is not enough","Error!", MB_ICONSTOP|MB_OK);
		return false;

 }
 memcpy(CharacterVq->m_sFileName,BmpFilePathName,MAX_FILE_NAME);///����ļ���
 CharacterVq->m_uBitCount=iBmpBitCount;  ///�õ�ͼ���λ��
CharacterVq->m_iImageWidth=ImageWidth;    //�õ���
CharacterVq->m_iImageHeigth=ImageHeight;  ///�õ���
 /*
char *data;
data=(char*)CharacterVq->m_sFileName;
CString p;
p=data;
/////������һ������ֵ��
*/
///end of ����
//��������
	GlobalFree(hRealImageByteData); ///ɾ���ڴ�3
///end of read bmp
	return true;
}

////��ȡ�׵�ַΪpdata����Ϊdatawidth����Ϊdataheight,���������������*charactervq
///����true����ȡ�ɹ�������ʧ��
bool VqRetrieveData::CharacterVq(unsigned char *pdata, CHARACTERVQ *charactervq, int datawidth, int dataheigth)
{
	int iCharacterNumbercheck=0;          //����ʸ��ά���ļ���,����һ��ʸ������һ�����Ӧ�õ���m_iCurrentCharacterNumber
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
					regiondata2=(regiontotallleft/regionnumberleft+regiontotalright/regionnumberright)/2.0;////���㹫ʽ
					if((unsigned char)regiondata2==(unsigned char)regiondata1)///����
						break;
					else 
						regiondata1=regiondata2;

		}
	charactervq->m_dFileOriginalCharacter[0]=regiondata2/255.0; ///��һ��
	iCharacterNumbercheck++;
	

///����2
	charactervq->m_dFileOriginalCharacter[1]=(double)regionnumberleft/(regionnumberleft+regionnumberright);
	iCharacterNumbercheck++;
////end of ��ɫ
	///��ɫ�����ĸ���
//	this->m_uColorCharacterNumber=iCharacterNumbercheck;


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
	charactervq->m_dFileOriginalCharacter[2]=(Con1+Con2)/2/255.0/255.0;             //��ȡ�������
	iCharacterNumbercheck++;
	charactervq->m_dFileOriginalCharacter[3]=(Asm1+Asm2)/2;              ///��ȡ��������
	iCharacterNumbercheck++;
	charactervq->m_dFileOriginalCharacter[4]=-(Ent1+Ent2)/2;              ///��ȡ�ر���
	iCharacterNumbercheck++;
	delete[] texturematrix;
	delete[] texturematriy;


//////����3��4��5��ȡ����	
////end of ����
///��������ĸ���
//	this->m_utextureCharacterNumber=iCharacterNumbercheck-this->m_uColorCharacterNumber;

	
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
	  	charactervq->m_dFileOriginalCharacter[5]=(pow((u_20-u_02),2.0)+4*u_11*u_11)*VECTOR_5;  ////���� 
		iCharacterNumbercheck++;
		///һ�ײ���ر���
		charactervq->m_dFileOriginalCharacter[6]=(u_20+u_02)*VECTOR_6;
		iCharacterNumbercheck++;
///end of ��״
 //��״�����ĸ���
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
////��׼������
/////charactervq:����һ���Ľṹ��numberbmp=ͼ�����Ŀ��characternumber��ʸ����ά��
///pstandequvarible:�����׼����׵�ַ��pstandaverage�������ֵ���׵�ַ
bool VqRetrieveData::StandCharacter(CHARACTERVQ *charactervq, long numberbmp, int characternumber,double *pstandequvarible,double *pstandaverage)
{ 
	
	  long double Datatotal=0;  /////ͬһ��Ĳ����ĺ�
	  long int number;     ///ѭ��������ʸ��ά��
	  double Average,squareDifference;  ////��ֵ�ͷ���
	  for(number=0;number<characternumber;number++)   ////����ά��ʸ��
	  {
			Datatotal=0;   ///��ʼ��
			for(long int i=0;i<numberbmp;i++)   ///ͼ�����Ŀ
			{
				  Datatotal=Datatotal+(charactervq+i)->m_dFileOriginalCharacter[number];
			}
			Average=Datatotal/numberbmp;     ///��ֵ
			Datatotal=0;   ///��ʼ��
			for(i=0;i<numberbmp;i++)
			{
				  Datatotal=Datatotal+pow((charactervq+i)->m_dFileOriginalCharacter[number]-Average,2.0);
			}
			squareDifference=sqrt(Datatotal/numberbmp);
			*(pstandequvarible+number)=squareDifference;///////���������
			*(pstandaverage+number)=Average;///��ֵ���
			for(i=0;i<numberbmp;i++)  ///�õ���һ������
			{
				  (charactervq+i)->m_dFileStandCharacter[number]=((charactervq+i)->m_dFileOriginalCharacter[number]-Average)/(*(pstandequvarible+number));
				  if(fabs((charactervq+i)->m_dFileStandCharacter[number])<=3.0)  //���Ʒ�Χ
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
///�����ֵ
	   for(number=0;number<numberbmp;number++)   ////���������ľ�ֵ
	   {
	    	Datatotal=0;
		    for(int i=0;i<characternumber;i++)
				Datatotal=Datatotal+(charactervq+number)->m_dFileStandCharacter[number];
		   (charactervq+number)->m_dAverage=Datatotal/characternumber;

	   }
return true;

}
///��ÿ�����ʾͼ�����Ŀ���������255�����ʾ��������0��15��ȷ
unsigned char VqRetrieveData::GetRetrieveDisplayBmpNumber()
{
	if(this->m_bRetrieve==false)
		return 255;        ///����ʧ��
	return this->m_uDisplayNumber;  ///0_15

}
////��õ�number��������ʾͼ����ļ���
CString VqRetrieveData::GetBmpDisplayFileName(unsigned char number)
{
	if (number<0||number>15||number>this->m_uDisplayNumber)     ///Խ��
	{
		MessageBox(NULL,"You overLoad the bmp","erro!",MB_OK);
		return "";
	}
	return this->m_sDisplayFile[number];        //���ظ�ͼ����ļ���

}
////��ü����ľ���
///number=0_15,���أ�1������
CString VqRetrieveData::GetRetrieveDistance(int number)
{
	if (number<0||number>15||number>this->m_uDisplayNumber)     ///Խ��
	{
		MessageBox(NULL,"The distance has not be caculate!","error!",MB_OK);
		return "";
	}
	CString sRetrieveDistance;
	sRetrieveDistance.Format("%s%d",sRetrieveDistance,m_dDisplayFileDistance[number]);
	return sRetrieveDistance;  //return the distance
}
//����ӿڣ����ʼ���ʱ��
CString VqRetrieveData::GetRetrieveTime()
{
	if (this->m_bRetrieve==false)
	{
		MessageBox(NULL,"You didn't Retrieve before!","error",MB_OK);
		return "";
	}
	return this->m_sRetrieveTime;

}
//��ü��������0��15�еļ��������ṹ��
CHARACTERVQ VqRetrieveData::GetRetrieveDisCharacterVq(unsigned char number)
{
	if (this->m_bRetrieve==false)
	{
		MessageBox(NULL,"You didn't Retrieve before!","error",MB_OK);
	}
	if (number<0||number>15||number>this->m_uDisplayNumber)     ///Խ��
	{
		MessageBox(NULL,"You overLoad the bmpName","erro!",MB_OK);
	}
	return this->m_cCharacterVq[number];
}

///ֱ�ӵļ���ʸ������ͼ���ʸ�����м���
///pCharacterVqͼ���ʸ���ṹ��ָ�룬iCurrentCharacter:����ʸ����������
//iRetrieveBmpNumberͼ���ͼ����Ŀ�� KeybmpCharactervq :�ؼ�ͼ��Ľṹ
//pOutCharactervq������ṹ���ͷָ�룬maxOutNumber���ͼ��������Ŀ��
//pOutDistance����ͼ��͹ؼ�ͼ��ľ��������ͷָ�룬RetrieveTime����ʱ��
bool VqRetrieveData::RetrieveKeyVqMethod1(CHARACTERVQ *pCharacterVq,int iCurrentCharacter, long int iRetrieveBmpNumber,CHARACTERVQ KeybmpCharactervq, CHARACTERVQ *pOutCharactervq, unsigned char maxOutNumber, double *pOutDistance, CString RetrieveTime)
{

	int vector=iCurrentCharacter;  //������δ������
	double *pDistance=new double[iRetrieveBmpNumber];//�����ڴ�ռ䱣���������
	///�����ڴ棬������ɫ���ξ�ֵ
	////��ʼ��////
	clock_t time1,time2;       ///����ʱ����� 
	double timecost;
	time1=clock();
			for(long int number=0;number<iRetrieveBmpNumber;number++)
	{
				pDistance[number]=0;             ///��ʼֵΪ0
				for(int vectornumber=0;vectornumber<vector;vectornumber++)
					pDistance[number]=pDistance[number]+pow((KeybmpCharactervq.m_dFileStandCharacter[vectornumber]-(pCharacterVq+number)->m_dFileStandCharacter[vectornumber]),2); ///��k�ּ�����ʽ

	}
///������Ϊֹ,pDistance[]�����˸���ͼ��͹ؼ�ͼ����ɫ����,����ֵ
///����,���Ŵ�С��������
//��������,�ҵ���С��ŷʽ�����,��������Ӧ��ͼ��·������ʾ����,Ȼ�󽫸�ֵ256
//���ڹ�һ�����ͼ���ŷʽ���벻����Ϊ256,��������һ��ͼ��ʱ�����ظ�
/*			int sign=0;            ///��������ͼ��ı��
			for(int displaynumber=0;displaynumber<maxOutNumber;displaynumber++)//16����ʾͼ��
			{
				if(displaynumber>m_iOverSign-1)        //���ͼ����Ŀ�������˳�
					{
						m_iDisplayNumber=m_iOverSign;
						break;
					}	
					for(int check=0;check<m_iOverSign;check++)
					{
						if(pDistance[sign]>pDistance[check])  //Ҫ��С��
						{
							sign=check;
						}
					}
					CString DisplayDistance;///Ϊ��ʾ��������ʱ����
					m_sRetrieveBmp[displaynumber].Empty();
					m_sRetrieveBmp[displaynumber]=this->m_cPathName[sign];///save the PathName for display
					for(int i=0;i<VECTOR;i++)///���������ʸ��
	  				this->m_dRetrieveImageDisplayCharacter[displaynumber][i]=this->m_dRetrieveImageCharacter[sign*VECTOR+i];
				    DisplayDistance.Format("%s%f",DisplayDistance,pDistance[sign]);///����ͼ������Ƴ̶�
					m_sDistance[displaynumber]=DisplayDistance;					///����ͼ������Ƴ̶�
					pDistance[sign]=OVER;             //�����ֵ

		}
///�º���

	delete[] pDistance;               //�ͷű���ŷʽ�����ڴ�
	time2=clock();
	  timecost=(double)(time2-time1)/CLOCKS_PER_SEC;
	  this->m_sRetrieveTime.Empty();
	  this->m_sRetrieveTime.Format("%s%f",m_sRetrieveTime,timecost);
 
///Ϊ��ʾ�ļ�����׼������ʾ�ļ���Ϊ��m_sDisplayFileName
	
	for(displaynumber=0;displaynumber<16;displaynumber++)//16����ʾͼ��
		  {
		  if(displaynumber>m_iOverSign-1)        //���ͼ����Ŀ�������˳�
				break;
		  CFile filedisplay;
		  filedisplay.Open(m_sRetrieveBmp[displaynumber],CFile::modeRead,NULL);
		  m_sDisplayFileName[displaynumber]=filedisplay.GetFileName();
		//		  filedisplay.Close();		  
		  }

//////////////////////////////////////////////////////////////////////////
	this->m_bRetrieve=TRUE;              //��������,�ñ�־λ
	 EndWaitCursor();
     UpdateAllViews(NULL);
	 */
	return true;
}
///������KeyBmpCharacterVqƥ���ͼ�񣬷���i
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
