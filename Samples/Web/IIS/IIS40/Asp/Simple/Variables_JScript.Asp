<%@ LANGUAGE = JScript %>

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
			// Declare variable
			var intVariable;

			// Assign the variable an integer value
			intVariable = 5;
		%>

		<P><%=intVariable%> + <%=intVariable%> =
		<%=intVariable + intVariable%></p>


		<HR>
		<H3> String Manipulation </h3>

		<%
			// Declare variable
			var strVariable;

			// Assign the variable a string value
			strVariable = "Jemearl";
		%>


		<P>This example was done by <%=strVariable + " Smith" %></p>		


		<HR>
		<H3> Boolean Manipulation </h3>

		<%
			// Declare variable
			var blnVariable;

			// Assign the variable a boolean value
			blnVariable = true;

			// Output Message based on value
			if (blnVariable = true)
			{
			  Response.Write("<P>The boolean value is True.</P>");
			}
			else
			{
			  Response.Write("<P>The boolean value is False.</P>");
			}
		%>
		
		<HR>
		<H3> Date and Time </h3>

		<%
			// Declare variable
			var dtmVariable;

			// Assign the variable a value
			dtmVariable = new Date(1997, 08, 27, 17, 11, 42);
		%>

		<P>The date and time is <%=dtmVariable%> </p>

		<%
			// Set the variable to the web server date and time
			dtmVariable = new Date();
		%>

		<P>The <STRONG>system</strong> date and time
		is <%=dtmVariable%></p>

    </BODY>
</HTML>
