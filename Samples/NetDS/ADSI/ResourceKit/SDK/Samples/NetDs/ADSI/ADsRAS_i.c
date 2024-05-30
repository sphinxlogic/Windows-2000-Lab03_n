/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Apr 13 11:18:46 1999
 */
/* Compiler settings for C:\projects\RTK\ADsRAS\ADsRAS.idl:
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

const IID IID_IADsRas = {0xF1F533EF,0xF118,0x11D2,{0xBC,0x88,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const IID LIBID_ADSRASLib = {0xF1F533E3,0xF118,0x11D2,{0xBC,0x88,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const CLSID CLSID_ADsRas = {0xF1F533F0,0xF118,0x11D2,{0xBC,0x88,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


#ifdef __cplusplus
}
#endif

