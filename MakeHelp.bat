@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by VQRETRIEVE.HPJ. >"hlp\VqRetrieve.hm"
echo. >>"hlp\VqRetrieve.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\VqRetrieve.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\VqRetrieve.hm"
echo. >>"hlp\VqRetrieve.hm"
echo // Prompts (IDP_*) >>"hlp\VqRetrieve.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\VqRetrieve.hm"
echo. >>"hlp\VqRetrieve.hm"
echo // Resources (IDR_*) >>"hlp\VqRetrieve.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\VqRetrieve.hm"
echo. >>"hlp\VqRetrieve.hm"
echo // Dialogs (IDD_*) >>"hlp\VqRetrieve.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\VqRetrieve.hm"
echo. >>"hlp\VqRetrieve.hm"
echo // Frame Controls (IDW_*) >>"hlp\VqRetrieve.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\VqRetrieve.hm"
REM -- Make help for Project VQRETRIEVE


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\VqRetrieve.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\VqRetrieve.hlp" goto :Error
if not exist "hlp\VqRetrieve.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\VqRetrieve.hlp" Debug
if exist Debug\nul copy "hlp\VqRetrieve.cnt" Debug
if exist Release\nul copy "hlp\VqRetrieve.hlp" Release
if exist Release\nul copy "hlp\VqRetrieve.cnt" Release
echo.
goto :done

:Error
echo hlp\VqRetrieve.hpj(1) : error: Problem encountered creating help file

:done
echo.
