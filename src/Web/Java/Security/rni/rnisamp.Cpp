// rnisamp.cpp
//
// Created 09/08/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

#include <windows.h>
#include <stdarg.h>
#include <native.h>

#include "rnisamp.h"

typedef struct Hjava_lang_SecurityManager HSecurity;


__declspec(dllexport)
DWORD __cdecl RNIGetCompatibleVersion()
{
    return RNIVER;
}


__declspec(dllexport)
struct HArrayOfByte * __cdecl rnisamp_MyRNIObject_RNICheckedLoad (
    struct Hrnisamp_MyRNIObject *_jthis,
    struct Hjava_lang_String *_jfilename
    )
{
    GCFrame gcf;
    struct {
        Hrnisamp_MyRNIObject *jthis;
        HString *jfilename;
    } gc;
    GCFramePush(&gcf, &gc, sizeof(gc));
    gc.jthis = _jthis;
    gc.jfilename = _jfilename;

    HSecurity *jsecurity = java_lang_System_getSecurityManager();
    if (jsecurity != NULL)
    {
        jsecurity->checkRead(gc.jfilename);
        if (exceptionOccurred(EE()))
        {
            GCFramePop(&gcf);
            return NULL;
        }
    }

    GCFramePop(&gcf);
    return rnisamp_MyRNIObject_JavaCheckedLoad0(gc.jthis, gc.jfilename);
}

__declspec(dllexport)
struct HArrayOfByte * __cdecl rnisamp_MyRNIObject_JavaCheckedLoad0 (
    struct Hrnisamp_MyRNIObject *_jthis,
    struct Hjava_lang_String *_jfilename
    )
{
    CHAR filename[MAX_PATH];

    if (_jfilename == NULL)
    {
        SignalError(EE(), JAVAPKG "NullPointerException", NULL);
        return NULL;
    }

    javaString2CString(_jfilename, filename, sizeof(filename));
    HArrayOfByte *jdata = NULL;
    BOOL outofmemory = FALSE;

    GCEnable();
    HANDLE file = CreateFile(
            filename,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
            );
    GCDisable();
    if (file != INVALID_HANDLE_VALUE)
    {
        DWORD size = GetFileSize(file, NULL);
        if (size != 0xffffffff)
        {
            jdata = (HArrayOfByte*)ArrayAlloc(T_BYTE, size);
            if (jdata != NULL)
            {
                HObject **jdatapin = GCNewPinnedHandle((HObject*)jdata);
                if (jdatapin != NULL)
                {
                    DWORD read;
                    if (!(ReadFile(
                            file,
                            &jdata->body[0],
                            jdata->length,
                            &read,
                            NULL
                            )
                          && read == size
                          ))
                    {
                        jdata = NULL;
                    }

                    GCFreePinnedHandle(jdatapin);
                }
                else
                {
                    outofmemory = TRUE;
                    jdata = NULL;
                }
            }
            else
            {
                outofmemory = TRUE;
            }
        }

        CloseHandle(file);
    }

    if (jdata != NULL)
        return jdata;

    if (outofmemory)
        SignalError(EE(), JAVAPKG "OutOfMemoryError", NULL);
    else
        SignalError(EE(), "java/io/IOException", filename);
    return NULL;
}


