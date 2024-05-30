// --ExEvHandler.cpp------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "exevhandler.h"
#include "suggestevents.h"
#include "propid.h"

#include "esconf_i.c"
#include "exchhndl_i.c"

// Define the Interfaces we will use
#define USES_IID_IMAPISession
#define USES_IID_IMsgStore
#define USES_IID_IMessage
#define USED_IID_IAddrBook
#define USES_IID_IABContainer
#define USES_IID_IDistList
#define USES_IID_IMAPITable
#define USES_IID_IMailUser

#define INITGUID        // Include only those IID's defined above
#include <initguid.h>
#include "mapiguid.h"

enum
{
	iPR_STORE_ENTRYID,
	iPR_PARENT_ENTRYID
};

/////////////////////////////////////////////////////////////////////////////
// CExEvHandler

// Implementation of ExecuteEvent (This will be called by the Event Service)
STDMETHODIMP CExEvHandler::ExecuteEvent(LPDISPATCH pSource)
{
	HRESULT			hr				=	S_OK;
	IEventSource*	pEventSource	=	NULL;
	DWORD			dwEventType		=	0;
	
	// Get the IEventSource Interface
	if(SUCCEEDED(hr = pSource->QueryInterface(IID_IEventSource, (void**)&pEventSource)))
	{
		// cache this pointer
		m_pEventSource = pEventSource;

		// Determine our Event Type
		if(SUCCEEDED(hr = GetEventType(&dwEventType)))
		{
			// We instantiate a instance of our events class 
			CSuggestEvents se;

			// Call appropriate function
			switch(dwEventType)
			{
			case Message_OnChange: 
				hr = se.OnChange(this);
				break;
			case Folder_OnMessageDeleted:
				hr = se.OnMessageDeleted(this);
				break;
			case Folder_OnTimer:
				hr = se.OnTimer(this);
				break;
			case Folder_OnMessageCreated:
				hr = se.OnMessageCreated(this);
				break;
			default: 
				hr = E_INVALIDARG; 
				break;
			}
		}
		m_pEventSource->Release();
	}
	
	return(hr);
}


// This function will obtain the EID of the Store and Parent of the Agent Message
HRESULT CExEvHandler::GetAgentProps(LPSPropValue* ppProps)
{
	HRESULT				hr			= S_OK;
	LPSPropValue		pProps		= NULL;
	LPSPropValue		pMsgProps	= NULL;
	LPMESSAGE			pMessage	= NULL;
	ULONG				cProps		= 0;

	SizedSPropTagArray(2,SourceProps) ={2,{PR_STORE_ENTRYID, PR_PARENT_ENTRYID}};
	
	// Get the Agent Message
	GetSource(&pMessage);

	// Get the EID's 
	hr = pMessage->GetProps((LPSPropTagArray)&SourceProps, 0, &cProps,ppProps);
	if(SUCCEEDED(hr))
	{
		if(!(SourceProps.aulPropTag[iPR_STORE_ENTRYID] == (*ppProps)[iPR_STORE_ENTRYID].ulPropTag) ||
		   !(SourceProps.aulPropTag[iPR_PARENT_ENTRYID]== (*ppProps)[iPR_PARENT_ENTRYID].ulPropTag))
		{
			hr = MAPI_E_NOT_FOUND;
			MAPIFreeBuffer(*ppProps);
		}
	}
	pMessage->Release();
	return(hr);
}

// This function will set props on the Agent Message
HRESULT CExEvHandler::SetAgentProps(ULONG cValues, LPSPropValue pProps)
{
	HRESULT				hr			= S_OK;
	LPMESSAGE			pMessage	= NULL;
	
	// Get the Agent Message
	GetSource(&pMessage);

	// Set Props 
	hr = pMessage->SetProps(cValues,pProps,NULL);
	pMessage->Release();
	return(hr);
}

// This function will retrieve the message that triggered the event
HRESULT CExEvHandler::GetTriggerMessage(LPSPropValue pProps,LPMESSAGE* ppMessage)
{
	HRESULT			hr				= S_OK;
	SBinary			EID				= {0};
	SBinary			*pStoreID		= NULL;
	BSTR			strMessageID	= NULL;
	LPMDB			pStore			= NULL;
	ULONG			ulType			= 0;
	ULONG			cProps			= 0;
	LPMAPISESSION	pSession		= NULL;

	pStoreID = &pProps[iPR_STORE_ENTRYID].Value.bin;
	if(pStoreID->lpb)
	{
		// Retrieve the Session
		if(SUCCEEDED(hr = GetSession(&pSession)))
		{
			// Retrieve the MsgStore
			if(SUCCEEDED(hr = pSession->OpenMsgStore(NULL,pStoreID->cb, (LPENTRYID)pStoreID->lpb,NULL,MAPI_BEST_ACCESS | MDB_NO_DIALOG | MAPI_DEFERRED_ERRORS, &pStore)))
			{
				// Retreive the Message ID
				if(SUCCEEDED(hr = GetMessageID(&strMessageID)))
				{
					// Convert to Binary
					EID = BSTRToBinary(strMessageID);
					if(EID.cb)
						// Open the Message
						hr = pStore->OpenEntry(EID.cb,(LPENTRYID)EID.lpb,NULL,MAPI_BEST_ACCESS |MAPI_DEFERRED_ERRORS, &ulType,(LPUNKNOWN*)ppMessage);
				}
				pStore->Release();
			}
			pSession->Release();
		}
	}
	return(hr);
}

/*********************************************************************************
	Utility functions follow...
 *********************************************************************************/

HRESULT CExEvHandler::VariantToMAPIObject(VARIANT var, REFIID iid, void** ppObject)
{
	HRESULT hr = S_OK;

	VARIANT varCopy;

	VariantInit(&varCopy);
	VariantCopyInd(&varCopy, &var);

	switch(varCopy.vt)
	{
	case VT_DISPATCH:
		if(varCopy.pdispVal)
		{
			hr = AMObjectToMAPIObject(varCopy.pdispVal, iid, ppObject);
			if(FAILED(hr))
			{
				hr = varCopy.pdispVal->QueryInterface(iid, (void**)ppObject);
			}
		}
		else
		{
			hr = E_INVALIDARG;
		}

		break;

	case VT_UNKNOWN:
		if(varCopy.punkVal)
		{
			hr = varCopy.punkVal->QueryInterface(iid, (void**)ppObject);
		}
		else
		{
			hr = E_INVALIDARG;
		}
		
		break;

	default:
		hr = DISP_E_TYPEMISMATCH;

		break;
	}

	VariantClear(&varCopy);

	return(hr);
}

HRESULT CExEvHandler::AMObjectToMAPIObject(LPDISPATCH pAMObject, REFIID iid, void** ppObject)
{
	HRESULT hr = S_OK;
	OLECHAR* szMAPIOBJECT = L"MAPIOBJECT";
	DISPID dispid;
	DISPPARAMS NoArgs = {NULL, NULL, 0, 0};
	VARIANT var;

	VariantInit(&var);

	if(pAMObject)
	{
		hr = pAMObject->GetIDsOfNames(IID_NULL, &szMAPIOBJECT, 1, LOCALE_USER_DEFAULT, &dispid);
		if(hr == S_OK)
		{
			hr = pAMObject->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &NoArgs, &var, NULL, NULL);
			if(hr == S_OK)
			{
				hr = var.punkVal->QueryInterface(iid, (void**)ppObject);
			}

			VariantClear(&var);
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return(hr);
}

SBinary CExEvHandler::BSTRToBinary(BSTR str)
{
	int		ich = 0;
	int		cch;
	SBinary bin = {0};
	LPBYTE  pb;

	if(str)
	{
		cch = SysStringLen(str);
		if(cch && !(cch & 1))
		{
			pb = bin.lpb = new BYTE[cch / 2];
			if(pb)
			{
				bin.cb = cch / 2;

				while(str[ich])
				{
					int		n = str[ich];
					int		ny;

					if (n >= L'0' && n <= L'9')
						ny = n - L'0';
					else if (n >= L'A' && n <= L'F')
						ny = n - L'A' + 10;
					else if (n >= L'a' && n <= L'f')
						ny = n - L'a' + 10;
					else
						break;

					if (ich++ & 1)
						*pb++ |= ny;
					else
						*pb = (BYTE) (ny << 4);
				}
			}
		}
	}

	return bin;
}

/*********************************************************************************
	IEventSource Shortcut functions follow...
 *********************************************************************************/

// Source = MAPI object (the agent message in the target folder)
// Function retrieves a Mapi Message (which is the agent)
HRESULT CExEvHandler::GetSource(LPMESSAGE* ppMessage)
{
	HRESULT hr;
	LPUNKNOWN			pSource		= NULL;
	IEventBinding*		pBinding	= NULL;
	VARIANT				var;

	if(SUCCEEDED(hr = m_pEventSource->get_Source(&pSource)))
	{
		if(SUCCEEDED(hr = pSource->QueryInterface(IID_IEventBinding, (void**)&pBinding)))
		{
			VariantInit(&var);
			if(SUCCEEDED(hr =pBinding->get_MAPIOBJECT(&var)))
			{
				hr = VariantToMAPIObject(var,IID_IMessage,(void**)ppMessage);
				VariantClear(&var);
			}
			pBinding->Release();
		}
		pSource->Release();
	}	
	return hr;
}

// SourceID = Entry identifier of the agent message in the EventConfig_<ServerName> folder 
HRESULT CExEvHandler::GetSourceID(BSTR* pstrSourceID)
{
	return m_pEventSource->get_SourceID(pstrSourceID);
}

// MessageID = Entry identifier of the message that was changed, added, or deleted 
// (NULL for timer events)
HRESULT CExEvHandler::GetMessageID(BSTR* pstrMessageID)
{
	return m_pEventSource->get_MessageID(pstrMessageID);
}

// Session = The MAPI session passed from the Microsoft Exchange Event Service
HRESULT CExEvHandler::GetSession(LPMAPISESSION* ppSession)
{
	HRESULT hr;
	LPUNKNOWN pSession = NULL;
	
	hr = m_pEventSource->get_Session(&pSession);
	if(SUCCEEDED(hr) && pSession != NULL)
	{
		// Turn the Session pointer into an Session Interface
		hr = pSession->QueryInterface(IID_IMAPISession,(void**)ppSession);
	}

	if(pSession) pSession->Release();
	return hr;
}

// EventType = The type of event that occurred (an integer enumeration: 0, 1, 2, or 3)
HRESULT CExEvHandler::GetEventType(DWORD* pdwEventType)
{
	return m_pEventSource->get_EventType(pdwEventType);
}

// MaxExecutionTime = Seconds of execution from beginning of agent execution until agent 
// execution is terminated.
HRESULT CExEvHandler::GetMaxExecutionTime(DWORD* pdwMaxExecutionTime)
{
	return m_pEventSource->get_MaxExecutionTime(pdwMaxExecutionTime);
}

// Response = Put a string here to record the outcome of the agent's execution. 
// The string is written to the Agent log. The Response property is a variant, but the 
// Event Service expects a string (if not a string, it will be ignored).  
HRESULT CExEvHandler::PutResponse(char * lpResponse)
{
	VARIANT				var;

	VariantInit(&var);
	return m_pEventSource->put_Response(var);
}


