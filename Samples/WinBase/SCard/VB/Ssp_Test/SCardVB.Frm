VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.1#0"; "RICHTX32.OCX"
Begin VB.Form FrmSCardVB
   BorderStyle     =   1  'Fixed Single
   Caption         =   "SSP/Smart Card Test"
   ClientHeight    =   3945
   ClientLeft      =   3765
   ClientTop       =   3615
   ClientWidth     =   8625
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3945
   ScaleWidth      =   8625
   Begin VB.TextBox ReaderName
      Height          =   285
      Left            =   3720
      TabIndex        =   8
      Text            =   "Bull CP8 Transac 0"
      Top             =   240
      Width           =   2775
   End
   Begin VB.CheckBox SaveToFile
      Caption         =   "Save results to file"
      Height          =   255
      Left            =   6840
      TabIndex        =   6
      Top             =   240
      Width           =   1695
   End
   Begin TabDlg.SSTab Tabs
      Height          =   3135
      Left            =   120
      TabIndex        =   3
      Top             =   720
      Width           =   7095
      _ExtentX        =   12515
      _ExtentY        =   5530
      _Version        =   327681
      Tabs            =   2
      TabHeight       =   520
      TabCaption(0)   =   "Test Step"
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Test_Step"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Test Output"
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Test_Output"
      Tab(1).ControlCount=   1
      Begin RichTextLib.RichTextBox Test_Step
         Height          =   2535
         Left            =   120
         TabIndex        =   5
         Top             =   480
         Width           =   6855
         _ExtentX        =   12091
         _ExtentY        =   4471
         _Version        =   327681
         Enabled         =   -1  'True
         ScrollBars      =   2
         TextRTF         =   $"scardvb.frx":0000
      End
      Begin RichTextLib.RichTextBox Test_Output
         Height          =   2535
         Left            =   -74880
         TabIndex        =   4
         Top             =   480
         Width           =   6855
         _ExtentX        =   12091
         _ExtentY        =   4471
         _Version        =   327681
         Enabled         =   -1  'True
         ScrollBars      =   2
         TextRTF         =   $"scardvb.frx":0090
      End
   End
   Begin VB.TextBox Iterations
      Alignment       =   1  'Right Justify
      Height          =   285
      Left            =   1680
      MaxLength       =   3
      TabIndex        =   2
      Text            =   "1"
      Top             =   240
      Width           =   495
   End
   Begin VB.CommandButton CallSSP
      Caption         =   "Run Test!"
      Height          =   495
      Left            =   7440
      TabIndex        =   0
      Top             =   3240
      Width           =   1095
   End
   Begin VB.Label Label2
      Alignment       =   1  'Right Justify
      Caption         =   "Reader Name:"
      Height          =   255
      Left            =   2520
      TabIndex        =   7
      Top             =   240
      Width           =   1095
   End
   Begin VB.Label Label1
      Caption         =   "Number of iterations:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   1455
   End
End
Attribute VB_Name = "FrmSCardVB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
'ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
'TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'PARTICULAR PURPOSE.
'
'Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
'
' Module name:
'   SCardVB
'
' Abstract
'   This project is a simple example of how to use Visual Basic 5
'   with the smartcard low-level SSPs
'
'
' Notes:
'
'   1. The SCardDat, SCardMgr and SCardSrv type libraries must be referenced within this
'   project. (Use Project/References...)
'
'   2. This project expects a data file to be available on the card (ID: 3F05)
'   of type transparent EF, of size 120 bytes minimum
'
'   3. This is simply a brute force approach to show how VB can call the low-level
'   SSPs

'
' Set up variables for each Object
'
' Or, since the type library is referenced in this project use:
' Dim ISCardAuth as New CSCardAuth
'
Dim ISCardCmd As New CSCardCmd
Dim ISCardISO7816 As New CSCardISO7816
Dim ISCard As New CSCard

Private Sub CallSSP_Click()
On Error GoTo ErrorHandler
    '
    ' Catch the click and do something...
    '
    Dim lIterations As Long
    Dim lLength As Long
    Dim rgDataWritten(1) As Long
    Dim rgDataRead(1) As Long
    Dim TempBuffer(250) As Byte
    Dim Pattern_1(120) As Byte
    Dim Pattern_2(120) As Byte
    Dim bySW1, bySW2 As Byte
    Dim FileName As New ByteBuffer
    Dim Patterns As New ByteBuffer
    Dim Apdu As IByteBuffer
    Dim ApduReply As IByteBuffer
    Dim sDisplay As String
    Dim sDisplayStep As String
    Dim Reader As String

    ' Initialize Patterns
    For i = 0 To 14
        ' Pattern 1
        Pattern_1(i * 8 + 0) = 1: Pattern_1(i * 8 + 1) = 2
        Pattern_1(i * 8 + 2) = 3: Pattern_1(i * 8 + 3) = 4
        Pattern_1(i * 8 + 4) = 5: Pattern_1(i * 8 + 5) = 6
        Pattern_1(i * 8 + 6) = 7: Pattern_1(i * 8 + 7) = 8
        ' Pattern 2
        Pattern_2(i * 8 + 0) = 3: Pattern_2(i * 8 + 1) = 5
        Pattern_2(i * 8 + 2) = 3: Pattern_2(i * 8 + 3) = 5
        Pattern_2(i * 8 + 4) = 3: Pattern_2(i * 8 + 5) = 5
        Pattern_2(i * 8 + 6) = 3: Pattern_2(i * 8 + 7) = 5
    Next i

    ' Set readername
    Reader = ReaderName.Text

    ' Get number of iterations
    lIterations = Iterations.Text

    ' Attach to a card
    ISCard.AttachByReader Reader, Exclusive, T0

    ' Lock for transactions
    Call ISCard.LockSCard

    Call ISCardISO7816.SetDefaultClassId(192)

    Test_Output.Text = ""
    Test_Step.Text = ""

    For iter = 1 To lIterations
        ' Display Step
        Test_Output.Text = Test_Output.Text + "Iteration:" + CStr(iter) + Chr(10)
        Test_Step.Text = Test_Step.Text + "Iteration:" + CStr(iter) + Chr(10)

        ' Build Select MF Command
        TempBuffer(0) = 63: TempBuffer(1) = 0
        Call FileName.Initialize(2)
        Call FileName.Seek(0, 0)
        Call FileName.Write(TempBuffer(0), 2, rgDataWritten(0))
        Call ISCardISO7816.SelectFile(0, 0, FileName, 0, ISCardCmd)

        ' Select the MF
        Call ISCard.Transaction(ISCardCmd)
        bySW1 = ISCardCmd.ReplyStatusSW1
        bySW2 = ISCardCmd.ReplyStatusSW2
        sDisplayStep = Chr(10) + "SelectFile 3F00"

        ' Build Select Data file
        TempBuffer(0) = 63: TempBuffer(1) = 5
        Call FileName.Seek(0, 0)
        Call FileName.Write(TempBuffer(0), 2, rgDataWritten(0))
        Call ISCardISO7816.SelectFile(0, 0, FileName, 0, ISCardCmd)

        ' Select the Data file
        Call ISCard.Transaction(ISCardCmd)
        bySW1 = ISCardCmd.ReplyStatusSW1
        bySW2 = ISCardCmd.ReplyStatusSW2
        sDisplayStep = sDisplayStep + Chr(10) + "SelectFile 3F05"

        ' Write Data to file
        For i = 0 To 119
            TempBuffer(i) = Pattern_1(i)
        Next i

        Call Patterns.Initialize(120)
        Call Patterns.Seek(0, 0)
        Call Patterns.Write(TempBuffer(0), 120, rgDataWritten(0))
        Call ISCardISO7816.UpdateBinary(0, 0, Patterns, ISCardCmd)

        ' Write Data
        Call ISCard.Transaction(ISCardCmd)
        bySW1 = ISCardCmd.ReplyStatusSW1
        bySW2 = ISCardCmd.ReplyStatusSW2
        sDisplayStep = sDisplayStep + Chr(10) + "UpdateBinary Pattern 1"

        ' Read Pattern back
        Call ISCardISO7816.ReadBinary(0, 0, 120, ISCardCmd)

        ' Read Data
        Call ISCard.Transaction(ISCardCmd)
        bySW1 = ISCardCmd.ReplyStatusSW1
        bySW2 = ISCardCmd.ReplyStatusSW2
        sDisplayStep = sDisplayStep + Chr(10) + "ReadBinary Pattern 1"

        lLength = ISCardCmd.ApduReplyLength
        Set ApduReply = ISCardCmd.ApduReply

        Call ApduReply.Read(TempBuffer(0), lLength, rgDataRead(0))
        sText = Chr(10) + "Pattern 1:" + Chr(10)
        For i = 0 To lLength / 16
            sDisplay = CStr(TempBuffer(i * 8 + 0)) + " " + CStr(TempBuffer(i * 8 + 1)) + " " + CStr(TempBuffer(i * 8 + 2)) + " " + CStr(TempBuffer(i * 8 + 3)) + " " + CStr(TempBuffer(i * 8 + 4)) + " " + CStr(TempBuffer(i * 8 + 5)) + " " + CStr(TempBuffer(i * 8 + 6)) + " " + CStr(TempBuffer(i * 8 + 7)) + " "
            sdisplay2 = CStr(TempBuffer(i * 8 + 8)) + " " + CStr(TempBuffer(i * 8 + 9)) + " " + CStr(TempBuffer(i * 8 + 10)) + " " + CStr(TempBuffer(i * 8 + 11)) + " " + CStr(TempBuffer(i * 8 + 12)) + " " + CStr(TempBuffer(i * 8 + 13)) + " " + CStr(TempBuffer(i * 8 + 14)) + " " + CStr(TempBuffer(i * 8 + 15)) + " "
            sText = sText + sDisplay + sdisplay2 + Chr(10)
        Next i

        ' Write Data to file
        For i = 0 To 119
            TempBuffer(i) = Pattern_2(i)
        Next i

        Call Patterns.Seek(0, 0)
        Call Patterns.Write(TempBuffer(0), 120, rgDataWritten(0))
        Call ISCardISO7816.UpdateBinary(0, 0, Patterns, ISCardCmd)

        ' Write Data
        Call ISCard.Transaction(ISCardCmd)
        bySW1 = ISCardCmd.ReplyStatusSW1
        bySW2 = ISCardCmd.ReplyStatusSW2
        sDisplayStep = sDisplayStep + Chr(10) + "UpdateBinary Pattern 2"

        ' Read Pattern back
        Call ISCardISO7816.ReadBinary(0, 0, 120, ISCardCmd)

        ' Read Data
        Call ISCard.Transaction(ISCardCmd)
        bySW1 = ISCardCmd.ReplyStatusSW1
        bySW2 = ISCardCmd.ReplyStatusSW2
        sDisplayStep = sDisplayStep + Chr(10) + "ReadBinary Pattern 2" + Chr(10)

        lLength = ISCardCmd.ApduReplyLength
        Set ApduReply = ISCardCmd.ApduReply

        ' Build buffer for text display
        Call ApduReply.Read(TempBuffer(0), lLength, rgDataRead(0))
        sText = sText + Chr(10) + "Pattern 2:" + Chr(10)
        For i = 0 To lLength / 16
            sDisplay = CStr(TempBuffer(i * 8 + 0)) + " " + CStr(TempBuffer(i * 8 + 1)) + " " + CStr(TempBuffer(i * 8 + 2)) + " " + CStr(TempBuffer(i * 8 + 3)) + " " + CStr(TempBuffer(i * 8 + 4)) + " " + CStr(TempBuffer(i * 8 + 5)) + " " + CStr(TempBuffer(i * 8 + 6)) + " " + CStr(TempBuffer(i * 8 + 7)) + " "
            sdisplay2 = CStr(TempBuffer(i * 8 + 8)) + " " + CStr(TempBuffer(i * 8 + 9)) + " " + CStr(TempBuffer(i * 8 + 10)) + " " + CStr(TempBuffer(i * 8 + 11)) + " " + CStr(TempBuffer(i * 8 + 12)) + " " + CStr(TempBuffer(i * 8 + 13)) + " " + CStr(TempBuffer(i * 8 + 14)) + " " + CStr(TempBuffer(i * 8 + 15)) + " "
            sText = sText + sDisplay + sdisplay2 + Chr(10)
        Next i

        Test_Output.Text = Test_Output.Text + sText + Chr(10)
        Test_Step.Text = Test_Step.Text + sDisplayStep + Chr(10)

    Next iter

    ' Unlock
    Call ISCard.UnlockSCard(LEAVE)

    ' Detach from card
    ISCard.Detach (1)

    '
    ' Unload the objects
    '
    Set ISCard = Nothing
    Set ISCardISO7816 = Nothing
    Set ISCardCmd = Nothing

    ' Leave
    Exit Sub

ErrorHandler:
    '
    ' Unload the objects
    '
    Set ISCard = Nothing
    Set ISCardISO7816 = Nothing
    Set ISCardCmd = Nothing

    MsgBox "An error occured!"

End Sub

Private Sub Form_Load()
On Error GoTo ErrorHandler
    '
    ' Center the dialog
    '
    Left = (Screen.Width - Width) / 2
    Top = (Screen.Height - Height) / 2

    Test_Output.Text = ""
    Test_Step.Text = ""

    ' Leave
    Exit Sub

ErrorHandler:
    ' Todo: Add error handling code

End Sub


Private Sub Form_Terminate()
On Error GoTo ErrorHandler
    '
    ' Unload the objects
    '
    Set ISCard = Nothing
    Set ISCardTypeConv = Nothing
    Set ISCardCmd = Nothing

    ' Clear text boxes
    Test_Output.Text = " "
    Test_Step.Text = " "

    ' Leave
    Exit Sub

ErrorHandler:
    ' Todo: Add error handling code

End Sub

Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrorHandler
    '
    ' Unload the objects
    '
    Set ISCard = Nothing
    Set ISCardTypeConv = Nothing
    Set ISCardCmd = Nothing

    ' Save data if needed
    If SaveToFile.Value = 1 Then
        Call Test_Output.SaveFile("SSPTestDat_1.rtf", 0)
        Call Test_Step.SaveFile("SSPTestDat_2.rtf", 0)
    End If

    ' Leave
    Exit Sub

ErrorHandler:
    ' Todo: Add error handling code

End Sub


