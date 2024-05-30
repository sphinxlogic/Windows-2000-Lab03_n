/******************************************************************************\
********************************************************************************
* Filename: action.cpp
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
#include "stdafx.h"
#include "..\..\..\common\inc\SimpleLog.h"
#include "action.h"




CAction::CAction()
{
	m_sPath1 = NULL;
	m_sPath2 = NULL;
	m_hLock=NULL;
	*m_pszLockedFile = NULL;
}	
CAction::~CAction()
{
	ReleaseLock();
	if (m_sPath1)
		delete [] m_sPath1;
	if (m_sPath2)
		delete [] m_sPath2;
}

CAction::CAction (CAction * pAction)
{
	m_sPath1 = NULL;
	m_sPath2 = NULL;
	m_hLock=NULL;
	m_eFileOp = pAction -> m_eFileOp;
	m_eRmCommand = pAction -> m_eRmCommand;	
	*m_pszLockedFile = NULL;
	if (pAction -> m_sPath1)
	{
		m_sPath1 = new TCHAR[lstrlen(pAction -> m_sPath1)+1];
		lstrcpy(m_sPath1, pAction -> m_sPath1);
	}

	if (pAction -> m_sPath2)
	{
		m_sPath2 = new TCHAR[lstrlen(pAction -> m_sPath2)+1];
		lstrcpy(m_sPath1, pAction -> m_sPath2);
	}
}

CAction::CAction(LOG_RM_COMMAND rmCommand, FILE_OPERATION eOpIn,  LPTSTR pszInParm1, LPTSTR pszInParm2)
{
	m_sPath1 = NULL;
	m_sPath2 = NULL;
	m_hLock=NULL;
	m_eFileOp = eOpIn;
	m_eRmCommand = rmCommand;
	*m_pszLockedFile = NULL;
	if (pszInParm1)
	{
		m_sPath1 = new TCHAR[lstrlen(pszInParm1) + 1];
		*m_sPath1 = NULL;
		lstrcpy(m_sPath1, pszInParm1);
	}

	if (pszInParm2)
	{
		m_sPath2 = new TCHAR[lstrlen(pszInParm2)+1];
		*m_sPath2 = NULL;
		lstrcpy(m_sPath2, pszInParm2);
	}		
}

BOOL CAction::LockFile(TCHAR * pFile)
{

	lstrcpy(m_pszLockedFile, pFile);
	m_hLock = CreateFile(   pFile,	// pointer to name of the file 
							GENERIC_WRITE|GENERIC_READ,	// access (read-write) mode 
							0L,	// share mode 
							NULL,	// pointer to security descriptor 
							OPEN_EXISTING,	// how to create 
							FILE_ATTRIBUTE_NORMAL,	// file attributes 
							NULL); 	// handle to file with attributes to copy  

	_ASSERTE(m_hLock);
	BOOL bRet;
	memset(&m_attrFile, NULL, sizeof(m_attrFile));

	// store the file attributes for later user
	bRet = GetFileAttributesEx(pFile, GetFileExInfoStandard, &m_attrFile);
	_ASSERTE(bRet);

	// set the file to Hidden (the file is Read only because it is open)
	bRet = SetFileAttributes(pFile, FILE_ATTRIBUTE_HIDDEN);
	_ASSERTE(bRet);
	return m_hLock ? TRUE : FALSE;


}

void CAction::ReleaseLock()
{
	if (m_hLock)
	{

		if (!CloseHandle(m_hLock))
			_ASSERTE(0);

		m_hLock = NULL;
		BOOL bRet = SetFileAttributes(m_pszLockedFile, m_attrFile.dwFileAttributes);
		_ASSERTE(bRet);			
	}
}
//
//	save the data into a byte stream
//

HRESULT CAction::Save(BYTE **ppByte, ULONG * cbByte)
{
	LPSTR sPath1, sPath2;
#ifdef _UNICODE // convert to ANSI
	USES_CONVERSION;
	sPath1  = W2A(m_sPath1);
	sPath2 = W2A(m_sPath2);
#else
	sPath1 = m_sPath1;
	sPath2 = m_sPath2;
#endif

	int lPath1Size = 1; 
	if (sPath1)
		lPath1Size += lstrlenA(sPath1);

	int lPath2Size = 1;
	if (sPath2)
		lPath2Size += lstrlenA(sPath2)+1;

	*cbByte =		sizeof(m_eFileOp)+
					lPath1Size + 
					sizeof(DWORD) + // string len
					lPath2Size + 
					sizeof(DWORD) + // string len
					sizeof(m_eRmCommand);
					

	
	*ppByte = new BYTE[*cbByte];
	_ASSERTE(*ppByte);
	if (!*ppByte)
		return E_OUTOFMEMORY;
	ULONG lOffset = 0;
	memset(*ppByte, NULL, (int)*cbByte);

	*(FILE_OPERATION *)(*ppByte + lOffset) =  m_eFileOp;	
	lOffset += sizeof(m_eFileOp);

	*(LOG_RM_COMMAND *)(*ppByte + lOffset) =  m_eRmCommand;
	lOffset += sizeof(m_eRmCommand);

	*(ULONG *)(*ppByte + lOffset) = lPath1Size;
	lOffset +=sizeof(ULONG);

	if (m_sPath1)
		lstrcatA((LPSTR)(*ppByte + lOffset), sPath1);

	lOffset += lPath1Size;

	*(ULONG *)(*ppByte + lOffset) = lPath2Size;
	lOffset +=sizeof(ULONG);

	if (m_sPath2)
		lstrcatA((LPSTR)(*ppByte + lOffset), sPath2);

	lOffset += lPath2Size;
	_ASSERTE(lOffset == *cbByte);

	return S_OK;

}
HRESULT CAction::Load(BYTE * pByte, long cbByte)
{

	LPSTR p1, p2;
	p1 = p2 = NULL;
	ULONG lOffset = 0;
	m_eFileOp	=  *(FILE_OPERATION *)(pByte) ;
	lOffset += sizeof(m_eFileOp);
	m_eRmCommand	=	*(LOG_RM_COMMAND *)(pByte + lOffset);
	lOffset += sizeof(m_eRmCommand);

	ULONG cbStringLen;
	cbStringLen = *(ULONG *)(pByte + lOffset);
	lOffset +=sizeof(ULONG);
	m_sPath1 = NULL;
	if (cbStringLen)
	{
		p1  = new CHAR[cbStringLen];
		memset(p1, NULL, cbStringLen);
		memcpy(p1, (LPCSTR)(pByte + lOffset), cbStringLen);
	}		
	lOffset += cbStringLen;

	cbStringLen = *(ULONG *)(pByte + lOffset);
	lOffset +=sizeof(ULONG);
	m_sPath2 = NULL;
	if (cbStringLen)
	{
		p2  = new CHAR[cbStringLen];
		memset(p2, NULL, cbStringLen);
		memcpy(p2, (LPCSTR)(pByte + lOffset), cbStringLen);
	}		
	lOffset += cbStringLen;
	_ASSERTE(lOffset == cbByte);

#ifdef _UNICODE
	USES_CONVERSION;
	m_sPath1 = new WCHAR[lstrlenA(p1)+1];
	*m_sPath1 = NULL;
	lstrcpy(m_sPath1, A2W(p1));	
	delete [] p1;

	m_sPath2 = new WCHAR[lstrlenA(p2)+1];
	*m_sPath2 = NULL;
	lstrcpy(m_sPath2, A2W(p2));	
	delete [] p2;
#else
	m_sPath1 = p1;
	m_sPath2 = p2;
#endif
	return S_OK;

}
//-----------------------------------------------------------------------------
// CActionList Implementation:
// Method implementations for the CActionList class.
//-----------------------------------------------------------------------------

	
CActionList::CActionList (void)
{
	
} // CActionList::CActionList


CActionList::~CActionList (void)
{
	CleanupAction ();
	
} // CActionList::~CActionList

//
//	if bCommit == TRUE then we check to see if we have 
//	a temp file in the recovery directory, and if we do
//	we delete it
//
void CActionList::CleanupAction (BOOL bCommit /* = FALSE */)
{
	// Iterate through the list and recover storage for list items.
	while (!empty())
	{
		// Remove the first item and reclaim storage for action.
		RemoveAction (bCommit);
	} // while -- end traversal of action list.
}// CActionList::CleanupAction

BOOL CActionList::PushAction (LOG_RM_COMMAND rmCommand,FILE_OPERATION eFileOp, TCHAR *pszParm1,TCHAR *pszParm2)
{
	CAction	*pAction = new CAction(rmCommand, eFileOp, pszParm1, pszParm2);

	_ASSERTE (0 != pAction);
	if (0 == pAction)
	{
		return FALSE;
	} // if

	insert(begin(), pAction);

	return TRUE;

} // CActionList::PushAction


BOOL CActionList::PushAction(CAction * pAction)
{
	_ASSERTE (0 != pAction);
	if (0 == pAction)
	{
		return FALSE;
	} // if	
 
	insert(begin(), pAction);
	return TRUE;

		
}

//
//	returns a pointer to the first element in the list
//
BOOL CActionList::PeekAction (CAction ** pprmAction)
{
	if (empty())
		return FALSE;

	CAction	*prmAction = NULL;	
	*pprmAction = front();
	return TRUE;
} // CActionList::GetAction


//
//	if bCommit is true, we delete any temporary files
//	created during the tx (the only temp file that will
//	still be around are files that were replaced during
//	a copy	
//
BOOL CActionList::RemoveAction (BOOL bCommit /* = FALSE */)
{
	if (empty())
		return FALSE;

	CAction	*pAction;
	PeekAction(&pAction); // get the pointer

// if we committed the tx, then we need to remove
// the recover file, if it exists
	if (bCommit)
	{
		if (pAction -> m_eFileOp == RM_DELETE)
		{
			pAction -> ReleaseLock();
			// delete the recover file
			DeleteFile(pAction -> m_pszLockedFile);
		}

	}
	delete pAction;
	pAction = 0;
	// remove it from the list
	pop_front();
	return TRUE;
} // CActionList::RemoveAction


	
BOOL CActionList::PopAction (CAction& rmAction)
{
	if (empty())
		return FALSE;
//
//	CODEREVIEW:
//		is this a correct dereference?
//
	rmAction  = *front();
	pop_front();
	return TRUE;
} // CActionList::PopAction



void CActionList::ResetActions (CActionList *actionList)
{
	// List of actions not empty.
	ACTIONLIST::iterator item;
	CAction * pAction;
	for (item = begin(); item != end(); ++item)
	{
		pAction = *item;
		delete pAction;
	}
	
	clear();
	// Set the current action list to the actionList
	Clone (actionList);

} // CActionList::ResetActions()

//
//	iterate through the list of actions
//	and copy the CAction* to the local list
//
void CActionList::Clone (CActionList * pList)
{
	 if (!pList)
		 return;

	 if (pList -> empty())
		 return;

	 ACTIONLIST::iterator item;
	 for (item=pList -> begin();item != pList -> end(); ++item)
	 {		
		push_back(*item); // mainttain the order
	 }
	

} // CActionList::Clone
	

//---------------------------------------------------------------------
// End of $Workfile: ACTION.CPP $
//---------------------------------------------------------------------

