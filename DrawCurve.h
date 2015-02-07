// DrawCurve.h: interface for the CDrawCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined (__DrawCurve_h)
#define __DrawCurve_h

static COLORREF Colors[10]={RGB(0,0,0)/*Black*/,RGB(255,255,255)/*White*/,RGB(128,128,128)/*Dark*/,RGB(192,192,192)/*Light*/,RGB(255,0,0)/*Red*/,RGB(0,255,0)/*Green*/,RGB(0,0,255)/*Blue*/,RGB(255,255,0),RGB(255,0,255),RGB(0,255,255)};
#define MAXTICKS 10
#define MAXSAMPLES 65536

typedef struct
{	
  //How to get the max min value from datax[] and datay[]?
  //[0]=0,1,2 Xmin=userinput,gotten from DataX,
  //               default(=0 only for 1-D) 
  //          Xmax=userinput,gotten from DataX,
  //               default(=NumberofSamples-1 only for 1-D)
  //[1]=0,1 Ymin=userinput,gotten from DataY
  //        Ymax=userinput,gotten from DataY
  BYTE m_bHowtoGetMinMax[2];
  //++++The users' max min inputs+++++
  //[0],[1] for 1-D data if Xmin>=Xmax,
  //then system sets Xmin=0,Xmax=NumberofSamples-1
  //[0] for 2-D,Xmin means the min of datax[];
  //[1] for 2-D,Xmax means the max of datax[];
  //[0],[1] for 2-D,if Xmin>=Xmax, seach maxmin in datax[]
  //for 1-D/2-D,X-interval-value-between-two-points
  //                    =(Xmax-Xmin)/NumberofSamples
  //for 1-D/2-D,X-value-between-two-displayinterval
  //                    =(Xmax-Xmin)/Xintervals
  //[2] for 1-D,Ymin means the min of datax[];
  //[2] for 2-D,Ymin means the min of datay[];
  //[3] for 1-D,Ymax means the max of datax[];
  //[3] for 2-D,Ymax means the max of datay[];
  //[2],[3] for 2-D, if Ymax<=Ymin, search maxmin in datay[]
  //for 2-D,Y-interval-value-between-two-points
  //        =(Ymax-Ymin)/NumberofSamples
  //for 2-D or 1-D,Y-value-between-two-displayinterval
  //               =(Ymax-Ymin)/Yintervals
  double m_dMinMaxInput[4];
  
  //++++Curvestyle++++++
  //[0] curve lining method 
  //[0]=0,1,2,3,4; point(1-D or 2-D),connected_solid(1-D or 2-D)
  //,connected_dash(1-D or 2-D),histogram-line(1-D),histogram-rectangle(1-D)
  //[1] with Borders?
  //[1]=0,1, without/with borders
  //[2] the grid-linestyle
  //[2]=0,1,2, None, dash, line
  //[3] curve color 
  //[3]=0-9, one of the ten colors
  //[4] Background color
  //[4]=0-9, one of the ten colors
  //[5] Border and grid color
  //[5]=0-9,one of the ten colors
  //[6] for 1-D,X displayinterval point denotation method
  //[6]=0,1,2,3; none,point,histogram-line,histogram-rectangle
  //[7] for 1-D,X displayInterval point denotation color
  //[7]=0-9,one of the ten colors
  BYTE m_bCurveStyle[8];
  
  //+++++Axes Style++++++++++
  //[0]=X/Y axis 0,1,2,3,4 none,line without arrow
  //line with arrow,dash without arrow,dash with arrow
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
  BYTE m_bAxes[10];
  
  //++++++++The titles++++++++++
  //[0]  DialogTitle[40];
  //[1]  Figuretitle[40];
  //[2]  X-title[40];
  //[3]  Y-title[40];
  char m_sTitles[4][40];
  
  //+++++The display style of titles+++++
  //[0] [1]:The display style of Figure title
  //[0]=0,1,2 none up down
  //[1]=color
  //[2][3]:The display style of X title
  //[2]=0,1,2 none middle up
  //[3]=color
  //[4][5]:The display style of Y title
  //[4]=0,1,2 none middle right
  //[5]=color
  BYTE m_bTitleStyle[6];
}CURVEDATAINFO;

class CDrawCurve  
{
public:
	CDrawCurve();
	virtual ~CDrawCurve();
    double *m_DataX;
	double *m_DataY;
	LONG m_Length;
	BYTE m_Dimension;
	bool CheckInputData();
	bool SetDefaultCDF();
	void SetCDFData(CURVEDATAINFO incdf);
	void GetCDFData(CURVEDATAINFO *outcdf);
	void CheckCDFData();
	bool DrawCurve(HDC hdc,int Left,int LeftE,int Right,int RightE,int Up,int UpE,int Bottom,int BottomE);
	bool SaveCurve(HDC hdc,int Left,int LeftE,int Right,int RightE,int Up,int UpE,int Bottom,int BottomE);
private:
    CURVEDATAINFO m_Cdf;
};

#endif // end of define
