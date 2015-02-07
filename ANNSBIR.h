// ANNSBIR.h : main header file for the ANNSBIR application
//

#if !defined(AFX_ANNSBIR_H__613F7BB3_4932_4DC2_A112_D8F11DCFB1AF__INCLUDED_)
#define AFX_ANNSBIR_H__613F7BB3_4932_4DC2_A112_D8F11DCFB1AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRApp:
// See ANNSBIR.cpp for the implementation of this class
//

class CANNSBIRApp : public CWinApp
{
public:
	CANNSBIRApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANNSBIRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CANNSBIRApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANNSBIR_H__613F7BB3_4932_4DC2_A112_D8F11DCFB1AF__INCLUDED_)
