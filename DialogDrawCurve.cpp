// DialogDrawCurve.cpp : implementation file
//

#include "stdafx.h"
#include "VQRETRIEVE.h"
#include "DialogDrawCurve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogDrawCurve dialog


CDialogDrawCurve::CDialogDrawCurve(CWnd* pParent/*=NULL*/)
	: CDialog(CDialogDrawCurve::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogDrawCurve)
	m_border = TRUE;
	m_figtitle = TRUE;
	m_showdigits = TRUE;
	m_showticks = TRUE;
	m_xtitle = TRUE;
	m_ytitle = TRUE;
	m_dlgtitle = _T("Dialog");
	m_sfigtitle = _T("Figure 1");
	m_xmax = 0.0;
	m_xmin = 0.0;
	m_sxtitle = _T("X axis");
	m_ymax = 0.0;
	m_ymin = 0.0;
	m_sytitle = _T("Y axis");
	m_xticks = 0;
	m_axescolor = 0;
	m_backcolor = 0;
	m_figtitlecolor = 0;
	m_gridcolor = 0;
	m_linecolor = 0;
	m_scalevcolor = 0;
	m_textcolor = 0;
	m_tickcolor = 0;
	m_xtitlecolor = 0;
	m_yticks = 0;
	m_ytitlecolor = 0;
	m_xminmaxstyle = -1;
	m_yminmaxstyle = -1;
	m_linestyle = -1;
	m_gridstyle = -1;
	m_scalevstyle = -1;
	m_axesstyle = -1;
	m_xaxisstyle = -1;
	m_yaxisstyle = -1;
	//}}AFX_DATA_INIT
}


void CDialogDrawCurve::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDrawCurve)
	DDX_Check(pDX, IDC_CHECK_BORDER, m_border);
	DDX_Check(pDX, IDC_CHECK_FIGTITLE, m_figtitle);
	DDX_Check(pDX, IDC_CHECK_SHOWDIGITS, m_showdigits);
	DDX_Check(pDX, IDC_CHECK_SHOWTICKS, m_showticks);
	DDX_Check(pDX, IDC_CHECK_XTITLE, m_xtitle);
	DDX_Check(pDX, IDC_CHECK_YTITLE, m_ytitle);
	DDX_Text(pDX, IDC_EDIT_DLGTITLE, m_dlgtitle);
	DDX_Text(pDX, IDC_EDIT_FIGTITLE, m_sfigtitle);
	DDX_Text(pDX, IDC_EDIT_XMAX, m_xmax);
	DDX_Text(pDX, IDC_EDIT_XMIN, m_xmin);
	DDX_Text(pDX, IDC_EDIT_XTITLE, m_sxtitle);
	DDX_Text(pDX, IDC_EDIT_YMAX, m_ymax);
	DDX_Text(pDX, IDC_EDIT_YMIN, m_ymin);
	DDX_Text(pDX, IDC_EDIT_YTITLE, m_sytitle);
	DDX_CBIndex(pDX, IDC_COMBO_XTICKS, m_xticks);
	DDX_CBIndex(pDX, IDC_COMBO_AXESCOLOR, m_axescolor);
	DDX_CBIndex(pDX, IDC_COMBO_BACKCOLOR, m_backcolor);
	DDX_CBIndex(pDX, IDC_COMBO_FIGTITLECOLOR, m_figtitlecolor);
	DDX_CBIndex(pDX, IDC_COMBO_GRIDCOLOR, m_gridcolor);
	DDX_CBIndex(pDX, IDC_COMBO_LINECOLOR, m_linecolor);
	DDX_CBIndex(pDX, IDC_COMBO_SCALEVCOLOR, m_scalevcolor);
	DDX_CBIndex(pDX, IDC_COMBO_TEXTCOLOR, m_textcolor);
	DDX_CBIndex(pDX, IDC_COMBO_TICKCOLOR, m_tickcolor);
	DDX_CBIndex(pDX, IDC_COMBO_XTITLECOLOR, m_xtitlecolor);
	DDX_CBIndex(pDX, IDC_COMBO_YTICKS, m_yticks);
	DDX_CBIndex(pDX, IDC_COMBO_YTITLECOLOR, m_ytitlecolor);
	DDX_Radio(pDX, IDC_RADIO_USER, m_xminmaxstyle);
	DDX_Radio(pDX, IDC_RADIO_USER3, m_yminmaxstyle);
	DDX_Radio(pDX, IDC_RADIO_POINT, m_linestyle);
	DDX_Radio(pDX, IDC_RADIO_GRIDLINENONE, m_gridstyle);
	DDX_Radio(pDX, IDC_RADIO_SCALEVNONE, m_scalevstyle);
	DDX_Radio(pDX, IDC_RADIO_AXESNONE, m_axesstyle);
	DDX_Radio(pDX, IDC_RADIO_XAXISBOTTOM, m_xaxisstyle);
	DDX_Radio(pDX, IDC_RADIO_YAXISLEFT, m_yaxisstyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDrawCurve, CDialog)
	//{{AFX_MSG_MAP(CDialogDrawCurve)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_EN_CHANGE(IDC_EDIT_XMAX, OnChangeEditXmax)
	ON_EN_CHANGE(IDC_EDIT_XMIN, OnChangeEditXmin)
	ON_EN_CHANGE(IDC_EDIT_XTITLE, OnChangeEditXtitle)
	ON_EN_CHANGE(IDC_EDIT_YMAX, OnChangeEditYmax)
	ON_EN_CHANGE(IDC_EDIT_YMIN, OnChangeEditYmin)
	ON_EN_CHANGE(IDC_EDIT_YTITLE, OnChangeEditYtitle)
	ON_BN_CLICKED(IDC_RADIO_AXESNONE, OnRadioAxesnone)
	ON_BN_CLICKED(IDC_RADIO_COMPUTE, OnRadioCompute)
	ON_BN_CLICKED(IDC_RADIO_COMPUTE3, OnRadioCompute3)
	ON_BN_CLICKED(IDC_RADIO_CONNECT, OnRadioConnect)
	ON_BN_CLICKED(IDC_RADIO_CONNECT2, OnRadioConnect2)
	ON_BN_CLICKED(IDC_RADIO_DASHARROW, OnRadioDasharrow)
	ON_BN_CLICKED(IDC_RADIO_DASHNOARROW, OnRadioDashnoarrow)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnRadioDefault)
	ON_BN_CLICKED(IDC_RADIO_GRIDDASH, OnRadioGriddash)
	ON_BN_CLICKED(IDC_RADIO_GRIDLINE, OnRadioGridline)
	ON_BN_CLICKED(IDC_RADIO_GRIDLINENONE, OnRadioGridlinenone)
	ON_BN_CLICKED(IDC_RADIO_HISTOGRAM, OnRadioHistogram)
	ON_BN_CLICKED(IDC_RADIO_HISTOGRAM2, OnRadioHistogram2)
	ON_BN_CLICKED(IDC_RADIO_LINEARROW, OnRadioLinearrow)
	ON_BN_CLICKED(IDC_RADIO_LINENOARROW, OnRadioLinenoarrow)
	ON_BN_CLICKED(IDC_RADIO_POINT, OnRadioPoint)
	ON_BN_CLICKED(IDC_RADIO_POINT2, OnRadioPoint2)
	ON_BN_CLICKED(IDC_RADIO_SINGLELINE, OnRadioSingleline)
	ON_BN_CLICKED(IDC_RADIO_SINGLELINE2, OnRadioSingleline2)
	ON_BN_CLICKED(IDC_RADIO_USER, OnRadioUser)
	ON_BN_CLICKED(IDC_RADIO_USER3, OnRadioUser3)
	ON_BN_CLICKED(IDC_RADIO_XAISMIDDLE, OnRadioXaismiddle)
	ON_BN_CLICKED(IDC_RADIO_XAISTOP, OnRadioXaistop)
	ON_BN_CLICKED(IDC_RADIO_XAXISBOTTOM, OnRadioXaxisbottom)
	ON_BN_CLICKED(IDC_RADIO_YAISMIDDLE, OnRadioYaismiddle)
	ON_BN_CLICKED(IDC_RADIO_YAISRIGHT, OnRadioYaisright)
	ON_BN_CLICKED(IDC_RADIO_YAXISLEFT, OnRadioYaxisleft)
	ON_CBN_SELCHANGE(IDC_COMBO_AXESCOLOR, OnSelchangeComboAxescolor)
	ON_CBN_SELCHANGE(IDC_COMBO_BACKCOLOR, OnSelchangeComboBackcolor)
	ON_CBN_SELCHANGE(IDC_COMBO_FIGTITLECOLOR, OnSelchangeComboFigtitlecolor)
	ON_CBN_SELCHANGE(IDC_COMBO_GRIDCOLOR, OnSelchangeComboGridcolor)
	ON_CBN_SELCHANGE(IDC_COMBO_LINECOLOR, OnSelchangeComboLinecolor)
	ON_CBN_SELCHANGE(IDC_COMBO_SCALEVCOLOR, OnSelchangeComboScalevcolor)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXTCOLOR, OnSelchangeComboTextcolor)
	ON_CBN_SELCHANGE(IDC_COMBO_TICKCOLOR, OnSelchangeComboTickcolor)
	ON_CBN_SELCHANGE(IDC_COMBO_XTICKS, OnSelchangeComboXticks)
	ON_CBN_SELCHANGE(IDC_COMBO_XTITLECOLOR, OnSelchangeComboXtitlecolor)
	ON_CBN_SELCHANGE(IDC_COMBO_YTICKS, OnSelchangeComboYticks)
	ON_CBN_SELCHANGE(IDC_COMBO_YTITLECOLOR, OnSelchangeComboYtitlecolor)
	ON_EN_CHANGE(IDC_EDIT_DLGTITLE, OnChangeEditDlgtitle)
	ON_EN_CHANGE(IDC_EDIT_FIGTITLE, OnChangeEditFigtitle)
	ON_BN_CLICKED(IDC_CHECK_BORDER, OnCheckBorder)
	ON_BN_CLICKED(IDC_CHECK_FIGTITLE, OnCheckFigtitle)
	ON_BN_CLICKED(IDC_CHECK_SHOWDIGITS, OnCheckShowdigits)
	ON_BN_CLICKED(IDC_CHECK_SHOWTICKS, OnCheckShowticks)
	ON_BN_CLICKED(IDC_CHECK_XTITLE, OnCheckXtitle)
	ON_BN_CLICKED(IDC_CHECK_YTITLE, OnCheckYtitle)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY, OnButtonDisplay)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
	ON_BN_CLICKED(IDC_RADIO_SCALEVNONE, OnRadioScalevnone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDialogDrawCurve::Data2View()
{
   m_yminmaxstyle=cdf.m_bHowtoGetMinMax[1];
   m_xminmaxstyle=cdf.m_bHowtoGetMinMax[0];
   if(m_xminmaxstyle>0)
   {
	 ((CWnd *)GetDlgItem(IDC_EDIT_XMIN))->EnableWindow(FALSE);
	 ((CWnd *)GetDlgItem(IDC_EDIT_XMAX))->EnableWindow(FALSE);
   }
   else
   {
	 ((CWnd *)GetDlgItem(IDC_EDIT_XMIN))->EnableWindow(TRUE);
	 ((CWnd *)GetDlgItem(IDC_EDIT_XMAX))->EnableWindow(TRUE);
   }
   if(m_yminmaxstyle>0)
   {
	 ((CWnd *)GetDlgItem(IDC_EDIT_YMIN))->EnableWindow(FALSE);
	 ((CWnd *)GetDlgItem(IDC_EDIT_YMAX))->EnableWindow(FALSE);
   }
   else
   {
	 ((CWnd *)GetDlgItem(IDC_EDIT_YMIN))->EnableWindow(TRUE);
	 ((CWnd *)GetDlgItem(IDC_EDIT_YMAX))->EnableWindow(TRUE);
   }
   m_xmin=cdf.m_dMinMaxInput[0];
   m_xmax=cdf.m_dMinMaxInput[1];
   m_ymin=cdf.m_dMinMaxInput[2];
   m_ymax=cdf.m_dMinMaxInput[3];
   m_linestyle=cdf.m_bCurveStyle[0];//linestyle
   m_border=cdf.m_bCurveStyle[1];//with Borders?
   m_gridstyle=cdf.m_bCurveStyle[2];//grid-linestyle
   m_linecolor=cdf.m_bCurveStyle[3];//curve color
   m_backcolor=cdf.m_bCurveStyle[4];//back color
   m_gridcolor=cdf.m_bCurveStyle[5];//grid color
   m_scalevstyle=cdf.m_bCurveStyle[6];//point the interval
   m_scalevcolor=cdf.m_bCurveStyle[7];//red point
   m_axesstyle=cdf.m_bAxes[0];
   m_xaxisstyle=cdf.m_bAxes[1];
   m_yaxisstyle=cdf.m_bAxes[2];
   m_xticks=cdf.m_bAxes[3]-2;//X-ticks
   m_yticks=cdf.m_bAxes[4]-2;//Y-ticks
   m_showticks=cdf.m_bAxes[5];//show tick lines?
   m_showdigits=cdf.m_bAxes[6];//show digit texts?
   m_axescolor=cdf.m_bAxes[7];//color of Axes
   m_tickcolor=cdf.m_bAxes[8];//color of Ticks
   m_textcolor=cdf.m_bAxes[9];//color of digits
   m_figtitle=cdf.m_bTitleStyle[0];
   m_xtitle=cdf.m_bTitleStyle[2];
   m_ytitle=cdf.m_bTitleStyle[4];
   m_figtitlecolor=cdf.m_bTitleStyle[1];
   m_xtitlecolor=cdf.m_bTitleStyle[3];
   m_ytitlecolor=cdf.m_bTitleStyle[5];
   m_dlgtitle=cdf.m_sTitles[0];
   m_sfigtitle=cdf.m_sTitles[1];
   m_sxtitle=cdf.m_sTitles[2];
   m_sytitle=cdf.m_sTitles[3];
   UpdateData(false);
}

void CDialogDrawCurve::View2Data()
{
   UpdateData(true);
   cdf.m_bHowtoGetMinMax[1]=m_yminmaxstyle;
   cdf.m_bHowtoGetMinMax[0]=m_xminmaxstyle;
   cdf.m_dMinMaxInput[0]=m_xmin;
   cdf.m_dMinMaxInput[1]=m_xmax;
   cdf.m_dMinMaxInput[2]=m_ymin;
   cdf.m_dMinMaxInput[3]=m_ymax;
   cdf.m_bCurveStyle[0]=m_linestyle;//linestyle
   cdf.m_bCurveStyle[1]=m_border;//with Borders?
   cdf.m_bCurveStyle[2]=m_gridstyle;//grid-linestyle
   cdf.m_bCurveStyle[3]=m_linecolor;//curve color
   cdf.m_bCurveStyle[4]=m_backcolor;//back color
   cdf.m_bCurveStyle[5]=m_gridcolor;//grid color
   cdf.m_bCurveStyle[6]=m_scalevstyle;//point the interval
   cdf.m_bCurveStyle[7]=m_scalevcolor;//red point
   cdf.m_bAxes[0]=m_axesstyle;
   cdf.m_bAxes[1]=m_xaxisstyle;
   cdf.m_bAxes[2]=m_yaxisstyle;
   cdf.m_bAxes[3]=m_xticks+2;//X-ticks
   cdf.m_bAxes[4]=m_yticks+2;//Y-ticks
   cdf.m_bAxes[5]=m_showticks;//show tick lines?
   cdf.m_bAxes[6]=m_showdigits;//show digit texts?
   cdf.m_bAxes[7]=m_axescolor;//color of Axes
   cdf.m_bAxes[8]=m_tickcolor;//color of Ticks
   cdf.m_bAxes[9]=m_textcolor;//color of digits
   cdf.m_bTitleStyle[0]=m_figtitle;
   cdf.m_bTitleStyle[2]=m_xtitle;
   cdf.m_bTitleStyle[4]=m_ytitle;
   cdf.m_bTitleStyle[1]=m_figtitlecolor;
   cdf.m_bTitleStyle[3]=m_xtitlecolor;
   cdf.m_bTitleStyle[5]=m_ytitlecolor;
   strcpy(cdf.m_sTitles[0],m_dlgtitle);
   strcpy(cdf.m_sTitles[1],m_sfigtitle);
   strcpy(cdf.m_sTitles[2],m_sxtitle);
   strcpy(cdf.m_sTitles[3],m_sytitle);
   c.SetCDFData(cdf);
   c.CheckCDFData();
   c.GetCDFData(&cdf);
}

void CDialogDrawCurve::MoveWindowtoPosition()
{
	MoveWindow(0,0,820,460);
	CenterWindow(NULL);

	((CWnd *)GetDlgItem(IDC_STATIC_GETMAXMIN))->MoveWindow(10,35,400,135);
	((CWnd *)GetDlgItem(IDC_STATIC_XMIN))->MoveWindow(15,52,40,25);
	((CWnd *)GetDlgItem(IDC_STATIC_XMAX))->MoveWindow(15,82,40,25);
	((CWnd *)GetDlgItem(IDC_STATIC_YMIN))->MoveWindow(15,112,40,25);
	((CWnd *)GetDlgItem(IDC_STATIC_YMAX))->MoveWindow(15,142,40,25);
	((CWnd *)GetDlgItem(IDC_RADIO_USER))->MoveWindow(60,65,80,25);
	((CWnd *)GetDlgItem(IDC_RADIO_USER3))->MoveWindow(60,125,80,25);
	((CWnd *)GetDlgItem(IDC_RADIO_COMPUTE))->MoveWindow(145,65,80,25);
	((CWnd *)GetDlgItem(IDC_RADIO_COMPUTE3))->MoveWindow(145,125,80,25);
	((CWnd *)GetDlgItem(IDC_RADIO_DEFAULT))->MoveWindow(230,65,80,25);
	((CWnd *)GetDlgItem(IDC_EDIT_XMIN))->MoveWindow(315,50,80,25);
	((CWnd *)GetDlgItem(IDC_EDIT_XMAX))->MoveWindow(315,80,80,25);
	((CWnd *)GetDlgItem(IDC_EDIT_YMIN))->MoveWindow(315,110,80,25);
	((CWnd *)GetDlgItem(IDC_EDIT_YMAX))->MoveWindow(315,140,80,25);
	
    ((CWnd *)GetDlgItem(IDC_STATIC_CURVESET))->MoveWindow(10,170,400,145);
	((CWnd *)GetDlgItem(IDC_STATIC_LINESTYLE))->MoveWindow(15,192,65,25);
	((CWnd *)GetDlgItem(IDC_STATIC_GRIDSTYLE))->MoveWindow(15,222,65,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_SCALEVSTYLE))->MoveWindow(15,252,65,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_LINECOLOR))->MoveWindow(15,282,65,25);

    ((CWnd *)GetDlgItem(IDC_RADIO_POINT))->MoveWindow(85,192,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_POINT))->MoveWindow(105,190,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_GRIDLINENONE))->MoveWindow(85,222,52,25);
    ((CWnd *)GetDlgItem(IDC_RADIO_SCALEVNONE))->MoveWindow(85,252,55,25);
	((CWnd *)GetDlgItem(IDC_COMBO_LINECOLOR))->MoveWindow(85,282,52,80);

    ((CWnd *)GetDlgItem(IDC_RADIO_CONNECT))->MoveWindow(142,192,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_CONNECT))->MoveWindow(162,190,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_GRIDDASH))->MoveWindow(142,222,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_GRIDDASH))->MoveWindow(162,220,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_POINT2))->MoveWindow(142,252,20,25);
	((CWnd *)GetDlgItem(IDC_STATIC_POINT2))->MoveWindow(162,250,32,32);
    ((CWnd *)GetDlgItem(IDC_STATIC_BACKCOLOR))->MoveWindow(142,282,57,25);
    
	((CWnd *)GetDlgItem(IDC_RADIO_CONNECT2))->MoveWindow(200,192,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_CONNECT2))->MoveWindow(220,190,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_GRIDLINE))->MoveWindow(200,222,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_GRIDLINE))->MoveWindow(220,220,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE2))->MoveWindow(200,252,20,25);
	((CWnd *)GetDlgItem(IDC_STATIC_SINGLELINE2))->MoveWindow(220,250,32,32);
    ((CWnd *)GetDlgItem(IDC_COMBO_BACKCOLOR))->MoveWindow(205,282,52,80);

    ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE))->MoveWindow(257,192,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_SINGLELINE))->MoveWindow(277,190,32,32);
    ((CWnd *)GetDlgItem(IDC_CHECK_BORDER))->MoveWindow(280,222,100,25);
    ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM2))->MoveWindow(258,252,20,25);
	((CWnd *)GetDlgItem(IDC_STATIC_HISTOGRAM2))->MoveWindow(278,250,32,32);
    ((CWnd *)GetDlgItem(IDC_STATIC_GRIDCOLOR))->MoveWindow(262,282,60,25);

    ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM))->MoveWindow(314,192,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_HISTOGRAM))->MoveWindow(334,190,32,32);
    ((CWnd *)GetDlgItem(IDC_STATIC_SCALEVCOLOR))->MoveWindow(320,252,35,25);
	((CWnd *)GetDlgItem(IDC_COMBO_SCALEVCOLOR))->MoveWindow(355,252,52,80);
    ((CWnd *)GetDlgItem(IDC_COMBO_GRIDCOLOR))->MoveWindow(330,282,52,80);
    
	((CWnd *)GetDlgItem(IDC_BUTTON_CHECK))->MoveWindow(20,330,80,30);
	((CWnd *)GetDlgItem(IDC_BUTTON_DISPLAY))->MoveWindow(120,330,80,30);
	((CWnd *)GetDlgItem(IDC_BUTTON_SAVE))->MoveWindow(220,330,80,30);
	((CWnd *)GetDlgItem(IDCANCEL))->MoveWindow(320,330,80,30);
	((CWnd *)GetDlgItem(IDC_BUTTON_RETURN))->ShowWindow(SW_HIDE);

    ((CWnd *)GetDlgItem(IDC_STATIC_AXESSET))->MoveWindow(420,35,380,175);
	((CWnd *)GetDlgItem(IDC_STATIC_AXESSTYLE))->MoveWindow(425,52,65,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_XAXIS))->MoveWindow(425,82,45,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_YAXIS))->MoveWindow(425,112,45,25);
    ((CWnd *)GetDlgItem(IDC_CHECK_SHOWTICKS))->MoveWindow(425,142,88,25);
    ((CWnd *)GetDlgItem(IDC_CHECK_SHOWDIGITS))->MoveWindow(425,172,92,25);

    ((CWnd *)GetDlgItem(IDC_RADIO_AXESNONE))->MoveWindow(490,52,60,25);
    ((CWnd *)GetDlgItem(IDC_RADIO_XAXISBOTTOM))->MoveWindow(470,82,65,25);
    ((CWnd *)GetDlgItem(IDC_RADIO_YAXISLEFT))->MoveWindow(470,112,50,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_TICKCOLOR))->MoveWindow(530,145,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_TEXTCOLOR))->MoveWindow(530,175,60,25);

    ((CWnd *)GetDlgItem(IDC_RADIO_LINENOARROW))->MoveWindow(550,52,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_LINENOARROW))->MoveWindow(570,52,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_XAISMIDDLE))->MoveWindow(535,82,60,25);
    ((CWnd *)GetDlgItem(IDC_RADIO_YAISMIDDLE))->MoveWindow(520,112,60,25);
    ((CWnd *)GetDlgItem(IDC_COMBO_TICKCOLOR))->MoveWindow(600,145,52,80);
    ((CWnd *)GetDlgItem(IDC_COMBO_TEXTCOLOR))->MoveWindow(600,175,52,80);

    ((CWnd *)GetDlgItem(IDC_RADIO_LINEARROW))->MoveWindow(610,52,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_LINEARROW))->MoveWindow(630,52,32,32);
    ((CWnd *)GetDlgItem(IDC_RADIO_XAISTOP))->MoveWindow(600,82,60,25);
    ((CWnd *)GetDlgItem(IDC_RADIO_YAISRIGHT))->MoveWindow(585,112,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_AXESCOLOR))->MoveWindow(660,145,60,25);

    ((CWnd *)GetDlgItem(IDC_RADIO_DASHNOARROW))->MoveWindow(670,52,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_DASHNOARROW))->MoveWindow(690,52,32,32);
    ((CWnd *)GetDlgItem(IDC_STATIC_XTICKS))->MoveWindow(660,84,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_YTICKS))->MoveWindow(660,114,60,25);
    ((CWnd *)GetDlgItem(IDC_COMBO_AXESCOLOR))->MoveWindow(720,145,52,80);

    ((CWnd *)GetDlgItem(IDC_RADIO_DASHARROW))->MoveWindow(730,52,20,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_DASHARROW))->MoveWindow(750,52,32,32);
    ((CWnd *)GetDlgItem(IDC_COMBO_XTICKS))->MoveWindow(720,84,52,80);
    ((CWnd *)GetDlgItem(IDC_COMBO_YTICKS))->MoveWindow(720,114,52,80);
	
	((CWnd *)GetDlgItem(IDC_STATIC_TITLESET))->MoveWindow(420,210,380,175);
	((CWnd *)GetDlgItem(IDC_STATIC_DLGTITLE))->MoveWindow(425,230,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_FIGTITLE))->MoveWindow(425,260,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_XTITLE))->MoveWindow(425,290,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_YTITLE))->MoveWindow(425,320,60,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_FIGTITLECOLOR))->MoveWindow(425,350,70,25);
	
	((CWnd *)GetDlgItem(IDC_EDIT_DLGTITLE))->MoveWindow(490,230,150,25);
    ((CWnd *)GetDlgItem(IDC_EDIT_FIGTITLE))->MoveWindow(490,260,150,25);
    ((CWnd *)GetDlgItem(IDC_EDIT_XTITLE))->MoveWindow(490,290,150,25);
    ((CWnd *)GetDlgItem(IDC_EDIT_YTITLE))->MoveWindow(490,320,150,25);
    ((CWnd *)GetDlgItem(IDC_COMBO_FIGTITLECOLOR))->MoveWindow(500,350,52,80);
	
    ((CWnd *)GetDlgItem(IDC_CHECK_FIGTITLE))->MoveWindow(650,260,100,25);
    ((CWnd *)GetDlgItem(IDC_CHECK_XTITLE))->MoveWindow(650,290,90,25);
    ((CWnd *)GetDlgItem(IDC_CHECK_YTITLE))->MoveWindow(650,320,90,25);
    ((CWnd *)GetDlgItem(IDC_STATIC_XTITLECOLOR))->MoveWindow(560,350,65,25);
	    
    ((CWnd *)GetDlgItem(IDC_COMBO_XTITLECOLOR))->MoveWindow(625,350,52,80);
    ((CWnd *)GetDlgItem(IDC_STATIC_YTITLECOLOR))->MoveWindow(677,350,65,25);
	
	((CWnd *)GetDlgItem(IDC_COMBO_YTITLECOLOR))->MoveWindow(742,350,52,80);
}

void CDialogDrawCurve::MakeWindowVisible(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
	{
	  MoveWindow(0,0,700,640);
	  CenterWindow(NULL);
	  SetWindowText(cdf.m_sTitles[0]);
	  ((CWnd *)GetDlgItem(IDC_BUTTON_RETURN))->ShowWindow(SW_SHOW);
	  ((CWnd *)GetDlgItem(IDC_BUTTON_RETURN))->MoveWindow(300,560,60,30);
	}
	else
	{
	  MoveWindow(0,0,820,460);
	  SetWindowText("Curve Setting Dialog");
	  CenterWindow(NULL);
	  ((CWnd *)GetDlgItem(IDC_BUTTON_RETURN))->ShowWindow(SW_HIDE);
	}

	((CWnd *)GetDlgItem(IDC_STATIC_GETMAXMIN))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_XMIN))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_XMAX))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_YMIN))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_YMAX))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_RADIO_USER))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_RADIO_USER3))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_RADIO_COMPUTE))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_RADIO_COMPUTE3))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_RADIO_DEFAULT))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_EDIT_XMIN))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_EDIT_XMAX))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_EDIT_YMIN))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_EDIT_YMAX))->ShowWindow(nCmdShow);
	
    ((CWnd *)GetDlgItem(IDC_STATIC_CURVESET))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_LINESTYLE))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_GRIDSTYLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_SCALEVSTYLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_LINECOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_POINT))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_POINT))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_GRIDLINENONE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_SCALEVNONE))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_RADIO_POINT2))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_POINT2))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_LINECOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_CONNECT))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_CONNECT))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_GRIDDASH))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_GRIDDASH))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE2))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_SINGLELINE2))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_BACKCOLOR))->ShowWindow(nCmdShow);
    
	((CWnd *)GetDlgItem(IDC_RADIO_CONNECT2))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_CONNECT2))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_GRIDLINE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_GRIDLINE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM2))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_HISTOGRAM2))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_BACKCOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_SINGLELINE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_CHECK_BORDER))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_SCALEVCOLOR))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_GRIDCOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_HISTOGRAM))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_SCALEVCOLOR))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_GRIDCOLOR))->ShowWindow(nCmdShow);
    
	((CWnd *)GetDlgItem(IDC_BUTTON_CHECK))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_BUTTON_DISPLAY))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_BUTTON_SAVE))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDCANCEL))->ShowWindow(nCmdShow);
	
    ((CWnd *)GetDlgItem(IDC_STATIC_AXESSET))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_AXESSTYLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_XAXIS))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_YAXIS))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_CHECK_SHOWTICKS))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_CHECK_SHOWDIGITS))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_AXESNONE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_XAXISBOTTOM))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_YAXISLEFT))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_TICKCOLOR))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_TEXTCOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_LINENOARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_LINENOARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_XAISMIDDLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_YAISMIDDLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_TICKCOLOR))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_TEXTCOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_LINEARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_LINEARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_XAISTOP))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_RADIO_YAISRIGHT))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_AXESCOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_DASHNOARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_DASHNOARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_XTICKS))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_YTICKS))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_AXESCOLOR))->ShowWindow(nCmdShow);

    ((CWnd *)GetDlgItem(IDC_RADIO_DASHARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_DASHARROW))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_XTICKS))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_YTICKS))->ShowWindow(nCmdShow);
	
	((CWnd *)GetDlgItem(IDC_STATIC_TITLESET))->ShowWindow(nCmdShow);
	((CWnd *)GetDlgItem(IDC_STATIC_DLGTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_FIGTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_XTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_YTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_FIGTITLECOLOR))->ShowWindow(nCmdShow);
	
	((CWnd *)GetDlgItem(IDC_EDIT_DLGTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_EDIT_FIGTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_EDIT_XTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_EDIT_YTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_COMBO_FIGTITLECOLOR))->ShowWindow(nCmdShow);
	
    ((CWnd *)GetDlgItem(IDC_CHECK_FIGTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_CHECK_XTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_CHECK_YTITLE))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_XTITLECOLOR))->ShowWindow(nCmdShow);
	    
    ((CWnd *)GetDlgItem(IDC_COMBO_XTITLECOLOR))->ShowWindow(nCmdShow);
    ((CWnd *)GetDlgItem(IDC_STATIC_YTITLECOLOR))->ShowWindow(nCmdShow);
	
	((CWnd *)GetDlgItem(IDC_COMBO_YTITLECOLOR))->ShowWindow(nCmdShow);
}
/////////////////////////////////////////////////////////////////////////////
// CDialogDrawCurve message handlers
BOOL CDialogDrawCurve::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	MoveWindowtoPosition();
	showhide=SW_SHOW;
	confirm=false;
	//Initial DrawCurve Class
    c.m_DataX=m_dDataX;
    c.m_DataY=m_dDataY;
    c.m_Dimension=m_bSampleDimensions;
    c.m_Length=m_lNumberofSamples;
    c.SetCDFData(cdf);
    c.CheckCDFData();
    c.GetCDFData(&cdf);
    if(c.CheckInputData()==false)
	{ 
	  MessageBox("Sorry,Number of Samples is too big, or SampleDimensions is not 1 or 2, or No data input!");
	  OnOK();
    }
	if(m_bSampleDimensions==1)
    {
     ((CWnd *)GetDlgItem(IDC_RADIO_COMPUTE))->EnableWindow(FALSE);
     ((CWnd *)GetDlgItem(IDC_RADIO_SCALEVNONE))->EnableWindow(TRUE);
	 ((CWnd *)GetDlgItem(IDC_RADIO_POINT2))->EnableWindow(TRUE);
     ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE))->EnableWindow(TRUE);
     ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM))->EnableWindow(TRUE);
	 ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE2))->EnableWindow(TRUE);
     ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM2))->EnableWindow(TRUE);
     ((CWnd *)GetDlgItem(IDC_COMBO_SCALEVCOLOR))->EnableWindow(TRUE);
	 ((CWnd *)GetDlgItem(IDC_RADIO_DEFAULT))->EnableWindow(TRUE);
	 
    }
    else
    {
     ((CWnd *)GetDlgItem(IDC_RADIO_COMPUTE))->EnableWindow(TRUE);
	 ((CWnd *)GetDlgItem(IDC_RADIO_SCALEVNONE))->EnableWindow(FALSE);
     ((CWnd *)GetDlgItem(IDC_RADIO_POINT2))->EnableWindow(FALSE);
     ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE))->EnableWindow(FALSE);
     ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM))->EnableWindow(FALSE);
	 ((CWnd *)GetDlgItem(IDC_RADIO_SINGLELINE2))->EnableWindow(FALSE);
     ((CWnd *)GetDlgItem(IDC_RADIO_HISTOGRAM2))->EnableWindow(FALSE);
     ((CWnd *)GetDlgItem(IDC_COMBO_SCALEVCOLOR))->EnableWindow(FALSE);
	 ((CWnd *)GetDlgItem(IDC_RADIO_DEFAULT))->EnableWindow(FALSE);
    }
	Data2View();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogDrawCurve::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CString tem="",tem1;
	char str[100];
	if(m_bSampleDimensions==1)
     tem="The data dimension is 1";
	else if(m_bSampleDimensions==2)
	  tem="The data dimension is 2";
	sprintf(str," and the length of data is %ld",m_lNumberofSamples);
	tem=tem+str;
	::SetTextColor(dc.m_hDC,RGB(255,0,0));
	::SetMapMode(dc.m_hDC,MM_TEXT);
	::SetBkMode(dc.m_hDC,TRANSPARENT);
	if(showhide==SW_SHOW)
	::TextOut(dc.m_hDC,200,3,tem,tem.GetLength());
	else
    ::TextOut(dc.m_hDC,100,3,tem,tem.GetLength());
	// Do not call CDialog::OnPaint() for painting messages
	/*if(c.SaveCurve(GetDC()->m_hDC,100,20,600,670,70,25,470,540)==false)
	{
	  MessageBox("Sorry, Save File Failed!","Inform",MB_ICONSTOP|MB_OK);
	  return;
	}*/
}

void CDialogDrawCurve::OnButtonCheck() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
	confirm=true;
}

void CDialogDrawCurve::OnChangeEditXmax() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditXmin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditXtitle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditYmax() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditYmin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditYtitle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioAxesnone() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioCompute() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
	View2Data();
	Data2View();
}

void CDialogDrawCurve::OnRadioCompute3() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
	View2Data();
	Data2View();
}

void CDialogDrawCurve::OnRadioConnect() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioConnect2() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioDasharrow() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioDashnoarrow() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioDefault() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
	View2Data();
	Data2View();
}

void CDialogDrawCurve::OnRadioGriddash() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioGridline() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioGridlinenone() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioHistogram() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioHistogram2() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioLinearrow() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioLinenoarrow() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioPoint() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioPoint2() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioSingleline() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioSingleline2() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioUser() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
    View2Data();
	Data2View();
}

void CDialogDrawCurve::OnRadioUser3() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
	View2Data();
	Data2View();
}

void CDialogDrawCurve::OnRadioXaismiddle() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioXaistop() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioXaxisbottom() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioYaismiddle() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioYaisright() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnRadioYaxisleft() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboAxescolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboBackcolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboFigtitlecolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboGridcolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboLinecolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboScalevcolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboTextcolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboTickcolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboXticks() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboXtitlecolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboYticks() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnSelchangeComboYtitlecolor() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditDlgtitle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnChangeEditFigtitle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnCheckBorder() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnCheckFigtitle() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnCheckShowdigits() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnCheckShowticks() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnCheckXtitle() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnCheckYtitle() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}

void CDialogDrawCurve::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	if(confirm==false)
	{
	  MessageBox("Please first confirm!","Inform",MB_ICONSTOP|MB_OK);
	  return;
	}
	if(c.SaveCurve(GetDC()->m_hDC,100,20,600,680,80,30,480,550)==false)
	{
	  MessageBox("Sorry, Save File Failed!","Inform",MB_ICONSTOP|MB_OK);
	  return;
	}

}

void CDialogDrawCurve::OnButtonDisplay() 
{
	// TODO: Add your control notification handler code here
	if(confirm==false)
	{
	  MessageBox("Please first confirm!","Inform",MB_ICONSTOP|MB_OK);
	  return;
	}
	//CWnd
	Invalidate(TRUE);
	MakeWindowVisible(SW_HIDE);
    if(c.DrawCurve(GetDC()->m_hDC,100,20,600,680,80,30,480,550)==false)
	{
	  MessageBox("Sorry, Error in displaying curve", "Error!",MB_ICONSTOP|MB_OK);
	}
	showhide=SW_HIDE;
}

void CDialogDrawCurve::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	MakeWindowVisible(SW_SHOW);
	showhide=SW_SHOW;
	Invalidate(TRUE);
}

void CDialogDrawCurve::OnRadioScalevnone() 
{
	// TODO: Add your control notification handler code here
	confirm=false;
}
