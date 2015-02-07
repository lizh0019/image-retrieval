// DialogFeatureSelection.cpp : implementation file
//

#include "stdafx.h"
#include "VqRetrieve.h"
#include "DialogFeatureSelection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDialogFeatureSelection dialog


CDialogFeatureSelection::CDialogFeatureSelection(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFeatureSelection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFeatureSelection)
	m_checkcolor = FALSE;
	m_checkhist = FALSE;
	m_checkinva = FALSE;
	m_checkother = FALSE;
	m_checkshape = FALSE;
	m_checktexture = FALSE;
	m_bins = -1;
	m_bins2 = -1;
	m_colorhist = -1;
	m_colorspace = -1;
	m_colorspace2 = -1;
	m_colorspace3 = -1;
	m_coocurr = -1;
	m_description = -1;
	m_description2 = -1;
	m_howtodescribe = -1;
	m_pointnum = -1;
	m_dim = 0;
	m_dim2 = 0;
	m_dim3 = 0;
	m_dim4 = 0;
	m_dim5 = 0;
	m_feature1 = _T("");
	m_feature2 = _T("");
	m_feature3 = _T("");
	m_feature4 = _T("");
	m_kinds = 0;
	m_checkfeature1 = FALSE;
	m_checkfeature2 = FALSE;
	m_checkfeature3 = FALSE;
	m_checkfeature4 = FALSE;
	m_angle = -1;
	m_dim6 = 0;
	m_colorspace4 = -1;
	m_per1 = 0;
	m_per2 = 0;
	m_per3 = 0;
	m_per4 = 0;
	m_per5 = 0;
	m_per6 = 0;
	m_per7 = 0;
	m_per8 = 0;
	//}}AFX_DATA_INIT
}


void CDialogFeatureSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFeatureSelection)
	DDX_Check(pDX, IDC_CHECK_COLOR, m_checkcolor);
	DDX_Check(pDX, IDC_CHECK_INVARIANT, m_checkinva);
	DDX_Check(pDX, IDC_CHECK_OTHER, m_checkother);
	DDX_Check(pDX, IDC_CHECK_SHAPE, m_checkshape);
	DDX_Check(pDX, IDC_CHECK_TEXTURE, m_checktexture);
	DDX_CBIndex(pDX, IDC_COMBO_BINS, m_bins);
	DDX_CBIndex(pDX, IDC_COMBO_BINS2, m_bins2);
	DDX_CBIndex(pDX, IDC_COMBO_COLORHISTOGRAM, m_colorhist);
	DDX_CBIndex(pDX, IDC_COMBO_COLORSPACE, m_colorspace);
	DDX_CBIndex(pDX, IDC_COMBO_COLORSPACE2, m_colorspace2);
	DDX_CBIndex(pDX, IDC_COMBO_COLORSPACE3, m_colorspace3);
	DDX_CBIndex(pDX, IDC_COMBO_COOCURRENCE, m_coocurr);
	DDX_CBIndex(pDX, IDC_COMBO_DESCRIPTION, m_description);
	DDX_CBIndex(pDX, IDC_COMBO_DESCRIPTION2, m_description2);
	DDX_CBIndex(pDX, IDC_COMBO_HOWTODESCRIBE, m_howtodescribe);
	DDX_CBIndex(pDX, IDC_COMBO_POINTNUM, m_pointnum);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONS, m_dim);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONS2, m_dim2);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONS3, m_dim3);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONS4, m_dim4);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONS5, m_dim5);
	DDX_Text(pDX, IDC_EDIT_FEATURE1, m_feature1);
	DDX_Text(pDX, IDC_EDIT_FEATURE2, m_feature2);
	DDX_Text(pDX, IDC_EDIT_FEATURE3, m_feature3);
	DDX_Text(pDX, IDC_EDIT_FEATURE4, m_feature4);
	DDX_Text(pDX, IDC_EDIT_KINDS, m_kinds);
	DDX_Check(pDX, IDC_CHECK_FEATURE1, m_checkfeature1);
	DDX_Check(pDX, IDC_CHECK_FEATURE2, m_checkfeature2);
	DDX_Check(pDX, IDC_CHECK_FEATURE3, m_checkfeature3);
	DDX_Check(pDX, IDC_CHECK_FEATURE4, m_checkfeature4);
	DDX_CBIndex(pDX, IDC_COMBO_ANGLE, m_angle);
	DDX_Text(pDX, IDC_EDIT_DIMENSIONS6, m_dim6);
	DDX_CBIndex(pDX, IDC_COMBO_COLORSPACE4, m_colorspace4);
	DDX_Text(pDX, IDC_EDIT_PER1, m_per1);
	DDV_MinMaxInt(pDX, m_per1, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER2, m_per2);
	DDV_MinMaxInt(pDX, m_per2, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER3, m_per3);
	DDV_MinMaxInt(pDX, m_per3, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER4, m_per4);
	DDV_MinMaxInt(pDX, m_per4, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER5, m_per5);
	DDV_MinMaxInt(pDX, m_per5, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER6, m_per6);
	DDV_MinMaxInt(pDX, m_per6, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER7, m_per7);
	DDV_MinMaxInt(pDX, m_per7, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PER8, m_per8);
	DDV_MinMaxInt(pDX, m_per8, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFeatureSelection, CDialog)
	//{{AFX_MSG_MAP(CDialogFeatureSelection)
	ON_CBN_SELCHANGE(IDC_COMBO_BINS, OnSelchangeComboBins)
	ON_CBN_SELCHANGE(IDC_COMBO_BINS2, OnSelchangeComboBins2)
	ON_CBN_SELCHANGE(IDC_COMBO_COLORHISTOGRAM, OnSelchangeComboColorhistogram)
	ON_CBN_SELCHANGE(IDC_COMBO_COLORSPACE, OnSelchangeComboColorspace)
	ON_CBN_SELCHANGE(IDC_COMBO_COLORSPACE2, OnSelchangeComboColorspace2)
	ON_CBN_SELCHANGE(IDC_COMBO_COLORSPACE3, OnSelchangeComboColorspace3)
	ON_CBN_SELCHANGE(IDC_COMBO_COOCURRENCE, OnSelchangeComboCoocurrence)
	ON_CBN_SELCHANGE(IDC_COMBO_DESCRIPTION, OnSelchangeComboDescription)
	ON_CBN_SELCHANGE(IDC_COMBO_DESCRIPTION2, OnSelchangeComboDescription2)
	ON_CBN_SELCHANGE(IDC_COMBO_HOWTODESCRIBE, OnSelchangeComboHowtodescribe)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUM, OnSelchangeComboPointnum)
	ON_EN_CHANGE(IDC_EDIT_FEATURE1, OnChangeEditFeature1)
	ON_EN_CHANGE(IDC_EDIT_FEATURE2, OnChangeEditFeature2)
	ON_EN_CHANGE(IDC_EDIT_FEATURE3, OnChangeEditFeature3)
	ON_EN_CHANGE(IDC_EDIT_FEATURE4, OnChangeEditFeature4)
	ON_BN_CLICKED(IDC_CHECK_COLOR, OnCheckColor)
	ON_BN_CLICKED(IDC_CHECK_FEATURE1, OnCheckFeature1)
	ON_BN_CLICKED(IDC_CHECK_FEATURE2, OnCheckFeature2)
	ON_BN_CLICKED(IDC_CHECK_FEATURE3, OnCheckFeature3)
	ON_BN_CLICKED(IDC_CHECK_FEATURE4, OnCheckFeature4)
	ON_BN_CLICKED(IDC_CHECK_INVARIANT, OnCheckInvariant)
	ON_BN_CLICKED(IDC_CHECK_OTHER, OnCheckOther)
	ON_BN_CLICKED(IDC_CHECK_SHAPE, OnCheckShape)
	ON_BN_CLICKED(IDC_CHECK_TEXTURE, OnCheckTexture)
	ON_CBN_SELCHANGE(IDC_COMBO_ANGLE, OnSelchangeComboAngle)
	ON_CBN_SELCHANGE(IDC_COMBO_COLORSPACE4, OnSelchangeComboColorspace4)
	ON_EN_KILLFOCUS(IDC_EDIT_PER1, OnKillfocusEditPer1)
	ON_EN_KILLFOCUS(IDC_EDIT_PER2, OnKillfocusEditPer2)
	ON_EN_KILLFOCUS(IDC_EDIT_PER3, OnKillfocusEditPer3)
	ON_EN_KILLFOCUS(IDC_EDIT_PER4, OnKillfocusEditPer4)
	ON_EN_KILLFOCUS(IDC_EDIT_PER5, OnKillfocusEditPer5)
	ON_EN_KILLFOCUS(IDC_EDIT_PER6, OnKillfocusEditPer6)
	ON_EN_KILLFOCUS(IDC_EDIT_PER7, OnKillfocusEditPer7)
	ON_EN_KILLFOCUS(IDC_EDIT_PER8, OnKillfocusEditPer8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFeatureSelection message handlers

BOOL CDialogFeatureSelection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(readonly==TRUE)
	{
		SetWindowText("Feature Selected");
        GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	}
	else
	{
		SetWindowText("Feature Selection");
		GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
	}
	// TODO: Add extra initialization here
	MoveWindow(0,0,800,460);
	CenterWindow(NULL);
	
	GetDlgItem(IDC_CHECK_COLOR)->MoveWindow(10,5,100,25);
    GetDlgItem(IDC_STATIC_COLORFEATURE)->MoveWindow(10,30,240,150);
    GetDlgItem(IDC_STATIC_COLORSPACE)->MoveWindow(20,50,90,25);
	GetDlgItem(IDC_COMBO_COLORSPACE)->MoveWindow(150,50,90,80);
	GetDlgItem(IDC_STATIC_DESCRIPTION)->MoveWindow(20,80,50,25);
	GetDlgItem(IDC_COMBO_COLORHISTOGRAM)->MoveWindow(70,80,170,80);
	GetDlgItem(IDC_STATIC_BINS)->MoveWindow(20,110,130,25);
	GetDlgItem(IDC_COMBO_BINS)->MoveWindow(150,110,90,80);
    GetDlgItem(IDC_STATIC_DIMENSION)->MoveWindow(20,140,130,25);
	GetDlgItem(IDC_EDIT_DIMENSIONS)->MoveWindow(150,140,90,25);

	GetDlgItem(IDC_CHECK_INVARIANT)->MoveWindow(260,5,180,25);
	GetDlgItem(IDC_STATIC_RTINVARIANT)->MoveWindow(260,30,240,200);
	GetDlgItem(IDC_STATIC_COLORSPACE2)->MoveWindow(270,50,90,25);
	GetDlgItem(IDC_COMBO_COLORSPACE2)->MoveWindow(400,50,90,80);
	GetDlgItem(IDC_STATIC_DESCRIPTION1)->MoveWindow(270,80,50,25);
	GetDlgItem(IDC_COMBO_HOWTODESCRIBE)->MoveWindow(320,80,170,80);
	GetDlgItem(IDC_STATIC_POINTS)->MoveWindow(270,110,130,25);
    GetDlgItem(IDC_COMBO_POINTNUM)->MoveWindow(400,110,90,80);
	GetDlgItem(IDC_STATIC_ANGLES)->MoveWindow(270,140,130,25);
    GetDlgItem(IDC_COMBO_ANGLE)->MoveWindow(400,140,90,80);
	GetDlgItem(IDC_STATIC_BINS2)->MoveWindow(270,170,130,25);
    GetDlgItem(IDC_COMBO_BINS2)->MoveWindow(400,170,90,80);
    GetDlgItem(IDC_STATIC_DIMENSION2)->MoveWindow(270,200,130,25);
	GetDlgItem(IDC_EDIT_DIMENSIONS2)->MoveWindow(400,200,90,25);
	
    
	GetDlgItem(IDC_CHECK_TEXTURE)->MoveWindow(10,195,110,25);
	GetDlgItem(IDC_STATIC_TEXTUREFEATURE)->MoveWindow(10,220,240,160);
	GetDlgItem(IDC_STATIC_COLORSPACE3)->MoveWindow(20,240,130,25);
    GetDlgItem(IDC_COMBO_COLORSPACE3)->MoveWindow(150,240,90,80);
	GetDlgItem(IDC_STATIC_DESCRIPTION2)->MoveWindow(20,270,50,25);
    GetDlgItem(IDC_COMBO_DESCRIPTION)->MoveWindow(70,270,170,80);
	GetDlgItem(IDC_STATIC_COOCCURENCE)->MoveWindow(20,300,70,50);
    GetDlgItem(IDC_COMBO_COOCURRENCE)->MoveWindow(90,310,150,80);
	GetDlgItem(IDC_STATIC_DIMENSION3)->MoveWindow(20,350,130,25);
    GetDlgItem(IDC_EDIT_DIMENSIONS3)->MoveWindow(150,350,90,25);
	

	GetDlgItem(IDC_CHECK_SHAPE)->MoveWindow(260,245,180,25);
	GetDlgItem(IDC_STATIC_SHAPEFEATURE)->MoveWindow(260,270,240,110);
	GetDlgItem(IDC_STATIC_COLORSPACE4)->MoveWindow(270,290,130,25);
    GetDlgItem(IDC_COMBO_COLORSPACE4)->MoveWindow(400,290,90,80);
	GetDlgItem(IDC_STATIC_DESCRIPTION3)->MoveWindow(270,320,50,25);
    GetDlgItem(IDC_COMBO_DESCRIPTION2)->MoveWindow(320,320,170,80);
	GetDlgItem(IDC_STATIC_DIMENSION4)->MoveWindow(270,350,130,25);
    GetDlgItem(IDC_EDIT_DIMENSIONS4)->MoveWindow(400,350,90,25);
    
    GetDlgItem(IDC_CHECK_OTHER)->MoveWindow(520,5,180,25);
	GetDlgItem(IDC_STATIC_OTHERFEATURE)->MoveWindow(520,30,260,170);
	GetDlgItem(IDC_CHECK_FEATURE1)->MoveWindow(530,50,16,25);
	GetDlgItem(IDC_STATIC_FEATURE1)->MoveWindow(550,50,60,25);
	GetDlgItem(IDC_EDIT_FEATURE1)->MoveWindow(606,50,164,25);
	GetDlgItem(IDC_CHECK_FEATURE2)->MoveWindow(530,80,16,25);
	GetDlgItem(IDC_STATIC_FEATURE2)->MoveWindow(550,80,60,25);
	GetDlgItem(IDC_EDIT_FEATURE2)->MoveWindow(606,80,164,25);
	GetDlgItem(IDC_CHECK_FEATURE3)->MoveWindow(530,110,16,25);
	GetDlgItem(IDC_STATIC_FEATURE3)->MoveWindow(550,110,60,25);
	GetDlgItem(IDC_EDIT_FEATURE3)->MoveWindow(606,110,164,25);
	GetDlgItem(IDC_CHECK_FEATURE4)->MoveWindow(530,140,16,25);
	GetDlgItem(IDC_STATIC_FEATURE4)->MoveWindow(550,140,60,25);
	GetDlgItem(IDC_EDIT_FEATURE4)->MoveWindow(606,140,164,25);
	GetDlgItem(IDC_STATIC_DIMENSION5)->MoveWindow(530,170,120,25);
    GetDlgItem(IDC_EDIT_DIMENSIONS5)->MoveWindow(650,170,120,25);
    
	GetDlgItem(IDC_STATIC_TOTALSETTINGS)->MoveWindow(520,210,260,170);
	GetDlgItem(IDC_STATIC_FEATUREKINDS)->MoveWindow(530,230,120,25);
    GetDlgItem(IDC_EDIT_KINDS)->MoveWindow(660,230,80,25);
	GetDlgItem(IDC_STATIC_TOTALDIMENSION)->MoveWindow(530,260,140,25);
    GetDlgItem(IDC_EDIT_DIMENSIONS6)->MoveWindow(660,260,80,25);
	GetDlgItem(IDC_STATIC_WEIGHTS)->MoveWindow(530,290,200,25);
	GetDlgItem(IDC_STATIC_CF)->MoveWindow(530,320,20,25);
	GetDlgItem(IDC_EDIT_PER1)->MoveWindow(550,320,40,25);
	GetDlgItem(IDC_STATIC_IF)->MoveWindow(590,320,20,25);
	GetDlgItem(IDC_EDIT_PER2)->MoveWindow(610,320,40,25);
	GetDlgItem(IDC_STATIC_TF)->MoveWindow(650,320,20,25);
	GetDlgItem(IDC_EDIT_PER3)->MoveWindow(670,320,40,25);
	GetDlgItem(IDC_STATIC_SF)->MoveWindow(710,320,20,25);
	GetDlgItem(IDC_EDIT_PER4)->MoveWindow(730,320,40,25);
	GetDlgItem(IDC_STATIC_OF1)->MoveWindow(530,350,20,25);
	GetDlgItem(IDC_EDIT_PER5)->MoveWindow(550,350,40,25);
	GetDlgItem(IDC_STATIC_OF2)->MoveWindow(590,350,20,25);
	GetDlgItem(IDC_EDIT_PER6)->MoveWindow(610,350,40,25);
	GetDlgItem(IDC_STATIC_OF3)->MoveWindow(650,350,20,25);
	GetDlgItem(IDC_EDIT_PER7)->MoveWindow(670,350,40,25);
	GetDlgItem(IDC_STATIC_OF4)->MoveWindow(710,350,20,25);
	GetDlgItem(IDC_EDIT_PER8)->MoveWindow(730,350,40,25);

	GetDlgItem(IDOK)->MoveWindow(240,390,80,25);
    GetDlgItem(IDCANCEL)->MoveWindow(440,390,80,25);
    Data2View();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogFeatureSelection::Data2View()
{
	m_checkcolor=ffi.m_bWithColor;
	m_checkinva=ffi.m_bWithRTInvariant;
	m_checkother=ffi.m_bWithOthers;
	m_checkshape=ffi.m_bWithShape;
	m_checktexture=ffi.m_bWithTexture;
	
	//color
	m_colorspace=ffi.m_bColorSpace_CF;
	m_colorhist=ffi.m_bDescription_CF;
	m_bins=ffi.m_bBins_CF;
	m_dim=ffi.m_wDimension_CF;
	
	//invariant
	m_colorspace2=ffi.m_bColorSpace_IF;
	m_howtodescribe=ffi.m_bDescription_IF;
	m_bins2=ffi.m_bBins_IF;
	m_pointnum=ffi.m_bPoints_IF;
	m_angle=ffi.m_bAngles_IF;
	m_dim2=ffi.m_wDimension_IF;
    
	//texture
	m_colorspace3=ffi.m_bColorSpace_TF;
	m_description=ffi.m_bDescription_TF;
	m_coocurr=ffi.m_bCoocurrence_TF;
	m_dim3=ffi.m_wDimension_TF;
    
	//shape
	m_colorspace4=ffi.m_bColorSpace_SF;
	m_description2=ffi.m_bDescription_SF;
	m_dim4=ffi.m_wDimension_SF;
	
    //others
	m_checkfeature1=ffi.m_bWithFeature1_OF;
	m_checkfeature2=ffi.m_bWithFeature2_OF;
	m_checkfeature3=ffi.m_bWithFeature3_OF;
	m_checkfeature4=ffi.m_bWithFeature4_OF;
	m_feature1=ffi.m_sFeature1_OF;
	m_feature2=ffi.m_sFeature2_OF;
	m_feature3=ffi.m_sFeature3_OF;
	m_feature4=ffi.m_sFeature4_OF;
	m_dim5=ffi.m_wDimension_OF;
	
	//total
	m_kinds=ffi.m_bFeatureTypes;
	m_dim6=ffi.m_wTotalDimensions;
	m_per1=ffi.m_wWeights[0];
	m_per2=ffi.m_wWeights[1];
	m_per3=ffi.m_wWeights[2];
	m_per4=ffi.m_wWeights[3];
	m_per5=ffi.m_wWeights[4];
	m_per6=ffi.m_wWeights[5];
	m_per7=ffi.m_wWeights[6];
	m_per8=ffi.m_wWeights[7];

	GetDlgItem(IDC_COMBO_COLORSPACE)->EnableWindow(m_checkcolor);
	GetDlgItem(IDC_COMBO_COLORHISTOGRAM)->EnableWindow(m_checkcolor);
	GetDlgItem(IDC_COMBO_BINS)->EnableWindow(m_checkcolor);
	GetDlgItem(IDC_EDIT_PER1)->EnableWindow(m_checkcolor);

	GetDlgItem(IDC_COMBO_COLORSPACE2)->EnableWindow(m_checkinva);
	GetDlgItem(IDC_COMBO_HOWTODESCRIBE)->EnableWindow(m_checkinva);
	GetDlgItem(IDC_COMBO_POINTNUM)->EnableWindow(m_checkinva);
	GetDlgItem(IDC_COMBO_ANGLE)->EnableWindow(m_checkinva);
	GetDlgItem(IDC_COMBO_BINS2)->EnableWindow(m_checkinva);
	GetDlgItem(IDC_EDIT_PER2)->EnableWindow(m_checkinva);
	
	GetDlgItem(IDC_COMBO_COLORSPACE3)->EnableWindow(m_checktexture);
	GetDlgItem(IDC_COMBO_DESCRIPTION)->EnableWindow(m_checktexture);
	GetDlgItem(IDC_COMBO_COOCURRENCE)->EnableWindow(m_checktexture);
	GetDlgItem(IDC_EDIT_PER3)->EnableWindow(m_checktexture);
	
	GetDlgItem(IDC_COMBO_COLORSPACE4)->EnableWindow(m_checkshape);
	GetDlgItem(IDC_COMBO_DESCRIPTION2)->EnableWindow(m_checkshape);
	GetDlgItem(IDC_EDIT_PER4)->EnableWindow(m_checkshape); 	

	GetDlgItem(IDC_CHECK_FEATURE1)->EnableWindow(m_checkother);
	GetDlgItem(IDC_EDIT_FEATURE1)->EnableWindow(m_checkother&m_checkfeature1);
	GetDlgItem(IDC_EDIT_PER5)->EnableWindow(m_checkother&m_checkfeature1);
	
	GetDlgItem(IDC_CHECK_FEATURE2)->EnableWindow(m_checkother);
	GetDlgItem(IDC_EDIT_FEATURE2)->EnableWindow(m_checkother&m_checkfeature2);
	GetDlgItem(IDC_EDIT_PER6)->EnableWindow(m_checkother&m_checkfeature2);
	
	GetDlgItem(IDC_CHECK_FEATURE3)->EnableWindow(m_checkother);
	GetDlgItem(IDC_EDIT_FEATURE3)->EnableWindow(m_checkother&m_checkfeature3);
	GetDlgItem(IDC_EDIT_PER7)->EnableWindow(m_checkother&m_checkfeature3);
	
	GetDlgItem(IDC_CHECK_FEATURE4)->EnableWindow(m_checkother);
	GetDlgItem(IDC_EDIT_FEATURE4)->EnableWindow(m_checkother&m_checkfeature4);
	GetDlgItem(IDC_EDIT_PER8)->EnableWindow(m_checkother&m_checkfeature4);
	
	if(readonly==TRUE)
	{
	  GetDlgItem(IDC_CHECK_COLOR)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_COLORSPACE)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_COLORHISTOGRAM)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_BINS)->EnableWindow(FALSE);
	  
	  GetDlgItem(IDC_CHECK_INVARIANT)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_COLORSPACE2)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_HOWTODESCRIBE)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_POINTNUM)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_ANGLE)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_BINS2)->EnableWindow(FALSE);
	  
	  GetDlgItem(IDC_CHECK_TEXTURE)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_COLORSPACE3)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_DESCRIPTION)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_COOCURRENCE)->EnableWindow(FALSE);
	  
	  GetDlgItem(IDC_CHECK_SHAPE)->EnableWindow(FALSE);
      GetDlgItem(IDC_COMBO_COLORSPACE4)->EnableWindow(FALSE);
	  GetDlgItem(IDC_COMBO_DESCRIPTION2)->EnableWindow(FALSE);
	  
	  GetDlgItem(IDC_CHECK_OTHER)->EnableWindow(FALSE);
 	  GetDlgItem(IDC_CHECK_FEATURE1)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_FEATURE1)->EnableWindow(FALSE);
	  GetDlgItem(IDC_CHECK_FEATURE2)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_FEATURE2)->EnableWindow(FALSE);
	  GetDlgItem(IDC_CHECK_FEATURE3)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_FEATURE3)->EnableWindow(FALSE);
	  GetDlgItem(IDC_CHECK_FEATURE4)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_FEATURE4)->EnableWindow(FALSE);
	  
	  GetDlgItem(IDC_EDIT_PER1)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER2)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER3)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER4)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER5)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER6)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER7)->EnableWindow(FALSE);
	  GetDlgItem(IDC_EDIT_PER8)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}
void CDialogFeatureSelection::View2Data()
{
    UpdateData(TRUE);
	ffi.m_bWithColor=m_checkcolor;
	ffi.m_bWithRTInvariant=m_checkinva;
	ffi.m_bWithOthers=m_checkother;
	ffi.m_bWithShape=m_checkshape;
	ffi.m_bWithTexture=m_checktexture;
	
	ffi.m_bBins_CF=m_bins;
	ffi.m_bDescription_CF=m_colorhist;
	ffi.m_bColorSpace_CF=m_colorspace;
	
	ffi.m_bBins_IF=m_bins2;
	ffi.m_bColorSpace_IF=m_colorspace2;
	ffi.m_bDescription_IF=m_howtodescribe;
	ffi.m_bPoints_IF=m_pointnum;
	ffi.m_bAngles_IF=m_angle;
	
	ffi.m_bColorSpace_TF=m_colorspace3;
	ffi.m_bCoocurrence_TF=m_coocurr;
	ffi.m_bDescription_TF=m_description;
	
	ffi.m_bColorSpace_SF=m_colorspace4;
	ffi.m_bDescription_SF=m_description2;
	
	ffi.m_bWithFeature1_OF=m_checkfeature1;
	ffi.m_bWithFeature2_OF=m_checkfeature2;
	ffi.m_bWithFeature3_OF=m_checkfeature3;
	ffi.m_bWithFeature4_OF=m_checkfeature4;
	
	CheckDimensionandWeights();
}
void CDialogFeatureSelection::CheckDimensionandWeights()
{
    BYTE oldtypes;
	oldtypes=ffi.m_bFeatureTypes;
	if(ffi.m_bWithOthers==FALSE)
	{
	  ffi.m_bWithFeature1_OF=FALSE;
	  ffi.m_bWithFeature2_OF=FALSE;
	  ffi.m_bWithFeature3_OF=FALSE;
	  ffi.m_bWithFeature4_OF=FALSE;
	}
	if(ffi.m_bWithColor==FALSE)
	   ffi.m_wDimension_CF=0;
	else
	{
	  if(ffi.m_bColorSpace_CF<6||ffi.m_bColorSpace_CF>12)
	    ffi.m_wDimension_CF=3*Bins[ffi.m_bBins_CF];
	  else
		ffi.m_wDimension_CF=Bins[ffi.m_bBins_CF];
	}
	
	if(ffi.m_bWithRTInvariant==FALSE)
		ffi.m_wDimension_IF=0;
	else
	{
	  if(ffi.m_bDescription_IF==0)
	  {
	     if(ffi.m_bColorSpace_IF<6||ffi.m_bColorSpace_IF>12)
	       ffi.m_wDimension_IF=3;
	     else
	       ffi.m_wDimension_IF=1;
	  }
	  else
	  {
	     if(ffi.m_bColorSpace_IF<6||ffi.m_bColorSpace_IF>12)
	       ffi.m_wDimension_IF=3*Bins[ffi.m_bBins_IF];
	     else
	      ffi.m_wDimension_IF=Bins[ffi.m_bBins_IF];
	  }
	}
	if(ffi.m_bWithTexture==FALSE)
	  ffi.m_wDimension_TF=0;
	else
	{
	  if(ffi.m_bColorSpace_TF<6||ffi.m_bColorSpace_TF>12)
	   ffi.m_wDimension_TF=3*TextureDim[ffi.m_bDescription_TF];
	  else
	   ffi.m_wDimension_TF=TextureDim[ffi.m_bDescription_TF];
	}
	if(ffi.m_bWithShape==FALSE)
	  ffi.m_wDimension_SF=0;
	else
	{
	  if(ffi.m_bColorSpace_SF<6||ffi.m_bColorSpace_SF>12)
	  ffi.m_wDimension_SF=3*ShapeDim[ffi.m_bDescription_SF];
	  else
	  ffi.m_wDimension_SF=ShapeDim[ffi.m_bDescription_SF];
	}

	if(ffi.m_bWithOthers==FALSE)
	  ffi.m_wDimension_OF=0;
	else
	{
	  ffi.m_wDimension_OF=0;
	  if(ffi.m_bWithFeature1_OF==TRUE)
		  ffi.m_wDimension_OF+=OtherDim[0];
	  if(ffi.m_bWithFeature2_OF==TRUE)
		  ffi.m_wDimension_OF+=OtherDim[1];
	  if(ffi.m_bWithFeature3_OF==TRUE)
		  ffi.m_wDimension_OF+=OtherDim[2];
	  if(ffi.m_bWithFeature4_OF==TRUE)
		  ffi.m_wDimension_OF+=OtherDim[3];
	}

	ffi.m_bFeatureTypes=0;
	if(ffi.m_bWithColor==TRUE&&ffi.m_wDimension_CF!=0)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithRTInvariant==TRUE&&ffi.m_wDimension_IF!=0)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithTexture==TRUE&&ffi.m_wDimension_TF!=0)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithShape==TRUE&&ffi.m_wDimension_SF!=0)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithFeature1_OF==TRUE)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithFeature2_OF==TRUE)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithFeature3_OF==TRUE)
	  ffi.m_bFeatureTypes+=1;
	if(ffi.m_bWithFeature4_OF==TRUE)
	  ffi.m_bFeatureTypes+=1;
	
	if(ffi.m_bFeatureTypes==0)
	{
	  MessageBox("Erorr! Zero Dimension,This system set color features as default!");
	  ffi.m_bWithColor=TRUE;
	  if(ffi.m_bWithColor==TRUE)
	  {
	     if(ffi.m_bColorSpace_CF<6||ffi.m_bColorSpace_CF>12)
		  ffi.m_wDimension_CF=3*Bins[ffi.m_bBins_CF];
		 else
		  ffi.m_wDimension_CF=Bins[ffi.m_bBins_CF];
	  }
      ffi.m_bFeatureTypes+=1;
	}

	ffi.m_wTotalDimensions=ffi.m_wDimension_CF+ffi.m_wDimension_IF+ffi.m_wDimension_TF+ffi.m_wDimension_SF+ffi.m_wDimension_OF;
    if(m_feature1.GetLength()>31)
    {
	  strcpy(ffi.m_sFeature1_OF,m_feature1.Left(31));
	  ffi.m_sFeature1_OF[31]='\0';
	}
	else
      strcpy(ffi.m_sFeature1_OF,m_feature1);
	if(m_feature2.GetLength()>31)
	{
	  strcpy(ffi.m_sFeature2_OF,m_feature2.Left(31));
	  ffi.m_sFeature2_OF[31]='\0';
	}
	else
      strcpy(ffi.m_sFeature2_OF,m_feature2);
	if(m_feature3.GetLength()>31)
	{
	  strcpy(ffi.m_sFeature3_OF,m_feature3.Left(31));
	  ffi.m_sFeature3_OF[31]='\0';
	}
	else
      strcpy(ffi.m_sFeature3_OF,m_feature3);
	if(m_feature4.GetLength()>31)
	{
	  strcpy(ffi.m_sFeature4_OF,m_feature4.Left(31));
	  ffi.m_sFeature4_OF[31]='\0';
	}
	else
      strcpy(ffi.m_sFeature4_OF,m_feature4);
	if(ffi.m_bWithFeature1_OF==FALSE)
	  strcpy(ffi.m_sFeature1_OF,"DCT-VQ Based Features");
	if(ffi.m_bWithFeature2_OF==FALSE)
      strcpy(ffi.m_sFeature2_OF,"VQ Based Features");
	if(ffi.m_bWithFeature3_OF==FALSE)
      strcpy(ffi.m_sFeature3_OF,"MSVQ Based Features");
	if(ffi.m_bWithFeature4_OF==FALSE)
      strcpy(ffi.m_sFeature4_OF,"MRVQ Based Features");
	
	int a=0;
	int i,l;
    int tempweights[8];
    BOOL checks[8];
	tempweights[0]=m_per1;
	tempweights[1]=m_per2;
	tempweights[2]=m_per3;
	tempweights[3]=m_per4;
	tempweights[4]=m_per5;
	tempweights[5]=m_per6;
	tempweights[6]=m_per7;
	tempweights[7]=m_per8;
	checks[0]=ffi.m_bWithColor;
	checks[1]=ffi.m_bWithRTInvariant;
	checks[2]=ffi.m_bWithTexture;
	checks[3]=ffi.m_bWithShape;
	checks[4]=ffi.m_bWithFeature1_OF;
	checks[5]=ffi.m_bWithFeature2_OF;
	checks[6]=ffi.m_bWithFeature3_OF;
	checks[7]=ffi.m_bWithFeature4_OF;
   
    for(i=0;i<8;i++)
	{
	  if(tempweights[i]<0)tempweights[i]=0;
      if(tempweights[i]>100)tempweights[i]=100;
	  if(checks[i]==FALSE)tempweights[i]=0;
	  a=a+tempweights[i];
	}
	if(oldtypes!=ffi.m_bFeatureTypes)
	{
	  for(i=0;i<8;i++)
	  {
		if(checks[i]==TRUE)tempweights[i]=100/ffi.m_bFeatureTypes;
	  }
	}
	else
    {
      for(i=0;i<8;i++)
	  {
	    ffi.m_wWeights[i]=0;
	    if(checks[i]==TRUE)tempweights[i]+=(100-a)/ffi.m_bFeatureTypes;
	  }
	}
	a=0;
	l=0;
	for(i=0;i<8;i++)
	{
	  if(tempweights[i]!=0)l=i;
	  a=a+tempweights[i];
	}
    tempweights[l]+=100-a;
	for(i=0;i<8;i++)
	  ffi.m_wWeights[i]=tempweights[i];
}

void CDialogFeatureSelection::OnSelchangeComboBins() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboBins2() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboColorhistogram() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboColorspace() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboColorspace2() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboColorspace3() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboCoocurrence() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboDescription() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboDescription2() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboHowtodescribe() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboPointnum() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnChangeEditFeature1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnChangeEditFeature2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnChangeEditFeature3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnChangeEditFeature4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnOK() 
{
	// TODO: Add extra validation here
	if(readonly==FALSE)
	{
	  View2Data();
	  Data2View();
	  if(ffi.m_wTotalDimensions>MAX_FEATUREVECTOR_DIMENSION)
	  {
	    MessageBox("The total dimension is larger than 500, please reselect again!","Info",MB_OK|MB_ICONINFORMATION);
		return;
	  }
	}
	CDialog::OnOK();
}

void CDialogFeatureSelection::OnCheckColor() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckFeature1() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckFeature2() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckFeature3() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckFeature4() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckInvariant() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckOther() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckShape() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnCheckTexture() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnSelchangeComboAngle() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();	
}

void CDialogFeatureSelection::OnSelchangeComboColorspace4() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer1() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer2() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer3() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer4() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer5() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer6() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer7() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}

void CDialogFeatureSelection::OnKillfocusEditPer8() 
{
	// TODO: Add your control notification handler code here
	View2Data();
	Data2View();
}
