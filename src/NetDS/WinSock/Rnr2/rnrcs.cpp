//----------------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      RnrCs.cpp
//
// Abstract:
//      In a traditional Winsock 1.1 client/server program, the server 
//      binds itself to a well known port of a particular protocol family. 
//      Then, any client can talk to the server only if it knows the server's 
//      addressing infomation which includes the server's address, protocol, 
//      and socket type.
//
//      The Winsock 2 Name Resolution and Registration (RnR) provides a unified
//      API set for client to search for registered services without having any
//      prior knowledge of addressing information. Basically, a server wants to 
//      register its existence within one or more name spaces through a friendly
//      service instance name and associate itself to a service class GUID.
//      Client application will be able to find the addressing 
//      information of a server by the friendly name and class GUID
//      in a name space.
//      
//      In this sample, the server program converts the user supplied Type Id 
//      into a service class GUID by SVCID_NETWARE() macro. (You can also 
//      generate your own service class GUID using uuidgen.exe or guidgen.exe 
//      and distribute this GUID to your client program.) It then checks the 
//      availability of various kind of name space providers and install this 
//      service class by filling out the relevant service class information 
//      with NS_NTDS (NT Directory Service name space provider available in Windows 2000) 
//      and/or NS_SAP (Service Advertising Protocol name space provider available 
//      both in Windows NT 4 and Windows 2000) name spaces whenever they are available.
//      If NS_NTDS has been installed, it binds itself to UDP protocol addresses
//      and a port number dynamically chosen by the system. If NS_SAP has been
//      installed, it also binds itself to a IPX protocol address and a socket
//      number chosen by the system. After filling out its bound socket addresses,
//      it advertises its availability through a service name supplied by a user.
//      For each bound non-blocking socket addresses, the server tries to
//      receive any datagram sent by any client and print out the client's socket
//      addressing information if a datagram is received.
//      When a user hits CTRL-C, the server program will unregister this 
//      service instance, remove the service class and close all sockets.
//
//      The client program converts the user supplied Type Id into a service
//      class GUID by SVCID_NETWARE() macro, such that it can find any SAP
//      predefined services (e.g. file server Type Id is 4) or the corresponding 
//      advertised server program. If the user supplies a service name, it 
//      will just look up the service with the same service name and Type Id. 
//      If the user supplies a wild card "*" for the service name, it will try 
//      to look up all registered services with the same
//      Type Id. For each service program found, it prints out the socket addressing
//      information of the service program and sends a message to it.  
//
//      NOTE: 
//      (1) To exploit the NS_NTDS name space (Active Directory):
//          (a) client and server machines should have Windows 2000 or later installed and both 
//              machines should be members of a Windows 2000 domain.
//          (b) If the server program is running in the security context of Domain Admins, 
//              you should have no problem in publishing the service. 
//          (c) If the server program is running in the context of a Domain Users, Domain
//              Admins have to modify the access control list (ACLs) on the WinsockServices 
//              container:
//              From the Active Directory Users and Computers MMC snap-in, access the View menu 
//              and select Advanced Features. Under the System container is another container 
//              listed as WinsockServices. Open the WinsockServices container, 
//              right-click Properties->Security, add your desired user/group with Full Control
//              permission. Make sure this applies onto "this object and all child objects"
//              by clicking the "Advanced..." button and "View/Edit..." your selected permission
//              entry. 
//      (2) To advertise in the SAP name space, server program machine should have
//          NWLink IPX/SPX Compatible Transport protocol and SAP Agent service installed.
//      (3) To lookup servers in the SAP name space, client program machine should have
//          NWLink IPX/SPX Compatible Transport protocol installed.
//      (4) When the server is running on a mutihomed machine, the SAP name space
//          provider will only make the first registered ipx address available, other
//          ipx addresses are ignored.
//
// Usage:  RnrCs
// -c (running this program as a client)
// -s (running this program as a server)
// -t server_type_id (default is: 200)
// -n server_instance_name (default is: MyServer)
// -p provider_name (default is: NS_ALL)
//                  (e.g. NS_NTDS, NS_SAP, NS_ALL)
// Examples:
// RnrCs -s -n MyServer   ....Run as server /w server_type_id of 200, service
//                             instance name of MyServer
// RnrCs -c -n * .............Run as client and find all servers /w server_type_id
//                             of 200 from all available name spaces
// RnrCs -c -n * -p NS_SAP ...Run as client and find all servers /w server_type_id
//                             of 200 from the SAP name space
// RnrCs -c -t 4 -n * ........Run as client and find all SAP file servers
// Hit Ctrl-C to quit the server program
//
// Build:
//  Use the headers and libs from the April98 Platform SDK or later.
//  Link with ws2_32.lib
//      
// Author: Frank K. Li - Microsoft Developer Support
//
//----------------------------------------------------------------------------
#include <winsock2.h>
#include <svcguid.h>
#include <wsipx.h>
#include <wsnwlink.h> 
#include <nspapi.h>

#include <stdio.h>
#include <stdlib.h>


void GetSockAddrString(SOCKADDR* pSAddr, char * dest);

//-------Server side structures and functions-------------------
// Global socket handles
const int g_nMaxNumOfCSAddr = 10; // advertise at most 10 addresses
const int g_nMaxNumOfSocks = 2;   // one for udp, another for ipx
int g_nNumOfUsedSocks = 0;        // number of socket created

SOCKET g_aSock[g_nMaxNumOfSocks] = {INVALID_SOCKET, INVALID_SOCKET};
CSADDR_INFO     g_aCSAddr[g_nMaxNumOfCSAddr];
SOCKADDR        g_aSockAddr[g_nMaxNumOfCSAddr]; // SOCKADDR buffer
GUID g_MyGuid;          // guid for this service class
WSAQUERYSET     g_QS;   // QuerySet to advertise service

SOCKADDR_IN     sa_in;  // socket address for AF_INET
SOCKADDR_IPX    sa_ipx; // socket address for AF_IPX

BOOL g_fSap   = FALSE;  // available name space providers on local machine
BOOL g_fNtds  = FALSE;
DWORD g_dwNumNs  = 0;   // total number of name space providers

BOOL fEndProgram = FALSE; // signal the end of program when user hits "Ctrl-C"

BOOL DoRnrServer(char * pszServerName, int  nServerType);
BOOL InstallClass(int nServerType);
BOOL Advertise(char* pszServerName);
BOOL ServerRecv();
BOOL CheckAvailableNameSpaceProviders(BOOL& fNsSap, BOOL& fNsNtds);
BOOL GetBoundIpxAddr(SOCKET soc, SOCKADDR_IPX * pSaIpx, int nAdapter);
BOOL WINAPI CtrlHandler (   DWORD dwEvent );


//-------Client side functions------------------------------
void DoRnrClient (int nServiceType, char * pszServerName, DWORD dwNameSpace);
void ClientSend(CSADDR_INFO* lpcsaBuffer);
void PrintError (char* errfunc);

#define OFFSET 1024  // a large buffer to hold returned WSAQUERYSET

//--------------------------------------------------------------
void Usage(char * pszProgramName)
{
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -c (running this program as a client)\n");
    fprintf(stderr, " -s (running this program as a server)\n");
    fprintf(stderr, " -t server_type_id (default is: 200)\n");
    fprintf(stderr, " -n server_instance_name (default is: MyServer) \n");
    fprintf(stderr, " -p provider name (default is: NS_ALL) \n");
    fprintf(stderr, "                  (e.g. NS_NTDS, NS_SAP, NS_ALL)\n");
    fprintf(stderr, "Examples:\n");
    fprintf(stderr, "RnrCs -s -n MyServer   ...Run as server /w server_type_id of 200, service\n");
    fprintf(stderr, "                             instance name of MyServer\n");
    fprintf(stderr, "RnrCs -c -n * ............Run as client and find all servers /w server_type_id\n");
    fprintf(stderr, "                             of 200 from all available name spaces\n");
    fprintf(stderr, "RnrCs -c -n * -p NS_SAP ..Run as client and find all servers /w server_type_id\n");
    fprintf(stderr, "                             of 200 from the SAP name space\n");
    fprintf(stderr, "RnrCs -c -t 4 -n * .......Run as client and find all SAP file servers\n");
    fprintf(stderr, "Hit Ctrl-C to quit the server program\n");
}

void main (int argc, char *argv[])
{
    char * pszServerName = "MyServer";   // default server instance name
    int    nServerType = 200;            // default server type id   
    char * pszNSProvider = "NS_ALL";
    DWORD  dwNameSpace = NS_ALL;
    int i;
    BOOL fServer = TRUE;                 // by default, running this program as the server
   
    // allow the user to override settings with command line switches
    for (i = 1; i < argc; i++) 
    {
        if ((*argv[i] == '-') || (*argv[i] == '/')) 
        {
            switch (tolower(*(argv[i]+1))) 
            {
            case 'n':  // server instance name
                pszServerName = argv[++i];
                break;
            case 't':  // server_type, this will be used as the base for the Server class id
                nServerType = atoi(argv[++i]);
                break;
            case 'c':
                fServer = FALSE;
                break;
            case 's':
                fServer = TRUE;
                break;
            case 'p':
                pszNSProvider = argv[++i];
                if (strnicmp("NS_NTDS", pszNSProvider, strlen("NS_NTDS")) == 0)
                    dwNameSpace = NS_NTDS;
                else if (strnicmp("NS_SAP", pszNSProvider, strlen("NS_SAP")) == 0)
                    dwNameSpace = NS_SAP;
                // default is NS_ALL
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
                return;
            }
        }
        else
        {
            Usage(argv[0]);
            return;
        }
    }

    if (fServer)
    {
        // check user input
        if (strcmp(pszServerName, "*") == 0)
        {
            printf("You can't supply wildcard (*) server instance name to run this server\n"); 
            Usage(argv[0]);
            return;
        }
    }

    __try
    {   
        // init winsock
        WSADATA wd;
        int nRet;
        if ( (nRet = WSAStartup (MAKEWORD (2, 2), &wd)) != 0)
        {
            printf ("Unable to start Winsock 2.  Error: %d\n", nRet);
            __leave;
        }

        if (fServer)
        {
            // running as a server program
            DoRnrServer(pszServerName, nServerType);
        }
        else
        {
            // running as a client program
            DoRnrClient(nServerType, pszServerName, dwNameSpace);
        }
    
    }
    __finally 
    {
        if (fServer)
        {
            SetConsoleCtrlHandler(CtrlHandler, FALSE);
        }

        WSACleanup();
    
    }
}


//---------------------------------------------
// server side routines
//---------------------------------------------


//---------------------------------------------------------------------------
//  FUNCTION: BOOL DoRnrServer(char * pszServerName, int  nServerType)
//
//  PURPOSE:  The driver for the server side code. It forms the global
//            class id "g_MyGuid" for this service class, installs this
//            service class, advertises the service name "pszServerName" with 
//            the associated bound SOCKADDR addresses and then loop through 
//            for data sent by client. This routine returns if user hits "Ctrl-C" 
//            or any error encountered.
//
//  RETURNS:
//    TRUE if user hits "Ctrl-C" to end the server program.
//    FALSE if there is any error encountered.
//
//---------------------------------------------------------------------------
BOOL DoRnrServer(char * pszServerName, int  nServerType)
{
    // I am using SVCID_NETWARE macro to form a common class id for the
    // client and server program such that the client program can also query 
    // some known SAP services on the network without running this program
    // as a server.
    // You can also generate your own class id by uuidgen.exe or guidgen.exe and
    // distribute the class id to client program.
    //
    // Please check svcguid.h for details about the macro.
    GUID guidNW = SVCID_NETWARE(nServerType); 

    memcpy(&g_MyGuid, &guidNW, sizeof(GUID));

    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE)) 
    {
        printf ("SetConsoleCtrlHandler failed to install console handler: %d\n", 
        GetLastError());
        return FALSE;
    }
    // Install the server class
    if (!InstallClass(nServerType))
    {
        return FALSE;
    }   
    // advertise the server instance
    if (!Advertise(pszServerName))
    {
        return FALSE;
    }
    
    // Make our bound sockets non-blocking such that
    // we can loop and test for data sent by client
    // without blocking.
    u_long arg = 1L;
    for (int i = 0; i < g_nNumOfUsedSocks; i++)
    {
        // make the socket as non-blocking socket
        if (ioctlsocket(g_aSock[i], FIONBIO, &arg) == SOCKET_ERROR)
        {
            printf("ioctlsocket[%d] error %d\n", i, WSAGetLastError());
            return FALSE;
        }
    }

    // receive data from client who find our address thru Winsock 2 RnR
    while (1)
    {
        if (ServerRecv() == FALSE)
        {
            return FALSE;
        }
        if (fEndProgram)
            return TRUE;
        Sleep(100);
    }
}

//---------------------------------------------------------------------------
//  FUNCTION: InstallClass(int nServerType)
//
//  PURPOSE:  Install a service class in NTDS and SAP name spaces if they are
//            available on this machine. "nServerType" is a numerical number used 
//            to generate a service class id by using SVCID_NETWARE macro as shown in 
//            the main program.
//            The name of this service class is obtained by composing "nServerType" 
//            with the string "TypeId.
//
//  RETURNS:
//    TRUE if succeed otherwise FALSE
//
//---------------------------------------------------------------------------
BOOL InstallClass(int nServerType)
{   
    WSASERVICECLASSINFO sci;
    WSANSCLASSINFO  aNameSpaceClassInfo[4];
    DWORD           dwSapId = nServerType;
    DWORD           dwZero = 0;
    TCHAR           szServiceClassName[256];
    int             nRet;
    DWORD           dwUdpPort = 0; // we use dynamic generated port number

    wsprintf(szServiceClassName, "TypeId %d", nServerType);
    printf("Installing ServiceClassName: %s\n", szServiceClassName);
    

    BOOL fSap  = FALSE;
    BOOL fNtds = FALSE;

    // see what name space providers are available
    if (!CheckAvailableNameSpaceProviders(fSap, fNtds))
        return FALSE;

    // save a copy
    g_fSap = fSap;
    g_fNtds = fNtds;

    // our total number of interested name space providers
    if (fSap)
        g_dwNumNs++;
    if (fNtds)
        g_dwNumNs++;
    
    // setup Service Class info
    memset(&sci, 0, sizeof(sci));
    
    sci.lpServiceClassId = (LPGUID) &g_MyGuid;
    sci.lpszServiceClassName = (LPSTR) szServiceClassName;
    sci.dwCount = g_dwNumNs * 2; // each name space has 2 NameSpaceClassInfo
    sci.lpClassInfos = aNameSpaceClassInfo;

    memset(aNameSpaceClassInfo, 0, sizeof(WSANSCLASSINFO)*4);

    

    DWORD i =0; // index to array of WSANSCLASSINFO

    // common service class registration in NTDS and SAP name spaces
    if (fNtds)
    {
        // NTDS setup
        printf("NTDS name space class installation\n");

        aNameSpaceClassInfo[i].lpszName = SERVICE_TYPE_VALUE_CONN;
        aNameSpaceClassInfo[i].dwNameSpace = NS_NTDS;
        aNameSpaceClassInfo[i].dwValueType = REG_DWORD;
        aNameSpaceClassInfo[i].dwValueSize = sizeof(DWORD);
        aNameSpaceClassInfo[i].lpValue = &dwZero;
        i++; // increment of the index
        
        aNameSpaceClassInfo[i].lpszName = SERVICE_TYPE_VALUE_UDPPORT;
        aNameSpaceClassInfo[i].dwNameSpace = NS_NTDS;
        aNameSpaceClassInfo[i].dwValueType = REG_DWORD;
        aNameSpaceClassInfo[i].dwValueSize = sizeof(DWORD);
        aNameSpaceClassInfo[i].lpValue = &dwUdpPort;
        i++; // increment of the index
    }

    if (fSap)
    {
        // SAP setup 
        printf("SAP name space class installation\n");

        aNameSpaceClassInfo[i].lpszName = SERVICE_TYPE_VALUE_CONN;
        aNameSpaceClassInfo[i].dwNameSpace = NS_SAP;
        aNameSpaceClassInfo[i].dwValueType = REG_DWORD;
        aNameSpaceClassInfo[i].dwValueSize = sizeof(DWORD);
        aNameSpaceClassInfo[i].lpValue = &dwZero;
        i++; // increment of the index

        aNameSpaceClassInfo[i].lpszName = SERVICE_TYPE_VALUE_SAPID;
        aNameSpaceClassInfo[i].dwNameSpace = NS_SAP;
        aNameSpaceClassInfo[i].dwValueType = REG_DWORD;
        aNameSpaceClassInfo[i].dwValueSize = sizeof(DWORD);
        aNameSpaceClassInfo[i].lpValue = &dwSapId;
    }       
    

    // Install the service class information
    nRet = WSAInstallServiceClass(&sci);
    if (nRet == SOCKET_ERROR)
    {
        printf("WSAInstallServiceClass error %d\n", WSAGetLastError());
        return FALSE;
    }
    return TRUE;
}

//---------------------------------------------------------------------------
//  FUNCTION: Advertise(char* pszServerName)
//
//  PURPOSE:  Given the name of this service instance "pszServerName",
//            advertise this instance to the available name spaces.
//
//  RETURNS:
//    TRUE if succeed otherwise FALSE
//
//---------------------------------------------------------------------------
BOOL Advertise(char* pszServerName)
{   
    
    int nRet;
    int i=0;              // number of socket created           
    int nNumOfCSAddr = 0; // number of bound socket addresses 
    
    // Advertizing
    
    // Set up the WSAQuery data
    memset(&g_QS, 0, sizeof(WSAQUERYSET));
    g_QS.dwSize = sizeof(WSAQUERYSET);
    g_QS.lpszServiceInstanceName = (LPSTR)pszServerName; // service instance name
    g_QS.lpServiceClassId = &g_MyGuid; // associated service class id
    g_QS.dwNameSpace = NS_ALL;         // advertise to all name spaces
    g_QS.lpNSProviderId = NULL;
    g_QS.lpcsaBuffer = g_aCSAddr;      // our bound socket addresses
    g_QS.lpBlob = NULL;


    // Set up the g_aCSAddr data
    if (g_fNtds)
    {
        char szName[256];              // local host name
        struct hostent *pHE = NULL;
        unsigned long ulSize = sizeof(szName);
        
        GetComputerName(szName, &ulSize);
        printf("HostName: %s\n", szName);
        pHE = gethostbyname(szName);
        if (pHE == NULL)
            return FALSE;
        
        // bind to local host ip addresses and let system to assign a port number
        memset(&sa_in, 0, sizeof(sa_in));
        sa_in.sin_family = AF_INET;
        sa_in.sin_addr.s_addr =  htonl(INADDR_ANY);
        sa_in.sin_port = 0;

        g_aSock[i] = socket ( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
        if ( INVALID_SOCKET == g_aSock[i] )
        {
            printf("socket error %d\n", WSAGetLastError());
            return FALSE;
        }

        nRet = bind ( g_aSock[i], (SOCKADDR *) &sa_in, sizeof (sa_in) );
        if ( SOCKET_ERROR == nRet )
        {
            printf("bind error %d\n", WSAGetLastError());
            return FALSE;
        }
        int cb = sizeof(sa_in);
        if (getsockname(g_aSock[i], (SOCKADDR *) &sa_in, &cb) == SOCKET_ERROR)
        {
            printf("getsockname error %d\n", WSAGetLastError());
            return FALSE;
        }
        
        int nIpIdx = 0; // total number of Ip Addresses for this host
        for (nIpIdx = 0; ; nIpIdx++)
        {
            if (pHE->h_addr_list[nIpIdx] == NULL)
                break;
        }
        
        printf("IP addresses bound...\n");
        
        SOCKADDR_IN* pSaIn;
        for (int j = 0; j < nIpIdx; j++)
        {
            if (j >= g_nMaxNumOfCSAddr)
            {
                printf("Max. number of socket address (%d) reached. We will not advertise extra ones\n", g_nMaxNumOfCSAddr);
                break;
            }
            pSaIn = (SOCKADDR_IN *) &g_aSockAddr[j];
            memcpy(pSaIn, &sa_in, sizeof(sa_in));
        
            pSaIn->sin_addr.s_addr =  *((long *) (pHE->h_addr_list[j]));
            pSaIn->sin_port = sa_in.sin_port;

            char temp[30];
            GetSockAddrString ((SOCKADDR *) &g_aSockAddr[j], temp);
            printf("%40s\n", temp);

            g_aCSAddr[j].iSocketType = SOCK_DGRAM;
            g_aCSAddr[j].iProtocol = IPPROTO_UDP;
            g_aCSAddr[j].LocalAddr.lpSockaddr = (struct sockaddr *)&g_aSockAddr[j]; 
            g_aCSAddr[j].LocalAddr.iSockaddrLength = sizeof(sa_in);
            g_aCSAddr[j].RemoteAddr.lpSockaddr = (struct sockaddr *)&g_aSockAddr[j];
            g_aCSAddr[j].RemoteAddr.iSockaddrLength = sizeof(sa_in);
            
            nNumOfCSAddr++; // increase the number SOCKADDR buffer used
        }
        i++; // increase the number of socket created
    }
    
    if (g_fSap && (nNumOfCSAddr < g_nMaxNumOfCSAddr))
    {
        // advertise into the NS_SAP name space if we still have enough
        // socket address buffer
        memset(sa_ipx.sa_netnum, 0, sizeof(sa_ipx.sa_netnum));
        memset(sa_ipx.sa_nodenum, 0, sizeof(sa_ipx.sa_nodenum));
        sa_ipx.sa_family = AF_IPX;
        sa_ipx.sa_socket = 0;

        g_aSock[i] = socket ( AF_IPX, SOCK_DGRAM, NSPROTO_IPX );
        if ( INVALID_SOCKET == g_aSock[i] )
        {
            printf("socket error %d\n", WSAGetLastError());
            return FALSE;
        }

        nRet = bind ( g_aSock[i], (SOCKADDR *) &sa_ipx, sizeof (sa_ipx) );
        if ( SOCKET_ERROR == nRet )
        {
            printf("bind error %d\n", WSAGetLastError());
            return FALSE;
        }
        
        //--------------Find out our bound ipx addresses------------
        int cb;        // size variable
        int nAdapters; // number of adapters bound with IPX

        // get the number of adapters
        cb = sizeof(nAdapters);
        nRet = getsockopt(g_aSock[i], NSPROTO_IPX, IPX_MAX_ADAPTER_NUM, (char *) &nAdapters, &cb);
        if (nRet == SOCKET_ERROR)
        {
            printf("getsockopt error %d\n", WSAGetLastError());
            return FALSE;
        }

        
        SOCKADDR_IPX* pSaIpx;           // a pointer to our current SOCKADDR buffer
        printf("IPX addresses bound...\n");

        for (int nIdx = 0; nIdx < nAdapters; nIdx++)
        {
            if (nNumOfCSAddr >= g_nMaxNumOfCSAddr)
            {
                printf("Max. number of socket address (%d) reached. We will not advertise extra ones\n", g_nMaxNumOfCSAddr);
                break;
            }
            // get the buffer for this SOCKADDR
            pSaIpx = (SOCKADDR_IPX *) &g_aSockAddr[nNumOfCSAddr];
        
            if (GetBoundIpxAddr(g_aSock[i],  pSaIpx, nIdx) == FALSE)
            {   
                printf("No valid bound IPX address at adapter index %d\n", nIdx);
                // since this link is not available, nNumOfCSAddr will reuse the current SOCKADDR buffer
                continue;
            }
        
            char temp[30];
            GetSockAddrString ((SOCKADDR *) &g_aSockAddr[nNumOfCSAddr], temp);
            printf("%40s\n", temp);

            g_aCSAddr[nNumOfCSAddr].iSocketType = SOCK_DGRAM;
            g_aCSAddr[nNumOfCSAddr].iProtocol = NSPROTO_IPX;
            g_aCSAddr[nNumOfCSAddr].LocalAddr.lpSockaddr = (struct sockaddr *)&g_aSockAddr[nNumOfCSAddr]; 
            g_aCSAddr[nNumOfCSAddr].LocalAddr.iSockaddrLength = sizeof(sa_ipx);
            g_aCSAddr[nNumOfCSAddr].RemoteAddr.lpSockaddr = (struct sockaddr *)&g_aSockAddr[nNumOfCSAddr];
            g_aCSAddr[nNumOfCSAddr].RemoteAddr.iSockaddrLength = sizeof(sa_ipx);
            
            nNumOfCSAddr++;
        }
        i++; // increase the number of socket created
        
        // Note: If g_fNtds is TRUE, this ipx address will be
        //       available from the NTDS name space too.

    }

    // update counters
    g_QS.dwNumberOfCsAddrs = nNumOfCSAddr;
    g_nNumOfUsedSocks = i;
    
    // Call WSASetService
    printf("Advertise server of instance name: %s ...\n", pszServerName);
    nRet = WSASetService(&g_QS, RNRSERVICE_REGISTER, 0L);
    if (nRet == SOCKET_ERROR)
    {
        printf("WSASetService error %d\n", WSAGetLastError());
        return FALSE;
    }
    printf("Wait for client talking to me, hit Ctrl-C to terminate...\n");
    return TRUE;

}

//---------------------------------------------------------------------------
//  FUNCTION: GetBoundIpxAddr(SOCKET soc, SOCKADDR_IPX * pSaIpx, int nAdapter)
//
//  PURPOSE:  Given a bound socket "soc", fill up "pSaIpx" with a valid
//            ipx address corresponding to the 0-based adapter index "nAdapter".
//
//  RETURNS:
//    TRUE if succeed otherwise FALSE
//
//---------------------------------------------------------------------------
BOOL GetBoundIpxAddr(SOCKET soc, SOCKADDR_IPX * pSaIpx, int nAdapter)
{
    IPX_ADDRESS_DATA ipx_data; // see wsnwlink.h for details
    int cb; // size variable
    int nRet;


    cb = sizeof ( IPX_ADDRESS_DATA );
    memset ( &ipx_data, 0, cb );
    ipx_data.adapternum = nAdapter;
            
    nRet = getsockopt ( soc, NSPROTO_IPX, IPX_ADDRESS, (char *) &ipx_data, &cb );
    if ( SOCKET_ERROR == nRet)
    {
        printf("getsockopt error %d\n", WSAGetLastError());
        return FALSE;
    }
        
    cb = sizeof(SOCKADDR_IPX);
    if (getsockname(soc, (SOCKADDR *) pSaIpx, &cb) == SOCKET_ERROR)
    {
        printf("getsockname error %d\n", WSAGetLastError());
        return FALSE;
    }
    else
    {
        if (ipx_data.status == TRUE)
        {
            // this link is UP
            memcpy(pSaIpx->sa_netnum, ipx_data.netnum, sizeof(pSaIpx->sa_netnum));
            memcpy(pSaIpx->sa_nodenum, ipx_data.nodenum, sizeof(pSaIpx->sa_nodenum));
            return TRUE;
        }
        else
            return FALSE; // this link is DOWN
    }
}

//---------------------------------------------------------------------------
//  FUNCTION: CheckAvailableNameSpaceProviders(BOOL& fNsSap, BOOL& fNsNtds)
//
//  PURPOSE:  Check the avaliable name space providers, set fNsSap to TRUE if
//            SAP is available, and fNsNtds to TRUE if NT Directory Service 
//            is avaialble.
//
//  RETURNS:
//    TRUE if succeed otherwise FALSE
//
//  NOTE: In this sample, we are only interested to know if NS_NTDS or NS_SAP
//        name space provoder is available.
//---------------------------------------------------------------------------
BOOL CheckAvailableNameSpaceProviders(BOOL& fNsSap, BOOL& fNsNtds)
{
    LPWSANAMESPACE_INFO pInfo;
    DWORD dwBufLen;
    PBYTE pBuf;
    int nCount;
    int nRet;

    dwBufLen = 0;

    fNsSap = fNsNtds = FALSE;

    nRet = WSAEnumNameSpaceProviders(&dwBufLen, NULL);
    if (nRet == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSAEFAULT)
        {
            printf("Error %d\n", WSAGetLastError());
            return FALSE;
        }
    }

    // dwBufLen contains the needed buffer size
    pBuf = (PBYTE) malloc(dwBufLen);
    if (pBuf == NULL)
    {
        printf("\nCould not allocate buffer\n");
        return FALSE;
    }

    nRet = WSAEnumNameSpaceProviders(&dwBufLen, (LPWSANAMESPACE_INFO)pBuf);
    if (nRet == SOCKET_ERROR)
    {
        printf("Error: %d\n", WSAGetLastError());
        free(pBuf);
        return FALSE;
    }

    //Loop thru the returned info
    pInfo = (LPWSANAMESPACE_INFO)pBuf;
    for (nCount = 0; nCount < nRet; nCount++)
    {
        switch (pInfo->dwNameSpace)
        {
        case NS_SAP:
            fNsSap = TRUE;
            break;
        case NS_NTDS:
            fNsNtds = TRUE;
            break;
        default:
            break;
        }
        pInfo++;
    }
    free(pBuf);
    return TRUE;

}

//---------------------------------------------------------------------------
//  FUNCTION: BOOL ServerRecv()
//
//  PURPOSE: For each bound socket in g_aSock[], try to do a non-blocking
//           receive and print out the peer's address information.
//
//  RETURNS:
//    TRUE if succeed otherwise FALSE
//---------------------------------------------------------------------------
BOOL ServerRecv()
{

    int nBytesReceived;
    char szBuf[1024];
    SOCKADDR sa_peer;
    int nPeerAddrLen; 

    for (int i = 0; i < g_nNumOfUsedSocks; i++)
    {
        nPeerAddrLen = sizeof(SOCKADDR);
        // You can use "nBytesReceived = recv(g_aSock[i], szBuf, sizeof(szBuf), 0 );", if
        // you don't want your peer's address information.
        nBytesReceived = recvfrom(g_aSock[i], szBuf, sizeof(szBuf), 0, &sa_peer, &nPeerAddrLen);
        
        if (nBytesReceived == SOCKET_ERROR)
        {
            int nRet = WSAGetLastError();
            if (nRet == WSAEWOULDBLOCK || nRet == WSAEMSGSIZE)
                continue;
            else
            {
                printf("recv error: %d\n", nRet);
                return FALSE;
                
            }
        }
        else
        {
            printf("received: [%s ", szBuf);

            char temp[30];
            GetSockAddrString (&sa_peer, temp);
            printf(": %s]\n", temp);
        }
    }
    return TRUE;
}

//---------------------------------------------------------------------------
//  FUNCTION: BOOL WINAPI CtrlHandler ( DWORD dwEvent )
//  Intercept CTRL-C or CTRL-BRK events and cause the server to 
//  initiate shutdown and cleanup.
//---------------------------------------------------------------------------
BOOL WINAPI CtrlHandler (   DWORD dwEvent )
{
    int nRet;
    int i=0;
    switch (dwEvent) 
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
        case CTRL_CLOSE_EVENT:
            fEndProgram = TRUE;
            printf("CtrlHandler: cleaning up...\n");

            printf("delete service instance...\n");
            nRet = WSASetService(&g_QS, RNRSERVICE_DELETE, 0L);
            if (nRet == SOCKET_ERROR)
            {
                printf("WSASetService DELETE error %d\n", WSAGetLastError());
            }
            
            printf("Removing Service class...\n");
            nRet = WSARemoveServiceClass(&g_MyGuid);
            if (nRet == SOCKET_ERROR)
            {
                printf("WSARemoveServiceClass error %d\n", WSAGetLastError());
            }
            
            for (i = 0; i < g_nMaxNumOfSocks; i++)
            {
                if ( g_aSock[i] != INVALID_SOCKET )
                    closesocket ( g_aSock[i] );
            }
            break;

        default:
            // unknown type--better pass it on.
            return(FALSE);
    }
    return(TRUE);
}


//-------------------------------------
// Client side routines
//-------------------------------------

//---------------------------------------------------------------------------
//  FUNCTION: void DoRnrClient (int nServiceType, char * pszServerName, DWORD dwNameSpace)
//
//  PURPOSE: Given the service type id "nServiceType", the server instance name
//           "pszServerName" and the name space to query "dwNameSpace", 
//           perform name resolution to the server and send a message to it.
//           If "nServiceType" is some known SAP Id such as Print Queue (3),
//           File Server (4), Job Server (5), Print Server (7), Archive
//           Server (9), Remote Bridge Server (36) or Advertising Print Server
//           (71), it will not send a message to the server.
//---------------------------------------------------------------------------
void DoRnrClient (int nServiceType, char * pszServerName, DWORD dwNameSpace)
{
    static GUID guid = SVCID_NETWARE ( nServiceType );  //use this as the class id
    WSAQUERYSET qs;
    AFPROTOCOLS afp[g_nMaxNumOfSocks] = {{AF_IPX,  NSPROTO_IPX}, {AF_INET, IPPROTO_UDP}};
    HANDLE hLookup;
    DWORD dwResult = 0;
    static char szName[100];
    BOOL fKnownSapId = FALSE;
    DWORD dwLength;
    BYTE abyBuf[sizeof(WSAQUERYSET) + OFFSET]; // provide a sufficient large 
                                               // buffer for returned query set
    WSAQUERYSET * pQS = (WSAQUERYSETA*) abyBuf;
    
    lstrcpy (szName, pszServerName);
    ZeroMemory (&qs, sizeof (qs));
    qs.dwSize = sizeof (WSAQUERYSET);
    qs.lpszServiceInstanceName = szName; 
    qs.lpServiceClassId = &guid;
    qs.dwNameSpace = dwNameSpace;
    qs.dwNumberOfProtocols = g_nMaxNumOfSocks; 
    qs.lpafpProtocols = afp; 

    ZeroMemory (abyBuf, sizeof (WSAQUERYSET) + OFFSET);
    dwLength = sizeof(WSAQUERYSET) + OFFSET;
    
    // some well known SAP name space services
    if (nServiceType == 3 || nServiceType == 4 || nServiceType == 5 ||
        nServiceType == 7 || nServiceType == 9 || nServiceType == 36 || nServiceType == 71)
        fKnownSapId = TRUE;

    if (WSALookupServiceBegin ( &qs,
                                LUP_RETURN_ADDR | LUP_RETURN_NAME,
                                &hLookup) == SOCKET_ERROR)
    {
        PrintError("WSALookupServiceBegin");
        return;
    }

    printf ("Performing Query for service (type, name) = (%d, %s) . . .\n\n", nServiceType, pszServerName);

    if (strcmp(pszServerName, "*") == 0)
    {   // enumerate all service instances
        while (TRUE)
        {
            dwResult = WSALookupServiceNext(hLookup,
                                            0,
                                            &dwLength,
                                            pQS);
            if (dwResult == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEFAULT)
                {
                    printf("WSALookupServiceNext Error: Oops, we need a larger buffer size of : %d Bytes\n", dwLength);
                }
                else
                {
                    PrintError("WSALookupServiceNext");
                }
                WSALookupServiceEnd (hLookup);
                return;
            }
            
            if (!dwResult)
            {
                for (DWORD i = 0; i < pQS->dwNumberOfCsAddrs; i++)
                {
                    SOCKADDR *mypt = (SOCKADDR *) pQS->lpcsaBuffer[i].RemoteAddr.lpSockaddr;
                    if (mypt)
                    {
                        // we have valid remote sockaddr
                        char temp[30];
                        printf ("Name[%d]: %30s", i, pQS->lpszServiceInstanceName);
                        GetSockAddrString (mypt, temp);
                        printf("%40s\n", temp);
    
                        if (! fKnownSapId)
                            ClientSend(&(pQS->lpcsaBuffer[i]));
                    }   
                }
            
            }
        }
    }
    else
    {
            dwResult = WSALookupServiceNext(hLookup,
                                            0,
                                            &dwLength,
                                            pQS);

            if (dwResult == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEFAULT)
                {
                    printf("WSALookupServiceNext Error: Oops, we need a larger buffer size of : %d Bytes\n", dwLength);
                }
                else
                {
                    PrintError("WSALookupServiceNext");
                }
                WSALookupServiceEnd (hLookup);
                return;
            }

            if (!dwResult)
            {
                for (DWORD i = 0; i < pQS->dwNumberOfCsAddrs; i++)
                {
                    SOCKADDR *mypt = (SOCKADDR *) pQS->lpcsaBuffer[i].RemoteAddr.lpSockaddr;
                    if (mypt)
                    {
                        // we have valid remote sockaddr
                        char temp[30];
                        printf ("Name[%d]: %30s", i, pQS->lpszServiceInstanceName);
                        GetSockAddrString (mypt, temp);
                        printf("%40s\n", temp);
    
                        if (! fKnownSapId)
                            ClientSend(&(pQS->lpcsaBuffer[i]));
                    }
                }       
            }
            WSALookupServiceEnd (hLookup);
    }   
}

//---------------------------------------------------------------------------
//  FUNCTION: void ClientSend(CSADDR_INFO* lpcsaBuffer)
//
//  PURPOSE: Given the server socket address info "lpcsaBuffer", 
//           send a message to the peer.
//---------------------------------------------------------------------------
void ClientSend(CSADDR_INFO* lpcsaBuffer)
{

    SOCKADDR *mypt = (SOCKADDR *) lpcsaBuffer->RemoteAddr.lpSockaddr;

    SOCKET s = INVALID_SOCKET;
    static char szMessage[256] = "A message from the client: ";
    static BOOL fHostname = FALSE;
    char szName[256];
    unsigned long ulSize = sizeof(szName);

    if (fHostname == FALSE)
    {
        GetComputerName(szName, &ulSize);
        strcat(szMessage, szName);
        fHostname = TRUE;
    }
    
    // The client doesn't need to know the detail of the addressing
    // information, it can just do the common sequence of
    // socket, connect, send/recv and closesocket by using the
    // discovered RemoteAddr.
    s = socket(lpcsaBuffer->RemoteAddr.lpSockaddr->sa_family, 
                                    lpcsaBuffer->iSocketType,
                                    lpcsaBuffer->iProtocol);

    if (s != INVALID_SOCKET)
    {
        if (connect(s, mypt, lpcsaBuffer->RemoteAddr.iSockaddrLength) != SOCKET_ERROR)
        {
            if (send(s, szMessage, strlen(szMessage)+1, 0) != SOCKET_ERROR )
            {
                printf("send a message to the peer...\n");
            }
            else
            {
                printf("send failed %d\n", WSAGetLastError());
            }
        }
        else
        {
            printf("connect failed %d\n", WSAGetLastError());
        }
                            
        closesocket(s);
    }
    else
        printf("Failed socket call %d\n", WSAGetLastError());
}

//---------------------------------------------------------------------------
// FUNCTION: void PrintError (char* errfunc)
// PURPOSE:  Print error message.
//---------------------------------------------------------------------------
void PrintError (char* errfunc)
{
    fflush (stdout);
    if (WSASERVICE_NOT_FOUND == WSAGetLastError())
        fprintf (stderr, "No matches found.\n");
    else
        if (WSA_E_NO_MORE == WSAGetLastError() || WSAENOMORE == WSAGetLastError())
           fprintf (stderr, "No more matches. \n");
    else
        fprintf (stderr, "Function %s failed with error %d\n", errfunc, WSAGetLastError());
}


//---------------------------------------------------------------------------
//  FUNCTION: void GetSockAddrString(SOCKADDR* pSAddr, char * dest)
//
//  PURPOSE:  Converts INET or IPX address in "pSAddr" into ascii string in "dest"
//
//
//  COMMENTS:
//
//    INET address in decimal dotted notation:
//       107.50.104.97:4790
//    IPX address format in hex:
//      <8 char network address>.<12 char node address>.<4 char sock address>
//
//  NOTE: Since Winsock 2 WSAAddressToString API is now only working for
//        IP (AF_INET) and ATM (AF_ATM) address family, I would rather implement
//        my version as GetSockAddrString()
//---------------------------------------------------------------------------
void GetSockAddrString(SOCKADDR* pSAddr, char * dest)
{
    if (pSAddr == NULL || dest == NULL)
        return;

    if (pSAddr->sa_family == AF_INET)
    {
        LPSTR pszDottedAddr = NULL;
        PSOCKADDR_IN pInAddr = (PSOCKADDR_IN) pSAddr;
        pszDottedAddr = inet_ntoa(pInAddr->sin_addr);
        if (pszDottedAddr == NULL)
        {
            lstrcpy(dest, "Error in inet_ntoa.");
        }
        else
        {
            char szBuf[15];
            lstrcpy(dest, pszDottedAddr);
            wsprintf(szBuf, ":%d", ntohs(pInAddr->sin_port));
            lstrcat(dest, szBuf);
        }
    }
    else if (pSAddr->sa_family == AF_IPX)
    { 
        PSOCKADDR_IPX pIpxAddr = (PSOCKADDR_IPX) pSAddr;
        wsprintf(dest, "%02X%02X%02X%02X.%02X%02X%02X%02X%02X%02X:%04X", 
            (unsigned char)pIpxAddr->sa_netnum[0],
            (unsigned char)pIpxAddr->sa_netnum[1],
            (unsigned char)pIpxAddr->sa_netnum[2],
            (unsigned char)pIpxAddr->sa_netnum[3],
            (unsigned char)pIpxAddr->sa_nodenum[0],
            (unsigned char)pIpxAddr->sa_nodenum[1],
            (unsigned char)pIpxAddr->sa_nodenum[2],
            (unsigned char)pIpxAddr->sa_nodenum[3],
            (unsigned char)pIpxAddr->sa_nodenum[4],
            (unsigned char)pIpxAddr->sa_nodenum[5],
            ntohs(pIpxAddr->sa_socket));

    }
    else
    {
        lstrcpy(dest, "Unknown socket address family.");
    }
   
}