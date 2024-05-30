    #ifndef __ACDPROXY_H__
    #define __ACDPROXY_H__


//////////////////////////////////////////////////////////////

#include "tapi3.h"
#include <time.h>
#include <list>
#include <stdio.h>

class Queue;
class Group;
class Call;
class Agent;
class AgentSession;
#define SZAPPNAME             L"acdproxy"
/////////////////////////////////////////////////////////////////////////////
using namespace std;
typedef list<Group *>     GroupListType;
typedef list<Queue *>     QueueListType;
typedef list<Agent *>     AgentListType;
typedef list<Call *>      CallListType;
typedef list<AgentSession *> AgentSessionListType;
typedef list<PWSTR>       UserListType;

//#define SZAPPNAME             L"AcdProxy"
/////////////////////////////////////////////////////////////////////////////
// CTheApp:
//
class CTheApp
{
private:
    HLINEAPP        hLineApp;
    DWORD           dwNumDevs;
    UINT            timerID;
    GroupListType   groupList;
    QueueListType   globalQueueList;
    CallListType    globalCallList;

    AgentListType   globalAgentList;
    AgentSessionListType globalAgentSessionList;
    UserListType    allowedUsersList;
    
public:
    GUID            AgentHandlerGUID;

public:
    BOOL  InitInstance();
    int  ExitInstance();
    void HandleTimerExpiry(UINT);
    HRESULT  InitializeTapi();
    HRESULT  ShutdownTapi();

    BOOL InitializeProxy();
    void DestroyGroups();
    void DestroyAgents();
    long HandleLineGetGroupList(LPLINEAGENTGROUPLIST);
    long HandleLineCreateAgent(PWSTR , PWSTR , PWSTR , LPHAGENT );
    long HandleLineCreateAgentSession(PWSTR , PWSTR , HAGENT ,GUID ,DWORD ,LPHAGENTSESSION );

    Group * FindGroup(GUID);
    long FindAgent(HAGENT , Agent **);
    long FindFreeAgent(Agent **);
    long FindCall(HCALL, Call **);
    long FindQueue(DWORD, Queue **);
    long FindAgentSession(HAGENTSESSION , AgentSession ** );
    long FindSessionUsingAddress( DWORD , AgentSession **);
    long HandleLineGetAgentStatus( DWORD , LINEAGENTSTATUS *);



    long FindWaitingCall(HCALL , Call **);
    void HandleNewIncomingCall( HCALL );
    void HandleCallStateChange(HCALL , DWORD );
    long HandleLineGetQueueInfo( DWORD , LPLINEQUEUEINFO );
    long HandleLineGetAgentSessionInfo(HAGENTSESSION , LPLINEAGENTSESSIONINFO );
    long HandleLineGetAgentInfo( HAGENT , LPLINEAGENTINFO );
    long HandleLineSetAgentStateEx( HAGENT , DWORD , DWORD );
    long HandleLineGetAgentSessionList(HAGENT ,LINEAGENTSESSIONLIST *);
    long HandleLineSetAgentSessionState(HAGENTSESSION ,DWORD ,DWORD );
    long HandleLineGetAgentCaps(LPLINEAGENTCAPS );

};


/////////////////////////////////////////////////////////////////////////////
// Group:
//
class Group
{
private:
    PWSTR           pszGroupName;
    GUID            GroupID;

    QueueListType   queueList;

public:
    Group(PWSTR name, GUID ID );
    ~Group();

    PWSTR  getName() {return pszGroupName;}
    GUID  getID() {return GroupID;}

    void addQueue(Queue **);
    long GetQueue(DWORD , Queue *);
    long HandleLineGetQueueList(LPLINEQUEUELIST );

};



/////////////////////////////////////////////////////////////////////////////
// Call
//
class Call
{
private:
    HCALL   hCall;
    DWORD    dwCallState;
    BOOL     bInService;
    DWORD    dwTimeCallReceived;
    Queue   *pQueueCallIn;
    Agent   *pAgent;
    AgentSession *pAgentSession;

public:
    Call(HCALL hNewCall, DWORD dwState) {hCall = hNewCall; dwCallState = dwState;}
    void setTimeCallArrived(DWORD dwTime) {dwTimeCallReceived = dwTime;}
    DWORD getTimeCallArrived() {return dwTimeCallReceived;}
    DWORD getCallState() {return dwCallState;}
    void setCallState (DWORD dwState) {dwCallState = dwState; if( dwState == LINECALLSTATE_CONNECTED) bInService = true;}
    void setQueue(Queue *pQueue) {pQueueCallIn = pQueue;}
    Queue * getQueue() {return pQueueCallIn;}
    void setAgent(Agent *pAgnt) {pAgent = pAgnt;}
    Agent * getAgent() {return pAgent;}
    void setSession(AgentSession *pSession) {pAgentSession = pSession;}
    AgentSession * getSession() {return pAgentSession;}
    BOOL IsInService() {return bInService;}
    void setInService( BOOL bServ ) {bInService = bServ;}
    HCALL getHandle() {return hCall;}
};   


/////////////////////////////////////////////////////////////////////////////
// Queue:
//
class Queue
{
private:
    PWSTR           pszQueueName;
    DWORD           QueueID;
    DWORD           LineID;
    LINEQUEUEINFO * pQueueInfo;
    CallListType    callList;

public:
    Queue(PWSTR , DWORD);
    ~Queue();

    void setLineID(DWORD dwLineID) {LineID = dwLineID;}
    DWORD getLineID() {return LineID;}
    PWSTR  getName() {return pszQueueName;}
    DWORD  getID() {return QueueID;} 
    void updateQueueInfo( DWORD, DWORD);
    DWORD getQueueInfoParam(void);
    LINEQUEUEINFO * getQueueInfo(void) {return pQueueInfo;}
    DWORD getInfoSize() {return pQueueInfo->dwTotalSize;}
    DWORD getInfoAddress() {return (DWORD)(&(pQueueInfo->dwNeededSize));}

    void adjustWaitingTime (DWORD dwNewCallTime)
    {
        if( dwNewCallTime > pQueueInfo->dwLongestEverWaitTime )
            pQueueInfo->dwLongestEverWaitTime  = dwNewCallTime;

        pQueueInfo->dwAverageWaitTime = (pQueueInfo->dwAverageWaitTime * pQueueInfo->dwTotalCallsQueued)
                                                /(pQueueInfo->dwTotalCallsQueued + 1);
        pQueueInfo->dwTotalCallsQueued = pQueueInfo->dwTotalCallsQueued + 1;
    }



    void IncomingCall(Call **pCall)
    {
        DWORD dwTime;
        time_t ltime;
        time(&ltime);
        dwTime = (DWORD)ltime;

        (*pCall)->setTimeCallArrived(dwTime);

        callList.push_back((*pCall));

        pQueueInfo->dwTotalCallsQueued = pQueueInfo->dwTotalCallsQueued + 1;
        pQueueInfo->dwCurrentCallsQueued = pQueueInfo->dwCurrentCallsQueued + 1;
    }

    void getNextCall( Call ** pCall )
    {
        CallListType::iterator i;

        i = callList.begin();
        *pCall = *i;
    }

    BOOL HasCallsToBeServiced() 
    {
        if( pQueueInfo->dwCurrentCallsQueued != 0 )
            return true;
        else 
            return false;
    }

    void removeCall( Call * pCall )
    {
        callList.remove(pCall);
        pQueueInfo->dwTotalCallsAbandoned++;
        pQueueInfo->dwCurrentCallsQueued = pQueueInfo->dwCurrentCallsQueued - 1;
    }

    void adjustState(Call *pCall)
    {
        pQueueInfo->dwCurrentCallsQueued = pQueueInfo->dwCurrentCallsQueued - 1;
        time_t ltime;

        time( &ltime );

        DWORD dwTotalElapsedTime = (DWORD)ltime - pCall->getTimeCallArrived();

        if( dwTotalElapsedTime > pQueueInfo->dwLongestEverWaitTime)
            pQueueInfo->dwLongestEverWaitTime = dwTotalElapsedTime;

        pQueueInfo->dwAverageWaitTime = 
            ((pQueueInfo->dwAverageWaitTime * (pQueueInfo->dwTotalCallsQueued - 1)) + dwTotalElapsedTime)
                                                /(pQueueInfo->dwTotalCallsQueued);

        callList.remove(pCall);
        return;
    }

};


////////////////////////////////////////////////////////////////////////////
//Agent Session
//
class AgentSession
{  
private:
    Group * pGroup;
    PWSTR           pszSessionName;
    PWSTR           pszSessionPIN;
    Agent          *pAgent;
    DWORD   dwAddressID;
    GUID    SessionID;
    DWORD   dwACDGroupID;
    LINEAGENTSESSIONINFO  *pSessionInfo;
    HAGENTSESSION   hAgentSession;

public:
    AgentSession(PWSTR name, GUID ID, PWSTR PIN, Agent *pAgnt, HAGENTSESSION hSession, DWORD dwWorkingAddressID)
    {
        pszSessionName = SysAllocString(name);
        SessionID = ID;
        pAgent = pAgnt;
        pszSessionPIN = SysAllocString(PIN);
        hAgentSession = hSession;
        dwAddressID = dwWorkingAddressID;
        pSessionInfo = (LINEAGENTSESSIONINFO *) LocalAlloc (LPTR, sizeof(LINEAGENTSESSIONINFO));
        pSessionInfo->dwTotalSize = sizeof(LINEAGENTSESSIONINFO);
        pSessionInfo->dwNeededSize = pSessionInfo->dwTotalSize;
        pSessionInfo->dwUsedSize = pSessionInfo->dwTotalSize;

        setState(ASST_READY);
    }

    ~AgentSession()
    {
        if( pszSessionName != NULL )
            SysFreeString(pszSessionName);
        if( pszSessionPIN != NULL )
            SysFreeString(pszSessionPIN);
        if(pSessionInfo != NULL)
            LocalFree(pSessionInfo);
    }

    Group * getSessionGroup() {return pGroup;}

    DWORD getInfoSize() {return pSessionInfo->dwTotalSize;}
    DWORD getInfoAddress() {return (DWORD)(&(pSessionInfo->dwNeededSize));}
    
    HAGENTSESSION getHandle() {return hAgentSession;}

    GUID getID() {return SessionID;}
    DWORD getGroupID() {return dwACDGroupID;}
    DWORD getAddress() {return dwAddressID;}
    Agent * getAgent() {return pAgent;}
    
    void setState ( DWORD dwState ) 
            { pSessionInfo->dwAgentSessionState =  dwState;}
    DWORD getState() {return pSessionInfo->dwAgentSessionState;}

    void setNextState ( DWORD dwNextState ) 
            { pSessionInfo->dwNextAgentSessionState =  dwNextState;}
};
    


/////////////////////////////////////////////////////////////////////////////
// Agent:
//
class Agent
{
private:
    PWSTR           pszAgentName;
    PWSTR           pszAgentID;
    PWSTR           pszAgentPIN;
    HAGENT          hAgent;
    DWORD           dwNumSessions;
    HCALL           hCallBeingServiced;

    LINEAGENTINFO * pAgentInfo;

    AgentSessionListType agentSessionList;
    HAGENTSESSION     hNextSession;

public:
    static HAGENT   hNextAgentHandle;

public:
    Agent(PWSTR ,PWSTR ,PWSTR , HAGENT );
    ~Agent();

    PWSTR  getName() {return pszAgentName;}
    PWSTR  getID() {return pszAgentID;}
    PWSTR  getPIN() {return pszAgentPIN;}
    HAGENT  getHandle() {return hAgent;}
    LINEAGENTINFO * getAgentInfo() {return pAgentInfo;}
    DWORD getInfoSize() {return pAgentInfo->dwTotalSize;}
    DWORD getInfoAddress() {return (DWORD)(&(pAgentInfo->dwNeededSize));}

    BOOL FindFreeSession (AgentSession  **pSession)
    {
        AgentSession *pTempSession;

        AgentSessionListType::iterator j;

        for (j = agentSessionList.begin(); j != agentSessionList.end(); j++)
        {
            pTempSession = *j;
            if( pTempSession->getState() == LINEAGENTSESSIONSTATE_READY )
            {
                *pSession = pTempSession;
                return true;
            }
        }
        pSession = NULL;
        return false;
    }

    DWORD getNumSessions() {return dwNumSessions;}

    AgentSession * getSessionNumber(DWORD dwNum)
    {
        AgentSessionListType::iterator j;

        j = agentSessionList.begin();
        DWORD dwTemp;
        for(dwTemp = 1; (dwTemp <= dwNum) && (j != agentSessionList.end()); dwTemp++, j++);
        if(dwTemp != dwNum)
            return NULL;
        else
            return *j;
    }

    void newSessionCreated( AgentSession ** pSession)
    {
        dwNumSessions++;
        agentSessionList.push_back(*pSession);
        return;
    }

    HAGENT getAgentHandle() {return hAgent;}

    static HAGENT getNextAgentHandle() {return ++hNextAgentHandle;}
    HAGENTSESSION getNextAgentSession() {return ++hNextSession;}

    void setState (DWORD dwState ) { pAgentInfo->dwAgentState =  dwState;}
    DWORD getState() {return pAgentInfo->dwAgentState;}

    void setNextState (DWORD dwNextState ) { pAgentInfo->dwNextAgentState =  dwNextState;}
    DWORD getNextState () {return pAgentInfo->dwNextAgentState;}

    void setCallBeingServiced(HCALL hCall) {hCallBeingServiced = hCall;}
    HCALL getCallBeingServiced() {return hCallBeingServiced;}
};



#endif // __ACDPROXY_H__


