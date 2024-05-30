
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// ObjVwCtl.cpp : Implementation of CObjVw
#include "stdafx.h"
#include "ObjVw.h"
#include "ObjVwCtl.h"

/////////////////////////////////////////////////////////////////////////////
// CObjVw

STDMETHODIMP CObjVw::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IObjVw,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CObjVw::SetClientSite(IOleClientSite *pClientSite)
{
	HRESULT hr = S_OK;

	if(NULL != pClientSite)
	{
		ATLTRACE(_T("SetClientSite called\n"));

		m_spClientSite = pClientSite;  // This AddRefs the client site
									   // if null, existing client site is released
	}
	else
	{
		//REMOVE: _ASSERT(0 != m_dwAdviseCookie);
		_ASSERT(m_spWebBrowser != NULL);

		ATLTRACE(_T("SetClientSite NULL called\n"));

		//REMOVE: hr = AtlUnadvise( m_spWebBrowser, __uuidof(SHDocVw::DWebBrowserEvents2), m_dwAdviseCookie );
		
		IDispEventImpl<0, CObjVw, &__uuidof(SHDocVw::DWebBrowserEvents2),
					&LIBID_OBJVWLib, 1, 0>::DispEventUnadvise(m_spWebBrowser);
		
		m_spWebBrowser.Release();

		return	S_OK;
	}
	
	try
	{
		IServiceProviderPtr spSP((LPOLECLIENTSITE)m_spClientSite);

		if(NULL == spSP)
			return hr;

		spSP->QueryService(__uuidof(SHDocVw::IWebBrowserApp), 
				__uuidof(SHDocVw::IWebBrowser2), (void**)&m_spWebBrowser);

		//REMOVE: hr = AtlAdvise(m_spWebBrowser, GetControllingUnknown(), __uuidof(SHDocVw::DWebBrowserEvents2), &m_dwAdviseCookie);
		
		IDispEventImpl<0, CObjVw, &__uuidof(SHDocVw::DWebBrowserEvents2),
		    &LIBID_OBJVWLib, 1, 0>::DispEventAdvise(m_spWebBrowser);

	}
	catch(...)
	{
		return S_FALSE;
	}

	return hr;
}

HRESULT CObjVw::OnDraw(ATL_DRAWINFO& di)
{
	return S_OK;
}

STDMETHODIMP CObjVw::Recalc()
{
	EnumFrames();
	return S_OK;
}



/////////////////////////////////////////////////////////////////////////////
// CIEDriveView message handlers

void CObjVw::EnumFrames() 
{	
	// Empty the tree view
	TreeView_DeleteAllItems(m_ctlSysTreeView32.m_hWnd);

	try
	{
		MSHTML::IHTMLDocument2Ptr spDocument(m_spWebBrowser->GetDocument());
		RecurseWindows(spDocument);
	}
	catch(_com_error Error)
	{
		ATLTRACE(Error.ErrorMessage());
	}
	catch(...)
	{
		ATLTRACE(_T("Unspecified exception thrown in OnTestEnumlinks\n"));
	}

	HTREEITEM hFirst = TreeView_GetRoot(m_ctlSysTreeView32.m_hWnd); 
	TreeView_Expand(m_ctlSysTreeView32.m_hWnd, hFirst, TVE_EXPAND); 
}

void CObjVw::RecurseWindows(MSHTML::IHTMLDocument2Ptr spDocument, LPVOID pvTreeParent)
{
	// I am passing in a pointer to the parent node to insert items in the Tree View.
	// Obviously this is specific to this application and has little to do with 
	// enumerating frames in a document.

	LPVOID ppvTree = NULL;

	if(spDocument == NULL)
		// Not an HTML document
		return;

	try
	{
		// Insert a root node for this page.  
		_bstr_t bstrDocTitle = spDocument->Gettitle();

		_bstr_t bstrNoTitle("");
		if(bstrDocTitle == bstrNoTitle)
			bstrDocTitle = "Untitled Document";

		InsertTreeItem(bstrDocTitle, pvTreeParent, &ppvTree); 

		// Find out if this page has a "BODY".  If it does, it will not have a 
		// <FRAMESET> but may still have a floating frame.

		MSHTML::IHTMLElementPtr spBodyElement = spDocument->Getbody();

		_bstr_t bstrBody("BODY");
		_bstr_t bstrTagName = spBodyElement->GettagName();

		if(bstrBody == bstrTagName)
		{
			ATLTRACE(_T("Found a body\n"));

			GetPageContents(spDocument, ppvTree);
		}

		MSHTML::IHTMLFramesCollection2Ptr spFrameset = spDocument->Getframes();

		for(long i = 0; i < spFrameset->Getlength(); i++)
		{
			_variant_t va(i, VT_I4);

			MSHTML::IHTMLWindow2Ptr spWindow2Next = spFrameset->item(&va);
			MSHTML::IHTMLDocument2Ptr spNextDocPtr;
			try
			{
				// This will die in the case of a cross frame security violation.
				// It would be a security risk to allow a page to access the contents 
				// of a page in another domain or zone.
				// It will also die if an HTML page is attempting to access the
				// document object model of a non-HTML page, such as Word, Excel, or
				// other Active Document

				spNextDocPtr = spWindow2Next->Getdocument();
			}
			catch(_com_error Error)
			{
				ATLTRACE(Error.ErrorMessage());
				if(E_ACCESSDENIED == Error.Error())
					InsertTreeItem(_T("Page - Access Denied - violates cross-frame security"), ppvTree, NULL);
				else if(DISP_E_MEMBERNOTFOUND == Error.Error())
					InsertTreeItem(_T("Page - Access Denied - non-HTML document"), ppvTree, NULL); 

				continue;
			}
			catch(...)
			{
				ATLTRACE(_T("Unspecified exception thrown in RecurseWindows\n"));
				continue;
			}

			RecurseWindows(spNextDocPtr, ppvTree);
		}
	}
	catch(_com_error Error)
	{
		ATLTRACE(Error.ErrorMessage());
	}
	catch(...)
	{
		ATLTRACE(_T("Unspecified exception thrown in RecurseWindows\n"));
	}
}

void CObjVw::GetPageContents(MSHTML::IHTMLDocument2Ptr spDocument, LPVOID pvTreeParent)
{
	try
	{
		MSHTML::IHTMLElementPtr spAnElement;
		MSHTML::IHTMLElementCollectionPtr spAllElements = spDocument->Getall();

		for(long i = 0; i < spAllElements->Getlength(); i++)
		{
			_variant_t va(i, VT_I4);
			spAnElement = spAllElements->item(va);

			_bstr_t bstrIsControl("OBJECT");
			_bstr_t bstrIsLink("A");
			_bstr_t bstrTagName = spAnElement->GettagName();

			if(bstrTagName == bstrIsControl)
			{
				// This will get you any ActiveX controls in a page.  It is possible 
				// to call methods and properties of the  control off the IHTMLElementPtr.
				
				////This is for illustration only
				//{
				//	OLECHAR* rgwzCaption[] = {OLESTR("Caption")};
				//	DISPID rgdispidCaption[1];
				//
				//	_bstr_t bstrLabel1("Label1");
				//	if(spAnElement->Getid() == bstrLabel1)
				//	{
				//		IDispatchPtr pDispatch(spAnElement);
				//		HRESULT hr = pDispatch->GetIDsOfNames(IID_NULL, rgwzCaption, 1, 
				//					LOCALE_SYSTEM_DEFAULT, rgdispidCaption);
				//
				//		if(SUCCEEDED(hr))
				//		{
				//			// You would call Invoke at this point
				//		}
				//	}
				//}

				_bstr_t bstrTagID("ActiveX Control - ");
				bstrTagID += spAnElement->Getid();

				InsertTreeItem(bstrTagID, pvTreeParent, NULL); 
			}
			if(bstrTagName == bstrIsLink)
			{
				MSHTML::IHTMLAnchorElementPtr spAnchor(spAnElement);
				_bstr_t bstrHref = spAnchor->Gethref();
				InsertTreeItem(bstrHref, pvTreeParent, NULL); 
			}
		}
	}
	catch(_com_error Error)
	{
		ATLTRACE(Error.ErrorMessage());
	}
	catch(...)
	{
		ATLTRACE(_T("Unspecified exception thrown in GetPageContents\n"));
	}
}

bool CObjVw::InsertTreeItem(LPTSTR pszItemText, LPVOID pvTreeParent, LPVOID* ppvTree)
{
    TV_ITEM         tvitem;
    TV_INSERTSTRUCT tvis;
    HTREEITEM*      ppTree = (HTREEITEM*)ppvTree;
    HTREEITEM       pTreeParent = (HTREEITEM)pvTreeParent;
    HTREEITEM       pretTree;

    tvitem.mask = TVIF_TEXT;
    tvitem.pszText = pszItemText;
    tvitem.cchTextMax = _tcslen(pszItemText);
    tvis.item = tvitem;
    tvis.hInsertAfter = (HTREEITEM)TVI_LAST;
    tvis.hParent = pTreeParent;

    pretTree = (HTREEITEM)::SendMessage(m_ctlSysTreeView32.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)&tvis);
    if(!pretTree)
        return false;
    
    if ( ppvTree )
        (*ppvTree) = (LPVOID)pretTree;

    return true;
}

STDMETHODIMP CObjVw::DocumentComplete(IDispatch* pDisp, VARIANT* URL)
{
	// DocumentComplete is fired for each frame that has completed loading.
	// The outer most frame will fire last.

	ATLTRACE(_T("DocumentComplete called\n"));

	if(m_spWebBrowser == pDisp)
	{
		EnumFrames();
	}

	return S_OK;
}
