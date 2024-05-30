<%@ LANGUAGE=VBScript Transaction=Required %>
<% Option Explicit %>
<% ' Copyright (c) 1998-1999 Microsoft Corporation.  All rights reserved. %>
<% Response.Buffer = TRUE %>
<% Response.Expires = 0 %>
<HTML>
<HEAD>
<TITLE>Request Item Response</TITLE>
<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">	

<SCRIPT LANGUAGE=VBSCRIPT>
<!--
   parent.request.style.display = "none"
   parent.requestok.style.display = ""
-->
</SCRIPT>

</HEAD>
<BODY BGCOLOR="FFFFFF" TEXT=000000 LINK=0099ff VLINK=800080 TOPMARGIN="0" LEFTMARGIN=0>

<% Dim szLogonName, szBibNumber, nBibNumber, szCustomerComment
	szLogonName = CStr(Request("Logon"))

	' First get the Bib Number to work with.
	'
	szBibNumber = Request("bib")
	nBibNumber = CLng(szBibNumber)

	szCustomerComment = Request.Form("txtCustomerComment") 
	IF szCustomerComment = "" THEN
		szCustomerComment = Request("CustomerComment")
	END IF

   Dim Requestor, nBorrowerID, Position, Location, nWaitListLength
	SET Requestor = Server.CreateObject("CML.User")
	Requestor.ConnectionString = Application("FmLib_ConnectionString")
	
	nBorrowerID = Session("BorrowerID")
	If nBorrowerID = 0 Then
	   nBorrowerID = Requestor.GetInfoFromTable(szLogonName)
	   Session("BorrowerID") = nBorrowerID
	   Session("Location") = Requestor.Location
	End If
	
	'--- Set delivery location from QueryString, if present
	Location = Request.QueryString("txtLocation")
	If Location = "" Then Location = Session("Location")
	
	Position = Requestor.Position(nBibNumber, nWaitListLength, nBorrowerID)
	If Position <= 0 Then
	   Requestor.MakeRequest nBibNumber, Location, szCustomerComment, nBorrowerID
%>
<BR>
<BR>
	<TABLE class="standard" WIDTH="100%">
		<TR ALIGN="LEFT" VALIGN="TOP">
			<TD ALIGN="Center" VALIGN="TOP">
				<STRONG>Thank you <%= UCase(szLogonName) %>!</STRONG><BR>
				Your request has been entered.
			</TD>
		</TR>
	</TABLE>
<% Else %>
<BR>
<BR>
	<TABLE class="standard" WIDTH="100%">
		<TR ALIGN="LEFT" VALIGN="TOP">
			<TD ALIGN="Center" VALIGN="TOP">
				<STRONG>A request for <%= UCase(szLogonName) %> has already been entered.</STRONG><BR>
				Your request is #<%= Position %> of <%= nWaitListLength %>.
			</TD>
		</TR>
	</TABLE>
<% End If %>

</BODY>
</HTML>


