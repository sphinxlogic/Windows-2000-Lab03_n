// --edkmidl.c------------------------------------------------------------------
//
// MIDL memory allocation functions.
//
// Copyright (C) Microsoft Corp. 1986-1996, All rights reserved.
//
// ----------------------------------------------------------------------------

#include "edk.h"

void __RPC_FAR * __RPC_API midl_user_allocate(size_t cb)
{
	void *	pv;

	pv = GlobalAlloc(GMEM_FIXED, cb);
	if (!pv)
		RpcRaiseException(RPC_S_OUT_OF_MEMORY);

	return pv;
}

void __RPC_API midl_user_free(void __RPC_FAR * pv)
{
	GlobalFree(pv);
}