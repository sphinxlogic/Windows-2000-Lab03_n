// -----------------------------------------------------------------------------
// ShowPage.CPP: Implements a default bStartPage helper function for the ExAdmin 
//               lib.  There is only one function in this file because it is
//               intended that the user can override this function by simply
//               defining their own.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"

// $--iStartPage()--------------------------------------------------------------
// This function is called once durring initialization.  Return -1 to cause the 
// first standard property sheet to be displayed.  Or return the index of one of 
// our property sheets to have it come up first.  The user can override this 
// function by simply defining their own function in their code.
// -----------------------------------------------------------------------------

INT PASCAL iStartPage( void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int i = -1; // Default to the first standard property sheet.
    return( i);
}

// -----------------------------------------------------------------------------
