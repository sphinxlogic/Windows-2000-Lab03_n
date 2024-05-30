// hatStuff.cpp : Implementation of CDb_OnlineEventsApp and DLL registration.

#include "stdafx.h"
#include "db_OnlineEvents.h"
#include "hatStuff.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP ChatStuff::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IChatStuff,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
