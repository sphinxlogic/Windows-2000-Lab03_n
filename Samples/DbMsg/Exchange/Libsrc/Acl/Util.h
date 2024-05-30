/* --------------------------------------------------------------------------

The header file for util.cpp
define a number of utility functions used in this object

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// 
// util.h
//

#pragma once

SBinary BSTRToBinary(BSTR str);
HRESULT VariantToMAPIObject(VARIANT var, REFIID iid, void** ppObject);
HRESULT AMObjectToMAPIObject(LPDISPATCH pAMObject, REFIID iid, void** ppObject);
HRESULT CopyBinary(SBinary& Source, SBinary* pDest);
HRESULT	ConvertToLongTerm( LPMAPISESSION pMAPISession, const SBinary &lShortEntryID, SBinary **ppLongEntryID );
BOOL IsShortTerm( SBinary& sbin );

#define ECheckPointer(p, type)							\
	{													\
		if(!(p) || IsBadWritePtr((p), sizeof(type)))	\
		{												\
			return(E_POINTER);							\
		}												\
	}

#define ECheckPointerClear(p, type)						\
	{													\
		ECheckPointer(p, type)							\
		ZeroMemory((p), sizeof(type));					\
	}

