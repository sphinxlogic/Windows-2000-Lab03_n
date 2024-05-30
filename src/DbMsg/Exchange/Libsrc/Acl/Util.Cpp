/* --------------------------------------------------------------------------

The cpp file for utility functions
It contains the following methods:
BinaryToBSTR:  Convert SBinary to a bstrized entry id
BSTRToBinary:  it does the opposite.
VariantToMAPIObject:  it converts a variant to a mapi object
AMObjectToMAPIObject: it converts a dispatch interface pointer to a mapi object
CopyBinary:  it copies a SBinary to another
IsShortTerm: Given a SBinary, determines whether it is a short term entry id
ConvertToLongTerm: Convert a short term entry id to a long term entry id

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
//
// util.cpp
//

#include "stdafx.h"
#ifdef _DEBUG
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

#include "aclcommon.h"
#include <mapix.h>
#include "util.h"
#include <xutility>
using namespace std;
#include "edkmdb.h"

#define C_ENTRYIDPROPS		1
#define I_PR_ENTRYID		0

SBinary BSTRToBinary(BSTR str)
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

HRESULT VariantToMAPIObject(VARIANT var, REFIID iid, void** ppObject)
{
	ECheckPointerClear(ppObject, void*);

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

HRESULT AMObjectToMAPIObject(LPDISPATCH pAMObject, REFIID iid, void** ppObject)
{
	HRESULT hr = S_OK;
	OLECHAR* szMAPIOBJECT = L"MAPIOBJECT";
	OLECHAR* szRawTable = L"RawTable";
	DISPID dispid;
	DISPPARAMS NoArgs = {NULL, NULL, 0, 0};
	VARIANT var;

	ECheckPointer(ppObject, void*);
	
	VariantInit(&var);

	if(pAMObject)
	{
		hr = pAMObject->GetIDsOfNames(IID_NULL, &szMAPIOBJECT, 1, LOCALE_USER_DEFAULT, &dispid);
		if(FAILED(hr))
		{
			hr = pAMObject->GetIDsOfNames(IID_NULL, &szRawTable, 1, LOCALE_USER_DEFAULT, &dispid);
		}

		if(hr == S_OK)
		{
			hr = pAMObject->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &NoArgs, &var, NULL, NULL);
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

HRESULT CopyBinary(SBinary& Source, SBinary* pDest)
{
	ECheckPointerClear(pDest, SBinary);

	if(Source.cb && IsBadReadPtr(Source.lpb, Source.cb))
		return E_INVALIDARG;

	pDest->cb = Source.cb;
	if(pDest->cb)
	{
		pDest->lpb = new BYTE[pDest->cb];
		if(pDest->lpb)
		{
			CopyMemory(pDest->lpb, Source.lpb, pDest->cb);
		}
		else
		{
			return E_OUTOFMEMORY;
		}
	}

	return S_OK;
}

BOOL IsShortTerm(SBinary &entryID)
{
	LPENTRYID	pEntryID;

	if(pEntryID=(LPENTRYID)entryID.lpb)
	{
		if(pEntryID->abFlags[0] & MAPI_SHORTTERM)
			return TRUE;
	}
	return FALSE;
}

HRESULT ConvertToLongTerm(LPMAPISESSION	pMAPISession,
						  const SBinary	&lShortEntryID,
						  SBinary **ppLongEntryID)
{
	LPADRBOOK		lpAddrBook=NULL;
	LPMAPIPROP		lpMAPIProp=NULL;
	LPSPropValue	lpSPropVals=NULL;
	SBinary			bin;
	ULONG			lObjType;
	ULONG			cValues;
	HRESULT			hr=NOERROR;
	BYTE*			lpb = NULL;

	if(pMAPISession)
	{
		if(SUCCEEDED(hr=pMAPISession->OpenAddressBook(0,NULL,AB_NO_DIALOG,&lpAddrBook)))
		{
			if(SUCCEEDED(hr=lpAddrBook->OpenEntry(lShortEntryID.cb,(LPENTRYID)lShortEntryID.lpb, 
													&IID_IMAPIProp, 
													MAPI_BEST_ACCESS, 
													&lObjType,(LPUNKNOWN*)&lpMAPIProp)))
			{
		
				SizedSPropTagArray(C_ENTRYIDPROPS, rgPropTag)=
				{
			    	C_ENTRYIDPROPS,
    				{
						PR_ENTRYID,
    				}
				};
				if(SUCCEEDED(hr=MAPIAllocateBuffer(sizeof(SPropValue)*C_ENTRYIDPROPS,(LPVOID*)&lpSPropVals)))
				{
					if(SUCCEEDED(hr=lpMAPIProp->GetProps((LPSPropTagArray)&rgPropTag,0,&cValues,&lpSPropVals)))
					{
						if(cValues>=I_PR_ENTRYID)
						{
							if(PT_BINARY==PROP_TYPE(lpSPropVals[I_PR_ENTRYID].ulPropTag))
							{
								bin = lpSPropVals[I_PR_ENTRYID].Value.bin;
								hr = MAPIAllocateBuffer( sizeof(SBinary), (void**)ppLongEntryID );
								if( SUCCEEDED(hr) )
								{
									(*ppLongEntryID)->cb = bin.cb;
									hr = MAPIAllocateMore( bin.cb, *ppLongEntryID, (void**)&lpb );
									if( SUCCEEDED(hr) )
									{
										memcpy(lpb, bin.lpb, bin.cb);
										(*ppLongEntryID)->lpb = lpb;
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
		hr=E_INVALIDARG;

	MAPIFreeBuffer(lpSPropVals);
	if(lpAddrBook)
		lpAddrBook->Release();
	if(lpMAPIProp)
		lpMAPIProp->Release();

	return hr;
}
