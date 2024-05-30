/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    bitmapwin.h

Abstract:
    
    Header file

--*/

#ifndef BITMAPWIN_H
#define BITMAPWIN_H

//
// Global variables
//

// Handle to the current instance of the application
extern HINSTANCE g_hInstance;

//
// TWAIN interface states
//

typedef enum _TWAINSTATE {

    State_1_Pre_Session           = 1,
    State_2_Source_Manager_Loaded = 2,
    State_3_Source_Manager_Open   = 3,
    State_4_Source_Open           = 4,
    State_5_Source_Enabled        = 5,
    State_6_Transfer_Ready        = 6,
    State_7_Transferring          = 7,

} TWAINSTATE;


//
// display monitor data
//

typedef struct _MONITORDATA {

    TCHAR       szName[CCHDEVICENAME];  // name of the monitor
    HPALETTE    hPalette;               // color palette 
    HBITMAP     hDIBSect;               // DIB converted to the 
                                        // current display format

#ifdef ICM_ENABLED
    TCHAR       szProfile[MAX_PATH];    // ICM color profile
#endif //ICM_ENABLED

#ifdef MULTIMON_ENABLED
    RECT        rMonitorScreen;         // monitor boundaries rectangle 
                                        // in screen coordinates
    RECT        rMonitorClient;         // monitor boundaries rectangle 
                                        // in window client area coordinates
#endif //MULTIMON_ENABLED

} MONITORDATA, *PMONITORDATA;


//
// BitmapWindow struct
//

typedef struct _BITMAPWINDOW {

#ifdef DEBUG
    DWORD           m_dwValid;   // debug field to test the proper 
                                 // initialization of the struct
#endif //DEBUG

    PBYTE           m_pDIB;       // pointer to RAW DIB data
    DWORD           m_dwOffBits;  // offset of the bitmap pixel data from 
                                  // the start of the m_pDIB
    DWORD           m_nImageW;    // width of the image
    DWORD           m_nImageH;    // height of the image
    
    PLOGPALETTE     m_pLogPal;    // image palette

    TCHAR           m_szFileName[MAX_PATH]; // image file name
    BOOL            m_bIsDirty;   // modified flag

    HICON           m_hIcon;      // handle to the window icon

    HWND            m_hWnd;       // handle to the window

    BOOL            m_bUpdatingScrollBars;  // used for avoiding recursion
                                           // during WM_SIZE message handling

    DWORD           m_nMouseXPos; // last mouse pointer location
    DWORD           m_nMouseYPos; // used in panning the image

    TW_IDENTITY     m_AppId;      // TWAIN id for the application
    TW_IDENTITY     m_SrcId;      // TWAIN current data source id

    TWAINSTATE      m_TwainState; // current TWAIN interface state

    HANDLE          m_hDevMode;   // printer device data
    HANDLE          m_hDevNames;  // printer device names
    RECT            m_rMargin;    // printable area margins

    DWORD           m_dwFlags;    // settings

#ifdef ICM_ENABLED
    BOOL            m_bDisableICM;                
    BOOL            m_bEnableProofing;            
    LCSGAMUTMATCH   m_lcsRenderIntent;
    LCSGAMUTMATCH   m_lcsProofIntent;             
    TCHAR           m_szPrinterName[MAX_PATH];    
    TCHAR           m_szPrinterProfile[MAX_PATH];
    TCHAR           m_szTargetProfile[MAX_PATH]; 
    TCHAR           m_szScannerProfile[MAX_PATH];
#endif //ICM_ENABLED

    int             m_nNumMonitors;  // number of display monitors
    MONITORDATA     m_Monitor[1];    // variable length (at least 1) array 
                                     // to hold monitor data

} BITMAPWINDOW, *PBITMAPWINDOW;


//
// window creation types
//

typedef enum _BitmapWindow_eOpenMethod {

    eOpenEmpty,
    eReadFromFile,
    ePasteFromClipboard,
    eAcquireFromTwain,
    eAttachToDIB

} BitmapWindow_eOpenMethod;


//
// setting flags
//

#define  BWF_STRETCHTOWINDOW    1
#define  BWF_KEEPASPECTRATIO    2
#define  BWF_AUTORESIZEWINDOW   4


//
// Construction / destruction (implementation in construct.c)
//

BOOL 
CreateBitmapWindow(
    int                      nCmdShow,
    BitmapWindow_eOpenMethod eOpenMethod,
    PCTSTR                   pFileName
);

BOOL
BitmapWindow_Construct(
    PBITMAPWINDOW pWin,
    int           nNumMonitors
);

BOOL
BitmapWindow_Destruct(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_DeleteContents(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_AssertValid(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_RegisterClass();

BOOL
BitmapWindow_Create(
    PBITMAPWINDOW pWin
);

#ifdef MULTIMON_ENABLED

PBITMAPWINDOW
BitmapWindow_ResizeStruct(
    PBITMAPWINDOW pWin,
    int           nNumMonitors
);

BOOL
CALLBACK
BitmapWindow_MonitorEnumProc(
    HMONITOR hMonitor,
    HDC      hdcMonitor,
    PRECT    prcMonitor,
    LPARAM   dwData
);

#endif //MULTIMON_ENABLED

//
// Window message handling (implementation in construct.c)
//

LRESULT 
CALLBACK 
BitmapWindow_WindowProc(  
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
);

BOOL 
CALLBACK 
BitmapWindow_DestroyWindow(  
    HWND   hWnd,
    LPARAM lParam
);

BOOL
BitmapWindow_ApplyPalette(
    PBITMAPWINDOW pWin,
    BOOL          bForceBackground
);

BOOL
BitmapWindow_OnPaint(
    PBITMAPWINDOW pWin
);

BOOL
CALLBACK
BitmapWindow_DisplayBitmap(
    PBITMAPWINDOW pWin,
    int           nIndex,
    HDC           hDC,
    LPARAM        lParam
);

BOOL
BitmapWindow_OnDisplayChange(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnMove(
    PBITMAPWINDOW pWin
);

VOID
BitmapWindow_OnSize(
    PBITMAPWINDOW pWin,
    DWORD         fwSizeType,
    DWORD         nWidth,
    DWORD         nHeight
);

BOOL
BitmapWindow_OnScroll(
    PBITMAPWINDOW pWin,
    int           fnBar,
    INT           nScrollCode
);

BOOL
BitmapWindow_OnMouseWheel(
    HWND  hWnd,
    short zDelta
);

VOID
BitmapWindow_OnLButtonDown(
    PBITMAPWINDOW pWin,
    short         xPos,
    short         yPos
);

BOOL
BitmapWindow_OnMouseMove(
    PBITMAPWINDOW pWin,
    DWORD         fwKeys,
    short         xPos,
    short         yPos
);

int
MoveScrollBar(
    HWND hWnd,
    int  fnBar,
    int  nDisplacement
);

BOOL
BitmapWindow_AdjustWindowSize(
    PBITMAPWINDOW pWin
);

//
//  Document handling (implementation in document.c)
//

BOOL
BitmapWindow_OnFileOpen(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnFileSave(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnFileSaveAs(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_CanClose(
    PBITMAPWINDOW pWin
);

VOID
BitmapWindow_OnDropFiles(
    PBITMAPWINDOW pWin,
    HDROP         hDrop
);

BOOL
BitmapWindow_OpenDocument(
    PBITMAPWINDOW            pWin,
    BitmapWindow_eOpenMethod eOpenMethod,
    PCTSTR                   pFileName
);

// TWAIN functions  (implementation in twain.c)

BOOL 
BitmapWindow_FillTwainInfo(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnSelectSource(
    PBITMAPWINDOW pWin
);

#ifdef ICM_ENABLED

BOOL
BitmapWindow_OnSelectSource_STI(
    PBITMAPWINDOW pWin
);

#endif //ICM_ENABLED

BOOL
BitmapWindow_OnSelectSource_Twain(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnAcquire(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_AcquireDIB(
    PBITMAPWINDOW pWin
);

TW_UINT16
SetCapOneValue(
    pTW_IDENTITY pOrigin,
    pTW_IDENTITY pDest,
    TW_UINT16    Cap,
    TW_UINT16    ItemType,
    TW_UINT32    Item
);

TW_UINT16
GetCapOneValue(
    pTW_IDENTITY pOrigin,
    pTW_IDENTITY pDest,
    TW_UINT16    Cap,
    pTW_UINT16   pItemType,
    pTW_UINT32   pItem
);

// Clipboard operations (implementation in clipboard.c)

BOOL
BitmapWindow_PasteFromClipboard(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_CopyToClipboard(
    PBITMAPWINDOW pWin
);

// DIB operations (implementation in dib.c)

BOOL
BitmapWindow_ProcessHeader(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_CreateDDB(
    PBITMAPWINDOW pWin,
    int           nIndex
);

HBITMAP
CreateCompatibleDIBSection(
    HDC         hDC,
    int         nWidth,
    int         nHeight,
#ifdef ICM_ENABLED 
    PCTSTR      pProfileName,
#endif //ICM_ENABLED 
    PLOGPALETTE plp
);

VOID
CenterBitmap(
    int   nImageW,
    int   nImageH,
    PRECT pRect,
    BOOL  bStretch,
    BOOL  bKeepAspectRatio
);

BOOL
DrawDDB(
    HDC      hDC,
    HBITMAP  hBitmap,
    HPALETTE hPalette,
    int      nImageW,
    int      nImageH,
    PRECT    pRect
);

BOOL
DrawDIB(
    HDC         hDC,
    PBYTE       pDIB,
    DWORD       dwOffset,
    HPALETTE    hPalette,
    PRECT       pRect
);

BOOL
CreatePaletteAndDrawDIB(
    HDC         hDC,
    PBYTE       pDIB,
    DWORD       dwOffBits,
    PLOGPALETTE pLogPal,
    HPALETTE    *phPalette,
    PRECT       pRect
);

//
// Printing operations (implementation in print.c)
//

BOOL
BitmapWindow_GetDefaultPrinter(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnPageSetup(
    PBITMAPWINDOW pWin
);

UINT 
CALLBACK 
BitmapWindow_PagePaintHook(  
    HWND   hdlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
);

BOOL
CALLBACK
BitmapWindow_PrintPreview(
     PBITMAPWINDOW pWin,
     int           nIndex,
     HDC           hDC,
     LPARAM        lParam
);

BOOL
BitmapWindow_OnPrint(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_PrintBitmap(
    PBITMAPWINDOW pWin,
    HDC           hDC
);

//
// User defined settings handling (implementation in settings.c)
//

BOOL
BitmapWindow_ReadRegistrySettings(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_SaveRegistrySettings(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnInitMenu(
    PBITMAPWINDOW pWin,
    HMENU         hMenu
);

BOOL
BitmapWindow_OnStretchToWindow(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnKeepAspectRatio(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_OnAutoResizeWindow(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_ToggleMenuItem(
    PBITMAPWINDOW pWin,
    DWORD dwFlag,
    UINT uItem
);

//
// Window icon (implementation in icon.c)
//

BOOL
BitmapWindow_CreateIcon(
    PBITMAPWINDOW pWin
);

//
// About dialog (implementation in about.c)
//

BOOL
BitmapWindow_OnHelpAbout(
    PBITMAPWINDOW pWin
);

//
// MultiMonitor support (implementation in mmon.c)
//

typedef BOOL (CALLBACK *MULTIMONCALLBACK)(PBITMAPWINDOW, int, HDC, LPARAM);

BOOL 
BitmapWindow_MultimonCall(
    MULTIMONCALLBACK pfnCallback,
    PBITMAPWINDOW    pWin,
    HDC              hDC,
    LPARAM           lParam
);

//
// ICM functions (implementation in icm.c)
//

#ifdef ICM_ENABLED

BOOL
BitmapWindow_OnColorSetup(
    PBITMAPWINDOW pWin,
    int           nMonitor
);

BOOL
BitmapWindow_OnCMMManager(
     PBITMAPWINDOW pWin
);

BOOL 
WINAPI 
ApplyCallbackFunction(  
    PCOLORMATCHSETUP pcms,
    LPARAM           lParam
);

BOOL
BitmapWindow_FillMonitorICMInfo(
     PBITMAPWINDOW pWin,
     int           nIndex
);

BOOL
BitmapWindow_FillPrinterICMInfo(
    PBITMAPWINDOW pWin
);

BOOL 
BitmapWindow_FillTwainICMInfo(
    PBITMAPWINDOW pWin
);

BOOL
GetDeviceValue_ReAlloc(
    IStillImage *pSti,
    PWSTR       pDeviceName,
    PWSTR       pValueName,
    PBYTE       *ppBuffer
);

BOOL 
GetDefaultICMProfile(
    HDC   hDC,
    PTSTR pProfileName,
    DWORD dwBufferSize
);

BOOL
EnumColorProfiles_ReAlloc(
    PENUMTYPE pet,
    PBYTE     *ppBuffer
);

BOOL
ModifyDIBColorSpace(
    PBYTE           pOldDIB,
    DWORD           dwOldOffBits,
    LPLOGCOLORSPACE plcs,
    PBYTE           *ppNewDIB,
    DWORD           *pdwNewOffBits
);

BOOL
GetColorSpaceFromDIB(
    PBYTE           pDIB,
    LPLOGCOLORSPACE plcs,
    PBOOL           pbTemporaryFileCreated
);

BOOL
SaveEmbeddedProfileToTempFile(
    PVOID pProfileData,
    DWORD dwProfileSize,
    PTSTR pFileName
);

BOOL
GetFullColorProfileName(
    PCTSTR pProfileName,
    PTSTR  pPathName,
    PDWORD pdwSize
);

BOOL
CreatePaletteAndDrawDIB_ICM(
    HDC           hDC,
    PBYTE         pDIB,
    DWORD         dwOffBits,
    PLOGPALETTE   pLogPal,
    HPALETTE      *phPalette,
    PRECT         pRect,
    PTSTR         pDestProfileName,
    LCSGAMUTMATCH lcsDestIntent,
    PTSTR         pTargetProfileName,
    LCSGAMUTMATCH lcsTargetIntent
);

BOOL
BitmapWindow_EditColorSpace(
    PBITMAPWINDOW pWin
);

#ifdef ICM_OUTSIDE_DC

BOOL
ColorTransformDIB(
    PBYTE         pOldDIB,
    DWORD         dwOffBits,
    PLOGPALETTE   pOldLogPal,
    PBYTE         *ppNewDIB,
    PLOGPALETTE   *ppNewLogPal,
    PCTSTR        pDestProfileName,
    LCSGAMUTMATCH lcsDestIntent,
    PCTSTR        pTargetProfileName,
    LCSGAMUTMATCH lcsTargetIntent,
    HWND          hWnd
);

BOOL 
WINAPI 
ICMProgressProcCallback(  
    ULONG  ulMax,  
    ULONG  ulCurrent,
    LPARAM ulCallbackData
);

HPROFILE
OpenColorProfileFromFile(
    PCTSTR pProfileName
);

BOOL
BitmapWindow_TransformDIB(
    PBITMAPWINDOW pWin
);

BOOL
BitmapWindow_ProfileToProfile(
    PBITMAPWINDOW pWin
);


#endif //ICM_OUTSIDE_DC

#endif //ICM_ENABLED

#endif //BITMAPWIN_H
