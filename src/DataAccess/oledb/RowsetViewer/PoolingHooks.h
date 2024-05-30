
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0266 */
/* at Wed May 26 14:31:20 1999
 */
/* Compiler settings for testhacks.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef __testhacks_h__
#define __testhacks_h__

/* Forward Declarations */ 

#ifndef __IPoolInfo_FWD_DEFINED__
#define __IPoolInfo_FWD_DEFINED__
typedef interface IPoolInfo IPoolInfo;
#endif 	/* __IPoolInfo_FWD_DEFINED__ */


#ifndef __IPoolNotify_FWD_DEFINED__
#define __IPoolNotify_FWD_DEFINED__
typedef interface IPoolNotify IPoolNotify;
#endif 	/* __IPoolNotify_FWD_DEFINED__ */


#ifndef __IPoolMngrInfo_FWD_DEFINED__
#define __IPoolMngrInfo_FWD_DEFINED__
typedef interface IPoolMngrInfo IPoolMngrInfo;
#endif 	/* __IPoolMngrInfo_FWD_DEFINED__ */


#ifndef __IGetPool_FWD_DEFINED__
#define __IGetPool_FWD_DEFINED__
typedef interface IGetPool IGetPool;
#endif 	/* __IGetPool_FWD_DEFINED__ */


#ifndef __IUdlCacheMngr_FWD_DEFINED__
#define __IUdlCacheMngr_FWD_DEFINED__
typedef interface IUdlCacheMngr IUdlCacheMngr;
#endif 	/* __IUdlCacheMngr_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPoolInfo_INTERFACE_DEFINED__
#define __IPoolInfo_INTERFACE_DEFINED__

/* interface IPoolInfo */
/* [object][helpstring][version][uuid] */ 


EXTERN_C const IID IID_IPoolInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e231fcd8-be3d-11d2-91a2-00c04fb6ee9d")
    IPoolInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetPoolTimeOut( 
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ DWORD __RPC_FAR *pdwPrevTimeOut) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetPoolTimeOut( 
            /* [out] */ DWORD __RPC_FAR *pdwTimeOut) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetRetryTimeOut( 
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ DWORD __RPC_FAR *pdwPrevTimeOut) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetRetryTimeOut( 
            /* [out] */ DWORD __RPC_FAR *pdwTimeOut) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ DWORD __RPC_FAR *pdwInUse,
            /* [out] */ DWORD __RPC_FAR *pdwIdle) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetPoolID( 
            /* [out] */ LPOLESTR __RPC_FAR *pwszPoolID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetPrototype( 
            /* [out] */ LPOLESTR __RPC_FAR *pwszInitString,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvoid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPoolInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoolInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoolInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoolInfo __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPoolTimeOut )( 
            IPoolInfo __RPC_FAR * This,
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ DWORD __RPC_FAR *pdwPrevTimeOut);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPoolTimeOut )( 
            IPoolInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwTimeOut);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRetryTimeOut )( 
            IPoolInfo __RPC_FAR * This,
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ DWORD __RPC_FAR *pdwPrevTimeOut);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRetryTimeOut )( 
            IPoolInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwTimeOut);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IPoolInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwInUse,
            /* [out] */ DWORD __RPC_FAR *pdwIdle);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPoolID )( 
            IPoolInfo __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *pwszPoolID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrototype )( 
            IPoolInfo __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *pwszInitString,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvoid);
        
        END_INTERFACE
    } IPoolInfoVtbl;

    interface IPoolInfo
    {
        CONST_VTBL struct IPoolInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoolInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoolInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoolInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoolInfo_SetPoolTimeOut(This,dwTimeOut,pdwPrevTimeOut)	\
    (This)->lpVtbl -> SetPoolTimeOut(This,dwTimeOut,pdwPrevTimeOut)

#define IPoolInfo_GetPoolTimeOut(This,pdwTimeOut)	\
    (This)->lpVtbl -> GetPoolTimeOut(This,pdwTimeOut)

#define IPoolInfo_SetRetryTimeOut(This,dwTimeOut,pdwPrevTimeOut)	\
    (This)->lpVtbl -> SetRetryTimeOut(This,dwTimeOut,pdwPrevTimeOut)

#define IPoolInfo_GetRetryTimeOut(This,pdwTimeOut)	\
    (This)->lpVtbl -> GetRetryTimeOut(This,pdwTimeOut)

#define IPoolInfo_GetCount(This,pdwInUse,pdwIdle)	\
    (This)->lpVtbl -> GetCount(This,pdwInUse,pdwIdle)

#define IPoolInfo_GetPoolID(This,pwszPoolID)	\
    (This)->lpVtbl -> GetPoolID(This,pwszPoolID)

#define IPoolInfo_GetPrototype(This,pwszInitString,riid,ppvoid)	\
    (This)->lpVtbl -> GetPrototype(This,pwszInitString,riid,ppvoid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_SetPoolTimeOut_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [in] */ DWORD dwTimeOut,
    /* [out] */ DWORD __RPC_FAR *pdwPrevTimeOut);


void __RPC_STUB IPoolInfo_SetPoolTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_GetPoolTimeOut_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwTimeOut);


void __RPC_STUB IPoolInfo_GetPoolTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_SetRetryTimeOut_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [in] */ DWORD dwTimeOut,
    /* [out] */ DWORD __RPC_FAR *pdwPrevTimeOut);


void __RPC_STUB IPoolInfo_SetRetryTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_GetRetryTimeOut_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwTimeOut);


void __RPC_STUB IPoolInfo_GetRetryTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_GetCount_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwInUse,
    /* [out] */ DWORD __RPC_FAR *pdwIdle);


void __RPC_STUB IPoolInfo_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_GetPoolID_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *pwszPoolID);


void __RPC_STUB IPoolInfo_GetPoolID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolInfo_GetPrototype_Proxy( 
    IPoolInfo __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *pwszInitString,
    /* [in] */ REFIID riid,
    /* [out] */ void __RPC_FAR *__RPC_FAR *ppvoid);


void __RPC_STUB IPoolInfo_GetPrototype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoolInfo_INTERFACE_DEFINED__ */


#ifndef __IPoolNotify_INTERFACE_DEFINED__
#define __IPoolNotify_INTERFACE_DEFINED__

/* interface IPoolNotify */
/* [object][helpstring][version][uuid] */ 

typedef /* [public][public] */ 
enum __MIDL_IPoolNotify_0001
    {	EID_CREATERES	= 0x1,
	EID_RELEASERES	= 0x2,
	EID_DESTROYRES	= 0x4,
	EID_ENLISTRES	= 0x8,
	EID_RESETRES	= 0x10,
	EID_RATERES	= 0x20,
	EID_DRAWRES	= 0x40
    }	SPNOTIFICATION_TYPE;


EXTERN_C const IID IID_IPoolNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69e59018-f1ce-11d2-91aa-00c04fb6ee9d")
    IPoolNotify : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SendNotification( 
            /* [in] */ IPoolInfo __RPC_FAR *pPoolInfo,
            /* [in] */ SPNOTIFICATION_TYPE eType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPoolNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoolNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoolNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoolNotify __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendNotification )( 
            IPoolNotify __RPC_FAR * This,
            /* [in] */ IPoolInfo __RPC_FAR *pPoolInfo,
            /* [in] */ SPNOTIFICATION_TYPE eType);
        
        END_INTERFACE
    } IPoolNotifyVtbl;

    interface IPoolNotify
    {
        CONST_VTBL struct IPoolNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoolNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoolNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoolNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoolNotify_SendNotification(This,pPoolInfo,eType)	\
    (This)->lpVtbl -> SendNotification(This,pPoolInfo,eType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IPoolNotify_SendNotification_Proxy( 
    IPoolNotify __RPC_FAR * This,
    /* [in] */ IPoolInfo __RPC_FAR *pPoolInfo,
    /* [in] */ SPNOTIFICATION_TYPE eType);


void __RPC_STUB IPoolNotify_SendNotification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoolNotify_INTERFACE_DEFINED__ */


#ifndef __IPoolMngrInfo_INTERFACE_DEFINED__
#define __IPoolMngrInfo_INTERFACE_DEFINED__

/* interface IPoolMngrInfo */
/* [object][helpstring][version][uuid] */ 


EXTERN_C const IID IID_IPoolMngrInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07e78e52-be3e-11d2-91a2-00c04fb6ee9d")
    IPoolMngrInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE EnumPools( 
            /* [out] */ ULONG __RPC_FAR *pcPools,
            /* [out] */ IPoolInfo __RPC_FAR *__RPC_FAR *__RPC_FAR rgPoolInfo[  ]) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetPoolNotify( 
            /* [in] */ IPoolNotify __RPC_FAR *pPoolNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPoolMngrInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoolMngrInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoolMngrInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoolMngrInfo __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumPools )( 
            IPoolMngrInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcPools,
            /* [out] */ IPoolInfo __RPC_FAR *__RPC_FAR *__RPC_FAR rgPoolInfo[  ]);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPoolNotify )( 
            IPoolMngrInfo __RPC_FAR * This,
            /* [in] */ IPoolNotify __RPC_FAR *pPoolNotify);
        
        END_INTERFACE
    } IPoolMngrInfoVtbl;

    interface IPoolMngrInfo
    {
        CONST_VTBL struct IPoolMngrInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoolMngrInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoolMngrInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoolMngrInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoolMngrInfo_EnumPools(This,pcPools,rgPoolInfo)	\
    (This)->lpVtbl -> EnumPools(This,pcPools,rgPoolInfo)

#define IPoolMngrInfo_SetPoolNotify(This,pPoolNotify)	\
    (This)->lpVtbl -> SetPoolNotify(This,pPoolNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IPoolMngrInfo_EnumPools_Proxy( 
    IPoolMngrInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcPools,
    /* [out] */ IPoolInfo __RPC_FAR *__RPC_FAR *__RPC_FAR rgPoolInfo[  ]);


void __RPC_STUB IPoolMngrInfo_EnumPools_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPoolMngrInfo_SetPoolNotify_Proxy( 
    IPoolMngrInfo __RPC_FAR * This,
    /* [in] */ IPoolNotify __RPC_FAR *pPoolNotify);


void __RPC_STUB IPoolMngrInfo_SetPoolNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoolMngrInfo_INTERFACE_DEFINED__ */


#ifndef __IGetPool_INTERFACE_DEFINED__
#define __IGetPool_INTERFACE_DEFINED__

/* interface IGetPool */
/* [object][helpstring][version][uuid] */ 

typedef /* [public] */ 
enum __MIDL_IGetPool_0001
    {	NOT_POOLED	= 0,
	CAN_BEPOOLED	= 0x1,
	DRAWN_FROMPOOL	= 0x2,
	CREATED_FROMPOOL	= 0x4
    }	SPDPOSTATE;


EXTERN_C const IID IID_IGetPool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10c2eaa8-be3e-11d2-91a2-00c04fb6ee9d")
    IGetPool : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetPool( 
            /* [out] */ IPoolInfo __RPC_FAR *__RPC_FAR *pPoolInfo) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ DWORD __RPC_FAR *pdwState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetPoolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGetPool __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGetPool __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGetPool __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPool )( 
            IGetPool __RPC_FAR * This,
            /* [out] */ IPoolInfo __RPC_FAR *__RPC_FAR *pPoolInfo);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IGetPool __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwState);
        
        END_INTERFACE
    } IGetPoolVtbl;

    interface IGetPool
    {
        CONST_VTBL struct IGetPoolVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetPool_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGetPool_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGetPool_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGetPool_GetPool(This,pPoolInfo)	\
    (This)->lpVtbl -> GetPool(This,pPoolInfo)

#define IGetPool_GetState(This,pdwState)	\
    (This)->lpVtbl -> GetState(This,pdwState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IGetPool_GetPool_Proxy( 
    IGetPool __RPC_FAR * This,
    /* [out] */ IPoolInfo __RPC_FAR *__RPC_FAR *pPoolInfo);


void __RPC_STUB IGetPool_GetPool_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IGetPool_GetState_Proxy( 
    IGetPool __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwState);


void __RPC_STUB IGetPool_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGetPool_INTERFACE_DEFINED__ */


#ifndef __IUdlCacheMngr_INTERFACE_DEFINED__
#define __IUdlCacheMngr_INTERFACE_DEFINED__

/* interface IUdlCacheMngr */
/* [object][helpstring][version][uuid] */ 


EXTERN_C const IID IID_IUdlCacheMngr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7ee07400-12ce-11d3-b5b8-00a0c9081c1d")
    IUdlCacheMngr : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetStringInfoFromFileName( 
            /* [in] */ LPCOLESTR wszFileName,
            /* [out] */ LPOLESTR __RPC_FAR *pwszInitString,
            /* [out] */ DWORD __RPC_FAR *pdwTickCount) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetUdlGlobalTickCount( 
            /* [out] */ DWORD __RPC_FAR *pdwGlobalTickCount) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetUdlGlobalTickCount( 
            /* [in] */ DWORD dwGlobalTickCount) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetUdlCacheSize( 
            /* [in] */ DWORD dwCacheSize) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetCurrentUdlCacheSize( 
            /* [out] */ DWORD __RPC_FAR *pdwCacheSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUdlCacheMngrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUdlCacheMngr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUdlCacheMngr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUdlCacheMngr __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStringInfoFromFileName )( 
            IUdlCacheMngr __RPC_FAR * This,
            /* [in] */ LPCOLESTR wszFileName,
            /* [out] */ LPOLESTR __RPC_FAR *pwszInitString,
            /* [out] */ DWORD __RPC_FAR *pdwTickCount);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUdlGlobalTickCount )( 
            IUdlCacheMngr __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwGlobalTickCount);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUdlGlobalTickCount )( 
            IUdlCacheMngr __RPC_FAR * This,
            /* [in] */ DWORD dwGlobalTickCount);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUdlCacheSize )( 
            IUdlCacheMngr __RPC_FAR * This,
            /* [in] */ DWORD dwCacheSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentUdlCacheSize )( 
            IUdlCacheMngr __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwCacheSize);
        
        END_INTERFACE
    } IUdlCacheMngrVtbl;

    interface IUdlCacheMngr
    {
        CONST_VTBL struct IUdlCacheMngrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUdlCacheMngr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUdlCacheMngr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUdlCacheMngr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUdlCacheMngr_GetStringInfoFromFileName(This,wszFileName,pwszInitString,pdwTickCount)	\
    (This)->lpVtbl -> GetStringInfoFromFileName(This,wszFileName,pwszInitString,pdwTickCount)

#define IUdlCacheMngr_GetUdlGlobalTickCount(This,pdwGlobalTickCount)	\
    (This)->lpVtbl -> GetUdlGlobalTickCount(This,pdwGlobalTickCount)

#define IUdlCacheMngr_SetUdlGlobalTickCount(This,dwGlobalTickCount)	\
    (This)->lpVtbl -> SetUdlGlobalTickCount(This,dwGlobalTickCount)

#define IUdlCacheMngr_SetUdlCacheSize(This,dwCacheSize)	\
    (This)->lpVtbl -> SetUdlCacheSize(This,dwCacheSize)

#define IUdlCacheMngr_GetCurrentUdlCacheSize(This,pdwCacheSize)	\
    (This)->lpVtbl -> GetCurrentUdlCacheSize(This,pdwCacheSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IUdlCacheMngr_GetStringInfoFromFileName_Proxy( 
    IUdlCacheMngr __RPC_FAR * This,
    /* [in] */ LPCOLESTR wszFileName,
    /* [out] */ LPOLESTR __RPC_FAR *pwszInitString,
    /* [out] */ DWORD __RPC_FAR *pdwTickCount);


void __RPC_STUB IUdlCacheMngr_GetStringInfoFromFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IUdlCacheMngr_GetUdlGlobalTickCount_Proxy( 
    IUdlCacheMngr __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwGlobalTickCount);


void __RPC_STUB IUdlCacheMngr_GetUdlGlobalTickCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IUdlCacheMngr_SetUdlGlobalTickCount_Proxy( 
    IUdlCacheMngr __RPC_FAR * This,
    /* [in] */ DWORD dwGlobalTickCount);


void __RPC_STUB IUdlCacheMngr_SetUdlGlobalTickCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IUdlCacheMngr_SetUdlCacheSize_Proxy( 
    IUdlCacheMngr __RPC_FAR * This,
    /* [in] */ DWORD dwCacheSize);


void __RPC_STUB IUdlCacheMngr_SetUdlCacheSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IUdlCacheMngr_GetCurrentUdlCacheSize_Proxy( 
    IUdlCacheMngr __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwCacheSize);


void __RPC_STUB IUdlCacheMngr_GetCurrentUdlCacheSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUdlCacheMngr_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


