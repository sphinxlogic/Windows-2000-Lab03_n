#ifndef __WIPEDLG_GLOBALS_H__
#define __WIPEDLG_GLOBALS_H__

// System includes
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>

#include <tchar.h>
#include <olectl.h>			// Required for showing property page
#include <crtdbg.h>
#include <comdef.h>

// DXTransform includes
#include <dxtransguid.h>
#include <dxtrans.h>
#include <dxterror.h>
#include <dxbounds.h>
#include <dxhelper.h>
#include "..\wipedll\Wipe.h"           // Wipe dll interface definitions

// App includes
#include "resource.h"
#include "WipeDlg.h"


// *** Global variables (declared in GLOBALS.CPP) ***
extern HWND					g_hDlg;

extern IDXTransformFactory	*g_pTransFact;
extern IDXSurfaceFactory	*g_pSurfFact;
extern IDXSurface			*g_pInSurfA;
extern IDXSurface			*g_pInSurfB;
extern IDXSurface			*g_pOutSurf;
extern IDXTransform			*g_pWipeTrans;
extern IDXEffect			*g_pEffect;

#endif
