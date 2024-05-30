
/******************************************************************************\
********************************************************************************
* Filename: CpyImageObj.cpp
*
* Description: Implementation of CCpyImageObj
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/
#include "stdafx.h"
#include "..\..\..\common\inc\CpyImage.h"




#ifndef DBNTWIN32
#define DBNTWIN32

#include <SQL.h>
#include <SQLEXT.h>
#include <ODBCINST.h>
#include "mtx.h"
#include "CpyImageObj.h"

#endif /* DBNTWIN32 */


#include "..\..\..\common\inc\txfiledisp.h"
#include "..\..\..\common\inc\txfiledisp_i.c"
#include "..\..\..\common\inc\mtsusereventobj.h"
#include "..\..\..\common\inc\mtsusereventobj_i.c"



/////////////////////////////////////////////////////////////////////////////
// CCpyImageObj
void GetError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR * msg);

STDMETHODIMP CCpyImageObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICpyImage,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
//
//	Inserts data into the database, and copies a file to the specified directory
//
//	NOTE:  this is designed as a sample application and as such does not call 
//			SetComplete or SetAbort until the client application calls another method
//
//	the [out] parameter is here so that the client can display a message box on an error
//	in order to propagate the message to the client, the function returns S_FALSE for all
//	errors
//
STDMETHODIMP CCpyImageObj::InsertData(BSTR sFromFile, BSTR sToFile, 
						   BSTR sDescription, BSTR sMainColor, 
						   BSTR sTheme, BSTR * msg)
{



	RETCODE                  rc = 0;
    RETCODE                  rc1 = 0;
    HENV                     henv = NULL;
    HDBC                     hdbc = NULL;
    HSTMT                    hstmt = NULL;

	long hPxyCon = 0;
    TCHAR sSQL[2048];;
	
	HRESULT hr;
	
	if (m_pEvents)
	{

		CComBSTR sEvent = L"Source: ";
		sEvent += sFromFile;
		sEvent += L" Destination: ";
		sEvent += sToFile;

		MtsTrace(sEvent);
		IMtsUserEventData * pData = NULL;
		CoCreateInstance(CLSID_MtsUserEventData, NULL, CLSCTX_ALL, IID_IMtsUserEventData, (void **)&pData);
		_ASSERTE(pData);
		pData->put_DisplayName(CComBSTR("CopyImage::InsertData"));
		CComVariant v;
		v = sFromFile;
		pData -> put_Value(CComBSTR("From File"), &v);

		v = sToFile;
		pData -> put_Value(CComBSTR("To File"), &v);

		v = sDescription;
		pData -> put_Value(CComBSTR("Description"), &v);

		v = sMainColor;
		pData -> put_Value(CComBSTR("Main Color"), &v);

		v = sTheme;
		pData -> put_Value(CComBSTR("Theme"), &v);
		v = (IUnknown *) pData;

		m_pEvents -> PostEvent(&v);
		pData -> Release();
		MtsTraceObject(L"CopyFile Event", sEvent);	
		
	}		
	


// create the Proxy
   	IFileRmPxy * pPxy = NULL;

	hr = CoCreateInstance(CLSID_FileRmPxy, NULL, CLSCTX_ALL, IID_IFileRmPxy, (void **)&pPxy);
	if (FAILED(hr))
	{
	        *msg = ::SysAllocString(L"Failed to create the CopyFileRm Resource Dispenser!\r\nMake sure that txfiledisp.dll is properly registered.");
			goto Exit;
	}

	
    /* Allocate the Environment handle */
    rc = SQLAllocEnv( &henv );
    if( rc )
    {
        *msg = ::SysAllocString(L"SQLAllocEnv failed!");
        goto Exit;
    }
    

    /* Allocate the Connection handle */
    rc = SQLAllocConnect( henv, &hdbc );
    if( rc )
    {
        
        *msg = ::SysAllocString(L"SQLAllocConnect failed!");
		goto Exit;
    }
    

	SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 5);

    /* Establish the database connection */
    rc = SQLConnect( hdbc, L"MTXSamples", SQL_NTS, 
							L"sa", SQL_NTS,
							L"", SQL_NTS );

    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     	*msg = ::SysAllocString(L"SQLConnect() failed.\r\nMake sure that the ODBC DSN 'MTXSamples' is created, and\r\nthat sa has a NULL password (or change the source code)");
        goto Exit;
    }

	
    /* Allocate the statement handle */
    rc = SQLAllocStmt( hdbc, &hstmt );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
        GetError( henv, hdbc, hstmt, msg);
        goto Exit;
    }


// done connecting to SQL Server, now Connect to the FileRm
	
	hr = pPxy -> Connect(&hPxyCon);
	_ASSERTE(hr == S_OK);
	

// SQL Do Work
     wsprintf(sSQL, L"insert into image values ('%s', '%s', '%s', '%s')", 
				sDescription, sMainColor, sTheme, sToFile);

	//
	//	insert the row into the database
	//
	//	NOTE: due to SQL server page locking, this will block all subsequent calls (until it returns)
	//		  it would be fairly easy to work around this, but I haven't done if for the demo.
	//

    rc = SQLExecDirect( hstmt, sSQL, SQL_NTS );	
	
	
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
		//GetError( henv, hdbc, hstmt, msg);
		BOOL bRet = CreateTable(hstmt, msg);
		if (!bRet)
			goto Exit;
		else
		{
			// insert the row into the database
		    rc = SQLExecDirect( hstmt, sSQL, SQL_NTS );	
			if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
			{
				GetError( henv, hdbc, hstmt, msg);
				goto Exit;
			}
		}
	}

	
// FileRM DoWork
	
	hr = pPxy -> CopyFileTx(hPxyCon, sFromFile, sToFile, FALSE);
	
	if (FAILED(hr))
	{
		*msg = ::SysAllocString(L"CopyFileTx Failed\r\nMake sure that your destination directory exists\r\nand that CPYIMAGE.DLL is installed in a package and\r\nmarked as Requires Transaction");
		goto Exit;
	}
   

// SQL Free Resources

    /* Free the statement handle */
    rc = SQLFreeStmt( hstmt, SQL_DROP );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
		GetError( henv, hdbc, hstmt, msg);        		
    }

    Exit:

// FileRm Free Resources
	HRESULT hrExit; // we don't want to touch the HRESULT obove the Exit: identifier
	if (pPxy)
	{
		if (hPxyCon) // if we have a connection
		{
			hrExit = pPxy -> Disconnect(hPxyCon);
			_ASSERTE(hrExit == S_OK);
		}

	    pPxy -> Release();
	}

    if (hdbc)
	{
	   rc1 = SQLDisconnect( hdbc );
	   SQLFreeConnect( hdbc );
       SQLFreeEnv( henv );

	}

    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO ) // ODBC error
		 hr = S_FALSE;

	if (FAILED(hr))
		hr = S_FALSE;

	return hr;
}

void GetError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR *msg)
{
		WCHAR szSqlState[64];
		SDWORD NativeError;
		WCHAR szErr[512];
		SWORD cbErrorMsg;
		SQLError(henv, hdbc, hstmt, szSqlState, &NativeError, szErr, 511, &cbErrorMsg);
		*msg = SysAllocString(szErr);
}


STDMETHODIMP CCpyImageObj::SetComplete()
{
	HRESULT hr = S_OK;
	IObjectContext * pInstanceContext;
	HRESULT hRes = GetObjectContext (&pInstanceContext);
	_ASSERTE(hr==S_OK);

	if (pInstanceContext)
	{
		pInstanceContext -> SetComplete();	    
		pInstanceContext -> Release();
	}

	return hr;
}
STDMETHODIMP CCpyImageObj::SetAbort()
{
	HRESULT hr = S_OK;
	IObjectContext * pInstanceContext;
	HRESULT hRes = GetObjectContext (&pInstanceContext);
	_ASSERTE(hr==S_OK);

	if (pInstanceContext)
	{
		pInstanceContext -> SetAbort();
		pInstanceContext -> Release();
	}
	return hr;
}

STDMETHODIMP CCpyImageObj::Test(BSTR * msg)
{
	*msg = ::SysAllocString(L"This is only a test!");
	return S_FALSE;


}
//
//	Post a message to the MTS Spy message Q
//
void CCpyImageObj::MtsTrace(BSTR sMsg)
{

	CComVariant var = sMsg;
	m_pEvents -> PostEvent(&var);
}

void CCpyImageObj::MtsTraceObject(BSTR sDisplayName, BSTR sVal)
{
	
}

BOOL CCpyImageObj::CreateTable(HSTMT hstmt, BSTR * msg)
{

	RETCODE rc;
	LPTSTR sSQL = _T("CREATE TABLE dbo.Image (ctr int IDENTITY (1, 1) NOT NULL,Description varchar (255) NULL , MainColor varchar (255) NULL ,Theme varchar (255) NULL ,FileName varchar (120) NOT NULL)");
	rc = SQLExecDirect( hstmt, sSQL, SQL_NTS );	
	if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
		*msg = ::SysAllocString(L"Failed to create the Image table.");
		return FALSE;
	}
	return TRUE;
}
