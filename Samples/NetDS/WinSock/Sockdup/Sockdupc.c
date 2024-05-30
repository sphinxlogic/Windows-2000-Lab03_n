// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1998   Microsoft Corporation.
// All Rights Reserved.
//
// Written By:    Mike Liu
//

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int DEFAULT_PORT        = 8765;
const int DEFAULT_ITERATIONS  = 10;
const int LOOP_FOREVER        = -1;
SOCKET gsConnect;

BOOL ConsoleCtrlHandler(DWORD dwEvent);

void Usage(char *szProgramName)
{
   fprintf(stderr, "Usage: %s [-n Server] [-e Endpoint] [-l Iterations]\n\n", szProgramName);
   fprintf(stderr, "   Server:     server name or IP address (default localhost)\n");
   fprintf(stderr, "   Endpoint:   port to connect to (default %d)\n", DEFAULT_PORT);
   fprintf(stderr, "   Iterations: number of messages to send (default %d)\n", DEFAULT_ITERATIONS);

   WSACleanup();
}

int main(int argc, char **argv)
{
   char szBuf[MAX_PATH];
   char *pszServerName = "localhost";
   unsigned short nPort = DEFAULT_PORT;
   unsigned int nAddress;
   int i, nStatus, nLoopCount;
   int nIterations = DEFAULT_ITERATIONS;
   struct sockaddr_in saServer;
   struct hostent *sHostEnt;
   WSADATA wsaData;
   WSABUF wsaBuf;
   DWORD dwSent = 0;
   DWORD dwFlags = 0;

   if (argc > 1)
   {
      for(i = 1; i < argc; i++)
      {
         if ((argv[i][0] == '-') || (argv[i][0] == '/'))
         {
            switch(tolower(argv[i][1]))
            {
               case 'n':
                  pszServerName = argv[++i];
                  break;

               case 'e':
                  nPort = atoi(argv[++i]);
                  break;

               case 'l':
                  if (argv[i+1])
                  {
                     if (argv[i+1][0] != '-')  // "-l 6"
                     {
                        nIterations = atoi(argv[i+1]);
                        i++;
                     }
                     else if (isdigit(argv[i+1][1])) // "-l -6"
                     {
                        nIterations = 0;
                        i++;
                     }
                     else // "-l -e 2000"
                        nIterations = LOOP_FOREVER;
                  }
                  else // "-e 2000 -l"
                     nIterations = LOOP_FOREVER;
   
                  break;

               default:
                  Usage(argv[0]);
                  exit(1);
            }
         }
         else
         {
            Usage(argv[0]);
            exit(1);
         }
      }
   }

   if (nIterations == 0)
      return -1; // no messages to be sent

   if (nPort == 0)
   {
      Usage(argv[0]);
      exit(1);
   }

   // Install the CTRL+BREAK and CTRL+C Handler
   if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleCtrlHandler,
                             TRUE)
                            == FALSE) 
      printf("SetConsoleCtrlHandler failed: %d", GetLastError());
   
   if ((nStatus = WSAStartup(0x202,&wsaData)) != 0)
   {
      fprintf(stderr, "\nWinsock 2 DLL initialization failed: %d\n", nStatus);
      WSACleanup();
      exit(-1);
   }
   
   if (isalpha(pszServerName[0]))
   {
      sHostEnt = gethostbyname(pszServerName);
   }
   else
   {
      nAddress = inet_addr(pszServerName);
      sHostEnt = gethostbyaddr((char *)&nAddress, 4, AF_INET);
   }

   if (sHostEnt == NULL)
   {
      fprintf(stderr, "Cannot resolve address [%s]: %d\n",
              pszServerName, WSAGetLastError());
      WSACleanup();
      exit(1);
   }

   memset(&saServer, 0, sizeof(saServer));
   memcpy(&(saServer.sin_addr), sHostEnt->h_addr, sHostEnt->h_length);
   saServer.sin_family = sHostEnt->h_addrtype;
   saServer.sin_port = htons(nPort);

   gsConnect = WSASocket(AF_INET,
                         SOCK_STREAM,
                         0,
                         (LPWSAPROTOCOL_INFO) NULL,
                         0,
                         0);

   if (gsConnect == INVALID_SOCKET)
   {
      fprintf(stderr, "\nWSASocket() failed: %d\n",
              WSAGetLastError());
      WSACleanup();
      return -1;
   }

   printf("Connecting to: %s ...\n",sHostEnt->h_name);

   if (connect(gsConnect, (struct sockaddr*)&saServer, sizeof(saServer))
               == SOCKET_ERROR)
   {
      fprintf(stderr, "\nconnect() failed: %d\n",
              WSAGetLastError());
      WSACleanup();
      return -1;
   }

   nLoopCount = 0;

   while (TRUE)
   {
      szBuf[0] = '\0';
      wsprintf(szBuf, "Test message %d\n", nLoopCount++);
      wsaBuf.len = lstrlen(szBuf);
      wsaBuf.buf = (char *)szBuf;

      printf("Sending --> %s", szBuf);

      // Note that we only send small buffers of data.
      // The return value is not checked to ensure that
      // all data is actually sent. In a real application,
      // the ckecking must be done.
      nStatus = WSASend(gsConnect,
                        &wsaBuf,
                        1,
                        &dwSent,
                        dwFlags,
                        (LPWSAOVERLAPPED) NULL,
                        0);

      if (nStatus == SOCKET_ERROR)
      {
         fprintf(stderr, "WSASend() failed: %d\n", WSAGetLastError());
         break;
      }
      else if (dwSent == 0)
      {
         printf("Server closed connection\n");
         break;
      }

      if (((nIterations != LOOP_FOREVER)) && (nLoopCount >= nIterations))
         break;
   }

   closesocket(gsConnect);
   WSACleanup();
}


// Handle CTRL+BREAK or CTRL+C events
BOOL ConsoleCtrlHandler(DWORD dwEvent)
{
   // Do a best effort cleanup
   closesocket(gsConnect);
   WSACleanup();
   printf("Client terminated. Bye!\n");

   return FALSE;
}
   
