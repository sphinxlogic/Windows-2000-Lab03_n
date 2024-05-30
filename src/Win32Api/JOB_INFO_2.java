// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class JOB_INFO_2 {
        public int JobId;
        public String pPrinterName;
        public String pMachineName;
        public String pUserName;
        public String pDocument;
        public String pNotifyName;
        public String pDatatype;
        public String pPrintProcessor;
        public String pParameters;
        public String pDriverName;
        public int  pDevMode;
        public String pStatus;
        public int pSecurityDescriptor;
        public int Status;
        public int Priority;
        public int Position;
        public int StartTime;
        public int UntilTime;
        public int TotalPages;
        public int Size;
        public SYSTEMTIME       Submitted;
        public int Time;
        public int PagesPrinted;
}

