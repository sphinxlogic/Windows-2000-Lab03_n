// Here's the magic... It reads in the type library and makes easy
// interfaces to use automatically.

#import "danim.tlb" \
  exclude( "_RemotableHandle", "IMoniker", "IPersist", "ISequentialStream", \
  "IParseDisplayName", "IOleClientSite", "_FILETIME", "tagSTATSTG" ) \
  rename( "GUID", "DAGUID" ) \
  rename_namespace( "DAnim" )

#include <vector>
#include <math.h>

using namespace std;
using namespace DAnim;

// Used by IDAUntilNotifier, to get its definition, be
// sure to add daguid.lib to the Object/library
// module editbox, on the link tab under Settings.
EXTERN_C const IID IID_IDABvrHook;

class CUpHandler;
class CDownHandler;
class CPickHandler;
class CControlPoint2;
class Cons;

/***************************************
 * Cons
 ***************************************/

class Cons  {
public:
  Cons()  {
    TOLERANCE = 0;
  }
public:
  double TOLERANCE;
  friend BOOL operator==(const Cons& x, const Cons& y);
  friend BOOL operator<(const Cons& x, const Cons& y);
  void satisfy(double* p) {
		double r = _a[0]*p[0] + _a[1]*p[1] + _a[2];

		if ((!_equality && (r < 0.0)) || (_equality && (abs(r) > TOLERANCE))) // not satisfied
		{
			p[0] -= r*_a[0];
			p[1] -= r*_a[1];
		}
  }
  double* _a;
  BOOL _equality;
};

/***************************************
 * CUpHandler
 ***************************************/

class CUpHandler : public IDAUntilNotifier  {

public:

	CUpHandler()  {
    _cRefs = 1;
  }

	~CUpHandler()  {
  }

	STDMETHOD_(ULONG, AddRef)(); 
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD(initNotify)(IDAEventPtr ev, CDownHandler* downHandler, IDAStaticsPtr e);
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
	IDAEventPtr _ev;
	CDownHandler* _downHandler;
	IDAStaticsPtr _e;
};

/***************************************
 * CDownHandler
 ***************************************/

class CDownHandler : public IDAUntilNotifier  {

public:

	CDownHandler()  {
    _cRefs = 1;
  }

	~CDownHandler()  {
  }

	STDMETHOD_(ULONG, AddRef)(); 
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD(initNotify)(IDAEventPtr ev, CUpHandler* upHandPtr,
    CControlPoint2* control, IDAStaticsPtr e);
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
public:
	CControlPoint2* _control;

protected:
	long _cRefs;
	IDAEventPtr _ev;
	IDAStaticsPtr _e;
  CUpHandler* _upHandPtr;
};

/***************************************
 * CPickHandler
 ***************************************/

class CPickHandler : public IDAUntilNotifier  {

public:

	CPickHandler()  {
    _cRefs = 1;
  }

	~CPickHandler()  {
  }

	STDMETHOD_(ULONG, AddRef)(); 
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD(initNotify)(IDAImagePtr img, IDAStaticsPtr e);
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
	IDAImagePtr _img;
	IDAStaticsPtr _e;
};

/***************************************
 * CControlPoint2
 ***************************************/

class CControlPoint2 : public IDABvrHook  {

public:

	CControlPoint2()  {
    _cRefs = 1;
  }

	~CControlPoint2()  {
  }

	STDMETHOD_(ULONG, AddRef)(); 
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD(initNotify)(IDAImagePtr img1, IDAImagePtr img2, 
    CPickHandler* pPickHandle, CDownHandler* pDownHandle,double x0, double y0, IDAStaticsPtr e);
  STDMETHOD(Cleanup)();

  // Since we are using #import, the pure virtual function Notify of the 
  // IDAUntilNotifier class (refer to danim.h)  has been renamed to raw_Notify.
  STDMETHOD(raw_Notify)(
    long id,
    VARIANT_BOOL startingPerformance,
    double startTime,
    double gTime,
    double lTime,
    struct IDABehavior * sampleVal,
    struct IDABehavior * curRunningBvr,
    struct IDABehavior * * ppBvr );

  void add(Cons constraint);
  
  void obeyConstraints();
  void obeyConstraints(double p[2]);

public:
	long _cRefs;
  IDAPoint2Ptr _pnt;
	IDAPoint2Ptr _initialPnt;
	IDAImagePtr _img;
  CPickHandler* _pPickHandle;
  CDownHandler* _pDownHandle;
  CUpHandler* _upHandPtr;
	double _p[2];
	vector<Cons> constraints;

	IDAStaticsPtr _e;
};


/***************************************
 * ConsLinear
 ***************************************/

class CConsLinear : public Cons
{
public:
	/** The equation a0*x + a1*y + a2 */
  CConsLinear(double a0, double a1, double a2, BOOL equality)  {
    _a = new double[3];

		double x = a0;
		double y = a1;

		double d = sqrt(x*x + y*y); 

		_a[0] = x/d;
		_a[1] = y/d;
		_a[2] = a2/d;
		_equality = equality;
	}

	/** The line containing (x0, y0) and (x1, y1) */
	CConsLinear(double x0, double y0, double x1, double y1, BOOL equality)  {
		_a = new double[3];

		double x = y0 - y1;
		double y = x1 - x0;

		double d = sqrt(x*x + y*y);

		_a[0] = x/d;
		_a[1] = y/d;
		_a[2] = (x0*y1 - x1*y0)/d;

    _equality = equality;
	}
};




