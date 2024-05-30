// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1999  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      enumerator.cpp
//
// Abstract:
//
// Entry Points:
//      Enumerator - enumerate ATM interfaces on the local machine.
//
// Author:
//      Barry R. Butterklee


#include "atmevent.h"


// Abstract:
//      Determine the number of ATM adapters on the machine and then print out
//      a list of each adaptors NSAP address.
//
//
void Enumerator(
    OPTIONS          *pOptions
    )
    {
    SOCKET          sd;
    SOCKADDR_ATM    atm_addr;
    CHAR            szAddress[MAX_ATM_INTERFACE_LEN];
    DWORD           dwNumInterfaces;
    DWORD           dwAddrLen;
    DWORD           dwBytes=sizeof(DWORD);
    int             nRet;


    sd = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, 
        &pOptions->protocolInfo, 0, WSA_FLAG_OVERLAPPED);
    if (INVALID_SOCKET == sd)
        {
        printf("WSASocket: %d\n", WSAGetLastError());
        return;
        }

    nRet = WSAIoctl(sd, SIO_GET_NUMBER_OF_ATM_DEVICES, 
        NULL, 0,
        (LPVOID)&dwNumInterfaces, sizeof(dwNumInterfaces), &dwBytes, 
        NULL, NULL);
    if (SOCKET_ERROR == nRet)
        {
        printf("WSAIoctl:SIO_GET_NUMBER_OF_ATM_DEVICES: %d\n", WSAGetLastError());
        return;
        }

    for(int i=0; i < (int)dwNumInterfaces ;i++)
        {
        ZeroMemory((PVOID)&atm_addr, sizeof(SOCKADDR_ATM));

        nRet = WSAIoctl(sd, SIO_GET_ATM_ADDRESS, 
            (LPVOID)&i, sizeof(DWORD),
            (LPVOID)&atm_addr.satm_number, sizeof(atm_addr.satm_number), &dwBytes, 
            NULL, NULL);
        if (SOCKET_ERROR == nRet)
            {
            printf("WSAIoctl:SIO_GET_ATM_ADDRESS: %d\n", WSAGetLastError());
            return;
            }
        
        // fill in remainder of ATM address structure
        atm_addr.satm_family                 = AF_ATM;
        atm_addr.satm_number.AddressType     = ATM_NSAP;
        atm_addr.satm_number.NumofDigits     = ATM_ADDR_SIZE;
        atm_addr.satm_blli.Layer2Protocol    = SAP_FIELD_ANY;
        atm_addr.satm_blli.Layer3Protocol    = SAP_FIELD_ABSENT;
        atm_addr.satm_bhli.HighLayerInfoType = SAP_FIELD_ABSENT;

        ZeroMemory((PVOID)szAddress, sizeof(szAddress));        
        dwAddrLen = sizeof(szAddress);
        if (WSAAddressToString((LPSOCKADDR)&atm_addr, sizeof(atm_addr), 
            &pOptions->protocolInfo, szAddress, &dwAddrLen))
            {
            printf("WSAAddressToString: %d\n", WSAGetLastError());
            break;
            }             
        printf("ATM Interface [%d]: <%s>\n", i, szAddress);
        }

    closesocket(sd);
    return;
    }
