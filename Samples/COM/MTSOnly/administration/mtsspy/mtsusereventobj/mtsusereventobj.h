/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Wed Mar 19 09:35:54 1997
 */
/* Compiler settings for MtsUserEventObj.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MtsUserEventObj_h__
#define __MtsUserEventObj_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMtsUserEventData_FWD_DEFINED__
#define __IMtsUserEventData_FWD_DEFINED__
typedef interface IMtsUserEventData IMtsUserEventData;
#endif 	/* __IMtsUserEventData_FWD_DEFINED__ */


#ifndef __MtsUserEventData_FWD_DEFINED__
#define __MtsUserEventData_FWD_DEFINED__

#ifdef __cplusplus
typedef class MtsUserEventData MtsUserEventData;
#else
typedef struct MtsUserEventData MtsUserEventData;
#endif /* __cplusplus */

#endif 	/* __MtsUserEventData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMtsUserEventData_INTERFACE_DEFINED__
#define __IMtsUserEventData_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsUserEventData
 * at Wed Mar 19 09:35:54 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IMtsUserEventData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F523E424-8485-11D0-B170-00AA00BA3258")
    IMtsUserEventData : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GuidEventId( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            BSTR sKey,
            /* [in] */ VARIANT __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsUserEventDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsUserEventData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsUserEventData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GuidEventId )( 
            IMtsUserEventData __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IMtsUserEventData __RPC_FAR * This,
            BSTR sKey,
            /* [in] */ VARIANT __RPC_FAR *newVal);
        
        END_INTERFACE
    } IMtsUserEventDataVtbl;

    interface IMtsUserEventData
    {
        CONST_VTBL struct IMtsUserEventDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsUserEventData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsUserEventData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsUserEventData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsUserEventData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMtsUserEventData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMtsUserEventData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMtsUserEventData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMtsUserEventData_put_DisplayName(This,newVal)	\
    (This)->lpVtbl -> put_DisplayName(This,newVal)

#define IMtsUserEventData_put_GuidEventId(This,newVal)	\
    (This)->lpVtbl -> put_GuidEventId(This,newVal)

#define IMtsUserEventData_put_Value(This,sKey,newVal)	\
    (This)->lpVtbl -> put_Value(This,sKey,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMtsUserEventData_put_DisplayName_Proxy( 
    IMtsUserEventData __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMtsUserEventData_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMtsUserEventData_put_GuidEventId_Proxy( 
    IMtsUserEventData __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMtsUserEventData_put_GuidEventId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMtsUserEventData_put_Value_Proxy( 
    IMtsUserEventData __RPC_FAR * This,
    BSTR sKey,
    /* [in] */ VARIANT __RPC_FAR *newVal);


void __RPC_STUB IMtsUserEventData_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsUserEventData_INTERFACE_DEFINED__ */



#ifndef __MTSUSEREVENTOBJLib_LIBRARY_DEFINED__
#define __MTSUSEREVENTOBJLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MTSUSEREVENTOBJLib
 * at Wed Mar 19 09:35:54 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_MTSUSEREVENTOBJLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_MtsUserEventData;

class DECLSPEC_UUID("F523E425-8485-11D0-B170-00AA00BA3258")
MtsUserEventData;
#endif
#endif /* __MTSUSEREVENTOBJLib_LIBRARY_DEFINED__ */

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
