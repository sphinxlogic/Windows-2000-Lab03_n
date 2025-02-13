// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface wing {
	int grp1 = 0x0430,
		grp2 = 0x0431,
		grp3 = 0x0432,
		grp4 = 0x0433,
		GCS_COMPREADSTR = 0x0001,
		GCS_COMPREADATTR = 0x0002,
		GCS_COMPREADCLAUSE = 0x0004,
		GCS_COMPSTR = 0x0008,
		GCS_COMPATTR = 0x0010,
		GCS_COMPCLAUSE = 0x0020,
		GCS_CURSORPOS = 0x0080,
		GCS_DELTASTART = 0x0100,
		GCS_RESULTREADSTR = 0x0200,
		GCS_RESULTREADCLAUSE = 0x0400,
		GCS_RESULTSTR = 0x0800,
		GCS_RESULTCLAUSE = 0x1000,
		GGL_LEVEL = 0x00000001,
		GGL_INDEX = 0x00000002,
		GGL_STRING = 0x00000003,
		GGL_PRIVATE = 0x00000004,
		GL_LEVEL_NOGUIDELINE = 0x00000000,
		GL_LEVEL_FATAL = 0x00000001,
		GL_LEVEL_ERROR = 0x00000002,
		GL_LEVEL_WARNING = 0x00000003,
		GL_LEVEL_INFORMATION = 0x00000004,
		GL_ID_UNKNOWN = 0x00000000,
		GL_ID_NOMODULE = 0x00000001,
		GL_ID_NODICTIONARY = 0x00000010,
		GL_ID_CANNOTSAVE = 0x00000011,
		GL_ID_NOCONVERT = 0x00000020,
		GL_ID_TYPINGERROR = 0x00000021,
		GL_ID_TOOMANYSTROKE = 0x00000022,
		GL_ID_READINGCONFLICT = 0x00000023,
		GL_ID_INPUTREADING = 0x00000024,
		GL_ID_INPUTRADICAL = 0x00000025,
		GL_ID_INPUTCODE = 0x00000026,
		GL_ID_INPUTSYMBOL = 0x00000027,
		GL_ID_CHOOSECANDIDATE = 0x00000028,
		GL_ID_REVERSECONVERSION = 0x00000029,
		GL_ID_PRIVATE_FIRST = 0x00008000,
		GL_ID_PRIVATE_LAST = 0x0000FFFF,
		GCL_CONVERSION = 0x0001,
		GCL_REVERSECONVERSION = 0x0002,
		GCL_REVERSE_LENGTH = 0x0003,
		GROUP_NAME = 0x80,
		GMEM_FIXED = 0x0000,
		GMEM_MOVEABLE = 0x0002,
		GMEM_NOCOMPACT = 0x0010,
		GMEM_NODISCARD = 0x0020,
		GMEM_ZEROINIT = 0x0040,
		GMEM_MODIFY = 0x0080,
		GMEM_DISCARDABLE = 0x0100,
		GMEM_NOT_BANKED = 0x1000,
		GMEM_SHARE = 0x2000,
		GMEM_DDESHARE = 0x2000,
		GMEM_NOTIFY = 0x4000,
		GMEM_LOWER = 0x1000,
		GMEM_VALID_FLAGS = 0x7F72,
		GMEM_INVALID_HANDLE = 0x8000,
		GHND = (0x0002|0x0040),
		GPTR = (0x0000|0x0040),
		GMEM_DISCARDED = 0x4000,
		GMEM_LOCKCOUNT = 0x00FF,
		GET_TAPE_MEDIA_INFORMATION = 0,
		GET_TAPE_DRIVE_INFORMATION = 1,
		GDI_ERROR = (0xFFFFFFFF),
		GETCOLORTABLE = 5,
		GETPHYSPAGESIZE = 12,
		GETPRINTINGOFFSET = 13,
		GETSCALINGFACTOR = 14,
		GETPENWIDTH = 16,
		GETTECHNOLGY = 20,
		GETTECHNOLOGY = 20,
		GETVECTORPENSIZE = 26,
		GETVECTORBRUSHSIZE = 27,
		GETSETPAPERBINS = 29,
		GETSETPRINTORIENT = 30,
		GETSETPAPERMETRICS = 35,
		GETDEVICEUNITS = 42,
		GETEXTENDEDTEXTMETRICS = 256,
		GETEXTENTTABLE = 257,
		GETPAIRKERNTABLE = 258,
		GETTRACKKERNTABLE = 259,
		GETFACENAME = 513,
		GETSETSCREENPARAMS = 3072,
		GB2312_CHARSET = 134,
		GREEK_CHARSET = 161,
		GM_COMPATIBLE = 1,
		GM_ADVANCED = 2,
		GM_LAST = 2,
		GRAY_BRUSH = 2,
		GGO_METRICS = 0,
		GGO_BITMAP = 1,
		GGO_NATIVE = 2,
		GGO_GRAY2_BITMAP = 4,
		GGO_GRAY4_BITMAP = 5,
		GGO_GRAY8_BITMAP = 6,
		GGO_GLYPH_INDEX = 0x0080,
		GCP_DBCS = 0x0001,
		GCP_REORDER = 0x0002,
		GCP_USEKERNING = 0x0008,
		GCP_GLYPHSHAPE = 0x0010,
		GCP_LIGATE = 0x0020,
		GCP_DIACRITIC = 0x0100,
		GCP_KASHIDA = 0x0400,
		GCP_ERROR = 0x8000,
		GCP_JUSTIFY = 0x00010000,
		GCP_CLASSIN = 0x00080000,
		GCP_MAXEXTENT = 0x00100000,
		GCP_JUSTIFYIN = 0x00200000,
		GCP_DISPLAYZWG = 0x00400000,
		GCP_SYMSWAPOFF = 0x00800000,
		GCP_NUMERICOVERRIDE = 0x01000000,
		GCP_NEUTRALOVERRIDE = 0x02000000,
		GCP_NUMERICSLATIN = 0x04000000,
		GCP_NUMERICSLOCAL = 0x08000000,
		GCPCLASS_LATIN = 1,
		GCPCLASS_HEBREW = 2,
		GCPCLASS_ARABIC = 2,
		GCPCLASS_NEUTRAL = 3,
		GCPCLASS_LOCALNUMBER = 4,
		GCPCLASS_LATINNUMBER = 5,
		GCPCLASS_LATINNUMERICTERMINATOR = 6,
		GCPCLASS_LATINNUMERICSEPARATOR = 7,
		GCPCLASS_NUMERICSEPARATOR = 8,
		GCPCLASS_PREBOUNDLTR = 0x80,
		GCPCLASS_PREBOUNDRTL = 0x40,
		GCPCLASS_POSTBOUNDLTR = 0x20,
		GCPCLASS_POSTBOUNDRTL = 0x10,
		GCPGLYPH_LINKBEFORE = 0x8000,
		GCPGLYPH_LINKAFTER = 0x4000,
		GDICOMMENT_IDENTIFIER = 0x43494447,
		GDICOMMENT_WINDOWS_METAFILE = 0x80000001,
		GDICOMMENT_BEGINGROUP = 0x00000002,
		GDICOMMENT_ENDGROUP = 0x00000003,
		GDICOMMENT_MULTIFORMATS = 0x40000004,
		GENERIC_READ = (0x80000000),
		GENERIC_WRITE = (0x40000000),
		GENERIC_EXECUTE = (0x20000000),
		GENERIC_ALL = (0x10000000),
		GROUP_SECURITY_INFORMATION = (0X00000002),
		GWL_WNDPROC = (-4),
		GWL_HINSTANCE = (-6),
		GWL_HWNDPARENT = (-8),
		GWL_STYLE = (-16),
		GWL_EXSTYLE = (-20),
		GWL_USERDATA = (-21),
		GWL_ID = (-12),
		GCL_MENUNAME = (-8),
		GCL_HBRBACKGROUND = (-10),
		GCL_HCURSOR = (-12),
		GCL_HICON = (-14),
		GCL_HMODULE = (-16),
		GCL_CBWNDEXTRA = (-18),
		GCL_CBCLSEXTRA = (-20),
		GCL_WNDPROC = (-24),
		GCL_STYLE = (-26),
		GCW_ATOM = (-32),
		GCL_HICONSM = (-34),
		GMDI_USEDISABLED = 0x0001,
		GMDI_GOINTOPOPUPS = 0x0002,
		GW_HWNDFIRST = 0,
		GW_HWNDLAST = 1,
		GW_HWNDNEXT = 2,
		GW_HWNDPREV = 3,
		GW_OWNER = 4,
		GW_CHILD = 5,
		GW_MAX = 5,
		GMR_VISIBLE = 0,
		GMR_DAYSTATE = 1,
		GDTR_MIN = 0x0001,
		GDTR_MAX = 0x0002,
		GDT_ERROR = -1,
		GDT_VALID = 0,
		GDT_NONE = 1;

}
