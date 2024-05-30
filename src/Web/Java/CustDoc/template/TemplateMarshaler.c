// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.

#pragma hdrstop

#include <windows.h>
#include "native.h" // Raw Native Interface declarations.


// TODO: Replace this typedef with your own definition of ETYPE, and/or replace
// all occurrences of ETYPE, PETYPE and PPETYPE with your own type.
typedef struct {
    int dummy;
} ETYPE;

typedef ETYPE *PETYPE, **PPETYPE;


// TODO: Define JTYPE with the appropriate type.
//
//   If your Java type is           replace JTYPE with
//   --------------------           ------------------
//   byte                           char            (see below)
//   char                           unsigned short  (see below)
//   short                          short           (see below)
//   int                            int
//   long                           long
//   boolean                        BOOL
//   float                          float
//   double                         double
//   an object type                 OBJECT* or output of msjavah.exe
//   an array                       HArrayOf<elemtype> (see native.h or
//                                   output of msjavah)
//
//
//  IMPORTANT NOTE:
//     If your java type is byte, char, or short, the return types
//     of toJava and toUninitJava must be declared as "int" and your
//     C function must expand the result to a full 32-bit signed integer
//     (RNI does not expand short integer return values on your behalf)
//
//     If your java tyoe is boolean, your C function must return
//     0 or 1 only (RNI does not normalize boolean return values.)
//

typedef int JTYPE;


#ifdef __cplusplus
#define EXTERNC     extern "C"
#else
#define EXTERNC
#endif


// Macro for declaring RNI Java methods's (and encapsulating the java class package.)
// TODO: Replace "TemplateMarshaler" with the name of your hook class. 
#define JAVAMETHOD(typ, name) \
    __declspec(dllexport) \
    EXTERNC \
    typ __cdecl TemplateMarshaler_##name


// This export tells what RNI version we were built under.  This is a
// NEW REQUIREMENT that was not needed for previous versions of the VM.
// DO NOT REMOVE THIS FUNCTION.  Without it, the VM will be unable to
// access your hook classes.   
DWORD __cdecl RNIGetCompatibleVersion()
{
  return RNIVER;
}


//==========================================================================
// toJava
//==========================================================================
JAVAMETHOD(JTYPE, toJava) (OBJECT*x, PPETYPE ppetype, int flags)
{
    PETYPE petype = *ppetype;
    // TODO: Add code to convert *petype to a value of type JTYPE.
    // If JTYPE is an object or array type, this method should return
    // a newly created instance of JTYPE.
    return 0;
}


//==========================================================================
// copyToExternal
//==========================================================================
JAVAMETHOD(void, copyToExternal) (OBJECT*x, JTYPE javaval, PPETYPE ppetype, int flags)
{
    PETYPE petype = *ppetype;
    // TODO: Add code to convert javaval into an ETYPE and store the resulting
    // ETYPE in the (already allocated) memory pointed to by petype. Do
    // not assume anything about the initial contents of *petype.
}


//==========================================================================
// releaseByValExternal
//==========================================================================
JAVAMETHOD(void, releaseByValExternal) (OBJECT*x, PPETYPE ppetype, int flags)
{
    PETYPE petype = *ppetype;
    // TODO: Add code to destroy any embedded resources owned by *petype.
    // Do not free the memory for *petype itself (if you need to do this,
    // do it in releaseExternal()).
    //
    // If no cleanup code is needed here, this method can be deleted.
    // (do not forget to remove the reference to in the .def file.)
}


//==========================================================================
// copyToJava
//==========================================================================
JAVAMETHOD(void, copyToJava) (OBJECT*x, PPETYPE ppetype, JTYPE javaval, int flags)
{
    PETYPE petype = *ppetype;
    // TODO: Add code to modify "javaval" so it is 'equivalent' to *petype.
    // Do not modify *petype or *ppetype.
    // If JTYPE is not mutable, or you do not need to support "[out]"
    // parameters, this method can be deleted.
    // (do not forget to remove the reference to in the .def file.)
}


//==========================================================================
// toUninitJava
//==========================================================================
JAVAMETHOD(JTYPE, toUninitJava) (OBJECT*x, PPETYPE ppetype, int flags)
{
    PETYPE petype = *ppetype;
    // TODO: Add code to convert *petype to an uninitialized value of
    // type JTYPE.
    // If JTYPE is an object or array type, this method should return
    // a newly created instance of JTYPE.
    // If JTYPE is not mutable, or you do not need to support "[out]"
    // parameters, this method can be deleted.
    // (do not forget to remove the reference to in the .def file.)
    return 0;
}


//==========================================================================
// toExternal
//==========================================================================
JAVAMETHOD(void, toExternal) (OBJECT*x, JTYPE javaval, int flags, PPETYPE ppetype)
{
    PETYPE petype = NULL;
    // TODO: Add code to allocate a new ETYPE, and initialize it to be
    // "equivalent" to javaval. Store a pointer to the new ETYPE in petype.
    // If you do not require ETYPE's that outlive method calls, this method
    // can be deleted.
    // (do not forget to remove the reference to in the .def file.)
    *ppetype = petype;
}


//==========================================================================
// releaseExternal
//==========================================================================
JAVAMETHOD(void, releaseExternal) (OBJECT*x, PPETYPE ppetype, int flags)
{
    PETYPE petype = *ppetype;

    // TODO: Add code to free the memory pointed to by petype. In addition,
    // if you have implemented releaseByValExternal, call it first.
    //
    // If you do not require ETYPE's that outlive method calls, this method
    // can be deleted.
    // (do not forget to remove the reference to in the .def file.)
}


//==========================================================================
// toUninitExternal
//==========================================================================
JAVAMETHOD(void, toUninitExternal) (OBJECT*x, JTYPE javaval, int flags, PPETYPE ppetype)
{
    PETYPE petype = NULL;
    // TODO: Add code to allocate a new ETYPE. It is not necessary to initialize
    // its contents. The value of javaval should be used only to determine
    // the size of the allocation.
    // If you do not require ETYPE's that outlive method calls, or you do not
    // need to support [out] parameters, this method can be deleted.
    // (do not forget to remove the reference to in the .def file.)
    *ppetype = petype;
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
































