// --SuggestEvents.cpp----------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "SuggestEvents.h"
#include "string.h"

#define MAX_REPLY_BUF 1024

CSuggestEvents::CSuggestEvents()
{
}

HRESULT CSuggestEvents::OnChange(CExEvHandler* phndlr)
{
	// TODO:  Place application dependent here....

	return S_OK;
}
HRESULT CSuggestEvents::OnMessageDeleted(CExEvHandler* phndlr)
{
	// TODO:  Place application dependent here....

	return S_OK;
}
HRESULT CSuggestEvents::OnTimer(CExEvHandler* phndlr)
{
	// TODO:  Place application dependent here....

	return S_OK;
}

// We only implement one Event response.  That is the MessageCreated Event.
// We are being passed a pointer to our Event Handler Class which contains
// All the necessary code to handler the Custom Agent issues.
HRESULT CSuggestEvents::OnMessageCreated(CExEvHandler* phndlr)
{
	HRESULT			hr				= S_OK;
	LPUNKNOWN		pSession		= NULL;
	LPMAPISESSION	pMSession		= NULL;
	LPMESSAGE		pMessage		= NULL;
	LPSPropValue	pStoreProps		= NULL;
	LPSPropValue	pMsgProps		= NULL;
	LPSTR			pSubject		= NULL;
	LPSTR			pBody			= NULL;
	LPSPropValue	pSenderEIDProp	= NULL;
	LPSPropValue	pProps			= NULL;
	ULONG			cProps			= 0;
	IABContainer*	pAddrBook		= NULL;
	char*			szTmp			= NULL;
	
	SizedSPropTagArray(2,MsgProps) ={2,{PR_SUBJECT,PR_SENDER_ENTRYID}};
	enum
	{
		iPR_SUBJECT,
		iPR_SENDER_ENTRYID
	};

	// Get a session pointer
	if(SUCCEEDED(hr = phndlr->GetSession(&pMSession)))
	{
		// We need to get the Message Store EID that our Newly create Message resides in.  
		// This is the Message that triggered the event.
		// To get the Message Store EID we need to open the Agent Message that was 
		// created when we bound our Agent to a Folder.
		if(SUCCEEDED(hr = phndlr->GetAgentProps(&pStoreProps)))
		{
			// Now we will get the Message that triggered the Event
			if(SUCCEEDED(hr = phndlr->GetTriggerMessage(pStoreProps,&pMessage)))
			{	
				// Get the properties we want off the message	
				if(SUCCEEDED(hr = pMessage->GetProps((LPSPropTagArray)&MsgProps,0L, &cProps,&pProps)))
				{
					// Check for valid PropTags to ensure good values
					if(MsgProps.aulPropTag[iPR_SUBJECT] == pProps[iPR_SUBJECT].ulPropTag &&
					   MsgProps.aulPropTag[iPR_SENDER_ENTRYID] == pProps[iPR_SENDER_ENTRYID].ulPropTag)
					{
						// Convert Prop Values to desirecd format
						pSubject = pProps[iPR_SUBJECT].Value.lpszA;
						pSenderEIDProp = &pProps[iPR_SENDER_ENTRYID];
						

						// Grab the configured data from the registry and put it into the body
						if(szTmp = new char[MAX_REPLY_BUF])
						{
							szTmp[0]='\0';
							LoadString(_Module.GetModuleInstance(),IDS_REPLYTEXT,szTmp,MAX_REPLY_BUF-1);
							pBody=szTmp;

							// Get our address books in order to send response
							if(SUCCEEDED(hr = GetGal(pMSession, &pAddrBook)))
							{
								// Send response...
								hr = SendMessage(pMSession,pAddrBook,pSubject,pBody,pStoreProps,pSenderEIDProp);
								pAddrBook->Release();
							}
							delete szTmp;
						}
					}
					MAPIFreeBuffer(pProps);
				}
				pMessage->Release();
			}
			MAPIFreeBuffer(pStoreProps);
		}
		pMSession->Release();
	}
	return (hr);
}

// Standard procecure to send a message.  We will send the message from the system attendant
// to the mailuser who triggered this event.
HRESULT CSuggestEvents::SendMessage(LPMAPISESSION pMSession,IABContainer* pAddrbook,LPSTR pSubject,LPSTR pBody,LPSPropValue pProps,LPSPropValue pSenderEIDProps)
{
	HRESULT hr= S_OK;
	
	LPSPropValue		pOutboxProps	= NULL;
	LPSPropValue		pMailbox		= NULL;
	SBinary*			pOutbxID		= NULL;
	ULONG				ulType          = NULL;
	IMAPIFolder*		pOutbox         = NULL;
	IMessage*			pMessage		= NULL;
	LPMAILUSER			pSender			= NULL;
	LPADRLIST			pAdrList		= NULL;
	LPMDB				pMsgStore		= NULL;
	ULONG				cvalue		    = 1;
	LPSPropValue		pProp			= NULL;

	SizedADRLIST(1,adrList);
	pAdrList = (LPADRLIST)&adrList;

	SizedSPropTagArray(1,outboxEID)= {1,{PR_IPM_OUTBOX_ENTRYID}};
	SizedSPropTagArray(3,Mailbox) = {3,{PR_ENTRYID,PR_DISPLAY_NAME,PR_ADDRTYPE}};

	// Get the default store
	if(SUCCEEDED(hr = GetDefMsgStore(pMSession, &pMsgStore)))
	{
		// Open the Outbox
		if(SUCCEEDED(hr = pMsgStore->GetProps((LPSPropTagArray)&outboxEID,0,&ulType,&pOutboxProps)))
		{	
			if(pOutboxProps[0].ulPropTag == outboxEID.aulPropTag[0])//got the props needed
			{
				pOutbxID = &pOutboxProps[0].Value.bin;
				if(SUCCEEDED(hr = pMsgStore->OpenEntry(	pOutbxID->cb,
												(LPENTRYID)pOutbxID->lpb,
												NULL,
												MAPI_MODIFY,
												&ulType,
												(LPUNKNOWN*)&pOutbox)))
				{
					// Create our message
					if(SUCCEEDED(hr = pOutbox->CreateMessage(NULL,0,&pMessage)))
					{
						// Get the addrEntry object of the sender
						if(SUCCEEDED(hr = pMSession->OpenEntry(pSenderEIDProps->Value.bin.cb,
											(LPENTRYID)pSenderEIDProps->Value.bin.lpb,
											 NULL,
											 0,
											 &ulType,
											 (LPUNKNOWN*)&pSender)))
						{
							// Get the necessary info on that mailuser
							if(SUCCEEDED(hr = pSender->GetProps((LPSPropTagArray)&Mailbox,
												0,
												&ulType,
												&pMailbox)))
							{
								if( pMailbox[0].ulPropTag == Mailbox.aulPropTag[0] && 
									pMailbox[1].ulPropTag == Mailbox.aulPropTag[1] &&
									pMailbox[2].ulPropTag == Mailbox.aulPropTag[2])
								{
									// Fill out the addrEntry object
									pAdrList->cEntries = 1;
									if(SUCCEEDED(hr = MAPIAllocateBuffer( sizeof(ADRENTRY),(LPVOID*) &pAdrList->aEntries)))
									{
										pAdrList->aEntries[0].cValues =4;
										pAdrList->aEntries[0].ulReserved1 =0;
									
										if(SUCCEEDED(hr = MAPIAllocateBuffer(4*sizeof(SPropValue),(LPVOID*)&(pAdrList->aEntries[0].rgPropVals))))
										{
											pAdrList->aEntries[0].rgPropVals[0].ulPropTag = PR_ENTRYID;
											pAdrList->aEntries[0].rgPropVals[0].Value.bin = pMailbox[0].Value.bin;
										
											pAdrList->aEntries[0].rgPropVals[1].ulPropTag = PR_DISPLAY_NAME;
											pAdrList->aEntries[0].rgPropVals[1].Value.lpszA = pMailbox[1].Value.lpszA;
		
											pAdrList->aEntries[0].rgPropVals[2].ulPropTag = PR_RECIPIENT_TYPE;
											pAdrList->aEntries[0].rgPropVals[2].Value.l = MAPI_TO;

								
											pAdrList->aEntries[0].rgPropVals[3].ulPropTag = PR_ADDRTYPE;
											pAdrList->aEntries[0].rgPropVals[3].Value.lpszA = pMailbox[2].Value.lpszA;
										
											// Add our recipient to the list
											if(SUCCEEDED(hr = pMessage->ModifyRecipients(MODRECIP_ADD,pAdrList)))
											{
								
												// The props we set so far are standard, if you want to
												// set additional items specific to your application
												// you should set them in the following function.
												if(SUCCEEDED(hr = SetOutGoingMessageProps(pMessage,pSubject,pBody)))
												{
													// Attempt to send the message
													hr = pMessage->SubmitMessage(FORCE_SUBMIT);
												}
											}
										}
										FreePadrlist(pAdrList);
									}
								}
								MAPIFreeBuffer(pMailbox);
							}
							pSender->Release();
						}
						pMessage->Release();
					}
					pOutbox->Release();
				}
			}
			MAPIFreeBuffer(pOutboxProps);
		}					
		pMsgStore->Release();
	}
	return hr;
}

// This function allows you to set additional properties on the
// message that are specific to your application.
// In the case of the sample, we simple send a reply back to the sender.
HRESULT CSuggestEvents::SetOutGoingMessageProps(IMessage* pMessage, LPSTR pSubject, LPSTR pBody)
{
	HRESULT				hr				 = S_OK;
	LPSPropValue		pMessageProps	 = NULL;
	ULONG				ulType			 = 0;
	ULONG				cvalue			 = 3;
	
	if(SUCCEEDED(hr = MAPIAllocateBuffer(sizeof(SPropValue)* cvalue , (LPVOID*)&pMessageProps)))
	{
		pMessageProps[0].ulPropTag = PR_SUBJECT_A;
		pMessageProps[1].ulPropTag = PR_BODY_A;
		pMessageProps[2].ulPropTag = PR_DELETE_AFTER_SUBMIT;

		pMessageProps[0].Value.lpszA = pSubject;
		pMessageProps[1].Value.lpszA = pBody;
		pMessageProps[2].Value.ul	 = TRUE;								

		hr = pMessage->SetProps(cvalue,	pMessageProps, NULL);
	}
	return hr;
}

// A couple of utility functions follow...

// Retrieves the Global Address List
HRESULT CSuggestEvents::GetGal(LPMAPISESSION pSession, IABContainer** ppAddrBook)
{
	HRESULT        hr				= S_OK;
	IAddrBook*     pAddrBook		= NULL;
	ULONG          ulType			= 0;
	DWORD          dwRow			= 0;
	IABContainer*  pRootContainer	= NULL;
    IMAPITable*    pContainerTable	= NULL;
    SRowSet*       prows			= NULL;
	LONG           addrBookDisplayType;
    LPSPropValue   pCurrProps		= NULL;
	
	SizedSPropTagArray(2,addrBkTags)  = {2,{PR_ENTRYID, PR_DISPLAY_TYPE}};
	
	if(SUCCEEDED(hr = pSession->OpenAddressBook( 0,NULL,AB_NO_DIALOG,&pAddrBook)))
	{
		if(SUCCEEDED(hr = pAddrBook->OpenEntry(0,NULL,NULL,MAPI_DEFERRED_ERRORS,&ulType,(LPUNKNOWN FAR *)&pRootContainer)))
		{
			if(SUCCEEDED(hr = pRootContainer->GetHierarchyTable(MAPI_DEFERRED_ERRORS,&pContainerTable)))
			{	   
				if(SUCCEEDED(hr = HrQueryAllRows(pContainerTable,(LPSPropTagArray)&addrBkTags,NULL,NULL,0,&prows)))
				{
					for(dwRow=0;dwRow< prows->cRows;dwRow++)
					{
						addrBookDisplayType = prows->aRow[dwRow].lpProps[1].Value.l;
						if(addrBookDisplayType == DT_GLOBAL)
						{
							pCurrProps = &(prows->aRow[dwRow].lpProps[0]);
							if(SUCCEEDED(hr = pAddrBook->OpenEntry(pCurrProps->Value.bin.cb,
															(LPENTRYID)pCurrProps->Value.bin.lpb,
															NULL,
															MAPI_DEFERRED_ERRORS | MAPI_MODIFY,
															&ulType,
															(LPUNKNOWN FAR *)ppAddrBook)))				
								break;
						}
					}
					FreeProws(prows);
				}
				pContainerTable->Release();
			}
			pRootContainer->Release();
		}
		pAddrBook->Release();
	}
	return hr;
}



// Retrieves the default message store for the pUserSession
HRESULT CSuggestEvents::GetDefMsgStore(LPMAPISESSION pMSession,LPMDB* ppStore)
{
	HRESULT			hr				= S_OK;
	LPMAPITABLE		pContentsTable	= NULL;
	DWORD			dwRow			= 0;
	ULONG			ul				= 0;
	SBinary			StoreID			= {0};
	LPSRowSet		prows			= NULL;

	SizedSPropTagArray(2, MsgStoreProps) ={2,{PR_DEFAULT_STORE,  PR_ENTRYID}};

	if(SUCCEEDED(hr = pMSession->GetMsgStoresTable(0,&pContentsTable)))
	{
		if(SUCCEEDED(hr = HrQueryAllRows(pContentsTable,(LPSPropTagArray)&MsgStoreProps,NULL,NULL,0,&prows)))
		{
			for(dwRow=0;dwRow<prows->cRows;dwRow++)
			{    
				if(	TRUE == prows->aRow[dwRow].lpProps[0].Value.b)
				{
					//pr_default_store is true
					StoreID = prows->aRow[dwRow].lpProps[1].Value.bin;
					hr =  pMSession->OpenMsgStore(
											NULL,
											StoreID.cb,
											(LPENTRYID)StoreID.lpb,
											NULL,
											MAPI_BEST_ACCESS  | MDB_NO_DIALOG | MDB_WRITE, 
											ppStore);
		
					break;
				}	
			}
			FreeProws(prows);
		}
		pContentsTable->Release();
	}
	return hr;
}


