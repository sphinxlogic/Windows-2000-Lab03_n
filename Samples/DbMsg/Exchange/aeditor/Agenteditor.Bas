Attribute VB_Name = "AgentEditorModule"
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998

'  AGENT EDITOR MODULE
'
'  Overview: This is the Agent Editor Module that holds all the public routines
'  used by the different UI portions of the code.
'***********************************************************************

Public Const EVENT_ON_SCHEDULE = 1
Public Const EVENT_ON_NEW_MESSAGE = 2
Public Const EVENT_ON_CHANGED_MESSAGE = 3
Public Const EVENT_ON_DELETE_MESSAGE = 4

Public Const TAB_SCRIPT = 0
Public Const TAB_MAP = 1
Public Const TAB_AGENT = 2

Public Const MODE_NEW_AGENT = 1
Public Const MODE_EDIT_AGENT = 2
Public Const MODE_NEW_MAP = 3
Public Const MODE_EDIT_MAP = 4
Public Const MODE_AGENT = 5
Public Const MODE_MAP = 6
Public Const MODE_ROUTE_AGENT = 7
Public Const MODE_SCRIPT_AGENT = 8
Public Const MODE_EDIT_MAP_ONLY = 9

Public Const ROUTING_SCRIPT_RESOURCE_NUMBER = 7000
Public Const EVENT_SCRIPT_RESOURCE_NUMBER = 7001

Public Const DIRTY_NONE = 0
Public Const DIRTY_SCRIPT = 1
Public Const DIRTY_AGENT = 2
Public Const DIRTY_MAP = 4

Public Const DIRTY_ADD = False
Public Const DIRTY_REMOVE = True
Public Const DIRTY_IGNORE = False

Public Const MENU_AGENT_FOLDER_SELECT = 0
Public Const MENU_AGENT_SELECT = 1
Public Const MENU_AGENT_SAVE = 3
Public Const MENU_AGENT_EXIT = 5
Public Const MENU_EXIT_NO_SAVE = 6

Public Const MENU_CUT_SCRIPT = 0
Public Const MENU_COPY_SCRIPT = 1
Public Const MENU_PASTE_SCRIPT = 2
Public Const MENU_SELECTALL_SCRIPT = 3

Public Const MENU_INSERT_COL = 1
Public Const MENU_INSERT_ROW = 2
Public Const MENU_DEL_ROW = 3
Public Const MENU_DEL_COL = 4
Public Const MENU_CUT_CELL = 6
Public Const MENU_COPY_CELL = 7
Public Const MENU_PASTE_CELL = 8

Public Const BTN_MAP_CLEAR = 0
Public Const BTN_MAP_IMPORT = 1
Public Const BTN_MAP_EXPORT = 2

Public Const TOOLBAR_AGENT = 1
Public Const TOOLBAR_SAVE = 3
Public Const TOOLBAR_DEL_COL = 5
Public Const TOOLBAR_INSERT_COL = 6
Public Const TOOLBAR_DEL_ROW = 7
Public Const TOOLBAR_INSERT_ROW = 8
Public Const TOOLBAR_ALL = 15

'------------------------------------------------
'   Sub: SET DELETE ROW
'
'   Action: Set the delete row options off or on.
'   Only set the flag option to on if the map is
'   current selected. Otherwise it's default off.
'------------------------------------------------

Public Sub SetDeleteRow()

   If AEditorUI.MainTabs.Tab = TAB_MAP Then
      With AEditorUI
         If .grdData.Rows < 3 Then
            Call UpdateMenuToolbarItem("DEL ROW", False)
         Else
            Call UpdateMenuToolbarItem("DEL ROW", True)
         End If
      End With
   Else
      Call UpdateMenuToolbarItem("DEL ROW", False)
   End If
   
End Sub

'---------------------------------------------
'   Sub: UPDATE MENU TOOLBAR ITEM
'
'   Action: Set the toolbar and menu enabled
'   status for different options.
'
'   Parm: sItem is the name of the button
'         bEnabled is either True or False
'----------------------------------------------
Public Sub UpdateMenuToolbarItem(ByVal sItem As String, ByVal bEnabled As Boolean)
   
With AEditorUI
   Select Case sItem
      Case "DEL ROW"
         .mnuEditSub2.item(MENU_DEL_ROW).Enabled = bEnabled
         .MainToolbar.Buttons.item(TOOLBAR_DEL_ROW).Enabled = bEnabled
      Case "DEL COL"
         .mnuEditSub2.item(MENU_DEL_COL).Enabled = bEnabled
         .MainToolbar.Buttons.item(TOOLBAR_DEL_COL).Enabled = bEnabled
      Case "ADD COL"
         .mnuEditSub2.item(MENU_INSERT_COL).Enabled = bEnabled
         .MainToolbar.Buttons.item(TOOLBAR_INSERT_COL).Enabled = bEnabled
   End Select
End With

End Sub

'----------------------------------------------
'   Sub: PREPARE GRID
'
'   Action: Get grid ready for displaying info
'
'----------------------------------------------
Public Sub PrepareGrid()
  
  With AEditorUI
      'Make sure we finish any editing changes
      If .txtGridEdit.Visible Then
         .grdData.TextMatrix(AEClass.CurrentRow, AEClass.CurrentCol) = AEditorUI.txtGridEdit.Text
         .txtGridEdit.Visible = False
      End If
      
      'Clear Grid and set up headers
      Call ClearGrid
      Call FormatGridHeaders
      
      'Allow Editing
      .grdData.Enabled = True
      
      'Clear Edit Box
      .txtGridEdit = ""
      .txtGridEdit.Visible = False
  End With
  
End Sub

'---------------------------------------------
'   Sub: CLEAR GRID
'
'   Action: Clears edit box and sets grid to
'   size of 2x4 after clearing.
'
'----------------------------------------------
Public Sub ClearGrid()

 With AEditorUI
   .txtGridEdit = ""
   .txtGridEdit.Visible = False
   .grdData.Clear
   .grdData.Rows = 2
   .grdData.Cols = 4
 End With
  
 Call FormatGridHeaders

End Sub

'---------------------------------------------
'   Sub: FORMAT GRID HEADERS
'
'   Action: Place the proper text in the headers
'   of the grid depending on the grid width.
'
'----------------------------------------------
Public Sub FormatGridHeaders()

   Dim sFormatString As String      'String for header formatting
   Dim X As Integer                 'Loop Variable
   
   sFormatString = "^ActivityID" & Space(6) & "|^Activity" & Space(32) & "|^Flags" & Space(20)
   For X = 3 To AEditorUI.grdData.Cols - 1
      sFormatString = sFormatString & "|^Parameters" & Space(32)
   Next
   AEditorUI.grdData.FormatString = sFormatString
End Sub

'------------------------------------------
'   Sub: DISPLAY MAP
'
'   Action: Read in Map and display in grid
'   on main UI.
'
'   Return: Boolean Success
'------------------------------------------
Public Function DisplayMap() As Boolean
 
  Dim lCntOut As Long         'Number of Arguments
  Dim lRowCnt As Long         'Number of Rows
  Dim lLoopOut As Long        'Outer Loop Variable
  Dim lLoopIn As Long         'Inner variable
  
  Dim oRowOut As Variant      'Row Object (must be variant)
  Dim vArgsOut As Variant     'Arguments (must be variant, normally holds variant array)
    
  Dim oMap As Object          'Route Map Object
  Dim oGrid As Object         'Grid Object
  
  Set oMap = AgentMap.Map
  
  'Set grid object to be the grid in the main UI form.
  Set oGrid = AEditorUI.grdData
  
  oGrid.Cols = 4
   
  Set oRowOut = Nothing
  
  'Get Number of Row
  lRowCnt = oMap.ActivityCount
  
  'If more than 0 rows, update grid
  If lRowCnt > 0 Then
    
    'Tell the grid the number of rows
    'One header and One empty.
    oGrid.Rows = lRowCnt + 2
    
    'Loop Through the rows.
    For lLoopOut = 1 To lRowCnt
  
      'Get IRow Object From Map
      oMap.GetRow lLoopOut - 1, oRowOut
      
      'Get arguments from IRow
      oRowOut.GetArgs lCntOut, vArgsOut
      
      'The reason the count out has 3 added is that the arguments
      'actually start on the 4th column. The first 3 columns are
      'show as the activityID, action and flags values. So the
      'miniumum columns to display is 3.
      '
      If lCntOut + 3 > oGrid.Cols Then
        oGrid.Cols = lCntOut + 3
      End If
      
      'Place Base Data in Grid
      oGrid.TextMatrix(lLoopOut, 0) = oRowOut.ActivityID
      oGrid.TextMatrix(lLoopOut, 1) = oRowOut.Action
      oGrid.TextMatrix(lLoopOut, 2) = oRowOut.Flags
      
      'Add extra column data to Grid
      For lLoopIn = 0 To lCntOut - 1
         'If data is numeric convert to string.
         If IsNumeric(vArgsOut(lLoopIn)) Then
            oGrid.TextMatrix(lLoopOut, lLoopIn + 3) = CStr(vArgsOut(lLoopIn))
         Else
            oGrid.TextMatrix(lLoopOut, lLoopIn + 3) = vArgsOut(lLoopIn)
         End If
      Next
    Next lLoopOut
    
    Call FormatGridHeaders
    
    'Set visibility of row delete feature
    Call SetDeleteRow
    
    DisplayMap = True
  Else
    DisplayMap = False
  End If
  
End Function

'----------------------------------------------
'   Public Sub: DIRTY STATUS UPDATE
'
'   Action: Checks the dirty flag and update the
'   UI menu and toolbar save changes options.
'
'   Parm: iDirtyVal is the new dirty constant
'         bAnd means to And instead of Or
'----------------------------------------------
Public Sub DirtyStatusUpdate(ByVal iDirtyVal As Integer, ByVal bAnd As Boolean)
   
   Select Case iDirtyVal
      Case DIRTY_NONE
         AEClass.Dirty = DIRTY_NONE
      Case Else
         If bAnd Then
            AEClass.Dirty = AEClass.Dirty And (Not iDirtyVal)
         Else
            AEClass.Dirty = AEClass.Dirty Or iDirtyVal
         End If
   End Select
   
   'Set the enable status of the save changes toolbar/menu items
   If AEClass.Dirty <> DIRTY_NONE Then
      AEditorUI.mnuAgent.item(MENU_AGENT_SAVE).Enabled = True
      AEditorUI.MainToolbar.Buttons.item(TOOLBAR_SAVE).Enabled = True
   Else
      AEditorUI.mnuAgent.item(MENU_AGENT_SAVE).Enabled = False
      AEditorUI.MainToolbar.Buttons.item(TOOLBAR_SAVE).Enabled = False
   End If
   
End Sub


'----------------------------------------------
'   Public Sub: SELECT SCRIPT
'
'   Action: Pops up a file dialog for selecting
'   the script.
'
'----------------------------------------------
Public Sub SelectScript()

    On Error GoTo SelectScriptErr
    
    Const CANCEL_ERROR = 32755
    
    Dim sTempStr As String    'Temporary String
    Dim ilocate As Integer    'Locate of token in string
    Dim sFilename As String   'Filename as string
    Dim sSPN As String        'PathName and Filename
    
    With AEditorUI
      ' Set CancelError is True
      .CommonDialog1.CancelError = True
    
      ' Clear Filename
      .CommonDialog1.filename = ""
      
      ' Set flags
      .CommonDialog1.Flags = cdlOFNHideReadOnly
    
      ' Set filters and intial directory
      .CommonDialog1.InitDir = AEClass.ScriptInitDir
      .CommonDialog1.Filter = "Script Files (*.vbs)|*.vbs|Text Files" & _
           "(*.txt)|*.txt|All Files (*.*)|*.*|"
      ' Specify default filter to be vbs
      .CommonDialog1.FilterIndex = 1
    
      ' Display the Open dialog box
      .CommonDialog1.ShowOpen
         
      ' Display name of selected file
      AEClass.ScriptPathName = .CommonDialog1.filename
    
      'Figure out initial directory and save
      sSPN = .CommonDialog1.filename
      sFilename = .CommonDialog1.FileTitle
        
      'Locate the last "\"
      ilocate = InStr(1, sSPN, sFilename)
      AEClass.ScriptInitDir = Left(sSPN, ilocate - 1)
    
      'AEClass.LoadFile AEClass.ScriptPathName, 1
      .RETextBox.LoadFile AEClass.ScriptPathName, 1
      .RETextBox.SaveFile "AEScript.tmp", 1
    End With
    
    Call DirtyStatusUpdate(DIRTY_SCRIPT, DIRTY_ADD)
    
    Exit Sub

'-------------------
SelectScriptErr:
    If Err.Number = CdoE_CANCEL Or Err.Number = CANCEL_ERROR Then
       'User pressed the Cancel button
    Else
       AgentMap.CdoErrorHandler ("Select Script")
    End If

End Sub

'------------------------------------------------
'   Sub: SCRIPT EDITING TOGGLE
'
'   Action: Enabled/Disabled menu options associated
'   with script editing.
'
'--------------------------------------
Public Sub ScriptEditingToggle(ByVal bEditOn As Boolean)
   Dim X As Integer  'loop variable
   For X = 0 To 3
      AEditorUI.mnuEditSub1(X).Enabled = bEditOn
   Next
End Sub

'------------------------------------------------
'   Sub: MAP EDITING TOGGLE
'
'   Action: Enable/Disable menu options associated
'   with map editing.
'
'--------------------------------------
Public Sub MapEditingToggle(ByVal bEditOn As Boolean)
   Dim X As Integer   'loop variable
   For X = 1 To 8
      If X <> 5 Then
         AEditorUI.mnuEditSub2(X).Enabled = bEditOn
      End If
   Next X
   With AEditorUI.MainToolbar.Buttons
      .item(TOOLBAR_DEL_COL).Enabled = bEditOn
      .item(TOOLBAR_INSERT_COL).Enabled = bEditOn
      .item(TOOLBAR_DEL_ROW).Enabled = bEditOn
      .item(TOOLBAR_INSERT_ROW).Enabled = bEditOn
   End With
End Sub


'------------------------------------------------
'   Sub: PICK FOLDER
'
'   Action: Handle showing the folder picker form
'
'--------------------------------------
Public Sub PickFolder()
   
   On Error Resume Next
        
   FolderPicker.Show vbModal
   
   'If not canceled then get folder
   If Not AEClass.Cancelled Then
       AEditorUI.lblFolderName = FolderPicker.tvwFolders.SelectedItem.Text
       Screen.MousePointer = vbHourglass
   End If

   Screen.MousePointer = vbNormal
   
End Sub

'-------------------------------------------------
'
'  Name: ESTABLISH CONNECTION
'
'  Action: Call Logon UI and initializes AgentMap class
'
'--------------------------------------------------
Public Function bEstablishConnection() As Boolean

   On Error Resume Next
   
   Dim lVal As Long         'Long
      
   'Fail by default
   bEstablishConnection = False
   
   LogonStatus.Show vbModal
   
   'Verify they logged on and didn't cancel
   If Not AgentMap.IsLoggedOn Then
      If Err Then
         AgentMap.CdoErrorHandler ("Establish Connection")
      Else
         MsgBox "Unable to Logon to Exchange Server.", vbCritical, App.Title
      End If
      Exit Function
     
   Else
      lVal = AgentMap.InitializeEvents()
      'Note - InitializeEvents is designed to raise a 80043E80 error
      'if ESCONF.DLL is not registered.
      If lVal > 0 Then
         Select Case lVal
            Case CdoE_CALL_FAILED
               MsgBox "Unable to initialize the events session. Exchange Server may be down.", vbCritical, App.Title
               bEstablishConnection = False
               Exit Function
            Case ERR_PERMISSIONS_DENIED
               MsgBox "No event permissions. You will only be able to edit the Folder Routing Message Map.", vbInformation, App.Title
               bEstablishConnection = True
            Case ERR_ESCONF_SETUP
               MsgBox "Unable to create AgentMap object. Verify that ESCONF.DLL is installed and registered properly. Otherwise you can only edit the Folder Routing Message Map.", vbCritical, App.Title
               bEstablishConnection = True
            Case ERR_NO_SESSION
               MsgBox "No Session available to initialize events."
            Case ERR_SYSTEM_ERROR
               AgentMap.CdoErrorHandler ("Establish Connection")
         End Select
      Else
         bEstablishConnection = True
      End If
   End If

End Function

'----------------------------------------------------------
' Sub: SAVE ROUTE MAP
'
' Action: Saves the grid as a map on the active msg which is
' stored in the class. The active message is the one that
' last obtained with the GetRoutingMsg or GetBindingMsg
' methods.
'
'----------------------------------------------------------
Public Sub SaveRouteMap(ByRef Grid As Object)

  Dim b_OK As Boolean             'Boolean Success
  Dim b_SAVED As Boolean          'Boolean Saved
  
  Dim lCol As Long                'Long Column Number
  Dim lRow As Long                'Long Row Number
  Dim lParamCols As Long          'Long Number of Columns
  Dim lCurParamCol As Long        '
  
  Dim iVal As Integer             'Return integer err value (>0 is error)
  
  Dim oRow As Variant             'IROW object
  Dim vntField As Variant         'Variant Field Array
  Dim vData As Variant            'Variant Data
  
  Dim vTempDouble As Double      'Have to allocate a double to check for double data type
  
  Dim bBlank As Boolean          'blank column detected
  
  b_SAVED = False
  
  On Error GoTo SaveMapError
  
   If Len(Grid.TextMatrix(1, 0)) = 0 And Grid.Rows = 2 Then
      'Save EmptyMap
      If (MsgBox("You have only one line in the map and the first column is blank, this will result in the deletion of the map. Do you wish to delete this map ?", vbYesNo + vbQuestion, App.Title) = vbYes) Then
         AgentMap.ReinitializeMap
         b_SAVED = AgentMap.SaveMap
         If Not b_SAVED Then
            MsgBox "Map was deleted."
         End If
      Else
         MsgBox "Map not saved."
      End If
      Exit Sub
   End If
   
   'Check for correct user entry.
   '-----------------------------
   For lRow = 1 To Grid.Rows - 1
      If Len(Grid.TextMatrix(lRow, 0)) > 0 And Grid.TextMatrix(lRow, 0) <> " " Then
          
         vData = Grid.TextMatrix(lRow, 0)
         
         'Filter out errors with activity ID Being to a double, a string, or negative
         If IsNumeric(vData) = False Then
            MsgBox "Activity ID must be a number in row " & lRow & ". Map not written."
            Exit Sub
         End If
         vTempDouble = 2147483648#
         If CDbl(vData) >= vTempDouble Then
            MsgBox "Activity ID must be smaller than 2147483648 in row " & lRow & ". Map not written."
            Exit Sub
         ElseIf CDbl(vData) < 1 Then
            MsgBox "Activity ID must be number greater than zero in row " & lRow & ". Map not written."
            Exit Sub
         End If
                
         vData = Grid.TextMatrix(lRow, 2)
         'Filter out nonnumeric and neg or > 2 for parameter 2
         If IsNumeric(vData) = False Then
            MsgBox "Flag must be a number in row " & lRow & ". Map not written."
            Exit Sub
         End If
         vTempDouble = 2#
         If CDbl(vData) > vTempDouble Then
            MsgBox "Flag must be smaller than 3 in row " & lRow & ". Map not written."
            Exit Sub
         ElseIf CDbl(vData) < 0 Then
            MsgBox "Flag must be a positive number in row " & lRow & ". Map not written."
            Exit Sub
         End If
         
         'Bogus Activity Entry Checks
         vData = Grid.TextMatrix(lRow, 1)
         If IsNumeric(vData) = True Then
            MsgBox "Cannot use numbers only in function name in row " & lRow & ". Map not written."
            Exit Sub
         End If
         If Len(vData) = 0 Then
            MsgBox "Activity cannot be zero length in row " & lRow & ". Map not written."
            Exit Sub
         End If
         If Len(LTrim(vData)) = 0 Then
            MsgBox "Activity doesn't contain any characters in row " & lRow & ". Map not written."
            Exit Sub
         End If
         
         
         With Grid 'Use the msflexgrid
            lParamCols = 0
            bBlank = False
            For lCol = 3 To Grid.Cols - 1
               If Len(Grid.TextMatrix(lRow, lCol)) <> 0 And Len(LTrim(Grid.TextMatrix(lRow, lCol))) <> 0 Then
                  lParamCols = lParamCols + 1
                  'If there was a blank in a column and another value is detected then
                  'post error.
                  If bBlank = True Then
                     MsgBox "Empty column in row " & lRow & ". Map not written."
                     Exit Sub
                  End If
               Else
                  bBlank = True
               End If
            Next
            'if flag = 2 then a parameter must exist.
            If lParamCols = 0 Then
               If .TextMatrix(lRow, 2) = "2" Then
                  MsgBox "All activity items with a Flag set to '2' must supply a parameter." & vbCrLf & vbCrLf & "The map has not been saved.", vbOKOnly + vbInformation, App.Title
                  Exit Sub
               End If
            End If
        End With
      Else
        'Trap Blank rows as error except for last one.
        If Grid.Rows - 1 = lRow Then
            'Ignore since this is the last row
        Else
            MsgBox "A column is empty in Row " & lRow & ". Map was not saved.", vbExclamation, App.Title
            Exit Sub
        End If
      End If
   Next lRow
  
   
   'Clear the map out.
   AgentMap.ReinitializeMap
   
    
   For lRow = 1 To Grid.Rows - 1
   
   If Grid.TextMatrix(lRow, 0) <> "" Then
   
      Set oRow = AgentMap.CreateRow()
      
      'Get row information from the grid and create a row
      With Grid
     
         lParamCols = 0  'Clear Accum
          
         'Get the number of columns. Iterate through all the columns
         'and quit when the empty or all space cell is found.
         'Note: lParamCols is used to dimension the array.
         For lCol = 3 To Grid.Cols - 1
            If Grid.TextMatrix(lRow, lCol) <> "" And Len(LTrim(Grid.TextMatrix(lRow, lCol))) <> 0 Then
              lParamCols = lParamCols + 1
            End If
         Next
   
         'If more than 0 columns
         If lParamCols > 0 Then
         
           'Dimension the variant field to the number of columns
           ReDim vntField(lParamCols - 1) As Variant
           
           'Clear Array Index for columns > 3
           lCurParamCol = 0
           
           'Iterate through the extra parameters skipping the
           'first 3 and skipping blanks or spaces (note: at this point the
           'only blank or space would be at the end).
           '
           'lCurParamCol is used to index the array from 0 since the
           'first three columns are directly written to properties.
           For lCol = 3 To lParamCols + 2
               If UCase(.TextMatrix(lRow, 1)) = "SEND" And lCol = 3 Then
                  vntField(lCurParamCol) = CStr(.TextMatrix(lRow, lCol))
               Else
                  If IsNumeric(.TextMatrix(lRow, lCol)) Then
                     vData = Val(.TextMatrix(lRow, lCol))
                     If CLng(vData) = vData Or UCase(.TextMatrix(lRow, 1)) = "WAIT" Then
                       vntField(lCurParamCol) = CLng(vData)
                     Else
                       vntField(lCurParamCol) = vData
                     End If
                  Else
                     vntField(lCurParamCol) = .TextMatrix(lRow, lCol)
                  End If
               End If
               lCurParamCol = lCurParamCol + 1
           Next
           oRow.SetArgs lParamCols, vntField
         End If
         
      'Initialize the first 3 rows with the
      'Activity ID, the action (a string) and the flag (0,1 or 2)
      oRow.ActivityID = .TextMatrix(lRow, 0)
      oRow.Action = .TextMatrix(lRow, 1)
      oRow.Flags = .TextMatrix(lRow, 2)
      End With
   
     iVal = AgentMap.InsertRow(oRow)
     If iVal > 0 Then
           If iVal = ERR_MAP_ROW_INVALID Then
               MsgBox "Map row was invalid. Map will not be saved.", vbExclamation, App.Title
           ElseIf iVal = ERR_INSERT_ROW_NO_VALID_MAP Then
               MsgBox "No valid map was available to write rows to. Map will not be saved.", vbExclamation, App.Title
           Else
               MsgBox "An Error occurred during the insert of row activity id " & oRow.ActivityID & ". Map will not be saved.", vbExclamation, App.Title
           End If
           Exit Sub
     End If
   End If
   Next lRow

  'The AgentMap class knows where to save the map (if it's a Routing Map (FAI) or Agent Map)
  'since this information was gotten during the GetMap/Get___Msg functions.
   b_SAVED = AgentMap.SaveMap
  
   If b_SAVED Then
      MsgBox "Map saved successfully."
   Else
      MsgBox "Map Deleted."
   End If
'---------------
Cleanup:
  Set oRow = Nothing
  
  Exit Sub
  
'---------------
SaveMapError:

  
  Call AgentMap.CdoErrorHandler("SaveRouteMap")
  
  GoTo Cleanup
  
End Sub

'------------------------------------------
'   Public Function: SAVE AGENT
'
'   Action: Saves a new or edited agent.
'
'------------------------------------------
Public Function SaveAgent() As Boolean

On Error Resume Next

Dim iEventMask As Integer       'Integer Event Mask (required)
Dim b_OK As Boolean             'Boolean Result
Dim sScript As String           'Script String

If Len(AEditorUI.lblAgentName) = 0 Then
      AEditorUI.lblAgentName = InputBox("You must enter a valid agent name or all changes will be lost:", , "New Agent")
      AEditorUI.txtAgentName = AEditorUI.lblAgentName
      If Len(AEditorUI.lblAgentName) = 0 Then
         SaveAgent = False
         Exit Function
      End If
End If

iEventMask = AEditorUI.ChkEvent(1).Value + AEditorUI.ChkEvent(2).Value * 2 + AEditorUI.ChkEvent(3).Value * 4 + AEditorUI.ChkEvent(4).Value * 8

Select Case AEClass.EditMode

'NEW AGENT SAVE
Case MODE_NEW_AGENT
   
   With AEditorUI
      .RETextBox.SaveFile "AEScript.tmp", 1
   
      b_OK = AgentMap.CreateAgent(.lblAgentName, iEventMask, "AEScript.tmp", AEClass.AgentClassID, AEditorUI.ChkActive.Value)
      If b_OK Then
         MsgBox "Agent Saved.", vbInformation, App.Title
         SaveAgent = True
      Else
         MsgBox "Agent save failed. Event permissions may not longer be valid.", vbExclamation, App.Title
         SaveAgent = False
      End If
      
   End With
   
   'Change to editing since it's now been saved.
   AEClass.EditMode = MODE_EDIT_AGENT
   
   'Update BindingEID for checking during edit saving.
   AEClass.BindingEID = AgentMap.BindingEID
   
'EDIT AGENT SAVE
Case MODE_EDIT_AGENT

   If Not AgentMap.VerifyEID(AEClass.BindingEID) Then
      MsgBox "Agent was deleted by another application. Select a new agent to edit.", vbExclamation, App.Title
      SaveAgent = False
      Exit Function
   End If
   
   With AEditorUI
      
      .RETextBox.SaveFile "AEScript.Tmp", 1
      
      b_OK = AgentMap.ModifyAgent(.lblAgentName, iEventMask, "AEScript.tmp", "", AEditorUI.ChkActive.Value)
      If b_OK Then
         MsgBox "Agent updated with changes.", vbInformation, App.Title
         SaveAgent = True
      Else
         MsgBox "Agent update failed. Event permissions may not be valid.", vbExclamation, App.Title
         SaveAgent = False
      End If
      
      On Error Resume Next
      Kill "AEScript.Tmp"
      If Err Then
         'Unable to delete temporary file. No big deal, We may not have modified script.
         Err.Clear
      End If
      On Error GoTo 0
         
   End With
   
Case MODE_EDIT_MAP_ONLY
   'Note - Nothing to save since we aren't allow to edit the agent only the map
   SaveAgent = False

Case Else
   SaveAgent = False

End Select

End Function
