        ��  ��                  h  (   T E X T   ��Y      0	        <SCRIPT RunAt=Server Language=VBScript>

'------------------------------------------------------------------------------
'FILE DESCRIPTION: Exchange Server Event Script
'------------------------------------------------------------------------------

Option Explicit 

'------------------------------------------------------------------------------
' Global Variables
'------------------------------------------------------------------------------

'------------------------------------------------------------------------------
' Event Handlers
'------------------------------------------------------------------------------

' DESCRIPTION: This event is fired when a new message is added to the folder
Public Sub Folder_OnMessageCreated
End Sub

' DESCRIPTION: This event is fired when a message in the folder is changed
Public Sub Message_OnChange
End Sub

' DESCRIPTION: This event is fired when a message is deleted from the folder
Public Sub Folder_OnMessageDeleted
End Sub

' DESCRIPTION: This event is fired when the timer on the folder expires
Public Sub Folder_OnTimer
End Sub

</SCRIPT>T; (   T E X T   ��X      0	        Attribute VB_Name = "Module1"
<SCRIPT RUNAT=Server Language=VBScript>

'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
'WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
'INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
'PURPOSE
'
'       Copyright (C) 1998 Microsoft Corporation
'
'
' Description: This VB script is the companion to the Microsoft Exchange
' Routing Wizard. It is the script that gets installed in a routing folder
' which serves as the hub for a route. It can handle both both sequential
' and parallel routes and implements all of the functions needed by the
' Microsoft Exchange Routing Wizard for all variations on these routes.
'

' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'
'       Routing Script Commands
'
'       - Routing Functions
'            - Route_Send
'            - Route_Receive
'            - Route_IsApprovalMsg
'            - Route_IsApprovedTable
'            - Route_AutoApprove
'            - Route_AutoReject
'            - Route_FinalizeReport
'            - Route_Consolidate
'            - Route_PreProcessing
'            - Route_NOP
'            - Route_IsNDR
'            - Route_IsReceipt
'            - Route_IsInvalidRecip
'            - Route_IsPost
'            - Route_CreateNote
'
'       - Utility Functions
'            - InitializeMsg
'            - InitializeVoteTable
'            - InitializeObjects
'            - InitializeCacheRecip
'            - GetCacheName
'            - GetCacheAddr
'            - PutCacheRecip
'            - DecCacheRecip
'
'       - Trace Functions
'            - TraceHeader
'            - TraceOutput
'            - TraceAppend
'            - ErrorCheck
'
' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Option Explicit

' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'      TRACE FLAGS
'
'   It is important to note that Trace Messages are sent to the INBOX of
'   the agent installer. If you turn on TRACE_FLAG then the routing script
'   will generate a LOT of trace messages.
' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

' Set the FLAG to true for trace messages
' Set the LOG to true for Event Viewer trace messages
Const TRACE_FLAG = False
Const TRACE_LOG = False

' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'       Global Variable Declarations
' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Dim g_bstrWFSendSubject          'Treated Subject String
Dim g_bstrWFSendBody             'Treated Body String

Dim g_bstrTrace                  'Trace String

Dim g_bstrReplyToName            'Reply To Name (Routing folder name)
Dim g_bstrReplyToID              'Reply To ID (Folder address entry ID)
Dim g_bstrReplyToAddr
Dim g_bstrInMsgSubject           'Truncated Incomming Mesage Subject
Dim g_bstrRouteType              'Value of "RouteType" Custom Prop
Dim g_bstrMsgSender              'Message Sender (from initializeobjects)

' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'       Global Booleans
' +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Dim g_boolIsPrivateStore         'True means private store otherwise public
Dim RT_AUTOADD                   'AutoAdd Prop on Recipient Table if True

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'         PROPERTY/ARGUMENT CONSTANTS
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Const g_PR_REPLY_RECIPIENT_NAMES = &H50001F
Const g_PR_REPLY_RECIPIENT_ENTRIES = &H4F0102
Const g_PR_ATTACH_LONG_FILENAME = &H3707001F
Const g_PR_ATTACH_FILENAME = &H3704001F
Const g_PR_ATTACH_EXTENSION = &H3703001F
Const g_PR_ADDRESS_BOOK_ENTRYID = &H663B0102
Const g_PR_INTERNET_ARTICLE_NUMBER = &HE230003
Const g_PR_MESSAGE_ATTACHMENTS = &HE13000D
Const g_PR_BODY = &H10000000  'Set to Generic for JPN (mapi will resolve to unicode)
Const g_PR_SMTP_ADDRESS_W = &H39FE001F
Const g_PR_CREATOR_NAME = &H3FF8001F

Const CdoE_INVALID_PARAMETER = &H80070057
Const CdoE_NOT_FOUND = &H8004010F

Const CdoTo = 1
Const CdoCc = 2
Const CdoBcc = 3

Const PR_STORE_SUPPORT_MASK = &H340D0003

Const VT_BSTR = 8      'OLE String
Const VT_I2 = 2        'OLE Integer
Const VT_BOOL = 11     'OLE Boolean

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'         ERROR CONSTANTS
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

'Not Currently Used

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'         GLOBAL OBJECTS
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Dim g_oMsgIn          'Incomming Message Object
Dim g_oProcInstance   'Process Instance
Dim g_oPIMsg          'Process Instance Message Object
Dim g_oSession        'Session Object
Dim g_oFolder         'Routing Folder Object
Dim g_oVoteTable     'VoteTable Object
Dim g_oAgentAddEntry  'Address Entry Object use for inbox mailings.
Dim g_oFolderAddEntry 'Address Entry object of Folder

Dim Item              'Used with For Each Statements must be explicitly declared

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'
'   Sub:  Route_PreProcessing
'   Area: Core Routing
'   Desc: Perform Initalization of the Route
'         1. Morph any IPM.Document to IPM.Note
'         2. Morph any IPM.Post to IPM.Note
'
'   Note: Assume this is a new Route at this point and all
'         information available from the engine is valid.
'   Parm: ByRef BoolSuccess
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
Sub Route_PreProcessing(boolSuccess)

    On Error Resume Next
    
    Dim boolRes    'Boolean Result Variable
    Dim MsgType    'Message Type String
    Dim vTemp      'Variant Temp
    
    Call TraceHeader("PreProcessing")
    
    

    
   boolRes = InitializeBaseObjects  'Lean and mean version of initializeobjects
   If Not boolRes Then
       Call TraceAppend("InitializeBaseObjects Failed")
       boolSuccess = False
     
    Else
       Set g_oProcInstance = RouteDetails.ProcInstance
       Set g_oPIMsg = g_oProcInstance.Message
       
       '-------------------
       ' Initialize Recipient Cache
       '
       ' Note: InitializeCacheRecip doesn't update the PIM it's
       ' done below
       Call InitializeCacheRecip
              
       
       MsgType = g_oPIMsg.Type
       Call TraceAppend("Message type of Pim is: " & g_oPIMsg.Type)
    
       'Morph any document class into IPM.Note class
       If InStr(1, MsgType, "IPM.Document") Then
          g_oPIMsg.Type = "IPM.Note"
          g_oPIMsg.Recipients.AddMultiple g_oFolder.Name, CdoTo
          g_oPIMsg.Fields.Add "Morph", VT_BOOL, True
          If Not Err Then
            boolSuccess = True
          Else
            Call ErrorCheck("g_oPIMsg.Update")
            boolSuccess = False
          End If
       Else
          'Check if Morph field exists, if not then add it and
          'set Morph field to false otherwise leave it as is.
          vTemp = g_oPIMsg.Fields("Morph")
          If Err Then
               g_oPIMsg.Fields.Add "Morph", VT_BOOL, False
               Err.Clear
          End If
       End If
       
       '-------------------
       '  Reject Status is always cleared
       g_oPIMsg.Fields.Add "StatusMsg", VT_BSTR, "<CLEAR>"
       
       '-----------------------------
       '  Update once for all changes
       g_oPIMsg.Update
       
    End If
    
    If Err Then
        Call ErrorCheck("PreProcessing")
    End If
    
    Call TraceAppend("PreProcessing Returns " & boolSuccess)
    Call traceOutput("PreProcessing", 0)
    
    'Releases
    Set g_oProcInstance = Nothing
    Set g_oPIMsg = Nothing
    Call ReleaseBaseObjects
    
End Sub

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'   Sub:  Route_IsOOF
'   Area: Core Routing
'   Desc: Is the incomming out of office reply.
'   Parm: BoolSuccess
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Sub Route_IsOOF(boolSuccess)
  
  On Error Resume Next
  
  Dim boolRes 'Result Boolean
  
  Call TraceHeader("IsOOF")

  boolRes = InitializeBaseObjects  'Lean and mean version of initializeobjects

  If Not boolRes Then
     Call TraceAppend("InitializeBaseObjects Failed")
  
  Else
     'Get Message Type
     If g_oMsgIn.Type = "IPM.Note.Rules.OofTemplate.Microsoft" Then
        Call TraceAppend("Found OOF.")
        boolSuccess = True
     End If
  End If

  Call TraceAppend("IsOOF returns " & boolSuccess)
  Call traceOutput("IsOOF", 1)

  Call ReleaseBaseObjects
  
End Sub


'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'   Sub:  Route_IsPost
'   Area: Core Routing
'   Desc: Is the incomming note a post
'   Parm: BoolSuccess
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
Sub Route_IsPost(boolSuccess)
  
  On Error Resume Next
  
  Dim boolRes 'Result Boolean
  
  Call TraceHeader("IsPost")

  boolRes = InitializeBaseObjects  'Lean and mean version of initializeobjects
  If Not boolRes Then
     Call TraceAppend("InitializeBaseObjects Failed")
  
  Else
    'Get Message Type
    If g_oMsgIn.Type = "IPM.Post" Then
        Call TraceAppend("Found Post.")
        boolSuccess = True
    End If
  End If
  
  Call TraceAppend("IsPost returns " & boolSuccess)
  Call traceOutput("IsPost", 1)
  
  Call ReleaseBaseObjects
  
End Sub

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'   Sub:  Route_CreateNote
'   Area: Core Routing
'   Desc: Convert Post to Note and delete PIM
'   Parm: BoolSuccess
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
Sub Route_CreateNote(boolSuccess)
  
  On Error Resume Next
  
  Dim boolRes    'Result Boolean
  Dim oNewPIM    'New message Object
  Dim oWorkItem  'Workitem for embedding
  
  Call TraceHeader("CreateNote")

  'Always intializeobjects
  boolRes = InitializeObjects

  If Not boolRes Then
     Call TraceAppend("InitializeObjects Failed")
     
  Else
     Call TraceAppend("Morph Post to Note.")
     ' 1. Create Note (don't save yet)
     ' 2. Embed Current PIM into note.
     ' 3. Save Note
     Set oNewPIM = g_oFolder.Messages.Add(g_oPIMsg.subject, "", "IPM.Note", g_oPIMsg.Importance)
     '----
     Set oWorkItem = RouteDetails.WorkItem
     oWorkItem.Item = oNewPIM
     oWorkItem.EmbedMsg g_oPIMsg 'Embed into Item
     oNewPIM.Recipients.AddMultiple g_oFolder.Name, CdoTo
     oNewPIM.sender = g_oPIMsg.sender
     oNewPIM.Fields.Add "Morph", VT_BOOL, True
     
     '--- Update the PIM and save
     oNewPIM.Update
     
  End If
  
  'Trap any errors
  If Err Then
     Call ErrorCheck("CreateNote")
  Else
     Call TraceAppend("No errors detected on completion.")
  End If
  g_bstrInMsgSubject = "MORPHED"
  
  Call TraceAppend("CreateNote " & boolSuccess)
  Call traceOutput("CreateNote", 1)
  
  Set oWorkItem.Item = Nothing
  Set oWorkItem = Nothing
  Set oNewPIM = Nothing

  Call ReleaseGlobalObjects

End Sub


'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'   Sub:  Route_IsNDR
'   Area: Core Routing
'   Desc: Check for NDR Mail
'   Parm: BoolSuccess
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
Sub Route_IsNDR(boolSuccess)
  
  On Error Resume Next
  
  Dim boolRes 'Result Boolean
  Dim bstrMsgType ' Message Type
  
  Call TraceHeader("IsNDR")

  boolRes = InitializeBaseObjects  'Lean and mean version of initializeobjects
  If Not boolRes Then
     Call TraceAppend("InitializeBaseObjects Failed")
  
  Else
     'Only trap NDR
     bstrMsgType = g_oMsgIn.Type
     Call TraceAppend("MsgType = " & bstrMsgType)
     If InStr(1, bstrMsgType, "REPORT.") > 0 Then
        If InStr(1, bstrMsgType, ".NDR") > 0 Then
           boolSuccess = True
        End If
     End If
  End If

  Call TraceAppend("IsNDR returns " & boolSuccess)
  Call traceOutput("IsNDR", 2)
  
  Call ReleaseBaseObjects
  
End Sub

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'   Sub:  Route_IsReceipt
'   Area: Core Routing
'   Desc: Check for Delivery Recipts, Read Recipts, etc.
'   Parm: ByRef BoolSuccess
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
Sub Route_IsReceipt(boolSuccess)
  
  On Error Resume Next
  
  Dim boolRes         'Result Boolean
  Dim bstrMsgType     'Message Type
  
  Call TraceHeader("IsReceipt")
    
  'Important Initialize Objects
  boolRes = InitializeBaseObjects  'Lean and mean version of initializeobjects
  If Not boolRes Then
     Call TraceAppend("InitializeBaseObjects Failed")
  
  Else
     bstrMsgType = o_MsgIn.Type
     Call TraceAppend("MsgType = " & bstrMsgType)
     If InStr(1, bstrMsgType, "REPORT.") > 0 Then
        'Catch all types of reports except NDR
        If InStr(1, bstrMsgType, ".DR") > 0 Or InStr(1, bstrMsgType, ".RN") > 0 Or InStr(1, bstrMsgType, ".NRN") > 0 Then
           boolSuccess = True
        End If
     End If
  End If

  Call TraceAppend("IsReceipt returns " & boolSuccess)
  Call traceOutput("IsReceipt", 2)
  
  Call ReleaseBaseObjects
  
End Sub

'------------------------------------------------
'  Sub:   NOP
'  Area:  Core Routing
'  Desc:  Can be used as a No Operation place holder when
'         doing map modifications.
'-------------------------------------------------
Sub Route_NOP(boolSuccess)

If TRACE_LOG Then
   'No Operation
   script.response = "Script NOP Executed"
End If

End Sub

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'
'   Sub:  Route_Send
'   Area: Core Routing
'   Desc: Distributing mail to recipients
'   Parm:
'         bstrRNames   = Comma Delimited string of recipient names
'                       "<BLANK>" is originator, one recipient is serial
'         boolPIM     = Include Pim in Final Report
'         bstrText    = Body of Text or "<FINALIZE>"
'         boolAttach  = Attachment = "<ATTACH>", Link = Name of OWA Server
'         bstrRole    = <ROLE>, <RECIP>
'         boolSuccess = True, False  (BYREF)
'   Retn: None
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

Sub Route_Send(bstrRNames, bstrAddresses, boolPIM, bstrtext, bstrAttach, bstrRole, boolSuccess)

    'NOTE: bstrAddresses = "<Unused>" is a condition for Manager Role
    
    On Error Resume Next
    
    'General message objects
    Dim oMsgOut          'Outgoing Message Object
    Dim oRecip           'Recipient object
    Dim oRecCol          'Recipients Collection
    Dim oTemp            'Temporary Object considered bogus if out of sight
    Dim oParticipant     'Participant Object
    Dim oWorkItem        'WorkItem Object
    
    'Reply to Entries Variables
    Dim FlatLength       'Length of FlatEntry
    Dim bstrFlatEntry    'FlatEntry String
    Dim StructLength     'Length of complete Structure
    Dim bstrBlob         '-Binary- blob as a string
    
    'Role Variables
    Dim bstrResolveAddr  'Contains the ADDRESS of the role member
    
    'Return Variables
    Dim varRet           'Return Variant
    Dim boolRes          'Boolean Result
                           
    'Consolidation variables
    Dim PropArray        'Property Array for workitem
                        
    'Utility Strings
    Dim bstrLinkURL      'Link URL
    Dim bstrStatusMsg    'Failed Status String
        
    'Used to parse out bstrName, bstrAddress
    Dim tLocName         'current location in name string
    Dim tLocAddr         'current location in addr string
    Dim bstrNewRNames    'new recipient names string
    Dim bstrNewAddresses 'new recipient addresses string
    Dim bstrTempName     'temporary name string store
    Dim bstrTempAddr     'temporary address string store
            
    'Boolean Flags
    Dim boolFinalize     'Is this the Finalized Report
    Dim boolAttach       'Use Attachment or Link
    Dim boolOriginator   'Set to originator
    Dim boolResolveErr   'Error resolving message
    Dim boolMorphed      'Is the PIM Morphed from IPM.Doc
    Dim boolSendFail     'Failure To Properly prepare for sending
        
    Call TraceHeader("Send")
    Call TraceAppend(" Names       = " & "." & bstrRNames & ".")
    Call TraceAppend(" Addresses   = " & "." & bstrAddresses & ".")
    Call TraceAppend(" boolPIM     = " & boolPIM)
    Call TraceAppend(" bstrText    = " & bstrtext)
    Call TraceAppend(" bstrAttach  = " & bstrAttach)
    Call TraceAppend(" bstrRole    = " & bstrRole)
    Call TraceAppend(" boolSuccess = " & boolSuccess)
        
    'Set Flags (finalize, attachment, originator)
    If bstrtext = "<FINALIZED>" Then
       boolFinalize = True
    Else
       boolFinalize = False
    End If
    If bstrAttach = "<ATTACH>" Then
       boolAttach = True
    Else
       boolAttach = False
    End If
    If bstrRNames = "<BLANK>" Then
       boolOriginator = True
    Else
       boolOriginator = False
    End If
      
    'Initialize Common Objects used by script
    boolRes = InitializeObjects
            
    If Not boolRes Then
       Call TraceAppend("InitializeObjects Failed")

    Else
       boolMorphed = g_oPIMsg.Fields("Morph")
       If Err Then
           Call ErrorCheck("Unable to get morph Custom property.")
       End If
       Call TraceAppend("boolMorphed = " & boolMorphed)
       Err.Clear  'If for some reason property doesn't exist.
       
       'If it's the final route don't add wizard test info to body.
       boolRes = InitializeMsg(bstrtext, g_oPIMsg.subject)
              
       If Not boolRes Then
          'Fail silently, this error is trapped in initialize message.
          Call TraceAppend("InitializeMsg Failed")

       Else
          If Len(g_bstrWFSendBody) = 0 Then
             boolSuccess = False
             Call TraceAppend("Body is blank. Terminating Send Execution")
             
          Else
             
             '-----------------------------------------------
             '        CREATE OUTGOING MESSAGE
             '-----------------------------------------------
             Set oMsgOut = g_oSession.Outbox.Messages.Add(g_bstrWFSendSubject, "", "IPM.Note", g_oPIMsg.Importance)
             If Err Then
                'Can not add message to outbox, probably a delete agent installer
            
             Else
             '-----------------------------------------------
             '       SET ORIGINATOR TO PIM.SENDER IF REQUIRED
             '-----------------------------------------------
             '<BLANK> means get originator from the PImsg
             If boolOriginator Then
                bstrRNames = g_oPIMsg.sender.Name
                bstrAddresses = g_oPIMsg.sender.address
             End If
   
             '-----------------------------------------------
             '         VOTE BUTTON CREATION
             '-----------------------------------------------
             ' VoteTable Treatment for OUTLOOK use.
             ' Not attach if final report
             If Not boolFinalize Then
                boolRes = InitializeVoteTable
                If boolRes Then
                   g_oVoteTable.AddButtons oMsgOut, "Approve,Reject"

                Else
                   Call TraceAppend("VoteTable Failed to Initialize")
                End If

                Call ErrorCheck("VoteTable.AddButtons")
             End If
             
             
             '-----------------------------------------------
             '     ROLE RESOLUTION
             '
             '  Resolve the role and then let it drop through
             '  to recipient collection population code.
             '-----------------------------------------------
             '
             If bstrRole = "<ROLE>" Then
                
                bstrResolveAddr = GetCacheAddr()
                If Err Then
                   'Send to Originator
                   Call ErrorCheck("Unable to get originator prop. Fail on first recipient.")
                   bstrResolveAddr = g_oPIMsg.sender.address
                End If
                
                'If it is a manager role then pass the RName as member name
                If bstrRNames = "Manager" And bstrAddresses = "<Unused>" Then
                    bstrAddresses = bstrRNames
                    bstrRNames = ""
                End If
                
                
                Call TraceAppend("Role Processing")
                Call TraceAppend("  Name: " & bstrResolveAddr) 'use user addr instead of name
                Call TraceAppend("  Role: " & bstrAddresses)  'Use addr instead of name
                                
                Set oParticipant = g_oProcInstance.Participant
                If Err Then
                   Call ErrorCheck("exrt.participant")
                    
                Else
                   oParticipant.RoleName = bstrAddresses
                   oParticipant.MemberName = bstrResolveAddr
                   bstrRNames = oParticipant.ResolveRole
                   bstrAddresses = bstrRNames
                   Call TraceAppend("Resolved Role =" & bstrRNames)
                End If
             If Err Then
                boolResolveErr = True
                Call ErrorCheck(" Role Resolution Error Occured")
             End If
           End If
             
             
           '------------------------------------------
           '    RECIPIENT COLLECTION POPULATION
           '------------------------------------------
           '**RECIPIENTS TO THE MESSAGE ARE HANDLED HERE**
           '  -Both serial and parallel cases
           ' 1) First try to resolve against the name
           ' 2) Then try to use the address
           ' 3) If this fails don't send the mail.
           '
           Set oRecCol = oMsgOut.Recipients
           
           'Trap blank name/address user modified script errors
           If Len(bstrRNames) = 0 Or bstrRNames = " " Then
              boolResolveErr = True
              Call TraceAppend("Invalid bstrRNames")
              
           Else
              If Not boolResolveErr Then
               Do
                 'Parse out next name/address pair
                 If Len(bstrAddresses) <> 0 And bstrAddresses <> " " Then
                    tLocAddr = InStr(1, bstrAddresses, ";")
                    If (tLocAddr = 0) Then
                      bstrTempAddr = bstrAddresses
                    Else
                      bstrTempAddr = Left(bstrAddresses, tLocAddr - 1)
                    End If
                    bstrNewAddresses = Right(bstrAddresses, Len(bstrAddresses) - tLocAddr)
                 Else
                    bstrTempAddr = ""
                 End If
                 
                 tLocName = InStr(1, bstrRNames, ";")
                 If (tLocName = 0) Then
                   bstrTempName = bstrRNames
                 Else
                   bstrTempName = Left(bstrRNames, tLocName - 1)
                 End If
                 bstrNewRNames = Right(bstrRNames, Len(bstrRNames) - tLocName)
         
                 'Add one name at a time to the recipient collection so
                 '  use AddMultiple since it works best for address/name instead
                 '  of address entry type adds.
                 Set oRecip = oRecCol.Add(bstrTempName, , CdoTo)
                 oRecip.Resolve False
                 Call ErrorCheck("Tried to resolve on name - fail is ok, now try address -")
                 
                 'If name can't be resolved use address
                 If Not oRecCol.Resolved Then
                   oRecip.Delete
                   Call TraceAppend("Unable to resolve name: " & bstrTempName & ", trying address " & bstrTempAddr)
                   If bstrTempAddr = "" Or bstrTempAddr = " " Then
                      boolSendFail = True
                      Call TraceAppend("Can't use empty address to resolve so terminating send (typ ROLE problem).")
                   
                   Else
                      oRecCol.AddMultiple bstrTempAddr, CdoTo
                   
                      oRecCol.Resolve False
                      Call ErrorCheck("Tried to resolve on addr - fail is ok")
                      If Not oRecCol.Resolved Then
                        'Remove unresolved item. Iterate through recipients to find it.
                        For Each Item In oRecCol
                          If Item.Name = bstrTempAddr Then
                             Item.Delete
                             Exit For
                          End If
                        Next
                        Call TraceAppend("Not able to resolve name/address: " & bstrTempName & "/" & bstrTempAddr)
                        boolResolveError = True
                        
                      Else
                        Call TraceAppend("  Recipient Added: " & bstrTempAddr)
                      End If
                   End If
                 Else
                   Call TraceAppend("  Recipient Added: " & bstrTempName)
                 End If
                 bstrAddresses = bstrNewAddresses
                 bstrRNames = bstrNewRNames
               Loop Until (tLocName = 0 Or boolSendFail)
               End If
            End If
                        
            'Trap error related to role resolution
            If Err Or boolResolveErr Then
              Call ErrorCheck("Error Info:")
              Call TraceAppend(" A resolve or role error occurred. Not sending message.")
              boolResolveErr = True
            Else
              If oRecCol.Count = 0 Then
                 Call TraceAppend(" No resolved recipients, no mail sent")
                 boolResolveErr = True
              End If
            End If
             
            Call TraceAppend("BoolResolveErr = " & boolResolveErr)
            
            If boolResolveErr Then
               'Won't process attachments/etc if failure has occured
                         
            Else
             '-----------------------------------------
             '  ATTACHMENT/LINK PROCESSING/EMBEDDED MSG
             '-----------------------------------------
             ' Finalize or ATTACH embeds PIM other cases send link.
             'If ((boolAttach And Not boolFinalize) Or (boolPIM And boolFinalize)) Then
             Call TraceAppend("Attach/Link/Embedded msg processing")
             
             If boolAttach Then
               Set oWorkItem = RouteDetails.WorkItem
               If Err Then
                  Call ErrorCheck("  RouteDetails.workitem")
                      
               Else
                  
                  'If boolPIM is off or the doc is morphed and has no info in PIM text body
                  If (boolMorphed And g_oPIMsg.Text = "") Or (Not boolPIM And boolFinalize) Then
                      'COPY ATTACHMENTS AND TEXT
                      
                      oWorkItem.Item = g_oPIMsg 'Assign msg to workitem
                                              
                      '------------------------------------
                      '           CONSOLIDATE ATTACHMENTS to outgoing message
                      '------------------------------------
                      If g_oPIMsg.attachments.Count Then
                        'Consolidate incomming message attachments onto PIM
                        'Note: When calling item consolidate, True = Add
                        '                                     False = Overwrite
                        PropArray = Array(g_PR_MESSAGE_ATTACHMENTS)
                        oWorkItem.ItemConsolidate PropArray, oMsgOut, True
                        oMsgOut.subject = oMsgOut.subject  'Force dirty flag set
                        If Err Then
                           Call ErrorCheck("  oWorkitem.ItemConsolidate")
                        Else
                           boolSuccess = True
                        End If
                      Else
                        Call TraceAppend("  No attachments to consolidate.")
                      End If
                    
                      If boolFinalize Then
                        '------------------------------------
                        '           CONSOLIDATE BODY
                        '------------------------------------
                        If g_oPIMsg.Text <> "" Then
                           PropArray = Array(g_PR_BODY)
                           oWorkItem.ItemConsolidate PropArray, oMsgOut, True
                           If Err Then
                              Call ErrorCheck("  oWorkitem.ItemConsolidate")
                           
                           Else
                              boolSuccess = True
                           End If
                        
                        Else
                           Call TraceAppend("  No Body to Consolidate.")
                        End If
                      End If
                      
                  Else
                     'Embedding PIM - this will not happen when the body is
                     'empty and the Morph custom property is true
                     oWorkItem.Item = oMsgOut
                     oWorkItem.EmbedMsg g_oPIMsg 'Embed into outgoing msg
                     oMsgOut.subject = oMsgOut.subject 'Force Dirty Flag
                  End If
                  
                  If Err Then
                    Call ErrorCheck("  Embed failed ! Still sending msg.")
                    'Fail Silently, still send but no attachment
                  End If
               End If

               'Order of concatenation is important
               oMsgOut.Text = oMsgOut.Text & vbCrLf & g_bstrWFSendBody & vbCrLf & vbCrLf
               
             Else
             
                '-- LINK PROCESSING --
                'PLACE URL in body that is the link to the original PIM.
                Call TraceAppend("Placing Link in Body")
                bstrLinkURL = "http://" & bstrAttach & "/exchange/forms/openitem.asp?obj=" & g_oPIMsg.ID
                oMsgOut.Text = bstrLinkURL & vbCrLf & vbCrLf & oMsgOut.Text & vbCrLf & g_bstrWFSendBody
             End If
             End If
             
             'Note: Don't add reply to and sender fields if from private store.
             If Not g_boolIsPrivateStore Then
                '------------------------------------
                '  REPLY RECIPIENT ENTRIES POPULATION
                '------------------------------------
                '
                'Developers: The mail should have the reply_recipients_entries field
                '            set so that the SEND in Outlook (or another client) that
                '            didn't use the URL will work properly. This is required
                '            in the case where you don't have send as permissions
                '            on the public folder and therefore can't set the FROM field.
                '
                '      Note: See MAPI SDK for information about these structures
                '
                FlatLength = CStr(Hex(Len(g_bstrReplyToID) / 2))
                bstrFlatEntry = FlatLength & "000000" & g_bstrReplyToID
                StructLength = Hex(Len(bstrFlatEntry) / 2)
                bstrBlob = "01000000" & StructLength & "000000" & bstrFlatEntry
                oMsgOut.Fields.Add g_PR_REPLY_RECIPIENT_NAMES, g_bstrReplyToName
                oMsgOut.Fields.Add g_PR_REPLY_RECIPIENT_ENTRIES, bstrBlob
   
                '--------------------------------------
                          
                '------------------------------------
                '   SET FROM FIELD OF MESSAGE
                '------------------------------------
                oMsgOut.sender = g_oFolderAddEntry
             End If
                     
             
             'Set CacheRecip
             If Not boolResolveErr Then
                If oMsgOut.Recipients.Count > 0 Then
                   Set oTemp = oMsgOut.Recipients.Item(1)
                   Call PutCacheRecip(oTemp.Name, oTemp.address)
                   Set oTemp = Nothing
                End If
             End If
             
             
             '---------------------------------------
             ' Add Rejected Status Message if Necessary
             '---------------------------------------
             bstrStatusMsg = g_oPIMsg.Fields("StatusMsg")
             If bstrStatusMsg <> "<CLEAR>" Then
                   oMsgOut.Text = bstrStatusMsg & vbCrLf & vbCrLf & oMsgOut.Text
                   g_oPIMsg.Fields.Add "StatusMsg", VT_BSTR, "<CLEAR>"
             End If
             
             
             '-----------------------------------
             '   Update PIM with any changes
             g_oPIMsg.Update
             
             '-----------------------------------
             '   SEND MESSAGE
             '-----------------------------------
             'Don't send anything if there was a role error since
             ' they recipient won't be valid
             If Not boolResolveErr Then
                ' The false argument will make the msg not save in the
                ' sent item folder.
                '
                ' Note: Send also UPDATES before it sends the message.
                oMsgOut.Send False
                If Err Then
                   Call ErrorCheck("oMsgOut.Send")
                   boolSuccess = False
                Else
                                
                   Call TraceAppend("Message Sent")
                   boolSuccess = True
                End If
             Else
               boolSuccess = False
             End If
             
             'Can't add message to outbox
             End If
          'Setup Terminate Error
          End If
       'InitializeMsg Error
       End If
    'InitializeObjects Error
    End If
   
    'One last check for any possible untrapped errors
    If Err Then
       Call ErrorCheck("!Route_send")
       
       boolSuccess = False
    End If

    Call TraceAppend("Send Exit" & vbCrLf)
    Call traceOutput("Send", 0)
        
    Set oTemp = Nothing
    Set oMsgOut = Nothing
    Set oRecip = Nothing
    Set oRecCol = Nothing
    Set oParticipant = Nothing
    Set oWorkItem.Item = Nothing
    Set oWorkItem = Nothing
    
    Call ReleaseGlobalObjects

End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: IsInvalidRecip
'   Area: Core Routing
'   Desc: verifies that recieved mail
'         matches this recipient other wise the mail is ignored.
'   Parm: byRef boolSuccess
'             Set to True IF a invalid recipient is detected, so it will
'             fall through if failure occurs naturally and the MSERW map
'             the true return to branch back to next.
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Sub Route_IsInvalidRecip(boolSuccess)

    On Error Resume Next
    
    Dim boolRes                'Boolean Result
    Dim bstrLastRecip          'Last Recipient String
    
    Call TraceHeader("IsInvalidRecip")
    
    boolRes = InitializeBaseObjects
    If Not boolRes Then
        Call TraceAppend("InitializeBaseObjects Failed")
            
    Else
        'Get PIM since intialize base objects doesn't give us this.
        Set g_oProcInstance = RouteDetails.ProcInstance
        Set g_oPIMsg = g_oProcInstance.Message

        'Get the NAME of the last recipient to which a message
        'was sent in order to do a lookup in the recipient
        'table.
        bstrLastRecip = GetCacheName()
        
        If g_oMsgIn.sender.Name <> bstrLastRecip Then
           boolSuccess = True
           Call TraceAppend("Invalid Recipient Detected.")
           Call TraceAppend("  Msg Sender name: " & g_oMsgIn.sender.Name)
           Call TraceAppend("  Last Recip name: " & bstrLastRecip)
        Else
           Call TraceAppend("Valid Recipient Detected")
        End If
                
        'Release Objects
        Set g_oProcInstance = Nothing
        Set g_oPIMsg = Nothing
    End If

     Call TraceAppend("IsInvalidRecip Exit returned " & boolSuccess & vbCrLf)
     Call traceOutput("IsInvalidRecip", 0)
    
    Call ReleaseBaseObjects
End Sub


'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_Receive
'   Area: Core Routing
'   Desc: Receive replies, update recipient table, remove and attach
'         attachments to PIMsg.
'   Parm: ByRef boolSuccess
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Sub Route_Receive(boolSuccess)

    On Error Resume Next

    Dim varRet              'Variant Return Value
    Dim boolRes             'Boolean Result
    Dim oRecipientEntry     'VoteTable Recipient Entry Object
    Dim bstrUSubject        'Uppercased Subject from incomming msg
    
    'Set to Default of False
    'boolSuccess = False
    
    Call TraceHeader("Receive")
    
    boolRes = InitializeObjects
    If Not boolRes Then
        Call TraceAppend("InitializeObjects Failed")
            
    Else
       'Notes: Outlook approval/reject buttons place the string
       '       Approve:" on the subject line, the URL version
       '       places APPWF: on the subject line.
       '       Check the subject line to find out if
       '       it's a Outlook message or a Non Outlook Message.
       '
       boolRes = InitializeVoteTable()
    
       If Not boolRes Then
          Call TraceAppend("Not able to initialize VoteTable")
            
       Else
          bstrUSubject = UCase(g_oMsgIn.subject)
          
          'Check for outlook treated message.
          If InStr(1, bstrUSubject, "APPROVE") Or InStr(1, bstrUSubject, "REJECT") Then
             
             '---------------------------------------------------------
             '       RECIPIENT TABLE UPDATE FOR OUTLOOK TREATED MESSAGE
             '---------------------------------------------------------
             Call TraceAppend("Process Outlook Treated Messsage")
             Call TraceAppend("Table Count Before ConsolidateResponse: " & CStr(g_oVoteTable.Count))

             '- Add Recipient Information to the PIM -
             'This passes the incomming message to the VoteTable object so
             'it can update information on the PIM. It will create a
             'new entry in the recipient table also if one doesn't exist.
             g_oVoteTable.ConsolidateResponse g_oMsgIn, True
             g_oVoteTable.Save
             
             If Err Then
                Call ErrorCheck("g_oVoteTable.Save")
             Else
                Call TraceAppend("Table Count After ConsolidateResponse: " & CStr(g_oVoteTable.Count))
                boolSuccess = True
             End If
             
              
          Else
          
             '-----------------------------------------------------
             '       RECIPIENT TABLE UPDATE FOR URL TREATED MESSAGE
             '-----------------------------------------------------
             Call TraceAppend("Process URL Handled Messsage")

             Set oRecipientEntry = CreateObject("exrt.RecipientEntry")
             If Err Then
                Call ErrorCheck("exrt.recipiententry")
                'Skip recipient processing if can't get object
                
             Else
                oRecipientEntry.recipient = g_oMsgIn.sender.Name
                oRecipientEntry.Date = g_oMsgIn.TimeSent
             
                'Look for APPROVE in subject.
                If InStr(1, UCase(g_oMsgIn.subject), "APPWF") Then
                   Call TraceAppend("Message Approval Found.")
                   oRecipientEntry.Status = "Approve"
                   boolSuccess = True
                 
                'Otherwise look for REJECT in subject
                ElseIf InStr(1, UCase(g_oMsgIn.subject), "REJWF") Then
                   Call TraceAppend("Message Reject Found.")
                   oRecipientEntry.Status = "Reject"
                   boolSuccess = True
             
                'If both fail this is an invalid incomming message
                Else
                   Call TraceAppend("Invalid Message - Subject missing approval info")
                End If
             'Recipient Entry Failure.
             End If
             
             If boolSuccess Then
                g_oVoteTable.ConsolidateResponse oRecipientEntry, True
                g_oVoteTable.Save
                If Err Then
                   Call ErrorCheck("g_oVoteTable.Save")
                Else
                   Call TraceAppend("Outlook Saved.")
                   boolSuccess = True
                End If
             End If
          'OUTLOOK OR URL TREATED
          End If
       'Votebuton initialize failure
       End If
    'Initialize object Failure
    End If
    
    'Check for untrapped errors.
    If Err Then
        Call ErrorCheck("!Route Receive")
        boolSuccess = False
    End If

    Call TraceAppend("Receive Exit returned " & boolSuccess & vbCrLf)
    Call traceOutput("Receive", 0)
        
    Set oRecipientEntry = Nothing

    Call ReleaseGlobalObjects
    
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_Consolidate
'   Area: Core Routing
'   Desc: This function takes incomming attachments and message body
'         and adds them to the PIMsg.
'   Parm: ByRef boolSuccess
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Sub Route_Consolidate(boolSuccess)

    On Error Resume Next

    Dim oWorkItem      'Routing WorkItem Object
    Dim InAttachCnt    'Attachment Count
    Dim PropArray      'Property Array for workitem
    Dim bstrSendFrom   'Send From String
    Dim boolRes        'Boolean Result
    Dim boolMsgUpdateFlag   'Boolean Msg Update Flag
    
    Call TraceHeader("Consolidate")
    
    boolSuccess = False
   
    boolRes = InitializeObjects
    If Not boolRes Then
        Call TraceAppend("InitializeObjects Failed")
       
    Else
       'Create workitem
       Set oWorkItem = RouteDetails.WorkItem
       oWorkItem.Item = g_oMsgIn  'Assign msg to workitem
    
       If Err Then
          Call ErrorCheck("oWorkItem")
          
       Else
          '------------------------------------
          '       CONSOLIDATE ATTACHMENTS
          '------------------------------------
          InAttachCnt = g_oMsgIn.attachments.Count
          Call TraceAppend("Number of Attachments: " & CStr(InAttachCnt))
          
          If InAttachCnt Then
             'Consolidate incomming message attachments onto PIM
             'Note: When calling item consolidate, True = Add
             '                                     False = Overwrite
                          
             Call TraceAppend("Consolidating Attachments")
             PropArray = Array(g_PR_MESSAGE_ATTACHMENTS)
             oWorkItem.ItemConsolidate PropArray, g_oPIMsg, True
             g_oPIMsg.subject = g_oPIMsg.subject  'Force dirty flag set
             boolMsgUpdateFlag = True
             If Err Then
                Call ErrorCheck("oWorkitem.ItemConsolidate")
             Else
                boolSuccess = True
             End If
          Else
             Call TraceAppend("No attachments to consolidate.")
          End If
        
          '------------------------------------
          '           CONSOLIDATE BODY
          '------------------------------------
          If g_oMsgIn.Text <> "" Then
             Call TraceAppend("Consolidating Body")
             PropArray = Array(g_PR_BODY)
             bstrSendFrom = vbCrLf & "==================================" & vbCrLf & g_oMsgIn.sender.Name & vbCrLf
             bstrSendFrom = bstrSendFrom & "=================================="
             g_oPIMsg.Text = g_oPIMsg.Text & bstrSendFrom
             oWorkItem.ItemConsolidate PropArray, g_oPIMsg, True
             
             boolMsgUpdateFlag = True
             If Err Then
                Call ErrorCheck("oWorkitem.ItemConsolidate")
             
             Else
                boolSuccess = True
             End If
          
          Else
             Call TraceAppend("No Body to Consolidate.")
          End If
          
          'Update PIM if it's been modified
          If boolMsgUpdateFlag Then
             g_oPIMsg.Update
          End If
       'Failure to create or use workitem
       End If
    'Initialize Object Failure
    End If
    
    Call TraceAppend("Consolidate Exit returned " & boolSuccess & vbCrLf)
    Call traceOutput("Consolidate", 0)

    Set oWorkItem.Item = Nothing
    Set oWorkItem = Nothing
    
    Call ReleaseGlobalObjects
    
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_IsTimeout
'   Area: Core Routing
'   Desc: This function checks to see if the timeout has occured
'         and returns this value is true for yes, false for no.
'         No would normally proceed to receive in the map.
'   Parm: byRef boolSuccess
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Sub Route_IsTimeout(boolSuccess)

   On Error Resume Next

   Dim boolRes           'Boolean Result
   
   Call TraceHeader("IsTimeout")
   
   boolRes = InitializeBaseObjects
   If Not boolRes Then
        Call TraceAppend("InitializeBaseObjects Failed")
        'Initialize Objects Failure
   Else
     'Since InitializeBaseobjects is used get the
     'procinstance here.
     Set g_oProcInstance = RouteDetails.ProcInstance
     boolSuccess = g_oProcInstance.Timeout
     If Err Then
        Call ErrorCheck("g_oProcInstance.Timeout")
     End If
     Set g_oProcInstance = Nothing
   End If
   
  Call TraceAppend("IsTimeout returns " & boolSuccess)
  Call traceOutput("IsTimeout", 2)

  Call ReleaseBaseObjects
  
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_FinalizeReport
'   Area: Core Routing
'   Desc: Textize approval/reject information onto the PIM.
'   Parm: boolReject, ByRef boolSuccess
'        (boolReject; True = Accept, False = Reject)
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Sub Route_FinalizeReport(boolAccept, boolSuccess)

    On Error Resume Next

    Dim boolRes              'Boolean Result
    Dim bResponses           'Boolean Response Occurred Flag
    Dim bSerialReject        'Reject Verify in Sequential Case
    
    Dim oRecipientEntry      'VoteTable Recipient Object
    
    'Numeric
    Dim x                    'Loop Variable
    Dim ApproveCnt           'Accept Accumulator
    Dim RejectCnt            'Reject Accumulator
    Dim lngRUI               'Routing Unique Identifier
    
    'Strings
    Dim bstrStatus           'Status of Recipient
    Dim bstrTA               'Text Accumulator String
    Dim bstrName             'Name of Recipient
    Dim bstrFolderName       'Folder name
    Dim bstrStatusMsg        'String Msg
    
    Call TraceHeader("FinalizeReport")
    Call TraceAppend("boolAccept = " & boolAccept)

    boolRes = InitializeObjects
    If Not boolRes Then
        Call TraceAppend("InitializeObjects Failed")
    
    Else
      'Textize voting results in PIMsg.
      bstrTA = " " & vbCrLf & vbCrLf & "----------------------------" & vbCrLf
      
      '*==*
      boolRes = InitializeVoteTable()
      If Not boolRes Then
         'Unable to properly intialize VoteTable, skip try to use it.
      
      Else
        Call TraceAppend("Number of Recipients in Table: " & CStr(g_oVoteTable.Count))
        
        'Move through each item in VoteTable and textize it into the PIM message body.
        bstrFolderName = g_oFolder.Name
        Call ErrorCheck("Before Loop Error Check")
        
        '************* Recipient Table Textizing ********
        For x = 1 To g_oVoteTable.Count
           
           Set oRecipientEntry = g_oVoteTable.Item(x)
           Call ErrorCheck("Loop after g_oVoteTable.item(x) error check")
           
           bstrName = oRecipientEntry.recipient
           Call TraceAppend("oRecipientEntry " & bstrName)
           
           bstrStatus = oRecipientEntry.Status
           If bstrStatus <> "" Then
              
              Call TraceAppend("  Textized : " & bstrName)
              bstrTA = bstrTA & " Name: " & bstrName & vbCrLf
              bstrTA = bstrTA & " Status: " & bstrStatus & vbCrLf
              bstrTA = bstrTA & " Date: " & oRecipientEntry.Date & vbCrLf & vbCrLf
              bResponses = True
             
              'Accumulate Responses
              If bstrStatus = "Approve" Or bstrStatus = "AutoApprove" Then
                ApproveCnt = ApproveCnt + 1
              ElseIf bstrStatus = "Reject" Or bstrStatus = "AutoReject" Then
                RejectCnt = RejectCnt + 1
              Else
                'Ignore if string doesn't match any cases above
              End If
             
           Else
              'Skip item if status is blank
              Call TraceAppend("  Skipped Empty Status Recipient Entry.")
           End If
        Next
        
        ' Select response based upon accept/reject counts
        ' It will only accept if  approvals > rejects
        ' -- NOTE:
        ' The only reason this is done is that with a sequential route when an
        ' item is rejected or not responded to it may return to sender.
        ' In this case the actual sum of approvals MAY be greater than
        ' rejects so we need to tabulate.
        bSerialReject = True
        If ApproveCnt = 0 And RejectCnt = 0 Then
            'No Response is rejected
            'bSerialReject will be true
        Else
            If ApproveCnt > RejectCnt Then
               bSerialReject = False
            End If
        End If
        
        If Err Then
           Call ErrorCheck("g_oVoteTable.item failure - finalize report will be incomplete.")
           
        Else
           'Status Msg is a special message that may be filled on reject or teimout cases.
           bstrStatusMsg = g_oPIMsg.Fields("StatusMsg")
           
           '<CLEAR> means that there isn't a special message to include in
           'the outgoing message.
           If bstrStatusMsg <> "<CLEAR>" Then
                bstrTA = vbCrLf & bstrStatusMsg & vbCrLf
                g_oPIMsg.Fields.Add "StatusMsg", VT_BSTR, "<CLEAR>"
                
           Else
                bstrTA = bstrTA & vbCrLf & "The workflow item "
                
                'Insert comment on status
                '  Accepted
                If boolAccept Then
                  bstrTA = bstrTA & "was ACCEPTED." & vbCrLf
                  
                '  Not Responsed to (reject case)
                ElseIf Not boolAccept And Not bResponses Then
                  bstrTA = bstrTA & "was not responded to." & vbCrLf
                  
                '  Rejected
                Else
                  If bSerialReject Then  'Special handle Failure Case
                      bstrTA = bstrTA & "was REJECTED." & vbCrLf  'no resp, rej >= app
                  Else
                      bstrTA = bstrTA & "was ACCEPTED." & vbCrLf  '(serial spec. case)
                  End If
                End If
           End If
           
           'Place text on the PIM
           bstrTA = bstrTA & vbCrLf & "----------------------------" & vbCrLf
           g_oPIMsg.Text = vbCrLf & g_oPIMsg.Text & bstrTA
           g_oPIMsg.Update
                   
           If Err Then
              Call ErrorCheck("Finalize Report")
           Else
              boolSuccess = True
           End If
        End If
        
      'Initalize VoteTable Failure
      End If
   'Initialize Object Failure
   End If
   
   Call TraceAppend("FinalizeReport Exit Returned" & boolSuccess & vbCrLf)
   Call traceOutput("FinalizeReport", 0)

   Set oRecipientEntry = Nothing

   Call ReleaseGlobalObjects
   
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_IsApprovalMsg
'   Area: Core Routing
'   Desc: Check Recipient Table for Approval Status of a recipient
'   Parm: byRef boolSuccess
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Sub Route_IsApprovalMsg(boolSuccess)

   On Error Resume Next

   Dim boolRes            'Result boolean
   Dim x                  'Loop Variable
   Dim oRecipientEntry    'Recipient Object
   Dim bstrMsg            'Rejection Message
   
   'The purpose of this function is to the iterate through each of
   'the recipients and when a match is found return the
   'approval status by setting the boolsuccess variable
   
   Call TraceHeader("IsApprovalMsg")

   'CRITIAL Must be here
   boolRes = InitializeObjects
   If Not boolRes Then
       Call TraceAppend("InitializeObjects Failed")
    
   Else
      boolRes = InitializeVoteTable()
      If Not boolRes Then
        Call TraceAppend("InitializeVoteTable Failed")
    
      Else
         Call TraceAppend("Number of Recipients in Table: " & CStr(g_oVoteTable.Count))
         For x = 1 To g_oVoteTable.Count
            Set oRecipientEntry = g_oVoteTable.Item(x)
            
            If oRecipientEntry.recipient = g_oMsgIn.sender.Name Then
               If Err Then
                  Call ErrorCheck("oRecipientEntry Handling")
                  
               'Note if information is not updated on the table for any reason
               'then it is automatically set to false since
               'the return value of this function is a boolean.
               Else
                  If oRecipientEntry.Status = "Approve" Or oRecipientEntry.Status = "AutoApprove" Then
                     boolSuccess = True
                     Call TraceAppend("Recipient Approval Found.")
                  Else
                     bstrMsg = g_oMsgIn.sender.Name & " has rejected the work item so it has been returned to you."
                     g_oPIMsg.Fields.Add "StatusMsg", VT_BSTR, bstrMsg
                     Call DecCacheRecip(True) 'True means always update
                     Call TraceAppend("Recipient Reject Found.")
                  End If
               End If
            Else
               Call TraceAppend("Ignored " & oRecipientEntry.recipient)
            End If
          Next
          
      'Initialize VoteTable failure
      End If
   'Initialize Object Failure
   End If
   
   Call TraceHeader("IsApprovalMsg Exit Returned " & boolSuccess & vbCrLf)
   Call traceOutput("IsApprovalMsg", 0)

   Set oRecipientEntry = Nothing

   Call ReleaseGlobalObjects
   
End Sub


'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_IsApprovedTable
'   Area: Core Routing
'   Desc: This function tally the status of all recipients in the
'         the recipient table and returns true for approved or  false
'         for failure.
'   Parm: ByRef BoolSuccess
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Sub Route_IsApprovedTable(boolSuccess)

   On Error Resume Next

   Dim boolRes             'Result Variable
   Dim ApproveCnt           'Accept count
   Dim RejectCnt           'Reject count
   Dim oRecipientEntry     'Recipient Entry Object
   Dim x                   'Loop Variable
   Dim bstrStatus          'Status String of Recipient
   
   'The purpose of this function is to the iterate through each of
   'the recipients, get the approval Status and then finally do a
   'compare on the totalized results

   Call TraceHeader("IsApprovedTable")

   boolRes = InitializeObjects
   If Not boolRes Then
        Call TraceAppend("InitializeObjects Failed")
    
   Else
      ApproveCnt = 0
      RejectCnt = 0

      boolRes = InitializeVoteTable()

      If Not boolRes Then
        Call TraceAppend("InitializeVoteTable Failed")
    
      Else
         'Iterate through the recipients in the recipient table
         'and get their status string
         For x = 1 To g_oVoteTable.Count
            Set oRecipientEntry = g_oVoteTable.Item(x)
            Call TraceAppend("Recip : " & oRecipientEntry.recipient)
            bstrStatus = oRecipientEntry.Status
            Call TraceAppend("Status: " & "." & bstrStatus & ".")
            
            Call ErrorCheck("Error occur during loop: " & CStr(x))
            
            If bstrStatus = "Approve" Or bstrStatus = "AutoApprove" Then
                ApproveCnt = ApproveCnt + 1
                Call TraceAppend(" Approved Detected: " & CStr(ApproveCnt))
                   
            ElseIf bstrStatus = "Reject" Or bstrStatus = "AutoReject" Then
                RejectCnt = RejectCnt + 1
                Call TraceAppend(" Reject Detected: " & CStr(RejectCnt))
                   
            Else
                Call TraceAppend("Recipient Ignored.")
                'Ignore recipient with no status set (might occur during parallel case).
            End If
         Next
         
         Call TraceAppend("Approvals : " & CStr(ApproveCnt) & "   Rejects: " & CStr(RejectCnt))
         If ApproveCnt = 0 And RejectCnt = 0 Then
            boolSuccess = False  'REJECT if no response from anyone
         
         Else
           If ApproveCnt > RejectCnt Then
              Call TraceAppend("Item is approved.")
              boolSuccess = True
           Else
             Call TraceAppend("Item is rejected.")
             boolSuccess = False
           End If
         End If
      End If
   End If
    
   If Err Then   'Trap any untrapped errors
      Call ErrorCheck("IsApprovedTable - Failure will cause rejection.")
      boolSuccess = False
   End If

   Call TraceAppend("IsApprovedTable Exit Returned " & boolSuccess & vbCrLf)
   Call traceOutput("IsApprovedTable", 0)

   Set oRecipientEntry = Nothing

   Call ReleaseGlobalObjects
   
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: Route_AutoSet
'   Area: Core Routing
'   Desc: This function can either AutoApprove or AutoReject a recipient
'         and update their entry in the status table.
'   Parm: BoolApproved (True=AutoApprove, False = AutoReject)
'         BoolAutoFlag (True =Autoset on, True AutoSet Off)
'         ByRef BoolSuccess
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Sub Route_AutoSet(boolApproved, BoolAutoFlag, boolSuccess)

    On Error Resume Next
         
    Dim boolRes                 'Result boolean
    Dim oRecipientEntry         'Recipient Entry Object
    Dim x                       'Loop Variable
    Dim bstrLastRecip           'Last Recipient
    Dim bstrMsg                 'Reject Message
    
    RT_AUTOADD = True
    
    Call TraceHeader("AutoSet")
    
    boolRes = InitializeObjects
    If Not boolRes Then
        Call TraceAppend("InitializeObjects Failed")
    
    Else
      boolRes = InitializeVoteTable()
      If Not boolRes Then
            Call TraceAppend("InitializeVoteTable Failed")
         
      Else
         'Find out who the message was last send to.
         'Get this NAME from the Recipient Cache
         bstrLastRecip = GetCacheName()
         Call TraceAppend("LastRecip = " & bstrLastRecip)
                    
         If BoolAutoFlag Then
          
          'Get Recipient Entry
          Set oRecipientEntry = CreateObject("exrt.RecipientEntry")
          
          If Err Then
             'Failed to get recipient object, exit
             Call ErrorCheck("exrt.recipiententry")
          
          Else
               
              oRecipientEntry.recipient = bstrLastRecip
              oRecipientEntry.Date = CStr(Now)
              
              'If true then it's a autoapproval
              If boolApproved Then
                  oRecipientEntry.Status = "AutoApprove"
              Else
                  bstrMsg = bstrLastRecip & " did not approve this item in the required time. The item has been returned to you."
                  g_oPIMsg.Fields.Add "FailStatus", VT_BSTR, bstrMsg
                  Call DecCacheRecip(False)   'don't update it's done below
                  oRecipientEntry.Status = "AutoReject"
              End If
               
              g_oVoteTable.ConsolidateResponse oRecipientEntry, RT_AUTOADD
              'Note: in this case don't set originator since the last
              'one didn't respond
              g_oVoteTable.Save
              g_oPIMsg.Update
              
              If Err Then
                 Call ErrorCheck("g_oVoteTable.Save")
              Else
                 Call TraceAppend("Recipient Status Set on Table")
                 boolSuccess = True
              End If

          'Failed to get Recipient Entry Object
          End If
       Else
          'Simple Message Treatment
          '  1. place message and udpate PIM
          '  2. Decrement Cache  (we don't care about decrement when returning to originator
          bstrMsg = bstrLastRecip & " did not respond in the required time so the workitem has been returned to you."
          g_oPIMsg.Fields.Add "StatusMsg", VT_BSTR, bstrMsg
          Call DecCacheRecip(True)  'Force update
          
       End If
      'VoteTable Failure
      End If
    'Initialize Object Failure
    End If

    Call TraceAppend("AutoSet Returns " & boolSuccess & vbCrLf)
    Call traceOutput("AutoSet", 0)

    Set oRecipientEntry = Nothing

    Call ReleaseGlobalObjects
    
End Sub

'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
'                         UTILITY FUNCTIONS
'+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: InitializeVoteTable
'   Area: Utility
'   Desc: Create VoteTable object and set PIM property
'   Parm: None
'   Retn: Boolean Success
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Function InitializeVoteTable()

   On Error Resume Next
   
   Dim boolSuccess
   boolSuccess = False
   
   'Add Approve/Reject Outlook information to message
   Set g_oVoteTable = g_oProcInstance.VoteTable
   If Err Then
      Call ErrorCheck("g_oProcInstance.VoteTable")
   Else
      boolSuccess = True
   End If
   
   InitializeVoteTable = boolSuccess
   Call TraceAppend("InitializeVoteTable returned " & boolSuccess)
   
End Function

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: ReleaseBaseObjects
'   Area: Utility
'   Desc: Release global objects
'   Parm: None
'   Retn: Success or Failure boolean
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub ReleaseBaseObjects()
    
    Set g_oMsgIn = Nothing          'Release in reverse order
    Set g_oFolder = Nothing
    Set g_oSession = Nothing
    
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: InitializeBaseObjects
'   Area: Utility
'   Desc: Lean and mean version of InitializeObjects
'   Note: DO NOT USE BOTH FUNCTIONS in the same core function
'   Parm: None
'   Retn: Boolean Success
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Function InitializeBaseObjects()

    On Error Resume Next
    
    Call TraceAppend("Entering Base Objects")
    
    Set g_oSession = EventDetails.session
    Set g_oMsgIn = RouteDetails.Msg
    Set g_oFolder = RouteDetails.Folder
    
    'Trap any untrapped failure
    If Err Then
         Call ErrorCheck("!InitializeBaseObjects")
         InitializeBaseObjects = False
    Else
         InitializeBaseObjects = True
    End If

End Function

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: InitializeObjects
'   Area: Utility
'   Desc: Set Message, Folder and other globals. Check Store agent
'         is operating in.
'   Parm: None
'   Retn: Boolean Success
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Function InitializeObjects()

    On Error Resume Next

    Dim bstrTemp
    Dim oStores             'InfoStores Object
    Dim oStore              'Store Object
    Dim bstrPStoreName      'Public Store Name
    Dim lmask               'Mask.
        
    'Get Important session,folder,msg info
    Set g_oProcInstance = RouteDetails.ProcInstance
    Set g_oPIMsg = g_oProcInstance.Message

    Set g_oSession = EventDetails.session
    Set g_oMsgIn = RouteDetails.Msg
    Set g_oFolder = RouteDetails.Folder
    Set g_oAgentAddEntry = g_oSession.currentuser
    
    'Get Public Folder name for non english versions.
    Set oStores = g_oSession.InfoStores
     For Each Item In oStores
        Set oStore = Item
        lmask = oStore.Fields.Item(PR_STORE_SUPPORT_MASK)  '&H340D0003
        Err.Clear
        If lmask And &H4000 Then        ' CDO_STORE_PUBLIC_FOLDERS
          bstrPStoreName = oStore.Name
          Exit For
        End If
    Next
      
    'Assign Private Store Boolean
    bstrTemp = g_oSession.GetInfoStore(g_oFolder.StoreID).Name
    If bstrTemp = bstrPStoreName Then
       g_boolIsPrivateStore = False
    Else
       g_boolIsPrivateStore = True
    End If
    
    'Get Sender Name if not exist (draft msg) then get originator name
    g_bstrMsgSender = g_oMsgIn.sender.Name
    If Err Then
       Err.Clear
       g_bstrMsgSender = g_oMsgIn.Fields.Item(g_PR_CREATOR_NAME)
    End If
    Call TraceAppend("Msg Sender Name: " & g_bstrMsgSender)
        
    'Save message Subject for Trace  reasons.
    g_bstrInMsgSubject = g_oPIMsg.subject
        
    'Trap any untrapped failure
    If Err Then
         Call TraceAppend("InitializeObjects returned False")
         Call ErrorCheck("!InitializeObjects")
         InitializeObjects = False
    Else
         Call TraceAppend("InitializeObjects returned True")
         InitializeObjects = True
    End If
 
    'Release objects
    Set oStore = Nothing
    Set oStores = Nothing
    
End Function


'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: ReleaseObjects
'   Area: Utility
'   Desc: Release global objects
'   Parm: None
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub ReleaseGlobalObjects()
    
    Set g_oMsgIn = Nothing          'Release in reverse order
    Set g_oFolder = Nothing
    Set g_oVoteTable = Nothing
    Set g_oAgentAddEntry = Nothing
    Set g_oFolderAddEntry = Nothing

    Set g_oPIMsg = Nothing
    Set Item = Nothing
    Set g_oSession = Nothing
    Set g_oProcInstance = Nothing
    
 
End Sub
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: InitializeMsg
'   Area: Utility
'   Desc: Set global Strings for outgoing message.
'   Parm: String (Msg Body), String (Msg Subject)
'   Retn: Success or Failure boolean
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Function InitializeMsg(bstrtext, bstrSubject)

    On Error Resume Next
  
    Dim oae                   'Address List Entry
  
    Dim bstrApprove           'Approve URL String
    Dim bstrReject            'Reject URL String
    Dim bstrReturnAddress     'Return Address
    Dim bstrAEID              'Reply To Address Entry
    
    Dim ts                    'Temp String
       
    Dim SMTP_Address          'SMTP Version of the address
    Dim Route_UI              'Unique Message Indentifier
    Dim FFlag                 'Finalize Report is on
    
    'Special message treatment if it the report going back to the originator
    If bstrtext = "<FINALIZED>" Then
       FFlag = True
       Call TraceAppend("<FINALIZED> was detected, change outgoing msg processing")
    Else
       FFlag = False
    End If

    
    'This handles the case if a person installs the route in their
    'private store inbox.
    If g_boolIsPrivateStore Then
       ' Handle Private Store
       ' Send to the route installer since they
       ' are the ones who own their inbox.
       Set oae = g_oAgentAddEntry
       Call TraceAppend("Private Store Detected.")
       
    Else
       'This method ONLY works on a public folder
       ' Get the address entry directly from the public folder via prop
       bstrAEID = g_oFolder.Fields(g_PR_ADDRESS_BOOK_ENTRYID)
       Set oae = g_oSession.GetAddressEntry(bstrAEID)
       Set g_oFolderAddEntry = oae
    End If
        
    If Err Then
       Call ErrorCheck("Error getting address entry information")
       InitializeMsg = False
       
    Else
       SMTP_Address = oae.Fields(g_PR_SMTP_ADDRESS_W)
       bstrReturnAddress = SMTP_Address
       Call TraceAppend("SMTP ADDRESS: " & bstrReturnAddress)
    
       g_bstrReplyToName = oae.Name
       g_bstrReplyToID = oae.ID
       g_bstrReplyToAddr = bstrReturnAddress
       
       If Not FFlag Then
          ts = "*AUTO-ROUTED MAIL*"
          ts = ts & vbCrLf & "================" & vbCrLf
          'Optional Map Text to be included with body
          If bstrtext <> "" Then
             ts = ts & vbCrLf & bstrtext & vbCrLf
          End If
          ts = ts & "================" & vbCrLf
       End If
        
    
        'Get RUI number
        
       Route_UI = g_oProcInstance.RUI
       Call TraceAppend("RUI = " & CStr(Route_UI))
               
       If FFlag Then
            ts = ts & "Route Number: " & CStr(Route_UI) & vbCrLf & "================"
            g_bstrWFSendSubject = bstrSubject & " - FINAL RESULTS   " & "RUI=" & CStr(Route_UI)
            ts = ts & "================" & vbCrLf
       End If
               
       If Not FFlag Then
            ts = ts & "Attached is the document(s) that has been submitted to you for your approval" & vbCrLf
            ts = ts & "To Process this item please:" & vbCrLf
            ts = ts & "   1. Review the attached document" & vbCrLf
            ts = ts & "   2. Approve or Reject it." & vbCrLf
            ts = ts & "   3. Make comments, add modified document, etc and send message." & vbCrLf
            ts = ts & "To Approve Or Reject:" & vbCrLf
            ts = ts & "   1. Using any client, click one of the URL's in the message body" & vbCrLf
            ts = ts & "   2. Using Outlook click the Approve or Reject button on the top of the message." & vbCrLf & vbCrLf
            ts = ts & "Note: Place new attachment(s) and/or text in the reply message after using the" & vbCrLf
            ts = ts & "      button or the URL" & vbCrLf
           
            bstrApprove = bstrReturnAddress & "?Subject=AppWF:" & ",RUI=" & CStr(Route_UI) & vbCrLf & vbCrLf
            bstrApprove = Replace(bstrApprove, " ", "%20")
            bstrReject = bstrReturnAddress & "?Subject=RejWF:" & ",RUI=" & CStr(Route_UI) & vbCrLf & vbCrLf
            bstrReject = Replace(bstrReject, " ", "%20")
            
            ts = ts & "Approve  :  mailto:" & bstrApprove
            ts = ts & "Reject   :  mailto:" & bstrReject
            If Len(bstrSubject) > 70 Then
               bstrSubject = Left(bstrSubject, 70)
            End If
            g_bstrWFSendSubject = bstrSubject & "  RUI=" & CStr(Route_UI) & "  "
       End If
    
       g_bstrWFSendBody = ts
       InitializeMsg = True
           
    'Couldn't get Address Entry Information
    End If
    
    If Err Then
         Call ErrorCheck("Unexpected Error")
         InitializeMsg = False
    End If
    
    If InitializeMsg Then
       Call TraceAppend("InitializeMsg returned True")
    Else
       Call TraceAppend("InitializeMsg returned False")
    End If

    Set oae = Nothing

End Function

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: PutCacheRecip
'   Area: Utility
'   Desc: Place Recipient in the list cache
'   Parm: String
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub PutCacheRecip(bstrName, bstrAddress)

' - Code Flow
'    1. Get Current Recip Number
'    2. Increment recipient Number
'    3. Write recipient number
'    4. write to custom prop
'    5. Check for errors

  On Error Resume Next
  
  Dim iRecipNum     'Number of Recipients
  
  Call TraceAppend("PutCacheRecip : Name:" & bstrName & "  Addr:" & bstrAddress)
  
  iRecipNum = g_oPIMsg.Fields("CacheRecipNum")
  iRecipNum = iRecipNum + 1
  g_oPIMsg.Fields.Add "CacheRecipNum", VT_I2, iRecipNum
  g_oPIMsg.Fields.Add "CacheRecip" & CStr(iRecipNum), VT_BSTR, bstrName
  g_oPIMsg.Fields.Add "CacheAddr" & CStr(iRecipNum), VT_BSTR, bstrAddress
  
  If Err Then
      Call ErrorCheck("PutCacheRecip")
  End If

End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: InitializeCacheRecip
'   Area: Utility
'   Desc: Initialize Recip Number and first recipient which is pim sender
'   Parm: None
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub InitializeCacheRecip()
' - Code Flow
'  1. Write recip number prop  "CacheRecipNum" = 1
'  2. Write Recip name 1 "CacheRecip1" = pim sender name
'  3. Update message
'  4. Check for errors

   On Error Resume Next
   Dim iRecipNum
   
   iRecipNum = 1
   Call TraceAppend("InitializeCacheRecip")
   g_oPIMsg.Fields.Add "CacheRecipNum", VT_I2, iRecipNum
   g_oPIMsg.Fields.Add "CacheRecip1", VT_BSTR, g_oPIMsg.sender.Name
   g_oPIMsg.Fields.Add "CacheAddr1", VT_BSTR, g_oPIMsg.sender.address
   If Err Then
      Call ErrorCheck("InitializeCacheRecip")
   End If
   
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: GetCacheName
'   Area: Utility
'   Desc: Get Current Recipient in the list cache
'   Parm: None
'   Retn: Recipient Name as string
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Function GetCacheName()
  
' - Code Flow
'    1. Get Current Recip Number
'    2. Get Current Recip name
'    3. Check for errors
  
  On Error Resume Next
  Dim iRecipNum
  Dim bstrRecip
  
  Call TraceAppend("GetCacheName")
  
  iRecipNum = g_oPIMsg.Fields("CacheRecipNum")

  bstrRecip = g_oPIMsg.Fields("CacheRecip" + CStr(iRecipNum))
  Call TraceAppend("  Prop =" & "CacheRecip" & CStr(iRecipNum) & "  Got Prop: " & bstrRecip)
  If Err Then
      Call ErrorCheck("GetCacheName")
      GetCacheName = "<ERROR>"
  Else
      GetCacheName = bstrRecip
  End If
  
End Function

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: GetCacheAddr
'   Area: Utility
'   Desc: Get Current Recipient in the list cache
'   Parm: None
'   Retn: Recipient Address as string
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Function GetCacheAddr()
  
' - Code Flow
'    1. Get Current Recip Number
'    2. Get Current Recip name
'    3. Check for errors
  
  On Error Resume Next
  Dim iRecipNum
  Dim bstrAddr
  
  Call TraceAppend("GetCacheAddr")
  
  iRecipNum = g_oPIMsg.Fields("CacheRecipNum")

  bstrAddr = g_oPIMsg.Fields("CacheAddr" + CStr(iRecipNum))
  Call TraceAppend("  Prop =" & "CacheAddr" & CStr(iRecipNum) & "  Got Prop: " & bstrAddr)
  If Err Then
      Call ErrorCheck("GetCacheAddr")
      GetCacheAddr = "<ERROR>"
  Else
      GetCacheAddr = bstrAddr
  End If
  
End Function

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: DecCacheRecip
'   Area: Utility
'   Desc: Decrement CacheRecip Count
'   Parm: None
'   Retn: None
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub DecCacheRecip(boolUpdate)
  '-Code Flow
  '1. Get Current Recipient Num
  '2. if num > 1 then write num - 2 (double decrements)
  '3. Trap errors
  
  On Error Resume Next
  
  Dim iRecipNum     'Current Recipient Cache Number
  
  Call TraceAppend("DecCacheRecip")
  
  iRecipNum = g_oPIMsg.Fields("CacheRecipNum")

  If iRecipNum > 2 Then
     iRecipNum = iRecipNum - 2
     g_oPIMsg.Fields.Add "CacheRecipNum", VT_I2, iRecipNum
  End If
  
  'Decrement Cache Recipient updates if requested
  If boolUpdate Then
      g_oPIMsg.Update
  End If
  
  If Err Then
      Call ErrorCheck("DecCacheRecip")
  End If
  
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: TraceOutput
'   Area:  Trace
'   Desc: Send Trace Message to Outbox and send to current user
'   Parm: String (Function Name)
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub traceOutput(bstrFN, ioption)
    
    ' 0 = Trace Msg and Trace Log
    ' 1 = Trace Msg Only   - Sends Trace Message to Agent installer
    ' 2 = Trace Log Only   - Sends Trace Information to Event Viewer
    ' 3 = it is recommended that trace msg be used, and only for
    '     a short time when trapping problems since it generates a
    '     lot of messages that are sent to the agent installer.
    
    If TRACE_FLAG And (ioption = 0 Or ioption = 1) Then
          
       Dim oMsgOut
       Set oMsgOut = g_oSession.Outbox.Messages.Add("Trace:" & bstrFN & " Subject:" & g_bstrInMsgSubject, g_bstrTrace, "IPM.Note", 2)
       oMsgOut.Recipients.Add "", "", 1, g_oSession.currentuser.ID
       
       'Send does the udpate
       oMsgOut.Send False  'False is don't save message in sent items.
       g_bstrTrace = ""
    End If
     
    If TRACE_LOG And (ioption = 0 Or ioption = 2) Then
       script.response = g_bstrTrace
    End If
    
    Set oMsgOut = Nothing

End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: TraceAppend
'   Area: Trace
'   Desc: Add to event Trace string
'   Parm: String
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub TraceAppend(varstr)
    g_bstrTrace = g_bstrTrace & "   " & varstr & vbCrLf
End Sub


'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: TraceHeader
'   Area: Trace
'   Desc: Add to event Trace string
'   Parm: String
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub TraceHeader(varstr)
    g_bstrTrace = g_bstrTrace & ":" & varstr & vbCrLf
End Sub

'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
'   Name: ErrorCheck
'   Area: Trace
'   Desc: Add to err number & description to Trace string
'   Parm: String
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Private Sub ErrorCheck(AddStr)
    If Err Then
       g_bstrTrace = g_bstrTrace & "   Err:" & AddStr & "  -  " & CStr(Hex(Err.Number)) & "  " & Err.Description & vbCrLf
       Err.Clear
    End If
End Sub

</SCRIPT>
