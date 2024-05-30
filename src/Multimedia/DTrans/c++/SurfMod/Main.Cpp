///////////////////////////////////////
// 
//  main.cpp
//
//  This sample demonstrates how surface modifiers can be
//  used to create a variety of images through a slide
//  show presentation.  
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//

///////////////////////////////////////
// 
//  Windows includes
//

#include <objbase.h>
#include <initguid.h>
#include <windows.h>
#include <wchar.h>
#include <tchar.h>

///////////////////////////////////////
// 
//  DXTransforms includes
//

#include <dxtguid.c>
#include <dxtmsftguid.h>
#include <dxtrans.h> 
#include <dxtmsft.h>
#include <dxbounds.h>
#include <dxterror.h>
#include "resource.h"

///////////////////////////////////////
// 
//  Macros
//

#define MAX_SLIDE_INDEX 11

///////////////////////////////////////
// 
//  Function Prototypes
//

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void HandleError(HRESULT hr, HWND hwnd, LPCSTR szErrorMsg);
void ReleaseAllObjects(void);
void GetImageDirectoryAndFileName(PWSTR wszImageDirAndFileName, 
								  PCWSTR wszFileName);

///////////////////////////////////////
// 
//  Global Variables
//

IDXTransformFactory*    g_pTransFact        = NULL;
IDXSurfaceFactory*      g_pSurfFact         = NULL;
IDXSurface*             g_pSurf1            = NULL;
IDXSurface*             g_pSurf2            = NULL;

IDXSurfaceModifier*     g_pSurfMod          = NULL;
IDXSurface*             g_pSurfModSurf      = NULL;

IDXLUTBuilder*          g_pLUTBuilder       = NULL;
IDXLookupTable*         g_pLookupTable      = NULL;

CDXDBnds                g_bndsMod;
CDXDBnds                g_bndsWnd;

int                     g_iFrameIndex       = -1;

LPCSTR                  g_szCaption         = NULL;
LPCSTR                  g_szNotes           = NULL;





////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
////////////////////////////////////////////////////////////////
{
    static char szAppName[] = "SurfMod";
    HWND        hwnd;
    MSG         msg;
    WNDCLASSEX  wc;

    CoInitialize(NULL);

    wc.cbSize           = sizeof(wc);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName     = MAKEINTRESOURCE(IDR_MENU1);
    wc.lpszClassName    = szAppName;
    wc.hIconSm          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
                          szAppName, "SurfMod",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          680, 480,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    if ( hwnd )
    {
        ShowWindow(hwnd, iCmdShow);
        UpdateWindow(hwnd);

        while ( GetMessage(&msg, NULL, 0, 0) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    ReleaseAllObjects();
    CoUninitialize();

    return msg.wParam;
}


////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
////////////////////////////////////////////////////////////////////////////
{
    PAINTSTRUCT ps;
    RECT        rc;
    HDC         hdc         = NULL;
    HRESULT     hr          = S_OK;
    WCHAR       wszImageFile[256];

    CDXDBnds    bndsCur;                    // A variable to hold the current
                                            // bounds of the surface modifier
                                            // if needed.

    POINT       pt          = { 50, 50 };   // Used for offset.

    IDXSurface* pSurfTemp   = NULL;         // A temporary surface used to
                                            // translate the surface modifier
                                            // to the screen's pixel format and
                                            // retrieve a handle to a DC.

    IDXDCLock*  pLock       = NULL;         // Used to lock a pSurfTemp and 
                                            // retrieve a handle to a DC.

    OPIDDXLUTBUILDER lutOps[] =             // Operations performed by the
        { OPID_DXLUTBUILDER_Invert };       // lookup table.


    switch ( iMsg )
    {
    case WM_COMMAND:

        // User selected Exit from the File menu.

        switch ( LOWORD(wParam) )
        {
        case IDM_EXIT:

            PostMessage(hwnd, WM_CLOSE, 0, 0L);
            return 0;
        }

        break;

    case WM_CREATE:

        ///////////////////////////////////////
        // 
        //  Create factories
        //

        // Transform factory.

        hr = CoCreateInstance(CLSID_DXTransformFactory, NULL, CLSCTX_INPROC,
                              IID_IDXTransformFactory, (void**) &g_pTransFact);

        // Surface factory.
        
        if ( SUCCEEDED(hr) )
        {
            hr = g_pTransFact->QueryService(SID_SDXSurfaceFactory,
                                            IID_IDXSurfaceFactory,
                                            (void**) &g_pSurfFact);
        }

        if ( FAILED(hr) )
        {
            HandleError(hr, NULL, "Can't create factories.  The DXMedia SDK "
                        "must be installed for this sample to work properly.");

            return -1;
        }

        ///////////////////////////////////////
        // 
        //  Load Images
        //

        GetImageDirectoryAndFileName(wszImageFile, L"eagle_ck.gif");

        hr = g_pSurfFact->LoadImage(wszImageFile, 
                                    NULL, NULL, &DDPF_PMARGB32, IID_IDXSurface,
                                    (void**) &g_pSurf1);

        if ( SUCCEEDED(hr) )
        {
            GetImageDirectoryAndFileName(wszImageFile, L"apple.gif");

            hr = g_pSurfFact->LoadImage(wszImageFile, 
                                        NULL, NULL, &DDPF_PMARGB32, IID_IDXSurface,
                                        (void**) &g_pSurf2);
        }

        if ( FAILED(hr) )
        {
            if ( DXTERR_REQ_IE_DLLNOTFOUND == hr )
            {
                HandleError(hr, NULL, "Error loading images, possibly because "
                            "IE4.0 or greater is not installed.");
            }
            else
            {
                HandleError(hr, NULL, "LoadImage failure.");
            }

            return -1;
        }


        ///////////////////////////////////////
        // 
        //  Create lookup table
        //

        // Create a lookup table builder.

        if ( SUCCEEDED(hr) )
        {
            hr = CoCreateInstance(CLSID_DXLUTBuilder, NULL, CLSCTX_INPROC,
                                  IID_IDXLUTBuilder, (void**) &g_pLUTBuilder);
        }

        // Setup to support color inversion operation.

        if ( SUCCEEDED(hr) )
        {
            hr = g_pLUTBuilder->SetBuildOrder(lutOps, 1);
        }

        // Modify the level of the color inversion.

        if ( SUCCEEDED(hr) )
        {
            hr = g_pLUTBuilder->SetInvert(0.5);
        }

        // Query for a lookup table to be attached to the surface modifier.

        if ( SUCCEEDED(hr) )
        {
            hr = g_pLUTBuilder->QueryInterface(IID_IDXLookupTable,
                                               (void**) &g_pLookupTable);
        }

        if ( FAILED(hr) )
        {
            HandleError(hr, NULL, "Error creating lookup table.");

            return -1;
        }

        // The g_iFrameIndex variable is initialized to -1.  Immediately 
        // sending the window a keypress right arrow message will update
        // b_iFrameIndex to 0 and setup the first sample frame.

        SendMessage(hwnd, WM_KEYDOWN, VK_RIGHT, 0);

        return 0;

    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;

    case WM_KEYDOWN:

        switch ( wParam )
        {
        
            // Only responds to the user pressing the right
            // or left arrow keys.

        case VK_RIGHT:
        case VK_LEFT:

            while ( TRUE )
            {
                if ( VK_RIGHT == wParam && g_iFrameIndex < MAX_SLIDE_INDEX )
                {
                    // Increase the frame count if the user pressed
                    // the right arrow key.

                    g_iFrameIndex++;
                    break;
                }

                if ( VK_LEFT == wParam && g_iFrameIndex > 0 )
                {
                    // Decrease the frame index if the user pressed
                    // the left arrow key.

                    g_iFrameIndex--;
                    break;
                }

                return 0;
            }

            ///////////////////////////////////////
            // 
            //  Reset surface modifier
            //

            // The surface modifier can be reset by calling all Set methods 
            // with NULL parameters or the it can be released and re-created.

            // 1. Release surface modifier and associated surface pointer.

            if ( g_pSurfModSurf )
            {
                g_pSurfModSurf->Release();
                g_pSurfModSurf = NULL;
            }

            if ( g_pSurfMod )
            {
                g_pSurfMod->Release();
                g_pSurfMod = NULL;
            }

            // 2. Re-create surface modifier.

            hr = CoCreateInstance(CLSID_DXSurfaceModifier, NULL, CLSCTX_INPROC,
                                  IID_IDXSurfaceModifier, (void**) &g_pSurfMod);

            // 3. Query for surface pointer to access the image.

            if ( SUCCEEDED(hr) )
            {
                hr = g_pSurfMod->QueryInterface(IID_IDXSurface, 
                                                (void**) &g_pSurfModSurf);
            }

            ///////////////////////////////////////
            // 
            //  Setup new frame
            //

            switch ( g_iFrameIndex )
            {
            case 0:

                // Blank opaque blue surface

                g_pSurfMod->SetFillColor(0xFF0000FF);
                g_pSurfMod->SetBounds(&g_bndsMod);

                g_szCaption = "0    "
                              "Fill Color: Opaque Blue    "
                              "[ Use left and right arrow keys to switch frames ]";

                g_szNotes = "When no background is used, the surface modifier "
                            "can be any size and sizes with the window.";

                break;

            case 1:

                // Blank opaque blue surface that's the
                // same size as the background surface

                g_pSurfMod->SetFillColor(0xFF0000FF);
                g_pSurfMod->SetBackground(g_pSurf1);

                g_szCaption = "1    "
                              "Background: Eagle    "
                              "Fill Color: Opaque Blue [ Obscures eagle ]";

                g_szNotes = "A surface modifier using a background always sizes "
                            "to the background.";

                break;

            case 2:

                // Eagle surface with a translucent blue
                // surface over the top.

                g_pSurfMod->SetFillColor(0x550000FF);
                g_pSurfMod->SetBackground(g_pSurf1);

                g_szCaption = "2    "
                              "Background: Eagle    "
                              "Fill Color: Translucent Blue    "
                              "Composite Operation: Over [ default ]    ";

                g_szNotes = "Fill color is always drawn in front of the "
                            "background surface.";

                break;

            case 3:

                // translucent blue eagle

                g_pSurfMod->SetFillColor(0x550000FF);
                g_pSurfMod->SetBackground(g_pSurf1);
                g_pSurfMod->SetCompositeOperation(DXSURFMOD_COMP_ALPHA_MASK);

                g_szCaption = "3    "
                              "Background: Eagle    "
                              "Fill Color: Translucent Blue    "
                              "Composite Operation: Alpha Mask    ";

                g_szNotes = "The background's alpha value is used to draw the "
                            "fill color.";

                break;

            case 4:

                // Apple in upper left hand corner of a 
                // translucent blue surface

                g_pSurfMod->SetFillColor(0x550000FF);
                g_pSurfMod->SetForeground(g_pSurf2, FALSE, NULL);
                g_pSurfMod->SetBounds(&g_bndsMod);

                g_szCaption = "4    "
                              "Fill Color: Translucent Blue    "
                              "Foreground: Apple";

                g_szNotes = "Foreground surfaces are always drawn in front of "
                            "the fill color.";

                break;

            case 5:

                // Apple in front of translucent blue surface
                // placed 50 pixels from both top and left edges

                g_pSurfMod->SetFillColor(0x550000FF);
                g_pSurfMod->SetForeground(g_pSurf2, FALSE, &pt);
                g_pSurfMod->SetBounds(&g_bndsMod);

                g_szCaption = "5    "
                              "Fill Color: Translucent Blue    "
                              "Foreground: Apple, offset [ 50, 50 ]";


                g_szNotes = "When not tiled, the foreground is offset relative "
                            "to the upper left corner of the surface modifier.";

                break;

            case 6:

                // Apples tiled in front of translucent blue surface
                // with first apple against top left edge.

                g_pSurfMod->SetFillColor(0x550000FF);
                g_pSurfMod->SetForeground(g_pSurf2, TRUE, NULL);
                g_pSurfMod->SetBounds(&g_bndsMod);

                g_szCaption = "6    "
                              "Fill Color: Translucent Blue    "
                              "Foreground: Apple, tiled";

                g_szNotes = "The first tiled foreground image is placed in the "
                            "upper left corner of the surface modifier.";

                break;

            case 7:

                // Apples tiled in front of translucent blue surface
                // with the [50, 50] coordinate of the first apple
                // at the top left corner.

                g_pSurfMod->SetFillColor(0x550000FF);
                g_pSurfMod->SetForeground(g_pSurf2, TRUE, &pt);
                g_pSurfMod->SetBounds(&g_bndsMod);

                g_szCaption = "7    "
                              "Fill Color: Translucent Blue    "
                              "Foreground: Apple, tiled, offset [ 50, 50 ]";

                g_szNotes = "When tiled, the offset is relative to the upper "
                            "left corner of the foreground surface.";

                break;

            case 8:

                // Apple in front of eagle.

                g_pSurfMod->SetBackground(g_pSurf1);
                g_pSurfMod->SetForeground(g_pSurf2, FALSE, NULL);

                g_szCaption = "8    "
                              "Background: Eagle    "
                              "Foreground: Apple    "
                              "Composite Operation: Over [ default ]";
                              
                g_szNotes = "The foreground surface is always drawn in front "
                            "of the background surface.";

                break;

            case 9:

                // translucent apple in front of eagle.

                g_pSurfMod->SetBackground(g_pSurf1);
                g_pSurfMod->SetForeground(g_pSurf2, FALSE, NULL);
                g_pSurfMod->SetOpacity(0.5);

                g_szCaption = "9    "
                              "Background: Eagle    "
                              "Foreground: Apple    "
                              "Composite Operation: Over [ default ]    "
                              "Opacity: 0.5";

                g_szNotes = "SetOpacity only affects the opacity of the "
                            "foreground surface.";

                break;

            case 10:

                // translucent tiled apples only show where eagle's
                // alpha value is greater than zero.

                g_pSurfMod->SetBackground(g_pSurf1);
                g_pSurfMod->SetForeground(g_pSurf2, TRUE, NULL);
                g_pSurfMod->SetCompositeOperation(DXSURFMOD_COMP_ALPHA_MASK);
                g_pSurfMod->SetOpacity(0.5);

                g_szCaption = "10    "
                              "Background: Eagle    "
                              "Foreground: Apple, tiled    "
                              "Composite Operation: Alpha Mask    "
                              "Opacity: 0.5";

                g_szNotes = "Alpha mask can be used for a cool effect with "
                            "a tiled foreground surface and opacity.";

                break;

            case 11:

                // Apple modified using a lookup table in front of
                // a translucent blue surface.

                g_pSurfMod->SetFillColor(0xFF000055);
                g_pSurfMod->SetForeground(g_pSurf2, FALSE, NULL);
                g_pSurfMod->SetLookup(g_pLookupTable);
                g_pSurfMod->SetBounds(&g_bndsMod);

                g_szCaption = "11    "
                              "Fill Color: Solid Dark Blue    "
                              "Foreground: Apple    "
                              "Lookup Table: Color Inversion";

                g_szNotes = "Lookup tables only modify the foreground surface.  "
                            "This was created with a lookup table builder.";

                break;
            }

            // Check for error

            if ( FAILED(hr) )
            {
                HandleError(hr, hwnd, "Error during frame setup.");
            }

            // Force window repaint

            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
        }

        return 0;

    case WM_PAINT:

        hdc = BeginPaint(hwnd, &ps);

        // Retrieve the bounds of the surface modifier.

        hr = g_pSurfModSurf->GetBounds(&bndsCur);

        //     Since you can't get a device context from a 
        //     surface modifier, you have to:

        // 1.  Create a new surface, same size as surface modifier.
        //     Sending parameter 3 as NULL means the surface will be
        //     created with the same pixel format as the display.

        if ( SUCCEEDED(hr) )
        {
            hr = g_pSurfFact->CreateSurface(NULL, NULL, NULL, &bndsCur, NULL,
                                            NULL, IID_IDXSurface, 
                                            (void**) &pSurfTemp);
        }

        // 2.  Use surface factory's BitBlt function to copy the image
        //     onto the new surface (this is the most efficient method).

        if ( SUCCEEDED(hr) )
        {
            hr = g_pSurfFact->BitBlt(pSurfTemp, NULL, g_pSurfModSurf, NULL, NULL);
        }

        // 3.  Lock the surface so that changes can't be made while painting.

        if ( SUCCEEDED(hr) ) 
        {
            hr = pSurfTemp->LockSurfaceDC(NULL, INFINITE, DXLOCKF_READ, &pLock);
        }

        // 4.  Retrieve a device context from the lock and then use the  GDI
        //     BitBlt function to blit the contents of the surface to the window.

        if ( SUCCEEDED(hr) )
        {
            hdc = pLock->GetDC();

            if ( bndsCur == g_bndsMod )
            {
                // If the bounds are the same as the largest possible
                // size for this window size, blit to (0,0).
                // [ Note:  Will run this code when the surface modifier
                //          does not use a background surface. ]

                BitBlt(ps.hdc, 0, 0, 
                       bndsCur.Width(), bndsCur.Height(), 
                       hdc, 0, 0, SRCCOPY);
            }
            else
            {
                // If the bounds are different than the largest possible
                // size for this window size, center inside the window.
                // [ Note:  Will run this code when the surface modifier
                //          uses a background surface. ]

                BitBlt(ps.hdc,
                       (g_bndsMod.Width()  - bndsCur.Width())  / 2,
                       (g_bndsMod.Height() - bndsCur.Height()) / 2,
                       bndsCur.Width(), bndsCur.Height(), 
                       hdc, 0, 0, SRCCOPY);
            }

            // Releasing the lock will also release the handle to the device
            // context (hdc) so ReleaseDC isn't needed.

            pLock->Release();
        }

        // Release the temporary surface used to convert the
        // pixel format and retrieve an hdc.

        if ( pSurfTemp )
        {
            pSurfTemp->Release();
        }

        // Print the caption text at the bottom of the screen.

        if ( SUCCEEDED(hr) )
        {
            SetBkMode(ps.hdc, TRANSPARENT);

            SetTextColor(ps.hdc, RGB(255, 0, 0));
            TextOut(ps.hdc, 10, g_bndsWnd.Height() - 45, g_szCaption, strlen(g_szCaption));

            SetTextColor(ps.hdc, RGB(0, 200, 0));
            TextOut(ps.hdc, 10, g_bndsWnd.Height() - 25, g_szNotes, strlen(g_szNotes));
        }

        EndPaint(hwnd, &ps);

        // Check for error

        if ( FAILED(hr) )
        {
            HandleError(hr, hwnd, "Error repainting frame.");
        }

        return 0;

    case WM_SIZE:

        GetClientRect(hwnd, &rc);

        // When the window is resized, set the sizes of 
        // two bounds objects:
        //
        // g_bndsWnd is the size of the full client area of the
        //   window.
        //
        // g_bndsMod is the size of the full client area of the
        //   window minus a few pixels to leave room for a caption.
        //   These are the bounds that will be used to size surface
        //   modifiers that don't use a background surface.
        
        g_bndsWnd.SetXYSize(rc.right - rc.left, rc.bottom - rc.top);

        g_bndsMod.SetXYSize(rc.right - rc.left, rc.bottom - rc.top - 50);

        // Set the "virtual size" of the surface modifier equal to
        // the same size as the window (leaving room at the bottom
        // for the frame caption.)  If the surface modifier uses 
        // a background surface it will ignore this method and retain
        // bounds equal to the size of the background surface.

        g_pSurfMod->SetBounds(&g_bndsMod);

        return 0;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


//////////////////////////////////////////////////////////
void HandleError(HRESULT hr, HWND hwnd, LPCSTR szErrorMsg)
//////////////////////////////////////////////////////////
{
    char    szMsg[256];

    wsprintf(szMsg, "HRESULT: 0x%08x\n%s", hr, szErrorMsg);

    MessageBox(hwnd, szMsg, "Error", MB_OK | MB_ICONEXCLAMATION);

    if ( hwnd )
        PostMessage(hwnd, WM_CLOSE, 0, 0);
}


////////////////////////////
void ReleaseAllObjects(void)
////////////////////////////
{
    if ( g_pLookupTable )
        g_pLookupTable->Release();

    if ( g_pLUTBuilder )
        g_pLUTBuilder->Release();

    if ( g_pSurfModSurf )
        g_pSurfModSurf->Release();

    if ( g_pSurfMod )
        g_pSurfMod->Release();

    if ( g_pSurf2 )
        g_pSurf2->Release();

    if ( g_pSurf1 )
        g_pSurf1->Release();

    if ( g_pSurfFact )
        g_pSurfFact->Release();

    if ( g_pTransFact )
        g_pTransFact->Release();
}


///////////////////////////////////////////////////////////////////////////////////
void GetImageDirectoryAndFileName(PWSTR wszImageDirAndFileName, PCWSTR wszFileName)
///////////////////////////////////////////////////////////////////////////////////
{
    // This function retrieves the directory where the SDK images
    // are located and appends the file name to the end of this
    // directory.  This is intended for use with IDXSurfaceFactory::LoadImage()
    // which takes absolute paths to images.
    // NOTE: This function returns a (Unicode) wide character string.

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








