/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 10 09:33:50 1999
 */
/* Compiler settings for msdfmap.idl:
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

#ifndef __msdfmap_h__
#define __msdfmap_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __Handler_FWD_DEFINED__
#define __Handler_FWD_DEFINED__

#ifdef __cplusplus
typedef class Handler Handler;
#else
typedef struct Handler Handler;
#endif /* __cplusplus */

#endif 	/* __Handler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __MSDFMAPLib_LIBRARY_DEFINED__
#define __MSDFMAPLib_LIBRARY_DEFINED__

/* library MSDFMAPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSDFMAPLib;

EXTERN_C const CLSID CLSID_Handler;

#ifdef __cplusplus

class DECLSPEC_UUID("9D3B7E05-5BAF-11d1-922A-00C04FBBBFB3")
Handler;
#endif
#endif /* __MSDFMAPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
