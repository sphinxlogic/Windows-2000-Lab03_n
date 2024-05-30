// Filename  : SocketMon.cpp
// Abstract  : This object is inherited from DTHandler and implements
//             our custom DT Winsock API hooking.
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998.  Microsoft Corporation.
//             All rights reserved.

#include <stdio.h>
#include "SocketMon.hpp"

bool
SocketMonitor::WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData, APIHook<int> hook) {
  char buffer[1024 * 8];
  FillMemory(buffer, sizeof(buffer), 0);
  if (hook.preAPI()) {
    sprintf(buffer,
            "\nWinsock API\t\t: WSAStartup()\n"
            "     Calling library\t\t: %s\n"
            "     Pre-API notify\t\t: Yes\n"
            "Parameter values\t\t:\n"
            "     wVersionRequested\t: %u\n",
            hook.libName(), wVersionRequested);
  } else {
    sprintf(buffer,
            "\nWinsock API\t\t\t: WSAStartup()\n"
            "     Calling library\t\t\t: %s\n"
            "     Pre-API notify\t\t\t: No\n"
            "Reference parameter values\t\t:\n"
            "     lpWSAData->wVersion\t\t: %d\n"
            "     lpWSAData->wHighVersion\t: %d\n"
            "     lpWSAData->iMaxSockets\t\t: %d\n"
            "     lpWSAData->iMaxUdpDg\t\t: %d\n"
            "     lpWSAData->szDescription\t\t: %s\n"
            "     lpWSAData->szSystemStatus\t: %s\n"
            "     lpWSAData->lpVendorInfo\t\t: %s\n"
            "API return value\t\t\t: %d\n",
            hook.libName(), lpWSAData->wVersion, lpWSAData->wHighVersion,
            lpWSAData->iMaxSockets, lpWSAData->iMaxUdpDg, lpWSAData->szDescription,
            lpWSAData->szSystemStatus, lpWSAData->lpVendorInfo, *hook.rValue());
  }
  MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);
  return (false); // don't veto API call
}

bool
SocketMonitor::WSACleanup(APIHook<int> hook) {
  char buffer[1024 * 8];
  FillMemory(buffer, sizeof(buffer), 0);
  if (hook.preAPI()) {
    sprintf(buffer,
            "\nWinsock API\t\t: WSACleanup()\n"
            "     Calling library\t\t: %s\n"
            "     Pre-API notify\t\t: Yes\n",
            hook.libName());
  } else {
    sprintf(buffer,
            "\nWinsock API\t\t: WSACleanup()\n"
            "     Calling library\t\t: %s\n"
            "     Pre-API notify\t\t: %s\n"
            "     API return value\t\t: %d\n",
            hook.libName(), "No", *hook.rValue());
  }
  MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);
  return (false); // don't veto API call
}

bool
SocketMonitor::send(SOCKET s, const char FAR *buf, int len, int flags, APIHook<int> hook) {
  char buffer[1024 * 8];
  FillMemory(buffer, sizeof(buffer), 0);
  if (hook.preAPI()) {
    sprintf(buffer,
            "Winsock API\t\t: send()\n"
            "     Calling library\t\t: %s\n"
            "     Pre-API notify\t\t: Yes\n"
            "Parameter values\t\t:\n"
            "     s\t\t\t: %d\n"
            "     len\t\t\t: %d\n"
            "     flags\t\t\t: %d\n",
            hook.libName(), s, len, flags);
  } else {
    sprintf(buffer,
            "Winsock API\t\t\t: send()\n"
            "     Calling library\t\t\t: %s\n"
            "     Pre-API notify\t\t\t: No\n"
            "     API return value\t\t\t: %d\n",
            hook.libName(), *hook.rValue());
  }
  MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);
  return (false); // don't veto API call
}

bool
SocketMonitor::recv(SOCKET s, char FAR *buf, int len, int flags, APIHook<int> hook) {
  char buffer[1024 * 8];
  FillMemory(buffer, sizeof(buffer), 0);
  if (hook.preAPI()) {
    sprintf(buffer,
            "[DT Hook]\n"
            "\tWinsock API\t\t: recv()\n"
            "     \tCalling library\t\t: %s\n"
            "     \tPre-API notify\t\t: Yes\n"
            "\tParameter values\t:\n"
            "     \ts\t\t\t: %d\n"
            "     \tlen\t\t\t: %d\n"
            "     \tflags\t\t\t: %d\n",
            hook.libName(), s, len, flags);
  } else {
    sprintf(buffer,
            "Winsock API\t\t\t: send()\n"
            "     Calling library\t\t\t: %s\n"
            "     Pre-API notify\t\t\t: No\n"
            "     API return value\t\t\t: %d\n"
            "Reference parameter values:\t:\n",
            hook.libName(), *hook.rValue());
  }
  MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);
  return (false); // don't veto API call
}
