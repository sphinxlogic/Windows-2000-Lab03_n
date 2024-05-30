<% @Language=VBScript %>
<% Option Explicit	  %>


<Script Language=VBScript RunAt=Server>

	' Define Server Side Script Function

	Function PrintOutMsg(msg, count)

		Dim i


		' Output Message count times

		For i = 1 to count
			Response.Write(msg & "<BR>")    
		Next


		' Return number of iterations
		
		PrintOutMsg = count	

	End Function
	
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
			' Store number of times Function printed message
			Dim x
		
			' Call Function			
			x = PrintOutMsg("This is a function test!", 4)

			' Output the function return value
			Response.Write("<p>The function printed out the message " & x & " times.")
		%>


    </BODY>
</HTML>
