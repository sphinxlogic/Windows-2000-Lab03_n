<%@ LANGUAGE = JScript %>

<!--#include file="adojavas.inc"-->

<HTML>
    <HEAD>
        <TITLE>Add/Delete Database Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Add/Delete Database Sample</b></font><br>
      
        <hr size="1" color="#000000">


		<%
			var oConn;	
			var oRs;		
			var curDir;	

			
			// Map authors database to physical path
			
			curDir = Server.MapPath("\\iissamples\\sdk\\asp\\database\\authors.mdb");


			// Create ADO Connection Component to connect
			// with sample database
			
			oConn = Server.CreateObject("ADODB.Connection");
			oConn.Open("DBQ="+curDir+";Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;")


			// Create ADO Recordset Component, and associate
			// it with ADO connection
			
			oRs = Server.CreateObject("ADODB.Recordset");
			oRs.ActiveConnection = oConn;
			
			
			// Get empty recordset
			
			oRs.Source = "SELECT * FROM authors Where 1=2";
			oRs.CursorType = adOpenStatic;			
			oRs.LockType = adLockOptimistic;
			oRs.Open();


			// Add New Record
			
			oRs.Addnew();							
			oRs("Author").Value = "Paul Enfield";
			oRs("YearBorn").Value = 1967;			
			oRs.Update();


			// Output Result
			
			Response.Write("<p>Inserted Author: "+oRs("Author")+"," + oRs("YearBorn"));


			// Close Recordset
			
			oRs.Close();

			
			// Create Recordset Component for deletion operation
			
			oRs = Server.CreateObject("ADODB.Recordset");
			oRs.ActiveConnection = oConn;
		
		
			// Create Recordset
			
			oRs.Source = "SELECT * FROM authors WHERE YearBorn=1967 and Author='Paul Enfield'";	
			oRs.CursorType = adOpenForwardOnly;
			oRs.LockType = adLockOptimistic;
			oRs.Open();


			// Delete record matching query
			
			oRs.Delete();
			oRs.Update();

			
			// Output Status Result
			
			Response.Write("<p>Deleted Author: Paul Enfield, 1967");
		%>
    </BODY>
</HTML>
