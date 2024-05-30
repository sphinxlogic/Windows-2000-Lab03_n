<%@ Language=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<% Response.Expires = 0 %>
<!-- #include file="AnonLogon.asp" -->
<html>
<head>
<title>Application Settings</title>
<meta NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<link rel="stylesheet" href="../_Themes/fm/theme.css">

<script LANGUAGE="JavaScript">
function showReport()
{
   var div = document.all('FolderReport');
   if(div!=null) div.style.display='';
}
</script>

<% 
   Dim rs,strItem,item,pfid,bChangedID
   Dim fExchange,fTimeLimits,fCritique,fMisc

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
         ' Boolean setting require special handling
         Case "debug", "critiqueenabled", "approvalrequired":
            If (LCase(strItem) = "on") Then
               rs(item) = 1
               Application(item) = True
            Else
               rs(item) = 0
               Application(item) = False
            End If
            
         ' Only update password if specified
         Case "exchangepass":
             If strItem <> "" Then
               rs("ExchangePass") = strItem
               Application("ExchangePass") = strItem
            End If

         Case "publicfoldername":
            If Application("PublicFolderName") <> strItem Then 
               bChangedID = True
               pfid = GetPublishedFolderID(strItem)
               If pfid <> "" Then
                  Application("PublicFolderName") = strItem
                  rs("PublicFolderName") = strItem
                  Application("PublicFolderObjectID") = pfid
                  rs("PublicFolderObjectID") = pfid
               Else
                  bChangedID = False
                  Response.Write "<" & "script LANGUAGE=JavaScript>showReport();</script>"
                  Call ReportError("Folder with name '" & _
                                   strItem & "' doesn't exist.",False)
               End If               
            End If
         
         ' Previous state of the selections
         Case "f_exchange":      fExchange = CBool(strItem)
         Case "f_timelimits":    fTimeLimits = CBool(strItem)
         Case "f_critique":      fCritique = CBool(strItem)
         Case "f_miscellaneous": fMisc = CBool(strItem)
            
         Case Else
            ' If public folder ID changes, don't revert it to old value
            If Not (bChangedID And item="PublicFolderObjectID") Then
               rs(item) = strItem
               Application(item) = strItem
            End If

         End Select
      Next
      
      rs.Update
      rs.Close 
      Set rs = Nothing
   Else
      fExchange = False
      fTimeLimits = False
      fCritique = False
      fMisc = False
   End If  
%>

<script LANGUAGE="JavaScript">
function init()
{
<% If Not fExchange Then %>
   document.all.Exchange.style.display='none';
<% Else %>
   document.all.Image1.src='../images/minus.gif';
<% End If %>

<% If Not fTimeLimits Then %>
   document.all.TimeLimits.style.display='none';
<% Else %>
   document.all.Image2.src='../images/minus.gif';
<% End If %>

<% If Not fCritique Then %>
   document.all.Critique.style.display='none';
<% Else %>
   document.all.Image3.src='../images/minus.gif';
<% End If %>

<% If Not fMisc Then %>
   document.all.Miscellaneous.style.display='none';
<% Else %>
   document.all.Image4.src='../images/minus.gif';
<% End If %>

   // Hide error report (from changing Public Folder Name)
   if (document.all('FolderReport') != null)
      document.all('FolderReport').style.display='none';
}

function expandCollapse ()
{
   var theForm = document.frmSettings;
   
   oSource = event.srcElement;
   if (oSource.className == "COLLAPSINGTITLE")
   {
   	oChild1 = document.all(oSource.getAttribute('CHILD1'));
      oChild2 = document.all(oSource.getAttribute('CHILD2'));
   	if (oChild1.style.display=='none')
   	{
   	   //alert('Expanding: ' + oSource.getAttribute('CHILD1'));
   	   theForm.elements('F_'+oSource.getAttribute('CHILD1')).value = 'True';
    	   oChild1.style.display='';
  	      oChild2.src='../images/minus.gif';
  	   }
   	else
   	{
   	   //alert('Collapsing: ' + oSource.getAttribute('CHILD1'));
   	   theForm.elements('F_'+oSource.getAttribute('CHILD1')).value = 'False';
     	   oChild1.style.display='none';
         oChild2.src='../images/plus.gif';
   	}
    }
  else if (oSource.className == "COLLAPSINGIMAGE")
     {
      oChild1 = document.all(oSource.getAttribute('CHILD1'));
      if(oChild1.style.display=='none')
      {
   	   //alert('Expanding: ' + oSource.getAttribute('CHILD1'));
   	   theForm.elements('F_'+oSource.getAttribute('CHILD1')).value = 'True';
         oChild1.style.display='';
         oSource.src='../images/minus.gif';
      }
      else
      {
   	   //alert('Collapsing: ' + oSource.getAttribute('CHILD1'));
   	   theForm.elements('F_'+oSource.getAttribute('CHILD1')).value = 'False';
         oChild1.style.display='none';
         oSource.src='../images/plus.gif';       
      } 
        
     }
  else
     return;
}

function doMouseOver()
{
   oSource = event.srcElement;
   if (oSource.className == "COLLAPSINGIMAGE")
      oSource = document.all(oSource.getAttribute('CHILD2'));
   if (oSource.className != "COLLAPSINGTITLE")
      return;
   oSource.style.cursor = "hand";
   oSource.style.color = "red";
}

function doMouseOut()
{
   oSource = event.srcElement;
   if (oSource.className == "COLLAPSINGIMAGE")
      oSource = document.all(oSource.getAttribute('CHILD2'));
   if (oSource.className != "COLLAPSINGTITLE") 
      return;
   oSource.style.cursor = "";
   oSource.style.color = "black"; 
}

</script>
</head>

<body BGCOLOR="#FFFFFF" onload="init()" onmouseover="doMouseOver()" onmouseout="doMouseOut()" onclick="expandCollapse()">
<img CLASS="logo" SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img CLASS="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">

<!-- #include file="Navigation.asp"-->

<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 110px; WIDTH: 95%; Z-INDEX: 5;">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Application Settings</span>
</div>

<div class="menui" style="POSITION:absolute;left;20px;top:160px">
<table border="0" class="watermark" height="250" width="200" CELLSPACING="0" CELLPADDING="0">
<tr vAlign="top"><td>
   <table class="admin" WIDTH="75%" BORDER="0" CELLSPACING="2" CELLPADDING="2">
   <tr>
      <td BGCOLOR="#ce6300" valign="top" ALIGN="center" NOWRAP id="mI">Administration</td>
   </tr>
   </table></td>
</tr>
</table>
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

<form NAME="frmSettings" ACTION="<%= Request.ServerVariables("SCRIPT_NAME") %>" METHOD="POST">
<div style="position:absolute;left:100px;top:190px">

<div><img CLASS="COLLAPSINGIMAGE" CHILD1="Exchange" CHILD2="Title1" ID="Image1" src="../images/plus.gif" WIDTH="15" HEIGHT="15">
&nbsp;&nbsp;&nbsp;&nbsp;<b CLASS="COLLAPSINGTITLE" CHILD1="Exchange" CHILD2="Image1" ID="Title1">Exchange</b>
</div>

<input TYPE=Hidden NAME="F_Exchange" VALUE="<%=CStr(fExchange)%>">

<div ID="Exchange">
<table width="65%" COLS="2" BORDER="0">
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Server:</td><td><input type="text" name="ExchangeServer" value="<%= Application("ExchangeServer") %>"></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Organization:</td><td><input type="text" name="ExchangeOrg" value="<%= Application("ExchangeOrg") %>"></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Site:</td><td><input type="text" name="ExchangeSite" value="<%= Application("ExchangeSite") %>" ></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Admin Account (Optional):</td><td><input type="text" name="ExchangeAdmin" value="<%= Application("ExchangeAdmin") %>"></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Admin Password(Optional):</td><td><input type="password" name="ExchangePass" value="<% 'Keep original value unless overwritten %>"></td></tr>
<tr><td COLSPAN="2"><font SIZE="-2">&nbsp;</font></td></tr>
</table>
</div>

<div><img CLASS="COLLAPSINGIMAGE" CHILD1="TimeLimits" CHILD2="Title2" ID="Image2" src="../images/plus.gif" WIDTH="15" HEIGHT="15">
&nbsp;&nbsp;&nbsp;&nbsp;<b CLASS="COLLAPSINGTITLE" CHILD1="TimeLimits" CHILD2="Image2" ID="Title2">Time Limits</b>
</div>
	
<input TYPE=Hidden NAME="F_TimeLimits" VALUE="<%=CStr(fTimeLimits)%>">

<div ID="TimeLimits">
<table width="65%" COLS="2" BORDER="0">
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Days before overdue:</td><td><input type="text" name="CheckoutPeriod" value="<%= Application("CheckoutPeriod") %>"></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Days between notices:</td><td><input type="text" name="RecallPeriod" value="<%= Application("RecallPeriod") %>"></td></tr>
<tr><td COLSPAN="2"><font SIZE="-2">&nbsp;</font></td></tr>
</table>
</div>

<div><img CLASS="COLLAPSINGIMAGE" CHILD1="Critique" CHILD2="Title3" ID="Image3" src="../images/plus.gif" WIDTH="15" HEIGHT="15">
&nbsp;&nbsp;&nbsp;&nbsp;<b CLASS="COLLAPSINGTITLE" CHILD1="Critique" CHILD2="Image3" ID="Title3">Critique</b>
</div>
	
<input TYPE=Hidden NAME="F_Critique" VALUE="<%=CStr(fCritique)%>">

<div ID="Critique">
<table width="65%" COLS="2" BORDER="0">
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Critique Enabled</td><td>
   <input type="radio" id="cbCEy" value="on" name="CritiqueEnabled" <% If Application("CritiqueEnabled") Then Response.Write "CHECKED" %>><label for="cbCEy">Yes</label>
   <input type="radio" id="cbCEn" value="off" name="CritiqueEnabled" <% If Not Application("CritiqueEnabled") Then Response.Write "CHECKED" %>><label for="cbCEn">No</label>
</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Approval Required</td><td>
   <input type="radio" id="cbARy" value="on" name="ApprovalRequired" <% If Application("ApprovalRequired") Then Response.Write "CHECKED" %>><label for="cbARy">Yes</label>
   <input type="radio" id="cbARn" value="off" name="ApprovalRequired" <% If Not Application("ApprovalRequired") Then Response.Write "CHECKED" %>><label for="cbARn">No</label>
</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Approver E-mail Address:</td><td><input type="text" name="ApproverEmail" value="<%= Application("ApproverEmail") %>"></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Maximum Find Results:</td><td><input type="text" name="MaxFindResults" value="<%= Application("MaxFindResults")%>"></td></tr> 
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Public Folder Name:</td><td><input type="text" name="PublicFolderName" value="<%= Application("PublicFolderName")%>" ></td></tr> 
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Public Folder ID:</td><td><input type="text" name="PublicFolderObjectID" value="<%= Application("PublicFolderObjectID")%>"></td></tr> 
<tr><td COLSPAN="2"><font SIZE="-2">&nbsp;</font></td></tr>
</table>
</div>

<div><img CLASS="COLLAPSINGIMAGE" CHILD1="Miscellaneous" CHILD2="Title4" ID="Image4" src="../images/plus.gif" WIDTH="15" HEIGHT="15">
&nbsp;&nbsp;&nbsp;&nbsp;<b CLASS="COLLAPSINGTITLE" CHILD1="Miscellaneous" CHILD2="Image4" ID="Title4">Miscellaneous</b>
</div>

<input TYPE=Hidden NAME="F_Miscellaneous" VALUE="<%=CStr(fMisc)%>">

<div ID="Miscellaneous">
<table width="65%" COLS="2" BORDER="0">
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Default Contact Email:</td><td><input type="text" name="DefaultContactEmail" value="<%= Application("DefaultContactEmail")%>" ></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Default Domain Name:</td><td><input type="text" name="DefaultDomainName" value="<%= Application("DefaultDomainName")%>" ></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Maximum Search Results:</td><td><input type="text" name="MaxSearchResults" value="<%= Application("MaxSearchResults")%>"></td></tr> 
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Default Item Location:</td><td><input type="text" name="DefaultLocation" value="<%= Application("DefaultLocation") %>" ></td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Default Item Status:</td><td>
   <input type="radio" id="in" value="in" name="DefaultItemStatus" <% If Application("DefaultItemStatus") = "in" Then Response.Write "CHECKED" %>><label for="in">In</label>
   <input type="radio" id="pend" value="pend" name="DefaultItemStatus" <% If Application("DefaultItemStatus") = "pend" Then Response.Write "CHECKED" %>><label for="pend">Pending</label>
</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Debugging Mode:</td><td>
   <input type="radio" id="cbDy" value="on" name="Debug" <% If Application("Debug") Then Response.Write "CHECKED" %>><label for="cbDy">On</label>
   <input type="radio" id="cbDn" value="off" name="Debug" <% If Not Application("Debug") Then Response.Write "CHECKED" %>><label for="cbDn">Off</label></td></tr>
<tr><td COLSPAN="2"><font SIZE="-2">&nbsp;</font></td></tr>
</table>
</div>

<div ID="Always">
<table width="65%" COLS="2" BORDER="0">
<tr><td COLSPAN="2"><input type="button" value="Save Changes" onClick="ChangeSettings()" id="button1" name="button1"></td></tr>
</table>
</div>

</div>
</form>
</body>
</html>

