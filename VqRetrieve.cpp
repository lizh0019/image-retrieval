// VqRetrieve.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VqRetrieve.h"

#include "MainFrm.h"
#include "VqRetrieveDoc.h"
#include "VqRetrieveView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//++++++++++++++++++++++++++++++++++++++Inserted code begin
//All types of image files to be opened/*.* is considered as the raw file
char szFilter[]= "BMP图像文件(*.bmp)|*.BMP|RAW图像文件(*.raw)|*.RAW|Jpeg图像文件(*.jpg)|*.JPG|JPG图像文件(*.jpeg)|*.jpeg|GIF图像文件(*.gif)|*.GIF|PCX图像文件(*.pcx)|*.PCX|Tif图像文件(*.tif)|*.TIF|各种图像文件(*.bmp,*.raw,*.jpg,*.gif,*.pcx,*.tif)|*.BMP;*.RAW;*.JPG;*.GIF;*.PCX;*.TIF|所有文件(*.*)|*.*||";
char szFilter1[]= "BMP图像文件(*.bmp)|*.BMP||";
//++++++++++++++++++++++++++++++++++++++Inserted code end
/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveApp

BEGIN_MESSAGE_MAP(CVqRetrieveApp, CWinApp)
	//{{AFX_MSG_MAP(CVqRetrieveApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveApp construction

CVqRetrieveApp::CVqRetrieveApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVqRetrieveApp object

CVqRetrieveApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVqRetrieveApp initialization

BOOL CVqRetrieveApp::InitInstance()
{

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVqRetrieveDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CVqRetrieveView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// 启动时不自动打开一个空文档 
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVqRetrieveApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////

void CVqRetrieveApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	static int nIndex=1;//the file type index 
	//Open file dialog
	CFileDialog DialogOpen(true,NULL,NULL,OFN_HIDEREADONLY,szFilter);
	//Set the file type
	DialogOpen.m_ofn.nFilterIndex=(DWORD)nIndex;

	//Get the filename and return
	if(DialogOpen.DoModal()==IDOK)
	{
	  //Get the filename
	  CString strPathName=DialogOpen.GetPathName();
	  //Open the documnet, need to load the serialize function
	  OpenDocumentFile(strPathName);
	  //save the filetype index
	  nIndex=(int)DialogOpen.m_ofn.nFilterIndex;
	}	
}