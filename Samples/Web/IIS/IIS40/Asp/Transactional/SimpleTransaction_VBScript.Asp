<%@ TRANSACTION=Required LANGUAGE="VBScript" %>

<HTML>
    <HEAD>
        <TITLE>Simple Transactional Web Page</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Simple Transactional Web Page</b></font><br>
      
        <hr size="1" color="#000000">


        <!-- Brief Description blurb.  -->

        This is a simple example demonstrating the basic
        structure of a Transacted Web Page.  

    </BODY>
</HTML>


<%
    ' The Transacted Script Commit Handler.  This sub-routine
    ' will be called if the transacted script commits.
    ' Note that in the example above, there is no way for the
    ' script not to commit.

    Sub OnTransactionCommit()
        Response.Write "<p><b>The Transaction just comitted</b>." 
        Response.Write "This message came from the "
        Response.Write "OnTransactionCommit() event handler."
    end sub


    ' The Transacted Script Abort Handler.  This sub-routine
    ' will be called if the script transacted aborts
    ' Note that in the example above, there is no way for the
    ' script not to commit.

    Sub OnTransactionAbort()
        Response.Write "<p><b>The Transaction just aborted</b>." 
        Response.Write "This message came from the "
        Response.Write "OnTransactionAbort() event handler."
    end sub
%>