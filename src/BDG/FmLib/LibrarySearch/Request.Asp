<%@ Language=VBScript Transaction=Required %>
<% Option Explicit %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Response.Buffer = TRUE %>
<% Response.Expires = 0 %>
<html>
<head>
<title>Request Item</title>
<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">	

<script LANGUAGE="VBSCRIPT">
<!--
   parent.ClearAllDivs
	parent.request.style.display = ""
	parent.document.all.ifRequest.style.display = ""
-->
</script>
</head>

<body>
<%
   Dim szLogonName, szBibNumber, nBibNumber, szTitle
   
	szLogonName = CStr(Request("Logon"))

	' First get the Bib Number to work with.
	'
	szBibNumber = Request("BibNo")
	If IsEmpty(szBibNumber) Or szBibNumber="" Then
	   Response.Write "ERROR: Missing BibNo."
	   Response.End
	Else
	   nBibNumber = CLng(szBibNumber)
	   If nBibNumber = 0 Then
	      Response.Write "ERROR: Invalid BibNo specified."
	      Response.End
	   End If
	End If
%>

<%
   Dim Requestor, nBorrowerID
	SET Requestor = Server.CreateObject("CML.User")
	Requestor.ConnectionString = Application("FmLib_ConnectionString")
	
	nBorrowerID = Session("BorrowerID")
	If nBorrowerID = 0 Then
	
	   '--- Update borrower information from exchange
	   nBorrowerID = Requestor.UpdateInfoFromExchange(Application("ExchangeServer"), Application("ExchangeOrg"), _
	                                                  Application("ExchangeSite"), szLogonName)
	
	   If nBorrowerID = 0 Then
	      Response.Write "<strong>Can't find '" & szLogonName & "' in Exchange directory...</strong>" & _
	                     "<br>Checkout requests are not allowed. Please contact <a href=""mailto:bdgfeed.microsoft.com"">the Library</a>."
	      Response.End
	   Else
	      Session("BorrowerID") = nBorrowerID
	      
	      '--- Since UpdateInfoFromExchange calls SetComplete, we lose all
	      '--- our user settings when MTS destroys the object.  Let's call
	      '--- up the information one more time.
	      Requestor.GetInfoFromTable nBorrowerID
	      Session("Location") = Requestor.Location
	   End If
	End If
	
	'--- Get current length of request queue
	Dim nWaitListCount, szWaitlist0, szWaitlist1, szWaitlist3
	Requestor.Position nBibNumber, nWaitListCount, nBorrowerID

   IF nWaitListCount >= 1 THEN
		szWaitlist0 = "The requested materials are currently checked out.  <BR>"
		szWaitlist1 = "You will be #" & CStr(nWaitListCount+1) & " on the wait list. <BR>"
		szWaitlist3 = "As soon as a copy is available, it will be delivered to you."
	ELSE
		szWaitlist0 = "<BR>The library will notify you when these materials have been sent. <BR>"
		szWaitlist1 = "For immediate assistance <a href=""mailto:bdgfeed@microsoft.com"">e-mail the Library.</a><BR>"
		szWaitlist3 = ""
	END IF
%>
<form NAME="PostRequest" METHOD="POST" ACTION="requestok.asp?Logon=<% = szLogonName %>&amp;bib=<%=nBibNumber%>">
	<div style="margin-left:50" width=100%>
	<table class="standard">
		<tr>
			<td ALIGN="Center" VALIGN="TOP" WIDTH="600">
				<div style="margin-left:20; font-size: 24pt; color: #ffcc00; text-decoration:none;font-style:italic; font-family: Franklin Gothic Demi,arial">Request this Title?</div><br>
				<p>
				<a CLASS="BlueLink" HREF="javascript:DoLong('<%= nBibNumber %>')" ALT="Full Description"><%= szTitle %></a></strong></font><br>
				<% = szWaitlist0 %>
				<% = szWaitlist1 %>
				<% = szWaitlist3 %>
				<p>
				Delivery location for this request:<br>
				<input name="txtLocation" type="text" size="50" value="<%= Session("Location") %>">
				<p>
				Notes to the library about this request:<br>
				<input name="txtCustomerComment" type="text" size="50"> <p>
				Click <b><input style= "position:absolute;top:288" TYPE="IMAGE" SRC="../images/gobutton.gif" ALT="Make Request" BORDER="0" WIDTH="25" HEIGHT="25" id=IMAGE1 name=IMAGE1> </b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;to make your request.
				<p>
				
			</td>
		</tr>
	</table>
	</div>
</form>

</body>
</html>
