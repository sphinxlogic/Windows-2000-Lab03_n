#include "stdafx.h"
#include "mapix.h"

#include "ICSDemo.h"
#include "ICSDemoDlg.h"

#include "TraceBox.h"

//
//	Including INITGUID.H redefines the DEFINE_GUID macro so that the
//	IID for IID_IExchangeImportContentsChanges is actually defined in
//	this module from the description given in ICSDemoCollector.h.
//
//	All other models that include ICSDemoCollector.h get an external
//	reference to the data blob defined here.
//

#include "initguid.h"
#include "ICSDemoCollector.h"

extern CICSDemoApp	theApp;
extern CTraceBox		theTraceBox;

CDemoCollector::CDemoCollector()
{
	m_cRef = 1;
}

STDMETHODIMP CDemoCollector::QueryInterface(REFIID riid,LPVOID *ppvObj)
{
	HRESULT hResult = S_OK;

	*ppvObj = NULL;

	if (riid == IID_IUnknown)
		*ppvObj = (LPUNKNOWN)this;
	else
	if (riid == IID_IExchangeImportContentsChanges)
		*ppvObj = (LPUNKNOWN)this;
	else
		hResult = E_NOINTERFACE;

	if (*ppvObj != NULL)
		((LPUNKNOWN)*ppvObj)->AddRef();

	return hResult;
}

STDMETHODIMP_(ULONG) CDemoCollector::AddRef()
{
	++m_cRef;
	return m_cRef;
}

STDMETHODIMP_(ULONG) CDemoCollector::Release()
{
	ULONG ulCount = --m_cRef;
	
	if (!ulCount)
	{
		delete this;
	}
	
	return ulCount;
}

STDMETHODIMP CDemoCollector::GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError)
{
	*lppMAPIError = NULL;
	
	return S_OK;
}

STDMETHODIMP CDemoCollector::Config(LPSTREAM lpStream, ULONG ulFlags)
{
	theTraceBox.Trace("CDemoCollector::Config");
	
	return S_OK;
}

STDMETHODIMP CDemoCollector::UpdateState(LPSTREAM lpStream)
{
	theTraceBox.Trace("CDemoCollector::UpdateState");

	return S_OK;
}

STDMETHODIMP CDemoCollector::ImportMessageChange(ULONG cpvalChanges, LPSPropValue ppvalChanges, ULONG ulFlags, LPMESSAGE *lppMessage)
{
	theTraceBox.Trace("CDemoCollector::ImportMessageChange");

	CString		objStr;


	LPSPropValue	lpProp		= ppvalChanges;
	ULONG				uPropCount	= cpvalChanges;

	while (uPropCount--)
	{
		switch (lpProp->ulPropTag)
		{
			case PR_ENTRYID :
			{
				LPMDB			lpStore = ((CICSDemoDlg *)(theApp.m_pMainWnd))->Store();
				LPMESSAGE	lpMessage = NULL;
				HRESULT		hResult;

				ASSERT(lpStore != NULL);

				ULONG	uObjType;
				
				hResult = lpStore->OpenEntry(
											lpProp->Value.bin.cb,
											(LPENTRYID)lpProp->Value.bin.lpb,
											NULL,
											MAPI_BEST_ACCESS,
											&uObjType,
											(LPUNKNOWN FAR *)&lpMessage);

				if (HR_FAILED(hResult))
					break;

				ASSERT(uObjType == MAPI_MESSAGE);

				//
				//	Read and display the subject line from the message.
				//

				SizedSPropTagArray(1,rgMessageProps) =
				{
					1,
					{
						PR_SUBJECT
					}
				};

				ULONG				uValuesCount;
				LPSPropValue	lpProps;

				hResult = lpMessage->GetProps(
											(LPSPropTagArray)&rgMessageProps,
											0,
											&uValuesCount,
											&lpProps);

				objStr.Format(" PR_SUBJECT=%s",lpProps[0].Value.lpszA);
				theTraceBox.Trace(objStr);
				
				MAPIFreeBuffer(lpProps);

				lpMessage->Release();

				break;
			}

			case PR_SOURCE_KEY :
			{
				theTraceBox.TraceBinary("PR_SOURCE_KEY",lpProp->Value.bin.cb,lpProp->Value.bin.lpb);
				break;
			}

			default :
				break;
		}

		++lpProp;
	}

	*lppMessage = NULL;

	return S_OK;
}

STDMETHODIMP CDemoCollector::ImportMessageDeletion(ULONG ulFlags, LPENTRYLIST lpSrcEntryList)
{
	theTraceBox.Trace("CDemoCollector::ImportMessageDeletion");

	ASSERT(lpSrcEntryList != NULL);

	ULONG	cValues = lpSrcEntryList->cValues;
	LPSBinary lpValues = lpSrcEntryList->lpbin;

	while (cValues--)
	{
		theTraceBox.TraceBinary("PR_SOURCE_KEY",lpValues->cb,lpValues->lpb);
		lpValues++;
	}

	return S_OK;
}

STDMETHODIMP CDemoCollector::ImportPerUserReadStateChange(ULONG cElements, LPREADSTATE lpReadState)
{
	theTraceBox.Trace("CDemoCollector::ImportPerUserReadStateChange");

	ASSERT(lpReadState != NULL);

	while (cElements--)
	{
		theTraceBox.TraceBinary("PR_SOURCE_KEY",lpReadState->cbSourceKey,lpReadState->pbSourceKey);

		if (lpReadState->ulFlags == SYNC_READ)
			theTraceBox.Trace(" Unread -> read");
		else
			theTraceBox.Trace(" Read -> unread");

		++lpReadState;
	}

	return S_OK;
}

STDMETHODIMP CDemoCollector::ImportMessageMove(	ULONG cbSourceKeySrcFolder,
		 										BYTE FAR * pbSourceKeySrcFolder,
		 										ULONG cbSourceKeySrcMessage,
		 										BYTE FAR * pbSourceKeySrcMessage,
		 										ULONG cbPCLMessage,
		 										BYTE FAR * pbPCLMessage,
		 										ULONG cbSourceKeyDestMessage,
		 										BYTE FAR * pbSourceKeyDestMessage,
		 										ULONG cbChangeNumDestMessage,
		 										BYTE FAR * pbChangeNumDestMessage)
{
	theTraceBox.Trace("CDemoCollector::ImportMessageMove");

	return S_OK;
}
