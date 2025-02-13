// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface wint {
	boolean TRUE = true;
	int TIMEOUT_ASYNC = 0xFFFFFFFF,
		TIME_MS = 0x0001,
		TIME_SAMPLES = 0x0002,
		TIME_BYTES = 0x0004,
		TIME_SMPTE = 0x0008,
		TIME_MIDI = 0x0010,
		TIME_TICKS = 0x0020,
		TIMERR_BASE = 96,
		TIMERR_NOERROR = (0),
		TIMERR_NOCANDO = (96+1),
		TIMERR_STRUCT = (96+33),
		TIME_ONESHOT = 0x0000,
		TIME_PERIODIC = 0x0001,
		TIME_CALLBACK_FUNCTION = 0x0000,
		TIME_CALLBACK_EVENT_SET = 0x0010,
		TIME_CALLBACK_EVENT_PULSE = 0x0020,
		TCP_BSDURGENT = 0x7000,
		TF_DISCONNECT = 0x01,
		TF_REUSE_SOCKET = 0x02,
		TF_WRITE_BEHIND = 0x04,
		TRANSPORT_TYPE_CN = 0x1,
		TRANSPORT_TYPE_DG = 0x2,
		TRANSPORT_TYPE_LPC = 0x4,
		TRANSPORT_TYPE_WMSG = 0x8;
	int TRUNCATE_EXISTING = 5,
		THREAD_PRIORITY_NORMAL = 0,
		TWOSTOPBITS = 2,
		TC_NORMAL = 0,
		TC_HARDERR = 1,
		TC_GP_TRAP = 2,
		TC_SIGNAL = 3;
	// TRUE = 1;
	int TYPE_E_BUFFERTOOSMALL = 0x80028016,
		TYPE_E_INVDATAREAD = 0x80028018,
		TYPE_E_UNSUPFORMAT = 0x80028019,
		TYPE_E_REGISTRYACCESS = 0x8002801C,
		TYPE_E_LIBNOTREGISTERED = 0x8002801D,
		TYPE_E_UNDEFINEDTYPE = 0x80028027,
		TYPE_E_QUALIFIEDNAMEDISALLOWED = 0x80028028,
		TYPE_E_INVALIDSTATE = 0x80028029,
		TYPE_E_WRONGTYPEKIND = 0x8002802A,
		TYPE_E_ELEMENTNOTFOUND = 0x8002802B,
		TYPE_E_AMBIGUOUSNAME = 0x8002802C,
		TYPE_E_NAMECONFLICT = 0x8002802D,
		TYPE_E_UNKNOWNLCID = 0x8002802E,
		TYPE_E_DLLFUNCTIONNOTFOUND = 0x8002802F,
		TYPE_E_BADMODULEKIND = 0x800288BD,
		TYPE_E_SIZETOOBIG = 0x800288C5,
		TYPE_E_DUPLICATEID = 0x800288C6,
		TYPE_E_INVALIDID = 0x800288CF,
		TYPE_E_TYPEMISMATCH = 0x80028CA0,
		TYPE_E_OUTOFBOUNDS = 0x80028CA1,
		TYPE_E_IOERROR = 0x80028CA2,
		TYPE_E_CANTCREATETMPFILE = 0x80028CA3,
		TYPE_E_CANTLOADLIBRARY = 0x80029C4A,
		TYPE_E_INCONSISTENTPROPFUNCS = 0x80029C83,
		TYPE_E_CIRCULARTYPE = 0x80029C84,
		TRUST_E_PROVIDER_UNKNOWN = 0x800B0001,
		TRUST_E_ACTION_UNKNOWN = 0x800B0002,
		TRUST_E_SUBJECT_FORM_UNKNOWN = 0x800B0003,
		TRUST_E_SUBJECT_NOT_TRUSTED = 0x800B0004,
		TRUST_E_NOSIGNATURE = 0x800B0100,
		TA_NOUPDATECP = 0,
		TA_UPDATECP = 1,
		TA_LEFT = 0,
		TA_RIGHT = 2,
		TA_CENTER = 6,
		TA_TOP = 0,
		TA_BOTTOM = 8,
		TA_BASELINE = 24,
		TA_RTLREADING = 256,
		TA_MASK = (24+6+1+256);
	// TA_MASK = (24+6+1);
	int TRANSFORM_CTM = 4107,
		TCI_SRCCHARSET = 1,
		TCI_SRCCODEPAGE = 2,
		TCI_SRCFONTSIG = 3,
		TMPF_FIXED_PITCH = 0x01,
		TMPF_VECTOR = 0x02,
		TMPF_DEVICE = 0x08,
		TMPF_TRUETYPE = 0x04,
		TURKISH_CHARSET = 162,
		THAI_CHARSET = 222,
		TRUETYPE_FONTTYPE = 0x004,
		TRANSPARENT = 1,
		TECHNOLOGY = 2,
		TEXTCAPS = 34,
		TC_OP_CHARACTER = 0x00000001,
		TC_OP_STROKE = 0x00000002,
		TC_CP_STROKE = 0x00000004,
		TC_CR_90 = 0x00000008,
		TC_CR_ANY = 0x00000010,
		TC_SF_X_YINDEP = 0x00000020,
		TC_SA_DOUBLE = 0x00000040,
		TC_SA_INTEGER = 0x00000080,
		TC_SA_CONTIN = 0x00000100,
		TC_EA_DOUBLE = 0x00000200,
		TC_IA_ABLE = 0x00000400,
		TC_UA_ABLE = 0x00000800,
		TC_SO_ABLE = 0x00001000,
		TC_RA_ABLE = 0x00002000,
		TC_VA_ABLE = 0x00004000,
		TC_RESERVED = 0x00008000,
		TC_SCROLLBLT = 0x00010000,
		TT_POLYGON_TYPE = 24,
		TT_PRIM_LINE = 1,
		TT_PRIM_QSPLINE = 2,
		TT_AVAILABLE = 0x0001,
		TT_ENABLED = 0x0002,
		TIME_NOMINUTESORSECONDS = 0x00000001,
		TIME_NOSECONDS = 0x00000002,
		TIME_NOTIMEMARKER = 0x00000004,
		TIME_FORCE24HOURFORMAT = 0x00000008,
		THREAD_TERMINATE = (0x0001),
		THREAD_SUSPEND_RESUME = (0x0002),
		THREAD_GET_CONTEXT = (0x0008),
		THREAD_SET_CONTEXT = (0x0010),
		THREAD_SET_INFORMATION = (0x0020),
		THREAD_QUERY_INFORMATION = (0x0040),
		THREAD_SET_THREAD_TOKEN = (0x0080),
		THREAD_IMPERSONATE = (0x0100),
		THREAD_DIRECT_IMPERSONATION = (0x0200),
		TLS_MINIMUM_AVAILABLE = 64,
		THREAD_BASE_PRIORITY_LOWRT = 15,
		THREAD_BASE_PRIORITY_MAX = 2,
		THREAD_BASE_PRIORITY_MIN = -2,
		THREAD_BASE_PRIORITY_IDLE = -15,
		TIME_ZONE_ID_UNKNOWN = 0,
		TIME_ZONE_ID_STANDARD = 1,
		TIME_ZONE_ID_DAYLIGHT = 2,
		TOKEN_ASSIGN_PRIMARY = (0x0001),
		TOKEN_DUPLICATE = (0x0002),
		TOKEN_IMPERSONATE = (0x0004),
		TOKEN_QUERY = (0x0008),
		TOKEN_QUERY_SOURCE = (0x0010),
		TOKEN_ADJUST_PRIVILEGES = (0x0020),
		TOKEN_ADJUST_GROUPS = (0x0040),
		TOKEN_ADJUST_DEFAULT = (0x0080),
		TOKEN_EXECUTE = (((0x00020000))),
		TOKEN_SOURCE_LENGTH = 8,
		TAPE_ERASE_SHORT = 0,
		TAPE_ERASE_LONG = 1,
		TAPE_LOAD = 0,
		TAPE_UNLOAD = 1,
		TAPE_TENSION = 2,
		TAPE_LOCK = 3,
		TAPE_UNLOCK = 4,
		TAPE_FORMAT = 5,
		TAPE_SETMARKS = 0,
		TAPE_FILEMARKS = 1,
		TAPE_SHORT_FILEMARKS = 2,
		TAPE_LONG_FILEMARKS = 3,
		TAPE_ABSOLUTE_POSITION = 0,
		TAPE_LOGICAL_POSITION = 1,
		TAPE_PSEUDO_LOGICAL_POSITION = 2,
		TAPE_REWIND = 0,
		TAPE_ABSOLUTE_BLOCK = 1,
		TAPE_LOGICAL_BLOCK = 2,
		TAPE_PSEUDO_LOGICAL_BLOCK = 3,
		TAPE_SPACE_END_OF_DATA = 4,
		TAPE_SPACE_RELATIVE_BLOCKS = 5,
		TAPE_SPACE_FILEMARKS = 6,
		TAPE_SPACE_SEQUENTIAL_FMKS = 7,
		TAPE_SPACE_SETMARKS = 8,
		TAPE_SPACE_SEQUENTIAL_SMKS = 9,
		TAPE_DRIVE_FIXED = 0x00000001,
		TAPE_DRIVE_SELECT = 0x00000002,
		TAPE_DRIVE_INITIATOR = 0x00000004,
		TAPE_DRIVE_ERASE_SHORT = 0x00000010,
		TAPE_DRIVE_ERASE_LONG = 0x00000020,
		TAPE_DRIVE_ERASE_BOP_ONLY = 0x00000040,
		TAPE_DRIVE_ERASE_IMMEDIATE = 0x00000080,
		TAPE_DRIVE_TAPE_CAPACITY = 0x00000100,
		TAPE_DRIVE_TAPE_REMAINING = 0x00000200,
		TAPE_DRIVE_FIXED_BLOCK = 0x00000400,
		TAPE_DRIVE_VARIABLE_BLOCK = 0x00000800,
		TAPE_DRIVE_WRITE_PROTECT = 0x00001000,
		TAPE_DRIVE_EOT_WZ_SIZE = 0x00002000,
		TAPE_DRIVE_ECC = 0x00010000,
		TAPE_DRIVE_COMPRESSION = 0x00020000,
		TAPE_DRIVE_PADDING = 0x00040000,
		TAPE_DRIVE_REPORT_SMKS = 0x00080000,
		TAPE_DRIVE_GET_ABSOLUTE_BLK = 0x00100000,
		TAPE_DRIVE_GET_LOGICAL_BLK = 0x00200000,
		TAPE_DRIVE_SET_EOT_WZ_SIZE = 0x00400000,
		TAPE_DRIVE_EJECT_MEDIA = 0x01000000,
		TAPE_DRIVE_RESERVED_BIT = 0x80000000,
		TAPE_DRIVE_LOAD_UNLOAD = 0x80000001,
		TAPE_DRIVE_TENSION = 0x80000002,
		TAPE_DRIVE_LOCK_UNLOCK = 0x80000004,
		TAPE_DRIVE_REWIND_IMMEDIATE = 0x80000008,
		TAPE_DRIVE_SET_BLOCK_SIZE = 0x80000010,
		TAPE_DRIVE_LOAD_UNLD_IMMED = 0x80000020,
		TAPE_DRIVE_TENSION_IMMED = 0x80000040,
		TAPE_DRIVE_LOCK_UNLK_IMMED = 0x80000080,
		TAPE_DRIVE_SET_ECC = 0x80000100,
		TAPE_DRIVE_SET_COMPRESSION = 0x80000200,
		TAPE_DRIVE_SET_PADDING = 0x80000400,
		TAPE_DRIVE_SET_REPORT_SMKS = 0x80000800,
		TAPE_DRIVE_ABSOLUTE_BLK = 0x80001000,
		TAPE_DRIVE_ABS_BLK_IMMED = 0x80002000,
		TAPE_DRIVE_LOGICAL_BLK = 0x80004000,
		TAPE_DRIVE_LOG_BLK_IMMED = 0x80008000,
		TAPE_DRIVE_END_OF_DATA = 0x80010000,
		TAPE_DRIVE_RELATIVE_BLKS = 0x80020000,
		TAPE_DRIVE_FILEMARKS = 0x80040000,
		TAPE_DRIVE_SEQUENTIAL_FMKS = 0x80080000,
		TAPE_DRIVE_SETMARKS = 0x80100000,
		TAPE_DRIVE_SEQUENTIAL_SMKS = 0x80200000,
		TAPE_DRIVE_REVERSE_POSITION = 0x80400000,
		TAPE_DRIVE_SPACE_IMMEDIATE = 0x80800000,
		TAPE_DRIVE_WRITE_SETMARKS = 0x81000000,
		TAPE_DRIVE_WRITE_FILEMARKS = 0x82000000,
		TAPE_DRIVE_WRITE_SHORT_FMKS = 0x84000000,
		TAPE_DRIVE_WRITE_LONG_FMKS = 0x88000000,
		TAPE_DRIVE_WRITE_MARK_IMMED = 0x90000000,
		TAPE_DRIVE_FORMAT = 0xA0000000,
		TAPE_DRIVE_FORMAT_IMMEDIATE = 0xC0000000,
		TAPE_DRIVE_HIGH_FEATURES = 0x80000000,
		TAPE_FIXED_PARTITIONS = 0,
		TAPE_SELECT_PARTITIONS = 1,
		TAPE_INITIATOR_PARTITIONS = 2,
		TME_HOVER = 0x00000001,
		TME_LEAVE = 0x00000002,
		TME_QUERY = 0x40000000,
		TME_CANCEL = 0x80000000,
		TPM_LEFTBUTTON = 0x0000,
		TPM_RIGHTBUTTON = 0x0002,
		TPM_LEFTALIGN = 0x0000,
		TPM_CENTERALIGN = 0x0004,
		TPM_RIGHTALIGN = 0x0008,
		TPM_TOPALIGN = 0x0000,
		TPM_VCENTERALIGN = 0x0010,
		TPM_BOTTOMALIGN = 0x0020,
		TPM_HORIZONTAL = 0x0000,
		TPM_VERTICAL = 0x0040,
		TPM_NONOTIFY = 0x0080,
		TPM_RETURNCMD = 0x0100,
		TKF_TOGGLEKEYSON = 0x00000001,
		TKF_AVAILABLE = 0x00000002,
		TKF_HOTKEYACTIVE = 0x00000004,
		TKF_CONFIRMHOTKEY = 0x00000008,
		TKF_HOTKEYSOUND = 0x00000010,
		TKF_INDICATOR = 0x00000020,
		TV_FIRST = 0x1100,
		TVN_FIRST = (0-400),
		TVN_LAST = (0-499),
		TTN_FIRST = (0-520),
		TTN_LAST = (0-549),
		TCN_FIRST = (0-550),
		TCN_LAST = (0-580),
		TBN_FIRST = (0-700),
		TBN_LAST = (0-720),
		TBSTATE_CHECKED = 0x01,
		TBSTATE_PRESSED = 0x02,
		TBSTATE_ENABLED = 0x04,
		TBSTATE_HIDDEN = 0x08,
		TBSTATE_INDETERMINATE = 0x10,
		TBSTATE_WRAP = 0x20,
		TBSTATE_ELLIPSES = 0x40,
		TBSTYLE_BUTTON = 0x00,
		TBSTYLE_SEP = 0x01,
		TBSTYLE_CHECK = 0x02,
		TBSTYLE_GROUP = 0x04,
		TBSTYLE_CHECKGROUP = (0x04|0x02),
		TBSTYLE_DROPDOWN = 0x08,
		TBSTYLE_TOOLTIPS = 0x0100,
		TBSTYLE_WRAPABLE = 0x0200,
		TBSTYLE_ALTDRAG = 0x0400,
		TBSTYLE_FLAT = 0x0800,
		TBSTYLE_LIST = 0x1000,
		TBSTYLE_CUSTOMERASE = 0x2000,
		TB_ENABLEBUTTON = (0x0400+1),
		TB_CHECKBUTTON = (0x0400+2),
		TB_PRESSBUTTON = (0x0400+3),
		TB_HIDEBUTTON = (0x0400+4),
		TB_INDETERMINATE = (0x0400+5),
		TB_ISBUTTONENABLED = (0x0400+9),
		TB_ISBUTTONCHECKED = (0x0400+10),
		TB_ISBUTTONPRESSED = (0x0400+11),
		TB_ISBUTTONHIDDEN = (0x0400+12),
		TB_ISBUTTONINDETERMINATE = (0x0400+13),
		TB_SETSTATE = (0x0400+17),
		TB_GETSTATE = (0x0400+18),
		TB_ADDBITMAP = (0x0400+19),
		TB_ADDBUTTONS = (0x0400+20),
		TB_INSERTBUTTON = (0x0400+21),
		TB_DELETEBUTTON = (0x0400+22),
		TB_GETBUTTON = (0x0400+23),
		TB_BUTTONCOUNT = (0x0400+24),
		TB_COMMANDTOINDEX = (0x0400+25),
		TB_SAVERESTOREA = (0x0400+26),
		TB_SAVERESTOREW = (0x0400+76),
		TB_CUSTOMIZE = (0x0400+27),
		TB_ADDSTRINGA = (0x0400+28),
		TB_ADDSTRINGW = (0x0400+77),
		TB_GETITEMRECT = (0x0400+29),
		TB_BUTTONSTRUCTSIZE = (0x0400+30),
		TB_SETBUTTONSIZE = (0x0400+31),
		TB_SETBITMAPSIZE = (0x0400+32),
		TB_AUTOSIZE = (0x0400+33),
		TB_GETTOOLTIPS = (0x0400+35),
		TB_SETTOOLTIPS = (0x0400+36),
		TB_SETPARENT = (0x0400+37),
		TB_SETROWS = (0x0400+39),
		TB_GETROWS = (0x0400+40),
		TB_SETCMDID = (0x0400+42),
		TB_CHANGEBITMAP = (0x0400+43),
		TB_GETBITMAP = (0x0400+44),
		TB_GETBUTTONTEXTA = (0x0400+45),
		TB_GETBUTTONTEXTW = (0x0400+75),
		TB_REPLACEBITMAP = (0x0400+46),
		TB_SETINDENT = (0x0400+47),
		TB_SETIMAGELIST = (0x0400+48),
		TB_GETIMAGELIST = (0x0400+49),
		TB_LOADIMAGES = (0x0400+50),
		TB_GETRECT = (0x0400+51),
		TB_SETHOTIMAGELIST = (0x0400+52),
		TB_GETHOTIMAGELIST = (0x0400+53),
		TB_SETDISABLEDIMAGELIST = (0x0400+54),
		TB_GETDISABLEDIMAGELIST = (0x0400+55),
		TB_SETSTYLE = (0x0400+56),
		TB_GETSTYLE = (0x0400+57),
		TB_GETBUTTONSIZE = (0x0400+58),
		TB_SETBUTTONWIDTH = (0x0400+59),
		TB_SETMAXTEXTROWS = (0x0400+60),
		TB_GETTEXTROWS = (0x0400+61),
		TBBF_LARGE = 0x0001,
		TB_GETBITMAPFLAGS = (0x0400+41),
		TBN_GETBUTTONINFOA = ((0-700)-0),
		TBN_GETBUTTONINFOW = ((0-700)-20),
		TBN_BEGINDRAG = ((0-700)-1),
		TBN_ENDDRAG = ((0-700)-2),
		TBN_BEGINADJUST = ((0-700)-3),
		TBN_ENDADJUST = ((0-700)-4),
		TBN_RESET = ((0-700)-5),
		TBN_QUERYINSERT = ((0-700)-6),
		TBN_QUERYDELETE = ((0-700)-7),
		TBN_TOOLBARCHANGE = ((0-700)-8),
		TBN_CUSTHELP = ((0-700)-9),
		TBN_DROPDOWN = ((0-700)-10),
		TBN_CLOSEUP = ((0-700)-11),
		TTS_ALWAYSTIP = 0x01,
		TTS_NOPREFIX = 0x02,
		TTF_IDISHWND = 0x0001,
		TTF_CENTERTIP = 0x0002,
		TTF_RTLREADING = 0x0004,
		TTF_SUBCLASS = 0x0010,
		TTF_TRACK = 0x0020,
		TTF_ABSOLUTE = 0x0080,
		TTF_TRANSPARENT = 0x0100,
		TTF_DI_SETITEM = 0x8000,
		TTDT_AUTOMATIC = 0,
		TTDT_RESHOW = 1,
		TTDT_AUTOPOP = 2,
		TTDT_INITIAL = 3,
		TTM_ACTIVATE = (0x0400+1),
		TTM_SETDELAYTIME = (0x0400+3),
		TTM_ADDTOOLA = (0x0400+4),
		TTM_ADDTOOLW = (0x0400+50),
		TTM_DELTOOLA = (0x0400+5),
		TTM_DELTOOLW = (0x0400+51),
		TTM_NEWTOOLRECTA = (0x0400+6),
		TTM_NEWTOOLRECTW = (0x0400+52),
		TTM_RELAYEVENT = (0x0400+7),
		TTM_GETTOOLINFOA = (0x0400+8),
		TTM_GETTOOLINFOW = (0x0400+53),
		TTM_SETTOOLINFOA = (0x0400+9),
		TTM_SETTOOLINFOW = (0x0400+54),
		TTM_HITTESTA = (0x0400+10),
		TTM_HITTESTW = (0x0400+55),
		TTM_GETTEXTA = (0x0400+11),
		TTM_GETTEXTW = (0x0400+56),
		TTM_UPDATETIPTEXTA = (0x0400+12),
		TTM_UPDATETIPTEXTW = (0x0400+57),
		TTM_GETTOOLCOUNT = (0x0400+13),
		TTM_ENUMTOOLSA = (0x0400+14),
		TTM_ENUMTOOLSW = (0x0400+58),
		TTM_GETCURRENTTOOLA = (0x0400+15),
		TTM_GETCURRENTTOOLW = (0x0400+59),
		TTM_WINDOWFROMPOINT = (0x0400+16),
		TTM_TRACKACTIVATE = (0x0400+17),
		TTM_TRACKPOSITION = (0x0400+18),
		TTM_SETTIPBKCOLOR = (0x0400+19),
		TTM_SETTIPTEXTCOLOR = (0x0400+20),
		TTM_GETDELAYTIME = (0x0400+21),
		TTM_GETTIPBKCOLOR = (0x0400+22),
		TTM_GETTIPTEXTCOLOR = (0x0400+23),
		TTM_SETMAXTIPWIDTH = (0x0400+24),
		TTM_GETMAXTIPWIDTH = (0x0400+25),
		TTM_SETMARGIN = (0x0400+26),
		TTM_GETMARGIN = (0x0400+27),
		TTM_POP = (0x0400+28),
		TTN_GETDISPINFOA = ((0-520)-0),
		TTN_GETDISPINFOW = ((0-520)-10),
		TTN_SHOW = ((0-520)-1),
		TTN_POP = ((0-520)-2),
		TTN_NEEDTEXTA = ((0-520)-0),
		TTN_NEEDTEXTW = ((0-520)-10),
		TBS_AUTOTICKS = 0x0001,
		TBS_VERT = 0x0002,
		TBS_HORZ = 0x0000,
		TBS_TOP = 0x0004,
		TBS_BOTTOM = 0x0000,
		TBS_LEFT = 0x0004,
		TBS_RIGHT = 0x0000,
		TBS_BOTH = 0x0008,
		TBS_NOTICKS = 0x0010,
		TBS_ENABLESELRANGE = 0x0020,
		TBS_FIXEDLENGTH = 0x0040,
		TBS_NOTHUMB = 0x0080,
		TBS_TOOLTIPS = 0x0100,
		TBM_GETPOS = (0x0400),
		TBM_GETRANGEMIN = (0x0400+1),
		TBM_GETRANGEMAX = (0x0400+2),
		TBM_GETTIC = (0x0400+3),
		TBM_SETTIC = (0x0400+4),
		TBM_SETPOS = (0x0400+5),
		TBM_SETRANGE = (0x0400+6),
		TBM_SETRANGEMIN = (0x0400+7),
		TBM_SETRANGEMAX = (0x0400+8),
		TBM_CLEARTICS = (0x0400+9),
		TBM_SETSEL = (0x0400+10),
		TBM_SETSELSTART = (0x0400+11),
		TBM_SETSELEND = (0x0400+12),
		TBM_GETPTICS = (0x0400+14),
		TBM_GETTICPOS = (0x0400+15),
		TBM_GETNUMTICS = (0x0400+16),
		TBM_GETSELSTART = (0x0400+17),
		TBM_GETSELEND = (0x0400+18),
		TBM_CLEARSEL = (0x0400+19),
		TBM_SETTICFREQ = (0x0400+20),
		TBM_SETPAGESIZE = (0x0400+21),
		TBM_GETPAGESIZE = (0x0400+22),
		TBM_SETLINESIZE = (0x0400+23),
		TBM_GETLINESIZE = (0x0400+24),
		TBM_GETTHUMBRECT = (0x0400+25),
		TBM_GETCHANNELRECT = (0x0400+26),
		TBM_SETTHUMBLENGTH = (0x0400+27),
		TBM_GETTHUMBLENGTH = (0x0400+28),
		TBM_SETTOOLTIPS = (0x0400+29),
		TBM_GETTOOLTIPS = (0x0400+30),
		TBM_SETTIPSIDE = (0x0400+31),
		TBTS_TOP = 0,
		TBTS_LEFT = 1,
		TBTS_BOTTOM = 2,
		TBTS_RIGHT = 3,
		TBM_SETBUDDY = (0x0400+32),
		TBM_GETBUDDY = (0x0400+33),
		TB_LINEUP = 0,
		TB_LINEDOWN = 1,
		TB_PAGEUP = 2,
		TB_PAGEDOWN = 3,
		TB_THUMBPOSITION = 4,
		TB_THUMBTRACK = 5,
		TB_TOP = 6,
		TB_BOTTOM = 7,
		TB_ENDTRACK = 8,
		TBCD_TICS = 0x0001,
		TBCD_THUMB = 0x0002,
		TBCD_CHANNEL = 0x0003,
		TVS_HASBUTTONS = 0x0001,
		TVS_HASLINES = 0x0002,
		TVS_LINESATROOT = 0x0004,
		TVS_EDITLABELS = 0x0008,
		TVS_DISABLEDRAGDROP = 0x0010,
		TVS_SHOWSELALWAYS = 0x0020,
		TVS_RTLREADING = 0x0040,
		TVS_NOTOOLTIPS = 0x0080,
		TVS_CHECKBOXES = 0x0100,
		TVS_TRACKSELECT = 0x0200,
		TVS_SHAREDIMAGELISTS = 0x0000,
		TVS_PRIVATEIMAGELISTS = 0x0400,
		TVIF_TEXT = 0x0001,
		TVIF_IMAGE = 0x0002,
		TVIF_PARAM = 0x0004,
		TVIF_STATE = 0x0008,
		TVIF_HANDLE = 0x0010,
		TVIF_SELECTEDIMAGE = 0x0020,
		TVIF_CHILDREN = 0x0040,
		TVIS_SELECTED = 0x0002,
		TVIS_CUT = 0x0004,
		TVIS_DROPHILITED = 0x0008,
		TVIS_BOLD = 0x0010,
		TVIS_EXPANDED = 0x0020,
		TVIS_EXPANDEDONCE = 0x0040,
		TVIS_EXPANDPARTIAL = 0x0080,
		TVIS_OVERLAYMASK = 0x0F00,
		TVIS_STATEIMAGEMASK = 0xF000,
		TVIS_USERMASK = 0xF000,
		TVI_ROOT = (0xFFFF0000),
		TVI_FIRST = (0xFFFF0001),
		TVI_LAST = (0xFFFF0002),
		TVI_SORT = (0xFFFF0003),
		TVM_INSERTITEMA = (0x1100+0),
		TVM_INSERTITEMW = (0x1100+50),
		TVM_DELETEITEM = (0x1100+1),
		TVM_EXPAND = (0x1100+2),
		TVE_COLLAPSE = 0x0001,
		TVE_EXPAND = 0x0002,
		TVE_TOGGLE = 0x0003,
		TVE_EXPANDPARTIAL = 0x4000,
		TVE_COLLAPSERESET = 0x8000,
		TVM_GETITEMRECT = (0x1100+4),
		TVM_GETCOUNT = (0x1100+5),
		TVM_GETINDENT = (0x1100+6),
		TVM_SETINDENT = (0x1100+7),
		TVM_GETIMAGELIST = (0x1100+8),
		TVSIL_NORMAL = 0,
		TVSIL_STATE = 2,
		TVM_SETIMAGELIST = (0x1100+9),
		TVM_GETNEXTITEM = (0x1100+10),
		TVGN_ROOT = 0x0000,
		TVGN_NEXT = 0x0001,
		TVGN_PREVIOUS = 0x0002,
		TVGN_PARENT = 0x0003,
		TVGN_CHILD = 0x0004,
		TVGN_FIRSTVISIBLE = 0x0005,
		TVGN_NEXTVISIBLE = 0x0006,
		TVGN_PREVIOUSVISIBLE = 0x0007,
		TVGN_DROPHILITE = 0x0008,
		TVGN_CARET = 0x0009,
		TVM_SELECTITEM = (0x1100+11),
		TVM_GETITEMA = (0x1100+12),
		TVM_GETITEMW = (0x1100+62),
		TVM_SETITEMA = (0x1100+13),
		TVM_SETITEMW = (0x1100+63),
		TVM_EDITLABELA = (0x1100+14),
		TVM_EDITLABELW = (0x1100+65),
		TVM_GETEDITCONTROL = (0x1100+15),
		TVM_GETVISIBLECOUNT = (0x1100+16),
		TVM_HITTEST = (0x1100+17),
		TVHT_NOWHERE = 0x0001,
		TVHT_ONITEMICON = 0x0002,
		TVHT_ONITEMLABEL = 0x0004,
		TVHT_ONITEMINDENT = 0x0008,
		TVHT_ONITEMBUTTON = 0x0010,
		TVHT_ONITEMRIGHT = 0x0020,
		TVHT_ONITEMSTATEICON = 0x0040,
		TVHT_ABOVE = 0x0100,
		TVHT_BELOW = 0x0200,
		TVHT_TORIGHT = 0x0400,
		TVHT_TOLEFT = 0x0800,
		TVM_CREATEDRAGIMAGE = (0x1100+18),
		TVM_SORTCHILDREN = (0x1100+19),
		TVM_ENSUREVISIBLE = (0x1100+20),
		TVM_SORTCHILDRENCB = (0x1100+21),
		TVM_ENDEDITLABELNOW = (0x1100+22),
		TVM_GETISEARCHSTRINGA = (0x1100+23),
		TVM_GETISEARCHSTRINGW = (0x1100+64),
		TVM_SETTOOLTIPS = (0x1100+24),
		TVM_GETTOOLTIPS = (0x1100+25),
		TVN_SELCHANGINGA = ((0-400)-1),
		TVN_SELCHANGINGW = ((0-400)-50),
		TVN_SELCHANGEDA = ((0-400)-2),
		TVN_SELCHANGEDW = ((0-400)-51),
		TVC_UNKNOWN = 0x0000,
		TVC_BYMOUSE = 0x0001,
		TVC_BYKEYBOARD = 0x0002,
		TVN_GETDISPINFOA = ((0-400)-3),
		TVN_GETDISPINFOW = ((0-400)-52),
		TVN_SETDISPINFOA = ((0-400)-4),
		TVN_SETDISPINFOW = ((0-400)-53),
		TVIF_DI_SETITEM = 0x1000,
		TVN_ITEMEXPANDINGA = ((0-400)-5),
		TVN_ITEMEXPANDINGW = ((0-400)-54),
		TVN_ITEMEXPANDEDA = ((0-400)-6),
		TVN_ITEMEXPANDEDW = ((0-400)-55),
		TVN_BEGINDRAGA = ((0-400)-7),
		TVN_BEGINDRAGW = ((0-400)-56),
		TVN_BEGINRDRAGA = ((0-400)-8),
		TVN_BEGINRDRAGW = ((0-400)-57),
		TVN_DELETEITEMA = ((0-400)-9),
		TVN_DELETEITEMW = ((0-400)-58),
		TVN_BEGINLABELEDITA = ((0-400)-10),
		TVN_BEGINLABELEDITW = ((0-400)-59),
		TVN_ENDLABELEDITA = ((0-400)-11),
		TVN_ENDLABELEDITW = ((0-400)-60),
		TVN_KEYDOWN = ((0-400)-12),
		TCS_SCROLLOPPOSITE = 0x0001,
		TCS_BOTTOM = 0x0002,
		TCS_RIGHT = 0x0002,
		TCS_MULTISELECT = 0x0004,
		TCS_FORCEICONLEFT = 0x0010,
		TCS_FORCELABELLEFT = 0x0020,
		TCS_HOTTRACK = 0x0040,
		TCS_VERTICAL = 0x0080,
		TCS_TABS = 0x0000,
		TCS_BUTTONS = 0x0100,
		TCS_SINGLELINE = 0x0000,
		TCS_MULTILINE = 0x0200,
		TCS_RIGHTJUSTIFY = 0x0000,
		TCS_FIXEDWIDTH = 0x0400,
		TCS_RAGGEDRIGHT = 0x0800,
		TCS_FOCUSONBUTTONDOWN = 0x1000,
		TCS_OWNERDRAWFIXED = 0x2000,
		TCS_TOOLTIPS = 0x4000,
		TCS_FOCUSNEVER = 0x8000,
		TCM_FIRST = 0x1300,
		TCM_GETIMAGELIST = (0x1300+2),
		TCM_SETIMAGELIST = (0x1300+3),
		TCM_GETITEMCOUNT = (0x1300+4),
		TCIF_TEXT = 0x0001,
		TCIF_IMAGE = 0x0002,
		TCIF_RTLREADING = 0x0004,
		TCIF_PARAM = 0x0008,
		TCIF_STATE = 0x0010,
		TCIS_BUTTONPRESSED = 0x0001,
		TCM_GETITEMA = (0x1300+5),
		TCM_GETITEMW = (0x1300+60),
		TCM_SETITEMA = (0x1300+6),
		TCM_SETITEMW = (0x1300+61),
		TCM_INSERTITEMA = (0x1300+7),
		TCM_INSERTITEMW = (0x1300+62),
		TCM_DELETEITEM = (0x1300+8),
		TCM_DELETEALLITEMS = (0x1300+9),
		TCM_GETITEMRECT = (0x1300+10),
		TCM_GETCURSEL = (0x1300+11),
		TCM_SETCURSEL = (0x1300+12),
		TCHT_NOWHERE = 0x0001,
		TCHT_ONITEMICON = 0x0002,
		TCHT_ONITEMLABEL = 0x0004,
		TCHT_ONITEM = (0x0002|0x0004),
		TCM_HITTEST = (0x1300+13),
		TCM_SETITEMEXTRA = (0x1300+14),
		TCM_ADJUSTRECT = (0x1300+40),
		TCM_SETITEMSIZE = (0x1300+41),
		TCM_REMOVEIMAGE = (0x1300+42),
		TCM_SETPADDING = (0x1300+43),
		TCM_GETROWCOUNT = (0x1300+44),
		TCM_GETTOOLTIPS = (0x1300+45),
		TCM_SETTOOLTIPS = (0x1300+46),
		TCM_GETCURFOCUS = (0x1300+47),
		TCM_SETCURFOCUS = (0x1300+48),
		TCM_SETMINTABWIDTH = (0x1300+49),
		TCM_DESELECTALL = (0x1300+50),
		TCN_KEYDOWN = ((0-550)-0),
		TCN_SELCHANGE = ((0-550)-1),
		TCN_SELCHANGING = ((0-550)-2),
		THREAD_PRIORITY_LOWEST = -2,
		THREAD_PRIORITY_BELOW_NORMAL = (-2+1),
		THREAD_PRIORITY_HIGHEST = 2,
		THREAD_PRIORITY_ABOVE_NORMAL = (2-1),
		THREAD_PRIORITY_ERROR_RETURN = (0x7fffffff),
		THREAD_PRIORITY_TIME_CRITICAL = 15,
		THREAD_PRIORITY_IDLE = -15,
		TVHT_ONITEM = (0x0002|0x0004|0x0040);

}
