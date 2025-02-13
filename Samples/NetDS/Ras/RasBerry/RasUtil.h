// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1993 - 1998 Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   rasutil.h
//
//  PURPOSE:  contains rasutil declarations
//

#ifndef _RASUTIL_H
#define _RASUTIL_H

#define IDS_RASCS                    100
#define IDS_OPENPORT                 IDS_RASCS+ 0
#define IDS_PORTOPENED               IDS_RASCS+ 1
#define IDS_CONNECTDEVICE            IDS_RASCS+ 2
#define IDS_DEVICECONNECTED          IDS_RASCS+ 3
#define IDS_ALLDEVICESCONNECTED      IDS_RASCS+ 4
#define IDS_AUTHENTICATE             IDS_RASCS+ 5
#define IDS_AUTHNOTIFY               IDS_RASCS+ 6
#define IDS_AUTHRETRY                IDS_RASCS+ 7
#define IDS_AUTHCALLBACK             IDS_RASCS+ 8
#define IDS_AUTHCHANGEPASSWORD       IDS_RASCS+ 9
#define IDS_AUTHPROJECT              IDS_RASCS+10
#define IDS_AUTHLINKSPEED            IDS_RASCS+11
#define IDS_AUTHACK                  IDS_RASCS+12
#define IDS_REAUTHENTICATE           IDS_RASCS+13
#define IDS_AUTHENTICATED            IDS_RASCS+14
#define IDS_PREPAREFORCALLBACK       IDS_RASCS+15
#define IDS_WAITFORMODEMRESET        IDS_RASCS+16
#define IDS_WAITFORCALLBACK          IDS_RASCS+17
#define IDS_INTERACTIVE              IDS_RASCS+18
#define IDS_RETRYAUTHENTICATION      IDS_RASCS+19
#define IDS_CALLBACKSETBYCALLER      IDS_RASCS+20
#define IDS_PASSWORDEXPIRED          IDS_RASCS+21
#define IDS_CONNECTED                IDS_RASCS+22
#define IDS_DISCONNECTED             IDS_RASCS+23
#define IDS_RASCS_END                IDS_DISCONNECTED
#define IDS_TRANSCODE                IDS_RASCS+24
                                                                                               

UINT GetRasConnState( RASCONNSTATE rasconn );

#endif

