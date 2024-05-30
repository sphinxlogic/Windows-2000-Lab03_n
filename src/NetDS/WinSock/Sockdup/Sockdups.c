// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1998  Microsoft Corporation.
// All Rights Reserved.
//
// Abstract:
//
//    The SOCKDUP sample demonstrates the basics of shared socket
//    programming in Winsock 2 using WSADuplicateSocket and WSASocket.
//    The parent and child processes use memory mapped files to exchange
//    the socket protocol information (WSAPROTOCOL_INFO) needed
//    to duplicate the socket in the child process.
//
//    The server application can function as either the parent
//    or a child.  The parent accepts each client connection request
//    and dispatches a child process to handle the actual I/O for
//    the connection.  After a child process is successfully created,
//    the parent is free to handle other client connection requests.
//
// Written By:    Mike Liu
//

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>

const int DEFAULT_PORT              = 8765;
const char FILE_MAPPING_BASE_NAME[] = "/MAPPED_FILE/WSADuplicateSocket";
const char PARENT[]                 = "parent";
const char CHILD[]                  = "child";
static int nChildProcCount          = 0;
SOCKET gsListen                     = INVALID_SOCKET;
SOCKET gsAccept                     = INVALID_SOCKET;
HANDLE ghParentFileMappingEvent     = NULL;
HANDLE ghChildFileMappingEvent      = NULL;
HANDLE ghMMFileMap                  = NULL;;

void Usage(char *szProgramName)
{
   fprintf(stderr, "Usage: %s [-e Endpoint] [-i IPAddress]\n\n", szProgramName);
   fprintf(stderr, "   Endpoint:  port to listen on (default %d)\n", DEFAULT_PORT);
   fprintf(stderr, "   IPAddress: IP address to bind to (default INADDR_ANY)\n");
   WSACleanup();
}

BOOL ConsoleCtrlHandler(DWORD dwEvent);
void DoCleanup(void);
void DoParent(char *pszIPAdress, unsigned short nPort, char *pszChildProcName);
void DoChild(char *pszChildFileMappingObj);
BOOL DispatchChild(SOCKET ClientSock, char *ChildProcName);
SOCKET GetSocket(char *szFileMappingObj);


int main(int argc, char **argv)
{
   char *pszIPAdress = NULL;
   char *pszChildFileMappingObj = NULL;
   unsigned short nPort = DEFAULT_PORT;
   WSADATA wsaData;
   BOOL bParent = TRUE;
   int nStatus;

   if (argc > 1)
   {
      int i;

      for(i = 1; i < argc; i++)
      {
         if ((argv[i][0] == '-') || (argv[i][0] == '/'))
         {
            switch(tolower(argv[i][1]))
            {
               case 'c':
                  bParent = FALSE;
                  pszChildFileMappingObj = argv[++i];
                  break;
               case 'i':
                  pszIPAdress = argv[++i];
                  break;
               case 'e':
                  nPort = atoi(argv[++i]);
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

   if (nPort == 0)
   {
      Usage(argv[0]);
      exit(1);
   }

   if ((nStatus = WSAStartup(0x202,&wsaData)) != 0)
   {
      fprintf(stderr, "\nWinsock 2 DLL initialization failed: %d\n", nStatus);
      WSACleanup();
      exit(-1);
   }
   
   if (bParent) // Run as parent
      DoParent(pszIPAdress, nPort, argv[0]);
   else    // Run as child
      DoChild(pszChildFileMappingObj);

   WSACleanup();

   return 0;
}


void DoParent(char *pszIPAdress, unsigned short nPort, char *pszChildProcName)
{
   int nFromLen;
   struct sockaddr_in saLocal, saFrom;
   DWORD dwProcID;

   // Install the CTRL+BREAK and CTRL+C Handler
   if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleCtrlHandler,
                             TRUE)
                            == FALSE) 
      printf("SetConsoleCtrlHandler failed: %d", GetLastError());
   
   dwProcID = GetCurrentProcessId();

   printf("Parent process %lu started ...\n", dwProcID);

   saLocal.sin_family = AF_INET;
   saLocal.sin_addr.s_addr = (pszIPAdress == NULL) ? INADDR_ANY: inet_addr(pszIPAdress);
   saLocal.sin_port = htons(nPort);

   gsListen = WSASocket(AF_INET,
                        SOCK_STREAM,
                        0,
                        (LPWSAPROTOCOL_INFO) NULL,
                        0,
                        WSA_FLAG_OVERLAPPED);

   if (gsListen == INVALID_SOCKET)
   {
      fprintf(stderr, "\nWSASocket() failed to obtain the listen socket: %d\n",
              WSAGetLastError());
      return;
   }

   // bind() associates a local address and port
   // combination with the socket just created. 
   if (bind(gsListen, (struct sockaddr*)&saLocal, sizeof(saLocal))
            == SOCKET_ERROR)
   {
      fprintf(stderr, "\nbind() failed: %d\n",
              WSAGetLastError());
      closesocket(gsListen);
      return;
   }

   // start listening on the socket for incoming connections
   if (listen(gsListen,5) == SOCKET_ERROR)
   {
      fprintf(stderr, "\nlisten() failed: %d\n",
              WSAGetLastError());
      closesocket(gsListen);
      return;
   }

   nFromLen = sizeof(saFrom);

   printf("Listening on port %d\n", nPort);

   while(TRUE)
   {
      printf("Waiting for new connection (Type CTRL+C to exit) ...\n\n");

      gsAccept = WSAAccept(gsListen,
                           (struct sockaddr*)&saFrom,
                           &nFromLen,
                           (LPCONDITIONPROC)NULL,
                           0);

      if(gsAccept == INVALID_SOCKET)
      {
         fprintf(stderr, "\nWSAAccept() failed: %d\n",
                 WSAGetLastError());
         break;
      }

      // Spawn a child process to handle the I/O.
      DispatchChild(gsAccept, pszChildProcName);

      // Doing a hard shutdown here is a no-no because it
      // will also reset the duplicated child socket.
      /*
      LINGER lingerStruct;

      lingerStruct.l_onoff = 1;
      lingerStruct.l_linger = 0;
      setsockopt(gsAccept, SOL_SOCKET, SO_LINGER,
                 (char *)&lingerStruct, sizeof(lingerStruct));
      */

      closesocket(gsAccept);
   }

   closesocket(gsListen);
}


void DoChild(char *pszChildFileMappingObj)
{
   SOCKET sockDuplicated;
   DWORD dwProcID;
   char szBuf[MAX_PATH];
   WSABUF wsaBuf;
   DWORD dwReceived = 0;
   DWORD dwFlags = 0;
   int nStatus;
   char cWait;

   dwProcID = GetCurrentProcessId();

   printf("Child process %lu started ...\n", dwProcID);

   if ((sockDuplicated = GetSocket(pszChildFileMappingObj))
         != INVALID_SOCKET)
   {
      while(TRUE)
      {
         szBuf[0] = '\0';
         wsaBuf.len = MAX_PATH;
         wsaBuf.buf = (char *)szBuf;

         // Note that we only receive small buffers of data.
         // We don't check the number of bytes for data integrity.
         // In a real application, the ckecking must be done.
         nStatus = WSARecv(sockDuplicated,
                           &wsaBuf,
                           1,
                           &dwReceived,
                           &dwFlags,
                           (LPWSAOVERLAPPED) NULL,
                           0);

         if (nStatus == 0) // success
         {
            if (dwReceived == 0) // Client closed connection
            {
               fprintf(stderr, "Client closed connection\n");
               break;
            }
            else
            {
               // Print whatever is received
               szBuf[dwReceived] = '\0';
               printf("%s", szBuf);
            }
         }
         else // SOCKET_ERROR
         {
            fprintf(stderr, "WSARecv() failed: %d\n", WSAGetLastError());
            break;
         }
      }

      closesocket(sockDuplicated);
   }
   else
      fprintf(stderr, "\nChild socket cannot be obtained: %d\n",
              WSAGetLastError());

   printf("\nChild process %lu has finished!!!\n", dwProcID);

   printf("Press any key to continue ...");
   cWait = getch();
}


// The server and client have to rely on
// certain interprocess communication schemes
// to exchange the WSAPROTOCOL_INFO needed for
// duplicating the socket.  In this sample,
// we use momory mapped files.
BOOL DispatchChild(SOCKET ClientSock, char *pszChildProcName)
{
   char szChildComandLineBuf[MAX_PATH];
   char szFileMappingObj[MAX_PATH];
   BOOL bResult = TRUE;
   STARTUPINFO siParent;
   PROCESS_INFORMATION piChild;
   char szParentEventName[MAX_PATH];
   char szChildEventName[MAX_PATH];

   ZeroMemory(&siParent, sizeof(siParent));
   siParent.cb = sizeof(siParent);
   siParent.dwFlags = STARTF_USECOUNTCHARS;
   siParent.dwXCountChars = 10 * MAX_PATH;
   siParent.dwYCountChars = MAX_PATH;

   // Compose a name for the memory mappled file.
   sprintf(szFileMappingObj,
           "%s%i",
           FILE_MAPPING_BASE_NAME,
           nChildProcCount++);

   sprintf(szParentEventName, "%s%s", szFileMappingObj, PARENT);
   sprintf(szChildEventName, "%s%s", szFileMappingObj, CHILD);

   // Create an event to signal the child
   // that the protocol info is set
   if ((ghParentFileMappingEvent = CreateEvent(NULL, TRUE, FALSE, szParentEventName)) == NULL)
   {
      fprintf(stderr, "\nCreateEvent() failed: %d\n", GetLastError());
      return FALSE;
   }

   // Create an event to for the child to signal the
   // parent that the protocol info can be released
   if ((ghChildFileMappingEvent = CreateEvent(NULL, TRUE, FALSE, szChildEventName)) == NULL)
   {
      fprintf(stderr, "\nCreateEvent() failed: %d\n", GetLastError());
      return FALSE;
   }

   // Set up the child process command line options.
   // The memory mapped file name is passed in as
   // one of the options.
   sprintf(szChildComandLineBuf,
           "%s /c %s",
           pszChildProcName,
           szFileMappingObj);

   if (CreateProcess(NULL,
                     szChildComandLineBuf,
                     NULL,
                     NULL,
                     TRUE,
                     CREATE_NEW_CONSOLE,
                     NULL,
                     NULL,
                     &siParent,
                     &piChild)) 
   {
      WSAPROTOCOL_INFO ProtocolInfo;
      int nError;
      int nWaitCount = 0;
      LPVOID lpView;
      int nStructLen = sizeof(WSAPROTOCOL_INFO);

      // Get the protocol information
      // to be used to duplicate the socket
      WSADuplicateSocket(ClientSock,
                         piChild.dwProcessId,
                         &ProtocolInfo);

      // Set the protocol information in a
      // memory mapped file for the child to use
      ghMMFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
                                      NULL,
                                      PAGE_READWRITE,
                                      0,
                                      nStructLen,
                                      szFileMappingObj);

      if (ghMMFileMap != NULL)
      {
         if ((nError = GetLastError()) == ERROR_ALREADY_EXISTS)
            fprintf(stderr, "CreateFileMapping(): mappping file already exists\n");
         else
         {
            lpView = MapViewOfFile(ghMMFileMap,
                                   FILE_MAP_READ | FILE_MAP_WRITE,
                                   0, 0, 0);

            if (lpView != NULL)
            {
               memcpy(lpView, &ProtocolInfo, nStructLen);
               UnmapViewOfFile(lpView);

               // Signal the child the protocol infomation is set
               SetEvent(ghParentFileMappingEvent);
               // Wait the child to signal that the protocol
               // infomation can be released now
               if (WaitForSingleObject(ghChildFileMappingEvent, 2000) == WAIT_FAILED)
               {
                  fprintf(stderr, "WaitForSingleObject() failed: %d\n", GetLastError());
                  DoCleanup();
                  exit(1);
               }
            }
            else
            {
               fprintf(stderr, "MapViewOfFile() failed: %d\n", GetLastError());
               bResult = FALSE;
            }
         }

         if (ghMMFileMap != NULL) 
         {
            CloseHandle(ghMMFileMap);
            ghMMFileMap = NULL;
         }
      }
      else
      {
         fprintf(stderr, "CreateFileMapping() failed: %d\n", GetLastError());
         bResult = FALSE;
      }

      CloseHandle(piChild.hThread);
      CloseHandle(piChild.hProcess);
   }
   else
   {
      printf("\nCreate child process failed!!!\n");
      bResult = FALSE;
   }

   if (ghParentFileMappingEvent != NULL) 
   {
      CloseHandle(ghParentFileMappingEvent);
      ghParentFileMappingEvent = NULL;
   }

   if (ghChildFileMappingEvent != NULL) 
   {
      CloseHandle(ghChildFileMappingEvent);
      ghChildFileMappingEvent = NULL;
   }

   return bResult;
}


// Once the protocol information is set by the
// parent in the memory mapped file, the child
// is ready to use it to duplicate the socket.
SOCKET GetSocket(char *szFileMappingObj)
{
   WSAPROTOCOL_INFO ProtocolInfo;
   SOCKET sockDuplicated = INVALID_SOCKET;
   char szParentEventName[MAX_PATH];
   char szChildEventName[MAX_PATH];

   sprintf(szParentEventName, "%s%s", szFileMappingObj, PARENT);
   sprintf(szChildEventName, "%s%s", szFileMappingObj, CHILD);

   // Open the events
   if ((ghParentFileMappingEvent = OpenEvent(SYNCHRONIZE, FALSE, szParentEventName)) == 0)
   {
      fprintf(stderr, "OpenEvent() failed: %d\n", GetLastError());
      return INVALID_SOCKET;
   }

   if ((ghChildFileMappingEvent = OpenEvent(SYNCHRONIZE, FALSE, szChildEventName)) == 0)
   {
      fprintf(stderr, "OpenEvent() failed: %d\n", GetLastError());
      return FALSE;
   }

   // Wait for the parent to signal that the protocol info
   // is ready to be accessed
   if (WaitForSingleObject(ghParentFileMappingEvent, 2000) == WAIT_FAILED)
   {
      fprintf(stderr, "WaitForSingleObject() failed: %d\n", GetLastError());
      DoCleanup();
      exit(1);
   }

   ghMMFileMap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                                 FALSE,
                                 szFileMappingObj);

   if (ghMMFileMap != NULL)
   {
      LPVOID lpView = MapViewOfFile(ghMMFileMap,
                                    FILE_MAP_READ | FILE_MAP_WRITE,
                                    0, 0, 0);

      if ((BYTE*) lpView != NULL)
      {
         int nStructLen = sizeof(WSAPROTOCOL_INFO);

         memcpy(&ProtocolInfo, lpView, nStructLen);
         UnmapViewOfFile(lpView);

         // Duplicate the socket based on the protocol
         // information stored in the memory mapped file.
         sockDuplicated = WSASocket(FROM_PROTOCOL_INFO,
                                    FROM_PROTOCOL_INFO,
                                    FROM_PROTOCOL_INFO,
                                    &ProtocolInfo,
                                    0,
                                    0);

         // Signal the parent the we are done
         // with the mapped file
         SetEvent(ghChildFileMappingEvent);
      }
      else
         fprintf(stderr, "MapViewOfFile() failed: %d\n", GetLastError());
   }
   else
      fprintf(stderr, "CreateFileMapping() failed: %d\n", GetLastError());

   if (ghParentFileMappingEvent != NULL) 
   {
      CloseHandle(ghParentFileMappingEvent);
      ghParentFileMappingEvent = NULL;
   }

   if (ghChildFileMappingEvent != NULL) 
   {
      CloseHandle(ghChildFileMappingEvent);
      ghChildFileMappingEvent = NULL;
   }

   if (ghMMFileMap != NULL) 
   {
      CloseHandle(ghMMFileMap);
      ghMMFileMap = NULL;
   }

   return sockDuplicated;
}


// Handle CTRL+BREAK or CTRL+C events
BOOL ConsoleCtrlHandler(DWORD dwEvent)
{
   DoCleanup();
   printf("Server terminated. Bye!\n");

   return FALSE;
}


void DoCleanup(void)
{
   // Do a best effort cleanup
   if (ghParentFileMappingEvent != NULL)
      CloseHandle(ghParentFileMappingEvent);
   if (ghChildFileMappingEvent != NULL)
      CloseHandle(ghChildFileMappingEvent);
   if (ghMMFileMap != NULL)
      CloseHandle(ghMMFileMap);
   if (gsListen != INVALID_SOCKET)
      closesocket(gsListen);
   if (gsAccept != INVALID_SOCKET)
      closesocket(gsAccept);

   WSACleanup();
}