#if !defined(AFX_DIALOGDATABASE_H__CDB61FE2_0009_4603_BF67_81001D22EAA8__INCLUDED_)
#define AFX_DIALOGDATABASE_H__CDB61FE2_0009_4603_BF67_81001D22EAA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogDatabase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogDatabase dialog

class CDialogDatabase : public CDialog
{
// Construction
public:
	CDialogDatabase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogDatabase)
	enum { IDD = IDD_DIALOG_DATABASE };
	CString	m_sPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDatabase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogDatabase)
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDATABASE_H__CDB61FE2_0009_4603_BF67_81001D22EAA8__INCLUDED_)
