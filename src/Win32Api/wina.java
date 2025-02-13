// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface wina {
	int APPCMD_CLIENTONLY = 0x00000010,
		APPCMD_FILTERINITS = 0x00000020,
		APPCMD_MASK = 0x00000FF0,
		APPCLASS_STANDARD = 0x00000000,
		APPCLASS_MASK = 0x0000000F,
		APPCLASS_MONITOR = 0x00000001,
		ATTR_INPUT = 0x00,
		ATTR_TARGET_CONVERTED = 0x01,
		ATTR_CONVERTED = 0x02,
		ATTR_TARGET_NOTCONVERTED = 0x03,
		ATTR_INPUT_ERROR = 0x04,
		AUXCAPS_CDAUDIO = 1,
		AUXCAPS_AUXIN = 2,
		AUXCAPS_VOLUME = 0x0001,
		AUXCAPS_LRVOLUME = 0x0002,
		ASYNCH = 0x80,
		ASYNC_MODE_COMPATIBILITY = 0x00000001,
		ASYNC_MODE_DEFAULT = 0x00000000,
		ACTIVEOBJECT_STRONG = 0x0,
		ACTIVEOBJECT_WEAK = 0x1,
		ABM_NEW = 0x00000000,
		ABM_REMOVE = 0x00000001,
		ABM_QUERYPOS = 0x00000002,
		ABM_SETPOS = 0x00000003,
		ABM_GETSTATE = 0x00000004,
		ABM_GETTASKBARPOS = 0x00000005,
		ABM_ACTIVATE = 0x00000006,
		ABM_GETAUTOHIDEBAR = 0x00000007,
		ABM_SETAUTOHIDEBAR = 0x00000008,
		ABM_WINDOWPOSCHANGED = 0x0000009,
		ABN_STATECHANGE = 0x0000000,
		ABN_POSCHANGED = 0x0000001,
		ABN_FULLSCREENAPP = 0x0000002,
		ABN_WINDOWARRANGE = 0x0000003,
		ABS_AUTOHIDE = 0x0000001,
		ABS_ALWAYSONTOP = 0x0000002,
		ABE_LEFT = 0,
		ABE_TOP = 1,
		ABE_RIGHT = 2,
		ABE_BOTTOM = 3,
		AC_LINE_OFFLINE = 0x00,
		AC_LINE_ONLINE = 0x01,
		AC_LINE_BACKUP_POWER = 0x02,
		AC_LINE_UNKNOWN = 0xFF,
		ALG_CLASS_ANY = (0),
		ALG_CLASS_SIGNATURE = (1<<13),
		ALG_CLASS_MSG_ENCRYPT = (2<<13),
		ALG_CLASS_DATA_ENCRYPT = (3<<13),
		ALG_CLASS_HASH = (4<<13),
		ALG_CLASS_KEY_EXCHANGE = (5<<13),
		ALG_TYPE_ANY = (0),
		ALG_TYPE_DSS = (1<<9),
		ALG_TYPE_RSA = (2<<9),
		ALG_TYPE_BLOCK = (3<<9),
		ALG_TYPE_STREAM = (4<<9),
		ALG_SID_ANY = (0),
		ALG_SID_RSA_ANY = 0,
		ALG_SID_RSA_PKCS = 1,
		ALG_SID_RSA_MSATWORK = 2,
		ALG_SID_RSA_ENTRUST = 3,
		ALG_SID_RSA_PGP = 4,
		ALG_SID_DSS_ANY = 0,
		ALG_SID_DSS_PKCS = 1,
		ALG_SID_DSS_DMS = 2,
		ALG_SID_DES = 1,
		ALG_SID_3DES = 3,
		ALG_SID_DESX = 4,
		ALG_SID_IDEA = 5,
		ALG_SID_CAST = 6,
		ALG_SID_SAFERSK64 = 7,
		ALD_SID_SAFERSK128 = 8,
		ALG_SID_RC2 = 2,
		ALG_SID_RC4 = 1,
		ALG_SID_SEAL = 2,
		ALG_SID_MD2 = 1,
		ALG_SID_MD4 = 2,
		ALG_SID_MD5 = 3,
		ALG_SID_SHA = 4,
		ALG_SID_MAC = 5,
		ALG_SID_RIPEMD = 6,
		ALG_SID_RIPEMD160 = 7,
		ALG_SID_SSL3SHAMD5 = 8,
		ALG_SID_EXAMPLE = 80,
		AT_KEYEXCHANGE = 1,
		AT_SIGNATURE = 2,
		ALTERNATE = 1,
		ASPECT_FILTERING = 0x0001,
		ABORTDOC = 2,
		ANTIALIASED_QUALITY = 4,
		ANSI_CHARSET = 0,
		ARABIC_CHARSET = 178,
		ABSOLUTE = 1,
		ANSI_FIXED_FONT = 11,
		ANSI_VAR_FONT = 12,
		AD_COUNTERCLOCKWISE = 1,
		AD_CLOCKWISE = 2,
		ASPECTX = 40,
		ASPECTY = 42,
		ASPECTXY = 44,
		ANYSIZE_ARRAY = 1,
		APPLICATION_ERROR_MASK = 0x20000000,
		ACCESS_SYSTEM_SECURITY = (0x01000000),
		ACL_REVISION = (2),
		ACL_REVISION1 = (1),
		ACL_REVISION2 = (2),
		ACL_REVISION3 = (3),
		ACCESS_ALLOWED_ACE_TYPE = (0x0),
		ACCESS_DENIED_ACE_TYPE = (0x1),
		ARW_BOTTOMLEFT = 0x0000,
		ARW_BOTTOMRIGHT = 0x0001,
		ARW_TOPLEFT = 0x0002,
		ARW_TOPRIGHT = 0x0003,
		ARW_STARTMASK = 0x0003,
		ARW_STARTRIGHT = 0x0001,
		ARW_STARTTOP = 0x0002,
		ARW_LEFT = 0x0000,
		ARW_RIGHT = 0x0000,
		ARW_UP = 0x0004,
		ARW_DOWN = 0x0004,
		ARW_HIDE = 0x0008,
		ARW_VALID = 0x000F,
		ATF_TIMEOUTON = 0x00000001,
		ATF_ONOFFFEEDBACK = 0x00000002,
		ACS_CENTER = 0x0001,
		ACS_TRANSPARENT = 0x0002,
		ACS_AUTOPLAY = 0x0004,
		ACS_TIMER = 0x0008,
		ACM_OPENA = (0x0400+100),
		ACM_OPENW = (0x0400+103),
		ACM_PLAY = (0x0400+101),
		ACM_STOP = (0x0400+102),
		ACN_START = 1,
		ACN_STOP = 2;

}
