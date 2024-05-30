// ----------------------------------------------------------------------------
//	util.cpp	- utility functions
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#include "stdafx.h"
#include <mapix.h>
#include <mapiutil.h>
#include <xutility>
using namespace std;
#include "edkmdb.h"
#include "util.h"
#include "math.h"

int		GetByteInt(char cChar);
void	intToStr(LPWSTR lpWStr,BYTE data);
void	intToStr(LPWSTR lpWStr,WORD data);
void	intToStr(LPWSTR lpWStr,DWORD data);
BOOL	tmFromVariantDate(DATE dtSrc,struct tm &tmDest);
BOOL	dateFromSysTime(const SYSTEMTIME &sysTime, DATE &dtDest);

#define MIN_DATE	(-657434L)		// about year 100
#define MAX_DATE    2958465L		// about year 9999
#define HALF_SECOND	(1.0/172800.0)	// Half a second, expressed in days
static int rgMonthDays[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

enum ADDRESS_PROPS
{
	I_ENTRYID,
	I_RECIPIENT_TYPE,
 	C_ADDRESSPROPS
};

BSTR BinaryToBSTR(SBinary* pBinary)
{
	ULONG	cb=pBinary->cb;
    BSTR	strReturn=pBinary ? SysAllocStringLen(NULL,_cpp_max(pBinary->cb * 2,(ULONG)1)): NULL;
	LPBYTE	pb=pBinary->lpb;
	LPWSTR	psz=strReturn;
	  
	if(psz)
	{
		while(cb--)
		{
			int n1=*pb & 0x0f;
			int n2 =(*pb >> 4)& 0x0f;

			*psz++ =(BYTE)(n2 +(n2 >= 10 ?(L'A' - 10): L'0'));
			*psz++ =(BYTE)(n1 +(n1 >= 10 ?(L'A' - 10): L'0'));
			++pb;
		}
		*psz=0;
	}

	return strReturn;
}

SBinary BSTRToBinary(BSTR str)
{
	int		ich=0;
	int		cch;
	SBinary bin={0};
	LPBYTE  pb=NULL;

	if(str)
	{
		cch=SysStringLen(str);
		if(cch && !(cch & 1))
		{
			pb=bin.lpb=new BYTE[cch / 2];
			if(pb)
			{
				bin.cb=cch / 2;

				while(str[ich])
				{
					int		n=str[ich];
					int		ny;

					if(n >= L'0' && n <= L'9')
						ny=n - L'0';
					else if(n >= L'A' && n <= L'F')
						ny=n - L'A' + 10;
					else if(n >= L'a' && n <= L'f')
						ny=n - L'a' + 10;
					else
						break;

					if(ich++ & 1)
						*pb++ |= ny;
					else
						*pb =(BYTE)(ny << 4);
				}
			}
		}
	}

	return bin;
}

HRESULT VariantToMAPIObject(VARIANT var,REFIID iid,void** ppObject)
{
	ECheckPointerClear(ppObject,void*);

	HRESULT hr=NOERROR;
	VARIANT varCopy;

	VariantInit(&varCopy);
	VariantCopyInd(&varCopy,&var);

	switch(varCopy.vt)
	{
	case VT_DISPATCH:
		if(varCopy.pdispVal)
		{
			hr=AMObjectToMAPIObject(varCopy.pdispVal,iid,ppObject);
			if(FAILED(hr))
			{
				hr=varCopy.pdispVal->QueryInterface(iid,(void**)ppObject);
			}
		}
		else
		{
			hr=E_INVALIDARG;
		}

		break;

	case VT_UNKNOWN:
		if(varCopy.punkVal)
		{
			hr=varCopy.punkVal->QueryInterface(iid,(void**)ppObject);
		}
		else
		{
			hr=E_INVALIDARG;
		}
		
		break;

	default:
		hr=DISP_E_TYPEMISMATCH;

		break;
	}

	VariantClear(&varCopy);

	return(hr);
}

HRESULT AMObjectToMAPIObject(LPDISPATCH pAMObject,REFIID iid,void** ppObject)
{
	DISPID		dispid;
	VARIANT		var;
	HRESULT		hr=NOERROR;
	OLECHAR		*szMAPIOBJECT=L"MAPIOBJECT";
	OLECHAR		*szRawTable=L"RawTable";
	DISPPARAMS	NoArgs={NULL,NULL,0,0};

	ECheckPointer(ppObject,void*);
	VariantInit(&var);

	if(pAMObject)
	{
		if(SUCCEEDED(hr=pAMObject->GetIDsOfNames(IID_NULL,&szMAPIOBJECT,1,LOCALE_USER_DEFAULT,&dispid)))
			if(SUCCEEDED(hr=pAMObject->Invoke(dispid,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_PROPERTYGET,&NoArgs,&var,NULL,NULL)))
			{
				hr=var.punkVal->QueryInterface(iid,(void**)ppObject);
				VariantClear(&var);
			}
		else
			hr=pAMObject->GetIDsOfNames(IID_NULL,&szRawTable,1,LOCALE_USER_DEFAULT,&dispid);
	}
	else
		hr=E_INVALIDARG;
	return(hr);
}

void ReplaceBadCharsA(LPSTR pszName,LPSTR pszBad,CHAR chNew)
{
	LPSTR pszCurrent=pszName;
	
	while(*(pszCurrent += strcspn(pszCurrent,pszBad)))
	{
		(*pszCurrent)= chNew;
	}
}

void ReplaceBadCharsW(LPWSTR pszName,LPWSTR pszBad,WCHAR chNew)
{
	LPWSTR pszCurrent=pszName;
	
	while(*(pszCurrent += wcscspn(pszCurrent,pszBad)))
	{
		(*pszCurrent)= chNew;
	}
}

HRESULT CopyBinary(SBinary& Source,SBinary* pDest)
{
	HRESULT		hr=NOERROR;

	ECheckPointerClear(pDest,SBinary);
	if(Source.cb && !IsBadReadPtr(Source.lpb,Source.cb))
	{
		if(pDest->cb=Source.cb)
		{
			pDest->lpb=new BYTE[pDest->cb];
			if(pDest->lpb)
				CopyMemory(pDest->lpb,Source.lpb,pDest->cb);
			else
				hr = E_OUTOFMEMORY;
		}
	}
	else
		hr = E_INVALIDARG;
	return hr;
}

HRESULT CheckProps(LPSPropTagArray pOld,LPSPropValue pNew)
{
	ULONG iProp=0;

	for(iProp=0;iProp<pOld->cValues;iProp++)
	{
		if(pNew[iProp].ulPropTag!= pOld->aulPropTag[iProp])
			break;
	}
	return iProp == pOld->cValues ? NOERROR : MAPI_E_NOT_FOUND;
}

bool IsServerStore(SBinary GUID)
{
	if(GUID.cb == sizeof(pbExchangeProviderPublicGuid)- 1 && 0 == memcmp(GUID.lpb,pbExchangeProviderPublicGuid,GUID.cb))
		return true;
	if(GUID.cb == sizeof(pbExchangeProviderPrimaryUserGuid)- 1 && 0 == memcmp(GUID.lpb,pbExchangeProviderPrimaryUserGuid,GUID.cb))
		return true;
	if(GUID.cb == sizeof(pbExchangeProviderDelegateGuid)- 1 && 0 == memcmp(GUID.lpb,pbExchangeProviderDelegateGuid,GUID.cb))
		return true;
	
	return false;
}

bool IsPublicStore(SBinary GUID)
{
	if(GUID.cb == sizeof(pbExchangeProviderPublicGuid)- 1 && 0 == memcmp(GUID.lpb,pbExchangeProviderPublicGuid,GUID.cb))
		return true;

	return false;
}

HRESULT GetBaseAddressProps(SAFEARRAY	*psaAdrList,
							void		*lpObject,
							LPADRLIST	lpAdrList)
{
	long			index=0;
	ULONG			cEntries=0;
	SBinary			lEntryID;
	VARIANT			lVar;
	HRESULT			hr=NOERROR;
	LPADRENTRY		lpAdrEntry=NULL;

	if((psaAdrList)&&(psaAdrList->rgsabound[0].cElements))
	{
		cEntries = psaAdrList->rgsabound[0].cElements;
		for(index=0;(index<cEntries)&&(SUCCEEDED(hr));index++)
		{
			lpAdrEntry = &lpAdrList->aEntries[index];
			if(SUCCEEDED(hr=SafeArrayGetElement(psaAdrList,&index,&lVar)))
			{
				if(VT_BSTR==lVar.vt)
				{
					lEntryID = BSTRToBinary(lVar.bstrVal);
					if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SPropValue)*C_ADDRESSPROPS,lpObject,(LPVOID*)&lpAdrEntry->rgPropVals)))
					{
						lpAdrEntry->ulReserved1 = 0;
						lpAdrEntry->cValues = C_ADDRESSPROPS;
						lpAdrEntry->rgPropVals[I_ENTRYID].ulPropTag = PR_ENTRYID;
						lpAdrEntry->rgPropVals[I_ENTRYID].dwAlignPad= 0;
						if(SUCCEEDED(hr=MAPIAllocateMore(lEntryID.cb,lpObject,
														 (void**)&lpAdrEntry->rgPropVals[I_ENTRYID].Value.bin.lpb)))
						{
							lpAdrEntry->rgPropVals[I_ENTRYID].Value.bin.cb = lEntryID.cb;
							memcpy(lpAdrEntry->rgPropVals[I_ENTRYID].Value.bin.lpb,lEntryID.lpb,lEntryID.cb);
							lpAdrEntry->rgPropVals[I_RECIPIENT_TYPE].ulPropTag = PR_RECIPIENT_TYPE;
							lpAdrEntry->rgPropVals[I_RECIPIENT_TYPE].dwAlignPad= 0;
							lpAdrEntry->rgPropVals[I_RECIPIENT_TYPE].Value.l = MAPI_TO;
						}
					}
					delete lEntryID.lpb;
				}
			}
		}
	}
	else
		hr=E_INVALIDARG;
	return hr;
}

HRESULT PropertyInvoke(LPDISPATCH pDispatch,WORD wFlags,_bstr_t propbSTR,VARIANT *pVarResult,DISPPARAMS *pDispParams)
{
	BSTR			bStrName;
	HRESULT			hr=NOERROR;
	VARDESC			*pVarDesc=NULL;
	MEMBERID		lMemID;
	ITypeInfo		*pTypeInfo=NULL;
	DISPPARAMS		dispParmsNoArgs={NULL,NULL,0,0};
	unsigned int	pcNames=0;
	unsigned int	propName=0;
	unsigned int	uArgErr=0;
	
	if(pDispatch)
	{
		if(SUCCEEDED(hr=pDispatch->GetTypeInfo(0,LOCALE_USER_DEFAULT,&pTypeInfo)))
		{
			pTypeInfo->AddRef();
			EXCEPINFO	lExcepInfo;

			for(propName=0;SUCCEEDED(hr=pTypeInfo->GetVarDesc(propName,&pVarDesc));propName++)
			{
				lMemID=pVarDesc->memid;
				pTypeInfo->GetNames(lMemID,&bStrName,1,&pcNames);
			
				if(_bstr_t(bStrName,false)==propbSTR)
				{
					// invoke a prop_get on this object to retrieve the value in VARIANT
					if(pVarDesc && pVarResult)
					{
						if(NULL==pDispParams)
							pDispParams = &dispParmsNoArgs;
						hr = pDispatch->Invoke(pVarDesc->memid,IID_NULL,LOCALE_USER_DEFAULT,
											   wFlags,pDispParams,pVarResult,&lExcepInfo,&uArgErr);
					}
					pTypeInfo->ReleaseVarDesc(pVarDesc);
					break;
				}
				pTypeInfo->ReleaseVarDesc(pVarDesc);
			}
		}
	}
	else
		hr=E_INVALIDARG;

	if(pTypeInfo)
		pTypeInfo->Release();
	return hr;
}

HRESULT MethodInvoke(LPDISPATCH pDispatch,_bstr_t propbSTR,VARIANT *pVarResult,DISPPARAMS *pDispParams,WORD wFlags)
{
	BSTR			bStrName;
	HRESULT			hr=NOERROR;
	FUNCDESC		*pFuncDesc=NULL;
	MEMBERID		lMemID;
	ITypeInfo		*pTypeInfo=NULL;
	unsigned int	pcNames=0;
	unsigned int	propName=0;
	unsigned int	uArgErr=0;

	if(pDispatch)
	{
		if(SUCCEEDED(hr=pDispatch->GetTypeInfo(0,LOCALE_USER_DEFAULT,&pTypeInfo)))
		{
			pTypeInfo->AddRef();
			for(propName=0;SUCCEEDED(hr=pTypeInfo->GetFuncDesc(propName,&pFuncDesc));propName++)
			{
				lMemID=pFuncDesc->memid;
				pTypeInfo->GetNames(lMemID,&bStrName,1,&pcNames);
			
				if(_bstr_t(bStrName,false)==propbSTR)
				{
					if(pFuncDesc && pVarResult)
					{
						hr = pDispatch->Invoke(pFuncDesc->memid,IID_NULL,LOCALE_USER_DEFAULT,
											   wFlags,pDispParams,pVarResult,NULL,&uArgErr);
					}
					pTypeInfo->ReleaseFuncDesc(pFuncDesc);
					break;
				}
				pTypeInfo->ReleaseFuncDesc(pFuncDesc);
			}
		}
	}
	else
		hr=E_INVALIDARG;

	if(pTypeInfo)
		pTypeInfo->Release();
	return hr;
}

HRESULT ConvertVariantToPropValue(VARIANT lVariant,LPSPropValue lpPropVal)
{
	long	cbT=0;
	long	lCount=0;
	HRESULT	hr=E_INVALIDARG;
	ULONG	ulPropType=0;

	if(!lpPropVal)
		return E_INVALIDARG;

	ulPropType=PROP_TYPE(lpPropVal->ulPropTag);
	switch(lVariant.vt)
	{
	case VT_I2:
		if((PT_I2==ulPropType)||(PT_I4==ulPropType))
		{
			lpPropVal->Value.i=lVariant.iVal;
			hr = NOERROR;
		}
		break;

	case VT_I4:
		if(PT_I4==ulPropType)
		{
			lpPropVal->Value.l=lVariant.lVal;
			hr = NOERROR;
		}
		break;

	case VT_R4:
		if((PT_R4==ulPropType)||(PT_R8==ulPropType))
		{
			lpPropVal->Value.flt=lVariant.fltVal;
			hr = NOERROR;
		}
		break;

	case VT_R8:
		if(PT_R8 == ulPropType)
		{
			lpPropVal->Value.dbl=lVariant.dblVal;
			hr = NOERROR;
		}
		else if(PT_APPTIME  == ulPropType)
		{
			lpPropVal->Value.at=lVariant.dblVal;
			hr = NOERROR;
		}
		else if(PT_I8 == ulPropType)
		{
			memcpy((void*)&lpPropVal->Value.li,(void*)&lVariant.dblVal,sizeof(LARGE_INTEGER));
			hr = NOERROR;
		}
		break;

	case VT_BOOL:
		if((PT_I2==ulPropType)||(PT_I4==ulPropType)||(PT_BOOLEAN==ulPropType))
		{
			lpPropVal->Value.b =(lVariant.boolVal==VARIANT_TRUE)? 1:0;
			hr = NOERROR;
		}
		break;

	case VT_CY:
		if(PT_CURRENCY==ulPropType)
		{
			lpPropVal->Value.cur=lVariant.cyVal;
			hr = NOERROR;
		}
		break;

	case VT_DATE:
		if(PT_APPTIME==ulPropType)
		{
			lpPropVal->Value.at = lVariant.date;
			hr = NOERROR;
		}
		else if(PT_SYSTIME==ulPropType)
		{
			struct tm	tmDate;
			
			if(tmFromVariantDate(lVariant.date,tmDate))
			{
				SYSTEMTIME	sysTime;
				FILETIME	fileTime;

				sysTime.wYear		= tmDate.tm_year;
				sysTime.wMonth		= tmDate.tm_mon;
				sysTime.wDayOfWeek	= tmDate.tm_wday;
				sysTime.wDay		= tmDate.tm_mday;
				sysTime.wHour		= tmDate.tm_hour;
				sysTime.wMinute		= tmDate.tm_min;
				sysTime.wSecond		= tmDate.tm_sec;
				sysTime.wMilliseconds = 0;

				if(SystemTimeToFileTime(&sysTime,&fileTime))
					if(LocalFileTimeToFileTime(&fileTime,&lpPropVal->Value.ft))
						hr = NOERROR;
			}
		}
		break;

	case VT_ERROR:
		if(PT_ERROR==ulPropType)
		{
			lpPropVal->Value.err=lVariant.scode;
			hr = NOERROR;
		}
		break;

	case VT_BSTR:
		{
			switch(ulPropType)
			{
			case PT_BINARY:
				lpPropVal->Value.bin=BSTRToBinary(lVariant.bstrVal);
				hr = NOERROR;
				break;

			case PT_STRING8:
				{
					_bstr_t		bstrt(lVariant.bstrVal);
					const char	*lpszA =(const char*)bstrt;
					if(lpPropVal->Value.lpszA=new char[lstrlenA(lpszA)+1])
					{
						lstrcpyA(lpPropVal->Value.lpszA,lpszA);
						hr = NOERROR;
					}
				}
				break;

			case PT_UNICODE:
				{
					_bstr_t		bstrt(lVariant.bstrVal);
					const WCHAR *lpszW =(const WCHAR*)bstrt;
					cbT =(lstrlenW(lpszW)+1)*sizeof(WCHAR);
					if(lpPropVal->Value.lpszW=new WCHAR[cbT])
					{
						memcpy(lpPropVal->Value.lpszW,lpszW,cbT);
						hr = NOERROR;
					}
				}
				break;

			case PT_CLSID:
				{
					if(lpPropVal->Value.lpguid=new GUID)
					{
						*lpPropVal->Value.lpguid = BSTRToGUID(lVariant.bstrVal);
						hr = NOERROR;
					}
				}
				break;
			}
			break;
		}
		break;

	case VT_ARRAY|VT_I2:
		if(PT_MV_I2 == ulPropType)
		{
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVi.cValues=lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVi.lpi	=new short[lpPropVal->Value.MVi.cValues])
				{
					memcpy( lpPropVal->Value.MVi.lpi,lVariant.parray->pvData,
							sizeof(short)*lpPropVal->Value.MVi.cValues);
					hr = NOERROR;
				}
			}
		}
		break;

	case VT_ARRAY|VT_I4:
		if(PT_MV_I4==ulPropType)
		{
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVl.cValues=lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVl.lpl	= new long[lpPropVal->Value.MVl.cValues])
				{
					memcpy( lpPropVal->Value.MVl.lpl,lVariant.parray->pvData,
							sizeof(long)*lpPropVal->Value.MVl.cValues);
					hr = NOERROR;
				}
			}
		}
		break;

	case VT_ARRAY|VT_R4:
		if(PT_MV_R4== ulPropType)
		{
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVflt.cValues	= lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVflt.lpflt	= new float[lpPropVal->Value.MVflt.cValues])
				{
					memcpy( lpPropVal->Value.MVflt.lpflt,lVariant.parray->pvData,
							sizeof(float)*lpPropVal->Value.MVflt.cValues);
					hr = NOERROR;
				}
			}
		}
		break;
	
	case VT_ARRAY|VT_R8:
		if((PT_MV_DOUBLE == ulPropType)||(PT_MV_APPTIME == ulPropType))
		{
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVdbl.cValues	= lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVdbl.lpdbl	= new double[lpPropVal->Value.MVdbl.cValues])
				{
					memcpy( lpPropVal->Value.MVdbl.lpdbl,lVariant.parray->pvData,
							sizeof(double)*lpPropVal->Value.MVdbl.cValues);
					hr = NOERROR;
				}
			}
		}
		else if(PT_MV_APPTIME == ulPropType)
		{
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVat.cValues	= lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVat.lpat	= new double[lpPropVal->Value.MVat.cValues])
				{
					memcpy( lpPropVal->Value.MVat.lpat,lVariant.parray->pvData,
							sizeof(double)*lpPropVal->Value.MVat.cValues);
					hr = NOERROR;
				}
			}
		}
		else if(PT_MV_I8 == ulPropType)
		{
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVli.cValues=lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVli.lpli=new LARGE_INTEGER[lpPropVal->Value.MVli.cValues])
				{
					memcpy( lpPropVal->Value.MVli.lpli,lVariant.parray->pvData,
							sizeof(LARGE_INTEGER)*lpPropVal->Value.MVli.cValues);
					hr = NOERROR;
				}
			}
		}
		break;

	case VT_ARRAY|VT_CY:
		if(PT_MV_CURRENCY == ulPropType)
		{
			if(lVariant.parray->cDims == 1)
			lpPropVal->Value.MVcur.cValues	= lVariant.parray->rgsabound[0].cElements;
			if(lpPropVal->Value.MVcur.lpcur	= new CURRENCY[lpPropVal->Value.MVcur.cValues])
			{
				memcpy( lpPropVal->Value.MVcur.lpcur,lVariant.parray->pvData,
						sizeof(CURRENCY)*lpPropVal->Value.MVcur.cValues);
				hr = NOERROR;
			}
		}
		break;

	case VT_ARRAY|VT_DATE:
		if((PT_MV_SYSTIME==ulPropType)||(PT_MV_APPTIME==ulPropType))
		{
			if(lVariant.parray->cDims == 1)
			{
				if(PT_MV_APPTIME==ulPropType)
				{
					lpPropVal->Value.MVat.cValues	= lVariant.parray->rgsabound[0].cElements;
					if(lpPropVal->Value.MVat.lpat	= new double[lpPropVal->Value.MVat.cValues])
					{
						memcpy(lpPropVal->Value.MVft.lpft,lVariant.parray->pvData,sizeof(double)*lpPropVal->Value.MVat.cValues);
						hr = NOERROR;
					}
				}
				else if(PT_MV_SYSTIME==ulPropType)
				{
					lpPropVal->Value.MVft.cValues	= lVariant.parray->rgsabound[0].cElements;
					if(lpPropVal->Value.MVft.lpft	= new FILETIME[lpPropVal->Value.MVft.cValues])
					{
						struct tm	tmDate;
						SYSTEMTIME	sysTime;
						for(long lCount=0;lCount<lpPropVal->Value.MVft.cValues;lCount++)
						{
							if(tmFromVariantDate(lVariant.date,tmDate))
							{
								sysTime.wYear		= tmDate.tm_year;
								sysTime.wMonth		= tmDate.tm_mon+1;	// struct tm month range is 0-11, while systimes' is 1-12
								sysTime.wDayOfWeek	= tmDate.tm_wday;
								sysTime.wDay		= tmDate.tm_mday;	//	day of the month
								sysTime.wHour		= tmDate.tm_hour;
								sysTime.wMinute		= tmDate.tm_min;
								sysTime.wSecond		= tmDate.tm_sec;
								sysTime.wMilliseconds = 0;
								if(!SystemTimeToFileTime(&sysTime,&lpPropVal->Value.MVft.lpft[lCount]))
									break;
							}
						}
					}
				}
			}
		}
		break;

	case VT_ARRAY|VT_BSTR:
	{
		BSTR	tmpBSTR;

		switch(ulPropType)
		{
		case PT_MV_BINARY:
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVbin.cValues = lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVbin.lpbin= new SBinary[lpPropVal->Value.MVbin.cValues])
				{
					for(lCount=0;lCount<lpPropVal->Value.MVbin.cValues;lCount++)
					{
						SafeArrayGetElement(lVariant.parray,&lCount,&tmpBSTR);
						lpPropVal->Value.MVbin.lpbin[lCount]=BSTRToBinary(tmpBSTR);
					}
					hr = NOERROR;
				}
			}
			break;

		case PT_STRING8:
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVszA.cValues=lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVszA.lppszA=new LPSTR[lpPropVal->Value.MVszA.cValues])
				{
					for(lCount=0;lCount<lpPropVal->Value.MVszA.cValues;lCount++)
					{
						SafeArrayGetElement(lVariant.parray,&lCount,&tmpBSTR);
						_bstr_t		bstrt(tmpBSTR);
						const char	*lpszA =(const char*)bstrt;
						if(lpPropVal->Value.MVszA.lppszA[lCount]=new char[lstrlenA(lpszA)+1])
						{
							lstrcpyA(lpPropVal->Value.MVszA.lppszA[lCount],lpszA);
						}
					}
					hr = NOERROR;
				}
			}
			break;

		case PT_UNICODE:
			if(lVariant.parray->cDims == 1)
			{
				lpPropVal->Value.MVszW.cValues=lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVszW.lppszW=new LPWSTR[lpPropVal->Value.MVszW.cValues])
				{
					for(lCount=0;lCount<lpPropVal->Value.MVszW.cValues;lCount++)
					{
						SafeArrayGetElement(lVariant.parray,&lCount,&tmpBSTR);
						_bstr_t		bstrt(tmpBSTR);
						const WCHAR *lpszW =(const WCHAR*)bstrt;
						cbT =(lstrlenW(lpszW)+1)*sizeof(WCHAR);
						if(lpPropVal->Value.MVszW.lppszW[lCount]=new WCHAR[cbT])
							memcpy(lpPropVal->Value.MVszW.lppszW[lCount],lpszW,cbT);
					}
					hr = NOERROR;
				}
			}
			break;


		case PT_CLSID:
			if(lVariant.parray->cDims==1)
			{
				lpPropVal->Value.MVguid.cValues=lVariant.parray->rgsabound[0].cElements;
				if(lpPropVal->Value.MVguid.lpguid=new GUID[lpPropVal->Value.MVguid.cValues])
				{
					for(lCount=0;lCount<lpPropVal->Value.MVguid.cValues;lCount++)
					{
						if(SUCCEEDED(hr=SafeArrayGetElement(lVariant.parray,&lCount,&tmpBSTR)))
							lpPropVal->Value.MVguid.lpguid[lCount] = BSTRToGUID(tmpBSTR);
						else
							break;
					}
					hr = NOERROR;
				}
			}
			break;
		}
	}
	case VT_NULL:
		break;

	default:
		return E_INVALIDARG;
	}
	return hr;
}

HRESULT ReleasePropVal(LPSPropValue lpPropVal)
{
	long	lCount=0;
	HRESULT	hr=NOERROR;
	
	if(!lpPropVal)
		return E_INVALIDARG;

	switch(PROP_TYPE(lpPropVal->ulPropTag))
	{
	default:
		return E_INVALIDARG;
	case PT_I2:
	case PT_LONG:
	case PT_R4:
	case PT_APPTIME:
	case PT_DOUBLE:
	case PT_BOOLEAN:
	case PT_CURRENCY:
	case PT_SYSTIME:
	case PT_CLSID:
	case PT_I8:
	case PT_ERROR:
	case PT_NULL:
			return hr;	// nothing to do

	case PT_BINARY:
		delete [] lpPropVal->Value.bin.lpb;
		break;

	case PT_STRING8:
		delete [] lpPropVal->Value.lpszA;
		break;

	case PT_UNICODE:
		delete [] lpPropVal->Value.lpszW;
		break;

	case PT_MV_I2:
		delete [] lpPropVal->Value.MVi.lpi;
		break;

	case PT_MV_LONG:
		delete [] lpPropVal->Value.MVl.lpl;
		break;

	case PT_MV_R4:
		delete [] lpPropVal->Value.MVflt.lpflt;
		break;

	case PT_MV_APPTIME:
		delete [] lpPropVal->Value.MVat.lpat;
		break;

	case PT_MV_DOUBLE:
		delete [] lpPropVal->Value.MVdbl.lpdbl;
		break;

	case PT_MV_CURRENCY:
		delete [] lpPropVal->Value.MVcur.lpcur;
		break;

	case PT_MV_SYSTIME:
		delete [] lpPropVal->Value.MVft.lpft;
		break;

	case PT_MV_CLSID:
		delete [] lpPropVal->Value.MVguid.lpguid;
		break;

	case PT_MV_I8:
		delete [] lpPropVal->Value.MVli.lpli;
		break;

	case PT_MV_BINARY:
		for(lCount=0;lCount<lpPropVal->Value.MVbin.cValues;lCount++)
		{
			delete [] lpPropVal->Value.MVbin.lpbin[lCount].lpb;
		}
		delete [] lpPropVal->Value.MVbin.lpbin;
		break;

	case PT_MV_STRING8:
		for(lCount=0;lCount<lpPropVal->Value.MVszA.cValues;lCount++)
		{
			delete [] lpPropVal->Value.MVszA.lppszA[lCount];
		}
		delete [] lpPropVal->Value.MVszA.lppszA;
		break;

	case PT_MV_UNICODE:
		for(lCount=0;lCount<lpPropVal->Value.MVszA.cValues;lCount++)
		{
			delete [] lpPropVal->Value.MVszW.lppszW[lCount];
		}
		delete [] lpPropVal->Value.MVszW.lppszW;
		break;
	}
	return hr;
}

HRESULT CopyPropVal(LPSPropValue lpPropDst,LPSPropValue lpPropSrc,void* lpObject)
{
	long	cbT=0;
	long	lCount=0;
	HRESULT	hr=NOERROR;
	
	lpPropDst->ulPropTag=lpPropSrc->ulPropTag;
	switch(PROP_TYPE(lpPropDst->ulPropTag))
	{
	default:
		return E_INVALIDARG;
	case PT_I2:
	case PT_LONG:
	case PT_R4:
	case PT_APPTIME:
	case PT_DOUBLE:
	case PT_BOOLEAN:
	case PT_CURRENCY:
	case PT_SYSTIME:
	case PT_CLSID:
	case PT_I8:
	case PT_ERROR:
	case PT_NULL:
		memcpy((void*)&lpPropDst->Value,(void*)&lpPropSrc->Value,sizeof(union _PV));
		return hr;	// nothing to do

	case PT_BINARY:
		cbT=lpPropDst->Value.bin.cb=lpPropSrc->Value.bin.cb;
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.bin.lpb)))
			memcpy(lpPropDst->Value.bin.lpb,lpPropSrc->Value.bin.lpb,lpPropDst->Value.bin.cb);
		break;

	case PT_STRING8:
		cbT=lstrlenA(lpPropSrc->Value.lpszA)+ 1;
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.lpszA)))
			memcpy(lpPropDst->Value.lpszA,lpPropSrc->Value.lpszA,cbT);
		break;

	case PT_UNICODE:
		cbT =(lstrlenW(lpPropSrc->Value.lpszW)+ 1)* sizeof(WCHAR);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.lpszW)))
			memcpy(lpPropDst->Value.lpszW,lpPropSrc->Value.lpszW,cbT);
		break;

	case PT_MV_I2:
		cbT=lpPropSrc->Value.MVi.cValues * sizeof(short int);
		lpPropDst->Value.MVi.cValues=lpPropSrc->Value.MVi.cValues;
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVi.lpi)))
			memcpy(lpPropDst->Value.MVi.lpi,lpPropSrc->Value.MVi.lpi,cbT);
		break;

	case PT_MV_LONG:
		cbT=lpPropSrc->Value.MVl.cValues * sizeof(long);
		lpPropDst->Value.MVl.cValues=lpPropSrc->Value.MVl.cValues;
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVl.lpl)))
			memcpy(lpPropDst->Value.MVl.lpl,lpPropSrc->Value.MVl.lpl,cbT);
		break;

	case PT_MV_R4:
		cbT=lpPropSrc->Value.MVflt.cValues * sizeof(float);
		lpPropDst->Value.MVflt.cValues=lpPropSrc->Value.MVflt.cValues;
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVflt.lpflt)))
			memcpy(lpPropDst->Value.MVflt.lpflt,lpPropSrc->Value.MVflt.lpflt,cbT);
		break;

	case PT_MV_APPTIME:
		cbT=lpPropSrc->Value.MVat.cValues * sizeof(double);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVat.lpat)))
			memcpy(lpPropDst->Value.MVat.lpat,lpPropSrc->Value.MVat.lpat,cbT);
		break;

	case PT_MV_DOUBLE:
		cbT=lpPropSrc->Value.MVdbl.cValues * sizeof(double);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVdbl.lpdbl)))
			memcpy(lpPropDst->Value.MVdbl.lpdbl,lpPropSrc->Value.MVdbl.lpdbl,cbT);
		break;

	case PT_MV_CURRENCY:
		cbT=lpPropSrc->Value.MVcur.cValues * sizeof(CURRENCY);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVcur.lpcur)))
			memcpy(lpPropDst->Value.MVcur.lpcur,lpPropSrc->Value.MVcur.lpcur,cbT);
		break;

	case PT_MV_SYSTIME:
		cbT=lpPropSrc->Value.MVft.cValues * sizeof(FILETIME);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
									     (void**)&lpPropDst->Value.MVft.lpft)))
			memcpy(lpPropDst->Value.MVft.lpft,lpPropSrc->Value.MVft.lpft,cbT);
		break;

	case PT_MV_CLSID:
		cbT=lpPropSrc->Value.MVguid.cValues * sizeof(GUID);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVguid.lpguid)))
			memcpy(lpPropDst->Value.MVguid.lpguid,lpPropSrc->Value.MVguid.lpguid,cbT);
		break;

	case PT_MV_I8:
		cbT=lpPropSrc->Value.MVli.cValues * sizeof(LARGE_INTEGER);
		if(SUCCEEDED(hr=MAPIAllocateMore(cbT,lpObject,
										 (void**)&lpPropDst->Value.MVli.lpli)))
			memcpy(lpPropDst->Value.MVli.lpli,lpPropSrc->Value.MVli.lpli,cbT);
		break;

	case PT_MV_BINARY:
		if(SUCCEEDED(hr=MAPIAllocateMore(lpPropSrc->Value.MVbin.cValues*sizeof(SBinary*),
										 lpObject,
										 (void**)&lpPropDst->Value.MVbin.lpbin)))
		{
			for(lCount=0;lCount<lpPropSrc->Value.MVbin.cValues;lCount++)
			{
				lpPropDst->Value.MVbin.lpbin[lCount].cb=
						lpPropSrc->Value.MVbin.lpbin[lCount].cb;
				if(SUCCEEDED(hr=MAPIAllocateMore(lpPropDst->Value.MVbin.lpbin[lCount].cb,
												 lpObject,
												 (void**)&lpPropDst->Value.MVbin.lpbin[lCount].lpb)))
					memcpy(lpPropDst->Value.MVbin.lpbin[lCount].lpb,
						   lpPropSrc->Value.MVbin.lpbin[lCount].lpb,
						   lpPropSrc->Value.MVbin.lpbin[lCount].cb);
				else
					break;
			}
		}
		break;

	case PT_MV_STRING8:
		if(SUCCEEDED(hr=MAPIAllocateMore(lpPropSrc->Value.MVszA.cValues*sizeof(LPSTR),
										 lpObject,
										 (void**)&lpPropDst->Value.MVszA.lppszA)))
		{
			for(lCount=0;lCount<lpPropSrc->Value.MVszA.cValues;lCount++)
			{
				if(SUCCEEDED(hr=MAPIAllocateMore(lstrlenA(lpPropSrc->Value.MVszA.lppszA[lCount]),
												 lpObject,
												 (void**)&lpPropDst->Value.MVszA.lppszA[lCount])))
					lstrcpyA(lpPropDst->Value.MVszA.lppszA[lCount],
						 	 lpPropSrc->Value.MVszA.lppszA[lCount]);
				else
					break;
			}
		}
		break;

	case PT_MV_UNICODE:
		if(SUCCEEDED(hr=MAPIAllocateMore(lpPropSrc->Value.MVszW.cValues*sizeof(LPWSTR),
										 lpObject,
										 (void**)&lpPropDst->Value.MVszW.lppszW)))
		for(lCount=0;lCount<lpPropSrc->Value.MVszA.cValues;lCount++)
		{
			cbT =(lstrlenW(lpPropSrc->Value.MVszW.lppszW[lCount])+1)*sizeof(WCHAR);
			if(SUCCEEDED(hr=MAPIAllocateMore(cbT,
											 lpObject,
											 (void**)&lpPropDst->Value.MVszW.lppszW[lCount])))
				memcpy(lpPropDst->Value.MVszW.lppszW[lCount],
					   lpPropSrc->Value.MVszW.lppszW[lCount],
					   cbT);
			else
				break;
			
		}
		break;
	}
	return S_OK;
}

HRESULT ConvertPropValueToVariant(LPVARIANT lpVariant,LPSPropValue lpPropVal)
{
	long			noElems=0;
	BSTR			bstrVal;
	SAFEARRAYBOUND	rgsabound[1];
	
	switch(PROP_TYPE(lpPropVal->ulPropTag))
	{
	default:			return E_INVALIDARG;
	case PT_ERROR:
	case PT_NULL:		return S_OK;
	case PT_I2:			lpVariant->vt	= VT_I2;
						lpVariant->iVal=lpPropVal->Value.i;
						break;
	case PT_LONG:		lpVariant->vt	= VT_I4;
						lpVariant->lVal=lpPropVal->Value.l;
						break;
	case PT_R4:			lpVariant->vt		= VT_R4;
						lpVariant->fltVal	= lpPropVal->Value.flt;
						break;
	case PT_APPTIME:	lpVariant->vt		= VT_DATE;
						lpVariant->dblVal	= lpPropVal->Value.at;
						break;
	case PT_DOUBLE:		lpVariant->vt		= VT_R8;
						lpVariant->dblVal	= lpPropVal->Value.dbl;
						break;
	case PT_SYSTIME:	{
							lpVariant->vt	= VT_DATE;
							FILETIME		localFiletime;
							SYSTEMTIME		sysTime;
							// 1. convert file time to local time
							// 2. getSystemtime from file time
							// 3. Convert system time to date using function dateFromSysTime
							if(FileTimeToLocalFileTime(&lpPropVal->Value.ft,&localFiletime))
								if(FileTimeToSystemTime(&localFiletime,&sysTime))
									dateFromSysTime(sysTime,lpVariant->date);
						}
						break;
	case PT_I8:			lpVariant->vt		= VT_R8;
						memcpy(&lpVariant->dblVal,&lpPropVal->Value.li,sizeof(double));
						break;
	case PT_BOOLEAN:	lpVariant->vt		= VT_BOOL;
						lpVariant->boolVal	= lpPropVal->Value.b? VARIANT_TRUE:VARIANT_FALSE;
						break;
	case PT_CURRENCY:	lpVariant->vt		= VT_CY;
						lpVariant->cyVal	= lpPropVal->Value.cur;
						break;
	case PT_CLSID:		lpVariant->vt		= VT_BSTR;
						lpVariant->bstrVal	= GUIDToBSTR(lpPropVal->Value.lpguid);
						break;
	case PT_BINARY:		lpVariant->vt		= VT_BSTR;
						lpVariant->bstrVal	= BinaryToBSTR(&lpPropVal->Value.bin);
						break;
	case PT_STRING8:	lpVariant->vt		= VT_BSTR;
						lpVariant->bstrVal	= SysAllocString((BSTR)_bstr_t(lpPropVal->Value.lpszA));
						break;
	case PT_UNICODE:	lpVariant->vt		= VT_BSTR;
						lpVariant->bstrVal	= SysAllocString(lpPropVal->Value.lpszW);
						break;
	case PT_MV_I2:		lpVariant->vt		= VT_ARRAY|VT_I2;
						rgsabound[0].cElements=lpPropVal->Value.MVi.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_I2,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVi.lpi,
								sizeof(short)*rgsabound[0].cElements);
						break;
	case PT_MV_LONG:	lpVariant->vt		= VT_ARRAY|VT_I4;
						rgsabound[0].cElements=lpPropVal->Value.MVl.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_I4,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVl.lpl,
								sizeof(long)*rgsabound[0].cElements);
						break;
	case PT_MV_R4:		lpVariant->vt		= VT_ARRAY|VT_R4;
						rgsabound[0].cElements=lpPropVal->Value.MVflt.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_R4,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVflt.lpflt,
								sizeof(float)*rgsabound[0].cElements);
						break;
	case PT_MV_APPTIME:	lpVariant->vt		= VT_ARRAY|VT_DATE;
						rgsabound[0].cElements=lpPropVal->Value.MVat.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_R8,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVat.lpat,
								sizeof(double)*rgsabound[0].cElements);
						break;
	case PT_MV_DOUBLE:	lpVariant->vt		= VT_ARRAY|VT_R8;
						rgsabound[0].cElements=lpPropVal->Value.MVdbl.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_R8,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVdbl.lpdbl,
								sizeof(double)*rgsabound[0].cElements);
						break;
	case PT_MV_CURRENCY:lpVariant->vt		= VT_ARRAY|VT_CY;
						rgsabound[0].cElements=lpPropVal->Value.MVcur.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_R8,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVcur.lpcur,
								sizeof(double)*rgsabound[0].cElements);
						break;
	case PT_MV_SYSTIME:	{
							lpVariant->vt		= VT_ARRAY|VT_VARIANT;
							rgsabound[0].cElements=lpPropVal->Value.MVft.cValues;
							lpVariant->parray	= SafeArrayCreate(VT_DATE,1,rgsabound);
							FILETIME		localFiletime;
							SYSTEMTIME		sysTime;

							for(noElems=0;noElems<lpPropVal->Value.MVft.cValues;noElems++)
							{
								VARIANT		lVar;

								lVar.vt	= VT_DATE;
								// 1. convert file time to local time
								// 2. getSystemtime from file time
								// 3. Convert system time to date using function dateFromSysTime
								if(FileTimeToLocalFileTime(&lpPropVal->Value.MVft.lpft[noElems],&localFiletime))
									if(FileTimeToSystemTime(&localFiletime,&sysTime))
										if(dateFromSysTime(sysTime,lVar.date))
											SafeArrayPutElement(lpVariant->parray,&noElems,&lVar);
							}
						}
						break;
	case PT_MV_CLSID:	lpVariant->vt		= VT_ARRAY|VT_BSTR;
						rgsabound[0].cElements=lpPropVal->Value.MVguid.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_BSTR,1,rgsabound);
						for(noElems=0;noElems< rgsabound[0].cElements;noElems++)
						{
							bstrVal	= GUIDToBSTR(lpPropVal->Value.lpguid);
							SafeArrayPutElement(lpVariant->parray,&noElems,&bstrVal);
						}
						break;
	case PT_MV_I8:		lpVariant->vt		= VT_ARRAY|VT_R8;
						rgsabound[0].cElements=lpPropVal->Value.MVli.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_R8,1,rgsabound);
						memcpy(lpVariant->parray->pvData,lpPropVal->Value.MVli.lpli,
								sizeof(double)*rgsabound[0].cElements);
						break;
	case PT_MV_BINARY:	lpVariant->vt		= VT_ARRAY|VT_BSTR;
						rgsabound[0].cElements=lpPropVal->Value.MVbin.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_BSTR,1,rgsabound);
						for(noElems=0;noElems< rgsabound[0].cElements;noElems++)
						{
							bstrVal=BinaryToBSTR(&lpPropVal->Value.MVbin.lpbin[noElems]);
							SafeArrayPutElement(lpVariant->parray,&noElems,&bstrVal);
						}
						break;
	case PT_MV_STRING8:	lpVariant->vt		= VT_ARRAY|VT_BSTR;
						rgsabound[0].cElements=lpPropVal->Value.MVszA.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_BSTR,1,rgsabound);
						for(noElems=0;noElems< rgsabound[0].cElements;noElems++)
						{
							bstrVal=SysAllocString((OLECHAR FAR*)lpPropVal->Value.MVszA.lppszA[noElems]);
							SafeArrayPutElement(lpVariant->parray,&noElems,&bstrVal);
						}
						break;
	case PT_MV_UNICODE:	lpVariant->vt		= VT_ARRAY|VT_BSTR;
						rgsabound[0].cElements=lpPropVal->Value.MVszW.cValues;
						lpVariant->parray	= SafeArrayCreate(VT_BSTR,1,rgsabound);
						for(noElems=0;noElems< rgsabound[0].cElements;noElems++)
						{
							bstrVal=SysAllocString(lpPropVal->Value.MVszW.lppszW[noElems]);
							SafeArrayPutElement(lpVariant->parray,&noElems,&bstrVal);
						}
						break;
	}
	return S_OK;
}

BSTR GUIDToBSTR(GUID *lpGUID)
{
	WORD		wTemp;
	BSTR		tmpBstr=NULL;
	wchar_t		guid[37];
	wchar_t		*lpWStr=(LPWSTR)guid;

	if(lpGUID)
	{
		 wTemp = ((WORD)lpGUID->Data4[0]<<4)|(WORD)lpGUID->Data4[1];

		 memset(guid,0,sizeof(wchar_t)*37);
		intToStr(lpWStr,lpGUID->Data1);
		lpWStr+=sizeof(lpGUID->Data1)*2;

		*lpWStr++ = '-';

		intToStr(lpWStr,lpGUID->Data2);
		lpWStr+=sizeof(lpGUID->Data2)*2;

		*lpWStr++ = '-';
		intToStr(lpWStr,lpGUID->Data3);
		lpWStr+=sizeof(lpGUID->Data3)*2;

		*lpWStr++ = '-';
		intToStr(lpWStr,wTemp);
		lpWStr+= sizeof(wTemp)*2;
		*lpWStr++ = '-';
		intToStr(lpWStr,lpGUID->Data4[2]);
		lpWStr+=2;
		intToStr(lpWStr,lpGUID->Data4[3]);
		lpWStr+=2;
		intToStr(lpWStr,lpGUID->Data4[4]);
		lpWStr+=2;
		intToStr(lpWStr,lpGUID->Data4[5]);
		lpWStr+=2;
		intToStr(lpWStr,lpGUID->Data4[6]);
		lpWStr+=2;
		intToStr(lpWStr,lpGUID->Data4[7]);
		lpWStr+=2;
		tmpBstr = ::SysAllocString((LPOLESTR)guid);
	}
	return tmpBstr;
}

GUID BSTRToGUID(BSTR bstrVal)
{
	int		len=0;
	BYTE	lbyte=0;
	BYTE	hbyte=0;
	WORD	lWord=0;
	WORD	hWord=0;
	GUID	lGUID;
	_bstr_t	bstrt(bstrVal);
	LPSTR	lpStr=(LPSTR)bstrt;
			
	if(36==(len=lstrlenA(lpStr)))
	{
		lpStr[8]	= 0;
		lpStr[13]	= 0;
		lpStr[18]	= 0;
		lpStr[23]	= 0;

		hbyte	= GetByteInt(lpStr[0])<<4;
		hbyte	|= GetByteInt(lpStr[1]);
		lbyte	= GetByteInt(lpStr[2])<<4;
		lbyte	|= GetByteInt(lpStr[3]);
		hWord	= ((WORD)hbyte<<8)|(WORD)lbyte;
		hbyte	= GetByteInt(lpStr[4])<<4;
		hbyte	|= GetByteInt(lpStr[5]);
		lbyte	= GetByteInt(lpStr[6])<<4;
		lbyte	|= GetByteInt(lpStr[7]);
		lWord	= ((WORD)hbyte<<8)|(WORD)lbyte;
		lGUID.Data1 =((long)hWord<<16)|(long)lWord;
		
		hbyte	= GetByteInt(lpStr[9])<<4;
		hbyte	|= GetByteInt(lpStr[10]);
		lbyte	= GetByteInt(lpStr[11])<<4;
		lbyte	|= GetByteInt(lpStr[12]);
		lGUID.Data2 =((WORD)hbyte<<8)|(WORD)lbyte;;
		
		lGUID.Data1 =((long)hWord<<16)|(long)lWord;
		hbyte	= GetByteInt(lpStr[14])<<4;
		hbyte	|= GetByteInt(lpStr[15]);
		lbyte	= GetByteInt(lpStr[16])<<4;
		lbyte	|= GetByteInt(lpStr[17]);
		lGUID.Data3 =((WORD)hbyte<<8)|(WORD)lbyte;;
	
		lGUID.Data4[0] = GetByteInt(lpStr[19])<<4;
		lGUID.Data4[0]|= GetByteInt(lpStr[20]);
		lGUID.Data4[1] = GetByteInt(lpStr[21])<<4;
		lGUID.Data4[1]|= GetByteInt(lpStr[22]);
		lGUID.Data4[2] = GetByteInt(lpStr[24])<<4;
		lGUID.Data4[2]|= GetByteInt(lpStr[25]);
		lGUID.Data4[3] = GetByteInt(lpStr[26])<<4;
		lGUID.Data4[3]|= GetByteInt(lpStr[27]);
		lGUID.Data4[4] = GetByteInt(lpStr[28])<<4;
		lGUID.Data4[4]|= GetByteInt(lpStr[29]);
		lGUID.Data4[5] = GetByteInt(lpStr[30])<<4;
		lGUID.Data4[5]|= GetByteInt(lpStr[31]);
		lGUID.Data4[6] = GetByteInt(lpStr[32])<<4;
		lGUID.Data4[6]|= GetByteInt(lpStr[33]);
		lGUID.Data4[7] = GetByteInt(lpStr[34])<<4;
		lGUID.Data4[7]|= GetByteInt(lpStr[34]);
		lGUID.Data4[8] = GetByteInt(lpStr[35])<<4;
		lGUID.Data4[8]|= GetByteInt(lpStr[35]);
	}
	return lGUID;
}

int GetByteInt(char cChar)
{
	int		ny=0;

	if(cChar>=L'0' && cChar<=L'9')
		ny = cChar-L'0';
	else if(cChar>=L'A' && cChar<=L'F')
		ny = cChar-L'A'+10;
	else if(cChar>=L'a' && cChar<=L'f')
		ny = cChar-L'a'+10;
	else
		ny = 0;
	return ny;
}

void intToStr(LPWSTR lpWStr,BYTE data)
{
	BYTE	lowByte=data&0x0f;
	BYTE	highByte=(data>>4)&0x0f;

	lpWStr[1]  =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[0]  =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));
}

void intToStr(LPWSTR lpWStr,WORD data)
{
	BYTE	lowByte	= data&0x000f;
	BYTE	highByte= (data>>4)&0x000f;

	lpWStr[3]  =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[2]  =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));

	lowByte	= (data>>8)&0x0000000f;
	highByte= (data>>12)&0x0000000f;
	lpWStr[1]  =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[0]  =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));

}

void intToStr(LPWSTR lpWStr,DWORD data)
{
	BYTE	lowByte	= data&0x0000000f;
	BYTE	highByte= (data>>4)&0x0000000f;

	lpWStr[7] =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[6] =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));

	lowByte	= (data>>8)&0x0000000f;
	highByte= (data>>12)&0x0000000f;
	lpWStr[5]  =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[4]  =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));

	lowByte	=(data>>16)&0x0000000f;
	highByte=(data>>20)&0x0000000f;
	lpWStr[3]  =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[2]  =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));

	lowByte	=(data>>24)&0x0000000f;
	highByte=(data>>28)&0x0000000f;
	lpWStr[1]  =(BYTE)(lowByte+(lowByte>=10? (L'A'- 10):L'0'));
	lpWStr[0]  =(BYTE)(highByte+(highByte>=10? (L'A'-10):L'0'));
}

BOOL tmFromVariantDate(DATE dtSrc, struct tm& tmDest)
{
	// The legal range does not actually span year 0 to 9999.
	if(dtSrc>MAX_DATE||dtSrc<MIN_DATE)	// about year 100 to about 9999
		return FALSE;

	long nDays=0;           // Number of days since Dec. 30, 1899
	long nDaysAbsolute=0;	// Number of days since 1/1/0
	long nSecsInDay=0;		// Time in seconds since midnight
	long nMinutesInDay=0;	// Minutes in day

	long n400Years=0;		// Number of 400 year increments since 1/1/0
	long n400Century=0;		// Century within 400 year block (0,1,2 or 3)
	long n4Years=0;			// Number of 4 year increments since 1/1/0
	long n4Day=0;           // Day within 4 year block
							//	(0 is 1/1/yr1, 1460 is 12/31/yr4)
	long n4Yr=0;              // Year within 4 year block (0,1,2 or 3)
	BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

	double dblDate = dtSrc; // tempory serial date

	// If a valid date, then this conversion should not overflow
	nDays = (long)dblDate;

	// Round to the second
	dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

	nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899
	dblDate = fabs(dblDate);
	nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

	// Calculate the day of week (sun=1, mon=2...)
	//	-1 because 1/1/0 is Sat.  +1 because we want 1-based
	tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

	// Leap years every 4 yrs except centuries not multiples of 400.
	n400Years = (long)(nDaysAbsolute / 146097L);

	// Set nDaysAbsolute to day within 400-year block
	nDaysAbsolute %= 146097L;

	// -1 because first century has extra day
	n400Century = (long)((nDaysAbsolute - 1) / 36524L);

	// Non-leap century
	if(n400Century!=0)
	{
		// Set nDaysAbsolute to day within century
		nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

		// +1 because 1st 4 year increment has 1460 days
		n4Years = (long)((nDaysAbsolute + 1) / 1461L);

		if (n4Years != 0)
			n4Day = (long)((nDaysAbsolute + 1) % 1461L);
		else
		{
			bLeap4 = FALSE;
			n4Day = (long)nDaysAbsolute;
		}
	}
	else
	{
		// Leap century - not special case!
		n4Years = (long)(nDaysAbsolute / 1461L);
		n4Day = (long)(nDaysAbsolute % 1461L);
	}

	if (bLeap4)
	{
		// -1 because first year has 366 days
		n4Yr = (n4Day - 1) / 365;

		if (n4Yr != 0)
			n4Day = (n4Day - 1) % 365;
	}
	else
	{
		n4Yr = n4Day / 365;
		n4Day %= 365;
	}

	// n4Day is now 0-based day of year. Save 1-based day of year, year number
	tmDest.tm_yday = (int)n4Day + 1;
	tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

	// Handle leap year: before, on, and after Feb. 29.
	if (n4Yr == 0 && bLeap4)
	{
		// Leap Year
		if (n4Day == 59)
		{
			/* Feb. 29 */
			tmDest.tm_mon = 2;
			tmDest.tm_mday = 29;
			if (nSecsInDay == 0)
				tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
			else
			{
				tmDest.tm_sec = (int)nSecsInDay % 60L;
				nMinutesInDay = nSecsInDay / 60L;
				tmDest.tm_min = (int)nMinutesInDay % 60;
				tmDest.tm_hour = (int)nMinutesInDay / 60;
			}
			return TRUE;
		}
		// Pretend it's not a leap year for month/day comp.
		if (n4Day >= 60)
			--n4Day;
	}
	// Make n4DaY a 1-based day of non-leap year and compute
	//  month/day for everything but Feb. 29.
	++n4Day;

	// Month number always >= n/32, so save some loop time */
	for (tmDest.tm_mon = (n4Day >> 5) + 1;
		n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

	tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

	if (nSecsInDay == 0)
		tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
	else
	{
		tmDest.tm_sec = (int)nSecsInDay % 60L;
		nMinutesInDay = nSecsInDay / 60L;
		tmDest.tm_min = (int)nMinutesInDay % 60;
		tmDest.tm_hour = (int)nMinutesInDay / 60;
	}
	return TRUE;
}

BOOL dateFromSysTime(const SYSTEMTIME &sysTime, DATE &dtDest)
{
	WORD	wYear	= sysTime.wYear;
	WORD	wMonth	= sysTime.wMonth;
	WORD	wDay	= sysTime.wDay;
	WORD	wHour	= sysTime.wHour;
	WORD	wMinute	= sysTime.wMinute;
	WORD	wSecond	= sysTime.wSecond;

	// Validate year and month (ignore day of week and milliseconds)
	if(wYear>9999||wMonth<1||wMonth>12)
		return FALSE;

	//  Check for leap year and set the number of days in the month
	BOOL	bLeapYear	= ((wYear&3)==0)&&((wYear%100)!=0||(wYear%400)==0);
	int		nDaysInMonth= rgMonthDays[wMonth]-rgMonthDays[wMonth-1]+
							((bLeapYear&&wDay==29&&wMonth==2)? 1:0);
	// Finish validating the date
	if(wDay<1||wDay>nDaysInMonth||wHour>23||wMinute>59||wSecond>59)
		return FALSE;

	// Cache the date in days and time in fractional days
	long	nDate;
	double	dblTime;

	//It is a valid date; make Jan 1, 1AD be 1
	nDate = wYear*365L+wYear/4-wYear/100+wYear/400+rgMonthDays[wMonth-1]+wDay;

	//  If leap year and it's before March, subtract 1:
	if(wMonth<=2&&bLeapYear)
		--nDate;

	//  Offset so that 12/30/1899 is 0
	nDate -= 693959L;

	dblTime = (((long)wHour*3600L)+		// hrs in seconds
			  ((long)wMinute*60L)+		// mins in seconds
			  ((long)wSecond))/86400;

	dtDest = (double)nDate+((nDate>=0)? dblTime:-dblTime);
	return TRUE;
}
