/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994- 1996
                         nhello Example

    FILE:       nhellos.c

    USAGE:      nhellos
                        -m maxcalls
                        -n mincalls
                        -f flag for RpcServerListen wait
                        -a nhello_sample_nsi_entry_name
                        -t name_syntax_type

    PURPOSE:    Server side of RPC distributed application nhello

    FUNCTIONS:  main() - registers server as RPC server

    COMMENTS:

****************************************************************************/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "nhello.h"   // header file generated by MIDL compiler

BOOL WINAPI ControlHandler ( DWORD dwCtrlType );

void Usage(char * pszProgramName)
{
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -m maxcalls\n");
    fprintf(stderr, " -n mincalls\n");
    fprintf(stderr, " -f flag for RpcServerListen wait\n");
    fprintf(stderr, " -a nhello_sample_nsi_entry_name\n");
    fprintf(stderr, " -t name_syntax_type\n");
    exit(1);
}

void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    RPC_BINDING_VECTOR * pBindingVector = NULL;
    unsigned char * pszEntryName    = "/.:/nhello_sample";
    unsigned char * pszSecurity     = NULL;
    unsigned int    cMinCalls       = 1;
    unsigned int    cMaxCalls       = 20;
    unsigned int    fDontWait       = 0;
    unsigned int    fNameSyntaxType = RPC_C_NS_SYNTAX_DEFAULT;
    unsigned int    fRegistered     = 0;
    unsigned int    fEndpoint       = 0;
    unsigned int    fExported       = 0;
    int i;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'm':
                cMaxCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'n':
                cMinCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'f':
                fDontWait = (unsigned int) atoi(argv[++i]);
                break;
            case 'a':
                pszEntryName = argv[++i];
                break;
            case 't':
                fNameSyntaxType = (unsigned int) atoi(argv[++i]);
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    SetConsoleCtrlHandler( ControlHandler, TRUE );

    printf("CallingRpcServerUseAllProtseqs...\n");

    status = RpcServerUseAllProtseqs(cMaxCalls,     // max concurrent calls
                                     pszSecurity);  // Security descriptor
    printf("RpcServerUseAllProtseqs returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }

    status = RpcServerRegisterIf(nhello_v1_0_s_ifspec, // interface to register
                                 NULL,   // MgrTypeUuid
                                 NULL);  // MgrEpv; null means use default
    printf("RpcServerRegisterIf returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }
    else
        fRegistered = 1;

    status = RpcServerInqBindings(&pBindingVector);
    printf("RpcServerInqBindings returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }

    status = RpcEpRegister(nhello_v1_0_s_ifspec,
                           pBindingVector,
                           NULL,
                           "");
    printf("RpcEpRegister returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }
    else
        fEndpoint = 1;

    status = RpcNsBindingExport(fNameSyntaxType,  // name syntax type
                                pszEntryName,     // nsi entry name
                                nhello_v1_0_s_ifspec,
                                pBindingVector,   // set in previous call
                                NULL);            // UUID vector
    printf("RpcNsBindingExport returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }
    else
        fExported = 1;

    printf("Calling RpcServerListen\n");
    status = RpcServerListen(cMinCalls,
                             cMaxCalls,
                             fDontWait);  // wait flag
    printf("RpcServerListen returned: 0x%x\n", status);
    if (status) {
        goto cleanup;
    }

    if (fDontWait) {
        printf("Calling RpcMgmtWaitServerListen\n");
        status = RpcMgmtWaitServerListen();  //  wait operation
        printf("RpcMgmtWaitServerListen returned: 0x%x\n", status);
    }

  cleanup:

    if ( fExported )
    {
        status = RpcNsBindingUnexport(RPC_C_NS_SYNTAX_DEFAULT,  // name syntax type
                                       pszEntryName,            // nsi entry name
                                       nhello_v1_0_s_ifspec,
                                       NULL);                   // UUID vector
        printf( "RpcNsBindingUnexport returned 0x%x\n", status);
    }


    if ( fEndpoint )
    {
        status = RpcEpUnregister(nhello_v1_0_s_ifspec,
                                  pBindingVector,
                                  NULL);
        printf( "RpcEpUnregister returned 0x%x\n", status);
    }

    if ( pBindingVector )
    {
        status = RpcBindingVectorFree(&pBindingVector);
        printf( "RpcBindingVectorFree returned 0x%x\n", status);
    }

    if ( fRegistered )
    {
        status = RpcServerUnregisterIf(nhello_v1_0_s_ifspec, // interface to register
                                       NULL,   // MgrTypeUuid
                                       1);     // wait for outstanding calls
        printf( "RpcServerUnregisterIf returned 0x%x\n", status);
    }


}  // end main()


//
//  FUNCTION: ControlHandler ( DWORD dwCtrlType )
//
//  PURPOSE: Handled console control events
//
//  PARAMETERS:
//    dwCtrlType - type of control event
//
//  RETURN VALUE:
//    True - handled
//    False - unhandled
//
//  COMMENTS:
//
BOOL WINAPI ControlHandler ( DWORD dwCtrlType )
{
    RPC_STATUS status;

    switch( dwCtrlType )
    {
        case CTRL_BREAK_EVENT:  // use Ctrl+C or Ctrl+Break to call shutdown
        case CTRL_C_EVENT:

            printf("Calling RpcMgmtIsServerListening\n");
            status = RpcMgmtIsServerListening(NULL);
            printf("RpcMgmtIsServerListening returned: 0x%x\n", status);

            if ( status == RPC_S_OK )
            {
                printf("Calling RpcMgmtStopServerListening\n");
                status = RpcMgmtStopServerListening(NULL);
                printf("RpcMgmtStopServerListening returned: 0x%x\n", status);
            }
            break;

    }
    return FALSE;
}


/*********************************************************************/
/*                 MIDL allocate and free                            */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

/* end file nhellos.c */