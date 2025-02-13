// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface winc {
	int CDERR_DIALOGFAILURE = 0xFFFF,
		CDERR_GENERALCODES = 0x0000,
		CDERR_STRUCTSIZE = 0x0001,
		CDERR_INITIALIZATION = 0x0002,
		CDERR_NOTEMPLATE = 0x0003,
		CDERR_NOHINSTANCE = 0x0004,
		CDERR_LOADSTRFAILURE = 0x0005,
		CDERR_FINDRESFAILURE = 0x0006,
		CDERR_LOADRESFAILURE = 0x0007,
		CDERR_LOCKRESFAILURE = 0x0008,
		CDERR_MEMALLOCFAILURE = 0x0009,
		CDERR_MEMLOCKFAILURE = 0x000A,
		CDERR_NOHOOK = 0x000B,
		CDERR_REGISTERMSGFAIL = 0x000C,
		CFERR_CHOOSEFONTCODES = 0x2000,
		CFERR_NOFONTS = 0x2001,
		CFERR_MAXLESSTHANMIN = 0x2002,
		CCERR_CHOOSECOLORCODES = 0x5000,
		CDN_FIRST = (0-601),
		CDN_LAST = (0-699),
		CDN_INITDONE = ((0-601)-0x0000),
		CDN_SELCHANGE = ((0-601)-0x0001),
		CDN_FOLDERCHANGE = ((0-601)-0x0002),
		CDN_SHAREVIOLATION = ((0-601)-0x0003),
		CDN_HELP = ((0-601)-0x0004),
		CDN_FILEOK = ((0-601)-0x0005),
		CDN_TYPECHANGE = ((0-601)-0x0006),
		CC_RGBINIT = 0x00000001,
		CC_FULLOPEN = 0x00000002,
		CC_PREVENTFULLOPEN = 0x00000004,
		CC_SHOWHELP = 0x00000008,
		CC_ENABLEHOOK = 0x00000010,
		CC_ENABLETEMPLATE = 0x00000020,
		CC_ENABLETEMPLATEHANDLE = 0x00000040,
		CC_SOLIDCOLOR = 0x00000080,
		CC_ANYCOLOR = 0x00000100,
		CF_SCREENFONTS = 0x00000001,
		CF_PRINTERFONTS = 0x00000002,
		CF_BOTH = (0x00000001|0x00000002),
		CF_SHOWHELP = 0x00000004,
		CF_ENABLEHOOK = 0x00000008,
		CF_ENABLETEMPLATE = 0x00000010,
		CF_ENABLETEMPLATEHANDLE = 0x00000020,
		CF_INITTOLOGFONTSTRUCT = 0x00000040,
		CF_USESTYLE = 0x00000080,
		CF_EFFECTS = 0x00000100,
		CF_APPLY = 0x00000200,
		CF_ANSIONLY = 0x00000400,
		CF_SCRIPTSONLY = 0x00000400,
		CF_NOVECTORFONTS = 0x00000800,
		CF_NOOEMFONTS = 0x00000800,
		CF_NOSIMULATIONS = 0x00001000,
		CF_LIMITSIZE = 0x00002000,
		CF_FIXEDPITCHONLY = 0x00004000,
		CF_WYSIWYG = 0x00008000,
		CF_FORCEFONTEXIST = 0x00010000,
		CF_SCALABLEONLY = 0x00020000,
		CF_TTONLY = 0x00040000,
		CF_NOFACESEL = 0x00080000,
		CF_NOSTYLESEL = 0x00100000,
		CF_NOSIZESEL = 0x00200000,
		CF_SELECTSCRIPT = 0x00400000,
		CF_NOSCRIPTSEL = 0x00800000,
		CF_NOVERTFONTS = 0x01000000,
		CD_LBSELNOITEMS = -1,
		CD_LBSELCHANGE = 0,
		CD_LBSELSUB = 1,
		CD_LBSELADD = 2,
		CADV_LATEACK = 0xFFFF,
		CP_WINANSI = 1004,
		CP_WINUNICODE = 1200;
	// CP_WINNEUTRAL = 1004;
	int CBF_FAIL_SELFCONNECTIONS = 0x00001000,
		CBF_FAIL_CONNECTIONS = 0x00002000,
		CBF_FAIL_ADVISES = 0x00004000,
		CBF_FAIL_EXECUTES = 0x00008000,
		CBF_FAIL_POKES = 0x00010000,
		CBF_FAIL_REQUESTS = 0x00020000,
		CBF_FAIL_ALLSVRXACTIONS = 0x0003f000,
		CBF_SKIP_CONNECT_CONFIRMS = 0x00040000,
		CBF_SKIP_REGISTRATIONS = 0x00080000,
		CBF_SKIP_UNREGISTRATIONS = 0x00100000,
		CBF_SKIP_DISCONNECTS = 0x00200000,
		CBF_SKIP_ALLNOTIFICATIONS = 0x003c0000,
		ctlFirst = 0x0400,
		ctlLast = 0x04ff,
		chx1 = 0x0410,
		chx2 = 0x0411,
		chx3 = 0x0412,
		chx4 = 0x0413,
		chx5 = 0x0414,
		chx6 = 0x0415,
		chx7 = 0x0416,
		chx8 = 0x0417,
		chx9 = 0x0418,
		chx10 = 0x0419,
		chx11 = 0x041a,
		chx12 = 0x041b,
		chx13 = 0x041c,
		chx14 = 0x041d,
		chx15 = 0x041e,
		chx16 = 0x041f,
		cmb1 = 0x0470,
		cmb2 = 0x0471,
		cmb3 = 0x0472,
		cmb4 = 0x0473,
		cmb5 = 0x0474,
		cmb6 = 0x0475,
		cmb7 = 0x0476,
		cmb8 = 0x0477,
		cmb9 = 0x0478,
		cmb10 = 0x0479,
		cmb11 = 0x047a,
		cmb12 = 0x047b,
		cmb13 = 0x047c,
		cmb14 = 0x047d,
		cmb15 = 0x047e,
		cmb16 = 0x047f,
		CPS_COMPLETE = 0x0001,
		CPS_CONVERT = 0x0002,
		CPS_REVERT = 0x0003,
		CPS_CANCEL = 0x0004,
		CS_INSERTCHAR = 0x2000,
		CS_NOMOVECARET = 0x4000,
		CFS_DEFAULT = 0x0000,
		CFS_RECT = 0x0001,
		CFS_POINT = 0x0002,
		CFS_FORCE_POSITION = 0x0020,
		CFS_CANDIDATEPOS = 0x0040,
		CFS_EXCLUDE = 0x0080,
		CALLBACK_TYPEMASK = 0x00070000,
		CALLBACK_NULL = 0x00000000,
		CALLBACK_WINDOW = 0x00010000,
		CALLBACK_TASK = 0x00020000,
		CALLBACK_FUNCTION = 0x00030000,
		CALLBACK_THREAD = (0x00020000),
		CALLBACK_EVENT = 0x00050000;
	char CFSEPCHAR = '+';
	int CALL_PENDING = 0x02,
		CWCSTORAGENAME = 32,
		COM_RIGHTS_EXECUTE = 1,
		cbNDRContext = 20,
		CREATE_NEW = 1,
		CREATE_ALWAYS = 2,
		CALLBACK_CHUNK_FINISHED = 0x00000000,
		CALLBACK_STREAM_SWITCH = 0x00000001,
		COPY_FILE_FAIL_IF_EXISTS = 0x00000001,
		COPY_FILE_RESTARTABLE = 0x00000002,
		COMMPROP_INITIALIZED = (0xE73CF52E),
		CREATE_SUSPENDED = 0x00000004,
		CREATE_NEW_CONSOLE = 0x00000010,
		CREATE_NEW_PROCESS_GROUP = 0x00000200,
		CREATE_UNICODE_ENVIRONMENT = 0x00000400,
		CREATE_SEPARATE_WOW_VDM = 0x00000800,
		CREATE_SHARED_WOW_VDM = 0x00001000,
		CREATE_FORCEDOS = 0x00002000,
		CREATE_DEFAULT_ERROR_MODE = 0x04000000,
		CREATE_NO_WINDOW = 0x08000000,
		CREATE_THREAD_DEBUG_EVENT = 2,
		CREATE_PROCESS_DEBUG_EVENT = 3,
		CBR_110 = 110,
		CBR_300 = 300,
		CBR_600 = 600,
		CBR_1200 = 1200,
		CBR_2400 = 2400,
		CBR_4800 = 4800,
		CBR_9600 = 9600,
		CBR_14400 = 14400,
		CBR_19200 = 19200,
		CBR_38400 = 38400,
		CBR_56000 = 56000,
		CBR_57600 = 57600,
		CBR_115200 = 115200,
		CBR_128000 = 128000,
		CBR_256000 = 256000,
		CE_RXOVER = 0x0001,
		CE_OVERRUN = 0x0002,
		CE_RXPARITY = 0x0004,
		CE_FRAME = 0x0008,
		CE_BREAK = 0x0010,
		CE_TXFULL = 0x0100,
		CE_PTO = 0x0200,
		CE_IOE = 0x0400,
		CE_DNS = 0x0800,
		CE_OOP = 0x1000,
		CE_MODE = 0x8000,
		CLRRTS = 4,
		CLRDTR = 6,
		CLRBREAK = 9,
		CAPSLOCK_ON = 0x0080,
		CTRL_C_EVENT = 0,
		CTRL_BREAK_EVENT = 1,
		CTRL_CLOSE_EVENT = 2,
		CTRL_LOGOFF_EVENT = 5,
		CTRL_SHUTDOWN_EVENT = 6,
		CONSOLE_TEXTMODE_BUFFER = 1,
		CRYPT_MODE_CBCI = 6,
		CRYPT_MODE_CFBP = 7,
		CRYPT_MODE_OFBP = 8,
		CRYPT_MODE_CBCOFM = 9,
		CRYPT_MODE_CBCOFMI = 10,
		CALG_MD2 = ((4<<13)|(0)|1),
		CALG_MD4 = ((4<<13)|(0)|2),
		CALG_MD5 = ((4<<13)|(0)|3),
		CALG_SHA = ((4<<13)|(0)|4),
		CALG_MAC = ((4<<13)|(0)|5),
		CALG_RSA_SIGN = ((1<<13)|(2<<9)|0),
		CALG_DSS_SIGN = ((1<<13)|(1<<9)|0),
		CALG_RSA_KEYX = ((5<<13)|(2<<9)|0),
		CALG_DES = ((3<<13)|(3<<9)|1),
		CALG_RC2 = ((3<<13)|(3<<9)|2),
		CALG_RC4 = ((3<<13)|(4<<9)|1),
		CALG_SEAL = ((3<<13)|(4<<9)|2),
		CRYPT_VERIFYCONTEXT = 0xF0000000,
		CRYPT_NEWKEYSET = 0x8,
		CRYPT_DELETEKEYSET = 0x10,
		CRYPT_EXPORTABLE = 0x00000001,
		CRYPT_USER_PROTECTED = 0x00000002,
		CRYPT_CREATE_SALT = 0x00000004,
		CRYPT_UPDATE_KEY = 0x00000008,
		CRYPT_USERDATA = 1,
		CRYPT_MODE_CBC = 1,
		CRYPT_MODE_ECB = 2,
		CRYPT_MODE_OFB = 3,
		CRYPT_MODE_CFB = 4,
		CRYPT_MODE_CTS = 5,
		CRYPT_ENCRYPT = 0x0001,
		CRYPT_DECRYPT = 0x0002,
		CRYPT_READ = 0x0008,
		CRYPT_WRITE = 0x0010,
		CRYPT_MAC = 0x0020;
	boolean CRYPT_FAILED = false,
		CRYPT_SUCCEED = true;
	int CRYPT_FIRST = 1,
		CRYPT_NEXT = 2,
		CRYPT_IMPL_HARDWARE = 1,
		CRYPT_IMPL_SOFTWARE = 2,
		CRYPT_IMPL_MIXED = 3,
		CRYPT_IMPL_UNKNOWN = 4,
		CUR_BLOB_VERSION = 2,
		CO_E_INIT_TLS = 0x80004006,
		CO_E_INIT_SHARED_ALLOCATOR = 0x80004007,
		CO_E_INIT_MEMORY_ALLOCATOR = 0x80004008,
		CO_E_INIT_CLASS_CACHE = 0x80004009,
		CO_E_INIT_RPC_CHANNEL = 0x8000400A,
		CO_E_INIT_TLS_SET_CHANNEL_CONTROL = 0x8000400B,
		CO_E_INIT_TLS_CHANNEL_CONTROL = 0x8000400C,
		CO_E_INIT_UNACCEPTED_USER_ALLOCATOR = 0x8000400D,
		CO_E_INIT_SCM_MUTEX_EXISTS = 0x8000400E,
		CO_E_INIT_SCM_FILE_MAPPING_EXISTS = 0x8000400F,
		CO_E_INIT_SCM_MAP_VIEW_OF_FILE = 0x80004010,
		CO_E_INIT_SCM_EXEC_FAILURE = 0x80004011,
		CO_E_INIT_ONLY_SINGLE_THREADED = 0x80004012,
		CO_E_CANT_REMOTE = 0x80004013,
		CO_E_BAD_SERVER_NAME = 0x80004014,
		CO_E_WRONG_SERVER_IDENTITY = 0x80004015,
		CO_E_OLE1DDE_DISABLED = 0x80004016,
		CO_E_RUNAS_SYNTAX = 0x80004017,
		CO_E_CREATEPROCESS_FAILURE = 0x80004018,
		CO_E_RUNAS_CREATEPROCESS_FAILURE = 0x80004019,
		CO_E_RUNAS_LOGON_FAILURE = 0x8000401A,
		CO_E_LAUNCH_PERMSSION_DENIED = 0x8000401B,
		CO_E_START_SERVICE_FAILURE = 0x8000401C,
		CO_E_REMOTE_COMMUNICATION_FAILURE = 0x8000401D,
		CO_E_SERVER_START_TIMEOUT = 0x8000401E,
		CO_E_CLSREG_INCONSISTENT = 0x8000401F,
		CO_E_IIDREG_INCONSISTENT = 0x80004020,
		CO_E_NOT_SUPPORTED = 0x80004021,
		CLASSFACTORY_E_FIRST = 0x80040110,
		CLASSFACTORY_E_LAST = 0x8004011F,
		CLASSFACTORY_S_FIRST = 0x00040110,
		CLASSFACTORY_S_LAST = 0x0004011F,
		CLASS_E_NOAGGREGATION = 0x80040110,
		CLASS_E_CLASSNOTAVAILABLE = 0x80040111,
		CACHE_E_FIRST = 0x80040170,
		CACHE_E_LAST = 0x8004017F,
		CACHE_S_FIRST = 0x00040170,
		CACHE_S_LAST = 0x0004017F,
		CACHE_E_NOCACHE_UPDATED = 0x80040170,
		CLIENTSITE_E_FIRST = 0x80040190,
		CLIENTSITE_E_LAST = 0x8004019F,
		CLIENTSITE_S_FIRST = 0x00040190,
		CLIENTSITE_S_LAST = 0x0004019F,
		CONVERT10_E_FIRST = 0x800401C0,
		CONVERT10_E_LAST = 0x800401CF,
		CONVERT10_S_FIRST = 0x000401C0,
		CONVERT10_S_LAST = 0x000401CF,
		CONVERT10_E_OLESTREAM_GET = 0x800401C0,
		CONVERT10_E_OLESTREAM_PUT = 0x800401C1,
		CONVERT10_E_OLESTREAM_FMT = 0x800401C2,
		CONVERT10_E_OLESTREAM_BITMAP_TO_DIB = 0x800401C3,
		CONVERT10_E_STG_FMT = 0x800401C4,
		CONVERT10_E_STG_NO_STD_STREAM = 0x800401C5,
		CONVERT10_E_STG_DIB_TO_BITMAP = 0x800401C6,
		CLIPBRD_E_FIRST = 0x800401D0,
		CLIPBRD_E_LAST = 0x800401DF,
		CLIPBRD_S_FIRST = 0x000401D0,
		CLIPBRD_S_LAST = 0x000401DF,
		CLIPBRD_E_CANT_OPEN = 0x800401D0,
		CLIPBRD_E_CANT_EMPTY = 0x800401D1,
		CLIPBRD_E_CANT_SET = 0x800401D2,
		CLIPBRD_E_BAD_DATA = 0x800401D3,
		CLIPBRD_E_CANT_CLOSE = 0x800401D4,
		CO_E_FIRST = 0x800401F0,
		CO_E_LAST = 0x800401FF,
		CO_S_FIRST = 0x000401F0,
		CO_S_LAST = 0x000401FF,
		CO_E_NOTINITIALIZED = 0x800401F0,
		CO_E_ALREADYINITIALIZED = 0x800401F1,
		CO_E_CANTDETERMINECLASS = 0x800401F2,
		CO_E_CLASSSTRING = 0x800401F3,
		CO_E_IIDSTRING = 0x800401F4,
		CO_E_APPNOTFOUND = 0x800401F5,
		CO_E_APPSINGLEUSE = 0x800401F6,
		CO_E_ERRORINAPP = 0x800401F7,
		CO_E_DLLNOTFOUND = 0x800401F8,
		CO_E_ERRORINDLL = 0x800401F9,
		CO_E_WRONGOSFORAPP = 0x800401FA,
		CO_E_OBJNOTREG = 0x800401FB,
		CO_E_OBJISREG = 0x800401FC,
		CO_E_OBJNOTCONNECTED = 0x800401FD,
		CO_E_APPDIDNTREG = 0x800401FE,
		CO_E_RELEASED = 0x800401FF,
		CACHE_S_FORMATETC_NOTSUPPORTED = 0x00040170,
		CACHE_S_SAMECACHE = 0x00040171,
		CACHE_S_SOMECACHES_NOTUPDATED = 0x00040172,
		CONVERT10_S_NO_PRESENTATION = 0x000401C0,
		CO_E_CLASS_CREATE_FAILED = 0x80080001,
		CO_E_SCM_ERROR = 0x80080002,
		CO_E_SCM_RPC_FAILURE = 0x80080003,
		CO_E_BAD_PATH = 0x80080004,
		CO_E_SERVER_EXEC_FAILURE = 0x80080005,
		CO_E_OBJSRV_RPC_FAILURE = 0x80080006,
		CO_E_SERVER_STOPPING = 0x80080008,
		CO_S_NOTALLINTERFACES = 0x00080012,
		CERT_E_EXPIRED = 0x800B0101,
		CERT_E_VALIDIYPERIODNESTING = 0x800B0102,
		CERT_E_ROLE = 0x800B0103,
		CERT_E_CRITICAL = 0x800B0105,
		CERT_E_PURPOSE = 0x800B0106,
		CERT_E_ISSUERCHAINING = 0x800B0107,
		CERT_E_MALFORMED = 0x800B0108,
		CERT_E_UNTRUSTEDROOT = 0x800B0109,
		CERT_E_CHAINING = 0x800B010A,
		COMPLEXREGION = 3,
		COLORONCOLOR = 3,
		CLIP_TO_PATH = 4097,
		CLOSECHANNEL = 4112,
		CM_OUT_OF_GAMUT = 255,
		CM_IN_GAMUT = 0,
		CLIP_DEFAULT_PRECIS = 0,
		CLIP_CHARACTER_PRECIS = 1,
		CLIP_STROKE_PRECIS = 2,
		CLIP_MASK = 0xf,
		CLIP_LH_ANGLES = (1<<4),
		CLIP_TT_ALWAYS = (2<<4),
		CLIP_EMBEDDED = (8<<4),
		CHINESEBIG5_CHARSET = 136,
		CLR_INVALID = 0xFFFFFFFF,
		CURVECAPS = 28,
		CLIPCAPS = 36,
		COLORRES = 108,
		CC_NONE = 0,
		CC_CIRCLES = 1,
		CC_PIE = 2,
		CC_CHORD = 4,
		CC_ELLIPSES = 8,
		CC_WIDE = 16,
		CC_STYLED = 32,
		CC_WIDESTYLED = 64,
		CC_INTERIORS = 128,
		CC_ROUNDRECT = 256,
		CP_NONE = 0,
		CP_RECTANGLE = 1,
		CP_REGION = 2,
		CBM_INIT = 0x04,
		CCHDEVICENAME = 32,
		CCHFORMNAME = 32,
		CA_NEGATIVE = 0x0001,
		CA_LOG_FILTER = 0x0002,
		CONNECT_UPDATE_PROFILE = 0x00000001,
		CONNECT_UPDATE_RECENT = 0x00000002,
		CONNECT_TEMPORARY = 0x00000004,
		CONNECT_INTERACTIVE = 0x00000008,
		CONNECT_PROMPT = 0x00000010,
		CONNECT_NEED_DRIVE = 0x00000020,
		CONNECT_REFCOUNT = 0x00000040,
		CONNECT_REDIRECT = 0x00000080,
		CONNECT_LOCALDRIVE = 0x00000100,
		CONNECT_CURRENT_MEDIA = 0x00000200,
		CONNECT_DEFERRED = 0x00000400,
		CONNECT_RESERVED = 0xFF000000,
		CONNDLG_RO_PATH = 0x00000001,
		CONNDLG_CONN_POINT = 0x00000002,
		CONNDLG_USE_MRU = 0x00000004,
		CONNDLG_HIDE_BOX = 0x00000008,
		CONNDLG_PERSIST = 0x00000010,
		CONNDLG_NOT_PERSIST = 0x00000020,
		CT_CTYPE1 = 0x00000001,
		CT_CTYPE2 = 0x00000002,
		CT_CTYPE3 = 0x00000004,
		C1_UPPER = 0x0001,
		C1_LOWER = 0x0002,
		C1_DIGIT = 0x0004,
		C1_SPACE = 0x0008,
		C1_PUNCT = 0x0010,
		C1_CNTRL = 0x0020,
		C1_BLANK = 0x0040,
		C1_XDIGIT = 0x0080,
		C1_ALPHA = 0x0100,
		C2_LEFTTORIGHT = 0x0001,
		C2_RIGHTTOLEFT = 0x0002,
		C2_EUROPENUMBER = 0x0003,
		C2_EUROPESEPARATOR = 0x0004,
		C2_EUROPETERMINATOR = 0x0005,
		C2_ARABICNUMBER = 0x0006,
		C2_COMMONSEPARATOR = 0x0007,
		C2_BLOCKSEPARATOR = 0x0008,
		C2_SEGMENTSEPARATOR = 0x0009,
		C2_WHITESPACE = 0x000A,
		C2_OTHERNEUTRAL = 0x000B,
		C2_NOTAPPLICABLE = 0x0000,
		C3_NONSPACING = 0x0001,
		C3_DIACRITIC = 0x0002,
		C3_VOWELMARK = 0x0004,
		C3_SYMBOL = 0x0008,
		C3_KATAKANA = 0x0010,
		C3_HIRAGANA = 0x0020,
		C3_HALFWIDTH = 0x0040,
		C3_FULLWIDTH = 0x0080,
		C3_IDEOGRAPH = 0x0100,
		C3_KASHIDA = 0x0200,
		C3_LEXICAL = 0x0400,
		C3_ALPHA = 0x8000,
		C3_NOTAPPLICABLE = 0x0000,
		CP_INSTALLED = 0x00000001,
		CP_SUPPORTED = 0x00000002,
		CP_ACP = 0,
		CP_OEMCP = 1,
		CP_MACCP = 2,
		CP_UTF7 = 65000,
		CP_UTF8 = 65001,
		CTRY_DEFAULT = 0,
		CTRY_AUSTRALIA = 61,
		CTRY_AUSTRIA = 43,
		CTRY_BELGIUM = 32,
		CTRY_BRAZIL = 55,
		CTRY_BULGARIA = 359,
		CTRY_CANADA = 2,
		CTRY_CROATIA = 385,
		CTRY_CZECH = 42,
		CTRY_DENMARK = 45,
		CTRY_FINLAND = 358,
		CTRY_FRANCE = 33,
		CTRY_GERMANY = 49,
		CTRY_GREECE = 30,
		CTRY_HONG_KONG = 852,
		CTRY_HUNGARY = 36,
		CTRY_ICELAND = 354,
		CTRY_IRELAND = 353,
		CTRY_ITALY = 39,
		CTRY_JAPAN = 81,
		CTRY_MEXICO = 52,
		CTRY_NETHERLANDS = 31,
		CTRY_NEW_ZEALAND = 64,
		CTRY_NORWAY = 47,
		CTRY_POLAND = 48,
		CTRY_PORTUGAL = 351,
		CTRY_PRCHINA = 86,
		CTRY_ROMANIA = 40,
		CTRY_RUSSIA = 7,
		CTRY_SINGAPORE = 65,
		CTRY_SLOVAK = 42,
		CTRY_SLOVENIA = 386,
		CTRY_SOUTH_KOREA = 82,
		CTRY_SPAIN = 34,
		CTRY_SWEDEN = 46,
		CTRY_SWITZERLAND = 41,
		CTRY_TAIWAN = 886,
		CTRY_TURKEY = 90,
		CTRY_UNITED_KINGDOM = 44,
		CTRY_UNITED_STATES = 1,
		CAL_ICALINTVALUE = 0x00000001,
		CAL_SCALNAME = 0x00000002,
		CAL_IYEAROFFSETRANGE = 0x00000003,
		CAL_SERASTRING = 0x00000004,
		CAL_SSHORTDATE = 0x00000005,
		CAL_SLONGDATE = 0x00000006,
		CAL_SDAYNAME1 = 0x00000007,
		CAL_SDAYNAME2 = 0x00000008,
		CAL_SDAYNAME3 = 0x00000009,
		CAL_SDAYNAME4 = 0x0000000a,
		CAL_SDAYNAME5 = 0x0000000b,
		CAL_SDAYNAME6 = 0x0000000c,
		CAL_SDAYNAME7 = 0x0000000d,
		CAL_SABBREVDAYNAME1 = 0x0000000e,
		CAL_SABBREVDAYNAME2 = 0x0000000f,
		CAL_SABBREVDAYNAME3 = 0x00000010,
		CAL_SABBREVDAYNAME4 = 0x00000011,
		CAL_SABBREVDAYNAME5 = 0x00000012,
		CAL_SABBREVDAYNAME6 = 0x00000013,
		CAL_SABBREVDAYNAME7 = 0x00000014,
		CAL_SMONTHNAME1 = 0x00000015,
		CAL_SMONTHNAME2 = 0x00000016,
		CAL_SMONTHNAME3 = 0x00000017,
		CAL_SMONTHNAME4 = 0x00000018,
		CAL_SMONTHNAME5 = 0x00000019,
		CAL_SMONTHNAME6 = 0x0000001a,
		CAL_SMONTHNAME7 = 0x0000001b,
		CAL_SMONTHNAME8 = 0x0000001c,
		CAL_SMONTHNAME9 = 0x0000001d,
		CAL_SMONTHNAME10 = 0x0000001e,
		CAL_SMONTHNAME11 = 0x0000001f,
		CAL_SMONTHNAME12 = 0x00000020,
		CAL_SMONTHNAME13 = 0x00000021,
		CAL_SABBREVMONTHNAME1 = 0x00000022,
		CAL_SABBREVMONTHNAME2 = 0x00000023,
		CAL_SABBREVMONTHNAME3 = 0x00000024,
		CAL_SABBREVMONTHNAME4 = 0x00000025,
		CAL_SABBREVMONTHNAME5 = 0x00000026,
		CAL_SABBREVMONTHNAME6 = 0x00000027,
		CAL_SABBREVMONTHNAME7 = 0x00000028,
		CAL_SABBREVMONTHNAME8 = 0x00000029,
		CAL_SABBREVMONTHNAME9 = 0x0000002a,
		CAL_SABBREVMONTHNAME10 = 0x0000002b,
		CAL_SABBREVMONTHNAME11 = 0x0000002c,
		CAL_SABBREVMONTHNAME12 = 0x0000002d,
		CAL_SABBREVMONTHNAME13 = 0x0000002e,
		CAL_GREGORIAN = 1,
		CAL_GREGORIAN_US = 2,
		CAL_JAPAN = 3,
		CAL_TAIWAN = 4,
		CAL_KOREA = 5,
		CAL_HIJRI = 6,
		CAL_THAI = 7,
		CAL_HEBREW = 8;
	int CONTAINER_INHERIT_ACE = (0x2),
		COMPRESSION_FORMAT_NONE = (0x0000),
		COMPRESSION_FORMAT_DEFAULT = (0x0001),
		COMPRESSION_FORMAT_LZNT1 = (0x0002),
		COMPRESSION_ENGINE_STANDARD = (0x0000),
		COMPRESSION_ENGINE_MAXIMUM = (0x0100),
		CS_VREDRAW = 0x0001,
		CS_HREDRAW = 0x0002,
		CS_KEYCVTWINDOW = 0x0004,
		CS_DBLCLKS = 0x0008,
		CS_OWNDC = 0x0020,
		CS_CLASSDC = 0x0040,
		CS_PARENTDC = 0x0080,
		CS_NOKEYCVT = 0x0100,
		CS_NOCLOSE = 0x0200,
		CS_SAVEBITS = 0x0800,
		CS_BYTEALIGNCLIENT = 0x1000,
		CS_BYTEALIGNWINDOW = 0x2000,
		CS_GLOBALCLASS = 0x4000,
		CS_IME = 0x00010000,
		CF_TEXT = 1,
		CF_BITMAP = 2,
		CF_METAFILEPICT = 3,
		CF_SYLK = 4,
		CF_DIF = 5,
		CF_TIFF = 6,
		CF_OEMTEXT = 7,
		CF_DIB = 8,
		CF_PALETTE = 9,
		CF_PENDATA = 10,
		CF_RIFF = 11,
		CF_WAVE = 12,
		CF_UNICODETEXT = 13,
		CF_ENHMETAFILE = 14,
		CF_HDROP = 15,
		CF_LOCALE = 16,
		CF_MAX = 17,
		CF_OWNERDISPLAY = 0x0080,
		CF_DSPTEXT = 0x0081,
		CF_DSPBITMAP = 0x0082,
		CF_DSPMETAFILEPICT = 0x0083,
		CF_DSPENHMETAFILE = 0x008E,
		CF_PRIVATEFIRST = 0x0200,
		CF_PRIVATELAST = 0x02FF,
		CF_GDIOBJFIRST = 0x0300,
		CF_GDIOBJLAST = 0x03FF,
		CW_USEDEFAULT = (0x80000000),
		CWP_ALL = 0x0000,
		CWP_SKIPINVISIBLE = 0x0001,
		CWP_SKIPDISABLED = 0x0002,
		CWP_SKIPTRANSPARENT = 0x0004,
		CTLCOLOR_MSGBOX = 0,
		CTLCOLOR_EDIT = 1,
		CTLCOLOR_LISTBOX = 2,
		CTLCOLOR_BTN = 3,
		CTLCOLOR_DLG = 4,
		CTLCOLOR_SCROLLBAR = 5,
		CTLCOLOR_STATIC = 6,
		CTLCOLOR_MAX = 7,
		COLOR_SCROLLBAR = 0,
		COLOR_BACKGROUND = 1,
		COLOR_ACTIVECAPTION = 2,
		COLOR_INACTIVECAPTION = 3,
		COLOR_MENU = 4,
		COLOR_WINDOW = 5,
		COLOR_WINDOWFRAME = 6,
		COLOR_MENUTEXT = 7,
		COLOR_WINDOWTEXT = 8,
		COLOR_CAPTIONTEXT = 9,
		COLOR_ACTIVEBORDER = 10,
		COLOR_INACTIVEBORDER = 11,
		COLOR_APPWORKSPACE = 12,
		COLOR_HIGHLIGHT = 13,
		COLOR_HIGHLIGHTTEXT = 14,
		COLOR_BTNFACE = 15,
		COLOR_BTNSHADOW = 16,
		COLOR_GRAYTEXT = 17,
		COLOR_BTNTEXT = 18,
		COLOR_INACTIVECAPTIONTEXT = 19,
		COLOR_BTNHIGHLIGHT = 20,
		COLOR_3DDKSHADOW = 21,
		COLOR_3DLIGHT = 22,
		COLOR_INFOTEXT = 23,
		COLOR_INFOBK = 24,
		COLOR_DESKTOP = 1,
		COLOR_3DFACE = 15,
		COLOR_3DSHADOW = 16,
		COLOR_3DHIGHLIGHT = 20,
		COLOR_3DHILIGHT = 20,
		COLOR_BTNHILIGHT = 20,
		CB_OKAY = 0,
		CB_ERR = (-1),
		CB_ERRSPACE = (-2),
		CBN_ERRSPACE = (-1),
		CBN_SELCHANGE = 1,
		CBN_DBLCLK = 2,
		CBN_SETFOCUS = 3,
		CBN_KILLFOCUS = 4,
		CBN_EDITCHANGE = 5,
		CBN_EDITUPDATE = 6,
		CBN_DROPDOWN = 7,
		CBN_CLOSEUP = 8,
		CBN_SELENDOK = 9,
		CBN_SELENDCANCEL = 10,
		CBS_SIMPLE = 0x0001,
		CBS_DROPDOWN = 0x0002,
		CBS_DROPDOWNLIST = 0x0003,
		CBS_OWNERDRAWFIXED = 0x0010,
		CBS_OWNERDRAWVARIABLE = 0x0020,
		CBS_AUTOHSCROLL = 0x0040,
		CBS_OEMCONVERT = 0x0080,
		CBS_SORT = 0x0100,
		CBS_HASSTRINGS = 0x0200,
		CBS_NOINTEGRALHEIGHT = 0x0400,
		CBS_DISABLENOSCROLL = 0x0800,
		CBS_UPPERCASE = 0x2000,
		CBS_LOWERCASE = 0x4000,
		CB_GETEDITSEL = 0x0140,
		CB_LIMITTEXT = 0x0141,
		CB_SETEDITSEL = 0x0142,
		CB_ADDSTRING = 0x0143,
		CB_DELETESTRING = 0x0144,
		CB_DIR = 0x0145,
		CB_GETCOUNT = 0x0146,
		CB_GETCURSEL = 0x0147,
		CB_GETLBTEXT = 0x0148,
		CB_GETLBTEXTLEN = 0x0149,
		CB_INSERTSTRING = 0x014A,
		CB_RESETCONTENT = 0x014B,
		CB_FINDSTRING = 0x014C,
		CB_SELECTSTRING = 0x014D,
		CB_SETCURSEL = 0x014E,
		CB_SHOWDROPDOWN = 0x014F,
		CB_GETITEMDATA = 0x0150,
		CB_SETITEMDATA = 0x0151,
		CB_GETDROPPEDCONTROLRECT = 0x0152,
		CB_SETITEMHEIGHT = 0x0153,
		CB_GETITEMHEIGHT = 0x0154,
		CB_SETEXTENDEDUI = 0x0155,
		CB_GETEXTENDEDUI = 0x0156,
		CB_GETDROPPEDSTATE = 0x0157,
		CB_FINDSTRINGEXACT = 0x0158,
		CB_SETLOCALE = 0x0159,
		CB_GETLOCALE = 0x015A,
		CB_GETTOPINDEX = 0x015b,
		CB_SETTOPINDEX = 0x015c,
		CB_GETHORIZONTALEXTENT = 0x015d,
		CB_SETHORIZONTALEXTENT = 0x015e,
		CB_GETDROPPEDWIDTH = 0x015f,
		CB_SETDROPPEDWIDTH = 0x0160,
		CB_INITSTORAGE = 0x0161,
		CB_MSGMAX = 0x0162;
	// CB_MSGMAX = 0x015B;
	int CDS_UPDATEREGISTRY = 0x00000001,
		CDS_TEST = 0x00000002,
		CDS_FULLSCREEN = 0x00000004,
		CDS_GLOBAL = 0x00000008,
		CDS_SET_PRIMARY = 0x00000010,
		CDS_RESET = 0x40000000,
		CDS_SETRECT = 0x20000000,
		CDS_NORESET = 0x10000000,
		CBEN_FIRST = (0-800),
		CBEN_LAST = (0-830),
		CDRF_DODEFAULT = 0x00000000,
		CDRF_NEWFONT = 0x00000002,
		CDRF_SKIPDEFAULT = 0x00000004,
		CDRF_NOTIFYPOSTPAINT = 0x00000010,
		CDRF_NOTIFYITEMDRAW = 0x00000020,
		CDRF_NOTIFYPOSTERASE = 0x00000040,
		CDRF_NOTIFYITEMERASE = 0x00000080,
		CDDS_PREPAINT = 0x00000001,
		CDDS_POSTPAINT = 0x00000002,
		CDDS_PREERASE = 0x00000003,
		CDDS_POSTERASE = 0x00000004,
		CDDS_ITEM = 0x00010000,
		CDDS_ITEMPREPAINT = (0x00010000|0x00000001),
		CDDS_ITEMPOSTPAINT = (0x00010000|0x00000002),
		CDDS_ITEMPREERASE = (0x00010000|0x00000003),
		CDDS_ITEMPOSTERASE = (0x00010000|0x00000004),
		CDIS_SELECTED = 0x0001,
		CDIS_GRAYED = 0x0002,
		CDIS_DISABLED = 0x0004,
		CDIS_CHECKED = 0x0008,
		CDIS_FOCUS = 0x0010,
		CDIS_DEFAULT = 0x0020,
		CDIS_HOT = 0x0040,
		CLR_NONE = 0xFFFFFFFF,
		CLR_DEFAULT = 0xFF000000,
		CLR_HILIGHT = 0xFF000000,
		CMB_MASKED = 0x02,
		CCS_TOP = 0x00000001,
		CCS_NOMOVEY = 0x00000002,
		CCS_BOTTOM = 0x00000003,
		CCS_NORESIZE = 0x00000004,
		CCS_NOPARENTALIGN = 0x00000008,
		CCS_ADJUSTABLE = 0x00000020,
		CCS_NODIVIDER = 0x00000040,
		CCS_VERT = 0x00000080,
		CCS_LEFT = (0x00000080|0x00000001),
		CCS_RIGHT = (0x00000080|0x00000003),
		CCS_NOMOVEX = (0x00000080|0x00000002),
		CBEIF_TEXT = 0x00000001,
		CBEIF_IMAGE = 0x00000002,
		CBEIF_SELECTEDIMAGE = 0x00000004,
		CBEIF_OVERLAY = 0x00000008,
		CBEIF_INDENT = 0x00000010,
		CBEIF_LPARAM = 0x00000020,
		CBEIF_DI_SETITEM = 0x10000000,
		CBEM_INSERTITEMA = (0x0400+1),
		CBEM_SETIMAGELIST = (0x0400+2),
		CBEM_GETIMAGELIST = (0x0400+3),
		CBEM_GETITEMA = (0x0400+4),
		CBEM_SETITEMA = (0x0400+5),
		CBEM_DELETEITEM = 0x0144,
		CBEM_GETCOMBOCONTROL = (0x0400+6),
		CBEM_GETEDITCONTROL = (0x0400+7),
		CBEM_SETEXSTYLE = (0x0400+8),
		CBEM_GETEXSTYLE = (0x0400+9),
		CBEM_HASEDITCHANGED = (0x0400+10),
		CBEM_INSERTITEMW = (0x0400+11),
		CBEM_SETITEMW = (0x0400+12),
		CBEM_GETITEMW = (0x0400+13),
		CBES_EX_NOEDITIMAGE = 0x00000001,
		CBES_EX_NOEDITIMAGEINDENT = 0x00000002,
		CBES_EX_PATHWORDBREAKPROC = 0x00000004,
		CBEN_GETDISPINFO = ((0-800)-0),
		CBEN_INSERTITEM = ((0-800)-1),
		CBEN_DELETEITEM = ((0-800)-2),
		CBEN_BEGINEDIT = ((0-800)-4),
		CBEN_ENDEDITA = ((0-800)-5),
		CBEN_ENDEDITW = ((0-800)-6),
		CBENF_KILLFOCUS = 1,
		CBENF_RETURN = 2,
		CBENF_ESCAPE = 3,
		CBENF_DROPDOWN = 4,
		CBEMAXSTRLEN = 260,
		CDM_FIRST = (0x0400+100),
		CDM_LAST = (0x0400+200),
		CDM_GETSPEC = ((0x0400+100)+0x0000),
		CDM_GETFILEPATH = ((0x0400+100)+0x0001),
		CDM_GETFOLDERPATH = ((0x0400+100)+0x0002),
		CDM_GETFOLDERIDLIST = ((0x0400+100)+0x0003),
		CDM_SETCONTROLTEXT = ((0x0400+100)+0x0004),
		CDM_HIDECONTROL = ((0x0400+100)+0x0005),
		CDM_SETDEFEXT = ((0x0400+100)+0x0006),
		CONTROL_C_EXIT = (0xC000013A);

}
