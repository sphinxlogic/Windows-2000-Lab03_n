/*----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.


CallStack.cpp

This file implements a command line utility that shows how to obtain
stack trace using ImageHlp StackWalk() API.
----------------------------------------------------------------------------*/

#include "callstack.h"
#include "imagehlp.h"
#include <tlhelp32.h>
#include <stdio.h>

/* typedef of all functions used in imagehlp.dll */

typedef DWORD (WINAPI *SymSetOptionsFn) (DWORD dwSymOptions);

typedef BOOL  (WINAPI *SymGetLineFromAddrFn) (
                HANDLE          hProcess,
                DWORD           dwAddr,
                PDWORD          pDwDisplacement,
                PIMAGEHLP_LINE  pImageLine);

typedef BOOL  (WINAPI *SymGetSymFromAddrFn) (
                HANDLE          hProcess,
                DWORD           dwAddr,
                PDWORD          pDwDisplacement,
                PIMAGEHLP_SYMBOL pSymbol);

typedef BOOL (WINAPI *SymInitializeFn) (
                HANDLE hProcess,     
                LPSTR pUserSearchPath,  
                BOOL fInvadeProcess);

typedef DWORD (WINAPI *SymLoadModuleFn) (
                HANDLE hProcess,
                HANDLE hFile,
                LPSTR pImageName,
                LPSTR pModuleName,
                DWORD dwBaseOfDll,
                DWORD dwSizeOfDll);

typedef BOOL (WINAPI *SymGetModuleInfoFn) (
                HANDLE hProcess,              
                DWORD dwAddr,
                PIMAGEHLP_MODULE pModuleInfo);

typedef BOOL (WINAPI *EnumerateLoadedModulesFn) (
                HANDLE hProcess,
                PENUMLOADED_MODULES_CALLBACK
                    pEnumLoadedModulesCallback,
                PVOID pUserContext);

typedef BOOL (WINAPI *SymCleanupFn) (
                HANDLE hProcess);

typedef BOOL (WINAPI *StackWalkFn) (
                DWORD dwMachineType,                               
                HANDLE hProcess,                                 
                HANDLE hThread,                                  
                LPSTACKFRAME pStk,                         
                PVOID pContextRecord,                             
                PREAD_PROCESS_MEMORY_ROUTINE
                    pReadMemoryRoutine,  
                PFUNCTION_TABLE_ACCESS_ROUTINE
                    pFunctionTableAccessRoutine,  
                PGET_MODULE_BASE_ROUTINE
                    pGetModuleBaseRoutine,              
                PTRANSLATE_ADDRESS_ROUTINE
                    pTranslateAddress);

/* Function pointers to imagehlp API Functions */ 
SymSetOptionsFn             g_pfnSymSetOptions;
SymInitializeFn             g_pfnSymInitialize;
SymCleanupFn                g_pfnSymCleanup;
SymGetSymFromAddrFn         g_pfnSymGetSymFromAddr;
SymGetLineFromAddrFn        g_pfnSymGetLineFromAddr;
EnumerateLoadedModulesFn    g_pfnEnumerateLoadedModules;
SymLoadModuleFn             g_pfnSymLoadModule;
SymGetModuleInfoFn          g_pfnSymGetModuleInfo;
StackWalkFn                 g_pfnStackWalk;

/*
   The callback function that will be invoked for every module
   loaded in the current process
*/
BOOL CALLBACK EnumLoadedModulesCallback
(
    LPSTR pModuleName,
    ULONG ulModuleBase,
    ULONG ulModuleSize,
    PVOID pUserContext
)
{
    /* Load symbolic information of every module */
    if (!g_pfnSymLoadModule((HANDLE)pUserContext,
            0, pModuleName,
            0, ulModuleBase,
            ulModuleSize))
    {
        printf("SymLoadModule failed with error code : %d\n",
            GetLastError());
    }
    return TRUE;
}

/*
   Helper function to load symbol modules on Windows9x
   and Windows NT platforms
*/
void LoadModuleSymbols(DWORD dwProcessId, HANDLE hProcess)
{
    OSVERSIONINFO   osver;
    HINSTANCE       hInstLib;
    HANDLE          hSnapShot;
    MODULEENTRY32   module;
    BOOL            fFlag;

    // ToolHelp Function Pointers.
    HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD);
    BOOL (WINAPI *lpfModule32First)(HANDLE,LPMODULEENTRY32);
    BOOL (WINAPI *lpfModule32Next)(HANDLE,LPMODULEENTRY32);

    // Check to see if were running under Windows9x or
    // Windows NT.

    osver.dwOSVersionInfoSize = sizeof(osver);
    if (!GetVersionEx(&osver))
    {
        printf("GetVersionEx failed with error code : %d\n",
            GetLastError());
        return;
    }
        
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        if (!g_pfnEnumerateLoadedModules(hProcess,
                EnumLoadedModulesCallback,
                (PVOID)hProcess))
        {
            printf("EnumerateLoadedModules failed with error code : %d\n",
                GetLastError());
        }
        return;
    }

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
        hInstLib = LoadLibraryA("Kernel32.DLL") ;
        if (hInstLib == NULL)
            return;

        // Get procedure addresses.
        // We are linking to these functions of Kernel32
        // explicitly, because otherwise a module using
        // this code would fail to load under Windows NT,
        // which does not have the Toolhelp32
        // functions in the Kernel32.

        lpfCreateToolhelp32Snapshot=(HANDLE(WINAPI *)(DWORD,DWORD))
            GetProcAddress(hInstLib, "CreateToolhelp32Snapshot");

        lpfModule32First=(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
            GetProcAddress(hInstLib, "Module32First");

        lpfModule32Next=(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
            GetProcAddress(hInstLib, "Module32Next");

        if (lpfModule32Next == NULL || lpfModule32First == NULL ||
            lpfCreateToolhelp32Snapshot == NULL)
        {
            FreeLibrary(hInstLib);
            return;
        }

        // Get a handle to a Toolhelp snapshot of the modules.
        
        hSnapShot = lpfCreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
                        dwProcessId);
        if (hSnapShot == INVALID_HANDLE_VALUE)
        {
            FreeLibrary(hInstLib);
            return;
        }

        // Get the first module' information.
        module.dwSize = sizeof(module) ;
        fFlag = lpfModule32First(hSnapShot, &module);

        // While there are modules, keep looping.
        while (fFlag)
        {
            if (!g_pfnSymLoadModule(hProcess, 0, module.szExePath, 0, 0, 0))
            {
                printf("SymLoadModule failed with error code : %d\n",
                    GetLastError());
            }
            fFlag = lpfModule32Next(hSnapShot, &module);
        }

        // Free the library
        FreeLibrary(hInstLib) ;
    }   
}

/*
    DWORD LogStackWalk(LPEXCEPTION_POINTERS exceptionInfo)

    This function will interface with imagehlp APIs to display the
    stack trace information. LogStackWalk can be either called in a
    filter expression of a Structured Exception Handling (SEH) block
    or for obtaining stack trace of a function call.
    
    Parameter:

    exceptionInfo   This is the exception information of the thread
                    where an exception occurred. If this parameter is
                    passed as NULL, this function will display the stack
                    trace of a function call of the current thread.

    Return

    This will return EXCEPTION_EXECUTE_HANDLER.
*/

DWORD LogStackWalk(LPEXCEPTION_POINTERS exceptionInfo)
{
    DWORD             dwDisplacement = 0;
    DWORD             dwMachType;
    int               nframes = 0;
    LPSTR             szSymName;
    IMAGEHLP_MODULE   mi;
    STACKFRAME        stk;
    CONTEXT           context;
    LPCONTEXT         lpContext = 0;
    HANDLE            hProcess, hThread;
    IMAGEHLP_LINE     imageLine;
    BOOL              fDisplayCurrentStackFrame = TRUE;
    char              buffer[1024];
    PIMAGEHLP_SYMBOL  pSymbol;
    HINSTANCE         hLibrary;

    hLibrary = LoadLibrary("imagehlp.dll");
    if (hLibrary)
    {
        /* Get all the function pointers to the api's in imagehlp.dll
           that are required */

        g_pfnSymSetOptions = (SymSetOptionsFn)
                            GetProcAddress(hLibrary,
                                "SymSetOptions");

        g_pfnSymInitialize = (SymInitializeFn)
                            GetProcAddress(hLibrary,
                                "SymInitialize");
        g_pfnSymCleanup = (SymCleanupFn)
                            GetProcAddress(hLibrary,
                                "SymCleanup");

        g_pfnSymGetSymFromAddr = (SymGetSymFromAddrFn)
                                GetProcAddress(hLibrary,
                                    "SymGetSymFromAddr");
        g_pfnSymGetLineFromAddr = (SymGetLineFromAddrFn)
                                GetProcAddress(hLibrary,
                                    "SymGetLineFromAddr");

        g_pfnEnumerateLoadedModules = (EnumerateLoadedModulesFn)
                                    GetProcAddress(hLibrary,
                                        "EnumerateLoadedModules");
        g_pfnSymGetModuleInfo = (SymGetModuleInfoFn)
                                GetProcAddress(hLibrary,
                                    "SymGetModuleInfo");
        g_pfnSymLoadModule = (SymLoadModuleFn)
                            GetProcAddress(hLibrary,
                                "SymLoadModule");
        g_pfnStackWalk = (StackWalkFn)
                        GetProcAddress(hLibrary,
                            "StackWalk");

        if (!g_pfnSymSetOptions || !g_pfnSymInitialize || !g_pfnSymCleanup
            || !g_pfnSymGetSymFromAddr || !g_pfnEnumerateLoadedModules
            || !g_pfnSymGetModuleInfo || !g_pfnSymLoadModule
            || !g_pfnStackWalk)
        {
            /* Some functions are not available in imagehlp.dll */
            FreeLibrary(hLibrary);
            return EXCEPTION_EXECUTE_HANDLER;
        }
    }
    else
    {
        return EXCEPTION_EXECUTE_HANDLER;
    }

    hProcess = GetCurrentProcess();
    hThread = GetCurrentThread();

    /* Get the current thread context, if an exception context record is not
       specified. To do this, we need to generate EXCEPTION_ACCESS_VIOLATION
       exception ourselves to capture the exception context record. Then we
       can skip the first stack frame that corresponds to this exception.
       This will be the easiest portable method to obtain a stack trace in
       the case of a function call. This is pretty useful to call this helper
       function to obtain stack trace in the case of an assertion failure
       anywhere in the caller's thread. 
    */
 
    if (!exceptionInfo)
    {
        char* ptr = 0;
        __try
        {
            *ptr = 0;
        }
        __except(CopyMemory(&context,
            (GetExceptionInformation())->ContextRecord,
            sizeof(context)),
            EXCEPTION_EXECUTE_HANDLER)
        {
        }
        lpContext = &context;
        fDisplayCurrentStackFrame = FALSE;
    }
    else
    {
        CopyMemory(&context,
            exceptionInfo->ContextRecord,
            sizeof(context));
        lpContext = &context;
    }

    /*
       Call SymSetOptions to undecorate symbol names and
       load line number information
    */
    g_pfnSymSetOptions(SYMOPT_UNDNAME|SYMOPT_LOAD_LINES);

    /* Initialize the imagehlp symbol handler */
    if (!g_pfnSymInitialize(hProcess, NULL, FALSE))
    {
        return EXCEPTION_EXECUTE_HANDLER;
    }

    /* Load symbol modules for the current process */
    LoadModuleSymbols(GetCurrentProcessId(), hProcess);

    /* Setup the initial stack frame for StackWalk API */
    ZeroMemory(&stk, sizeof(stk));

#if defined(_M_IX86)
    dwMachType = IMAGE_FILE_MACHINE_I386;
    stk.AddrPC.Offset = lpContext->Eip;
    stk.AddrStack.Offset = lpContext->Esp;
    stk.AddrFrame.Offset = lpContext->Ebp;
#elif defined(_M_MRX000)
    dwMachType = IMAGE_FILE_MACHINE_R4000;
    stk.AddrPC.Offset = lpContext->Fir;
    stk.AddrStack.Offset = lpContext->IntSp;
    stk.AddrFrame.Offset = 0;
#elif defined(_M_ALPHA)
    dwMachType = IMAGE_FILE_MACHINE_ALPHA;
    stk.AddrPC.Offset = (ULONG)lpContext->Fir;
    stk.AddrStack.Offset = (ULONG)lpContext->IntSp;
    stk.AddrFrame.Offset = 0;
#elif defined(_M_PPC)
    dwMachType = IMAGE_FILE_MACHINE_POWERPC;
    stk.AddrPC.Offset = lpContext->Iar;
    stk.AddrStack.Offset = lpContext->Gpr1;
    stk.AddrFrame.Offset = 0;
#else
    #error( "unknown target machine" );   // add IA64 someday
    stk.AddrPC.Offset = 0;
#endif

    stk.AddrPC.Mode = AddrModeFlat;
    stk.AddrStack.Mode = AddrModeFlat;
    stk.AddrFrame.Mode = AddrModeFlat;

    /* Setup buffer for retrieving symbol name of a function */
    memset(buffer, 0, sizeof(buffer));
    pSymbol = (PIMAGEHLP_SYMBOL)buffer;
    pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
    pSymbol->MaxNameLength = sizeof(buffer) -
                                sizeof(IMAGEHLP_SYMBOL) + 1;

    /* Call StackWalk to obtain all stack frames */
    while (g_pfnStackWalk(dwMachType,
                        hProcess,
                        hThread,
                        &stk,
                        lpContext,
                        0,
                        0,
                        0,
                        0))
    {
        /* Skip the initial stack frame if it is a function call */
        if (!fDisplayCurrentStackFrame)
        {
            fDisplayCurrentStackFrame = TRUE;
            continue;
        }

        /*
           Get function name corresponding to PC address in
           the current stack frame
        */
        pSymbol->Address = stk.AddrPC.Offset;
        dwDisplacement = 0;
        if (g_pfnSymGetSymFromAddr(hProcess, stk.AddrPC.Offset,
                &dwDisplacement, pSymbol))
        {
            szSymName = pSymbol->Name;
        }
        else
        {

            szSymName = "<nosymbols>";
            printf("SymGetSymFromAddr failed with error code : %d\n",
                GetLastError());
        }

        nframes++;

        /*
           Display the PC address and the parameters passed
           to the function
        */
        printf("(%02d) Return PC Address : %08x\n",
                nframes, stk.AddrPC.Offset);
        printf("     Parameter 1 : %08x\n", stk.Params[0]);
        printf("     Parameter 2 : %08x\n", stk.Params[1]);
        printf("     Parameter 3 : %08x\n", stk.Params[2]);
        printf("     Parameter 4 : %08x\n", stk.Params[3]);

        /*
           Get module name corresponding to PC address in the
           current stack frame
        */
        mi.SizeOfStruct = sizeof(mi);
        if (g_pfnSymGetModuleInfo(hProcess, stk.AddrPC.Offset, &mi))
        {
            printf("     ModuleName : %s\n", mi.ModuleName);
        }

        printf("     Function Name : %s\n", szSymName);

        /*
           Get line number and file name corresponding to PC address
           in the current stack frame
        */
        dwDisplacement = 0;
        imageLine.SizeOfStruct = sizeof(imageLine);
        if (g_pfnSymGetLineFromAddr)
        {
            if (g_pfnSymGetLineFromAddr(
                    hProcess,
                    stk.AddrPC.Offset,
                    &dwDisplacement,
                    &imageLine))
            {
                printf("     File Name : %s\n", imageLine.FileName);
                printf("     Line Number : %d\n", imageLine.LineNumber);
            }
        }

        printf("\n\n");

        if (!stk.AddrReturn.Offset)
        {
            break;
        }
    }

    /* Cleanup all resources of imagehlp symbol handler */
    g_pfnSymCleanup(hProcess);

    printf("\n");

    FreeLibrary(hLibrary);

    return EXCEPTION_EXECUTE_HANDLER;
}

/***** The code above can be plugged into any application *****/

/*
   The following functions below are just an example how to call
   LogStackWalk() in the following cases.

   1. For tracing a function call
   2. In an exception caught using SEH
   3. In an exception caught by unhandled exception filter
*/

/*
   UnhandledExceptionFilter function to call
   LogStackWalk for an exception that is unhandled
*/
LONG WINAPI MyUnhandledExceptionFilter(LPEXCEPTION_POINTERS pExceptionInfo)
{
    if (pExceptionInfo)
    {
        LogStackWalk(pExceptionInfo);
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

int f4a(int a, int b, int c, int d)
{
    /* Stack trace of the current thread */
    printf("\nStack Trace of a function call\n\n");

    LogStackWalk(NULL);

    return 0;
}

int f4b(int a, int b, int c, int d)
{
    char* ptr = 0;

    /* Stack trace in an exception caught using SEH */
    printf("\nStack Trace of an exception caught using SEH\n\n");

    __try
    {
        *ptr = 0;
    }
    __except (LogStackWalk(GetExceptionInformation()))
    {
    }

    return 0;
}

int f4c(int a, int b, int c, int d)
{
    char* ptr = 0;
    LPTOP_LEVEL_EXCEPTION_FILTER pfnFilter;

    /* Stack trace in an exception caught by UnhandledExceptionFilter */
    printf("\nStack Trace of an exception caught by"
            "UnhandledExceptionFilter\n\n");

    pfnFilter = SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

    *ptr = 0;

    return 0;
}

int f4(int a, int b, int c, int d)
{
    f4a(a, b, c, d);
    f4b(a, b, c, d);
    f4c(a, b, c, d);

    return 0;
}

int f3(int a, int b, int c, int d)
{
    a = b + c;
    return f4(a, b, c, d);
}

int f2(int a, int b, int c, int d)
{
    b = c + d;
    return f3(a, b, c, d);
}

int f1(int a, int b, int c, int d)
{
    c = d;
    return f2(a, b, c, d);
}

void main(int argc, char** argv)
{
    f1(0, 0, 0, 2);
}
