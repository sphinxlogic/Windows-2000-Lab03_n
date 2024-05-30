****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What StatMsg Does & How

    StatMsg is very similar to the CustMsg sample, everything is the same
    except for the method call and the in-parameters for the method.
    After parsing the command line options and connecting, StatMsg
    creates an instance of IWbemContext.  This instance, also known as
    a context object, is populated with the ApplicationName and 
    MachineName properties.  These 2 context values must be specified when calling
    any of the three SMS_StatusMessage methods: RaiseErrorStatusMsg, 
    RaiseInformationalStatusMsg, and RaiseWarningStatusMsg.  Next, the application 
    retrieves the SMS_StatusMessage class. From this class, StatMsg extracts the 
    in-parameter class for whichever method was selected from the command line and 
    spawns a new instance of this in-param class.  After creating the new instance, 
    StatMsg populates several of the properties, such as the MessageText and the 
    MessageType using the WMI method IWbemClassObject->Put().  Last, after the context 
    object and in-param instance have finished preparations, StatMsg executes the Method, 
    passing in both the context and the in-param instance.  By this time, SMS will have 
    generated a new status message that can be retrieved as an instance of the class
    SMS_StatusMessage

2. Running the Sample

    Command Line Arguments:

	StatMsg <Server> <Message Type> <Message Text> [-I, -W, or -E]
		[options] [-U:<User> [<Password> | *]]
	
	Requirements:
	  Server        : Identifies the name of the machine running the SMS Provider
	  MessageType   : The Type of status Message.  (256=MileStone, 
			  512=Detail, 768=Audit, 1024=NTEvent)
	  MessageText   : The actual text of the status message
	  -I, -W, or -E : Specifies whether to raise an Informational, Warning
			  or Error status message

	Options:
	  -A:<Appname>     : The name of the application raising the status message
			     (Default = "Unknown Application")
	  -M:<Machname>    : The name of the machine raising the status message
			     (Default = "Unknown Machine")
	  -PID:<ProcessID> : The ProcessID of the process raising the status message
			     (Default = 0)
	  -TID:<ThreadID>  : The ThreadID of the thread raising the status message
			     (Default = 0)
	  -U:<username>	   : The UserID for the connection
	     <password>    : Password for the UserID, specifying "*" as the password will
			     force StatMsg to prompt the user for a password

3. Requirements

    Runs on:	NT 4.0+ 
    Windows Management Instrumentation (WMI) must be installed.

4. Building the Sample

    Note: Building the Sample App requires the WMI SDK to be installed.

    Using NMAKE:
	Running NMake at the command line will build the default "makefile" in
	the sample's directory.

    Using the VC++ IDE:
	Open the .DSP Project file and select Build -> Build
	

    