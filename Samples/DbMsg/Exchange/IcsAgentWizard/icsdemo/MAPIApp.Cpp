// MAPIApp.cpp: implementation of the CMAPIApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICSDemo.h"
#include "MAPIApp.h"

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

//
//	The static m_bIsInitialised and m_lpMAPISession
//	variables ensure that no matter how many instances
//	of CMAPIApp are created, initialization is only
//	performed once.
//
//	Defensive programming taken to the level of paranoia!
//

BOOL CMAPIApp::m_bIsInitialized = FALSE;
LPMAPISESSION CMAPIApp::m_lpMAPISession = NULL;

CMAPIApp::CMAPIApp()
{
	HRESULT		hResult = S_OK;
	
	MAPIINIT_0	structMAPIInit = {0,0};

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
		LPSTR	lpszLogonProfileName			=	NULL;
		LPSTR	lpszLogonProfilePassword	=	NULL;
		FLAGS	fLogonFlags						=	MAPI_EXPLICIT_PROFILE |
														MAPI_NEW_SESSION |
														MAPI_LOGON_UI |
														MAPI_EXTENDED |
														MAPI_NO_MAIL;

		hResult = MAPILogonEx(	0,
										lpszLogonProfileName,
										lpszLogonProfilePassword,
										fLogonFlags,
										&m_lpMAPISession);
	}

	m_hConstructorResult = hResult;
}

CMAPIApp::~CMAPIApp()
{
	//
	//	Logoff and release the MAPI session if one exists.
	//

	if (m_lpMAPISession != NULL)
	{
		m_lpMAPISession->Logoff(0,0,0);
		m_lpMAPISession->Release();
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

LPCSTR CMAPIApp::TranslateErrorCode(HRESULT hResult)
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
