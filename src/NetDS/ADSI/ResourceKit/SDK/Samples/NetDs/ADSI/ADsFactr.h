/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 17 15:13:27 1998
 */
/* Compiler settings for C:\projects\ADsFactr\ADsFactr.idl:
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

#ifndef __ADsFactr_h__
#define __ADsFactr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IADsFactory_FWD_DEFINED__
#define __IADsFactory_FWD_DEFINED__
typedef interface IADsFactory IADsFactory;
#endif 	/* __IADsFactory_FWD_DEFINED__ */


#ifndef __ADsFactory_FWD_DEFINED__
#define __ADsFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADsFactory ADsFactory;
#else
typedef struct ADsFactory ADsFactory;
#endif /* __cplusplus */

#endif 	/* __ADsFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IADsFactory_INTERFACE_DEFINED__
#define __IADsFactory_INTERFACE_DEFINED__

/* interface IADsFactory */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IADsFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BACFDB72-7E23-11D2-B447-0080C7D071BF")
    IADsFactory : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            BSTR bstrADsPath,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenDSObject( 
            BSTR bstrADsPath,
            BSTR bstrUser,
            BSTR bstrPassword,
            LONG lFlag,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsFactory __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsFactory __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsFactory __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObject )( 
            IADsFactory __RPC_FAR * This,
            BSTR bstrADsPath,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDSObject )( 
            IADsFactory __RPC_FAR * This,
            BSTR bstrADsPath,
            BSTR bstrUser,
            BSTR bstrPassword,
            LONG lFlag,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDisp);
        
        END_INTERFACE
    } IADsFactoryVtbl;

    interface IADsFactory
    {
        CONST_VTBL struct IADsFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsFactory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsFactory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsFactory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsFactory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsFactory_GetObject(This,bstrADsPath,pDisp)	\
    (This)->lpVtbl -> GetObject(This,bstrADsPath,pDisp)

#define IADsFactory_OpenDSObject(This,bstrADsPath,bstrUser,bstrPassword,lFlag,pDisp)	\
    (This)->lpVtbl -> OpenDSObject(This,bstrADsPath,bstrUser,bstrPassword,lFlag,pDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsFactory_GetObject_Proxy( 
    IADsFactory __RPC_FAR * This,
    BSTR bstrADsPath,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDisp);


void __RPC_STUB IADsFactory_GetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsFactory_OpenDSObject_Proxy( 
    IADsFactory __RPC_FAR * This,
    BSTR bstrADsPath,
    BSTR bstrUser,
    BSTR bstrPassword,
    LONG lFlag,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDisp);


void __RPC_STUB IADsFactory_OpenDSObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsFactory_INTERFACE_DEFINED__ */



#ifndef __ADSFACTRLib_LIBRARY_DEFINED__
#define __ADSFACTRLib_LIBRARY_DEFINED__

/* library ADSFACTRLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ADSFACTRLib;

EXTERN_C const CLSID CLSID_ADsFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("BACFDB73-7E23-11D2-B447-0080C7D071BF")
ADsFactory;
#endif
#endif /* __ADSFACTRLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
