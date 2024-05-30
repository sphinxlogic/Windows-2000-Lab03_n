// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      qosevent.cpp
//
// Abstract:
//      This application demonstrates how to GQOS-enable a simple Winsock 
//      application.  This application makes no attempt to do anything useful 
//      per se, but concentrates on illustrating key techniques to use when 
//      developing your GQOS-enabled application.  Additionally, this application 
//      demonstrates several Winsock2-specific APIs and techniques that are useful 
//      whether or not your main interest is GQOS-enabling your application.
//
//      Commandline parameters determine whether this application functions as 
//      either a sender (-n) or a receiver (default).  Use the -? commandline 
//      switch to determine available options.
//
//      This application simply sends a buffer of data when acting as the sender,
//      to an instance of itself acting as a receiver.  Any number of senders (up
//      to MAXCLIENTS) can be started to interact with one instance of a receiver.
//      The size of the data buffer (-b), its contents (-d), and the number of 
//      times to send (-l) this buffer are controllable via commandline switches. 
//      A repeat value of 0 implies continuous sending.  The (-c) commandline switch
//      allows enabling/disabling QOS on the socket every 5 sends and will cause any
//      repeat count entered to be overridden and set to continuous mode. A delay 
//      commandline switch (-s:#), measured in milliseconds can be specified for the 
//      sender to insure the total transfer spans a measured unit of time (this would 
//      be interesting for observing RSVP PATH/RESV message refresh).
//
//      The sender and receiver can choose to use either UDP or TCP (default) for data 
//      transfers by using the -p commandline option.  The port number (endpoint) used 
//      by TCP and UDP is also controllable via commandline switch (-e).  
//
//      The application is also multicast capable. A multicast receiver must specify
//      the multicast option (-m) and the multicast IP address to join or allow a
//      default to be used.  The sender has the option of sending data directly to that 
//      multicast address (with the -n option) or joining the multicast group as well 
//      (using the -n and -m options).  When both -n and -m values are used (by a
//      multicast sender) any address specified in -n is overriden by the value used
//      in -m.
//
//      This application can be enabled to support GQOS by specifying a specific GQOS
//      template to use (-q) for transfers.  Additionally, when to enable GQOS 
//      (i.e. when to inform the GQOS Service Provider) can be controlled via a 
//      commandline switch (-i).  The priority to use for sending data is also 
//      controllable via a commandline switch (-tc-priority). 
//
// Entry Points:
//      main - this is where it all starts
//
// Usage:
//      Act as a TCP receiver and enable QOS using g711 codec
//          qosevent -q:g711
//      Act as a TCP sender and enable QOS using g711 and send buffer 10 times
//          qosevent -n:receiver_host -q:g711 -l:10
//      Act as a UDP sender and enable QOS using g711, set QOS during connect, send 
//      buffer 30 times with a 2 second delay between sends
//          qosevent -p:udp -n:receiver_host -q:g711 -i:d -l:30 -s:2000
//      Act as a TCP sender, no QOS, and send buffer once
//          qosevent -n:receiver_host
//      Act as a UDP sender, no QOS, and send buffer once
//          qosevent -n:receiver_host
//      Act as a multicast receiver and enable QOS using g711
//          qosevent -q:g711 -m:234.5.6.7
//
// Build:
//      Use the headers and libs from the June98 Platform SDK or later.
//      Link with ws2_32.lib
//      
// Author:
//      Barry R. Butterklee
//
// Changes:
//      8/99 - Correct handling of SIO_GET_QOS for Windows 2000 (and workaround for Windows 98)
//             added to GetQos().
//      8/99 - Fix handling of RSVP_RESERVE_INFO in PrintQos() and SetQos()
//      8/99 - Remove obsolete QOS_OBJECT_PRIORITY
//      8/99 - Update comments in CreateSendingSocket


#define QOSEVENT_MAIN
#include "qosevent.h"
    

static BOOL ValidOptions(char *argv[], int argc, OPTIONS *pOptions);
static VOID PrintOptions(OPTIONS *pOptions);
static VOID Usage(CHAR *szProgramname, OPTIONS *pOptions);




int main(int argc, char *argv[])
    {
    int n;
    OPTIONS options;
    WSADATA WSAData; 
    WSAPROTOCOL_INFO protocol_info;


    if (!ValidOptions(argv, argc, &options))
        exit(1);

    if ((n = WSAStartup(MAKEWORD(2,2), &WSAData)))
        {
        printf("WSAStartup %d\n", n);
        exit(1);
        }

    if (!FindServiceProvider(
            options.spOptions.iProtocol, 
            options.spOptions.bQos,
            options.spOptions.bMulticast,
            &protocol_info))
        {
        printf("No matching service provider found\n");
        }
    else
        {   
        PrintOptions(&options);
        if (options.qosOptions.bReceiver)
            Receiver(&options, &protocol_info);
        else
            Sender(&options, &protocol_info);
        }

    free(options.buf);
    WSACleanup();
    return(0);
    }




// Abstract:
//      Verify options passed in and set options structure accordingly.
//
BOOL ValidOptions(char *argv[], int argc, OPTIONS *pOptions)
    {
    BOOL        bValidOptions = TRUE;
    OSVERSIONINFO   verInfo = {0};


    *pOptions = default_options;

    for (int i=1; i<argc; i++)
        {
        if ((argv[i][0] == '-') || (argv[i][0] == '/') ) 
            {
            switch(tolower(argv[i][1])) 
                {
                case 'b' :
                    if (strlen(argv[i]) > 3)
                        pOptions->nBufSize = 1024*atoi(&argv[i][3]);
                    break;

                case 'c' :
                    pOptions->qosOptions.bAlternateQos = TRUE;
                    break;

                case 'd' :
                    if (strlen(argv[i]) > 3)
                        pOptions->fillchar = argv[i][3];
                    break;

                case 'e' :
                    if (strlen(argv[i]) > 3)
                        pOptions->port = atoi(&argv[i][3]);
                    break;

                case 'i' :
                    if (strlen(argv[i]) > 3)
                        {
                        if ('a' == argv[i][3] || 'A' == argv[i][3])
                            pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_AFTER;
                        else if ('b' == argv[i][3] || 'B' == argv[i][3])
                            pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;
                        else if ('d' == argv[i][3] || 'D' == argv[i][3])
                            pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_DURING;
                        else if ('q' == argv[i][3] || 'Q' == argv[i][3])
                            pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_QOS;
                        else
                            pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;
                        }
                    break;

                case 'l' :
                    if (strlen(argv[i]) > 3)
                        pOptions->nRepeat = atoi(&argv[i][3]);
                    break;

                case 'm' :
                    pOptions->spOptions.bMulticast = TRUE;
                    if (strlen(argv[i]) > 3)
                        strcpy(pOptions->szHostname, &argv[i][3]);
                    else
                        strcpy(pOptions->szHostname, DEFAULT_MULTICASTGROUP);
                    break;

                case 'n' : 
                    pOptions->qosOptions.bReceiver = FALSE; 
                    // multicast group overrides hostname on -n
                    if (!pOptions->spOptions.bMulticast)
                        {
                        if (strlen(argv[i]) > 3)
                            strcpy(pOptions->szHostname, &argv[i][3]);
                        }
                    break;

                case 'p' :
                    if (strlen(argv[i]) > 3)
                        {
                        if ('u' == argv[i][3] || 'U' == argv[i][3])
                            pOptions->spOptions.iProtocol = IPPROTO_UDP;
                        else if ('t' == argv[i][3] || 'T' == argv[i][3])
                            pOptions->spOptions.iProtocol = IPPROTO_TCP;
                        else
                            pOptions->spOptions.iProtocol = IPPROTO_TCP;
                        }
                    break;

                case 'q' : 
                    pOptions->spOptions.bQos = TRUE; 
                    if (strlen(argv[i]) > 3)
                        strcpy(pOptions->qosOptions.szTemplate, &argv[i][3]);
                    break;

                case 'r' :
                    if (strlen(argv[i]) > 3)
                        {
                        if ((stricmp(argv[i], "-rsvp-confirm") == 0) ||
                            (stricmp(argv[i], "-rsvp_confirm") == 0))
                            {
                            pOptions->qosOptions.bConfirmResv = TRUE;
                            pOptions->qosOptions.bProviderSpecific = TRUE;
                            }
                        else if ((stricmp(argv[i], "-rsvp-wait") == 0) ||
                            (stricmp(argv[i], "-rsvp_wait") == 0))
                            {
                            pOptions->qosOptions.bWaitToSend = TRUE;
                            pOptions->qosOptions.bProviderSpecific = TRUE;
                            }
                        else
                            {
                            printf("Ignoring option <%s>\n", argv[i]);
                            }
                        }
                    break;

                case 's' :
                    if (strlen(argv[i]) > 3)
                        pOptions->dwSleep = atoi(&argv[i][3]);
                    break;

                case '?' :
                    Usage(argv[0], &default_options);
                    return(FALSE);
                    break;

                default:
                    printf("  unknown options flag %s\n", argv[i]);
                    Usage(argv[0], &default_options);
                    return(FALSE);
                    break;
                }
            }
        else
            {
            printf("  unknown option %s\n", argv[i]);
            Usage(argv[0], &default_options);
            return(FALSE);
            }
        }


    if (pOptions->qosOptions.bReceiver)
        pOptions->fillchar = 0;

    if (pOptions->spOptions.bMulticast)
        {
        pOptions->spOptions.iProtocol = IPPROTO_UDP;
        pOptions->qosOptions.bSetDestaddr = FALSE;
        }

    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
        {
        pOptions->spOptions.bMulticast = FALSE;
        pOptions->qosOptions.bSetDestaddr = FALSE;
        }
    else if (!pOptions->spOptions.bMulticast)
        pOptions->qosOptions.bSetDestaddr = TRUE;

    if (pOptions->spOptions.bQos)
        {
        if (pOptions->qosOptions.bReceiver && pOptions->qosOptions.bWaitToSend)
            pOptions->qosOptions.bWaitToSend = FALSE;  // not a valid receiver option

        if (!pOptions->qosOptions.bReceiver && pOptions->qosOptions.bConfirmResv)
            pOptions->qosOptions.bWaitToSend = FALSE;  // not a valid sender option

        if (pOptions->qosOptions.bAlternateQos)
            pOptions->nRepeat = 0;  // override repeat count to continuous mode

        if ((IPPROTO_UDP == pOptions->spOptions.iProtocol) && 
            (!pOptions->spOptions.bMulticast))
            {
            // using UDP, there WSAAccept will not be called, therefore do not wait to set qos
            pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;
            }

        verInfo.dwOSVersionInfoSize = sizeof(verInfo);
        GetVersionEx(&verInfo);
        switch (verInfo.dwPlatformId)
            {
            case VER_PLATFORM_WIN32_NT:
                pOptions->qosOptions.bQueryBufferSize = TRUE;
                pOptions->qosOptions.bMustSetQosInAccept = FALSE;
                pOptions->qosOptions.bFineGrainErrorAvail = TRUE;
                pOptions->qosOptions.bQosabilityIoctls = TRUE;
                printf("running on NT\n");
                break;

            case VER_PLATFORM_WIN32_WINDOWS:
                pOptions->qosOptions.bQueryBufferSize = FALSE;
                pOptions->qosOptions.bMustSetQosInAccept = TRUE;
                pOptions->qosOptions.bFineGrainErrorAvail = FALSE;
                pOptions->qosOptions.bQosabilityIoctls = FALSE;
                printf("running on 9x\n");
                break;

            default:
                printf ("requires Windows NT or Windows 98\n");
                pOptions->qosOptions.bQueryBufferSize = FALSE;
                pOptions->qosOptions.bMustSetQosInAccept = TRUE;
                pOptions->qosOptions.bFineGrainErrorAvail = FALSE;
                pOptions->qosOptions.bQosabilityIoctls = FALSE;
                break;
            }
        }

    if (!(pOptions->buf = (char *)malloc(pOptions->nBufSize)))
        return(FALSE);
    else
        {
        FillMemory(pOptions->buf, pOptions->nBufSize, pOptions->fillchar);
        return(TRUE);
        }
    }




// Abstract:
//      Just print the options to be used for this run.
//
static VOID PrintOptions(OPTIONS *pOptions)
    {
    printf("Options\n");
    printf("  Protocol %d\n", pOptions->spOptions.iProtocol);
    printf("  Port %d\n", pOptions->port);
    if (pOptions->qosOptions.bReceiver)
        printf("  Act as Receiver\n");
    else
        {
        printf("  Act as sender and send to %s\n", pOptions->szHostname);
        printf("  Sleep %d milliseconds between sends\n", pOptions->dwSleep);
        printf("  Fill buffer with <%c>\n", pOptions->fillchar);
        if (pOptions->nRepeat)
            printf("  Repeat sending the buffer %d times\n", pOptions->nRepeat);
        else
            printf("  Repeat sending the buffer continually\n");

        }
    printf("  Bufsize %d (1K increments)\n", pOptions->nBufSize);
    printf("  Multicast is %s\n", (pOptions->spOptions.bMulticast ? "Enabled" : "Disabled"));

    if (pOptions->spOptions.bQos)
        {
        printf("  Qos template %s\n", pOptions->qosOptions.szTemplate);
        printf("  Qos to be set ");
        switch (pOptions->qosOptions.qosIoctlSet)
            {
            case QOS_IOCTL_SET_BEFORE: 
                printf("Before accept/connect/joinleaf\n");
                break;
            case QOS_IOCTL_SET_AFTER:  
                printf("After accept/connect/joinleaf\n"); 
                break;
            case QOS_IOCTL_SET_DURING: 
                printf("During accept/connect/joinleaf\n");
                break;
            case QOS_IOCTL_SET_QOS: 
                if (pOptions->qosOptions.bReceiver)
                    printf("During FD_QOS, implies QOS with no signaling set before accept/connect (eventually)\n");
                else
                    {
                    pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;
                    printf("Before connect\n");
                    }
                break;
            }

        if (pOptions->qosOptions.bConfirmResv )
            printf("  RESV confirmation to be requested\n");
        if (INVALID_SEND_PRIORITY != pOptions->qosOptions.SendPriority)
            printf("  Qos TC SendPriority to be set to %d\n", 
                pOptions->qosOptions.SendPriority);
        if (!pOptions->qosOptions.bReceiver)
            {
            if (pOptions->qosOptions.bWaitToSend)
                printf("  Wait for RESV before sending data\n");
            else
                printf("  Do not wait for RESV to start sending data\n");
            }
        else
            printf("  Qos must be set during Accept = %s\n", 
                (pOptions->qosOptions.bMustSetQosInAccept?"TRUE":"FALSE"));
           
        printf("  Query for QOS buffer size: %s\n",
            (pOptions->qosOptions.bQueryBufferSize?"TRUE":"FALSE"));
        }
    printf("\n");
    return;
    }




// Abstract:
//      Print out usage table for the program
//
VOID Usage(CHAR *szProgramname, OPTIONS *pOptions)
    {
    printf("usage:\n  %s -?\n\n", szProgramname);
    printf("  %s [-b:#] [-d:c] [-e:#] [-l:#] [-m:group] [-n:host] [-s:#] [-u]\n\t[-q:template [-i:[a|b|d|q]] [-c] [-rsvp-confirm] [-rsvp-wait]]\n\n",
        szProgramname);
    printf("  -?\t\tDisplay this help\n");
    printf("\n");
    printf("  -b:bufsize\tSize of send/recv buffer; in 1K increments (Def:%d)\n",
        pOptions->nBufSize);
    printf("  -d:c\t\tCharacter used to fill buffer (Def:%c)\n",
        pOptions->fillchar);
    printf("  -e:port\tEndpoint number (port) to use (Def:%d)\n",
        pOptions->port);
    printf("  -l:loop\tLoop count for sending buffer (0==>continuous)\n",
        pOptions->nRepeat);
    printf("  -m:group\tMulticast group (IP) to join (Def:%s)\n", 
        DEFAULT_MULTICASTGROUP);
    printf("  -n:host\tAct as the client and connect to 'host' (Def:%s)\n",
        pOptions->szHostname);
    printf("  -p:protocol\tTCP or UDP (def:TCP)\n");
    printf("  -s:#\t\tSleep # milliseconds between sends (def: 0)\n");
    printf("\n");
    printf("  -q:template\tEnable QoS and use 'template' to specify the name (Def:%s)\n",
        pOptions->qosOptions.szTemplate);
    printf("  -c\t\tCycle enabling/disabling QOS on sending socket (Def: no cycling)\n");
    printf("  -i:[a|b|d|q]\tSet Qos After, Before, During accept/connect, or during FD_QOS\n\t\t\t(def: Before)\n");
    printf("  -rsvp-confirm\t\tRequest RESV confirmation be sent (Def: no confirmation)\n");
    printf("  -rsvp-wait\t\tWait for RESV from receiver before sending data\n");
    return;
    }

