/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

    cresprop.cpp

Abstract:

    Implements the CEnumResourceJAVAPROPERTY class.

--*/

#pragma hdrstop

#include <windows.h>
#include "javaprop.hpp"

// Construct a new, empty property enumerator.

CEnumJAVAPROPERTY::CEnumJAVAPROPERTY()
{
    m_cRef = 1;

    m_pPropList   = NULL;
    m_pCurProp    = NULL;
    m_cProperties = 0;
}

CEnumJAVAPROPERTY::~CEnumJAVAPROPERTY()
{
    LPJAVAPROPLink pProp = m_pPropList;
    LPJAVAPROPLink pPropTmp;
    
    // Walk down the list of properties freeing each node.

    while (pProp)
    {
        if (pProp->pszKey)   delete(pProp->pszKey);
        if (pProp->pszValue) delete(pProp->pszValue);
        
        pPropTmp = pProp;
        pProp    = pProp->pNext;

        delete(pPropTmp);
    }
}

STDMETHODIMP
CEnumJAVAPROPERTY::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
    HRESULT hr;

    if (riid == IID_IEnumJAVAPROPERTY || riid == IID_IUnknown) {
        *ppvObj = (LPENUMJAVAPROPERTY) this;
        m_cRef++;
        hr = S_OK;
    } else {
        *ppvObj = NULL;
        hr = E_NOINTERFACE;
    }

    return hr;
}

STDMETHODIMP_(ULONG)
CEnumJAVAPROPERTY::AddRef()
{
    m_cRef++;

    return m_cRef;
}

STDMETHODIMP_(ULONG)
CEnumJAVAPROPERTY::Release()
{
    m_cRef--;

    if (m_cRef > 0)
        return m_cRef;

    delete this;
    return 0;
}

STDMETHODIMP
CEnumJAVAPROPERTY::Next(ULONG celt, LPJAVAPROPERTY rgelt, ULONG
    *pceltFetched)
{
    HRESULT hr;
    ULONG celtFetched;

    hr = S_OK;
    celtFetched = 0;

    while (hr == S_OK && celtFetched < celt) {

        if (m_pCurProp == NULL) {
            hr = S_FALSE;
            break;
        }

        // Copy the value.

        rgelt->pszValue = (LPOLESTR)
            CoTaskMemAlloc((lstrlenW(m_pCurProp->pszValue) + 1) *
            sizeof(OLECHAR));

        if (rgelt->pszValue != NULL) {
            wcscpy(rgelt->pszValue, m_pCurProp->pszValue);
        } else {
            hr = E_OUTOFMEMORY;
        }

        // Copy the key.

        if (hr == S_OK) 
        {

            rgelt->pszKey = (LPOLESTR)
                CoTaskMemAlloc((lstrlenW(m_pCurProp->pszKey) + 1) *
                sizeof(OLECHAR));

            if (rgelt->pszKey != NULL) {

                wcscpy(rgelt->pszKey, m_pCurProp->pszKey);

                rgelt++;
                m_pCurProp = m_pCurProp->pNext;
                celtFetched++;

            } else {
                CoTaskMemFree(rgelt->pszValue);
                hr = E_OUTOFMEMORY;
            }
        }
    }

    if (pceltFetched != NULL)
        *pceltFetched = celtFetched;

    return hr;
}

STDMETHODIMP
CEnumJAVAPROPERTY::Skip(ULONG celt)
{
    HRESULT hr = S_OK;

    while ( celt > 0 )
    {
        if ( m_pCurProp->pNext == NULL )
        {
            hr = S_FALSE;
            break;
        }

        m_pCurProp = m_pCurProp->pNext;
        celt--;
    }

    return hr;
}

STDMETHODIMP
CEnumJAVAPROPERTY::Reset()
{
    m_pCurProp = m_pPropList;
    return S_OK;
}

STDMETHODIMP
CEnumJAVAPROPERTY::Clone(LPENUMJAVAPROPERTY *ppenum)
{
    return E_NOTIMPL;
}

// Add a property to the list of properties.  The string parameter is
// expected to be of the form <key>=<value>.

BOOL CEnumJAVAPROPERTY::Add(char *pszKeyAndValue)
{
    char *pszKey = pszKeyAndValue;
    char *pszVal = pszKey;
    int   cchUnicode;

    if ( *pszKey == '\0' )
        return FALSE;

    // Walk down the string looking for the '=' that seperates the key
    // and value.
    while ( *pszVal && *pszVal != '=' )
        pszVal++;

    if ( *pszVal == '=' ) {
       *pszVal = '\0';
       pszVal++;
    }

    // Create a new node for our linked list.
    LPJAVAPROPLink pProp = new(JAVAPROPLink);

    if ( !pProp )
        return FALSE;

    // We want to keep track of the key and value strings as unicode.  
    // Convert them and stash them off into the property node.
    
    // Convert the key.

    cchUnicode = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszKey, -1, 
                                     NULL, 0);

    pProp->pszKey = new(OLECHAR[cchUnicode]);

    if ( !pProp->pszKey )
    {
        delete(pProp);
        return FALSE;
    }

    MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pszKey,-1,pProp->pszKey,
                        cchUnicode);

    // Convert the value.

    cchUnicode = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszVal, 
                                     -1, NULL, 0);

    pProp->pszValue = new(OLECHAR[cchUnicode]);

    if ( !pProp->pszValue )
    {
        delete(pProp->pszKey);
        delete(pProp);
        return FALSE;
    }

    MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pszVal,-1,pProp->pszValue,
                        cchUnicode);

    // Link the new node into the list.

    pProp->pNext = m_pPropList;
    m_pPropList  = pProp;
    m_pCurProp   = m_pPropList;

    return TRUE;
}

