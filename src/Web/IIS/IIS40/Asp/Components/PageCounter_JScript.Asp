<%@ Language=JScript		%>


<%
	// Ensure that this page is not cached
	
	Response.Expires = 0;
%>


<HTML>
    <HEAD>
        <TITLE>Page Counter</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Page Counter Component</b></font><br>   

		<%
			// Instantiate Page Counter Component	

			var MyPageCounter;
			MyPageCounter = Server.CreateObject("MSWC.PageCounter");


			// Determine the number of page hits
			
			var HitMe;
			HitMe = MyPageCounter.Hits("/iissamples/sdk/asp/components/PageCounter_JScript.asp");


			// Output the number of hits to the page

			Response.Write("<p>Times visited: " + HitMe);
		%>
		
		<p><A href=PageCounter_JScript.asp> Click here to revisit Page </A>
		
	</BODY>
</HTML>
