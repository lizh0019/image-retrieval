#if !defined(AFX_IMAGERESULTDIALOG_H__74BD9773_19B6_4C7E_A714_232FF8EAD2BA__INCLUDED_)
#define AFX_IMAGERESULTDIALOG_H__74BD9773_19B6_4C7E_A714_232FF8EAD2BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageResultDialog.h : header file
//
#include "Classes/PictCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CImageResultDialog dialog

class CImageResultDialog : public CDialog
{
// Construction
public:
	BOOL m_bRetrievalChanged;
	CString m_sImageFullPath;
	int m_iImageID;
	CImageResultDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageResultDialog)
	enum { IDD = IDD_DIALOG_DISPLAYRESULT };
	CPictureCtrl	m_cResultImage;
	CString	m_sHeight;
	CString	m_sWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageResultDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageResultDialog)
		virtual BOOL OnInitDialog();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonRetrievalChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGERESULTDIALOG_H__74BD9773_19B6_4C7E_A714_232FF8EAD2BA__INCLUDED_)
