<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<html>

<head>
<title>Microsoft OLE DB Provider for DB2 - Active Server Pages Sample</title>
</head>

<body bgcolor="#FFFFFF">
<div align="center"><center>
<table border="0" width="500">
    <tr>
		<td align="center"><font COLOR="#800000"><strong>
		Microsoft OLE DB Provider for DB2
		<BR>Active Server Pages Sample
		</strong></font></td>
    </tr>
</table>
</center></div>

<%
If Not IsObject(Session("Conn")) Or Not IsObject(Session("RS")) Then
	'On Error Resume Next
	Set Session("Conn") = Nothing
	Set Session("Conn") = Server.CreateObject("ADODB.Connection")
	Session("Conn").Open "Provider=DB2OLEDB;NetLib=SNA;NetAddr=;NetPort=;RemoteLU=DRDADEMO;LocalLU=LOCAL;ModeName=QPCSUPP;User ID=SNA;Password=SNA;InitCat=OLYMPIA;Default Schema=PUBS;PkgCol=PUBS;TPName=0X07F9F9F9;Commit=YES;IsoLvl=NC;AccMode=;CCSID=37;PCCodePage=1252;BinAsChar=NO;Data Source=Sample;"
	Set Session("RS") = Nothing
	Set Session("RS") = Server.CreateObject("ADODB.Recordset")
	Session("RS").Open "SELECT * FROM PUBS.AUTHORS", Session("Conn"), 0, 1, 1 
End If

Select Case Request("action")
	Case 1
		Session("RS").MoveFirst
	Case 2
		Session("RS").MoveNext
		If Session("RS").EOF = True Then
			Session("RS").MoveFirst
		End If
	End Select
%>

<form action="oledbddm.asp" method="POST">
    <input type="hidden" name="action" value="30"><div
    align="center"><center><table border="0" cellspacing="0"
    width="300">
        <tr>
            <td align="right"><font size="3">First Name:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(2))%> </font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">Last Name:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(1))%></font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">Address:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(4))%></font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">ID:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(0))%></font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">City &amp; State:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(5)) & "       "%><% =rtrim(Session("RS")(6))%></font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">Zip Code:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(7))%></font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">Phone Number:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(3))%></font></td>
        </tr>
        <tr>
            <td align="right"><font size="3">Contract:</font></td>
            <td><font size="3"><% =rtrim(Session("RS")(8))%></font></td>
        </tr>

    </table>
    </center></div>
</form>

<form>
    <div align="center"><center><table border="0" cellspacing="0" nowrap width="300">
        <tr>
            <input 
			type="button" 
			name="MoveFirst" 
			value="&lt;&lt; First"
            onclick="top.location='oledbddm.asp?action=1'">
            
            <input type="button" name="MoveNext"
            value="Next &gt; "
            onclick="top.location='oledbddm.asp?action=2'">
            
        </tr>
    </table>
    </center></div>
</form>

</body>
</html>

<!--
' Last updated on 12/10/98.
' Copyright 1998 Microsoft Corporation
-->