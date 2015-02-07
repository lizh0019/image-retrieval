#ifndef _MATRIX_H
#define _MATRIX_H

#include <vector>
const double	MAX_ADJUST_VALUE	=	10e6;

using namespace std;

typedef vector <double> VDOUBLE;
typedef vector <VDOUBLE> TMatrix;
class CMatrix  
{	

	/************************************************************************
	*				the interface function of the class CMatrix 			*
	************************************************************************/
public:
	void InitializeMatrixData(double data,unsigned int nRow,unsigned int nCol);
	bool LoadDataFromDoubleFile(CString &sFullPathName,int iRow,int iCol);
	bool SaveDataDoubleToFile(CString &strFileName);
	TMatrix  CMatrix::GetMatrixPoint()
{
	return this->m_pTMatrix;
};
	double GetMatirxData_double(unsigned int iRow, unsigned int iCol)
	{
	return this->m_pTMatrix[iRow][iCol];	
	};
	unsigned int GetMatirxData_uint(unsigned int iRow,unsigned iCol)
	{	
	return ( unsigned int)this->m_pTMatrix[iRow][iCol];	
	};
	bool ReListByRow_Decrease(int iRow);
	void SetMatrixData(double dMatrix,unsigned int nRow,unsigned int nCol)
	{
		this->m_pTMatrix[nRow][nCol]=dMatrix;
	};
	void AddOneCol(double dData=0.0)
	{
	this->m_nCol++;
	//add every row,and initialize it to zero
	for(int i=0;i<m_nRow;i++)
		m_pTMatrix[i].push_back(dData);

	};
	void InitializeMatrixData(double *pMatrix,unsigned int iRow,unsigned int iCol);

	/////////////////////////////////////////////////////////////////////////
	// Construction and Destruction	
	CMatrix();

	CMatrix(double *pMatrix,unsigned int nRow,unsigned int nCol);
	CMatrix(double MatrixInitializeData,unsigned int nRow,unsigned int nCol);
	virtual ~CMatrix();


	/////////////////////////////////////////////////////////////////////////
	// According to the parameters nRow & nCol to construct a matrix
	CMatrix(unsigned int nRow, unsigned int nCol);

	bool LoadDataFromStringFile(CString& strFileName);

	/////////////////////////////////////////////////////////////////////////
	// Save the data from the CMatrix object to the specified file
	//
	bool SaveDataStringToFile(CString& strFileName);
	
	/////////////////////////////////////////////////////////////////////////
	// Get the matrix Row Number
	//
	unsigned int GetMatrixRowNumber() const
	{
		return m_nRow;
	}

	/////////////////////////////////////////////////////////////////////////
	// Get the matrix Colum Number
	//
	unsigned int GetMatrixColNumber() const
	{
		return m_nCol;
	}
	//set the row
	void SetMatrixRowNumber(unsigned int nRow);
	//set the col
	void SetMatrixColNumber(unsigned int nRow);

private:

	unsigned int m_nRow;			// 矩阵所拥有的行数
	unsigned int m_nCol;			// 矩阵所拥有的列数	
	TMatrix	m_pTMatrix;				// 指向矩阵的头指针
	vector<char> test;

};


#endif // _MATRIX_H