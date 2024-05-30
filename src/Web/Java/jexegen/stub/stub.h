/*
 * stub.h
 *
 * (C) Copyright 1996, Microsoft Corporation and it suppliers.
 */

#ifndef _EXEGENSTUB_INCLUDED_
#define _EXEGENSTUB_INCLUDED_

#define INITGUID 1

#include <windows.h>
#include <cguid.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>

#include "..\..\..\include\javaexec.h"

#include "resource.h"

#define   BUFSIZE 512     // A one-size fits all buffer size...

//
// Macros
//

#define deleteSZ(p) if ((p) != NULL)  \
                    {                 \
                       delete [] (p); \
                       (p) = NULL;    \
                    }

class CJView
{
public:
    DWORD m_dwMsgLoopThreadID;

    int    m_ac;
    char **m_av;

    LPSTR     m_pszClassName;
    INT       m_iArgs;
    LPOLESTR *m_ppszArgs;

    IJavaExecute2 *m_pJE;

    void   m_FatalError       (INT idString, ...);
    void   m_FatalErrorHR     (HRESULT hr, INT idString, ...);
    BOOL   m_InitComAndJava   ();
    LPWSTR m_MB2WC            (LPCSTR szAnsi,int cchAnsi = -1);
    LPSTR  m_WC2MB            (LPCWSTR pwsz, int cchWide = -1);
    LPSTR  m_newSZ            (int cBytes);
    BOOL   m_ParseParameters  ();

    BOOL   LoadDataResource( DWORD dwResID, BYTE *pBuffer, DWORD *pdwSize );

public:
    CJView(int ac, char **av);
    ~CJView();

public:
    BOOL Initialize         ();
    BOOL ParseCommandLine   ();
    int  ExecuteClass       ();
};

#endif //_EXEGENSTUB_INCLUDED_

