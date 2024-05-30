<SCRIPT RunAt=Server Language=VBScript>

'------------------------------------------------------------------------------
'FILE DESCRIPTION: Exchange Server Event Script
'------------------------------------------------------------------------------

Option Explicit 

'----------------------------------------------------------------------
' Global Variables
'----------------------------------------------------------------------
Dim g_bstrDebug,CDOSession,fldrOutbox,msgTarget,fldrTarget,msgResponse
Dim Rating,CritiqueTitle,ServerName,dateOfCritique,LDAPString,UserName
Dim ApproverEmail,ApprovalRequired,isApproved
Dim AuthName,bibNo,CritiqueNo,NewMessageID


'---------------------------------------------------------------------------
'Following are PropertyTags to retrieve the Standard MAPI properties
'which cannot be retrieved using Item("name")
'---------------------------------------------------------------------------

Const MAPI_PROPTAG_CRITIQUETITLE = &HE1D001F  'Subject Field
Const MAPI_PROPTAG_SERVERNAME  = &H6644001F   'Server Name
Const MAPI_PROPTAG_DATESUBMITTED = &H30080040 'Sent field
Const MAPI_PROPTAG_LDAPSTRING = &HC1F001F     'Connection String to Exchange
Const MAPI_PROPTAG_USERNAME = &HC1A001F       'User Name
'-----------------------------------------------------------------------------

Const cdoTo = 1

Const Approved = 1

Const ConnectionString = "DSN=Fmlib;UID=sa;PWD=;Database=Fmlib"
Const ApprovalFormSubject = "Critique Approval Required"

'----------------------------------------------------------------------
' Event Handlers
'----------------------------------------------------------------------

'DESCRIPTION This event is fired when  new message is posted in the folder.
Public Sub Folder_OnMessageCreated()
   On Error Resume Next
   Call DebugReport("LitCrit_Review - OnMessageCreated",False)
   Call GetEventDetails()
   If Err.Number = 0 Then
      Call MakeResponseMessage()
   Else 
     Call DebugReport("GetEventDetails",True)
   End If
   Script.Response = g_bstrDebug 
End Sub

'DESCRIPTION: This event is fired when a message is changed 
Public Sub Message_OnChange()
   Dim objCritique
 
   On Error Resume Next
 
   Call DebugReport("LitCrit_Review - OnMessageChange",False)
   Call GetEventDetails()
   If Err.Number = 0 Then 
      Call GetPropertiesFromLitCrit()
      ' If critique# is set and approval is required, then we resubmit
      ' otherwise, we just allow the update to occur
      If CritiqueNo <> 0 Then 

         Set objCritique = CreateObject("LitCrit.Critique")
         If Not IsObject(objCritique) Then
            Call DebugReport("Create LitCrit Object",True)
            Exit Sub
         End If
         objCritique.ConnectionString = ConnectionString

         If ApprovalRequired = 1 Then
            isApproved = 0
            'Send for approval and Delete From Public Folder
            Call CopyToApprover()
            Call SendApproverForm()
            msgTarget.Delete	' Delete event will run next time
         End If

         ' Update the database with this new info (it will not be copied after approved)
         Call DebugReport("UPDATE #" & CritiqueNo & ": " & CritiqueTitle & _
                          " rated: " & Rating & " date: " & dateOfCritique, False)
         objCritique.UpdateRecord CritiqueNo,NewMessageID,CBool(isApproved),Rating, _ 
                                  CritiqueTitle,CDate(dateOfCritique)

      Else 
         Call DebugReport("GetPropertiesFromLitCrit",True)
      End If
   Else
      Call DebugReport("GetEventDetails",True)
   End If
   Call D
   Script.Response = g_bstrDebug
End Sub

' DESCRIPTION: This event is fired when a message is deleted from the folder
Public Sub Folder_OnMessageDeleted()
   Dim objCritique

   On Error Resume Next

   Call DebugReport("LitCrit_Review - OnMessageDeleted",False)

   Set objCritique = CreateObject("LitCrit.Critique")
   If Not IsObject(objCritique) Then
      Call DebugReport("Create LitCrit Object",True)
   Else
      Call DebugReport("DELETE OBJECT:" & EventDetails.MessageID,False)
      objCritique.ConnectionString = ConnectionString
      objCritique.DeleteRecordByObjectID EventDetails.MessageID
   End If
 
   Script.Response = g_bstrDebug     
End Sub

' DESCRIPTION: This event is fired when the timer on the folder expires
Public Sub Folder_OnTimer()
	On Error Resume Next
        'Doing Nothing so far
End Sub

'----------------------------------------------------------------------
' DESCRIPTION: Get the details of the event that fired
'----------------------------------------------------------------------
Private Sub GetEventDetails()
   Dim idTargetFolder,idTargetMessage

   On Error Resume Next

   idTargetFolder = EventDetails.FolderID
   idTargetMessage = EventDetails.MessageID

   Set CDOSession = EventDetails.Session
   Call DebugReport("EventDetails.Session",True)

   If Err.Number = 0 Then
      ' We will send a msg, so let's get the Outbox here
      Set fldrOutbox = CDOSession.Outbox
      Call DebugReport("CDOSession.Outbox",True)

      If Err.Number = 0 Then
         Set fldrTarget = CDOSession.GetFolder( idTargetFolder, Null )
         Call DebugReport("CDOSession.GetFolder",True)
    
         If Err.Number = 0 Then
 	    Set msgTarget = CDOSession.GetMessage( idTargetMessage, Null )
	    Call DebugReport("CDOSession.GetMessage",True)
         End If
      End If
    End If
End Sub

'------------------------------------------------------------------------
' DESCRIPTION: Make a response message
' PARAMETERS: STRING SUBJECT OF THE MESSAGE
'------------------------------------------------------------------------
Private Sub MakeResponseMessage()
   Dim objCritique,borrowerNo
   On Error Resume Next
   'fldrTarget.Messages.Count

   Set objCritique = CreateObject("LitCrit.Critique")
   If Not IsObject(objCritique) Then
      Call DebugReport("Create LitCrit Object",True)
      Exit Sub
   End If

   objCritique.ConnectionString = ConnectionString
   Call GetPropertiesFromLitCrit()

   If CritiqueNo = 0 Then
     If bibNo <> 0 Then ' This is a library title
        'Get Information about the reviewer from borrower table or create new one 
        'resolving with exchange
        borrowerNo = objCritique.BorrowerInfo(LDAPString,ServerName)

        If borrowerNo <> 0 Then

           CritiqueNo = objCritique.AddRecord(bibNo,borrowerNo,CritiqueTitle, _
                                              NewMessageID,Rating,CDate(dateOfCritique), _
                                              isApproved) 

           If CritiqueNo <> 0 Then 
              If ApprovalRequired = 1 Then
                 'Send for approval, delete it from PF
		 Call CopyToApprover()
                 Call SendApproverForm()
                 msgTarget.Delete
              Else  ' Approval is not required
                 ' Add fields to the form since it doesn't go for approval process
                 msgTarget.Fields("CritiqueNo") = CritiqueNo
	         msgTarget.Fields("isApproved") = 1
                 msgTarget.Update True,True ' Commit changes, flush cache, reload 
              End If
           Else
              Call DebugReport("objCritique.AddRecord",True)
           End If
        Else
	  Call DebugReport("objCritique.BorrowerInfo",True)    
        End If 

     Else ' Title is not a library item (or was not looked up)
        ' Add fields to the form since it doesn't go for approval process
        msgTarget.Fields("CritiqueNo") = 0
	msgTarget.Fields("isApproved") = 1
        msgTarget.Update True,True ' Commit changes, flush cache,reload 
     End If

   Else ' CritiqueNo is set: this is an approval message
        ' update record in database  
      If isApproved = 1 Then 
         Call DebugReport("UPDATE #" & CritiqueNo & ": " & Mid(NewMessageID,93,44),False)
         objCritique.UpdateRecord CritiqueNo, NewMessageID, True
         Call DebugReport("Returned testing Update Method",True) 
      Else
         Call DebugReport("DELETE #" & CritiqueNo, False)
         objCritique.DeleteRecordByCritiqueNo CritiqueNo
         msgTarget.Delete ' triggers the delete event
      End If
   End If
End Sub

'--------------------------------------------------------------------------
'Desc: Getting the Passed Properties From Enhanced LitCrit Form
'Parameters: None
'------------------------------------------------------------------------- 
Private Sub GetPropertiesFromLitCrit()
   On Error Resume Next

   Select Case msgTarget.Fields("Overall Rating").Value
   Case "*":     Rating = 1
   Case "**":    Rating = 2
   Case "***":   Rating = 3
   Case "****":  Rating = 4
   End Select

   CritiqueTitle = msgTarget.Fields(MAPI_PROPTAG_CRITIQUETITLE).Value
   ServerName = msgTarget.Fields(MAPI_PROPTAG_SERVERNAME).Value
   dateOfCritique =  msgTarget.Fields(MAPI_PROPTAG_DATESUBMITTED ).Value
   LDAPString = msgTarget.Fields(MAPI_PROPTAG_LDAPSTRING).Value
   UserName = msgTarget.Fields(MAPI_PROPTAG_USERNAME).Value
  
   ApproverEmail = msgTarget.Fields("ApproverEmail").Value
   ApprovalRequired = msgTarget.Fields("ApprovalRequired").Value

   If ApprovalRequired = 1 Then
      isApproved = msgTarget.Fields("isApproved").Value
   Else
      ' Automatically assume this message is approved
      isApproved = 1
   End If
 
   AuthName = msgTarget.Fields("AuthName").Value
   bibNo = msgTarget.Fields("bibNo").Value
   CritiqueNo = msgTarget.Fields("CritiqueNo").Value
   OldUserName = msgTarget.Fields("OldUserName").Value
   NewMessageID = EventDetails.MessageID

   If Err.Number = 0 Then
	Call DebugReport("Processing Message: " & CritiqueTitle,False)
   Else
   	Call DebugReport("Getting Properties From LitCrit :",True)
   End If
End Sub

'--------------------------------------------------------------------------
'DESC: To Copy LitCrit Field Values to Approver Form before sending
'Parameters: Nothing
'--------------------------------------------------------------------------
Private Sub CopyToApprover()
   Set msgResponse = fldrOutbox.Messages.Add(ApprovalFormSubject,"","IPM.Post.ToApprover")
   Call DebugReport("fldrOutBox.Messages.Add",True)
   If Err.Number <> 0 Then Exit Sub

   '>> Copy the values from Enhanced LitCrit Form to Approver Form before sending 
   msgResponse.Fields.Add "ApprovalRequired",vbLong,1
   msgResponse.Fields.Add "ApproverEmail",vbString,ApproverEmail
   msgResponse.Fields.Add "AuthName",vbString,AuthName
   msgResponse.Fields.Add "bibNo",vbLong,bibNo
   msgResponse.Fields.Add "Clarity Rating",vbString,msgTarget.Fields("Clarity Rating").Value
   msgResponse.Fields.Add "CritiqueNo",vbLong,CritiqueNo
   msgResponse.Fields.Add "CritiqueText",vbString,msgTarget.Fields("CritiqueText").Value
   msgResponse.Fields.Add "isApproved",vbLong,isApproved
   msgResponse.Fields.Add "Item Title",vbString,msgTarget.Fields("Item Title").Value
   msgResponse.Fields.Add "Job Relevance",vbString,msgTarget.Fields("Job Relevance").Value
   msgResponse.Fields.Add "LongAuthor",vbString,msgTarget.Fields("LongAuthor").Value
   msgResponse.Fields.Add "LongMedia",vbString,msgTarget.Fields("LongMedia").Value
   msgResponse.Fields.Add "Media",vbString,msgTarget.Fields("Media").Value
   msgResponse.Fields.Add "Overall Rating",vbString,msgTarget.Fields("Overall Rating").Value
   msgResponse.Fields.Add "FolderID",vbString,EventDetails.FolderID
   msgResponse.Fields.Add "OldUserName",vbString,OldUserName
   msgResponse.Fields.Add "Tech Level",vbString,msgTarget.Fields("Tech Level").Value
   msgResponse.Update True, True
   Call DebugReport("Adding field values",True)
End Sub 

Private Sub SendApproverForm()
   msgResponse.Recipients.AddMultiple ApproverEmail,cdoTo
   Call DebugReport("MessageResponse.Recipients.Add",True)
   If Err.Number <> 0 Then Exit Sub

   msgResponse.Recipients.Resolve(False)	
   If msgResponse.Recipients.Resolved = True Then
      msgResponse.Send
      If Err.Number = 0 Then
         Call DebugReport("Approver form Sent",False)
      Else
         Call DebugReport("SendApproverForm",True)
      End If
   Else
      Call DebugReport("Recipient.Resolve",True)
   End If 
End Sub

'--------------------------------------------------------------------------
'Desc: Simple Debugging Function
'Parameters: String Text, Boolean ErrorFlag
'--------------------------------------------------------------------------
Private Sub DebugReport(bstrParm,boolErrChkFlag)
  If boolErrChkFlag = True Then
     If Err.Number <> 0 Then
        g_bstrDebug = g_bstrDebug & bstrParm & " Failed: " & Hex(Err.Number) & _
                      " -- " & Err.Description & vbCrLf
        Err.Clear
     End If
  Else
     g_bstrDebug = g_bstrDebug & bstrParm & vbCrLf
  End If
End Sub
</SCRIPT>
