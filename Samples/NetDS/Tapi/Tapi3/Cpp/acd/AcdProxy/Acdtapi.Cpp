#include "resource.h"
#include "tapi3.h"
#include "tapi.h"

#include "acdproxy.h"
#include "acdtapi.h"


VOID CALLBACK LineCallback (DWORD ,DWORD ,DWORD , DWORD ,DWORD , DWORD );
 
void HandleLineProxyRequest(HLINE , LPLINEPROXYREQUEST );
long HandleLineGetAgentCaps( LPLINEAGENTCAPS );
long HandleLineGetGroupList( LPLINEAGENTGROUPLIST );
BOOL CALLBACK MainDialogProc(
                             HWND,
                             UINT,
                             WPARAM,
                             LPARAM
                            );

void print(LPCTSTR format, ... );

HINSTANCE               ghInst;
HWND                    ghDlg = NULL;


extern CTheApp theApp;

//////////////////////////////////////////////////////////////
// InitializeTapi
//
// Various initializations
///////////////////////////////////////////////////////////////
HRESULT  CTheApp::InitializeTapi()
{
    HRESULT                     hr = S_OK;
    DWORD                       dwAPIVersion;
    LINEINITIALIZEEXPARAMS      exparams;
    LONG                        lResult;
    

  
    // fill in lineinitex parameters
    exparams.dwTotalSize             = sizeof(LINEINITIALIZEEXPARAMS);
    exparams.dwOptions               = LINEINITIALIZEEXOPTION_USEHIDDENWINDOW;
    
    dwAPIVersion = TAPI_CURRENT_VERSION;

    // line init
    lResult = lineInitializeEx(&hLineApp,
                                    NULL,
                                    LineCallback,
                                    SZAPPNAME,
                                    &dwNumDevs,
                                    &dwAPIVersion,
                                    &exparams);


    if(lResult < 0)
    {
        print(L"lineInitializeEx failed\r\n");
        hr = S_FALSE;
    }
    else
    {
        print(L"TAPI initialize OK\r\n");
        print(L"%d devices\r\n",dwNumDevs);
        print(L"hLineApp %X\r\n", hLineApp);
        print(L"dwAPIVersion %X\r\n", dwAPIVersion);
        // if there are no tapi devices, should probably
        // not continue
        if( dwNumDevs == 0 )
        {
            print(L"No TAPI devices installed\r\n");
            lineShutdown(hLineApp);
            hr = FALSE;
        }
    }
    return hr;
}


//////////////////////////////////////////////////////////////
// CTheApp::ShutdownTapi
//
//////////////////////////////////////////////////////////////
HRESULT CTheApp::ShutdownTapi()
{
    HRESULT         hr;

    // shutdown
    hr = lineShutdown(hLineApp);
    return hr;
}



//////////////////////////////////////////////////////////////////////////////////
//
// LineCallback() - TAPI callback function
//
//////////////////////////////////////////////////////////////////////////////////
void CALLBACK LineCallback (DWORD hDevice,
                            DWORD dwMsg,
                            DWORD dwCallbackInstance,
                            DWORD dwParam1,
                            DWORD dwParam2, 
                            DWORD dwParam3)
{
    switch(dwMsg)
    {
      case LINE_PROXYREQUEST:
           HandleLineProxyRequest((HLINE) hDevice, (LPLINEPROXYREQUEST)dwParam1);
           return;
      case LINE_CALLSTATE:
           if( dwParam1 == LINECALLSTATE_OFFERING )
           {
                theApp.HandleNewIncomingCall((HCALL) hDevice);
                return;
           }
           theApp.HandleCallStateChange((HCALL) hDevice, dwParam1);
           return;
      case LINE_CALLINFO:
            return;
      default:
          return;
   }

}


//////////////////////////////////////////////////////////////
// HandleLineProxyRequest
//
//////////////////////////////////////////////////////////////
void HandleLineProxyRequest(HLINE hLine, LPLINEPROXYREQUEST pProxyRequest)
{
    long    lResult = 0;
    PWSTR   pszClientMachineName = NULL;
    PWSTR   pszClientUserName = NULL;

    if  (pProxyRequest->dwClientMachineNameSize != 0)
        pszClientMachineName = (PWSTR)( (PBYTE)pProxyRequest + pProxyRequest->dwClientMachineNameOffset );

    if  (pProxyRequest->dwClientUserNameSize != 0)
        pszClientUserName = (PWSTR)( (PBYTE)pProxyRequest + pProxyRequest->dwClientUserNameOffset );
        
    print(L"Received proxy request from machine: %s user: %s\r\n", pszClientMachineName, pszClientUserName);

    switch (pProxyRequest->dwRequestType)
    {
        case LINEPROXYREQUEST_GETAGENTCAPS:
            print(L"Proxy Request Get Agent Caps \r\n");
            lResult = theApp.HandleLineGetAgentCaps( &pProxyRequest->GetAgentCaps.AgentCaps);
            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

        case LINEPROXYREQUEST_GETGROUPLIST:
            print(L"Proxy Request Get group list \r\n");
            lResult = theApp.HandleLineGetGroupList( &pProxyRequest->GetGroupList.GroupList);
            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

        case LINEPROXYREQUEST_SETAGENTSTATEEX:
            print(L"Proxy Request set Agent State\r\n");
            lResult = theApp.HandleLineSetAgentStateEx(
                                                     pProxyRequest->SetAgentStateEx.hAgent,
                                                     pProxyRequest->SetAgentStateEx.dwAgentState,
                                                     pProxyRequest->SetAgentStateEx.dwNextAgentState
                                                     );

            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;
            
        case LINEPROXYREQUEST_GETAGENTSTATUS:
            print(L"Proxy Request Get Agent Status \r\n");
            lResult = theApp.HandleLineGetAgentStatus(
                                                     pProxyRequest->GetAgentStatus.dwAddressID,
                                                     &pProxyRequest->GetAgentStatus.AgentStatus);
            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;
            
        case LINEPROXYREQUEST_CREATEAGENT:
            {
            
                print(L"Proxy Request Create agent\r\n");
                PWSTR pszAgentID;
                PWSTR pszAgentPIN;
                PBYTE pCreateAgent = (PBYTE)&pProxyRequest->CreateAgent;
                pszAgentID = (PWSTR)( (PBYTE)pCreateAgent + pProxyRequest->CreateAgent.dwAgentIDOffset );
                pszAgentPIN = (PWSTR)( (PBYTE)pCreateAgent + pProxyRequest->CreateAgent.dwAgentPINOffset );
            
                lResult = theApp.HandleLineCreateAgent(
                                                       pszClientUserName, 
                                                       pszAgentID,
                                                       pszAgentPIN,
                                                       &pProxyRequest->CreateAgent.hAgent
                                                       );

                lineProxyResponse(hLine, pProxyRequest, lResult);
            }
            break;

        case LINEPROXYREQUEST_GETAGENTINFO:
            print(L"Proxy Request Get Agent information \r\n");
            lResult = theApp.HandleLineGetAgentInfo(
                                                    pProxyRequest->GetAgentInfo.hAgent,
                                                    &pProxyRequest->GetAgentInfo.AgentInfo
                                                    );
                                                    
            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

        case LINEPROXYREQUEST_CREATEAGENTSESSION://clashes with callcent-i.doc
            {
                print(L"Proxy Request create agent session\r\n");

                PWSTR pszAgentPIN;
                PBYTE pCreateAgentSession = (PBYTE)&pProxyRequest->CreateAgentSession;
            
                pszAgentPIN = (PWSTR)( (PBYTE)pCreateAgentSession + pProxyRequest->CreateAgentSession.dwAgentPINOffset );
            
                lResult = theApp.HandleLineCreateAgentSession(
                                                       pszClientUserName, 
                                                       pszAgentPIN,
                                                       pProxyRequest->CreateAgentSession.hAgent,
                                                       pProxyRequest->CreateAgentSession.GroupID,
                                                       pProxyRequest->CreateAgentSession.dwWorkingAddressID,
                                                       &pProxyRequest->CreateAgentSession.hAgentSession
                                                       );

                lineProxyResponse(hLine, pProxyRequest, lResult);
            }
            break;

        case LINEPROXYREQUEST_GETAGENTSESSIONLIST:
     
            print(L"Proxy Request Get agent session list \r\n");
            lResult = theApp.HandleLineGetAgentSessionList(
                                                           pProxyRequest->GetAgentSessionList.hAgent,
                                                           &pProxyRequest->GetAgentSessionList.SessionList
                                                           );
            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

        case LINEPROXYREQUEST_SETAGENTSESSIONSTATE:

            print(L"Proxy Request Get agent session state \r\n");
            lResult = theApp.HandleLineSetAgentSessionState(
                                                            pProxyRequest->SetAgentSessionState.hAgentSession,
                                                            pProxyRequest->SetAgentSessionState.dwAgentSessionState,
                                                            pProxyRequest->SetAgentSessionState.dwNextAgentSessionState
                                                            );

            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

        case LINEPROXYREQUEST_GETAGENTSESSIONINFO:
            print(L"Proxy Request Get agent session info\r\n");
            lResult = theApp.HandleLineGetAgentSessionInfo(
                                                           pProxyRequest->GetAgentSessionInfo.hAgentSession,
                                                           &pProxyRequest->GetAgentSessionInfo.SessionInfo
                                                           );
            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

        case LINEPROXYREQUEST_GETQUEUELIST:

            Group * pGroup;
            WCHAR guidName[100];

            print(L"hLine %X > LINEPROXYREQUEST_GETQUEUELIST \r\n", hLine);

            StringFromGUID2(pProxyRequest->GetQueueList.GroupID, (LPOLESTR)&guidName, 100);
            print(L"group %s\r\n", guidName);

            pGroup = theApp.FindGroup(pProxyRequest->GetQueueList.GroupID);
            if (pGroup != NULL)
            {
                lResult = pGroup->HandleLineGetQueueList(&pProxyRequest->GetQueueList.QueueList);
            }
            else
            {
                lResult = LINEERR_INVALAGENTGROUP;
            }

            lineProxyResponse(hLine, pProxyRequest, lResult);
            
            
            print(L"LINEPROXYREQUEST_GETQUEUELIST Done\r\n", hLine);

            break;

        case LINEPROXYREQUEST_GETQUEUEINFO:
 
            print(L"Proxy Request Get queue info \r\n");
            lResult = theApp.HandleLineGetQueueInfo(
                                                    pProxyRequest->GetQueueInfo.dwQueueID,
                                                    &pProxyRequest->GetQueueInfo.QueueInfo
                                                    );

            lineProxyResponse(hLine, pProxyRequest, lResult);
            break;

            default:
            break;
    }
            
}


//////////////////////////////////////////////////////////////
// CTheApp::HandleNewIncomingCall
//
//////////////////////////////////////////////////////////////
void CTheApp::HandleNewIncomingCall( HCALL hCall )
{

    Call *pNewCall;
    Queue *pQueue;

    print(L"New incoming call \r\n");
    pNewCall = new Call(hCall, LINECALLSTATE_OFFERING);

    LINECALLINFO * pCallInfo;
    pCallInfo = (LINECALLINFO *) LocalAlloc(LPTR, sizeof(LINECALLINFO));
    pCallInfo->dwTotalSize = sizeof(LINECALLINFO);
    long lResult = lineGetCallInfo(hCall, pCallInfo);
    
    if( lResult )
        return;

    FindQueue(pCallInfo->dwLineDeviceID, &pQueue);

    LocalFree(pCallInfo);
    if( pQueue == NULL )
        return;
    else
    {
        pNewCall->setQueue(pQueue);
        pQueue->IncomingCall(&pNewCall);
        globalCallList.push_back(pNewCall);
    }
}



//////////////////////////////////////////////////////////////
// CTheApp::HandleCallStateChange
//
//////////////////////////////////////////////////////////////
void CTheApp::HandleCallStateChange(HCALL hCall, DWORD dwState)
{
    Call * pCall = NULL;

    long lResult = FindCall(hCall, &pCall);
    if( lResult )
        //VERY Wierd, but just in case, prnt err msg
        return;

    Queue *pQueue = pCall->getQueue();
    if( dwState == LINECALLSTATE_CONNECTED )
    {
        if( pCall->IsInService() )
        {
            pQueue->adjustState(pCall);
            //free up agent and session
        }
    }
    if( dwState == LINECALLSTATE_DISCONNECTED )
    {
        if( !pCall->IsInService() )
        {
            pQueue->removeCall(pCall); //Just kill call on global waiting queues and call list.
            return;
        }
        else
        {
            AgentSession * pSession;

            pSession = pCall->getSession();
            pSession->setState(ASST_BUSY_WRAPUP);
        }
    }

    if( dwState == LINECALLSTATE_IDLE )
    {
        if( !pCall->IsInService() )
        {
            pQueue->removeCall(pCall); //Just kill call on global call Q and list.
            return;
        }
    }
            
    return;
}

//////////////////////////////////////////////////////////////
// CTheApp::HandleLineGetQueueInfo
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineGetQueueInfo( DWORD dwQueueID, LPLINEQUEUEINFO QueueInfo)
{
    long lResult = 0;

    Queue *pQueue = NULL;

    lResult = FindQueue( dwQueueID, &pQueue);

    if( lResult )
        return lResult;

    DWORD dwTemp = pQueue->getInfoSize();

    if( dwTemp > QueueInfo->dwTotalSize )
    {
        QueueInfo->dwNeededSize = dwTemp;
        return LINEERR_STRUCTURETOOSMALL;
    }

    CopyMemory(QueueInfo + sizeof(DWORD),
               (LPVOID)pQueue->getInfoAddress(),
               dwTemp - sizeof(DWORD));

    return lResult;
}

//////////////////////////////////////////////////////////////
// CTheApp::HandleLineGetAgentSessionInfo
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineGetAgentSessionInfo(HAGENTSESSION hAgentSession, LPLINEAGENTSESSIONINFO SessionInfo)
{
    long lResult = 0;
    AgentSession * pAgentSession = NULL;

    lResult = FindAgentSession(hAgentSession, &pAgentSession);

    if( lResult )
        return lResult;

    if( pAgentSession->getInfoSize() > SessionInfo->dwTotalSize )
    {
        SessionInfo->dwNeededSize = pAgentSession->getInfoSize();
        return LINEERR_STRUCTURETOOSMALL;
    }

    CopyMemory(SessionInfo + sizeof(DWORD),
               (LPVOID)pAgentSession->getInfoAddress(),
               pAgentSession->getInfoSize() - sizeof(DWORD));

    return lResult;
}

//////////////////////////////////////////////////////////////
// CTheApp::handleLineGetAgentInfo
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineGetAgentInfo( HAGENT hAgent, LPLINEAGENTINFO AgentInfo)
{
    long lResult = 0;
    Agent * pAgent = NULL;

    lResult = FindAgent(hAgent, &pAgent);

    if( lResult )
        return lResult;


    if( pAgent->getInfoSize() > AgentInfo->dwTotalSize )
    {
        AgentInfo->dwNeededSize = pAgent->getInfoSize();
        return LINEERR_STRUCTURETOOSMALL;
    }

    CopyMemory(AgentInfo + sizeof(DWORD),
               (LPVOID)pAgent->getInfoAddress(),
               pAgent->getInfoSize() - sizeof(DWORD));

    return lResult;
}

//////////////////////////////////////////////////////////////
// CTheApp::HandleLineSetAgentStateEx
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineSetAgentStateEx( HAGENT hAgent, DWORD dwAgentState, DWORD dwNextAgentState)
{

    long lResult = 0;

    Agent * pAgent = NULL;

    lResult = FindAgent(hAgent, &pAgent);

    if( lResult )
        return lResult;

    pAgent->setState( dwAgentState);
    pAgent->setNextState(dwNextAgentState);

    return lResult;

}

//////////////////////////////////////////////////////////////
// CTheApp::HandleLineGetAgentSessionList
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineGetAgentSessionList(HAGENT hAgent, LINEAGENTSESSIONLIST * pSessionList)
{
    long lResult = 0;

    AgentSession * pTempAgentSession = NULL;
    Agent        * pTempAgent = NULL;
    DWORD dwTemp;

    lResult = FindAgent(hAgent, &pTempAgent);

    if( lResult )
        return lResult;

    dwTemp = pTempAgent->getNumSessions();

    DWORD dwMinNeededSize = sizeof(LINEAGENTSESSIONLIST) 
                    + dwTemp * sizeof(LINEAGENTSESSIONENTRY);


    if( pSessionList->dwTotalSize < dwMinNeededSize )
    {
        pSessionList->dwNeededSize = dwMinNeededSize;
        return LINEERR_STRUCTURETOOSMALL;
    }

    pSessionList->dwUsedSize = dwMinNeededSize;
    pSessionList->dwNeededSize = dwMinNeededSize;
    pSessionList->dwNumEntries = dwTemp;
    pSessionList->dwListSize = dwMinNeededSize - sizeof(LINEAGENTSESSIONLIST);
    pSessionList->dwListOffset = sizeof(LINEAGENTSESSIONLIST);

    LINEAGENTSESSIONENTRY * pASList;

    DWORD j;

    for( j = 0; j < dwTemp; j++)
    {
        pASList = new LINEAGENTSESSIONENTRY;

        pTempAgentSession = pTempAgent->getSessionNumber(j + 1);

        pASList->hAgentSession = pTempAgentSession->getHandle();
        pASList->hAgent = hAgent;

        pASList->GroupID = pTempAgentSession->getID();
        pASList->dwWorkingAddressID = pTempAgentSession->getAddress();

        CopyMemory(pSessionList + j * sizeof(LINEAGENTSESSIONENTRY),
                   pASList,
                   sizeof(LINEAGENTSESSIONENTRY));

        delete(pASList);
    }
    return 0;
}

//////////////////////////////////////////////////////////////
// CTheApp::HandleLineSetAgentSessionState
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineSetAgentSessionState(HAGENTSESSION hState,
                                    DWORD dwAgentSessionState,
                                    DWORD dwNextAgentSessionState)
{
    AgentSession    *pTempAgentSession = NULL;

    long lResult = 0;

    lResult = FindAgentSession(hState, &pTempAgentSession);

    if( lResult )
        return lResult;

    pTempAgentSession->setState( dwAgentSessionState);
    pTempAgentSession->setNextState( dwNextAgentSessionState);

    return lResult;
}


//////////////////////////////////////////////////////////////
// CTheApp::HandleLineGetAgentCaps
//
//////////////////////////////////////////////////////////////
long CTheApp::HandleLineGetAgentCaps(LPLINEAGENTCAPS pAgentCaps)
{
    long        lResult;
    
    pAgentCaps->dwNeededSize = sizeof(LINEAGENTCAPS) + ((lstrlen(SZAPPNAME)+1)*sizeof(TCHAR));
    
    if (pAgentCaps->dwTotalSize < pAgentCaps->dwNeededSize)
    {
        pAgentCaps->dwUsedSize = sizeof(LINEAGENTCAPS);
        lResult = LINEERR_STRUCTURETOOSMALL;
    }
    else
    {
        lResult = 0;
        pAgentCaps->dwAgentHandlerInfoSize =  ((lstrlen(SZAPPNAME)+1)*sizeof(TCHAR));;
        pAgentCaps->dwAgentHandlerInfoOffset =  sizeof(LINEAGENTCAPS);
		lstrcpy((PTCHAR)(((LPBYTE)pAgentCaps)+sizeof(LINEAGENTCAPS)),
              SZAPPNAME);

    }

    pAgentCaps->dwCapsVersion = TAPI_CURRENT_VERSION;
    pAgentCaps->dwFeatures = LINEAGENTFEATURE_SETAGENTSTATE;

    pAgentCaps->ProxyGUID = theApp.AgentHandlerGUID;

    pAgentCaps->dwStates = LINEAGENTSTATE_READY |
                           LINEAGENTSTATE_BUSYACD |
                           LINEAGENTSTATE_WORKINGAFTERCALL;

    pAgentCaps->dwNextStates = LINEAGENTSTATE_READY |
                               LINEAGENTSTATE_BUSYACD |
                               LINEAGENTSTATE_WORKINGAFTERCALL;

    pAgentCaps->dwAgentStatusMessages = LINEAGENTSTATE_READY |
                                        LINEAGENTSTATE_BUSYACD |
                                        LINEAGENTSTATE_WORKINGAFTERCALL;

    pAgentCaps->dwUsedSize = pAgentCaps->dwNeededSize;

    return lResult;
}


//////////////////////////////////////////////////////////////
// CTheApp::HandleLineGetGroupList
//
//////////////////////////////////////////////////////////////
long  CTheApp::HandleLineGetGroupList(LPLINEAGENTGROUPLIST pGroupList)
{
    long                     lResult = 0;
    DWORD                    dwTotalSizeNeeded, dwNameOffset, dwNumEntries;
    LPLINEAGENTGROUPENTRY    pEntry;
    LPTSTR                   pName;
    GroupListType::iterator  j;
    Group                  * pGroup;
    GUID                   * pGroupID;

    dwTotalSizeNeeded = sizeof(LINEAGENTGROUPLIST);
    pGroupList->dwNumEntries = 0;
    dwNumEntries = 0;

    // walk list of groups
    for (j = groupList.begin(); j != groupList.end(); j++)
    {
        pGroup = *j;

        // incrememt number of entries
        dwNumEntries++;
        // add to total size needed
        dwTotalSizeNeeded += sizeof(LINEAGENTGROUPENTRY);
        dwTotalSizeNeeded += (lstrlen(pGroup->getName()) + 1) * sizeof(WCHAR);
    }

    pGroupList->dwNeededSize = dwTotalSizeNeeded;

    if (pGroupList->dwTotalSize < dwTotalSizeNeeded)
    {
        pGroupList->dwUsedSize = sizeof(LINEAGENTGROUPLIST);
        lResult = LINEERR_STRUCTURETOOSMALL;
    }
    else
    {
        pGroupList->dwNumEntries = dwNumEntries;
        pGroupList->dwListSize = sizeof(LINEAGENTGROUPENTRY) * pGroupList->dwNumEntries;
        pGroupList->dwListOffset = sizeof(LINEAGENTGROUPLIST);

        // get the first agentgroup entry struct
        pEntry = (LPLINEAGENTGROUPENTRY)(((LPBYTE)pGroupList) + pGroupList->dwListOffset);

        dwNameOffset = pGroupList->dwListOffset + pGroupList->dwListSize;
        // loop through the list of groups again, and fill in the structure
        for (j = groupList.begin(); j != groupList.end(); j++)
        {
            pGroup = *j;
            // Set Group ID GUID
            pGroupID = (GUID*) &pEntry->GroupID.dwGroupID1;
            *pGroupID = pGroup->getID();

            // set name of group
            pName = (LPTSTR)(((LPBYTE)pGroupList) + dwNameOffset);

            pEntry->dwNameSize = (lstrlen(pGroup->getName()) + 1) * sizeof(WCHAR);
            pEntry->dwNameOffset = dwNameOffset;
            lstrcpy( pName, pGroup->getName() );

            dwNameOffset += pEntry->dwNameSize;

            // get next entry
            pEntry++;
        }

        pGroupList->dwUsedSize = dwTotalSizeNeeded;
    }

    return lResult;
}



//////////////////////////////////////////////////////////////
// CTheApp::HandleLineCreateAgent
//
//////////////////////////////////////////////////////////////
long  CTheApp::HandleLineCreateAgent(
                                     PWSTR pszUserName, 
                                     PWSTR pszAgentID, 
                                     PWSTR pszAgentPIN, 
                                     LPHAGENT phAgent)
{
    long                     lResult = 0;
    HAGENT                   hNewAgent;
    Agent                  * pAgent;
    PWSTR                    pUserName;

    UserListType::iterator j;

    lResult = -1;
    for ( j = allowedUsersList.begin(); j != allowedUsersList.end(); j++ )
    {
        pUserName = NULL;
        pUserName = SysAllocString(*j);

        if( _wcsicmp(pszUserName, pUserName) == 0 )
        {
            lResult = 0;
            break;
        }
        SysFreeString(pUserName);
    }

    if( lResult )
        return lResult;

    hNewAgent = Agent:: getNextAgentHandle();

    pAgent = new Agent(pszUserName, 
                      pszAgentID,
                      pszAgentPIN,
                      hNewAgent
                      );

    if( pAgent == NULL )
        return -1;

    globalAgentList.push_back(pAgent);

    *phAgent = hNewAgent;

    return lResult;
}


//////////////////////////////////////////////////////////////
// CTheApp::HandleLineCreateAgentSession
//
//////////////////////////////////////////////////////////////
long  CTheApp::HandleLineCreateAgentSession(
                                     PWSTR           pszUserName, 
                                     PWSTR           pszAgentPIN, 
                                     HAGENT          hAgent,
                                     GUID            GroupID,
                                     DWORD           dwWorkingAddressID,
                                     LPHAGENTSESSION phAgentSession)
{
    long                     lResult = 0;

    HAGENTSESSION            hNewAgentSession;
    Agent                  * pAgent = NULL;
    AgentSession           * pAgentSession = NULL;

    print(L"Got session creation request \r\n");

    lResult = FindAgent(hAgent, &pAgent);

    if( lResult )   //lResult is not 0 so agent find unsuccessful, return error.
        return lResult;

    hNewAgentSession = pAgent->getNextAgentSession();

    pAgentSession = new AgentSession(pszUserName, 
                                    GroupID,
                                    pszAgentPIN,
                                    pAgent,
                                    hNewAgentSession,
                                    dwWorkingAddressID
                                    );

    if( pAgentSession == NULL )
        return -1;

    globalAgentSessionList.push_back(pAgentSession);

    pAgent->newSessionCreated(&pAgentSession);

    *phAgentSession = hNewAgentSession;

    print(L"Agent: %8d name:%s PIN:%s\r\n", hAgent, pszUserName, pszAgentPIN);

    return lResult;
}


//////////////////////////////////////////////////////////////
// CTheApp::FindGroup and similarly find AGENT, CALL, QUEUE and SESSIONS
//
//////////////////////////////////////////////////////////////

Group * CTheApp::FindGroup(GUID id)
{
    GroupListType::iterator  j;
    Group                  * pGroup;
    Group                  * pMatchingGroup = NULL;


    // walk list of groups
    for (j = groupList.begin(); j != groupList.end(); j++)
    {
        pGroup = *j;

        if ( IsEqualGUID(id, pGroup->getID() ) )
        {
            pMatchingGroup = pGroup;
            break;
        }
    }

    return  pMatchingGroup;   
}

//////////////////////////////////////////////////////////////
// CTheApp::FindAgent
//
//////////////////////////////////////////////////////////////
long CTheApp::FindAgent( HAGENT hAgent, Agent **pAgent)
{
    AgentListType::iterator j;
    Agent * pTempAgent;

    //go thorugh all agents
    for( j = globalAgentList.begin(); j!= globalAgentList.end(); j++)
    {
        pTempAgent = *j;
        if( hAgent == pTempAgent->getHandle() )
        {
            *pAgent = pTempAgent;
            return 0;
        }
    }

    *pAgent = NULL;
    return -1;
}


//////////////////////////////////////////////////////////////
// CTheApp::FindQueue
//
//////////////////////////////////////////////////////////////
long CTheApp::FindQueue( DWORD dwQueueID, Queue **pQueue)
{
    QueueListType::iterator j;
    Queue * pTempQueue;

    //go thorugh all agents
    for( j = globalQueueList.begin(); j!= globalQueueList.end(); j++)
    {
        pTempQueue = *j;

        // if( dwQueueID == pTempQueue->getID())
        {
            *pQueue = pTempQueue;
            return 0;
        }
    }

    *pQueue = NULL;
    return -1;
}

//////////////////////////////////////////////////////////////
// CTheApp::FindCall
//
//////////////////////////////////////////////////////////////
long CTheApp::FindCall( HCALL hCall, Call **pCall)
{
    CallListType::iterator j;
    Call * pTempCall;

    //go thorugh all agents
    for( j = globalCallList.begin(); j!= globalCallList.end(); j++)
    {
        pTempCall = *j;

        if( hCall == pTempCall->getHandle() )
        {
            *pCall = pTempCall;
            return 0;
        }
    }

    *pCall = NULL;
    return -1;
}

//////////////////////////////////////////////////////////////
// CTheApp::FindAgentSession
//
//////////////////////////////////////////////////////////////
long CTheApp::FindAgentSession( HAGENTSESSION hAgentSession, AgentSession **pAgentSession)
{
    AgentSessionListType::iterator j;
    AgentSession * pTempAgentSession;

    //go thorugh all agentSessions
    for( j = globalAgentSessionList.begin(); j!= globalAgentSessionList.end(); j++)
    {
        pTempAgentSession = *j;

        if( hAgentSession == pTempAgentSession->getHandle() )
        {
            *pAgentSession = pTempAgentSession;
            return 0;
        }
    }

    pAgentSession = NULL;
    return -1;
}

//////////////////////////////////////////////////////////////
// CTheApp::FindSessionUsingAddress
//
//////////////////////////////////////////////////////////////
long CTheApp::FindSessionUsingAddress( DWORD dwAddress, AgentSession **pAgentSession)
{
    AgentSessionListType::iterator j;
    AgentSession * pTempAgentSession;

    //go thorugh all agentSessions
    for( j = globalAgentSessionList.begin(); j!= globalAgentSessionList.end(); j++)
    {
        pTempAgentSession = *j;

        if( pTempAgentSession->getAddress() == dwAddress )
        {
            *pAgentSession = pTempAgentSession;
            return 0;
        }
    }

    *pAgentSession = NULL;
    return -1;
}


///////////////////////////////////////////////////////////////////////////
// CTheApp::HandleLineGetAgentStatus
//
long CTheApp::HandleLineGetAgentStatus( DWORD dwAddressID, LINEAGENTSTATUS * pAgentStatus)
{
    AgentSession    * pTempSession = NULL;
    long              lResult = 0;

    lResult = FindSessionUsingAddress(dwAddressID, &pTempSession);

    if( lResult )
        return lResult;

    Agent *pAgent = pTempSession->getAgent();

    pAgentStatus->dwState = pAgent->getState();
    pAgentStatus->dwNextState = pAgent->getNextState();
    return lResult;
}

//////////////////////////////////////////////////////////////
// Group::HandleLineGetQueueList
//
//////////////////////////////////////////////////////////////
long  Group::HandleLineGetQueueList(LPLINEQUEUELIST pQueueList)
{
    long                     lResult = 0;
    DWORD                    dwTotalSizeNeeded, dwNameOffset, dwNumEntries;
    LPLINEQUEUEENTRY         pEntry;
    LPTSTR                   pName;
    QueueListType::iterator  j;
    Queue                  * pQueue;
    

    dwTotalSizeNeeded = sizeof(LINEQUEUELIST);
    pQueueList->dwNumEntries = 0;
    dwNumEntries = 0;

    // walk list of queues
    for (j = queueList.begin(); j != queueList.end(); j++)
    {
        pQueue = *j;

        // incrememt number of entries
        dwNumEntries++;
        // add to total size needed
        dwTotalSizeNeeded += sizeof(LINEQUEUEENTRY);
        dwTotalSizeNeeded += (lstrlen(pQueue->getName()) + 1) * sizeof(WCHAR);
    }

    pQueueList->dwNeededSize = dwTotalSizeNeeded;
    
    if (pQueueList->dwTotalSize < dwTotalSizeNeeded)
    {
        pQueueList->dwUsedSize = sizeof(LINEQUEUELIST);
        lResult = LINEERR_STRUCTURETOOSMALL;
    }
    else
    {
        pQueueList->dwNumEntries = dwNumEntries;
        pQueueList->dwListSize = sizeof(LINEQUEUEENTRY) * pQueueList->dwNumEntries;
        pQueueList->dwListOffset = sizeof(LINEQUEUELIST);
    
        // get the first agentgroup entry struct
        pEntry = (LPLINEQUEUEENTRY)(((LPBYTE)pQueueList) + pQueueList->dwListOffset);
    
        dwNameOffset = pQueueList->dwListOffset + pQueueList->dwListSize;
    
        // loop through the list of queues again, and fill in the structure
        for (j = queueList.begin(); j != queueList.end(); j++)
        {
            pQueue = *j;
    
            // Set Queue ID
            pEntry->dwQueueID = pQueue->getID();

            // set name of queue
            pName = (LPTSTR)(((LPBYTE)pQueueList) + dwNameOffset);
                
            pEntry->dwNameSize = (lstrlen(pQueue->getName()) + 1) * sizeof(WCHAR);
            pEntry->dwNameOffset = dwNameOffset;
            lstrcpy( pName, pQueue->getName() );

            dwNameOffset += pEntry->dwNameSize;

            // get next entry
            pEntry++;
        }
    
        pQueueList->dwUsedSize = dwTotalSizeNeeded;
    }

    return lResult;
}

int
WINAPI
WinMain(
        HINSTANCE hInst,
        HINSTANCE hPrevInst,
        LPSTR lpCmdLine,
        int nCmdShow
       )
{
     ghInst = hInst;

    if( theApp.InitInstance() )
    {
        DialogBox(
              ghInst,
              MAKEINTRESOURCE(IDD_MAINDLG),
              NULL,
              MainDialogProc
             );
    }

    theApp.ShutdownTapi();

    return 1;
}

BOOL
CALLBACK
MainDialogProc(
               HWND hDlg,
               UINT uMsg,
               WPARAM wParam,
               LPARAM lParam
              )
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            // set up dialog
            ghDlg = hDlg;
            SendDlgItemMessage(
                           ghDlg,
                           IDC_EXIT,
                           BM_SETSTYLE,
                           BS_DEFPUSHBUTTON,
                           0
                          );
            EnableWindow(
                     GetDlgItem( ghDlg, IDC_EXIT ),
                     TRUE
                    );
            return 1;
        }

        case WM_COMMAND:
        {
            if ( LOWORD(wParam) == IDC_EXIT )
            {
                EndDialog(hDlg, 0);
                return 1;
            }

            default:
                return 0;
        }
    }
}

void print( LPCTSTR format, ... )
{
    WCHAR buf[256];
    WCHAR term[] = L"\r\n";
    va_list ap;

    va_start(ap, format);
    wvsprintf (buf, format, ap);

    WCHAR * editText;

    long lExistingStatsLength = SendDlgItemMessage(
                                                ghDlg,
                                                IDC_EDIT,
                                                WM_GETTEXTLENGTH,
                                                0,
                                                0);

    long lTotalStatsLength = lExistingStatsLength + wcslen(buf) + 5;

    editText = (LPWSTR)GlobalAlloc(LPTR, lTotalStatsLength * sizeof(WCHAR));

    if( editText == NULL )
        return;

    SendDlgItemMessage(
                       ghDlg,
                       IDC_EDIT,
                       WM_GETTEXT,
                       (WPARAM) lExistingStatsLength,
                       (LPARAM) (LPWSTR)(editText));

    wcscat(editText, buf);
    wcscat(editText, term);

    SendDlgItemMessage(
                     ghDlg,
                     IDC_EDIT,
                     WM_SETTEXT,
                     0,
                     (LPARAM)(LPCTSTR)editText);

    GlobalFree(editText);

    return;
}
