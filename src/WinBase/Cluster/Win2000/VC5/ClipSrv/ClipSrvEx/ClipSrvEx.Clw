; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=4
Class1=CClipSrvApp
Class2=CExtObject
Class3=CBasePropertyPage
Class4=CClipSrvParamsPage
ResourceCount=1
Resource1=IDD_PP_CLIPSRV_PARAMETERS
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ClipSrvEx.h"

[CLS:CClipSrvApp]
Type=0
HeaderFile=ClipSrvEx.h
ImplementationFile=ClipSrvEx.cpp
Filter=N
LastObject=CClipSrvApp

[CLS:CExtObject]
Type=0
HeaderFile=ExtObj.h
ImplementationFile=ExtObj.cpp
BaseClass=CComObjectRoot
Filter=N
LastObject=CExtObject
VirtualFilter=C

[CLS:CBasePropertyPage]
Type=0
HeaderFile=BasePage.h
ImplementationFile=BasePage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CBasePropertyPage
VirtualFilter=idWC

[CLS:CClipSrvParamsPage]
Type=0
HeaderFile=ResProp.h
ImplementationFile=ResProp.cpp
BaseClass=CBasePropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CClipSrvParamsPage

[DLG:IDD_PP_CLIPSRV_PARAMETERS]
Type=1
Class=CClipSrvParamsPage
ControlCount=3
Control1=IDC_PP_ICON,static,1342177283
Control2=IDC_PP_TITLE,static,1342308492
