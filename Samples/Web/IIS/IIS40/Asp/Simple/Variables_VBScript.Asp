<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<HTML>
    <HEAD>
        <TITLE>Variable Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Variable Sample</b></font><br>
      
	  
        <hr>
		<H3> Integer Manipulaiton </h3>

		<%
			' Declare variable
			Dim intVariable

			' Assign the variable an integer value
			intVariable = 5
		%>


		<P><%=intVariable%> + <%=intVariable%> =
		<%=intVariable + intVariable%></p>


		<HR>
		<H3> String Manipulation </h3>

		<%
			' Declare variable
			Dim strVariable

			' Assign the variable a string value
			strVariable = "Jemearl"
		%>

		<P>This example was done by	<%=strVariable + " Smith" %></p>		


		<HR>
		<H3> Boolean Manipulation </h3>

		<%
			' Declare variable
			Dim blnVariable

			' Assign the variable a boolean value
			blnVariable = true
			
			' Output message based on value
			If (blnVariable = true) Then
			  Response.Write "<P>The boolean value is True.</P>"
			Else
			  Response.Write "<P>The boolean value is False.</P>"
			End If
		%>
		
		<HR>
		<H3> Date and Time </h3>

		<%
			' Declare variable
			Dim dtmVariable

			' Assign the variable a value
			dtmVariable = #08 / 27 / 97 5:11:42pm#
		%>

		<P>The date and time is <%=dtmVariable%> </p>

		<%
			' Set the variable to the web server date and time
			dtmVariable = Now
		%>

		<P>The <STRONG>system</strong> date and time is
		<%=dtmVariable%></p>

    </BODY>
</HTML>
