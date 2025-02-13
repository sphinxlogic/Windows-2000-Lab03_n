/*+==========================================================================
  File:      SERVER.H

  Summary:   Internal include file for the PERSERVE.DLL server code
             sample.  Contains class declarations, resource IDs and string
             macros for internal use in constructing this DLL as a COM
             component server housing.  Declares the CServer server
             control object class. The CThreaded OwnThis mechanism is used
             to ensure mutually exclusive access to this CServer object by
             multiple threads.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CServer.

  Functions: .

  Origin:    5-8-97: atrent - Editor-inheritance from SERVER.H in
               the STOSERVE Tutorial Code Sample. [Revised]

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) 1995-1998 Microsoft Corporation.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/


#if !defined(SERVER_H)
#define SERVER_H


#ifdef __cplusplus

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CServer

  Summary:  Class to encapsulate control of this COM server (eg, handle
            Lock and Object counting, encapsulate otherwise global data).

  Methods:  none
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CServer : public CThreaded
{
  public:
    CServer(void);
    ~CServer(void);

    // Methods for server lifetime control: object counts and lock counts.
    void Lock(void);
    void Unlock(void);
    void ObjectsUp(void);
    void ObjectsDown(void);
    HRESULT CanUnloadNow(void);

    // A place to store the handle to loaded instance of this DLL module.
    HINSTANCE m_hDllInst;

    // A place to store a client's parent window.
    HWND m_hWndParent;

    // Global DLL Server living Object count.
    LONG m_cObjects;

    // Global DLL Server Client Lock count.
    LONG m_cLocks;
};

#endif // __cplusplus

// Allow other internal PERSERVE modules to get at the globals.
extern CServer* g_pServer;


#endif // SERVER_H
