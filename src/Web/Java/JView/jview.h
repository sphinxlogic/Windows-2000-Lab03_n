/*
 * jview.h - JView project header file.
 *
 * (C) Copyright 1996, Microsoft Corporation and it suppliers.
 */

#ifndef _JVIEW_INCLUDED_
#define _JVIEW_INCLUDED_

#define INITGUID 1

#include <windows.h>
#include <cguid.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>

#include <javaexec.h>

#include "resource.h"
#include "jview.h"
#include "javaprop.hpp"

#define BUFSIZE 512     // A one-size fits all buffer size...

// Macros
//------------------------------------------------------------------------------
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

    BOOL      m_fApplet;
    BOOL      m_fPause;
    BOOL      m_fVerify;
    LPSTR     m_pszClassPath;
    LPSTR     m_pszAppend;
    LPSTR     m_pszPrepend;
    LPSTR     m_pszClassName;
    INT       m_iArgs;
    LPOLESTR *m_ppszArgs;

    IJavaExecute *m_pJE;

    CEnumJAVAPROPERTY *m_pProperties;

    void   m_Pause            ();
    void   m_FatalError       (INT idString, ...);
    void   m_FatalErrorHR     (HRESULT hr, INT idString, ...);
    BOOL   m_InitComAndJava   ();
    LPWSTR m_MB2WC            (LPCSTR szAnsi,int cchAnsi = -1);
    LPSTR  m_WC2MB            (LPCWSTR pwsz, int cchWide = -1);
    LPSTR  m_newSZ            (int cBytes);
    BOOL   m_AppendPathString (LPSTR *ppszPath, LPSTR pszAppend);
    void   m_DisplayUsage     ();
    void   m_PreParseSwitches ();
    BOOL   m_ParseSwitches    (int *piArg);
    BOOL   m_ParseParameters  (int iNext);
    void   m_DisplayBanner    ();

public:
    CJView(int ac, char **av);
    ~CJView();

public:
    BOOL Initialize         ();
    BOOL ParseCommandLine   ();
    HRESULT ExecuteClass    (LPERRORINFO*);
    HRESULT SetSystemProperties();
};

#endif //_JVIEW_INCLUDED_

