/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 14 18:29:41 1999
 */
/* Compiler settings for Student.idl:
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

#ifndef __Student_h__
#define __Student_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IStudent_FWD_DEFINED__
#define __IStudent_FWD_DEFINED__
typedef interface IStudent IStudent;
#endif 	/* __IStudent_FWD_DEFINED__ */


#ifndef __UDT_FWD_DEFINED__
#define __UDT_FWD_DEFINED__

#ifdef __cplusplus
typedef class UDT UDT;
#else
typedef struct UDT UDT;
#endif /* __cplusplus */

#endif 	/* __UDT_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Student_LIBRARY_DEFINED__
#define __Student_LIBRARY_DEFINED__

/* library Student */
/* [helpstring][lcid][version][uuid] */ 

typedef 
enum tagclassification
    {	school_Bully	= 0,
	class_Clown	= school_Bully + 1,
	teachers_Favorite	= class_Clown + 1
    }	classification;

typedef /* [uuid] */ struct  tagStudentStruct
    {
    BSTR name;
    short grade;
    classification type;
    VARIANT_BOOL graduate;
    }	StudentStruct;

typedef StudentStruct __RPC_FAR *LPSTUDENTSTRUCT;


EXTERN_C const IID LIBID_Student;

#ifndef __IStudent_INTERFACE_DEFINED__
#define __IStudent_INTERFACE_DEFINED__

/* interface IStudent */
/* [unique][dual][helpstring][uuid][object] */ 

typedef IStudent __RPC_FAR *LPSTUDENT;


EXTERN_C const IID IID_IStudent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D50BD660-7471-11d2-9A80-006097DA88F5")
    IStudent : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Test1( 
            /* [out][in] */ LPSTUDENTSTRUCT lpStudent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Test2( 
            /* [out][in] */ SAFEARRAY __RPC_FAR * __MIDL_0010) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStudentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStudent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStudent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStudent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStudent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStudent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStudent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStudent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test1 )( 
            IStudent __RPC_FAR * This,
            /* [out][in] */ LPSTUDENTSTRUCT lpStudent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test2 )( 
            IStudent __RPC_FAR * This,
            /* [out][in] */ SAFEARRAY __RPC_FAR * __MIDL_0010);
        
        END_INTERFACE
    } IStudentVtbl;

    interface IStudent
    {
        CONST_VTBL struct IStudentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStudent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStudent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStudent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStudent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStudent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStudent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStudent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStudent_Test1(This,lpStudent)	\
    (This)->lpVtbl -> Test1(This,lpStudent)

#define IStudent_Test2(This,__MIDL_0010)	\
    (This)->lpVtbl -> Test2(This,__MIDL_0010)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStudent_Test1_Proxy( 
    IStudent __RPC_FAR * This,
    /* [out][in] */ LPSTUDENTSTRUCT lpStudent);


void __RPC_STUB IStudent_Test1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStudent_Test2_Proxy( 
    IStudent __RPC_FAR * This,
    /* [out][in] */ SAFEARRAY __RPC_FAR * __MIDL_0010);


void __RPC_STUB IStudent_Test2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStudent_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UDT;

#ifdef __cplusplus

class DECLSPEC_UUID("D50BD662-7471-11d2-9A80-006097DA88F5")
UDT;
#endif
#endif /* __Student_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
