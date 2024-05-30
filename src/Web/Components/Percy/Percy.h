/* Microsoft Corporation Copyright 1999 */
/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 19 16:19:45 1998
 */
/* Compiler settings for Percy.idl:
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

#ifndef __Percy_h__
#define __Percy_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __Ipercyctl_FWD_DEFINED__
#define __Ipercyctl_FWD_DEFINED__
typedef interface Ipercyctl Ipercyctl;
#endif 	/* __Ipercyctl_FWD_DEFINED__ */


#ifndef __percyctl_FWD_DEFINED__
#define __percyctl_FWD_DEFINED__

#ifdef __cplusplus
typedef class percyctl percyctl;
#else
typedef struct percyctl percyctl;
#endif /* __cplusplus */

#endif 	/* __percyctl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __Ipercyctl_INTERFACE_DEFINED__
#define __Ipercyctl_INTERFACE_DEFINED__

/* interface Ipercyctl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_Ipercyctl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4912B21E-05B0-11D1-AF9A-00A0C909FE5F")
    Ipercyctl : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IpercyctlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Ipercyctl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Ipercyctl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Ipercyctl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Ipercyctl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Ipercyctl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Ipercyctl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Ipercyctl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IpercyctlVtbl;

    interface Ipercyctl
    {
        CONST_VTBL struct IpercyctlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ipercyctl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Ipercyctl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Ipercyctl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Ipercyctl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Ipercyctl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Ipercyctl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Ipercyctl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Ipercyctl_INTERFACE_DEFINED__ */



#ifndef __PERCYLib_LIBRARY_DEFINED__
#define __PERCYLib_LIBRARY_DEFINED__

/* library PERCYLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PERCYLib;

EXTERN_C const CLSID CLSID_percyctl;

#ifdef __cplusplus

class DECLSPEC_UUID("F1D8212E-059E-11D1-AF9A-00A0C909FE5F")
percyctl;
#endif
#endif /* __PERCYLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
