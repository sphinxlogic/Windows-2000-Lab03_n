<% @Language=VBScript 	%>
<% Option Explicit		%>


<HTML>
    <HEAD>
        <TITLE>CDO Component</TITLE>
    </HEAD>


    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>CDO Component</b></font><p>   

		This sample demonstrates how to use the Collaboration
		Data Objects for NTS Component to send a simple
		e-mail message.

		<p>To actually send the message, you must have the SMTP
		Server that comes with the Windows NT Option Pack Installed.

		<%
			Dim myMail
			Set myMail = Server.CreateObject("CDONTS.NewMail")

			' For demonstration proposes, both From and To
			' properties are set to the same address.
		
			myMail.From = "someone@Microsoft.com"
			myMail.To = "someone@Microsoft.com"
		
			myMail.Subject = "Sample"
			myMail.Body = "I hope you like the sample"
			
			myMail.Send
		%>
    </BODY>
</HTML>
