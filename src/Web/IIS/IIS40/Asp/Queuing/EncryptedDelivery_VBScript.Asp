<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<HTML>
    <HEAD>
        <TITLE>Encrypted MSMQ Transmission</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">

        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Encrypted MSMQ Transmission</b></font><br>
      
        <hr size="1" color="#000000">

		This sample demonstrates how to send an encrypted asynchronous message using 
        the Microsoft Message Queueing Server (MSMQ).  MSMQ is one of the components
        that comes with the Windows NT 4.0 Option Pack.
  
        <p> For this example to work, MSMQ must be first be installed on the host machine.
        Using the MSMQ Explorer, a queue named "IIS_SDK_EXAMPLE" should then be created.
        After the example is run, return to the MSMQ Explorer and select "Refresh" from
        the "View" menu.  The recently sent message will then appear within the "IIS_SDK_EXAMPLE"
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

			QueueInfo.pathname = ".\IIS_SDK_EXAMPLE"
			Set Queue = QueueInfo.Open(2, 0)


			' Create Message Component for Queue
            
			Set Msg = Server.CreateObject("MSMQ.MSMQMessage")


			' Construct Message.  Note that the PrivLevel of
			' the message has been set to require encryption.
			' This will ensure that the message remains encrypted
			' until an authorized receiver reads it.

			Msg.PrivLevel = 1
			Msg.body = "This is the message body"
			Msg.Label = "This is the message label"


			' Send Message
		    
			Msg.Send(Queue)


			' Close Queue
            
			Queue.Close
		%>

    </BODY>
</HTML>
