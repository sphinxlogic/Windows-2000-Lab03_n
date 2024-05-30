<% @Language=JScript	%>

<%
	// Because we might be redirecting, we must use buffering
	Response.Buffer = true;
%>

<HTML>
    <HEAD>
        <TITLE>Redirect Sample</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Redirect Sample</b></font><br>   

		<%
			// If the referring page did not come
			// from the sight "trainer3", Redirect
			// the user to www.microsoft.com

			var referer = Request.ServerVariables("HTTP_REFERER");

			if (referer == "trainer3") 
			{
				// They came from withing the trainer3
				// web site so we let them continue
			}
			else
			{
				// They just linked from outside of the site
				Response.Redirect("http://www.microsoft.com");
			}


			// Flush Response Buffer
			Response.Flush();
		%>

    </BODY>
</HTML>
