****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What InvList Does & How

    After parsing the command line options and connecting, an
    instance of CInvSink (invsink.cpp) is created.  A call to 
    IWbemServices->ExecQueryAsync is performed passing the new
    CInvSink as the ResponseHandler parameter.  CInvSink->Wait is
    then called to pause execution until the query has completed.
    Executing the query synchronously would have been ideal in this
    situation; an asynchronous call is used for demonstration purposes.
    (for more information, see the section titled Asynchronous Processing
    in the WMI SDK documentation)  ProcessResults() is then passed
    the query results.  For each result from the asynchronous query
    a count query is constructed and executed.  The results of each
    count query are then displayed.

2. Running the Sample

    Command Line Arguments:

	InvList <Server> [-O] [-C] [-M] [-U:<User> [<Password> | *]]
	
	Requirements:
	  Server        : Identifies the name of the machine running the SMS Provider

	Options:
	  -U:<username>	: The UserID for the connection
	     <password> : Password for the UserID, specifying "*" as the password will
			  force InvList to prompt the user for a password
	  -O		: Query Operating System Inventory
	  -C		: Query Processer Inventory
	  -M		: Query RAM Inventory

	Note:
	  By default -O, -C, and -M are specified

3. Requirements

    Runs on:	NT 4.0+ 
    Windows Management Instrumentation (WMI) must be installed.

    Note: You'll need an SMS Site running Hardware Inventory to see any results

4. Building the Sample

    Note: Building the Sample App requires the WMI SDK to be installed.

    Using NMAKE:
	Running NMake at the command line will build the default "makefile" in
	the sample's directory.

    Using the VC++ IDE:
	Open the .DSP Project file and select Build -> Build
	

    