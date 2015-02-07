#if !defined(AFX_DIALOGDISPLAYIMAGE_H__F00E2052_5247_4615_BFD1_B79E43C15942__INCLUDED_)
#define AFX_DIALOGDISPLAYIMAGE_H__F00E2052_5247_4615_BFD1_B79E43C15942__INCLUDED_

#include "CRetrieveMethod.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define BINNUM 64
#include "DialogDrawCurve.h"
// DialogDisplayImage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogDisplayImage dialog

class CDialogDisplayImage : public CDialog
{
// Construction
public:
	void MyOnCancel();
    CURVEDATAINFO cdi;
	int sizex,sizey;
	int QueryorRetrieval;
	HBITMAP Image;
	FEATUREVECTOR m_cFeatureVector;
	char m_CurrentDirectory[_MAX_PATH];
	char m_StandardBmpInfoc[54];
	char m_StandardBmpInfo[1078];
	BYTE *rgbimage;
	void initialize();
	int DisplayJpegFile(char m_sFileName[MAX_PATH]);
	CDialogDisplayImage(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDialogDisplayImage)
	enum { IDD = IDD_DISPLAYIMAGE };
	CStatic	m_cBigDisplayImage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDisplayImage)
	public:
	virtual int DoModal();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogDisplayImage)
	afx_msg void OnPaint();
	afx_msg void OnSavechooseimage();
	afx_msg void OnButtonleft();
	afx_msg void OnButtonritht();
	afx_msg void OnButtonup();
	afx_msg void OnButtondown();
	afx_msg void OnMyMove();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnImageinformation();
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnDestroy();
	afx_msg void OnImageHhist();
	afx_msg void OnImageGhist();
	afx_msg void OnImageBhist();
	afx_msg void OnImageRhist();
	afx_msg void OnImageShist();
	afx_msg void OnImageVhist();
	afx_msg void OnImageYhist();
	afx_msg void OnImageCbHIST();
	afx_msg void OnImageCrHIST();
	afx_msg void OnImageY1hist();
	afx_msg void OnImageIhist();
	afx_msg void OnImageQhist();
	afx_msg void OnImageH1hist();
	afx_msg void OnImageChist();
	afx_msg void OnImageV1hist();
	afx_msg void OnImageLhist();
	afx_msg void OnImageAhist();
	afx_msg void OnImageB1hist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_bCanMove;
	double *image_double;
	BYTE *image_byte;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDISPLAYIMAGE_H__F00E2052_5247_4615_BFD1_B79E43C15942__INCLUDED_)
