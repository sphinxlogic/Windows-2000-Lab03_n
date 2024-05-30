// macro.h

#ifndef _MACRO_H_
#define _MACRO_H_

#define	RELEASE(p)	if (p)			\
					p->Release();	\
					p = 0			\

#define SAFERELEASE(p)	RELEASE(p)

#define leave(hr)	if FAILED(hr)	\
					__leave;

#define ret(hr)		if FAILED(hr)	\
				    return hr;	

#define exit(hr)	if FAILED(hr)	\
					goto exit;	

#define jump(hr)	if FAILED(hr)	\
					goto jump;

#define		NUM_COMBO			6	// Number of combo boxes
#define		NUM_INTERFACE		3	// Number of methods
#define		NUM_METHOD_IDISK		1
#define		NUM_METHOD_IFILESYSTEM	4
#define		NUM_METHOD_ISYSTEM	3


#endif