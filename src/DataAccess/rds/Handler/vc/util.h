//-----------------------------------------------------------------------------
//
// File:		util.h
//
// Copyright:	Copyright (c) 1997-1999 Microsoft Corporation
//
// Contents:	Definition of class CUtil
//
// Comments:
//
//-----------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H

#include <assert.h>

#define UTIL_NOACCESS   0
#define UTIL_READONLY   2
#define UTIL_READWRITE  3

void ThrowHR(HRESULT hr);


const DWORD CUtilString_padsize = 1024;

class CUtilString   // Never write directly into buffers returned, unless fAllowStomping is true!
{
public:
	CUtilString(bool fAllowStomping = false)
	{
		Clear();
		m_fAllowStomping = fAllowStomping;
	}
	~CUtilString() { Free(); }
	CUtilString(const WCHAR* s, bool fAllowStomping = false)
	{
		Clear();
		*this = s;
		m_fAllowStomping = fAllowStomping;
	}
	CUtilString(const CHAR* s, bool fAllowStomping = false)
	{
		Clear();
		*this = s;
		m_fAllowStomping = fAllowStomping;
	}
	operator WCHAR*()
	{
		return m_pwszVal;
	}
	operator CHAR*()
	{
		if (!m_pwszVal)
			return NULL;
		assert(m_fAllowStomping || m_dwCurLen == wcslen(m_pwszVal));
		if (!m_fDirty && !m_fAllowStomping)
			return m_pszVal;
		m_fDirty = false;
		delete [] m_pszVal;
		DWORD len = WideCharToMultiByte(CP_ACP, 0, m_pwszVal, -1, 0, 0, 0, 0);
		m_pszVal = new CHAR[len+1];
		if (WideCharToMultiByte(CP_ACP, 0, m_pwszVal, -1, m_pszVal, len, 0, 0) == 0)
			m_pszVal[0] = '\0';
		return m_pszVal;
	}
	CUtilString& operator=(const CUtilString& s)
	{
		return operator=(s.m_pwszVal);
	}
	CUtilString& operator=(const WCHAR* s)
	{
		Free();
		if (s)
		{
			m_dwCurLen = wcslen(s);
			m_dwMaxLen = m_dwCurLen + CUtilString_padsize;
			m_pwszVal = new WCHAR[m_dwMaxLen+1];
			wcscpy(m_pwszVal, s);
			assert(m_dwCurLen == wcslen(m_pwszVal));
		}
		return *this;
	}
	CUtilString& operator+=(const WCHAR* s)
	{
		if (!s)
			return *this;
		if (!m_pwszVal)
			return operator=(s);
		if (m_fAllowStomping)
			m_dwCurLen = wcslen(m_pwszVal);
		assert(m_dwCurLen == wcslen(m_pwszVal));
		m_fDirty = true;
		DWORD len = wcslen(s);
		if ((m_dwCurLen+len) > m_dwMaxLen)
		{
			m_dwMaxLen = m_dwCurLen + len + CUtilString_padsize;
			WCHAR * pwsz = new WCHAR[m_dwMaxLen+1];
			wcscpy(pwsz, m_pwszVal);
			delete [] m_pwszVal;
			m_pwszVal = pwsz;
		}
		wcscpy(m_pwszVal+m_dwCurLen, s);
		m_dwCurLen += len;
		assert(m_dwCurLen == wcslen(m_pwszVal));
		return *this;
	}
	CUtilString& operator=(const CHAR* s)
	{
		Free();
		if (s)
		{
			m_dwCurLen = MultiByteToWideChar(CP_ACP, 0, s, -1, 0, 0);
			if (m_dwCurLen)
			{
				m_dwCurLen--;
				m_dwMaxLen = m_dwCurLen + CUtilString_padsize;
				m_pwszVal = new WCHAR[m_dwMaxLen+1];
				if (MultiByteToWideChar(CP_ACP, 0, s, -1, m_pwszVal, m_dwMaxLen+1) == 0)
				{
					m_pwszVal[0] = L'\0';
					m_dwCurLen = 0;
				}
				assert(m_dwCurLen == wcslen(m_pwszVal));
			}
		}
		return *this;
	}
	void Free() { delete [] m_pwszVal; delete [] m_pszVal; Clear(); }
	void Clear() { m_pwszVal = NULL; m_pszVal = NULL; m_dwCurLen = 0; m_dwMaxLen = 0; m_fDirty = true; m_fAllowStomping = false; }

private:
	WCHAR *m_pwszVal;
	CHAR *m_pszVal;
	DWORD m_dwCurLen;
	DWORD m_dwMaxLen;
	bool m_fDirty;
	bool m_fAllowStomping;
};


class CUtil
{
public:
	CUtil();
	~CUtil();
	void SetIniFile(BSTR args);
	void SetSql(BSTR str);
	void SetConn(BSTR conn);
	inline WCHAR *GetSql()  { return (WCHAR *)m_bstrSql; }
	inline WCHAR *GetConn()  { return (WCHAR *)m_bstrConn; }
	inline BOOL HasReadAccess()  { return (m_lAccess >= UTIL_READONLY); }
	inline BOOL HasWriteAccess()  { return (m_lAccess == UTIL_READWRITE); }
	void RaiseError(HRESULT hr);
	inline CHAR * GetUsername()  { return m_pszUsername; }

private:
	void SubstituteParameters(CUtilString &RetVal, CHAR * str, WCHAR * params);  // NOTE: this function is destructive to the "params" buffer.
	CHAR * GetIniString(CHAR * section, CHAR * key);
	void SetSection(void);
	void ParseConn(WCHAR * conn);

	// INI file
	CUtilString m_bstrIniFile;
	CHAR * m_pszLastIniString;
	ULONG m_cLastIniString;

	// Username variables.
	CHAR * m_pszUsername;

	// SQL variables.
	CUtilString m_bstrSqlSection;
	CUtilString m_bstrSql;

	// Connection variables.
	CUtilString m_bstrSectionName;
	CUtilString m_bstrSectionConn;
	CUtilString m_bstrSectionUserlist;
	CUtilString m_bstrConn;
	CUtilString m_bstrDatasource;
	long m_lAccess;
};


class CUtilBSTR
{
public:
	CUtilBSTR(WCHAR *s) { m_bstr = SysAllocString(s); }
	~CUtilBSTR() { SysFreeString(m_bstr); }
	operator BSTR() { return m_bstr; }
private:
	BSTR m_bstr;
};


template <class T>
class CUtilComPtr
{
public:
	CUtilComPtr() { m_p = NULL; }
	~CUtilComPtr() { if (m_p) m_p->Release(); }
	operator T*() { return m_p; }
	T** operator&() { assert(m_p==NULL); return &m_p; }
	T * Detach() { T * p = m_p; m_p = NULL; return p; }
private:
	T * m_p;
};


#endif
