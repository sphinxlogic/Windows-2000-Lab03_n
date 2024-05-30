// -----------------------------------------------------------------------------
// ShowPage.CPP: Implements a default bShowPage helper function for the ExAdmin 
//               lib.  There is only one function in this file because it is
//               intended that the user can override this function by simply
//               defining their own.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"

// $--bShowPage()---------------------------------------------------------------
// This is called once per standard property sheet.  Not at all for our property
// sheets.  If you want to disable some or all of the standard property sheets 
// Then define this function in your code.  Your function will need to return 
// FALSE to disable a default property sheet.
// -----------------------------------------------------------------------------

BOOL PASCAL bShowPage( UINT iddAdminPage)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    BOOL bRet = TRUE;   // Show the standard property sheet.
    return( bRet);
}

// -----------------------------------------------------------------------------
