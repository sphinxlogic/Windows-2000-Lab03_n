<%@ LANGUAGE = JScript %>

<HTML>
    <HEAD>
        <TITLE>Using Components</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">

        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Using Components with ASP</b></font><br>
      
        <hr size="1" color="#000000">

		This script use the Tools component 
		that comes with IIS to generate a random number.
		<br>
		<br>


		<% 
			// Instantiate Component on the Server
			example = Server.CreateObject("MSWC.Tools");
		%>
		
		Random Number = <% = example.Random() %>

    </BODY>
</HTML>
