// Copyright (c) 1997  Microsoft Corporation.  All rights reserved.
//=====================================================================
// Sample Java/COM Marshaling Hook Class.
//
// Java Type:  double
// Com  Type:  struct {
//                 WORD     fract;
//                 short    value;
//             } FIXED;
//=====================================================================



#pragma hdrstop

#include <windows.h>
#include "native.h" // Raw Native Interface declarations.


typedef FIXED *PFIXED, **PPFIXED;



#ifdef __cplusplus
#define EXTERNC     extern "C"
#else
#define EXTERNC
#endif


// Macro for declaring RNI Java methods's (and encapsulating the java class package.)
#define JAVAMETHOD(typ, name) \
    __declspec(dllexport) \
    EXTERNC \
    typ __cdecl FixedPtMarshaler_##name


#define LOGCALL(hookname) OutputDebugString("FixedPtMarshaler." hookname "() called.\n")

// Export that tells what RNI version we were built under.
DWORD __cdecl RNIGetCompatibleVersion()
{
  return RNIVER;
}


//==========================================================================
// toJava
//==========================================================================
JAVAMETHOD(double, toJava) (OBJECT*x, PPFIXED ppFIXED, int flags)
{
    const FIXED *pFIXED = *ppFIXED;

    LOGCALL("toJava");

    // Convert FIXED to double.
    return ((double)(pFIXED->value)) + ((double)(pFIXED->fract)) / 65536.0;
}


//==========================================================================
// copyToExternal
//==========================================================================
JAVAMETHOD(void, copyToExternal) (OBJECT*x, double javaval, PPFIXED ppFIXED, int flags)
{
    FIXED *pFIXED = *ppFIXED;

    LOGCALL("copyToExternal");

    // Convert double to FIXED.
    if (javaval > 32767.0 || javaval < -32768.0) {
        SignalErrorPrintf("java/lang/IllegalArgumentException", "Overflow on double->FIXED conversion.");
    } else {
        pFIXED->value = (short)javaval;
        pFIXED->fract = (short) ((javaval - (short)javaval) * 65536.0);
    }
}




//==========================================================================
// TODO: Remove this copy of DllMain if you are embedding this file in your
//  own DLL.
// DLL Loader entry point.
//==========================================================================
BOOL WINAPI DllMain(HINSTANCE hmod, DWORD dwReason,
                                PVOID pvReserved)
{
   return TRUE;
}




