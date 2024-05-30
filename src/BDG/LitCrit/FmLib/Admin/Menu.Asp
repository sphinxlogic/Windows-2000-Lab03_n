<%@ Language=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<HTML>
<HEAD>
<TITLE>Administrative Menu</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">	
<img class="logo" SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img class="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">
</HEAD>
<BODY>

<% 
dim currentpage
sub Orange(description, page)
   dim imgx
	imgx="../images/orangedot.gif"
	Response.Write("<TD><IMG src='" & imgx & "'WIDTH=21 HEIGHT=21 id=mI>")
	Response.Write("<TD nowrap class=menu><a class=menu href='" & page & "' id=mIa>" & description & "</a>")
end sub
%>
<body>
<div class=menui id=menu>
<TABLE border=0 class="watermark" height=250 width=250 CELLSPACING=0 CELLPADDING=0>
<TR vAlign=top><TD>

  
   <TABLE class=admin WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
   <TR>
   <TD BGCOLOR=#ce6300 valign=top ALIGN=middle NOWRAP id=mI>
       Administration</TD>
   </TR>
   </TABLE>
   <br>
	<DIV class=orangemenu>
	<TABLE class=small BORDER=0 CELLSPACING=2 CELLPADDING=2>
	<tr>
           <% orange "Library Home Page", "../default.asp" %>
       </tr>
	<tr>
           <% orange "View Library Catalog", "CFilter.asp" %>
       </tr>
	<tr>
           <% orange "Add New Title", "adnmat/AddTitles.asp" %>
       </tr>
   <tr>
           <% orange "View Requests and Check Out","ViewRequests.asp?ShowNoItems=1"%>
       </tr>
   <tr>
           <% orange "Check In Materials", "Checkin.asp" %>
       </tr>
   <tr>
           <% orange "Renew Materials", "Renew.asp" %>
       </tr>
	<tr>
           <% orange "Change Application Settings", "Appsettings.asp" %>
       </tr>
	
	</TABLE>
	</DIV>
</TD></TR>
</TABLE>

<% If Application("Debug") Then
      Dim strLogon
      strLogon = Request.ServerVariables("AUTH_USER")
      If strLogon = "" Then
         strLogon = "<font COLOR=Red>Anonymous</font>"
      End If
  %>
<br><br><center>
<font SIZE=-1>Administrative Logon: <strong><%= strLogon %></strong>
</center>
<% End If %>

</div>
</BODY>
</HTML>
