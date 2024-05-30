// --msgparse.cpp-------------------------------------------------------------
//
// API entry points for the msgemit static link library.
// Contains helper functions for converting Ascii
// 822-style headers to MAPI messages.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "msgemit.h"
#include "tagnames.h" 
#include "msgparse.chk"

// Value to string lookup tables.

// Day of week lookup table
static const STRINGVALUEPAIRA rgSortedDay[nDays]  =
{
    {5, lpszFridayA      },
    {1, lpszMondayA      },
    {6, lpszSaturdayA    },
    {0, lpszSundayA      },
    {4, lpszThursdayA    },
    {2, lpszTuesdayA     },
    {3, lpszWednesdayA   }
};

// Month of year lookup table
static const STRINGVALUEPAIRA rgSortedMonth[nMonths]  =   
{
    {4,  lpszAprilA      },
    {8,  lpszAugustA     },
    {12, lpszDecemberA   },
    {2,  lpszFebruaryA   },
    {1,  lpszJanuaryA    },
    {7,  lpszJulyA       },
    {6,  lpszJuneA       },
    {3,  lpszMarchA      },
    {5,  lpszMayA        },
    {11, lpszNovemberA   },
    {10, lpszOctoberA    },
    {9,  lpszSeptemberA  }
};

// Trace action lookup table
static const STRINGVALUEPAIR rgAction[nActions]    =
{
    { MD_AC_EXPANDED,    lpszExpanded   },  // MD_AC_EXPANDED = -2
    { MD_AC_REDIRECTED,  lpszRedirected },  // MD_AC_REDIRECTED = -1
    { MD_AC_RELAYED,     lpszRelayed    },  // MD_AC_RELAYED = 0
    { MD_AC_REROUTED,    lpszRerouted   }   // MD_AC_REROUTED = 1
};

// Priority string lookup table
static const STRINGVALUEPAIR rgPriority[nPriorities]   =   
{
    { PRIO_NONURGENT,   lpszNonUrgent       },  // PRIO_NONURGENT = -1
    { PRIO_NORMAL,      lpszNormalUrgency   },  // PRIO_NORMAL = 0
    { PRIO_URGENT,      lpszUrgent          }   // PRIO_URGENT = 1
};

// Importance values lookup table
static const STRINGVALUEPAIR rgImportance[nImportances]    =   
{
    { IMPORTANCE_HIGH,      lpszHighImp     },  // IMPORTANCE_HIGH = 2
    { IMPORTANCE_LOW,       lpszLowImp      },  // IMPORTANCE_LOW = 0
    { IMPORTANCE_NORMAL,    lpszNormalImp   }   // IMPORTANCE_NORAML = 1
};

// static inline "macro" function for speed of execution.

//$--nAsciiHexToInt------------------------------------------------------------
// DESCRIPTION:
//
// Static inline function which converts a hexadecimal
// "character" to its equivalent integer value (e.g. 'F' to 15).
// This function is a static inline function with
// no parameter checking for speed!
//
// INPUT:   chHex   --  hexadecimal character
//
// RETURNS: UINT
//
// ----------------------------------------------------------------------------
static inline UINT nAsciiHexToInt(
            IN CHAR chHex)         // hexadecimal character
{
    // Covert hex character to decimal
    if ( isdigit(chHex) ) 
    {
        return(chHex - '0');
    }
    
    else
    {        
        return((chHex - 'A') + 10);
    }
}

//$----HrFindStringValue--------------------------------------------------------
//
// DESCRIPTION: Convert a string to its associated
//              integer value.
//
// INPUT:       lpString  --  string
//              nValues --  number of values in array
//              rgValue --  string value pair array
//             
// OUTPUT:      pulValue --  pointer to value
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
static HRESULT HrFindStringValue(
    IN LPSTR lpString,         // string
    IN UINT nValues,            // number values in array
    IN const STRINGVALUEPAIR rgValue[],   // string value pair array
    OUT ULONG * pulValue)       // value pointer
{
    HRESULT hr          =   NOERROR;
    UINT    iValue      =   0;      // current index into string value array
    INT     nRetVal     =   0;      // lstrcmp return value
    BOOL    fFound      =   FALSE;  // TRUE if value found

    DEBUGPRIVATE("HrFindStringValue()\n");

    // check input parameters
    hr = CHK_HrFindStringValue(lpString, nValues, rgValue, pulValue);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pulValue = 0;   // initialize

    // Find matching string
    // These arrays are small enough that a linear search is
    // acceptable.
    for ( iValue = 0; iValue < nValues; iValue++ )
    {
        nRetVal = lstrcmp(
                lpString, 
                rgValue[iValue].lpszString);

        if ( nRetVal == 0 )     // strings match
        {
            // found it.  Assign value.
            *pulValue = rgValue[iValue].lValue;

            fFound = TRUE;

            break;
        }

        // continue with next entry

    }   // end for

    // Test to see if value found
    if ( fFound == FALSE )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done.

cleanup:

    RETURN(hr);

}

//$----HrReadNextString---------------------------------------------------------
//
// DESCRIPTION: Read string up to next separator character.
//
// INPUT:   lpString    --  input string
//          chSeparator --  separator character
//          cbBuffer    --  # bytes in output buffer          
//
// OUTPUT:  pszOutput  --  output string
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise
//
// ----------------------------------------------------------------------------
static HRESULT HrReadNextString(
    IN LPSTR lpString,     // input string
    IN CHAR chSeparator,   // separator character
    IN UINT cbBuffer,       // # bytes in buffer
    OUT CHAR * pszOutput)  // output buffer
{
    HRESULT hr      =   NOERROR;
    LPSTR  lpTemp  =   NULL;       // temporary string pointer
    LPSTR  lpOut   =   NULL;       // pointer intot output string
    UINT    cbRead  =   0;          // count of bytes read into output buffer
    CHAR   cTemp   =   0;          // current character

    DEBUGPRIVATE("HrReadNextString()\n");

    // check input parameters
    hr = CHK_HrReadNextString(lpString, chSeparator, cbBuffer,
                              pszOutput);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pszOutput = 0;     // initialize output buffer

    lpOut = pszOutput;  // output string pointer
    lpTemp = lpString;  // input string pointer

    while ( cbRead < cbBuffer )
    {
        cTemp = *lpTemp;    // get current character

        // Test the current character
        if ( cTemp == chSeparator )
        {
            // We are done!
            goto cleanup;
        }
        
        if ( cTemp == 0 )
        {
            // we have reached the end of the string.
            // and haven't seen the separator.
            hr = HR_LOG(E_FAIL);            

            goto cleanup;
        }

        // Otherwise, copy the character read into the 
        // output buffer.
        *lpOut = cTemp;

        cbRead += sizeof(CHAR);    // increment # of characters read
        
        lpTemp++;   // increment pointer into input string
        lpOut++;    // increment pointer into output string

    }   // end while

    // we are done

cleanup:

    *lpOut = 0;

    RETURN(hr);

}

//$----HrParseTagAndData-------------------------------------------------------
//
// DESCRIPTION: Parse ASCII 822-style header line into
//              tag and data components.
//
// INPUT:       lpStream    --  stream pointer to read from
//
// OUTPUT:      pcbRead --  number of bytes read from stream
//              ppTag   --  pointer to tag buffer
//              ppData  --  pointer to data buffer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_OUTOFMEMORY if memory problem
//                          EDK_E_END_OF_FILE if end of stream
//                          E_FAIL otherwise
//
// ---------------------------------------------------------------------------
HRESULT HrParseTagAndData(
        IN LPSTREAM lpStream,   // stream pointer
        OUT ULONG * pcbRead,    // # of bytes read
        OUT LPSTR * lppTag,    // pointer to tag buffer
        OUT LPSTR * lppData)   // pointer to data buffer
{
    HRESULT         hr          =   NOERROR;
    CHAR           ch          =   0;          // character read
    ULONG           cb          =   0;          // number of bytes read
    ULONG           cbTag       =   0;          // number of bytes in tag
    ULONG           cbData      =   0;          // number of bytes in data
    LONGLONG	   	cbOffsetBack=   0;        	// offset for Seek
	LARGE_INTEGER	sOffsetBack	=	{0};		// offset for Seek
    BOOL            fBlankLine  =   FALSE;      // TRUE if reading a blank line

    DEBUGPRIVATE("HrParseTagAndData()\n");

    // check input parameters
    hr = CHK_HrParseTagAndData(lpStream, pcbRead, 
                               lppTag, lppData);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize output variables.
    *lppTag = 0;
    *lppData = 0;
    *pcbRead = 0;
    
    // Read in one character at a time until we read the
    // whole tag or encounter an error.
    while ( TRUE )
    {
        hr = lpStream->Read(
                &ch,            // buffer to read character into
                sizeof(CHAR),  // number of bytes to read
                &cb);           // number of bytes read

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // See if we have reached the end of the file.
        if ( cb == 0 )
        {
            // Early terminate of tag string.
            // This is an error.
            hr = HR_LOG(EDK_E_END_OF_FILE);

            goto cleanup;
            
        }   // end if end of file

        ASSERTERROR(cb == sizeof(CHAR), "Bad cb");

        // increment # bytes read
        *pcbRead += cb;
        cbTag += cb;    // increment # bytes in the tag

        // Test the character read.
        if ( ch == chColon )
        {
            // have read whole tag.
            // Go on to find the data.
            break;            

        }   // end if colon character

        if ( ch == chNewLine )
        {
            // Read in a new line.
            // We have not found a tag.
            // This is an error if this is not a blank line
            // (i.e. \r\n).
            if ( *pcbRead == 2 )
            {
                // have a blank line.
                // This is not an error.
                fBlankLine = TRUE;

                // Pass back an empty tag and data
                cbTag = sizeof(CHAR);
                cbData = sizeof(CHAR);

                break;
            }

            // Otherwise, have a general error
            hr = HR_LOG(E_FAIL);

            goto cleanup;

        }   // end if new line character
    }   // end while looking for tag

    // Read in one character at a time until we read the
    // whole data string or encounter an error.
    // Don't read any more if we have read in a blank line.
    while ( TRUE && (fBlankLine == FALSE) )
    {
        hr = lpStream->Read(
                &ch,            // buffer to read character into
                sizeof(CHAR),  // number of bytes to read
                &cb);           // number of bytes read

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERTERROR(cb == sizeof(CHAR), "Bad cb");

        // See if we have reached the end of the file.
        if ( cb == 0 )
        {
            // Reached end of file before new line.
            // This is an error.
            hr = HR_LOG(EDK_E_END_OF_FILE);

            goto cleanup;

        }   // end if end of file

        // increment # bytes read
        *pcbRead += cb;

        // Don't count the carriage return character
        if ( ch != chReturn )
        {
            cbData += cb;           // increment number of data bytes
        }

        if ( ch == chNewLine )
        {
            // Found the end of this line.
            // We are done reading in the data.
            break;

        }   // end if new line character
    }   // end while looking for data

    // Allocate memory for the tag
    // (have room for null terminator, since
    // counted the colon which is not part of the tag.
    hr = MAPIAllocateBuffer(
        cbTag,      // # bytes
        (VOID **) lppTag);    // tag buffer pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERT_WRITE_PTR(*lppTag, cbTag, "Bad *lppTag");

    // Initialize tag string
    **lppTag = 0;

    // Allocate memory for the data string.
    // We have room for the null, since we
    // counted the newline, which is not part
    // of the data string.
    hr = MAPIAllocateBuffer(
        cbData,     // # of bytes
        (VOID **) lppData);   // data string buffer pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERT_WRITE_PTR(*lppData, cbData, "Bad *lppData");

    // Initialize data string
    **lppData = 0;

    // Read in tag and data if haven't already determined
    // that they are empty.
    if ( fBlankLine == FALSE )
    {
        // Seek back to where we were in the stream and copy in
        // the tag and data.
        cbOffsetBack = (*pcbRead) * ((LONGLONG) (-1));	// # bytes read

		sOffsetBack.LowPart = LOWLONG(cbOffsetBack);
		sOffsetBack.HighPart = HILONG(cbOffsetBack);

        hr = lpStream->Seek(
            sOffsetBack,        // negative offset
            STREAM_SEEK_CUR,    // from current position
            NULL);              // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Read in the tag
        hr = lpStream->Read(
            *lppTag,    // destination buffer.
            cbTag,      // # bytes to read
            &cb);       // # bytes read

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERTERROR(cb == cbTag, "Bad cb");

        // Null terminate tag by replacing colon with a NULL character.
        *(*lppTag + (cbTag/sizeof(CHAR) - 1)) = 0;

        // Read in the data.
        hr = lpStream->Read(
            *lppData,   // destination buffer.
            cbData,     // # bytes to read
            &cb);       // # bytes read

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERTERROR(cb == cbData, "Bad cb");

        // Null terminate data by replacing carriage
        // return with a NULL character.
        ASSERTERROR(*(*lppData + (cbData/sizeof(CHAR) - 1)) == chReturn, 
            "Bad *lppData last character");

        *(*lppData + (cbData/sizeof(CHAR) - 1)) = 0;

        // Read in the new line character.
        hr = lpStream->Read(
            &ch,            // buffer
            sizeof(CHAR),  // # bytes
            &cb);

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERTERROR(cb == sizeof(CHAR), "Bad cb");
        ASSERTERROR(ch == chNewLine, "Bad ch");

    }   // end if not returning blank tag and data

    // we are done

cleanup:

    if ( FAILED(hr) )
    {
        MAPIFREEBUFFER(*lppTag);
        MAPIFREEBUFFER(*lppData);
    }

    RETURN(hr);

}

//$----HrParseDateTimeString----------------------------------------------------
//
// DESCRIPTION: Parses a date and time string into a file time
//              structure.
//
// INPUT:       lpDateTimeString    --  date and time string
//
// OUTPUT:      pFileTime   --  file time pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParseDateTimeString(
    IN LPSTR lpDateTimeString,     // date and time string
    OUT FILETIME * pFileTime)       // file time pointer
{
    HRESULT     hr                              = NOERROR;    
    CHAR       szTempBuffer[cbDateTimeString]  = {0};// temporary buffer
    LPSTR      lpTemp                          = NULL;    // string pointer
    SYSTEMTIME  sSystemTime                     = {0};     // system time structure
    ULONG       ulValue                         = 0;       // value pointer
    BOOL        fSucceeded                      = FALSE;   // Win32 API return code

    // constants
    const UINT  ncDay       =   5;      // length of day string
    const UINT  ncMonth     =   4;      // length of month string
    const UINT  ncDuoDigit  =   2;      // length of two-digit integer
    const UINT  ncYear      =   4;      // length of year

    DEBUGPRIVATE("HrParseDateTimeString()\n");

    // check input parameters
    hr = CHK_HrParseDateTimeString(lpDateTimeString, pFileTime);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    ZeroMemory(pFileTime, sizeof(FILETIME));      // initialize output

    // If the date/time string is empty, we are done.
    // (This is a valid case.)
    if ( lstrcmp(lpDateTimeString, lpszBlank) == 0 )
    {
        goto cleanup;
    }

    lpTemp = lpDateTimeString;  // intialize string pointer

    // Read in day string
    lstrcpyn(szTempBuffer, lpTemp, ncDay + 1);

    // Find value associated with day of week.
    hr = HrFindStringValue(
            szTempBuffer,       // string
            nDays,              // number values
            rgSortedDay,        // string value pair array
            &ulValue);          // value pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    sSystemTime.wDayOfWeek = (WORD) ulValue;    // set day of week

    lpTemp += ncDay;  // increment string pointer

    // Read in day of month (2 digits)
    lstrcpyn(szTempBuffer, lpTemp, ncDuoDigit + 1);
    sSystemTime.wDay = atoi(szTempBuffer);

    // Check day of month
    if ( (sSystemTime.wDay == 0) || (sSystemTime.wDay > 31) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += ncDuoDigit;   // increment string pointer

    // Next character should be a space
    if ( *lpTemp != chSpace )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp ++;              // skip over space

    // Read in month string
    lstrcpyn(szTempBuffer, lpTemp, ncMonth + 1);

    // Find value associated with month.
    hr = HrFindStringValue(
            szTempBuffer,       // string
            nMonths,            // number values
            rgSortedMonth,      // string value pair array
            &ulValue);          // value pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    sSystemTime.wMonth = (WORD) ulValue;    // set month value

    lpTemp += ncMonth;  // increment string pointer

    // Read in year
    lstrcpyn(szTempBuffer, lpTemp, ncYear + 1);
    sSystemTime.wYear = atoi(szTempBuffer);

    // Check year
    if ( sSystemTime.wYear == 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    lpTemp += ncYear;   // increment string pointer

    // Next character should be a space
    if ( *lpTemp != chSpace )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp++;              // skip over space

    // read in hours
    lstrcpyn(szTempBuffer, lpTemp, ncDuoDigit + 1);
    sSystemTime.wHour = atoi(szTempBuffer);

    // check hour
    if ( sSystemTime.wHour > 23 )
    {
        hr = HR_LOG(E_FAIL);
        
        goto cleanup;
    }

    lpTemp += ncDuoDigit;   // increment pointer
    
    // next character should be a colon
    if ( *lpTemp != chColon )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp++;   // skip over colon

    // read in minutes
    lstrcpyn(szTempBuffer, lpTemp, ncDuoDigit + 1);
    sSystemTime.wMinute = atoi(szTempBuffer);

    // check minutes
    if ( sSystemTime.wMinute > 59 )
    {
        hr = HR_LOG(E_FAIL);
        
        goto cleanup;
    }

    lpTemp += ncDuoDigit;   // increment pointer
    
    // next character should be a colon
    if ( *lpTemp != chColon )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp++;   // skip over colon
    
    // read in seconds
    lstrcpyn(szTempBuffer, lpTemp, ncDuoDigit + 1);
    sSystemTime.wSecond = atoi(szTempBuffer);

    // check seconds
    if ( sSystemTime.wSecond > 59 )
    {
        hr = HR_LOG(E_FAIL);
        
        goto cleanup;
    }

    lpTemp += ncDuoDigit;   // increment pointer
        
    // read in UT string
    lstrcpyn(szTempBuffer, lpTemp, lstrlen(lpszUniversalTime) + 1);
    
    // check universal time string
    if ( lstrcmp(szTempBuffer, lpszUniversalTime) != 0 )
    {
        hr = HR_LOG(E_FAIL);
        
        goto cleanup;
    }

    // Convert the system time structure to a file time
    // structure.
    fSucceeded = SystemTimeToFileTime(
                &sSystemTime,       // system time pointer
                pFileTime);         // file time pointer
                
    if ( fSucceeded == FALSE )
    {
        hr = HR_LOG(E_FAIL);
        
        goto cleanup;
    }

    // we are done
                
cleanup:

    RETURN(hr);

}

//$----HrParsePriorityString----------------------------------------------------
//
// DESCRIPTION: Convert a priority string to its associated
//              integer value.
//
// INPUT:       lpPriority  --  priority string
//             
// OUTPUT:      pulPriority --  pointer to priority value
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParsePriorityString(
    IN LPSTR lpPriority,       // Priority string
    OUT ULONG * pulPriority)    // priority value pointer
{
    HRESULT hr          =   NOERROR;
    UINT    iPriority   =   0;      // index into priority array

    DEBUGPRIVATE("HrParsePriorityString()\n");

    // check input parameters
    hr = CHK_HrParsePriorityString(lpPriority, pulPriority);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pulPriority = 0;   // initialize

    // Find matching priority string
    hr = HrFindStringValue(
                lpPriority,     // string
                nPriorities,    // number of values
                rgPriority,   // string value pair array
                pulPriority);   // value pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // we are done.

cleanup:

    RETURN(hr);

}

//$----HrParseImportanceString----------------------------------------------------
//
// DESCRIPTION: Convert an importance string to its associated
//              integer value.
//
// INPUT:       lpImportance  --  importance string
//             
// OUTPUT:      pulImportance --  pointer to importance value
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParseImportanceString(
    IN LPSTR lpImportance,     // Importance string
    OUT ULONG * pulImportance)  // importance value pointer
{
    HRESULT hr          =   NOERROR;
    UINT    iImportance =   0;      // index into importance array

    DEBUGPRIVATE("HrParseImportanceString()\n");

    // check input parameters
    hr = CHK_HrParseImportanceString(lpImportance, pulImportance);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pulImportance = 0;   // initialize

    // Find matching priority string
    hr = HrFindStringValue(
                lpImportance,       // string
                nImportances,       // number of values
                rgImportance,     // String value pair array
                pulImportance);     // value pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // we are done.

cleanup:

    RETURN(hr);

}

//$--HrParseExternalTraceString-------------------------------------------------
//
// DESCRIPTION: Parse External-Received-By or 
//              External-Attempted-By trace string into
//              its separate components.
//
// INPUT:       lpTraceString   --  External-Received/Attempted-By trace string
//
// OUTPUT:      plAction   --  trace action
//              pCountry  --  country name
//              pADMDName --  ADMD name
//              pPRMDId   --  PRMD identifier
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise
//
// -----------------------------------------------------------------------------
HRESULT HrParseExternalTraceString(
    IN LPSTR lpTraceString,      // trace information string
    OUT LONG * plAction,          // trace action pointer
    OUT CHAR * pCountry,         // country name
    OUT CHAR * pADMDName,        // ADMD name
    OUT CHAR * pPRMDId)          // PRMD identifier
{
    HRESULT hr      =   NOERROR;
    UINT    nChars  =   0;          // length of trace string
    LPSTR  lpTemp  =   NULL;       // temporary string pointer
    INT     nUnread =   0;          // number of characters not read so far.
    UINT    nLength =   0;          // length of current string

    // temporary string buffer
    CHAR   szTempBuffer[ulMaxOutStringLen] =   {0};

    DEBUGPRIVATE("HrParseExternalTraceString()\n");

    // check input parameters
    hr = CHK_HrParseExternalTraceString(
		lpTraceString,
		plAction,
		pCountry,
        pADMDName,
		pPRMDId);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize parameters
    *plAction = 0;
    *pCountry = 0;
    *pADMDName = 0;
    *pPRMDId = 0;

    // If we have no trace data, then we are done.
    // (This is a valid case.)
    if ( lstrcmp(lpTraceString, lpszBlank) == 0 )
    {
        goto cleanup;
    }

    nChars = lstrlen(lpTraceString);    // length of input string
    nUnread = nChars;                   // # characters not read yet
    lpTemp = lpTraceString;             // string pointer

    // Read in PRMD identifier prefix.
    nLength = lstrlen(lpszPRMDId);  // length of PRMD ID prefix

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszPRMDId) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in PRMD identifier.
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // terminating/separating character
            MAX_PRMD_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pPRMDId);     // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine PRMD identifier length
    nLength = lstrlen(pPRMDId);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in ADMD name prefix.
    nLength = lstrlen(lpszADMDName);  // length of ADMD name prefix

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszADMDName) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in ADMD name
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // teminating/separating character
            MAX_ADMD_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pADMDName);       // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine ADMD name length
    nLength = lstrlen(pADMDName);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in country prefix
    nLength = lstrlen(lpszCountry);  // length of country

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszCountry) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in country name
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // teminating/separating character
            MAX_COUNTRY_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pCountry);       // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine country name length
    nLength = lstrlen(pCountry);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in country postfix
    nLength = lstrlen(lpszCountryEnd);  // length of country

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszCountryEnd) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Action is currently pointed to by lpTemp.
    // Convert the action string to an integer value
    hr = HrFindStringValue(
                lpTemp,         // string
                nActions,       // number of values
                rgAction,       // String value pair array
                (ULONG *) plAction);      // value pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // we are done.

cleanup:

    RETURN(hr);

}

//$--HrParseInternalTraceString-------------------------------------------------
//
// DESCRIPTION: Parse Internal-Received-By or 
//              Internal-Attempted-By trace string into
//              its separate components.
//
// INPUT:       lpTraceString   --  Internal-Received/Attempted-By trace string
//
// OUTPUT:      plAction  --  trace action
//              pCountry  --  country name
//              pADMDName --  ADMD name
//              pPRMDId   --  PRMD identifier
//              pMTAName  --  MTA name
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise
//
// -----------------------------------------------------------------------------
HRESULT HrParseInternalTraceString(
    IN LPTSTR lpTraceString,      // trace information string
    OUT LONG * plAction,          // trace action pointer
    OUT CHAR * pCountry,          // country name
    OUT CHAR * pADMDName,         // ADMD name
    OUT CHAR * pPRMDId,           // PRMD identifier
    OUT CHAR * pMTAName)          // MTA name
{
    HRESULT hr      =   NOERROR;
    UINT    nChars  =   0;          // length of trace string
    LPTSTR  lpTemp  =   NULL;       // temporary string pointer
    INT     nUnread =   0;          // number of characters not read so far.
    UINT    nLength =   0;          // length of current string

    // temporary string buffer
    CHAR    szTempBuffer[ulMaxOutStringLen] =   TEXT("");

    DEBUGPRIVATE("HrParseInternalTraceString()\n");

    // check input parameters
    hr = CHK_HrParseInternalTraceString(
		lpTraceString,
		plAction,
		pCountry,
        pADMDName,
		pPRMDId,
		pMTAName);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize parameters
    *plAction = 0;
    *pCountry = 0;
    *pADMDName = 0;
    *pPRMDId = 0;
    *pMTAName = 0;

    // If we have no trace data, then we are done.
    // (This is a valid case.)
    if ( lstrcmp(lpTraceString, lpszBlank) == 0 )
    {
        goto cleanup;
    }

    nChars = lstrlen(lpTraceString);    // length of input string
    nUnread = nChars;                   // # characters not read yet
    lpTemp = lpTraceString;             // string pointer

    // Read in MTA name prefix.
    nLength = lstrlen(lpszMTAName);  // length of MTA name prefix

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszMTAName) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in MTA name
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // terminating/separating character
            MAX_MTA_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pMTAName);       // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine MTA name length
    nLength = lstrlen(pMTAName);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in PRMD identifier prefix.
    nLength = lstrlen(lpszPRMDId);  // length of PRMD ID prefix

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszPRMDId) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in PRMD identifier.
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // terminating/separating character
            MAX_PRMD_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pPRMDId);     // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine PRMD identifier length
    nLength = lstrlen(pPRMDId);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in ADMD name prefix.
    nLength = lstrlen(lpszADMDName);  // length of ADMD name prefix

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszADMDName) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in ADMD name
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // teminating/separating character
            MAX_ADMD_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pADMDName);       // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine ADMD name length
    nLength = lstrlen(pADMDName);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in country prefix
    nLength = lstrlen(lpszCountry);  // length of country

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszCountry) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Read in country name
    hr = HrReadNextString(
            lpTemp,         // input string
            chForwardSlash,    // teminating/separating character
            MAX_COUNTRY_NAME_SIZ * sizeof(CHAR),  // size of output buffer
            pCountry);       // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Determine country name length
    nLength = lstrlen(pCountry);
    nUnread -= nLength;             // update # character unread

    lpTemp += nLength;      // increment string pointer

    // Read in country postfix
    nLength = lstrlen(lpszCountryEnd);  // length of country

    // Check number of characters read.
    nUnread -= nLength;

    if ( nUnread < 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpyn(szTempBuffer, lpTemp, nLength + 1);

    // Check prefix
    if ( lstrcmp(szTempBuffer, lpszCountryEnd) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpTemp += nLength;  // increment pointer

    // Action is currently pointed to by lpTemp.
    // Convert the action string to an integer value
    hr = HrFindStringValue(
                lpTemp,         // string
                nActions,       // number of values
                rgAction,       // String value pair array
                (ULONG *) plAction);      // value pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // we are done.

cleanup:

    RETURN(hr);

}

//$----HrParseAttachmentHeader--------------------------------------------------
//
// DESCRIPTION: Parse attachment header data into its file name
//              and file size components.
//
// INPUT:   lpHeader    --  attachment header data string
//
// OUTPUT:  lppFileName --  attachment file name
//          pcb         --  pointer to # of bytes in attachment
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT HrParseAttachmentHeader(
    IN LPSTR lpHeader,         // attachment header data string
    OUT LPSTR * lppFileName,   // attachment file name
    OUT ULONG * pcb)            // pointer to number of bytes in file name
{
    HRESULT hr      =   NOERROR;
    LPSTR  lpTemp  =   NULL;       // temporary string pointer
    ULONG   cbSize  =   0;          // size of file name buffer

    DEBUGPRIVATE("HrParseAttachmentHeader()\n");

    // check input parameters
    hr = CHK_HrParseAttachmentHeader(lpHeader, lppFileName, pcb);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Allocate file name buffer
    cbSize = ulMaxOutStringLen * sizeof(CHAR); // size of file name buffer
    hr = MAPIAllocateBuffer(cbSize,     // # bytes to allocate
                            (LPVOID *) lppFileName);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERTERROR(!IsBadWritePtr(*lppFileName, sizeof(LPSTR)),
                "Bad *lppFileName");

    ZeroMemory(*lppFileName, cbSize); // intialize file name
    *pcb = 0;             // set number of file bytes to 0.

    lpTemp = lpHeader;    // initialize string pointer

    // Read in the file name.
    hr = HrReadNextString(
            lpTemp,             // input string
            chColon,            // teminating/separating character
            cbSize,             // size of output buffer            
            *lppFileName);      // output buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Skip over file name and colon character
    lpTemp += lstrlen(*lppFileName) + 1;    // increment pointer

    // Read in the file size.
    // File size is currently pointed to by lpTemp.
    *pcb = atol(lpTemp);

    // We are done.

cleanup:

    if ( FAILED(hr) )
    {
        MAPIFREEBUFFER(*lppFileName);
    }

    RETURN(hr);

}

//$----HrEDKDecodeBinaryStreamDataToStream-----------------------------------------------
//
// DESCRIPTION: Read attachment hexadecimal encoding from input
//              stream to attachment.
//
// INPUT:       cb  --  number of bytes in original binary attachment.
//              lpStreamIn  --  input stream pointer
//              lpStreamOut --  Output stream pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------

HRESULT HrEDKDecodeBinaryStreamDataToStream(
    IN LPSTREAM lpStreamIn, // input stream
    IN ULONG cb,            // number of bytes in original binary data
    IN LPSTREAM lpStreamOut)// output stream
{
    HRESULT     hr          =   NOERROR;
    ULONG       iByte       =   0;          // byte index
    UINT        nOutput     =   0;          // integer value to write to attachment
    UINT        nHigh       =   0;          // 16's place
    UINT        nLow        =   0;          // 1's place
    ULONG       cbRead      =   0;          // number of bytes read from stream

    // temporary buffer size
    const UINT  cbTempBuffer    =   nCharsPerEncodedByte * sizeof(CHAR);

    // indices of characters in temporary buffer
    const UINT  iHigh       =   0;          // high-order hex digit
    const UINT  iLow        =   1;          // low-order hex digit
    const UINT  iReturn     =   2;          // return or space character

    // temporary string buffer
    CHAR       szTempBuffer[cbTempBuffer]  =   {0};

    DEBUGPRIVATE("HrEDKDecodeBinaryStreamDataToStream()\n");

    // check input parameters
    hr = CHK_HrEDKDecodeBinaryStreamDataToStream(lpStreamIn, cb, lpStreamOut);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Read and convert one logical byte encoding from the
    // input stream to the output stream.
    for ( iByte = 0; iByte < cb; iByte++ )
    {
        // read in three bytes at a time from the input stream.
        // The first two will be an ASCII representation
        // of a hexadecimal number (e.g. FF).  
        // The third character will either be a space or
        // a return character.
        hr = lpStreamIn->Read(
                    szTempBuffer,       // data buffer
                    cbTempBuffer,       // # bytes in data buffer
                    &cbRead);           // # bytes read.

        if ( FAILED(hr) || (cbRead != cbTempBuffer) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Convert two-character ASCII portion of buffer to
        // a character to write to the output stream.
        nHigh = nAsciiHexToInt(
                szTempBuffer[iHigh]);// high-order hexadecimal character

        nLow = nAsciiHexToInt(        
                szTempBuffer[iLow]);// low-order hexadecimal character

        // compute output digit
        nOutput = (16 * nHigh) + nLow;
                                   
        // Write the byte to the output stream
        hr = lpStreamOut->Write(
                    (CHAR *) &(nOutput),      // data buffer
                    sizeof(CHAR),          // # bytes in buffer
                    NULL);

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Check for the last pair on the line
        if ( szTempBuffer[iReturn] == chReturn)
        {
            // We have just read the last pair on the line,
            // since the third character read in is the 
            // return character.  Since the return character
            // is followed by a newline character, we should read
            // that in now.
            hr = lpStreamIn->Read(
                        szTempBuffer,       // input buffer
                        sizeof(chNewLine),  // # bytes to read in
                        &cbRead);

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

        }   // end if
    }   // end for

    // commit changes to output stream
    // Do we need to do this?
    hr = lpStreamOut->Commit(STGC_DEFAULT);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done.

cleanup:

    RETURN(hr);

}

//$--HrEDKParseSubjectPrefix---------------------------------------------------
//
// DESCRIPTION: Break a subject into its prefix component & its
//              original subject component.  (The prefix is everything
//              up to and including the first colon and the first space
//              after the colon, if any.
//
// INPUT:       pszSubject --  subject text
//
// OUTPUT       ppszPrefix  --  prefix string pointer
//              ppszOrigSub --  original subject pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_OUTOFMEMORY if memory propblems,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT HrEDKParseSubjectPrefix(
            IN LPSTR pszSubject,       // subject text
            OUT LPSTR * ppszPrefix,    // subject prefix
            OUT LPSTR * ppszOrigSub)   // original subject text
{
    HRESULT hr          =   NOERROR;
    ULONG   cbSubject   =   0;          // # bytes in the subject
    CHAR   chCur       =   NULL;       // current character
    BOOL    fPrefix     =   FALSE;      // TRUE if a prefix is found
    LPSTR  pszPrefix   =   NULL;       // pointer into prefix string
    LPSTR  pszOrigSub  =   NULL;       // pointer into original subject
    LPSTR  pszCur      =   NULL;       // pointer into subject text

    DEBUGPRIVATE("HrEDKParseSubjectPrefix()\n");

    // check input parameters
    hr = CHK_HrEDKParseSubjectPrefix(pszSubject, ppszPrefix, 
                                     ppszOrigSub);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // initialize pointer
    *ppszPrefix = NULL;
    *ppszOrigSub = NULL;

    // allocate memory for output variables
    cbSubject = cbStrLen(pszSubject);
    hr = MAPIAllocateBuffer(
                cbSubject,      // # bytes
                (VOID **) ppszPrefix);    // buffer pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERTERROR(ppszPrefix != NULL, "Bad ppszPrefix");
    ASSERTERROR(*ppszPrefix != NULL, "Bad **ppszPrefix");

    hr = MAPIAllocateBuffer(
                cbSubject,      // # bytes
                (VOID **) ppszOrigSub);   // buffer pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERTERROR(ppszOrigSub != NULL, "Bad ppszOrigSub");
    ASSERTERROR(*ppszOrigSub != NULL, "Bad *ppszOrigSub");

    // null-terminate strings.
    **ppszPrefix = 0;
    **ppszOrigSub = 0;

    // look for a colon in the subject text
    pszCur = pszSubject;
    chCur = *pszCur;
    pszPrefix = *ppszPrefix;
    pszOrigSub = *ppszOrigSub;
    while ( chCur != 0 )
    {
        if ( chCur == chColon )
        {
            // there is a prefix
            fPrefix = TRUE;

            // copy colon into candidate prefix
            *pszPrefix = chCur;
            pszPrefix++;        // increment prefix pointer

            // Test next character for a space
            if ( *(pszCur + 1) == chSpace )
            {
                // first space after the colon is part of the prefix
                pszCur++;           // increment current pointer
                *pszPrefix = chSpace;
                pszPrefix++;
            }
        }

        else if ( fPrefix == FALSE )
        {
            // copy character into candidate prefix
            *pszPrefix = chCur;
            pszPrefix++;
        }

        else // Have already found prefix
        {
            // copy character into the original subject
            *pszOrigSub = chCur;
            pszOrigSub++;
        }

        // advance to next character
        pszCur++;
        chCur = *pszCur;

    }   // end while

    // NULL terminate prefix and original subject found
    *pszPrefix = 0;
    *pszOrigSub = 0;

    // handle case where no prefix found
    if ( fPrefix == FALSE )
    {
        // null out prefix
        **ppszPrefix = 0;

        // Copy subject into original subject
        lstrcpy(*ppszOrigSub, pszSubject);

    }   // end if no prefix found
                        
cleanup:

    if ( FAILED(hr) )
    {
        // deallocate memory
        MAPIFREEBUFFER(*ppszOrigSub);
        MAPIFREEBUFFER(*ppszPrefix);
    }

    RETURN(hr);

}

