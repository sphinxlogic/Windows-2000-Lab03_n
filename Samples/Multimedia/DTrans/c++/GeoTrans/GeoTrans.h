#ifndef __GEOTRANS_H__
#define __GEOTRANS_H__

///////////////////////////////////////////////////////////////////////////////////
//*****************Includes*******************
///////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <crtdbg.h>
#include <math.h>  
#include <time.h>
#include <string.h>
#include <assert.h>
#include <tchar.h>
#include <stdlib.h>
#include "resource.h"
#include <DXTMsftGUID.h>
#include <DXTMsft.h>
#include <DDrawEx.h>
#include <atlbase.h>
#include <d3drmwin.h>

///////////////////////////////////////////////////////////////////////////////////
//*******************defines******************
///////////////////////////////////////////////////////////////////////////////////
#define MAX_STRING_SIZE 250

// flags for the HandleError Function
#define HE_EXIT			TRUE
#define HE_NO_EXIT		FALSE
#define HE_DEBUG		1
#define HE_MBOX			2
#define HE_ASSERT		3
 
///////////////////////////////////////////////////////////////////////////////////
//**************functions prototypes**********
/////////////////////////////////////////////////////////////////////////////////// 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);
HRESULT LoadTrans(void);
D3DVALUE ScaleMesh( IDirect3DRMMeshBuilder3* mesh, D3DVALUE dim);
COLORREF D3DCOLOR_2_COLORREF(D3DCOLOR d3dclr);
BOOL OnFileOpen(void);

void InitApp(void);
bool CreateTheD3DRM(void); 
void OnEraseBkgnd(void);
void CreateDevice(void);
void CreateScene(void); 
void OnSize(int cx, int cy);
void OnMouseMove( UINT state, POINT point );
void OnLButtonDown(void);
void OnLButtonUp(void);
void UpdateFrame(IDirect3DRMFrame3* someframe, void*, D3DVALUE);
void InitMesh(LPCTSTR filename);
void InitSceneVars(void);
void RunTrans(void);
void CreateTheTransform(void);
void InitGlobalvars(void);
void OnPaint(void);
void HandleError(HRESULT hr,LPCTSTR szErrorMessage,bool bExitApp,short nHEFlag);
void RestoreDefaults(void);
void PickaTrans(int CaseID);
void DispInitMsg(void); 
void CleanUp(void);
void MySetMenuItem(UINT MenuID, bool bActive);

#endif 
 

