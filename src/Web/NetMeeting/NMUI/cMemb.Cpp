//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CMEMB.CPP
//  Content:    INmMember Routines
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

COBLIST * g_pListUser = (COBLIST *) NULL;

UINT gcUsers = 0;


//****************************************************************************
//
// PUSER PUserFromINmMember(INmMember * pMember)
//
//****************************************************************************

PUSER PUserFromINmMember(INmMember * pMember)
{
	if (NULL != g_pListUser)
	{
		POSITION pos = g_pListUser->GetHeadPosition();
		while (NULL != pos)
		{
			PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
			if (pMember == pUser->pMember)
				return pUser;
		}
	}

	return NULL;
}


//****************************************************************************
//
// int ItemFromPUser(PUSER pUser)
//
//****************************************************************************

int ItemFromPUser(PUSER pUser)
{
	if (NULL == ghwndLView)
		return -1;

	LV_FINDINFO findInfo;
	ClearStruct(&findInfo);
	findInfo.flags = LVFI_PARAM;
    findInfo.lParam = (LPARAM) pUser; 
    return ListView_FindItem(ghwndLView, -1, &findInfo);
}


//****************************************************************************
//
// PUSER PUserLocal()
//
// Return a pointer to the local user information
//
//****************************************************************************

PUSER PUserLocal()
{
	if (NULL != g_pListUser)
	{
		POSITION pos = g_pListUser->GetHeadPosition();
		while (NULL != pos)
		{
			PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
			if (pUser->fLocal)
				return pUser;
		}
	}

	return NULL;
}

//****************************************************************************
//
// VOID UpdateUserDisplay(PUSER pUser)
//
//****************************************************************************

VOID UpdateUserDisplay(PUSER pUser)
{
	int iItem = ItemFromPUser(pUser);
	TCHAR sz[MAX_PATH];

	ASSERT(NULL != ghwndLView);

	wsprintf(sz, "%d", pUser->uVersion);
	ListView_SetItemText(ghwndLView, iItem, ILV_VERSION, sz);
	
	wsprintf(sz, "%d", pUser->fMcu);
	ListView_SetItemText(ghwndLView, iItem, ILV_MCU, sz);

	wsprintf(sz, "%d", pUser->fLocal);
	ListView_SetItemText(ghwndLView, iItem, ILV_LOCAL, sz);

	wsprintf(sz, "%X", pUser->m_pChannelAudio);
	ListView_SetItemText(ghwndLView, iItem, ILV_AUDIO, sz);

	wsprintf(sz, "%X", pUser->m_pChannelVideo);
	ListView_SetItemText(ghwndLView, iItem, ILV_VIDEO, sz);

	wsprintf(sz, "%X", pUser->m_pChannelAs);
	ListView_SetItemText(ghwndLView, iItem, ILV_AS, sz);

	wsprintf(sz, "%X", pUser->m_pChannelFt);
	ListView_SetItemText(ghwndLView, iItem, ILV_FT, sz);

	wsprintf(sz, "%08X", pUser->uchCaps);
	ListView_SetItemText(ghwndLView, iItem, ILV_CAPS, sz);

	ListView_SetItemText(ghwndLView, iItem, ILV_ADDR,
		(NULL == pUser->pszAddr) ? TEXT("?") : pUser->pszAddr);

	wsprintf(sz, "%08X", pUser->uId);
	ListView_SetItemText(ghwndLView, iItem, ILV_ID, sz);

}

//****************************************************************************
//
// VOID UpdateUserCount(void)
//
//****************************************************************************

VOID UpdateUserCount(void)
{
	TCHAR sz[MAX_PATH];

	if (1 == gcUsers)
		lstrcpy(sz, TEXT("1 user"));
	else
		wsprintf(sz, TEXT("%d users"), gcUsers);

	UpdateStatusBar(sz, IDSBP_USERCOUNT, 0);
}


//****************************************************************************
//
// PUSER AllocUser(INmMember * pMember)
//
//****************************************************************************

PUSER AllocUser(INmMember * pMember)
{
	HRESULT hr;
	BSTR bstr;
	INmConference * pConference;

	PUSER pUser = new USER;
	if (NULL == pUser)
	{
		return NULL;
	}
	ClearStruct(pUser);
	pUser->pMember = pMember;
	pMember->AddRef();

	hr = pMember->GetName(&bstr);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetName");
	}
	else
	{
		pUser->pszName = PszFromBstr(bstr);
		SysFreeString(bstr);
	}

	hr = pMember->GetAddr(&bstr, &pUser->uType);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetAddr");
	}
	else
	{
		pUser->pszAddr = PszFromBstr(bstr);
		SysFreeString(bstr);
	}

	hr = pMember->GetNmchCaps(&pUser->uchCaps);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetNmchCaps");
		pUser->uchCaps = 0;
	}

	hr = pMember->GetNmVersion(&pUser->uVersion);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetNmVersion");
		pUser->uVersion = 0;
	}

	hr = pMember->GetID(&pUser->uId);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetID");
		pUser->uId = 0;
	}

	pUser->fLocal = S_OK == pMember->IsSelf();
	pUser->fMcu = S_OK == pMember->IsMCU();
	pUser->fTop = FALSE;
	hr = pMember->GetConference(&pConference);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetConference");
	}
	else
	{
		INmMember * pMemberTop;
		if (SUCCEEDED(pConference->GetTopProvider(&pMemberTop)))
		{
			pUser->fTop = (pMember == pMemberTop);
			pMemberTop->Release();
		}
		pConference->Release();
	}

	return pUser;
}

//****************************************************************************
//
// VOID FreeUser(PUSER pUser)
//
//****************************************************************************

VOID FreeUser(PUSER pUser)
{
	ASSERT(NULL != pUser);

	FreePlpv(&pUser->pszName);
	FreePlpv(&pUser->pszAddr);
	
	if (NULL != pUser->pMember)
	{
		OBJECT_MSG("[%08X] member released", pUser->pMember);
		pUser->pMember->Release();
	}
}


//****************************************************************************
//
// VOID FreeAllUsers(void)
//
//****************************************************************************

VOID FreeAllUsers(void)
{
	if (NULL != g_pListUser)
	{
		while (!g_pListUser->IsEmpty())
		{
			RemoveMember(((PUSER) g_pListUser->GetHead())->pMember);
		}
	}
}

//****************************************************************************
//
// VOID AddMember(INmMember * pMember)
//
//****************************************************************************

VOID AddMember(INmMember * pMember)
{
	PUSER pUser = AllocUser(pMember);
	if (NULL == pUser)
	{
		return;
	}
	
	AddNode(pUser, &g_pListUser);

	LV_ITEM  lvItem;
	ClearStruct(&lvItem);
	lvItem.iItem = gcUsers;
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.pszText = pUser->pszName;
	lvItem.cchTextMax = lstrlen(pUser->pszName);
	lvItem.lParam = (LPARAM) pUser;
	ListView_InsertItem(ghwndLView, &lvItem);

	gcUsers++;
	UpdateUserCount();
	UpdateUserDisplay(pUser);

	AddUserToUList(pUser, ghwndUList, FALSE);
}

//****************************************************************************
//
// VOID RemoveMember(INmMember * pMember)
//
//****************************************************************************

VOID RemoveMember(INmMember * pMember)
{
	if (NULL == g_pListUser)
		return;

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		POSITION posSav = pos;
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		if (pMember == pUser->pMember)
		{
			RemoveUserFromUList(pUser, ghwndUList);
			ListView_DeleteItem(ghwndLView, ItemFromPUser(pUser));
			FreeUser(pUser);
			g_pListUser->RemoveAt(posSav);

			gcUsers--;
			UpdateUserCount();
			return;
		}
	}
}

//****************************************************************************
//
// VOID UpdateUserChannel(PUSER pUser, INmChannel * pChannel, NM_MEMBER_NOTIFY uNotify)
//
//****************************************************************************

VOID UpdateUserChannel(PUSER pUser, INmChannel * pChannel, NM_MEMBER_NOTIFY uNotify)
{
	ULONG uch;
	PVOID *ppChannel = NULL;
	
	ASSERT(NULL != pChannel);

	if (FAILED(pChannel->GetNmch(&uch)))
	{
		return;
	}

	if (NM_MEMBER_ADDED == uNotify)
	{
	switch (uch)
		{
	case NMCH_AUDIO:
	{
		INmChannelAudio * pChannelAudio;
		if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelAudio, (PVOID *) &pChannelAudio)))
		{
			if ((S_OK == pChannelAudio->IsIncoming()) != pUser->fLocal)
			{
				ASSERT((NULL == pUser->m_pChannelAudio) || (pChannelAudio == pUser->m_pChannelAudio));
				// This is non-standard - we're storing a pointer to the specific channel,
				// yet keeping a lock on the generic channel - weird....
				pUser->m_pChannelAudio = pChannelAudio;
			}
			pChannelAudio->Release();
		}
		break;
	}
	case NMCH_VIDEO:
	{
		INmChannelVideo * pChannelVideo;
		if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelVideo, (PVOID *) &pChannelVideo)))
		{
			if ((S_OK == pChannelVideo->IsIncoming()) != pUser->fLocal)
			{
				ASSERT((NULL == pUser->m_pChannelVideo) || (pChannelVideo == pUser->m_pChannelVideo));
				pUser->m_pChannelVideo = pChannelVideo;
			}
			pChannelVideo->Release();
		}
		break;
	}
	case NMCH_SHARE:
		if (NULL == pUser->m_pChannelAs)
		{
			INmChannelAppShare * pChannelAs;
			if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelAppShare, (PVOID *) &pChannelAs)))
			{
				pUser->m_pChannelAs = pChannelAs;
				pChannelAs->Release();
			}
		}
		break;
	case NMCH_FT:
		if (NULL == pUser->m_pChannelFt)
		{
			INmChannelFt * pChannelFt;
			if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelFt, (PVOID *) &pChannelFt)))
			{
				pUser->m_pChannelFt = pChannelFt;
				pChannelFt->Release();
			}
		}
		break;
	case NMCH_DATA:
		ppChannel = (PVOID *) &(pUser->m_pChannelData);
		break;
	case NMCH_NONE:
	case NMCH_ALL:
	default:
		break;
		}
	} /* CONFN_MEMBER_ADDED */

	UpdateUserDisplay(pUser);
}


//****************************************************************************
//
// VOID UpdateUserInfo(PUSER pUser)
//
//****************************************************************************

VOID UpdateUserInfo(PUSER pUser)
{
	ULONG   ul;
	HRESULT hr;
	LPTSTR  psz;
	BSTR    bstr;
	INmMember * pMember = pUser->pMember;

	hr = pMember->GetName(&bstr);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetName");
	}
	else
	{
		psz = PszFromBstr(bstr);
		SysFreeString(bstr);

		if (0 != lstrcmp(pUser->pszName, psz))
		{
			WARN_MSG("Replacing Name [%s] => [%s]", pUser->pszName, psz);
		}
		FreePlpv(&pUser->pszName);
		pUser->pszName = psz;
	}

	hr = pMember->GetAddr(&bstr, &pUser->uType);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetAddr");
	}
	else
	{
		psz = PszFromBstr(bstr);
		SysFreeString(bstr);

		if (0 != lstrcmp(pUser->pszAddr, psz))
		{
			WARN_MSG("Replacing Addr [%s] => [%s]", pUser->pszAddr, psz);
		}
		FreePlpv(&pUser->pszAddr);
		pUser->pszAddr = psz;
	}

	hr = pMember->GetNmchCaps(&ul);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetNmchCaps");
		pUser->uchCaps = 0;
	}
	else if (pUser->uchCaps != ul)
	{
		WARN_MSG("Updating uchCaps [%08X] => [%08X]", pUser->uchCaps, ul);
		pUser->uchCaps = ul;
	}

	hr = pMember->GetNmVersion(&ul);
	if (FAILED(hr))
	{
		WARN_MSG("Problem with GetNmVersion");
		pUser->uVersion = 0;
	}
	else if (pUser->uVersion != ul)
	{
		WARN_MSG("Updating version [%08X] => [%08X]", pUser->uVersion, ul);
		pUser->uchCaps = ul;
	}

	
	if (pUser->fLocal != (S_OK == pMember->IsSelf()) )
	{
		ERROR_MSG("Local User status changed?");
	}

	if (pUser->fMcu != (S_OK == pMember->IsMCU()))
	{
		ERROR_MSG("MCU status changed?");
	}
}


//****************************************************************************
//
// VOID UpdateConfView(void)
//
//****************************************************************************

VOID UpdateConfView(void)
{
	if (NULL == g_pListUser)
		return;

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		UpdateUserInfo(pUser);
		UpdateUserDisplay(pUser);
	}
}

