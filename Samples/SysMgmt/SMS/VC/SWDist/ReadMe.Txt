****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What SWDist Does & How

    After parsing the command line and connecting, SWDist calls
    IWbemServices->GetObject to get a SMS_Package class object.
    This class object is used to call SpawnInstance to return an
    instance object.  The Name property is stored with
    IWbemClassObject->Put and the instance is then stored with
    IWbemServices->PutInstance.  PutInstance returns an IWbemCallResult
    object, which is then used to call GetResultString.  This 
    returns the object path of the newly created package.
    This procedure is re-used to create instances of SMS_Program
    and SMS_Advertisement that correlate with the Package

2. Running the Sample

    Command Line Arguments:

	SWDist <Server> [-U:<User> [<Password> | *]]
	
	Requirements:
	  Server        : Identifies the name of the machine running the SMS Provider

	Options:
	  -U:<username>	   : The UserID for the connection
	     <password>    : Password for the UserID, specifying "*" as the password will
			     force SWDist to prompt the user for a password

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
	

    