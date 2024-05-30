#include "resource.h"

#include "acdproxy.h"
#include "acdtapi.h"

extern CTheApp theApp;
DWORD nextQueueID = 1;
HAGENT Agent::hNextAgentHandle = 0;
void print(LPCTSTR format, ... );


/////////////////////////////////////////////////////////////////////////////
// Group
// Constructor
//
Group::Group(PWSTR name, GUID ID)
{
    WCHAR guidName[100];

    pszGroupName = NULL;
    pszGroupName = SysAllocString(name);
    GroupID = ID; 


    StringFromGUID2(ID, (LPOLESTR)&guidName, 100);
    //print(L"Created group %s %s\r\n", guidName, name);
}

/////////////////////////////////////////////////////////////////////////////
// Group
// addQueue
//
void Group::addQueue(Queue ** pQueue)
{
    queueList.push_back(*pQueue);
}

/////////////////////////////////////////////////////////////////////////////
// Group
// Destructor
//
Group::~Group()
{
    QueueListType::iterator  j;


    if (pszGroupName != NULL)
        SysFreeString(pszGroupName);



    for (j = queueList.begin(); j != queueList.end(); j++)
    {
        delete *j;
    }
    queueList.clear();
    

}



/////////////////////////////////////////////////////////////////////////////
// Queue
// Constructor
//
Queue::Queue(PWSTR name, DWORD ID)
{
    pszQueueName = NULL;
    pszQueueName = SysAllocString(name);
    QueueID = ID; 

    pQueueInfo = (LINEQUEUEINFO *) LocalAlloc(LPTR, sizeof(LINEQUEUEINFO));
    pQueueInfo->dwTotalSize = sizeof(LINEQUEUEINFO);
    pQueueInfo->dwNeededSize = pQueueInfo->dwTotalSize;
    pQueueInfo->dwUsedSize = pQueueInfo->dwTotalSize;

    //print(L"\tCreated queue [%8d] %s\r\n", ID, name);

}



/////////////////////////////////////////////////////////////////////////////
// Queue
// Destructor
//
Queue::~Queue()
{
    if (pszQueueName != NULL)
        SysFreeString(pszQueueName);
    if( pQueueInfo != NULL )
        LocalFree(pQueueInfo);
}


    

/////////////////////////////////////////////////////////////////////////////
// Agent
// Constructor
//
Agent::Agent(PWSTR name,PWSTR id,PWSTR pin, HAGENT agent)
{
    pszAgentName = NULL;
    pszAgentID   = NULL;
    pszAgentPIN  = NULL;

    pszAgentName = SysAllocString(name);
    pszAgentID   = SysAllocString(id);
    pszAgentPIN  = SysAllocString(pin);
    hCallBeingServiced = NULL;

    hAgent = agent; 

    pAgentInfo = (LINEAGENTINFO *) LocalAlloc(LPTR, sizeof(LINEAGENTINFO));
    pAgentInfo->dwTotalSize = sizeof(LINEAGENTINFO);
    pAgentInfo->dwNeededSize = pAgentInfo->dwTotalSize;
    pAgentInfo->dwUsedSize = pAgentInfo->dwTotalSize;

 //   pAgentInfo->dwAgentState = AS_READY;
    setState(AS_READY);

    //print(L"Created agent %s %s %s %d\r\n", name, id, pin, hAgent);

}



/////////////////////////////////////////////////////////////////////////////
// Agent
// Destructor
//
Agent::~Agent()
{
    if (pszAgentName != NULL)
        SysFreeString(pszAgentName);

    if (pszAgentID != NULL)
        SysFreeString(pszAgentID);

    if (pszAgentPIN != NULL)
        SysFreeString(pszAgentPIN);

    if( pAgentInfo != NULL )
        LocalFree(pAgentInfo);
}