#if !defined(AFX_DIALOGFEEDBACK_H__38E5D951_BC77_4232_83E4_0CBC7A58752B__INCLUDED_)
#define AFX_DIALOGFEEDBACK_H__38E5D951_BC77_4232_83E4_0CBC7A58752B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFeedback.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFeedback dialog

class CDialogFeedback : public CDialog
{
// Construction
public:
	void DisplayControl(int maxdisplay);
	CDialogFeedback(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogFeedback)
	enum { IDD = IDD_DIALOG_FEEDBACK };
	CEdit	m_control9;
	CEdit	m_control8;
	CEdit	m_control7;
	CEdit	m_control6;
	CEdit	m_control5;
	CEdit	m_control4;
	CEdit	m_control3;
	CEdit	m_control2;
	CEdit	m_control16;
	CEdit	m_control15;
	CEdit	m_control14;
	CEdit	m_control12;
	CEdit	m_control13;
	CEdit	m_control11;
	CEdit	m_control10;
	CEdit	m_control1;
	float	m_fedit1;
	float	m_fedit10;
	CString	m_sCurrent;
	float	m_fedit11;
	float	m_fedit12;
	float	m_fedit13;
	float	m_fedit14;
	float	m_fedit15;
	float	m_fedit16;
	float	m_fedit2;
	float	m_fedit3;
	float	m_fedit4;
	float	m_fedit5;
	float	m_fedit6;
	float	m_fedit7;
	float	m_fedit8;
	float	m_fedit9;
	int		m_iChooseOperation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFeedback)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogFeedback)
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnSetfocusEdit2();
	afx_msg void OnSetfocusEdit3();
	afx_msg void OnSetfocusEdit4();
	afx_msg void OnSetfocusEdit5();
	afx_msg void OnSetfocusEdit6();
	afx_msg void OnSetfocusEdit7();
	afx_msg void OnSetfocusEdit8();
	afx_msg void OnSetfocusEdit9();
	afx_msg void OnSetfocusEdit10();
	afx_msg void OnSetfocusEdit11();
	afx_msg void OnSetfocusEdit12();
	afx_msg void OnSetfocusEdit13();
	afx_msg void OnSetfocusEdit14();
	afx_msg void OnSetfocusEdit15();
	afx_msg void OnSetfocusEdit16();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit10();
	afx_msg void OnChangeEdit11();
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit16();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bChanged;
	float m_fCurrent;
	long int m_iCanBeBack;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFEEDBACK_H__38E5D951_BC77_4232_83E4_0CBC7A58752B__INCLUDED_)
