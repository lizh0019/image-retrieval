// DrawCurve.cpp: implementation of the CDrawCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawCurve.h"
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawCurve::CDrawCurve()
{

}

CDrawCurve::~CDrawCurve()
{

}
bool CDrawCurve::CheckInputData()
{
   if(m_Dimension!=1&&m_Dimension!=2)return false;
   if(m_DataX==NULL)return false;
   if(m_Dimension==2&&m_DataY==NULL)return false;
   if(m_Length<=0||m_Length>MAXSAMPLES)return false;
   return true;
}

bool CDrawCurve::SetDefaultCDF()
{
     if(CheckInputData()==false)return false;
     LONG i;
     m_Cdf.m_bCurveStyle[0]=1;//connected_solid
	 m_Cdf.m_bCurveStyle[1]=1;//with Borders
	 m_Cdf.m_bCurveStyle[2]=1;//dash grid-linestyle
	 m_Cdf.m_bCurveStyle[3]=0;//black curve color
	 m_Cdf.m_bCurveStyle[4]=1;//white back color
	 m_Cdf.m_bCurveStyle[5]=3;//dark gray grid color

//+++++Axes Style++++++++++
  //[0]=X/Y axis 0,1,2,3,4 
  //none,line without arrow,line with arrow,
  //dash without arrow,dash with arrow
  //[1]=Xaxis Position 0,1,2 bottom middle top
  //[2]=Yaxis Position 0,1,2 left middle right
  //[3]: num of Xticks if<2, system sets to be 5
  //if>MAXTICKS, system sets to be MAXTICKS
  //[4]: num of Yticks if<2, system sets to be 5
  //if>MAXTICKS, system sets to be MAXTICKS
  //[5]=X/Y display axis's ticks? 0,1 none,line
  //[6]=0,1,without/with denotation Text
  //[7]=X/Y axis colors 0-9
  //[8]=X/Y axis's ticks color
  //[9]=X/Y denotation color
  	 m_Cdf.m_bAxes[0]=1;//line without arrow
	 m_Cdf.m_bAxes[1]=0;//X-axis bottom
	 m_Cdf.m_bAxes[2]=0;//Y-axis left
	 m_Cdf.m_bAxes[3]=5;//X-ticks
	 m_Cdf.m_bAxes[4]=5;//Y-ticks
	 m_Cdf.m_bAxes[5]=1;//show tick lines
	 m_Cdf.m_bAxes[6]=1;//show digit texts
	 m_Cdf.m_bAxes[7]=0;//color of Axes Black
	 m_Cdf.m_bAxes[8]=0;//color of Ticks Black
	 m_Cdf.m_bAxes[9]=0;//color of digits
	 //[0] [1]:The display style of Figure title
  //[0]=0,1,2 none up down
  //[1]=color
  //[2][3]:The display style of X title
  //[2]=0,1,2 none middle up
  //[3]=color
  //[4][5]:The display style of Y title
  //[4]=0,1,2 none middle right
  //[5]=color
	 m_Cdf.m_bTitleStyle[0]=2;//Figtitle down
     m_Cdf.m_bTitleStyle[1]=0;//Figtitle in Black
	 m_Cdf.m_bTitleStyle[2]=1;//Xtitle midle
     m_Cdf.m_bTitleStyle[3]=0;//Xtitle in Black
	 m_Cdf.m_bTitleStyle[4]=1;//Ytitle middle
     m_Cdf.m_bTitleStyle[5]=0;//Ytitle in Black
	 strcpy(m_Cdf.m_sTitles[0],"Result Chart");//The Dialog Title;
	 strcpy(m_Cdf.m_sTitles[1],"Experimental Results");//The Figure Title;
     strcpy(m_Cdf.m_sTitles[2],"X");//The X Title
	 strcpy(m_Cdf.m_sTitles[3],"Y");//The Y Title
     if(m_Dimension==1)
	 {
	   m_Cdf.m_bHowtoGetMinMax[0]=2;//default Xmin=0 default Xmax=m_Length-1
	   m_Cdf.m_bHowtoGetMinMax[1]=1;//search Ymin from DataX Ymax from DataX
       m_Cdf.m_dMinMaxInput[0]=0;//default Xmin
	   m_Cdf.m_dMinMaxInput[1]=m_Length-1;//default Xmax
	   m_Cdf.m_dMinMaxInput[2]=m_DataX[0];
       for(i=1;i<m_Length;i++)
	   {
	     if(m_Cdf.m_dMinMaxInput[2]>m_DataX[i])m_Cdf.m_dMinMaxInput[2]=m_DataX[i];
	   }
	   m_Cdf.m_dMinMaxInput[3]=m_DataX[0];
	   for(i=1;i<m_Length;i++)
	   {
	     if(m_Cdf.m_dMinMaxInput[3]<m_DataX[i])m_Cdf.m_dMinMaxInput[3]=m_DataX[i];
	   }
	   m_Cdf.m_bCurveStyle[6]=0;//point the interval
	   m_Cdf.m_bCurveStyle[7]=4;//red point
	 }
     else if(m_Length==2)
	 {
	   m_Cdf.m_bHowtoGetMinMax[0]=1;//search Xmin Xmax from DataX
	   m_Cdf.m_bHowtoGetMinMax[1]=1;//search  Ymin Ymax from DataY
	   m_Cdf.m_dMinMaxInput[0]=m_DataX[0];
       for(i=1;i<m_Length;i++)
	   {
	     if(m_Cdf.m_dMinMaxInput[0]>m_DataX[i])m_Cdf.m_dMinMaxInput[0]=m_DataX[i];
	   }
	   m_Cdf.m_dMinMaxInput[1]=m_DataX[0];
	   for(i=1;i<m_Length;i++)
	   {
	     if(m_Cdf.m_dMinMaxInput[1]<m_DataX[i])m_Cdf.m_dMinMaxInput[1]=m_DataX[i];
	   }
	   m_Cdf.m_dMinMaxInput[2]=m_DataY[0];
       for(i=1;i<m_Length;i++)
	   {
	     if(m_Cdf.m_dMinMaxInput[2]>m_DataY[i])m_Cdf.m_dMinMaxInput[2]=m_DataY[i];
	   }
	   m_Cdf.m_dMinMaxInput[3]=m_DataY[0];
	   for(i=1;i<m_Length;i++)
	   {
	     if(m_Cdf.m_dMinMaxInput[3]<m_DataY[i])m_Cdf.m_dMinMaxInput[3]=m_DataY[i];
	   }
	   m_Cdf.m_bCurveStyle[6]=0;//No use for 2-D
	   m_Cdf.m_bCurveStyle[7]=0;//No use for 2-D
	 }
     return true;
}
void CDrawCurve::SetCDFData(CURVEDATAINFO incdf)
{
  m_Cdf=incdf;
}
void CDrawCurve::GetCDFData(CURVEDATAINFO *outcdf)
{
  memcpy(outcdf,&m_Cdf,sizeof(CURVEDATAINFO));
  return;
}
void CDrawCurve::CheckCDFData()
{
	 double tem;
	 int i;
	 if(m_Cdf.m_bCurveStyle[1]>1)
		m_Cdf.m_bCurveStyle[1]=1;//with Borders
	 if(m_Cdf.m_bCurveStyle[2]>2)
	    m_Cdf.m_bCurveStyle[2]=1;//dash grid-linestyle
	 if(m_Cdf.m_bCurveStyle[3]>9)//[3] curve color 
		m_Cdf.m_bCurveStyle[3]=0;
	 if(m_Cdf.m_bCurveStyle[4]>9)//[4] Background color
		m_Cdf.m_bCurveStyle[4]=0;
	 if(m_Cdf.m_bCurveStyle[5]>9)//[5] Border and grid color
	    m_Cdf.m_bCurveStyle[5]=0;
	 if(m_Cdf.m_bCurveStyle[3]==m_Cdf.m_bCurveStyle[4])
	    m_Cdf.m_bCurveStyle[4]+=1;
	 if(m_Cdf.m_bCurveStyle[4]>9)
		m_Cdf.m_bCurveStyle[4]=0;
	 if(m_Cdf.m_bCurveStyle[5]==m_Cdf.m_bCurveStyle[4])
		m_Cdf.m_bCurveStyle[5]+=1;
	 if(m_Cdf.m_bCurveStyle[5]>9)
		m_Cdf.m_bCurveStyle[5]=0;
	 if(m_Cdf.m_bAxes[0]>4)m_Cdf.m_bAxes[0]=1;//line without arrow
	 if(m_Cdf.m_bAxes[1]>2)m_Cdf.m_bAxes[1]=0;//X-axis bottom
	 if(m_Cdf.m_bAxes[2]>2)m_Cdf.m_bAxes[2]=0;//Y-axis left
	 if(m_Cdf.m_bAxes[3]<2)m_Cdf.m_bAxes[3]=5;//X-ticks
	 if(m_Cdf.m_bAxes[3]>MAXTICKS)m_Cdf.m_bAxes[3]=MAXTICKS;
	 if(m_Cdf.m_bAxes[4]<2)m_Cdf.m_bAxes[4]=5;//Y-ticks
	 if(m_Cdf.m_bAxes[4]>MAXTICKS)m_Cdf.m_bAxes[4]=MAXTICKS;
	 if(m_Cdf.m_bAxes[5]>1)m_Cdf.m_bAxes[5]=1;//show tick lines
	 if(m_Cdf.m_bAxes[6]>1)m_Cdf.m_bAxes[6]=1;//show tick digits
	 if(m_Cdf.m_bAxes[7]>9)m_Cdf.m_bAxes[7]=0;//color of Axes Black
	 if(m_Cdf.m_bAxes[7]==m_Cdf.m_bCurveStyle[4])
		 m_Cdf.m_bAxes[7]+=1;
     if(m_Cdf.m_bAxes[7]>9)m_Cdf.m_bAxes[7]=0;
	 if(m_Cdf.m_bAxes[8]>9)m_Cdf.m_bAxes[8]=0;//color of Ticks Black
	 if(m_Cdf.m_bAxes[8]==m_Cdf.m_bCurveStyle[4])
		 m_Cdf.m_bAxes[8]+=1;
     if(m_Cdf.m_bAxes[8]>9)m_Cdf.m_bAxes[8]=0;
	 if(m_Cdf.m_bAxes[9]>9)m_Cdf.m_bAxes[9]=0;//color of digits
	 if(m_Cdf.m_bAxes[9]==m_Cdf.m_bCurveStyle[4])
		 m_Cdf.m_bAxes[9]+=1;
     if(m_Cdf.m_bAxes[9]>9)m_Cdf.m_bAxes[9]=0;

	 if(m_Cdf.m_bTitleStyle[0]>2)
		 m_Cdf.m_bTitleStyle[0]=2;//Figtitle down
     if(m_Cdf.m_bTitleStyle[1]>9)
		 m_Cdf.m_bTitleStyle[1]=0;//Figtitle color
	 if(m_Cdf.m_bTitleStyle[1]==m_Cdf.m_bCurveStyle[4])
         m_Cdf.m_bTitleStyle[1]+=1;
     if(m_Cdf.m_bTitleStyle[1]>9)
		 m_Cdf.m_bTitleStyle[1]=0;
	 if(m_Cdf.m_bTitleStyle[2]>2)m_Cdf.m_bTitleStyle[2]=1;//Xtitle midle
     if(m_Cdf.m_bTitleStyle[3]>9)
		 m_Cdf.m_bTitleStyle[3]=0;//Xtitle color
	 if(m_Cdf.m_bTitleStyle[3]==m_Cdf.m_bCurveStyle[4])
         m_Cdf.m_bTitleStyle[3]+=1;
     if(m_Cdf.m_bTitleStyle[3]>9)
		 m_Cdf.m_bTitleStyle[3]=0;
	 if(m_Cdf.m_bTitleStyle[4]>2)m_Cdf.m_bTitleStyle[4]=1;//Ytitle midle
     if(m_Cdf.m_bTitleStyle[5]>9)
		 m_Cdf.m_bTitleStyle[5]=0;//Ytitle color
	 if(m_Cdf.m_bTitleStyle[5]==m_Cdf.m_bCurveStyle[4])
         m_Cdf.m_bTitleStyle[5]+=1;
     if(m_Cdf.m_bTitleStyle[5]>9)
		 m_Cdf.m_bTitleStyle[5]=0;
	 if(m_Dimension==1)
	 {
	   if(m_Cdf.m_bCurveStyle[0]>4)
		 m_Cdf.m_bCurveStyle[0]=1;//connected_solid
	   if(m_Cdf.m_bCurveStyle[6]>3)
		   m_Cdf.m_bCurveStyle[6]=0;//None point the interval
	   //[7] for 1-D,X displayInterval point denotation color
	   if(m_Cdf.m_bCurveStyle[7]>9)
		   m_Cdf.m_bCurveStyle[7]=0;
	   if(m_Cdf.m_bCurveStyle[7]==m_Cdf.m_bCurveStyle[3])
		   m_Cdf.m_bCurveStyle[7]+=1;
       if(m_Cdf.m_bCurveStyle[7]>9)
		   m_Cdf.m_bCurveStyle[7]=0;
	   if(m_Cdf.m_bCurveStyle[7]==m_Cdf.m_bCurveStyle[4])
		   m_Cdf.m_bCurveStyle[7]+=1;
       if(m_Cdf.m_bCurveStyle[7]>9)
		   m_Cdf.m_bCurveStyle[7]=0;
	   if(m_Cdf.m_bHowtoGetMinMax[0]>2||m_Cdf.m_bHowtoGetMinMax[0]==1)
		 m_Cdf.m_bHowtoGetMinMax[0]=2;//default Xmin=0 //default Xmax=m_Length-1
	   if(m_Cdf.m_bHowtoGetMinMax[1]>1)
	      m_Cdf.m_bHowtoGetMinMax[1]=1;//search Ymin from DataX search Ymax from DataX
	   if(m_Cdf.m_bHowtoGetMinMax[0]==0)
	   {
	     if(m_Cdf.m_dMinMaxInput[0]>m_Cdf.m_dMinMaxInput[1])
		 {
		   tem=m_Cdf.m_dMinMaxInput[0];
		   m_Cdf.m_dMinMaxInput[0]=m_Cdf.m_dMinMaxInput[1];
		   m_Cdf.m_dMinMaxInput[1]=tem;
		 }
		 if(m_Cdf.m_dMinMaxInput[0]==m_Cdf.m_dMinMaxInput[1])
		   m_Cdf.m_dMinMaxInput[1]+=1;
	   }
	   else if(m_Cdf.m_bHowtoGetMinMax[0]==2)
	   {
         m_Cdf.m_dMinMaxInput[0]=0;//default Xmin
	     m_Cdf.m_dMinMaxInput[1]=m_Length-1;//default Xmax
	   }
	   if(m_Cdf.m_bHowtoGetMinMax[1]==0)
	   {
	     if(m_Cdf.m_dMinMaxInput[2]>m_Cdf.m_dMinMaxInput[3])
		 {
		   tem=m_Cdf.m_dMinMaxInput[2];
		   m_Cdf.m_dMinMaxInput[2]=m_Cdf.m_dMinMaxInput[3];
		   m_Cdf.m_dMinMaxInput[3]=tem;
		 }
		 if(m_Cdf.m_dMinMaxInput[2]==m_Cdf.m_dMinMaxInput[3])
		   m_Cdf.m_dMinMaxInput[3]+=1;
	   }
	   else if(m_Cdf.m_bHowtoGetMinMax[1]==1)
	   {
	     m_Cdf.m_dMinMaxInput[2]=m_DataX[0];
         for(i=1;i<m_Length;i++)
		 {
	       if(m_Cdf.m_dMinMaxInput[2]>m_DataX[i])m_Cdf.m_dMinMaxInput[2]=m_DataX[i];
		 }
	     m_Cdf.m_dMinMaxInput[3]=m_DataX[0];
	     for(i=1;i<m_Length;i++)
		 {
	       if(m_Cdf.m_dMinMaxInput[3]<m_DataX[i])m_Cdf.m_dMinMaxInput[3]=m_DataX[i];
		 }
	   }
	 }
     else if(m_Dimension==2)
	 {
	   if(m_Cdf.m_bCurveStyle[0]>2)
		 m_Cdf.m_bCurveStyle[0]=1;//connected_solid
	   if(m_Cdf.m_bHowtoGetMinMax[0]>1)
		 m_Cdf.m_bHowtoGetMinMax[0]=1;//search Xmin Xmax from DataX
	   if(m_Cdf.m_bHowtoGetMinMax[1]>1)
		 m_Cdf.m_bHowtoGetMinMax[1]=1;//search Ymin Ymax from DataY
 	   if(m_Cdf.m_bHowtoGetMinMax[0]==0)
	   {
	     if(m_Cdf.m_dMinMaxInput[0]>m_Cdf.m_dMinMaxInput[1])
		 {
		   tem=m_Cdf.m_dMinMaxInput[0];
		   m_Cdf.m_dMinMaxInput[0]=m_Cdf.m_dMinMaxInput[1];
		   m_Cdf.m_dMinMaxInput[1]=tem;
		 }
		 if(m_Cdf.m_dMinMaxInput[0]==m_Cdf.m_dMinMaxInput[1])
		   m_Cdf.m_dMinMaxInput[1]+=1;
	   }
	   else if(m_Cdf.m_bHowtoGetMinMax[0]==1)
	   {
	     m_Cdf.m_dMinMaxInput[0]=m_DataX[0];
         for(i=1;i<m_Length;i++)
		 {
	       if(m_Cdf.m_dMinMaxInput[0]>m_DataX[i])m_Cdf.m_dMinMaxInput[0]=m_DataX[i];
		 }
		 m_Cdf.m_dMinMaxInput[1]=m_DataX[0];
	     for(i=1;i<m_Length;i++)
		 {
	       if(m_Cdf.m_dMinMaxInput[1]<m_DataX[i])m_Cdf.m_dMinMaxInput[1]=m_DataX[i];
		 }
	   }
	   if(m_Cdf.m_bHowtoGetMinMax[1]==0)
	   {
	     if(m_Cdf.m_dMinMaxInput[2]>m_Cdf.m_dMinMaxInput[3])
		 {
		   tem=m_Cdf.m_dMinMaxInput[2];
		   m_Cdf.m_dMinMaxInput[2]=m_Cdf.m_dMinMaxInput[3];
		   m_Cdf.m_dMinMaxInput[3]=tem;
		 }
		 if(m_Cdf.m_dMinMaxInput[2]==m_Cdf.m_dMinMaxInput[3])
		   m_Cdf.m_dMinMaxInput[3]+=1;
	   }
	   else if(m_Cdf.m_bHowtoGetMinMax[1]==1)
	   {
	     m_Cdf.m_dMinMaxInput[2]=m_DataY[0];
         for(i=1;i<m_Length;i++)
		 {
	       if(m_Cdf.m_dMinMaxInput[2]>m_DataY[i])m_Cdf.m_dMinMaxInput[2]=m_DataY[i];
		 }
	     m_Cdf.m_dMinMaxInput[3]=m_DataY[0];
	     for(i=1;i<m_Length;i++)
		 {
	       if(m_Cdf.m_dMinMaxInput[3]<m_DataY[i])m_Cdf.m_dMinMaxInput[3]=m_DataY[i];
		 }
	   }
	 }
}

bool CDrawCurve::DrawCurve(HDC hdc,int Left,int LeftE,int Right,int RightE,int Up,int UpE,int Bottom,int BottomE)
{
   CheckCDFData();
   int i;
   double spacex,spacey,gridspacex,gridspacey;
   int posix,posix2,posiy;
   int Width,Height;
   int cases;
   if(hdc==NULL)return false;
   if(LeftE<0||UpE<0)return false;
   if(Left<=LeftE)return false;
   if(Left>=Right)return false;
   if(RightE<=Right)return false;
   if(Up<=UpE)return false;
   if(BottomE<=Bottom)return false;
   if(Up>=Bottom)return false;
   Width=Right-Left;
   Height=Bottom-Up;
   //pen[0]  curve pen   //pen[1]  grid pen
   //pen[2]  scalev pen for 1-D   //pen[3]  Axes color
   //pen[4]  tick pen   //pen[5]  digits pen
   //pen[6]  figtitle   //pen[7]  xtitle
   //pen[8]  ytitle  //penb pen for backcolor
   //pen[9]  border pen
   CPen pen[10],penb;
   
   //brush1 for backcolor 
   //brush2 for histogram linestyle 1-D
   //brush3 for histogram scalevstyle 1-D
   CBrush brush1,brush2,brush3;
   double displayx[11];
   double displayy[11];
   //+++++++++++++++The initial for pens and brushes+++++++++
   //for backcolor
   penb.CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bCurveStyle[4]]);
   brush1.CreateSolidBrush(Colors[m_Cdf.m_bCurveStyle[4]]);
   //For curve line mode
   if(m_Cdf.m_bCurveStyle[0]==2)//curve line dash or not
     pen[0].CreatePen(PS_DASH,1,Colors[m_Cdf.m_bCurveStyle[3]]);
   else
	 pen[0].CreatePen(PS_SOLID,2,Colors[m_Cdf.m_bCurveStyle[3]]);
   brush2.CreateSolidBrush(Colors[m_Cdf.m_bCurveStyle[3]]);
   if(m_Cdf.m_bCurveStyle[2]==1)//grid line dash or not
     pen[1].CreatePen(PS_DASH,1,Colors[m_Cdf.m_bCurveStyle[5]]);
   else
     pen[1].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bCurveStyle[5]]);
   //for border pen
   pen[9].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bCurveStyle[5]]);
   //for Scale V color pen or brush
   pen[2].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bCurveStyle[7]]);
   brush3.CreateSolidBrush(Colors[m_Cdf.m_bCurveStyle[7]]);
   //for axes color
   if(m_Cdf.m_bAxes[0]==3||m_Cdf.m_bAxes[0]==4)
     pen[3].CreatePen(PS_DASH,1,Colors[m_Cdf.m_bAxes[7]]);
   else
     pen[3].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bAxes[7]]);
   //for tick color
   pen[4].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bAxes[8]]);
   
   //for digits color
   pen[5].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bAxes[9]]);
   //for figtitle
   pen[6].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bTitleStyle[1]]);
   //for xtitle
   pen[7].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bTitleStyle[3]]);
   //for figtitle
   pen[8].CreatePen(PS_SOLID,1,Colors[m_Cdf.m_bTitleStyle[5]]);
   
   //Clear the Curve Region
   ::SelectObject(hdc,brush1);
   ::SelectObject(hdc,penb);
   ::Rectangle(hdc,LeftE,UpE,RightE,BottomE);
   
   //The space btw two points
   spacex=499.0/(double)(m_Length-1);
   spacey=399.0/(double)(m_Length-1);
   //The space btw two grids
   gridspacex=499.0/(double)m_Cdf.m_bAxes[3];
   gridspacey=399.0/(double)m_Cdf.m_bAxes[4];
   //+++++++++++++The curve+++++++++++++
   if(m_Cdf.m_bAxes[0]==0)cases=0;
   else
   {
     if(m_Cdf.m_bAxes[1]==2&&m_Cdf.m_bAxes[2]!=2)cases=1;
	 else if(m_Cdf.m_bAxes[1]!=2&&m_Cdf.m_bAxes[2]==2)cases=2;
	 else if(m_Cdf.m_bAxes[1]==2&&m_Cdf.m_bAxes[2]==2)cases=3;
	 else
	  cases=0;
   }
   //for 1-d
   if(m_Dimension==1)
   {
     ::SelectObject(hdc,pen[0]);
 	 switch(m_Cdf.m_bCurveStyle[0])
	 {
	   case 0:
	   for(i=0;i<m_Length;i++)
	   {
		posix=(int)(i*spacex);
		posiy=(int)((double)(m_DataX[i]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
		switch(cases)
		{
		  case 0:
		    posix=Left+posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
		  break;
		  case 1:
		    posix=Left+posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
		  break;
		  case 2:
		    posix=Right-posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 3:
		  	posix=Right-posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  default:
			  break;
		}
		::SetPixel(hdc,posix,posiy,Colors[m_Cdf.m_bCurveStyle[3]]);
	   }
	   break;
	   case 1:
	   case 2:
		posiy=(int)((double)(m_DataX[0]-\
	    m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
	    -m_Cdf.m_dMinMaxInput[2])*Height);
   		switch(cases)
		{
		  case 0:
	       posix=Left;
	       posiy=Bottom-posiy;
	       if(posiy<Up)posiy=Up;
		   break;
		  case 1:
           posix=Left;
	       posiy=Up+posiy;
	       if(posiy>Bottom)posiy=Bottom;
		   break;
		  case 2:
           posix=Right;
	       posiy=Bottom-posiy;
	       if(posiy<Up)posiy=Up;
		   break;
		  case 3:
           posix=Right;
	       posiy=Up+posiy;
	       if(posiy>Bottom)posiy=Bottom;
		   break;
		  default:
		   break;
		}
	   ::MoveToEx(hdc,posix,posiy,NULL);
	   for(i=1;i<m_Length;i++)
	   { 
   		posix=(int)(i*spacex);
		posiy=(int)((double)(m_DataX[i]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
		switch(cases)
		{
		  case 0:
		    posix=Left+posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 1:
		    posix=Left+posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  case 2:
		    posix=Right-posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 3:
		    posix=Right-posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  default:
			break;
		}
		::LineTo(hdc,posix,posiy);
		::MoveToEx(hdc,posix,posiy,NULL);
	   } 
	   break;
	   case 3:
	   for(i=0;i<m_Length;i++)
	   { 
		posix=(int)(i*spacex);
		posiy=(int)((double)(m_DataX[i]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
	    switch(cases)
		{
		  case 0:
            posix=Left+posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			::MoveToEx(hdc,posix,Bottom,NULL);
			break;
		  case 1:
            posix=Left+posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			::MoveToEx(hdc,posix,Up,NULL);
			break;
		  case 2:
            posix=Right-posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			::MoveToEx(hdc,posix,Bottom,NULL);
			break;
		  case 3:
            posix=Right-posix;
   		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			::MoveToEx(hdc,posix,Up,NULL);
            break;
		  default:
			break;
		}
		::LineTo(hdc,posix,posiy);
	   } 
	   break;
	   case 4:
	   ::SelectObject(hdc,brush2);
	   for(i=0;i<m_Length-1;i++)
	   { 
		posix=(int)(i*spacex);
		posix2=int((i+1)*spacex)-1;
		posiy=(int)((double)(m_DataX[i]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
		switch(cases)
		{
		  case 0:
			posix=Left+posix;
		    posix2=Left+posix2;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			::Rectangle(hdc,posix,posiy,posix2,Bottom);
			break;
		  case 1:
			posix=Left+posix;
		    posix2=Left+posix2;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			::Rectangle(hdc,posix,posiy,posix2,Up);
			break;
		  case 2:
			posix=Right-posix;
		    posix2=Right-posix2;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			::Rectangle(hdc,posix,posiy,posix2,Bottom);
			break;
		  case 3:
			posix=Right-posix;
		    posix2=Right-posix2;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			::Rectangle(hdc,posix,posiy,posix2,Up);
			break;
		}
	   } 
	   break;
	   default:
	   break;
	 }
   }
   else if(m_Dimension==2)
   {
     ::SelectObject(hdc,pen[0]);
	 if(m_Cdf.m_bCurveStyle[0]==0)
	 {
	   for(i=0;i<m_Length;i++)
	   {
	    posix=(int)((double)(m_DataX[i]\
		-m_Cdf.m_dMinMaxInput[0])/(m_Cdf.m_dMinMaxInput[1]\
		-m_Cdf.m_dMinMaxInput[0])*Width);
		posiy=(int)((double)(m_DataY[i]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
		switch(cases)
		{
		  case 0:
			posix=Left+posix;
		    if(posix>Right)posix=Right;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 1:
			posix=Left+posix;
		    if(posix>Right)posix=Right;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  case 2:
			posix=Right-posix;
		    if(posix<Left)posix=Left;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 3:
			posix=Right-posix;
		    if(posix<Left)posix=Left;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  default:
		  break;
		}
		 ::SetPixel(hdc,posix,posiy,Colors[m_Cdf.m_bCurveStyle[3]]);
	   }
	 }
	 else if(m_Cdf.m_bCurveStyle[0]==1||m_Cdf.m_bCurveStyle[0]==2)
	 {
	   	posix=(int)((double)(m_DataX[0]\
	    -m_Cdf.m_dMinMaxInput[0])/(m_Cdf.m_dMinMaxInput[1]\
	    -m_Cdf.m_dMinMaxInput[0])*Width);
	    posiy=(int)((double)(m_DataY[0]\
	    -m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
	    -m_Cdf.m_dMinMaxInput[2])*Height);
	    switch(cases)
		{
		  case 0:
			posix=Left+posix;
	        if(posix>Right)posix=Right;
	        posiy=Bottom-posiy;
	        if(posiy<Up)posiy=Up;
			break;
		  case 1:
			posix=Left+posix;
	        if(posix>Right)posix=Right;
	        posiy=Up+posiy;
	        if(posiy>Bottom)posiy=Bottom;
			break;
		  case 2:
			posix=Right-posix;
	        if(posix<Left)posix=Left;
	        posiy=Bottom-posiy;
	        if(posiy<Up)posiy=Up;
			break;
		  case 3:
			posix=Right-posix;
	        if(posix<Left)posix=Left;
	        posiy=Up+posiy;
	        if(posiy>Bottom)posiy=Bottom;
			break;
		  default:
			break;
		}
	   ::MoveToEx(hdc,posix,posiy,NULL);
	   for(i=1;i<m_Length;i++)
	   { 
	   	posix=(int)((double)(m_DataX[i]\
		-m_Cdf.m_dMinMaxInput[0])/(m_Cdf.m_dMinMaxInput[1]\
		-m_Cdf.m_dMinMaxInput[0])*Width);
		posiy=(int)((double)(m_DataY[i]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
		switch(cases)
		{
		  case 0:
		    posix=Left+posix;
		    if(posix>Right)posix=Right;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 1:
		    posix=Left+posix;
		    if(posix>Right)posix=Right;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  case 2:
		    posix=Right-posix;
		    if(posix<Left)posix=Left;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			break;
		  case 3:
		    posix=Right-posix;
		    if(posix<Left)posix=Left;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			break;
		  default:
			break;
		}
		::LineTo(hdc,posix,posiy);
		::MoveToEx(hdc,posix,posiy,NULL);
	   } 
	 }
   }
   //++++++++++++++++++The Grid+++++++++++++++++++++++
   if(m_Cdf.m_bCurveStyle[2]>0)
   {
     ::SelectObject(hdc,pen[1]);
	 for(i=1;i<m_Cdf.m_bAxes[3];i++)
	 {
	   posix=Left+(int)(i*gridspacex);
	   posiy=Bottom;
	   ::MoveToEx(hdc,posix,posiy,NULL);
	   posix=Left+(int)(i*gridspacex);
	   posiy=Up;
	   ::LineTo(hdc,posix,posiy);
	 }
	 for(i=1;i<m_Cdf.m_bAxes[4];i++)
	 {
	   posix=Left;
	   posiy=Bottom-(int)(i*gridspacey);
	   ::MoveToEx(hdc,posix,posiy,NULL);
	   posix=Right;
	   posiy=Bottom-(int)(i*gridspacey);
	   ::LineTo(hdc,posix,posiy);
	 }
   }
   
   //++++++++++++++++++The Border+++++++++++++++++++++++
   if(m_Cdf.m_bCurveStyle[1]==1)
   {
     ::SelectObject(hdc,pen[9]);
	 ::MoveToEx(hdc,Left,Up,NULL);
	 ::LineTo(hdc,Left,Bottom);
	 ::MoveToEx(hdc,Right,Up,NULL);
	 ::LineTo(hdc,Right,Bottom);
	 ::MoveToEx(hdc,Left,Up,NULL);
	 ::LineTo(hdc,Right,Up);
	 ::MoveToEx(hdc,Left,Bottom,NULL);
	 ::LineTo(hdc,Right,Bottom);
   }
   //++++++++++++++++++The ScaleV for 1-D+++++++++++++++
   if(m_Dimension==1)
   {
     ::SelectObject(hdc,pen[2]);  
     switch(m_Cdf.m_bCurveStyle[6])
	 {
	   case 0: //none
	   break;
	   case 1:  //point
	   for(i=0;i<=m_Cdf.m_bAxes[3];i++)
	   {
		posix=(int)((double)((int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3]))*spacex);
		posiy=(int)((double)(m_DataX[(int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3])]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
	   	switch(cases)
		{
		  case 0:
		    posix=Left+posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
		    break;
		  case 1:
		    posix=Left+posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
		    break;
		  case 2:
		    posix=Right-posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
		    break;
		  case 3:
		    posix=Right-posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
		    break;
		  default:
			break;
		}
		 ::SetPixel(hdc,posix,posiy,Colors[m_Cdf.m_bCurveStyle[7]]);
	   }
	   break;
	   case 2://single line
	   
	   for(i=0;i<=m_Cdf.m_bAxes[3];i++)
	   { 
	   	posix=(int)((double)((int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3]))*spacex);
		posiy=(int)((double)(m_DataX[(int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3])]\
		-m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		-m_Cdf.m_dMinMaxInput[2])*Height);
		switch(cases)
		{
		  case 0:
		    posix=Left+posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			::MoveToEx(hdc,posix,Bottom,NULL);
			break;
		  case 1:
		    posix=Left+posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			::MoveToEx(hdc,posix,Up,NULL);
			break;
		  case 2:
		    posix=Right-posix;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
			::MoveToEx(hdc,posix,Bottom,NULL);
			break;
		  case 3:
		    posix=Right-posix;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
			::MoveToEx(hdc,posix,Up,NULL);
			break;
		  default:
			break;
		}
		::LineTo(hdc,posix,posiy);
	   } 
	   break;
	   case 3: //histogram bar
	   ::SelectObject(hdc,brush3);
	   for(i=0;i<m_Cdf.m_bAxes[3];i++)
	   { 
	   	 posix=(int)((double)((int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3]))*spacex);
		 posix2=(int)((double)((int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3])+1)*spacex)-1;
		 posiy=(int)((double)(m_DataX[(int)((double)i*(double)(m_Length-1)/(double)m_Cdf.m_bAxes[3])]\
		 -m_Cdf.m_dMinMaxInput[2])/(m_Cdf.m_dMinMaxInput[3]\
		 -m_Cdf.m_dMinMaxInput[2])*Height);
		 switch(cases)
		 {
		  case 0:
		    posix=Left+posix;
		    posix2=Left+posix2;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
		    ::Rectangle(hdc,posix,posiy,posix2,Bottom);
			break;
		  case 1:
		    posix=Left+posix;
		    posix2=Left+posix2;
		    posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
		    ::Rectangle(hdc,posix,posiy,posix2,Up);
			break;
		  case 2:
		    posix=Right-posix;
		    posix2=Right-posix2;
		    posiy=Bottom-posiy;
		    if(posiy<Up)posiy=Up;
		    ::Rectangle(hdc,posix,posiy,posix2,Bottom);
			break;
		  case 3:
		    posix=Right-posix;
		    posix2=Right-posix2;
			posiy=Up+posiy;
		    if(posiy>Bottom)posiy=Bottom;
		    ::Rectangle(hdc,posix,posiy,posix2,Up);
			break;
		  default:
			break;
		 }
	   } 
	   break;
	   default:
	   break;
	 }
   }
   //++++++++++++++++++The axes+++++++++++++++++++++++
   ::SelectObject(hdc,pen[3]);
   int xposiy,yposix;
   if(m_Cdf.m_bAxes[1]==0)//X-axis position bottom
     xposiy=Bottom;
   else if(m_Cdf.m_bAxes[1]==1)
	 xposiy=Bottom-(int)((double)(m_Cdf.m_bAxes[4]/2)*gridspacey);
   else
	 xposiy=Up;
   if(m_Cdf.m_bAxes[2]==0)//X-axis position bottom
     yposix=Left;
   else if(m_Cdf.m_bAxes[2]==1)
	 yposix=Left+(int)((double)(m_Cdf.m_bAxes[3]/2)*gridspacex);
   else
	 yposix=Right;
   switch(m_Cdf.m_bAxes[0])
   {
      case 0: //none
       break;
	  case 1://without arrow
	  case 3:
        ::MoveToEx(hdc,yposix,Up-10,NULL);
	    ::LineTo(hdc,yposix,Bottom+10);
	    ::MoveToEx(hdc,Left-10,xposiy,NULL);
	    ::LineTo(hdc,Right+10,xposiy);
	 	break;
	  case 2://with arrow
	  case 4:
        ::MoveToEx(hdc,yposix,Up-10,NULL);
	    ::LineTo(hdc,yposix,Bottom+10);
		if(m_Cdf.m_bAxes[1]!=2)
		{
		  ::MoveToEx(hdc,yposix-3,Up-5,NULL);
	      ::LineTo(hdc,yposix,Up-10);
	      ::MoveToEx(hdc,yposix+3,Up-5,NULL);
	      ::LineTo(hdc,yposix,Up-10);
		}
		else
		{
		  ::MoveToEx(hdc,yposix-3,Bottom+5,NULL);
	      ::LineTo(hdc,yposix,Bottom+10);
	      ::MoveToEx(hdc,yposix+3,Bottom+5,NULL);
	      ::LineTo(hdc,yposix,Bottom+10);		
		}
		::MoveToEx(hdc,Left-10,xposiy,NULL);
	    ::LineTo(hdc,Right+10,xposiy);
		if(m_Cdf.m_bAxes[2]!=2)
		{
	      ::MoveToEx(hdc,Right+5,xposiy-3,NULL);
	      ::LineTo(hdc,Right+10,xposiy);
		  ::MoveToEx(hdc,Right+5,xposiy+3,NULL);
	      ::LineTo(hdc,Right+10,xposiy);
		}
		else
		{
	      ::MoveToEx(hdc,Left-5,xposiy-3,NULL);
	      ::LineTo(hdc,Left-10,xposiy);
		  ::MoveToEx(hdc,Left-5,xposiy+3,NULL);
	      ::LineTo(hdc,Left-10,xposiy);
		}
		break;
	  default:
		break;
   }
   //++++++++++++++++++The ticks+++++++++++++++++++++++
   
   if(m_Cdf.m_bCurveStyle[5]>0)
   {
     ::SelectObject(hdc,pen[4]);
	 for(i=1;i<m_Cdf.m_bAxes[3];i++)
	 {
	   switch(m_Cdf.m_bAxes[1])
	   {
	     case 0:
		  posix=Left+(int)(i*gridspacex);
	      posiy=Bottom;
		  break;
	     case 1:
		  posix=Left+(int)(i*gridspacex);
	      posiy=Bottom-(int)((double)(m_Cdf.m_bAxes[4]/2)*gridspacey);
		  break;
         case 2:
		  posix=Left+(int)(i*gridspacex);
	      posiy=Up;
		  break;
		 default:
		  break;
	   }
	   ::MoveToEx(hdc,posix,posiy,NULL);
	   switch(m_Cdf.m_bAxes[1])
	   {
	     case 0:
		  posix=Left+(int)(i*gridspacex);
	      posiy=Bottom-5;
	      break;
	     case 1:
		  posix=Left+(int)(i*gridspacex);
	      posiy=Bottom-(int)((double)(m_Cdf.m_bAxes[4]/2)*gridspacey)-5;
		  break;
         case 2:
		  posix=Left+(int)(i*gridspacex);
	      posiy=Up+5;
		  break;
		 default:
		  break;
	   }
	   ::LineTo(hdc,posix,posiy);
	 }
	 for(i=1;i<m_Cdf.m_bAxes[4];i++)
	 {
	   switch(m_Cdf.m_bAxes[2])
	   {
	     case 0:
	       posix=Left;
	       posiy=Bottom-(int)(i*gridspacey);
		   break;
		 case 1:
	       posix=Left+(int)((double)(m_Cdf.m_bAxes[3]/2)*gridspacex);
	       posiy=Bottom-(int)(i*gridspacey);
		   break;
		 case 2:
	       posix=Right;
	       posiy=Bottom-(int)(i*gridspacey);
		   break;
		 default:
		   break;
	   }
	   ::MoveToEx(hdc,posix,posiy,NULL);
	   switch(m_Cdf.m_bAxes[2])
	   {
	     case 0:
	       posix=Left+5;
	       posiy=Bottom-(int)(i*gridspacey);
		   break;
		 case 1:
	       posix=Left+(int)((double)(m_Cdf.m_bAxes[3]/2)*gridspacex)+5;
	       posiy=Bottom-(int)(i*gridspacey);
		   break;
		 case 2:
	       posix=Right-5;
	       posiy=Bottom-(int)(i*gridspacey);
		   break;
		 default:
		   break;
	   }
	   ::LineTo(hdc,posix,posiy);
	 }
   }
   //++++++++++++++++++The Digits+++++++++++++++++++++++
   displayx[0]=m_Cdf.m_dMinMaxInput[0];
   displayx[m_Cdf.m_bAxes[3]]=m_Cdf.m_dMinMaxInput[1];
   for(i=1;i<m_Cdf.m_bAxes[3];i++)
     displayx[i]=(m_Cdf.m_dMinMaxInput[1]-m_Cdf.m_dMinMaxInput[0])*(double)i/(double)m_Cdf.m_bAxes[3]+m_Cdf.m_dMinMaxInput[0];
   displayy[0]=m_Cdf.m_dMinMaxInput[2];
   displayy[m_Cdf.m_bAxes[4]]=m_Cdf.m_dMinMaxInput[3];
   for(i=1;i<m_Cdf.m_bAxes[4];i++)
     displayy[i]=(m_Cdf.m_dMinMaxInput[3]-m_Cdf.m_dMinMaxInput[2])*(double)i/(double)m_Cdf.m_bAxes[4]+m_Cdf.m_dMinMaxInput[2];   
   CString temp,tp;
   double times,diff;
   char tmp[40];
   if(m_Cdf.m_bAxes[6]>0)
   {
	 ::SetTextColor(hdc,Colors[m_Cdf.m_bAxes[9]]);
	 ::SetBkMode(hdc,TRANSPARENT);
	 diff=m_Cdf.m_dMinMaxInput[1]-m_Cdf.m_dMinMaxInput[0];
	 if(diff<0.000001)
	 {
		 times=1000000.0;
		 tp="(x10^-6)";
	 }
	 else if(diff>=0.000001&&diff<0.00001)
	 {
		 times=100000.0;
		 tp="(x10^-5)";
	 }
     else if(diff>=0.00001&&diff<0.0001)
	 {
		 times=10000.0;
		 tp="(x10^-4)";
	 }
     else if(diff>=0.0001&&diff<0.001)
	 {
		 times=1000.0;
		 tp="(x0.001)";
	 }
     else if(diff>=0.001&&diff<0.01)
	 {
		 times=100.0;
		 tp="(x0.01)";
	 }
     else if(diff>=0.01&&diff<10)
	 {
		 times=1;
		 tp="";
	 }
     else if(diff>=10&&diff<100)
	 {
		 times=0.1;
		 tp="(x10)";
	 }
     else if(diff>=100&&diff<1000)
	 {
		 times=0.01;
		 tp="(x100)";
	 }
     else if(diff>=1000&&diff<10000)
	 {
		 times=0.001;
		 tp="(x1000)";
	 }
     else if(diff>=10000&&diff<100000)
	 {
		 times=0.0001;
		 tp="(x10^4)";
	 }
     else if(diff>=100000&&diff<1000000)
	 {
		 times=0.00001;
		 tp="(x10^5)";
	 }
	 else if(diff>=1000000&&diff<10000000)
	 {
		 times=0.000001;
		 tp="(x10^6)";
	 }
	 else if(diff>=10000000&&diff<100000000)
	 {
		 times=0.0000001;
		 tp="(x10^7)";
	 }
	 else if(diff>=1000000000)
	 {
		 times=0.00000001;
		 tp="(x10^8)";
	 }
     for(i=0;i<=m_Cdf.m_bAxes[3];i++)
	 {
	   sprintf(tmp,"%.2f",displayx[i]*times);
	   temp=tmp;
	   if(cases==0)
	   {
		 ::SetTextAlign(hdc,TA_LEFT);
		 posix=Left+(int)(i*(double)Width/(double)m_Cdf.m_bAxes[3])-10;
	     posiy=Bottom+8;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy+16,tp,tp.GetLength());
	   }
	   else if(cases==1)
	   {
	     ::SetTextAlign(hdc,TA_LEFT);
		 posix=Left+(int)(i*(double)Width/(double)m_Cdf.m_bAxes[3])-10;
	     posiy=Up-28;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy-16,tp,tp.GetLength());
	   }
	   else if(cases==2)
	   {
	     ::SetTextAlign(hdc,TA_RIGHT);
		 posix=Right-(int)(i*(double)Width/(double)m_Cdf.m_bAxes[3])+10;
	     posiy=Bottom+8;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy+16,tp,tp.GetLength());
	   }
	   else
	   {
	     ::SetTextAlign(hdc,TA_RIGHT);
		 posix=Right-(int)(i*(double)Width/(double)m_Cdf.m_bAxes[3])+10;
	     posiy=Up-28;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy-16,tp,tp.GetLength());
	   }
	   ::TextOut(hdc,posix,posiy,temp,temp.GetLength());
	   
	 }
	 diff=m_Cdf.m_dMinMaxInput[3]-m_Cdf.m_dMinMaxInput[2];
	 if(diff<0.000001)
	 {
		 times=1000000.0;
		 tp="(x10^-6)";
	 }
	 else if(diff>=0.000001&&diff<0.00001)
	 {
		 times=100000.0;
		 tp="(x10^-5)";
	 }
     else if(diff>=0.00001&&diff<0.0001)
	 {
		 times=10000.0;
		 tp="(x10^-4)";
	 }
     else if(diff>=0.0001&&diff<0.001)
	 {
		 times=1000.0;
		 tp="(x0.001)";
	 }
     else if(diff>=0.001&&diff<0.01)
	 {
		 times=100.0;
		 tp="(x0.01)";
	 }
     else if(diff>=0.01&&diff<10)
	 {
		 times=1;
		 tp="";
	 }
     else if(diff>=10&&diff<100)
	 {
		 times=0.1;
		 tp="(x10)";
	 }
     else if(diff>=100&&diff<1000)
	 {
		 times=0.01;
		 tp="(x100)";
	 }
     else if(diff>=1000&&diff<10000)
	 {
		 times=0.001;
		 tp="(x1000)";
	 }
     else if(diff>=10000&&diff<100000)
	 {
		 times=0.0001;
		 tp="(x10^4)";
	 }
     else if(diff>=100000&&diff<1000000)
	 {
		 times=0.00001;
		 tp="(x10^5)";
	 }
	 else if(diff>=1000000&&diff<10000000)
	 {
		 times=0.000001;
		 tp="(x10^6)";
	 }
	 else if(diff>=10000000&&diff<100000000)
	 {
		 times=0.0000001;
		 tp="(x10^7)";
	 }
	 else if(diff>=1000000000)
	 {
		 times=0.00000001;
		 tp="(x10^8)";
	 }
     for(i=0;i<=m_Cdf.m_bAxes[4];i++)
	 {
	   if(cases==0)
	   {
         ::SetTextAlign(hdc,TA_RIGHT);
		 posix=Left-10;
	     posiy=Bottom-(int)(i*(double)Height/(double)m_Cdf.m_bAxes[4])-10;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy+16,tp,tp.GetLength());
	   }
	   else if(cases==1)
	   {
         ::SetTextAlign(hdc,TA_RIGHT);
		 posix=Left-10;
	     posiy=Up+(int)(i*(double)Height/(double)m_Cdf.m_bAxes[4])+10;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy-16,tp,tp.GetLength());
	   }
	   else if(cases==2)
	   {
         ::SetTextAlign(hdc,TA_LEFT);
		 posix=Right+10;
	     posiy=Bottom-(int)(i*(double)Height/(double)m_Cdf.m_bAxes[4])-10;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy+16,tp,tp.GetLength());
	   }
	   else if(cases==3)
	   {
         ::SetTextAlign(hdc,TA_LEFT);
		 posix=Right+10;
	     posiy=Up+(int)(i*(double)Height/(double)m_Cdf.m_bAxes[4])-10;
		 if(i==m_Cdf.m_bAxes[3])
	     ::TextOut(hdc,posix,posiy-16,tp,tp.GetLength());
	   }
	   sprintf(tmp,"%.2f",displayy[i]*times);
	   temp=tmp;
	   ::TextOut(hdc,posix,posiy,temp,temp.GetLength());
	 }
   }
   //++++++++Display Title++++++++
   if(m_Cdf.m_bTitleStyle[0]>0)
   {
       ::SetTextColor(hdc,Colors[m_Cdf.m_bTitleStyle[1]]);
	   ::SetBkMode(hdc,TRANSPARENT);
	   ::SetTextAlign(hdc,TA_LEFT);
	   temp=m_Cdf.m_sTitles[1];
	   posix=Left+Width/2-4*temp.GetLength();
	   posiy=BottomE-24;
	   ::TextOut(hdc,posix,posiy,temp,temp.GetLength());
   }
   if(m_Cdf.m_bTitleStyle[2]>0)
   {
       ::SetTextColor(hdc,Colors[m_Cdf.m_bTitleStyle[3]]);
	   ::SetBkMode(hdc,TRANSPARENT);
	   temp=m_Cdf.m_sTitles[2];
	   if(cases==0)
	   { 
		   ::SetTextAlign(hdc,TA_LEFT);
	       posix=Left+Width/2-4*temp.GetLength();
	       posiy=Bottom+24;
	   }
	   else if(cases==1)
	   {
		   ::SetTextAlign(hdc,TA_LEFT);
	       posix=Left+Width/2-4*temp.GetLength();
	       posiy=Up-48;
	   }
	   else if(cases==2)
	   {
		   ::SetTextAlign(hdc,TA_RIGHT);
	       posix=Right-Width/2+4*temp.GetLength();
	       posiy=Bottom+24;	   
	   }
	   else if(cases==3)
	   {
		   ::SetTextAlign(hdc,TA_RIGHT);
	       posix=Right-Width/2+4*temp.GetLength();
	       posiy=Up-48;	   
	   }
	   ::TextOut(hdc,posix,posiy,temp,temp.GetLength());
   }
   if(m_Cdf.m_bTitleStyle[4]>0)
   {
       ::SetTextColor(hdc,Colors[m_Cdf.m_bTitleStyle[1]]);
	   ::SetBkMode(hdc,TRANSPARENT);
	   
	   if(cases==0)
	   {
	     ::SetTextAlign(hdc,TA_LEFT);
		 posix=Left+5;
	     posiy=Up-20;
	   }
	   else if(cases==1)
	   {
	     ::SetTextAlign(hdc,TA_LEFT);
		 posix=Left+5;
	     posiy=Bottom+15;
	   }
	   else if(cases==2)
	   {
	     ::SetTextAlign(hdc,TA_RIGHT);
		 posix=Right-5;
	     posiy=Up-20;
	   }
	   else if(cases==3)
	   {
	     ::SetTextAlign(hdc,TA_RIGHT);
		 posix=Right-5;
	     posiy=Bottom+15;
	   }
	   temp=m_Cdf.m_sTitles[3];
       ::TextOut(hdc,posix,posiy,temp,temp.GetLength());
   }
   return true;
}
bool CDrawCurve::SaveCurve(HDC hdc,int Left,int LeftE,int Right,int RightE,int Up,int UpE,int Bottom,int BottomE)
{
  int Width,Height;
  int WidthE,HeightE;
  int i,j,l;
  long int fh;
  long linebytes,w,p,q;
  WORD bmPlanes; 
  WORD bmBitsPixel; 
  HBITMAP hbmp;
  HDC hmemdc;
  BITMAP bmp;
  HGLOBAL bmpbits;
  unsigned char *bmBits,*bmBits24;
  BITMAPFILEHEADER bitfile;
  BITMAPINFOHEADER bitinfo;
  CString FileName;
  //judge the input data
  if(LeftE<0||UpE<0)return false;
  if(Left<=LeftE)return false;
  if(Left>=Right)return false;
  if(RightE<=Right)return false;
  if(Up<=UpE)return false;
  if(BottomE<=Bottom)return false;
  if(Up>=Bottom)return false;
  
  //Compute the width and height
  WidthE=RightE-LeftE;
  HeightE=BottomE-UpE;
  Width=Right-Left;
  Height=Bottom-Up;
  
  //create hmemdc and hbmp from hdc
  hmemdc=CreateCompatibleDC(hdc);
  if(hmemdc==NULL)return false;
  hbmp=CreateCompatibleBitmap(hdc,WidthE,HeightE);
  if(hbmp==NULL)
  {
      DeleteObject(hmemdc);
	  return false;
  }
  //draw curve in memory
  if(SelectObject(hmemdc,hbmp)==NULL) 
  {
      DeleteObject(hmemdc);
	  DeleteObject(hbmp);
	  return false;
  }
  DrawCurve(hmemdc,Left-LeftE,0,Right-LeftE,RightE-LeftE,Up-UpE,0,Bottom-UpE,BottomE-UpE);
  //get the bmp info
  if(GetObject(hbmp,sizeof(BITMAP),&bmp)==0)
  {
     DeleteObject(hmemdc);
	 DeleteObject(hbmp);
	 return false;
  }
  linebytes=bmp.bmWidthBytes;
  bmPlanes=bmp.bmPlanes;
  bmBitsPixel=bmp.bmBitsPixel;
  //apply the memory according to the info
  bmpbits=GlobalAlloc(GMEM_FIXED,linebytes*HeightE*2);
  if(bmpbits==NULL)
  {
	DeleteObject(hbmp);
    DeleteObject(hmemdc);
    return false;
  }
  bmBits=(unsigned char *)bmpbits; 
  bmBits24=(unsigned char *)bmpbits+linebytes*HeightE; 
  //Get the bitmap data
  GetBitmapBits(hbmp,linebytes*HeightE,bmBits);
  
  //change 32 to 24 bits image
  if(bmBitsPixel==32)
  {
    bmBitsPixel=24;
	w=(WidthE*24+31)/32*4;
	for(i=0;i<HeightE;i++)
	{
      for(j=0;j<WidthE;j++)
	  {
		 p=i*w+j*3;
		 q=i*linebytes+j*4;
		 for(l=0;l<3;l++)
		  bmBits24[p+l]=bmBits[q+l];
	  }
	}
	linebytes=w;
	memcpy(bmBits,bmBits24,linebytes*HeightE);
  }
  
  //Set the FILE and INFO Headers
  bitfile.bfOffBits=sizeof(bitfile)+sizeof(bitinfo);
  bitfile.bfReserved1=0;
  bitfile.bfReserved2=0;
  bitfile.bfSize=sizeof(bitfile)+sizeof(bitinfo)+linebytes*HeightE;
  bitfile.bfType=0x4d42;
  bitinfo.biBitCount=bmBitsPixel;
  bitinfo.biClrImportant=0;
  bitinfo.biClrUsed=0;
  bitinfo.biCompression=BI_RGB;
  bitinfo.biHeight=HeightE;
  bitinfo.biPlanes=bmPlanes;
  bitinfo.biSize=sizeof(bitinfo);
  bitinfo.biSizeImage=HeightE*linebytes;
  bitinfo.biWidth=WidthE;
  bitinfo.biXPelsPerMeter=1;
  bitinfo.biYPelsPerMeter=1;
  //Open a file dialog
  char BASED_CODE szFilter[]="BMP Files(*.bmp)|*.bmp|All Files(*.*)|*.*||";
  CFileDialog cfd(FALSE,"*.bmp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
  if(cfd.DoModal()!=IDOK)
  {
	DeleteObject(hbmp);
    DeleteObject(hmemdc);
    GlobalFree(bmpbits);
    return false;
  }
  //Get filename
  FileName=cfd.GetPathName();

  //open and save file
  fh=_open(FileName,_O_WRONLY|_O_CREAT,_S_IREAD|_S_IWRITE);
  if(fh==-1)
  {
	DeleteObject(hbmp);
    DeleteObject(hmemdc);
    GlobalFree(bmpbits);
    close(fh);
    return false;
  }
  if(_write(fh,&bitfile,sizeof(bitfile))!=sizeof(bitfile))
  {
	DeleteObject(hbmp);
    DeleteObject(hmemdc);
    GlobalFree(bmpbits);
    close(fh);
    return false;
  }
  if(_write(fh,&bitinfo,sizeof(bitinfo))!=sizeof(bitinfo))
  {
	DeleteObject(hbmp);
    DeleteObject(hmemdc);
    GlobalFree(bmpbits);
    close(fh);
    return false;
  }
  for(i=0;i<HeightE;i++)
  {
    if(_write(fh,bmBits+(HeightE-i-1)*linebytes,linebytes)!=linebytes)
	{
	  DeleteObject(hbmp);
      DeleteObject(hmemdc);
      GlobalFree(bmpbits);
      close(fh);
	  return false;
	}
  }
  DeleteObject(hbmp);
  DeleteObject(hmemdc);
  GlobalFree(bmpbits);
  close(fh);
  return true;
}
