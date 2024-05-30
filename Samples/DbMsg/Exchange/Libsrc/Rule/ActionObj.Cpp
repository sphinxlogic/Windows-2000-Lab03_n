// ----------------------------------------------------------------------------
//	ActionObj.cpp : Implementation of CAction
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "PropVal.h"
#include "util.h"
#include "ActionObj.h"

// CAction
CAction::CAction()
{
	m_lIndex = 0;
	memset((void*)&m_uActionArgs,0,sizeof(uActionArgs));
	m_actionType = ACTION_DEFER;
}

CAction::~CAction()
{
	cleanup();
}

STDMETHODIMP CAction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAction,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAction::get_Arg(VARIANT *pVal)
{
	HRESULT		hr=NOERROR;

	if(pVal)
	{
		VariantInit(pVal);
		switch(m_actionType)
		{
		case ACTION_MOVE:
		case ACTION_COPY:
			pVal->vt = VT_DISPATCH;
			hr = m_uActionArgs.lpMoveCopyFolder->QueryInterface(IID_IDispatch,(LPVOID*)&pVal->pdispVal);
		break;

		case ACTION_REPLY:
		case ACTION_OOFREPLY:
		{
			SAFEARRAYBOUND	rgsabound[1];
			SAFEARRAY		*psa;
			long			index;
			VARIANT			lVar;
				
			hr = E_OUTOFMEMORY;
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = 2;
			if(psa=SafeArrayCreate(VT_VARIANT,1,rgsabound))
			{
				index = 0;
				lVar.vt = VT_BSTR;
				lVar.bstrVal = BinaryToBSTR(&m_uActionArgs.lReplyTemplate.sReplyEntryId);
				if(SUCCEEDED(hr=SafeArrayPutElement(psa,&index,&lVar)))
				{
					index = 1;
					lVar.vt = VT_BSTR;
					lVar.bstrVal = GUIDToBSTR(&m_uActionArgs.lReplyTemplate.guidReplyTemplate);
					if(SUCCEEDED(hr = SafeArrayPutElement(psa,&index,&lVar)))
					{
						VARIANT		tmpVar;

						tmpVar.vt = VT_ARRAY|VT_VARIANT;
						tmpVar.parray = psa;
						hr = ::VariantCopy(pVal,&tmpVar);
					}
				}
			}
		}
		break;

		case ACTION_BOUNCE:
		{
			_bstr_t		bstrBounceCode;

			if(m_uActionArgs.scBounceCode == BOUNCE_MESSAGE_SIZE_TOO_LARGE)
				bstrBounceCode = "BOUNCE_MESSAGE_SIZE_TOO_LARGE";
			else if(m_uActionArgs.scBounceCode == BOUNCE_FORMS_MISMATCH)
				bstrBounceCode = "BOUNCE_FORMS_MISMATCH";
			else if(m_uActionArgs.scBounceCode == BOUNCE_ACCESS_DENIED)
				bstrBounceCode = "BOUNCE_ACCESS_DENIED";

			pVal->vt = VT_BSTR;
			pVal->bstrVal = bstrBounceCode;
		}
		break;

		case ACTION_FORWARD:
		case ACTION_DELEGATE:
			{
				VARIANT	tmpVar;

				tmpVar.vt = VT_ARRAY|VT_VARIANT;
				tmpVar.parray = m_uActionArgs.lpAdressList;
				::VariantInit(pVal);
				::VariantCopy(pVal,&tmpVar);
			}
			break;

		case ACTION_TAG:
			pVal->vt = VT_DISPATCH;
			hr =(*m_uActionArgs.pPropValPtr)->QueryInterface(IID_IDispatch,
												(LPVOID*)&pVal->pdispVal);
			break;
		case ACTION_DELETE:
		case ACTION_MARKREAD:
		case ACTION_DEFER:
		default:				break;
		}
	}
	else
		hr = E_INVALIDARG;

	return hr;
}

STDMETHODIMP CAction::put_Arg(VARIANT newVal)
{
	HRESULT		hr=NOERROR;

	switch(m_actionType)
	{
	case ACTION_MOVE:
	case ACTION_COPY:
		if(VT_DISPATCH==newVal.vt)
		{
			if(newVal.pdispVal)
				hr = newVal.pdispVal->QueryInterface(IID_IDispatch,(LPVOID*)&m_uActionArgs.lpMoveCopyFolder);
		}
		else
			hr = E_INVALIDARG;
		break;

	case ACTION_REPLY:
	case ACTION_OOFREPLY:
		{
			if((VT_BSTR==newVal.vt)||((VT_BSTR|VT_BYREF)==newVal.vt))
			{
				BSTR bstrVal = VT_BSTR==newVal.vt? newVal.bstrVal:*newVal.pbstrVal;
				m_uActionArgs.lReplyTemplate.sReplyEntryId = BSTRToBinary(bstrVal);
				if(!m_uActionArgs.lReplyTemplate.sReplyEntryId.cb)
					hr = E_INVALIDARG;
			}
			else if(((VT_ARRAY|VT_VARIANT)==newVal.vt)||((VT_ARRAY|VT_VARIANT|VT_BYREF)==newVal.vt))
			{
				VARIANT		lVar;
				SAFEARRAY	*psa;
				LONG		index=0;

				psa	= (newVal.vt==(VT_ARRAY|VT_BYREF|VT_VARIANT))? *(newVal.pparray):newVal.parray;
				if(psa)
				{
					if((1<=psa->cDims)&&(psa->rgsabound[0].cElements>=1))
					{
						for(index=0;index<psa->rgsabound[0].cElements;index++)
						{
							if(SUCCEEDED(hr=SafeArrayGetElement(psa,&index,&lVar)))
							{
								if(VT_BSTR==lVar.vt)
								{
									if(index==0)
										m_uActionArgs.lReplyTemplate.sReplyEntryId = BSTRToBinary(lVar.bstrVal);
									else if(index==1)
										m_uActionArgs.lReplyTemplate.guidReplyTemplate = BSTRToGUID(lVar.bstrVal);
									else
										break;
								}
							}
						}
					}
				}
			}
			else
				hr = E_INVALIDARG;
		}
		break;


	case ACTION_BOUNCE:
		{
			if(VT_BSTR==newVal.vt)
			{
				if(newVal.bstrVal)
				{
					if(bstr_t("BOUNCE_MESSAGE_SIZE_TOO_LARGE")==bstr_t(newVal.bstrVal))
						m_uActionArgs.scBounceCode = BOUNCE_MESSAGE_SIZE_TOO_LARGE;
					else if(bstr_t("BOUNCE_FORMS_MISMATCH")==bstr_t(newVal.bstrVal))
						m_uActionArgs.scBounceCode = BOUNCE_FORMS_MISMATCH;
					else if(bstr_t("BOUNCE_ACCESS_DENIED")==bstr_t(newVal.bstrVal))
						m_uActionArgs.scBounceCode = BOUNCE_ACCESS_DENIED;
					else
						hr=E_INVALIDARG;
				}
				else
					hr=E_INVALIDARG;
			}
			else
				hr=E_INVALIDARG;
		}
		break;

	case ACTION_FORWARD:
	case ACTION_DELEGATE:
		if(((VT_ARRAY|VT_VARIANT)==newVal.vt)||((VT_ARRAY|VT_VARIANT|VT_BYREF)==newVal.vt))
		{
			SAFEARRAY	*parray;

			parray = (newVal.vt==(VT_ARRAY|VT_BYREF|VT_VARIANT))? *(newVal.pparray):newVal.parray;
			if(parray)
			{
				if(parray->cDims>=1)
				{
					SAFEARRAYBOUND	rgsabound[1];
					long			lEntry;
					VARIANT			lVar;

					rgsabound[0].lLbound =0;
					rgsabound[0].cElements = parray->rgsabound[0].cElements;

					if(m_uActionArgs.lpAdressList=SafeArrayCreate(VT_VARIANT,1,rgsabound))
					{
						for(lEntry=0;lEntry<rgsabound[0].cElements;lEntry++)
						{
							if(SUCCEEDED(hr=SafeArrayGetElement(parray,&lEntry,&lVar)))
							{
								hr=SafeArrayPutElement(m_uActionArgs.lpAdressList,&lEntry,&lVar);
								if(SUCCEEDED(hr))
									continue;
								else
									break;
							}
							else
								break;
						}
					}
					else
						hr = E_OUTOFMEMORY;
				}
				else
					hr = E_INVALIDARG;

			}
			else
				hr = E_INVALIDARG;
		}
		else
			hr = E_INVALIDARG;
		break;

	case ACTION_TAG:
		{
			if(VT_DISPATCH==newVal.vt)
			{
				LPPROPVAL	lpPropVal;

				if(SUCCEEDED(hr=newVal.pdispVal->QueryInterface(IID_IPropVal,(LPVOID*)&lpPropVal)))
				{
					if(!(m_uActionArgs.pPropValPtr=new CPropValPtr(lpPropVal)))
						hr = E_OUTOFMEMORY;
					lpPropVal->Release();
				}
			}
			else
				hr = E_INVALIDARG;
		}
		break;

	case ACTION_DELETE:
	case ACTION_MARKREAD:
	case ACTION_DEFER:
	default:				break;
	}
	return hr;
}

STDMETHODIMP CAction::get_ActionType(ACTION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_actionType;
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CAction::put_ActionType(ACTION_TYPES newVal)
{
	cleanup();
	m_actionType = newVal;
	return S_OK;
}

void CAction::cleanup()
{
	switch(m_actionType)
	{
	case ACTION_COPY:
	case ACTION_MOVE:
		if(m_uActionArgs.lpMoveCopyFolder)
		{
			m_uActionArgs.lpMoveCopyFolder->Release();
			m_uActionArgs.lpMoveCopyFolder = NULL;
		}
		break;

	case ACTION_REPLY:
	case ACTION_OOFREPLY:
		m_uActionArgs.lReplyTemplate.sReplyEntryId.cb = 0;
		delete [] m_uActionArgs.lReplyTemplate.sReplyEntryId.lpb;
		m_uActionArgs.lReplyTemplate.sReplyEntryId.lpb = NULL;
		memset(&m_uActionArgs.lReplyTemplate.guidReplyTemplate.Data1,0,sizeof(GUID));
		break;

	case ACTION_FORWARD:
	case ACTION_DELEGATE:
		if(m_uActionArgs.lpAdressList)
			SafeArrayDestroy(m_uActionArgs.lpAdressList);
		break;
	case ACTION_TAG:
		delete m_uActionArgs.pPropValPtr;
		m_uActionArgs.pPropValPtr = NULL;
		break;
	default:break;
	}
	return;
}

HRESULT	CAction::load(LPACTION	lpAction)
{
	HRESULT		hr=NOERROR;

	if(lpAction)
	{
		cleanup();
		switch(lpAction->acttype)
		{
		case OP_MOVE:
			m_actionType = ACTION_MOVE;
			break;

		case OP_COPY:
			m_actionType = ACTION_COPY;
			break;

		case OP_REPLY:
			m_actionType = ACTION_REPLY;
			break;

		case OP_OOF_REPLY:
			m_actionType = ACTION_OOFREPLY;
			break;

		case OP_DEFER_ACTION:
			m_actionType = ACTION_DEFER;
			break;

		case OP_BOUNCE:
			m_actionType = ACTION_BOUNCE;
			break;

		case OP_FORWARD:
			m_actionType = ACTION_FORWARD;
			break;

		case OP_DELEGATE:
			m_actionType = ACTION_DELEGATE;
			break;

		case OP_TAG:
			m_actionType = ACTION_TAG;
			break;

		case OP_DELETE:
			m_actionType = ACTION_DELETE;
			break;

		case OP_MARK_AS_READ:
			m_actionType = ACTION_MARKREAD;
			break;

		default:
			break;
		}

		switch(lpAction->acttype)
		{
		case OP_MOVE:
		case OP_COPY:
		{
			if(_Module.m_pCDOSession)
			{
				VARIANT		varResult;
				DISPPARAMS	dispParams;
				SBinary		lSBin[2];

				lSBin[0].cb = lpAction->actMoveCopy.cbStoreEntryId;
				lSBin[0].lpb= (LPBYTE)lpAction->actMoveCopy.lpStoreEntryId;
				lSBin[1].cb = lpAction->actMoveCopy.cbFldEntryId;
				lSBin[1].lpb= (LPBYTE)lpAction->actMoveCopy.lpFldEntryId;

				dispParams.rgvarg = new VARIANTARG[2];
				dispParams.rgvarg[0].vt = VT_BSTR;
				dispParams.rgvarg[0].bstrVal = BinaryToBSTR(lSBin);
				dispParams.rgvarg[1].vt = VT_BSTR;
				dispParams.rgvarg[1].bstrVal = BinaryToBSTR(lSBin+1);
				dispParams.cArgs = 2;
				dispParams.cNamedArgs = 0;

				if(SUCCEEDED(hr=::MethodInvoke(_Module.m_pCDOSession,_T("GetFolder"),&varResult,&dispParams)))
				{
					if(VT_DISPATCH==varResult.vt)
						hr = varResult.pdispVal->QueryInterface(IID_IDispatch,(LPVOID*)&m_uActionArgs.lpMoveCopyFolder);
				}
				else if(SUCCEEDED(hr==::PropertyInvoke(_Module.m_pCDOSession,DISPATCH_PROPERTYGET,_T("InfoStores"),&varResult)))
				{
					if(VT_DISPATCH==varResult.vt)
					{
						VARIANT		varCount;
						DISPPARAMS	indexParam;

						if(SUCCEEDED(hr==::PropertyInvoke(varResult.pdispVal,DISPATCH_PROPERTYGET,_T("Count"),&varCount)))
						{
							if(VT_I4==varCount.vt)
							{
								VARIANT		varInfoStore;
								VARIANT		infoStoreID;
								
								indexParam.rgvarg = new VARIANTARG[1];
								indexParam.rgvarg[0].vt = VT_I4;
								indexParam.cArgs = 1;
								indexParam.cNamedArgs = 0;
								
								for(long infoStoreIndex=1;infoStoreIndex<=varCount.lVal;infoStoreIndex++)
								{
									indexParam.rgvarg[0].lVal = infoStoreIndex;
									if(SUCCEEDED(hr==::MethodInvoke(varResult.pdispVal,_T("Item"),&varInfoStore,&indexParam,DISPATCH_PROPERTYGET)))
									{
										if(VT_DISPATCH==varInfoStore.vt)
										{
											if(SUCCEEDED(hr==::PropertyInvoke(varInfoStore.pdispVal,DISPATCH_PROPERTYGET,_T("ID"),&infoStoreID)))
											{
												if(VT_BSTR==infoStoreID.vt)
												{
													dispParams.rgvarg[0].bstrVal = infoStoreID.bstrVal;
													if(SUCCEEDED(hr=::MethodInvoke(_Module.m_pCDOSession,_T("GetFolder"),&varResult,&dispParams,DISPATCH_PROPERTYGET)))
													{
														if(VT_DISPATCH==varResult.vt)
															hr = varResult.pdispVal->QueryInterface(IID_IDispatch,(LPVOID*)&m_uActionArgs.lpMoveCopyFolder);
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
				else
					hr = E_FAIL;
				::SysFreeString(dispParams.rgvarg[0].bstrVal);
				::SysFreeString(dispParams.rgvarg[1].bstrVal);
				delete [] dispParams.rgvarg;
			}
			else
				hr = E_FAIL;
		}
		break;

		case OP_REPLY:
		case OP_OOF_REPLY:
		{
			m_uActionArgs.lReplyTemplate.sReplyEntryId.cb = lpAction->actReply.cbEntryId;
			if(m_uActionArgs.lReplyTemplate.sReplyEntryId.lpb = new BYTE[lpAction->actReply.cbEntryId])
			{
				memcpy(m_uActionArgs.lReplyTemplate.sReplyEntryId.lpb,lpAction->actReply.lpEntryId,lpAction->actReply.cbEntryId);
				m_uActionArgs.lReplyTemplate.guidReplyTemplate = lpAction->actReply.guidReplyTemplate;
			}
			else
				hr = E_OUTOFMEMORY;
		}
		break;

		case OP_BOUNCE:
			m_uActionArgs.scBounceCode = lpAction->scBounceCode;
			break;

		case OP_FORWARD:
		case OP_DELEGATE:
		{
			SAFEARRAYBOUND	rgsabound[1];
			LPADRENTRY		lpAdrEntry=NULL;
			VARIANT			lVar;
			LPSPropValue	lpPropVal=NULL;
			long			lEntry=0;
			long			lPropValIndex=0;

			rgsabound[0].lLbound =0;
			rgsabound[0].cElements = lpAction->lpadrlist->cEntries;
			if(m_uActionArgs.lpAdressList=SafeArrayCreate(VT_VARIANT,1,rgsabound))
			{
				for(lEntry=0;lEntry<lpAction->lpadrlist->cEntries;lEntry++)
				{	
					if(SUCCEEDED(hr))
					{
						lpAdrEntry = &lpAction->lpadrlist->aEntries[lEntry];
						if(lpPropVal=lpAdrEntry->rgPropVals)
						{
							for(lPropValIndex=0;lPropValIndex<lpAdrEntry->cValues;
								lpPropVal++,lPropValIndex++)
							{
								if(lpPropVal)
								{
									if(PR_ENTRYID==lpPropVal->ulPropTag)
									{
										lVar.vt = VT_BSTR;
										lVar.bstrVal = BinaryToBSTR(&lpPropVal->Value.bin);
										hr = SafeArrayPutElement(m_uActionArgs.lpAdressList,&lEntry,(LPVOID)&lVar);
										SysFreeString(lVar.bstrVal);
										break;
									}
								}
								else
								{
									hr = E_INVALIDARG;
									break;
								}
							}
						}
						else
							hr=E_INVALIDARG;
					}
				}
			}
			else
				hr=E_OUTOFMEMORY;
		}
		break;

		case OP_TAG:
		{
			CPropValObject	*pPropValOb=NULL;

			if(SUCCEEDED(hr=CPropValObject::CreateInstance(&pPropValOb)))
			{
				if(m_uActionArgs.pPropValPtr=new CPropValPtr(pPropValOb))
					hr=pPropValOb->load(&lpAction->propTag);
			}
		}
		break;

		case OP_DEFER_ACTION:
		case OP_DELETE:
		case OP_MARK_AS_READ:
		default:	// Nothing more to do.
			break;
		}
	}
	else
		hr = E_INVALIDARG;
	return hr;
}

HRESULT	CAction::pack(LPACTION lpAction,LPVOID lpObject)
{
	HRESULT		hr=NOERROR;

	//	initialize all untouched members to zeros. The store might intrpret 
	//	the values present if any, and fail otherwise
	lpAction->ulActionFlavor=0;
	lpAction->lpRes=NULL;
	lpAction->lpPropTagArray=NULL;
	lpAction->ulFlags=0;
	lpAction->dwAlignPad=0;
	lpAction->scBounceCode=0;
	lpAction->lpadrlist=NULL;
	lpAction->propTag.ulPropTag=0;
	lpAction->propTag.dwAlignPad=0;
	lpAction->propTag.Value.ul=0;

	if(lpAction)
	{
		switch(m_actionType)
		{
		case ACTION_MOVE:
		case ACTION_COPY:
		{
			VARIANT		varResult;

			lpAction->acttype =(m_actionType==ACTION_MOVE? OP_MOVE:OP_COPY);
			if(m_uActionArgs.lpMoveCopyFolder)
			{
				if(SUCCEEDED(hr=::PropertyInvoke(m_uActionArgs.lpMoveCopyFolder,DISPATCH_PROPERTYGET,_T("StoreID"),&varResult)))
				{
					if(VT_BSTR==varResult.vt)
					{
						SBinary		lSBin;

						lSBin = BSTRToBinary(varResult.bstrVal);
						lpAction->actMoveCopy.cbStoreEntryId = lSBin.cb;

						if(SUCCEEDED(hr=MAPIAllocateMore(lpAction->actMoveCopy.cbStoreEntryId,
												 lpObject,(LPVOID*)&lpAction->actMoveCopy.lpStoreEntryId)))
						{
							memcpy( lpAction->actMoveCopy.lpStoreEntryId->abFlags,
									lSBin.lpb,lpAction->actMoveCopy.cbStoreEntryId);
							if(SUCCEEDED(hr=::PropertyInvoke(m_uActionArgs.lpMoveCopyFolder,DISPATCH_PROPERTYGET,_T("ID"),&varResult)))
							{
								if(VT_BSTR==varResult.vt)
								{
									SBinary		lSBin1;
									lSBin1 = BSTRToBinary(varResult.bstrVal);
									lpAction->actMoveCopy.cbFldEntryId = lSBin1.cb;

									if(SUCCEEDED(hr=MAPIAllocateMore(lpAction->actMoveCopy.cbFldEntryId,lpObject,
												 (LPVOID FAR*)&lpAction->actMoveCopy.lpFldEntryId)))
									{
										memcpy(lpAction->actMoveCopy.lpFldEntryId,lSBin1.lpb,lSBin1.cb);
									}
									delete lSBin1.lpb;
								}
								else
									hr = E_FAIL;
							}
						}
						else
							hr = E_FAIL;
						delete lSBin.lpb;
					}
				}
			}
			else
				hr = E_INVALIDARG;
		}
		break;

		case ACTION_REPLY:
		case ACTION_OOFREPLY:
		{
			lpAction->acttype =(m_actionType==ACTION_REPLY)? OP_REPLY:OP_OOF_REPLY;
			lpAction->actReply.cbEntryId = m_uActionArgs.lReplyTemplate.sReplyEntryId.cb;
			if(m_uActionArgs.lReplyTemplate.sReplyEntryId.cb)
			{
				if(SUCCEEDED(hr=MAPIAllocateMore(lpAction->actReply.cbEntryId,
												 lpObject,(LPVOID FAR*)&lpAction->actReply.lpEntryId)))
				{
					memcpy(lpAction->actReply.lpEntryId, m_uActionArgs.lReplyTemplate.sReplyEntryId.lpb,
						   m_uActionArgs.lReplyTemplate.sReplyEntryId.cb);
					lpAction->actReply.guidReplyTemplate = m_uActionArgs.lReplyTemplate.guidReplyTemplate;
				}
			}
			else
				hr = E_INVALIDARG;
		}
		break;

		case ACTION_DEFER:
			lpAction->acttype = OP_DEFER_ACTION;
			break;

		case ACTION_BOUNCE:
			lpAction->acttype = OP_BOUNCE;
			if( (m_uActionArgs.scBounceCode!=BOUNCE_MESSAGE_SIZE_TOO_LARGE)	||
				(m_uActionArgs.scBounceCode!=BOUNCE_FORMS_MISMATCH)			||
				(m_uActionArgs.scBounceCode!=BOUNCE_ACCESS_DENIED))
				lpAction->scBounceCode = m_uActionArgs.scBounceCode;
			else
				hr = E_INVALIDARG;
			break;
	
		case ACTION_FORWARD:
		case ACTION_DELEGATE:
		{
			lpAction->acttype =(m_actionType==ACTION_FORWARD)?OP_FORWARD:OP_DELEGATE;
			long	cElements=m_uActionArgs.lpAdressList->rgsabound[0].cElements;

			if(m_uActionArgs.lpAdressList)
			{
				if(SUCCEEDED(hr=MAPIAllocateMore(CbNewADRLIST(cElements),
												 lpObject,(LPVOID FAR*)&lpAction->lpadrlist)))
				{
					lpAction->lpadrlist->cEntries = cElements;
					hr=GetBaseAddressProps(m_uActionArgs.lpAdressList,lpObject,lpAction->lpadrlist);
				}
			}
			else
				hr = E_INVALIDARG;
		}
		break;

		case ACTION_TAG:
		{
			lpAction->acttype = OP_TAG;

			CPropVal	*pPropVal;

			if(m_uActionArgs.pPropValPtr)
			{
				IPropVal	*lpPropVal=*m_uActionArgs.pPropValPtr;

				if(pPropVal=dynamic_cast<CPropVal*>(lpPropVal))
					hr=pPropVal->pack(&lpAction->propTag,lpObject);
			}
			else
				hr = E_INVALIDARG;
		}
		break;

		case ACTION_DELETE:
			lpAction->acttype = OP_DELETE;
			break;

		case ACTION_MARKREAD:
			lpAction->acttype = OP_MARK_AS_READ;
		default:break;
		}
	}
	else
		hr=E_INVALIDARG;
	return hr;
}
