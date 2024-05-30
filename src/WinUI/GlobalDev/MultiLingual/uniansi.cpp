//
// UniAnsi.cpp 
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
//  Purpose:
//  This module contains wrapper functions that parallel selected Win32 API
//  "W" entry points for use on Windows 9x. The name of each function is the 
//  same as the Win32 API it mimicks, followed by AU. For example, LoadStringAU
//  should behave just as LoadStringW does under ideal condition (all characters
//  in all strings passed are in the system code page).
//
//  Most AU wrapper functions convert ANSI strings to/from Unicode using the 
//  system code page, and call the appropriate "A" entry point. Some, such as
//  SetWindowTextAU do so indirectly via another entry point. Those that take a
//  LPWSTR input as a resource ID, e.g. LoadAcceleratorsAU. convert via a cast 
//  from LPWSTR to LPSTR.
//
//  See the README.HTM file for more details
//

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "UNIANSI.H"

// Global variables used only in this module, not exported
UINT g_UICodePage    = CP_ACP ;
UINT g_InputCodePage = CP_ACP ;

// Utility routines used only in this module
BOOL CopyLfaToLfw  (LPLOGFONTA , LPLOGFONTW ) ;
BOOL CopyLfwToLfa  (LPLOGFONTW , LPLOGFONTA ) ;
UINT LangToCodePage(IN LANGID wLangID       ) ;

int  StandardUtoA  (LPCWSTR, int , LPSTR    ) ; // Default Unicode to ANSI conversion
//int  StandardAtoU(LPCSTR , int , LPWSTR   ) ; // Default ANSI to Unicode conversion (replaced by macro)

//
//  FUNCTION: DllMain
//
//  PURPOSE:  Standard DLLMain program
//
BOOL APIENTRY DllMain(HANDLE hDll, DWORD  dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) 
    {
        DisableThreadLibraryCalls((HMODULE) hDll) ;
    }

    return TRUE ;
}


//
//  FUNCTION: LoadStringAU
//
//  PURPOSE:  Wrapper over LoadStringA that mimics LoadStringW
//
int WINAPI LoadStringAU(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int nBufferMax)
{
    CHAR szBufferA[MAX_LOADSTRING]  ;

    int iLoadString ;
    int iMbToWc     ;

    // Get ANSI version of the string
    iLoadString = LoadStringA(hInstance, uID, szBufferA, MIN(MAX_LOADSTRING, nBufferMax) ) ;

    // Convert to Unicode
    iMbToWc = MultiByteToWideChar(CP_ACP, 0, szBufferA, iLoadString, lpBuffer, nBufferMax) ;

    // Null terminate
    lpBuffer[MIN(nBufferMax-1, iMbToWc)] = L'\0' ;

    return MIN(nBufferMax-1, iMbToWc) ;
}


//
//  FUNCTION: RegisterClassExAU
//
//  PURPOSE:  Wrapper over RegisterClassExA that mimics RegisterClassExW
//
//  COMMENTS: 
//      This is an important wrapper function; if you call this function,
//      any window that you create with the given class name will be an ANSI 
//      window, i.e., its WndProc will receive text from the system as ANSI. If 
//      your WndProc assumes Unicode you'll have to convert to/from Unicode
//      as appropriate.
//      You should not call this wrapper on Windows NT except when emulating
//      Windows 9x behavior for testing puposes.
//      See README.HTM for more on this.
// 
ATOM WINAPI RegisterClassExAU(CONST WNDCLASSEXW *lpWcw)
{
    WNDCLASSEXA wca                   ;
    CHAR        szClassName[MAX_NAME] ;

    // Set up ANSI version of class struct
    wca.cbSize       = sizeof(WNDCLASSEXA)  ;
    wca.cbClsExtra   = lpWcw->cbClsExtra    ;
    wca.cbWndExtra   = lpWcw->cbWndExtra    ;
    wca.hbrBackground= lpWcw->hbrBackground ;
    wca.hCursor      = lpWcw->hCursor       ;
    wca.hIcon        = lpWcw->hIcon         ;
    wca.hIconSm      = lpWcw->hIconSm       ;
    wca.hInstance    = lpWcw->hInstance     ;
    wca.lpfnWndProc  = lpWcw->lpfnWndProc   ;
    wca.style        = lpWcw->style         ;

    if(NULL == lpWcw->lpszClassName) 
    {
        return 0 ;
    }
    wca.lpszClassName   = szClassName ;


    // Convert class name from Unicode to ANSI using system code page
    if(!StandardUtoA(lpWcw->lpszClassName, MAX_NAME, szClassName))
    {
        return 0 ;
    }

    // Note: This doesn't work if the menu id is a string rather than a
    // constant
    wca.lpszMenuName = (LPSTR) lpWcw->lpszMenuName ; 

    return RegisterClassExA(&wca) ; // Register class as ANSI
}


//
//  FUNCTION: CreateWindowExAU
//
//  PURPOSE:  Wrapper over CreateWindowExA that mimics CreateWindowExW
//
HWND WINAPI CreateWindowExAU(  
  DWORD dwExStyle,      
  LPCWSTR lpClassNameW,  
  LPCWSTR lpWindowNameW, 
  DWORD dwStyle,        
  int x,                
  int y,                
  int nWidth,           
  int nHeight,          
  HWND hWndParent,      
  HMENU hMenu,          
  HINSTANCE hInstance,  
  LPVOID lpParam)
{
    CHAR szClassNameA [MAX_NAME]  ;
    CHAR szWindowNameA[MAX_NAME]  ;

    // Convert class name and Window name from Unicode to ANSI
    if(!StandardUtoA(lpClassNameW, MAX_NAME, szClassNameA) 
        ||
       !StandardUtoA(lpWindowNameW, MAX_NAME, szWindowNameA)
       ) 
    {
        return NULL ;
    }

    return CreateWindowExA(dwExStyle, szClassNameA, szWindowNameA,
        dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam) ;
}


//
//  FUNCTION: LoadAcceleratorsAU
//
//  PURPOSE:  Wrapper over LoadAcceleratorsA that mimics LoadAcceleratorsW
//
//  COMMENTS: 
//          This simply casts the resource ID to LPSTR and calls the ANSI
//          version. There is an implicit assumption that the resource ID
//          is a constant integer < 64k, rather than the address of a string
//          constant. This DOES NOT WORK if this assumption is false.
//  
HACCEL WINAPI LoadAcceleratorsAU(HINSTANCE hInstance, LPCWSTR lpTableName)
{
    return LoadAcceleratorsA(hInstance, (LPSTR) lpTableName) ;
}


//
//  FUNCTION: LoadMenuAU 
//
//  PURPOSE:  Wrapper over LoadMenuA that mimics LoadMenuW
//
//  COMMENTS: 
//          This simply casts the resource ID to LPSTR and calls the ANSI
//          version. There is an implicit assumption that the resource ID
//          is a constant integer < 64k, rather than the address of a string
//          constant. This DOES NOT WORK if this assumption is false.
// 
HMENU  WINAPI LoadMenuAU(HINSTANCE hInstance, LPCWSTR lpwMenuName)
{
    return LoadMenuA(hInstance, (LPSTR) lpwMenuName) ;
}


//
//  FUNCTION: DialogBoxParamAU 
//
//  PURPOSE:  Wrapper over DialogBoxParamA that mimics DialogBoxParamW
//
//  COMMENTS: 
//          This simply casts the resource ID to LPSTR and calls the ANSI
//          version. There is an implicit assumption that the resource ID
//          is a constant integer < 64k, rather than the address of a string
//          constant. This DOES NOT WORK if this assumption is false.
//
int WINAPI DialogBoxParamAU(
    HINSTANCE hInstance   ,
    LPCWSTR lpTemplateName,
    HWND hWndParent       ,
    DLGPROC lpDialogFunc  ,
    LPARAM dwInitParam)
{
    return DialogBoxParamA(hInstance, (LPCSTR) lpTemplateName, 
        hWndParent, lpDialogFunc, dwInitParam) ;
}


//
//  FUNCTION: CreateFontIndirectAU 
//
//  PURPOSE:  Wrapper over CreateFontIndirectA that mimics CreateFontIndirectW
//
HFONT WINAPI CreateFontIndirectAU(CONST LOGFONTW *lpLfw)
{
    LOGFONTA lfa ;

    // Most of the real work takes place here
    if(!CopyLfwToLfa((LPLOGFONTW) lpLfw, &lfa)) 
    {
        return NULL ;
    }

    return CreateFontIndirectA(&lfa) ;
}


//
//  FUNCTION: ChooseFontAU 
//
//  PURPOSE:  Wrapper over ChooseFontA that mimics ChooseFontW
//
BOOL WINAPI ChooseFontAU(LPCHOOSEFONTW lpCfw)
{
    CHOOSEFONTA cfa ;
    LOGFONTA    lfa ;

    CHAR szTemplateName[MAX_NAME] ;
    CHAR szStyle[MAX_NAME]        ;

    // Copy fields from Unicode CHOOSEFONT struct into ANSI CHOOSEFONT struct
    cfa.lStructSize    = sizeof(CHOOSEFONTA) ;
    cfa.hwndOwner      = lpCfw->hwndOwner    ;
    cfa.hDC            = lpCfw->hDC          ;
    cfa.lpLogFont      = &lfa                ;

    cfa.iPointSize     = lpCfw->iPointSize   ;
    cfa.Flags          = lpCfw->Flags        ;
    cfa.rgbColors      = lpCfw->rgbColors    ;
    cfa.lCustData      = lpCfw->lCustData    ;
    cfa.lpfnHook       = lpCfw->lpfnHook     ;
    cfa.hInstance      = lpCfw->hInstance    ;

    cfa.nFontType      = lpCfw->nFontType    ;
    cfa.nSizeMin       = lpCfw->nSizeMin     ;
    cfa.nSizeMax       = lpCfw->nSizeMax     ;

    cfa.lpTemplateName = szTemplateName      ;

    if(NULL != lpCfw->lpTemplateName && 
       !StandardUtoA(lpCfw->lpTemplateName, MAX_NAME, (LPSTR) cfa.lpTemplateName)) 
    {
        return FALSE ;
    }

    cfa.lpszStyle  = szStyle ; 

    if(NULL != lpCfw->lpszStyle && 
       !StandardUtoA(lpCfw->lpszStyle, MAX_NAME, cfa.lpszStyle)) 
    {
        return FALSE ;
    }

    if(!CopyLfwToLfa( lpCfw->lpLogFont , cfa.lpLogFont)) 
    {
        return FALSE ;
    }

    if(!ChooseFontA(&cfa)) 
    {
        return FALSE ;
    }

    // We have to copy the infomation in cfa back into lpCfw because it
    // will be used in calls to CreateFont hereafter
    CopyLfaToLfw(cfa.lpLogFont, lpCfw->lpLogFont) ;

    return TRUE ;
}


//
//  FUNCTION: CharLowerAU
//
//  PURPOSE:  Wrapper over CharLowerA that mimics CharLowerW
//
//  COMMENTS: 
//           This function converts a Unicode string to lowercase in the dumbest way possible 
//           on Windows 9x. You could make this a lot more fancy, to handle multi-script text,
//           for example, but for our purposes it works fine.
//
LPWSTR WINAPI CharLowerAU(LPWSTR lpsz)
{
    if(!(0xFFFF0000 & (DWORD) lpsz)) 
    {
        // Single character, not an address
        WCHAR wcCharOut[2] ;
        CHAR cChar[2], cTemp ;
        
        wcCharOut[0] = (WCHAR) lpsz ;
        wcCharOut[1] = L'\0' ;

        if(!StandardUtoA(wcCharOut, 2, cChar)) 
        {
            return NULL ;
        }

        if(!(cTemp = (CHAR) CharLowerA((LPSTR) cChar[0]))) 
        {
            return NULL ;
        }

        if(!MultiByteToWideChar(CP_ACP, 0, &cTemp, 1, wcCharOut, 2)) 
        {
            return NULL ;
        }
    
        return (LPWSTR) wcCharOut[0] ;
    }
    else 
    {
        int nLength = wcslen(lpsz) ;
        CHAR cStrOut[LARGEBUFFER]  ;    // Should really use HeapAlloc

        if(nLength > LARGEBUFFER)
        {
            return NULL ;
        }
    
        if(!StandardUtoA(lpsz, LARGEBUFFER, cStrOut)) 
        {
            return NULL ;
        }
    
        if(NULL == CharLowerA(cStrOut)) 
        {
            return NULL ;
        }
    
        if(!StandardAtoU(cStrOut, LARGEBUFFER, lpsz)) 
        {
            return NULL ;
        }
    
        return lpsz ;
    }
}


//
//  FUNCTION: FindFirstFileAU 
//
//  PURPOSE:  Wrapper over FindFirstFileA that mimics FindFirstFileW
//
HANDLE WINAPI FindFirstFileAU(IN LPCWSTR lpInFileName, OUT LPWIN32_FIND_DATAW lpFindFileData)
{
    WIN32_FIND_DATAA fda        ;

    CHAR cInFileNameA[MAX_PATH] = {'\0'} ;

    HANDLE hFindFile            ;

    // Convert file name from Unicode to ANSI
    if(!StandardUtoA(lpInFileName, MAX_PATH , cInFileNameA) ) 
    {
        return INVALID_HANDLE_VALUE ;
    }

    // Look for file using ANSI interface
    if(INVALID_HANDLE_VALUE == (hFindFile = FindFirstFileA(cInFileNameA, &fda)) ) 
    {
        return INVALID_HANDLE_VALUE ;
    }

    // Copy results into the wide version of the find data struct
    lpFindFileData->dwFileAttributes = fda.dwFileAttributes ;
    lpFindFileData->ftCreationTime   = fda.ftCreationTime   ;
    lpFindFileData->ftLastAccessTime = fda.ftLastAccessTime ;
    lpFindFileData->ftLastWriteTime  = fda.ftLastWriteTime  ;  
    lpFindFileData->nFileSizeHigh    = fda.nFileSizeHigh    ;
    lpFindFileData->nFileSizeLow     = fda.nFileSizeLow     ;

    if(!StandardAtoU(fda.cFileName, MAX_PATH, lpFindFileData->cFileName)
        ||
       !StandardAtoU(fda.cAlternateFileName, 14, lpFindFileData->cAlternateFileName) )
    {
        return NULL ;
    }

    // Return handle if everything was successful
    return hFindFile ;
}


//
//  FUNCTION: FindNextFileAU 
//
//  PURPOSE:  Wrapper over FindNextFileA that mimics FindNextFileW
//
BOOL  WINAPI FindNextFileAU(IN HANDLE hFile, OUT LPWIN32_FIND_DATAW lpFindFileData)
{
    WIN32_FIND_DATAA fda        ;

    // Look for file using ANSI interface
    if(FALSE == FindNextFileA(hFile, &fda) ) 
    {
        return FALSE ;
    }

    // Copy results into the wide version of the find data struct
    lpFindFileData->dwFileAttributes = fda.dwFileAttributes ;
    lpFindFileData->ftCreationTime   = fda.ftCreationTime   ;
    lpFindFileData->ftLastAccessTime = fda.ftLastAccessTime ;
    lpFindFileData->ftLastWriteTime  = fda.ftLastWriteTime  ;  
    lpFindFileData->nFileSizeHigh    = fda.nFileSizeHigh    ;
    lpFindFileData->nFileSizeLow     = fda.nFileSizeLow     ;

    if(!StandardAtoU(fda.cFileName, MAX_PATH, lpFindFileData->cFileName)
        ||
       !StandardAtoU(fda.cAlternateFileName, 14, lpFindFileData->cAlternateFileName) )
    {
        return FALSE ;
    }

    return TRUE ;
}

//
//  FUNCTION: LoadLibraryExAU 
//
//  PURPOSE:  Wrapper over LoadLibraryExA that mimics LoadLibraryExW
//
HMODULE WINAPI LoadLibraryExAU(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    CHAR cLibFileNameA[MAX_PATH] ;

    if(!StandardUtoA(lpLibFileName, MAX_PATH, cLibFileNameA)) 
    {
        return NULL ;
    }

    return LoadLibraryExA(cLibFileNameA, hFile, dwFlags) ; 
}


//
//  FUNCTION: GetModuleFileNameAU 
//
//  PURPOSE:  Wrapper over GetModuleFileNameA that mimics GetModuleFileNameW
//
DWORD WINAPI GetModuleFileNameAU(HMODULE hModule, LPWSTR lpFileName, DWORD nSize)
{
    CHAR cFileNameA[MAX_PATH] = {'\0'} ;

    if(!GetModuleFileNameA( hModule, cFileNameA, MIN(nSize, MAX_PATH)) ) 
    {
        return 0 ;
    }

    return StandardAtoU(cFileNameA, MIN(nSize, MAX_PATH), lpFileName) ;
}


//
//  FUNCTION: SendMessageAU 
//
//  PURPOSE:  Wrapper over SendMessageA that mimics SendMessageW
//
//  COMMENTS: 
//            Note: This function can send any of the hundreds of windows
//            messages to window, and the behavior may be different for each
//            one. I have tested those cases used in this sample application, 
//            as well as WM_CHAR, WM_IME_CHAR, WM_GETTEXT, and WM_SETTEXT.
//            You should test it with every message you intend to use it with.
// 
LRESULT WINAPI SendMessageAU(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult      = 0    ;
    LPVOID  lpTempBuffer = NULL ;
    int     nLength      = 0   ;
    CHAR  cCharA[3] ;
    WCHAR cCharW[3] ;

#if 0
    // These are some cases found during investigation that have not been tested.
    // Enable this section at your own risk.
    switch (Msg) 
    {
    // Cases that require conversion, but are not handled by this sample.
    // NOTE: There are probably others. These are all I could find with
    // a quick examination of the help files

         // RichEdit Messages. Requires #include<richedit.h>
        case EM_GETSELTEXT:
        case EM_FINDTEXT:
        case EM_SETPUNCTUATION:
            
        // Video capture messages. Requires #include<vfw.h>
        case WM_CAP_FILE_SAVEAS:
        case WM_CAP_FILE_SAVEDIB:
        case WM_CAP_FILE_SET_CAPTURE_FILE:
        case WM_CAP_PAL_OPEN:
        case WM_CAP_PAL_SAVE:
        case WM_CAP_SET_MCI_DEVICE:

        // Other special cases
        case WM_MENUCHAR:        // LOWORD(wParam) is char, HIWORD(wParam) is menu flag,
                                 // lParam is hmenu (handle of menu sending message)
        case WM_CHARTOITEM:      // LOWORD(wParam) = nKey, HIWORD(wParam) = nCaretPos 
                                 // lParam is handle of list box sending message
        case WM_IME_COMPOSITION: // wParam is dbcs char, lParam is fFlags 

            return FALSE ;
    }
#endif


    // Preprocess messages that pass chars and strings via wParam
    // and lParam
    switch (Msg) 
    {
        // Single Unicode Character in wParam. Convert Unicode character
        // to ANSI and pass lParam as is.
        case EM_SETPASSWORDCHAR: // wParam is char, lParam = 0 

        case WM_CHAR:            // wParam is char, lParam = key data
        case WM_SYSCHAR:         // wParam is char, lParam = key data
            // Note that we don't handle LeadByte and TrailBytes for
            // these two cases. An application should send WM_IME_CHAR
            // in these cases anyway

        case WM_DEADCHAR:        // wParam is char, lParam = key data
        case WM_SYSDEADCHAR:     // wParam is char, lParam = key data
        case WM_IME_CHAR:        // 

            cCharW[0] = (WCHAR) wParam ;
            cCharW[1] = L'\0' ;

            if(!WideCharToMultiByte(CP_ACP, 0, cCharW, 1, cCharA, 3, NULL, NULL)) 
            {
                return FALSE ;
            }

            if(Msg == WM_IME_CHAR) 
            {
                wParam = (cCharA[1] & 0x00FF) | (cCharA[0] << 8) ;
            } 
            else 
            {
                wParam = cCharA[0] ;
            }

            wParam &= 0x0000FFFF;

            break ;

        // In the following cases, lParam is pointer to IN buffer containing
        // text to send to window.
        // Preprocess by converting from Unicode to ANSI
        case CB_ADDSTRING:       // wParam = 0, lParm = lpStr, buffer to add 
        case LB_ADDSTRING:       // wParam = 0, lParm = lpStr, buffer to add
        case CB_DIR:             // wParam = file attributes, lParam = lpszFileSpec buffer
        case LB_DIR:             // wParam = file attributes, lParam = lpszFileSpec buffer
        case CB_FINDSTRING:      // wParam = start index, lParam = lpszFind  
        case LB_FINDSTRING:      // wParam = start index, lParam = lpszFind
        case CB_FINDSTRINGEXACT: // wParam = start index, lParam = lpszFind
        case LB_FINDSTRINGEXACT: // wParam = start index, lParam = lpszFind
        case CB_INSERTSTRING:    //*wParam = index, lParam = lpszString to insert
        case LB_INSERTSTRING:    //*wParam = index, lParam = lpszString to insert
        case CB_SELECTSTRING:    // wParam = start index, lParam = lpszFind
        case LB_SELECTSTRING:    // wParam = start index, lParam = lpszFind
        case WM_SETTEXT:         //*wParam = 0, lParm = lpStr, buffer to set 
        {
            if(NULL != (LPWSTR) lParam) 
            {

                nLength = 2*wcslen((LPWSTR) lParam)+1 ; // Need double length for DBCS characters

                lpTempBuffer // This is time-consuming, but so is the conversion
                    = (LPVOID) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, nLength) ;
            }

            if(NULL == lpTempBuffer)
            {
                return FALSE ;
            }

            if(!StandardUtoA((LPWSTR) lParam, nLength, (LPSTR) lpTempBuffer) ) 
            {
                HeapFree(GetProcessHeap(), 0, lpTempBuffer) ;
                return FALSE ;
            }

            lParam = (LPARAM) lpTempBuffer ;

            break ;

        }
    }

    // This is where the actual SendMessage takes place
    lResult = SendMessageA(hWnd, Msg, wParam, lParam) ;

    nLength = 0 ;

    if(lResult > 0) 
    {

        switch (Msg) 
        {
            // For these cases, lParam is pointer to OUT buffer that received text from
            // SendMessageA in ANSI. Convert to Unicode and send back.
            case WM_GETTEXT:         // wParam = numCharacters, lParam = lpBuff to RECEIVE string
            case WM_ASKCBFORMATNAME: // wParam = nBufferSize, lParam = lpBuff to RECEIVE string 

                nLength = (int) wParam ;

                if(!nLength) 
                {

                    break ;
                }

            case CB_GETLBTEXT:       // wParam = index, lParam = lpBuff to RECEIVE string
            case EM_GETLINE:         // wParam = Line no, lParam = lpBuff to RECEIVE string

                if(!nLength) 
                {
                    
                    nLength = wcslen((LPWSTR) lParam) + 1 ;
                }

                lpTempBuffer
                    = (LPVOID) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, nLength*sizeof(WCHAR)) ;

                if(!StandardAtoU((LPCSTR) lParam, nLength, (LPWSTR) lpTempBuffer) ) 
                {
                    *((LPWSTR) lParam) = L'\0' ;
                    HeapFree(GetProcessHeap(), 0, lpTempBuffer) ;
                    return FALSE ;
                }

            wcscpy((LPWSTR) lParam, (LPWSTR) lpTempBuffer) ;
        }
    }

    if(lpTempBuffer != NULL) 
    {
        HeapFree(GetProcessHeap(), 0, lpTempBuffer) ;
    }

    return lResult ;
}


//
//  FUNCTION: SendDlgItemMessageAU 
//
//  PURPOSE:  Wrapper over to mimic SendDlgItemMessageW
//
//  COMMENTS: 
//     Rather than going through SendDlgItemMessageA, we just
//     do what the system does, i.e., go through SendMessage
// 
LONG WINAPI SendDlgItemMessageAU(
    HWND hDlg,
    int nIDDlgItem,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam)
{

    HWND hWnd = GetDlgItem(hDlg, nIDDlgItem) ;

    if(NULL == hWnd) 
    {
        return 0L;
    }

    return SendMessageAU(hWnd, Msg, wParam, lParam) ;
}


//
//  FUNCTION: SetWindowTextAU 
//
//  PURPOSE:  Wrapper to mimic SetWindowTextW
//
//  COMMENTS: 
//     Rather than going through SetWindowTextA, we just
//     do what the system does, i.e., go through SendMessage
// 
BOOL WINAPI SetWindowTextAU(HWND hWnd, LPCWSTR lpStringW)
{
    return (BOOL) (0 < SendMessageAU(hWnd, WM_SETTEXT, 0, (LPARAM) lpStringW)) ;
}


//
//  FUNCTION: GetWindowTextAU 
//
//  PURPOSE:  Wrapper over GetWindowTextA that mimics GetWindowTextW
//
//  COMMENTS: 
//     Rather than going through GetWindowTextA, we just
//     do what the system does, i.e., go through SendMessage
//
int WINAPI GetWindowTextAU(HWND hWnd, LPWSTR lpStringW, int nMaxChars)
{
    return (int) SendMessageAU(hWnd, WM_GETTEXT, (WPARAM) nMaxChars, (LPARAM) lpStringW) ;
}


//
//  FUNCTION: GetLocaleInfoAU 
//
//  PURPOSE:  Wrapper over GetLocaleInfoA that mimics GetLocaleInfoW
//
INT WINAPI GetLocaleInfoAU(LCID dwLCID, LCTYPE lcType, LPWSTR lpOutBufferW, INT nBufferSize) 
{
    CHAR cBufferA[BUFFER_SIZE] ;  

    DWORD nLength = GetLocaleInfoA(dwLCID, lcType, cBufferA, nBufferSize) ;

    if(0 == nLength) 
    {
        return 0 ;
    }

    return StandardAtoU(cBufferA, MIN(nBufferSize, BUFFER_SIZE), lpOutBufferW) ;
}


//
//  FUNCTION: GetDateFormatAU 
//
//  PURPOSE:  Wrapper over GetDateFormatA that mimics GetDateFormatW
//
int WINAPI GetDateFormatAU(
  LCID dwLocale,
  DWORD dwFlags,
  CONST SYSTEMTIME *lpDate,
  LPCWSTR lpFormat,
  LPWSTR lpDateStr,
  int cchDate
  )
{
    CHAR cDateStr[BUFFER_SIZE] ;
    LPSTR lpFormatA = NULL ;

    if(NULL != lpFormat) 
    {       
        lpFormatA = (LPSTR) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 2*wcslen(lpFormat)+1 ) ;
    }

   if(!GetDateFormatA(dwLocale, dwFlags, lpDate, lpFormatA, cDateStr,BUFFER_SIZE)) 
   {
       return 0 ;
   }

    if(NULL != lpFormatA) 
    {
        HeapFree(GetProcessHeap(), 0, (LPVOID) lpFormatA) ;
    }

    return StandardAtoU(cDateStr, cchDate, lpDateStr) ;  
}


//
//  FUNCTION: UpdateUnicodeAPIAU
//
//  PURPOSE:  Update global variables in this DLL.
//
//  COMMENTS: Called by the application to update global variables. This avoids having
//            to export global variables from this DLL. When running on Windows NT,
//            the pointer UpdateUnicodeAPI will point to a stub and this function will 
//            never be called.
// 
BOOL WINAPI UpdateUnicodeAPIAU(IN LANGID wCurrentUILang, IN UINT InputCodePage)
{
    g_UICodePage    = LangToCodePage(wCurrentUILang) ;
    g_InputCodePage = InputCodePage                ;

    return TRUE ;
}


//
//  FUNCTION: ConvertMessageAU
//
//  PURPOSE:  Converts message parameters from ANSI to Unicode for use by a Unicode
//            WndProc function when running on Windows 9x.
//
//  COMMENTS: When running on Windows NT, the pointer ConvertMessage will point to a 
//            stub and this function will never be called.
// 
BOOL WINAPI ConvertMessageAU(IN  HWND hWnd, IN  UINT message, IN OUT  WPARAM *pwParam, IN OUT  LPARAM *plParam)
{

    static CHAR s_sANSIchar[3] = "\0" ;

    int nReturn ;

    switch (message)
    {
    case WM_CHAR:

        // We have to go through all this malarky because DBCS characters arrive one byte
        // at a time. It's much better to get DBCS characters via WM_IME_CHAR messages, 
        // because even in ANSI mode, you get both bytes at once. 
        // In this sample application, most of this code is never used because DBCS chars
        // are handled by WM_IME_CHAR below. You can comment out that case (and the 
        // corresponding one in WinProc) to test this code.

        if(!s_sANSIchar[0]) 
        {  // No lead byte already waiting for trail byte

#ifdef _DEBUG
			int nScanCode = LPARAM_TOSCANCODE(*plParam) ;
#endif
            s_sANSIchar[0] = (CHAR) *pwParam ; 

            if(IsDBCSLeadByteEx(g_InputCodePage , *pwParam)) 
            {
                // This is a lead byte. Save it and wait for trail byte
                return FALSE ;
            }

            // Not a DBCS character. Convert to Unicode.
            MultiByteToWideChar(g_InputCodePage , 0, s_sANSIchar, 1, (LPWSTR) pwParam, 1) ;
            s_sANSIchar[0] = 0 ;    // Reset to indicate no Lead byte waiting
            
            return TRUE ;
        }
        else 
        { // Already have a lead byte, pwParam should contain the trail byte
            s_sANSIchar[1] = (CHAR) *pwParam ;
            // Convert both bytes into one Unicode character
            MultiByteToWideChar(g_InputCodePage , 0, s_sANSIchar, 2, (LPWSTR) pwParam, 1) ;
            s_sANSIchar[0] = 0 ;    // Reset to non-waiting state
            return TRUE ;
        }

// Disable this section to test WM_CHAR logic for DBCS characters
#if 1
    case WM_IME_CHAR:

        // The next 3 lines replace all but one line in the WM_CHAR case above. This is why 
        // it's best to get IME chars through WM_IME_CHAR rather than WM_CHAR when in 
        // ANSI mode.
        s_sANSIchar[1] = LOBYTE((WORD) *pwParam) ;
        s_sANSIchar[0] = HIBYTE((WORD) *pwParam) ;
        
        nReturn = MultiByteToWideChar(g_InputCodePage, 0, s_sANSIchar, 2, (LPWSTR) pwParam, 1) ;
        return (nReturn > 0) ;
#endif

    case WM_INPUTLANGCHANGEREQUEST:
    {
        HKL NewInputLocale = (HKL) *plParam ;

        LANGID wPrimaryLang 
            = PRIMARYLANGID(LANGIDFROMLCID(LOWORD(NewInputLocale))) ;

        // Reject change to Indic input locales, since they are not supported by
        // ANSI applications
        switch (wPrimaryLang) 
        {

            case LANG_ASSAMESE :
            case LANG_BENGALI :
            case LANG_GUJARATI :
            case LANG_HINDI :
            case LANG_KANNADA :
            case LANG_KASHMIRI :
            case LANG_KONKANI :
            case LANG_MALAYALAM :
            case LANG_MARATHI :
            case LANG_NEPALI :
            case LANG_ORIYA :
            case LANG_PUNJABI :
            case LANG_SANSKRIT :
            case LANG_SINDHI :
            case LANG_TAMIL :
            case LANG_TELUGU :

                return FALSE ;
        }

        // Utility program defined below
        g_InputCodePage = LangToCodePage( LOWORD(NewInputLocale) ) ;

        return TRUE ;
    }

    default:

        return TRUE ;
    }
}


//
//  FUNCTION: InitUniAnsi
//
//  PURPOSE:  Initialize U function pointers to point to the corresponding
//            wrapper functions in this DLL
//
//  COMMENTS: This avoids multiple calls to GetProcAddress.
// 
BOOL InitUniAnsi(PUAPIINIT pUAInit) 
{

    *(pUAInit->pCharLowerU)         = CharLowerAU          ;
    *(pUAInit->pChooseFontU)        = ChooseFontAU         ;
    *(pUAInit->pCreateWindowExU)    = CreateWindowExAU     ;
    *(pUAInit->pCreateFontIndirectU)= CreateFontIndirectAU ;
    *(pUAInit->pDialogBoxParamU)    = DialogBoxParamAU     ;
    *(pUAInit->pFindFirstFileU)     = FindFirstFileAU      ;
    *(pUAInit->pFindNextFileU)      = FindNextFileAU       ;
    *(pUAInit->pGetDateFormatU)     = GetDateFormatAU      ;
    *(pUAInit->pGetLocaleInfoU)     = GetLocaleInfoAU      ;
    *(pUAInit->pGetModuleFileNameU) = GetModuleFileNameAU  ;
    *(pUAInit->pLoadAcceleratorsU)  = LoadAcceleratorsAU   ;
    *(pUAInit->pLoadLibraryExU)     = LoadLibraryExAU      ;
    *(pUAInit->pLoadMenuU)          = LoadMenuAU           ;
    *(pUAInit->pLoadStringU)        = LoadStringAU         ;
    *(pUAInit->pRegisterClassExU)   = RegisterClassExAU    ;
    *(pUAInit->pSendDlgItemMessageU)= SendDlgItemMessageAU ;
    *(pUAInit->pSendMessageU)       = SendMessageAU        ;
    *(pUAInit->pSetWindowTextU)     = SetWindowTextAU      ;
    *(pUAInit->pGetWindowTextU)     = GetWindowTextAU      ;

    *(pUAInit->pConvertMessage)     = ConvertMessageAU      ;
    *(pUAInit->pUpdateUnicodeAPI)   = UpdateUnicodeAPIAU    ;

    return TRUE ;
}


// Utility functions

//
//  FUNCTION: CopyLfwToLfa
//
//  PURPOSE:  Copies contents of a Unicode LOGFONT into an ANSI LOGFONT.
//
BOOL CopyLfwToLfa(IN LPLOGFONTW lpLfw, OUT LPLOGFONTA lpLfa)
{
    lpLfa->lfCharSet       = lpLfw->lfCharSet       ;
    lpLfa->lfClipPrecision = lpLfw->lfClipPrecision ;
    lpLfa->lfEscapement    = lpLfw->lfEscapement    ;
    lpLfa->lfHeight        = lpLfw->lfHeight        ;
    lpLfa->lfItalic        = lpLfw->lfItalic        ;
    lpLfa->lfOrientation   = lpLfw->lfOrientation   ;
    lpLfa->lfOutPrecision  = lpLfw->lfOutPrecision  ;
    lpLfa->lfPitchAndFamily= lpLfw->lfPitchAndFamily;
    lpLfa->lfQuality       = lpLfw->lfQuality       ;
    lpLfa->lfStrikeOut     = lpLfw->lfStrikeOut     ;
    lpLfa->lfUnderline     = lpLfw->lfUnderline     ;
    lpLfa->lfWeight        = lpLfw->lfWeight        ;
    lpLfa->lfWidth         = lpLfw->lfWidth         ;

    if(NULL != lpLfw->lfFaceName) 
    {
        return (BOOL) StandardUtoA(lpLfw->lfFaceName, LF_FACESIZE, lpLfa->lfFaceName) ;
    }

    // Fail the call if lpLfw has no buffer for the facename. 
    return FALSE ;
}


//
//  FUNCTION: CopyLfaToLfw
//
//  PURPOSE:  Copies contents of an ANSI LOGFONT into a Unicode LOGFONT
//
BOOL CopyLfaToLfw(IN LPLOGFONTA lpLfa, OUT LPLOGFONTW lpLfw)
{
    lpLfw->lfCharSet       = lpLfa->lfCharSet       ;
    lpLfw->lfClipPrecision = lpLfa->lfClipPrecision ;
    lpLfw->lfEscapement    = lpLfa->lfEscapement    ;
    lpLfw->lfHeight        = lpLfa->lfHeight        ;
    lpLfw->lfItalic        = lpLfa->lfItalic        ;
    lpLfw->lfOrientation   = lpLfa->lfOrientation   ;
    lpLfw->lfOutPrecision  = lpLfa->lfOutPrecision  ;
    lpLfw->lfPitchAndFamily= lpLfa->lfPitchAndFamily;
    lpLfw->lfQuality       = lpLfa->lfQuality       ;
    lpLfw->lfStrikeOut     = lpLfa->lfStrikeOut     ;
    lpLfw->lfUnderline     = lpLfa->lfUnderline     ;
    lpLfw->lfWeight        = lpLfa->lfWeight        ;
    lpLfw->lfWidth         = lpLfa->lfWidth         ;

    if(NULL != lpLfa->lfFaceName) 
    {
        return StandardAtoU(lpLfa->lfFaceName, LF_FACESIZE, lpLfw->lfFaceName) ;
    }

    return TRUE ;
}


//
//  FUNCTION: StandardUtoA
//
//  PURPOSE:  Performs standard Unicode to ANSI conversion using ACP
//
int StandardUtoA(IN LPCWSTR lpwStrIn ,IN int nOutBufferSize, OUT LPSTR lpStrOut)
{
    int nNumCharsConverted  =
        WideCharToMultiByte(CP_ACP, 0, lpwStrIn, -1, lpStrOut, nOutBufferSize, NULL, NULL) ;

    if(!nNumCharsConverted) 
    {
        return 0 ;
    }

    *(lpStrOut+nNumCharsConverted) = '\0' ; // Null terminate

    return (nNumCharsConverted) ; 
}

#if 0
//
//  FUNCTION: StandardAtoU
//
//  PURPOSE:  Performs standard ANSI to Unicode conversion using ACP
//
//  COMMENTS: Replaced by macro in UNIANSI.H
// 
int StandardAtoU(IN  LPCSTR lpInStrA, IN int nBufferSize, OUT LPWSTR lpOutStrW)
{
    return MultiByteToWideChar(CP_ACP, 0, lpInStrA, -1, lpOutStrW, nBufferSize) ;
}
#endif

//
//  FUNCTION: LangToCodePage
//
//  PURPOSE:  Gets the default codepage for a given langID.
//
UINT LangToCodePage(IN LANGID wLangID)
{
    CHAR szLocaleData[6] ;

    GetLocaleInfoA(wLangID , LOCALE_IDEFAULTANSICODEPAGE, szLocaleData, 6) ;

    return strtoul(szLocaleData, NULL, 10) ;
}


#ifdef __cplusplus
}
#endif  /* __cplusplus */
