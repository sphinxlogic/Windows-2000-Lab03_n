/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 10 09:33:45 1999
 */
/* Compiler settings for msdfhdl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID LIBID_MSDFHDL = {0xD80DE8B3,0x0001,0x11d1,{0x91,0xE6,0x00,0xC0,0x4F,0xBB,0xBF,0xB3}};


const IID IID_IDataFactoryHandler = {0xD80DE8B5,0x0001,0x11d1,{0x91,0xE6,0x00,0xC0,0x4F,0xBB,0xBF,0xB3}};


#ifdef __cplusplus
}
#endif

