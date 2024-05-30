// MtsSqlAudit.cpp : Implementatioof CMtsSqlAudit
#include "stdafx.h"
#include "MtsAudit.h"
#ifndef DBNTWIN32
#define DBNTWIN32
#include <SQL.h>
#include <SQLEXT.h>
#include <ODBCINST.h>
#endif /* DBNTWIN32 */
#include <ODBCINST.h>
#include "MtsSqlAudit.h"

#define SQL_EXEC(x)													\
	{																\
		RETCODE rc;													\
		rc = SQLExecDirect(m_hstmt, x, lstrlen(x));					\
	    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )		\
		{															\
			CComBSTR msg;											\
			GetError( m_henv, m_hdbc, m_hstmt, &msg.m_str);			\
			ATLTRACE(L"Warning! SQlExecDirec failed! Msg: ");		\
			ATLTRACE(msg.m_str);									\
			ATLTRACE(L"\n");										\
		}															\
	}







/////////////////////////////////////////////////////////////////////////////
// CMtsSqlAudit

STDMETHODIMP CMtsSqlAudit::OnUserEvent(
                LONGLONG perfCount,
                VARIANT * pvarEvent
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);

	
	return S_OK;
}
STDMETHODIMP CMtsSqlAudit::OnThreadStart(
                LONGLONG perfCount,
                ULONG ThreadID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);

	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ThreadEvents (tick, threadid, event) values (%d, %d, '%s')",
			 TickCount, 
			 ThreadID,
			 L"OnThreadStart");
	SQL_EXEC(m_sSQL);	
	return S_OK;
}


STDMETHODIMP CMtsSqlAudit::OnThreadTerminate(
                LONGLONG perfCount,
                ULONG ThreadID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);

	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ThreadEvents (tick, threadid, event) values (%d, %d, '%s')",
			 TickCount, 
			 ThreadID,
			 L"OnThreadTerminate");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnThreadAssignToActivity(
                LONGLONG perfCount,
                LPCOLESTR guidActivity,
                ULONG ThreadID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ThreadEvents(tick, threadid, guidActivity, event)	\
				values (%d, %d, '%s', '%s')",
			 TickCount, 
			 ThreadID,
			 guidActivity,
			 L"OnThreadAssignToActivity");
	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnThreadUnassignFromActivity(
                LONGLONG perfCount,
                LPCOLESTR guidActivity,
                ULONG ThreadID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ThreadEvents(tick, threadid, guidActivity, event)	\
				values (%d, %d, '%s', '%s')",
			 TickCount, 
			 ThreadID,
			 guidActivity, 
			 L"OnThreadUnassignFromActivity");

	SQL_EXEC(m_sSQL);
	return S_OK;
}
STDMETHODIMP CMtsSqlAudit::OnPackageActivation(
                LONGLONG perfCount,
                LPCOLESTR guidPackage,
                LPCOLESTR sPackageName
            )
{
   // this should never be called...
	_ASSERTE(0);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnPackageShutdown(
                LONGLONG perfCount,
                LPCOLESTR guidPackage,
                LPCOLESTR sPackageName
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into PackageEvents values (%d, '%s', '%s')",
			 TickCount, 
			 guidPackage,
			 sPackageName);

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnTransactionStart(
                LONGLONG perfCount,
                LPCOLESTR guidTx,
                LPCOLESTR tsid,
                BOOL fRoot
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into TransactionEvents (tick, guidTx, tsid, root, event) \
				values (%d, '%s', '%s', %d, '%s')",
			 TickCount, 
			 guidTx,
			 tsid,
			 fRoot ? 1 : 0,
			 L"OnTransactionStart");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnTransactionPrepared(
                LONGLONG perfCount,
                LPCOLESTR guidTx,
                BOOL fVoteYes
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into TransactionEvents (tick, guidTx, voteYes, event) \
				values (%d, '%s', %d, '%s')",
			 TickCount, 
			 guidTx,
			 fVoteYes ? 1 : 0,
			 L"OnTransactionPrepared");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnTransactionAborted(
                LONGLONG perfCount,
                LPCOLESTR guidTx
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into TransactionEvents (tick, guidTx, event) \
				values (%d, '%s', '%s')",
			 TickCount, 
			 guidTx,
			 L"OnTransactionAborted");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnMethodCall(
                LONGLONG perfCount,
                MTS_OBJID oid,
                LPCOLESTR guidCid,
                LPCOLESTR guidRid,
                LPCOLESTR sMethod
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);

	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into MethodEvents (tick, oid, cid, rid, Method, event) \
				values (%d, %d, '%s', '%s', '%s', '%s')",
			 TickCount, 
			 oid,
			 guidCid,
			 guidRid,
			 sMethod,
			 L"OnMethodCall");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnMethodReturn(
                LONGLONG perfCount,
                MTS_OBJID oid,
                LPCOLESTR guidCid,
                LPCOLESTR guidRid,
                LPCOLESTR sMethod,
                HRESULT hresult
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into MethodEvents (tick, oid, cid, rid, method, hresult, event) \
				values (%d, %d, '%s', '%s', '%s', %d, '%s')",
			 TickCount, 
			 oid,
			 guidCid,
			 guidRid,
			 sMethod,
			 hresult, 
			 L"OnMethodReturn");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnMethodException(
                LONGLONG perfCount,
                MTS_OBJID oid,
                LPCOLESTR guidCid,
                LPCOLESTR guidRid,
                LPCOLESTR sMethod
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
    TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into MethodEvents (tick, oid, cid, rid, Method, event) \
				values (%d, %d, '%s', '%s', '%s', '%s')",
			 TickCount, 
			 oid,
			 guidCid,
			 guidRid,
			 sMethod,
			 L"OnMethodException");

	SQL_EXEC(m_sSQL);
	return S_OK;
}
STDMETHODIMP CMtsSqlAudit::OnObjectCreate(
                LONGLONG perfCount,
                LPCOLESTR guidActivity,
                LPCOLESTR clsid,
                LPCOLESTR tsid,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
    TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, activity, clsid, tsid, ObjectId, event) \
				values (%d, '%s', '%s', '%s', %d, '%s')",
			 TickCount, 
			 guidActivity,
			 clsid,
			 tsid,
			 ObjectID,
			 L"OnObjectCreate");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnObjectRelease(
                LONGLONG perfCount,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, ObjectId, event) \
				values (%d,  %d, '%s')",
			 TickCount, 
			 ObjectID,
			 L"OnObjectRelease");

	SQL_EXEC(m_sSQL);

	return S_OK;
}
STDMETHODIMP CMtsSqlAudit::OnObjectActivate(
                LONGLONG perfCount,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, ObjectId, event) \
				values (%d,  %d, '%s')",
			 TickCount, 
			 ObjectID,
			 L"OnObjectActivate");

	SQL_EXEC(m_sSQL);
	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnObjectDeactivate(
                LONGLONG perfCount,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, ObjectId, event) \
				values (%d,  %d, '%s')",
			 TickCount, 
			 ObjectID,
			 L"OnObjectDeactivate");

	SQL_EXEC(m_sSQL);

	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnDisableCommit(
                LONGLONG perfCount,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, ObjectId, event) \
				values (%d,  %d, '%s')",
			 TickCount, 
			 ObjectID,
			 L"OnDisableCommit");

	SQL_EXEC(m_sSQL);


	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnEnableCommit(
                LONGLONG perfCount,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, ObjectId, event) \
				values (%d,  %d, '%s')",
			 TickCount, 
			 ObjectID,
			 L"OnEnableCommit");

	SQL_EXEC(m_sSQL);


	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnSetComplete(
                LONGLONG perfCount,
                MTS_OBJID ObjectID
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ObjectEvents (tick, ObjectId, event) \
				values (%d,  %d, '%s')",
			 TickCount, 
			 ObjectID,
			 L"OnSetComplete");

	SQL_EXEC(m_sSQL);


	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnResourceCreate(
                LONGLONG perfCount,
				LPCOLESTR guidActivity, 
                MTS_OBJID ObjectID,
                LPCOLESTR pszType,
                MTS_RESID resId
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);

	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ResourceEvents (tick, ActivityGuid, ObjectID, type, resid, event) \
				values (%d, '%s', %d, '%s', %d, '%s')",
			 TickCount, 
			 guidActivity,
			 ObjectID,
			 pszType,
			 resId,			
			 L"OnResourceCreate");

	SQL_EXEC(m_sSQL);

	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnResourceAllocate(
                LONGLONG perfCount,
				LPCOLESTR guidActivity, 
                MTS_OBJID ObjectID,
                LPCOLESTR pszType,
                MTS_RESID resId
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ResourceEvents (tick, ActivityGuid, ObjectID, type, resid, event) \
				values (%d, '%s', %d, '%s', %d, '%s')",
			 guidActivity,
			 TickCount, 
			 ObjectID,
			 pszType,
			 resId,			
			 L"OnResourceAllocate");

	SQL_EXEC(m_sSQL);

	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnResourceRecycle(
                LONGLONG perfCount,
                MTS_OBJID ObjectID,
                LPCOLESTR pszType,
                MTS_RESID resId
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	
	wsprintf(m_sSQL, 
			 L"insert into ResourceEvents (tick, ObjectID, type, resid, event) \
				values (%d, %d, '%s', %d, '%s')",
			 TickCount, 
			 ObjectID,
			 pszType,
			 resId,			
			 L"OnResourceRecycle");

	SQL_EXEC(m_sSQL);

	return S_OK;
}

STDMETHODIMP CMtsSqlAudit::OnResourceDestroy(
                LONGLONG perfCount,
                MTS_OBJID ObjectID,
                LPCOLESTR pszType,
                MTS_RESID resId
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into ResourceEvents (tick, ObjectID, type, resid, event) \
				values (%d, %d, '%s', %d, '%s')",
			 TickCount, 
			 ObjectID,
			 pszType,
			 resId,			
			 L"OnResourceDestroy");

	SQL_EXEC(m_sSQL);

	return S_OK;
}
STDMETHODIMP CMtsSqlAudit::OnAuthenticate(
		          LONGLONG perfCount, 
				  LPCOLESTR guidActivity, 
				  LPCOLESTR sOriginalUser,
				  LPCOLESTR sDirectUser, 
				  BOOL bCurrentUserInpersonatingInProc
            )
{
    long TickCount = 0;
    if (m_PerformanceFrequency != 0)
        TickCount = (long)((1000 * perfCount) / m_PerformanceFrequency);

	
	ZeroMemory(m_sSQL, SQL_BUF_SIZE * sizeof(WCHAR));
	wsprintf(m_sSQL, 
			 L"insert into Authenticate values (%d, '%s', '%s', '%s', %d)",
			 TickCount, 
			 guidActivity, 
			 sOriginalUser,
			 sDirectUser, 
			 bCurrentUserInpersonatingInProc);

	SQL_EXEC(m_sSQL);
	return S_OK;
}