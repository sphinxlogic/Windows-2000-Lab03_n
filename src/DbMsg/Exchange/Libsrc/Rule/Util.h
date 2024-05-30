// ----------------------------------------------------------------------------
//	util.h
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#pragma once

#define DEFAULT_STRING_LENGTH			1024
#define BAD_FILENAME_CHARS				L"\"/\\[]:;|=,?<>*"

BSTR	BinaryToBSTR(SBinary* pBinary);
SBinary BSTRToBinary(BSTR str);
GUID	BSTRToGUID(BSTR bstrVal);
BSTR	GUIDToBSTR(GUID *lpGUID);
HRESULT VariantToMAPIObject(VARIANT var,REFIID iid,LPVOID* ppObject);
HRESULT AMObjectToMAPIObject(LPDISPATCH pAMObject,REFIID iid,LPVOID* ppObject);
HRESULT CopyBinary(SBinary& Source,SBinary* pDest);
HRESULT CheckProps(LPSPropTagArray pOld,LPSPropValue pNew);
HRESULT GetBaseAddressProps(SAFEARRAY *psaAdrList,void *lpObject,LPADRLIST lpAdrList);
HRESULT PropertyInvoke(LPDISPATCH pDispatch,WORD wFlags,_bstr_t propName,VARIANT *pVarResult,DISPPARAMS *pDispParams=NULL);
HRESULT MethodInvoke(LPDISPATCH pDispatch,_bstr_t propbSTR,VARIANT *pVarResult,DISPPARAMS *pDispParams,WORD wFlags=DISPATCH_METHOD);
HRESULT ConvertVariantToPropValue(VARIANT lVariant,LPSPropValue lpPropVal);
HRESULT ConvertPropValueToVariant(LPVARIANT lpVariant,LPSPropValue lpPropVal);
HRESULT	ReleasePropVal(LPSPropValue lpPropVal);
HRESULT CopyPropVal(LPSPropValue lpPropDst,LPSPropValue lPropSrc,LPVOID lpObj);

bool IsServerStore(SBinary GUID);
bool IsPublicStore(SBinary GUID);
void ReplaceBadCharsA(LPSTR pszName,LPSTR pszBad,CHAR chNew);
void ReplaceBadCharsW(LPWSTR pszName,LPWSTR pszBad,WCHAR chNew);

#ifdef UNICODE
#define ReplaceBadChars ReplaceBadCharsW
#else
#define ReplaceBadChars ReplaceBadCharsA
#endif

class CCriticalSectionUser
{
public:
	CCriticalSectionUser(LPCRITICAL_SECTION pSync)
	{
		if(m_pSync = pSync)
		{
			EnterCriticalSection(m_pSync);
		}
	}

	~CCriticalSectionUser()
	{
		if(m_pSync)
		{
			LeaveCriticalSection(m_pSync);
		}
	}

protected:
	LPCRITICAL_SECTION m_pSync;
};

#define RemoveFavoritesBit(pFolderID,EIDLength)		\
	{												\
		*(pFolderID + 0x15)&= ~0x80;				\
		*(pFolderID + EIDLength -2)= 0x00;			\
		*(pFolderID + EIDLength -1)= 0x00;			\
	}

#define SafeRelease(dest)				\
	{									\
		if(dest)						\
		{								\
			(dest)->Release();			\
		}								\
	}

#define ReleaseClear(dest)				\
	{									\
		(dest)->Release();				\
		(dest)= NULL;					\
	}

#define SafeReleaseClear(dest)			\
	{									\
		if(dest)						\
		{								\
			ReleaseClear(dest);			\
		}								\
	}

#define SafeAssignAddRef(dest,source)	\
	{									\
		if((dest)=(source))				\
		{								\
			(dest)->AddRef();			\
		}								\
	}

#define ECheckPointer(p,type)							\
	{													\
		if(!(p)|| IsBadWritePtr((p),sizeof(type)))		\
		{												\
			return(E_POINTER);							\
		}												\
	}

#define ECheckPointerClear(p,type)						\
	{													\
		ECheckPointer(p,type)							\
		ZeroMemory((p),sizeof(type));					\
	}

#define IsSBinarySameAsArray(b,a)						\
	(													\
		(b.cb + 1 == sizeof(a))&&						\
		(0 == memcmp(b.lpb,a,b.cb))						\
	)

#define ECheckVariantPointerClear(p)					\
	{													\
		ECheckPointer(p,VARIANT)						\
		VariantClear(p);								\
	}

#define ECheckBSTRPointerClear(p)						\
	{													\
		ECheckPointer(p,BSTR)							\
		if(*p)											\
		{												\
			SysFreeString(*p);							\
			(*p)= NULL;									\
		}												\
	}

#define ECheckAccess(ulAccess)							\
	{													\
		if(0 ==(MAPI_ACCESS_MODIFY & ulAccess))			\
		{												\
			return(E_ACCESSDENIED);						\
		}												\
	}

#define IfOnReturnHR(flag,hr)							\
	{													\
		if(flag)										\
		{												\
			return(hr);									\
		}												\
	}

