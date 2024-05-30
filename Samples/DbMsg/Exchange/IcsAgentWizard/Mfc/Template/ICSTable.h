/************************************************************************
*                                                                       *
*   $$Root$$Table.h													*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#ifndef $$ROOT$$_TABLE_H
#define $$ROOT$$_TABLE_H

#include "stdafx.h"
#include "$$Root$$Util.h"
#include "$$Root$$ContentCollector.h"
#include "$$Root$$HierarchyCollector.h"
#include "$$Root$$Synchronizer.h"

class C$$Root$$Agent;

//
// The default size for the C$$Root$$Table.  It was chosen
// because it was a prime number close to a power of 2.
//
#define IT_DEFLT_SIZE 1549  



class C$$Root$$Table {

public:
	C$$Root$$Table();
	C$$Root$$Table(LPUNKNOWN lpCollector, 
			  short sCollectorType, 
			  C$$Root$$Agent * lpAgent);
	C$$Root$$Table(LPUNKNOWN lpCollector, 
			  short sCollectorType, 
			  C$$Root$$Agent * lpAgent,
			  ULONG initialSize);
	~C$$Root$$Table();

	
	HRESULT					Get(ULONG ulCb,
								LPENTRYID lpeid,
								LP$$ROOT$$SYNCHRONIZER * lppICSSynchronizer);
	BOOL					HasMoreElems();
	BOOL					Initialize();
	LP$$ROOT$$SYNCHRONIZER	NextElem();
	HRESULT					Put(ULONG ulCb,
								LPENTRYID lpeid,
								LPMDB lpStore);
	void					ResetEnumeration();
	void					SetCurrentSynchronizer(LP$$ROOT$$SYNCHRONIZER lpSynchronizer);

	//
	// Data-member access methods
	//

	C$$Root$$Agent * Agent()	{ return m_lpAgent; }
	LPUNKNOWN Collector()		{ return m_lpCollector; }
	short CollectorType()		{ return m_sCollectorType; }


	//
	// Converts this C$$Root$$Table to an ASCII representation
	// 

	operator string();	
	
private:

	HRESULT DecreaseSize() { return E_FAIL; }  // not yet implemented
	HRESULT IncreaseSize();
	HRESULT InitEnumeration();

	//
	// Methods to perform operations upon an arbitrary table
	//
	static HRESULT AddToTable(ULONG cb, 
  							  LPENTRYID lpEntryID,
							  ULONG ulTableSize,
							  LP$$ROOT$$SYNCHRONIZER * lpTable,
							  LP$$ROOT$$SYNCHRONIZER lpICSSynchronizer
							  );
	static HRESULT GetFromTable(ULONG cb, 
							    LPENTRYID lpEntryID,
								ULONG ulTableSize,
								LP$$ROOT$$SYNCHRONIZER * lpTable,
								LP$$ROOT$$SYNCHRONIZER * lpICSSynchronizer);
	static ULONG HashFunction(ULONG ulKey, ULONG ulTableSize) { return ulKey % ulTableSize; }
	static ULONG lpeidToUl(LPENTRYID lpeid, ULONG cb);


	//
	// Data members containing the data to implement
	// the Enumeration methods for this class
	//
	ULONG								m_ulCurrentElem;
	BOOL								m_fNextElemReady;
	
	//
	// The data members representing the actual hashtable 
	//
	LP$$ROOT$$SYNCHRONIZER *					m_lpTable;
	ULONG								m_ulNumElems;
	ULONG								m_ulTableSize;

	//
	// Data members representing the collector which
	// uses the data stored in this C$$Root$$Table
	//
	LPUNKNOWN       					m_lpCollector;
	short m_sCollectorType;

	//
	// A backpointer to the C$$Root$$Agent object that created
	// this C$$Root$$Table.  It should not be modified.
	//
	C$$Root$$Agent *							m_lpAgent;
};

typedef C$$Root$$Table * LP$$ROOT$$TABLE;

#endif // #ifndef $$ROOT$$_TABLE_H
