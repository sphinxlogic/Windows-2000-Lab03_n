// EventViewer.cpp : Implementation of CEventViewer
#include "stdafx.h"
#include "Util_EventViewer.h"
#include "EventViewer.h"

/////////////////////////////////////////////////////////////////////////////
// CEventViewer

STDMETHODIMP CEventViewer::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEventViewer,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEventViewer::AddLog(BSTR bstrSource, BSTR bstrString, long lEventType, long lCategory, long lEventID)
{

	HANDLE hEventLog;
	WORD wType;
	WORD wCategory;
	DWORD dwEventID;
	PSID lpUserSid;
	WORD wNumStrings;
	DWORD dwDataSize;
	LPCTSTR lpStrings;
	LPVOID lpRawData;

	// bstrSource must be  a subkey of
	// HKLM\System\CurrentControlSet\Services\EventLog\Application

	DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR szBuffer [MAX_COMPUTERNAME_LENGTH + 1];
	LPTSTR lpBuf = szBuffer;
	LPDWORD nSize = &dwSize;
	::GetComputerName (lpBuf, nSize);

	TCHAR szSource [4096];
	wsprintf (szSource, _TEXT("%ws"), bstrSource);
	LPCTSTR lpBuffer = szBuffer;
	LPCTSTR lpSource = szSource;
	hEventLog = RegisterEventSource (lpBuffer, lpSource);

	// Event type
	// Choose from:
	//EVENTLOG_SUCCESS                0x0000
	//EVENTLOG_ERROR_TYPE             0x0001
	//EVENTLOG_WARNING_TYPE           0x0002
	//EVENTLOG_INFORMATION_TYPE       0x0004
	//EVENTLOG_AUDIT_SUCCESS          0x0008
	//EVENTLOG_AUDIT_FAILURE          0x0010
	wType = (WORD) lEventType;

	// Event category
	// Source specific
	wCategory = (WORD) lCategory;

	// Event identifier
	// Source specific
	dwEventID = (WORD) lEventID;

	// User security identifier
	// NULL if no security
	lpUserSid = NULL;

	// Num strings - only one for now
	wNumStrings = 1;

	// Size of data - not implemented
	dwDataSize = 0;

	// Pointer to strings - use string given by user
	TCHAR szString [4096];
	wsprintf (szString, _TEXT("%ws"), bstrString);
	lpStrings = szString;
	
	// Address of data - not implemented
	lpRawData = NULL;

	BOOL lRetVal;
	lRetVal = ::ReportEvent (hEventLog, wType, wCategory, dwEventID, 
		lpUserSid, wNumStrings, dwDataSize, &lpStrings, lpRawData);

	return (lRetVal ? S_OK : E_FAIL);
}
