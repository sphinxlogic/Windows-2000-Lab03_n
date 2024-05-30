// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Spoolss {
        /** @dll.import("SPOOLSS",auto) */
        public native static boolean AbortPrinter (int hPrinter);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean AddForm (int hPrinter, int Level, FORM_INFO_1 pForm);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean AddJob (int hPrinter, int Level, Object pData, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean AddMonitor (String pName, int Level, Object pMonitors);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean AddPort (String pName, int hWnd, String pMonitorName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean AddPrintProcessor (String pName, String pEnvironment, String pPathName, String pPrintProcessorName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean AddPrintProvidor (String pName, int level, Object pProvidorInfo);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean AddPrinterConnection (String pName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean AddPrinterDriver (String pName, int Level, Object pDriverInfo);

        /** @dll.import("SPOOLSS", auto) */
        public native static int AddPrinter (String pName, int Level, Object pPrinter);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean ClosePrinter (int hPrinter);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean ConfigurePort (String pName, int hWnd, String pPortName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeleteForm (int hPrinter, String pFormName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeleteMonitor (String pName, String pEnvironment, String pMonitorName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeletePort (String pName, int hWnd, String pPortName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeletePrintProcessor (String pName, String pEnvironment, String pPrintProcessorName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeletePrintProvidor (String pName, String pEnvironment, String pPrintProvidorName);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean DeletePrinter (int hPrinter);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeletePrinterConnection (String pName);

        /** @dll.import("SPOOLSS", auto) */
        public native static int DeletePrinterData (int hPrinter, String pValueName);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean DeletePrinterDriver (String pName, String pEnvironment, String pDriverName);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean EndDocPrinter (int hPrinter);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean EndPagePrinter (int hPrinter);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean EnumForms (int hPrinter, int Level, Object pForm, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean EnumJobs (int hPrinter, int FirstJob, int NoJobs, int Level, Object pJob, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean EnumMonitors (String pName, int Level, Object pMonitors, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean EnumPorts (String pName, int Level, Object pPorts, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean EnumPrintProcessorDatatypes (String pName, String pPrintProcessorName, int Level, Object pDatatypes, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean EnumPrintProcessors (String pName, String pEnvironment, int Level, Object pPrintProcessorInfo, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS", auto) */
        public native static int EnumPrinterData (int hPrinter, int dwIndex, String pValueName, int cbValueName, int[] pcbValueName, int[] pType, Object pData, int cbData, int[] pcbData);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean EnumPrinterDrivers (String pName, String pEnvironment, int Level, Object pDriverInfo, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean EnumPrinters (int Flags, String Name, int Level, Object pPrinterEnum, int cbBuf, int[] pcbNeeded, int[] pcReturned);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean FindClosePrinterChangeNotification (int hChange);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean GetForm (int hPrinter, String pFormName, int Level, Object pForm, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean GetJob (int hPrinter, int JobId, int Level, Object pJob, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean GetPrintProcessorDirectory (String pName, String pEnvironment, int Level, Object pPrintProcessorInfo, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS", auto) */
        public native static int GetPrinterData (int hPrinter, String pValueName, int[] pType, Object pData, int nSize, int[] pcbNeeded);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean GetPrinterDriverDirectory (String pName, String pEnvironment, int Level, Object pDriverDirectory, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean GetPrinterDriver (int hPrinter, String pEnvironment, int Level, Object pDriverInfo, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean GetPrinter (int hPrinter, int Level, Object pPrinter, int cbBuf, int[] pcbNeeded);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean OpenPrinter (String pPrinterName, int[] phPrinter, PRINTER_DEFAULTS pDefault);

        /** @dll.import("SPOOLSS", auto) */
        public native static int PrinterMessageBox (int hPrinter, int Error, int hWnd, String pText, String pCaption, int dwType);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean ReadPrinter (int hPrinter, Object pBuf, int cbBuf, int[] pNoBytesRead);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean ResetPrinter (int hPrinter, PRINTER_DEFAULTS pDefault);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean ScheduleJob (int hPrinter, int JobId);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean SetForm (int hPrinter, String pFormName, int Level, FORM_INFO_1 pForm);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean SetJob (int hPrinter, int JobId, int Level, Object pJob, int Command);

        /** @dll.import("SPOOLSS", auto) */
        public native static boolean SetPort (String pName, String pPortName, int dwLevel, Object pPortInfo);

        /** @dll.import("SPOOLSS", auto) */
        public native static int SetPrinterData (int hPrinter, String pValueName, int Type, Object pData, int cbData);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean SetPrinter (int hPrinter, int Level, Object pPrinter, int Command);

        /** @dll.import("SPOOLSS",auto) */
        public native static int StartDocPrinter (int hPrinter, int Level, Object pDocInfo);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean StartPagePrinter (int hPrinter);

        /** @dll.import("SPOOLSS",auto) */
        public native static int WaitForPrinterChange (int hPrinter, int Flags);

        /** @dll.import("SPOOLSS",auto) */
        public native static boolean WritePrinter (int hPrinter, Object pBuf, int cbBuf, int[] pcWritten);
}

