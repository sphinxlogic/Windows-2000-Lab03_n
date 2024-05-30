/************************************************************************
*                                                                       *
*   $$Root$$Synchronizer.h											*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#ifndef $$ROOT$$_SYNCHRONIZER_H
#define $$ROOT$$_SYNCHRONIZER_H

#include "stdafx.h"
#include "$$Root$$Util.h"

class C$$Root$$Table;
typedef C$$Root$$Table * LP$$ROOT$$TABLE;

class C$$Root$$Synchronizer {

public:
	C$$Root$$Synchronizer(LPMDB lpStore,
					 ULONG ulCb,
					 LPENTRYID lpEntryID,
					 LP$$ROOT$$TABLE lpICSTable);
		
	~C$$Root$$Synchronizer();

	HRESULT Initialize();
	HRESULT RefreshState();
	HRESULT Synchronize();

	//
	// Data-member access methods
	//
	LPENTRYID EntryID()							{ return m_lpEntryID; }
	ULONG EntryIDCb()							{ return m_ulCb; }
	LPMAPIFOLDER Folder()						{ return m_lpFolder; }
	LPTSTR FolderName()							{ return m_lpszFolderName; }
	LPEXCHANGEEXPORTCHANGES Synchronizer()		{ return m_lpSynchronizer; }
	HGLOBAL	MemBlock()							{ return m_hMemBlock; }
	LPSTREAM SynchState()						{ return m_lpSynchState; }
	LP$$ROOT$$TABLE $$Root$$Table()				{ return m_lpICSTable; }

	//
	// Utility methods
	//
	HRESULT equals(ULONG ulCb, LPENTRYID lpEntryID, ULONG * lpulResult);
	HRESULT equals(C$$Root$$Synchronizer * icsSynchronizer, ULONG FAR * lpulResult);
	operator string();

private:

	BOOL					m_fIsInitialized;

	//
	// Data members representing the folder on which 
	// incremental synchronization will be performed
	//
	LPENTRYID				m_lpEntryID;
	LPMAPIFOLDER			m_lpFolder;
	LPTSTR					m_lpszFolderName;	// The name of the folder monitored by this class
	ULONG					m_ulCb; 

	//
	// Data members representing the synchronizer 
	//
	HGLOBAL					m_hMemBlock;
	LPEXCHANGEEXPORTCHANGES m_lpSynchronizer;
	LPSTREAM				m_lpSynchState;
	
	//
	// Back pointers to various useful structures.  
	// These have been allocated elsewhere, and
	// should not be modified or deleted from within this class
	//
	LP$$ROOT$$TABLE			m_lpICSTable;		// Back pointer to the ICS table containing this ICSPair
	LPMDB					m_lpStore;			// The information store containing the folder monitored by this class
	
};

typedef C$$Root$$Synchronizer * LP$$ROOT$$SYNCHRONIZER;

#endif  // #ifndef $$ROOT$$_SYNCHRONIZER_H

