// Filename  : DTHandler.cpp
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

#pragma warning(disable: 4100 4189)

#include "DTHandler.hpp"
#include "dt_dll.hpp"

bool
DTHandler::dispatch(int notificationCode, void *returnCode,
                    char *LibraryName, bool preAPI, va_list vl) {
  switch (notificationCode) {
    case DTCODE_accept :
      return (_accept(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_bind :
      return (_bind(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_closesocket :
      return (_closesocket(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_connect :
      return (_connect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getpeername :
      return (_getpeername(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getsockname :
      return (_getsockname(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getsockopt :
      return (_getsockopt(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_htonl :
      return (_htonl(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_htons :
      return (_htons(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_ioctlsocket :
      return (_ioctlsocket(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_listen :
      return (_listen(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_ntohl :
      return (_ntohl(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_ntohs :
      return (_ntohs(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_recv :
      return (_recv(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_recvfrom :
      return (_recvfrom(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_select :
      return (_select(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_send :
      return (_send(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_sendto :
      return (_sendto(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_setsockopt :
      return (_setsockopt(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_shutdown :
      return (_shutdown(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_socket :
      return (_socket(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAccept :
      return (_WSAAccept(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncSelect :
      return (_WSAAsyncSelect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSACancelBlockingCall :
      return (_WSACancelBlockingCall(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSACleanup :
      return (_WSACleanup(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSACloseEvent :
      return (_WSACloseEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAConnect :
      return (_WSAConnect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSACreateEvent :
      return (_WSACreateEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSADuplicateSocketA :
      return (_WSADuplicateSocketA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAEnumNetworkEvents :
      return (_WSAEnumNetworkEvents(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAEnumProtocolsA :
      return (_WSAEnumProtocolsA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAEventSelect :
      return (_WSAEventSelect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetLastError :
      return (_WSAGetLastError(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetOverlappedResult :
      return (_WSAGetOverlappedResult(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetQOSByName :
      return (_WSAGetQOSByName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAHtonl :
      return (_WSAHtonl(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAHtons :
      return (_WSAHtons(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAIoctl :
      return (_WSAIoctl(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAIsBlocking :
      return (_WSAIsBlocking(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAJoinLeaf :
      return (_WSAJoinLeaf(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSANtohl :
      return (_WSANtohl(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSANtohs :
      return (_WSANtohs(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSARecv :
      return (_WSARecv(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSARecvDisconnect :
      return (_WSARecvDisconnect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSARecvFrom :
      return (_WSARecvFrom(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAResetEvent :
      return (_WSAResetEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASend :
      return (_WSASend(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASendDisconnect :
      return (_WSASendDisconnect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASendTo :
      return (_WSASendTo(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASetBlockingHook :
      return (_WSASetBlockingHook(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASetEvent :
      return (_WSASetEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASetLastError :
      return (_WSASetLastError(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASocketA :
      return (_WSASocketA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAStartup :
      return (_WSAStartup(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAUnhookBlockingHook :
      return (_WSAUnhookBlockingHook(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAWaitForMultipleEvents :
      return (_WSAWaitForMultipleEvents(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_gethostbyaddr :
      return (_gethostbyaddr(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_gethostbyname :
      return (_gethostbyname(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_gethostname :
      return (_gethostname(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getprotobyname :
      return (_getprotobyname(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getprotobynumber :
      return (_getprotobynumber(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getservbyname :
      return (_getservbyname(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_getservbyport :
      return (_getservbyport(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_inet_addr :
      return (_inet_addr(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_inet_ntoa :
      return (_inet_ntoa(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncGetHostByAddr :
      return (_WSAAsyncGetHostByAddr(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncGetHostByName :
      return (_WSAAsyncGetHostByName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncGetProtoByName :
      return (_WSAAsyncGetProtoByName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncGetProtoByNumber :
      return (_WSAAsyncGetProtoByNumber(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncGetServByName :
      return (_WSAAsyncGetServByName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAsyncGetServByPort :
      return (_WSAAsyncGetServByPort(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSACancelAsyncRequest :
      return (_WSACancelAsyncRequest(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPAccept :
      return (_WSPAccept(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPAsyncSelect :
      return (_WSPAsyncSelect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPBind :
      return (_WSPBind(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPCancelBlockingCall :
      return (_WSPCancelBlockingCall(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPCleanup :
      return (_WSPCleanup(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPCloseSocket :
      return (_WSPCloseSocket(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPConnect :
      return (_WSPConnect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPDuplicateSocket :
      return (_WSPDuplicateSocket(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPEnumNetworkEvents :
      return (_WSPEnumNetworkEvents(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPEventSelect :
      return (_WSPEventSelect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPGetOverlappedResult :
      return (_WSPGetOverlappedResult(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPGetPeerName :
      return (_WSPGetPeerName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
//  case DTCODE_WSPGetProcTable :
//    return (_WSPGetProcTable(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPGetSockName :
      return (_WSPGetSockName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPGetSockOpt :
      return (_WSPGetSockOpt(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPGetQOSByName :
      return (_WSPGetQOSByName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPIoctl :
      return (_WSPIoctl(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPJoinLeaf :
      return (_WSPJoinLeaf(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPListen :
      return (_WSPListen(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPRecv :
      return (_WSPRecv(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPRecvDisconnect :
      return (_WSPRecvDisconnect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPRecvFrom :
      return (_WSPRecvFrom(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPSelect :
      return (_WSPSelect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPSend :
      return (_WSPSend(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPSendDisconnect :
      return (_WSPSendDisconnect(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPSendTo :
      return (_WSPSendTo(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPSetSockOpt :
      return (_WSPSetSockOpt(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPShutdown :
      return (_WSPShutdown(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPSocket :
      return (_WSPSocket(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPStartup :
      return (_WSPStartup(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUCloseEvent :
      return (_WPUCloseEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUCloseSocketHandle :
      return (_WPUCloseSocketHandle(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUCreateEvent :
      return (_WPUCreateEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUCreateSocketHandle :
      return (_WPUCreateSocketHandle(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCDeinstallProvider :
      return (_WSCDeinstallProvider(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCInstallProvider :
      return (_WSCInstallProvider(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUModifyIFSHandle :
      return (_WPUModifyIFSHandle(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUQueryBlockingCallback :
      return (_WPUQueryBlockingCallback(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUQuerySocketHandleContext :
      return (_WPUQuerySocketHandleContext(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUQueueApc :
      return (_WPUQueueApc(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUResetEvent :
      return (_WPUResetEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUSetEvent :
      return (_WPUSetEvent(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCEnumProtocols :
      return (_WSCEnumProtocols(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUGetProviderPath :
      return (_WPUGetProviderPath(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUPostMessage :
      return (_WPUPostMessage(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WPUFDIsSet :
      return (_WPUFDIsSet(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSADuplicateSocketW :
      return (_WSADuplicateSocketW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAEnumProtocolsW :
      return (_WSAEnumProtocolsW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASocketW :
      return (_WSASocketW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE___WSAFDIsSet :
      return (___WSAFDIsSet(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAddressToStringA :
      return (_WSAAddressToStringA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAAddressToStringW :
      return (_WSAAddressToStringW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAStringToAddressA :
      return (_WSAStringToAddressA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAStringToAddressW :
      return (_WSAStringToAddressW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSALookupServiceBeginA :
      return (_WSALookupServiceBeginA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSALookupServiceBeginW :
      return (_WSALookupServiceBeginW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSALookupServiceNextA :
      return (_WSALookupServiceNextA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSALookupServiceNextW :
      return (_WSALookupServiceNextW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSALookupServiceEnd :
      return (_WSALookupServiceEnd(APIHook<void>(returnCode, LibraryName, preAPI), vl));
//  case DTCODE_WSAGetAddressByNameA :
//    return (_WSAGetAddressByNameA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
//  case DTCODE_WSAGetAddressByNameW :
//    return (_WSAGetAddressByNameW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAInstallServiceClassA :
      return (_WSAInstallServiceClassA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAInstallServiceClassW :
      return (_WSAInstallServiceClassW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASetServiceA :
      return (_WSASetServiceA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSASetServiceW :
      return (_WSASetServiceW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSARemoveServiceClass :
      return (_WSARemoveServiceClass(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetServiceClassInfoA :
      return (_WSAGetServiceClassInfoA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetServiceClassInfoW :
      return (_WSAGetServiceClassInfoW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAEnumNameSpaceProvidersA :
      return (_WSAEnumNameSpaceProvidersA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAEnumNameSpaceProvidersW :
      return (_WSAEnumNameSpaceProvidersW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetServiceClassNameByClassIdA :
      return (_WSAGetServiceClassNameByClassIdA(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSAGetServiceClassNameByClassIdW :
      return (_WSAGetServiceClassNameByClassIdW(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPAddressToString :
      return (_NSPAddressToString(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPStringToAddress :
      return (_NSPStringToAddress(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPLookupServiceBegin :
      return (_NSPLookupServiceBegin(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPLookupServiceNext :
      return (_NSPLookupServiceNext(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPLookupServiceEnd :
      return (_NSPLookupServiceEnd(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPGetAddressByName :
      return (_NSPGetAddressByName(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPInstallServiceClass :
      return (_NSPInstallServiceClass(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPSetService :
      return (_NSPSetService(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPRemoveServiceClass :
      return (_NSPRemoveServiceClass(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPGetServiceClassInfo :
      return (_NSPGetServiceClassInfo(APIHook<void>(returnCode, LibraryName, preAPI), vl));
//  case DTCODE_NSPEnumNameSpaceProviders :
//    return (_NSPEnumNameSpaceProviders(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_NSPGetServiceClassNameByClassId :
      return (_NSPGetServiceClassNameByClassId(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCGetProviderPath :
      return (_WSCGetProviderPath(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCInstallNameSpace :
      return (_WSCInstallNameSpace(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCUnInstallNameSpace :
      return (_WSCUnInstallNameSpace(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSCEnableNSProvider :
      return (_WSCEnableNSProvider(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPAddressToString :
      return (_WSPAddressToString(APIHook<void>(returnCode, LibraryName, preAPI), vl));
    case DTCODE_WSPStringToAddress :
      return (_WSPStringToAddress(APIHook<void>(returnCode, LibraryName, preAPI), vl));
  }
  return (0);
}

bool
DTHandler::accept(SOCKET s, struct sockaddr *addr, int *addrlen, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_accept(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *addr = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  int *addrlen = (int *)*va_arg(vList, int **);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->accept(s, addr, addrlen, apiHook));
}

bool
DTHandler::bind(SOCKET s, const struct sockaddr *name, int namelen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_bind(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->bind(s, name, namelen, apiHook));
}

bool
DTHandler::closesocket(SOCKET s, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_closesocket(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->closesocket(s, apiHook));
}

bool
DTHandler::connect(SOCKET s, const struct sockaddr *name, int namelen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_connect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->connect(s, name, namelen, apiHook));
}

bool
DTHandler::getpeername(SOCKET s, struct sockaddr *name, int *namelen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_getpeername(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  int *namelen = (int *)*va_arg(vList, int **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getpeername(s, name, namelen, apiHook));
}

bool
DTHandler::getsockname(SOCKET s, struct sockaddr *name, int *namelen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_getsockname(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  int *namelen = (int *)*va_arg(vList, int **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getsockname(s, name, namelen, apiHook));
}

bool
DTHandler::getsockopt(SOCKET s, int level, int optname, char *optval, int *optlen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_getsockopt(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int level = (int)*va_arg(vList, int *);
  int optname = (int)*va_arg(vList, int *);
  char *optval = (char *)*va_arg(vList, char **);
  int *optlen = (int *)*va_arg(vList, int **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getsockopt(s, level, optname, optval, optlen, apiHook));
}

bool
DTHandler::htonl(DWORD hostlong, APIHook<DWORD> hook) {
  return (0);
}

bool
DTHandler::_htonl(APIHook<void> hook, va_list vList) {
  DWORD hostlong = (DWORD)*va_arg(vList, DWORD *);
  APIHook<DWORD> apiHook((DWORD *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->htonl(hostlong, apiHook));
}

bool
DTHandler::htons(unsigned short hostshort, APIHook<unsigned short> hook) {
  return (0);
}

bool
DTHandler::_htons(APIHook<void> hook, va_list vList) {
  unsigned short hostshort = (unsigned short)*va_arg(vList, unsigned short *);
  APIHook<unsigned short> apiHook((unsigned short *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->htons(hostshort, apiHook));
}

bool
DTHandler::ioctlsocket(SOCKET s, long cmd, unsigned long *argp, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_ioctlsocket(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  long cmd = (long)*va_arg(vList, long *);
  unsigned long *argp = (unsigned long *)*va_arg(vList, unsigned long **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->ioctlsocket(s, cmd, argp, apiHook));
}

bool
DTHandler::listen(SOCKET s, int backlog, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_listen(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int backlog = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->listen(s, backlog, apiHook));
}

bool
DTHandler::ntohl(unsigned long netlong, APIHook<DWORD> hook) {
  return (0);
}

bool
DTHandler::_ntohl(APIHook<void> hook, va_list vList) {
  unsigned long netlong = (unsigned long)*va_arg(vList, unsigned long *);
  APIHook<DWORD> apiHook((DWORD *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->ntohl(netlong, apiHook));
}

bool
DTHandler::ntohs(unsigned short netshort, APIHook<unsigned short> hook) {
  return (0);
}

bool
DTHandler::_ntohs(APIHook<void> hook, va_list vList) {
  unsigned short netshort = (unsigned short)*va_arg(vList, unsigned short *);
  APIHook<WORD> apiHook((WORD *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->ntohs(netshort, apiHook));
}

bool
DTHandler::recv(SOCKET s, char *buf, int len, int flags, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_recv(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  char *buf = (char *)*va_arg(vList, char **);
  int len = (int)*va_arg(vList, int *);
  int flags = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->recv(s, buf, len, flags, apiHook));
}

bool
DTHandler::recvfrom(SOCKET s, char *buf, int len, int flags, struct sockaddr *from, int *fromlen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_recvfrom(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  char *buf = (char *)*va_arg(vList, char **);
  int len = (int)*va_arg(vList, int *);
  int flags = (int)*va_arg(vList, int *);
  struct sockaddr *from = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  int *fromlen = (int *)*va_arg(vList, int **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->recvfrom(s, buf, len, flags, from, fromlen, apiHook));
}

bool
DTHandler::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,             
                  const struct timeval *timeout, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_select(APIHook<void> hook, va_list vList) {
  int nfds = (int)*va_arg(vList, int *);
  fd_set *readfds = (fd_set *)*va_arg(vList, fd_set **);
  fd_set *writefds = (fd_set *)*va_arg(vList, fd_set **);
  fd_set *exceptfds = (fd_set *)*va_arg(vList, fd_set **);
  const struct timeval *timeout = (const struct timeval *)*va_arg(vList, const struct timeval **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->select(nfds, readfds, writefds, exceptfds, timeout, apiHook));
}

bool
DTHandler::send(SOCKET s, const char *buf, int len, int flags, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_send(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const char *buf = (const char *)*va_arg(vList, const char **);
  int len = (int)*va_arg(vList, int *);
  int flags = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->send(s, buf, len, flags, apiHook));
}

bool
DTHandler::sendto(SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_sendto(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const char *buf = (const char *)*va_arg(vList, const char **);
  int len = (int)*va_arg(vList, int *);
  int flags = (int)*va_arg(vList, int *);
  const struct sockaddr *to = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int tolen = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->sendto(s, buf, len, flags, to, tolen, apiHook));
}

bool
DTHandler::setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_setsockopt(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int level = (int)*va_arg(vList, int *);
  int optname = (int)*va_arg(vList, int *);
  const char *optval = (const char *)*va_arg(vList, const char **);
  int optlen = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->setsockopt(s, level, optname, optval, optlen, apiHook));
}

bool
DTHandler::shutdown(SOCKET s, int how, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_shutdown(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int how = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->shutdown(s, how, apiHook));
}

bool
DTHandler::socket(int af, int type, int protocol, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_socket(APIHook<void> hook, va_list vList) {
  int af = (int)*va_arg(vList, int *);
  int type = (int)*va_arg(vList, int *);
  int protocol = (int)*va_arg(vList, int *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->socket(af, type, protocol, apiHook));
}

bool
DTHandler::WSAAccept(SOCKET s, struct sockaddr *addr, int *addrlen, LPCONDITIONPROC lpfnCondition, unsigned long dwCallbackData, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSAAccept(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *addr = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  int *addrlen = (int *)*va_arg(vList, int **);
  LPCONDITIONPROC lpfnCondition = (LPCONDITIONPROC)*va_arg(vList, LPCONDITIONPROC *);
  unsigned long dwCallbackData = (unsigned long)*va_arg(vList, unsigned long *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAccept(s, addr, addrlen, lpfnCondition, dwCallbackData, apiHook));
}

bool
DTHandler::WSAAsyncSelect(SOCKET s, HWND hWnd, unsigned int wMsg, long lEvent, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncSelect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  long lEvent = (long)*va_arg(vList, long *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncSelect(s, hWnd, wMsg, lEvent, apiHook));
}

bool
DTHandler::WSACancelBlockingCall(APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSACancelBlockingCall(APIHook<void> hook, va_list vList) {
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSACancelBlockingCall(apiHook));
}

bool
DTHandler::WSACleanup(APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSACleanup(APIHook<void> hook, va_list vList) {
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSACleanup(apiHook));
}

bool
DTHandler::WSACloseEvent(WSAEVENT hEvent, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSACloseEvent(APIHook<void> hook, va_list vList) {
  WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSACloseEvent(hEvent, apiHook));
}

bool
DTHandler::WSAConnect(SOCKET s, const struct sockaddr *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAConnect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
  LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS, apiHook));
}

bool
DTHandler::WSACreateEvent(APIHook<WSAEVENT> hook) {
  return (0);
}

bool
DTHandler::_WSACreateEvent(APIHook<void> hook, va_list vList) {
  APIHook<WSAEVENT> apiHook((WSAEVENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSACreateEvent(apiHook));
}

bool
DTHandler::WSADuplicateSocketA(SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOA lpProtocolInfo, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSADuplicateSocketA(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  DWORD dwProcessId = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSADuplicateSocketA(s, dwProcessId, lpProtocolInfo, apiHook));
}

bool
DTHandler::WSADuplicateSocketW(SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOW lpProtocolInfo, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSADuplicateSocketW(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  DWORD dwProcessId = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSADuplicateSocketW(s, dwProcessId, lpProtocolInfo, apiHook));
}

bool
DTHandler::WSAEnumNetworkEvents(SOCKET s, WSAEVENT hEventObject, LPWSANETWORKEVENTS lpNetworkEvents, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAEnumNetworkEvents(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  LPWSANETWORKEVENTS lpNetworkEvents = (LPWSANETWORKEVENTS)*va_arg(vList, LPWSANETWORKEVENTS *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAEnumNetworkEvents(s, hEventObject, lpNetworkEvents, apiHook));
}

bool
DTHandler::WSAEnumProtocolsA(LPINT lpiProtocols, LPWSAPROTOCOL_INFOA lpProtocolBuffer,
                             LPDWORD lpdwBufferLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAEnumProtocolsA(APIHook<void> hook, va_list vList) {
  LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
  LPWSAPROTOCOL_INFOA lpProtocolBuffer = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAEnumProtocolsA(lpiProtocols, lpProtocolBuffer, lpdwBufferLength, apiHook));
}

bool
DTHandler::WSAEnumProtocolsW(LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                             LPDWORD lpdwBufferLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAEnumProtocolsW(APIHook<void> hook, va_list vList) {
  LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
  LPWSAPROTOCOL_INFOW lpProtocolBuffer = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAEnumProtocolsW(lpiProtocols, lpProtocolBuffer, lpdwBufferLength, apiHook));
}

bool
DTHandler::WSAEventSelect(SOCKET s, WSAEVENT hEventObject, long lNetworkEvents, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAEventSelect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  long lNetworkEvents = (long)*va_arg(vList, long *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAEventSelect(s, hEventObject, lNetworkEvents, apiHook));
}

bool
DTHandler::WSAGetLastError(APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetLastError(APIHook<void> hook, va_list vList) {
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetLastError(apiHook));
}

bool
DTHandler::WSAGetOverlappedResult(SOCKET s, LPWSAOVERLAPPED lpOverlapped, LPDWORD lpcbTransfer,
                                  BOOL fWait, LPDWORD lpdwFlags, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetOverlappedResult(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPDWORD lpcbTransfer = (LPDWORD)*va_arg(vList, LPDWORD *);
  BOOL fWait = (BOOL)*va_arg(vList, BOOL *);
  LPDWORD lpdwFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetOverlappedResult(s, lpOverlapped, lpcbTransfer, fWait, lpdwFlags, apiHook));
}

bool
DTHandler::WSAGetQOSByName(SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetQOSByName(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpQOSName = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPQOS lpQOS = (LPQOS)*va_arg(vList, LPQOS *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetQOSByName(s, lpQOSName, lpQOS, apiHook));
}

bool
DTHandler::WSAHtonl(SOCKET s, unsigned long hostlong, unsigned long *lpnetlong, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAHtonl(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  unsigned long hostlong = (unsigned long)*va_arg(vList, unsigned long *);
  unsigned long *lpnetlong = (unsigned long *)*va_arg(vList, unsigned long **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAHtonl(s, hostlong, lpnetlong, apiHook));
}

bool
DTHandler::WSAHtons(SOCKET s, unsigned short hostshort, unsigned short *lpnetshort, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAHtons(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  unsigned short hostshort = (unsigned short)*va_arg(vList, unsigned short *);
  unsigned short *lpnetshort = (unsigned short *)*va_arg(vList, unsigned short **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAHtons(s, hostshort, lpnetshort, apiHook));
}

bool
DTHandler::WSAIoctl(SOCKET s, DWORD dwIoControlCode,
                    LPVOID lpvInBuffer, DWORD cbInBuffer,
                    LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                    LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped,
                    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAIoctl(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  DWORD dwIoControlCode = (DWORD)*va_arg(vList, DWORD *);
  LPVOID lpvInBuffer = (LPVOID)*va_arg(vList, LPVOID *);
  DWORD cbInBuffer = (DWORD)*va_arg(vList, DWORD *);
  LPVOID lpvOutBuffer = (LPVOID)*va_arg(vList, LPVOID *);
  DWORD cbOutBuffer = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpcbBytesReturned = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAIoctl(s, dwIoControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer, cbOutBuffer,
                         lpcbBytesReturned, lpOverlapped, lpCompletionRoutine, apiHook));
}

bool
DTHandler::WSAIsBlocking(APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAIsBlocking(APIHook<void> hook, va_list vList) {
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAIsBlocking(apiHook));
}

bool
DTHandler::WSAJoinLeaf(SOCKET s, const struct sockaddr *name, int namelen,
                       LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                       LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags,
                       APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSAJoinLeaf(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
  LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAJoinLeaf(s, name, namelen, lpCallerData, lpCalleeData,
                            lpSQOS, lpGQOS, dwFlags, apiHook));
}

bool
DTHandler::WSANtohl(SOCKET s, unsigned long netlong, unsigned long *lphostlong, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSANtohl(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  unsigned long netlong = (unsigned long)*va_arg(vList, unsigned long *);
  unsigned long *lphostlong = (unsigned long *)*va_arg(vList, unsigned long **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSANtohl(s, netlong, lphostlong, apiHook));
}

bool
DTHandler::WSANtohs(SOCKET s, unsigned short netshort, unsigned short *lphostshort, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSANtohs(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  unsigned short netshort = (unsigned short)*va_arg(vList, unsigned short *);
  unsigned short *lphostshort = (unsigned short *)*va_arg(vList, unsigned short **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSANtohs(s, netshort, lphostshort, apiHook));
}

bool
DTHandler::WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                   LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                   LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSARecv(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                        lpOverlapped, lpCompletionRoutine, apiHook));
}

bool
DTHandler::WSARecvDisconnect(SOCKET s, LPWSABUF lpInboundDisconnectData, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSARecvDisconnect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpInboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSARecvDisconnect(s, lpInboundDisconnectData, apiHook));
}

bool
DTHandler::WSARecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                       LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                       struct sockaddr *lpFrom, LPINT lpFromlen,
                       LPWSAOVERLAPPED lpOverlapped,
                       LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                       APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSARecvFrom(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
  struct sockaddr *lpFrom = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  LPINT lpFromlen = (LPINT)*va_arg(vList, LPINT *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSARecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                            lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine, apiHook));
}

bool
DTHandler::WSAResetEvent(WSAEVENT hEvent, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAResetEvent(APIHook<void> hook, va_list vList) {
  WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAResetEvent(hEvent, apiHook));
}

bool
DTHandler::WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent,
                   DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSASend(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                        lpOverlapped, lpCompletionRoutine, apiHook));
}

bool
DTHandler::WSASendDisconnect(SOCKET s, LPWSABUF lpOutboundDisconnectData, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSASendDisconnect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpOutboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASendDisconnect(s, lpOutboundDisconnectData, apiHook));
}

bool
DTHandler::WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent,
                     DWORD dwFlags, const struct sockaddr *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped,
                     LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                     APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSASendTo(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  const struct sockaddr *lpTo = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int iTolen = (int)*va_arg(vList, int *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                          lpTo, iTolen, lpOverlapped, lpCompletionRoutine, apiHook));
}

bool
DTHandler::WSASetBlockingHook(FARPROC lpBlockFunc, APIHook<FARPROC> hook) {
  return (0);
}

bool
DTHandler::_WSASetBlockingHook(APIHook<void> hook, va_list vList) {
  FARPROC lpBlockFunc = (FARPROC)*va_arg(vList, FARPROC *);
  APIHook<FARPROC> apiHook((FARPROC *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASetBlockingHook(lpBlockFunc, apiHook));
}

bool
DTHandler::WSASetEvent(WSAEVENT hEvent, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSASetEvent(APIHook<void> hook, va_list vList) {
  WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASetEvent(hEvent, apiHook));
}

bool
DTHandler::WSASetLastError(int iError, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSASetLastError(APIHook<void> hook, va_list vList) {
  int iError = (int)*va_arg(vList, int *);
  // WSASetLastError returns void, so return value should be NULL
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASetLastError(iError, apiHook));
}

bool
DTHandler::WSASocketA(int af, int type, int protocol, LPWSAPROTOCOL_INFOA lpProtocolInfo,
                      GROUP g, DWORD dwFlags, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSASocketA(APIHook<void> hook, va_list vList) {
  int af = (int)*va_arg(vList, int *);
  int type = (int)*va_arg(vList, int *);
  int protocol = (int)*va_arg(vList, int *);
  LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  GROUP g = (GROUP)*va_arg(vList, GROUP *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASocketA(af, type, protocol, lpProtocolInfo, g, dwFlags, apiHook));
}

bool
DTHandler::WSASocketW(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo,
                      GROUP g, DWORD dwFlags, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSASocketW(APIHook<void> hook, va_list vList) {
  int af = (int)*va_arg(vList, int *);
  int type = (int)*va_arg(vList, int *);
  int protocol = (int)*va_arg(vList, int *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  GROUP g = (GROUP)*va_arg(vList, GROUP *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASocketW(af, type, protocol, lpProtocolInfo, g, dwFlags, apiHook));
}

bool
DTHandler::WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAStartup(APIHook<void> hook, va_list vList) {
  WORD wVersionRequested = (WORD)*va_arg(vList, LPDWORD);
  LPWSADATA lpWSAData = (LPWSADATA)*va_arg(vList, LPWSADATA *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAStartup(wVersionRequested, lpWSAData, apiHook));
}

bool
DTHandler::WSAUnhookBlockingHook(APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAUnhookBlockingHook(APIHook<void> hook, va_list vList) {
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAUnhookBlockingHook(apiHook));
}

bool
DTHandler::WSAWaitForMultipleEvents(DWORD cEvents, const WSAEVENT *lphEvents,
                                    BOOL fWaitAll, DWORD dwTimeout, BOOL fAlertable,
                                    APIHook<DWORD> hook) {
  return (0);
}

bool
DTHandler::_WSAWaitForMultipleEvents(APIHook<void> hook, va_list vList) {
  DWORD cEvents = (DWORD)*va_arg(vList, DWORD *);
  const WSAEVENT *lphEvents = (const WSAEVENT *)*va_arg(vList, const WSAEVENT **);
  BOOL fWaitAll = (BOOL)*va_arg(vList, BOOL *);
  DWORD dwTimeout = (DWORD)*va_arg(vList, DWORD *);
  BOOL fAlertable = (BOOL)*va_arg(vList, BOOL *);
  APIHook<DWORD> apiHook((DWORD *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAWaitForMultipleEvents(cEvents, lphEvents, fWaitAll, dwTimeout, fAlertable, apiHook));
}

bool
DTHandler::gethostbyaddr(const char *addr, int len, int type, APIHook<HOSTENT> hook) {
  return (0);
}

bool
DTHandler::_gethostbyaddr(APIHook<void> hook, va_list vList) {
  const char *addr = (const char *)*va_arg(vList, const char **);
  int len = (int)*va_arg(vList, int *);
  int type = (int)*va_arg(vList, int *);
  APIHook<HOSTENT> apiHook((HOSTENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->gethostbyaddr(addr, len, type, apiHook));
}

bool
DTHandler::gethostbyname(const char *name, APIHook<HOSTENT> hook) {
  return (0);
}

bool
DTHandler::_gethostbyname(APIHook<void> hook, va_list vList) {
  const char *name = (const char *)*va_arg(vList, const char **);
  APIHook<HOSTENT> apiHook((HOSTENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->gethostbyname(name, apiHook));
}

bool
DTHandler::gethostname(char *name, int namelen, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_gethostname(APIHook<void> hook, va_list vList) {
  char *name = (char *)*va_arg(vList, char **);
  int namelen = (int)*va_arg(vList, int *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->gethostname(name, namelen, apiHook));
}

bool
DTHandler::getprotobyname(const char *name, APIHook<PROTOENT> hook) {
  return (0);
}

bool
DTHandler::_getprotobyname(APIHook<void> hook, va_list vList) {
  const char *name = (const char *)*va_arg(vList, const char **);
  APIHook<PROTOENT> apiHook((PROTOENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getprotobyname(name, apiHook));
}

bool
DTHandler::getprotobynumber(int number, APIHook<PROTOENT> hook) {
  return (0);
}

bool
DTHandler::_getprotobynumber(APIHook<void> hook, va_list vList) {
  int number = (int)*va_arg(vList, int *);
  APIHook<PROTOENT> apiHook((PROTOENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getprotobynumber(number, apiHook));
}

bool
DTHandler::getservbyname(const char *name, const char *proto, APIHook<SERVENT> hook) {
  return (0);
}

bool
DTHandler::_getservbyname(APIHook<void> hook, va_list vList) {
  const char *name = (const char *)*va_arg(vList, const char **);
  const char *proto = (const char *)*va_arg(vList, const char **);
  APIHook<SERVENT> apiHook((SERVENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getservbyname(name, proto, apiHook));
}

bool
DTHandler::getservbyport(int port, const char *proto, APIHook<SERVENT> hook) {
  return (0);
}

bool
DTHandler::_getservbyport(APIHook<void> hook, va_list vList) {
  int port = (int)*va_arg(vList, int *);
  const char *proto = (const char *)*va_arg(vList, const char **);
  APIHook<SERVENT> apiHook((SERVENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->getservbyport(port, proto, apiHook));
}

bool
DTHandler::inet_addr(const char *cp, APIHook<unsigned long> hook) {
  return (0);
}

bool
DTHandler::_inet_addr(APIHook<void> hook, va_list vList) {
  const char *cp = (const char *)*va_arg(vList, const char **);
  APIHook<unsigned long> apiHook((unsigned long *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->inet_addr(cp, apiHook));
}

bool
DTHandler::inet_ntoa(struct in_addr in, APIHook<char *> hook) {
  return (0);
}

bool
DTHandler::_inet_ntoa(APIHook<void> hook, va_list vList) {
  struct in_addr in = (struct in_addr)*va_arg(vList, struct in_addr *);
  APIHook<char *> apiHook((char **)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->inet_ntoa(in, apiHook));
}

bool
DTHandler::WSAAsyncGetHostByAddr(HWND hWnd, unsigned int wMsg, const char *addr,  
                                 int len, int type, char *buf, int buflen,
                                 APIHook<HANDLE> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncGetHostByAddr(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  const char *addr = (const char *)*va_arg(vList, const char **);
  int len = (int)*va_arg(vList, int *);
  int type = (int)*va_arg(vList, int *);
  char *buf = (char *)*va_arg(vList, char **);
  int buflen = (int)*va_arg(vList, int *);
  APIHook<HANDLE> apiHook((HANDLE *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncGetHostByAddr(hWnd, wMsg, addr, len, type, buf, buflen, apiHook));
}

bool
DTHandler::WSAAsyncGetHostByName(HWND hWnd, unsigned int wMsg, const char *name,  
                                 char *buf, int buflen, APIHook<HANDLE> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncGetHostByName(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  const char *name = (const char *)*va_arg(vList, const char **);
  char *buf = (char *)*va_arg(vList, char **);
  int buflen = (int)*va_arg(vList, int *);
  APIHook<HANDLE> apiHook((HANDLE *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncGetHostByName(hWnd, wMsg, name, buf, buflen, apiHook));
}

bool
DTHandler::WSAAsyncGetProtoByName(HWND hWnd, unsigned int wMsg, const char *name,  
                                  char *buf, int buflen, APIHook<HANDLE> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncGetProtoByName(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  const char *name = (const char *)*va_arg(vList, const char **);
  char *buf = (char *)*va_arg(vList, char **);
  int buflen = (int)*va_arg(vList, int *);
  APIHook<HANDLE> apiHook((HANDLE *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncGetProtoByName(hWnd, wMsg, name, buf, buflen, apiHook));
}

bool
DTHandler::WSAAsyncGetProtoByNumber(HWND hWnd, unsigned int wMsg, int number, char *buf,
                                    int buflen, APIHook<HANDLE> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncGetProtoByNumber(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  int number = (int)*va_arg(vList, int *);
  char *buf = (char *)*va_arg(vList, char **);
  int buflen = (int)*va_arg(vList, int *);
  APIHook<HANDLE> apiHook((HANDLE *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncGetProtoByNumber(hWnd, wMsg, number, buf, buflen, apiHook));
}

bool
DTHandler::WSAAsyncGetServByName(HWND hWnd, unsigned int wMsg, const char *name,  
                                 const char *proto, char *buf, int buflen,
                                 APIHook<HANDLE> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncGetServByName(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  const char *name = (const char *)*va_arg(vList, const char **);
  const char *proto = (const char *)*va_arg(vList, const char **);
  char *buf = (char *)*va_arg(vList, char **);
  int buflen = (int)*va_arg(vList, int *);
  APIHook<HANDLE> apiHook((HANDLE *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncGetServByName(hWnd, wMsg, name, proto, buf, buflen, apiHook));
}

bool
DTHandler::WSAAsyncGetServByPort(HWND hWnd, unsigned int wMsg, int port,
                                 const char *proto, char *buf, int buflen,
                                 APIHook<HANDLE> hook) {
  return (0);
}

bool
DTHandler::_WSAAsyncGetServByPort(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  int port = (int)*va_arg(vList, int *);
  char *proto = (char *)*va_arg(vList, char **);
  char *buf = (char *)*va_arg(vList, char **);
  int buflen = (int)*va_arg(vList, int *);
  APIHook<HANDLE> apiHook((HANDLE *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAsyncGetServByPort(hWnd, wMsg, port, proto, buf, buflen, apiHook));
}

bool
DTHandler::WSACancelAsyncRequest(HANDLE hAsyncTaskHandle, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSACancelAsyncRequest(APIHook<void> hook, va_list vList) {
  HANDLE hAsyncTaskHandle = (HANDLE)*va_arg(vList, HANDLE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSACancelAsyncRequest(hAsyncTaskHandle, apiHook));
}

bool
DTHandler::WSPAccept(SOCKET s, struct sockaddr *addr, LPINT addrlen,
                     LPCONDITIONPROC lpfnCondition, DWORD dwCallbackData,
                     LPINT lpErrno, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSPAccept(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *addr = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  LPINT addrlen = (LPINT)*va_arg(vList, LPINT *);
  LPCONDITIONPROC lpfnCondition = (LPCONDITIONPROC)*va_arg(vList, LPCONDITIONPROC *);
  DWORD dwCallbackData = (DWORD)*va_arg(vList, DWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPAccept(s, addr, addrlen, lpfnCondition, dwCallbackData, lpErrno, apiHook));
}

bool
DTHandler::WSPAsyncSelect(SOCKET s, HWND hWnd, unsigned int wMsg,
                          long lEvent, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPAsyncSelect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
  long lEvent = (long)*va_arg(vList, long *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno, apiHook));
}

bool
DTHandler::WSPBind(SOCKET s, const struct sockaddr *name, int namelen,
                   LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPBind(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPBind(s, name, namelen, lpErrno, apiHook));
}

bool
DTHandler::WSPCancelBlockingCall(LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPCancelBlockingCall(APIHook<void> hook, va_list vList) {
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPCancelBlockingCall(lpErrno, apiHook));
}

bool
DTHandler::WSPCleanup(LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPCleanup(APIHook<void> hook, va_list vList) {
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPCleanup(lpErrno, apiHook));
}

bool
DTHandler::WSPCloseSocket(SOCKET s, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPCloseSocket(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPCloseSocket(s, lpErrno, apiHook));
}

bool
DTHandler::WSPConnect(SOCKET s, const struct sockaddr *name, int namelen,
                      LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                      LPQOS lpSQOS, LPQOS lpGQOS, LPINT lpErrno,
                      APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPConnect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
  LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPConnect(s, name, namelen, lpCallerData, lpCalleeData,
                           lpSQOS, lpGQOS, lpErrno, apiHook));
}

bool
DTHandler::WSPDuplicateSocket(SOCKET s, DWORD dwProcessId,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPINT lpErrno,
                              APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPDuplicateSocket(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  DWORD dwProcessId = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPDuplicateSocket(s, dwProcessId, lpProtocolInfo, lpErrno, apiHook));
}

bool
DTHandler::WSPEnumNetworkEvents(SOCKET s, WSAEVENT hEventObject,
                                LPWSANETWORKEVENTS lpNetworkEvents, LPINT lpErrno,
                                APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPEnumNetworkEvents(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  LPWSANETWORKEVENTS lpNetworkEvents = (LPWSANETWORKEVENTS)*va_arg(vList, LPWSANETWORKEVENTS *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPEnumNetworkEvents(s, hEventObject, lpNetworkEvents, lpErrno, apiHook));
}

bool
DTHandler::WSPEventSelect(SOCKET s, WSAEVENT hEventObject, long lNetworkEvents,
                          LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPEventSelect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  long lNetworkEvents = (long)*va_arg(vList, long *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPEventSelect(s, hEventObject, lNetworkEvents, lpErrno, apiHook));
}

bool
DTHandler::WSPGetOverlappedResult(SOCKET s, LPWSAOVERLAPPED lpOverlapped,
                                  LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags,
                                  LPINT lpErrno, APIHook<BOOL> hook) {
  return (0);
}

bool
DTHandler::_WSPGetOverlappedResult(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPDWORD lpcbTransfer = (LPDWORD)*va_arg(vList, LPDWORD *);
  BOOL fWait = (BOOL)*va_arg(vList, BOOL *);
  LPDWORD lpdwFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<BOOL> apiHook((BOOL *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPGetOverlappedResult(s, lpOverlapped, lpcbTransfer, fWait,
                                       lpdwFlags, lpErrno, apiHook));
}

bool
DTHandler::WSPGetPeerName(SOCKET s, struct sockaddr *name, LPINT namelen,
                          LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPGetPeerName(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  LPINT namelen = (LPINT)*va_arg(vList, LPINT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPGetPeerName(s, name, namelen, lpErrno, apiHook));
}

bool
DTHandler::WSPGetSockName(SOCKET s, struct sockaddr *name, LPINT namelen,
                          LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPGetSockName(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  LPINT namelen = (LPINT)*va_arg(vList, LPINT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPGetSockName(s, name, namelen, lpErrno, apiHook));
}

bool
DTHandler::WSPGetSockOpt(SOCKET s, int level, int optname, char *optval, 
                         LPINT optlen, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPGetSockOpt(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int level = (int)*va_arg(vList, int *);
  int optname = (int)*va_arg(vList, int *);
  char *optval = (char *)*va_arg(vList, char **);
  LPINT optlen = (LPINT)*va_arg(vList, LPINT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPGetSockOpt(s, level, optname, optval, optlen, lpErrno, apiHook));
}

bool
DTHandler::WSPGetQOSByName(SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS,
                           LPINT lpErrno, APIHook<BOOL> hook) {
  return (0);
}

bool 
DTHandler::_WSPGetQOSByName(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpQOSName = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPQOS lpQOS = (LPQOS)*va_arg(vList, LPQOS *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<BOOL> apiHook((BOOL *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPGetQOSByName(s, lpQOSName, lpQOS, lpErrno, apiHook));
}

bool
DTHandler::WSPIoctl(SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer,
                    DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                    LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped,
                    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                    LPWSATHREADID lpThreadId, LPINT lpErrno,
                    APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPIoctl(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  DWORD dwIoControlCode = (DWORD)*va_arg(vList, DWORD *);
  LPVOID lpvInBuffer = (LPVOID)*va_arg(vList, LPVOID *);
  DWORD cbInBuffer = (DWORD)*va_arg(vList, DWORD *);
  LPVOID lpvOutBuffer = (LPVOID)*va_arg(vList, LPVOID *);
  DWORD cbOutBuffer = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpcbBytesReturned = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPIoctl(s, dwIoControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer,
                         cbOutBuffer, lpcbBytesReturned, lpOverlapped,
                          lpCompletionRoutine, lpThreadId, lpErrno, apiHook));
}

bool
DTHandler::WSPJoinLeaf(SOCKET s, const struct sockaddr *name, int namelen,
                       LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS,
                       LPQOS lpGQOS, DWORD dwFlags, LPINT lpErrno,
                       APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSPJoinLeaf(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int namelen = (int)*va_arg(vList, int *);
  LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
  LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPJoinLeaf(s, name, namelen, lpCallerData, lpCalleeData,
                            lpSQOS, lpGQOS, dwFlags, lpErrno, apiHook));
}

bool
DTHandler::WSPListen(SOCKET s, int backlog, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPListen(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int backlog = (int)*va_arg(vList, int *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPListen(s, backlog, lpErrno, apiHook));
}

bool
DTHandler::WSPRecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                   LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                   LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   LPWSATHREADID lpThreadId, LPINT lpErrno,
                   APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPRecv(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPRecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                        lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno, apiHook));
}

bool
DTHandler::WSPRecvDisconnect(SOCKET s, LPWSABUF lpInboundDisconnectData,
                             LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPRecvDisconnect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpInboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPRecvDisconnect(s, lpInboundDisconnectData, lpErrno, apiHook));
}

bool
DTHandler::WSPRecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                       LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                       struct sockaddr *lpFrom, LPINT lpFromlen,
                       LPWSAOVERLAPPED lpOverlapped,
                       LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                       LPWSATHREADID lpThreadId, LPINT lpErrno,
                       APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPRecvFrom(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
  struct sockaddr *lpFrom = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
  LPINT lpFromlen = (LPINT)*va_arg(vList, LPINT *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPRecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                            lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine,
                            lpThreadId, lpErrno, apiHook));
}

bool
DTHandler::WSPSelect(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, const struct timeval *timeout,
                     LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPSelect(APIHook<void> hook, va_list vList) {
  int nfds = (int)*va_arg(vList, int *);
  fd_set *readfds = (fd_set *)*va_arg(vList, fd_set **);
  fd_set *writefds = (fd_set *)*va_arg(vList, fd_set **);
  fd_set *exceptfds = (fd_set *)*va_arg(vList, fd_set **);
  const struct timeval *timeout = (const struct timeval *)*va_arg(vList, const struct timeval **);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPSelect(nfds, readfds, writefds, exceptfds, timeout, lpErrno, apiHook));
}

bool
DTHandler::WSPSend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                   LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                   LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   LPWSATHREADID lpThreadId, LPINT lpErrno,
                   APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPSend(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPSend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                        lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno, apiHook));
}

bool
DTHandler::WSPSendDisconnect(SOCKET s, LPWSABUF lpOutboundDisconnectData,
                             LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPSendDisconnect(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpOutboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPSendDisconnect(s, lpOutboundDisconnectData, lpErrno, apiHook));
}

bool
DTHandler::WSPSendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                     LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                     const struct sockaddr *lpTo, int iTolen,
                     LPWSAOVERLAPPED lpOverlapped,
                     LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                     LPWSATHREADID lpThreadId, LPINT lpErrno,
                     APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPSendTo(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
  DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  const struct sockaddr *lpTo = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
  int iTolen = (int)*va_arg(vList, int *);
  LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
  LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPSendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                          lpTo, iTolen, lpOverlapped, lpCompletionRoutine,
                          lpThreadId, lpErrno, apiHook));
}

bool
DTHandler::WSPSetSockOpt(SOCKET s, int level, int optname, const char *optval,
                         int optlen, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPSetSockOpt(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int level = (int)*va_arg(vList, int *);
  int optname = (int)*va_arg(vList, int *);
  const char *optval = (const char *)*va_arg(vList, const char **);
  int optlen = (int)*va_arg(vList, int *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPSetSockOpt(s, level, optname, optval, optlen, lpErrno, apiHook));
}

bool
DTHandler::WSPShutdown(SOCKET s, int how, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPShutdown(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  int how = (int)*va_arg(vList, int *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPShutdown(s, how, lpErrno, apiHook));
}

bool
DTHandler::WSPSocket(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo,
                     GROUP g, DWORD dwFlags, LPINT lpErrno, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WSPSocket(APIHook<void> hook, va_list vList) {
  int af = (int)*va_arg(vList, int *);
  int type = (int)*va_arg(vList, int *);
  int protocol = (int)*va_arg(vList, int *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  GROUP g = (GROUP)*va_arg(vList, GROUP *);
  DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPSocket(af, type, protocol, lpProtocolInfo, g, dwFlags, lpErrno, apiHook));
}

bool
DTHandler::WSPStartup(WORD wVersionRequested, LPWSPDATA lpWSPData,
                      LPWSAPROTOCOL_INFOW lpProtocolInfo, WSPUPCALLTABLE UpcallTable,
                      LPWSPPROC_TABLE lpProcTable, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPStartup(APIHook<void> hook, va_list vList) {
  WORD wVersionRequested = (WORD)*va_arg(vList, WORD *);
  LPWSPDATA lpWSPData = (LPWSPDATA)*va_arg(vList, LPWSPDATA *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  WSPUPCALLTABLE UpcallTable = (WSPUPCALLTABLE)*va_arg(vList, WSPUPCALLTABLE *);
  LPWSPPROC_TABLE lpProcTable = (LPWSPPROC_TABLE)*va_arg(vList, LPWSPPROC_TABLE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPStartup(wVersionRequested, lpWSPData, lpProtocolInfo,
                           UpcallTable, lpProcTable, apiHook));
}

bool
DTHandler::WPUCloseEvent(WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> hook) {
  return (0);
}

bool
DTHandler::_WPUCloseEvent(APIHook<void> hook, va_list vList) {
  WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<BOOL> apiHook((BOOL *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUCloseEvent(hEvent, lpErrno, apiHook));
}

bool
DTHandler::WPUCloseSocketHandle(SOCKET s, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WPUCloseSocketHandle(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUCloseSocketHandle(s, lpErrno, apiHook));
}

bool
DTHandler::WPUCreateEvent(LPINT lpErrno, APIHook<WSAEVENT> hook) {
  return (0);
}

bool
DTHandler::_WPUCreateEvent(APIHook<void> hook, va_list vList) {
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<WSAEVENT> apiHook((WSAEVENT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUCreateEvent(lpErrno, apiHook));
}

bool
DTHandler::WPUCreateSocketHandle(DWORD dwCatalogEntryId, DWORD dwContext,
                                 LPINT lpErrno, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WPUCreateSocketHandle(APIHook<void> hook, va_list vList) {
  DWORD dwCatalogEntryId = (DWORD)*va_arg(vList, DWORD *);
  DWORD dwContext = (DWORD)*va_arg(vList, DWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUCreateSocketHandle(dwCatalogEntryId, dwContext, lpErrno, apiHook));
}

bool
DTHandler::WSCDeinstallProvider(LPGUID lpProviderId, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCDeinstallProvider(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCDeinstallProvider(lpProviderId, lpErrno, apiHook));
}

bool
DTHandler::WSCInstallProvider(const LPGUID lpProviderId, const LPWSTR lpszProviderDllPath,
                              const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
                              DWORD dwNumberOfEntries, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCInstallProvider(APIHook<void> hook, va_list vList) {
  const LPGUID lpProviderId = (const LPGUID)*va_arg(vList, const LPGUID *);
  const LPWSTR lpszProviderDllPath = (const LPWSTR)*va_arg(vList, const LPWSTR *);
  const LPWSAPROTOCOL_INFOW lpProtocolInfoList = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCInstallProvider(lpProviderId, lpszProviderDllPath, lpProtocolInfoList,
                                   dwNumberOfEntries, lpErrno, apiHook));
}

bool
DTHandler::WPUModifyIFSHandle(DWORD dwCatalogEntryId, SOCKET ProposedHandle,
                              LPINT lpErrno, APIHook<SOCKET> hook) {
  return (0);
}

bool
DTHandler::_WPUModifyIFSHandle(APIHook<void> hook, va_list vList) {
  DWORD dwCatalogEntryId = (DWORD)*va_arg(vList, DWORD *);
  SOCKET ProposedHandle = (SOCKET)*va_arg(vList, SOCKET *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<SOCKET> apiHook((SOCKET *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUModifyIFSHandle(dwCatalogEntryId, ProposedHandle, lpErrno, apiHook));
}

bool
DTHandler::WPUQueryBlockingCallback(DWORD dwCatalogEntryId,
                                    LPBLOCKINGCALLBACK *lplpfnCallback,
                                    LPDWORD lpdwContext, LPINT lpErrno,
                                    APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WPUQueryBlockingCallback(APIHook<void> hook, va_list vList) {
  DWORD dwCatalogEntryId = (DWORD)*va_arg(vList, DWORD *);
  LPBLOCKINGCALLBACK *lplpfnCallback = (LPBLOCKINGCALLBACK *)*va_arg(vList, LPBLOCKINGCALLBACK **);
  LPDWORD lpdwContext = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUQueryBlockingCallback(dwCatalogEntryId, lplpfnCallback, lpdwContext, lpErrno, apiHook));
}

bool
DTHandler::WPUQuerySocketHandleContext(SOCKET s, LPDWORD lpContext,
                                       LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WPUQuerySocketHandleContext(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  LPDWORD lpContext = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUQuerySocketHandleContext(s, lpContext, lpErrno, apiHook));
}

bool
DTHandler::WPUQueueApc(LPWSATHREADID lpThreadId, LPWSAUSERAPC lpfnUserApc,
                       DWORD dwContext, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WPUQueueApc(APIHook<void> hook, va_list vList) {
  LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
  LPWSAUSERAPC lpfnUserApc = (LPWSAUSERAPC)*va_arg(vList, LPWSAUSERAPC *);
  DWORD dwContext = (DWORD)*va_arg(vList, DWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUQueueApc(lpThreadId, lpfnUserApc, dwContext, lpErrno, apiHook));
}

bool
DTHandler::WPUResetEvent(WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> hook) {
  return (0);
}

bool
DTHandler::_WPUResetEvent(APIHook<void> hook, va_list vList) {
  WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<BOOL> apiHook((BOOL *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUResetEvent(hEvent, lpErrno, apiHook));
}

bool
DTHandler::WPUSetEvent(WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> hook) {
  return (0);
}

bool
DTHandler::_WPUSetEvent(APIHook<void> hook, va_list vList) {
  WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<BOOL> apiHook((BOOL *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUSetEvent(hEvent, lpErrno, apiHook));
}

bool
DTHandler::WPUFDIsSet(SOCKET s, FD_SET *set, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WPUFDIsSet(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  FD_SET *set = (FD_SET *)*va_arg(vList, FD_SET **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUFDIsSet(s, set, apiHook));
}

bool
DTHandler::WPUGetProviderPath(LPGUID lpProviderId, LPWSTR lpszProviderDllPath,
                              LPINT lpProviderDllPathLen, LPINT lpErrno,
                              APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WPUGetProviderPath(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSTR lpszProviderDllPath = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPINT lpProviderDllPathLen = (LPINT)*va_arg(vList, LPINT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUGetProviderPath(lpProviderId, lpszProviderDllPath, lpProviderDllPathLen,
                                   lpErrno, apiHook));
}

bool
DTHandler::WPUPostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, APIHook<BOOL> hook) {
  return (0);
}

bool
DTHandler::_WPUPostMessage(APIHook<void> hook, va_list vList) {
  HWND hWnd = (HWND)*va_arg(vList, HWND *);
  UINT Msg = (UINT)*va_arg(vList, UINT *);
  WPARAM wParam = (WPARAM)*va_arg(vList, WPARAM *);
  LPARAM lParam = (LPARAM)*va_arg(vList, LPARAM *);
  APIHook<BOOL> apiHook((BOOL *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUPostMessage(hWnd, Msg, wParam, lParam, apiHook));
}

bool
DTHandler::__WSAFDIsSet(SOCKET s, FD_SET *set, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::___WSAFDIsSet(APIHook<void> hook, va_list vList) {
  SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
  FD_SET *set = (FD_SET *)*va_arg(vList, FD_SET **);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WPUFDIsSet(s, set, apiHook));
}

bool
DTHandler::WSCEnumProtocols(LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                            LPDWORD lpdwBufferLength, LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCEnumProtocols(APIHook<void> hook, va_list vList) {
  LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
  LPWSAPROTOCOL_INFOW lpProtocolBuffer = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCEnumProtocols(lpiProtocols, lpProtocolBuffer, lpdwBufferLength,
                                 lpErrno, apiHook));
}

bool
DTHandler::WSAAddressToStringA(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                               LPWSAPROTOCOL_INFOA lpProtocolInfo, OUT LPTSTR lpszAddressString,
                               IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAAddressToStringA(APIHook<void> hook, va_list vList) {
  LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  LPTSTR lpszAddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
  LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAddressToStringA(lpsaAddress, dwAddressLength, lpProtocolInfo,
                                    lpszAddressString, lpdwAddressStringLength, apiHook));
}

bool
DTHandler::WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                               LPWSAPROTOCOL_INFOW lpProtocolInfo, OUT LPTSTR lpszAddressString,
                               IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAAddressToStringW(APIHook<void> hook, va_list vList) {
  LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPTSTR lpszAddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
  LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAAddressToStringW(lpsaAddress, dwAddressLength, lpProtocolInfo,
                                    lpszAddressString, lpdwAddressStringLength, apiHook));
}

bool
DTHandler::WSAStringToAddressA(LPTSTR AddressString, INT AddressFamily,
                               LPWSAPROTOCOL_INFOA lpProtocolInfo, LPSOCKADDR lpAddress,
                               LPINT lpAddressLength, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAStringToAddressA(APIHook<void> hook, va_list vList) {
  LPTSTR AddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
  INT AddressFamily = (INT)*va_arg(vList, INT *);
  LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
  LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAStringToAddressA(AddressString, AddressFamily, lpProtocolInfo,
                                    lpAddress, lpAddressLength, apiHook));
}

bool
DTHandler::WSAStringToAddressW(LPTSTR AddressString, INT AddressFamily,
                               LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                               LPINT lpAddressLength, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAStringToAddressW(APIHook<void> hook, va_list vList) {
  LPTSTR AddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
  INT AddressFamily = (INT)*va_arg(vList, INT *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAStringToAddressW(AddressString, AddressFamily, lpProtocolInfo,
                                    lpAddress, lpAddressLength, apiHook));
}

bool
DTHandler::WSALookupServiceBeginA(LPWSAQUERYSETA lpqsRestrictions, DWORD dwControlFlags,
                                  LPHANDLE lphLookup, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSALookupServiceBeginA(APIHook<void> hook, va_list vList) {
  LPWSAQUERYSETA lpqsRestrictions = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  LPHANDLE lphLookup = (LPHANDLE)*va_arg(vList, LPHANDLE *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSALookupServiceBeginA(lpqsRestrictions, dwControlFlags, lphLookup, apiHook));
}

bool
DTHandler::WSALookupServiceBeginW(LPWSAQUERYSETW lpqsRestrictions, DWORD dwControlFlags,
                                  LPHANDLE lphLookup, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSALookupServiceBeginW(APIHook<void> hook, va_list vList) {
  LPWSAQUERYSETW lpqsRestrictions = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  LPHANDLE lphLookup = (LPHANDLE)*va_arg(vList, LPHANDLE *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSALookupServiceBeginW(lpqsRestrictions, dwControlFlags, lphLookup, apiHook));
}

bool
DTHandler::WSALookupServiceNextA(HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                 LPWSAQUERYSETA lpqsResults, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSALookupServiceNextA(APIHook<void> hook, va_list vList) {
  HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAQUERYSETA lpqsResults = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSALookupServiceNextA(hLookup, dwControlFlags, lpdwBufferLength,
                                      lpqsResults, apiHook));
}

bool
DTHandler::WSALookupServiceNextW(HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                 LPWSAQUERYSETW lpqsResults, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSALookupServiceNextW(APIHook<void> hook, va_list vList) {
  HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAQUERYSETW lpqsResults = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSALookupServiceNextW(hLookup, dwControlFlags, lpdwBufferLength,
                                      lpqsResults, apiHook));
}

bool
DTHandler::WSALookupServiceEnd(HANDLE hLookup, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSALookupServiceEnd(APIHook<void> hook, va_list vList) {
  HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSALookupServiceEnd(hLookup, apiHook));
}

bool
DTHandler::WSAGetAddressByNameA(LPSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                                DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                                LPWSAQUERYSETA lpqsResults, DWORD dwResolution,
                                LPSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                                APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetAddressByNameA(APIHook<void> hook, va_list vList) {
  LPSTR lpszServiceInstanceName = (LPSTR)*va_arg(vList, LPSTR *);
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAQUERYSETA lpqsResults = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);
  DWORD dwResolution = (DWORD)*va_arg(vList, DWORD *);
  LPSTR lpszAliasBuffer = (LPSTR)*va_arg(vList, LPSTR *);
  LPDWORD lpdwAliasBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetAddressByNameA(lpszServiceInstanceName, lpServiceClassId, dwNameSpace,
                                     lpdwBufferLength, lpqsResults, dwResolution,
                                     lpszAliasBuffer, lpdwAliasBufferLength, apiHook));
}

bool
DTHandler::WSAGetAddressByNameW(LPSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                                DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                                LPWSAQUERYSETW lpqsResults, DWORD dwResolution,
                                LPSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                                APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetAddressByNameW(APIHook<void> hook, va_list vList) {
  LPSTR lpszServiceInstanceName = (LPSTR)*va_arg(vList, LPSTR *);
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAQUERYSETW lpqsResults = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  DWORD dwResolution = (DWORD)*va_arg(vList, DWORD *);
  LPSTR lpszAliasBuffer = (LPSTR)*va_arg(vList, LPSTR *);
  LPDWORD lpdwAliasBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetAddressByNameW(lpszServiceInstanceName, lpServiceClassId, dwNameSpace,
                                     lpdwBufferLength, lpqsResults, dwResolution,
                                     lpszAliasBuffer, lpdwAliasBufferLength, apiHook));
}

bool
DTHandler::WSAInstallServiceClassA(LPWSASERVICECLASSINFOA lpServiceClassInfo, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAInstallServiceClassA(APIHook<void> hook, va_list vList) {
  LPWSASERVICECLASSINFOA lpServiceClassInfo = (LPWSASERVICECLASSINFOA)*va_arg(vList, LPWSASERVICECLASSINFOA *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAInstallServiceClassA(lpServiceClassInfo, apiHook));
}

bool
DTHandler::WSAInstallServiceClassW(LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAInstallServiceClassW(APIHook<void> hook, va_list vList) {
  LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAInstallServiceClassW(lpServiceClassInfo, apiHook));
}

bool
DTHandler::WSASetServiceA(LPWSAQUERYSETA lpqsRegInfo, WSAESETSERVICEOP essOperation,
                          DWORD dwControlFlags, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSASetServiceA(APIHook<void> hook, va_list vList) {
  LPWSAQUERYSETA lpqsRegInfo = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);
  WSAESETSERVICEOP essOperation = (WSAESETSERVICEOP)*va_arg(vList, LPWSAESETSERVICEOP);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASetServiceA(lpqsRegInfo, essOperation, dwControlFlags, apiHook));
}

bool
DTHandler::WSASetServiceW(LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation,
                          DWORD dwControlFlags, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSASetServiceW(APIHook<void> hook, va_list vList) {
  LPWSAQUERYSETW lpqsRegInfo = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  WSAESETSERVICEOP essOperation = (WSAESETSERVICEOP)*va_arg(vList, LPWSAESETSERVICEOP);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSASetServiceW(lpqsRegInfo, essOperation, dwControlFlags, apiHook));
}

bool
DTHandler::WSARemoveServiceClass(LPGUID lpServiceClassId, APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSARemoveServiceClass(APIHook<void> hook, va_list vList) {
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSARemoveServiceClass(lpServiceClassId, apiHook));
}

bool
DTHandler::WSAGetServiceClassInfoA(LPGUID lpProviderId, LPGUID lpServiceClassId,
                                   LPDWORD lpdwBufferLength, LPWSASERVICECLASSINFOA lpServiceClassInfo,
                                   APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAGetServiceClassInfoA(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSASERVICECLASSINFOA lpServiceClassInfo = (LPWSASERVICECLASSINFOA)*va_arg(vList, LPWSASERVICECLASSINFOA *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetServiceClassInfoA(lpProviderId, lpServiceClassId, lpdwBufferLength,
                                        lpServiceClassInfo, apiHook));
}

bool
DTHandler::WSAGetServiceClassInfoW(LPGUID lpProviderId, LPGUID lpServiceClassId,
                                   LPDWORD lpdwBufferLength, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                   APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAGetServiceClassInfoW(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetServiceClassInfoW(lpProviderId, lpServiceClassId, lpdwBufferLength,
                                        lpServiceClassInfo, apiHook));
}

bool
DTHandler::WSAEnumNameSpaceProvidersA(IN OUT LPDWORD lpdwBufferLength,
                                      OUT LPWSANAMESPACE_INFOA lpnspBuffer,
                                      APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAEnumNameSpaceProvidersA(APIHook<void> hook, va_list vList) {
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSANAMESPACE_INFOA lpnspBuffer = (LPWSANAMESPACE_INFOA)*va_arg(vList, LPWSANAMESPACE_INFOA *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAEnumNameSpaceProvidersA(lpdwBufferLength, lpnspBuffer, apiHook));
}

bool
DTHandler::WSAEnumNameSpaceProvidersW(IN OUT LPDWORD lpdwBufferLength,
                                      OUT LPWSANAMESPACE_INFOW lpnspBuffer,
                                      APIHook<INT> hook) {
  return (0);
}

bool
DTHandler::_WSAEnumNameSpaceProvidersW(APIHook<void> hook, va_list vList) {
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSANAMESPACE_INFOW lpnspBuffer = (LPWSANAMESPACE_INFOW)*va_arg(vList, LPWSANAMESPACE_INFOW *);
  APIHook<INT> apiHook((INT *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAEnumNameSpaceProvidersW(lpdwBufferLength, lpnspBuffer, apiHook));
}

bool
DTHandler::WSAGetServiceClassNameByClassIdA(LPGUID lpServiceClassId, LPSTR lpszServiceClassName,
                                            LPDWORD lpdwBufferLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetServiceClassNameByClassIdA(APIHook<void> hook, va_list vList) {
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  LPSTR lpszServiceClassName = (LPSTR)*va_arg(vList, LPSTR *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetServiceClassNameByClassIdA(lpServiceClassId, lpszServiceClassName,
                                                 lpdwBufferLength, apiHook));
}

bool
DTHandler::WSAGetServiceClassNameByClassIdW(LPGUID lpServiceClassId, LPWSTR lpszServiceClassName,
                                            LPDWORD lpdwBufferLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSAGetServiceClassNameByClassIdW(APIHook<void> hook, va_list vList) {
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSTR lpszServiceClassName = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSAGetServiceClassNameByClassIdW(lpServiceClassId, lpszServiceClassName,
                                                 lpdwBufferLength, apiHook));
}

bool
DTHandler::NSPAddressToString(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString,
                              LPDWORD lpdwAddressStringLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPAddressToString(APIHook<void> hook, va_list vList) {
  LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPWSTR lpszAddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo,
                                   lpszAddressString, lpdwAddressStringLength, apiHook));
}

bool
DTHandler::NSPStringToAddress(LPWSTR AddressString, INT AddressFamily,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                              LPINT lpAddressLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPStringToAddress(APIHook<void> hook, va_list vList) {
  LPWSTR AddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
  INT AddressFamily = (INT)*va_arg(vList, INT *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo,
                                   lpAddress, lpAddressLength, apiHook));
}

bool
DTHandler::NSPLookupServiceBegin(LPGUID lpProviderId, LPWSAQUERYSETW lpqsRestrictions,
                                 LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                 DWORD dwControlFlags, LPHANDLE lphLookup,
                                 APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPLookupServiceBegin(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSAQUERYSETW lpqsRestrictions = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  LPHANDLE lphLookup = (LPHANDLE)*va_arg(vList, LPHANDLE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPLookupServiceBegin(lpProviderId, lpqsRestrictions, lpServiceClassInfo,
                                      dwControlFlags, lphLookup, apiHook));
}

bool
DTHandler::NSPLookupServiceNext(HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                LPWSAQUERYSET lpqsResults, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPLookupServiceNext(APIHook<void> hook, va_list vList) {
  HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAQUERYSET lpqsResults = (LPWSAQUERYSET)*va_arg(vList, LPWSAQUERYSET *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPLookupServiceNext(hLookup, dwControlFlags, lpdwBufferLength,
                                     lpqsResults, apiHook));
}

bool
DTHandler::NSPLookupServiceEnd(HANDLE hLookup, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPLookupServiceEnd(APIHook<void> hook, va_list vList) {
  HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPLookupServiceEnd(hLookup, apiHook));
}

bool
DTHandler::NSPGetAddressByName(LPWSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                               DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                               LPWSAQUERYSETW lpqsResults, DWORD dwResolution,
                               LPWSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                               APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPGetAddressByName(APIHook<void> hook, va_list vList) {
  LPWSTR lpszServiceInstanceName = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSAQUERYSETW lpqsResults = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  DWORD dwResolution = (DWORD)*va_arg(vList, DWORD *);
  LPWSTR lpszAliasBuffer = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPDWORD lpdwAliasBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPGetAddressByName(lpszServiceInstanceName, lpServiceClassId, dwNameSpace,
                                    lpdwBufferLength, lpqsResults, dwResolution,
                                    lpszAliasBuffer, lpdwAliasBufferLength, apiHook));
}

bool
DTHandler::NSPInstallServiceClass(LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                  APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPInstallServiceClass(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPInstallServiceClass(lpProviderId, lpServiceClassInfo, apiHook));
}

bool
DTHandler::NSPSetService(LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                         LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation,
                         DWORD dwControlFlags, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPSetService(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
  LPWSAQUERYSETW lpqsRegInfo = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
  WSAESETSERVICEOP essOperation = (WSAESETSERVICEOP)*va_arg(vList, WSAESETSERVICEOP *);
  DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPSetService(lpProviderId, lpServiceClassInfo, lpqsRegInfo, essOperation,
                              dwControlFlags, apiHook));
}

bool
DTHandler::NSPRemoveServiceClass(IN LPGUID lpProviderId, IN LPGUID lpServiceClassId,
                                 APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPRemoveServiceClass(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPRemoveServiceClass(lpProviderId, lpServiceClassId, apiHook));
}

bool
DTHandler::NSPGetServiceClassInfo(IN LPGUID lpProviderId, IN OUT LPDWORD lpdwBufSize,
                                  IN OUT LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                  APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPGetServiceClassInfo(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPDWORD lpdwBufSize = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPGetServiceClassInfo(lpProviderId, lpdwBufSize, lpServiceClassInfo, apiHook));
}

bool
DTHandler::NSPGetServiceClassNameByClassId(LPGUID lpServiceClassId, LPWSTR lpszServiceClassName,
                                           LPDWORD lpdwBufferLength, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_NSPGetServiceClassNameByClassId(APIHook<void> hook, va_list vList) {
  LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSTR lpszServiceClassName = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->NSPGetServiceClassNameByClassId(lpServiceClassId, lpszServiceClassName,
                                                lpdwBufferLength, apiHook));
}

bool
DTHandler::WSCGetProviderPath(LPGUID lpProviderId, LPWSTR lpszProviderDllPath,
                              LPINT lpProviderDllPathLen, LPINT lpErrno,
                              APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCGetProviderPath(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  LPWSTR lpszProviderDllPath = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPINT lpProviderDllPathLen = (LPINT)*va_arg(vList, LPINT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCGetProviderPath(lpProviderId, lpszProviderDllPath, lpProviderDllPathLen,
                                   lpErrno, apiHook));
}

bool
DTHandler::WSCInstallNameSpace(LPWSTR lpszIdentifier, LPWSTR lpszPathName,
                               DWORD dwNameSpace, DWORD dwVersion,
                               LPGUID lpProviderId, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCInstallNameSpace(APIHook<void> hook, va_list vList) {
  LPWSTR lpszIdentifier = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPWSTR lpszPathName = (LPWSTR)*va_arg(vList, LPWSTR *);
  DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
  DWORD dwVersion = (DWORD)*va_arg(vList, DWORD *);
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCInstallNameSpace(lpszIdentifier, lpszPathName, dwNameSpace,
                                    dwVersion, lpProviderId, apiHook));
}

bool
DTHandler::WSCUnInstallNameSpace(LPGUID lpProviderId, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCUnInstallNameSpace(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCUnInstallNameSpace(lpProviderId, apiHook));
}

bool
DTHandler::WSCEnableNSProvider(LPGUID lpProviderId, BOOL fEnable, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSCEnableNSProvider(APIHook<void> hook, va_list vList) {
  LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
  BOOL fEnable = (BOOL)*va_arg(vList, BOOL *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSCEnableNSProvider(lpProviderId, fEnable, apiHook));
}

bool
DTHandler::WSPAddressToString(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo,
                              LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength,
                              LPINT lpErrno, APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPAddressToString(APIHook<void> hook, va_list vList) {
  LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPWSTR lpszAddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
  LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo, lpszAddressString,
                                   lpdwAddressStringLength, lpErrno, apiHook));
}

bool
DTHandler::WSPStringToAddress(LPWSTR AddressString, INT AddressFamily,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                              LPINT lpAddressLength, LPINT lpErrno,
                              APIHook<int> hook) {
  return (0);
}

bool
DTHandler::_WSPStringToAddress(APIHook<void> hook, va_list vList) {
  LPWSTR AddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
  INT AddressFamily = (INT)*va_arg(vList, INT *);
  LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
  LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
  LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);
  LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);
  APIHook<int> apiHook((int *)hook.rValue(), hook.libName(), hook.preAPI());
  return (this->WSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo, lpAddress,
                                   lpAddressLength, lpErrno, apiHook));
}
