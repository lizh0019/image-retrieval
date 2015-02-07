#if !defined(_JPEGCP_)
#define _JPEGCP_

#include <windows.h>
#include <fstream.h>

#define FIXED_1 0x00010000
#define FIXED_half 0x00008000
#define LONG_TO_FIXED(l)	((l)*FIXED_1)
#define FLOAT_TO_FIXED(f)	((long)((f)*FIXED_1))
#define FIXED_TO_SHORT(f)	((short)((f)>>16))
#define FIXED_TO_BYTE(f)	((BYTE)((f)>>16))
#define FIXED_TO_LONG(f)	((f)>>16)

#define JPEGCPERR_NOERROR				0
#define JPEGCPERR_UNKNOWNERROR			1
#define JPEGCPERR_UNSUPPORTEDVERSION	2
#define JPEGCPERR_QTERROR				3
#define JPEGCPERR_FRAMEERROR			4
#define JPEGCPERR_HTERROR				5
#define JPEGCPERR_SOSERROR				6

#define IDCT_FLOAT		0
#define IDCT_INT		1
#define IDCT_MMX		2

typedef struct NODE
{	NODE *lNode;
	NODE *rNode;
	BOOL isLeave;
	unsigned char code;
}NODE;

typedef struct
{	unsigned char *stream;
	UINT bufIdx;
	UINT bitIdx;
	UINT remain;
}DECODE_PARAM;

class CHuffmanTable
{
private:
	NODE root;
private:
public:
	CHuffmanTable();
	~CHuffmanTable();
	BOOL addNode(UINT len,unsigned char c);
	BOOL addNode(NODE* node,UINT len,unsigned char c);
	void clear();
	void clearNode(NODE* node);
	BOOL deCode(DECODE_PARAM* pa,unsigned char *p);
public:
	friend class CJpeg;
};


typedef struct
{	UINT v,h;
	UINT qtID;
}COMPONENT;

typedef struct
{	UINT imgWidth,imgHeight;
	UINT bufWidth,bufHeight;
	int comNum;
	BYTE *image[5];
}JPEG_IMAGE_INFO;

class CJpeg
{
//private:
private:
	BOOL error;
	UINT errorCode;
	BOOL opened;
	UINT imgWidth,imgHeight;
	UINT bufWidth,bufHeight;
	UINT numOfCOM;
	UINT ri;
	UINT qt[4][64];
	CHuffmanTable htDC[4];
	CHuffmanTable htAC[4];
	COMPONENT com[6];
	UINT maxH,maxV;
	UINT unitNumH,unitNumV;
	BYTE *image[5];
	void (CJpeg::* pIdctFunc)(short*,BYTE*);
private:
	void init();
	void idctFloat(short* coef_block,BYTE *output_buf);
	void idctInt (short* coef_block,BYTE *output_buf);
	void domidct8x8llmW(short *inptr,int*,BYTE* outptr);
	void idctMMX(short* coef_block,BYTE *output_buf);
	void storeBlock(UINT comID,UINT num,BYTE *block,BYTE *img);
	void YCbCrToRGB();
	BOOL readQTable(ifstream &ifs);
	BOOL readHTable(ifstream &ifs);
	BOOL readSOF0(ifstream &ifs);
	BOOL readRI(ifstream &ifs);
	BOOL readSOS(ifstream &ifs);
public:
	CJpeg();
	CJpeg(LPCSTR fileName,UINT idctMode);
	~CJpeg();
	BOOL operator!();
	BOOL open(LPCSTR fileName,UINT idctMode);
	void getImageInfo(JPEG_IMAGE_INFO* info);
	void close();
	UINT getLastError();
public:
};

#endif