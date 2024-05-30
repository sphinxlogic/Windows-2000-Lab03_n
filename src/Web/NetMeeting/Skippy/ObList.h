//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       oblist.h
//  Content:    This file contains the list class functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#ifndef _OBLIST_H_
#define _OBLIST_H_

// class COBNODE;
#define POSITION COBNODE*

struct COBNODE
{
	POSITION  pNext;
	void*     pItem;
};

class COBLIST
{
protected:
	POSITION        m_pHead;
	POSITION        m_pTail;
	virtual BOOL    Compare(void* pItemToCompare, void* pComparator)
		{return(pItemToCompare == pComparator);};
public:
	COBLIST() : m_pHead(NULL), m_pTail(NULL) { };
	~COBLIST() {};

	POSITION        GetHeadPosition() { return(m_pHead); };
	POSITION        GetTailPosition() { return(m_pTail); };
	virtual void *  RemoveAt(POSITION rPos);
	POSITION        AddTail(void* pItem);
	BOOL            IsEmpty() { return(!m_pHead); };
	void *          GetTail();
	void *          GetNext(POSITION& rPos);
	void *          SafeGetFromPosition(POSITION rPos);
	POSITION        GetPosition(void* pItem);
	POSITION        Lookup(void* pComparator);
	void            EmptyList();

	void *          GetHead(){return GetFromPosition(GetHeadPosition());};
	void *          RemoveHead() { return RemoveAt(m_pHead); };
	void *          GetFromPosition(POSITION rPos){return(rPos->pItem);};
};

#endif // ifndef _OBLIST_H_
