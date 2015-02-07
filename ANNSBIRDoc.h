// ANNSBIRDoc.h : interface of the CANNSBIRDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANNSBIRDOC_H__370DBD7C_862B_48FC_B388_B2853F396694__INCLUDED_)
#define AFX_ANNSBIRDOC_H__370DBD7C_862B_48FC_B388_B2853F396694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CANNSBIRDoc : public CDocument
{
protected: // create from serialization only
	CANNSBIRDoc();
	DECLARE_DYNCREATE(CANNSBIRDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANNSBIRDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CANNSBIRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CANNSBIRDoc)
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANNSBIRDOC_H__370DBD7C_862B_48FC_B388_B2853F396694__INCLUDED_)
