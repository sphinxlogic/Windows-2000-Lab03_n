//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 1999
//
// File:        policy.cpp
//
// Contents:    Cert Server Policy Module implementation
//
//---------------------------------------------------------------------------
#include "pch.cpp"
#pragma hdrstop

#include "policy.h"
#include "celib.h"
//#include "newcrypt.h"
#include <stdio.h>
#include <assert.h>

#ifndef wszATTREMAIL1
# define wszATTREMAIL1                    TEXT("E")
# define wszATTREMAIL2                    TEXT("EMail")
#endif

#ifndef DBG_CERTSRV
#error -- DBG_CERTSRV not defined!
#endif

BOOL fDebug = DBG_CERTSRV;

#define wszDESCRIPTION  L"Microsoft Certificate Server Default Policy Module"


//+--------------------------------------------------------------------------
// CCertPolicy::~CCertPolicy -- destructor
//
// free memory associated with this instance
//+--------------------------------------------------------------------------

CCertPolicy::~CCertPolicy()
{
    _Cleanup();
}


//+--------------------------------------------------------------------------
// CCertPolicy::_Cleanup -- free memory associated with this instance
//
// free memory associated with this instance
//+--------------------------------------------------------------------------

VOID
CCertPolicy::_Cleanup()
{
    DWORD i;

    // RevocationExtension variables:

    if (NULL != m_apstrRevocationURL)
    {
        for (i = 0; i < m_cRevocationURL; i++)
        {
            if (NULL != m_apstrRevocationURL[i])
            {
                SysFreeString(m_apstrRevocationURL[i]);
            }
        }
        LocalFree(m_apstrRevocationURL);
        m_apstrRevocationURL = NULL;
    }


    // CertTypeExtension variables:

    m_RevocationType = REVTYPE_NONE;


    // SubjectAltNameExtension variables:

    for (i = 0; i < 2; i++)
    {
	if (NULL != m_astrSubjectAltNameProp[i])
	{
	    SysFreeString(m_astrSubjectAltNameProp[i]);
	    m_astrSubjectAltNameProp[i] = NULL;
	}
	if (NULL != m_astrSubjectAltNameObjectId[i])
	{
	    SysFreeString(m_astrSubjectAltNameObjectId[i]);
	    m_astrSubjectAltNameObjectId[i] = NULL;
	}
    }

    // AuthorityInfoAccessExtension variables:

    if (NULL == m_strAuthorityInfoAccess)
    {
	SysFreeString(m_strAuthorityInfoAccess);
	m_strAuthorityInfoAccess = NULL;
    }
}


//+--------------------------------------------------------------------------
// CCertPolicy::_InitRevocationExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

#define wszREVTYPE_NETSCAPE	TEXT("Netscape")
#define wszREVTYPE_CRL		TEXT("CRL")

VOID
CCertPolicy::_InitRevocationExtension(
    IN HKEY hkey)
{
    DWORD err;
    DWORD i;
    DWORD dwType;
    DWORD cbbuf;
    WCHAR *pwc;
    WCHAR const *pwszRegRevocation;
    WCHAR awcbuf[MAX_PATH];

    cbbuf = sizeof(awcbuf);
    err = RegQueryValueEx(
                hkey,
                wszREGREVOCATIONTYPE,
                NULL,           // lpdwReserved
                &dwType,
                (BYTE *) awcbuf,
                &cbbuf);
    if (ERROR_SUCCESS != err || REG_SZ != dwType || sizeof(awcbuf) <= cbbuf)
    {
        goto error;
    }
    if (0 == lstrcmpi(awcbuf, wszREVTYPE_CRL))
    {
        m_RevocationType = REVTYPE_CRLDIST;
        pwszRegRevocation = wszREGREVOCATIONCRLURL;
    }
    else
    if (0 == lstrcmpi(awcbuf, wszREVTYPE_NETSCAPE))
    {
        m_RevocationType = REVTYPE_NETSCAPE;
        pwszRegRevocation = wszREGREVOCATIONURL;
    }
    else
    {
        goto error;
    }

    cbbuf = sizeof(awcbuf) - 2 * sizeof(WCHAR);
    err = RegQueryValueEx(
		    hkey,
		    pwszRegRevocation,
		    NULL,           // lpdwReserved
		    &dwType,
		    (BYTE *) awcbuf,
		    &cbbuf);
    if (ERROR_SUCCESS != err ||
        (REG_SZ != dwType && REG_MULTI_SZ != dwType) ||
        sizeof(awcbuf) - 2 * sizeof(WCHAR) <= cbbuf)
    {
        goto error;
    }

    // Double null terminate to make a REG_SZ value look like REG_MULTI_SZ.

    awcbuf[cbbuf/sizeof(WCHAR)] = L'\0';
    awcbuf[cbbuf/sizeof(WCHAR) + 1] = L'\0';

    m_cRevocationURL = 0;
    pwc = awcbuf;
    while (TRUE)
    {
        pwc = wcschr(pwc, L'\0');
        assert(NULL != pwc);
        pwc++;
        m_cRevocationURL++;
        if (L'\0' == *pwc)
        {
            break;
        }
    }

    m_apstrRevocationURL = (BSTR *) LocalAlloc(
                                        LMEM_FIXED,
                                        m_cRevocationURL * sizeof(BSTR));
    if (NULL == m_apstrRevocationURL)
    {
        goto error;
    }
    memset(m_apstrRevocationURL, 0, m_cRevocationURL * sizeof(BSTR));

    pwc = awcbuf;
    for (i = 0; i < m_cRevocationURL; i++)
    {
        DWORD cwc = wcslen(SysAllocString(pwc));

        if (REVTYPE_NETSCAPE == m_RevocationType)
        {
            cwc++;
        }
        m_apstrRevocationURL[i] = SysAllocStringLen(NULL, cwc);
        if (NULL == m_apstrRevocationURL[i])
        {
            _Cleanup();
            goto error;
        }
        wcscpy(m_apstrRevocationURL[i], pwc);
        if (REVTYPE_NETSCAPE == m_RevocationType)
        {
            wcscat(m_apstrRevocationURL[i], L"?");
        }
        if (fDebug)
        {
            printf(
                "Policy: Revocation URL(type=%u): %s[%u]: %ws\n",
                m_RevocationType,
                REVTYPE_CRLDIST == m_RevocationType?
                    "CRLDistPoint" : "Netscape",
                i,
                m_apstrRevocationURL[i]);
        }
        pwc = wcschr(pwc, L'\0');
        assert(NULL != pwc);
        pwc++;
        assert(L'\0' != *pwc || i + 1 == m_cRevocationURL);
    }

error:
    ;
}


//+--------------------------------------------------------------------------
// CCertPolicy::_InitCertTypeExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

VOID
CCertPolicy::_InitCertTypeExtension(
    IN HKEY hkey)
{
    DWORD err;
    DWORD dwType;
    DWORD cbbuf;
    DWORD dwCertType;

    cbbuf = sizeof(dwCertType);
    err = RegQueryValueEx(
			hkey,
			wszREGNETSCAPECERTTYPE,
			NULL,         // lpdwReserved
			&dwType,
			(BYTE *) &dwCertType,
			&cbbuf);
    if (ERROR_SUCCESS != err || REG_DWORD != dwType)
    {
        goto error;
    }
    if (dwCertType == CERTTYPE_NETSCAPE)
    {
        m_CertType = CERTTYPE_NETSCAPE;
    }
    if (fDebug && m_CertType)
    {
        printf(
            "Policy: Netscape Certificate Type(type=%u): %s\n",
            m_CertType,
            CERTTYPE_NETSCAPE == m_CertType? "Netscape" : "None");
    }

error:
    ;
}


//+--------------------------------------------------------------------------
// CCertPolicy::_InitAuthorityInfoAccessExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

VOID
CCertPolicy::_InitAuthorityInfoAccessExtension(
    IN HKEY hkey)
{
    DWORD err;
    DWORD dwType;
    DWORD cbbuf;
    WCHAR awcbuf[MAX_PATH];

    cbbuf = sizeof(awcbuf) - 2 * sizeof(WCHAR);
    err = RegQueryValueEx(
		    hkey,
		    wszREGISSUERCERTURL,
		    NULL,         // lpdwReserved
		    &dwType,
		    (BYTE *) awcbuf,
		    &cbbuf);
    if (ERROR_SUCCESS != err ||
        REG_SZ != dwType ||
        sizeof(awcbuf) - 2 * sizeof(WCHAR) <= cbbuf)
    {
        goto error;
    }
    if (!ceConvertWszToBstr(&m_strAuthorityInfoAccess, awcbuf, -1))
    {
	goto error;
    }

    if (fDebug)
    {
        printf(
            "Policy: %ws: %ws\n",
	    wszREGISSUERCERTURL,
	    m_strAuthorityInfoAccess);
    }

error:
    ;
}


//+--------------------------------------------------------------------------
// CCertPolicy::_InitSubjectAltNameExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

VOID
CCertPolicy::_InitSubjectAltNameExtension(
    IN HKEY hkey,
    IN WCHAR const *pwszRegName,
    IN WCHAR const *pwszObjectId,
    IN DWORD iAltName)
{
    DWORD err;
    DWORD dwType;
    DWORD cbbuf;
    WCHAR awcbuf[MAX_PATH];

    cbbuf = sizeof(awcbuf) - 2 * sizeof(WCHAR);
    err = RegQueryValueEx(
		    hkey,
		    pwszRegName,
		    NULL,         // lpdwReserved
		    &dwType,
		    (BYTE *) awcbuf,
		    &cbbuf);
    if (ERROR_SUCCESS != err ||
        REG_SZ != dwType ||
        sizeof(awcbuf) - 2 * sizeof(WCHAR) <= cbbuf)
    {
        goto error;
    }
    if (0 == lstrcmpi(awcbuf, wszATTREMAIL1) ||
	0 == lstrcmpi(awcbuf, wszATTREMAIL2))
    {
        if (!ceConvertWszToBstr(
			&m_astrSubjectAltNameObjectId[iAltName],
			pwszObjectId,
			-1))
	{
	    goto error;
	}

        if (!ceConvertWszToBstr(
			&m_astrSubjectAltNameProp[iAltName],
			wszPROPSUBJECTEMAIL,
			-1))
	{
	    goto error;
	}
    }
    if (fDebug)
    {
        printf(
            "Policy: %ws(RDN=%ws): %ws\n",
	    pwszRegName,
            awcbuf,
            m_astrSubjectAltNameProp[iAltName]);
    }

error:
    ;
}


//+--------------------------------------------------------------------------
// CCertPolicy::Initialize
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertPolicy::Initialize(
    /* [in] */ BSTR const strConfig)
{
    HRESULT hr;
    DWORD err;
    HKEY hkey = NULL;
    WCHAR awcReg[MAX_PATH];

    _Cleanup();

    wcscpy(awcReg, wszREGKEYBASE);
    wcscat(awcReg, L"\\");
    wcscat(awcReg, wszREGKEYCONFIG);
    wcscat(awcReg, L"\\");
    wcscat(awcReg, strConfig);

    err = RegOpenKeyEx(
                HKEY_LOCAL_MACHINE,
                awcReg,
                0,              // dwReserved
                KEY_ENUMERATE_SUB_KEYS | KEY_EXECUTE | KEY_QUERY_VALUE,
                &hkey);

    if (ERROR_SUCCESS != err)
    {
	hr = HRESULT_FROM_WIN32(err);
        goto error;
    }

    _InitRevocationExtension(hkey);
    _InitCertTypeExtension(hkey);
    _InitSubjectAltNameExtension(
			    hkey,
			    wszREGSUBJECTALTNAME,
			    TEXT(szOID_SUBJECT_ALT_NAME),
			    0);
    _InitSubjectAltNameExtension(
			    hkey,
			    wszREGSUBJECTALTNAME2,
			    TEXT(szOID_SUBJECT_ALT_NAME2),
			    1);

    _InitAuthorityInfoAccessExtension(hkey);

    hr = S_OK;

error:
    if (NULL != hkey)
    {
        RegCloseKey(hkey);
    }
    return(hr);
}


HRESULT
EnumerateExtensions(
    IN ICertServerPolicy *pServer,
    OUT DWORD *pKeyUsageState)
{
    HRESULT hr;
    HRESULT hr2;
    BSTR strName = NULL;
    LONG ExtFlags;
    VARIANT varValue;
    BOOL fClose = FALSE;
    CERT_ENHKEY_USAGE *pKeyUsage = NULL;
    DWORD cb;

    *pKeyUsageState = 0;
    VariantInit(&varValue);
    hr = pServer->EnumerateExtensionsSetup(0);
    if (S_OK != hr)
    {
        if (fDebug)
        {
            printf("Policy:EnumerateExtensionsSetup: %x\n", hr);
        }
        goto error;
    }
    fClose = TRUE;
    while (TRUE)
    {
        hr = pServer->EnumerateExtensions(&strName);
        if (S_OK != hr)
        {
            if (S_FALSE == hr)
            {
                hr = S_OK;
                break;
            }
            if (fDebug)
            {
                printf("Policy:EnumerateExtensions: %x\n", hr);
            }
            goto error;
        }
        hr = pServer->GetCertificateExtension(
                                        strName,
                                        PROPTYPE_BINARY,
                                        &varValue);
        if (S_OK != hr)
        {
            if (fDebug)
            {
                printf("Policy:GetCertificateExtension: %x\n", hr);
            }
            goto error;
        }
        hr = pServer->GetCertificateExtensionFlags(&ExtFlags);

        if (S_OK != hr)
        {
            if (fDebug)
            {
                printf("Policy:GetCertificateExtensionFlags: %x\n", hr);
            }
            goto error;
        }

        // If this is enhanced key usage, add the extension to the cert

        if (0 == lstrcmpi(strName, TEXT(szOID_ENHANCED_KEY_USAGE)))
	{
	    DWORD i;

            ExtFlags &= ~EXTENSION_DISABLE_FLAG;
            hr = pServer->SetCertificateExtension(
					strName,
					PROPTYPE_BINARY,
					ExtFlags,
					&varValue);

            if (S_OK != hr)
            {
                if (fDebug)
                {
		    printf("Policy:SetCertificateExtensionFlags: %x\n", hr);
                }
                goto error;
            }

	    // Decode to plain text
	    if (!ceDecodeObject(
			    X509_ASN_ENCODING,
			    X509_ENHANCED_KEY_USAGE,
			    (BYTE const *) varValue.bstrVal,
			    SysStringByteLen(varValue.bstrVal),
			    (VOID **) &pKeyUsage,
			    &cb))
	    {
		hr = GetLastError();
		printf("Policy:ceDecodeObject: %x\n", hr);
		goto error;
	    }
	    for (i = 0; i < pKeyUsage->cUsageIdentifier; i++)
	    {
		char const *psz = pKeyUsage->rgpszUsageIdentifier[i];

		if (0 == strcmp(psz, szOID_PKIX_KP_SERVER_AUTH) ||
		    0 == strcmp(psz, szOID_PKIX_KP_CLIENT_AUTH) ||
		    0 == strcmp(psz, szOID_PKIX_KP_EMAIL_PROTECTION))
		{
		    *pKeyUsageState = 1;	// Exchange
		    break;
		}
		else
		if (0 == strcmp(psz, szOID_PKIX_KP_CODE_SIGNING) ||
		    0 == strcmp(psz, szOID_PKIX_KP_IPSEC_END_SYSTEM) ||
		    0 == strcmp(psz, szOID_PKIX_KP_IPSEC_TUNNEL) ||
		    0 == strcmp(psz, szOID_PKIX_KP_IPSEC_USER) ||
		    0 == strcmp(psz, szOID_PKIX_KP_TIMESTAMP_SIGNING))
		{
		    *pKeyUsageState = 2;	// Signing
		    break;
		}
	    }
        }

        if (fDebug)
        {
            printf(
                "Policy:EnumerateExtensions(%ws, Flags=%x, %x bytes)\n",
                strName,
                ExtFlags,
                SysStringByteLen(varValue.bstrVal));
        }
        VariantClear(&varValue);
    }

error:
    if (fClose)
    {
        hr2 = pServer->EnumerateExtensionsClose();
        if (S_OK != hr2)
        {
            if (fDebug)
            {
                printf("Policy:EnumerateExtensionsClose: %x\n", hr2);
            }
            if (S_OK == hr)
            {
                hr = hr2;
            }
            goto error;
        }
    }
    if (NULL != pKeyUsage)
    {
        LocalFree(pKeyUsage);
    }
    if (NULL != strName)
    {
        SysFreeString(strName);
    }
    VariantClear(&varValue);
    return(hr);
}


HRESULT
EnumerateAttributes(
    IN ICertServerPolicy *pServer)
{
    HRESULT hr;
    HRESULT hr2;
    BSTR strName = NULL;
    BOOL fClose = FALSE;
    BSTR strValue = NULL;

    hr = pServer->EnumerateAttributesSetup(0);
    if (S_OK != hr)
    {
        if (fDebug)
        {
            printf("Policy:EnumerateAttributesSetup: %x\n", hr);
        }
        goto error;
    }
    fClose = TRUE;
    while (TRUE)
    {
        hr = pServer->EnumerateAttributes(&strName);
        if (S_OK != hr)
        {
            if (S_FALSE == hr)
            {
                hr = S_OK;
                break;
            }
            if (fDebug)
            {
                printf("Policy:EnumerateAttributes: %x\n", hr);
            }
            goto error;
        }

        hr = pServer->GetRequestAttribute(strName, &strValue);
        if (S_OK != hr)
        {
            if (fDebug)
            {
                printf("Policy:GetRequestAttribute: %x\n", hr);
            }
            goto error;
        }
        if (fDebug)
        {
            printf(
                "Policy:EnumerateAttributes(%ws = %ws)\n",
                strName,
                strValue);
        }
        if (NULL != strValue)
        {
            SysFreeString(strValue);
            strValue = NULL;
        }
    }

error:
    if (fClose)
    {
        hr2 = pServer->EnumerateAttributesClose();
        if (S_OK != hr2)
        {
            if (fDebug)
            {
                printf("Policy:EnumerateAttributesClose: %x\n", hr2);
            }
            if (S_OK == hr)
            {
                hr = hr2;
            }
            goto error;
        }
    }

    if (NULL != strName)
    {
        SysFreeString(strName);
    }
    if (NULL != strValue)
    {
        SysFreeString(strValue);
    }
    return(hr);
}


HRESULT
CheckRequestProperties(
    IN ICertServerPolicy *pServer)
{
    HRESULT hr;
    VARIANT varValue;
    BSTR strName = NULL;

    VariantInit(&varValue);

    strName = SysAllocString(wszPROPREQUESTREQUESTID);
    if (NULL == strName)
    {
        hr = E_OUTOFMEMORY;
        goto error;
    }

    hr = pServer->GetRequestProperty(strName, PROPTYPE_LONG, &varValue);
    if (S_OK != hr)
    {
        if (fDebug)
        {
            printf("Policy:GetRequestProperty: %x\n", hr);
        }
        goto error;
    }
    if (fDebug)
    {
        printf(
            "Policy:CheckRequestProperties(%ws = %x)\n",
            strName,
            varValue.lVal);
    }
    VariantClear(&varValue);

error:
    if (NULL != strName)
    {
        SysFreeString(strName);
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::_AddRevocationExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

HRESULT
CCertPolicy::_AddRevocationExtension(
    IN ICertServerPolicy *pServer)
{
    HRESULT hr = S_OK;
    ICertEncodeCRLDistInfo *pCRLDist = NULL;
    BSTR strExtension = NULL;
    VARIANT varExtension;
    DWORD i;

    if (NULL != m_apstrRevocationURL)
    {
        varExtension.vt = VT_BSTR;
        if (REVTYPE_CRLDIST == m_RevocationType)
        {
            hr = CoCreateInstance(
                            CLSID_CCertEncodeCRLDistInfo,
                            NULL,               // pUnkOuter
                            CLSCTX_INPROC_SERVER,
                            IID_ICertEncodeCRLDistInfo,
                            (VOID **) &pCRLDist);
            if (S_OK != hr)
            {
                goto error;
            }

            hr = pCRLDist->Reset(m_cRevocationURL);
            if (S_OK != hr)
            {
                goto error;
            }
            for (i = 0; i < m_cRevocationURL; i++)
            {
                DWORD j;

                hr = pCRLDist->SetNameCount(i, 1);
                if (S_OK != hr)
                {
                    goto error;
                }
                for (j = 0; j < 1; j++)
                {
                    hr = pCRLDist->SetNameEntry(
                                            i,
                                            j,
                                            CERT_ALT_NAME_URL,
                                            m_apstrRevocationURL[i]);
                    if (S_OK != hr)
                    {
                        goto error;
                    }
                }
            }
            hr = pCRLDist->Encode(&strExtension);
            if (S_OK != hr)
            {
                goto error;
            }
            varExtension.bstrVal = strExtension;
            hr = pServer->SetCertificateExtension(
                                    TEXT(szOID_CRL_DIST_POINTS),
                                    PROPTYPE_BINARY,
                                    0,
                                    &varExtension);
            if (S_OK != hr)
            {
                goto error;
            }
        }
        else
        if (REVTYPE_NETSCAPE == m_RevocationType)
        {
            varExtension.bstrVal = m_apstrRevocationURL[0];
            hr = pServer->SetCertificateExtension(
                                    TEXT(szOID_NETSCAPE_REVOCATION_URL),
                                    PROPTYPE_STRING,
                                    0,
                                    &varExtension);
            if (S_OK != hr)
            {
                goto error;
            }
        }
    }

error:
    if (NULL != strExtension)
    {
        SysFreeString(strExtension);
    }
    if (NULL != pCRLDist)
    {
        pCRLDist->Release();
    }
    return(hr);
}


#define HIGHBIT(bitno)	(1 << (7 - (bitno)))	// bit counted from high end

#define SSLBIT_CLIENT	((BYTE) HIGHBIT(0))	// certified for client auth
#define SSLBIT_SERVER	((BYTE) HIGHBIT(1))	// certified for server auth
#define SSLBIT_CA	((BYTE) HIGHBIT(5))	// certified for issuing certs
#define SSLBIT_CA2	((BYTE) HIGHBIT(6))	// second ca bit

#define NSCERTTYPE_CLIENT  ((BYTE) SSLBIT_CLIENT)
#define NSCERTTYPE_SERVER  ((BYTE) (SSLBIT_SERVER | SSLBIT_CLIENT))
#define NSCERTTYPE_CA	   ((BYTE) (SSLBIT_CA | SSLBIT_CA2))

//+--------------------------------------------------------------------------
// CCertPolicy::_AddCertTypeExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

HRESULT
CCertPolicy::_AddCertTypeExtension(
    IN ICertServerPolicy *pServer)
{
    HRESULT hr = S_OK;
    ICertEncodeBitString *pBitString = NULL;
    BSTR strExtension = NULL;
    VARIANT varExtension;
    BSTR strBitString = NULL;
    BSTR strCertType = NULL;

    if (CERTTYPE_NETSCAPE == m_CertType)
    {
	BYTE CertType;

	hr = CoCreateInstance(
			CLSID_CCertEncodeBitString,
			NULL,               // pUnkOuter
			CLSCTX_INPROC_SERVER,
			IID_ICertEncodeBitString,
			(VOID **) &pBitString);
	if (S_OK != hr)
	{
	    goto error;
	}

	CertType = NSCERTTYPE_CLIENT;	// Default to client auth. cert
        hr = pServer->GetRequestAttribute(L"CertType", &strCertType);
        if (S_OK == hr)
        {
            if (0 == lstrcmpi(strCertType, L"server"))
            {
                CertType = NSCERTTYPE_SERVER;
            }
            else if (0 == lstrcmpi(strCertType, L"ca"))
            {
                CertType = NSCERTTYPE_CA;
            }
        }

        if (!ceConvertWszToBstr(
		    &strBitString,
		    (WCHAR const *) &CertType,
		    sizeof(CertType)))
	{
	    hr = E_OUTOFMEMORY;
	    goto error;
	}

	hr = pBitString->Encode(
			    sizeof(CertType) * 8,
			    strBitString,
			    &strExtension);
	if (S_OK != hr)
	{
	    goto error;
	}

        varExtension.vt = VT_BSTR;
	varExtension.bstrVal = strExtension;
	hr = pServer->SetCertificateExtension(
				TEXT(szOID_NETSCAPE_CERT_TYPE),
				PROPTYPE_BINARY,
				0,
				&varExtension);
	if (S_OK != hr)
	{
	    goto error;
	}
    }

error:
    if (NULL != strExtension)
    {
        SysFreeString(strExtension);
    }
    if (NULL != strBitString)
    {
        SysFreeString(strBitString);
    }
    if (NULL != strCertType)
    {
        SysFreeString(strCertType);
    }
    if (NULL != pBitString)
    {
        pBitString->Release();
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::_AddSubjectAltNameExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

HRESULT
CCertPolicy::_AddSubjectAltNameExtension(
    IN ICertServerPolicy *pServer,
    IN DWORD iAltName)
{
    HRESULT hr = S_OK;
    ICertEncodeAltName *pAltName = NULL;
    BSTR strExtension = NULL;
    VARIANT varExtension;
    BSTR strCertType = NULL;
    BSTR strName = NULL;
    VARIANT varValue;

    VariantInit(&varValue);
    if (NULL != m_astrSubjectAltNameProp[iAltName])
    {
	BYTE CertType;

	hr = CoCreateInstance(
			CLSID_CCertEncodeAltName,
			NULL,               // pUnkOuter
			CLSCTX_INPROC_SERVER,
			IID_ICertEncodeAltName,
			(VOID **) &pAltName);
	if (S_OK != hr)
	{
	    goto error;
	}

	hr = pServer->GetRequestProperty(
				    m_astrSubjectAltNameProp[iAltName],
				    PROPTYPE_STRING,
				    &varValue);
	if (S_OK != hr)
	{
	    printf(
		"Policy:GetRequestProperty(%ws):%s %x\n",
		m_astrSubjectAltNameProp[iAltName],
		CERTSRV_E_PROPERTY_EMPTY == hr? " MISSING ATTRIBUTE" : "",
		hr);
	    if (CERTSRV_E_PROPERTY_EMPTY == hr)
	    {
		hr = S_OK;
	    }
	    goto error;
	}
        if (VT_BSTR != varValue.vt)
	{
 	    hr = E_INVALIDARG;
	    goto error;
	}

        if (L'\0' == varValue.bstrVal[0])
	{
	    hr = S_OK;
	    goto error;
	}
        if (!ceConvertWszToBstr(&strName, varValue.bstrVal, -1))
	{
	    hr = E_OUTOFMEMORY;
	    goto error;
	}

	hr = pAltName->Reset(1);
	if (S_OK != hr)
	{
	    goto error;
	}

	hr = pAltName->SetNameEntry(0, CERT_ALT_NAME_RFC822_NAME, strName);
	if (S_OK != hr)
	{
	    goto error;
	}

	hr = pAltName->Encode(&strExtension);
	if (S_OK != hr)
	{
	    goto error;
	}

        varExtension.vt = VT_BSTR;
	varExtension.bstrVal = strExtension;
	hr = pServer->SetCertificateExtension(
				m_astrSubjectAltNameObjectId[iAltName],
				PROPTYPE_BINARY,
				0,
				&varExtension);
	if (S_OK != hr)
	{
	    goto error;
	}
    }

error:
    if (NULL != strName)
    {
        SysFreeString(strName);
    }
    if (NULL != strExtension)
    {
        SysFreeString(strExtension);
    }
    if (NULL != pAltName)
    {
        pAltName->Release();
    }
    VariantClear(&varValue);
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::_AddBasicConstraintsExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

HRESULT
CCertPolicy::_AddBasicConstraintsExtension(
    IN ICertServerPolicy *pServer)
{
    HRESULT hr = S_OK;
    BYTE *pbEncoded = NULL;
    DWORD cbEncoded;
    CERT_BASIC_CONSTRAINTS2_INFO bc2i;
    BSTR strExtension = NULL;
    VARIANT varExtension;

    bc2i.fCA = FALSE;
    bc2i.fPathLenConstraint = FALSE;
    bc2i.dwPathLenConstraint = 0;

    if (!ceEncodeObject(
		    X509_ASN_ENCODING,
		    X509_BASIC_CONSTRAINTS2,
		    &bc2i,
		    &pbEncoded,
		    &cbEncoded))
    {
	hr = GetLastError();
	printf("Policy:ceEncodeObject: %x\n", hr);
	goto error;
    }
    if (!ceConvertWszToBstr(
			&strExtension,
			(WCHAR const *) pbEncoded,
			cbEncoded))
    {
	hr = E_OUTOFMEMORY;
	goto error;
    }

    varExtension.vt = VT_BSTR;
    varExtension.bstrVal = strExtension;
    hr = pServer->SetCertificateExtension(
			    TEXT(szOID_BASIC_CONSTRAINTS2),
			    PROPTYPE_BINARY,
			    0,
			    &varExtension);
    if (S_OK != hr)
    {
	goto error;
    }

error:
    if (NULL != pbEncoded)
    {
	LocalFree(pbEncoded);
    }
    if (NULL != strExtension)
    {
        SysFreeString(strExtension);
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::_AddAuthorityInfoAccessExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

HRESULT
CCertPolicy::_AddAuthorityInfoAccessExtension(
    IN ICertServerPolicy *pServer)
{
    HRESULT hr = S_OK;
    BYTE *pbEncoded = NULL;
    DWORD cbEncoded;
    BSTR strExtension = NULL;
    VARIANT varExtension;

    CERT_AUTHORITY_INFO_ACCESS caio;
    CERT_ACCESS_DESCRIPTION cad;

    if (NULL != m_strAuthorityInfoAccess)
    {
	caio.cAccDescr = 1;
	caio.rgAccDescr = &cad;

	cad.pszAccessMethod = szOID_PKIX_CA_ISSUERS;
	cad.AccessLocation.dwAltNameChoice = CERT_ALT_NAME_URL;
	cad.AccessLocation.pwszURL = m_strAuthorityInfoAccess;

	if (!ceEncodeObject(
			X509_ASN_ENCODING,
			X509_AUTHORITY_INFO_ACCESS,
			&caio,
			&pbEncoded,
			&cbEncoded))
	{
	    hr = GetLastError();
	    printf("Policy:ceEncodeObject: %x\n", hr);
	    goto error;
	}
	if (!ceConvertWszToBstr(
			    &strExtension,
			    (WCHAR const *) pbEncoded,
			    cbEncoded))
	{
	    hr = E_OUTOFMEMORY;
	    goto error;
	}

	varExtension.vt = VT_BSTR;
	varExtension.bstrVal = strExtension;
	hr = pServer->SetCertificateExtension(
				TEXT(szOID_AUTHORITY_INFO_ACCESS),
				PROPTYPE_BINARY,
				0,
				&varExtension);
	if (S_OK != hr)
	{
	    goto error;
	}
    }

error:
    if (NULL != pbEncoded)
    {
	LocalFree(pbEncoded);
    }
    if (NULL != strExtension)
    {
        SysFreeString(strExtension);
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::_AddKeyUsageExtension
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

HRESULT
CCertPolicy::_AddKeyUsageExtension(
    IN ICertServerPolicy *pServer,
    IN DWORD KeyUsageState)
{
    HRESULT hr = S_OK;
    BSTR strName = NULL;
    ICertEncodeBitString *pBitString = NULL;
    BSTR strExtension = NULL;
    VARIANT varExtension;
    BSTR strBitString = NULL;

    if (0 != KeyUsageState)
    {
	BYTE KeyUsage = 1 == KeyUsageState?

	    (CERT_KEY_ENCIPHERMENT_KEY_USAGE | 
		CERT_DATA_ENCIPHERMENT_KEY_USAGE | 
		CERT_KEY_AGREEMENT_KEY_USAGE) :

	    (CERT_DIGITAL_SIGNATURE_KEY_USAGE |
		CERT_NON_REPUDIATION_KEY_USAGE);

	hr = CoCreateInstance(
			CLSID_CCertEncodeBitString,
			NULL,               // pUnkOuter
			CLSCTX_INPROC_SERVER,
			IID_ICertEncodeBitString,
			(VOID **) &pBitString);
	if (S_OK != hr)
	{
	    goto error;
	}

        if (!ceConvertWszToBstr(
		    &strBitString,
		    (WCHAR const *) &KeyUsage,
		    sizeof(KeyUsage)))
	{
	    hr = E_OUTOFMEMORY;
	    goto error;
	}

	hr = pBitString->Encode(
			    sizeof(KeyUsage) * 8,
			    strBitString,
			    &strExtension);
	if (S_OK != hr)
	{
	    goto error;
	}

	if (!ceConvertWszToBstr(&strName, TEXT(szOID_KEY_USAGE), -1))
	{
	    hr = E_OUTOFMEMORY;
	    goto error;
	}
        varExtension.vt = VT_BSTR;
	varExtension.bstrVal = strExtension;
	hr = pServer->SetCertificateExtension(
				strName,
				PROPTYPE_BINARY,
				0,
				&varExtension);
	if (S_OK != hr)
	{
	    goto error;
	}
    }

error:
    if (NULL != strName)
    {
        SysFreeString(strName);
    }
    if (NULL != strExtension)
    {
        SysFreeString(strExtension);
    }
    if (NULL != strBitString)
    {
        SysFreeString(strBitString);
    }
    if (NULL != pBitString)
    {
        pBitString->Release();
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::VerifyRequest
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertPolicy::VerifyRequest(
    /* [in] */ BSTR const strConfig,
    /* [in] */ LONG Context,
    /* [in] */ LONG bNewRequest,
    /* [in] */ LONG Flags,
    /* [out, retval] */ LONG __RPC_FAR *pDisposition)
{
    HRESULT hr;
    ICertServerPolicy *pServer = NULL;
    DWORD KeyUsageState;

    hr = CoCreateInstance(
                    CLSID_CCertServerPolicy,
                    NULL,               // pUnkOuter
                    CLSCTX_INPROC_SERVER,
                    IID_ICertServerPolicy,
                    (VOID **) &pServer);
    if (S_OK != hr)
    {
        goto error;
    }
    hr = pServer->SetContext(Context);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddRevocationExtension(pServer);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddCertTypeExtension(pServer);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddSubjectAltNameExtension(pServer, 0);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddSubjectAltNameExtension(pServer, 1);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddBasicConstraintsExtension(pServer);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddAuthorityInfoAccessExtension(pServer);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = EnumerateExtensions(pServer, &KeyUsageState);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = _AddKeyUsageExtension(pServer, KeyUsageState);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = EnumerateAttributes(pServer);
    if (S_OK != hr)
    {
        goto error;
    }

    hr = CheckRequestProperties(pServer);
    if (S_OK != hr)
    {
        goto error;
    }

error:
    *pDisposition = S_OK == hr? VR_INSTANT_OK : VR_INSTANT_BAD;
    if (NULL != pServer)
    {
        pServer->Release();
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::GetDescription
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertPolicy::GetDescription(
    /* [out, retval] */ BSTR __RPC_FAR *pstrDescription)
{
    HRESULT hr = S_OK;

    *pstrDescription = SysAllocString(wszDESCRIPTION);
    if (NULL == *pstrDescription)
    {
        hr = E_OUTOFMEMORY;
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertPolicy::ShutDown
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertPolicy::ShutDown(VOID)
{
    return(S_OK);
}


STDMETHODIMP
CCertPolicy::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID *arr[] =
    {
        &IID_ICertPolicy,
    };

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i], riid))
        {
            return(S_OK);
        }
    }
    return(S_FALSE);
}
