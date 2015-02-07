
#include "stdafx.h"
#include <math.h>
#include "cjpeg.h"
#define PI 3.14159535897932

extern void jpeg_idct8x8aan (short *src_result);

#define ICHG(c1,c2)		((((UINT)(c1))<<8) + (c2))
BYTE zigzag[64] =	
{0	,1	,8	,16	,9	,2	,3	,10	,
					 17	,24	,32	,25	,18	,11	,4	,5	,
					 12	,19	,26	,33	,40	,48	,41	,34	,
					 27	,20	,13	,6	,7	,14	,21	,28	,
					 35	,42	,49	,56	,57	,50	,43	,36	,
					 29	,22	,15	,23	,30	,37	,44	,51	,
					 58	,59	,52	,45	,38	,31	,39	,46	,
					 53	,60	,61	,54	,47	,55	,62	,63	
					};

CJpeg::CJpeg()
{	init();
}

CJpeg::CJpeg(LPCSTR fileName,UINT idctMode)
{	init();
	if(open(fileName,idctMode))
	{	opened = TRUE;
		error = FALSE;
	}
	else
	{	close();
		opened = FALSE;
		error = TRUE;
	}
}

void CJpeg::init()
{	int i;
	opened = FALSE;
	error = FALSE;
	errorCode = JPEGCPERR_NOERROR;
	for(i=0;i<5;i++)
		image[i] = NULL;
	maxH = 0 , maxV = 0;
	unitNumH = 0 , unitNumV = 0;
}
		
BOOL CJpeg::operator!()
{	return error;
}

UINT CJpeg::getLastError()
{	return errorCode;
}

BOOL CJpeg::open(LPCSTR fileName,UINT idctMode)
{
	unsigned char seg[2];

	unsigned char len[2];
	if(opened)
		return FALSE;
	init();
	if(idctMode == IDCT_FLOAT)
		pIdctFunc = idctFloat;
	else if(idctMode == IDCT_MMX)
		pIdctFunc = idctMMX;
	else
		pIdctFunc = idctInt;
	ifstream ifs(fileName,ios::binary|ios::nocreate);
	if(!ifs)
		return FALSE;

	ifs.read(seg,2);
	if(seg[0] != 0xff || seg[1] != 0xd8)
	{
		ifs.seekg(143);	//针对IREN的图像格式做出的修改	
		ifs.read(seg,2);
		if(seg[0] != 0xff || seg[1] != 0xd8)
		{
			return FALSE;
		}
	}

	while(1)
	{	ifs.read(seg,2);
		if(seg[0] != 0xff)
			goto error;
		while(seg[1] == 0xff)
		{	ifs.read(&seg[1],1);
		}
		switch(seg[1])
		{	case 0x01:
			case 0xd0:
			case 0xd1:
			case 0xd2:
			case 0xd3:
			case 0xd4:
			case 0xd5:
			case 0xd6:
			case 0xd7:
				break;
			case 0xc1:
			case 0xc2:
			case 0xc3:
			case 0xc5:
			case 0xc6:
			case 0xc7:
			case 0xc8:
			case 0xc9:
			case 0xca:
			case 0xcb:
			case 0xcc:
			case 0xcd:
			case 0xce:
			case 0xcf:
				goto error;
			case 0xdb:
				if(readQTable(ifs) == FALSE)
				{	errorCode = JPEGCPERR_QTERROR;
					goto error;
				}
				break;
			case 0xc0:
				if(readSOF0(ifs) == FALSE)
				{	errorCode = JPEGCPERR_FRAMEERROR;
					goto error;
				}
				break;
			case 0xdd:
				if(readRI(ifs) == FALSE)
				{	errorCode = JPEGCPERR_UNKNOWNERROR;
					goto error;
				}
				break;
			case 0xc4:
				if(readHTable(ifs) == FALSE)
				{	errorCode = JPEGCPERR_HTERROR;
					goto error;
				}
				break;
			case 0xda:
				if(readSOS(ifs) == FALSE)
				{	errorCode = JPEGCPERR_SOSERROR;
					goto error;
				}
				break;
			case 0xd9:
				YCbCrToRGB();
				return TRUE;
				break;
			default:
				ifs.read(len,2);
				ifs.seekg(ICHG(len[0],len[1])-2,ios::cur);
		}
		if(!ifs.good() || ifs.eof())
			goto error;
	}
	return TRUE;
error:
	return FALSE;
}

BOOL CJpeg::readQTable(ifstream &ifs)
{	unsigned char c;
	unsigned char len[2];
	int lenth,i;
	UINT jd,qtID;
	ifs.read(len,2);
	lenth = (int)(ICHG(len[0],len[1])-2);
	while(lenth > 0)
	{	ifs.read(&c,1);
		lenth--;
		qtID = c&0x0f , jd = c>>4;
		if(jd != 0 || qtID >= 4)
			return FALSE;
		for(i=0;i<64;i++)
		{	ifs.read(&c,1);
			qt[qtID][i] = c;
		}
		lenth -= 64;
	}
	if(lenth != 0)
		return FALSE;
	return TRUE;
}

BOOL CJpeg::readSOF0(ifstream &ifs)
{	unsigned char c;
	unsigned char len[2];
	int lenth;
	UINT i;
	ifs.read(len,2);
	lenth = (int)(ICHG(len[0],len[1])-2);
	ifs.read(&c,1);
	if(c != 8)
		return FALSE;
	ifs.read(len,2);
	imgHeight = ICHG(len[0],len[1]);
	ifs.read(len,2);
	imgWidth = ICHG(len[0],len[1]);
	if(imgWidth == 0 || imgHeight == 0)
		return FALSE;
	ifs.read(&c,1);
	numOfCOM = c;
	for(i=0;i<numOfCOM;i++)
	{	ifs.read(&c,1);
		if(c > 5)
			return FALSE;
		ifs.read(len,2);
		com[c].h = len[0]>>4 , com[c].v = len[0]&0x0f;
		com[c].qtID = len[1];
		if(com[c].h == 0 || com[c].v == 0)
			return FALSE;
		if(maxH < com[c].h)
			maxH = com[c].h;
		if(maxV < com[c].v)
			maxV = com[c].v;
	}
	unitNumH = (imgWidth+(maxH*8)-1)/(maxH*8);
	unitNumV = (imgHeight+(maxV*8)-1)/(maxV*8);
	bufWidth = unitNumH*maxH*8;
	bufHeight = unitNumV*maxV*8;
	for(i=0;i<numOfCOM;i++)
	{	if((image[i] = new BYTE[bufWidth*bufHeight]) == NULL)
			return FALSE;
	}
	return TRUE;
}

BOOL CJpeg::readRI(ifstream &ifs)
{	unsigned char len[2];
	UINT lenth;
	ifs.read(len,2);
	lenth = ICHG(len[0],len[1]);
	if(lenth != 4)
		return FALSE;
	ifs.read(len,2);
	ri = ICHG(len[0],len[1]);
	return TRUE;
}

BOOL CJpeg::readHTable(ifstream &ifs)
{	unsigned char c;
	unsigned char len[2];
	unsigned char cn[16];
	int lenth;
	UINT i,j;
	UINT htID,type;
	CHuffmanTable *h;
	ifs.read(len,2);
	lenth = (int)(ICHG(len[0],len[1])-2);
	while(lenth > 0)
	{	ifs.read(&c,1);
		lenth--;
		htID = c&0x0f , type = (c>>4)&0x01;
		if(htID >= 2)
			return FALSE;
		if(type == 0)
			h = &htDC[htID];
		else
			h = &htAC[htID];
		ifs.read(cn,16);
		lenth -= 16;
		for(i=0;i<16;i++)
		{	for(j=0;j<cn[i];j++)
			{	ifs.read(&c,1);
				lenth--;
				h->addNode(i+1,c);
			}
		}
	}
	if(lenth != 0)
		return FALSE;
	return TRUE;
}

#define NEXT_BYTE														\
	{	if(bitIdx == 0)													\
		{	if(cc[bufIndex] == 0xff)									\
			{	while(cc[bufIndex+1] == 0xff)							\
				{	bufIndex++;											\
					remainInBuf--;										\
				}														\
				if(cc[bufIndex+1] != 0)									\
					goto sync;											\
			}															\
			else if(cc[bufIndex] == 0 && cc[bufIndex-1] == 0xff)		\
			{	bufIndex++;												\
				remainInBuf--;											\
				if(cc[bufIndex] == 0xff)								\
				{	while(cc[bufIndex+1] == 0xff)						\
					{	bufIndex++;										\
						remainInBuf--;									\
					}													\
					if(cc[bufIndex+1] != 0)								\
						goto sync;										\
				}														\
			}															\
		}																\
	}

BOOL CJpeg::readSOS(ifstream &ifs)
{	unsigned char c;
	unsigned char len[2];
	UINT lenth,comNum;
	UINT i,j;
	int k,l;
	UINT comID[4],htDcID[4],htAcID[4],blockIdx[4];
	ifs.read(len,2);
	lenth = (int)(ICHG(len[0],len[1])-2);
	ifs.read(&c,1);
	if(c<1 || c>4)
		return FALSE;
	comNum = c;
	for(i=0;i<comNum;i++)
	{	ifs.read(&c,1);
		if(c > 5)
			return FALSE;
		comID[i] = c;
		ifs.read(&c,1);
		htDcID[i] = c>>4;
		htAcID[i] = c&0x0f;
		if(htDcID[i] > 4 || htAcID[i] > 4)
			return FALSE;		
	}
	ifs.seekg(3,ios::cur);
	UINT DCbk[4];
	UINT dcac[100];
	short dcacUZ[64];
	BYTE imgBlock[64];
	unsigned char cc[140];
	int remainInBuf=0,bitIdx=0;
	UINT bufIndex=0;
	BOOL readOK=FALSE;
	unsigned char cv;
	DECODE_PARAM param;
	BOOL retVal;
	blockIdx[0] = 0,blockIdx[1] = 0,blockIdx[2] = 0,blockIdx[3] = 0;
	DCbk[0] = 0,DCbk[1] = 0,DCbk[2] = 0,DCbk[3] = 0;
	param.stream = cc;
startScan:
	for(;;)
	{	for(i=0;i<comNum;i++)
		{	CHuffmanTable *htA,*htD;
			htD = htDC + htDcID[i];
			htA = htAC + htAcID[i];
			UINT ID = comID[i];
			for(j=0;j<com[ID].h*com[ID].v;j++)
			{	for(l=0;l<64;)
				{	if(remainInBuf<=30 && readOK==FALSE)
					{	for(k=0;k<remainInBuf;k++)
							cc[k] = cc[bufIndex+k];
						bufIndex = 0;
						ifs.read(cc+remainInBuf,100);
						remainInBuf += ifs.gcount();
						if(ifs.bad())
							return FALSE;
						if(ifs.eof())
						{	readOK = TRUE;
							ifs.clear();
						}
					}
					param.bufIdx = bufIndex;
					param.bitIdx = bitIdx;
					param.remain = remainInBuf;
					if(l == 0)
						retVal = htD->deCode(&param,&cv);
					else
						retVal = htA->deCode(&param,&cv);
					bitIdx = param.bitIdx;
					bufIndex = param.bufIdx;
					remainInBuf = param.remain;
					bitIdx = bitIdx % 8;
					if(remainInBuf <= 0)
						return FALSE;
					if(retVal == TRUE)
					{	UINT u,zn,gn,bno;
						unsigned char ct[4];
						int bn,bn1,it;
						if(l == 0)
						{	if(cv == 0)
								u = 0;
							else
							{	bn = (int)cv;
								it = 0;
								bno = bitIdx;
								NEXT_BYTE
								while(bn > 0 && it < 4)
								{	bn1 = 8-bitIdx;
									ct[it] = cc[bufIndex];
									if(bn >= bn1)
										bufIndex++,bitIdx=0,remainInBuf--;
									else
										bitIdx += bn;
									bn -= bn1;
									it++;
									NEXT_BYTE
								}
								u = (*((UINT*)ct));
								_asm mov	eax,u
								_asm bswap	eax
								_asm mov	u,eax
								u <<= bno;
								if(((INT)u) > 0)
									u = 0 - ((~u)>>(32 - cv));
								else
									u = u >> (32 - cv);
							}
							dcac[0] = DCbk[i] = DCbk[i] + u;
							l++;
						}
						else
						{	if(cv == 0)
							{	while(l < 64)
								{	dcac[l] = 0;
									l++;
								}
							}
							else
							{	UINT m;
								if(cv == 0xf0)
								{	for(m=0;m<16;m++)
									{	dcac[l] = 0;
										l++;
									}
								}
								else
								{	zn = cv>>4;
									gn = cv&0x0f;
									for(m=0;m<zn;m++)
									{	dcac[l] = 0;
										l++;
									}
									if(gn != 0)
									{	bn = (int)gn;
										it = 0;
										bno = bitIdx;
										NEXT_BYTE
										while(bn > 0 && it < 4)
										{	bn1 = 8-bitIdx;
											ct[it] = cc[bufIndex];
											if(bn >= bn1)
												bufIndex++,bitIdx=0,remainInBuf--;
											else
												bitIdx += bn;
											bn -= bn1;
											it++;
											NEXT_BYTE
										}
										u = (*((UINT*)ct));
										_asm mov	eax,u
										_asm bswap	eax
										_asm mov	u,eax
										u <<= bno;
										if(((INT)u) > 0)
											u = 0 - ((~u)>>(32 - gn));
										else
											u = u >> (32 - gn);
										dcac[l] = u;
										l++;
									}
								}
							}
						}
					}
					else
						goto sync;
				}
				if(l>64)
					goto sync;
				UINT *q = qt[com[ID].qtID];
				for(k=0;k<64;k++)
				{	dcac[k] = ((INT)dcac[k])*((INT)q[k]);
				}
				for(k=0;k<64;k++)
				{	dcacUZ[zigzag[k]] = (short)((INT)dcac[k]);
				}
				BYTE *b = imgBlock;
				(this->*pIdctFunc)(dcacUZ,b);
				storeBlock(ID,blockIdx[i],b,image[i]);
				blockIdx[i]++;
			}
		}
	}
sync:
	for(;;)
	{	unsigned char c1,c2;
		c1 = cc[bufIndex],c2 = cc[bufIndex+1];
		if(c1 == 0xff && c2 != 0xff && c2 != 0)
		{	if(c2<0xd0 || c2>0xd7)
			{	ifs.seekg(-remainInBuf,ios::cur);
				return TRUE;
			}
			else
			{	DCbk[0] = 0,DCbk[1] = 0,DCbk[2] = 0,DCbk[3] = 0;
				bufIndex += 2,bitIdx = 0,remainInBuf-=2;
				break;
			}
		}
		else
		{	if(remainInBuf<=30 && readOK==FALSE)
			{	for(k=0;k<remainInBuf;k++)
					cc[k] = cc[bufIndex+k];
				bufIndex = 0;
				ifs.read(cc+remainInBuf,100);
				remainInBuf += ifs.gcount();
				if(ifs.bad())
					return FALSE;
				if(ifs.eof())
				{	readOK = TRUE;
					ifs.clear();
				}
			}
			bufIndex++,remainInBuf--;
			if(remainInBuf <= 0)
				return TRUE;
			c1 = cc[bufIndex],c2 = cc[bufIndex+1];
		}
	}
	goto startScan;
}

void CJpeg::storeBlock(UINT comID,UINT bNum,BYTE *block,BYTE *img)
{	UINT x,y,ux,uy,bx,by,uNum,mh,mv,j,k,m,n;
	BYTE *b,*p,*pImg = img;
	uNum = bNum/(com[comID].h*com[comID].v);
	bNum = bNum%(com[comID].h*com[comID].v);
	ux = uNum%unitNumH , uy = uNum/unitNumH;
	bx = bNum%com[comID].h , by = bNum/com[comID].h;
	if(ux >= unitNumH || uy >= unitNumV)
		return;
	ux *= maxH*8 , uy *= maxV*8;
	mh = maxH/com[comID].h, mv = maxV/com[comID].v;
	bx *= mh*8 , by *= mv*8;
	x = ux+bx , y = uy+by;
	pImg += bufWidth*y+x;
	for(m=0;m<mv;m++)
	{	for(n=0;n<mh;n++)
		{	b = block;	
			for(j=0;j<8;j++)
			{	p = pImg + (m + j*mv) * bufWidth + n;
				for(k=0;k<8;k++)
				{	*p = *b++;
					p += mh;
				}
			}
		}
	}
}


#pragma warning( disable : 4035 )
inline long fixedMul(long a,long b)
{	__asm
	{	mov		eax,a
		mov		ebx,b
		imul	ebx
		shrd	eax,edx,16
	}
}

void CJpeg::YCbCrToRGB()
{	UINT j,k;
	BYTE *p1,*p2,*p3;
	long a,b,c,d,y,cb,cr,l,rr,gg,bb;
	if(numOfCOM != 3)
		return;
	p1 = image[0], p2 = image[1], p3 = image[2];
	a = FLOAT_TO_FIXED((float)1.402);
	b = FLOAT_TO_FIXED((float)0.34414);
	c = FLOAT_TO_FIXED((float)0.71414);
	d = FLOAT_TO_FIXED((float)1.772);
	l = LONG_TO_FIXED(128);
	for(j=0;j<bufHeight;j++)
	{	for(k=0;k<bufWidth;k++)
		{	y = LONG_TO_FIXED((long)(*p1));
			cb = LONG_TO_FIXED((long)(*p2)) - l;
			cr = LONG_TO_FIXED((long)(*p3)) - l;
			rr = FIXED_TO_LONG(y+fixedMul(a,cr));
			gg = FIXED_TO_LONG(y-fixedMul(b,cb)-fixedMul(c,cr));
			bb = FIXED_TO_LONG(y+fixedMul(d,cb));
			if(rr>255)
				rr = 255;
			else if(rr<0)
				rr = 0;
			if(gg>255)
				gg = 255;
			else if(gg<0)
				gg = 0;
			if(bb>255)
				bb = 255;
			else if(bb<0)
				bb = 0;
			*p1 = (BYTE)rr;
			*p2 = (BYTE)gg;
			*p3 = (BYTE)bb;
			p1++,p2++,p3++;
		}
	}
}

void CJpeg::getImageInfo(JPEG_IMAGE_INFO* info)
{	info->bufWidth = bufWidth;
	info->bufHeight = bufHeight;
	info->imgWidth = imgWidth;
	info->imgHeight = imgHeight;
	info->comNum = numOfCOM;
	info->image[0] = image[0];
	info->image[1] = image[1];
	info->image[2] = image[2];
	info->image[3] = image[3];
	info->image[4] = image[4];
}

void CJpeg::close()
{	int i;
	for(i=0;i<4;i++)
	{	htDC[i].clear();
		htAC[i].clear();
	}
	for(i=0;i<5;i++)
	if(image[i] != NULL)
	{	delete[] image[i];
		image[i] = NULL;
	}
	opened = FALSE;
}

CJpeg::~CJpeg()
{	close();
}

//*************************************************************
CHuffmanTable::CHuffmanTable()
{	root.lNode = NULL;
	root.rNode = NULL;
	root.isLeave = FALSE;
}

BOOL CHuffmanTable::addNode(UINT len,unsigned char c)
{	return addNode(&root,len,c);
}

BOOL CHuffmanTable::addNode(NODE* node,UINT len,unsigned char c)
{	if(len == 1)
	{	if(node->lNode == NULL)
		{	node->lNode = new NODE;
			node->lNode->lNode = NULL;
			node->lNode->rNode = NULL;
			node->lNode->code = c;
			node->lNode->isLeave = TRUE;
			return TRUE;
		}
		if(node->rNode == NULL)
		{	node->rNode = new NODE;
			node->rNode->lNode = NULL;
			node->rNode->rNode = NULL;
			node->rNode->code = c;
			node->rNode->isLeave = TRUE;
			return TRUE;
		}
		return FALSE;
	}
	else
	{	if(node->lNode == NULL)
		{	node->lNode = new NODE;
			node->lNode->lNode = NULL;
			node->lNode->rNode = NULL;
			node->lNode->isLeave = FALSE;
			return addNode(node->lNode,len-1,c);
		}
		if(node->lNode->isLeave == FALSE)
		{	if(addNode(node->lNode,len-1,c) == TRUE)
				return TRUE;
		}
		if(node->rNode == NULL)
		{	node->rNode = new NODE;
			node->rNode->lNode = NULL;
			node->rNode->rNode = NULL;
			node->rNode->isLeave = FALSE;
			return addNode(node->rNode,len-1,c);
		}
		if(node->rNode->isLeave == FALSE)
		{	return addNode(node->rNode,len-1,c);
		}
		return FALSE;
	}
}

void CHuffmanTable::clear()
{	if(root.lNode != NULL)
		clearNode(root.lNode);
	if(root.rNode != NULL)
		clearNode(root.rNode);
	root.lNode = NULL;
	root.rNode = NULL;
}

void CHuffmanTable::clearNode(NODE* node)
{	if(node->lNode != NULL)
		clearNode(node->lNode);
	if(node->rNode != NULL)
		clearNode(node->rNode);
	delete node;
}

BOOL CHuffmanTable::deCode(DECODE_PARAM* pa,unsigned char *p)
{	unsigned char uc;
	NODE *n = &root;
	unsigned char *stream = pa->stream + pa->bufIdx;
	UINT bufIdx,bufIdxBK;
	bufIdx = bufIdxBK = pa->bufIdx;
	UINT bitIdx = pa->bitIdx;
	uc = (*stream++);
	bufIdx++;
	if(uc == 0xff)
	{	while((*stream) == 0xff)
			stream++,bufIdx++;
		if((*stream) != 0)	
			return FALSE;
		else
			stream++,bufIdx++;
	}
	uc <<= bitIdx;
	for(;;)
	{	if(uc&0x80)
		{	n = n->rNode;
		}
		else
		{	n = n->lNode;
		}
		bitIdx++;
		if(n == NULL)
		{	n = &root;
			bitIdx = 8;
			goto ttt;
		}
		if(n->isLeave == TRUE)
		{	pa->bitIdx = bitIdx;
			if(bitIdx == 8)
			{	pa->bufIdx = bufIdx;
				pa->bitIdx = 0;
			}
			pa->remain -= pa->bufIdx - bufIdxBK;
			*p = n->code;
			return TRUE;
		}
ttt:
		if(bitIdx == 8)
		{	bitIdx = 0;
			pa->bufIdx = bufIdx;
			uc = *stream++;
			bufIdx++;
			if(uc == 0xff)
			{	while((*stream) == 0xff)
					stream++,bufIdx++;
				if((*stream) != 0)
				{	pa->remain -= pa->bufIdx - bufIdxBK;	
					return FALSE;
				}
				else
					stream++,bufIdx++;
			}
			continue;
		}
		uc <<= 1;
	}
	pa->remain -= pa->bufIdx - bufIdxBK;
	return FALSE;
}

CHuffmanTable::~CHuffmanTable()
{	
	clear();
}
