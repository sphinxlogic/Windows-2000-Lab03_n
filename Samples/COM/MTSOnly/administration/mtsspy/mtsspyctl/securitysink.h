
/******************************************************************************\
********************************************************************************
* Filename: SecuritySink.h
*
* Description:  Sink for package events
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/


// SecuritySink.h : Declaration of the CSecuritySink

#ifndef __SECURITY_H__
#define __SECURITY_H__

#include "stdafx.h"
#include "resource.h"       // main symbols

#define USERNAMELEN 64

CComBSTR GuidToBstr(REFGUID guid);

class CMtsSpy;


/////////////////////////////////////////////////////////////////////////////
// CSecuritySink 
class ATL_NO_VTABLE CSecuritySink : 
	public CMtsSink,
	public IMtsSecurityEvents
{
public:
	CSecuritySink()
	{
		m_pSpy = NULL;
	}
	CSecuritySink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}

DECLARE_NOT_AGGREGATABLE(CSecuritySink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CSecuritySink)
	COM_INTERFACE_ENTRY(IMtsSecurityEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()



virtual REFIID GetIID(){return IID_IMtsSecurityEvents;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = Security;return S_OK;}

STDMETHODIMP OnAuthenticate(  LONGLONG perfCount, 
							  REFGUID guidActivity, 
							  ULONG cbByteOrig,  
							  BYTE * pSidOriginalUser,
							  ULONG cbByteCur,   
							  BYTE * pSidCurrentUser, 
							  BOOL bCurrentUserInpersonatingInProc
						)
{

	m_pSpy -> AddEventToList(perfCount, _TEXT("OnAuthenticate"), m_sPackageName);
	CComBSTR sGuidActivity = GuidToBstr(guidActivity);
	m_pSpy -> AddParamValueToList(L"guidActivity", sGuidActivity);

	WCHAR sOriginalUser[256];
	ZeroMemory(sOriginalUser, 256*sizeof(WCHAR));

	if (GetDomainSlashUser(pSidOriginalUser, sOriginalUser))
		m_pSpy -> AddParamValueToList(L"Original User", sOriginalUser);
	else
		m_pSpy -> AddParamValueToList(L"Original User", L"<Error converting SID>");

	WCHAR sDirectUser[256];
	ZeroMemory(sDirectUser, 256*sizeof(WCHAR));

	if (GetDomainSlashUser(pSidCurrentUser, sDirectUser))
		m_pSpy -> AddParamValueToList(L"Direct User", sDirectUser);
	else
		m_pSpy -> AddParamValueToList(L"Direct User", L"<Error converting SID>");

	m_pSpy -> AddParamValueToList(L"Direct User Inpersonating InProc", bCurrentUserInpersonatingInProc ? L"Yes" : L"No");


	IF_AUDIT_DO(OnAuthenticate)(perfCount,							
								sGuidActivity,						
								sOriginalUser,						
								sDirectUser,			
								bCurrentUserInpersonatingInProc);
	return S_OK;
}

BOOL GetDomainSlashUser(
	 PSID Sid,							// in
	 WCHAR* DomainSlashUser)			// out
{
	WCHAR Name[USERNAMELEN + 1];
	DWORD cbName = USERNAMELEN;
	DWORD cbReferencedDomainName = USERNAMELEN;
	SID_NAME_USE eUse;
	WCHAR* p;
	ZeroMemory(Name, cbName);
	if (!LookupAccountSid(NULL,	Sid, Name, &cbName, DomainSlashUser, &cbReferencedDomainName, &eUse))
		return FALSE;

	// concat domain\user
	p = DomainSlashUser + wcslen(DomainSlashUser);
	*p++ = '\\';
	wcscpy(p, Name);
	return TRUE;
}


};

#endif //__SECURITY_H__
