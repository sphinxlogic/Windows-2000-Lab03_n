/*************************************************************************
                    Copyright Microsoft Corp. 1992-1996
                        Remote Machine strout sample

  FILE      :   server.c

  USAGE     :   server  -p protocol_sequence
                        -e endpoint
                        
  PURPOSE   :   Server side of the RPC distributed application strout.

  COMMENTS  :   This application uses the implicit binding method.

*************************************************************************/
#include "strout.h"                 /* Generated by the midl compiler   */
#include "common.h"                 /* Common definitions in this file  */

/* Local Procedures */
void CleanUpServer(void);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Procedure   :   void Usage(_TUCHAR *)                               */
/*  Desc        :   This procedure prints out an error message if the   */
/*                  command line arguments are wrong                    */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Usage(_TUCHAR * pszProgramName)
{
    _tprintf(TEXT("USAGE : %s [-option]\n"), pszProgramName);
    _tprintf(TEXT("Options : -p Protocol Sequence\n"));  
    _tprintf(TEXT("          -e Endpoint\n"));  
    exit(EXECUTION_OK);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* The server main program                                              */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int main(int argc, char *argv[])
{
    int             nNumArgs,   /* The number of command line arguments */
                    nIdx;       /* Counter in loops                     */
    RPC_STATUS      nStatus;    /* Error status returned                */

    // Variabels used for selecting the protocol and the endpoint
    _TUCHAR *pszProtocolSequence    = PROTOCOL_SEQUENCE;
    _TUCHAR *pszEndpoint            = END_POINT;
    _TUCHAR *pszSecurity            = NULL;


/* Get a common handle on the command line arguments for both UNICODE   */
/* and ASCII                                                            */
#ifdef _UNICODE
    LPWSTR	*pArglist = CommandLineToArgvW(GetCommandLine(), &nNumArgs);
    if (NULL == pArglist)
    {
        _tprintf(TEXT("SERVER.C : CommandLineToArgW failed"));
        exit(EXECUTION_FAILED);
    }
#else
    char **pArglist = argv;
    nNumArgs = argc;
#endif

    /* Allow the user to override settings with commandline switches    */
    for (nIdx = 1; nIdx < nNumArgs; nIdx++) 
    {
        if((_tcscmp(pArglist[nIdx], TEXT("-p")) == 0) || 
           (_tcscmp(pArglist[nIdx], TEXT("-P")) == 0))
        {
            pszProtocolSequence = pArglist[++nIdx];
        }
        else if((_tcscmp(pArglist[nIdx], TEXT("-e")) == 0) || 
                (_tcscmp(pArglist[nIdx], TEXT("-e")) == 0))
        {
            pszEndpoint = pArglist[++nIdx];
        }
        else 
        {
            Usage(pArglist[0]);
        }
    }
            
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Register the interface with the RPC run-time library             */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    _tprintf(TEXT("Registering the interface\n"));
    nStatus = RpcServerRegisterIf(
        strout_sample_v1_0_s_ifspec,    // Interface specification
        NULL,                           // UUID to ass. with MgrEnv arg.
        NULL);                          // Managers entry point vector.
    EXIT_IF_FAIL(nStatus, "RpcServerRegisterIf");


    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Select Protocal sequence : This sample uses namedpipes as the    */
    /* default protocol. The RpcServerUseProtseqEp function tells the   */
    /* RPC run-time library to use the specified protocol sequence      */
    /* combined with the specified endpoint for receiving remote        */
    /* procedure calls                                                  */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    _tprintf(TEXT("Selecting the protocol sequence: \"%s\"\n"),
        pszProtocolSequence);
    nStatus = RpcServerUseProtseqEp(
        pszProtocolSequence,            // String with the protocol in
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT, // Max number of calls
        pszEndpoint,                    // Endpoint addres information
        pszSecurity);                   // Security
    EXIT_IF_FAIL(nStatus, "RpcServerUseProtseqsEp");

	
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Now start listening for remote procedure calls from the client   */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    RpcTryExcept
    {
        _tprintf(TEXT("Listening for remote calls...\n"));
        nStatus = RpcServerListen(
            1,                              // The minimum number of calls
            RPC_C_LISTEN_MAX_CALLS_DEFAULT, // The maximum number of calls
            FALSE);                         // Cont. until expl. stopped
        EXIT_IF_FAIL(nStatus, "RpcServerListen");
    }
    RpcExcept(DO_EXCEPTION)
    {
        // Print out the exception code 
        _tprintf(TEXT("Run-time exception %u in %s at line %d\n"), 
                RpcExceptionCode(), TEXT(__FILE__), __LINE__);
        exit(EXECUTION_FAILED);
    }
    RpcEndExcept


    // If no exceptions occured, clean up the server and exit
    CleanUpServer();

    // Deallocate the memory used for the ARGLIST if using UNICODE
#ifdef _UNICODE
    if (NULL != pArglist)
        free(pArglist);
#endif

    return (EXECUTION_OK);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Procedure    : void CleanUpServer(RPC_BINDING_VECTOR);               */
/* Desc.        : This procedure will unregister the interface          */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void CleanUpServer(void)
{
    RPC_STATUS nStatus;          // Error status returned from RPC calls 

    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Unregister the interface from the RPC run-time library           */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    _tprintf(TEXT("Unregistering the Interface"));
    nStatus = RpcServerUnregisterIf(
        NULL, NULL, // Prevents server from receiving new remote calls
        FALSE);     // Wait until all the active calls are complete 
    EXIT_IF_FAIL(nStatus, "RpcServerUnRegisterIf");
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Procedure    :   midl_user_allocate() and midl_user_free()           */
/* Desc.        :   These procedure are declared in the header file     */
/*                  generated by the midl compiler. These procedures    */
/*                  should be used for all memory allocation and        */
/*                  deallocation.                                       */
/*                  These procedures are also called by the stub code   */
/*                  to allocate and free memory.                        */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void __RPC_FAR * __RPC_API midl_user_allocate(size_t nLen)
{
    return (malloc(nLen));
}

void __RPC_API midl_user_free(void __RPC_FAR * lpvPointer)
{
    if(NULL != lpvPointer)
        free (lpvPointer);
}

