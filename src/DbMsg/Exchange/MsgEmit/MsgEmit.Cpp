// --msgemit.cpp--------------------------------------------------------------
//
// API entry points for the msgemit static link library.
// Contains helper functions for converting MAPI messages to 
// 822-style headers.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "msgemit.h"
#include "tagnames.h"
#include "msgemit.chk"

// Value to string lookup tables.
// These tables are referrend by offset for a speedy conversion

// Day of week lookup table
static const STRINGVALUEPAIRW rgDayW[nDays]  =
{
    {0, lpszSundayW      },
    {1, lpszMondayW      },
    {2, lpszTuesdayW     },
    {3, lpszWednesdayW   },
    {4, lpszThursdayW    },
    {5, lpszFridayW      },
    {6, lpszSaturdayW    }
};

static const STRINGVALUEPAIRA rgDayA[nDays]  =
{
    {0, lpszSundayA      },
    {1, lpszMondayA      },
    {2, lpszTuesdayA     },
    {3, lpszWednesdayA   },
    {4, lpszThursdayA    },
    {5, lpszFridayA      },
    {6, lpszSaturdayA    }
};

// Month of year lookup table
static const STRINGVALUEPAIRW rgMonthW[nMonths]  =   
{
    {1,  lpszJanuaryW    },
    {2,  lpszFebruaryW   },
    {3,  lpszMarchW      },
    {4,  lpszAprilW      },
    {5,  lpszMayW        },
    {6,  lpszJuneW       },
    {7,  lpszJulyW       },
    {8,  lpszAugustW     },
    {9,  lpszSeptemberW  },
    {10, lpszOctoberW    },
    {11, lpszNovemberW   },
    {12, lpszDecemberW   }
};

static const STRINGVALUEPAIRA rgMonthA[nMonths]  =   
{
    {1,  lpszJanuaryA    },
    {2,  lpszFebruaryA   },
    {3,  lpszMarchA      },
    {4,  lpszAprilA      },
    {5,  lpszMayA        },
    {6,  lpszJuneA       },
    {7,  lpszJulyA       },
    {8,  lpszAugustA     },
    {9,  lpszSeptemberA  },
    {10, lpszOctoberA    },
    {11, lpszNovemberA   },
    {12, lpszDecemberA   }
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
    { IMPORTANCE_LOW,       lpszLowImp      },  // IMPORTANCE_LOW = 0
    { IMPORTANCE_NORMAL,    lpszNormalImp   },  // IMPORTANCE_NORAML = 1
    { IMPORTANCE_HIGH,      lpszHighImp     }   // IMPORTANCE_HIGH = 2
};

// inline constant encoding "macro" used
// by HrEDKEncodeBinaryStreamDataToStream and
// HrEDKEncodeBinaryDataToStream.
static inline VOID EDKEncodeByte(       // RETURNS: VOID
    IN BYTE b,                          // byte to encode
    OUT CHAR szOutBuffer[])            // static output buffer
{
    wsprintf(
        szOutBuffer,            // output buffer
        "%2.2X ",               // format string
        b);                     // byte to encode
}

//$--HrCreateDateTimeString@-------------------------------------------------
//
// DESCRIPTION: Builds a date & time created string for a MAPI message file time
//
// INPUT:       lpFileTime  --  File Time structure pointer
//
// OUTPUT:      lppTimeString   --  Pointer to time string output buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if bad input,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------
HRESULT HrCreateDateTimeStringW(
    IN LPFILETIME lpFileTime,       // message file time pointer
    OUT LPWSTR * lppTimeString)     // pointer to time string buffer
{
    HRESULT     hr              =   NOERROR;    // return code
    SYSTEMTIME  sSystemTime     =   {0};        // system time structure
    WCHAR       szTempString[ulMaxOutStringLen] =   {0};        // for integer to ASCII conversions
    BOOL        fSucceeded      =   FALSE;      // Windows API return code

    DEBUGPUBLIC( "HrCreateDateTimeStringW()");

    // Check input parameters.
    hr = CHK_HrCreateDateTimeStringW(lpFileTime, lppTimeString);
    if ( FAILED(hr) )
        RETURN(hr);

    // Allocate memory for output string.
    hr = MAPIAllocateBuffer(
        ulMaxOutStringLen * sizeof(WCHAR), 
        (PVOID *)lppTimeString);
    if ( FAILED(hr) )
        goto cleanup;

    **lppTimeString = L'\0';    // Set output string to empty string

    // If input time is all zeros, then we are done.  The
    // output string is the empty string.
    if ( (lpFileTime->dwLowDateTime == 0) && 
         (lpFileTime->dwHighDateTime == 0) )
    {
        goto cleanup;
    }

    // Convert FILETIME structure to a SYSTEMTIME structure
    fSucceeded = FileTimeToSystemTime(lpFileTime, &sSystemTime);
    if ( !fSucceeded )
    {
        GetSystemTime(&sSystemTime);
    }

    // Build new date time string.  New date time string format is:
    // 
    // "DAY, DT MON YEAR HH:MM:SS"
    //
    // (Day, date month year hours:minutes:seconds)

    ASSERTERROR(sSystemTime.wDayOfWeek < nDays, "Bad sSystemTime.wDayOfWeek");

    // Set day of week (0 - 6)  (offset is 0)
    lstrcpyW( *lppTimeString, 
            rgDayW[sSystemTime.wDayOfWeek].lpszString);
                    
    // Set date (1-31).  Space pad it to two characters.
    wsprintfW(szTempString, L"%2.2d ", sSystemTime.wDay);
    lstrcatW(*lppTimeString, szTempString);

    ASSERTERROR(sSystemTime.wMonth <= nMonths, "Bad sSystemTime.wMonth");
    ASSERTERROR(sSystemTime.wMonth > 0, "Bad sSystemTime.wMonth");
        
    // Set month (1-12) (e.g. offset is 1)
    lstrcatW(*lppTimeString, 
            rgMonthW[sSystemTime.wMonth - 1].lpszString);

    // Set year, hour, minute and second.
    wsprintfW(szTempString, 
             L"%u %2.2u:%2.2u:%2.2u UT",   // format string
             sSystemTime.wYear,
             sSystemTime.wHour,
             sSystemTime.wMinute,
             sSystemTime.wSecond);
    lstrcatW(*lppTimeString, szTempString);

cleanup:
    if( FAILED(hr))
        MAPIFREEBUFFER(*lppTimeString);

    RETURN(hr);
}

HRESULT HrCreateDateTimeStringA(
    IN LPFILETIME lpFileTime,       // message file time pointer
    OUT LPSTR   * lppTimeString)    // pointer to time string buffer
{
    HRESULT     hr              =   NOERROR;    // return code
    SYSTEMTIME  sSystemTime     =   {0};        // system time structure
    CHAR        szTempString[ulMaxOutStringLen] =   {0};        // for integer to ASCII conversions
    BOOL        fSucceeded      =   FALSE;      // Windows API return code

    DEBUGPUBLIC( "HrCreateDateTimeStringA()");

    // Check input parameters.
    hr = CHK_HrCreateDateTimeStringA(lpFileTime, lppTimeString);
    if ( FAILED(hr) )
        RETURN(hr);

    // Allocate memory for output string.
    hr = MAPIAllocateBuffer(
        ulMaxOutStringLen * sizeof(CHAR), 
        (PVOID *)lppTimeString);
    if (FAILED( hr))
        goto cleanup;

    **lppTimeString = '\0';    // Set output string to empty string

    // If input time is all zeros, then we are done.  The
    // output string is the empty string.
    if ( (lpFileTime->dwLowDateTime == 0) && 
         (lpFileTime->dwHighDateTime == 0) )
    {
        goto cleanup;
    }

    // Convert FILETIME structure to a SYSTEMTIME structure
    fSucceeded = FileTimeToSystemTime(lpFileTime, &sSystemTime);
    if ( !fSucceeded )
    {
        GetSystemTime(&sSystemTime);
    }

    // Build new date time string.  New date time string format is:
    // 
    // "DAY, DT MON YEAR HH:MM:SS"
    //
    // (Day, date month year hours:minutes:seconds)

    ASSERTERROR(sSystemTime.wDayOfWeek < nDays, "Bad sSystemTime.wDayOfWeek");

    // Set day of week (0 - 6)  (offset is 0)
    lstrcpyA( *lppTimeString, 
            rgDayA[sSystemTime.wDayOfWeek].lpszString);
                    
    // Set date (1-31).  Space pad it to two characters.
    wsprintfA(szTempString, "%2.2d ", sSystemTime.wDay);
    lstrcatA(*lppTimeString, szTempString);

    ASSERTERROR(sSystemTime.wMonth <= nMonths, "Bad sSystemTime.wMonth");
    ASSERTERROR(sSystemTime.wMonth > 0, "Bad sSystemTime.wMonth");
        
    // Set month (1-12) (e.g. offset is 1)
    lstrcatA(*lppTimeString, 
            rgMonthA[sSystemTime.wMonth - 1].lpszString);

    // Set year, hour, minute and second.
    wsprintfA(szTempString, 
             "%u %2.2u:%2.2u:%2.2u UT",   // format string
             sSystemTime.wYear,
             sSystemTime.wHour,
             sSystemTime.wMinute,
             sSystemTime.wSecond);
    lstrcatA(*lppTimeString, szTempString);

cleanup:
    if( FAILED(hr))
        MAPIFREEBUFFER(*lppTimeString);

    RETURN(hr);
}

//$--HrCreateImportanceString------------------------------------------------
//
// DESCRIPTION: Creates an message importance string from a MAPI message importance value
//
// INPUT:       ulImportance    --  message's PR_IMPORTANCE value
//              
// OUTPUT:      lppImportance --  Pointer to importance string buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL otherwise.
//
// ---------------------------------------------------------------------------

HRESULT HrCreateImportanceString(                   //  RETURNS:    HRESULT
                    IN ULONG ulImportance,             // message's PR_IMPORTANCE value
                    OUT LPSTR * lppImportance)  // pointer to importance string buffer
{
    HRESULT hr      =   NOERROR;    // return code

    DEBUGPRIVATE("HrCreateImportanceString()");

    // Check input parameters.
    hr = CHK_HrCreateImportanceString(ulImportance, lppImportance);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Allocate memory for output string
    hr = MAPIAllocateBuffer(ulMaxOutStringLen * sizeof(CHAR), 
                            (LPVOID *) lppImportance);

    if ( FAILED(hr) )
    {
        hr = E_OUTOFMEMORY;

        goto cleanup;
    }

    ASSERTERROR(!IsBadWritePtr(*lppImportance, sizeof(LPSTR)),
                "Bad *lppImportance");

    **lppImportance = 0;    // set output string to empty string
    
    // Create importance string (offset is 0)
    lstrcpy(*lppImportance,
            rgImportance[ulImportance].lpszString);

cleanup:

    if ( FAILED(hr) )
    {
        // free the output buffer
        MAPIFREEBUFFER(*lppImportance);
    }

    RETURN(hr);

}   // end HrCreateImportanceString()

//$--HrEmitTagDataLine-------------------------------------------------------
//
// DESCRIPTION: Emits a line constructed from a static tag and dynamic
//              data to the specified stream.  If the data is the empty
//              string, writes the NULL byte (0x00) out to the stream.
//
// INPUT:       lpszTag --  tag portion of line 
//              lpData      --  data portion of line (may be "")
//              lpStream    --  stream to write line to
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,d
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------

HRESULT HrEmitTagDataLine(   
        IN LPCSTR lpszTag,     // static portion of line
        IN LPSTR lpData,       // dynamic portion of line
        IN LPSTREAM lpStream)   // stream to write line to
{
    HRESULT hr              =   NOERROR;
    ULONG   cbWritten       =   0;      // # bytes written

    DEBUGPRIVATE("HrEmitTagDataLine()");

    // Check input parameters
    hr = CHK_HrEmitTagDataLine(lpszTag, lpData, 
                               lpStream);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }
    
    // Write tag to stream.
    hr = lpStream->Write(lpszTag, 
                         cbStrBytes(lpszTag),
                         &cbWritten);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR((cbWritten == cbStrBytes(lpszTag)), "Bad cbWritten");

    // Write colon to stream
    hr = lpStream->Write(lpszColon, 
                         cbStrBytes(lpszColon),
                         &cbWritten);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR((cbWritten == cbStrBytes(lpszColon)), "Bad cbWritten");

    // Write data to stream
    hr = lpStream->Write(
                lpData, 
                cbStrBytes(lpData), 
                &cbWritten);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR((cbWritten == cbStrBytes(lpData)), "Bad cbWritten");

    // Write new line to stream (indicates end of line)
    hr = lpStream->Write(lpszNewLine, 
                         cbStrBytes(lpszNewLine),
                         &cbWritten);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR((cbWritten == cbStrBytes(lpszNewLine)), "Bad cbWritten");

    // we are done.

cleanup:

    RETURN(hr);

}

//$--HrCreatePriorityString-------------------------------------------------------
//
// DESCRIPTION: Creates message priority data string from a MAPI priority value
//
// INPUT:       ulPriority  --  message's PR_PRIORITY value
//
// OUTPUT:      lppPriorityString --  message priority data string pointer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------

HRESULT HrCreatePriorityString(   
        IN ULONG ulPriority,         // message's PR_PRIORITY value
        OUT LPSTR * lppPriorityString)   // message priority data string pointer
{
    HRESULT hr      =   NOERROR;

    DEBUGPRIVATE("HrCreatePriorityString()");

    // check input parameters
    hr = CHK_HrCreatePriorityString(ulPriority, lppPriorityString);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Allocate memory for output string
    hr = MAPIAllocateBuffer(ulMaxOutStringLen * sizeof(CHAR), 
                            (LPVOID *) lppPriorityString);

    if ( FAILED(hr) )
    {
        hr = E_OUTOFMEMORY;

        goto cleanup;
    }

    ASSERTERROR(!IsBadWritePtr(*lppPriorityString, sizeof(LPSTR)),
                "Bad *lppPriorityString");

    **lppPriorityString = 0;    // set output string to empty string

    // Assign appropriate string (offset is -1)
    lstrcpy(*lppPriorityString,
            rgPriority[ulPriority + nPrioOffset].lpszString);

    // we are done

cleanup:

    if ( FAILED(hr) )
    {
        // free output buffer
        MAPIFREEBUFFER(*lppPriorityString);
    }

    RETURN(hr);

}

//$--HrEDKEncodeBinaryStreamDataToStream-----------------------------------------------
//
// DESCRIPTION: Copies binary data from an input stream or
//              specified output stream,
//              encoding each byte as a two-character
//              hexadecimal ASCII representation of the byte.
//              E.g. 255 becomes 'FF'.
//
// INPUT:       
//              lpStreamIn  --  input stream pointer
//              lpStreamOut --  output stream pointer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------
HRESULT HrEDKEncodeBinaryStreamDataToStream(               
    IN LPSTREAM lpStreamIn,     // input stream pointer
    IN LPSTREAM lpStreamOut)    // output stream pointer
{
    HRESULT     hr                  =   NOERROR;    // return code
    ULONG       cbRead              =   0;          // # bytes read
    ULONG       cbWrite             =   0;          // # bytes to be written
    BYTE *      lpByteRead          =   NULL;       // pointer into bytes read buffer
    CHAR *     lpCharWrite         =   NULL;       // pointer into characters to write buffer
    ULONG       iLoopCount          =   0;          // loop counter

    BYTE       szBinaryData[nBytesEncodePerLine] = "";        // byte buffer to read data into
    CHAR       szOutputLine[ulMaxOutStringLen] =   {0};       // Converted ASCII text
    CHAR       szTempBuffer[ulMaxOutStringLen] =   {0};       // temporary buffer

    DEBUGPRIVATE("HrEDKEncodeBinaryStreamDataToStream()");

    // Check input parameters.
    hr = CHK_HrEDKEncodeBinaryStreamDataToStream(
                            lpStreamIn, 
                            lpStreamOut);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Read data from input stream and
    // write encoded version to output stream.
    while ( TRUE )
    {
            // Read 24 bytes of text from input stream.
        hr = lpStreamIn->Read(
                    szBinaryData,   // buffer
                    nBytesEncodePerLine,      // # bytes
                    &cbRead);       // # bytes read

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // See if there are no more bytes to process (last line of
        // file has exactly 24 bytes)
        if ( cbRead == 0 )
        {
            // we are done!
            break;
        }

        // Convert each byte to a two-digit hexadecimal representation
        // of it.
        lpByteRead = szBinaryData;      // initialize pointer into input buffer
        lpCharWrite = szOutputLine;     // initialize pointer into write buffer
        *lpCharWrite = 0;               // null terminate output string
        for ( iLoopCount = 0; iLoopCount < cbRead; 
              iLoopCount++ )
        {
            // Encode byte
            EDKEncodeByte(
                    *lpByteRead,        // byte to encode
                    szTempBuffer);      // output buffer

            // Append encoded by to output string
            lstrcpy(lpCharWrite, szTempBuffer);
            lpCharWrite += lstrlen(szTempBuffer);   // increment write pointer
            lpByteRead++;       // increment read pointer by one byte

        }   // end for

        // replace the last space with a new line character.
        lpCharWrite--;
        lstrcpy(lpCharWrite, lpszNewLine);

        cbWrite = lstrlen(szOutputLine) * sizeof(CHAR);

        // Write the converted attachment text from body stream to the output stream.
        // Decision:  Don't try to recover from a partial write.
        hr = lpStreamOut->Write(
                    szOutputLine,   // buffer
                    cbWrite,        // # bytes
                    NULL);          // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        if ( cbRead != nBytesEncodePerLine )
        {
            break;  // done reading from body stream
        }

        // do next set of input bytes

    }   // end while

    // we are done

cleanup:

    RETURN(hr);

}   // end HrEDKEncodeBinaryStreamDataToStream()

//$--HrCreateExternalTraceString------------------------------------------------
//
// DESCRIPTION: Creates a string from a message's external trace information.
//
// INPUT:       lAction --  trace action
//              lpCountry   --  country
//              lpADMDName  --  ADMD name
//              lpPRMDId    --  PRMD identifier
//          
// OUTPUT:      lppTraceString  --  pointer to trace information string buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems
//                              E_FAIL otherwise,
//
// -----------------------------------------------------------------------------

HRESULT HrCreateExternalTraceString(        
    IN LONG lAction,             // trace action
    IN LPSTR lpCountry,         // country name
    IN LPSTR lpADMDName,        // ADMD name
    IN LPSTR lpPRMDId,          // PRMD identifier    
    OUT LPSTR * lppTraceString)    // trace information string pointer
{
    HRESULT         hr              =   NOERROR;    

    DEBUGPRIVATE("HrCreateExternalTraceString()");

    hr = CHK_HrCreateExternalTraceString(
		lAction,
		lpCountry,
		lpADMDName, 
        lpPRMDId,
		lppTraceString);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Allocate memory for output string.
    hr = MAPIAllocateBuffer(ulMaxOutStringLen * sizeof(CHAR), 
                            (LPVOID *) lppTraceString);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERTERROR(!IsBadWritePtr(*lppTraceString, sizeof(LPSTR)),
                "Bad *lppTraceString");

    **lppTraceString = 0;    // Set output string to empty string

    // Check to see if the PRMD, ADMD and country strings are
    // empty.  If they are, then we are done (The trace string
    // to output is the empty string).
    if ( (*lpCountry == 0) && (*lpADMDName == 0) && (*lpPRMDId == 0) )
    {
        goto cleanup;
    }

    // Format of trace string is:
    // by /P=<Prmd> /A=<Admd> /C=<Country>/;<Action>;
    // NOTE:  The trace arrival date and time is printed out
    // separately.

    // Copy in "/P=" string
    lstrcpy(*lppTraceString, lpszPRMDId);

    // Add the PRMD data
    lstrcat(*lppTraceString, lpPRMDId);

    // Copy in the /A= string
    lstrcat(*lppTraceString, lpszADMDName);

    // Add the ADMD data
    lstrcat(*lppTraceString, lpADMDName);

    // Copy in the /C= string
    lstrcat(*lppTraceString, lpszCountry);

    // Add the country data
    lstrcat(*lppTraceString, lpCountry);

    // Copy in the /; string
    lstrcat(*lppTraceString, lpszCountryEnd);
    
    // Add the action data (offset is -2)
    lstrcat(*lppTraceString,
            rgAction[lAction + nActOffset].lpszString);                

    // We are done.

cleanup:

    if ( FAILED(hr) )
    {
        // free output buffer
        MAPIFREEBUFFER(*lppTraceString);
    }

    RETURN(hr);

}

//$--HrCreateInternalTraceString------------------------------------------------
//
// DESCRIPTION: Creates a string from a message's internal trace information.
//
// INPUT:       lAction		--  trace action
//              lpCountry   --  country
//              lpADMDName  --  ADMD name
//              lpPRMDId    --  PRMD identifier
//              lpMTAName   --  MTA name
//          
// OUTPUT:      lppTraceString  --  pointer to trace information string buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems
//                              E_FAIL otherwise,
//
// -----------------------------------------------------------------------------
HRESULT HrCreateInternalTraceString(        
    IN LONG lAction,             // trace action
    IN LPTSTR lpCountry,         // country name
    IN LPTSTR lpADMDName,        // ADMD name
    IN LPTSTR lpPRMDId,          // PRMD identifier    
	IN LPTSTR lpMTAName,         // MTA name
    OUT LPTSTR * lppTraceString)    // trace information string pointer
{
    HRESULT         hr              =   NOERROR;    

    DEBUGPRIVATE("HrCreateInternalTraceString()");

    hr = CHK_HrCreateInternalTraceString(
		lAction,
		lpCountry,
		lpADMDName, 
        lpPRMDId,
		lpMTAName,
		lppTraceString);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Allocate memory for output string.
    hr = MAPIAllocateBuffer(ulMaxOutStringLen * sizeof(TCHAR), 
                            (LPVOID *) lppTraceString);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERTERROR(!IsBadWritePtr(*lppTraceString, sizeof(LPTSTR)),
                "Bad *lppTraceString");

    **lppTraceString = 0;    // Set output string to empty string

    // Check to see if the PRMD, ADMD and country strings are
    // empty.  If they are, then we are done (The trace string
    // to output is the empty string).
    if ( (*lpCountry == 0) && (*lpADMDName == 0) &&
		 (*lpPRMDId == 0) &&  (*lpMTAName == 0) )
    {
        goto cleanup;
    }

    // Format of trace string is:
    // by /M=<Mta> /P=<Prmd> /A=<Admd> /C=<Country>/;<Action>;
    // NOTE:  The trace arrival date and time is printed out
    // separately.

    // Copy in the /M= string
    lstrcpy(*lppTraceString, lpszMTAName);

    // Add the MTA data
    lstrcat(*lppTraceString, lpMTAName);

    // Copy in "/P=" string
    lstrcat(*lppTraceString, lpszPRMDId);

    // Add the PRMD data
    lstrcat(*lppTraceString, lpPRMDId);

    // Copy in the /A= string
    lstrcat(*lppTraceString, lpszADMDName);

    // Add the ADMD data
    lstrcat(*lppTraceString, lpADMDName);

    // Copy in the /C= string
    lstrcat(*lppTraceString, lpszCountry);

    // Add the country data
    lstrcat(*lppTraceString, lpCountry);

    // Copy in the /; string
    lstrcat(*lppTraceString, lpszCountryEnd);
    
    // Add the action data (offset is -2)
    lstrcat(*lppTraceString,
            rgAction[lAction + nActOffset].lpszString);                

    // We are done.

cleanup:

    if ( FAILED(hr) )
    {
        // free output buffer
        MAPIFREEBUFFER(*lppTraceString);
    }

    RETURN(hr);

}

//$--HrGetRecipientList------------------------------------------
//
// DESCRIPTION: Utility function which retrieves columns 
// desired from a MAPI recipient table.
//
// INPUT:   lpMessage   --  pointer to MAPI message
//          lpPropTags  --  list of columns (properties) to retrieve
//          
// OUTPUT:  lppRows --  pointer to array of rows returned pointer.
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise
//
// -------------------------------------------------------------
HRESULT HrGetRecipientList(           
        IN LPMESSAGE lpMessage,         // MAPI message  pointer
        IN LPSPropTagArray lpPropTags,  // properties (columns) desired
        OUT LPSRowSet * lppRows)        // pointer to rows returned
{
    HRESULT     hr      =   NOERROR;
    LPMAPITABLE lpTable =   NULL;       // MAPI table pointer 
     
    DEBUGPRIVATE("HrGetRecipientList()");

    // check input parameters
    hr = CHK_HrGetRecipientList(lpMessage, lpPropTags, 
                                  lppRows);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Open the report envelope's recipient table
    hr = lpMessage->GetRecipientTable(
        MAPI_DEFERRED_ERRORS | fMapiUnicode,    // flags
        &lpTable);     // MAPI table pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(lpTable),
                "Bad lpTable");

    // Retrieve all of the rows in the table.    
    // (HrQueryAllRows does a SetColumns for us.)
    hr = HrQueryAllRows(lpTable,    // MAPI table pointer
                        lpPropTags, // columns to return
                        NULL,       // restriction pointer
                        NULL,       // order set pointer
                        0,          // maximum # rows (defaults to all)
                        lppRows);   // pointer to property value array pointer

    if ( FAILED(hr) || (hr == MAPI_W_POSITION_CHANGED) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(lppRows != NULL, "Bad lppRows");
    ASSERTERROR(!IsBadReadPtr(*lppRows, sizeof(SRowSet)),
                "Bad *lppRows");

cleanup:

    if ( FAILED(hr) )
    {
        FREEPROWS(*lppRows);
    }

    // Release MAPI objects
    ULRELEASE(lpTable);

    RETURN(hr);
}
