<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<% SendHeader 0, 1 %>
<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN">
<% 
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- PostTitl.asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->

On Error Resume Next
urlTab       = Request.QueryString("tab")
urlAtt       = Request.QueryString("att")
urlImportance= Request.QueryString("imp")
bstrObj      = Request.QueryString("obj")
bstrFormMode = Request.QueryString("fmode")
bCanPost     = cBool(Request.QueryString("canpost"))
bCanDelete   = cBool(Request.QueryString("candelete"))
bstrFolderID  = Request.QueryString("folderID")

CurForm      = cint(urlTab)
if urlAtt = "" then urlAtt = "0"
bgcolor="c0c0c0"

Dim bstrMainTabTitle(7)

iTotalTabs = 0

'=== LITCRIT FORM doesn't accept attachments, nor does it need tabs
'iTotalTabs = iTotalTabs + 1
'bstrMainTabTitle(iTotalTabs) = "Message"    '--- WAS: Others
'iTotalTabs = iTotalTabs + 1
'bstrMainTabTitle(iTotalTabs) = "Attachments"

For iCurTab = 1 to iTotalTabs
  If bstrMainTabTitle(iCurTab) = "Message" Then
    bstrMainTabTitle(iCurTab) = L_Message_Text
  End If
  If bstrMainTabTitle(iCurTab) = "Attachments" Then
    bstrMainTabTitle(iCurTab) = L_Attachments_Text
  End If
Next

fCompose = (bstrFormMode = "compose")

bAuthenticated = Session(bstrAuthenticated)

urlTab = CInt(urlTab)

iVisibleTabs = 4
If iVisibleTabs > iTotalTabs Then
  iVisibleTabs = iTotalTabs
End If

iTabWidth = 122
iOtherWidth = 96 + ((4 - iVisibleTabs) * (iTabWidth + 10))

For j = 1 to iTotalTabs Step iVisibleTabs 
  If CInt(urlTab) < j + iVisibleTabs Then
    iStartTab = j
    Exit For
  End If
Next
%>
<HTML>
<!--#include file="../../../../lib/jsutil.inc"-->
<SCRIPT language='javascript'>

function tabToForm(iForm) {
  if (parent.fBusyTabbing==false) {
    parent.fBusyTabbing = true;
    parent.iNextForm=iForm;
    if (parent.iCurForm!=2) parent.DoCommand("bind",parent.form_fr.document.mainForm);
    else parent.gotoForm(iForm);
  }
}

function setImportanceRemote(varVal) { //used from other frames
    fErr=false;  
    if (typeof(varVal)=="number"){
        parent.iImportance=varVal;
    }
    else {
        varVal = varVal.toLowerCase();
        if (varVal=="normal" || varVal=="1") parent.iImportance=1;
        else if (varVal=="high" || varVal=="hi" || varVal=="2") parent.iImportance=2;
        else if (varVal=="low" || varVal=="lo" || varVal=="0") parent.iImportance=0;
        else fErr=true;
    }
    if (fErr==false) {
        self.location="PostTitl.asp?tab=<%=urlTab%>&att=<%=urlAtt%>&imp=" + parent.iImportance + "&obj=<%=bstrObj%>&fmode=<%=bstrFormMode%>&canpost=<%=bCanPost%>&candelete=<%=bCanDelete%>";
    }
    else alert("Error\nInvalid entry for importance.");
}


function setImportance(iVal) {
   var curVal=parent.iImportance;
   if (iVal==2) curVal=(curVal==2 ? 1 : 2);
   else curVal=(curVal==0 ? 1 : 0);
   parent.iImportance=curVal;
   self.location="PostTitl.asp?tab=<%=urlTab%>&att=<%=urlAtt%>&imp=" + curVal + "&obj=<%=bstrObj%>&fmode=<%=bstrFormMode%>&canpost=<%=bCanPost%>&candelete=<%=bCanDelete%>";
}

</script>
<STYLE TYPE="text/css">
<!--
A:link 	{ color: black;
          text-decoration: none }
A:visited 	{ color: black;
              text-decoration: none }
A:active 	{ color: black;
            text-decoration: none }
-->
</STYLE>
<body topmargin=4 leftmargin=4 bgcolor='c0c0c0' link=black vlink=black alink=black>
<FORM name="toolbar">
<!--    Send note fields -->
<table width=100% bgcolor="<%=bgcolor%>" border=0 cellpadding=2 cellspacing=0>
<tr><td>

<% If fCompose Then %>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<A href="javascript:parent.parent.parent.DoCommand('post', parent.form_fr.document.mainForm)">  
<IMG SRC="<%=bstrVirtRoot%>/forms/post.gif" align="middle" Alt='<%=L_Post_ToolTip%>' border=0 height=24 width=24></a>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<A href='javascript:setImportance(2);'>
<% if urlImportance="2" Then %>
<IMG SRC="<%=bstrVirtRoot%>/forms/highdown.gif" alt='<%=L_Importance_StaticText & " " & L_High_Text%>' align="middle" border=0 height=20 width=20></a>	
<% else %>
<IMG SRC="<%=bstrVirtRoot%>/forms/high.gif" alt='<%=L_Importance_StaticText & " " & L_High_Text%>' align="middle" border=0 height=20 width=20></a>	
<% end if %>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<A href='javascript:setImportance(0);'>
<% if urlImportance="0" Then %>
<IMG SRC="<%=bstrVirtRoot%>/forms/LOWDOWN.gif" alt='<%=L_Importance_StaticText & " " & L_Low_Text%>' align="middle" border=0 height=20 width=20></a>	
<% else %>
<IMG SRC="<%=bstrVirtRoot%>/forms/low.gif" alt='<%=L_Importance_StaticText & " " & L_Low_Text%>' align="middle" border=0 height=20 width=20></a>	
<% end if %>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<A href='<%=bstrVirtRoot%>/help/NEWPOST.HTM' target='inlineHelpWindow'>
<IMG SRC="<%=bstrVirtRoot%>/images/help.gif" alt='<%=L_Help_ToolTip%>' align="middle" border=0 height=20 width=20></a>	
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
</td>
<% Else 'in read mode
    'validate underlying message structure
    err.clear
    Set objMessages = Session(CURRENT_CONTENTS) 
    If objMessages Is Nothing Or Err.Number <> 0 Then 
        fHaveContent = False 'no next/prev
    Else 
        fHaveContent = True
    End If %>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<%   If bCanPost Then %>
<A href='JavaScript:parent.DoCommand("save", parent.form_fr.document.mainForm)'>  
<IMG SRC="<%=bstrVirtRoot%>/forms/save.gif"  align="middle" Alt="<%=L_Save_ToolTip%>" border=0 height=24 width=24></a>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<%   End If%>
<%

dim rgGifNames(3)
rgGifNames(3) = "ReplyFld.gif"
rgGifNames(1) = "Reply.gif"
rgGifNames(2) = "forward.gif"
%>

<%If bAuthenticated Then 'Anon cannot create sendable responses %>
<A href="JavaScript:parent.DoCommand('1', parent.form_fr.document.mainForm)">  
<IMG SRC="<%=bstrVirtRoot%>/forms/<%=rgGifNames(1)%>" Alt="Reply" align="middle" border=0></a>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<%End If %>
<%If bAuthenticated Then %>
<a href="JavaScript:openNewWindow('<%=bstrVirtRoot%>/movcpy/root.asp?msgid=<%=bstrObj%>&folderid=<%=bstrFolderID%>&process=1','newMessageWindow',400,400)">
<IMG SRC="<%=bstrVirtRoot%>/forms/movcpy.gif" alt='<%=L_MoveCopy_ToolTip%>' align="middle" border=0 height=24 width=24></a>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<%End If%>
<%   If bCanDelete Then %>
<A HREF="javascript:parent.DoCommand('delete', parent.form_fr.document.mainForm)">
<IMG SRC="<%=bstrVirtRoot%>/forms/delmark.gif" alt="<%=L_Delete_ToolTip%>" WIDTH=24 HEIGHT=24 align="middle" BORDER=0></a>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<%End If %>
<%   If fHaveContent Then%>
<A href="javascript:parent.DoCommand('previous', parent.form_fr.document.mainForm)"> 
<IMG SRC="<%=bstrVirtRoot%>/forms/prevmsg.gif" Alt="<%=L_PrevMsg_ToolTip%>" align="middle" border=0 width=24 height=24></a>
<A href="javascript:parent.DoCommand('next', parent.form_fr.document.mainForm)">  
<IMG SRC="<%=bstrVirtRoot%>/forms/nextmsg.gif" Alt='<%=L_NextMsg_ToolTip%>' align="middle" border=0 width=24 height=24></a>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<A href='JavaScript:setImportance(2);'>
<% if urlImportance="2" Then %>
<IMG SRC="<%=bstrVirtRoot%>/forms/highdown.gif" alt='<%=L_Importance_StaticText & " " & L_High_Text%>' align="middle" border=0 height=20 width=20></a>	
<% else %>
<IMG SRC="<%=bstrVirtRoot%>/forms/high.gif" alt='<%=L_Importance_StaticText & " " & L_High_Text%>' align="middle" border=0 height=20 width=20></a>	
<% end if %>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<A href='JavaScript:setImportance(0);'>
<% if urlImportance="0" Then %>
<IMG SRC="<%=bstrVirtRoot%>/forms/LOWDOWN.gif" alt='<%=L_Importance_StaticText & " " & L_Low_Text%>' align="middle" border=0 height=20 width=20></a>	
<% else %>
<IMG SRC="<%=bstrVirtRoot%>/forms/low.gif" alt='<%=L_Importance_StaticText & " " & L_Low_Text%>' align="middle" border=0 height=20 width=20></a>	
<% end if %>
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
<%   End If%>
<A href="javascript:openNewWindow('<%=bstrVirtRoot%>/help/postedms.htm','inlineHelpWindow',600,400)">
<IMG SRC="<%=bstrVirtRoot%>/images/help.gif" alt='<%=L_Help_ToolTip%>' border=0 height=20 width=20 align="middle"></a>			
<img src="<%=bstrVirtRoot%>/images/divider.gif" width=4 height=24 align="middle">
</td>
<% End If %>

<td align=right valign=bottom>
<input type=button value="<%=L_Close_Text%>" onClick="parent.parent.DoCommand('cancel', parent.form_fr.document.MainForm)">
</td></tr>
<tr>
<%If fCompose = False Then %>
<!--Response List-->
<td>
    
   

    
   

    
   


</td>
</td></tr>
<%End If%>
</table>

<!--Tabs table-->
<table border=0 cellpadding=0 cellspacing=0 width=640>
<tr>
<!-- Top of tabs -->
<% For i = iStartTab to iStartTab + iVisibleTabs-1 %>
  <% If i <= iTotalTabs Then %>
    <td valign=top width=5 height=5><img src=<%=bstrVirtRoot%>/forms/tablcor.gif width=5 height=5></td>
    <td valign=top width=<%=iTabWidth%>><img src=<%=bstrVirtRoot%>/forms/tabWdot.gif width=<%=iTabWidth%> height=2></td>
    <td valign=top width=5><img src=<%=bstrVirtRoot%>/forms/tabrcor.gif width=5 height=5></td>
  <% Else %>
    <td width=5 height=5></td>
    <td width=<%=iTabWidth%>></td>
    <td width=5></td>
  <% End If %>
<% Next %>

<!-- Place holders for left and right gif's -->
<td align=right width=<%=iOtherWidth%>></td>
<td width=16></td>

</tr>
<tr>

<!--middle text row-->
<% For i = iStartTab To iStartTab + iVisibleTabs-1 %>
  <% If i <= iTotalTabs Then %>
    <td><img src=<%=bstrVirtRoot%>/forms/tabWdot.gif width=2 height='22'></td>
    <td align=center valign=top>
      <% If urlTab <> i Then %><a href=javascript:tabToForm(<%=i%>)><% End If %>
      <font size=2><%=bstrMainTabTitle(i)%></font>
      <% If urlTab <> i Then %></a><% End If %>
      <%if urlAtt="1" and i = 2 Then %>
	    &nbsp;<IMG SRC=<%=bstrVirtRoot%>/images/papclip.gif border=0 height=16 width=10>
      <%end if%>
    </td>
    <td align=right><img src=<%=bstrVirtRoot%>/forms/tabrline.gif width=2 height='22'></td>
  <% Else %>
    <td></td><td></td><td></td>
  <% End If %>
<% Next %>
<td align=right>
  <% If urlTab > iVisibleTabs Then
     ' LITCRIT: LAST.GIF doesn't exist. Let's ignore this line... %>
     <!-- <a href=javascript:tabToForm(<%=iStartTab-iVisibleTabs%>)><img src=<%=bstrVirtRoot%>/forms/last.gif width=16 height=15 BORDER=0></a> -->
  <% End If %>
</td>
<td align=left>
  <% If iStartTab + iVisibleTabs <= iTotalTabs Then 
     ' LITCRIT: Not sure what they mean here. NEXT.GIF doesn't exist either... %>
     <!-- <a href=javascript:tabToForm(<%=iStartTab+iVisibleTabs%>)><img src=<%=bstrVirtRoot%>/forms/next.gif width=16 height=15 BORDER=0></a> -->
  <% End If %>
</td>

</tr>
<tr>

<!-- bottom tab lines (no line under current tab) -->
<% For i = iStartTab To iStartTab + iVisibleTabs-1 %>
<td height=2 colspan=3 valign=top><% If urlTab<>i Then %><img src=<%=bstrVirtRoot%>/forms/tabWdot.gif width=<%=iTabWidth+10%> height=2><% End If %></td>
<% Next %>

<td height=2 colspan=2 valign=top><img src=<%=bstrVirtRoot%>/forms/tabWdot.gif width=<%=iOtherWidth + 16%> height=2></td>

</tr>
</table>
</Form>
</body>
</html>


