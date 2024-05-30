
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
/****************************************************************************
*
* HeadDump: requests the default HTML document from the server and prints 
*			along with HTTP headers.
*			Microsoft Corporation (C). L.B.
*	
* PURPOSE: 
* This sample demonstrates how to create and submit HTTP 
* request. Sample requests the default HTML document from the
* server and then display it along with the HTTP transaction headers.
* This sample also allows to access password protected pages. It 
* checks for HTTP server response code and it is "401 Access Denied"
* it asks password and user name and then resubmit request.

*
* This sample features: 
*  - SSL/PCT support
*  - NTLM Authentication (when IE 3.0 or above is installed)
*  - Basic Authentication
*  - Generating standard user name/password UI to get user credentials.
*  - Getting user name and password without UI
*  - getting any document of any MIME type
*  - translation of Internet error codes to the extended error messages
*  - ability to save remote object to a local file (when no local file
*	 specify output goes to STDOUT).
*
* Usage:
*   headdump.exe -h host [-o object] [-p proxy] [-u] [-s] [-?] [-f file]
*		-h host is a HTTP server such as www.server.com 
*		-p proxy is optional proxy, in form: http://proxy:80
*		-o object is optional document to GET, in form: /foobar.htm
*		-u use this flag to bring user name and password UI (optional)
*		-f save remote object as local file  (optional)
*		-? get help
*		-s use SSL (optional)
*
* Samples:
* To get help on command line parameters:
*	C:> headdump.exe -?	
*	
* Note that HeadDump can also invoke ISAPI dll or CGI like this:
* 	C:> headdump.exe -s www.server.name -o /scripts/myisapi.dll 
*
* Since sample generates large output, you may want to pipe to more:
* 	C:> headdump.exe -s www.server.name -o /scripts/myisapi.dll  | more
*
* To save remote HTML object as file:
*	C:> headdump.exe -s www.server.name -o /exe_files/foo.exe -f foo.exe
*
*
* 
****************************************************************************/



#include <windows.h>
#include <wininet.h>
#include <iostream.h>

BOOL ErrorOut  ( DWORD dError, TCHAR * szCallingFunc);
BOOL ParseParams (int argc , CHAR ** argv, CHAR* szServer, CHAR* szObject, 
                  CHAR* szProxy, CHAR * szFile, BOOL& bUi, BOOL& bSSL);
void Usage (CHAR *szName);                  


int main (int argc, char *argv[])
{
 HINTERNET hOpen, hConnect, hReq;
 DWORD  dwSize, dwCode;
 DWORD  dwFlags = INTERNET_FLAG_RELOAD | 
                  INTERNET_FLAG_NO_CACHE_WRITE |
                  INTERNET_FLAG_KEEP_CONNECTION;
                  
 CHAR *lpBuffer, szData[51];
 CHAR szServer[256], szObject [256], szProxy [256], szFile [256];
 BOOL bSSL, bUi;
 HANDLE hFile = NULL;
 INTERNET_PORT dwPort;
 TCHAR szAccept[] = "*/*";
 LPSTR AcceptTypes[2]={0}; 

 
 AcceptTypes[0]=szAccept;



if (!ParseParams ( argc , argv, szServer, szObject, 
                  szProxy,  szFile, bUi, bSSL))
    return (FALSE);

if (szFile [0])
{
	// Open local file
	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, FALSE};
	if  ( !(hFile = CreateFile (szFile, 
		                        GENERIC_WRITE, 
								FILE_SHARE_READ, 
								&sa, 
								CREATE_ALWAYS, 
								FILE_ATTRIBUTE_NORMAL, NULL) ))
	{
		cerr << "Can't open file: " << szFile << " Error: " << GetLastError() << endl;
		return 0;
	}
}



if (szProxy [0] == NULL)
{  
    // No proxy was specified
    if ( !(hOpen = InternetOpen ( "HeadDump",  LOCAL_INTERNET_ACCESS , NULL, 0, 0) ) )
    {
        ErrorOut ( GetLastError(), "InternetOpen");
        return 0;
    }
 }
 else
 {
    // Use proxy server
   if ( !(hOpen = InternetOpen ( "HeadDump",  CERN_PROXY_INTERNET_ACCESS, szProxy, NULL, 0) ) )
   {
        ErrorOut ( GetLastError(), "InternetOpen");
       return 0;
   }
  }
        

if  (bSSL)
{
    dwPort = INTERNET_DEFAULT_HTTPS_PORT;
    dwFlags |= INTERNET_FLAG_SECURE | 
               INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
               INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  ;
}
else
    dwPort = INTERNET_INVALID_PORT_NUMBER;
    
        
if ( !(hConnect = InternetConnect ( hOpen, szServer , dwPort, "",  "", INTERNET_SERVICE_HTTP, 0  , 0) ) )
{
    ErrorOut (GetLastError(), "InternetConnect");
    return 0;
}

if ( !(hReq = HttpOpenRequest (hConnect, "GET", szObject, HTTP_VERSION, "", 
                                (LPCTSTR*) AcceptTypes, dwFlags ,0 )))
{
    ErrorOut (GetLastError(), "HttpOpenRequest");
    return 0;
}


again:
if (!HttpSendRequest (hReq, NULL, 0, NULL, 0) )
{
    ErrorOut (GetLastError(), "HttpSend");
    return 0;
}

dwSize = sizeof (DWORD) ;  
if ( !HttpQueryInfo (hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, NULL))
{
	ErrorOut (GetLastError(), "HttpQueryInfo");
	return FALSE;
}

if ( dwCode == HTTP_STATUS_DENIED || dwCode == HTTP_STATUS_PROXY_AUTH_REQ)
{  

    // We have to read all outstanding data on the Internet handle
    // before we can resubmit request. Just discard the data.
    do
	{
		InternetReadFile (hReq, (LPVOID)szData, 50, &dwSize);
	}
	while (dwSize != 0);

    if (!bUi)
    {
        // This is a secure page.
        cerr << "This page is password protected. " << endl;
    	CHAR szUser[50]="";
    	CHAR szPass[50]="";

    	cerr << "User: ";
    	cin  >> szUser;
    	cerr << "Pass: ";
    	cin  >> szPass;
        if ( !InternetSetOption (hConnect, INTERNET_OPTION_USERNAME, (LPVOID) szUser, lstrlen (szUser) ))
        {
            cerr << "InternetSetOptionFailed: " << GetLastError() << endl;
            return FALSE;
        }
    
        if ( !InternetSetOption (hConnect, INTERNET_OPTION_PASSWORD, (LPVOID) szPass, lstrlen (szPass) ))
        {
            cerr << "InternetSetOptionFailed: " << GetLastError() << endl;
            return FALSE;
        }
        goto again;    
    }
    else
    {
        if ( InternetErrorDlg (GetDesktopWindow(),
                               hReq, 
                               ERROR_INTERNET_INCORRECT_PASSWORD,
                               FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
                               FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
                               FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
                               NULL) == ERROR_INTERNET_FORCE_RETRY)
            goto again;
    }
	
}

                                                                          
// First time we will find out the size of the headers.
HttpQueryInfo (hReq,HTTP_QUERY_RAW_HEADERS_CRLF,  NULL, &dwSize, NULL);
lpBuffer =  new char [dwSize + 1 ];

// Now we call HttpQueryInfo again to get the headers.
if (!HttpQueryInfo (hReq,HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID) lpBuffer,
    &dwSize, NULL))
{
	ErrorOut (GetLastError(), "HttpQueryInfo");
	return FALSE;
}
*(lpBuffer + dwSize) = '\0';
cout << lpBuffer << endl;


do
{
	if (!InternetReadFile (hReq, (LPVOID)szData, 50, &dwSize) )
	{
	 	ErrorOut (GetLastError (), "InternetReadFile");
		return FALSE;
	}
	if (dwSize != 0) 
	{
		if (!hFile)
		{
			// dump text to the screen
			szData[dwSize] = '\0';
			cout << szData;
		}
		else
		{
			DWORD dwWritten;
			if (!WriteFile(hFile,  szData, dwSize,  &dwWritten,  NULL))
            {
              CloseHandle (hFile);
              cerr << "WriteFile to " << szFile << " failed: " <<
				    GetLastError () << endl;
              return FALSE;
            } 
		}
	}
}
while (dwSize);


cout << endl;

if (!InternetCloseHandle (hReq) )
{
    ErrorOut (GetLastError (), "CloseHandle on hReq");
    return FALSE;
}
if (!InternetCloseHandle (hConnect) )
{
    ErrorOut (GetLastError (), "CloseHandle on hConnect");
    return FALSE;
}
if (!InternetCloseHandle (hOpen) )
{
    ErrorOut (GetLastError (), "CloseHandle on hOpen");
    return FALSE;
}


delete [] lpBuffer;

if (hFile)
{
	FlushFileBuffers (hFile);
	CloseHandle (hFile);
}
return TRUE;
}

/****************************************************************************
*
*    FUNCTION: ErrorOut
*
*    PURPOSE: This function is used to get extended Internet error.
*
*    COMMENTS:  Function returns TRUE on success and FALSE on failure.
*
****************************************************************************/

BOOL ErrorOut ( DWORD dError, TCHAR * szCallFunc)
{
    TCHAR szTemp[100] = "", *szBuffer=NULL, *szBufferFinal = NULL;
    char strName[256]="";
    DWORD  dwIntError , dwLength = 0; 
    

    FormatMessage(FORMAT_MESSAGE_FROM_HMODULE,
 	              GetModuleHandle("wininet.dll"),dError,0,
                  (LPSTR)strName,256,NULL);
    wsprintf (szTemp,  "%s error code: %d\nMessage: %s\n", 
    szCallFunc, dError, strName);
	    
	if (dError == ERROR_INTERNET_EXTENDED_ERROR)
	{
		InternetGetLastResponseInfo (&dwIntError, NULL, &dwLength);
		if (dwLength)
		{
			if ( !(szBuffer = (TCHAR *) LocalAlloc ( LPTR,  dwLength) ) )
			{
				lstrcat (szTemp, TEXT ( "Unable to allocate memory to display Internet error code. Error code: ") );
				lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
				lstrcat (szTemp, TEXT ("\n") );
				cerr << szTemp << endl;
				return FALSE;
			}
			if (!InternetGetLastResponseInfo (&dwIntError, (LPTSTR) szBuffer, &dwLength))
			{
				lstrcat (szTemp, TEXT ( "Unable to get Internet error. Error code: ") );
				lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
				lstrcat (szTemp, TEXT ("\n") );
				cerr << szTemp << endl;
				return FALSE;
			}
			if ( !(szBufferFinal = (TCHAR *) LocalAlloc ( LPTR,  (strlen (szBuffer) +strlen (szTemp) + 1)  ) )  )
			{
				lstrcat (szTemp, TEXT ( "Unable to allocate memory. Error code: ") );
				lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
				lstrcat (szTemp, TEXT ("\n") );
				cerr << szTemp << endl;
				return FALSE;
			}
			lstrcpy (szBufferFinal, szTemp);
			lstrcat (szBufferFinal, szBuffer);
			LocalFree (szBuffer);
			cerr <<  szBufferFinal  << endl;
			LocalFree (szBufferFinal);
		}
	}
	else
        cerr << szTemp << endl;
    return TRUE;
}
BOOL ParseParams (int argc , CHAR ** argv, CHAR* szServer, CHAR* szObject, 
                  CHAR* szProxy, CHAR * szFile, BOOL& bUi, BOOL& bSSL)
{
    int i = 1;
    BOOL bServer = FALSE;
    
    szProxy[0]  = NULL, bUi = FALSE, bSSL = FALSE, szFile[0]  = NULL;
    lstrcpy (szObject, "");
    
    while (i < argc)
    {
       if ( *argv[i] != '-')
       {
           Usage (argv[0]);
           return FALSE;
       }
       switch (argv[i][1])
       {
           case 'H':
           case 'h':
              lstrcpy (szServer,argv[i+1]);
              i += 2;
              bServer = TRUE;
           break;
           case 'o':
           case 'O':
              lstrcpy (szObject, argv[i+1]);
              i += 2;
           break;
           
           case 'p':
           case 'P':
              lstrcpy (szProxy, argv[i+1]);
              i += 2;  
           break;    
           
           case 'u':
           case 'U':
              bUi = TRUE;
              i++;  
           break; 
           
           case 's':
           case 'S':
              bSSL = TRUE;
              i++;  
           break; 

           case 'f':
           case 'F':
			  lstrcpy (szFile, argv[i+1]);
              i += 2; 
           break; 
		   
		   case '?':
			   Usage (argv[0]);
			   return FALSE;
		   break;
           default:
               cerr << "Invalid command line argument: "<< argv[i] << endl;
               Usage (argv[0]);
               return FALSE;
        }
    }
    if ( bServer )
        return TRUE;
    else
    {
        Usage(argv[0]);
        return FALSE;
    }
}

                

void Usage (CHAR *szName)
{
    cerr << "Usage: " << szName <<" -h host [-o object] [-p proxy] [-u] [-s] [-?] [-f file]" << endl;
    cerr << "\t-h host is a HTTP server such as www.server.com" << endl;
    cerr << "\t-p proxy is optional proxy in form: http://proxy:80" << endl;
    cerr << "\t-o object is optional document to GET in form: /foobar.htm" << endl;
    cerr << "\t-u use this flag to bring user name and password UI " << endl;
	cerr << "\t-f save remote object as local file " << endl;
	cerr << "\t-? get help " << endl;
    cerr << "\t-s use SSL " << endl;
}