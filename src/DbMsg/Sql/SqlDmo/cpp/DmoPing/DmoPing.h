// ************************************************************************ //
// dmoping.h
// ************************************************************************ //
#ifndef _DMOPING_H_
#define _DMOPING_H_

#define	STRICT
#define WIN32_LEAN_AND_MEAN
#define INC_OLE2
#define UNICODE
#define _UNICODE

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <initguid.h>

// SQL Server 6.x SQLOLE
#include <sqloleid.h>		
#include <sqlole.h>

// SQL Server 7.0 SQLDMO
#include <sqldmoid.h>
#include <sqldmo.h>

class CDmoPing
{
public:
	CDmoPing();
	~CDmoPing();

	BOOL			Parse(INT argc, TCHAR* argv[]);
	BOOL			GetVersion();
	BOOL			Ping();
	SQLDMO_SQL_VER	GetSQLVersion() {return m_eSQLVersion;}

private:			// member variables
	LPTSTR			m_pServer;
	LPTSTR			m_pUser;
	LPTSTR			m_pPassword;
	BOOL			m_bIntegratedSec;
	BOOL			m_bVerbose;
	SQLDMO_SQL_VER	m_eSQLVersion;
};

extern "C" INT	_tmain(INT argc, TCHAR** argv, TCHAR** envp);
VOID DisplayError();
BOOL IsArgDelimiter(LPTSTR lpArg);
BOOL GetArg(INT& i, LPTSTR& lpValue, INT argc, TCHAR* argv[]);

#endif // _DMOPING_H_