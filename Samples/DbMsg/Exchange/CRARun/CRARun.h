//--crarun.h------------------------------------------------------------------
//
// declaration of the CExchRuleExt class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

class CExchRuleExt : public IExchangeRuleExt
{
public:
    CExchRuleExt(); 
    ~CExchRuleExt();

    STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj);
	STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release(); 

    STDMETHODIMP Install (LPEXCHANGERULEEXTCALLBACK percb, ULONG context);

	STDMETHODIMP QueryRelease();
    
	STDMETHODIMP GetCommand (
		LPEXCHANGERULEEXTCALLBACK percb,
		LPTSTR pszCommand, ULONG cchCommand,
		LPTSTR pszDisplayName, ULONG cchDisplayName);
	
	STDMETHODIMP QueryCommandDisplayName(
		LPEXCHANGERULEEXTCALLBACK percb,
		LPCTSTR pszCommand,
		LPTSTR pszDisplayName, ULONG cchDisplayName);
	
	STDMETHODIMP Command(
		LPEXCHANGERULEEXTCALLBACK percb,
		LPCTSTR pszCommand,
		ULONG cb, LPENTRYID peid);
private:
    ULONG m_cRef;
};

