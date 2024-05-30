///////////////////////////////////////////////////////////////////////////////////
//
//GeoTrans : a simple demo app on how to use a geometric 3D Transform (with Mesh) 
////////////////////////Copyright Micosoft(c) 1998/////////////////////////////////
// 
//after the window is created This app calls CreateTheD3DRM() and CreateTheTransform()
//to initialize D3DRM and to create the transform factory.
//The global stage is set by calling CreateDevice() and CreateScene().

//* When loading a mesh from the menu these steps are executed:
//- D3DRM loads the mesh with " the LOAD API "; subsequently the mesh is initialized.
//- LoadTrans() is called to set up and display the meshes.
//- Mesh manipulation via the mouse is handled by OnMouseMove(), OnLButtonDown(), and   
//  OnLButtonUP().

//* When Run is selected from the menu RunTrans() calls IDXEffect::put_Progress() 
//and IDXEffect::Execute() repeatedly to display the mesh which is being "transformed".
//
///////////////////////////////////////////////////////////////////////////////////

#include "globals.h"


HINSTANCE hInst;   // current instance

LPCTSTR lpszAppName  = "GeoTrans";
LPCTSTR lpszTitle    = "GeoTrans"; 
 
///////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine, int nCmdShow)
///////////////////////////////////////////////////////////////////////////////////

{
   MSG          msg;
   WNDCLASSEX   wc;
   HRESULT     hr;

   // Register the main application window class.
   //............................................
   wc.style         = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc   = (WNDPROC)WndProc;       
   wc.cbClsExtra    = 0;                      
   wc.cbWndExtra    = 0;                      
   wc.hInstance     = hInstance;              
   wc.hIcon         = LoadIcon( hInstance,lpszAppName); 
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wc.lpszMenuName  = lpszAppName;              
   wc.lpszClassName = lpszAppName;              
   wc.cbSize        = sizeof(WNDCLASSEX);
   wc.hIconSm       = (HICON)LoadImage(wc.hInstance, lpszAppName, 
                            IMAGE_ICON, 16, 16,
                            LR_DEFAULTCOLOR );
    
   RegisterClassEx( &wc );
   hInst = hInstance; 
    
   // initialize COM .
    hr=CoInitialize( NULL ); 
    HandleError( hr, "Failed to CoInitialize()...\n", HE_EXIT, HE_MBOX );

   // Create the main application window.
   //....................................
   g_hWnd = CreateWindow( lpszAppName, 
                        lpszTitle,    
                        WS_OVERLAPPEDWINDOW, 
                        CW_USEDEFAULT, 0, 
                        CW_USEDEFAULT, 0,  
                        NULL,              
                        NULL,              
                        hInstance,         
                        NULL               
                      );
  

   if ( !g_hWnd ) 
      return( FALSE );

   ShowWindow( g_hWnd, nCmdShow ); 
   UpdateWindow( g_hWnd );         
    
    // Initialize D3DRM and transforms variabales
    InitApp();

    // application message loop
    while( GetMessage( &msg, NULL, 0, 0) )   
   {
      TranslateMessage( &msg ); 
      DispatchMessage( &msg );  
   }
    
    // Release all global pointers and uninitialize the COM library
    CleanUp();
    CoUninitialize();
   
    return( msg.wParam ); 
    
}
 
///////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
///////////////////////////////////////////////////////////////////////////////////
{
 
    
    POINT   xPoint;
            

   switch( uMsg )
   {

        case WM_CREATE :
            break;
      
        case WM_ERASEBKGND :
           OnEraseBkgnd();
           InvalidateRect(g_hWnd, NULL, false);
           break;

        case WM_PAINT :
            OnPaint();
            break;

        case WM_SIZE :
            OnSize( LOWORD(lParam), HIWORD(lParam) ); 
            break;
    
        case WM_MOUSEMOVE :
            xPoint.x=LOWORD( lParam );
            xPoint.y=HIWORD( lParam );
            OnMouseMove( wParam, xPoint );
            break;

        case WM_LBUTTONDOWN :
            OnLButtonDown();
            break;

        case WM_LBUTTONUP :
            OnLButtonUp();
            break;

        case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
 
                    case IDM_TEST :
                        // execute the transform
                        RunTrans(); 
                        break;

                    case IDM_LOADMESH :
 
                        // check if the open file dialog succeed .
                        if(OnFileOpen())
                        {   
                            DispInitMsg();
                            LoadTrans(); // if a mesh was selected setup the transform
                            MySetMenuItem( IDM_TEST, true ); // enable the Run menu 
                        }
                        
                        break;
                    
                    case IDM_EXPLODE :
                        // mark the selection 
                        CheckMenuRadioItem( GetMenu(g_hWnd), IDM_EXPLODE, 
                                            IDM_RUFFLE,IDM_EXPLODE, MF_BYCOMMAND );
                        InitSceneVars();
                        PickaTrans(1); // select explode
                        if(g_meshbuilder)
                        {
                            DispInitMsg();
                            LoadTrans();
							InvalidateRect(g_hWnd, NULL, false);
                        }
                        break;

                    case IDM_RUFFLE :
                        CheckMenuRadioItem(GetMenu(g_hWnd), IDM_EXPLODE, 
                                            IDM_RUFFLE,IDM_RUFFLE, MF_BYCOMMAND );
                        InitSceneVars();
                        PickaTrans(2); //select ruffle
                        if(g_meshbuilder)
                        {
                            DispInitMsg();
                            LoadTrans(); // if a mesh was selected setup the transform
							InvalidateRect(g_hWnd, NULL, false);
                        }
                        break;

                    case IDM_EXIT :
                        DestroyWindow( hWnd );
                        break;
                    
                    case IDM_ABOUT :
                        DialogBox( hInst, "AboutBox", hWnd, (DLGPROC)About );
                        break;
              }
              break;
      
      case WM_DESTROY :
              
              PostQuitMessage(0);
              
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}


///////////////////////////////////////////////////////////////////////////////////
void OnPaint() 
///////////////////////////////////////////////////////////////////////////////////
{
        
    LPDIRECT3DRMWINDEVICE   windev=NULL;
    PAINTSTRUCT             ps;
    

    if (GetUpdateRect(g_hWnd, 0, FALSE )==FALSE)
        return;
    
    // display unrelated D3D
    BeginPaint(g_hWnd,&ps);  
    EndPaint(g_hWnd, &ps); 

    if (g_device) 
    {   
        
        if (g_device->QueryInterface(IID_IDirect3DRMWinDevice, (void**)&windev)==0)
        {   
            // use the D3D API HandlePaint to display the mesh .
            BeginPaint(g_hWnd,&ps);  
            if (windev->HandlePaint(ps.hdc)!=0)
            {
                windev->Release();
                windev=NULL;
            } 
            if((g_d3drm3)&&(g_meshbuilder))
            {
                g_d3drm3->Tick( D3DVALUE(0) );
                
            }
            EndPaint(g_hWnd, &ps);  
        } 
    
    } 
}

///////////////////////////////////////////////////////////////////////////////////
void OnEraseBkgnd() 
///////////////////////////////////////////////////////////////////////////////////
//paint the background with black
//
{
    COLORREF    bgcolor;
    HBRUSH      hBr;
    LOGBRUSH    lb;
    RECT        rc;
    HDC         hDC;
 
    if (g_scene)
    {
        D3DCOLOR scenecolor=g_scene->GetSceneBackground();
        bgcolor=D3DCOLOR_2_COLORREF( scenecolor );
    }
    else
    {
        bgcolor=RGB( 0, 0, 0 );
    }

    lb.lbStyle=BS_SOLID;    
    lb.lbColor=bgcolor;     

    hBr=CreateBrushIndirect( &lb );
    hDC=GetDC( g_hWnd );
     

    SelectObject( hDC, hBr );
    GetClientRect( g_hWnd, &rc );
    PatBlt( hDC,rc.left, rc.top, rc.right, rc.bottom, PATCOPY );
    ReleaseDC( g_hWnd, hDC );
    DeleteObject( hBr );
  
     
}
 
/////////////////////////////////////////////////////////////////////////////////// 
void OnSize(int iCx, int iCy)
///////////////////////////////////////////////////////////////////////////////////
// adjust the viewport and scene when resizing
//
{
    int                 iWidth = iCx;
    int                 iHeight = iCy;
    int                 iOldDither;
    int                 iOldShades;
    int                 iViewWidth;
    int                 iViewHeight;
    int                 iDevWidth;
    int                 iDevHeight;
    HRESULT             hr;
    D3DRMRENDERQUALITY  old_quality;
     

    if ((!g_device)||(!g_viewport))
        return;

    

    if (iWidth && iHeight)  // if viewport gets dimension
    {
        iViewWidth  = g_viewport->GetWidth();
        iViewHeight = g_viewport->GetHeight();
        iDevWidth   = g_device->GetWidth();
        iDevHeight  = g_device->GetHeight();

        if (iViewWidth == iWidth && iViewHeight == iHeight)
            return;

        iOldDither  = g_device->GetDither();
        old_quality = g_device->GetQuality();
        iOldShades  = g_device->GetShades();
        
        //release device to recreate it
        g_device.Release();
         
        hr=g_d3drm3->CreateDeviceFromClipper( g_clipper, NULL, iWidth, iHeight, &g_device );
        HandleError( hr, "Failed to CreateDeviceFromClipper in OnSize()...\n", HE_EXIT, HE_MBOX );
        
        // restore device properties
        g_device->SetDither( iOldDither );
        g_device->SetQuality( old_quality );
        g_device->SetShades( iOldShades );

        iWidth = g_device->GetWidth();
        iHeight = g_device->GetHeight();
        
        // release viewport to recreate it
        g_viewport.Release();

        hr=g_d3drm3->CreateViewport( g_device, g_camera,0, 0, iWidth, iHeight, &g_viewport );
        HandleError( hr, "Failed to CreateViewport in OnSize()...\n", HE_EXIT,  HE_MBOX );
        
        // invalidate the client area to cause repaint
        UpdateWindow( g_hWnd );
        
    }
}

///////////////////////////////////////////////////////////////////////////////////
void HandleError(HRESULT hr,LPCTSTR szErrorMessage,bool bExitApp,short nHEFlag)
///////////////////////////////////////////////////////////////////////////////////
//
//Display the argument string in the debugger, message box or cause an assertion.
//cause  exit app if requested , the flags for this fuction  are defined in geotrans.h
//
{
    char szBuffer[MAX_STRING_SIZE];
 

    if(FAILED(hr))
    {   
        wsprintf( szBuffer, "%s line=%d, hr=%x", szErrorMessage, __LINE__, hr );
        
        switch(nHEFlag)
        {
        case HE_DEBUG :
            OutputDebugString( szBuffer );
            break;

        case HE_MBOX :
            MessageBox( g_hWnd, szBuffer, "Error", MB_OK | MB_ICONERROR );
            break;

        case HE_ASSERT :
            assert( SUCCEEDED(hr) );
            break;
 
        }//end switch
        
        if (bExitApp)
        {
           PostMessage( g_hWnd, WM_DESTROY, 0, 0 );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////
void DispInitMsg()
///////////////////////////////////////////////////////////////////////////////////
// display a message while waiting to initialize a transform
//
{

    HDC hDC;

    hDC=GetDC( g_hWnd );
    SetTextColor( hDC, RGB(255,0,0) ); //text color : red
    TextOut(hDC,300,200,"Initializing Transform...", 25);
    ReleaseDC( g_hWnd, hDC );

}

///////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK About( HWND hDlg,           
                        UINT message,        
                        WPARAM wParam,       
                        LPARAM lParam)
///////////////////////////////////////////////////////////////////////////////////
{
   switch (message) 
   {
       case WM_INITDIALOG: 
               return (TRUE);

       case WM_COMMAND:                              
               if (   LOWORD(wParam) == IDOK         
                   || LOWORD(wParam) == IDCANCEL)    
               {
                       EndDialog( hDlg, TRUE );        
                       return ( TRUE );
               }
               break;
   }

   return (FALSE); 
}
///////////////////////////////////////////////////////////////////////////////////
void InitApp()
///////////////////////////////////////////////////////////////////////////////////
{
    // Prepare the D3D scene 
    if(CreateTheD3DRM())
	{
     CreateTheTransform();
     InitGlobalvars();
     CreateDevice();
     InitSceneVars();
     CreateScene();

     // disable the Run menu because mesh still not loaded .
     MySetMenuItem(IDM_TEST, false);
    }
}

///////////////////////////////////////////////////////////////////////////////////
void CleanUp()
///////////////////////////////////////////////////////////////////////////////////
//
//Release all global pointers
//
{
    g_d3drm.Release();
    g_d3drm3.Release();
    g_scene.Release();
    g_camera.Release();
    g_viewport.Release();
    g_device.Release();
    g_pSomeTrans.Release();
    g_pDDrawFact.Release();
    g_pDDraw.Release();
    g_pTransFact.Release();
    g_meshbuilder.Release();
    g_frame.Release();
    g_cpEffect.Release();
    g_clipper.Release();
    if(g_pOutMesh)
    {g_pOutMesh->Release();}

}   

///////////////////////////////////////////////////////////////////////////////////
void MySetMenuItem(UINT MenuID, bool bActive)
///////////////////////////////////////////////////////////////////////////////////
// enable or disable a menu
//
{
    HMENU   hMenu;      
 

    hMenu=GetMenu( g_hWnd );
 
    if(bActive)
    {
        EnableMenuItem( hMenu , MenuID, MFS_ENABLED | MF_BYCOMMAND );
    }else
        {
            EnableMenuItem( hMenu , MenuID, MFS_GRAYED | MF_BYCOMMAND );
        }
    
    DrawMenuBar( g_hWnd );
}
