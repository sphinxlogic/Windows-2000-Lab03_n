// --UTL_CLI.C------------------------------------------------------------------
//
// Command line argument parsing helper functions.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "edk.h"

#include <stdio.h>
#include <string.h>
#include "utl_cli.chk"

#define NO_MATCH    ((ULONG) ~0)
#define MAXARG      250     // Maximum length of a single command line argument.
        
//$--_HrFindArrayValue--------------------------------------------------------
// Scan through an array of string pointers searching for a value string that
// matches up to the length of the value string.  Case INSENSITIVE.
//
// OUTPUT:  pnIndex will contain the index into the array of the match.  It will
//          contain ~0 if no match was found.  
//
// RETURNS: NOERROR
//          EDK_E_NOT_FOUND if match was not found.
//          EDK_E_AMBIGUOUS if more than one match was found.
//          E_INVALIDARG
// -----------------------------------------------------------------------------

HRESULT _HrFindArrayValue(
    IN  char*  pszValue,    // Ptr to string value to find.
    IN  char** rgpszArray,  // Array of strings containing known values.
    IN  ULONG  nArraySize,  // Number of known values.
    OUT ULONG* pnIndex)     // Ptr to index of known value, ~0 if no match found.
{
    HRESULT hr          = NOERROR;
    ULONG   ii          = 0;
    int     nCompLen    = 0;

    DEBUGPUBLIC( "_HrFindArrayValue()\n");

    // Check the input parameters.
    hr = CHK__HrFindArrayValue( pszValue, rgpszArray, nArraySize, pnIndex);
    if( FAILED( hr))
        RETURN( hr);
    
    // Get the length of the input string and verify that it is greater than zero.
    nCompLen = lstrlenA( pszValue);
    if( nCompLen <= 0)
        RETURN( E_INVALIDARG);

    // Initialize output parameter and return value.
    *pnIndex = NO_MATCH;
    hr = EDK_E_NOT_FOUND;  

    // Search for the value.
    for( ii = 0; ii < nArraySize; ii ++)
    {
        // Ignore NULL's in the array.
        if( rgpszArray[ ii] == NULL)
            continue;

        // Compare value and entry in array.  The comparison is NOT case sensitive.
        if( _strnicmp( pszValue, rgpszArray[ ii], nCompLen) == 0)
        {   //  If no previous matches have been found, then remember
            //  the current array index.  If a match has already been
            //  found then abort.
            if( *pnIndex == NO_MATCH)
            {   // The first match has been found
                *pnIndex = ii;
                hr = NOERROR;
            }
            else
            {   // Second match, this is ambiguous.
                *pnIndex = NO_MATCH;

                // Return the appropriate error.
                hr = EDK_E_AMBIGUOUS;

                goto cleanup;
            }
        }
    }

cleanup:
    // Don't use RETURN() since it would log EDK_E_NOT_FOUND as an error
    // and we don't wish to log this here. Let the caller do it if need be.
    return( hr);
}


//$--_HrExpandCommandLineArgument-----------------------------------------------
//
// DESCRIPTION: Expands abbreviated command line flags of the form -FLAG=VALUE (or
//              /FLAG=VALUE) to their full text forms returning the index of the  
//              matching flag and a pointer to the data part of the flag (ie the 
//              part after the equals sign).  The caller passes an array of known 
//              flag names, and the function tries to make an unambiguous match 
//              with one of the names.  In this way users can be offered the 
//              convenience of entering /V=Foo, instead of
//              /VERY-LONG-AND-CLUMSY-NAME=Foo (assuming no other flag begins with
//              V, otherwise the user might have to enter more letters).
//
//              The comparison is not case sensitive; the flag names /BLUTO and
//              -bluto are not distinguished, and /b might match on either of them.
//
//              To maintain greater compatibility with other Microsoft NT and DOS
//              command line applications, the ":" character may be substituted 
//              for the "=".  So /FLAG:VALUE or -FLAG:VALUE are also valid.
//
//
//  INPUT:  pszArg          command line flag
//          rgpszArgArray   array of known flag names (without leading dashes)
//          nArraySize      number of elements in rgpszArgArray
//
//  OUTPUT: pnFlagIndex     pointer to index of matching flag name, ~0 if no match.
//          ppszFlagName    pointer to known flag name.
//                          Either of the above output parameters may be NULL.
//          ppszArgData     pointer to flag data. (NULL is NOT okay)
//
//  RETURNS:    HRESULT     NOERROR if no error (value without flag is OK),
//                          E_INVALIDARG if bad input,
//                          EDK_E_NOT_FOUND if unknown flag name
//                          EDK_E_AMBIGUOUS if more than one match found.
//                          E_FAIL if user argument is too long.
// -----------------------------------------------------------------------------

HRESULT _HrExpandCommandLineArgument(
    IN  char*  pszArg,          // flag user entered
    IN  char** rgpszArgArray,   // array of known flag names (w/o leading dashes)
    IN  ULONG  nArraySize,      // number of known flags
    OUT ULONG* pnFlagIndex,     // ptr to index of known flag, -1 if no match found.
	OUT char** ppszFlagName,	// pointer to known flag name
    OUT char** ppszArgData)     // ptr to user data for flag
{
    HRESULT hr                  = NOERROR;
    ULONG   nMatchIndex         = NO_MATCH;
    int     nCompLen            = 0;
    char*   pszSeparatorChar    = NULL;
    char    szArg[MAXARG + 1]  = "";

    DEBUGPUBLIC("_HrExpandCommandLineArgument()\n");

    // Check the input parameters
    hr = CHK__HrExpandCommandLineArgument( pszArg, rgpszArgArray, nArraySize,
                                            pnFlagIndex, ppszFlagName, ppszArgData);
    if( FAILED( hr))
        RETURN( hr);

    // Initialize output parameters.        
    if( pnFlagIndex)
        *pnFlagIndex = NO_MATCH;
    if( ppszFlagName)
        *ppszFlagName = NULL;
    *ppszArgData = NULL;

    if (*pszArg != '-' && *pszArg != '/')
    {
        //
        //  If this is not a flag parameter, set the argument
        //  data pointer to point to the beginning of the
        //  argument.
        //

        *ppszArgData = pszArg;
        goto cleanup;
    }

    //
    //  Advance beyond the flag introducer.
    //

    ++pszArg;

    //
    //  Look for an separator character ('=' or ':'), marking the end of the
    //  flag text and the start of the flag data.  Only use characters before 
    //  the separator character (if it is there) for matching.
    //

    pszSeparatorChar = pszArg + strcspn(pszArg,"=:");
    if (*pszSeparatorChar == 0)
        pszSeparatorChar = NULL;

    if (pszSeparatorChar == NULL)
        nCompLen = lstrlenA(pszArg);
    else
        nCompLen = (pszSeparatorChar - pszArg);

    //
    //  Abort if there is nothing to examine.
    //

    if (nCompLen <= 0)
    {
        hr = HR_LOG(EDK_E_NOT_FOUND);
        goto cleanup;
    }


    // If argument is not too long copy it into a buffer.
    if( nCompLen > MAXARG)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }
    CopyMemory( szArg, pszArg, nCompLen);
    szArg[ nCompLen] = '\0';
    

    // Scan through the argument array looking for matches with the 
    // command line argument.
    hr = _HrFindArrayValue( szArg, rgpszArgArray, nArraySize, &nMatchIndex);
    if( FAILED( hr))
        goto cleanup;

    // Found the argument so set the output parameters.
    if (pszSeparatorChar != NULL)
        *ppszArgData = pszSeparatorChar + 1;
    if( pnFlagIndex)
        *pnFlagIndex = nMatchIndex;
    if( ppszFlagName)
        *ppszFlagName = rgpszArgArray[ nMatchIndex];

cleanup:

    RETURN(hr);
}

//$--_nEcFromHr--------------------------------------------------------------
//
// DESCRIPTION:
//
// Convert an HRESULT to an exit code suitable for return
// from a console application.
//
// NOTE:
//
// EDK HRESULTS get converted to their "code" (current 1 - 6).
// Any successful HRESULT converts to zero.
// Any EDK "approved" Win32 or OLE HRESULT gets converted
// to its EDK exit code (currently 11 - 15).
// Any non-EDK approved HRESULT gets converted to EC_EDK_E_UNKNOWN
// (currently 20).  See edkcode.h for definitions.
//
// INPUT:       hr  --  HRESULT to convert
//
// RETURNS:     INT --  see note above
//
//-----------------------------------------------------------------------------
INT _nEcFromHr(      // returns INT
            IN HRESULT hr)      // HRESULT to convert to exit code
{                      
    INT ec  =   0;              // console application exit code

    DEBUGPUBLIC("_nEcFromHr()\n");

    // doesn't need a check function.
        
    if ( SCODE_FACILITY(hr) ==
         FACILITY_EDK )       
    {                         
        // EDK HRESULT defined in edk.h
        // return HRESULT code.
        ec = SCODE_CODE(hr); 
        goto cleanup;
    }                         

    // See if we have an "approved" EDK Win32 or OLE HRESULT    
    switch ( hr )             
    {                         
        case NOERROR:
            // Success!  Return standard "success" exit
            // code
            ec = 0;
            break;

        case E_FAIL:          
            // return corresponding EDK exit code
            ec = EC_EDK_E_FAIL; 
            break;
                                  
        case E_INVALIDARG:        
            // return corresponding EDK exit code
            ec = EC_EDK_E_INVALIDARG;
            break;
                                         
        case E_NOTIMPL:                  
            // return corresponding EDK exit code
            ec = EC_EDK_E_NOTIMPL;     
            break;
                                         
        case E_NOINTERFACE:              
            // return corresponding EDK exit code
            ec = EC_EDK_E_NOINTERFACE; 
            break;
                                         
        case E_OUTOFMEMORY:              
            // return corresponding EDK exit code
            ec = EC_EDK_E_OUTOFMEMORY; 
            break;

		case E_ACCESSDENIED:
			// return corresponding EDK exit code
			ec = EC_EDK_E_ACCESSDENIED;
			break;
			                                         
        default:                         
            // Non-EDK approved HRESULT.
            // return "unknown" exit code.
            ec = EC_EDK_E_UNKNOWN;
            break;

    }   // end switch

cleanup:

    // we are done
    return ec;

}
