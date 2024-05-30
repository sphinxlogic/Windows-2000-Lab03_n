<%@ LANGUAGE="VBSCRIPT" %>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual InterDev 1.0">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE>Microsoft OLE DB Provider for AS/400 and VSAM - Active Server Pages Sample</TITLE>
</HEAD>
<BODY BGCOLOR=#FFFFFF> 
<H2>Simple Example Retrieving All Results into an Array</H2>

<%
'This sample is based on host tables similar to those in the Microsoft SQL Server Pubs sample database
	'On Error Resume Next
	Set Conn = Nothing
	Set Conn = Server.CreateObject("ADODB.Connection")
	Conn.Open "Provider=SNAOLEDB;NetLib=SNA;NetAddr=;NetPort=;RemoteLU=DDMDEMO;LocalLU=LOCAL;ModeName=QPCSUPP;Password=SNA;User ID=SNA;Location=DDMDEMO;DefaultLibrary=PUBS;CCSID=37;PCCodePage=1252;HCDFileName=;BinAsChar=NO;RepairKeys=NO;StrictVal=NO;Data Source=Sample;"
	Set RS = Nothing
	Set RS = Server.CreateObject("ADODB.Recordset")
	RS.Open "EXEC OPEN PUBS/AUTHORS", Conn, 2, 4, 1
	' Session.ScriptTimeOut = nMinutes
%>

Here are the results from the query:
<P>
<P>
<TABLE BORDER=1>
<TR>
<% For i = 0 to RS.Fields.Count - 1 %>
	<TD><B><% = RS(i).Name %></B></TD>
<% Next %>
</TR>
<%
' Put up to 10 rows in a 2d variant array
v=RS.GetRows(10) 
%>
<P>
<% For row = 0 to UBound(v,2)  ' iterate through the rows in the variant array %>
	<TR>
	<% For col = 0 to UBound(v,1) %>  
		<TD><% = v(col,row) %> </TD>
	<% Next %>
	</TR>
<% Next %>
</TABLE>
<%
RS.close
set RS = nothing
%>
<BR>
</BODY>
</HTML>

<!--
' Last updated on 12/10/98.
' Copyright 1998 Microsoft Corporation
-->