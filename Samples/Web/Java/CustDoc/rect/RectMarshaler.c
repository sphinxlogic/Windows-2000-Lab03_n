// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.

#pragma hdrstop

#define INITGUID 1
#include <windows.h>
#include "native.h" // Raw Native Interface declarations.


typedef RECT *PRECT, **PPRECT;



#ifdef __cplusplus
#define EXTERNC     extern "C"
#else
#define EXTERNC
#endif


// Macro for declaring RNI Java methods's (and encapsulating the java class package.)
// TODO: Replace "RectMarshaler" with the name of your hook class. 
#define JAVAMETHOD(typ, name) \
    __declspec(dllexport) \
    EXTERNC \
    typ __cdecl RectMarshaler_##name

#define LOGCALL(hookname) OutputDebugString("RectMarshaler." hookname "() called.\n")

// Export that tells what RNI version we were built under.
DWORD __cdecl RNIGetCompatibleVersion()
{
  return RNIVER;
}

// Cache the various class and fields we will need.
ClassClass*         gRectangleClass;
struct fieldblock*  gRectangleXField;
struct fieldblock*  gRectangleYField;
struct fieldblock*  gRectangleWidthField;
struct fieldblock*  gRectangleHeightField;



//==========================================================================
// toJava
//==========================================================================
JAVAMETHOD(OBJECT*, toJava) (OBJECT*x, PPRECT ppRECT, int flags)
{

    PRECT prect = *ppRECT;

    LOGCALL("toJava");



    return execute_java_constructor(NULL,
                                    NULL,
                                    gRectangleClass,
                                    "(IIII)",
                                    prect->left,
                                    prect->top,
                                    prect->right - prect->left,
                                    prect->bottom - prect->top);
}



void copyToExternalWorker(OBJECT *javaval, PRECT pRECT)
{

    int x, y, width, height;

    x      = Field_GetInt(javaval, gRectangleXField);
    y      = Field_GetInt(javaval, gRectangleYField);
    width  = Field_GetInt(javaval, gRectangleWidthField);
    height = Field_GetInt(javaval, gRectangleHeightField);

    pRECT->left   = x;
    pRECT->top    = y;
    pRECT->right  = x + width;
    pRECT->bottom = y + height;
}


//==========================================================================
// copyToExternal
//==========================================================================
JAVAMETHOD(void, copyToExternal) (OBJECT*x, OBJECT* javaval, PPRECT ppRECT, int flags)
{
    LOGCALL("copyToExternal");

    copyToExternalWorker(javaval, *ppRECT);
}






//==========================================================================
// toExternal
//==========================================================================
JAVAMETHOD(void, toExternal) (OBJECT*x, OBJECT* javaval, int flags, PPRECT ppRECT)
{
    PRECT pRECT = NULL;

    LOGCALL("toExternal");

    pRECT = (RECT*)CoTaskMemAlloc(sizeof(RECT));
    if (!pRECT) {
        SignalErrorPrintf("java/lang/OutOfMemoryError", "Could not allocate from task heap!");
    } else {
        char msg[100];
        wsprintf(msg, "Hook allocated RECT at %lxh\n", pRECT);
        OutputDebugString(msg);
        copyToExternalWorker(javaval, pRECT);
        *ppRECT = pRECT;
    }
}


//==========================================================================
// releaseExternal
//==========================================================================
JAVAMETHOD(void, releaseExternal) (OBJECT*x, PPRECT ppRECT, int flags)
{
    PRECT pRECT = *ppRECT;
    char msg[100];

    LOGCALL("releaseExternal");
    wsprintf(msg, "Hook freeing RECT at %lxh\n", pRECT);
    OutputDebugString(msg);
    if (pRECT) {
        CoTaskMemFree(pRECT);
    }
}


//==========================================================================
// classInit (one time initialization routine)
//==========================================================================
JAVAMETHOD(void, classInit) (OBJECT*x)
{
    gRectangleClass = FindClass(NULL, "java/awt/Rectangle", TRUE);
    if (!gRectangleClass) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Could not preload java.awt.Rectangle class!");
    }

    gRectangleXField = Class_GetField(gRectangleClass, "x");
    if (!gRectangleXField) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Bogus java.awt.Rectangle class!");
    }

    gRectangleYField = Class_GetField(gRectangleClass, "y");
    if (!gRectangleYField) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Bogus java.awt.Rectangle class!");
    }

    gRectangleWidthField = Class_GetField(gRectangleClass, "width");
    if (!gRectangleWidthField) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Bogus java.awt.Rectangle class!");
    }

    gRectangleHeightField = Class_GetField(gRectangleClass, "height");
    if (!gRectangleHeightField) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Bogus java.awt.Rectangle class!");
    }
}





//==========================================================================
// TODO: Remove this copy of DllMain if you are embedding this file in your
//  own DLL.
// DLL Loader entry Rectangle.
//==========================================================================
BOOL WINAPI DllMain(HINSTANCE hmod, DWORD dwReason,
                                PVOID pvReserved)
{
   return TRUE;
}
































