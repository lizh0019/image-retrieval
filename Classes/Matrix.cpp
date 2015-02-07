#include "stdafx.h"
#include "Matrix.h"
#include <math.h>
#include <stdlib.h>
//#include "alldef.h"
#include <conio.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix()
{
	m_nRow = 0;
	m_nCol = 0;

	m_pTMatrix.resize (m_nRow);
	for(unsigned int i=0; i < m_nRow; i++)
	{
		for(unsigned int j=0; j < m_nCol; j++)
		{
			m_pTMatrix[i].resize (m_nCol);
			m_pTMatrix[i][j] = (double) 0;
		}
	}
}

CMatrix::~CMatrix()
{	

}

CMatrix::CMatrix(double *pMatrix,unsigned int nRow,unsigned int nCol)
{	
	this->InitializeMatrixData(pMatrix,nRow,nCol);

}

CMatrix::CMatrix(double MatrixInitializeData,unsigned int nRow,unsigned int nCol)
{	
	// 动态分配二维数组
	TMatrix tMatrix;
	tMatrix.resize (nRow);

	for(unsigned int i=0; i < nRow; i++)
	{
		for(unsigned int j = 0; j < nCol; j++)
		{
	        tMatrix[i].resize(nCol);
			tMatrix[i][j] = 0.0;
		}
	}

	// 对对象变量赋值
	m_nRow	= nRow;
	m_nCol	= nCol;
	m_pTMatrix = tMatrix;

}
CMatrix::CMatrix(unsigned int nRow,unsigned int nCol)
{
	// 动态分配二维数组
	TMatrix tMatrix;
	tMatrix.resize (nRow);

	for(unsigned int i=0; i < nRow; i++)
	{
		for(unsigned int j=0; j < nCol; j++)
		{
	        tMatrix[i].resize(nCol);
			tMatrix[i][j] = (long double) 0.00001;
		}
	}

	// 对对象变量赋值
	m_nRow	= nRow;
	m_nCol	= nCol;
	m_pTMatrix = tMatrix;

}

bool CMatrix::LoadDataFromStringFile(CString& strFileName)
{
	CStdioFile dataFile;
	LPCTSTR	lpszFileName = "";

	// CString convert to LPCTSTR
	strFileName.TrimLeft ();
	strFileName.TrimRight ();
	//strFileName.Format (lpszFileName);

	lpszFileName = (LPCTSTR)strFileName;

	if(!dataFile.Open (lpszFileName,CFile::modeRead))// | CFile::typeText
	{
		::AfxMessageBox (TEXT("不能打开要读取数据的文件!"),MB_OK | MB_ICONERROR);
	//	dataFile.Close ();
		return FALSE;
	}

	// 用来存储提取文本文件中一行的数据
	CString	strData;				 
	// 用来记录文本文件中一共有多少行数据?
	unsigned int	nRow = 0;		

	/////////////////////////////////////////////////////////////////////////
	// Step 1: 得到文件的行列数目并根据文本文件的行列数目来设置对象(矩阵)的行
	// 列数目
	//

	while(dataFile.ReadString (strData) != FALSE)
	{
		++nRow;
	}

	// 根据文本文件的数据的行数设置对象(矩阵)的行数
	m_nRow = nRow;
	SetMatrixRowNumber(m_nRow);

	// 重新定位当前文件指针到文件开头
	dataFile.SeekToBegin ();

	dataFile.ReadString (strData);
	strData.TrimLeft ();
	strData.TrimRight ();

	TCHAR	SPACE_CHARACTER = ' ';
	// 用来记录文本文件中一行有多少列?
	unsigned int	nCol = 0;						
	
	// 空格符在字符串中的位置索引
	int nIndex = 0;

	do
	{
		nIndex = strData.Find (SPACE_CHARACTER);

		++nCol;

		// 提取字符串的子字符串,即提取一个double型实数数据
		//CString strDoubleNumber = strData.Left (nIndex);	

		// 将字符串转换为double型实数
		//double RealNumber = atof(strDoubleNumber);

		//int nTempNumber = strData.GetLength ();

		strData = strData.Right (strData.GetLength () - nIndex -1);

		// 去掉多余的空格
		strData.TrimLeft ();

		// Use for debugging
		//int nTempNum = strData.GetLength ();

	}while(nIndex != -1);

	// 根据文本文件的数据的列数设置对象(矩阵)的列数
	m_nCol = nCol;
	SetMatrixColNumber(m_nCol);

	// End of Getting the Rows and Cols of the Text File
	/////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////
	// Step 2: 根据文本文件中的数据对矩阵赋值,并检测每行的列数是否和第一行的
	// 列数相等,不相等提示出错信息
	//

	// 重新定位当前文件指针到文件开头
	dataFile.SeekToBegin ();

	// 对矩阵中的元素装入文本文件的数据
	for(unsigned int i=0; i < m_nRow; i++)
	{
		dataFile.ReadString (strData);
		strData.TrimLeft ();
		strData.TrimRight ();

		// 验证每行的列数是否与第一行的列数相等
		unsigned int nVerifyColNum = 0;

		do
		{
			nIndex = strData.Find (SPACE_CHARACTER);

			++nVerifyColNum;

			if(nIndex != -1)
			{
				// 提取字符串的子字符串,即提取一个double型实数数据
				CString strDoubleNumber = strData.Left (nIndex);	

				// 将字符串转换为double型实数
				double RealNumber = atof(strDoubleNumber);

				m_pTMatrix [i][nVerifyColNum - 1] = RealNumber;
				//int nTempNumber = strData.GetLength ();

				strData = strData.Right (strData.GetLength () - nIndex -1);

				// 去掉多余的空格
				strData.TrimLeft ();

				// Using for debugging
				//double nReadNumber = m_pTMatrix [i][nVerifyColNum - 1];

				// Using for debugging
				//int nTempNum = strData.GetLength ();
			}
			else
			{
				double RealNumber = atof(strData);

				m_pTMatrix [i][nVerifyColNum - 1] = RealNumber;
			}

		}while(nIndex != -1);

		if(nVerifyColNum != m_nCol)
		{
			CString strRowNumber;
			strRowNumber.Format("%d",i + 1);

			CString strColNumber;
			strColNumber.Format("%d",m_nCol);

			CString strVerifyColNumber;
			strVerifyColNumber.Format("%d",nVerifyColNum);

			CString strMessage =  CString(TEXT("文本文件第")) + strRowNumber + CString(TEXT("行一共有")) + strVerifyColNumber + CString(TEXT("列,与第一行中的列数")) + strColNumber + CString(TEXT("不相等!"));

			LPCTSTR lpszText = "";
			lpszText = (LPCTSTR)strMessage;

			//strMessage.FormatMessage (lpszText);
			//::AfxMessageBox (lpszText,MB_OK);


			::AfxMessageBox (lpszText,MB_OK | MB_ICONERROR);
			dataFile.Close ();
			return false;
		}


	}


	dataFile.Close ();

	return TRUE;
}


bool CMatrix::SaveDataStringToFile (CString& strFileName)
{
	CStdioFile dataFile;
	LPCTSTR	lpszFileName = "";

	// CString convert to LPCTSTR
	strFileName.TrimLeft ();
	strFileName.TrimRight ();

	lpszFileName = (LPCTSTR)strFileName;


	if(!dataFile.Open (lpszFileName,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText))
	{
		::AfxMessageBox(TEXT("不能创建文件!"),MB_OK | MB_ICONERROR);
		dataFile.Close ();
		return false;
	}
	
	dataFile.SeekToBegin();

	// 将对象(矩阵)中的数据写进文件
	for(unsigned int i=0; i < m_nRow; i++)
	{
		for(unsigned int j=0; j < m_nCol; j++)
		{
			 CString strRealNumber;

			 strRealNumber.Format ("%.3f  ", m_pTMatrix [i][j]);

			 // Using for debugging
			 //double nReadNumber = m_pTMatrix [i][j];

			 char *pBuffer = new char[strRealNumber.GetLength()];

			 memcpy(pBuffer,strRealNumber,strRealNumber.GetLength());

			 dataFile.Write (pBuffer,strRealNumber.GetLength ());

		}
		
		if( i != m_nRow - 1)
		{
			//char ReturnNewline[] = "\r\n";
			char ReturnNewline[] = "\n";
			
			dataFile.Write (ReturnNewline, (sizeof(ReturnNewline) - 1)/sizeof(char));
		}

	}


	dataFile.Close ();
	return true;
}



void CMatrix::InitializeMatrixData(double *pMatrix, unsigned int nRow, unsigned int nCol)
{
//	TMatrix tMatrix;
	m_pTMatrix.resize (nRow);
	m_nRow	= nRow;
	m_nCol	= nCol;

	int iNumber=0;
	unsigned int i,j;
	for( i=0; i < nRow; i++)
	{
		m_pTMatrix[i].resize(nCol);	
		for(j=0; j < nCol; j++)
		{    		
		m_pTMatrix[i][j] = pMatrix[iNumber++];
		}
		
	}
	// 对对象变量赋值

}


//iRow=0,1,2
bool CMatrix::ReListByRow_Decrease(int iRow)
{
	if(iRow>=m_nRow) return false;
	
	int i,j,k;
	double dTempleData;

	double dMaxdata=this->m_pTMatrix[iRow][0]; //max data
	int iTempMaxColNumber=0;  // the id
	if (m_nCol==0) return false;
	for(i=0;i<m_nCol-1;i++)
	{
		dMaxdata=this->m_pTMatrix[iRow][i]; //max data
		iTempMaxColNumber=i;  // the id	
		//find the maxcol
		for(j=i+1;j<m_nCol;j++)		
			if(this->m_pTMatrix[iRow][j]>this->m_pTMatrix[iRow][iTempMaxColNumber])		
				iTempMaxColNumber=j;		
		//end for j
			
		if (iTempMaxColNumber!=i)  //change the col i and j
		{
			for(k=0;k<m_nRow;k++)
			{
				dTempleData=this->m_pTMatrix[k][iTempMaxColNumber];  //iTempMaxColNumber->Temp
				this->m_pTMatrix[k][iTempMaxColNumber]=this->m_pTMatrix[k][i];//i->iTempMaxColNumber
				this->m_pTMatrix[k][i]=dTempleData;		//temp->i				
			}
		}
	}//end for :i
			
 return true;

}

void CMatrix::SetMatrixRowNumber(unsigned int nRow)
{
	m_nRow = nRow;

	m_pTMatrix.resize (m_nRow);
	for(unsigned int i=0; i < m_nRow; i++)
	{
			m_pTMatrix[i].resize (m_nCol);


	}

}
void CMatrix::SetMatrixColNumber(unsigned int nCol)
{
	m_nCol = nCol;

	m_pTMatrix.resize (m_nRow);
	for(unsigned int i=0; i < m_nRow; i++)
	{
			m_pTMatrix[i].resize (m_nCol);

	}

}

bool CMatrix::SaveDataDoubleToFile(CString &strFileName)
{
	CFile cWriteFile;
	if(cWriteFile.Open(strFileName,CFile::modeReadWrite|CFile::modeCreate)==false) return false;
	//save data for temple
	double *pTempleData=new double[this->m_nCol*m_nRow];
		for(int i=0;i<m_nRow;i++)
			for(int j=0;j<m_nCol;j++)
				pTempleData[i*m_nCol+j]=m_pTMatrix[i][j];

	cWriteFile.SeekToBegin();
	cWriteFile.WriteHuge(pTempleData,sizeof(double)*m_nCol*m_nRow);
	cWriteFile.Close();
	//end 
	delete[]pTempleData;
	return true;
}

bool CMatrix::LoadDataFromDoubleFile(CString &sFullPathName,int iRow,int iCol)
{
	CFile cWriteFile;
	if(cWriteFile.Open(sFullPathName,CFile::modeRead)==false) return false;
	double *pTemple=new double[iRow*iCol];
	if(cWriteFile.ReadHuge(pTemple,sizeof(double)*iRow*iCol)!=sizeof(double)*iRow*iCol) 
	{
		delete[]pTemple;
		cWriteFile.Close();
		return false;
	}
	cWriteFile.Close();
	this->InitializeMatrixData(pTemple,iRow,iCol);
/*
	for(int i=0;i<m_nRow;i++)
		for(int j=0;j<m_nCol;j++)
			this->m_pTMatrix[i][j]=pTemple[i*m_nCol+j];*/

	delete[]pTemple;
	return true;
}

void CMatrix::InitializeMatrixData(double data, unsigned int nRow, unsigned int nCol)
{

	TMatrix tMatrix;
	tMatrix.resize (nRow);
	for(unsigned int i=0; i < nRow; i++)
	{
		for(unsigned int j = 0; j < nCol; j++)
		{
	        tMatrix[i].resize(nCol);
			tMatrix[i][j] =data;
		}
	}
	// 对对象变量赋值
	m_nRow	= nRow;
	m_nCol	= nCol;
	m_pTMatrix = tMatrix;
}
