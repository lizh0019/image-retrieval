#if !defined(AFX_DIALOGFEATURESELECTION_H__90047EEA_2EC8_4F9B_9225_55FC6681AE03__INCLUDED_)
#define AFX_DIALOGFEATURESELECTION_H__90047EEA_2EC8_4F9B_9225_55FC6681AE03__INCLUDED_
#include "CRetrieveMethod.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFeatureSelection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFeatureSelection dialog

class CDialogFeatureSelection : public CDialog
{
// Construction
public:
	CDialogFeatureSelection(CWnd* pParent = NULL);   // standard constructor
    FEATUREFILEINFO ffi;
	BOOL readonly;
// Dialog Data
	//{{AFX_DATA(CDialogFeatureSelection)
	enum { IDD = IDD_DIALOG_FEATURESELECTION };
	BOOL	m_checkcolor;
	BOOL	m_checkhist;
	BOOL	m_checkinva;
	BOOL	m_checkother;
	BOOL	m_checkshape;
	BOOL	m_checktexture;
	int		m_bins;
	int		m_bins2;
	int		m_colorhist;
	int		m_colorspace;
	int		m_colorspace2;
	int		m_colorspace3;
	int		m_coocurr;
	int		m_description;
	int		m_description2;
	int		m_howtodescribe;
	int		m_pointnum;
	int		m_dim;
	int		m_dim2;
	int		m_dim3;
	int		m_dim4;
	int		m_dim5;
	CString	m_feature1;
	CString	m_feature2;
	CString	m_feature3;
	CString	m_feature4;
	int		m_kinds;
	BOOL	m_checkfeature1;
	BOOL	m_checkfeature2;
	BOOL	m_checkfeature3;
	BOOL	m_checkfeature4;
	int		m_angle;
	int		m_dim6;
	int		m_colorspace4;
	int		m_per1;
	int		m_per2;
	int		m_per3;
	int		m_per4;
	int		m_per5;
	int		m_per6;
	int		m_per7;
	int		m_per8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFeatureSelection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void Data2View();
	void View2Data();
	void CheckDimensionandWeights();
	// Generated message map functions
	//{{AFX_MSG(CDialogFeatureSelection)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboBins();
	afx_msg void OnSelchangeComboBins2();
	afx_msg void OnSelchangeComboColorhistogram();
	afx_msg void OnSelchangeComboColorspace();
	afx_msg void OnSelchangeComboColorspace2();
	afx_msg void OnSelchangeComboColorspace3();
	afx_msg void OnSelchangeComboCoocurrence();
	afx_msg void OnSelchangeComboDescription();
	afx_msg void OnSelchangeComboDescription2();
	afx_msg void OnSelchangeComboHowtodescribe();
	afx_msg void OnSelchangeComboPointnum();
	afx_msg void OnChangeEditFeature1();
	afx_msg void OnChangeEditFeature2();
	afx_msg void OnChangeEditFeature3();
	afx_msg void OnChangeEditFeature4();
	virtual void OnOK();
	afx_msg void OnCheckColor();
	afx_msg void OnCheckFeature1();
	afx_msg void OnCheckFeature2();
	afx_msg void OnCheckFeature3();
	afx_msg void OnCheckFeature4();
	afx_msg void OnCheckInvariant();
	afx_msg void OnCheckOther();
	afx_msg void OnCheckShape();
	afx_msg void OnCheckTexture();
	afx_msg void OnSelchangeComboAngle();
	afx_msg void OnSelchangeComboColorspace4();
	afx_msg void OnKillfocusEditPer1();
	afx_msg void OnKillfocusEditPer2();
	afx_msg void OnKillfocusEditPer3();
	afx_msg void OnKillfocusEditPer4();
	afx_msg void OnKillfocusEditPer5();
	afx_msg void OnKillfocusEditPer6();
	afx_msg void OnKillfocusEditPer7();
	afx_msg void OnKillfocusEditPer8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFEATURESELECTION_H__90047EEA_2EC8_4F9B_9225_55FC6681AE03__INCLUDED_)
