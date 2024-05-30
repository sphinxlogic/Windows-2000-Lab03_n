; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutBox
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "urlpad.h"
LastPage=0

ClassCount=12
Class1=CAboutBox
Class2=CSplashWnd
Class3=CBigIcon
Class4=CModFileDialog
Class5=CInPlaceFrame
Class6=CMainFrame
Class7=CPadDoc
Class8=CPadFrame
Class9=CPadView
Class10=CPageSetupDlg
Class11=CTheApp
Class12=CSetTabStops

ResourceCount=14
Resource1=IDR_TEXTTYPE
Resource2=IDR_TEXTTYPE_EMBEDDED (_MAC)
Resource3=IDR_TEXTTYPE_INPLACE (_MAC)
Resource4=IDR_TEXTTYPE_INPLACE
Resource5=IDR_TEXTTYPE (_MAC)
Resource6=MYFILEOPEN
Resource7=IDD_SET_TABSTOPS
Resource8=IDD_PAGE_SETUP
Resource9=IDD_ABOUTBOX
Resource10=IDD_SPLASH
Resource11=IDR_MAINFRAME
Resource12=IDR_TEXTTYPE_EMBEDDED
Resource13=IDR_MAINFRAME (_MAC)
Resource14=IDD_ABOUTBOX (_MAC)

[CLS:CAboutBox]
Type=0
BaseClass=CDialog
HeaderFile=AboutBox.h
ImplementationFile=AboutBox.Cpp
LastObject=65535

[CLS:CSplashWnd]
Type=0
BaseClass=CDialog
HeaderFile=AboutBox.h
ImplementationFile=AboutBox.Cpp

[CLS:CBigIcon]
Type=0
BaseClass=CButton
HeaderFile=AboutBox.h
ImplementationFile=AboutBox.Cpp

[CLS:CModFileDialog]
Type=0
BaseClass=CFileDialog
HeaderFile=FileOpen.h
ImplementationFile=FileOpen.Cpp

[CLS:CInPlaceFrame]
Type=0
BaseClass=COleIPFrameWnd
HeaderFile=IPFrame.h
ImplementationFile=IPFrame.Cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.Cpp

[CLS:CPadDoc]
Type=0
BaseClass=COleServerDoc
HeaderFile=PadDoc.h
ImplementationFile=PadDoc.Cpp

[CLS:CPadFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=PadFrame.h
ImplementationFile=PadFrame.Cpp

[CLS:CPadView]
Type=0
BaseClass=CEditView
HeaderFile=PadView.h
ImplementationFile=PadView.Cpp

[CLS:CPageSetupDlg]
Type=0
BaseClass=CDialog
HeaderFile=PageSet.h
ImplementationFile=PageSet.Cpp

[CLS:CTheApp]
Type=0
BaseClass=CWinApp
HeaderFile=SuperPad.h
ImplementationFile=SuperPad.Cpp

[CLS:CSetTabStops]
Type=0
BaseClass=CDialog
HeaderFile=TabStop.h
ImplementationFile=TabStop.Cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutBox
ControlCount=10
Control1=IDC_BIGICON,button,1476395019
Control2=IDC_STATIC,static,1342177280
Control3=IDC_STATIC,static,1342177280
Control4=IDC_STATIC,static,1342177284
Control5=IDC_STATIC,static,1342177280
Control6=IDC_PHYSICAL_MEM,static,1342177280
Control7=IDC_STATIC,static,1342177280
Control8=IDC_DISK_SPACE,static,1342177280
Control9=IDOK,button,1342242817
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_SPLASH]
Type=1
Class=CSplashWnd
ControlCount=10
Control1=IDC_BIGICON,button,1476395019
Control2=IDC_STATIC,static,1342177280
Control3=IDC_STATIC,static,1342177280
Control4=IDC_STATIC,static,1342177284
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_PAGE_SETUP]
Type=1
Class=CPageSetupDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_HEADER,edit,1350631552
Control3=IDC_HEADER_FILE,button,1342373897
Control4=IDC_HEADER_SYSTEM,button,1342177289
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FOOTER,edit,1350631552
Control7=IDC_FOOTER_FILE,button,1342373897
Control8=IDC_FOOTER_SYSTEM,button,1342177289
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816

[DLG:IDD_SET_TABSTOPS]
Type=1
Class=CSetTabStops
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_TABS,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_PAGE_SETUP
Command4=ID_FILE_PRINT_SETUP
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_TEXTTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_PAGE_SETUP
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CLEAR
Command17=ID_EDIT_FIND
Command18=ID_EDIT_REPEAT
Command19=ID_EDIT_REPLACE
Command20=ID_EDIT_SELECT_ALL
Command21=ID_WORD_WRAP
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_SET_TABSTOPS
Command25=ID_CHOOSE_FONT
Command26=ID_CHOOSE_PRINT_FONT
Command27=ID_MIRROR_DISPLAY_FONT
Command28=ID_WINDOW_CASCADE
Command29=ID_WINDOW_TILE_HORZ
Command30=ID_WINDOW_ARRANGE
Command31=ID_APP_ABOUT
CommandCount=31

[MNU:IDR_TEXTTYPE_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_CLEAR
Command6=ID_EDIT_FIND
Command7=ID_EDIT_REPEAT
Command8=ID_EDIT_REPLACE
Command9=ID_EDIT_SELECT_ALL
Command10=ID_WORD_WRAP
Command11=ID_SET_TABSTOPS
Command12=ID_CHOOSE_FONT
Command13=ID_CHOOSE_PRINT_FONT
Command14=ID_MIRROR_DISPLAY_FONT
Command15=ID_VIEW_UPDATENOW
Command16=ID_APP_ABOUT
CommandCount=16

[MNU:IDR_TEXTTYPE_EMBEDDED]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_UPDATE
Command5=ID_FILE_SAVE_COPY_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_PAGE_SETUP
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CLEAR
Command17=ID_EDIT_FIND
Command18=ID_EDIT_REPEAT
Command19=ID_EDIT_REPLACE
Command20=ID_EDIT_SELECT_ALL
Command21=ID_WORD_WRAP
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_SET_TABSTOPS
Command25=ID_CHOOSE_FONT
Command26=ID_CHOOSE_PRINT_FONT
Command27=ID_MIRROR_DISPLAY_FONT
Command28=ID_WINDOW_CASCADE
Command29=ID_WINDOW_TILE_HORZ
Command30=ID_WINDOW_ARRANGE
Command31=ID_APP_ABOUT
CommandCount=31

[MNU:IDR_MAINFRAME (_MAC)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_PAGE_SETUP
Command4=ID_FILE_PRINT_SETUP
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
CommandCount=8

[MNU:IDR_TEXTTYPE (_MAC)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_PAGE_SETUP
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CLEAR
Command17=ID_EDIT_FIND
Command18=ID_EDIT_REPEAT
Command19=ID_EDIT_REPLACE
Command20=ID_EDIT_SELECT_ALL
Command21=ID_WORD_WRAP
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_CHOOSE_FONT
Command25=ID_CHOOSE_PRINT_FONT
Command26=ID_MIRROR_DISPLAY_FONT
Command27=ID_WINDOW_CASCADE
Command28=ID_WINDOW_TILE_HORZ
CommandCount=28

[MNU:IDR_TEXTTYPE_EMBEDDED (_MAC)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_UPDATE
Command5=ID_FILE_SAVE_COPY_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_PAGE_SETUP
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CLEAR
Command17=ID_EDIT_FIND
Command18=ID_EDIT_REPEAT
Command19=ID_EDIT_REPLACE
Command20=ID_EDIT_SELECT_ALL
Command21=ID_WORD_WRAP
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_CHOOSE_FONT
Command25=ID_CHOOSE_PRINT_FONT
Command26=ID_MIRROR_DISPLAY_FONT
Command27=ID_WINDOW_CASCADE
Command28=ID_WINDOW_TILE_HORZ
CommandCount=28

[MNU:IDR_TEXTTYPE_INPLACE (_MAC)]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_CLEAR
Command6=ID_EDIT_FIND
Command7=ID_EDIT_REPEAT
Command8=ID_EDIT_REPLACE
Command9=ID_EDIT_SELECT_ALL
Command10=ID_WORD_WRAP
Command11=ID_CHOOSE_FONT
Command12=ID_CHOOSE_PRINT_FONT
Command13=ID_MIRROR_DISPLAY_FONT
Command14=ID_VIEW_UPDATENOW
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_REPEAT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[ACL:IDR_TEXTTYPE_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_REPEAT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_CUT
Command9=ID_EDIT_UNDO
Command10=ID_CANCEL_INPLACE
CommandCount=10

[ACL:IDR_MAINFRAME (_MAC)]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_APP_EXIT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_REPEAT
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[ACL:IDR_TEXTTYPE_INPLACE (_MAC)]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_CANCEL_INPLACE
Command6=ID_EDIT_REPEAT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:MYFILEOPEN]
Type=1
Class=?
ControlCount=16
Control1=stc3,static,1342308352
Control2=edt1,edit,1350632576
Control3=lst1,listbox,1352732755
Control4=65535,static,1342308352
Control5=stc1,static,1342308480
Control6=lst2,listbox,1352732755
Control7=stc2,static,1342308352
Control8=cmb1,combobox,1352728643
Control9=stc4,static,1342308352
Control10=cmb2,combobox,1352729427
Control11=IDOK,button,1342373889
Control12=IDCANCEL,button,1342373888
Control13=pshHelp,button,1342373888
Control14=chx1,button,1342242818
Control15=psh14,button,1342373888
Control16=url,button,1342242819

[DLG:IDD_ABOUTBOX (_MAC)]
Type=1
Class=?
ControlCount=4
Control1=IDC_BIGICON,button,1476395019
Control2=65535,static,1342177280
Control3=65535,static,1342177280
Control4=IDOK,button,1342242817

