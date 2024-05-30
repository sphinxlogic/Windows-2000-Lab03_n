****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What MakeColl Does & How

   After parsing the command line and connecting, MakeColl creates a new instance of SMS_Collection.
   (see the SMS SDK sample app SWDist for more info on creating new instances)  In order for the
   new collection to be visible to the SMS Admin UI, an accompanying instance of
   SMS_CollectToSubCollect_a must also be created.  Next, the text file is read line by line and
   calls to GetResourceIDForNetbiosName (or GetResourceIDForIPAddress, depending on the command-
   line parameters) return ResourceID's for machine names or IP's.  This is done by executing a 
   query against instances of SMS_R_System.	After a ResourceID has been retrieved, it is stored
   in an instance of SMS_CollectionRuleDirect, which is embedded in the CollectionRule in-parameter of
   of AddMembershipRule: a method of the newly created collection.  RequestRefresh is then called
   to update the collection's membership according to the new rules.

   This sample demonstrates how to use the helper classes and symbols in SshWbemHelpers.h/.cpp, 
   T_SafeVector.h, and SMSProv.h.  See these files for more information on the helper classes.

2. Running the Sample

    Command Line Arguments:

	MakeColl <FileName> <Collection> <Server> [-S:<SiteCode>]
		 [-U:<User> [<Password> | *]] [-I]
	
	Requirements:
	  FileName	: Text file list of machine names or IP addresses.
	  Collection	: The Name for the collection to be created
	  Server        : Identifies the name of the machine running the SMS Provider

	Options:
	  -U:<username>	: The UserID for the connection
	     <password>	: Password for the UserID, specifying "*" as the password will
			  force MakeColl to prompt the user for a password
	  -I		: Tells MakeColl that the text file contains IP addresses rather
			  than machine names

    The Input File:

	MakeColl requires a text file with a simple newline delimited 
	list of Netbios Machine Names or IP Addresses

3. Requirements

    Runs on:	NT 4.0+ 
    Windows Management Instrumentation (WMI) must be installed.

4. Building the Sample

    To build this sample, you must be using VC++ 5.0 Service Pack 3 or greater
	If you do not have Service Pack 3, you can find it at 
	http://msdn.microsoft.com/vstudio/
    Note: Building the Sample App requires the WMI SDK to be installed.

    Using NMAKE:
	Running NMake at the command line will build the default "makefile" in
	the sample's directory.

    Using the VC++ IDE:
	Open the .DSP Project file and select Build -> Build
	

    