/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 99 <company name>
//
//	Module Name:
//		SmbSmp.cpp
//
//	Description:
//		Resource DLL for SMB Sample (SmbSmp).
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 99
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#include "ClRes.h"
#include <lm.h>
#include <lmerr.h>

//
// Type and constant definitions.
//

// ADDPARAM: Add new properties here.
#define PROP_NAME__SHARENAME L"ShareName"
#define PROP_NAME__PATH L"Path"
#define PROP_NAME__REMARK L"Remark"
#define PROP_NAME__MAXUSERS L"MaxUsers"

#define PROP_MIN__MAXUSERS		(0)
#define PROP_MAX__MAXUSERS		(4294967295)
#define PROP_DEFAULT__MAXUSERS	(0)

// ADDPARAM: Add new properties here.
typedef struct _SMBSMP_PROPS
{
	PWSTR			pszShareName;
	PWSTR			pszPath;
	PWSTR			pszRemark;
	DWORD			nMaxUsers;
} SMBSMP_PROPS, * PSMBSMP_PROPS;

typedef struct _SMBSMP_RESOURCE
{
	RESID					resid; // For validation
	SMBSMP_PROPS			propsActive; // The active props.  Used for program flow and control when the resource is online.
	SMBSMP_PROPS			props; // The props in cluster DB.  May differ from propsActive until OnlineThread reloads them as propsActive.
	HCLUSTER				hCluster;
	HRESOURCE				hResource;
	HKEY					hkeyParameters;
	RESOURCE_HANDLE 		hResourceHandle;
	LPWSTR					pszResourceName;
	CLUS_WORKER 			cwWorkerThread;
	CLUSTER_RESOURCE_STATE	state;
	WCHAR					szComputerName[ MAX_COMPUTERNAME_LENGTH + 1 ];
} SMBSMP_RESOURCE, * PSMBSMP_RESOURCE;


//
// Global data.
//

// Forward reference to our RESAPI function table.

extern CLRES_FUNCTION_TABLE g_SmbSmpFunctionTable;

//
// SMB Sample resource read-write private properties.
//
RESUTIL_PROPERTY_ITEM
SmbSmpResourcePrivateProperties[] =
{
	{ PROP_NAME__SHARENAME, NULL, CLUSPROP_FORMAT_SZ, 0, 0, 0, RESUTIL_PROPITEM_REQUIRED, FIELD_OFFSET( SMBSMP_PROPS, pszShareName ) },
	{ PROP_NAME__PATH, NULL, CLUSPROP_FORMAT_SZ, 0, 0, 0, RESUTIL_PROPITEM_REQUIRED, FIELD_OFFSET( SMBSMP_PROPS, pszPath ) },
	{ PROP_NAME__REMARK, NULL, CLUSPROP_FORMAT_SZ, 0, 0, 0, 0, FIELD_OFFSET( SMBSMP_PROPS, pszRemark ) },
	{ PROP_NAME__MAXUSERS, NULL, CLUSPROP_FORMAT_DWORD, PROP_DEFAULT__MAXUSERS, PROP_MIN__MAXUSERS, PROP_MAX__MAXUSERS, 0, FIELD_OFFSET( SMBSMP_PROPS, nMaxUsers ) },
	{ 0 }
};

//
// Registry key checkpoints.
//
LPCWSTR g_pszRegKeysSmbSmp[] =
{
	// TODO: Specify any registry keys to be checkpointed for resources of this type
	// e.g. L"System\\CurrentControlSet\\Services\\myservice",
	NULL
};

//
// Crypto key checkpoints.
//
LPCWSTR g_pszCryptoKeysSmbSmp[] =
{
	// TODO: Specify any crypto keys to be checkpointed for resources of this type
	// e.g. L"1\\My Provider v1.0\\MYACRONYM",
	NULL
};

//
// Domestic crypto key checkpoints.
//
LPCWSTR g_pszDomesticCryptoKeysSmbSmp[] =
{
	// TODO: Specify any domestic crypto keys to be checkpointed for resources of this type
	// e.g. L"1\\My Enhanced Provider v1.0\\MYACRONYM_128",
	NULL
};

//
// Function prototypes.
//

RESID WINAPI SmbSmpOpen(
	IN	LPCWSTR			pszResourceName,
	IN	HKEY			hkeyResourceKey,
	IN	RESOURCE_HANDLE	hResourceHandle
	);

void WINAPI SmbSmpClose( IN RESID resid );

DWORD WINAPI SmbSmpOnline(
	IN		RESID	resid,
	IN OUT	PHANDLE	phEventHandle
	);

DWORD WINAPI SmbSmpOnlineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PSMBSMP_RESOURCE	pResourceEntry
	);

DWORD WINAPI SmbSmpOffline( IN RESID resid );

DWORD WINAPI SmbSmpOfflineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PSMBSMP_RESOURCE		pResourceEntry
	);

void WINAPI SmbSmpTerminate( IN RESID resid );

BOOL WINAPI SmbSmpLooksAlive( IN RESID resid );

BOOL WINAPI SmbSmpIsAlive( IN RESID resid );

BOOL SmbSmpCheckIsAlive(
	IN PSMBSMP_RESOURCE	pResourceEntry,
	IN BOOL				bFullCheck
	);

DWORD WINAPI SmbSmpResourceControl(
	IN	RESID	resid,
	IN	DWORD	nControlCode,
	IN	PVOID	pInBuffer,
	IN	DWORD	cbInBufferSize,
	OUT	PVOID	pOutBuffer,
	IN	DWORD	cbOutBufferSize,
	OUT	LPDWORD	pcbBytesReturned
	);

DWORD SmbSmpGetPrivateResProperties(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	OUT		PVOID	pOutBuffer,
	IN		DWORD	cbOutBufferSize,
	OUT		LPDWORD	pcbBytesReturned
	);

DWORD SmbSmpValidatePrivateResProperties(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	IN		const PVOID	pInBuffer,
	IN		DWORD		cbInBufferSize,
	OUT		PSMBSMP_PROPS	pProps
	);

DWORD SmbSmpSetPrivateResProperties(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	IN		const PVOID	pInBuffer,
	IN		DWORD		cbInBufferSize
	);

DWORD SmbSmpSetNameHandler(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	IN		LPWSTR				pszName
	);


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpDllMain
//
//	Description:
//		Main DLL entry point for the SMB Sample resource type.
//
//	Arguments:
//		DllHandle	[IN] DLL instance handle.
//		Reason		[IN] Reason for being called.
//		Reserved	[IN] Reserved argument.
//
//	Return Value:
//		TRUE		Success.
//		FALSE		Failure.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOLEAN WINAPI SmbSmpDllMain(
	IN	HINSTANCE	hDllHandle,
	IN	DWORD		nReason,
	IN	LPVOID		Reserved
	)
{
	switch ( nReason )
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls( hDllHandle );
			break;

		case DLL_PROCESS_DETACH:
			break;

	} // switch: nReason

	return TRUE;

} //*** SmbSmpDllMain()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpStartup
//
//	Description:
//		Startup the resource DLL for the SMB Sample resource type.
//		This routine verifies that at least one currently supported version
//		of the resource DLL is between nMinVersionSupported and
//		nMaxVersionSupported. If not, then the resource DLL should return
//		ERROR_REVISION_MISMATCH.
//
//		If more than one version of the resource DLL interface is supported
//		by the resource DLL, then the highest version (up to
//		nMaxVersionSupported) should be returned as the resource DLL's
//		interface. If the returned version is not within range, then startup
//		fails.
//
//		The Resource Type is passed in so that if the resource DLL supports
//		more than one Resource Type, it can pass back the correct function
//		table associated with the Resource Type.
//
//	Arguments:
//		pszResourceType [IN]
//			Type of resource requesting a function table.
//
//		nMinVersionSupported [IN]
//			Minimum resource DLL interface version supported by the cluster
//			software.
//
//		nMaxVersionSupported [IN]
//			Maximum resource DLL interface version supported by the cluster
//			software.
//
//		pfnSetResourceStatus [IN]
//			Pointer to a routine that the resource DLL should call to update
//			the state of a resource after the Online or Offline routine
//			have returned a status of ERROR_IO_PENDING.
//
//		pfnLogEvent [IN]
//			Pointer to a routine that handles the reporting of events from
//			the resource DLL.
//
//		pFunctionTable [IN]
//			Returns a pointer to the function table defined for the version
//			of the resource DLL interface returned by the resource DLL.
//
//	Return Value:
//		ERROR_SUCCESS
//			The operation was successful.
//
//		ERROR_CLUSTER_RESNAME_NOT_FOUND
//			The resource type name is unknown by this DLL.
//
//		ERROR_REVISION_MISMATCH
//			The version of the cluster service doesn't match the version of
//			the DLL.
//
//		Win32 error code
//			The operation failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpStartup(
	IN	LPCWSTR							pszResourceType,
	IN	DWORD							nMinVersionSupported,
	IN	DWORD							nMaxVersionSupported,
	IN	PSET_RESOURCE_STATUS_ROUTINE	pfnSetResourceStatus,
	IN	PLOG_EVENT_ROUTINE				pfnLogEvent,
	OUT	PCLRES_FUNCTION_TABLE * 		pFunctionTable
	)
{
	DWORD nStatus;

	if (   (nMinVersionSupported > CLRES_VERSION_V1_00)
		|| (nMaxVersionSupported < CLRES_VERSION_V1_00) )
	{
		nStatus = ERROR_REVISION_MISMATCH;
	} // if: version not supported
	else if ( lstrcmpiW( pszResourceType, SMBSMP_RESNAME ) != 0 )
	{
		//
		// This check is also performed by the Startup() in CLRES.CPP.
		//
		nStatus = ERROR_CLUSTER_RESNAME_NOT_FOUND;
	} // if: resource type name not supported
	else
	{
		if ( g_pfnLogEvent == NULL )
		{
			g_pfnLogEvent = pfnLogEvent;
			g_pfnSetResourceStatus = pfnSetResourceStatus;
		} // if:  function pointers specified
		*pFunctionTable = &g_SmbSmpFunctionTable;
		nStatus = ERROR_SUCCESS;
	} // else: we support this type of resource

	return nStatus;

} //*** SmbSmpStartup()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpOpen
//
//	Description:
//		Open routine for SMB Sample resources.
//
//		Open the specified resource (create an instance of the resource).
//		Allocate all structures necessary to bring the specified resource
//		online.
//
//	Arguments:
//		pszResourceName [IN]
//			Supplies the name of the resource to open.
//
//		hkeyResourceKey [IN]
//					Supplies handle to the resource's cluster database key.
//
//		hResourceHandle [IN]
//			A handle that is passed back to the Resource Monitor when the
//			SetResourceStatus or LogEvent method is called.  See the
//			description of the pfnSetResourceStatus and pfnLogEvent arguments
//			to the SmbSmpStartup routine.  This handle should never be
//			closed or used for any purpose other than passing it as an
//			argument back to the Resource Monitor in the SetResourceStatus or
//			LogEvent callbacks.
//
//	Return Value:
//		resid
//			RESID of opened resource.
//
//		NULL
//			Error occurred opening the resource.  Resource Monitor may call
//			GetLastError() to get more details on the error.
//
//--
/////////////////////////////////////////////////////////////////////////////
RESID WINAPI SmbSmpOpen(
	IN	LPCWSTR			pszResourceName,
	IN	HKEY			hkeyResourceKey,
	IN	RESOURCE_HANDLE	hResourceHandle
	)
{
	DWORD				nStatus;
	RESID				resid = 0;
	HKEY				hkeyParameters = NULL;
	PSMBSMP_RESOURCE	pResourceEntry = NULL;
	DWORD				cchComputerName = sizeof( pResourceEntry->szComputerName );

	do											// Loop to avoid goto's.
	{
		//
		// Open the Parameters registry key for this resource.
		//
		nStatus = ClusterRegOpenKey(
						hkeyResourceKey,
						L"Parameters",
						KEY_ALL_ACCESS,
						&hkeyParameters
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Open: Unable to open Parameters key. Error: %1!u!.\n",
				nStatus
				);
			break;
		} // if: error creating the Parameters key for the resource

		//
		// Allocate a resource entry.
		//
		pResourceEntry = static_cast< SMBSMP_RESOURCE * >(
			LocalAlloc( LMEM_FIXED, sizeof( SMBSMP_RESOURCE ) )
			);
		if ( pResourceEntry == NULL )
		{
			nStatus = GetLastError();
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Open: Unable to allocate resource entry structure. Error: %1!u!.\n",
				nStatus
				);
			break;
		} // if: error allocating memory for the resource

		//
		// Initialize the resource entry..
		//
		ZeroMemory( pResourceEntry, sizeof( SMBSMP_RESOURCE ) );

		pResourceEntry->resid = static_cast< RESID >( pResourceEntry ); // for validation
		pResourceEntry->hResourceHandle = hResourceHandle;
		pResourceEntry->hkeyParameters = hkeyParameters;
		pResourceEntry->state = ClusterResourceOffline;

		//
		// Save the name of the resource.
		//
		pResourceEntry->pszResourceName = static_cast< LPWSTR >(
			LocalAlloc( LMEM_FIXED, (lstrlenW( pszResourceName ) + 1) * sizeof( WCHAR ) )
			);
		if ( pResourceEntry->pszResourceName == NULL )
		{
			nStatus = GetLastError();
			break;
		} // if: error allocating memory for the name.
		lstrcpyW( pResourceEntry->pszResourceName, pszResourceName );

		//
		// Open the cluster.
		//
		pResourceEntry->hCluster = OpenCluster( NULL );
		if ( pResourceEntry->hCluster == NULL )
		{
			nStatus = GetLastError();
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Open: Unable to open the cluster. Error: %1!u!.\n",
				nStatus
				);
			break;
		} // if: error opening the cluster

		//
		// Open the resource.
		//
		pResourceEntry->hResource = OpenClusterResource(
										pResourceEntry->hCluster,
										pszResourceName
										);
		if ( pResourceEntry->hResource == NULL )
		{
			nStatus = GetLastError();
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Open: Unable to open the resource. Error: %1!u!.\n",
				nStatus
				);
			break;
		} // if: error opening the resource

		//
		// Configure registry key checkpoints.
		//
		nStatus = ConfigureRegistryCheckpoints(
						pResourceEntry->hResource,
						hResourceHandle,
						g_pszRegKeysSmbSmp
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error configuring registry key checkpoints

		//
		// Configure crypto key checkpoints.
		//
		nStatus = ConfigureCryptoKeyCheckpoints(
						pResourceEntry->hResource,
						hResourceHandle,
						g_pszCryptoKeysSmbSmp
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error configuring crypto key checkpoints

		//
		// Configure domestic crypto key checkpoints.
		//
		nStatus = ConfigureDomesticCryptoKeyCheckpoints(
						pResourceEntry->hResource,
						hResourceHandle,
						g_pszDomesticCryptoKeysSmbSmp
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error configuring domestic crypto key checkpoints

		//
		// Startup for the resource.
		//
		// TODO: Add your resource startup code here.


		//
		// Get the computer name for use in IsAlive checking.
		//
		if ( ! GetComputerNameW( pResourceEntry->szComputerName, &cchComputerName ) )
		{
			nStatus = GetLastError();
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Open: Unable to get the computer name. Error: %1!u!.\n",
				nStatus
				);
			break;
		} // if:  error getting computer name

		resid = static_cast< RESID >( pResourceEntry );
	} while ( 0 );


	if ( resid == 0 )
	{
		if ( hkeyParameters != NULL )
		{
			ClusterRegCloseKey( hkeyParameters );
		} // if: registry key was opened
		if ( pResourceEntry != NULL )
		{
			LocalFree( pResourceEntry->pszResourceName );
			LocalFree( pResourceEntry );
		} // if: resource entry allocated
	}

	if ( nStatus != ERROR_SUCCESS )
	{
		SetLastError( nStatus );
	} // if: error occurred

	return resid;

} //*** SmbSmpOpen()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpClose
//
//	Description:
//		Close routine for SMB Sample resources.
//
//		Close the specified resource and deallocate all structures, etc.,
//		allocated in the Open call.  If the resource is not in the offline
//		state, then the resource should be taken offline (by calling
//		Terminate) before the close operation is performed.
//
//	Arguments:
//		resid		[IN] Supplies the resource ID  of the resource to close.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void WINAPI SmbSmpClose( IN RESID resid )
{
	PSMBSMP_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: Close request for a nonexistent resource id %p\n",
			resid
			);
		return;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Close resource sanity check failed! resid = %1!u!.\n",
			resid
			);
		return;
	} // if: invalid resource ID

#ifdef LOG_VERBOSE
	(g_pfnLogEvent)(
		pResourceEntry->hResourceHandle,
		LOG_INFORMATION,
		L"Close request.\n"
		);
#endif

	//
	// Close the Parameters key.
	//
	if ( pResourceEntry->hkeyParameters )
	{
		ClusterRegCloseKey( pResourceEntry->hkeyParameters );
	} // if: parameters key is open


	//
	// Deallocate the resource entry.
	//

	// ADDPARAM: Add new properties here.
	LocalFree( pResourceEntry->props.pszShareName );
	LocalFree( pResourceEntry->props.pszPath );
	LocalFree( pResourceEntry->props.pszRemark );

	LocalFree( pResourceEntry->propsActive.pszShareName );
	LocalFree( pResourceEntry->propsActive.pszPath );
	LocalFree( pResourceEntry->propsActive.pszRemark );

	LocalFree( pResourceEntry->pszResourceName );
	LocalFree( pResourceEntry );

} //*** SmbSmpClose()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpOnline
//
//	Description:
//		Online routine for SMB Sample resources.
//
//		Bring the specified resource online (available for use).  The resource
//		DLL should attempt to arbitrate for the resource if it is present on
//		a shared medium, like a shared SCSI bus.
//
//	Arguments:
//		resid [IN]
//			Supplies the resource ID of the resource to be brought online
//			(available for use).
//
//		phEventHandle [IN OUT]
//			Returns a signalable handle that is signaled when the resource DLL
//			detects a failure on the resource.  This argument is NULL on
//			input, and the resource DLL returns NULL if asynchronous
//			notification of failurs is not supported.  Otherwise this must be
//			the address of a handle that is signaled on resource failures.
//
//	Return Value:
//		ERROR_SUCCESS
//			The operation was successful, and the resource is now online.
//
//		ERROR_RESOURCE_NOT_FOUND
//			Resource ID is not valid.
//
//		ERROR_RESOURCE_NOT_AVAILABLE
//			If the resource was arbitrated with some other systems and one of
//			the other systems won the arbitration.
//
//		ERROR_IO_PENDING
//			The request is pending.  A thread has been activated to process
//			the online request.  The thread that is processing the online
//			request will periodically report status by calling the
//			SetResourceStatus callback method until the resource is placed
//			into the ClusterResourceOnline state (or the resource monitor
//			decides to timeout the online request and Terminate the resource.
//			This pending timeout value is settable and has a default value of
//			3 minutes.).
//
//		Win32 error code
//			The operation failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpOnline(
	IN		RESID		resid,
	IN OUT	PHANDLE 	phEventHandle
	)
{
	PSMBSMP_RESOURCE	pResourceEntry;
	DWORD				nStatus;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: Online request for a nonexistent resource id %p.\n",
			resid
			);
		return ERROR_RESOURCE_NOT_FOUND;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Online service sanity check failed! resid = %1!u!.\n",
			resid
			);
		return ERROR_RESOURCE_NOT_FOUND;
	} // if: invalid resource ID

#ifdef LOG_VERBOSE
	(g_pfnLogEvent)(
		pResourceEntry->hResourceHandle,
		LOG_INFORMATION,
		L"Online request.\n"
		);
#endif

	//
	// Start the Online thread to perform the online operation.
	//
	pResourceEntry->state = ClusterResourceOffline;
	ClusWorkerTerminate( &pResourceEntry->cwWorkerThread );
	nStatus = ClusWorkerCreate(
				&pResourceEntry->cwWorkerThread,
				reinterpret_cast< PWORKER_START_ROUTINE >( SmbSmpOnlineThread ),
				pResourceEntry
				);
	if ( nStatus != ERROR_SUCCESS )
	{
		pResourceEntry->state = ClusterResourceFailed;
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Online: Unable to start thread. Error: %1!u!.\n",
			nStatus
			);
	} // if: error creating the worker thread
	else
	{
		nStatus = ERROR_IO_PENDING;
	} // if: worker thread created successfully

	return nStatus;

} //*** SmbSmpOnline()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpOnlineThread
//
//	Description:
//		Worker function which brings a resource online.
//		This function is executed in a separate thread.
//
//	Arguments:
//		pWorker [IN]
//			Supplies the worker thread structure.
//
//		pResourceEntry [IN]
//			A pointer to the SMBSMP_RESOURCE block for this resource.
//
//	Return Value:
//		ERROR_SUCCESS
//			The operation completed successfully.
//
//		Win32 error code
//			The operation failed.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpOnlineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PSMBSMP_RESOURCE	pResourceEntry
	)
{
	RESOURCE_STATUS 	resourceStatus;
	DWORD				nStatus = ERROR_SUCCESS;
	LPWSTR				pszNameOfPropInError;
	SHARE_INFO_2		shareInfo;

	ResUtilInitializeResourceStatus( &resourceStatus );

	resourceStatus.ResourceState = ClusterResourceFailed;
	resourceStatus.WaitHint = 0;
	resourceStatus.CheckPoint = 1;

	do											// Loop to avoid goto's.
	{
		//
		// Read properties.
		//
		nStatus = ResUtilGetPropertiesToParameterBlock(
					pResourceEntry->hkeyParameters,
					SmbSmpResourcePrivateProperties,
					reinterpret_cast< LPBYTE >( &pResourceEntry->propsActive ),
					TRUE, // CheckForRequiredProperties
					&pszNameOfPropInError
					);
		if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"OnlineThread: Unable to read the '%1' property. Error: %2!u!.\n",
				(pszNameOfPropInError == NULL ? L"" : pszNameOfPropInError),
				nStatus
				);
			break;
		} // if: error getting properties

		//
		// Start the LanmanServer service
		// The call to ClusWorkerCheckTerminate checks to see if this resource
		// has been terminated, in which case it should not start the service.
		//
		if ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			nStatus = ResUtilStartResourceService( SMBSMP_SVCNAME, NULL );
			if ( nStatus == ERROR_SERVICE_ALREADY_RUNNING )
			{
				nStatus = ERROR_SUCCESS;
			} // if: service was already started
			else if ( nStatus != ERROR_SUCCESS )
			{
				break;
			} // else if: error starting the service
		} // if: resource has not been terminated
		else
		{
			break;
		} // else: resource has been terminated

		//
		// Bring the resource online.
		// The call to ClusWorkerCheckTerminate checks to see if this resource
		// has been terminated, in which case it should not be brought online.
		//
		if ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			// TODO: Add code to bring your resource online.
			ZeroMemory( &shareInfo, sizeof( shareInfo ) );
			shareInfo.shi2_netname =	pResourceEntry->propsActive.pszShareName;
			shareInfo.shi2_type =		STYPE_DISKTREE;
			shareInfo.shi2_remark =		pResourceEntry->propsActive.pszRemark;
			shareInfo.shi2_max_uses =	static_cast< DWORD >( -1 );
			shareInfo.shi2_path =		pResourceEntry->propsActive.pszPath;

			nStatus = NetShareAdd( NULL, 2, reinterpret_cast< PBYTE >( &shareInfo ), NULL );
			if ( nStatus == ERROR_SUCCESS )
			{
				resourceStatus.ResourceState = ClusterResourceOnline;
			} // if: resource brought online
			else
			{
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_ERROR,
					L"OnlineThread: Error%1!u! creating share '%2!ws!' for path '%3!ws!'.\n",
					nStatus,
					pResourceEntry->propsActive.pszShareName,
					pResourceEntry->propsActive.pszPath
					);
				break;
			} // else:  error creating share
		} // if: resource has not been terminated

	} while ( 0 );

	if ( nStatus != ERROR_SUCCESS )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"OnlineThread: Error %1!u! bringing resource online.\n",
			nStatus
			);
	} // if: error occurred

	g_pfnSetResourceStatus( pResourceEntry->hResourceHandle, &resourceStatus );
	pResourceEntry->state = resourceStatus.ResourceState;

	return nStatus;

} //*** SmbSmpOnlineThread()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpOffline
//
//	Description:
//		Offline routine for SMB Sample resources.
//
//		Take the specified resource offline (unavailable for use).  Wait
//		for any cleanup operations to complete before returning.
//
//	Arguments:
//		resid [IN]
//			Supplies the resource ID of the resource to be shutdown
//			gracefully.
//
//	Return Value:
//		ERROR_SUCCESS
//			The operation was successful, and the resource is now offline.
//
//		ERROR_RESOURCE_NOT_FOUND
//			Resource ID is not valid.
//
//		ERROR_RESOURCE_NOT_AVAILABLE
//			If the resource was arbitrated with some other systems and one of
//			the other systems won the arbitration.
//
//		ERROR_IO_PENDING
//			The request is still pending.  A thread has been activated to
//			process the offline request.  The thread that is processing the
//			offline request will periodically report status by calling the
//			SetResourceStatus callback method until the resource is placed
//			into the ClusterResourceOffline state (or the resource monitor
//			decides  to timeout the offline request and Terminate the
//			resource).
//
//		Win32 error code
//			The operation failed.  This will cause the Resource Monitor to
//			log an event and call the Terminate routine.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpOffline( IN RESID resid )
{
	PSMBSMP_RESOURCE	pResourceEntry;
	DWORD				nStatus;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: Offline request for a nonexistent resource id %p\n",
			resid
			);
		return ERROR_RESOURCE_NOT_FOUND;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Offline resource sanity check failed! resid = %1!u!.\n",
			resid
			);
		return ERROR_RESOURCE_NOT_FOUND;
	} // if: invalid resource ID

#ifdef LOG_VERBOSE
	(g_pfnLogEvent)(
		pResourceEntry->hResourceHandle,
		LOG_INFORMATION,
		L"Offline request.\n"
		);
#endif

	//
	// Start the Offline thread to perform the offline operation.
	//
	pResourceEntry->state = ClusterResourceOfflinePending;
	ClusWorkerTerminate( &pResourceEntry->cwWorkerThread );
	nStatus = ClusWorkerCreate(
				&pResourceEntry->cwWorkerThread,
				reinterpret_cast< PWORKER_START_ROUTINE >( SmbSmpOfflineThread ),
				pResourceEntry
				);
	if ( nStatus != ERROR_SUCCESS )
	{
		pResourceEntry->state = ClusterResourceFailed;
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Offline: Unable to start thread. Error: %1!u!.\n",
			nStatus
			);
	} // if: error creating the worker thread
	else
	{
		nStatus = ERROR_IO_PENDING;
	} // if: worker thread created successfully

	return nStatus;

} //*** SmbSmpOffline()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpOfflineThread
//
//	Description:
//		Worker function which takes a resource offline.
//		This function is executed in a separate thread.
//
//	Arguments:
//		pWorker [IN]
//			Supplies the worker thread structure.
//
//		pResourceEntry [IN]
//			A pointer to the SMBSMP_RESOURCE block for this resource.
//
//	Return Value:
//		ERROR_SUCCESS
//			The operation completed successfully.
//
//		Win32 error code
//			The operation failed.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpOfflineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PSMBSMP_RESOURCE	pResourceEntry
	)
{
	RESOURCE_STATUS 	resourceStatus;
	DWORD				nStatus = ERROR_SUCCESS;

	ResUtilInitializeResourceStatus( &resourceStatus );

	resourceStatus.ResourceState = ClusterResourceFailed;
	resourceStatus.WaitHint = 0;
	resourceStatus.CheckPoint = 1;

	do											// Loop to avoid goto's.
	{
		//
		// Take the resource offline.
		// The call to ClusWorkerCheckTerminate checks to see if this
		// resource has been terminated or not.
		//
		if ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			// TODO: Add code to take your resource offline.
		nStatus = NetShareDel( NULL, pResourceEntry->propsActive.pszShareName, 0 );
			if ( nStatus == ERROR_SUCCESS )
			{
				resourceStatus.ResourceState = ClusterResourceOffline;
			} // if: resource taken offline successfully
			else
			{
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_ERROR,
					L"OfflineThread: Error %1!u! deleting share '%2!ws!'.\n",
					nStatus,
					pResourceEntry->propsActive.pszShareName
					);
			} // else: error taking the resource offline
		} // if: resource not terminated
	} while ( 0 );

	g_pfnSetResourceStatus( pResourceEntry->hResourceHandle, &resourceStatus );
	pResourceEntry->state = resourceStatus.ResourceState;

	return nStatus;

} //*** SmbSmpOfflineThread()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpTerminate
//
//	Description:
//		Terminate routine for SMB Sample resources.
//
//		Take the specified resource offline immediately (the resource is
//		unavailable for use).
//
//	Arguments:
//		resid [IN]
//			Supplies the resource ID of the resource to be shutdown
//			ungracefully.
//
//	Return Value:
//		None.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
void WINAPI SmbSmpTerminate( IN RESID resid )
{
	PSMBSMP_RESOURCE	pResourceEntry;
	DWORD				nStatus;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: Terminate request for a nonexistent resource id %p\n",
			resid
			);
		return;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Terminate resource sanity check failed! resid = %1!u!.\n",
			resid
			);
		return;
	} // if: invalid resource ID

#ifdef LOG_VERBOSE
	(g_pfnLogEvent)(
		pResourceEntry->hResourceHandle,
		LOG_INFORMATION,
		L"Terminate request.\n"
		);
#endif

	//
	// Kill off any pending threads.
	//
	ClusWorkerTerminate( &pResourceEntry->cwWorkerThread );

	//
	// Terminate the resource.
	//
	// TODO: Add code to terminate the resource.

	nStatus = NetShareDel( NULL, pResourceEntry->propsActive.pszShareName, 0 );
	if ( nStatus != ERROR_SUCCESS )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"Terminate: Error %1!u! removing share '%2!ws!'.\n",
			nStatus,
			pResourceEntry->propsActive.pszShareName
			);
	} // if:  error taking the resource offline

	pResourceEntry->state = ClusterResourceOffline;

} //*** SmbSmpTerminate()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpLooksAlive
//
//	Description:
//		LooksAlive routine for SMB Sample resources.
//
//		Perform a quick check to determine if the specified resource is
//		probably online (available for use).  This call should not block for
//		more than 300 ms, preferably less than 50 ms.
//
//	Arguments:
//		resid	[IN] Supplies the resource ID for the resource to be polled.
//
//	Return Value:
//		TRUE
//			The specified resource is probably online and available for use.
//
//		FALSE
//			The specified resource is not functioning normally.  The IsAlive
//			function will be called to perform a more thorough check.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL WINAPI SmbSmpLooksAlive( IN RESID resid )
{
	PSMBSMP_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: LooksAlive request for a nonexistent resource id %p\n",
			resid
			);
		return FALSE;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"LooksAlive sanity check failed! resid = %1!u!.\n",
			resid
			);
		return FALSE;
	} // if: invalid resource ID

#ifdef LOG_VERBOSE
	(g_pfnLogEvent)(
		pResourceEntry->hResourceHandle,
		LOG_INFORMATION,
		L"LooksAlive request.\n"
		);
#endif

	// TODO: LooksAlive code

	// NOTE: LooksAlive should be a quick check to see if the resource is
	// available or not, whereas IsAlive should be a thorough check.  If
	// there are no differences between a quick check and a thorough check,
	// IsAlive can be called for LooksAlive, as it is below.  However, if there
	// are differences, replace the call to IsAlive below with your quick
	// check code.

	//
	// Check to see if the resource is alive.
	//
	return SmbSmpCheckIsAlive( pResourceEntry, FALSE /* bFullCheck */ );

} //*** SmbSmpLooksAlive()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpIsAlive
//
//	Description:
//		IsAlive routine for SMB Sample resources.
//
//		Perform a thorough check to determine if the specified resource is
//		online (available for use).  This call should not block for more
//		more than 300 ms, preferably less than 50 ms.  If it must block for
//		longer than this, create a separate thread dedicated to polling for
//		this information and have this routine return the status of the last
//		poll performed.
//
//	Arguments:
//		resid	[IN] Supplies the resource ID for the resource to be polled.
//
//	Return Value:
//		TRUE
//			The specified resource is online and functioning normally.
//
//		FALSE
//			The specified resource is not functioning normally.  The resource
//			will be terminated and then Online will be called.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL WINAPI SmbSmpIsAlive( IN RESID resid )
{
	PSMBSMP_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: IsAlive request for a nonexistent resource id %p\n",
			resid
			);
		return FALSE;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"IsAlive sanity check failed! resid = %1!u!.\n",
			resid
			);
		return FALSE;
	} // if: invalid resource ID

#ifdef LOG_VERBOSE
	(g_pfnLogEvent)(
		pResourceEntry->hResourceHandle,
		LOG_INFORMATION,
		L"IsAlive request.\n"
		);
#endif

	//
	// Check to see if the resource is alive.
	//
	return SmbSmpCheckIsAlive( pResourceEntry, TRUE /* bFullCheck */ );

} //** SmbSmpIsAlive()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpCheckIsAlive
//
//	Description:
//		Check to see if the resource is alive for SMB Sample
//		resources.
//
//	Arguments:
//		pResourceEntry	[IN]
//			Supplies the resource entry for the resource to polled.
//
//		bFullCheck [IN]
//			TRUE = Perform a full check.
//			FALSE = Perform a cursory check.
//
//	Return Value:
//		TRUE	The specified resource is online and functioning normally.
//		FALSE	The specified resource is not functioning normally.
//
//	Notes:
//		When using properties in this routine it is recommended that you
//		use the properties in propsActive of the CLIPSRV_RESOURCE struct
//		instead of the properties in props.  The primary reason you should
//		use propsActive is that the properties in props could be changed by
//		the SetPrivateResProperties() routine.  Using propsActive allows
//		the online state of the resource to be steady while still allowing
//		an administrator to change the stored value of the properties.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL SmbSmpCheckIsAlive(
	IN PSMBSMP_RESOURCE	pResourceEntry,
	IN BOOL				bFullCheck
	)
{
	BOOL	bIsAlive = TRUE;
	DWORD			nStatus;
	SHARE_INFO_2	shareInfo;

	do											// Loop to avoid goto's.
	{
		//
		// Check to see if the resource is alive.
		//
		// TODO: Add code to determine if your resource is alive.
		nStatus = NetShareGetInfo(
						NULL,
						pResourceEntry->propsActive.pszShareName,
						2, // return a SHARE_INFO_2 structure
						reinterpret_cast< LPBYTE * >( &shareInfo )
						);
		if ( nStatus == NERR_NetNameNotFound )
		{
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"CheckIsAlive: Error, share '%1!ws!' went away.\n",
				pResourceEntry->propsActive.pszShareName
				);
		} // if:  share name not found
		else if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"CheckIsAlive: Error %1!u! checking for share '%2!ws!'.\n",
				nStatus,
				pResourceEntry->propsActive.pszShareName
				);
		} // else if:  error getting share info
		else
		{
			//
			// Cleanup after call to NetShareGetInfo().
			//
			NetApiBufferFree( &shareInfo );

			if ( bFullCheck )
			{
				HANDLE			hFile;
				WIN32_FIND_DATA	fileData;
				WCHAR			szShareName[ MAX_PATH ];

				//
				// See if we can find a file on the share.  This is the only way
				// we can detect the share becoming unavailable if the directory
				// is deleted.
				//
				wsprintfW(
					szShareName,
					L"\\\\%ws\\%ws\\*.*\0",
					pResourceEntry->szComputerName,
					pResourceEntry->propsActive.pszShareName
					);
				hFile = FindFirstFileW( szShareName, &fileData );

				//
				// If we fail on the first attempt, try again.  There seems to be
				// a bug in the RDR where the first attempt to read a share after
				// it has been deleted and reinstated.  The bug is that the RDR
				// returns failure on the first operation following the
				// reinstatement of the share.
				//

				if ( hFile == INVALID_HANDLE_VALUE )
				{
					hFile = FindFirstFileW( szShareName, &fileData );
				} // if:  error finding file

				//
				// If we succeeded in finding a file, or there were no files in
				// the path, then return success, otherwise we had a failure.
				//
				nStatus = GetLastError();
				if (	(hFile == INVALID_HANDLE_VALUE)
					&&	(nStatus != ERROR_FILE_NOT_FOUND)
					&& (nStatus != ERROR_ACCESS_DENIED)
					)
				{
					(g_pfnLogEvent)(
						pResourceEntry->hResourceHandle,
						LOG_ERROR,
						L"CheckIsAlive: Share has gone offline!\n"
						);
				} // if:  error finding the file
				else
				{
					FindClose( hFile );
					nStatus = ERROR_SUCCESS;				// there are other non-failure status codes possible...  Reset to success...
				} // else:  found file
			} // if:  performing a full check
		} // else:  share is defined
	} while ( 0 );

	if ( nStatus != ERROR_SUCCESS )
	{
		bIsAlive = FALSE;
		SetLastError( nStatus );
	} // if:  error occurred

	return bIsAlive;

} //*** SmbSmpCheckIsAlive()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpResourceControl
//
//	Description:
//		ResourceControl routine for SMB Sample resources.
//
//		Perform the control request specified by nControlCode on the specified
//		resource.
//
//	Arguments:
//		resid [IN]
//			Supplies the resource ID for the specific resource.
//
//		nControlCode [IN]
//			Supplies the control code that defines the action to be performed.
//
//		pInBuffer [IN]
//			Supplies a pointer to a buffer containing input data.
//
//		cbInBufferSize [IN]
//			Supplies the size, in bytes, of the data pointed to by pInBuffer.
//
//		pOutBuffer [OUT]
//			Supplies a pointer to the output buffer to be filled in.
//
//		cbOutBufferSize [IN]
//			Supplies the size, in bytes, of the available space pointed to by
//			pOutBuffer.
//
//		pcbBytesReturned [OUT]
//			Returns the number of bytes of pOutBuffer actually filled in by
//			the resource.  If pOutBuffer is too small, pcbBytesReturned
//			contains the total number of bytes for the operation to succeed.
//
//	Return Value:
//		ERROR_SUCCESS
//			The function completed successfully.
//
//		ERROR_RESOURCE_NOT_FOUND
//			Resource ID is not valid.
//
//		ERROR_MORE_DATA
//			The output buffer is too small to return the data.
//			pcbBytesReturned contains the required size.
//
//		ERROR_INVALID_FUNCTION
//			The requested control code is not supported.  In some cases,
//			this allows the cluster software to perform the work.
//
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpResourceControl(
	IN	RESID	resid,
	IN	DWORD	nControlCode,
	IN	PVOID	pInBuffer,
	IN	DWORD	cbInBufferSize,
	OUT	PVOID	pOutBuffer,
	IN	DWORD	cbOutBufferSize,
	OUT	LPDWORD	pcbBytesReturned
	)
{
	DWORD				nStatus;
	PSMBSMP_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PSMBSMP_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"SmbSmp: ResourceControl request for a nonexistent resource id %p\n",
			resid
			);
		return ERROR_RESOURCE_NOT_FOUND;
	} // if: NULL resource ID

	if ( pResourceEntry->resid != resid )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"ResourceControl sanity check failed! resid = %1!u!.\n",
			resid
			);
		return ERROR_RESOURCE_NOT_FOUND;
	} // if: invalid resource ID

	switch ( nControlCode )
	{
		case CLUSCTL_RESOURCE_UNKNOWN:
			*pcbBytesReturned = 0;
			nStatus = ERROR_SUCCESS;
			break;

		case CLUSCTL_RESOURCE_ENUM_PRIVATE_PROPERTIES:
		{
			DWORD cbRequired = 0;
			nStatus = ResUtilEnumProperties(
							SmbSmpResourcePrivateProperties,
							static_cast< LPWSTR >( pOutBuffer ),
							cbOutBufferSize,
							pcbBytesReturned,
							&cbRequired
							);
			if ( nStatus == ERROR_MORE_DATA )
			{
				*pcbBytesReturned = cbRequired;
			} // if: output buffer is too small
			break;
		}

		case CLUSCTL_RESOURCE_GET_PRIVATE_PROPERTIES:
			nStatus = SmbSmpGetPrivateResProperties(
							pResourceEntry,
							pOutBuffer,
							cbOutBufferSize,
							pcbBytesReturned
							);
			break;

		case CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES:
			nStatus = SmbSmpValidatePrivateResProperties(
							pResourceEntry,
							pInBuffer,
							cbInBufferSize,
							NULL
							);
			break;

		case CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES:
			nStatus = SmbSmpSetPrivateResProperties(
							pResourceEntry,
							pInBuffer,
							cbInBufferSize
							);
			break;

		case CLUSCTL_RESOURCE_SET_NAME:
			nStatus = SmbSmpSetNameHandler(
							pResourceEntry,
							static_cast< LPWSTR >( pInBuffer )
							);
			break;

		case CLUSCTL_RESOURCE_GET_REQUIRED_DEPENDENCIES:
		case CLUSCTL_RESOURCE_GET_CHARACTERISTICS:
		case CLUSCTL_RESOURCE_GET_CLASS_INFO:
		case CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO:
		case CLUSCTL_RESOURCE_STORAGE_IS_PATH_VALID:
		case CLUSCTL_RESOURCE_DELETE:
		case CLUSCTL_RESOURCE_INSTALL_NODE:
		case CLUSCTL_RESOURCE_EVICT_NODE:
		case CLUSCTL_RESOURCE_ADD_DEPENDENCY:
		case CLUSCTL_RESOURCE_REMOVE_DEPENDENCY:
		case CLUSCTL_RESOURCE_ADD_OWNER:
		case CLUSCTL_RESOURCE_REMOVE_OWNER:
		case CLUSCTL_RESOURCE_CLUSTER_NAME_CHANGED:
		case CLUSCTL_RESOURCE_CLUSTER_VERSION_CHANGED:
		default:
			nStatus = ERROR_INVALID_FUNCTION;
			break;
	} // switch: nControlCode

	return nStatus;

} //*** SmbSmpResourceControl()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpResourceTypeControl
//
//	Description:
//		ResourceTypeControl routine for SMB Sample resources.
//
//		Perform the control request specified by nControlCode.
//
//	Arguments:
//		pszResourceTypeName [IN]
//			Supplies the name of the resource type.
//
//		nControlCode [IN]
//			Supplies the control code that defines the action to be performed.
//
//		pInBuffer [IN]
//			Supplies a pointer to a buffer containing input data.
//
//		cbInBufferSize [IN]
//			Supplies the size, in bytes, of the data pointed to by pInBuffer.
//
//		pOutBuffer [OUT]
//			Supplies a pointer to the output buffer to be filled in.
//
//		cbOutBufferSize [IN]
//			Supplies the size, in bytes, of the available space pointed to by
//			pOutBuffer.
//
//		pcbBytesReturned [OUT]
//			Returns the number of bytes of pOutBuffer actually filled in by
//			the resource.  If pOutBuffer is too small, pcbBytesReturned
//			contains the total number of bytes for the operation to succeed.
//
//	Return Value:
//		ERROR_SUCCESS
//			The function completed successfully.
//
//		ERROR_MORE_DATA
//			The output buffer is too small to return the data.
//			pcbBytesReturned contains the required size.
//
//		ERROR_INVALID_FUNCTION
//			The requested control code is not supported.  In some cases,
//			this allows the cluster software to perform the work.
//
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI SmbSmpResourceTypeControl(
	IN	LPCWSTR	pszResourceTypeName,
	IN	DWORD	nControlCode,
	IN	PVOID	pInBuffer,
	IN	DWORD	cbInBufferSize,
	OUT	PVOID	pOutBuffer,
	IN	DWORD	cbOutBufferSize,
	OUT	LPDWORD	pcbBytesReturned
	)
{
	DWORD	nStatus;

	switch ( nControlCode )
	{

		case CLUSCTL_RESOURCE_TYPE_UNKNOWN:
			*pcbBytesReturned = 0;
			nStatus = ERROR_SUCCESS;
			break;

		case CLUSCTL_RESOURCE_TYPE_ENUM_PRIVATE_PROPERTIES:
		{
			DWORD cbRequired = 0;
			nStatus = ResUtilEnumProperties(
							SmbSmpResourcePrivateProperties,
							static_cast< LPWSTR >( pOutBuffer ),
							cbOutBufferSize,
							pcbBytesReturned,
							&cbRequired
							);
			if ( nStatus == ERROR_MORE_DATA )
			{
				*pcbBytesReturned = cbRequired;
			} // if: output buffer is too small
			break;
		}

		case CLUSCTL_RESOURCE_TYPE_GET_REQUIRED_DEPENDENCIES:
		case CLUSCTL_RESOURCE_TYPE_GET_CHARACTERISTICS:
		case CLUSCTL_RESOURCE_TYPE_GET_CLASS_INFO:
		case CLUSCTL_RESOURCE_TYPE_STORAGE_GET_AVAILABLE_DISKS:
		case CLUSCTL_RESOURCE_TYPE_INSTALL_NODE:
		case CLUSCTL_RESOURCE_TYPE_EVICT_NODE:
		default:
			nStatus = ERROR_INVALID_FUNCTION;
			break;
	} // switch: nControlCode

	return nStatus;

} //*** SmbSmpResourceTypeControl()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpGetPrivateResProperties
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_GET_PRIVATE_PROPERTIES control
//		function for resources of type SMB Sample.
//
//	Arguments:
//		pResourceEntry [IN OUT]
//			Supplies the resource entry on which to operate.
//
//		pOutBuffer [OUT]
//			Supplies a pointer to the output buffer to be filled in.
//
//		cbOutBufferSize [IN]
//			Supplies the size, in bytes, of the available space pointed to by
//			pOutBuffer.
//
//		pcbBytesReturned [OUT]
//			Returns the number of bytes of pOutBuffer actually filled in by
//			the resource.  If pOutBuffer is too small, pcbBytesReturned
//			contains the total number of bytes for the operation to succeed.
//
//	Return Value:
//		ERROR_SUCCESS
//			The function completed successfully.
//
//		ERROR_MORE_DATA
//			The output buffer is too small to return the data.
//			pcbBytesReturned contains the required size.
//
//		ERROR_INVALID_PARAMETER
//			The data is formatted incorrectly.
//
//		ERROR_NOT_ENOUGH_MEMORY
//			An error occurred allocating memory.
//
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD SmbSmpGetPrivateResProperties(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	OUT		PVOID				pOutBuffer,
	IN		DWORD				cbOutBufferSize,
	OUT		LPDWORD				pcbBytesReturned
	)
{
	DWORD	nStatus;
	DWORD	cbRequired = 0;

	nStatus = ResUtilGetAllProperties(
					pResourceEntry->hkeyParameters,
					SmbSmpResourcePrivateProperties,
					pOutBuffer,
					cbOutBufferSize,
					pcbBytesReturned,
					&cbRequired
					);
	if ( nStatus == ERROR_MORE_DATA )
	{
		*pcbBytesReturned = cbRequired;
	} // if: output buffer is too small

	return nStatus;

} //*** SmbSmpGetPrivateResProperties()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpValidatePrivateResProperties
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES control
//		function for resources of type SMB Sample.
//
//	Arguments:
//		pResourceEntry [IN OUT]
//			Supplies the resource entry on which to operate.
//
//		pInBuffer [IN]
//			Supplies a pointer to a buffer containing input data.
//
//		cbOutBufferSize [IN]
//			Supplies the size, in bytes, of the data pointed to by pInBuffer.
//
//		pProps [OUT]
//			Supplies the parameter block to fill in (optional).
//
//	Return Value:
//		ERROR_SUCCESS
//			The function completed successfully.
//
//		ERROR_INVALID_PARAMETER
//			The data is formatted incorrectly.
//
//		ERROR_NOT_ENOUGH_MEMORY
//			An error occurred allocating memory.
//
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD SmbSmpValidatePrivateResProperties(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	IN		PVOID				pInBuffer,
	IN		DWORD				cbInBufferSize,
	OUT		PSMBSMP_PROPS	pProps
	)
{
	DWORD		nStatus = ERROR_SUCCESS;
	SMBSMP_PROPS		propsCurrent;
	SMBSMP_PROPS		propsNew;
	PSMBSMP_PROPS	pLocalProps = NULL;
	LPWSTR		pszNameOfPropInError;
	BOOL		bRetrievedProps = FALSE;

	do											// Loop to avoid goto's.
	{
		//
		// Check if there is input data.
		//
		if (	(pInBuffer == NULL)
			||	(cbInBufferSize < sizeof( DWORD )) )
		{
			nStatus = ERROR_INVALID_DATA;
			break;
		} // if: no input buffer or input buffer not big enough to contain property list

		//
		// Retrieve the current set of private properties from the
		// cluster database.
		//
		ZeroMemory( &propsCurrent, sizeof( propsCurrent ) );

		nStatus = ResUtilGetPropertiesToParameterBlock(
					 pResourceEntry->hkeyParameters,
					 SmbSmpResourcePrivateProperties,
					 reinterpret_cast< LPBYTE >( &propsCurrent ),
					 FALSE, /*CheckForRequiredProperties*/
					 &pszNameOfPropInError
					 );

		if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"Unable to read the '%1' property. Error: %2!u!.\n",
				(pszNameOfPropInError == NULL ? L"" : pszNameOfPropInError),
				nStatus
				);
			break;
		} // if: error getting properties
		bRetrievedProps = TRUE;

		//
		// Duplicate the resource parameter block.
		//
		if ( pProps == NULL )
		{
			pLocalProps = &propsNew;
		} // if: no parameter block passed in
		else
		{
			pLocalProps = pProps;
		} // else: parameter block passed in
		ZeroMemory( pLocalProps, sizeof( SMBSMP_PROPS ) );
		nStatus = ResUtilDupParameterBlock(
						reinterpret_cast< LPBYTE >( pLocalProps ),
						reinterpret_cast< LPBYTE >( &propsCurrent ),
						SmbSmpResourcePrivateProperties
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error duplicating the parameter block

		//
		// Parse and validate the properties.
		//
		nStatus = ResUtilVerifyPropertyTable(
						SmbSmpResourcePrivateProperties,
						NULL,
						TRUE, // AllowUnknownProperties
						pInBuffer,
						cbInBufferSize,
						reinterpret_cast< LPBYTE >( pLocalProps )
						);
		if ( nStatus == ERROR_SUCCESS )
		{
			//
			// Validate the property values.
			//
			// TODO: Code to validate interactions between properties goes here.
		} // if: property list validated successfully
	} while ( 0 );

	//
	// Cleanup our parameter block.
	//
	if (	(pLocalProps == &propsNew)
		||	(	(nStatus != ERROR_SUCCESS)
			&&	(pLocalProps != NULL)
			)
		)
	{
		ResUtilFreeParameterBlock(
			reinterpret_cast< LPBYTE >( pLocalProps ),
			reinterpret_cast< LPBYTE >( &propsCurrent ),
			SmbSmpResourcePrivateProperties
			);
	} // if: we duplicated the parameter block

	if ( bRetrievedProps )
	{
		ResUtilFreeParameterBlock(
			reinterpret_cast< LPBYTE >( &propsCurrent ),
			NULL,
			SmbSmpResourcePrivateProperties
			);
	} // if: properties were retrieved

	return nStatus;

} // SmbSmpValidatePrivateResProperties


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpSetPrivateResProperties
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES control
//		function for resources of type SMB Sample.
//
//	Arguments:
//		pResourceEntry [IN OUT]
//			Supplies the resource entry on which to operate.
//
//		pInBuffer [IN]
//			Supplies a pointer to a buffer containing input data.
//
//		cbOutBufferSize [IN]
//			Supplies the size, in bytes, of the data pointed to by pInBuffer.
//
//	Return Value:
//		ERROR_SUCCESS
//			The function completed successfully.
//
//		ERROR_INVALID_PARAMETER
//			The data is formatted incorrectly.
//
//		ERROR_NOT_ENOUGH_MEMORY
//			An error occurred allocating memory.
//
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD SmbSmpSetPrivateResProperties(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	IN		PVOID				pInBuffer,
	IN		DWORD				cbInBufferSize
	)
{
	DWORD			nStatus = ERROR_SUCCESS;
	SMBSMP_PROPS	props;
	BOOL			bDynamicChangeAllowed;

	//
	// Parse the properties so they can be validated together.
	// This routine does individual property validation.
	//
	nStatus = SmbSmpValidatePrivateResProperties( pResourceEntry, pInBuffer, cbInBufferSize, &props );
	if ( nStatus == ERROR_SUCCESS )
	{
		//
		// If the name changed, we can't change the share while the
		// resource is online.
		//
		if (	(pResourceEntry->props.pszShareName != NULL)
			&&	(lstrcmpW( props.pszShareName, pResourceEntry->props.pszShareName ) != 0)
			)
		{
			bDynamicChangeAllowed = FALSE;
		} // if:  share name changed
		else
		{
			if (	(pResourceEntry->props.pszPath != NULL)
				&&	(lstrcmpW( props.pszPath, pResourceEntry->props.pszPath ) != 0)
				)
			{
				bDynamicChangeAllowed = FALSE;
			} // if:  path changed
			else
			{
				bDynamicChangeAllowed = TRUE;
			} // else:  path didn't change
		} // else:  share name didn't change

		//
		// Save the property values.
		//
		nStatus = ResUtilSetPropertyParameterBlock(
						pResourceEntry->hkeyParameters,
						SmbSmpResourcePrivateProperties,
						NULL,
						reinterpret_cast< LPBYTE >( &props ),
						pInBuffer,
						cbInBufferSize,
						reinterpret_cast< LPBYTE >( &pResourceEntry->props )
						);

		ResUtilFreeParameterBlock(
			reinterpret_cast< LPBYTE >( &props ),
			reinterpret_cast< LPBYTE >( &pResourceEntry->props ),
			SmbSmpResourcePrivateProperties
			);

		//
		// If the resource is online, return a non-success status.
		//
		// TODO: Modify the code below if your resource can handle
		// changes to properties while it is still online.
		if ( nStatus == ERROR_SUCCESS )
		{
			if (	(pResourceEntry->state == ClusterResourceOnline)
				&&	bDynamicChangeAllowed
				)
			{
				PSHARE_INFO_2	psiOld;
				SHARE_INFO_2	siNew;
				DWORD			nInvalidParam;

				nStatus = NetShareGetInfo(
								NULL,	// pszServer
								pResourceEntry->props.pszShareName,
								2,		// level
								reinterpret_cast< LPBYTE * >( &psiOld )
								);
				if ( nStatus == ERROR_SUCCESS )
				{
					//
					// Set new share info.
					//
					CopyMemory( &siNew, psiOld, sizeof( siNew ) );
					siNew.shi2_netname =	pResourceEntry->props.pszShareName;
					siNew.shi2_remark =		pResourceEntry->props.pszRemark;
					siNew.shi2_path =		pResourceEntry->props.pszPath;

					nStatus = NetShareSetInfo(
									NULL,	// pszServer
									pResourceEntry->props.pszShareName,
									2,		// level
									reinterpret_cast< LPBYTE >( &siNew ),
									&nInvalidParam
									);
					if ( nStatus != ERROR_SUCCESS )
					{
						(g_pfnLogEvent)(
							pResourceEntry->hResourceHandle,
							LOG_ERROR,
							L"SetPrivateProps: Error setting info on share '%1!ws!. Error %2!u!, property # %3!d!.\n",
							pResourceEntry->props.pszShareName,
							nStatus,
							nInvalidParam
							);
						nStatus = ERROR_RESOURCE_PROPERTIES_STORED;
					} // if:  error setting new share info

					NetApiBufferFree( psiOld );

				} // if:  share info retrieved successfully
				else
				{
					nStatus = ERROR_RESOURCE_PROPERTIES_STORED;
				} // else:  error retrieving share info
			} // if: resource is currently online
			else if (	(pResourceEntry->state == ClusterResourceOnline)
					||	(pResourceEntry->state == ClusterResourceOnlinePending)
					)
			{
				nStatus = ERROR_RESOURCE_PROPERTIES_STORED;
			} // else if: resource is currently in online pending
			else
			{
				nStatus = ERROR_SUCCESS;
			} // else: resource is in some other state
		} // if: properties set successfully
	} // if: no error validating properties

	return nStatus;

} //*** SmbSmpSetPrivateResProperties()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	SmbSmpSetNameHandler
//
//	Description:
//		Handle the CLUSCTL_RESOURCE_SET_NAME control code by saving the new
//		name of the resource.
//
//	Arguments:
//		pResourceEntry [IN OUT]
//			Supplies the resource entry on which to operate.
//
//		pszName [IN]
//			The new name of the resource.
//
//	Return Value:
//		ERROR_SUCCESS
//			The function completed successfully.
//
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD SmbSmpSetNameHandler(
	IN OUT	PSMBSMP_RESOURCE	pResourceEntry,
	IN		LPWSTR				pszName
	)
{
	DWORD	nStatus = ERROR_SUCCESS;

	do											// Loop to avoid goto's.
	{
		//
		// Save the name of the resource.
		//
		LocalFree( pResourceEntry->pszResourceName );
		pResourceEntry->pszResourceName = static_cast< LPWSTR >(
			LocalAlloc( LMEM_FIXED, (lstrlenW( pszName ) + 1) * sizeof( WCHAR ) )
			);
		if ( pResourceEntry->pszResourceName == NULL )
		{
			nStatus = GetLastError();
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"Failed to allocate memory for the new resource name '%1'. Error %2!u!.\n",
				pszName,
				nStatus
				);
			break;
		} // if: error allocating memory for the name.
		lstrcpyW( pResourceEntry->pszResourceName, pszName );

	} while ( 0 );

	return nStatus;

} //*** SmbSmpSetNameHandler()


/////////////////////////////////////////////////////////////////////////////
//
// Define Function Table
//
/////////////////////////////////////////////////////////////////////////////

CLRES_V1_FUNCTION_TABLE(
	g_SmbSmpFunctionTable,		// Name
	CLRES_VERSION_V1_00,			// Version
	SmbSmp, 						// Prefix
	NULL,							// Arbitrate
	NULL,							// Release
	SmbSmpResourceControl,		// ResControl
	SmbSmpResourceTypeControl	// ResTypeControl
	);
