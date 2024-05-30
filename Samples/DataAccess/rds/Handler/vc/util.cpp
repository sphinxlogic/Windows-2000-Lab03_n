//-----------------------------------------------------------------------------
//
// File:		util.cpp
//
// Copyright:	Copyright (c) 1997-1999 Microsoft Corporation
//
// Contents:	Implementation of class CUtil
//
// Comments:
//
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "util.h"

static WCHAR const s_wszDatasource[] = L"Data Source";
static int const s_cDatasource = sizeof(s_wszDatasource) / sizeof(WCHAR) - 1;


//
// The user of this class must use try/catch
// on the constructor and member functions.
//
static void ThrowHR(HRESULT hr)
{
	throw hr;
}


//
// Constructor
//
CUtil::CUtil()
{
	m_bstrIniFile = L"msdfmap.ini";
	m_lAccess = UTIL_NOACCESS;

	m_cLastIniString = 4096;
	m_pszLastIniString = new CHAR [m_cLastIniString];

	ULONG namelen = 0;
	GetUserNameA("", &namelen);
	if (namelen == 0)
		namelen = 256;
	m_pszUsername = new CHAR [namelen + 1];
	if (!m_pszUsername)
		ThrowHR(E_OUTOFMEMORY);
    if (!GetUserNameA(m_pszUsername, &namelen))
		m_pszUsername[0] = '\0';

	if (!m_pszLastIniString)
		ThrowHR(E_OUTOFMEMORY);
}


//
// Destructor
//
CUtil::~CUtil()
{
	delete [] m_pszLastIniString;
	delete [] m_pszUsername;
}


//
// Raise a Win32 error
//
void CUtil::RaiseError(HRESULT hr)
{
	CHAR * ErrFileName = GetIniString("logs", "err");

	if (ErrFileName[0])
	{
		FILE * fp = fopen(ErrFileName, "at");
		if (fp)
		{
			time_t t;
			struct tm *ptm;

			time(&t);
			ptm = localtime(&t);
			fprintf(fp, "user=%s, hr=%lX, datetime=%s", GetUsername(), hr, asctime(ptm));
			fclose(fp);
		}
	}
	ThrowHR(hr);
}


//
// Set the name of the INI file to open.
// (the default name is set in the constructor)
//
void CUtil::SetIniFile(BSTR args)
{
	if (!args || !wcslen(args))
		return;

	if (wcschr(args, L':') || wcschr(args, L'\\'))
	{
		RaiseError(HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED));  //Handler argument can't specify a path.
		return;
	}

	m_bstrIniFile = args;
}


//
// Search for a character, but ignore those inside quoted strings.
//
static WCHAR * FindChr(WCHAR * str, WCHAR chr)
{
	WCHAR *pChr;
	WCHAR *pQuote;

	if (!str)
		return NULL;
	while(1)
	{
		// Outside of quotes
		pChr = wcschr(str, chr);
		if (!pChr)
			return NULL;
		pQuote = wcschr(str, L'\'');
		if (!pQuote)
			return pChr;
		if (pChr < pQuote)
			return pChr;

		// We are now inside a quoted string.
		str = pQuote + 1;
		while(1)
		{
			// Find the end of the quoted string.
			pQuote = wcschr(str, L'\'');
			if (!pQuote)
				return NULL;
			if (pQuote[1] != L'\'')
				break;

			// Skip double quotes
			str = pQuote + 2;
		}
		str = pQuote + 1;
	}
}


//
// SubstituteParameters(RetVal,pszStr,params) replaces each "?" in "pszStr"
// with the corresponding parameter in the comma separated list in "params".
// (NOTE: this function is destructive to the "params" buffer!)
//
void CUtil::SubstituteParameters(CUtilString &RetVal, CHAR * pszStr, WCHAR * params)
{
	assert(pszStr);
	assert(params);
	WCHAR *pStrNext;
	WCHAR *pArgNext;
	CUtilString bstrStr(pszStr, true);
	WCHAR *str;

	// Initialize return value.
	RetVal = L"";

	// Check and initialize input arguments
	str = bstrStr;
	if (!str)
		return;

	while(1)
	{
		// Search for a parameter in the input string.
		pStrNext = FindChr(str, L'?');
		if (!pStrNext)
			break;

		// Append the stuff before the parameter to the output string.
		*pStrNext++ = L'\0';
		RetVal += str;

		// Search for a parameter in the parameter list.
		pArgNext = FindChr(params, L',');
		if (pArgNext)
			*pArgNext++ = L'\0';
		else
			pArgNext = params;

		// Append the parameter to the output string.
		RetVal += params;

		// Next interation.
		str = pStrNext;
		params = pArgNext;
	}

	// Append the last stuff to the output string.
	RetVal += str;
}


//
// GetIniString(section,key)
// returns the value of the "key" in the "section" of the INI file.
//
CHAR * CUtil::GetIniString(CHAR * section, CHAR * key)
{
	assert(section);
	assert(key);
	ULONG rc;

	while(1)
	{
		if (!m_pszLastIniString)
			ThrowHR(E_OUTOFMEMORY);

		// Get the value for the key in the section.
		rc = GetPrivateProfileStringA(section, key, "",
			m_pszLastIniString, m_cLastIniString, m_bstrIniFile);
		if (rc == 0)
			m_pszLastIniString[0] = '\0';
		if (rc < (m_cLastIniString-1))
			break;

		// Make the buffer twice as big and try again.
		m_cLastIniString *= 2;
		delete [] m_pszLastIniString;
		m_pszLastIniString = new CHAR [m_cLastIniString];
	}
	return m_pszLastIniString;
}


//
// SetSql(bstrStr) will set the sql string.  It will parse "bstrStr" for
// "func(args)" then it look for "func" in the INI file.  If "bstrStr" does
// not contain a function, then it searches for the whole string in the INI
// file.  If it does not find it in the INI file then it will retrieve the
// default sql string from the INI file.  If the "func" is found in the INI
// file and there are "args" then the SubstituteParameters function is called.
//
void CUtil::SetSql(BSTR bstrStr)
{
	WCHAR *pLP, *pRP, *pFunc, *pArgs;
	CHAR *pTemp;
	WCHAR *str = bstrStr ? bstrStr : L"";
	CUtilString temp(str, true);  // Make a copy of the string, so we are not destructive.

	// Parse "func(args)" into "func" and "args".
	pFunc = temp;
	pLP = wcschr(pFunc, L'(');
	if (pLP)
	{
		*pLP++ = L'\0';
		pArgs = pLP;
		pRP = wcsrchr(pLP, L')');
		if (pRP)
			*pRP = L'\0';
	}
	else
		pArgs = L"";

	// Figure out the section name and get the override for the sql string, if any.
	m_bstrSqlSection = L"sql ";
	m_bstrSqlSection += pFunc;
	pTemp = GetIniString(m_bstrSqlSection, "Sql");
	if (*pTemp)
	{
		SubstituteParameters(m_bstrSql, pTemp, pArgs);
	}
	else
	{
		m_bstrSqlSection = L"sql default";
		pTemp = GetIniString(m_bstrSqlSection, "Sql");
		if (*pTemp)
			m_bstrSql = pTemp;
		else
			m_bstrSql = str;
	}
}


//
// SetSection is an internal function used to set the INI file section names.
//
void CUtil::SetSection(void)
{
	CHAR *pTemp;

	m_bstrSectionName = m_bstrDatasource;
	m_bstrSectionConn = L"connect ";
	m_bstrSectionConn += m_bstrSectionName;
	pTemp = GetIniString(m_bstrSectionConn, "Access");
	if (!*pTemp)
	{
		m_bstrSectionName = L"default";
		m_bstrSectionConn = L"connect default";
	}
	m_bstrSectionUserlist = L"userlist ";
	m_bstrSectionUserlist += m_bstrSectionName;
}


//
// DecodeAccess will decode an "Access" string from the INI file.
//
static long DecodeAccess(CHAR *pszAccess)
{
	long lAccess = UTIL_NOACCESS;

	if (pszAccess && *pszAccess)
	{
		if (!_stricmp(pszAccess, "ReadOnly"))
			lAccess = UTIL_READONLY;
		if (!_stricmp(pszAccess, "ReadWrite"))
			lAccess = UTIL_READWRITE;
	}

	return lAccess;
}


void CUtil::SetConn(BSTR conn)
{
	CHAR *pTemp;
	WCHAR *pConn = conn ? conn : L"";

	// Parse the connection string for the value of "Data Source".
	ParseConn(pConn);

	// Figure out the section names.
	SetSection();

	// Get the override for the connection string, if any.
	pTemp = GetIniString(m_bstrSectionConn, "Connect");
	if (*pTemp)
		m_bstrConn = pTemp;
	else
		m_bstrConn = pConn;

	// Get the connect access.
	pTemp = GetIniString(m_bstrSectionConn, "Access");
	m_lAccess = DecodeAccess(pTemp);

	if (m_pszUsername[0])
	{
		pTemp = GetIniString(m_bstrSectionUserlist, m_pszUsername);
		if (*pTemp)
			m_lAccess = DecodeAccess(pTemp);
	}
}


//
// FindDatasource will search for the "Data Source" name/value pair
// in a connection string.  It will either return a pointer to the value
// or return NULL if not found.
//
static WCHAR * FindDatasource(WCHAR *pwszConn)
{
	WCHAR *pwszCurr;
	WCHAR *pwszEq;

	if (!pwszConn)
		return NULL;

	pwszCurr = pwszConn;
	while(1)
	{
		// Search for next name/value pair.
		pwszEq = wcschr(pwszCurr, L'=');
		if (!pwszEq)
			break;

		// Check the length of the name first.
		if ((pwszEq-pwszCurr) == s_cDatasource)
		{
			// Now check the name.
			// NOTE: _wcsnicmp does not work in general, but works for ASCII constants.
			if (!_wcsnicmp(pwszCurr, s_wszDatasource, s_cDatasource))
				return pwszEq+1;
		}

		// Move on to the next name/value pair.
		pwszCurr = wcschr(pwszEq, L';');
		if (!pwszCurr)
			break;
		pwszCurr++;
	}
	return NULL;
}


//
// ParseConn will parse a connection string for the value of the
// "Data Source" name/value pair.  If it is not found, it will be "default".
//
void CUtil::ParseConn(WCHAR *conn)
{
	assert(conn);
	WCHAR *pwszValue;
	WCHAR *pwszSemi;
	CUtilString bstrTemp(conn, true);

	m_bstrDatasource = L"default";

	// Search for the "Data Source" name/value pair.
	pwszValue = FindDatasource(bstrTemp);
	if (!pwszValue)
		return;

	// See if there is more connection string after the value.
	pwszSemi = wcschr(pwszValue, L';');
	if (pwszSemi)
		*pwszSemi = L'\0';

	// Save off the value of "Data Source".
	m_bstrDatasource = pwszValue;
}


#ifdef UTILTEST
// This lets you test your parsing changes.
#include "utiltest.cpp"
#endif
