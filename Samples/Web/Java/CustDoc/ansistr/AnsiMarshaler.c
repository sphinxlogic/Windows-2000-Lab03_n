// Copyright (c) 1997 Microsoft Corporation.  All rights reserved.

#pragma hdrstop

#define INITGUID 1
#include <windows.h>
#include "native.h" // Raw Native Interface declarations.


typedef CHAR *PSTR, **PPSTR;



#ifdef __cplusplus
#define EXTERNC     extern "C"
#else
#define EXTERNC
#endif


// Macro for declaring RNI Java methods's (and encapsulating the java class package.)
// TODO: Replace "AnsiMarshaler" with the name of your hook class. 
#define JAVAMETHOD(typ, name) \
    __declspec(dllexport) \
    EXTERNC \
    typ __cdecl AnsiMarshaler_##name


#define LOGCALL(hookname) OutputDebugString("AnsiMarshaler." hookname "() called.\n")

// Export that tells what RNI version we were built under.
DWORD __cdecl RNIGetCompatibleVersion()
{
  return RNIVER;
}


//==========================================================================
// toJava
//==========================================================================
JAVAMETHOD(HString*, toJava) (OBJECT*x, PPSTR pPSTR, int flags)
{
    PSTR pstr = *pPSTR;

    LOGCALL("toJava");

    if (pstr == NULL) {
        return NULL;
    } else {
        return makeJavaString(pstr, lstrlen(pstr));
    }
}




//==========================================================================
// toExternal
//==========================================================================
JAVAMETHOD(void, toExternal) (OBJECT*x, HString* javaval, int flags, PPSTR pPSTR)
{
    PSTR pstr = NULL;

    LOGCALL("toExternal");

    if (javaval != NULL) {

        DWORD len = javaStringLength(javaval);
        pstr = (LPSTR)CoTaskMemAlloc(len+1);
        if (!pstr) {
            SignalErrorPrintf("java/lang/OutOfMemoryError", "Could not allocate from task heap!");
        } else {
            char msg[100];
            DWORD i;
            unicode *pwc = javaStringStart(javaval);

            wsprintf(msg, "Hook created new string at %lxh\n", pstr);
            OutputDebugString(msg);

            for (i = 0; i < len; i++) {
                pstr[i] = (CHAR)(pwc[i]);
            }
            pstr[i] = '\0';
        }

    }
    *pPSTR = pstr;
}


//==========================================================================
// releaseExternal
//==========================================================================
JAVAMETHOD(void, releaseExternal) (OBJECT*x, PPSTR pPSTR, int flags)
{
    PSTR pstr = *pPSTR;

    LOGCALL("releaseExternal");

    if (pstr) {
        char msg[100];
        wsprintf(msg, "Hook freeing string at %lxh\n", pstr);
        OutputDebugString(msg);

        CoTaskMemFree(pstr);
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
































