// --InstForm.cpp---------------------------------------------------------------
// Command line utility to install or remove Exchange forms.
//  
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "exchcli.h"

class CUserParams;			// must be declared before "instform.chk"

#include "iformmsg.h"		// created from instform.mc by the message compiler
#include "instform.chk"

// Define a warning to exit if user asks for help.
const HRESULT EXIT_WARNING = MAPI_W_ERRORS_RETURNED;

LPTSTR		lpszAppName = TEXT("InstForm");

//$--INTERNAL_ERROR-------------------------------------------------------------
//  Helper function for EventLogMsg
// -----------------------------------------------------------------------------
static inline VOID INTERNAL_ERROR(
    IN LPCTSTR str,
    IN const HRESULT hr)
{
    TCHAR   szErrorCode[16] = {0};

    EventLogMsg(
        INSTFORM_INTERNAL_ERROR,
        2, str, _itot( hr, szErrorCode, 16),
        0);
}

//$--fFileExists()--------------------------------------------------------------
// RETURNS: TRUE if the file exists and FALSE if not.
// -----------------------------------------------------------------------------

BOOL fFileExists( 
    IN LPTSTR lpszFileSpec)   // File to validate exists.
{
    struct _tfinddata_t FileInfo = {0};
    long lhRet = _tfindfirst( lpszFileSpec, &FileInfo);

    if( lhRet == -1)
        return( FALSE);
    _findclose( lhRet);
    
    return( TRUE);
}


//$--CUserParams----------------------------------------------------------------
// Container class for user's parameters and parsing the command line.
// -----------------------------------------------------------------------------

class CUserParams
{
public:
    CUserParams();
    
    HRESULT HrParseCommandLine(
        IN int      argc,       // number of arguments on command line
        IN char*    argv[]);    // array of command line arguments

	friend HRESULT	HrSetupAndDoIt( CUserParams&);

    // These members will contain the arguments 
    // and values specified by the user.
    BOOL    m_fInstall;         // TRUE when installing a form.

protected:
    BOOL    m_fRemove;          // TRUE when removing a form.
    HFRMREG m_hFrmReg;          // The registry to install form in.
    char*   m_pszCfgFile;       // The configuration file name for installing a form.
    char*   m_pszMsgClass;      // The message class for removing a form.
    char*   m_pszFolder;        // The path of the folder for installing in a folder registry.
    char*   m_pszProfile;       // The profile to logon to.
    char*   m_pszPassword;      // The password for logon.
    char*   m_pszMsgStore;      // The Display Name of the message store.

protected:
    void PrintUsage( IN BOOL fHelp = FALSE);
    static char*    m_pszFlagArray[];
    static char*    m_pszRegArray[];

    // These MUST correspond to the m_pszFlagArray[].
    enum eFlagIndex
    {
        NON_FLAG = MAX_ULONG,
        HELP1 = 0,
        HELP2,
        INSTALL,
        REMOVE,
        VALUE_REQUIRED, // Place flags that require a value below.
        REGISTRY = VALUE_REQUIRED,
        FOLDER,
        PASSWORD,
        EPROFILE,
        MSGSTORE,
    };
};

// -----------------------------------------------------------------------------
// Arrays that belong to CUserParams for parsing command line.
// -----------------------------------------------------------------------------

char* CUserParams::m_pszFlagArray[] = 
{
    "?",
    "HELP",
    "INSTALL",
    "REMOVE",
    // Place flags that require a value below.
    "REGISTRY",
    "FOLDER",
    "PASSWORD",
    "PROFILE",
    "MSGSTORE",
};

// This array is defined to correspond to MAPI defined constants listed in 
// the m_hFrmRegArray defined below, so the order is important.
char* CUserParams::m_pszRegArray[] = 
{
    "LOCAL",     
    "PERSONAL",  
    "FOLDER",    
    "ENTERPRISE",
};

// This array is defined to correspond to the strings 
// in the array m_pszRegArray defined above.
static HFRMREG m_hFrmRegArray[] =
{
    HFRMREG_LOCAL,
    HFRMREG_PERSONAL,
    HFRMREG_FOLDER,
    HFRMREG_ENTERPRISE,
};

// $--CUserParams::PrintUsage()-------------------------------------------------
// Print the usage message for the command line parameters.
// -----------------------------------------------------------------------------

void CUserParams::PrintUsage( 
    IN BOOL fHelp) // True if complete help is wanted.
{
    printf( 
        "USAGE:  INSTFORM /INSTALL cfg_file [flags]\n"
        "   OR:  INSTFORM /REMOVE msg_class [flags]\n");
        
    if( !fHelp)
        return;

    printf(     
        "\n"
        "   /HELP or /? Show help information.\n"
        "\n"
        "   /INSTALL    To install the form specified in the cfg_file\n"
        "\n"
        "   /REMOVE     To remove the form specified by the msg_class.\n"
        "\n"
        "   /REGISTRY=  Flag to specify which registry to install form in.\n"
        "               FOLDER the /FOLDER option must be specified.\n"
        "               PERSONAL\n"
        "               LOCAL\n"
        "               ENTERPRISE\n"
        "\n"
        "   /FOLDER=    Specify the folder path of the registry to install in. Example:\n"
        "                   /FOLDER=\"top of information store\\inbox\"\n"
        "\n"
        "               When this parameter is specified the /REGISTRY=FOLDER is\n"
        "               assumed and need not be specified.  Any other /REGISTRY=\n"
        "               option is an error.\n"
        "\n"
        "   /PROFILE=   Specify the profile for logon.  Optional for local registry.\n"
        "\n"
        "   /PASSWORD=  Specify the password if needed.\n"
        "\n"
        "   /MSGSTORE=  Specify the display name of the message store that contains\n"
        "               the folder specified.  This is only valid with folders.  If\n"
        "               not specified the default message store will be used.\n"
        "\n"
        "   cfg_file    The name of the configuration file of the form to install.\n"
        "\n"
        "   msg_class   The message class of the form to be removed from the\n"
        "               forms registry.\n"
    );
}

// $--CUserParams::CUserParams()------------------------------------------------
// CONSTRUCTOR to initialize the user parameter container.
// -----------------------------------------------------------------------------

CUserParams::CUserParams()
{
    m_fInstall      = FALSE;
    m_fRemove       = FALSE;
    m_hFrmReg       = MAX_ULONG;
    m_pszMsgClass   = NULL;
    m_pszCfgFile    = NULL;
    m_pszFolder     = NULL;
    m_pszProfile    = NULL;
    m_pszPassword   = NULL;
    m_pszMsgStore   = NULL;
}

// $--CUserParams::HrParseCommandLine()-----------------------------------------
// Parse the command line arguments and place their values in the appropriate 
// member variables.
// -----------------------------------------------------------------------------

HRESULT CUserParams::HrParseCommandLine(
    IN int      argc,           // number of arguments on command line
    IN char*    argv[])         // array of command line arguments
{
    HRESULT     hr              = NOERROR;
    int         iArg            = 0;
    int         cNonFlagArgs    = 0;
    eFlagIndex  nFlagIndex      = NON_FLAG;
    char*       pszValue        = NULL;
    char*       pszFirstArg     = NULL;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    DEBUGPRIVATE( "CUserParams::HrParseCommandLine()");

    // If there are no flags on the command line then just print a usage message.
    if( argc < 2)
    {
        PrintUsage();
        return( EXIT_WARNING);
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Do an initial check for /? or /HELP.  If found, don't do any other parsing.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    for (iArg = 1; iArg < argc; iArg++)
    {   // Ignore return value while we look for help flags.
        hr = _HrExpandCommandLineArgument( argv[iArg], m_pszFlagArray, 
            ARRAY_CNT( m_pszFlagArray), (ULONG*) &nFlagIndex, NULL, &pszValue);

        if( SUCCEEDED( hr) && nFlagIndex == HELP1 || nFlagIndex == HELP2)
        {
            PrintUsage( TRUE);
            return( EXIT_WARNING);
        }
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Loop through and parse all the command line arguments.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    for( iArg = 1; iArg < argc; iArg++)
    {
        hr = _HrExpandCommandLineArgument( argv[iArg], m_pszFlagArray,
            ARRAY_CNT( m_pszFlagArray), (ULONG*) &nFlagIndex, NULL, &pszValue);
        if( FAILED(hr))
        {
            fprintf(stderr, "ERROR: unknown command line parameter: %s.\n", argv[ iArg]);
            goto cleanup;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // Parse non-flag arguments.
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        if( nFlagIndex == NON_FLAG && pszValue != NULL)
        {
            switch( cNonFlagArgs ++)
            {
                case 0:     // Either cfg_file or msg_class
                    pszFirstArg = pszValue;
                    break;

                default:    // Too many arguments!!!
                    fprintf( stderr, "ERROR: too many arguments: %s\n", argv[iArg]);
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
            }
        }
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        else // Parse the flag arguments.
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        {
            if( nFlagIndex < VALUE_REQUIRED)
            {               
                if( pszValue)
                {   // No value needed here.
                    fprintf( stderr, "ERROR: flag /%s does not take a value.\n", m_pszFlagArray[ nFlagIndex]);
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
            }
            else // nFlagIndex >= VALUE_REQUIRED
            {
                if( !pszValue)
                {   // Make sure user supplied required values.
                    fprintf( stderr, "ERROR: flag /%s requires a value.\n", m_pszFlagArray[ nFlagIndex]);
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
            }

            switch( nFlagIndex)
            {
                case INSTALL:
                    m_fInstall = TRUE;
                    break;

                case REMOVE:
                    m_fRemove = TRUE;
                    break;

                case REGISTRY:
                    // Look up the registry value entered by the user and convert 
                    // to a value that MAPI will understand.
                    hr = _HrFindArrayValue( pszValue, m_pszRegArray, ARRAY_CNT( m_pszRegArray), &m_hFrmReg);
                    if (FAILED(hr))
                    {
                        fprintf(stderr, "ERROR: invalid registry value: %s\n", pszValue);
                        goto cleanup;
                    }
                    m_hFrmReg = m_hFrmRegArray[ m_hFrmReg];

                    // If they specified the /FOLDER= flag then the only registry
                    // flag they can specify is FOLDER.
                    if( m_hFrmReg != HFRMREG_FOLDER && m_pszFolder != NULL)
                    {
                        fprintf( stderr, "ERROR: When specifying \"/FOLDER=\" omit the \"/REGISTRY=\" flag.\n");
                        hr = HR_LOG(E_FAIL);
                        goto cleanup;
                    }
                    break;

                case FOLDER:
                    if( m_hFrmReg != HFRMREG_FOLDER && m_hFrmReg != MAX_ULONG)
                    {
                        fprintf( stderr, "ERROR: When specifying \"/FOLDER=\" omit the \"/REGISTRY=\" flag.\n");
                        hr = HR_LOG(E_FAIL);
                        goto cleanup;
                    }
                    m_hFrmReg = HFRMREG_FOLDER;
                    m_pszFolder = pszValue;
                    break;
                
                case PASSWORD:
                    m_pszPassword = pszValue;
                    break;

                case EPROFILE:
                    m_pszProfile = pszValue;
                    break;

                case MSGSTORE:
                    m_pszMsgStore = pszValue;
                    break;

                default:
                    // Unexpected value in m_pszFlagArray and the user specified it.
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
            }
        }
    }   // End For Loop

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Final parameter validation.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Validate that either INSTALL or REMOVE was specifed.
    if( m_fInstall)
    {   // They specified /INSTALL
        if( m_fRemove)
        {
            fprintf( stderr, "ERROR: Conflicting command line arguments.\n"
                             "       Both /INSTALL and /REMOVE can not be specified.\n");
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        if( !pszFirstArg)
        {
            fprintf( stderr, "ERROR: please specify the cfg_file name.\n");
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        if( !fFileExists( pszFirstArg))
        {
            fprintf( stderr, "ERROR: can not find file %s\n", pszFirstArg);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        m_pszCfgFile = pszFirstArg;
    }
    else if( m_fRemove)
    {   // They specified /REMOVE
        if( !pszFirstArg)
        {
            fprintf( stderr, "ERROR: please specify the msg_class name.\n");
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        m_pszMsgClass = pszFirstArg;
    }
    else
    {
        fprintf( stderr, "ERROR: please specify either /INSTALL or /REMOVE.\n");
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // It is an error to specify the folder registry but no folder name.
    if( m_hFrmReg == HFRMREG_FOLDER && !m_pszFolder)
    {   
        fprintf( stderr, "ERROR: You must specify \"/FOLDER=\" with the \"/REGISTRY=FOLDER\" flag.\n");
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // It is an error to specify message store without specifiying the folder registry.
    if( m_pszMsgStore && m_hFrmReg != HFRMREG_FOLDER)
    {   
        fprintf( stderr, "ERROR: \"/MSGSTORE=\" is only valid when \"/FOLDER=\" has been specified.\n");
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // The profile must be specified unless using the local registry.
    if( m_hFrmReg != HFRMREG_LOCAL && !m_pszProfile)
    {   
        fprintf( stderr, "ERROR: You must specify the profile name.\n");
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // If user did not specify the registry then use the default one.
    if( m_hFrmReg == MAX_ULONG)
        m_hFrmReg = HFRMREG_DEFAULT;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
cleanup:
    RETURN( hr);
}

//$--HrOpenMsgStoreFolderByName()-----------------------------------------------
// Returns pointer to open folder resource.  If MsgStore is NULL, default message
// store is assumed.
// -----------------------------------------------------------------------------

HRESULT
HrOpenMsgStoreFolderByName(
	IN	LPMAPISESSION	lpMAPISession,  // Active session handle
	IN	LPTSTR			lpszMsgStore,   // Name of message store, or NULL for default
	IN	LPTSTR			lpszFolder,     // Folder path name to open
	OUT	LPMAPIFOLDER	*lppFolder)     // RETURN: open folder interface
{
	HRESULT			hr			 = NOERROR;
	ULONG			cbeid 		 = 0L;
	LPENTRYID		lpeid		 = NULL;
	LPMDB			lpMDB		 = NULL;
	LPMAPIFOLDER	lpFolder	 = NULL;

	DEBUGPUBLIC( "HrOpenMsgStoreFolderByName()");

	hr = CHK_HrOpenMsgStoreFolderByName(
		lpMAPISession, lpszMsgStore, lpszFolder,
		lppFolder);
	if( FAILED( hr))
		RETURN( hr);

	// Get the entry ID of the specified or default message store.
	if( lpszMsgStore)
	    hr = HrMAPIFindStore( lpMAPISession, lpszMsgStore, &cbeid, &lpeid);
	else
	    hr = HrMAPIFindDefaultMsgStore( lpMAPISession, &cbeid, &lpeid);
	if( FAILED( hr))
		goto cleanup;

	ASSERTERROR( cbeid != 0, "Entry ID count should not be zero."); 
	ASSERTERROR( lpeid != NULL, "NULL lpeid pointer");

	// Open the message store.
	hr = lpMAPISession->OpenMsgStore(
			0, cbeid, lpeid, NULL, 
			MDB_WRITE | MAPI_DEFERRED_ERRORS | MDB_NO_DIALOG,
			&lpMDB);
	if( FAILED(hr))
	    goto cleanup;

	ASSERT_IUNKNOWN_PTR( lpMDB, "Invalid store pointer");

    hr = HrMAPIOpenFolderEx( lpMDB, TEXT('\\'), lpszFolder, &lpFolder);
    if( FAILED(hr))
    	goto cleanup;

	*lppFolder = lpFolder;

cleanup:
	MAPIFREEBUFFER( lpeid);

	ULRELEASE( lpMDB);

	RETURN( hr);
}

//$--HrOpenFormContainer-----------------------------------------------------
// Returns open form container interface.  NULLs may be passed for unnecessary
// string values.  For all but HFRMREG_LOCAL, a MAPI session handle is also
// returned.  The user assumes responsibility of logging off and releasing
// this session.
//
// There are two container types for forms.  The first involves logging
// on to a MAPI session to open the form container that the form will be 
// installed on.  The second is simpler and does not require logging on to a
// MAPI session, but only works for installing local forms.  Both techniques
// are demonstrated below.
//----------------------------------------------------------------------------

HRESULT
HrOpenFormContainer(
	IN	HFRMREG		hFrmReg,            // Desired form registry container
	IN	LPTSTR		lpszProfile,        // Session profile, if needed
	IN	LPTSTR		lpszPassword,       // Session password, if needed
	IN	LPTSTR		lpszMsgStore,       // Message store of folder, if needed
	IN	LPTSTR		lpszFolder,         // Folder name, if needed
	OUT	LPMAPISESSION		*lppMAPISession,    // RETURN: active session
	OUT	LPMAPIFORMCONTAINER	*lppFormContainer)  // RETURN: open folder container
{
	HRESULT				hr				= NOERROR;
	LPMAPIFOLDER		lpFolder		= NULL;
    LPMAPIFORMMGR		lpFormMgr		= NULL;
	LPMAPISESSION		lpMAPISession	= NULL;
	LPMAPIFORMCONTAINER	lpFormContainer	= NULL;

	hr = CHK_HrOpenFormContainer(
		hFrmReg, lpszProfile, lpszPassword, lpszMsgStore, lpszFolder,
		lppMAPISession, lppFormContainer);
	if( FAILED( hr))
		RETURN( hr);
	
    // Initialize return values
    if( lppMAPISession)
        *lppMAPISession = NULL;

    *lppFormContainer = NULL;

    if( hFrmReg == HFRMREG_LOCAL)
    {
	    hr = MAPIOpenLocalFormContainer( &lpFormContainer);
        if( FAILED( hr))
        {
            INTERNAL_ERROR( TEXT("MAPIOpenLocalFormContainer()"), hr);
            goto cleanup;
        }
    }
    else
    {
        ASSERTERROR( lppMAPISession != NULL, "NULL lppMAPISession passed");
    	ASSERTERROR( lpszProfile != NULL, "NULL Profile name");

        hr = MAPILogonEx( 
                NULL, lpszProfile, lpszPassword, 
                MAPI_LOGON_UI | MAPI_NO_MAIL | MAPI_NEW_SESSION, 
                &lpMAPISession);
        if( FAILED( hr))
        {            
            INTERNAL_ERROR( TEXT("MAPILogonEx()"), hr);
            goto cleanup;
        }

        if( hFrmReg == HFRMREG_FOLDER)
        {
        	ASSERTERROR( lpszFolder != NULL, "NULL Folder name");

        	hr = HrOpenMsgStoreFolderByName( lpMAPISession,
        			lpszMsgStore, lpszFolder, &lpFolder);
        	if( hr == EDK_E_NOT_FOUND)
        	{
                TCHAR    szErrorCode[16] = {0};

        		EventLogMsg( INSTFORM_NOTFOUND_ERROR,
        			1, _itot( hr, szErrorCode, 16),
        			0);

        		goto cleanup;
        	}
        	if( FAILED( hr)) {
                INTERNAL_ERROR( TEXT("HrOpenMsgStoreFolderByName()"), hr);
        		goto cleanup;
        	}
        }

        // Open form manager interface.
        hr = MAPIOpenFormMgr( lpMAPISession, &lpFormMgr);
        if( FAILED( hr))
        {
            INTERNAL_ERROR( TEXT("MAPIOpenFormMgr()"), hr);
            goto cleanup;
        }

        // Open appropriate form container.
        hr = lpFormMgr->OpenFormContainer( hFrmReg, lpFolder, &lpFormContainer);
        if( FAILED( hr))
        {
            INTERNAL_ERROR( TEXT("IMAPIFormMgr::OpenFormContainer()"), hr);
            goto cleanup;
        }

        // Success!  Set return interface pointers.
        if( lppMAPISession)
            *lppMAPISession = lpMAPISession;
    }

	*lppFormContainer = lpFormContainer;

cleanup:
	ULRELEASE( lpFolder);
	ULRELEASE( lpFormMgr);

	if( FAILED( hr) && lpMAPISession)
	{
		lpMAPISession->Logoff( 0L, 0L, 0L);
		ULRELEASE( lpMAPISession);
	}

	RETURN( hr);
}

//$--HrSetupAndDoIt()-----------------------------------------------------------
// Open form container interface, and install or remove.
// -----------------------------------------------------------------------------

static HRESULT HrSetupAndDoIt(
    IN CUserParams& UserParams)     // Parsed parameters from the user.
{
    HRESULT				hr 				= NOERROR;
	LPMAPISESSION		lpMAPISession	= NULL;
	LPMAPIFORMCONTAINER	lpFormContainer	= NULL;

    DEBUGPRIVATE( "HrSetupAndDoIt()");

    // Open appropriate form container interface.
    hr = HrOpenFormContainer(
		UserParams.m_hFrmReg,
		UserParams.m_pszProfile, UserParams.m_pszPassword,
		UserParams.m_pszMsgStore, UserParams.m_pszFolder,
		&lpMAPISession, &lpFormContainer);
	if( FAILED( hr))
		goto cleanup;

    if( UserParams.m_fInstall)
    {
		ULONG	ulUIFlags = MAPI_DIALOG;

		// Shouldn't use MAPI_DIALOG flag if installing to local forms registry.
		if( UserParams.m_hFrmReg == HFRMREG_LOCAL)
			ulUIFlags = 0L;

        hr = lpFormContainer->InstallForm( NULL, ulUIFlags, UserParams.m_pszCfgFile);
        if( FAILED( hr))
        {
            if( hr == MAPI_E_USER_CANCEL)
			{
                EventLogMsg( INSTFORM_USER_CANCEL_ERROR,
                	0,
                	0);
            }
            else
            {
                LPMAPIERROR lpMAPIError = NULL;
                HRESULT     hrT = NOERROR;

                hrT = lpFormContainer->GetLastError (hr, 0L, &lpMAPIError);

                if (SUCCEEDED(hrT) && lpMAPIError)
                {
					EventLogMsg( INSTFORM_EXTENDED_ERROR,
						1, lpMAPIError->lpszError,
						0);
                    MAPIFREEBUFFER (lpMAPIError);
                }

                INTERNAL_ERROR( TEXT("IMAPIFormContainer::InstallForm()"), hr);

                hr = HR_LOG( E_FAIL);
			}
        }
    }
    else
    {
        hr = lpFormContainer->RemoveForm( UserParams.m_pszMsgClass);
        if( FAILED( hr) || hr == MAPI_W_PARTIAL_COMPLETION)
        {
            if( hr == MAPI_E_NOT_FOUND)
			{
                EventLogMsg( INSTFORM_FORM_NOT_FOUND_ERROR,
                	1, UserParams.m_pszMsgClass,
                	0);
            }
            else
			{
                LPMAPIERROR lpMAPIError = NULL;
                HRESULT     hrT = NOERROR;

                hrT = lpFormContainer->GetLastError (hr, 0L, &lpMAPIError);

                if (SUCCEEDED(hrT) && lpMAPIError)
                {
					EventLogMsg( INSTFORM_EXTENDED_ERROR,
						1, lpMAPIError->lpszError,
						0);
                    MAPIFREEBUFFER (lpMAPIError);
                }

                INTERNAL_ERROR( TEXT("IMAPIFormContainer::RemoveForm()"), hr);

                hr = HR_LOG( E_FAIL);
			}
        }
    }

cleanup:
	ULRELEASE( lpFormContainer);

	if( lpMAPISession)
	{
		lpMAPISession->Logoff( 0L, 0L, 0L);
		ULRELEASE( lpMAPISession);
	}

    RETURN( hr);
}

//$--main()---------------------------------------------------------------------
// See CUserParams::PrintUsage() for user parameters.
// -----------------------------------------------------------------------------

int main( int argc, char *argv[])
{
    HRESULT		hr				 = NOERROR;
	BOOL		fMAPIInitialized = FALSE;
	BOOL		fEventLogOpen	 = FALSE;

    CUserParams UserParams;

    DEBUGPUBLIC( "main()");

	// Parse the user's parameters.
    hr = UserParams.HrParseCommandLine( argc, argv);
    if( hr == EXIT_WARNING || FAILED( hr))
        goto cleanup;

    // Initialize MAPI.
    hr = MAPIInitialize( NULL);
    if( FAILED( hr))
        goto cleanup;
    
    fMAPIInitialized = TRUE;

    // Open an event logging handle for this application.
    hr = HrEventOpenLog(
        lpszAppName,	// application name
        NULL,			// executable name (computed)
        NULL,			// event message file (computed)
        NULL,			// parameter message file (this)
        NULL,			// category message file (this)
        NULL);			// event logging handle
    if( FAILED(hr))
    {
        fprintf( stderr, "ERROR: unable to open event log.\n");
        goto cleanup;
	}

	fEventLogOpen = TRUE;

    hr = HrSetupAndDoIt( UserParams);
    if( FAILED( hr))
    {
        printf( "FAILURE! Could not %s form.\n", UserParams.m_fInstall ? "install" : "remove");
        goto cleanup;
    }

    printf( "Form %s successfully.\n", UserParams.m_fInstall ? "installed" : "removed");

cleanup:

	if( fEventLogOpen)
	{
	    EDKEVENTCOUNT   sEventCount     = {0};
        HRESULT			hrT				= NOERROR;

        hrT = HrEventGetCounts(&sEventCount);
        if( SUCCEEDED( hrT)) 
        {
            // Print the number of errors logged.
            if (sEventCount.cError == 1)
                fprintf(stderr, "ERROR: 1 error written to NT event log.\n");
            else if (sEventCount.cError > 1)
                fprintf(stderr, "ERROR: %d errors written to NT event log.\n", 
                    sEventCount.cError);

            // Print the number of warnings logged.
            if (sEventCount.cWarning == 1)
                fprintf(stderr, "WARNING: 1 warning written to NT event log.\n");
            else if (sEventCount.cWarning > 1)
                fprintf(stderr, "WARNING: %d warnings written to NT event log.\n", 
                    sEventCount.cWarning);
        }
		else
		{
            fprintf(stderr, "WARNING: unable to get number of errors logged.\n");
        }

		(void)HrEventCloseLog();
    }

	if( fMAPIInitialized)
		MAPIUninitialize();

    return( _nEcFromHr(hr));
}

// -----------------------------------------------------------------------------
