// ----------------------------------------------------------------------------
//	module.h
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef _MODULE_H_
#define _MODULE_H_

class CEDKRulesComModule : public CComModule
{
public:
	LPDISPATCH		m_pCDOSession;	// CDO Session object IDispatch interface pointer
	LPDISPATCH		m_pDispFolder;	// CDO Folder pointer set by clients
	HRESULT CreateResInstance(ULONG rt,LPVOID *ppRes);
};

#endif	// _MODULE_H_
