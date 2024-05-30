#include <stdio.h>
#include <objbase.h>
#include <assert.h>
#include <EventSys.h>
#include "db_OnlineEvents.h"
#include "db_OnlineEvents_i.c"

int main(int argc, char* argv[])
{
	int			rc   = 0;
	HRESULT		hr   = 0;
	LPOLESTR	strGUID;

	// --------------------------------------------
	//  Initialize COM
	// --------------------------------------------

	CoInitialize(NULL);
  
	// --------------------------------------------
	//  Instantiate the Event System
	// --------------------------------------------

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
	
	// --------------------------------------------
	//  Build an event class
	// --------------------------------------------
	
	BSTR	bstrEventClassID;
	BSTR	bstrEventProgID;
	BSTR	bstrFiringIID;

	IEventClass* pIEventClass = NULL;
	hr = CoCreateInstance(CLSID_CEventClass,
						  NULL,
						  CLSCTX_SERVER,
						  IID_IEventClass,
						  (void**)&pIEventClass);
	if (FAILED(hr))
	{
		wprintf(L"Failed to create IEventClass - hr = <%x>\n", hr);
		return(1);
	}

	bstrEventClassID = SysAllocString(L"{2BB5219D-F67B-11d1-9734-00805F31E0AF}");
	bstrEventProgID = SysAllocString(L"OnlineEvents");

	hr = StringFromIID(IID_IUsersOnline, &strGUID);
	bstrFiringIID = SysAllocString(strGUID);

	hr = pIEventClass->put_EventClassID(bstrEventClassID);
	hr = pIEventClass->put_EventClassName(bstrEventProgID);
	hr = pIEventClass->put_FiringInterfaceID(bstrFiringIID);

	hr = pIEventSystem->Store(PROGID_EventClass, pIEventClass);
    if (FAILED(hr))
    {
        wprintf(L"Failed to store event, hr = %x\n", hr);
        return 1 ;
    }

	pIEventClass->Release();


    // ----------------------------------------------------
    //   Add a subscription for StockPriceChange event in
    //   IStockEvents class (no property bag)
    // ----------------------------------------------------

	BSTR	bstrSubscriptionID;
	BSTR	bstrSubscriptionName;
	BSTR	bstrPublisherID;
	BSTR	bstrMethodName;
	BSTR	bstrSubscriberCLSID;
	BSTR	bstrPROGID_Subscription;
    VARIANT PropertyBagValue;
    BSTR    PropertyBagName;

	IEventSubscription	*pIEventSubscription = NULL;

	// These values stay the same per subscription
	PropertyBagName = SysAllocString(L"Table");
    VariantInit(&PropertyBagValue);
    PropertyBagValue.vt = VT_BSTR;

	// These values stay the same per subscription
	// Should not need to use publisher id
	bstrPublisherID = SysAllocString(L"{2BB5219F-F67B-11d1-9734-00805F31E0AF}");
	bstrPROGID_Subscription = SysAllocString(PROGID_EventSubscription);
	bstrMethodName = SysAllocString(L"Update");
	hr = StringFromIID(CLSID_UsersOnline, &strGUID);
	bstrSubscriberCLSID = SysAllocString(strGUID);



	// Start **** Dave Reed Subscription
	// This value changes
    PropertyBagValue.bstrVal = SysAllocString(L"davereed");

	// A unique ID for each subscription
	bstrSubscriptionID = SysAllocString(L"{2BB5219E-F67B-11d1-9734-00805F31E0AF}");
	
	// A unique name for each subscription
	bstrSubscriptionName = SysAllocString(L"OnlineSubscription1");

	// Create subscription class
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


	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutSubscriberProperty(PropertyBagName, &PropertyBagValue);


	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// End *** Dave Reed Subscription

	// Start **** Traceyt Subscription
	// This value changes
    PropertyBagValue.bstrVal = SysAllocString(L"traceyt");

	// A unique ID for each subscription
	bstrSubscriptionID = SysAllocString(L"{2916BB51-F692-11d1-9734-00805F31E0AF}");
	
	// A unique name for each subscription
	bstrSubscriptionName = SysAllocString(L"OnlineSubscription2");

	// Create subscription class
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


	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutSubscriberProperty(PropertyBagName, &PropertyBagValue);


	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// End *** TraceyT Subscription

	// Start **** GeraldH Subscription
	// This value changes
    PropertyBagValue.bstrVal = SysAllocString(L"geraldh");

	// A unique ID for each subscription
	bstrSubscriptionID = SysAllocString(L"{2916BB52-F692-11d1-9734-00805F31E0AF}");
	
	// A unique name for each subscription
	bstrSubscriptionName = SysAllocString(L"OnlineSubscription3");

	// Create subscription class
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


	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutSubscriberProperty(PropertyBagName, &PropertyBagValue);


	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// End *** GeraldH Subscription

		// Start **** MohsenA Subscription
	// This value changes
    PropertyBagValue.bstrVal = SysAllocString(L"mohsena");

	// A unique ID for each subscription
	bstrSubscriptionID = SysAllocString(L"{8C8FB523-F7FB-11d1-8A03-0080C7B23BDA}");
	
	// A unique name for each subscription
	bstrSubscriptionName = SysAllocString(L"OnlineSubscription4");

	// Create subscription class
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


	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutSubscriberProperty(PropertyBagName, &PropertyBagValue);


	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// End *** MohsenA Subscription

		// Start **** FrankRed Subscription
	// This value changes
    PropertyBagValue.bstrVal = SysAllocString(L"frankred");

	// A unique ID for each subscription
	bstrSubscriptionID = SysAllocString(L"{8C8FB524-F7FB-11d1-8A03-0080C7B23BDA}");
	
	// A unique name for each subscription
	bstrSubscriptionName = SysAllocString(L"OnlineSubscription5");

	// Create subscription class
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


	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutSubscriberProperty(PropertyBagName, &PropertyBagValue);


	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// End *** FrankRed Subscription

		// Start **** DCameron Subscription
	// This value changes
    PropertyBagValue.bstrVal = SysAllocString(L"dcameron");

	// A unique ID for each subscription
	bstrSubscriptionID = SysAllocString(L"{8C8FB525-F7FB-11d1-8A03-0080C7B23BDA}");
	
	// A unique name for each subscription
	bstrSubscriptionName = SysAllocString(L"OnlineSubscription6");

	// Create subscription class
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


	hr = pIEventSubscription->put_SubscriptionID(bstrSubscriptionID);
	hr = pIEventSubscription->put_SubscriptionName(bstrSubscriptionName);
    hr = pIEventSubscription->put_PublisherID(bstrPublisherID);
	hr = pIEventSubscription->put_EventClassID(bstrEventClassID);
	hr = pIEventSubscription->put_MethodName(bstrMethodName);
	hr = pIEventSubscription->put_SubscriberCLSID(bstrSubscriberCLSID);
	hr = pIEventSubscription->PutSubscriberProperty(PropertyBagName, &PropertyBagValue);


	hr = pIEventSystem->Store(bstrPROGID_Subscription, pIEventSubscription);
    if (FAILED(hr))
        wprintf(L"Failed to store subscription, hr = %x\n", hr);

	pIEventSubscription->Release();

	// End *** DCameron Subscription

	// --------------------------------------------
	//  Cleanup 
	// --------------------------------------------

	pIEventSystem->Release();
  
//   Test code to call the event class .....

	IUsersOnline* pIUsersOnline = NULL;
	GUID		CLSID_GUID;
	hr = IIDFromString(bstrEventClassID, &CLSID_GUID);

	hr = CoCreateInstance(CLSID_GUID,
						  NULL,
						  CLSCTX_SERVER,
						  IID_IUsersOnline,
						  (void**)&pIUsersOnline);
	if (FAILED(hr))
	{
		wprintf(L"Failed to create OnlineEvents, HRESULT=%x\n", hr);
		return (1);
	}
	wprintf(L"Successfully created OnlineEvents\n");
	
	hr = pIUsersOnline->Update(L"davereed@microsoftcom");


	// --------------------------------------------
	//  Shutdown COM
	// --------------------------------------------
	CoUninitialize();
	return rc;
}

