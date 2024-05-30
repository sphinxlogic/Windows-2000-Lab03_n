<% If (Request("Called") = "") and (Request.Cookies("Search")("BeenHere") <> "") Then %>
	<% Response.Redirect("directory.asp") %>
<% Else %>
	<% Response.Cookies("Search")("BeenHere") = TRUE %>
<% End If %>

<html>
<head>
<title>ILS Intro Page</title>
</head>
<body bgcolor="#FFFFFF">
<table cellspacing="0" width="100%">
	<tr>
		<td width="288"><img src="images/B_NETMEETING.gif" alt="Microsoft NetMeeting" height="67" width="288"></td>
		<td align="CENTER"><b><font face="Arial, Helvetica" size=5>Introduction</font></b></td>
	</tr>
</table>
<p>
<br>
<br>
<br>
<center>
<font face="Arial, Helvetica">
<font size="4" color="#0000CC">Introducing the new ILS Web Site</font> 
<table width=100% cellspacing="10">
	<tr>
		<td colspan="2"><font face="Arial, Helvetica" size="2">
		Along with the release of NetMeeting 2.0, we are pleased to announce a new and enhanced
		ILS web site. This web directory has improved search functionality, helping you  find the NetMeeting users that
		you want to	contact quickly. These enhancements include:<br>
		<br>
		Filter the directory with these criteria:
		<ul>
		<table border=0 cellspacing=0 cellpadding=2>
			<tr>
				<td valign="top"><font face="Arial, Helvetica" size="2"><li><i>Category:</i></td>
				<td><font face="Arial, Helvetica" size="2">Search and list people from within a NetMeeting User Category.</td>
			</tr>
			
			<tr>
				<td valign="top"><font face="Arial, Helvetica" size="2"><li><nobr><i>Call status:</i></nobr></td>
				<td><font face="Arial, Helvetica" size="2">Search for users who are currently not in a call, or who are already in a meeting.</td>
			</tr>
			
			<tr>
				<td valign="top"><font face="Arial, Helvetica" size="2"><li><i>Capability:</i></td>
				<td valign="top"><font face="Arial, Helvetica" size="2">Filter the list based on audio or video capabilities.</td>
			</tr>
		</table>
		</ul>
		
		Search for a particular user based on these criteria:
		<ul>
		<li>Names
		<li>E-Mail Addresses
		<li>Cities/States
		<li>Countries
		<li>Comments
		</ul>
		
		You can also combine several of these options to help you find people more efficiently.<br>
		<br>
		We hope that you find the new web page searches to be powerful yet easy to use. Please
		<a href="mailto:msils@microsoft.com">contact us</a> with your opinion of the new site. Thanks, and keep on NetMeeting!
		</font>
		</td>
	</tr>

	<tr>
		<td>
		<center>
		<font face="Arial, Helvetica" size="3">
		<a href="directory.asp"><b>Look at User Directory</b></a>
		</font>
		</center>
		</td>
	</tr>
</table>
</body>
</html>