/*==========================================================================;
 *
 *  Copyright (C) 1998 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:	htfield.h
 *  Content:	Height Field include file
 *  Author:     Steve J Lacey
 *
 *
 *  Generates a 1x1x1 height field mesh
 ***************************************************************************/

#ifndef __HTFIELD_H_
#define __HTFIELD_H_

#include "resource.h"

class ATL_NO_VTABLE CHeightField : 
        public CDXBaseNTo1,
	public CComCoClass<CHeightField, &CLSID_HeightField>,
#if(_ATL_VER < 0x0300)
        public CComPropertySupport<CHeightField>,
#endif
        public IObjectSafetyImpl2<CHeightField>,
        public IPersistStorageImpl<CHeightField>,
        public ISpecifyPropertyPagesImpl<CHeightField>,
        public IPersistPropertyBagImpl<CHeightField>,
	public IDispatchImpl<IHeightField,
                             &IID_IHeightField,
                             &LIBID_DXTMSFTLib>
{
public:
	CHeightField();

        DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
        DECLARE_REGISTER_DX_3D_AUTHOR_TRANS(IDR_HEIGHTFIELD)
        
        HRESULT OnSetup(DWORD /* dwFlags */);
        HRESULT OnExecute(const GUID*    /* pRequestID */,
			  const DXBNDS * /* pClipBnds  */,
                          const DXVEC *  /* pPlacement */);
        void FinalRelease(void);
	HRESULT DetermineBnds(CDXCBnds & Bnds);

BEGIN_COM_MAP(CHeightField)
	COM_INTERFACE_ENTRY(IHeightField)
        COM_INTERFACE_ENTRY(IDXEffect)
	COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety,
				IObjectSafetyImpl2<CHeightField>)
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

private:
	DWORD m_dwSamples;
	float m_flDepth;
	float m_flWidth;
	float m_flHeight;
	HRESULT ResizeSurface(IDXSurface **ppDst, IDXSurface *pSrc);
        float GetHeight(IDXARGBReadPtr*, CDXDBnds*, float, float);
public:
#if(_ATL_VER >= 0x0300)
        BOOL  m_bRequiresSave;
#endif

public:
	STDMETHOD(get_Samples)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Samples)(/*[in]*/ long newVal);
	STDMETHOD(get_Depth)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Depth)(/*[in]*/ float newVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Height)(/*[in]*/ float newVal);
	STDMETHOD(get_Width)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Width)(/*[in]*/ float newVal);
        IDirect3DRMTexture3*     m_pRMTex;
	IDirectDrawSurface*      m_pDDS;

#if(_ATL_VER < 0x0300)
    BEGIN_PROPERTY_MAP(CHeightField)
#else
    BEGIN_PROP_MAP(CHeightField)
#endif
        //PROP_ENTRY("Description", dispid, clsid)
        PROP_PAGE(CLSID_HtFieldProp)
#if(_ATL_VER < 0x0300)
    END_PROPERTY_MAP()
#else
    END_PROP_MAP()
#endif
};

#endif /* _HTFIELD_H_ */
