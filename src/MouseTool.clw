; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptContext
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MouseTool.h"

ClassCount=32
Class1=CMouseToolApp
Class2=CMouseToolDlg

ResourceCount=45
Resource2=IDD_MOUSETOOL_DIALOG
Resource1=IDR_MENU1
Class3=COptionsDlg
Resource3=IDD_DLG_WARN_LEFT_HOTKEY
Class4=CAboutDlg
Class5=CAbtDlg
Resource4=IDD_OPT_KEYS
Class6=CExpiredDialog
Resource5=IDD_DLG_ALERT_SD
Class7=CMouseDownDlg
Resource6=IDD_DLG_ALERT_CK_CLICK
Class8=CSplash
Resource7=IDD_DLG_ALERT_NEXTCLICK
Class9=CStoppedDlg
Class10=CExpiringDlg
Class11=CModeChanger
Resource8=IDD_DLG_OLD_COMCTL32
Class12=CAbtTrialDlg
Resource9=IDD_DLG_TYPE_DESCRIPTION
Class13=CExpdDlg
Resource10=IDD_ABTDIALOG
Class14=CRegisterDlg
Resource11=IDD_SPLASH
Class15=CTempStrDlg
Resource12=IDD_OPT_TIMING
Resource13=IDD_DLG_CONTEXT
Resource14=IDD_DLG_TYPE_DESCRIPTION (English (U.S.))
Class16=COptGeneral
Class17=COptJoystick
Class18=COptTiming
Class19=COptionsSheet
Resource15=IDD_OPT_GENERAL
Class20=COptKeys
Resource16=IDD_DLG_WELCOME
Class21=COptContext
Resource17=6
Class22=CDlgWndTypeDesc
Resource18=IDD_DLG_ALERT_CONTEXTS
Class23=CDlgGetHotkey
Resource19=IDD_DLG_GET_HOTKEY
Resource20=IDR_MAINFRAME
Resource21=IDD_OPTIONSDIALOG (English (U.S.))
Resource22=IDD_ABTDIALOG (English (U.S.))
Resource23=IDD_EXPIRED_DIALOG (English (U.S.))
Resource24=IDD_DLG_GET_HOTKEY (English (U.S.))
Resource25=IDD_STOPPEDDIALOG (English (U.S.))
Resource26=IDD_EXPIRINGDLG (English (U.S.))
Resource27=IDD_ABTTRIALDLG (English (U.S.))
Resource28=IDD_EXPDDIALOG (English (U.S.))
Resource29=IDD_REGISTER_DIALOG (English (U.S.))
Resource30=IDD_TEMPSTRDLG (English (U.S.))
Resource31=IDD_OPT_GENERAL (English (U.S.))
Resource32=IDD_OPT_TIMING (English (U.S.))
Resource33=IDD_OPT_JOYSTICK (English (U.S.))
Resource34=IDD_OPT_KEYS (English (U.S.))
Resource35=IDD_MOUSETOOL_DIALOG (English (U.S.))
Resource36=IDD_SPLASH (English (U.S.))
Class24=CDlgRegister
Class25=CDlgWelcome
Class26=CDlgOldSystemFiles
Class27=CDlgAlertContexts
Class28=CDlgAlertNextClick
Class29=CDlgAlertSmartDrag
Class30=CDlgExtend
Class31=CDlgWarnLeftHotkey
Class32=CDlgAlertCheckIfClicking
Resource37=IDD_DLG_CONTEXT (English (U.S.))
Resource38=IDD_DLG_ALERT_CK_CLICK (English (U.S.))
Resource39=IDD_DLG_OLD_COMCTL32 (English (U.S.))
Resource40=IDD_DLG_ALERT_SD (English (U.S.))
Resource41=IDD_DLG_ALERT_NEXTCLICK (English (U.S.))
Resource42=IDD_DLG_ALERT_CONTEXTS (English (U.S.))
Resource43=IDD_DLG_WARN_LEFT_HOTKEY (English (U.S.))
Resource44=IDD_DLG_WELCOME (English (U.S.))
Resource45=IDR_MAINFRAME (English (U.S.))

[CLS:CMouseToolApp]
Type=0
HeaderFile=MouseTool.h
ImplementationFile=MouseTool.cpp
Filter=N
LastObject=CMouseToolApp

[CLS:CMouseToolDlg]
Type=0
HeaderFile=MouseToolDlg.h
ImplementationFile=MouseToolDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMouseToolDlg


[DLG:IDD_MOUSETOOL_DIALOG]
Type=1
Class=CMouseToolDlg
ControlCount=9
Control1=IDC_BUTTON1,button,1342242944
Control2=IDC_OPTIONSBUTTON,button,1342242816
Control3=IDC_HELPBUTTON,button,1342242816
Control4=IDC_JOYPROGRESS,msctls_progress32,1082130432
Control5=IDC_LSTATIC,static,1342177294
Control6=IDC_DSTATIC,static,1342177294
Control7=IDC_RSTATIC,static,1342177294
Control8=IDC_SMALLBUTTON,button,1342242944
Control9=IDC_EDIT1,edit,1082196096

[CLS:COptionsDlg]
Type=0
HeaderFile=OptionsDlg.h
ImplementationFile=OptionsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=COptionsDlg
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABTDIALOG]
Type=1
Class=CAbtDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_VERSION,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC1,static,1342308352
Control6=IDC_STATIC,static,1342177294
Control7=IDC_STATIC,static,1342308352

[CLS:CAbtDlg]
Type=0
HeaderFile=AbtDlg.h
ImplementationFile=AbtDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAbtDlg
VirtualFilter=dWC

[CLS:CExpiredDialog]
Type=0
HeaderFile=ExpiredDialog.h
ImplementationFile=ExpiredDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_REGBUTTON
VirtualFilter=dWC

[CLS:CMouseDownDlg]
Type=0
HeaderFile=MouseDownDlg.h
ImplementationFile=MouseDownDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMouseDownDlg

[DLG:IDD_SPLASH]
Type=1
Class=CSplash
ControlCount=2
Control1=IDC_STATIC_VERSION,static,1073872907
Control2=IDC_STATIC,static,1073741838

[CLS:CSplash]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CDialog
Filter=D
LastObject=CSplash
VirtualFilter=dWC

[CLS:CStoppedDlg]
Type=0
HeaderFile=StoppedDlg.h
ImplementationFile=StoppedDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStoppedDlg

[CLS:CExpiringDlg]
Type=0
HeaderFile=ExpiringDlg.h
ImplementationFile=ExpiringDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CExpiringDlg
VirtualFilter=dWC

[CLS:CModeChanger]
Type=0
HeaderFile=ModeChanger.h
ImplementationFile=ModeChanger.cpp
BaseClass=CStatic
Filter=W

[CLS:CAbtTrialDlg]
Type=0
HeaderFile=AbtTrialDlg.h
ImplementationFile=AbtTrialDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STAT_TRIAL

[CLS:CExpdDlg]
Type=0
HeaderFile=ExpdDlg.h
ImplementationFile=ExpdDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[CLS:CRegisterDlg]
Type=0
HeaderFile=RegisterDlg.h
ImplementationFile=RegisterDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_FULL_CODE_BUTTON

[CLS:CTempStrDlg]
Type=0
HeaderFile=TempStrDlg.h
ImplementationFile=TempStrDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDTTEMP_STR
VirtualFilter=dWC

[DLG:IDD_OPT_GENERAL]
Type=1
Class=COptGeneral
ControlCount=21
Control1=IDC_KEEP_ON_TOP,button,1342242819
Control2=IDC_SHOW_DRAG_CHECK,button,1342242819
Control3=IDC_AUDIBLE_TICK,button,1342242819
Control4=IDC_STARTUPCHECK,button,1342242819
Control5=IDC_BUTTON_ABOUT,button,1342242816
Control6=IDC_TICKS,edit,1350631552
Control7=IDC_STAT_DWELL_TIME,static,1342308352
Control8=IDC_EDT_DWELL_ZONE,edit,1350631552
Control9=IDC_STAT_DWELL_ZONE,static,1342308352
Control10=IDC_SMART_DRAG_CHECK,button,1342242819
Control11=IDC_SMART_DRAG_DELAY_EDIT,edit,1350631552
Control12=IDC_SMART_DRAG_FRAME,button,1342177287
Control13=IDC_STAT_SMART_DRAG,static,1342308352
Control14=IDC_STRETCH_TIMER_CHECK,button,1342242819
Control15=IDC_MINSTOWAIT,edit,1350631552
Control16=IDC_STATIC_STRETCH_FRAME,button,1342177287
Control17=IDC_TIME_TO_GO,edit,1350568064
Control18=IDC_STAT_MINS_BTWN_BREAK,static,1342308352
Control19=IDC_STAT_MINS_TO_NEXT_BREAK,static,1342308352
Control20=IDC_CK_OVERRIDE_NEXT_CLICK,button,1342242819
Control21=IDC_CK_MOUSE_DN,button,1342242819

[DLG:IDD_OPT_TIMING]
Type=1
Class=COptTiming
ControlCount=4
Control1=IDC_SLOW_CLICK_CHECK,button,1342242819
Control2=IDC_SLOW_CLICK_DELAY_EDIT,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_SLOW_CLICK_STATIC,static,1342308352

[CLS:COptGeneral]
Type=0
HeaderFile=OptGeneral.h
ImplementationFile=OptGeneral.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_CK_MOUSE_DN
VirtualFilter=idWC

[CLS:COptJoystick]
Type=0
HeaderFile=OptJoystick.h
ImplementationFile=OptJoystick.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_MONITORJOYCHECK
VirtualFilter=idWC

[CLS:COptTiming]
Type=0
HeaderFile=OptTiming.h
ImplementationFile=OptTiming.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=COptTiming

[CLS:COptionsSheet]
Type=0
HeaderFile=OptionsSheet.h
ImplementationFile=OptionsSheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=COptionsSheet
VirtualFilter=hWC

[DLG:IDD_OPT_KEYS]
Type=1
Class=COptKeys
ControlCount=24
Control1=IDC_EDT_DBL_KEY,edit,1350633600
Control2=IDC_EDT_RIGHT_KEY,edit,1350633600
Control3=IDC_STAT_DBL_KEY,static,1342308352
Control4=IDC_BUTTON_DBL_KEY,button,1342242816
Control5=IDC_STAT_RIGHT_KEY,static,1342308352
Control6=IDC_BUTTON_RIGHT_KEY,button,1342242816
Control7=IDC_CK_ENABLE_HOTKEYS,button,1342242819
Control8=IDC_STAT_HOTKEY_FRAME,button,1342177287
Control9=IDC_EDT_STOP_KEY,edit,1350633600
Control10=IDC_STAT_STOP_KEY,static,1342308352
Control11=IDC_BUTTON_STOP_KEY,button,1342242816
Control12=IDC_EDT_LEFT_BUTTON,edit,1350633600
Control13=IDC_EDT_RIGHT_BUTTON,edit,1350633600
Control14=IDC_EDT_DBL_BUTTON,edit,1350633600
Control15=IDC_STAT_LEFT_BUTTON,static,1342308352
Control16=IDC_STAT_FRAME_BUTTONS,button,1342177287
Control17=IDC_STAT_RIGHT_BUTTON,static,1342308352
Control18=IDC_STAT_DOUBLE_BUTTON,static,1342308352
Control19=IDC_BUTTON_LEFT,button,1342242816
Control20=IDC_BUTTON_RIGHT,button,1342242816
Control21=IDC_BUTTON_DOUBLE,button,1342242816
Control22=IDC_STAT_TOGGLE_LEFT,static,1342308352
Control23=IDC_EDT_TOGGLE_BTN,edit,1350633600
Control24=IDC_BUTTON_TOGGLE,button,1342242816

[CLS:COptKeys]
Type=0
HeaderFile=OptKeys.h
ImplementationFile=OptKeys.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=COptKeys
VirtualFilter=idWC

[DLG:IDD_DLG_CONTEXT]
Type=1
Class=COptContext
ControlCount=13
Control1=IDC_CK_ENABLE_CONTEXT,button,1342242819
Control2=IDC_LST_APPS,listbox,1352728835
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_RADIO5,button,1342177289
Control8=IDC_EDT_LAST_CONTEXT,edit,1350633600
Control9=IDC_STAT_LAST_CONTEXT,static,1342308352
Control10=IDC_BUTTON_ADD_CONTEXT,button,1342242816
Control11=IDC_BUTTON_DELETE_CONTEXT,button,1342242816
Control12=IDC_STAT_LST_APPS,static,1342308352
Control13=IDC_STAT_ACTION,button,1342177287

[CLS:COptContext]
Type=0
HeaderFile=OptContext.h
ImplementationFile=OptContext.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_CHECK1

[DLG:IDD_DLG_TYPE_DESCRIPTION]
Type=1
Class=CDlgWndTypeDesc
ControlCount=4
Control1=IDC_EDT_TYPE_DESCRIPTION,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CDlgWndTypeDesc]
Type=0
HeaderFile=dlgwndtypedesc.h
ImplementationFile=dlgwndtypedesc.cpp
BaseClass=CDialog
LastObject=CDlgWndTypeDesc

[DLG:IDD_DLG_GET_HOTKEY]
Type=1
Class=CDlgGetHotkey
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDT_HOTKEY,edit,1350633600
Control5=IDC_BTN_DEL,button,1342242816
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgGetHotkey]
Type=0
HeaderFile=DlgGetHotkey.h
ImplementationFile=DlgGetHotkey.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDT_HOTKEY

[DLG:IDD_MOUSETOOL_DIALOG (English (U.S.))]
Type=1
Class=CMouseToolDlg
ControlCount=9
Control1=IDC_BUTTON1,button,1342242944
Control2=IDC_OPTIONSBUTTON,button,1342242816
Control3=IDC_HELPBUTTON,button,1342242816
Control4=IDC_JOYPROGRESS,msctls_progress32,1082130432
Control5=IDC_LSTATIC,static,1342177294
Control6=IDC_DSTATIC,static,1342177294
Control7=IDC_RSTATIC,static,1342177294
Control8=IDC_SMALLBUTTON,button,1342242944
Control9=IDC_EDIT1,edit,1082196096

[DLG:IDD_OPTIONSDIALOG (English (U.S.))]
Type=1
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_CHECK1,button,1342242819
Control5=IDC_SHOW_DRAG_CHECK,button,1342242819
Control6=IDC_TICK_CHECK,button,1342242819
Control7=IDC_STARTUPCHECK,button,1342242819
Control8=IDC_TICKS,edit,1350631552
Control9=IDC_SLOW_CLICK_CHECK,button,1342242819
Control10=IDC_SLOW_CLICK_DELAY_EDIT,edit,1350631552
Control11=IDC_CONFIGCHECK,button,1342242819
Control12=IDC_MONITORJOYCHECK,button,1342242819
Control13=IDC_DRAG_CHECK,button,1342242819
Control14=IDC_REVERSE_CHECK,button,1342242819
Control15=IDC_TIMER_CHECK,button,1342242819
Control16=IDC_MINSTOWAIT,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,button,1342177287
Control20=IDC_TIME_TO_GO,edit,1350568064
Control21=IDC_STRETCH_BREAK_STATIC,static,1342308352
Control22=IDC_NEXT_BREAK_STATIC,static,1342308352
Control23=IDC_SLOW_CLICK_STATIC,static,1342308352
Control24=IDC_JOYSTATIC,button,1342177287
Control25=IDC_REGISTERBUTTON,button,1342242816
Control26=IDC_TEST_BUTTON,button,1342242816
Class=COptionsDlg

[DLG:IDD_ABTDIALOG (English (U.S.))]
Type=1
Class=CAbtDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_VERSION,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC1,static,1342308352
Control6=IDC_STATIC,static,1342177294
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_EXPIRED_DIALOG (English (U.S.))]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_REGBUTTON,button,1342242816
Class=CExpiredDialog

[DLG:IDD_SPLASH (English (U.S.))]
Type=1
Class=CSplash
ControlCount=2
Control1=IDC_STATIC_VERSION,static,1073872907
Control2=IDC_STATIC,static,1073741838

[DLG:IDD_STOPPEDDIALOG (English (U.S.))]
Type=1
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Class=CStoppedDlg

[DLG:IDD_EXPIRINGDLG (English (U.S.))]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC1,static,1342308352
Control3=IDC_STATIC,static,1342308352
Class=CExpiringDlg

[DLG:IDD_ABTTRIALDLG (English (U.S.))]
Type=1
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ORDERINFOEDIT,edit,1342179332
Control6=IDC_MESTATIC,static,1342181390
Control7=IDC_STATIC,static,1342308352
Class=CAbtTrialDlg

[DLG:IDD_EXPDDIALOG (English (U.S.))]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Class=CExpdDlg

[DLG:IDD_REGISTER_DIALOG (English (U.S.))]
Type=1
ControlCount=4
Control1=IDCANCEL,button,1342242816
Control2=IDC_FULL_CODE_BUTTON,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Class=CRegisterDlg

[DLG:IDD_TEMPSTRDLG (English (U.S.))]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDTTEMP_STR,edit,1350631552
Class=CTempStrDlg

[DLG:IDD_OPT_GENERAL (English (U.S.))]
Type=1
Class=COptGeneral
ControlCount=21
Control1=IDC_KEEP_ON_TOP,button,1342242819
Control2=IDC_SHOW_DRAG_CHECK,button,1342242819
Control3=IDC_AUDIBLE_TICK,button,1342242819
Control4=IDC_STARTUPCHECK,button,1342242819
Control5=IDC_BUTTON_ABOUT,button,1342242816
Control6=IDC_TICKS,edit,1350631552
Control7=IDC_STAT_DWELL_TIME,static,1342308352
Control8=IDC_EDT_DWELL_ZONE,edit,1350631552
Control9=IDC_STAT_DWELL_ZONE,static,1342308352
Control10=IDC_SMART_DRAG_CHECK,button,1342242819
Control11=IDC_SMART_DRAG_DELAY_EDIT,edit,1350631552
Control12=IDC_SMART_DRAG_FRAME,button,1342177287
Control13=IDC_STAT_SMART_DRAG,static,1342308352
Control14=IDC_STRETCH_TIMER_CHECK,button,1342242819
Control15=IDC_MINSTOWAIT,edit,1350631552
Control16=IDC_STATIC_STRETCH_FRAME,button,1342177287
Control17=IDC_TIME_TO_GO,edit,1350568064
Control18=IDC_STAT_MINS_BTWN_BREAK,static,1342308352
Control19=IDC_STAT_MINS_TO_NEXT_BREAK,static,1342308352
Control20=IDC_CK_OVERRIDE_NEXT_CLICK,button,1342242819
Control21=IDC_CK_MOUSE_DN,button,1342242819

[DLG:IDD_OPT_TIMING (English (U.S.))]
Type=1
Class=COptTiming
ControlCount=4
Control1=IDC_SLOW_CLICK_CHECK,button,1342242819
Control2=IDC_SLOW_CLICK_DELAY_EDIT,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_SLOW_CLICK_STATIC,static,1342308352

[DLG:IDD_OPT_JOYSTICK (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_MONITORJOYCHECK,button,1342242819
Control2=IDC_DRAG_CHECK,button,1342242819
Control3=IDC_REVERSE_CHECK,button,1342242819
Control4=IDC_JOYSTATIC,button,1342177287
Class=COptJoystick

[DLG:IDD_OPT_KEYS (English (U.S.))]
Type=1
Class=COptKeys
ControlCount=24
Control1=IDC_EDT_DBL_KEY,edit,1350633600
Control2=IDC_EDT_RIGHT_KEY,edit,1350633600
Control3=IDC_STAT_DBL_KEY,static,1342308352
Control4=IDC_BUTTON_DBL_KEY,button,1342242816
Control5=IDC_STAT_RIGHT_KEY,static,1342308352
Control6=IDC_BUTTON_RIGHT_KEY,button,1342242816
Control7=IDC_CK_ENABLE_HOTKEYS,button,1342242819
Control8=IDC_STAT_HOTKEY_FRAME,button,1342177287
Control9=IDC_EDT_STOP_KEY,edit,1350633600
Control10=IDC_STAT_STOP_KEY,static,1342308352
Control11=IDC_BUTTON_STOP_KEY,button,1342242816
Control12=IDC_EDT_LEFT_BUTTON,edit,1350633600
Control13=IDC_EDT_RIGHT_BUTTON,edit,1350633600
Control14=IDC_EDT_DBL_BUTTON,edit,1350633600
Control15=IDC_STAT_LEFT_BUTTON,static,1342308352
Control16=IDC_STAT_FRAME_BUTTONS,button,1342177287
Control17=IDC_STAT_RIGHT_BUTTON,static,1342308352
Control18=IDC_STAT_DOUBLE_BUTTON,static,1342308352
Control19=IDC_BUTTON_LEFT,button,1342242816
Control20=IDC_BUTTON_RIGHT,button,1342242816
Control21=IDC_BUTTON_DOUBLE,button,1342242816
Control22=IDC_STAT_TOGGLE_LEFT,static,1342308352
Control23=IDC_EDT_TOGGLE_BTN,edit,1350633600
Control24=IDC_BUTTON_TOGGLE,button,1342242816

[DLG:IDD_DLG_CONTEXT (English (U.S.))]
Type=1
Class=COptContext
ControlCount=14
Control1=IDC_CK_ENABLE_CONTEXT,button,1342242819
Control2=IDC_LST_APPS,listbox,1352728835
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_RADIO5,button,1342177289
Control8=IDC_EDT_LAST_CONTEXT,edit,1350633600
Control9=IDC_STAT_LAST_CONTEXT,static,1342308352
Control10=IDC_BUTTON_ADD_CONTEXT,button,1342242816
Control11=IDC_BUTTON_DELETE_CONTEXT,button,1342242816
Control12=IDC_STAT_LST_APPS,static,1342308352
Control13=IDC_STAT_ACTION,button,1342177287
Control14=IDC_CHECK1,button,1342242819

[DLG:IDD_DLG_TYPE_DESCRIPTION (English (U.S.))]
Type=1
Class=CDlgWndTypeDesc
ControlCount=4
Control1=IDC_EDT_TYPE_DESCRIPTION,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_GET_HOTKEY (English (U.S.))]
Type=1
Class=CDlgGetHotkey
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDT_HOTKEY,edit,1350633600
Control5=IDC_BTN_DEL,button,1342242816
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgRegister]
Type=0
HeaderFile=DlgRegister.h
ImplementationFile=DlgRegister.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgRegister

[DLG:IDD_DLG_WELCOME]
Type=1
Class=CDlgWelcome
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgWelcome]
Type=0
HeaderFile=DlgWelcome.h
ImplementationFile=DlgWelcome.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgWelcome

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_RIGHTCLICK_DOUBLECLICK
Command2=ID_RIGHTCLICK_LEFTCLICK
CommandCount=2

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_TRAYMENU_RESTORE
Command2=ID_TRAYMENU_RIGHTCLICK
Command3=ID_TRAYMENU_DOUBLECLICK
Command4=ID_TRAYMENU_LEFTCLICK
Command5=ID_TRAYMENU_STOPMOUSETOOL
Command6=ID_TRAYMENU_NEXTONLY
CommandCount=6

[MNU:6]
Type=1
Command1=ID_TRAYMENU_RIGHTCLICK
Command2=ID_TRAYMENU_DOUBLECLICK
Command3=ID_TRAYMENU_LEFTCLICK
CommandCount=3

[DLG:IDD_DLG_OLD_COMCTL32]
Type=1
Class=CDlgOldSystemFiles
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STAT_COMUPD,static,1342308352
Control8=IDC_BUTTON_GET_FILES,button,1073815552

[CLS:CDlgOldSystemFiles]
Type=0
HeaderFile=DlgOldSystemFiles.h
ImplementationFile=DlgOldSystemFiles.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgOldSystemFiles

[DLG:IDD_DLG_ALERT_SD]
Type=1
Class=CDlgAlertSmartDrag
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CK_DONT_REMIND,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_ALERT_NEXTCLICK]
Type=1
Class=CDlgAlertNextClick
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CK_DONT_REMIND,button,1342242819

[DLG:IDD_DLG_ALERT_CONTEXTS]
Type=1
Class=CDlgAlertContexts
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352

[CLS:CDlgAlertContexts]
Type=0
HeaderFile=DlgAlertContexts.h
ImplementationFile=DlgAlertContexts.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAlertContexts
VirtualFilter=dWC

[CLS:CDlgAlertNextClick]
Type=0
HeaderFile=DlgAlertNextClick.h
ImplementationFile=DlgAlertNextClick.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAlertNextClick
VirtualFilter=dWC

[CLS:CDlgAlertSmartDrag]
Type=0
HeaderFile=DlgAlertSmartDrag.h
ImplementationFile=DlgAlertSmartDrag.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgAlertSmartDrag

[CLS:CDlgExtend]
Type=0
HeaderFile=DlgExtend.h
ImplementationFile=DlgExtend.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgExtend

[CLS:CDlgWarnLeftHotkey]
Type=0
HeaderFile=DlgWarnLeftHotkey.h
ImplementationFile=DlgWarnLeftHotkey.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgWarnLeftHotkey

[DLG:IDD_DLG_WARN_LEFT_HOTKEY]
Type=1
Class=CDlgWarnLeftHotkey
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CK_DONT_SHOW_AGAIN,button,1342242819
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_ALERT_CK_CLICK]
Type=1
Class=CDlgAlertCheckIfClicking
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CK_DONT_WARN_CK_CLICK,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgAlertCheckIfClicking]
Type=0
HeaderFile=DlgAlertCheckIfClicking.h
ImplementationFile=DlgAlertCheckIfClicking.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CK_DONT_WARN_CK_CLICK

[DLG:IDD_DLG_WELCOME (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_OLD_COMCTL32 (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STAT_COMUPD,static,1342308352
Control8=IDC_BUTTON_GET_FILES,button,1073815552

[DLG:IDD_DLG_ALERT_SD (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CK_DONT_REMIND,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_ALERT_NEXTCLICK (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CK_DONT_REMIND,button,1342242819

[DLG:IDD_DLG_ALERT_CONTEXTS (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_WARN_LEFT_HOTKEY (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CK_DONT_SHOW_AGAIN,button,1342242819
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_ALERT_CK_CLICK (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CK_DONT_WARN_CK_CLICK,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_TRAYMENU_RESTORE
Command2=ID_TRAYMENU_RIGHTCLICK
Command3=ID_TRAYMENU_DOUBLECLICK
Command4=ID_TRAYMENU_LEFTCLICK
Command5=ID_TRAYMENU_STOPMOUSETOOL
Command6=ID_TRAYMENU_NEXTONLY
CommandCount=6

