//====================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//=====================================================================
//
//  MODULE:   sampincl.h
//
//  PURPOSE:  The precompiled headers file
//

#ifndef _SICILY_SAMPLE_C_H_
#define _SICILY_SAMPLE_C_H_

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h> 
#include <issperr.h>
#ifndef WIN16_BUILD
#include <sspi.h>
#else // WIN16_BUILD
#include <stdlib.h>
#include <siclibc.h>
#include <sspi16.h>

#define SEC_WINNT_AUTH_IDENTITY_ANSI 0x1

#define SEC_WINNT_AUTH_IDENTITY SEC_WINNT_AUTH_IDENTITY_A
#define PSEC_WINNT_AUTH_IDENTITY PSEC_WINNT_AUTH_IDENTITY_A
#define _SEC_WINNT_AUTH_IDENTITY _SEC_WINNT_AUTH_IDENTITY_A
                                  
#endif WIN16_BUILD
#include <commdef.h>

#include "client.h"

#endif
