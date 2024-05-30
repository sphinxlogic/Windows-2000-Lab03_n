///////////////////////////////////////////////////////////////////////////////////
//globals.cpp : module where all global variable are defined
///////////////////////////////////////////////////////////////////////////////////
#include "globals.h"

 
HWND								g_hWnd;

CComPtr<IDirect3DRM>				g_d3drm;
CComPtr<IDirect3DRM3>				g_d3drm3;
CComPtr<IDirect3DRMFrame3>			g_scene;
CComPtr<IDirect3DRMFrame3>			g_camera;
CComPtr<IDirect3DRMViewport2>		g_viewport;
CComPtr<IDirect3DRMDevice3>			g_device;
CComPtr<IDXTransform>				g_pSomeTrans;
CComPtr<IDirectDrawFactory>			g_pDDrawFact;
CComPtr<IDirectDraw>				g_pDDraw;
CComPtr<IDXTransformFactory>		g_pTransFact;
CComPtr<IDirect3DRMMeshBuilder3>	g_meshbuilder;
CComPtr<IDirect3DRMFrame3>			g_frame;
IDirect3DRMMeshBuilder3*			g_pOutMesh;
CComPtr<IDXEffect>					g_cpEffect;
CComPtr<IDirectDrawClipper>			g_clipper;

D3DCOLORMODEL						g_colormodel;
D3DVALUE							g_meshscale;
D3DRMRENDERQUALITY					g_meshquality;
D3DCOLOR							g_meshcolor;
int									g_iLast_x;
int									g_iLast_y;
char								g_szXFileName[MAX_STRING_SIZE];
UINT								g_uiMousestate;
long								g_lgMousex;
long								g_lgMousey;
BOOL								g_bEndDrag;
BOOL								g_bDrag;
 
 