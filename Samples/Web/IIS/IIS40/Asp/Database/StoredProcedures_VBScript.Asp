<% 	@ LANGUAGE="VBSCRIPT" 		%>
<%	Option Explicit				%>

<!--#include file="adovbs.inc"-->

<%
	' This example can be used to call the ByRoyalty stored procedure 
	' installed with the PUBS database with Microsoft SQL Server.

	' This sample assumes that SQL Server is running on the local machine
%>


<HTML>
    <HEAD>
        <TITLE>Using Stored Procedures</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Using Stored Procedures</b></font><p>   

		<%
			Dim oConn		
			Dim oCmd	
			Dim oRs		

			Set oConn = Server.CreateObject("ADODB.Connection")
			Set oCmd = Server.CreateObject("ADODB.Command")

			
			' Open ADO Connection using account "sa"
			' and blank password

			oConn.Open "DSN=LocalServer;UID=sa;PWD=;DATABASE=pubs"
			Set oCmd.ActiveConnection = oConn


			' Setup Call to Stored Procedure and append parameters

			oCmd.CommandText = "{call byroyalty(?)}"
			oCmd.Parameters.Append oCmd.CreateParameter("@Percentage", adInteger, adParamInput)

			
			' Assign value to input parameter

			oCmd("@Percentage") = 75


			' Fire the Stored Proc and assign resulting recordset
			' to our previously created object variable
					
			Set oRs = oCmd.Execute			
		%>

		Author ID = <% Response.Write oRs("au_id") %><BR>

    </BODY>
</HTML>
