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

LPTSTR sTables[] = {
_T("Authenticate"),
_T("MethodEvents"), 
_T("ObjectEvents"), 
_T("PackageEvents"),
_T("ResourceEvents"),
_T("ThreadEvents"),
_T("TransactionEvents")
};

LPTSTR sCreateTable = 
_T("CREATE TABLE dbo.%s (					\
	ctr int IDENTITY (1, 1) NOT NULL ,		\
	tick int NOT NULL ,						\
	guidActivity varchar (40) NOT NULL ,	\
	OriginalUser varchar (255) NULL ,		\
	DirectUser varchar (255) NULL ,			\
	fImpersonation int NOT NULL				\
)");



STDMETHODIMP CMtsSqlAudit::Init(LPCOLESTR sDSN, LPCOLESTR sUser, LPCOLESTR sPw)
{
	CComBSTR msg;
	RETCODE rc;

	if (m_henv || m_hstmt || m_hdbc)
		return E_UNEXPECTED; //did you call Init() twice?
	
	rc = SQLAllocEnv( &m_henv );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
    {
        msg = L"CSqlLogObj::SetupEnv() - SQLAllocEnv failed!\n";
		goto Exit;
    }
    

    /* Allocate the Connection handle */
    rc = SQLAllocConnect( m_henv, &m_hdbc );
   
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
        msg = L"CSqlLogObj::SetupEnv() - SQLAllocConnect failed!\n";
		goto Exit;		
    }
    

	SQLSetConnectOption(m_hdbc, SQL_LOGIN_TIMEOUT, 5);
    
    rc = SQLConnect( m_hdbc, (SQLWCHAR *)sDSN,  SQL_NTS, 
							 (SQLWCHAR *)sUser, SQL_NTS,
							 (SQLWCHAR *)sPw,   SQL_NTS );

    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
        msg = L"CSqlLogObj::SetupEnv() - SQLConnect failed!\n";
		goto Exit;
    }

	
    /* Allocate the statement handle */
    rc = SQLAllocStmt( m_hdbc, &m_hstmt);
	if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
        msg = L"CSqlLogObj::SetupEnv() - SQLConnect failed!\n";
		goto Exit;
    }
	//
	//	verify the table existence
	//
	{
		BOOL bOk = TRUE;
		TCHAR sSQL[1024];
		for (int i=0; i<sizeof(sTables)/sizeof(sTables[0]); i++)
		{
			ZeroMemory(sSQL, 1024 * sizeof(TCHAR));
			wsprintf(sSQL, sCreateTable, sTables[i]);
			rc = SQLExecDirect(m_hstmt, sSQL, lstrlen(sSQL));
			if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
			{
				//
				// this means the db isn't set up
				//

				ZeroMemory(sSQL, 1024 * sizeof(TCHAR));
				wsprintf(sSQL, _T("drop table %s"), sTables[i]);
				rc = SQLExecDirect(m_hstmt, sSQL, lstrlen(sSQL));
				msg = L"Database not setup correctly";
				bOk = FALSE;
				break;
			}

		}

		if (bOk) rc = 0;
	}
	
	

Exit:
	if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
		
		ATLTRACE(msg);
		ATLTRACE(_T("\n"));
		
		if (m_hstmt)
		{
			SQLFreeStmt( m_hstmt, SQL_DROP );    
		}

		if (m_hdbc)
		{
		   rc = SQLDisconnect( m_hdbc);
		   SQLFreeConnect( m_hdbc);
		   if (m_henv)
			 SQLFreeEnv( m_henv );
		}

		m_hdbc = m_hstmt  = m_henv = NULL;
		
		return E_FAIL;
	}

	return S_OK;
}


void CMtsSqlAudit::GetError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR *msg)
{
		WCHAR szSqlState[64];
		SDWORD NativeError;
		WCHAR szErr[512];
		SWORD cbErrorMsg;
		SQLError(henv, hdbc, hstmt, szSqlState, &NativeError, szErr, 511, &cbErrorMsg);
		*msg = SysAllocString(szErr);
}
