// EventMonFilterImpl.h : Declaration of the CEventMonFilter

#ifndef __EventMonFILTER_H_
#define __EventMonFILTER_H_

#include "resource.h"       // main symbols
#include "..\include\macro.h"

/////////////////////////////////////////////////////////////////////////////
// CEventMonFilter
class ATL_NO_VTABLE CEventMonFilter : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEventMonFilter, &__uuidof(EventMonFilter)>,
	public IDispatchImpl<IDiskEvents, &__uuidof(IDiskEvents), &LIBID_EventMonFILTERLib>,
	public IFileSystemEvents,
	public ISystemEvents,
	public IMultiInterfacePublisherFilter
{
public:
	CEventMonFilter();
	~CEventMonFilter();
	
DECLARE_REGISTRY_RESOURCEID(IDR_EVENTMONFILTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEventMonFilter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDiskEvents)
	COM_INTERFACE_ENTRY(IFileSystemEvents)
	COM_INTERFACE_ENTRY(ISystemEvents)
	COM_INTERFACE_ENTRY(IMultiInterfacePublisherFilter)
END_COM_MAP()

public:
	// IDiskEvents methods
	STDMETHOD (DiskFull)(BSTR);

	// IFIleSystemEvents methods
	STDMETHOD (FileCreated)(BSTR); 
	STDMETHOD (FileDeleted)(BSTR);
	STDMETHOD (FileRenamed)(BSTR);
	STDMETHOD (FileUpdated)(BSTR);

	// ISystemEvents methods
	STDMETHOD (ProcessCreated)(BSTR);
	STDMETHOD (ProcessTerminated)(BSTR);
	STDMETHOD (PNPDeviceAdded)(BSTR);

	// IMultiInterfacePublisherFilter methods
	STDMETHOD (Initialize) (IMultiInterfaceEventControl *pmiec);
	STDMETHOD (PrepareToFire) (REFIID riid, BSTR methodname, IFiringControl* firingcontrol);

private:
	// Helper methods
	HRESULT ReleaseCollection(BOOL fcoll, BOOL ffc);
	HRESULT InitializeStructure();
	HRESULT CommonFilter(BSTR bstr, int nInterface, int nMethod);
	HRESULT GetProperty(IEventSubscription *psub, VARIANT *pvar);


	// Data member
	struct filtattr
	{
		IEventObjectCollection *pcoll;
		IFiringControl			*pfc;
	};

	filtattr m_filtattr[NUM_INTERFACE][NUM_METHOD_IFILESYSTEM];
};

#endif //__EventMonFILTER_H_
