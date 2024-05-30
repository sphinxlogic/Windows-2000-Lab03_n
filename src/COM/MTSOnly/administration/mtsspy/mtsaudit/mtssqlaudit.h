	
// MtsSqlAudit.h : Declaration of the CMtsSqlAudit

#ifndef __MTSSQLAUDIT_H_
#define __MTSSQLAUDIT_H_

#include "resource.h"       // main symbols
#define SQL_BUF_SIZE	1024

/////////////////////////////////////////////////////////////////////////////
// CMtsSqlAudit
class ATL_NO_VTABLE CMtsSqlAudit : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMtsSqlAudit, &CLSID_MtsSqlAudit>,
	public IMtsSqlAudit

{

private:
		HENV m_henv;
		HDBC m_hdbc;
		HSTMT m_hstmt;
		LONGLONG m_PerformanceFrequency;
		WCHAR m_sSQL[SQL_BUF_SIZE];

public:
	CMtsSqlAudit()
	{
		m_hdbc = m_henv = m_hstmt = NULL;
		m_PerformanceFrequency = 0;
		m_pUnkMarshaler = NULL;
	}

	void GetError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR *msg);

DECLARE_REGISTRY_RESOURCEID(IDR_MTSSQLAUDIT)
DECLARE_NOT_AGGREGATABLE(CMtsSqlAudit)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CMtsSqlAudit)
	COM_INTERFACE_ENTRY(IMtsSqlAudit)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

	HRESULT FinalConstruct()
	{
		
		QueryPerformanceFrequency((LARGE_INTEGER *)&m_PerformanceFrequency);
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
		RETCODE rc;
		if (m_hstmt)
		{
			SQLFreeStmt( m_hstmt, SQL_DROP );    
		}
		if (m_hdbc)
		{
		   rc = SQLDisconnect( m_hdbc);
		   SQLFreeConnect( m_hdbc);
		   SQLFreeEnv( m_henv );
		}
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// IMtsSqlAudit
public:
	STDMETHOD(Init)(LPCOLESTR sDSN, LPCOLESTR sUser, LPCOLESTR sPw);

    STDMETHOD(OnUserEvent)(				
				LONGLONG perfCount,		
                VARIANT * pvarEvent		
            );
    STDMETHOD(OnThreadStart)(			
                LONGLONG perfCount,		
                ULONG ThreadID			
            );

    STDMETHOD(OnThreadTerminate)(		
                LONGLONG perfCount,		
                ULONG ThreadID			
            );

    STDMETHOD(OnThreadAssignToActivity)(	
                LONGLONG perfCount,			
                LPCOLESTR guidActivity,		
                ULONG ThreadID				
            );

    STDMETHOD(OnThreadUnassignFromActivity)(	
                LONGLONG perfCount,				
                LPCOLESTR guidActivity,			
                ULONG ThreadID					
            );
    STDMETHOD(OnPackageActivation)(				
                LONGLONG perfCount,				
                LPCOLESTR guidPackage,			
                LPCOLESTR sPackageName			
            );

    STDMETHOD(OnPackageShutdown)(				
                LONGLONG perfCount,				
                LPCOLESTR guidPackage,			
                LPCOLESTR sPackageName			
            );
    STDMETHOD(OnObjectCreate)(			
                LONGLONG perfCount,		
                LPCOLESTR guidActivity,	
                LPCOLESTR clsid,			
                LPCOLESTR tsid,			
                MTS_OBJID ObjectID		
            );

    STDMETHOD(OnObjectRelease)(				
                LONGLONG perfCount,			
                MTS_OBJID ObjectID			
            );

    STDMETHOD(OnTransactionStart)(			
                LONGLONG perfCount,			
                LPCOLESTR guidTx,				
                LPCOLESTR tsid,				
                BOOL fRoot					
            );

    STDMETHOD(OnTransactionPrepared)(		
                LONGLONG perfCount,			
                LPCOLESTR guidTx,				
                BOOL fVoteYes				
            );

    STDMETHOD(OnTransactionAborted)(		
                LONGLONG perfCount,			
                LPCOLESTR guidTx				
            );

    STDMETHOD(OnMethodCall)(				
                LONGLONG perfCount,			
                MTS_OBJID oid,				
                LPCOLESTR guidCid,			
                LPCOLESTR guidRid,				
                LPCOLESTR sMethod
            );

    STDMETHOD(OnMethodReturn)(				
                LONGLONG perfCount,			
                MTS_OBJID oid,				
                LPCOLESTR guidCid,			
                LPCOLESTR guidRid,				
                LPCOLESTR sMethod,				
                HRESULT hresult				
            );

    STDMETHOD(OnMethodException)(			
                LONGLONG perfCount,			
                MTS_OBJID oid,				
                LPCOLESTR guidCid,			
                LPCOLESTR guidRid,				
                LPCOLESTR sMethod
            );
    STDMETHOD(OnObjectActivate)(			
                LONGLONG perfCount,			
                MTS_OBJID ObjectID			
            );

    STDMETHOD(OnObjectDeactivate)(			
                LONGLONG perfCount,			
                MTS_OBJID ObjectID			
            );

    STDMETHOD(OnDisableCommit)(				
                LONGLONG perfCount,			
                MTS_OBJID ObjectID			
            );

    STDMETHOD(OnEnableCommit)(				
                LONGLONG perfCount,			
                MTS_OBJID ObjectID			
            );

    STDMETHOD(OnSetComplete)(				
                LONGLONG perfCount,			
                MTS_OBJID ObjectID			
            );
   STDMETHOD(OnResourceCreate)(				
				LONGLONG perfCount,	
				LPCOLESTR guidActivity,
                MTS_OBJID ObjectID,			
                LPCOLESTR pszType,			
                MTS_RESID resId				
            );

    STDMETHOD(OnResourceAllocate)(		
                LONGLONG perfCount,		
				LPCOLESTR guidActivity,
                MTS_OBJID ObjectID,		
                LPCOLESTR pszType,		
                MTS_RESID resId			
            );

    STDMETHOD(OnResourceRecycle)(		
                LONGLONG perfCount,		
                MTS_OBJID ObjectID,		
                LPCOLESTR pszType,		
                MTS_RESID resId			
            );

    STDMETHOD(OnResourceDestroy)(		
                LONGLONG perfCount,		
                MTS_OBJID ObjectID,		
                LPCOLESTR pszType,		
                MTS_RESID resId			
            );
    STDMETHOD(OnAuthenticate)(								
		          LONGLONG perfCount, 
				  LPCOLESTR guidActivity, 
				  LPCOLESTR sOriginalUser,
				  LPCOLESTR sDirectUser, 
				  BOOL bCurrentUserInpersonatingInProc
            );



	};

#endif //__MTSSQLAUDIT_H_
