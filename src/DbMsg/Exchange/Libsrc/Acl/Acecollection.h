/* --------------------------------------------------------------------------

The header file for ACECollection Object

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// ACECollection.h : Declaration of the CACECollection

#ifndef __ACECOLLECTION_H_
#define __ACECOLLECTION_H_

#include "resource.h"       // main symbols
#include "ACLCommon.h"
#include "ExchTable.h"
#include "ACEMap.h"
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CACECollection
class ATL_NO_VTABLE CACECollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public IDispatchImpl<IACEs, &IID_IACEs, &LIBID_MSExchangeACLLib>
{
public:
	CACECollection() : m_pACEMap(NULL),
                       m_pExchTable(NULL)
	{
	}

	~CACECollection()
	{
		delete m_pACEMap;
		m_pACEMap = NULL;
		delete m_pExchTable;
		m_pExchTable = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ACECOLLECTION)
DECLARE_NOT_AGGREGATABLE(CACECollection)

BEGIN_COM_MAP(CACECollection)
	COM_INTERFACE_ENTRY(IACEs)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IACECollection
public:
// interface methods
	STDMETHOD(Delete)(/*[in]*/ VARIANT Index);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ LPVARIANT pItem);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(Add)(/*[in]*/ IACE* ACE);

// class methods
	STDMETHOD(SetDoc)(LPDISPATCH lpdispDoc);
	STDMETHOD(Update)();
	STDMETHOD(Initialize)();
private:
	// a member holding map object
	CACEMap* m_pACEMap;
	// a member holding the exchange table
	CExchTable* m_pExchTable;
};

#endif //__ACECOLLECTION_H_
