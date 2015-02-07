#if !defined(AFX_DIALOGDRAWCURVE_H__DA93E248_EC8F_4E2D_905B_7498D96DBF3A__INCLUDED_)
#define AFX_DIALOGDRAWCURVE_H__DA93E248_EC8F_4E2D_905B_7498D96DBF3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogDrawCurve.h : header file
//
#include "DrawCurve.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogDrawCurve dialog

class CDialogDrawCurve : public CDialog
{
// Construction
public:
	CDialogDrawCurve(CWnd* pParent = NULL);   // standard constructor
    LONG m_lNumberofSamples;
	BYTE m_bSampleDimensions;   
    double *m_dDataX;
	double *m_dDataY;
    CURVEDATAINFO cdf;
	CDrawCurve c;
	bool confirm;
	int showhide;
// Dialog Data
	//{{AFX_DATA(CDialogDrawCurve)
	enum { IDD = IDD_DIALOG_DRAWCURVE };
	BOOL	m_border;
	BOOL	m_figtitle;
	BOOL	m_showdigits;
	BOOL	m_showticks;
	BOOL	m_xtitle;
	BOOL	m_ytitle;
	CString	m_dlgtitle;
	CString	m_sfigtitle;
	double	m_xmax;
	double	m_xmin;
	CString	m_sxtitle;
	double	m_ymax;
	double	m_ymin;
	CString	m_sytitle;
	int		m_xticks;
	int		m_axescolor;
	int		m_backcolor;
	int		m_figtitlecolor;
	int		m_gridcolor;
	int		m_linecolor;
	int		m_scalevcolor;
	int		m_textcolor;
	int		m_tickcolor;
	int		m_xtitlecolor;
	int		m_yticks;
	int		m_ytitlecolor;
	int		m_xminmaxstyle;
	int		m_yminmaxstyle;
	int		m_linestyle;
	int		m_gridstyle;
	int		m_scalevstyle;
	int		m_axesstyle;
	int		m_xaxisstyle;
	int		m_yaxisstyle;
	//}}AFX_DATA

private:
	void Data2View();
	void MoveWindowtoPosition();
	void MakeWindowVisible(int nCmdShow);
	void View2Data();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDrawCurve)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 
	// Generated message map functions
	//{{AFX_MSG(CDialogDrawCurve)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonCheck();
	afx_msg void OnChangeEditXmax();
	afx_msg void OnChangeEditXmin();
	afx_msg void OnChangeEditXtitle();
	afx_msg void OnChangeEditYmax();
	afx_msg void OnChangeEditYmin();
	afx_msg void OnChangeEditYtitle();
	afx_msg void OnRadioAxesnone();
	afx_msg void OnRadioCompute();
	afx_msg void OnRadioCompute3();
	afx_msg void OnRadioConnect();
	afx_msg void OnRadioConnect2();
	afx_msg void OnRadioDasharrow();
	afx_msg void OnRadioDashnoarrow();
	afx_msg void OnRadioDefault();
	afx_msg void OnRadioGriddash();
	afx_msg void OnRadioGridline();
	afx_msg void OnRadioGridlinenone();
	afx_msg void OnRadioHistogram();
	afx_msg void OnRadioHistogram2();
	afx_msg void OnRadioLinearrow();
	afx_msg void OnRadioLinenoarrow();
	afx_msg void OnRadioPoint();
	afx_msg void OnRadioPoint2();
	afx_msg void OnRadioSingleline();
	afx_msg void OnRadioSingleline2();
	afx_msg void OnRadioUser();
	afx_msg void OnRadioUser3();
	afx_msg void OnRadioXaismiddle();
	afx_msg void OnRadioXaistop();
	afx_msg void OnRadioXaxisbottom();
	afx_msg void OnRadioYaismiddle();
	afx_msg void OnRadioYaisright();
	afx_msg void OnRadioYaxisleft();
	afx_msg void OnSelchangeComboAxescolor();
	afx_msg void OnSelchangeComboBackcolor();
	afx_msg void OnSelchangeComboFigtitlecolor();
	afx_msg void OnSelchangeComboGridcolor();
	afx_msg void OnSelchangeComboLinecolor();
	afx_msg void OnSelchangeComboScalevcolor();
	afx_msg void OnSelchangeComboTextcolor();
	afx_msg void OnSelchangeComboTickcolor();
	afx_msg void OnSelchangeComboXticks();
	afx_msg void OnSelchangeComboXtitlecolor();
	afx_msg void OnSelchangeComboYticks();
	afx_msg void OnSelchangeComboYtitlecolor();
	afx_msg void OnChangeEditDlgtitle();
	afx_msg void OnChangeEditFigtitle();
	afx_msg void OnCheckBorder();
	afx_msg void OnCheckFigtitle();
	afx_msg void OnCheckShowdigits();
	afx_msg void OnCheckShowticks();
	afx_msg void OnCheckXtitle();
	afx_msg void OnCheckYtitle();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonDisplay();
	afx_msg void OnButtonReturn();
	afx_msg void OnRadioScalevnone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDRAWCURVE_H__DA93E248_EC8F_4E2D_905B_7498D96DBF3A__INCLUDED_)
