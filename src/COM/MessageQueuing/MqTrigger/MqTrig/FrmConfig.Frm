VERSION 5.00
Begin VB.Form frmConfig 
   Caption         =   "Trigger Configuration"
   ClientHeight    =   1305
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5520
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   1305
   ScaleWidth      =   5520
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   2760
      TabIndex        =   2
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Set"
      Height          =   495
      Left            =   4200
      TabIndex        =   3
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox txtThreshold 
      Height          =   375
      Left            =   960
      TabIndex        =   1
      Top             =   720
      Width           =   615
   End
   Begin VB.TextBox txtQueueName 
      Height          =   375
      Left            =   960
      TabIndex        =   0
      Top             =   120
      Width           =   4455
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Threshold:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   840
      Width           =   735
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Local Queue:"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   735
   End
End
Attribute VB_Name = "frmConfig"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdCancel_Click()
    bContinue = False
    Unload Me
End Sub

Private Sub cmdClose_Click()
    'Save new values to the registry
    SaveSetting "MQTrigger", "Settings", "Threshold", txtThreshold
    SaveSetting "MQTrigger", "Settings", "QueueName", txtQueueName
    Unload Me
End Sub

Private Sub Form_Load()
    'Retrieve initial values from the registry
    txtThreshold = GetSetting("MQTrigger", "Settings", "Threshold")
    txtQueueName = GetSetting("MQTrigger", "Settings", "QueueName")
End Sub


