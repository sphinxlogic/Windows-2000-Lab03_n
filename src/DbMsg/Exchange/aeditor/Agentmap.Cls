VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "AgentMapClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Description = "Agent Map Class - CDO/Event/Map methods and properties."
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
' WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
' INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
' OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
' PURPOSE
'
'***********************************************************************
'
'   AGENTMAP CLASS
'
'   Overview: This class is made up of 3 distinct class groups. CDOhandler,
'   Event and Map. The purpose is to demonstrate in a single class the
'   properties and methods exposed by the CDO.DLL, ESCONF.DLL and EXRTOBJ.DLL.
'   It also gives examples of how to create and modify Microsoft Event
'   Service Bindings (commonly called agents) and Route Object Maps.
'
'  Requirements: In order to use this class in your own project you need the
'                following:
'
'      1. CDO.DLL - Collaboration Data Objects - Version 1.2x or later
'      2. ESCONF.DLL - Event Service
'      3. EXRTOBJ.DLL - Routing Objects (only if you are using the map group)
'
'      4. You also need to install CDOHandler module in your project.
'          (Cdohandler.bas), it holds constants used by this class.
'
'
'***********************************************************************
'   EVENT CLASS GROUP
'***********************************************************************
'   This Class group is used to wrap the event service functionality
'   associated with placing and editing agents in folders.
'
'   Requires the following registered DLL's
'         CDO.dll
'         Esconf.dll
'
'   It uses ESCONF.DLL for the events object and
'   this supplies the bindings in a folder.
'
'   Typical Usage:
'      1. Logon
'      2. InitializeEvents
'      3. InitializeFolder using the folder Id
'      4. Obtain binding using either
'          a. GetBindingbyName
'          b. GetBindingbyIndex
'          c. GetBindingByProp (locate a binding with a specialized prop)
'          d. GetBindingByEID (typically used for pickers for saved eid info)
'
'
'   Public Methods
'      InitializeEvents()
'      InitializeFolder()
'      CreateAgent(AgentName, EventMask, ScriptPathName,ClassID)
'      ModifyAgent(AgentName, Eventmask,ScriptPathname,ClassId,Active)
'      GetBindingByName(AgentName)
'      GetBindingByIndex(index)
'      GetBindingByEID(EntryID)
'      GetHostName(index)
'      GetHandlerName(index)
'      GetHandlerID(index)
'      GetScript(ScriptPathName)
'      UpdateScript(ScriptPathName)
'      Delete(AgentName,Exact)
'      BindingCheckPropExist(Property Name)
'
'   Public Props
'      HostCount                (readonly)      (integer)
'      HandlerCount             (readonly)      (integer)
'      BindingCount             (readonly)      (integer)
'      BindingID                (readonly)      (string)
'      BindingCreationTime      (readonly)      (date)
'      BindingClassID           (readonly)      (string)
'      BindingHandlerName       (readonly)      (string)
'      BindingName              (readonly)      (string)
'      Permissions              (readonly)      (Boolean)
'      ActiveStatus             (readonly)      (Boolean)
'      Folder                   (readonly)      (Object)
'      EventMask                (readonly)      (integer)
'      IsInitialized            (readonly)      (Boolean)
'---------------------------------------------------

Private moEvents As Object         'Events Object
Private moBindings As Object       'Event Bindings
Private moFolder As Object         'Folder Object
Private moBoundFolder As Object    'Bound folder object
Private moBinding As Object        'Binding Object
Private moHosts As Object          'Hosts Object
Private moHandlers As Object       'Handlers of 1st Host (normally only one)
Private mbPermissions As Boolean   'boolean permissions

'*****************************************************************
'  CDOHANDLER CLASS GROUP
'*****************************************************************
'  This simple Class group is used to deal with common CDO
'  handling used during normal processing. Is required by
'  the class for logon and session needs.
'-----------------------------------------------------

'Methods
'
'   GetMessage(EntryID as string)
'   ResolveNames(Names as string)
'   Folder(FolderID as string)
'   CdoErrorHandler(sDisplay as string)
'   LogOn(bUIFlag As Boolean, sProfileInfo As String, bSilent as boolean)
'   Logon
'
'
'Properties
'
'   IsLoggedOn         (readonly)      (Boolean)
'   PublicStoreName     (readonly)      (String)
'   Session             (readonly)      (object)
'   ActiveFolder        (readonly)      (object)
'   ActiveFolderID      (read/write)    (folderid)

Private moSession As Object            'Session Object
Private item As Object                 'Used with For Each Loops
Private msPublicStoreName As String    'Public Store String (for languages)
Private mbLoggedOn As Boolean          'Logged On Boolean
Private msFolderID As String           'Current Active Folder (used for special applications)

'*****************************************************************
'    ROUTEMAP CLASS GROUP
'*****************************************************************
'  This class has methods and properties related toward handling
'  routing maps. The maps can be located on Routing Map Msg, Routing
'  Agent Binding or Process Instance Messages.
'
'  Requirements:
'       CDO.DLL - Collaboration Data Objects - Version 1.2x or later
'       ESCONF.DLL - Event Service
'       EXRTOBJ.DLL - Routing Objects
'
'  CLASS INFORMATION - Other files required with this class
'       CDOHANDLER.BAS
'
'  General use info
'     1. GetxxxMsg - Get the Msg that will be associated with the map
'     2. GetMap
'     3. Insert Activities into the map
'     3. Save the map
'
'  Methods:
'          NAME         RETURN          PARM
'--------------------------------------------------------------
'       GetRoutingMsg   Success         Void
'       GetBindingMsg   Success         Void
'       SaveMap         None            Void
'       InsertRow       Success         iRow as variant
'       ReinitializeMap None            void
'       GetMap          Success         String Target
'       CreateRow       Variant iRow    Void
'
'
'                       Read/Write   Data Type      Description
'--------------------------------------------------------------
'  Properties:
'       MapType         ReadOnly     Integer       1,2
'       IsWizardMap     ReadOnly     Boolean       Checks Routetype prop
'       Map             ReadOnly     Object        Map Object
'       MapMsg          ReadOnly     Object        Message Object
'       Row             ReadOnly     Variant       iRow Object
'       MapMsgEID       ReadOnly     string        Map Message EID
'
'
'---------------------------------------------------------------

Const TBL_OPEN_READWRITE = 1

'Map Type Constants
Private miMapType As Integer                   'Map type is (1) Agent (2) Routing
Private moRow As Variant                       'Row Variant (iROW)
Private moMap As Object                        'Map Object
Private moMapMsg As Object                     'Local Map Message Object
Private msMsgEntryID As String                 'Map Message Entry Id String

'*******************************************************************
'                  CDO CLASS GROUP METHODS/PROPERTIES
'*******************************************************************

'--------------------------------------------
' Prop: FOLDER NAME
'
' Action: Get Folder Name associated with
'         stored folder ID
'
' Return: Message Object
'
' CLASS GROUP: CDO
'
'--------------------------------------------
Public Property Get FolderName() As String
   If Not (moSession Is Nothing Or Len(msFolderID) = 0) Then
      FolderName = moSession.GetFolder(msFolderID, Null).name
   Else
      FolderName = ""
      
   End If
End Property

'--------------------------------------------
' Method: GET MESSAGE
'
' Action: Get message associated with entryid
'         using the default store.
'
' Return: Message Object
'
' CLASS GROUP: CDO
'
'--------------------------------------------
Public Function GetMessage(ByVal sId As String) As Object
    If sId <> "" Then
       Set GetMessage = moSession.GetMessage(sId, Null)
    End If
End Function

'--------------------------------------------
' Prop: IS LOGGED ON
'
' Action: Get the Logon Status
'
' Return: Boolean (True=Logged on)
'
' CLASS GROUP: CDO
'
'--------------------------------------------
Public Property Get IsLoggedOn() As Boolean
    IsLoggedOn = mbLoggedOn
End Property

'--------------------------------------------
' Prop: PUBLIC STORE NAME
'
' Return: Public Store Name String
'
' GROUP: CDO
'
'--------------------------------------------
Public Property Get PublicStoreName() As String
    PublicStoreName = msPublicStoreName
End Property

'--------------------------------------------
' Method: CDO ERROR HANDLER
'
' Action: Generic Global Error Handler for CDO
'         Errors
'
' Parm: String to display in error box.
'
' CLASS GROUP: CDO
'
'--------------------------------------------
Public Sub CdoErrorHandler(ByVal sProcessDesc As String)

Dim ts As String
Dim CriticalFlag As Boolean  'Critical error has occured


'Expand Cases As Needed
Select Case Err.Number
   Case CdoE_NETWORK_ERROR
      CriticalFlag = True
      ts = "Network Error."
      
   Case CdoE_TIMEOUT
      ts = "Timeout Error."
      
   Case CdoE_EXTENDED_ERROR
      ts = "Extended Mapi Error."
   
   Case CdoE_LOGON_FAILED
      ts = "Logon Failed."
      
   Case CdoE_UNKNOWN_ENTRYID
      ts = "Entry ID not found."
      
   Case CdoE_NO_ACCESS
      ts = "No Access."
      
   Case CdoE_FAILONEPROVIDER
      AgentMap.LogOff
      ts = "Exchange Server is unavailable. Please choose another profile or try again later."
      
   Case CdoE_USER_CANCEL
      'This is a User Cancel Case - No problem exists just exit quietly
      'This should be trapped by inline code if special handling is
      'desired.
      Err.Clear
      Exit Sub
   
   Case CdoE_UNCONFIGURED
      'This means that the user didn't properly specify a server or alias for the
      'profileinfo logon
      Err.Clear
      Exit Sub
         
   Case Else
      ts = ""
      
End Select

If ts <> "" Then
   ts = ts & vbCrLf & vbCrLf
End If
   
ts = ts & "Error String = " & sProcessDesc & vbCrLf & vbCrLf
ts = ts & "Error Number = &H" & Hex(Err.Number) & vbCrLf & vbCrLf
ts = ts & "Error Description = " & Err.Description

If CriticalFlag Then
   MsgBox ts, vbCritical & vbOKOnly, App.Title
Else
   MsgBox ts, vbExclamation & vbOKOnly, App.Title
End If
Err.Clear

End Sub

'--------------------------------------------
' Method: LOGOFF
'
' Action: Will log off if the user is logged
' on, otherwise it does nothing.
'
' CLASS GROUP: CDO
'
'--------------------------------------------
Public Sub LogOff()
   If mbLoggedOn Then
      moSession.LogOff
      mbLoggedOn = False
   End If
End Sub


'------------------------------------------------------------------
' Method: LOGON
'
' Action: Logs on and gets a  mapi session using either a mapi
'         profile or the profileinfo method for "quiet" logons.
'
' Parms: bUIFlag - True = Show UI, False = Don't show UI
'        sProfileInfo - String - <servername> & vblf & <mailbox>
'        bsilent = True
'
' Returns: Integer Error Number or zero for no error
'
' CLASS GROUP: CDO
'
'------------------------------------------------------------------
Public Function Logon(ByVal bUIFlag As Boolean, ByVal sProfileInfo As String, ByVal bSilent As Boolean) As Integer

On Error GoTo ETrap

Dim ostores As Object         'InfoStores Collection
Dim ostore As Object          'Infostore Object
Dim orootfolder As Object     'Root folder Object
Dim ofoldercol As Object      'Folder Collection

Dim lmask As Long             'Long Mask


Logon = NO_ERROR

'If user is not already logged on then do mapi logon
If mbLoggedOn Then
    'User is already logged on, no need to logon,
    'just exit quietly.
    GoTo Cleanup
End If

'Create Session Object
Set moSession = CreateObject("Mapi.session")

'Log in using UI or otherwise use the ProfileInfo technique
'which has no UI.
If bUIFlag Then
     moSession.Logon "", "", True, True, 0
Else
     moSession.Logon , , False, , , , sProfileInfo
End If
  
'Get Public Folder name. For localization reasons we get
'the name.
 Set ostores = moSession.InfoStores
 For Each item In ostores
    Set ostore = item
    On Error Resume Next
    lmask = ostore.Fields.item(CdoPR_STORE_SUPPORT_MASK)  '&H340D0003
    Err.Clear
    If lmask And &H4000 Then        ' CDO_STORE_PUBLIC_FOLDERS
      msPublicStoreName = ostore.name
      Exit For
    End If
Next
On Error GoTo ETrap

'Get the ALL PUBLIC FOLDERS infostore Object
For Each item In ostores
  If item.name = msPublicStoreName Then
     Set ostore = item
     Exit For
  End If
Next

mbLoggedOn = True

'------------
Cleanup:

    'Release Objects
    Set ostores = Nothing
    Set ostore = Nothing
    Set orootfolder = Nothing
    Set ofoldercol = Nothing

Exit Function

'------------
ETrap:
 
 'Specifically display errors for the more common problems, otherwise pass to error handler
 Select Case Err
    Case CdoE_USER_CANCEL
       'This is just a logon cancel. Exit quietly.
       'This won't occur with profile info logons
       
    Case CdoE_LOGON_FAILED
       If bSilent Then
          Logon = ERR_INCORRECT_PROFILE_OR_PASSWORD
       Else
          MsgBox "Unable log on to your mail server: incorrect profile name or password. ", vbOKOnly + vbCritical, App.Title
       End If
       
    Case CdoE_FAILONEPROVIDER
       If bSilent Then
          Logon = ERR_UNABLE_TO_LOGON
       Else
          MsgBox "Unable to logon to Exchange Server, please try again later." & vbCrLf & vbCrLf & "If the problem persists contact your administrator."
          Call LogOff
       End If
    Case Else
       If bSilent Then
'         Logon = ERR_SYSTEM_ERROR
          Err.Raise Err.Number, "CdoHandler", Err.Description
       Else
          Call CdoErrorHandler("CDOHander Logon")
       End If
       
 End Select
 
GoTo Cleanup

End Function

'----------------------------------------------
'  Prop: ActiveFolderID
'
'  Action: Get the current folder ID associated
'  with most recently obtained folder object
'
'  Return: FolderID as string
'
'  CLASS GROUP: CDO
'
'---------------------------------------------
Public Property Get ActiveFolderId() As String
   ActiveFolderId = msFolderID
End Property


'----------------------------------------------
'  Prop: ActiveFolderID
'
'  Action: Let the current folder ID associated
'  with most recently obtained folder object
'
'  CLASS GROUP: CDO
'
'---------------------------------------------
Public Property Let ActiveFolderId(ByVal sId As String)
   msFolderID = sId
End Property

'-----------------------------------------
'  Prop: SESSION
'
'  Action: Get the current session object associated
'  with the currently logged on profile.
'
'  Return: Session Object
'
'  CLASS GROUP: CDO
'-----------------------------------------
Public Property Get Session() As Object

If mbLoggedOn Then
   If IsObject(moSession) Then
      Set Session = moSession.Session
   End If
Else
   Set Session = Nothing
End If
   
End Property


'*******************************************************************
'                  EVENTS CLASS GROUP METHODS/PROPERTIES
'*******************************************************************

'-----------------------------------------------
'   Method: BINDING CHECK PROPERTY EXIST
'
'   Action: Find out if a custom property exists
'   on an event binding.
'
'   Parm: Binding Name
'
'   Return: (bool) True of False
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Function BindingCheckPropExist(ByVal sPropname As String) As Boolean

   On Error Resume Next
   
   Dim vFieldTemp As Variant
   Dim omsgtemp As Object
   
   BindingCheckPropExist = False
   
   If Not moBinding Is Nothing Then
      Set omsgtemp = moSession.GetMessage(moBinding.EntryID, Null)
      vFieldTemp = omsgtemp.Fields.item(sPropname)
      If Err Then
         Err.Clear 'prop doesn't exist
      Else
         BindingCheckPropExist = True
      End If
   End If
   Set omsgtemp = Nothing
  
End Function


'-----------------------------------------------
'   Method: VerifyEID
'
'   Action: Check if the internal moBinding object
'   Still Exists (hasn't been deleted).
'
'   Return: (boolean) True or False
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Function VerifyEID(sBindingEID) As Boolean

   Dim item As Object
   
   'Default is failure to find
   VerifyEID = False
      
   'Search for Binding
   For Each item In moBindings
       If item.EntryID = sBindingEID Then
            VerifyEID = True
            Set item = Nothing
            Exit Function
       End If
   Next
   
   Set item = Nothing
   
End Function

'-----------------------------------------------
'   Prop: IS INITIALIZED
'
'   Action: Find out if events has already been
'   initialized.
'
'   Return: (boolean) True or False
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Property Get IsInitialized() As Boolean
    If Not moEvents Is Nothing Then
       IsInitialized = True
    Else
       IsInitialized = False
    End If
End Property

'-----------------------------------------------
'   Method: GET BOUND HOST NAME
'
'   Action: Get the name of a host by index
'
'   Return: (string) Name of host
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Function GetBoundHostName() As String
   If Not moBoundFolder Is Nothing Then
      GetBoundHostName = moBoundFolder.HostName
   Else
      GetBoundHostName = ""
   End If
End Function


'-----------------------------------------------
'   Method: GET HOST NAME
'
'   Action: Get the name of a host by index
'
'   Parm: Index as integer. The function checks
'   the index for valid range.
'
'   Return: (string) Name of host
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Function GetHostName(ByVal Index As Integer) As String
   If Not moHosts Is Nothing Then
      If Index > 0 And Index <= moHosts.Count Then
           GetHostName = moHosts.item(Index).name
      End If
   End If
End Function

'-----------------------------------------------
'   Prop: HOST COUNT
'
'   Action: Get the number of hosts (can use for
'   interating through hosts).
'
'   Parm: Void
'
'   Return: (integer) Number of Host
'
'  CLASS GROUP: EVENTS
'-----------------------------------------------
Public Property Get HostCount() As Integer
    If Not moHosts Is Nothing Then
        HostCount = moHosts.Count
    End If
End Property

'-----------------------------------------------
'   Prop: BINDING EVENT MASK
'
'   Action: Get the Event Mask of the current
'   binding
'
'   Parm: Void
'
'   Return: (integer) Binding Bit Mask
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Property Get EventMask() As String
   If Not moBinding Is Nothing Then
      EventMask = moBinding.EventMask
   End If
End Property

'-----------------------------------------------
'   Prop: BINDING CLASS ID
'
'   Action: Get the id of the current active
'   binding handler class.
'
'   Parm: Void
'
'   Return: (string) Binding Handler Class ID
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------
Public Property Get BindingClassID() As String
   If Not moBinding Is Nothing Then
      BindingClassID = moBinding.HandlerClassID
   End If
End Property

'--------------------------------------------------
'  Prop: HANDLER COUNT
'
'  Action: Get the handler count associated with the
'          active handler collection
'
'  Return: (integer) Number of Handlers
'
'  CLASS GROUP: EVENTS
'--------------------------------------------------
Public Property Get HandlerCount() As Integer
   If Not moHandlers Is Nothing Then
       HandlerCount = moHandlers.Count
   End If
End Property

'--------------------------------------------------
'  Method: GET HANDLER NAME
'
'  Action: Get the name associated with the
'          index given. Index value is checked.
'
'  Parm: (integer) index
'
'  Return: (string) Name
'
'  CLASS GROUP: EVENTS
'--------------------------------------------------
Public Function GetHandlerName(ByVal Index As Integer) As String
   If Not moHandlers Is Nothing Then
      If Index > 0 And Index <= moHandlers.Count Then
           GetHandlerName = moHandlers.item(Index).name
      End If
   End If
End Function

'--------------------------------------------------
'  Method: GET HANDLER ID
'
'  Action: Get the handler id associated with the
'          index given. Index is checked.
'
'  Parm: Index of Handler.
'
'  Return: Class ID (string)
'
'  CLASS GROUP: EVENTS
'--------------------------------------------------
Public Function GetHandlerId(ByVal Index As Integer) As String
   If Not moHandlers Is Nothing Then
      If Index > 0 And Index <= moHandlers.Count Then
           GetHandlerId = moHandlers.item(Index).ClassID
      End If
   End If
End Function
'--------------------------------------------------
'  Prop: BINDING EID
'
'  Action: Get the message entry ID of the message
'  associated with the binding. This is commonly for
'  adding or checking custom props or writing
'  maps.
'
'  Parm: Void
'
'  Return: (string) Binding ID
'
'  CLASS GROUP: EVENTS
'--------------------------------------------------
Public Property Get BindingEID() As String
    If Not moBinding Is Nothing Then
      BindingEID = moBinding.EntryID
    Else
      BindingEID = ""
    End If
End Property

'---------------------------------------------------------
'
'  Private Method: GET BINDING WITH PROP
'
'  Action: This private methods finds a binding that has
'  a custom property with the correct value. This becomes
'  the new binding internally used by the class.
'
'  Parm: (string) Custom Property Name
'        (variant) Data the property should have
'
'  Return: (Boolean) True if the binding is found
'
'  CLASS GROUP: EVENTS
'---------------------------------------------------------
Private Function GetBindingWithProp(ByVal sPropname As String, ByVal vData As Variant) As Boolean
    
    On Error Resume Next
    
    Dim X As Integer            'Loop Variable
    Dim omsgtemp As Object      'Temp Message Object
    Dim vFieldTemp As Variant   'Field Temp
    
    'Default is false
    GetBindingWithProp = False
    
    If Not moBinding Is Nothing Then
      If moBindings.Count > 0 Then
         For X = 1 To moBindings.Count
           Set moBinding = moBindings.item(X)
           
           'Get CDO message for searching custom prop
           Set omsgtemp = moSession.GetMessage(moBinding.EntryID, Null)
           vFieldTemp = omsgtemp.Fields.item(sPropname)
           If Err = CdoE_NOT_FOUND Then
              Err.Clear  'prop not found on this message
           Else
              If vFieldTemp = vData Then
                 'match is made
                 GetBindingWithProp = True
                 Exit For
              End If
           End If
         Next
      End If
   End If
   
End Function

'---------------------------------------------
'  Prop: PERMISSIONS
'
'  Action: Get Status of Event Permissions
'
'  Return: (Boolean) Event Permissions True/False
'
'  CLASS GROUP: EVENTS
'----------------------------------------------
Public Property Get Permissions() As Boolean
   Permissions = mbPermissions
End Property

'-------------------------------------------
'   Prop: SCHEDULE
'
'   Action: Get the Schedule from the current
'   active binding
'
'   Return: (object) Schedule
'
'   CLASS GROUP: EVENTS
'-------------------------------------------
Public Property Get Schedule() As Object
   If Not moBinding Is Nothing Then
      Set Schedule = moBinding.Schedule
   End If
End Property

'-------------------------------------------
'   Prop: BINDING CREATION TIME
'
'   Action: Get the Creation Time of the
'   current active binding
'
'   Return: Creation Time as a variant
'
'   CLASS GROUP: EVENTS
'-------------------------------------------
Public Property Get BindingCreationTime() As Variant
   If Not moBinding Is Nothing Then
      BindingCreationTime = moBinding.CreationTime
   End If
End Property

'---------------------------------------------
'   Prop: BINDING NAME
'
'   Get the name of the current active binding
'
'   Return: Binding Name as a string
'
'   CLASS GROUP: EVENTS
'---------------------------------------------
Public Property Get BindingName() As String
   If Not moBinding Is Nothing Then
      BindingName = moBinding.name
   End If
End Property

'--------------------------------------
'   Prop: BINDING HANDLER NAME
'
'   Action: Get the name of the current
'   active binding.
'
'   Return: Name of Binding Handler as string
'
'   CLASS GROUP: EVENTS
'--------------------------------------
Public Property Get BindingHandlerName() As String

  Dim sBindingClassId
  Dim X As Integer

  BindingHandlerName = ""
  
  If Not moBinding Is Nothing Then
    sBindingClassId = moBinding.HandlerClassID
    For X = 1 To moHandlers.Count
        If moHandlers.item(X).ClassID = sBindingClassId Then
           BindingHandlerName = moHandlers.item(X).name
           Exit Property
        End If
    Next
  End If
  
End Property

'---------------------------------------------
'   Method: UPDATE SCRIPT
'
'   Action: Updates the script on the current
'   active binding.
'
'   Parm: (string) Script path and Name
'
'   Return: Boolean Success (S_OK)
'
'   CLASS GROUP: EVENTS
'--------------------------------------
Public Function UpdateScript(ByVal ScriptPath As String) As Boolean
   
   On Error GoTo UpdateScriptFail
   
   'Default is failure
   UpdateScript = False
   
   Dim ofield As Object
   Dim oMsg As Object
   
   If Not moBinding Is Nothing Then
         
         'Get CDO message for writing the script to
         Set oMsg = moSession.GetMessage(moBinding.EntryID, Null)
         
         'Update Script
         Set ofield = oMsg.Fields.Add(PR_EVENT_SCRIPT, "script")
         ofield.ReadFromFile ScriptPath
         
         oMsg.Subject = oMsg.Subject  'Dirty the cdo msg
         oMsg.Update
         
         'Save event object changes.
         moBinding.SaveCustomChanges oMsg
         moBinding.SaveChanges
         moBoundFolder.SaveChanges
         Set oMsg = Nothing
         UpdateScript = True
         
         Set oMsg = Nothing
      End If

'Jump around code if error occurs
UpdateScriptFail:
   
   Set ofield = Nothing
   Set oMsg = Nothing
   
End Function

'--------------------------------------------------------
'   Method: GET SCRIPT
'
'   Action: Gets a script from the agent and
'   places it in a file specified. This is the
'   standard method of getting the script using
'   an ole write to file method.
'
'   Parm: (string) Path and Name or script
'
'   Return: Boolean Success
'
'   CLASS GROUP: EVENTS
'--------------------------------------------------------
Public Function GetScript(ByVal sScriptPath As String) As Boolean

   'Default is failure
   GetScript = False
   If Not moBinding Is Nothing Then
      Dim oMsg As Object
      Dim ofield As Object
      
      'Get CDO Message to get the script from.
      Set oMsg = moSession.GetMessage(moBinding.EntryID, Null)
      
      'Update Script
      Set ofield = oMsg.Fields(PR_EVENT_SCRIPT)
      ofield.WriteToFile sScriptPath
      Set ofield = Nothing
      Set oMsg = Nothing
      GetScript = True
   End If

End Function

'--------------------------------------------
'   Method: DELETE
'
'   Action: Deletes the binding from the bound
'   folder if it has the proper entry id.
'
'   Parm: (string)   Entry ID of Agent
'
'   CLASS GROUP: EVENTS
'--------------------------------------
Public Function Delete(ByVal sEntryID As String) As Boolean
    
    On Error GoTo DeleteErr
    
    If Not moBindings Is Nothing Then
      
      Dim bFound As Boolean
      Dim item As Object
      
      Delete = False
      
      For Each item In moBindings
         If item.EntryID = sEntryID Then
            moBindings.Delete item     'Delete Binding
            moBoundFolder.SaveChanges
            Delete = True
         End If
      Next
      
    End If
    
    Set item = Nothing
    
    Exit Function
    
DeleteErr:
    
    Err.Raise Err.Number, "Delete Agent"
    
End Function

'---------------------------------------------
'   Prop: ACTIVE STATUS
'
'   Action: Get the active status of the
'   current active binding.
'
'   Return: Active Status Boolean
'
'  CLASS GROUP: EVENTS
'---------------------------------------------
Public Property Get ActiveStatus() As Boolean
   If Not moBinding Is Nothing Then
      ActiveStatus = moBinding.Active
   End If
End Property

'-----------------------------------------------------
'   Method: MODIFY AGENT
'
'   Action: Modifies the active binding in the current
'           folder.
'
'   Parm: Name of Agent  (Blank = don't change)
'         Event Mask (0-15)  (required)
'         ScriptPath and Name (ie: C:\ducks\myscript.txt) (Blank= don't change)
'         Class Id string: "SCRIPT" or "ROUTING" use internal class id.
'                          blank is don't change, otherwise use specified ID.
'         Active: True or False (required)
'
'
'   Return: Boolean Success (S_OK)
'
'  CLASS GROUP: EVENTS
'-----------------------------------------------------
Public Function ModifyAgent(ByVal name As String, ByVal EventMask As Variant, ByVal sScriptPathname As String, ByVal sClassID As String, ByVal bActive As Boolean) As Boolean
    
    On Error GoTo ModifyErr
    
    Dim oMsg As Object          'Message Object
    Dim ofield As Object
    
    'Default is failure
    ModifyAgent = False
    
    If Not moBinding Is Nothing Then
       
       'Update Name
       If name <> "" Then
          moBinding.name = name
       End If
       
       'Update Event Mask (required)
       moBinding.EventMask = EventMask
       
       'Active Setting (Required)
       moBinding.Active = bActive
       
       'If the classId is blank then don't change
       'If "SCRIPT" then script handler Id
       'if "ROUTING" then routing class id
       'otherwise use Id passed in.
       If sClassID <> "" Then
            If sClassID = "SCRIPT" Then
                 moBinding.HandlerClassID = SCRIPT_HANDLER_CLASS_ID
            ElseIf sClassID = "ROUTING" Then
                 moBinding.HandlerClassID = ROUTING_CLASS_ID
            Else
                 moBinding.HandlerClassID = sClassID
            End If
       End If
       
       moBinding.SaveChanges
       
       'Get Cdo Msg interface for updating the script.
       Set oMsg = moSession.GetMessage(moBinding.EntryID, Null)
       
       'Update Script
       If sScriptPathname <> "" Then
           Set ofield = oMsg.Fields.Add(PR_EVENT_SCRIPT, "Script")  'Script text gets replaced
           ofield.ReadFromFile sScriptPathname
       End If
       
       'Add routing agent property if routing type
       If sClassID = "ROUTING" Or sClassID = ROUTING_CLASS_ID Then
          oMsg.Fields.Add "RoutingAgent", VT_BOOL, True
       End If
       
       'Update Visible Name
       If name <> "" Then
           oMsg.Subject = name  'Set visible name
       End If
       
       oMsg.Update
          
       'Save alll custom changes
       moBinding.SaveCustomChanges oMsg
       moBinding.SaveChanges
       moBoundFolder.SaveChanges
      
       ModifyAgent = True  'Success
       
    End If

'---------
ModifyErr:
       
    Set ofield = Nothing
    Set oMsg = Nothing

End Function


'-----------------------------------------------------
'   Method: CREATE AGENT
'
'   Action: Creates any type of agent in the active
'   folder
'
'   Parm: Name of Agent
'         Event Mask (0-15)
'         ScriptPath and Name (ie: C:\ducks\myscript.txt)
'         Class Id string: If blank or "SCRIPT" then default script
'                          class id or if "ROUTING" then routing
'                          class id or otherwise use as class id.
'
'   Return: Error Number
'
'   CLASS GROUP: EVENTS
'-----------------------------------------------------
Public Function CreateAgent(ByVal name As String, ByVal EventMask As Variant, ByVal sScriptPathname As String, ByVal sClassID As String, ByVal bActive As Boolean) As Integer
    
    On Error GoTo CreateErr
    
    Dim oMsg As Object          'Message Object
    Dim ofield As Object
    Dim oSchedule As Object
       
    CreateAgent = False
    
    If Not moBindings Is Nothing Then
       'Add binding to bindings collection
       Set moBinding = Nothing
       Set moBinding = moBindings.Add
       
       'Fill in binding info.
       moBinding.name = name
       moBinding.Active = bActive
       moBinding.EventMask = EventMask
       
       'If the classId is blank then use the standard scripthandlerID.
       'or if the classid is set to "ROUTING" then use the internal
       'routing class id.
       If sClassID = "" Or sClassID = "SCRIPTHANDLER" Then
            moBinding.HandlerClassID = SCRIPT_HANDLER_CLASS_ID
       ElseIf sClassID = "ROUTING" Then
            moBinding.HandlerClassID = ROUTING_CLASS_ID
       Else
            moBinding.HandlerClassID = sClassID
       End If
            
       
       'This sets the schedule to be an all day event
       'It fires every hour and the default is type 1(hourly)
       'days are monday - friday
       Set oSchedule = moBinding.Schedule
       With oSchedule
         .Interval = 60
         .Type = 1
         .Days = 127
         .StartTime = 0
         .EndTime = 0.99999
       End With
      
       'Must save or message won't exist to get it to
       'attach a CDO custom property to it.
       moBinding.SaveChanges
       
       'Get Cdo Msg interface for updating the script.
       Set oMsg = moSession.GetMessage(moBinding.EntryID, Null)
       
       'Update Script
       Set ofield = oMsg.Fields.Add(PR_EVENT_SCRIPT, "Script")  'Script text gets replaced
       ofield.ReadFromFile sScriptPathname
       
       'Add routing agent property if routing class
       If moBinding.HandlerClassID = ROUTING_CLASS_ID Then
          oMsg.Fields.Add "RouteAgent", VT_BOOL, True
       End If
       
       oMsg.Subject = name  'Set visible name
       oMsg.Update
          
       'Save all plus custom changes
       moBinding.SaveCustomChanges oMsg
       moBinding.SaveChanges
       moBoundFolder.SaveChanges
    
    End If
    
    CreateAgent = True
    
    Exit Function

'---------
CreateErr:
          
    Set ofield = Nothing
    Set oMsg = Nothing
    Set oSchedule = Nothing
    
    Err.Raise Err.Number, "Create Agent", Err.Description
    
End Function

'----------------------------------------------
'   Property: FOLDER
'
'   Action: Returns a CDO folder object for the
'   currently active folder.
'----------------------------------------------
Public Property Get Folder() As Object
   If Len(msFolderID) <> 0 And Not moSession Is Nothing Then
      Set Folder = moSession.GetFolder(msFolderID, Null)
   Else
      Set Folder = Nothing
   End If
End Property

'--------------------------------------
'   Method: GET BINDING BY EID
'
'   Action: Find a binding by it's EID
'   This is a UNIQUE search.
'
'   Parm: (str) Message Entry ID
'
'   Return: Boolean Success
'--------------------------------------
Public Function GetBindingbyEID(ByVal sEntryID As String) As Boolean
      
      'Default is failure to find
      GetBindingbyEID = False
      
      'Verify binding index is within range, and if so then get binding
      For Each item In moBindings
         If item.EntryID = sEntryID Then
            Set moBinding = item
            GetBindingbyEID = True
            Exit Function
         End If
      Next
      
End Function

'--------------------------------------
'   Method: GET BINDING BY INDEX
'
'   Action: Find a binding by it's index.
'   This is exposed but the name search
'   method is preferred unless a name
'   isn't going to be unique.
'
'   Parm: (int) Index in the bindings collection
'
'   Return: Boolean Success
'
'  CLASS GROUP: EVENTS
'--------------------------------------
Public Function GetBindingbyIndex(ByVal Index As Integer) As Boolean
      
      'Default is failure to find
      GetBindingbyIndex = False
      
      'Verify binding index is within range, and if so then get binding
      If Index <= moBindings.Count And Index > 0 Then
         Set moBinding = moBindings.item(Index)
         GetBindingbyIndex = True
      End If
      
End Function

'------------------------------------------------
'   Method: GET BINDING NAME
'
'   Action: Get a binding by Agent Name
'
'   Note: It matches first one if duplicates exist.
'
'   Parm: (string)    Agent Name to search for
'         (boolean)   Exact match (true) or match first
'
'   Return: Boolean Success
'
'   CLASS GROUP: EVENTS
'------------------------------------------------
Public Function GetBindingByName(ByVal name As String, ByVal bExact As Boolean) As Boolean
      
      Dim Index As Integer
      Dim bFound As Boolean
      Dim iFirstMatchIndex As Integer
      
      GetBindingByName = False
      
      'Interate thorough bindings and take first match.
      For Index = 1 To moBindings.Count
         Set moBinding = moBindings.item(Index)
         If name = moBinding.name Then
            If bFound And bExact Then
               'Already located a name, fail as duplicate since exact search is on
               Set moBinding = Nothing
               Exit Function
            Else
               bFound = True
               iFirstMatchIndex = Index
               If Not bExact Then
                  'not exact search just exit
                  GetBindingByName = True
                  Exit Function
               End If
            End If
         End If
      Next
     
      If bFound Then
          'exact search only turned up one binding by the name specified.
          Set moBinding = moBindings.item(iFirstMatchIndex)
          GetBindingByName = True
          Exit Function
      End If
      
      Set moBinding = Nothing  'If it fails set binding to nothing.
      
End Function

'--------------------------------------
'  Prop: BINDING COUNT
'
'  Action: Gets the number of bindings
'  in the active folder
'
'  Return: (Integer) Count
'
'  CLASS GROUP: EVENTS
'--------------------------------------
Public Property Get BindingCount() As Integer
      If Not moBindings Is Nothing Then
          BindingCount = moBindings.Count
      Else
          BindingCount = 0
      End If
End Property

'-----------------------------------------------
'  Method: INITIALIZE EVENTS
'
'  Action: The first method that should always
'  be called to initialize the event class properly
'  It creates the events object (using ESCONF.DLL)
'  and assigns the CDO Session to the events object.
'
'  Return: (bool) Success or Fail
'
'  CLASS GROUP: EVENTS
'-----------------------------------------------
Public Function InitializeEvents() As Long

If Not moSession Is Nothing Then
   On Error GoTo EventFail
   Set moEvents = CreateObject("MSExchange.Events")
   moEvents.Session = moSession.Session
   Set moHosts = moEvents.Hosts
   If moHosts.Count > 0 Then
      Set moHandlers = moHosts.item(1).Handlers
   Else
      Set moHandlers = Nothing
   End If
   mbPermissions = True
Else
   InitializeEvents = ERR_NO_SESSION
   Err.Clear
End If

Exit Function

'----------
EventFail:

   'Trap Failure to create the events object
   'Usually means that esconf.dll isn't registered or the
   'registry entry is corrupt.
   Select Case Err.Number
      Case VB_PERMISSIONS_DENIED  '70
         InitializeEvents = ERR_PERMISSIONS_DENIED
         Err.Clear
      Case VB_ACTIVE_X_CANT_CREATE '429
         InitializeEvents = ERR_ESCONF_SETUP
         Err.Clear
      Case CdoE_CALL_FAILED
         InitializeEvents = CdoE_CALL_FAILED
         Err.Clear
      Case Else
         InitializeEvents = ERR_SYSTEM_ERROR
         Err.Raise Err.Number, "EventClass", Err.Description
   End Select
   
End Function

'--------------------------------------------
'   Method: INITIALIZE FOLDER
'
'   Action: Sets the active folder
'
'   Note: Also checks for valid Session, Events
'   objects, vData and set permissions flag.
'
'   Return: (boolean) Success
'
'   CLASS GROUP: EVENTS
'---------------------------------------------
Public Function InitializeFolder() As Integer
    
    On Error Resume Next
    
    InitializeFolder = False
    mbPermissions = False
    
    If moEvents Is Nothing Then
       InitializeFolder = ERR_EVENTS_NOT_INITIALIZED
    End If
    
    If Len(msFolderID) > 0 Then
       
       'Get the cdo folder associated with the ID
       Set moFolder = moSession.GetFolder(msFolderID, Null)
       
       'Remove references that may have used this folder
       Set moBinding = Nothing        'Binding Object
       Set moBindings = Nothing       'Bindings Object
       Set moBoundFolder = Nothing    'Bound folder object
       
       'Get Bindings
       Set moBoundFolder = moEvents.BoundFolder(moFolder, 1)
       'err 70 and 424
       'If any errors then deny permissions quietly
       If Err = VB_PERMISSIONS_DENIED Or Err = VB_OBJECT_REQUIRED Then
          Err.Clear
          moBoundFolder = Nothing
       Else
          Set moBindings = moBoundFolder.Bindings
          mbPermissions = True
          InitializeFolder = True
       End If
       
    Else
       InitializeFolder = ERR_FOLDER_ID_NOT_SET
    End If
    
End Function

'*******************************************************************
'            ROUTEMAP CLASS GROUP METHODS/PROPERTIES
'*******************************************************************

'-----------------------------------------------
'  Prop: IS ROUTE AGENT
'
'  Action: Is the current binding a Route Agent ?
'
'  Returns: (boolean) True or False
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Property Get IsRouteAgent() As Boolean
   If Not moBinding Is Nothing Then
       IsRouteAgent = BindingCheckPropExist("RouteAgent")
   Else
       IsRouteAgent = False
   End If
End Property

'-----------------------------------------------
'  Prop: MAP MSG EID
'
'  Action: Get the Entry ID of the Map Msg
'
'  Returns: (string) Entry ID
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Property Get MapMsgEID() As String

If Not moMapMsg Is Nothing Then
   MapMsgEID = moMapMsg.ID
Else
   MapMsgEID = ""
End If

End Property

'-----------------------------------------------
'  Method: CREATE ROW
'
'  Action: Create an IROW object
'
'  Returns: IROW object as variant (must be variant)
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Function CreateRow() As Variant
   Set moRow = Nothing
   Set moRow = CreateObject("exrt.row")
   Set CreateRow = moRow
End Function

'-----------------------------------------------
'  Prop: ROW
'
'  Action: Get the current row object
'
'  Returns: IROW object as variant (must be variant)
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Property Get Row() As Variant
   Set Row = moRow
End Property

'-----------------------------------------------
'  Prop: MAP TYPE
'
'  Action: Gets the type of map: Agent, Msg
'
'  Returns: Integer of map type 1,2
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Property Get MapType() As Integer
   MapType = miMapType
End Property

'-----------------------------------------------
'  Method: GET BINDING MSG
'
'  Action: Get the binding agent msg if available
'          and update private variables
'
'  Return: Boolean Success
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Function GetBindingMsg() As Boolean
   
   Dim bFound As Boolean
   
   GetBindingMsg = False
   
   'make sure we have an object to work with
   If moBinding Is Nothing Then
      Exit Function
   End If
   
   Set moMap = Nothing
   
   'Find the Routing Agent Binding, which will set the event
   'class to the proper binding.
   bFound = GetBindingWithProp("RouteAgent", True)
   
   'Route Type Property is not used with Routing Binding Agent.
   miMapType = BINDING_MAP
   
   If Not bFound Then
      'Clear out private variables
      msMsgEntryID = ""
      Set moMapMsg = Nothing
      Exit Function
    
   Else
      GetBindingMsg = True
      
      'Get CDO message associated with the map
      Set moMapMsg = AgentMap.Session.GetMessage(moBinding.EntryID, Null)
      msMsgEntryID = moMapMsg.ID
   End If
End Function


'-----------------------------------------------
'  Method: GET ROUTING MSG
'
'  Action: Get the Routing Map Message and update
'  private variables.
'
'  Return: Boolean True/False
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Function GetRoutingMsg() As Boolean

   On Error Resume Next
   
   Dim oFolder As Object       'Folder Object
   Dim lx As Long              'Loop Variable
   Dim vTempField As Variant   'Temporary Field Value Variant
   Dim bFound As Boolean       'Boolean Found Variable
   
   bFound = False
   
   GetRoutingMsg = False
   
   'Get the active folder object
   Set oFolder = moSession.GetFolder(msFolderID, Null)
   If oFolder Is Nothing Then
      Exit Function
   End If
   
   'Clear internal variables
   Set moMap = Nothing
   
   miMapType = ROUTING_MAP
   
   If oFolder.HiddenMessages.Count > 0 Then
      For lx = 1 To oFolder.HiddenMessages.Count
         Set moMapMsg = oFolder.HiddenMessages.item(lx)
           
         'Find message with RouteType Field
         vTempField = moMapMsg.Fields("RouteMap")
         
         If Err = CdoE_NOT_FOUND Then
            'No property on this message
            Err.Clear
         Else
            bFound = True
            Exit For
         End If
      Next
   Else
      'No Hidden Messages Found
   End If
   
   GetRoutingMsg = bFound
   
   If Not bFound Then
      'Clear moMapMsg
      Set moMapMsg = Nothing
   End If
   Set oFolder = Nothing
   
End Function


'---------------------------------------------
'  Method: IS WIZARD MAP
'
'  Action: Find out if the RouteType property
'  exists and is set to parallel or sequential
'  which indicates it's a wizard generated map.
'
'  Return: Boolean True or False
'
'  CLASS GROUP: MAP
'---------------------------------------------
Public Function IsWizardMap() As Boolean
    
    On Error Resume Next
    
    Dim vtemp As Variant

    vtemp = moMapMsg.Fields(ROUTE_TYPE_PROP)
    If Err = CdoE_NOT_FOUND Then
        'No routetype property ?
        Err.Clear
        IsWizardMap = False
    Else
        If vtemp = PARALLEL_ROUTING Or vtemp = SEQUENTIAL_ROUTING Then
           IsWizardMap = True
        End If
    End If
End Function

'---------------------------------------------
'  Method: SAVE MAP
'
'  Action: Save the currently map onto the
'  map msg.
'
'  CLASS GROUP: MAP
'---------------------------------------------
Public Function SaveMap() As Boolean
   
   Const DELETED = False
   Const SAVED = True
   
   Dim oTemp As Object
   
   If Not moMap Is Nothing Then
      
      If moMap.ActivityCount = 0 Then
         'Delete Map on Message
         moMap.DeleteMap
         
         'NOTE: The deletemap method on the map object only deletes the
         'cached version of the map and doesn't delete the map table
         'stored on the message. CDO is used below to completely
         'remove the map from the message.
         Set oTemp = moMapMsg.Fields.item("RTMap Table")
         oTemp.Delete
         
         SaveMap = DELETED
      Else
         'Save Map
         moMap.SaveMap
         SaveMap = SAVED
      End If
      
      'Dirty the CDO Msg Object or save won't occur.
      moMapMsg.Subject = moMapMsg.Subject
      
      
      'If a Binding install map then inform events to save
      'custom changes. Save prop changes is an event function.
      If miMapType = BINDING_MAP Then
         moBinding.name = moBinding.name  'Dirty the message
         moBinding.SaveCustomChanges moMapMsg
         moBinding.SaveChanges
         moBoundFolder.SaveChanges
      End If
      
      'Must do CDO Update
      moMapMsg.Update
            
   End If
   
End Function

'---------------------------------------------
'  Method: INSERT ROW
'
'  Action: Insert a row in an existing map
'
'  Return: Integer Error Number (0=no error)
'
'  CLASS GROUP: MAP
'---------------------------------------------
Public Function InsertRow(ByVal IRow As Variant) As Integer

   On Error Resume Next
   
   If Not moMap Is Nothing Then
      moMap.InsertActivity -1, IRow
      If Err Then
         If Err = 5 Then
            InsertRow = ERR_MAP_ROW_INVALID
         Else
            InsertRow = Err.Number
            Exit Function
         End If
      Else
         InsertRow = NO_ERROR
      End If
   Else
      InsertRow = ERR_INSERT_ROW_NO_VALID_MAP
   End If
End Function

'---------------------------------------------
'  Method: REINITIALIZE MAP
'
'  Action: Reopen map and clean out for writing
'  new map.
'      1. Set local map object to nothing
'      2. Creates a new map object
'      3. Assign message.
'      4. Save Empty map
'      5. Open for readwrite.
'
'  Return: Boolean Success/Fail
'
'  CLASS GROUP: MAP
'---------------------------------------------
Public Function ReinitializeMap() As Boolean
   
   ReinitializeMap = False
   
   If Not moMapMsg Is Nothing Then
      Set moMap = Nothing
      Set moMap = CreateObject("exrt.map")
      moMap.Message = moMapMsg
      moMap.SaveMap
      moMap.OpenMap TBL_OPEN_READWRITE
      ReinitializeMap = True
   End If
End Function


'-----------------------------------------------
'  Prop: MAP
'
'  Action: Get the class map object
'
'  Return: Map Object
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Property Get Map() As Object
    If Not moMap Is Nothing Then
       Set Map = moMap
    End If
End Property

'-----------------------------------------------
'  Prop: MAP MSG
'
'  Action: Get the class map msg object
'
'  Return: Map Message Object
'
'  CLASS GROUP: MAP
'-----------------------------------------------
Public Property Get MapMsg() As Object
    If Not moMapMsg Is Nothing Then
       Set Map = moMapMsg
    End If
End Property

'-----------------------------------------------
'  Method: GetMap
'
'  Action: Gets the map information for the
'  current active map message.
'     1. CREATES MAP OBJECT
'     2. Get msg where map will be stored.
'     3. Assigns message to the map
'     4. Performs and OPEN MAP on the message (open readwrite)
'
'  NOTE: We have no way of knowing if a map does or
'  doesn't exist on a message, but as far as the routing
'  engine is concerned a empty map is equivalent to no map.
'
'  Parm:  (str) Target [ROUTING, BINDING]
'
'  Returns: (integer) err number (0 = no error)
'
'  CLASS GROUP: MAP
'----------------------------------------------
Public Function GetMap(ByVal sTarget As String) As Integer

   On Error Resume Next
    
   Dim oFolder As Object
   
   GetMap = NO_ERROR
    
   Set oFolder = moSession.GetFolder(msFolderID, Null)
   If oFolder Is Nothing Then
      Exit Function
   End If
   
   'Create Map Object and trap error
   Set moMap = CreateObject("exrt.map")
   If Err Then
      GetMap = ERR_EXRTOBJ_SETUP
      Exit Function
   End If
   
   If sTarget = "ROUTING" Then
        
        'Add map message to message collection if one doesn't exist.
        If moMapMsg Is Nothing Then
            Set moMapMsg = oFolder.HiddenMessages.Add("Agent Editor Route", "", "IPM.Note", CdoNormal)
            If Err Then
               GetMap = ERR_AgentMap_ACTIVE_FOLDER_ID_NOT_SET
               Exit Function
            End If
            moMapMsg.Fields.Add "RouteMap", VT_BOOL, True
            moMapMsg.Update
        End If
        If Err Then
            GetMap = ERR_UNABLE_TO_ADD_ROUTING_MAP_MSG
            Exit Function
        End If
        
        moMap.Message = moMapMsg
        moMap.OpenMap TBL_OPEN_READWRITE
      
    ElseIf sTarget = "BINDING" Then
        If Not moMapMsg Is Nothing Then
            moMap.Message = moMapMsg
            moMap.OpenMap TBL_OPEN_READWRITE
        Else
            GetMap = ERR_MAP_AGENT_DOESNT_EXIST
        End If
    Else
       'Unmatched Argument
       GetMap = ERR_ARGUMENT_ERROR
    End If
    
End Function

'-----------------------------------------
'  PRIVATE Sub: Class_Initialize
'
'  Performs class initialization jobs
'-----------------------------------------
Private Sub Class_Initialize()
  
Set moRow = Nothing
Set moMap = Nothing
Set moMapMsg = Nothing

mbPermissions = False
mbLoggedOn = False
msFolderID = ""

End Sub

'-----------------------------------------
'  PRIVATE Sub: Class_Terminate
'
'  Performs class termination jobs
'-----------------------------------------
Private Sub Class_Terminate()

'Release all object in proper order.
Set item = Nothing

Set moRow = Nothing
Set moMap = Nothing
Set moMapMsg = Nothing
Set moBinding = Nothing        'Binding Object
Set moBindings = Nothing       'Bindings Object
Set moBoundFolder = Nothing    'Bound folder object
Set moFolder = Nothing         'CDO Folder Object
Set moHandlers = Nothing       'Handlers of 1st Host (normally only one)
Set moHosts = Nothing          'Hosts Object
Set moEvents = Nothing         'Events Object
Set moSession = Nothing


End Sub

