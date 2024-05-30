<%@ Language=VBScript Transaction=Required %>
<% 'Copyright Microsoft 1998-1999.  All rights reserved. %>
<% Option Explicit %>
<% Response.Buffer = True
   Response.Expires = 0 %>

<script LANGUAGE=VBScript RUNAT=Server>
Private Function RowColor(nRow)
   If nRow Mod 2 Then
       RowColor="#AFCFFF"
   Else
      RowColor="#FFFFFF"
   End If
End Function
Private Sub ReportWarning(strMsg)
   Response.Write "<" & "script LANGUAGE=VBScript>" & vbCrLf & _
                  "MsgBox """ & strMsg & """" & vbCrLf & _
                  "</" & "script>"
End Sub
</script>

<HTML>
<HEAD>
<Title>Renew Materials </Title>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<link rel="stylesheet" href="../_Themes/fm/theme.css">
</HEAD>

<BODY>
<!-- #include file="AdNMat/Verify.asp" -->
<!--#include file="navigation.asp"-->

<img CLASS="logo"     SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img CLASS= "sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">

<div class=menui>
<TABLE border=0 class="watermark" height=250 width=200 CELLSPACING=0 CELLPADDING=0>
<TR vAlign=top><TD>
   <TABLE class=admin WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
   <TR>
      <TD BGCOLOR=#ce6300 valign=top ALIGN=center NOWRAP id=mI>Administration</TD>
   </TR>
   </TABLE></TD>
</TR>
</TABLE>
</div>

<script LANGUAGE=VBScript>
Sub RenewItems()
   Dim theForm,i,bSelected
   If FormSubmitOK Then
      Set theForm = document.frmRenew
      
      ' Code varies if one item or multiple items are displayed
      If VarType(theForm.Renew) = vbString Then
         bSelected = theForm.Renew.Checked
      Else
         bSelected = False
         For i = 0 To theForm.Renew.Length-1
            If theForm.Renew(i).Checked Then
               bSelected = True
               Exit For
            End If
         Next
      End If
      
      If bSelected Then
         If IsValidDate(theForm.RenewDate.Value) Then
            If CDate(theForm.RenewDate.Value) > DateAdd("d",1,Date) Then
               theForm.Action.Value = "Renew"
               theForm.Submit
            Else
               MsgBox "You should enter a date in the future."
               theForm.RenewDate.Focus
            End If
         Else
            MsgBox "You have not entered a valid date."
            theForm.RenewDate.Focus
         End If
      Else
         MsgBox "You must select at least one item to renew."
      End If
   End If
End Sub
</script>

<script LANGUAGE=VBScript>
Function FormSubmitOK()
   Dim theForm
   Set theForm = document.frmRenew
   
   '--- Submit by default
   FormSubmitOK = True
   
   If Trim(theForm.alias.Value) = "" Then
      MsgBox "Please enter a user alias."
      theForm.alias.Focus
      FormSubmitOK = False
   End If
End Function
</script>

<form NAME=frmRenew ACTION="<%= Request.ServerVariables("SCRIPT_NAME") %>" METHOD=POST
      onSubmit="javascript:return FormSubmitOK()">
      
<INPUT TYPE=Hidden NAME=Action VALUE="Lookup">

<% Dim objUser,objAdmin,UserAlias,nborrowerNo,rs,nRowCount
   Dim item,strDueDate,nRet
   
   If (UCASE(Request.ServerVariables("HTTP_METHOD"))="POST") Then
%>
<div ID=RenewDate style="position:absolute;top:120;left:295;z-index:500">
<table>
<tr ALIGN=CENTER>
   <td>&nbsp;Renew Date:&nbsp;
   <input name="RenewDate" VALUE="<%= DateAdd("d",Application("CheckoutPeriod"),Date) %>">
   </td>
</tr>
<tr>
   <td><input type="Button" value="Renew Selected Materials" onClick="RenewItems()"></td>
</tr>
</table>
</div>

<div style="position:absolute;top:200;left:285;z-index:500">
<%
      If Request.Form("Action") = "Renew" Then
         strDueDate = Request.Form("RenewDate")
         Set objAdmin = Server.CreateObject("CML.Admin")
         If IsObject(objAdmin) Then
            objAdmin.ConnectionString = Application("FmLib_ConnectionString") 
            For Each item In Request.Form("Renew")
               nRet = objAdmin.Renew(item, CDate(strDueDate))
               If nRet = 0 Then ReportWarning "Failed to renew this item: " & item & ". Check to see if there are outstanding requests for this item."
            Next
            Set objAdmin = Nothing
         Else
             Response.Write "Unable to instantiate CML.Admin object. No renewals could be performed.<br>"
         End If
      End If
      
      Set objUser = Server.CreateObject("CML.User")
      If IsObject(objUser) Then
         objUser.ConnectionString = Application("FmLib_ConnectionString")
    
         UserAlias = Request.Form("alias")
         nborrowerNo = objUser.GetInfoFromTable(UserAlias)     
         If nborrowerNo > 0 then
            'Retrieves recordset of already checkouts for particular borrowerNo
            Set rs = objUser.CheckOuts(nborrowerNo)
     
            If Not rs.EOF Then
               nRowCount = 0
%>
<table COLS=5 BORDER=0 CELLSPACING=4 CELLPADDING=0>
<tr><th ALIGN=left></th><th ALIGN=Left>Title</th><th ALIGN=Left>Checkout Date</th><th ALIGN=Left>Due Date</th></tr>
<%             Do Until rs.EOF
                  nRowCount = nRowCount + 1
%>
<tr BGCOLOR="<%= RowColor(nRowCount) %>" VALIGN=Top>
<td BGCOLOR=#FFFFFF><input type="checkbox" NAME="Renew" ID="cb<%= nRowcount%>" value="<%=rs("Barcode")%>"></td>
<td><%= rs("Title") %> <font SIZE=-2>(<%= rs("Barcode") %>)</font></td>
<td><%= rs("Checkout Date") %></td>
<td><%= rs("Due Date") %></td>
</tr>
<%   
                  rs.MoveNext
               Loop
%>         
</table><br><font SIZE=-2>Items shown: <%= nRowCount %></font>
<%          Else %>
   <i>No checkouts appear for user: <strong><%= UserAlias %></strong>.</i>
<%          End If

            rs.Close
            Set rs = Nothing
         Else
%>         
   <i>No checkouts appear for user: <strong><%= UserAlias %></strong>.</i>
<%   
         End If
         Set objUser = Nothing
      Else
          Response.Write "Unable to instantiate CML.User object. Can't determine what materials have been checked out.<br>"
      End If 
%>      
</div>
<% End If   ' END OF POST %>

<DIV ID="RenewAlias" STYLE="POSITION: absolute; LEFT: 20px; TOP: 120px; WIDTH: 95%; Z-INDEX:101">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Renew Materials</span>

  <br><br><br><br><br>
  <font SIZE=-2>Enter <strong>Alias</strong> for user with items to renew.</font>
  <br>
  <TABLE COLS=2 WIDTH=15% COLSPAN=2 BORDER=0 CELLSPACING=0 CELLPADDING=1>
  <tr>
      <td>&nbspAlias:&nbsp;</td>
      <td><input name="alias" SIZE=20 value="<%= UserAlias %>"></td>
  </tr>
  <tr>
      <td>&nbsp;</td>
      <td><input type="Submit" value="Submit"></td>
  </tr>
  </Table>
</DIV>

</FORM>

<script Language= vbscript>
Sub window_onload()
   document.frmRenew.alias.focus
End Sub
</script>

</body>
</Html>



      
      