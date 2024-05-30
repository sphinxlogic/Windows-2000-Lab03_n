; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CICSDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ICSDemo.h"

ClassCount=3
Class1=CICSDemoApp
Class2=CICSDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ICSDEMO_DIALOG

[CLS:CICSDemoApp]
Type=0
HeaderFile=ICSDemo.h
ImplementationFile=ICSDemo.cpp
Filter=N

[CLS:CICSDemoDlg]
Type=0
HeaderFile=ICSDemoDlg.h
ImplementationFile=ICSDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SYNCH

[CLS:CAboutDlg]
Type=0
HeaderFile=ICSDemoDlg.h
ImplementationFile=ICSDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_HELP_TEXT_1,static,1342308480
Control3=IDC_HELP_TEXT_2,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_HELP_TEXT_3,static,1342308352

[DLG:IDD_ICSDEMO_DIALOG]
Type=1
Class=CICSDemoDlg
ControlCount=5
Control1=IDC_START,button,1342242816
Control2=IDC_SYNCH,button,1342242816
Control3=IDC_STOP,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_TRACE_LIST,listbox,1352663296

