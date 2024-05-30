/*
 * stub.cpp
 *
 * Sample code.
 *  
 * (C) Copyright 1996, Microsoft Corporation and it suppliers.
 */

#pragma hdrstop

#include "stub.h"

// Macros

#define WIN32_ERROR_TO_HRESULT(err)    MAKE_SCODE(SEVERITY_ERROR, FACILITY_WIN32, (err))
#define WIN32_RESULT_TO_HRESULT(err)   ((err) == ERROR_SUCCESS ? S_OK : WIN32_ERROR_TO_HRESULT(err))
#define LAST_WIN32_ERROR_TO_HRESULT()  WIN32_RESULT_TO_HRESULT(GetLastError())

// Resource IDs for the class resource data and the main class name data.
// These are the IDs of the resources that jexegen will create when used
// with the /bindto option.

#define CLASSRESOURCEID         1000
#define MAINCLASSNAMERESOURCEID 1001

//------------------------------------------------------------------------------
// CJView::CJView:
//    Constructor
//------------------------------------------------------------------------------

CJView::CJView (int ac, char **av) : m_ac (ac), m_av (av)
{
    m_pszClassName = NULL;
    m_ppszArgs     = NULL;
    m_iArgs        = 0;
    m_pJE          = NULL;
}

//------------------------------------------------------------------------------
// CJView::~CJView:
//    Destructor
//------------------------------------------------------------------------------

CJView::~CJView ()
{
    if (m_ppszArgs)
    {
        INT n = 0;

        while (m_ppszArgs[n] != NULL)
            delete [] m_ppszArgs[n++];
        delete [] m_ppszArgs;
    }

    if (m_pJE)
    {
        m_pJE->Release();
        CoUninitialize();
    }
}

//------------------------------------------------------------------------------
// CJView::m_FatalError:
//
// Print a formatted error message to stderr
//
// Returns: Nothing
//------------------------------------------------------------------------------

void CJView::m_FatalError
(
    INT idString,
    ...
)
{
    CHAR szFmt[BUFSIZE];
    va_list va;
    va_start(va, idString);

    LoadString(NULL, IDS_ERROR, szFmt, sizeof(szFmt));
    fprintf(stderr, szFmt);

    if (idString)
        LoadString(NULL, idString, szFmt, sizeof(szFmt));
    else
        lstrcpy(szFmt, "%s");

    vfprintf(stderr, szFmt, va);
    va_end(va);
    fprintf(stderr, "\n");
}

//------------------------------------------------------------------------------
// CJView::m_FatalErrorHR:
//
//      Print a formatted error followup by an hresult tp stderr
//------------------------------------------------------------------------------

void CJView::m_FatalErrorHR
(
    HRESULT hr,
    INT     idString,
    ...
)
{
    CHAR  szFmt[BUFSIZE];
    CHAR  buf[BUFSIZE];
    DWORD res;
    va_list va;
    va_start(va, idString);

    LoadString(NULL, IDS_ERROR, szFmt, sizeof(szFmt));
    fprintf(stderr, szFmt);
    LoadString(NULL, idString, szFmt, sizeof(szFmt));
    vfprintf(stderr, szFmt, va);
    va_end(va);

    res = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL,
                        (DWORD)hr,
                        LOCALE_SYSTEM_DEFAULT,
                        buf,
                        sizeof(buf),
                        NULL);

    CHAR szNoMain[BUFSIZE] = "";

    if (!res)
    {
        CHAR szSCODE[BUFSIZE];

        LoadString(NULL, IDS_SCODE, szSCODE, sizeof(szSCODE));
        sprintf(buf, szSCODE, (DWORD)hr);
    }
    else
    {
        // Now we check if the error is "Member not found", and if it is, we
        // will append some additional info to the error message letting
        // the user know it was main() that could not be found, since that
        // is the only time this message should be generated.
        
        if (hr == DISP_E_MEMBERNOTFOUND)
        {
            CHAR sz[BUFSIZE] = "";

            LoadString(NULL, IDS_NOMAIN, sz, sizeof(sz));
            sprintf(szNoMain, sz, m_pszClassName, m_pszClassName);
        }
        else
            *szNoMain = '\0';
    }


    fprintf(stderr, ": %s\n", buf);
    if (*szNoMain)
        fprintf(stderr, "%s", szNoMain);
}

//------------------------------------------------------------------------------
// CJView::m_InitComAndJava:
//
// Initializes COM and obtains the neccessary interfaces from the Java VM
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------

BOOL CJView::m_InitComAndJava ()
{
    HRESULT           hr   = E_UNEXPECTED;
    IClassFactory    *pcf  = NULL;

    hr = CoInitialize(NULL);

    if (FAILED(hr))
    {
        m_FatalErrorHR(hr, IDS_COULDNOTINITOLE);
    }
    else
    {
        hr = CoGetClassObject(CLSID_JavaExecute,
                              CLSCTX_INPROC_SERVER |
                              CLSCTX_INPROC_HANDLER |
                              CLSCTX_LOCAL_SERVER,
                              NULL,
                              IID_IClassFactory,
                              (LPVOID*)(&pcf));
        if (FAILED(hr))
        {
            m_FatalErrorHR(hr, IDS_JAVAVM);
        }
        else
        {
            hr = pcf->CreateInstance(NULL, IID_IJavaExecute2, (LPVOID *)(&m_pJE));
            if (FAILED(hr))
            {
                m_pJE = NULL;
                m_FatalErrorHR(hr, IDS_CLASSLOADER);
            }

            pcf->Release();
        }

        if (NULL == m_pJE)
            CoUninitialize();
    }

    return (m_pJE != NULL);
}

//------------------------------------------------------------------------------
// CJView::MB2WC:
//
//   Converts the multibyte string to a UNICODE string, allocating space
// for the destination string.
//
// Returns: Pointer to newly allocated and converted string, NULL if it fails
//------------------------------------------------------------------------------

LPWSTR CJView::m_MB2WC
(
    LPCSTR szAnsi,
    int    cchAnsi
)
{
   // First, determine size of converted string
   LPWSTR pwsz    = NULL;
   int    cchWide = MultiByteToWideChar(0, 0, szAnsi, cchAnsi, NULL, 0) + 1;

   if (cchWide > 0)
   {
       // Got size so allocate the space and convert the string
       if (pwsz = new WCHAR[cchWide])
          MultiByteToWideChar(0, 0, szAnsi, cchAnsi, pwsz, cchWide);
    }

   return pwsz;
}

//------------------------------------------------------------------------------
// CJView::m_WC2MB:
//
//   Converts the given UNICODE string to a multibyte string, allocating space
// for the destination string.
//
// Returns: Pointer to newly allocated and converted string, NULL if it fails
//------------------------------------------------------------------------------

LPSTR CJView::m_WC2MB
(
   LPCWSTR pwsz,
   int     cchWide
)
{
   // First, determine size of converted string
   LPSTR psz     = NULL;
   int   cchAnsi = WideCharToMultiByte(0, 0, pwsz, cchWide, NULL, 0, NULL, NULL);

   if (cchAnsi > 0)
   {
       // Got size so allocate the space and convert the string
      if (psz = new CHAR[cchAnsi])
          WideCharToMultiByte(0, 0, pwsz, cchWide, psz, cchAnsi, NULL, NULL);
    }

    return psz;
}

//------------------------------------------------------------------------------
// CJView::m_ParseParameters
//
// Parses off the command line arguments following the class simply
// copying them into a list of OLESTRS
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------

BOOL CJView::m_ParseParameters()
{
    m_iArgs = m_ac - 1;

    m_ppszArgs = new LPOLESTR[m_iArgs + 1];
    if (!m_ppszArgs)
    {
        m_FatalError(IDS_OUTOFMEMORY);
        return FALSE;
    }

    (m_ppszArgs)[0] = NULL; // Initially empty!

    // Now, run through the list of arguments and process
    int iNext = 1;
    int i;

    for (i = 0; i < m_iArgs; i++)
    {
        if (!((m_ppszArgs)[i] = m_MB2WC(m_av[iNext++])))
            break;
    }

    // If succesful, mark end of array
    if (i == m_iArgs)
    {
        (m_ppszArgs)[i] = NULL;
    }
    else
    {
        // Clean up if we fail
        int n;

        for (n = 0; n < i; n++)
            deleteSZ(m_ppszArgs[n]);
        deleteSZ(m_ppszArgs);
    }

    return (i == m_iArgs);
}

//------------------------------------------------------------------------------

BOOL CJView::LoadDataResource( DWORD dwResID, BYTE *pBuffer, DWORD *pdwSize )
{
   HMODULE hMod = GetModuleHandle(NULL);
   DWORD   dwBufferSize;
   HRSRC   hRes;
   HANDLE  hLoadedRes;
   PVOID   pData;
   
   if ( !pdwSize || !pBuffer )
      return FALSE;

   dwBufferSize = *pdwSize;
   *pdwSize = 0;
   
   hRes = FindResource( hMod, MAKEINTRESOURCE(dwResID), RT_RCDATA );

   if ( hRes == NULL )
      return FALSE;

   *pdwSize = SizeofResource( hMod, hRes );

   if ( dwBufferSize < *pdwSize )
      return FALSE;

   hLoadedRes = LoadResource( hMod, hRes );

   if ( !hLoadedRes )
      return FALSE;

   pData = LockResource( hLoadedRes );

   CopyMemory( pBuffer, pData, *pdwSize );

   FreeResource( hLoadedRes );
   
   return TRUE;
}

//------------------------------------------------------------------------------
// CJView::Initialize:
//
//  Performs initialization for CJView
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------

BOOL CJView::Initialize ()
{
   // Load the name of the main class file to
   // execute.
   
   char  szBuffer[1024];
   DWORD dwSize = sizeof(szBuffer);

   if ( !LoadDataResource( MAINCLASSNAMERESOURCEID, (BYTE *)szBuffer, &dwSize ) )
   {  
      m_FatalError( IDS_NOCLASSGIVEN );
      return FALSE;
   }
   
   m_pszClassName = new char[ lstrlen(szBuffer) + 1];

   if ( !m_pszClassName )
   {
      m_FatalError( IDS_OUTOFMEMORY );
      return FALSE;
   }

   lstrcpy( m_pszClassName, szBuffer );

   return m_InitComAndJava();
}

//------------------------------------------------------------------------------
// RunMessageLoop:
//      Message pump for OLE
//------------------------------------------------------------------------------

UINT RunMessageLoop(void)
{
    MSG msg;

    // No accelerators to load.  Get and dispatch messages until a WM_QUIT
    // message is received.
    ZeroMemory(&msg, sizeof(msg));

    msg.wParam = S_OK;

    while (GetMessage(&msg, NULL, 0, 0))
      //
      // Dispatch message to target window.
      //
      // We don't have any windows, so there are no window procedures that
      // require TranslateMessage(&msg).
      //
      DispatchMessage(&msg);

    return(msg.wParam);
}

//------------------------------------------------------------------------------
// CJView::ExecuteClass:
//
//  Executes the given class file
//
// Returns: 0 if successful, 1 if not
//------------------------------------------------------------------------------

DWORD _stdcall RunClassThread
(
    PVOID pv
)
{
    CJView* pJV     = (CJView*)pv;
    HRESULT hr;
    int     iResult;

    if ( pJV->m_ParseParameters() )
    {
        // Tell the VM that it should look in the current module for 
        // class files.  The /bindto option of the jexegen tool will 
        // place the resource data in the exe with a resource ID of 
        // 1001 so we tell the VM that is where the data is.
    
        JAVACLASSRESOURCEINFO jcri;
        jcri.hModule      = GetModuleHandle(NULL);
        jcri.dwResourceID = CLASSRESOURCEID;     // Compatible with jexegen.
      
        hr = pJV->m_pJE->SetClassSource( CLASS_SOURCE_TYPE_MODULERESOURCES, 
                                         &jcri, 
                                         sizeof(JAVACLASSRESOURCEINFO) );

        if ( !SUCCEEDED(hr) )
        {
           pJV->m_FatalError( IDS_VMCANTFINDRESOURCE );
           return 0;
        }
        
        // Execute.
        LPOLESTR        pszClassName = pJV->m_MB2WC(pJV->m_pszClassName);
        LPERRORINFO     pIErrorInfo = NULL;
        JAVAEXECUTEINFO jei;

        jei.cbSize       = sizeof(jei);
        jei.dwFlags      = 0;
        jei.pszClassName = pszClassName;
        jei.rgszArgs     = (LPCOLESTR *)(pJV->m_ppszArgs);
        jei.cArgs        = pJV->m_iArgs;
        jei.pszClassPath = NULL;

        hr = pJV->m_pJE->Execute(&jei, &pIErrorInfo);

        if (!SUCCEEDED(hr))
        {
            // Most likely .class file did not exist
            pJV->m_FatalErrorHR (hr, IDS_EXECUTINGCLASS, pJV->m_pszClassName);
            iResult = 1;
        }
        else if (pIErrorInfo)
        {
            // VM threw an exception while running the .class file.  We
            // get the info via the returned IErrorInfo interface
            BSTR bstrError = NULL;

            if (SUCCEEDED(pIErrorInfo->GetDescription(&bstrError)))
            {
                LPSTR pszError = pJV->m_WC2MB(bstrError);

                if (pszError)
                {
                    pJV->m_FatalError (0, pszError);
                    deleteSZ(pszError);
                }
                else
                    pJV->m_FatalError (IDS_UNKNOWNERROR);

                SysFreeString(bstrError);
            }
            else
                pJV->m_FatalError(IDS_UNKNOWNERROR);

            iResult = 1;

            pIErrorInfo->Release();
        }
        else
            // Success.
            iResult = 0;

        deleteSZ(pszClassName);
    }
    else
        iResult = 1;

    // Terminate message pump
    PostThreadMessage(pJV->m_dwMsgLoopThreadID, WM_QUIT, 0, 0);

    return (DWORD)iResult;
}

//------------------------------------------------------------------------------

int __cdecl main
(
    int    ac,
    char **av
)
{
    int     iRet = 1;
    CJView* pJV  = new CJView(ac, av);

    if ( !pJV )
    {
        CHAR szFmt[20];

        LoadString(NULL, IDS_ERROR, szFmt, sizeof(szFmt));
        fprintf(stderr, szFmt);
        LoadString(NULL, IDS_OUTOFMEMORY, szFmt, sizeof(szFmt));
        fprintf(stderr, szFmt);
        fprintf(stderr, "\n");
        return iRet;
    }

    if (pJV->Initialize())
    {
        // OK, we're ready, everything is done on the applet thread
        HANDLE hth;
        DWORD  dwThreadID;

        pJV->m_dwMsgLoopThreadID = GetCurrentThreadId();
        hth = CreateThread(NULL, 0, &RunClassThread, pJV, 0, &dwThreadID);

        if (hth)
        {
            RunMessageLoop();

            // If we returned from RunMessageLoop() as a result of
            // RunClassThread() posting the WM_QUIT message, then the thread
            // will be exiting shortly (if not already).  We wait for it to
            // terminate and grab its exit code.  1/2 second is plenty --
            // if the thread doesn't die by then, something is wrong (we
            // got a quit message from someone else, perhaps?) in which case
            // we return 1 for failure.

            if (WaitForSingleObject (hth, 500) == WAIT_OBJECT_0)
            {
                DWORD   dwRetCode = 1;

                // Thread's dead, baby... thread's dead...
                GetExitCodeThread (hth, &dwRetCode);
                iRet = dwRetCode;
            }
            CloseHandle(hth);
            hth = NULL;
        }
        else
        {
            pJV->m_FatalErrorHR(LAST_WIN32_ERROR_TO_HRESULT(),
                                IDS_NOJAVATHREAD);
        }
    }

    delete pJV;
    return iRet;
}

