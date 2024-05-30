VERSION 5.00
Begin VB.Form AgentPicker 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Agents"
   ClientHeight    =   3690
   ClientLeft      =   5085
   ClientTop       =   3720
   ClientWidth     =   5460
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3690
   ScaleWidth      =   5460
   Begin VB.ListBox AgentListID 
      Height          =   645
      Left            =   3960
      TabIndex        =   6
      Top             =   2940
      Visible         =   0   'False
      Width           =   1335
   End
   Begin VB.CommandButton btnAction 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   3
      Left            =   3960
      TabIndex        =   5
      Top             =   2220
      Width           =   1335
   End
   Begin VB.CommandButton btnAction 
      Caption         =   "&New Agent"
      Enabled         =   0   'False
      Height          =   375
      Index           =   0
      Left            =   3960
      TabIndex        =   4
      Top             =   600
      Width           =   1395
   End
   Begin VB.CommandButton btnAction 
      Caption         =   "&Delete Agent"
      Enabled         =   0   'False
      Height          =   375
      Index           =   2
      Left            =   3960
      TabIndex        =   3
      Top             =   1560
      Width           =   1395
   End
   Begin VB.CommandButton btnAction 
      Caption         =   "&Edit Agent"
      Enabled         =   0   'False
      Height          =   375
      Index           =   1
      Left            =   3960
      TabIndex        =   2
      Top             =   1080
      Width           =   1395
   End
   Begin VB.ListBox AgentList 
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2985
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   3495
   End
   Begin VB.Label label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Agents available in this folder"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   240
      TabIndex        =   1
      Top             =   180
      Width           =   2955
   End
End
Attribute VB_Name = "AgentPicker"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'Button Constants
Private Const BTN_NEW_AGENT = 0
Private Const BTN_EDIT_AGENT = 1
Private Const BTN_DELETE_AGENT = 2
Private Const BTN_CANCEL = 3
Private Const BTN_CHANGE_ALL = 6

'----------------------------------------------------
'  Method: BUTTON UPDATE
'
'  Action: Enables or Disables Buttons on UI
'
'  Parm:  (int) ButtonKey - Index Number of button
'        (bool) bEnabled - Disabled or Enabled Button
'        (bool) bVisible = Button visible or invisible
'----------------------------------------------------
Private Sub ButtonUpdate(ByVal iButtonKey As Integer, ByVal bEnabled As Boolean, ByVal bVisible As Boolean)

Dim X As Integer

If iButtonKey = BTN_CHANGE_ALL Then
   For X = 0 To 2
      btnAction(X).Enabled = bEnabled
      btnAction(X).Visible = bVisible
   Next
Else
   btnAction(iButtonKey).Visible = bVisible
   btnAction(iButtonKey).Enabled = bEnabled
End If

End Sub


'-----------------------------------------------
'   Sub: UPDATE AGENT LIST
'
'   Action: Populate ListBoxes with Agent Names
'   and the respective entry id of the binding.
'-----------------------------------------------
Private Sub UpdateAgentList()

   Dim X As Integer           'Loop variable
   Dim b_IGNORE As Boolean    'boolean not used
   Dim bListPopulated         'boolean
   
   'Populate List Box and hidden list box which
   'has the entry id of the binding in it.
   AgentList.Clear
   AgentListID.Clear
   
   AEClass.RouteAgentExists = False
   bListPopulated = False
   
   If AgentMap.BindingCount > 0 Then
      For X = 1 To AgentMap.BindingCount
         b_IGNORE = AgentMap.GetBindingbyIndex(X)
         If AgentMap.BindingClassID = SCRIPT_HANDLER_CLASS_ID Or _
            AgentMap.BindingClassID = ROUTING_CLASS_ID Then
            'Flag if a routing agent already exists.
            If AgentMap.BindingClassID = ROUTING_CLASS_ID Then
               AEClass.RouteAgentExists = True
            End If
            bListPopulated = True
            AgentList.AddItem AgentMap.BindingName
            AgentListID.AddItem AgentMap.BindingEID
         End If
      Next
      
      If bListPopulated Then
         AgentList.ListIndex = 0
         AgentListID.ListIndex = 0
         Call ButtonUpdate(BTN_EDIT_AGENT, True, True)
         Call ButtonUpdate(BTN_DELETE_AGENT, True, True)
      Else
         Call ButtonUpdate(BTN_EDIT_AGENT, False, True)
         Call ButtonUpdate(BTN_DELETE_AGENT, False, True)
      End If
      
      Call ButtonUpdate(BTN_NEW_AGENT, True, True)
      
   Else
      'No agents available so don't allow delete or edit
      Call ButtonUpdate(BTN_NEW_AGENT, True, True)
      Call ButtonUpdate(BTN_EDIT_AGENT, False, True)
      Call ButtonUpdate(BTN_DELETE_AGENT, False, True)
   End If

End Sub

'----------------------------------------------------
'   Sub: AGENTLIST DBLCLICK
'
'   Action: If list count > 0 then edit the agent
'----------------------------------------------------
Private Sub AgentList_DblClick()
   If AgentList.ListCount <> 0 Then
      btnAction_Click (1) 'Auto Edit
   End If
End Sub


'----------------------------------------------
'  Sub: EDIT AGENT
'
'  Action: This subroutine gets the binding and
'  populates the UI with the proper values.
'----------------------------------------------
Private Sub EditAgent()

  Dim b_IGNORE As Boolean        'Boolean Not Used
  Dim X As Integer               'Loop Variable
  Dim sHandlerName As String     'Script Handler
  Dim iHC As Integer
  Dim iEventMask As Integer
  
  If AgentList.ListCount <> 0 Then
    
     With AEditorUI
         'Get the binding that was selected.
         b_IGNORE = AgentMap.GetBindingbyEID(AgentListID.List(AgentList.ListIndex))
         
         'Defaults to all false for AgentMap
         For X = 1 To 4
            .ChkEvent(X).Value = Unchecked
         Next X
         
         'Update ActiveFlag
         If AgentMap.ActiveStatus Then
            .ChkActive.Value = vbChecked
         Else
            .ChkActive.Value = vbUnchecked
         End If
         
         iEventMask = AgentMap.EventMask
         
         'Update EventMask with current script flags
         If iEventMask And BIT_EVENT_SCHEDULE Then
           .ChkEvent(EVENT_ON_SCHEDULE).Value = vbChecked
         End If
         
         If iEventMask And BIT_EVENT_NEWMSG Then
            .ChkEvent(EVENT_ON_NEW_MESSAGE).Value = vbChecked
         End If
         
         If iEventMask And BIT_EVENT_CHGMSG Then
            .ChkEvent(EVENT_ON_CHANGED_MESSAGE).Value = vbChecked
         End If
         
         If iEventMask And BIT_EVENT_DELMSG Then
            .ChkEvent(EVENT_ON_DELETE_MESSAGE).Value = vbChecked
         End If
         
         'Update readonly part of UI
         .txtAgentName = AgentMap.BindingName
         .lblHandlerName = AgentMap.BindingHandlerName
         .lblAgentName = AgentMap.BindingName
         .lblHostName = AgentMap.GetBoundHostName
          b_IGNORE = AgentMap.GetScript("AEScript.tmp")
         .RETextBox.LoadFile "AEScript.tmp", 1
         
         'Get the binding EID if the agent we are editing to check later during save.
         AEClass.BindingEID = AgentMap.BindingEID
      End With
   End If

End Sub

'--------------------------------------------
'  Sub: NEW AGENT
'
'  Action: Set up the defaults for a new agent
'  scripthandler or events agent and updates
'  the main UI.
'--------------------------------------------
Private Sub NewAgent()

  Dim bScripthandler As Boolean  'Scripthandler Agent Flag
  Dim b_IGNORE As Boolean            'Boolean Success
  Dim X As Integer               'Loop Variable
  
  If AEClass.AgentClassID = SCRIPT_HANDLER_CLASS_ID Then
     bScripthandler = True
  End If
  
  With AEditorUI
     
     'Default is Script Handler Class
     .ChkActive.Value = vbChecked
     .txtAgentName = AEClass.AgentName
     .lblAgentName = AEClass.AgentName
     
     
     .MainTabs.TabEnabled(TAB_SCRIPT) = True
     .MainTabs.TabEnabled(TAB_AGENT) = True
     .optMap(0).Value = True
     
     If bScripthandler Then
         .lblHandlerName = "ScriptHandler Class"
          AEditorUI.MainTabs.TabEnabled(TAB_MAP) = False
     Else
         .lblHandlerName = "Microsoft Routing Class"
     
         'Enable the map editing tab
         .MainTabs.TabEnabled(TAB_MAP) = True
         b_IGNORE = AgentMap.GetRoutingMsg
                  
         'Note: If a FAI Map doesn't exist it automatically
         'creates one with a blank map.
         b_IGNORE = AgentMap.GetMap("ROUTING")
         
         'Setup the main map grid
         Call PrepareGrid
         Call DisplayMap
     End If
     
     ' Currently there isn't a host assigned so we
     ' grab the first default one and display it.
     ' The first item always exists since it's the default.
     .lblHostName = AgentMap.GetHostName(1)

     'Start out with no checked values
     For X = 1 To 4
        If bScripthandler Then
           .ChkEvent(X).Value = vbUnchecked
        Else
           .ChkEvent(X).Value = vbChecked
        End If
     Next X
  End With
  
End Sub

'--------------------------------------------
'  Sub: BTN ACTION CLICK
'
'  Action: Processes Click Events for the
'  Agent Picker Action Buttons
'--------------------------------------------
Private Sub btnAction_Click(Index As Integer)

Dim b_IGNORE As Boolean           'Boolean Not used


Select Case Index

   Case BTN_NEW_AGENT
      AEClass.EditMode = MODE_NEW_AGENT
      
      NewAgentType.Show vbModal
      If AEClass.Cancelled Then
         Exit Sub
      Else
         Call TurnOnControls
      End If
      
      Call NewAgent
      Call ScriptEditingToggle(True)
      
      AEClass.Cancelled = False
      
      AgentPicker.Hide
      
      
   'EDIT AGENT SELECTION
   Case BTN_EDIT_AGENT
      AEClass.EditMode = MODE_EDIT_AGENT
      
      Call EditAgent
      Call ScriptEditingToggle(True)
      Call TurnOnControls
      
      With AEditorUI
            
         'Update Tab Control
         .MainTabs.TabEnabled(TAB_SCRIPT) = True
         .MainTabs.TabEnabled(TAB_AGENT) = True
      
         'Use the IsRouteAgent property to find
         'out if this is a routing agent.
         If AgentMap.IsRouteAgent Then
            .optMap(0).Value = True
            .MainTabs.TabEnabled(TAB_MAP) = True
            b_IGNORE = AgentMap.GetRoutingMsg
                  
            'Note: If a FAI Map doesn't exist one
            'is automatically created. We have no
            'way of knowing a map exists. It is
            'simply blank if we get it.
            b_IGNORE = AgentMap.GetMap("ROUTING")
            Call PrepareGrid
            Call DisplayMap
         Else
            .MainTabs.TabEnabled(TAB_MAP) = False
         End If
      
         AEClass.Cancelled = False
      
         'Set Dirty Status to none.
         Call DirtyStatusUpdate(DIRTY_NONE, DIRTY_REMOVE)
      
      End With
      
      AgentPicker.Hide
      
   Case BTN_DELETE_AGENT
      Call DeleteAgent
      
   Case BTN_CANCEL
      AgentPicker.Hide
      
End Select


End Sub

'---------------------------------------------------------
'  Sub: TURN ON CONTROLS
'
'  Action: Makes Select script and Rich Edit text box (for
'  editing script) visible.
'---------------------------------------------------------
Private Sub TurnOnControls()

If AEditorUI.btnSelectScript.Visible = False Then
   AEditorUI.btnSelectScript.Visible = True
End If

If AEditorUI.RETextBox.Visible = False Then
   AEditorUI.RETextBox.Visible = True
End If

End Sub
'---------------------------------------------------------
'  Sub: FORM ACTIVATE
'
'  Action: Update listbox whenever the form is activated.
'  Use this instead of load form since we hide the form
'  when we aren't using it.
'-------------------------------------------------
Private Sub Form_Activate()
    
    Call UpdateAgentList

    'Set cancel to true in case user closes window
    'unexpectantly
    AEClass.Cancelled = True
   
   
End Sub


'--------------------------------------
'   Sub: DELETE AGENT
'
'   Action: Delete Binding with associated
'   entry id and update buttons on UI.
'--------------------------------------
Private Sub DeleteAgent()

   If AgentList.ListCount <> 0 Then
      Dim vRes As Variant
      Dim b_OK As Boolean
      
      vRes = MsgBox("Do you want to delete the agent?", vbYesNo + vbQuestion, App.Title)
      If vRes = vbYes Then
         
         On Error Resume Next
         b_OK = AgentMap.Delete(AgentListID.List(AgentList.ListIndex))
         If b_OK Then
            MsgBox "Agent Deleted.", vbInformation, App.Title
         Else
            MsgBox "Unable to delete agent. Event permissions may no longer be valid.", vbExclamation, App.Title
            Err.Clear
         End If
         On Error GoTo 0
         
         Call UpdateAgentList   'Also update buttons
      End If
   End If
End Sub

