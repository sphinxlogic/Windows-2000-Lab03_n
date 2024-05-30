// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Kernel32 {
        /** @dll.import("KERNEL32", auto) */
        public native static short AddAtom (String lpString);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean AllocConsole ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean AreFileApisANSI ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean BackupRead (int hFile, byte[] lpBuffer, int nNumberOfBytesToRead, int[] lpNumberOfBytesRead, boolean bAbort, boolean bProcessSecurity, int[] lpContext);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean BackupRead (int hFile, Object lpBuffer, int nNumberOfBytesToRead, int[] lpNumberOfBytesRead, boolean bAbort, boolean bProcessSecurity, int[] lpContext);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean BackupSeek (int hFile, int dwLowBytesToSeek, int dwHighBytesToSeek, int[] lpdwLowByteSeeked, int[] lpdwHighByteSeeked, int[] lpContext);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean BackupWrite (int hFile, byte[] lpBuffer, int nNumberOfBytesToWrite, int[] lpNumberOfBytesWritten, boolean bAbort, boolean bProcessSecurity, int[] lpContext);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean BackupWrite (int hFile, Object lpBuffer, int nNumberOfBytesToWrite, int[] lpNumberOfBytesWritten, boolean bAbort, boolean bProcessSecurity, int[] lpContext);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean Beep (int dwFreq, int dwDuration);

        /** @dll.import("KERNEL32", auto) */
        public native static int BeginUpdateResource (String pFileName, boolean bDeleteExistingResources);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean BuildCommDCBAndTimeouts (String lpDef, DCB lpDCB, COMMTIMEOUTS lpCommTimeouts);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean BuildCommDCB (String lpDef, DCB lpDCB);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean CallNamedPipe (String lpNamedPipeName, Object lpInBuffer, int nInBufferSize, Object lpOutBuffer, int nOutBufferSize, int[] lpBytesRead, int nTimeOut);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean CancelIo (int hFile);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean CancelWaitableTimer (int hTimer);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ClearCommBreak (int hFile);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ClearCommError (int hFile, int[] lpErrors, COMSTAT lpStat);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean CloseHandle (int hObject);



        /** @dll.import("KERNEL32",auto) */
        public native static int CompareFileTime (FILETIME lpFileTime1, FILETIME lpFileTime2);

        /** @dll.import("KERNEL32", auto) */
        public native static int CompareString (int Locale, int dwCmpFlags, String lpString1, int cchCount1, String lpString2, int cchCount2);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ConnectNamedPipe (int hNamedPipe, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ContinueDebugEvent (int dwProcessId, int dwThreadId, int dwContinueStatus);

        /** @dll.import("KERNEL32",auto) */
        public native static int ConvertDefaultLocale (int Locale);

        /** @dll.import("KERNEL32",auto) */
        public native static int ConvertThreadToFiber (int lpParameter);


        private static int expandCoord(COORD c)
        {
            return ( ((int)c.X) & 0xffff ) | ( ((int)c.Y) << 16);
        }


        /** @dll.import("KERNEL32", auto) */
        public native static boolean CopyFileEx (String lpExistingFileName, String lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, int lpData, int[] pbCancel, int dwCopyFlags);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean CopyFile (String lpExistingFileName, String lpNewFileName, boolean bFailIfExists);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateConsoleScreenBuffer (int dwDesiredAccess, int dwShareMode, SECURITY_ATTRIBUTES lpSecurityAttributes, int dwFlags, int lpScreenBufferData);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean CreateDirectoryEx (String lpTemplateDirectory, String lpNewDirectory, SECURITY_ATTRIBUTES lpSecurityAttributes);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean CreateDirectory (String lpPathName, SECURITY_ATTRIBUTES lpSecurityAttributes);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateEvent (SECURITY_ATTRIBUTES lpEventAttributes, boolean bManualReset, boolean bInitialState, String lpName);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateFiber (int dwStackSize, LPFIBER_START_ROUTINE lpStartAddress, int lpParameter);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateFiber (int dwStackSize, com.ms.dll.Callback lpStartAddress, int lpParameter);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateFileMapping (int hFile, SECURITY_ATTRIBUTES lpFileMappingAttributes, int flProtect, int dwMaximumSizeHigh, int dwMaximumSizeLow, String lpName);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateFile (String lpFileName, int dwDesiredAccess, int dwShareMode, SECURITY_ATTRIBUTES lpSecurityAttributes, int dwCreationDisposition, int dwFlagsAndAttributes, int hTemplateFile);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateIoCompletionPort (int FileHandle, int ExistingCompletionPort, int CompletionKey, int NumberOfConcurrentThreads);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateMailslot (String lpName, int nMaxMessageSize, int lReadTimeout, SECURITY_ATTRIBUTES lpSecurityAttributes);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateMutex (SECURITY_ATTRIBUTES lpMutexAttributes, boolean bInitialOwner, String lpName);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateNamedPipe (String lpName, int dwOpenMode, int dwPipeMode, int nMaxInstances, int nOutBufferSize, int nInBufferSize, int nDefaultTimeOut, SECURITY_ATTRIBUTES lpSecurityAttributes);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean CreatePipe (int[] hReadPipe, int[] hWritePipe, SECURITY_ATTRIBUTES lpPipeAttributes, int nSize);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean CreateProcess (String lpApplicationName, String lpCommandLine, SECURITY_ATTRIBUTES lpProcessAttributes, SECURITY_ATTRIBUTES lpThreadAttributes, boolean bInheritHandles, int dwCreationFlags, int lpEnvironment, String lpCurrentDirectory, STARTUPINFO lpStartupInfo, PROCESS_INFORMATION lpProcessInformation);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateRemoteThread (int hProcess, SECURITY_ATTRIBUTES lpThreadAttributes, int dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, int lpParameter, int dwCreationFlags, int[] lpThreadId);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateSemaphore (SECURITY_ATTRIBUTES lpSemaphoreAttributes, int lInitialCount, int lMaximumCount, String lpName);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateTapePartition (int hDevice, int dwPartitionMethod, int dwCount, int dwSize);

        /** @dll.import("KERNEL32",auto) */
        public native static int CreateThread (SECURITY_ATTRIBUTES lpThreadAttributes, int dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, int lpParameter, int dwCreationFlags, int[] lpThreadId);

        /** @dll.import("KERNEL32", auto) */
        public native static int CreateWaitableTimer (SECURITY_ATTRIBUTES lpTimerAttributes, boolean bManualReset, String lpTimerName);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DebugActiveProcess (int dwProcessId);

        /** @dll.import("KERNEL32",auto) */
        public native static void DebugBreak ();

        /** @dll.import("KERNEL32", auto) */
        public native static boolean DefineDosDevice (int dwFlags, String lpDeviceName, String lpTargetPath);

        /** @dll.import("KERNEL32",auto) */
        public native static short DeleteAtom (short nAtom);



        /** @dll.import("KERNEL32",auto) */
        public native static void DeleteFiber (int lpFiber);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean DeleteFile (String lpFileName);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DeviceIoControl (int hDevice, int dwIoControlCode, int lpInBuffer, int nInBufferSize, int lpOutBuffer, int nOutBufferSize, int[] lpBytesReturned, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DeviceIoControl (int hDevice, int dwIoControlCode, Object lpInBuffer, int nInBufferSize, Object lpOutBuffer, int nOutBufferSize, int[] lpBytesReturned, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DisableThreadLibraryCalls (int hLibModule);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DisconnectNamedPipe (int hNamedPipe);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DosDateTimeToFileTime (short wFatDate, short wFatTime, FILETIME lpFileTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean DuplicateHandle (int hSourceProcessHandle, int hSourceHandle, int hTargetProcessHandle, int[] lpTargetHandle, int dwDesiredAccess, boolean bInheritHandle, int dwOptions);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EndUpdateResource (int hUpdate, boolean fDiscard);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean EnumCalendarInfo (CALINFO_ENUMPROC lpCalInfoEnumProc, int Locale, int Calendar, int CalType);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EnumDateFormats (DATEFMT_ENUMPROC lpDateFmtEnumProc, int Locale, int dwFlags);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean EnumResourceLanguages (int hModule, String lpType, String lpName, ENUMRESLANGPROC lpEnumFunc, int lParam);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean EnumResourceNames (int hModule, String lpType, ENUMRESNAMEPROC lpEnumFunc, int lParam);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EnumResourceTypes (int hModule, ENUMRESTYPEPROC lpEnumFunc, int lParam);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EnumSystemCodePages (CODEPAGE_ENUMPROC lpCodePageEnumProc, int dwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EnumSystemLocales (LOCALE_ENUMPROC lpLocaleEnumProc, int dwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EnumTimeFormats (TIMEFMT_ENUMPROC lpTimeFmtEnumProc, int Locale, int dwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static int EraseTape (int hDevice, int dwEraseType, boolean bImmediate);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean EscapeCommFunction (int hFile, int dwFunc);

        /** @dll.import("KERNEL32",auto) */
        public native static void ExitProcess (int uExitCode);

        /** @dll.import("KERNEL32",auto) */
        public native static void ExitThread (int dwExitCode);

        /** @dll.import("KERNEL32", auto) */
        public native static int ExpandEnvironmentStrings (String lpSrc, StringBuffer lpDst, int nSize);

        /** @dll.import("KERNEL32", auto) */
        public native static void FatalAppExit (int uAction, String lpMessageText);

        /** @dll.import("KERNEL32",auto) */
        public native static void FatalExit (int ExitCode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FileTimeToDosDateTime (FILETIME lpFileTime, short[] lpFatDate, short[] lpFatTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FileTimeToLocalFileTime (FILETIME lpFileTime, FILETIME lpLocalFileTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FileTimeToSystemTime (FILETIME lpFileTime, SYSTEMTIME lpSystemTime);

        /** @dll.import("KERNEL32", auto, entrypoint="FillConsoleOutputAttribute") */
        private native static boolean FillConsoleOutputAttribute_I (int hConsoleOutput, short wAttribute, int nLength, int dwWriteCoord, int[] lpNumberOfAttrsWritten);
		  
        public static boolean FillConsoleOutputAttribute (int hConsoleOutput, short wAttribute, int nLength, COORD dwWriteCoord, int[] lpNumberOfAttrsWritten)
		{
		   return FillConsoleOutputAttribute_I (hConsoleOutput, wAttribute, nLength, expandCoord(dwWriteCoord), lpNumberOfAttrsWritten);
		}

        /** @dll.import("KERNEL32", auto, entrypoint="FillConsoleOutputCharacter") */
        private native static boolean FillConsoleOutputCharacter_I (int hConsoleOutput, char cCharacter, int nLength, int dwWriteCoord, int[] lpNumberOfCharsWritten);

        public static boolean FillConsoleOutputCharacter (int hConsoleOutput, char cCharacter, int nLength, COORD dwWriteCoord, int[] lpNumberOfCharsWritten)
		{
		   return FillConsoleOutputCharacter_I (hConsoleOutput, cCharacter, nLength, expandCoord(dwWriteCoord), lpNumberOfCharsWritten);
		}

        /** @dll.import("KERNEL32", auto) */
        public native static short FindAtom (String lpString);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FindClose (int hFindFile);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FindCloseChangeNotification (int hChangeHandle);

        /** @dll.import("KERNEL32", auto) */
        public native static int FindFirstChangeNotification (String lpPathName, boolean bWatchSubtree, int dwNotifyFilter);

        /** @dll.import("KERNEL32", auto, setLastError) */
        public native static int FindFirstFileEx (String lpFileName, int fInfoLevelId, Object lpFindFileData, int fSearchOp, Object lpSearchFilter, int dwAdditionalFlags);

        /** @dll.import("KERNEL32", auto, setLastError) */
        public native static int FindFirstFile (String lpFileName, WIN32_FIND_DATA lpFindFileData);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FindNextChangeNotification (int hChangeHandle);

        /** @dll.import("KERNEL32",auto,setLastError) */
        public native static boolean FindNextFile (int hFindFile, WIN32_FIND_DATA lpFindFileData);

        /** @dll.import("KERNEL32", auto) */
        public native static int FindResourceEx (int hModule, String lpType, String lpName, short wLanguage);

        /** @dll.import("KERNEL32", auto) */
        public native static int FindResource (int hModule, String lpName, String lpType);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FlushConsoleInputBuffer (int hConsoleInput);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FlushFileBuffers (int hFile);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FlushInstructionCache (int hProcess, int lpBaseAddress, int dwSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FlushViewOfFile (int lpBaseAddress, int dwNumberOfBytesToFlush);

        /** @dll.import("KERNEL32", auto) */
        public native static int FoldString (int dwMapFlags, String lpSrcStr, int cchSrc, StringBuffer lpDestStr, int cchDest);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean FreeConsole ();

        /** @dll.import("KERNEL32", auto) */
        public native static boolean FreeEnvironmentStrings (int anonymous0);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FreeLibrary (int hLibModule);

        /** @dll.import("KERNEL32",auto) */
        public native static void FreeLibraryAndExitThread (int hLibModule, int dwExitCode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean FreeResource (int hResData);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GenerateConsoleCtrlEvent (int dwCtrlEvent, int dwProcessGroupId);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetACP ();

        /** @dll.import("KERNEL32", auto) */
        public native static int GetAtomName (short nAtom, StringBuffer lpBuffer, int nSize);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetBinaryType (String lpApplicationName, int[] lpBinaryType);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetCPInfo (int CodePage, CPINFO lpCPInfo);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetCommMask (int hFile, int[] lpEvtMask);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetCommModemStatus (int hFile, int[] lpModemStat);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetCommState (int hFile, DCB lpDCB);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetCommTimeouts (int hFile, COMMTIMEOUTS lpCommTimeouts);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetCommandLine ();

        /** @dll.import("KERNEL32", auto) */
        public native static int GetCompressedFileSize (String lpFileName, int[] lpFileSizeHigh);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetComputerName (StringBuffer lpBuffer, int[] nSize);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetConsoleCP ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetConsoleCursorInfo (int hConsoleOutput, CONSOLE_CURSOR_INFO lpConsoleCursorInfo);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetConsoleMode (int hConsoleHandle, int[] lpMode);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetConsoleOutputCP ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetConsoleScreenBufferInfo (int hConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetConsoleTitle (StringBuffer lpConsoleTitle, int nSize);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetCurrencyFormat (int Locale, int dwFlags, String lpValue, CURRENCYFMT lpFormat, StringBuffer lpCurrencyStr, int cchCurrency);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetCurrentDirectory (int nBufferLength, StringBuffer lpBuffer);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetCurrentProcess ();

        /** @dll.import("KERNEL32",auto) */
        public native static int GetCurrentProcessId ();

        /** @dll.import("KERNEL32",auto) */
        public native static int GetCurrentThread ();

        /** @dll.import("KERNEL32",auto) */
        public native static int GetCurrentThreadId ();

        /** @dll.import("KERNEL32", auto) */
        public native static int GetDateFormat (int Locale, int dwFlags, SYSTEMTIME lpDate, String lpFormat, StringBuffer lpDateStr, int cchDate);



        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetDiskFreeSpaceEx (String lpDirectoryName, long[] lpFreeBytesAvailableToCaller, long[] lpTotalNumberOfBytes, long[] lpTotalNumberOfFreeBytes);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetDiskFreeSpace (String lpRootPathName, int[] lpSectorsPerCluster, int[] lpBytesPerSector, int[] lpNumberOfFreeClusters, int[] lpTotalNumberOfClusters);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetDriveType (String lpRootPathName);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetEnvironmentStrings ();

        /** @dll.import("KERNEL32", auto) */
        public native static int GetEnvironmentVariable (String lpName, StringBuffer lpBuffer, int nSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetExitCodeProcess (int hProcess, int[] lpExitCode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetExitCodeThread (int hThread, int[] lpExitCode);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetFileAttributesEx (String lpFileName, int fInfoLevelId, Object lpFileInformation);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetFileAttributes (String lpFileName);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetFileInformationByHandle (int hFile, BY_HANDLE_FILE_INFORMATION lpFileInformation);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetFileSize (int hFile, int[] lpFileSizeHigh);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetFileTime (int hFile, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetFileType (int hFile);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetFullPathName (String lpFileName, int nBufferLength, StringBuffer lpBuffer, int lpFilePart);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetHandleInformation (int hObject, int[] lpdwFlags);

        /** @dll.import("KERNEL32",auto, entrypoint="GetLargestConsoleWindowSize") */
        private native static int GetLargestConsoleWindowSize_I (int hConsoleOutput);

        public static COORD GetLargestConsoleWindowSize (int hConsoleOutput)
		  {
			  int coord_val = GetLargestConsoleWindowSize_I (hConsoleOutput);
			  COORD c = new COORD();
			  c.X = (short) (coord_val >> 16);
			  c.Y = (short) (coord_val & 0xFFFF);
			  return c;
		  }

        /** @dll.import("KERNEL32",auto) */
        public native static int GetLastError ();

        /** @dll.import("KERNEL32",auto) */
        public native static void GetLocalTime (SYSTEMTIME lpSystemTime);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetLocaleInfo (int Locale, int LCType, StringBuffer lpLCData, int cchData);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetLogicalDriveStrings (int nBufferLength, Object lpBuffer);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetLogicalDrives ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetMailslotInfo (int hMailslot, int[] lpMaxMessageSize, int[] lpNextSize, int[] lpMessageCount, int[] lpReadTimeout);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetModuleFileName (int hModule, StringBuffer lpFilename, int nSize);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetModuleHandle (String lpModuleName);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetNamedPipeHandleState (int hNamedPipe, int[] lpState, int[] lpCurInstances, int[] lpMaxCollectionCount, int[] lpCollectDataTimeout, StringBuffer lpUserName, int nMaxUserNameSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetNamedPipeInfo (int hNamedPipe, int[] lpFlags, int[] lpOutBufferSize, int[] lpInBufferSize, int[] lpMaxInstances);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetNumberFormat (int Locale, int dwFlags, String lpValue, NUMBERFMT lpFormat, StringBuffer lpNumberStr, int cchNumber);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetNumberOfConsoleInputEvents (int hConsoleInput, int[] lpNumberOfEvents);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetNumberOfConsoleMouseButtons (int[] lpNumberOfMouseButtons);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetOEMCP ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetOverlappedResult (int hFile, OVERLAPPED lpOverlapped, int[] lpNumberOfBytesTransferred, boolean bWait);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetPriorityClass (int hProcess);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetPrivateProfileInt (String lpAppName, String lpKeyName, int nDefault, String lpFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetPrivateProfileSectionNames (Object lpszReturnBuffer, int nSize, String lpFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetPrivateProfileSection (String lpAppName, Object lpReturnedString, int nSize, String lpFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetPrivateProfileString (String lpAppName, String lpKeyName, String lpDefault, StringBuffer lpReturnedString, int nSize, String lpFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetPrivateProfileStruct (String lpszSection, String lpszKey, Object lpStruct, int uSizeStruct, String szFile);

        /** @dll.import("KERNEL32", ansi) */
        public native static int GetProcAddress (int hModule, String lpProcName);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetProcessAffinityMask (int hProcess, int[] lpProcessAffinityMask, int[] lpSystemAffinityMask);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetProcessHeap ();

        /** @dll.import("KERNEL32",auto) */
        public native static int GetProcessHeaps (int NumberOfHeaps, int[] ProcessHeaps);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetProcessPriorityBoost (int hProcess, boolean[] pDisablePriorityBoost);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetProcessShutdownParameters (int[] lpdwLevel, int[] lpdwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetProcessTimes (int hProcess, FILETIME lpCreationTime, FILETIME lpExitTime, FILETIME lpKernelTime, FILETIME lpUserTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetProcessVersion (int ProcessId);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetProcessWorkingSetSize (int hProcess, int[] lpMinimumWorkingSetSize, int[] lpMaximumWorkingSetSize);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetProfileInt (String lpAppName, String lpKeyName, int nDefault);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetProfileSection (String lpAppName, Object lpReturnedString, int nSize);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetProfileString (String lpAppName, String lpKeyName, String lpDefault, StringBuffer lpReturnedString, int nSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetQueuedCompletionStatus (int CompletionPort, int[] lpNumberOfBytesTransferred, int[] lpCompletionKey, OVERLAPPED lpOverlapped, int dwMilliseconds);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetShortPathName (String lpszLongPath, StringBuffer lpszShortPath, int cchBuffer);

        /** @dll.import("KERNEL32",entrypoint="GetStartupInfo") */
        private native static void GetStartupInfo_I (STARTUPINFO_I lpStartupInfo);

        public static void GetStartupInfo(STARTUPINFO lpStartupInfo)
        {
            STARTUPINFO_I sii = new STARTUPINFO_I();
            sii.cb = com.ms.dll.DllLib.sizeOf(sii.getClass());
            GetStartupInfo_I(sii);
            lpStartupInfo.cb                = sii.cb;
            lpStartupInfo.lpReserved        = com.ms.dll.DllLib.ptrToString(sii.lpReserved);
            lpStartupInfo.lpDesktop         = com.ms.dll.DllLib.ptrToString(sii.lpDesktop);
            lpStartupInfo.lpTitle           = com.ms.dll.DllLib.ptrToString(sii.lpTitle);
            lpStartupInfo.dwX               = sii.dwX;
            lpStartupInfo.dwY               = sii.dwY;
            lpStartupInfo.dwXSize           = sii.dwXSize;
            lpStartupInfo.dwYSize           = sii.dwYSize;
            lpStartupInfo.dwXCountChars     = sii.dwXCountChars;
            lpStartupInfo.dwYCountChars     = sii.dwYCountChars;
            lpStartupInfo.dwFillAttribute   = sii.dwFillAttribute;
            lpStartupInfo.dwFlags           = sii.dwFlags;
            lpStartupInfo.wShowWindow       = sii.wShowWindow;
            lpStartupInfo.cbReserved2       = sii.cbReserved2;
            lpStartupInfo.lpReserved2       = sii.lpReserved2;
            lpStartupInfo.hStdInput         = sii.hStdInput;
            lpStartupInfo.hStdOutput        = sii.hStdOutput;
            lpStartupInfo.hStdError         = sii.hStdError;
        }

        /** @dll.import("KERNEL32",auto) */
        public native static int GetStdHandle (int nStdHandle);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetStringTypeEx (int Locale, int dwInfoType, String lpSrcStr, int cchSrc, short[] lpCharType);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetStringType (int dwInfoType, String lpSrcStr, int cchSrc, short[] lpCharType);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetSystemDefaultLCID ();

        /** @dll.import("KERNEL32",auto) */
        public native static short GetSystemDefaultLangID ();

        /** @dll.import("KERNEL32", auto) */
        public native static int GetSystemDirectory (StringBuffer lpBuffer, int uSize);

        /** @dll.import("KERNEL32", auto) */
        public native static void GetSystemInfo(SYSTEM_INFO lpSystemInfo);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetSystemPowerStatus (SYSTEM_POWER_STATUS lpSystemPowerStatus);

        /** @dll.import("KERNEL32",auto) */
        public native static void GetSystemTime (SYSTEMTIME lpSystemTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetSystemTimeAdjustment (int[] lpTimeAdjustment, int[] lpTimeIncrement, boolean[] lpTimeAdjustmentDisabled);

        /** @dll.import("KERNEL32",auto) */
        public native static void GetSystemTimeAsFileTime (FILETIME lpSystemTimeAsFileTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetTapeParameters (int hDevice, int dwOperation, int[] lpdwSize, Object lpTapeInformation);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetTapePosition (int hDevice, int dwPositionType, int[] lpdwPartition, int[] lpdwOffsetLow, int[] lpdwOffsetHigh);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetTapeStatus (int hDevice);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetTempFileName (String lpPathName, String lpPrefixString, int uUnique, StringBuffer lpTempFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetTempPath (int nBufferLength, StringBuffer lpBuffer);



        /** @dll.import("KERNEL32",auto) */
        public native static int GetThreadLocale ();

        /** @dll.import("KERNEL32",auto) */
        public native static int GetThreadPriority (int hThread);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetThreadPriorityBoost (int hThread, boolean[] pDisablePriorityBoost);


        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetThreadTimes (int hThread, FILETIME lpCreationTime, FILETIME lpExitTime, FILETIME lpKernelTime, FILETIME lpUserTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetTickCount ();

        /** @dll.import("KERNEL32", auto) */
        public native static int GetTimeFormat (int Locale, int dwFlags, SYSTEMTIME lpTime, String lpFormat, StringBuffer lpTimeStr, int cchTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetTimeZoneInformation (TIME_ZONE_INFORMATION lpTimeZoneInformation);

        /** @dll.import("KERNEL32",auto) */
        public native static int GetUserDefaultLCID ();

        /** @dll.import("KERNEL32",auto) */
        public native static short GetUserDefaultLangID ();

        /** @dll.import("KERNEL32",auto) */
        public native static int GetVersion ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GetVersionEx (OSVERSIONINFO lpVersionInformation);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean GetVolumeInformation (String lpRootPathName, StringBuffer lpVolumeNameBuffer, int nVolumeNameSize, int[] lpVolumeSerialNumber, int[] lpMaximumComponentLength, int[] lpFileSystemFlags, StringBuffer lpFileSystemNameBuffer, int nFileSystemNameSize);

        /** @dll.import("KERNEL32", auto) */
        public native static int GetWindowsDirectory (StringBuffer lpBuffer, int uSize);

        /** @dll.import("KERNEL32", auto) */
        public native static short GlobalAddAtom (String lpString);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalAlloc (int uFlags, int dwBytes);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalCompact (int dwMinFree);

        /** @dll.import("KERNEL32",auto) */
        public native static short GlobalDeleteAtom (short nAtom);

        /** @dll.import("KERNEL32", auto) */
        public native static short GlobalFindAtom (String lpString);

        /** @dll.import("KERNEL32",auto) */
        public native static void GlobalFix (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalFlags (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalFree (int hMem);

        /** @dll.import("KERNEL32", auto) */
        public native static int GlobalGetAtomName (short nAtom, StringBuffer lpBuffer, int nSize);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalHandle (int pMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalLock (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static void GlobalMemoryStatus (MEMORYSTATUS lpBuffer);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalReAlloc (int hMem, int dwBytes, int uFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalSize (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GlobalUnWire (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static void GlobalUnfix (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean GlobalUnlock (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int GlobalWire (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int HeapAlloc (int hHeap, int dwFlags, int dwBytes);

        /** @dll.import("KERNEL32",auto) */
        public native static int HeapCompact (int hHeap, int dwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static int HeapCreate (int flOptions, int dwInitialSize, int dwMaximumSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean HeapDestroy (int hHeap);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean HeapFree (int hHeap, int dwFlags, int lpMem);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean HeapLock (int hHeap);

        /** @dll.import("KERNEL32",auto) */
        public native static int HeapReAlloc (int hHeap, int dwFlags, int lpMem, int dwBytes);

        /** @dll.import("KERNEL32",auto) */
        public native static int HeapSize (int hHeap, int dwFlags, int lpMem);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean HeapUnlock (int hHeap);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean HeapValidate (int hHeap, int dwFlags, int lpMem);


        /** @dll.import("KERNEL32",auto) */
        public native static boolean InitAtomTable (int nSize);


        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsBadCodePtr (int lpfn);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsBadHugeReadPtr (int lp, int ucb);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsBadHugeWritePtr (int lp, int ucb);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsBadReadPtr (int lp, int ucb);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean IsBadStringPtr (int lpsz, int ucchMax);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsBadWritePtr (int lp, int ucb);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsDBCSLeadByte (byte TestChar);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsDBCSLeadByteEx (int CodePage, byte TestChar);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsProcessorFeaturePresent (int ProcessorFeature);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsValidCodePage (int CodePage);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean IsValidLocale (int Locale, int dwFlags);

        /** @dll.import("KERNEL32", auto) */
        public native static int LCMapString (int Locale, int dwMapFlags, String lpSrcStr, int cchSrc, StringBuffer lpDestStr, int cchDest);



        /** @dll.import("KERNEL32", auto,setLastError) */
        public native static int LoadLibraryEx (String lpLibFileName, int hFile, int dwFlags);

        /** @dll.import("KERNEL32", auto,setLastError) */
        public native static int LoadLibrary (String lpLibFileName);


        /** @dll.import("KERNEL32",auto) */
        public native static int LoadResource (int hModule, int hResInfo);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalAlloc (int uFlags, int uBytes);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalCompact (int uMinFree);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean LocalFileTimeToFileTime (FILETIME lpLocalFileTime, FILETIME lpFileTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalFlags (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalFree (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalHandle (int pMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalLock (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalReAlloc (int hMem, int uBytes, int uFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalShrink (int hMem, int cbNewSize);

        /** @dll.import("KERNEL32",auto) */
        public native static int LocalSize (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean LocalUnlock (int hMem);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean LockFile (int hFile, int dwFileOffsetLow, int dwFileOffsetHigh, int nNumberOfBytesToLockLow, int nNumberOfBytesToLockHigh);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean LockFileEx (int hFile, int dwFlags, int dwReserved, int nNumberOfBytesToLockLow, int nNumberOfBytesToLockHigh, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static int LockResource (int hResData);

        /** @dll.import("KERNEL32",auto) */
        public native static int MapViewOfFile (int hFileMappingObject, int dwDesiredAccess, int dwFileOffsetHigh, int dwFileOffsetLow, int dwNumberOfBytesToMap);

        /** @dll.import("KERNEL32",auto) */
        public native static int MapViewOfFileEx (int hFileMappingObject, int dwDesiredAccess, int dwFileOffsetHigh, int dwFileOffsetLow, int dwNumberOfBytesToMap, int lpBaseAddress);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean MoveFileEx (String lpExistingFileName, String lpNewFileName, int dwFlags);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean MoveFile (String lpExistingFileName, String lpNewFileName);

        /** @dll.import("KERNEL32",auto) */
        public native static int MulDiv (int nNumber, int nNumerator, int nDenominator);

        /////** @dll.import("KERNEL32", auto) */
        ////public native static int MultiByteToWideChar (int CodePage, int dwFlags, String lpMultiByteStr, int cchMultiByte, StringBuffer lpWideCharStr, int cchWideChar);

        /** @dll.import("KERNEL32", auto) */
        public native static int OpenEvent (int dwDesiredAccess, boolean bInheritHandle, String lpName);

        /** @dll.import("KERNEL32", ansi) */
        public native static int OpenFile (String lpFileName, OFSTRUCT lpReOpenBuff, int uStyle);

        /** @dll.import("KERNEL32", auto) */
        public native static int OpenFileMapping (int dwDesiredAccess, boolean bInheritHandle, String lpName);

        /** @dll.import("KERNEL32", auto) */
        public native static int OpenMutex (int dwDesiredAccess, boolean bInheritHandle, String lpName);

        /** @dll.import("KERNEL32",auto) */
        public native static int OpenProcess (int dwDesiredAccess, boolean bInheritHandle, int dwProcessId);

        /** @dll.import("KERNEL32", auto) */
        public native static int OpenSemaphore (int dwDesiredAccess, boolean bInheritHandle, String lpName);

        /** @dll.import("KERNEL32", auto) */
        public native static int OpenWaitableTimer (int dwDesiredAccess, boolean bInheritHandle, String lpTimerName);

        /** @dll.import("KERNEL32", auto) */
        public native static void OutputDebugString (String lpOutputString);


        /** @dll.import("KERNEL32",auto) */
        public native static boolean PeekNamedPipe (int hNamedPipe, Object lpBuffer, int nBufferSize, int[] lpBytesRead, int[] lpTotalBytesAvail, int[] lpBytesLeftThisMessage);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean PostQueuedCompletionStatus (int CompletionPort, int dwNumberOfBytesTransferred, int dwCompletionKey, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static int PrepareTape (int hDevice, int dwOperation, boolean bImmediate);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean PulseEvent (int hEvent);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean PurgeComm (int hFile, int dwFlags);

        /** @dll.import("KERNEL32", auto) */
        public native static int QueryDosDevice (String lpDeviceName, Object lpTargetPath, int ucchMax);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean QueryPerformanceCounter(long[] lpPerformanceCount);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean QueryPerformanceFrequency(long[] lpPerformanceFreq);

        /** @dll.import("KERNEL32",auto) */
        public native static int QueueUserAPC (PAPCFUNC pfnAPC, int hThread, int dwData);



        /** @dll.import("KERNEL32",auto, entrypoint="ReadConsoleOutputAttribute") */
        private native static boolean ReadConsoleOutputAttribute_I (int hConsoleOutput, short[] lpAttribute, int nLength, int dwReadCoord, int[] lpNumberOfAttrsRead);
		  
        public static boolean ReadConsoleOutputAttribute (int hConsoleOutput, short[] lpAttribute, int nLength, COORD dwReadCoord, int[] lpNumberOfAttrsRead)
		{
		   return ReadConsoleOutputAttribute_I (hConsoleOutput, lpAttribute, nLength, expandCoord(dwReadCoord), lpNumberOfAttrsRead);
		}
		  
        /** @dll.import("KERNEL32", auto, entrypoint="ReadConsoleOutputCharacter") */
        private native static boolean ReadConsoleOutputCharacter_I (int hConsoleOutput, StringBuffer lpCharacter, int nLength, int dwReadCoord, int[] lpNumberOfCharsRead);
		  
        public static boolean ReadConsoleOutputCharacter (int hConsoleOutput, StringBuffer lpCharacter, int nLength, COORD dwReadCoord, int[] lpNumberOfCharsRead)
		{
		   return ReadConsoleOutputCharacter_I (hConsoleOutput, lpCharacter, nLength, expandCoord(dwReadCoord), lpNumberOfCharsRead);
		}

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ReadConsole (int hConsoleInput, Object lpBuffer, int nNumberOfCharsToRead, int[] lpNumberOfCharsRead, int lpReserved);

        /** @dll.import("KERNEL32", unicode) */
        public native static boolean ReadDirectoryChangesW (int hDirectory, Object lpBuffer, int nBufferLength, boolean bWatchSubtree, int dwNotifyFilter, int[] lpBytesReturned, OVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ReadFile (int hFile, Object lpBuffer, int nNumberOfBytesToRead, int[] lpNumberOfBytesRead, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ReadFileEx (int hFile, Object lpBuffer, int nNumberOfBytesToRead, OVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ReadProcessMemory (int hProcess, int lpBaseAddress, Object lpBuffer, int nSize, int[] lpNumberOfBytesRead);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ReleaseMutex (int hMutex);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ReleaseSemaphore (int hSemaphore, int lReleaseCount, int[] lpPreviousCount);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean RemoveDirectory (String lpPathName);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean ResetEvent (int hEvent);

        /** @dll.import("KERNEL32",auto) */
        public native static int ResumeThread (int hThread);


        /** @dll.import("KERNEL32", auto) */
        public native static int SearchPath (String lpPath, String lpFileName, String lpExtension, int nBufferLength, StringBuffer lpBuffer, int lpFilePart);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetCommBreak (int hFile);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetCommMask (int hFile, int dwEvtMask);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetCommState (int hFile, DCB lpDCB);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetCommTimeouts (int hFile, COMMTIMEOUTS lpCommTimeouts);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetComputerName (String lpComputerName);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleActiveScreenBuffer (int hConsoleOutput);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleCP (int wCodePageID);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleCtrlHandler (PHANDLER_ROUTINE HandlerRoutine, boolean Add);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleCursorInfo (int hConsoleOutput, CONSOLE_CURSOR_INFO lpConsoleCursorInfo);

        /** @dll.import("KERNEL32",auto, entrypoint="SetConsoleCursorPosition") */
        private native static boolean SetConsoleCursorPosition_I (int hConsoleOutput, int dwCursorPosition);
		  
        public static boolean SetConsoleCursorPosition (int hConsoleOutput, COORD dwCursorPosition)
		{
		   return SetConsoleCursorPosition_I (hConsoleOutput, expandCoord(dwCursorPosition));
		}
		  
        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleMode (int hConsoleHandle, int dwMode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleOutputCP (int wCodePageID);

        /** @dll.import("KERNEL32",auto, entrypoint="SetConsoleScreenBufferSize") */
        private native static boolean SetConsoleScreenBufferSize_I (int hConsoleOutput, int dwSize);
		  
        public static boolean SetConsoleScreenBufferSize (int hConsoleOutput, COORD dwSize)
		{
		   return SetConsoleScreenBufferSize_I (hConsoleOutput, expandCoord(dwSize));
		}

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleTextAttribute (int hConsoleOutput, short wAttributes);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetConsoleTitle (String lpConsoleTitle);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetConsoleWindowInfo (int hConsoleOutput, boolean bAbsolute, SMALL_RECT lpConsoleWindow);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetCurrentDirectory (String lpPathName);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetEndOfFile (int hFile);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetEnvironmentVariable (String lpName, String lpValue);

        /** @dll.import("KERNEL32",auto) */
        public native static int SetErrorMode (int uMode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetEvent (int hEvent);

        /** @dll.import("KERNEL32",auto) */
        public native static void SetFileApisToANSI ();

        /** @dll.import("KERNEL32",auto) */
        public native static void SetFileApisToOEM ();

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetFileAttributes (String lpFileName, int dwFileAttributes);

        /** @dll.import("KERNEL32",auto) */
        public native static int SetFilePointer (int hFile, int lDistanceToMove, int[] lpDistanceToMoveHigh, int dwMoveMethod);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetFileTime (int hFile, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime);

        /** @dll.import("KERNEL32",auto) */
        public native static int SetHandleCount (int uNumber);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetHandleInformation (int hObject, int dwMask, int dwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static void SetLastError (int dwErrCode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetLocalTime (SYSTEMTIME lpSystemTime);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetLocaleInfo (int Locale, int LCType, String lpLCData);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetMailslotInfo (int hMailslot, int lReadTimeout);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetNamedPipeHandleState (int hNamedPipe, int[] lpMode, int[] lpMaxCollectionCount, int[] lpCollectDataTimeout);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetPriorityClass (int hProcess, int dwPriorityClass);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetProcessAffinityMask (int hProcess, int dwProcessAffinityMask);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetProcessPriorityBoost (int hProcess, boolean bDisablePriorityBoost);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetProcessShutdownParameters (int dwLevel, int dwFlags);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetProcessWorkingSetSize (int hProcess, int dwMinimumWorkingSetSize, int dwMaximumWorkingSetSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetStdHandle (int nStdHandle, int hHandle);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetSystemPowerState (boolean fSuspend, boolean fForce);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetSystemTime (SYSTEMTIME lpSystemTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetSystemTimeAdjustment (int dwTimeAdjustment, boolean bTimeAdjustmentDisabled);

        /** @dll.import("KERNEL32",auto) */
        public native static int SetTapeParameters (int hDevice, int dwOperation, Object lpTapeInformation);

        /** @dll.import("KERNEL32",auto) */
        public native static int SetTapePosition (int hDevice, int dwPositionMethod, int dwPartition, int dwOffsetLow, int dwOffsetHigh, boolean bImmediate);

        /** @dll.import("KERNEL32",auto) */
        public native static int SetThreadAffinityMask (int hThread, int dwThreadAffinityMask);



        /** @dll.import("KERNEL32",auto) */
        public native static int SetThreadIdealProcessor (int hThread, int dwIdealProcessor);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetThreadLocale (int Locale);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetThreadPriority (int hThread, int nPriority);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetThreadPriorityBoost (int hThread, boolean bDisablePriorityBoost);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetTimeZoneInformation (TIME_ZONE_INFORMATION lpTimeZoneInformation);


        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetVolumeLabel (String lpRootPathName, String lpVolumeName);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean SetWaitableTimer(int hTimer, long[] pDueTime, int lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, int pArgToCompletionRoutine, boolean fResume);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SetupComm (int hFile, int dwInQueue, int dwOutQueue);

        /** @dll.import("KERNEL32",auto) */
        public native static int SignalObjectAndWait (int hObjectToSignal, int hObjectToWaitOn, int dwMilliseconds, boolean bAlertable);

        /** @dll.import("KERNEL32",auto) */
        public native static int SizeofResource (int hModule, int hResInfo);

        /** @dll.import("KERNEL32",auto) */
        public native static void Sleep (int dwMilliseconds);

        /** @dll.import("KERNEL32",auto) */
        public native static int SleepEx (int dwMilliseconds, boolean bAlertable);

        /** @dll.import("KERNEL32",auto) */
        public native static int SuspendThread (int hThread);

        /** @dll.import("KERNEL32",auto) */
        public native static void SwitchToFiber (int lpFiber);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SwitchToThread ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SystemTimeToFileTime (SYSTEMTIME lpSystemTime, FILETIME lpFileTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean SystemTimeToTzSpecificLocalTime (TIME_ZONE_INFORMATION lpTimeZoneInformation, SYSTEMTIME lpUniversalTime, SYSTEMTIME lpLocalTime);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean TerminateProcess (int hProcess, int uExitCode);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean TerminateThread (int hThread, int dwExitCode);

        /** @dll.import("KERNEL32",auto) */
        public native static int TlsAlloc ();

        /** @dll.import("KERNEL32",auto) */
        public native static boolean TlsFree (int dwTlsIndex);

        /** @dll.import("KERNEL32",auto) */
        public native static int TlsGetValue (int dwTlsIndex);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean TlsSetValue (int dwTlsIndex, int lpTlsValue);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean TransactNamedPipe (int hNamedPipe, Object lpInBuffer, int nInBufferSize, Object lpOutBuffer, int nOutBufferSize, int[] lpBytesRead, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32", ansi) */
        public native static boolean TransmitCommChar (int hFile, char cChar);



        /** @dll.import("KERNEL32",auto) */
        public native static boolean UnlockFile (int hFile, int dwFileOffsetLow, int dwFileOffsetHigh, int nNumberOfBytesToUnlockLow, int nNumberOfBytesToUnlockHigh);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean UnlockFileEx (int hFile, int dwReserved, int nNumberOfBytesToUnlockLow, int nNumberOfBytesToUnlockHigh, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean UnmapViewOfFile (int lpBaseAddress);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean UpdateResource (int hUpdate, String lpType, String lpName, short wLanguage, int lpData, int cbData);

        /** @dll.import("KERNEL32", auto) */
        public native static int VerLanguageName (int wLang, StringBuffer szLang, int nSize);

        /** @dll.import("KERNEL32",auto) */
        public native static int VirtualAlloc (int lpAddress, int dwSize, int flAllocationType, int flProtect);

        /** @dll.import("KERNEL32",auto) */
        public native static int VirtualAllocEx (int hProcess, int lpAddress, int dwSize, int flAllocationType, int flProtect);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean VirtualFree (int lpAddress, int dwSize, int dwFreeType);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean VirtualFreeEx (int hProcess, int lpAddress, int dwSize, int dwFreeType);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean VirtualLock (int lpAddress, int dwSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean VirtualProtect (int lpAddress, int dwSize, int flNewProtect, int[] lpflOldProtect);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean VirtualProtectEx (int hProcess, int lpAddress, int dwSize, int flNewProtect, int[] lpflOldProtect);

        /** @dll.import("KERNEL32",auto) */
        public native static int VirtualQuery (int lpAddress, MEMORY_BASIC_INFORMATION lpBuffer, int dwLength);

        /** @dll.import("KERNEL32",auto) */
        public native static int VirtualQueryEx (int hProcess, int lpAddress, MEMORY_BASIC_INFORMATION lpBuffer, int dwLength);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean VirtualUnlock (int lpAddress, int dwSize);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean WaitCommEvent (int hFile, int[] lpEvtMask, OVERLAPPED lpOverlapped);



        /** @dll.import("KERNEL32",auto) */
        public native static int WaitForMultipleObjects (int nCount, int[] lpHandles, boolean bWaitAll, int dwMilliseconds);

        /** @dll.import("KERNEL32",auto) */
        public native static int WaitForMultipleObjectsEx (int nCount, int[] lpHandles, boolean bWaitAll, int dwMilliseconds, boolean bAlertable);

        /** @dll.import("KERNEL32",auto) */
        public native static int WaitForSingleObject (int hHandle, int dwMilliseconds);

        /** @dll.import("KERNEL32",auto) */
        public native static int WaitForSingleObjectEx (int hHandle, int dwMilliseconds, boolean bAlertable);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean WaitNamedPipe (String lpNamedPipeName, int nTimeOut);

////        /** @dll.import("KERNEL32", ansi) */
////        public native static int WideCharToMultiByte (int CodePage, int dwFlags, String lpWideCharStr, int cchWideChar, StringBuffer lpMultiByteStr, int cchMultiByte, String lpDefaultChar, boolean[] lpUsedDefaultChar);

		  /** @dll.import("KERNEL32", ansi) */
		  public native static int WinExec (String lpCmdLine, int uCmdShow);


		/** @dll.import("KERNEL32",auto, entrypoint="WriteConsoleOutputAttribute") */
		private native static boolean WriteConsoleOutputAttribute_I (int hConsoleOutput, short[] lpAttribute, int nLength, int dwWriteCoord, int[] lpNumberOfAttrsWritten);

		public static boolean WriteConsoleOutputAttribute (int hConsoleOutput, short[] lpAttribute, int nLength, COORD dwWriteCoord, int[] lpNumberOfAttrsWritten)
		{
		   return WriteConsoleOutputAttribute_I (hConsoleOutput, lpAttribute, nLength, expandCoord(dwWriteCoord), lpNumberOfAttrsWritten);
		}

        /** @dll.import("KERNEL32", auto, entrypoint="WriteConsoleOutputCharacter") */
        private native static boolean WriteConsoleOutputCharacter_I (int hConsoleOutput, String lpCharacter, int nLength, int dwWriteCoord, int[] lpNumberOfCharsWritten);
		  
        public static boolean WriteConsoleOutputCharacter (int hConsoleOutput, String lpCharacter, int nLength, COORD dwWriteCoord, int[] lpNumberOfCharsWritten)
		{
		   return WriteConsoleOutputCharacter_I (hConsoleOutput, lpCharacter, nLength, expandCoord(dwWriteCoord), lpNumberOfCharsWritten);
		}
		  
        /** @dll.import("KERNEL32",auto) */
        public native static boolean WriteConsole (int hConsoleOutput, char[] lpBuffer, int nNumberOfCharsToWrite, int[] lpNumberOfCharsWritten, int lpReserved);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean WriteFile (int hFile, Object lpBuffer, int nNumberOfBytesToWrite, int[] lpNumberOfBytesWritten, OVERLAPPED lpOverlapped);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean WriteFileEx (int hFile, Object lpBuffer, int nNumberOfBytesToWrite, OVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean WritePrivateProfileSection (String lpAppName, String lpString, String lpFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean WritePrivateProfileString (String lpAppName, String lpKeyName, String lpString, String lpFileName);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean WritePrivateProfileStruct (String lpszSection, String lpszKey, Object lpStruct, int uSizeStruct, String szFile);

        /** @dll.import("KERNEL32",auto) */
        public native static boolean WriteProcessMemory (int hProcess, int lpBaseAddress, Object lpBuffer, int nSize, int[] lpNumberOfBytesWritten);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean WriteProfileSection (String lpAppName, String lpString);

        /** @dll.import("KERNEL32", auto) */
        public native static boolean WriteProfileString (String lpAppName, String lpKeyName, String lpString);

        /** @dll.import("KERNEL32",auto) */
        public native static int WriteTapemark (int hDevice, int dwTapemarkType, int dwTapemarkCount, boolean bImmediate);

        /** @dll.import("KERNEL32",auto) */
        public native static int _hread (int hFile, Object lpBuffer, int lBytes);

        /** @dll.import("KERNEL32", ansi) */
        public native static int _hwrite (int hFile, Object lpBuffer, int lBytes);

        /** @dll.import("KERNEL32",auto) */
        public native static int _lclose (int hFile);

        /** @dll.import("KERNEL32", ansi) */
        public native static int _lcreat (String lpPathName, int iAttribute);

        /** @dll.import("KERNEL32",auto) */
        public native static int _llseek (int hFile, int lOffset, int iOrigin);

        /** @dll.import("KERNEL32", ansi) */
        public native static int _lopen (String lpPathName, int iReadWrite);

        /** @dll.import("KERNEL32",auto) */
        public native static int _lread (int hFile, int lpBuffer, int uBytes);

        /** @dll.import("KERNEL32",auto) */
        public native static int _lread (int hFile, Object lpBuffer, int uBytes);

        /** @dll.import("KERNEL32", auto) */
        public native static int _lwrite (int hFile, int lpBuffer, int uBytes);

        /** @dll.import("KERNEL32", auto) */
        public native static int _lwrite (int hFile, Object lpBuffer, int uBytes);

        /** @dll.import("KERNEL32", auto) */
        public native static int lstrcat (StringBuffer lpString1, String lpString2);

        /** @dll.import("KERNEL32", auto) */
        public native static int lstrcmp (String lpString1, String lpString2);

        /** @dll.import("KERNEL32", auto) */
        public native static int lstrcmpi (String lpString1, String lpString2);

        /** @dll.import("KERNEL32", auto) */
        public native static int lstrcpy (StringBuffer lpString1, String lpString2);

        /** @dll.import("KERNEL32", auto) */
        public native static int lstrcpyn (StringBuffer lpString1, String lpString2, int iMaxLength);

        /** @dll.import("KERNEL32", auto) */
        public native static int lstrlen (String lpString);


}
