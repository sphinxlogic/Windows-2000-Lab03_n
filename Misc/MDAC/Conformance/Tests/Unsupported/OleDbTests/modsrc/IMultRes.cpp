//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright 1995-1998 Microsoft Corporation.
//
// @doc 
//
// @module multres.cpp | Source file for all IMultipleResults.
//
//--------------------------------------------------------------------

#include "modstandard.hpp"
#include "imultres.h"
#include "ExtraLib.h"

// Define our static data members
IMalloc *	CMultResults::s_pIMalloc = NULL;		// Task memory allocator
DBORDINAL *	CMultResults::s_rgParamOrdinals = NULL;	// Array of parameter ordinals 
BOOL		g_fKagera=FALSE;
BOOL		g_fSQLOLEDB=FALSE;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Module Values
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// {{ TCW_MODULE_GLOBALS
DECLARE_MODULE_CLSID = { 0x27e72d20, 0x128b, 0x11d0, { 0xba, 0x46, 0x00, 0xa0, 0xc9, 0x0d, 0x80, 0x78 }};
DECLARE_MODULE_NAME("IMultipleResults");
DECLARE_MODULE_OWNER("Microsoft");
DECLARE_MODULE_DESCRIP("Test Module for IMultipleResults");
DECLARE_MODULE_VERSION(795921705);
// TCW_WizardVersion(2)
// TCW_Automation(True)
// }} TCW_MODULE_GLOBALS_END


//--------------------------------------------------------------------
// @func Module level initialization routine
//
// @rdesc Success or Failure
// 		@flag  TRUE  | Successful initialization
//		@flag  FALSE | Initialization problems
//
BOOL ModuleInit(CThisTestModule * pThisTestModule)
{
	BOOL				fResults = FALSE;	
	ULONG				ulValue;
	ULONG				i;
	LPWSTR				wszProviderName=NULL;
	IDBCreateCommand *	pIDBCreateCommand=NULL;
	ICommandText *		pICommandText=NULL;
	IMultipleResults *	pIMultipleResults=NULL;
	WCHAR * 			pwszSQLText=NULL;

	// Initialize our static members in CMultResults.  These
	// can now be used everywhere in this file
	if (FAILED(CoGetMalloc(1, &CMultResults::s_pIMalloc)))
		return FALSE;	
	
	CMultResults::s_rgParamOrdinals = 
		(DBORDINAL *)CMultResults::s_pIMalloc->Alloc(MAX_PARAM_NUM * sizeof(LONG));

	if (!CMultResults::s_rgParamOrdinals)
		goto CLEANUP;

	// For the elements of the array, put 
	// consecutive ordinals, beginning with 1
	for (i=0; i<MAX_PARAM_NUM; i++)
		CMultResults::s_rgParamOrdinals[i] = i+1;

	// Make sure we support IMultipleResults or stop immediately
	if (ModuleCreateDBSession(pThisTestModule))
	{
		if (!((GetProperty(DBPROP_MULTIPLERESULTS, DBPROPSET_DATASOURCEINFO, pThisTestModule->m_pIUnknown, &ulValue)) &&
			(ulValue != DBPROPVAL_MR_NOTSUPPORTED)))
		{
			CTable CTestTable((IUnknown *)pThisTestModule->m_pIUnknown2,(LPWSTR)gwszModuleName);

			odtLog<<L"IMultipleResults not supported by the Provider."<<ENDL;

			fResults = TEST_SKIPPED;

			// If the property claims no support then try to get the interface.  We'd better get E_NOINTERFACE.
			// We have to have commands in order to do this
			if (!VerifyInterface(pThisTestModule->m_pIUnknown2, IID_IDBCreateCommand,SESSION_INTERFACE,
				(IUnknown **)&pIDBCreateCommand))
				goto CLEANUP;

			// Unfortunately we need a table to try this also
			if (FAILED(CTestTable.CreateTable(0)))
			{
				fResults=FALSE;
				goto CLEANUP;
			}

			if (SUCCEEDED(pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText,(IUnknown **)&pICommandText)))
			{
				CTestTable.CreateSQLStmt(SELECT_ALLFROMTBL,NULL,
														&pwszSQLText,NULL,NULL);
				if (CHECK(pICommandText->SetCommandText(DBGUID_DBSQL, pwszSQLText), S_OK) &&
					!CHECK(pICommandText->Execute(NULL, IID_IMultipleResults, NULL, NULL,
					(IUnknown **)&pIMultipleResults),E_NOINTERFACE))
					fResults=FALSE;
			}

			CTestTable.DropTable();
			PROVIDER_FREE(pwszSQLText);

			goto CLEANUP;
		}

		g_fKagera=FALSE;
		g_fSQLOLEDB=FALSE;
		if (GetProperty(DBPROP_PROVIDERNAME, DBPROPSET_DATASOURCEINFO, pThisTestModule->m_pIUnknown, &wszProviderName)
			&& wszProviderName)
		{
			if (!wcscmp((LPWSTR)wszProviderName, L"MSDASQL.DLL"))
				g_fKagera=TRUE;
			if (!wcscmp((LPWSTR)wszProviderName, L"sqloledb.dll"))
				g_fSQLOLEDB=TRUE;
		}


		PROVIDER_FREE(wszProviderName);
		
		fResults=TRUE;
	}
	
CLEANUP:

	SAFE_RELEASE(pICommandText);
	SAFE_RELEASE(pIMultipleResults);
	SAFE_RELEASE(pIDBCreateCommand);

	return fResults;
}	
  
//--------------------------------------------------------------------
// @func Module level termination routine
//
// @rdesc Success or Failure
// 		@flag  TRUE  | Successful initialization
//		@flag  FALSE | Initialization problems
//
BOOL ModuleTerminate(CThisTestModule * pThisTestModule)
{
	// Release our static data members
	if (CMultResults::s_pIMalloc)
	{
		if (CMultResults::s_rgParamOrdinals)
			CMultResults::s_pIMalloc->Free(CMultResults::s_rgParamOrdinals);

		CMultResults::s_pIMalloc->Release();
		CMultResults::s_pIMalloc = NULL;
	}

	if (ModuleReleaseDBSession(pThisTestModule))
		return TRUE;
	else
		return FALSE;
}	

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Helper functions
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
BOOL IsServerCursorProperty(DBPROPID dwPropID)
{
	switch(dwPropID)
	{
		case DBPROP_IRowsetChange:
		case DBPROP_IRowsetFind:
		case DBPROP_IRowsetLocate:
		case DBPROP_IRowsetResynch:
		case DBPROP_IRowsetUpdate:
		case DBPROP_IRowsetScroll:
			return TRUE;
			break;
		default:
			return FALSE;
	}
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Base class declarations
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


//////////////////////////////////////////////////////////////////
// CTestBase
//////////////////////////////////////////////////////////////////

// CTestBase::Init --------------------------------------------
//
// Initialization
//        
//
BOOL CTestBase::Init()
{
	BOOL	fResults = FALSE;
	ULONG	i;
	
	m_pSelectTable = NULL;
	m_pChangeTable = NULL;
	
	///////////////////////////////////////////////////////////////
	//Get a command object and set our ICommandText pointer to it.
	//Note that we create the DBSession in ModuleInit, and here call 
	//IDBCreateCommand explicitly (rather than CreateCommandObject)
	//so we don't force a CreateTable call in CreateCommandObject,
	//since we won't use the CTable in that object.
	///////////////////////////////////////////////////////////////
	SetDBSession((IDBCreateCommand *)m_pThisTestModule->m_pIUnknown2);

	//Make sure that setting the session yielded us an IDBCreateCommand,
	//otherwise commands aren't supported and we can't go on
	if (m_pIDBCreateCommand)
	{
		if (CHECK(m_pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText,
			(IUnknown **)&m_pICommandText), S_OK))
				fResults = TRUE;
	}
	else
	{
		odtLog << L"Commands not supported, testcase will not be executed.\n";
		goto END;
	}

	// Hack for Kagera.  We have to force the insert to use commands otherwise we
	// end up getting into QBU mode which can't insert BLOB columns.
	GetModInfo()->SetInsert(INSERT_COMMAND);

	//////////////////////////////////////////////////////	
	//Create tables to be used by all objects in our vars
	//We own these and must delete them in Terminate
	//////////////////////////////////////////////////////
	m_pChangeTable = new CTable(m_pIDBCreateCommand,(LPWSTR)gwszModuleName, NONULLS);
	if (!m_pChangeTable)
		goto END;

	m_pSelectTable = new CTable(m_pIDBCreateCommand,(LPWSTR)gwszModuleName, NONULLS);
	if (!m_pSelectTable)
		goto END;

	// Create the table with index so we can obtain support IRowsetLocate on Sql server
	if(m_pSelectTable->CreateTable(0) != S_OK)
		goto END;

	// Create the table with no index so we can insert duplicate rows
	if(m_pChangeTable->CreateTable(0, 0) != S_OK)
		goto END;

	//Put in all rows based on seed ROW_SEED for our select table	
	for (i=0; i<SELECT_ROW_NUM; i++)
	{
		if (!CHECK(m_pSelectTable->Insert(ROW_SEED+i), S_OK))
			goto END;	
	}

	// Note: MakeData creates different data for an index column than 
	// for a non-index column.  Since we need the data to match between
	// the tables we'll find out what the index column of the first
	// table is and lie to CTable by telling it we have an index on the
	// second table that matches.  Therefore it will make identical data.
	m_pChangeTable->SetIndexColumn(m_pSelectTable->GetIndexColumn());

	//Put in all rows based on seed ROW_SEED for our Change table
	//NOTE:  m_cRowsInSelectTable is assigned to CHANGE_ROW_NUM
	//in our constructor, so if this code is changed, change
	//m_cRowsInSelectTable accordingly.  We need to assign
	//the value in the CTOR so it is available to the
	//derived class's FInit before it defers to this base class FInit.
	for (i=0; i<CHANGE_ROW_NUM; i++)
	{
		// Force insert 
		if (!CHECK(m_pChangeTable->Insert(ROW_SEED), S_OK))
			goto END;	
	}
	

	//This is a total hack to force SQL Server into firehose mode,
	//the only mode in which batched statements are allowed.  We
	//must make sure there is only one command active per session,
	//so we will keep the command passed to our constructor, but
	//release the ones associated with our CTable objects.  Note
	//this will totally disable command functionality on the CTable
	//objects we have, so we must always do the command functionality
	//ourselves.
	if (m_pChangeTable->m_pICommand)
	{
		m_pChangeTable->m_pICommand->Release();
		m_pChangeTable->m_pICommand = NULL;
	}
	if (m_pSelectTable->m_pICommand)
	{
		m_pSelectTable->m_pICommand->Release();
		m_pSelectTable->m_pICommand = NULL;
	}

END:

	if (fResults)
		return TRUE;
	else	
		return FALSE;
}

// CTestBase::SetRowsetPropertyDefault ------------------------------------
//
// Sets the given rowset property using ICommandProperties to the default value
//
//
HRESULT CTestBase::SetRowsetPropertyDefault(DBPROPID DBPropID)
{
	ICommandProperties * pICmdProps = NULL;
	DBPROPSET	DBPropSet;
	DBPROP		DBProp;

	ASSERT(m_pICommandText);

	m_hr = E_FAIL;

	//Set up the rowset property structure to use the ID passed in
	DBPropSet.rgProperties = &DBProp;
	DBPropSet.cProperties = 1;
	DBPropSet.guidPropertySet = DBPROPSET_ROWSET;

	DBProp.dwPropertyID = DBPropID;
	DBProp.dwOptions = DBPROPOPTIONS_OPTIONAL;
	DBProp.colid = DB_NULLID;
	DBProp.vValue.vt = VT_EMPTY;	//Causes default to be set
	
	
	if (CHECK(m_hr = m_pICommandText->QueryInterface(IID_ICommandProperties, 
		(void **)&pICmdProps), S_OK))
	{
		
		m_hr = pICmdProps->SetProperties(1, &DBPropSet);
		if (SUCCEEDED(m_hr))
			//Check that it went OK.  We won't increment error count if it 
			//fails since it may just not be supported, in which case we
			//return FALSE
			if (DBProp.dwStatus != DBPROPSTATUS_OK)
				m_hr = E_FAIL;
			
		pICmdProps->Release();
	}
	
	return m_hr;
}


// CTestBase::SetRowsetPropertyOn ------------------------------------
//
// Sets the given rowset property using ICommandProperties to VARIANT_TRUE
//
//
HRESULT CTestBase::SetRowsetPropertyOn(DBPROPID DBPropID)
{
	ICommandProperties * pICmdProps = NULL;
	DBPROPSET	DBPropSet;
	DBPROP		DBProp;

	ASSERT(m_pICommandText);

	m_hr = E_FAIL;

	//Set up the rowset property structure to use the ID passed in
	DBPropSet.rgProperties = &DBProp;
	DBPropSet.cProperties = 1;
	DBPropSet.guidPropertySet = DBPROPSET_ROWSET;

	DBProp.dwPropertyID = DBPropID;
	DBProp.dwOptions = DBPROPOPTIONS_REQUIRED;
	DBProp.colid = DB_NULLID;
	DBProp.dwStatus = DBPROPSTATUS_OK;
	DBProp.vValue.vt = VT_BOOL;
	V_BOOL(&(DBProp.vValue)) = VARIANT_TRUE;	//Turn property on

	if (CHECK(m_hr = m_pICommandText->QueryInterface(IID_ICommandProperties, 
		(void **)&pICmdProps), S_OK))
	{
	
		m_hr = pICmdProps->SetProperties(1, &DBPropSet);
		if (SUCCEEDED(m_hr))
			//Check that it went OK.  We won't increment error count if it 
			//fails since it may just not be supported, in which case we
			//return FALSE
			if (DBProp.dwStatus == DBPROPSTATUS_OK)
				m_hr = NOERROR;
		
		pICmdProps->Release();
	}
	
	return m_hr;
}


// CTestBase::TryLocate ------------------------------------
//
//Uses IRowsetLocate to ensure it is functional on this rowset
//
//
HRESULT CTestBase::TryLocate(IRowsetLocate * pIRowLoc)
{
	
	DBBOOKMARK	Bkmk = DBBMK_FIRST;
	ULONG		cRowsObtained = 0;
	HROW		hRow1 = DB_NULL_HROW;
	HROW *		phRow1 = &hRow1;
	HROW		hRow2 = DB_NULL_HROW;
	HROW *		phRow2 = &hRow2;
	DBBINDING * rgBindings = NULL;
	ULONG		cBindings = 0;
	ULONG		cbRowSize = 0;
	HACCESSOR	hAccessor = DB_NULL_HACCESSOR;
	IAccessor * pIAccessor = NULL;
	BYTE *		pData1 = NULL;
	BYTE *		pData2 = NULL;

	m_hr = NOERROR;	

	if (!CHECK(m_hr = pIRowLoc->QueryInterface(IID_IAccessor, 
												(void **)&pIAccessor), 
												S_OK))
		goto CLEANUP;

	//Create an accessor
	if (S_OK != (m_hr = GetAccessorAndBindings(pIRowLoc, 
												DBACCESSOR_ROWDATA,
												&hAccessor, 
												&rgBindings, 
												&cBindings, 
												&cbRowSize)))
		goto CLEANUP;

	//Allocate a new data buffers
	pData1 = (BYTE *)CMultResults::s_pIMalloc->Alloc(cbRowSize);
	if (!pData1)			
	{
		m_hr = ResultFromScode(E_OUTOFMEMORY);
		goto CLEANUP;
	}
	
	pData2 = (BYTE *)CMultResults::s_pIMalloc->Alloc(cbRowSize);
	if (!pData2)			
	{
		m_hr = ResultFromScode(E_OUTOFMEMORY);
		goto CLEANUP;
	}
	
	memset(pData1, 0, cbRowSize);
	memset(pData2, 0, cbRowSize);
	////////////////////////////////////////////////
	//Get first row with GetNextRows for comparison
	////////////////////////////////////////////////

	if (!CHECK(m_hr = pIRowLoc->GetNextRows(NULL, 
											0, 
											1, 
											&cRowsObtained, 
											&phRow1), 
											S_OK))	
		goto CLEANUP;		
	
	
	if (!CHECK(m_hr = pIRowLoc->GetData(hRow1, 
										hAccessor, 
										pData1), 
										S_OK))
		goto CLEANUP;

	CHECK(pIRowLoc->ReleaseRows(1, 
								&hRow1, 
								NULL, 
								NULL, 
								NULL), 
								S_OK);
	hRow1 = DB_NULL_HROW;

	////////////////////////////////////////////////
	//Now get the same row with GetRowsAt	
	////////////////////////////////////////////////

	if (!CHECK(m_hr = pIRowLoc->GetRowsAt(0,
											0, 
											sizeof(DBBOOKMARK), 
											(BYTE *)&Bkmk, 
											0, 
											1,
											&cRowsObtained, 
											&phRow2), 
											S_OK))
		goto CLEANUP;

	if (!CHECK(m_hr = pIRowLoc->GetData(hRow2, 
										hAccessor, 
										pData2), 
										S_OK))
		goto CLEANUP;

	CHECK(pIRowLoc->ReleaseRows(1, 
								&hRow2, 
								NULL, 
								NULL, 
								NULL), 
								S_OK);
	hRow2 = DB_NULL_HROW;

	////////////////////////////////////////////////
	// Compare the two, should be the same row
	////////////////////////////////////////////////
	if (!COMPARE(memcmp(pData1, pData2, cbRowSize), 0)) 
		m_hr = E_FAIL;
	
CLEANUP:

	if (pIAccessor)
	{
		pIAccessor->ReleaseAccessor(hAccessor, NULL);
		pIAccessor->Release();
	}

	if (rgBindings)	
		CMultResults::s_pIMalloc->Free(rgBindings);
		

	if (pData1)	
		CMultResults::s_pIMalloc->Free(pData1);

	if (pData2)	
		CMultResults::s_pIMalloc->Free(pData2);

	if (hRow1 != DB_NULL_HROW)
		pIRowLoc->ReleaseRows(1, 
							&hRow1, 
							NULL, 
							NULL, 
							NULL);

	if (hRow2 != DB_NULL_HROW)
		pIRowLoc->ReleaseRows(1, 
							&hRow2, 
							NULL, 
							NULL, 
							NULL);


	return m_hr;	

}


// CTestBase::TryHoldRows ------------------------------------
//
// Ensures CANHOLDROWS works on this rowset
//
//
HRESULT CTestBase::TryHoldRows(IRowset * pIRowset)
{	
	ULONG		cRowsObtained = 0;
	HROW		hRow1 = DB_NULL_HROW;
	HROW *		phRow1 = &hRow1;
	HROW		hRow2 = DB_NULL_HROW;
	HROW *		phRow2 = &hRow2;
	DBBINDING * rgBindings = NULL;
	ULONG		cBindings = 0;
	ULONG		cbRowSize = 0;
	HACCESSOR	hAccessor = DB_NULL_HACCESSOR;
	IAccessor * pIAccessor = NULL;
	BYTE *		pData1 = NULL;
	BYTE *		pData2 = NULL;

	m_hr = NOERROR;	

	if (!CHECK(m_hr = pIRowset->QueryInterface(IID_IAccessor, 
												(void **)&pIAccessor), 
												S_OK))
		goto CLEANUP;

	//Create an accessor
	if (S_OK != (m_hr = GetAccessorAndBindings(pIRowset, 
												DBACCESSOR_ROWDATA,
												&hAccessor, 
												&rgBindings, 
												&cBindings, 
												&cbRowSize)))
		goto CLEANUP;

	//Allocate a new data buffers
	pData1 = (BYTE *)CMultResults::s_pIMalloc->Alloc(cbRowSize);
	if (!pData1)			
	{
		m_hr = ResultFromScode(E_OUTOFMEMORY);
		goto CLEANUP;
	}
	
	pData2 = (BYTE *)CMultResults::s_pIMalloc->Alloc(cbRowSize);
	if (!pData2)			
	{
		m_hr = ResultFromScode(E_OUTOFMEMORY);
		goto CLEANUP;
	}
	
	memset(pData1, 0, cbRowSize);
	memset(pData2, 0, cbRowSize);
	////////////////////////////////////////////////
	//Get first row with GetNextRows for comparison
	////////////////////////////////////////////////

	if (!CHECK(m_hr = pIRowset->GetNextRows(NULL, 
											0, 
											1, 
											&cRowsObtained, 
											(HROW **)&phRow1), 
											S_OK))	
		goto CLEANUP;		
	
	
	//Hold a row
	if (!CHECK(m_hr = pIRowset->GetData(hRow1, 
										hAccessor, 
										pData1), 
										S_OK))
		goto CLEANUP;

	
	////////////////////////////////////////////////
	//Now get another row, should be no problem
	//even with a held row
	////////////////////////////////////////////////
if (!CHECK(m_hr = pIRowset->GetNextRows(NULL, 
											0, 
											1, 
											&cRowsObtained, 
											(HROW **)&phRow2), 
											S_OK))	
		goto CLEANUP;		
	
	
	if (!CHECK(m_hr = pIRowset->GetData(hRow2, 
										hAccessor,	
										pData2),	
										S_OK))
		goto CLEANUP;
	

	/////////////////////////////////////////////////////////
	// Compare the two, data should be the same for both rows
	/////////////////////////////////////////////////////////
	if (!COMPARE(memcmp(pData1, pData2, cbRowSize), 0)) 
		m_hr = E_FAIL;
	
CLEANUP:

	//Release all rows
	if (hRow1 != DB_NULL_HROW)
		CHECK(pIRowset->ReleaseRows(1, 
									&hRow1, 
									NULL, 
									NULL, 
									NULL), 
									S_OK);
	
	if (hRow2 != DB_NULL_HROW)
		CHECK(pIRowset->ReleaseRows(1, 
									&hRow2, 
									NULL, 
									NULL, 
									NULL), 
									S_OK);	

	if (pIAccessor)
	{
		pIAccessor->ReleaseAccessor(hAccessor, NULL);
		pIAccessor->Release();
	}

	if (rgBindings)	
		CMultResults::s_pIMalloc->Free(rgBindings);
		

	if (pData1)	
		CMultResults::s_pIMalloc->Free(pData1);

	if (pData2)	
		CMultResults::s_pIMalloc->Free(pData2);
	

	return m_hr;	

}


// CTestBase::SetUpGetResult ------------------------------------
//
// Init's (*ppMultResult)->m_pIMultResults so it is ready to call GetResult.  
// User must delete *ppMultResult unless an error is returned.
// If ceSQLStmts is 0, the user does not care what SQL statements are used,
// so this routine uses a fixed on
//
//
HRESULT CTestBase::SetUpGetResult(CMultResults ** ppMultResult,
										   ULONG ceSQLStmts, ESQLSTMT * rgeSQLStmts)
{
	ESQLSTMT 		rgFixedeSQLStmts[] = {																													
									ESELECT,
									EINSERT,
									EDELETE
									};
	ULONG			cFixedeSQLStmts = sizeof(rgFixedeSQLStmts) / sizeof(ESQLSTMT);
	CBatch *		pNewBatch = NULL;
	BOOL			fResults = FALSE;	

	m_hr = E_FAIL;
	
	if (!ppMultResult)
		return E_INVALIDARG;

	//Warn user that they shouldn't be passing valid
	//array if count is 0 -- we'll ignore the array
	if (ceSQLStmts == 0)
		if (rgeSQLStmts)
			return E_INVALIDARG;

	//Init parameter
	*ppMultResult = NULL;

	//If user doesn't specify SQL, use ours
	if (ceSQLStmts == 0)
	{
		ceSQLStmts = cFixedeSQLStmts;
		rgeSQLStmts = rgFixedeSQLStmts;
	}
	
	pNewBatch = new CBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	if (!pNewBatch)
		return E_OUTOFMEMORY;

	//Initialize batch statement with the proper SQL for this variation
	if (!pNewBatch->FInit(ceSQLStmts, rgeSQLStmts))	
		goto CLEANUP;

	//Make sure we start clean
	pNewBatch->m_pIMultResults = NULL;

	//This should put a valid interface in pNewBatch->m_pIMultResults
	m_hr = pNewBatch->SetAndExecute(IID_IMultipleResults);

CLEANUP:
	
	if (SUCCEEDED(m_hr))
	{
		//Return our object to user
		*ppMultResult = pNewBatch;
		
	}
	else 
	{
		if (pNewBatch)
		{			
			delete pNewBatch;
		}		
	}

	return m_hr;
}


// CTestBase::Terminate --------------------------------------------
//
// Cleanup
//        
//
BOOL CTestBase::Terminate()
{
	////////////////////////////////////////////////////
	//Release what we created in Init
	////////////////////////////////////////////////////

	if (m_pChangeTable)
	{
		m_pChangeTable->DropTable();
		delete m_pChangeTable;
		m_pChangeTable = NULL;
	}

	if (m_pSelectTable)
	{
		m_pSelectTable->DropTable();
		delete m_pSelectTable;
		m_pSelectTable = NULL;
	}

	if (m_pICommandText)
	{
		m_pICommandText->Release();
		m_pICommandText = NULL;
	}

	ReleaseDBSession();

	return TRUE;
}


//////////////////////////////////////////////////////////////////
// CMultResults
//////////////////////////////////////////////////////////////////


// CMultResults::CMultResults --------------------------------------------
//
// CTOR
//        
//
CMultResults::CMultResults(IDBCreateCommand * pIDBCreateCommand,
						   ICommandText * pICommandText,
						   CTable * pSelectTable,
						   CTable * pChangeTable)
{		
	//Init everything
	m_pwszNewTableName = NULL;	
	m_pICommandText = NULL;
	m_pIDBCreateCommand = NULL;	
	m_ceSQLStmts = 0;
	m_rgeSQLStmts = NULL;
	m_rgStmtRowsAffected = NULL;	
	m_pIMultResults = NULL;	
	m_pIRowset = NULL;		
	m_cRowsExecuteAffected = 0;
	m_cRowsGetResultAffected = 0;
	m_pwszSQLStmt = NULL;	
	m_rgSelectOrds = NULL;
	m_rgCompOrds = NULL;
	m_cRowsInChgTable = 0;
	m_cTotalResultsExpected = 0;	
	m_hr = NOERROR;
	m_cRowsInSelect = SELECT_ROW_NUM;
	
	//Init our string table to all null elements
	memset(m_rgpwszSQL, 0, sizeof(m_rgpwszSQL));
	
	//Increment ref counts and hold onto pointers	
	m_pICommandText = pICommandText;
	m_pICommandText->AddRef();	
	m_pIDBCreateCommand = pIDBCreateCommand;
	m_pIDBCreateCommand->AddRef(); 
	
	//We don't own these objects, just sharing them,
	//so don't clean them up in DTOR
	m_pSelectTable = pSelectTable;
	m_pChangeTable = pChangeTable;

}


// CMultResults::FInit --------------------------------------------------------
//
// Performs necessary initialization for object -- must always be called 
// immediately after creating object for it to function correctly
//        
//
BOOL CMultResults::FInit(const ULONG cSQLStmts,
						 ESQLSTMT * rgSQLStmts, 
						 LONG * rgStmtRowsAffected)
{
	ULONG	i;

	//Initialize members
	m_ceSQLStmts = cSQLStmts;			
	//Default total results is the number of statements in the batch
	m_cTotalResultsExpected = cSQLStmts;
	
	//////////////////////////////////////////////////////	
	//Copy to our own memory user's SQL stmt arrays
	//////////////////////////////////////////////////////
	
	m_rgeSQLStmts = 
		(ESQLSTMT *)CMultResults::s_pIMalloc->Alloc(cSQLStmts * sizeof(ESQLSTMT));	
	if (!m_rgeSQLStmts)
		goto FAILED;
	
	m_rgStmtRowsAffected = 
		(LONG *)CMultResults::s_pIMalloc->Alloc(cSQLStmts * sizeof(LONG));
	if (!m_rgStmtRowsAffected)
		goto FAILED;

	for (i=0; i<cSQLStmts; i++)
	{
		m_rgeSQLStmts[i] = rgSQLStmts[i];
		m_rgStmtRowsAffected[i] = rgStmtRowsAffected[i];
	}

	
	////////////////////////////////////////////////////
	//Build an array of select rowset ordinals 
	////////////////////////////////////////////////////

	//This memory is freed in DTOR
	m_rgSelectOrds = 
		(LONG *)CMultResults::s_pIMalloc->Alloc(m_pSelectTable->CountColumnsOnTable() * sizeof(LONG));
	m_rgCompOrds = 
		(LONG *)CMultResults::s_pIMalloc->Alloc(m_pSelectTable->CountColumnsOnTable() * sizeof(LONG));
	if (!m_rgSelectOrds || !m_rgCompOrds)
		goto FAILED;

	for (i=0; i< m_pSelectTable->CountColumnsOnTable(); i++)
	{
		//Fill zero based array with one based column ordinals
		m_rgSelectOrds[i] = i+1;
		m_rgCompOrds[i] = i+1;
	}
	/////////////////////////////////////////////////////////////
	//Generate a table name for our Create/Drop table statements
	/////////////////////////////////////////////////////////////

	m_pwszNewTableName = (WCHAR *)CMultResults::s_pIMalloc->Alloc(
			(wcslen(m_pChangeTable->GetTableName()) + 1) * sizeof(WCHAR));
	if (!m_pwszNewTableName)
		goto FAILED;

	//Copy in our base name, taken from Change Table
	wcscpy(m_pwszNewTableName, m_pChangeTable->GetTableName());
	//Now add a suffix to make a new name, copying over last chars of
	//old name so we don't need any additional memory
	ASSERT(wcslen(m_pwszNewTableName) >= wcslen(wszCrtTblSuffix));
	wcscpy(m_pwszNewTableName + wcslen(m_pwszNewTableName) - wcslen(wszCrtTblSuffix),
			wszCrtTblSuffix);


	/////////////////////////////////////////////////////////////
	//Build string table containing all SQL text
	/////////////////////////////////////////////////////////////
	if (!BuildSQLStringTable())
		goto FAILED;


	return TRUE;

FAILED:
	return FALSE;
}


// CMultResults::BuildSQLStringTable --------------------------------------------------------
//
// Builds SQL Strings for all of our operations which have not been
// built already, places them in m_rgpwszSQL.
//        
//
BOOL CMultResults::BuildSQLStringTable()
{

	//////////////////////////////////////////////////////////////////////
	//Note that we created a Change table with all rows having
	//the same value.  Each row we insert using the SQL insert
	//statement below will also insert the same row values.
	//When we update, we look for that same row and update
	//it to the same old values again.  This is done so that
	//we are guaranteed that we will always have enough rows
	//in the table to update given our update clause.  When 
	//we delete, we use row values in the delete clause which
	//do not exist in the table.  This is done for 2 reasons:
	// 1f)  We get more coverage by testing statements that affect
	//     0 rows (the delete) as well as 1 row (the updates and inserts).
	// 2)  When we execute the delete, it doesn't wipe out all rows,
	//     causing the next delete to not affect the same number
	//     of rows as the first delete.
	//////////////////////////////////////////////////////////////////////


	//We are responsible for freeing all these strings in DTOR

	//Set the select string
	if (!m_rgpwszSQL[ESELECT])
		if (FAILED(m_pSelectTable->CreateSQLStmt(
											SELECT_ORDERBYNUMERIC,
											NULL,
											&m_rgpwszSQL[ESELECT],	
											NULL,
											NULL)))
			goto FAILED;
	
	//Set the insert string, always insert same value, based on seed ROW_SEED
	if (!m_rgpwszSQL[EINSERT])
		if (FAILED(m_pChangeTable->Insert(
									ROW_SEED,
									PRIMARY,
									FALSE,	// Don't execute
									&m_rgpwszSQL[EINSERT])))
			goto FAILED;
		

	//Set the update string, always update the value based on seed ROW_SEED,
	//and update it back to the same value
	if (!m_rgpwszSQL[EUPDATE])
		if (FAILED(m_pChangeTable->Update(	
									ROW_SEED,
									PRIMARY,
									FALSE,		//Don't Execute
									&m_rgpwszSQL[EUPDATE],
									TRUE)))		//We want the where clause and set clause to use the same values
			goto FAILED;

	//Set the delete string, always use a row which isn't there so it affects 0 rows
	if (!m_rgpwszSQL[EDELETE])
		if (FAILED(m_pChangeTable->Delete( 
									ROW_SEED+1,
									PRIMARY,	
									FALSE,	//Don't exeucte
									&m_rgpwszSQL[EDELETE])))
		goto FAILED;
		

	//Build and set the Create Table string
	if (!m_rgpwszSQL[ECREATE])
	{
		m_rgpwszSQL[ECREATE] = (WCHAR *)CMultResults::s_pIMalloc->Alloc((wcslen(m_pwszNewTableName) + 
		wcslen(wszCrtTbl) + 1) * sizeof(WCHAR));
	
		if (!m_rgpwszSQL[ECREATE])
			goto FAILED;

		swprintf(m_rgpwszSQL[ECREATE], wszCrtTbl, m_pwszNewTableName); 
	}


	//Build and set the Drop Table string
	if (!m_rgpwszSQL[EDROP])
	{
		m_rgpwszSQL[EDROP] = (WCHAR *)CMultResults::s_pIMalloc->Alloc((wcslen(m_pwszNewTableName) + 
			wcslen(wszDropTbl) + 1) * sizeof(WCHAR));
		if (!m_rgpwszSQL[EDROP])
			goto FAILED;

		swprintf(m_rgpwszSQL[EDROP], wszDropTbl, m_pwszNewTableName); 
	}

	if (!m_rgpwszSQL[EEMPTYSELECT])
		if (FAILED(m_pSelectTable->CreateSQLStmt(
											SELECT_EMPTYROWSET,
											NULL,
											&m_rgpwszSQL[EEMPTYSELECT],	
											NULL,
											NULL)))
			goto FAILED;
	
	// Build the computed sum statement
	if (!m_rgpwszSQL[ECOMPUTESUM])
		if (FAILED(m_pSelectTable->CreateSQLStmt(
											SELECT_COLLISTORDERBYCOLONECOMPUTE,
											NULL,
											&m_rgpwszSQL[ECOMPUTESUM],	
											NULL,
											NULL)))
			goto FAILED;

	return TRUE;

FAILED:

	return FALSE;
}

// CMultResults::BuildConcatSQL -------------------------------------------------
//
// Allocates and builds a concatenated SQL String for all of our operations, 
// places it in m_pwszSQLStmt.
//        
//
HRESULT CMultResults::BuildConcatSQL()
{	
	ULONG	cbSQLStmt = 0;
	ULONG	i;

	
	////////////////////////////////////////////////////
	// Allocate the buffer for the SQL Statement
	// and build it.  It will be formed by taking each 
	// statement in our array concatenated together, 
	// separated by a space.
	////////////////////////////////////////////////////

	//Free and Allocate again just to be sure we haven't had the
	//number of statements changed on us since last time we allocated 
	if (m_pwszSQLStmt)
	{
		CMultResults::s_pIMalloc->Free(m_pwszSQLStmt);
		m_pwszSQLStmt = NULL;
	}

	for (i=0; i<m_ceSQLStmts; i++)
	{
		//Allocate room for the SQL Stmt plus a space and a semicolon 
		//at end of each stmt.  We put a space in to get around
		//Use the current element of our ESQLSTMT array to determine
		//the index of the correct SQL string in the string table array
		cbSQLStmt += (wcslen(m_rgpwszSQL[m_rgeSQLStmts[i]]) + 2) * sizeof(WCHAR);
	}

	//Add null terminator to length
	cbSQLStmt += sizeof(WCHAR);

	//This is freed in DTOR, or freed and realloc'd on 
	//subseqent calls to this function
	m_pwszSQLStmt = (WCHAR *)CMultResults::s_pIMalloc->Alloc(cbSQLStmt);
	if (!m_pwszSQLStmt)
		return E_OUTOFMEMORY;


	memset(m_pwszSQLStmt, 0, cbSQLStmt);

	//Init to empty string so concats start at beginning
	m_pwszSQLStmt[0] = L'\0';
	
	for (i=0; i<m_ceSQLStmts; i++)
	{		
		//Concat the next statement
		wcscat(m_pwszSQLStmt, m_rgpwszSQL[m_rgeSQLStmts[i]]);				
		wcscat(m_pwszSQLStmt, L" ;");
	}

	return NOERROR;
}


// CMultResults::Execute ------------------------------------------------
//
// Does Execute on m_pICommandText which must already be set
//        
//
HRESULT	CMultResults::Execute(REFIID riid, DBPARAMS * pParams)
{
	IUnknown * pIUnknown = NULL;

	//Nothing special here, just execute and dump results in member vars
	m_hr = m_pICommandText->Execute(NULL, 
									riid, 
									pParams, 
									&m_cRowsExecuteAffected,
									&pIUnknown);

	// If IID is IUnknown or IMultipleResults always QI for IMultRes
	if ((riid == IID_IMultipleResults || riid == IID_IUnknown) &&
		S_OK == m_hr && !VerifyInterface(pIUnknown, IID_IMultipleResults,
		COMMAND_INTERFACE, (IUnknown **)&m_pIMultResults))
		m_hr = E_NOINTERFACE;

	//Put interface pointer in right member variable
	if (riid == IID_IMultipleResults)
	{
		// Use the pIUnknown returned from the method
		SAFE_RELEASE(m_pIMultResults);
		m_pIMultResults = (IMultipleResults *)pIUnknown;
	}
	else if (riid == IID_IRowset)
	{
		m_pIRowset=(IRowset *)pIUnknown;
	}
	else
		// We don't use the IUnknown interface, so release it here.
		SAFE_RELEASE(pIUnknown);
		
	return m_hr;
}


// CMultResults::ProcessAllResults --------------------------------------------
//
// Verifies everything about all results remaining for this result object
// (ie, the executed ole db command object), then releases all interfaces
// received from Execute and GetResult.
//
// NOTE:  riidGetResult is the iid asked for  on GetResult calls, and does not
// apply to Execute.   
// If cTotalResults is -1, the number of statements in the batch is used as
// the total expected number of results.
//
HRESULT CMultResults::ProcessAllResults(ULONG cResultsAlreadyProcessed,
										REFIID  riidExecute,
										REFIID  riidGetResult)
{	
	ULONG		i;
	IUnknown * pUnkRowset = NULL;
	HRESULT hr = E_FAIL;

	//This will be our return value variable
	m_hr = NOERROR;


	if (m_pIMultResults)
	{
		//Starting at index cResultsAlreadyProcessed will put
		//us at the next element to be processed since the
		//array is 0-based and cResultsAlreadyProcessed is 1-based	
		for (i=cResultsAlreadyProcessed; i<m_cTotalResultsExpected; i++)
		{
		
			if (S_OK == (m_hr = m_pIMultResults->GetResult(NULL, 
															0, 
															riidGetResult,
															&m_cRowsGetResultAffected,
															(IUnknown **)&pUnkRowset)))
			{
				//Check everything is correct for this result
				if (!COMPARE(AreGetResultOutParamsRight(i, pUnkRowset, riidGetResult), TRUE))				
				{
					m_hr = E_FAIL;
					odtLog << L"GetResult output params are not right for result: " << i+1 << wszNewLine;
				}

			}
			else
			{
				odtLog << L"GetResult did not return S_OK for result: " << i+1 << wszNewLine;
			}

			//Release this rowset if it exists
			if (pUnkRowset)
			{
				pUnkRowset->Release();
				pUnkRowset = NULL;
			}
		}	

		//Init to garbage so we can tell that it is cleared by this method
		pUnkRowset = (IUnknown *)0x12345678;

		//We should have retrieved all results already, so next should be DB_S_NORESULT
		
		if (DB_S_NORESULT == (hr = m_pIMultResults->GetResult(NULL, 
														0, 
														riidGetResult,
														&m_cRowsGetResultAffected,
														(IUnknown **)&pUnkRowset)))
		{
			//Pass an iResult of i, which means we've gone passed all 
			//possible results.  This function will then look for 
			//*ppRowset = NULL and *pcRowsAffected = -1.
			if (!AreGetResultOutParamsRight(i, pUnkRowset, riidGetResult))
				m_hr = E_FAIL;

		}
		else
			if (S_OK == m_hr)
				m_hr = hr;

		if(pUnkRowset && (pUnkRowset!=(IUnknown *)0x12345678))
			pUnkRowset->Release();
		pUnkRowset = NULL;
		//Now release interface received from Execute
		ReleaseIMultipleResults();
	}
	else
	{	
		//Verify Execute's result matches the first result expected
		if (!AreExecuteOutParamsRight(riidExecute, m_pIRowset))				
		{
			m_hr = E_FAIL;
			odtLog << L"Execute output params are not right for first result." << wszNewLine;
		}

		//Now release interface received from Execute
		ReleaseIRowset();
	}


	return m_hr;

}


// CMultResults::AreGetResultOutParamsRight --------------------------------
//
// Checks *pcRowsAffected and *ppRowset, and verifies against
// the results we are supposed to get back
//        
//
BOOL CMultResults::AreGetResultOutParamsRight(ULONG iResult, IUnknown * pUnkRowset, REFIID riid) 
{ 
	
	//If we have called GetResult for more times that we have results,
	//*ppRowset must be NULL and *pcRowsAffected must be -1 and no
	//further checking is necessary.  This is the DB_S_NORESULT case.
	if (iResult >= m_cTotalResultsExpected)
	{
		if (pUnkRowset == NULL &&
			m_cRowsGetResultAffected == -1)
			return TRUE;
		else
			return FALSE;
	}

	switch (m_rgeSQLStmts[iResult])
	{
		case EINSERT:
		case EDELETE:
		case EUPDATE:
			//we can check the row count
			if (IsGetResultRowsAffectedRight(iResult))
				//and the rowset interface returned must be NULL
				return (NULL == pUnkRowset);
			break;
		case ECREATE:
		case EDROP:
			//Row count is undefined, only check rowset is null
			return (NULL == pUnkRowset);
			break;	
		
		case ESELECT:
			if (pUnkRowset)
				return S_OK == VerifySelectRowset(riid, pUnkRowset);
			break;
		
		case EEMPTYSELECT:
			if (pUnkRowset)
				return DB_S_ENDOFROWSET == VerifySelectRowset(riid, pUnkRowset);
			break;
		
		default:
			//Need to add more code for other enums
			ASSERT(FALSE);

	}		
				
		
	//We haven't returned through one of our successful paths,
	//meaning there was an error, so return FALSE
	return FALSE;
}


// CMultResults::AreExecuteOutParamsRight --------------------------------
//
// Checks *pcRowsAffected and *ppRowset, and verifies against
// the results we are supposed to get back for the first result
//        
//
BOOL CMultResults::AreExecuteOutParamsRight(REFIID riid, IUnknown * pUnkRowset) 
{ 
	////////////////////////////////////////////////////
	//Check everything against the first result in our set,
	//that is all Execute with IID_IRowset can bring back
	////////////////////////////////////////////////////
	switch(m_rgeSQLStmts[0])
	{
		case EINSERT:
		case EUPDATE:
		case EDELETE:
			//we can check the row count
			if (IsExecuteRowsAffectedRight())
				//and the rowset interface returned must be NULL
				return (NULL == pUnkRowset);
		break;
		
		case ECREATE:
		case EDROP:
			//Row count is undefined, only check rowset is null
			return (NULL == pUnkRowset);
		break;

		case ESELECT:
			if (pUnkRowset)
				return S_OK == VerifySelectRowset(riid, pUnkRowset);
		break;
		
		case EEMPTYSELECT:
			if (pUnkRowset)
				return DB_S_ENDOFROWSET == VerifySelectRowset(riid, pUnkRowset);
		break;
		
		default: 
			//Need more code to deal with new enums
			ASSERT(FALSE);
		
	}
		
	//We haven't returned through one of our successful paths,
	//meaning there was an error, so return FALSE
	return FALSE;
}


// CMultResults::VerifySelectRowset --------------------------------
//
// Checks *pcRowsAffected and *ppRowset, and verifies against
// the results we are supposed to get back
//        
//
HRESULT CMultResults::VerifySelectRowset(REFIID riid, IUnknown * pUnkRowset) 
{ 
	
	ULONG		cRowsObtained;
	BYTE *		pData = NULL;
	HROW *		prghRows = NULL;
	HACCESSOR	hAccessor = DB_NULL_HACCESSOR;
	ULONG		cbRowSize = 0;
	ULONG		cBindings = 0;
	DBBINDING * rgBindings = NULL;
	IAccessor * pIAccessor = NULL;
	ULONG		i;
	IRowset *	pIRowset = NULL;
	IUnknown *  pIUnknown = NULL;
	IUnknown *  pIOwnInterface = NULL;
	IColumnsInfo * pIColumnsInfo = NULL;
	IConvertType * pIConvertType = NULL;
	IRowsetInfo * pIRowsetInfo = NULL;
	DBCOLUMNINFO * pColInfo = NULL;
	WCHAR * pStringsBuffer = NULL;
	ULONG cPropertySets=0;
	DBPROPSET * pPropertySets = NULL;

	//User error if we don't have a Rowset
	ASSERT(pUnkRowset);

	//Init this to something bad so if we fall out 
	//anywhere we'll return a negative return code
	m_hr = E_FAIL;
	cRowsObtained = 0;

	// We can always QI for our own interface off the pointer
	if (FAILED(m_hr = pUnkRowset->QueryInterface(riid, (void **)&pIOwnInterface)))
		goto CLEANUP;

	// We should always be able to get IUnknown
	if (FAILED(m_hr = pUnkRowset->QueryInterface(IID_IUnknown, (void **)&pIUnknown)))
		goto CLEANUP;

	// IRowset is mandatory
	if (FAILED(m_hr = pUnkRowset->QueryInterface(IID_IRowset, (void **)&pIRowset)))
		goto CLEANUP;

	// IAccessor is mandatory
	if (FAILED(m_hr = pUnkRowset->QueryInterface(IID_IAccessor, (void **)&pIAccessor)))
		goto CLEANUP;
	
	// IColumnsInfo is mandatory.  It's used in GetAccessorAndBindings but it's better
	// to fail here if not available.
	if (FAILED(m_hr = pUnkRowset->QueryInterface(IID_IColumnsInfo, (void **)&pIColumnsInfo)))
		goto CLEANUP;

	// IConvertType is mandatory.  It may be used in GetAccessorAndBindings but it's better
	// to fail here if not available.
	if (FAILED(m_hr = pUnkRowset->QueryInterface(IID_IConvertType, (void **)&pIConvertType)))
		goto CLEANUP;

	// IRowsetInfo is mandatory
	if (FAILED(m_hr = pUnkRowset->QueryInterface(IID_IRowsetInfo, (void **)&pIRowsetInfo)))
		goto CLEANUP;

	// Make sure the interface passed in actually works by calling a method on it.
	// For IID_IRowset and IID_IAccessor we call methods always.

	if (riid == IID_IUnknown)
	{
		IUnknown * pIUnknown = (IUnknown *)pUnkRowset;

		pIUnknown->AddRef();
		pIUnknown->Release();
	}
	else if (riid == IID_IAccessor)
	{
		// Use the one we were passed even though it should be the same
		SAFE_RELEASE(pIAccessor);
		pIAccessor = (IAccessor *)pUnkRowset;
		pIAccessor->AddRef();
	}
	else if (riid == IID_IConvertType)
	{
		IConvertType * pIConvertType = (IConvertType *)pUnkRowset;

		// WSTR is always a mandatory conversion
		TESTC_(pIConvertType->CanConvert(DBTYPE_WSTR, DBTYPE_WSTR, DBCONVERTFLAGS_COLUMN), S_OK);
	}
	else if (riid == IID_IRowset)
	{
		// Use the one we were passed even though it should be the same
		SAFE_RELEASE(pIRowset);
		pIRowset = (IRowset *)pUnkRowset;
		pIRowset->AddRef();
	}
	else if (riid == IID_IRowsetInfo)
	{
		IRowsetInfo * pIRowsetInfo = (IRowsetInfo *)pUnkRowset;

		TESTC_(pIRowsetInfo->GetProperties(0, NULL, &cPropertySets, &pPropertySets), S_OK);

		TESTC(cPropertySets > 0);
		TESTC(pPropertySets != NULL);
		TESTC(pPropertySets[0].cProperties > 0);
		TESTC(pPropertySets[0].rgProperties != NULL);
		TESTC(pPropertySets[0].guidPropertySet == DBPROPSET_ROWSET);
	}
	else if (riid == IID_IColumnsInfo)
	{
		IColumnsInfo * pIColumnsInfo = (IColumnsInfo *)pUnkRowset;
		ULONG cColumns;

		TESTC_(pIColumnsInfo->GetColumnInfo(&cColumns, &pColInfo, &pStringsBuffer), S_OK);

		TESTC(cColumns == m_pSelectTable->CountColumnsOnTable()+!pColInfo[0].iOrdinal);
	}
	else if (riid == IID_IRowsetScroll)
	{
		ULONG cRowsObtained;
		HROW hRow;
		HROW * phRow = &hRow;
		IRowsetScroll * pIRowsetScroll = (IRowsetScroll *)pUnkRowset;

		// Fetch one row at ratio 1/2.
		TESTC_(m_hr = pIRowsetScroll->GetRowsAtRatio(NULL, NULL, 1, 2, 1, &cRowsObtained, &phRow), S_OK);

		pIRowsetScroll->ReleaseRows(1, phRow, NULL, NULL, NULL);
	
	}
	else
	{
		ASSERT(!L"Need a new value for rowset RIID.\n");
		odtLog << L"Need a new value for rowset RIID.\n";
	}	
		

	//Create an accessor
	TESTC_(m_hr = GetAccessorAndBindings(pIRowset, 
												DBACCESSOR_ROWDATA,
												&hAccessor, 
												&rgBindings, 
												&cBindings, 
												&cbRowSize), S_OK);

	//Allocate a new data buffer
	pData = (BYTE *)CMultResults::s_pIMalloc->Alloc(cbRowSize);
	if (!pData)			
	{
		m_hr = ResultFromScode(E_OUTOFMEMORY);
		goto CLEANUP;
	}
	
	memset(pData, 0, cbRowSize);

	//Use IRowset to retrieve data, ask for one more than
	//there should be to verify we get DB_S_ENDOFROWSET and
	//there aren't too many rows in the rowset
	if (DB_S_ENDOFROWSET != (m_hr = pIRowset->GetNextRows(NULL, 
															0, 
															m_cRowsInSelect+1, 
															&cRowsObtained, 
															(HROW **)&prghRows)))
	{
		//In this case S_OK is the wrong answer, so bubble up an error to caller
		if (m_hr == S_OK)
			m_hr = E_FAIL;

		goto CLEANUP;		
	}
		 	
	//Make sure we got the right number of rows
	if (cRowsObtained != m_cRowsInSelect)
	{
		//Signal user that DB_S_ENDOFROWSET was really returned
		//meaning the rowset was empty if no rows are there
		if (cRowsObtained == 0)
			m_hr = DB_S_ENDOFROWSET;
		else
			//The rowset isn't empty, so some other failure must have occurred
			m_hr = E_FAIL;

		goto CLEANUP;
	}

	//From here on out we'll assume success and if this changes
	//we'll assign m_hr to the appropriate code and break from the loop 
	m_hr = NOERROR;

	for (i=0; i< cRowsObtained; i++)
	{
		//GetData and fail right away if it doesn't work
		if (!CHECK(m_hr = pIRowset->GetData(prghRows[i], 
												hAccessor, 
												pData), S_OK))
			break;
			
		//Verify data value, length and status are what is expected
		if (!COMPARE(CompareData(m_pSelectTable->CountColumnsOnTable(), 
							m_rgCompOrds, 
							ROW_SEED+i, 
							pData, 
							cBindings, 
							rgBindings,
							m_pSelectTable, 
							CMultResults::s_pIMalloc, 
							PRIMARY), TRUE))			
		{		
			m_hr = E_FAIL;
			break;
		}
				
	}

CLEANUP:
	
	if (pIAccessor)
	{
		if (hAccessor != DB_NULL_HACCESSOR)
			pIAccessor->ReleaseAccessor(hAccessor, NULL);
		pIAccessor->Release();
	}

	if (pIRowset)
	{
		pIRowset->ReleaseRows(cRowsObtained,
							prghRows, 
							NULL, 
							NULL,
							NULL);

		pIRowset->Release();
		pIRowset = NULL;

	}

	SAFE_FREE(prghRows);
	SAFE_RELEASE(pIUnknown);
	SAFE_RELEASE(pIOwnInterface);
	SAFE_RELEASE(pIColumnsInfo);
	SAFE_RELEASE(pIConvertType);
	SAFE_RELEASE(pIRowsetInfo);

	if (rgBindings)
		CMultResults::s_pIMalloc->Free(rgBindings);

	//Clean up fixed buffer 
	if (pData)
		CMultResults::s_pIMalloc->Free(pData);

	PROVIDER_FREE(pColInfo);
	PROVIDER_FREE(pStringsBuffer);
	FreeProperties(&cPropertySets, &pPropertySets);
	
	return m_hr;


}


// CMultResults::~CMultResults --------------------------------------------
//
// DTOR
//        
//
CMultResults::~CMultResults()
{
		
	ULONG i;	
	
	if (m_pIDBCreateCommand)
	{
		m_pIDBCreateCommand->Release();
		m_pIDBCreateCommand = NULL;
	}
	
	if (m_pICommandText)
	{
		m_pICommandText->Release();
		m_pICommandText = NULL;
	}

	if (m_rgSelectOrds)
	{
		CMultResults::s_pIMalloc->Free(m_rgSelectOrds);
		m_rgSelectOrds = NULL;
	}

	if (m_rgCompOrds)
	{
		CMultResults::s_pIMalloc->Free(m_rgCompOrds);
		m_rgCompOrds = NULL;
	}

	if (m_pwszSQLStmt)
	{
		CMultResults::s_pIMalloc->Free(m_pwszSQLStmt);
		m_pwszSQLStmt = NULL;
	}
	
	if (m_rgeSQLStmts)
	{
		CMultResults::s_pIMalloc->Free(m_rgeSQLStmts);

	}
	if (m_rgStmtRowsAffected)
	{
		CMultResults::s_pIMalloc->Free(m_rgStmtRowsAffected);

	}
	
	if (m_pwszNewTableName)	
		CMultResults::s_pIMalloc->Free(m_pwszNewTableName);
		

	//Free all elements of string table
	for (i=0; i<NUM_SQLSTMTS; i++)
		if(m_rgpwszSQL[i])
			CMultResults::s_pIMalloc->Free(m_rgpwszSQL[i]);

}


// CMultResults::CheckErrorOutParams ------------------------------------------------
//
// Verifies that the GetResults out parameters are correctly set when method 
// returns an error.  Assumes GetResult is always called with pcRowsAffected 
// as &this->m_cRowsGetResultAffected.
//        
//
BOOL	CMultResults::CheckErrorOutParams(IUnknown * pRowset)
{
	if (COMPARE(pRowset, NULL))
		if (COMPARE(m_cRowsGetResultAffected, DB_COUNTUNAVAILABLE))	
			return TRUE;
	
	return FALSE;
}

//////////////////////////////////////////////////////////////////
// CBatch
//////////////////////////////////////////////////////////////////


// CBatch::SetAndExecute ------------------------------------------------
//
// Implementation of pure virtual function from CMultResults.  Sets SQL in proper
// format for a batch statement and executes it.  The execute is done by calling
// CMultResults::Execute().
//        
//
HRESULT CBatch::SetAndExecute(REFIID riid)
{

	//For pure batched statements, just build a string of
	//all SQL stmts concatenated together, separated by spaces	
	if (SUCCEEDED(m_hr = BuildConcatSQL()))
			
		//Set that string
		if (SUCCEEDED(m_hr = m_pICommandText->SetCommandText(DBGUID_DBSQL, m_pwszSQLStmt)))

			//Execute it
			m_hr = Execute(riid, NULL);
	
	
	return m_hr;
}


// CBatch::FInit ------------------------------------------------
//
// Does post construction initialization.  
//
//
BOOL CBatch::FInit(const ULONG cSQLStmts, ESQLSTMT * rgSQLStmts)
{
	LONG	* rgRowsAffected = NULL;
	ULONG	i;
	ULONG	cTotalRowsAffected = 0;
	BOOL	fResults = FALSE;
	ULONG	cInserts = 0;

	
	////////////////////////////////////////////////////
	//All we need to do is determine the parameters that
	//are derived class specific, then delegate to our
	//base class FInit
	////////////////////////////////////////////////////

	//Alloc memory for our array
	rgRowsAffected = (LONG *)CMultResults::s_pIMalloc->Alloc(cSQLStmts * sizeof(LONG));
	if (!rgRowsAffected)
		goto CLEANUP;

	//Find out how many rows we have, should always be more than 0
	//Note we count this each time so that if previous variations' inserts
	//fail we still have an accurate count of how many rows are
	//actually in the table.
	m_cRowsInChgTable = m_pChangeTable->CountRowsOnTable();
	if (!m_cRowsInChgTable)
		goto CLEANUP;

	//Free the CTable command that was created in CountRowsOnTable
	//so that we can be in firehose mode when we execute
	if (m_pChangeTable->m_pICommand)
	{
		(m_pChangeTable->m_pICommand)->Release();
		m_pChangeTable->m_pICommand = NULL;
	}

	//Figure out how many rows each statement in the batch
	//affects, and init corresponding array element to that value
	for (i=0; i<cSQLStmts; i++)
	{
		switch(rgSQLStmts[i])
		{
			case ESELECT:
			case EEMPTYSELECT:
			case ECREATE:	
			case EDROP:	
			case ECOMPUTESUM:
				//This is undefined, to flag it's not to be looked at
				rgRowsAffected[i] = -1;
				break;
											
			case EDELETE:		
				//Our delete clause should never find any rows
				rgRowsAffected[i] = 0;
				break;
			
			case EUPDATE:		
				//The update will always affect all rows in the table
				//which is number of rows existing when we start
				//the batch plus number of inserts we've done so far
				//in this batch
				rgRowsAffected[i] = m_cRowsInChgTable + cInserts;
				break;
			
			case EINSERT:		
				//We always insert just one row
				rgRowsAffected[i] = 1;
				//Keep track of how many inserts we do in this batch
				//so we know how many rows updates will affect
				cInserts++;
				break;
			
			default:
				//Need to add code to deal with any other enum values
				ASSERT(FALSE);
		}
	}
	
	
	//Just add up all of the above (which are row affecting) to find 
	//the total for a batch statement's total rows affected
	for (i=0; i<cSQLStmts; i++)
		if (rgSQLStmts[i] == EUPDATE || 
			rgSQLStmts[i] == EINSERT || 
			rgSQLStmts[i] == EDELETE)
			//Add the total for this element
			cTotalRowsAffected += rgRowsAffected[i];

	//Now delegate to our base class FInit, it copies rgRowsAffected
	fResults =CMultResults::FInit(cSQLStmts, rgSQLStmts, rgRowsAffected);

	// The non-parameterized select returns all rows in the table.
	m_cRowsInSelect = SELECT_ROW_NUM;


CLEANUP:
	
	//Free our array since FInit only copied it and doesn't own it
	if (rgRowsAffected)
		CMultResults::s_pIMalloc->Free(rgRowsAffected);

	return fResults;

}


//////////////////////////////////////////////////////////////////
// CParamSets
//////////////////////////////////////////////////////////////////


// CParamSets::CParamSets --------------------------------------------
//
// CTOR
//        
//
CParamSets::CParamSets(ULONG cParamSets, 
						IDBCreateCommand * pIDBCreateCommand,
						ICommandText * pICommandText,
						CTable * pSelectTable,
						CTable * pChangeTable)
				: CMultResults(pIDBCreateCommand,
							 pICommandText,
							 pSelectTable,
							 pChangeTable)
{
	m_cTotalRowsAffected = 0;	
	m_dbParams.pData = NULL;
	m_dbParams.cParamSets = cParamSets;
	m_dbParams.hAccessor = DB_NULL_HACCESSOR;
	m_rgBindings = NULL;
	m_cBindings = 0;

}


// CParamSets::~CParamSets --------------------------------------------
//
// DTOR
//        
//
CParamSets::~CParamSets()
{

	if (m_rgBindings)
	{
		CMultResults::s_pIMalloc->Free(m_rgBindings);
		m_rgBindings = NULL;		
	}

	if (m_dbParams.pData)
	{
		CMultResults::s_pIMalloc->Free(m_dbParams.pData);
		m_dbParams.pData = NULL;
	}

	if (m_pIAccessor)
	{	
		if (m_dbParams.hAccessor)
		{
			m_pIAccessor->ReleaseAccessor(m_dbParams.hAccessor, NULL);
			m_dbParams.hAccessor = DB_NULL_HACCESSOR;
		}

		m_pIAccessor->Release();
		m_pIAccessor = NULL;
	}
}


// CParamSets::SetAndExecute ------------------------------------------------
//
// Implementation of pure virtual function from CMultResults.  Sets SQL in proper
// format for a batch statement and executes it.  The execute is done by calling
// CMultResults::Execute().
//        
//
HRESULT CParamSets::SetAndExecute(REFIID riid)
{

	
	//Build SQL statement -- for this class there is only one
	//statement to concat, but we can still use this function.
	if (SUCCEEDED(m_hr = BuildConcatSQL()))
			
		//Set that string
		if (SUCCEEDED(m_hr = m_pICommandText->SetCommandText(DBGUID_DBSQL, m_pwszSQLStmt)))
		{
			//Execute it with Param structs
			m_hr = Execute(riid, &m_dbParams);
		}
	
	
	return m_hr;
}


// CParamSets::CalcTotalResultsExpected ------------------------------------------------
//
// Calculates the proper m_cTotalResultsExpected
//
//
void CParamSets::CalcTotalResultsExpected()
{

	ULONG	i = 0;

	//////////////////////////////////////////////////////
	//Find how many results we expect and modify the 
	//appropriate data members
	//////////////////////////////////////////////////////

	//Override the default results count calculated in CMultResults::FInit
	m_cTotalResultsExpected = 0;	

	for (i=0; i< m_ceSQLStmts; i++)
	{
		switch (m_rgeSQLStmts[i])
		{
			case ESELECT:							
				//One result for each param set element
				m_cTotalResultsExpected += m_dbParams.cParamSets;
			break;
					
			case EINSERT:						
				//Inserts are only counted as a result
				//if there are only inserts in the batch
				if (m_ceSQLStmts == 1)
					m_cTotalResultsExpected++;		
			break;
			
			default:
				//Need to add code to deal with any other enum values
				ASSERT(FALSE);
		}
	}

}

// CParamSets::CalcTotalRowsAffected ------------------------------------------------
//
// Calculates the proper m_cTotalRowsAffected
//
//
void CParamSets::CalcTotalRowsAffected()
{

	ULONG	i = 0;

	//////////////////////////////////////////////////////
	//Find the total rows affected by the whole execution
	//////////////////////////////////////////////////////
		
	m_cTotalRowsAffected = 0;

	for (i=0; i< m_ceSQLStmts; i++)
	{
		switch (m_rgeSQLStmts[i])
		{
			case ESELECT:			
				;	//No rows affected for a select.				
			break;
					
			case EINSERT:		
				//We always insert just one row for a single param set
				m_cTotalRowsAffected += m_dbParams.cParamSets;						
			break;
			
			default:
				//Need to add code to deal with any other enum values
				ASSERT(FALSE);
		}
	}

}

// CParamSets::FInit ------------------------------------------------
//
// Does post construction initialization.  
//
//
BOOL CParamSets::FInit(const ULONG cSQLStmts, ESQLSTMT * rgSQLStmts)
{
	LONG	* rgRowsAffected = NULL;
	ULONG	i = 0;
	ULONG	j = 0;
	ULONG	cTotalRowsAffected = 0;
	BOOL	fResults = FALSE;
	ULONG	cInserts = 0;
	
	////////////////////////////////////////////////////
	//Perform CParamSets specific initialization,
	//determine the parameters that are derived class specific, 
	//then delegate to our base class FInit
	////////////////////////////////////////////////////		
		

	//Alloc memory for our count of rows affected array
	rgRowsAffected = (LONG *)CMultResults::s_pIMalloc->Alloc(cSQLStmts * sizeof(LONG));
	if (!rgRowsAffected)
		goto CLEANUP;

	m_ceSQLStmts = cSQLStmts;
	m_rgeSQLStmts = rgSQLStmts;

	//Set m_cTotalRowsAffected
	CalcTotalRowsAffected();

	//Fill the rows affected array
	for (i=0; i<cSQLStmts; i++)
	{
		//For param sets, each individual count is the total rows affected
		rgRowsAffected[i] = m_cTotalRowsAffected;
	}
		

	//Now delegate to our base class FInit, it copies rgRowsAffected
	if (CMultResults::FInit(cSQLStmts, rgSQLStmts, rgRowsAffected))
	{
		//Now override the SQL statments we built in CMultResults::FInit
		//to use parametmers, also build accessors and data needed 
		//for param execution

		//Free non parameterized statement
		if (m_rgpwszSQL[ESELECT])
		{
			//Free first since we've built this table
			//once in our base FInit and want to redo
			//this string in it
			CMultResults::s_pIMalloc->Free(m_rgpwszSQL[ESELECT]);
			m_rgpwszSQL[ESELECT] = NULL;
		}

		if (FAILED(m_pSelectTable->CreateSQLStmt(
								SELECT_ALL_WITH_SEARCHABLE_AND_UPDATEABLE,
								NULL,
								&m_rgpwszSQL[ESELECT],	
								NULL,
								NULL)))
			goto CLEANUP;
		
		
		//Free non parameterized statement
		if (m_rgpwszSQL[EINSERT])
		{

			//Free first since we've built this table
			//once in our base FInit and want to redo
			//this string in it
			CMultResults::s_pIMalloc->Free(m_rgpwszSQL[EINSERT]);
			m_rgpwszSQL[EINSERT] = NULL;
		}

		if (FAILED(m_pChangeTable->InsertWithParams(
								ROW_SEED,
								PRIMARY,
								FALSE,	// Don't execute
								&m_rgpwszSQL[EINSERT])))
			goto CLEANUP;	
		
	
		//Override the total num of results expected
		//which was set in CMultResults::FInit, since
		//param sets cause a different number of
		//results than just the number of statements 
		//in the batch
		CalcTotalResultsExpected();		

		if (FAILED(BuildParamAccessorAndData(cSQLStmts)))
					goto CLEANUP;

		// We only expect one row from the parameterized
		// select stmt.
		m_cRowsInSelect = 1;
		
		//We're OK if we made it this far
		fResults = TRUE;
	}


CLEANUP:
	
	//Free our array since FInit only copied it and doesn't own it
	if (rgRowsAffected)
		CMultResults::s_pIMalloc->Free(rgRowsAffected);

		
	return fResults;

}


// CParamSets::ProcessAllResults --------------------------------------------
//
// Verifies everything about all results remaining for this result object
// (ie, the executed ole db command object), then releases all interfaces
// received from Execute and GetResult.
//
// NOTE:  riidGetResult is the iid asked for  on GetResult calls, and does not
// apply to Execute.   
// If cTotalResults is -1, the number of statements in the batch is used as
// the total expected number of results.
//
HRESULT CParamSets::ProcessAllResults(ULONG cResultsAlreadyProcessed,
									    REFIID  riidExecute,
										REFIID  riidGetResult)
{	
	ULONG		i;
	IUnknown * pUnkRowset = NULL;
	ULONG		ulCurSQLStmt = cResultsAlreadyProcessed;
	ULONG		ulCurParamSet = 1;

	//This will be our return value variable
	m_hr = NOERROR;

	if (m_pIMultResults)
	{
		//Starting at index cResultsAlreadyProcessed will put
		//us at the next element to be processed since the
		//array is 0-based and cResultsAlreadyProcessed is 1-based	
		for (i=cResultsAlreadyProcessed; i<m_cTotalResultsExpected; i++)
		{			
			if (S_OK == (m_hr = m_pIMultResults->GetResult(NULL, 
															0, 
															riidGetResult,
															&m_cRowsGetResultAffected,
															(IUnknown **)&pUnkRowset)))
			{
								
				//Check everything is correct for this result
				if (!AreGetResultOutParamsRight(ulCurSQLStmt, pUnkRowset, riidGetResult))				
				{
					m_hr = E_FAIL;
					odtLog << L"GetResult output params are not right for result: " << i+1 << wszNewLine;
					goto CLEANUP;
				}

			}
			else
			{

				m_hr = E_FAIL;
				odtLog << L"GetResult did not return S_OK for result: " << i+1 << wszNewLine;
				goto CLEANUP;
			}

			//Release this rowset if it exists
			if (pUnkRowset)
			{
				pUnkRowset->Release();
				pUnkRowset = NULL;
			}

						
			//Stay on same SQLStatment for verifying results
			//if it is a select and we haven't gotten thru
			//all the parameter sets yet
			if (m_rgeSQLStmts[ulCurSQLStmt] == ESELECT && 
				ulCurParamSet < m_dbParams.cParamSets)
			{
				ulCurParamSet++;
			}
			else			
			{
				//Time to move on to next SQL Statement in batch				
				ulCurParamSet = 1;
				ulCurSQLStmt++;

				//Only check this if we have another iteration coming
				if (i+1 < m_cTotalResultsExpected)
					//Since for multiple param sets in batch, the inserts
					//are not counted as a result, we'll skip them				
					if (m_rgeSQLStmts[ulCurSQLStmt] == EINSERT)
						ulCurSQLStmt++;

			}
		
		}	

		//Init to garbage so we can tell that it is cleared by this method
		pUnkRowset = (IUnknown *)0x12345678;

		//We should have retrieved all results already, so next should be DB_S_NORESULT
		if (DB_S_NORESULT == m_pIMultResults->GetResult(NULL, 
														0, 
														riidGetResult,
														&m_cRowsGetResultAffected,
														(IUnknown **)&pUnkRowset))	
		{
		
			
			//Pass an iResult of i, which means we've gone passed all 
			//possible results.  This function will then look for 
			//*ppRowset = NULL and *pcRowsAffected = -1.
			if (!AreGetResultOutParamsRight(i, pUnkRowset, riidGetResult))
			{
				m_hr = E_FAIL;
				goto CLEANUP;
			}
		}
		else
		{
			m_hr = E_FAIL;
			goto CLEANUP;
		}
		//Now release interface received from Execute
		ReleaseIMultipleResults();
	}
	else
	{	
		//Verify Execute's result matches the first result expected
		if (!AreExecuteOutParamsRight(riidExecute, m_pIRowset))				
		{
			m_hr = E_FAIL;
			odtLog << L"Execute output params are not right for first result." << wszNewLine;
		}

		//Now release interface received from Execute
		ReleaseIRowset();
	}

CLEANUP:

	ReleaseIMultipleResults();

	if (pUnkRowset)
	{
		pUnkRowset->Release();
		pUnkRowset = NULL;
	}

	return m_hr;
}

// CParamSets::BuildParamAccessorAndData ------------------------------------
//
// Builds all needed parameter stuff for execution
//
//
HRESULT CParamSets::BuildParamAccessorAndData(const ULONG cSQLStmts)
{

	EQUERY	eQuery;
	WCHAR * wszTempQuery = NULL;
	ULONG	cParamCols = 0;
	CCol	tempCol;
	BYTE *  pSetOffset = NULL;	
	ULONG	i = 0;
	ULONG	j = 0;
	ULONG	k = 0;
	DBBINDING *		pCurBindings = NULL;
	LONG *			pCurParamCols = NULL;
	ULONG			cCurBindings = 0;	
	ULONG			cbCurRowSize = 0;

	m_cbRowSize = 0;
	m_cBindings = 0;	
	m_hr = E_FAIL;


	//Get rid of the select col list that non parameterized
	//statements use
	if (m_rgSelectOrds)
	{
		CMultResults::s_pIMalloc->Free(m_rgSelectOrds);
		m_rgSelectOrds = NULL;
	}

	if (m_rgCompOrds)
	{
		CMultResults::s_pIMalloc->Free(m_rgCompOrds);
		m_rgCompOrds = NULL;
	}

	//Get Accessor interface	
	if (FAILED(m_hr = m_pICommandText->QueryInterface(IID_IAccessor, 
									(void **)&m_pIAccessor)))
		goto CLEANUP;


	//Alloc arrays which are sure to be large enough, 
	//but we may not use all of the size we alloc
	m_rgSelectOrds = 
		(LONG *)CMultResults::s_pIMalloc->Alloc(m_pSelectTable->CountColumnsOnTable() 
												* cSQLStmts * sizeof(LONG) * m_dbParams.cParamSets);
	m_rgCompOrds = 
		(LONG *)CMultResults::s_pIMalloc->Alloc(m_pSelectTable->CountColumnsOnTable() 
												* cSQLStmts * sizeof(LONG) * m_dbParams.cParamSets);
	if (m_rgBindings)
	{
		CMultResults::s_pIMalloc->Free(m_rgBindings);
		m_rgBindings = NULL;
	}

	m_rgBindings = 
		(DBBINDING *)CMultResults::s_pIMalloc->Alloc(m_pSelectTable->CountColumnsOnTable() 
													* cSQLStmts * sizeof(DBBINDING) * m_dbParams.cParamSets);
	if (!m_rgBindings || !m_rgSelectOrds || !m_rgCompOrds)
	{
		m_hr = E_OUTOFMEMORY;
		goto CLEANUP;
	}

	////////////////////////////////////////////////////
	//Setup according to what kind of parameters we have
	////////////////////////////////////////////////////


	//For each statement in the batch
	for (k=0; k<m_ceSQLStmts; k++)
	{
		//Set our offset to the right place in m_rgSelectOrds
		//for this portion of the batch
		pCurParamCols = &m_rgSelectOrds[m_cBindings];

		if (m_rgeSQLStmts[k] == EINSERT)
		{
			//Our temp query will be all updateable cols
			eQuery = SELECT_UPDATEABLE;

			//Build array of all updateable cols' ordinals
			for (i=1, j=0; i<=m_pSelectTable->CountColumnsOnTable(); i++)
			{
				m_pSelectTable->GetColInfo(i, tempCol);
				if (tempCol.GetUpdateable())
				{
					pCurParamCols[j] = i;
					j++;
				}
			}

		}
		else
			if (m_rgeSQLStmts[k] == ESELECT)
			{
				//Our temp query will be one which finds all
				//columns which work  in a parameterized where clause
				eQuery = SELECT_ALL_WITH_SEARCHABLE_AND_UPDATEABLE;

				//Build array of all cols which will be in the				
				//SELECT_ALL_WITH_SEARCHABLE_AND_UPDATEABLE statement.
				//We don't use any long columns as they are illegal in a LIKE clause if
				//over 255 chars on SQL Server. 				
				for (i=1, j=0; i<=m_pSelectTable->CountColumnsOnTable(); i++)
				{
					m_pSelectTable->GetColInfo(i, tempCol);
					if (tempCol.GetSearchable() != DB_UNSEARCHABLE && 
						!tempCol.GetIsLong() &&
						tempCol.GetUpdateable())
					{
						pCurParamCols[j] = i;
						m_rgCompOrds[j] = i;
						j++;
					}

				}
			}
			else
				//We need to add more code for addional enum values
				ASSERT(FALSE);
			
		
		//Remember total number of param ordinals we found
		cParamCols += j;


		////////////////////////////////////////////////
		//Create Accessor
		////////////////////////////////////////////////

		//Temporarily set query to contain all correct
		//columns so we can figure out
		//the binding info on the parameters for our 
		//parameterized statement
		if (FAILED(m_hr = m_pSelectTable->CreateSQLStmt(
								eQuery,
								NULL,
								&wszTempQuery,	
								NULL,
								NULL)))
			goto CLEANUP;


		if (FAILED(m_hr = m_pICommandText->SetCommandText(DBGUID_DBSQL,
													wszTempQuery)))
			goto CLEANUP;

		if (wszTempQuery)
			CMultResults::s_pIMalloc->Free(wszTempQuery);
			wszTempQuery = NULL;

		//Use the temp query to generate bindings for this portion of the batch
		if (FAILED(m_hr = GetAccessorAndBindings(m_pICommandText, 
									DBACCESSOR_PARAMETERDATA,
									&m_dbParams.hAccessor,
									&pCurBindings,
									&cCurBindings,
									&cbCurRowSize,
									DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS,
									ALL_COLS_BOUND,	//Use param array we built ourselves
									FORWARD,
									NO_COLS_BY_REF,
									NULL,
									NULL,
									NULL,
									DBTYPE_EMPTY,
									0,
									NULL,									
									s_rgParamOrdinals,
									NO_COLS_OWNED_BY_PROV,
									DBPARAMIO_INPUT,
									BLOB_LONG)))	//Bind all cols since we include then in SQL stmt
			goto CLEANUP;

		//Adjust the offsets
		for (ULONG i=0; i<cCurBindings; i++)
		{
			pCurBindings[i].obValue += m_cbRowSize;
			pCurBindings[i].obLength += m_cbRowSize;
			pCurBindings[i].obStatus += m_cbRowSize;
		}


		//Adjust our total binding values to include the partial ones we just built
		memcpy(&m_rgBindings[m_cBindings], pCurBindings, cCurBindings * sizeof(DBBINDING));
		m_cBindings +=cCurBindings;
		m_cbRowSize +=cbCurRowSize;	
		

		//Free what was allocated in GetAccessorAndBindings since we've
		//already copied it into m_rgBindings
		CMultResults::s_pIMalloc->Free(pCurBindings);

		//Release this accessor since we only want the bindings
		m_pIAccessor->ReleaseAccessor(m_dbParams.hAccessor, NULL);
		m_dbParams.hAccessor = DB_NULL_HACCESSOR;
	
	}	

	/////////////////////////////////////////////////////////
	//Now create the real accessor with the total binding info
	/////////////////////////////////////////////////////////

	//Set the correct ordinals
	for (i=0; i<m_cBindings; i++)
		m_rgBindings[i].iOrdinal = s_rgParamOrdinals[i];

	if ((m_hr = m_pIAccessor->CreateAccessor(DBACCESSOR_PARAMETERDATA,
										m_cBindings,										
										m_rgBindings,										
										m_cbRowSize,
										&m_dbParams.hAccessor,
										NULL)) != S_OK)	
			goto CLEANUP;

	
	////////////////////////////////////////////////
	//Build the data
	////////////////////////////////////////////////

	//Allocate a buffer big enough for all the param sets
	m_dbParams.pData = 
		(BYTE *)CMultResults::s_pIMalloc->Alloc(m_dbParams.cParamSets * m_cbRowSize);
	if (!m_dbParams.pData)
	{
		m_hr = E_OUTOFMEMORY;
		goto CLEANUP;
	}


	for (i=0; i<m_dbParams.cParamSets; i++)
	{		

	
		pSetOffset = (BYTE *)m_dbParams.pData + (i*m_cbRowSize);

		if (FAILED(m_hr = FillInputBindings(m_pChangeTable,
											DBACCESSOR_PARAMETERDATA,	
											m_cBindings,	
											m_rgBindings,	
											&pSetOffset,
											ROW_SEED,
											cParamCols,	
											m_rgSelectOrds,					
											PRIMARY)))
		goto CLEANUP;

	}


CLEANUP:

	if (wszTempQuery)
		CMultResults::s_pIMalloc->Free(wszTempQuery);
	
	return m_hr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Case Section
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


// {{ TCW_TEST_CASE_MAP(TCGeneralGetResult)
//--------------------------------------------------------------------
// @class All Purpose GetResult Tests
//
class TCGeneralGetResult : public CTestBase { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();
	
public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(TCGeneralGetResult,CTestBase);
	// }} TCW_DECLARE_FUNCS_END
 
	//@cmember Performs thorough valid tests on the given 
	//multiple result generating command in rMultRes
	int TestValidMultResults(CMultResults& rMultRes, //Object to test
							REFIID  riidGetResult = IID_IRowset,//riid to pass to GetResult
							REFIID riidExecute = IID_IMultipleResults);	//riid to pass to Execute								

	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();
	
	// {{ TCW_TESTVARS()
	// @cmember Batch - insert, update, delete, update
	int Variation_1();
	// @cmember Batch - select, select, select
	int Variation_2();
	// @cmember Batch - select, insert, update, delete
	int Variation_3();
	// @cmember Batch - insert, update, delete, select
	int Variation_4();
	// @cmember Batch - select, insert, select
	int Variation_5();
	// @cmember Multiple ParamSets - select
	int Variation_6();
	// @cmember Multiple ParamSets - Insert
	int Variation_7();
	// @cmember Single - select
	int Variation_8();
	// @cmember Single - insert
	int Variation_9();
	// @cmember Batch - select, insert, delete; Ask for IID_IRowset on Execute
	int Variation_10();
	// @cmember Batch - insert, select, delete; Ask for IID_IRowset on Execute
	int Variation_11();
	// @cmember IMultipleResults AddRef(
	int Variation_12();
	// @cmember S_OK - riid == IAccessor
	int Variation_13();
	// @cmember S_OK - riid == IColumnsInfo
	int Variation_14();
	// @cmember S_OK - riid == IConverType
	int Variation_15();
	// @cmember S_OK - riid == IRowset
	int Variation_16();
	// @cmember S_OK - riid == IRowsetInfo
	int Variation_17();
	// @cmember S_OK - riid == IUnknown
	int Variation_18();
	// @cmember E_NOINTERFACE - riid == IID_IMultipleResults
	int Variation_19();
	// @cmember E_NOINTERFACE - riid == IRowsetUpdate
	int Variation_20();
	// @cmember DB_E_NOAGGREGATION - Valid pUnkOuter
	int Variation_21();
	// @cmember DB_E_OBJECTOPEN - Rowset with Open Rowset without support for multiple concurrent results
	int Variation_22();
	// @cmember E_INVALIDARG - lReserved != 0
	int Variation_23();
	// @cmember riid == IID_NULL, rowset returning results
	int Variation_24();
	// @cmember riid == IID_NULL, Non rowset returning results
	int Variation_25();
	// @cmember ppRowset = NULL, rowset returning results
	int Variation_26();
	// @cmember ppRowset != NULL, Non rowset returning results
	int Variation_27();
	// @cmember pcRowsAffected == NULL, rowset returning result
	int Variation_28();
	// @cmember pcRowsAffected == NULL, Non rowset returning result
	int Variation_29();
	// @cmember Multiple Executions of same command open at same time
	int Variation_30();
	// @cmember Select, insert, select - RestartPosition on first and last select
	int Variation_31();
	// @cmember DB_S_NORESULT - Call after receiving DB_S_NORESULT once
	int Variation_32();
	// @cmember DBPROP_IRowsetLocate - insert, update, delete
	int Variation_33();
	// @cmember DBPROP_IRowsetLocate - insert, select, delete
	int Variation_34();
	// @cmember DBPROP_IRowsetLocate - insert, select, select
	int Variation_35();
	// @cmember DBPROP_CANHOLDROWS
	int Variation_36();
	// @cmember E_NOINTERFACE - IID_IMultipleResults on IOpenRowset::OpenRowset
	int Variation_37();
	// @cmember E_NOINTERFACE - IID_IMultipleResults on IDBSchemaRowset::GetRowset
	int Variation_38();
	// @cmember Select with empty rowset, mixed with poulated rowsets
	int Variation_39();
	// @cmember Release IMultipleResults while Rowset open
	int Variation_40();
	// @cmember Rowset creation failure do to E_NOINTERFACE
	int Variation_41();
	// @cmember Rowset creation failure due to non forward only cursor
	int Variation_42();
	// @cmember Multiple ParamSets in a batch - select, insert, select
	int Variation_43();
	// @cmember Multiple ParamSets in a batch - insert, select, insert
	int Variation_44();
	// @cmember Multiple ParamSets in a batch - select, select, select
	int Variation_45();
	// @cmember single select, RestartPosition -- DB_S_COMMANDREEXECUTED
	int Variation_46();
	// @cmember S_OK - Select on 2nd command while processing GetResult on first command
	int Variation_47();
	// @cmember S_OK - Single select, ask for IID_IRowsetScroll
	int Variation_48();
	// @cmember Aggregated batch - select, select, select
	int Variation_49();
	// @cmember Aggregated Result - Select, Select, Select
	int Variation_50();
	// @cmember DBPROP_IMultipleResults - Execute with IID_IUnknown but DBPROP_IMultipleResults
	int Variation_51();
	// @cmember DB_E_INTEGRITYVIOLATION: Batch - select, insert, select. Fail insert.
	int Variation_52();
	// @cmember DB_E_NOAGGREGATION: Aggregated Result asking for IID != IID_IUnknown
	int Variation_53();
	// @cmember S_OK: IMultipleResults with compute by clause
	int Variation_54();
	// }} TCW_TESTVARS_END
};
// {{ TCW_TESTCASE(TCGeneralGetResult)
#define THE_CLASS TCGeneralGetResult
BEG_TEST_CASE(TCGeneralGetResult, CTestBase, L"All Purpose GetResult Tests")
	TEST_VARIATION(1, 		L"Batch - insert, update, delete, update")
	TEST_VARIATION(2, 		L"Batch - select, select, select")
	TEST_VARIATION(3, 		L"Batch - select, insert, update, delete")
	TEST_VARIATION(4, 		L"Batch - insert, update, delete, select")
	TEST_VARIATION(5, 		L"Batch - select, insert, select")
	TEST_VARIATION(6, 		L"Multiple ParamSets - select")
	TEST_VARIATION(7, 		L"Multiple ParamSets - Insert")
	TEST_VARIATION(8, 		L"Single - select")
	TEST_VARIATION(9, 		L"Single - insert")
	TEST_VARIATION(10, 		L"Batch - select, insert, delete; Ask for IID_IRowset on Execute")
	TEST_VARIATION(11, 		L"Batch - insert, select, delete; Ask for IID_IRowset on Execute")
	TEST_VARIATION(12, 		L"IMultipleResults AddRef(")
	TEST_VARIATION(13, 		L"S_OK - riid == IAccessor")
	TEST_VARIATION(14, 		L"S_OK - riid == IColumnsInfo")
	TEST_VARIATION(15, 		L"S_OK - riid == IConverType")
	TEST_VARIATION(16, 		L"S_OK - riid == IRowset")
	TEST_VARIATION(17, 		L"S_OK - riid == IRowsetInfo")
	TEST_VARIATION(18, 		L"S_OK - riid == IUnknown")
	TEST_VARIATION(19, 		L"E_NOINTERFACE - riid == IID_IMultipleResults")
	TEST_VARIATION(20, 		L"E_NOINTERFACE - riid == IRowsetUpdate")
	TEST_VARIATION(21, 		L"DB_E_NOAGGREGATION - Valid pUnkOuter")
	TEST_VARIATION(22, 		L"DB_E_OBJECTOPEN - Rowset with Open Rowset without support for multiple concurrent results")
	TEST_VARIATION(23, 		L"E_INVALIDARG - lReserved != 0")
	TEST_VARIATION(24, 		L"riid == IID_NULL, rowset returning results")
	TEST_VARIATION(25, 		L"riid == IID_NULL, Non rowset returning results")
	TEST_VARIATION(26, 		L"ppRowset = NULL, rowset returning results")
	TEST_VARIATION(27, 		L"ppRowset != NULL, Non rowset returning results")
	TEST_VARIATION(28, 		L"pcRowsAffected == NULL, rowset returning result")
	TEST_VARIATION(29, 		L"pcRowsAffected == NULL, Non rowset returning result")
	TEST_VARIATION(30, 		L"Multiple Executions of same command open at same time")
	TEST_VARIATION(31, 		L"Select, insert, select - RestartPosition on first and last select")
	TEST_VARIATION(32, 		L"DB_S_NORESULT - Call after receiving DB_S_NORESULT once")
	TEST_VARIATION(33, 		L"DBPROP_IRowsetLocate - insert, update, delete")
	TEST_VARIATION(34, 		L"DBPROP_IRowsetLocate - insert, select, delete")
	TEST_VARIATION(35, 		L"DBPROP_IRowsetLocate - insert, select, select")
	TEST_VARIATION(36, 		L"DBPROP_CANHOLDROWS")
	TEST_VARIATION(37, 		L"E_NOINTERFACE - IID_IMultipleResults on IOpenRowset::OpenRowset")
	TEST_VARIATION(38, 		L"E_NOINTERFACE - IID_IMultipleResults on IDBSchemaRowset::GetRowset")
	TEST_VARIATION(39, 		L"Select with empty rowset, mixed with poulated rowsets")
	TEST_VARIATION(40, 		L"Release IMultipleResults while Rowset open")
	TEST_VARIATION(41, 		L"Rowset creation failure do to E_NOINTERFACE")
	TEST_VARIATION(42, 		L"Rowset creation failure due to non forward only cursor")
	TEST_VARIATION(43, 		L"Multiple ParamSets in a batch - select, insert, select")
	TEST_VARIATION(44, 		L"Multiple ParamSets in a batch - insert, select, insert")
	TEST_VARIATION(45, 		L"Multiple ParamSets in a batch - select, select, select")
	TEST_VARIATION(46, 		L"single select, RestartPosition -- DB_S_COMMANDREEXECUTED")
	TEST_VARIATION(47, 		L"S_OK - Select on 2nd command while processing GetResult on first command")
	TEST_VARIATION(48, 		L"S_OK - Single select, ask for IID_IRowsetScroll")
	TEST_VARIATION(49, 		L"Aggregated batch - select, select, select")
	TEST_VARIATION(50, 		L"Aggregated Result - Select, Select, Select")
	TEST_VARIATION(51, 		L"DBPROP_IMultipleResults - Execute with IID_IUnknown but DBPROP_IMultipleResults")
	TEST_VARIATION(52, 		L"DB_E_INTEGRITYVIOLATION: Batch - select, insert, select. Fail insert.")
	TEST_VARIATION(53, 		L"DB_E_NOAGGREGATION: Aggregated Result asking for IID != IID_IUnknown")
	TEST_VARIATION(54, 		L"S_OK: IMultipleResults with compute by clause")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END


// {{ TCW_TEST_CASE_MAP(TCTxn)
//--------------------------------------------------------------------
// @class Tests Rowset behavior upon ending aTransaction
//
class TCTxn : public CTestBase { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();
	
public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(TCTxn,CTestBase);
	// }} TCW_DECLARE_FUNCS_END
 
	//@cmember Flag indicatign preservation of rowset on commit
	BOOL	m_fCommitPreserve;

	//@cmember Flag indicatign preservation of rowset on commit
	BOOL	m_fAbortPreserve;

	//@cmember Helper function to do all zombie testing for this testcase
	int TCTxn::TestTxn(ETXN	eTxn, BOOL	fRetaining);

	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();
	
	// {{ TCW_TESTVARS()
	// @cmember Commit Retaining
	int Variation_1();
	// @cmember Commit NonRetaining
	int Variation_2();
	// @cmember Abort Retaining
	int Variation_3();
	// @cmember Abort NonRetaining
	int Variation_4();
	// }} TCW_TESTVARS_END
};
// {{ TCW_TESTCASE(TCTxn)
#define THE_CLASS TCTxn
BEG_TEST_CASE(TCTxn, CTestBase, L"Tests Rowset behavior upon ending aTransaction")
	TEST_VARIATION(1, 		L"Commit Retaining")
	TEST_VARIATION(2, 		L"Commit NonRetaining")
	TEST_VARIATION(3, 		L"Abort Retaining")
	TEST_VARIATION(4, 		L"Abort NonRetaining")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END


// }} END_DECLARE_TEST_CASES()

// {{ TCW_TESTMODULE(ThisModule)
TEST_MODULE(2, ThisModule, gwszModuleDescrip)
	TEST_CASE(1, TCGeneralGetResult)
	TEST_CASE(2, TCTxn)
END_TEST_MODULE()
// }} TCW_TESTMODULE_END


// {{ TCW_TC_PROTOTYPE(TCGeneralGetResult)
//*-----------------------------------------------------------------------
//| Test Case:		TCGeneralGetResult - All Purpose GetResult Tests
//|	Created:			09/22/96
//*-----------------------------------------------------------------------

//--------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL TCGeneralGetResult::Init()
{
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CTestBase::Init())
	// }}
	{
		return TRUE;
	}
	return FALSE;
}


//--------------------------------------------------------------------
// @mfunc Does valid testing of IMultipleResults
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::TestValidMultResults(CMultResults& rMultRes,  
											 REFIID riidGetResult,
											 REFIID riidExecute)
{
	//Generate the result(s)		
	if (CHECK(rMultRes.SetAndExecute(riidExecute), S_OK))
		//Make sure they are correct, specifying we haven't
		//processed any of them ourselves already
		if (CHECK(rMultRes.ProcessAllResults(0, riidExecute, riidGetResult), S_OK))
			return TEST_PASS;

	//Problems!
	return TEST_FAIL;

}

// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Batch - insert, update, delete, update
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_1()
{
	
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,										
									EUPDATE,
									EDELETE,
									EUPDATE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);

}
// }}


// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Batch - select, select, select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_2()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									ESELECT,										
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);

}
// }}


// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Batch - select, insert, update, delete
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_3()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EINSERT,
									EUPDATE,
									EDELETE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);

}
// }}


// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Batch - insert, update, delete, select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_4()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,										
									EUPDATE,
									EDELETE,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);

}
// }}


// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Batch - select, insert, select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_5()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EINSERT,
									ESELECT									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);

}
// }}


// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Multiple ParamSets - select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_6()
{
	CParamSets			oParamSets(5,	//Use five paramter sets
							m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT
									};

	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oParamSets.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;
	

	//Test that all results are correct
	return TestValidMultResults(oParamSets);

}
// }}


// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Multiple ParamSets - Insert
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_7()
{
	CParamSets			oParamSets(8,	//Use 8 paramter sets
							m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT
									};

	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oParamSets.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct.  
	return TestValidMultResults(oParamSets);

}
// }}


// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Single - select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_8()
{
	CBatch			oSingle(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oSingle.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oSingle);

}
// }}


// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Single - insert
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_9()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,										
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);
}
// }}


// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Batch - select, insert, delete; Ask for IID_IRowset on Execute
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_10()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,
									EINSERT,
									EDELETE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch, IID_IRowset, IID_IRowset);
}
// }}


// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Batch - insert, select, delete; Ask for IID_IRowset on Execute
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_11()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,
									ESELECT,
									EDELETE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch, IID_IRowset, IID_IRowset);
}
// }}


// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc IMultipleResults AddRef(
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_12()
{	
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;

	
	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults), S_OK))			
	{
		//Do a net ref count of zero
		pMultResults->m_pIMultResults->AddRef();
		pMultResults->m_pIMultResults->Release();
		pMultResults->m_pIMultResults->AddRef();
		pMultResults->m_pIMultResults->AddRef();
		pMultResults->m_pIMultResults->Release();
		pMultResults->m_pIMultResults->AddRef();
		pMultResults->m_pIMultResults->Release();
		pMultResults->m_pIMultResults->Release();

		//Only count we are guaranteed of is 0, and we
		//should be there right now
		if (COMPARE(pMultResults->m_pIMultResults->Release(), 0))
		{
			fResults = TRUE;
			pMultResults->m_pIMultResults = NULL;
		}
	
		delete pMultResults;

	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc S_OK - riid == IAccessor
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_13()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,
									ESELECT,
									EDELETE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Verify we can get IID_IAccessor on all rowset returning results
	return TestValidMultResults(oBatch,  IID_IAccessor);	
}
// }}


// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc S_OK - riid == IColumnsInfo
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_14()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																													
									ESELECT,
									EDELETE,
									EINSERT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Verify we can get IID_IAccessor on all rowset returning results
	return TestValidMultResults(oBatch,  IID_IColumnsInfo);	
}
// }}


// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc S_OK - riid == IConverType
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_15()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,
									ESELECT,
									EDELETE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Verify we can get IID_IAccessor on all rowset returning results
	return TestValidMultResults(oBatch,  IID_IConvertType);	
}
// }}


// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc S_OK - riid == IRowset
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_16()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									ESELECT,
									ESELECT,
									EDELETE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Verify we can get IID_IAccessor on all rowset returning results
	return TestValidMultResults(oBatch,  IID_IRowset);	
}
// }}


// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc S_OK - riid == IRowsetInfo
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_17()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									ESELECT,
									ESELECT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Verify we can get IID_IAccessor on all rowset returning results
	return TestValidMultResults(oBatch,  IID_IRowsetInfo);	
}
// }}


// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc S_OK - riid == IUnknown
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_18()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,
									ESELECT,
									EDELETE,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Verify we can get IID_IAccessor on all rowset returning results
	return TestValidMultResults(oBatch,  IID_IUnknown);	
}
// }}


// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc E_NOINTERFACE - riid == IID_IMultipleResults
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_19()
{
	IRowset * pIRowset = (IRowset *)0x12345678;	//Init so we know if it's nulled
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {																			
									EINSERT,
									ESELECT,											
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	

	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
	{
		//Do a successful call
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_NULL, 
						
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowset), 
															S_OK)) 
		{
			COMPARE(pIRowset, NULL);
			COMPARE(pMultResults->m_cRowsGetResultAffected, 1);
			if(pIRowset && (pIRowset != (IUnknown *)0x12345678))
				pIRowset->Release();
			pIRowset = (IRowset *)0x12345678;
			
			//Try unsupported IID
			if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
																0, 
																IID_IMultipleResults, 
																&pMultResults->m_cRowsGetResultAffected, 
																(IUnknown **)&pIRowset), 
																E_NOINTERFACE))
				if ((pMultResults->CheckErrorOutParams(pIRowset))&&(COMPARE(pMultResults->m_cRowsGetResultAffected,-1)) )
					//the current is lost. Now verify the next one
					if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
																		0, 
																		IID_IRowset, 
																		&pMultResults->m_cRowsGetResultAffected, 
																		(IUnknown **)&pIRowset), 
																		S_OK))
					{
								
						if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))				
							fResults = TRUE;
						pIRowset->Release();
						pIRowset = NULL;
					}
				
		}
	}
	
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}

	
	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(20)
//*-----------------------------------------------------------------------
// @mfunc E_NOINTERFACE - riid == IRowsetUpdate
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_20()
{
	IRowsetUpdate * pIRowUpdate = (IRowsetUpdate *)0x12345678;//Init so we know if it's nulled
	IUnknown *		pIUnknown = (IUnknown *)0x12345678;	//Init so we know if it's nulled
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	

	ESQLSTMT 		rgeSQLStmts[] = {																			
									EINSERT,
									ESELECT,											
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	

	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
	{
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0, 
														IID_IUnknown, 
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIUnknown), S_OK))
			if ( (COMPARE(pIUnknown, NULL))&&(COMPARE(pMultResults->m_cRowsGetResultAffected, 1)) )
				fResults = TRUE;
			else if(pIUnknown && (pIUnknown != (IUnknown *)0x12345678))
				pIUnknown->Release();
			pIUnknown = (IUnknown *)0x12345678;

		//Try unsupported IID		
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0, 
														IID_IRowsetUpdate, 
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIRowUpdate), E_NOINTERFACE))
		{	
			if ((COMPARE(pIRowUpdate, NULL))&&(COMPARE(pMultResults->m_cRowsGetResultAffected, -1)) )					
				fResults &= TRUE;
			else if(pIRowUpdate && (pIRowUpdate != (IRowsetUpdate *)0x12345678))
			{
				fResults = FALSE;
				pIRowUpdate->Release();
			}
		}

		//Now verify that we have no result, since current is lost
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IUnknown, 
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIUnknown), DB_S_NORESULT))
			if( (COMPARE(pIUnknown, NULL))&&(COMPARE(pMultResults->m_cRowsGetResultAffected, -1)) )
				fResults &= TRUE;
	}											
	
	if(pIUnknown && (pIUnknown!= (IUnknown *)0x12345678))
		COMPARE(pIUnknown->Release(), 0);
	
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;
	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(21)
//*-----------------------------------------------------------------------
// @mfunc DB_E_NOAGGREGATION - Valid pUnkOuter
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_21()
{
	IUnknown * pIUnknown = (IUnknown *)0x87654321;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	//We are faking that this is a valid pointer
	//for the purpose of pretending to aggregate.
	//We should be able to pass this and just not
	//do anything on the aggregated object to be safe.
	IUnknown *		pValidUnk = new CFakeUnk;	
	
	if (!pValidUnk)
		return TEST_FAIL;

	
	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults), S_OK))	
	{
		//Try "valid" punkouter
		m_hr = pMultResults->m_pIMultResults->GetResult(pValidUnk, 
														0, 
														IID_IUnknown,	//Must ask for IUnknown
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIUnknown);

		//Either return code is acceptable
		if (m_hr == S_OK)
		{
			if(pIUnknown && (pIUnknown!=(IUnknown *)0x87654321))
				pIUnknown->Release();
			pIUnknown = NULL;
			//Make sure the rest of the results are right
			fResults = CHECK(pMultResults->ProcessAllResults(1), S_OK);

		}

		if (m_hr == DB_E_NOAGGREGATION)
		{
			//Make sure parameters were nulled out on error
			if (pMultResults->CheckErrorOutParams(pIUnknown))				
				fResults = TRUE;
			//Provider should allow us to get next result on this error code
			if (CHECK(pMultResults->ProcessAllResults(0), S_OK))		
				fResults &= TRUE;
			else
				fResults = FALSE;

		}
		if (pIUnknown &&(pIUnknown != (IUnknown *)0x87654321))
			pIUnknown->Release();			
			pIUnknown = NULL;
	}
		
	
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}

	if (pValidUnk)
		delete pValidUnk;

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(22)
//*-----------------------------------------------------------------------
// @mfunc DB_E_OBJECTOPEN - Rowset with Open Rowset without support for multiple concurrent results
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_22()
{
	BOOL		 fResults = FALSE;
	ULONG		 ulValue;
	IRowset *	 pFirstRowset = NULL;
	IRowset *	 pSecondRowset = NULL;
	CBatch		 oBatch(m_pIDBCreateCommand, 
						m_pICommandText,
						m_pSelectTable,
						m_pChangeTable);	
	ESQLSTMT 	 rgeSQLStmts[] = {																				
								  ESELECT,
								  ESELECT,
								  ESELECT									
								 };
	ULONG		 ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	if ((GetProperty(DBPROP_MULTIPLERESULTS, DBPROPSET_DATASOURCEINFO, m_pThisTestModule->m_pIUnknown, &ulValue)) && 
		!(ulValue & DBPROPVAL_MR_CONCURRENT))
	{
		// Initialize batch statement with the proper SQL for this variation
		if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
			return TEST_FAIL;
		
		if (CHECK(oBatch.SetAndExecute(IID_IMultipleResults),S_OK))
		{
			//Open first rowset
			if (CHECK(oBatch.m_pIMultResults->GetResult(NULL, 0, IID_IRowset,
						NULL, (IUnknown **)&pFirstRowset), S_OK))
			{
												
				if (CHECK(oBatch.m_pIMultResults->GetResult(NULL, 0, 
													IID_IRowset,
													&oBatch.m_cRowsGetResultAffected, 
													(IUnknown **)&pSecondRowset), DB_E_OBJECTOPEN))						
					if (oBatch.CheckErrorOutParams(pSecondRowset))
						fResults = TRUE;
				
				//now close the rowset object
				pFirstRowset->Release();
				pFirstRowset = NULL;

				//Provider should allow us to get next result on this error code
				if (CHECK(oBatch.ProcessAllResults(1), S_OK))		
					fResults &= TRUE;
				else
					fResults = FALSE;
			}

			if(pSecondRowset)
				pSecondRowset->Release();
			pSecondRowset = NULL;

			if(pFirstRowset)
				pFirstRowset->Release();	
			pFirstRowset = NULL;

			//Clean up from SetAndExecute
			oBatch.ReleaseIMultipleResults();			
		}
	}
	else
	{
		// Current results are supported, test is not applicable
		odtLog << L"Current results are supported, test is not applicable.\n";
		fResults = TEST_SKIPPED;
	}

	return fResults;
}
// }}


// {{ TCW_VAR_PROTOTYPE(23)
//*-----------------------------------------------------------------------
// @mfunc E_INVALIDARG - lReserved != 0
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_23()
{
	IRowset * pIRowset = (IRowset *) 0x87654321;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	
	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults), S_OK))				
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														1,	//Make lReserved Non Zero
														IID_IRowset, 
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIRowset),
														E_INVALIDARG))
		{
			if (pMultResults->CheckErrorOutParams(pIRowset))				
				fResults = TRUE;
			//In case provider is incorrectly giving us a rowset, 
			//release it so the open object doesn't hose the
			//rest of our variations
			if (pIRowset&&(pIRowset!=(IRowset *)0x87654321))
				pIRowset->Release();
			pIRowset = NULL;
			
			//Provider should allow us to get next result on this error code
			if (CHECK(pMultResults->ProcessAllResults(0), S_OK))		
				fResults &= TRUE;
			else
				fResults = FALSE;
		}

	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{		
		pMultResults->ReleaseIMultipleResults();			
		delete pMultResults;				

	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(24)
//*-----------------------------------------------------------------------
// @mfunc riid == IID_NULL, rowset returning results
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_24()
{
	IRowset * pIRowset = (IRowset *) 0x87654321;
	//IRowset * pIRowset = NULL;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									ESELECT,	//Start with rowset returning
									EINSERT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Get an IMultipleResults interface, use our own SQLStmts
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
	{		
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0,
														IID_NULL, //Test IID
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIRowset),
														S_OK))
		{
			//Check row count
			if (COMPARE(pMultResults->IsGetResultRowsAffectedRight(0), TRUE))
				//Interface must be nulled
				if (COMPARE(pIRowset, NULL))
					//Make sure the rest of the results are OK (we processed the first one already)
					if (CHECK(pMultResults->ProcessAllResults(1), S_OK))		
						fResults = TRUE;

	
		}
		if((pIRowset)&&(pIRowset!=(IRowset *)0x87654321))
			pIRowset->Release();
		pIRowset = NULL;

	}
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;
		
	}
	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(25)
//*-----------------------------------------------------------------------
// @mfunc riid == IID_NULL, Non rowset returning results
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_25()
{
	IRowset * pIRowset = (IRowset *) 0x87654321;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,	//Start with non rowset returning
									ESELECT,
									EINSERT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Get an IMultipleResults interface, use our own SQLStmts
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
			
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0,
														IID_NULL, //Test IID
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIRowset),
														S_OK))
		
			//It should be just like an error, outparams nulled
			if (COMPARE(pMultResults->IsGetResultRowsAffectedRight(0), TRUE))
				//Make sure the rest of the results are OK (we processed the first one already)
				if (CHECK(pMultResults->ProcessAllResults(1), S_OK))		
					fResults = TRUE;
	
	if((pIRowset)&&(pIRowset!=(IRowset *)0x87654321))
		pIRowset->Release();
	pIRowset = NULL;

	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();
		delete pMultResults;
	
	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(26)
//*-----------------------------------------------------------------------
// @mfunc ppRowset = NULL, rowset returning results
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_26()
{	
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									ESELECT,	//Start with rowset returning
									EINSERT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Get an IMultipleResults interface, use our own SQLStmts
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
			
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0,
														IID_IRowset, 
														&pMultResults->m_cRowsGetResultAffected, 
														NULL),	//Test NULL ppRowset
														S_OK))
			//Check row count
			if (COMPARE(pMultResults->IsGetResultRowsAffectedRight(0), TRUE))
				//Make sure the rest of the results are OK (we processed the first one already)
				if (CHECK(pMultResults->ProcessAllResults(1), S_OK))		
					fResults = TRUE;
		

	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;
	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(27)
//*-----------------------------------------------------------------------
// @mfunc ppRowset != NULL, Non rowset returning results
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_27()
{	
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	IRowset *		pIRowset = (IRowset *)0x12345678;
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,	//Start with non rowset returning
									ESELECT,
									EINSERT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Get an IMultipleResults interface, use our own SQLStmts
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
			
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0,
														IID_IRowset, 
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIRowset),
														S_OK))
			
			if (COMPARE(pIRowset, NULL))
				if (COMPARE(pMultResults->IsGetResultRowsAffectedRight(0), TRUE))
					if (CHECK(pMultResults->ProcessAllResults(1), S_OK))		
						fResults = TRUE;
		
	
	if((pIRowset)&&(pIRowset!=(IRowset *)0x12345678))
		pIRowset->Release();
	pIRowset = NULL;

	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;
	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(28)
//*-----------------------------------------------------------------------
// @mfunc pcRowsAffected == NULL, rowset returning result
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_28()
{

	IRowset *		pIRowset = NULL;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									ESELECT,	//Start with rowset returning
									EINSERT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Get an IMultipleResults interface, use our own SQLStmts
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
			
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0,
														IID_IRowset, 
														NULL, //Try NULL pcRowsAffected
														(IUnknown **)&pIRowset),	
														S_OK))
			//It should still be valid rowset
			if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))
			{
			
				if (pIRowset)
					pIRowset->Release();
				pIRowset = NULL;

				//Make sure the rest of the results are OK (we processed the first one already)
				if (CHECK(pMultResults->ProcessAllResults(1), S_OK))		
					fResults = TRUE;
			}

	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();
		delete pMultResults;

	}

	if (pIRowset)
		pIRowset->Release();
	pIRowset = NULL;

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(29)
//*-----------------------------------------------------------------------
// @mfunc pcRowsAffected == NULL, Non rowset returning result
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_29()
{
	IRowset *		pIRowset = (IRowset *)0x12345678;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;	
	ESQLSTMT 		rgeSQLStmts[] = {																				
									EINSERT,	//Start with non rowset returning
									ESELECT,
									EINSERT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Get an IMultipleResults interface, use our own SQLStmts
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
			
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0,
														IID_IRowset, 
														NULL, //Try NULL pcRowsAffected
														(IUnknown **)&pIRowset),	
														S_OK))
		{	
			//It should be just like an error, outparams nulled
			if (pIRowset == NULL)
				//Make sure the rest of the results are OK (we processed the first one already)
				if (CHECK(pMultResults->ProcessAllResults(1), S_OK))		
					fResults = TRUE;
			if((pIRowset)&&(pIRowset!=(IRowset *)0x12345678))
				pIRowset->Release();
			pIRowset = NULL;
		}

	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();
		delete pMultResults;

	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(30)
//*-----------------------------------------------------------------------
// @mfunc Multiple Executions of same command open at same time
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_30()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EUPDATE,
									ESELECT,
									EUPDATE
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	IMultipleResults * pIMultResults1 = NULL;
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;


	//Puts interface in m_pIRowset
	if (CHECK(oBatch.SetAndExecute(IID_IRowset), S_OK))
	{
		//Puts interface in m_pIMultResults
		if (CHECK(oBatch.Execute(IID_IMultipleResults, NULL), S_OK))
		{
			//Save this interface so we can write over it to create a new one
			pIMultResults1 = oBatch.m_pIMultResults;

			//Create another IMultipleResults via another execution
			if (CHECK(oBatch.Execute(IID_IMultipleResults, NULL), S_OK))
			{
				CHECK(oBatch.ProcessAllResults(0), S_OK);
				
				//Now check results of first IMultResults interface
				oBatch.m_pIMultResults = pIMultResults1;
				CHECK(oBatch.ProcessAllResults(0), S_OK);
			}

			//Try to cleanup in case we had a failure and didn't get to cleanup above
			oBatch.ReleaseIMultipleResults();
			
		}
	
		//Now check single IRowset
		CHECK(oBatch.VerifySelectRowset(IID_IRowset, oBatch.m_pIRowset), S_OK);
		//And Release it
		oBatch.ReleaseIRowset();		

	}

	//Count on our CHECKs to do any necessary error incrementing
	return TEST_PASS;

}
// }}


// {{ TCW_VAR_PROTOTYPE(31)
//*-----------------------------------------------------------------------
// @mfunc Select, insert, select - RestartPosition on first and last select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_31()
{

	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EINSERT,
									ESELECT									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	//CBatch *		poBatch = NULL;
	IRowset * pIRowset = NULL;
	BOOL			fResults = TRUE;
	CMultResults *	pMultResults = NULL;	
	ULONG			cRowsObtained;
	HROW 			rghRows[1];
	HROW *			prghRows=rghRows;


	////////////////////////////////////////////////
	//This is a ODBC Provider specific test!
	////////////////////////////////////////////////
	if (!g_fKagera && !g_fSQLOLEDB)
		return TEST_SKIPPED;

	//Create a multiple results object
	//if (CHECK(SetUpGetResult((CMultResults **)&poBatch, ceSQLStmts, rgeSQLStmts), S_OK))
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))
	{

		if (CHECK((pMultResults->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&pMultResults->m_cRowsGetResultAffected,
													(IUnknown **)&(pIRowset)), S_OK))	
		{
			//Need to reexecute, which should be impossible
			//since we don't want the undesireable side affects
			//of reexecuting the whole batch	
			if(pIRowset)
			{
				// We have to retrieve data before DB_S_COMMANDREEXECUTED will be returned by 
				// some providers
				if (CHECK(pIRowset->GetNextRows(NULL, 0, 1, &cRowsObtained, &prghRows), S_OK))
				{
					if (CHECK(pIRowset->ReleaseRows(1, rghRows, NULL, NULL, NULL), S_OK))
					{
						if (CHECK(m_hr = pIRowset->RestartPosition(0), DB_S_COMMANDREEXECUTED))
							fResults = TRUE;
					}
				}
			
				pIRowset->Release();
				pIRowset = NULL;
			}
			else 
				fResults = FALSE;
			
			if (CHECK((pMultResults->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&pMultResults->m_cRowsGetResultAffected,
													(IUnknown **)&(pIRowset)), S_OK))	
			{
				COMPARE(pIRowset, NULL);
				COMPARE(pMultResults->IsGetResultRowsAffectedRight(1), TRUE);
				if(pIRowset)
				{
					pIRowset->Release();
					pIRowset = NULL;
				}
			}
			else
				fResults = FALSE;

			if (CHECK((pMultResults->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&pMultResults->m_cRowsGetResultAffected,
													(IUnknown **)&(pIRowset)), S_OK))	
			{
				if(pIRowset)
				{
					// We have to retrieve data before DB_S_COMMANDREEXECUTED will be returned by 
					// some providers
					if (CHECK(pIRowset->GetNextRows(NULL, 0, 1, &cRowsObtained, &prghRows), S_OK))
					{
						if (CHECK(pIRowset->ReleaseRows(1, rghRows, NULL, NULL, NULL), S_OK))
						{
							if (CHECK(m_hr = pIRowset->RestartPosition(0), DB_E_CANNOTRESTART))
								fResults = TRUE;
						}
					}

					pIRowset->Release();
					pIRowset = NULL;
				}
			}
			else
				fResults = FALSE;

		}
		else 
			fResults = FALSE;

		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}
	else
		fResults = FALSE;

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(32)
//*-----------------------------------------------------------------------
// @mfunc DB_S_NORESULT - Call after receiving DB_S_NORESULT once
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_32()
{
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EINSERT,
									ESELECT									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch *		poBatch = NULL;

	//Create a multiple results object
	if (CHECK(SetUpGetResult((CMultResults **)&poBatch, ceSQLStmts, rgeSQLStmts), S_OK))
	{

		while ( (m_hr = (poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)) )
					!= DB_S_NORESULT)	
		{
			
			poBatch->ReleaseIRowset();
			//Get out of loop if we receive an error
			if (m_hr != DB_S_NORESULT && m_hr != S_OK)
				break;
		}
		
		//Make sure we did end correctly
		CHECK(m_hr, DB_S_NORESULT);
		//Now make sure we get the same return code again
		CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)), DB_S_NORESULT);

		poBatch->ReleaseIRowset();
		poBatch->ReleaseIMultipleResults();		
		delete poBatch;

		return TEST_PASS;
	}


	return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(33)
//*-----------------------------------------------------------------------
// @mfunc DBPROP_IRowsetLocate - insert, update, delete
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_33()
{
		
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,										
									EUPDATE,
									EDELETE									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch *		poBatch = NULL;
	BOOL			fResults = TRUE;	//In case IRowsetLocate isn't supported

	////////////////////////////////////////////////////////////////////////////////////////////////
	//This is a Provider specific test due to the use of batch SQL supported by SQL Server!
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (!g_fKagera && !g_fSQLOLEDB)
		return TEST_SKIPPED;

	//Only continue if we can set this property
	if (SUCCEEDED(SetRowsetPropertyOn(DBPROP_IRowsetLocate)))
	{
		fResults = FALSE;
		
		// Create a multiple results object
		// It is provider specific whether Execute can succeed with batch SQL and IRowsetLocate
		// property.
		if (SUCCEEDED(SetUpGetResult((CMultResults **)&poBatch, ceSQLStmts, rgeSQLStmts)))
		{

			//Check the insert results
			if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
				if (COMPARE(poBatch->AreGetResultOutParamsRight(0, poBatch->m_pIRowset, IID_IRowsetLocate), TRUE))
				{
					poBatch->ReleaseIRowset();	
					//Check the update results
					if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL,
													0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
						if (COMPARE(poBatch->AreGetResultOutParamsRight(1, poBatch->m_pIRowset, IID_IRowsetLocate), TRUE))
						{
							poBatch->ReleaseIRowset();	
							//Check the delete results
							if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
																	0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
								if (COMPARE(poBatch->AreGetResultOutParamsRight(2, poBatch->m_pIRowset, IID_IRowsetLocate), TRUE))
									fResults = TRUE;
						}
				}
			//Now free everything
			poBatch->ReleaseIRowset();	
			poBatch->ReleaseIMultipleResults();

			if (poBatch)
				delete poBatch;
		}
		else
		{
			odtLog<<L"It is provider specific whether Execute succeeds for batch SQL and DBPROP_IRowsetLocate"<<ENDL;
			odtLog<<L"Execute failure is allowed but should be verified that it's not a provider bug"<<ENDL;
			fResults = TRUE;
		}
		
		//Go back to a normal command
		CHECK(SetRowsetPropertyDefault(DBPROP_IRowsetLocate), S_OK);
	}

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(34)
//*-----------------------------------------------------------------------
// @mfunc DBPROP_IRowsetLocate - insert, select, delete
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_34()
{
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,										
									ESELECT,
									EDELETE									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch *		poBatch = NULL;
	IRowsetLocate * pIRowLoc1 = NULL;	
	BOOL			fResults = TRUE;
	HRESULT			hr = E_FAIL;
		
	////////////////////////////////////////////////////////////////////////////////////////////////
	//This is a Provider specific test due to the use of batch SQL supported by SQL Server!
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (!g_fKagera && !g_fSQLOLEDB)
		return TEST_SKIPPED;

	//Only continue if we can set this property
	if (SUCCEEDED(SetRowsetPropertyOn(DBPROP_IRowsetLocate)))
	{
		fResults = FALSE;

		//Create a multiple results object.  Assuming 
		//that the only cursor type that can be returned here is forward only, read only,
		//we should expect DB_E_ERRORSOCCURRED from ODBC Provider, but not until GetResult 
		//is called, since we expect the insert to succeed.
		if (CHECK(SetUpGetResult((CMultResults **)&poBatch, ceSQLStmts, rgeSQLStmts), S_OK))
		{

			//Check the insert results
			if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
				if (COMPARE(poBatch->AreGetResultOutParamsRight(0, poBatch->m_pIRowset, IID_IRowsetLocate), TRUE))
			
					// Check the select.  Since the required interface is not available
					// this should return E_NOINTERFACE.
					hr = (poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&pIRowLoc1);
					
					if (hr == S_OK)
					{
						if (CHECK(TryLocate(pIRowLoc1), S_OK))

							//Check the delete
							if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
																	0, 
												IID_IRowsetLocate,
												&poBatch->m_cRowsGetResultAffected,
												(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
								if (COMPARE(poBatch->AreGetResultOutParamsRight(2, 
																				poBatch->m_pIRowset, IID_IRowsetLocate), 
																				TRUE))
									fResults = TRUE;
					}
					else
					{
						// I'd really like E_NOINTERFACE, but if they detect they can't
						// support the required prop we might get DB_E_ERRORSOCCURRED
						if (hr != DB_E_ERRORSOCCURRED)
							fResults = CHECK(hr, E_NOINTERFACE);
					}
				
		}
		
		//Now free everything
		if (poBatch)
		{
			poBatch->ReleaseIRowset();

			SAFE_RELEASE(pIRowLoc1);

			poBatch->ReleaseIMultipleResults();

			delete poBatch;
		}
		else
		{
			odtLog<<L"It is provider specific whether Execute succeeds for batch SQL and DBPROP_IRowsetLocate"<<ENDL;
			odtLog<<L"Execute failure is allowed but should be verified that it's not a provider bug"<<ENDL;
			fResults = TRUE;
		}

		//Go back to a normal command
		CHECK(SetRowsetPropertyDefault(DBPROP_IRowsetLocate), S_OK);
	}

	
	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(35)
//*-----------------------------------------------------------------------
// @mfunc DBPROP_IRowsetLocate - insert, select, select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_35()
{
	
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,										
									ESELECT,
									ESELECT									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch *		poBatch = NULL;
	BOOL			fResults = TRUE;	//In case IRowsetLocate isn't supported
	HRESULT			hr = E_FAIL;
	IRowsetLocate * pIRowLoc1 = NULL;	

	////////////////////////////////////////////////////////////////////////////////////////////////
	//This is a Provider specific test due to the use of batch SQL supported by SQL Server!
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (!g_fKagera && !g_fSQLOLEDB)
		return TEST_SKIPPED;


	//Only continue if we can set this property
	if (SUCCEEDED(SetRowsetPropertyOn(DBPROP_IRowsetLocate)))
	{
		fResults = FALSE;

		//Create a multiple results object.  Assuming 
		//that the only cursor type that can be returned here is forward only, read only,
		//we should expect DB_E_ERRORSOCCURRED from ODBC Provider, but not until GetResult 
		//is called, since we expect the insert to succeed.
		if (CHECK(SetUpGetResult((CMultResults **)&poBatch, ceSQLStmts, rgeSQLStmts), S_OK))
		{

			//Check the insert results
			if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
				if (COMPARE(poBatch->AreGetResultOutParamsRight(0, poBatch->m_pIRowset, IID_IRowsetLocate), TRUE))
			
					// Check the select.  Since the required interface is not available
					// this should return E_NOINTERFACE.
					hr = (poBatch->m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowsetLocate,
													&poBatch->m_cRowsGetResultAffected,
													(IUnknown **)&pIRowLoc1);
					
					if (hr == S_OK)
					{
						if (CHECK(TryLocate(pIRowLoc1), S_OK))

							//Check the delete
							if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
																	0, 
												IID_IRowsetLocate,
												&poBatch->m_cRowsGetResultAffected,
												(IUnknown **)&(poBatch->m_pIRowset)), S_OK))
								if (COMPARE(poBatch->AreGetResultOutParamsRight(2, 
																				poBatch->m_pIRowset, IID_IRowsetLocate), 
																				TRUE))
									fResults = TRUE;
					}
					else
					{
						// I'd really like E_NOINTERFACE, but if they detect they can't
						// support the required prop we might get DB_E_ERRORSOCCURRED
						if (hr != DB_E_ERRORSOCCURRED)
							fResults = CHECK(hr, E_NOINTERFACE);
					}

		}
			

		//Now free everything
		if (poBatch)
		{
			SAFE_RELEASE(pIRowLoc1);
			poBatch->ReleaseIRowset();
			poBatch->ReleaseIMultipleResults();
			delete poBatch;
		}
		
		//Go back to a normal command
		CHECK(SetRowsetPropertyDefault(DBPROP_IRowsetLocate), S_OK);
	}

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(36)
//*-----------------------------------------------------------------------
// @mfunc DBPROP_CANHOLDROWS
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_36()
{
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EDELETE,
									ESELECT									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch *		poBatch = NULL;
	BOOL			fResults = TRUE;	//In case IRowsetLocate isn't supported
	HRESULT			hr = E_FAIL;
	
	
	////////////////////////////////////////////////
	//This is a ODBC Provider specific test!
	////////////////////////////////////////////////
	if (!g_fKagera)
	{
		odtLog << L"This is an ODBC Provider specific test.\n";
		return TEST_SKIPPED;
	}
	
	//Only continue if we can set this property
	if (SUCCEEDED(SetRowsetPropertyOn(DBPROP_CANHOLDROWS)))
	{
		fResults  = FALSE;

		//Create a multiple results object.  Expect that with two selects
		//in the batch we can't support CANHOLDROWS
		hr = SetUpGetResult((CMultResults **)&poBatch, ceSQLStmts, rgeSQLStmts);
		// Some providers will return DB_E_ERRORSINCOMMAND because they can't distinguish 
		// a property failure.
		if (hr == DB_E_ERRORSINCOMMAND || CHECK(hr, DB_E_ERRORSOCCURRED))
		{								
			fResults = TRUE;
		}

		if (poBatch)
		{
			poBatch->ReleaseIRowset();			
			poBatch->ReleaseIMultipleResults();
			delete poBatch;
		}
		
		//Go back to a normal command
		CHECK(SetRowsetPropertyDefault(DBPROP_CANHOLDROWS), S_OK);
	}

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(37)
//*-----------------------------------------------------------------------
// @mfunc E_NOINTERFACE - IID_IMultipleResults on IOpenRowset::OpenRowset
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_37()
{
	ESQLSTMT 		rgeSQLStmts[] = {ESELECT};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch			oSingle(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	IOpenRowset *	pIOpenRowset = NULL;
	IMultipleResults * pIMultRes = NULL;
	IRowset *		pIRowset = NULL;
	BOOL			fResults = FALSE;
	DBID			TableID;
	HRESULT			hr = E_FAIL;

	TableID = m_pSelectTable->GetTableID();
	
	
	//This interface is optional, so pass if we don't support it
	if (VerifyInterface(m_pThisTestModule->m_pIUnknown2, IID_IOpenRowset,
		SESSION_INTERFACE, (IUnknown **)&pIOpenRowset))
	{
		
		hr = pIOpenRowset->OpenRowset(NULL, 
					&TableID, 
					NULL, 
					IID_IMultipleResults,	//Shouldn't work
					0, 
					NULL, 
					(IUnknown **)&pIMultRes); 

		
		if (hr == E_NOINTERFACE)
			fResults = COMPARE(pIMultRes, NULL);
		else if (hr == S_OK)
		{
			// Set up batch for ease in verification.
			// Note: We assume OpenRowset is equivalent to "select *"
			TESTC(pIMultRes != NULL);

			//Initialize batch statement with the proper SQL for this variation
			if (!oSingle.FInit(ceSQLStmts, rgeSQLStmts))	
				goto CLEANUP;

			//Set the imultres interface
			oSingle.m_pIMultResults = pIMultRes;
			pIMultRes->AddRef();	// Because it gets released by ProcessAllResults.

			//Test that all results are correct
			fResults = CHECK(oSingle.ProcessAllResults(0, IID_IMultipleResults, IID_IRowset), S_OK);
		}
		else
			fResults = CHECK(hr, E_NOINTERFACE);
	}
	else
	{
		odtLog << L"IOpenRowset is not supported.\n";
		return TEST_SKIPPED;
	}

CLEANUP:

	SAFE_RELEASE(pIMultRes);
	SAFE_RELEASE(pIRowset);
	SAFE_RELEASE(pIOpenRowset);

	return fResults ? TEST_PASS : TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(38)
//*-----------------------------------------------------------------------
// @mfunc E_NOINTERFACE - IID_IMultipleResults on IDBSchemaRowset::GetRowset
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_38()
{
	IDBSchemaRowset *	pIDBSchemaRowset = NULL;
	BOOL				fResults = FALSE;	
	IRowset *		pIRowset = (IRowset *)0x12345678;

	//This interface is optional, so pass if we don't support it
	if (!VerifyInterface(m_pThisTestModule->m_pIUnknown2, IID_IDBSchemaRowset,
		SESSION_INTERFACE, (IUnknown **)&pIDBSchemaRowset))
		return TEST_PASS;
			

	fResults = CHECK(pIDBSchemaRowset->GetRowset(NULL, 
											DBSCHEMA_TABLES, 
											0, 
											NULL,
											IID_IMultipleResults,	//Shouldn't work
											0, 
											NULL, 
											(IUnknown **)&pIRowset), 
											E_NOINTERFACE);
	COMPARE (pIRowset, NULL);
	pIDBSchemaRowset->Release();
	pIDBSchemaRowset = NULL;

	if(pIRowset && (pIRowset != (IRowset *)0x12345678))
		pIRowset->Release();
	pIRowset = NULL;

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(39)
//*-----------------------------------------------------------------------
// @mfunc Select with empty rowset, mixed with poulated rowsets
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_39()
{
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EEMPTYSELECT,																			
									EINSERT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oBatch);

}
// }}


// {{ TCW_VAR_PROTOTYPE(40)
//*-----------------------------------------------------------------------
// @mfunc Release IMultipleResults while Rowset open
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_40()
{
	//IRowset * pIRowset = (IRowset *)0x12345678;	//Init so we know if it's nulled
	IRowset * pIRowset = NULL;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {																			
									ESELECT,
									EINSERT,
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	

	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, 
							ceSQLStmts, 
							rgeSQLStmts), 
							S_OK))	

		//Do a successful call
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IRowset, 
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowset), 
															S_OK)) 
									
		{
			//Now should be able to release IMultipleResults
			pMultResults->ReleaseIMultipleResults();
						
			//Should also still be able to use our rowset
			if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))				
				fResults = TRUE;
			
			pIRowset->Release();
			pIRowset = NULL;
		}
				
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}


	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(41)
//*-----------------------------------------------------------------------
// @mfunc Rowset creation failure do to E_NOINTERFACE
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_41()
{
	IRowset * pIRowset = (IRowset *)0x12345678;	//Init so we know if it's nulled
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {																			
									ESELECT,
									EINSERT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	

	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, 
							ceSQLStmts, 
							rgeSQLStmts), 
							S_OK))	

		//Do a call getting E_NOINTERFACE
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IRowsetUpdate, 
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowset), 
															E_NOINTERFACE)) 
									
		{
			//Now try again with a valid interface
			//TODO:  Uncomment if the provider allows		
			/*if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IRowset, 
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowset), 
															S_OK)) 
			
				
				if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))				
				{	
					pIRowset->Release();
					pIRowset = NULL;

					//Should also still be able to process the rest of the results
					if (CHECK(pMultResults->ProcessAllResults(1), S_OK))				
						fResults = TRUE;
				}*/
			
			COMPARE (pIRowset, NULL);
			if (CHECK(pMultResults->ProcessAllResults(1), S_OK))				
				fResults = TRUE;
			if ((pIRowset)&&(pIRowset!=(IRowset *)0x12345678))
				pIRowset->Release();
			pIRowset = NULL;

		}
		
				
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}


	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;

}
// }}


// {{ TCW_VAR_PROTOTYPE(42)
//*-----------------------------------------------------------------------
// @mfunc Rowset creation failure due to non forward only cursor
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_42()
{
	IRowset * pIRowset = (IRowset *)0x12345678;	//Init so we know if it's nulled
	IRowsetLocate * pIRowsetLocate = (IRowsetLocate *)0x12345678;	//Init so we know if it's nulled
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {																			
									ESELECT,			
									ESELECT,
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);

	////////////////////////////////////////////////
	//This is a ODBC Provider specific test!
	////////////////////////////////////////////////
	if (!g_fKagera)
		return TEST_SKIPPED;

	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, 
							ceSQLStmts, 
							rgeSQLStmts), 
							S_OK))	

		//Do a call getting regular supported rowset
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IRowset, 
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowset), 
															S_OK)) 
									
		{
			if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))				
			{	
				pIRowset->Release();
				pIRowset = NULL;

				//Now try again with a non forward only rowset
				//TODO:  
				if (CHECK(m_hr = pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IRowsetLocate, 
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowsetLocate), 
															E_NOINTERFACE)) 
				{

					COMPARE (pIRowsetLocate, NULL);
					if (pIRowsetLocate && (pIRowsetLocate!= (IRowsetLocate *)0x12345678))
						pIRowsetLocate->Release();
					pIRowsetLocate = NULL;

					//Get same result again, this time with valid interface
					if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
																		0, 
																		IID_IRowset, 
																		&pMultResults->m_cRowsGetResultAffected, 
																		(IUnknown **)&pIRowset), 
																		S_OK)) 
												
					{
						if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))				
						{	
							pIRowset->Release();
							pIRowset = NULL;
							
					
							//Should also still be able to process the rest of the results
							//TODO:  May need to change this from 3 to 2 depending on the provider
							if (CHECK(pMultResults->ProcessAllResults(3), S_OK))				
								fResults = TRUE;
						}
					}						
				}
			}
		}
				
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}

	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;
}
// }}


// {{ TCW_VAR_PROTOTYPE(43)
//*-----------------------------------------------------------------------
// @mfunc Multiple ParamSets in a batch - select, insert, select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_43()
{
	CParamSets			oParamSets(3,	//Use three param sets
							m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,
									EINSERT,
									ESELECT
									};

	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oParamSets.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oParamSets);

}
// }}


// {{ TCW_VAR_PROTOTYPE(44)
//*-----------------------------------------------------------------------
// @mfunc Multiple ParamSets in a batch - insert, select, insert
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_44()
{
	CParamSets			oParamSets(2,	
							m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	
	ESQLSTMT 		rgeSQLStmts[] = {											
									EINSERT,
									ESELECT,
									EINSERT									
									};

	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oParamSets.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	// Test that all results are correct
	// Note the spec states it's an error to use multiple paramsets with row
	// returning statements
	return TestValidMultResults(oParamSets);

}
// }}


// {{ TCW_VAR_PROTOTYPE(45)
//*-----------------------------------------------------------------------
// @mfunc Multiple ParamSets in a batch - select, select, select
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_45()
{
		CParamSets			oParamSets(3,	//Use three param sets
							m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,
									ESELECT,
									ESELECT
									};

	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	
	//Initialize batch statement with the proper SQL for this variation
	if (!oParamSets.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oParamSets);

}
// }}


// {{ TCW_VAR_PROTOTYPE(46)
//--------------------------------------------------------------------
// @mfunc single select, RestartPosition -- DB_S_COMMANDREEXECUTED
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCGeneralGetResult::Variation_46()
{
	CBatch			oSingle(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	IRowset			*pIRowset = NULL;
	BOOL			fResults = FALSE;
	ULONG			cRowsObtained;
	HROW 			rghRows[1];
	HROW *			prghRows=rghRows;

	//Initialize batch statement with the proper SQL for this variation
	if (!oSingle.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	if (CHECK(oSingle.SetAndExecute(IID_IMultipleResults), S_OK))
	{

		//if (CHECK((poBatch->m_pIMultResults)->GetResult(NULL, 
		if (CHECK((oSingle.m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&oSingle.m_cRowsGetResultAffected,
													(IUnknown **)&(pIRowset)), S_OK))	
		{
			if(pIRowset)
			{
				// We have to retrieve data before DB_S_COMMANDREEXECUTED will be returned by 
				// some providers
				if (CHECK(pIRowset->GetNextRows(NULL, 0, 1, &cRowsObtained, &prghRows), S_OK))
				{
					if (CHECK(pIRowset->ReleaseRows(1, rghRows, NULL, NULL, NULL), S_OK))
					{
						m_hr = pIRowset->RestartPosition(0);
						if (m_hr == S_OK || CHECK(m_hr, DB_S_COMMANDREEXECUTED))
							fResults = TRUE;
					}
				}
			
				pIRowset->Release();
				pIRowset = NULL;

			}
		}
	}

	oSingle.ReleaseIMultipleResults();

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;
			
}
// }}


// {{ TCW_VAR_PROTOTYPE(47)
//*-----------------------------------------------------------------------
// @mfunc S_OK - Select on 2nd command while processing GetResult on first command
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_47()
{ 
	IRowset * pIRowset = (IRowset *)0x12345678;	//Init so we know if it's nulled
	ICommand * pICommand = NULL;
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {																			
									ESELECT,
									ESELECT,											
									ESELECT
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	

	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK))	
	{
		//Do a successful call
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
															0, 
															IID_IRowset, 
						
															&pMultResults->m_cRowsGetResultAffected, 
															(IUnknown **)&pIRowset), 
															S_OK)) 
		{
			// Check the results
			TESTC(pIRowset != NULL);
			COMPARE(pMultResults->m_cRowsGetResultAffected, -1);

			// Release the rows and rowset
			if(pIRowset && (pIRowset != (IUnknown *)0x12345678))
				pIRowset->Release();

			// Create a second command object and open a rowset on it
			TESTC_(m_pSelectTable->ExecuteCommand(SELECT_ALLFROMTBL, IID_IRowset, NULL,
				NULL, NULL, NULL, EXECUTE_IFNOERROR, 0, NULL, NULL, (IUnknown**)&pIRowset,
				&pICommand), S_OK);

			// Validate the data also.
			TESTC_(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK);

			SAFE_RELEASE(pIRowset);

			pIRowset = (IRowset *)0x12345678;
			
			//Try unsupported IID
			if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
																0, 
																IID_IMultipleResults, 
																&pMultResults->m_cRowsGetResultAffected, 
																(IUnknown **)&pIRowset), 
																E_NOINTERFACE))
				if ((pMultResults->CheckErrorOutParams(pIRowset))&&(COMPARE(pMultResults->m_cRowsGetResultAffected,-1)) )
					//the current is lost. Now verify the next one
					if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
																		0, 
																		IID_IRowset, 
																		&pMultResults->m_cRowsGetResultAffected, 
																		(IUnknown **)&pIRowset), 
																		S_OK))
					{
								
						if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))				
							fResults = TRUE;
						pIRowset->Release();
						pIRowset = NULL;
					}
				
		}
	}
	
CLEANUP:
	
	//Cleanup from SetUpGetResult()
	if (pMultResults)
	{
		pMultResults->ReleaseIMultipleResults();		
		delete pMultResults;

	}

	SAFE_RELEASE(pICommand);
	
	if (fResults)
		return TEST_PASS;
	else 
		return TEST_FAIL;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(48)
//*-----------------------------------------------------------------------
// @mfunc S_OK - Single select, ask for IID_IRowsetScroll
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_48()
{ 
	CBatch			oSingle(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	
	// Since we're only asking Execute for IID_IMultipleResults we need to
	// require IID_IRowsetScroll on the rowset or GetResult may not necessarily 
	// be able to return it.
	if (FAILED(SetRowsetPropertyOn(DBPROP_IRowsetScroll)))
	{
		odtLog << L"Couldn't set DBPROP_IRowsetScroll on.\n";
		return TEST_SKIPPED;
	}

	//Initialize batch statement with the proper SQL for this variation
	if (!oSingle.FInit(ceSQLStmts, rgeSQLStmts))	
		return TEST_FAIL;

	//Test that all results are correct
	return TestValidMultResults(oSingle, IID_IRowsetScroll, IID_IMultipleResults);

} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(49)
//*-----------------------------------------------------------------------
// @mfunc Aggregated batch - select, select, select
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_49()
{ 
	ESQLSTMT 		rgeSQLStmts[] = {ESELECT, ESELECT, ESELECT};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CBatch * pBatch = NULL;
	ICommandText * pIAggCommandText = NULL;
	IUnknown *		pIAggUnknown = NULL;
	TESTRESULT		testresult = TEST_FAIL;
	HRESULT			hr = E_FAIL;

	CAggregate Aggregate;

	// Hack for Sql Server: If we have a valid command object we must release it
	// before creating a new one otherwise we end up with a server cursor which 
	// doesn't support IMultipleResults
	SAFE_RELEASE(m_pICommandText);
	
	// Create a new ICommandText object aggregated from IDBCreateCommand object.
	hr = m_pIDBCreateCommand->CreateCommand(&Aggregate, IID_IUnknown, 
		(IUnknown **)&pIAggUnknown);
	Aggregate.SetUnkInner(pIAggUnknown);

	TESTC(Aggregate.VerifyAggregationQI(hr, IID_ICommand));

	if (DB_E_NOAGGREGATION == hr || CLASS_E_NOAGGREGATION == hr)
	{
		testresult = TEST_SKIPPED;
		goto CLEANUP;
	}

	// See if we can get ICommandText off our aggregated object
	TESTC_(Aggregate.QueryInterface(IID_ICommandText, (void **)&pIAggCommandText), S_OK);

	pBatch = new CBatch(m_pIDBCreateCommand, pIAggCommandText, m_pSelectTable, m_pChangeTable);

	if (!pBatch)
	{
		odtLog << L"Out of memory!\n";
		goto CLEANUP;
	}

	//Initialize batch statement with the proper SQL for this variation
	TESTC(pBatch->FInit(ceSQLStmts, rgeSQLStmts));	

	//Test that all results are correct
	TESTC(TestValidMultResults(*(CMultResults *)pBatch));

	SAFE_DELETE(pBatch);

	// Now release our aggregated command text object and IUnknown
	// We expect the aggregated object to go away when the last ref is released.
	SAFE_RELEASE(pIAggCommandText);
	TESTC(Aggregate.GetRefCount()==1);	// Object gone!

	testresult = TEST_PASS;

CLEANUP:

	SAFE_DELETE(pBatch);
	SAFE_RELEASE(pIAggUnknown);
	SAFE_RELEASE(pIAggCommandText);

	// Now we must restore the member command text object
	if (!CHECK(m_pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown **)&m_pICommandText), S_OK))
	{
		odtLog << L"Fatal error, unable to recreate command text object.\n.";
		testresult = TEST_FAIL;
	}

	return testresult;

} 
// }} TCW_VAR_PROTOTYPE_END

// {{ TCW_VAR_PROTOTYPE(50)
//*-----------------------------------------------------------------------
// @mfunc Aggregated Result - Select, Select, Select
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_50()
{ 
	HRESULT hrExecute = E_FAIL;
	ULONG	iProp;
	ULONG	cInterfaces;
	INTERFACEMAP * prgInterfaces = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {ESELECT, ESELECT, ESELECT};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CMultResults *	pMultResults = NULL;
	IRowset *		pIRowset = NULL;
	TESTRESULT		testresult = TEST_PASS;
	HRESULT			hr = E_FAIL;
	ULONG			i=0;
	CAggregate * pAggregate = NULL;
	IUnknown *		pIAggUnknown = NULL;

	// Get the list of rowset interfaces/properties
	TESTC(GetInterfaceArray(ROWSET_INTERFACE, &cInterfaces, &prgInterfaces));

	for (iProp=0; iProp < cInterfaces; iProp++)
	{
		odtLog << prgInterfaces[iProp].pwszName << L"\n";

		if (!SettableProperty(prgInterfaces[iProp].dwPropertyID, DBPROPSET_ROWSET,
			m_pThisTestModule->m_pIUnknown, ROWSET_INTERFACE))
			continue;

		CHECK(SetRowsetProperty(m_pICommandText, DBPROPSET_ROWSET, prgInterfaces[iProp].dwPropertyID, TRUE), S_OK);

		hrExecute = SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts);

		// This should always be S_OK or DB_E_ERRORSOCCURRED, but due to provider bug may
		// return DB_S_ERRORSOCCURRED.
		if (SUCCEEDED(hrExecute))
		{
			CHECK(hrExecute, S_OK);

			for (i=0; i<ceSQLStmts+1; i++)
			{
				pAggregate = new CAggregate;

				TESTC(pAggregate != NULL);
			
				hr = pMultResults->m_pIMultResults->GetResult(pAggregate, 
																0, 
																IID_IUnknown,
																&pMultResults->m_cRowsGetResultAffected,
																(IUnknown **)&pIAggUnknown);
				pAggregate->SetUnkInner(pIAggUnknown);


				// Make sure there are no more results
				if (i == ceSQLStmts)
				{
					TESTC_(hr, DB_S_NORESULT);
					TESTC(pMultResults->m_cRowsGetResultAffected == -1);
					TESTC(pIAggUnknown == NULL);
				}
				else
				{
					// This is a valid result, process it.
					if (!pAggregate->VerifyAggregationQI(hr, IID_IRowset))
					{
						// We depend on LTM turning this into TEST_FAILURE if there is one
						testresult=TEST_SKIPPED;
						goto CLEANUP;
					}

					TESTC(VerifyInterface(pAggregate, IID_IRowset,
						ROWSET_INTERFACE, (IUnknown **)&pIRowset));


					//Check everything is correct for this result
					if (!COMPARE(pMultResults->AreGetResultOutParamsRight(i, pIRowset, IID_IRowset), TRUE))				
						odtLog << L"GetResult output params are not right for result: " << i+1 << wszNewLine;

					SAFE_RELEASE(pIRowset);
					TESTC(pAggregate->GetRefCount()==1);	// Object gone!

					SAFE_RELEASE(pIAggUnknown);
					SAFE_DELETE(pAggregate);
				}
			}

			SAFE_RELEASE(pMultResults->m_pIMultResults);
			SAFE_DELETE(pMultResults);
		}
		else if (hrExecute == DB_E_ERRORSOCCURRED)
		{
			COMPARE(IsServerCursorProperty(prgInterfaces[iProp].dwPropertyID), TRUE);
		}
		else
			CHECK(hrExecute, S_OK);

		// Set property back to default to avoid any other interactions.
		CHECK(SetRowsetPropertyDefault(prgInterfaces[iProp].dwPropertyID), S_OK);
	}

	testresult = TEST_PASS;

CLEANUP:

	SAFE_RELEASE(pIRowset);
	SAFE_RELEASE(pIAggUnknown);
	SAFE_DELETE(pAggregate);
	if (pMultResults)
		SAFE_RELEASE(pMultResults->m_pIMultResults);
	SAFE_DELETE(pMultResults);

	return testresult;

} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(51)
//*-----------------------------------------------------------------------
// @mfunc DBPROP_IMultipleResults - Execute with IID_IUnknown but DBPROP_IMultipleResults
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_51()
{ 
	HRESULT hrExecute = E_FAIL;
	ULONG	iProp;
	ULONG	cInterfaces;
	INTERFACEMAP * prgInterfaces = NULL;
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pChangeTable);	
	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EUPDATE,
									ESELECT,
									EUPDATE
									};

	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);

	TESTC(GetInterfaceArray(ROWSET_INTERFACE, &cInterfaces, &prgInterfaces));

	// Set on DBPROP_IMultipleResults
	CHECK(SetRowsetProperty(m_pICommandText, DBPROPSET_ROWSET, DBPROP_IMultipleResults, TRUE), S_OK);

	for (iProp=0; iProp < cInterfaces; iProp++)
	{
		odtLog << prgInterfaces[iProp].pwszName << L"\n";

		if (!SettableProperty(prgInterfaces[iProp].dwPropertyID, DBPROPSET_ROWSET,
			m_pThisTestModule->m_pIUnknown, ROWSET_INTERFACE))
			continue;

		CHECK(SetRowsetProperty(m_pICommandText, DBPROPSET_ROWSET, prgInterfaces[iProp].dwPropertyID, TRUE), S_OK);

		//Initialize batch statement with the proper SQL for this variation
		if (!oBatch.FInit(ceSQLStmts, rgeSQLStmts))	
			return TEST_FAIL;

		//Puts interface in m_pIMultRes
		// Note: For SQL Server, at least, we must have a FO/RO cursor to be able to support
		// IMultipleResults object, so asking for a prop that would require a server cursor
		// will return DB_E_ERRORSOCCURRED, which is legal.
		hrExecute = oBatch.SetAndExecute(IID_IUnknown);

		if (hrExecute == S_OK)
		{
			CHECK(oBatch.ProcessAllResults(0), S_OK);

			//Try to cleanup in case we had a failure and didn't get to cleanup above
			oBatch.ReleaseIMultipleResults();
		}
		else if (hrExecute == DB_E_ERRORSOCCURRED)
		{
			COMPARE(IsServerCursorProperty(prgInterfaces[iProp].dwPropertyID), TRUE);
		}
		else
			CHECK(hrExecute, S_OK);

		// Set property back to default to avoid any other interactions.
		CHECK(SetRowsetPropertyDefault(prgInterfaces[iProp].dwPropertyID), S_OK);
	}

	// Set property back to default to avoid any other interactions.
	CHECK(SetRowsetPropertyDefault(DBPROP_IMultipleResults), S_OK);

	//Count on our CHECKs to do any necessary error incrementing
	return TEST_PASS;

CLEANUP:

	return TEST_FAIL;

} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(52)
//*-----------------------------------------------------------------------
// @mfunc DB_E_INTEGRITYVIOLATION: Batch - select, insert, select. Fail insert.
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_52()
{ 
	ULONG	 iResult = 0;
	CBatch			oBatch(m_pIDBCreateCommand, 
							m_pICommandText,
							m_pSelectTable,
							m_pSelectTable);	

	ESQLSTMT 		rgeSQLStmts[] = {											
									ESELECT,										
									EINSERT,
									ESELECT									
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CCol ColIndex;
	ULONG ulIndexCol = 1;
	HRESULT hrCreateIndex = E_FAIL;
	

	// If the index column happens to be an autoincrement or non-updatable column
	// then the insert query below will not contain that column and the integrity
	// violation will not occur. To prevent this create another index.
	ulIndexCol = m_pSelectTable->GetIndexColumn();

	TESTC_(m_pSelectTable->GetColInfo(ulIndexCol, ColIndex), S_OK);

	if (ColIndex.GetAutoInc())
	{
		for (ULONG iNewIndex = 1; iNewIndex <= m_pSelectTable->CountColumnsOnTable();
			iNewIndex++)
		{
			if (iNewIndex == ulIndexCol)
				continue;

			TESTC_(m_pSelectTable->GetColInfo(iNewIndex, ColIndex), S_OK);

			// Providers generally cannot create an index on autoincrement, non-updatable, or bool cols
			if (!ColIndex.GetAutoInc() && ColIndex.GetUpdateable() && ColIndex.GetProviderType() != DBTYPE_BOOL)
				break;
		}

		TESTC(iNewIndex <= m_pSelectTable->CountColumnsOnTable());

		// Since there's already an index with the default name we need to 
		// create one with a new name.
		TESTC_(m_pSelectTable->GetColInfo(iNewIndex, ColIndex), S_OK);
		hrCreateIndex = m_pSelectTable->CreateIndex(iNewIndex, UNIQUE, ColIndex.GetColName());
		TESTC_(hrCreateIndex, S_OK);
	}
	
	TESTC(oBatch.FInit(ceSQLStmts, rgeSQLStmts));	

	//Create a multiple results object
	if (CHECK(oBatch.SetAndExecute(IID_IMultipleResults), S_OK))
	{

		while ( (m_hr = (oBatch.m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&oBatch.m_cRowsGetResultAffected,
													(IUnknown **)&(oBatch.m_pIRowset)) )
					!= DB_S_NORESULT)	
		{
			iResult++;

			// Results 1 and 3 are rowsets
			if (iResult != 2)
			{
				// Note using TESTC_ etc. will cause hang
				CHECK(m_hr, S_OK);
				COMPARE(oBatch.m_pIRowset != NULL, TRUE);
				CHECK(oBatch.VerifySelectRowset(IID_IRowset, oBatch.m_pIRowset), S_OK);
				SAFE_RELEASE(oBatch.m_pIRowset);
			}
			else
			{
				// Note using TESTC_ etc. will cause hang
				// Result 2 should be our integrity violation
				CHECK(m_hr, DB_E_INTEGRITYVIOLATION);
				COMPARE(oBatch.m_pIRowset == NULL, TRUE);
				SAFE_RELEASE(oBatch.m_pIRowset);	// Just in case it was returned.
			}		
		}
		
		//Make sure we did end correctly
		CHECK(m_hr, DB_S_NORESULT);
		COMPARE(iResult, 3);

		//Now make sure we get the same return code again
		CHECK((oBatch.m_pIMultResults)->GetResult(NULL, 
													0, 
													IID_IRowset,
													&oBatch.m_cRowsGetResultAffected,
													(IUnknown **)&(oBatch.m_pIRowset)), DB_S_NORESULT);

		oBatch.ReleaseIRowset();
		oBatch.ReleaseIMultipleResults();		

		return TEST_PASS;
	}

CLEANUP:

	// In case we didn't release the rowset above try again here
	SAFE_RELEASE(oBatch.m_pIRowset);

	return TEST_FAIL;

} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(53)
//*-----------------------------------------------------------------------
// @mfunc DB_E_NOAGGREGATION: Aggregated Result asking for IID != IID_IUnknown
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_53()
{ 
	HRESULT hrExecute = E_FAIL;
	ULONG	iProp;
	ULONG	cInterfaces;
	INTERFACEMAP * prgInterfaces = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {ESELECT, ESELECT, ESELECT};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	CMultResults *	pMultResults = NULL;
	IRowset *		pIRowset = NULL;
	TESTRESULT		testresult = TEST_PASS;
	HRESULT			hr = E_FAIL;
	ULONG			i=0;
	CAggregate * pAggregate = NULL;
	IUnknown *		pIAggUnknown = NULL;

	// Get the list of rowset interfaces/properties
	TESTC(GetInterfaceArray(ROWSET_INTERFACE, &cInterfaces, &prgInterfaces));

	for (iProp=0; iProp < cInterfaces; iProp++)
	{
		TESTC_(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK);

		for (i=0; i<ceSQLStmts+1; i++)
		{
			// IID_IUnknown is a success case and tested in a different variation
			if (*prgInterfaces[iProp].pIID == IID_IUnknown)
				continue;

			pAggregate = new CAggregate;

			TESTC(pAggregate != NULL);
		
			hr = pMultResults->m_pIMultResults->GetResult(pAggregate, 
															0, 
															*prgInterfaces[iProp].pIID,
															&pMultResults->m_cRowsGetResultAffected,
															(IUnknown **)&pIAggUnknown);

			if (hr != DB_E_NOAGGREGATION)
				odtLog << prgInterfaces[iProp].pwszName << L"\n";

			TESTC_(hr, DB_E_NOAGGREGATION);

			SAFE_RELEASE(pIAggUnknown);
			SAFE_DELETE(pAggregate);

		}

		SAFE_RELEASE(pMultResults->m_pIMultResults);
		SAFE_DELETE(pMultResults);

	}

	testresult = TEST_PASS;

CLEANUP:

	SAFE_RELEASE(pIRowset);
	SAFE_RELEASE(pIAggUnknown);
	SAFE_DELETE(pAggregate);
	if (pMultResults)
		SAFE_RELEASE(pMultResults->m_pIMultResults);
	SAFE_DELETE(pMultResults);

	return testresult;

} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(54)
//*-----------------------------------------------------------------------
// @mfunc S_OK: IMultipleResults with compute by clause
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int TCGeneralGetResult::Variation_54()
{ 
	// This variation repros a failure that occurred in one provider when a compute
	// clause was used with multiple results statement asking for IID_IRowset
	// and not retrieving the results, just releasing the rowset.
	IRowset * pIRowset = NULL;	
	BOOL			fResults = FALSE;
	CMultResults *	pMultResults = NULL;
	ESQLSTMT 		rgeSQLStmts[] = {																			
									ECOMPUTESUM,
									ECOMPUTESUM,
									};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	BOOL fResult = TEST_FAIL;
	HROW rghRow[1] = {DB_NULL_HROW};
	HROW * prghRow = (HROW *)rghRow;
	ULONG cRowsObtained = 0;
	HRESULT hr = E_FAIL;

	//Get an IMultipleResults interface, use our own SQLStmts
	TESTC_(SetUpGetResult(&pMultResults, ceSQLStmts, rgeSQLStmts), S_OK);

	// Release the multiple results object obtained above
	SAFE_RELEASE(pMultResults->m_pIMultResults);

	TESTC_(SetCommandText(m_pIMalloc,m_pICommandText,m_pSelectTable,NULL,eSQL,SELECT_ALLFROMTBL,pMultResults->GetSQLStmt()), S_OK);

	TESTC_(m_pICommandText->Execute(NULL, IID_IRowset, NULL, NULL,(IUnknown **)&pIRowset), S_OK);

	// If we don't retrieve any rows from the rowset we won't repro the failure
	for (; (hr = pIRowset->GetNextRows(NULL, 0, 1, &cRowsObtained, &prghRow)) == S_OK;)
		CHECK(pIRowset->ReleaseRows(1, rghRow, NULL, NULL, NULL), S_OK);

	TESTC_(hr, DB_S_ENDOFROWSET);

	fResult = TEST_PASS;

CLEANUP:

	// Failure actually occurs on release of the rowset.
	SAFE_RELEASE(pIRowset);
	delete pMultResults;

	return fResult;
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//--------------------------------------------------------------------
// @mfunc TestCase Termination Routine
//
// @rdesc TRUE or FALSE
//
BOOL TCGeneralGetResult::Terminate()
{
	// {{ TCW_TERM_BASECLASS_CHECK2
	return(CTestBase::Terminate());
}	// }}
// }}
// }}


// {{ TCW_TC_PROTOTYPE(TCTxn)
//*-----------------------------------------------------------------------
//| Test Case:		TCTxn - Tests Rowset behavior upon ending aTransaction
//|	Created:			10/01/96
//*-----------------------------------------------------------------------

//--------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL TCTxn::Init()
{
	ICommandProperties * pICmdProps = NULL;	
	ULONG				 ulIndex = 0;

	m_hr			  = E_FAIL;
	m_fCommitPreserve = FALSE;
	m_fAbortPreserve  = FALSE;

	// {{ TCW_INIT_BASECLASS_CHECK
	if(CTestBase::Init())
	// }}
	{
		if (FAILED(m_hr=m_pICommandText->QueryInterface(IID_ICommandProperties, 
														(void **)&pICmdProps)))
			goto END;

		if (GetProperty(DBPROP_ABORTPRESERVE, DBPROPSET_ROWSET, pICmdProps))
			m_fAbortPreserve = TRUE;

		if (GetProperty(DBPROP_COMMITPRESERVE, DBPROPSET_ROWSET, pICmdProps))
			m_fCommitPreserve = TRUE;
	}

END:

	// Release ICommandProperties pointer
	if (pICmdProps)
		pICmdProps->Release();

	if (SUCCEEDED(m_hr))
		return TRUE;
	else
		return FALSE;
}


//*-----------------------------------------------------------------------
// @mfunc TestTxn
// Tests commit/abort preservation with respect to IAccessor on rowsets
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCTxn::TestTxn(ETXN	eTxn, BOOL	fRetaining)
{
	
	BOOL					fSuccess = FALSE;
	ITransactionLocal * 	pITxnLocal = NULL;

	IRowset * 				pIRowset = NULL;
	IRowset * 				pIRowset2 = NULL;
	BOOL					fResults = FALSE;
	CMultResults *			pMultResults = NULL;	
	ESQLSTMT 				rgeSQLStmts[] = {																													
											ESELECT,
											EINSERT,
											ESELECT
											};
	ULONG			ceSQLStmts = sizeof(rgeSQLStmts) / sizeof(ESQLSTMT);
	ULONG			cRowsObtained = 0;
	HROW			hRow;
	HROW *			phRow = &hRow;
	
	
	//If we don't support Transactions, we won't test them
	if (!CHECK((m_pThisTestModule->m_pIUnknown2)->QueryInterface(IID_ITransactionLocal,
																(void **)&pITxnLocal),
																S_OK))
		return TEST_PASS;


	if (!CHECK(pITxnLocal->StartTransaction(ISOLATIONLEVEL_READCOMMITTED,
											0,
											NULL,
											NULL), 
											S_OK))
		goto CLEANUP;


	//Get an IMultipleResults interface
	if (CHECK(SetUpGetResult(&pMultResults, 
								ceSQLStmts, 
								rgeSQLStmts), 
								S_OK))	
	{
		
		if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
														0, 
														IID_IRowset, 
														&pMultResults->m_cRowsGetResultAffected, 
														(IUnknown **)&pIRowset), S_OK))
			
		{	
			if (eTxn == ETXN_COMMIT)
			{
				//Commit the transaction, with retention as specified
				if (!CHECK(pITxnLocal->Commit(fRetaining, 0, 0), S_OK))
					goto CLEANUP;
			}
			else
			{
				//Abort the transaction, with retention as specified
				if(!CHECK(pITxnLocal->Abort(NULL, fRetaining, FALSE), S_OK))
					goto CLEANUP;
			}
			
			
			//Make sure everything still works after commit or abort
			if((eTxn == ETXN_COMMIT && m_fCommitPreserve) ||
				(eTxn == ETXN_ABORT && m_fAbortPreserve))
			{	
			
				//Make sure our present rowset results worsk
				if (CHECK(pMultResults->VerifySelectRowset(IID_IRowset, pIRowset), S_OK))
				{
					//Mark that we've released this interface
					pIRowset->Release();
					pIRowset = NULL;

					//Also process the rest of the results
					if (CHECK(pMultResults->ProcessAllResults(1), S_OK))
						fResults = TRUE;
				}
			}
			//We should be zombied so check that we behave that way
			else
			{
				if (CHECK(pMultResults->m_pIMultResults->GetResult(NULL, 
																	0, 
																	IID_IRowset, 
																	&pMultResults->m_cRowsGetResultAffected, 
																	(IUnknown **)&pIRowset2), 
																	E_UNEXPECTED))
				{
					COMPARE(pIRowset2, NULL);
					if (CHECK(pIRowset->GetNextRows(NULL, 	
													0, 
													1, 
													&cRowsObtained, 
													(HROW **)&phRow), 
													E_UNEXPECTED))	
						fResults = TRUE;
				}
			}
		
		}
	}

CLEANUP:


	//Return code of Commit/Abort will vary depending on whether
	//or not we have an open txn, so adjust accordingly
	if (pITxnLocal)
	{
		if (fRetaining)
			CHECK(pITxnLocal->Commit(FALSE, 0, 0), S_OK);
		else
			CHECK(pITxnLocal->Commit(FALSE, 0, 0),XACT_E_NOTRANSACTION);
	
		pITxnLocal->Release();
	}

	if (pIRowset)
		pIRowset->Release();

	if (pIRowset2)
		pIRowset2->Release();
	
	if (pMultResults)
	{		
		pMultResults->ReleaseIMultipleResults(); 

		delete pMultResults;
	}

	if (fResults)
		return TEST_PASS;
	else
		return TEST_FAIL;
}


// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Commit Retaining
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCTxn::Variation_1()
{
	return TestTxn(ETXN_COMMIT, TRUE);
}
// }}


// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Commit NonRetaining
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCTxn::Variation_2()
{
	return TestTxn(ETXN_COMMIT, FALSE);
}
// }}


// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Abort Retaining
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCTxn::Variation_3()
{
	return TestTxn(ETXN_ABORT, TRUE);
}
// }}


// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Abort NonRetaining
//
// @rdesc TEST_PASS or TEST_FAIL
//
int TCTxn::Variation_4()
{
	return TestTxn(ETXN_ABORT, FALSE);
}
// }}


// {{ TCW_TERMINATE_METHOD
//--------------------------------------------------------------------
// @mfunc TestCase Termination Routine
//
// @rdesc TRUE or FALSE
//
BOOL TCTxn::Terminate()
{
	// {{ TCW_TERM_BASECLASS_CHECK2
	return(CTestBase::Terminate());
}	// }}
// }}
// }}
