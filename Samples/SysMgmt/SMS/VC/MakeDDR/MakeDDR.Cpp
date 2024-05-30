// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// MakeDDR - Version 1.0
//
// MakeDDR demonstrates using the DDR (Data Discovery Record)
// Functions in the SMSRsGen.dll library.
// These functions allow applications to create their own
// DDR files and send them to the SMS Server from a Client
// machine or the SMS Site Machine.  
// DDR files are used to update Resource information, add extra
// properties such as asset tags to existing Resources, and to
// create new resources. 
// The following sample will create a Car resource which will
// become SMS_R_Car in the SMS Provider. The Car resource will
// contain several default properties and some Additional
// ones MakeDRR will add.
//
// Note, The SMSRsGen.DLL file must be in the same directory 
// as any application which uses the DLL.
//
// The SMSRsGen.lib and SMSRsGen.h files must visible and included
// in order to build this sample.
// *************************************************************

#include <stdio.h>
#include "SMSRsGen.h"

int main(int argc, char *argv[])
{
	printf("Starting\n");
	// *** Begin Creating a New DDR ***
	// Parameters:
	//  1 - The Resource Name, which becomes SMS_R_<ResourceName> in the Provider
	//  2 - The Discovery Agent that found the resource
	//  3 - The Sitecode of the SMS Site that discovered this resource.
	DDRNew("Car","VEHICLE_DISCOVERY","ABC");
	

	// *** Add a string property. ***
	// Parameters:
	//  1 - Property name
	//  2 - Actual Value of the property
	//  3 - Width of the SQL Column that is generated for this property (usually 32, 64, or 256)
	//  4 - Flags, ( In this case, this property is a key value and will be the Name for the resource)
	//             ( All resources must have One Name property)
	//             ( See the SMSRsGen.h file for more info on the Flags)
	DDRAddString("LicenseNumber", "ABC123", 32, ADDPROP_NAME);
	

	// *** Add a guid property. ***
	// 
	// Flags, ( Here, we are adding a GUID Property.  All Architectures should have this property defined in them)
	//        ( The "SMS Unique Identifier" property is what links the Resource data with Inventory Data)
	//        ( See the SMSRsGen.h file for more info on the Flags)
	DDRAddString("SMS Unique Identifier", "GUID:12345678-1234-1234-1234-123456789012", 45, ADDPROP_GUID | ADDPROP_KEY);


	// *** Add an integer property ***
	// Parameters:
	//  1 - Property Name
	//  2 - Actual Value of the Property
	//  3 - Flags (This property will also be a Key value for the resource)
	DDRAddInteger("CarID", 1, ADDPROP_KEY);


	// *** Add an array of integers ***
	long lArray[3] = {91,92,93};

	// Parameters
	//  1 - Property Name
	//  2 - Address of the Array
	//  3 - Number of Elements in the array
	//  4 - Flags 
	DDRAddIntegerArray("Years", lArray, 3, 0);
	

	// *** Add an array of strings ***
	char *sColors[3] = {"Red", "Black", "Blue"};
	
	// Parameters:
	//  1 - Property Name
	//  2 - Address of the Array
	//  3 - Number of elements in the array
	//  4 - Size of the SQL Table that SMS creates (usually 32, 64, or 256)
	//  5 - Flags
	DDRAddStringArray("Colors", sColors, 3, 64, 0);
	

	// *** Send the DDR to SMS ***
	// Note: This presently requires the application to be running from an SMS Client or Site Server
	// that supports UNC naming conventions, more support is planned in the future.
	printf("- Sending DDR");
	
	if(DDRSendToSMS() != S_OK)	
	{
		printf("-- Error Sending DDR");
	}
	else
	{
		printf("- Success");
	}

	// *** Write the DDR to a file in the current directory ***
	printf("- Writing the DDR");

	// Parameters:
	//  1 - FileName
	DDRWrite("Car.ddr");

	// At this point, there should be a new SMS_R_Car class in the provider,
	// and an instance correlating to the properties specified in this application

	return 0;
}