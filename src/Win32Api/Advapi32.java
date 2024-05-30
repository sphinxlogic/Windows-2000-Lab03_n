// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Advapi32 {
        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean AccessCheckAndAuditAlarm (String SubsystemName, int HandleId, String ObjectTypeName, String ObjectName, int SecurityDescriptor, int DesiredAccess, GENERIC_MAPPING GenericMapping, boolean ObjectCreation, int[] GrantedAccess, boolean[] AccessStatus, boolean[] pfGenerateOnClose);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean BackupEventLog (int hEventLog, String lpBackupFileName);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean ClearEventLog (int hEventLog, String lpBackupFileName);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CloseEventLog (int hEventLog);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean CreateProcessAsUser (int hToken, String lpApplicationName, String lpCommandLine, SECURITY_ATTRIBUTES lpProcessAttributes, SECURITY_ATTRIBUTES lpThreadAttributes, boolean bInheritHandles, int dwCreationFlags, int lpEnvironment, String lpCurrentDirectory, STARTUPINFO lpStartupInfo, PROCESS_INFORMATION lpProcessInformation);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean CryptAcquireContext (int[] phProv, String pszContainer, String pszProvider, int dwProvType, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptCreateHash (int hProv, int Algid, int hKey, int dwFlags, int[] phHash);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptDecrypt (int hKey, int hHash, boolean Final, int dwFlags, byte[] pbData, int[] pdwDataLen);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptDeriveKey (int hProv, int Algid, int hBaseData, int dwFlags, int[] phKey);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptDestroyHash (int hHash);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptDestroyKey (int hKey);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptEncrypt (int hKey, int hHash, boolean Final, int dwFlags, byte[] pbData, int[] pdwDataLen, int dwBufLen);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptExportKey (int hKey, int hExpKey, int dwBlobType, int dwFlags, byte[] pbData, int[] pdwDataLen);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptGenKey (int hProv, int Algid, int dwFlags, int[] phKey);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptGenRandom (int hProv, int dwLen, byte[] pbBuffer);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptGetHashParam (int hHash, int dwParam, byte[] pbData, int[] pdwDataLen, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptGetKeyParam (int hKey, int dwParam, byte[] pbData, int[] pdwDataLen, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptGetProvParam (int hProv, int dwParam, byte[] pbData, int[] pdwDataLen, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptGetUserKey (int hProv, int dwKeySpec, int[] phUserKey);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptHashData (int hHash, byte[] pbData, int dwDataLen, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptHashSessionKey (int hHash, int hKey, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptImportKey (int hProv, byte[] pbData, int dwDataLen, int hPubKey, int dwFlags, int[] phKey);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptReleaseContext (int hProv, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptSetHashParam (int hHash, int dwParam, byte[] pbData, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptSetKeyParam (int hKey, int dwParam, byte[] pbData, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean CryptSetProvParam (int hProv, int dwParam, byte[] pbData, int dwFlags);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean CryptSetProvider (String pszProvName, int dwProvType);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean CryptSignHash (int hHash, int dwKeySpec, String sDescription, int dwFlags, byte[] pbSignature, int[] pdwSigLen);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean CryptVerifySignature (int hHash, byte[] pbSignature, int dwSigLen, int hPubKey, String sDescription, int dwFlags);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean DeregisterEventSource (int hEventLog);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean DuplicateTokenEx (int hExistingToken, int dwDesiredAccess, SECURITY_ATTRIBUTES lpTokenAttributes, int ImpersonationLevel, int TokenType, int[] phNewToken);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean GetCurrentHwProfile (HW_PROFILE_INFO lpHwProfileInfo);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean GetFileSecurity (String lpFileName, int RequestedInformation, int pSecurityDescriptor, int nLength, int[] lpnLengthNeeded);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean GetNumberOfEventLogRecords (int hEventLog, int[] NumberOfRecords);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean GetOldestEventLogRecord (int hEventLog, int[] OldestRecord);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean GetUserName (StringBuffer lpBuffer, int[] nSize);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean ImpersonateLoggedOnUser (int hToken);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean IsTextUnicode (Object lpBuffer, int cb, int[] lpi);

        /** @dll.import("ADVAPI32", auto) */
        public native static boolean LogonUser (String lpszUsername, String lpszDomain, String lpszPassword, int dwLogonType, int dwLogonProvider, int[] phToken);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean LookupAccountName (String lpSystemName, String lpAccountName, int Sid, int[] cbSid, StringBuffer ReferencedDomainName, int[] cbReferencedDomainName, int[] peUse);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean LookupAccountSid (String lpSystemName, int Sid, StringBuffer Name, int[] cbName, StringBuffer ReferencedDomainName, int[] cbReferencedDomainName, int[] peUse);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean LookupPrivilegeDisplayName (String lpSystemName, String lpName, StringBuffer lpDisplayName, int[] cbDisplayName, int[] lpLanguageId);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean LookupPrivilegeName (String lpSystemName, long[] lpLuid, StringBuffer lpName, int[] cbName);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean LookupPrivilegeValue (String lpSystemName, String lpName, long[] lpLuid);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean NotifyChangeEventLog (int hEventLog, int hEvent);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean ObjectCloseAuditAlarm (String SubsystemName, int HandleId, boolean GenerateOnClose);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean ObjectDeleteAuditAlarm (String SubsystemName, int HandleId, boolean GenerateOnClose);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean ObjectOpenAuditAlarm (String SubsystemName, int HandleId, String ObjectTypeName, String ObjectName, int pSecurityDescriptor, int ClientToken, int DesiredAccess, int GrantedAccess, PRIVILEGE_SET Privileges, boolean ObjectCreation, boolean AccessGranted, int[] GenerateOnClose);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean ObjectPrivilegeAuditAlarm (String SubsystemName, int HandleId, int ClientToken, int DesiredAccess, PRIVILEGE_SET Privileges, boolean AccessGranted);

        /** @dll.import("ADVAPI32", auto) */
        public native static int OpenBackupEventLog (String lpUNCServerName, String lpFileName);

        /** @dll.import("ADVAPI32", auto) */
        public native static int OpenEventLog (String lpUNCServerName, String lpSourceName);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean PrivilegedServiceAuditAlarm (String SubsystemName, String ServiceName, int ClientToken, PRIVILEGE_SET Privileges, boolean AccessGranted);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean ReadEventLog (int hEventLog, int dwReadFlags, int dwRecordOffset, Object lpBuffer, int nNumberOfBytesToRead, int[] pnBytesRead, int[] pnMinNumberOfBytesNeeded);

        /** @dll.import("ADVAPI32", auto) */
        public native static int RegisterEventSource (String lpUNCServerName, String lpSourceName);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean ReportEvent (int hEventLog, short wType, short wCategory, int dwEventID, int lpUserSid, short wNumStrings, int dwDataSize, Object lpStrings, Object lpRawData);

        /** @dll.import("ADVAPI32", auto) */
        /* explicitly excluded */ // public native static boolean SetFileSecurity (String lpFileName, int SecurityInformation, int pSecurityDescriptor);

        /** @dll.import("ADVAPI32",auto) */
        public native static boolean SetThreadToken (int[] Thread, int Token);


}

