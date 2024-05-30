//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       oblist.cpp
//  Content:    This file contains the list class functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include <windows.h>
#include "oblist.h"

//****************************************************************************
// void* COBLIST::GetTail()
//
// Returns the end of the list.
//
//****************************************************************************
VOID* COBLIST::GetTail()
{
	return m_pTail->pItem;
}

//****************************************************************************
// VOID* COBLIST::GetNext(POSITION& rPos)
//
// Returns the next item of the list.
//
//****************************************************************************
VOID* COBLIST::GetNext(POSITION& rPos)
{
	VOID* pReturn = rPos->pItem;
	rPos = rPos->pNext;
	return pReturn;
}

//****************************************************************************
// VOID* COBLIST::RemoveAt(POSITION Pos)
//
// Removes an item from the list.
//
//****************************************************************************
VOID* COBLIST::RemoveAt(POSITION Pos)
{
	VOID* pReturn = NULL;

	if (m_pHead)
	{
		if (m_pHead == Pos)
		{
			// Removing the first element in the list
			
			m_pHead = Pos->pNext;
			pReturn = Pos->pItem;
			delete Pos;

			if (NULL == m_pHead)
			{
				// Removing the only element!
				m_pTail = NULL;
			}
		}
		else
		{
			POSITION pCur = m_pHead;

			while (pCur && pCur->pNext)
			{
				if (pCur->pNext == Pos)
				{
					// Removing 
					
					pCur->pNext = Pos->pNext;
					if (m_pTail == Pos)
					{
						m_pTail = pCur;
					}
					pReturn = Pos->pItem;
					delete Pos;
				}

				pCur = pCur->pNext;
			}
		}
	}

	return pReturn;
}


//****************************************************************************
// POSITION COBLIST::AddTail(VOID* pItem)
//
// Add to the end of the list.
//
//****************************************************************************
POSITION COBLIST::AddTail(VOID* pItem)
{
	POSITION posRet = NULL;

	if (m_pTail)
	{
		if (m_pTail->pNext = new COBNODE)
		{
			m_pTail = m_pTail->pNext;
			m_pTail->pItem = pItem;
			m_pTail->pNext = NULL;
		}
	}
	else
	{
		if (m_pHead = new COBNODE)
		{
			m_pTail = m_pHead;
			m_pTail->pItem = pItem;
			m_pTail->pNext = NULL;
		}
	}

	return m_pTail;
}

//****************************************************************************
// POSITION COBLIST::EmpytList(VOID* pItem)
//
// Frees the entire list.
//
//****************************************************************************
void COBLIST::EmptyList()
{
	while (!IsEmpty()) {
		RemoveAt(GetHeadPosition());
	}
}


//****************************************************************************
// POSITION COBLIST::GetPosition(VOID* _pItem)
//
// return the position of an item in the list
//
//****************************************************************************
POSITION COBLIST::GetPosition(void* _pItem)
{
	POSITION Position = m_pHead;

	while (Position) {
		if (Position->pItem == _pItem) {
			break;
		}
		GetNext(Position);
	}
	return Position;
}

//****************************************************************************
// POSITION COBLIST::Lookup(VOID* _pItem)
//
//
//****************************************************************************
POSITION COBLIST::Lookup(void* pComparator)
{
	POSITION    Position = m_pHead;

	while (Position) {
		if (Compare(Position->pItem, pComparator)) {
			break;
		}
		GetNext(Position);
	}
	return Position;
}


//****************************************************************************
// POSITION COBLIST::SafeGetFromPosition(POSITION Pos)
//
// Safe way to validate that an entry is still in the list,
//
//****************************************************************************
void * COBLIST::SafeGetFromPosition(POSITION Pos)
{
	POSITION PosWork = m_pHead;
	
	while (PosWork) {
		if (PosWork == Pos) {
			return Pos->pItem;
		}
		GetNext(PosWork);
	}
	return NULL;
}
