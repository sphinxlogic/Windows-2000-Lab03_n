****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What CustMsg Does & How

    After parsing the command line options and connecting, CustMsg
    creates an instance of IWbemContext.  This instance, also known as
    a context object, is populated with the ApplicationName and 
    MachineName properties.  These 2 context values must be specifed when calling
    the SMS_StatusMessage::RaiseRawStatusMessage method.  Next, the application
    retrieves the SMS_StatusMessage class.  From this class, CustMsg extracts the
    in-parameter class for the RaiseRawStatusMessage method, and spawns a new instance
    of this in-param class.  After creating the new instance, CustMsg populates several
    of the properties, such as the MessageID and the MessageType using the WMI method
    IWbemClassObject->Put().  Last, after the context object and in-param instance have
    finished preparing, CustMsg executes the Method, passing in both the context and the
    in-param instance.  By this time, SMS will have generated a new status message that
    can be retrieved as an instance of SMS_StatusMessage

2. Running the Sample

    Command Line Arguments:

	CustMsg <Server> <Message ID> <Message Type>
		[options] [-U:<User> [<Password> | *]]
	
	Requirements:
	  Server      : Identifies the name of the machine running the SMS Provider
	  MessageID   : The Message ID of the status message
	  MessageType : The Type of status Message.  (256=MileStone, 
			512=Detail, 768=Audit, 1024=NTEvent)

	Options:
	  -C:<ModuleName>  : The name of the module containing the status message
			     This parameter is only useful for raising status messages
			     From Custom Message DLLs, otherwise use the default
			     (Default = "SMS Provider")
	  -A:<Appname>     : The name of the application raising the status message
			     (Default = "Unknown Application")
	  -M:<Machname>    : The name of the machine raising the status message
			     (Default = "Unknown Machine")
	  -PID:<ProcessID> : The ProcessID of the process raising the status message
			     (Default = 0)
	  -TID:<ThreadID>  : The ThreadID of the thread raising the status message
			     (Default = 0)
	  -I:<ins string 1>,<ins string 2>,...,<ins string n>:
			     this option is used to specify the Insertion strings for
			     the status message. (ex\ -I:Monday,January)
	  -U:<username>	   : The UserID for the connection
	     <password>    : Password for the UserID, specifying "*" as the password will
			     force CustMsg to prompt the user for a password

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
	

    