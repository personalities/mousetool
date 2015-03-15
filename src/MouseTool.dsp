# Microsoft Developer Studio Project File - Name="MouseTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MouseTool - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MouseTool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MouseTool.mak" CFG="MouseTool - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MouseTool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MouseTool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MouseTool - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /Qwd985 /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib eyehook.lib /nologo /subsystem:windows /map /machine:I386
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "MouseTool - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /Qwd985 /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib eyehook.lib /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "MouseTool - Win32 Release"
# Name "MouseTool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AbtDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Clicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ClickInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlertCheckIfClicking.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlertContexts.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlertNextClick.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlertSmartDrag.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetHotkey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOldSystemFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWarnLeftHotkey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWelcome.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWndTypeDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\ModeChanger.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseTool.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseTool.rc
# End Source File
# Begin Source File

SOURCE=.\MouseToolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptContext.cpp
# End Source File
# Begin Source File

SOURCE=.\OptGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\OptKeys.cpp
# End Source File
# Begin Source File

SOURCE=.\OptTiming.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TempStrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRAYICON.CPP
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AbtDlg.h
# End Source File
# Begin Source File

SOURCE=.\Clicker.h
# End Source File
# Begin Source File

SOURCE=.\ClickInfo.h
# End Source File
# Begin Source File

SOURCE=.\constants.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlertCheckIfClicking.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlertContexts.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlertNextClick.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlertSmartDrag.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetHotkey.h
# End Source File
# Begin Source File

SOURCE=.\DlgOldSystemFiles.h
# End Source File
# Begin Source File

SOURCE=.\DlgWarnLeftHotkey.h
# End Source File
# Begin Source File

SOURCE=.\DlgWelcome.h
# End Source File
# Begin Source File

SOURCE=.\DlgWndTypeDesc.h
# End Source File
# Begin Source File

SOURCE=.\KeyHandler.h
# End Source File
# Begin Source File

SOURCE=.\ModeChanger.h
# End Source File
# Begin Source File

SOURCE=.\MouseTool.h
# End Source File
# Begin Source File

SOURCE=.\MouseToolDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptContext.h
# End Source File
# Begin Source File

SOURCE=.\OptGeneral.h
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.h
# End Source File
# Begin Source File

SOURCE=.\OptKeys.h
# End Source File
# Begin Source File

SOURCE=.\OptTiming.h
# End Source File
# Begin Source File

SOURCE=.\ProcessHandler.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TempStrDlg.h
# End Source File
# Begin Source File

SOURCE=.\TRAYICON.H
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\WineyesTest.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ddn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dfl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\drag.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\lfl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_dfl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_drag.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_dup.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_flat.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_ldn.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_lfl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_lup.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rddn.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rdfl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rdn.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rdra.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rdup.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rfl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lrg_rup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MouseTool.ico
# End Source File
# Begin Source File

SOURCE=.\res\MouseTool.rc2
# End Source File
# Begin Source File

SOURCE=.\Res\mtDouble.ico
# End Source File
# Begin Source File

SOURCE=.\Res\mtStopped.ico
# End Source File
# Begin Source File

SOURCE=.\res\restore.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rfl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rup.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\splash.gif
# End Source File
# Begin Source File

SOURCE=.\Res\splash256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\splash3.gif
# End Source File
# Begin Source File

SOURCE=.\Res\splash4.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\splashbeta256.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\splashpr256.bmp
# End Source File
# Begin Source File

SOURCE=.\trouble.bmp
# End Source File
# End Group
# End Target
# End Project
# Section MouseTool : {6B0CDAB9-F6FE-11D0-8072-00A0C923B345}
# 	2:5:Class:CShareLock
# 	2:10:HeaderFile:sharelock.h
# 	2:8:ImplFile:sharelock.cpp
# End Section
# Section MouseTool : {6B0CDABB-F6FE-11D0-8072-00A0C923B345}
# 	2:21:DefaultSinkHeaderFile:sharelock.h
# 	2:16:DefaultSinkClass:CShareLock
# End Section
