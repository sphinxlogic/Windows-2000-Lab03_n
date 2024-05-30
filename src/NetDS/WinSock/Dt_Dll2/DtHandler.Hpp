// Filename  : DTHandler.hpp
// Abstract  : This object implements a mechanism for hooking Winsock
//             API calls via the 'DT hooks' present in the checked-build
//             version of the ws2_32.dll. (See the Winsock DT sample on
//             on the Platform SDK for specifications.)  Through invoking
//             the DTHandler::dispatch() method, this object translates
//             the hook's code ordinal and calls the appropriate virtual
//             member function of the same Winsock API name, which you can
//             overload through inheritance, with the proper API parameters
//             expanded from DT's variable argument list call, making it
//             possible for you to easily trace your Winsock application
//             in a debug setting.
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998.  Microsoft Corporation.
//             All rights reserved.

#ifndef _DTHANDLER_H
#define _DTHANDLER_H

// Prevent inclusion of winsock.h in windows.h
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include <ws2spi.h>
#include "APIHook.hpp"

class DTHandler {
  bool _accept                                  (APIHook<void>, va_list);
  bool _bind                                    (APIHook<void>, va_list);
  bool _closesocket                             (APIHook<void>, va_list);
  bool _connect                                 (APIHook<void>, va_list);
  bool _getpeername                             (APIHook<void>, va_list);
  bool _getsockname                             (APIHook<void>, va_list);
  bool _getsockopt                              (APIHook<void>, va_list);
  bool _htonl                                   (APIHook<void>, va_list);
  bool _htons                                   (APIHook<void>, va_list);
  bool _ioctlsocket                             (APIHook<void>, va_list);
  bool _listen                                  (APIHook<void>, va_list);
  bool _ntohl                                   (APIHook<void>, va_list);
  bool _ntohs                                   (APIHook<void>, va_list);
  bool _recv                                    (APIHook<void>, va_list);
  bool _recvfrom                                (APIHook<void>, va_list);
  bool _select                                  (APIHook<void>, va_list);
  bool _send                                    (APIHook<void>, va_list);
  bool _sendto                                  (APIHook<void>, va_list);
  bool _setsockopt                              (APIHook<void>, va_list);
  bool _shutdown                                (APIHook<void>, va_list);
  bool _socket                                  (APIHook<void>, va_list);
  bool _WSAAccept                               (APIHook<void>, va_list);
  bool _WSAAsyncSelect                          (APIHook<void>, va_list);
  bool _WSACancelBlockingCall                   (APIHook<void>, va_list);
  bool _WSACleanup                              (APIHook<void>, va_list);
  bool _WSACloseEvent                           (APIHook<void>, va_list);
  bool _WSAConnect                              (APIHook<void>, va_list);
  bool _WSACreateEvent                          (APIHook<void>, va_list);
  bool _WSADuplicateSocketA                     (APIHook<void>, va_list);
  bool _WSADuplicateSocketW                     (APIHook<void>, va_list);
  bool _WSAEnumNetworkEvents                    (APIHook<void>, va_list);
  bool _WSAEnumProtocolsA                       (APIHook<void>, va_list);
  bool _WSAEnumProtocolsW                       (APIHook<void>, va_list);
  bool _WSAEventSelect                          (APIHook<void>, va_list);
  bool _WSAGetLastError                         (APIHook<void>, va_list);
  bool _WSAGetOverlappedResult                  (APIHook<void>, va_list);
  bool _WSAGetQOSByName                         (APIHook<void>, va_list);
  bool _WSAHtonl                                (APIHook<void>, va_list);
  bool _WSAHtons                                (APIHook<void>, va_list);
  bool _WSAIoctl                                (APIHook<void>, va_list);
  bool _WSAIsBlocking                           (APIHook<void>, va_list);
  bool _WSAJoinLeaf                             (APIHook<void>, va_list);
  bool _WSANtohl                                (APIHook<void>, va_list);
  bool _WSANtohs                                (APIHook<void>, va_list);
  bool _WSARecv                                 (APIHook<void>, va_list);
  bool _WSARecvDisconnect                       (APIHook<void>, va_list);
  bool _WSARecvFrom                             (APIHook<void>, va_list);
  bool _WSAResetEvent                           (APIHook<void>, va_list);
  bool _WSASend                                 (APIHook<void>, va_list);
  bool _WSASendDisconnect                       (APIHook<void>, va_list);
  bool _WSASendTo                               (APIHook<void>, va_list);
  bool _WSASetBlockingHook                      (APIHook<void>, va_list);
  bool _WSASetEvent                             (APIHook<void>, va_list);
  bool _WSASetLastError                         (APIHook<void>, va_list);
  bool _WSASocketA                              (APIHook<void>, va_list);
  bool _WSASocketW                              (APIHook<void>, va_list);
  bool _WSAStartup                              (APIHook<void>, va_list);
  bool _WSAUnhookBlockingHook                   (APIHook<void>, va_list);
  bool _WSAWaitForMultipleEvents                (APIHook<void>, va_list);
  bool _gethostbyaddr                           (APIHook<void>, va_list);
  bool _gethostbyname                           (APIHook<void>, va_list);
  bool _gethostname                             (APIHook<void>, va_list);
  bool _getprotobyname                          (APIHook<void>, va_list);
  bool _getprotobynumber                        (APIHook<void>, va_list);
  bool _getservbyname                           (APIHook<void>, va_list);
  bool _getservbyport                           (APIHook<void>, va_list);
  bool _inet_addr                               (APIHook<void>, va_list);
  bool _inet_ntoa                               (APIHook<void>, va_list);
  bool _WSAAsyncGetHostByAddr                   (APIHook<void>, va_list);
  bool _WSAAsyncGetHostByName                   (APIHook<void>, va_list);
  bool _WSAAsyncGetProtoByName                  (APIHook<void>, va_list);
  bool _WSAAsyncGetProtoByNumber                (APIHook<void>, va_list);
  bool _WSAAsyncGetServByName                   (APIHook<void>, va_list);
  bool _WSAAsyncGetServByPort                   (APIHook<void>, va_list);
  bool _WSACancelAsyncRequest                   (APIHook<void>, va_list);
  bool _WSPAccept                               (APIHook<void>, va_list);
  bool _WSPAsyncSelect                          (APIHook<void>, va_list);
  bool _WSPBind                                 (APIHook<void>, va_list);
  bool _WSPCancelBlockingCall                   (APIHook<void>, va_list);
  bool _WSPCleanup                              (APIHook<void>, va_list);
  bool _WSPCloseSocket                          (APIHook<void>, va_list);
  bool _WSPConnect                              (APIHook<void>, va_list);
  bool _WSPDuplicateSocket                      (APIHook<void>, va_list);
  bool _WSPEnumNetworkEvents                    (APIHook<void>, va_list);
  bool _WSPEventSelect                          (APIHook<void>, va_list);
  bool _WSPGetOverlappedResult                  (APIHook<void>, va_list);
  bool _WSPGetPeerName                          (APIHook<void>, va_list);
  bool _WSPGetSockName                          (APIHook<void>, va_list);
  bool _WSPGetSockOpt                           (APIHook<void>, va_list);
  bool _WSPGetQOSByName                         (APIHook<void>, va_list);
  bool _WSPIoctl                                (APIHook<void>, va_list);
  bool _WSPJoinLeaf                             (APIHook<void>, va_list);
  bool _WSPListen                               (APIHook<void>, va_list);
  bool _WSPRecv                                 (APIHook<void>, va_list);
  bool _WSPRecvDisconnect                       (APIHook<void>, va_list);
  bool _WSPRecvFrom                             (APIHook<void>, va_list);
  bool _WSPSelect                               (APIHook<void>, va_list);
  bool _WSPSend                                 (APIHook<void>, va_list);
  bool _WSPSendDisconnect                       (APIHook<void>, va_list);
  bool _WSPSendTo                               (APIHook<void>, va_list);
  bool _WSPSetSockOpt                           (APIHook<void>, va_list);
  bool _WSPShutdown                             (APIHook<void>, va_list);
  bool _WSPSocket                               (APIHook<void>, va_list);
  bool _WSPStartup                              (APIHook<void>, va_list);
  bool _WPUCloseEvent                           (APIHook<void>, va_list);
  bool _WPUCloseSocketHandle                    (APIHook<void>, va_list);
  bool _WPUCreateEvent                          (APIHook<void>, va_list);
  bool _WPUCreateSocketHandle                   (APIHook<void>, va_list);
  bool _WSCDeinstallProvider                    (APIHook<void>, va_list);
  bool _WSCInstallProvider                      (APIHook<void>, va_list);
  bool _WPUModifyIFSHandle                      (APIHook<void>, va_list);
  bool _WPUQueryBlockingCallback                (APIHook<void>, va_list);
  bool _WPUQuerySocketHandleContext             (APIHook<void>, va_list);
  bool _WPUQueueApc                             (APIHook<void>, va_list);
  bool _WPUResetEvent                           (APIHook<void>, va_list);
  bool _WPUSetEvent                             (APIHook<void>, va_list);
  bool _WPUFDIsSet                              (APIHook<void>, va_list);
  bool _WPUGetProviderPath                      (APIHook<void>, va_list);
  bool _WPUPostMessage                          (APIHook<void>, va_list);
  bool ___WSAFDIsSet                            (APIHook<void>, va_list);
  bool _WSCEnumProtocols                        (APIHook<void>, va_list);
  bool _WSAAddressToStringA                     (APIHook<void>, va_list);
  bool _WSAAddressToStringW                     (APIHook<void>, va_list);
  bool _WSAStringToAddressA                     (APIHook<void>, va_list);
  bool _WSAStringToAddressW                     (APIHook<void>, va_list);
  bool _WSALookupServiceBeginA                  (APIHook<void>, va_list);
  bool _WSALookupServiceBeginW                  (APIHook<void>, va_list);
  bool _WSALookupServiceNextA                   (APIHook<void>, va_list);
  bool _WSALookupServiceNextW                   (APIHook<void>, va_list);
  bool _WSALookupServiceEnd                     (APIHook<void>, va_list);
  bool _WSAGetAddressByNameA                    (APIHook<void>, va_list);
  bool _WSAGetAddressByNameW                    (APIHook<void>, va_list);
  bool _WSAInstallServiceClassA                 (APIHook<void>, va_list);
  bool _WSAInstallServiceClassW                 (APIHook<void>, va_list);
  bool _WSASetServiceA                          (APIHook<void>, va_list);
  bool _WSASetServiceW                          (APIHook<void>, va_list);
  bool _WSARemoveServiceClass                   (APIHook<void>, va_list);
  bool _WSAGetServiceClassInfoA                 (APIHook<void>, va_list);
  bool _WSAGetServiceClassInfoW                 (APIHook<void>, va_list);
  bool _WSAEnumNameSpaceProvidersA              (APIHook<void>, va_list);
  bool _WSAEnumNameSpaceProvidersW              (APIHook<void>, va_list);
  bool _WSAGetServiceClassNameByClassIdA        (APIHook<void>, va_list);
  bool _WSAGetServiceClassNameByClassIdW        (APIHook<void>, va_list);
  bool _NSPAddressToString                      (APIHook<void>, va_list);
  bool _NSPStringToAddress                      (APIHook<void>, va_list);
  bool _NSPCleanup                              (APIHook<void>, va_list);
  bool _NSPLookupServiceBegin                   (APIHook<void>, va_list);
  bool _NSPLookupServiceNext                    (APIHook<void>, va_list);
  bool _NSPLookupServiceEnd                     (APIHook<void>, va_list);
  bool _NSPGetAddressByName                     (APIHook<void>, va_list);
  bool _NSPSetService                           (APIHook<void>, va_list);
  bool _NSPInstallServiceClass                  (APIHook<void>, va_list);
  bool _NSPRemoveServiceClass                   (APIHook<void>, va_list);
  bool _NSPGetServiceClassInfo                  (APIHook<void>, va_list);
//bool _NSPEnumNameSpaceProviders               (APIHook<void>, va_list);
  bool _NSPGetServiceClassNameByClassId         (APIHook<void>, va_list);
  bool _WSCGetProviderPath                      (APIHook<void>, va_list);
  bool _WSCInstallNameSpace                     (APIHook<void>, va_list);
  bool _WSCUnInstallNameSpace                   (APIHook<void>, va_list);
  bool _WSCEnableNSProvider                     (APIHook<void>, va_list);
  bool _WSPAddressToString                      (APIHook<void>, va_list);
  bool _WSPStringToAddress                      (APIHook<void>, va_list);
protected :
  virtual bool accept                           (SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen,
                                                 APIHook<SOCKET> hook);
  virtual bool bind                             (SOCKET s, const struct sockaddr FAR *name, int namelen,
                                                 APIHook<int> hook);
  virtual bool closesocket                      (SOCKET s, APIHook<int> hook);
  virtual bool connect                          (SOCKET s, const struct sockaddr FAR *name, int namelen,
                                                 APIHook<int> hook);
  virtual bool getpeername                      (SOCKET s, struct sockaddr FAR *name, int FAR *namelen,
                                                 APIHook<int> hook);
  virtual bool getsockname                      (SOCKET s, struct sockaddr FAR *name, int FAR *namelen,
                                                 APIHook<int> hook);
  virtual bool getsockopt                       (SOCKET s, int level, int optname, char FAR *optval,
                                                 int FAR *optlen, APIHook<int> hook);
  virtual bool htonl                            (unsigned long hostlong, APIHook<unsigned long> hook);
  virtual bool htons                            (unsigned short hostshort, APIHook<unsigned short> hook);
  virtual bool ioctlsocket                      (SOCKET s, long cmd, unsigned long FAR *argp,
                                                 APIHook<int> hook);
  virtual bool listen                           (SOCKET s, int backlog, APIHook<int> hook);
  virtual bool ntohl                            (unsigned long netlong, APIHook<unsigned long> hook);
  virtual bool ntohs                            (unsigned short netshort, APIHook<unsigned short> hook);
  virtual bool recv                             (SOCKET s, char FAR *buf, int len, int flags,
                                                 APIHook<int> hook);
  virtual bool recvfrom                         (SOCKET s, char FAR *buf, int len, int flags,
                                                 struct sockaddr FAR *from, int FAR *fromlen,
                                                 APIHook<int> hook);
  virtual bool select                           (int nfds, fd_set FAR *readfds, fd_set FAR *writefds,
                                                 fd_set FAR *exceptfds, const struct timeval FAR *timeout,
                                                 APIHook<int> hook);
  virtual bool send                             (SOCKET s, const char FAR *buf, int len, int flags,
                                                 APIHook<int> hook);
  virtual bool sendto                           (SOCKET s, const char FAR *buf, int len, int flags,
                                                 const struct sockaddr FAR *to, int tolen,
                                                 APIHook<int> hook);
  virtual bool setsockopt                       (SOCKET s, int level, int optname, const char FAR *optval,
                                                 int optlen, APIHook<int> hook);
  virtual bool shutdown                         (SOCKET s, int how, APIHook<int> hook);
  virtual bool socket                           (int af, int type, int protocol, APIHook<SOCKET> hook);
  virtual bool WSAAccept                        (SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen, LPCONDITIONPROC lpfnCondition, unsigned long dwCallbackData, APIHook<SOCKET> hook);
  virtual bool WSAAsyncSelect                   (SOCKET s, HWND hWnd, unsigned int wMsg, long lEvent, APIHook<int> hook);
  virtual bool WSACancelBlockingCall            (APIHook<int> hook);
  virtual bool WSACleanup                       (APIHook<int> hook);
  virtual bool WSACloseEvent                    (WSAEVENT hEvent, APIHook<int> hook);
  virtual bool WSAConnect                       (SOCKET s, const struct sockaddr FAR *name, int namelen,
                                                 LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                                                 LPQOS lpSQOS, LPQOS lpGQOS, APIHook<int> hook);
  virtual bool WSACreateEvent                   (APIHook<WSAEVENT> hook);
  virtual bool WSADuplicateSocketA              (SOCKET s, DWORD dwProcessId,
                                                 LPWSAPROTOCOL_INFOA lpProtocolInfo,
                                                 APIHook<int> hook);
  virtual bool WSADuplicateSocketW              (SOCKET s, DWORD dwProcessId,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                                 APIHook<int> hook);
  virtual bool WSAEnumNetworkEvents             (SOCKET s, WSAEVENT hEventObject,
                                                 LPWSANETWORKEVENTS lpNetworkEvents,
                                                 APIHook<int> hook);
  virtual bool WSAEnumProtocolsA                (LPINT lpiProtocols, LPWSAPROTOCOL_INFOA lpProtocolBuffer,
                                                 LPDWORD lpdwBufferLength, APIHook<int> hook);
  virtual bool WSAEnumProtocolsW                (LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                                                 LPDWORD lpdwBufferLength, APIHook<int> hook);
  virtual bool WSAEventSelect                   (SOCKET s, WSAEVENT hEventObject, long lNetworkEvents,
                                                 APIHook<int> hook);
  virtual bool WSAGetLastError                  (APIHook<int> hook);
  virtual bool WSAGetOverlappedResult           (SOCKET s, LPWSAOVERLAPPED lpOverlapped,
                                                 LPDWORD lpcbTransfer, BOOL fWait,
                                                 unsigned long *lpdwFlags, APIHook<int> hook);
  virtual bool WSAGetQOSByName                  (SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS,
                                                 APIHook<int> hook);
  virtual bool WSAHtonl                         (SOCKET s, unsigned long hostlong,
                                                 unsigned long FAR *lpnetlong, APIHook<int> hook);
  virtual bool WSAHtons                         (SOCKET s, unsigned short hostshort, 
                                                 unsigned short FAR *lpnetshort, APIHook<int> hook);
  virtual bool WSAIoctl                         (SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer,
                                                 DWORD cbInBuffer, LPVOID lpvOutBuffer,
                                                 DWORD cbOutBuffer, LPDWORD lpcbBytesReturned,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 APIHook<int> hook);
  virtual bool WSAIsBlocking                    (APIHook<int> hook);
  virtual bool WSAJoinLeaf                      (SOCKET s, const struct sockaddr *name, int namelen,
                                                 LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                                                 LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags,
                                                 APIHook<SOCKET> hook);
  virtual bool WSANtohl                         (SOCKET s, unsigned long netlong,
                                                 unsigned long *lphostlong, APIHook<int> hook);
  virtual bool WSANtohs                         (SOCKET s, unsigned short netshort,
                                                 unsigned short *lphostshort, APIHook<int> hook);
  virtual bool WSARecv                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 APIHook<int> hook);
  virtual bool WSARecvDisconnect                (SOCKET s, LPWSABUF lpInboundDisconnectData,
                                                 APIHook<int> hook);
  virtual bool WSARecvFrom                      (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                                                 struct sockaddr *lpFrom, LPINT lpFromlen,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 APIHook<int> hook);
  virtual bool WSAResetEvent                    (WSAEVENT hEvent, APIHook<int> hook);
  virtual bool WSASend                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 APIHook<int> hook);
  virtual bool WSASendDisconnect                (SOCKET s, LPWSABUF lpOutboundDisconnectData,
                                                 APIHook<int> hook);
  virtual bool WSASendTo                        (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                                                 const struct sockaddr *lpTo, int iTolen,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 APIHook<int> hook);
  virtual bool WSASetBlockingHook               (FARPROC lpBlockFunc, APIHook<FARPROC> hook);
  virtual bool WSASetEvent                      (WSAEVENT hEvent, APIHook<int> hook);
  virtual bool WSASetLastError                  (int iError, APIHook<int> hook);
  virtual bool WSASocketA                       (int af, int type, int protocol,
                                                 LPWSAPROTOCOL_INFOA lpProtocolInfo, GROUP g,
                                                 DWORD dwFlags, APIHook<SOCKET> hook);
  virtual bool WSASocketW                       (int af, int type, int protocol,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g,
                                                 DWORD dwFlags, APIHook<SOCKET> hook);
  virtual bool WSAStartup                       (WORD wVersionRequested, LPWSADATA lpWSAData,
                                                 APIHook<int> hook);
  virtual bool WSAUnhookBlockingHook            (APIHook<int> hook);
  virtual bool WSAWaitForMultipleEvents         (DWORD cEvents, const WSAEVENT FAR *lphEvents,
                                                 BOOL fWaitAll, DWORD dwTimeout, BOOL fAlertable,
                                                 APIHook<DWORD> hook);
  virtual bool gethostbyaddr                    (const char FAR *addr, int len, int type,
                                                 APIHook<struct HOSTENT> hook);
  virtual bool gethostbyname                    (const char FAR *name, APIHook<HOSTENT> hook);
  virtual bool gethostname                      (char FAR *name, int namelen, APIHook<int> hook);
  virtual bool getprotobyname                   (const char FAR *name, APIHook<PROTOENT> hook);
  virtual bool getprotobynumber                 (int number, APIHook<PROTOENT> hook);
  virtual bool getservbyname                    (const char FAR *name, const char FAR *proto,
                                                 APIHook<SERVENT> hook);
  virtual bool getservbyport                    (int port, const char FAR *proto, APIHook<SERVENT> hook);
  virtual bool inet_addr                        (const char FAR *cp, APIHook<unsigned long> hook);
  virtual bool inet_ntoa                        (struct in_addr in, APIHook<char FAR *> hook);
  virtual bool WSAAsyncGetHostByAddr            (HWND hWnd, unsigned int wMsg, const char FAR *addr,  
                                                 int len, int type, char FAR *buf, int buflen,
                                                 APIHook<HANDLE> hook);
  virtual bool WSAAsyncGetHostByName            (HWND hWnd, unsigned int wMsg, const char FAR *name,  
                                                 char FAR *buf, int buflen, APIHook<HANDLE> hook);
  virtual bool WSAAsyncGetProtoByName           (HWND hWnd, unsigned int wMsg, const char FAR *name,  
                                                 char FAR *buf, int buflen, APIHook<HANDLE> hook);
  virtual bool WSAAsyncGetProtoByNumber         (HWND hWnd, unsigned int wMsg, int number, char FAR *buf,
                                                 int buflen, APIHook<HANDLE> hook);
  virtual bool WSAAsyncGetServByName            (HWND hWnd, unsigned int wMsg, const char FAR *name,  
                                                 const char FAR *proto, char FAR *buf, int buflen,
                                                 APIHook<HANDLE> hook);
  virtual bool WSAAsyncGetServByPort            (HWND hWnd, unsigned int wMsg, int port,
                                                 const char FAR *proto, char FAR *buf, int buflen,
                                                 APIHook<HANDLE> hook);
  virtual bool WSACancelAsyncRequest            (HANDLE hAsyncTaskHandle, APIHook<int> hook);
  virtual bool WSPAccept                        (SOCKET s, struct sockaddr FAR *addr, LPINT addrlen,
                                                 LPCONDITIONPROC lpfnCondition, DWORD dwCallbackData,
                                                 LPINT lpErrno, APIHook<SOCKET> hook);
  virtual bool WSPAsyncSelect                   (SOCKET s, HWND hWnd, unsigned int wMsg,
                                                 long lEvent, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPBind                          (SOCKET s, const struct sockaddr FAR *name, int namelen,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPCancelBlockingCall            (LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPCleanup                       (LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPCloseSocket                   (SOCKET s, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPConnect                       (SOCKET s, const struct sockaddr FAR *name, int namelen,
                                                 LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                                                 LPQOS lpSQOS, LPQOS lpGQOS, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPDuplicateSocket               (SOCKET s, DWORD dwProcessId,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPEnumNetworkEvents             (SOCKET s, WSAEVENT hEventObject,
                                                 LPWSANETWORKEVENTS lpNetworkEvents, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPEventSelect                   (SOCKET s, WSAEVENT hEventObject, long lNetworkEvents,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPGetOverlappedResult           (SOCKET s, LPWSAOVERLAPPED lpOverlapped,
                                                 LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags,
                                                 LPINT lpErrno, APIHook<BOOL> hook);
  virtual bool WSPGetPeerName                   (SOCKET s, struct sockaddr FAR *name, LPINT namelen,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPGetSockName                   (SOCKET s, struct sockaddr FAR *name, LPINT namelen,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPGetSockOpt                    (SOCKET s, int level, int optname, char FAR *optval, 
                                                 LPINT optlen, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPGetQOSByName                  (SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS,
                                                 LPINT lpErrno, APIHook<BOOL> hook);
  virtual bool WSPIoctl                         (SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer,
                                                 DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                                                 LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 LPWSATHREADID lpThreadId, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPJoinLeaf                      (SOCKET s, const struct sockaddr FAR *name, int namelen,
                                                 LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS,
                                                 LPQOS lpGQOS, DWORD dwFlags, LPINT lpErrno,
                                                 APIHook<SOCKET> hook);
  virtual bool WSPListen                        (SOCKET s, int backlog, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPRecv                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 LPWSATHREADID lpThreadId, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPRecvDisconnect                (SOCKET s, LPWSABUF lpInboundDisconnectData,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPRecvFrom                      (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                                                 struct sockaddr FAR *lpFrom, LPINT lpFromlen,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 LPWSATHREADID lpThreadId, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPSelect                        (int nfds, fd_set FAR *readfds, fd_set FAR *writefds,
                                                 fd_set FAR *exceptfds, const struct timeval FAR *timeout,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPSend                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 LPWSATHREADID lpThreadId, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPSendDisconnect                (SOCKET s, LPWSABUF lpOutboundDisconnectData,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPSendTo                        (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                                                 LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                                                 const struct sockaddr FAR *lpTo, int iTolen,
                                                 LPWSAOVERLAPPED lpOverlapped,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                                                 LPWSATHREADID lpThreadId, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSPSetSockOpt                    (SOCKET s, int level, int optname, const char FAR *optval,
                                                 int optlen, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPShutdown                      (SOCKET s, int how, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPSocket                        (int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                                 GROUP g, DWORD dwFlags, LPINT lpErrno, APIHook<SOCKET> hook);
  virtual bool WSPStartup                       (WORD wVersionRequested, LPWSPDATA lpWSPData,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, WSPUPCALLTABLE UpcallTable,
                                                 LPWSPPROC_TABLE lpProcTable, APIHook<int> hook);
  virtual bool WPUCloseEvent                    (WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> hook);
  virtual bool WPUCloseSocketHandle             (SOCKET s, LPINT lpErrno, APIHook<int> hook);
  virtual bool WPUCreateEvent                   (LPINT lpErrno, APIHook<WSAEVENT> hook);
  virtual bool WPUCreateSocketHandle            (DWORD dwCatalogEntryId, DWORD dwContext,
                                                 LPINT lpErrno, APIHook<SOCKET> hook);
  virtual bool WSCDeinstallProvider             (LPGUID lpProviderId, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSCInstallProvider               (const LPGUID lpProviderId, const LPWSTR lpszProviderDllPath,
                                                 const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
                                                 DWORD dwNumberOfEntries, LPINT lpErrno, APIHook<int> hook);
  virtual bool WPUModifyIFSHandle               (DWORD dwCatalogEntryId, SOCKET ProposedHandle,
                                                 LPINT lpErrno, APIHook<SOCKET> hook);
  virtual bool WPUQueryBlockingCallback         (DWORD dwCatalogEntryId, LPBLOCKINGCALLBACK FAR *lplpfnCallback,
                                                 LPDWORD lpdwContext, LPINT lpErrno, APIHook<int> hook);
  virtual bool WPUQuerySocketHandleContext      (SOCKET s, LPDWORD lpContext, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WPUQueueApc                      (LPWSATHREADID lpThreadId, LPWSAUSERAPC lpfnUserApc,
                                                 DWORD dwContext, LPINT lpErrno, APIHook<int> hook);
  virtual bool WPUResetEvent                    (WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> hook);
  virtual bool WPUSetEvent                      (WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> hook);
  virtual bool WPUFDIsSet                       (SOCKET s, FD_SET FAR *set, APIHook<int> hook);
  virtual bool WPUGetProviderPath               (LPGUID lpProviderId, LPWSTR lpszProviderDllPath,
                                                 LPINT lpProviderDllPathLen, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WPUPostMessage                   (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, APIHook<BOOL> hook);
  virtual bool __WSAFDIsSet            (SOCKET s, FD_SET FAR *set, APIHook<int> hook);
  virtual bool WSCEnumProtocols                 (LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                                                 LPDWORD lpdwBufferLength, LPINT lpErrno, APIHook<int> hook);
  virtual bool WSAAddressToStringA              (LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                                                 LPWSAPROTOCOL_INFOA lpProtocolInfo, OUT LPTSTR lpszAddressString,
                                                 IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> hook);
  virtual bool WSAAddressToStringW              (LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, OUT LPTSTR lpszAddressString,
                                                 IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> hook);
  virtual bool WSAStringToAddressA              (LPTSTR AddressString, INT AddressFamily,
                                                 LPWSAPROTOCOL_INFOA lpProtocolInfo, LPSOCKADDR lpAddress,
                                                 LPINT lpAddressLength, APIHook<INT> hook);
  virtual bool WSAStringToAddressW              (LPTSTR AddressString, INT AddressFamily,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                                                 LPINT lpAddressLength, APIHook<INT> hook);
  virtual bool WSALookupServiceBeginA           (LPWSAQUERYSETA lpqsRestrictions, DWORD dwControlFlags,
                                                 LPHANDLE lphLookup, APIHook<INT> hook);
  virtual bool WSALookupServiceBeginW           (LPWSAQUERYSETW lpqsRestrictions, DWORD dwControlFlags,
                                                 LPHANDLE lphLookup, APIHook<INT> hook);
  virtual bool WSALookupServiceNextA            (HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                                 LPWSAQUERYSETA lpqsResults, APIHook<INT> hook);
  virtual bool WSALookupServiceNextW            (HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                                 LPWSAQUERYSETW lpqsResults, APIHook<INT> hook);
  virtual bool WSALookupServiceEnd              (HANDLE hLookup, APIHook<INT> hook);
  virtual bool WSAGetAddressByNameA             (LPSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                                                 DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                                                 LPWSAQUERYSETA lpqsResults, DWORD dwResolution,
                                                 LPSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                                                 APIHook<int> hook);
  virtual bool WSAGetAddressByNameW             (LPSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                                                 DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                                                 LPWSAQUERYSETW lpqsResults, DWORD dwResolution,
                                                 LPSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                                                 APIHook<int> hook);
  virtual bool WSAInstallServiceClassA          (LPWSASERVICECLASSINFOA lpServiceClassInfo, APIHook<INT> hook);
  virtual bool WSAInstallServiceClassW          (LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<INT> hook);
  virtual bool WSASetServiceA                   (LPWSAQUERYSETA lpqsRegInfo, WSAESETSERVICEOP essOperation,
                                                 DWORD dwControlFlags, APIHook<INT> hook);
  virtual bool WSASetServiceW                   (LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation,
                                                 DWORD dwControlFlags, APIHook<INT> hook);
  virtual bool WSARemoveServiceClass            (LPGUID lpServiceClassId, APIHook<INT> hook);
  virtual bool WSAGetServiceClassInfoA          (LPGUID lpProviderId, LPGUID lpServiceClassId,
                                                 LPDWORD lpdwBufferLength,
                                                 LPWSASERVICECLASSINFOA lpServiceClassInfo,
                                                 APIHook<INT> hook);
  virtual bool WSAGetServiceClassInfoW          (LPGUID lpProviderId, LPGUID lpServiceClassId,
                                                 LPDWORD lpdwBufferLength,
                                                 LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                                 APIHook<INT> hook);
  virtual bool WSAEnumNameSpaceProvidersA       (IN OUT LPDWORD lpdwBufferLength,
                                                 OUT LPWSANAMESPACE_INFOA lpnspBuffer,
                                                 APIHook<INT> hook);
  virtual bool WSAEnumNameSpaceProvidersW       (IN OUT LPDWORD lpdwBufferLength,
                                                 OUT LPWSANAMESPACE_INFOW lpnspBuffer,
                                                 APIHook<INT> hook);
  virtual bool WSAGetServiceClassNameByClassIdA (LPGUID lpServiceClassId, LPSTR lpszServiceClassName,
                                                 LPDWORD lpdwBufferLength, APIHook<int> hook);
  virtual bool WSAGetServiceClassNameByClassIdW (LPGUID lpServiceClassId, LPWSTR lpszServiceClassName,
                                                 LPDWORD lpdwBufferLength, APIHook<int> hook);
  virtual bool NSPAddressToString               (LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                                 LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength,
                                                 APIHook<int> hook);
  virtual bool NSPStringToAddress               (LPWSTR AddressString, INT AddressFamily,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                                                 LPINT lpAddressLength, APIHook<int> hook);
  virtual bool NSPLookupServiceBegin            (LPGUID lpProviderId, LPWSAQUERYSETW lpqsRestrictions,
                                                 LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                                 DWORD dwControlFlags, LPHANDLE lphLookup,
                                                 APIHook<int> hook);
  virtual bool NSPLookupServiceNext             (HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                                 LPWSAQUERYSET lpqsResults, APIHook<int> hook);
  virtual bool NSPLookupServiceEnd              (HANDLE hLookup, APIHook<int> hook);
  virtual bool NSPGetAddressByName              (LPWSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                                                 DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                                                 LPWSAQUERYSETW lpqsResults, DWORD dwResolution,
                                                 LPWSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                                                 APIHook<int> hook);
  virtual bool NSPInstallServiceClass           (LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                                 APIHook<int> hook);
  virtual bool NSPSetService                    (LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                                 LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation,
                                                 DWORD dwControlFlags, APIHook<int> hook);
  virtual bool NSPRemoveServiceClass            (IN LPGUID lpProviderId, IN LPGUID lpServiceClassId,
                                                 APIHook<int> hook);
  virtual bool NSPGetServiceClassInfo           (IN LPGUID lpProviderId, IN OUT LPDWORD lpdwBufSize,
                                                 IN OUT LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                                 APIHook<int> hook);
//virtual bool NSPEnumNameSpaceProviders        ()
  virtual bool NSPGetServiceClassNameByClassId  (LPGUID lpServiceClassId, LPWSTR lpszServiceClassName,
                                                 LPDWORD lpdwBufferLength, APIHook<int> hook);
  virtual bool WSCGetProviderPath               (LPGUID lpProviderId, LPWSTR lpszProviderDllPath,
                                                 LPINT lpProviderDllPathLen, LPINT lpErrno,
                                                 APIHook<int> hook);
  virtual bool WSCInstallNameSpace              (LPWSTR lpszIdentifier, LPWSTR lpszPathName,
                                                 DWORD dwNameSpace, DWORD dwVersion,
                                                 LPGUID lpProviderId, APIHook<int> hook);
  virtual bool WSCUnInstallNameSpace            (LPGUID lpProviderId, APIHook<int> hook);
  virtual bool WSCEnableNSProvider              (LPGUID lpProviderId, BOOL fEnable, APIHook<int> hook);
  virtual bool WSPAddressToString               (LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                                 LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength,
                                                 LPINT lpErrno, APIHook<int> hook);
  virtual bool WSPStringToAddress               (LPWSTR AddressString, INT AddressFamily,
                                                 LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                                                 LPINT lpAddressLength, LPINT lpErrno,
                                                 APIHook<int> hook);
public:
  bool dispatch(int notificationCode, void *returnCode, char *LibraryName, bool preAPI, va_list vl);
};

#endif
