// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;



/** @dll.struct() */
public class BY_HANDLE_FILE_INFORMATION {
	public int	dwFileAttributes;
	// ftCreationTime was a by-value FILETIME structure
	public int	ftCreationTime_dwLowDateTime;
	public int	ftCreationTime_dwHighDateTime;
	// ftLastAccessTime was a by-value FILETIME structure
	public int	ftLastAccessTime_dwLowDateTime;
	public int	ftLastAccessTime_dwHighDateTime;
	// ftLastWriteTime was a by-value FILETIME structure
	public int	ftLastWriteTime_dwLowDateTime;
	public int	ftLastWriteTime_dwHighDateTime;
	public int	dwVolumeSerialNumber;
	public int	nFileSizeHigh;
	public int	nFileSizeLow;
	public int	nNumberOfLinks;
	public int	nFileIndexHigh;
	public int	nFileIndexLow;
}

