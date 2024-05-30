// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      findsp.cpp
//
// Abstract:
//      Implement functionality to find/select a Winsock Service Provider based
//      on selected options.
//
// Entry Points:
//      FindServiceProvider - find a service provider
//
// Author:
//      barry r. butterklee

#include "qosevent.h"




// Abstract:
//      Look for a service provider.  If QoS has been requested, then look for a 
//      QoS-enabled IP service provider.  Return TRUE only if a service provider 
//      is found that matches all the criteria. Also, if QoS was not requested do 
//      not pick a QoS-enabled service provider (even though that should NOT matter).
//
//      Notice that actual service provider names are different on NT and Win9x 
//      when searching for a service provider, you should not use the service provider 
//      name, but instead use the various flags in the protocol structure.
//
BOOL FindServiceProvider(
    int                 iProtocol,
    BOOL                bQos,
    BOOL                bMulticast,
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
    {
    int nRet;
    WSAPROTOCOL_INFO *lpProtocolBuf = NULL;
    DWORD dwBufLen = 0;
    DWORD dwErr;
    BOOL bProtocolFound = FALSE;


    // first have WSAEnumProtocols tell us how big a buffer is needed
    nRet = WSAEnumProtocols(NULL, lpProtocolBuf, &dwBufLen);
    if (SOCKET_ERROR != nRet)
        {
        printf("WSAEnumProtocols: should not have suceeded\n");
        }
    else if (WSAENOBUFS != (dwErr = WSAGetLastError()))
        {
        // WSAEnumProtocols failed for some reason not relating to buffer size 
        printf("WSAEnumProtocols(1): %d\n", WSAGetLastError());
        }
    else
        {
        // WSAEnumProtocols failed for the "expected" reason, allocate a buffer
        // of the needed size
        lpProtocolBuf = (WSAPROTOCOL_INFO *)malloc(dwBufLen);
        if (lpProtocolBuf)
            {
            // now we can call WSAEnumProtocols again with the expectation it will
            // succeed because we have allocated a big enough buffer.
            nRet = WSAEnumProtocols(NULL, lpProtocolBuf, &dwBufLen);
            if (SOCKET_ERROR == nRet)
                {
                printf("WSAEnumProtocols(3): %d\n", WSAGetLastError());
                }
            else
                {
                // loop thru protocols, looking for a matching service provider 
                for (int i=0; i<nRet; i++)
                    {
                    printf("  sp <%s>\n", lpProtocolBuf[i].szProtocol);
                    if (AF_INET == lpProtocolBuf[i].iAddressFamily &&
                        iProtocol == lpProtocolBuf[i].iProtocol)
                        {
                        // look for 
                        if (bQos && bMulticast)
                            {
                            if ((XP1_QOS_SUPPORTED == (XP1_QOS_SUPPORTED &
                                     lpProtocolBuf[i].dwServiceFlags1)) &&
                                (XP1_SUPPORT_MULTIPOINT == (XP1_SUPPORT_MULTIPOINT &                                              lpProtocolBuf[i].dwServiceFlags1)))
                                {
                                *pProtocolInfo = lpProtocolBuf[i];
                                bProtocolFound = TRUE;
                                break;
                                }
                            }
                        else if (bQos)
                            {
                            if ((XP1_QOS_SUPPORTED == (XP1_QOS_SUPPORTED &                                                        lpProtocolBuf[i].dwServiceFlags1)))
                                {
                                *pProtocolInfo = lpProtocolBuf[i];
                                bProtocolFound = TRUE;
                                break;
                                } 
                            }
                        else if (bMulticast)
                            {
                            if ((XP1_SUPPORT_MULTIPOINT == (XP1_SUPPORT_MULTIPOINT &                                              lpProtocolBuf[i].dwServiceFlags1)) &&
                                (XP1_QOS_SUPPORTED != (XP1_QOS_SUPPORTED &                                                        lpProtocolBuf[i].dwServiceFlags1)))
                                {
                                *pProtocolInfo = lpProtocolBuf[i];
                                bProtocolFound = TRUE;
                                break;
                                }
                            }
                        else 
                            {
                            if ((XP1_QOS_SUPPORTED != (XP1_QOS_SUPPORTED &                                                        lpProtocolBuf[i].dwServiceFlags1)))
                                {
                                *pProtocolInfo = lpProtocolBuf[i];
                                bProtocolFound = TRUE;
                                break;
                                }
                            }
                        } 
                    } // for    
                } // WSAEnumProtocols
            free(lpProtocolBuf);
            } // lpProtocolBuf
        } // WSAEnumProtocols

    if (bProtocolFound)
        printf("  Using service provider <%s>\n\n", pProtocolInfo->szProtocol);

    return(bProtocolFound);
    }

