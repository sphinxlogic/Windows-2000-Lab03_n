
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// LOGPARSE.CPP - Implementation file for your Internet Server
//    LogParse Extension

#include "stdafx.h"
#include "LogParse.h"
#include "urlmon.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;

#define USE_DECODER 1

#define MAX_SIZE        2048
#define LOG_BUF_SIZE    512
#define NUMLOG          23

TCHAR   LogEntries[NUMLOG][LOG_BUF_SIZE] = {
        "",                 //0 remote addr
        "-",                //1 user name, "-" means anonymous
        "",                 //2 request date
        "",                 //3 request time
        "W3SVC",            //4 service type (default = W3SVC)
        "",                 //5 server name
        "",                 //6 server ip
        "0",                //7 elapsed time (default = 0)
        "0",                //8 bytes received (default = 0)
        "0",                //9 bytes sent (default = 0)
        "200",              //a service response code (default = 200)
        "0",                //b system (NT) response code (default = 0)
        "GET",              //c method type  (HEAD,POST, default = GET)
        "",                 //d uri
        "",                 //e user agent
        "-",                //f referrer (default = "-" means unknown)
        "",                 //10 cookie
        "-",                //11 query string ("-" means no query string)
        "",                 //12 duration
        "",                 //13 context
        "",                 //14 client cache
        "-",                //15 metatag
        "-"                 //16 additional parameters (ignored)
    };


///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CLogParseExtension, CHttpServer)
	// TODO: insert your ON_PARSE_COMMAND() and 
	// ON_PARSE_COMMAND_PARAMS() here to hook up your commands.
	// For example:
	DEFAULT_PARSE_COMMAND(LogParse, CLogParseExtension)
	ON_PARSE_COMMAND(LogParse, CLogParseExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("input_text=default")
END_PARSE_MAP(CLogParseExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CLogParseExtension object

CLogParseExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CLogParseExtension implementation

CLogParseExtension::CLogParseExtension()
{
	m_hFile = NULL;
	m_ContentLen = 0;
	m_szEncoding = NULL;
    m_cbURILen = 0;
    m_fInLog = FALSE;
}

CLogParseExtension::~CLogParseExtension()
{
	if (m_szEncoding)
		GlobalFree(m_szEncoding);

}

BOOL CLogParseExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CLogParseExtension command handlers

// pszString : post string (using FORM)
void CLogParseExtension::LogParse(CHttpServerContext* pCtxt, LPTSTR pszString)
{

	StartContent(pCtxt);
	WriteTitle(pCtxt);

	*pCtxt << _T("Server DLL, just shown that we were here. \r\n");

    // real work starts
    DWORD   err;
    DWORD   dwLen = sizeof(DWORD);
    char    buf[LOG_BUF_SIZE];
    DWORD   cbsize = LOG_BUF_SIZE;
    BOOL    bret;
	BOOL    fEncoded = FALSE;

    // get server variables
    if (!pCtxt->GetServerVariable("CONTENT_LENGTH", buf, &dwLen) ||
        !pCtxt->GetServerVariable("REQUEST_METHOD", (void *)LogEntries[12], &cbsize) )
    {
        err = GetLastError();
        *pCtxt << _T("LogParse failed: couldn't get server variables.\r\n");
        goto _exithere;
    }

    if (lstrcmp(LogEntries[12], _T("POST")))
    {
        *pCtxt << _T("LogParse failed: wrong request method.\r\n");
        goto _exithere;
    }
    else    
    {    
		cbsize = LOG_BUF_SIZE;
		m_szEncoding = (LPTSTR)GlobalAlloc(LPTR, LOG_BUF_SIZE);
		if (!m_szEncoding)
		{
			*pCtxt << _T("LogParse failed: couldn't allocate g_szEncoding \r\n");
			goto _exithere;
		}

        if (pCtxt->GetServerVariable("HTTP_CONTENT_TRANSFER_ENCODING", (void *)m_szEncoding, &cbsize))
			fEncoded = TRUE;

		if (*pszString == NULL)
		{
			*pCtxt << _T("LogParse: no posting string \r\n");
			goto _exithere;
		}

		bret = OpenLogFile(pCtxt);
		if (!bret)
		{
			*pCtxt << _T("LogParse: create/open file failed \r\n");
			goto _exithere;
		}

		dwLen = AppendContentToLogfile(pCtxt, pszString, atoi(buf), fEncoded);
		
		ISAPITRACE1("LogParse: server logged   %d bytes\n", dwLen);
		ISAPITRACE1("LogParse: encoding by %s\n", m_szEncoding);

    }
    

_exithere:
	EndContent(pCtxt);

}

BOOL CLogParseExtension::OpenLogFile(CHttpServerContext* pCtxt)
{
	SYSTEMTIME	st;
    TCHAR   szLogPath[MAX_PATH];
    DWORD   cbpath = MAX_PATH;
	TCHAR	pszfile[MAX_PATH];
    HKEY    hkey;

	// generate filename based on date
	GetLocalTime(&st);
    wsprintf(pszfile, "ie%.2d%.2d%.2d.log", st.wYear, st.wMonth, st.wDay);

    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, g_szRegW3SVC, 0, KEY_READ, &hkey))
    {
        *pCtxt << _T("LogParse failed: RegOpenKeyEx\r\n");
	    return FALSE;
    }

	if (ERROR_SUCCESS != RegQueryValueEx(hkey, g_szRegLogFileDirectory, 
                                             NULL, NULL, (LPBYTE)szLogPath, &cbpath))
	{
	    *pCtxt << _T("LogParse failed: GetLogFileDirectory.\r\n");
        RegCloseKey(hkey);
	    return FALSE;	 
    }

    RegCloseKey(hkey);

    lstrcpy(m_szLogFile, szLogPath);
    lstrcat(m_szLogFile, g_szLogFilePath);
	lstrcat(m_szLogFile, pszfile);

    m_hFile = CreateFile(m_szLogFile, GENERIC_READ|GENERIC_WRITE, 0, NULL, 
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (m_hFile == INVALID_HANDLE_VALUE)
        return FALSE;

	SetFilePointer(m_hFile, 0, NULL, FILE_END);

	return TRUE;
}

DWORD CLogParseExtension::AppendContentToLogfile(CHttpServerContext* pCtxt, LPCTSTR pszContent, DWORD ContentLen, BOOL fEncoded)
{
	LPTSTR  pszDecContent = NULL;
	LPTSTR  pszLog = NULL;
    DWORD   dwWritten = 0;

	if (fEncoded)
	{
		DWORD   dwlen;
		//decoding
		dwlen = ContentLen * 4;
		pszDecContent = (LPTSTR)GlobalAlloc(LPTR, dwlen);
		if (DecodeContent(pCtxt, pszContent, ContentLen, pszDecContent, dwlen))
			pszLog = pszDecContent;
        else
            return 0;       // failed to decompress the data somehow
	}
	else
	{
		pszLog = (LPTSTR)pszContent;
		m_ContentLen = lstrlenA(pszLog);
	}

	//transform to W3C flexible log format
	dwWritten = ConvertToW3CFlexible(pCtxt, pszLog);

	if (pszDecContent)
		GlobalFree(pszDecContent);

    return dwWritten;
}

// we need to extract out the decoder's name from "x-filtername" string
BOOL CLogParseExtension::DecodeContent(CHttpServerContext* pCtxt, LPCTSTR pszEncodedString, 
									   DWORD cbEnc, LPTSTR pszDecString, DWORD cbDec)
{
#ifdef USE_DECODER
	LPWSTR	pwszEncoding = NULL;
	LPTSTR  pszEncoding = m_szEncoding;
	DWORD   dwlen;
	BOOL    bInDash = FALSE;
	BOOL	bret = FALSE;
	IEncodingFilterFactory* pEflt = NULL;
    IDataFilter*    pDF = NULL;

	//parse encoding header string
	while (*pszEncoding != 0)
	{
		if (bInDash)
			break;
		
		if (*pszEncoding == '-')
			bInDash = TRUE;

		pszEncoding ++;
	};

	dwlen = (lstrlenA(pszEncoding) + 1) * sizeof(WCHAR);
	pwszEncoding = (LPWSTR)GlobalAlloc(LPTR, dwlen);

	//find/load decoder
    if (!pwszEncoding)
    {
		*pCtxt << _T("LogParse: DecodeContent mem error \r\n");
		goto _exitDecode;
	}

	dwlen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszEncoding, lstrlenA(pszEncoding),
			pwszEncoding, dwlen);

	if (dwlen == 0)
	{
		*pCtxt << _T("LogParse : DecodeContent wide char convert failed\r\n");
		goto _exitDecode;
	}
	
    CoCreateInstance(CLSID_StdEncodingFilterFac, NULL, CLSCTX_INPROC_SERVER,
                                    IID_IEncodingFilterFactory, (void**)&pEflt);

	if (pEflt)
    {                
		pEflt->GetDefaultFilter(pwszEncoding, L"text", &pDF);
        if (pDF)
        {
            LONG lInUsed = 0;
            LONG lOutUsed = 0;
            HRESULT hrCode = NOERROR;

            hrCode = pDF->DoEncode(
                                   0,
                                   cbEnc,
                                   (BYTE *)pszEncodedString, 
                                   cbDec,
                                   (BYTE *)pszDecString, 
                                   cbEnc,
                                   &lInUsed,
                                   &lOutUsed,
                                   0);

            if (SUCCEEDED(hrCode))
            {
                m_ContentLen = (DWORD)lOutUsed;
				bret = TRUE;
            }
            pDF->Release();
        
		}
        
        pEflt->Release();
        
	}   

_exitDecode:
	if (pwszEncoding)
		GlobalFree(pwszEncoding);

	return bret;
#else
	return TRUE;
#endif
}


DWORD CLogParseExtension::ConvertToW3CFlexible(CHttpServerContext* pCtxt, LPTSTR pszClientLog)
{

#ifdef _DEBUG
#define NUMVARS 20

  char varnames[NUMVARS][30] = {
    "AUTH_TYPE",
    "CONTENT_LENGTH",
    "CONTENT_TYPE",
    "PATH_INFO",
    "PATH_TRANSLATED",
    "QUERY_STRING",
    "REMOTE_ADDR",
    "REMOTE_HOST",
    "REMOTE_USER",
    "UNMAPPED_REMOTE_USER",
    "REQUEST_METHOD",
    "SCRIPT_NAME",
    "SERVER_NAME",
    "SERVER_PORT",
    "SERVER_PORT_SECURE",
    "SERVER_PROTOCOL",
    "SERVER_SOFTWARE",
    "ALL_HTTP",
    "HTTP_ACCEPT",
    "URL"
  };

  char buf[1024];
  unsigned long bufsize;

  for (int index = 0; index < NUMVARS; index++) {

    bufsize = 1024;
    if (pCtxt->GetServerVariable (&varnames[index][0], buf, &bufsize)) {

      ISAPITRACE2("[%s] = [%s]\n", &varnames[index], buf);
    }
    else {

      ISAPITRACE1("[%s] = (Oops!)\n", varnames[index]);
    }
  }
#endif

    DWORD  dwFixedBytes = 0;
    DWORD  dwTotalBytes = 0;
    TCHAR  szSpace[] = " ";
    LPTSTR pszServerLog;
    DWORD  dwCount = m_ContentLen + 1;  // over 1 from end
    DWORD  dwmove;
    
    dwFixedBytes = ProcessFixedLogFields(pCtxt);
    dwFixedBytes = dwFixedBytes + NUMLOG*lstrlen(szSpace) + lstrlen(LogEntries[4]) 
                + 6*lstrlen(LogEntries[7]) + lstrlen(LogEntries[10]);

    // parse client log
    m_cbURILen = 0;
    do 
    {
        DWORD   dwthisclientlog = 0;
        DWORD   dwthislog = 0;
        DWORD   dwwritten;

        dwthisclientlog = ProcessClientLog(pCtxt, pszClientLog, &dwmove);
        if (dwthisclientlog == 0)
            break;

        dwthislog = dwFixedBytes + dwthisclientlog;

        // fill in temp buffer
        pszServerLog = (LPTSTR)GlobalAlloc(LPTR, dwthislog);
        if (!pszServerLog)
        {
            ISAPITRACE0("LogParse: mem alloc failed, pszServerLog\n");
            continue;
        }

        int ilog, i;
        int index = 0;
        for (ilog=0; ilog<NUMLOG; ilog++)
        {
            for (i=0; LogEntries[ilog][i]; i++, index++)
                pszServerLog[index] = LogEntries[ilog][i];

            // Add space
            pszServerLog[index++] = ' ';
        }

        // null terminated
        pszServerLog[index] = 0;

        // write to server log file
        WriteFile(m_hFile, pszServerLog, index, &dwwritten, NULL);
        dwTotalBytes += dwwritten;
        GlobalFree(pszServerLog);

        // keep track of end of string
        dwCount -= dwmove;
        if (dwCount == 0)
            break;

        pszClientLog += dwmove;

    } while (TRUE);

	CloseHandle(m_hFile);
	
    return dwTotalBytes;
}

#define NUMSERVER   7
#define NUMCLIENT   5

char Varnames[NUMSERVER][20] = {
    "REMOTE_ADDR",
    "REMOTE_USER",
    "SERVER_NAME",
    "SERVER_PORT",
    "HTTP_USER_AGENT",
    "HTTP_REFERER",
    "QUERY_STRING"
    };

int SvrIdx[NUMSERVER+NUMCLIENT] = {0, 1, 5, 6, 14, 15, 17, 19, 20, 2, 3, 18};


DWORD CLogParseExtension::ProcessFixedLogFields(CHttpServerContext* pCtxt)
{
    DWORD   dwBytes;
    DWORD   cbsize;
    char    buf[1024];

    // remote addr
    dwBytes = 0;
    for (int i=0; i<NUMSERVER; i++)
    {
        cbsize = LOG_BUF_SIZE;
        if (!pCtxt->GetServerVariable(Varnames[i], buf, &cbsize))
        {
            ISAPITRACE1("LogParse: can't get %s\n", Varnames[i]);
        }
        else
        {
            if (*buf)
                lstrcpy(LogEntries[SvrIdx[i]], buf);
        }
        dwBytes += lstrlen(LogEntries[SvrIdx[i]]);
    }

    // method type
    dwBytes += lstrlen(LogEntries[12]);

    // cookie
    cbsize = LOG_BUF_SIZE;
    if (!GetUserCookie(pCtxt, LogEntries[16], &cbsize))
    {
        ISAPITRACE0("LogParse: can't get request method\n");
        cbsize = 0;
    }
    dwBytes += cbsize;

    return dwBytes;
}


BOOL CLogParseExtension::GetUserCookie(CHttpServerContext* pCtxt, LPTSTR pszCookie, LPDWORD pcb)
{
    BOOL    bret = FALSE;
    DWORD   sizeof_cookies = sizeof_header;
    char *  cookie;

    cookie = (char *)GlobalAlloc(LPTR, sizeof_cookies);
    if (!cookie)
        return bret;

    char * interse_cookie = &cookie[0];   // interse' cookie

    // Obtain the list of cookies.
    if (pCtxt->GetServerVariable("ALL_HTTP", interse_cookie, &sizeof_cookies))
    {
        if (interse_cookie = strstr (interse_cookie, "HTTP_COOKIE:"))
        {
            // Does the client already have a Interse' cookie? Also, remove cookies
            // to the left of the Interse' cookie.
            //
            if (interse_cookie = strstr (interse_cookie, interselog_cookiename))
            {
                // Remove cookies to the right of Interse' cookie.
                //
                char * next_cookie = strstr (interse_cookie, ";");
                if (next_cookie) *next_cookie = 0;
                *pcb = lstrlen(interse_cookie);
                if (*pcb >= LOG_BUF_SIZE)
                {
                    ISAPITRACE0("LogParse: cookie memory overflow!!\n");
                }
                lstrcpy(pszCookie, interse_cookie);
                bret = TRUE;
            }
            else
            {
                *pszCookie = 0;
                *pcb = 0;
            }
        }
        else
        {
            *pszCookie = 0;
            *pcb = 0;
        }
    }

    return bret;
}

/*
 * client log is in "extended server log format"
 * #Fields: s-URI
 * http://www.msnbc.com/news/66784.asp
 * #Fields: x-context x-cache x-date x-time x-duration x-meta
 * N 1 06-10-1997 14:03:54 00:12:32 customestring
 * N 1 06-11-1997 10:13:04 00:05:13
 * N 1 06-17-1997 04:07:15 00:11:33
 */

DWORD CLogParseExtension::ProcessClientLog(CHttpServerContext* pCtxt, LPTSTR pszClientLog, LPDWORD pMove)
{
    char*   pszNext;
    DWORD   cbBytes = 0;
    LPTSTR  pszInbuf = pszClientLog;

    if (m_cbURILen == 0)
    {
        // look for URI
        if (*pszClientLog == ' ')
            pszClientLog ++;

        if (memicmp(pszClientLog, g_szURIFields, lstrlen(g_szURIFields)))
            return 0;

        pszClientLog += lstrlen(g_szURIFields);
        pszNext = strstr(pszClientLog, " ");
        if (pszNext)
            *pszNext = 0;

        lstrcpy(LogEntries[13], pszClientLog);
        m_cbURILen = pszNext - pszClientLog;
        pszClientLog += m_cbURILen;
        pszClientLog ++;    // the space  (pNext)
    }

    cbBytes = m_cbURILen;
 
    // next line should be either log or #Fields: x-context.... or end_of_string
    if (!memicmp(pszClientLog, g_szFields, lstrlen(g_szFields)))
    {
        pszClientLog = strstr(pszClientLog, g_szMeta);
        pszClientLog += lstrlen(g_szMeta);
        if (*pszClientLog == ' ')
            pszClientLog ++;        // the 1st space in log cache!! 
    }
    else if (*pszClientLog == 0)
    {
        // end of log string
        return 0;
    }

    for (int i = NUMSERVER; i < NUMSERVER+NUMCLIENT; i ++)
    {
        pszNext = strstr(pszClientLog, " ");
        if (pszNext)
            *pszNext = 0;
        lstrcpy(LogEntries[SvrIdx[i]], pszClientLog);
        cbBytes += lstrlen(LogEntries[SvrIdx[i]]);
        pszClientLog += lstrlen(LogEntries[SvrIdx[i]]);
        pszClientLog ++ ;   // the space
    }

    // look for URI
    if (!memicmp(pszClientLog, g_szURIFields, lstrlen(g_szURIFields)))
    {
        m_cbURILen = 0;
    }
    //
    *pMove = pszClientLog - pszInbuf;    
    return cbBytes;        

}

// Do not edit the following lines, which are needed by ClassWizard.
#ifdef PROCESS_MESSAGE
BEGIN_MESSAGE_MAP(CLogParseExtension, CHttpServer)
	//{{AFX_MSG_MAP(CLogParseExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif



///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/

/* W3C flexible log file format */
/*
	157.56.230.204		//remote addr
	-					//user name, "-" means anonymous
	06/17/97			//request date
	19:51:44			//request time
	W3SVC				//service type (default = W3SVC)
	A282527				//server name
	157.56.230.168		//server ip
	340					//elapsed time (default = 0)
	450					//bytes received (default = 0)
	123					//bytes sent (default = 0)
	200					//service response code (default = 200)
	0					//system (NT) response code (default = 0)
	GET					//method type  (HEAD,POST, default = GET)
	/impsrvr/index.html	//uri
	Mozilla/2.0 (compatible; MSIE 3.02; WIndows NT)	//user agent
	-					//referrer (default = "-" means unknown)
	INTERSE=157222862038521	//cookie
	-					//query string ("-" means no query string)
	00:00:18			//duration
	N					//context
	1					//client cache
	-					//additional parameters (ignored)
*/
