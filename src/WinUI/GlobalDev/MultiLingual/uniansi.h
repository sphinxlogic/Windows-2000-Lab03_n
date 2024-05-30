//
// UNIANSI.H
//

#ifndef _UNIANSI
#define _UNIANSI

#define MAX_LOADSTRING  200
#define BUFFER_SIZE     200
#define MAX_NAME        100
#define LARGEBUFFER     1000
#define MAX_LOADSTRING  200
#define BUFFER_SIZE     200
#define MAX_NAME        100
#define LARGEBUFFER     1000

// Win32 entry points that require a hand-written UA version to convert between
// Unicode and ANSI
typedef WINUSERAPI INT     (WINAPI *UAPI_LoadString)         (HINSTANCE, UINT, LPWSTR, INT) ;
typedef WINUSERAPI ATOM    (WINAPI *UAPI_RegisterClassEx)    (CONST WNDCLASSEXW *)          ; 
typedef WINUSERAPI HACCEL  (WINAPI *UAPI_LoadAccelerators)   (HINSTANCE , LPCWSTR )         ;
typedef WINUSERAPI HFONT   (WINAPI *UAPI_CreateFontIndirect) (CONST LOGFONTW *)             ;
typedef WINUSERAPI BOOL    (WINAPI *UAPI_ChooseFont)         (LPCHOOSEFONTW)                ;
typedef WINUSERAPI HMENU   (WINAPI *UAPI_LoadMenu)           (HINSTANCE, LPCWSTR)           ;
typedef WINUSERAPI HWND    (WINAPI *UAPI_CreateWindowEx)
        (DWORD , LPCWSTR, LPCWSTR , DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
typedef WINUSERAPI BOOL    (WINAPI *UAPI_SetWindowText)      (HWND, LPCWSTR)                ;
typedef WINUSERAPI int     (WINAPI *UAPI_GetWindowText)      (HWND, LPWSTR, int)           ;

typedef WINUSERAPI LONG    (WINAPI *UAPI_SendDlgItemMessage) (HWND, INT, UINT, WPARAM, LPARAM );
typedef WINUSERAPI LRESULT (WINAPI *UAPI_SendMessage)        (HWND, UINT, WPARAM, LPARAM )  ;
typedef WINBASEAPI DWORD   (WINAPI *UAPI_GetModuleFileName)  (HMODULE, LPWSTR, DWORD )      ;
typedef WINUSERAPI LPWSTR  (WINAPI *UAPI_CharLower)          (LPWSTR)                       ;
typedef WINBASEAPI HMODULE (WINAPI *UAPI_LoadLibraryEx)      (LPCWSTR, HANDLE, DWORD)       ;
typedef WINBASEAPI HANDLE  (WINAPI *UAPI_FindFirstFile)      (LPCWSTR , LPWIN32_FIND_DATAW) ;
typedef WINBASEAPI BOOL    (WINAPI *UAPI_FindNextFile)       (HANDLE, LPWIN32_FIND_DATAW)   ;
typedef WINBASEAPI INT     (WINAPI *UAPI_GetLocaleInfo)      (LCID, LCTYPE, LPWSTR, INT)    ;
typedef WINUSERAPI int     (WINAPI *UAPI_DialogBoxParam)
        (HINSTANCE , LPCWSTR , HWND , DLGPROC , LPARAM) ;
typedef WINBASEAPI int     (WINAPI *UAPI_GetDateFormat)      
        (LCID, DWORD, CONST SYSTEMTIME*, LPCWSTR, LPWSTR, int) ;


// Special case function pointers for use with the Unicode API
typedef BOOL (WINAPI *UAPI_ConvertMessage)      (HWND, UINT, WPARAM *, LPARAM *) ;
typedef BOOL (WINAPI *UAPI_UpdateUnicodeAPI)    (LANGID, UINT )                  ;               

#ifndef MIN
#define MIN(_aa, _bb) ((_aa) < (_bb) ? (_aa) : (_bb))
#endif

typedef struct _tagUAPIInit {

    UAPI_CharLower          *pCharLowerU ;
    UAPI_ChooseFont         *pChooseFontU ;
    UAPI_CreateWindowEx     *pCreateWindowExU ;
    UAPI_CreateFontIndirect *pCreateFontIndirectU ;
    UAPI_DialogBoxParam     *pDialogBoxParamU ;
    UAPI_FindFirstFile      *pFindFirstFileU ;
    UAPI_FindNextFile       *pFindNextFileU ;
    UAPI_GetDateFormat      *pGetDateFormatU ;
    UAPI_GetLocaleInfo      *pGetLocaleInfoU ;
    UAPI_GetModuleFileName  *pGetModuleFileNameU ;
    UAPI_LoadAccelerators   *pLoadAcceleratorsU ;
    UAPI_LoadLibraryEx      *pLoadLibraryExU ;
    UAPI_LoadMenu           *pLoadMenuU ;
    UAPI_LoadString         *pLoadStringU ;
    UAPI_RegisterClassEx    *pRegisterClassExU ;
    UAPI_SendDlgItemMessage *pSendDlgItemMessageU ;
    UAPI_SendMessage        *pSendMessageU ;
    UAPI_SetWindowText      *pSetWindowTextU ;
    UAPI_GetWindowText      *pGetWindowTextU ;

    UAPI_ConvertMessage     *pConvertMessage ;
    UAPI_UpdateUnicodeAPI   *pUpdateUnicodeAPI ;

    int nCount;
} UAPIINIT, *PUAPIINIT ;

BOOL InitUniAnsi(PUAPIINIT) ;

// Macro to get scan code on WM_CHAR
#ifdef _DEBUG
#define LPARAM_TOSCANCODE(_ArglParam) (((_ArglParam) >> 16) & 0x000000FF)
#endif

#define StandardAtoU(_lpInStrA, _nBufferSize, _lpOutStrW) \
    MultiByteToWideChar(CP_ACP, 0, _lpInStrA, -1, _lpOutStrW, _nBufferSize)

#endif /* _UNIANSI */
