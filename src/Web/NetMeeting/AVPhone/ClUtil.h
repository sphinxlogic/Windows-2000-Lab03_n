//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       CLUTIL.H
//  Content:    Utility Classes
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#ifndef _CL_UTIL_H_
#define _CL_UTIL_H_
#define ASSERT assert


//****************************************************************************
//
// CLASS RefCount
//
//****************************************************************************

class RefCount
{
private:
   LONG m_cRef;

public:
   RefCount();
   // Virtual destructor defers destruction to destructor of derived class.
   virtual ~RefCount();

   ULONG STDMETHODCALLTYPE AddRef(void);
   ULONG STDMETHODCALLTYPE Release(void);
};



//****************************************************************************
//
// CLASS CNotify
//
// Notification sink
//
//****************************************************************************

class CNotify
{
private:
    DWORD  m_dwCookie;
	IUnknown * m_pUnk;
    IConnectionPoint           * m_pcnp;
    IConnectionPointContainer  * m_pcnpcnt;
public:
    CNotify(void);
    ~CNotify();

    HRESULT Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN);
    HRESULT Disconnect(void);

    IUnknown * GetPunk() {return m_pUnk;}
};



//****************************************************************************
//
// CLASS BSTRING
//
//****************************************************************************

class BSTRING
{
private:
	BSTR   m_bstr;

public:
	// Constructors
	BSTRING() {m_bstr = NULL;}

	inline BSTRING(LPCWSTR lpcwString);

#if !defined(UNICODE)
	// We don't support construction from an ANSI string in the Unicode build.
	BSTRING(LPCSTR lpcString);
#endif // !defined(UNICODE)

	// Destructor
	inline ~BSTRING();

	// Cast to BSTR
	operator BSTR() {return m_bstr;}
	inline LPBSTR GetLPBSTR(void);
};

BSTRING::BSTRING(LPCWSTR lpcwString)
{
	if (NULL != lpcwString)
	{
		m_bstr = SysAllocString(lpcwString);
		ASSERT(NULL != m_bstr);
	}
	else
	{
		m_bstr = NULL;
	}
}

BSTRING::~BSTRING()
{
	if (NULL != m_bstr)
	{
		SysFreeString(m_bstr);
	}
}

inline LPBSTR BSTRING::GetLPBSTR(void)
{
	ASSERT(NULL != m_bstr);

	return &m_bstr;
}



//****************************************************************************
//
// CLASS BTSTR
//
//****************************************************************************

class BTSTR
{
private:
	LPTSTR m_psz;

public:
	BTSTR(BSTR bstr);
	~BTSTR();

	// Cast to BSTR
	operator LPTSTR() {return (NULL == m_psz) ? TEXT("<null>") : m_psz;}
};

LPTSTR PszFromBstr(BSTR bst);

#endif  // _CL_UTIL_H_

