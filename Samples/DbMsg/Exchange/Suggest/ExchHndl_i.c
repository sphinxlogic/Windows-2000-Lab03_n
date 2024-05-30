// --Exchhndl_i.c------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------

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

const IID IID_IExchangeEventHandler = {0x69E54156,0xB371,0x11D0,{0xBC,0xD9,0x00,0xAA,0x00,0xC1,0xAB,0x1C}};


const IID IID_IEventSource = {0x69E54152,0xB371,0x11D0,{0xBC,0xD9,0x00,0xAA,0x00,0xC1,0xAB,0x1C}};


#ifdef __cplusplus
}
#endif

