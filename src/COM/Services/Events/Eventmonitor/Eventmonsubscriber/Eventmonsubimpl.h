// EventMonSubImpl.h : Declaration of the CEventMonSubImpl

#ifndef __EventMonSUBIMPL_H_
#define __EventMonSUBIMPL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEventMonSubImpl
class ATL_NO_VTABLE CEventMonSubImpl : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEventMonSubImpl, &__uuidof(EventMonSubscriber)>,
	public IDispatchImpl<IDiskEvents, &__uuidof(IDiskEvents), &LIBID_EventMonSUBSCRIBERLib>,
	public IFileSystemEvents,
	public ISystemEvents
{
public:
	CEventMonSubImpl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EVENTMONSUBIMPL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEventMonSubImpl)
	COM_INTERFACE_ENTRY(IDiskEvents)  
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IFileSystemEvents)
	COM_INTERFACE_ENTRY(ISystemEvents)
END_COM_MAP()

public:
	// IDiskEvent methods
	STDMETHOD (DiskFull)(BSTR);

	// IFileSystem methods
	STDMETHOD (FileCreated)(BSTR); 
	STDMETHOD (FileDeleted)(BSTR);
	STDMETHOD (FileRenamed)(BSTR);
	STDMETHOD (FileUpdated)(BSTR);

	// ISystem methods
	STDMETHOD (ProcessCreated)(BSTR);
	STDMETHOD (ProcessTerminated)(BSTR);
	STDMETHOD (PNPDeviceAdded)(BSTR);
private:
	HRESULT CommonMethod(TCHAR* tzmethod, BSTR bstr);
};

#endif //__EventMonSUBIMPL_H_
