// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      setqos.cpp
//
// Abstract:    
//      This file contains the functionality needed to fill in a 
//      QOS structure. 
//
// Entry Points:
//      SetQos 
//
// Author:
//      Barry R. Butterklee

#include "qosevent.h"





static VOID FillQosFlowspecDefault(QOS *pQos, DWORD *cbQosLen, QOS_OPTIONS *pQosOptions);
static BOOL FillQosProviderSpecific(QOS *pQos, DWORD *cbQosLen, QOS_OPTIONS *pQosOptions);




// Abstract:
//      Depending upon commandline QoS options, either use some default values
//      (see FillQosDefault) or pick up the QoS data by template name.
//
BOOL SetQos(
    SOCKET          sd, 
    QOS_OPTIONS     *pQosOptions,
    BOOL            bSetQos,
    QOS             *pQos, 
    DWORD           *cbQosLen 
    )
    {
    int nRet;
    WSABUF wsabuf;
    DWORD dwBytes;
    BOOL bError = FALSE;


    // fill in some default values
    if (stricmp(pQosOptions->szTemplate, QOS_DEFAULTNAME) == 0)
        {
        FillQosFlowspecDefault(pQos, cbQosLen, pQosOptions);
        }
    else 
        {       
        ZeroMemory(pQos, sizeof(QOS));
        ZeroMemory((char *)&wsabuf, sizeof(wsabuf));
        wsabuf.len = strlen(pQosOptions->szTemplate) + 1;
        wsabuf.buf = (char *)malloc(wsabuf.len);
        strcpy(wsabuf.buf, pQosOptions->szTemplate);
        if (!WSAGetQOSByName(sd, &wsabuf, pQos))
            {
            printf("WSAGetQosByName: %d\n", WSAGetLastError());
            bError = TRUE;
            }
        else
            {
            if (pQosOptions->bReceiver)
                {
                pQos->SendingFlowspec   = default_notraffic;
                if (pQosOptions->bFixTemplate)
                    {
                    pQos->ReceivingFlowspec.TokenRate /= 8;
                    pQos->ReceivingFlowspec.PeakBandwidth /= 8;
                    }
                }
            else
                {
                pQos->ReceivingFlowspec = default_notraffic;
                if (pQosOptions->bFixTemplate)
                    {
                    pQos->SendingFlowspec.TokenRate /= 8;
                    pQos->SendingFlowspec.PeakBandwidth /= 8;
                    }
                }

            pQos->ProviderSpecific.len = 0;
            pQos->ProviderSpecific.buf = NULL;
            *cbQosLen = sizeof(QOS) + pQos->ProviderSpecific.len;
            }
        }

    if (!bError)
        {
        if (pQosOptions->bDisableSignalling)
            {
            pQos->ReceivingFlowspec.ServiceType |= SERVICE_NO_QOS_SIGNALING;
            }

        if (!FillQosProviderSpecific(pQos, cbQosLen, pQosOptions))
            {
            bError = TRUE;
            }
        }

    if (!bError && bSetQos)
        {
        RSVP_STATUS_INFO rsvpStatus;

        if (pQosOptions->bFineGrainErrorAvail)
            {
            // uncomment next line to test error handling on SIO_SET_QOS
            // pQos->ReceivingFlowspec.ServiceType = 0x555;
            nRet = WSAIoctl(sd, SIO_SET_QOS, (LPVOID)pQos, *cbQosLen, 
                &rsvpStatus, sizeof(RSVP_STATUS_INFO), &dwBytes, NULL, NULL);
            if (SOCKET_ERROR == nRet)
                {
                printf("WSAIoctl(SIO_SET_QOS) %d, \n\tStatusCode=%d\n\tExtendedStatus1=%d\n\tExtendedStatus2=%d\n", 
                    WSAGetLastError(),
                    rsvpStatus.StatusCode, 
                    rsvpStatus.ExtendedStatus1, 
                    rsvpStatus.ExtendedStatus2);
                bError = TRUE;
                }
            else
                bError = FALSE;
            }
        else
            {
            nRet = WSAIoctl(sd, SIO_SET_QOS, (LPVOID)pQos, *cbQosLen, 
                NULL, 0, &dwBytes, NULL, NULL);
            if (SOCKET_ERROR == nRet)
                {
                printf("WSAIoctl(SIO_SET_QOS) %d\n", WSAGetLastError());
                bError = TRUE;
                }
            else
                bError = FALSE;
            }
        }

    return(!bError);
    }





// Abstract:
//      Fill in default values for QoS structure.  The default values were
//      simply choosen from existing QOS templates available via WSAGetQosByName.
//      Notice that ProviderSpecific settings are being allowed when picking the 
//      "default" template but not for "well-known" QOS templates.  Also notice 
//      that since data is only flowing from sender to receiver, different 
//      flowspecs are filled in depending upon whether this application is 
//      acting as a sender or receiver.
// 
static VOID FillQosFlowspecDefault(
    QOS             *pQos, 
    DWORD           *cbQosLen, 
    QOS_OPTIONS     *pQosOptions
    )
    {

    if (pQosOptions->bReceiver)
        {
        pQos->ReceivingFlowspec = default_g711;
        pQos->SendingFlowspec   = default_notraffic;        
        }
    else
        {
        pQos->SendingFlowspec   = default_g711;     
        pQos->ReceivingFlowspec = default_notraffic;
        }

    // allocate enough space for a RSVP_STATUS_INFO structure to be returned upon error.
    pQos->ProviderSpecific.len = 0;
    pQos->ProviderSpecific.buf = NULL;
    *cbQosLen = sizeof(QOS) + pQos->ProviderSpecific.len;
    return;
    }




// Abstract:
//      Fill in the Provider-specific portion of the QOS structure.  Potentially
//      no provider-specific changes may need to be made or an existing
//      provider-specific buffer may need to be added to and/or changed. 
//
//      *** Currently if a Provider-specific buffer already exists it is not 
//      overwritten and this call will fail.
//
static BOOL FillQosProviderSpecific(
    QOS             *pQos, 
    DWORD           *cbQosLen, 
    QOS_OPTIONS     *pQosOptions
    )
    {
    DWORD cbProviderSpecificLen = 0;


    if (!pQosOptions->bProviderSpecific)
        return(TRUE);

    if (0 != pQos->ProviderSpecific.len)
        {
        printf("FillQosProviderSpecific: reallocating existing ProviderSpecific buf not supported\n");
        return(FALSE);
        }

    if (pQosOptions->bReceiver)
        {
        if (pQosOptions->bConfirmResv)
            {
            static RSVP_RESERVE_INFO RsvpResv;    // since we are returning a ptr to this
                                                  //   structure it must be static

            ZeroMemory((char *)&RsvpResv, sizeof(RsvpResv));
            RsvpResv.ObjectHdr.ObjectType = RSVP_OBJECT_RESERVE_INFO;
            RsvpResv.ObjectHdr.ObjectLength = sizeof(RsvpResv);
            RsvpResv.Style = RSVP_DEFAULT_STYLE;
            RsvpResv.ConfirmRequest = 1; 
            RsvpResv.PolicyElementList = NULL;
            RsvpResv.NumFlowDesc = 0;
            RsvpResv.FlowDescList = NULL;
            pQos->ProviderSpecific.len = RsvpResv.ObjectHdr.ObjectLength;
            pQos->ProviderSpecific.buf = (char *)&RsvpResv;
            PrintQos(pQos, "  ");
            return(TRUE);
            }
        else
            return(TRUE);
        }
    else
        {
        // if sender and not multicast fill in QOS_DESTADDR
        // as well alloc a big enough buffer for all objects and memcpy the objects 
        // into the buffer.
        char *pBuf = NULL;
        char *pBufTmp = NULL;
        int len = 0;
        QOS_DESTADDR QosDestaddr;

        if (pQosOptions->bSetDestaddr)
            {
            ZeroMemory((char *)&QosDestaddr, sizeof(QosDestaddr));
            QosDestaddr.ObjectHdr.ObjectType   = QOS_OBJECT_DESTADDR;
            QosDestaddr.ObjectHdr.ObjectLength = sizeof(QosDestaddr);
            QosDestaddr.SocketAddress = (SOCKADDR *)&g_destaddr;
            QosDestaddr.SocketAddressLength = sizeof(g_destaddr);
            len += sizeof(QOS_DESTADDR);
            }

        if (!(pBuf = (char *)malloc(len)))
            return(FALSE);

        // copy QOS objects into buffer.  We could have avoided the buffer
        // copy, but it was felt that this method would be a bit more readable
        pBufTmp = pBuf;
        if (pQosOptions->bSetDestaddr)
            {            
            CopyMemory(pBufTmp, &QosDestaddr, sizeof(QosDestaddr));
            pBufTmp += sizeof(QOS_DESTADDR);
            }

        pQos->ProviderSpecific.len = len;
        pQos->ProviderSpecific.buf = pBuf;
        PrintQos(pQos, "  ");
        return(TRUE);
        }
    }

