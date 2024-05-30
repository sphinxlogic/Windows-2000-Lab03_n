// --UTL_PAS.C------------------------------------------------------------------
//
// Get password from the user helper function
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "utl_pas.chk"

//$--_HrInputCommandLinePassword---------------------------------------------------------
//
//  DESCRIPTION: Input password and echo *'s.
//
//  INPUT:  dwFlags     --  reserved - must be zero
//          cbLength    --  length of buffer/password
//
//  OUTPUT: pszBuffer   --  buffer to write password into
//
//  RETURNS:    HRESULT --  NOERROR if no error,
//                          E_FAIL if user enters ctrl-c,
//                          E_INVALIDARG if bad input
//
// -----------------------------------------------------------------------------
HRESULT _HrInputCommandLinePassword(				// RETURNS: HRESULT
	IN DWORD dwFlags,					// reserved--must be zero
	IN DWORD cbLength,	  		        // size of the buffer in bytes
	OUT LPSTR pszBuffer)				// buffer to write string into
{
    HRESULT     hr          = NOERROR;
    LPSTR		psz			= pszBuffer;

	DEBUGPUBLIC("_HrInputCommandLinePassword()\n");

    // check input parameters
    hr = CHK__HrInputCommandLinePassword(dwFlags, cbLength, pszBuffer);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    for(;;)
    {
        int ch = _getch();

		// Handle Ctrl-C.

		if (ch == '\003')
		{
			printf("^C");
			hr = HR_LOG(E_FAIL);
			*pszBuffer = 0;
			break;
		}

		// Handle backspace.

		if (ch == '\b' && psz > pszBuffer)
		{
			printf( "\b \b" );
			psz--;
			cbLength++;
		}

		// Handle normal printable character.

		if (isprint(ch))
		{
	        printf ( "*" );
	        *psz++ = ch;
	        cbLength--;
		}

		// Handle input termination.

        if (ch == '\n' || ch == '\r' || cbLength < 2)
        {
            *psz = 0;
            break;
        }
    }

    printf ( "\n" );

	RETURN(hr);

}
