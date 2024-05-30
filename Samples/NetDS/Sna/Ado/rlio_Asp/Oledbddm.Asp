<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<html>

<head>
<title>Microsoft OLE DB Provider for AS/400 and VSAM - Active Server Pages Sample</title>
</head>

<body bgcolor="#FFFFFF">
<div align="center"><center>
<table border="0" width="500">
    <tr>
		<td align="center"><font COLOR="#800000"><strong>
		Microsoft OLE DB Provider for AS/400 and VSAM
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
	Session("Conn").Open "Provider=SNAOLEDB;NetLib=SNA;NetAddr=;NetPort=;RemoteLU=DDMDEMO;LocalLU=LOCAL;ModeName=QPCSUPP;Password=SNA;User ID=SNA;Location=DDMDEMO;DefaultLibrary=PUBS;CCSID=37;PCCodePage=1252;HCDFileName=;BinAsChar=NO;RepairKeys=NO;StrictVal=NO;Data Source=Sample;"
	Set Session("RS") = Nothing
	Set Session("RS") = Server.CreateObject("ADODB.Recordset")
	Session("RS").Open "EXEC OPEN PUBS/AUTHORS", Session("Conn"), 2, 4, 1
End If

Select Case Request("action")
	Case 1
		Session("RS").MoveFirst
	Case 2
		Session("RS").MovePrevious
		If Session("RS").BOF = True Then
			Session("RS").MoveFirst
		End If
	Case 3
		Session("RS").MoveNext
		If Session("RS").EOF = True Then
			Session("RS").MoveLast
		End If
	Case 4  
		Session("RS").MoveLast
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
            
			<input 
			type="button" 
			name="MovePrevious"
            value="&lt; Prev "
            onclick="top.location='oledbddm.asp?action=2'">

            <input type="button" name="MoveNext"
            value="Next &gt; "
            onclick="top.location='oledbddm.asp?action=3'">

            <input type="button" name="MoveLast"
            value="Last  &gt;&gt;"
            onclick="top.location='oledbddm.asp?action=4'">
            
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