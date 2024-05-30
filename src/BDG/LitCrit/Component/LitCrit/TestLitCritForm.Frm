VERSION 5.00
Begin VB.Form TestLitCritForm 
   Caption         =   "Form1"
   ClientHeight    =   2640
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4215
   LinkTopic       =   "Form1"
   ScaleHeight     =   2640
   ScaleWidth      =   4215
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtBibNo 
      Height          =   285
      Left            =   1200
      TabIndex        =   9
      Top             =   0
      Width           =   3015
   End
   Begin VB.TextBox txtBorrowerNo 
      Height          =   285
      Left            =   1200
      TabIndex        =   8
      Top             =   360
      Width           =   3015
   End
   Begin VB.TextBox txtTitle 
      Height          =   285
      Left            =   1200
      TabIndex        =   7
      Top             =   1080
      Width           =   3015
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "&Update"
      Height          =   495
      Left            =   2160
      TabIndex        =   6
      Top             =   2160
      Width           =   975
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Add"
      Height          =   495
      Left            =   0
      TabIndex        =   5
      Top             =   2160
      Width           =   975
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "&Delete"
      Height          =   495
      Left            =   1080
      TabIndex        =   4
      Top             =   2160
      Width           =   975
   End
   Begin VB.CommandButton cmdBorrowerInfo 
      Caption         =   "&Boro'er Info"
      Height          =   495
      Left            =   3240
      TabIndex        =   3
      Top             =   2160
      Width           =   975
   End
   Begin VB.TextBox txtCritiqueNo 
      Height          =   285
      Left            =   1200
      TabIndex        =   2
      Top             =   1440
      Width           =   3015
   End
   Begin VB.TextBox txtConnect 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Text            =   "DSN=FmLib;UID=sa;PWD=;DATABASE=FmLib"
      Top             =   1800
      Width           =   3015
   End
   Begin VB.TextBox txtobjectID 
      Height          =   285
      Left            =   1200
      TabIndex        =   0
      Top             =   720
      Width           =   3015
   End
   Begin VB.Label Label1 
      Caption         =   "Bib#"
      Height          =   255
      Left            =   0
      TabIndex        =   15
      Top             =   0
      Width           =   1095
   End
   Begin VB.Label Label2 
      Caption         =   "Borrower#"
      Height          =   255
      Left            =   0
      TabIndex        =   14
      Top             =   360
      Width           =   1095
   End
   Begin VB.Label Label3 
      Caption         =   "Critique Title"
      Height          =   255
      Left            =   0
      TabIndex        =   13
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Label Label4 
      Caption         =   "Critique#"
      Height          =   255
      Left            =   0
      TabIndex        =   12
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Label Label5 
      Caption         =   "Connect..."
      Height          =   255
      Left            =   0
      TabIndex        =   11
      Top             =   1800
      Width           =   1095
   End
   Begin VB.Label Label6 
      Caption         =   "objectID"
      Height          =   255
      Left            =   0
      TabIndex        =   10
      Top             =   720
      Width           =   1215
   End
End
Attribute VB_Name = "TestLitCritForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub cmdAdd_Click()
   Dim oCritique As Critique
   Dim CritiqueNo As Long
   
   Set oCritique = New Critique
   CritiqueNo = oCritique.AddRecord(CLng(txtBibNo), CLng(txtBorrowerNo), txtTitle, "abcd1234", 3, Date, False, "DSN=FmLib;UID=sa;PWD=;DATABASE=FmLib")
   MsgBox "Critique #" & CritiqueNo & " was added.", vbInformation
   txtCritiqueNo.Text = CritiqueNo
End Sub

Private Sub cmdDelete_Click()
   Dim oCritique As Critique
   Dim objectID As String
   
   Set oCritique = New Critique
   objectID = CStr(txtobjectID)
   oCritique.DeleteRecordByObjectID objectID, txtConnect
   MsgBox "Critique #" & objectID & " was deleted.", vbInformation
   txtCritiqueNo.Text = ""
   Exit Sub
   
ErrHandler:
   MsgBox "Failed to delete critique #" & objectID, vbCritical
End Sub

Private Sub cmdUpdate_Click()
   Dim oCritique As Critique
   Dim CritiqueNo As Long
   
   Set oCritique = New Critique
   CritiqueNo = CLng(txtCritiqueNo)
   oCritique.UpdateRecord CritiqueNo, "0000111", True, 3, txtTitle, Date, txtConnect
   MsgBox "Critique #" & CritiqueNo & " was Updated.", vbInformation
   txtCritiqueNo.Text = ""
End Sub

Private Sub cmdBorrowerInfo_Click()
   Dim oCritique As Critique
   Dim BorrowerNo As Long
   
   Set oCritique = New Critique
   BorrowerNo = oCritique.BorrowerInfo("/o=boue/ou=lab/cn=recipients/cn=brettz", "UELABDC04")
   MsgBox "Borrower # " & BorrowerNo & " is there in database", vbInformation
End Sub

