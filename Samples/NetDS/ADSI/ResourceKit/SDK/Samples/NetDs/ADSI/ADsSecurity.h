/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon May 17 12:54:52 1999
 */
/* Compiler settings for C:\projects\RTK\ADsSecurity\ADsSecurity.idl:
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

#ifndef __ADsSecurity_h__
#define __ADsSecurity_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IADsSecurity_FWD_DEFINED__
#define __IADsSecurity_FWD_DEFINED__
typedef interface IADsSecurity IADsSecurity;
#endif 	/* __IADsSecurity_FWD_DEFINED__ */


#ifndef __IADsSID_FWD_DEFINED__
#define __IADsSID_FWD_DEFINED__
typedef interface IADsSID IADsSID;
#endif 	/* __IADsSID_FWD_DEFINED__ */


#ifndef __ADsSecurity_FWD_DEFINED__
#define __ADsSecurity_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADsSecurity ADsSecurity;
#else
typedef struct ADsSecurity ADsSecurity;
#endif /* __cplusplus */

#endif 	/* __ADsSecurity_FWD_DEFINED__ */


#ifndef __ADsSID_FWD_DEFINED__
#define __ADsSID_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADsSID ADsSID;
#else
typedef struct ADsSID ADsSID;
#endif /* __cplusplus */

#endif 	/* __ADsSID_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IADsSecurity_INTERFACE_DEFINED__
#define __IADsSecurity_INTERFACE_DEFINED__

/* interface IADsSecurity */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IADsSecurity;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("212029A9-C50D-11D2-BC7E-00C04FD430AF")
    IADsSecurity : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSecurityDescriptor( 
            /* [optional][in] */ VARIANT varPath,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSecurityDescriptor( 
            /* [in] */ VARIANT varData,
            /* [optional][in] */ VARIANT varPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSID( 
            /* [in] */ VARIANT varPath,
            /* [retval][out] */ VARIANT __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSecurityDescriptorAs( 
            /* [in] */ long lFormat,
            /* [optional][in] */ VARIANT varPath,
            /* [retval][out] */ VARIANT __RPC_FAR *pRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsSecurityVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsSecurity __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsSecurity __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsSecurity __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSecurityDescriptor )( 
            IADsSecurity __RPC_FAR * This,
            /* [optional][in] */ VARIANT varPath,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSecurityDescriptor )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ VARIANT varData,
            /* [optional][in] */ VARIANT varPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSID )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ VARIANT varPath,
            /* [retval][out] */ VARIANT __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSecurityDescriptorAs )( 
            IADsSecurity __RPC_FAR * This,
            /* [in] */ long lFormat,
            /* [optional][in] */ VARIANT varPath,
            /* [retval][out] */ VARIANT __RPC_FAR *pRet);
        
        END_INTERFACE
    } IADsSecurityVtbl;

    interface IADsSecurity
    {
        CONST_VTBL struct IADsSecurityVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsSecurity_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsSecurity_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsSecurity_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsSecurity_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsSecurity_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsSecurity_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsSecurity_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsSecurity_GetSecurityDescriptor(This,varPath,pVariant)	\
    (This)->lpVtbl -> GetSecurityDescriptor(This,varPath,pVariant)

#define IADsSecurity_SetSecurityDescriptor(This,varData,varPath)	\
    (This)->lpVtbl -> SetSecurityDescriptor(This,varData,varPath)

#define IADsSecurity_GetSID(This,varPath,pRet)	\
    (This)->lpVtbl -> GetSID(This,varPath,pRet)

#define IADsSecurity_GetSecurityDescriptorAs(This,lFormat,varPath,pRet)	\
    (This)->lpVtbl -> GetSecurityDescriptorAs(This,lFormat,varPath,pRet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsSecurity_GetSecurityDescriptor_Proxy( 
    IADsSecurity __RPC_FAR * This,
    /* [optional][in] */ VARIANT varPath,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IADsSecurity_GetSecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsSecurity_SetSecurityDescriptor_Proxy( 
    IADsSecurity __RPC_FAR * This,
    /* [in] */ VARIANT varData,
    /* [optional][in] */ VARIANT varPath);


void __RPC_STUB IADsSecurity_SetSecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsSecurity_GetSID_Proxy( 
    IADsSecurity __RPC_FAR * This,
    /* [in] */ VARIANT varPath,
    /* [retval][out] */ VARIANT __RPC_FAR *pRet);


void __RPC_STUB IADsSecurity_GetSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsSecurity_GetSecurityDescriptorAs_Proxy( 
    IADsSecurity __RPC_FAR * This,
    /* [in] */ long lFormat,
    /* [optional][in] */ VARIANT varPath,
    /* [retval][out] */ VARIANT __RPC_FAR *pRet);


void __RPC_STUB IADsSecurity_GetSecurityDescriptorAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsSecurity_INTERFACE_DEFINED__ */


#ifndef __IADsSID_INTERFACE_DEFINED__
#define __IADsSID_INTERFACE_DEFINED__

/* interface IADsSID */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IADsSID;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("212029AE-C50D-11D2-BC7E-00C04FD430AF")
    IADsSID : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAs( 
            /* [in] */ long lFormat,
            /* [retval][out] */ VARIANT __RPC_FAR *pVar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAs( 
            /* [in] */ long lFormat,
            /* [in] */ VARIANT varData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsSIDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsSID __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsSID __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsSID __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsSID __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsSID __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsSID __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsSID __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAs )( 
            IADsSID __RPC_FAR * This,
            /* [in] */ long lFormat,
            /* [retval][out] */ VARIANT __RPC_FAR *pVar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAs )( 
            IADsSID __RPC_FAR * This,
            /* [in] */ long lFormat,
            /* [in] */ VARIANT varData);
        
        END_INTERFACE
    } IADsSIDVtbl;

    interface IADsSID
    {
        CONST_VTBL struct IADsSIDVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsSID_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsSID_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsSID_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsSID_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsSID_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsSID_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsSID_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsSID_GetAs(This,lFormat,pVar)	\
    (This)->lpVtbl -> GetAs(This,lFormat,pVar)

#define IADsSID_SetAs(This,lFormat,varData)	\
    (This)->lpVtbl -> SetAs(This,lFormat,varData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsSID_GetAs_Proxy( 
    IADsSID __RPC_FAR * This,
    /* [in] */ long lFormat,
    /* [retval][out] */ VARIANT __RPC_FAR *pVar);


void __RPC_STUB IADsSID_GetAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADsSID_SetAs_Proxy( 
    IADsSID __RPC_FAR * This,
    /* [in] */ long lFormat,
    /* [in] */ VARIANT varData);


void __RPC_STUB IADsSID_SetAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsSID_INTERFACE_DEFINED__ */



#ifndef __ADSSECURITYLib_LIBRARY_DEFINED__
#define __ADSSECURITYLib_LIBRARY_DEFINED__

/* library ADSSECURITYLib */
/* [helpstring][version][uuid] */ 


enum ADS_SD_FORMAT
    {	ADS_SD_RAW	= 0,
	ADS_SD_HEXSTRING	= ADS_SD_RAW + 1,
	ADS_SD_SDDL	= ADS_SD_HEXSTRING + 1,
	ADS_SD_IID	= ADS_SD_SDDL + 1
    };

enum ADS_SID_FORMAT
    {	ADS_SID_RAW	= 0,
	ADS_SID_HEXSTRING	= ADS_SID_RAW + 1,
	ADS_SID_SAM	= ADS_SID_HEXSTRING + 1,
	ADS_SID_UPN	= ADS_SID_SAM + 1,
	ADS_SID_SDDL	= ADS_SID_UPN + 1,
	ADS_SID_WINNT_PATH	= ADS_SID_SDDL + 1,
	ADS_SID_ACTIVE_DIRECTORY_PATH	= ADS_SID_WINNT_PATH + 1,
	ADS_SID_SID_BINDING	= ADS_SID_ACTIVE_DIRECTORY_PATH + 1
    };

enum ADS_RIGHT_RGY_ENUM
    {	ADS_RIGHT_RGY_KEY_READ	= 0x20019,
	ADS_RIGHT_RGY_KEY_WRITE	= 0x20006,
	ADS_RIGHT_RGY_KEY_EXECUTE	= 0x20019,
	ADS_RIGHT_RGY_KEY_ALL_ACCESS	= 0xf003f,
	ADS_RIGHT_RGY_KEY_QUERY_VALUE	= 0x1,
	ADS_RIGHT_RGY_KEY_SET_VALUE	= 0x2,
	ADS_RIGHT_RGY_CREATE_SUB_KEY	= 0x4,
	ADS_RIGHT_RGY_ENUMERATE_SUB_KEYS	= 0x8,
	ADS_RIGHT_RGY_NOTIFY	= 0x10,
	ADS_RIGHT_RGY_CREATE_LINK	= 0x20
    };

enum ADS_RIGHT_EXCH_ENUM
    {	ADS_RIGHT_EXCH_ADD_CHILD	= 0x1L,
	ADS_RIGHT_EXCH_MODIFY_USER_ATT	= 0x2L,
	ADS_RIGHT_EXCH_MODIFY_ADMIN_ATT	= 0x4L,
	ADS_RIGHT_EXCH_DELETE	= 0x10000L,
	ADS_RIGHT_EXCH_MAIL_SEND_AS	= 0x8L,
	ADS_RIGHT_EXCH_MAIL_RECEIVE_AS	= 0x10L,
	ADS_RIGHT_EXCH_MAIL_ADMIN_AS	= 0x20L,
	ADS_RIGHT_EXCH_DS_REPLICATION	= 0x40L,
	ADS_RIGHT_EXCH_MODIFY_SEC_ATT	= 0x80L,
	ADS_RIGHT_EXCH_DS_SEARCH	= 0x100L
    };

EXTERN_C const IID LIBID_ADSSECURITYLib;

EXTERN_C const CLSID CLSID_ADsSecurity;

#ifdef __cplusplus

class DECLSPEC_UUID("212029AA-C50D-11D2-BC7E-00C04FD430AF")
ADsSecurity;
#endif

EXTERN_C const CLSID CLSID_ADsSID;

#ifdef __cplusplus

class DECLSPEC_UUID("212029AF-C50D-11D2-BC7E-00C04FD430AF")
ADsSID;
#endif
#endif /* __ADSSECURITYLib_LIBRARY_DEFINED__ */

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
