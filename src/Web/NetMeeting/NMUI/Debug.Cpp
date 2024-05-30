//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       DEBUG.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"


#define STRING_CASE(val)               case val: pcsz = #val; break

//****************************************************************************
//
// LPCTSTR GetHrSz(HRESULT hr)
//
//****************************************************************************

LPCTSTR GetHrSz(HRESULT hr)
{
	LPCTSTR pcsz;
	static TCHAR _szHRESULT[] = "0x12345678";

	switch (hr)
		{
	STRING_CASE(S_OK);
	STRING_CASE(S_FALSE);

	STRING_CASE(NM_E_NOT_INITIALIZED);
	STRING_CASE(NM_E_CHANNEL_ALREADY_EXISTS);
	STRING_CASE(NM_E_NO_T120_CONFERENCE);
	STRING_CASE(NM_E_NOT_ACTIVE);

	STRING_CASE(DRAGDROP_S_CANCEL);
	STRING_CASE(DRAGDROP_S_DROP);
	STRING_CASE(DRAGDROP_S_USEDEFAULTCURSORS);

	STRING_CASE(E_UNEXPECTED);
	STRING_CASE(E_NOTIMPL);
	STRING_CASE(E_OUTOFMEMORY);
	STRING_CASE(E_INVALIDARG);
	STRING_CASE(E_NOINTERFACE);
	STRING_CASE(E_POINTER);
	STRING_CASE(E_HANDLE);
	STRING_CASE(E_ABORT);
	STRING_CASE(E_FAIL);
	STRING_CASE(E_ACCESSDENIED);

	STRING_CASE(CLASS_E_NOAGGREGATION);

	STRING_CASE(CO_E_NOTINITIALIZED);
	STRING_CASE(CO_E_ALREADYINITIALIZED);
	STRING_CASE(CO_E_INIT_ONLY_SINGLE_THREADED);

	STRING_CASE(REGDB_E_INVALIDVALUE);
	STRING_CASE(REGDB_E_CLASSNOTREG);
	STRING_CASE(REGDB_E_IIDNOTREG);

	STRING_CASE(DV_E_DVASPECT);
	STRING_CASE(DV_E_LINDEX);
	STRING_CASE(DV_E_TYMED);
	STRING_CASE(DV_E_FORMATETC);

	default:
		wsprintf(_szHRESULT, TEXT("%#lx"), hr);
		pcsz = _szHRESULT;
		break;
		}

	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetConfnSz(CONFN confn)
//
//****************************************************************************

LPCTSTR GetConfnSz(CONFN confn)
{
	LPCTSTR pcsz;
	static TCHAR _szMsg[256];

	switch (confn)
		{
	STRING_CASE(CONFN_FT_UI);
	STRING_CASE(CONFN_FT_OFFERED);
	STRING_CASE(CONFN_FT_STARTED);
	STRING_CASE(CONFN_FT_PROGRESS);
	STRING_CASE(CONFN_FT_COMPLETE);
	STRING_CASE(CONFN_FT_CANCELED);
	
	STRING_CASE(CONFN_CALL_INCOMPATIBLE);
	STRING_CASE(CONFN_CALL_OLDER);
	STRING_CASE(CONFN_CALL_NEWER);
	STRING_CASE(CONFN_CALL_IGNORED);
	STRING_CASE(CONFN_CALL_FAILED);
	STRING_CASE(CONFN_CALL_IN_CONFERENCE);

	STRING_CASE(CONFN_NM_STARTED);
	STRING_CASE(CONFN_NM_STOPPED);

	default:
		wsprintf(_szMsg, TEXT("CONFN_%08X"), confn);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetNmchSz(ULONG uch)
//
//****************************************************************************

LPCTSTR GetNmchSz(ULONG uch)
{
	LPCTSTR pcsz;
	static TCHAR _szMsg[256];

	switch (uch)
		{
	case NMCH_DATA:  pcsz = TEXT("Data");  break;
	case NMCH_AUDIO: pcsz = TEXT("Audio"); break;
	case NMCH_VIDEO: pcsz = TEXT("Video"); break;
	case NMCH_SHARE: pcsz = TEXT("Share"); break;
	case NMCH_FT:    pcsz = TEXT("Ft");    break;
	
	case NMCH_ALL:
	case NMCH_NONE:
	default:
		wsprintf(_szMsg, TEXT("%04X"), uch);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetCallStateSz(NM_CALL_STATE uState)
//
//****************************************************************************

LPCTSTR GetCallStateSz(NM_CALL_STATE uState)
{
	LPCTSTR pcsz;
	static TCHAR _szMsg[256];

	switch (uState)
		{
	STRING_CASE(NM_CALL_INVALID);
	STRING_CASE(NM_CALL_INIT);
	STRING_CASE(NM_CALL_RING);
	STRING_CASE(NM_CALL_SEARCH);
	STRING_CASE(NM_CALL_WAIT);
	STRING_CASE(NM_CALL_ACCEPTED);
	STRING_CASE(NM_CALL_REJECTED);
	STRING_CASE(NM_CALL_CANCELED);

	default:
		wsprintf(_szMsg, TEXT("NM_CALL_%04X"), uState);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetConferenceStateSz(NM_CONFERENCE_STATE uState)
//
//****************************************************************************

LPCTSTR GetConferenceStateSz(NM_CONFERENCE_STATE uState)
{
	LPCTSTR pcsz;
	static TCHAR _szMsg[256];

	switch (uState)
		{
	STRING_CASE(NM_CONFERENCE_IDLE);
	STRING_CASE(NM_CONFERENCE_WAITING);
	STRING_CASE(NM_CONFERENCE_INITIALIZING);
	STRING_CASE(NM_CONFERENCE_ACTIVE);

	default:
		wsprintf(_szMsg, TEXT("NM_CONFERENCE_%04X"), uState);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}

//****************************************************************************
//
// VOID FAR PASCAL AssertProc(LPSTR lpszMsg, LPSTR lpszAssert, LPSTR lpszFile, UINT line)
//
//****************************************************************************

VOID FAR PASCAL AssertProc(LPSTR lpszMsg, LPSTR lpszAssert, LPSTR lpszFile, UINT line)
{
	int  id;
	TCHAR szBuffer[1024]; // a big buffer

	wsprintf((LPSTR)szBuffer,
		"Assert: %s\nFile %s, Line %d",
		(lpszMsg && *lpszMsg) ? lpszMsg  : lpszAssert,
		lpszFile ? lpszFile : "", line);

	OutputDebugString(szBuffer);

	do {
		id = MessageBox(NULL, (LPSTR)szBuffer, TEXT("NmUi Assert"),
					MB_ICONHAND | MB_ABORTRETRYIGNORE | MB_SYSTEMMODAL);

		switch (id)
		{
		case IDRETRY:
			DebugBreak();
			break;
		case IDABORT:
			FatalAppExit(0, (LPSTR)szBuffer);
			break;
		case IDIGNORE:
		default:
			break;
		}
	} while (id == IDRETRY);
}


//****************************************************************************
//
// VOID Log(COLORREF cv, LPTSTR pszMsg)
//
//****************************************************************************

VOID Log(COLORREF cv, LPTSTR pszMsg)
{
	int iItem;
	iItem = SendMessage(ghwndMsg, LB_ADDSTRING, 0, (LPARAM) pszMsg);

	SendMessage(ghwndMsg, LB_SETITEMDATA, (WPARAM)iItem, (LPARAM) cv);

	PostMessage(ghwndMsg, WM_VSCROLL, SB_BOTTOM, 0);
}

//****************************************************************************
//
// VOID ClearLog(void)
//
//****************************************************************************

VOID ClearLog(void)
{
	SendMessage(ghwndMsg, LB_RESETCONTENT, 0, 0);
}


//****************************************************************************
//
// VOID TraceMsg(PSTR pszFormat,...)
//
//****************************************************************************

VOID TraceMsg(PSTR pszFormat,...)
{
	TCHAR szMsg[1024];
	va_list v1;
	
	va_start(v1, pszFormat);
	wvsprintfA(szMsg, pszFormat, v1);
	va_end(v1);

	Log(RGB(0, 0, 0), szMsg);

	lstrcat(szMsg, "\r\n");
	OutputDebugString(szMsg);
}


//****************************************************************************
//
// VOID WarnMsg(PSTR pszFormat,...)
//
//****************************************************************************

VOID WarnMsg(PSTR pszFormat,...)
{
	TCHAR szMsg[1024];
	va_list v1;
	
	va_start(v1, pszFormat);
	wvsprintfA(szMsg, pszFormat, v1);
	va_end(v1);

	Log(RGB(0, 0, 255), szMsg);

	lstrcat(szMsg, "\r\n");
	OutputDebugString(szMsg);
}


//****************************************************************************
//
// VOID ErrorMsg(PSTR pszFormat,...)
//
//****************************************************************************

VOID ErrorMsg(PSTR pszFormat,...)
{
	TCHAR szMsg[1024];
	va_list v1;
	
	va_start(v1, pszFormat);
	wvsprintfA(szMsg, pszFormat, v1);
	va_end(v1);

	Log(RGB(255, 0, 0), szMsg);

	lstrcat(szMsg, "\r\n");
	OutputDebugString(szMsg);
}


//****************************************************************************
//
// VOID LogMsg(COLORREF cv, PSTR pszFormat,...)
//
//****************************************************************************

VOID LogMsg(COLORREF cv, PSTR pszFormat,...)
{
	TCHAR szMsg[1024];
	va_list v1;
	
	va_start(v1, pszFormat);
	wvsprintfA(szMsg, pszFormat, v1);
	va_end(v1);

	Log(cv, szMsg);

	lstrcat(szMsg, "\r\n");
	OutputDebugString(szMsg);
}


//****************************************************************************
//
// VOID DumpCallInfo(INmCall * pCall)
//
//****************************************************************************

VOID DumpCallInfo(INmCall * pCall)
{
	HRESULT hr;
	BSTR bstrName;
	BSTR bstrAddr;
	NM_ADDR_TYPE uType;
	NM_CALL_STATE uState;
	INmConference * pConference = NULL;

	OBJECT_MSG("[%08X] - dump call info", pCall);
	if (NULL == pCall)
	{
		ERROR_MSG("DumpCallInfo: Invalid Call");
		return;
	}

	hr = pCall->GetName(&bstrName);
	if (FAILED(hr))
	{
		bstrName = NULL;
    	ERROR_MSG("DumpCallInfo: GetName failed");
	}

	if (FAILED(pCall->GetAddr(&bstrAddr, &uType)))
	{
		bstrAddr = NULL;
		uType = NM_ADDR_UNKNOWN; 
    	ERROR_MSG("DumpCallInfo: GetAddr failed");
	}

    if (FAILED(pCall->GetState(&uState)))
    {
		uState = NM_CALL_INVALID; 
    	ERROR_MSG("DumpCallInfo: GetState failed");
    }

	hr = pCall->GetConference(&pConference);
	if (FAILED(hr))
	{
    	WARN_MSG("DumpCallInfo: GetConference failed %s", GetHrSz(hr));
	}

	TRACE_MSG("Call=[%s] Addr=[%s], Type=%d, State=%s %s conf=%08X",
		(LPTSTR) BTSTR(bstrName), (LPTSTR) BTSTR(bstrAddr),
		uType, GetCallStateSz(uState),
		(S_OK == pCall->IsIncoming()) ? TEXT("(Incoming)") : TEXT(""), pConference);

	if (NULL != pConference)
	{
		pConference->Release();
	}

	SysFreeString(bstrName);
	SysFreeString(bstrAddr);
}


//****************************************************************************
//
// VOID DumpAllCalls(void)
//
//****************************************************************************

VOID DumpAllCalls(void)
{
	if (NULL == g_pListCall)
		return;

	for (POSITION pos = g_pListCall->GetHeadPosition(); NULL != pos; )
	{
		INmCall * pCall = (INmCall *) g_pListCall->GetNext(pos);
		DumpCallInfo(pCall);
	}
}


//****************************************************************************
//
// VOID DumpConferenceInfo(INmConference * pConference)
//
//****************************************************************************

VOID DumpConferenceInfo(INmConference * pConference)
{
	HRESULT hr;
	BSTR bstr;
	ULONG cMember;
	ULONG cChannel;
	NM_CONFERENCE_STATE uState;

	if (NULL == pConference)
	{
		ERROR_MSG("DumpConferenceInfo: Invalid conference");
		return;
	}

	hr = pConference->GetName(&bstr);
	if (FAILED(hr))
	{
		ERROR_MSG("GetName failed");
		bstr = NULL;
	}
	
	hr = pConference->GetState(&uState);
	if (FAILED(hr))
	{
		ERROR_MSG("GetState failed?");
	}
	
	hr = pConference->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
		ERROR_MSG("GetMemberCount failed");
		cMember = 0;
	}
	
	hr = pConference->GetChannelCount(&cChannel);
	if (FAILED(hr))
	{
		ERROR_MSG("GetChannelCount failed");
		cChannel = 0;
	}
	
	TRACE_MSG("[%08X] - Conference=[%s] state=%s", pConference,
		(LPTSTR) BTSTR(bstr), GetConferenceStateSz(uState));
	TRACE_MSG("  MemberCount=%d, ChannelCount=%d", cMember, cChannel);

	SysFreeString(bstr);
}


//****************************************************************************
//
// VOID DumpMemberInfo(INmMember * pMember)
//
//****************************************************************************

VOID DumpMemberInfo(INmMember * pMember)
{
	HRESULT hr;
	BSTR bstr;
	BOOL fLocal;
	BOOL fMcu;
	BOOL fTop;
	ULONG uchCaps;
	ULONG uVer;
	INmConference * pConference;

	hr = pMember->GetName(&bstr);
	if (FAILED(hr))
	{
		ERROR_MSG("Problem with GetName");
	}

	hr = pMember->GetNmchCaps(&uchCaps);
	if (FAILED(hr))
	{
		ERROR_MSG("Problem with GetNmchCaps");
		uchCaps = 0;
	}

	hr = pMember->GetNmVersion(&uVer);
	if (FAILED(hr))
	{
		ERROR_MSG("Problem with GetNmVersion");
		uVer = 0;
	}

	fLocal = S_OK == pMember->IsSelf();
	fMcu = S_OK == pMember->IsMCU();

	fTop = FALSE;
	hr = pMember->GetConference(&pConference);
	if (FAILED(hr))
	{
		TRACE_MSG("Problem with GetConference");
	}
	else
	{
		INmMember * pMemberTop;
		if (SUCCEEDED(pConference->GetTopProvider(&pMemberTop)))
		{
			fTop = (pMember == pMemberTop);
			pMemberTop->Release();
		}
		pConference->Release();
	}

	TRACE_MSG("[%08X] Member=[%s] ", pMember, (LPTSTR) BTSTR(bstr));
	TRACE_MSG("  Local=%d, MCU=%d, Top=%d, uch=%08X, version=%d", fLocal, fMcu, fTop, uchCaps, uVer);

	SysFreeString(bstr);
}


//****************************************************************************
//
// VOID DumpChannelInfo(INmChannel * pChannel)
//
//****************************************************************************

VOID DumpChannelInfo(INmChannel * pChannel)
{
	HRESULT hr;
	ULONG uch;
	ULONG cMember;

	hr = pChannel->GetNmch(&uch);
	if (FAILED(hr))
	{
		ERROR_MSG("GetNmch failed");
		uch = 0;
	}
	
	hr = pChannel->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
		ERROR_MSG("GetMemberCount failed");
		cMember = 0;
	}

	TRACE_MSG("[%08X] - Channel=[%s] MemberCount=%d", pChannel, GetNmchSz(uch), cMember);
	switch (uch)
		{
	case NMCH_AUDIO:
	{
		INmChannelAudio * pChannelAudio;
		hr = pChannel->QueryInterface(IID_INmChannelAudio, (void **)&pChannelAudio);
		if (FAILED(hr))
		{
			ERROR_MSG("Not an audio channel?");
		}
		else
		{
			NM_AUDIO_STATE uState;
			pChannelAudio->GetState(&uState);
			TRACE_MSG("Audio State: %d", uState);
			pChannelAudio->Release();
		}
		break;
	}

	case NMCH_VIDEO:
	{
		INmChannelVideo * pChannelVideo;
		hr = pChannel->QueryInterface(IID_INmChannelVideo, (void **)&pChannelVideo);
		if (FAILED(hr))
		{
			ERROR_MSG("Not an video channel?");
		}
		else
		{
			NM_VIDEO_STATE uState;
			pChannelVideo->GetState(&uState);
			TRACE_MSG("Video State: %d (%s)", uState,
				(S_OK == pChannelVideo->IsActive()) ? TEXT("Active") : TEXT("Inactive"));
			pChannelVideo->Release();
		}
		break;
	}

	case NMCH_DATA:
	{
		INmChannelData * pChannelData;
		hr = pChannel->QueryInterface(IID_INmChannelData, (void **)&pChannelData);
		if (FAILED(hr))
		{
			ERROR_MSG("Not a data channel?");
		}
		else
		{
			TRACE_MSG("Data channel is %s",
				(S_OK == pChannelData->IsActive()) ? TEXT("Active") : TEXT("Inactive"));
			pChannelData->Release();
		}
		break;
	}
	default:
		break;
		}
}

//****************************************************************************
//
// VOID DoEnumChannelMember(INmChannel * pChannel)
//
//****************************************************************************

VOID DoEnumChannelMember(INmChannel * pChannel)
{
	HRESULT hr;
	IEnumNmMember * pEnum;
	ULONG cFetched;
	ULONG cMember;

	ASSERT(NULL != pChannel);

	hr = pChannel->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
    	ERROR_MSG("GetMemberCount Failed (%s)", GetHrSz(hr));
    	return;
	}
	TRACE_MSG("%d members in channel (%08X)", cMember, pChannel);

	if (0 == cMember)
		return;

	if (cMember > 10)
		cMember = 10;

	hr = pChannel->EnumMember(&pEnum);
	if (FAILED(hr))
	{
    	ERROR_MSG("EnumMember Failed (%s)", GetHrSz(hr));
    	return;
	}

	INmMember * rgpMember[10];
	hr = pEnum->Next(cMember, rgpMember, &cFetched);
	if (FAILED(hr))
	{
    	ERROR_MSG("EnumMember Failed (%s)", GetHrSz(hr));
	}
	else
	{
		for (UINT iMember = 0; iMember < cFetched; iMember++)
		{
			DumpMemberInfo(rgpMember[iMember]);
			rgpMember[iMember]->Release();
		}
	}

	pEnum->Release();

}


//****************************************************************************
//
// VOID DoEnumConferenceMember(INmConference * pConference)
//
//****************************************************************************

VOID DoEnumConferenceMember(INmConference * pConference)
{
	HRESULT hr;
	IEnumNmMember * pEnum;
	ULONG cFetched;
	ULONG cMember;

	ASSERT(NULL != pConference);
	hr = pConference->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
    	ERROR_MSG("GetMemberCount Failed (%s)", GetHrSz(hr));
    	return;
	}
	TRACE_MSG("%d members in conference (%08X)", cMember, pConference);

	if (cMember > 10)
		cMember = 10;

	hr = pConference->EnumMember(&pEnum);
	if (FAILED(hr))
	{
    	ERROR_MSG("EnumMember Failed (%s)", GetHrSz(hr));
    	return;
	}

	INmMember * rgpMember[10];
	hr = pEnum->Next(cMember, rgpMember, &cFetched);
	if (FAILED(hr))
	{
    	ERROR_MSG("EnumMember Failed (%s)", GetHrSz(hr));
	}
	else
	{
		for (UINT iMember = 0; iMember < cFetched; iMember++)
		{
			DumpMemberInfo(rgpMember[iMember]);
			rgpMember[iMember]->Release();
		}
	}

	pEnum->Release();
}


//****************************************************************************
//
// VOID DoEnumAll(void)
//
//****************************************************************************

VOID DoEnumAll(void)
{
	HRESULT hr;
	IEnumNmChannel * pEnum;
	ULONG cFetched;
	ULONG cChannel;
	INmConference * pConference = GetCurrentConference();

	if (NULL == pConference)
	{
		TRACE_MSG("No current conference");
		return;
	}

	DumpConferenceInfo(pConference);

	DoEnumConferenceMember(pConference);

	hr = pConference->GetChannelCount(&cChannel);
	if (FAILED(hr))
	{
    	ERROR_MSG("GetChannelCount Failed (%s)", GetHrSz(hr));
    	return;
	}
	TRACE_MSG("%d channels in conference", cChannel);

	if (cChannel > 10)
		cChannel = 10;

	hr = pConference->EnumChannel(&pEnum);
	if (FAILED(hr))
	{
    	ERROR_MSG("EnumChannel Failed (%s)", GetHrSz(hr));
    	return;
	}

	INmChannel * rgpChannel[10];
	hr = pEnum->Next(cChannel, rgpChannel, &cFetched);
	if (FAILED(hr))
	{
    	ERROR_MSG("EnumMember Failed (%s)", GetHrSz(hr));
	}
	else
	{
		for (UINT iChannel = 0; iChannel < cFetched; iChannel++)
		{
			DumpChannelInfo(rgpChannel[iChannel]);
			DoEnumChannelMember(rgpChannel[iChannel]);
			rgpChannel[iChannel]->Release();
		}
	}

	pEnum->Release();
}


