<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<!--#include file="../../../../lib/store.inc"-->
<% SendHeader 0, 1 %>
<!--#include file="../../../../lib/render.inc"-->
<!--#include file="../../../../lib/delete.inc"-->
<!--#include file="formutil.inc"-->
<!--#include file="bindprop.inc"-->
<% 
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- Commands.asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
    
On Error Resume Next
iRespType = 0 'Global flag for identifying resonse type. ie... Reply, Forward etc...   See bindprops.inc for definitions
fm__szErrMsg="" 'GLOBAL: indicates error state for custom forms

urlCommand = Request.QueryString("command")
bstrObj = Request.QueryString("obj")

bstrMsgType = "IPM.Post.EnhancedLitCrit"

If bstrObj = "" then
  bstrObj = Request.Form("objID")
End If

'Event handler code - Compose new, Open unsubmitted, Open submitted
If urlCommand <> "" then
   bstrCommand       = urlCommand
   bstrReplyToFolder = Request.QueryString("obj")
   bstrImportance    = Request.QueryString("imp")
Else
   bstrCommand       = Request.Form("command")
   bstrTab           = Request.Form("tab")
   bstrReplyToFolder = Request.Form("replytofolder")
   bstrImportance    = Request.Form("importance")
End If

fSessionTimedout = False
fSingleFrame = False
'Need to call checksession2 if commands is run as single window during a response.
If left(bstrCommand,5)="reply" or bstrCommand="forward" Then
    CheckSession2 bstrVirtRoot+"/forms/IPM/Post/EnhancedLitCrit/commands.asp?" + Request.QueryString()
    fSingleFrame = True 
ElseIf bstrCommand = "delete" or bstrCommand = "" then
    fSingleFrame = True
    CheckSession2 bstrVirtRoot+"/forms/IPM/Post/EnhancedLitCrit/commands.asp?" + Request.QueryString() 
Else

    If bstrCommand="timedout" Then
        x = CheckSession3("1","newwindow", Request.QueryString("store"))
    Elseif Not SessionIsValid() Then
        fSessionTimedout = true 'flag to call commands.asp with store id on url
        bstrCommand      = ""
    End If
End If

bstrBodyTag = "<body text=000000 link=cccc99 vlink=cccc99 onLoad=""statusAlert()"">"
bstrNewObj = ""
bstrFormPath = bstrVirtRoot + "/forms/IPM/Post/EnhancedLitCrit/frmRoot.asp"

Select Case  bstrCommand
    Case "1" 'Response for Reply
        bstrNewObj = CreateObjID()
        bstrClassPath = "IPM/Note"
        If bstrClassPath = "" then
            bstrClassPath = "/ipm/note"
        End If
        bstrFormPath = bstrVirtRoot & "/forms/" & bstrClassPath & "/"
        bstrPrefix = "RE"
        If bstrPrefix <> "" then
            bstrPrefix =  bstrPrefix & ": "
        End If
        Set objMsg = GenerateResponse(0, 0, 1,  bstrFormPath, bstrBodyTag, bstrPrefix, bstrClassPath)
        'Set the message class for the new message.
        bstrMessageClass = "IPM.Note"
        If bstrMessageClass <> "" then
            objMsg.Type = bstrMessageClass
        Else
            objMsg.Type = "IPM.Note"
        End If
    Case "post" 
      Set objNewMsg = Session(bstrobj)
      BindData(bstrTab)
      IF Len(fm__szErrMsg) = 0 THEN 'field validation failed so don't send
        fm__szErrMsg = ValidateRequiredFields()
        IF Len(fm__szErrMsg) = 0 THEN 'everything hunky-dory
              strUserName = objOMSession.CurrentUser.Name
              'If the current user has no name then sender must be logged in anonymously.
              If "" = strUserName then
                 strUserName = L_AnonymousUser_Text
              End If       
              oMsgFields.Add ActMsgPR_SENT_REPRESENTING_NAME, strUserName
              SubjPrefix  = Request.Form("subjprefix") & " "   'Space is removed by form
              objNewMsg.Fields.Add ActMsgPR_SUBJECT_PREFIX, SubjPrefix

              objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_NAME) = strUserName
              objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS) = objOMSession.CurrentUser.Address

              objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_ADDRTYPE) = objOMSession.CurrentUser.Type
              objNewMsg.TimeReceived = Now 
              objNewMsg.TimeSent = Now
              objNewMsg.Sent = True 
              objNewMsg.Submitted = True 
              objNewMsg.Unread = True

              objNewMsg.Type = "IPM.Post.EnhancedLitCrit"
              Err.Clear
              If objNewMsg.Attachments.Count <> 0 then
                objNewMsg.Text = vbCrLf + objNewMsg.Text
              End If
              objNewMsg.Update
              If Err.Number <> 0 Then
                      If MAPI_E_NO_ACCESS = Err.Number Then
                        'You do not have permission to create items in this folder.
                          ReportErrorClose L_errCreateItemPermision_ErrorMessage
                      Else
                        'There were problems sending the message. Try again or cancel.
                        ReportErrorClose L_errMessage004_ErrorMessage
                      End If
              Else
        
                MessageSent="post"
                Set Session(bstrobj) = nothing
RemoveIDFromCache(bstrobj)
              End If
        END IF
      END IF
    Case "delete"
      
      Err.Clear
      OpenAllStores
      DeleteItemByID bstrObj, False
      If Err.Number <> 0 Then
        ReportError1 L_errFailDeleteMessage_ErrorMessage
      Else
        Set Session(bstrObj) = Nothing
RemoveIDFromCache(bstrobj)
        bstrBodyTag = "<body bgcolor=FFFFFF onLoad=""parent.close()"">"
      End If

    Case "cancel"
    'If the user canels then dismiss the window and kill the session object
     Set Session(bstrObj) = Nothing
     RemoveIDFromCache(bstrobj)

     '=== LITCRIT SPECIFIC: Workaround for OWA "anon/auth" switching
     '--- For reasons discussed in the BDG text, this workaround may make
     '--- the problem go away, but it doesn't really fix it.

     ' ClearSession
          
    Case "save"
        Set objNewMsg = Session(bstrobj)
        If objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_NAME) <> "" Then
            'Todo - This causes the reply method to error out if it is deleted.
            'objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_NAME).Delete 'in case post
        End If
        err.clear
        BindData(bstrTab)
               
        
        objNewMsg.Update
        
        Set Session(bstrObj) = objNewMsg
        If Err.Number <> 0 then
            ReportError1 L_errFailSaveMessage_ErrorMessage
        End If
    
    Case "bind"
        Set objNewMsg = Session(bstrObj)
        BindData(bstrTab) 
     Case "next"
        Set Session(bstrObj) = Nothing
RemoveIDFromCache(bstrObj)
        bstrBodyTag = "<body onLoad=top.location='"+ bstrVirtRoot + "/item.asp?action=next';>"
    Case "previous"
        Set Session(bstrObj) = Nothing
RemoveIDFromCache(bstrObj)
        bstrBodyTag = "<body onLoad=top.location='"+ bstrVirtRoot + "/item.asp?action=prev';>"
       

End Select    

Sub BindData(bstrThisTab)
    On Error Resume Next

    fm__szErrMsg = BindCustomFields()
    'importance allways get bound (set in title at any time)
    objNewMsg.Importance = CInt(bstrImportance)

    For Each item In Request.Form
        bstrCtrlName = lcase(item)
       
        If bstrCtrlName="message" Then
            If Request.Form("message") <>"" Then
              bstrText    = Request.Form("message")
              If isMSIE then
                If isMac then 
                  If getVersion() < 4 then 
                    bstrText = Replace(bstrText,vbCRLF + chr(10), vbCRLF)           
                  End If
                End If
              End If
              objNewMsg.Text = bstrText
            End If         
        ElseIf  bstrCtrlName="subject" Then
            objNewMsg.Subject = Request.Form("subject")
            ' Set PR_SUBJECT_PREFIX to enable proper generation of 
            ' PR_NORMALIZED_SUBJECT and PR_CONVERSATION_TOPIC
            oMsgFields.Add ActMsgPR_SUBJECT_PREFIX, L_ReplyPrefix_Text
        ElseIf  bstrCtrlName="sensitivity" Then
            objNewMsg.Fields.Item(ActMsgPR_SENSITIVITY) = CInt(Request.Form("sensitivity"))
        ElseIf  bstrCtrlName="keywords" Then
            bstrKeywordData = Request.Form("keywords")
            If "" <> bstrKeywordData Then
            SetKeywords objNewMsg.Fields, bstrKeywordData
            End If
        ElseIf  bstrCtrlName="importance" Then
            objNewMsg.Importance = CInt(Request.Form("importance"))
        End If

    Next

    If bstrReplyToFolder<>"1" Then 'original convesation topic perist on replytofolder
      If objNewMsg.ConversationIndex = "" Then
         objNewMsg.ConversationIndex = objOMSession.CreateConversationIndex
      End If
      If objNewMsg.ID = "" Then
        objNewMsg.ConversationTopic = objNewMsg.Subject
      End If
    End If
    Err.Clear
End Sub



Function GenerateResponse(iAddressLike, iAction, iReply, bstrFormPath, bstrBodyTag, bstrPrefix, bstrClsPath)
    On Error Resume Next
    Set objOneMsg = Session(bstrObj)
    
    If objOneMsg Is Nothing then
      Set objOneMsg = OpenMessage(bstrObj)
    End If
            
    If objOneMsg.ID = "" Then
        bstrError = "<b>" + L_Error_ErrorMessage + "<br><br>" _
        + L_errFailOpenMessage_ErrorMessage + "</b><br>" _
        + L_errMessageDeleted_ErrorMessage
    End If

    'Create a new message in memory
      If instr(1,bstrClsPath, "ipm/note", 1) > 0 then
        iRespMethod = 10 'Sendable Message
    ElseIf instr(1,bstrClsPath, "ipm/post", 1) > 0 then
        iRespMethod = 20 'Postable Message
    ElseIf instr(1,bstrClsPath, "ipm/contact", 1) > 0 then
        iRespMethod = 30 'Contact item
    ElseIf instr(1,bstrClsPath, "ipm/appointment", 1) > 0 then
        iRespMethod = 40 'Appointment item
    Else
        iRespMethod = 999 'Other
    End If

    iCreateMethod = iAddressLike + iRespMethod
    iRespType = iAddressLike + 1
     Select Case iCreateMethod
        Case 10 'Send and address like Reply 
            Set objNewMsg = objOneMsg.Reply
        Case 11 'Send and Address like ReplyAll
            Set objNewMsg = objOneMsg.ReplyAll
        Case 12  'Send Address like Forward
            Set objNewMsg = objOneMsg.Forward
        Case 13 'Send Address like ReplyToFolder
            Set objNewMsg = objOneMsg.Reply
            objNewMsg.Recipients.Delete
        Case 20, 21, 22, 23
            Set objNewMsg = CreateReplyToFolder(objOneMsg)
        Case 30, 31, 32, 33
            Set objNewMsg = CreateReplyToFolder(objOneMsg)
        Case 40, 41, 42, 43
            Set objNewMsg = CreateApptItem()
            bstrFormPath = bstrVirtRoot + "/forms/ipm/schedule/meeting/request/"
        Case Else
            Set objNewMsg = CreateReplyToFolder(objOneMsg)
    End Select
    
        
    If iAction = 0 or iaction = 1 then 'Open or send immediately are treated the same
        bstrFormPath = bstrFormPath & "frmRoot.asp"
        bstrBodyTag = "<body text=000000 onLoad=""LaunchForm('" + bstrFormPath + "')"">"
    Elseif iAction = 2 then
        bstrFormPath = bstrFormPath & "frmRoot.asp"
        bstrBodyTag = "<body text=000000 onLoad=""LaunchForm('" + bstrFormPath + "')"">"
    End if
    
    objNewMsg.Subject = ""
    bstrFolderName = GetFolderName(objOneMsg.FolderID)
    InitResponse objOneMsg, objNewMsg, iAddressLike, iReply, bstrFolderName, bstrPrefix
    Set Session(bstrNewObj) = objNewMsg
    AddIDToCache(bstrNewObj)

    'Delete source message in memory
    Set Session(bstrObj) = Nothing
RemoveIDFromCache(bstrObj)
    Set GenerateResponse = objNewMsg    
End Function


Sub InitResponse (srcMsg, objNewMsg, iResponsetype, iReply, bstrFolderName, bstrSubjectPrefix)
    On Error Resume Next
    Set objRenderer = GetObjectRenderer
    objRenderer.DataSource = srcMsg

    If iReply <> 0 then 'Do not include original message text if iReply = 0
        lSensitivity = 0
        lSensitivity = srcMsg.Fields.Item(ActMsgPR_SENSITIVITY)
        Select Case lSensitivity
            Case 0
            'Normal
                bstrSensisitivity = ""
            Case 1
                'Personal
                bstrSensisitivity = L_HeaderSensitivity_Text & " " & L_Personal_Text & vbCrLf
            Case 2
                'Private
                bstrSensisitivity = L_HeaderSensitivity_Text & " " & L_Priv_Text & vbCrLf
            Case 3
                'Confidential
                bstrSensisitivity = L_HeaderSensitivity_Text & " " & L_Confidential_Text & vbCrLf
        End Select
        lImportance = srcMsg.Importance

        If lImportance = ActMsgHigh then
            bstrImportance = L_HeaderImportance_Text& " " & L_High_Text & vbCrLf
        ElseIf lImportance = ActMsgLow then
            bstrImportance = L_HeaderImportance_Text & " " & L_Low_Text & vbCrLf
        Else
            bstrImportance = ""
        End If
        bstrConversation = srcMsg.ConversationTopic

        If bstrConversation <> "" then
            bstrConversationDisplay = L_HeaderConversation_Text & " " & bstrConversation & vbCrLf
        Else
            bstrConversationDisplay = ""
        End If

       bstrMessageData = " " & vbCrLf & " "  & vbCrLf & "-----" & L_OriginalMessage_Text & "-----" & vbCrLf 
       
       
        bstrPostedAt  = L_HeaderPostedAt_Text & " " & objRenderer.RenderProperty(ActMsgPR_CLIENT_SUBMIT_TIME)  & vbCrLf
        bstrSubject = srcMsg.Subject
        If bstrSubject <> "" then
            bstrSubject = L_HeaderSubject_Text  & " "& bstrSubject & vbCrLf
        End If
        bstrPostedFrom   = L_HeaderFrom_Text & " " & srcMsg.Fields.Item(ActMsgPR_SENDER_NAME) & vbCrLf
        bstrPostedTo = L_HeaderPostedTo_Text & " " & bstrFolderName & vbCRLF
        rgbstrKeywordData = srcMsg.Fields("Keywords")
        
        If vartype(rgbstrKeywordData) = vbArray + vbVariant then
          bstrKeywords       = L_HeaderKeywords_Text & " "
          For i = LBound(rgbstrKeywordData) to Ubound(rgbstrKeywordData)
            If i=Ubound(rgbstrKeywordData) Then
                bstrKeywords=bstrKeywords + rgbstrKeywordData(i)
            Else
                bstrKeywords = bstrKeywords + rgbstrKeywordData(i) & ";" 
            End If
          Next
          bstrKeywords = bstrKeywords + vbCrLf
          objNewMsg.Fields.Add "Keywords", &H2000, rgbstrKeywordData   ' vbArray
        Else
          bstrKeywords = ""
        End If
        
        bstrMessageData  = bstrMessageData & bstrPostedFrom & bstrPostedAt  & bstrPostedTo & bstrConversationDisplay & bstrKeywords & bstrImportance & bstrSensisitivity & bstrSubject & vbCRLF
    
        bstrMessageData = bstrMessageData + objRenderer.RenderProperty( AMHTMLPLAIN_BODY)
        objNewMsg.Text  = bstrMessageData
    Else
        objNewMsg.Text = "" 'Clean out the text field
        objNewMsg.Attachments.Delete 'Wipe out attachments
        objNewMsg.Fields.Item(ActMsgPR_HASATTACH).Delete
    End If  'End Message body textizing   
    objNewMsg.Categories=srcMsg.Categories

    'Delete outlook specific fields 
    objNewMsg.Fields.Item(&H10800003).Delete
    objNewMsg.Fields.Item(&H10810003).Delete
    objNewMsg.Fields.Item(&H10820040).Delete
   
    If iResponsetype = 2 and objNewMsg.Fields.Item(ActMsgPR_HASATTACH) Then ' Forward case
        objNewMsg.Importance = srcMsg.Importance
        Set objAttachCol = objNewMsg.Attachments
        For each objAttach in objAttachCol
            objAttach.Position = 1
        Next
    Else
        objNewMsg.Attachments.Delete
    End If
    
    If iResponsetype = 3 then 'Reply to folder
      
        objNewMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_ADDRTYPE) = srcMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_ADDRTYPE)
        objNewMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS)  = srcMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS)
        objNewMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_NAME) = srcMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_NAME)
    End If
    
    If iResponsetype <> 3 then 'Not equal to replytofolder
      bstrSubjectData = bstrSubjectPrefix & srcMsg.Fields.Item(ActMsgPR_NORMALIZED_SUBJECT)
      objNewMsg.Subject = bstrSubjectData
    End If
    objNewMsg.Fields.Item(ActMsgPR_SENSITIVITY) = srcMsg.Fields.Item(ActMsgPR_SENSITIVITY)
    objNewMsg.ConversationTopic = srcMsg.ConversationTopic
    objNewMsg.ConversationIndex = objOMSession.CreateConversationIndex(srcMsg.ConversationIndex)
End Sub


Public Sub SetKeywords( objMsgFields, KeywordStr)
    bstrList = KeywordStr
    iLength = Len(KeywordStr)
    ' Convert commas to semicolons
    bstrList = Replace(bstrList, ",", ";")
    ' Copy tokens to Keywords array
    StartPos = 1
    NumWords = 0
   Do
        EndPos = InStr(StartPos, bstrList, ";", 1)
        If EndPos = 0 Then
            If StartPos <= iLength Then
                bstrItem = Trim(Mid(bstrList, StartPos, iLength))
                ReDim Preserve Keywords(Numwords)
                Keywords(Numwords) = bstrItem
                Exit Do
            Else
                Exit Do
            End If
        End If
        bstrItem = Trim(Mid(bstrList, StartPos, EndPos - StartPos))
        If bstrItem <> "" Then
            ReDim Preserve Keywords(Numwords)
            Keywords(Numwords) = bstrItem
            Numwords = Numwords + 1
        End If
        StartPos = EndPos + 1
    Loop
    objMsgFields.Add "Keywords", &H2000, Keywords       ' vbArray
End Sub


%>

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<!--#include file="../../../../lib/jsutil.inc"-->
<script language='javascript'>
    var holdMinutes=5;
    var holdMs=60000 * holdMinutes; //5 min we could get the current session timeout if we felt like it?
    var L_SessionHasTimedOut_Message = "Your session under this message has timed out.  You may use this window only to copy any unsaved work you may have.";

    function holdSession() {
      setTimeout("self.location='commands.asp?command=holding'",holdMs);
    }

<%If fSingleFrame = False then %>
    if (parent.fSessionTimedout == true) {
        <% if urlCommand<>"timedout" and urlCommand<>"cancel" Then %>
        alert (L_SessionHasTimedOut_Message);
        parent.fLockForm = false;
        parent.fBusyTabbing = false;
        <% end if %>
    }
    else {
    <% if fSessionTimedout Then %>
        parent.fSessionTimedout = true;
        self.location = "<%=bstrVirtRoot%>/forms/IPM/Post/EnhancedLitCrit/commands.asp?command=timedout&store="+parent.iCurStore;
        parent.fLockForm = false;
        parent.fBusyTabbing = false;
    <% Else %>

            <% if urlCommand="holding" then %>
              parent.fLockForm = true;
              setTimeout("self.location='commands.asp?command=holding'",holdMs);
            <% else %>
              parent.fLockForm = false;
            <% end if %>


    <% End If %>
    }

    function statusAlert() {
        if (parent.fSessionTimedout == false) {
            <%IF len(fm__szErrMsg)>0 AND MessageSend<>"error" THEN%>
                alert("<%=fm__szErrMsg%>");
                parent.gotoForm(parent.iCurForm);
            <%ELSE%>
            <% If bstrCommand="bind" Then
%>
                parent.gotoForm(parent.iNextForm);
            <% ElseIf MessageSent="post" Then %>
                parent.close();
            <% ElseIf MessageSent="failure" Then %>
               var L_MessagePostError_Message = "There were problems posting the message. Try again or cancel.";
               alert(L_MessagePostError_Message);
            <% ElseIf MessageSent="error" Then %>
                alert("<%=AlertMessage%>");
            <% End If %>
            <%END IF %>
        }
        else {
              parent.fLockForm = false;
        }
    }
<%End If%>
function LaunchForm(szFormPath) {
  openNewWindow(szFormPath + "?command=new&obj=<%=bstrNewObj%>&rt=<%=iRespType%>",'newMessageWindow',640,500);
  parent.close();
}
</script>
<TITLE>IPM.Post.EnhancedLitCrit</TITLE>
<%If bstrCommand <> "" then%>
    <%=bstrBodyTag%>
<%Else%>
    <body>
<%End If%>
</body>
</HTML>
