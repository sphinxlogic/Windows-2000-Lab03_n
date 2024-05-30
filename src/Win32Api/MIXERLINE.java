// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct(pack=1, auto) */
public class MIXERLINE {
	public int	cbStruct = com.ms.dll.DllLib.sizeOf(this);
	public int	dwDestination;
	public int	dwSource;
	public int	dwLineID;
	public int	fdwLine;
	public int	dwUser;
	public int	dwComponentType;
	public int	cChannels;
	public int	cConnections;
	public int	cControls;
	/** @dll.structmap([type=TCHAR[16]]) */
	public String	szShortName;
	/** @dll.structmap([type=TCHAR[64]]) */
	public String	szName;
	// Target was a by-value anonymous_data_structure structure
	public int	Target_dwType;
	public int	Target_dwDeviceID;
	public short	Target_wMid;
	public short	Target_wPid;
	public int	Target_vDriverVersion;
	/** @dll.structmap([type=TCHAR[32]]) */
	public String	Target_szPname;
}

