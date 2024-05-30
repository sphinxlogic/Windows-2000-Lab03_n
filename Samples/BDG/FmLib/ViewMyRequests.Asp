<%@ Language=VBScript Transaction=Required %>
<% Option Explicit %>
<% Response.Buffer = True
   Response.Expires = 0
%>
<script LANGUAGE=VBScript RUNAT=Server>
Private Function RowColor(nRow)
   If nRow Mod 2 Then
      RowColor="#AFCFFF"
   Else
      RowColor="#FFFFFF"
   End If
End Function
</script>
<% Dim strLogon
   '--- Check for valid logon, and detect it if missing
   strLogon = Request("Logon")
   If IsEmpty(strLogon) Or strLogon="" Then
   
      '=== The following frameset wraps the page being requested with a dynamic
      '=== redirection that includes the user's logon.  Doing it in this fashion
      '=== (rather than using 'document.location.href') produces a more natural
      '=== response if the user presses the 'Back' button.
%>
<html>
<head>
<TITLE>View My Requests and Checkouts</TITLE>
<object id="UserInfo" 
        classid="CLSID:81163377-6EC1-11D2-9BF0-080009DC024D"
        codebase="CMLC.CAB#version=1,0,0,0" 
        height="0" width="0" VIEWASTEXT>
</object>
<script LANGUAGE="JavaScript">
function Redirect() {
   document.all.innerFrame.src = '<%= Request.ServerVariables("SCRIPT_NAME") %>?Logon=' + UserInfo.Logon;
}
</script>
</head>
<frameset COLS="*" BORDER=0 FRAMEBORDER=0 FRAMESPACING=0 onLoad="Redirect()">
<frame id=innerFrame WIDTH=100% HEIGHT=100% SCROLLING=none FRAMEBORDER=0>
<noframes>I'm sorry. This page requires frames, and your browser doesn't support them.</noframes>
</frameset>
</html>
<% Response.End
   End If
%>
<HTML>
<HEAD>
<TITLE>View My Requests and Checkouts</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>

<!--#include file="common.asp"-->
<div CLASS=CuserMenu >
<table CLASS=Cuser COLSPAN=2 CELLSPACING=0 CELLPADDING=5>
<tr>
<td><span onclick="javascript:GoHomePage()"  TITLE="Go to home page">Home</span></td>
<td><span onclick="javascript:GoRequestPage()"  TITLE="Go to search library" >Search&ndash;Library</span></td>
</tr>
</table>
</div>


<script language=JavaScript>
function GoHomePage(){
   top.location.href="default.asp";
}
function GoRequestPage(){
   top.location.href="librarysearch/library.asp";
}
</script>

<% Dim oUser,nBorrowerNo,rs,nRowCount

   Set oUser = Server.CreateObject("CML.User")
   oUser.ConnectionString = Application("FmLib_ConnectionString")
   nBorrowerNo = oUser.GetInfoFromTable(strLogon)
%>
<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 130px; WIDTH: 95%; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Materials Requested</span>
<%
   If nBorrowerNo > 0 Then

      '--- Handle request cancellations here
      If Request.QueryString("Action") = "Cancel" Then
         Dim item
         For Each item In Request.Form("Cancel")
            '--- NOTE: MTS destroys this object each time through the loop,
            '--- because it calls ObjectContext.SetComplete internally
            oUser.CancelRequest item, nBorrowerNo
         Next
      End If
      
      Set rs = oUser.Requests(nBorrowerNo)
      If Not rs.EOF Then
         nRowCount = 0
%>
   <script LANGUAGE=JavaScript>
   function ConfirmCancel() {
      var coll = document.frmCancel.tags('INPUT');
      if (coll!=null) {
         for (var i=0; i<coll.length; i++) {
           	if (coll[i].type == 'checkbox' && coll[i].checked) {
               return confirm('This operation will cancel the requests for the materials\nyou have marked. OK to continue?');
            }
         }
      }
      alert('You should select at least one title to cancel.');
      return false;
   }
   </script>

   <form NAME=frmCancel ACTION="<%= Request.ServerVariables("SCRIPT_NAME") %>?Action=Cancel"
         METHOD=Post onSubmit="return ConfirmCancel()">
   <input NAME=Logon TYPE=Hidden VALUE="<%= strLogon %>">
   <table BORDER=0 CELLSPACING=4 CELLPADDING=0 WIDTH="100%">
   <tr><th>&nbsp;</th><th ALIGN=Left>Title</th><th ALIGN=Left>Position</th><th ALIGN=Left>Date Requested</th></tr>
<%   
         Dim nBibNo,nPos,nLength
         Do Until rs.EOF
            nRowCount = nRowCount + 1
            nBibNo = rs("bib#")
            nPos = oUser.Position(nBibNo,nLength,nBorrowerNo)
%>            
   <tr BGCOLOR="<%=RowColor(nRowCount) %>" VALIGN=Top>
   <td><input NAME=Cancel TYPE=Checkbox ID=cb<%= nBibNo %> VALUE="<%= nBibNo %>"></td>
   <td><LABEL FOR=cb<%= nBibNo %>><%= rs("Title") %></label></td>
   <td><%= nPos & " of " & nLength %></td>
   <td><%= rs("Date Requested") %></td></tr>
<%   
            rs.MoveNext
         Loop
%>         
   </table><br><br>
   <input TYPE=Submit VALUE="Cancel Selected Requests">&nbsp;
   <input TYPE=Reset VALUE="Reset the Form">
   </form>
<%    Else %>
   <p><i>No requests appear for user: <strong><%= strLogon %></strong>.</i>
<%    End If
      rs.Close
%>
   <br><br>
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Materials Checked-Out</span>
<%
      Set rs = oUser.Checkouts(nBorrowerNo)
      If Not rs.EOF Then
         nRowCount = 0
%>      
   <table BORDER=0 CELLSPACING=4 CELLPADDING=0>
   <tr><th ALIGN=Left>Title</th><th ALIGN=Left>Checkout Date</th><th ALIGN=Left>Due Date</th></tr>
<%       Do Until rs.EOF
            nRowCount = nRowCount + 1
%>
   <tr BGCOLOR="<%= RowColor(nRowCount) %>" VALIGN=Top>
   <td><%= rs("Title") %> <font SIZE=-2>(<%= rs("Barcode") %>)</font></td>
   <td><%= rs("Checkout Date") %></td>
   <td><%= rs("Due Date") %></td></tr>
<%   
            rs.MoveNext
         Loop
%>         
   </table>
<%    Else %>
   <p><i>No checkouts appear for user: <strong><%= strLogon %></strong>.</i>
<%   
      End If
      rs.Close
      
      Set rs = Nothing
   Else
%>   
   <p><i>No checkouts or requests appear for user: <strong><%= strLogon %></strong>.</i>
<%
   End If
%>

</div>
</BODY>
</HTML>
