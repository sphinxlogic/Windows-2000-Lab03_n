// --UTL_REG.C------------------------------------------------------------------
//
// Registry key helper functions.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "edk.h"
#include "utl_reg.chk"

//$--HrIdentifyRegistryRootKey------------------------------------------------------
//
//  DESCRIPTION:Checks that a fully qualified key name begins with one of the four
//				predefined NT Registry keys: HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT,
//				HKEY_CURRENT_USER, or HKEY_USERS.  The output from this function
//				can be passed to registry functions like RegOpenKeyEx().
//
//	INPUT:	pszKey - pointer to fully qualified key name
//
//	OUTPUT:	phkKeyHandle - pointer to key handle
//				ppszSubKey - pointer to subkey section of pszKey
//
//	RETURNS:	HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise,
//
//	Notes:   		Successful completion.  hkKey is the Registry key handle,
//					pszSubKey points to the remainder of the subkey string.  Note
//					that it is legitimate for pszSubKey to be NULL, meaning that
//					the user is trying to access values in the root of one of the
//					predefined registry keys.
//
// -----------------------------------------------------------------------------

#define	NOT_A_KEY_HANDLE				(0)

HRESULT HrIdentifyRegistryRootKey(      // RETURNS: HRESULT
                                    IN  char *pszKey,   // pointer to fully qualified key name
									OUT HKEY *phkKeyHandle, // pointer to key handle
									OUT char **ppszSubKey)  // pointer to subkey section
{
    HRESULT     hr  =   NOERROR;
	char *		pszBackslashChar    =   NULL;
	int			nCompLen    =   0;

    DEBUGPUBLIC("HrIdentifyRegistryRootKey()");

    // check input parameters
    hr = CHK_HrIdentifyRegistryRootKey(pszKey, phkKeyHandle, ppszSubKey);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	//
	//	initialise
	//	outputs.
	//	

    *phkKeyHandle = NOT_A_KEY_HANDLE;
	*ppszSubKey = NULL;

	//
	//	Ignore leading backslash character.
	//
	//	e.g. pszKey = "\HKEY_LOCAL_MACHINE\SubKey"
	//

	if (*pszKey == '\\')
		++pszKey;

	//
	//	Search for the next backslash in the key name
	//

	pszBackslashChar = strchr(pszKey,'\\');

	//
	//	The subkey string begins with the first character
	//	after the backslash delimiter.  (In NT 3.5 the function
	//	RegCreateKeyEx() requires that subkey strings *not*
	//	begin with a backslash).
	//

	if (pszBackslashChar == NULL)
		*ppszSubKey = NULL;
	else
	{
		*ppszSubKey = pszBackslashChar + 1;
		
		//
		//	Set pszSubKey to NULL if there are no characters after
		//	the backslash delimiter.
		//
		//	e.g. pszKey = "HKEY_LOCAL_KEY\"
		//

		if (**ppszSubKey == '\0')
			*ppszSubKey = NULL;
	}

	//
	//	Perform comparisons only on characters before
	//	the backslash delimiter.
	//

	if (pszBackslashChar == NULL)
		nCompLen = strlen(pszKey);
	else
		nCompLen = (pszBackslashChar - pszKey);

	//
	//	Exit if there is nothing to compare.
	//

	if (nCompLen <= 0)
	{
        hr = HR_LOG(E_FAIL);

		goto cleanup;
	}

	//
	//	Select on the number of characters to compare,
	//	then check for a string match.
	//

	ASSERTERROR(strlen("HKEY_LOCAL_MACHINE") == 18,"Invalid string length");
	ASSERTERROR(strlen("HKEY_CLASSES_ROOT") == 17,"Invalid string length");
	ASSERTERROR(strlen("HKEY_CURRENT_USER") == 17,"Invalid string length");
	ASSERTERROR(strlen("HKEY_USERS") == 10,"Invalid string length");

	switch(nCompLen)
	{
		case 18 :

			if (strncmp(pszKey,"HKEY_LOCAL_MACHINE",nCompLen) == 0)
				*phkKeyHandle = HKEY_LOCAL_MACHINE;
			else
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

			break;

		case 17 :

			if (strncmp(pszKey,"HKEY_CLASSES_ROOT",nCompLen) == 0)
				*phkKeyHandle = HKEY_CLASSES_ROOT;
			else
			if (strncmp(pszKey,"HKEY_CURRENT_USER",nCompLen) == 0)
				*phkKeyHandle = HKEY_CURRENT_USER;
			else
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
			}

			break;

		case 10 :

			if (strncmp(pszKey,"HKEY_USERS",nCompLen) == 0)
				*phkKeyHandle = HKEY_USERS;
			else
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

			break;

		default :

            hr = HR_LOG(E_FAIL);

            goto cleanup;
	}

cleanup:

	if ( FAILED(hr) && (hr != E_INVALIDARG) )
	{
		*phkKeyHandle = NOT_A_KEY_HANDLE;
		*ppszSubKey = NULL;
	}
	
    RETURN(hr);

}

//$--_HrReadRegistrySZ--------------------------------------------------------
//
//  DESCRIPTION :Read a string from the registry.
//
//  INPUT:  hRegistryKey    --  registry key to read value from
//          lpszValueName   --  name of value to read
//
//  INPUT OUTPUT:   lpcbBufferSize  --  size of buffer for value and size of value
//
//  OUTPUT: lpszBuffer      -- buffer to read value into
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          EDK_E_NOT_FOUND if value does not exist
//                          E_FAIL if failure due to other error
//
// -----------------------------------------------------------------------------

HRESULT _HrReadRegistrySZ(			// RETURNS: HRESULT
	IN HKEY hRegistryKey,				// registry key to read value from
	IN LPSTR lpszValueName,			// name of value to read
	OUT LPSTR lpszBuffer,				// buffer to read value into
	IN OUT DWORD *lpcbBufferSize)		// size of buffer to read value into
{
    HRESULT     hr          = NOERROR;
	DWORD		dwStatus	= ERROR_SUCCESS;
	DWORD		dwType		= 0;

	DEBUGPUBLIC("_HrReadRegistrySZ()");

    // Check input parameters
    hr = CHK__HrReadRegistrySZ(hRegistryKey, lpszValueName, lpszBuffer, lpcbBufferSize);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	dwStatus = RegQueryValueEx(
		hRegistryKey, 
		lpszValueName, 
		NULL, 
		&dwType, 
		(LPBYTE)lpszBuffer, 
		lpcbBufferSize);

	if (dwStatus != ERROR_SUCCESS || dwType != REG_SZ)
	{
        if(dwStatus != ERROR_SUCCESS)
        {
            hr = HR_LOG(HRESULT_FROM_WIN32(dwStatus));
        }
        else
        {
            hr = HR_LOG(E_FAIL);
        }
		
        goto cleanup;
	}

cleanup:

    RETURN(hr);

}

//$--_HrReadRegistryDWORD-----------------------------------------------------
//
//  DESCRIPTION: Read a DWORD integer from the registry.
//
//  INPUT:  hRegistryKey    --  registry key to read value from
//          lpszValueName   --  name of value to read
//
//  OUTPUT: lpdwBuffer  --  DWORD buffer to read value into
//
//  RETURNS:    HRESULT --  NOERROR is success,
//                          E_INVALIDARG if bad input
//                          EDK_E_NOT_FOUND if value does not exist
//                          E_FAIL if failure due to other error
//
// -----------------------------------------------------------------------------
HRESULT _HrReadRegistryDWORD(			// RETURNS: HRESULT
	IN HKEY hRegistryKey,				// registry key to read value from
	IN LPSTR lpszValueName,			// name of value to read
	OUT LPDWORD lpdwBuffer)				// address of DWORD to read value into
{
    HRESULT     hr              = NOERROR;
	DWORD		dwStatus		= ERROR_SUCCESS;
	DWORD		dwType			= 0;
	DWORD		cbBufferSize	= sizeof(DWORD);

	DEBUGPUBLIC("_HrReadRegistryDWORD()");

    // Check input parameters.
    hr = CHK__HrReadRegistryDWORD(hRegistryKey, lpszValueName, lpdwBuffer);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	dwStatus = RegQueryValueEx(
		hRegistryKey, 
		lpszValueName, 
		NULL, 
		&dwType, 
		(LPBYTE)lpdwBuffer, 
		&cbBufferSize);

	if (dwStatus != ERROR_SUCCESS || dwType != REG_DWORD)
	{
        if(dwStatus != ERROR_SUCCESS)
        {
            hr = HR_LOG(HRESULT_FROM_WIN32(dwStatus));
        }
        else
        {
            hr = HR_LOG(E_FAIL);
        }
		
        goto cleanup;
	}

cleanup:    

    RETURN(hr);

}

//$--_HrWriteRegistrySZ-------------------------------------------------------
//
//  DESCRIPTION: Write a string to the registry.
//
//  INPUT:  hRegistryKey    --  registry key to write value to
//          lpszValueName   --  name of value to write
//          lpszValue       --  string value to write
//
//  RETURNS:    HRESULT --  NOERROR if success
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
HRESULT _HrWriteRegistrySZ(			// RETURNS: HRESULT
	IN HKEY hRegistryKey,				// registry key to write value to
	IN LPSTR lpszValueName,			// name of value to write
	IN LPCSTR lpszValue)				// string value to write
{
    HRESULT     hr          = NOERROR;
	DWORD		dwStatus	= ERROR_SUCCESS;

	DEBUGPUBLIC("_HrWriteRegistrySZ()");

    // Check input parameters
    hr = CHK__HrWriteRegistrySZ(hRegistryKey, lpszValueName, lpszValue);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	dwStatus = RegSetValueEx(
		hRegistryKey, 
		lpszValueName, 
		0L, 
		REG_SZ, 
		(LPBYTE)lpszValue, 
		(lstrlen(lpszValue) + 1) * sizeof(CHAR));

	if (dwStatus != ERROR_SUCCESS)
	{
        hr = HR_LOG(HRESULT_FROM_WIN32(dwStatus));

        goto cleanup;
	}

cleanup:

    RETURN(hr);

}

//$--_HrWriteRegistryDWORD----------------------------------------------------
//
//  DESCRIPTION: Write a DWORD integer to the registry.
//
//  INPUT:  hRegistryKey    --  registry key to write value to
//          lpszValueName   --  name of value to write
//          dwValue         --  value to write
//
//  RETURNS:    HRESULT --  NOERROR is success,
//              E_INVALIDARG if bad input
//              E_FAIL otherwise
//
// -----------------------------------------------------------------------------

HRESULT _HrWriteRegistryDWORD(		// RETURNS: HRESULT
	IN HKEY hRegistryKey,				// registry key to write value to
	IN LPSTR lpszValueName,			// name of value to write
	IN DWORD dwValue)					// DWORD value to write
{
    HRESULT     hr          = NOERROR;
	DWORD		dwStatus	= ERROR_SUCCESS;

	DEBUGPUBLIC("_HrWriteRegistryDWORD()");

    // Check input parameters
    hr = CHK__HrWriteRegistryDWORD(hRegistryKey, lpszValueName, dwValue);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	dwStatus = RegSetValueEx(
		hRegistryKey, 
		lpszValueName, 
		0L, 
		REG_DWORD, 
		(LPBYTE)&dwValue, 
		sizeof(dwValue));

	if (dwStatus != ERROR_SUCCESS)
	{
        hr = HR_LOG(HRESULT_FROM_WIN32(dwStatus));

        goto cleanup;
	}

cleanup:

    RETURN(hr);

}
