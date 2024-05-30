// Explode.h : Declaration of the CExplode

#ifndef __EXPLODE_H_
#define __EXPLODE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExplode
class ATL_NO_VTABLE CExplode : 
    public CDXBaseNTo1,
    public CComCoClass<CExplode, &CLSID_Explode>,
#if(_ATL_VER < 0x0300)
    public CComPropertySupport<CExplode>,
#endif
    public IDispatchImpl<IExplode, &IID_IExplode, &LIBID_DXTMSFTLib>,
    public IObjectSafetyImpl2<CExplode>,
    public IPersistStorageImpl<CExplode>,
    public ISpecifyPropertyPagesImpl<CExplode>,
    public IPersistPropertyBagImpl<CExplode>
{
  public:
    DECLARE_POLY_AGGREGATABLE(CExplode)
	DECLARE_REGISTER_DX_3D_AUTHOR_TRANS(IDR_EXPLODE)
    DECLARE_GET_CONTROLLING_UNKNOWN()
 
    BEGIN_COM_MAP(CExplode)
        COM_INTERFACE_ENTRY(IExplode)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IDXEffect)
        COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafetyImpl2<CExplode>)
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
    BEGIN_PROPERTY_MAP(CExplode)
#else
    BEGIN_PROP_MAP(CExplode)
#endif
        PROP_ENTRY("Tumble",		51, CLSID_ExplodeProp)
        PROP_ENTRY("MaxRotations", 52, CLSID_ExplodeProp)
        PROP_ENTRY("FinalVelocity",53, CLSID_ExplodeProp)
        PROP_ENTRY("PositionJump", 54, CLSID_ExplodeProp)
        PROP_ENTRY("DecayTime",	55, CLSID_ExplodeProp)
        PROP_PAGE(CLSID_ExplodeProp)
#if(_ATL_VER < 0x0300)
    END_PROPERTY_MAP()
#else
    END_PROP_MAP()
#endif

    //=== Member data
  protected:
	BOOL  m_bTumble;
   	int   m_iSpin;
	int   m_iMaxRotations;
	float m_fFinalVelocity;
	float m_fPositionJump;
	float m_fDecayTime;
	DWORD m_dwNextRandom;
  public:
#if(_ATL_VER >= 0x0300)
        BOOL  m_bRequiresSave;
#endif

  public:
	CExplode();
	~CExplode();
	HRESULT DetermineBnds(CDXCBnds & Bnds);
    HRESULT OnSetup(DWORD dwFlags);
	HRESULT OnExecute( const GUID* pRequestID, const DXBNDS *pClipBnds, const DXVEC *pPlacement );

	// IExplode
private:
	HRESULT DoOneMeshBuilder(IDirect3DRMMeshBuilder3* lpMeshBuilderOut, IDirect3DRMMeshBuilder3* lpMeshBuilderIn);

	void NextRandom(void) {m_dwNextRandom = m_dwNextRandom * 1103515245 + 12345;}
	DWORD RandomBits(void);
	float RandomFloat(void) 
	{
	    NextRandom();
	    DWORD dwMaxDWORD = -1;
	    double dRetVal = m_dwNextRandom;
	    dRetVal /= dwMaxDWORD;
	    return (float) dRetVal; // ((float)m_dwNextRandom)/dwMaxDWORD;
	}

	double RandomSpin(void);
	void SeedRandSpin(DWORD seed)
	{
	    _ASSERT(seed);
	    m_dwNextRandom = seed;
	}

public:
	void SetMaximumRotations(int iRot);
	int GetMaximumRotations(void) {return m_iMaxRotations;}
	
	friend HRESULT TraverseSubMeshCallBack (void *lpThis, 
					IDirect3DRMMeshBuilder3* lpMeshBuilderOut,
					IDirect3DRMMeshBuilder3* lpMeshBuilderIn);

  public:
    //=== IDXEffect ======================================================
    DECLARE_IDXEFFECT_METHODS(0);

    //=== IDXTWipe =======================================================
	STDMETHOD(get_Tumble)( BOOL *pVal);
	STDMETHOD(put_Tumble)( BOOL newVal);
	STDMETHOD(get_MaxRotations)( long *pVal);
	STDMETHOD(put_MaxRotations)( long newVal);
	STDMETHOD(get_FinalVelocity)( float *pVal);
	STDMETHOD(put_FinalVelocity)( float newVal);
	STDMETHOD(get_PositionJump)( float *pVal);
	STDMETHOD(put_PositionJump)( float newVal);
	STDMETHOD(get_DecayTime)( float *pVal);
	STDMETHOD(put_DecayTime)( float newVal);
};

#endif //__EXPLODE_H_
