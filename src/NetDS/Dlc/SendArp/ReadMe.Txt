DLC

/*++

Copyright (c) 1998  Microsoft Corporation

Module Name:

   SendArp.c

Author:

    Gary Yukish (garyy)    15-July-98

Summary:

   This module illustrates how to use the Windows NT DLC API to post
   and receive an ARP query to a Direct Station on an Ethernet adapter.
   The code retrieves the MAC address given a specific IP address.

   Limitations in the Win95 & Win98 DLC stacks prevent Direct Stations
   from being used in this manner.  This application will not function
   correctly on those platforms.

   The point of this sample is to demonstrate that any type of Ethernet
   frame could be sent through a Direct Station and how you would prepare
   the LLC Buffers to performs such and operation.

   The format for the Ethernet Frame and ARP Packet were taken from 
   "TCP/IP Illustrated,	Volume 1 The Protocols" by W. Richard Stevens.
   Pages 21-23 and 56-57.


More Information:

   Call the program by providing a local IP Address and the remote IP 
   Address you want to query.

      Syntax: SendRaw LocalIPAddress RemoteIPAddress
      Sample: SendRaw 157.24.176.111 157.24.176.1

      /v displays frames as they are received.

   The results will be some information about what DLC Api calls where successful
   and what the MAC address of the associated IP address you requested was.

--*/