// ----------------------------------------------------------------------------
//	BaseCondition.h : Declaration of the CBaseCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __BASECONDITION_H_
#define __BASECONDITION_H_

// CBaseCondition
class CBaseCondition
{
public:
	virtual HRESULT	load(LPSRestriction	pRes)=0;
	virtual HRESULT	pack(LPSRestriction	lpRes,LPVOID lpObject=NULL)=0;
};
#endif //__BASECONDITION_H_
