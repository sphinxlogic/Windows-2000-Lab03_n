<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<% SendHeader 1, 1 %>
<!--#include file="../../../../lib/store.inc"-->
<!--#include file="../../../../lib/render.inc"-->
<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN">

<% 
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- Stock_Message-Read.asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
    
On Error Resume Next
bstrObj = Request.QueryString("obj")

CheckSession2 bstrVirtRoot + "/forms/IPM/Post/EnhancedLitCrit/frmRoot.asp?obj="+bstrObj

fHasAttach=false
bAuthenticated = Session(bstrAuthenticated)

If bstrObj <> "" then  'open msg and get data
    Set objOneMsg = Session(bstrObj)
    Set objRenderer = GetMessageRenderer
    objRenderer.DataSource = objOneMsg
    bstrFolderID = objOneMsg.FolderID
    Set objFolder = OpenFolder(bstrFolderID)

    AddrType = objOneMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_ADDRTYPE)
    Address  = objOneMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS)
    bstrSentRepresentingName = objOneMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_NAME)
    If AddrType <> "" And AddrType <> "EX" And Address <> "" Then 
      AddrType = "[" + AddrType
      Address = ":" + Address + "]"
      bstrSentRepresentingName = bstrSentRepresentingName + AddrType + Address
    End If     

   fHasAttach = objOneMsg.Fields.Item(ActMsgPR_HASATTACH)

   bstrConvTopic = objOneMsg.ConversationTopic
   bstrSubject   = objOneMsg.Subject
   bstrMsgText   = objOneMsg.Text
Else
   Set objFolder  = Session(CURRENT_FOLDER)
   bstrConvTopic  = ""
   bstrSubject    = ""
   bstrMsgText    = ""
End If
bstrFolderName = objFolder.Name

'Table(pixels) to field width adjustments
nTWfactor = Session("nTWfactor")
nTAfactor = Session("nTAfactor")
nRows = Session("nTARows") - 3

'localized textbox width adjustments
L_PostTileColumnWidthAdjUnix_Number = 0         ' adjust title column for UNIX
L_PostTileColumnWidthAdjMac_Number = 0          ' adjust title column for Mac
L_PostTileColumnWidthAdjustmentWin16_Number = 0 ' adjust title column for Win16 (i.e. Win3.1)
L_PostTileColumnWidthAdjustmentWin32_Number = 0 ' adjust title column for Win32 (i.e. Win95 and NT) - default

L_PostMsgBodyWidthAdjUnix_Number = 0            ' adjust message body for Unix
L_PostMsgBodyWidthAdjMac_Number = 0             ' adjust message body for Mac
L_PostMsgBodyWidthAdjustmentWin16_Number = 0    ' adjust message body for Win16 (i.e. Win3.1)
L_PostMsgBodyWidthAdjustmentWin32_Number = 0    ' adjust message body for Win32 (i.e. Win95 and NT) - default

If isUNIX Then
    titleColumnWidthAdj = L_PostTileColumnWidthAdjUnix_Number
    msgBodyWidthAdj = L_PostMsgBodyWidthAdjUnix_Number
ElseIf isMac Then
    titleColumnWidthAdj = L_PostTileColumnWidthAdjMac_Number
    msgBodyWidthAdj = L_PostMsgBodyWidthAdjMac_Number
ElseIf isWin16 Then
    titleColumnWidthAdj = L_PostTileColumnWidthAdjustmentWin16_Number
    msgBodyWidthAdj = L_PostMsgBodyWidthAdjustmentWin16_Number
Else
    titleColumnWidthAdj = L_PostTileColumnWidthAdjustmentWin32_Number
    msgBodyWidthAdj = L_PostMsgBodyWidthAdjustmentWin32_Number
End If

iTablePixWidth = 625 + msgBodyWidthAdj
iCol1PixWidth = 100 + titleColumnWidthAdj
iCol2PixWidth = iTablePixWidth-iCol1PixWidth

iCol2InputWidth = cint((iCol2PixWidth * (nTWfactor)) + ((iCol2PixWidth-1000)\1000))
iTableTAWidth = cint((iTablePixWidth * nTAfactor) + ((iTablePixWidth-1000)\140))  
Set objRenderer = GetObjectRenderer
objRenderer.DataSource = objOneMsg
%>
<HTML>
<body onLoad="parent.fBusyTabbing = false;" leftmargin=4 bgcolor="c0c0c0" text=000000 link=000000 vlink=000000 alink=000000>
<FORM name="mainForm" ACTION="commands.asp" METHOD="POST" target="command_fr" onSubmit="return(false)">
<table bgcolor=c0c0c0 border=0 cellpadding=4 cellspacing=0 width="<%=iTablePixWidth%>">
<TR>
		<TD width=10%>
			<font size=2><%=L_HeaderPostedBy_Text%></font>
		</TD>		
		<TD id=from width=30%>
			<font size=2>
			<%
            'Compare sender and sent representing properties to check for 'send on behalf of' situations
            Rep=objOneMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_SEARCH_KEY)
            Sender=objOneMsg.Fields.Item(ActMsgPR_SENDER_SEARCH_KEY)

            'Localizable strings for send on behalf of case
            '(PreFromText)Sender(MidFromText)Representing(PostFromText)

            L_PreFrom_Text=""
            L_PostFrom_Text=""

            If Rep<>Sender Then%>

	            <%=L_PreFrom_Text%>
	            <%objRenderer.RenderProperty ActMsgPR_SENDER_NAME,0,Response%>&nbsp;
	            <%=L_OnBehalfOf_Text%>&nbsp;&nbsp;
            <%
            End If

            AddrType = objOneMsg.Fields(ActMsgPR_SENT_REPRESENTING_ADDRTYPE)
            Address  = objOneMsg.Fields(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS)
            objRenderer.RenderProperty ActMsgPR_SENT_REPRESENTING_NAME, 0, Response %>
            <% If AddrType <> "" And AddrType <> "EX" And Address <> "" Then %>
                [<% objRenderer.RenderProperty ActMsgPR_SENT_REPRESENTING_ADDRTYPE, 0, Response %>:<% objRenderMsg.RenderProperty ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS, 0, Response %>]
            <% End If %>
            &nbsp;
            <%=L_PostFrom_Text%>
			</font>
		</TD></TR>
	<TR>
        <TD>
        <font size=2><nobr><%=L_HeaderPostedAt_Text%></nobr></font>
		</TD>
	    <TD><font size=2><nobr>
			<% objRenderer.RenderProperty ActMsgPR_CLIENT_SUBMIT_TIME, 0, Response %>&nbsp;</nobr></font><br>
		</TD>
    
    </TR>
<tr><td width="<%=iCol1PixWidth%>">
<font  size="2"><nobr><%=L_HeaderPostedTo_Text%></nobr></font></td>
<td><font size=2><% objRenderer.Write bstrFolderName, Response %></font></td></tr><tr><td>
<font size=2><nobr><%=L_HeaderConversation_Text%></nobr></font></td>
<!-- UniqueID=conversation Property=&H0070001f PropertyType=8 PropertyFormat=0 -->
<td><font size=2><% objRenderer.Write bstrConvTopic, Response %></font></td></tr>
<tr bgcolor=c0c0c0><td>
<font size=2><nobr><%=L_HeaderKeywords_Text%></nobr></font></td>

<td><font size=<%=iFontSize%>>
<% if fNew Then %>
<INPUT TYPE=TEXT NAME='keywords' size=<%=iCol2InputWidth%>>
<% else %>
<INPUT TYPE=TEXT NAME='keywords' size=<%=iCol2InputWidth%> VALUE="<% objRenderer.RenderProperty "Keywords", 0, Response %>">
<% end if %>
</font>
</td>
</tr>

<tr bgcolor=c0c0c0>

<td>
<font  size="2"><nobr><%=L_HeaderSubject_Text%></nobr></font>
</td>

<td><font size=<%=iFontSize%>>
<!-- UniqueID=subject Property=&H0037001f PropertyType=8 PropertyFormat=0 -->
<INPUT TYPE=TEXT NAME='subject' maxlength=255 size=<%=iCol2InputWidth%> value="<% objRenderer.Write bstrSubject, Response %>">
</font>
</td>
</tr>

<tr bgcolor="c0c0c0"></tr>

</table>

<table bgcolor=c0c0c0 border=0 cellpadding=4 cellspacing=0 width=<%=iTablePixWidth%>>

<tr>
<td width=100%>
<!-- Textarea html on single line avoids cr/lf in textarea -->
<!-- UniqueID=message Property=&H1000001f PropertyType=8 PropertyFormat=0 -->
<TEXTAREA cols="<%=iTableTAWidth%>" rows="<%=nRows%>" name=message wrap=virtual><% objRenderer.Write GetPlainBodyText(objOneMsg), Response %></TEXTAREA>

</td>
</tr>
</table>

<!-- **** COMMON FIELDS SUBMITTED ON ALL FORMS **** -->
<input type="hidden" name="tab" value="message">
<input type="hidden" name="command" value="post">
<input type="hidden" name="objID"   value="<%=bstrObj%>">
<input type="hidden" name="replytofolder" value="0">
<input type="hidden" name="importance" value="1">

</form>
<%
' Set msg state to "read" only for Authenticated users
' Do this at the end for better server performance.

If bAuthenticated Then
    objOneMsg.Unread = False
    objOneMsg.Update()
End If
%>

</BODY>
</HTML>
