// Dissolve.h : Declaration of the CDissolve

#ifndef __DISSOLVE_H_
#define __DISSOLVE_H_

#include "resource.h"       // main symbols

#define DXEFFECT_MSFT_DISSOLVE_NUM_RATES 10

/////////////////////////////////////////////////////////////////////////////
// CDissolve
class ATL_NO_VTABLE CDissolve : 
	public CDXBaseNTo1,
       	public CComCoClass<CDissolve, &CLSID_Dissolve>,
#if(_ATL_VER < 0x0300)
        public CComPropertySupport<CDissolve>,
#endif
        public IObjectSafetyImpl2<CDissolve>,
        public IPersistStorageImpl<CDissolve>,
        public ISpecifyPropertyPagesImpl<CDissolve>,
        public IPersistPropertyBagImpl<CDissolve>,
	public IDispatchImpl<IDissolve, &IID_IDissolve, &LIBID_DXTMSFTLib>
{
        DECLARE_IDXEFFECT_METHODS(0)

public:
// The speed rate of dissolve for positions along the X axis.
// 0.0 means don't dissolve at this location.
// 0.5 means stop half way down at time == 1.0.
// 1.0 means hit the bottom at time == 1.0.
// 2.0 means hit the bottom at time == 0.5.
	STDMETHOD(get_SpeedPt9)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt9)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt8)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt8)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt7)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt7)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt6)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt6)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt5)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt5)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt4)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt4)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt3)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt3)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt2)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt2)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt1)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt1)(/*[in]*/ float newVal);
	STDMETHOD(get_SpeedPt0)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_SpeedPt0)(/*[in]*/ float newVal);
	CDissolve();
        ~CDissolve() {};

        DECLARE_REGISTER_DX_3D_AUTHOR_TRANS(IDR_DISSOLVE);
        
        HRESULT OnSetup(DWORD dwFlags);
        HRESULT OnExecute(const GUID* /* pRequestID */,
                         const DXBNDS * /* pClipBnds */,
                         const DXVEC * /* pPlacement */);
	HRESULT DetermineBnds(CDXCBnds & Bnds);

    BEGIN_COM_MAP(CDissolve)
	COM_INTERFACE_ENTRY(IDissolve)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IDXEffect)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafetyImpl2<CDissolve>)
#if(_ATL_VER < 0x0300)
        COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
        COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
        COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
#else
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
        COM_INTERFACE_ENTRY(IPersistStorage)
        COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
#endif
        COM_INTERFACE_ENTRY_CHAIN(CDXBaseNTo1)
    END_COM_MAP()

#if(_ATL_VER < 0x0300)
    BEGIN_PROPERTY_MAP(CDissolve)
#else
    BEGIN_PROP_MAP(CDissolve)
#endif
        PROP_PAGE(CLSID_Disslvpp)
#if(_ATL_VER < 0x0300)
    END_PROPERTY_MAP()
#else
    END_PROP_MAP()
#endif

// IDissolve
private:
    HRESULT UpdateVertices(LPDIRECT3DRMMESHBUILDER3 lpMBlder, float Percent, BOOL isB);
    int             m_iXVertices, m_iYVertices;
    float           m_BaseRate[DXEFFECT_MSFT_DISSOLVE_NUM_RATES];
    int             m_iDirection;
public:
#if(_ATL_VER >= 0x0300)
    BOOL            m_bRequiresSave;
#endif
};

#endif //__DISSOLVE_H_
