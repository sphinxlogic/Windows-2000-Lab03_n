#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "GeoTrans.h"
 

extern HWND									g_hWnd;

extern CComPtr<IDirect3DRM>					g_d3drm;
extern CComPtr<IDirect3DRM3>				g_d3drm3;
extern CComPtr<IDirect3DRMFrame3>			g_scene;
extern CComPtr<IDirect3DRMFrame3>			g_camera;
extern CComPtr<IDirect3DRMViewport2>		g_viewport;
extern CComPtr<IDirect3DRMDevice3>			g_device; 
extern CComPtr<IDXTransform>				g_pSomeTrans; 
extern CComPtr<IDirect3DRMMeshBuilder3>		g_meshbuilder;
extern CComPtr<IDirect3DRMFrame3>			g_frame;
extern CComPtr<IDirectDrawFactory>			g_pDDrawFact;
extern CComPtr<IDirectDraw>					g_pDDraw;
extern CComPtr<IDXTransformFactory>			g_pTransFact;
extern IDirect3DRMMeshBuilder3*				g_pOutMesh;
extern CComPtr<IDXEffect>					g_cpEffect;
extern CComPtr<IDirectDrawClipper>			g_clipper;

extern D3DCOLORMODEL						g_colormodel;
extern D3DVALUE								g_meshscale;
extern D3DRMRENDERQUALITY					g_meshquality;
extern D3DCOLOR								g_meshcolor;
extern int									g_iLast_x;
extern int									g_iLast_y;
extern char									g_szXFileName[MAX_STRING_SIZE];

extern BOOL									g_bDrag;
extern UINT									g_uiMousestate;
extern long									g_lgMousex;
extern long									g_lgMousey;
extern BOOL									g_bEndDrag;

#endif

 