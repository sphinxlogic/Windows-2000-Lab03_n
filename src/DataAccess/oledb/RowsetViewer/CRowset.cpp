//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CROWSET.CPP
//
//-----------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
// Includes
//
//////////////////////////////////////////////////////////////////////////////
#include "Headers.h"


/////////////////////////////////////////////////////////////////
// CDataAccess::CDataAccess
//
/////////////////////////////////////////////////////////////////
CDataAccess::CDataAccess(SOURCE eObjectType, CMainWindow* pCMainWindow, CMDIChild* pCMDIChild) 
	: CAsynchBase(eObjectType, pCMainWindow, pCMDIChild)
{
	//eBaseClass
	m_eBaseClass = BASE_CLASS(m_eBaseClass | eCDataAccess);

	//ColInfo
	m_cColInfo			= 0;
	m_rgColumnInfo		= NULL;
	m_pStringBuffer		= NULL;
	m_cHiddenColumns	= 0;

	//Rowset
	m_pIAccessor		= NULL;		//Rowset Interface
	m_pIColumnsInfo		= NULL;		//Rowset Interface
	m_pIConvertType		= NULL;		//Rowset Interface
	m_pIColumnsRowset	= NULL;		//Rowset interface

	//Extra Interfaces

	//Accessor
	m_cBindings			= 0;
	m_rgBindings		= NULL;
	m_hAccessor			= NULL;
	m_cbRowSize			= 0;
	m_pData				= NULL;

	//Bookmark Accessor
	m_hBmkAccessor		= NULL;
	m_bSchemaRowset		= FALSE;
}


/////////////////////////////////////////////////////////////////
// CDataAccess::~CDataAccess
//
/////////////////////////////////////////////////////////////////
CDataAccess::~CDataAccess()
{
}


/////////////////////////////////////////////////////////////////
// IUnknown** CDataAccess::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CDataAccess::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(IAccessor);
	HANDLE_GETINTERFACE(IColumnsInfo);
	HANDLE_GETINTERFACE(IConvertType);
	HANDLE_GETINTERFACE(IColumnsRowset);

	//Otherwise delegate
	return CAsynchBase::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CAsynchBase::AutoQI(dwCreateOpts);

	//[MANDATORY] Obtain [mandatory] interfaces
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(IColumnsInfo);
		OBTAIN_INTERFACE(IAccessor);
		OBTAIN_INTERFACE(IConvertType);
	}

	//Auto QI
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
		OBTAIN_INTERFACE(IColumnsRowset);
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////
// CDataAccess::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::AutoRelease()
{
	//Data
	m_bSchemaRowset		= FALSE;

	//ColInfo
	m_cColInfo	= 0;
	SAFE_FREE(m_rgColumnInfo);
	SAFE_FREE(m_pStringBuffer);
	m_cHiddenColumns = 0;

	ReleaseAccessor(&m_hAccessor);
	FreeBindings(&m_cBindings, &m_rgBindings);
	SAFE_FREE(m_pData);
	ReleaseAccessor(&m_hBmkAccessor);

	//Rowset
	RELEASE_INTERFACE(IAccessor);
	RELEASE_INTERFACE(IColumnsInfo);
	RELEASE_INTERFACE(IConvertType);
	RELEASE_INTERFACE(IColumnsRowset);

	//Delegate
	return CAsynchBase::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// DBCOLUMNINFO* CDataAccess::GetColInfo
//
/////////////////////////////////////////////////////////////////
DBCOLUMNINFO* CDataAccess::GetColInfo(DBORDINAL iOrdinal)
{ 
	//Due to the bookmark column being present or absent causes the ColInfo
	//to not be lined exactly (1:1) to the Ordinal position...

	//no-ops
	if(m_cColInfo==0 || m_rgColumnInfo == NULL || (iOrdinal==0 && m_rgColumnInfo[0].iOrdinal!=0))
		return NULL;
	
	if(m_rgColumnInfo[0].iOrdinal==0)
	{
		//[0,1,2,3,4,5...]
		ASSERT(iOrdinal < m_cColInfo);
		ASSERT(m_rgColumnInfo[iOrdinal].iOrdinal == iOrdinal);
		return &m_rgColumnInfo[iOrdinal];
	}
	else
	{
		//[1,2,3,4,5...]
		ASSERT(iOrdinal && iOrdinal <= m_cColInfo);
		ASSERT(m_rgColumnInfo[iOrdinal-1].iOrdinal == iOrdinal);
		return &m_rgColumnInfo[iOrdinal-1];
	}
	
	return NULL;
}


/////////////////////////////////////////////////////////////////
// DBBINDING* CDataAccess::GetBinding
//
/////////////////////////////////////////////////////////////////
DBBINDING* CDataAccess::GetBinding(DBORDINAL iOrdinal)
{
	//Due to the bookmark column being present or absent causes the Binding
	//to not be lined exactly (1:1) to the Ordinal position...

	//no-ops
	if(m_cBindings==0 || m_rgBindings == NULL || (iOrdinal==0 && m_rgBindings[0].iOrdinal!=0))
		return NULL;
	
	//Bookmark
	if(m_rgBindings[0].iOrdinal == 0)
	{
		//[0,1,2,3,4,5...]
		ASSERT(iOrdinal < m_cBindings);
		ASSERT(m_rgBindings[iOrdinal].iOrdinal == iOrdinal);
		return &m_rgBindings[iOrdinal];
	}
	else
	{
		//[1,2,3,4,5...]
		ASSERT(iOrdinal && iOrdinal <= m_cBindings);
		ASSERT(m_rgBindings[iOrdinal-1].iOrdinal == iOrdinal);
		return &m_rgBindings[iOrdinal-1];
	}
	
	return NULL;
}

	
/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::GetColInfo
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::GetColInfo()
{
	HRESULT		hr = E_FAIL;
	
	//Release an Previous Info
	m_cColInfo = 0;
	SAFE_FREE(m_rgColumnInfo);
	SAFE_FREE(m_pStringBuffer);
	m_cHiddenColumns = 0;

	//Delegate
	TESTC(hr = GetColInfo(&m_cColInfo, &m_rgColumnInfo, &m_pStringBuffer, &m_cHiddenColumns));

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::GetColInfo
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::GetColInfo(DBORDINAL* pcColumns, DBCOLUMNINFO** prgColumnInfo, WCHAR** ppStringBuffer, ULONG* pcHiddenColumns)
{
	HRESULT		hr = E_FAIL;
	
	if(m_pIColumnsInfo)
	{
		//Get column information from the command object via IColumnsInfo::GetColumnsInfo 
		XTEST(hr = m_pIColumnsInfo->GetColumnInfo(pcColumns, prgColumnInfo, ppStringBuffer));
		TESTC(TRACE_METHOD(hr, L"IColumnsInfo::GetColumnInfo(&%lu, &0x%p, &0x%p)", pcColumns ? *pcColumns : 0, prgColumnInfo ? *prgColumnInfo : NULL, ppStringBuffer ? *ppStringBuffer : NULL));

		//Obtain any Hidden Columns (if requested by the user)
		if(GetOptions()->m_dwRowsetOpts & ROWSET_HIDDENCOLUMNS)
		{
			//DBPROP_HIDDENCOLUMNS
			if(pcColumns && pcHiddenColumns)
			{
				IRowsetInfo* pIRowsetInfo = NULL;
				if(SUCCEEDED(m_pIColumnsInfo->QueryInterface(IID_IRowsetInfo, (void**)&pIRowsetInfo)))
				{
					if(SUCCEEDED(GetProperty(IID_IRowsetInfo, pIRowsetInfo, DBPROP_HIDDENCOLUMNS, DBPROPSET_ROWSET, DBTYPE_I4, pcHiddenColumns)))
						*pcColumns += *pcHiddenColumns;
					SAFE_RELEASE(pIRowsetInfo);
				}
			}
		}
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// CDataAccess::GetColumnImage
//
/////////////////////////////////////////////////////////////////
INT CDataAccess::GetColumnImage(DBCOLUMNINFO* pColInfo, DBSTATUS dbStatus)
{
	//NOTE:  Errors take precidence in the following function over readonly or chapter icons...

	//Otherwise determine image from Status
	switch(dbStatus)
	{
		case DBSTATUS_S_OK:
		case DBSTATUS_S_ISNULL:
		case DBSTATUS_S_DEFAULT:
		case DBSTATUS_S_IGNORE:
			if(pColInfo)
			{
				//Hidden Column?
				if(m_cHiddenColumns)
				{
					//cColInfo already includes cHiddenColumns, this...
					ASSERT(m_cHiddenColumns <= m_cColInfo);
					ASSERT(m_rgColumnInfo);

					//Is this a hidden column
					//If this ordinal is >= to the first hidden column then its hidden...
					if(pColInfo->iOrdinal >= m_rgColumnInfo[m_cColInfo - m_cHiddenColumns].iOrdinal)
						return IMAGE_DELETE;
				}

				//Chapter Column (takes precidence)
				if(pColInfo->dwFlags & DBCOLUMNFLAGS_ISCHAPTER)
					return IMAGE_CHAPTER;
			
				//ReadOnly Column
				if(!(pColInfo->dwFlags & DBCOLUMNFLAGS_WRITE || pColInfo->dwFlags & DBCOLUMNFLAGS_WRITEUNKNOWN))
					return IMAGE_LOCK;
			}
			return IMAGE_NONE;

		case DBSTATUS_S_TRUNCATED:
			return IMAGE_QUESTION;

		default:
			return IMAGE_ERROR;
	}

	return IMAGE_NORMAL;
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::ValidateAccessor
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::ValidateAccessor(HACCESSOR hAccessor, ULONG ulRefCount)
{
	//Warn user about NULL Accessor handle...
	if(hAccessor == DB_NULL_HACCESSOR || ulRefCount == 0)
	{
		if(IDNO == wMessageBox
			(
				GetFocus(), 
				MB_TASKMODAL | MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1, 
				wsz_ERROR, 
				L"hAccessor == 0x%p\n"
				L"%s\n\n"
				L"This may crash your Provider...\n"
				L"Do you wish to continue anyway?", 
				hAccessor,
				hAccessor == DB_NULL_HROW ? L"Invalid Accessor Handle" : L"Released Accessor Handle"
			)
		  )
			return E_FAIL;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::CreateAccessors
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::CreateAccessors(BINDCOLS eBindCols)
{
	HRESULT hr = S_OK;
	
	//Release Previous Accessors
	ReleaseAccessor(&m_hAccessor);
	FreeBindings(&m_cBindings, &m_rgBindings);
	SAFE_FREE(m_pData);
	ReleaseAccessor(&m_hBmkAccessor);

	//Delegate
	TESTC(hr = SetupBindings(eBindCols, &m_cBindings, &m_rgBindings, &m_cbRowSize));
	TESTC(hr = CreateAccessor(DBACCESSOR_ROWDATA, m_cBindings, m_rgBindings, m_cbRowSize, &m_hAccessor));

	//Allocate pData
	SAFE_ALLOC(m_pData, BYTE, m_cbRowSize);

CLEANUP:
	return hr;
}
	

/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::SetupBindings
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::SetupBindings(BINDCOLS eBindCols, DBCOUNTITEM* pcBindings, DBBINDING** prgBindings, DBLENGTH* pcRowSize)
{
	HRESULT hr = S_OK;

	DBLENGTH dwOffset = 0;
	DBCOUNTITEM i,cBindings = 0;
	DBBINDING* rgBindings = NULL;
	
	//Only capable of the Following Converions (for Display)
	DWORD	dwMaxLength		= GetOptions()->m_dwMaxLength;
	DWORD	dwAccessorOpts	= GetOptions()->m_dwAccessorOpts;
	
	//Alloc the space to hold the Bindings
	SAFE_ALLOC(rgBindings, DBBINDING, m_cColInfo);

	cBindings = 0;
	for(i=0; i<m_cColInfo; i++) 
	{
		ASSERT(m_rgColumnInfo);
		DBCOLUMNINFO*	pColInfo	= &m_rgColumnInfo[i];
		DBBINDING*		pBinding	= &rgBindings[cBindings];

		//Setup the Bindings
		pBinding->iOrdinal	= pColInfo->iOrdinal;
		pBinding->obStatus	= dwOffset;
		pBinding->obLength	= dwOffset + sizeof(DBSTATUS);
		pBinding->obValue	= dwOffset + sizeof(DBSTATUS) + sizeof(DBLENGTH);
		
		pBinding->pTypeInfo = NULL;
		pBinding->pBindExt  = NULL;

		pBinding->dwPart	= dwAccessorOpts & (DBPART_VALUE|DBPART_LENGTH|DBPART_STATUS);			
		pBinding->dwMemOwner= DBMEMOWNER_CLIENTOWNED;
		pBinding->eParamIO	= DBPARAMIO_NOTPARAM;
		
		pBinding->dwFlags	= 0;
		pBinding->bPrecision= pColInfo->bPrecision;
		pBinding->bScale	= pColInfo->bScale;

		pBinding->pObject	= NULL;
		pBinding->wType		= GetOptions()->GetBindingType(pColInfo->wType);
		pBinding->cbMaxLen	= GetMaxDisplaySize(pBinding->wType, pColInfo->wType, pColInfo->ulColumnSize, dwMaxLength);
						
		//BLOB or IUnknown Bindings
		if(pBinding->wType == DBTYPE_IUNKNOWN || pColInfo->wType == DBTYPE_IUNKNOWN || 
			(pColInfo->dwFlags & DBCOLUMNFLAGS_ISLONG && (dwAccessorOpts & (ACCESSOR_BLOB_ISEQSTREAM|ACCESSOR_BLOB_ILOCKBYTES|ACCESSOR_BLOB_ISTORAGE|ACCESSOR_BLOB_ISTREAM))))
		{
			//For ColumnsRowset
			pBinding->wType		= DBTYPE_IUNKNOWN;
			pBinding->cbMaxLen	= sizeof(IUnknown*);

			//Create pObject
			SAFE_ALLOC(pBinding->pObject, DBOBJECT, 1);
			pBinding->pObject->dwFlags	= STGM_READ;
			pBinding->pObject->iid		= IID_IUnknown;

			//Setup pObject->iid 
			if(dwAccessorOpts & ACCESSOR_BLOB_ISEQSTREAM)
				pBinding->pObject->iid		= IID_ISequentialStream;
			else if(dwAccessorOpts & ACCESSOR_BLOB_ISTREAM)
				pBinding->pObject->iid		= IID_IStream;
			else if(dwAccessorOpts & ACCESSOR_BLOB_ILOCKBYTES)
				pBinding->pObject->iid		= IID_ILockBytes;
			else if(dwAccessorOpts & ACCESSOR_BLOB_ISTORAGE)
				pBinding->pObject->iid		= IID_IStorage;
		}	

		//Special Handling for other non-OLE DB defined convertable types to WSTR
		//NOTE: The spec requires all supported types to be converted to 
		//WSTR, but this only applies where the OLE DB conversion is defined.
		//Some are not defined so we need to bind nativly.
		switch(pColInfo->wType)
		{
			case DBTYPE_IUNKNOWN:
			case DBTYPE_IDISPATCH:
				pBinding->wType		= pColInfo->wType;
				pBinding->cbMaxLen	= sizeof(IUnknown*);
				break;

			case DBTYPE_HCHAPTER:
				pBinding->wType		= pColInfo->wType;
				pBinding->cbMaxLen	= sizeof(HCHAPTER);
				break;

			default:
				//DBTYPE_VECTOR
				if(pColInfo->wType & DBTYPE_VECTOR)
				{
					pBinding->wType		= pColInfo->wType;
					pBinding->cbMaxLen	= sizeof(DBVECTOR);
				}

				//DBTYPE_ARRAY
				if(pColInfo->wType	& DBTYPE_ARRAY)
				{
					pBinding->wType		= pColInfo->wType;
					pBinding->cbMaxLen	= sizeof(SAFEARRAY*);
				}
				break;
		};

		//Offset
		dwOffset = pBinding->cbMaxLen + pBinding->obValue;
		dwOffset = ROUNDUP( dwOffset );

		switch(eBindCols)
		{
			case BIND_ALLCOLS:
				cBindings++;
				break;

			case BIND_ALLCOLSEXPECTBOOKMARK:
				if(pColInfo->iOrdinal != 0)
					cBindings++;
				break;

			case BIND_UPDATEABLECOLS:
				if(pColInfo->dwFlags & DBCOLUMNFLAGS_WRITE || pColInfo->dwFlags & DBCOLUMNFLAGS_WRITEUNKNOWN)
					cBindings++;
				break;

			default:
				ASSERT(!"Unhandled Type!");
				break;
		}
	}

	//Size for pData
	if(pcRowSize)
		*pcRowSize = dwOffset;

CLEANUP:
	//Accessors
	if(pcBindings)
		*pcBindings = cBindings;
	if(prgBindings)
		*prgBindings = rgBindings;
	else
		SAFE_FREE(rgBindings);
	
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::CreateAccessor
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::CreateAccessor(DBACCESSORFLAGS dwAccessorFlags, DBCOUNTITEM cBindings, DBBINDING* rgBindings, DBLENGTH cRowSize, HACCESSOR* phAccessor)
{
	ASSERT(phAccessor);

	HRESULT hr = E_FAIL;
	DBBINDSTATUS* rgStatus = NULL;

	if(m_pIAccessor)
	{
		//Alloc the space to hold the status
		SAFE_ALLOC(rgStatus, DBBINDSTATUS, cBindings);

		//Create the accessor
		*phAccessor = NULL;
		XTEST(hr = m_pIAccessor->CreateAccessor(dwAccessorFlags, cBindings, rgBindings, cRowSize, phAccessor, rgStatus));
		TRACE_METHOD(hr, L"IAccessor::CreateAccessor(0x%08x, %lu, 0x%p, %lu, &0x%p, 0x%p)", dwAccessorFlags, cBindings, rgBindings, cRowSize, *phAccessor, rgStatus);

		//Display Errors
		TESTC(hr = DisplayAccessorErrors(hr, cBindings, rgBindings, rgStatus));
	}

CLEANUP:
	SAFE_FREE(rgStatus);
	return hr;
}
	


/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::AddRefAccessor
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::AddRefAccessor(HACCESSOR hAccessor)
{
	HRESULT hr = S_OK;
	ULONG ulRefCount = 0;

	if(m_pIAccessor)
	{
		//IAccessor::AddRefAccessor
		XTEST(hr = m_pIAccessor->AddRefAccessor(hAccessor, &ulRefCount));
		TESTC(TRACE_METHOD(hr, L"IAccessor::AddRefAccessor(0x%p, &%d)", hAccessor, ulRefCount));
	}

CLEANUP:
	return hr;
}

				
/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::ReleaseAccessor
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::ReleaseAccessor(HACCESSOR* phAccessor, BOOL fReleaseAlways)
{
	ASSERT(phAccessor);
	HRESULT hr = S_OK;
	ULONG ulRefCount = 0;

	if(m_pIAccessor && (*phAccessor || fReleaseAlways))
	{
		XTEST(hr = m_pIAccessor->ReleaseAccessor(*phAccessor, &ulRefCount));
		TESTC(TRACE_METHOD(hr, L"IAccessor::ReleaseAccessor(0x%p, &%d)", *phAccessor, ulRefCount));
	}

CLEANUP:
	//Only NULL the handle if the RefCount is 0
	if(ulRefCount == 0)
		*phAccessor = NULL;
	return hr;
}


////////////////////////////////////////////////////////////////
// CDataAccess::GetColumnData
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::GetColumnData(DBBINDING* pBinding, void* pData, DBSTATUS* pdbStatus, DBLENGTH* pdbLength, DBTYPE* pwSubType, WCHAR* pwszValue, ULONG ulMaxSize, DWORD dwConvFlags, DBTYPE wBackendType)
{
	ASSERT(pBinding);
	ASSERT(pwszValue);
	HRESULT hr = S_OK;
	DBTYPE	wSubType = DBTYPE_EMPTY;

	//STATUS
	DBSTATUS dbStatus		= STATUS_IS_BOUND(*pBinding) ? BINDING_STATUS(*pBinding, pData) : DBSTATUS_E_BADSTATUS;

	//LENGTH is the Actual (Untruncated) length of the string
	//We we need to make sure all operations are off of cbMaxLen and not LENGTH bound
	//NOTE: If the length is not bound, we set the length to our cbMaxLength NOT 0.  This is because
	//many datatypes can still be returned, and our conversion routines are based upon the length...
	DBLENGTH dbLength		= LENGTH_IS_BOUND(*pBinding) ? BINDING_LENGTH(*pBinding, pData) : pBinding->cbMaxLen;
	
	//VALUE
	pwszValue[0] = wEOL;
	void* pValue = VALUE_IS_BOUND(*pBinding) ? &BINDING_VALUE(*pBinding, pData) : NULL;

	//cbMaxLen
	//NOTE: The maximum size we can possibly read is either the specified cbMaxLen or our 
	//data buffer we are retriving into for display...

	switch(dbStatus)
	{
		case DBSTATUS_S_ISNULL:
		case DBSTATUS_S_DEFAULT:
		case DBSTATUS_S_IGNORE:
			hr = S_OK;
			goto CLEANUP;

		case DBSTATUS_S_TRUNCATED:
		case DBSTATUS_S_OK:
			break;

		default:
			hr = E_FAIL;
			goto CLEANUP;
	};

	if(pValue)
	{
		//Handle any special conversions ourselves...
		switch(DBTYPE_SRC_DST(pBinding->wType, DBTYPE_WSTR))
		{
			//DBTYPE_IUNKNOWN => DBTYPE_WSTR
			case DBTYPE_SRC_DST(DBTYPE_IUNKNOWN, DBTYPE_WSTR):
			case DBTYPE_SRC_DST(DBTYPE_IUNKNOWN | DBTYPE_BYREF, DBTYPE_WSTR):
			{
				//Handle BYREF as well. (simple enough)
				if(pBinding->wType & DBTYPE_BYREF)
					pValue = *(void**)pValue;
				
				//IUnknown is not a required conversion to string (WSTR)
				IUnknown* pIUnknown = *(IUnknown**)pValue;
				REFIID iid = pBinding->pObject ? pBinding->pObject->iid : IID_IUnknown;
				
				//Create a temporary stream wrapper...
				CStream  cStream(m_pCMainWindow);
				cStream.CreateObject(this, iid, pIUnknown);

				//Read the Stream Object (numerous different stream objects)
				//TODO64: Currently I*Stream::Read only takes a ULONG?
				if(FAILED(hr = cStream.ReadObject(iid, wBackendType, pwszValue, (ULONG)ulMaxSize)))
				{
					//I have no clue what type of object this is, or was unable to read the 
					//stream for some reason, so just display the pointer
					StringFormat(pwszValue, ulMaxSize, L"0x%p", pIUnknown);
				}

				//The refcount of the Stream now is 1. 
				//Our FreeBindingData frees outofline data...
				break;
			}

			default:
			{
				//Otherwise delegate...
				//NOTE: Make sure we indicate to DataConvert that the input buffer is only
				//as large as the specified length, but is bound by our allocated buffer size,
				//so it doesn't try and read beyond valid memory...
				XTESTC_(hr = DataConvert
					(
						dbStatus, 
						dbLength, 
						pBinding->cbMaxLen,
						pBinding->wType, 
						pValue, 
						pBinding->bPrecision, 
						pBinding->bScale, 
						
						DBTYPE_WSTR,
						
						//Status. 
						//Only update our status if returned successfully from the provider.
						dbStatus == DBSTATUS_S_OK ? &dbStatus : NULL,	
						NULL,
						pwszValue,
						ulMaxSize*sizeof(WCHAR),
						dwConvFlags
					),S_OK);
				
				
				//Indicate a sub type...
				if(pBinding->wType == DBTYPE_VARIANT)
				{
					VARIANT* pVariant = (VARIANT*)pValue;
					wSubType = pVariant->vt;
				}
				break;
			}
		};
	}
	
	//PostProcessing 
	if(SUCCEEDED(hr))
	{
		//Hexadecimal
		if(dwConvFlags & CONV_HEX)
		{
			switch(wBackendType)
			{
				case DBTYPE_I1:
				case DBTYPE_UI1:
				case DBTYPE_I2:
				case DBTYPE_UI2:
				case DBTYPE_I4:
				case DBTYPE_UI4:
					PostProcessString(pwszValue, ulMaxSize, dwConvFlags);
					break;

				default:
					break;
			};
		}

		//Schema Rowsets:
		if(m_bSchemaRowset && (dwConvFlags & CONV_TYPENAME))
		{
			//Special Handling for Known Schema Rowsets, 
			//map the "DBTYPE" column from UI2 to a textual name of the Type...
			if(
					(pBinding->iOrdinal == 2  	&& m_guidSource == DBSCHEMA_PROVIDER_TYPES)
				||	(pBinding->iOrdinal == 12 	&& m_guidSource == DBSCHEMA_COLUMNS)
				||	(pBinding->iOrdinal == 8  	&& m_guidSource == DBSCHEMA_TABLES_INFO)
				||	(pBinding->iOrdinal == 10	&& m_guidSource == DBSCHEMA_PROCEDURE_COLUMNS) 
			  )
			{
				ASSERT(wBackendType == DBTYPE_UI2);
				StringCopy(pwszValue, GetDBTypeName((DBTYPE)wcstol(pwszValue, NULL, 0)), ulMaxSize);
			}
		}
	}

CLEANUP:
	//Output Params
	if(pdbStatus)
		*pdbStatus = dbStatus;
	if(pdbLength)
		*pdbLength = dbLength;
	if(pwSubType)
		*pwSubType = wSubType;
	return hr;
}




////////////////////////////////////////////////////////////////
// CDataAccess::SetColumnData
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::SetColumnData(DBBINDING* pBinding, void* pData, DBSTATUS dbStatus, DBLENGTH dbLength, WCHAR* pwszValue, DWORD dwConvFlags, DBTYPE wBackendType)
{
	//NOTE: We ASSERT on pwszValue since DataConvert and even our conversion reqturns will fails
	//for NULL source.  If you really have a NULL string it should be since as an empty
	//string for conversion purposes and DataConvert will set length = 0...
	ASSERT(pwszValue);
	ASSERT(pBinding);

	HRESULT hr = S_OK;
	void* pValue = VALUE_IS_BOUND(*pBinding) ? &BINDING_VALUE(*pBinding, pData) : NULL; 
	DBSTATUS	dbDstStatus	=	dbStatus;
	DBLENGTH	cbDstLength =	0;

	//STATUS
	switch(dbStatus)
	{
		case DBSTATUS_S_OK:
		case DBSTATUS_S_TRUNCATED:
			break;

		default:
			//Any other Status, IGNORE, ISNULL, DEFAULT, ERROR, were done, nothing to convert...
			goto CLEANUP;
	}

	if(pValue)
	{
		//Handle any special conversions ourselves...
		switch(DBTYPE_SRC_DST(pBinding->wType, DBTYPE_WSTR))
		{
			//DBTYPE_IUNKNOWN => DBTYPE_WSTR
			case DBTYPE_SRC_DST(DBTYPE_IUNKNOWN, DBTYPE_WSTR):
			case DBTYPE_SRC_DST(DBTYPE_IUNKNOWN | DBTYPE_BYREF, DBTYPE_WSTR):
			{
				//Handle BYREF as well. (simple enough)
				if(pBinding->wType & DBTYPE_BYREF)
				{
					SAFE_ALLOC(*(void**)pValue, IUnknown*, 1);
					pValue = *(void**)pValue;
				}

				//Create the storage object to use for SetData.
				CStorageBuffer* pCStorageBuffer = new CStorageBuffer(m_pCMainWindow); //m_cRef=1
				WCHAR pBuffer[MAX_COL_SIZE] = {0};

				//First Convert the user entered data into the backend format...
				//So the stream is a native stream of bytes to set into the backend...
				XTESTC_(hr = DataConvert
					(
						dbStatus, 
						dbLength * sizeof(WCHAR), 
						dbLength * sizeof(WCHAR) + sizeof(WCHAR),
						DBTYPE_WSTR,
						pwszValue,
						pBinding->bPrecision,
						pBinding->bScale, 
						
						(wBackendType == DBTYPE_IUNKNOWN || wBackendType == (DBTYPE_BYREF|DBTYPE_IUNKNOWN))
							? DBTYPE_BYTES : wBackendType,
						
						&dbDstStatus,
						&cbDstLength,
						pBuffer,
						sizeof(pBuffer),
						dwConvFlags
					),S_OK);

				//Now, Set the user entered data into our storage object.
				//NOTE:  We set the Length = total bytes in stream, since some providers
				//requires this ahead of time.  And we reset the stream so the current seek
				//is at the head for when the provider begins to read from the stream on SetData
				//TODO64:  I*Stream::Write only takes a ULONG
				pCStorageBuffer->WriteBuffer(0, pBuffer, (ULONG)cbDstLength, NULL);
				pCStorageBuffer->Seek(0);
				
				//Passing the object pointer should be suffiencent enough, as the provider
				//will have to QI of the object anyway to determine if it even supports
				//the interface, but since many incorrectly do not we will explictly
				//QI here so the majority of the providers don't crash
				IUnknown* pIUnknown = NULL;
				XTESTC_(pCStorageBuffer->QueryInterface(pBinding->pObject ? pBinding->pObject->iid : IID_IUnknown, (void**)&pIUnknown), S_OK);
				*(IUnknown**)pValue = pIUnknown;

				//The refcount of the Stream now is 2. 
				//The provider releases one, and our FreeBindingData fress outofline data...
				break;
			}

			default:
			{
				//Otherwise delegate...
				XTESTC_(hr = DataConvert
					(
						dbStatus, 
						dbLength * sizeof(WCHAR), 
						dbLength * sizeof(WCHAR) + sizeof(WCHAR),
						DBTYPE_WSTR,
						pwszValue,
						pBinding->bPrecision,
						pBinding->bScale, 
						
						pBinding->wType,
						&dbDstStatus,
						&cbDstLength,
						pValue,
						pBinding->cbMaxLen,
						dwConvFlags
					),S_OK);
				break;
			}
		};
	}

CLEANUP:
	if(STATUS_IS_BOUND(*pBinding))
		BINDING_STATUS(*pBinding, pData) = dbDstStatus;
	if(LENGTH_IS_BOUND(*pBinding))
		BINDING_LENGTH(*pBinding, pData) = cbDstLength;
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataAccess::GetColumnsRowset
//
/////////////////////////////////////////////////////////////////
HRESULT CDataAccess::GetColumnsRowset(CAggregate* pCAggregate, BOOL fOptColumns, REFIID riid, ULONG cPropSets, DBPROPSET* rgPropSets, IUnknown** ppIUnknown)
{
	DBORDINAL i,cOptColumns = 0;
	DBID* rgOptColumns = 0;
	HRESULT hr = S_OK;

	if(!m_pIColumnsRowset)
		return E_FAIL;

	//GetAvailableColumns
	//We just use cRestrictions passed in as the flag
	//to indicate weither to use Optional Columns
	if(fOptColumns)
	{
		XTEST(hr = m_pIColumnsRowset->GetAvailableColumns(&cOptColumns, &rgOptColumns));
		TESTC(TRACE_METHOD(hr, L"IColumnsRowset::GetAvailableColumns(&%lu, &0x%p)", cOptColumns, rgOptColumns));
	}

	//GetColumnsRowset
	XTEST_(hr = m_pIColumnsRowset->GetColumnsRowset(
						pCAggregate,		// punkOuter
						cOptColumns,		// cOptionalColumns
						rgOptColumns,		// rgOptionalColumns
						riid,				// rowset interface
						cPropSets,			// # of properties
						rgPropSets,			// properties
						ppIUnknown),S_OK);	// rowset pointer
	TRACE_METHOD(hr, L"IColumnsRowset::GetColumnsRowset(0x%p, %lu, 0x%p, %s, %d, 0x%p, &0x%p)", pCAggregate, cOptColumns, rgOptColumns, GetInterfaceName(riid), cPropSets, rgPropSets, ppIUnknown ? *ppIUnknown : NULL);

	//Display Errors (if occurred)
	TESTC(hr = DisplayPropErrors(hr, cPropSets, rgPropSets));

	//Handle Aggregation
	if(pCAggregate)
		TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));

CLEANUP:
	//FreeDBIDs
	for(i=0; i<cOptColumns; i++)
		DBIDFree(&rgOptColumns[i]);
	SAFE_FREE(rgOptColumns);
	return hr;
}

				
/////////////////////////////////////////////////////////////////
// CRowset::CRowset
//
/////////////////////////////////////////////////////////////////
CRowset::CRowset(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild) 
	: CDataAccess(eCRowset, pCMainWindow, pCMDIChild)
{
	//Rowset
//	m_pIAccessor					= NULL;//DataAccess Base Class
//	m_pIColumnsInfo					= NULL;//DataAccess Base Class
//	m_pIConvertType					= NULL;//DataAccess Base Class
	m_pIRowset						= NULL;//Rowset Interface
	m_pIRowsetInfo					= NULL;//Rowset Interface
	m_pIRowsetChange				= NULL;//Rowset Interface
	m_pIRowsetIdentity				= NULL;//Rowset Interface
	m_pIRowsetLocate				= NULL;//Rowset Interface
	m_pIRowsetFind					= NULL;//Rowset Interface
	m_pIRowsetView					= NULL;//Rowset Interface
	m_pIChapteredRowset				= NULL;//Rowset Interface
	m_pIRowsetResynch				= NULL;//Rowset Interface
	m_pIRowsetRefresh				= NULL;//Rowset Interface
	m_pIRowsetScroll				= NULL;//Rowset Interface
	m_pIRowsetUpdate				= NULL;//Rowset Interface
	m_pIGetRow						= NULL;//Rowset Interface

	//Extra Interfaces
	m_dwCookieRowsetNotify			= 0;

	//Chapters
	m_hChapter			= DB_NULL_HCHAPTER;
}


/////////////////////////////////////////////////////////////////
// CRowset::~CRowset
//
/////////////////////////////////////////////////////////////////
CRowset::~CRowset()
{
	ReleaseObject(0);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CRowset::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CRowset::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(IRowset);
	HANDLE_GETINTERFACE(IRowsetInfo);
	HANDLE_GETINTERFACE(IRowsetChange);
	HANDLE_GETINTERFACE(IRowsetIdentity);
	HANDLE_GETINTERFACE(IRowsetLocate);
	HANDLE_GETINTERFACE(IRowsetFind);
	HANDLE_GETINTERFACE(IRowsetView);
	HANDLE_GETINTERFACE(IChapteredRowset);
	HANDLE_GETINTERFACE(IRowsetResynch);
	HANDLE_GETINTERFACE(IRowsetRefresh);
	HANDLE_GETINTERFACE(IRowsetScroll);
	HANDLE_GETINTERFACE(IRowsetUpdate);
	HANDLE_GETINTERFACE(IGetRow);

	//Otherwise delegate
	return CDataAccess::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First, so we have IConnectionPointContainer
	CDataAccess::AutoQI(dwCreateOpts);

	//[MANDATORY] Obtain [mandatory] interfaces
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(IRowset);
		OBTAIN_INTERFACE(IRowsetInfo);
	}

	//Auto QI
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
		//Obtain [optional] interfaces
		OBTAIN_INTERFACE(IRowsetChange);
		OBTAIN_INTERFACE(IRowsetIdentity);
		OBTAIN_INTERFACE(IRowsetLocate);
		OBTAIN_INTERFACE(IRowsetFind);
		OBTAIN_INTERFACE(IRowsetView);
		OBTAIN_INTERFACE(IChapteredRowset);
		OBTAIN_INTERFACE(IRowsetResynch);
		OBTAIN_INTERFACE(IRowsetRefresh);
		OBTAIN_INTERFACE(IRowsetScroll);
		OBTAIN_INTERFACE(IRowsetUpdate);
		OBTAIN_INTERFACE(IGetRow);
	}

	//Listeners
	AdviseListener(IID_IRowsetNotify,	&m_dwCookieRowsetNotify);
	return S_OK;
}


/////////////////////////////////////////////////////////////////
// CRowset::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::AutoRelease()
{
	//Data

	//Rowset
	RELEASE_INTERFACE(IRowset);
	RELEASE_INTERFACE(IRowsetInfo);
	RELEASE_INTERFACE(IRowsetChange);
	RELEASE_INTERFACE(IRowsetIdentity);
	RELEASE_INTERFACE(IRowsetLocate);
	RELEASE_INTERFACE(IRowsetFind);
	RELEASE_INTERFACE(IRowsetView);
	RELEASE_INTERFACE(IChapteredRowset);
	RELEASE_INTERFACE(IRowsetResynch);
	RELEASE_INTERFACE(IRowsetRefresh);
	RELEASE_INTERFACE(IRowsetScroll);
	RELEASE_INTERFACE(IRowsetUpdate);
	RELEASE_INTERFACE(IGetRow);

	//Don't Unadvise the Listeners until the Rowset goes away.
	//We want to receive and Display the ROWSET_RELEASE notifications
//	UnadviseListener(IID_IRowsetNotify,		&m_dwCookieRowsetNotify);

	//Delegate
	return CDataAccess::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::DisplayObject
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::DisplayObject()
{
	HRESULT hr = S_OK;

	BINDCOLS eBindCols = (GetOptions()->m_dwAccessorOpts & ACCESSOR_BIND_BOOKMARK ? BIND_ALLCOLS : BIND_ALLCOLSEXPECTBOOKMARK);
	if(m_pCMDIChild)
	{
		//Reset Cursor
		m_pCMDIChild->m_fLastFetchForward = FALSE;
		m_pCMDIChild->m_lCurPos = 0;

		//First Clear the existing Window...
		TESTC(hr = m_pCMDIChild->m_pCDataGrid->ClearAll());
	}

	//Create ColumnInfo
	TESTC(hr = GetColInfo());

	//Create Accessors and Setup bindings
	TESTC(hr = CreateAccessors(eBindCols));

	if(m_pCMDIChild)
	{
		//Refresh the Columns and Rows
		TESTC(hr = m_pCMDIChild->RefreshData());
	}

	//Display the object...
	TESTC(hr = CDataAccess::DisplayObject());

CLEANUP:
	if(m_pCMDIChild)
		m_pCMDIChild->UpdateControls();
	return hr;
}


/////////////////////////////////////////////////////////////////////////////
// CRowset::GetObjectDesc
//
/////////////////////////////////////////////////////////////////////////////
WCHAR* CRowset::GetObjectDesc()
{
	if(!m_pwszObjectDesc && m_guidSource != GUID_NULL)
	{
		//Schema Rowset
		if(m_bSchemaRowset)
		{
			//Lookup the "Friendly Name" of the Schema Rowset...
			m_pwszObjectDesc = wcsDuplicate(GetSchemaName(m_guidSource));
		}
		else if(m_guidSource == IID_IColumnsRowset)
		{
			//What interface created this...
			m_pwszObjectDesc = wcsDuplicate(GetInterfaceName(m_guidSource));
		}
	}

	return m_pwszObjectDesc;
}


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::ValidateRow
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::ValidateRow(HROW hRow, ULONG ulRefCount)
{
	//Warn user about NULL Rowhandles...
	if(hRow == DB_NULL_HROW || ulRefCount == 0)
	{
		if(IDNO == wMessageBox
			(
				GetFocus(), 
				MB_TASKMODAL | MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1, 
				wsz_ERROR, 
				L"hRow == 0x%p\n"
				L"%s\n\n"
				L"This may crash your Provider...\n"
				L"Do you wish to continue anyway?", 
				hRow,
				hRow == DB_NULL_HROW ? L"Invalid Row Handle" : L"Released Row Handle"
				)
			)
			return E_FAIL;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////
// HRESULT CRowset::GetData
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::GetData(REFIID riidSource, HROW hRow, HACCESSOR hAccessor, void* pData)
{
	//Since GetData is the only OLE DB method that is allowed to crash
	//if given invalid argumenets (for effiecientcy - provider speicific
	//weither it validates arguments), we should check the params and at the 
	//very least warn the user...
	HRESULT hr = E_FAIL;

	//Defaults
	if(hAccessor == NULL)
		hAccessor = m_hAccessor;
	if(pData == NULL)
		pData = m_pData;

	//Check Arguments...
	TESTC(hr = ValidateRow(hRow));
	TESTC(hr = ValidateAccessor(hAccessor));

	//GetData
 	if(riidSource == IID_IRowset)
	{
		//IRowset::GetData
		if(m_pIRowset)
		{
			XTEST(hr = m_pIRowset->GetData(hRow, hAccessor, pData));
			TESTC(TRACE_METHOD(hr, L"IRowset::GetData(0x%p, 0x%p, 0x%p)", hRow, hAccessor, pData));
		}
	}
 	else if(riidSource == IID_IRowsetLocate)
	{
		//IRowsetLocate::GetData
		if(m_pIRowsetLocate)
		{
			XTEST(hr = m_pIRowsetLocate->GetData(hRow, hAccessor, pData));
			TESTC(TRACE_METHOD(hr, L"IRowsetLocate::GetData(0x%p, 0x%p, 0x%p)", hRow, hAccessor, pData));
		}
	}
 	else if(riidSource == IID_IRowsetScroll)
	{
		//IRowsetScroll::GetData
		if(m_pIRowsetScroll)
		{
			XTEST(hr = m_pIRowsetScroll->GetData(hRow, hAccessor, pData));
			TESTC(TRACE_METHOD(hr, L"IRowsetScroll::GetData(0x%p, 0x%p, 0x%p)", hRow, hAccessor, pData));
		}
	}
 	else if(riidSource == IID_IRowsetUpdate)
	{
		//IRowsetUpdate::GetOriginalData
		if(m_pIRowsetUpdate)
		{
			XTEST(hr = m_pIRowsetUpdate->GetOriginalData(hRow, hAccessor, pData));
			TESTC(TRACE_METHOD(hr, L"IRowsetUpdate::GetOriginalData(0x%p, 0x%p, 0x%p)", hRow, hAccessor, pData));
		}
	}
 	else if(riidSource == IID_IRowsetResynch)
	{
		//IRowsetResynch::GetVisibleData
		if(m_pIRowsetResynch)
		{
			XTEST(hr = m_pIRowsetResynch->GetVisibleData(hRow, hAccessor, pData));
			TESTC(TRACE_METHOD(hr, L"IRowsetResynch::GetVisibleData(0x%p, 0x%p, 0x%p)", hRow, hAccessor, pData));
		}
	}
 	else if(riidSource == IID_IRowsetRefresh)
	{
		//IRowsetRefresh::GetLastVisibleData
		if(m_pIRowsetRefresh)
		{
			XTEST(hr = m_pIRowsetRefresh->GetLastVisibleData(hRow, hAccessor, pData));
			TESTC(TRACE_METHOD(hr, L"IRowsetRefresh::GetLastVisibleData(0x%p, 0x%p, 0x%p)", hRow, hAccessor, pData));
		}
	}
	else
	{
		ASSERT(!"Unhandled Source!");
	}

CLEANUP:
	return hr;
}	


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::GetBookmark
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::GetBookmark(HROW hRow, DBBKMARK* pcbBookmark, BYTE** ppBookmark)
{
	ASSERT(pcbBookmark);
	ASSERT(ppBookmark);
	HRESULT hr = S_OK;
	*pcbBookmark = 0;
	*ppBookmark = NULL;
	
	DBSTATUS dbStatus = 0;
	BYTE* pData = NULL;

	//Make sure we have a bookmark...
	if(m_cColInfo==0 || m_rgColumnInfo==NULL || m_rgColumnInfo[0].iOrdinal!=0)
		return E_FAIL;
	
	//Obtain the maximum bookmark size...
	DBLENGTH ulMaxBmkSize = ROUNDUP(GetMaxDisplaySize(DBTYPE_BYTES, m_rgColumnInfo[0].wType, m_rgColumnInfo[0].ulColumnSize, MAX_COL_SIZE));

	//Deferred Accessor Creation
	if(m_hBmkAccessor==NULL)
	{
		//Static bindings
		//Design the bindigs so the value is first and status length last.  This way we can return
		//the bookmark memory, the rest of the code can access the bookmark directly, and we can free
		//all the memory as well starting with the bookmark address...
		const DBCOUNTITEM cBindings = 1;
		DBBINDING rgBindings[cBindings] = 
			{
				0,
				0,									//VALUE
				ulMaxBmkSize,						//LENGTH
				ulMaxBmkSize + sizeof(DBLENGTH),	//STATUS
				NULL,			
				NULL, 		
				NULL,		
				DBPART_VALUE|DBPART_LENGTH|DBPART_STATUS,
				DBMEMOWNER_CLIENTOWNED,
				DBPARAMIO_NOTPARAM,
				ulMaxBmkSize + sizeof(DBLENGTH) + sizeof(DBSTATUS),
				0, 				
				DBTYPE_BYTES, 	
				0,	
				0, 				
			};

		//Now create the accessor...
		TESTC(hr = CreateAccessor(DBACCESSOR_ROWDATA, cBindings, rgBindings, 0, &m_hBmkAccessor));
	}

	//Allocate enough space for the bookmark, (including status and length of course)
	SAFE_ALLOC(pData, BYTE, ulMaxBmkSize + sizeof(DBLENGTH) + sizeof(DBSTATUS));

	//GetData to obtain Bookmark value (delegate)
	TESTC(hr = GetData(IID_IRowset, hRow, m_hBmkAccessor, pData));
	
	//Length

	dbStatus = *(DBSTATUS*)(pData + ulMaxBmkSize + sizeof(DBLENGTH));
	if(dbStatus == DBSTATUS_S_OK)
	{
		*pcbBookmark = *(ULONG*)(pData + ulMaxBmkSize);	//LENGTH
		*ppBookmark = pData;							//VALUE
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::GetChapter
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::GetChapter(HROW hRow, DBORDINAL iOrdinal, HCHAPTER* phChapter)
{
	ASSERT(hRow);
	ASSERT(phChapter);
	HRESULT hr = S_OK;
	HACCESSOR hAccessor = NULL;
	
	//Initialize in case of ISNULL data...
	*phChapter = NULL;

	//Bind only the Chapter column...
	const static DBCOUNTITEM cBindings = 1;
	DBBINDING rgBindings[cBindings] = 
	{
			iOrdinal,
			0,	//pData = phChapter + 0 offset = phChapter
			0,
			0,	
			NULL,			
			NULL, 		
			NULL,		
			DBPART_VALUE,
			DBMEMOWNER_CLIENTOWNED,		
			DBPARAMIO_NOTPARAM, 
			sizeof(HCHAPTER),
			0, 				
			DBTYPE_HCHAPTER,
			0,	
			0, 				
	};

	//Create the Accessor...
	TESTC(hr = CreateAccessor(DBACCESSOR_ROWDATA, cBindings, rgBindings, 0, &hAccessor));

	//GetData to obtain Bookmark value (delegate)
	TESTC(hr = GetData(IID_IRowset, hRow, hAccessor, phChapter));
	
CLEANUP:
	ReleaseAccessor(&hAccessor);
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::RestartPosition
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::RestartPosition()
{
	HRESULT hr = E_FAIL;

	//IRowset::RestartPosition
	if(m_pIRowset)
	{
		XTEST(hr = m_pIRowset->RestartPosition(m_hChapter));
		TESTC(TRACE_METHOD(hr, L"IRowset::RestartPosition(0x%p)", m_hChapter));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::GetNextRows
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::GetNextRows(DBROWOFFSET lOffset, DBROWCOUNT cRows, DBCOUNTITEM* pcRowsObtained, HROW** prghRows)
{
	HRESULT hr = E_FAIL;

	DBCOUNTITEM cRowsObtained = 0;
	HROW* rghRows = NULL;
	if(prghRows)
		rghRows = *prghRows;

	if(m_pIRowset)
	{
		//GetNextRows
		XTEST(hr = m_pIRowset->GetNextRows(
			m_hChapter,					// hChapter
			lOffset,					// lOffset
			cRows,						// cRows
			&cRowsObtained,				// cRowsObtained
			&rghRows));					// rghRows
		TESTC(TRACE_METHOD(hr, L"IRowset::GetNextRows(0x%p, %ld, %ld, &%lu, &0x%p)", m_hChapter, lOffset, cRows, cRowsObtained, rghRows));
	}

CLEANUP:
	if(pcRowsObtained)
		*pcRowsObtained = cRowsObtained;
	
	if(prghRows)
		*prghRows = rghRows;
	else
		SAFE_FREE(rghRows);
	return hr;
}	


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::AddRefRows
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::AddRefRows(DBROWCOUNT cRows, HROW* rghRows, ULONG* rgRefCounts)
{
	HRESULT hr = E_FAIL;

	//Alloc Array for Status
	DBROWSTATUS* rgRowStatus = NULL;
	SAFE_ALLOC(rgRowStatus, DBROWSTATUS, cRows);

	if(m_pIRowset)
	{
		//AddRefRows
		XTEST(hr = m_pIRowset->AddRefRows(cRows, rghRows, rgRefCounts, rgRowStatus));
		DisplayRowErrors(hr, cRows, rghRows, rgRowStatus);
		TESTC(TRACE_METHOD(hr, L"IRowset::AddRefRows(%lu, 0x%p, 0x%p, 0x%p)", cRows, rghRows, rgRefCounts, rgRowStatus));
	}

CLEANUP:
	SAFE_FREE(rgRowStatus);
	return hr;
}	


/////////////////////////////////////////////////////////////////
// HRESULT CRowset::ReleaseRows
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::ReleaseRows(DBROWCOUNT cRows, HROW* rghRows, ULONG* rgRefCounts)
{
	HRESULT hr = E_FAIL;
	DBROWSTATUS* rgRowStatus = NULL;

	if(m_pIRowset)
	{
		//Alloc Array for Status
		SAFE_ALLOC(rgRowStatus, DBROWSTATUS, cRows);

		//ReleaseRows
		XTEST(hr = m_pIRowset->ReleaseRows(cRows, rghRows, NULL, rgRefCounts, rgRowStatus));
		DisplayRowErrors(hr, cRows, rghRows, rgRowStatus);
		TESTC(TRACE_METHOD(hr, L"IRowset::ReleaseRows(%lu, 0x%p, NULL, 0x%p, 0x%p)", cRows, rghRows, rgRefCounts, rgRowStatus));
	}

CLEANUP:
	SAFE_FREE(rgRowStatus);
	return hr;
}	


#ifdef INTERNAL_ONLY
/////////////////////////////////////////////////////////////////
// HRESULT CRowset::InvokeCursorEngine
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::InvokeCursorEngine(IUnknown* pIUnkRowset, ULONG cPropSets, DBPROPSET* rgPropSets, REFIID riid, IUnknown** ppIUnknown)
{
	HRESULT				hr = S_OK;				// HRESULT
	IFoxService* pIFoxService = NULL;
	IServiceProperties* pIServiceProperties = NULL;

	//Arguments
	ASSERT(pIUnkRowset);

	//Obtain the CursorEngine
	XTESTC(hr = m_pCMainWindow->m_pCRootEnumerator->CreateInstance(NULL, CLSID_FoxRowset, CLSCTX_ALL, IID_IFoxService, (IUnknown**)&pIFoxService));

	//Set requested properties
	if(cPropSets)
	{
		//Obtain the IServiceProperties interface
		TESTC(hr = TRACE_QI(pIFoxService, IID_IServiceProperties, (IUnknown**)&pIServiceProperties, L"IFoxService"));
		
		//IServiceProperties::SetRequestedProperties
		XTEST(hr = pIServiceProperties->SetRequestedProperties(cPropSets, rgPropSets));
		TESTC(TRACE_METHOD(hr, L"IServiceProperties::SetRequestedProperties(%d, 0x%p)", cPropSets, rgPropSets));
	}
	
	//Invoke the CE on top of our existing rowset...
	XTEST(hr = pIFoxService->InvokeService(riid, pIUnkRowset, ppIUnknown));
	TESTC(TRACE_METHOD(hr, L"IFoxService::InvokeService(%s, 0x%p, &0x%p)", GetInterfaceName(riid), pIUnkRowset, ppIUnknown ? *ppIUnknown : NULL));

CLEANUP:
	SAFE_RELEASE(pIFoxService);
	SAFE_RELEASE(pIServiceProperties);
	return hr;
}
#endif //INTERNAL_ONLY


/////////////////////////////////////////////////////////////////
//	HRESULT CRowset::GetRowFromHROW
//
/////////////////////////////////////////////////////////////////
HRESULT CRowset::GetRowFromHROW(CAggregate* pCAggregate, HROW hRow, REFIID riid, IUnknown** ppIUnknown)
{
	HRESULT hr = E_FAIL;
	
	if(m_pIGetRow)
	{
		//IGetRow::GetRowFromHROW
		XTEST(hr = m_pIGetRow->GetRowFromHROW(pCAggregate, hRow, riid, ppIUnknown));
		TESTC(TRACE_METHOD(hr, L"IGetRow::GetRowFromHROW(0x%p, 0x%p, %s, &0x%p)", pCAggregate, hRow, GetInterfaceName(riid), ppIUnknown ? *ppIUnknown : NULL));

		//Handle Aggregation
		if(pCAggregate)
			TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));
	}
	
CLEANUP:
	return hr;
}

							
