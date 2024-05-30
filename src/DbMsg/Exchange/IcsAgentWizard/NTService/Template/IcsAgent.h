/************************************************************************
*                                                                       *
*   $$Root$$Agent.h														*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#ifndef $$ROOT$$_AGENT_H
#define $$ROOT$$_AGENT_H

#pragma once

#include "stdafx.h"
#include "$$Root$$MAPIApp.h"
#include "$$Root$$Util.h"
#include "$$Root$$Table.h"
#include "$$Root$$ContentCollector.h"
#include "$$Root$$HierarchyCollector.h"


typedef struct {
	LPENTRYID folderEID;
	ULONG ulFolderCb;
	LPENTRYID storeEID;
	ULONG ulStoreCb;
} SSynchID, * LPSYNCHID;

typedef struct {
	LPENTRYID storeEID;
	ULONG ulStoreCb;
	LPMDB lpStore;
	LPTSTR lpszDisplayName;
} SStoreID, * LPSTOREID;


class C$$Root$$Agent
{
public:

	C$$Root$$Agent();
	~C$$Root$$Agent();

	//
	// The standard interface to the Agent.  
	// 
	DWORD Start();
	DWORD Stop();
	DWORD Synch();	

	

	DWORD GetSynchronizer(ULONG ulCb,
							LPENTRYID lpeid,
							LP$$ROOT$$SYNCHRONIZER * lppICSSynchronizer);
	DWORD GetSynchronizer(ULONG ulCb,
							LPENTRYID lpeid,
							short sCollectorType,
							LP$$ROOT$$SYNCHRONIZER * lppICSSynchronizer);
	const LP$$ROOT$$MAPIAPP MAPIApp() { return m_lpMAPIApp; }
	HRESULT OpenMsgStore(ULONG ulCb,
						 LPENTRYID lpeid,
						 LPMDB FAR * lppStore);

private:
	
	static DWORD InitMAPI(C$$Root$$MAPIApp ** lppMAPIApp);
	static DWORD InitCollectors(ULONG ulNumTables,
								LP$$ROOT$$TABLE ** lpppICSTable,
								C$$Root$$Agent * lpAgent);
	static DWORD InitSynchIDs(vector<LPSYNCHID> * lpVecSynchIDs);
	static DWORD InitSynchronizer(ULONG ulCb, 
								  LPENTRYID lpeid,
								  LPMDB lpStore,
								  ULONG ulNumTables,
								  LP$$ROOT$$TABLE * lppICSTable);
	static DWORD InitThreads(ULONG ulNumThreads,
							 HANDLE ** lpphThread,
							 HANDLE ** lpphIOCP,
							 LPTHREAD_START_ROUTINE lpThreadProc);

	static DWORD StopThreads(ULONG ulNumThreads,
							 HANDLE ** lpphThread,
							 HANDLE ** lpphIOCP);

	

	//
	// Methods to implement the persisted state of the agent
	//
	DWORD LoadFolderData();
	DWORD LoadSynchState();
	DWORD SaveSynchState();


	BOOL				m_fICSStarted;

	//
	// The list of SynchID objects contains all folders which
	// are to be monitored by the agent.  The list of StoreIDs
	// contains all open stores.  This allows for stores to be
	// cached and reused, rather than opened more than once.
	//
	vector<LPSYNCHID>	m_vecSynchIDs;
	vector<LPSTOREID>	m_vecStoreIDs;
	
	//
	// Each C$$Root$$Table maps a collector onto a 
	// collection of folderID-synchronizer pairs.
	// 
	LP$$ROOT$$TABLE *	m_lppICSTable;
	ULONG				m_ulNumTables;

	//
	// Data members to store handles to the threading constructs
	// needed to support multithreading in the agent.
	//
	HANDLE *			m_lphThread;
	HANDLE *			m_lphIOCP;
	ULONG				m_ulNumThreads;
	BOOL				m_fThreadsStarted;
	
	//
	// Files which contain the data necessary to load the agent.
	// The folderdata file contains the ENTRYIDs of the folders
	// which the agent is to monitor, and the synchstate file 
	// contains the current state of the synchronization being
	// performed on these folders.
	//
	TCHAR 				m_szFolderDataFile[MAX_PATH];
	TCHAR				m_szSynchStateFile[MAX_PATH];

	//
	// A pointer to the CMAPIApp object which contains
	// the active MAPI session
	//
	C$$Root$$MAPIApp *			m_lpMAPIApp;

};

typedef C$$Root$$Agent *	LP$$ROOT$$AGENT;

const DWORD AGENT_PAUSE = 0x00000001;
const DWORD AGENT_SYNCH = 0x00000002;
const DWORD AGENT_STOP	= 0x00000003;

$$IF(PROJTYPE_NTSERVICE)  
extern TCHAR g_szICSDataDirectory[MAX_PATH];
$$ENDIF

DWORD WINAPI SynchThreadProc(LPVOID lpParameter);

#endif // #ifndef $$ROOT$$_AGENT_H

