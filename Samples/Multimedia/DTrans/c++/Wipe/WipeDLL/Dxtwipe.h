/*******************************************************************************
* DXTWipe.h *
*-----------*
*   Description:
*       This is the header file for the CDXTWipe implementation.
*-------------------------------------------------------------------------------
*  Created By: EDC                                      Date: 01/06/98
*  Copyright (C) 1998 Microsoft Corporation
*  All Rights Reserved
*
*-------------------------------------------------------------------------------
*  Revisions:
*
*******************************************************************************/
#ifndef DXTWipe_h
#define DXTWipe_h

//--- Additional includes
#ifndef DTBase_h
#include <DTBase.h>
#endif

#include "resource.h"

//=== Constants ====================================================

//=== Class, Enum, Struct and Union Declarations ===================

/*** CDXTWipe
*   Sample wipe effect transform. The IOleObjectDXImpl is added to 
*   pick up the IOleClientSite if the transform needs it, otherwise
*   IOleObjectDXImpl should be omitted.
*/
class ATL_NO_VTABLE CDXTWipe : 
    public CDXBaseNTo1,
    public CComCoClass<CDXTWipe, &CLSID_DXTWipeSample>,
    public IDispatchImpl<IDXTWipeSample, &IID_IDXTWipeSample, &LIBID_WIPELib>,
#if(_ATL_VER < 0x0300)
    public CComPropertySupport<CDXTWipe>,
#endif
    public IObjectSafetyImpl2<CDXTWipe>,
    public IPersistStorageImpl<CDXTWipe>,
    public ISpecifyPropertyPagesImpl<CDXTWipe>,
    public IPersistPropertyBagImpl<CDXTWipe>,
    public IOleObjectDXImpl<CDXTWipe>
{
  /*=== ATL Setup ===*/
  public:
    DECLARE_POLY_AGGREGATABLE(CDXTWipe)
#if( _LICENSED_VERSION == 0 )
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_DXTWIPE)
#else
    DECLARE_REGISTER_DX_IMAGE_AUTHOR_TRANS(IDR_DXTWIPE)
#endif


    DECLARE_GET_CONTROLLING_UNKNOWN()

    BEGIN_COM_MAP(CDXTWipe)
        COM_INTERFACE_ENTRY(IDXEffect)
        COM_INTERFACE_ENTRY(IDXTWipeSample)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafetyImpl2<CDXTWipe>)
#if(_ATL_VER <= 0x0200)
        COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
        COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
        COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
#else // Assume version 0x0300 or greater.
        COM_INTERFACE_ENTRY(IPersistStorage)
        COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
#endif
        COM_INTERFACE_ENTRY_DXIMPL(IOleObject)
        COM_INTERFACE_ENTRY_CHAIN( CDXBaseNTo1 )
    END_COM_MAP()

#if(_ATL_VER <= 0x0200)
    BEGIN_PROPERTY_MAP(CDXTWipe)
#else // Assume version 0x0300 or greater.
    BEGIN_PROP_MAP(CDXTWipe)
#endif
        //PROP_ENTRY("Description", dispid, clsid)
        PROP_ENTRY("Gradient Size", DISPID_DXW_GradientSize, CLSID_DXTWipePropPage)
        PROP_ENTRY("Wipe Style", DISPID_DXW_WipeStyle, CLSID_DXTWipePropPage)
        PROP_PAGE(CLSID_DXTWipePropPage)
#if(_ATL_VER <= 0x0200)
    END_PROPERTY_MAP()
#else // Assume version 0x0300 or greater.
    END_PROP_MAP()
#endif

  /*=== Member Data ===*/
    CComPtr<IUnknown> m_pUnkMarshaler;
    long            m_GradientSize;
    float           m_GradPercentSize;
    PULONG          m_pGradientWeights;
    DXWIPEDIRECTION m_eWipeStyle;
    SIZE            m_InputSize;
    BOOL            m_bCopyrightIsNotValid;
#if(_ATL_VER >= 0x0300)
    BOOL            m_bRequiresSave;
#endif

  /*=== Methods =======*/
  public:
    //--- Constructors
    HRESULT FinalConstruct();
    HRESULT FinalRelease() { delete m_pGradientWeights; return S_OK; }

    //--- Non interface methods
    HRESULT _UpdateGradWeights( void );
    void    _UpdateStepRes( void );
    void _ComputeStartPoints(const CDXDBnds & bnds,
            ULONG & AWid, ULONG & AStart, ULONG & BWid, ULONG & BUnpackWid,
            ULONG & GradStart, ULONG & GradWid, ULONG & GradWgtStart);


    //--- Base class overrides
    HRESULT WorkProc( const CDXTWorkInfoNTo1& WI, BOOL* pbContinue );
    HRESULT OnSetup( DWORD dwFlags );
    void OnGetSurfacePickOrder(const CDXDBnds & TestPoint, ULONG & ulInToTest, ULONG aInIndex[], BYTE aWeight[]);

  public:
    //=== IDXEffect ======================================================
    DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)

    //=== IPersistPropertyBag ============================================
    // We don't persist unless we are the licensed version
#if( _LICENSED_VERSION == 0 )
    STDMETHOD( Save )( IPropertyBag* pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties )
    {
        return E_FAIL;
    }
#endif

    //=== IDXTWipe =======================================================
    STDMETHOD( get_GradientSize )( float *pPercentSize  );
    STDMETHOD( put_GradientSize )( float PercentSize );
    STDMETHOD( get_WipeStyle )( DXWIPEDIRECTION *pVal );
    STDMETHOD( put_WipeStyle )( DXWIPEDIRECTION newVal );
    STDMETHOD( get_Copyright )( BSTR *pVal );
    STDMETHOD( put_Copyright )( BSTR newVal );
};

//=== Inline Function Definitions ========================================

#endif /* This must be the last line in the file */
