// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface winl {
	int lst1 = 0x0460,
		lst2 = 0x0461,
		lst3 = 0x0462,
		lst4 = 0x0463,
		lst5 = 0x0464,
		lst6 = 0x0465,
		lst7 = 0x0466,
		lst8 = 0x0467,
		lst9 = 0x0468,
		lst10 = 0x0469,
		lst11 = 0x046a,
		lst12 = 0x046b,
		lst13 = 0x046c,
		lst14 = 0x046d,
		lst15 = 0x046e,
		lst16 = 0x046f,
		LZERROR_BADINHANDLE = (-1),
		LZERROR_BADOUTHANDLE = (-2),
		LZERROR_READ = (-3),
		LZERROR_WRITE = (-4),
		LZERROR_GLOBALLOC = (-5),
		LZERROR_GLOBLOCK = (-6),
		LZERROR_BADVALUE = (-7),
		LZERROR_UNKNOWNALG = (-8),
		LISTEN_OUTSTANDING = 0x01,
		LMEM_FIXED = 0x0000,
		LMEM_MOVEABLE = 0x0002,
		LMEM_NOCOMPACT = 0x0010,
		LMEM_NODISCARD = 0x0020,
		LMEM_ZEROINIT = 0x0040,
		LMEM_MODIFY = 0x0080,
		LMEM_DISCARDABLE = 0x0F00,
		LMEM_VALID_FLAGS = 0x0F72,
		LMEM_INVALID_HANDLE = 0x8000,
		LHND = (0x0002|0x0040),
		LPTR = (0x0000|0x0040),
		LMEM_DISCARDED = 0x4000,
		LMEM_LOCKCOUNT = 0x00FF,
		LOAD_DLL_DEBUG_EVENT = 6,
		LPTx = 0x80,
		LOCKFILE_FAIL_IMMEDIATELY = 0x00000001,
		LOCKFILE_EXCLUSIVE_LOCK = 0x00000002,
		LOAD_LIBRARY_AS_DATAFILE = 0x00000002,
		LOAD_WITH_ALTERED_SEARCH_PATH = 0x00000008,
		LOGON32_LOGON_INTERACTIVE = 2,
		LOGON32_LOGON_NETWORK = 3,
		LOGON32_LOGON_BATCH = 4,
		LOGON32_LOGON_SERVICE = 5,
		LOGON32_PROVIDER_DEFAULT = 0,
		LOGON32_PROVIDER_WINNT35 = 1,
		LOGON32_PROVIDER_WINNT40 = 2,
		LEFT_ALT_PRESSED = 0x0002,
		LEFT_CTRL_PRESSED = 0x0008,
		LCS_CALIBRATED_RGB = 0x00000000,
		LCS_DEVICE_RGB = 0x00000001,
		LCS_DEVICE_CMYK = 0x00000002,
		LCS_GM_BUSINESS = 0x00000001,
		LCS_GM_GRAPHICS = 0x00000002,
		LCS_GM_IMAGES = 0x00000004,
		LF_FACESIZE = 32,
		LF_FULLFACESIZE = 64,
		LTGRAY_BRUSH = 1,
		LINECAPS = 30,
		LOGPIXELSX = 88,
		LOGPIXELSY = 90,
		LC_NONE = 0,
		LC_POLYLINE = 2,
		LC_MARKER = 4,
		LC_POLYMARKER = 8,
		LC_WIDE = 16,
		LC_STYLED = 32,
		LC_WIDESTYLED = 64,
		LC_INTERIORS = 128,
		LPD_DOUBLEBUFFER = 0x00000001,
		LPD_STEREO = 0x00000002,
		LPD_SUPPORT_GDI = 0x00000010,
		LPD_SUPPORT_OPENGL = 0x00000020,
		LPD_SHARE_DEPTH = 0x00000040,
		LPD_SHARE_STENCIL = 0x00000080,
		LPD_SHARE_ACCUM = 0x00000100,
		LPD_SWAP_EXCHANGE = 0x00000200,
		LPD_SWAP_COPY = 0x00000400,
		LPD_TRANSPARENT = 0x00001000,
		LPD_TYPE_RGBA = 0,
		LPD_TYPE_COLORINDEX = 1,
		LCMAP_LOWERCASE = 0x00000100,
		LCMAP_UPPERCASE = 0x00000200,
		LCMAP_SORTKEY = 0x00000400,
		LCMAP_BYTEREV = 0x00000800,
		LCMAP_HIRAGANA = 0x00100000,
		LCMAP_KATAKANA = 0x00200000,
		LCMAP_HALFWIDTH = 0x00400000,
		LCMAP_FULLWIDTH = 0x00800000,
		LCMAP_LINGUISTIC_CASING = 0x01000000,
		LCMAP_SIMPLIFIED_CHINESE = 0x02000000,
		LCMAP_TRADITIONAL_CHINESE = 0x04000000,
		LCID_INSTALLED = 0x00000001,
		LCID_SUPPORTED = 0x00000002,
		LOCALE_NOUSEROVERRIDE = 0x80000000,
		LOCALE_USE_CP_ACP = 0x40000000,
		LOCALE_ILANGUAGE = 0x00000001,
		LOCALE_SLANGUAGE = 0x00000002,
		LOCALE_SENGLANGUAGE = 0x00001001,
		LOCALE_SABBREVLANGNAME = 0x00000003,
		LOCALE_SNATIVELANGNAME = 0x00000004,
		LOCALE_ICOUNTRY = 0x00000005,
		LOCALE_SCOUNTRY = 0x00000006,
		LOCALE_SENGCOUNTRY = 0x00001002,
		LOCALE_SABBREVCTRYNAME = 0x00000007,
		LOCALE_SNATIVECTRYNAME = 0x00000008,
		LOCALE_IDEFAULTLANGUAGE = 0x00000009,
		LOCALE_IDEFAULTCOUNTRY = 0x0000000A,
		LOCALE_IDEFAULTCODEPAGE = 0x0000000B,
		LOCALE_IDEFAULTANSICODEPAGE = 0x00001004,
		LOCALE_IDEFAULTMACCODEPAGE = 0x00001011,
		LOCALE_SLIST = 0x0000000C,
		LOCALE_IMEASURE = 0x0000000D,
		LOCALE_SDECIMAL = 0x0000000E,
		LOCALE_STHOUSAND = 0x0000000F,
		LOCALE_SGROUPING = 0x00000010,
		LOCALE_IDIGITS = 0x00000011,
		LOCALE_ILZERO = 0x00000012,
		LOCALE_INEGNUMBER = 0x00001010,
		LOCALE_SNATIVEDIGITS = 0x00000013,
		LOCALE_SCURRENCY = 0x00000014,
		LOCALE_SINTLSYMBOL = 0x00000015,
		LOCALE_SMONDECIMALSEP = 0x00000016,
		LOCALE_SMONTHOUSANDSEP = 0x00000017,
		LOCALE_SMONGROUPING = 0x00000018,
		LOCALE_ICURRDIGITS = 0x00000019,
		LOCALE_IINTLCURRDIGITS = 0x0000001A,
		LOCALE_ICURRENCY = 0x0000001B,
		LOCALE_INEGCURR = 0x0000001C,
		LOCALE_SDATE = 0x0000001D,
		LOCALE_STIME = 0x0000001E,
		LOCALE_SSHORTDATE = 0x0000001F,
		LOCALE_SLONGDATE = 0x00000020,
		LOCALE_STIMEFORMAT = 0x00001003,
		LOCALE_IDATE = 0x00000021,
		LOCALE_ILDATE = 0x00000022,
		LOCALE_ITIME = 0x00000023,
		LOCALE_ITIMEMARKPOSN = 0x00001005,
		LOCALE_ICENTURY = 0x00000024,
		LOCALE_ITLZERO = 0x00000025,
		LOCALE_IDAYLZERO = 0x00000026,
		LOCALE_IMONLZERO = 0x00000027,
		LOCALE_S1159 = 0x00000028,
		LOCALE_S2359 = 0x00000029,
		LOCALE_ICALENDARTYPE = 0x00001009,
		LOCALE_IOPTIONALCALENDAR = 0x0000100B,
		LOCALE_IFIRSTDAYOFWEEK = 0x0000100C,
		LOCALE_IFIRSTWEEKOFYEAR = 0x0000100D,
		LOCALE_SDAYNAME1 = 0x0000002A,
		LOCALE_SDAYNAME2 = 0x0000002B,
		LOCALE_SDAYNAME3 = 0x0000002C,
		LOCALE_SDAYNAME4 = 0x0000002D,
		LOCALE_SDAYNAME5 = 0x0000002E,
		LOCALE_SDAYNAME6 = 0x0000002F,
		LOCALE_SDAYNAME7 = 0x00000030,
		LOCALE_SABBREVDAYNAME1 = 0x00000031,
		LOCALE_SABBREVDAYNAME2 = 0x00000032,
		LOCALE_SABBREVDAYNAME3 = 0x00000033,
		LOCALE_SABBREVDAYNAME4 = 0x00000034,
		LOCALE_SABBREVDAYNAME5 = 0x00000035,
		LOCALE_SABBREVDAYNAME6 = 0x00000036,
		LOCALE_SABBREVDAYNAME7 = 0x00000037,
		LOCALE_SMONTHNAME1 = 0x00000038,
		LOCALE_SMONTHNAME2 = 0x00000039,
		LOCALE_SMONTHNAME3 = 0x0000003A,
		LOCALE_SMONTHNAME4 = 0x0000003B,
		LOCALE_SMONTHNAME5 = 0x0000003C,
		LOCALE_SMONTHNAME6 = 0x0000003D,
		LOCALE_SMONTHNAME7 = 0x0000003E,
		LOCALE_SMONTHNAME8 = 0x0000003F,
		LOCALE_SMONTHNAME9 = 0x00000040,
		LOCALE_SMONTHNAME10 = 0x00000041,
		LOCALE_SMONTHNAME11 = 0x00000042,
		LOCALE_SMONTHNAME12 = 0x00000043,
		LOCALE_SMONTHNAME13 = 0x0000100E,
		LOCALE_SABBREVMONTHNAME1 = 0x00000044,
		LOCALE_SABBREVMONTHNAME2 = 0x00000045,
		LOCALE_SABBREVMONTHNAME3 = 0x00000046,
		LOCALE_SABBREVMONTHNAME4 = 0x00000047,
		LOCALE_SABBREVMONTHNAME5 = 0x00000048,
		LOCALE_SABBREVMONTHNAME6 = 0x00000049,
		LOCALE_SABBREVMONTHNAME7 = 0x0000004A,
		LOCALE_SABBREVMONTHNAME8 = 0x0000004B,
		LOCALE_SABBREVMONTHNAME9 = 0x0000004C,
		LOCALE_SABBREVMONTHNAME10 = 0x0000004D,
		LOCALE_SABBREVMONTHNAME11 = 0x0000004E,
		LOCALE_SABBREVMONTHNAME12 = 0x0000004F,
		LOCALE_SABBREVMONTHNAME13 = 0x0000100F,
		LOCALE_SPOSITIVESIGN = 0x00000050,
		LOCALE_SNEGATIVESIGN = 0x00000051,
		LOCALE_IPOSSIGNPOSN = 0x00000052,
		LOCALE_INEGSIGNPOSN = 0x00000053,
		LOCALE_IPOSSYMPRECEDES = 0x00000054,
		LOCALE_IPOSSEPBYSPACE = 0x00000055,
		LOCALE_INEGSYMPRECEDES = 0x00000056,
		LOCALE_INEGSEPBYSPACE = 0x00000057,
		LOCALE_FONTSIGNATURE = 0x00000058,
		LOCALE_SISO639LANGNAME = 0x00000059,
		LOCALE_SISO3166CTRYNAME = 0x0000005A,
		LANG_NEUTRAL = 0x00,
		LANG_AFRIKAANS = 0x36,
		LANG_ALBANIAN = 0x1c,
		LANG_ARABIC = 0x01,
		LANG_BASQUE = 0x2d,
		LANG_BELARUSIAN = 0x23,
		LANG_BULGARIAN = 0x02,
		LANG_CATALAN = 0x03,
		LANG_CHINESE = 0x04,
		LANG_CROATIAN = 0x1a,
		LANG_CZECH = 0x05,
		LANG_DANISH = 0x06,
		LANG_DUTCH = 0x13,
		LANG_ENGLISH = 0x09,
		LANG_ESTONIAN = 0x25,
		LANG_FAEROESE = 0x38,
		LANG_FARSI = 0x29,
		LANG_FINNISH = 0x0b,
		LANG_FRENCH = 0x0c,
		LANG_GERMAN = 0x07,
		LANG_GREEK = 0x08,
		LANG_HEBREW = 0x0d,
		LANG_HUNGARIAN = 0x0e,
		LANG_ICELANDIC = 0x0f,
		LANG_INDONESIAN = 0x21,
		LANG_ITALIAN = 0x10,
		LANG_JAPANESE = 0x11,
		LANG_KOREAN = 0x12,
		LANG_LATVIAN = 0x26,
		LANG_LITHUANIAN = 0x27,
		LANG_NORWEGIAN = 0x14,
		LANG_POLISH = 0x15,
		LANG_PORTUGUESE = 0x16,
		LANG_ROMANIAN = 0x18,
		LANG_RUSSIAN = 0x19,
		LANG_SERBIAN = 0x1a,
		LANG_SLOVAK = 0x1b,
		LANG_SLOVENIAN = 0x24,
		LANG_SPANISH = 0x0a,
		LANG_SWEDISH = 0x1d,
		LANG_THAI = 0x1e,
		LANG_TURKISH = 0x1f,
		LANG_UKRAINIAN = 0x22,
		LANG_VIETNAMESE = 0x2a,
		LR_DEFAULTCOLOR = 0x0000,
		LR_MONOCHROME = 0x0001,
		LR_COLOR = 0x0002,
		LR_COPYRETURNORG = 0x0004,
		LR_COPYDELETEORG = 0x0008,
		LR_LOADFROMFILE = 0x0010,
		LR_LOADTRANSPARENT = 0x0020,
		LR_DEFAULTSIZE = 0x0040,
		LR_VGACOLOR = 0x0080,
		LR_LOADMAP3DCOLORS = 0x1000,
		LR_CREATEDIBSECTION = 0x2000,
		LR_COPYFROMRESOURCE = 0x4000,
		LR_SHARED = 0x8000,
		LB_CTLCODE = 0,
		LB_OKAY = 0,
		LB_ERR = (-1),
		LB_ERRSPACE = (-2),
		LBN_ERRSPACE = (-2),
		LBN_SELCHANGE = 1,
		LBN_DBLCLK = 2,
		LBN_SELCANCEL = 3,
		LBN_SETFOCUS = 4,
		LBN_KILLFOCUS = 5,
		LB_ADDSTRING = 0x0180,
		LB_INSERTSTRING = 0x0181,
		LB_DELETESTRING = 0x0182,
		LB_SELITEMRANGEEX = 0x0183,
		LB_RESETCONTENT = 0x0184,
		LB_SETSEL = 0x0185,
		LB_SETCURSEL = 0x0186,
		LB_GETSEL = 0x0187,
		LB_GETCURSEL = 0x0188,
		LB_GETTEXT = 0x0189,
		LB_GETTEXTLEN = 0x018A,
		LB_GETCOUNT = 0x018B,
		LB_SELECTSTRING = 0x018C,
		LB_DIR = 0x018D,
		LB_GETTOPINDEX = 0x018E,
		LB_FINDSTRING = 0x018F,
		LB_GETSELCOUNT = 0x0190,
		LB_GETSELITEMS = 0x0191,
		LB_SETTABSTOPS = 0x0192,
		LB_GETHORIZONTALEXTENT = 0x0193,
		LB_SETHORIZONTALEXTENT = 0x0194,
		LB_SETCOLUMNWIDTH = 0x0195,
		LB_ADDFILE = 0x0196,
		LB_SETTOPINDEX = 0x0197,
		LB_GETITEMRECT = 0x0198,
		LB_GETITEMDATA = 0x0199,
		LB_SETITEMDATA = 0x019A,
		LB_SELITEMRANGE = 0x019B,
		LB_SETANCHORINDEX = 0x019C,
		LB_GETANCHORINDEX = 0x019D,
		LB_SETCARETINDEX = 0x019E,
		LB_GETCARETINDEX = 0x019F,
		LB_SETITEMHEIGHT = 0x01A0,
		LB_GETITEMHEIGHT = 0x01A1,
		LB_FINDSTRINGEXACT = 0x01A2,
		LB_SETLOCALE = 0x01A5,
		LB_GETLOCALE = 0x01A6,
		LB_SETCOUNT = 0x01A7,
		LB_INITSTORAGE = 0x01A8,
		LB_ITEMFROMPOINT = 0x01A9,
		LB_MSGMAX = 0x01B0;
	// LB_MSGMAX = 0x01A8;
	int LBS_NOTIFY = 0x0001,
		LBS_SORT = 0x0002,
		LBS_NOREDRAW = 0x0004,
		LBS_MULTIPLESEL = 0x0008,
		LBS_OWNERDRAWFIXED = 0x0010,
		LBS_OWNERDRAWVARIABLE = 0x0020,
		LBS_HASSTRINGS = 0x0040,
		LBS_USETABSTOPS = 0x0080,
		LBS_NOINTEGRALHEIGHT = 0x0100,
		LBS_MULTICOLUMN = 0x0200,
		LBS_WANTKEYBOARDINPUT = 0x0400,
		LBS_EXTENDEDSEL = 0x0800,
		LBS_DISABLENOSCROLL = 0x1000,
		LBS_NODATA = 0x2000,
		LBS_NOSEL = 0x4000,
		LBS_STANDARD = (0x0001|0x0002|0x00200000|0x00800000),
		LVM_FIRST = 0x1000,
		LVN_FIRST = (0-100),
		LVN_LAST = (0-199),
		LVS_ICON = 0x0000,
		LVS_REPORT = 0x0001,
		LVS_SMALLICON = 0x0002,
		LVS_LIST = 0x0003,
		LVS_TYPEMASK = 0x0003,
		LVS_SINGLESEL = 0x0004,
		LVS_SHOWSELALWAYS = 0x0008,
		LVS_SORTASCENDING = 0x0010,
		LVS_SORTDESCENDING = 0x0020,
		LVS_SHAREIMAGELISTS = 0x0040,
		LVS_NOLABELWRAP = 0x0080,
		LVS_AUTOARRANGE = 0x0100,
		LVS_EDITLABELS = 0x0200,
		LVS_OWNERDATA = 0x1000,
		LVS_NOSCROLL = 0x2000,
		LVS_TYPESTYLEMASK = 0xfc00,
		LVS_ALIGNTOP = 0x0000,
		LVS_ALIGNLEFT = 0x0800,
		LVS_ALIGNMASK = 0x0c00,
		LVS_OWNERDRAWFIXED = 0x0400,
		LVS_NOCOLUMNHEADER = 0x4000,
		LVS_NOSORTHEADER = 0x8000,
		LVM_GETBKCOLOR = (0x1000+0),
		LVM_SETBKCOLOR = (0x1000+1),
		LVM_GETIMAGELIST = (0x1000+2),
		LVSIL_NORMAL = 0,
		LVSIL_SMALL = 1,
		LVSIL_STATE = 2,
		LVM_SETIMAGELIST = (0x1000+3),
		LVM_GETITEMCOUNT = (0x1000+4),
		LVIF_TEXT = 0x0001,
		LVIF_IMAGE = 0x0002,
		LVIF_PARAM = 0x0004,
		LVIF_STATE = 0x0008,
		LVIF_INDENT = 0x0010,
		LVIF_NORECOMPUTE = 0x0800,
		LVIS_FOCUSED = 0x0001,
		LVIS_SELECTED = 0x0002,
		LVIS_CUT = 0x0004,
		LVIS_DROPHILITED = 0x0008,
		LVIS_OVERLAYMASK = 0x0F00,
		LVIS_STATEIMAGEMASK = 0xF000,
		LVM_GETITEMA = (0x1000+5),
		LVM_GETITEMW = (0x1000+75),
		LVM_SETITEMA = (0x1000+6),
		LVM_SETITEMW = (0x1000+76),
		LVM_INSERTITEMA = (0x1000+7),
		LVM_INSERTITEMW = (0x1000+77),
		LVM_DELETEITEM = (0x1000+8),
		LVM_DELETEALLITEMS = (0x1000+9),
		LVM_GETCALLBACKMASK = (0x1000+10),
		LVM_SETCALLBACKMASK = (0x1000+11),
		LVNI_ALL = 0x0000,
		LVNI_FOCUSED = 0x0001,
		LVNI_SELECTED = 0x0002,
		LVNI_CUT = 0x0004,
		LVNI_DROPHILITED = 0x0008,
		LVNI_ABOVE = 0x0100,
		LVNI_BELOW = 0x0200,
		LVNI_TOLEFT = 0x0400,
		LVNI_TORIGHT = 0x0800,
		LVM_GETNEXTITEM = (0x1000+12),
		LVFI_PARAM = 0x0001,
		LVFI_STRING = 0x0002,
		LVFI_PARTIAL = 0x0008,
		LVFI_WRAP = 0x0020,
		LVFI_NEARESTXY = 0x0040,
		LVM_FINDITEMA = (0x1000+13),
		LVM_FINDITEMW = (0x1000+83),
		LVIR_BOUNDS = 0,
		LVIR_ICON = 1,
		LVIR_LABEL = 2,
		LVIR_SELECTBOUNDS = 3,
		LVM_GETITEMRECT = (0x1000+14),
		LVM_SETITEMPOSITION = (0x1000+15),
		LVM_GETITEMPOSITION = (0x1000+16),
		LVM_GETSTRINGWIDTHA = (0x1000+17),
		LVM_GETSTRINGWIDTHW = (0x1000+87),
		LVHT_NOWHERE = 0x0001,
		LVHT_ONITEMICON = 0x0002,
		LVHT_ONITEMLABEL = 0x0004,
		LVHT_ONITEMSTATEICON = 0x0008,
		LVHT_ONITEM = (0x0002|0x0004|0x0008),
		LVHT_ABOVE = 0x0008,
		LVHT_BELOW = 0x0010,
		LVHT_TORIGHT = 0x0020,
		LVHT_TOLEFT = 0x0040,
		LVM_HITTEST = (0x1000+18),
		LVM_ENSUREVISIBLE = (0x1000+19),
		LVM_SCROLL = (0x1000+20),
		LVM_REDRAWITEMS = (0x1000+21),
		LVA_DEFAULT = 0x0000,
		LVA_ALIGNLEFT = 0x0001,
		LVA_ALIGNTOP = 0x0002,
		LVA_SNAPTOGRID = 0x0005,
		LVM_ARRANGE = (0x1000+22),
		LVM_EDITLABELA = (0x1000+23),
		LVM_EDITLABELW = (0x1000+118),
		LVM_GETEDITCONTROL = (0x1000+24),
		LVCF_FMT = 0x0001,
		LVCF_WIDTH = 0x0002,
		LVCF_TEXT = 0x0004,
		LVCF_SUBITEM = 0x0008,
		LVCF_IMAGE = 0x0010,
		LVCF_ORDER = 0x0020,
		LVCFMT_LEFT = 0x0000,
		LVCFMT_RIGHT = 0x0001,
		LVCFMT_CENTER = 0x0002,
		LVCFMT_JUSTIFYMASK = 0x0003,
		LVCFMT_IMAGE = 0x0800,
		LVCFMT_BITMAP_ON_RIGHT = 0x1000,
		LVCFMT_COL_HAS_IMAGES = 0x8000,
		LVM_GETCOLUMNA = (0x1000+25),
		LVM_GETCOLUMNW = (0x1000+95),
		LVM_SETCOLUMNA = (0x1000+26),
		LVM_SETCOLUMNW = (0x1000+96),
		LVM_INSERTCOLUMNA = (0x1000+27),
		LVM_INSERTCOLUMNW = (0x1000+97),
		LVM_DELETECOLUMN = (0x1000+28),
		LVM_GETCOLUMNWIDTH = (0x1000+29),
		LVSCW_AUTOSIZE = -1,
		LVSCW_AUTOSIZE_USEHEADER = -2,
		LVM_SETCOLUMNWIDTH = (0x1000+30),
		LVM_GETHEADER = (0x1000+31),
		LVM_CREATEDRAGIMAGE = (0x1000+33),
		LVM_GETVIEWRECT = (0x1000+34),
		LVM_GETTEXTCOLOR = (0x1000+35),
		LVM_SETTEXTCOLOR = (0x1000+36),
		LVM_GETTEXTBKCOLOR = (0x1000+37),
		LVM_SETTEXTBKCOLOR = (0x1000+38),
		LVM_GETTOPINDEX = (0x1000+39),
		LVM_GETCOUNTPERPAGE = (0x1000+40),
		LVM_GETORIGIN = (0x1000+41),
		LVM_UPDATE = (0x1000+42),
		LVM_SETITEMSTATE = (0x1000+43),
		LVM_GETITEMSTATE = (0x1000+44),
		LVM_GETITEMTEXTA = (0x1000+45),
		LVM_GETITEMTEXTW = (0x1000+115),
		LVM_SETITEMTEXTA = (0x1000+46),
		LVM_SETITEMTEXTW = (0x1000+116),
		LVSICF_NOINVALIDATEALL = 0x00000001,
		LVSICF_NOSCROLL = 0x00000002,
		LVM_SETITEMCOUNT = (0x1000+47),
		LVM_SORTITEMS = (0x1000+48),
		LVM_SETITEMPOSITION32 = (0x1000+49),
		LVM_GETSELECTEDCOUNT = (0x1000+50),
		LVM_GETITEMSPACING = (0x1000+51),
		LVM_GETISEARCHSTRINGA = (0x1000+52),
		LVM_GETISEARCHSTRINGW = (0x1000+117),
		LVM_SETICONSPACING = (0x1000+53),
		LVM_SETEXTENDEDLISTVIEWSTYLE = (0x1000+54),
		LVM_GETEXTENDEDLISTVIEWSTYLE = (0x1000+55),
		LVS_EX_GRIDLINES = 0x00000001,
		LVS_EX_SUBITEMIMAGES = 0x00000002,
		LVS_EX_CHECKBOXES = 0x00000004,
		LVS_EX_TRACKSELECT = 0x00000008,
		LVS_EX_HEADERDRAGDROP = 0x00000010,
		LVS_EX_FULLROWSELECT = 0x00000020,
		LVS_EX_ONECLICKACTIVATE = 0x00000040,
		LVS_EX_TWOCLICKACTIVATE = 0x00000080,
		LVM_GETSUBITEMRECT = (0x1000+56),
		LVM_SUBITEMHITTEST = (0x1000+57),
		LVM_SETCOLUMNORDERARRAY = (0x1000+58),
		LVM_GETCOLUMNORDERARRAY = (0x1000+59),
		LVM_SETHOTITEM = (0x1000+60),
		LVM_GETHOTITEM = (0x1000+61),
		LVM_SETHOTCURSOR = (0x1000+62),
		LVM_GETHOTCURSOR = (0x1000+63),
		LVM_APPROXIMATEVIEWRECT = (0x1000+64),
		LVM_SETWORKAREA = (0x1000+65),
		LVN_ITEMCHANGING = ((0-100)-0),
		LVN_ITEMCHANGED = ((0-100)-1),
		LVN_INSERTITEM = ((0-100)-2),
		LVN_DELETEITEM = ((0-100)-3),
		LVN_DELETEALLITEMS = ((0-100)-4),
		LVN_BEGINLABELEDITA = ((0-100)-5),
		LVN_BEGINLABELEDITW = ((0-100)-75),
		LVN_ENDLABELEDITA = ((0-100)-6),
		LVN_ENDLABELEDITW = ((0-100)-76),
		LVN_COLUMNCLICK = ((0-100)-8),
		LVN_BEGINDRAG = ((0-100)-9),
		LVN_BEGINRDRAG = ((0-100)-11),
		LVN_ODCACHEHINT = ((0-100)-13),
		LVN_ODFINDITEMA = ((0-100)-52),
		LVN_ODFINDITEMW = ((0-100)-79),
		LVN_ITEMACTIVATE = ((0-100)-14),
		LVN_ODSTATECHANGED = ((0-100)-15),
		LVN_GETDISPINFOA = ((0-100)-50),
		LVN_GETDISPINFOW = ((0-100)-77),
		LVN_SETDISPINFOA = ((0-100)-51),
		LVN_SETDISPINFOW = ((0-100)-78),
		LVIF_DI_SETITEM = 0x1000,
		LVN_KEYDOWN = ((0-100)-55),
		LVN_MARQUEEBEGIN = ((0-100)-56),
		LVM_INSERTCOLUMN = (0x1000+27);

}