/*																			 */
/*		ISVReg.c - C routine that creates Registry entries					 */
/*		for ISV Application Launching in SMS 1.2							 */
/*																			 */
/*																			 */

#include <windows.h>
#include "isvreg.h"

#if defined(__cplusplus)
extern "C"
{
#endif

int MakeMultiSz(LPTSTR lpBuf, LPCTSTR lpData)
{
	/* fills lpBuf from lpData converting carriage returns to	*/
	/* nulls and eliminating other control characters.			*/
	/* Adds an additional null at the end						*/
	/* to make a valid REG_MULTI_SZ string						*/
	/* returns size in bytes of result including nulls			*/	
	LPTSTR lpB;
	LPCTSTR lpD;

	lpB = lpBuf;
	lpD = lpData;
	while (*lpD  != _T('\0'))
	{
		if (*lpD == _T('\r'))
		{
			*lpB++ = _T('\0');
		}
		else
		if (!_istcntrl(*lpD))
		{
			*lpB++ = *lpD;
		}
		lpD++;
	}
	*lpB++ = _T('\0');	/* add additional null */
	*lpB++ = _T('\0');	/* add additional null */
	/* return size as the differential in bytes */
	return ((LPBYTE)lpB - (LPBYTE)lpBuf);
}

/* 
    UnregisterApplication(HKEY hkParentKey, LPCTSTR lpAppName)

    Deletes the key with the given name after deleting any context
    keys that may be underneath it. This routine is necessary because
    Windows NT 3.51 RegDeleteKey doesn't automatically delete subkeys.
    
    This routine will break if subkeys are added to the context keys.
    It can be removed if RegDeleteKey is eventually brought to up speed
    and so can delete all subkeys like it does in Win95.
*/
long UnregisterApplication(HKEY hkParentKey, LPCTSTR lptAppName)
{
    long    lRet;
    HKEY    hkAppKey;
	TCHAR	tSubKey[MAX_PATH+1];

    /* open the appName key */
	lRet = RegOpenKeyEx( hkParentKey, lptAppName, 0, KEY_ALL_ACCESS, &hkAppKey);
	if (lRet != ERROR_SUCCESS)
    {
        return ERROR_SUCCESS;    /* if not there it's OK */
    }

    /* enumerate the subkeys, deleting each one, assumes they don't have */
    /* subkeys themselves                                                */
    while(TRUE)
    {
        lRet = RegEnumKey(hkAppKey, 0, tSubKey, MAX_PATH+1);
        if (lRet == ERROR_NO_MORE_ITEMS || lRet != ERROR_SUCCESS)
        {
            break;
        }
   		lRet = RegDeleteKey(hkAppKey, tSubKey);
        if (lRet != ERROR_SUCCESS)
        {
            break;
        }
	}

    if (lRet == ERROR_SUCCESS || lRet == ERROR_NO_MORE_ITEMS)
    {
        RegCloseKey(hkAppKey);
        lRet = RegDeleteKey(hkParentKey, lptAppName);
    }

    return lRet;
}

/*
	RegisterSMSTool(BOOL bRemove, LPISVAppReg lpisv)

	This routine makes multiple calls to Registry APIs to create or update	
	information about a single application that wants to be visible in the
	SMS menu and launchable from the SMS Admin UI.
	
	bRemove == TRUE means get rid of named application in the Registry.
	bRemove == FALSE means add or update the application into the Registry.

	The input struct contains all the strings and values to be registered.
	See the ISV Application Launching spec for details about what these
	strings should be. In general the name of the key or value is the
	about the same as the member variable. Because an application can support 
	multiple contexts, the structure takes a pointer to multiple ISVContext
	structs in an array, plus a count.

	Return ERROR_SUCCESS if successful, otherwise the error code from the
	Registry function that failed. Does some preliminary error checking to
    catch some bad input situations.
*/

LONG WINAPI RegisterSMSTool(BOOL bRemove, LPISVAppReg lpisv)
{
	/* This code creates or updates the registry settings for an	*/
	/* SMS ISV application that wants to be launched from the SMS	*/
	/* Administrator UI.											*/
	
	TCHAR	tCurKey[MAX_PATH+1];
	TCHAR	tValueName[MAX_PATH+1];
	TCHAR	tValueData[SmsRegMaxLength];
	LONG	lRet;
	HKEY	hkParentKey;
	HKEY	hkCurKey;
	DWORD	dwKeyDisp;
	int		nSize;
	int		i;

    /* do some preliminary error checking */
    if (_tcslen(lpisv->m_pAppNameKey) <= 0 ||
        _tcslen(lpisv->m_pVendor) <= 0 ||
        (bRemove == FALSE && _tcslen(lpisv->m_pCommand) <= 0) ||
        (bRemove == FALSE && lpisv->m_nNumContexts <= 0) ||
        (lpisv->m_nNumContexts > SmsTotalNumContexts-1) ||
        (bRemove == FALSE && _tcslen(lpisv->m_pAppName) <= 0))
    {
        return ERROR_INVALID_PARAMETER;
    }

    /* get the starting key. This routine should NOT create it */
	_tcscpy(tCurKey, SmsRegRootKey);
	lRet = RegOpenKeyEx
		(
			lpisv->m_bHkeyLocal ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER, 
			tCurKey, 0, KEY_ALL_ACCESS, &hkParentKey
		);
	if (lRet != ERROR_SUCCESS)
    {
        return lRet;
    }

	/* version checking will happen here if and when */

	/* Make subkeys and values */
	/* Vendor key is the passed in name of the vendor */
	_tcscpy(tCurKey, lpisv->m_pVendor);
    lRet = RegCreateKeyEx(hkParentKey, tCurKey, 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkCurKey, &dwKeyDisp);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkParentKey);
        return lRet;
    }

	if (bRemove)
	{
		/* remove the named application */
        lRet = UnregisterApplication(hkCurKey, lpisv->m_pAppNameKey);
        if (lRet == ERROR_SUCCESS)
        {
            // if there are no more subkeys then delete the vendor key
            DWORD dwNumSubkeys = 1;
            RegQueryInfoKey(hkCurKey, NULL, NULL, NULL, &dwNumSubkeys, 
                NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            RegCloseKey(hkCurKey);
            if (dwNumSubkeys == 0)
            {
                lRet = RegDeleteKey(hkParentKey, tCurKey);
            }
        }
        else
        {
            RegCloseKey(hkCurKey);
        }
        RegCloseKey(hkParentKey);
        return lRet;
    }

	/* Make the key for the application itself */
    RegCloseKey(hkParentKey);
	hkParentKey = hkCurKey;
	_tcscpy(tCurKey, lpisv->m_pAppNameKey);
	lRet = RegCreateKeyEx(hkParentKey, tCurKey, 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkCurKey, &dwKeyDisp);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }

	/* values for the named application key */
	/* ApplicationName */
	_tcscpy(tValueName, SmsRegNameValue);
	lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_SZ, 
		lpisv->m_pAppName, _tcslen(lpisv->m_pAppName)+1);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }
	
	/* Order */
	_tcscpy(tValueName, SmsRegOrder);
	lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_DWORD, 
		(const BYTE *)&lpisv->m_dwOrder, sizeof(DWORD));
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }

	/* Command */
	_tcscpy(tValueName, SmsRegCommand);
	lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_SZ, 
		lpisv->m_pCommand, _tcslen(lpisv->m_pCommand)+1);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }

	/* Description */
	_tcscpy(tValueName, SmsRegDescription);
	lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_SZ, 
		lpisv->m_pDescription, _tcslen(lpisv->m_pDescription)+1);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }

	/* Working Directory */
	_tcscpy(tValueName, SmsRegWorkingDir);
	lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_EXPAND_SZ, 
		lpisv->m_pWorkingDir, _tcslen(lpisv->m_pWorkingDir)+1);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }

	/* Run Window */
	_tcscpy(tValueName, SmsRegRunWindow);
	lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_SZ, 
		lpisv->m_pRunWindow, _tcslen(lpisv->m_pRunWindow)+1);
	if (lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hkCurKey);
        RegCloseKey(hkParentKey);
        return lRet;
    }
    
    /* create a subkey for each context */
    RegCloseKey(hkParentKey);
	hkParentKey = hkCurKey;

	for (i = 0; i < lpisv->m_nNumContexts; i++)
	{
		ISVContext isvContext;

		isvContext = lpisv->m_pContexts[i];

		/* create/open context key */
		_tcscpy(tCurKey, isvContext.m_pContextKey);
		lRet = RegCreateKeyEx(hkParentKey, tCurKey, 0, NULL, 
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hkCurKey, &dwKeyDisp);
	    if (lRet != ERROR_SUCCESS)
        {
            RegCloseKey(hkCurKey);
            RegCloseKey(hkParentKey);
            return lRet;
        }
		
		/* values for context, construct REG_MULTI_SZ strings from input */
		/* Enable Rule */
		_tcscpy(tValueName, SmsRegEnableRule);
		nSize = MakeMultiSz(tValueData, isvContext.m_pEnableRule);
		lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_MULTI_SZ, 
			tValueData, nSize);
	    if (lRet != ERROR_SUCCESS)
        {
            RegCloseKey(hkCurKey);
            RegCloseKey(hkParentKey);
            return lRet;
        }

		/* Present Rule */
		_tcscpy(tValueName, SmsRegPresentRule);
		nSize = MakeMultiSz(tValueData, isvContext.m_pPresentRule);
		lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_MULTI_SZ, 
			tValueData, nSize);
	    if (lRet != ERROR_SUCCESS)
        {
            RegCloseKey(hkCurKey);
            RegCloseKey(hkParentKey);
            return lRet;
        }

		/* Arguments */
		_tcscpy(tValueName, SmsRegArguments);
		nSize = MakeMultiSz(tValueData, isvContext.m_pArguments);
		lRet = RegSetValueEx(hkCurKey, tValueName, 0, REG_MULTI_SZ, 
			tValueData, nSize);
	    if (lRet != ERROR_SUCCESS)
        {
            RegCloseKey(hkCurKey);
            RegCloseKey(hkParentKey);
            return lRet;
        }

        RegCloseKey(hkCurKey);      /* close this subkey */
	}

    RegCloseKey(hkParentKey);
	return ERROR_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
