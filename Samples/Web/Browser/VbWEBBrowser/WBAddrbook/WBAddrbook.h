/* Microsoft Corporation Copyright 1999 				  */
/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 20 11:48:46 1998
 */
/* Compiler settings for WBAddrBook.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WBAddrBook_h__
#define __WBAddrBook_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWBWAB_FWD_DEFINED__
#define __IWBWAB_FWD_DEFINED__
typedef interface IWBWAB IWBWAB;
#endif 	/* __IWBWAB_FWD_DEFINED__ */


#ifndef __WBWAB_FWD_DEFINED__
#define __WBWAB_FWD_DEFINED__

#ifdef __cplusplus
typedef class WBWAB WBWAB;
#else
typedef struct WBWAB WBWAB;
#endif /* __cplusplus */

#endif 	/* __WBWAB_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IWBWAB_INTERFACE_DEFINED__
#define __IWBWAB_INTERFACE_DEFINED__

/* interface IWBWAB */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWBWAB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0340F05E-E75D-11D1-AFDB-000086189887")
    IWBWAB : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_WebBrowser( 
            /* [retval][out] */ LPDISPATCH __RPC_FAR *ppWebBrowser) = 0;
        
        virtual /* [helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_WebBrowser( 
            /* [in] */ LPDISPATCH pWebBrowser) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Offline( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOffline) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Offline( 
            /* [in] */ VARIANT_BOOL bOffline) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowAddressBook( 
            /* [in] */ LONG __MIDL_0015) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowMail( 
            /* [in] */ LONG hWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowNews( 
            /* [in] */ LONG hWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowProperties( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowViewSource( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowFind( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowOrganizeFavorites( 
            /* [in] */ LONG __MIDL_0016) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowUpdateSubscriptions( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowMyComputer( 
            /* [in] */ LONG __MIDL_0017) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetURL( 
            /* [in] */ VARIANT vPath,
            /* [out] */ LPVARIANT vURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWBWABVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWBWAB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWBWAB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWBWAB __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WebBrowser )( 
            IWBWAB __RPC_FAR * This,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *ppWebBrowser);
        
        /* [helpstring][propputref][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_WebBrowser )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ LPDISPATCH pWebBrowser);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Offline )( 
            IWBWAB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOffline);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Offline )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bOffline);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowAddressBook )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ LONG __MIDL_0015);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowMail )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ LONG hWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowNews )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ LONG hWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowProperties )( 
            IWBWAB __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowViewSource )( 
            IWBWAB __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowFind )( 
            IWBWAB __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowOrganizeFavorites )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ LONG __MIDL_0016);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowUpdateSubscriptions )( 
            IWBWAB __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowMyComputer )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ LONG __MIDL_0017);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetURL )( 
            IWBWAB __RPC_FAR * This,
            /* [in] */ VARIANT vPath,
            /* [out] */ LPVARIANT vURL);
        
        END_INTERFACE
    } IWBWABVtbl;

    interface IWBWAB
    {
        CONST_VTBL struct IWBWABVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWBWAB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWBWAB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWBWAB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWBWAB_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWBWAB_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWBWAB_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWBWAB_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWBWAB_get_WebBrowser(This,ppWebBrowser)	\
    (This)->lpVtbl -> get_WebBrowser(This,ppWebBrowser)

#define IWBWAB_putref_WebBrowser(This,pWebBrowser)	\
    (This)->lpVtbl -> putref_WebBrowser(This,pWebBrowser)

#define IWBWAB_get_Offline(This,pbOffline)	\
    (This)->lpVtbl -> get_Offline(This,pbOffline)

#define IWBWAB_put_Offline(This,bOffline)	\
    (This)->lpVtbl -> put_Offline(This,bOffline)

#define IWBWAB_ShowAddressBook(This,__MIDL_0015)	\
    (This)->lpVtbl -> ShowAddressBook(This,__MIDL_0015)

#define IWBWAB_ShowMail(This,hWnd)	\
    (This)->lpVtbl -> ShowMail(This,hWnd)

#define IWBWAB_ShowNews(This,hWnd)	\
    (This)->lpVtbl -> ShowNews(This,hWnd)

#define IWBWAB_ShowProperties(This)	\
    (This)->lpVtbl -> ShowProperties(This)

#define IWBWAB_ShowViewSource(This)	\
    (This)->lpVtbl -> ShowViewSource(This)

#define IWBWAB_ShowFind(This)	\
    (This)->lpVtbl -> ShowFind(This)

#define IWBWAB_ShowOrganizeFavorites(This,__MIDL_0016)	\
    (This)->lpVtbl -> ShowOrganizeFavorites(This,__MIDL_0016)

#define IWBWAB_ShowUpdateSubscriptions(This)	\
    (This)->lpVtbl -> ShowUpdateSubscriptions(This)

#define IWBWAB_ShowMyComputer(This,__MIDL_0017)	\
    (This)->lpVtbl -> ShowMyComputer(This,__MIDL_0017)

#define IWBWAB_GetURL(This,vPath,vURL)	\
    (This)->lpVtbl -> GetURL(This,vPath,vURL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_get_WebBrowser_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *ppWebBrowser);


void __RPC_STUB IWBWAB_get_WebBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_putref_WebBrowser_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ LPDISPATCH pWebBrowser);


void __RPC_STUB IWBWAB_putref_WebBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_get_Offline_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOffline);


void __RPC_STUB IWBWAB_get_Offline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_put_Offline_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bOffline);


void __RPC_STUB IWBWAB_put_Offline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowAddressBook_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ LONG __MIDL_0015);


void __RPC_STUB IWBWAB_ShowAddressBook_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowMail_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ LONG hWnd);


void __RPC_STUB IWBWAB_ShowMail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowNews_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ LONG hWnd);


void __RPC_STUB IWBWAB_ShowNews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowProperties_Proxy( 
    IWBWAB __RPC_FAR * This);


void __RPC_STUB IWBWAB_ShowProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowViewSource_Proxy( 
    IWBWAB __RPC_FAR * This);


void __RPC_STUB IWBWAB_ShowViewSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowFind_Proxy( 
    IWBWAB __RPC_FAR * This);


void __RPC_STUB IWBWAB_ShowFind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowOrganizeFavorites_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ LONG __MIDL_0016);


void __RPC_STUB IWBWAB_ShowOrganizeFavorites_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowUpdateSubscriptions_Proxy( 
    IWBWAB __RPC_FAR * This);


void __RPC_STUB IWBWAB_ShowUpdateSubscriptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_ShowMyComputer_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ LONG __MIDL_0017);


void __RPC_STUB IWBWAB_ShowMyComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWBWAB_GetURL_Proxy( 
    IWBWAB __RPC_FAR * This,
    /* [in] */ VARIANT vPath,
    /* [out] */ LPVARIANT vURL);


void __RPC_STUB IWBWAB_GetURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWBWAB_INTERFACE_DEFINED__ */



#ifndef __WBADDRBOOKLib_LIBRARY_DEFINED__
#define __WBADDRBOOKLib_LIBRARY_DEFINED__

/* library WBADDRBOOKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBADDRBOOKLib;

EXTERN_C const CLSID CLSID_WBWAB;

#ifdef __cplusplus

class DECLSPEC_UUID("0340F05F-E75D-11D1-AFDB-000086189887")
WBWAB;
#endif
#endif /* __WBADDRBOOKLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
