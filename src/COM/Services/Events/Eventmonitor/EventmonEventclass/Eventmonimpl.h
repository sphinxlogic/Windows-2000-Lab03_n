// EventMonImpl.h : Declaration of the CEventMonImpl

#ifndef __EventMonIMPL_H_
#define __EventMonIMPL_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CEventMonImpl
class ATL_NO_VTABLE CEventMonImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEventMonImpl, &__uuidof(EventMonEventClass)>
{
public:
	CEventMonImpl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EVENTMONIMPL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEventMonImpl)
END_COM_MAP()

public:


};

#endif //__EventMonIMPL_H_
