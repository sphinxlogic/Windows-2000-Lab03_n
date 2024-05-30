<%@ TRANSACTION=Required LANGUAGE="VBScript" %>
<%  Option Explicit %>

<HTML>
    <HEAD>
        <TITLE>Forced Abort with a Transactional Web Page</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Forced Abort with a Transactional Web Page</b></font><br>
      
        <hr size="1" color="#000000">


        <!-- Brief Description blurb.  -->

        This is an example demonstrating a forced abort
        within a Transacted Web Page.  When an abort occurs,
        all transacted changes within this web page (Database Access,
        MSMQ Message Transmission, etc.) will be rolled back to
        their previous state -- guarenteeing data integrity.


        <%
            ' Abort Transaction

            ObjectContext.SetAbort
        %>

    </BODY>
</HTML>


<%
    ' The Transacted Script Commit Handler.  This sub-routine
    ' will be called if the transacted script commits.
    ' Note that in the example above, there is no way for the
    ' script not to abort.

    Sub OnTransactionCommit()
        Response.Write "<p><b>The Transaction just comitted</b>." 
        Response.Write "This message came from the "
        Response.Write "OnTransactionCommit() event handler."
    end sub


    ' The Transacted Script Abort Handler.  This sub-routine
    ' will be called if the transacted script aborts
    ' Note that in the example above, there is no way for the
    ' script not to abort.

    Sub OnTransactionAbort()
        Response.Write "<p><b>The Transaction just aborted</b>." 
        Response.Write "This message came from the "
        Response.Write "OnTransactionAbort() event handler."
    end sub
%>