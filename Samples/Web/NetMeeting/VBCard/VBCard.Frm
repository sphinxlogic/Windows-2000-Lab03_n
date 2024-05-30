VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Object = "{53D22821-D7E8-11CF-AD0A-0080C7137C82}#1.0#0"; "xmsconf.ocx"
Begin VB.Form VbCard 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Conference Card"
   ClientHeight    =   4125
   ClientLeft      =   1515
   ClientTop       =   3375
   ClientWidth     =   6375
   Icon            =   "VbCard.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4125
   ScaleWidth      =   6375
   ShowInTaskbar   =   0   'False
   Begin ComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   390
      Left            =   0
      TabIndex        =   5
      Top             =   0
      Width           =   6375
      _ExtentX        =   11245
      _ExtentY        =   688
      ImageList       =   "ImageList1"
      _Version        =   327680
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   8
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   ""
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            Style           =   3
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   "hangup"
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   ""
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            Style           =   3
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   "sendfile"
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   "whiteboard"
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   "chat"
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            ImageIndex      =   4
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   ""
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            Style           =   3
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Caption         =   ""
            Key             =   "sendcard"
            Description     =   ""
            Object.ToolTipText     =   ""
            Object.Tag             =   ""
            ImageIndex      =   5
         EndProperty
      EndProperty
      MouseIcon       =   "VbCard.frx":0442
   End
   Begin VB.ComboBox UserName 
      Height          =   315
      Left            =   120
      TabIndex        =   4
      Top             =   480
      Width           =   5415
   End
   Begin VB.CommandButton StartConf 
      Caption         =   "Call"
      Height          =   615
      Left            =   5640
      TabIndex        =   2
      Top             =   480
      Width           =   615
   End
   Begin VB.TextBox State 
      BackColor       =   &H8000000F&
      Height          =   300
      Left            =   120
      TabIndex        =   1
      Top             =   3720
      Width           =   3015
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   3480
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
      DialogTitle     =   "Send File"
      Filter          =   "All Files (*.*)|*.*"
      Flags           =   5
   End
   Begin ComctlLib.ListView MemberList 
      Height          =   2415
      Left            =   120
      TabIndex        =   3
      Top             =   1200
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   4260
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327680
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   1
      MouseIcon       =   "VbCard.frx":045E
      NumItems        =   2
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Name"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Connection"
         Object.Width           =   2540
      EndProperty
   End
   Begin ComctlLib.ProgressBar Progress 
      Height          =   300
      Left            =   3240
      TabIndex        =   0
      Top             =   3720
      Width           =   3015
      _ExtentX        =   5318
      _ExtentY        =   529
      _Version        =   327680
      Appearance      =   1
      MouseIcon       =   "VbCard.frx":047A
   End
   Begin VB.Image Unknown 
      Height          =   2355
      Left            =   4680
      Picture         =   "VbCard.frx":0496
      Top             =   1200
      Visible         =   0   'False
      Width           =   2100
   End
   Begin ActiveXConferenceCtl.ActiveXConference ConfMgr 
      Left            =   2880
      Top             =   720
   End
   Begin VB.Image Photo 
      BorderStyle     =   1  'Fixed Single
      Height          =   2415
      Left            =   4080
      Top             =   1200
      Width           =   2175
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   3960
      Top             =   720
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327680
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   5
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "VbCard.frx":3140
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "VbCard.frx":3252
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "VbCard.frx":3364
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "VbCard.frx":3476
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "VbCard.frx":3588
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuConference 
      Caption         =   "&Conference"
      Begin VB.Menu mnuStart 
         Caption         =   "&Start..."
      End
      Begin VB.Menu mnuLeave 
         Caption         =   "&Leave"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuConfSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptions 
         Caption         =   "&Options..."
      End
      Begin VB.Menu mnuConfSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuTools 
      Caption         =   "&Tools"
      Begin VB.Menu mnuSendFile 
         Caption         =   "Send &File..."
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuWhiteboard 
         Caption         =   "&Whiteboard"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuChat 
         Caption         =   "&Chat"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuStartRemote 
         Caption         =   "Start &Remote"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuToolsSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSendCard 
         Caption         =   "&Send Card"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuShowCard 
         Caption         =   "S&how Card"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Enabled         =   0   'False
   End
End
Attribute VB_Name = "VbCard"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'****************************************************************************
'
'  Module:     VBCARD.EXE
'  File:       VbCard.frm
'  Content:    Implementation of the main form
'
'  Copyright (c) Microsoft Corporation 1995-1997
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'****************************************************************************

Option Explicit

Const AppID As String = _
    "{54A4A060-CF42-11cf-8796-444553540000}"
Const AppName As String = "HotTalk"

Dim Conference As IConferenceX

Private Sub ConfMgr_ConferenceCreated( _
    ByVal pcnf As IConferenceX)
    
    Set Conference = pcnf
    Conference.Advise
End Sub

Private Sub ConfMgr_DataReceived( _
    ByVal pDataExchange As IConfDataExchangeX, _
    ByVal pMember As IConfMemberX, _
    ByVal pDataTransfer As IConfDataTransferX, _
    ByVal hr As Long)
    
    If pDataTransfer.BytesTransferred = BIZCARD_DATA_SIZE Then
        ReceiveBizCard pMember.Name, pDataTransfer
    Else
        ReceiveImage pMember.Name, pDataTransfer
    End If
End Sub

Private Sub ConfMgr_DataSent( _
    ByVal pDataExchange As IConfDataExchangeX, _
    ByVal pMember As IConfMemberX, _
    ByVal pDataTransfer As IConfDataTransferX, _
    ByVal hr As Long)
    
    If pDataTransfer.BytesTransferred = BIZCARD_DATA_SIZE Then
        State = "Bizcard sent"
    Else
        State = "Picture sent"
    End If
End Sub

Private Sub ConfMgr_FileReceived( _
    ByVal pFileExchange As IConfFileExchangeX, _
    ByVal pMember As IConfMemberX, _
    ByVal pFileTransfer As IConfFileTransferX, _
    ByVal hr As Long)
    
    FileRxTx pMember, pFileTransfer, False
End Sub

Private Sub ConfMgr_FileSent( _
    ByVal pFileExchange As IConfFileExchangeX, _
    ByVal pMember As IConfMemberX, _
    ByVal pFileTransfer As IConfFileTransferX, _
    ByVal hr As Long)
    
    FileRxTx pMember, pFileTransfer, True
End Sub

Private Sub ConfMgr_MemberChanged( _
    ByVal pConference As IConferenceX, _
    ByVal pMember As IConfMemberX, _
    ByVal lNotify As Long)
   
    Select Case lNotify
        Case CNF_MEMB_ADDED
            'member is now added in UpdateMemberList
            'callee doesn't get added notifications on startup
            'AddMember pMember
        Case CNF_MEMB_REMOVED
            DeleteMember pMember
    End Select
    
    UpdateMemberList
End Sub

Private Sub ConfMgr_StateChanged( _
    ByVal pConference As IConferenceX, _
    ByVal lConfState As Long, _
    ByVal hr As Long)
    
    Select Case lConfState
        Case CNF_STATE_IDLE
            State.text = "Conference is idle."
        Case CNF_STATE_INIT
            State.text = "Conference is initialized."
        Case CNF_STATE_START
            State.text = "Conference has started."
            OnConferenceRunning
        Case CNF_STATE_STOP
            State.text = "Conference has stopped."
            OnConferenceStopped
        Case CNF_STATE_OFFERED
            State.text = "Conference has been offered."
    End Select
End Sub

Private Sub Form_Load()
    Dim Conferences As IConferences
    
    Set Conference = Nothing
    
    InitChannels
    
    InitMemberArray
    
    UpdateMemberList
    UpdateButtons False
    
    ReadBizCard AppName, "Self", MyCard
    
    ConfMgr.Initialize AppID
    ConfMgr.Advise
    
    On Error Resume Next
    Set Conferences = ConfMgr.Conferences
    If Not (Conferences Is Nothing) Then
        ' get the first conference
        Set Conference = Conferences(0)
        
        If Not (Conference Is Nothing) Then
            Conference.Advise
            OnConferenceRunning
        End If
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    OnConferenceStopped
    ConfMgr.Unadvise
    
    WriteBizCard AppName, "Self", MyCard
End Sub

Private Sub MemberList_ItemClick(ByVal Item As ListItem)
    UpdateActiveIndex Item.text
End Sub

Private Sub mnuChat_Click()
    LaunchChat
End Sub

Private Sub mnuExit_Click()
    Unload VbCard
End Sub

Private Sub mnuOptions_Click()
    Options.Show 1
End Sub

Private Sub mnuSendFile_Click()
    SendFile
End Sub

Private Sub mnuStart_Click()
    Start
End Sub

Private Sub mnuLeave_Click()
    Leave
End Sub

Private Sub mnuWhiteboard_Click()
    LaunchWhiteboard
End Sub

Private Sub mnuSendCard_Click()
    SendCard
End Sub

Private Sub mnuShowCard_Click()
    ShowCard
End Sub

Private Sub Photo_DblClick()
    ShowCard
End Sub

Private Sub StartConf_Click()
    Start
End Sub

Private Sub Toolbar1_ButtonClick(ByVal Button As Button)
    Select Case Button.Key
        Case "hangup"
            Leave
        Case "sendfile"
            SendFile
        Case "whiteboard"
            LaunchWhiteboard
        Case "chat"
            LaunchChat
        Case "sendcard"
            SendCard
    End Select

End Sub

Private Sub UpdateButtons(State As Boolean)
    Toolbar1.Buttons("hangup").Enabled = State
    Toolbar1.Buttons("sendfile").Enabled = State
    Toolbar1.Buttons("whiteboard").Enabled = State
    Toolbar1.Buttons("chat").Enabled = State
    Toolbar1.Buttons("sendcard").Enabled = State
    mnuLeave.Enabled = State
    mnuSendFile.Enabled = State
    mnuWhiteboard.Enabled = State
    mnuChat.Enabled = State
    mnuStartRemote.Enabled = State
    mnuSendCard.Enabled = State
    mnuShowCard.Enabled = State
End Sub

Private Sub Start()
    Dim User As IConfUserX
    
    On Error Resume Next
    If Conference Is Nothing Then
        Set Conference = ConfMgr.CreateConference("MyConf", CNF_CAPS_DATA)
        If Conference Is Nothing Then
            ErrorMsg "failed to create conference"
            Exit Sub
        End If
        
        Conference.Advise
    End If
        
    Set User = ConfMgr.CreateUser(UserName.text, CNF_USER_MACHINENAME)
    If User Is Nothing Then
        ErrorMsg "failed to create user"
    Else
        If Not Conference.Invite(User) Then
            ErrorMsg "failed to invite user"
        End If
    End If
    
    UpdateButtons True
End Sub

Private Sub Leave()
    On Error Resume Next
    If Not (Conference Is Nothing) Then
        Conference.Leave
    End If
    UpdateButtons False
End Sub

Private Sub SendFile()
    Dim FileXfer As IConfFileTransferX
    
    On Error Resume Next
    CommonDialog1.ShowOpen
    If Err <> cdlCancel Then
        If FileChannel Is Nothing Then
            MsgBox "No File Exchange channel"
        Else
            Set FileXfer = FileChannel.SendFile(Nothing, Nothing, _
                CommonDialog1.FileName, CNFF_SFOPT_NONE)
            If FileXfer Is Nothing Then
                ErrorMsg "Failed to send file"
            End If
        End If
    End If
End Sub

Private Sub LaunchChat()
    MsgBox "Launch Chat"
End Sub

Private Sub LaunchWhiteboard()
    MsgBox "Launch Whiteboard"
End Sub

Private Sub FileRxTx( _
    ByVal pMember As IConfMemberX, _
    ByVal pFileTransfer As IConfFileTransferX, _
    fSend As Boolean)
    
    Dim MemberName As String
    
    If pMember Is Nothing Then
        MemberName = "somebody"
    Else
        MemberName = pMember.Name
    End If
    
    Select Case pFileTransfer.State
        Case CNF_FILE_IDLE
        Case CNF_FILE_INITIALIZING
        Case CNF_FILE_PROGRESS
        Case CNF_FILE_COMPLETE
            If pFileTransfer.TotalSize = pFileTransfer.BytesTransferred Then
                If fSend Then
                    MsgBox pFileTransfer.Name & " was sent to " & MemberName
                Else
                    MsgBox pFileTransfer.Name & " was received from " & MemberName
                End If
            Else
                MsgBox "File transfer canceled"
            End If
    End Select
        
    Progress.Max = pFileTransfer.TotalSize
    Progress.Value = pFileTransfer.BytesTransferred
End Sub


Private Sub OnConferenceStopped()
    If Not (Conference Is Nothing) Then
        Conference.Unadvise
        Set Conference = Nothing
    End If
    
    CloseChannels
    
    UpdateMemberList
    UpdateButtons False
End Sub

Private Sub OnConferenceRunning()
    OpenChannels Conference
    UpdateMemberList
    UpdateButtons True
End Sub

Private Sub ErrorMsg(text As String)
    MsgBox "Error " & Err.Number & ": " & text
End Sub

Private Sub UpdateMemberList()
    Dim Members As IConfMembers
    Dim Member As IConfMemberX
    Dim itmX As ListItem

    MemberList.ListItems.Clear

    On Error Resume Next
    If Not (Conference Is Nothing) Then
        Set Members = Conference.Members
        If Not (Members Is Nothing) Then
            For Each Member In Members
                Set itmX = MemberList.ListItems.Add(, , Member.Name)
                itmX.SubItems(1) = ConfCapsToString(Member.ConferenceCapabilities)
                AddMember Member    'NOP if already added
            Next
        End If
    End If
    
    If MemberList.ListItems.Count > 0 Then
        MemberList.ListItems(1).Selected = True
        UpdateActiveIndex MemberList.ListItems(1).text
    Else
        UpdateActiveIndex ""
    End If
End Sub

Private Sub SendCard()
    Dim Buffer1() As Byte
    Dim Buffer2() As Byte
    Dim Size As Integer

    If Not (DataChannel Is Nothing) Then
        Size = PictureToBytes(MyCard.PhotoFile, Buffer2)
        If Not Size = 0 Then
            BizCardToBytes MyCard, Buffer1, Size

            On Error Resume Next
            If Not DataChannel.SendData(Nothing, Nothing, Buffer1, CNFF_SDOPT_NONE) Then
                MsgBox "Unable to send bizcard"
            Else
                If Not DataChannel.SendData(Nothing, Nothing, Buffer2, CNFF_SDOPT_NONE) Then
                    MsgBox "Unable to send picture"
                End If
            End If
        Else
            MsgBox "Unable to send picture"
        End If
    End If
End Sub

Private Sub ShowCard()
    BizCard.Show 1
End Sub

