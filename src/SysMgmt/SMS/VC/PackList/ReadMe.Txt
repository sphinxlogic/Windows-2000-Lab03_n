****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What PackList Does & How

    After parsing the command line and connecting, packlist enumerates instances of SMS_Package.
    For each instance, the PackageID and Name properties are extracted and displayed.  The PackageID
    is passed to EnumPrograms. EnumPrograms then constructs a query in the form 
    SELECT * FROM SMS_Program where PackageID="<packageid>".
    For each instance returned by the query, the ProgramName is displayed.

2. Running the Sample

    Command Line Arguments:

	PackList <Server> [-U:<User> [<Password> | *]]
	
	Requirements:
	  Server        : Identifies the name of the machine running the SMS Provider.

	Options:
	  -U:<username>	: The UserID for the connection
	     <password> : Password for the UserID, specifying "*" as the password will
			  force PackList to prompt the user for a password

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
	

    