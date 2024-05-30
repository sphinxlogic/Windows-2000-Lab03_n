//-------------------------------------------------------------------------------
// (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

// CertSrc.cpp : Implementation of CCertSrc
#include "certstdafx.h"
#include "CertSource.h"
#include "CertSrc.h"
#include <winldap.h>

/////////////////////////////////////////////////////////////////////////////
// CCertSrc


HRESULT CCertSrc::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("ATL 2.0"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return S_OK;
}

STDMETHODIMP CCertSrc::get_Certificate(BSTR * pVal)
{

  if (pVal == NULL)  return E_INVALIDARG;
  if (!m_bCertInitialized)  return E_FAIL;

  if (*pVal != NULL)  SysFreeString ( *pVal );
  *pVal = m_bstrCertificate.Copy();
  
	return S_OK;
}

STDMETHODIMP CCertSrc::put_Certificate(BSTR newVal)
{

  m_bstrCertificate = newVal;
  m_bCertInitialized = 1;

	return S_OK;
}

STDMETHODIMP CCertSrc::get_DN(BSTR * pVal)
{

  if (pVal == NULL)  return E_INVALIDARG;
  if (!m_bDNInitialized)  return E_FAIL;

  if (*pVal != NULL)  SysFreeString ( *pVal );
  *pVal = m_bstrDN.Copy();

	return S_OK;
}

STDMETHODIMP CCertSrc::put_DN(BSTR newVal)
{

  m_bstrDN = newVal;
  m_bDNInitialized = 1;

	return S_OK;
}

STDMETHODIMP CCertSrc::get_ServerName(BSTR * pVal)
{
  if (pVal == NULL)  return E_INVALIDARG;
  if (!m_bServerNameInitialized)  return E_FAIL;

  if (*pVal != NULL)  SysFreeString ( *pVal );
  *pVal = m_bstrServerName.Copy();

	return S_OK;
}

STDMETHODIMP CCertSrc::put_ServerName(BSTR newVal)
{

  m_bstrServerName = newVal;
  m_bServerNameInitialized = 1;

	return S_OK;
}


STDMETHODIMP CCertSrc::AddCertToDN()
{

	LDAP  *ldapConn = NULL;
	LDAPMessage  *results=NULL;
	LDAP_TIMEVAL  timeVal;
	BOOL  fBinary = FALSE, fSSL = FALSE;
	int				sta = 0;

	LDAP_BERVAL	cert;
	PLDAP_BERVAL certvals[2];
	LDAPMod  val;
	PLDAPMod vals[2];


  // Verify that all of the parameters have been set.  We do not support defaults.
  if ( (!m_bCertInitialized)        || 
       (!m_bDNInitialized)          || 
       (!m_bServerNameInitialized)  || 
       (!m_bPortInitialized)
     )
  {
    return E_FAIL;
  }

  // Connect to the LDAP server. 
	ldapConn = ldap_sslinit(m_bstrServerName.m_str, m_ulPort, (int)fSSL );
	sta = ldap_connect(  ldapConn, &timeVal);
	if(sta != 0 || ldapConn == NULL) {
    return E_FAIL;
	}

  // Setup the LDAP data structures, etc.
  certvals[0] = &cert;
	certvals[1] = NULL;

  val.mod_op = LDAP_MOD_REPLACE | LDAP_MOD_BVALUES;
	val.mod_type = L"userCertificate;binary";
	val.mod_vals.modv_bvals = certvals;

	vals[0] = &val;
	vals[1] = NULL;

  cert.bv_val = (PCHAR)m_bstrCertificate.m_str;
	cert.bv_len = m_bstrCertificate.Length();

  // Write the certificate to the LDAP store.
	sta = ldap_modify( ldapConn, m_bstrDN.m_str,  vals );
  // Note sta will contain the number of messages.  Not an error code.

	return S_OK;
}


STDMETHODIMP CCertSrc::get_PortNumber(long * pVal)
{

  if ((!m_bPortInitialized) || (pVal == NULL))  return E_FAIL;

  *pVal = m_ulPort;

	return S_OK;
}

STDMETHODIMP CCertSrc::put_PortNumber(long newVal)
{

  m_ulPort = (ULONG) newVal;
  
  m_bPortInitialized = 1;

	return S_OK;
}
