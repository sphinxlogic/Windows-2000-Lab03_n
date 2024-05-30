//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 26 11:28:28 1998
 */
/* Compiler settings for AtlBrowser.idl:
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

#ifndef __AtlBrowser_h__
#define __AtlBrowser_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAtlBrCon_FWD_DEFINED__
#define __IAtlBrCon_FWD_DEFINED__
typedef interface IAtlBrCon IAtlBrCon;
#endif 	/* __IAtlBrCon_FWD_DEFINED__ */


#ifndef __AtlBrCon_FWD_DEFINED__
#define __AtlBrCon_FWD_DEFINED__

#ifdef __cplusplus
typedef class AtlBrCon AtlBrCon;
#else
typedef struct AtlBrCon AtlBrCon;
#endif /* __cplusplus */

#endif 	/* __AtlBrCon_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAtlBrCon_INTERFACE_DEFINED__
#define __IAtlBrCon_INTERFACE_DEFINED__

/* interface IAtlBrCon */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAtlBrCon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0818D42F-6247-11D1-ABEE-00D049C10000")
    IAtlBrCon : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHwnd( 
            long __RPC_FAR *phwnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SayHello( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlBrConVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAtlBrCon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAtlBrCon __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAtlBrCon __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAtlBrCon __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAtlBrCon __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAtlBrCon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAtlBrCon __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IAtlBrCon __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IAtlBrCon __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHwnd )( 
            IAtlBrCon __RPC_FAR * This,
            long __RPC_FAR *phwnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SayHello )( 
            IAtlBrCon __RPC_FAR * This);
        
        END_INTERFACE
    } IAtlBrConVtbl;

    interface IAtlBrCon
    {
        CONST_VTBL struct IAtlBrConVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlBrCon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAtlBrCon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAtlBrCon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAtlBrCon_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAtlBrCon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAtlBrCon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAtlBrCon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAtlBrCon_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IAtlBrCon_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IAtlBrCon_GetHwnd(This,phwnd)	\
    (This)->lpVtbl -> GetHwnd(This,phwnd)

#define IAtlBrCon_SayHello(This)	\
    (This)->lpVtbl -> SayHello(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAtlBrCon_Run_Proxy( 
    IAtlBrCon __RPC_FAR * This);


void __RPC_STUB IAtlBrCon_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAtlBrCon_Stop_Proxy( 
    IAtlBrCon __RPC_FAR * This);


void __RPC_STUB IAtlBrCon_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAtlBrCon_GetHwnd_Proxy( 
    IAtlBrCon __RPC_FAR * This,
    long __RPC_FAR *phwnd);


void __RPC_STUB IAtlBrCon_GetHwnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAtlBrCon_SayHello_Proxy( 
    IAtlBrCon __RPC_FAR * This);


void __RPC_STUB IAtlBrCon_SayHello_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAtlBrCon_INTERFACE_DEFINED__ */



#ifndef __ATLBROWSERLib_LIBRARY_DEFINED__
#define __ATLBROWSERLib_LIBRARY_DEFINED__

/* library ATLBROWSERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ATLBROWSERLib;

EXTERN_C const CLSID CLSID_AtlBrCon;

#ifdef __cplusplus

class DECLSPEC_UUID("0818D430-6247-11D1-ABEE-00D049C10000")
AtlBrCon;
#endif
#endif /* __ATLBROWSERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
