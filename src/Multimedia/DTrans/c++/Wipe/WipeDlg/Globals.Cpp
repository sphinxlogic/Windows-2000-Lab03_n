#include "globals.h"
#include "..\wipedll\wipe_i.c"         // Wipe dll GUID definitions

HWND                g_hDlg          = NULL;
int                 g_nDCWidth      = 0;
int                 g_nDCHeight     = 0;

IDXTransformFactory *g_pTransFact   = NULL;
IDXSurfaceFactory   *g_pSurfFact    = NULL;
IDXSurface          *g_pInSurfA     = NULL;
IDXSurface          *g_pInSurfB     = NULL;
IDXSurface          *g_pOutSurf     = NULL;
IDXTransform        *g_pWipeTrans   = NULL;
IDXEffect           *g_pEffect      = NULL;


