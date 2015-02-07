// ImageLoad.h: interface for the CImageLoad class.
#if !defined(__ImageLoad_h)
#define __ImageLoad_h
//#include "lib/CIMAGE.H"
#include "..\LIB\CIMAGE.H"	// Added by ClassView
#define  PI 3.1415926
class CImageLoad  
{
public:
	bool LoadImage(CString filename);

	void CloseImage();
//	bool GetComplex_256(double *pImageComplex,byte type);  //get the complex and the type is"type"
	int GetWidth();
	int GetHeight();
	byte* GetPixel_R();
	byte* GetPixel_G();
	byte* GetPixel_B();
	float * GetImageH();
	float * GetImageS();
	float * GetImageV();
	BOOL IsSucceed();
	bool LoadImageDialog();

	

	CImageLoad();
	virtual ~CImageLoad();

protected:
	void RGBToGray(byte *r,byte *g,byte *b,byte *gray,int height,int width);
	bool RGBToHSI(byte *r, byte *g, byte *b, float *h, float *s, float *v, int heigth, int width);

	void deleteMemory();
	byte *m_yR,*m_yG,*m_yB,*m_yGray;//R G B and gray
	float *m_fH,*m_fS,*m_fV;
	byte m_yR_threshold,m_yG_threshold,m_yB_threshold,m_yGray_threshold;  //the threshold of them
	int m_iImageWidth,m_iImageHeight; //height and width
	CString m_sFileName;  //file name
//	CImage m_image;  //image read 
	bool m_bLoadSuccess;
protected://other class
//	CImageProcess m_ImageProcess;
private:
};

#endif // define ImageLoad_h
