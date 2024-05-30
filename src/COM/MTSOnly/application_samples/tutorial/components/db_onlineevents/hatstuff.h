// hatStuff.h: Definition of the ChatStuff class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HATSTUFF_H__273392CE_F64C_11D1_9734_00805F31E0AF__INCLUDED_)
#define AFX_HATSTUFF_H__273392CE_F64C_11D1_9734_00805F31E0AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// ChatStuff

class ChatStuff : 
	public CComDualImpl<IChatStuff, &IID_IChatStuff, &LIBID_DB_ONLINEEVENTSLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<ChatStuff,&CLSID_ChatStuff>
{
public:
	ChatStuff() {}
BEGIN_COM_MAP(ChatStuff)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IChatStuff)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(ChatStuff) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_hatStuff)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IhatStuff
public:
};

#endif // !defined(AFX_HATSTUFF_H__273392CE_F64C_11D1_9734_00805F31E0AF__INCLUDED_)
