VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SupportedPlatform"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
' SupportedPlatform.cls
'
' This class module is used as a representation of the SMS_OS_Details class.
'
'************************************************************

Option Explicit

Public OSPlatform As String
Public OSName As String
Public OSMinVersion As String
Public OSMaxVersion As String
Public DisplayText As String
Public StringId As Long
Public ListIndex As Long



