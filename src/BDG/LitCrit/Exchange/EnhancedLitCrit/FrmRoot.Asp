<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/store.inc"-->
<!--#include file="../../../../lib/render.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<!--#include file="formutil.inc"-->
<!--#include file="bindprop.inc"-->

<!-- #include file="litcrit.inc" -->

<% SendHeader 0, 1 %>
<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN">
<% 
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- FrmRoot.asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->

On Error Resume Next

urlcommand   = Request.QueryString("command")
url          = Request.QueryString()
bstrObj      = Request.QueryString("obj")
strIndex     = Request.QueryString("index")
urlStore     = Request.QueryString("store")
bstrFolderID = Request.QueryString("ID")
iurlRespType = cint(Request.QuerySTring("rt"))

if urlStore="" Then iStore=-1 Else iStore=cint(urlStore)

iImportance     = 1 'default to normal
bstrError       = ""

x=CheckSession3(bstrVirtRoot + "/forms/IPM/Post/EnhancedLitCrit/frmroot.asp?"+url+"&timedout=1","self",iStore)

bstrMsgType = "IPM.Post.EnhancedLitCrit"

'do own checkindex (avoid pageutil (15k))
If Len(strIndex) > 0 Then
   iIndex = CInt(strIndex)
   Session(CURRENT_INDEX) = iIndex
End If

fHasAttach = 0

Set objRenderer = GetObjectRenderer
OpenAllStores

fIsReplyToFolder= false
If bstrFolderID = "" Then
    Set objFolder = Session(CURRENT_FOLDER)
Else
    Set objFolder = OpenFolder(bstrFolderID)
End If
nAccess = objFolder.Fields.Item(ActMsgPR_ACCESS)
bCanPost = nAccess And MAPI_ACCESS_CREATE_CONTENTS
bCanDelete = nAccess And MAPI_ACCESS_DELETE

If urlcommand = "new" Then
  If  bstrObj="" Then
     Randomize
     bstrObj = cstr(int(100000 * Rnd()))
     If bCanPost <> 0 then
       bstrFormMode = "compose"
       bstrTitle = "New " & "EnhancedLitCrit"
       bstrSubject = "<untitled>"
       Set objOneMsg =  objFolder.Messages.Add(bstrSubject,,bstrMsgType)
       Set Session(bstrObj) = objOneMsg
       AddIDToCache(bstrObj)

       '=== LITCRIT-SPECIFIC
       firstPage = "Message.asp"
       Call SetLitCritFieldsFromURL

     End If

  ' set all the initial values
  SetInitialValue "{2903020000000000C000000000000046}Clarity Rating", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Job Relevance", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  ' LITCRIT: LongMedia already set by SetLitCritFieldsFromURL
  ' SetInitialValue "{2903020000000000C000000000000046}LongMedia", 8, 0, "<untitled>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Media", 8, 0, "Book", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Overall Rating", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  SetInitialValue &H0037001f, 8, -1, "<untitled>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Tech Level", 8, 0, "<Select Rating>", 0, 1, objOneMsg

If objOneMsg.ID <> "" then 
  
   If iurlRespType <> CDO_Forward Then
       objOneMsg.Importance = 1
   End If   
   

End If


    'Set initial value for body field
 
    objOneMsg.Text = "" 
  Else 
    set objOneMsg = Session(bstrObj)
     fIsReplyToFolder=true
     If "<untitled>" <> "" Then
       objOneMsg.Subject = "<untitled>"
     End If
     bstrTitle = objOneMsg.Subject
     objOneMsg.Type = "IPM.Post.EnhancedLitCrit"

  ' set all the initial values
  SetInitialValue "{2903020000000000C000000000000046}Clarity Rating", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Job Relevance", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  ' LITCRIT: LongMedia already set by SetLitCritFieldsFromURL
  ' SetInitialValue "{2903020000000000C000000000000046}LongMedia", 8, 0, "<untitled>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Media", 8, 0, "Book", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Overall Rating", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  SetInitialValue &H0037001f, 8, -1, "<untitled>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Tech Level", 8, 0, "<Select Rating>", 0, 1, objOneMsg
If objOneMsg.ID <> "" then 
  
   If iurlRespType <> CDO_Forward Then
       objOneMsg.Importance = 1
   End If   
   If iurlRespType <> CDO_Forward Then
       objOneMsg.Fields.Item(ActMsgPR_Sensitivity) = 0
   End If   

End If

    bstrFormMode = "compose"
     
  End If
Else
  'Get the message from the cache
  Set objOneMsg = Session(bstrObj)
  If objOneMsg Is Nothing Then
     Set objOneMsg = OpenMessage(bstrObj)
     If objOneMsg.ID="" Then
		    If Request.QueryString("timedout")<>"" Then 'session timedout - lost message
			    bstrError = "<b>" + L_Error_ErrorMessage + "<br><br>" _ 
		               + L_errFailOpenMessage_ErrorMessage + "</b><br>" _
		               + L_errMessageTimedOut_ErrorMessage
		    
		    Else
			    bstrError = "<b>" + L_Error_ErrorMessage + "<br><br>" _ 
		               + L_errFailOpenMessage_ErrorMessage + "</b><br>" _
		               + L_errMessageDeleted_ErrorMessage
		    End If
     Else
       Set Session(bstrObj) = objOneMsg
       AddIDToCache(bstrObj)
     End If
  End If
  bstrFormMode = "read"
  If Session(bstrAuthenticated) Then
    objOneMsg.Unread = False
    objOneMsg.Update
  End If
  bstrTitle = objOneMsg.Subject
  
  fHasAttach = 0 'Assume false
  fAttachments = false 'Assume false
  fAttachments = objOneMsg.Fields.Item(ActMsgPR_HASATTACH)
  If fAttachments then
     fHasAttach = 1
  End If

  ' set all the initial values
  SetInitialValue "{2903020000000000C000000000000046}Clarity Rating", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Job Relevance", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  ' LITCRIT: LongMedia already set by SetLitCritFieldsFromURL
  ' SetInitialValue "{2903020000000000C000000000000046}LongMedia", 8, 0, "<untitled>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Media", 8, 0, "Book", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Overall Rating", 8, 0, "<Select Rating>", 0, 1, objOneMsg
  SetInitialValue &H0037001f, 8, -1, "<untitled>", 0, 1, objOneMsg
  SetInitialValue "{2903020000000000C000000000000046}Tech Level", 8, 0, "<Select Rating>", 0, 1, objOneMsg
End If

Dim bstrTabMainFiles(7)
iCurTab = 1
If bstrFormMode = "compose" Then
bstrTabMainFiles(iCurTab) = firstPage '--- WAS: "Message.asp"
  iCurTab = iCurTab + 1
bstrTabMainFiles(iCurTab) = "Stock_Attachments.asp"
  iCurTab = iCurTab + 1
Else
bstrTabMainFiles(iCurTab) = "Message-Read.asp"
  iCurTab = iCurTab + 1
bstrTabMainFiles(iCurTab) = "Stock_Attachments.asp"
  iCurTab = iCurTab + 1
End If
iImportance = objOneMsg.Importance

If Session("Registry" & bstrObj) Is Nothing then
    Set objFormFieldsRegistry = Server.CreateObject("Scripting.Dictionary")
Else
    Set objFormFieldsRegistry = Session("Registry" & bstrObj)
End If
     
Set Session("Registry" & bstrObj) = objFormFieldsRegistry 

' Add items to Registry
If bstrFormMode = "compose" Then %>
<!--#include file="Message.inc"-->
<!--#include file="Page_2.inc"-->
<!--#include file="Page_3.inc"-->
<!--#include file="Stock_Attachments.inc"-->
<% Else %>
<!--#include file="Message-Read.inc"-->
<!--#include file="Page_2-Read.inc"-->
<!--#include file="Page_3.inc"-->
<!--#include file="Stock_Attachments.inc"-->
    
<% End If %>

<HTML><HEAD><TITLE><% objRenderer.Write bstrTitle, Response%></TITLE></HEAD>
<% if bCanPost=0 And urlcommand = "new" Then %>
<Body><table cellpadding=0 cellspacing=0 border=0 width=100%><TR>
<td align=center><FONT SIZE=4><b>You do not have the necessary permissions to post to this folder.</b>
<br><br>Contact your Exchange Administrator for assistance or choose another folder.<br><br>
<A href="JAVASCRIPT:self.close()"><b>Close</b></font></a>
</b></font><br></td></TR></table>
<% ElseIf bstrError="" Then %>
<!--#include file="jscript.inc"-->
<SCRIPT language='javascript'>
var fSessionTimedout = false;
var iCurStore    = <%=iStore%>;
var iCurForm       = 3;
var iNextForm      = 1;
var fBusyTabbing   = true;
var fLockForm      = false;
var iImportance    = <%=iImportance%>;
var fHasAttachments= <%=fHasAttach%>;
var fMode          = "<%=bstrFormMode%>";
var fCanPost       = <%=bCanPost%>;
var fCanDelete     = <%=bCanDelete%>;
<% if fIsReplyToFolder Then %>
var fIsReplyToFolder = true;
<% else %>
var fIsReplyToFolder = false;
<% end if %>

function errMsg_ReadOnly() {
    alert("You have modified a read-only field. \n\n"+
          "Any changes to this field will not be saved.");
}

function submitForm(szCommand, form, fLock) {
   if (iCurForm==2) {   //don't submit attachments form!
      window.command_fr.location="commands.asp?command=" + szCommand + "&obj="+form.objID.value + "&reply=" + (fIsReplyToFolder?"1":"0")+"&imp="+iImportance; 
   }
   else {
      fLockForm = fLock;
      form.command.value = szCommand;
      form.replytofolder.value=(fIsReplyToFolder ? 1 : 0);
      form.importance.value=iImportance;
      form.submit();
   }
}
function DoCommand(szCommand, form) {
  sendFlag = true
  theMessage = ""
  if (fLockForm != true) {
      if (szCommand == "bind") {
        submitForm(szCommand, form, false);
      }
      else if (szCommand != "cancel") {
        submitForm(szCommand, form, true);
      }
      else {
        window.command_fr.location="commands.asp?command=cancel&obj=<%=bstrObj%>";
        window.close();
      }
  }
}
    
function gotoForm(iForm) {
   if (iCurForm != iForm && iForm != 2) {
      self.title_fr.location="PostTitl.asp?obj=<%=bstrObj%>&tab="+iForm + "&att="+fHasAttachments+"&imp="+iImportance+"&fmode="+fMode+"&canpost=<%=bCanPost%>&candelete=<%=bCanDelete%>";
   }
   if (false) {
   }
<% iCurTab = 1 %>
<% If bstrFormMode = "compose" Then %>
else if (iForm==<%=iCurTab%>) {
      self.form_fr.location="Page_3.asp?obj=<%=bstrObj%>"; // LITCRIT USES PAGE_3 FOR COMPOSE
   }
<% iCurTab = iCurTab + 1 %>
else if (iForm==<%=iCurTab%>) {
      self.form_fr.location="Stock_Attachments.asp?obj=<%=bstrObj%>";
   }
<% iCurTab = iCurTab + 1 %>
<% Else 'Read Mode %>
else if (iForm==<%=iCurTab%>) {
      self.form_fr.location="Message-Read.asp?obj=<%=bstrObj%>";
   }
<% iCurTab = iCurTab + 1 %>
else if (iForm==<%=iCurTab%>) {
      self.form_fr.location="Stock_Attachments.asp?obj=<%=bstrObj%>";
   }
<% iCurTab = iCurTab + 1 %>
<% End If %>
   iCurForm=iForm;
}

function AttachFile(form) {
    window.title_fr.location="<%=bstrVirtRoot%>/forms/copynew.asp";
    window.command_fr.holdSession();
    fLockForm=true;
    fBusyUploading=true;
    form.submit();
}
</SCRIPT>
<%
bstrFrameHeight = "45" 'Default size
If bstrFormMode = "read" then
     bstrFrameHeight = "45" 'Increase the size of this value if you need more room
                                    'for custom actions
End If     
%>
<FRAMESET ROWS="<%=bstrFrameHeight%>,100%,*" border=0 frameborder=no bordercolor=e7e7d6> 
   <FRAME SRC='postTitl.asp?tab=1&att=<%=fHasAttach%>&imp=<%=iImportance%>&fmode=<%=bstrFormMode%>&canpost=<%=bCanPost%>&obj=<%=bstrObj%>&folderID=<%=objOneMsg.FolderID%>&candelete=<%=bCanDelete%>' name="title_fr" marginheight=0 marginwidth=0 scrolling=no>
   <FRAME SRC="<%=bstrTabMainFiles(1)%>?obj=<%=bstrObj%>" name=form_fr  noresize marginheight=0 marginwidth=0 scrolling=auto>
   <FRAME SRC="commands.asp?obj=<%=bstrObj%>" name="command_fr" marginheight=0 marginwidth=0 scrolling=no>
</FRAMESET>
<body bgcolor='c0c0c0'>
<NOFRAMES>
Microsoft Outlook Web Access must be viewed on a browser that supports frames. <br>
To obtain such a browser, please click <a href="http://www.microsoft.com/ie/download/" target="_blank">here</a> to 
download the Microsoft <a href="http://www.microsoft.com/ie/download" target="_blank"><b>Internet Explorer</b></a>.
</NOFRAMES>
<% Else %>
	<center><font size=4><%=bstrError%><br><br>
	<a href='javascript:window.close()'>OK</a></b></font>
<% End If %>
</body></HTML>
