/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: JavaLib */

#ifndef _JavaLib_H_
#define _JavaLib_H_

DEFINE_GUID(LIBID_JavaLib,0x2BEBEC40L,0x6499,0x11D0,0xBF,0xFC,0x00,0xAA,0x00,0x3C,0xFD,0xFC);

typedef struct MYVARIANT {
    unsigned short vt;
    unsigned short pad1;
    unsigned short pad2;
    unsigned short pad3;
    BSTR bstrVal;
    unsigned long pad4;
} MYVARIANT;

DEFINE_GUID(IID_ICustSample,0x2BEBEC41L,0x6499,0x11D0,0xBF,0xFC,0x00,0xAA,0x00,0x3C,0xFD,0xFC);

/* Definition of interface: ICustSample */
#undef INTERFACE
#define INTERFACE ICustSample

DECLARE_INTERFACE_(ICustSample, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* ICustSample methods */
    STDMETHOD(PassFixedPtIn)(THIS_ FIXED fp) PURE;
    STDMETHOD(PassPFixedPtOutRetVal)(THIS_ FIXED FAR* pfp) PURE;
    STDMETHOD(PassPFixedPtIn)(THIS_ FIXED FAR* pfp) PURE;
    STDMETHOD(PassPFixedPtOut)(THIS_ FIXED FAR* pfp) PURE;
    STDMETHOD(PassPFixedPtInOut)(THIS_ FIXED FAR* pfp) PURE;
    STDMETHOD(PassFixedPtsFromComToJava)(THIS_ ICustSample FAR* pCustSample) PURE;
    STDMETHOD(PassMyVariantIn)(THIS_ struct MYVARIANT v) PURE;
    STDMETHOD(PassPMyVariantOutRetVal)(THIS_ struct MYVARIANT FAR* pv) PURE;
    STDMETHOD(PassPMyVariantIn)(THIS_ struct MYVARIANT FAR* pv) PURE;
    STDMETHOD(PassPMyVariantOut)(THIS_ struct MYVARIANT FAR* pv) PURE;
    STDMETHOD(PassPMyVariantInOut)(THIS_ struct MYVARIANT FAR* pv) PURE;
    STDMETHOD(PassMyVariantFromComToJava)(THIS_ ICustSample FAR* pCustSample) PURE;
    STDMETHOD(PassPPointOut)(THIS_ POINT FAR* ppt) PURE;
    STDMETHOD(PassPPointInOut)(THIS_ POINT FAR* ppt) PURE;
    STDMETHOD(PassPointFromComToJava)(THIS_ ICustSample FAR* pCustSample) PURE;
    STDMETHOD(PassRectIn)(THIS_ RECT r) PURE;
    STDMETHOD(PassPRectOutRetVal)(THIS_ RECT FAR* pr) PURE;
    STDMETHOD(PassPRectIn)(THIS_ RECT FAR* pr) PURE;
    STDMETHOD(PassPRectOut)(THIS_ RECT FAR* pr) PURE;
    STDMETHOD(PassPRectInOut)(THIS_ RECT FAR* pr) PURE;
    STDMETHOD(PassPPRectOutRetVal)(THIS_ RECT FAR* FAR* ppr) PURE;
    STDMETHOD(PassPPRectIn)(THIS_ RECT FAR* FAR* ppr) PURE;
    STDMETHOD(PassPPRectOut)(THIS_ RECT FAR* FAR* ppr) PURE;
    STDMETHOD(PassPPRectInOut)(THIS_ RECT FAR* FAR* ppr) PURE;
    STDMETHOD(PassRectFromComToJava)(THIS_ ICustSample FAR* pCustSample) PURE;
    STDMETHOD(PassPStrIn)(THIS_ MYCHAR FAR* pstr) PURE;
    STDMETHOD(PassPPStrOutRetVal)(THIS_ MYCHAR FAR* FAR* ppstr) PURE;
    STDMETHOD(PassPPStrIn)(THIS_ MYCHAR FAR* FAR* ppstr) PURE;
    STDMETHOD(PassPPStrOut)(THIS_ MYCHAR FAR* FAR* ppstr) PURE;
    STDMETHOD(PassPPStrInOut)(THIS_ MYCHAR FAR* FAR* ppstr) PURE;
    STDMETHOD(PassAnsiFromComToJava)(THIS_ ICustSample FAR* pCustSample) PURE;
};

DEFINE_GUID(CLSID_CCustSample,0x2BEBEC42L,0x6499,0x11D0,0xBF,0xFC,0x00,0xAA,0x00,0x3C,0xFD,0xFC);

#ifdef __cplusplus
class CCustSample;
#endif

#endif