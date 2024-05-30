<% @ LANGUAGE = JScript %>


<HTML>
    <HEAD>
        <TITLE>Ad Rotator Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Ad Rotator Sample</b></font><br>
      
        <hr size="1" color="#000000">


		<%
			var ad;
			
		 	ad = Server.CreateObject("MSWC.AdRotator");
		%>

		<%= ad.GetAdvertisement("adrot.txt") %>

		<a href="AdRotator_JScript.asp"> Revisit Page </a>

    </BODY>
</HTML>
