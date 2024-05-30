#include "notifiers.h"


/***************************************
 * CUpHandler
 ***************************************/

STDMETHODIMP_(ULONG) CUpHandler::AddRef()  { 
	return InterlockedIncrement(&_cRefs); 
}
	
STDMETHODIMP_(ULONG) CUpHandler::Release()  {
	ULONG refCount = InterlockedDecrement(&_cRefs);
	if (!refCount) {
		delete this;
		return refCount;
	}
	return _cRefs;
}

STDMETHODIMP CUpHandler::Cleanup()  {
  _ev->Release();
  _downHandler->Release();
  _e->Release();
  
  return S_OK;
}

STDMETHODIMP CUpHandler::QueryInterface(REFIID riid, void **ppv)  {
	if (!ppv)
		return E_POINTER;
	
	*ppv = NULL;
	if (riid == IID_IUnknown)  {
		*ppv = (void *)(IUnknown *)this;
	} else if (riid == IID_IDABvrHook)  {
		*ppv = (void *)(IDAUntilNotifier *)this;
	}
	
	if (*ppv)  {
		((IUnknown *)*ppv)->AddRef();
		return S_OK;
	}
	
	return E_NOINTERFACE;
}

STDMETHODIMP CUpHandler::initNotify(IDAEventPtr ev, CDownHandler* downHandler, IDAStaticsPtr e)  {
   _e  = e;
   _ev = ev;
   _downHandler = downHandler;
   _downHandler->AddRef();
  return S_OK;
}

STDMETHODIMP CUpHandler::raw_Notify(IDABehavior* eventData,
					IDABehavior* curRunningBvr,
					IDAView* curView,
					IDABehavior** ppBvr)  {
  
  IDAPoint2Ptr downHandlerPt = _e->Point2(_downHandler->_control->_p[0], _downHandler->_control->_p[1]);
  IDATransform2Ptr downHandlerTrans = _e->Translate2Point(downHandlerPt);
  IDAEventPtr downHandlerEv = _e->AndEvent(_ev, _e->LeftButtonDown);

  IDATransform2Ptr finalTrans = (IDATransform2Ptr)_e->UntilNotify(downHandlerTrans, downHandlerEv, _downHandler);

  *ppBvr = (IDABehavior*)finalTrans;

  finalTrans->AddRef();

  return S_OK;
}

/***************************************
 * CDownHandler
 ***************************************/

STDMETHODIMP_(ULONG) CDownHandler::AddRef()  { 
	return InterlockedIncrement(&_cRefs); 
}
	
STDMETHODIMP_(ULONG) CDownHandler::Release()  {
	ULONG refCount = InterlockedDecrement(&_cRefs);
	if (!refCount) {
		delete this;
		return refCount;
	}
	return _cRefs;
}

STDMETHODIMP CDownHandler::Cleanup()  {
	_ev->Release();
	_e->Release();
  _upHandPtr->Release();
  _control->Release();
  
  return S_OK;
}

STDMETHODIMP CDownHandler::QueryInterface(REFIID riid, void **ppv)  {
	if (!ppv)
		return E_POINTER;
	
	*ppv = NULL;
	if (riid == IID_IUnknown)  {
		*ppv = (void *)(IUnknown *)this;
	} else if (riid == IID_IDABvrHook)  {
		*ppv = (void *)(IDAUntilNotifier *)this;
	}
	
	if (*ppv)  {
		((IUnknown *)*ppv)->AddRef();
		return S_OK;
	}
	
	return E_NOINTERFACE;
}

STDMETHODIMP CDownHandler::initNotify(IDAEventPtr ev, CUpHandler* upHandPtr, CControlPoint2* control, IDAStaticsPtr e)  {
   _e  = e;
   _ev = ev;
   _control = control;
   _control->AddRef();
   _upHandPtr = upHandPtr;
  _upHandPtr->AddRef();
  return S_OK;
}

STDMETHODIMP CDownHandler::raw_Notify(IDABehavior* eventData,
					IDABehavior* curRunningBvr,
					IDAView* curView,
					IDABehavior** ppBvr)  {

  IDAPairPtr pair = (IDAPairPtr)eventData;
  IDAPairPtr pair1 = (IDAPairPtr)(pair->First);

  _upHandPtr->initNotify(_ev, this, _e);

  IDAPoint2Ptr hitPoint = (IDAPoint2Ptr)(pair1->First);

  IDAPoint2Ptr localHitPoint = hitPoint->Transform(((IDATransform2Ptr)curRunningBvr)->Inverse());
  IDAVector2Ptr clickOffset = _e->Vector2Anim(localHitPoint->X, localHitPoint->Y);

  IDAPoint2Ptr sample = _e->AddPoint2Vector((IDAPoint2Ptr)_e->SubPoint2Vector(_e->GetMousePosition(), clickOffset)->Hook(_control), clickOffset);

  IDATransform2Ptr xfrm = _e->Compose2((IDATransform2Ptr)curRunningBvr, _e->Translate2Vector(_e->SubPoint2(sample, hitPoint)));

  IDATransform2Ptr finalTrans = _e->UntilNotify(xfrm, _e->LeftButtonUp->Snapshot(xfrm), _upHandPtr);

  *ppBvr = (IDABehavior*)finalTrans;

	finalTrans->AddRef();

	return S_OK;
}

/***************************************
 * CPickHandler
 ***************************************/

STDMETHODIMP_(ULONG) CPickHandler::AddRef()  { 
	return InterlockedIncrement(&_cRefs); 
}
	
STDMETHODIMP_(ULONG) CPickHandler::Release()  {
	ULONG refCount = InterlockedDecrement(&_cRefs);
	if (!refCount) {
		delete this;
		return refCount;
	}
	return _cRefs;
}

STDMETHODIMP CPickHandler::Cleanup()  {
	_img->Release();
	_e->Release();
  
  return S_OK;
}

STDMETHODIMP CPickHandler::QueryInterface(REFIID riid, void **ppv)  {
	if (!ppv)
		return E_POINTER;
	
	*ppv = NULL;
	if (riid == IID_IUnknown)  {
		*ppv = (void *)(IUnknown *)this;
	} else if (riid == IID_IDABvrHook)  {
		*ppv = (void *)(IDAUntilNotifier *)this;
	}
	
	if (*ppv)  {
		((IUnknown *)*ppv)->AddRef();
		return S_OK;
	}
	
	return E_NOINTERFACE;
}

STDMETHODIMP CPickHandler::initNotify(IDAImagePtr img, IDAStaticsPtr e)  {
   _e  = e;
   _img = img;
  return S_OK;
}

STDMETHODIMP CPickHandler::raw_Notify(IDABehavior* eventData,
					IDABehavior* curRunningBvr,
					IDAView* curView,
					IDABehavior** ppBvr)  {

  *ppBvr = (IDABehavior*)_img;

	_img->AddRef();

	return S_OK;
}

/***************************************
 * CControlPoint2
 ***************************************/

STDMETHODIMP_(ULONG) CControlPoint2::AddRef()  { 
	return InterlockedIncrement(&_cRefs); 
}
	
STDMETHODIMP_(ULONG) CControlPoint2::Release()  {
	ULONG refCount = InterlockedDecrement(&_cRefs);
	if (!refCount) {
		delete this;
		return refCount;
	}
	return _cRefs;
}

STDMETHODIMP CControlPoint2::Cleanup()  {
  _pnt->Release();
	_initialPnt->Release();
	_img->Release();
	_e->Release();
  _pPickHandle->Release();
  _pDownHandle->Release();
  _upHandPtr->Cleanup();
  return S_OK;
}

STDMETHODIMP CControlPoint2::QueryInterface(REFIID riid, void **ppv)  {
	if (!ppv)
		return E_POINTER;
	
	*ppv = NULL;
	if (riid == IID_IUnknown)  {
		*ppv = (void *)(IUnknown *)this;
	} else if (riid == IID_IDABvrHook)  {
		*ppv = (void *)(IDABvrHook *)this;
	}
	
	if (*ppv)  {
		((IUnknown *)*ppv)->AddRef();
		return S_OK;
	}
	
	return E_NOINTERFACE;
}

STDMETHODIMP CControlPoint2::initNotify(IDAImagePtr img1, IDAImagePtr img2, 
                                        CPickHandler* pPickHandle, CDownHandler* pDownHandle,
                                        double x0, double y0, IDAStaticsPtr e)  {
   _e  = e;
   _p[0] = x0;
   _p[1] = y0;

  // Set up transform here so it can go under PickableImage
  IDATransform2Ptr xfrm;
  xfrm.CreateInstance( L"DirectAnimation.DATransform2");
  _img = img1->Transform(xfrm);
 
  // Create pickable
  IDAPickableResultPtr pImg = _img->Pickable();
	IDAEventPtr ev = pImg->GetPickEvent();

  _pPickHandle = pPickHandle;
  _pPickHandle->AddRef();
  _pPickHandle->initNotify(img2, _e);
  
  _upHandPtr = new CUpHandler();
  _pDownHandle = pDownHandle;
  _pDownHandle->AddRef();
  _pDownHandle->initNotify(ev, _upHandPtr, this, _e);

  IDAImagePtr aux;
  aux.CreateInstance( L"DirectAnimation.DAImage");
  aux->Init(_e->Until((IDAImagePtr)_e->UntilNotify(_e->EmptyImage, ev, _pPickHandle),_e->NotEvent(ev), aux));

  _img = _e->Overlay(pImg->GetImage(), aux->Transform(xfrm));

	_initialPnt.CreateInstance( L"DirectAnimation.DAPoint2");

  xfrm->Init((IDATransform2Ptr)_e->UntilNotify(_e->Translate2Point(_initialPnt), 
	_e->AndEvent(ev, _e->LeftButtonDown), _pDownHandle));

  _pnt = _e->Point2(0, 0)->Transform(xfrm);
  return S_OK;
}

STDMETHODIMP CControlPoint2::raw_Notify(
    long id,
    VARIANT_BOOL startingPerformance,
    double startTime,
    double gTime,
    double lTime,
    struct IDABehavior * sampleVal,
    struct IDABehavior * curRunningBvr,
    struct IDABehavior * * ppBvr )  {

  _p[0] = ((double)((IDAPoint2Ptr)sampleVal)->X->Extract());
	_p[1] = ((double)((IDAPoint2Ptr)sampleVal)->Y->Extract());

  obeyConstraints(_p);

  IDAPoint2Ptr finalPoint = _e->Point2(_p[0], _p[1]);
  *ppBvr = (IDABehavior*)finalPoint;
	finalPoint->AddRef();

	return S_OK;
}

void CControlPoint2::obeyConstraints()  {
  obeyConstraints(_p);
  _initialPnt->Init((IDAPoint2Ptr)_e->Point2(_p[0], _p[1]));
}		

void CControlPoint2::obeyConstraints(double p[2])  {
  double dx, dy;
  double x = p[0];
  double y = p[1];
  
  do  {
    vector<Cons>::iterator consIterator;
    consIterator = constraints.begin();
    while ( consIterator!= constraints.end())  {
      Cons cons = *consIterator++;
      cons.satisfy(p);
    }
    
    dx = p[0] - x;
    dy = p[1] - y;
    
    x = p[0];
		y = p[1];
  
  } while(dx*dx + dy*dy > 0);
}

void CControlPoint2::add(Cons constraint)  {
  constraints.push_back(constraint);
}

//Overide the == and < operators to keep the vector template happy
BOOL operator==(const Cons& x, const Cons& y)  {
    return x == y;
}
BOOL operator<(const Cons& x, const Cons& y)  {
    return x < y;
}


