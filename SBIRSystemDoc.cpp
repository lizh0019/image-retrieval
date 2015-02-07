// SBIRSystemDoc.cpp : implementation of the CSBIRSystemDoc class
//

#include "stdafx.h"
#include "SBIRSystem.h"

#include "SBIRSystemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemDoc

IMPLEMENT_DYNCREATE(CSBIRSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CSBIRSystemDoc, CDocument)
	//{{AFX_MSG_MAP(CSBIRSystemDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemDoc construction/destruction

CSBIRSystemDoc::CSBIRSystemDoc()
{
	// TODO: add one-time construction code here

}

CSBIRSystemDoc::~CSBIRSystemDoc()
{
}

BOOL CSBIRSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemDoc serialization

void CSBIRSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemDoc diagnostics

#ifdef _DEBUG
void CSBIRSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSBIRSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSBIRSystemDoc commands



