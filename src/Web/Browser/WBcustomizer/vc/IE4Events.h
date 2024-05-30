//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
//
// IE4Events.h : Declaration of the CIE4Events
//--------------------------------------------------------------------------

#ifndef __IE4Events_H_
#define __IE4Events_H_

class CWBCustomizer;

class CIE4Events :
	public CComObjectRootEx<CComSingleThreadModel>,
   public IDispatch
{
public:
   CIE4Events() : m_pParent(NULL)
   {
   }

   void Init(CWBCustomizer* pParent)
   {
      _ASSERT(pParent);
      m_pParent = pParent;
   }

BEGIN_COM_MAP(CIE4Events)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

protected:
   // IDispatch Methods
   STDMETHOD(GetTypeInfoCount)(unsigned int FAR* pctinfo)
   {
      ATLTRACENOTIMPL("GetTypeInfoCount");
   }
 
   STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)        
   {
      ATLTRACENOTIMPL("GetTypeInfo");
   }

        
   STDMETHOD(GetIDsOfNames)(REFIID riid, OLECHAR FAR* FAR* rgszNames, 
                         unsigned int cNames, LCID lcid, DISPID FAR* rgDispId)
   {
      ATLTRACENOTIMPL("GetIDsOfNames");
   }
 
   STDMETHOD(Invoke)(DISPID dispidMember,REFIID riid, LCID lcid, WORD wFlags,
                     DISPPARAMS* pdispparams, VARIANT* pvarResult,
                     EXCEPINFO* pexcepinfo, UINT* puArgErr);

private:
   CWBCustomizer* m_pParent;
};

#endif  // __IE4Events_H_