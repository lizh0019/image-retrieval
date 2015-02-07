// SourceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vqretrieve.h"
#include "SourceDlg.h"
#include "CRetrieveMethod.h"
///////////////My code begins/////////////

// These six header files are for "_open", "_read" and "_write" functions 
//and string functions
#include <io.h> 
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
///////////////My code ends//////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceDlg dialog

//I have overrided this construct function with three additional
// parameters to input additional parameters
CSourceDlg::CSourceDlg(CWnd* pParent /*=NULL*/,int number /*=1*/,char *file[16] /*=NULL*/,CString m_sDatabasePath /*=NULL*/)
	: CDialog(CSourceDlg::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(CSourceDlg)
///////////////My code begins/////////////
	//initial the dialog parameters
	m_Number=number;
	m_sPath=m_sDatabasePath;
	//}}AFX_DATA_INIT
	int i;
	for(i=0;i<m_Number;i++)
	strcpy(m_FileNames[i],file[i]);
///////////////My code ends/////////////
}


void CSourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSourceDlg)
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_Number);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSourceDlg, CDialog)
	//{{AFX_MSG_MAP(CSourceDlg)
	ON_BN_CLICKED(IDC_ADD_FILE, OnAddFile)
	ON_LBN_SELCHANGE(IDC_LIST_FILE, OnSelchangeListFile)
	ON_BN_CLICKED(IDC_DELETE_FILE, OnDeleteFile)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceDlg message handlers

/////////The Functions added by VC with my code begins///////////////
//The function added by myself to test the settings
int CSourceDlg::CheckSettings(int f)
{
	int i,num;
    int j;
    int value;
	int count;
	int flag;
	char temp[_MAX_PATH+100];
	CListBox *ccb;
	num=m_Number;
	if(num>16)return 1;
 	ccb=(CListBox *)GetDlgItem(IDC_LIST_FILE);
	count=0;
	for(i=0;i<16;i++)
	  strcpy(m_FileNames[i],"");
    for(i=0;i<m_Number;i++)
      ccb->GetText(i,m_FileNames[m_Number-i-1]);
    for(i=0;i<num;i++)
	{
       flag=0;
       value=JudgeImageFile(m_FileNames[i]);
	   switch(value)
	   {
	     case 0:
		   count++;
		   if(count>16)
		   { 
			 flag=1;
			 sprintf(temp,"There are more than 16 images selected!,delete the file[%s]",m_FileNames[i]);
		   } 
		   break;
	     case -1:
	       sprintf(temp,"Because the file [%s] cannot be opened,delete it from the file list",m_FileNames[i]);
		   flag=1;
		   break;
	     case -2:
		   sprintf(temp,"Because the file [%s] cannot be read,delete it from the file list",m_FileNames[i]);
		   flag=1;
           break;
	     case -3:
		   sprintf(temp,"File[%s] is less than 256*256 or larger than 1024*1024,delete it from the list",m_FileNames[i]);
		   flag=1;
		   break;
	     case -4:
  	       sprintf(temp,"Because the file [%s] format error,delete it from the file list",m_FileNames[i]);
		   flag=1;
		   break;
	   }
	   if(flag)
	   {
	     MessageBox(temp,"Training Image Setting",MB_ICONINFORMATION|MB_OK);
		 m_Number--;	 
		 ccb->DeleteString(ccb->FindString(-1,m_FileNames[i]));
	   }
	}
   for(i=0;i<16;i++)
     strcpy(m_FileNames[i],"");
   for(i=0;i<m_Number;i++)
     ccb->GetText(i,m_FileNames[m_Number-i-1]);
   if(m_Number==16)
   	 (GetDlgItem(IDC_ADD_FILE))->EnableWindow(FALSE);
   else
     (GetDlgItem(IDC_ADD_FILE))->EnableWindow(TRUE);
   if(m_Number>1)
   {
       for(i=0;i<m_Number-1;i++)
	   {
	       for(j=i+1;j<m_Number;j++)
		   {
		     if(!strcmp(_strupr(m_FileNames[i]),_strupr(m_FileNames[j])))
			 {
				 if(f==0)
				 MessageBox("Warning: The selected file is duplicated: Please delete the same file","Training image setting",MB_ICONINFORMATION|MB_OK);
				 else
				 MessageBox("There are some duplicated files, please delete the same file","Training image setting",MB_ICONSTOP|MB_OK);
				 return 1;
			 }
		   }
	   }
   }
   return 0;
}

//The function to initialize the dialog
BOOL CSourceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	

	///////My code begins: Initialize DialogControls//////////////////
    //Set the size the Dialog
	MoveWindow(0,0,600,550);
	//Center the dialog
    CenterWindow(NULL);
	//Set the size and position of each DialogControl
	(GetDlgItem(IDC_STATIC_NUMBER))->MoveWindow(150,20,160,30);
	(GetDlgItem(IDC_EDIT_NUMBER))->MoveWindow(150,50,200,25);
	(GetDlgItem(IDC_LIST_FILE))->MoveWindow(50,140,400,320);
	(GetDlgItem(IDC_ADD_FILE))->MoveWindow(475,240,100,30);
	(GetDlgItem(IDC_DELETE_FILE))->MoveWindow(475,330,100,30);
	(GetDlgItem(IDOK))->MoveWindow(120,482,80,30);
	(GetDlgItem(IDCANCEL))->MoveWindow(420,482,80,30);
    //Initial the ListBox strings and Compute the Initial
	//TotalLenth and check the validate of the old filenames
	int i;
	for(i=0;i<m_Number;i++)
	{
	  ((CListBox *)GetDlgItem(IDC_LIST_FILE))->AddString(m_FileNames[i]);
	}  
	CheckSettings(0);
	((CListBox *)GetDlgItem(IDC_LIST_FILE))->SetHorizontalExtent(1000); 
	(GetDlgItem(IDC_DELETE_FILE))->EnableWindow(FALSE);
	UpdateData(FALSE);
	///////My code ends: Initialize DialogControls//////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//The overrided function for button IDOK
void CSourceDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(CheckSettings(1))
	{
	  if(m_Number>16)
	  {
	     MessageBox("There are more than 16 images selected, please delete some","Training image setting",MB_ICONINFORMATION|MB_OK);
	  }
	  return;
	}
	if(m_Number==0)
	{
	  MessageBox("There are no valid images selected, please add some","Training image setting",MB_ICONINFORMATION|MB_OK);
	  return;
	}
	CDialog::OnOK();
}

//The function to add files
void CSourceDlg::OnAddFile() 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);
   
   //The structure to open a FileDialog 
   OPENFILENAME ofn;
   //The file handle

   long int i;
   
   //The Filename and FileTitle 
   char FileName[1600],FileTitle[1600];
   FileName[0]='\0';
   FileTitle[0]='\0';
   /////Initialize the FileOpenDialog structure begins////
   //The structure size
   ofn.lStructSize=sizeof(OPENFILENAME); 
   //The Owner window handle
   ofn.hwndOwner=m_hWnd; 
   ofn.hInstance=NULL; 
   //The filter
   ofn.lpstrFilter=TEXT("JPG,BMP Images *.jpg;*.bmp\0*.jpg;*.bmp\0\0"); 
   
   //None user filter
   ofn.lpstrCustomFilter=NULL; 
   ofn.nMaxCustFilter=0; 
   //Select the first item
   ofn.nFilterIndex=1; 
   //The filename with full path
   ofn.lpstrFile=FileName; 
   ofn.nMaxFile=1600; 
   //The filename without path
   ofn.lpstrFileTitle=FileTitle; 
   ofn.nMaxFileTitle=1600; 
   //The initial directory is current directory
   ofn.lpstrInitialDir=m_sPath; 
   //The title
   ofn.lpstrTitle="Open 24bits JPG or BMP images"; 
   //The flags
   ofn.Flags=OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_EXPLORER;
   //The offset of the filename in the full path
   ofn.nFileOffset; 
   //The offset of the extension in the full path
   ofn.nFileExtension; 
   //Default extension
   ofn.lpstrDefExt="JPG"; 
   ofn.lCustData=NULL; 
   ofn.lpfnHook=NULL; 
   //User defined dialog
   ofn.lpTemplateName=NULL; 
   /////Initialize the FileOpenDialog structure ends////
   //Open the Dialog, and save the structure including the filename
   //If cancle or error,then return
   if(GetOpenFileName(&ofn)==0)return;
   int l;
   int len;
   char temppath[_MAX_PATH],tempfile[_MAX_PATH],tempname[_MAX_PATH];
   strcpy(temppath,FileName);
   len=strlen(temppath);
   if(FileName[len+1]!='\0')
   {
     FileName[len]='\\';
     l=len;
     i=0;
     for(;;)
	 {
	   if(FileName[i]=='\0'&&FileName[i+1]!='\0')
	   {
	     memcpy(tempname,FileName+l,i-l+1);
	     strcpy(tempfile,temppath);
	     strcat(tempfile,tempname);
	     ((CListBox *)GetDlgItem(IDC_LIST_FILE))->AddString(tempfile);
	     m_Number++;
         FileName[i]='\\';
	     l=i;
	   }
	   if(FileName[i]=='\0'&&FileName[i+1]=='\0')
	   {
	     memcpy(tempname,FileName+l,i-l+1);
	     strcpy(tempfile,temppath);
	     strcat(tempfile,tempname);
	     ((CListBox *)GetDlgItem(IDC_LIST_FILE))->AddString(tempfile);
	     m_Number++;
         break;
	   }
	   i++;
	 }
   }
   else
   {
	 ((CListBox *)GetDlgItem(IDC_LIST_FILE))->AddString(FileName);
     m_Number++;  
   }
   UpdateData(FALSE);
   CheckSettings(0);
   UpdateData(FALSE);
}

void CSourceDlg::OnSelchangeListFile() 
{
	// TODO: Add your control notification handler code here    	
	(GetDlgItem(IDC_DELETE_FILE))->EnableWindow(TRUE);
}

void CSourceDlg::OnDeleteFile() 
{
	// TODO: Add your control notification handler code here

	CListBox *clb;
	clb=(CListBox *)GetDlgItem(IDC_LIST_FILE);
	clb->DeleteString(clb->GetCurSel());
	m_Number--;
	(GetDlgItem(IDC_DELETE_FILE))->EnableWindow(FALSE);
	(GetDlgItem(IDC_ADD_FILE))->EnableWindow(TRUE);
	UpdateData(FALSE);
}


/////////The Functions added by VC with my code ends///////////////

int CSourceDlg::JudgeImageFile(char m_sFileName[MAX_PATH])
{
	CFile file;
	CJpeg jpg;
	DWORD m_iImageSize;
	JPEG_IMAGE_INFO info;
	BITMAPFILEHEADER bitfile;
    BITMAPINFOHEADER bitinfo;
	//Image open failed
	if(file.Open(m_sFileName,CFile::modeRead,NULL)==NULL)return -1; 
	m_iImageSize=file.GetLength();
	if(file.Read(&bitfile,sizeof(BITMAPFILEHEADER))!=sizeof(BITMAPFILEHEADER))
	{
	  file.Close();
	  return -2;
	}
	if(file.Read(&bitinfo,sizeof(BITMAPINFOHEADER))!=sizeof(BITMAPINFOHEADER))
	{
	  file.Close();
	  return -2;
	}
	file.Close();//close the file
    
	if(bitfile.bfType!=0x4d42)
	{
        //Reopen the file
		if(jpg.open(m_sFileName,IDCT_INT))
		{  
	       jpg.getImageInfo(&info);
	       if(info.comNum==3)
		   {
	           if(info.imgHeight>1024||info.imgHeight<256||info.imgWidth<256||info.imgWidth>1024)
			   {
				 jpg.close();
			     return -3;
			   }
			   jpg.close();
			   return 0;
		   }
	       else
		   {
	          jpg.close();
			  return -4;
		   }
	       
		}
		else
 		   return -4;
	}
    if(bitinfo.biWidth>1024||bitinfo.biWidth<256||bitinfo.biHeight<256||bitinfo.biHeight>1024)return -3;
    ////If the image is a 24bits image or not
	if(bitinfo.biBitCount!=24)
	  return -4;
	////If the image is compressed or not
	if(bitinfo.biCompression!=0)
	  return -4;
	///Check Palette
	if(bitfile.bfOffBits!=(int)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)))
	  return -4;
	//File size judgement
	if(m_iImageSize-bitfile.bfOffBits-WIDTHBYTES(24*bitinfo.biWidth)*bitinfo.biHeight<0) 
	  return -4;
	///end of read Image and computing feature
    return 0;
}
