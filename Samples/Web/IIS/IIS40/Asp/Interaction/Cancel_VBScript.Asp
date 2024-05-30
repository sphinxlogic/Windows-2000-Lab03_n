<%@ Language=VBScript	%>
<% Option Explicit		%>

<HTML>
    <HEAD>
        <TITLE>Client Connection</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Client Connection</b></font><br>   

		<p>About to perform compute intensive operation<br>

		<%
			Dim x, i
			x = 1
		
		
			' Perform a long operation.....

			For i = 1 to 1000
				x = x + 5				
			Next


			' Check to see if the client is still connected
			' before doing anything more

			If Response.IsClientConnected Then 

				' Ouput Status
				Response.Write "User is still connected<br>"


				' Perform another long operation

				For i = 1 to 1000
					x = x + 5				
				Next
				
			End If

			
			' If the user is still connected, send back
			' a closing message
			
			If Response.IsClientConnected Then 

				Response.Write "<p>Finished<br>"
				Response.Write "Thank you for staying around!  :-)"

			End If
		%>

    </BODY>
</HTML>
