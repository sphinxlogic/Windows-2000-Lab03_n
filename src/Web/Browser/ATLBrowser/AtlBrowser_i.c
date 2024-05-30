//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 26 11:28:28 1998
 */
/* Compiler settings for AtlBrowser.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IAtlBrCon = {0x0818D42F,0x6247,0x11D1,{0xAB,0xEE,0x00,0xD0,0x49,0xC1,0x00,0x00}};


const IID LIBID_ATLBROWSERLib = {0x0818D422,0x6247,0x11D1,{0xAB,0xEE,0x00,0xD0,0x49,0xC1,0x00,0x00}};


const CLSID CLSID_AtlBrCon = {0x0818D430,0x6247,0x11D1,{0xAB,0xEE,0x00,0xD0,0x49,0xC1,0x00,0x00}};


#ifdef __cplusplus
}
#endif

