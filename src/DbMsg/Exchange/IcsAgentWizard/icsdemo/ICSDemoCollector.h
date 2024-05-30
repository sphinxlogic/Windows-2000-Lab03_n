#pragma once

#include "mapix.h"

DEFINE_GUID(IID_IExchangeImportContentsChanges, 0xf75abfa0,0xd0e0,0x11cd,0x80,0xfc,0x00,0xaa,0x00,0x4b,0xba,0x0b);

class CDemoCollector : public IExchangeImportContentsChanges
{
private:
	ULONG	m_cRef;

public:
	CDemoCollector();

	STDMETHODIMP QueryInterface(REFIID riid,LPVOID *ppvObj);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	STDMETHODIMP GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError);
	STDMETHODIMP Config(LPSTREAM lpStream, ULONG ulFlags);
	STDMETHODIMP UpdateState(LPSTREAM lpStream);
	STDMETHODIMP ImportMessageChange(ULONG cpvalChanges, LPSPropValue	ppvalChanges, ULONG ulFlags, LPMESSAGE *lppmessage);
	STDMETHODIMP ImportMessageDeletion(ULONG ulFlags, LPENTRYLIST lpSrcEntryList);
	STDMETHODIMP ImportPerUserReadStateChange(ULONG cElements, LPREADSTATE lpReadState);
	STDMETHODIMP ImportMessageMove(	ULONG cbSourceKeySrcFolder,
		 							BYTE FAR * pbSourceKeySrcFolder,
		 							ULONG cbSourceKeySrcMessage,
		 							BYTE FAR * pbSourceKeySrcMessage,
		 							ULONG cbPCLMessage,
		 							BYTE FAR * pbPCLMessage,
		 							ULONG cbSourceKeyDestMessage,
		 							BYTE FAR * pbSourceKeyDestMessage,
		 							ULONG cbChangeNumDestMessage,
		 							BYTE FAR * pbChangeNumDestMessage);
};
