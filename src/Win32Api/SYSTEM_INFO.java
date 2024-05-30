// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct() */
public class SYSTEM_INFO {
    public short wProcessorArchitecture;
    public short wReserved;
    public int   dwPageSize;
    public int   lpMinimumApplicationAddress;
    public int   lpMaximumApplicationAddress;
    public int   dwActiveProcessorMask;
    public int   dwNumberOfProcessors;
    public int   dwProcessorType;
    public int   dwAllocationGranularity;
    public short wProcessorLevel;
    public short wProcessorRevision;
}

