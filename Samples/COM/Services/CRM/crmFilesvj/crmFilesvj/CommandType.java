package crmfilesvj;

/*+==========================================================================
File: crmfilesvj.CommandType.java

Summary: 
	This is a sample Compensating Resource Manager (CRM) that creates and 
	deletes files. The CRM Worker provides an interface for creating or 
	deleting files.The CRM Compensator implements ICrmCompensator to receive 
	transaction outcome notifications. The CRM Compensator also implements 
	ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library
	application. The CRM Worker requires a transaction. The CRM Compensator
	should not have a transaction.

----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/


import com.ms.wfc.core.*;

class CommandType extends Enum
	{
	// Fields

	public static final int ct_CreateFile = 0;
	public static final int ct_DeleteFile = 1;

	// Methods
	
	public static boolean valid( int value )
		{
		return value == ct_CreateFile || value == ct_DeleteFile;
		}
	}
