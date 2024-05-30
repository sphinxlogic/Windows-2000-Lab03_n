#include "resource.h"

#ifndef GET_WM_COMMAND_ID

#define GET_WM_COMMAND_ID(wp, lp)               (wp)
#define GET_WM_COMMAND_HWND(wp, lp)             (HWND)(LOWORD(lp))
#define GET_WM_COMMAND_CMD(wp, lp)              HIWORD(lp)

#endif

#ifdef WIN32
   #define CBACK  CALLBACK
#else
   #define CBACK  _export CALLBACK
#endif

