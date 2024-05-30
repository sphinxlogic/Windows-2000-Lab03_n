/**	comsvcs.XACTE.java

This is a sample Compensating Resource Manager (CRM) that creates and 
deletes files. The CRM Worker provides an interface for creating or 
deleting files.The CRM Compensator implements ICrmCompensator to receive 
transaction outcome notifications. The CRM Compensator also implements 
ICrmFormatLogRecords to support monitoring.

This CRM can be installed in a server application or in a library
application. The CRM Worker requires a transaction. The CRM Compensator
should not have a transaction.


This file is part of the Microsoft COM Technology Samples.

Copyright (C) 1998 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

*/

package comsvcs;

import com.ms.wfc.core.*;

public class XACTE extends Enum
	{
	public static final int XACT_E_FIRST					= 0x8004d000;
	public static final int XACT_E_LAST						= 0x8004d022;
	public static final int XACT_S_FIRST					= 0x0004d000;
	public static final int XACT_S_LAST						= 0x0004d009;
	public static final int XACT_E_ALREADYOTHERSINGLEPHASE	= 0x8004d000;
	public static final int XACT_E_CANTRETAIN				= 0x8004d001;
	public static final int XACT_E_COMMITFAILED				= 0x8004d002;
	public static final int XACT_E_COMMITPREVENTED			= 0x8004d003;
	public static final int XACT_E_HEURISTICABORT			= 0x8004d004;
	public static final int XACT_E_HEURISTICCOMMIT			= 0x8004d005;
	public static final int XACT_E_HEURISTICDAMAGE			= 0x8004d006;
	public static final int XACT_E_HEURISTICDANGER			= 0x8004d007;
	public static final int XACT_E_ISOLATIONLEVEL			= 0x8004d008;
	public static final int XACT_E_NOASYNC					= 0x8004d009;
	public static final int XACT_E_NOENLIST					= 0x8004d00a;
	public static final int XACT_E_NOISORETAIN				= 0x8004d00b;
	public static final int XACT_E_NORESOURCE				= 0x8004d00c;
	public static final int XACT_E_NOTCURRENT				= 0x8004d00d;
	public static final int XACT_E_NOTRANSACTION			= 0x8004d00e;
	public static final int XACT_E_NOTSUPPORTED				= 0x8004d00f;
	public static final int XACT_E_UNKNOWNRMGRID			= 0x8004d010;
	public static final int XACT_E_WRONGSTATE				= 0x8004d011;
	public static final int XACT_E_WRONGUOW					= 0x8004d012;
	public static final int XACT_E_XTIONEXISTS				= 0x8004d013;
	public static final int XACT_E_NOIMPORTOBJECT			= 0x8004d014;
	public static final int XACT_E_INVALIDCOOKIE			= 0x8004d015;
	public static final int XACT_E_INDOUBT					= 0x8004d016;
	public static final int XACT_E_NOTIMEOUT				= 0x8004d017;
	public static final int XACT_E_ALREADYINPROGRESS		= 0x8004d018;
	public static final int XACT_E_ABORTED					= 0x8004d019;
	public static final int XACT_E_LOGFULL					= 0x8004d01a;
	public static final int XACT_E_TMNOTAVAILABLE			= 0x8004d01b;
	public static final int XACT_E_CONNECTION_DOWN			= 0x8004d01c;
	public static final int XACT_E_CONNECTION_DENIED		= 0x8004d01d;
	public static final int XACT_E_REENLISTTIMEOUT			= 0x8004d01e;
	public static final int XACT_E_TIP_CONNECT_FAILED		= 0x8004d01f;
	public static final int XACT_E_TIP_PROTOCOL_ERROR		= 0x8004d020;
	public static final int XACT_E_TIP_PULL_FAILED			= 0x8004d021;
	public static final int XACT_E_DEST_TMNOTAVAILABLE		= 0x8004d022;
	public static final int XACT_E_CLERKNOTFOUND			= 0x8004d080;
	public static final int XACT_E_CLERKEXISTS				= 0x8004d081;
	public static final int XACT_E_RECOVERYINPROGRESS		= 0x8004d082;
	public static final int XACT_E_TRANSACTIONCLOSED		= 0x8004d083;
	public static final int XACT_E_INVALIDLSN				= 0x8004d084;
	public static final int XACT_E_REPLAYREQUEST			= 0x8004d085;
	public static final int XACT_S_ASYNC					= 0x0004d000;
	public static final int XACT_S_DEFECT					= 0x0004d001;
	public static final int XACT_S_READONLY					= 0x0004d002;
	public static final int XACT_S_SOMENORETAIN				= 0x0004d003;
	public static final int XACT_S_OKINFORM					= 0x0004d004;
	public static final int XACT_S_MADECHANGESCONTENT		= 0x0004d005;
	public static final int XACT_S_MADECHANGESINFORM		= 0x0004d006;
	public static final int XACT_S_ALLNORETAIN				= 0x0004d007;
	public static final int XACT_S_ABORTING					= 0x0004d008;
	public static final int XACT_S_SINGLEPHASE				= 0x0004d009;

	public static boolean valid(int value)
		{
		return ( XACT_S_FIRST <= value && value <= XACT_S_LAST ) || ( XACT_E_FIRST <= value && value <= XACT_E_LAST );
		}
	}
