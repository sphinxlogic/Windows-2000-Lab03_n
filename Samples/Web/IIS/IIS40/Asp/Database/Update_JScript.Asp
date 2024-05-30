<%@ LANGUAGE = JScript %>

<!--#include file="adojavas.inc"-->

<HTML>
    <HEAD>
        <TITLE>Update Database</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Update Database</b></font><br>
      
        <hr size="1" color="#000000">

		<%
			var oConn;		// object for ADODB.Connection obj
			var oRs;		// object for output recordset object
			var curDir;		// Directory of authors.mdb file

			
			// Map authors database to physical path
			curDir = Server.MapPath("\\iissamples\\sdk\\asp\\database\\authors.mdb");


			// Create ADO Connection Component to connect with sample database
			oConn = Server.CreateObject("ADODB.Connection");
			oConn.Open("DBQ="+curDir+";Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;");


			// Create ADO Recordset Component, and associate it with ADO connection
			oRs = Server.CreateObject("ADODB.Recordset");
			oRs.ActiveConnection = oConn;
			
			
			// Get empty recordset
			oRs.Source = "SELECT * FROM authors";
			oRs.CursorType = adOpenStatic;			// use a cursor other than Forward Only
			oRs.LockType = adLockOptimistic;		// use a locktype permitting insertions
			oRs.Open();


			// Change values in first record found
			oRs("Author").Value = "Scott Guthrie";
			oRs("Yearborn").Value = 1975;
			oRs.Update();
		%>

		Changed Author: <%= oRs("Author") %>, <%= oRs("Yearborn") %>
    </BODY>
</HTML>