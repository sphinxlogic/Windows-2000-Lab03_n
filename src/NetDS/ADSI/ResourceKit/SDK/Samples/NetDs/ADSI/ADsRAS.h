/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Apr 13 11:18:46 1999
 */
/* Compiler settings for C:\projects\RTK\ADsRAS\ADsRAS.idl:
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

#ifndef __ADsRAS_h__
#define __ADsRAS_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IADsRas_FWD_DEFINED__
#define __IADsRas_FWD_DEFINED__
typedef interface IADsRas IADsRas;
#endif 	/* __IADsRas_FWD_DEFINED__ */


#ifndef __ADsRas_FWD_DEFINED__
#define __ADsRas_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADsRas ADsRas;
#else
typedef struct ADsRas ADsRas;
#endif /* __cplusplus */

#endif 	/* __ADsRas_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IADsRas_INTERFACE_DEFINED__
#define __IADsRas_INTERFACE_DEFINED__

/* interface IADsRas */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IADsRas;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1F533EF-F118-11D2-BC88-00C04FD430AF")
    IADsRas : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DialinPrivilege( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DialinPrivilege( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRasCallBack( 
            /* [in] */ long lCallBack,
            /* [optional][in] */ BSTR szPhoneNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRasCallBack( 
            /* [retval][out] */ long __RPC_FAR *lPrivilege) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRasPhoneNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *pszPhoneNumber) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsRasVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsRas __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsRas __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsRas __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsRas __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsRas __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsRas __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsRas __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DialinPrivilege )( 
            IADsRas __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DialinPrivilege )( 
            IADsRas __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRasCallBack )( 
            IADsRas __RPC_FAR * This,
            /* [in] */ long lCallBack,
            /* [optional][in] */ BSTR szPhoneNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRasCallBack )( 
            IADsRas __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *lPrivilege);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRasPhoneNumber )( 
            IADsRas __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pszPhoneNumber);
        
        END_INTERFACE
    } IADsRasVtbl;

    interface IADsRas
    {
        CONST_VTBL struct IADsRasVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsRas_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsRas_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsRas_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsRas_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsRas_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsRas_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsRas_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsRas_get_DialinPrivilege(This,pVal)	\
    (This)->lpVtbl -> get_DialinPrivilege(This,pVal)

#define IADsRas_put_DialinPrivilege(This,newVal)	\
    (This)->lpVtbl -> put_DialinPrivilege(This,newVal)

#define IADsRas_SetRasCallBack(This,lCallBack,szPhoneNumber)	\
    (This)->lpVtbl -> SetRasCallBack(This,lCallBack,szPhoneNumber)

#define IADsRas_GetRasCallBack(This,lPrivilege)	\
    (This)->lpVtbl -> GetRasCallBack(This,lPrivilege)

#define IADsRas_GetRasPhoneNumber(This,pszPhoneNumber)	\
    (This)->lpVtbl -> GetRasPhoneNumber(This,pszPhoneNumber)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADsRas_get_DialinPrivilege_Proxy( 
    IADsRas __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IADsRas_get_DialinPrivilege_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IADsRas_put_DialinPrivilege_Proxy( 
    IADsRas __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IADsRas_put_DialinPrivilege_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsRas_SetRasCallBack_Proxy( 
    IADsRas __RPC_FAR * This,
    /* [in] */ long lCallBack,
    /* [optional][in] */ BSTR szPhoneNumber);


void __RPC_STUB IADsRas_SetRasCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsRas_GetRasCallBack_Proxy( 
    IADsRas __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *lPrivilege);


void __RPC_STUB IADsRas_GetRasCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsRas_GetRasPhoneNumber_Proxy( 
    IADsRas __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pszPhoneNumber);


void __RPC_STUB IADsRas_GetRasPhoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsRas_INTERFACE_DEFINED__ */



#ifndef __ADSRASLib_LIBRARY_DEFINED__
#define __ADSRASLib_LIBRARY_DEFINED__

/* library ADSRASLib */
/* [helpstring][version][uuid] */ 


enum ADS_RAS_CALLBACK_ENUM
    {	ADS_RAS_NOCALLBACK	= 0x1,
	ADS_RAS_ADMIN_SETCALLBACK	= 0x2,
	ADS_RAS_CALLER_SETCALLBACK	= 0x4
    };

EXTERN_C const IID LIBID_ADSRASLib;

EXTERN_C const CLSID CLSID_ADsRas;

#ifdef __cplusplus

class DECLSPEC_UUID("F1F533F0-F118-11D2-BC88-00C04FD430AF")
ADsRas;
#endif
#endif /* __ADSRASLib_LIBRARY_DEFINED__ */

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
