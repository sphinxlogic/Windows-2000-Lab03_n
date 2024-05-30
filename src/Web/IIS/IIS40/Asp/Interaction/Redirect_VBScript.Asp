<% @Language=VBScript	%>
<% Option Explicit		%>


<%
	' Because we might be redirecting, we must use buffering
	Response.Buffer = True
%>


<HTML>
    <HEAD>
        <TITLE>Redirect Sample</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Redirect Sample</b></font><br>   

		<%
			' If the referring page did not come from
			' the sight "trainer3", Redirect the user
			' to www.microsoft.com

			If Instr(Request.ServerVariables("HTTP_REFERER"), "trainer3") > 0 Then

				' They came from withing the trainer3 web
				' site so we let them continue
				
			Else
			
				' They just linked from outside of the site
				Response.Redirect("http://www.microsoft.com")
				
			End If


			' Flush Response Buffer

			Response.Flush
		%>

    </BODY>
</HTML>
