****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What DiscData Does & How

    This VB Script/Windows Scripting Host sample will prompt the user for the Netbios name of 
    a machine in the SMS hierarchy.  It will then use that name to look up the machine and 
    retrieve any Discovery Data that is associated with it.  

2. Running the Sample

    Use notepad to open up the DiscData.vbs file.  Under the 'Setup connection information'
    comment section, there are four variables that must be set to the correct connection data.
    Change the values of the following variables:

	sAdminUser   : The UserID for connecting to the provider
	sAdminpasswd : Password for the UserID
	sMachine     : The machine name of the provider machine
	sSite	     : SiteCode of the SMS Site Server

    Save the edited DiscData.vbs file, then double-click on it in
    explorer or run it from the command line

3. Requirements

    Runs on:	NT 4.0+ 
    Windows Management Instrumentation (WMI) must be installed.
    The Windows Scripting Host must be installed.
      (The Windows Scripting host can be found at http://msdn.microsoft.com/scripting/)

	

    