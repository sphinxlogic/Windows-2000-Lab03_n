****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What MakeCap Does & How

    MakeCap creates an instance of SMS_SCI_SysResUse.
    Given the machine name provided on the command line, an
    instance of SMS_SCI_SysResUse is spawned, it's itemtype property is
    set to "Client Access Point", and the NALPath property is set to
    \\MachineName\.  This indicates to SMS that the specified
    machine is now available to be used as a client access point.

2. Running the Sample

    Command Line Arguments:

	MakeCap <Server> <Cap Machine> [-S:<Sitecode>] [-U:<User> [<Password> | *]]
	
	Requirements:
	  Server        : Identifies the name of the machine running the SMS Provider
	  Cap Machine 	: The name of the machine to make a Client Access Point (CAP) on

	Options:
	  -S:<Sitecode>	: The Sitecode of the Site Control File to add the CAP to. MakeCap
			     will automatically detect the sitecode if it is not specified
	  -U:<username>	: The UserID for the connection
	     <password>	: Password for the UserID, specifying "*" as the password will
			     force MakeCap to prompt the user for a password

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
	

    