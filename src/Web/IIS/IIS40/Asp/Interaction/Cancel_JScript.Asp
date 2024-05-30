<%@ Language=JScript 	%>

<HTML>
    <HEAD>
        <TITLE>Client Connection</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Client Connection</b></font><br>   

		<p>About to perform a compute intensive operation... <br>

		<%
			var x, i;
			x = 1;
		
		
			// Perform a long operation.....

			for(i = 0; i < 1000; i++)
			{
				x = x + 5;
			}				


			// Check to see if the client is still
			// connected before doing anything more

			if (Response.IsClientConnected())
			{ 
				// Ouput Status
				Response.Write("User still connected<br>");


				// Perform another long operation

				for (i = 1; i < 1000; i++)
				{
					x = x + 5;
				}				
			}

			
			// If the user is still connected, send back
			// a closing message
			
			if (Response.IsClientConnected())
			{ 
				Response.Write("<p>Finished<br>");
				Response.Write("Thank you for staying around!  :-)");
			}
		%>

	</BODY>
</HTML>
