VERSION 5.00
Begin VB.Form NewAgentType 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "New Agent"
   ClientHeight    =   3795
   ClientLeft      =   5685
   ClientTop       =   2760
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3795
   ScaleWidth      =   4680
   Begin VB.CommandButton btnAction 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   435
      Index           =   0
      Left            =   3060
      TabIndex        =   7
      Top             =   3300
      Width           =   1575
   End
   Begin VB.CommandButton btnAction 
      Caption         =   "OK"
      Height          =   435
      Index           =   1
      Left            =   60
      TabIndex        =   6
      Top             =   3300
      Width           =   1575
   End
   Begin VB.Frame Frame1 
      Caption         =   "New Agent Properties"
      Height          =   3135
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   4575
      Begin VB.OptionButton Option1 
         Caption         =   "&Routing"
         Height          =   315
         Index           =   1
         Left            =   240
         TabIndex        =   5
         Top             =   2580
         Width           =   3435
      End
      Begin VB.OptionButton Option1 
         Caption         =   "&Script Handler"
         Height          =   315
         Index           =   0
         Left            =   240
         TabIndex        =   4
         Top             =   2160
         Value           =   -1  'True
         Width           =   3435
      End
      Begin VB.TextBox txtAgentName 
         Height          =   315
         Left            =   240
         TabIndex        =   2
         Text            =   "txtAgentName"
         Top             =   900
         Width           =   4035
      End
      Begin VB.Label Label2 
         Caption         =   "Specify Agent Type:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         Left            =   240
         TabIndex        =   3
         Top             =   1740
         Width           =   3015
      End
      Begin VB.Label Label1 
         Caption         =   "Specify Agent Name:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         Left            =   240
         TabIndex        =   1
         Top             =   540
         Width           =   3015
      End
   End
End
Attribute VB_Name = "NewAgentType"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'
'  NEW AGENT TYPE
'
'  Overview: This simple form is used to select the type for the new agent.
'  It also loads the default script to be used which is stored in the
'  resource file. There are 2 default scripts, one for the standard
'  Event Service Agent and one for the Routing Agent.
'***********************************************************************

Private Const OPT_SCRIPTHANDLER = 0
Private Const OPT_ROUTING = 1
Private Const BTN_OK = 0

'--------------------------------------------
'  Sub: BTN ACTION CLICK
'
'  Action: Processes Click Events for the
'  New Agent Type Action Buttons (ok and cancel)
'--------------------------------------------
Private Sub btnAction_Click(Index As Integer)
   
With AEClass
   If Index = BTN_OK Then
      'Cancel Form
      .Cancelled = True
      NewAgentType.Hide
   Else

      .Cancelled = False
      If Option1.item(OPT_SCRIPTHANDLER).Value Then
         .AgentMode = MODE_SCRIPT_AGENT
         .AgentClassID = SCRIPT_HANDLER_CLASS_ID
         If Len(txtAgentName) = 0 Then
            txtAgentName = "New Agent"
            .AgentName = "New Agent"
         End If
         Call DirtyStatusUpdate(DIRTY_AGENT Or DIRTY_SCRIPT, DIRTY_ADD)
         AEditorUI.RETextBox.Text = StrConv(LoadResData(EVENT_SCRIPT_RESOURCE_NUMBER, "Text"), vbUnicode)
         AEditorUI.MainTabs.TabEnabled(TAB_SCRIPT) = True
         AEditorUI.MainTabs.TabEnabled(TAB_MAP) = False
         AEditorUI.MainTabs.TabEnabled(TAB_AGENT) = True
      Else
         Call DirtyStatusUpdate(DIRTY_AGENT Or DIRTY_SCRIPT Or DIRTY_MAP, DIRTY_ADD)
         .AgentMode = MODE_ROUTE_AGENT
         .AgentClassID = ROUTING_CLASS_ID
         .AgentName = "Routing Agent"
         txtAgentName = "Routing Agent"
         AEditorUI.MainTabs.TabEnabled(TAB_SCRIPT) = True
         AEditorUI.MainTabs.TabEnabled(TAB_MAP) = True
         AEditorUI.MainTabs.TabEnabled(TAB_AGENT) = True
         AEditorUI.RETextBox.Text = StrConv(LoadResData(ROUTING_SCRIPT_RESOURCE_NUMBER, "Text"), vbUnicode)
      End If
      .AgentName = txtAgentName
      NewAgentType.Hide
   End If
End With

End Sub

'-------------------------------------------------
'  Sub: FORM ACTIVATE
'
'  Action: Set up defaults every time the form
'  is activated. (It is never closed, only hidden).
'-------------------------------------------------

Private Sub Form_Activate()
   txtAgentName.Enabled = True
   txtAgentName = "New Agent"
   Option1(0).Value = vbChecked
   If AEClass.RouteAgentExists Then
      Option1(1).Enabled = False
   Else
      Option1(1).Enabled = True
   End If
End Sub

'--------------------------------------------
'  Sub: OPTION1 CLICK
'
'  Action: Processes Click Events for the
'  option buttons (scripthandler or routing)
'--------------------------------------------
Private Sub Option1_Click(Index As Integer)
   If Index = OPT_ROUTING Then
      txtAgentName = "Routing Agent"
      txtAgentName.Enabled = False
   Else
      txtAgentName = "New Agent"
      txtAgentName.Enabled = True
   End If
End Sub
