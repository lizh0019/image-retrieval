//********************************************************************************************
//idctInt()和idctFloat()函数摘自“The Independent JPEG Group's JPEG software”文档，由下面
//地址下载：ftp://ftp.simtel.net/pub/simtelnet/msdos/graphics/jpegsr6a.zip 并做了少量修改
//domidct8x8llmW()函数摘自http://developer.intel.com/ 并做了少量修改
//*******************************************************************************************

#include "stdafx.h"
#include "cjpeg.h"

#define NO_ZERO_ROW_TEST
#define BITS_IN_JSAMPLE 8

#define MAXJSAMPLE	255
#define CENTERJSAMPLE	128

#define CONST_BITS  13
#define PASS1_BITS  2

#define FIX_0_298631336  ((INT32)  2446)	/* FIX(0.298631336) */
#define FIX_0_390180644  ((INT32)  3196)	/* FIX(0.390180644) */
#define FIX_0_541196100  ((INT32)  4433)	/* FIX(0.541196100) */
#define FIX_0_765366865  ((INT32)  6270)	/* FIX(0.765366865) */
#define FIX_0_899976223  ((INT32)  7373)	/* FIX(0.899976223) */
#define FIX_1_175875602  ((INT32)  9633)	/* FIX(1.175875602) */
#define FIX_1_501321110  ((INT32)  12299)	/* FIX(1.501321110) */
#define FIX_1_847759065  ((INT32)  15137)	/* FIX(1.847759065) */
#define FIX_1_961570560  ((INT32)  16069)	/* FIX(1.961570560) */
#define FIX_2_053119869  ((INT32)  16819)	/* FIX(2.053119869) */
#define FIX_2_562915447  ((INT32)  20995)	/* FIX(2.562915447) */
#define FIX_3_072711026  ((INT32)  25172)	/* FIX(3.072711026) */

#define ONE	((INT32) 1)
#define RIGHT_SHIFT(x,shft)  \
	((shift_temp = (x)) < 0 ? \
	 (shift_temp >> (shft)) | ((~((INT32) 0)) << (32-(shft))) : \
	 (shift_temp >> (shft)))
#define DESCALE(x,n)  RIGHT_SHIFT((x) + (ONE << ((n)-1)), n)
#define RANGE_MASK  (MAXJSAMPLE * 4 + 3) /* 2 bits wider than legal samples */
#define RANGE_LIMIT(i) \
		if((i) > MAXJSAMPLE)	\
			(i) = MAXJSAMPLE;	\
		else if((i) < 0)	\
			(i) = 0

void CJpeg::idctInt(short* coef_block,BYTE *output_buf)
{	INT32 tmp0, tmp1, tmp2, tmp3;
	INT32 tmp10, tmp11, tmp12, tmp13;
	INT32 z1, z2, z3, z4, z5;
	int itp;
	short *inptr;
	int * wsptr;
	char *outptr;
	int ctr;
	int workspace[64];
	INT32 shift_temp;

	inptr = coef_block;
	wsptr = workspace;
	for (ctr = 8; ctr > 0; ctr--)
	{	if ((inptr[8] | inptr[16] | inptr[24] | inptr[32] | inptr[40] | inptr[48] |
				inptr[56]) == 0) 
		{	int dcval = inptr[0] << PASS1_BITS;
		    wsptr[0] = dcval;
		    wsptr[8] = dcval;
		    wsptr[16] = dcval;
		    wsptr[24] = dcval;
		    wsptr[32] = dcval;
		    wsptr[40] = dcval;
		    wsptr[48] = dcval;
		    wsptr[56] = dcval;
		    inptr++;
		    wsptr++;
		    continue;
	    }
	    z2 = inptr[16];
	    z3 = inptr[48];
	    z1 = (z2 + z3)*FIX_0_541196100;
	    tmp2 = z1 + z3*(- FIX_1_847759065);
	    tmp3 = z1 + z2*FIX_0_765366865;
	    z2 = inptr[0];
	    z3 = inptr[32];
	    tmp0 = (z2 + z3) << CONST_BITS;
	    tmp1 = (z2 - z3) << CONST_BITS;
	    tmp10 = tmp0 + tmp3;
	    tmp13 = tmp0 - tmp3;
	    tmp11 = tmp1 + tmp2;
	    tmp12 = tmp1 - tmp2;
	    tmp0 = inptr[56];
	    tmp1 = inptr[40];
	    tmp2 = inptr[24];
	    tmp3 = inptr[8];
	    z1 = tmp0 + tmp3;
	    z2 = tmp1 + tmp2;
	    z3 = tmp0 + tmp2;
	    z4 = tmp1 + tmp3;
	    z5 = (z3 + z4) * FIX_1_175875602; 
	    tmp0 = tmp0 * FIX_0_298631336; 
	    tmp1 = tmp1 * FIX_2_053119869;
	    tmp2 = tmp2 * FIX_3_072711026;
	    tmp3 = tmp3 * FIX_1_501321110;
	    z1 = z1 * (- FIX_0_899976223);
	    z2 = z2 * (- FIX_2_562915447);
	    z3 = z3 * (- FIX_1_961570560);
	    z4 = z4 * (- FIX_0_390180644);
	    z3 += z5;
	    z4 += z5;
	    tmp0 += z1 + z3;
	    tmp1 += z2 + z4;
	    tmp2 += z2 + z3;
	    tmp3 += z1 + z4;
	    wsptr[0] = (int) DESCALE(tmp10 + tmp3, CONST_BITS-PASS1_BITS);
	    wsptr[56] = (int) DESCALE(tmp10 - tmp3, CONST_BITS-PASS1_BITS);
	    wsptr[8] = (int) DESCALE(tmp11 + tmp2, CONST_BITS-PASS1_BITS);
	    wsptr[48] = (int) DESCALE(tmp11 - tmp2, CONST_BITS-PASS1_BITS);
	    wsptr[16] = (int) DESCALE(tmp12 + tmp1, CONST_BITS-PASS1_BITS);
	    wsptr[40] = (int) DESCALE(tmp12 - tmp1, CONST_BITS-PASS1_BITS);
	    wsptr[24] = (int) DESCALE(tmp13 + tmp0, CONST_BITS-PASS1_BITS);
	    wsptr[32] = (int) DESCALE(tmp13 - tmp0, CONST_BITS-PASS1_BITS);
	    inptr++;
	    wsptr++;
	}
	wsptr = workspace;
	for (ctr = 0; ctr < 8; ctr++) {
    outptr = (char*)(output_buf + ctr*8);
#ifndef NO_ZERO_ROW_TEST
    if ((wsptr[1] | wsptr[2] | wsptr[3] | wsptr[4] | wsptr[5] | wsptr[6] | wsptr[7]) == 0)
	{	char dcval;
		itp = (int) DESCALE((INT32) wsptr[0], PASS1_BITS+3)+128;
		if(itp > MAXJSAMPLE)
			itp = MAXJSAMPLE;
		else if(itp < 0)
			itp = 0;
		dcval = (char)itp;
	    outptr[0] = dcval;
		outptr[1] = dcval;
	    outptr[2] = dcval;
		outptr[3] = dcval;
	    outptr[4] = dcval;
		outptr[5] = dcval;
	    outptr[6] = dcval;
		outptr[7] = dcval;
	    wsptr += 8;
		continue;
	}
#endif
    z2 = (INT32) wsptr[2];
    z3 = (INT32) wsptr[6];
    z1 = (z2 + z3) * FIX_0_541196100;
    tmp2 = z1 + z3 * (- FIX_1_847759065);
    tmp3 = z1 + z2 * FIX_0_765366865;
    tmp0 = ((INT32) wsptr[0] + (INT32) wsptr[4]) << CONST_BITS;
    tmp1 = ((INT32) wsptr[0] - (INT32) wsptr[4]) << CONST_BITS;
    tmp10 = tmp0 + tmp3;
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;
    tmp0 = (INT32) wsptr[7];
    tmp1 = (INT32) wsptr[5];
    tmp2 = (INT32) wsptr[3];
    tmp3 = (INT32) wsptr[1];
    z1 = tmp0 + tmp3;
    z2 = tmp1 + tmp2;
    z3 = tmp0 + tmp2;
    z4 = tmp1 + tmp3;
    z5 = (z3 + z4) * FIX_1_175875602;
    tmp0 = tmp0 * FIX_0_298631336;
    tmp1 = tmp1 * FIX_2_053119869;
    tmp2 = tmp2 * FIX_3_072711026;
    tmp3 = tmp3 * FIX_1_501321110;
    z1 = z1 * (- FIX_0_899976223);
    z2 = z2 * (- FIX_2_562915447);
    z3 = z3 * (- FIX_1_961570560);
    z4 = z4 * (- FIX_0_390180644);
    z3 += z5;
    z4 += z5;
    tmp0 += z1 + z3;
    tmp1 += z2 + z4;
    tmp2 += z2 + z3;
    tmp3 += z1 + z4;
    itp = (int) DESCALE(tmp10 + tmp3,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[0] = (char)itp;
    itp = (int) DESCALE(tmp10 - tmp3,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[7] = (char)itp;
    itp = (int) DESCALE(tmp11 + tmp2,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[1] = (char)itp;
    itp = (int) DESCALE(tmp11 - tmp2,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[6] = (char)itp;
    itp = (int) DESCALE(tmp12 + tmp1,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[2] = (char)itp;
    itp = (int) DESCALE(tmp12 - tmp1,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[5] = (char)itp;
    itp = (int) DESCALE(tmp13 + tmp0,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[3] = (char)itp;
    itp = (int) DESCALE(tmp13 - tmp0,CONST_BITS+PASS1_BITS+3)+128;
	RANGE_LIMIT(itp);
	outptr[4] = (char)itp;
    wsptr += 8;
  }
}

void CJpeg::idctFloat(short* coef_block,BYTE *output_buf)
{	float tmp0, tmp1, tmp2, tmp3;
	float tmp10, tmp11, tmp12, tmp13;
	float z1, z2, z3, z4, z5;
	int itp;
	short *inptr;
	float * wsptr;
	char *outptr;
	int ctr;
	float workspace[64];
	INT32 shift_temp;

	inptr = coef_block;
	wsptr = workspace;
	for (ctr = 8; ctr > 0; ctr--)
	{	if ((inptr[8] | inptr[16] | inptr[24] | inptr[32] | inptr[40] | inptr[48] |
				inptr[56]) == 0) 
		{	float dcval = inptr[0];
		    wsptr[0] = dcval;
		    wsptr[8] = dcval;
		    wsptr[16] = dcval;
		    wsptr[24] = dcval;
		    wsptr[32] = dcval;
		    wsptr[40] = dcval;
		    wsptr[48] = dcval;
		    wsptr[56] = dcval;
		    inptr++;
		    wsptr++;
		    continue;
	    }
	    z2 = inptr[16];
	    z3 = inptr[48];
	    z1 = (z2 + z3)*(float)0.541196100;
	    tmp2 = z1 + z3*(float)(-1.847759065);
	    tmp3 = z1 + z2*(float)0.765366865;
	    z2 = inptr[0];
	    z3 = inptr[32];
	    tmp0 = (z2 + z3);
	    tmp1 = (z2 - z3);
	    tmp10 = tmp0 + tmp3;
	    tmp13 = tmp0 - tmp3;
	    tmp11 = tmp1 + tmp2;
	    tmp12 = tmp1 - tmp2;
	    tmp0 = inptr[56];
	    tmp1 = inptr[40];
	    tmp2 = inptr[24];
	    tmp3 = inptr[8];
	    z1 = tmp0 + tmp3;
	    z2 = tmp1 + tmp2;
	    z3 = tmp0 + tmp2;
	    z4 = tmp1 + tmp3;
	    z5 = (z3 + z4) * (float)1.175875602; 
	    tmp0 = tmp0 * (float)0.298631336; 
	    tmp1 = tmp1 * (float)2.053119869;
	    tmp2 = tmp2 * (float)3.072711026;
	    tmp3 = tmp3 * (float)1.501321110;
	    z1 = z1 * (float)(-0.899976223);
	    z2 = z2 * (float)(-2.562915447);
	    z3 = z3 * (float)(-1.961570560);
	    z4 = z4 * (float)(-0.390180644);
	    z3 += z5;
	    z4 += z5;
	    tmp0 += z1 + z3;
	    tmp1 += z2 + z4;
	    tmp2 += z2 + z3;
	    tmp3 += z1 + z4;
	    wsptr[0] = tmp10 + tmp3;
	    wsptr[56] = tmp10 - tmp3;
	    wsptr[8] = tmp11 + tmp2;
	    wsptr[48] = tmp11 - tmp2;
	    wsptr[16] = tmp12 + tmp1;
	    wsptr[40] = tmp12 - tmp1;
	    wsptr[24] = tmp13 + tmp0;
	    wsptr[32] = tmp13 - tmp0;
	    inptr++;
	    wsptr++;
	}
	wsptr = workspace;
	for (ctr = 0; ctr < 8; ctr++) {
    outptr = (char*)(output_buf + ctr*8);
    z2 = wsptr[2];
    z3 = wsptr[6];
    z1 = (z2 + z3) * (float)0.541196100;
    tmp2 = z1 + z3 * (float)(-1.847759065);
    tmp3 = z1 + z2 * (float)0.765366865;
    tmp0 = wsptr[0] + wsptr[4];
    tmp1 = wsptr[0] - wsptr[4];
    tmp10 = tmp0 + tmp3;
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;
    tmp0 = wsptr[7];
    tmp1 = wsptr[5];
    tmp2 = wsptr[3];
    tmp3 = wsptr[1];
    z1 = tmp0 + tmp3;
    z2 = tmp1 + tmp2;
    z3 = tmp0 + tmp2;
    z4 = tmp1 + tmp3;
    z5 = (z3 + z4) * (float)1.175875602;
    tmp0 = tmp0 * (float)0.298631336;
    tmp1 = tmp1 * (float)2.053119869;
    tmp2 = tmp2 * (float)3.072711026;
    tmp3 = tmp3 * (float)1.501321110;
    z1 = z1 * (float)(-0.899976223);
    z2 = z2 * (float)(-2.562915447);
    z3 = z3 * (float)(-1.961570560);
    z4 = z4 * (float)(-0.390180644);
    z3 += z5;
    z4 += z5;
    tmp0 += z1 + z3;
    tmp1 += z2 + z4;
    tmp2 += z2 + z3;
    tmp3 += z1 + z4;
    itp = (int) DESCALE((INT32)(tmp10 + tmp3),3)+128;
	RANGE_LIMIT(itp);
	outptr[0] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp10 - tmp3),3)+128;
	RANGE_LIMIT(itp);
	outptr[7] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp11 + tmp2),3)+128;
	RANGE_LIMIT(itp);
	outptr[1] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp11 - tmp2),3)+128;
	RANGE_LIMIT(itp);
	outptr[6] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp12 + tmp1),3)+128;
	RANGE_LIMIT(itp);
	outptr[2] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp12 - tmp1),3)+128;
	RANGE_LIMIT(itp);
	outptr[5] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp13 + tmp0),3)+128;
	RANGE_LIMIT(itp);
	outptr[3] = (char)itp;
    itp = (int) DESCALE((INT32)(tmp13 - tmp0),3)+128;
	RANGE_LIMIT(itp);
	outptr[4] = (char)itp;
    wsptr += 8;
  }
}

void CJpeg::idctMMX(short* coef_block,BYTE *output_buf)
{	int workspace[64+4];
	domidct8x8llmW(coef_block, workspace, output_buf);
}

static	__int64 fix_029_n089n196	= 0x098ea46e098ea46e;
	static	__int64 fix_n196_n089		= 0xc13be333c13be333;
	static	__int64 fix_205_n256n039	= 0x41b3a18141b3a181;
	static	__int64 fix_n039_n256		= 0xf384adfdf384adfd;
	static	__int64 fix_307n256_n196	= 0x1051c13b1051c13b;
	static	__int64 fix_n256_n196		= 0xadfdc13badfdc13b;
	static	__int64 fix_150_n089n039	= 0x300bd6b7300bd6b7;
	static	__int64 fix_n039_n089		= 0xf384e333f384e333;
	static	__int64 fix_117_117			= 0x25a125a125a125a1;
	static	__int64 fix_054_054p076		= 0x115129cf115129cf;
	static	__int64 fix_054n184_054		= 0xd6301151d6301151;
	static	__int64 fix_054n184 		= 0xd630d630d630d630;
	static	__int64 fix_054				= 0x1151115111511151;
	static	__int64 fix_054p076			= 0x29cf29cf29cf29cf;
	static	__int64 fix_n196p307n256	= 0xd18cd18cd18cd18c;
	static	__int64 fix_n089n039p150	= 0x06c206c206c206c2;
	static	__int64 fix_n256			= 0xadfdadfdadfdadfd;
	static	__int64 fix_n039			= 0xf384f384f384f384;
	static	__int64 fix_n256n039p205	= 0xe334e334e334e334;
	static	__int64 fix_n196			= 0xc13bc13bc13bc13b;
	static	__int64 fix_n089			= 0xe333e333e333e333;
	static	__int64 fixn089n196p029		= 0xadfcadfcadfcadfc;
	static  __int64 const_0x2xx8		= 0x0000010000000100;
	static  __int64 const_0x0808		= 0x0808080808080808;
void CJpeg::domidct8x8llmW(short *inptr,int *wsptr,BYTE* outptr)
{	
	__asm{
	mov		ebx, inptr
	mov		esi, wsptr
	add		esi, 0x07		;align wsptr to qword
	and		esi, 0xfffffff8	;align wsptr to qword
	mov		eax, esi
	/* Pass 1. */
	movq		mm0, [ebx + 8*4]	;p1(1,0)
    movq		mm1, [ebx + 8*12]	;p1(2,0)
	movq		mm6, [ebx + 8*0]	;p1(5,0)
	movq		mm2, mm0			;p1(3,0)
	movq		mm7, [ebx + 8*8]	;p1(6,0)
	punpcklwd	mm0, mm1			;p1(3,1)
	movq		mm4, mm0			;p1(3,2)
	punpckhwd	mm2, mm1			;p1(3,4)
	pmaddwd		mm0, fix_054n184_054;p1(3,3)
	movq		mm5, mm2			;p1(3,5)
	pmaddwd		mm2, fix_054n184_054;p1(3,6)
	pxor		mm1, mm1			;p1(7,0)
	pmaddwd		mm4, fix_054_054p076;p1(4,0)
	punpcklwd   mm1, mm6			;p1(7,1)
	pmaddwd		mm5, fix_054_054p076;p1(4,1)
	psrad		mm1, 3				;p1(7,2)
	pxor		mm3, mm3			;p1(7,3)
	punpcklwd	mm3, mm7			;p1(7,4)
	psrad		mm3, 3				;p1(7,5)
	paddd		mm1, mm3			;p1(7,6)
	movq		mm3, mm1			;p1(7,7)	
	paddd		mm1, mm4			;p1(7,8)
	psubd		mm3, mm4			;p1(7,9)
	movq		[esi + 8*16], mm1	;p1(7,10)
	pxor		mm4, mm4			;p1(7,12)
	movq		[esi + 8*22], mm3	;p1(7,11)
	punpckhwd	mm4, mm6			;p1(7,13)
	psrad		mm4, 3				;p1(7,14)
	pxor		mm1, mm1			;p1(7,15)
	punpckhwd	mm1, mm7			;p1(7,16)
	psrad		mm1, 3				;p1(7,17)
	paddd		mm4, mm1			;p1(7,18)
	movq		mm3, mm4			;p1(7,19)	
	pxor		mm1, mm1			;p1(8,0)
	paddd		mm3, mm5			;p1(7,20)
	punpcklwd	mm1, mm6			;p1(8,1)
	psubd		mm4, mm5			;p1(7,21)
	psrad		mm1, 3				;p1(8,2)
	movq		[esi + 8*17], mm3	;p1(7,22)
	pxor		mm5, mm5			;p1(8,3)
	movq		[esi + 8*23], mm4	;p1(7,23)
	punpcklwd	mm5, mm7			;p1(8,4)
	psrad		mm5, 3				;p1(8,5)
	pxor		mm4, mm4			;p1(8,12)
	psubd		mm1, mm5			;p1(8,6)	
	punpckhwd	mm4, mm6			;p1(8,13)
	movq		mm3, mm1			;p1(8,7)
	psrad		mm4, 3				;p1(8,14)
	paddd		mm1, mm0			;p1(8,8)
	pxor		mm5, mm5			;p1(8,15)
	psubd		mm3, mm0			;p1(8,9)
	movq		mm0, [ebx + 8*14]	;p1(9,0)
	punpckhwd	mm5, mm7			;p1(8,16)
	movq		[esi + 8*18], mm1	;p1(8,10)
	psrad		mm5, 3				;p1(8,17)
	movq		[esi + 8*20], mm3	;p1(8,11)
	psubd		mm4, mm5			;p1(8,18)
	movq		mm3, mm4			;p1(8,19)
	movq		mm1, [ebx + 8*6]	;p1(10,0)
	paddd		mm3, mm2			;p1(8,20)
	psubd		mm4, mm2			;p1(8,21)
	movq		mm5, mm0			;p1(11,1)
	movq		[esi + 8*21], mm4	;p1(8,23)
	movq		[esi + 8*19], mm3	;p1(8,22)
	movq		mm4, mm0			;p1(11,0)
	punpcklwd	mm4, mm1			;p1(11,2)
	movq		mm2, [ebx + 8*10]	;p1(12,0)
	punpckhwd	mm5, mm1			;p1(11,4)	
	movq		mm3, [ebx + 8*2]	;p1(13,0)
	movq		mm6, mm2			;p1(14,0)
	pmaddwd		mm4, fix_117_117	;p1(11,3)
	movq		mm7, mm2			;p1(14,1)
	pmaddwd		mm5, fix_117_117	;p1(11,5)
	punpcklwd	mm6, mm3			;p1(14,2)
	pmaddwd		mm6, fix_117_117	;p1(14,3)
	punpckhwd	mm7, mm3			;p1(14,4)
	pmaddwd		mm7, fix_117_117	;p1(14,5)
	paddd		mm4, mm6			;p1(15,0)
	paddd		mm5, mm7			;p1(15,1)
   	movq		[esi+8*24], mm4		;p1(15,2)
	movq		[esi+8*25], mm5		;p1(15,3)
	movq		mm6, mm0				;p1(16,0)
	movq		mm7, mm3				;p1(16,3)
	punpcklwd	mm6, mm2				;p1(16,1)
	punpcklwd	mm7, mm3				;p1(16,4)
	pmaddwd		mm6, fix_n039_n089		;p1(16,2)
	pmaddwd		mm7, fix_150_n089n039	;p1(16,5)
	movq		mm4, mm0				;p1(16,12)
	paddd		mm6, [esi+8*24]			;p1(16,6)
	punpckhwd	mm4, mm2				;p1(16,13)
	paddd		mm6, mm7				;p1(16,7)
	pmaddwd		mm4, fix_n039_n089		;p1(16,14)
	movq		mm7, mm6				;p1(16,8)
	paddd		mm4, [esi+8*25]			;p1(16,18)
	movq		mm5, mm3				;p1(16,15)
	paddd		mm6, [esi + 8*16]		;p1(16,9)
	punpckhwd	mm5, mm3				;p1(16,16)
	paddd		mm6, const_0x2xx8		;p1(16,10)
	psrad		mm6, 9					;p1(16,11)
	pmaddwd		mm5, fix_150_n089n039	;p1(16,17)
	paddd		mm4, mm5				;p1(16,19)
	movq		mm5, mm4				;p1(16,20)
	paddd		mm4, [esi + 8*17]		;p1(16,21)
	paddd		mm4, const_0x2xx8		;p1(16,22)
	psrad		mm4, 9					;p1(16,23)
	packssdw	mm6, mm4				;p1(16,24)
	movq		[esi + 8*0], mm6		;p1(16,25)
	movq		mm4, [esi + 8*16]		;p1(16,26)
	psubd		mm4, mm7				;p1(16,27)
	movq		mm6, [esi + 8*17]		;p1(16,30)
	paddd		mm4, const_0x2xx8		;p1(16,28)
	movq		mm7, mm1				;p1(17,3)
	psrad		mm4, 9					;p1(16,29)
	psubd		mm6, mm5				;p1(16,31)
	paddd		mm6, const_0x2xx8		;p1(16,32)
	punpcklwd	mm7, mm1				;p1(17,4)
	pmaddwd		mm7, fix_307n256_n196	;p1(17,5)
	psrad		mm6, 9					;p1(16,33)
	packssdw	mm4, mm6				;p1(16,34)
	movq		[esi + 8*14], mm4		;p1(16,35)
	movq		mm6, mm0				;p1(17,0)
	movq		mm4, mm0				;p1(17,12)
	punpcklwd	mm6, mm2				;p1(17,1)
	punpckhwd	mm4, mm2				;p1(17,13)
	pmaddwd		mm6, fix_n256_n196		;p1(17,2)
	movq		mm5, mm1				;p1(17,15)
	paddd		mm6, [esi+8*24]			;p1(17,6)
	punpckhwd	mm5, mm1				;p1(17,16)
	paddd		mm6, mm7				;p1(17,7)
	pmaddwd		mm4, fix_n256_n196		;p1(17,14)
	movq		mm7, mm6				;p1(17,8)
	pmaddwd		mm5, fix_307n256_n196	;p1(17,17)
	paddd		mm6, [esi + 8*18]		;p1(17,9)
	paddd		mm6, const_0x2xx8		;p1(17,10)
	psrad		mm6, 9					;p1(17,11)
	paddd		mm4, [esi+8*25]			;p1(17,18)
	paddd		mm4, mm5				;p1(17,19)
	movq		mm5, mm4				;p1(17,20)
	paddd		mm4, [esi + 8*19]		;p1(17,21)
	paddd		mm4, const_0x2xx8		;p1(17,22)
	psrad		mm4, 9					;p1(17,23)
	packssdw	mm6, mm4				;p1(17,24)
	movq		[esi + 8*2], mm6		;p1(17,25)
	movq		mm4, [esi + 8*18]		;p1(17,26)
	movq		mm6, [esi + 8*19]		;p1(17,30)
	psubd		mm4, mm7				;p1(17,27)
	paddd		mm4, const_0x2xx8		;p1(17,28)
	psubd		mm6, mm5				;p1(17,31)
	psrad		mm4, 9					;p1(17,29)
	paddd		mm6, const_0x2xx8		;p1(17,32)
	psrad		mm6, 9					;p1(17,33)
	movq		mm7, mm2				;p1(18,3)
	packssdw	mm4, mm6				;p1(17,34)
	movq		[esi + 8*12], mm4		;p1(17,35)
	movq		mm6, mm1				;p1(18,0)
	punpcklwd	mm7, mm2				;p1(18,4)
	punpcklwd	mm6, mm3				;p1(18,1)
	pmaddwd		mm7, fix_205_n256n039	;p1(18,5)
	pmaddwd		mm6, fix_n039_n256		;p1(18,2)
	movq		mm4, mm1				;p1(18,12)
	paddd		mm6, [esi+8*24]			;p1(18,6)
	punpckhwd	mm4, mm3				;p1(18,13)
	paddd		mm6, mm7				;p1(18,7)
	pmaddwd		mm4, fix_n039_n256		;p1(18,14)
	movq		mm7, mm6				;p1(18,8)
	movq		mm5, mm2				;p1(18,15)
	paddd		mm6, [esi + 8*20]		;p1(18,9)
	punpckhwd	mm5, mm2				;p1(18,16)
	paddd		mm6, const_0x2xx8		;p1(18,10)
	psrad		mm6, 9					;p1(18,11)
	pmaddwd		mm5, fix_205_n256n039	;p1(18,17)
	paddd		mm4, [esi+8*25]			;p1(18,18)
	paddd		mm4, mm5				;p1(18,19)
	movq		mm5, mm4				;p1(18,20)
	paddd		mm4, [esi + 8*21]		;p1(18,21)
	paddd		mm4, const_0x2xx8		;p1(18,22)
	psrad		mm4, 9					;p1(18,23)
	packssdw	mm6, mm4				;p1(18,24)
	movq		[esi + 8*4], mm6		;p1(18,25)
	movq		mm4, [esi + 8*20]		;p1(18,26)
	psubd		mm4, mm7				;p1(18,27)
	paddd		mm4, const_0x2xx8		;p1(18,28)
	movq		mm7, mm0				;p1(19,3)
	psrad		mm4, 9					;p1(18,29)
	movq		mm6, [esi + 8*21]		;p1(18,30)
	psubd		mm6, mm5				;p1(18,31)
	punpcklwd	mm7, mm0				;p1(19,4)
	paddd		mm6, const_0x2xx8		;p1(18,32)
	psrad		mm6, 9					;p1(18,33)
	pmaddwd		mm7, fix_029_n089n196	;p1(19,5)
	packssdw	mm4, mm6				;p1(18,34)
	movq		[esi + 8*10], mm4		;p1(18,35)
	movq		mm6, mm3				;p1(19,0)
	punpcklwd	mm6, mm1				;p1(19,1)	
	movq		mm5, mm0				;p1(19,15)
	pmaddwd		mm6, fix_n196_n089		;p1(19,2)
	punpckhwd	mm5, mm0				;p1(19,16)
	paddd		mm6, [esi+8*24]			;p1(19,6)
	movq		mm4, mm3				;p1(19,12)
	paddd		mm6, mm7				;p1(19,7)
	punpckhwd	mm4, mm1				;p1(19,13)
	movq		mm7, mm6				;p1(19,8)
	pmaddwd		mm4, fix_n196_n089  	;p1(19,14)
	paddd		mm6, [esi + 8*22]		;p1(19,9)
	pmaddwd		mm5, fix_029_n089n196	;p1(19,17)
	paddd		mm6, const_0x2xx8		;p1(19,10)
	psrad		mm6, 9					;p1(19,11)
	paddd		mm4, [esi+8*25]			;p1(19,18)
	paddd		mm4, mm5				;p1(19,19)
	movq		mm5, mm4				;p1(19,20)
	paddd		mm4, [esi + 8*23]		;p1(19,21)
	paddd		mm4, const_0x2xx8		;p1(19,22)
	psrad		mm4, 9					;p1(19,23)
	packssdw	mm6, mm4				;p1(19,24)
	movq		[esi + 8*6], mm6		;p1(19,25)
	movq		mm4, [esi + 8*22]		;p1(19,26)
	psubd		mm4, mm7				;p1(19,27)
	movq		mm6, [esi + 8*23]		;p1(19,30)
	paddd		mm4, const_0x2xx8		;p1(19,28)
	psubd		mm6, mm5				;p1(19,31)
	psrad		mm4, 9					;p1(19,29)
	paddd		mm6, const_0x2xx8		;p1(19,32)
	psrad		mm6, 9					;p1(19,33)
	packssdw	mm4, mm6				;p1(19,34)
	movq		[esi + 8*8], mm4		;p1(19,35)
//************************************************************  
//	add		edi, 8
	add		ebx, 8
	add		esi, 8
//************************************************************  
	/* Pass 1. */
	movq		mm0, [ebx + 8*4]		;p1(1,0)
    movq		mm1, [ebx + 8*12]		;p1(2,0)
	movq		mm6, [ebx + 8*0]		;p1(5,0)
	movq		mm2, mm0				;p1(3,0)
	movq		mm7, [ebx + 8*8]		;p1(6,0)
	punpcklwd	mm0, mm1				;p1(3,1)
	movq		mm4, mm0				;p1(3,2)
	punpckhwd	mm2, mm1				;p1(3,4)
	pmaddwd		mm0, fix_054n184_054	;p1(3,3)
	movq		mm5, mm2				;p1(3,5)
	pmaddwd		mm2, fix_054n184_054	;p1(3,6)
	pxor		mm1, mm1				;p1(7,0)
	pmaddwd		mm4, fix_054_054p076	;p1(4,0)
	punpcklwd   mm1, mm6				;p1(7,1)
	pmaddwd		mm5, fix_054_054p076	;p1(4,1)
	psrad		mm1, 3					;p1(7,2)
	pxor		mm3, mm3				;p1(7,3)
	punpcklwd	mm3, mm7				;p1(7,4)
	psrad		mm3, 3					;p1(7,5)
	paddd		mm1, mm3				;p1(7,6)
	movq		mm3, mm1				;p1(7,7)	
	paddd		mm1, mm4				;p1(7,8)
	psubd		mm3, mm4				;p1(7,9)
	movq		[esi + 8*16], mm1		;p1(7,10)
	pxor		mm4, mm4				;p1(7,12)
	movq		[esi + 8*22], mm3		;p1(7,11)
	punpckhwd	mm4, mm6				;p1(7,13)
	psrad		mm4, 3					;p1(7,14)
	pxor		mm1, mm1				;p1(7,15)
	punpckhwd	mm1, mm7				;p1(7,16)
	psrad		mm1, 3					;p1(7,17)
	paddd		mm4, mm1				;p1(7,18)
	movq		mm3, mm4				;p1(7,19)	
	pxor		mm1, mm1				;p1(8,0)
	paddd		mm3, mm5				;p1(7,20)
	punpcklwd	mm1, mm6				;p1(8,1)
	psubd		mm4, mm5				;p1(7,21)
	psrad		mm1, 3					;p1(8,2)
	movq		[esi + 8*17], mm3		;p1(7,22)
	pxor		mm5, mm5				;p1(8,3)
	movq		[esi + 8*23], mm4		;p1(7,23)
	punpcklwd	mm5, mm7				;p1(8,4)
	psrad		mm5, 3					;p1(8,5)
	pxor		mm4, mm4				;p1(8,12)
	psubd		mm1, mm5				;p1(8,6)	
	punpckhwd	mm4, mm6				;p1(8,13)
	movq		mm3, mm1				;p1(8,7)
	psrad		mm4, 3					;p1(8,14)
	paddd		mm1, mm0				;p1(8,8)
	pxor		mm5, mm5				;p1(8,15)
	psubd		mm3, mm0				;p1(8,9)
	movq		mm0, [ebx + 8*14]		;p1(9,0)
	punpckhwd	mm5, mm7				;p1(8,16)
	movq		[esi + 8*18], mm1		;p1(8,10)
	psrad		mm5, 3					;p1(8,17)
	movq		[esi + 8*20], mm3		;p1(8,11)
	psubd		mm4, mm5				;p1(8,18)
	movq		mm3, mm4				;p1(8,19)
	movq		mm1, [ebx + 8*6]		;p1(10,0)
	paddd		mm3, mm2				;p1(8,20)
	psubd		mm4, mm2				;p1(8,21)
	movq		mm5, mm0				;p1(11,1)
	movq		[esi + 8*21], mm4		;p1(8,23)
	movq		[esi + 8*19], mm3		;p1(8,22)
	movq		mm4, mm0				;p1(11,0)
	punpcklwd	mm4, mm1				;p1(11,2)
	movq		mm2, [ebx + 8*10]		;p1(12,0)
	punpckhwd	mm5, mm1				;p1(11,4)	
	movq		mm3, [ebx + 8*2]		;p1(13,0)
	movq		mm6, mm2				;p1(14,0)
	pmaddwd		mm4, fix_117_117		;p1(11,3)
	movq		mm7, mm2				;p1(14,1)
	pmaddwd		mm5, fix_117_117		;p1(11,5)
	punpcklwd	mm6, mm3				;p1(14,2)
	pmaddwd		mm6, fix_117_117		;p1(14,3)
	punpckhwd	mm7, mm3				;p1(14,4)
	pmaddwd		mm7, fix_117_117		;p1(14,5)
	paddd		mm4, mm6				;p1(15,0)
	paddd		mm5, mm7				;p1(15,1)
   	movq		[esi+8*24], mm4			;p1(15,2)
	movq		[esi+8*25], mm5			;p1(15,3)
	movq		mm6, mm0				;p1(16,0)
	movq		mm7, mm3				;p1(16,3)
	punpcklwd	mm6, mm2				;p1(16,1)
	punpcklwd	mm7, mm3				;p1(16,4)
	pmaddwd		mm6, fix_n039_n089		;p1(16,2)
	pmaddwd		mm7, fix_150_n089n039	;p1(16,5)
	movq		mm4, mm0				;p1(16,12)
	paddd		mm6, [esi+8*24]			;p1(16,6)
	punpckhwd	mm4, mm2				;p1(16,13)
	paddd		mm6, mm7				;p1(16,7)
	pmaddwd		mm4, fix_n039_n089		;p1(16,14)
	movq		mm7, mm6				;p1(16,8)
	paddd		mm4, [esi+8*25]			;p1(16,18)
	movq		mm5, mm3				;p1(16,15)
	paddd		mm6, [esi + 8*16]		;p1(16,9)
	punpckhwd	mm5, mm3				;p1(16,16)
	paddd		mm6, const_0x2xx8		;p1(16,10)
	psrad		mm6, 9					;p1(16,11)
	pmaddwd		mm5, fix_150_n089n039	;p1(16,17)
	paddd		mm4, mm5				;p1(16,19)
	movq		mm5, mm4				;p1(16,20)
	paddd		mm4, [esi + 8*17]		;p1(16,21)
	paddd		mm4, const_0x2xx8		;p1(16,22)
	psrad		mm4, 9					;p1(16,23)
	packssdw	mm6, mm4				;p1(16,24)
	movq		[esi + 8*0], mm6		;p1(16,25)
	movq		mm4, [esi + 8*16]		;p1(16,26)
	psubd		mm4, mm7				;p1(16,27)
	movq		mm6, [esi + 8*17]		;p1(16,30)
	paddd		mm4, const_0x2xx8		;p1(16,28)
	movq		mm7, mm1				;p1(17,3)
	psrad		mm4, 9					;p1(16,29)
	psubd		mm6, mm5				;p1(16,31)
	paddd		mm6, const_0x2xx8		;p1(16,32)
	punpcklwd	mm7, mm1				;p1(17,4)
	pmaddwd		mm7, fix_307n256_n196	;p1(17,5)
	psrad		mm6, 9					;p1(16,33)
	packssdw	mm4, mm6				;p1(16,34)
	movq		[esi + 8*14], mm4		;p1(16,35)
	movq		mm6, mm0				;p1(17,0)
	movq		mm4, mm0				;p1(17,12)
	punpcklwd	mm6, mm2				;p1(17,1)
	punpckhwd	mm4, mm2				;p1(17,13)
	pmaddwd		mm6, fix_n256_n196		;p1(17,2)
	movq		mm5, mm1				;p1(17,15)
	paddd		mm6, [esi+8*24]			;p1(17,6)
	punpckhwd	mm5, mm1				;p1(17,16)
	paddd		mm6, mm7				;p1(17,7)
	pmaddwd		mm4, fix_n256_n196		;p1(17,14)
	movq		mm7, mm6				;p1(17,8)
	pmaddwd		mm5, fix_307n256_n196	;p1(17,17)
	paddd		mm6, [esi + 8*18]		;p1(17,9)
	paddd		mm6, const_0x2xx8		;p1(17,10)
	psrad		mm6, 9					;p1(17,11)
	paddd		mm4, [esi+8*25]			;p1(17,18)
	paddd		mm4, mm5				;p1(17,19)
	movq		mm5, mm4				;p1(17,20)
	paddd		mm4, [esi + 8*19]		;p1(17,21)
	paddd		mm4, const_0x2xx8		;p1(17,22)
	psrad		mm4, 9					;p1(17,23)
	packssdw	mm6, mm4				;p1(17,24)
	movq		[esi + 8*2], mm6		;p1(17,25)
	movq		mm4, [esi + 8*18]		;p1(17,26)
	movq		mm6, [esi + 8*19]		;p1(17,30)
	psubd		mm4, mm7				;p1(17,27)
	paddd		mm4, const_0x2xx8		;p1(17,28)
	psubd		mm6, mm5				;p1(17,31)
	psrad		mm4, 9					;p1(17,29)
	paddd		mm6, const_0x2xx8		;p1(17,32)
	psrad		mm6, 9					;p1(17,33)
	movq		mm7, mm2				;p1(18,3)
	packssdw	mm4, mm6				;p1(17,34)
	movq		[esi + 8*12], mm4		;p1(17,35)
	movq		mm6, mm1				;p1(18,0)
	punpcklwd	mm7, mm2				;p1(18,4)
	punpcklwd	mm6, mm3				;p1(18,1)
	pmaddwd		mm7, fix_205_n256n039	;p1(18,5)
	pmaddwd		mm6, fix_n039_n256		;p1(18,2)
	movq		mm4, mm1				;p1(18,12)
	paddd		mm6, [esi+8*24]			;p1(18,6)
	punpckhwd	mm4, mm3				;p1(18,13)
	paddd		mm6, mm7				;p1(18,7)
	pmaddwd		mm4, fix_n039_n256		;p1(18,14)
	movq		mm7, mm6				;p1(18,8)
	movq		mm5, mm2				;p1(18,15)
	paddd		mm6, [esi + 8*20]		;p1(18,9)
	punpckhwd	mm5, mm2				;p1(18,16)
	paddd		mm6, const_0x2xx8		;p1(18,10)
	psrad		mm6, 9					;p1(18,11)
	pmaddwd		mm5, fix_205_n256n039	;p1(18,17)
	paddd		mm4, [esi+8*25]			;p1(18,18)
	paddd		mm4, mm5				;p1(18,19)
	movq		mm5, mm4				;p1(18,20)
	paddd		mm4, [esi + 8*21]		;p1(18,21)
	paddd		mm4, const_0x2xx8		;p1(18,22)
	psrad		mm4, 9					;p1(18,23)
	packssdw	mm6, mm4				;p1(18,24)
	movq		[esi + 8*4], mm6		;p1(18,25)
	movq		mm4, [esi + 8*20]		;p1(18,26)
	psubd		mm4, mm7				;p1(18,27)
	paddd		mm4, const_0x2xx8		;p1(18,28)
	movq		mm7, mm0				;p1(19,3)
	psrad		mm4, 9					;p1(18,29)
	movq		mm6, [esi + 8*21]		;p1(18,30)
	psubd		mm6, mm5				;p1(18,31)
	punpcklwd	mm7, mm0				;p1(19,4)
	paddd		mm6, const_0x2xx8		;p1(18,32)
	psrad		mm6, 9					;p1(18,33)
	pmaddwd		mm7, fix_029_n089n196	;p1(19,5)
	packssdw	mm4, mm6				;p1(18,34)
	movq		[esi + 8*10], mm4		;p1(18,35)
	movq		mm6, mm3				;p1(19,0)
	punpcklwd	mm6, mm1				;p1(19,1)	
	movq		mm5, mm0				;p1(19,15)
	pmaddwd		mm6, fix_n196_n089		;p1(19,2)
	punpckhwd	mm5, mm0				;p1(19,16)
	paddd		mm6, [esi+8*24]			;p1(19,6)
	movq		mm4, mm3				;p1(19,12)
	paddd		mm6, mm7				;p1(19,7)
	punpckhwd	mm4, mm1				;p1(19,13)
	movq		mm7, mm6				;p1(19,8)
	pmaddwd		mm4, fix_n196_n089  	;p1(19,14)
	paddd		mm6, [esi + 8*22]		;p1(19,9)
	pmaddwd		mm5, fix_029_n089n196	;p1(19,17)
	paddd		mm6, const_0x2xx8		;p1(19,10)
	psrad		mm6, 9					;p1(19,11)
	paddd		mm4, [esi+8*25]			;p1(19,18)
	paddd		mm4, mm5				;p1(19,19)
	movq		mm5, mm4				;p1(19,20)
	paddd		mm4, [esi + 8*23]		;p1(19,21)
	paddd		mm4, const_0x2xx8		;p1(19,22)
	psrad		mm4, 9					;p1(19,23)
	packssdw	mm6, mm4				;p1(19,24)
	movq		[esi + 8*6], mm6		;p1(19,25)
	movq		mm4, [esi + 8*22]		;p1(19,26)
	psubd		mm4, mm7				;p1(19,27)
	movq		mm6, [esi + 8*23]		;p1(19,30)
	paddd		mm4, const_0x2xx8		;p1(19,28)
	psubd		mm6, mm5				;p1(19,31)
	psrad		mm4, 9					;p1(19,29)
	paddd		mm6, const_0x2xx8		;p1(19,32)
	psrad		mm6, 9					;p1(19,33)
	packssdw	mm4, mm6				;p1(19,34)
	movq		[esi + 8*8], mm4		;p1(19,35)
//************************************************************  
	mov			esi, eax
	mov			edi, outptr
//transpose 4 rows of wsptr
	movq		mm0, [esi+8*0]			;tran(0)
	movq		mm1, mm0				;tran(1)
	movq		mm2, [esi+8*2]			;tran(2)		
	punpcklwd	mm0, mm2				;tran(3)
	movq		mm3, [esi+8*4]			;tran(5)
	punpckhwd	mm1, mm2				;tran(4)
	movq		mm5, [esi+8*6]			;tran(7)
	movq		mm4, mm3				;tran(6)
	movq		mm6, mm0				;tran(10)
	punpcklwd	mm3, mm5				;tran(8)
	movq		mm7, mm1				;tran(11)
	punpckldq	mm0, mm3				;tran(12)
	punpckhwd	mm4, mm5				;tran(9)
	movq		[esi+8*0], mm0			;tran(16)
	punpckhdq	mm6, mm3				;tran(13)
	movq		mm0, [esi+8*1]			;tran(20)
	punpckldq	mm1, mm4				;tran(14)
	movq		[esi+8*2], mm6			;tran(17)
	punpckhdq	mm7, mm4				;tran(15)
	movq		[esi+8*4], mm1			;tran(18)
	movq		mm1, mm0				;tran(21)
	movq		mm3, [esi+8*5]			;tran(25)
	movq		mm2, [esi+8*3]			;tran(22)
	movq		mm4, mm3				;tran(26)
	punpcklwd	mm0, mm2				;tran(23)
	movq		[esi+8*6], mm7			;tran(19)
	punpckhwd	mm1, mm2				;tran(24)
	movq		mm5, [esi+8*7]			;tran(27)
	punpcklwd	mm3, mm5				;tran(28)
	movq		mm6, mm0				;tran(30)
	movq		mm7, mm1				;tran(31)
	punpckhdq	mm6, mm3				;tran(33)
	punpckhwd	mm4, mm5				;tran(29)
	movq		mm2, mm6				;p2(1,0)
	punpckhdq	mm7, mm4				;tran(35)
	movq		mm5, [esi + 8*2]		;p2(1,2)
	paddw		mm2, mm7				;p2(1,1)
	paddw		mm5, [esi + 8*6]		;p2(1,3)
	punpckldq	mm0, mm3				;tran(32)
	paddw		mm2, mm5				;p2(1,4)
	punpckldq	mm1, mm4				;tran(34)
	movq		mm5, [esi + 8*2]		;p2(3,0)
	pmulhw		mm2, fix_117_117		;p2(1,5)
	movq		mm4, mm7				;p2(2,0)
	pmulhw		mm4, fixn089n196p029	;p2(2,1)
	movq		mm3, mm6				;p2(6,0)
	pmulhw		mm3, fix_n256n039p205	;p2(6,1)
	pmulhw		mm5, fix_n089			;p2(3,1)
	movq		[eax + 8*24], mm2		;p2(1,6)
	movq		mm2, [esi + 8*6]		;p2(4,0)
	pmulhw		mm2, fix_n196			;p2(4,1)
	paddw		mm4, [eax + 8*24]		;p2(5,0)
	paddw		mm3, [eax + 8*24]		;p2(9,0)
	paddw		mm5, mm2				;p2(5,1)
	movq		mm2, [esi + 8*2]		;p2(7,0)
	paddw		mm5, mm4				;p2(5,2)
	pmulhw		mm2, fix_n039			;p2(7,1)
	movq		[esi + 8*1], mm5		;p2(5,3)
	movq		mm4, [esi + 8*6]		;p2(8,0)
	movq		mm5, mm6				;p2(10,0)
	pmulhw		mm4, fix_n256			;p2(8,1)
	pmulhw		mm5, fix_n039			;p2(10,1)
	pmulhw		mm6, fix_n256			;p2(15,0)
	paddw		mm2, mm4				;p2(9,1)
	movq		mm4, mm7				;p2(11,0)
	pmulhw		mm4, fix_n089			;p2(11,1)
	paddw		mm2, mm3				;p2(9,2)
	movq		[esi + 8*3], mm2		;p2(9,3)
	movq		mm3, [esi + 8*2]		;p2(13,0)
	pmulhw		mm7, fix_n196			;p2(16,0)
	pmulhw		mm3, fix_n089n039p150	;p2(13,1)
	paddw		mm5, mm4				;p2(12,0)
	paddw		mm5, [eax + 8*24]		;p2(14,0)
	movq		mm2, [esi + 8*6]		;p2(18,0)
	pmulhw		mm2, fix_n196p307n256	;p2(18,1)
	paddw		mm5, mm3				;p2(14,1)
	movq		[esi + 8*5], mm5		;p2(14,2)
	paddw		mm6, mm7				;p2(17,0)
	paddw		mm6, [eax + 8*24]		;p2(19,0)
	movq		mm3, mm1				;p2(21,0)
	movq		mm4, [esi + 8*4]		;p2(20,0)
	paddw		mm6, mm2				;p2(19,1)
	movq		[esi + 8*7], mm6		;p2(19,2)	
	movq		mm5, mm4				;p2(20,1)
	movq		mm7, [esi + 8*0]		;p2(26,0)
	pmulhw		mm4, fix_054p076		;p2(20,2)	
	psubw		mm7, mm0				;p2(27,0)
	pmulhw		mm3, fix_054			;p2(21,1)
	movq		mm2, mm0				;p2(26,1)
	pmulhw		mm5, fix_054			;p2(23,0)
	psraw		mm7, 3					;p2(27,1)
	paddw		mm2, [esi + 8*0]		;p2(26,2)
	movq		mm6, mm7				;p2(28,0)
	pmulhw		mm1, fix_054n184		;p2(24,0)
	psraw		mm2, 3					;p2(26,3)			
	paddw		mm4, mm3				;p2(22,0)	
	paddw		mm5, mm1				;p2(25,0)
	psubw		mm6, mm5				;p2(29,0)	
	movq		mm3, mm2				;p2(30,0)
	paddw		mm2, mm4				;p2(30,1)		
	paddw		mm7, mm5				;p2(28,1)			
	movq		mm1, mm2				;p2(32,0)
	psubw		mm3, mm4				;p2(31,0)		
	paddw		mm1, [esi + 8*5]		;p2(32,1)
	movq		mm0, mm7				;p2(33,0)
	psubw		mm2, [esi + 8*5]		;p2(32,2)
	movq		mm4, mm6				;p2(34,0)
	paddw		mm1, const_0x0808		;p2(32,3)
	paddw		mm2, const_0x0808		;p2(32,4)
	psraw		mm1, 4					;p2(32,5)
	psraw		mm2, 4					;p2(32,6)
	paddw		mm7, [esi + 8*7]		;p2(33,1)
	packuswb	mm1, mm2				;p2(32,7)
	psubw		mm0, [esi + 8*7]		;p2(33,2)
	paddw		mm7, const_0x0808		;p2(33,3)
	paddw		mm0, const_0x0808		;p2(33,4)
	psraw		mm7, 4					;p2(33,5)
	psraw		mm0, 4					;p2(33,6)
	paddw		mm4, [esi + 8*3]		;p2(34,1)
	packuswb	mm7, mm0				;p2(33,7)
	psubw		mm6, [esi + 8*3]		;p2(34,2)
	paddw		mm4, const_0x0808		;p2(34,3)
	movq		mm5, mm3				;p2(35,0)
	paddw		mm6, const_0x0808		;p2(34,4)
	psraw		mm4, 4					;p2(34,5)
	psraw		mm6, 4					;p2(34,6)
	paddw		mm3, [esi + 8*1]		;p2(35,1)
	packuswb	mm4, mm6				;p2(34,7)
	psubw		mm5, [esi + 8*1]		;p2(35,2)
	movq		mm0, mm1				;p2(36,0)
	paddw		mm3, const_0x0808		;p2(35,3)
	paddw		mm5, const_0x0808		;p2(35,4)
	punpcklbw	mm0, mm7				;p2(36,1)
	psraw		mm3, 4					;p2(35,5)
	movq		mm2, mm4				;p2(37,0)
	psraw		mm5, 4					;p2(35,6)
	movq		mm6, mm0				;p2(38,0)
	packuswb	mm3, mm5				;p2(35,7)
	lea			ebx, [edi]				;p2(42,0)
	punpckhbw	mm7, mm1				;p2(36,2)
	lea			ecx, [edi+8]			;p2(42,1)
	punpcklbw	mm2, mm3				;p2(37,1)	
	lea			edx, [edi+16]			;p2(42,2)
	punpckhbw	mm3, mm4				;p2(37,2)	
	punpcklwd	mm0, mm2				;p2(38,1)	
	movq		mm5, mm3				;p2(39,0)
	punpckhwd	mm6, mm2				;p2(38,2)	
	movq		mm1, mm0				;p2(40,0)
	punpcklwd	mm3, mm7				;p2(39,1)	
	punpckldq	mm0, mm3				;p2(40,1)	
	punpckhdq	mm1, mm3				;p2(40,2)	
	movq		[ebx], mm0				;p2(43,0)	
	punpckhwd	mm5, mm7				;p2(39,2)	
	movq		[ecx], mm1				;p2(43,1)	
	movq		mm4, mm6				;p2(41,0)
	lea			ebx, [edi+24]			;p2(43,3)
	punpckldq	mm4, mm5				;p2(41,1)	
	punpckhdq	mm6, mm5				;p2(41,2)	
	movq		[edx], mm4				;p2(43,2)		
	movq		[ebx], mm6				;p2(43,5)
//************************************************************
//	Process next 4 rows
	add			esi, 64
	add			edi, 32							
//transpose next 4 rows of wsptr
	movq		mm0, [esi+8*0]			;tran(0)
	movq		mm1, mm0				;tran(1)
	movq		mm2, [esi+8*2]			;tran(2)		
	punpcklwd	mm0, mm2				;tran(3)
	movq		mm3, [esi+8*4]			;tran(5)
	punpckhwd	mm1, mm2				;tran(4)
	movq		mm5, [esi+8*6]			;tran(7)
	movq		mm4, mm3				;tran(6)
	movq		mm6, mm0				;tran(10)
	punpcklwd	mm3, mm5				;tran(8)
	movq		mm7, mm1				;tran(11)
	punpckldq	mm0, mm3				;tran(12)
	punpckhwd	mm4, mm5				;tran(9)
	movq		[esi+8*0], mm0			;tran(16)
	punpckhdq	mm6, mm3				;tran(13)
	movq		mm0, [esi+8*1]			;tran(20)
	punpckldq	mm1, mm4				;tran(14)
	movq		[esi+8*2], mm6			;tran(17)
	punpckhdq	mm7, mm4				;tran(15)
	movq		[esi+8*4], mm1			;tran(18)
	movq		mm1, mm0				;tran(21)
	movq		mm3, [esi+8*5]			;tran(25)
	movq		mm2, [esi+8*3]			;tran(22)
	movq		mm4, mm3				;tran(26)
	punpcklwd	mm0, mm2				;tran(23)
	movq		[esi+8*6], mm7			;tran(19)
	punpckhwd	mm1, mm2				;tran(24)
	movq		mm5, [esi+8*7]			;tran(27)
	punpcklwd	mm3, mm5				;tran(28)
	movq		mm6, mm0				;tran(30)
	movq		mm7, mm1				;tran(31)
	punpckhdq	mm6, mm3				;tran(33)
	punpckhwd	mm4, mm5				;tran(29)
	movq		mm2, mm6				;p2(1,0)
	punpckhdq	mm7, mm4				;tran(35)
	movq		mm5, [esi + 8*2]		;p2(1,2)
	paddw		mm2, mm7				;p2(1,1)
	paddw		mm5, [esi + 8*6]		;p2(1,3)
	punpckldq	mm0, mm3				;tran(32)
	paddw		mm2, mm5				;p2(1,4)
	punpckldq	mm1, mm4				;tran(34)
	movq		mm5, [esi + 8*2]		;p2(3,0)
	pmulhw		mm2, fix_117_117		;p2(1,5)
	movq		mm4, mm7				;p2(2,0)
	pmulhw		mm4, fixn089n196p029	;p2(2,1)
	movq		mm3, mm6				;p2(6,0)
	pmulhw		mm3, fix_n256n039p205	;p2(6,1)
	pmulhw		mm5, fix_n089			;p2(3,1)
	movq		[eax + 8*24], mm2		;p2(1,6)
	movq		mm2, [esi + 8*6]		;p2(4,0)
	pmulhw		mm2, fix_n196			;p2(4,1)
	paddw		mm4, [eax + 8*24]		;p2(5,0)
	paddw		mm3, [eax + 8*24]		;p2(9,0)
	paddw		mm5, mm2				;p2(5,1)
	movq		mm2, [esi + 8*2]		;p2(7,0)
	paddw		mm5, mm4				;p2(5,2)
	pmulhw		mm2, fix_n039			;p2(7,1)
	movq		[esi + 8*1], mm5		;p2(5,3)
	movq		mm4, [esi + 8*6]		;p2(8,0)
	movq		mm5, mm6				;p2(10,0)
	pmulhw		mm4, fix_n256			;p2(8,1)
	pmulhw		mm5, fix_n039			;p2(10,1)
	pmulhw		mm6, fix_n256			;p2(15,0)
	paddw		mm2, mm4				;p2(9,1)
	movq		mm4, mm7				;p2(11,0)
	pmulhw		mm4, fix_n089			;p2(11,1)
	paddw		mm2, mm3				;p2(9,2)
	movq		[esi + 8*3], mm2		;p2(9,3)
	movq		mm3, [esi + 8*2]		;p2(13,0)
	pmulhw		mm7, fix_n196			;p2(16,0)
	pmulhw		mm3, fix_n089n039p150	;p2(13,1)
	paddw		mm5, mm4				;p2(12,0)
	paddw		mm5, [eax + 8*24]		;p2(14,0)
	movq		mm2, [esi + 8*6]		;p2(18,0)
	pmulhw		mm2, fix_n196p307n256	;p2(18,1)
	paddw		mm5, mm3				;p2(14,1)
	movq		[esi + 8*5], mm5		;p2(14,2)
	paddw		mm6, mm7				;p2(17,0)
	paddw		mm6, [eax + 8*24]		;p2(19,0)
	movq		mm3, mm1				;p2(21,0)
	movq		mm4, [esi + 8*4]		;p2(20,0)
	paddw		mm6, mm2				;p2(19,1)
	movq		[esi + 8*7], mm6		;p2(19,2)	
	movq		mm5, mm4				;p2(20,1)
	movq		mm7, [esi + 8*0]		;p2(26,0)
	pmulhw		mm4, fix_054p076		;p2(20,2)	
	psubw		mm7, mm0				;p2(27,0)
	pmulhw		mm3, fix_054			;p2(21,1)
	movq		mm2, mm0				;p2(26,1)
	pmulhw		mm5, fix_054			;p2(23,0)
	psraw		mm7, 3					;p2(27,1)
	paddw		mm2, [esi + 8*0]		;p2(26,2)
	movq		mm6, mm7				;p2(28,0)
	pmulhw		mm1, fix_054n184		;p2(24,0)
	psraw		mm2, 3					;p2(26,3)			
	paddw		mm4, mm3				;p2(22,0)	
	paddw		mm5, mm1				;p2(25,0)
	psubw		mm6, mm5				;p2(29,0)	
	movq		mm3, mm2				;p2(30,0)
	paddw		mm2, mm4				;p2(30,1)		
	paddw		mm7, mm5				;p2(28,1)			
	movq		mm1, mm2				;p2(32,0)
	psubw		mm3, mm4				;p2(31,0)		
	paddw		mm1, [esi + 8*5]		;p2(32,1)
	movq		mm0, mm7				;p2(33,0)
	psubw		mm2, [esi + 8*5]		;p2(32,2)
	movq		mm4, mm6				;p2(34,0)
	paddw		mm1, const_0x0808		;p2(32,3)
	paddw		mm2, const_0x0808		;p2(32,4)
	psraw		mm1, 4					;p2(32,5)
	psraw		mm2, 4					;p2(32,6)
	paddw		mm7, [esi + 8*7]		;p2(33,1)
	packuswb	mm1, mm2				;p2(32,7)
	psubw		mm0, [esi + 8*7]		;p2(33,2)
	paddw		mm7, const_0x0808		;p2(33,3)
	paddw		mm0, const_0x0808		;p2(33,4)
	psraw		mm7, 4					;p2(33,5)
	psraw		mm0, 4					;p2(33,6)
	paddw		mm4, [esi + 8*3]		;p2(34,1)
	packuswb	mm7, mm0				;p2(33,7)
	psubw		mm6, [esi + 8*3]		;p2(34,2)
	paddw		mm4, const_0x0808		;p2(34,3)
	movq		mm5, mm3				;p2(35,0)
	paddw		mm6, const_0x0808		;p2(34,4)
	psraw		mm4, 4					;p2(34,5)
	psraw		mm6, 4					;p2(34,6)
	paddw		mm3, [esi + 8*1]		;p2(35,1)
	packuswb	mm4, mm6				;p2(34,7)
	psubw		mm5, [esi + 8*1]		;p2(35,2)
	movq		mm0, mm1				;p2(36,0)
	paddw		mm3, const_0x0808		;p2(35,3)
	paddw		mm5, const_0x0808		;p2(35,4)
	punpcklbw	mm0, mm7				;p2(36,1)
	psraw		mm3, 4					;p2(35,5)
	movq		mm2, mm4				;p2(37,0)
	psraw		mm5, 4					;p2(35,6)
	movq		mm6, mm0				;p2(38,0)
	packuswb	mm3, mm5				;p2(35,7)
	lea			ebx, [edi]				;p2(42,0)
	punpckhbw	mm7, mm1				;p2(36,2)
	lea			ecx, [edi+8]			;p2(42,1)
	punpcklbw	mm2, mm3				;p2(37,1)	
	lea			edx, [edi+16]			;p2(42,2)
	punpckhbw	mm3, mm4				;p2(37,2)	
	punpcklwd	mm0, mm2				;p2(38,1)	
	movq		mm5, mm3				;p2(39,0)
	punpckhwd	mm6, mm2				;p2(38,2)	
	movq		mm1, mm0				;p2(40,0)
	punpcklwd	mm3, mm7				;p2(39,1)	
	punpckldq	mm0, mm3				;p2(40,1)	
	punpckhdq	mm1, mm3				;p2(40,2)	
	movq		[ebx], mm0				;p2(43,0)	
	punpckhwd	mm5, mm7				;p2(39,2)	
	movq		[ecx], mm1				;p2(43,1)	
	movq		mm4, mm6				;p2(41,0)
	lea			ebx, [edi+24]			;p2(43,3)
	punpckldq	mm4, mm5				;p2(41,1)	
	punpckhdq	mm6, mm5				;p2(41,2)	
	movq		[edx], mm4				;p2(43,2)		
	movq		[ebx], mm6				;p2(43,5)
	emms
	}
}		





