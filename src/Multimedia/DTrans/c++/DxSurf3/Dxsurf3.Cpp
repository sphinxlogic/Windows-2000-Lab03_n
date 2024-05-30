///////////////////////////////////////////////////////////////////////////////
// DXSurf3.cpp
//
// This sample shows a fractal being rendered translucently over a parrot.
//
// This sample demonstrates
// - using a DXSurface in fullscreen and windowed mode
// - loading an image onto a DXSurface
// - directly manipulating the Alpha, Red, Green, and Blue components of pixels
// - using GDI operations on DXSurfaces
// - using a DXTransform to scale a DXSurface to fit the window
//   (Use this instead of StretchBlt() to preserve alpha quality.)
//
// USAGE:
//      c:\> dxsurf3.exe [-width xxx -height yyy -bpp zzz -windowed]
//               xxx specifies the width in pixels of the window, e.g. 1024
//               yyy specifies the height in pixels of the window, e.g. 768
//               zzz specifies the bits-per-pixel of the window, e.g. 16
//               -windowed indicates whether to run in a window or fullscreen
//
// NOTE:
// The PTSTR type and the TEXT() macro deal with ANSI / Multibyte Character 
// compatibility.  For further information see the Unicode topic in the 
// Developer Studio documentation or in MSDN.
//
// Copyright (c) 1998 Microsoft Corporation.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#define STRICT
#include <windows.h>
#include <DXTrans.h>
#include <DXTGuid.c>
#include <DXBounds.h>
#include <DXHelper.h>
#include <DXTError.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <mmsystem.h>
#include <stdio.h>

#include "resource.h"

#define SAFE_RELEASE(ptr) if(ptr) { ptr->Release(); ptr = NULL; }
#define NUMPIXELSTODRAW 100 // Draw this many pixels per rendering iteration.

typedef struct
{
    int         nWidth;
    int         nHeight;
    int         nBPP;
    BOOL        bWindowed;
    HINSTANCE   hInstance;
} WININFO;

BOOL ParseCommandLine(WININFO*, PTSTR);
BOOL InitInstance(WININFO*, PTSTR);
int FindNumWithParameter(PTSTR);
int FindParameter(PTSTR);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void GetImageDirectoryAndFileName(PWSTR, PCWSTR);

static WCHAR g_wstrImagePathAndFile[_MAX_PATH + _MAX_FNAME + _MAX_EXT];

///////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE    hInstance,
                   HINSTANCE /* hPrevInstance */,
                   PTSTR        pszCmdLine,
                   int       /* nCmdShow */)
///////////////////////////////////////////////////////////////////////////////
{
    static  WININFO wi;
            PTSTR   pstrClassName = TEXT("DXSurface Sample 3");
            HWND    hWnd;
            DWORD   dwStyle, dwExStyle;
            int     nX, nY;
            MSG     msg;
            int     nEdgeX, nEdgeY, nTopY;
            DWORD   dwPresentTime, dwLastTime;
            HMENU   hMenu;

    CoInitialize(NULL);

    wi.hInstance = hInstance;
    if(!ParseCommandLine(&wi, pszCmdLine))
        goto CLEANUP_AND_EXIT;

    // Register the window class and change the display settings if necessary.
    if(!InitInstance(&wi, pstrClassName))
        goto CLEANUP_AND_EXIT;

    if(wi.bWindowed)
    {
        dwExStyle = 0;
        dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
        nX = nY = CW_USEDEFAULT;
        nEdgeX = GetSystemMetrics(SM_CXEDGE);
        nEdgeY = GetSystemMetrics(SM_CYEDGE);
        nTopY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
        hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_DXSURFMENU));
    }
    else
    {
        dwExStyle = WS_EX_TOPMOST;
        dwStyle = WS_POPUP | WS_VISIBLE;
        nX = nY = 0;
        nEdgeX = nEdgeY = nTopY = 0;
        hMenu = NULL;
    }

    hWnd = CreateWindowEx(
                    dwExStyle,                  // extended window style
                    pstrClassName,              // pointer to registered class name
                    pstrClassName,              // pointer to window name
                    dwStyle,                    // window style
                    nX,                         // horizontal position of window
                    nY,                         // vertical position of window
                    wi.nWidth + (2*nEdgeX),     // window width
                    wi.nHeight + (2*nEdgeY) + nTopY, // window height
                    NULL,                       // handle to parent or owner window
                    hMenu,                      // handle to menu or child-window identifier
                    hInstance,                  // handle to application instance
                    (LPVOID)&wi);               // pointer to window-creation data
    if(!hWnd)
        goto CLEANUP_AND_EXIT;

    // Store the WININFO structure so that other functions can get to it.
    SetWindowLong(hWnd, GWL_USERDATA, (LONG)&wi);

    // Showtime!
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // Initialize time variables used to maintain a steady framerate.
    dwPresentTime = timeGetTime();
    dwLastTime    = dwPresentTime;

    while(1)
    {
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                goto CLEANUP_AND_EXIT;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Check if it's time to render.
        if(dwPresentTime - dwLastTime >= 35)
        {
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            dwLastTime = timeGetTime();
        }
        dwPresentTime = timeGetTime();
    }

CLEANUP_AND_EXIT:
    if(!wi.bWindowed)
        ChangeDisplaySettings(0, 0);

    CoUninitialize();
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
///////////////////////////////////////////////////////////////////////////////
{
    static IDXSurface*         pSurfImage       = NULL;
    static IDXSurface*         pSurfSierpinski  = NULL;
    static IDXSurface*         pSurfOut         = NULL;
    static IDXSurfaceFactory*  pSurfFact        = NULL;
    static POINT               ptSierpinskiVertices[3];
           WININFO*            pwi;

    pwi = (WININFO*)GetWindowLong(hWnd, GWL_USERDATA);

    switch(uMsg)
    {
        case WM_CREATE:
        {
            LPCREATESTRUCT          lpcs        = (LPCREATESTRUCT)lParam;
            IDXSurface*             pSurfTemp   = NULL;
            IDXTransformFactory*    pTransFact  = NULL;
            IDXTransform*           pScaleTransform = NULL;
            SIZE                    size;
            HRESULT                 hRes;
            IDXTScale*              pScale      = NULL;
            CDXDBnds                bounds;
            DXPMSAMPLE              sample;
            LRESULT                 lRet = -1;

            // Get the structure that describes the physical window.
            pwi = (WININFO*)lpcs->lpCreateParams;
            bounds.SetXYSize(pwi->nWidth, pwi->nHeight);
            size.cx = pwi->nWidth; size.cy = pwi->nHeight;

            // Create a transform factory through which we'll get
            // our surface factory.  Using the surface factory
            // we can create and manipulate DXSurfaces.
            hRes = CoCreateInstance(CLSID_DXTransformFactory, NULL,
                            CLSCTX_INPROC, IID_IDXTransformFactory, (void**)&pTransFact);
            if(FAILED(hRes))
            {
                MessageBox(NULL, TEXT("Failed to CoCreate the Transform Factory!\n"
                    "Please register dxtrans.dll."), TEXT("DXSurface Sample 3"), MB_OK);
                goto FAILED;
            }

            // Get the surface factory from the transform factory.
            pTransFact->QueryInterface(IID_IDXSurfaceFactory, (void**)&pSurfFact);

            // Call a helper function that retrieves an absolute path to
            // the image file passed in.
            GetImageDirectoryAndFileName(g_wstrImagePathAndFile, L"parrot.png");

            // Create a surface from an image file.
            // NOTE: The first parameter is a wide character string.  If your path
            // is in ANSI, use mbstowcs() or MultiByteToWideChar().
            hRes = pSurfFact->LoadImage(
                                    g_wstrImagePathAndFile, 
                                    NULL,
                                    NULL,
                                    NULL,
                                    IID_IDXSurface, 
                                    (void**)&pSurfTemp);
            if(FAILED(hRes))
            {
                if(hRes == DXTERR_REQ_IE_DLLNOTFOUND) // Need IE4.0 or greater.
                {
                    MessageBox(NULL, TEXT("Failed to load the image!\n"
                        "IE4.0 or greater is required for DXTransforms.\n"
                        "Press enter to exit."), 
                        TEXT("DXSurface Sample 3"), MB_OK);
                }
                else // Assume we couldn't find dxmedia image directory.
                {
                    MessageBox(NULL, TEXT("Couldn't find the dxmedia installation!\n"
                        "Please install the complete dxmedia SDK.\n"
                        "Press enter to exit."),
                        TEXT("DXSurface Sample 3"), MB_OK);
                }

                goto FAILED;
            }

            // Create a second, empty surface, using the size of the window
            // for the bounds.  This surface will hold the resized version of
            // the image we loaded.
            hRes = pSurfFact->CreateSurface(
                                    NULL,               // ddraw surface
                                    NULL,               // ddsurfacedesc
                                    &DDPF_PMARGB32,     // format id
                                    &bounds,
                                    0,
                                    NULL,
                                    IID_IDXSurface,
                                    (void**)&pSurfImage);
            if(FAILED(hRes))
            {
                MessageBox(NULL, TEXT("Failed to load image!\n"
                    "Please provide a valid image file."), TEXT("DXSurface Sample 3"), MB_OK);
                goto FAILED;
            }

            // Create and set-up the scale transform which will resize our image to fit
            // the entire window.  Use this instead of StretchBlt() to preserve
            // image quality as alpha is ignored with StretchBlt().
            hRes = pTransFact->CreateTransform(NULL, 0, NULL, 0, NULL, NULL, CLSID_DXTScale,
                                IID_IDXTransform, (void**)&pScaleTransform);
            if(FAILED(hRes))
            {
                MessageBox(NULL, TEXT("Failed to create the Scale transform!\n"
                    "Please register dxtrans.dll."), TEXT("DXSurface Sample 3"), MB_OK);
                goto FAILED;
            }

            pScaleTransform->Setup(
                                (IUnknown**)&pSurfTemp,     // Source (from LoadImage)
                                1,
                                (IUnknown**)&pSurfImage,    // Dest (from CreateSurface)
                                1, 
                                0);

            // Get the IDXTScale interface because IDXTScale::ScaleFitToSize() 
            // is what we need to call.
            pScaleTransform->QueryInterface(IID_IDXTScale, (void**)&pScale);
            pScale->ScaleFitToSize(NULL, size, FALSE);

            // Scale the output surface to the window size.
            pScaleTransform->Execute(NULL, NULL, NULL);

            // Create a surface the same size as the output surface
            // for fractal plotting.
            pSurfFact->CreateSurface(
                        NULL,               // ddraw surface
                        NULL,               // ddsurfacedesc
                        &DDPF_PMARGB32,     // format id
                        &bounds,    
                        0,
                        NULL,    
                        IID_IDXSurface,     
                        (void**)&pSurfSierpinski);

            // Create the output surface which will hold the final result of our
            // composition of the image and the fractal.
            pSurfFact->CreateSurface(
                        NULL,               // ddraw surface
                        NULL,               // ddsurfacedesc
                        &DDPF_PMARGB32,     // format id
                        &bounds,    
                        0,
                        NULL,
                        IID_IDXSurface,
                        (void**)&pSurfOut);

            // Set up the sierpinski vertices.
            ptSierpinskiVertices[0].x = bounds.Width() / 2;
            ptSierpinskiVertices[0].y = 0;
            ptSierpinskiVertices[1].x = 0;
            ptSierpinskiVertices[1].y = bounds.Height() - 1;
            ptSierpinskiVertices[2].x = bounds.Width() - 1;
            ptSierpinskiVertices[2].y = bounds.Height() - 1;

            // Initialize the sierpinski surface to full on red but zero alpha,
            // i.e. a transparent red surface.
            sample.Alpha = sample.Green = sample.Blue = 0x00;
            sample.Red = 0x40;
            DXFillSurface(
                pSurfSierpinski,
                sample,
                FALSE,  // Don't do a blend, just do a straight copy.
                10000); // Wait this many milliseconds.

            srand((unsigned)time(NULL));

            lRet = 0;
            goto OK;


// If we failed, we clean up all COM interfaces that we created.
// If we're successful, only clean up the temporary interfaces.
FAILED:
            SAFE_RELEASE(pSurfOut);
            SAFE_RELEASE(pSurfImage);
            SAFE_RELEASE(pSurfSierpinski);
            SAFE_RELEASE(pSurfFact);
OK:
            SAFE_RELEASE(pScaleTransform);
            SAFE_RELEASE(pScale);
            SAFE_RELEASE(pSurfTemp);
            SAFE_RELEASE(pTransFact);
            return lRet;
        } // WM_CREATE

        case WM_CLOSE:
            SAFE_RELEASE(pSurfImage);
            SAFE_RELEASE(pSurfOut);
            SAFE_RELEASE(pSurfSierpinski);
            SAFE_RELEASE(pSurfFact);
            PostQuitMessage(0);
            return 0;
        
        case WM_PAINT:
        {
            HDC         hDC;
            PAINTSTRUCT ps;
            IDXDCLock*  pIDCLock = NULL;
            CDXDBnds    bounds;
            static POINT ptCurrent = { -1, -1 };

            hDC = BeginPaint(hWnd, &ps);

            if(ptCurrent.x == -1)
                ptCurrent = ptSierpinskiVertices[rand() % 3];

            pSurfImage->GetBounds(&bounds);

            // Use IDXSurfaceFactory::BitBlt() to blt the image to the output
            // surface.
            pSurfFact->BitBlt(
                            pSurfOut,
                            NULL,
                            pSurfImage,
                            NULL,
                            0);
 
            IDXARGBReadWritePtr* pRWPtr = NULL;
            
            // Lock the DXSurface, and get an interface that allows
            // us to access the pixels.
            pSurfSierpinski->LockSurface(
                                    NULL,
                                    INFINITE,
                                    DXLOCKF_READWRITE,
                                    IID_IDXARGBReadWritePtr,
                                    (void**)&pRWPtr,
                                    NULL);

            // We use GetNativeType to give us a pointer to the first pixel,
            // and the number of pixels per row.
            DXNATIVETYPEINFO info;
            pRWPtr->GetNativeType(&info);
            DXSAMPLE* pSample = (DXSAMPLE*)info.pFirstByte;
            ULONG ulRowSampWidth = info.lPitch / sizeof(DXSAMPLE);

            // Calculate pixels to turn on.
            for(int i=0; i<NUMPIXELSTODRAW; i++)
            {
                POINT ptTemp = ptSierpinskiVertices[rand() % 3];
                ptCurrent.x = abs((ptTemp.x - ptCurrent.x) / 2) + min(ptTemp.x, ptCurrent.x);
                ptCurrent.y = abs((ptTemp.y - ptCurrent.y) / 2) + min(ptTemp.y, ptCurrent.y);

                assert(ptCurrent.x >= 0);
                assert(ptCurrent.x < pwi->nWidth);
                assert(ptCurrent.y >= 0);
                assert(ptCurrent.y < pwi->nHeight);

                // Calculate the index to the pixel.
                // Turn on the alpha channel to 1/4 intensity.
                UINT uIndex =  ulRowSampWidth * ptCurrent.y + ptCurrent.x;
                pSample[uIndex].Alpha = 0x40;
            }

            // Releasing this unlocks the Sierpinski dxsurface locked above.
            SAFE_RELEASE(pRWPtr);

            // Blend the fractal surface onto the output surface.
            pSurfFact->BitBlt(
                            pSurfOut,
                            NULL,
                            pSurfSierpinski,
                            NULL,
                            DXBOF_DO_OVER); // Do an alpha blend.
             
            // Lock the output surface and draw it to the DC, using GDI's BitBlt.
            pSurfOut->LockSurfaceDC(NULL, INFINITE, DXLOCKF_READ, &pIDCLock);

            PTSTR pstrMessage = TEXT("Red pixels alpha-blended over an image");
            SetBkMode(pIDCLock->GetDC(), TRANSPARENT);
            SetTextColor(pIDCLock->GetDC(), RGB(0xFF, 0x00, 0x00));
            TextOut(pIDCLock->GetDC(), 0, 0, pstrMessage, lstrlen(pstrMessage));

            BitBlt(
                hDC,                // handle to destination device context
                0,                  // x-coordinate of upper-left corner of dest. rect.
                0,                  // y-coordinate of upper-left corner of dest. rect.
                pwi->nWidth,        // width of destination rectangle
                pwi->nHeight,       // height of destination rectangle
                pIDCLock->GetDC(),  // handle to source device context
                0,                  // x-coordinate of upper-left corner of source rectangle
                0,                  // y-coordinate of upper-left corner of source rectangle  
                SRCCOPY);           // raster operation code

            SAFE_RELEASE(pIDCLock);
            EndPaint(hWnd, &ps);
            return 0;
        }

        case WM_CHAR:
            if(wParam == VK_ESCAPE)
                PostMessage(hWnd, WM_CLOSE, 0, 0);
            return 0;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_FILE_EXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    break;

                case ID_FILE_ABOUT:
                    MessageBox(hWnd, TEXT("DXSurface Sample 3 Version 1.0\n"
                                          "Copyright (c) 1998 Microsoft Corporation.\n"
                                          "All rights reserved."), 
                                          TEXT("DXSurface Sample 3"), 
                                          MB_ICONINFORMATION | MB_OK);
                    break;
            }
            return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////
BOOL ParseCommandLine(WININFO* pwi, PTSTR pszCmdLine)
///////////////////////////////////////////////////////////////////////////////
// Go through the command line, setting pertinent info in WININFO structure.
{
    pwi->nWidth = FindNumWithParameter(TEXT("-width"));
    pwi->nHeight = FindNumWithParameter(TEXT("-height"));
    pwi->nBPP   = FindNumWithParameter(TEXT("-bpp"));
    pwi->bWindowed = FindParameter(TEXT("-windowed"));

    if(pwi->nWidth < 0  ||  pwi->nHeight < 0  ||  pwi->nBPP < 0)
    {
        // Get the current display settings.
        HDC hDC = GetDC(NULL);
        int nCurrentBPP = GetDeviceCaps(hDC, BITSPIXEL);
        ReleaseDC(NULL, hDC);

        // Set to a default resolution of 640x480 windowed.
        pwi->nWidth = 640;
        pwi->nHeight = 480;
        pwi->nBPP = nCurrentBPP;
        pwi->bWindowed = TRUE;
    }
    else if(pwi->bWindowed == -1)
        pwi->bWindowed = FALSE;

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
BOOL InitInstance(WININFO* pwi, PTSTR strClassName)
///////////////////////////////////////////////////////////////////////////////
// Register the window class and possibly change the video mode,
// taking into acount WININFO.
{
    BOOL        bRet = FALSE;
    DEVMODE     devmode;
    WNDCLASSEX  wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc,
                            0, 0, pwi->hInstance, 
                            LoadIcon(pwi->hInstance, MAKEINTRESOURCE(IDI_DXS3)), 
                            LoadCursor(NULL, IDC_ARROW),
                            NULL, NULL, strClassName, 0 };

    if(!RegisterClassEx(&wcex))
        goto EXIT_FAIL;

    if(!pwi->bWindowed)
    {
        ZeroMemory(&devmode, sizeof(devmode));
        devmode.dmSize          = sizeof(DEVMODE);
        devmode.dmBitsPerPel    = pwi->nBPP;
        devmode.dmPelsWidth     = pwi->nWidth;
        devmode.dmPelsHeight    = pwi->nHeight;
        devmode.dmFields        = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        if(ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            MessageBox(NULL, TEXT("Failed to set the display mode!\n"
                       "See dxsurf3.txt for how to choose another."), 
                       TEXT("DXSurface Sample 3"), MB_OK);
            goto EXIT_FAIL;
        }
        ShowCursor(FALSE);
    }

    bRet = TRUE;
EXIT_FAIL:
    return bRet;
}

///////////////////////////////////////////////////////////////////////////////
int FindNumWithParameter(PTSTR strParam)
///////////////////////////////////////////////////////////////////////////////
// Returns the number associated with a command-line parameter, e.g. 
// returns the number 640 when passed a string "-width 640".  
// If the string is not found, -1 is returned.
{
    // TODO: Check that argv[i+1] is not past end of string AND that it
    // is a positive string of numbers.
    for(int i=0; i<__argc; i++)
    {
        if(lstrcmpi(strParam, __argv[i]) == 0)
            if(i+1 < __argc)
                return atoi(__argv[i+1]);
            else // We're at the end of the command line string.
                break;;
    }

    return -1;
}

///////////////////////////////////////////////////////////////////////////////
int FindParameter(PTSTR strParam)
///////////////////////////////////////////////////////////////////////////////
// Returns -1 if parameter not found, else 1.
{
    for(int i=0; i<__argc; i++)
    {
        if(lstrcmpi(strParam, __argv[i]) == 0)
            return 1;
    }

    return -1;
}

/////////////////////////////////////////////////////////////
void GetImageDirectoryAndFileName(PWSTR wszImageDirAndFileName, PCWSTR wszFileName)
/////////////////////////////////////////////////////////////
// This function retrieves the directory where the SDK images
// are located and appends the file name to the end of this
// directory.  This is intended for use with IDXSurfaceFactory::LoadImage()
// which takes absolute paths to images.
// NOTE: This function returns a (Unicode) wide character string.
{
    unsigned char   szImagePath[256] = "";
    HKEY            hkey;
    LONG            lResult;
    DWORD           dwImagePathSize = 256;

    // Open the reg key.
    lResult  = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                        "Software\\Microsoft\\Multimedia\\DirectXMedia", 0, 
                        KEY_READ, 
                        &hkey);

    if(ERROR_SUCCESS != lResult)
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
