// Here's the magic... It reads in the type library and makes easy
// interfaces to use automatically.
#import "danim.tlb" \
  exclude( "_RemotableHandle", "IMoniker", "IPersist", "ISequentialStream", \
  "IParseDisplayName", "IOleClientSite", "_FILETIME", "tagSTATSTG" ) \
  rename( "GUID", "DAGUID" ) \
  rename_namespace( "DAnim" )

using namespace DAnim;

// Used by IDAUntilNotifier, to get its definition, be
// sure to add daguid.lib to the Object/library
// module editbox, on the link tab under Settings.
EXTERN_C const IID IID_IDABvrHook;

class CDADrag;
class CDARelease;

class CDADrag : public IDAUntilNotifier  {

public:

	CDADrag()  {
    _cRefs = 1;
  }

  IDAImagePtr getImagePtr()  { 
	  return _draggableImg; 
	};

	IDAEventPtr getGrabEvent()  { 
	  return _pickEv;
	}

	IDAEventPtr getReleaseEvent()  { 
	  return _releaseEv; 
	}

	IDAPoint2Ptr getPointPtr()  { 
	  return _draggablePt; 
	}

	STDMETHOD_(ULONG, AddRef)(); 
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD(initNotify)(IDAImagePtr im, CDARelease *releaseHdlr, IDAPoint2Ptr pt, IDAStaticsPtr e);
    STDMETHOD(Cleanup)();

  // Since we are using #import, the pure virtual function Notify of the 
  // IDAUntilNotifier class (refer to danim.h)  has been renamed to raw_Notify.
	STDMETHOD(raw_Notify)(IDABehavior* eventData,
					IDABehavior* curRunningBvr,
					IDAView* curView,
					IDABehavior** ppBvr);

	STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)  { 
    return E_NOTIMPL; 
  }

	STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfo){ 
    return E_NOTIMPL; 
  }

	STDMETHOD(GetIDsOfNames)(
		REFIID riid, LPOLESTR *rgszNames, UINT cNames,
		LCID lcid, DISPID *rgdispid)  { 
    return E_NOTIMPL; 
  }

	STDMETHOD(Invoke)(
		DISPID dispidMember, REFIID riid, LCID lcid,
		WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pvarResult,
		EXCEPINFO *pexcepinfo, UINT *puArgErr){ 
    return E_NOTIMPL; 
  }

	STDMETHOD(ClearEngine)(){ 
    return S_OK;
  }

protected:
	long _cRefs;
    IDAEventPtr _pickEv;
	IDAEventPtr _releaseEv;
	IDAImagePtr _draggableImg;
	IDAPoint2Ptr _draggablePt;
    CDARelease* _releaseHdlr;
	IDAStaticsPtr _e;
};


class CDARelease : public IDAUntilNotifier {

public:

  CDARelease()  {
    _cRefs = 1;
  }

  STDMETHOD_(ULONG, AddRef)(); 
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD(initNotify)(IDAEventPtr pickEv, CDADrag* grabHdlr, IDAStaticsPtr e);
    STDMETHOD(Cleanup)();

  // Since we are using #import, the pure virtual function Notify of the 
  // IDAUntilNotifier class (refer to danim.h)  has been renamed to raw_Notify.
  STDMETHOD(raw_Notify)(IDABehavior* eventData,
					IDABehavior* curRunningBvr,
					IDAView* curView,
					IDABehavior** ppBvr);


	STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)  { 
    return E_NOTIMPL; 
  }

	STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfo){ 
    return E_NOTIMPL; 
  }

	STDMETHOD(GetIDsOfNames)(
		REFIID riid, LPOLESTR *rgszNames, UINT cNames,
		LCID lcid, DISPID *rgdispid)  { 
    return E_NOTIMPL; 
  }

	STDMETHOD(Invoke)(
		DISPID dispidMember, REFIID riid, LCID lcid,
		WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pvarResult,
		EXCEPINFO *pexcepinfo, UINT *puArgErr){ 
    return E_NOTIMPL; 
  }

	STDMETHOD(ClearEngine)(){ 
    return S_OK;
  }


protected:
    long _cRefs;
    IDAEventPtr _pickEv;
	IDAStaticsPtr _e;
    CDADrag* _grabHdlr;
};
