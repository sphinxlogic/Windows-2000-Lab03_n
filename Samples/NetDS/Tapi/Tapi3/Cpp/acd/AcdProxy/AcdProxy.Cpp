
#include "resource.h"

#include "acdproxy.h"
#include "acdtapi.h"
//#include "tapi.h"
//#include "tapi3.h"

void print(LPCTSTR format, ... );

/////////////////////////////////////////////////////////////////////////////
// GLOBALS
/////////////////////////////////////////////////////////////////////////////
CTheApp NEAR theApp;
DWORD  dwAPIVersion;

void CALLBACK TimerProc( HWND , UINT ,UINT , DWORD);

/////////////////////////////////////////////////////////////////////////////
// CTheApp
// InitInstance:
//
BOOL CTheApp::InitInstance()
{

    // Generate our UUID
    CoCreateGuid( &AgentHandlerGUID);

    if( SUCCEEDED(InitializeTapi()) )
    {
        if(InitializeProxy())
        {
            timerID = SetTimer(NULL, 0, 5000, TimerProc);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////////
// CALLBACK procedure for timer
//

void CALLBACK TimerProc(
                        HWND hwnd,
                        UINT uMsg,
                        UINT idEvent,
                        DWORD dwTime)
{
    theApp.HandleTimerExpiry(idEvent);
}

////////////////////////////////////////////////////////////////////////////////
// CTheApp
// HandleTimerExpiry
//

void CTheApp::HandleTimerExpiry(UINT uTimerID)
{
    if( timerID != uTimerID )
        return;

    QueueListType::iterator i;
    Queue * pTempQueue;
    Agent * pAgent;
    Call * pCall;
    AgentSession * pSession;
    long lResult;

    for( i = globalQueueList.begin(); i != globalQueueList.end(); i++ )
    {
        pTempQueue = *i;

        if( pTempQueue->HasCallsToBeServiced() )
        {
            FindFreeAgent(&pAgent);
            if( pAgent == NULL )
                return;

            pAgent->FindFreeSession(&pSession);

            if( pSession == NULL )
                return;
            
            pTempQueue->getNextCall(&pCall);

            LINEADDRESSCAPS *pAddrCaps;
            pAddrCaps = (LINEADDRESSCAPS *) LocalAlloc(LPTR,3 * sizeof(LINEADDRESSCAPS));
            pAddrCaps->dwTotalSize = 3 * sizeof(LINEADDRESSCAPS);

            lResult = lineGetAddressCaps(hLineApp,
                                              0,
                                              pSession->getAddress(),
                                              dwAPIVersion,
                                              0,
                                              pAddrCaps
                                              );

            if( ( lResult ) || ( pAddrCaps->dwAddressSize == 0 ) )
            {
                LocalFree(pAddrCaps);
                return;//prnt err msg
            }
			// To build some intelligence in how to distribute calls say based on caller ID, redirect the call without answering it.

            lResult = lineAnswer(pCall->getHandle(),
                                    NULL,
                                   0);
		
			lResult = lineBlindTransfer(pCall->getHandle(),
                                    (LPCWSTR)((LPBYTE)(pAddrCaps) + pAddrCaps->dwAddressOffset),
                                   0);
		

            LocalFree(pAddrCaps);

            if( lResult )
                return;//prnt err msg and do WHAT to the poor call???
            else
            {
                pCall->setInService(true);
                pAgent->setState(AS_BUSY_INCOMING);
                pSession->setState(ASST_BUSY_ON_CALL);

                pAgent->setCallBeingServiced(pCall->getHandle());
                pTempQueue->adjustState(pCall);

                globalCallList.push_back(pCall);
            }

        }
    }
    return;
}

#define SZGROUPS        TEXT("Groups")
#define SZUSERS         TEXT("Users")
#define SZQUEUES        TEXT("Queues")
#define SZPROXIES       TEXT("Proxies")
#define SZNAME          TEXT("NAME")
#define SZADDRESSES     TEXT("Address")
#define SZGENERAL       TEXT("General")

#define SZINIFILE       TEXT("PROXY.INI")

#define SZNUMUSERS      TEXT("NumUsers")
#define SZNUMGROUPS     TEXT("NumGroups")
#define SZNUMQUEUES     TEXT("NumQueues")
#define SZNUMPROXIES    TEXT("NumProxies")
#define SZLINE          TEXT("Line")

/////////////////////////////////////////////////////////////////////////////
// CTheApp
// InitializeProxy
//
BOOL CTheApp::InitializeProxy()
{
    long lResult = 0;
	LINEEXTENSIONID            ExtID = {0,0,0,0};
    Group * newGroup;
    Queue * newQueue;
	 

    DWORD dwQueueID = 0;
    GUID ID;

    LPDWORD           pdwProxyRequests;
    DWORD             dwSize = sizeof(LINECALLPARAMS) + ( 14 * sizeof(DWORD) );
    LPLINECALLPARAMS  pLCP = (LPLINECALLPARAMS)GlobalAlloc(GPTR,dwSize);
    HLINE             hLine;

    DWORD       dwID, dwNumProxies, dwNumGroups, dwNumUsers, dwNum;
    DWORD       dwCount, dwCount2;
    LPWSTR      szLineBuffer = NULL;

        
    pdwProxyRequests = (LPDWORD)((LPBYTE)pLCP + sizeof(LINECALLPARAMS));
    // each constant is in a DWORD at the end of LINECALLPARAMS
    *pdwProxyRequests++ = LINEPROXYREQUEST_SETAGENTSTATEEX;
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETAGENTSTATUS;
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETAGENTCAPS;
    *pdwProxyRequests++ = LINEPROXYREQUEST_CREATEAGENT;
    *pdwProxyRequests++ = LINEPROXYREQUEST_SETAGENTMEASUREMENTPERIOD;
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETAGENTINFO;
    *pdwProxyRequests++ = LINEPROXYREQUEST_CREATEAGENTSESSION;
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETAGENTSESSIONLIST;
    *pdwProxyRequests++ = LINEPROXYREQUEST_SETAGENTSESSIONSTATE;
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETAGENTSESSIONINFO;       
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETQUEUELIST;              
    *pdwProxyRequests++ = LINEPROXYREQUEST_SETQUEUEMEASUREMENTPERIOD; 
    *pdwProxyRequests++ = LINEPROXYREQUEST_GETQUEUEINFO;              
    *pdwProxyRequests   = LINEPROXYREQUEST_GETGROUPLIST;
    pLCP->dwTotalSize           = sizeof(LINECALLPARAMS) + 14 * sizeof(DWORD);
    pLCP->dwDevSpecificOffset   = sizeof(LINECALLPARAMS);
    pLCP->dwDevSpecificSize     = 14 * sizeof(DWORD);   
    
    szLineBuffer = (LPTSTR)LocalAlloc(LPTR, 512 * sizeof(WCHAR));
    dwNumProxies = GetPrivateProfileInt(SZGENERAL,
                                        SZNUMPROXIES,
                                        20,
                                        SZINIFILE);

    dwNumGroups = GetPrivateProfileInt(SZGENERAL,
                                        SZNUMGROUPS,
                                        1,
                                        SZINIFILE);

    if( (dwNumGroups == 0) || (dwNumProxies == 0) )
    {
       print( L"No ACD groups and / or proxy lines defined. \r\n");
        GlobalFree(pLCP);
        return false;
    }

    for( dwCount = 0; dwCount < dwNumProxies; dwCount++ )
    {
         dwID = GetPrivateProfileInt(SZPROXIES,
                                        SZLINE,
                                        dwCount,
                                        SZINIFILE);


        if( (dwID >= 0 ) && (dwID < dwNumDevs) )
        {		lResult = lineNegotiateAPIVersion(hLineApp,
                                dwID,
                                0,
                                TAPI_CURRENT_VERSION,
                                &dwAPIVersion,
                                &ExtID);
            lResult = lineOpen(hLineApp,
                               dwID,
                               &hLine,
                               dwAPIVersion,
                               0,
                               0,
                               LINEOPENOPTION_PROXY | LINECALLPRIVILEGE_NONE,
                               LINEMEDIAMODE_INTERACTIVEVOICE,
                               pLCP);
            if (lResult == 0)
            {
                //print(L"Ok proxy line %X\r\n", hLine);
            }
            else
            {
                //print (L"Proxy line open error %X\r\n", lResult);
            }
        }
    }

    dwNumUsers = GetPrivateProfileInt(SZGENERAL,
                                        SZUSERS,
                                        1,
                                        SZINIFILE);
    for( dwCount = 0; dwCount < dwNumUsers; dwCount++ )
    {
        static PWSTR lpszName;
		 GetPrivateProfileString(SZUSERS,
                                SZNAME,
                                TEXT("anjaliv"),
                                szLineBuffer,
                                512,
                                SZINIFILE);

   
       lpszName = NULL;
        lpszName = SysAllocString((PWSTR)szLineBuffer);
        

        if(wcscmp(lpszName, (LPWSTR)"") )
            allowedUsersList.push_back(lpszName);
    }
    pLCP->dwTotalSize           = sizeof(LINECALLPARAMS);
    pLCP->dwDevSpecificOffset   = 0;
    pLCP->dwDevSpecificSize     = 0;   

    for( dwCount = 0; dwCount < dwNumGroups; dwCount++ )
    {
        static PWSTR lpszName;
        
		GetPrivateProfileString(SZGROUPS,
                                SZNAME,
                                TEXT("Group1"),
                                szLineBuffer,
                                512,
                                SZINIFILE);
		
		lpszName = NULL;
        lpszName = SysAllocString((PWSTR)szLineBuffer);
        

        if(wcscmp(lpszName, (LPWSTR)"") )
        {
            CoCreateGuid(&ID);
            newGroup = new Group((PWSTR)(lpszName), ID);
            if( newGroup != NULL )
            {
                groupList.push_back(newGroup);
                 dwNum = GetPrivateProfileInt(SZGROUPS,
                                             SZNUMQUEUES,
                                             1,
                                             SZINIFILE);
                if( dwNum > 0 )
                {
                    //getQueueName, AddressID, form queue
                    for( dwCount2 = 0; dwCount2 < dwNum; dwCount2++ )
                    {
                        static PWSTR lpszQueueName;
                        
						GetPrivateProfileString(SZQUEUES,
                                                SZNAME,
                                                TEXT("queue1"),
                                                szLineBuffer,
                                                512,
                                                SZINIFILE);
                        lpszQueueName = NULL;
                        lpszQueueName = SysAllocString((PWSTR)szLineBuffer);

                        if(wcscmp(lpszName, (LPWSTR)"") )
                        {
                            dwID = GetPrivateProfileInt(SZADDRESSES,
                                                        NULL,
                                                        2,
                                                        SZINIFILE);
                            if( (dwID >= 0) && (dwID < dwNumDevs) )
                            {
                                newQueue = new Queue((PWSTR)(lpszQueueName), dwQueueID);
                                if( newQueue != NULL )
                                {
                                    globalQueueList.push_back(newQueue);
                                    newGroup->addQueue(&newQueue);
                                    dwQueueID++;
                                    newQueue->setLineID(dwID);
                                    lResult = lineOpen(hLineApp,
                                                  dwID,
                                                  &hLine,
                                                  dwAPIVersion,
                                                  0,
                                                  0,
                                                  LINECALLPRIVILEGE_OWNER,
                                                  LINEMEDIAMODE_INTERACTIVEVOICE,
                                                  pLCP);
                                    if (lResult == 0)
                                       print(L"Ok line %X\r\n", hLine);
                                    else
                                        print (L"line open error %X\r\n", lResult);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    GlobalFree(pLCP);

    return true;
}



//////////////////////////////////////////////////////////////////////////////
// CTheApp
// FindFreeAgent
//
long CTheApp::FindFreeAgent(Agent **pAgent)
{
    AgentListType::iterator j;
    long lResult = 0;

    Agent *pTempAgent;

    for(j = globalAgentList.begin(); j != globalAgentList.end(); j++)
    {
        pTempAgent = *j;
        DWORD dw = pTempAgent->getState();
        if(pTempAgent->getState() == LINEAGENTSTATEEX_READY)
        {
            *pAgent = pTempAgent;
            return lResult;;
        }
    }
    *pAgent = NULL;
    return -1;
}



/////////////////////////////////////////////////////////////////////////////
// CTheApp
// ExitInstance:
//
BOOL CTheApp::ExitInstance()
{
    ShutdownTapi();
    CoUninitialize();


    DestroyGroups();
    DestroyAgents();

        
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTheApp
// DestroyGroups:
//
void  CTheApp::DestroyGroups()
{
    GroupListType::iterator  j;


    for (j = groupList.begin(); j != groupList.end(); j++)
    {
        delete *j;
    }
    
    groupList.clear();
    
}


/////////////////////////////////////////////////////////////////////////////
// CTheApp
// DestroyAgents:
//
void  CTheApp::DestroyAgents()
{
    AgentListType::iterator  j;


    for (j = globalAgentList.begin(); j != globalAgentList.end(); j++)
    {
        delete *j;
    }
    
    globalAgentList.clear();
    
}
