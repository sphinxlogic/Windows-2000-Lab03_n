<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<% SendHeader 0, 1 %>
<!--#include file="../../../../lib/attach.inc"-->
<%
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- Stock_Attachments.asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->

bcMsgBdy="c0c0c0"
bcMsgHdr="a0a0a0"

On Error resume next
bstrObj = Request.QueryString("obj")
CheckSession2 bstrVirtRoot + "/forms/IPM/Post/EnhancedLitCrit/frmroot.asp?command=open&obj="+bstrObj+"&timedout=1"
urlDelete = Request.QueryString("delete")
ffname = Request.QueryString("ffname")
ffnameTMP = Request.QueryString("ffNameTMP")
ffNameTYPE = Request.QueryString("ffNameTYPE")
Set objMsg = Session(bstrObj)
Set objAttachColl = objMsg.Attachments
If ffnameTMP <>"" then
	Set objAttach = AddAttachment(objMsg, ffnameTMP, ffNameTYPE, ffname)		
    objMsg.Update False
elseif urlDelete<>"" then
   DeleteAttachments urlDelete, objAttachColl 
End If

If objAttachColl.Count <> 0 then
	fHasAttach = 1
Else
	fHasAttach = 0
End If

'Table(pixels) to field width adjustments
   nTWfactor = Session("nTWfactor")
   L_AttachmentFieldWidth_Number = 410 '2/3 width of window in pixels
   iFileInputWidth = cint((L_AttachmentFieldWidth_Number * (nTWfactor)) + ((L_AttachmentFieldWidth_Number-1000)\1000) - 10)

%>
<HTML>
<script language='javascript'>
parent.fLockForm = false;
parent.fHasAttachments=<% If fHasAttach Then %> 1 <% Else %> 0 <% End If %>;
parent.title_fr.location="<%=bstrVirtRoot%>/Forms/IPM/Post/EnhancedLitCrit/postTitl.asp?obj=<%=bstrObj%>&tab="+parent.iCurForm+"&att=<%=fHasAttach%>&imp="+parent.iImportance+"&fmode="+parent.fMode+"&canpost="+parent.fCanPost+"&candelete="+parent.fCanDelete;

if (parent.fBusyUploading) {
	parent.fBusyUploading=false;
	top.command_fr.location='commands.asp';
}

function DeleteMarkedFiles() {
   var url="";
   var elementName="";
   thisForm=self.document.mainForm;
   for (count=thisForm.elements.length-1; count>=0; count--) { 
    //mangle the name since 'element.type' isn't supported by IE
    elementName=thisForm.elements[count].name;
    if (elementName.substring(0,1)=="_") {
      if (thisForm.elements[count].checked){ 
        url = url + ";" + thisForm.elements[count].value;
	  }
    }
   }
   self.location="Stock_Attachments.asp?obj=<%=bstrObj%>&delete="+url;
}

</script>
<body onLoad="parent.fBusyTabbing = false;" bgcolor=<%=bcMsgBdy%> text="#000000" link="#000000" vlink=#"000000">
<center>
<% If isAttachSupported() Then %>
<FORM  NAME='mainForm' ACTION='<%=bstrVirtRoot%>/exupload.dll' ENCTYPE='multipart/form-data' METHOD='POST' onSubmit='parent.AttachFile(document.mainForm);return(false);'>
<br>
<center>
<TABLE border=0 cellpadding=0 cellspacing=0 width=90%>
<tr><td colspan=2 align="left" width="100%"><%=L_AttachInstruct_Text%></td></tr>
<TR><td colspan=2 width="100%" height=10>&nbsp;</td></tr>	
<tr><TD align="left"><INPUT TYPE=FILE NAME=ffname SIZE=<%=iFileInputWidth%>></TD></TR>
<TR><td colspan=2 width="100%" height=10>&nbsp;</td></tr>
<tr><TD colspan=2 width="100%" align="center"><INPUT TYPE=submit VALUE='<%=L_AddAttachmentsNow_Text%>'></TD></TR>
</TABLE></center>
<%Else%>
<b><center><%=L_strAttachmentsNotSupported_Message%></center></b><br>
<% End If %>
<br>
<center><TABLE bordercolor=#000000 border=1 cellpadding=0 cellspacing=0 width=90%>
   <TR bgcolor="#a0a0a0">
   <td align="center" valign="middle" width=10%>
   <a href='javascript:DeleteMarkedFiles();'>
      <img src="<%=bstrVirtRoot%>/forms/Delete.GIF" border=0 width=16 height=16 alt="<%=L_DeleteMarkedForms_Text%>"></a>
   </td>
   <td align="center" valign="middle"><Font size=2 color="#ffffff"><nobr><B><%=L_FileName_Text%></B></nobr></font></td>
   <td align="center" valign="middle"><Font size=2 color="#ffffff"><nobr><b><%=L_Size_Text%></b></nobr></font></td></tr>

<% If fHasAttach then
    For i = 1 to objAttachColl.Count
        Set objAttach = objAttachColl.Item(i)
        bstrName = objAttach.Name
        If bstrName = "" then
            bstrName = objAttach.Fields.Item(ActMsgPR_DISPLAY_NAME)
        End If
        If bstrName = "" then
            bstrName = L_UntitledAttach_Text
        End If
        lAttachSize = objAttach.Fields.Item(ActMsgPR_ATTACH_SIZE)
        If  lAttachSize < 1024 then
          bstrSize = "1" + L_Kilobytes_Text
        Else
          bstrSize = cstr(lAttachSize\1024) + L_Kilobytes_Text
        End If
%>
  <TR bgcolor="#FFFFFF"><TD align=center>    
	<input type="checkbox" name="_<%=bstrName%>" value="<%=i%>">
	</td><td align="left" bgcolor="#FFFFFF">
  <A HREF="<%=bstrVirtroot%>/Attach/read.asp?obj=<%=bstrObj%>&att=<%=objAttach.Fields.Item(ActMsgPR_RECORD_KEY)%>" TARGET="_blank" TITLE="<%=bstrName%>"><%=bstrName%></a>
	</TD><TD align="Left"><%=bstrSize%></td></TR>
<%  
      
   Next
  End If
%>

</TABLE></center>

<!-- **** INTERNAL STUFF **** -->
<input type="hidden" name="tab" value="nobind">
<input type="hidden" name="command" value="post">
<input type="hidden" name="objID"   value="<%=bstrObj%>">
<INPUT TYPE='Hidden' Name=obj Value=<%=bstrObj%>>
<INPUT TYPE='Hidden' Name=RedirectURL value="<%=bstrVirtRoot%>/Forms/IPM/Post/EnhancedLitCrit/Stock_Attachments.asp">

</FORM></center></Body></HTML>
