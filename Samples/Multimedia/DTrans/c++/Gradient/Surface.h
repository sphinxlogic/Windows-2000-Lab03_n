// Surface.h : Declaration of the CSurface

#ifndef __SURFACE_H_
#define __SURFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSurface
class ATL_NO_VTABLE CSurface : 
	public CComCoClass<CSurface, &CLSID_SimpleGradient>,
	public IDispatchImpl<ISimpleGradient, &IID_ISimpleGradient, &LIBID_GRADLib>,
        public CDXBaseSurface,
        public IDXTScaleOutput
{
public:
    DXPMSAMPLE  m_ULColor;
    DXPMSAMPLE  m_LLColor;
    DXPMSAMPLE  m_URColor;
    DXPMSAMPLE  m_LRColor;

    CSurface() :
        m_ULColor(0xFF0000FF),   // Blue
        m_LLColor(0xFFFFFFFF),   // White
        m_URColor(0xFFFFFFFF),   // White
        m_LRColor(0xFF0000FF)    // Blue
    {
        m_Width = 640;      // Default to something reasonable
        m_Height = 480;
    }

    STDMETHODIMP GetObjectSize(ULONG *pcbSize)
    {
        if( DXIsBadWritePtr(pcbSize, sizeof(*pcbSize) ) ) return E_POINTER;
        *pcbSize = sizeof(this);
        return S_OK;
    }


    const GUID & SurfaceCLSID() { return GetObjectCLSID(); }
    HRESULT CreateARGBPointer(CDXBaseSurface * pSurface, CDXBaseARGBPtr ** ppPtr);
    void DeleteARGBPointer(CDXBaseARGBPtr *pPtr);

    //
    //  Override SampleFormatEnum to return accruate info on transparency
    //
    DXSAMPLEFORMATENUM SampleFormatEnum()
    {
        if ((m_ULColor.Alpha & m_LLColor.Alpha &
             m_URColor.Alpha & m_LRColor.Alpha) == 0xFF)
        {   
            return DXPF_NONSTANDARD;
        }
        else
        {
            return (DXSAMPLEFORMATENUM)(DXPF_NONSTANDARD | DXPF_TRANSPARENCY | DXPF_TRANSLUCENCY);
        }
    }


DECLARE_REGISTER_DX_SURFACE(IDR_SURFACE)
DECLARE_POLY_AGGREGATABLE(CSurface)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSurface)
	COM_INTERFACE_ENTRY(ISimpleGradient)
	COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IDXTScaleOutput)
        COM_INTERFACE_ENTRY_CHAIN(CDXBaseSurface)
END_COM_MAP()

public:
// IDXTScaleOutput
        STDMETHODIMP SetOutputSize(const SIZE OutputSize, BOOL bMaintainAspect);
// ISimpleGradient
	STDMETHOD(get_Width)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Width)(/*[in]*/ long newVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Height)(/*[in]*/ long newVal);
	STDMETHOD(get_LowerLeftColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_LowerLeftColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_UpperLeftColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_UpperLeftColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_UpperRightColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_UpperRightColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_LowerRightColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_LowerRightColor)(/*[in]*/ OLE_COLOR newVal);
};

#endif //__SURFACE_H_
