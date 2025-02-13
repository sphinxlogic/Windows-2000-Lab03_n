//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       CMEMB.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


typedef struct tagUser {
	INmMember * pMember;
	LPTSTR pszName;
	ULONG  uVersion;
	BOOL   fLocal;
	BOOL   fMcu;
	BOOL   fTop;
} USER;
typedef USER * PUSER;

extern COBLIST * g_pListUser;
extern INmMember * g_pMemberLocal;

// from cMemb.cpp
VOID AddMember(INmMember * pMember);
VOID RemoveMember(INmMember * pMember);
VOID FreeAllUsers(void);
VOID FreeUser(PUSER pUser);
PUSER PUserFromINmMember(INmMember * pMember);
INmMember * GetSelectedMember(void);


