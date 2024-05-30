
// --SuggestEvents.h------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _SUGGESTEVENTS_H_
#define _SUGGESTEVENTS_H_

#include "exevhandler.h"

class CSuggestEvents
{
public:
	CSuggestEvents();

	HRESULT OnChange(CExEvHandler* phndlr);
	HRESULT OnMessageDeleted(CExEvHandler* phndlr);
	HRESULT OnTimer(CExEvHandler* phndlr);
	HRESULT OnMessageCreated(CExEvHandler* phndlr);

	HRESULT SendMessage(LPMAPISESSION pSession,IABContainer* pAddrbook,LPSTR pSubject,LPSTR pBody,LPSPropValue pProps,LPSPropValue pSenderEIDProps);
	HRESULT SetOutGoingMessageProps(IMessage* pMessage, LPSTR pSubject,LPSTR pBody);
	HRESULT GetGal(LPMAPISESSION pSession, IABContainer** ppAddrBook);
	HRESULT GetDefMsgStore(LPMAPISESSION pMSession,LPMDB* ppStore);
};

#endif // _SUGGESTEVENTS_H_
