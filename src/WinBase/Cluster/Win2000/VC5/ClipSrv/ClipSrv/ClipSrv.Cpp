/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 99 <company name>
//
//	Module Name:
//		ClipSrv.cpp
//
//	Description:
//		Resource DLL for ClipBook Server (ClipSrv).
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

//
// Type and constant definitions.
//

// ADDPARAM: Add new properties here.
#define PROP_NAME__COMMENT L"Comment"


// ADDPARAM: Add new properties here.
typedef struct _CLIPSRV_PROPS
{
	PWSTR			pszComment;
} CLIPSRV_PROPS, * PCLIPSRV_PROPS;

typedef struct _CLIPSRV_RESOURCE
{
	RESID					resid; // For validation.
	CLIPSRV_PROPS			propsActive; // The active props.  Used for program flow and control when the resource is online.
	CLIPSRV_PROPS			props; // The props in cluster DB.  May differ from propsActive until OnlineThread reloads them as propsActive.
	HCLUSTER				hCluster;
	HRESOURCE				hResource;
	SC_HANDLE				hService;
	DWORD					dwServicePid;
	HKEY					hkeyParameters;
	RESOURCE_HANDLE 		hResourceHandle;
	LPWSTR					pszResourceName;
	CLUS_WORKER 			cwWorkerThread;
	CLUSTER_RESOURCE_STATE	state;
} CLIPSRV_RESOURCE, * PCLIPSRV_RESOURCE;


//
// Global data.
//

// Forward reference to our RESAPI function table.

extern CLRES_FUNCTION_TABLE g_ClipSrvFunctionTable;

// Single instance semaphore.

#define CLIPSRV_SINGLE_INSTANCE_SEMAPHORE L"Cluster_ClipSrv_Semaphore"
static HANDLE g_hSingleInstanceSemaphoreClipSrv = NULL;
static PCLIPSRV_RESOURCE g_pSingleInstanceResourceClipSrv = NULL;

//
// ClipBook Server resource read-write private properties.
//
RESUTIL_PROPERTY_ITEM
ClipSrvResourcePrivateProperties[] =
{
	{ PROP_NAME__COMMENT, NULL, CLUSPROP_FORMAT_SZ, 0, 0, 0, 0, FIELD_OFFSET( CLIPSRV_PROPS, pszComment ) },
	{ 0 }
};

//
// Registry key checkpoints.
//
LPCWSTR g_pszRegKeysClipSrv[] =
{
	// TODO: Specify any registry keys to be checkpointed for resources of this type
	// e.g. L"System\\CurrentControlSet\\Services\\myservice",
	NULL
};

//
// Crypto key checkpoints.
//
LPCWSTR g_pszCryptoKeysClipSrv[] =
{
	// TODO: Specify any crypto keys to be checkpointed for resources of this type
	// e.g. L"1\\My Provider v1.0\\MYACRONYM",
	NULL
};

//
// Domestic crypto key checkpoints.
//
LPCWSTR g_pszDomesticCryptoKeysClipSrv[] =
{
	// TODO: Specify any domestic crypto keys to be checkpointed for resources of this type
	// e.g. L"1\\My Enhanced Provider v1.0\\MYACRONYM_128",
	NULL
};

//
// Function prototypes.
//

RESID WINAPI ClipSrvOpen(
	IN	LPCWSTR			pszResourceName,
	IN	HKEY			hkeyResourceKey,
	IN	RESOURCE_HANDLE	hResourceHandle
	);

void WINAPI ClipSrvClose( IN RESID resid );

DWORD WINAPI ClipSrvOnline(
	IN		RESID	resid,
	IN OUT	PHANDLE	phEventHandle
	);

DWORD WINAPI ClipSrvOnlineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PCLIPSRV_RESOURCE	pResourceEntry
	);

DWORD WINAPI ClipSrvOffline( IN RESID resid );

DWORD WINAPI ClipSrvOfflineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PCLIPSRV_RESOURCE		pResourceEntry
	);

void WINAPI ClipSrvTerminate( IN RESID resid );

BOOL WINAPI ClipSrvLooksAlive( IN RESID resid );

BOOL WINAPI ClipSrvIsAlive( IN RESID resid );

BOOL ClipSrvCheckIsAlive(
	IN PCLIPSRV_RESOURCE	pResourceEntry,
	IN BOOL				bFullCheck
	);

DWORD WINAPI ClipSrvResourceControl(
	IN	RESID	resid,
	IN	DWORD	nControlCode,
	IN	PVOID	pInBuffer,
	IN	DWORD	cbInBufferSize,
	OUT	PVOID	pOutBuffer,
	IN	DWORD	cbOutBufferSize,
	OUT	LPDWORD	pcbBytesReturned
	);

DWORD ClipSrvGetRequiredDependencies(
	OUT	PVOID	pOutBuffer,
	IN	DWORD	cbOutBufferSize,
	OUT	LPDWORD	pcbBytesReturned
	);

DWORD ClipSrvGetPrivateResProperties(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	OUT		PVOID	pOutBuffer,
	IN		DWORD	cbOutBufferSize,
	OUT		LPDWORD	pcbBytesReturned
	);

DWORD ClipSrvValidatePrivateResProperties(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	IN		const PVOID	pInBuffer,
	IN		DWORD		cbInBufferSize,
	OUT		PCLIPSRV_PROPS	pProps
	);

DWORD ClipSrvSetPrivateResProperties(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	IN		const PVOID	pInBuffer,
	IN		DWORD		cbInBufferSize
	);

DWORD ClipSrvSetNameHandler(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	IN		LPWSTR				pszName
	);


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvDllMain
//
//	Description:
//		Main DLL entry point for the ClipBook Server resource type.
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
BOOLEAN WINAPI ClipSrvDllMain(
	IN	HINSTANCE	hDllHandle,
	IN	DWORD		nReason,
	IN	LPVOID		Reserved
	)
{
	switch ( nReason )
	{
		case DLL_PROCESS_ATTACH:
			g_hSingleInstanceSemaphoreClipSrv = CreateSemaphoreW(
				NULL,
				0,
				1,
				CLIPSRV_SINGLE_INSTANCE_SEMAPHORE
				);
			if ( g_hSingleInstanceSemaphoreClipSrv == NULL )
			{
				return FALSE;
			} // if: error creating semaphore
			if ( GetLastError() != ERROR_ALREADY_EXISTS )
			{
				// If the semaphore didnt exist, set its initial count to 1.
				ReleaseSemaphore( g_hSingleInstanceSemaphoreClipSrv, 1, NULL );
			} // if: semaphore didn't already exist
			break;

		case DLL_PROCESS_DETACH:
			if ( g_hSingleInstanceSemaphoreClipSrv != NULL )
			{
				CloseHandle( g_hSingleInstanceSemaphoreClipSrv );
				g_hSingleInstanceSemaphoreClipSrv = NULL;
			} // if: single instance semaphore was created
			break;

	} // switch: nReason

	return TRUE;

} //*** ClipSrvDllMain()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvStartup
//
//	Description:
//		Startup the resource DLL for the ClipBook Server resource type.
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
DWORD WINAPI ClipSrvStartup(
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
	else if ( lstrcmpiW( pszResourceType, CLIPSRV_RESNAME ) != 0 )
	{
		//
		// This check is also performed by the Startup() in CLRES.CPP.
		//
		nStatus = ERROR_CLUSTER_RESNAME_NOT_FOUND;
	} // if: resource type name not supported
	else
	{
		*pFunctionTable = &g_ClipSrvFunctionTable;
		nStatus = ERROR_SUCCESS;
	} // else: we support this type of resource

	return nStatus;

} //*** ClipSrvStartup()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvOpen
//
//	Description:
//		Open routine for ClipBook Server resources.
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
//			to the ClipSrvStartup routine.  This handle should never be
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
RESID WINAPI ClipSrvOpen(
	IN	LPCWSTR			pszResourceName,
	IN	HKEY			hkeyResourceKey,
	IN	RESOURCE_HANDLE	hResourceHandle
	)
{
	DWORD				nStatus;
	RESID				resid = 0;
	HKEY				hkeyParameters = NULL;
	PCLIPSRV_RESOURCE	pResourceEntry = NULL;

	do											// Loop to avoid goto's.
	{
		//
		// Check if more than one resource of this type.
		//
		if ( WaitForSingleObject( g_hSingleInstanceSemaphoreClipSrv, 0 ) == WAIT_TIMEOUT )
		{
			//
			// A version of this service is already running.
			//
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Service is already running.\n"
				);
			nStatus = ERROR_SERVICE_ALREADY_RUNNING;
			break;
		} // if: semaphore for resources of this type already already locked

		if ( g_pSingleInstanceResourceClipSrv != NULL )
		{
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Service resource info non-null!\n"
				);
			nStatus = ERROR_DUPLICATE_SERVICE_NAME;
			break;
		} // if: resource of this type already exists

		g_pSingleInstanceResourceClipSrv = pResourceEntry;

		//
		// Get a global handle to the Service Control Manager (SCM).
		// There is no call to CloseSCManager(), since the only time we will
		// need to close this handle is if we are shutting down.
		//
		if ( g_schSCMHandle == NULL )
		{
			g_schSCMHandle = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
			if ( g_schSCMHandle == NULL )
			{
				nStatus = GetLastError();
				(g_pfnLogEvent)(
					hResourceHandle,
					LOG_ERROR,
					L"Failed to open Service Control Manager. Error: %1!u!.\n",
					nStatus
					);
				break;
			} // if: error opening the Service Control Manager
		} // if: Service Control Manager not open yet

		//
		// Make sure the service has been stopped.
		//
		nStatus = ResUtilStopResourceService( CLIPSRV_SVCNAME );
		if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				hResourceHandle,
				LOG_ERROR,
				L"Failed to stop the '%1' service. Error: %2!u!.\n",
				CLIPSRV_SVCNAME,
				nStatus
				);
		} // if: error stopping the service

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
		pResourceEntry = static_cast< CLIPSRV_RESOURCE * >(
			LocalAlloc( LMEM_FIXED, sizeof( CLIPSRV_RESOURCE ) )
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
		ZeroMemory( pResourceEntry, sizeof( CLIPSRV_RESOURCE ) );

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
						g_pszRegKeysClipSrv
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
						g_pszCryptoKeysClipSrv
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
						g_pszDomesticCryptoKeysClipSrv
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error configuring domestic crypto key checkpoints

		//
		// Startup for the resource.
		//
		// TODO: Add your resource startup code here.


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

} //*** ClipSrvOpen()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvClose
//
//	Description:
//		Close routine for ClipBook Server resources.
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
void WINAPI ClipSrvClose( IN RESID resid )
{
	PCLIPSRV_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: Close request for a nonexistent resource id %p\n",
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
	// Clean up the semaphore if this is the single resource instance.
	//
	if ( pResourceEntry == g_pSingleInstanceResourceClipSrv )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_INFORMATION,
			L"Close: Setting semaphore %1.\n",
			CLIPSRV_SINGLE_INSTANCE_SEMAPHORE
			);
		g_pSingleInstanceResourceClipSrv = NULL;
		ReleaseSemaphore( g_hSingleInstanceSemaphoreClipSrv, 1 , NULL );
	} // if: this is the single resource instance

	//
	// Deallocate the resource entry.
	//

	// ADDPARAM: Add new properties here.
	LocalFree( pResourceEntry->propsActive.pszComment );
	LocalFree( pResourceEntry->props.pszComment );

	LocalFree( pResourceEntry->pszResourceName );
	LocalFree( pResourceEntry );

} //*** ClipSrvClose()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvOnline
//
//	Description:
//		Online routine for ClipBook Server resources.
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
DWORD WINAPI ClipSrvOnline(
	IN		RESID		resid,
	IN OUT	PHANDLE 	phEventHandle
	)
{
	PCLIPSRV_RESOURCE	pResourceEntry;
	DWORD				nStatus;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: Online request for a nonexistent resource id %p.\n",
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
				reinterpret_cast< PWORKER_START_ROUTINE >( ClipSrvOnlineThread ),
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

} //*** ClipSrvOnline()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvOnlineThread
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
//			A pointer to the CLIPSRV_RESOURCE block for this resource.
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
DWORD WINAPI ClipSrvOnlineThread(
	IN	PCLUS_WORKER		pWorker,
	IN	PCLIPSRV_RESOURCE	pResourceEntry
	)
{
	RESOURCE_STATUS 		resourceStatus;
	DWORD					nStatus = ERROR_SUCCESS;
	DWORD					nPrevCheckpoint;
	DWORD					cbBytesNeeded;
	SERVICE_STATUS_PROCESS	ServiceStatus = { 0 };
	RESOURCE_EXIT_STATE		resExitState;
	LPWSTR					pszNameOfPropInError;

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
					ClipSrvResourcePrivateProperties,
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
		// Create the new environment with the simulated net name when the
		// services queries GetComputerName.
		//
		if ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			nStatus = ResUtilSetResourceServiceEnvironment(
							CLIPSRV_SVCNAME,
							pResourceEntry->hResource,
							g_pfnLogEvent,
							pResourceEntry->hResourceHandle
							);
			if ( nStatus != ERROR_SUCCESS )
			{
				break;
			} // if: error setting the environment for the service
		} // if: not terminating
		else
		{
			break;
		} // else: terminating

		//
		// Stop the service if it's running since we are about to change
		// its parameters.
		//
		nStatus = ResUtilStopResourceService( CLIPSRV_SVCNAME );
		if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"OnlineThread: Failed to stop the '%1' service. Error %2!u!.\n",
				CLIPSRV_SVCNAME,
				nStatus
				);
			break;
		} // if: error stopping the service

		//
		// Make sure the service is ready to be controlled by the cluster.
		//
		if ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			nStatus = ResUtilSetResourceServiceStartParameters(
							CLIPSRV_SVCNAME,
							g_schSCMHandle,
							&pResourceEntry->hService,
							g_pfnLogEvent,
							pResourceEntry->hResourceHandle
							);
			if ( nStatus != ERROR_SUCCESS )
			{
				break;
			} // if:  error setting service start parameters
		} // if: not terminating
		else
		{
			break;
		} // else: terminating

		//
		// Perform resource-specific initialization before starting the service.
		//
		// TODO: Add code to initialize the resource before starting the service.

		//
		// Start the service.
		//
		if ( ! StartServiceW(
						pResourceEntry->hService,
						0,
						NULL
						) )
		{
			nStatus = GetLastError();
			if ( nStatus != ERROR_SERVICE_ALREADY_RUNNING )
			{
				// TODO: Log event to the event log.
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_ERROR,
					L"OnlineThread: Failed to start the '%1' service. Error: %2!u!.\n",
					CLIPSRV_SVCNAME,
					nStatus
					);
				nStatus = ERROR_SERVICE_NEVER_STARTED;
				break;
			} // if: error other than service already running occurred
		} // if: error starting the service

		//
		// Query the status of the service in a loop until it leaves
		// the pending state.
		//
		resourceStatus.ResourceState = ClusterResourceOnlinePending;
		nPrevCheckpoint = 0;
		while ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			//
			// Query the service status.
			//
			if ( ! QueryServiceStatusEx(
						pResourceEntry->hService,
						SC_STATUS_PROCESS_INFO,
						reinterpret_cast< LPBYTE >( &ServiceStatus ),
						sizeof( SERVICE_STATUS_PROCESS ),
						&cbBytesNeeded
						) )
			{
				nStatus = GetLastError();
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_ERROR,
					L"OnlineThread: Failed to query service status for the '%1' service. Error: %2!u!.\n",
					CLIPSRV_SVCNAME,
					nStatus
					);
				resourceStatus.ResourceState = ClusterResourceFailed;
				break;
			} // if: error querying service status

			//
			// If the service is no longer pending, we are done.
			//
			if ( ServiceStatus.dwCurrentState != SERVICE_START_PENDING )
			{
				break;
			} // if: service state is not pending

			//
			// If the service checkpoint value changed, use it when notifying
			// the Resource Monitor of our current status.
			//
			if ( nPrevCheckpoint != ServiceStatus.dwCheckPoint )
			{
				nPrevCheckpoint = ServiceStatus.dwCheckPoint;
				resourceStatus.CheckPoint++;
			}

			//
			// Notify the Resource Monitor of our current state.
			//
			resExitState = static_cast< RESOURCE_EXIT_STATE >(
				(g_pfnSetResourceStatus)(
								pResourceEntry->hResourceHandle,
								&resourceStatus
								) );
			if ( resExitState == ResourceExitStateTerminate )
			{
				break;
			} // if: resource is being terminated

			//
			// Check again in 1/2 second.
			//
			Sleep( 500 );

		} // while: not terminating while querying the status of the service

		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error querying the status of the service

		//
		// Assume that we failed.
		//
		resourceStatus.ResourceState = ClusterResourceFailed;

		//
		// If we exited the loop before setting ServiceStatus, then return now.
		//
		if ( ClusWorkerCheckTerminate( pWorker ) )
		{
			break;
		} // if: being terminated

		if ( ServiceStatus.dwCurrentState != SERVICE_RUNNING )
		{
			nStatus = ERROR_SERVICE_NEVER_STARTED;
			// TODO: Log event to the event log
			(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_ERROR,
					L"OnlineThread: Failed to start the '%1' service. Error: %2!u!.\n",
					CLIPSRV_SVCNAME,
					nStatus
					);
			break;
		} // if: service not running when loop exited

		//
		// Set status to online and save process ID of the service.
		// This is used to enable us to terminate the resource more
		// effectively.
		//
		resourceStatus.ResourceState = ClusterResourceOnline;
		if ( ! (ServiceStatus.dwServiceFlags & SERVICE_RUNS_IN_SYSTEM_PROCESS) )
		{
			pResourceEntry->dwServicePid = ServiceStatus.dwProcessId;
		} // if: not running in the system process

		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_INFORMATION,
			L"The '%1' service is now on line.\n",
			CLIPSRV_SVCNAME
			);

	} while ( 0 );

	if ( nStatus != ERROR_SUCCESS )
	{
		(g_pfnLogEvent)(
			pResourceEntry->hResourceHandle,
			LOG_ERROR,
			L"OnlineThread: Error %1!u! bringing resource online.\n",
			nStatus
			);
		if ( pResourceEntry->hService != NULL )
		{
			CloseServiceHandle( pResourceEntry->hService );
			pResourceEntry->hService = NULL;
		} // if: service handle was opened
	} // if: error occurred

	g_pfnSetResourceStatus( pResourceEntry->hResourceHandle, &resourceStatus );
	pResourceEntry->state = resourceStatus.ResourceState;

	return nStatus;

} //*** ClipSrvOnlineThread()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvOffline
//
//	Description:
//		Offline routine for ClipBook Server resources.
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
DWORD WINAPI ClipSrvOffline( IN RESID resid )
{
	PCLIPSRV_RESOURCE	pResourceEntry;
	DWORD				nStatus;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: Offline request for a nonexistent resource id %p\n",
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
				reinterpret_cast< PWORKER_START_ROUTINE >( ClipSrvOfflineThread ),
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

} //*** ClipSrvOffline()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvOfflineThread
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
//			A pointer to the CLIPSRV_RESOURCE block for this resource.
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
DWORD WINAPI ClipSrvOfflineThread(
	IN	PCLUS_WORKER	pWorker,
	IN	PCLIPSRV_RESOURCE	pResourceEntry
	)
{
	RESOURCE_STATUS 	resourceStatus;
	DWORD				nStatus = ERROR_SUCCESS;
	DWORD				nRetryTime = 300;	  // 300 msec at a time
	BOOL				bDidStop = FALSE;
	SERVICE_STATUS		ServiceStatus;

	ResUtilInitializeResourceStatus( &resourceStatus );

	resourceStatus.ResourceState = ClusterResourceFailed;
	resourceStatus.WaitHint = 0;
	resourceStatus.CheckPoint = 1;

	do											// Loop to avoid goto's.
	{
		//
		// If the service has gone offline or was never brought online,
		// we're done.
		//
		if ( pResourceEntry->hService == NULL )
		{
			resourceStatus.ResourceState = ClusterResourceOffline;
			break;
		}

		//
		// Try to stop the service.  Wait for it to terminate as long
		// as we're not asked to terminate.
		//
		while ( ! ClusWorkerCheckTerminate( pWorker ) )
		{
			nStatus = (ControlService(
							pResourceEntry->hService,
							(bDidStop
								? SERVICE_CONTROL_INTERROGATE
								: SERVICE_CONTROL_STOP),
							&ServiceStatus
							)
						? ERROR_SUCCESS
						: GetLastError()
						);

			if ( nStatus == ERROR_SUCCESS )
			{
				bDidStop = TRUE;

				if ( ServiceStatus.dwCurrentState == SERVICE_STOPPED )
				{
					(g_pfnLogEvent)(
						pResourceEntry->hResourceHandle,
						LOG_INFORMATION,
						L"OfflineThread: The '%1' service stopped.\n",
						CLIPSRV_SVCNAME
						);

					//
					// Set the status.
					//
					resourceStatus.ResourceState = ClusterResourceOffline;
					CloseServiceHandle( pResourceEntry->hService );
					pResourceEntry->hService = NULL;
					pResourceEntry->dwServicePid = 0;
					(g_pfnLogEvent)(
						pResourceEntry->hResourceHandle,
						LOG_INFORMATION,
						L"OfflineThread: Service is now offline.\n"
						);
					break;
				} // if: current service state is STOPPED
			} // if: ControlService completed successfully

			if (	( nStatus == ERROR_EXCEPTION_IN_SERVICE )
				||	( nStatus == ERROR_PROCESS_ABORTED )
				||	( nStatus == ERROR_SERVICE_NOT_ACTIVE ) )
			{
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_INFORMATION,
					L"OfflineThread: The '%1' service died or is not active any more; status = %2!u!.\n",
					CLIPSRV_SVCNAME,
					nStatus
					);

				//
				// Set the status.
				//
				resourceStatus.ResourceState = ClusterResourceOffline;
				CloseServiceHandle( pResourceEntry->hService );
				pResourceEntry->hService = NULL;
				pResourceEntry->dwServicePid = 0;
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_INFORMATION,
					L"OfflineThread: Service is now offline.\n"
					);
				break;
			} // if: service stopped abnormally

			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_INFORMATION,
				L"OfflineThread: retrying...\n"
				);

			Sleep( nRetryTime );

		} // while: not asked to terminate
	} while ( 0 );

	g_pfnSetResourceStatus( pResourceEntry->hResourceHandle, &resourceStatus );
	pResourceEntry->state = resourceStatus.ResourceState;

	return nStatus;

} //*** ClipSrvOfflineThread()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvTerminate
//
//	Description:
//		Terminate routine for ClipBook Server resources.
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
void WINAPI ClipSrvTerminate( IN RESID resid )
{
	PCLIPSRV_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: Terminate request for a nonexistent resource id %p\n",
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

	if ( pResourceEntry->hService != NULL )
	{
		DWORD			nTotalRetryTime = 30*1000;	// Wait 30 secs for shutdown
		DWORD			nRetryTime = 300;			// 300 msec at a time
		DWORD			nStatus;
		BOOL			bDidStop = FALSE;
		SERVICE_STATUS	ServiceStatus;

		for (;;)
		{
			nStatus = (ControlService(
							pResourceEntry->hService,
							(bDidStop
								? SERVICE_CONTROL_INTERROGATE
								: SERVICE_CONTROL_STOP),
							&ServiceStatus
							)
						? ERROR_SUCCESS
						: GetLastError()
						);

			if ( nStatus == ERROR_SUCCESS )
			{
				bDidStop = TRUE;

				if ( ServiceStatus.dwCurrentState == SERVICE_STOPPED )
				{
					(g_pfnLogEvent)(
						pResourceEntry->hResourceHandle,
						LOG_INFORMATION,
						L"Terminate: The '%1' service stopped.\n",
						CLIPSRV_SVCNAME
						);
					break;
				} // if: current service state is STOPPED
			} // if: ControlService completed successfully

			if (	( nStatus == ERROR_EXCEPTION_IN_SERVICE )
				||	( nStatus == ERROR_PROCESS_ABORTED )
				||	( nStatus == ERROR_SERVICE_NOT_ACTIVE ) )
			{
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_INFORMATION,
					L"Terminate: Service died; status = %1!u!.\n",
					nStatus
					);
				break;
			} // if: service stopped abnormally

			if ( (nTotalRetryTime -= nRetryTime) <= 0 )
			{
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_ERROR,
					L"Terminate: Service did not stop; giving up.\n" );

				break;
			} // if: retried too many times

			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_INFORMATION,
				L"Terminate: retrying...\n"
				);

			Sleep( nRetryTime );

		} // forever

		//
		// Declare the service offline.  It may not truly be offline, so
		// if there is a pid for this service, try and terminate that process.
		// Note that terminating a process doesnt terminate all the child
		// processes.
		//
		if ( pResourceEntry->dwServicePid != 0 )
		{
			HANDLE hSvcProcess = NULL;

			hSvcProcess = OpenProcess(
								PROCESS_TERMINATE,
								FALSE,
								pResourceEntry->dwServicePid
								);
			if ( hSvcProcess != NULL )
			{
				(g_pfnLogEvent)(
					pResourceEntry->hResourceHandle,
					LOG_INFORMATION,
					L"Terminate: Terminating processid %1!u!\n",
					pResourceEntry->dwServicePid
					);
				TerminateProcess( hSvcProcess, 0 );
				CloseHandle( hSvcProcess );
			} // if: opened process successfully
		} // if: service process ID available

		CloseServiceHandle( pResourceEntry->hService );
		pResourceEntry->hService = NULL;
		pResourceEntry->dwServicePid = 0;

	} // if: service was started

	pResourceEntry->state = ClusterResourceOffline;

} //*** ClipSrvTerminate()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvLooksAlive
//
//	Description:
//		LooksAlive routine for ClipBook Server resources.
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
BOOL WINAPI ClipSrvLooksAlive( IN RESID resid )
{
	PCLIPSRV_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: LooksAlive request for a nonexistent resource id %p\n",
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
	return ClipSrvCheckIsAlive( pResourceEntry, FALSE /* bFullCheck */ );

} //*** ClipSrvLooksAlive()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvIsAlive
//
//	Description:
//		IsAlive routine for ClipBook Server resources.
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
BOOL WINAPI ClipSrvIsAlive( IN RESID resid )
{
	PCLIPSRV_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: IsAlive request for a nonexistent resource id %p\n",
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
	return ClipSrvCheckIsAlive( pResourceEntry, TRUE /* bFullCheck */ );

} //** ClipSrvIsAlive()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvCheckIsAlive
//
//	Description:
//		Check to see if the resource is alive for ClipBook Server
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
BOOL ClipSrvCheckIsAlive(
	IN PCLIPSRV_RESOURCE	pResourceEntry,
	IN BOOL					bFullCheck
	)
{
	BOOL	bIsAlive = TRUE;
	DWORD	nStatus;

	do											// Loop to avoid goto's.
	{
		//
		// Check to see if the resource is alive.
		//
		nStatus = ResUtilVerifyService( pResourceEntry->hService );
		if ( nStatus != ERROR_SUCCESS )
		{
			(g_pfnLogEvent)(
				pResourceEntry->hResourceHandle,
				LOG_ERROR,
				L"CheckIsAlive: Verification of the '%1' service failed. Error: %2!u!.\n",
				CLIPSRV_SVCNAME,
				nStatus
				);
			bIsAlive = FALSE;
			break;
		} // if: error verifying service

		if ( bFullCheck )
		{
			// TODO: Add code to perform a full check.
		} // if: performing a full check
	} while ( 0 );

	return bIsAlive;

} //*** ClipSrvCheckIsAlive()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvResourceControl
//
//	Description:
//		ResourceControl routine for ClipBook Server resources.
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
DWORD WINAPI ClipSrvResourceControl(
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
	PCLIPSRV_RESOURCE	pResourceEntry;

	//
	// Verify we have a valid resource ID.
	//

	pResourceEntry = static_cast< PCLIPSRV_RESOURCE >( resid );

	if ( pResourceEntry == NULL )
	{
		DBG_PRINT(
			"ClipSrv: ResourceControl request for a nonexistent resource id %p\n",
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
							ClipSrvResourcePrivateProperties,
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
			nStatus = ClipSrvGetPrivateResProperties(
							pResourceEntry,
							pOutBuffer,
							cbOutBufferSize,
							pcbBytesReturned
							);
			break;

		case CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES:
			nStatus = ClipSrvValidatePrivateResProperties(
							pResourceEntry,
							pInBuffer,
							cbInBufferSize,
							NULL
							);
			break;

		case CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES:
			nStatus = ClipSrvSetPrivateResProperties(
							pResourceEntry,
							pInBuffer,
							cbInBufferSize
							);
			break;

		case CLUSCTL_RESOURCE_SET_NAME:
			nStatus = ClipSrvSetNameHandler(
							pResourceEntry,
							static_cast< LPWSTR >( pInBuffer )
							);
			break;

		case CLUSCTL_RESOURCE_GET_REQUIRED_DEPENDENCIES:
			nStatus = ClipSrvGetRequiredDependencies(
							pOutBuffer,
							cbOutBufferSize,
							pcbBytesReturned
							);
			break;

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

} //*** ClipSrvResourceControl()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvResourceTypeControl
//
//	Description:
//		ResourceTypeControl routine for ClipBook Server resources.
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
DWORD WINAPI ClipSrvResourceTypeControl(
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
							ClipSrvResourcePrivateProperties,
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
			nStatus = ClipSrvGetRequiredDependencies(
							pOutBuffer,
							cbOutBufferSize,
							pcbBytesReturned
							);
			break;

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

} //*** ClipSrvResourceTypeControl()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvGetRequiredDependencies
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_GET_REQUIRED_DEPENDENCIES control
//		function for resources of type ClipBook Server.
//
//	Arguments:
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
//		Win32 error code
//			The function failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD ClipSrvGetRequiredDependencies(
	OUT	PVOID	pOutBuffer,
	IN	DWORD	cbOutBufferSize,
	OUT	LPDWORD	pcbBytesReturned
	)
{
	// TODO: Specify your resource's required dependencies here.
	//   The default is that the resource requires a dependency on a
	//   storage class resource (e.g. Physical Disk) and an IP Address
	//   resource.
	struct DEP_DATA
	{
		CLUSPROP_RESOURCE_CLASS	rcStorage;
		CLUSPROP_SZ_DECLARE( netnameEntry, sizeof( RESOURCE_TYPE_NETWORK_NAME ) / sizeof( WCHAR ) );
		CLUSPROP_SYNTAX			endmark;
	};
	DEP_DATA *	pdepdata = static_cast< DEP_DATA * >( pOutBuffer );
	DWORD		nStatus;

	*pcbBytesReturned = sizeof( DEP_DATA );
	if ( cbOutBufferSize < sizeof( DEP_DATA ) )
	{
		if ( pOutBuffer == NULL )
		{
			nStatus = ERROR_SUCCESS;
		} // if: no buffer specified
		else
		{
			nStatus = ERROR_MORE_DATA;
		} // if: buffer specified
	} // if: output buffer is too small
	else
	{
		ZeroMemory( pdepdata, sizeof( DEP_DATA ) );

		//
		// Add the Storage class entry.
		//
		pdepdata->rcStorage.Syntax.dw = CLUSPROP_SYNTAX_RESCLASS;
		pdepdata->rcStorage.cbLength = sizeof( pdepdata->rcStorage.rc );
		pdepdata->rcStorage.rc = CLUS_RESCLASS_STORAGE;

		//
		// Add the IP Address entry.
		//
		pdepdata->netnameEntry.Syntax.dw = CLUSPROP_SYNTAX_NAME;
		pdepdata->netnameEntry.cbLength = sizeof( RESOURCE_TYPE_NETWORK_NAME );
		lstrcpyW( pdepdata->netnameEntry.sz, RESOURCE_TYPE_NETWORK_NAME );

		//
		// Add the endmark.
		//
		pdepdata->endmark.dw = CLUSPROP_SYNTAX_ENDMARK;

		nStatus = ERROR_SUCCESS;
	} // else: output buffer is large enough

	return nStatus;

} //*** ClipSrvGetRequiredDependencies()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvGetPrivateResProperties
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_GET_PRIVATE_PROPERTIES control
//		function for resources of type ClipBook Server.
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
DWORD ClipSrvGetPrivateResProperties(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	OUT		PVOID				pOutBuffer,
	IN		DWORD				cbOutBufferSize,
	OUT		LPDWORD				pcbBytesReturned
	)
{
	DWORD	nStatus;
	DWORD	cbRequired = 0;

	nStatus = ResUtilGetAllProperties(
					pResourceEntry->hkeyParameters,
					ClipSrvResourcePrivateProperties,
					pOutBuffer,
					cbOutBufferSize,
					pcbBytesReturned,
					&cbRequired
					);
	if ( nStatus == ERROR_MORE_DATA )
	{
		if ( pcbBytesReturned != NULL )
		{
			*pcbBytesReturned = cbRequired;
		} // if: pcbBytesReturned arg is not NULL
	} // if: output buffer is too small

	return nStatus;

} //*** ClipSrvGetPrivateResProperties()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvValidatePrivateResProperties
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES control
//		function for resources of type ClipBook Server.
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
DWORD ClipSrvValidatePrivateResProperties(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	IN		PVOID				pInBuffer,
	IN		DWORD				cbInBufferSize,
	OUT		PCLIPSRV_PROPS		pProps
	)
{
	DWORD			nStatus = ERROR_SUCCESS;
	CLIPSRV_PROPS	propsCurrent;
	CLIPSRV_PROPS	propsNew;
	PCLIPSRV_PROPS	pLocalProps = NULL;
	LPWSTR			pszNameOfPropInError;
	BOOL			bRetrievedProps = FALSE;

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
					 ClipSrvResourcePrivateProperties,
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
		ZeroMemory( pLocalProps, sizeof( CLIPSRV_PROPS ) );
		nStatus = ResUtilDupParameterBlock(
						reinterpret_cast< LPBYTE >( pLocalProps ),
						reinterpret_cast< LPBYTE >( &propsCurrent ),
						ClipSrvResourcePrivateProperties
						);
		if ( nStatus != ERROR_SUCCESS )
		{
			break;
		} // if: error duplicating the parameter block

		//
		// Parse and validate the properties.
		//
		nStatus = ResUtilVerifyPropertyTable(
						ClipSrvResourcePrivateProperties,
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
			ClipSrvResourcePrivateProperties
			);
	} // if: we duplicated the parameter block

	if ( bRetrievedProps )
	{
		ResUtilFreeParameterBlock(
			reinterpret_cast< LPBYTE >( &propsCurrent ),
			NULL,
			ClipSrvResourcePrivateProperties
			);
	} // if: properties were retrieved

	return nStatus;

} // ClipSrvValidatePrivateResProperties


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvSetPrivateResProperties
//
//	Description:
//		Processes the CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES control
//		function for resources of type ClipBook Server.
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
DWORD ClipSrvSetPrivateResProperties(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
	IN		PVOID				pInBuffer,
	IN		DWORD				cbInBufferSize
	)
{
	DWORD			nStatus = ERROR_SUCCESS;
	CLIPSRV_PROPS	props;

	//
	// Parse the properties so they can be validated together.
	// This routine does individual property validation.
	//
	nStatus = ClipSrvValidatePrivateResProperties( pResourceEntry, pInBuffer, cbInBufferSize, &props );
	if ( nStatus == ERROR_SUCCESS )
	{
		//
		// Save the property values.
		//
		nStatus = ResUtilSetPropertyParameterBlock(
						pResourceEntry->hkeyParameters,
						ClipSrvResourcePrivateProperties,
						NULL,
						reinterpret_cast< LPBYTE >( &props ),
						pInBuffer,
						cbInBufferSize,
						reinterpret_cast< LPBYTE >( &pResourceEntry->props )
						);

		ResUtilFreeParameterBlock(
			reinterpret_cast< LPBYTE >( &props ),
			reinterpret_cast< LPBYTE >( &pResourceEntry->props ),
			ClipSrvResourcePrivateProperties
			);

		//
		// If the resource is online, return a non-success status.
		//
		// TODO: Modify the code below if your resource can handle
		// changes to properties while it is still online.
		if ( nStatus == ERROR_SUCCESS )
		{
			if ( pResourceEntry->state == ClusterResourceOnline )
			{
				nStatus = ERROR_RESOURCE_PROPERTIES_STORED;
			} // if: resource is currently online
			else if ( pResourceEntry->state == ClusterResourceOnlinePending )
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

} //*** ClipSrvSetPrivateResProperties()


/////////////////////////////////////////////////////////////////////////////
//++
//
//	ClipSrvSetNameHandler
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
DWORD ClipSrvSetNameHandler(
	IN OUT	PCLIPSRV_RESOURCE	pResourceEntry,
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

} //*** ClipSrvSetNameHandler()


/////////////////////////////////////////////////////////////////////////////
//
// Define Function Table
//
/////////////////////////////////////////////////////////////////////////////

CLRES_V1_FUNCTION_TABLE(
	g_ClipSrvFunctionTable,		// Name
	CLRES_VERSION_V1_00,			// Version
	ClipSrv, 						// Prefix
	NULL,							// Arbitrate
	NULL,							// Release
	ClipSrvResourceControl,		// ResControl
	ClipSrvResourceTypeControl	// ResTypeControl
	);
