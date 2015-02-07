#if !defined(AFX_DIALOGIMAGEINFORMATION_H__EC4827F7_3ACA_48BE_86BE_34F1FC8E1E05__INCLUDED_)
#define AFX_DIALOGIMAGEINFORMATION_H__EC4827F7_3ACA_48BE_86BE_34F1FC8E1E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogImageInformation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogImageInformation dialog

class CDialogImageInformation : public CDialog
{
// Construction
public:
	CDialogImageInformation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogImageInformation)
	enum { IDD = IDD_INFORMATION };
	CString	m_sBitCount;
	CString	m_sHeight;
	CString	m_sPathName;
	CString	m_sWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogImageInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogImageInformation)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGIMAGEINFORMATION_H__EC4827F7_3ACA_48BE_86BE_34F1FC8E1E05__INCLUDED_)
