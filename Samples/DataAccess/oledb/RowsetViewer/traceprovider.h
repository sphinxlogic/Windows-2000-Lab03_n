
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.02.0235 */
/* at Wed Jul 21 14:20:33 1999
 */
/* Compiler settings for traceprovider.idl:
    Oicf (OptLev=i2), W1, Zp2, env=Win32 (32b run), ms_ext, c_ext
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

#ifndef __traceprovider_h__
#define __traceprovider_h__

/* Forward Declarations */ 

#ifndef __IDBTraceControlEnumerator_FWD_DEFINED__
#define __IDBTraceControlEnumerator_FWD_DEFINED__
typedef interface IDBTraceControlEnumerator IDBTraceControlEnumerator;
#endif 	/* __IDBTraceControlEnumerator_FWD_DEFINED__ */


#ifndef __IDBTraceControlProviders_FWD_DEFINED__
#define __IDBTraceControlProviders_FWD_DEFINED__
typedef interface IDBTraceControlProviders IDBTraceControlProviders;
#endif 	/* __IDBTraceControlProviders_FWD_DEFINED__ */


#ifndef __IDBTraceControlReceivers_FWD_DEFINED__
#define __IDBTraceControlReceivers_FWD_DEFINED__
typedef interface IDBTraceControlReceivers IDBTraceControlReceivers;
#endif 	/* __IDBTraceControlReceivers_FWD_DEFINED__ */


#ifndef __IDBTraceControlFilters_FWD_DEFINED__
#define __IDBTraceControlFilters_FWD_DEFINED__
typedef interface IDBTraceControlFilters IDBTraceControlFilters;
#endif 	/* __IDBTraceControlFilters_FWD_DEFINED__ */


#ifndef __IDBTraceReceiver_FWD_DEFINED__
#define __IDBTraceReceiver_FWD_DEFINED__
typedef interface IDBTraceReceiver IDBTraceReceiver;
#endif 	/* __IDBTraceReceiver_FWD_DEFINED__ */


#ifndef __IDBTraceNotify_FWD_DEFINED__
#define __IDBTraceNotify_FWD_DEFINED__
typedef interface IDBTraceNotify IDBTraceNotify;
#endif 	/* __IDBTraceNotify_FWD_DEFINED__ */


#ifndef __IDBTraceEnumParameters_FWD_DEFINED__
#define __IDBTraceEnumParameters_FWD_DEFINED__
typedef interface IDBTraceEnumParameters IDBTraceEnumParameters;
#endif 	/* __IDBTraceEnumParameters_FWD_DEFINED__ */


#ifndef __IDBTracePackage_FWD_DEFINED__
#define __IDBTracePackage_FWD_DEFINED__
typedef interface IDBTracePackage IDBTracePackage;
#endif 	/* __IDBTracePackage_FWD_DEFINED__ */


#ifndef __IDBTraceParameter_FWD_DEFINED__
#define __IDBTraceParameter_FWD_DEFINED__
typedef interface IDBTraceParameter IDBTraceParameter;
#endif 	/* __IDBTraceParameter_FWD_DEFINED__ */


#ifndef __IDBTraceInterpreter_FWD_DEFINED__
#define __IDBTraceInterpreter_FWD_DEFINED__
typedef interface IDBTraceInterpreter IDBTraceInterpreter;
#endif 	/* __IDBTraceInterpreter_FWD_DEFINED__ */


#ifndef __IProviderEnum_FWD_DEFINED__
#define __IProviderEnum_FWD_DEFINED__
typedef interface IProviderEnum IProviderEnum;
#endif 	/* __IProviderEnum_FWD_DEFINED__ */


#ifndef __TraceControl_FWD_DEFINED__
#define __TraceControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TraceControl TraceControl;
#else
typedef struct TraceControl TraceControl;
#endif /* __cplusplus */

#endif 	/* __TraceControl_FWD_DEFINED__ */


#ifndef __Tracer_FWD_DEFINED__
#define __Tracer_FWD_DEFINED__

#ifdef __cplusplus
typedef class Tracer Tracer;
#else
typedef struct Tracer Tracer;
#endif /* __cplusplus */

#endif 	/* __Tracer_FWD_DEFINED__ */


#ifndef __TraceReceiver_FWD_DEFINED__
#define __TraceReceiver_FWD_DEFINED__

#ifdef __cplusplus
typedef class TraceReceiver TraceReceiver;
#else
typedef struct TraceReceiver TraceReceiver;
#endif /* __cplusplus */

#endif 	/* __TraceReceiver_FWD_DEFINED__ */


#ifndef __TraceInterpreter_FWD_DEFINED__
#define __TraceInterpreter_FWD_DEFINED__

#ifdef __cplusplus
typedef class TraceInterpreter TraceInterpreter;
#else
typedef struct TraceInterpreter TraceInterpreter;
#endif /* __cplusplus */

#endif 	/* __TraceInterpreter_FWD_DEFINED__ */


#ifndef __ProviderEnum_FWD_DEFINED__
#define __ProviderEnum_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProviderEnum ProviderEnum;
#else
typedef struct ProviderEnum ProviderEnum;
#endif /* __cplusplus */

#endif 	/* __ProviderEnum_FWD_DEFINED__ */


/* header files for imported files */
#include "oledb.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_traceprovider_0000 */
/* [local] */ 

typedef struct tagDBTRACEINFO
    {
    DOUBLE perfTime;
    HRESULT hResult;
    DBORDINAL dwProviderID;
    DBORDINAL dwCotypeID;
    DBORDINAL dwInterfaceID;
    DBORDINAL dwMethodID;
    DBORDINAL dwUniqueID;
    DWORD dwInterpreterVersion;
    DWORD dwProcessID;
    DWORD dwThreadID;
    DBCOUNTITEM cbParameterCount;
    DWORD dwTraceLevel;
    DBLENGTH cbPackageSize;
    DWORD dwPackageType;
    DWORD dwIntAddr;
    DWORD dwCotypeAddr;
    }	DBTRACEINFO;

typedef struct tagDBTRACEPARAMINFO
    {
    DWORD argValue;
    DBORDINAL dwInterfaceID;
    DBORDINAL dwParamIndex;
    DBORDINAL dwTypeID;
    DBLENGTH cbDataSize;
    BYTE bInputOrOutput;
    BYTE fIsConst;
    BYTE fHasBrackets;
    LPWSTR type;
    BYTE bLevelsOfIndirection;
    LPWSTR indexOfArraySize;
    }	DBTRACEPARAMINFO;













extern RPC_IF_HANDLE __MIDL_itf_traceprovider_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_traceprovider_0000_v0_0_s_ifspec;

#ifndef __IDBTraceControlEnumerator_INTERFACE_DEFINED__
#define __IDBTraceControlEnumerator_INTERFACE_DEFINED__

/* interface IDBTraceControlEnumerator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceControlEnumerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d5f0bc77-3bb7-11d3-b310-00c04f611c75")
    IDBTraceControlEnumerator : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [out] */ BSTR __RPC_FAR *pbstrName,
            /* [out] */ BSTR __RPC_FAR *pbstrClsid,
            /* [out] */ BSTR __RPC_FAR *pbstrState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ DWORD dwPositions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceControlEnumeratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceControlEnumerator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceControlEnumerator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrName,
            /* [out] */ BSTR __RPC_FAR *pbstrClsid,
            /* [out] */ BSTR __RPC_FAR *pbstrState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IDBTraceControlEnumerator __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IDBTraceControlEnumerator __RPC_FAR * This,
            /* [in] */ DWORD dwPositions);
        
        END_INTERFACE
    } IDBTraceControlEnumeratorVtbl;

    interface IDBTraceControlEnumerator
    {
        CONST_VTBL struct IDBTraceControlEnumeratorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceControlEnumerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceControlEnumerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceControlEnumerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceControlEnumerator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDBTraceControlEnumerator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDBTraceControlEnumerator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDBTraceControlEnumerator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDBTraceControlEnumerator_Next(This,pbstrName,pbstrClsid,pbstrState)	\
    (This)->lpVtbl -> Next(This,pbstrName,pbstrClsid,pbstrState)

#define IDBTraceControlEnumerator_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IDBTraceControlEnumerator_Skip(This,dwPositions)	\
    (This)->lpVtbl -> Skip(This,dwPositions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlEnumerator_Next_Proxy( 
    IDBTraceControlEnumerator __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrName,
    /* [out] */ BSTR __RPC_FAR *pbstrClsid,
    /* [out] */ BSTR __RPC_FAR *pbstrState);


void __RPC_STUB IDBTraceControlEnumerator_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlEnumerator_Reset_Proxy( 
    IDBTraceControlEnumerator __RPC_FAR * This);


void __RPC_STUB IDBTraceControlEnumerator_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlEnumerator_Skip_Proxy( 
    IDBTraceControlEnumerator __RPC_FAR * This,
    /* [in] */ DWORD dwPositions);


void __RPC_STUB IDBTraceControlEnumerator_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceControlEnumerator_INTERFACE_DEFINED__ */


#ifndef __IDBTraceControlProviders_INTERFACE_DEFINED__
#define __IDBTraceControlProviders_INTERFACE_DEFINED__

/* interface IDBTraceControlProviders */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceControlProviders;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82de2-2bdb-11d2-90e1-00805fc752eb")
    IDBTraceControlProviders : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Enable( 
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disable( 
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEnumerator( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppiDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceControlProvidersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceControlProviders __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceControlProviders __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Enable )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disable )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnumerator )( 
            IDBTraceControlProviders __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppiDisp);
        
        END_INTERFACE
    } IDBTraceControlProvidersVtbl;

    interface IDBTraceControlProviders
    {
        CONST_VTBL struct IDBTraceControlProvidersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceControlProviders_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceControlProviders_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceControlProviders_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceControlProviders_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDBTraceControlProviders_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDBTraceControlProviders_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDBTraceControlProviders_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDBTraceControlProviders_Enable(This,bstrCLSID,lFlags)	\
    (This)->lpVtbl -> Enable(This,bstrCLSID,lFlags)

#define IDBTraceControlProviders_Disable(This,bstrCLSID,lFlags)	\
    (This)->lpVtbl -> Disable(This,bstrCLSID,lFlags)

#define IDBTraceControlProviders_GetEnumerator(This,ppiDisp)	\
    (This)->lpVtbl -> GetEnumerator(This,ppiDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlProviders_Enable_Proxy( 
    IDBTraceControlProviders __RPC_FAR * This,
    /* [in] */ BSTR bstrCLSID,
    /* [in] */ long lFlags);


void __RPC_STUB IDBTraceControlProviders_Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlProviders_Disable_Proxy( 
    IDBTraceControlProviders __RPC_FAR * This,
    /* [in] */ BSTR bstrCLSID,
    /* [in] */ long lFlags);


void __RPC_STUB IDBTraceControlProviders_Disable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlProviders_GetEnumerator_Proxy( 
    IDBTraceControlProviders __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppiDisp);


void __RPC_STUB IDBTraceControlProviders_GetEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceControlProviders_INTERFACE_DEFINED__ */


#ifndef __IDBTraceControlReceivers_INTERFACE_DEFINED__
#define __IDBTraceControlReceivers_INTERFACE_DEFINED__

/* interface IDBTraceControlReceivers */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceControlReceivers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ec866301-3bb7-11d3-b310-00c04f611c75")
    IDBTraceControlReceivers : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Enable( 
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disable( 
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEnumerator( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppiDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UsePrivate( 
            /* [in] */ IDispatch __RPC_FAR *piDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceControlReceiversVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceControlReceivers __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceControlReceivers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Enable )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disable )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ BSTR bstrCLSID,
            /* [in] */ long lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnumerator )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppiDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UsePrivate )( 
            IDBTraceControlReceivers __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *piDisp);
        
        END_INTERFACE
    } IDBTraceControlReceiversVtbl;

    interface IDBTraceControlReceivers
    {
        CONST_VTBL struct IDBTraceControlReceiversVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceControlReceivers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceControlReceivers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceControlReceivers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceControlReceivers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDBTraceControlReceivers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDBTraceControlReceivers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDBTraceControlReceivers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDBTraceControlReceivers_Enable(This,bstrCLSID,lFlags)	\
    (This)->lpVtbl -> Enable(This,bstrCLSID,lFlags)

#define IDBTraceControlReceivers_Disable(This,bstrCLSID,lFlags)	\
    (This)->lpVtbl -> Disable(This,bstrCLSID,lFlags)

#define IDBTraceControlReceivers_GetEnumerator(This,ppiDisp)	\
    (This)->lpVtbl -> GetEnumerator(This,ppiDisp)

#define IDBTraceControlReceivers_UsePrivate(This,piDisp)	\
    (This)->lpVtbl -> UsePrivate(This,piDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlReceivers_Enable_Proxy( 
    IDBTraceControlReceivers __RPC_FAR * This,
    /* [in] */ BSTR bstrCLSID,
    /* [in] */ long lFlags);


void __RPC_STUB IDBTraceControlReceivers_Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlReceivers_Disable_Proxy( 
    IDBTraceControlReceivers __RPC_FAR * This,
    /* [in] */ BSTR bstrCLSID,
    /* [in] */ long lFlags);


void __RPC_STUB IDBTraceControlReceivers_Disable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlReceivers_GetEnumerator_Proxy( 
    IDBTraceControlReceivers __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppiDisp);


void __RPC_STUB IDBTraceControlReceivers_GetEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlReceivers_UsePrivate_Proxy( 
    IDBTraceControlReceivers __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *piDisp);


void __RPC_STUB IDBTraceControlReceivers_UsePrivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceControlReceivers_INTERFACE_DEFINED__ */


#ifndef __IDBTraceControlFilters_INTERFACE_DEFINED__
#define __IDBTraceControlFilters_INTERFACE_DEFINED__

/* interface IDBTraceControlFilters */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceControlFilters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f7cda2bf-3bb7-11d3-b310-00c04f611c75")
    IDBTraceControlFilters : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TraceOLEDBServices( 
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TraceIUnknown( 
            /* [in] */ long lFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUnknownTraceStatus( 
            /* [out] */ long __RPC_FAR *plStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OLEDBServicesTraceStatus( 
            /* [out] */ long __RPC_FAR *plStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceControlFiltersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceControlFilters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceControlFilters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TraceOLEDBServices )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [in] */ long lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TraceIUnknown )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [in] */ long lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IUnknownTraceStatus )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OLEDBServicesTraceStatus )( 
            IDBTraceControlFilters __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plStatus);
        
        END_INTERFACE
    } IDBTraceControlFiltersVtbl;

    interface IDBTraceControlFilters
    {
        CONST_VTBL struct IDBTraceControlFiltersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceControlFilters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceControlFilters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceControlFilters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceControlFilters_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDBTraceControlFilters_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDBTraceControlFilters_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDBTraceControlFilters_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDBTraceControlFilters_TraceOLEDBServices(This,lFlags)	\
    (This)->lpVtbl -> TraceOLEDBServices(This,lFlags)

#define IDBTraceControlFilters_TraceIUnknown(This,lFlags)	\
    (This)->lpVtbl -> TraceIUnknown(This,lFlags)

#define IDBTraceControlFilters_IUnknownTraceStatus(This,plStatus)	\
    (This)->lpVtbl -> IUnknownTraceStatus(This,plStatus)

#define IDBTraceControlFilters_OLEDBServicesTraceStatus(This,plStatus)	\
    (This)->lpVtbl -> OLEDBServicesTraceStatus(This,plStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlFilters_TraceOLEDBServices_Proxy( 
    IDBTraceControlFilters __RPC_FAR * This,
    /* [in] */ long lFlags);


void __RPC_STUB IDBTraceControlFilters_TraceOLEDBServices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlFilters_TraceIUnknown_Proxy( 
    IDBTraceControlFilters __RPC_FAR * This,
    /* [in] */ long lFlags);


void __RPC_STUB IDBTraceControlFilters_TraceIUnknown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlFilters_IUnknownTraceStatus_Proxy( 
    IDBTraceControlFilters __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plStatus);


void __RPC_STUB IDBTraceControlFilters_IUnknownTraceStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceControlFilters_OLEDBServicesTraceStatus_Proxy( 
    IDBTraceControlFilters __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plStatus);


void __RPC_STUB IDBTraceControlFilters_OLEDBServicesTraceStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceControlFilters_INTERFACE_DEFINED__ */


#ifndef __IDBTraceReceiver_INTERFACE_DEFINED__
#define __IDBTraceReceiver_INTERFACE_DEFINED__

/* interface IDBTraceReceiver */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceReceiver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82de3-2bdb-11d2-90e1-00805fc752eb")
    IDBTraceReceiver : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ LPUNKNOWN pUnknown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uninitialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            /* [retval][out] */ LPVARIANT pvCLSIDString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceReceiverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceReceiver __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceReceiver __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [in] */ LPUNKNOWN pUnknown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialize )( 
            IDBTraceReceiver __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IDBTraceReceiver __RPC_FAR * This,
            /* [retval][out] */ LPVARIANT pvCLSIDString);
        
        END_INTERFACE
    } IDBTraceReceiverVtbl;

    interface IDBTraceReceiver
    {
        CONST_VTBL struct IDBTraceReceiverVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceReceiver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceReceiver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceReceiver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceReceiver_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDBTraceReceiver_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDBTraceReceiver_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDBTraceReceiver_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDBTraceReceiver_Initialize(This,pUnknown)	\
    (This)->lpVtbl -> Initialize(This,pUnknown)

#define IDBTraceReceiver_Uninitialize(This)	\
    (This)->lpVtbl -> Uninitialize(This)

#define IDBTraceReceiver_GetCLSID(This,pvCLSIDString)	\
    (This)->lpVtbl -> GetCLSID(This,pvCLSIDString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceReceiver_Initialize_Proxy( 
    IDBTraceReceiver __RPC_FAR * This,
    /* [in] */ LPUNKNOWN pUnknown);


void __RPC_STUB IDBTraceReceiver_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceReceiver_Uninitialize_Proxy( 
    IDBTraceReceiver __RPC_FAR * This);


void __RPC_STUB IDBTraceReceiver_Uninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceReceiver_GetCLSID_Proxy( 
    IDBTraceReceiver __RPC_FAR * This,
    /* [retval][out] */ LPVARIANT pvCLSIDString);


void __RPC_STUB IDBTraceReceiver_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceReceiver_INTERFACE_DEFINED__ */


#ifndef __IDBTraceNotify_INTERFACE_DEFINED__
#define __IDBTraceNotify_INTERFACE_DEFINED__

/* interface IDBTraceNotify */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82de4-2bdb-11d2-90e1-00805fc752eb")
    IDBTraceNotify : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPackageReady( 
            /* [in] */ DBLENGTH cbPackageDataLen,
            /* [size_is][in] */ BYTE __RPC_FAR *pPackageData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceNotify __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPackageReady )( 
            IDBTraceNotify __RPC_FAR * This,
            /* [in] */ DBLENGTH cbPackageDataLen,
            /* [size_is][in] */ BYTE __RPC_FAR *pPackageData);
        
        END_INTERFACE
    } IDBTraceNotifyVtbl;

    interface IDBTraceNotify
    {
        CONST_VTBL struct IDBTraceNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceNotify_OnPackageReady(This,cbPackageDataLen,pPackageData)	\
    (This)->lpVtbl -> OnPackageReady(This,cbPackageDataLen,pPackageData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceNotify_OnPackageReady_Proxy( 
    IDBTraceNotify __RPC_FAR * This,
    /* [in] */ DBLENGTH cbPackageDataLen,
    /* [size_is][in] */ BYTE __RPC_FAR *pPackageData);


void __RPC_STUB IDBTraceNotify_OnPackageReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceNotify_INTERFACE_DEFINED__ */


#ifndef __IDBTraceEnumParameters_INTERFACE_DEFINED__
#define __IDBTraceEnumParameters_INTERFACE_DEFINED__

/* interface IDBTraceEnumParameters */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceEnumParameters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82ded-2bdb-11d2-90e1-00805fc752eb")
    IDBTraceEnumParameters : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cParameters,
            /* [size_is][out] */ IDBTraceParameter __RPC_FAR *__RPC_FAR *rgpParameters,
            /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cParameters) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceEnumParametersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceEnumParameters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceEnumParameters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceEnumParameters __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IDBTraceEnumParameters __RPC_FAR * This,
            /* [in] */ ULONG cParameters,
            /* [size_is][out] */ IDBTraceParameter __RPC_FAR *__RPC_FAR *rgpParameters,
            /* [out] */ ULONG __RPC_FAR *pcFetched);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IDBTraceEnumParameters __RPC_FAR * This,
            /* [in] */ ULONG cParameters);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IDBTraceEnumParameters __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IDBTraceEnumParameters __RPC_FAR * This,
            /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IDBTraceEnumParametersVtbl;

    interface IDBTraceEnumParameters
    {
        CONST_VTBL struct IDBTraceEnumParametersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceEnumParameters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceEnumParameters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceEnumParameters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceEnumParameters_Next(This,cParameters,rgpParameters,pcFetched)	\
    (This)->lpVtbl -> Next(This,cParameters,rgpParameters,pcFetched)

#define IDBTraceEnumParameters_Skip(This,cParameters)	\
    (This)->lpVtbl -> Skip(This,cParameters)

#define IDBTraceEnumParameters_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IDBTraceEnumParameters_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceEnumParameters_Next_Proxy( 
    IDBTraceEnumParameters __RPC_FAR * This,
    /* [in] */ ULONG cParameters,
    /* [size_is][out] */ IDBTraceParameter __RPC_FAR *__RPC_FAR *rgpParameters,
    /* [out] */ ULONG __RPC_FAR *pcFetched);


void __RPC_STUB IDBTraceEnumParameters_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceEnumParameters_Skip_Proxy( 
    IDBTraceEnumParameters __RPC_FAR * This,
    /* [in] */ ULONG cParameters);


void __RPC_STUB IDBTraceEnumParameters_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceEnumParameters_Reset_Proxy( 
    IDBTraceEnumParameters __RPC_FAR * This);


void __RPC_STUB IDBTraceEnumParameters_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceEnumParameters_Clone_Proxy( 
    IDBTraceEnumParameters __RPC_FAR * This,
    /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IDBTraceEnumParameters_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceEnumParameters_INTERFACE_DEFINED__ */


#ifndef __IDBTracePackage_INTERFACE_DEFINED__
#define __IDBTracePackage_INTERFACE_DEFINED__

/* interface IDBTracePackage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBTracePackage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82de5-2bdb-11d2-90e1-00805fc752eb")
    IDBTracePackage : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Attach( 
            /* [in] */ DBLENGTH cbPackageDataLen,
            /* [size_is][in] */ BYTE __RPC_FAR *pPackageData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Detach( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPackageContext( 
            /* [in] */ DBTRACEINFO __RPC_FAR *pTraceInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumParameters( 
            /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParameterAt( 
            /* [in] */ DBORDINAL iParameter,
            /* [out] */ IDBTraceParameter __RPC_FAR *__RPC_FAR *ppIParameter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Persist( 
            /* [in] */ IStream __RPC_FAR *pIStream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NameFromID( 
            /* [in] */ DBORDINAL dwInfoID,
            /* [out] */ BSTR __RPC_FAR *bstrName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetResultString( 
            /* [in] */ DBORDINAL dwMethodID,
            /* [in] */ HRESULT hr,
            /* [out] */ BSTR __RPC_FAR *bstrResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTracePackageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTracePackage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTracePackage __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Attach )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ DBLENGTH cbPackageDataLen,
            /* [size_is][in] */ BYTE __RPC_FAR *pPackageData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Detach )( 
            IDBTracePackage __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPackageContext )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ DBTRACEINFO __RPC_FAR *pTraceInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumParameters )( 
            IDBTracePackage __RPC_FAR * This,
            /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParameterAt )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ DBORDINAL iParameter,
            /* [out] */ IDBTraceParameter __RPC_FAR *__RPC_FAR *ppIParameter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Persist )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ IStream __RPC_FAR *pIStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NameFromID )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ DBORDINAL dwInfoID,
            /* [out] */ BSTR __RPC_FAR *bstrName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetResultString )( 
            IDBTracePackage __RPC_FAR * This,
            /* [in] */ DBORDINAL dwMethodID,
            /* [in] */ HRESULT hr,
            /* [out] */ BSTR __RPC_FAR *bstrResult);
        
        END_INTERFACE
    } IDBTracePackageVtbl;

    interface IDBTracePackage
    {
        CONST_VTBL struct IDBTracePackageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTracePackage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTracePackage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTracePackage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTracePackage_Attach(This,cbPackageDataLen,pPackageData)	\
    (This)->lpVtbl -> Attach(This,cbPackageDataLen,pPackageData)

#define IDBTracePackage_Detach(This)	\
    (This)->lpVtbl -> Detach(This)

#define IDBTracePackage_GetPackageContext(This,pTraceInfo)	\
    (This)->lpVtbl -> GetPackageContext(This,pTraceInfo)

#define IDBTracePackage_EnumParameters(This,ppEnum)	\
    (This)->lpVtbl -> EnumParameters(This,ppEnum)

#define IDBTracePackage_GetParameterAt(This,iParameter,ppIParameter)	\
    (This)->lpVtbl -> GetParameterAt(This,iParameter,ppIParameter)

#define IDBTracePackage_Persist(This,pIStream)	\
    (This)->lpVtbl -> Persist(This,pIStream)

#define IDBTracePackage_NameFromID(This,dwInfoID,bstrName)	\
    (This)->lpVtbl -> NameFromID(This,dwInfoID,bstrName)

#define IDBTracePackage_GetResultString(This,dwMethodID,hr,bstrResult)	\
    (This)->lpVtbl -> GetResultString(This,dwMethodID,hr,bstrResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_Attach_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [in] */ DBLENGTH cbPackageDataLen,
    /* [size_is][in] */ BYTE __RPC_FAR *pPackageData);


void __RPC_STUB IDBTracePackage_Attach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_Detach_Proxy( 
    IDBTracePackage __RPC_FAR * This);


void __RPC_STUB IDBTracePackage_Detach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_GetPackageContext_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [in] */ DBTRACEINFO __RPC_FAR *pTraceInfo);


void __RPC_STUB IDBTracePackage_GetPackageContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_EnumParameters_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IDBTracePackage_EnumParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_GetParameterAt_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [in] */ DBORDINAL iParameter,
    /* [out] */ IDBTraceParameter __RPC_FAR *__RPC_FAR *ppIParameter);


void __RPC_STUB IDBTracePackage_GetParameterAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_Persist_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [in] */ IStream __RPC_FAR *pIStream);


void __RPC_STUB IDBTracePackage_Persist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_NameFromID_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [in] */ DBORDINAL dwInfoID,
    /* [out] */ BSTR __RPC_FAR *bstrName);


void __RPC_STUB IDBTracePackage_NameFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTracePackage_GetResultString_Proxy( 
    IDBTracePackage __RPC_FAR * This,
    /* [in] */ DBORDINAL dwMethodID,
    /* [in] */ HRESULT hr,
    /* [out] */ BSTR __RPC_FAR *bstrResult);


void __RPC_STUB IDBTracePackage_GetResultString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTracePackage_INTERFACE_DEFINED__ */


#ifndef __IDBTraceParameter_INTERFACE_DEFINED__
#define __IDBTraceParameter_INTERFACE_DEFINED__

/* interface IDBTraceParameter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceParameter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82de6-2bdb-11d2-90e1-00805fc752eb")
    IDBTraceParameter : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParameterContext( 
            /* [in] */ DBTRACEPARAMINFO __RPC_FAR *pTraceParamInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumStructElements( 
            /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsStruct( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ BSTR __RPC_FAR *bstrName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLinkedName( 
            /* [in] */ DBORDINAL paramNumber,
            /* [out] */ BSTR __RPC_FAR *bstrName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceParameterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceParameter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceParameter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceParameter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParameterContext )( 
            IDBTraceParameter __RPC_FAR * This,
            /* [in] */ DBTRACEPARAMINFO __RPC_FAR *pTraceParamInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumStructElements )( 
            IDBTraceParameter __RPC_FAR * This,
            /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsStruct )( 
            IDBTraceParameter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IDBTraceParameter __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *bstrName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLinkedName )( 
            IDBTraceParameter __RPC_FAR * This,
            /* [in] */ DBORDINAL paramNumber,
            /* [out] */ BSTR __RPC_FAR *bstrName);
        
        END_INTERFACE
    } IDBTraceParameterVtbl;

    interface IDBTraceParameter
    {
        CONST_VTBL struct IDBTraceParameterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceParameter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceParameter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceParameter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceParameter_GetParameterContext(This,pTraceParamInfo)	\
    (This)->lpVtbl -> GetParameterContext(This,pTraceParamInfo)

#define IDBTraceParameter_EnumStructElements(This,ppEnum)	\
    (This)->lpVtbl -> EnumStructElements(This,ppEnum)

#define IDBTraceParameter_IsStruct(This)	\
    (This)->lpVtbl -> IsStruct(This)

#define IDBTraceParameter_GetName(This,bstrName)	\
    (This)->lpVtbl -> GetName(This,bstrName)

#define IDBTraceParameter_GetLinkedName(This,paramNumber,bstrName)	\
    (This)->lpVtbl -> GetLinkedName(This,paramNumber,bstrName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceParameter_GetParameterContext_Proxy( 
    IDBTraceParameter __RPC_FAR * This,
    /* [in] */ DBTRACEPARAMINFO __RPC_FAR *pTraceParamInfo);


void __RPC_STUB IDBTraceParameter_GetParameterContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceParameter_EnumStructElements_Proxy( 
    IDBTraceParameter __RPC_FAR * This,
    /* [out] */ IDBTraceEnumParameters __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IDBTraceParameter_EnumStructElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceParameter_IsStruct_Proxy( 
    IDBTraceParameter __RPC_FAR * This);


void __RPC_STUB IDBTraceParameter_IsStruct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceParameter_GetName_Proxy( 
    IDBTraceParameter __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *bstrName);


void __RPC_STUB IDBTraceParameter_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceParameter_GetLinkedName_Proxy( 
    IDBTraceParameter __RPC_FAR * This,
    /* [in] */ DBORDINAL paramNumber,
    /* [out] */ BSTR __RPC_FAR *bstrName);


void __RPC_STUB IDBTraceParameter_GetLinkedName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceParameter_INTERFACE_DEFINED__ */


#ifndef __IDBTraceInterpreter_INTERFACE_DEFINED__
#define __IDBTraceInterpreter_INTERFACE_DEFINED__

/* interface IDBTraceInterpreter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBTraceInterpreter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82de7-2bdb-11d2-90e1-00805fc752eb")
    IDBTraceInterpreter : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NameFromID( 
            /* [in] */ DWORD dwProcessID,
            /* [in] */ DWORD dwThreadID,
            /* [in] */ DBORDINAL dwInfoID,
            /* [out] */ BSTR __RPC_FAR *bstrName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubItemCount( 
            /* [in] */ DBORDINAL dwInfoID,
            /* [out] */ DBCOUNTITEM __RPC_FAR *pdwCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateNewPackage( 
            /* [out] */ IDBTracePackage __RPC_FAR *__RPC_FAR *ppIDBTracePackage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEnumString( 
            /* [in] */ LONG lEnumTypeID,
            /* [in] */ LONG lEnumNumericalValue,
            /* [out] */ BSTR __RPC_FAR *pbstrEnumString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBTraceInterpreterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBTraceInterpreter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBTraceInterpreter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBTraceInterpreter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NameFromID )( 
            IDBTraceInterpreter __RPC_FAR * This,
            /* [in] */ DWORD dwProcessID,
            /* [in] */ DWORD dwThreadID,
            /* [in] */ DBORDINAL dwInfoID,
            /* [out] */ BSTR __RPC_FAR *bstrName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubItemCount )( 
            IDBTraceInterpreter __RPC_FAR * This,
            /* [in] */ DBORDINAL dwInfoID,
            /* [out] */ DBCOUNTITEM __RPC_FAR *pdwCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateNewPackage )( 
            IDBTraceInterpreter __RPC_FAR * This,
            /* [out] */ IDBTracePackage __RPC_FAR *__RPC_FAR *ppIDBTracePackage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnumString )( 
            IDBTraceInterpreter __RPC_FAR * This,
            /* [in] */ LONG lEnumTypeID,
            /* [in] */ LONG lEnumNumericalValue,
            /* [out] */ BSTR __RPC_FAR *pbstrEnumString);
        
        END_INTERFACE
    } IDBTraceInterpreterVtbl;

    interface IDBTraceInterpreter
    {
        CONST_VTBL struct IDBTraceInterpreterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBTraceInterpreter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBTraceInterpreter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBTraceInterpreter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBTraceInterpreter_NameFromID(This,dwProcessID,dwThreadID,dwInfoID,bstrName)	\
    (This)->lpVtbl -> NameFromID(This,dwProcessID,dwThreadID,dwInfoID,bstrName)

#define IDBTraceInterpreter_SubItemCount(This,dwInfoID,pdwCount)	\
    (This)->lpVtbl -> SubItemCount(This,dwInfoID,pdwCount)

#define IDBTraceInterpreter_CreateNewPackage(This,ppIDBTracePackage)	\
    (This)->lpVtbl -> CreateNewPackage(This,ppIDBTracePackage)

#define IDBTraceInterpreter_GetEnumString(This,lEnumTypeID,lEnumNumericalValue,pbstrEnumString)	\
    (This)->lpVtbl -> GetEnumString(This,lEnumTypeID,lEnumNumericalValue,pbstrEnumString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceInterpreter_NameFromID_Proxy( 
    IDBTraceInterpreter __RPC_FAR * This,
    /* [in] */ DWORD dwProcessID,
    /* [in] */ DWORD dwThreadID,
    /* [in] */ DBORDINAL dwInfoID,
    /* [out] */ BSTR __RPC_FAR *bstrName);


void __RPC_STUB IDBTraceInterpreter_NameFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceInterpreter_SubItemCount_Proxy( 
    IDBTraceInterpreter __RPC_FAR * This,
    /* [in] */ DBORDINAL dwInfoID,
    /* [out] */ DBCOUNTITEM __RPC_FAR *pdwCount);


void __RPC_STUB IDBTraceInterpreter_SubItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceInterpreter_CreateNewPackage_Proxy( 
    IDBTraceInterpreter __RPC_FAR * This,
    /* [out] */ IDBTracePackage __RPC_FAR *__RPC_FAR *ppIDBTracePackage);


void __RPC_STUB IDBTraceInterpreter_CreateNewPackage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDBTraceInterpreter_GetEnumString_Proxy( 
    IDBTraceInterpreter __RPC_FAR * This,
    /* [in] */ LONG lEnumTypeID,
    /* [in] */ LONG lEnumNumericalValue,
    /* [out] */ BSTR __RPC_FAR *pbstrEnumString);


void __RPC_STUB IDBTraceInterpreter_GetEnumString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBTraceInterpreter_INTERFACE_DEFINED__ */


#ifndef __IProviderEnum_INTERFACE_DEFINED__
#define __IProviderEnum_INTERFACE_DEFINED__

/* interface IProviderEnum */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IProviderEnum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29d82ddf-2bdb-11d2-90e1-00805fc752eb")
    IProviderEnum : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRegisteredProviders( 
            /* [retval][out] */ LPVARIANT pvProviders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTraceProviderCLSID( 
            /* [retval][out] */ LPVARIANT pvCLSIDString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProviderEnumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProviderEnum __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProviderEnum __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProviderEnum __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IProviderEnum __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IProviderEnum __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IProviderEnum __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IProviderEnum __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRegisteredProviders )( 
            IProviderEnum __RPC_FAR * This,
            /* [retval][out] */ LPVARIANT pvProviders);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTraceProviderCLSID )( 
            IProviderEnum __RPC_FAR * This,
            /* [retval][out] */ LPVARIANT pvCLSIDString);
        
        END_INTERFACE
    } IProviderEnumVtbl;

    interface IProviderEnum
    {
        CONST_VTBL struct IProviderEnumVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProviderEnum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProviderEnum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProviderEnum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProviderEnum_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IProviderEnum_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IProviderEnum_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IProviderEnum_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IProviderEnum_GetRegisteredProviders(This,pvProviders)	\
    (This)->lpVtbl -> GetRegisteredProviders(This,pvProviders)

#define IProviderEnum_GetTraceProviderCLSID(This,pvCLSIDString)	\
    (This)->lpVtbl -> GetTraceProviderCLSID(This,pvCLSIDString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProviderEnum_GetRegisteredProviders_Proxy( 
    IProviderEnum __RPC_FAR * This,
    /* [retval][out] */ LPVARIANT pvProviders);


void __RPC_STUB IProviderEnum_GetRegisteredProviders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProviderEnum_GetTraceProviderCLSID_Proxy( 
    IProviderEnum __RPC_FAR * This,
    /* [retval][out] */ LPVARIANT pvCLSIDString);


void __RPC_STUB IProviderEnum_GetTraceProviderCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProviderEnum_INTERFACE_DEFINED__ */



#ifndef __TraceProviderLib_LIBRARY_DEFINED__
#define __TraceProviderLib_LIBRARY_DEFINED__

/* library TraceProviderLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TraceProviderLib;

EXTERN_C const CLSID CLSID_TraceControl;

#ifdef __cplusplus

class DECLSPEC_UUID("29d82de9-2bdb-11d2-90e1-00805fc752eb")
TraceControl;
#endif

EXTERN_C const CLSID CLSID_Tracer;

#ifdef __cplusplus

class DECLSPEC_UUID("29d82dea-2bdb-11d2-90e1-00805fc752eb")
Tracer;
#endif

EXTERN_C const CLSID CLSID_TraceReceiver;

#ifdef __cplusplus

class DECLSPEC_UUID("29d82deb-2bdb-11d2-90e1-00805fc752eb")
TraceReceiver;
#endif

EXTERN_C const CLSID CLSID_TraceInterpreter;

#ifdef __cplusplus

class DECLSPEC_UUID("29d82dec-2bdb-11d2-90e1-00805fc752eb")
TraceInterpreter;
#endif

EXTERN_C const CLSID CLSID_ProviderEnum;

#ifdef __cplusplus

class DECLSPEC_UUID("29d82de1-2bdb-11d2-90e1-00805fc752eb")
ProviderEnum;
#endif
#endif /* __TraceProviderLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


