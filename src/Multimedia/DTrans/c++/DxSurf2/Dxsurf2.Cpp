//-----------------------------------------------------------------------------
// File: DXSurf2.CPP
//
// Desc: DXSurface example program 2. Demonstrates alpha blending pixels
//       from one image over another using DXSurfaces and Surface Modifiers.
//
// Note: The LoadImage api requires IE4 or greater to be installed
// Note: In order to compile this sample you need to install the 
//       DirectX Foundation SDK and set its include path (\mssdk\include) 
//       topmost in Tools | Options | Directories."
//
// Copyright (c) 1995-1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <initguid.h>
#include <dxtrans.h>  // DXSurface header file
#include <dxbounds.h> // Defines the CDXDBnds class
#include <dxtguid.c>  // Guids for DXSurfaces
#include <dxterror.h> // DXT error codes
#include "resource.h"


//-----------------------------------------------------------------------------
// Local definitions
//-----------------------------------------------------------------------------
#define NAME                "DXSurf2"
#define TITLE               "DXSurface Example 2"
#define SAFE_RELEASE( ptr )         \
{                                   \
        if (ptr) ptr->Release();    \
        ptr=NULL;                   \
}

//-----------------------------------------------------------------------------
// Default settings
//-----------------------------------------------------------------------------
#define TIMER_ID            1

//-----------------------------------------------------------------------------
// Global data
//-----------------------------------------------------------------------------
IDXSurfaceFactory*      g_pSurfFact         = NULL;
IDXSurface*             g_pDXSurf1          = NULL;
IDXSurface*             g_pDXSurf2          = NULL;
IDXSurface*             g_pDXOutSurf        = NULL;
CDXDBnds                g_bnds;             // Boundaries for the output surface
IDXSurface*             g_pDXSurfOnSurfMod  = NULL;
IDXSurfaceModifier*     g_pSurfMod          = NULL;
BOOL                    g_bActive           = FALSE;
BOOL                    g_bBrighten         = TRUE;
float                   g_fOpacity          = .5;
HINSTANCE               g_hInst             = NULL;


//-----------------------------------------------------------------------------
// Name: ReleaseAllObjects()
// Desc: Finished with all objects we use; release them
//-----------------------------------------------------------------------------
static void ReleaseAllObjects(void)
{
    SAFE_RELEASE( g_pSurfMod )
    SAFE_RELEASE( g_pDXSurf1 )
    SAFE_RELEASE( g_pDXSurf2 )
    SAFE_RELEASE( g_pDXSurfOnSurfMod )
    SAFE_RELEASE( g_pDXOutSurf )    
    SAFE_RELEASE( g_pSurfFact )
}

//-----------------------------------------------------------------------------
// Name: InitFail()
// Desc: This function is called if an initialization function fails
//-----------------------------------------------------------------------------
HRESULT InitFail(HWND hWnd, HRESULT hr, LPCTSTR szError,...)
{
    char                    szBuff[128];
    va_list                 vl;

    g_bActive = FALSE;
    va_start( vl, szError );
    vsprintf( szBuff, szError, vl );
    MessageBox( hWnd, szBuff, TITLE, MB_OK );
    ReleaseAllObjects();
    DestroyWindow( hWnd );
    va_end( vl );
    return hr;
}

//-----------------------------------------------------------------------------
// Name: ModifySurface()
// Desc: Sets the foreground and background for the surface modifier and queries
//       for and IDXSurface interface off the surface modifier.
//-----------------------------------------------------------------------------
HRESULT ModifySurface()
{
    HRESULT                 hr;

    // Create the Surface Modifier object
    hr = CoCreateInstance( CLSID_DXSurfaceModifier, NULL, CLSCTX_INPROC,
                                 IID_IDXSurfaceModifier, (void **)&g_pSurfMod );
    
    // Set the foreground to the parrot.png
    if( SUCCEEDED( hr ) )
    {
        hr = g_pSurfMod->SetForeground( g_pDXSurf2, FALSE, NULL );
    }

    // Set the background to tulipshol2.jpg
    if( SUCCEEDED( hr ) )
    {
        hr = g_pSurfMod->SetBackground( g_pDXSurf1 );
    }

    // Query the Surface Modifier for an IDXSurface pointer
    if( SUCCEEDED( hr ) )
    {
        hr = g_pSurfMod->QueryInterface( IID_IDXSurface, (void**)&g_pDXSurfOnSurfMod );
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: RenderToWindow()
// Desc: Blit the surface containing the image to the window
//-----------------------------------------------------------------------------
HRESULT RenderToWindow( HANDLE hWnd, HDC hdcWnd, float fOpacity )
{
    HRESULT                 hr;
    char                    szOpacity[256];
    CDXDBnds                bnds;
    IDXDCLock*              pDCLock = NULL;
    RECT                    rect;
    HDC                     hdcSurf = NULL;
            
    // This call sets the new Opacity on the foreground surface
    hr =  g_pSurfMod->SetOpacity( fOpacity );
    if ( FAILED( hr ) )
        return InitFail((HWND)hWnd, hr, "Failed to SetOpacity on Surface Modifier.");
    
    // Blit the DXSurface on associated with the Surface Modifier to the Output DXSurface
    hr = g_pSurfFact->BitBlt( g_pDXOutSurf, NULL, g_pDXSurfOnSurfMod, NULL, DXBOF_DO_OVER );
    if ( FAILED( hr ) )
        return InitFail( (HWND)hWnd, hr, "BitBlt failed" );
    
    // Call LockSurfaceDC to get the DC of the surface
    hr  = g_pDXOutSurf->LockSurfaceDC( NULL, 3000, 0, &pDCLock );
    if ( FAILED( hr ) )
        return InitFail( (HWND)hWnd, hr, "LockSurfaceDC failed." );

    hdcSurf = pDCLock->GetDC();
    
    GetClientRect( (HWND)hWnd, &rect );

    // Use GDI BitBlt to blit the surface DC to the window DC
    BitBlt( hdcWnd, 0, 0, rect.right, rect.bottom, hdcSurf, 0, 0, SRCCOPY );
    
    sprintf( szOpacity, "Parrot alpha blended with %d%% opacity over tulips.", 
                    (int)((g_fOpacity*100)+.01) );
    SetTextColor( hdcWnd, RGB(255, 255, 0) );
    SetBkMode( hdcWnd, TRANSPARENT );
    DrawText( hdcWnd, szOpacity, -1, &rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE );
    
    // Release the IDXDCLock pointer which releases the DC lock on the surface as well
    SAFE_RELEASE( pDCLock )
    
    return hr;
}

//-----------------------------------------------------------------------------
// Name: GetImageDirectoryAndFileName()
// Desc: This function retrieves the directory where the SDK images
//       are located and appends the file name to the end of this
//       directory.  This is intended for use with IDXSurfaceFactory::LoadImage()
//       which takes absolute paths to images.
//       NOTE: This function returns a (Unicode) wide character string.
//-----------------------------------------------------------------------------
void GetImageDirectoryAndFileName( PWSTR wszImageDirAndFileName, PCWSTR wszFileName )
{
    // Look in registry for the DirectX Media SDK
    // base path so application can find images.
    unsigned char   szImagePath[256] = "";
    HKEY            hkey;
    LONG            lResult;
    DWORD           dwImagePathSize = 256;

    // Open the reg key.
    lResult  = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
						"Software\\Microsoft\\Multimedia\\DirectXMedia", 0, 
						KEY_READ, 
						&hkey);

    if ( ERROR_SUCCESS != lResult )
    {
        // If the registry path isn't found, set the base path
        // to the root of the current drive plus dxmedia.
        wcscpy(wszImageDirAndFileName, L"\\dxmedia");
    }
    else
    {
        // Lookup the value for BaseSDKPath and convert
        // it to a wide character string.
        RegQueryValueEx(hkey, "BaseSDKPath", NULL, NULL,
                        szImagePath, &dwImagePathSize);
        RegCloseKey(hkey);

        // If path wasn't retrieved from the registry, use the default.
        if(szImagePath[0] == NULL)
            wcscpy(wszImageDirAndFileName, L"\\dxmedia");
        else // Convert the returned path to wide string format.
            MultiByteToWideChar(CP_ACP, NULL, (const char*)szImagePath, 
                dwImagePathSize, wszImageDirAndFileName, 256);
    }

    // Add the image directory and filename information onto the base path.
	swprintf(wszImageDirAndFileName, 
			 L"%s\\samples\\multimedia\\media\\image\\%s",
			 wszImageDirAndFileName, wszFileName);
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
    HRESULT         hr = S_OK;
    RECT            rect;
    HDC             hdcWnd;
    PAINTSTRUCT     ps;
            
    switch( iMsg )
    {
    case WM_PAINT:
        hdcWnd = BeginPaint( hWnd, &ps );

        // Render the DXSurface to the window
        if( g_bActive )
        {
            RenderToWindow( hWnd, hdcWnd, g_fOpacity );
        }        

        EndPaint( hWnd, &ps );
        return 0;

    case WM_TIMER:
            // Change opacity
            if ( g_bActive && TIMER_ID == wParam )
            {
                if ( g_bBrighten )
                {
                    g_fOpacity += .05f;
                    if( g_fOpacity > 1 )
                    {
                        g_fOpacity = 1;
                        g_bBrighten = FALSE;
                    }
                }
                else
                {
                    g_fOpacity -= .05f;
                    if( g_fOpacity < 0 )
                    {
                        g_fOpacity = 0;
                        g_bBrighten = TRUE;
                    }
                }

                GetClientRect( hWnd, &rect );
                InvalidateRect( hWnd, &rect, FALSE );                
            }
            return 0;

    case WM_SIZE:
        if( g_bActive )
        {
            // Get the boundaries of the window
            GetClientRect( hWnd, &rect );
            g_bnds.SetXYSize( rect.right, rect.bottom );

            // Release the existing output DXSurface and create a new one
            SAFE_RELEASE( g_pDXOutSurf )
            hr = g_pSurfFact->CreateSurface( NULL, NULL, NULL, &g_bnds, 0,      
                                NULL, IID_IDXSurface, (void **)&g_pDXOutSurf );
        }
        return 0;

    case WM_DESTROY:
        ReleaseAllObjects();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc( hWnd, iMsg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: InitApp()
// Desc: Do work required for every instance of the application:
//          Create the window, initialize data
//-----------------------------------------------------------------------------
static HRESULT InitApp( HINSTANCE hInstance, int iCmdShow )
{
    HRESULT     hr;
    HWND        hWnd;
    WNDCLASSEX  wndclass;
    WCHAR       wstrImagePathAndFile[_MAX_PATH + _MAX_FNAME + _MAX_EXT];
    char        szError[256];
    char        szAnsiPath[256];
    RECT        rect;
    
    wndclass.cbSize         = sizeof( wndclass );
    wndclass.style          = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc    = WndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance      = hInstance;
    wndclass.hIcon          = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_DXTICON) );
    wndclass.hCursor        = LoadCursor( NULL, IDC_ARROW );
    wndclass.hbrBackground  = ( HBRUSH ) GetStockObject( WHITE_BRUSH );
    wndclass.lpszMenuName   = NAME;
    wndclass.lpszClassName  = NAME;
    wndclass.hIconSm        = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_DXTICON) );

    RegisterClassEx( &wndclass );
    g_hInst = hInstance;

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
        return InitFail( hWnd, hr, "Failed to Create Transform/Surface Factory" );

    // -- Load the first image

    // Call a helper function that retrieves an absolute path to
    // the image file passed in.
    GetImageDirectoryAndFileName( wstrImagePathAndFile, L"tulipshol2.jpg" );

    // Create a surface from an image file.
    // NOTE: The first parameter is a wide character string.  If your path
    // is in ANSI, use mbstowcs() or MultiByteToWideChar().
    hr = g_pSurfFact->LoadImage( wstrImagePathAndFile, NULL, NULL,
                                  &DDPF_PMARGB32, IID_IDXSurface, (void**)&g_pDXSurf1 );
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
            
            // Convert the unicode path and file string to ansi
            wcstombs( szAnsiPath, wstrImagePathAndFile, 256 );
            sprintf( szError, "LoadImage failed with error code 0x%X.\nTried to load %s", 
                                hr, szAnsiPath );
            return InitFail( hWnd, hr, szError );
        }
    }

    // -- Load the second image

    // Call a helper function that retrieves an absolute path to
    // the image file passed in.
    GetImageDirectoryAndFileName( wstrImagePathAndFile, L"parrot.png" );

    // Create a surface from an image file.
    // NOTE: The first parameter is a wide character string.  If your path
    // is in ANSI, use mbstowcs() or MultiByteToWideChar().
    hr = g_pSurfFact->LoadImage( wstrImagePathAndFile, NULL, NULL,
                                  &DDPF_PMARGB32, IID_IDXSurface, (void**)&g_pDXSurf2 );
    if( FAILED( hr ) )
    {
        if( hr == DXTERR_REQ_IE_DLLNOTFOUND ) // Possibly need IE4.0 or greater.
        {
            return InitFail( hWnd, hr, "LoadImage failed!\n"
                "Possible cause is that IE4.0 or greater is not installed.");
        }
        else 
        {
            // Convert the unicode path and file string to ansi
            wcstombs( szAnsiPath, wstrImagePathAndFile, 256 );
            sprintf( szError, "LoadImage failed with error code 0x%X.\nTried to load %s", 
                                hr, szAnsiPath );
            return InitFail( hWnd, hr, szError );
        }
    }

    // Call ModifySurface function to apply opacity values to g_pDXSurf2
    hr = ModifySurface();
    if ( FAILED( hr ) )
        return InitFail( hWnd, hr, "MakeSurfaceOpaque failed" );

    GetClientRect( hWnd, &rect );
    // Set the boundaries of the Output DXSurface
    g_bnds.SetXYSize( rect.right, rect.bottom );

    // Create an output DXSurface
    hr = g_pSurfFact->CreateSurface( NULL, NULL, NULL, &g_bnds, 0,      
                            NULL, IID_IDXSurface, (void **)&g_pDXOutSurf );
    if ( FAILED( hr ) )
        return InitFail( hWnd, hr, "Failed to create an output DXSurface." );

    // Create a timer to change the opacity of the parrot
    if ( TIMER_ID != SetTimer(hWnd, TIMER_ID, 0, NULL ))
        return InitFail( hWnd, E_FAIL, "SetTimer failed." );

    g_bActive = TRUE;

    return hr;

}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Initialization, message loop
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
    MSG         msg;
    HRESULT     hr;
    
    // Initialize the COM library
    hr = CoInitialize( NULL );    
    if( FAILED ( hr ) )
    {
        return FALSE;
    }

    if ( InitApp(hInstance, iCmdShow) != S_OK )
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






