// SBIRSystem.h : main header file for the SBIRSYSTEM application
//

#if !defined(AFX_SBIRSYSTEM_H__E564C5D3_D0D7_40F3_9B06_B8FCE210154B__INCLUDED_)
#define AFX_SBIRSYSTEM_H__E564C5D3_D0D7_40F3_9B06_B8FCE210154B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemApp:
// See SBIRSystem.cpp for the implementation of this class
//

class CSBIRSystemApp : public CWinApp
{
public:
	CSBIRSystemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSBIRSystemApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSBIRSystemApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SBIRSYSTEM_H__E564C5D3_D0D7_40F3_9B06_B8FCE210154B__INCLUDED_)
