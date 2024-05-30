//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CCOMMAND.CPP
//
//-----------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////
#include "Headers.h"


/////////////////////////////////////////////////////////////////
// CCommand::CCommand
//
/////////////////////////////////////////////////////////////////
CCommand::CCommand(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild) 
	: CDataAccess(eCCommand, pCMainWindow, pCMDIChild)
{
	//OLE DB Interfaces
	m_pICommand					= NULL;		//Command interface
	m_pICommandProperties		= NULL;		//Command interface
	m_pICommandText				= NULL;		//Command interface
	m_pICommandPrepare			= NULL;		//Command interface
	m_pICommandPersist			= NULL;		//Command interface
	m_pICommandWithParameters	= NULL;		//Command interface

	//Parameters
	m_cParamBindings = 0;
	m_rgParamBindings = NULL;
	memset(&m_ParamInfo, 0, sizeof(DBPARAMS));

	//Data
	m_guidDialect				= DBGUID_DEFAULT;
}

/////////////////////////////////////////////////////////////////
// CCommand::~CCommand
//
/////////////////////////////////////////////////////////////////
CCommand::~CCommand()
{
	ReleaseObject(0);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CCommand::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CCommand::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(ICommand);
	HANDLE_GETINTERFACE(ICommandProperties);
	HANDLE_GETINTERFACE(ICommandText);
	HANDLE_GETINTERFACE(ICommandPrepare);
	HANDLE_GETINTERFACE(ICommandPersist);
	HANDLE_GETINTERFACE(ICommandWithParameters);

	//Otherwise delegate
	return CDataAccess::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// HRESULT CCommand::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::AutoRelease()
{
	ReleaseAccessor(&m_ParamInfo.hAccessor);
	FreeBindings(&m_cParamBindings, &m_rgParamBindings);
	SAFE_FREE(m_ParamInfo.pData);

	//Command
	RELEASE_INTERFACE(IAccessor);
	RELEASE_INTERFACE(IColumnsInfo);
	RELEASE_INTERFACE(ICommand);
	RELEASE_INTERFACE(ICommandProperties);
	RELEASE_INTERFACE(ICommandText);
	RELEASE_INTERFACE(IConvertType);
	RELEASE_INTERFACE(ICommandPrepare);
	RELEASE_INTERFACE(ICommandPersist);
	RELEASE_INTERFACE(ICommandWithParameters);

	//Delegate
	return CDataAccess::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// HRESULT CCommand::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CDataAccess::AutoQI(dwCreateOpts);

	//[MANDATORY]
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(ICommand);
		OBTAIN_INTERFACE(ICommandText);
	}

	//[OPTIONAL]
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
		//[OPTIONAL]
		OBTAIN_INTERFACE(ICommandProperties);
		OBTAIN_INTERFACE(ICommandPrepare);
		OBTAIN_INTERFACE(ICommandPersist);
		OBTAIN_INTERFACE(ICommandWithParameters);
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////
// HRESULT CCommand::SetProperties
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::SetProperties(ULONG cPropSets, DBPROPSET* rgPropSets)
{
	HRESULT hr = E_FAIL;

	//Initally setup up some rowset properties that are very useful functionality
	//These are mainly to have the most common operations on the rowset and to
	//be able to obtain blob columns...

	if(m_pICommandProperties)
	{
		//ICommandProperties::SetProperties
		XTEST_(hr = m_pICommandProperties->SetProperties(cPropSets, rgPropSets),S_OK);
		TRACE_METHOD(hr, L"ICommandProperties::SetProperties(%d, 0x%p)", cPropSets, rgPropSets);

		//Display property errors
		TESTC(hr = DisplayPropErrors(hr, cPropSets, rgPropSets));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CCommand::GetCurrentCommand
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::GetCurrentCommand(DBID** ppCommandID)
{
	HRESULT hr = E_FAIL;

	if(m_pICommandPersist)
	{
		WCHAR wszCommandID[MAX_NAME_LEN] = {0};

		//ICommandPersist::GetCurrentCommand
		hr = m_pICommandPersist->GetCurrentCommand(ppCommandID);

		//Format the resultant DBID into something the user can look at...
		DBIDToString(ppCommandID ? *ppCommandID : NULL, wszCommandID, MAX_NAME_LEN);
		TESTC(TRACE_METHOD(hr, L"ICommandPersist::GetCurrentCommand({\"%s\"})", wszCommandID));
	}

CLEANUP:
	return hr;
}

	
/////////////////////////////////////////////////////////////////
// HRESULT CCommand::CreateParamAccessor
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::CreateParamAccessor(DB_UPARAMS cParams, DBPARAMINFO* rgParamInfo)
{
	HRESULT hr = S_OK;
	DBLENGTH cbRowSize = 0;
	
	//Release Previous Accessor
	m_ParamInfo.cParamSets = 0;
	ReleaseAccessor(&m_ParamInfo.hAccessor);
	SAFE_FREE(m_ParamInfo.pData);
	FreeBindings(&m_cParamBindings, &m_rgParamBindings);

	//Setup the Bindings
	TESTC(hr = SetupBindings(cParams, rgParamInfo, &m_cParamBindings, &m_rgParamBindings, &cbRowSize));
	
	//Create the Accessor
	TESTC(hr = CreateAccessor(DBACCESSOR_PARAMETERDATA, m_cParamBindings, m_rgParamBindings, cbRowSize, &m_ParamInfo.hAccessor));
	SAFE_ALLOC(m_ParamInfo.pData, BYTE, cbRowSize);
	m_ParamInfo.cParamSets = 1;

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CCommand::SetupBindings
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::SetupBindings(DB_UPARAMS cParams, DBPARAMINFO* rgParamInfo, DBCOUNTITEM* pcBindings, DBBINDING** prgBindings, DBLENGTH* pcRowSize)
{
	ASSERT(pcBindings);
	ASSERT(prgBindings);

	HRESULT hr = S_OK;

	DBLENGTH dwOffset = 0;
	DBCOUNTITEM i,cBindings = 0;
	DBBINDING* rgBindings = NULL;
	
	//Only capable of the Following Converions (for Display)
	DWORD	dwMaxLength		= GetOptions()->m_dwMaxLength;
	DWORD	dwAccessorOpts	= GetOptions()->m_dwAccessorOpts;

	//Alloc the space to hold the Bindings and Accessors
	SAFE_ALLOC(rgBindings, DBBINDING, cParams);

	cBindings = 0;
	for(i=0; i<cParams; i++) 
	{
		ASSERT(rgParamInfo);

		//SetUp the Bindings
		rgBindings[cBindings].iOrdinal	= rgParamInfo[i].iOrdinal;
		rgBindings[cBindings].obStatus	= dwOffset;
		rgBindings[cBindings].obLength	= dwOffset + sizeof(DBSTATUS);
		rgBindings[cBindings].obValue	= dwOffset + sizeof(DBSTATUS) + sizeof(DBLENGTH);
		
		rgBindings[cBindings].pTypeInfo = NULL;
		rgBindings[cBindings].pBindExt  = NULL;

		rgBindings[cBindings].dwPart	= dwAccessorOpts & (DBPART_VALUE|DBPART_LENGTH|DBPART_STATUS);
		rgBindings[cBindings].dwMemOwner= DBMEMOWNER_CLIENTOWNED;
		
		rgBindings[cBindings].eParamIO	= DBPARAMIO_NOTPARAM;
		if(rgParamInfo[i].dwFlags & DBPARAMFLAGS_ISINPUT)
			rgBindings[cBindings].eParamIO |= DBPARAMIO_INPUT;
		if(rgParamInfo[i].dwFlags & DBPARAMFLAGS_ISOUTPUT)
			rgBindings[cBindings].eParamIO |= DBPARAMIO_OUTPUT;
		
		rgBindings[cBindings].dwFlags	= 0;
		rgBindings[cBindings].bPrecision= rgParamInfo[i].bPrecision;
		rgBindings[cBindings].bScale	= rgParamInfo[i].bScale;

		rgBindings[cBindings].pObject	= NULL;
		rgBindings[cBindings].wType		= GetOptions()->GetBindingType(rgParamInfo[i].wType);

		//MAX_LENGTH
		rgBindings[cBindings].cbMaxLen	= GetMaxDisplaySize(rgBindings[cBindings].wType, rgParamInfo[i].wType, rgParamInfo[i].ulParamSize, dwMaxLength);
		
		dwOffset = rgBindings[cBindings].cbMaxLen + rgBindings[cBindings].obValue;
		dwOffset = ROUNDUP( dwOffset );
		cBindings++;
	}

	//Size for pData
	if(pcRowSize)
		*pcRowSize = dwOffset;

CLEANUP:
	//Accessors
	*pcBindings = cBindings;
	*prgBindings = rgBindings;
	return hr;
}



/////////////////////////////////////////////////////////////////
// HRESULT CCommand::Prepare
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::Prepare(ULONG cExpectedRuns)
{
	HRESULT hr = S_OK;

	//Prepare
	if(m_pICommandPrepare)
	{
		//ICommandPrepare::Prepare
		hr = m_pICommandPrepare->Prepare(0);
		TRACE_METHOD(hr, L"ICommandPrepare::Prepare(%d)", cExpectedRuns);
	}

	return hr;
}

	
/////////////////////////////////////////////////////////////////
// HRESULT CCommand::GetParameterInfo
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::GetParameterInfo(DB_UPARAMS* pcParams, DBPARAMINFO** prgParamInfo, OLECHAR** ppwszNamesBuffer)
{
	HRESULT hr = S_OK;

	if(m_pICommandWithParameters)
	{
		//ICommandWithParameters::GetParameterInfo
		hr = m_pICommandWithParameters->GetParameterInfo(pcParams, prgParamInfo, ppwszNamesBuffer);
		TRACE_METHOD(hr, L"ICommandWithParameters::GetParameterInfo(&%lu, &0x%p, &0x%p)", pcParams ? *pcParams : 0, prgParamInfo ? *prgParamInfo : NULL, ppwszNamesBuffer ? *ppwszNamesBuffer : NULL);
	}

	return hr;
}

	
/////////////////////////////////////////////////////////////////
// HRESULT CCommand::SetCommandText
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::SetCommandText(WCHAR* pwszText, GUID* pGuidDialect)
{
	HRESULT hr = S_OK;
	GUID guidDialect = pGuidDialect ? *pGuidDialect : m_guidDialect;

	//Set CommandText
	if(m_pICommandText)
	{
		XTEST(hr = m_pICommandText->SetCommandText(guidDialect, pwszText));
		TESTC(TRACE_METHOD(hr, L"ICommandText::SetCommandText(%s, \"%s\")", GetDialectName(guidDialect), pwszText));

		//Save the Command Text on Success...
		if(pGuidDialect)
			m_guidDialect = *pGuidDialect;
	}

CLEANUP:
	return hr;
}



/////////////////////////////////////////////////////////////////
// HRESULT CCommand::Execute
//
/////////////////////////////////////////////////////////////////
HRESULT CCommand::Execute(CAggregate* pCAggregate, WCHAR* pwszCommandText, REFIID riid, DBPARAMS* pParams, DBROWCOUNT* pcRowsAffected, IUnknown** ppIUnknown)
{
	HRESULT hr = S_OK;
	DBROWCOUNT cRowsAffected = DB_COUNTUNAVAILABLE;

	//Execute
	if(m_pICommand)
	{
		//SetCommandText (if user requested new text)
		if(pwszCommandText)
		{
			//Clear previous object (if requested and really need to...)
			if(GetOptions()->m_dwCommandOpts & COMMAND_RELEASEROWSET)
			{
				//Only need to release the object if its a child of this object.
				//We do have cases where the CDataAccess wiull be filled in but its not a parent
				//of this object.  For example Row -> Command (row is not a child of the command)
				if(m_pCMDIChild->m_pCDataAccess && m_pCMDIChild->m_pCDataAccess->m_pCParent == this)
					m_pCMDIChild->m_pCDataAccess->ReleaseObject();
				if(m_pCMDIChild && m_pCMDIChild->m_pCMultipleResults && m_pCMDIChild->m_pCMultipleResults->m_pCParent == this)
					m_pCMDIChild->m_pCMultipleResults->ReleaseObject();
			}
			
			//SetCommandText...
			TESTC(hr = SetCommandText(pwszCommandText));
		}

		//Execute
		XTEST_(hr = m_pICommand->Execute(
							pCAggregate,			// pUnkOuter
							riid,					// refiid
							pParams,				// params
							&cRowsAffected,			// rows affected
 							ppIUnknown),S_OK);  	// IRowset pointer
		TRACE_METHOD(hr, L"ICommand::Execute(0x%p, %s, NULL, &%ld, &0x%p)", pCAggregate, GetInterfaceName(riid), cRowsAffected, ppIUnknown ? *ppIUnknown : NULL);
		
		//Display Property Errors
		TESTC(hr = DisplayPropErrors(hr, IID_ICommandProperties, m_pICommand));

		//ParameterBinding Errors
		if(pParams)
			TESTC(hr = DisplayBindingErrors(hr, m_cParamBindings, m_rgParamBindings, m_ParamInfo.pData));

		//Handle Aggregation
		if(pCAggregate)
			TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));

		//Display RowsAffected - (if desired)
		if(!pcRowsAffected)
		{
			if(!ppIUnknown || !*ppIUnknown)
			{
				if(cRowsAffected==DB_COUNTUNAVAILABLE)
					wMessageBox(GetFocus(), MB_TASKMODAL | MB_ICONWARNING | MB_OK, wsz_INFO, 
						L"RowsAffected = %s, No Rowset returned", L"DB_COUNTUNAVAILABLE");				
				else
					wMessageBox(GetFocus(), MB_TASKMODAL | MB_ICONWARNING | MB_OK, wsz_INFO, 
						L"RowsAffected = %ld, No Rowset returned", cRowsAffected );
			}
		}
	}

CLEANUP:
	if(pcRowsAffected)
		*pcRowsAffected = cRowsAffected;
	return hr;
}





