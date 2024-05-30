//-----------------------------------------------------------------------------
// File: DXSurf1.CPP
//
// Desc: DXSurface example program 1.  Allows the user to load an image onto a 
//       DXSurface and then blits it to a second, primary DXSurface.
//
// Copyright (c) 1995-1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include <windows.h>
#include <initguid.h>
#include <stdio.h>
#include <stdarg.h>
#include <dxtrans.h>  // DXSurface header file
#include <dxtguid.c>  // Guids for DXSurfaces
#include <dxterror.h> // DXSurface error codes
#include <dxbounds.h> // Contains the CDXDVec and CDXDBnds classes used in this program
#include "resource.h"

//-----------------------------------------------------------------------------
// Local definitions
//-----------------------------------------------------------------------------
#define NAME                "DXSurf1"
#define TITLE               "DXSurface Example 1"
#define SAFE_RELEASE( ptr )         \
{                                   \
        if (ptr) ptr->Release();    \
        ptr=NULL;                   \
}
//-----------------------------------------------------------------------------
// Global data
//-----------------------------------------------------------------------------
IDXSurfaceFactory*      g_pSurfFact                 = NULL;
IDXSurface*             g_pDXImageSurf              = NULL;
IDXSurface*             g_pPrimaryDXSurf            = NULL;
BOOL                    g_bActive                   = FALSE;

//-----------------------------------------------------------------------------
// Name: ReleaseAllObjects()
// Desc: Finished with all objects we use; release them
//-----------------------------------------------------------------------------
static void ReleaseAllObjects( void )
{
    SAFE_RELEASE( g_pDXImageSurf )
    SAFE_RELEASE( g_pPrimaryDXSurf )
    SAFE_RELEASE( g_pSurfFact )
}

//-----------------------------------------------------------------------------
// Name: InitFail()
// Desc: This function is called if an initialization function fails
//-----------------------------------------------------------------------------
HRESULT InitFail( HWND hWnd, HRESULT hr, LPCTSTR szError,... )
{
    char                        szBuff[128];
    va_list                     vl;

    g_bActive = FALSE;
    va_start( vl, szError );
    vsprintf( szBuff, szError, vl );
    ReleaseAllObjects();
    MessageBox( hWnd, szBuff, TITLE, MB_OK );
    DestroyWindow( hWnd );
    va_end( vl );
    return hr;
}

//-----------------------------------------------------------------------------
// Name: OnFileOpen()
// Desc: This function pops the Open File Dialog and retrieves a string for
//       the call to LoadImage.
//-----------------------------------------------------------------------------
BOOL OnFileOpen( HWND hWnd, LPSTR szName )
{
    OPENFILENAME    ofn;

    // Initialize the OPENFILENAME structure.
    memset( &ofn, 0, sizeof( OPENFILENAME ) );
    ofn.lStructSize      = sizeof( OPENFILENAME );
    ofn.hwndOwner        = hWnd;
    ofn.lpstrFilter      = "Image files (*.png;*.jpg;*.bmp)\0*.png;*.jpg;*.bmp\0All files {*.*}\0*.*\0\0";                          
    ofn.lpstrFile        = szName;
    ofn.lpstrInitialDir  = "c:\\dxmedia\\samples\\multimedia\\media\\image";
    ofn.nMaxFile         = 256;
    ofn.Flags            = OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt      = "png";

    // Create the open file dialog.
    return GetOpenFileName( &ofn );    
}

//-----------------------------------------------------------------------------
// Name: RestoreLostSurfaces()
// Desc: Restores the underlying DirectDraw surface if the display memory is
//       lost to another application . This can happen if the user presses
//       Alt-Tab (see DirectDraw SDK for more information on this). We only need
//       to worry about the primary surface since its a video memory surface. 
//       The other DXSurface (g_pDXImageSurf) which contains the image is a 
//       system memory surface since that is the default DXSurface type.
//-----------------------------------------------------------------------------
void RestoreLostSurfaces( HWND hWnd )
{
    HRESULT                 hr;
    IDirectDrawSurface2*    pUnderlyingPrimaryDDSurf    = NULL;

    // Get the underlying DirectDraw surface for the Primary DXSurface
    hr = g_pPrimaryDXSurf->GetDirectDrawSurface( IID_IDirectDrawSurface, 
                                            (void**)&pUnderlyingPrimaryDDSurf );
    if( SUCCEEDED( hr ) )
    {
        // Restore any potentially lost contents from window swapping
        if( pUnderlyingPrimaryDDSurf->IsLost() == DDERR_SURFACELOST )
        {        
            hr = pUnderlyingPrimaryDDSurf->Restore();
        }
        
        // Release the Direct Draw Surface
        pUnderlyingPrimaryDDSurf->Release();
    }
    
    if ( FAILED( hr ) )
        InitFail( hWnd, hr, "RestoreLostSurfaces() failed" );
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
    HRESULT         hr = S_OK;
    HDC             hdcWnd;
    PAINTSTRUCT     ps;
    RECT            rect;
    POINT           point;
    char            szError[256] = "";
    char            szFileName[256] = "";
    WCHAR           szWFileName[256];
    
    switch( iMsg )
    {
    case WM_PAINT:
        hdcWnd = BeginPaint( hWnd, &ps );
        
        GetClientRect( hWnd, &rect );
        SetBkMode( hdcWnd, TRANSPARENT );
            
        // Render the DXSurface
        if( g_bActive )
        {
            point.x = rect.top;
            point.y = rect.left;
            ClientToScreen(hWnd, &point);

            // Initialize the placement vector for the BitBlt with the top left corner
            // coordinates of the window.
            CDXDVec   vPlacement( point.x, point.y, 0, 0 );

            // Set the portion of the primary surface that we want to BitBlt to to be
            // the size of the window
            CDXDBnds  PortionBnds( rect.right, rect.bottom );
            
            // Use IDXSurfaceFactory::BitBlt to blit the eagle (g_pDXImageSurf) to the Primary
            // Surface (g_pPrimaryDXSurf)
            hr = g_pSurfFact->BitBlt( g_pPrimaryDXSurf, &vPlacement, g_pDXImageSurf, 
                                                &PortionBnds, DXBOF_DO_OVER );
            if ( FAILED( hr ) )
                return InitFail( hWnd, hr, "BitBlt failed" );

            DrawText( hdcWnd, "DXSurface Sample 1. Demonstrates DXSurface BitBlt to a "
                      "Primary Surface.", -1, &rect, 
                      DT_CENTER | DT_BOTTOM | DT_SINGLELINE );
        }
        else
        {
            DrawText( hdcWnd, "DXSurface Sample 1. Please open an image file.", -1, &rect, 
                      DT_CENTER | DT_BOTTOM | DT_SINGLELINE );
        }
                
        EndPaint( hWnd, &ps );
        break;

    case WM_ACTIVATE:
        {
            if( g_bActive )
            {
                // If someone switches between windows using Alt-Tab the contents of the
                // underlying DDraw Surfaces may get lost. This function restores them.
                RestoreLostSurfaces( hWnd );
            }
            break;
        }

    case WM_COMMAND :
        switch( LOWORD( wParam ) )
        {
            case IDM_OPEN:
                // Check if the open file dialog succeed .
                if( OnFileOpen( hWnd, szFileName ) )
                {   
                    // Convert the szFileName string to a Unicode string
                    mbstowcs( szWFileName, szFileName, 256 );
                    
                    // Release any previous image surfaces
                    SAFE_RELEASE( g_pDXImageSurf );

                    // Call load image which creates a DXSurface with an image on it
                    hr = g_pSurfFact->LoadImage( szWFileName, NULL, NULL,
                                    &DDPF_PMARGB32, IID_IDXSurface, (void**)&g_pDXImageSurf );
                    if( FAILED( hr ) )
                    {
                        if( hr == DXTERR_REQ_IE_DLLNOTFOUND ) // Possibly need IE4.0 or greater.
                        {
                            return InitFail( hWnd, hr, "LoadImage failed!\n"
                                "Possible cause is that IE4.0 or greater is not installed.");
                        }
                        else 
                        {
                            // Note - some possible errors may include:
                            // MK_E_SYNTAX - Couldn't find the image directory
                            // INET_E_RESOURCE_NOT_FOUND - Couldn't find the image filename
                            sprintf( szError, "LoadImage failed with error code 0x%X.", hr );
                            return InitFail( hWnd, hr, szError );
                        }
                    }

                    // Let the app know that its now active and from here on when it processes 
                    // WM_PAINT messages it can Blit. Prior to this we don't want to call 
                    // BitBlt in WM_PAINT
                    g_bActive = TRUE;

                    // Force a WM_PAINT message
                    InvalidateRect( NULL, NULL, TRUE );
                }              
                break;

            case IDM_EXIT:
                SendMessage( hWnd, WM_DESTROY, 0, 0 );
                break;

            case IDM_ABOUT:
                MessageBox( hWnd, "DXSurface Sample 1.\nDemonstrates DXSurface BitBlt to a "
                          "Primary Surface.\n\nCopyright © 1998 Microsoft® Corporation", 
                          "About", MB_OK );
                break;
        }
        break;
                
    case WM_DESTROY:
        ReleaseAllObjects();
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hWnd, iMsg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: InitApp()
// Desc: Do work required for every instance of the application:
//       Create the window, initialize data
//-----------------------------------------------------------------------------
static HRESULT
InitApp( HINSTANCE hInstance, int iCmdShow )
{
    HRESULT     hr;
    HWND        hWnd;
    WNDCLASSEX  wndclass;
    
    wndclass.cbSize         = sizeof( wndclass );
    wndclass.style          = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc    = WndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance      = hInstance;
    wndclass.hIcon          = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_DXTICON) );
    wndclass.hCursor        = LoadCursor( NULL, IDC_ARROW );
    wndclass.hbrBackground  = ( HBRUSH ) GetStockObject( GRAY_BRUSH );
    wndclass.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);
    wndclass.lpszClassName  = NAME;
    wndclass.hIconSm        = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_DXTICON) );

    RegisterClassEx( &wndclass );

    hWnd = CreateWindowEx( NULL,
                           NAME,
                           TITLE,
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           NULL,
                           NULL,
                           hInstance,
                           NULL );

    if ( !hWnd )
        return FALSE;
    ShowWindow( hWnd, iCmdShow );
    UpdateWindow( hWnd );
        
    // Create the Surface Factory and return a pointer 
    // (note the CLSID says DXTransformFactory but these are the same object)
    hr = CoCreateInstance( CLSID_DXTransformFactory, NULL, CLSCTX_INPROC,
                             IID_IDXSurfaceFactory, (void **)&g_pSurfFact );
    if ( FAILED( hr ) )
        return InitFail( hWnd, hr, "Failed to create the Surface Factory" );

    // Initialize the DDSURFACEDESC structure
    DDSURFACEDESC   ddsd;

    ZeroMemory( &ddsd, sizeof( ddsd ) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    // Pass in DDraw info to the call to IDXSurfaceFactory::CreateSurface so it
    // will know what type of underlying surface to create. Note that applications
    // that don't care what type of underlying Direct Draw surface to use would just 
    // pass NULL for the first 2 parameters. 
    // Applications that use this method for creating surfaces other than primary 
    // surfaces will have to specify dimensions either through the DDSURFACEDESC
    // parameter (param 2) or throught the DXBNDS parameter (param 4).
    hr = g_pSurfFact->CreateSurface( NULL, &ddsd, NULL, NULL, 0,      
                            NULL, IID_IDXSurface, (void **)&g_pPrimaryDXSurf );
    if ( FAILED( hr ) )
        return InitFail( hWnd, hr, "Failed to create a primary DXSurface." );

    return hr;
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Initialization, message loop
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
    MSG         msg;
    
    // Initialize the COM library
    CoInitialize( NULL );    

    if ( InitApp( hInstance, iCmdShow ) != S_OK )
    {
        ReleaseAllObjects();
        return FALSE;
    }

    while( GetMessage ( &msg, NULL, 0, 0 ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Uninitialize the COM library
    CoUninitialize();

    return msg.wParam;
}


