VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form trayform 
   Caption         =   "StatTray"
   ClientHeight    =   780
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2250
   Icon            =   "trayform.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   780
   ScaleWidth      =   2250
   StartUpPosition =   3  'Windows Default
   Visible         =   0   'False
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   1800
      Top             =   360
   End
   Begin ComctlLib.ImageList imlMain 
      Left            =   1680
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   11
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":014A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":0464
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":077E
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":0A98
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":0DB2
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":10CC
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":13E6
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":1700
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":1A1A
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":1D34
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "trayform.frx":204E
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "If you are reading this, something went very wrong"
      Height          =   495
      Left            =   0
      TabIndex        =   0
      Top             =   180
      Width           =   2235
   End
   Begin VB.Menu mnuRoot 
      Caption         =   "root"
      Visible         =   0   'False
      Begin VB.Menu mnuRefresh 
         Caption         =   "Refresh &Interval"
         Begin VB.Menu mnuRefresh5m 
            Caption         =   "5 Minutes"
         End
         Begin VB.Menu mnuRefresh15m 
            Caption         =   "15 Minutes"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuRefresh30m 
            Caption         =   "30 Minutes"
         End
      End
      Begin VB.Menu mnuSep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRemove 
         Caption         =   "E&xit"
      End
   End
End
Attribute VB_Name = "trayform"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
' Trayform.frm
'
'  This form contains the bulk of the code for the program.
' All the major updating as well as interaction with CIMOM takes
' place here.  After the first call into this code to determine
' the initial state of the SMS Site, the Timer control will fire
' every minute and perform updates as dictated by the interval.
'
'  For more information about how to manipulate the System Tray from
' VB5 you can refer to the Microsoft Knowledge Base Article: Q176085.
' This article can be found at http://www.microsoft.com/support/ in
' the Online Support section.
'
'************************************************************

Option Explicit

Public Server As String         'The machine name of the SMS Provider host
Public Sitecode As String       'The Sitecode for the Site to monitor
Public User As String           'The User to use when connecting to CIMOM
Public Password As String       'The Password of the User

Public iCurrentMin As Integer   'The Current Minute that the timer is on
Public iTargetMin As Integer    'The Target Minute that the timer will update the data at

Private wServices As SWbemServices     'The ISWbemServices object
Private nid As NOTIFYICONDATA           'The custom type that contains the Status Tray
                                        ' configuration data.

Private Sub Form_Load()
'On load initialize the default polling interval
' and start the Timer.
    iCurrentMin = 0
    iTargetMin = 15
    Timer1.Enabled = True

End Sub

Public Sub AddNotifyIcon()
'Populate the initial state of the traybar icon
' Start with the "?" icon.

    nid.cbSize = Len(nid)
    nid.hIcon = Me.Icon
    nid.hwnd = Me.hwnd
    nid.szTip = "SMS StatTray (not connected)" & Chr(0)
    nid.uFlags = NIF_ICON Or NIF_TIP Or NIF_MESSAGE
    nid.uCallBackMessage = WM_MOUSEMOVE
    nid.uId = vbNull
    Shell_NotifyIcon NIM_ADD, nid

End Sub

Public Sub Connect()
'This sub will change the icon to a "?", and then create a connection
' to CIMOM.  This sub will be called every polling interval because
' the polling interval is somewhat long and we can not always be
' assured that the previous connection has survived the interval.
    
    On Error Resume Next
    
    'Update the icon to show that we are connecting.
    nid.szTip = "SMS StatTray (Connecting...)" & Chr(0)
    Me.Icon = imlMain.ListImages(1).Picture
    nid.hIcon = Me.Icon
    nid.uFlags = NIF_TIP Or NIF_ICON
    Shell_NotifyIcon NIM_MODIFY, nid
 
    'Create a WbemLocator
    Dim wLocator As New SWbemLocator
    If Err.Number Then
        nid.szTip = "SMS StatTray (Error Occurred During Connect)" & Chr(0)
        Me.Icon = imlMain.ListImages(1).Picture
        nid.hIcon = Me.Icon
        nid.uFlags = NIF_TIP Or NIF_ICON
        Shell_NotifyIcon NIM_MODIFY, nid
        Set wServices = Nothing
        Exit Sub
    End If

   'Get the global ISWbemServices object here.
    Set wServices = wLocator.ConnectServer(Server, "root/sms/site_" & Sitecode, User, Password)
    If Err.Number Then
        nid.szTip = "SMS StatTray (Error Occurred During Connect)" & Chr(0)
        Me.Icon = imlMain.ListImages(1).Picture
        nid.hIcon = Me.Icon
        nid.uFlags = NIF_TIP Or NIF_ICON
        Shell_NotifyIcon NIM_MODIFY, nid
        Set wServices = Nothing
        Exit Sub
    End If

End Sub

Private Sub Timer1_Timer()
'The timer control is set to fire every 60 seconds.
' Therefore this function will fire every minute, and it will
' increment the iCurrentMin variable until it hits the iTargetMin
' that defines the interval in minutes we want to update at.
    
    iCurrentMin = iCurrentMin + 1
    
    'Reconnect, update the Icon, and reset the counter.
    If iCurrentMin >= iTargetMin Then
       Connect
       UpdateStatus
       iCurrentMin = 0
    End If

End Sub

Public Sub UpdateStatus()
'Call GetStatus and use its return value to determine the state of the site.
' Update the icon as appropriate

    Select Case GetStatus
        
        'Error
        Case -1
            nid.szTip = "SMS StatTray (Cannot retrieve status)" & Chr(0)
            Me.Icon = imlMain.ListImages(1).Picture
            nid.hIcon = Me.Icon
            nid.uFlags = NIF_TIP Or NIF_ICON
            Shell_NotifyIcon NIM_MODIFY, nid
        
        'Green
        Case 0
            nid.szTip = "SMS StatTray (" & Server & ":" & Sitecode & ")" & Chr(0)
            Me.Icon = imlMain.ListImages(2).Picture
            nid.hIcon = Me.Icon
            nid.uFlags = NIF_TIP Or NIF_ICON
            Shell_NotifyIcon NIM_MODIFY, nid
        
        'Yellow
        Case 1
            nid.szTip = "SMS StatTray (" & Server & ":" & Sitecode & ")" & Chr(0)
            Me.Icon = imlMain.ListImages(3).Picture
            nid.hIcon = Me.Icon
            nid.uFlags = NIF_TIP Or NIF_ICON
            Shell_NotifyIcon NIM_MODIFY, nid
        
        'Red
        Case 2
            nid.szTip = "SMS StatTray (" & Server & ":" & Sitecode & ")" & Chr(0)
            Me.Icon = imlMain.ListImages(4).Picture
            nid.hIcon = Me.Icon
            nid.uFlags = NIF_TIP Or NIF_ICON
            Shell_NotifyIcon NIM_MODIFY, nid
    End Select
    
End Sub

Private Function GetStatus() As Long
'Retrieve the value of the Status property from SMS_SummarizerSiteStatus
' 0 = Green, 1 = Yellow, 2 = Red
' Note: We automatically default to retrieving the status of the SiteCode
'        that was entered in the frmConnect form.
    
    On Error Resume Next
    GetStatus = wServices.Get("sms_summarizersitestatus.sitecode=""" & Sitecode & """").Properties_("status").Value
    If Err.Number <> 0 Then GetStatus = -1

End Function

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
'This procedure receives the callbacks from the System Tray icon.

    Dim msg As Long
    msg = X / Screen.TwipsPerPixelX
    If msg = WM_RBUTTONUP Then
        SetForegroundWindow Me.hwnd
        Me.PopupMenu Me.mnuRoot, vbPopupMenuRightAlign
    End If

End Sub

Private Sub mnuRefresh15m_Click()
'The user wants to changes the default refresh interval.
' So update the menu, and change the timer
    
    mnuRefresh15m.Checked = True
    mnuRefresh30m.Checked = False
    mnuRefresh5m.Checked = False
    iTargetMin = 15

End Sub

Private Sub mnuRefresh5m_Click()
'The user wants to changes the default refresh interval.
' So update the menu, and change the timer
    
    mnuRefresh15m.Checked = False
    mnuRefresh30m.Checked = False
    mnuRefresh5m.Checked = True
    iTargetMin = 5

End Sub

Private Sub mnuRefresh30m_Click()
'The user wants to changes the default refresh interval.
' So update the menu, and change the timer
    
    mnuRefresh15m.Checked = False
    mnuRefresh30m.Checked = True
    mnuRefresh5m.Checked = False
    iTargetMin = 30

End Sub

Private Sub mnuRemove_Click()
'The user wants to exit the application so start unloading
    
    Unload Me

End Sub

Private Sub Form_Unload(Cancel As Integer)
'Remove the icon from the tray.
    
    Shell_NotifyIcon NIM_DELETE, nid

End Sub

