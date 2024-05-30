// AcctMgmt.h : Declaration of the CAcctMgmt

#ifndef __ACCTMGMT_H_
#define __ACCTMGMT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAcctMgmt
class ATL_NO_VTABLE CAcctMgmt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAcctMgmt, &CLSID_AcctMgmt>,
	public IDispatchImpl<IAcctMgmt, &IID_IAcctMgmt, &LIBID_MSExchangeAcctLib>
{
public:
	CAcctMgmt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ACCTMGMT)
DECLARE_NOT_AGGREGATABLE(CAcctMgmt)

BEGIN_COM_MAP(CAcctMgmt)
	COM_INTERFACE_ENTRY(IAcctMgmt)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IAcctMgmt
public:
	STDMETHOD(ChangeOwnerOfSecDescriptor)(BSTR bstrOldDomain, BSTR bstrOldOwner, BSTR bstrNewDomain, BSTR bstrNewOwner, VARIANT varSecDesp, VARIANT* varNewSecDesp);
   STDMETHOD(GenerateSecDescriptor)(BSTR bstrDomain, BSTR bstrUserLogin,VARIANT* varSecDes);
	STDMETHOD(GetNameFromSid)(BSTR bstrDomain, VARIANT varSid, VARIANT* varDomainName, VARIANT* varUserLogin);
	STDMETHOD(GetSidFromName)(/*[in]*/ BSTR bstrDomain, /*[in]*/ BSTR bstrUserLogin, VARIANT* varSid);

	STDMETHOD(NtAccountCreate)(/*[in]*/ BSTR bstrDomain, /*[in]*/ BSTR bstrUserLogin,  /*[in]*/ BSTR bstrPassword, /*[in]*/BSTR bstrUserComment, /*[in]*/ BSTR bstrLocalGroup);
	
	STDMETHOD(NtAccountDelete)(/*[in]*/ BSTR bstrDomain, /*[in]*/ BSTR bstrUserLogin);

protected:
    STDMETHOD(BstrToArrayOfOctets)(BSTR bstrInput, VARIANT* varArrayOfOctets);
    STDMETHODIMP StructToOctetString(byte* buf, unsigned long lSidLeng, SAFEARRAY **saOT);
    STDMETHODIMP VARIANT2Struct(VARIANT varOctetString, void** ppStruct);
    STDMETHODIMP ReplaceSidInAcl(PACL pAcl, PSID pOldSid, PSID pNewSid, int iSidLeng);
    STDMETHODIMP GetServerFromDomain(BSTR bstrDomain, LPWSTR* wcsServerName);
    bool IsOneCharacter(BSTR bstrSrc, wchar_t cMatch);
    STDMETHODIMP GetSidStruct(BSTR bstrDomain, BSTR bstrUserLogin, PSID *pSid, unsigned long *pulSidLeng);


};

#endif //__ACCTMGMT_H_
