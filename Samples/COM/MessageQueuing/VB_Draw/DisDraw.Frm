VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5820
   ClientLeft      =   3345
   ClientTop       =   2295
   ClientWidth     =   6330
   LinkTopic       =   "Form1"
   ScaleHeight     =   5820
   ScaleWidth      =   6330
   Begin VB.Frame Frame1 
      Caption         =   "Sent Messages"
      Height          =   975
      Left            =   3120
      TabIndex        =   6
      Top             =   4680
      Width           =   2535
      Begin VB.OptionButton Option1 
         Caption         =   "&Express"
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   4
         Top             =   240
         Value           =   -1  'True
         Width           =   2052
      End
      Begin VB.OptionButton Option1 
         Caption         =   "&Recoverable"
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   5
         Top             =   600
         Width           =   2052
      End
   End
   Begin VB.PictureBox Picture1 
      Height          =   3855
      Left            =   240
      MousePointer    =   1  'Arrow
      ScaleHeight     =   253
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   389
      TabIndex        =   3
      Top             =   120
      Width           =   5895
   End
   Begin VB.CommandButton Attach 
      Caption         =   "&Attach"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4800
      TabIndex        =   2
      Top             =   4200
      Width           =   1335
   End
   Begin VB.TextBox FriendName 
      Height          =   285
      Left            =   1440
      TabIndex        =   1
      Top             =   4200
      Width           =   2055
   End
   Begin VB.Label Label1 
      Caption         =   "Remote &Friend:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   4200
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ------------------------------------------------------------------------
'               Copyright (C) 1995 Microsoft Corporation
'
' You have a royalty-free right to use, modify, reproduce and distribute
' the Sample Application Files (and/or any modified version) in any way
' you find useful, provided that you agree that Microsoft has no warranty,
' obligations or liability for any Sample Application Files.
' ------------------------------------------------------------------------
'
' Type Guid
'
Const guidDraw = "{151ceac0-acb5-11cf-8b51-0020af929546}"
Option Explicit
Const MaxNumLen = 7
Private Type Line
    X1 As Long
    Y1 As Long
    X2 As Long
    Y2 As Long
End Type

Dim lLastX As Long
Dim lLastY As Long
Dim Lines() As Line
Dim cLines As Integer
Dim lArraySize As Integer
Dim strScreenText As String
Dim fWasText As Integer
Dim strLogin As String
Dim q As MSMQQueue
Attribute q.VB_VarHelpID = -1
Dim WithEvents qevent As MSMQEvent
Attribute qevent.VB_VarHelpID = -1
Dim qFriend As MSMQQueue
Dim msgOut As MSMQMessage

'
'Locate a remote queue
'
Private Sub Attach_Click()
    Dim queryFriend As New MSMQQuery
    Dim qinfoFriend As MSMQQueueInfo
    Dim qinfos As MSMQQueueInfos
    FriendName = UCase(FriendName)
    Set qinfos = queryFriend.LookupQueue( _
        Label:=(FriendName), _
        ServiceTypeGuid:=guidDraw)
    qinfos.Reset
    Set qinfoFriend = qinfos.Next
    If qinfoFriend Is Nothing Then                   'And locate it
        MsgBox "No Such friend, Sorry..."   'No queue defined
    Else
        If Not qFriend Is Nothing Then
          If qFriend.IsOpen Then qFriend.Close
        End If

        Set qFriend = qinfoFriend.Open(MQ_SEND_ACCESS, 0)
        Caption = strLogin + " - Connected to " + FriendName
        Attach.Enabled = False
    End If
End Sub

'
' Application Initialization
'
Private Sub Form_Load()
    Dim strDefaultQueueName As String
    Dim lTempPointer As Long
    Dim query As New MSMQQuery
    Dim qinfo As MSMQQueueInfo
    Dim qinfos As MSMQQueueInfos
    Dim strComputerName As String
    
    Set msgOut = New MSMQMessage
    strDefaultQueueName = Environ("USERNAME")
    strLogin = InputBox("Your Name Please", "Login", strDefaultQueueName)
    If strLogin = "" Then End
    strLogin = UCase(strLogin)
    Caption = strLogin
    Set qinfos = query.LookupQueue( _
        Label:=strLogin, _
        ServiceTypeGuid:=guidDraw)
    qinfos.Reset             'And locate this queue
    Set qinfo = qinfos.Next
    If qinfo Is Nothing Then
        Set qinfo = New MSMQQueueInfo
        strComputerName = "."
        qinfo.PathName = strComputerName + "\" + strLogin
        qinfo.Label = strLogin
        qinfo.ServiceTypeGuid = guidDraw
        qinfo.Create                 'If there is no such create one.
    End If
    On Error GoTo retry_on_error
        lTempPointer = Screen.MousePointer
        Screen.MousePointer = 11 'ccArrowHourglass
        Set q = qinfo.Open(MQ_RECEIVE_ACCESS, 0)
        On Error GoTo 0
        Screen.MousePointer = lTempPointer
        GoTo all_ok
retry_on_error:
    '
    'We may still not see the queue until the next replication
    ' In this case, we get MQ_ERROR_QUEUE_NOT_FOUND and retry.
    '
    If Err.Number = MQ_ERROR_QUEUE_NOT_FOUND Then
        Err.Clear
        DoEvents
        Resume
    Else
        MsgBox Err.Description, , "Error in Open"
        End
    End If
    
all_ok:
    'All messages will be received asynchronously
    ' So need an event handler
    Set qevent = New MSMQEvent
    q.EnableNotification qevent
End Sub
'
'Gets points and returns a line
'
Private Function PointsToLine(ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Line
    Dim lineNew As Line
    lineNew.X1 = X1
    lineNew.Y1 = Y1
    lineNew.X2 = X2
    lineNew.Y2 = Y2
    PointsToLine = lineNew
End Function
'
'Draw a line in the picture control
'
Private Sub DrawLine(lineDraw As Line)
    Picture1.Line (lineDraw.X1, lineDraw.Y1)-(lineDraw.X2, lineDraw.Y2)
    fWasText = False
End Sub
'
'Display a line
'
Private Sub AddLine(lineNew As Line)
    DrawLine lineNew
    cLines = cLines + 1
    If (cLines > lArraySize) Then
        lArraySize = cLines * 2
        ReDim Preserve Lines(lArraySize)
    End If
    Lines(cLines - 1) = lineNew
End Sub
'
'Clear the display
'
Private Sub ClearDraw()
    cLines = 0
    strScreenText = ""
    Picture1.Refresh
End Sub
'
'Decode a string into a line
'
Private Function LineToString(lineIn As Line) As String
    Dim strFormat As String
    strFormat = String(MaxNumLen, "0")
    LineToString = Format$(lineIn.X1, strFormat) + Format$(lineIn.Y1, strFormat) + Format$(lineIn.X2, strFormat) + Format$(lineIn.Y2, strFormat)
End Function
'
'Encode a line into a string
'
Private Function StringToLine(strIn As String) As Line
    Dim lineOut As Line
    lineOut.X1 = Val(Mid$(strIn, 1, MaxNumLen))
    lineOut.Y1 = Val(Mid$(strIn, MaxNumLen + 1, MaxNumLen))
    lineOut.X2 = Val(Mid$(strIn, MaxNumLen * 2 + 1, MaxNumLen))
    lineOut.Y2 = Val(Mid$(strIn, MaxNumLen * 3 + 1, MaxNumLen))
    StringToLine = lineOut
End Function

Private Sub Form_Unload(Cancel As Integer)
    If Not q Is Nothing Then
        q.Close
    End If
    If Not qFriend Is Nothing Then qFriend.Close
    
End Sub



Private Sub FriendName_Change()
        Attach.Enabled = True
End Sub


'
'Message Receive event
'
Private Sub qevent_Arrived(ByVal q As Object, ByVal lCursor As Long)
    Dim msgIn As MSMQMessage
    Dim lineNew As Line
    Dim strTextIn As String
    
    On Error GoTo ErrorHandler
    Set msgIn = q.Receive(ReceiveTimeout:=100)
    If Not msgIn Is Nothing Then
        strTextIn = msgIn.Body          'Read the body of the message
        If Len(strTextIn) = 1 Then         'If 1 byte long
            TypeChar strTextIn             'it is a character - so display it
        Else
            lineNew = StringToLine(msgIn.Body)   'Otherwise it is a line
            AddLine lineNew                         'so draw it
        End If
    End If
ErrorHandler:
    ' reenable event firing
    q.EnableNotification qevent
End Sub




Private Sub qevent_ArrivedError(ByVal pdispQueue As Object, ByVal lErrorCode As Long, ByVal lCursor As Long)
    MsgBox Hex$(lErrorCode), , "Receive Error!"
    q.EnableNotification qevent
End Sub

Private Sub Option1_Click(Index As Integer)
    msgOut.Delivery = Index
End Sub


'
'Key press event
'
Private Sub Picture1_KeyPress(KeyAscii As Integer)
    TypeChar (Chr(KeyAscii))                'Display the character
    If Not qFriend Is Nothing Then
        If qFriend.IsOpen Then
            msgOut.Priority = 4                 'Set the priority to 4 (high)
            msgOut.Body = Chr(KeyAscii)         'Fill the body with the character
            msgOut.Label = "Key: " + msgOut.Body
            msgOut.Send qFriend                 'And send the message
        End If
    End If
End Sub
'
'Display a character
'(Handles backspace)
'
Private Sub TypeChar(Key As String)
    If Asc(Key) = 8 Then 'BackSpace
        If strScreenText <> "" Then
            strScreenText = Left$(strScreenText, Len(strScreenText) - 1)
            Picture1.Refresh
        End If
    Else
        strScreenText = strScreenText + Key
        If fWasText Then
            Picture1.Print Key;
        Else
            Picture1.Refresh
        End If
    End If
End Sub
'
'Mouse Down Event
'
Private Sub Picture1_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = 1 Then      'Remember the
        lLastX = X           'Mouse location
        lLastY = Y
    End If
End Sub
'
'Mouse Move Event
'
Private Sub Picture1_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = 1 And X > 0 And Y > 0 Then          'Something to draw?
        Dim lineNew As Line
        lineNew = PointsToLine(lLastX, lLastY, X, Y)  'Get a new line
        AddLine lineNew                             'And display it
        If Not qFriend Is Nothing Then
            If qFriend.IsOpen Then
                msgOut.Priority = 3                     'Set the priority to 3 (low)
                msgOut.Body = LineToString(lineNew)     'Fill the body with the line
                msgOut.Label = Str(lLastX) + "," + Str(lLastY) + " To " + Str(X) + "," + Str(Y)
                msgOut.Send qFriend                     'And send the message
            End If
        End If
        lLastX = X
        lLastY = Y
    End If
End Sub
'
'2nd button click == Clear the display
'
Private Sub Picture1_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = 2 Then ClearDraw
End Sub
'
'Repaint the display event
'
Private Sub Picture1_Paint()
    Dim I As Integer
    For I = 0 To cLines - 1
        DrawLine Lines(I)
    Next
    Picture1.CurrentX = 0
    Picture1.CurrentY = 0
    Picture1.Print strScreenText;
    fWasText = True
End Sub
