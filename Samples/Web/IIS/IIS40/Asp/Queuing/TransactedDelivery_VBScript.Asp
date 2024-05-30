<%@ TRANSACTION=REQUIRED LANGUAGE=VBScript %>
<%  Option Explicit                        %>

<HTML>
    <HEAD>
        <TITLE>Transacted MSMQ Transmission</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">

        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Transacted MSMQ Transmission</b></font><br>
      
        <hr size="1" color="#000000">

		This sample demonstrates how to send a transacted asynchronous message using 
        the Microsoft Message Queueing Server (MSMQ).  MSMQ is one of the components
        that comes with the Windows NT 4.0 Option Pack.
  
        <p> For this example to work, MSMQ must be first be installed on the host machine.
        Using the MSMQ Explorer, a queue named "IIS_SDK_TRANSACTED" should then be created.  
        Please click the "transacted" option when creating the queue.

        <p>After the example is run, return to the MSMQ Explorer and select "Refresh" from
        the "View" menu.  The recently sent message will then appear within the "IIS_SDK_TRANSACTED"
        queue.

        <%
			Dim QueueInfo
			Dim Queue
			Dim Msg


			' Create MSMQQueueInfo Component to Open
			' MessageQueue

			Set QueueInfo = Server.CreateObject("MSMQ.MSMQQueueInfo")


			' Open Queue.  The queue could be physically located
			' on any machine.  The period in the line below indicates
			' that the queue is located on the local machine.

			QueueInfo.pathname = ".\IIS_SDK_TRANSACTED"
			Set Queue = QueueInfo.Open(2, 0)


			' Create Message Component for Queue
            
			Set Msg = Server.CreateObject("MSMQ.MSMQMessage")


			' Construct Message.  Anything can be passed into both
			' the body and label.  The developer is responsible
			' for marshalling all arguments.  Note that the
			' delivery property has been sent to "Recoverable".
			' This will guarentee that the message will survive
			' a crash or shutdown on the queue machine.
            
			Msg.body = "This is the message body"
			Msg.Label = "This is the message label"
			Msg.Delivery = 1


			' Send Message
		    
			Msg.Send Queue


			' Close Queue
            
			Queue.Close
		%>

    </BODY>
</HTML>

<% 
	' The Transacted Script Commit Handler.  This function
	' will be called if the transacted script commits.

    Sub OnTransactionCommit
    
        Response.Write "<p><b>The Transaction just comitted</b>."
        Response.Write "The MSMQ message was <b>successfully</b> sent"

    End Sub


    ' The Transacted Script Abort Handler.  This function
    ' will be called if the script transacted aborts

    Sub OnTransactionAbort
    
        Response.Write "<p><b>The Transaction just aborted</b>."
        Response.Write "The MSMQ message was <b>not</b> sent"
    
    End Sub
%>
