#if !defined(AFX_DIALOGLOADIMAGE_H__99522CC8_CD01_4859_8A29_24FFB5F615A0__INCLUDED_)
#define AFX_DIALOGLOADIMAGE_H__99522CC8_CD01_4859_8A29_24FFB5F615A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogLoadImage.h : header file
//
#include "Classes\PictCtrl.h"
#include "Classes/Matrix.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogLoadImage dialog

class CDialogLoadImage : public CDialog
{
// Construction
public:
	CString GetFilePathName();
	int m_iTotalImageNumber;
//	int m_iCurentNumber;
	CString m_sImagePath;
//	CMatrix *pMatrx;


	CDialogLoadImage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogLoadImage)
	enum { IDD = IDD_DIALOG_LOADSAMPLE };
	CPictureCtrl	m_cControlLoadImage;
	BOOL	m_bRandomChecked;
	int		m_iCurentNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogLoadImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogLoadImage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDisplayCuuretn();
	afx_msg void OnButtonNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGLOADIMAGE_H__99522CC8_CD01_4859_8A29_24FFB5F615A0__INCLUDED_)
