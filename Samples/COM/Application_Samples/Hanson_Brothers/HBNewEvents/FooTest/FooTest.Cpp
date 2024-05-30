// FooTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\HBEventClass\hb.h"
#include "..\HBEventClass\HBEventClass.h"
#include <objbase.h>

#define	exit(hr)	if FAILED(hr)	\
					goto exit;

int main(int argc, char* argv[])
{
	HRESULT		hr =0;
	IHB			*pgb =0;
	BSTR		bstrboo=0;

	hr = CoInitialize(NULL);
	exit(hr);

	hr = CoCreateInstance(__uuidof(HBEventClass),
			              NULL,
						  CLSCTX_SERVER,
						  __uuidof(IHB),
						  (LPVOID*)&pgb);
	exit(hr);

	bstrboo = SysAllocString(L"Boooh!!");
	if (!bstrboo)
		exit(E_OUTOFMEMORY);

	hr = pgb->NewEvent(bstrboo);

exit:
	if (pgb)
		pgb->Release();
	SysFreeString(bstrboo);
	CoUninitialize();
	return hr;
}

