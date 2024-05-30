<% @Language=JScript %>


<Script Language=JScript RunAt=Server>

	// Define Server Side Script Function

	function PrintOutMsg(msg, count)
	{
		// Output Message count times

		for(i = 0; i < count; i++)
		{
			Response.Write(msg + "<BR>");
		}


		// Return number of iterations
		
		return count;
	}
	
</Script>


<HTML>
    <HEAD>
        <TITLE>Functions</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Server Side Functions</b></font><br>   

		<p>
		The function "PrintOutMsg" prints out a specific message a set number of times.
		<p>
		

		<%
			// Call Function			
			x = PrintOutMsg("This is a function test!", 4);

			// Output the function return value
			Response.Write("<p>The function printed out the message " + x + " times.");
		%>


    </BODY>
</HTML>
