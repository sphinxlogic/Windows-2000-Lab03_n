/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Nov 28 16:03:27 2023
 */
/* Compiler settings for idls.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "idls.h"

#define TYPE_FORMAT_STRING_SIZE   1                                 
#define PROC_FORMAT_STRING_SIZE   1                                 

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_idls_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IEnumNetCfgBindingInterface, ver. 0.0,
   GUID={0xC0E8AE90,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: IEnumNetCfgBindingPath, ver. 0.0,
   GUID={0xC0E8AE91,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: IEnumNetCfgComponent, ver. 0.0,
   GUID={0xC0E8AE92,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfg, ver. 0.0,
   GUID={0xC0E8AE93,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgLock, ver. 0.0,
   GUID={0xC0E8AE9F,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgBindingInterface, ver. 0.0,
   GUID={0xC0E8AE94,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgBindingPath, ver. 0.0,
   GUID={0xC0E8AE96,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgClass, ver. 0.0,
   GUID={0xC0E8AE97,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgClassSetup, ver. 0.0,
   GUID={0xC0E8AE9D,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgComponent, ver. 0.0,
   GUID={0xC0E8AE99,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


/* Object interface: INetCfgComponentBindings, ver. 0.0,
   GUID={0xC0E8AE9E,0x306E,0x11D1,{0xAA,0xCF,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {

			0x0
        }
    };

const CInterfaceProxyVtbl * _idls_ProxyVtblList[] = 
{
    0
};

const CInterfaceStubVtbl * _idls_StubVtblList[] = 
{
    0
};

PCInterfaceName const _idls_InterfaceNamesList[] = 
{
    0
};


#define _idls_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _idls, pIID, n)

int __stdcall _idls_IID_Lookup( const IID * pIID, int * pIndex )
{
    return 0;
}

const ExtendedProxyFileInfo idls_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _idls_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _idls_StubVtblList,
    (const PCInterfaceName * ) & _idls_InterfaceNamesList,
    0, // no delegation
    & _idls_IID_Lookup, 
    0,
    2
};
