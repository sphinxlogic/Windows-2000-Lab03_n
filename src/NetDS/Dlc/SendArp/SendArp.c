/*
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.


Module Name:

   SendArp.c

Required modules:

   dlcapi.lib  ( AcsLan() )
   ws2_32.lib  ( inet_addr(), inet_ntoa(), htons() )

Author:

   Gary Yukish (garyy)    15-July-98

Abstract:

   This module illustrates how to use the Windows NT DLC API to post
   and receive an ARP query to a Direct Station on an Ethernet adapter.
   The code retrieves the MAC address given a specific IP address.

   The format for the Ethernet Frame and ARP Packet were taken from 
   "TCP/IP Illustrated,	Volume 1 The Protocols" by W. Richard Stevens.
   Pages 21-23 and 56-57.

   Given the local Hardware Address, IP Address and a Destination IP
   Address, this program will broadcast a request to get the Hardware
   Address that the Destination IP Address is assigned to.

   It then reads frames from the Network adapter until an ARP Reply is
   received.

   The application uses the AcsLan() api to send DLC commands to the DLC
   protocol.  The basic idea with using this function is that you create
   a CCB (command control block) that contains the LLC command you want 
   to use, parameters and data buffers applicable to that command.  For 
   instance the LLC_DIR_OPEN_DIRECT function requires that you pass a
   pointer to a LLC_DIR_OPEN_DIRECT_PARMS structure that it can fill in.

   The standard pattern for issuing a DLC command is:
   1) ZeroMemory the LLC_CCB structure.
   2) Set the uchDlcCommand member of the CCB to the command you want to call.
   3) ZeroMemory any buffers you are going to pass along to the command.
   4) Fill in any settings in the CCB structure and other structures you are
      passing.
   5) Set the hCompletionEvent member of the CCB to an event you had 
      previously created.
   6) ResetEvent the hCompletionEvent.
   7) Make the AcsLan API call passing the CCB you created.
   8) WaitForSingleObject on the event you set.
   9) Check the results for Success, TimeOut or Error.
   
   You must have the DLC protocol installed for the application
   to work correctly. The application was tested on WinNT 3.51, 
   WinNT 4.0.

   Using AcsLan to control the DLC Protocol
   ========================================
   The command sequence used by this sample follows the following logic.

   1)  LLC_DIR_INITIALIZE
   2)  LLC_DIR_OPEN_ADAPTER
   3)  LLC_DIR_OPEN_DIRECT          
   4)  LLC_BUFFER_CREATE
   5)  LLC_BUFFER_GET
   6)  LLC_BUFFER_FREE
   7)  LLC_RECEIVE
   8)  LLC_TRANSMIT_DIR_FRAME

   LOOP
      9)  LLC_READ
      10) LLC_BUFFER_FREE
   UNTIL LLC_READ fails or good data received

   11) LLC_RECEIVE_CANCEL
   12) LLC_DIR_CLOSE_DIRECT
   13) LLC_DIR_CLOSE_ADAPTER

   Other sources of information DLC
   ================================
   "A C Programmer's Guide to the IBM Token Ring", by William H. Roetzheim

   "IBM LAN Technical Reference  IEEE 802.2 and NETBIOS Application Program Interface", by IBM.
   The book is out of print but is available in a software format at www.ibm.com. 
   As of 7/10/98 it was available at: 
   http://service2.boulder.ibm.com/devcon/showcase/cat/bk8p7000.htm
   or seach their web page on "IEEE 802.2"
   

*/

#include <windows.h>
#include <dlcapi.h>
#include <stdio.h>

#define STATION_ID 0
#define ADAPTER_ID 0

#pragma pack(push, 2)   //The structure must be packed on a 2 byte alignment
                        //in order for it to go accross the internet as one IP Packet
struct ethernet_hdr {
   char dest[6];        // ETHERNET MANDATED PACKET HEADER
   char src[6];         // (14 bytes)
   WORD type;           // Filled in by adapter
} *PETHER;

typedef struct arp_packet
{
   struct ethernet_hdr;
   WORD  hardType;      //Type of Hardware Address: 1 for Ethernet
   WORD  protType;      //Type of Protocol: 0x0800 for IP, 0x0806 for ARP
   BYTE  hardSize;      //Size of Hardware Address: 6 for Ethernet
   BYTE  protSize;      //Size of Protocol Address: 4 for IP addresses
   WORD  opCode;        //Operation Code: 1=ARP Request, 2=ARP Reply, 3=RARP Request, 4=RARP Reply
   BYTE  srcAddr[6];    //Hardware Address of source
   ULONG srcIP;         //IP Address of source
   BYTE  destAddr[6];   //Hardware Address of destination
   ULONG destIP;        //IP address of destination
   char  padding[18];
} ARP_PACKET, *PARP_PACKET;

#pragma pack(pop)

void twiddle_bits(LPBYTE, DWORD );
void FillArpPacket(PARP_PACKET a, LPSTR srcAddr, LPSTR srcIPAddress, LPSTR ipAddr);
void PrintNext(LPBYTE *t, int c);

#define RECEIVE_COMPLETE_FLAG   0x80204030
#define RECEIVE_DATA_FLAG       0x80204040   //Unique flag to test if its my data

#define BUFFSIZE 2000
char BigBuff[20000]; //Create a buffer to receive info from the adapter

void main (int argc, char *argv[])
{  
   LLC_CCB CCB, *pBadCCB;
   char headerBuff[255];
   PLLC_XMIT_BUFFER pxmitBuff=(PLLC_XMIT_BUFFER) headerBuff;
   ACSLAN_STATUS rtrn;
   HANDLE hEvent;
   LLC_DIR_INITIALIZE_PARMS   InitParms;
   LLC_DIR_OPEN_ADAPTER_PARMS OpenParms;
   LLC_DIR_OPEN_DIRECT_PARMS  OpenDirectParms;
   LLC_DLC_PARMS              DlcParms;
   LLC_ADAPTER_OPEN_PARMS     AdapterOpenParms;
   LLC_EXTENDED_ADAPTER_PARMS ExtendedAdapterParms;
   LLC_TRANSMIT_PARMS         TransmitParms;
   LLC_RECEIVE_PARMS          ReceiveParms;
   LLC_READ_PARMS             ReadParms;
   LLC_BUFFER_CREATE_PARMS    BufferCreateParms;
   LLC_BUFFER_GET_PARMS       BufferGetParms;
   LLC_BUFFER_FREE_PARMS      BufferFreeParms;
   UCHAR AppID;
   HANDLE BufferHandle;
   LPBYTE BufferPool = (LPBYTE)BigBuff;
   DWORD readStatus;
   BOOL Done = FALSE;
   UCHAR *pStat = &CCB.uchDlcStatus;
   char verbose = 0;


   ARP_PACKET a;
   if(argv[argc-1][1]=='v')
      verbose=argc--;

   if(argc<3)
   {
      printf("Syntax: SendRaw LocalIPAddress RemoteIPAddress [/v]\n"
          "Sample: SendRaw 157.24.176.111 157.24.176.1\n"
          "\n/v displays the frames as they are received.\n\n");
      return;
   }

   hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

   // Initialize DLC
   ZeroMemory(&CCB, sizeof(CCB));
   CCB.uchDlcCommand = LLC_DIR_INITIALIZE;
   ZeroMemory(&InitParms, sizeof(InitParms));
   CCB.u.pParameterTable = (PLLC_PARMS)&InitParms;
   rtrn = AcsLan(&CCB, &pBadCCB);
   printf("%-22s returned %u \tStatus: 0x%X\n","LLC_DIR_INITIALIZE",rtrn,*pStat);
   if(*pStat==0)
   {
      // Open the Adapter
      ZeroMemory(&CCB, sizeof(CCB));
      CCB.uchDlcCommand = LLC_DIR_OPEN_ADAPTER;
      ZeroMemory(&OpenParms, sizeof(OpenParms));
      CCB.u.pParameterTable = (PLLC_PARMS)&OpenParms;
      ZeroMemory(&AdapterOpenParms, sizeof(AdapterOpenParms));
      OpenParms.pAdapterParms = &AdapterOpenParms;
      ZeroMemory(&ExtendedAdapterParms, sizeof(ExtendedAdapterParms));
      ExtendedAdapterParms.LlcEthernetType=LLC_ETHERNET_TYPE_DEFAULT;
      OpenParms.pExtendedParms = &ExtendedAdapterParms;
      ZeroMemory(&DlcParms, sizeof(DlcParms));
      OpenParms.pDlcParms = &DlcParms;
      CCB.hCompletionEvent = hEvent;
      ResetEvent(hEvent);
      rtrn = AcsLan(&CCB, &pBadCCB);
      WaitForSingleObject(hEvent, 5000);
      //format bits from IBM Token ring format to Ethernet MAC address format
      twiddle_bits(AdapterOpenParms.auchNodeAddress, 6);  
      printf("%-22s returned %u \tStatus: 0x%X\n", "LLC_DIR_OPEN_ADAPTER", rtrn, *pStat);
      AppID = CCB.uchReserved2;
      if(*pStat==0)
      {
         //LLC_BUFFER_CREATE - Create a buffer to receive frame directed at the direct station
         ResetEvent(hEvent);
         ZeroMemory(&CCB, sizeof(CCB));
         CCB.uchDlcCommand = LLC_BUFFER_CREATE; 
         ZeroMemory(&BufferCreateParms, sizeof(BufferCreateParms));
         ZeroMemory(&BigBuff, sizeof(BigBuff));
         BufferCreateParms.pBuffer = BigBuff;
         BufferCreateParms.cbBufferSize = sizeof(BigBuff);
         BufferCreateParms.cbMinimumSizeThreshold=sizeof(BigBuff) / 4;
         CCB.u.pParameterTable = (PLLC_PARMS)&BufferCreateParms;
         CCB.hCompletionEvent = hEvent;
         CCB.uchReserved2 = AppID;
         rtrn = AcsLan(&CCB, &pBadCCB);
         if(WaitForSingleObject(hEvent, 5000) == WAIT_TIMEOUT)
            printf("Buffer.Create Timed out.\n");
         BufferHandle = BufferCreateParms.hBufferPool;
         printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_BUFFER_CREATE", rtrn, *pStat);
         if(*pStat==0)
         {
            //LLC_BUFFER_GET - Test & Initialize the buffer by getting the entire buffer
            ResetEvent(hEvent);
            ZeroMemory(&CCB, sizeof(CCB));
            ZeroMemory(&BufferGetParms, sizeof(BufferGetParms));
            BufferGetParms.cBuffersToGet = 1;
            BufferGetParms.cbBufferSize = 256;

            CCB.uchDlcCommand = LLC_BUFFER_GET;
            CCB.u.pParameterTable = (PLLC_PARMS)&BufferGetParms;
            CCB.hCompletionEvent = hEvent;
            CCB.uchReserved2 = AppID;

            rtrn = AcsLan(&CCB, NULL);
            if(WaitForSingleObject(hEvent, 5000) == WAIT_TIMEOUT)
               printf("LLC_BUFFER_GET Timed out.\n");
            printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_BUFFER_GET", rtrn, *pStat);
            if(*pStat==0)  
            {
               //LLC_BUFFER_FREE - Free the entire buffer you grabbed earlier
               ResetEvent(hEvent);
               ZeroMemory(&CCB, sizeof(CCB));
               ZeroMemory(&BufferFreeParms, sizeof(BufferFreeParms));
               BufferFreeParms.pFirstBuffer = BufferGetParms.pFirstBuffer;

               CCB.uchDlcCommand = LLC_BUFFER_FREE;
               CCB.u.pParameterTable = (PLLC_PARMS)&BufferFreeParms;
               CCB.hCompletionEvent = hEvent;
               CCB.uchReserved2 = AppID;

               rtrn = AcsLan(&CCB, NULL);
               if(WaitForSingleObject(hEvent, 5000) == WAIT_TIMEOUT)
                  printf("LLC_BUFFER_FREE Timed out.\n");
               printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_BUFFER_FREE", rtrn, *pStat);
               if(*pStat==0)
               {
                  // Open the Direct Station
                  ZeroMemory(&CCB, sizeof(CCB));
                  CCB.uchDlcCommand = LLC_DIR_OPEN_DIRECT; 
                  ZeroMemory(&OpenDirectParms, sizeof(OpenDirectParms));
                  CCB.uchReserved2 = AppID;
                  CCB.u.dlc.usStationId=STATION_ID;
                  /************************************************************************************/
                  //One of the most important parts of getting this to work is getting the 
                  //correct Protocol Type and offset established.  
         
                  //EFFECT ON RECEIVING FRAMES:
                  //=========================
                  //The Receive command is going to use these values to decide what frames to pick up.

                  //For an ARP Packet the protocol type is loaded 2 bytes into the frame itself
                  //Whenever LLC_DIR_OPEN_DIRECT sees anything other than the following values:

                     // LLC_ETHERNET_TYPE_DEFAULT,      // use the parameter value set in registry
                     // LLC_ETHERNET_TYPE_AUTO,         // automatic header type selction for links
                     // LLC_ETHERNET_TYPE_802_3,        // use always 802.3 lan headers
                     // LLC_ETHERNET_TYPE_DIX           // use always LLC on DIX SNA type.
         
                  //it will compare the 2 bytes in the protocol frame offset by the value of 
                  //OpenDirectParms.usProtocolTypeOffset (in this case 2 bytes), AND them together
                  //and compare the result with OpenDirectParms.ulProtocolTypeMatch.

                  //FROM THE PLATFORM SDK:
                  //The ulProtoTypeMask, ulProtocolTypeMatch, and usProtocolTypeOffset members are optional. 
                  //They specify the protocol type mask, match, and offset, respectively. 
                  //They receive frames for a particular subprotocol type or socket. 
                  //That is, the packet is received whenever the following statement is true: 

                  //(* (PULONG)((PUCHAR)pFrame + 14 + offset) & mask) == match


                  //EFFECT ON SENDING FRAMES:
                  //========================
                  //It also uses the OpenDirectParms.usEthernetType to determine how to setup the frame
                  //to be transmitted.
                  //In an Ethernet Frame bytes 13 & 14 are the type of frame that is sent, the same bytes
                  //are used to show the length of an 802.3 frame.  No Ethernet types are valid lengths for
                  //an 802.3 frame. The AcsLan API looks at the proto type located in the ethernet frame offset
                  //by the value of usProtocolTypeOffset value.  If this is a valid frame type then it continues
                  //otherwise it assumes it is a length value and you'll probably end up transmitting an 
                  //unknown frame type.

                  OpenDirectParms.usEthernetType=0x0806;       //SUB Protocol Type: ARP;
                  OpenDirectParms.ulProtocolTypeMask=0x0000;
                  OpenDirectParms.ulProtocolTypeMatch=0x0000;
                  OpenDirectParms.usProtocolTypeOffset=2;
                  /************************************************************************************/
                  CCB.u.pParameterTable = (PLLC_PARMS)&OpenDirectParms;
                  CCB.hCompletionEvent = hEvent;
                  ResetEvent(hEvent);
                  rtrn = AcsLan(&CCB, &pBadCCB);
                  WaitForSingleObject(hEvent, 5000);
                  printf("%-22s returned %u \tStatus: 0x%X\n", "LLC_DIR_OPEN_DIRECT", rtrn, *pStat);

                  if(*pStat==0)
                  {
                     //LLC_RECEIVE - Setup the receive to start listening for data on the adapter
                     ResetEvent(hEvent);
                     ZeroMemory(&CCB, sizeof(CCB));
                     ZeroMemory(&ReceiveParms, sizeof(ReceiveParms));
                     ReceiveParms.usStationId=STATION_ID;
                     ReceiveParms.uchOptions = LLC_CONTIGUOUS_DATA;
                     ReceiveParms.ulReceiveFlag = RECEIVE_DATA_FLAG;
                     ReceiveParms.uchRcvReadOption = LLC_RCV_READ_INDIVIDUAL_FRAMES;
                     ReceiveParms.pFirstBuffer = BufferCreateParms.hBufferPool;

                     CCB.uchAdapterNumber = ADAPTER_ID;
                     CCB.uchDlcCommand = LLC_RECEIVE;
                     CCB.ulCompletionFlag = RECEIVE_COMPLETE_FLAG;
                     CCB.u.pParameterTable = (PLLC_PARMS)&ReceiveParms;
                     CCB.hCompletionEvent = hEvent;
                     CCB.uchReserved2 = AppID;
                     rtrn = AcsLan(&CCB, &pBadCCB);
                     printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_RECEIVE", rtrn, *pStat);
                     if(*pStat==0xFF)
                     {
                        //LLC_TRANSMIT_DIR_FRAME - Broadcast the ARP Packet as a Direct Frame
                        FillArpPacket(&a, AdapterOpenParms.auchNodeAddress, argv[1], argv[2]);
                        ResetEvent(hEvent);
                        ZeroMemory(&CCB, sizeof(CCB));
                        CCB.uchDlcCommand = LLC_TRANSMIT_DIR_FRAME;
                        CCB.ulCompletionFlag = 0;
                        ZeroMemory(&headerBuff, sizeof(headerBuff));
                        pxmitBuff->cbBuffer=14;
                        CopyMemory(&pxmitBuff->auchData[0],&a,14);
                        ZeroMemory(&TransmitParms, sizeof(TransmitParms));
                        TransmitParms.pXmitQueue1=pxmitBuff;
                        TransmitParms.usStationId = STATION_ID;
                        TransmitParms.cbBuffer1 = sizeof(a)-14;
                        TransmitParms.cbBuffer2 = 0; 
                        TransmitParms.pBuffer1 = (LPBYTE)&a.hardType;
                        TransmitParms.pBuffer2 = NULL;
                        TransmitParms.uchXmitReadOption = LLC_COMPLETE_SINGLE_XMIT_FRAME;
                        CCB.u.pParameterTable = (PLLC_PARMS)&TransmitParms;
                        CCB.hCompletionEvent = hEvent;
                        CCB.uchReserved2 = AppID;
                        rtrn = AcsLan(&CCB, &pBadCCB);
                        if(WaitForSingleObject(hEvent, 5000) == WAIT_TIMEOUT)
                           printf("LLC_TRANSMIT_DIR_FRAME Timed out.\n");

                        printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_TRANSMIT_DIR_FRAME", rtrn, *pStat);
                        if(*pStat==0)
                        {
                           //LLC_READ - Check to see if we received any data until we read the data 
                           //           we want or tried to read 50 (an arbitrary value) times.
                           int d=50;
                           readStatus = 0;
                           while((readStatus == 0) && !Done)
                           {
                              printf("\n=====================\n");
                              //Post a Read
                              ResetEvent(hEvent);
                              ZeroMemory(&CCB, sizeof(CCB));
                              ZeroMemory(&ReadParms, sizeof(ReadParms));

                              ReadParms.usStationId=STATION_ID;
                              ReadParms.uchOptionIndicator = 0;
                              ReadParms.uchEventSet  = LLC_EVENT_RECEIVE_DATA;

                              CCB.uchDlcCommand = LLC_READ;
                              CCB.ulCompletionFlag = RECEIVE_COMPLETE_FLAG;
                              CCB.u.pParameterTable = (PLLC_PARMS)&ReadParms;
                              CCB.hCompletionEvent = hEvent;
                              CCB.uchReserved2 = AppID;
                              rtrn = AcsLan(&CCB, &pBadCCB);
                              if(WaitForSingleObject(hEvent, 5000) != WAIT_OBJECT_0)
                              {
                                 //if we timed out or another error occured
                                 //setup loop to end, by making readStatus not Zero
                                 printf("Read Timed out or another error occurred.\n");
                                 readStatus = *pStat;
                              }
                              else
                              {
                                 printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_READ", rtrn, *pStat);
                                 readStatus = *pStat;
                                 // Organize the results of the LLC_READ
                                 // Filter out all but RECEIVE_DATA events.
                                 if(ReadParms.uchEvent == LLC_EVENT_RECEIVE_DATA)
                                 {
                                    PLLC_BUFFER pFrame = ReadParms.Type.Event.pReceivedFrame;
                                    PARP_PACKET pArp = (PARP_PACKET) ((LPBYTE) pFrame + pFrame->Buffer.Header.offUserData);
                                    DWORD i;
                                    LPBYTE t = (LPBYTE) pFrame + pFrame->Buffer.Header.offUserData;

                                    if(verbose)
                                    {
                                       PrintNext(&t,14); //print out the entire frame 
                                       PrintNext(&t,8);  //in an easy to read format
                                       PrintNext(&t,6);
                                       PrintNext(&t,4);
                                       PrintNext(&t,6);
                                       PrintNext(&t,4);
                                       PrintNext(&t,8);
                                       i=(LPBYTE) pFrame + pFrame->Buffer.Header.offUserData - t;
                                       PrintNext(&t,(LPBYTE) pFrame + pFrame->Buffer.Header.offUserData - t);
                                    }
                                    //Compare the destination of the frame that was read
                                    //if it is the same as the MAC address we submitted in 
                                    //our transmit frame then this frame was directed to us
                                    if(memcmp(pArp->dest,AdapterOpenParms.auchNodeAddress,6) == 0)
                                    {
                                       struct in_addr x;
                                       x.s_addr = pArp->srcIP;

                                       printf("Got data!\nIP Address: %s\t Mac Address: ", inet_ntoa(x));
                                       for(i=0;i<5;i++)
                                          printf("%02X-",pArp->srcAddr[i]);
                                       printf("%02X\n\n",pArp->srcAddr[i]);
                                       Done = TRUE;

                                    }
                                    else
                                    {  //data was bound for another MAC address
                                       printf("Data bound for: ");
                                       for(i=0;i<5;i++)
                                          printf("%02X-",(BYTE)pArp->dest[i]);
                                       printf("%02X\n\n",(BYTE)pArp->dest[i]);
                                       if(d-- == 0)
                                          Done = TRUE;
                                    }

                                    //LLC_BUFFER_FREE - You must free every buffer that comes
                                    //in, even if it wasn't to your MAC Address, direct station,
                                    //or SAP
                                    ResetEvent(hEvent);
                                    ZeroMemory(&CCB, sizeof(CCB));
                                    ZeroMemory(&BufferFreeParms, sizeof(BufferFreeParms));
                                    BufferFreeParms.pFirstBuffer = (PLLC_XMIT_BUFFER)ReadParms.Type.Event.pReceivedFrame;

                                    CCB.uchDlcCommand = LLC_BUFFER_FREE;
                                    CCB.u.pParameterTable = (PLLC_PARMS)&BufferFreeParms;
                                    CCB.hCompletionEvent = hEvent;

                                    rtrn = AcsLan(&CCB, NULL);
                                    if(WaitForSingleObject(hEvent, 5000) == WAIT_TIMEOUT)
                                       printf("LLC_BUFFER_FREE Timed out.\n");
                                    printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_BUFFER_FREE", rtrn, *pStat);
                                    printf("Free Buffers: %u\n",BufferFreeParms.cBuffersLeft);
                                 }
                                 else
                                    //Show the type of event you received this should
                                    //never get called since we asked only to get 
                                    //LLC_EVENT_RECEIVE_DATA events when we did the LLC_READ
                                    printf("%d\n",ReadParms.uchEvent);
                              }
                           }
                        }
                     printf("\n=====================\n");
                     ZeroMemory(&CCB, sizeof(CCB));
                     ResetEvent(hEvent);
                     //LLC_RECEIVE_CANCEL
                     //Release the request to RECEIVE frames on this station
                     //This isn't really necessary in this APP since the app
                     //is going away. But normally you should do this anyway.
                     CCB.uchAdapterNumber = ADAPTER_ID;
                     CCB.uchDlcCommand = LLC_RECEIVE_CANCEL;
                     CCB.u.pParameterTable = (PLLC_PARMS)&ReceiveParms;
                     CCB.hCompletionEvent = hEvent;
                     CCB.uchReserved2 = AppID;
                     rtrn = AcsLan(&CCB, &pBadCCB);
                     printf("%-22s returned %u\tStatus: 0x%X\n", "LLC_RECEIVE_CANCEL", rtrn, *pStat);
                  }
                  // Close the Direct Station
                  ZeroMemory(&CCB, sizeof(CCB));
                  CCB.uchDlcCommand = LLC_DIR_CLOSE_DIRECT; 
                  CCB.uchReserved2 = AppID;
                  CCB.hCompletionEvent = hEvent;
                  ResetEvent(hEvent);
                  rtrn = AcsLan(&CCB, &pBadCCB);
                  WaitForSingleObject(hEvent, 5000);
                  printf("%-22s returned %u \tStatus: 0x%X\n", "LLC_DIR_CLOSE_DIRECT", rtrn, *pStat);
                 }
               }
            }
         }
         // Close the Adapter
         ZeroMemory(&CCB, sizeof(CCB));
         CCB.uchDlcCommand = LLC_DIR_CLOSE_ADAPTER;
         CCB.uchReserved2 = AppID;
         CCB.u.pParameterTable = (PLLC_PARMS)&OpenParms;
         OpenParms.pAdapterParms = &AdapterOpenParms;
         OpenParms.pExtendedParms = &ExtendedAdapterParms;
         OpenParms.pDlcParms = &DlcParms;
         CCB.hCompletionEvent = hEvent;
         ResetEvent(hEvent);
         rtrn = AcsLan(&CCB, &pBadCCB);
         WaitForSingleObject(hEvent, 5000);
         printf("%-22s returned %u \tStatus: 0x%X\n", "LLC_DIR_CLOSE_ADAPTER", rtrn, *pStat);
      }
   }
   return;
}

void FillArpPacket(PARP_PACKET a, LPSTR srcAddr, LPSTR srcIPAddress, LPSTR ipAddr)
{
   //build an ARP packet

   // /-----------------------------------------------------------------------------------------------/
   // |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |
   // /-----------------------------------------------------------------------------------------------/
   // |        Destination Address        |           Source Address          |    Type   | Hard Type |
   // /-----------------------------------------------------------------------------------------------/
   // | Prot Type | HS* | PS* | Oper Code |      Sender Enternet Address      |     Sender IP Address |
   // /-----------------------------------------------------------------------------------------------/
   // |      Target Ethernet Address      |   Target IP Address   |  18 Bytes of Padding              |
   // /-----------------------------------------------------------------------------------------------/
   // |      Padding Continued                                                | 
   // /-----------------------------------------------------------------------/
   //
   // *HS = Hardware Address Size, PS = Protocol Address Size

   ZeroMemory(a,sizeof(ARP_PACKET));
   FillMemory(a->dest,6, 0xFF);
   a->type=htons(0x0806);        //Network byte order
   a->hardType=htons(0x0001);    //Network byte order
   a->protType=htons(0x0800);    //Network byte order
   a->hardSize=0x06;
   a->protSize=0x04;
   a->opCode=0x0100;
   CopyMemory(a->srcAddr, srcAddr, 6);
   a->srcIP = inet_addr(srcIPAddress);
   a->destIP = inet_addr(ipAddr);
}

unsigned char swap_bits(unsigned char b) 
{
   unsigned char bb = 0;
   unsigned char mask;

   for (mask = 1; mask; mask <<= 1) 
   {
      bb <<= 1;

      bb |= ((b & mask) ? 1 : 0);
   }
   return bb;
}

void twiddle_bits(LPBYTE buffer, DWORD length) 
{
   //This function is used to format bits from IBM Token ring (BigEndian)
   //format to Ethernet MAC address format (LittleEndian)

   while (length--) 
   {
      *buffer = swap_bits(*buffer);
      ++buffer;
   }
}

void PrintNext(LPBYTE *t, int c)
{
   //This function prints c bytes of memory on one line
   //with spaces between each byte... like this:
   //00 A0 C9 C9 F6 11 00 10 54 42 C0 80 00 00
   int i;
   for(i=0;i<c;i++)
   {
      printf("%02X ",**t);
      (*t)++;
   }
   printf("\n");
}
