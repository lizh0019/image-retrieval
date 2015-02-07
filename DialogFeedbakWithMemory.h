#if !defined(AFX_DIALOGFEEDBAKWITHMEMORY_H__CB74850A_79A9_417F_AC02_407CD6C73FC1__INCLUDED_)
#define AFX_DIALOGFEEDBAKWITHMEMORY_H__CB74850A_79A9_417F_AC02_407CD6C73FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFeedbakWithMemory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFeedbakWithMemory dialog

class CDialogFeedbakWithMemory : public CDialog
{
// Construction
public:
	CDialogFeedbakWithMemory(CWnd* pParent = NULL);   // standard constructor
    void ComputeMemoryWeights(float *weights);
// Dialog Data
	//{{AFX_DATA(CDialogFeedbakWithMemory)
	enum { IDD = IDD_DIALOG_FEEDBACKWITHMEMORY };
	int		m_T1;
	int		m_T2;
	CString	m_weights;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFeedbakWithMemory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogFeedbakWithMemory)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnKillfocusEditT1();
	afx_msg void OnKillfocusEditT2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFEEDBAKWITHMEMORY_H__CB74850A_79A9_417F_AC02_407CD6C73FC1__INCLUDED_)
