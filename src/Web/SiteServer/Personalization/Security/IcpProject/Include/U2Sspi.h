//+---------------------------------------------------------------------------
//
//  File:       u2sspi.h
//
//  Contents:   This file describes the parameters for passing
//              Virtual Server information for Basic and DPA SSPI
//              packages.
//
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//----------------------------------------------------------------------------
#ifndef _U2_SSPI_H_
#define _U2_SSPI_H_

//
// Opaque message passed in AcceptSecurityContext for BAsic
// and DPA
//
typedef struct _MBS_SERVICE_ID_MESSAGE {
    UNICODE_STRING wszServiceComment;
     // the format of this buffer is a unicode string, null
     // terminated, and contains the description of the u2 virtual
     // server that the sspi package should use to authenticate.
} MBS_SERVICE_ID_MESSAGE, *PMBS_SERVICE_ID_MESSAGE;

#endif
