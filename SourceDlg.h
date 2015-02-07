#if !defined(AFX_SOURCEDLG_H__220F316E_B881_11D4_848A_D46AC307C673__INCLUDED_)
#define AFX_SOURCEDLG_H__220F316E_B881_11D4_848A_D46AC307C673__INCLUDED_
#include "jpeg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSourceDlg dialog

class CSourceDlg : public CDialog
{
// Construction
public:
	int CheckSettings(int f);
	CSourceDlg(CWnd* pParent = NULL,int number=1,char *file[16]=NULL,CString m_sDatabasePath="");   // standard constructor
    char m_FileNames[16][_MAX_PATH];
    int JudgeImageFile(char m_sFileName[MAX_PATH]);
	CString m_sPath;
	// Dialog Data
	//{{AFX_DATA(CSourceDlg)
	enum { IDD = IDD_DIALOG_SOURCE };
	int		m_Number;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSourceDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddFile();
	afx_msg void OnSelchangeListFile();
	afx_msg void OnDeleteFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOURCEDLG_H__220F316E_B881_11D4_848A_D46AC307C673__INCLUDED_)
