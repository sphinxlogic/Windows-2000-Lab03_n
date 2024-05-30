// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class LPPROGRESS_ROUTINE extends Callback {
	public abstract int lpprogress_routine(long TotalFileSize, long TotalBytesTransferred, long StreamSize, long StreamBytesTransferred, int dwStreamNumber, int dwCallbackReason, int hSourceFile, int hDestinationFile, int lpData);

	protected int callback(long TotalFileSize, long TotalBytesTransferred, long StreamSize, long StreamBytesTransferred, int dwStreamNumber, int dwCallbackReason, int hSourceFile, int hDestinationFile, int lpData)
	{
		return lpprogress_routine(TotalFileSize, TotalBytesTransferred, StreamSize, StreamBytesTransferred, dwStreamNumber, dwCallbackReason, hSourceFile, hDestinationFile, lpData);
	}
}

