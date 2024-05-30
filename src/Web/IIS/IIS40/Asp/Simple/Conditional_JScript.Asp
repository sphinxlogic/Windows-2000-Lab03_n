<%@ LANGUAGE = JScript %>

<HTML>
    <HEAD>
        <TITLE>Conditional Operator Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Conditional Operator Sample</b></font><br>
      
        <hr size="1" color="#000000">


		<%
			// Determine Date

			var dtmVar = new Date();
		%>
		
		
		<!-- Display Date -->

		<P>The date is: <%=dtmVar.getMonth()+1%>/<%=dtmVar.getDate()%>/<%=dtmVar.getYear()%></p>  

		<%
		    // Switch statement to display a message based on the day of the month
			switch (dtmVar.getDate())
			 {
			  case 1:
			  case 2:
			  case 3:
			  case 4:
			  case 5:
			  case 6:
			  case 7:
			  case 8:
			  case 9:
			  case 10:
			   Response.Write("<P>It's the beginning of the month.</P>");
			   break;
			  case 11:
			  case 12:
			  case 13:
			  case 14:
			  case 15:
			  case 16:
			  case 17:
			  case 18:
			  case 19:
			  case 20:
			   Response.Write("<P>It's the middle of the month.</P>");
			   break;
			  default:
			    Response.Write("<P>It's the end of the month.</P>");
			 }
		%>

		<P>The time is: <%=dtmVar.getHours()%>:<%=dtmVar.getMinutes()%>:<%=dtmVar.getSeconds()%></P>

		<%
			// Check for AM/PM, and output appropriate message
		
			if (dtmVar.getHours() >= 12)
			{
				Response.Write("<P>Good Evening</p>");
			}
			else
			{
				Response.Write("<P>Good Morning</p>");
			}
		%>

    </BODY>
</HTML>
