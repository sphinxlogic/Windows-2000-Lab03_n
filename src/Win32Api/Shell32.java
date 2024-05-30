// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Shell32 {
        /** @dll.import("SHELL32", unicode) */
        public native static int CommandLineToArgvW (String lpCmdLine, int[] pNumArgs);

        /** @dll.import("SHELL32",auto) */
        public native static void DragAcceptFiles (int anonymous0, boolean anonymous1);

        /** @dll.import("SHELL32",auto) */
        public native static void DragFinish (int anonymous0);

        /** @dll.import("SHELL32", auto) */
        public native static int DragQueryFile (int anonymous0, int anonymous1, StringBuffer anonymous2, int anonymous3);

        /** @dll.import("SHELL32",auto) */
        public native static boolean DragQueryPoint (int anonymous0, POINT anonymous1);

        /** @dll.import("SHELL32", auto) */
        public native static int ExtractAssociatedIcon (int hInst, StringBuffer lpIconPath, short[] lpiIcon);

        /** @dll.import("SHELL32", auto) */
        public native static int ExtractIconEx (String lpszFile, int nIconIndex, int[] phiconLarge, int[] phiconSmall, int nIcons);

        /** @dll.import("SHELL32", auto) */
        public native static int ExtractIcon (int hInst, String lpszExeFileName, int nIconIndex);

        /** @dll.import("SHELL32", auto) */
        public native static int FindExecutable (String lpFile, String lpDirectory, StringBuffer lpResult);

        /** @dll.import("SHELL32",auto) */
        public native static int SHAppBarMessage (int dwMessage, APPBARDATA pData);

        /** @dll.import("SHELL32",auto) */
        public native static int SHFileOperation (SHFILEOPSTRUCT lpFileOp);

        /** @dll.import("SHELL32",auto) */
        public native static void SHFreeNameMappings (int hNameMappings);

        /** @dll.import("SHELL32", auto) */
        public native static int SHGetFileInfo (String pszPath, int dwFileAttributes, SHFILEINFO psfi, int cbFileInfo, int uFlags);

        /** @dll.import("SHELL32", auto) */
        public native static int ShellAbout (int hWnd, String szApp, String szOtherStuff, int hIcon);

        /** @dll.import("SHELL32",auto) */
        public native static boolean ShellExecuteEx (SHELLEXECUTEINFO lpExecInfo);

        /** @dll.import("SHELL32", auto) */
        public native static int ShellExecute (int hwnd, String lpOperation, String lpFile, String lpParameters, String lpDirectory, int nShowCmd);

        /** @dll.import("SHELL32",auto) */
        public native static boolean Shell_NotifyIcon (int dwMessage, NOTIFYICONDATA lpData);
}

