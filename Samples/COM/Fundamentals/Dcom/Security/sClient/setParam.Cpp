/*
Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


DWORD dwActivationAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
DWORD dwActivationImp = RPC_C_IMP_LEVEL_IMPERSONATE;
DWORD dwProcessAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
DWORD dwProcessImp = RPC_C_IMP_LEVEL_IMPERSONATE;
DWORD dwProxyAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
DWORD dwProxyImp = RPC_C_IMP_LEVEL_IMPERSONATE;
TCHAR szServerFile[100] = TEXT("server.txt");
TCHAR szActivationDomain[100]=TEXT("");
TCHAR szActivationUser[100]=TEXT("");
TCHAR szActivationPassword[100]=TEXT("");
TCHAR szProxyDomain[100]=TEXT("");
TCHAR szProxyUser[100]=TEXT("");
TCHAR szProxyPassword[100]=TEXT("");
TCHAR szAccessPermissions[500]=TEXT("");
DWORD dwActivationCaps = EOAC_NONE;
DWORD dwProcessCaps = EOAC_NONE;
DWORD dwProxyCaps = EOAC_NONE;

void Message(LPTSTR szPrefix, HRESULT hr);


BOOL SetSecurityParams ()
{
	FILE *fp;
	TCHAR szBuf[500];
	TCHAR *token;
	
	lstrcpy(szServerFile,TEXT(""));
	lstrcpy(szProxyDomain,TEXT(""));
	lstrcpy(szProxyUser,TEXT(""));
	lstrcpy(szProxyPassword,TEXT(""));
	dwProxyCaps = EOAC_NONE;
	dwProxyAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
	dwProxyImp = RPC_C_IMP_LEVEL_IMPERSONATE;

	fp = _tfopen(TEXT("sclient.cfg"), TEXT("r"));
	if (!fp)
	{
		Message(TEXT("fopen error on sclient.cfg"), S_OK);
		return FALSE;
	}
	while(_fgetts(szBuf, sizeof(szBuf), fp))
	{
		if (_tcsstr(szBuf, TEXT("//")))
			continue;
		szBuf[lstrlen(szBuf)-1] = 0;
		if (_tcsstr(szBuf, TEXT("-file:")))
			lstrcpy(szServerFile, szBuf+lstrlen(TEXT("-file:")));
		else if (_tcsstr(szBuf, TEXT("-act:")))
		{
			token = _tcstok(szBuf+lstrlen(TEXT("-act:")), TEXT(","));
			if (token)
			{
				if (!lstrcmpi(token, TEXT("none")))
					dwActivationAuthn = (DWORD)-1; // do not use COAUTHINFO
				else if (!lstrcmpi(token, TEXT("sn")))
					dwActivationAuthn = RPC_C_AUTHN_LEVEL_NONE;
				else if (!lstrcmpi(token, TEXT("sc")))
					dwActivationAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
				else if (!lstrcmpi(token, TEXT("sl")))
					dwActivationAuthn = RPC_C_AUTHN_LEVEL_CALL;
				else if (!lstrcmpi(token, TEXT("sp")))
					dwActivationAuthn = RPC_C_AUTHN_LEVEL_PKT;
				else if (!lstrcmpi(token, TEXT("si")))
					dwActivationAuthn = RPC_C_AUTHN_LEVEL_PKT_INTEGRITY;
				else if (!lstrcmpi(token, TEXT("se")))
					dwActivationAuthn = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;
				else
					Message(TEXT("Incorrect -act:<authlevel>"), S_OK);
			}
			token = _tcstok(NULL, TEXT(","));
			if (token)
			{
				if (!lstrcmpi(token, TEXT("an")))
					dwActivationImp = RPC_C_IMP_LEVEL_ANONYMOUS;
				else if (!lstrcmpi(token, TEXT("id")))
					dwActivationImp = RPC_C_IMP_LEVEL_IDENTIFY;
				else if (!lstrcmpi(token, TEXT("im")))
					dwActivationImp = RPC_C_IMP_LEVEL_IMPERSONATE;
				else if (!lstrcmpi(token, TEXT("dl")))
					dwActivationImp = RPC_C_IMP_LEVEL_DELEGATE;
				else
					Message(TEXT("Incorrect -act:<implevel>"), S_OK);
			}
			token = _tcstok(NULL, TEXT(","));
			if (token)
			{
				lstrcpy(szActivationDomain, token);
				token = _tcstok(NULL, TEXT(","));
				if (token)
				{
					lstrcpy(szActivationUser, token);
					token = _tcstok(NULL, TEXT(","));
					if (token)
					{
						lstrcpy(szActivationPassword, token);
					}
				}
			}

		}
		else if (_tcsstr(szBuf, TEXT("-procaps:")))
		{
			token = _tcstok(szBuf+lstrlen(TEXT("-procaps:")), TEXT(","));
			while (token)
			{
				if (!lstrcmpi(token, TEXT("mutual")))
					dwProcessCaps |= EOAC_MUTUAL_AUTH;
				else if (!lstrcmpi(token, TEXT("secure")))
					dwProcessCaps |= EOAC_SECURE_REFS;
				else if (!lstrcmpi(token, TEXT("scloak")))
					dwProcessCaps |= EOAC_STATIC_CLOAKING;
				else if (!lstrcmpi(token, TEXT("dcloak")))
					dwProcessCaps |= EOAC_DYNAMIC_CLOAKING;
				token = _tcstok(NULL, TEXT(","));
			}
		}
		else if (_tcsstr(szBuf, TEXT("-prxcaps:")))
		{
			token = _tcstok(szBuf+lstrlen(TEXT("-prxcaps:")), TEXT(","));
			while (token)
			{
				// ignored for NTLM SSP for proxies
				if (!lstrcmpi(token, TEXT("mutual")))
					dwProxyCaps |= EOAC_MUTUAL_AUTH;
				else if (!lstrcmpi(token, TEXT("scloak")))
					dwProcessCaps |= EOAC_STATIC_CLOAKING;
				else if (!lstrcmpi(token, TEXT("dcloak")))
					dwProcessCaps |= EOAC_DYNAMIC_CLOAKING;
				token = _tcstok(NULL, TEXT(","));
			}
		}
		else if (_tcsstr(szBuf, TEXT("-pro:")))
		{
			token = _tcstok(szBuf+lstrlen(TEXT("-pro:")), TEXT(","));
			if (token)
			{
				if (!lstrcmpi(token, TEXT("none")))
					dwProcessAuthn = (DWORD)-1; // do not call CIS
				else if (!lstrcmpi(token, TEXT("sn")))
					dwProcessAuthn = RPC_C_AUTHN_LEVEL_NONE;
				else if (!lstrcmpi(token, TEXT("sc")))
					dwProcessAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
				else if (!lstrcmpi(token, TEXT("sl")))
					dwProcessAuthn = RPC_C_AUTHN_LEVEL_CALL;
				else if (!lstrcmpi(token, TEXT("sp")))
					dwProcessAuthn = RPC_C_AUTHN_LEVEL_PKT;
				else if (!lstrcmpi(token, TEXT("si")))
					dwProcessAuthn = RPC_C_AUTHN_LEVEL_PKT_INTEGRITY;
				else if (!lstrcmpi(token, TEXT("se")))
					dwProcessAuthn = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;
				else
					Message(TEXT("Incorrect -pro:<authlevel>"), S_OK);
			}
			token = _tcstok(NULL, TEXT(","));
			if (token)
			{
				if (!lstrcmpi(token, TEXT("an")))
					dwProcessImp = RPC_C_IMP_LEVEL_ANONYMOUS;
				else if (!lstrcmpi(token, TEXT("id")))
					dwProcessImp = RPC_C_IMP_LEVEL_IDENTIFY;
				else if (!lstrcmpi(token, TEXT("im")))
					dwProcessImp = RPC_C_IMP_LEVEL_IMPERSONATE;
				else if (!lstrcmpi(token, TEXT("dl")))
					dwProcessImp = RPC_C_IMP_LEVEL_DELEGATE;
				else
					Message(TEXT("Incorrect -pro:<implevel>"), S_OK);
			}
			token = _tcstok(NULL, TEXT(","));
			while (token)
			{
				lstrcat(szAccessPermissions, token);
				lstrcat(szAccessPermissions,TEXT(","));
				token = _tcstok(NULL, TEXT(","));
			}	
		}
		else if (_tcsstr(szBuf, TEXT("-prx:")))
		{
			token = _tcstok(szBuf+lstrlen(TEXT("-prx:")), TEXT(","));
			if (token)
			{
				if (!lstrcmpi(token, TEXT("none")))
					dwProxyAuthn = (DWORD)-1; // do not call CSPB
				else if (!lstrcmpi(token, TEXT("sn")))
					dwProxyAuthn = RPC_C_AUTHN_LEVEL_NONE;
				else if (!lstrcmpi(token, TEXT("sc")))
					dwProxyAuthn = RPC_C_AUTHN_LEVEL_CONNECT;
				else if (!lstrcmpi(token, TEXT("sl")))
					dwProxyAuthn = RPC_C_AUTHN_LEVEL_CALL;
				else if (!lstrcmpi(token, TEXT("sp")))
					dwProxyAuthn = RPC_C_AUTHN_LEVEL_PKT;
				else if (!lstrcmpi(token, TEXT("si")))
					dwProxyAuthn = RPC_C_AUTHN_LEVEL_PKT_INTEGRITY;
				else if (!lstrcmpi(token, TEXT("se")))
					dwProxyAuthn = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;
				else
					Message(TEXT("Incorrect -prx:<authlevel>"), S_OK);
			}
			token = _tcstok(NULL, TEXT(","));
			if (token)
			{
				if (!lstrcmpi(token, TEXT("an")))
					dwProxyImp = RPC_C_IMP_LEVEL_ANONYMOUS;
				else if (!lstrcmpi(token, TEXT("id")))
					dwProxyImp = RPC_C_IMP_LEVEL_IDENTIFY;
				else if (!lstrcmpi(token, TEXT("im")))
					dwProxyImp = RPC_C_IMP_LEVEL_IMPERSONATE;
				else if (!lstrcmpi(token, TEXT("dl")))
					dwProxyImp = RPC_C_IMP_LEVEL_DELEGATE;
				else
					Message(TEXT("Incorrect -prx:<implevel>"), S_OK);
			}
			token = _tcstok(NULL, TEXT(","));
			if (token)
			{
				lstrcpy(szProxyDomain, token);
				token = _tcstok(NULL, TEXT(","));
				if (token)
				{
					lstrcpy(szProxyUser, token);
					token = _tcstok(NULL, TEXT(","));
					if (token)
					{
						lstrcpy(szProxyPassword, token);
					}
				}
			}
		}

	}
	fclose(fp);
	return TRUE;
}