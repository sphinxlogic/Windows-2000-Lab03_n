/******************************Module*Header*******************************\
* Module Name: glscrnsv.h
*
* Include for modified scrnsave.c
*
* Copyright 1996 - 1998 Microsoft Corporation
*
\**************************************************************************/

#ifndef __glscrnsv_h__
#define __glscrnsv_h__

#include "sscommon.hxx"
#include "sswproc.hxx"

#ifdef __cplusplus
extern "C" {
#endif

extern LRESULT DoScreenSave( HWND hwndParent );
extern LRESULT DoWindowedScreenSave( LPCTSTR szArgs );
extern LRESULT DoConfigBox( HWND hwndParent );

#ifdef __cplusplus
}
#endif

#endif // __glscrnsv_h__
