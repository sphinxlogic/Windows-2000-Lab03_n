/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 05 11:00:35 1999
 */
/* Compiler settings for C:\projects\RTK\ADsVersion\ADsVersion.idl:
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

const IID IID_IADsVersion = {0x4F7D6500,0xD272,0x11D2,{0x9A,0x95,0x00,0x80,0xC7,0xA2,0xDC,0x6B}};


const IID LIBID_ADSVERSIONLib = {0x12A2A870,0xD272,0x11D2,{0x9A,0x95,0x00,0x80,0xC7,0xA2,0xDC,0x6B}};


const CLSID CLSID_ADsVersion = {0x4F7D6501,0xD272,0x11D2,{0x9A,0x95,0x00,0x80,0xC7,0xA2,0xDC,0x6B}};


#ifdef __cplusplus
}
#endif

