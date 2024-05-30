//
//  invokevm.c
//
//  Copyright (c) 1997, Microsoft Corporation
//
//  Demonstrates the use of the PrepareThreadForJava and UnprepareThreadForJava
//  invocation APIs.
//

#include <windows.h>
#include <stdio.h>
#include <native.h>

void main(int argc, char *argv[])
{
    HRESULT hr;
    ThreadEntryFrame threadEntryFrame;
    ClassClass *pClass;

    hr = CoInitialize(NULL);

    if (hr == S_OK) {

        //  Call this API before calling into the Microsoft Java VM to allow the
        //  VM to allocate any per-thread structures and to do any first-time
        //  initialization.  After return from this call, Java objects may be
        //  accessed or RNI APIs may be called.
        if (PrepareThreadForJava(&threadEntryFrame)) {

            pClass = FindClass(NULL, "TestClass", TRUE);

            if (pClass != NULL) {
                execute_java_static_method(NULL, pClass, "someMethod", "()V");
            } else {
                printf("Failed to find class!\n");
            }

            //  Detaches the "entry frame" from this thread.  After return from
            //  this call, it is no longer safe to directly touch Java objects
            //  or call RNI APIs.
            UnprepareThreadForJava(&threadEntryFrame);

        } else {
            printf("Failed to initialize thread!\n");
        }

        CoUninitialize();
    }
}
