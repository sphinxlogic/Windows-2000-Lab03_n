<%@ Language=VBScript	%>
<%  Option Explicit		%>


<%
	' Ensure that this page is not cached
	Response.Expires = 0
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
			' Instantiate Page Counter Component	

			Dim MyPageCounter
			Set MyPageCounter = Server.CreateObject("MSWC.PageCounter")


			' Determine the number of page hits
			
			Dim HitMe
			HitMe = MyPageCounter.Hits("/iissamples/sdk/asp/components/PageCounter_VBScript.asp")


			' Output the number of hits to the page

			Response.Write "<p>Times visited: " & HitMe
		%>
		
		<p><A href=PageCounter_VBScript.asp> Click here to revisit Page </A>
		
	</BODY>
</HTML>