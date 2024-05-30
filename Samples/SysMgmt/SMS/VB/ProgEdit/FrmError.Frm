VERSION 5.00
Begin VB.Form frmError 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   4230
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4455
   Icon            =   "frmError.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4230
   ScaleWidth      =   4455
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.ComboBox cboReason 
      Height          =   315
      ItemData        =   "frmError.frx":014A
      Left            =   1380
      List            =   "frmError.frx":0190
      Style           =   2  'Dropdown List
      TabIndex        =   16
      Top             =   1680
      Width           =   2955
   End
   Begin VB.TextBox txtParameter 
      Height          =   285
      Left            =   1380
      TabIndex        =   14
      Top             =   2580
      Width           =   2955
   End
   Begin VB.TextBox txtErrorCode 
      Height          =   285
      Left            =   1380
      TabIndex        =   1
      Top             =   120
      Width           =   2955
   End
   Begin VB.TextBox txtDescription 
      Height          =   795
      Left            =   1380
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   12
      Top             =   2940
      Width           =   2955
   End
   Begin VB.TextBox txtOperation 
      Height          =   285
      Left            =   1380
      TabIndex        =   9
      Top             =   2220
      Width           =   2955
   End
   Begin VB.ComboBox cboObject 
      Height          =   315
      ItemData        =   "frmError.frx":02E3
      Left            =   1380
      List            =   "frmError.frx":031D
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   1320
      Width           =   2970
   End
   Begin VB.ComboBox cboAction 
      Height          =   315
      ItemData        =   "frmError.frx":03C6
      Left            =   1380
      List            =   "frmError.frx":03E8
      Style           =   2  'Dropdown List
      TabIndex        =   5
      Top             =   960
      Width           =   2970
   End
   Begin VB.ComboBox cboFacility 
      Height          =   315
      ItemData        =   "frmError.frx":0461
      Left            =   1380
      List            =   "frmError.frx":0486
      Style           =   2  'Dropdown List
      TabIndex        =   3
      Top             =   600
      Width           =   2970
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Default         =   -1  'True
      Height          =   315
      Left            =   1620
      TabIndex        =   13
      Top             =   3840
      Width           =   1035
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Reason:"
      Height          =   195
      Index           =   8
      Left            =   120
      TabIndex        =   15
      Top             =   1740
      Width           =   600
   End
   Begin VB.Line Line2 
      X1              =   60
      X2              =   4380
      Y1              =   2100
      Y2              =   2100
   End
   Begin VB.Line Line1 
      X1              =   60
      X2              =   4380
      Y1              =   480
      Y2              =   480
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Description:"
      Height          =   195
      Index           =   7
      Left            =   120
      TabIndex        =   11
      Top             =   3000
      Width           =   840
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Parameter Info:"
      Height          =   195
      Index           =   6
      Left            =   120
      TabIndex        =   10
      Top             =   2640
      Width           =   1080
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Operation:"
      Height          =   195
      Index           =   5
      Left            =   120
      TabIndex        =   8
      Top             =   2280
      Width           =   735
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Object:"
      Height          =   195
      Index           =   4
      Left            =   120
      TabIndex        =   6
      Top             =   1380
      Width           =   510
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "SMS Error Code:"
      Height          =   195
      Index           =   3
      Left            =   120
      TabIndex        =   0
      Top             =   180
      Width           =   1185
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Action:"
      Height          =   195
      Index           =   2
      Left            =   120
      TabIndex        =   4
      Top             =   1020
      Width           =   495
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      Caption         =   "Facility:"
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   2
      Top             =   660
      Width           =   525
   End
End
Attribute VB_Name = "frmError"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
' frmError.frm
'
'This form decodes sms_extendedstatus classes and displays them.
'When an error occurs, the user is presented the option of viewing this form.
'
'************************************************************
Option Explicit

' Close button pressed
Private Sub cmdClose_Click()

    'Unload the form
    Unload Me

End Sub

'Get SWbemLastError and decode it
Private Sub Form_Load()
    
    'Enable error trapping.
    On Error Resume Next
    
    'Get the lastest instance of SWbemLastError
    Dim ExtendedStatus As New SWbemLastError
    
    'If getting the lastest SWbemLastError instance failed, then
    'we report the there is no extended error status available
    If Err.Number <> 0 Then
        Me.Caption = "No Extended Error Status Available"
        txtDescription.Text = Err.Description
    Else
        'Make sure some sort of error object was returned
        If ExtendedStatus Is Nothing Then Stop
        
        'Handle "standard wbem error"
        If ExtendedStatus.Path_.Class = "__ExtendedStatus" Then
            Me.Caption = "Basic Extended Status"
            txtErrorCode.Text = "N/A - WBEM Error"
            txtOperation.Text = ExtendedStatus.Operation
            txtParameter.Text = ExtendedStatus.ParameterInfo
            txtDescription.Text = ExtendedStatus.Description
        'Handle SMS-Specific error
        ElseIf ExtendedStatus.Path_.Class = "SMS_ExtendedStatus" Then
            Me.Caption = "SMS Extended Error Status"
            txtErrorCode.Text = Hex(ExtendedStatus.Errorcode)
            cboReason.ListIndex = Val(ExtendedStatus.Errorcode) And 255
            cboObject.ListIndex = (Val(ExtendedStatus.Errorcode) And 65280) / 256
            cboAction.ListIndex = (Val(ExtendedStatus.Errorcode) And 4128768) / 65536
            cboFacility.ListIndex = (Val(ExtendedStatus.Errorcode) And 264241152) / 4194304
            txtOperation.Text = ExtendedStatus.Operation
            txtParameter.Text = ExtendedStatus.ParameterInfo
            txtDescription.Text = ExtendedStatus.Description
        End If
    End If
    
    'Clear the error object
    Err.Clear
    
End Sub
