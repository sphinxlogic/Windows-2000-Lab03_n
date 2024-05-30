// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.

#pragma hdrstop

#define INITGUID 1
#include <windows.h>
#include "native.h" // Raw Native Interface declarations.



typedef POINT *PPOINT, **PPPOINT;


typedef OBJECT* JPoint;

#ifdef __cplusplus
#define EXTERNC     extern "C"
#else
#define EXTERNC
#endif


// Macro for declaring RNI Java methods's (and encapsulating the java class package.)
#define JAVAMETHOD(typ, name) \
    __declspec(dllexport) \
    EXTERNC \
    typ __cdecl PointMarshaler_##name



#define LOGCALL(hookname) OutputDebugString("PointMarshaler." hookname "() called.\n")


// Export that tells what RNI version we were built under.
DWORD __cdecl RNIGetCompatibleVersion()
{
  return RNIVER;
}


// Cache the various class and fields we will need.
ClassClass*         gPointClass;
struct fieldblock*  gPointXField;
struct fieldblock*  gPointYField;



//==========================================================================
// toJava
//==========================================================================
JAVAMETHOD(JPoint, toJava) (OBJECT*x, PPPOINT ppPOINT, int flags)
{
    PPOINT pPOINT = *ppPOINT;
    JPoint jpoint;

    LOGCALL("toJava");

    jpoint = execute_java_constructor(NULL, NULL, gPointClass, "(II)", pPOINT->x, pPOINT->y);
    return jpoint;
}


//==========================================================================
// copyToExternal
//==========================================================================
JAVAMETHOD(void, copyToExternal) (OBJECT*x, JPoint javaval, PPPOINT ppPOINT, int flags)
{
    PPOINT pPOINT = *ppPOINT;

    LOGCALL("copyToExternal");

    pPOINT->x = Field_GetInt(javaval, gPointXField);
    pPOINT->y = Field_GetInt(javaval, gPointYField);

}




//==========================================================================
// copyToJava
//==========================================================================
JAVAMETHOD(void, copyToJava) (OBJECT*x, PPPOINT ppPOINT, JPoint javaval, int flags)
{
    PPOINT pPOINT = *ppPOINT;    \

    LOGCALL("copyToJava");


    Field_SetInt(javaval, gPointXField, pPOINT->x);
    Field_SetInt(javaval, gPointYField, pPOINT->y);

}


//==========================================================================
// toUninitJava
//==========================================================================
JAVAMETHOD(JPoint, toUninitJava) (OBJECT*x, PPPOINT ppPOINT, int flags)
{
    JPoint jpoint;

    LOGCALL("toUninitJava");

    jpoint = execute_java_constructor(NULL, NULL, gPointClass, "(II)", -1, -1);
    return jpoint;
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



//==========================================================================
// classInit (one time initialization routine)
//==========================================================================
JAVAMETHOD(void, classInit) (OBJECT*x)
{
    gPointClass = FindClass(NULL, "java/awt/Point", TRUE);
    if (!gPointClass) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Could not preload java.awt.Point class!");
    }

    gPointXField = Class_GetField(gPointClass, "x");
    if (!gPointXField) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Bogus java.awt.Point class!");
    }

    gPointYField = Class_GetField(gPointClass, "y");
    if (!gPointYField) {
        SignalErrorPrintf("java/lang/ClassNotFoundException", "Bogus java.awt.Point class!");
    }
}






























