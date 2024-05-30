Attribute VB_Name = "systray"
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
' Systray.bas
'
' Declare some public data variables for use when maintaining
' the icon in the Status Tray.
'
'************************************************************

Option Explicit

Public Type NOTIFYICONDATA
    cbSize As Long
    hwnd As Long
    uId As Long
    uFlags As Long
    uCallBackMessage As Long
    hIcon As Long
    szTip As String * 64
End Type

Public Const NIM_ADD = 0
Public Const NIM_MODIFY = 1
Public Const NIM_DELETE = 2

Public Const NIF_MESSAGE = 1
Public Const NIF_ICON = 2
Public Const NIF_TIP = 4

Public Const WM_MOUSEMOVE = &H200

Public Const WM_LBUTTONDOWN = &H201
Public Const WM_LBUTTONUP = &H202
Public Const WM_LBUTTONDBLCLK = &H203
Public Const WM_RBUTTONDOWN = &H204
Public Const WM_RBUTTONUP = &H205
Public Const WM_RBUTTONDBLCLK = &H206

Public Declare Function SetForegroundWindow Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function Shell_NotifyIcon Lib "shell32" Alias "Shell_NotifyIconA" (ByVal dwMessage As Long, pnid As NOTIFYICONDATA) As Boolean



