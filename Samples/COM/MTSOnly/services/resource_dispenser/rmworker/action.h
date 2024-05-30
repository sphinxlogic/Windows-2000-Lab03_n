/******************************************************************************\
********************************************************************************
* Filename: action.h
*
* Description:  abstracts a RM "Action"
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

#ifndef _ACTIONLIST_H_
#define _ACTIONLIST_H_

#include "..\..\..\common\inc\rmworker.h"
#include <list>

using namespace std;
//---------------------------------------------------------------------
// This file contains all type and class definitions used by the file
// resource manager to manage an in-memory list of all its actions.
//---------------------------------------------------------------------

class CAction
{
public:
// non-logged info...this isn't logged because the lock on the file
// is released when the process crashes (in this case the rm)

	HANDLE m_hLock;			// the handle to the file that acts as a lock
	WIN32_FILE_ATTRIBUTE_DATA m_attrFile;
	TCHAR m_pszLockedFile[ MAX_PATH ];



public:

// permanent information -- logged
	FILE_OPERATION m_eFileOp;
	LOG_RM_COMMAND m_eRmCommand;
    LPTSTR m_sPath1;
	LPTSTR m_sPath2;
	
	CAction();	
	~CAction();
	CAction (CAction * pAction);
	CAction(LOG_RM_COMMAND rmCommand, FILE_OPERATION eOpIn,  LPTSTR pszInParm1, LPTSTR pszInParm2);
	BOOL LockFile(TCHAR * pFile);	
	void ReleaseLock();

	HRESULT Save(BYTE **ppByte, ULONG * cbByte);
	HRESULT Load(BYTE * pByte, long cbByte);
	
};

//---------------------------------------------------------------------
// CActionList:
// Class definition for the action list manager.
//---------------------------------------------------------------------
typedef list <CAction *> ACTIONLIST;

class CActionList : public ACTIONLIST
{
public:

	// Consructor interface:
	// Defines the constructor and destructor for a CActionList
	// class.
	//		CActionList		-- instantiates a Action list object
	//		~CActionList	-- deletes a Action list object
	
    CActionList (void);	
											// Action list constructor
	~CActionList (void);					// Action list destructor

	// Action List Interface
	// Defines group of interfaces that manage the in-memory action list for 
	// a recovery manager.
	//		AddAction		-- logs and executes an action.
	//      GetAction		-- get action item from action list.
	//		RemoveAction	-- undoes an action and logs an undo record.
	//		RecoverActions	-- recovers a list of actions from the log.
	//		UndoActions		-- undoes all actions on the action list.
	//

	void CleanupAction (BOOL bCommit = FALSE);					// Delete all items from action list.
	BOOL PushAction (LOG_RM_COMMAND rmCommand, FILE_OPERATION eFileOp, TCHAR *pszParm1, TCHAR *pszParm2);					
	BOOL PushAction(CAction * pAction);	// Add an action to the action list.												
	BOOL PeekAction (CAction ** pprmAction);	// Get action at top of action list.
	BOOL RemoveAction (BOOL bCommit = FALSE);	// Removes and action from top of list.
	BOOL PopAction (CAction& prmAction);		// Pops action at top of list combines				
												// Peek action and remove action.
											
	void ResetActions (CActionList *actionList); // Resets the action list to actionList
	void  Clone(CActionList * pList);			// copies the
	

	//ACTIONLIST	*m_plistAction;	
												// In-memory list of all actions.
												// performed for transaction manager.



}; // CActionList




#endif _ACTIONLIST_H_
