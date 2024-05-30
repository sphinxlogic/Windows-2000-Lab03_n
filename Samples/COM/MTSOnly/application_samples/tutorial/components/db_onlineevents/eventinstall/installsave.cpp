#include <stdio.h>
#include <objbase.h>
#include <assert.h>
#include <EventSys.h>
#include "StockPublisherEvents.h"
#include "StockPublisher_i.c"
#include "StockSubscription.h"

int main(int argc, char* argv[])
{
	int			rc = 0;
	HRESULT		hr = 0;
	LPOLESTR	strGUID;
    VARIANT     PropertyBagValue;
    BSTR        PropertyBagName;

	// ----------------------------------------------
	//      Initialize COM
	// ----------------------------------------------

	CoInitialize(NULL);
  
	// ----------------------------------------------
	//      Instantiate the Event System
	// ----------------------------------------------
	IEventSystem* pIEventSystem = NULL;

	hr = CoCreateInstance(CLSID_CEventSystem,
						  NULL,
						  CLSCTX_SERVER,
						  IID_IEventSystem,
						  (void**)&pIEventSystem);
	if (FAILED(hr))
	{
		wprintf(L"Failed to create CEventSystem, HRESULT=%x\n", hr);
		return (1);
	}
	wprintf(L"Successfully created CEventSystem\n");
	
    // ----------------------------------------------------
    //   Add a subscription for StockPriceChange event in
    //   IStockEvents class (no property bag)
    // ----------------------------------------------------

	BSTR	bstrSubscriptionID;
	BSTR	bstrSubscriptionName;
	BSTR	bstrPublisherID;
	BSTR	bstrEventClassID;
	BSTR	bstrMethodName;
	BSTR	bstrSubscriberCLSID;
	BSTR	bstrPROGID_Subscription;

	IEventSubscription	*pIEventSubscription = NULL;

	hr = CoCreateInstance(CLSID_CEventSubscription,
						  NULL,
						  CLSCTX_SERVER,
						  IID_IEventSubscription,
						  (void**)&pIEventSubscription);
	if (FAILED(hr))
	{
		wprintf(L"Failed to create IEventSubscription - hr = <%x>\n", hr);
		return(1);
	}

	bstrPROGID_Subscription = SysAllocString(PROGID_EventSubscription);

	hr = StringFromIID(guid_StockPriceChangeSub1, &strGUID);
	bstrSubscriptionID = SysAllocString(strGUID);

	bstrSubscriptionName = SysAllocString(str_StockPriceChangeSub);
  
	hr = StringFromIID(guid_StockPublisherID, &strGUID);
	bstrPublisherID = SysAllocString(strGUID);

	hr = StringFromIID(CLSID_StockEvents, &strGUID);
	bstrEventClassID = SysAllocString(strGUID);

	bstrMethodName = SysAllocString(str_StockPriceChange);

	bstrSubscriberCLSID = SysAllocString(L"{C658CAB0-89A2-11D1-891C-0080C7D771BF}");

	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);

	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

    // ----------------------------------------------------
    //   Add a subscription for StockPriceChange event in
    //   IStockEvents class (with property bag)
    // ----------------------------------------------------

	hr = CoCreateInstance(CLSID_CEventSubscription,
						  NULL,
						  CLSCTX_SERVER,
						  IID_IEventSubscription,
						  (void**)&pIEventSubscription);
	if (FAILED(hr))
	{
		wprintf(L"Failed to create IEventSubscription - hr = <%x>\n", hr);
		return(1);
	}

	bstrPROGID_Subscription = SysAllocString(PROGID_EventSubscription);

	hr = StringFromIID(guid_StockPriceChangeSub2, &strGUID);
	bstrSubscriptionID = SysAllocString(strGUID);

	bstrSubscriptionName = SysAllocString(str_StockPriceChangeSub);
  
	hr = StringFromIID(guid_StockPublisherID, &strGUID);
	bstrPublisherID = SysAllocString(strGUID);

	hr = StringFromIID(CLSID_StockEvents, &strGUID);
	bstrEventClassID = SysAllocString(strGUID);

	bstrMethodName = SysAllocString(str_StockPriceChange);

	bstrSubscriberCLSID = SysAllocString(L"{C658CAB0-89A2-11D1-891C-0080C7D771BF}");

    PropertyBagName = SysAllocString(L"StockSymbol");

    VariantInit(&PropertyBagValue);
    PropertyBagValue.vt = VT_BSTR;
    PropertyBagValue.bstrVal = SysAllocString(L"MSFT");

	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutPublisherProperty(PropertyBagName, &PropertyBagValue);

	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

    // ----------------------------------------------------
    //   Add a subscription for NewStock event in
    //   IStockEvents class
    // ----------------------------------------------------

	hr = CoCreateInstance(CLSID_CEventSubscription,
						  NULL,
						  CLSCTX_SERVER,
						  IID_IEventSubscription,
						  (void**)&pIEventSubscription);
	if (FAILED(hr))
	{
		wprintf(L"Failed to create IEventSubscription - hr = <%x>\n", hr);
		return(1);
	}

	hr = StringFromIID(guid_NewStockSub, &strGUID);
	bstrSubscriptionID = SysAllocString(strGUID);

	bstrSubscriptionName = SysAllocString(str_NewStockSub);

	hr = StringFromIID(guid_StockPublisherID, &strGUID);
	bstrPublisherID = SysAllocString(strGUID);

	hr = StringFromIID(CLSID_StockEvents, &strGUID);
	bstrEventClassID = SysAllocString(strGUID);

	bstrMethodName = SysAllocString(str_NewStock);

	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);

	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// ----------------------------------------------
	//      Cleanup 
	// ----------------------------------------------

	pIEventSystem->Release();
  
	// ----------------------------------------------
	//      Shutdown COM
	// ----------------------------------------------

	CoUninitialize();
	return rc;
}
