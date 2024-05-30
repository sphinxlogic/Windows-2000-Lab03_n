// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface wink {
	int KEY_EVENT = 0x0001,
		KP_IV = 1,
		KP_SALT = 2,
		KP_PADDING = 3,
		KP_MODE = 4,
		KP_MODE_BITS = 5,
		KP_PERMISSIONS = 6,
		KP_ALGID = 7,
		KP_BLOCKLEN = 8,
		KEY_QUERY_VALUE = (0x0001),
		KEY_SET_VALUE = (0x0002),
		KEY_CREATE_SUB_KEY = (0x0004),
		KEY_ENUMERATE_SUB_KEYS = (0x0008),
		KEY_NOTIFY = (0x0010),
		KEY_CREATE_LINK = (0x0020),
		KF_EXTENDED = 0x0100,
		KF_DLGMODE = 0x0800,
		KF_MENUMODE = 0x1000,
		KF_ALTDOWN = 0x2000,
		KF_REPEAT = 0x4000,
		KF_UP = 0x8000,
		KLF_ACTIVATE = 0x00000001,
		KLF_SUBSTITUTE_OK = 0x00000002,
		KLF_UNLOADPREVIOUS = 0x00000004,
		KLF_REORDER = 0x00000008,
		KLF_REPLACELANG = 0x00000010,
		KLF_NOTELLSHELL = 0x00000080,
		KL_NAMELENGTH = 9,
		KEYEVENTF_EXTENDEDKEY = 0x0001,
		KEYEVENTF_KEYUP = 0x0002;

}
