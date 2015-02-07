#if !defined(AFX_IMAGESHOW_H__14800EEB_30B8_4D82_AC75_272DDF91EEB2__INCLUDED_)
#define AFX_IMAGESHOW_H__14800EEB_30B8_4D82_AC75_272DDF91EEB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageShow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageShow dialog

class CImageShow : public CDialog
{
// Construction
public:
	CImageShow(CWnd* pParent = NULL);   // standard constructor
    int width;
	int height;
	int showcom;
	unsigned char *m_DisplayImageBytes[2];
	char *file;
	int SuitableWidth(int Width, int Heigth, int DisplayWidth, int DisplayHeigth);
///Return the suitable dispaly height
    int SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth);

// Dialog Data
	//{{AFX_DATA(CImageShow)
	enum { IDD = IDD_DIALOG_SHOW };
	CString	m_comp;
	float	m_psnr;
	int		m_width;
	int		m_height;
	CString	m_path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageShow)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESHOW_H__14800EEB_30B8_4D82_AC75_272DDF91EEB2__INCLUDED_)
