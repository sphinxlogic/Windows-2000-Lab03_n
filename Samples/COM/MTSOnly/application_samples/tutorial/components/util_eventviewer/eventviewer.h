// EventViewer.h : Declaration of the CEventViewer

#ifndef __EVENTVIEWER_H_
#define __EVENTVIEWER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEventViewer
class ATL_NO_VTABLE CEventViewer : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEventViewer, &CLSID_EventViewer>,
	public ISupportErrorInfo,
	public IDispatchImpl<IEventViewer, &IID_IEventViewer, &LIBID_UTIL_EVENTVIEWERLib>
{
public:
	CEventViewer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EVENTVIEWER)

BEGIN_COM_MAP(CEventViewer)
	COM_INTERFACE_ENTRY(IEventViewer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IEventViewer
public:
	STDMETHOD(AddLog)(/*[in]*/ BSTR bstrSource, /*[in]*/ BSTR bstrString, /*[in]*/ long lEventType,/*[in]*/ long lCategory, /*[in]*/ long lEventID);
};

#endif //__EVENTVIEWER_H_
