<%@ TRANSACTION=Required LANGUAGE="JScript" %>

<HTML>
    <HEAD>
        <TITLE>Syntax Error Abort within a Transactional Web Page</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


		<!-- Display Header -->

		<font size="4" face="Arial, Helvetica">
		<b>Syntax Error Abort within a Transactional Web Page</b></font><br>
      
		<hr size="1" color="#000000">


		<!-- Brief Description blurb.  -->

		This is an example demonstrating how a runtime error (that will
		stop the execution of the ASP page), will force an abort
		within the Transacted Web Page.  When an abort occurs,
		all transacted changes within this web page (Database,
		MSMQ Message Transmission, etc.) will be rolled back to
		their previous state -- guarenteeing data integrity.


		<%
			// Syntax Error that will produce abort

			blah.blah();
		%>

    </BODY>
</HTML>


<% 
    // The Transacted Script Commit Handler.  This function
    // will be called if the transacted script commits.
    // Note that in the example above, there is no way for the
    // script not to abort.

    function OnTransactionCommit()
    {
        Response.Write ("<p><b>The Transaction just comitted</b>.");
        Response.Write ("This message came from the ");
        Response.Write ("OnTransactionCommit() event handler.");
    }


    // The Transacted Script Abort Handler.  This function
    // will be called if the transacted script aborts
    // Note that in the example above, there is no way for the
    // script not to abort.

    function OnTransactionAbort()
    {
        Response.Write ("<p><b>The Transaction just aborted</b>."); 
        Response.Write ("This message came from the ");
        Response.Write ("OnTransactionAbort() event handler.");
    }
%>