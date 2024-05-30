<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<HTML>
    <HEAD>
        <TITLE>Conditional Operator Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Conditional Operator Sample</b></font><br>
      
        <hr size="1" color="#000000">


		<!-- If...Then example -->

		<% Dim varDate
		   varDate = Date
		%>

		<P>The date is: <%=varDate%></p>

		<%
		  ' Select Case statement to display a message based on the day of the month
			Select Case Day(varDate)
			  Case 1,2,3,4,5,6,7,8,9,10
			    Response.Write("<P>It's the beginning of the month.</P>")
			  Case 11,12,13,14,15,16,17,18,19,20
			    Response.Write("<P>It's the middle of the month.</P>")
			  Case Else
			    Response.Write("<P>It's the end of the month.</P>")
			End Select
		%>

		<P>The time is: <%=Time%></P>


		<%
			' Check for AM/PM, and output appropriate message
		
			if (Right(Time,2)="AM") Then
			
				Response.Write("<P>Good Morning</p>")
				
			Else
			
				Response.Write("<P>Good Evening</p>")
				
			End If
		%>

    </BODY>
</HTML>
