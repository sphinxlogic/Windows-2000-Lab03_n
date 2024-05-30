/************************************************************************
*                                                                       *
*   $$Root$$MAPIApp.cpp												*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#include "stdafx.h"
#include "$$Root$$MAPIApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//
//	Structures and local functions for error code lookup.
//

typedef struct tagErrorInfo
{
	HRESULT		hValue;
	LPCSTR		lpsz;
}
ERROR_INFO, *LPERROR_INFO;

static int CompareErrors(const void *lp1, const void *lp2);
static void SortErrorTable(LPERROR_INFO lpErrorTable,int nTableSize);
static LPCSTR SearchErrorTable(LPERROR_INFO lpErrorTable,int nTableSize,HRESULT hValue);
#include "ErrorCodes.h"


C$$Root$$MAPIApp::C$$Root$$MAPIApp()
{
	HRESULT		hResult = S_OK;
	
$$IF(PROJTYPE_NTSERVICE)
	MAPIINIT_0	structMAPIInit = {0, MAPI_NT_SERVICE};
$$ELSE
	MAPIINIT_0 structMAPIInit = {0, 0};
$$ENDIF

	m_bIsInitialized = FALSE;
	m_lpMAPISession = NULL;

	if (!m_bIsInitialized)
	{
		hResult = MAPIInitialize(&structMAPIInit);

		if (HR_FAILED(hResult))
			m_bIsInitialized = FALSE;
		else
			m_bIsInitialized = TRUE;

		//
		//	Sort the table of error codes.
		//
		//	Implementation note: the error table sorting only
		//	needs to be done once, but by placing the
		//	SortErrorTable call here we leave open the
		//	possibility that it might be called multiple
		//	times, i.e. whenever MAPI needs to be initialized.
		//	This should not be a problem, except in the
		//	unlikely case that MAPI is being frequently
		//	uninitialized then reinitialized.
		//

		SortErrorTable(rgMAPIErrorCodes,constMAPIErrorCodesTableSize);
	}

	if (m_lpMAPISession == NULL)
	{
		LPSTR	lpszLogonProfileName			= "$$PROFILE_NAME$$";
		LPSTR	lpszLogonProfilePassword		= NULL;
$$IF(PROJTYPE_NTSERVICE)
		FLAGS	fLogonFlags						= MAPI_EXPLICIT_PROFILE | 
												  MAPI_NEW_SESSION		|
												  MAPI_NT_SERVICE		|
												  MAPI_EXTENDED			|
												  MAPI_NO_MAIL;
$$ELSE
		FLAGS	fLogonFlags						= MAPI_EXPLICIT_PROFILE | 
												  MAPI_NEW_SESSION		|
												  MAPI_LOGON_UI			|
												  MAPI_EXTENDED			|
												  MAPI_NO_MAIL;
$$ENDIF

		hResult = MAPILogonEx(0,
							  lpszLogonProfileName,
							  lpszLogonProfilePassword,
							  fLogonFlags,
							  &m_lpMAPISession
							  );
	}

	m_hConstructorResult = hResult;
}



C$$Root$$MAPIApp::~C$$Root$$MAPIApp()
{
	//
	//	Logoff and release the MAPI session if one exists.
	//

	if (m_lpMAPISession != NULL)
	{
		m_lpMAPISession->Logoff(0,0,0);
		m_lpMAPISession->Release();
		m_lpMAPISession = NULL;
	}
	
	//
	//	Uninitialize MAPI.
	//

	if (m_bIsInitialized)
	{
		MAPIUninitialize();
	}
}

//----------------------------------------------------------------------

//
//	Error lookup functions.
//

LPCSTR C$$Root$$MAPIApp::TranslateErrorCode(HRESULT hResult)
{
	return (SearchErrorTable(rgMAPIErrorCodes,constMAPIErrorCodesTableSize,hResult));
}

static void SortErrorTable(LPERROR_INFO lpErrorTable,int nTableSize)
{
	qsort(lpErrorTable,nTableSize,sizeof(ERROR_INFO),CompareErrors);
}

static LPCSTR SearchErrorTable(LPERROR_INFO lpErrorTable,int nTableSize,HRESULT hValue)
{
	ERROR_INFO		structErrInfo;
	LPERROR_INFO	lpRetVal;

	structErrInfo.hValue = hValue;

	lpRetVal = (LPERROR_INFO)bsearch(&structErrInfo,lpErrorTable,nTableSize,sizeof(ERROR_INFO),CompareErrors);

	if (lpRetVal == NULL)
		return(NULL);
	else
		return(lpRetVal->lpsz);
}

static int CompareErrors(const void *lp1, const void *lp2)
{
	LPERROR_INFO		lpErr1 = (LPERROR_INFO)lp1;
	LPERROR_INFO		lpErr2 = (LPERROR_INFO)lp2;

	if (lpErr1->hValue > lpErr2->hValue)
		return(1);
	else
	if (lpErr1->hValue == lpErr2->hValue)
		return(0);
	else
		return(-1);
}
