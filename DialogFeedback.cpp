// DialogFeedback.cpp : implementation file
//

#include "stdafx.h"
#include "vqretrieve.h"
#include "DialogFeedback.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFeedback dialog


CDialogFeedback::CDialogFeedback(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFeedback::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFeedback)
	m_fedit1 = 0.0f;
	m_fedit10 = 0.0f;
	m_sCurrent = _T("");
	m_fedit11 = 0.0f;
	m_fedit12 = 0.0f;
	m_fedit13 = 0.0f;
	m_fedit14 = 0.0f;
	m_fedit15 = 0.0f;
	m_fedit16 = 0.0f;
	m_fedit2 = 0.0f;
	m_fedit3 = 0.0f;
	m_fedit4 = 0.0f;
	m_fedit5 = 0.0f;
	m_fedit6 = 0.0f;
	m_fedit7 = 0.0f;
	m_fedit8 = 0.0f;
	m_fedit9 = 0.0f;
	m_iChooseOperation = 0;
	//}}AFX_DATA_INIT
}


void CDialogFeedback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFeedback)
	DDX_Control(pDX, IDC_EDIT9, m_control9);
	DDX_Control(pDX, IDC_EDIT8, m_control8);
	DDX_Control(pDX, IDC_EDIT7, m_control7);
	DDX_Control(pDX, IDC_EDIT6, m_control6);
	DDX_Control(pDX, IDC_EDIT5, m_control5);
	DDX_Control(pDX, IDC_EDIT4, m_control4);
	DDX_Control(pDX, IDC_EDIT3, m_control3);
	DDX_Control(pDX, IDC_EDIT2, m_control2);
	DDX_Control(pDX, IDC_EDIT16, m_control16);
	DDX_Control(pDX, IDC_EDIT15, m_control15);
	DDX_Control(pDX, IDC_EDIT14, m_control14);
	DDX_Control(pDX, IDC_EDIT12, m_control12);
	DDX_Control(pDX, IDC_EDIT13, m_control13);
	DDX_Control(pDX, IDC_EDIT11, m_control11);
	DDX_Control(pDX, IDC_EDIT10, m_control10);
	DDX_Control(pDX, IDC_EDIT1, m_control1);
	DDX_Text(pDX, IDC_EDIT1, m_fedit1);
	DDV_MinMaxFloat(pDX, m_fedit1, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT10, m_fedit10);
	DDV_MinMaxFloat(pDX, m_fedit10, 0.f, 100.f);
	DDX_Text(pDX, IDC_BACK0, m_sCurrent);
	DDX_Text(pDX, IDC_EDIT11, m_fedit11);
	DDV_MinMaxFloat(pDX, m_fedit11, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT12, m_fedit12);
	DDV_MinMaxFloat(pDX, m_fedit12, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT13, m_fedit13);
	DDV_MinMaxFloat(pDX, m_fedit13, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT14, m_fedit14);
	DDV_MinMaxFloat(pDX, m_fedit14, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT15, m_fedit15);
	DDV_MinMaxFloat(pDX, m_fedit15, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT16, m_fedit16);
	DDV_MinMaxFloat(pDX, m_fedit16, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT2, m_fedit2);
	DDV_MinMaxFloat(pDX, m_fedit2, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT3, m_fedit3);
	DDV_MinMaxFloat(pDX, m_fedit3, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT4, m_fedit4);
	DDV_MinMaxFloat(pDX, m_fedit4, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT5, m_fedit5);
	DDV_MinMaxFloat(pDX, m_fedit5, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT6, m_fedit6);
	DDV_MinMaxFloat(pDX, m_fedit6, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT7, m_fedit7);
	DDV_MinMaxFloat(pDX, m_fedit7, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT8, m_fedit8);
	DDV_MinMaxFloat(pDX, m_fedit8, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT9, m_fedit9);
	DDV_MinMaxFloat(pDX, m_fedit9, 0.f, 100.f);
	DDX_Radio(pDX, IDC_RADIO1, m_iChooseOperation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFeedback, CDialog)
	//{{AFX_MSG_MAP(CDialogFeedback)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT2, OnSetfocusEdit2)
	ON_EN_SETFOCUS(IDC_EDIT3, OnSetfocusEdit3)
	ON_EN_SETFOCUS(IDC_EDIT4, OnSetfocusEdit4)
	ON_EN_SETFOCUS(IDC_EDIT5, OnSetfocusEdit5)
	ON_EN_SETFOCUS(IDC_EDIT6, OnSetfocusEdit6)
	ON_EN_SETFOCUS(IDC_EDIT7, OnSetfocusEdit7)
	ON_EN_SETFOCUS(IDC_EDIT8, OnSetfocusEdit8)
	ON_EN_SETFOCUS(IDC_EDIT9, OnSetfocusEdit9)
	ON_EN_SETFOCUS(IDC_EDIT10, OnSetfocusEdit10)
	ON_EN_SETFOCUS(IDC_EDIT11, OnSetfocusEdit11)
	ON_EN_SETFOCUS(IDC_EDIT12, OnSetfocusEdit12)
	ON_EN_SETFOCUS(IDC_EDIT13, OnSetfocusEdit13)
	ON_EN_SETFOCUS(IDC_EDIT14, OnSetfocusEdit14)
	ON_EN_SETFOCUS(IDC_EDIT15, OnSetfocusEdit15)
	ON_EN_SETFOCUS(IDC_EDIT16, OnSetfocusEdit16)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFeedback message handlers
////¿ØÖÆÏÔÊ¾
void CDialogFeedback::OnSetfocusEdit1() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  if (this->m_iCanBeBack<1)
	  {
	 this->m_fedit1=0;
	 this->UpdateData(FALSE);
	 this->m_control1.EnableWindow(FALSE);
	  }

}

void CDialogFeedback::OnSetfocusEdit2() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<2)
	  {
	 this->m_fedit2=0;
	 this->UpdateData(FALSE);
	 this->m_control2.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit3() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<3)
	  {
	 this->m_fedit3=0;
	 this->UpdateData(FALSE);
	 this->m_control3.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit4() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<4)
	  {
	 this->m_fedit4=0;
	 this->UpdateData(FALSE);
	 this->m_control4.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit5() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<5)
	  {
	 this->m_fedit5=0;
	 this->UpdateData(FALSE);
	 this->m_control5.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit6() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<6)
	  {
	 this->m_fedit6=0;
	 this->UpdateData(FALSE);
	 this->m_control6.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit7() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<7)
	  {
	 this->m_fedit7=0;
	 this->UpdateData(FALSE);
	 this->m_control7.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit8() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<8)
	  {
	 this->m_fedit8=0;
	 this->UpdateData(FALSE);
	 this->m_control8.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit9() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<9)
	  {
	 this->m_fedit9=0;
	 this->UpdateData(FALSE);
	 this->m_control9.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit10() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  if (this->m_iCanBeBack<10)
	  {
	 this->m_fedit10=0;
	 this->UpdateData(FALSE);
	 this->m_control10.EnableWindow(FALSE);
	  }

	
}

void CDialogFeedback::OnSetfocusEdit11() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  	  if (this->m_iCanBeBack<11)
	  {
	 this->m_fedit11=0;
	 this->UpdateData(FALSE);
	 this->m_control11.EnableWindow(FALSE);
	  }
	
}

void CDialogFeedback::OnSetfocusEdit12() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  	  if (this->m_iCanBeBack<12)
	  {
	 this->m_fedit12=0;
	 this->UpdateData(FALSE);
	 this->m_control12.EnableWindow(FALSE);
	  }
	
}

void CDialogFeedback::OnSetfocusEdit13() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  	  if (this->m_iCanBeBack<13)
	  {
	 this->m_fedit13=0;
	 this->UpdateData(FALSE);
	 this->m_control13.EnableWindow(FALSE);
	  }
	
}

void CDialogFeedback::OnSetfocusEdit14() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  	  if (this->m_iCanBeBack<14)
	  {
	 this->m_fedit14=0;
	 this->UpdateData(FALSE);
	 this->m_control14.EnableWindow(FALSE);
	  }
	
}

void CDialogFeedback::OnSetfocusEdit15() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  	  	  if (this->m_iCanBeBack<15)
	  {
	 this->m_fedit15=0;
	 this->UpdateData(FALSE);
	 this->m_control15.EnableWindow(FALSE);
	  }
	
}

void CDialogFeedback::OnSetfocusEdit16() 
{
	// TODO: Add your control notification handler code here
//	  OnRadio1();
	  	  	  	  if (this->m_iCanBeBack<16)
	  {
	 this->m_fedit16=0;
	 this->UpdateData(FALSE);
	 this->m_control16.EnableWindow(FALSE);
	  }
	
}



void CDialogFeedback::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit1<0||m_fedit1>100)
	{
	  m_fedit1=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit1;//»Ö¸´
				 m_fedit1=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData(false);
  

	
}

void CDialogFeedback::OnChangeEdit10() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit10<0||m_fedit10>100)
	{
	  m_fedit10=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit10;//»Ö¸´
				 m_fedit10=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	  
	
}

void CDialogFeedback::OnChangeEdit11() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
			if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit11<0||m_fedit11>100)
	{
	  m_fedit11=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit11;//»Ö¸´
				 m_fedit11=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit12() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit12<0||m_fedit12>100)
	{
	  m_fedit12=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit12;//»Ö¸´
				 m_fedit12=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit13() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
		if(this->m_fedit13<0||m_fedit13>100)
	{
	  m_fedit13=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit13;//»Ö¸´
				 m_fedit13=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit14() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit14<0||m_fedit14>100)
	{
	  m_fedit14=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit14;//»Ö¸´
				 m_fedit14=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit15() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit15<0||m_fedit15>100)
	{
	  m_fedit15=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit15;//»Ö¸´
				 m_fedit15=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit16() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit16<0||m_fedit16>100)
	{
	  m_fedit16=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit16;//»Ö¸´
				 m_fedit16=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit2<0||m_fedit2>100)
	{
	  m_fedit2=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit2;//»Ö¸´
				 m_fedit2=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit3<0||m_fedit3>100)
	{
	  m_fedit3=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit3;//»Ö¸´
				 m_fedit3=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit4<0||m_fedit4>100)
	{
	  m_fedit4=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit4;//»Ö¸´
				 m_fedit4=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
	if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit5<0||m_fedit5>100)
	{
	  m_fedit5=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit5;//»Ö¸´
				 m_fedit5=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
	if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit6<0||m_fedit6>100)
	{
	  m_fedit6=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit6;//»Ö¸´
				 m_fedit6=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));

  
	
}

void CDialogFeedback::OnChangeEdit7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit7<0||m_fedit7>100)
	{
	  m_fedit7=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit7;//»Ö¸´
				 m_fedit7=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit8<0||m_fedit8>100)
	{
	  m_fedit8=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit8;//»Ö¸´
				 m_fedit8=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnChangeEdit9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	  	UpdateData(TRUE);
		if(m_bChanged==FALSE)
	{
		  OnRadio1();
		  m_bChanged=TRUE;
	 }
	if(this->m_fedit9<0||m_fedit9>100)
	{
	  m_fedit9=0; 
	  MessageBox("Input a number between 0~100","error",MB_OK);
	}
	m_fCurrent=100-m_fedit1-m_fedit2-m_fedit3-m_fedit4-m_fedit5-m_fedit6-m_fedit7
				  -m_fedit8-m_fedit9-m_fedit10-m_fedit11-m_fedit12-m_fedit13-m_fedit14-m_fedit15
				  -m_fedit16;  ///¼ÆËã
			if (m_fCurrent<0)
			{
				 m_fCurrent=m_fCurrent+m_fedit9;//»Ö¸´
				 m_fedit9=0;
				 MessageBox("the number you input is too large!","error",MB_OK);
			}	
	m_sCurrent.Empty();
	 this->m_sCurrent.Format("%s%f",m_sCurrent,m_fCurrent);
	UpdateData((false));
  
	
}

void CDialogFeedback::OnRadio1() 
{
	// TODO: Add your control notification handler code here

			 this->m_control1.EnableWindow(false);
			this->m_control2.EnableWindow(false);
			this->m_control3.EnableWindow(false);
			this->m_control4.EnableWindow(false);
			this->m_control5.EnableWindow(false);
			this->m_control6.EnableWindow(false);
			this->m_control7.EnableWindow(false);
			this->m_control8.EnableWindow(false);
			this->m_control9.EnableWindow(false);
			this->m_control10.EnableWindow(false);
			this->m_control11.EnableWindow(false);
			this->m_control12.EnableWindow(false);
			this->m_control13.EnableWindow(false);
			this->m_control14.EnableWindow(false);
			this->m_control15.EnableWindow(false);
			this->m_control16.EnableWindow(false);	
			
			    if(this->m_iCanBeBack>=16) this->m_control16.EnableWindow(true);
				 if(this->m_iCanBeBack>=15) this->m_control15.EnableWindow(true);
				 if(this->m_iCanBeBack>=14) this->m_control14.EnableWindow(true);
				 if(this->m_iCanBeBack>=13) this->m_control13.EnableWindow(true);
				 if(this->m_iCanBeBack>=12) this->m_control12.EnableWindow(true);
				 if(this->m_iCanBeBack>=11) this->m_control11.EnableWindow(true);
				 if(this->m_iCanBeBack>=10) this->m_control10.EnableWindow(true);
				 if(this->m_iCanBeBack>=9) this->m_control9.EnableWindow(true);
				 if(this->m_iCanBeBack>=8) this->m_control8.EnableWindow(true);
				 if(this->m_iCanBeBack>=7) this->m_control7.EnableWindow(true);
				 if(this->m_iCanBeBack>=6) this->m_control6.EnableWindow(true);
				 if(this->m_iCanBeBack>=5) this->m_control5.EnableWindow(true);
				 if(this->m_iCanBeBack>=4) this->m_control4.EnableWindow(true);
				 if(this->m_iCanBeBack>=3) this->m_control3.EnableWindow(true);
				 if(this->m_iCanBeBack>=2) this->m_control2.EnableWindow(true);
				 if(this->m_iCanBeBack>=1) this->m_control1.EnableWindow(true);	

}



void CDialogFeedback::OnRadio2() 
{
	// TODO: Add your control notification handler code here
		    this->m_control1.EnableWindow(false);
			this->m_control2.EnableWindow(false);
			this->m_control3.EnableWindow(false);
			this->m_control4.EnableWindow(false);
			this->m_control5.EnableWindow(false);
			this->m_control6.EnableWindow(false);
			this->m_control7.EnableWindow(false);
			this->m_control8.EnableWindow(false);
			this->m_control9.EnableWindow(false);
			this->m_control10.EnableWindow(false);
			this->m_control11.EnableWindow(false);
			this->m_control12.EnableWindow(false);
			this->m_control13.EnableWindow(false);
			this->m_control14.EnableWindow(false);
			this->m_control15.EnableWindow(false);
			this->m_control16.EnableWindow(false);
	
}
