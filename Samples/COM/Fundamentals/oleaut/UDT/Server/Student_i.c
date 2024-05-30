/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 14 18:29:41 1999
 */
/* Compiler settings for Student.idl:
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

const IID LIBID_Student = {0xD50BD661,0x7471,0x11d2,{0x9A,0x80,0x00,0x60,0x97,0xDA,0x88,0xF5}};


const IID IID_IStudent = {0xD50BD660,0x7471,0x11d2,{0x9A,0x80,0x00,0x60,0x97,0xDA,0x88,0xF5}};


const CLSID CLSID_UDT = {0xD50BD662,0x7471,0x11d2,{0x9A,0x80,0x00,0x60,0x97,0xDA,0x88,0xF5}};


#ifdef __cplusplus
}
#endif

