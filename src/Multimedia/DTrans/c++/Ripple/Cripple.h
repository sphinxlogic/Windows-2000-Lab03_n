// Ripple.h : Declaration of the CRipple

#ifndef __RIPPLE_H_
#define __RIPPLE_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CRipple
class ATL_NO_VTABLE CRipple : 
        public CDXBaseNTo1,
	public CComCoClass<CRipple, &CLSID_Ripple>,
#if(_ATL_VER < 0x0300)
        public CComPropertySupport<CRipple>,
#endif
        public IObjectSafetyImpl2<CRipple>,
	public IDispatchImpl<IRipple, &IID_IRipple, &LIBID_RIPPLELib>,
        public IPersistStorageImpl<CRipple>,
        public ISpecifyPropertyPagesImpl<CRipple>,
        public IPersistPropertyBagImpl<CRipple>
{
public:
	CRipple();

        DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
        DECLARE_REGISTER_DX_TRANSFORM(IDR_RIPPLE, CATID_DX3DTransform)
        
        HRESULT InitializeBitmap(void);
        HRESULT OnSetup( DWORD /* dwFlags */);
        HRESULT OnExecute(const GUID* /* pRequestID */, const DXBNDS * /*pClipBnds */,
                          const DXVEC * /*pPlacement */ );
        HRESULT Reset(void);
        void FinalRelease(void);
	HRESULT DetermineBnds(CDXCBnds & Bnds);

BEGIN_COM_MAP(CRipple)
	COM_INTERFACE_ENTRY(IRipple)
        COM_INTERFACE_ENTRY(IDXEffect)
	COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafetyImpl2<CRipple>)
#if(_ATL_VER <= 0x0200)
        COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
        COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
        COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
#else // Assume version 0x0300 or greater.
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
        COM_INTERFACE_ENTRY(IPersistStorage)
        COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
#endif
        COM_INTERFACE_ENTRY_CHAIN(CDXBaseNTo1)
END_COM_MAP()

#if(_ATL_VER <= 0x0200)
BEGIN_PROPERTY_MAP(CRipple)
#else // Assume version 0x0300 or greater.
BEGIN_PROP_MAP(CRipple)
#endif
    //PROP_ENTRY("Description", dispid, clsid)
    PROP_ENTRY("XOrigin", 11, CLSID_RipProp)
    PROP_ENTRY("YOrigin", 12, CLSID_RipProp)
    PROP_ENTRY("Wavelength", 13, CLSID_RipProp)
    PROP_ENTRY("Amplitde", 14, CLSID_RipProp)
    PROP_ENTRY("NumberOfWaves", 15, CLSID_RipProp)
    PROP_ENTRY("MinSteps", 16, CLSID_RipProp)
    PROP_ENTRY("MaxSteps", 17, CLSID_RipProp)
    PROP_PAGE(CLSID_RipProp)
#if(_ATL_VER <= 0x0200)
END_PROPERTY_MAP()
#else // Assume version 0x0300 or greater.
END_PROP_MAP()
#endif

private:
	float GetCurrentAmplitude(void);

// IRipple
public:
	long m_NumWaves;
        long    m_MinSteps;
        long    m_MaxSteps;
        long    m_Steps;
	float m_Amplitude;
	float m_Wavelength;
	float m_YOrigin;
	float m_XOrigin;
        float * m_pflDistanceTable;
        float m_flWidth;
        float m_flHeight;

        int   m_cVertices;
        CComPtr<IDirect3DRMTexture3> m_cpInputTexture;
        D3DRMGROUPINDEX  m_group;
        D3DRMVERTEX*     m_prgvert;
#if(_ATL_VER >= 0x0300)
        BOOL            m_bRequiresSave;
#endif
	STDMETHOD(get_NumberOfWaves)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumberOfWaves)(/*[in]*/ long newVal);
	STDMETHOD(get_Amplitude)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Amplitude)(/*[in]*/ float newVal);
	STDMETHOD(get_Wavelength)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Wavelength)(/*[in]*/ float newVal);
	STDMETHOD(get_YOrigin)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_YOrigin)(/*[in]*/ float newVal);
	STDMETHOD(get_XOrigin)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_XOrigin)(/*[in]*/ float newVal);
	STDMETHOD(get_MinSteps)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MinSteps)(/*[in]*/ long newVal);
	STDMETHOD(get_MaxSteps)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxSteps)(/*[in]*/ long newVal);

	STDMETHODIMP SetQuality(float fQuality);
};



#endif //__RIPPLE_H_
