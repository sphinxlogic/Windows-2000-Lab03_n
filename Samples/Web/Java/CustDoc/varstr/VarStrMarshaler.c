//=====================================================================
// Sample Java/COM Marshaling Hook Class.
//
// Java Type:  String
// Com  Type:  VARIANT (BSTR type).
// 
// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.
//=====================================================================




#pragma hdrstop

#include <windows.h>
#include "native.h" // Raw Native Interface declarations.



typedef VARIANT *PVARIANT, **PPVARIANT;



#ifdef __cplusplus
#define EXTERNC     extern "C"
#else
#define EXTERNC
#endif


// Macro for declaring RNI Java methods's (and encapsulating the java class package.)
#define JAVAMETHOD(typ, name) \
    __declspec(dllexport) \
    EXTERNC \
    typ __cdecl VarStrMarshaler_##name

// Export that tells what RNI version we were built under.
DWORD __cdecl RNIGetCompatibleVersion()
{
  return RNIVER;
}


#define LOGCALL(hookname) OutputDebugString("VarStrMarshaler." hookname "() called.\n")


//==========================================================================
// toJava
//==========================================================================
JAVAMETHOD(HString*, toJava) (OBJECT*x, PPVARIANT ppVARIANT, int flags)
{
    VARIANT *pvar = *ppVARIANT;

    LOGCALL("toJava");

    
    if (pvar->vt != VT_BSTR) {
        // Could try to coerce the variant, but this is just an example.
        SignalErrorPrintf("java/lang/IllegalArgumentException",
                          "Variant is of wrong type (must be VT_BSTR.)");
    } else {
        return makeJavaStringW(pvar->bstrVal, SysStringLen(pvar->bstrVal));
    }
}


//==========================================================================
// copyToExternal
//==========================================================================
JAVAMETHOD(void, copyToExternal) (OBJECT*x, HString* javaval, PPVARIANT ppVARIANT, int flags)
{
    PVARIANT pVARIANT = *ppVARIANT;
    BSTR bstr;

    LOGCALL("copyToExternal");

    if (!javaval) {
        SignalErrorPrintf("java/lang/NullPointerException", "Null string not allowed.");
    } else {
        bstr = SysAllocStringLen(javaStringStart(javaval),
                                 (UINT)(javaStringLength(javaval)));
    
    
        if (!bstr) {
            SignalErrorPrintf("java/lang/OutOfMemoryError", "Not enough room in BSTR system heap.");
        } else {
    
            char msg[100];
            wsprintf(msg, "Hook class allocated BSTR at %lxh\n", bstr);
            OutputDebugString(msg);
    
            // We explicitly do NOT call VariantClear before overwriting the variant.
            // That is the job of releaseByValExternal, which will be called when needed.
            pVARIANT->vt      = VT_BSTR;
            pVARIANT->bstrVal = bstr;
        }
    }

}


//==========================================================================
// releaseByValExternal
//==========================================================================
JAVAMETHOD(void, releaseByValExternal) (OBJECT*x, PPVARIANT ppVARIANT, int flags)
{
    PVARIANT pVARIANT = *ppVARIANT;

    LOGCALL("releaseByValExternal");
    if (pVARIANT->vt == VT_BSTR) {
        char msg[100];
        wsprintf(msg, "Hook class freeing BSTR at %lxh\n", pVARIANT->bstrVal);
        OutputDebugString(msg);

        SysFreeString(pVARIANT->bstrVal);
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
































