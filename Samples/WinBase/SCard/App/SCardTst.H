/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.


Module Name:

    SCardTestApp

Abstract:

        CWinApp header/object description file for the smart card test/example
        program. This application implements a OLE container to test the smart
        card vendor wrapper COM object and associated Smart Card resources.

Environment:

    Win32, C++ w/Exceptions, COM/OLE

Notes:

--*/

#ifndef __SCARDTST_H__
#define __SCARDTST_H__

/////////////////////////////////////////////////////////////////////////////
//
// Includes
//

#ifndef __AFXWIN_H__
        #error include 'stdafx.h' before including this file for PCH
#endif

#include "resapp.h"             // main symbols


/////////////////////////////////////////////////////////////////////////////
//
// Class Declaration
//

class CSCardTestApp : public CWinApp
{
public:
        CSCardTestApp();

        /////////////////////////////////////////////////////////////////////////
        //
        // Overrides for CSCardTestApp
        //
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CSCardTestApp)
        public:
        virtual BOOL InitInstance();
        //}}AFX_VIRTUAL

        // Implementation


        //////////////////////////////////////////////////////////////////////////
        // CSCardTestApp Message Map
        //
        //{{AFX_MSG(CSCardTestApp)
                // NOTE - the ClassWizard will add and remove member functions here.
                //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

#endif //__SCARDTST_H__