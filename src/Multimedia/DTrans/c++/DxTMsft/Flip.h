// Flip.h : Declaration of the CFlip

#ifndef __FLIP_H_
#define __FLIP_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlip
class ATL_NO_VTABLE CFlip : 
	public CDXBaseNTo1,
       	public CComCoClass<CFlip, &CLSID_Flip>,
#if(_ATL_VER < 0x0300)
        public CComPropertySupport<CFlip>,
#endif
        public IObjectSafetyImpl2<CFlip>,
        public IPersistStorageImpl<CFlip>,
        public ISpecifyPropertyPagesImpl<CFlip>,
        public IPersistPropertyBagImpl<CFlip>,
	public IDispatchImpl<IFlip, &IID_IFlip, &LIBID_DXTMSFTLib>
{
        DECLARE_IDXEFFECT_METHODS(0)

public:
	STDMETHOD(get_Width)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Width)(/*[in]*/ float newVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Height)(/*[in]*/ float newVal);
	STDMETHOD(get_Depth)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Depth)(/*[in]*/ float newVal);
	CFlip();
        ~CFlip() {};

        DECLARE_REGISTER_DX_3D_AUTHOR_TRANS(IDR_FLIP);
        
        HRESULT OnSetup(DWORD dwFlags);
        HRESULT OnExecute(const GUID* /* pRequestID */,
                         const DXBNDS * /* pClipBnds */,
                         const DXVEC * /* pPlacement */);
	HRESULT DetermineBnds(CDXCBnds & Bnds);

    BEGIN_COM_MAP(CFlip)
	COM_INTERFACE_ENTRY(IFlip)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IDXEffect)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafetyImpl2<CFlip>)
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
    BEGIN_PROPERTY_MAP(CFlip)
#else
    BEGIN_PROP_MAP(CFlip)
#endif
        //PROP_ENTRY("Description", dispid, clsid)
        PROP_PAGE(CLSID_FlipProp)
#if(_ATL_VER < 0x0300)
    END_PROPERTY_MAP()
#else
    END_PROP_MAP()
#endif


// IFlip
private:
    float m_flWidth;
    float m_flHeight;
    float m_flDepth;
    HRESULT UpdateVertices(LPDIRECT3DRMMESHBUILDER3 lpMBlder, float Percent, BOOL bIsB);
public:
#if(_ATL_VER >= 0x0300)
    BOOL  m_bRequiresSave;
#endif
};

#endif //__FLIP_H_
