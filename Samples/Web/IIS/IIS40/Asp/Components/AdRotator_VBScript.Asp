<% @ LANGUAGE = VBScript %>
<% Option Explicit      %>

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
			Dim ad
			
		 	Set ad = Server.CreateObject("MSWC.AdRotator")
		%>

		<%= ad.GetAdvertisement("adrot.txt") %>

		<a href="AdRotator_VBScript.asp"> Revisit Page </a>

    </BODY>
</HTML>
