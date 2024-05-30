// WBWAB.h : Declaration of the CWBWAB
// This is a helper ActiveX control for the Visual Basic and Visual J++
// MyWebBrowser applications. CWBWAB provides 
//    - access to the Internet Explorer Address Book API to start up
//      the Address Book with the same parameters are used by IE itself
//    - Mail and News clients using the registry settings for current default
//      clients
//    - access to the Find and Properties commands in the OleCommmandTarget
//      group  as documented in the Knowledge Base Article Q175513.
//    - Organize favorites function exported from shdocvw.dll
// Microsoft Corporation Copyright 1999 

#ifndef __WBWAB_H_
#define __WBWAB_H_

#include "resource.h"       // main symbols
#include <ExDisp.h>

/////////////////////////////////////////////////////////////////////////////
// CWBWAB
class ATL_NO_VTABLE CWBWAB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWBWAB, &CLSID_WBWAB>,
	public IObjectWithSiteImpl<CWBWAB>,
	public IDispatchImpl<IWBWAB, &IID_IWBWAB, &LIBID_WBADDRBOOKLib>
{
public:
	STDMETHOD(get_WebBrowser)(/*[out, retval]*/ LPDISPATCH* ppWebBrowser);
	STDMETHOD(putref_WebBrowser)(/*[in]*/ LPDISPATCH pWebBrowser);
	STDMETHOD(get_Offline)(/*[out, retval]*/ VARIANT_BOOL * pbOffline);
	STDMETHOD(put_Offline)(/*[in]*/ VARIANT_BOOL bOffline);
	STDMETHOD(ShowAddressBook)(LONG hWnd);
	STDMETHOD(ShowMail)(LONG hWnd);
	STDMETHOD(ShowNews)(LONG hWnd);
    STDMETHOD(ShowProperties)(void);
    STDMETHOD(ShowFind)(void);
    STDMETHOD(ShowViewSource)(void);
    STDMETHOD(ShowOrganizeFavorites)(LONG hWnd);
    STDMETHOD(ShowUpdateSubscriptions)(void);
    STDMETHOD(ShowMyComputer)(LONG hWnd);
	STDMETHOD(GetURL)(VARIANT vPath, LPVARIANT vURL);

	CWBWAB()
	{
	}

	~CWBWAB()
	{
		if (m_hInstWAB)
		{
			FreeLibrary(m_hInstWAB);
		}
      // release the webbrowser ptr here?
	}
DECLARE_REGISTRY_RESOURCEID(IDR_WBWAB)

BEGIN_COM_MAP(CWBWAB)
	COM_INTERFACE_ENTRY(IWBWAB)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IObjectWithSite)
END_COM_MAP()

// Data Members
private:
   CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser;
	HMODULE m_hInstWAB;

// Utility Methods
   STDMETHOD(ShowClient)(LONG hWnd, TCHAR * szClient);
   STDMETHOD(ShowWBCmdGroup)(int);
#ifndef UNICODE
   char * getAnsi(CComBSTR bstr);
#endif

private:
	
////////////////////////////////////////////////////
// Interface Implementation

// IDispatch
protected:

// IWBWAB
public:
};

#endif //__WBWAB_H_
