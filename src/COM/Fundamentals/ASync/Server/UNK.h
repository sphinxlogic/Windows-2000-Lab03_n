/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */

#define DECLARE_UNKNOWN													\
	virtual HRESULT __stdcall											\
		QueryInterface(REFIID iid, PVOID *ppv);							\
    virtual ULONG __stdcall AddRef()									\
	{																	\
		return InterlockedIncrement(reinterpret_cast<PLONG>(&m_cRef));	\
	} ;																	\
	virtual ULONG __stdcall Release()									\
	{																	\
		_ASSERT(m_cRef > 0); /* not thread safe	*/						\
		if (InterlockedDecrement(reinterpret_cast<PLONG>(&m_cRef)) == 0)\
		{																\
			FinalRelease();												\
			delete this;												\
			return 0;													\
		}																\
		return m_cRef;													\
																		\
	} ;																	\
	virtual void __stdcall FinalRelease();

