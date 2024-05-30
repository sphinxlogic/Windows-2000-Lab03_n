#include "globals.h"

static OPENFILENAME ofn ;

void InitializeFileOpenDlg (HWND hwnd)
{
    static TCHAR szFilter[] =   _T("PNG Files (*.PNG)\0*.png\0")    \
                                _T("JPEG Files (*.JPG)\0*.jpg\0")   \
                                _T("All Files (*.*)\0*.*\0\0");

    ofn.lStructSize         = sizeof (OPENFILENAME) ;
    ofn.hwndOwner           = hwnd ;
    ofn.hInstance           = NULL ;
    ofn.lpstrFilter         = szFilter ;
    ofn.lpstrCustomFilter   = NULL ;
    ofn.nMaxCustFilter      = 0 ;
    ofn.nFilterIndex        = 0 ;
    ofn.lpstrFile           = NULL ;         // Set in Open and Close functions
    ofn.nMaxFile            = _MAX_PATH ;
    ofn.lpstrFileTitle      = NULL ;         // Set in Open and Close functions
    ofn.nMaxFileTitle       = _MAX_FNAME + _MAX_EXT ;
    ofn.lpstrInitialDir     = NULL ;
    ofn.lpstrTitle          = NULL ;
    ofn.Flags               = 0 ;            // Set in Open and Close functions
    ofn.nFileOffset         = 0 ;
    ofn.nFileExtension      = 0 ;
    ofn.lpstrDefExt         = _T("png") ;
    ofn.lCustData           = 0L ;
    ofn.lpfnHook            = NULL ;
    ofn.lpTemplateName      = NULL ;
}

BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner           = hwnd ;
    ofn.lpstrFile           = pstrFileName ;
    ofn.lpstrFileTitle      = pstrTitleName ;
    ofn.Flags               = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;

    return GetOpenFileName (&ofn) ;
}

BOOL ReadImageFile (IDXSurface **lplpDXSurf, PTSTR pstrFileName)
{
    WCHAR   pwcsBuffer[256] ;
    HRESULT hr;
    char    szString[256];
    
#ifndef UNICODE
    mbstowcs( pwcsBuffer, pstrFileName, strlen(pstrFileName)+1 ); 
#endif

    // Load Input surfaces
    hr = g_pSurfFact->LoadImage( pwcsBuffer, NULL, NULL,
                                &DDPF_PMARGB32, IID_IDXSurface, (void**)lplpDXSurf );

    if (FAILED(hr))
    {
        wsprintf(szString, "Couldn't load image! hr=0x%08x", hr);
        MessageBox(g_hDlg, szString, _T("Error Loading"), MB_ICONERROR );
    }

    return SUCCEEDED( hr );
}
