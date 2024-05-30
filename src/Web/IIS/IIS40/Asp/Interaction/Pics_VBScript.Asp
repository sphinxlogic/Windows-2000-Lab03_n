<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<% 
	' Insert PICS ratings
	Response.PICS("(PICS-1.1 <http://www.rsac.org/ratingv01.html> labels on " & chr(34) & "1997.01.05T08:15-0500" & chr(34) & " until" & chr(34) & "1999.12.31T23:59-0000" & chr(34) & " ratings (v 1 s 0 l 2 n 0))")
%>

<HTML>
    <HEAD>
        <TITLE>PICS Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>PICS Sample</b></font><br>
      
        <hr size="1" color="#000000">

		<p>This sample has the following PICS rating:<p>
		
		violence = 1<br>
		sex = 0<br>
		language = 2<br>
		nudity = 0<br>
    </BODY>
</HTML>
