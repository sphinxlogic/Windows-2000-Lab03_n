<%@ TRANSACTION=Required LANGUAGE="JScript" %>

<!--#include file="adojavas.inc"-->

<HTML>
    <HEAD>
        <TITLE>Transactional Database Update</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Transactional Database Update</b></font><br>
      
        <hr size="1" color="#000000">


        <!-- Brief Description blurb.  -->

        This is a simple example demonstrating how to transactionally 
        update a SQL 6.5 database using ADO and Transacted ASP.
        The example will obtain information regarding a book sale from 
        the SQL 6.5 "Pubs" database.  It will then increment the quantity 
        of books sold by one, as well as change the zip-code of the store 
        in which the book was sold.  

        <p> Because the two database operations are wrapped
        within a shared ASP Transaction, both will be automatically rolled
        back to their previous state in the event of a failure.


	<%
		var oConn;		// object for ADODB.Connection obj
		var oRs;		// object for recordset object
		var oRs2;		// object for recordset object


		// Create Connection and Recordset components

		oConn = Server.CreateObject("ADODB.Connection");
		oRs   = Server.CreateObject("ADODB.Recordset");
		oRs2  = Server.CreateObject("ADODB.Recordset");


		// Open ADO Connection using account "sa"
		// and blank password

		oConn.Open("DSN=LocalServer;UID=sa;PWD=;DATABASE=pubs");
		oRs.ActiveConnection = oConn;
		oRs2.ActiveConnection = oConn;



		// Find a random book sale 

		oRs.Source = "SELECT * FROM sales";
		oRs.CursorType = adOpenStatic;			// use a cursor other than Forward Only
		oRs.LockType = adLockOptimistic;		// use a locktype permitting insertions
		oRs.Open();


		// Change quantity sold

		if (! oRs.EOF) {
			oRs("qty").Value = oRs("qty").Value + 1;
			oRs.Update();
		}
			

			
		// Find the store in which the book was sold

		oRs2.Source = "SELECT * FROM stores where stor_id='" + oRs("stor_id") + "'";
		oRs2.CursorType = adOpenStatic;			// use a cursor other than Forward Only
		oRs2.LockType = adLockOptimistic;		// use a locktype permitting insertions
		oRs2.Open();


		// Change zip code

		if (! oRs2.EOF) {
			oRs2("Zip").Value = new Number(oRs2("Zip").Value) + 1;
			oRs2.Update();
		}
	%>


    </BODY>
</HTML>


<%
    // The Transacted Script Commit Handler.  This sub-routine
    // will be called if the transacted script commits.

    function OnTransactionCommit()
    {
	Response.Write("<p><b>The update was successful</b>.");
    }


    // The Transacted Script Abort Handler.  This sub-routine
    // will be called if the script transacted aborts

    function OnTransactionAbort()
    {
	Response.Write("<p><b>The update was not successful</b>.");
    }
%>