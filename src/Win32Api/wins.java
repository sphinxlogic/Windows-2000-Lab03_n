// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface wins {
	int SIMULATED_FONTTYPE = 0x8000,
		SCREEN_FONTTYPE = 0x2000,
		ST_CONNECTED = 0x0001,
		ST_ADVISE = 0x0002,
		ST_ISLOCAL = 0x0004,
		ST_BLOCKED = 0x0008,
		ST_CLIENT = 0x0010,
		ST_TERMINATED = 0x0020,
		ST_INLIST = 0x0040,
		ST_BLOCKNEXT = 0x0080,
		ST_ISSELF = 0x0100,
		stc1 = 0x0440,
		stc2 = 0x0441,
		stc3 = 0x0442,
		stc4 = 0x0443,
		stc5 = 0x0444,
		stc6 = 0x0445,
		stc7 = 0x0446,
		stc8 = 0x0447,
		stc9 = 0x0448,
		stc10 = 0x0449,
		stc11 = 0x044a,
		stc12 = 0x044b,
		stc13 = 0x044c,
		stc14 = 0x044d,
		stc15 = 0x044e,
		stc16 = 0x044f,
		stc17 = 0x0450,
		stc18 = 0x0451,
		stc19 = 0x0452,
		stc20 = 0x0453,
		stc21 = 0x0454,
		stc22 = 0x0455,
		stc23 = 0x0456,
		stc24 = 0x0457,
		stc25 = 0x0458,
		stc26 = 0x0459,
		stc27 = 0x045a,
		stc28 = 0x045b,
		stc29 = 0x045c,
		stc30 = 0x045d,
		stc31 = 0x045e,
		stc32 = 0x045f,
		scr1 = 0x0490,
		scr2 = 0x0491,
		scr3 = 0x0492,
		scr4 = 0x0493,
		scr5 = 0x0494,
		scr6 = 0x0495,
		scr7 = 0x0496,
		scr8 = 0x0497,
		STYLE_DESCRIPTION_SIZE = 32,
		SCS_CAP_COMPSTR = 0x00000001,
		SCS_CAP_MAKEREAD = 0x00000002,
		SELECT_CAP_CONVERSION = 0x00000001,
		SELECT_CAP_SENTENCE = 0x00000002,
		SCS_SETSTR = (0x0001|0x0008),
		SCS_CHANGEATTR = (0x0002|0x0010),
		SCS_CHANGECLAUSE = (0x0004|0x0020),
		SOFTKEYBOARD_TYPE_T1 = 0x0001,
		SOFTKEYBOARD_TYPE_C1 = 0x0002,
		SND_SYNC = 0x0000,
		SND_ASYNC = 0x0001,
		SND_NODEFAULT = 0x0002,
		SND_MEMORY = 0x0004,
		SND_LOOP = 0x0008,
		SND_NOSTOP = 0x0010,
		SND_NOWAIT = 0x00002000,
		SND_ALIAS = 0x00010000,
		SND_ALIAS_ID = 0x00110000,
		SND_FILENAME = 0x00020000,
		SND_RESOURCE = 0x00040004,
		SND_PURGE = 0x0040,
		SND_APPLICATION = 0x0080,
		SND_ALIAS_START = 0,
		SEEK_SET = 0,
		SEEK_CUR = 1,
		SEEK_END = 2,
		SELECTDIB = 41,
		SC_SCREENSAVE = 0xF140,
		SO_CONNDATA = 0x7000,
		SO_CONNOPT = 0x7001,
		SO_DISCDATA = 0x7002,
		SO_DISCOPT = 0x7003,
		SO_CONNDATALEN = 0x7004,
		SO_CONNOPTLEN = 0x7005,
		SO_DISCDATALEN = 0x7006,
		SO_DISCOPTLEN = 0x7007,
		SO_OPENTYPE = 0x7008,
		SO_SYNCHRONOUS_ALERT = 0x10,
		SO_SYNCHRONOUS_NONALERT = 0x20,
		SO_MAXDG = 0x7009,
		SO_MAXPATHDG = 0x700A,
		SO_UPDATE_ACCEPT_CONTEXT = 0x700B,
		SO_CONNECT_TIME = 0x700C,
		SESSION_ESTABLISHED = 0x03,
		SESSION_ABORTED = 0x06,
		STGM_DIRECT = 0x00000000,
		STGM_TRANSACTED = 0x00010000,
		STGM_SIMPLE = 0x08000000,
		STGM_READ = 0x00000000,
		STGM_WRITE = 0x00000001,
		STGM_READWRITE = 0x00000002,
		STGM_SHARE_DENY_NONE = 0x00000040,
		STGM_SHARE_DENY_READ = 0x00000030,
		STGM_SHARE_DENY_WRITE = 0x00000020,
		STGM_SHARE_EXCLUSIVE = 0x00000010,
		STGM_PRIORITY = 0x00040000,
		STGM_DELETEONRELEASE = 0x04000000,
		STGM_NOSCRATCH = 0x00100000,
		STGM_CREATE = 0x00001000,
		STGM_CONVERT = 0x00020000,
		STGM_FAILIFTHERE = 0x00000000,
		STGM_NOSNAPSHOT = 0x00200000,
		STGTY_REPEAT = 0x00000100,
		STG_TOEND = 0xFFFFFFFF,
		STG_LAYOUT_SEQUENTIAL = 0x00000000,
		STG_LAYOUT_INTERLEAVED = 0x00000001,
		STDOLE_MAJORVERNUM = 0x1,
		STDOLE_MINORVERNUM = 0x0,
		STDOLE_LCID = 0x0000,
		STDOLE2_MAJORVERNUM = 0x2,
		STDOLE2_MINORVERNUM = 0x0,
		STDOLE2_LCID = 0x0000,
		SEC_WINNT_AUTH_IDENTITY_ANSI = 0x1,
		SEC_WINNT_AUTH_IDENTITY_UNICODE = 0x2,
		SE_ERR_FNF = 2,
		SE_ERR_PNF = 3,
		SE_ERR_ACCESSDENIED = 5,
		SE_ERR_OOM = 8,
		SE_ERR_DLLNOTFOUND = 32,
		SE_ERR_SHARE = 26,
		SE_ERR_ASSOCINCOMPLETE = 27,
		SE_ERR_DDETIMEOUT = 28,
		SE_ERR_DDEFAIL = 29,
		SE_ERR_DDEBUSY = 30,
		SE_ERR_NOASSOC = 31,
		SEE_MASK_CLASSNAME = 0x00000001,
		SEE_MASK_CLASSKEY = 0x00000003,
		SEE_MASK_IDLIST = 0x00000004,
		SEE_MASK_INVOKEIDLIST = 0x0000000c,
		SEE_MASK_ICON = 0x00000010,
		SEE_MASK_HOTKEY = 0x00000020,
		SEE_MASK_NOCLOSEPROCESS = 0x00000040,
		SEE_MASK_CONNECTNETDRV = 0x00000080,
		SEE_MASK_FLAG_DDEWAIT = 0x00000100,
		SEE_MASK_DOENVSUBST = 0x00000200,
		SEE_MASK_FLAG_NO_UI = 0x00000400,
		SEE_MASK_UNICODE = 0x00004000,
		SEE_MASK_NO_CONSOLE = 0x00008000,
		SEE_MASK_ASYNCOK = 0x00100000;
	long SHGFI_ICON = 0x000000100L,
		SHGFI_DISPLAYNAME = 0x000000200L,
		SHGFI_TYPENAME = 0x000000400L,
		SHGFI_ATTRIBUTES = 0x000000800L,
		SHGFI_ICONLOCATION = 0x000001000L,
		SHGFI_EXETYPE = 0x000002000L,
		SHGFI_SYSICONINDEX = 0x000004000L,
		SHGFI_LINKOVERLAY = 0x000008000L,
		SHGFI_SELECTED = 0x000010000L,
		SHGFI_LARGEICON = 0x000000000L,
		SHGFI_SMALLICON = 0x000000001L,
		SHGFI_OPENICON = 0x000000002L,
		SHGFI_SHELLICONSIZE = 0x000000004L,
		SHGFI_PIDL = 0x000000008L,
		SHGFI_USEFILEATTRIBUTES = 0x000000010L,
		SHGNLI_PIDL = 0x000000001L,
		SHGNLI_PREFIXNAME = 0x000000002L,
		SHGNLI_NOUNIQUE = 0x000000004L;
	int SECURITY_CONTEXT_TRACKING = 0x00040000,
		SECURITY_EFFECTIVE_ONLY = 0x00080000,
		SECURITY_SQOS_PRESENT = 0x00100000,
		SECURITY_VALID_SQOS_FLAGS = 0x001F0000,
		SP_SERIALCOMM = (0x00000001),
		SP_PARITY = (0x0001),
		SP_BAUD = (0x0002),
		SP_DATABITS = (0x0004),
		SP_STOPBITS = (0x0008),
		SP_HANDSHAKING = (0x0010),
		SP_PARITY_CHECK = (0x0020),
		SP_RLSD = (0x0040),
		STOPBITS_10 = (0x0001),
		STOPBITS_15 = (0x0002),
		STOPBITS_20 = (0x0004),
		SPACEPARITY = 4,
		SETXOFF = 1,
		SETXON = 2,
		SETRTS = 3,
		SETDTR = 5,
		SETBREAK = 8,
		S_QUEUEEMPTY = 0,
		S_THRESHOLD = 1,
		S_ALLTHRESHOLD = 2,
		S_NORMAL = 0,
		S_LEGATO = 1,
		S_STACCATO = 2,
		S_PERIOD512 = 0,
		S_PERIOD1024 = 1,
		S_PERIOD2048 = 2,
		S_PERIODVOICE = 3,
		S_WHITE512 = 4,
		S_WHITE1024 = 5,
		S_WHITE2048 = 6,
		S_WHITEVOICE = 7,
		S_SERDVNA = (-1),
		S_SEROFM = (-2),
		S_SERMACT = (-3),
		S_SERQFUL = (-4),
		S_SERBDNT = (-5),
		S_SERDLN = (-6),
		S_SERDCC = (-7),
		S_SERDTP = (-8),
		S_SERDVL = (-9),
		S_SERDMD = (-10),
		S_SERDSH = (-11),
		S_SERDPT = (-12),
		S_SERDFQ = (-13),
		S_SERDDR = (-14),
		S_SERDSR = (-15),
		S_SERDST = (-16),
		SCS_32BIT_BINARY = 0,
		SCS_DOS_BINARY = 1,
		SCS_WOW_BINARY = 2,
		SCS_PIF_BINARY = 3,
		SCS_POSIX_BINARY = 4,
		SCS_OS216_BINARY = 5,
		SEM_FAILCRITICALERRORS = 0x0001,
		SEM_NOGPFAULTERRORBOX = 0x0002,
		SEM_NOALIGNMENTFAULTEXCEPT = 0x0004,
		SEM_NOOPENFILEERRORBOX = 0x8000,
		SET_TAPE_MEDIA_INFORMATION = 0,
		SET_TAPE_DRIVE_INFORMATION = 1,
		STREAM_NORMAL_ATTRIBUTE = 0x00000000,
		STREAM_MODIFIED_WHEN_READ = 0x00000001,
		STREAM_CONTAINS_SECURITY = 0x00000002,
		STREAM_CONTAINS_PROPERTIES = 0x00000004,
		STARTF_USESHOWWINDOW = 0x00000001,
		STARTF_USESIZE = 0x00000002,
		STARTF_USEPOSITION = 0x00000004,
		STARTF_USECOUNTCHARS = 0x00000008,
		STARTF_USEFILLATTRIBUTE = 0x00000010,
		STARTF_RUNFULLSCREEN = 0x00000020,
		STARTF_FORCEONFEEDBACK = 0x00000040,
		STARTF_FORCEOFFFEEDBACK = 0x00000080,
		STARTF_USESTDHANDLES = 0x00000100,
		STARTF_USEHOTKEY = 0x00000200,
		SHUTDOWN_NORETRY = 0x00000001,
		SHIFT_PRESSED = 0x0010,
		SCROLLLOCK_ON = 0x0040,
		SIMPLEBLOB = 0x1,
		SEVERITY_SUCCESS = 0,
		SEVERITY_ERROR = 1,
		STG_E_INVALIDFUNCTION = 0x80030001,
		STG_E_FILENOTFOUND = 0x80030002,
		STG_E_PATHNOTFOUND = 0x80030003,
		STG_E_TOOMANYOPENFILES = 0x80030004,
		STG_E_ACCESSDENIED = 0x80030005,
		STG_E_INVALIDHANDLE = 0x80030006,
		STG_E_INSUFFICIENTMEMORY = 0x80030008,
		STG_E_INVALIDPOINTER = 0x80030009,
		STG_E_NOMOREFILES = 0x80030012,
		STG_E_DISKISWRITEPROTECTED = 0x80030013,
		STG_E_SEEKERROR = 0x80030019,
		STG_E_WRITEFAULT = 0x8003001D,
		STG_E_READFAULT = 0x8003001E,
		STG_E_SHAREVIOLATION = 0x80030020,
		STG_E_LOCKVIOLATION = 0x80030021,
		STG_E_FILEALREADYEXISTS = 0x80030050,
		STG_E_INVALIDPARAMETER = 0x80030057,
		STG_E_MEDIUMFULL = 0x80030070,
		STG_E_PROPSETMISMATCHED = 0x800300F0,
		STG_E_ABNORMALAPIEXIT = 0x800300FA,
		STG_E_INVALIDHEADER = 0x800300FB,
		STG_E_INVALIDNAME = 0x800300FC,
		STG_E_UNKNOWN = 0x800300FD,
		STG_E_UNIMPLEMENTEDFUNCTION = 0x800300FE,
		STG_E_INVALIDFLAG = 0x800300FF,
		STG_E_INUSE = 0x80030100,
		STG_E_NOTCURRENT = 0x80030101,
		STG_E_REVERTED = 0x80030102,
		STG_E_CANTSAVE = 0x80030103,
		STG_E_OLDFORMAT = 0x80030104,
		STG_E_OLDDLL = 0x80030105,
		STG_E_SHAREREQUIRED = 0x80030106,
		STG_E_NOTFILEBASEDSTORAGE = 0x80030107,
		STG_E_EXTANTMARSHALLINGS = 0x80030108,
		STG_E_DOCFILECORRUPT = 0x80030109,
		STG_E_BADBASEADDRESS = 0x80030110,
		STG_E_INCOMPLETE = 0x80030201,
		STG_E_TERMINATED = 0x80030202,
		STG_S_CONVERTED = 0x00030200,
		STG_S_BLOCK = 0x00030201,
		STG_S_RETRYNOW = 0x00030202,
		STG_S_MONITORING = 0x00030203,
		SIMPLEREGION = 2,
		STRETCH_ANDSCANS = 1,
		STRETCH_ORSCANS = 2,
		STRETCH_DELETESCANS = 3,
		STRETCH_HALFTONE = 4,
		SETCOLORTABLE = 4,
		SETABORTPROC = 9,
		STARTDOC = 10,
		SETCOPYCOUNT = 17,
		SELECTPAPERSOURCE = 18,
		SETLINECAP = 21,
		SETLINEJOIN = 22,
		SETMITERLIMIT = 23,
		SETDIBSCALING = 32,
		SETKERNTRACK = 770,
		SETALLJUSTVALUES = 771,
		SETCHARSET = 772,
		STRETCHBLT = 2048,
		SAVE_CTM = 4101,
		SET_ARC_DIRECTION = 4102,
		SET_BACKGROUND_COLOR = 4103,
		SET_POLY_MODE = 4104,
		SET_SCREEN_ANGLE = 4105,
		SET_SPREAD = 4106,
		SET_CLIP_BOX = 4108,
		SET_BOUNDS = 4109,
		SET_MIRROR_MODE = 4110,
		SP_NOTREPORTED = 0x4000,
		SP_ERROR = (-1),
		SP_APPABORT = (-2),
		SP_USERABORT = (-3),
		SP_OUTOFDISK = (-4),
		SP_OUTOFMEMORY = (-5),
		SYMBOL_CHARSET = 2,
		SHIFTJIS_CHARSET = 128,
		SYSTEM_FONT = 13,
		SYSTEM_FIXED_FONT = 16,
		STOCK_LAST = 17;
	// STOCK_LAST = 16;
	int SIZEPALETTE = 104,
		SCALINGFACTORX = 114,
		SCALINGFACTORY = 115,
		SYSPAL_ERROR = 0,
		SYSPAL_STATIC = 1,
		SYSPAL_NOSTATIC = 2,
		SORT_STRINGSORT = 0x00001000,
		SUBLANG_NEUTRAL = 0x00,
		SUBLANG_DEFAULT = 0x01,
		SUBLANG_SYS_DEFAULT = 0x02,
		SUBLANG_ARABIC_SAUDI_ARABIA = 0x01,
		SUBLANG_ARABIC_IRAQ = 0x02,
		SUBLANG_ARABIC_EGYPT = 0x03,
		SUBLANG_ARABIC_LIBYA = 0x04,
		SUBLANG_ARABIC_ALGERIA = 0x05,
		SUBLANG_ARABIC_MOROCCO = 0x06,
		SUBLANG_ARABIC_TUNISIA = 0x07,
		SUBLANG_ARABIC_OMAN = 0x08,
		SUBLANG_ARABIC_YEMEN = 0x09,
		SUBLANG_ARABIC_SYRIA = 0x0a,
		SUBLANG_ARABIC_JORDAN = 0x0b,
		SUBLANG_ARABIC_LEBANON = 0x0c,
		SUBLANG_ARABIC_KUWAIT = 0x0d,
		SUBLANG_ARABIC_UAE = 0x0e,
		SUBLANG_ARABIC_BAHRAIN = 0x0f,
		SUBLANG_ARABIC_QATAR = 0x10,
		SUBLANG_CHINESE_TRADITIONAL = 0x01,
		SUBLANG_CHINESE_SIMPLIFIED = 0x02,
		SUBLANG_CHINESE_HONGKONG = 0x03,
		SUBLANG_CHINESE_SINGAPORE = 0x04,
		SUBLANG_DUTCH = 0x01,
		SUBLANG_DUTCH_BELGIAN = 0x02,
		SUBLANG_ENGLISH_US = 0x01,
		SUBLANG_ENGLISH_UK = 0x02,
		SUBLANG_ENGLISH_AUS = 0x03,
		SUBLANG_ENGLISH_CAN = 0x04,
		SUBLANG_ENGLISH_NZ = 0x05,
		SUBLANG_ENGLISH_EIRE = 0x06,
		SUBLANG_ENGLISH_SOUTH_AFRICA = 0x07,
		SUBLANG_ENGLISH_JAMAICA = 0x08,
		SUBLANG_ENGLISH_CARIBBEAN = 0x09,
		SUBLANG_ENGLISH_BELIZE = 0x0a,
		SUBLANG_ENGLISH_TRINIDAD = 0x0b,
		SUBLANG_FRENCH = 0x01,
		SUBLANG_FRENCH_BELGIAN = 0x02,
		SUBLANG_FRENCH_CANADIAN = 0x03,
		SUBLANG_FRENCH_SWISS = 0x04,
		SUBLANG_FRENCH_LUXEMBOURG = 0x05,
		SUBLANG_GERMAN = 0x01,
		SUBLANG_GERMAN_SWISS = 0x02,
		SUBLANG_GERMAN_AUSTRIAN = 0x03,
		SUBLANG_GERMAN_LUXEMBOURG = 0x04,
		SUBLANG_GERMAN_LIECHTENSTEIN = 0x05,
		SUBLANG_ITALIAN = 0x01,
		SUBLANG_ITALIAN_SWISS = 0x02,
		SUBLANG_KOREAN = 0x01,
		SUBLANG_KOREAN_JOHAB = 0x02,
		SUBLANG_NORWEGIAN_BOKMAL = 0x01,
		SUBLANG_NORWEGIAN_NYNORSK = 0x02,
		SUBLANG_PORTUGUESE = 0x02,
		SUBLANG_PORTUGUESE_BRAZILIAN = 0x01,
		SUBLANG_SERBIAN_LATIN = 0x02,
		SUBLANG_SERBIAN_CYRILLIC = 0x03,
		SUBLANG_SPANISH = 0x01,
		SUBLANG_SPANISH_MEXICAN = 0x02,
		SUBLANG_SPANISH_MODERN = 0x03,
		SUBLANG_SPANISH_GUATEMALA = 0x04,
		SUBLANG_SPANISH_COSTA_RICA = 0x05,
		SUBLANG_SPANISH_PANAMA = 0x06,
		SUBLANG_SPANISH_DOMINICAN_REPUBLIC = 0x07,
		SUBLANG_SPANISH_VENEZUELA = 0x08,
		SUBLANG_SPANISH_COLOMBIA = 0x09,
		SUBLANG_SPANISH_PERU = 0x0a,
		SUBLANG_SPANISH_ARGENTINA = 0x0b,
		SUBLANG_SPANISH_ECUADOR = 0x0c,
		SUBLANG_SPANISH_CHILE = 0x0d,
		SUBLANG_SPANISH_URUGUAY = 0x0e,
		SUBLANG_SPANISH_PARAGUAY = 0x0f,
		SUBLANG_SPANISH_BOLIVIA = 0x10,
		SUBLANG_SPANISH_EL_SALVADOR = 0x11,
		SUBLANG_SPANISH_HONDURAS = 0x12,
		SUBLANG_SPANISH_NICARAGUA = 0x13,
		SUBLANG_SPANISH_PUERTO_RICO = 0x14,
		SUBLANG_SWEDISH = 0x01,
		SUBLANG_SWEDISH_FINLAND = 0x02,
		SORT_DEFAULT = 0x0,
		SORT_JAPANESE_XJIS = 0x0,
		SORT_JAPANESE_UNICODE = 0x1,
		SORT_CHINESE_BIG5 = 0x0,
		SORT_CHINESE_PRCP = 0x0,
		SORT_CHINESE_UNICODE = 0x1,
		SORT_CHINESE_PRC = 0x2,
		SORT_KOREAN_KSC = 0x0,
		SORT_KOREAN_UNICODE = 0x1,
		SORT_GERMAN_PHONE_BOOK = 0x1,
		STATUS_WAIT_0 = (0x00000000),
		STATUS_ABANDONED_WAIT_0 = (0x00000080),
		STATUS_USER_APC = (0x000000C0),
		STATUS_TIMEOUT = (0x00000102),
		STATUS_PENDING = (0x00000103),
		STATUS_SEGMENT_NOTIFICATION = (0x40000005),
		STATUS_GUARD_PAGE_VIOLATION = (0x80000001),
		STATUS_DATATYPE_MISALIGNMENT = (0x80000002),
		STATUS_BREAKPOINT = (0x80000003),
		STATUS_SINGLE_STEP = (0x80000004),
		STATUS_ACCESS_VIOLATION = (0xC0000005),
		STATUS_IN_PAGE_ERROR = (0xC0000006),
		STATUS_INVALID_HANDLE = (0xC0000008),
		STATUS_NO_MEMORY = (0xC0000017),
		STATUS_ILLEGAL_INSTRUCTION = (0xC000001D),
		STATUS_NONCONTINUABLE_EXCEPTION = (0xC0000025),
		STATUS_INVALID_DISPOSITION = (0xC0000026),
		STATUS_ARRAY_BOUNDS_EXCEEDED = (0xC000008C),
		STATUS_FLOAT_DENORMAL_OPERAND = (0xC000008D),
		STATUS_FLOAT_DIVIDE_BY_ZERO = (0xC000008E),
		STATUS_FLOAT_INEXACT_RESULT = (0xC000008F),
		STATUS_FLOAT_INVALID_OPERATION = (0xC0000090),
		STATUS_FLOAT_OVERFLOW = (0xC0000091),
		STATUS_FLOAT_STACK_CHECK = (0xC0000092),
		STATUS_FLOAT_UNDERFLOW = (0xC0000093),
		STATUS_INTEGER_DIVIDE_BY_ZERO = (0xC0000094),
		STATUS_INTEGER_OVERFLOW = (0xC0000095),
		STATUS_PRIVILEGED_INSTRUCTION = (0xC0000096),
		STATUS_STACK_OVERFLOW = (0xC00000FD),
		STATUS_CONTROL_C_EXIT = (0xC000013A),
		SIZE_OF_80387_REGISTERS = 80,
		SEMAPHORE_MODIFY_STATE = 0x0002,
		SECTION_QUERY = 0x0001,
		SECTION_MAP_WRITE = 0x0002,
		SECTION_MAP_READ = 0x0004,
		SECTION_MAP_EXECUTE = 0x0008,
		SECTION_EXTEND_SIZE = 0x0010,
		SEC_FILE = 0x800000,
		SEC_IMAGE = 0x1000000,
		SEC_RESERVE = 0x4000000,
		SEC_COMMIT = 0x8000000,
		SEC_NOCACHE = 0x10000000,
		SYNCHRONIZE = (0x00100000),
		STANDARD_RIGHTS_REQUIRED = (0x000F0000),
		STANDARD_RIGHTS_READ = ((0x00020000)),
		STANDARD_RIGHTS_WRITE = ((0x00020000)),
		STANDARD_RIGHTS_EXECUTE = ((0x00020000)),
		STANDARD_RIGHTS_ALL = (0x001F0000),
		SPECIFIC_RIGHTS_ALL = (0x0000FFFF),
		SID_REVISION = (1),
		SID_MAX_SUB_AUTHORITIES = (15),
		SID_RECOMMENDED_SUB_AUTHORITIES = (1),
		SECURITY_NULL_RID = (0x00000000),
		SECURITY_WORLD_RID = (0x00000000),
		SECURITY_LOCAL_RID = (0X00000000),
		SECURITY_CREATOR_OWNER_RID = (0x00000000),
		SECURITY_CREATOR_GROUP_RID = (0x00000001),
		SECURITY_CREATOR_OWNER_SERVER_RID = (0x00000002),
		SECURITY_CREATOR_GROUP_SERVER_RID = (0x00000003),
		SECURITY_DIALUP_RID = (0x00000001),
		SECURITY_NETWORK_RID = (0x00000002),
		SECURITY_BATCH_RID = (0x00000003),
		SECURITY_INTERACTIVE_RID = (0x00000004),
		SECURITY_SERVICE_RID = (0x00000006),
		SECURITY_ANONYMOUS_LOGON_RID = (0x00000007),
		SECURITY_PROXY_RID = (0x00000008),
		SECURITY_SERVER_LOGON_RID = (0x00000009),
		SECURITY_LOGON_IDS_RID = (0x00000005),
		SECURITY_LOGON_IDS_RID_COUNT = (3),
		SECURITY_LOCAL_SYSTEM_RID = (0x00000012),
		SECURITY_NT_NON_UNIQUE = (0x00000015),
		SECURITY_BUILTIN_DOMAIN_RID = (0x00000020),
		SE_GROUP_MANDATORY = (0x00000001),
		SE_GROUP_ENABLED_BY_DEFAULT = (0x00000002),
		SE_GROUP_ENABLED = (0x00000004),
		SE_GROUP_OWNER = (0x00000008),
		SE_GROUP_LOGON_ID = (0xC0000000),
		SYSTEM_AUDIT_ACE_TYPE = (0x2),
		SYSTEM_ALARM_ACE_TYPE = (0x3),
		SUCCESSFUL_ACCESS_ACE_FLAG = (0x40),
		SECURITY_DESCRIPTOR_REVISION = (1),
		SECURITY_DESCRIPTOR_REVISION1 = (1),
		SECURITY_DESCRIPTOR_MIN_LENGTH = (20),
		SE_OWNER_DEFAULTED = (0x0001),
		SE_GROUP_DEFAULTED = (0x0002),
		SE_DACL_PRESENT = (0x0004),
		SE_DACL_DEFAULTED = (0x0008),
		SE_SACL_PRESENT = (0x0010),
		SE_SACL_DEFAULTED = (0x0020),
		SE_SELF_RELATIVE = (0x8000),
		SE_PRIVILEGE_ENABLED_BY_DEFAULT = (0x00000001),
		SE_PRIVILEGE_ENABLED = (0x00000002),
		SE_PRIVILEGE_USED_FOR_ACCESS = (0x80000000);
	boolean SECURITY_DYNAMIC_TRACKING = (true),
		SECURITY_STATIC_TRACKING = (false);
	int SACL_SECURITY_INFORMATION = (0X00000008),
		SIZEOF_RFPO_DATA = 16,
		SERVICE_KERNEL_DRIVER = 0x00000001,
		SERVICE_FILE_SYSTEM_DRIVER = 0x00000002,
		SERVICE_ADAPTER = 0x00000004,
		SERVICE_RECOGNIZER_DRIVER = 0x00000008,
		SERVICE_WIN32_OWN_PROCESS = 0x00000010,
		SERVICE_WIN32_SHARE_PROCESS = 0x00000020,
		SERVICE_INTERACTIVE_PROCESS = 0x00000100,
		SERVICE_BOOT_START = 0x00000000,
		SERVICE_SYSTEM_START = 0x00000001,
		SERVICE_AUTO_START = 0x00000002,
		SERVICE_DEMAND_START = 0x00000003,
		SERVICE_DISABLED = 0x00000004,
		SERVICE_ERROR_IGNORE = 0x00000000,
		SERVICE_ERROR_NORMAL = 0x00000001,
		SERVICE_ERROR_SEVERE = 0x00000002,
		SERVICE_ERROR_CRITICAL = 0x00000003,
		SERVER_ACCESS_ADMINISTER = 0x00000001,
		SERVER_ACCESS_ENUMERATE = 0x00000002;
	char SC_GROUP_IDENTIFIERW = '+',
		SC_GROUP_IDENTIFIERA = '+';
	int SERVICE_NO_CHANGE = 0xffffffff,
		SERVICE_ACTIVE = 0x00000001,
		SERVICE_INACTIVE = 0x00000002,
		SERVICE_CONTROL_STOP = 0x00000001,
		SERVICE_CONTROL_PAUSE = 0x00000002,
		SERVICE_CONTROL_CONTINUE = 0x00000003,
		SERVICE_CONTROL_INTERROGATE = 0x00000004,
		SERVICE_CONTROL_SHUTDOWN = 0x00000005,
		SERVICE_STOPPED = 0x00000001,
		SERVICE_START_PENDING = 0x00000002,
		SERVICE_STOP_PENDING = 0x00000003,
		SERVICE_RUNNING = 0x00000004,
		SERVICE_CONTINUE_PENDING = 0x00000005,
		SERVICE_PAUSE_PENDING = 0x00000006,
		SERVICE_PAUSED = 0x00000007,
		SERVICE_ACCEPT_STOP = 0x00000001,
		SERVICE_ACCEPT_PAUSE_CONTINUE = 0x00000002,
		SERVICE_ACCEPT_SHUTDOWN = 0x00000004,
		SC_MANAGER_CONNECT = 0x0001,
		SC_MANAGER_CREATE_SERVICE = 0x0002,
		SC_MANAGER_ENUMERATE_SERVICE = 0x0004,
		SC_MANAGER_LOCK = 0x0008,
		SC_MANAGER_QUERY_LOCK_STATUS = 0x0010,
		SC_MANAGER_MODIFY_BOOT_CONFIG = 0x0020,
		SERVICE_QUERY_CONFIG = 0x0001,
		SERVICE_CHANGE_CONFIG = 0x0002,
		SERVICE_QUERY_STATUS = 0x0004,
		SERVICE_ENUMERATE_DEPENDENTS = 0x0008,
		SERVICE_START = 0x0010,
		SERVICE_STOP = 0x0020,
		SERVICE_PAUSE_CONTINUE = 0x0040,
		SERVICE_INTERROGATE = 0x0080,
		SERVICE_USER_DEFINED_CONTROL = 0x0100,
		SB_HORZ = 0,
		SB_VERT = 1,
		SB_CTL = 2,
		SB_BOTH = 3,
		SB_LINEUP = 0,
		SB_LINELEFT = 0,
		SB_LINEDOWN = 1,
		SB_LINERIGHT = 1,
		SB_PAGEUP = 2,
		SB_PAGELEFT = 2,
		SB_PAGEDOWN = 3,
		SB_PAGERIGHT = 3,
		SB_THUMBPOSITION = 4,
		SB_THUMBTRACK = 5,
		SB_TOP = 6,
		SB_LEFT = 6,
		SB_BOTTOM = 7,
		SB_RIGHT = 7,
		SB_ENDSCROLL = 8,
		SW_HIDE = 0,
		SW_SHOWNORMAL = 1,
		SW_NORMAL = 1,
		SW_SHOWMINIMIZED = 2,
		SW_SHOWMAXIMIZED = 3,
		SW_MAXIMIZE = 3,
		SW_SHOWNOACTIVATE = 4,
		SW_SHOW = 5,
		SW_MINIMIZE = 6,
		SW_SHOWMINNOACTIVE = 7,
		SW_SHOWNA = 8,
		SW_RESTORE = 9,
		SW_SHOWDEFAULT = 10,
		SW_MAX = 10,
		SHOW_OPENWINDOW = 1,
		SHOW_ICONWINDOW = 2,
		SHOW_FULLSCREEN = 3,
		SHOW_OPENNOACTIVATE = 4,
		SW_PARENTCLOSING = 1,
		SW_OTHERZOOM = 2,
		SW_PARENTOPENING = 3,
		SW_OTHERUNZOOM = 4,
		ST_BEGINSWP = 0,
		ST_ENDSWP = 1,
		SMTO_NORMAL = 0x0000,
		SMTO_BLOCK = 0x0001,
		SMTO_ABORTIFHUNG = 0x0002,
		SIZE_RESTORED = 0,
		SIZE_MINIMIZED = 1,
		SIZE_MAXIMIZED = 2,
		SIZE_MAXSHOW = 3,
		SIZE_MAXHIDE = 4,
		SIZENORMAL = 0,
		SIZEICONIC = 1,
		SIZEFULLSCREEN = 2,
		SIZEZOOMSHOW = 3,
		SIZEZOOMHIDE = 4,
		SWP_NOSIZE = 0x0001,
		SWP_NOMOVE = 0x0002,
		SWP_NOZORDER = 0x0004,
		SWP_NOREDRAW = 0x0008,
		SWP_NOACTIVATE = 0x0010,
		SWP_FRAMECHANGED = 0x0020,
		SWP_SHOWWINDOW = 0x0040,
		SWP_HIDEWINDOW = 0x0080,
		SWP_NOCOPYBITS = 0x0100,
		SWP_NOOWNERZORDER = 0x0200,
		SWP_NOSENDCHANGING = 0x0400,
		SWP_DRAWFRAME = 0x0020,
		SWP_NOREPOSITION = 0x0200,
		SWP_DEFERERASE = 0x2000,
		SWP_ASYNCWINDOWPOS = 0x4000,
		SM_CXSCREEN = 0,
		SM_CYSCREEN = 1,
		SM_CXVSCROLL = 2,
		SM_CYHSCROLL = 3,
		SM_CYCAPTION = 4,
		SM_CXBORDER = 5,
		SM_CYBORDER = 6,
		SM_CXDLGFRAME = 7,
		SM_CYDLGFRAME = 8,
		SM_CYVTHUMB = 9,
		SM_CXHTHUMB = 10,
		SM_CXICON = 11,
		SM_CYICON = 12,
		SM_CXCURSOR = 13,
		SM_CYCURSOR = 14,
		SM_CYMENU = 15,
		SM_CXFULLSCREEN = 16,
		SM_CYFULLSCREEN = 17,
		SM_CYKANJIWINDOW = 18,
		SM_MOUSEPRESENT = 19,
		SM_CYVSCROLL = 20,
		SM_CXHSCROLL = 21,
		SM_DEBUG = 22,
		SM_SWAPBUTTON = 23,
		SM_RESERVED1 = 24,
		SM_RESERVED2 = 25,
		SM_RESERVED3 = 26,
		SM_RESERVED4 = 27,
		SM_CXMIN = 28,
		SM_CYMIN = 29,
		SM_CXSIZE = 30,
		SM_CYSIZE = 31,
		SM_CXFRAME = 32,
		SM_CYFRAME = 33,
		SM_CXMINTRACK = 34,
		SM_CYMINTRACK = 35,
		SM_CXDOUBLECLK = 36,
		SM_CYDOUBLECLK = 37,
		SM_CXICONSPACING = 38,
		SM_CYICONSPACING = 39,
		SM_MENUDROPALIGNMENT = 40,
		SM_PENWINDOWS = 41,
		SM_DBCSENABLED = 42,
		SM_CMOUSEBUTTONS = 43,
		SM_CXFIXEDFRAME = 7,
		SM_CYFIXEDFRAME = 8,
		SM_CXSIZEFRAME = 32,
		SM_CYSIZEFRAME = 33,
		SM_SECURE = 44,
		SM_CXEDGE = 45,
		SM_CYEDGE = 46,
		SM_CXMINSPACING = 47,
		SM_CYMINSPACING = 48,
		SM_CXSMICON = 49,
		SM_CYSMICON = 50,
		SM_CYSMCAPTION = 51,
		SM_CXSMSIZE = 52,
		SM_CYSMSIZE = 53,
		SM_CXMENUSIZE = 54,
		SM_CYMENUSIZE = 55,
		SM_ARRANGE = 56,
		SM_CXMINIMIZED = 57,
		SM_CYMINIMIZED = 58,
		SM_CXMAXTRACK = 59,
		SM_CYMAXTRACK = 60,
		SM_CXMAXIMIZED = 61,
		SM_CYMAXIMIZED = 62,
		SM_NETWORK = 63,
		SM_CLEANBOOT = 67,
		SM_CXDRAG = 68,
		SM_CYDRAG = 69,
		SM_SHOWSOUNDS = 70,
		SM_CXMENUCHECK = 71,
		SM_CYMENUCHECK = 72,
		SM_SLOWMACHINE = 73,
		SM_MIDEASTENABLED = 74,
		SM_MOUSEWHEELPRESENT = 75,
	        SM_CMETRICS = 76;
	int SW_SCROLLCHILDREN = 0x0001,
		SW_INVALIDATE = 0x0002,
		SW_ERASE = 0x0004,
		SC_SIZE = 0xF000,
		SC_MOVE = 0xF010,
		SC_MINIMIZE = 0xF020,
		SC_MAXIMIZE = 0xF030,
		SC_NEXTWINDOW = 0xF040,
		SC_PREVWINDOW = 0xF050,
		SC_CLOSE = 0xF060,
		SC_VSCROLL = 0xF070,
		SC_HSCROLL = 0xF080,
		SC_MOUSEMENU = 0xF090,
		SC_KEYMENU = 0xF100,
		SC_ARRANGE = 0xF110,
		SC_RESTORE = 0xF120,
		SC_TASKLIST = 0xF130,
		SC_HOTKEY = 0xF150,
		SC_DEFAULT = 0xF160,
		SC_MONITORPOWER = 0xF170,
		SC_CONTEXTHELP = 0xF180,
		SC_SEPARATOR = 0xF00F,
		SC_ICON = 0xF020,
		SC_ZOOM = 0xF030,
		SS_LEFT = 0x00000000,
		SS_CENTER = 0x00000001,
		SS_RIGHT = 0x00000002,
		SS_ICON = 0x00000003,
		SS_BLACKRECT = 0x00000004,
		SS_GRAYRECT = 0x00000005,
		SS_WHITERECT = 0x00000006,
		SS_BLACKFRAME = 0x00000007,
		SS_GRAYFRAME = 0x00000008,
		SS_WHITEFRAME = 0x00000009,
		SS_USERITEM = 0x0000000A,
		SS_SIMPLE = 0x0000000B,
		SS_LEFTNOWORDWRAP = 0x0000000C,
		SS_OWNERDRAW = 0x0000000D,
		SS_BITMAP = 0x0000000E,
		SS_ENHMETAFILE = 0x0000000F,
		SS_ETCHEDHORZ = 0x00000010,
		SS_ETCHEDVERT = 0x00000011,
		SS_ETCHEDFRAME = 0x00000012,
		SS_TYPEMASK = 0x0000001F,
		SS_NOPREFIX = 0x00000080,
		SS_NOTIFY = 0x00000100,
		SS_CENTERIMAGE = 0x00000200,
		SS_RIGHTJUST = 0x00000400,
		SS_REALSIZEIMAGE = 0x00000800,
		SS_SUNKEN = 0x00001000,
		SS_ENDELLIPSIS = 0x00004000,
		SS_PATHELLIPSIS = 0x00008000,
		SS_WORDELLIPSIS = 0x0000C000,
		SS_ELLIPSISMASK = 0x0000C000,
		STM_SETICON = 0x0170,
		STM_GETICON = 0x0171,
		STM_SETIMAGE = 0x0172,
		STM_GETIMAGE = 0x0173,
		STN_CLICKED = 0,
		STN_DBLCLK = 1,
		STN_ENABLE = 2,
		STN_DISABLE = 3,
		STM_MSGMAX = 0x0174,
		SBS_HORZ = 0x0000,
		SBS_VERT = 0x0001,
		SBS_TOPALIGN = 0x0002,
		SBS_LEFTALIGN = 0x0002,
		SBS_BOTTOMALIGN = 0x0004,
		SBS_RIGHTALIGN = 0x0004,
		SBS_SIZEBOXTOPLEFTALIGN = 0x0002,
		SBS_SIZEBOXBOTTOMRIGHTALIGN = 0x0004,
		SBS_SIZEBOX = 0x0008,
		SBS_SIZEGRIP = 0x0010,
		SBM_SETPOS = 0x00E0,
		SBM_GETPOS = 0x00E1,
		SBM_SETRANGE = 0x00E2,
		SBM_SETRANGEREDRAW = 0x00E6,
		SBM_GETRANGE = 0x00E3,
		SBM_ENABLE_ARROWS = 0x00E4,
		SBM_SETSCROLLINFO = 0x00E9,
		SBM_GETSCROLLINFO = 0x00EA,
		SIF_RANGE = 0x0001,
		SIF_PAGE = 0x0002,
		SIF_POS = 0x0004,
		SIF_DISABLENOSCROLL = 0x0008,
		SIF_TRACKPOS = 0x0010,
		SIF_ALL = (0x0001|0x0002|0x0004|0x0010),
		SPI_GETBEEP = 1,
		SPI_SETBEEP = 2,
		SPI_GETMOUSE = 3,
		SPI_SETMOUSE = 4,
		SPI_GETBORDER = 5,
		SPI_SETBORDER = 6,
		SPI_GETKEYBOARDSPEED = 10,
		SPI_SETKEYBOARDSPEED = 11,
		SPI_LANGDRIVER = 12,
		SPI_ICONHORIZONTALSPACING = 13,
		SPI_GETSCREENSAVETIMEOUT = 14,
		SPI_SETSCREENSAVETIMEOUT = 15,
		SPI_GETSCREENSAVEACTIVE = 16,
		SPI_SETSCREENSAVEACTIVE = 17,
		SPI_GETGRIDGRANULARITY = 18,
		SPI_SETGRIDGRANULARITY = 19,
		SPI_SETDESKWALLPAPER = 20,
		SPI_SETDESKPATTERN = 21,
		SPI_GETKEYBOARDDELAY = 22,
		SPI_SETKEYBOARDDELAY = 23,
		SPI_ICONVERTICALSPACING = 24,
		SPI_GETICONTITLEWRAP = 25,
		SPI_SETICONTITLEWRAP = 26,
		SPI_GETMENUDROPALIGNMENT = 27,
		SPI_SETMENUDROPALIGNMENT = 28,
		SPI_SETDOUBLECLKWIDTH = 29,
		SPI_SETDOUBLECLKHEIGHT = 30,
		SPI_GETICONTITLELOGFONT = 31,
		SPI_SETDOUBLECLICKTIME = 32,
		SPI_SETMOUSEBUTTONSWAP = 33,
		SPI_SETICONTITLELOGFONT = 34,
		SPI_GETFASTTASKSWITCH = 35,
		SPI_SETFASTTASKSWITCH = 36,
		SPI_SETDRAGFULLWINDOWS = 37,
		SPI_GETDRAGFULLWINDOWS = 38,
		SPI_GETNONCLIENTMETRICS = 41,
		SPI_SETNONCLIENTMETRICS = 42,
		SPI_GETMINIMIZEDMETRICS = 43,
		SPI_SETMINIMIZEDMETRICS = 44,
		SPI_GETICONMETRICS = 45,
		SPI_SETICONMETRICS = 46,
		SPI_SETWORKAREA = 47,
		SPI_GETWORKAREA = 48,
		SPI_SETPENWINDOWS = 49,
		SPI_GETHIGHCONTRAST = 66,
		SPI_SETHIGHCONTRAST = 67,
		SPI_GETKEYBOARDPREF = 68,
		SPI_SETKEYBOARDPREF = 69,
		SPI_GETSCREENREADER = 70,
		SPI_SETSCREENREADER = 71,
		SPI_GETANIMATION = 72,
		SPI_SETANIMATION = 73,
		SPI_GETFONTSMOOTHING = 74,
		SPI_SETFONTSMOOTHING = 75,
		SPI_SETDRAGWIDTH = 76,
		SPI_SETDRAGHEIGHT = 77,
		SPI_SETHANDHELD = 78,
		SPI_GETLOWPOWERTIMEOUT = 79,
		SPI_GETPOWEROFFTIMEOUT = 80,
		SPI_SETLOWPOWERTIMEOUT = 81,
		SPI_SETPOWEROFFTIMEOUT = 82,
		SPI_GETLOWPOWERACTIVE = 83,
		SPI_GETPOWEROFFACTIVE = 84,
		SPI_SETLOWPOWERACTIVE = 85,
		SPI_SETPOWEROFFACTIVE = 86,
		SPI_SETCURSORS = 87,
		SPI_SETICONS = 88,
		SPI_GETDEFAULTINPUTLANG = 89,
		SPI_SETDEFAULTINPUTLANG = 90,
		SPI_SETLANGTOGGLE = 91,
		SPI_GETWINDOWSEXTENSION = 92,
		SPI_SETMOUSETRAILS = 93,
		SPI_GETMOUSETRAILS = 94,
		SPI_SCREENSAVERRUNNING = 97,
		SPI_GETFILTERKEYS = 50,
		SPI_SETFILTERKEYS = 51,
		SPI_GETTOGGLEKEYS = 52,
		SPI_SETTOGGLEKEYS = 53,
		SPI_GETMOUSEKEYS = 54,
		SPI_SETMOUSEKEYS = 55,
		SPI_GETSHOWSOUNDS = 56,
		SPI_SETSHOWSOUNDS = 57,
		SPI_GETSTICKYKEYS = 58,
		SPI_SETSTICKYKEYS = 59,
		SPI_GETACCESSTIMEOUT = 60,
		SPI_SETACCESSTIMEOUT = 61,
		SPI_GETSERIALKEYS = 62,
		SPI_SETSERIALKEYS = 63,
		SPI_GETSOUNDSENTRY = 64,
		SPI_SETSOUNDSENTRY = 65,
		SPI_GETSNAPTODEFBUTTON = 95,
		SPI_SETSNAPTODEFBUTTON = 96,
		SPI_GETMOUSEHOVERWIDTH = 98,
		SPI_SETMOUSEHOVERWIDTH = 99,
		SPI_GETMOUSEHOVERHEIGHT = 100,
		SPI_SETMOUSEHOVERHEIGHT = 101,
		SPI_GETMOUSEHOVERTIME = 102,
		SPI_SETMOUSEHOVERTIME = 103,
		SPI_GETWHEELSCROLLLINES = 104,
		SPI_SETWHEELSCROLLLINES = 105,
		SPIF_UPDATEINIFILE = 0x0001,
		SPIF_SENDWININICHANGE = 0x0002,
		SPIF_SENDCHANGE = 0x0002,
		SERKF_SERIALKEYSON = 0x00000001,
		SERKF_AVAILABLE = 0x00000002,
		SERKF_INDICATOR = 0x00000004,
		SKF_STICKYKEYSON = 0x00000001,
		SKF_AVAILABLE = 0x00000002,
		SKF_HOTKEYACTIVE = 0x00000004,
		SKF_CONFIRMHOTKEY = 0x00000008,
		SKF_HOTKEYSOUND = 0x00000010,
		SKF_INDICATOR = 0x00000020,
		SKF_AUDIBLEFEEDBACK = 0x00000040,
		SKF_TRISTATE = 0x00000080,
		SKF_TWOKEYSOFF = 0x00000100,
		SSGF_NONE = 0,
		SSGF_DISPLAY = 3,
		SSTF_NONE = 0,
		SSTF_CHARS = 1,
		SSTF_BORDER = 2,
		SSTF_DISPLAY = 3,
		SSWF_NONE = 0,
		SSWF_TITLE = 1,
		SSWF_WINDOW = 2,
		SSWF_DISPLAY = 3,
		SSWF_CUSTOM = 4,
		SSF_SOUNDSENTRYON = 0x00000001,
		SSF_AVAILABLE = 0x00000002,
		SSF_INDICATOR = 0x00000004,
		SLE_ERROR = 0x00000001,
		SLE_MINORERROR = 0x00000002,
		SLE_WARNING = 0x00000003,
		STD_CUT = 0,
		STD_COPY = 1,
		STD_PASTE = 2,
		STD_UNDO = 3,
		STD_REDOW = 4,
		STD_DELETE = 5,
		STD_FILENEW = 6,
		STD_FILEOPEN = 7,
		STD_FILESAVE = 8,
		STD_PRINTPRE = 9,
		STD_PROPERTIES = 10,
		STD_HELP = 11,
		STD_FIND = 12,
		STD_REPLACE = 13,
		STD_PRINT = 14,
		SBARS_SIZEGRIP = 0x0100,
		SB_SETTEXTA = (0x0400+1),
		SB_SETTEXTW = (0x0400+11),
		SB_GETTEXTA = (0x0400+2),
		SB_GETTEXTW = (0x0400+13),
		SB_GETTEXTLENGTHA = (0x0400+3),
		SB_GETTEXTLENGTHW = (0x0400+12),
		SB_SETPARTS = (0x0400+4),
		SB_GETPARTS = (0x0400+6),
		SB_GETBORDERS = (0x0400+7),
		SB_SETMINHEIGHT = (0x0400+8),
		SB_SIMPLE = (0x0400+9),
		SB_GETRECT = (0x0400+10),
		SB_ISSIMPLE = (0x0400+14),
		SBT_OWNERDRAW = 0x1000,
		SBT_NOBORDERS = 0x0100,
		SBT_POPOUT = 0x0200,
		SBT_RTLREADING = 0x0400;
	char SC_GROUP_IDENTIFIER = '+';
	int STILL_ACTIVE = (0x00000103),
		SEMAPHORE_ALL_ACCESS = ((0x000F0000)|(0x00100000)|0x3);

}