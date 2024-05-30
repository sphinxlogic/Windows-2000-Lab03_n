#include "globals.h"

//
// Message handlers and WndProc
//
LPARAM CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL HandleInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam);
void HandleSize(HWND hWnd, UINT state, int nWidth, int nHeight);
void HandleCommand(HWND hWnd, int id, HWND hWndControl, UINT codeNotify);
void HandleDrawItem( HWND hwnd, const DRAWITEMSTRUCT *lpDrawItem );
void HandleClose(HWND hWnd);
void HandleDestroy(HWND hWnd);

//
// Handle actions from controls (ie buttons, etc)
//
void HandleTrackBar( HWND, HWND, UINT, int );
void HandlePlayForward( void );
void HandlePlayBackward( void );
void HandleProperties( void );

//
// Other local prototypes
//
void UpdateSettings( void );
BOOL CheckImages( void );

//
// Handy macros
//
// Only use this on interfaces where the RefCount == 1
#define SAFE_RELEASE( ptr )         \
{                                   \
        if (ptr) ptr->Release();    \
        ptr=NULL;                   \
}


// ---------------------------------------------------------------------------
// WinMain
// ---------------------------------------------------------------------------
// Description:         Program entry point.
// Arguments:
//  HINSTANCE [in]      Program instance handle.
//  HINSTANCE [in]      Unused in Win32.
//  LPSTR [in]          Program command line.
//  int [in]            Command to pass to ShowWindow().
// Returns:
//  int                 0 if all goes well.
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND                hWnd = NULL;
    MSG                 msg;
    WNDCLASSEX          wc;
    
    InitCommonControls();

    // Register the window class
    ZeroMemory( &wc, sizeof(wc) );
    wc.cbSize = sizeof(wc);
    GetClassInfoEx(NULL, WC_DIALOG, &wc);
    wc.lpfnWndProc      = MainWndProc;
    wc.hInstance        = hInst;
    wc.hIcon            = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = _T("WipeDlg");
    wc.hIconSm          = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON));

    if(!RegisterClassEx(&wc))
        goto failure;

    // Create the main window
    hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_WIPEDLG), NULL, (DLGPROC)MainWndProc);

    if(!hWnd || !g_pSurfFact)
        goto failure;

    // Make the window visible
    if(nCmdShow == SW_MINIMIZE)
        ShowWindow(hWnd, SW_MINIMIZE);
    else
        ShowWindow(hWnd, SW_RESTORE);

    UpdateWindow(hWnd);


    // Enter the message loop
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        if(!IsDialogMessage(hWnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


failure:

    SAFE_RELEASE(g_pTransFact)
    SAFE_RELEASE(g_pSurfFact)
    SAFE_RELEASE(g_pInSurfA)
    SAFE_RELEASE(g_pInSurfB)
    SAFE_RELEASE(g_pOutSurf)
    SAFE_RELEASE(g_pWipeTrans)
    SAFE_RELEASE(g_pEffect)

    // Close the window
    DestroyWindow(hWnd);
    
    // Return 0
    return 0;
}


// ---------------------------------------------------------------------------
// MainWndProc
// ---------------------------------------------------------------------------
// Description:         Main window procedure.
// Arguments:
//  HWND [in]           Window handle.
//  UINT [in]           Message identifier.
//  WPARAM [in]         Depends on message.
//  LPARAM [in]         Depends on message.
// Returns:
//  LPARAM              Depends on message.
LPARAM CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL                    bHandled = TRUE;

    // Call the appropriate message handler
    switch(uMsg)                                                    
    {
        HANDLE_MSG( hwnd, WM_INITDIALOG, HandleInitDialog );
        HANDLE_MSG( hwnd, WM_SIZE, HandleSize );
        HANDLE_MSG( hwnd, WM_COMMAND, HandleCommand );
        HANDLE_MSG( hwnd, WM_DRAWITEM, HandleDrawItem );
        HANDLE_MSG( hwnd, WM_CLOSE, HandleClose );      
        HANDLE_MSG( hwnd, WM_DESTROY, HandleDestroy );
        HANDLE_MSG( hwnd, WM_HSCROLL, HandleTrackBar );
    }

    // Call the default message handler
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


/////////////////////////////////////////////////////////////////
BOOL HandleInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
/////////////////////////////////////////////////////////////////
{
    HRESULT     hr  = S_OK;

    // Store the dialog handle
    g_hDlg  = hWnd;

    // Initialize the "Percent Complete" slider
    SendDlgItemMessage( hWnd, IDS_PCTCOMP, TBM_SETRANGE, TRUE, MAKELONG( 0, 100 ) );
    SendDlgItemMessage( hWnd, IDS_PCTCOMP, TBM_SETTICFREQ, 20, 0 );

    CoInitialize(NULL);

    // Create the transform factory
    hr = CoCreateInstance( CLSID_DXTransformFactory, NULL, CLSCTX_INPROC,
                             IID_IDXTransformFactory, (void **)&g_pTransFact );
    _ASSERTE( g_pTransFact != NULL );

    if( SUCCEEDED( hr ) )
    {
        //--- Get the surface factory interface
        hr = g_pTransFact->QueryService( SID_SDXSurfaceFactory, IID_IDXSurfaceFactory, (void **)&g_pSurfFact );
        _ASSERTE( g_pSurfFact != NULL );
    }

    // Create the wipe transform and set it up
    if( SUCCEEDED( hr ) )
    {
        hr = g_pTransFact->CreateTransform( NULL, 0, NULL, 0, NULL, NULL,
                                           CLSID_DXTWipeSample, IID_IDXTransform,
                                           (void **)&g_pWipeTrans );
        _ASSERTE( g_pWipeTrans != NULL );
    }

    //
    // Get the Effect interface.  We'll use this to set
    // execution properties for the effect (ie PercentComplete, Duration)
    //
    if( SUCCEEDED( hr ) )
    {
        hr = g_pWipeTrans->QueryInterface( IID_IDXEffect, (void **)&g_pEffect );
        _ASSERTE( g_pEffect != NULL );

        // Update the dialog with our current settings
        UpdateSettings();
    }

    return SUCCEEDED(hr);
}


/////////////////////////////////////////////////////////////////
void HandleSize(HWND hWnd, UINT state, int nWidth, int nHeight)
/////////////////////////////////////////////////////////////////
{
    DWORD           DCWidth, DCHeight;

    HRESULT hr = S_OK;
    HWND    hOwnerDraw = GetDlgItem(hWnd, IDB_OWNERDRAW);
    RECT    rectOwnerDraw, rectDialog;

    DWORD   x=250, y=10, gap=10;

    // Resize the image window, based on the dialog size
    GetClientRect( hWnd, &rectDialog );
    GetClientRect( hOwnerDraw, &rectOwnerDraw );

    DCWidth     = rectDialog.right-gap-x;   
    DCHeight    = rectDialog.bottom-gap-y;

    MoveWindow( hOwnerDraw, x, y, DCWidth, DCHeight, TRUE );

    // Create Output surface
    SAFE_RELEASE(g_pOutSurf);
    CDXDBnds bnds;
    bnds.SetXYSize(DCWidth, DCHeight);
    hr = g_pSurfFact->CreateSurface(    NULL, NULL, &DDPF_PMARGB32, &bnds, 0, NULL,
                                        IID_IDXSurface, (void**)&g_pOutSurf );

    if (g_pInSurfA && g_pInSurfB)
    {
        // Setup the transform
        // Give it an array of inputs, and an array of outputs
        // Since Setup doesn't know what type of inputs/outputs we're
        // providing (ie surfaces or meshes), we provide an
        // array of IUnknowns, and the transform QIs for the stuff
        // it needs.
        if( SUCCEEDED( hr ) )
        {
            IUnknown* In[2];
            IUnknown* Out[1];
            In[0] = g_pInSurfA;
            In[1] = g_pInSurfB;
            Out[0]= g_pOutSurf;
            hr = g_pWipeTrans->Setup( In, 2, Out, 1, 0 );
        }
    }

    HandleDrawItem(NULL, NULL);

    return;
}


/////////////////////////////////////////////////////////////////
void HandleCommand(HWND hWnd, int id, HWND hWndControl, UINT codeNotify)
/////////////////////////////////////////////////////////////////
{
    TCHAR   szFileName[256]=_T("");
    TCHAR   szTitleName[256]=_T("");

    switch(id)
    {
        case IDOK:
            PostMessage( g_hDlg, WM_CLOSE, 0, 0 ) ;
            break;

        case IDB_PLAYFWD:
            HandlePlayForward( );
            break;

        case IDB_PLAYBKWD:
            HandlePlayBackward( );
            break;

        case IDB_PROPERTIES:
            HandleProperties( );
            break;

        case IDM_IMAGEA:
        case IDM_IMAGEB:
            IDXSurface  **ppSurface     = NULL;
            TCHAR       szError[256]    = _T("");

            if (id == IDM_IMAGEA)
            {
                ppSurface = &g_pInSurfA;
                _tcscpy(szError, _T("Couldn't read Image A\n"));
            }
            else
            {
                ppSurface = &g_pInSurfB;
                _tcscpy(szError, _T("Couldn't read Image B\n"));
            }

            InitializeFileOpenDlg( g_hDlg );
            if (PopFileOpenDlg (g_hDlg, szFileName, szTitleName))
            {
                if (!ReadImageFile (ppSurface, szFileName))
                    MessageBox( g_hDlg, szError, _T("Load Error"), MB_ICONERROR );
            }

            // If we have both surfaces, force send a resize
            // to force Setup and Repaint.
            HandleSize( g_hDlg, 0, 0, 0 );
            break;
    }

    return;
}


/////////////////////////////////////////////////////////////////
void HandleDrawItem( HWND hwnd, const DRAWITEMSTRUCT *lpDrawItem )
/////////////////////////////////////////////////////////////////
//
// Gets a Display Context from the owner draw button
// on the dialog, then executes a frame of the transform
// and blits the result over the owner draw button
// 
// The arguments are ignored.
{
    HDC                 hdc         = NULL;
    HRESULT             hr          = S_OK;
    HDC                 hdcSurf     = NULL;
    IDirectDrawSurface  *pDDSurf    = NULL;
    HWND                hOwnerDraw  = NULL;
    DWORD               DCWidth, DCHeight;
    RECT                rect;

    // If we don't have an output surface, bail
    if ( !g_pOutSurf )
        return;

    // Get the handle and size of the owner draw button
    hOwnerDraw  = GetDlgItem( g_hDlg, IDB_OWNERDRAW );
    GetClientRect( hOwnerDraw, &rect );
    DCWidth     = rect.right;
    DCHeight    = rect.bottom;

    // Get the Display Context so we have someplace to blit.
    hdc = GetDC(hOwnerDraw);

    // Erase the output surface with a color.
    DXFillSurface( g_pOutSurf, 0xFFC0C0FF, false );

    //--- Test unlocking the transform
    //  Note: Duplication of the "Copyright" string is illegal, we are copying
    //        our own string for test purposes
    static BSTR g_Notice( L"Copyright Microsoft Corporation 1998, Unauthorized duplication of this string is illegal {AF279B30-86EB-11D1-81BF-0000F87557DB}" );
    IDXTWipeSample* pWipe;
    
    hr = g_pWipeTrans->QueryInterface( IID_IDXTWipeSample, (void**)&pWipe );
    if ( SUCCEEDED(hr) )
    {
        hr = pWipe->put_Copyright( g_Notice );
        pWipe->Release();
    }

    //--- Execute if we have our inputs
    if (g_pInSurfA && g_pInSurfB)
    {
        // Execute the transform
        DXVEC Placement = { DXBT_DISCRETE, 0 };

        hr = g_pWipeTrans->Execute( NULL, NULL, &Placement );
    }

    if( SUCCEEDED( hr ) )
    {
        // Get the DirectDraw surface from our output DXTransform surface
        hr = g_pOutSurf->GetDirectDrawSurface( IID_IDirectDrawSurface, (void**)&pDDSurf );
        if( SUCCEEDED( hr ) )
        {
            // Get the DC from the DirectDraw surface
            hr = pDDSurf->GetDC( &hdcSurf );
        }
    }

    if( SUCCEEDED( hr ) )                                            
    {
        // Blit the output surface to our DC on the screen
        BOOL bStat = BitBlt( hdc, 0, 0, DCWidth, DCHeight,
                               hdcSurf, 0, 0, SRCCOPY );
        hr = pDDSurf->ReleaseDC( hdcSurf );
    }

    // If we don't have both input images, let the user know...
    SetTextAlign( hdc, TA_CENTER );

    if ( !g_pInSurfA )
        TextOut( hdc, DCWidth/2, (DCHeight/2) - 20, _T("Need to Load Image A"), 20 ); 

    if ( !g_pInSurfB )
        TextOut( hdc, DCWidth/2, (DCHeight/2), _T("Need to Load Image B"), 20 ); 

    if( hr == DXTERR_COPYRIGHT_IS_INVALID  )
        TextOut( hdc, DCWidth/2, (DCHeight/2) - 40, _T("Copyright is invalid"), 20 ); 

    // Clean up and get outta here
    ReleaseDC( hOwnerDraw, hdc );
    SAFE_RELEASE( pDDSurf );

    return;
}


/////////////////////////////////////////////////////////////////
void HandleClose(HWND hWnd)
/////////////////////////////////////////////////////////////////
{
    // Terminate the app
    PostQuitMessage(0);

    // Return success
    return;
}


/////////////////////////////////////////////////////////////////
void HandleDestroy(HWND hWnd)
/////////////////////////////////////////////////////////////////
{
    CoUninitialize();

    // Return success
    return;                                                           
}


/////////////////////////////////////////////////////////////////
void HandleTrackBar( HWND hwnd, HWND hctl, UINT code, int pos)
/////////////////////////////////////////////////////////////////
{
    int     nPosition   = pos;
    TCHAR   szString[256];

    if ( (code == SB_THUMBPOSITION) && !CheckImages() )
        return;

    nPosition   = SendMessage( hctl, TBM_GETPOS, 0, 0 );
    _stprintf(szString, _T("Percent Complete: %u%%"), nPosition);
    SetDlgItemText( hwnd, IDT_PCTCOMP, szString);

    g_pEffect->put_Progress( (float)(nPosition/100.0) );

    HandleDrawItem( NULL, NULL );

    return;
}


/////////////////////////////////////////////////////////////////
void HandlePlayForward( void )
/////////////////////////////////////////////////////////////////
{
    float Duration, PercentComplete = 0;
    DWORD msStartTime = timeGetTime();
    ULONG ulFrames = 0;

    if (CheckImages())
    {
        // This duration can be set via the property page for
        // the effect.  It defaults to .50
        g_pEffect->get_Duration( &Duration );

        do
        {
            // Set percent complete
            g_pEffect->put_Progress( PercentComplete );

            // Cause repaint
            HandleDrawItem( NULL, NULL );

            // Next
            PercentComplete = (float)(( (timeGetTime() - msStartTime) / 1000. ) / Duration);
            ++ulFrames;
        }
        while( PercentComplete <= 1. );

        // Update the dialog with our frame rate.
        TCHAR szFrames[20];
        _stprintf( szFrames, _T("Frames/Sec = %.2f"), (double)ulFrames / Duration );
        SetDlgItemText( g_hDlg, IDT_FRAMES_PER_SEC, szFrames );
    }

    return;
}


/////////////////////////////////////////////////////////////////
void HandlePlayBackward( void )
/////////////////////////////////////////////////////////////////
{
    float Duration, PercentComplete = 1.0;
    DWORD msStartTime = timeGetTime();
    ULONG ulFrames = 0;

    if ( CheckImages() )
    {
        // This duration can be set via the property page for
        // the effect.  It defaults to .50
        g_pEffect->get_Duration( &Duration );

        do
        {
            // Set percent complete
            g_pEffect->put_Progress( PercentComplete );

            // Cause repaint
            HandleDrawItem( NULL, NULL );

            // Next
            PercentComplete = 1.f - (float)(( (timeGetTime() - msStartTime) / 1000. ) / Duration);
            ++ulFrames;
        }
        while( PercentComplete >= 0. );

        // Float division never gets to exactly 0
        g_pEffect->put_Progress( 0.0 );
        HandleDrawItem( NULL, NULL );


        TCHAR szFrames[20];
        _stprintf( szFrames, _T("Frames/Sec = %.2f"), (double)ulFrames / Duration );
        SetDlgItemText( g_hDlg, IDT_FRAMES_PER_SEC, szFrames );
    }

    return;
}


/////////////////////////////////////////////////////////////////
void HandleProperties( void )
/////////////////////////////////////////////////////////////////
// Display the property page which is stored in the effect.
//
{
    ISpecifyPropertyPages *pSpecPropPages;

    if( S_OK == g_pWipeTrans->QueryInterface( IID_ISpecifyPropertyPages,
                                              (void **)&pSpecPropPages))
    {
        CAUUID cauuid;
        HRESULT hr;
        
        hr  = pSpecPropPages->GetPages(&cauuid);
        SAFE_RELEASE( pSpecPropPages );

        if( SUCCEEDED(hr) )
        {
            OleCreatePropertyFrame( g_hDlg, 0, 0, L"Testing",
                                    1, (IUnknown **)&g_pWipeTrans,  
                                    cauuid.cElems, cauuid.pElems,
                                    GetUserDefaultLCID(), 0, NULL);
            CoTaskMemFree(cauuid.pElems);
        }
    }

    // Float division never gets to exactly 1.0
    g_pEffect->put_Progress( 1.0 );
    HandleDrawItem( NULL, NULL );

    // Update the dialog with the new settings
    UpdateSettings();

    // Force repaint
    HandleDrawItem( NULL, NULL );

    return;
}


/////////////////////////////////////////////////////////////////
void UpdateSettings( void )
/////////////////////////////////////////////////////////////////
//
// Update the text fields on the dialog w/
// information from the transform
//
{
    TCHAR   szString[20];
    float   fValue;

    g_pEffect->get_Duration(&fValue);
    _stprintf( szString, _T("Duration: %0.2f"), fValue);
    SetDlgItemText( g_hDlg, IDT_DURATION, szString );

    return;
}


BOOL CheckImages( )
{
    BOOL    bNeedA  = !g_pInSurfA;
    BOOL    bNeedB  = !g_pInSurfB;
    TCHAR   szError[256]=_T("");

    if (bNeedA && bNeedB)
        _tcscpy( szError, _T("Need to load both input images" ));
    else if (bNeedA)
        _tcscpy( szError, _T("Need to load input image A" ));
    else if (bNeedB)
        _tcscpy( szError, _T("Need to load input image B" ));
    else
        return TRUE;

    MessageBox( g_hDlg, szError, _T("Need inputs"), MB_ICONERROR );
    return FALSE;
}
