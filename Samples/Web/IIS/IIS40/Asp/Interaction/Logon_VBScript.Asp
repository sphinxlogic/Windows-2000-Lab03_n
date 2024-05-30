<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<% 
	' Force Authentication if the LOGON_USER Server Variable is blank
	' by sending the Response.Status of 401 Access Denied
	
	' Finish the Page by issuing a Response.End so that a user
	' cannot Cancel through the dialog Box

	If Request.ServerVariables("LOGON_USER") = "" Then
		Response.Status = "401 access denied"
		Response.End		
	End If
%>

<HTML>
    <HEAD>
        <TITLE>Login Screens</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Login Screens</b></font><br>
      
        <hr size="1" color="#000000">

	
		<!-- Display LOGON_USER Server Variable -->

        You logged in as user:<B>  <% = Request.ServerVariables("LOGON_USER") %></B>


		<!-- Display AUTH_TYPE Server Variable -->

		<p>You were authenticated using:<B>  <% = Request.ServerVariables("AUTH_TYPE") %></B> authentication

    </BODY>
</HTML>
