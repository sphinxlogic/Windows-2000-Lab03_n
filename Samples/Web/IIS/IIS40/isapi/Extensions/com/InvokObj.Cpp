/*++

Copyright (c) 1997  Microsoft Corporation

Module Name:    InvokObj.cpp

Abstract:

    ISAPI Extension sample to invoke an automation server method

--*/

#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <httpext.h>


//
// Import type library information about the COM object
//

#import "GetUserName.dll"


BOOL WINAPI 
GetExtensionVersion(
    HSE_VERSION_INFO *pVer
    )
/*++

Purpose:

    This is required ISAPI Extension DLL entry point.

Arguments:

    pVer - poins to extension version info structure 

Returns:

    always returns TRUE

--*/
{
    pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR, 
                                         HSE_VERSION_MAJOR );
    lstrcpyn( pVer->lpszExtensionDesc, 
        "InvokObj ISAPI Sample", HSE_MAX_EXT_DLL_NAME_LEN );

    //
    // Ensure COM is initialized
    //

    CoInitialize( NULL );

    return TRUE;
}


DWORD WINAPI 
HttpExtensionProc(
    EXTENSION_CONTROL_BLOCK *pECB
    )
/*++

Purpose:

    Demonstrate how to create an instance of the automation object
    using VC++ 5.0 extensions and how to invoke its method.

Arguments:

    pECB - pointer to the extenstion control block 

Returns:

    HSE_STATUS_SUCCESS on successful transmission completion
    HSE_STATUS_ERROR on failure

--*/
{
    char szOutput[1024];
    DWORD dwBuffSize;
    GETUSERNAMELib::IGetUserNameObjPtr pItf;
    HSE_SEND_HEADER_EX_INFO HeaderExInfo;
    HRESULT hr;

    //
    // Send headers back to client
    //

    HeaderExInfo.pszStatus = "200 OK";
    HeaderExInfo.cchStatus = strlen( HeaderExInfo.pszStatus );
    HeaderExInfo.pszHeader = "Content-type: text/html\r\n\r\n";
    HeaderExInfo.cchHeader = strlen( HeaderExInfo.pszHeader );
    HeaderExInfo.fKeepConn = FALSE;

    pECB->ServerSupportFunction( pECB->ConnID, 
        HSE_REQ_SEND_RESPONSE_HEADER_EX,
        &HeaderExInfo, NULL, NULL );

    //
    // Initialize an instance of the automation server
    //
    
    hr = pItf.CreateInstance( L"GetUserNameObj.GetUserNameObj.1" );

    if ( FAILED( hr ) )
    {
        wsprintf( szOutput, "<h1>Error.</h1><hr>Attempt to create instance "
            "of GetUserNameObj object failed with error %x.", hr );
        dwBuffSize = strlen( szOutput );

        pECB->WriteClient( pECB->ConnID, szOutput, &dwBuffSize, 0 );

        return HSE_STATUS_SUCCESS;
    }


    //
    // Build the output using the result of the call to
    // GetUserNameObj's GetMyName method
    //
    
    wsprintf( szOutput, "<h1>GetUserNameObj successfully instantiated."
        "</h1><hr>The GetMyName method returned %s.", 
        (char *)pItf->GetMyName( ) );
    

    //
    // Send the output back to the client
    //
    
    dwBuffSize = strlen( szOutput );
    pECB->WriteClient( pECB->ConnID, szOutput, &dwBuffSize, 0 );


    return HSE_STATUS_SUCCESS;
}


BOOL WINAPI 
TerminateExtension(
    DWORD dwFlags
    )
/*++

Purpose:

    This is optional ISAPI extension DLL entry point.
    If present, it will be called before unloading the DLL,
    giving it a chance to perform any shutdown procedures.
    
Arguments:
    
    dwFlags - specifies whether the DLL can refuse to unload or not
    
Returns:
    
    TRUE, if the DLL can be unloaded
    
--*/
{
    //
    // Balance the call to CoInitialize that we made in GetExtensionVersion
    //

    CoUninitialize( );

    //
    // It is now OK to unload
    //
    
    return TRUE;
}



