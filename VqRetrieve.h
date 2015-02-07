// VqRetrieve.h : main header file for the VQRETRIEVE application
//

#if !defined(AFX_VQRETRIEVE_H__9F0E6264_F4A0_42EC_9493_73765D556C5B__INCLUDED_)
#define AFX_VQRETRIEVE_H__9F0E6264_F4A0_42EC_9493_73765D556C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveApp:
// See VqRetrieve.cpp for the implementation of this class
//

class CVqRetrieveApp : public CWinApp
{
public:
	CVqRetrieveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVqRetrieveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVqRetrieveApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VQRETRIEVE_H__9F0E6264_F4A0_42EC_9493_73765D556C5B__INCLUDED_)
