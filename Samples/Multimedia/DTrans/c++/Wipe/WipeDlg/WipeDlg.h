#ifndef _INC_WIPEDLG
#define _INC_WIPEDLG

#include "globals.h"

// Constant definitions
#define DIALOG_TITLE        "WipeDlg"


// *** Global function prototypes ***
void InitializeFileOpenDlg (HWND hwnd);
BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
BOOL ReadImageFile (IDXSurface **lplpDXSurf, PTSTR pstrFileName);

#endif // _INC_WIPEDLG
