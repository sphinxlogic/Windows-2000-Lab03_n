// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface winx {
	int XST_NULL = 0,
		XST_INCOMPLETE = 1,
		XST_CONNECTED = 2,
		XST_INIT1 = 3,
		XST_INIT2 = 4,
		XST_REQSENT = 5,
		XST_DATARCVD = 6,
		XST_POKESENT = 7,
		XST_POKEACKRCVD = 8,
		XST_EXECSENT = 9,
		XST_EXECACKRCVD = 10,
		XST_ADVSENT = 11,
		XST_UNADVSENT = 12,
		XST_ADVACKRCVD = 13,
		XST_UNADVACKRCVD = 14,
		XST_ADVDATASENT = 15,
		XST_ADVDATAACKRCVD = 16,
		XTYPF_NOBLOCK = 0x0002,
		XTYPF_NODATA = 0x0004,
		XTYPF_ACKREQ = 0x0008,
		XCLASS_MASK = 0xFC00,
		XCLASS_BOOL = 0x1000,
		XCLASS_DATA = 0x2000,
		XCLASS_FLAGS = 0x4000,
		XCLASS_NOTIFICATION = 0x8000,
		XTYP_ERROR = (0x0000|0x8000|0x0002),
		XTYP_ADVDATA = (0x0010|0x4000),
		XTYP_ADVREQ = (0x0020|0x2000|0x0002),
		XTYP_ADVSTART = (0x0030|0x1000),
		XTYP_ADVSTOP = (0x0040|0x8000),
		XTYP_EXECUTE = (0x0050|0x4000),
		XTYP_CONNECT = (0x0060|0x1000|0x0002),
		XTYP_CONNECT_CONFIRM = (0x0070|0x8000|0x0002),
		XTYP_XACT_COMPLETE = (0x0080|0x8000),
		XTYP_POKE = (0x0090|0x4000),
		XTYP_REGISTER = (0x00A0|0x8000|0x0002),
		XTYP_REQUEST = (0x00B0|0x2000),
		XTYP_DISCONNECT = (0x00C0|0x8000|0x0002),
		XTYP_UNREGISTER = (0x00D0|0x8000|0x0002),
		XTYP_WILDCONNECT = (0x00E0|0x2000|0x0002),
		XTYP_MASK = 0x00F0,
		XTYP_SHIFT = 4,
		XTYP_MONITOR = (0x00F0|0x8000|0x0002);

}
