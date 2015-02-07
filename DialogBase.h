#if !defined(AFX_DIALOGBASE_H__3E20E36B_5A7D_41FD_95F1_C898F44EEF75__INCLUDED_)
#define AFX_DIALOGBASE_H__3E20E36B_5A7D_41FD_95F1_C898F44EEF75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogBase dialog

class CDialogBase : public CDialog
{
// Construction
public:
	CDialogBase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogBase)
	enum { IDD = IDD_IMAGEBASE };
	CString	m_sPathName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	bool GetImageBaseFolder();
	int imagebasechoose;  //1,2, 0
	CString sLoadImageBaseFile;

protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogBase)
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonCreat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBASE_H__3E20E36B_5A7D_41FD_95F1_C898F44EEF75__INCLUDED_)
