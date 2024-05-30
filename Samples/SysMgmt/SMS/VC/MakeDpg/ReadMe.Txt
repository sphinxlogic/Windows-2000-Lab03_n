****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What MakeDPG Does & How

    MakeDPG creates instances of SMS_DistributionPointGroup.
    Instances of SMS_DistributionPointGroup contain an array
    defining which distribution points are included in the
    group.  To populate this array, MakeDPG reads entries from
    a text file.  As each entry is read from the file, it is
    checked against a list of available distribution points
    in the site control file.  If the entry from the file is
    a valid distribution point, it is added to the distribution
    point group array.

2. Running the Sample

    Command Line Arguments:

	MakeDPG <File Name> <Group Name> <Server> [-S:<Sitecode>] [-U:<User> [<Password> | *]]
	
	Requirements:
	  File Name	: Text file that contains a list of distribution points
	  Group Name	: Name for the new distribution point group
	  Server        : Identifies the name of the machine running the SMS Provider

	Options:
	  -S:<Sitecode>    : The Sitecode of the Site Server. MakeDPG will automatically
			     detect the sitecode if it is not specified
	  -U:<username>	   : The UserID for the connection
	     <password>    : Password for the UserID, specifying "*" as the password will
			     force MakeDPG to prompt the user for a password

    Input file:

	The input file is a simple text file that contains a newline delimited
	list of Netbios machine names.

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
	

    