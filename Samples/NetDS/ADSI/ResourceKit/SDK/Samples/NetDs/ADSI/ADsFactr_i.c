/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 17 15:13:27 1998
 */
/* Compiler settings for C:\projects\ADsFactr\ADsFactr.idl:
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

const IID IID_IADsFactory = {0xBACFDB72,0x7E23,0x11D2,{0xB4,0x47,0x00,0x80,0xC7,0xD0,0x71,0xBF}};


const IID LIBID_ADSFACTRLib = {0xBACFDB66,0x7E23,0x11D2,{0xB4,0x47,0x00,0x80,0xC7,0xD0,0x71,0xBF}};


const CLSID CLSID_ADsFactory = {0xBACFDB73,0x7E23,0x11D2,{0xB4,0x47,0x00,0x80,0xC7,0xD0,0x71,0xBF}};


#ifdef __cplusplus
}
#endif

