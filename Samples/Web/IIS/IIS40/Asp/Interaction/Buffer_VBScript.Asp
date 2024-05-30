<% @Language=VBScript	%>
<% Option Explicit		%>


<%
	' Turn Buffering on (this must be done before anything is sent
	Response.Buffer = TRUE
%>


<HTML>
    <HEAD>
        <TITLE>This is Bogus HTML</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>You shouldn't see this!!</b></font><br>   

    </BODY>
</HTML>


<%
	' Clear everything already printed
	Response.Clear
%>


<HTML>
    <HEAD>
        <TITLE>Buffering Example</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Buffering Example</b></font><p>   

		This html was buffered on the server before it was sent.

    </BODY>
</HTML>


<%
	' Send the new html
	
	Response.Flush
%>
