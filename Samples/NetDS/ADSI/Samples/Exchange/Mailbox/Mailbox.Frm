VERSION 5.00
Begin VB.Form MailboxFrm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Create Exchange Mailbox with ADSI"
   ClientHeight    =   4080
   ClientLeft      =   1560
   ClientTop       =   1845
   ClientWidth     =   9360
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4080
   ScaleWidth      =   9360
   Begin VB.Frame Frame2 
      Caption         =   "Mailbox Settings"
      Height          =   3735
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   5175
      Begin VB.TextBox txtUserName 
         Height          =   285
         Left            =   1560
         TabIndex        =   10
         Top             =   2040
         Width           =   3255
      End
      Begin VB.TextBox txtFirstName 
         Height          =   285
         Left            =   1560
         TabIndex        =   12
         Top             =   2400
         Width           =   3255
      End
      Begin VB.TextBox txtLastName 
         Height          =   285
         Left            =   1560
         TabIndex        =   14
         Top             =   2760
         Width           =   3255
      End
      Begin VB.TextBox txtEMailAddress 
         Height          =   285
         Left            =   1560
         TabIndex        =   16
         Text            =   "@ntmarst.com"
         Top             =   3120
         Width           =   3255
      End
      Begin VB.TextBox txtExchOrganization 
         Height          =   285
         Left            =   1560
         TabIndex        =   6
         Text            =   "NTMARST"
         Top             =   1080
         Width           =   3255
      End
      Begin VB.TextBox txtExchSite 
         Height          =   285
         Left            =   1560
         TabIndex        =   8
         Text            =   "MAIL"
         Top             =   1440
         Width           =   3255
      End
      Begin VB.TextBox txtExchServer 
         Height          =   285
         Left            =   1560
         TabIndex        =   4
         Text            =   "IRIS"
         Top             =   720
         Width           =   3255
      End
      Begin VB.TextBox txtNTServer 
         Height          =   285
         Left            =   1560
         TabIndex        =   2
         Text            =   "IRIS"
         Top             =   360
         Width           =   3255
      End
      Begin VB.Label Label2 
         Caption         =   "User/Mailbox ID"
         Height          =   255
         Left            =   240
         TabIndex        =   9
         Top             =   2040
         Width           =   1335
      End
      Begin VB.Label Label3 
         Caption         =   "First name"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   2400
         Width           =   1215
      End
      Begin VB.Label Label4 
         Caption         =   "Last name"
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   2760
         Width           =   1215
      End
      Begin VB.Label Label11 
         Caption         =   "E-mail Address"
         Height          =   255
         Left            =   240
         TabIndex        =   15
         Top             =   3120
         Width           =   1215
      End
      Begin VB.Label Label8 
         Caption         =   "Exchange Org"
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   1080
         Width           =   1215
      End
      Begin VB.Label Label9 
         Caption         =   "Exchange Site"
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   1440
         Width           =   1215
      End
      Begin VB.Label Label10 
         Caption         =   "Exchange Server"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   1335
      End
      Begin VB.Label Label5 
         Caption         =   "NT Server"
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Administrative Credentials"
      Height          =   1575
      Left            =   5640
      TabIndex        =   17
      Top             =   120
      Width           =   3495
      Begin VB.TextBox txtDomain 
         Height          =   285
         Left            =   1320
         TabIndex        =   21
         Text            =   "ARGUS"
         Top             =   720
         Width           =   1935
      End
      Begin VB.TextBox txtAdmin 
         Height          =   315
         Left            =   1320
         TabIndex        =   19
         Text            =   "Administrator"
         Top             =   360
         Width           =   1935
      End
      Begin VB.TextBox txtPassword 
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   1320
         PasswordChar    =   "*"
         TabIndex        =   23
         Top             =   1080
         Width           =   1935
      End
      Begin VB.Label Label1 
         Caption         =   "NT Domain :"
         Height          =   255
         Left            =   240
         TabIndex        =   20
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label13 
         Caption         =   "Administrator :"
         Height          =   255
         Left            =   240
         TabIndex        =   18
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Label14 
         Caption         =   "Password :"
         Height          =   255
         Left            =   240
         TabIndex        =   22
         Top             =   1080
         Width           =   975
      End
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   6000
      TabIndex        =   26
      Top             =   3480
      Width           =   2895
   End
   Begin VB.CommandButton cmdDeleteMailbox 
      Caption         =   "Delete Mailbox"
      Height          =   375
      Left            =   6000
      TabIndex        =   25
      Top             =   2640
      Width           =   2895
   End
   Begin VB.CommandButton cmdCreateMailbox 
      Caption         =   "Create Mailbox"
      Default         =   -1  'True
      Height          =   375
      Left            =   6000
      TabIndex        =   24
      Top             =   2040
      Width           =   2895
   End
End
Attribute VB_Name = "MailboxFrm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' ADSI Sample to create and delete Exchange 5.5 Mailboxes
''
'' Richard Ault, Jean-Philippe Balivet, Neil Wemple -- 1998
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Private Sub cmdCreateMailbox_Click()
    MailboxFrm.MousePointer = vbHourglass
    Call Create_NT_Account(txtDomain, txtAdmin, txtPassword, _
                           txtUserName, txtFirstName & txtLastName, _
                           txtNTServer)
    Call Create_Exchange_MailBox(False, txtNTServer, txtDomain, txtAdmin, _
                                 txtPassword, txtUserName, txtEMailAddress, _
                                 txtFirstName, txtLastName, txtExchServer, _
                                 txtExchSite, txtExchOrganization)
    MailboxFrm.MousePointer = vbDefault
End Sub

Private Sub cmdDeleteMailbox_Click()
    MailboxFrm.MousePointer = vbHourglass
    Call Delete_Exchange_Mailbox(False, txtDomain, txtAdmin, _
                                 txtPassword, txtUserName, txtExchServer, _
                                 txtExchSite, txtExchOrganization)
    Call Delete_NT_Account(txtDomain, txtAdmin, txtPassword, txtUserName)
    MailboxFrm.MousePointer = vbDefault
End Sub

Private Sub cmdExit_Click()
    End
End Sub


