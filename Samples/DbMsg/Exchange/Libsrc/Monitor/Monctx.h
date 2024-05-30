// --monctx.h-------------------------------------------------------------------
//
//  File containing definitions for monitor context and related structures.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#if !defined(_MONCTX_H)
#define _MONCTX_H

#include <winperf.h>

//
// Macro definitions
//

// This checks to see that the value is a valid detail level as defined in 
// WINPERF.H.  Detail level describes the level of knowledge needed to 
// understand a given counter or object.
#define TEST_DETAIL_LEVEL(x) ( \
	(x) == PERF_DETAIL_NOVICE || \
	(x) == PERF_DETAIL_ADVANCED || \
	(x) == PERF_DETAIL_EXPERT || \
	(x) == PERF_DETAIL_WIZARD)

#define ASSERT_DETAIL_LEVEL(x, y) ASSERTERROR(TEST_DETAIL_LEVEL(x), y)

#define TEST_COUNTERDEF_ARRAY(_ccd, _lpcd) fIsValidCounterDefArray(_ccd, _lpcd)



// Casts a FILETIME or LARGE_INTEGER to an __int64
#define INT64(li) (*( \
	(__int64 *) \
	(ASSERTERROR(sizeof(li) == sizeof(__int64), "wrong size"), &(li)) \
	))

// Casts an __int64 to a FILETIME
#define TO_FILETIME(i64) (*((FILETIME *)&(i64)))

// Constant value for one minute in system 8-byte time format.
#define ONE_MINUTE	((__int64)60*10000000)



//
// Internal Structure Definitions
//

//$--MONCOUNTER-----------------------------------------------------------------
//  Internal structure representing a counter to be updated.
// -----------------------------------------------------------------------------
typedef struct _MonCounter				// (hungarian notation = mc)
{										
	struct _MonCounter *lpmcNext;		// ptr to next in current counter list
	struct _MonCounter *lpmcNextJSW;	// ptr to next in master JSW list
	HJSWINDOW hjswJumpWindow;			// handle of JSW for counter (or NULL)
	LPCOUNTER lpcntCounter;				// ptr to actual counter to update
    BOOL fZeroOnFree;                   // TRUE=zero this counter on gw shutdown
} MONCOUNTER, *LPMONCOUNTER;



//$--MONFOLDER------------------------------------------------------------------
//  Internal structure representing a folder to be monitored.
// -----------------------------------------------------------------------------
typedef struct _MonFolder				// (hungarian notation = mf)
{
	struct _MonFolder *lpmfNext;		// pointer to next folder in chain
	struct _MonContext *lpmcx;			// pointer back to main context
	LPMAPIFOLDER lpFolder;				// folder this structure is linked to
	LPMAPITABLE lpTable;				// table of messages in folder
	LPMAPIADVISESINK lpAdvise;			// advise structure attached to table
	ULONG ulConnection;					// connection returned from Advise()

	LPMONCOUNTER lpmcMessagesInFolder;	// (lists of counters for this folder)
	LPMONCOUNTER lpmcBytesInFolder;
	LPMONCOUNTER lpmcMessagesEnteringFolder;
	LPMONCOUNTER lpmcBytesEnteringFolder;
	LPMONCOUNTER lpmcMessagesLeavingFolder;
	LPMONCOUNTER lpmcBytesLeavingFolder;

	CRITICAL_SECTION csCriticalSection;	// critical section to synchronize 
										// access to the "update request" 
										// variables
	BOOL fCriticalSectionInitialized;	// flag that this critical section 
										// was initialized
	
	// "Update request" variables.  The following four variables are set by 
	// the folder notification routine and are used by the folder update 
	// thread to update the folder counters.  This lets the folder notification 
	// routine do less work.

	DWORD cMessagesEnteringFolder;		// messages entering folder to process
	DWORD cBytesEnteringFolder;			// bytes entering folder to process
	DWORD cMessagesLeavingFolder;		// messages leaving folder to process
	DWORD cBytesLeavingFolder;			// bytes leaving folder to process

	// The following two variables are kept track of by the folder update 
	// thread.  They keep a running total of the total number of bytes that 
	// have entered and left the folder AS REPORTED TO THE WINDOWS NT 
	// PERFORMANCE MONITOR SO FAR.  Together with the total bytes in the folder,
	// they are used to determine when bytes are leaving the folder.  This 
	// is nescessary because the notification engine tells us that a message 
	// has left the folder, but not how many bytes it contained.

	ULONG cTotalBytesEnteringFolder;	// total bytes we said entered folder
	ULONG cTotalBytesLeavingFolder;		// total bytes we said left folder

	BOOL fUpdateFolderSize;				// "update request" to get new count 
										// of messages and bytes in folder
} MONFOLDER, *LPMONFOLDER;



//$--MONCONTEXT-----------------------------------------------------------------
//  Internal structure that holds all the variables needed for a performance 
//  monitoring session.  Right now the performance monitoring API is written 
//  to only allow one session, but it could easily be changed to allow multiple 
//  sessions.
// -----------------------------------------------------------------------------
typedef struct _MonContext {			// (hungarian notation = mcx)

	// name of gateway type and gateway instance

	LPSTR lpszObjectClass;				// object class
	LPSTR lpszObjectName;				// object instance name

	// shared memory to communicate with the DLL

	DWORD cbSharedMemorySize;			// size of shared memory block
	HANDLE hSharedMemoryMapping;		// handle of file mapping object
	LPMONSHAREDMEMORY lpmsmSharedMemory; // pointer to shared memory block
	LPCOUNTER lpcntCounter;				// ptr to actual counters in shared mem
	HANDLE hSharedMemoryMutex;			// mutex to share memory

	// lists of non-folder INCREMENTING counters being monitored

	LPMONCOUNTER lpmcMessagesTransferredIn; // messages into Exchange
	LPMONCOUNTER lpmcMessagesTransferredOut; // messages out of Exchange
	LPMONCOUNTER lpmcBytesTransferredIn; // bytes into Exchange
	LPMONCOUNTER lpmcBytesTransferredOut; // bytes out of Exchange
	LPMONCOUNTER lpmcNDRsIn;			// non-deliverables into Exchange
	LPMONCOUNTER lpmcNDRsOut;			// non-deliverables out of Exchange

	// lists of non-folder ABSOLUTE counters being monitored

	LPMONCOUNTER lpmcAssociations;		// current number of associations

	// list of counters allocated but not put onto another list yet
	// (this is to avoid memory leaks in case of aborting startup)

	LPMONCOUNTER lpmcFreeList;			// list of counters not being used

	// information about folders being monitored

	LPMONFOLDER lpmfFolderList;			// list of folders to monitor

	// information needed by jumping sliding windows

	LPMONCOUNTER lpmcJSWCounterList;	// list of counters with JSW's
	__int64 dwlCurrentTime;				// 64 bit current system time

	// information about the thread that updates the jumping sliding 
	// windows and folders

	BOOL fUpdateThreadRunning;			// set if the thread is running
	HANDLE hUpdateThread;				// handle to the thread process
	DWORD dwUpdateThreadID;				// thread ID
	HANDLE hUpdateThreadWakeEvent;		// handle to event to wake the thread
	BOOL fUpdateThreadTerminate;		// flag set to terminate thread

	// First Counter and First Help values for this gateway.  These are taken 
	// from the SYSTEM\CurrentControlSet\Services\<lpszObjectClass>\Performance
	// key in the registry.

	DWORD dwFirstCounter;				// "First Counter" from registry
	DWORD dwFirstHelp;					// "First Help" from registry
	DWORD dwLastCounter;				// "Last Counter" from registry
	DWORD dwLastHelp;					// "Last Help" from registry
	DWORD iObjectTitleOffset;			// offset of object name from
										// First Counter

	// Other things that need to be kept track of

	DWORD dwObjectDetailLevel;			// complexity of object (winperf.h)
	DWORD dwDefaultCounter;				// default counter on lists

} MONCONTEXT, *LPMONCONTEXT;

#endif
