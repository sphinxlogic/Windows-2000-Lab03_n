; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMFCIEEvtSpyDlg
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCIEEvtSpy.h"

ClassCount=4
Class1=CMFCIEEvtSpyApp
Class2=CMFCIEEvtSpyDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CIE4Events
Resource3=IDD_MFCIEEVTSPY_DIALOG

[CLS:CMFCIEEvtSpyApp]
Type=0
HeaderFile=MFCIEEvtSpy.h
ImplementationFile=MFCIEEvtSpy.cpp
Filter=N

[CLS:CMFCIEEvtSpyDlg]
Type=0
HeaderFile=MFCIEEvtSpyDlg.h
ImplementationFile=MFCIEEvtSpyDlg.cpp
Filter=D
LastObject=CMFCIEEvtSpyDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MFCIEEvtSpyDlg.h
ImplementationFile=MFCIEEvtSpyDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCIEEVTSPY_DIALOG]
Type=1
Class=CMFCIEEvtSpyDlg
ControlCount=11
Control1=IDC_STARTIE,button,1342242816
Control2=IDC_EXIT,button,1342242816
Control3=IDC_WB_EVENTS_LST,listbox,1353793793
Control4=IDC_IE4_EVENTS_LST,listbox,1353793793
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_WEBBROWSER,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control8=IDC_ADDRESS_EDITBOX,edit,1350631552
Control9=IDC_GO,button,1342242817
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CLEAR_LISTBOXES,button,1342242816

[CLS:CIE4Events]
Type=0
HeaderFile=IE4Events.h
ImplementationFile=IE4Events.cpp
BaseClass=CCmdTarget
Filter=N

