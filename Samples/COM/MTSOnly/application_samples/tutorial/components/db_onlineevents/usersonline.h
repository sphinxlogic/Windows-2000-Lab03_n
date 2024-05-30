// UsersOnline.h: Definition of the UsersOnline class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSONLINE_H__273392CB_F64C_11D1_9734_00805F31E0AF__INCLUDED_)
#define AFX_USERSONLINE_H__273392CB_F64C_11D1_9734_00805F31E0AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// UsersOnline

class UsersOnline : 
	public CComDualImpl<IUsersOnline, &IID_IUsersOnline, &LIBID_DB_ONLINEEVENTSLib>, 
	public ISubscriberControl,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<UsersOnline,&CLSID_UsersOnline>
{
public:
	UsersOnline() {}
BEGIN_COM_MAP(UsersOnline)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUsersOnline)
	COM_INTERFACE_ENTRY(ISubscriberControl)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(UsersOnline) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_REGISTRY_RESOURCEID(IDR_UsersOnline)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUsersOnline
public:
	STDMETHOD(Update)(IN BSTR strCustomerID);
	STDMETHOD(PreEventCall)( /* [in] */ IUnknown *pISubscription);

private:
	WCHAR m_strTableName[100];

};

#endif // !defined(AFX_USERSONLINE_H__273392CB_F64C_11D1_9734_00805F31E0AF__INCLUDED_)
