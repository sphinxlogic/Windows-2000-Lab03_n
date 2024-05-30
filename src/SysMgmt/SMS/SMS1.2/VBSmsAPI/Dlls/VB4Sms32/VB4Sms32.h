//****************************************************************************
//
//  Copyright (c) 1995, Microsoft Corporation
//
//  File:  VB4SMS32.H
//
//  Definitions for the 32-bit Visual Basic interface DLL
//  for SMSAPI.DLL (a Win32 dll)
//
//  History:
//
//      Gary F. Fuehrer, SEA     21 Mar 95    Created.
//
//****************************************************************************

// NOTE:  This file is NOT a C or C++ interface file as are most .H files.
//        Instead, this is where all assumptions about SMSAPI.H are kept.
//        If SMSAPI.H changes, this file will need to be updated, and
//        hopefully VB4SMS32.CPP won't compile until it too is updated.


typedef struct _TOKENVB {
    UINT    tokenType;
    BSTR    szName;
    BSTR    szValue;
    DWORD   dwOp;
    BSTR    szArchitecture;
    BSTR    szGroupClass;
    BSTR    szAttributeName;
    BSTR    szTokenString;
    BOOL    bIndent;
} TOKENVB;

typedef struct _FILTER_INFOVB {
    BSTR    szTag;
    DWORD   filterType;
    BSTR    szName;
    BSTR    szValue;
    BSTR    szOperator;
    BSTR    szArchitecture;
    BSTR    szGroupClass;
    BSTR    szAttributeName;
} FILTER_INFOVB;

typedef struct _SCALAR_INFOVB {
    BSTR    szName;                 // Scalar's name.
    SCALARTYPE scType;              // Type: SCALAR_STRING, INT, TIME etc
    DWORD   fAccess;                // Access mode: ACCESS_READ, MODIFY etc
} SCALAR_INFOVB;

typedef struct _OBJDESCRIPTORVB {
    DWORD objType;
    BSTR szName;
    BSTR szFriendlyName;
    BOOL bGotFriendlyName;
    DWORD dwRelopMin;
    DWORD dwRelopMax;
    BOOL bGotRelops;
} OBJDESCRIPTORVB;

//////////////////////////////////////////////////////////////////////////////
