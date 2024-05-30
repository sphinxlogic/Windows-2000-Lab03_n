/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Nov 28 16:03:25 2023
 */
/* Compiler settings for sfiltern.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data , no_format_optimization
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "sfiltern.h"

#define TYPE_FORMAT_STRING_SIZE   23                                
#define PROC_FORMAT_STRING_SIZE   25                                

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


/* Standard interface: __MIDL_itf_sfiltern_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: INetCfgPnpReconfigCallback, ver. 0.0,
   GUID={0x8d84bd35,0xe227,0x11d2,{0xb7,0x00,0x00,0xa0,0xc9,0x8a,0x6a,0x85}} */


/* Object interface: INetCfgComponentControl, ver. 0.0,
   GUID={0x932238df,0xbea1,0x11d0,{0x92,0x98,0x00,0xc0,0x4f,0xc9,0x9d,0xcf}} */


/* Object interface: INetCfgComponentSetup, ver. 0.0,
   GUID={0x932238e3,0xbea1,0x11d0,{0x92,0x98,0x00,0xc0,0x4f,0xc9,0x9d,0xcf}} */


/* Object interface: INetCfgComponentPropertyUi, ver. 0.0,
   GUID={0x932238e0,0xbea1,0x11d0,{0x92,0x98,0x00,0xc0,0x4f,0xc9,0x9d,0xcf}} */


/* Object interface: INetCfgComponentNotifyBinding, ver. 0.0,
   GUID={0x932238e1,0xbea1,0x11d0,{0x92,0x98,0x00,0xc0,0x4f,0xc9,0x9d,0xcf}} */


/* Object interface: INetCfgComponentNotifyGlobal, ver. 0.0,
   GUID={0x932238e2,0xbea1,0x11d0,{0x92,0x98,0x00,0xc0,0x4f,0xc9,0x9d,0xcf}} */


/* Object interface: INetCfgComponentUpperEdge, ver. 0.0,
   GUID={0x932238e4,0xbea1,0x11d0,{0x92,0x98,0x00,0xc0,0x4f,0xc9,0x9d,0xcf}} */


/* Object interface: INetLanConnectionUiInfo, ver. 0.0,
   GUID={0xC08956A6,0x1CD3,0x11D1,{0xB1,0xC5,0x00,0x80,0x5F,0xC1,0x27,0x0E}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO INetLanConnectionUiInfo_ServerInfo;

#pragma code_seg(".orpc")

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x301004b, /* MIDL Version 3.1.75 */
    0,
    0,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short INetLanConnectionUiInfo_FormatStringOffsetTable[] = 
    {
    0
    };

static const MIDL_SERVER_INFO INetLanConnectionUiInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &INetLanConnectionUiInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO INetLanConnectionUiInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &INetLanConnectionUiInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(4) _INetLanConnectionUiInfoProxyVtbl = 
{
    &INetLanConnectionUiInfo_ProxyInfo,
    &IID_INetLanConnectionUiInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* INetLanConnectionUiInfo::GetDeviceGuid */
};

const CInterfaceStubVtbl _INetLanConnectionUiInfoStubVtbl =
{
    &IID_INetLanConnectionUiInfo,
    &INetLanConnectionUiInfo_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

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

	/* Procedure GetDeviceGuid */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x28 ),	/* 40 */
/* 10 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter pguid */

/* 12 */	NdrFcShort( 0x4112 ),	/* 16658 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 16 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 18 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 22 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  2 */	NdrFcShort( 0x8 ),	/* Offset= 8 (10) */
/*  4 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/*  6 */	NdrFcShort( 0x8 ),	/* 8 */
/*  8 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 10 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 12 */	NdrFcShort( 0x10 ),	/* 16 */
/* 14 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 16 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 18 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (4) */
			0x5b,		/* FC_END */

			0x0
        }
    };

const CInterfaceProxyVtbl * _sfiltern_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INetLanConnectionUiInfoProxyVtbl,
    0
};

const CInterfaceStubVtbl * _sfiltern_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INetLanConnectionUiInfoStubVtbl,
    0
};

PCInterfaceName const _sfiltern_InterfaceNamesList[] = 
{
    "INetLanConnectionUiInfo",
    0
};


#define _sfiltern_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _sfiltern, pIID, n)

int __stdcall _sfiltern_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_sfiltern_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo sfiltern_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _sfiltern_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _sfiltern_StubVtblList,
    (const PCInterfaceName * ) & _sfiltern_InterfaceNamesList,
    0, // no delegation
    & _sfiltern_IID_Lookup, 
    1,
    2
};
