<%@ LANGUAGE = JScript	 %>

<%
	// Ensure that the client-browser doesn't cache
	Response.Expires = 0;
%>

<HTML>
    <HEAD>
        <TITLE>Content Rotator Sample</TITLE>
    </HEAD>


    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Contenet Rotator Sample</b></font><br>
      
        <hr size="1" color="#000000">

        <% 
			var Tip;
			Tip = Server.CreateObject("MSWC.ContentRotator");

			Response.Write(Tip.ChooseContent("tiprot.txt"));
		%>

		<hr size="1" color="#000000">
		<A href="ContentRotator_VBScript.asp">Refresh (You may have to do this several times)</A>

    </BODY>
</HTML>
