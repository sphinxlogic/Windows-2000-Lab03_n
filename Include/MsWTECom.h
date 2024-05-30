
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0279 */
/* at Mon Aug 16 13:14:55 1999
 */
/* Compiler settings for mswtecom.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __mswtecom_h__
#define __mswtecom_h__

/* Forward Declarations */ 

#ifndef __IWebTE_FWD_DEFINED__
#define __IWebTE_FWD_DEFINED__
typedef interface IWebTE IWebTE;
#endif 	/* __IWebTE_FWD_DEFINED__ */


#ifndef __IWebTEArrays_FWD_DEFINED__
#define __IWebTEArrays_FWD_DEFINED__
typedef interface IWebTEArrays IWebTEArrays;
#endif 	/* __IWebTEArrays_FWD_DEFINED__ */


#ifndef __IWebTEArray_FWD_DEFINED__
#define __IWebTEArray_FWD_DEFINED__
typedef interface IWebTEArray IWebTEArray;
#endif 	/* __IWebTEArray_FWD_DEFINED__ */


#ifndef __IWebTEServers_FWD_DEFINED__
#define __IWebTEServers_FWD_DEFINED__
typedef interface IWebTEServers IWebTEServers;
#endif 	/* __IWebTEServers_FWD_DEFINED__ */


#ifndef __IWebTEServer_FWD_DEFINED__
#define __IWebTEServer_FWD_DEFINED__
typedef interface IWebTEServer IWebTEServer;
#endif 	/* __IWebTEServer_FWD_DEFINED__ */


#ifndef __IWebTEAddresses_FWD_DEFINED__
#define __IWebTEAddresses_FWD_DEFINED__
typedef interface IWebTEAddresses IWebTEAddresses;
#endif 	/* __IWebTEAddresses_FWD_DEFINED__ */


#ifndef __IWebTEAddress_FWD_DEFINED__
#define __IWebTEAddress_FWD_DEFINED__
typedef interface IWebTEAddress IWebTEAddress;
#endif 	/* __IWebTEAddress_FWD_DEFINED__ */


#ifndef __IWebTELineStatus_FWD_DEFINED__
#define __IWebTELineStatus_FWD_DEFINED__
typedef interface IWebTELineStatus IWebTELineStatus;
#endif 	/* __IWebTELineStatus_FWD_DEFINED__ */


#ifndef __IWebTEVendorDataSets_FWD_DEFINED__
#define __IWebTEVendorDataSets_FWD_DEFINED__
typedef interface IWebTEVendorDataSets IWebTEVendorDataSets;
#endif 	/* __IWebTEVendorDataSets_FWD_DEFINED__ */


#ifndef __IWebTEVendorDataSet_FWD_DEFINED__
#define __IWebTEVendorDataSet_FWD_DEFINED__
typedef interface IWebTEVendorDataSet IWebTEVendorDataSet;
#endif 	/* __IWebTEVendorDataSet_FWD_DEFINED__ */


#ifndef __IWebTEHtmlPropertyPages_FWD_DEFINED__
#define __IWebTEHtmlPropertyPages_FWD_DEFINED__
typedef interface IWebTEHtmlPropertyPages IWebTEHtmlPropertyPages;
#endif 	/* __IWebTEHtmlPropertyPages_FWD_DEFINED__ */


#ifndef __IWebTEHtmlPropertyPage_FWD_DEFINED__
#define __IWebTEHtmlPropertyPage_FWD_DEFINED__
typedef interface IWebTEHtmlPropertyPage IWebTEHtmlPropertyPage;
#endif 	/* __IWebTEHtmlPropertyPage_FWD_DEFINED__ */


#ifndef __IWebTEParametersSets_FWD_DEFINED__
#define __IWebTEParametersSets_FWD_DEFINED__
typedef interface IWebTEParametersSets IWebTEParametersSets;
#endif 	/* __IWebTEParametersSets_FWD_DEFINED__ */


#ifndef __IWebTEParametersSet_FWD_DEFINED__
#define __IWebTEParametersSet_FWD_DEFINED__
typedef interface IWebTEParametersSet IWebTEParametersSet;
#endif 	/* __IWebTEParametersSet_FWD_DEFINED__ */


#ifndef __IWebTELog_FWD_DEFINED__
#define __IWebTELog_FWD_DEFINED__
typedef interface IWebTELog IWebTELog;
#endif 	/* __IWebTELog_FWD_DEFINED__ */


#ifndef __IWebTEApplications_FWD_DEFINED__
#define __IWebTEApplications_FWD_DEFINED__
typedef interface IWebTEApplications IWebTEApplications;
#endif 	/* __IWebTEApplications_FWD_DEFINED__ */


#ifndef __IWebTEApplication_FWD_DEFINED__
#define __IWebTEApplication_FWD_DEFINED__
typedef interface IWebTEApplication IWebTEApplication;
#endif 	/* __IWebTEApplication_FWD_DEFINED__ */


#ifndef __ITelephonyStepConstrains_FWD_DEFINED__
#define __ITelephonyStepConstrains_FWD_DEFINED__
typedef interface ITelephonyStepConstrains ITelephonyStepConstrains;
#endif 	/* __ITelephonyStepConstrains_FWD_DEFINED__ */


#ifndef __ISession_FWD_DEFINED__
#define __ISession_FWD_DEFINED__
typedef interface ISession ISession;
#endif 	/* __ISession_FWD_DEFINED__ */


#ifndef __ITTSMode_FWD_DEFINED__
#define __ITTSMode_FWD_DEFINED__
typedef interface ITTSMode ITTSMode;
#endif 	/* __ITTSMode_FWD_DEFINED__ */


#ifndef __ISRMode_FWD_DEFINED__
#define __ISRMode_FWD_DEFINED__
typedef interface ISRMode ISRMode;
#endif 	/* __ISRMode_FWD_DEFINED__ */


#ifndef __ITelephonyStep_FWD_DEFINED__
#define __ITelephonyStep_FWD_DEFINED__
typedef interface ITelephonyStep ITelephonyStep;
#endif 	/* __ITelephonyStep_FWD_DEFINED__ */


#ifndef __ILogCustomField_FWD_DEFINED__
#define __ILogCustomField_FWD_DEFINED__
typedef interface ILogCustomField ILogCustomField;
#endif 	/* __ILogCustomField_FWD_DEFINED__ */


#ifndef __IExOM_FWD_DEFINED__
#define __IExOM_FWD_DEFINED__
typedef interface IExOM IExOM;
#endif 	/* __IExOM_FWD_DEFINED__ */


#ifndef __IWebIvrActiveConnection_FWD_DEFINED__
#define __IWebIvrActiveConnection_FWD_DEFINED__
typedef interface IWebIvrActiveConnection IWebIvrActiveConnection;
#endif 	/* __IWebIvrActiveConnection_FWD_DEFINED__ */


#ifndef __IWebIvrService_FWD_DEFINED__
#define __IWebIvrService_FWD_DEFINED__
typedef interface IWebIvrService IWebIvrService;
#endif 	/* __IWebIvrService_FWD_DEFINED__ */


#ifndef __IWebTESnapinNode_FWD_DEFINED__
#define __IWebTESnapinNode_FWD_DEFINED__
typedef interface IWebTESnapinNode IWebTESnapinNode;
#endif 	/* __IWebTESnapinNode_FWD_DEFINED__ */


#ifndef __WebTE_FWD_DEFINED__
#define __WebTE_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTE WebTE;
#else
typedef struct WebTE WebTE;
#endif /* __cplusplus */

#endif 	/* __WebTE_FWD_DEFINED__ */


#ifndef __WebTEArray_FWD_DEFINED__
#define __WebTEArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEArray WebTEArray;
#else
typedef struct WebTEArray WebTEArray;
#endif /* __cplusplus */

#endif 	/* __WebTEArray_FWD_DEFINED__ */


#ifndef __WebTEArrays_FWD_DEFINED__
#define __WebTEArrays_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEArrays WebTEArrays;
#else
typedef struct WebTEArrays WebTEArrays;
#endif /* __cplusplus */

#endif 	/* __WebTEArrays_FWD_DEFINED__ */


#ifndef __WebTEServers_FWD_DEFINED__
#define __WebTEServers_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEServers WebTEServers;
#else
typedef struct WebTEServers WebTEServers;
#endif /* __cplusplus */

#endif 	/* __WebTEServers_FWD_DEFINED__ */


#ifndef __WebTEServer_FWD_DEFINED__
#define __WebTEServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEServer WebTEServer;
#else
typedef struct WebTEServer WebTEServer;
#endif /* __cplusplus */

#endif 	/* __WebTEServer_FWD_DEFINED__ */


#ifndef __WebTEAddresses_FWD_DEFINED__
#define __WebTEAddresses_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEAddresses WebTEAddresses;
#else
typedef struct WebTEAddresses WebTEAddresses;
#endif /* __cplusplus */

#endif 	/* __WebTEAddresses_FWD_DEFINED__ */


#ifndef __WebTEAddress_FWD_DEFINED__
#define __WebTEAddress_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEAddress WebTEAddress;
#else
typedef struct WebTEAddress WebTEAddress;
#endif /* __cplusplus */

#endif 	/* __WebTEAddress_FWD_DEFINED__ */


#ifndef __WebTELineStatus_FWD_DEFINED__
#define __WebTELineStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTELineStatus WebTELineStatus;
#else
typedef struct WebTELineStatus WebTELineStatus;
#endif /* __cplusplus */

#endif 	/* __WebTELineStatus_FWD_DEFINED__ */


#ifndef __IWebTEParametersChanges_FWD_DEFINED__
#define __IWebTEParametersChanges_FWD_DEFINED__
typedef interface IWebTEParametersChanges IWebTEParametersChanges;
#endif 	/* __IWebTEParametersChanges_FWD_DEFINED__ */


#ifndef __WebTEVendorDataSets_FWD_DEFINED__
#define __WebTEVendorDataSets_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEVendorDataSets WebTEVendorDataSets;
#else
typedef struct WebTEVendorDataSets WebTEVendorDataSets;
#endif /* __cplusplus */

#endif 	/* __WebTEVendorDataSets_FWD_DEFINED__ */


#ifndef __WebTEVendorDataSet_FWD_DEFINED__
#define __WebTEVendorDataSet_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEVendorDataSet WebTEVendorDataSet;
#else
typedef struct WebTEVendorDataSet WebTEVendorDataSet;
#endif /* __cplusplus */

#endif 	/* __WebTEVendorDataSet_FWD_DEFINED__ */


#ifndef __WebTEHtmlPropertyPages_FWD_DEFINED__
#define __WebTEHtmlPropertyPages_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEHtmlPropertyPages WebTEHtmlPropertyPages;
#else
typedef struct WebTEHtmlPropertyPages WebTEHtmlPropertyPages;
#endif /* __cplusplus */

#endif 	/* __WebTEHtmlPropertyPages_FWD_DEFINED__ */


#ifndef __WebTEHtmlPropertyPage_FWD_DEFINED__
#define __WebTEHtmlPropertyPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEHtmlPropertyPage WebTEHtmlPropertyPage;
#else
typedef struct WebTEHtmlPropertyPage WebTEHtmlPropertyPage;
#endif /* __cplusplus */

#endif 	/* __WebTEHtmlPropertyPage_FWD_DEFINED__ */


#ifndef __WebTEParametersSets_FWD_DEFINED__
#define __WebTEParametersSets_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEParametersSets WebTEParametersSets;
#else
typedef struct WebTEParametersSets WebTEParametersSets;
#endif /* __cplusplus */

#endif 	/* __WebTEParametersSets_FWD_DEFINED__ */


#ifndef __WebTEParametersSet_FWD_DEFINED__
#define __WebTEParametersSet_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEParametersSet WebTEParametersSet;
#else
typedef struct WebTEParametersSet WebTEParametersSet;
#endif /* __cplusplus */

#endif 	/* __WebTEParametersSet_FWD_DEFINED__ */


#ifndef __WebTELog_FWD_DEFINED__
#define __WebTELog_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTELog WebTELog;
#else
typedef struct WebTELog WebTELog;
#endif /* __cplusplus */

#endif 	/* __WebTELog_FWD_DEFINED__ */


#ifndef __WebTEApplications_FWD_DEFINED__
#define __WebTEApplications_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEApplications WebTEApplications;
#else
typedef struct WebTEApplications WebTEApplications;
#endif /* __cplusplus */

#endif 	/* __WebTEApplications_FWD_DEFINED__ */


#ifndef __WebTEApplication_FWD_DEFINED__
#define __WebTEApplication_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTEApplication WebTEApplication;
#else
typedef struct WebTEApplication WebTEApplication;
#endif /* __cplusplus */

#endif 	/* __WebTEApplication_FWD_DEFINED__ */


#ifndef __IWebIvrConnectionEvents_FWD_DEFINED__
#define __IWebIvrConnectionEvents_FWD_DEFINED__
typedef interface IWebIvrConnectionEvents IWebIvrConnectionEvents;
#endif 	/* __IWebIvrConnectionEvents_FWD_DEFINED__ */


#ifndef __WebIvrService_FWD_DEFINED__
#define __WebIvrService_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebIvrService WebIvrService;
#else
typedef struct WebIvrService WebIvrService;
#endif /* __cplusplus */

#endif 	/* __WebIvrService_FWD_DEFINED__ */


#ifndef __WebIvrActiveConnection_FWD_DEFINED__
#define __WebIvrActiveConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebIvrActiveConnection WebIvrActiveConnection;
#else
typedef struct WebIvrActiveConnection WebIvrActiveConnection;
#endif /* __cplusplus */

#endif 	/* __WebIvrActiveConnection_FWD_DEFINED__ */


#ifndef __TelephonyStep_FWD_DEFINED__
#define __TelephonyStep_FWD_DEFINED__

#ifdef __cplusplus
typedef class TelephonyStep TelephonyStep;
#else
typedef struct TelephonyStep TelephonyStep;
#endif /* __cplusplus */

#endif 	/* __TelephonyStep_FWD_DEFINED__ */


#ifndef __TelephonyStepConstrains_FWD_DEFINED__
#define __TelephonyStepConstrains_FWD_DEFINED__

#ifdef __cplusplus
typedef class TelephonyStepConstrains TelephonyStepConstrains;
#else
typedef struct TelephonyStepConstrains TelephonyStepConstrains;
#endif /* __cplusplus */

#endif 	/* __TelephonyStepConstrains_FWD_DEFINED__ */


#ifndef __Session_FWD_DEFINED__
#define __Session_FWD_DEFINED__

#ifdef __cplusplus
typedef class Session Session;
#else
typedef struct Session Session;
#endif /* __cplusplus */

#endif 	/* __Session_FWD_DEFINED__ */


#ifndef __TTSMode_FWD_DEFINED__
#define __TTSMode_FWD_DEFINED__

#ifdef __cplusplus
typedef class TTSMode TTSMode;
#else
typedef struct TTSMode TTSMode;
#endif /* __cplusplus */

#endif 	/* __TTSMode_FWD_DEFINED__ */


#ifndef __SRMode_FWD_DEFINED__
#define __SRMode_FWD_DEFINED__

#ifdef __cplusplus
typedef class SRMode SRMode;
#else
typedef struct SRMode SRMode;
#endif /* __cplusplus */

#endif 	/* __SRMode_FWD_DEFINED__ */


#ifndef __ExOM_FWD_DEFINED__
#define __ExOM_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExOM ExOM;
#else
typedef struct ExOM ExOM;
#endif /* __cplusplus */

#endif 	/* __ExOM_FWD_DEFINED__ */


#ifndef __LogCustomField_FWD_DEFINED__
#define __LogCustomField_FWD_DEFINED__

#ifdef __cplusplus
typedef class LogCustomField LogCustomField;
#else
typedef struct LogCustomField LogCustomField;
#endif /* __cplusplus */

#endif 	/* __LogCustomField_FWD_DEFINED__ */


#ifndef __WebTESnapinNode_FWD_DEFINED__
#define __WebTESnapinNode_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebTESnapinNode WebTESnapinNode;
#else
typedef struct WebTESnapinNode WebTESnapinNode;
#endif /* __cplusplus */

#endif 	/* __WebTESnapinNode_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "tapi3if.h"
#include "mswteImports.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_mswtecom_0000 */
/* [local] */ 



















extern RPC_IF_HANDLE __MIDL_itf_mswtecom_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mswtecom_0000_v0_0_s_ifspec;

#ifndef __IWebTE_INTERFACE_DEFINED__
#define __IWebTE_INTERFACE_DEFINED__

/* interface IWebTE */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTE;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8310-336C-11D3-8657-0090272F9EEB")
    IWebTE : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Arrays( 
            /* [retval][out] */ IWebTEArrays __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTE __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTE __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTE __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTE __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTE __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTE __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTE __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Arrays )( 
            IWebTE __RPC_FAR * This,
            /* [retval][out] */ IWebTEArrays __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTE __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTE __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTE __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IWebTEVtbl;

    interface IWebTE
    {
        CONST_VTBL struct IWebTEVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTE_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTE_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTE_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTE_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTE_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTE_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTE_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTE_get_Arrays(This,pVal)	\
    (This)->lpVtbl -> get_Arrays(This,pVal)

#define IWebTE_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTE_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTE_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTE_get_Arrays_Proxy( 
    IWebTE __RPC_FAR * This,
    /* [retval][out] */ IWebTEArrays __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTE_get_Arrays_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTE_Save_Proxy( 
    IWebTE __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTE_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTE_Refresh_Proxy( 
    IWebTE __RPC_FAR * This);


void __RPC_STUB IWebTE_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTE_get_VendorDataSets_Proxy( 
    IWebTE __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTE_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTE_INTERFACE_DEFINED__ */


#ifndef __IWebTEArrays_INTERFACE_DEFINED__
#define __IWebTEArrays_INTERFACE_DEFINED__

/* interface IWebTEArrays */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEArrays;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8311-336C-11D3-8657-0090272F9EEB")
    IWebTEArrays : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT v,
            /* [retval][out] */ IWebTEArray __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetContainingArray( 
            /* [retval][out] */ IWebTEArray __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT v) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEArraysVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEArrays __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEArrays __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEArrays __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEArrays __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEArrays __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEArrays __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEArrays __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEArrays __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEArrays __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEArrays __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEArrays __RPC_FAR * This,
            VARIANT v,
            /* [retval][out] */ IWebTEArray __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEArrays __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetContainingArray )( 
            IWebTEArrays __RPC_FAR * This,
            /* [retval][out] */ IWebTEArray __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEArrays __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWebTEArrays __RPC_FAR * This,
            VARIANT v);
        
        END_INTERFACE
    } IWebTEArraysVtbl;

    interface IWebTEArrays
    {
        CONST_VTBL struct IWebTEArraysVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEArrays_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEArrays_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEArrays_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEArrays_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEArrays_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEArrays_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEArrays_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEArrays_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEArrays_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEArrays_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IWebTEArrays_Item(This,v,pItem)	\
    (This)->lpVtbl -> Item(This,v,pItem)

#define IWebTEArrays_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IWebTEArrays_GetContainingArray(This,pItem)	\
    (This)->lpVtbl -> GetContainingArray(This,pItem)

#define IWebTEArrays_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#define IWebTEArrays_Remove(This,v)	\
    (This)->lpVtbl -> Remove(This,v)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_Save_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEArrays_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_Refresh_Proxy( 
    IWebTEArrays __RPC_FAR * This);


void __RPC_STUB IWebTEArrays_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_get_Count_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWebTEArrays_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_Item_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    VARIANT v,
    /* [retval][out] */ IWebTEArray __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEArrays_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_get__NewEnum_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEArrays_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_GetContainingArray_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    /* [retval][out] */ IWebTEArray __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEArrays_GetContainingArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_get_VendorDataSets_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEArrays_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArrays_Remove_Proxy( 
    IWebTEArrays __RPC_FAR * This,
    VARIANT v);


void __RPC_STUB IWebTEArrays_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEArrays_INTERFACE_DEFINED__ */


#ifndef __IWebTEArray_INTERFACE_DEFINED__
#define __IWebTEArray_INTERFACE_DEFINED__

/* interface IWebTEArray */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8312-336C-11D3-8657-0090272F9EEB")
    IWebTEArray : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Servers( 
            /* [retval][out] */ IWebTEServers __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Applications( 
            /* [retval][out] */ IWebTEApplications __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Log( 
            /* [retval][out] */ IWebTELog __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEArray __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEArray __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEArray __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEArray __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEArray __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebTEArray __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IWebTEArray __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IWebTEArray __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IWebTEArray __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Servers )( 
            IWebTEArray __RPC_FAR * This,
            /* [retval][out] */ IWebTEServers __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Applications )( 
            IWebTEArray __RPC_FAR * This,
            /* [retval][out] */ IWebTEApplications __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Log )( 
            IWebTEArray __RPC_FAR * This,
            /* [retval][out] */ IWebTELog __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEArray __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEArray __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEArray __RPC_FAR * This);
        
        END_INTERFACE
    } IWebTEArrayVtbl;

    interface IWebTEArray
    {
        CONST_VTBL struct IWebTEArrayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEArray_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEArray_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IWebTEArray_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IWebTEArray_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IWebTEArray_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define IWebTEArray_get_Servers(This,pVal)	\
    (This)->lpVtbl -> get_Servers(This,pVal)

#define IWebTEArray_get_Applications(This,pVal)	\
    (This)->lpVtbl -> get_Applications(This,pVal)

#define IWebTEArray_get_Log(This,pVal)	\
    (This)->lpVtbl -> get_Log(This,pVal)

#define IWebTEArray_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#define IWebTEArray_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEArray_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArray_get_Name_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEArray_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEArray_put_Name_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEArray_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArray_get_Description_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEArray_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEArray_put_Description_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEArray_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArray_get_Servers_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [retval][out] */ IWebTEServers __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEArray_get_Servers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArray_get_Applications_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [retval][out] */ IWebTEApplications __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEArray_get_Applications_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArray_get_Log_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [retval][out] */ IWebTELog __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEArray_get_Log_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEArray_get_VendorDataSets_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEArray_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArray_Save_Proxy( 
    IWebTEArray __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEArray_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEArray_Refresh_Proxy( 
    IWebTEArray __RPC_FAR * This);


void __RPC_STUB IWebTEArray_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEArray_INTERFACE_DEFINED__ */


#ifndef __IWebTEServers_INTERFACE_DEFINED__
#define __IWebTEServers_INTERFACE_DEFINED__

/* interface IWebTEServers */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEServers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8313-336C-11D3-8657-0090272F9EEB")
    IWebTEServers : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT v,
            /* [retval][out] */ IWebTEServer __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEServersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEServers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEServers __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEServers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEServers __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEServers __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEServers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEServers __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEServers __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEServers __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEServers __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEServers __RPC_FAR * This,
            VARIANT v,
            /* [retval][out] */ IWebTEServer __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEServers __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEServers __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IWebTEServersVtbl;

    interface IWebTEServers
    {
        CONST_VTBL struct IWebTEServersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEServers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEServers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEServers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEServers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEServers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEServers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEServers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEServers_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IWebTEServers_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEServers_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEServers_Item(This,v,pItem)	\
    (This)->lpVtbl -> Item(This,v,pItem)

#define IWebTEServers_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IWebTEServers_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServers_get_Count_Proxy( 
    IWebTEServers __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWebTEServers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEServers_Save_Proxy( 
    IWebTEServers __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEServers_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEServers_Refresh_Proxy( 
    IWebTEServers __RPC_FAR * This);


void __RPC_STUB IWebTEServers_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEServers_Item_Proxy( 
    IWebTEServers __RPC_FAR * This,
    VARIANT v,
    /* [retval][out] */ IWebTEServer __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEServers_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServers_get__NewEnum_Proxy( 
    IWebTEServers __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEServers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServers_get_VendorDataSets_Proxy( 
    IWebTEServers __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEServers_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEServers_INTERFACE_DEFINED__ */


#ifndef __IWebTEServer_INTERFACE_DEFINED__
#define __IWebTEServer_INTERFACE_DEFINED__

/* interface IWebTEServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8314-336C-11D3-8657-0090272F9EEB")
    IWebTEServer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProductVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProductId( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Addresses( 
            /* [retval][out] */ IWebTEAddresses __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEServer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEServer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEServer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebTEServer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProductVersion )( 
            IWebTEServer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProductId )( 
            IWebTEServer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IWebTEServer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IWebTEServer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Addresses )( 
            IWebTEServer __RPC_FAR * This,
            /* [retval][out] */ IWebTEAddresses __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEServer __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEServer __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEServer __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IWebTEServerVtbl;

    interface IWebTEServer
    {
        CONST_VTBL struct IWebTEServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEServer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEServer_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IWebTEServer_get_ProductVersion(This,pVal)	\
    (This)->lpVtbl -> get_ProductVersion(This,pVal)

#define IWebTEServer_get_ProductId(This,pVal)	\
    (This)->lpVtbl -> get_ProductId(This,pVal)

#define IWebTEServer_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IWebTEServer_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define IWebTEServer_get_Addresses(This,pVal)	\
    (This)->lpVtbl -> get_Addresses(This,pVal)

#define IWebTEServer_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEServer_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEServer_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServer_get_Name_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEServer_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServer_get_ProductVersion_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEServer_get_ProductVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServer_get_ProductId_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEServer_get_ProductId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServer_get_Description_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEServer_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEServer_put_Description_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEServer_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServer_get_Addresses_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [retval][out] */ IWebTEAddresses __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEServer_get_Addresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEServer_Save_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEServer_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEServer_Refresh_Proxy( 
    IWebTEServer __RPC_FAR * This);


void __RPC_STUB IWebTEServer_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEServer_get_VendorDataSets_Proxy( 
    IWebTEServer __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEServer_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEServer_INTERFACE_DEFINED__ */


#ifndef __IWebTEAddresses_INTERFACE_DEFINED__
#define __IWebTEAddresses_INTERFACE_DEFINED__

/* interface IWebTEAddresses */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEAddresses;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8315-336C-11D3-8657-0090272F9EEB")
    IWebTEAddresses : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RefreshStatus( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT v,
            /* [retval][out] */ IWebTEAddress __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEAddressesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEAddresses __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEAddresses __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEAddresses __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshStatus )( 
            IWebTEAddresses __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEAddresses __RPC_FAR * This,
            VARIANT v,
            /* [retval][out] */ IWebTEAddress __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEAddresses __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IWebTEAddressesVtbl;

    interface IWebTEAddresses
    {
        CONST_VTBL struct IWebTEAddressesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEAddresses_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEAddresses_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEAddresses_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEAddresses_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEAddresses_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEAddresses_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEAddresses_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEAddresses_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IWebTEAddresses_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEAddresses_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEAddresses_RefreshStatus(This)	\
    (This)->lpVtbl -> RefreshStatus(This)

#define IWebTEAddresses_Item(This,v,pItem)	\
    (This)->lpVtbl -> Item(This,v,pItem)

#define IWebTEAddresses_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IWebTEAddresses_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_get_Count_Proxy( 
    IWebTEAddresses __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWebTEAddresses_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_Save_Proxy( 
    IWebTEAddresses __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEAddresses_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_Refresh_Proxy( 
    IWebTEAddresses __RPC_FAR * This);


void __RPC_STUB IWebTEAddresses_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_RefreshStatus_Proxy( 
    IWebTEAddresses __RPC_FAR * This);


void __RPC_STUB IWebTEAddresses_RefreshStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_Item_Proxy( 
    IWebTEAddresses __RPC_FAR * This,
    VARIANT v,
    /* [retval][out] */ IWebTEAddress __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEAddresses_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_get__NewEnum_Proxy( 
    IWebTEAddresses __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEAddresses_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddresses_get_VendorDataSets_Proxy( 
    IWebTEAddresses __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEAddresses_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEAddresses_INTERFACE_DEFINED__ */


#ifndef __IWebTEAddress_INTERFACE_DEFINED__
#define __IWebTEAddress_INTERFACE_DEFINED__

/* interface IWebTEAddress */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEAddress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8316-336C-11D3-8657-0090272F9EEB")
    IWebTEAddress : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportsCalledID( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DialableAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AssignedApplication( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AssignedApplication( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ IWebTELineStatus __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEAddressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEAddress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEAddress __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEAddress __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEAddress __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEAddress __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEAddress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEAddress __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SupportsCalledID )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DialableAddress )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AssignedApplication )( 
            IWebTEAddress __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AssignedApplication )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ IWebTELineStatus __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IWebTEAddress __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEAddress __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEAddress __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEAddress __RPC_FAR * This);
        
        END_INTERFACE
    } IWebTEAddressVtbl;

    interface IWebTEAddress
    {
        CONST_VTBL struct IWebTEAddressVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEAddress_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEAddress_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEAddress_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEAddress_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEAddress_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEAddress_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEAddress_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEAddress_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IWebTEAddress_get_SupportsCalledID(This,pVal)	\
    (This)->lpVtbl -> get_SupportsCalledID(This,pVal)

#define IWebTEAddress_get_DialableAddress(This,pVal)	\
    (This)->lpVtbl -> get_DialableAddress(This,pVal)

#define IWebTEAddress_put_AssignedApplication(This,newVal)	\
    (This)->lpVtbl -> put_AssignedApplication(This,newVal)

#define IWebTEAddress_get_AssignedApplication(This,pVal)	\
    (This)->lpVtbl -> get_AssignedApplication(This,pVal)

#define IWebTEAddress_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define IWebTEAddress_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IWebTEAddress_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define IWebTEAddress_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#define IWebTEAddress_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEAddress_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_Name_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_SupportsCalledID_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_SupportsCalledID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_DialableAddress_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_DialableAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_put_AssignedApplication_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEAddress_put_AssignedApplication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_AssignedApplication_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_AssignedApplication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_Status_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ IWebTELineStatus __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_Description_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_put_Description_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEAddress_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_get_VendorDataSets_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEAddress_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_Save_Proxy( 
    IWebTEAddress __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEAddress_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEAddress_Refresh_Proxy( 
    IWebTEAddress __RPC_FAR * This);


void __RPC_STUB IWebTEAddress_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEAddress_INTERFACE_DEFINED__ */


#ifndef __IWebTELineStatus_INTERFACE_DEFINED__
#define __IWebTELineStatus_INTERFACE_DEFINED__

/* interface IWebTELineStatus */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTELineStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8317-336C-11D3-8657-0090272F9EEB")
    IWebTELineStatus : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ LineStatusType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CallerId( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CalledId( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTELineStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTELineStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTELineStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [retval][out] */ LineStatusType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallerId )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CalledId )( 
            IWebTELineStatus __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTELineStatus __RPC_FAR * This);
        
        END_INTERFACE
    } IWebTELineStatusVtbl;

    interface IWebTELineStatus
    {
        CONST_VTBL struct IWebTELineStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTELineStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTELineStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTELineStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTELineStatus_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTELineStatus_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTELineStatus_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTELineStatus_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTELineStatus_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define IWebTELineStatus_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IWebTELineStatus_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define IWebTELineStatus_get_CallerId(This,pVal)	\
    (This)->lpVtbl -> get_CallerId(This,pVal)

#define IWebTELineStatus_get_CalledId(This,pVal)	\
    (This)->lpVtbl -> get_CalledId(This,pVal)

#define IWebTELineStatus_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELineStatus_get_Status_Proxy( 
    IWebTELineStatus __RPC_FAR * This,
    /* [retval][out] */ LineStatusType __RPC_FAR *pVal);


void __RPC_STUB IWebTELineStatus_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELineStatus_get_Duration_Proxy( 
    IWebTELineStatus __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IWebTELineStatus_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELineStatus_get_Application_Proxy( 
    IWebTELineStatus __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTELineStatus_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELineStatus_get_CallerId_Proxy( 
    IWebTELineStatus __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTELineStatus_get_CallerId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELineStatus_get_CalledId_Proxy( 
    IWebTELineStatus __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTELineStatus_get_CalledId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTELineStatus_Refresh_Proxy( 
    IWebTELineStatus __RPC_FAR * This);


void __RPC_STUB IWebTELineStatus_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTELineStatus_INTERFACE_DEFINED__ */


#ifndef __IWebTEVendorDataSets_INTERFACE_DEFINED__
#define __IWebTEVendorDataSets_INTERFACE_DEFINED__

/* interface IWebTEVendorDataSets */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEVendorDataSets;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8318-336C-11D3-8657-0090272F9EEB")
    IWebTEVendorDataSets : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT v,
            /* [retval][out] */ IWebTEVendorDataSet __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Id,
            /* [retval][out] */ IWebTEVendorDataSet __RPC_FAR *__RPC_FAR *ppNewSet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT v) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEVendorDataSetsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEVendorDataSets __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEVendorDataSets __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            VARIANT v,
            /* [retval][out] */ IWebTEVendorDataSet __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEVendorDataSets __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            /* [in] */ BSTR Id,
            /* [retval][out] */ IWebTEVendorDataSet __RPC_FAR *__RPC_FAR *ppNewSet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWebTEVendorDataSets __RPC_FAR * This,
            VARIANT v);
        
        END_INTERFACE
    } IWebTEVendorDataSetsVtbl;

    interface IWebTEVendorDataSets
    {
        CONST_VTBL struct IWebTEVendorDataSetsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEVendorDataSets_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEVendorDataSets_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEVendorDataSets_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEVendorDataSets_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEVendorDataSets_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEVendorDataSets_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEVendorDataSets_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEVendorDataSets_Item(This,v,pItem)	\
    (This)->lpVtbl -> Item(This,v,pItem)

#define IWebTEVendorDataSets_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IWebTEVendorDataSets_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IWebTEVendorDataSets_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEVendorDataSets_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEVendorDataSets_Add(This,Id,ppNewSet)	\
    (This)->lpVtbl -> Add(This,Id,ppNewSet)

#define IWebTEVendorDataSets_Remove(This,v)	\
    (This)->lpVtbl -> Remove(This,v)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_Item_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This,
    VARIANT v,
    /* [retval][out] */ IWebTEVendorDataSet __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEVendorDataSets_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_get__NewEnum_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEVendorDataSets_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_get_Count_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWebTEVendorDataSets_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_Save_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEVendorDataSets_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_Refresh_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This);


void __RPC_STUB IWebTEVendorDataSets_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_Add_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This,
    /* [in] */ BSTR Id,
    /* [retval][out] */ IWebTEVendorDataSet __RPC_FAR *__RPC_FAR *ppNewSet);


void __RPC_STUB IWebTEVendorDataSets_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSets_Remove_Proxy( 
    IWebTEVendorDataSets __RPC_FAR * This,
    VARIANT v);


void __RPC_STUB IWebTEVendorDataSets_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEVendorDataSets_INTERFACE_DEFINED__ */


#ifndef __IWebTEVendorDataSet_INTERFACE_DEFINED__
#define __IWebTEVendorDataSet_INTERFACE_DEFINED__

/* interface IWebTEVendorDataSet */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEVendorDataSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8319-336C-11D3-8657-0090272F9EEB")
    IWebTEVendorDataSet : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PropertyPages( 
            /* [retval][out] */ IWebTEHtmlPropertyPages __RPC_FAR *__RPC_FAR *ppPages) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParametersSets( 
            /* [retval][out] */ IWebTEParametersSets __RPC_FAR *__RPC_FAR *ppSets) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Id( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEVendorDataSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEVendorDataSet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEVendorDataSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PropertyPages )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [retval][out] */ IWebTEHtmlPropertyPages __RPC_FAR *__RPC_FAR *ppPages);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParametersSets )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [retval][out] */ IWebTEParametersSets __RPC_FAR *__RPC_FAR *ppSets);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Id )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Id )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEVendorDataSet __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEVendorDataSet __RPC_FAR * This);
        
        END_INTERFACE
    } IWebTEVendorDataSetVtbl;

    interface IWebTEVendorDataSet
    {
        CONST_VTBL struct IWebTEVendorDataSetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEVendorDataSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEVendorDataSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEVendorDataSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEVendorDataSet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEVendorDataSet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEVendorDataSet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEVendorDataSet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEVendorDataSet_get_PropertyPages(This,ppPages)	\
    (This)->lpVtbl -> get_PropertyPages(This,ppPages)

#define IWebTEVendorDataSet_get_ParametersSets(This,ppSets)	\
    (This)->lpVtbl -> get_ParametersSets(This,ppSets)

#define IWebTEVendorDataSet_get_Id(This,pVal)	\
    (This)->lpVtbl -> get_Id(This,pVal)

#define IWebTEVendorDataSet_put_Id(This,newVal)	\
    (This)->lpVtbl -> put_Id(This,newVal)

#define IWebTEVendorDataSet_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEVendorDataSet_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSet_get_PropertyPages_Proxy( 
    IWebTEVendorDataSet __RPC_FAR * This,
    /* [retval][out] */ IWebTEHtmlPropertyPages __RPC_FAR *__RPC_FAR *ppPages);


void __RPC_STUB IWebTEVendorDataSet_get_PropertyPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSet_get_ParametersSets_Proxy( 
    IWebTEVendorDataSet __RPC_FAR * This,
    /* [retval][out] */ IWebTEParametersSets __RPC_FAR *__RPC_FAR *ppSets);


void __RPC_STUB IWebTEVendorDataSet_get_ParametersSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSet_get_Id_Proxy( 
    IWebTEVendorDataSet __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEVendorDataSet_get_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSet_put_Id_Proxy( 
    IWebTEVendorDataSet __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEVendorDataSet_put_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSet_Save_Proxy( 
    IWebTEVendorDataSet __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEVendorDataSet_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEVendorDataSet_Refresh_Proxy( 
    IWebTEVendorDataSet __RPC_FAR * This);


void __RPC_STUB IWebTEVendorDataSet_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEVendorDataSet_INTERFACE_DEFINED__ */


#ifndef __IWebTEHtmlPropertyPages_INTERFACE_DEFINED__
#define __IWebTEHtmlPropertyPages_INTERFACE_DEFINED__

/* interface IWebTEHtmlPropertyPages */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEHtmlPropertyPages;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E831A-336C-11D3-8657-0090272F9EEB")
    IWebTEHtmlPropertyPages : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT v,
            /* [retval][out] */ IWebTEHtmlPropertyPage __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            BSTR Caption,
            BSTR RelativePath,
            /* [retval][out] */ IWebTEHtmlPropertyPage __RPC_FAR *__RPC_FAR *ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT v) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEHtmlPropertyPagesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            VARIANT v,
            /* [retval][out] */ IWebTEHtmlPropertyPage __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            BSTR Caption,
            BSTR RelativePath,
            /* [retval][out] */ IWebTEHtmlPropertyPage __RPC_FAR *__RPC_FAR *ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWebTEHtmlPropertyPages __RPC_FAR * This,
            VARIANT v);
        
        END_INTERFACE
    } IWebTEHtmlPropertyPagesVtbl;

    interface IWebTEHtmlPropertyPages
    {
        CONST_VTBL struct IWebTEHtmlPropertyPagesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEHtmlPropertyPages_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEHtmlPropertyPages_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEHtmlPropertyPages_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEHtmlPropertyPages_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEHtmlPropertyPages_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEHtmlPropertyPages_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEHtmlPropertyPages_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEHtmlPropertyPages_Item(This,v,pItem)	\
    (This)->lpVtbl -> Item(This,v,pItem)

#define IWebTEHtmlPropertyPages_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IWebTEHtmlPropertyPages_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IWebTEHtmlPropertyPages_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEHtmlPropertyPages_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEHtmlPropertyPages_Add(This,Caption,RelativePath,ppVal)	\
    (This)->lpVtbl -> Add(This,Caption,RelativePath,ppVal)

#define IWebTEHtmlPropertyPages_Remove(This,v)	\
    (This)->lpVtbl -> Remove(This,v)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_Item_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This,
    VARIANT v,
    /* [retval][out] */ IWebTEHtmlPropertyPage __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEHtmlPropertyPages_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_get__NewEnum_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEHtmlPropertyPages_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_get_Count_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWebTEHtmlPropertyPages_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_Save_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEHtmlPropertyPages_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_Refresh_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This);


void __RPC_STUB IWebTEHtmlPropertyPages_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_Add_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This,
    BSTR Caption,
    BSTR RelativePath,
    /* [retval][out] */ IWebTEHtmlPropertyPage __RPC_FAR *__RPC_FAR *ppVal);


void __RPC_STUB IWebTEHtmlPropertyPages_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPages_Remove_Proxy( 
    IWebTEHtmlPropertyPages __RPC_FAR * This,
    VARIANT v);


void __RPC_STUB IWebTEHtmlPropertyPages_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEHtmlPropertyPages_INTERFACE_DEFINED__ */


#ifndef __IWebTEHtmlPropertyPage_INTERFACE_DEFINED__
#define __IWebTEHtmlPropertyPage_INTERFACE_DEFINED__

/* interface IWebTEHtmlPropertyPage */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEHtmlPropertyPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E831B-336C-11D3-8657-0090272F9EEB")
    IWebTEHtmlPropertyPage : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RelativePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RelativePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HtmHelpPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HtmHelpPath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HtmHelpEntry( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HtmHelpEntry( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEHtmlPropertyPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RelativePath )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RelativePath )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HtmHelpPath )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HtmHelpPath )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HtmHelpEntry )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HtmHelpEntry )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEHtmlPropertyPage __RPC_FAR * This);
        
        END_INTERFACE
    } IWebTEHtmlPropertyPageVtbl;

    interface IWebTEHtmlPropertyPage
    {
        CONST_VTBL struct IWebTEHtmlPropertyPageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEHtmlPropertyPage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEHtmlPropertyPage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEHtmlPropertyPage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEHtmlPropertyPage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEHtmlPropertyPage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEHtmlPropertyPage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEHtmlPropertyPage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEHtmlPropertyPage_get_RelativePath(This,pVal)	\
    (This)->lpVtbl -> get_RelativePath(This,pVal)

#define IWebTEHtmlPropertyPage_put_RelativePath(This,newVal)	\
    (This)->lpVtbl -> put_RelativePath(This,newVal)

#define IWebTEHtmlPropertyPage_get_Caption(This,pVal)	\
    (This)->lpVtbl -> get_Caption(This,pVal)

#define IWebTEHtmlPropertyPage_put_Caption(This,newVal)	\
    (This)->lpVtbl -> put_Caption(This,newVal)

#define IWebTEHtmlPropertyPage_get_HtmHelpPath(This,pVal)	\
    (This)->lpVtbl -> get_HtmHelpPath(This,pVal)

#define IWebTEHtmlPropertyPage_put_HtmHelpPath(This,newVal)	\
    (This)->lpVtbl -> put_HtmHelpPath(This,newVal)

#define IWebTEHtmlPropertyPage_get_HtmHelpEntry(This,pVal)	\
    (This)->lpVtbl -> get_HtmHelpEntry(This,pVal)

#define IWebTEHtmlPropertyPage_put_HtmHelpEntry(This,newVal)	\
    (This)->lpVtbl -> put_HtmHelpEntry(This,newVal)

#define IWebTEHtmlPropertyPage_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEHtmlPropertyPage_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_get_RelativePath_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEHtmlPropertyPage_get_RelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_put_RelativePath_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEHtmlPropertyPage_put_RelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_get_Caption_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEHtmlPropertyPage_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_put_Caption_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEHtmlPropertyPage_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_get_HtmHelpPath_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEHtmlPropertyPage_get_HtmHelpPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_put_HtmHelpPath_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEHtmlPropertyPage_put_HtmHelpPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_get_HtmHelpEntry_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEHtmlPropertyPage_get_HtmHelpEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_put_HtmHelpEntry_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEHtmlPropertyPage_put_HtmHelpEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_Save_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEHtmlPropertyPage_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEHtmlPropertyPage_Refresh_Proxy( 
    IWebTEHtmlPropertyPage __RPC_FAR * This);


void __RPC_STUB IWebTEHtmlPropertyPage_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEHtmlPropertyPage_INTERFACE_DEFINED__ */


#ifndef __IWebTEParametersSets_INTERFACE_DEFINED__
#define __IWebTEParametersSets_INTERFACE_DEFINED__

/* interface IWebTEParametersSets */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEParametersSets;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E831C-336C-11D3-8657-0090272F9EEB")
    IWebTEParametersSets : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            VARIANT v,
            /* [retval][out] */ IWebTEParametersSet __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Id,
            /* [retval][out] */ IWebTEParametersSet __RPC_FAR *__RPC_FAR *ppNewSet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT v) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEParametersSetsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEParametersSets __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEParametersSets __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEParametersSets __RPC_FAR * This,
            VARIANT v,
            /* [retval][out] */ IWebTEParametersSet __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEParametersSets __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWebTEParametersSets __RPC_FAR * This,
            /* [in] */ BSTR Id,
            /* [retval][out] */ IWebTEParametersSet __RPC_FAR *__RPC_FAR *ppNewSet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWebTEParametersSets __RPC_FAR * This,
            VARIANT v);
        
        END_INTERFACE
    } IWebTEParametersSetsVtbl;

    interface IWebTEParametersSets
    {
        CONST_VTBL struct IWebTEParametersSetsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEParametersSets_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEParametersSets_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEParametersSets_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEParametersSets_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEParametersSets_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEParametersSets_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEParametersSets_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEParametersSets_Item(This,v,pItem)	\
    (This)->lpVtbl -> Item(This,v,pItem)

#define IWebTEParametersSets_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IWebTEParametersSets_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IWebTEParametersSets_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEParametersSets_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEParametersSets_Add(This,Id,ppNewSet)	\
    (This)->lpVtbl -> Add(This,Id,ppNewSet)

#define IWebTEParametersSets_Remove(This,v)	\
    (This)->lpVtbl -> Remove(This,v)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_Item_Proxy( 
    IWebTEParametersSets __RPC_FAR * This,
    VARIANT v,
    /* [retval][out] */ IWebTEParametersSet __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB IWebTEParametersSets_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_get__NewEnum_Proxy( 
    IWebTEParametersSets __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEParametersSets_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_get_Count_Proxy( 
    IWebTEParametersSets __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWebTEParametersSets_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_Save_Proxy( 
    IWebTEParametersSets __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEParametersSets_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_Refresh_Proxy( 
    IWebTEParametersSets __RPC_FAR * This);


void __RPC_STUB IWebTEParametersSets_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_Add_Proxy( 
    IWebTEParametersSets __RPC_FAR * This,
    /* [in] */ BSTR Id,
    /* [retval][out] */ IWebTEParametersSet __RPC_FAR *__RPC_FAR *ppNewSet);


void __RPC_STUB IWebTEParametersSets_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSets_Remove_Proxy( 
    IWebTEParametersSets __RPC_FAR * This,
    VARIANT v);


void __RPC_STUB IWebTEParametersSets_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEParametersSets_INTERFACE_DEFINED__ */


#ifndef __IWebTEParametersSet_INTERFACE_DEFINED__
#define __IWebTEParametersSet_INTERFACE_DEFINED__

/* interface IWebTEParametersSet */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEParametersSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E831D-336C-11D3-8657-0090272F9EEB")
    IWebTEParametersSet : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveValue( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE WaitForChanges( 
            /* [in] */ DWORD hEvent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllNames( 
            /* [retval][out] */ VARIANT __RPC_FAR *pItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEParametersSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEParametersSet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEParametersSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveValue )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEParametersSet __RPC_FAR * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForChanges )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [in] */ DWORD hEvent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AllNames )( 
            IWebTEParametersSet __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pItem);
        
        END_INTERFACE
    } IWebTEParametersSetVtbl;

    interface IWebTEParametersSet
    {
        CONST_VTBL struct IWebTEParametersSetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEParametersSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEParametersSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEParametersSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEParametersSet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEParametersSet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEParametersSet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEParametersSet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEParametersSet_get_Value(This,Name,pVal)	\
    (This)->lpVtbl -> get_Value(This,Name,pVal)

#define IWebTEParametersSet_put_Value(This,Name,newVal)	\
    (This)->lpVtbl -> put_Value(This,Name,newVal)

#define IWebTEParametersSet_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define IWebTEParametersSet_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define IWebTEParametersSet_RemoveValue(This,Name)	\
    (This)->lpVtbl -> RemoveValue(This,Name)

#define IWebTEParametersSet_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEParametersSet_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEParametersSet_WaitForChanges(This,hEvent)	\
    (This)->lpVtbl -> WaitForChanges(This,hEvent)

#define IWebTEParametersSet_get_AllNames(This,pItem)	\
    (This)->lpVtbl -> get_AllNames(This,pItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_get_Value_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IWebTEParametersSet_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_put_Value_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IWebTEParametersSet_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_get_Name_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB IWebTEParametersSet_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_put_Name_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB IWebTEParametersSet_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_RemoveValue_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB IWebTEParametersSet_RemoveValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_Save_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEParametersSet_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_Refresh_Proxy( 
    IWebTEParametersSet __RPC_FAR * This);


void __RPC_STUB IWebTEParametersSet_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_WaitForChanges_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [in] */ DWORD hEvent);


void __RPC_STUB IWebTEParametersSet_WaitForChanges_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEParametersSet_get_AllNames_Proxy( 
    IWebTEParametersSet __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pItem);


void __RPC_STUB IWebTEParametersSet_get_AllNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEParametersSet_INTERFACE_DEFINED__ */


#ifndef __IWebTELog_INTERFACE_DEFINED__
#define __IWebTELog_INTERFACE_DEFINED__

/* interface IWebTELog */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTELog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E831F-336C-11D3-8657-0090272F9EEB")
    IWebTELog : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogType( 
            /* [retval][out] */ LogType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogType( 
            /* [in] */ LogType newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFilePeriod( 
            /* [retval][out] */ LogPeriodType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFilePeriod( 
            /* [in] */ LogPeriodType newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFileTruncateSize( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFileTruncateSize( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFieldSelection( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFieldSelection( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFilesCompress( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFilesCompress( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFileKeepOld( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFileKeepOld( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFileStopIfFull( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFileStopIfFull( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFileDirectory( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFileDirectory( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogSqlDataSource( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogSqlDataSource( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogSqlTableName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogSqlTableName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogFileDirectoryType( 
            /* [retval][out] */ LogFileDirectoryType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogFileDirectoryType( 
            /* [in] */ LogFileDirectoryType newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTELogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTELog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTELog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTELog __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTELog __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTELog __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogType )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ LogType __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogType )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ LogType newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFilePeriod )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ LogPeriodType __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFilePeriod )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ LogPeriodType newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFileTruncateSize )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFileTruncateSize )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFieldSelection )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFieldSelection )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFilesCompress )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFilesCompress )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFileKeepOld )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFileKeepOld )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFileStopIfFull )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFileStopIfFull )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFileDirectory )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFileDirectory )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogSqlDataSource )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogSqlDataSource )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogSqlTableName )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogSqlTableName )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogFileDirectoryType )( 
            IWebTELog __RPC_FAR * This,
            /* [retval][out] */ LogFileDirectoryType __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogFileDirectoryType )( 
            IWebTELog __RPC_FAR * This,
            /* [in] */ LogFileDirectoryType newVal);
        
        END_INTERFACE
    } IWebTELogVtbl;

    interface IWebTELog
    {
        CONST_VTBL struct IWebTELogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTELog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTELog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTELog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTELog_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTELog_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTELog_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTELog_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTELog_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTELog_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTELog_get_LogType(This,pVal)	\
    (This)->lpVtbl -> get_LogType(This,pVal)

#define IWebTELog_put_LogType(This,newVal)	\
    (This)->lpVtbl -> put_LogType(This,newVal)

#define IWebTELog_get_LogFilePeriod(This,pVal)	\
    (This)->lpVtbl -> get_LogFilePeriod(This,pVal)

#define IWebTELog_put_LogFilePeriod(This,newVal)	\
    (This)->lpVtbl -> put_LogFilePeriod(This,newVal)

#define IWebTELog_get_LogFileTruncateSize(This,pVal)	\
    (This)->lpVtbl -> get_LogFileTruncateSize(This,pVal)

#define IWebTELog_put_LogFileTruncateSize(This,newVal)	\
    (This)->lpVtbl -> put_LogFileTruncateSize(This,newVal)

#define IWebTELog_get_LogFieldSelection(This,pVal)	\
    (This)->lpVtbl -> get_LogFieldSelection(This,pVal)

#define IWebTELog_put_LogFieldSelection(This,newVal)	\
    (This)->lpVtbl -> put_LogFieldSelection(This,newVal)

#define IWebTELog_get_LogFilesCompress(This,pVal)	\
    (This)->lpVtbl -> get_LogFilesCompress(This,pVal)

#define IWebTELog_put_LogFilesCompress(This,newVal)	\
    (This)->lpVtbl -> put_LogFilesCompress(This,newVal)

#define IWebTELog_get_LogFileKeepOld(This,pVal)	\
    (This)->lpVtbl -> get_LogFileKeepOld(This,pVal)

#define IWebTELog_put_LogFileKeepOld(This,newVal)	\
    (This)->lpVtbl -> put_LogFileKeepOld(This,newVal)

#define IWebTELog_get_LogFileStopIfFull(This,pVal)	\
    (This)->lpVtbl -> get_LogFileStopIfFull(This,pVal)

#define IWebTELog_put_LogFileStopIfFull(This,newVal)	\
    (This)->lpVtbl -> put_LogFileStopIfFull(This,newVal)

#define IWebTELog_get_LogFileDirectory(This,pVal)	\
    (This)->lpVtbl -> get_LogFileDirectory(This,pVal)

#define IWebTELog_put_LogFileDirectory(This,newVal)	\
    (This)->lpVtbl -> put_LogFileDirectory(This,newVal)

#define IWebTELog_get_LogSqlDataSource(This,pVal)	\
    (This)->lpVtbl -> get_LogSqlDataSource(This,pVal)

#define IWebTELog_put_LogSqlDataSource(This,newVal)	\
    (This)->lpVtbl -> put_LogSqlDataSource(This,newVal)

#define IWebTELog_get_LogSqlTableName(This,pVal)	\
    (This)->lpVtbl -> get_LogSqlTableName(This,pVal)

#define IWebTELog_put_LogSqlTableName(This,newVal)	\
    (This)->lpVtbl -> put_LogSqlTableName(This,newVal)

#define IWebTELog_get_LogFileDirectoryType(This,pVal)	\
    (This)->lpVtbl -> get_LogFileDirectoryType(This,pVal)

#define IWebTELog_put_LogFileDirectoryType(This,newVal)	\
    (This)->lpVtbl -> put_LogFileDirectoryType(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTELog_Save_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTELog_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTELog_Refresh_Proxy( 
    IWebTELog __RPC_FAR * This);


void __RPC_STUB IWebTELog_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogType_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ LogType __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogType_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ LogType newVal);


void __RPC_STUB IWebTELog_put_LogType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFilePeriod_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ LogPeriodType __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFilePeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFilePeriod_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ LogPeriodType newVal);


void __RPC_STUB IWebTELog_put_LogFilePeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFileTruncateSize_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFileTruncateSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFileTruncateSize_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTELog_put_LogFileTruncateSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFieldSelection_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFieldSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFieldSelection_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTELog_put_LogFieldSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFilesCompress_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFilesCompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFilesCompress_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTELog_put_LogFilesCompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFileKeepOld_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFileKeepOld_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFileKeepOld_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTELog_put_LogFileKeepOld_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFileStopIfFull_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFileStopIfFull_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFileStopIfFull_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTELog_put_LogFileStopIfFull_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFileDirectory_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFileDirectory_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTELog_put_LogFileDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogSqlDataSource_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogSqlDataSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogSqlDataSource_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTELog_put_LogSqlDataSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogSqlTableName_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogSqlTableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogSqlTableName_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTELog_put_LogSqlTableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTELog_get_LogFileDirectoryType_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [retval][out] */ LogFileDirectoryType __RPC_FAR *pVal);


void __RPC_STUB IWebTELog_get_LogFileDirectoryType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTELog_put_LogFileDirectoryType_Proxy( 
    IWebTELog __RPC_FAR * This,
    /* [in] */ LogFileDirectoryType newVal);


void __RPC_STUB IWebTELog_put_LogFileDirectoryType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTELog_INTERFACE_DEFINED__ */


#ifndef __IWebTEApplications_INTERFACE_DEFINED__
#define __IWebTEApplications_INTERFACE_DEFINED__

/* interface IWebTEApplications */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEApplications;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8321-336C-11D3-8657-0090272F9EEB")
    IWebTEApplications : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR HomePage,
            /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEApplicationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEApplications __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEApplications __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEApplications __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IWebTEApplications __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEApplications __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IWebTEApplications __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR HomePage,
            /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IWebTEApplications __RPC_FAR * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEApplications __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEApplications __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        END_INTERFACE
    } IWebTEApplicationsVtbl;

    interface IWebTEApplications
    {
        CONST_VTBL struct IWebTEApplicationsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEApplications_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEApplications_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEApplications_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEApplications_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEApplications_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEApplications_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEApplications_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEApplications_get_Count(This,retval)	\
    (This)->lpVtbl -> get_Count(This,retval)

#define IWebTEApplications_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#define IWebTEApplications_Item(This,Index,retval)	\
    (This)->lpVtbl -> Item(This,Index,retval)

#define IWebTEApplications_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define IWebTEApplications_Add(This,Name,HomePage,ppVal)	\
    (This)->lpVtbl -> Add(This,Name,HomePage,ppVal)

#define IWebTEApplications_Remove(This,v)	\
    (This)->lpVtbl -> Remove(This,v)

#define IWebTEApplications_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEApplications_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_get_Count_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IWebTEApplications_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_get_VendorDataSets_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEApplications_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_Item_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IWebTEApplications_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_get__NewEnum_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *retval);


void __RPC_STUB IWebTEApplications_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_Add_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR HomePage,
    /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *ppVal);


void __RPC_STUB IWebTEApplications_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_Remove_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IWebTEApplications_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_Refresh_Proxy( 
    IWebTEApplications __RPC_FAR * This);


void __RPC_STUB IWebTEApplications_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplications_Save_Proxy( 
    IWebTEApplications __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEApplications_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEApplications_INTERFACE_DEFINED__ */


#ifndef __IWebTEApplication_INTERFACE_DEFINED__
#define __IWebTEApplication_INTERFACE_DEFINED__

/* interface IWebTEApplication */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebTEApplication;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83E8322-336C-11D3-8657-0090272F9EEB")
    IWebTEApplication : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VendorDataSets( 
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HomePage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HomePage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputTerminator( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputTerminator( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HomeKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HomeKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OperatorKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OperatorKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OperatorExtension( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OperatorExtension( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressButtonKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressButtonKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SkipButtonKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SkipButtonKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SetCheckBoxKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SetCheckBoxKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClearCheckBoxKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClearCheckBoxKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IgnoreNavigationKeysTillTermination( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IgnoreNavigationKeysTillTermination( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DetectABCD( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DetectABCD( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxRecordTime( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxRecordTime( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordStopSilenceTime( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordStopSilenceTime( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InvalidKeyAnnouncement( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InvalidKeyAnnouncement( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeoutAnnouncement( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimeoutAnnouncement( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxRetries( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxRetries( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FirstTimeoutInterval( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstTimeoutInterval( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InterTimeoutInterval( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InterTimeoutInterval( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecurringErrorPage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecurringErrorPage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RenderTTS( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RenderTTS( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TTSParameters( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TTSParameters( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SRParameters( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SRParameters( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogEventSelection( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogEventSelection( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DelayedAnswering( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DelayedAnswering( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FinalPage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FinalPage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RenderTablesAsTabularData( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RenderTablesAsTabularData( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitialAutoNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InitialAutoNumber( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShutdownTime( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShutdownTime( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShutdownAnnouncement( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShutdownAnnouncement( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SRThreshold( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SRThreshold( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseSR( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseSR( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfirmBefore( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConfirmBefore( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfirmAfter( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConfirmAfter( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OfferItems( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OfferItems( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressButtonPhrases( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressButtonPhrases( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SkipButtonPhrases( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SkipButtonPhrases( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SetCheckBoxPhrases( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SetCheckBoxPhrases( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClearCheckBoxPhrases( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClearCheckBoxPhrases( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NavigationAnnouncement( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NavigationAnnouncement( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RepeatMenuAnnouncement( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RepeatMenuAnnouncement( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RepeatMenuKey( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RepeatMenuKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DownloadControlFlags( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DownloadControlFlags( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OperatorTransferType( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OperatorTransferType( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Vendor( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Vendor( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableFullConfiguration( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableFullConfiguration( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordStopOnAnyKey( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordStopOnAnyKey( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTEApplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEApplication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEApplication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEApplication __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebTEApplication __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IWebTEApplication __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VendorDataSets )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomePage )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomePage )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputTerminator )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputTerminator )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomeKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomeKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperatorKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OperatorKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperatorExtension )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OperatorExtension )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressButtonKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressButtonKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SkipButtonKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SkipButtonKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SetCheckBoxKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SetCheckBoxKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClearCheckBoxKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearCheckBoxKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IgnoreNavigationKeysTillTermination )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IgnoreNavigationKeysTillTermination )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DetectABCD )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DetectABCD )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxRecordTime )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxRecordTime )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecordStopSilenceTime )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecordStopSilenceTime )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InvalidKeyAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InvalidKeyAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeoutAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TimeoutAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxRetries )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxRetries )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FirstTimeoutInterval )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FirstTimeoutInterval )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InterTimeoutInterval )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InterTimeoutInterval )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecurringErrorPage )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecurringErrorPage )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RenderTTS )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RenderTTS )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TTSParameters )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TTSParameters )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SRParameters )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SRParameters )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogEventSelection )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogEventSelection )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DelayedAnswering )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DelayedAnswering )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FinalPage )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FinalPage )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RenderTablesAsTabularData )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RenderTablesAsTabularData )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitialAutoNumber )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InitialAutoNumber )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShutdownTime )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShutdownTime )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShutdownAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShutdownAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SRThreshold )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SRThreshold )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseSR )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseSR )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConfirmBefore )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConfirmBefore )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConfirmAfter )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConfirmAfter )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OfferItems )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OfferItems )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressButtonPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressButtonPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SkipButtonPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SkipButtonPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SetCheckBoxPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SetCheckBoxPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClearCheckBoxPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClearCheckBoxPhrases )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NavigationAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NavigationAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RepeatMenuAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RepeatMenuAnnouncement )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RepeatMenuKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RepeatMenuKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DownloadControlFlags )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DownloadControlFlags )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperatorTransferType )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OperatorTransferType )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Vendor )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Vendor )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableFullConfiguration )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableFullConfiguration )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecordStopOnAnyKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecordStopOnAnyKey )( 
            IWebTEApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IWebTEApplicationVtbl;

    interface IWebTEApplication
    {
        CONST_VTBL struct IWebTEApplicationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEApplication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEApplication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEApplication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEApplication_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEApplication_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEApplication_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEApplication_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebTEApplication_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebTEApplication_Save(This,SaveOnlyIfCurrent)	\
    (This)->lpVtbl -> Save(This,SaveOnlyIfCurrent)

#define IWebTEApplication_get_VendorDataSets(This,pVal)	\
    (This)->lpVtbl -> get_VendorDataSets(This,pVal)

#define IWebTEApplication_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IWebTEApplication_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IWebTEApplication_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IWebTEApplication_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define IWebTEApplication_get_HomePage(This,pVal)	\
    (This)->lpVtbl -> get_HomePage(This,pVal)

#define IWebTEApplication_put_HomePage(This,newVal)	\
    (This)->lpVtbl -> put_HomePage(This,newVal)

#define IWebTEApplication_get_InputTerminator(This,pVal)	\
    (This)->lpVtbl -> get_InputTerminator(This,pVal)

#define IWebTEApplication_put_InputTerminator(This,newVal)	\
    (This)->lpVtbl -> put_InputTerminator(This,newVal)

#define IWebTEApplication_get_BackKey(This,pVal)	\
    (This)->lpVtbl -> get_BackKey(This,pVal)

#define IWebTEApplication_put_BackKey(This,newVal)	\
    (This)->lpVtbl -> put_BackKey(This,newVal)

#define IWebTEApplication_get_HomeKey(This,pVal)	\
    (This)->lpVtbl -> get_HomeKey(This,pVal)

#define IWebTEApplication_put_HomeKey(This,newVal)	\
    (This)->lpVtbl -> put_HomeKey(This,newVal)

#define IWebTEApplication_get_OperatorKey(This,pVal)	\
    (This)->lpVtbl -> get_OperatorKey(This,pVal)

#define IWebTEApplication_put_OperatorKey(This,newVal)	\
    (This)->lpVtbl -> put_OperatorKey(This,newVal)

#define IWebTEApplication_get_OperatorExtension(This,pVal)	\
    (This)->lpVtbl -> get_OperatorExtension(This,pVal)

#define IWebTEApplication_put_OperatorExtension(This,newVal)	\
    (This)->lpVtbl -> put_OperatorExtension(This,newVal)

#define IWebTEApplication_get_PressButtonKey(This,pVal)	\
    (This)->lpVtbl -> get_PressButtonKey(This,pVal)

#define IWebTEApplication_put_PressButtonKey(This,newVal)	\
    (This)->lpVtbl -> put_PressButtonKey(This,newVal)

#define IWebTEApplication_get_SkipButtonKey(This,pVal)	\
    (This)->lpVtbl -> get_SkipButtonKey(This,pVal)

#define IWebTEApplication_put_SkipButtonKey(This,newVal)	\
    (This)->lpVtbl -> put_SkipButtonKey(This,newVal)

#define IWebTEApplication_get_SetCheckBoxKey(This,pVal)	\
    (This)->lpVtbl -> get_SetCheckBoxKey(This,pVal)

#define IWebTEApplication_put_SetCheckBoxKey(This,newVal)	\
    (This)->lpVtbl -> put_SetCheckBoxKey(This,newVal)

#define IWebTEApplication_get_ClearCheckBoxKey(This,pVal)	\
    (This)->lpVtbl -> get_ClearCheckBoxKey(This,pVal)

#define IWebTEApplication_put_ClearCheckBoxKey(This,newVal)	\
    (This)->lpVtbl -> put_ClearCheckBoxKey(This,newVal)

#define IWebTEApplication_get_IgnoreNavigationKeysTillTermination(This,pVal)	\
    (This)->lpVtbl -> get_IgnoreNavigationKeysTillTermination(This,pVal)

#define IWebTEApplication_put_IgnoreNavigationKeysTillTermination(This,newVal)	\
    (This)->lpVtbl -> put_IgnoreNavigationKeysTillTermination(This,newVal)

#define IWebTEApplication_get_DetectABCD(This,pVal)	\
    (This)->lpVtbl -> get_DetectABCD(This,pVal)

#define IWebTEApplication_put_DetectABCD(This,newVal)	\
    (This)->lpVtbl -> put_DetectABCD(This,newVal)

#define IWebTEApplication_get_MaxRecordTime(This,pVal)	\
    (This)->lpVtbl -> get_MaxRecordTime(This,pVal)

#define IWebTEApplication_put_MaxRecordTime(This,newVal)	\
    (This)->lpVtbl -> put_MaxRecordTime(This,newVal)

#define IWebTEApplication_get_RecordStopSilenceTime(This,pVal)	\
    (This)->lpVtbl -> get_RecordStopSilenceTime(This,pVal)

#define IWebTEApplication_put_RecordStopSilenceTime(This,newVal)	\
    (This)->lpVtbl -> put_RecordStopSilenceTime(This,newVal)

#define IWebTEApplication_get_InvalidKeyAnnouncement(This,pVal)	\
    (This)->lpVtbl -> get_InvalidKeyAnnouncement(This,pVal)

#define IWebTEApplication_put_InvalidKeyAnnouncement(This,newVal)	\
    (This)->lpVtbl -> put_InvalidKeyAnnouncement(This,newVal)

#define IWebTEApplication_get_TimeoutAnnouncement(This,pVal)	\
    (This)->lpVtbl -> get_TimeoutAnnouncement(This,pVal)

#define IWebTEApplication_put_TimeoutAnnouncement(This,newVal)	\
    (This)->lpVtbl -> put_TimeoutAnnouncement(This,newVal)

#define IWebTEApplication_get_MaxRetries(This,pVal)	\
    (This)->lpVtbl -> get_MaxRetries(This,pVal)

#define IWebTEApplication_put_MaxRetries(This,newVal)	\
    (This)->lpVtbl -> put_MaxRetries(This,newVal)

#define IWebTEApplication_get_FirstTimeoutInterval(This,pVal)	\
    (This)->lpVtbl -> get_FirstTimeoutInterval(This,pVal)

#define IWebTEApplication_put_FirstTimeoutInterval(This,newVal)	\
    (This)->lpVtbl -> put_FirstTimeoutInterval(This,newVal)

#define IWebTEApplication_get_InterTimeoutInterval(This,pVal)	\
    (This)->lpVtbl -> get_InterTimeoutInterval(This,pVal)

#define IWebTEApplication_put_InterTimeoutInterval(This,newVal)	\
    (This)->lpVtbl -> put_InterTimeoutInterval(This,newVal)

#define IWebTEApplication_get_RecurringErrorPage(This,pVal)	\
    (This)->lpVtbl -> get_RecurringErrorPage(This,pVal)

#define IWebTEApplication_put_RecurringErrorPage(This,newVal)	\
    (This)->lpVtbl -> put_RecurringErrorPage(This,newVal)

#define IWebTEApplication_get_RenderTTS(This,pVal)	\
    (This)->lpVtbl -> get_RenderTTS(This,pVal)

#define IWebTEApplication_put_RenderTTS(This,newVal)	\
    (This)->lpVtbl -> put_RenderTTS(This,newVal)

#define IWebTEApplication_get_TTSParameters(This,pVal)	\
    (This)->lpVtbl -> get_TTSParameters(This,pVal)

#define IWebTEApplication_put_TTSParameters(This,newVal)	\
    (This)->lpVtbl -> put_TTSParameters(This,newVal)

#define IWebTEApplication_get_SRParameters(This,pVal)	\
    (This)->lpVtbl -> get_SRParameters(This,pVal)

#define IWebTEApplication_put_SRParameters(This,newVal)	\
    (This)->lpVtbl -> put_SRParameters(This,newVal)

#define IWebTEApplication_get_LogEventSelection(This,pVal)	\
    (This)->lpVtbl -> get_LogEventSelection(This,pVal)

#define IWebTEApplication_put_LogEventSelection(This,newVal)	\
    (This)->lpVtbl -> put_LogEventSelection(This,newVal)

#define IWebTEApplication_get_DelayedAnswering(This,pVal)	\
    (This)->lpVtbl -> get_DelayedAnswering(This,pVal)

#define IWebTEApplication_put_DelayedAnswering(This,newVal)	\
    (This)->lpVtbl -> put_DelayedAnswering(This,newVal)

#define IWebTEApplication_get_FinalPage(This,pVal)	\
    (This)->lpVtbl -> get_FinalPage(This,pVal)

#define IWebTEApplication_put_FinalPage(This,newVal)	\
    (This)->lpVtbl -> put_FinalPage(This,newVal)

#define IWebTEApplication_get_RenderTablesAsTabularData(This,pVal)	\
    (This)->lpVtbl -> get_RenderTablesAsTabularData(This,pVal)

#define IWebTEApplication_put_RenderTablesAsTabularData(This,newVal)	\
    (This)->lpVtbl -> put_RenderTablesAsTabularData(This,newVal)

#define IWebTEApplication_get_InitialAutoNumber(This,pVal)	\
    (This)->lpVtbl -> get_InitialAutoNumber(This,pVal)

#define IWebTEApplication_put_InitialAutoNumber(This,newVal)	\
    (This)->lpVtbl -> put_InitialAutoNumber(This,newVal)

#define IWebTEApplication_get_ShutdownTime(This,pVal)	\
    (This)->lpVtbl -> get_ShutdownTime(This,pVal)

#define IWebTEApplication_put_ShutdownTime(This,newVal)	\
    (This)->lpVtbl -> put_ShutdownTime(This,newVal)

#define IWebTEApplication_get_ShutdownAnnouncement(This,pVal)	\
    (This)->lpVtbl -> get_ShutdownAnnouncement(This,pVal)

#define IWebTEApplication_put_ShutdownAnnouncement(This,newVal)	\
    (This)->lpVtbl -> put_ShutdownAnnouncement(This,newVal)

#define IWebTEApplication_get_SRThreshold(This,pVal)	\
    (This)->lpVtbl -> get_SRThreshold(This,pVal)

#define IWebTEApplication_put_SRThreshold(This,newVal)	\
    (This)->lpVtbl -> put_SRThreshold(This,newVal)

#define IWebTEApplication_get_UseSR(This,pVal)	\
    (This)->lpVtbl -> get_UseSR(This,pVal)

#define IWebTEApplication_put_UseSR(This,newVal)	\
    (This)->lpVtbl -> put_UseSR(This,newVal)

#define IWebTEApplication_get_ConfirmBefore(This,pVal)	\
    (This)->lpVtbl -> get_ConfirmBefore(This,pVal)

#define IWebTEApplication_put_ConfirmBefore(This,newVal)	\
    (This)->lpVtbl -> put_ConfirmBefore(This,newVal)

#define IWebTEApplication_get_ConfirmAfter(This,pVal)	\
    (This)->lpVtbl -> get_ConfirmAfter(This,pVal)

#define IWebTEApplication_put_ConfirmAfter(This,newVal)	\
    (This)->lpVtbl -> put_ConfirmAfter(This,newVal)

#define IWebTEApplication_get_OfferItems(This,pVal)	\
    (This)->lpVtbl -> get_OfferItems(This,pVal)

#define IWebTEApplication_put_OfferItems(This,newVal)	\
    (This)->lpVtbl -> put_OfferItems(This,newVal)

#define IWebTEApplication_get_PressButtonPhrases(This,pVal)	\
    (This)->lpVtbl -> get_PressButtonPhrases(This,pVal)

#define IWebTEApplication_put_PressButtonPhrases(This,newVal)	\
    (This)->lpVtbl -> put_PressButtonPhrases(This,newVal)

#define IWebTEApplication_get_SkipButtonPhrases(This,pVal)	\
    (This)->lpVtbl -> get_SkipButtonPhrases(This,pVal)

#define IWebTEApplication_put_SkipButtonPhrases(This,newVal)	\
    (This)->lpVtbl -> put_SkipButtonPhrases(This,newVal)

#define IWebTEApplication_get_SetCheckBoxPhrases(This,pVal)	\
    (This)->lpVtbl -> get_SetCheckBoxPhrases(This,pVal)

#define IWebTEApplication_put_SetCheckBoxPhrases(This,newVal)	\
    (This)->lpVtbl -> put_SetCheckBoxPhrases(This,newVal)

#define IWebTEApplication_get_ClearCheckBoxPhrases(This,pVal)	\
    (This)->lpVtbl -> get_ClearCheckBoxPhrases(This,pVal)

#define IWebTEApplication_put_ClearCheckBoxPhrases(This,newVal)	\
    (This)->lpVtbl -> put_ClearCheckBoxPhrases(This,newVal)

#define IWebTEApplication_get_NavigationAnnouncement(This,pVal)	\
    (This)->lpVtbl -> get_NavigationAnnouncement(This,pVal)

#define IWebTEApplication_put_NavigationAnnouncement(This,newVal)	\
    (This)->lpVtbl -> put_NavigationAnnouncement(This,newVal)

#define IWebTEApplication_get_RepeatMenuAnnouncement(This,pVal)	\
    (This)->lpVtbl -> get_RepeatMenuAnnouncement(This,pVal)

#define IWebTEApplication_put_RepeatMenuAnnouncement(This,newVal)	\
    (This)->lpVtbl -> put_RepeatMenuAnnouncement(This,newVal)

#define IWebTEApplication_get_RepeatMenuKey(This,pVal)	\
    (This)->lpVtbl -> get_RepeatMenuKey(This,pVal)

#define IWebTEApplication_put_RepeatMenuKey(This,newVal)	\
    (This)->lpVtbl -> put_RepeatMenuKey(This,newVal)

#define IWebTEApplication_get_DownloadControlFlags(This,pVal)	\
    (This)->lpVtbl -> get_DownloadControlFlags(This,pVal)

#define IWebTEApplication_put_DownloadControlFlags(This,newVal)	\
    (This)->lpVtbl -> put_DownloadControlFlags(This,newVal)

#define IWebTEApplication_get_OperatorTransferType(This,pVal)	\
    (This)->lpVtbl -> get_OperatorTransferType(This,pVal)

#define IWebTEApplication_put_OperatorTransferType(This,newVal)	\
    (This)->lpVtbl -> put_OperatorTransferType(This,newVal)

#define IWebTEApplication_get_Vendor(This,pVal)	\
    (This)->lpVtbl -> get_Vendor(This,pVal)

#define IWebTEApplication_put_Vendor(This,newVal)	\
    (This)->lpVtbl -> put_Vendor(This,newVal)

#define IWebTEApplication_get_EnableFullConfiguration(This,pVal)	\
    (This)->lpVtbl -> get_EnableFullConfiguration(This,pVal)

#define IWebTEApplication_put_EnableFullConfiguration(This,newVal)	\
    (This)->lpVtbl -> put_EnableFullConfiguration(This,newVal)

#define IWebTEApplication_get_RecordStopOnAnyKey(This,pVal)	\
    (This)->lpVtbl -> get_RecordStopOnAnyKey(This,pVal)

#define IWebTEApplication_put_RecordStopOnAnyKey(This,newVal)	\
    (This)->lpVtbl -> put_RecordStopOnAnyKey(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_Refresh_Proxy( 
    IWebTEApplication __RPC_FAR * This);


void __RPC_STUB IWebTEApplication_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_Save_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL SaveOnlyIfCurrent);


void __RPC_STUB IWebTEApplication_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_VendorDataSets_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ IWebTEVendorDataSets __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_VendorDataSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_Name_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_Name_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_Description_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_Description_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_HomePage_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_HomePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_HomePage_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_HomePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_InputTerminator_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_InputTerminator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_InputTerminator_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_InputTerminator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_BackKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_BackKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_BackKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_BackKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_HomeKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_HomeKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_HomeKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_HomeKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_OperatorKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_OperatorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_OperatorKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_OperatorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_OperatorExtension_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_OperatorExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_OperatorExtension_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_OperatorExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_PressButtonKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_PressButtonKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_PressButtonKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_PressButtonKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_SkipButtonKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_SkipButtonKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_SkipButtonKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_SkipButtonKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_SetCheckBoxKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_SetCheckBoxKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_SetCheckBoxKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_SetCheckBoxKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_ClearCheckBoxKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_ClearCheckBoxKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_ClearCheckBoxKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_ClearCheckBoxKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_IgnoreNavigationKeysTillTermination_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_IgnoreNavigationKeysTillTermination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_IgnoreNavigationKeysTillTermination_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_IgnoreNavigationKeysTillTermination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_DetectABCD_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_DetectABCD_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_DetectABCD_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_DetectABCD_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_MaxRecordTime_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_MaxRecordTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_MaxRecordTime_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_MaxRecordTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RecordStopSilenceTime_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RecordStopSilenceTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RecordStopSilenceTime_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_RecordStopSilenceTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_InvalidKeyAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_InvalidKeyAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_InvalidKeyAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_InvalidKeyAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_TimeoutAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_TimeoutAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_TimeoutAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_TimeoutAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_MaxRetries_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_MaxRetries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_MaxRetries_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_MaxRetries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_FirstTimeoutInterval_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_FirstTimeoutInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_FirstTimeoutInterval_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_FirstTimeoutInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_InterTimeoutInterval_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_InterTimeoutInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_InterTimeoutInterval_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_InterTimeoutInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RecurringErrorPage_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RecurringErrorPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RecurringErrorPage_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_RecurringErrorPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RenderTTS_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RenderTTS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RenderTTS_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_RenderTTS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_TTSParameters_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_TTSParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_TTSParameters_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_TTSParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_SRParameters_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_SRParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_SRParameters_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_SRParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_LogEventSelection_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_LogEventSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_LogEventSelection_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_LogEventSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_DelayedAnswering_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_DelayedAnswering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_DelayedAnswering_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_DelayedAnswering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_FinalPage_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_FinalPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_FinalPage_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_FinalPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RenderTablesAsTabularData_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RenderTablesAsTabularData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RenderTablesAsTabularData_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_RenderTablesAsTabularData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_InitialAutoNumber_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_InitialAutoNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_InitialAutoNumber_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_InitialAutoNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_ShutdownTime_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_ShutdownTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_ShutdownTime_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_ShutdownTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_ShutdownAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_ShutdownAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_ShutdownAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_ShutdownAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_SRThreshold_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_SRThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_SRThreshold_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_SRThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_UseSR_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_UseSR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_UseSR_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_UseSR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_ConfirmBefore_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_ConfirmBefore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_ConfirmBefore_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_ConfirmBefore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_ConfirmAfter_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_ConfirmAfter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_ConfirmAfter_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_ConfirmAfter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_OfferItems_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_OfferItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_OfferItems_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_OfferItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_PressButtonPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_PressButtonPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_PressButtonPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_PressButtonPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_SkipButtonPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_SkipButtonPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_SkipButtonPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_SkipButtonPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_SetCheckBoxPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_SetCheckBoxPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_SetCheckBoxPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_SetCheckBoxPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_ClearCheckBoxPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_ClearCheckBoxPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_ClearCheckBoxPhrases_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_ClearCheckBoxPhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_NavigationAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_NavigationAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_NavigationAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_NavigationAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RepeatMenuAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RepeatMenuAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RepeatMenuAnnouncement_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_RepeatMenuAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RepeatMenuKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RepeatMenuKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RepeatMenuKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_RepeatMenuKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_DownloadControlFlags_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_DownloadControlFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_DownloadControlFlags_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_DownloadControlFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_OperatorTransferType_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_OperatorTransferType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_OperatorTransferType_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IWebTEApplication_put_OperatorTransferType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_Vendor_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_Vendor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_Vendor_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWebTEApplication_put_Vendor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_EnableFullConfiguration_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_EnableFullConfiguration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_EnableFullConfiguration_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_EnableFullConfiguration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_get_RecordStopOnAnyKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IWebTEApplication_get_RecordStopOnAnyKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWebTEApplication_put_RecordStopOnAnyKey_Proxy( 
    IWebTEApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWebTEApplication_put_RecordStopOnAnyKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTEApplication_INTERFACE_DEFINED__ */


#ifndef __ITelephonyStepConstrains_INTERFACE_DEFINED__
#define __ITelephonyStepConstrains_INTERFACE_DEFINED__

/* interface ITelephonyStepConstrains */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITelephonyStepConstrains;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD0-33A8-11D3-8658-0090272F9EEB")
    ITelephonyStepConstrains : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TerminationString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LegalDigits( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitialNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LowerBoundary( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperBoundary( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LowerBlocked( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperBlocked( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITelephonyStepConstrainsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITelephonyStepConstrains __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITelephonyStepConstrains __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerminationString )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LegalDigits )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitialNumber )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LowerBoundary )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperBoundary )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LowerBlocked )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperBlocked )( 
            ITelephonyStepConstrains __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITelephonyStepConstrainsVtbl;

    interface ITelephonyStepConstrains
    {
        CONST_VTBL struct ITelephonyStepConstrainsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITelephonyStepConstrains_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITelephonyStepConstrains_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITelephonyStepConstrains_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITelephonyStepConstrains_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITelephonyStepConstrains_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITelephonyStepConstrains_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITelephonyStepConstrains_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITelephonyStepConstrains_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITelephonyStepConstrains_get_TerminationString(This,pVal)	\
    (This)->lpVtbl -> get_TerminationString(This,pVal)

#define ITelephonyStepConstrains_get_LegalDigits(This,pVal)	\
    (This)->lpVtbl -> get_LegalDigits(This,pVal)

#define ITelephonyStepConstrains_get_InitialNumber(This,pVal)	\
    (This)->lpVtbl -> get_InitialNumber(This,pVal)

#define ITelephonyStepConstrains_get_LowerBoundary(This,pVal)	\
    (This)->lpVtbl -> get_LowerBoundary(This,pVal)

#define ITelephonyStepConstrains_get_UpperBoundary(This,pVal)	\
    (This)->lpVtbl -> get_UpperBoundary(This,pVal)

#define ITelephonyStepConstrains_get_LowerBlocked(This,pVal)	\
    (This)->lpVtbl -> get_LowerBlocked(This,pVal)

#define ITelephonyStepConstrains_get_UpperBlocked(This,pVal)	\
    (This)->lpVtbl -> get_UpperBlocked(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_Type_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_TerminationString_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_TerminationString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_LegalDigits_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_LegalDigits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_InitialNumber_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_InitialNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_LowerBoundary_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_LowerBoundary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_UpperBoundary_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_UpperBoundary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_LowerBlocked_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_LowerBlocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStepConstrains_get_UpperBlocked_Proxy( 
    ITelephonyStepConstrains __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITelephonyStepConstrains_get_UpperBlocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITelephonyStepConstrains_INTERFACE_DEFINED__ */


#ifndef __ISession_INTERFACE_DEFINED__
#define __ISession_INTERFACE_DEFINED__

/* interface ISession */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD1-33A8-11D3-8658-0090272F9EEB")
    ISession : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT __RPC_FAR *pnewVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Value( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT __RPC_FAR *pnewVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastVisitedPage( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastVisitedPage) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastVisitedTagID( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastVisitedTagID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionState( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSessionState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrServerName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSessionName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISession __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISession __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISession __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISession __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISession __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            ISession __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            ISession __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT __RPC_FAR *pnewVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Value )( 
            ISession __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT __RPC_FAR *pnewVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastVisitedPage )( 
            ISession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastVisitedPage);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastVisitedTagID )( 
            ISession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLastVisitedTagID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionState )( 
            ISession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSessionState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServerName )( 
            ISession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrServerName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionName )( 
            ISession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrSessionName);
        
        END_INTERFACE
    } ISessionVtbl;

    interface ISession
    {
        CONST_VTBL struct ISessionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISession_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISession_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISession_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISession_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISession_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISession_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISession_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISession_get_Value(This,bstrName,pVal)	\
    (This)->lpVtbl -> get_Value(This,bstrName,pVal)

#define ISession_put_Value(This,bstrName,pnewVal)	\
    (This)->lpVtbl -> put_Value(This,bstrName,pnewVal)

#define ISession_putref_Value(This,bstrName,pnewVal)	\
    (This)->lpVtbl -> putref_Value(This,bstrName,pnewVal)

#define ISession_get_LastVisitedPage(This,pbstrLastVisitedPage)	\
    (This)->lpVtbl -> get_LastVisitedPage(This,pbstrLastVisitedPage)

#define ISession_get_LastVisitedTagID(This,pbstrLastVisitedTagID)	\
    (This)->lpVtbl -> get_LastVisitedTagID(This,pbstrLastVisitedTagID)

#define ISession_get_SessionState(This,pbstrSessionState)	\
    (This)->lpVtbl -> get_SessionState(This,pbstrSessionState)

#define ISession_get_ServerName(This,pbstrServerName)	\
    (This)->lpVtbl -> get_ServerName(This,pbstrServerName)

#define ISession_get_SessionName(This,pbstrSessionName)	\
    (This)->lpVtbl -> get_SessionName(This,pbstrSessionName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISession_get_Value_Proxy( 
    ISession __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ISession_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISession_put_Value_Proxy( 
    ISession __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT __RPC_FAR *pnewVal);


void __RPC_STUB ISession_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ISession_putref_Value_Proxy( 
    ISession __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT __RPC_FAR *pnewVal);


void __RPC_STUB ISession_putref_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISession_get_LastVisitedPage_Proxy( 
    ISession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrLastVisitedPage);


void __RPC_STUB ISession_get_LastVisitedPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISession_get_LastVisitedTagID_Proxy( 
    ISession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrLastVisitedTagID);


void __RPC_STUB ISession_get_LastVisitedTagID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISession_get_SessionState_Proxy( 
    ISession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrSessionState);


void __RPC_STUB ISession_get_SessionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISession_get_ServerName_Proxy( 
    ISession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrServerName);


void __RPC_STUB ISession_get_ServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISession_get_SessionName_Proxy( 
    ISession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrSessionName);


void __RPC_STUB ISession_get_SessionName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISession_INTERFACE_DEFINED__ */


#ifndef __ITTSMode_INTERFACE_DEFINED__
#define __ITTSMode_INTERFACE_DEFINED__

/* interface ITTSMode */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITTSMode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD2-33A8-11D3-8658-0090272F9EEB")
    ITTSMode : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EngineID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MfgName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProductName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ModeID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ModeName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LanguageID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dialect( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Speaker( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Gender( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Age( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Features( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Interfaces( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EngineFeatures( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTSModeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTSMode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTSMode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTSMode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTSMode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTSMode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTSMode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTSMode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EngineID )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MfgName )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProductName )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModeID )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModeName )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LanguageID )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dialect )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speaker )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Gender )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Age )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Features )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Interfaces )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EngineFeatures )( 
            ITTSMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITTSModeVtbl;

    interface ITTSMode
    {
        CONST_VTBL struct ITTSModeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTSMode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTSMode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTSMode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTSMode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTSMode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTSMode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTSMode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTSMode_get_EngineID(This,pVal)	\
    (This)->lpVtbl -> get_EngineID(This,pVal)

#define ITTSMode_get_MfgName(This,pVal)	\
    (This)->lpVtbl -> get_MfgName(This,pVal)

#define ITTSMode_get_ProductName(This,pVal)	\
    (This)->lpVtbl -> get_ProductName(This,pVal)

#define ITTSMode_get_ModeID(This,pVal)	\
    (This)->lpVtbl -> get_ModeID(This,pVal)

#define ITTSMode_get_ModeName(This,pVal)	\
    (This)->lpVtbl -> get_ModeName(This,pVal)

#define ITTSMode_get_LanguageID(This,pVal)	\
    (This)->lpVtbl -> get_LanguageID(This,pVal)

#define ITTSMode_get_Dialect(This,pVal)	\
    (This)->lpVtbl -> get_Dialect(This,pVal)

#define ITTSMode_get_Speaker(This,pVal)	\
    (This)->lpVtbl -> get_Speaker(This,pVal)

#define ITTSMode_get_Style(This,pVal)	\
    (This)->lpVtbl -> get_Style(This,pVal)

#define ITTSMode_get_Gender(This,pVal)	\
    (This)->lpVtbl -> get_Gender(This,pVal)

#define ITTSMode_get_Age(This,pVal)	\
    (This)->lpVtbl -> get_Age(This,pVal)

#define ITTSMode_get_Features(This,pVal)	\
    (This)->lpVtbl -> get_Features(This,pVal)

#define ITTSMode_get_Interfaces(This,pVal)	\
    (This)->lpVtbl -> get_Interfaces(This,pVal)

#define ITTSMode_get_EngineFeatures(This,pVal)	\
    (This)->lpVtbl -> get_EngineFeatures(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_EngineID_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_EngineID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_MfgName_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_MfgName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_ProductName_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_ProductName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_ModeID_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_ModeID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_ModeName_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_ModeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_LanguageID_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_LanguageID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Dialect_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Dialect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Speaker_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Speaker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Style_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Gender_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Gender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Age_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Age_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Features_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Features_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_Interfaces_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_Interfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTSMode_get_EngineFeatures_Proxy( 
    ITTSMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITTSMode_get_EngineFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTSMode_INTERFACE_DEFINED__ */


#ifndef __ISRMode_INTERFACE_DEFINED__
#define __ISRMode_INTERFACE_DEFINED__

/* interface ISRMode */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISRMode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD3-33A8-11D3-8658-0090272F9EEB")
    ISRMode : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EngineID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MfgName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProductName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ModeID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ModeName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LanguageID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dialect( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sequencing( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxWordsVocab( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxWordsState( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Grammars( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Features( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Interfaces( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EngineFeatures( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISRModeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISRMode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISRMode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISRMode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISRMode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISRMode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISRMode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISRMode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EngineID )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MfgName )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProductName )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModeID )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModeName )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LanguageID )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dialect )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Sequencing )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxWordsVocab )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxWordsState )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Grammars )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Features )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Interfaces )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EngineFeatures )( 
            ISRMode __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ISRModeVtbl;

    interface ISRMode
    {
        CONST_VTBL struct ISRModeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISRMode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISRMode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISRMode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISRMode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISRMode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISRMode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISRMode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISRMode_get_EngineID(This,pVal)	\
    (This)->lpVtbl -> get_EngineID(This,pVal)

#define ISRMode_get_MfgName(This,pVal)	\
    (This)->lpVtbl -> get_MfgName(This,pVal)

#define ISRMode_get_ProductName(This,pVal)	\
    (This)->lpVtbl -> get_ProductName(This,pVal)

#define ISRMode_get_ModeID(This,pVal)	\
    (This)->lpVtbl -> get_ModeID(This,pVal)

#define ISRMode_get_ModeName(This,pVal)	\
    (This)->lpVtbl -> get_ModeName(This,pVal)

#define ISRMode_get_LanguageID(This,pVal)	\
    (This)->lpVtbl -> get_LanguageID(This,pVal)

#define ISRMode_get_Dialect(This,pVal)	\
    (This)->lpVtbl -> get_Dialect(This,pVal)

#define ISRMode_get_Sequencing(This,pVal)	\
    (This)->lpVtbl -> get_Sequencing(This,pVal)

#define ISRMode_get_MaxWordsVocab(This,pVal)	\
    (This)->lpVtbl -> get_MaxWordsVocab(This,pVal)

#define ISRMode_get_MaxWordsState(This,pVal)	\
    (This)->lpVtbl -> get_MaxWordsState(This,pVal)

#define ISRMode_get_Grammars(This,pVal)	\
    (This)->lpVtbl -> get_Grammars(This,pVal)

#define ISRMode_get_Features(This,pVal)	\
    (This)->lpVtbl -> get_Features(This,pVal)

#define ISRMode_get_Interfaces(This,pVal)	\
    (This)->lpVtbl -> get_Interfaces(This,pVal)

#define ISRMode_get_EngineFeatures(This,pVal)	\
    (This)->lpVtbl -> get_EngineFeatures(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_EngineID_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_EngineID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_MfgName_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_MfgName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_ProductName_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_ProductName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_ModeID_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_ModeID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_ModeName_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_ModeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_LanguageID_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_LanguageID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_Dialect_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_Dialect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_Sequencing_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_Sequencing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_MaxWordsVocab_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_MaxWordsVocab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_MaxWordsState_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_MaxWordsState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_Grammars_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_Grammars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_Features_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_Features_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_Interfaces_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_Interfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISRMode_get_EngineFeatures_Proxy( 
    ISRMode __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISRMode_get_EngineFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISRMode_INTERFACE_DEFINED__ */


#ifndef __ITelephonyStep_INTERFACE_DEFINED__
#define __ITelephonyStep_INTERFACE_DEFINED__

/* interface ITelephonyStep */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITelephonyStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD4-33A8-11D3-8658-0090272F9EEB")
    ITelephonyStep : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MenuItemsLength( 
            /* [retval][out] */ long __RPC_FAR *plLength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMenuItem( 
            /* [in] */ long lIndex,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppMenuItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubmitMenu( 
            /* [retval][out] */ BOOL __RPC_FAR *pfIsSubmit) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioItemsLength( 
            /* [retval][out] */ long __RPC_FAR *plLength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioItem( 
            /* [in] */ long lIndex,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrAudioItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CutThroughMode( 
            /* [retval][out] */ BOOL __RPC_FAR *pfCutThroughMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsRecordType( 
            /* [retval][out] */ BOOL __RPC_FAR *pfIsRecord) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITelephonyStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITelephonyStep __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITelephonyStep __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITelephonyStep __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITelephonyStep __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITelephonyStep __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITelephonyStep __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITelephonyStep __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MenuItemsLength )( 
            ITelephonyStep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMenuItem )( 
            ITelephonyStep __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppMenuItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubmitMenu )( 
            ITelephonyStep __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfIsSubmit);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioItemsLength )( 
            ITelephonyStep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioItem )( 
            ITelephonyStep __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrAudioItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CutThroughMode )( 
            ITelephonyStep __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfCutThroughMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsRecordType )( 
            ITelephonyStep __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pfIsRecord);
        
        END_INTERFACE
    } ITelephonyStepVtbl;

    interface ITelephonyStep
    {
        CONST_VTBL struct ITelephonyStepVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITelephonyStep_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITelephonyStep_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITelephonyStep_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITelephonyStep_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITelephonyStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITelephonyStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITelephonyStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITelephonyStep_get_MenuItemsLength(This,plLength)	\
    (This)->lpVtbl -> get_MenuItemsLength(This,plLength)

#define ITelephonyStep_GetMenuItem(This,lIndex,ppMenuItem)	\
    (This)->lpVtbl -> GetMenuItem(This,lIndex,ppMenuItem)

#define ITelephonyStep_get_SubmitMenu(This,pfIsSubmit)	\
    (This)->lpVtbl -> get_SubmitMenu(This,pfIsSubmit)

#define ITelephonyStep_get_AudioItemsLength(This,plLength)	\
    (This)->lpVtbl -> get_AudioItemsLength(This,plLength)

#define ITelephonyStep_GetAudioItem(This,lIndex,pbstrAudioItem)	\
    (This)->lpVtbl -> GetAudioItem(This,lIndex,pbstrAudioItem)

#define ITelephonyStep_get_CutThroughMode(This,pfCutThroughMode)	\
    (This)->lpVtbl -> get_CutThroughMode(This,pfCutThroughMode)

#define ITelephonyStep_get_IsRecordType(This,pfIsRecord)	\
    (This)->lpVtbl -> get_IsRecordType(This,pfIsRecord)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_get_MenuItemsLength_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLength);


void __RPC_STUB ITelephonyStep_get_MenuItemsLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_GetMenuItem_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppMenuItem);


void __RPC_STUB ITelephonyStep_GetMenuItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_get_SubmitMenu_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfIsSubmit);


void __RPC_STUB ITelephonyStep_get_SubmitMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_get_AudioItemsLength_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLength);


void __RPC_STUB ITelephonyStep_get_AudioItemsLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_GetAudioItem_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrAudioItem);


void __RPC_STUB ITelephonyStep_GetAudioItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_get_CutThroughMode_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfCutThroughMode);


void __RPC_STUB ITelephonyStep_get_CutThroughMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITelephonyStep_get_IsRecordType_Proxy( 
    ITelephonyStep __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pfIsRecord);


void __RPC_STUB ITelephonyStep_get_IsRecordType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITelephonyStep_INTERFACE_DEFINED__ */


#ifndef __ILogCustomField_INTERFACE_DEFINED__
#define __ILogCustomField_INTERFACE_DEFINED__

/* interface ILogCustomField */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILogCustomField;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD5-33A8-11D3-8658-0090272F9EEB")
    ILogCustomField : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultValue( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILogCustomFieldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILogCustomField __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILogCustomField __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILogCustomField __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILogCustomField __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILogCustomField __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILogCustomField __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILogCustomField __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            ILogCustomField __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultValue )( 
            ILogCustomField __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ILogCustomFieldVtbl;

    interface ILogCustomField
    {
        CONST_VTBL struct ILogCustomFieldVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogCustomField_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILogCustomField_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILogCustomField_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILogCustomField_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILogCustomField_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILogCustomField_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILogCustomField_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILogCustomField_put_Value(This,Name,newVal)	\
    (This)->lpVtbl -> put_Value(This,Name,newVal)

#define ILogCustomField_put_DefaultValue(This,newVal)	\
    (This)->lpVtbl -> put_DefaultValue(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILogCustomField_put_Value_Proxy( 
    ILogCustomField __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILogCustomField_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILogCustomField_put_DefaultValue_Proxy( 
    ILogCustomField __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILogCustomField_put_DefaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILogCustomField_INTERFACE_DEFINED__ */


#ifndef __IExOM_INTERFACE_DEFINED__
#define __IExOM_INTERFACE_DEFINED__

/* interface IExOM */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExOM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD6-33A8-11D3-8658-0090272F9EEB")
    IExOM : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hostName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHostName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Abandon( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ ISession __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Configuration( 
            /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *ppApp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Log( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ITBasicCallControl( 
            /* [retval][out] */ ITBasicCallControl __RPC_FAR *__RPC_FAR *ppCall) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AlternativePhrases( 
            /* [retval][out] */ VARIANT __RPC_FAR *pAlternativePhrases) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogCustomField( 
            /* [retval][out] */ ILogCustomField __RPC_FAR *__RPC_FAR *ppLogCustomField) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Event( 
            /* [retval][out] */ LPDISPATCH __RPC_FAR *ppEvent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TTSMode( 
            /* [retval][out] */ ITTSMode __RPC_FAR *__RPC_FAR *ppTTSMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SRMode( 
            /* [retval][out] */ ISRMode __RPC_FAR *__RPC_FAR *ppSRMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExOMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExOM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExOM __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExOM __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExOM __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExOM __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExOM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExOM __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hostName )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrHostName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abandon )( 
            IExOM __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ ISession __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Configuration )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *ppApp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Log )( 
            IExOM __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ITBasicCallControl )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ ITBasicCallControl __RPC_FAR *__RPC_FAR *ppCall);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlternativePhrases )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pAlternativePhrases);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogCustomField )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ ILogCustomField __RPC_FAR *__RPC_FAR *ppLogCustomField);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Event )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *ppEvent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TTSMode )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ ITTSMode __RPC_FAR *__RPC_FAR *ppTTSMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SRMode )( 
            IExOM __RPC_FAR * This,
            /* [retval][out] */ ISRMode __RPC_FAR *__RPC_FAR *ppSRMode);
        
        END_INTERFACE
    } IExOMVtbl;

    interface IExOM
    {
        CONST_VTBL struct IExOMVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExOM_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExOM_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExOM_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExOM_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExOM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExOM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExOM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExOM_get_hostName(This,pbstrHostName)	\
    (This)->lpVtbl -> get_hostName(This,pbstrHostName)

#define IExOM_Abandon(This)	\
    (This)->lpVtbl -> Abandon(This)

#define IExOM_get_Session(This,ppSession)	\
    (This)->lpVtbl -> get_Session(This,ppSession)

#define IExOM_get_Configuration(This,ppApp)	\
    (This)->lpVtbl -> get_Configuration(This,ppApp)

#define IExOM_Log(This)	\
    (This)->lpVtbl -> Log(This)

#define IExOM_get_ITBasicCallControl(This,ppCall)	\
    (This)->lpVtbl -> get_ITBasicCallControl(This,ppCall)

#define IExOM_get_AlternativePhrases(This,pAlternativePhrases)	\
    (This)->lpVtbl -> get_AlternativePhrases(This,pAlternativePhrases)

#define IExOM_get_LogCustomField(This,ppLogCustomField)	\
    (This)->lpVtbl -> get_LogCustomField(This,ppLogCustomField)

#define IExOM_get_Event(This,ppEvent)	\
    (This)->lpVtbl -> get_Event(This,ppEvent)

#define IExOM_get_TTSMode(This,ppTTSMode)	\
    (This)->lpVtbl -> get_TTSMode(This,ppTTSMode)

#define IExOM_get_SRMode(This,ppSRMode)	\
    (This)->lpVtbl -> get_SRMode(This,ppSRMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_hostName_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrHostName);


void __RPC_STUB IExOM_get_hostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExOM_Abandon_Proxy( 
    IExOM __RPC_FAR * This);


void __RPC_STUB IExOM_Abandon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_Session_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ ISession __RPC_FAR *__RPC_FAR *ppSession);


void __RPC_STUB IExOM_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_Configuration_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ IWebTEApplication __RPC_FAR *__RPC_FAR *ppApp);


void __RPC_STUB IExOM_get_Configuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExOM_Log_Proxy( 
    IExOM __RPC_FAR * This);


void __RPC_STUB IExOM_Log_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_ITBasicCallControl_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ ITBasicCallControl __RPC_FAR *__RPC_FAR *ppCall);


void __RPC_STUB IExOM_get_ITBasicCallControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_AlternativePhrases_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pAlternativePhrases);


void __RPC_STUB IExOM_get_AlternativePhrases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_LogCustomField_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ ILogCustomField __RPC_FAR *__RPC_FAR *ppLogCustomField);


void __RPC_STUB IExOM_get_LogCustomField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_Event_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *ppEvent);


void __RPC_STUB IExOM_get_Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_TTSMode_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ ITTSMode __RPC_FAR *__RPC_FAR *ppTTSMode);


void __RPC_STUB IExOM_get_TTSMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExOM_get_SRMode_Proxy( 
    IExOM __RPC_FAR * This,
    /* [retval][out] */ ISRMode __RPC_FAR *__RPC_FAR *ppSRMode);


void __RPC_STUB IExOM_get_SRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExOM_INTERFACE_DEFINED__ */


#ifndef __IWebIvrActiveConnection_INTERFACE_DEFINED__
#define __IWebIvrActiveConnection_INTERFACE_DEFINED__

/* interface IWebIvrActiveConnection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebIvrActiveConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD7-33A8-11D3-8658-0090272F9EEB")
    IWebIvrActiveConnection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedObjectModel( 
            /* [retval][out] */ IExOM __RPC_FAR *__RPC_FAR *ppExOm) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephonyStep( 
            /* [retval][out] */ ITelephonyStep __RPC_FAR *__RPC_FAR *ppTelephonyStep) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebIvrActiveConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebIvrActiveConnection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebIvrActiveConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedObjectModel )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [retval][out] */ IExOM __RPC_FAR *__RPC_FAR *ppExOm);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephonyStep )( 
            IWebIvrActiveConnection __RPC_FAR * This,
            /* [retval][out] */ ITelephonyStep __RPC_FAR *__RPC_FAR *ppTelephonyStep);
        
        END_INTERFACE
    } IWebIvrActiveConnectionVtbl;

    interface IWebIvrActiveConnection
    {
        CONST_VTBL struct IWebIvrActiveConnectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebIvrActiveConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebIvrActiveConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebIvrActiveConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebIvrActiveConnection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebIvrActiveConnection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebIvrActiveConnection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebIvrActiveConnection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebIvrActiveConnection_get_ExtendedObjectModel(This,ppExOm)	\
    (This)->lpVtbl -> get_ExtendedObjectModel(This,ppExOm)

#define IWebIvrActiveConnection_get_TelephonyStep(This,ppTelephonyStep)	\
    (This)->lpVtbl -> get_TelephonyStep(This,ppTelephonyStep)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebIvrActiveConnection_get_ExtendedObjectModel_Proxy( 
    IWebIvrActiveConnection __RPC_FAR * This,
    /* [retval][out] */ IExOM __RPC_FAR *__RPC_FAR *ppExOm);


void __RPC_STUB IWebIvrActiveConnection_get_ExtendedObjectModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebIvrActiveConnection_get_TelephonyStep_Proxy( 
    IWebIvrActiveConnection __RPC_FAR * This,
    /* [retval][out] */ ITelephonyStep __RPC_FAR *__RPC_FAR *ppTelephonyStep);


void __RPC_STUB IWebIvrActiveConnection_get_TelephonyStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebIvrActiveConnection_INTERFACE_DEFINED__ */


#ifndef __IWebIvrService_INTERFACE_DEFINED__
#define __IWebIvrService_INTERFACE_DEFINED__

/* interface IWebIvrService */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebIvrService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA50DD8-33A8-11D3-8658-0090272F9EEB")
    IWebIvrService : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActiveConnection( 
            /* [in] */ BSTR bstrApplicationName,
            /* [out][retval] */ IWebIvrActiveConnection __RPC_FAR *__RPC_FAR *ppConnection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebIvrServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebIvrService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebIvrService __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebIvrService __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebIvrService __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebIvrService __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebIvrService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebIvrService __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActiveConnection )( 
            IWebIvrService __RPC_FAR * This,
            /* [in] */ BSTR bstrApplicationName,
            /* [out][retval] */ IWebIvrActiveConnection __RPC_FAR *__RPC_FAR *ppConnection);
        
        END_INTERFACE
    } IWebIvrServiceVtbl;

    interface IWebIvrService
    {
        CONST_VTBL struct IWebIvrServiceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebIvrService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebIvrService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebIvrService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebIvrService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebIvrService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebIvrService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebIvrService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebIvrService_GetActiveConnection(This,bstrApplicationName,ppConnection)	\
    (This)->lpVtbl -> GetActiveConnection(This,bstrApplicationName,ppConnection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebIvrService_GetActiveConnection_Proxy( 
    IWebIvrService __RPC_FAR * This,
    /* [in] */ BSTR bstrApplicationName,
    /* [out][retval] */ IWebIvrActiveConnection __RPC_FAR *__RPC_FAR *ppConnection);


void __RPC_STUB IWebIvrService_GetActiveConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebIvrService_INTERFACE_DEFINED__ */


#ifndef __IWebTESnapinNode_INTERFACE_DEFINED__
#define __IWebTESnapinNode_INTERFACE_DEFINED__

/* interface IWebTESnapinNode */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWebTESnapinNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c59f0ca0-401c-11d3-8659-0090272f9eeb")
    IWebTESnapinNode : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentObject( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParentArray( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebTESnapinNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTESnapinNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTESnapinNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTESnapinNode __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentObject )( 
            IWebTESnapinNode __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParentArray )( 
            IWebTESnapinNode __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IWebTESnapinNodeVtbl;

    interface IWebTESnapinNode
    {
        CONST_VTBL struct IWebTESnapinNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTESnapinNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTESnapinNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTESnapinNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTESnapinNode_get_CurrentObject(This,pVal)	\
    (This)->lpVtbl -> get_CurrentObject(This,pVal)

#define IWebTESnapinNode_get_ParentArray(This,pVal)	\
    (This)->lpVtbl -> get_ParentArray(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTESnapinNode_get_CurrentObject_Proxy( 
    IWebTESnapinNode __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTESnapinNode_get_CurrentObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWebTESnapinNode_get_ParentArray_Proxy( 
    IWebTESnapinNode __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IWebTESnapinNode_get_ParentArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebTESnapinNode_INTERFACE_DEFINED__ */



#ifndef __msivrCom_LIBRARY_DEFINED__
#define __msivrCom_LIBRARY_DEFINED__

/* library msivrCom */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_msivrCom;

EXTERN_C const CLSID CLSID_WebTE;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8324-336C-11D3-8657-0090272F9EEB")
WebTE;
#endif

EXTERN_C const CLSID CLSID_WebTEArray;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8325-336C-11D3-8657-0090272F9EEB")
WebTEArray;
#endif

EXTERN_C const CLSID CLSID_WebTEArrays;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8326-336C-11D3-8657-0090272F9EEB")
WebTEArrays;
#endif

EXTERN_C const CLSID CLSID_WebTEServers;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8327-336C-11D3-8657-0090272F9EEB")
WebTEServers;
#endif

EXTERN_C const CLSID CLSID_WebTEServer;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8328-336C-11D3-8657-0090272F9EEB")
WebTEServer;
#endif

EXTERN_C const CLSID CLSID_WebTEAddresses;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8329-336C-11D3-8657-0090272F9EEB")
WebTEAddresses;
#endif

EXTERN_C const CLSID CLSID_WebTEAddress;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E832A-336C-11D3-8657-0090272F9EEB")
WebTEAddress;
#endif

EXTERN_C const CLSID CLSID_WebTELineStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E832B-336C-11D3-8657-0090272F9EEB")
WebTELineStatus;
#endif

#ifndef __IWebTEParametersChanges_DISPINTERFACE_DEFINED__
#define __IWebTEParametersChanges_DISPINTERFACE_DEFINED__

/* dispinterface IWebTEParametersChanges */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IWebTEParametersChanges;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B83E832C-336C-11D3-8657-0090272F9EEB")
    IWebTEParametersChanges : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWebTEParametersChangesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebTEParametersChanges __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebTEParametersChanges __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebTEParametersChanges __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebTEParametersChanges __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebTEParametersChanges __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebTEParametersChanges __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebTEParametersChanges __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IWebTEParametersChangesVtbl;

    interface IWebTEParametersChanges
    {
        CONST_VTBL struct IWebTEParametersChangesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebTEParametersChanges_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebTEParametersChanges_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebTEParametersChanges_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebTEParametersChanges_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebTEParametersChanges_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebTEParametersChanges_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebTEParametersChanges_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWebTEParametersChanges_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebTEVendorDataSets;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E832D-336C-11D3-8657-0090272F9EEB")
WebTEVendorDataSets;
#endif

EXTERN_C const CLSID CLSID_WebTEVendorDataSet;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E832E-336C-11D3-8657-0090272F9EEB")
WebTEVendorDataSet;
#endif

EXTERN_C const CLSID CLSID_WebTEHtmlPropertyPages;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E832F-336C-11D3-8657-0090272F9EEB")
WebTEHtmlPropertyPages;
#endif

EXTERN_C const CLSID CLSID_WebTEHtmlPropertyPage;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8330-336C-11D3-8657-0090272F9EEB")
WebTEHtmlPropertyPage;
#endif

EXTERN_C const CLSID CLSID_WebTEParametersSets;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8331-336C-11D3-8657-0090272F9EEB")
WebTEParametersSets;
#endif

EXTERN_C const CLSID CLSID_WebTEParametersSet;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8332-336C-11D3-8657-0090272F9EEB")
WebTEParametersSet;
#endif

EXTERN_C const CLSID CLSID_WebTELog;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8334-336C-11D3-8657-0090272F9EEB")
WebTELog;
#endif

EXTERN_C const CLSID CLSID_WebTEApplications;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8336-336C-11D3-8657-0090272F9EEB")
WebTEApplications;
#endif

EXTERN_C const CLSID CLSID_WebTEApplication;

#ifdef __cplusplus

class DECLSPEC_UUID("B83E8337-336C-11D3-8657-0090272F9EEB")
WebTEApplication;
#endif

#ifndef __IWebIvrConnectionEvents_DISPINTERFACE_DEFINED__
#define __IWebIvrConnectionEvents_DISPINTERFACE_DEFINED__

/* dispinterface IWebIvrConnectionEvents */
/* [uuid] */ 


EXTERN_C const IID DIID_IWebIvrConnectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AFA50DDA-33A8-11D3-8658-0090272F9EEB")
    IWebIvrConnectionEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWebIvrConnectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebIvrConnectionEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebIvrConnectionEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebIvrConnectionEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebIvrConnectionEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebIvrConnectionEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebIvrConnectionEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebIvrConnectionEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IWebIvrConnectionEventsVtbl;

    interface IWebIvrConnectionEvents
    {
        CONST_VTBL struct IWebIvrConnectionEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebIvrConnectionEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebIvrConnectionEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebIvrConnectionEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebIvrConnectionEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebIvrConnectionEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebIvrConnectionEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebIvrConnectionEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWebIvrConnectionEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebIvrService;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DDB-33A8-11D3-8658-0090272F9EEB")
WebIvrService;
#endif

EXTERN_C const CLSID CLSID_WebIvrActiveConnection;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DDC-33A8-11D3-8658-0090272F9EEB")
WebIvrActiveConnection;
#endif

EXTERN_C const CLSID CLSID_TelephonyStep;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DDD-33A8-11D3-8658-0090272F9EEB")
TelephonyStep;
#endif

EXTERN_C const CLSID CLSID_TelephonyStepConstrains;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DDE-33A8-11D3-8658-0090272F9EEB")
TelephonyStepConstrains;
#endif

EXTERN_C const CLSID CLSID_Session;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DDF-33A8-11D3-8658-0090272F9EEB")
Session;
#endif

EXTERN_C const CLSID CLSID_TTSMode;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DE0-33A8-11D3-8658-0090272F9EEB")
TTSMode;
#endif

EXTERN_C const CLSID CLSID_SRMode;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DE1-33A8-11D3-8658-0090272F9EEB")
SRMode;
#endif

EXTERN_C const CLSID CLSID_ExOM;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DE2-33A8-11D3-8658-0090272F9EEB")
ExOM;
#endif

EXTERN_C const CLSID CLSID_LogCustomField;

#ifdef __cplusplus

class DECLSPEC_UUID("AFA50DE3-33A8-11D3-8658-0090272F9EEB")
LogCustomField;
#endif

EXTERN_C const CLSID CLSID_WebTESnapinNode;

#ifdef __cplusplus

class DECLSPEC_UUID("b3a60310-401c-11d3-8659-0090272f9eeb")
WebTESnapinNode;
#endif
#endif /* __msivrCom_LIBRARY_DEFINED__ */

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


