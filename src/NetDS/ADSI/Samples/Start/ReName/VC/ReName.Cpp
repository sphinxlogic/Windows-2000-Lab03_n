// Rename.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "activeds.h"

int main(int argc, char* argv[])
{
	HRESULT hr;
    IADsContainer *pCont=NULL;
	IDispatch *pDisp=NULL;

    CoInitialize(NULL);

    hr = ADsGetObject(L"WinNT://INDEPENDENCE", IID_IADsContainer, (void**) &pCont);
    if ( !SUCCEEDED(hr) )
    {
        return 0;
    }
	hr = pCont->MoveHere(L"WinNT://INDEPENDENCE/JSmith",L"JJohnson", &pDisp );

	if ( SUCCEEDED(hr) )
	{
		pDisp->Release();
	}

	CoUninitialize();

	return 0;
}
