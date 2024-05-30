/************************************************************************
*                                                                       *
*   mswteError.h --  error code definitions for Web Telephony Engine.   *
*                                                                       *
*   Copyright (c) 1991-1999, Microsoft Corp. All rights reserved.       *
*                                                                       *
*   This is prerelease software and is provided as is and Microsoft     *
*   makes no warranties, either express or implied. The entire risk of  *
*   the use or the results of the use of this prerelease software       *
*   remains with the user.                                              *
*                                                                       *
************************************************************************/

#ifndef MSWTEERROR_H_INCLUDED
#define MSWTEERROR_H_INCLUDED

   
#include <WinError.h>

#define WEBTE_ERR(_code) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, _code)

#define E_WEBTE_NO_STORAGE                          WEBTE_ERR(0x200)

#define E_WEBTE_OBJECT_INVALID                      WEBTE_ERR(0x201)

#define E_WEBTE_CORRUPTED_OBJECT_DATA               WEBTE_ERR(0x202)

#define E_WEBTE_INVALID_SERVER_NAME                 WEBTE_ERR(0x203)

#define E_WEBTE_STRING_CONTAINS_INVALID_CHARACTERS  WEBTE_ERR(0x204)

#define E_WEBTE_EMPTY_STRING                        WEBTE_ERR(0x205)

#define E_WEBTE_VALUE_TOO_LARGE                     WEBTE_ERR(0x206)

#define E_WEBTE_VALUE_TOO_SMALL                     WEBTE_ERR(0x207)

#define E_WEBTE_CREATE_CHILD_INSTANCE_FAILED        WEBTE_ERR(0x208)

#endif // ! MSWTEERROR_H_INCLUDED


