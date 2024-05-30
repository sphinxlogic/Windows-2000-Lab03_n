<%@ Language=JScript%>

<HTML>
    <HEAD>
        <TITLE>Permission Checker</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Permission Checker</b></font><br>   

		<%	
			// Instantiate Permission Checker Component
			
			Check = Server.CreateObject("MSWC.PermissionChecker");
		%>
		
		<p> Verify current user's access to a sample file: 
		
		<p> Using Physical Path =
		<%= Check.HasAccess(".\\PermissionCheck_JScript.asp") %> <br>

		Using Virtual Path =
		<%= Check.HasAccess("/iissamples/sdk/asp/components/PermissionCheck_JScript.asp") %>

    </BODY>
</HTML>
