<%@ Language=JScript %>

<HTML>
    <HEAD>
        <TITLE>Session Management</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Session Management</b></font><br>   

		<p>This ASP Session will timeout after 25 minutes
		of inactivity.

		<%
			Session.Timeout = 25;
		%>

    </BODY>
</HTML>
