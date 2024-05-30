// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Lz32 {
	/** @dll.import("LZ32", auto) */
	public native static int CopyLZFile (int anon0, int anon1);

	/** @dll.import("LZ32", auto) */
	public native static int GetExpandedName (StringBuffer anon0, StringBuffer anon1);

	/** @dll.import("LZ32", auto) */
	public native static void LZClose (int anon0);

	/** @dll.import("LZ32", auto) */
	public native static int LZCopy (int anon0, int anon1);

	/** @dll.import("LZ32", auto) */
	public native static void LZDone ();

	/** @dll.import("LZ32", auto) */
	public native static int LZInit (int anon0);

	/** @dll.import("LZ32", auto) */
	public native static int LZOpenFile (StringBuffer anon0, OFSTRUCT anon1, short anon2);

	/** @dll.import("LZ32", ansi) */
	public native static int LZRead (int anon0, StringBuffer anon1, int anon2);

	/** @dll.import("LZ32", auto) */
	public native static int LZSeek (int anon0, int anon1, int anon2);

	/** @dll.import("LZ32", auto) */
	public native static int LZStart ();


}

