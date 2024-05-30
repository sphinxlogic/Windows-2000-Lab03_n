<% @Language=JScript	%>


<!-- Define Client Side Scripting Function to Display to User 		-->
<!-- Note that server-side scripting is being used to dynamically 	-->
<!-- construct the return message.									-->

<Script Language=JavaScript>
	function Doit()
	{
		alert("Your ASP Session ID is:" + <%=Session.SessionID %>);
	}
</Script>


<HTML>
    <HEAD>
        <TITLE>Client Side Scripting</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
		<!-- Display Header -->

		<font size="4" face="Arial, Helvetica">
		<b>Client Side Scripting</b></font><p>   

		<Input Type=Button Value="Click Here" OnClick=Doit()>
		
    </BODY>
</HTML>
