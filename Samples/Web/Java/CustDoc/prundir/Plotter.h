/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: JavaLib */

#ifndef _JavaLib_H_
#define _JavaLib_H_

DEFINE_GUID(LIBID_JavaLib,0xEFFA21E0L,0x6928,0x11D0,0xBF,0xFC,0x00,0xAA,0x00,0x3C,0xFD,0xFC);

DEFINE_GUID(IID_IPlotter,0xEFFA21E1L,0x6928,0x11D0,0xBF,0xFC,0x00,0xAA,0x00,0x3C,0xFD,0xFC);

/* Definition of interface: IPlotter */
#undef INTERFACE
#define INTERFACE IPlotter

DECLARE_INTERFACE_(IPlotter, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
#endif

    /* IPlotter methods */
    STDMETHOD(DrawLine)(THIS_ POINT FAR* start, POINT FAR* end) PURE;
};

DEFINE_GUID(CLSID_CPlotter,0xEFFA21E2L,0x6928,0x11D0,0xBF,0xFC,0x00,0xAA,0x00,0x3C,0xFD,0xFC);

#ifdef __cplusplus
class CPlotter;
#endif

#endif
