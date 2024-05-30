<%@ Language=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<% Dim rs,strItem,item

   If (UCase(Request.ServerVariables("HTTP_METHOD")) = "POST") Then
      Set rs = Server.CreateObject("ADODB.Recordset")
      rs.Open "Settings", Application("FmLib_ConnectionString"), adOpenForwardOnly, adLockOptimistic, adCmdTable
      
      ' Add new record if one doesn't already exist
      If rs.EOF Then
         rs.AddNew
      End If
      
      For Each item In Request.Form
         strItem = Trim(Request.Form(item))
         
         Select Case LCase(item)
         Case "exchangepass":
            ' Only update password if specified
            If strItem <> "" Then
               rs("ExchangePass") = strItem
               Application("ExchangePass") = strItem
            End If
         
         Case "debug":
            If (LCase(strItem) = "on") Then
               rs("Debug") = 1
               Application("Debug") = True
            Else
               rs("Debug") = 0
               Application("Debug") = False
            End If
            
         Case Else
            rs(item) = strItem
            Application(item) = strItem
            
         End Select
      Next
      
      rs.UpDate
      rs.Close 
      Set rs = Nothing
   End If      
%>
<HTML>
<HEAD>
<TITLE>Application Settings</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<link rel="stylesheet" href="../_Themes/fm/theme.css">
</HEAD>

<img CLASS="logo"    SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img CLASS="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">
<!-- #include file="Navigation.asp"-->

<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 110px; WIDTH: 95%; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Application Settings</span>
</div>

<div class=menui style="POSITION:absolute;left;20px;top:160px;">
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

<script LANGUAGE="VBScript">
Option Explicit

'--- Trap ENTER key and invoke SUBMIT function
Sub document_onkeypress()
	If Window.Event.keyCode = 13 Then
	   ChangeSettings()
	End If
End Sub

Sub ChangeSettings()
   Dim theForm,aFields,item,strMissing
   Set theForm = document.frmSettings
   
   ' Check for empty strings in required values
   aFields = Array("ExchangeServer","ExchangeSite","ExchangeOrg","CheckoutPeriod","RecallPeriod","DefaultLocation")
   For Each item In aFields
      If Trim(theForm.Elements(item).Value) = "" Then
         strMissing = strMissing & item & vbCrLf
      End If
   Next

   If strMissing = "" Then
      If Not IsNumeric(theForm.CheckoutPeriod.Value) Then
         MsgBox """Days before overdue"" is not a numeric value."
         theForm.CheckoutPeriod.Focus
      ElseIf Not IsNumeric(theForm.RecallPeriod.Value) Then
         MsgBox """Days between notices"" is not a numeric value."
         theForm.RecallPeriod.Focus
      Else
         theForm.Submit
      End If
   Else
      MsgBox "You are missing information from the following field(s):" & _
             vbCrLf & vbCrLf & strMissing & vbCrLf & "Please fill in these fields.",_
             vbCritical, "Missing Information"
      ' Focus on the first missing element in the form
      theForm.Elements(Left(strMissing,InStr(strMissing,vbCrLf)-1)).Focus
   End If
End Sub
</script>

<div id="App" style=position:absolute;left:100px;top:170px;z-index:300">
<form NAME="frmSettings" ACTION="<%= Request.ServerVariables("SCRIPT_NAME") %>" METHOD=POST>
<table width=60% COLS=2 BORDER=0 >
<tr><td COLSPAN=2><b>Exchange</b></td></tr>
<tr><td>Server:</td><td><input  type="text" name="ExchangeServer" value="<%= Application("ExchangeServer") %>" MAXLENGTH=128></td></tr>
<tr><td>Organization:</td><td><input  type="text" name="ExchangeOrg" value="<%= Application("ExchangeOrg") %>" MAXLENGTH=128></td></tr>
<tr><td>Site:</td><td><input  type="text" name="ExchangeSite" value="<%= Application("ExchangeSite") %>" MAXLENGTH=128></td></tr>
<tr><td>Admin Account (Optional):</td><td><input  type="text" name="ExchangeAdmin" value="<%= Application("ExchangeAdmin") %>" MAXLENGTH=128></td></tr>
<tr><td>Admin Password (Optional):</td><td><input type="password" name="ExchangePass" value="<% 'Keep original value unless overwritten %>" MAXLENGTH=128></td></tr>
<tr><td COLSPAN=2><font SIZE=-2>&nbsp;</font></td></tr>

<tr><td COLSPAN=2><b>Time Limits</b></td></tr>
<tr><td>Days before overdue:</td><td><input type="text" name="CheckoutPeriod" value="<%= Application("CheckoutPeriod") %>"></td></tr>
<tr><td>Days between notices:</td><td><input type="text" name="RecallPeriod" value="<%= Application("RecallPeriod") %>"></td></tr>
<tr><td COLSPAN=2><font SIZE=-2>&nbsp;</font></td></tr>

<tr><td COLSPAN=2><b>Miscellaneous</b></td><tr> 
<tr><td>Default Item Location:</td><td><input type="text" name="DefaultLocation" value="<%= Application("DefaultLocation") %>" MAXLENGTH=64></td></tr>
<tr><td>Default Domain Name:</td><td><input type="text" name="DefaultDomainName" value="<%= Application("DefaultDomainName")%>" MAXLENGTH=64></td></tr>
<tr><td>Maximum Search Results:</td><td><input type="text" name="MaxSearchResults" value="<%= Application("MaxSearchResults")%>"></td></tr> 
<tr><td>Default Item Status:</td><td><input type="radio" id="in" value="in" name="DefaultItemStatus" <% If Application("DefaultItemStatus") = "in" Then Response.Write "CHECKED" %>><label for="in">In</label>
    <input type="radio" id="pend" value="pend" name="DefaultItemStatus" <% If Application("DefaultItemStatus") = "pend" Then Response.Write "CHECKED" %>><label for="pend">Pending</label>
    
</td></tr>
<tr><td>Debugging Mode:</td><td><input type="radio" id="on" value="on" name="Debug" <% If Application("Debug") Then Response.Write "CHECKED" %>><label for="on">On</Label>
    <input type="radio" id="off" value="off" name="Debug" <% If Not Application("Debug") Then Response.Write "CHECKED" %>><label for="off">Off</Label></td></tr>
<tr><td COLSPAN=2><font SIZE=-2>&nbsp;</font></td></tr>

<tr><td COLSPAN=2><input type="button" value="Update Settings" onClick="ChangeSettings()"></td></tr>

</table>
</form>
</div>
</HTML>
