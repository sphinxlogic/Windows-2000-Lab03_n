// Ruffle.h : Declaration of the CRuffle

#ifndef __RUFFLE_H_
#define __RUFFLE_H_
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRuffle
class ATL_NO_VTABLE CRuffle : 
    public CDXBaseNTo1,
    public CComCoClass<CRuffle, &CLSID_Ruffle>,
#if(_ATL_VER < 0x0300)
    public CComPropertySupport<CRuffle>,
#endif
    public IDispatchImpl<IRuffle, &IID_IRuffle, &LIBID_DXTMSFTLib>,
    public IObjectSafetyImpl2<CRuffle>,
    public IPersistStorageImpl<CRuffle>,
    public ISpecifyPropertyPagesImpl<CRuffle>,
    public IPersistPropertyBagImpl<CRuffle>
{
  /*=== ATL Setup ===*/
  public:
    DECLARE_POLY_AGGREGATABLE(CRuffle)
    DECLARE_REGISTER_DX_3D_AUTHOR_TRANS(IDR_RUFFLE)
    DECLARE_GET_CONTROLLING_UNKNOWN()

    BEGIN_COM_MAP(CRuffle)
	COM_INTERFACE_ENTRY(IRuffle)
	COM_INTERFACE_ENTRY(IDXEffect)
	COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafetyImpl2<CRuffle>)
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
    BEGIN_PROPERTY_MAP(CRuffle)
#else
    BEGIN_PROP_MAP(CRuffle)
#endif
        PROP_ENTRY("MaxRotations", DISPID_Ruffle_MaxRotations, CLSID_RuffleProp)
        PROP_PAGE(CLSID_RuffleProp)
#if(_ATL_VER < 0x0300)
    END_PROPERTY_MAP()
#else
    END_PROP_MAP()
#endif

  public:
    CRuffle();
    ~CRuffle();

    HRESULT OnSetup(DWORD dwFlags);
    HRESULT OnExecute(const GUID* pRequestID, const DXBNDS *pClipBnds, const DXVEC *pPlacement );
    HRESULT DetermineBnds(CDXCBnds & Bnds);

  private:
    HRESULT DoOneMeshBuilder(IDirect3DRMMeshBuilder3* lpMeshBuilderOut, IDirect3DRMMeshBuilder3* lpMeshBuilderIn);
    int             m_iSpin;
    int             m_iMaxRotations;
    DWORD           m_dwNextRandom;
    double RandomSpin(void);

    void SeedRandSpin(DWORD seed)
    {
	_ASSERT(seed);
	m_dwNextRandom = seed;
    }

  public:
#if(_ATL_VER >= 0x0300)
    BOOL            m_bRequiresSave;
#endif
    void SetMaximumRotations(int iRot);
    int GetMaximumRotations(void) {return m_iMaxRotations;}

    friend HRESULT TraverseSubMeshCallBack (void *lpThis, 
				    IDirect3DRMMeshBuilder3* lpMeshBuilderOut,
				    IDirect3DRMMeshBuilder3* lpMeshBuilderIn);

  public:
    //=== IDXEffect ======================================================
    DECLARE_IDXEFFECT_METHODS(0);

    //=== IRuffle interface methods ========================================
    STDMETHOD(get_MaxRotations)( long *pVal  );
    STDMETHOD(put_MaxRotations)( long newVal );
};

#endif //__RUFFLE_H_
