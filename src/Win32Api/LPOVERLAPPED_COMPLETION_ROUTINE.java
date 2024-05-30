// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class LPOVERLAPPED_COMPLETION_ROUTINE extends Callback {
	public abstract int lpoverlapped_completion_routine(int dwErrorCode, int dwNumberOfBytesTransferred, OVERLAPPED lpOverlapped);

	protected int callback(int dwErrorCode, int dwNumberOfBytesTransferred, int lpOverlapped)
	{
		return lpoverlapped_completion_routine(dwErrorCode, dwNumberOfBytesTransferred, (OVERLAPPED)DllLib.ptrToStruct(OVERLAPPED.class, lpOverlapped));
	}
}

