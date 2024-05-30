/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 18 12:05:52 1999
 */
/* Compiler settings for E:\mssdk\Samples\COM\Services\Events\EventMonitor\EventMonSubscriber\EventMonSubscriber.idl:
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

#ifndef __EventMonSubscriber_h__
#define __EventMonSubscriber_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __EventMonSubscriber_FWD_DEFINED__
#define __EventMonSubscriber_FWD_DEFINED__

#ifdef __cplusplus
typedef class EventMonSubscriber EventMonSubscriber;
#else
typedef struct EventMonSubscriber EventMonSubscriber;
#endif /* __cplusplus */

#endif 	/* __EventMonSubscriber_FWD_DEFINED__ */


/* header files for imported files */
#include "EventMon.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __EventMonSUBSCRIBERLib_LIBRARY_DEFINED__
#define __EventMonSUBSCRIBERLib_LIBRARY_DEFINED__

/* library EventMonSUBSCRIBERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EventMonSUBSCRIBERLib;

EXTERN_C const CLSID CLSID_EventMonSubscriber;

#ifdef __cplusplus

class DECLSPEC_UUID("14DF7DE8-D26D-11D2-9A34-00C04F72EB9B")
EventMonSubscriber;
#endif
#endif /* __EventMonSUBSCRIBERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
