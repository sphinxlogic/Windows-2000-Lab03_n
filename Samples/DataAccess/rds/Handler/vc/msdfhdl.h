/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 10 09:33:45 1999
 */
/* Compiler settings for msdfhdl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __msdfhdl_h__
#define __msdfhdl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDataFactoryHandler_FWD_DEFINED__
#define __IDataFactoryHandler_FWD_DEFINED__
typedef interface IDataFactoryHandler IDataFactoryHandler;
#endif 	/* __IDataFactoryHandler_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __MSDFHDL_LIBRARY_DEFINED__
#define __MSDFHDL_LIBRARY_DEFINED__

/* library MSDFHDL */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MSDFHDL;

#ifndef __IDataFactoryHandler_INTERFACE_DEFINED__
#define __IDataFactoryHandler_INTERFACE_DEFINED__

/* interface IDataFactoryHandler */
/* [object][version][uuid] */ 


EXTERN_C const IID IID_IDataFactoryHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D80DE8B5-0001-11d1-91E6-00C04FBBBFB3")
    IDataFactoryHandler : public IUnknown
    {
    public:
        virtual HRESULT __stdcall GetRecordset( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ BSTR query,
            /* [retval][out] */ /* external definition not present */ _Recordset __RPC_FAR *__RPC_FAR *ppRS) = 0;
        
        virtual HRESULT __stdcall Reconnect( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ /* external definition not present */ _Recordset __RPC_FAR *pRS) = 0;
        
        virtual HRESULT __stdcall OpenConnection( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ long lFlags,
            /* [out][in] */ BSTR __RPC_FAR *pQuery,
            /* [retval][out] */ /* external definition not present */ _Connection __RPC_FAR *__RPC_FAR *ppConnection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDataFactoryHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDataFactoryHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDataFactoryHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDataFactoryHandler __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *GetRecordset )( 
            IDataFactoryHandler __RPC_FAR * This,
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ BSTR query,
            /* [retval][out] */ /* external definition not present */ _Recordset __RPC_FAR *__RPC_FAR *ppRS);
        
        HRESULT ( __stdcall __RPC_FAR *Reconnect )( 
            IDataFactoryHandler __RPC_FAR * This,
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ /* external definition not present */ _Recordset __RPC_FAR *pRS);
        
        HRESULT ( __stdcall __RPC_FAR *OpenConnection )( 
            IDataFactoryHandler __RPC_FAR * This,
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ long lFlags,
            /* [out][in] */ BSTR __RPC_FAR *pQuery,
            /* [retval][out] */ /* external definition not present */ _Connection __RPC_FAR *__RPC_FAR *ppConnection);
        
        END_INTERFACE
    } IDataFactoryHandlerVtbl;

    interface IDataFactoryHandler
    {
        CONST_VTBL struct IDataFactoryHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataFactoryHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDataFactoryHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDataFactoryHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDataFactoryHandler_GetRecordset(This,conn,args,query,ppRS)	\
    (This)->lpVtbl -> GetRecordset(This,conn,args,query,ppRS)

#define IDataFactoryHandler_Reconnect(This,conn,args,pRS)	\
    (This)->lpVtbl -> Reconnect(This,conn,args,pRS)

#define IDataFactoryHandler_OpenConnection(This,conn,args,lFlags,pQuery,ppConnection)	\
    (This)->lpVtbl -> OpenConnection(This,conn,args,lFlags,pQuery,ppConnection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IDataFactoryHandler_GetRecordset_Proxy( 
    IDataFactoryHandler __RPC_FAR * This,
    /* [in] */ BSTR conn,
    /* [in] */ BSTR args,
    /* [in] */ BSTR query,
    /* [retval][out] */ /* external definition not present */ _Recordset __RPC_FAR *__RPC_FAR *ppRS);


void __RPC_STUB IDataFactoryHandler_GetRecordset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDataFactoryHandler_Reconnect_Proxy( 
    IDataFactoryHandler __RPC_FAR * This,
    /* [in] */ BSTR conn,
    /* [in] */ BSTR args,
    /* [in] */ /* external definition not present */ _Recordset __RPC_FAR *pRS);


void __RPC_STUB IDataFactoryHandler_Reconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDataFactoryHandler_OpenConnection_Proxy( 
    IDataFactoryHandler __RPC_FAR * This,
    /* [in] */ BSTR conn,
    /* [in] */ BSTR args,
    /* [in] */ long lFlags,
    /* [out][in] */ BSTR __RPC_FAR *pQuery,
    /* [retval][out] */ /* external definition not present */ _Connection __RPC_FAR *__RPC_FAR *ppConnection);


void __RPC_STUB IDataFactoryHandler_OpenConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDataFactoryHandler_INTERFACE_DEFINED__ */

#endif /* __MSDFHDL_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
