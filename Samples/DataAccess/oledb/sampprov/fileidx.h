//--------------------------------------------------------------------
// Microsoft OLE DB Sample Provider
// (C) Copyright 1995 - 1998 Microsoft Corporation. All Rights Reserved.
//
// @doc
//
// @module FILEIDX.H | Class Definitions for CFileIdx Class
//
//
#ifndef _FILEIDX_H_
#define _FILEIDX_H_
#include <windows.h>

//--------------------------------------------------------------------
// @struct FILEDEX | Simple structure used to maintain file offset and
// deletion status for the rows.
//
typedef struct {
	ULONG	ulOffset;			//@field Offset into file
	BYTE	bStatus;			//@field Deletion Status
	} FILEDEX, FAR * LPFILEDEX;


//--------------------------------------------------------------------
// @class CFileIdx | Manages the array of offsets into a file.  This 
// maintains whether the row has been deleted and where the row begins.
// 
// @hungarian 
//
class CFileIdx
{
private: //@access private
	//@cmember Array of Offset and Status flags
	LPFILEDEX	m_rgDex;
	//@cmember Current number of rows allocated 
	DBCOUNTITEM	m_ulDexCnt;
	//@cmember Reallocation Routine
	BOOL ReAlloc(DBCOUNTITEM ulRows);

public: //@access public
	//@cmember Class Constructor
	CFileIdx(void);	 
	//@cmember Class Destructor
	~CFileIdx(void);
	//@cmember Initialization Routine
	BOOL fInit(void);
	//@cmember Sets file offset of a particular index
	BOOL SetIndex(DBCOUNTITEM ulDex, DBCOUNTITEM ulOffset);
	//@cmember Sets the delete flag for a particular row
	BOOL DeleteRow(DBCOUNTITEM ulDex);
	//@cmember Has the Row been deleted
	BOOL IsDeleted(DBCOUNTITEM ulDex);
	//@cmember Returns the offset in the file for a particular row
	ULONG GetRowOffset(DBCOUNTITEM ulDex);
};


#endif

