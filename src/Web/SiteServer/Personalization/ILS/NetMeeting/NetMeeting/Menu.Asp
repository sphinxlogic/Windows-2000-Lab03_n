<%
Dim IE 
 
If (InStr(Request.ServerVariables("HTTP_USER_AGENT"), "MSIE")) Then 
	IE = TRUE
Else
	IE = FALSE
End If
%>

<html>

<head>
<title>NetMeeting</title>
</head>
<body bgcolor="#FFFFFF" background="images/L_side_graphic200.GIF" link="#FFFFFF" vlink="#FFFFFF">
<table width="100%" height="100%" cellspacing="0" cellpadding="0">
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="intro.asp?called=True" target="Body">
		<b>Introduction</b></a>
		</font>
		</td>
	</tr>

	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="directory.asp" target="Body">
		<b>Directory</b></a>
		</font>
		</td>
	</tr>
		
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="search.asp" target="Body">
		<b>Search</b></a>
		</font>
		</td>
	</tr>
		
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="srvlist.asp" target="Body">
		<b>Other ILS Servers</b></a>
		</font>
		</td>
	</tr>
		
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="help.htm" target="Body">
		<b>Help</b></a>
		</font>
		</td>
	</tr>
		
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="HTTP://www.microsoft.com/netmeeting" target="_top">
		<b>NetMeeting Home</b></a>
		</font>
		</td>
	</tr>
		
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="mailto:msils@microsoft.com">
		<b>Feedback</b></a>
		</font>
		</td>
	</tr>
		
	<tr>
		<td valign="MIDDLE" align="CENTER">
		<font face="Arial, Helvetica" size="2">
		<a href="about.htm" target="Body">
		<b>About</b></a>
		</font>
		</td>
	</tr>
</table>
</body>
</html>
