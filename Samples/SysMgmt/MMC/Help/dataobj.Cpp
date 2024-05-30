//==============================================================;
//
//	This source code is only intended as a supplement to existing Microsoft documentation. 
//
//	Use of this code is NOT supported.  
//
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
//
//    Microsoft Premier Support for Developers
//
//==============================================================;

#include "DataObj.h"
#include "guids.h"
#include "DeleBase.h"

//
// This is the minimum set of clipboard formats we must implement.
// MMC uses these to get necessary information from our snapin about
// our nodes.
//

UINT CDataObject::s_cfDisplayName = 0;
UINT CDataObject::s_cfNodeType    = 0;
UINT CDataObject::s_cfSZNodeType  = 0;
UINT CDataObject::s_cfSnapinClsid = 0;
UINT CDataObject::s_cfInternal    = 0;

static const _TCHAR *CCF_INTERNAL_SNAPIN = _T("{2479DB32-5276-11d2-94F5-00C04FB92EC2}");

CDataObject::CDataObject(MMC_COOKIE cookie, DATA_OBJECT_TYPES context)
: m_lCookie(cookie), m_context(context)
{
    m_cref = 0;
    
    // These are the clipboard formats that we must supply at a minimum.
    // mmc.h actually defined these. We can make up our own to use for
    // other reasons. We don't need any others at this time.
    if (s_cfDisplayName == 0) {
        s_cfDisplayName = RegisterClipboardFormat(CCF_DISPLAY_NAME);
        s_cfNodeType    = RegisterClipboardFormat(CCF_NODETYPE);
        s_cfSZNodeType  = RegisterClipboardFormat(CCF_SZNODETYPE);
        s_cfSnapinClsid = RegisterClipboardFormat(CCF_SNAPIN_CLASSID);
        s_cfInternal    = RegisterClipboardFormat(CCF_INTERNAL_SNAPIN);
    }
}

CDataObject::~CDataObject()
{
}

///////////////////////
// IUnknown implementation
///////////////////////

STDMETHODIMP CDataObject::QueryInterface(REFIID riid, LPVOID *ppv)
{
    if (!ppv)
        return E_FAIL;
    
    *ppv = NULL;
    
    if (IsEqualIID(riid, IID_IUnknown))
        *ppv = static_cast<IDataObject *>(this);
    else if (IsEqualIID(riid, IID_IDataObject))
        *ppv = static_cast<IDataObject *>(this);
    
    if (*ppv)
    {
        reinterpret_cast<IUnknown *>(*ppv)->AddRef();
        return S_OK;
    }
    
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CDataObject::AddRef()
{
    return InterlockedIncrement((LONG *)&m_cref);
}

STDMETHODIMP_(ULONG) CDataObject::Release()
{
    if (InterlockedDecrement((LONG *)&m_cref) == 0)
    {
        delete this;
        return 0;
    }
    return m_cref;
    
}

/////////////////////////////////////////////////////////////////////////////
// IDataObject implementation
// 
HRESULT CDataObject::GetDataHere(
                                 FORMATETC *pFormatEtc,     // [in]  Pointer to the FORMATETC structure 
                                 STGMEDIUM *pMedium         // [out] Pointer to the STGMEDIUM structure  
                                 )
{
    HRESULT hr = DV_E_FORMATETC;         // Unknown format
    const   CLIPFORMAT cf = pFormatEtc->cfFormat;
    IStream *pStream = NULL;
    
    CDelegationBase *base = GetBaseNodeObject();
    
    hr = CreateStreamOnHGlobal( pMedium->hGlobal, FALSE, &pStream );
    if ( FAILED(hr) )
        return hr;                       // Minimal error checking
    
    if (cf == s_cfDisplayName) {
        const _TCHAR *pwszName = base->GetDisplayName();
        
        ULONG ulSizeofName = _tcslen(pwszName);
        ulSizeofName++;                      // Count null character
        ulSizeofName *= sizeof(_TCHAR);
        
        hr = pStream->Write(pwszName, ulSizeofName, NULL);
    } else if (cf == s_cfNodeType) {
        const GUID *pGUID = (const GUID *)&base->getNodeType();
        
        hr = pStream->Write(pGUID, sizeof(GUID), NULL);
    } else if (cf == s_cfSZNodeType) {
        LPOLESTR szGuid;
        hr = StringFromCLSID(base->getNodeType(), &szGuid);
        
        if (SUCCEEDED(hr)) {
            hr = pStream->Write(szGuid, _tcslen(szGuid), NULL);
            CoTaskMemFree(szGuid);
        }
    } else if (cf == s_cfSnapinClsid) {
        const GUID *pGUID = NULL;
        pGUID = &CLSID_CComponentData;
        
        hr = pStream->Write(pGUID, sizeof(GUID), NULL);
    } else if (cf == s_cfInternal) {
        // we are being asked to get our this pointer from the IDataObject interface
        // only our own snap-in objects will know how to do this.
        CDataObject *pThis = this;
        hr = pStream->Write( &pThis, sizeof(CDataObject*), NULL );
    }
    
    pStream->Release();
    
    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// Global helper functions to help work with dataobjects and
// clipboard formats


//---------------------------------------------------------------------------
//  Returns the current object based on the s_cfInternal clipboard format
// 
CDataObject* GetOurDataObject (
                               LPDATAOBJECT lpDataObject      // [in] IComponent pointer 
                               )
{
    HGLOBAL			 hGlobal = NULL;
    HRESULT			 hr      = S_OK;
    CDataObject *pSDO     = NULL;
    
    // quick exit if we didn't get a DataObject
    if (lpDataObject == NULL)
        return NULL;
    
    STGMEDIUM stgmedium = { TYMED_HGLOBAL,  NULL  };
    FORMATETC formatetc = { CDataObject::s_cfInternal, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
    
    // Allocate memory for the stream
    stgmedium.hGlobal = GlobalAlloc( GMEM_SHARE, sizeof(CDataObject *));
    
    if (!stgmedium.hGlobal)	{
        hr = E_OUTOFMEMORY;
    }
    
    if SUCCEEDED(hr)
        // Attempt to get data from the object
        hr = lpDataObject->GetDataHere( &formatetc, &stgmedium );
    
    // stgmedium now has the data we need 
    if (SUCCEEDED(hr))  {
        pSDO = *(CDataObject **)(stgmedium.hGlobal);
    }
    
    // if we have memory free it
    if (stgmedium.hGlobal)
        GlobalFree(hGlobal);
    
    return pSDO;
    
} // end GetOurDataObject()

