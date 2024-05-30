/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

    javaprop.hpp

Abstract:

    Contains the CEnumJAVAPROPERTY class definition.

--*/

#ifndef __CJAVAPROP_HPP__
#define __CJAVAPROP_HPP__

#include "javaexec.h"

// Linked list node to keep track of a single property.

typedef struct _JAVAPROPLINK  JAVAPROPLink, *LPJAVAPROPLink;

struct _JAVAPROPLINK
{
    LPOLESTR        pszKey;
    LPOLESTR        pszValue;
    LPJAVAPROPLink  pNext;
};

// Property enumeration interface suitable for use with
// IJavaExecute2::SetSystemProperties

class CEnumJAVAPROPERTY : public IEnumJAVAPROPERTY
{
    private:
        ULONG          m_cRef;

        LPJAVAPROPLink m_pPropList;     // List of properties.
        ULONG          m_cProperties;   // # of properties in list.
        LPJAVAPROPLink m_pCurProp;      // Current property.

    public:
        CEnumJAVAPROPERTY();
        ~CEnumJAVAPROPERTY();

        BOOL Add( char *pszKeyAndValue );

        //  IUnknown methods
        STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppvObj);
        STDMETHOD_(ULONG, AddRef)();
        STDMETHOD_(ULONG, Release)();

        //  IEnumJAVAPROPERTY methods
        STDMETHOD(Next)(ULONG celt, LPJAVAPROPERTY rgelt, ULONG *pceltFetched);
        STDMETHOD(Skip)(ULONG celt);
        STDMETHOD(Reset)();
        STDMETHOD(Clone)(LPENUMJAVAPROPERTY *ppenum);
};

#endif  /* ! __CJAVAPROP_HPP__ */

