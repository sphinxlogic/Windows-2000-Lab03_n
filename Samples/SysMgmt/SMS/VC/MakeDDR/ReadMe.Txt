****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What MakeDDR Does & How

    MakeDDR demonstrates using the DDR (Data Discovery Record)
    Functions in the SMSRsGen.dll library.
    These functions allow applications to create their own
    DDR files and send them to the SMS Server from a Client
    machine or the SMS Site Machine.  
    DDR files are used to update Resource information, add extra
    properties such as asset tags to existing Resources, and to
    create new resources. 
    The following sample will create a Car resource which will
    become SMS_R_Car in the SMS Provider. The Car resource will
    contain several default properties and some additional
    ones MakeDDR will add.

    Note, the SMSRsGen.DLL file must be in the same directory 
    as any application which uses the DLL.

2. Running the Sample

    Note: This sample does not use any command line parameters. 

    MakeDDR must be run from an SMS Client machine or an SMS
    Site Server.  Simply type "MakeDDR" from the command line and the
    Site Server will be updated with a new resource that can be accessed
    via the SMS Provider as an instance of SMS_R_Car

3. Requirements

    Runs on:	NT 4.0+
    Running Machine must be an SMS client or an SMS site server

4. Building the Sample

    Using NMAKE:
	Running NMake at the command line will build the default "makefile" in
	the sample's directory.

    Using the VC++ IDE:		
	Now, Open the .DSP Project file and select Build -> Build

	
5. Using the SMSRsGen.DLL

    The SMSRsGen.DLL library provides a set of functions to create
    new Data Discovery Records (DDRs).  The functions allow applications
    to build DDRs and pass them along to the Site Server, thus creating new
    or updating existing resources in the SMS Provider.  Resources are represented
    as instances of classes derived from SMS_Resource and use the SMS_R_ naming
    convention.  For example, system resources are represented as instances of
    the SMS_R_System resource class.  DDRs allow applications to create new types
    of resources, add properties to existing resources, and update information
    in existing resources.

    In order for DDRs to get processed by SMS, they must be sent to either the 
    DDR.BOX directory on the Client Access Point (CAP) or the DDM.BOX directory
    on the site server.  The library code will first check if the machine is an SMS site 
	server and if so will use the DDM inbox.  If it is not a site server the code will 
	get the path to the CAP and use this.  Both directory locations are determined from
	registry settings.  The SMSRsGen.DLL Library handles this through the 
    DDRSendToSMS() function.  When you are done building your ddr, your application 
    should call DDRSendToSMS().

    The library currently consists of the following functions (Note, see the 
    SMSRsGen.h header file in the \include directory for a more detailed
    explanation of each function and its parameters)

	DDRNew() 		- Begins creating a new Data Discovery Record
	DDRAddInteger()		- Adds an integer property to the DDR
    	DDRAddString()		- Adds a string property to the DDR
	DDRAddIntegerArray()	- Adds an integer array property to the DDR
	DDRAddStringArray()	- Adds a string array property to the DDR
	DDRWrite()		- Write the DDR to a file in the current directory
	DDRSendToSMS()		- Locates the CAP or Site Server and sends the DDR to it

    Extending current resource information, such as adding an asset tag to a system
    resource, is rather simple.  To add a property to an existing resource class, 
    create a DDR using the same resource name as the class you wish to extend.  Next,
    specify all the key properties for that resource. (Note: The properties in the System
    resource contain spaces, these are not visible in the class definition, but they are
    visible in the SQL Database.  The NetBIOSName property for instance, would actually be
    specified as 'NetBIOS Name' in a DDR for the System Resource.)  Third, add your new property
    to the end of the DDR, and Send it to SMS.  For example, after you've added the
    Car resource by running MakeDDR, edit the code to add a new integer property called
    "Engine Size" and give it some value, such as 357 or 427.  Re-build the sample
    and run it.  Your car resource should now have the new "Engine Size" property

	If your program is generating multiple DDR records then DDRNew function must be called 
	at the start of each. In other words it's not possible to change one property and then call
	DDRWrite or DDRSendToSMS again for a single DDRNew.

    The generated DDRs are a binary file that contains a resource name, and some
    properties for that resource.  For instance, this sample creates a DDR
    that adds a Car resource to SMS, thus creating an SMS_R_Car class in the
    SMS Provider.  The DDR created by the sample would look something like
    the following: 
    (Several pieces have been removed for the sake of clarity.)

	<Car>			// The Resource Name

	BEGIN_PROPERTY
	<LicenseNumber><ABC123>		// A string property (Name, Value)
	END_PROPERTY

	BEGIN_PROPERTY
	<CarID><1>			// An integer property (Name, Value)
	END_PROPERTY

	BEGIN_PROPERTY
	<Years>				// An integer array property (Name)
	BEGIN_ARRAY_VALUES
	<91>				// 1st element in the array
	<92>				// 2nd element in the array
	<93>				// 3rd element in the array
	END_ARRAY_VALUES
	END_PROPERTY

	BEGIN_PROPERTY
	<Colors>			// A string array property (Name)
	BEGIN_ARRAY_VALUES
	<Red>				// 1st element in the array
	<Black>				// 2nd element in the array
	<Blue>				// 3rd element in the array
	END_ARRAY_VALUES
	END_PROPERTY

	// Info on the discovery agent
	AGENTINFO<VEHICLE_DISCOVERY><ABC><1/18/1999 15:31:16>		
