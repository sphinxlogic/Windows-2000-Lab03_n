// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface wine {
	int EC_ENABLEALL = 0,
		EC_ENABLEONE = 0x0080,
		EC_DISABLE = 0x0008,
		EC_QUERYWAITING = 2,
		edt1 = 0x0480,
		edt2 = 0x0481,
		edt3 = 0x0482,
		edt4 = 0x0483,
		edt5 = 0x0484,
		edt6 = 0x0485,
		edt7 = 0x0486,
		edt8 = 0x0487,
		edt9 = 0x0488,
		edt10 = 0x0489,
		edt11 = 0x048a,
		edt12 = 0x048b,
		edt13 = 0x048c,
		edt14 = 0x048d,
		edt15 = 0x048e,
		edt16 = 0x048f,
		EXCEPTION_EXECUTE_HANDLER = 1,
		EXCEPTION_CONTINUE_SEARCH = 0,
		EXCEPTION_CONTINUE_EXECUTION = -1,
		EMBDHLP_INPROC_HANDLER = 0x0000,
		EMBDHLP_INPROC_SERVER = 0x0001,
		EMBDHLP_CREATENOW = 0x00000000,
		EMBDHLP_DELAYCREATE = 0x00010000,
		EXCEPTION_DEBUG_EVENT = 1,
		EXIT_THREAD_DEBUG_EVENT = 4,
		EXIT_PROCESS_DEBUG_EVENT = 5,
		EVENPARITY = 2,
		EV_RXCHAR = 0x0001,
		EV_RXFLAG = 0x0002,
		EV_TXEMPTY = 0x0004,
		EV_CTS = 0x0008,
		EV_DSR = 0x0010,
		EV_RLSD = 0x0020,
		EV_BREAK = 0x0040,
		EV_ERR = 0x0080,
		EV_RING = 0x0100,
		EV_PERR = 0x0200,
		EV_RX80FULL = 0x0400,
		EV_EVENT1 = 0x0800,
		EV_EVENT2 = 0x1000,
		ENHANCED_KEY = 0x0100,
		ENABLE_PROCESSED_INPUT = 0x0001,
		ENABLE_LINE_INPUT = 0x0002,
		ENABLE_ECHO_INPUT = 0x0004,
		ENABLE_WINDOW_INPUT = 0x0008,
		ENABLE_MOUSE_INPUT = 0x0010,
		ENABLE_PROCESSED_OUTPUT = 0x0001,
		ENABLE_WRAP_AT_EOL_OUTPUT = 0x0002,
		ERROR_SUCCESS = 0,
		ERROR_INVALID_FUNCTION = 1,
		ERROR_FILE_NOT_FOUND = 2,
		ERROR_PATH_NOT_FOUND = 3,
		ERROR_TOO_MANY_OPEN_FILES = 4,
		ERROR_ACCESS_DENIED = 5,
		ERROR_INVALID_HANDLE = 6,
		ERROR_ARENA_TRASHED = 7,
		ERROR_NOT_ENOUGH_MEMORY = 8,
		ERROR_INVALID_BLOCK = 9,
		ERROR_BAD_ENVIRONMENT = 10,
		ERROR_BAD_FORMAT = 11,
		ERROR_INVALID_ACCESS = 12,
		ERROR_INVALID_DATA = 13,
		ERROR_OUTOFMEMORY = 14,
		ERROR_INVALID_DRIVE = 15,
		ERROR_CURRENT_DIRECTORY = 16,
		ERROR_NOT_SAME_DEVICE = 17,
		ERROR_NO_MORE_FILES = 18,
		ERROR_WRITE_PROTECT = 19,
		ERROR_BAD_UNIT = 20,
		ERROR_NOT_READY = 21,
		ERROR_BAD_COMMAND = 22,
		ERROR_CRC = 23,
		ERROR_BAD_LENGTH = 24,
		ERROR_SEEK = 25,
		ERROR_NOT_DOS_DISK = 26,
		ERROR_SECTOR_NOT_FOUND = 27,
		ERROR_OUT_OF_PAPER = 28,
		ERROR_WRITE_FAULT = 29,
		ERROR_READ_FAULT = 30,
		ERROR_GEN_FAILURE = 31,
		ERROR_SHARING_VIOLATION = 32,
		ERROR_LOCK_VIOLATION = 33,
		ERROR_WRONG_DISK = 34,
		ERROR_SHARING_BUFFER_EXCEEDED = 36,
		ERROR_HANDLE_EOF = 38,
		ERROR_HANDLE_DISK_FULL = 39,
		ERROR_NOT_SUPPORTED = 50,
		ERROR_REM_NOT_LIST = 51,
		ERROR_DUP_NAME = 52,
		ERROR_BAD_NETPATH = 53,
		ERROR_NETWORK_BUSY = 54,
		ERROR_DEV_NOT_EXIST = 55,
		ERROR_TOO_MANY_CMDS = 56,
		ERROR_ADAP_HDW_ERR = 57,
		ERROR_BAD_NET_RESP = 58,
		ERROR_UNEXP_NET_ERR = 59,
		ERROR_BAD_REM_ADAP = 60,
		ERROR_PRINTQ_FULL = 61,
		ERROR_NO_SPOOL_SPACE = 62,
		ERROR_PRINT_CANCELLED = 63,
		ERROR_NETNAME_DELETED = 64,
		ERROR_NETWORK_ACCESS_DENIED = 65,
		ERROR_BAD_DEV_TYPE = 66,
		ERROR_BAD_NET_NAME = 67,
		ERROR_TOO_MANY_NAMES = 68,
		ERROR_TOO_MANY_SESS = 69,
		ERROR_SHARING_PAUSED = 70,
		ERROR_REQ_NOT_ACCEP = 71,
		ERROR_REDIR_PAUSED = 72,
		ERROR_FILE_EXISTS = 80,
		ERROR_CANNOT_MAKE = 82,
		ERROR_FAIL_I24 = 83,
		ERROR_OUT_OF_STRUCTURES = 84,
		ERROR_ALREADY_ASSIGNED = 85,
		ERROR_INVALID_PASSWORD = 86,
		ERROR_INVALID_PARAMETER = 87,
		ERROR_NET_WRITE_FAULT = 88,
		ERROR_NO_PROC_SLOTS = 89,
		ERROR_TOO_MANY_SEMAPHORES = 100,
		ERROR_EXCL_SEM_ALREADY_OWNED = 101,
		ERROR_SEM_IS_SET = 102,
		ERROR_TOO_MANY_SEM_REQUESTS = 103,
		ERROR_INVALID_AT_INTERRUPT_TIME = 104,
		ERROR_SEM_OWNER_DIED = 105,
		ERROR_SEM_USER_LIMIT = 106,
		ERROR_DISK_CHANGE = 107,
		ERROR_DRIVE_LOCKED = 108,
		ERROR_BROKEN_PIPE = 109,
		ERROR_OPEN_FAILED = 110,
		ERROR_BUFFER_OVERFLOW = 111,
		ERROR_DISK_FULL = 112,
		ERROR_NO_MORE_SEARCH_HANDLES = 113,
		ERROR_INVALID_TARGET_HANDLE = 114,
		ERROR_INVALID_CATEGORY = 117,
		ERROR_INVALID_VERIFY_SWITCH = 118,
		ERROR_BAD_DRIVER_LEVEL = 119,
		ERROR_CALL_NOT_IMPLEMENTED = 120,
		ERROR_SEM_TIMEOUT = 121,
		ERROR_INSUFFICIENT_BUFFER = 122,
		ERROR_INVALID_NAME = 123,
		ERROR_INVALID_LEVEL = 124,
		ERROR_NO_VOLUME_LABEL = 125,
		ERROR_MOD_NOT_FOUND = 126,
		ERROR_PROC_NOT_FOUND = 127,
		ERROR_WAIT_NO_CHILDREN = 128,
		ERROR_CHILD_NOT_COMPLETE = 129,
		ERROR_DIRECT_ACCESS_HANDLE = 130,
		ERROR_NEGATIVE_SEEK = 131,
		ERROR_SEEK_ON_DEVICE = 132,
		ERROR_IS_JOIN_TARGET = 133,
		ERROR_IS_JOINED = 134,
		ERROR_IS_SUBSTED = 135,
		ERROR_NOT_JOINED = 136,
		ERROR_NOT_SUBSTED = 137,
		ERROR_JOIN_TO_JOIN = 138,
		ERROR_SUBST_TO_SUBST = 139,
		ERROR_JOIN_TO_SUBST = 140,
		ERROR_SUBST_TO_JOIN = 141,
		ERROR_BUSY_DRIVE = 142,
		ERROR_SAME_DRIVE = 143,
		ERROR_DIR_NOT_ROOT = 144,
		ERROR_DIR_NOT_EMPTY = 145,
		ERROR_IS_SUBST_PATH = 146,
		ERROR_IS_JOIN_PATH = 147,
		ERROR_PATH_BUSY = 148,
		ERROR_IS_SUBST_TARGET = 149,
		ERROR_SYSTEM_TRACE = 150,
		ERROR_INVALID_EVENT_COUNT = 151,
		ERROR_TOO_MANY_MUXWAITERS = 152,
		ERROR_INVALID_LIST_FORMAT = 153,
		ERROR_LABEL_TOO_LONG = 154,
		ERROR_TOO_MANY_TCBS = 155,
		ERROR_SIGNAL_REFUSED = 156,
		ERROR_DISCARDED = 157,
		ERROR_NOT_LOCKED = 158,
		ERROR_BAD_THREADID_ADDR = 159,
		ERROR_BAD_ARGUMENTS = 160,
		ERROR_BAD_PATHNAME = 161,
		ERROR_SIGNAL_PENDING = 162,
		ERROR_MAX_THRDS_REACHED = 164,
		ERROR_LOCK_FAILED = 167,
		ERROR_BUSY = 170,
		ERROR_CANCEL_VIOLATION = 173,
		ERROR_ATOMIC_LOCKS_NOT_SUPPORTED = 174,
		ERROR_INVALID_SEGMENT_NUMBER = 180,
		ERROR_INVALID_ORDINAL = 182,
		ERROR_ALREADY_EXISTS = 183,
		ERROR_INVALID_FLAG_NUMBER = 186,
		ERROR_SEM_NOT_FOUND = 187,
		ERROR_INVALID_STARTING_CODESEG = 188,
		ERROR_INVALID_STACKSEG = 189,
		ERROR_INVALID_MODULETYPE = 190,
		ERROR_INVALID_EXE_SIGNATURE = 191,
		ERROR_EXE_MARKED_INVALID = 192,
		ERROR_BAD_EXE_FORMAT = 193,
		ERROR_ITERATED_DATA_EXCEEDS_64k = 194,
		ERROR_INVALID_MINALLOCSIZE = 195,
		ERROR_DYNLINK_FROM_INVALID_RING = 196,
		ERROR_IOPL_NOT_ENABLED = 197,
		ERROR_INVALID_SEGDPL = 198,
		ERROR_AUTODATASEG_EXCEEDS_64k = 199,
		ERROR_RING2SEG_MUST_BE_MOVABLE = 200,
		ERROR_RELOC_CHAIN_XEEDS_SEGLIM = 201,
		ERROR_INFLOOP_IN_RELOC_CHAIN = 202,
		ERROR_ENVVAR_NOT_FOUND = 203,
		ERROR_NO_SIGNAL_SENT = 205,
		ERROR_FILENAME_EXCED_RANGE = 206,
		ERROR_RING2_STACK_IN_USE = 207,
		ERROR_META_EXPANSION_TOO_LONG = 208,
		ERROR_INVALID_SIGNAL_NUMBER = 209,
		ERROR_THREAD_1_INACTIVE = 210,
		ERROR_LOCKED = 212,
		ERROR_TOO_MANY_MODULES = 214,
		ERROR_NESTING_NOT_ALLOWED = 215,
		ERROR_EXE_MACHINE_TYPE_MISMATCH = 216,
		ERROR_BAD_PIPE = 230,
		ERROR_PIPE_BUSY = 231,
		ERROR_NO_DATA = 232,
		ERROR_PIPE_NOT_CONNECTED = 233,
		ERROR_MORE_DATA = 234,
		ERROR_VC_DISCONNECTED = 240,
		ERROR_INVALID_EA_NAME = 254,
		ERROR_EA_LIST_INCONSISTENT = 255,
		ERROR_NO_MORE_ITEMS = 259,
		ERROR_CANNOT_COPY = 266,
		ERROR_DIRECTORY = 267,
		ERROR_EAS_DIDNT_FIT = 275,
		ERROR_EA_FILE_CORRUPT = 276,
		ERROR_EA_TABLE_FULL = 277,
		ERROR_INVALID_EA_HANDLE = 278,
		ERROR_EAS_NOT_SUPPORTED = 282,
		ERROR_NOT_OWNER = 288,
		ERROR_TOO_MANY_POSTS = 298,
		ERROR_PARTIAL_COPY = 299,
		ERROR_MR_MID_NOT_FOUND = 317,
		ERROR_INVALID_ADDRESS = 487,
		ERROR_ARITHMETIC_OVERFLOW = 534,
		ERROR_PIPE_CONNECTED = 535,
		ERROR_PIPE_LISTENING = 536,
		ERROR_EA_ACCESS_DENIED = 994,
		ERROR_OPERATION_ABORTED = 995,
		ERROR_IO_INCOMPLETE = 996,
		ERROR_IO_PENDING = 997,
		ERROR_NOACCESS = 998,
		ERROR_SWAPERROR = 999,
		ERROR_STACK_OVERFLOW = 1001,
		ERROR_INVALID_MESSAGE = 1002,
		ERROR_CAN_NOT_COMPLETE = 1003,
		ERROR_INVALID_FLAGS = 1004,
		ERROR_UNRECOGNIZED_VOLUME = 1005,
		ERROR_FILE_INVALID = 1006,
		ERROR_FULLSCREEN_MODE = 1007,
		ERROR_NO_TOKEN = 1008,
		ERROR_BADDB = 1009,
		ERROR_BADKEY = 1010,
		ERROR_CANTOPEN = 1011,
		ERROR_CANTREAD = 1012,
		ERROR_CANTWRITE = 1013,
		ERROR_REGISTRY_RECOVERED = 1014,
		ERROR_REGISTRY_CORRUPT = 1015,
		ERROR_REGISTRY_IO_FAILED = 1016,
		ERROR_NOT_REGISTRY_FILE = 1017,
		ERROR_KEY_DELETED = 1018,
		ERROR_NO_LOG_SPACE = 1019,
		ERROR_KEY_HAS_CHILDREN = 1020,
		ERROR_CHILD_MUST_BE_VOLATILE = 1021,
		ERROR_NOTIFY_ENUM_DIR = 1022,
		ERROR_DEPENDENT_SERVICES_RUNNING = 1051,
		ERROR_INVALID_SERVICE_CONTROL = 1052,
		ERROR_SERVICE_REQUEST_TIMEOUT = 1053,
		ERROR_SERVICE_NO_THREAD = 1054,
		ERROR_SERVICE_DATABASE_LOCKED = 1055,
		ERROR_SERVICE_ALREADY_RUNNING = 1056,
		ERROR_INVALID_SERVICE_ACCOUNT = 1057,
		ERROR_SERVICE_DISABLED = 1058,
		ERROR_CIRCULAR_DEPENDENCY = 1059,
		ERROR_SERVICE_DOES_NOT_EXIST = 1060,
		ERROR_SERVICE_CANNOT_ACCEPT_CTRL = 1061,
		ERROR_SERVICE_NOT_ACTIVE = 1062,
		ERROR_FAILED_SERVICE_CONTROLLER_CONNECT = 1063,
		ERROR_EXCEPTION_IN_SERVICE = 1064,
		ERROR_DATABASE_DOES_NOT_EXIST = 1065,
		ERROR_SERVICE_SPECIFIC_ERROR = 1066,
		ERROR_PROCESS_ABORTED = 1067,
		ERROR_SERVICE_DEPENDENCY_FAIL = 1068,
		ERROR_SERVICE_LOGON_FAILED = 1069,
		ERROR_SERVICE_START_HANG = 1070,
		ERROR_INVALID_SERVICE_LOCK = 1071,
		ERROR_SERVICE_MARKED_FOR_DELETE = 1072,
		ERROR_SERVICE_EXISTS = 1073,
		ERROR_ALREADY_RUNNING_LKG = 1074,
		ERROR_SERVICE_DEPENDENCY_DELETED = 1075,
		ERROR_BOOT_ALREADY_ACCEPTED = 1076,
		ERROR_SERVICE_NEVER_STARTED = 1077,
		ERROR_DUPLICATE_SERVICE_NAME = 1078,
		ERROR_DIFFERENT_SERVICE_ACCOUNT = 1079,
		ERROR_END_OF_MEDIA = 1100,
		ERROR_FILEMARK_DETECTED = 1101,
		ERROR_BEGINNING_OF_MEDIA = 1102,
		ERROR_SETMARK_DETECTED = 1103,
		ERROR_NO_DATA_DETECTED = 1104,
		ERROR_PARTITION_FAILURE = 1105,
		ERROR_INVALID_BLOCK_LENGTH = 1106,
		ERROR_DEVICE_NOT_PARTITIONED = 1107,
		ERROR_UNABLE_TO_LOCK_MEDIA = 1108,
		ERROR_UNABLE_TO_UNLOAD_MEDIA = 1109,
		ERROR_MEDIA_CHANGED = 1110,
		ERROR_BUS_RESET = 1111,
		ERROR_NO_MEDIA_IN_DRIVE = 1112,
		ERROR_NO_UNICODE_TRANSLATION = 1113,
		ERROR_DLL_INIT_FAILED = 1114,
		ERROR_SHUTDOWN_IN_PROGRESS = 1115,
		ERROR_NO_SHUTDOWN_IN_PROGRESS = 1116,
		ERROR_IO_DEVICE = 1117,
		ERROR_SERIAL_NO_DEVICE = 1118,
		ERROR_IRQ_BUSY = 1119,
		ERROR_MORE_WRITES = 1120,
		ERROR_COUNTER_TIMEOUT = 1121,
		ERROR_FLOPPY_ID_MARK_NOT_FOUND = 1122,
		ERROR_FLOPPY_WRONG_CYLINDER = 1123,
		ERROR_FLOPPY_UNKNOWN_ERROR = 1124,
		ERROR_FLOPPY_BAD_REGISTERS = 1125,
		ERROR_DISK_RECALIBRATE_FAILED = 1126,
		ERROR_DISK_OPERATION_FAILED = 1127,
		ERROR_DISK_RESET_FAILED = 1128,
		ERROR_EOM_OVERFLOW = 1129,
		ERROR_NOT_ENOUGH_SERVER_MEMORY = 1130,
		ERROR_POSSIBLE_DEADLOCK = 1131,
		ERROR_MAPPED_ALIGNMENT = 1132,
		ERROR_SET_POWER_STATE_VETOED = 1140,
		ERROR_SET_POWER_STATE_FAILED = 1141,
		ERROR_TOO_MANY_LINKS = 1142,
		ERROR_OLD_WIN_VERSION = 1150,
		ERROR_APP_WRONG_OS = 1151,
		ERROR_SINGLE_INSTANCE_APP = 1152,
		ERROR_RMODE_APP = 1153,
		ERROR_INVALID_DLL = 1154,
		ERROR_NO_ASSOCIATION = 1155,
		ERROR_DDE_FAIL = 1156,
		ERROR_DLL_NOT_FOUND = 1157,
		ERROR_BAD_USERNAME = 2202,
		ERROR_NOT_CONNECTED = 2250,
		ERROR_OPEN_FILES = 2401,
		ERROR_ACTIVE_CONNECTIONS = 2402,
		ERROR_DEVICE_IN_USE = 2404,
		ERROR_BAD_DEVICE = 1200,
		ERROR_CONNECTION_UNAVAIL = 1201,
		ERROR_DEVICE_ALREADY_REMEMBERED = 1202,
		ERROR_NO_NET_OR_BAD_PATH = 1203,
		ERROR_BAD_PROVIDER = 1204,
		ERROR_CANNOT_OPEN_PROFILE = 1205,
		ERROR_BAD_PROFILE = 1206,
		ERROR_NOT_CONTAINER = 1207,
		ERROR_EXTENDED_ERROR = 1208,
		ERROR_INVALID_GROUPNAME = 1209,
		ERROR_INVALID_COMPUTERNAME = 1210,
		ERROR_INVALID_EVENTNAME = 1211,
		ERROR_INVALID_DOMAINNAME = 1212,
		ERROR_INVALID_SERVICENAME = 1213,
		ERROR_INVALID_NETNAME = 1214,
		ERROR_INVALID_SHARENAME = 1215,
		ERROR_INVALID_PASSWORDNAME = 1216,
		ERROR_INVALID_MESSAGENAME = 1217,
		ERROR_INVALID_MESSAGEDEST = 1218,
		ERROR_SESSION_CREDENTIAL_CONFLICT = 1219,
		ERROR_REMOTE_SESSION_LIMIT_EXCEEDED = 1220,
		ERROR_DUP_DOMAINNAME = 1221,
		ERROR_NO_NETWORK = 1222,
		ERROR_CANCELLED = 1223,
		ERROR_USER_MAPPED_FILE = 1224,
		ERROR_CONNECTION_REFUSED = 1225,
		ERROR_GRACEFUL_DISCONNECT = 1226,
		ERROR_ADDRESS_ALREADY_ASSOCIATED = 1227,
		ERROR_ADDRESS_NOT_ASSOCIATED = 1228,
		ERROR_CONNECTION_INVALID = 1229,
		ERROR_CONNECTION_ACTIVE = 1230,
		ERROR_NETWORK_UNREACHABLE = 1231,
		ERROR_HOST_UNREACHABLE = 1232,
		ERROR_PROTOCOL_UNREACHABLE = 1233,
		ERROR_PORT_UNREACHABLE = 1234,
		ERROR_REQUEST_ABORTED = 1235,
		ERROR_CONNECTION_ABORTED = 1236,
		ERROR_RETRY = 1237,
		ERROR_CONNECTION_COUNT_LIMIT = 1238,
		ERROR_LOGIN_TIME_RESTRICTION = 1239,
		ERROR_LOGIN_WKSTA_RESTRICTION = 1240,
		ERROR_INCORRECT_ADDRESS = 1241,
		ERROR_ALREADY_REGISTERED = 1242,
		ERROR_SERVICE_NOT_FOUND = 1243,
		ERROR_NOT_AUTHENTICATED = 1244,
		ERROR_NOT_LOGGED_ON = 1245,
		ERROR_CONTINUE = 1246,
		ERROR_ALREADY_INITIALIZED = 1247,
		ERROR_NO_MORE_DEVICES = 1248,
		ERROR_NOT_ALL_ASSIGNED = 1300,
		ERROR_SOME_NOT_MAPPED = 1301,
		ERROR_NO_QUOTAS_FOR_ACCOUNT = 1302,
		ERROR_LOCAL_USER_SESSION_KEY = 1303,
		ERROR_NULL_LM_PASSWORD = 1304,
		ERROR_UNKNOWN_REVISION = 1305,
		ERROR_REVISION_MISMATCH = 1306,
		ERROR_INVALID_OWNER = 1307,
		ERROR_INVALID_PRIMARY_GROUP = 1308,
		ERROR_NO_IMPERSONATION_TOKEN = 1309,
		ERROR_CANT_DISABLE_MANDATORY = 1310,
		ERROR_NO_LOGON_SERVERS = 1311,
		ERROR_NO_SUCH_LOGON_SESSION = 1312,
		ERROR_NO_SUCH_PRIVILEGE = 1313,
		ERROR_PRIVILEGE_NOT_HELD = 1314,
		ERROR_INVALID_ACCOUNT_NAME = 1315,
		ERROR_USER_EXISTS = 1316,
		ERROR_NO_SUCH_USER = 1317,
		ERROR_GROUP_EXISTS = 1318,
		ERROR_NO_SUCH_GROUP = 1319,
		ERROR_MEMBER_IN_GROUP = 1320,
		ERROR_MEMBER_NOT_IN_GROUP = 1321,
		ERROR_LAST_ADMIN = 1322,
		ERROR_WRONG_PASSWORD = 1323,
		ERROR_ILL_FORMED_PASSWORD = 1324,
		ERROR_PASSWORD_RESTRICTION = 1325,
		ERROR_LOGON_FAILURE = 1326,
		ERROR_ACCOUNT_RESTRICTION = 1327,
		ERROR_INVALID_LOGON_HOURS = 1328,
		ERROR_INVALID_WORKSTATION = 1329,
		ERROR_PASSWORD_EXPIRED = 1330,
		ERROR_ACCOUNT_DISABLED = 1331,
		ERROR_NONE_MAPPED = 1332,
		ERROR_TOO_MANY_LUIDS_REQUESTED = 1333,
		ERROR_LUIDS_EXHAUSTED = 1334,
		ERROR_INVALID_SUB_AUTHORITY = 1335,
		ERROR_INVALID_ACL = 1336,
		ERROR_INVALID_SID = 1337,
		ERROR_INVALID_SECURITY_DESCR = 1338,
		ERROR_BAD_INHERITANCE_ACL = 1340,
		ERROR_SERVER_DISABLED = 1341,
		ERROR_SERVER_NOT_DISABLED = 1342,
		ERROR_INVALID_ID_AUTHORITY = 1343,
		ERROR_ALLOTTED_SPACE_EXCEEDED = 1344,
		ERROR_INVALID_GROUP_ATTRIBUTES = 1345,
		ERROR_BAD_IMPERSONATION_LEVEL = 1346,
		ERROR_CANT_OPEN_ANONYMOUS = 1347,
		ERROR_BAD_VALIDATION_CLASS = 1348,
		ERROR_BAD_TOKEN_TYPE = 1349,
		ERROR_NO_SECURITY_ON_OBJECT = 1350,
		ERROR_CANT_ACCESS_DOMAIN_INFO = 1351,
		ERROR_INVALID_SERVER_STATE = 1352,
		ERROR_INVALID_DOMAIN_STATE = 1353,
		ERROR_INVALID_DOMAIN_ROLE = 1354,
		ERROR_NO_SUCH_DOMAIN = 1355,
		ERROR_DOMAIN_EXISTS = 1356,
		ERROR_DOMAIN_LIMIT_EXCEEDED = 1357,
		ERROR_INTERNAL_DB_CORRUPTION = 1358,
		ERROR_INTERNAL_ERROR = 1359,
		ERROR_GENERIC_NOT_MAPPED = 1360,
		ERROR_BAD_DESCRIPTOR_FORMAT = 1361,
		ERROR_NOT_LOGON_PROCESS = 1362,
		ERROR_LOGON_SESSION_EXISTS = 1363,
		ERROR_NO_SUCH_PACKAGE = 1364,
		ERROR_BAD_LOGON_SESSION_STATE = 1365,
		ERROR_LOGON_SESSION_COLLISION = 1366,
		ERROR_INVALID_LOGON_TYPE = 1367,
		ERROR_CANNOT_IMPERSONATE = 1368,
		ERROR_RXACT_INVALID_STATE = 1369,
		ERROR_RXACT_COMMIT_FAILURE = 1370,
		ERROR_SPECIAL_ACCOUNT = 1371,
		ERROR_SPECIAL_GROUP = 1372,
		ERROR_SPECIAL_USER = 1373,
		ERROR_MEMBERS_PRIMARY_GROUP = 1374,
		ERROR_TOKEN_ALREADY_IN_USE = 1375,
		ERROR_NO_SUCH_ALIAS = 1376,
		ERROR_MEMBER_NOT_IN_ALIAS = 1377,
		ERROR_MEMBER_IN_ALIAS = 1378,
		ERROR_ALIAS_EXISTS = 1379,
		ERROR_LOGON_NOT_GRANTED = 1380,
		ERROR_TOO_MANY_SECRETS = 1381,
		ERROR_SECRET_TOO_LONG = 1382,
		ERROR_INTERNAL_DB_ERROR = 1383,
		ERROR_TOO_MANY_CONTEXT_IDS = 1384,
		ERROR_LOGON_TYPE_NOT_GRANTED = 1385,
		ERROR_NT_CROSS_ENCRYPTION_REQUIRED = 1386,
		ERROR_NO_SUCH_MEMBER = 1387,
		ERROR_INVALID_MEMBER = 1388,
		ERROR_TOO_MANY_SIDS = 1389,
		ERROR_LM_CROSS_ENCRYPTION_REQUIRED = 1390,
		ERROR_NO_INHERITANCE = 1391,
		ERROR_FILE_CORRUPT = 1392,
		ERROR_DISK_CORRUPT = 1393,
		ERROR_NO_USER_SESSION_KEY = 1394,
		ERROR_LICENSE_QUOTA_EXCEEDED = 1395,
		ERROR_INVALID_WINDOW_HANDLE = 1400,
		ERROR_INVALID_MENU_HANDLE = 1401,
		ERROR_INVALID_CURSOR_HANDLE = 1402,
		ERROR_INVALID_ACCEL_HANDLE = 1403,
		ERROR_INVALID_HOOK_HANDLE = 1404,
		ERROR_INVALID_DWP_HANDLE = 1405,
		ERROR_TLW_WITH_WSCHILD = 1406,
		ERROR_CANNOT_FIND_WND_CLASS = 1407,
		ERROR_WINDOW_OF_OTHER_THREAD = 1408,
		ERROR_HOTKEY_ALREADY_REGISTERED = 1409,
		ERROR_CLASS_ALREADY_EXISTS = 1410,
		ERROR_CLASS_DOES_NOT_EXIST = 1411,
		ERROR_CLASS_HAS_WINDOWS = 1412,
		ERROR_INVALID_INDEX = 1413,
		ERROR_INVALID_ICON_HANDLE = 1414,
		ERROR_PRIVATE_DIALOG_INDEX = 1415,
		ERROR_LISTBOX_ID_NOT_FOUND = 1416,
		ERROR_NO_WILDCARD_CHARACTERS = 1417,
		ERROR_CLIPBOARD_NOT_OPEN = 1418,
		ERROR_HOTKEY_NOT_REGISTERED = 1419,
		ERROR_WINDOW_NOT_DIALOG = 1420,
		ERROR_CONTROL_ID_NOT_FOUND = 1421,
		ERROR_INVALID_COMBOBOX_MESSAGE = 1422,
		ERROR_WINDOW_NOT_COMBOBOX = 1423,
		ERROR_INVALID_EDIT_HEIGHT = 1424,
		ERROR_DC_NOT_FOUND = 1425,
		ERROR_INVALID_HOOK_FILTER = 1426,
		ERROR_INVALID_FILTER_PROC = 1427,
		ERROR_HOOK_NEEDS_HMOD = 1428,
		ERROR_GLOBAL_ONLY_HOOK = 1429,
		ERROR_JOURNAL_HOOK_SET = 1430,
		ERROR_HOOK_NOT_INSTALLED = 1431,
		ERROR_INVALID_LB_MESSAGE = 1432,
		ERROR_SETCOUNT_ON_BAD_LB = 1433,
		ERROR_LB_WITHOUT_TABSTOPS = 1434,
		ERROR_DESTROY_OBJECT_OF_OTHER_THREAD = 1435,
		ERROR_CHILD_WINDOW_MENU = 1436,
		ERROR_NO_SYSTEM_MENU = 1437,
		ERROR_INVALID_MSGBOX_STYLE = 1438,
		ERROR_INVALID_SPI_VALUE = 1439,
		ERROR_SCREEN_ALREADY_LOCKED = 1440,
		ERROR_HWNDS_HAVE_DIFF_PARENT = 1441,
		ERROR_NOT_CHILD_WINDOW = 1442,
		ERROR_INVALID_GW_COMMAND = 1443,
		ERROR_INVALID_THREAD_ID = 1444,
		ERROR_NON_MDICHILD_WINDOW = 1445,
		ERROR_POPUP_ALREADY_ACTIVE = 1446,
		ERROR_NO_SCROLLBARS = 1447,
		ERROR_INVALID_SCROLLBAR_RANGE = 1448,
		ERROR_INVALID_SHOWWIN_COMMAND = 1449,
		ERROR_NO_SYSTEM_RESOURCES = 1450,
		ERROR_NONPAGED_SYSTEM_RESOURCES = 1451,
		ERROR_PAGED_SYSTEM_RESOURCES = 1452,
		ERROR_WORKING_SET_QUOTA = 1453,
		ERROR_PAGEFILE_QUOTA = 1454,
		ERROR_COMMITMENT_LIMIT = 1455,
		ERROR_MENU_ITEM_NOT_FOUND = 1456,
		ERROR_INVALID_KEYBOARD_HANDLE = 1457,
		ERROR_HOOK_TYPE_NOT_ALLOWED = 1458,
		ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION = 1459,
		ERROR_TIMEOUT = 1460,
		ERROR_EVENTLOG_FILE_CORRUPT = 1500,
		ERROR_EVENTLOG_CANT_START = 1501,
		ERROR_LOG_FILE_FULL = 1502,
		ERROR_EVENTLOG_FILE_CHANGED = 1503,
		EPT_S_INVALID_ENTRY = 1751,
		EPT_S_CANT_PERFORM_OP = 1752,
		EPT_S_NOT_REGISTERED = 1753,
		ERROR_INVALID_USER_BUFFER = 1784,
		ERROR_UNRECOGNIZED_MEDIA = 1785,
		ERROR_NO_TRUST_LSA_SECRET = 1786,
		ERROR_NO_TRUST_SAM_ACCOUNT = 1787,
		ERROR_TRUSTED_DOMAIN_FAILURE = 1788,
		ERROR_TRUSTED_RELATIONSHIP_FAILURE = 1789,
		ERROR_TRUST_FAILURE = 1790,
		ERROR_NETLOGON_NOT_STARTED = 1792,
		ERROR_ACCOUNT_EXPIRED = 1793,
		ERROR_REDIRECTOR_HAS_OPEN_HANDLES = 1794,
		ERROR_PRINTER_DRIVER_ALREADY_INSTALLED = 1795,
		ERROR_UNKNOWN_PORT = 1796,
		ERROR_UNKNOWN_PRINTER_DRIVER = 1797,
		ERROR_UNKNOWN_PRINTPROCESSOR = 1798,
		ERROR_INVALID_SEPARATOR_FILE = 1799,
		ERROR_INVALID_PRIORITY = 1800,
		ERROR_INVALID_PRINTER_NAME = 1801,
		ERROR_PRINTER_ALREADY_EXISTS = 1802,
		ERROR_INVALID_PRINTER_COMMAND = 1803,
		ERROR_INVALID_DATATYPE = 1804,
		ERROR_INVALID_ENVIRONMENT = 1805,
		ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT = 1807,
		ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT = 1808,
		ERROR_NOLOGON_SERVER_TRUST_ACCOUNT = 1809,
		ERROR_DOMAIN_TRUST_INCONSISTENT = 1810,
		ERROR_SERVER_HAS_OPEN_HANDLES = 1811,
		ERROR_RESOURCE_DATA_NOT_FOUND = 1812,
		ERROR_RESOURCE_TYPE_NOT_FOUND = 1813,
		ERROR_RESOURCE_NAME_NOT_FOUND = 1814,
		ERROR_RESOURCE_LANG_NOT_FOUND = 1815,
		ERROR_NOT_ENOUGH_QUOTA = 1816,
		EPT_S_CANT_CREATE = 1899,
		ERROR_INVALID_TIME = 1901,
		ERROR_INVALID_FORM_NAME = 1902,
		ERROR_INVALID_FORM_SIZE = 1903,
		ERROR_ALREADY_WAITING = 1904,
		ERROR_PRINTER_DELETED = 1905,
		ERROR_INVALID_PRINTER_STATE = 1906,
		ERROR_PASSWORD_MUST_CHANGE = 1907,
		ERROR_DOMAIN_CONTROLLER_NOT_FOUND = 1908,
		ERROR_ACCOUNT_LOCKED_OUT = 1909,
		ERROR_NO_BROWSER_SERVERS_FOUND = 6118,
		ERROR_INVALID_PIXEL_FORMAT = 2000,
		ERROR_BAD_DRIVER = 2001,
		ERROR_INVALID_WINDOW_STYLE = 2002,
		ERROR_METAFILE_NOT_SUPPORTED = 2003,
		ERROR_TRANSFORM_NOT_SUPPORTED = 2004,
		ERROR_CLIPPING_NOT_SUPPORTED = 2005,
		ERROR_UNKNOWN_PRINT_MONITOR = 3000,
		ERROR_PRINTER_DRIVER_IN_USE = 3001,
		ERROR_SPOOL_FILE_NOT_FOUND = 3002,
		ERROR_SPL_NO_STARTDOC = 3003,
		ERROR_SPL_NO_ADDJOB = 3004,
		ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED = 3005,
		ERROR_PRINT_MONITOR_ALREADY_INSTALLED = 3006,
		ERROR_INVALID_PRINT_MONITOR = 3007,
		ERROR_PRINT_MONITOR_IN_USE = 3008,
		ERROR_PRINTER_HAS_JOBS_QUEUED = 3009,
		ERROR_SUCCESS_REBOOT_REQUIRED = 3010,
		ERROR_SUCCESS_RESTART_REQUIRED = 3011,
		ERROR_WINS_INTERNAL = 4000,
		ERROR_CAN_NOT_DEL_LOCAL_WINS = 4001,
		ERROR_STATIC_INIT = 4002,
		ERROR_INC_BACKUP = 4003,
		ERROR_FULL_BACKUP = 4004,
		ERROR_REC_NON_EXISTENT = 4005,
		ERROR_RPL_NOT_ALLOWED = 4006,
		E_UNEXPECTED = 0x8000FFFF,
		E_NOTIMPL = 0x80004001,
		E_OUTOFMEMORY = 0x8007000E,
		E_INVALIDARG = 0x80070057,
		E_NOINTERFACE = 0x80004002,
		E_POINTER = 0x80004003,
		E_HANDLE = 0x80070006,
		E_ABORT = 0x80004004,
		E_FAIL = 0x80004005,
		E_ACCESSDENIED = 0x80070005;
	// E_NOTIMPL = 0x80000001;
	// int E_OUTOFMEMORY = 0x80000002;
	// int E_INVALIDARG = 0x80000003;
	// int E_NOINTERFACE = 0x80000004;
	// int E_POINTER = 0x80000005;
	// int E_HANDLE = 0x80000006;
	// int E_ABORT = 0x80000007;
	// int E_FAIL = 0x80000008;
	// int E_ACCESSDENIED = 0x80000009;
	int E_PENDING = 0x8000000A,
		ENUM_E_FIRST = 0x800401B0,
		ENUM_E_LAST = 0x800401BF,
		ENUM_S_FIRST = 0x000401B0,
		ENUM_S_LAST = 0x000401BF,
		ERROR = 0,
		ETO_OPAQUE = 0x0002,
		ETO_CLIPPED = 0x0004,
		ETO_GLYPH_INDEX = 0x0010,
		ETO_RTLREADING = 0x0080,
		ETO_IGNORELANGUAGE = 0x1000,
		ENDDOC = 11,
		ENABLEDUPLEX = 28,
		ENUMPAPERBINS = 31,
		EPSPRINTING = 33,
		ENUMPAPERMETRICS = 34,
		EXTTEXTOUT = 512,
		ENABLERELATIVEWIDTHS = 768,
		ENABLEPAIRKERNING = 769,
		END_PATH = 4098,
		EXT_DEVICE_CAPS = 4099,
		ENCAPSULATED_POSTSCRIPT = 4116,
		EASTEUROPE_CHARSET = 238,
		ELF_VENDOR_SIZE = 4,
		ELF_VERSION = 0,
		ELF_CULTURE_LATIN = 0,
		ENHMETA_SIGNATURE = 0x464D4520,
		ENHMETA_STOCK_OBJECT = 0x80000000,
		EMR_HEADER = 1,
		EMR_POLYBEZIER = 2,
		EMR_POLYGON = 3,
		EMR_POLYLINE = 4,
		EMR_POLYBEZIERTO = 5,
		EMR_POLYLINETO = 6,
		EMR_POLYPOLYLINE = 7,
		EMR_POLYPOLYGON = 8,
		EMR_SETWINDOWEXTEX = 9,
		EMR_SETWINDOWORGEX = 10,
		EMR_SETVIEWPORTEXTEX = 11,
		EMR_SETVIEWPORTORGEX = 12,
		EMR_SETBRUSHORGEX = 13,
		EMR_EOF = 14,
		EMR_SETPIXELV = 15,
		EMR_SETMAPPERFLAGS = 16,
		EMR_SETMAPMODE = 17,
		EMR_SETBKMODE = 18,
		EMR_SETPOLYFILLMODE = 19,
		EMR_SETROP2 = 20,
		EMR_SETSTRETCHBLTMODE = 21,
		EMR_SETTEXTALIGN = 22,
		EMR_SETCOLORADJUSTMENT = 23,
		EMR_SETTEXTCOLOR = 24,
		EMR_SETBKCOLOR = 25,
		EMR_OFFSETCLIPRGN = 26,
		EMR_MOVETOEX = 27,
		EMR_SETMETARGN = 28,
		EMR_EXCLUDECLIPRECT = 29,
		EMR_INTERSECTCLIPRECT = 30,
		EMR_SCALEVIEWPORTEXTEX = 31,
		EMR_SCALEWINDOWEXTEX = 32,
		EMR_SAVEDC = 33,
		EMR_RESTOREDC = 34,
		EMR_SETWORLDTRANSFORM = 35,
		EMR_MODIFYWORLDTRANSFORM = 36,
		EMR_SELECTOBJECT = 37,
		EMR_CREATEPEN = 38,
		EMR_CREATEBRUSHINDIRECT = 39,
		EMR_DELETEOBJECT = 40,
		EMR_ANGLEARC = 41,
		EMR_ELLIPSE = 42,
		EMR_RECTANGLE = 43,
		EMR_ROUNDRECT = 44,
		EMR_ARC = 45,
		EMR_CHORD = 46,
		EMR_PIE = 47,
		EMR_SELECTPALETTE = 48,
		EMR_CREATEPALETTE = 49,
		EMR_SETPALETTEENTRIES = 50,
		EMR_RESIZEPALETTE = 51,
		EMR_REALIZEPALETTE = 52,
		EMR_EXTFLOODFILL = 53,
		EMR_LINETO = 54,
		EMR_ARCTO = 55,
		EMR_POLYDRAW = 56,
		EMR_SETARCDIRECTION = 57,
		EMR_SETMITERLIMIT = 58,
		EMR_BEGINPATH = 59,
		EMR_ENDPATH = 60,
		EMR_CLOSEFIGURE = 61,
		EMR_FILLPATH = 62,
		EMR_STROKEANDFILLPATH = 63,
		EMR_STROKEPATH = 64,
		EMR_FLATTENPATH = 65,
		EMR_WIDENPATH = 66,
		EMR_SELECTCLIPPATH = 67,
		EMR_ABORTPATH = 68,
		EMR_GDICOMMENT = 70,
		EMR_FILLRGN = 71,
		EMR_FRAMERGN = 72,
		EMR_INVERTRGN = 73,
		EMR_PAINTRGN = 74,
		EMR_EXTSELECTCLIPRGN = 75,
		EMR_BITBLT = 76,
		EMR_STRETCHBLT = 77,
		EMR_MASKBLT = 78,
		EMR_PLGBLT = 79,
		EMR_SETDIBITSTODEVICE = 80,
		EMR_STRETCHDIBITS = 81,
		EMR_EXTCREATEFONTINDIRECTW = 82,
		EMR_EXTTEXTOUTA = 83,
		EMR_EXTTEXTOUTW = 84,
		EMR_POLYBEZIER16 = 85,
		EMR_POLYGON16 = 86,
		EMR_POLYLINE16 = 87,
		EMR_POLYBEZIERTO16 = 88,
		EMR_POLYLINETO16 = 89,
		EMR_POLYPOLYLINE16 = 90,
		EMR_POLYPOLYGON16 = 91,
		EMR_POLYDRAW16 = 92,
		EMR_CREATEMONOBRUSH = 93,
		EMR_CREATEDIBPATTERNBRUSHPT = 94,
		EMR_EXTCREATEPEN = 95,
		EMR_POLYTEXTOUTA = 96,
		EMR_POLYTEXTOUTW = 97,
		EMR_SETICMMODE = 98,
		EMR_CREATECOLORSPACE = 99,
		EMR_SETCOLORSPACE = 100,
		EMR_DELETECOLORSPACE = 101,
		EMR_GLSRECORD = 102,
		EMR_GLSBOUNDEDRECORD = 103,
		EMR_PIXELFORMAT = 104,
		EMR_MIN = 1,
		EMR_MAX = 104;
	// EMR_MAX = 97;
	int EPS_SIGNATURE = 0x46535045,
		ENUM_ALL_CALENDARS = 0xffffffff,
		ERROR_SEVERITY_SUCCESS = 0x00000000,
		ERROR_SEVERITY_INFORMATIONAL = 0x40000000,
		ERROR_SEVERITY_WARNING = 0x80000000,
		ERROR_SEVERITY_ERROR = 0xC0000000,
		EXCEPTION_NONCONTINUABLE = 0x1,
		EXCEPTION_MAXIMUM_PARAMETERS = 15,
		EVENT_MODIFY_STATE = 0x0002,
		EVENTLOG_SEQUENTIAL_READ = 0X0001,
		EVENTLOG_SEEK_READ = 0X0002,
		EVENTLOG_FORWARDS_READ = 0X0004,
		EVENTLOG_BACKWARDS_READ = 0X0008,
		EVENTLOG_SUCCESS = 0X0000,
		EVENTLOG_ERROR_TYPE = 0x0001,
		EVENTLOG_WARNING_TYPE = 0x0002,
		EVENTLOG_INFORMATION_TYPE = 0x0004,
		EVENTLOG_AUDIT_SUCCESS = 0x0008,
		EVENTLOG_AUDIT_FAILURE = 0x0010,
		EVENTLOG_START_PAIRED_EVENT = 0x0001,
		EVENTLOG_END_PAIRED_EVENT = 0x0002,
		EVENTLOG_END_ALL_PAIRED_EVENTS = 0x0004,
		EVENTLOG_PAIRED_EVENT_ACTIVE = 0x0008,
		EVENTLOG_PAIRED_EVENT_INACTIVE = 0x0010,
		EDGE_RAISED = (0x0001|0x0004),
		EDGE_SUNKEN = (0x0002|0x0008),
		EDGE_ETCHED = (0x0002|0x0004),
		EDGE_BUMP = (0x0001|0x0008),
		EW_RESTARTWINDOWS = 0x0042,
		EW_REBOOTSYSTEM = 0x0043,
		EW_EXITANDEXECAPP = 0x0044,
		ENDSESSION_LOGOFF = 0x80000000,
		EWX_LOGOFF = 0,
		EWX_SHUTDOWN = 1,
		EWX_REBOOT = 2,
		EWX_FORCE = 4,
		EWX_POWEROFF = 8,
		ESB_ENABLE_BOTH = 0x0000,
		ESB_DISABLE_BOTH = 0x0003,
		ESB_DISABLE_LEFT = 0x0001,
		ESB_DISABLE_RIGHT = 0x0002,
		ESB_DISABLE_UP = 0x0001,
		ESB_DISABLE_DOWN = 0x0002,
		ESB_DISABLE_LTUP = 0x0001,
		ESB_DISABLE_RTDN = 0x0002,
		ES_LEFT = 0x0000,
		ES_CENTER = 0x0001,
		ES_RIGHT = 0x0002,
		ES_MULTILINE = 0x0004,
		ES_UPPERCASE = 0x0008,
		ES_LOWERCASE = 0x0010,
		ES_PASSWORD = 0x0020,
		ES_AUTOVSCROLL = 0x0040,
		ES_AUTOHSCROLL = 0x0080,
		ES_NOHIDESEL = 0x0100,
		ES_OEMCONVERT = 0x0400,
		ES_READONLY = 0x0800,
		ES_WANTRETURN = 0x1000,
		ES_NUMBER = 0x2000,
		EN_SETFOCUS = 0x0100,
		EN_KILLFOCUS = 0x0200,
		EN_CHANGE = 0x0300,
		EN_UPDATE = 0x0400,
		EN_ERRSPACE = 0x0500,
		EN_MAXTEXT = 0x0501,
		EN_HSCROLL = 0x0601,
		EN_VSCROLL = 0x0602,
		EC_LEFTMARGIN = 0x0001,
		EC_RIGHTMARGIN = 0x0002,
		EC_USEFONTINFO = 0xffff,
		EM_GETSEL = 0x00B0,
		EM_SETSEL = 0x00B1,
		EM_GETRECT = 0x00B2,
		EM_SETRECT = 0x00B3,
		EM_SETRECTNP = 0x00B4,
		EM_SCROLL = 0x00B5,
		EM_LINESCROLL = 0x00B6,
		EM_SCROLLCARET = 0x00B7,
		EM_GETMODIFY = 0x00B8,
		EM_SETMODIFY = 0x00B9,
		EM_GETLINECOUNT = 0x00BA,
		EM_LINEINDEX = 0x00BB,
		EM_SETHANDLE = 0x00BC,
		EM_GETHANDLE = 0x00BD,
		EM_GETTHUMB = 0x00BE,
		EM_LINELENGTH = 0x00C1,
		EM_REPLACESEL = 0x00C2,
		EM_GETLINE = 0x00C4,
		EM_LIMITTEXT = 0x00C5,
		EM_CANUNDO = 0x00C6,
		EM_UNDO = 0x00C7,
		EM_FMTLINES = 0x00C8,
		EM_LINEFROMCHAR = 0x00C9,
		EM_SETTABSTOPS = 0x00CB,
		EM_SETPASSWORDCHAR = 0x00CC,
		EM_EMPTYUNDOBUFFER = 0x00CD,
		EM_GETFIRSTVISIBLELINE = 0x00CE,
		EM_SETREADONLY = 0x00CF,
		EM_SETWORDBREAKPROC = 0x00D0,
		EM_GETWORDBREAKPROC = 0x00D1,
		EM_GETPASSWORDCHAR = 0x00D2,
		EM_SETMARGINS = 0x00D3,
		EM_GETMARGINS = 0x00D4,
		EM_SETLIMITTEXT = 0x00C5,
		EM_GETLIMITTEXT = 0x00D5,
		EM_POSFROMCHAR = 0x00D6,
		EM_CHARFROMPOS = 0x00D7,
		ENUM_CURRENT_SETTINGS = (-1),
		ENUM_REGISTRY_SETTINGS = (-2),
		E_DRAW = 0x80040140,
		EXCEPTION_ACCESS_VIOLATION = (0xC0000005),
		EXCEPTION_DATATYPE_MISALIGNMENT = (0x80000002),
		EXCEPTION_BREAKPOINT = (0x80000003),
		EXCEPTION_SINGLE_STEP = (0x80000004),
		EXCEPTION_ARRAY_BOUNDS_EXCEEDED = (0xC000008C),
		EXCEPTION_FLT_DENORMAL_OPERAND = (0xC000008D),
		EXCEPTION_FLT_DIVIDE_BY_ZERO = (0xC000008E),
		EXCEPTION_FLT_INEXACT_RESULT = (0xC000008F),
		EXCEPTION_FLT_INVALID_OPERATION = (0xC0000090),
		EXCEPTION_FLT_OVERFLOW = (0xC0000091),
		EXCEPTION_FLT_STACK_CHECK = (0xC0000092),
		EXCEPTION_FLT_UNDERFLOW = (0xC0000093),
		EXCEPTION_INT_DIVIDE_BY_ZERO = (0xC0000094),
		EXCEPTION_INT_OVERFLOW = (0xC0000095),
		EXCEPTION_PRIV_INSTRUCTION = (0xC0000096),
		EXCEPTION_IN_PAGE_ERROR = (0xC0000006),
		EXCEPTION_ILLEGAL_INSTRUCTION = (0xC000001D),
		EXCEPTION_NONCONTINUABLE_EXCEPTION = (0xC0000025),
		EXCEPTION_STACK_OVERFLOW = (0xC00000FD),
		EXCEPTION_INVALID_DISPOSITION = (0xC0000026),
		EXCEPTION_GUARD_PAGE = (0x80000001),
		EXCEPTION_INVALID_HANDLE = (0xC0000008),
		EVENT_ALL_ACCESS = ((0x000F0000)|(0x00100000)|0x3);

}