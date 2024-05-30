****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What SiteBoun Does & How

    SiteBoun performs operations on instances of SMS_SCI_SiteAssignment.
    This class configures the boundaries of an SMS Site using a string 
    array of IP subnets.  Siteboun allows the user to export the array 
    of addresses to a text file, import a text file to replace the array, 
    or append a text file to the end of the array.

2. Running the Sample

    Command Line Arguments:

	SiteBoun <FileName> <Server> [-S:<Sitecode>] 
		 [-E | -I | -A] [-U:<User> [<Password> | *]]
	
	Requirements:
	  FileName	: Text file name to use for importing, exporting, and appending addresses
	  Server        : Identifies the name of the machine running the SMS Provider

	Options:
	  -S:<Sitecode>	: The Sitecode to process the site boundaries. (Default = Login SiteCode)
	  -E		: Export the existing site boundary addresses to the specified file
	  -I		: Import. Overwrites the existing site boundaries with those in the specified file
	  -A		: Append. (SiteBoun defaults to append)
	  -U:<username>	: The UserID for the connection
	     <password>	: Password for the UserID, specifying "*" as the password will
			     force SiteBoun to prompt the user for a password

    Import/Export File:

	This file contains a newline delimited list of site boundaries.  The site boundaries are
	in this format:

	Detail,[type]

	Detail  : Required, usually an IP subnet
	Type	: Optional, defines the boundary type of Detail, defaults to "IP Subnets"

	An exported file would look similar to the following:

	123.234.123.234,IP Subnets
	132.143.132.143,IP Subnets


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
	

    