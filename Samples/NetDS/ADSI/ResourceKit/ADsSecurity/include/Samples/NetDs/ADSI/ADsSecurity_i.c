/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Mar 15 17:06:48 1999
 */
/* Compiler settings for C:\projects\RTK\ADsSecurity\ADsSecurity.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IADsSecurity = {0x212029A9,0xC50D,0x11D2,{0xBC,0x7E,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const IID IID_IADsSID = {0x212029AE,0xC50D,0x11D2,{0xBC,0x7E,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const IID LIBID_ADSSECURITYLib = {0x2120299D,0xC50D,0x11D2,{0xBC,0x7E,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const CLSID CLSID_ADsSecurity = {0x212029AA,0xC50D,0x11D2,{0xBC,0x7E,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const CLSID CLSID_ADsSID = {0x212029AF,0xC50D,0x11D2,{0xBC,0x7E,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


#ifdef __cplusplus
}
#endif

