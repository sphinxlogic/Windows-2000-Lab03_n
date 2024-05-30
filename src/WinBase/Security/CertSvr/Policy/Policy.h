//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       policy.h
//
//--------------------------------------------------------------------------

// policy.h: Declaration of CCertPolicy


#include "resource.h"       // main symbols
#include "certpsam.h"

/////////////////////////////////////////////////////////////////////////////
// certpol

#define REVTYPE_NONE		0x00000000
#define REVTYPE_CRLDIST		0x00000001
#define REVTYPE_NETSCAPE	0x00000003

#define CERTTYPE_NONE           0x00000000
#define CERTTYPE_NETSCAPE       0x00000001

class CCertPolicy: 
    public CComDualImpl<ICertPolicy, &IID_ICertPolicy, &LIBID_CERTPOLICYLib>, 
    public ISupportErrorInfo,
    public CComObjectRoot,
    public CComCoClass<CCertPolicy, &CLSID_CCertPolicy>
{
public:
    CCertPolicy()
    {
	// RevocationExtension variables:

	m_RevocationType = REVTYPE_NONE;
	m_apstrRevocationURL = NULL;


	// CertTypeExtension variables:

	m_CertType = CERTTYPE_NONE;


	// SubjectAltNameExtension variables:

	m_astrSubjectAltNameProp[0] = NULL;
	m_astrSubjectAltNameProp[1] = NULL;
	m_astrSubjectAltNameObjectId[0] = NULL;
	m_astrSubjectAltNameObjectId[1] = NULL;

	// AuthorityInfoAccessExtension variables:

	m_strAuthorityInfoAccess = NULL;
    }
    ~CCertPolicy();

BEGIN_COM_MAP(CCertPolicy)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ICertPolicy)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CCertPolicy) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation.  The default is to support it

DECLARE_REGISTRY(
    CCertPolicy,
    wszCLASS_CERTPOLICY TEXT(".1"),
    wszCLASS_CERTPOLICY,
    IDS_CERTPOLICY_DESC,
    THREADFLAGS_BOTH)

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICertPolicy
public:
    STDMETHOD(Initialize)( 
	    /* [in] */ BSTR const strConfig);

    STDMETHOD(VerifyRequest)( 
	    /* [in] */ BSTR const strConfig,
	    /* [in] */ LONG Context,
	    /* [in] */ LONG bNewRequest,
	    /* [in] */ LONG Flags,
	    /* [out, retval] */ LONG __RPC_FAR *pDisposition);

    STDMETHOD(GetDescription)( 
	    /* [out, retval] */ BSTR __RPC_FAR *pstrDescription);

    STDMETHOD(ShutDown)();

private:
    VOID _Cleanup();

    VOID _InitRevocationExtension(IN HKEY hkey);
    VOID _InitCertTypeExtension(IN HKEY hkey);
    VOID _InitSubjectAltNameExtension(
				IN HKEY hkey,
				IN WCHAR const *pwszRegName,
				IN WCHAR const *pwszObjectId,
				IN DWORD iAltName);

    VOID _InitAuthorityInfoAccessExtension(IN HKEY hkey);

    HRESULT _AddRevocationExtension(IN ICertServerPolicy *pServer);
    HRESULT _AddCertTypeExtension(IN ICertServerPolicy *pServer);

    HRESULT _AddSubjectAltNameExtension(
				IN ICertServerPolicy *pServer,
				IN DWORD iAltName);

    HRESULT _AddBasicConstraintsExtension(
				IN ICertServerPolicy *pServer);

    HRESULT _AddAuthorityInfoAccessExtension(
				IN ICertServerPolicy *pServer);

    HRESULT _AddKeyUsageExtension(
				IN ICertServerPolicy *pServer,
				IN DWORD KeyUsageState);

    // Add local variables here!

    // RevocationExtension variables:

    DWORD m_RevocationType;
    DWORD m_cRevocationURL;
    BSTR *m_apstrRevocationURL;

    // CertTypeExtension variables:

    DWORD m_CertType;

    // SubjectAltNameExtension variables:

    BSTR m_astrSubjectAltNameProp[2];
    BSTR m_astrSubjectAltNameObjectId[2];

    // AuthorityInfoAccessExtension variables:

    BSTR m_strAuthorityInfoAccess;
};
