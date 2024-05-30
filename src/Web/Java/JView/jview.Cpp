/*
 * jview.cpp - JView front end, including command-line parsing logic.
 *
 * (C) Copyright 1996, Microsoft Corporation and it suppliers.
 */

#pragma hdrstop

#include "jview.h"
#include "javaprop.hpp"

// Macros

#define WIN32_ERROR_TO_HRESULT(err)    MAKE_SCODE(SEVERITY_ERROR, FACILITY_WIN32, (err))

#define WIN32_RESULT_TO_HRESULT(err)   ((err) == ERROR_SUCCESS ? S_OK : WIN32_ERROR_TO_HRESULT(err))

#define LAST_WIN32_ERROR_TO_HRESULT()  WIN32_RESULT_TO_HRESULT(GetLastError())

#define APPLETVIEWER "sun.applet.AppletViewer"

//------------------------------------------------------------------------------
// LoadOemString
//
// Wrapper for the Win32 LoadString API that translates the string to the OEM
// character set before returning it to the caller.
//------------------------------------------------------------------------------

BOOL LoadOemString(HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int
    nBufferMax)
{
    BOOL fResult;

    fResult = LoadString(hInstance, uID, lpBuffer, nBufferMax);

    if (fResult)
        CharToOem(lpBuffer, lpBuffer);

    return fResult;
}

//------------------------------------------------------------------------------
// CJView::CJView:
//    Constructor
//------------------------------------------------------------------------------
CJView::CJView (int ac, char **av) : m_ac (ac), m_av (av)
{
    m_fApplet      = FALSE;
    m_fPause       = FALSE;
    m_fVerify      = FALSE;
    m_pszClassPath = NULL;
    m_pszAppend    = NULL;
    m_pszPrepend   = NULL;
    m_pszClassName = NULL;
    m_ppszArgs     = NULL;
    m_iArgs        = 0;
    m_pJE          = NULL;
    m_pProperties  = NULL;
}

//------------------------------------------------------------------------------
// CJView::~CJView:
//    Destructor
//------------------------------------------------------------------------------
CJView::~CJView ()
{
    deleteSZ(m_pszClassPath);
    deleteSZ(m_pszClassName);
    deleteSZ(m_pszAppend);
    deleteSZ(m_pszPrepend);

    if (m_ppszArgs)
    {
        INT n = 0;

        while (m_ppszArgs[n] != NULL)
            delete [] m_ppszArgs[n++];
        delete [] m_ppszArgs;
    }

    if (m_pProperties)
    {
        m_pProperties->Release();
        delete(m_pProperties);
    }

    if (m_pJE)
    {
        m_pJE->Release();
        CoUninitialize();
    }
}

//------------------------------------------------------------------------------
// CJView::m_Pause:
//
// -p was given on the command line, and we have an error, thus we display
// amessage to the user to press a key to terminate JView, thus allowing enough
// time to read the message before JView termnates and the console it was
// running in goes away if being executed from the IDE
//
// Returns: Nothing
//------------------------------------------------------------------------------
void CJView::m_Pause()
{
    CHAR szText[BUFSIZE];

    LoadOemString(NULL, IDS_PRESSANYKEY, szText, sizeof(szText));
    fprintf(stderr, "%s", szText);
    _getch();
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


    LoadOemString(NULL, IDS_ERROR, szFmt, sizeof(szFmt));
    fprintf(stderr, szFmt);

    if (idString)
        LoadOemString(NULL, idString, szFmt, sizeof(szFmt));
    else
        lstrcpy(szFmt, "%s");

    vfprintf(stderr, szFmt, va);
    va_end(va);
    fprintf(stderr, "\n");

    if (m_fPause)
        m_Pause();
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

    LoadOemString(NULL, IDS_ERROR, szFmt, sizeof(szFmt));
    fprintf(stderr, szFmt);
    LoadOemString(NULL, idString, szFmt, sizeof(szFmt));
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

        LoadOemString(NULL, IDS_SCODE, szSCODE, sizeof(szSCODE));
        sprintf(buf, szSCODE, (DWORD)hr);
    }
    else
    {
        // Convert ANSI string returned by FormatMessage to OEM.
        CharToOem(buf, buf);

        // Now we check if the error is "Member not found", and if it is, we
        // will append some additional info to the error message letting
        // the user know it was main() that could not be found, since that
        // is the only time this message should be generated.
        if (hr == DISP_E_MEMBERNOTFOUND)
        {
            CHAR sz[BUFSIZE] = "";

            LoadOemString(NULL, IDS_NOMAIN, sz, sizeof(sz));
            sprintf(szNoMain, sz, m_pszClassName, m_pszClassName);
        }
        else
            *szNoMain = '\0';
    }

    fprintf(stderr, ": %s\n", buf);
    if (*szNoMain)
        fprintf(stderr, "%s", szNoMain);

    if (m_fPause)
        m_Pause();
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
            hr = pcf->CreateInstance(NULL, IID_IJavaExecute, (LPVOID *)(&m_pJE));
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
   //--------------------------------------------------------------------------
   LPWSTR pwsz    = NULL;
   int    cchWide = MultiByteToWideChar(0, 0, szAnsi, cchAnsi, NULL, 0) + 1;

   if (cchWide > 0)
   {
       // Got size so allocate the space and convert the string
       //----------------------------------------------------------------------
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
   //--------------------------------------------------------------------------
   LPSTR psz     = NULL;
   int   cchAnsi = WideCharToMultiByte(0, 0, pwsz, cchWide, NULL, 0, NULL, NULL);

   if (cchAnsi > 0)
   {
       // Got size so allocate the space and convert the string
       //----------------------------------------------------------------------
      if (psz = new CHAR[cchAnsi])
          WideCharToMultiByte(0, 0, pwsz, cchWide, psz, cchAnsi, NULL, NULL);
    }

    return psz;
}


//------------------------------------------------------------------------------
// CJView::m_newSZ:
//
// Allocates the given string, generating OUT OF MEMORY if it fails
//
// Returns: LPSTR to allocated buffer if successful, NULL if not
//------------------------------------------------------------------------------
LPSTR CJView::m_newSZ
(
    int cBytes
)
{
    LPSTR psz = new CHAR[cBytes + 1]; // +1 for \0

    if (!psz)
        m_FatalError(IDS_OUTOFMEMORY);

    return psz;
}

//------------------------------------------------------------------------------
// CJView::m_AppendPathString
//
// Appends the given path the the other given path, allocating and freeing
// as neccessary
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------
BOOL CJView::m_AppendPathString
(
    LPSTR *ppszPath,
    LPSTR  pszAppend
)
{
    LPSTR psz    = NULL;
    BOOL  fSemi2 = *CharPrev(pszAppend, pszAppend + lstrlen(pszAppend)) != ';';

    if (*ppszPath)
    {
        // Been here before, so we append the given string to the given path
        //----------------------------------------------------------------------
        if (!(psz = m_newSZ(lstrlen(*ppszPath))))
            return FALSE;

        lstrcpy(psz, *ppszPath);
        deleteSZ(*ppszPath);

        BOOL fSemi1 = *CharPrev(psz, psz + lstrlen(psz)) != ';';

        if (!(*ppszPath = m_newSZ(lstrlen(psz) + lstrlen(pszAppend) + fSemi1 + fSemi2)))
        {
            deleteSZ(psz);
            return FALSE;
        }

        lstrcpy(*ppszPath, psz);

        // Add semi-colon between paths if original path did not have one
        //----------------------------------------------------------------------
        if (fSemi1)
            lstrcat(*ppszPath, ";");

        lstrcat(*ppszPath, pszAppend);
        deleteSZ(psz);
    }
    else
    {
        // First time here, so copy Append string into Path
        //----------------------------------------------------------------------
        if (!(*ppszPath = m_newSZ(lstrlen(pszAppend) + fSemi2)))
            return FALSE;

        lstrcpy(*ppszPath , pszAppend);
    }

    // Append final semi-colon if string being append does not have one
    //--------------------------------------------------------------------------
    if (fSemi2)
        lstrcat(*ppszPath, ";");

    return TRUE;
}

//------------------------------------------------------------------------------
// CJView::m_DisplayUsage:
//
//  Displays the usage text for JView.exe
//
// Returns: Nothing
//------------------------------------------------------------------------------
VOID CJView::m_DisplayUsage ()
{
    // NOTE: All usage lines must be sequential String
    //       IDS starting with IDS_USAGE1
    CHAR sz[BUFSIZE];
    INT  i = 0;

    m_DisplayBanner();

    while (TRUE)
    {
        LoadOemString(NULL, IDS_USAGE1 + (i++), sz, sizeof(sz));
        if (*sz == '~')
            break;
        printf(sz);
    }
}

//------------------------------------------------------------------------------
// CJView::m_ParseSwitches:
//
//  Parses off the switches portion of the command line
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------
BOOL CJView::m_ParseSwitches
(
    int *piArg
)
{
    BOOL   fSuccess = TRUE;
    BOOL   fReplace = m_pszClassPath != NULL;
    LPSTR *ppsz;
    LPSTR  psz;

    *piArg = 1;

    // We support both '-' and '/' switch designators
    //--------------------------------------------------------------------------
    while ((*piArg < m_ac) && ((m_av[*piArg][0] == '-') || (m_av[*piArg][0] == '/')))
    {
        psz = CharNext(m_av[*piArg]);
        
		// Check for the -D switch prior to CharLowering the switch string.

		if ( (*psz == 'D' || *psz == 'd') && (*(psz+1)==':') )
        {
            char *pszPropStr = psz+2;

            if ( *pszPropStr == '\0' )
            {
                m_FatalError(IDS_INVALIDSWITCH, psz);
                fSuccess = FALSE;
                break;
            }

            // If we don't already have a properties object, create one.
            if ( !m_pProperties )
            {
                m_pProperties = new(CEnumJAVAPROPERTY);

                if (!m_pProperties)
                {
                    m_FatalError(IDS_OUTOFMEMORY);
                    fSuccess = FALSE;
                    break;
                }
            }

            // Add the property to the property enumerator.
            m_pProperties->Add(psz+2);
        }
		else
		{
			// All other switches are case insensitive, so just knock 'em down to 
			// lowercase here.

            CharLower(psz);
    
            // Check for usage switch first.  This is only valid as first switch
            //----------------------------------------------------------------------
            if (*piArg == 1 && lstrcmp(psz, "?") == 0)
            {
             m_DisplayUsage();
                fSuccess = FALSE;
                break;
            }
    
            // Check for "run in sun.applet.AppletViewer switch" , -a
            if (lstrcmp(psz, "a") == 0)
                m_fApplet = TRUE;
            // Check for "pause after error switch" , -p
            else if (lstrcmp(psz, "p") == 0)
                m_fPause = TRUE;
            // Check for "verify all" switch, -v
            else if (lstrcmp(psz, "v") == 0)
                m_fVerify = TRUE;
            // Silently ignore the old "quiet" switch for compatibility with
            // existing scripts.
            else if (lstrcmp(psz, "q") == 0)
                ;
            else
            {
                // Check for classpath switches -cp, -cp:p, or -cp:a
                //------------------------------------------------------------------
                BOOL fAppend  = FALSE;
                BOOL fPrepend = FALSE;
    
                if (           !lstrcmp(psz, "cp")    ||
                   (fPrepend = !lstrcmp(psz, "cp:p")) ||
                   (fAppend  = !lstrcmp(psz, "cp:a")))
                {
                    // We have classpath switch, so check for path.  If not given,
                    // i.e, we're out of arguments, it's a bogus command line
                    //--------------------------------------------------------------
                    if (++(*piArg) == m_ac ||
                       (m_av[*piArg][0] == '-' || m_av[*piArg][0] == '/'))
                    {
                        // We're about to exit, so we don't have to worry about
                        // losing information in the ANSI to OEM conversion.
                        CharToOem(m_av[*piArg - 1], m_av[*piArg - 1]);
    
                        m_FatalError(IDS_NOPATHGIVEN, m_av[*piArg - 1]);
                        fSuccess = FALSE;
                        break;
                    }
    
                    // If we are given a class path on the command line and we also
                    // have a classpath from the environment variable CLASSPATH,
                    // the one given on the command line instructs us to ignore the
                    // environment variable, and we instead append/prepend other
                    // paths to this one instead
                    //--------------------------------------------------------------
                    if (fReplace && !(fPrepend || fAppend))
                    {
                        deleteSZ(m_pszClassPath);
                        fReplace = FALSE;
                    }
    
                    ppsz = fPrepend ? &m_pszPrepend : (fAppend ? &m_pszAppend :
                                                                 &m_pszClassPath);
                    m_AppendPathString(ppsz, m_av[*piArg]);
                }
                else
                {
                    // We're about to exit, so we don't have to worry about
                    // losing information in the ANSI to OEM conversion.
                    CharToOem(m_av[*piArg], m_av[*piArg]);
    
                    // Bogus switch!
                    m_FatalError(IDS_INVALIDSWITCH, m_av[*piArg]);
                    fSuccess = FALSE;
                    break;
                }
            }
        }

        (*piArg)++;
    }

    return fSuccess;
}

//------------------------------------------------------------------------------
// CJView::m_ParseParameters
//
// Parses off the remaining command line arguments following the class simply
// copying them into a list of OLESTRS
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------
BOOL CJView::m_ParseParameters
(
    int iNext
)
{
    // If applet or stand-alone, we need a values array
    //--------------------------------------------------------------------------
    m_iArgs = m_ac - iNext;

    m_ppszArgs = new LPOLESTR[m_iArgs + 1];
    if (!m_ppszArgs)
    {
        m_FatalError(IDS_OUTOFMEMORY);
        return FALSE;
    }

    (m_ppszArgs)[0] = NULL; // Initially empty!

    // Now, run through the list of arguments and process
    //--------------------------------------------------------------------------
    int i;

    for (i = 0; i < m_iArgs; i++)
    {
        if (!((m_ppszArgs)[i] = m_MB2WC(m_av[iNext++])))
            break;
    }

    // If succesful, mark end of array
    //--------------------------------------------------------------------------
    if (i == m_iArgs)
    {
        (m_ppszArgs)[i] = NULL;
    }
    else
    {
        // Clean up if we fail
        //----------------------------------------------------------------------
        int n;

        for (n = 0; n < i; n++)
            deleteSZ(m_ppszArgs[n]);
        deleteSZ(m_ppszArgs);
    }

    return (i == m_iArgs);
}

//------------------------------------------------------------------------------
// CJView::ParseCommandLine:
//
//  Parses the command line, which must be in the format:
//
//  JView [switches] ClassName [Parameters]
//
//  switches:   None          :  Invoke main()
//              -a            :  Run as Applet
//              -cp   <path>  :  Set CLASSPATH to <path.
//              -cp:p <path>  :  Prepend <path> to CLASSPATH
//              -cp:a <path>  :  Append  <path> to CLASSPATH
//
//  Classname:  Class file to run.  Valid previously compiled .JAVA file(s)
//
//  Parameters: Name=Value
//
//              if value contains spaces, value must be contained in double
//              quotes
//
//              Name="Value contains spaces"
//
// Returns: TRUE if successful, FALSE if not
//------------------------------------------------------------------------------
BOOL CJView::ParseCommandLine ()
{
    // Must have at least one command line arguement of class name
    // Argument 0 is JVIEW itself
    //--------------------------------------------------------------------------
    if (m_ac == 1)
    {
        m_DisplayUsage();
        return FALSE;
    }

    // Get current CLASSPATH from VM.  We start with this, and append, prepend,
    // or replace it with what we find on the command line
    //--------------------------------------------------------------------------
    LPOLESTR psz = NULL;

    if (m_pszClassPath = new CHAR[1])
        *m_pszClassPath = 0;

    // First thing we check for are switches, processing all arguments that
    // begin with "-".
    // NOTE: All switches must come before class name and parameters
    //--------------------------------------------------------------------------
    INT i;

    if (!m_ParseSwitches(&i))
        return FALSE;

    // Next on the command line should be the class file to execute.  If no more
    // arguments, it's a bogus command line
    //--------------------------------------------------------------------------
    BOOL fSuccess = TRUE;

    if (i == m_ac)
    {
        m_FatalError(IDS_NOCLASSGIVEN);
        fSuccess = FALSE;
    }
    else
    {
        // OK, we have another argument, so whatever it is we simply treat it as
        // the class file name and let the VM deal with verifying it.
        //----------------------------------------------------------------------
        if (m_pszClassName = m_newSZ(lstrlen(m_fApplet ? APPLETVIEWER : m_av[i])))
        {
            lstrcpy(m_pszClassName, m_fApplet ? APPLETVIEWER : m_av[i++]);

            // Finally, if we have any more arguments, they are all treated as
            // parameters to be used by the class
            //------------------------------------------------------------------
            if (i < m_ac)
                fSuccess = m_ParseParameters(i);
        }
    }

    if (fSuccess)
    {
        // Build final path string
        //----------------------------------------------------------------------
        if (m_pszPrepend)
        {
            if (m_pszClassPath)
                m_AppendPathString(&m_pszPrepend, m_pszClassPath);
            deleteSZ(m_pszClassPath);
            m_pszClassPath = m_pszPrepend;
            m_pszPrepend   = NULL;
        }

        if (m_pszAppend)
        {
            if (m_pszClassPath)
            {
                m_AppendPathString(&m_pszClassPath, m_pszAppend);
                deleteSZ(m_pszAppend);
            }
            else
            {
                m_pszClassPath = m_pszAppend;
                m_pszAppend    = NULL;
            }
        }
    }

    return fSuccess;
}

//------------------------------------------------------------------------------
// CJView::m_DisplayBanner:
//
//  Displays the banner for JView.exe
//
// Returns: Nothing
//------------------------------------------------------------------------------
VOID CJView::m_DisplayBanner ()
{
    // Get FileVersion info
    //--------------------------------------------------------------------------
    DWORD dwVer = 0;

    CHAR szFile[MAX_PATH];

    GetModuleFileName(NULL, szFile, sizeof(szFile));

    VS_FIXEDFILEINFO *lpInfo;
    DWORD  dw;
    DWORD  dwSize = GetFileVersionInfoSize(szFile, &dw);
    LPVOID lpData = (LPVOID)new CHAR[dwSize];

    GetFileVersionInfo(szFile, 0, dwSize, lpData);

    // Get File Version and File Description
    //--------------------------------------------------------------------------
    UINT ui;
    VerQueryValue (lpData, "\\", (LPVOID*)&lpInfo, &ui);

    CHAR sz[BUFSIZE];

    LoadOemString(NULL, IDS_BANNER1, sz, sizeof(sz));
    printf(sz, HIWORD(lpInfo->dwFileVersionMS),
               LOWORD(lpInfo->dwFileVersionMS),
               LOWORD(lpInfo->dwFileVersionLS));
    LoadOemString(NULL, IDS_BANNER2, sz, sizeof(sz));
    printf(sz);

    delete lpData;
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
   return m_InitComAndJava();
}

//------------------------------------------------------------------------------
// RunMessageLoop:
//      Message pump for OLE
//
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
// CJView::SetSystemProperties:
//
// Will inform the VM of any additional system properties that we want to
// set.

HRESULT CJView::SetSystemProperties()
{
    HRESULT        hr;
    IJavaExecute2 *pije2;

    // If no properties defined, bail.
    if ( !m_pProperties )
        return S_OK;

    // Query for the IJavaExecute2 interface off of the existing
    // IJavaExecute interface.
    if (m_pJE->QueryInterface(IID_IJavaExecute2, (LPVOID*)&pije2) == S_OK)
    {
        // We found IJavaExecute2, set the system properties.
        hr = pije2->SetSystemProperties( (IEnumJAVAPROPERTY *)m_pProperties);
        pije2->Release();
    }
    else
    {
        // If the QI failed, this current VM does not support IJavaExecute2
        hr = E_FAIL;
        m_FatalError(IDS_PROPSNOTSUPPORTED);
    }

    return hr;
}

//------------------------------------------------------------------------------
// CJView::ExecuteClass:
//
//  Executes the given class file
//
// Returns: result of IJavaExecute::Execute
//------------------------------------------------------------------------------

HRESULT CJView::ExecuteClass (LPERRORINFO *ppIErrorInfo)
{
    LPOLESTR        pszClassName;
    LPOLESTR        pszClassPath;
    JAVAEXECUTEINFO jei;

    pszClassName = m_MB2WC(m_pszClassName);
    pszClassPath = m_MB2WC(m_pszClassPath);

    jei.cbSize       = sizeof(jei);
    jei.dwFlags      = m_fVerify ? JEIF_VERIFYCLASSES : 0;
    jei.pszClassName = pszClassName;
    jei.rgszArgs     = (LPCOLESTR *)(m_ppszArgs);
    jei.cArgs        = m_iArgs;
    jei.pszClassPath = pszClassPath;

    HRESULT hr = m_pJE->Execute(&jei, ppIErrorInfo);

    deleteSZ(pszClassPath);
    deleteSZ(pszClassName);
    return hr;
}


//------------------------------------------------------------------------------
// RunClassThread
//
//  Executes the given class file.  If not found, executes without .class
//  extension, if it has it.
//
// Returns: 0 if successful, 1 if not
//------------------------------------------------------------------------------

DWORD _stdcall RunClassThread
(
    PVOID pv
)
{
    CJView* pJV     = (CJView*)pv;
    int     iResult = 1;            // Assume failure.

    if (pJV->ParseCommandLine())
    {
        HRESULT hr;
        LPERRORINFO     pIErrorInfo = NULL;

        // Check for prepended path

        int len = strlen(pJV->m_pszClassName);

        if (len > 2 && (pJV->m_pszClassName[1] == ':' || strchr(pJV->m_pszClassName,'\\') != NULL))
        {
            char *fullname = pJV->m_newSZ(MAX_PATH);
            char *endofpath;

            if (GetFullPathName(pJV->m_pszClassName, MAX_PATH+1, fullname, &endofpath))
            {
                // Convert to long filename, if needed

                WIN32_FIND_DATA findinfo;
                HANDLE hfind;

                hfind = FindFirstFile(fullname, &findinfo);

                if (hfind == INVALID_HANDLE_VALUE)
                {
                    // Try appending a .class extension

                    strcat(endofpath, ".class");

                    hfind = FindFirstFile(fullname, &findinfo);
                }

                if (hfind != INVALID_HANDLE_VALUE)
                {
                    // Split path from name

                    *(endofpath-1) = '\0';

                    // Create the real class name and update length

                    deleteSZ(pJV->m_pszClassName);
                    len = lstrlen(findinfo.cFileName);
                    pJV->m_pszClassName = pJV->m_newSZ(len);
                    lstrcpy(pJV->m_pszClassName, findinfo.cFileName);

                    // Prepend to specified path

                    if (*pJV->m_pszClassPath == '\0')
                    {
                        deleteSZ(pJV->m_pszClassPath);
                        pJV->m_pszClassPath = fullname;
                    }
                    else
                    {
                        pJV->m_AppendPathString(&fullname, pJV->m_pszClassPath);
                        deleteSZ(pJV->m_pszClassPath);
                        pJV->m_pszClassPath = fullname;
                    }

                    FindClose(hfind);
                }
            }

            // else let the vm deal with whatever was specified.
        }

        // Check for .class extension.

        const char classext1[] = ".cla";
        const int classext1len = sizeof(classext1)-1;
        const char classext2[] = ".class";
        const int classext2len = sizeof(classext2)-1;

        char *classnameext = NULL;

        if (len > classext1len)
        {
            char *ext = pJV->m_pszClassName+len-classext1len;

            if (_stricmp(ext, classext1) == 0)
            {
                // Truncate at extension.

                *ext = '\0';
                classnameext = ext;
            }
            else
            {
                // Try the full extension.

                ext -= classext2len-classext1len;

                if (_stricmp(ext, classext2) == 0)
                {
                    *ext = '\0';
                    classnameext = ext;
                }
            }
        }

        // Set any user defined system properties.
        hr = pJV->SetSystemProperties();

        if ( hr == S_OK )
        {
            hr = pJV->ExecuteClass(&pIErrorInfo);

            if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) && classnameext != NULL)
            {
                // Try the 1 in a billion possibility that someone is trying
                // to execute some class named 'class' in a package.  Of course,
                // if someone has a class with the same name as the package, we
                // hit it first above.

                *classnameext = '.';

                hr = pJV->ExecuteClass(&pIErrorInfo);
            }

            if (!SUCCEEDED(hr))
            {
                // We're about to exit, so we don't have to worry about
                // losing information in the ANSI to OEM conversion.
                CharToOem(pJV->m_pszClassName, pJV->m_pszClassName);

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
                        CharToOem(pszError, pszError);
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
        }
    }

    // Terminate message pump
    PostThreadMessage(pJV->m_dwMsgLoopThreadID, WM_QUIT, 0, 0);

    return (DWORD)iResult;
}

//------------------------------------------------------------------------------
// main() - Entry point for JView
//
// Returns: 0 if successful, 1 if not
//------------------------------------------------------------------------------

#ifdef NO_CONSOLE
#define ENTRYPOINT int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
#else
#define ENTRYPOINT int __cdecl main( int, char ** )
#endif

ENTRYPOINT
{
    int     iRet = 1;
    CJView* pJV  = new CJView(__argc,__argv);

    if (!pJV)
    {
        CHAR szFmt[64];

        LoadOemString(NULL, IDS_ERROR, szFmt, sizeof(szFmt));
        fprintf(stderr, szFmt);
        LoadOemString(NULL, IDS_OUTOFMEMORY, szFmt, sizeof(szFmt));
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

