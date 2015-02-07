// ANNSBIRDoc.cpp : implementation of the CANNSBIRDoc class
//

#include "stdafx.h"
#include "ANNSBIR.h"

#include "ANNSBIRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRDoc

IMPLEMENT_DYNCREATE(CANNSBIRDoc, CDocument)

BEGIN_MESSAGE_MAP(CANNSBIRDoc, CDocument)
	//{{AFX_MSG_MAP(CANNSBIRDoc)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRDoc construction/destruction

CANNSBIRDoc::CANNSBIRDoc()
{
	// TODO: add one-time construction code here

}

CANNSBIRDoc::~CANNSBIRDoc()
{
}

BOOL CANNSBIRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CANNSBIRDoc serialization

void CANNSBIRDoc::Serialize(CArchive& ar)
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
// CANNSBIRDoc diagnostics

#ifdef _DEBUG
void CANNSBIRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CANNSBIRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CANNSBIRDoc commands

void CANNSBIRDoc::OnFilePrint() 
{
	// TODO: Add your command handler code here
	
}

void CANNSBIRDoc::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
