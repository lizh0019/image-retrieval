# Microsoft Developer Studio Project File - Name="SBIRSystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SBIRSystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SBIRSystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SBIRSystem.mak" CFG="SBIRSystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SBIRSystem - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SBIRSystem - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SBIRSystem - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SBIRSystem - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SBIRSystem - Win32 Release"
# Name "SBIRSystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DialogBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogLoadImage.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogParamentSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageBaseManage.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageResultDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RetrievalControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SBIRSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\SBIRSystem.rc
# End Source File
# Begin Source File

SOURCE=.\SBIRSystemDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SBIRSystemView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WriteAnnotionFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DialogBase.h
# End Source File
# Begin Source File

SOURCE=.\DialogLoadImage.h
# End Source File
# Begin Source File

SOURCE=.\DialogParamentSet.h
# End Source File
# Begin Source File

SOURCE=.\ImageBaseManage.h
# End Source File
# Begin Source File

SOURCE=.\ImageResultDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RetrievalControl.h
# End Source File
# Begin Source File

SOURCE=.\SBIRSystem.h
# End Source File
# Begin Source File

SOURCE=.\SBIRSystemDoc.h
# End Source File
# Begin Source File

SOURCE=.\SBIRSystemView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Classes\CFeatureExtractMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\CFeatureExtractMethod.h
# End Source File
# Begin Source File

SOURCE=.\Classes\cjpeg.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\cjpeg.h
# End Source File
# Begin Source File

SOURCE=.\Classes\idct.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\Matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\Classes\PictCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\PictCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Classes\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\Picture.h
# End Source File
# Begin Source File

SOURCE=.\res\SBIRSystem.ico
# End Source File
# Begin Source File

SOURCE=.\res\SBIRSystem.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SBIRSystemDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Classes\StatLink.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes\StatLink.h
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
