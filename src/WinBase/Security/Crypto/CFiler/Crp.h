/*-----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

CRP.H
-----------------------------------------------------------------------------*/

#ifndef CRYPTROUTINES_INCLUDED
#define CRYPTROUTINES_INCLUDED

BOOL CALLBACK	EnterPass			   (HWND hDlg, UINT wMsgID, WPARAM wParam, LPARAM lParam);
BOOL            GetPass                (HWND);
LRESULT         WINAPI CryptDlgProc    (HWND, UINT, UINT, LPARAM);
LRESULT         WINAPI EncryptDlgProc  (HWND, UINT, UINT, LPARAM);
LRESULT         WINAPI HashDlgProc     (HWND, UINT, UINT, LPARAM);
BOOL            Logon                  (HWND);
BOOL            Logoff                 (HWND);
BOOL            CFILEREncryptFile      (HWND, LPTSTR);
BOOL            CFILERDecryptFile      (HWND, LPTSTR);
BOOL            GetEncryptPublicKey    (HWND, HCRYPTKEY *);
BOOL            GetSignaturePublicKey  (HWND, HCRYPTKEY *);
HCRYPTKEY       GetfnKey               (HWND);
BOOL            SignFile               (HWND, LPTSTR);
BOOL            VerifyFile             (HWND, LPTSTR);
BOOL            MakeHashDirectory      (VOID);
BOOL            SHAtoRadix64           (LPBYTE, LPTSTR);
VOID            Exit1                  (HWND, LPTSTR, HANDLE, HANDLE);
VOID            Exit2                  (HWND, LPTSTR, HWND, HANDLE, HANDLE);
BOOL            c2r64                  (INT, LPTSTR);
BOOL            EncryptDir             (HWND, LPTSTR, LPCINFO lpCInfo);
BOOL            DecryptDir             (HWND, LPTSTR, LPCINFO lpCInfo);
BOOL            GenRandomName          (LPTSTR);
BOOL            GenRandomName2         (LPTSTR);
BOOL            HasSignature           (LPTSTR, TABLE, BOOL *);
BOOL            GetDecryptedFileName   (HWND, LPTSTR, LPTSTR, HANDLE *);
BOOL            GetDecryptedDirName    (HWND, LPTSTR, LPTSTR, BOOL, HANDLE *);
BOOL            HideSignatures         (VOID);
BOOL            ShowSignatures         (VOID);
BOOL            GetSigFileName         (LPTSTR, LPTSTR);
BOOL            DeleteHashDirectory    (VOID);
BOOL            GetSigDir              (LPTSTR);

#endif
