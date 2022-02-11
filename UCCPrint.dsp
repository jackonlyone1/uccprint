# Microsoft Developer Studio Project File - Name="UCCPrint" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UCCPrint - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UCCPrint.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UCCPrint.mak" CFG="UCCPrint - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UCCPrint - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UCCPrint - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UCCPrint - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\Bin/UCCPrint.exe"

!ELSEIF  "$(CFG)" == "UCCPrint - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\Bin/UCCPrintD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UCCPrint - Win32 Release"
# Name "UCCPrint - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppLookDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CanvasOffsetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChoiceListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBChartShape.cpp
# End Source File
# Begin Source File

SOURCE=.\DBGridMainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DbPrintGridShape.cpp
# End Source File
# Begin Source File

SOURCE=.\DBRecordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBSubConnectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBSubDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableShape.cpp
# End Source File
# Begin Source File

SOURCE=.\DIB.CPP
# End Source File
# Begin Source File

SOURCE=.\DIBStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\EFEventSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EFSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtTabModel.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtTabModelManager.cpp
# End Source File
# Begin Source File

SOURCE=.\FODecimalEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FOEFHyperLinkShape.cpp
# End Source File
# Begin Source File

SOURCE=.\FOHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeShape.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPBoxShape.cpp
# End Source File
# Begin Source File

SOURCE=..\ExtSource\FOPGDIPlusHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\ExtSource\FOPGDIPlusProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPNewAutoFontSizeShape.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPODBCDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPPropList.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPRichTextWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FOSplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GWExtBmpListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg6.cpp
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg7.cpp
# End Source File
# Begin Source File

SOURCE=.\MBTemplageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MBTemplateFileObj.cpp
# End Source File
# Begin Source File

SOURCE=.\MBTemplatePage0.cpp
# End Source File
# Begin Source File

SOURCE=.\MyImageShape.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListItemObj.cpp
# End Source File
# Begin Source File

SOURCE=.\MyNewTemplateWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBoxBar.cpp
# End Source File
# Begin Source File

SOURCE=.\NewButtonShape.cpp
# End Source File
# Begin Source File

SOURCE=.\NewVisualProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\ODBCAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\registry.cpp
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StartPageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SVImageControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SVRichEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SVSaveAsTemplateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SVShapeDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TableBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UCCPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\UCCPrint.rc
# End Source File
# Begin Source File

SOURCE=.\UCCPrintDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\UCCPrintView.cpp
# End Source File
# Begin Source File

SOURCE=.\UPChartStyleDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppLookDlg.h
# End Source File
# Begin Source File

SOURCE=.\CanvasOffsetDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChoiceListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBChartShape.h
# End Source File
# Begin Source File

SOURCE=.\DBGridMainDlg.h
# End Source File
# Begin Source File

SOURCE=.\DbPrintGridShape.h
# End Source File
# Begin Source File

SOURCE=.\DBRecordDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBSubConnectDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBSubDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBTableShape.h
# End Source File
# Begin Source File

SOURCE=.\DIB.H
# End Source File
# Begin Source File

SOURCE=.\DIBStatic.h
# End Source File
# Begin Source File

SOURCE=.\EFEventSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\EFSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\ExtTabModel.h
# End Source File
# Begin Source File

SOURCE=.\ExtTabModelManager.h
# End Source File
# Begin Source File

SOURCE=.\FODecimalEdit.h
# End Source File
# Begin Source File

SOURCE=.\FOEFHyperLinkShape.h
# End Source File
# Begin Source File

SOURCE=.\FOHyperLink.h
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeDefine.h
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\FOPBarcodeShape.h
# End Source File
# Begin Source File

SOURCE=.\FOPBoxShape.h
# End Source File
# Begin Source File

SOURCE=.\FOPHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FOPNewAutoFontSizeShape.h
# End Source File
# Begin Source File

SOURCE=.\FOPODBCDataSource.h
# End Source File
# Begin Source File

SOURCE=.\FOPPropList.h
# End Source File
# Begin Source File

SOURCE=.\FOPRichTextWnd.h
# End Source File
# Begin Source File

SOURCE=.\FOSplashWnd.h
# End Source File
# Begin Source File

SOURCE=.\GWExtBmpListBox.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg6.h
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg7.h
# End Source File
# Begin Source File

SOURCE=.\MBTemplageDlg.h
# End Source File
# Begin Source File

SOURCE=.\MBTemplateFileObj.h
# End Source File
# Begin Source File

SOURCE=.\MBTemplatePage0.h
# End Source File
# Begin Source File

SOURCE=.\MyImageShape.h
# End Source File
# Begin Source File

SOURCE=.\MyListItemObj.h
# End Source File
# Begin Source File

SOURCE=.\MyNewTemplateWnd.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBoxBar.h
# End Source File
# Begin Source File

SOURCE=.\NewButtonShape.h
# End Source File
# Begin Source File

SOURCE=.\NewVisualProxy.h
# End Source File
# Begin Source File

SOURCE=.\ODBCAccess.h
# End Source File
# Begin Source File

SOURCE=.\OptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StartPageDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SVImageControl.h
# End Source File
# Begin Source File

SOURCE=.\SVRichEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\SVSaveAsTemplateDlg.h
# End Source File
# Begin Source File

SOURCE=.\SVShapeDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\TableBar.h
# End Source File
# Begin Source File

SOURCE=.\TemplateDlg.h
# End Source File
# Begin Source File

SOURCE=.\UCCPrint.h
# End Source File
# Begin Source File

SOURCE=.\UCCPrintDoc.h
# End Source File
# Begin Source File

SOURCE=.\UCCPrintView.h
# End Source File
# Begin Source File

SOURCE=.\UPChartStyleDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_l.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_n.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_p.bmp
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

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp2208.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp2209.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp2210.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp2225.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fo_drawbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fo_toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\font_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_bar.ico
# End Source File
# Begin Source File

SOURCE=.\res\imagelis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mb_bitma.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mb_image.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mintitle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sv_richedit_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UCCPrint.ico
# End Source File
# Begin Source File

SOURCE=.\res\UCCPrint.rc2
# End Source File
# Begin Source File

SOURCE=.\res\UCCPrintDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\UCCPrint.reg
# End Source File
# End Target
# End Project
