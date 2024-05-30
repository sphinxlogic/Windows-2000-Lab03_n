'====================================================================
'                                                                     
'   Microsoft Site Server v3.00                                   
'                                                                     
'   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
'   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
'   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
'   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'   PARTICULAR PURPOSE.
'=====================================================================

''''''''''''''''''''''''''''''''''''
'
' CRSTOOL.VBS
'
''''''''''''''''''''''''''''''''''''
	Option Explicit
	On Error Resume Next



	' Global Constants

	Const NOERROR = 0
	Const E_FAIL = &h80004005
	Const GENERAL_FAILURE = 2
	Const GENERAL_WARNING = 1

	'Global Registry Constants
	Const READ_CONTROL = &H20000
	Const KEY_QUERY_VALUE = &H1
	Const KEY_SET_VALUE = &H2
	Const KEY_CREATE_SUB_KEY = &H4
	Const KEY_ENUMERATE_SUB_KEYS = &H8
	Const KEY_NOTIFY = &H10
	Const SYNCHRONIZE = &H100000
	Const STANDARD_RIGHTS_ALL = &H1F0000

	Dim STANDARD_RIGHTS_READ
	Dim KEY_READ
	Dim KEY_ALL_ACCESS
	STANDARD_RIGHTS_READ = (READ_CONTROL)
	KEY_READ = ((STANDARD_RIGHTS_READ Or KEY_QUERY_VALUE Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY) And (Not SYNCHRONIZE))
	KEY_ALL_ACCESS = ((STANDARD_RIGHTS_ALL Or KEY_QUERY_VALUE Or KEY_SET_VALUE Or KEY_CREATE_SUB_KEY Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY Or KEY_CREATE_LINK) And (Not SYNCHRONIZE))


	Const KEY_CREATE_LINK = &H20

	' Global CRS Constants
	Const CREATE_NEW_PROJECT = &h1
	Const OPEN_EXISTING_PROJECT = &h2

	Dim CRS_ADMIN_ACCESS
	Dim CRS_USER_ACCESS
	CRS_ADMIN_ACCESS = (KEY_ALL_ACCESS Or READ_CONTROL)
	CRS_USER_ACCESS = (KEY_READ)

	Const STAGER = &h1
	Const ENDPOINT = &h2

	' Global CRS Replication Flags
	Const RF_NO_DELETE			= &h00000001		
	Const RF_REPLICATE_ACLS		= &h00000002	
	Const RF_NO_DATA			= &h00000004	
	Const RF_FORCE_REPL			= &h00000008	
	Const RF_PERMIT_TREE		= &h00000010
	Const RF_IN_PROC			= &h00000020
	Const RF_INCREMENTAL		= &h00000040	
	Const RF_FASTMODE			= &h00000080
	Const RF_ON_DIR_CHANGE		= &h00000100
	Const RF_AUTO_ROUTE			= &h00000200
	Const RF_ON_NOTIFY			= &h00000400
	Const RF_NO_CHAIN			= &h00000800
	Const RF_EXCLUDE_ALL		= &h00001000
	Const RF_UNINSTALL			= &h00002000
	Const RF_ACLS_ONLY			= &h00004000

	Const RF_DELETE				= &h00008000
	Const RF_NO_REPLICATE_ACLS  = &h00010000
	Const RF_DATA				= &h00020000	
	Const RF_NO_FORCE_REPL		= &h00040000	
	Const RF_NO_PERMIT_TREE		= &h00080000
	Const RF_NO_IN_PROC			= &h00100000
	Const RF_NO_INCREMENTAL		= &h00200000	
	Const RF_NO_FASTMODE		= &h00400000
	Const RF_NO_ON_DIR_CHANGE	= &h00800000
	Const RF_NO_AUTO_ROUTE		= &h01000000
	Const RF_NO_ON_NOTIFY       = &h02000000
	Const RF_CHAIN				= &h04000000
	Const RF_NO_ACLS_ONLY		= &h08000000


	Const REPL_STATE_EMPTY	   = &h0  
	Const REPL_STATE_STARTING  = &h1
	Const REPL_STATE_RUNNING   = &h2
	Const REPL_STATE_COMPLETE  = &h3
	Const REPL_STATE_ABORTED   = &h4
	Const REPL_STATE_CANCELED  = &h5
	Const REPL_STATE_RECEIVING = &h6
	Const REPL_STATE_PENDING   = &h7
	Const REPL_STATE_PARTIAL   = &h8


	' Global CRS Error Constants

	Const CRS_ERROR_SERVICE_ALREADY_RUNNING = &hC0003B0D
	Const CRS_ERROR_SERVICE_NOT_RUNNING = &hC0003B02
	Const CRS_ERROR_NO_PROJECTS = &hC0003AFC
	Const CRS_ERROR_ROUTE_NOT_FOUND = &hC0003B05
	Const CRS_ERROR_NO_ROUTES = &hC0003B06
	Const CRS_ERROR_REPLICATION_NOT_FOUND = &hC0003B0C
	Const CRS_ERROR_NO_MORE_ITEMS = &h80003B17
	Const CRS_ERROR_NO_MAPPING = &hC0003B27

	' Global command line parameters
	Const HELP_		= "help"
	Const HELP_SHORT_	= "/?"

	Const DELPROJ_ALL_	= "delproj_all"
	Const DELROUTE_ALL_	= "delroute_all"
	Const QUERYREP_		= "queryrep"
	Const REPORT_		= "report"
	Const LISTITEMS_	= "listitems"
	Const LISTPA_		= "listpa"
	Const SETPA_		= "setpa"
	Const GETPA_		= "getpa"
	Const LISTEVENTSINKS_	= "listeventsinks"
	Const LISTSERVERS_	= "listservers"
	Const LISTVERSION_	= "listversion"
	Const LISTUSER_		= "listuser"
	Const CHECKUSER_	= "checkuser"
	Const MAPURL2PROJ_	= "mapurl2proj"
	Const XLATEEVENT_	= "xlateevent"
	Const CLEAREVENTSINK_	= "cleareventsink"
	Const SENDFILE_		= "sendfile"
	Const SENDFILES_	= "sendfiles"
	Const DELETEFILE_	= "deletefile"
	Const STARTREP_		= "startrep"
	Const DEPLOY_		= "deploy"

	' Global command line options
	Const DEFAULTSERVER_		= "/server"
	Const DEFAULTSERVER_SHORT_	= "/srv"
	Const USERNAME_			= "/username"
	Const USERNAME_SHORT_		= "/u"
	Const PASSWORD_			= "/password"
	Const PASSWORD_SHORT_		= "/p"
	Const RECURSE_DIRECTORIES_OPTION_	= "/r"

	'
	' Global API reference strings
	'
	' Generic COM
	const g_szQueryInterface			= "QueryInterface"
	const g_szCoInitialize				= "CoInitialize"
	const g_szCoCreateInstance			= "CoCreateInstance"


	' CRS Properties
	const g_szComments				= "Comments"
	' Specific to IReplicationServer
	const g_szIReplicationServer			= "IReplicationServer"
	const g_szAddRoute				= "AddRoute"
	const g_szCheckAccess			= "CheckAccess"
	const g_szClearEvents			= "ClearEvents"
	const g_szCommit					= "Commit"
	const g_szContinue				= "Continue"
	const g_szDeleteProject			= "DeleteProject"
	const g_szDeleteRoute			= "DeleteRoute"
	const g_szEnumEventSinks			= "EnumEventSinks"
	const g_szEnumItems				= "EnumItems"
	const g_szEnumProjects			= "EnumProjects"
	const g_szEnumReplications		= "EnumReplications"
	const g_szEnumRoutes				= "EnumRoutes"
	const g_szEnumServers			= "EnumServers"
	const g_szGet					= "Get"
	const g_szget_ServerName			= "get_ServerName"
	const g_szget_UseTransactions	= "get_UseTransactions"
	const g_szGrantAccess			= "GrantAccess"
	const g_szInitialize				= "Initialize"
	const g_szLockTransactions		= "LockTransactions"
	const g_szMapUrl					= "MapUrl"
	const g_szOpenProject			= "OpenProject"
	const g_szOpenPostingAcceptor	= "OpenPostingAcceptor"
	const g_szPause					= "Pause"
	const g_szPut					= "Put"
	const g_szput_UseTransactions	= "put_UseTransactions"
	const g_szRemoveAccess			= "RemoveAccess"
	const g_szStart					= "Start"
	const g_szStop					= "Stop"
	const g_szTranslateEventCode		= "TranslateEventCode"
	const g_szUnlockTransactions		= "UnlockTransactions"


	' Specific to IReplicationProject
	const g_szIReplicationProject		= "IReplicationProject"
	const g_szAddDestination			= "AddDestination"
	const g_szCancel					= "Cancel"
	' NOTE: g_szCommit defined in IReplicationServer
	const g_szEnum					= "Enum"
	const g_szEnumAccess				= "EnumAccess"
	const g_szEnumDestination		= "EnumDestination"
	' NOTE: g_szEnumReplications defined in IReplicationServer
	' NOTE: g_szGet defined in IReplicationServer
	const g_szget_Flags				= "get_Flags"
	const g_szget_LocalDirectory	= "get_LocalDirectory"
	const g_szget_Name				= "get_Name"
	const g_szget_ReplicationMethod	= "get_ReplicationMethod"
	' NOTE: g_szGrantAccess defined in IReplicationServer
	' NOTE: g_szLockTransactions defined in IReplicationServer
	' NOTE: g_szPut defined in IReplicationServer
	const g_szput_Flags				= "put_Flags"
	const g_szput_LocalDirectory		= "put_LocalDirectory"
	const g_szput_Name				= "put_Name"
	const g_szput_ReplicationMethod	= "put_ReplicationMethod"
	' NOTE: g_szRemoveAccess defined in IReplicationServer
	const g_szRemoveDestination		= "RemoveDestination"
	const g_szRollback				= "Rollback"
	const g_szRollbackToTime			= "RollbackToTime"
	const g_szSchedule				= "Schedule"
	' NOTE: g_szStart defined in IReplicationServer
	const g_szStartReplicationClient	= "StartReplicationClient"
	' NOTE: g_szUnlockTransactions defined in IReplicationServer


	' Specific to IReplicationInstance
	const g_szIReplicationInstance		= "IReplicationInstance"
	const g_szget_BytesReceived		= "get_BytesReceived"
	const g_szget_BytesSent			= "get_BytesSent"
	const g_szget_EndTime			= "get_EndTime"
	const g_szget_FilesErrored		= "get_FilesErrored"
	const g_szget_FilesErroredBytes	= "get_FilesErroredBytes"
	const g_szget_FilesMatched		= "get_FilesMatched"
	const g_szget_FilesMatchedBytes	= "get_FilesMatchedBytes"
	const g_szget_FilesReceived		= "get_FilesReceived"
	const g_szget_FilesSent			= "get_FilesSent"
	' NOTE: g_szget_Flags defined in IReplicationProject
	const g_szget_ID				= "get_ID"
	const g_szget_StartTime			= "get_StartTime"
	const g_szget_State				= "get_State"
	const g_szget_Status			= "get_Status"

	' Specific to IReplicationRoute
	const g_szIReplicationRoute			= "IReplicationRoute"

	' Specific to IReplicationEventSinkConfig
	const g_szIReplicationEventSinkConfig	= "IReplicationEventSinkConfig"

	' Specific to IReplicationItem
	const g_szIReplicationItem			= "IReplicationItem"
	' NOTE: g_szget_Name defined in IReplicationProject
	const g_szget_Attributes				= "get_Attributes"
	'const g_szget_Storage					= "get_Storage"
	const g_szget_CreationTime				= "get_CreationTime"
	const g_szget_LastAccessTime			= "get_LastAccessTime"
	const g_szget_LastModifiedTime			= "get_LastModifiedTime"
	const g_szget_SizeLow					= "get_SizeLow"
	const g_szget_SizeHigh					= "get_SizeHigh"

	' Specific to IReplicationPostingAcceptor
	const g_szIReplicationPostingAcceptor	= "IReplicationPostingAcceptor"

	' Specific to IReplicationClient
	const g_szIReplicationClient			= "IReplicationClient"
	const g_szAbort						= "Abort"
	const g_szConnect					= "Connect"
	const g_szDeleteFile				= "DeleteFile"
	const g_szDisconnect				= "Disconnect"
	const g_szGetExtendedErrorInfo		= "GetExtendedErrorInfo"
	const g_szget_FastMode				= "get_FastMode"
	const g_szget_Force					= "get_Force"
	const g_szget_ACLs					= "get_ACLs"
	const g_szget_NumDestinations		= "get_NumDestinations"
	const g_szget_SkipLockedFiles		= "get_SkipLockedFiles"
	const g_szput_FastMode				= "put_FastMode"
	const g_szput_Force					= "put_Force"
	const g_szput_ACLs					= "put_ACLs"
	const g_szput_SkipLockedFiles		= "put_SkipLockedFiles"
	const g_szSendFile					= "SendFile"
	const g_szSendFiles					= "SendFiles"

	' Specific to IReplicationClientError
	const g_szIReplicationClientError		= "IReplicationClientError"
	const g_szget_ErrorCode				= "get_ErrorCode"
	const g_szput_ErrorCode				= "put_ErrorCode"
	const g_szget_Description			= "get_Description"
	const g_szput_Description			= "put_Description"
	const g_szget_Destination			= "get_Destination"
	const g_szput_Destination			= "put_Destination"
	const g_szget_FileName				= "get_FileName"
	const g_szput_FileName				= "put_FileName"
	const g_szget_Project				= "get_Project"
	const g_szput_Project				= "put_Project"
	const g_szget_Source				= "get_Source"
	const g_szput_Source				= "put_Source"


	' Global Variables
	Dim gszProjectName
	Dim gszDirectory
	Dim gszPropertyName
	Dim gszPropertyValue
	Dim gszUrl
	Dim glEventCode
	Dim gszEventSink
	Dim gszFilename
	Dim gpszFilenames
	Dim gcFilenames
	Dim gszUsername
	Dim gszDefaultServerName
	Dim gszCRSUsername
	Dim gszCRSPassword
	Dim gfRecurseDirectories
	Dim g_iMethod
	Dim fDebug

	fDebug = FALSE ' Set to True to output debug strings
	
	gszDefaultServerName = vbNullString
	gszCRSUserName = vbNullString
	gszCRSPassword = vbNullString

''''''''''''''''''
' Main Script Code
''''''''''''''''''
	' Local Main variables
	Dim ArgObj ' Object which contains the command line argument
	Dim hr     ' Result of the command function call
	Dim pIServer ' ReplicationServer object

	hr = NOERROR
	gfRecurseDirectories = False

	' Get the Arguments object
	Set ArgObj = WScript.Arguments

	' Test to make sure there is at least one command line arg - the command
	If ArgObj.Count < 1 Then
        	DisplayHelpMessage
        	WScript.Quit (GENERAL_FAILURE)
	End If

	' Parse command line and assign values to global variables
	AssignCmdLineGlobals(ArgObj)

if (fDebug) then DebugPrintCmdLineGlobals

	Set pIServer = WScript.CreateObject("Crsapi.ReplicationServer")

	call pIServer.InitializeEx(gszDefaultServerName, gszCRSUserName, gszCRSPassword, 0)
	hr = Err.Number
	if (hr <> 0 And (CRS_ERROR_SERVICE_NOT_RUNNING <> hr)) then

		Err.Clear
 		call PrintAPIError(g_szIReplicationServer, g_szInitialize, vbNullString, gszDefaultServerName, hr)
        WScript.Quit (hr)

	elseif (CRS_ERROR_SERVICE_NOT_RUNNING = hr) then

		Err.Clear
		' This is separated only so we can easily comment out this section
		'   and try calling APIs when Initialize failed due to a stopped service
		call PrintAPIError(g_szIReplicationServer, g_szInitialize, vbNullString, gszDefaultServerName, hr)
        WScript.Quit (hr)

	end if

	Select Case LCase(g_iMethod)
	
		case "delproj_all"
			DeleteAllProjects(pIServer)
			
		case "delroute_all"
			DeleteAllRoutes(pIServer)
			
		case "queryrep"
			call QueryRep(pIServer, gszProjectName)
					
		case "listitems"
			call ListItems(pIServer, gszProjectName, gszDirectory)
			
		case "listpa"
			ListPostingAcceptor(pIServer)
			
		case "setpa"
			SetPostingAcceptor(pIServer)
			
		case "getpa"
			GetPostingAcceptor(pIServer)
			
		case "listeventsinks"
			ListEventSinks(pIServer)
			
		case "listservers"
			ListServers(pIServer)
			
		case "listversion"
			ListVersion(pIServer)
			
		case "listuser"
			call ListUser(pIServer, gszProjectName)
			
		case "checkuser"
			CheckUser(pIServer)
			
		case "checkuserproject"
			call CheckUserProject(pIServer, gszProjectName)
			
		case "mapurl2proj"
			call MapURL2Proj(pIServer, gszURL)
			
		case "xlateevent"
			call TranslateEvent(pIServer, glEventCode)
			
		case "cleareventsink"
			call ClearEventSink(pIServer, gszEventSink)
			
		case "sendfile"
			call SendFile(pIServer, gszProjectName, gszFileName)
			
		case "sendfiles"
			call SendFiles(pIServer, gszProjectName, gpszFileNames, gcFileNames)
			
		case "deletefile"
			call DeleteFile(pIServer, gszProjectName, gszFileName)

		case "startrep"
			call StartRep(pIServer, gszProjectName)
			
		case else
			WScript.Echo "ERROR: Unrecognized parameter"
			WScript.Echo
			WScript.Echo
			DisplayHelpMessage
			
	End Select

	Set pIServer = Nothing

WScript.Quit (hr)

''''''''''
' End Main
''''''''''

Sub DebugPrintCmdLineGlobals
	WScript.Echo "DEBUG: g_iMethod            = " & g_iMethod
	WScript.Echo "DEBUG: gszProjectName       = " & gszProjectName
	WScript.Echo "DEBUG: gszDirectory         = " & gszDirectory
	WScript.Echo "DEBUG: gszPropertyName      = " & gszPropertyName
	WScript.Echo "DEBUG: gszPropertyValue     = " & gszPropertyValue
	WScript.Echo "DEBUG: gszUrl               = " & gszUrl
	WScript.Echo "DEBUG: glEventCode          = " & glEventCode
	WScript.Echo "DEBUG: gszEventSink         = " & gszEventSink
	WScript.Echo "DEBUG: gszFilename          = " & gszFilename
	WScript.Echo "DEBUG: gpszFilenames        = " & gpszFilenames
	WScript.Echo "DEBUG: gcFilenames          = " & gcFilenames
	WScript.Echo "DEBUG: gszUsername          = " & gszUsername
	WScript.Echo "DEBUG: gszDefaultServerName = " & gszDefaultServerName
	WScript.Echo "DEBUG: gszCRSUsername       = " & gszCRSUsername
	WScript.Echo "DEBUG: gszCRSPassword       = " & gszCRSPassword
	WScript.Echo "DEBUG: gfRecurseDirectories = " & gfRecurseDirectories
End Sub
''''''''''''''''''''''''''''
'
' Display Help Message
'
''''''''''''''''''''''''''''
Sub DisplayHelpMessage()

	WScript.Echo "Name"
	WScript.Echo "  crstool - Content Deployment SDK Test Tool"
	WScript.Echo
	WScript.Echo "Syntax"
	WScript.Echo "  cscript crstool.vbs [parameter] [option(s)]"
	WScript.Echo
	WScript.Echo "Description"
	WScript.Echo "  Shows usage of APIs in the Content Deployment SDK."
	WScript.Echo
	WScript.Echo
	WScript.Echo "Parameters:"
	WScript.Echo
	WScript.Echo "   help                           Displays this usage information"
	WScript.Echo "   /?                             Equivalent to help parameter"
	WScript.Echo "   delproj_all                    Deletes all projects"
	WScript.Echo "   delroute_all                   Deletes all routes"
	WScript.Echo "   queryrep <project_name>        Lists in detail all replications for a project"
	WScript.Echo "   listitems <project_name> [/r]  Lists in detail all items for a project"
	WScript.Echo "   listpa                         Lists all Posting Acceptor properties and"
	WScript.Echo "                                    values"
	WScript.Echo "   getpa <property>               Gets the value of a Posting Acceptor property"
	WScript.Echo "   setpa <property=value>         Sets the value of a Posting Acceptor property"
	WScript.Echo "   listservers                    Lists all servers associated with projects"
	WScript.Echo "   listeventsinks                 Lists all event sinks and their properties"
	WScript.Echo "   listuser <project_name>        Lists all users and their access permissions"
	WScript.Echo "   checkuser [<project_name>]     Lists access permissions for local user"
	WScript.Echo "   mapurl2proj <url>              Lists all projects this url maps to"
	WScript.Echo "   xlateevent <event_code>        Displays description + severity + category"
	WScript.Echo "                                    for given event code"
	WScript.Echo "   cleareventsink <event_sink>    Clear events in the event sink"
	WScript.Echo "   listversion                    Displays CRS version number"
	WScript.Echo "   sendfile <project_name> <filename>    Sends one file"
	WScript.Echo "   sendfiles <project_name> ""<file1> <file2>...""  Sends one or more files"
	WScript.Echo "   deletefile <project_name> <filename>  Deletes one file"
	WScript.Echo "   startrep <project_name>        Starts project replication"
	WScript.Echo
	WScript.Echo "Options:"
	WScript.Echo "   /server <servername>           Specifies which server to run the command on"
	WScript.Echo "   /username <username>           Specifies CRS authentication account"
	WScript.Echo "   /password <password>           Specifies CRS authentication account password"

	WScript.Echo "   /r                             Recurse all items for listitems"
	WScript.Echo


End Sub


''''''''''''''''''''''''''''
'
' Assign command line globals
'
''''''''''''''''''''''''''''
Sub AssignCmdLineGlobals(ArgObj)

if (fDebug) then WScript.Echo "DEBUG: AssignCmdLineGlobals"
On Error Resume Next
	Dim i

	for i = 0 to ArgObj.Count - 1

		if (StrComp(ArgObj.Item(i), HELP_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), HELP_SHORT_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: help"
			DisplayHelpMessage
			WScript.Quit (NOERROR)

		elseif (StrComp(ArgObj.Item(i), LISTITEMS_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: listitems"		
			g_iMethod = "listitems"

			gszProjectName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then
	
				gszProjectName = ArgObj.Item(i)

				i = i + 1

				if (i < ArgObj.Count) then	' not a required parameter

					if (StrComp(ArgObj.Item(i), RECURSE_DIRECTORIES_OPTION_, vbTextCompare) = 0) then

						gfRecurseDirectories = TRUE

					elseif (StrComp(ArgObj.Item(i), DEFAULTSERVER_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), DEFAULTSERVER_SHORT_, vbTextCompare) = 0) then

						' We want to parse the /server option down below, not here
						i = i - 1

					else

						gszDirectory = ArgObj.Item(i)

						if (StrComp(ArgObj.Item(i), RECURSE_DIRECTORIES_OPTION_, vbTextCompare) = 0) then

							gfRecurseDirectories = TRUE

						end if

					end if

				end if
			
			else

				WScript.Echo "ERROR: " & LISTITEMS_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), DELPROJ_ALL_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: delproj_all"
			g_iMethod = "delproj_all"

		elseif (StrComp(ArgObj.Item(i), DELROUTE_ALL_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: delroute_all"
			g_iMethod = "delroute_all"

		elseif ((StrComp(ArgObj.Item(i), QUERYREP_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), REPORT_, vbTextCompare) = 0)) then
if (fDebug) then WScript.Echo "DEBUG: queryrep"
			g_iMethod = "queryrep"

			gszProjectName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszProjectName = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & QUERYREP_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), LISTPA_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: listpa"
			g_iMethod = "listpa"

		elseif (StrComp(ArgObj.Item(i), GETPA_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: getpa"
			g_iMethod = "getpa"

			gszProjectName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszPropertyName = ArgObj.Item(i)

				if (StrComp(gszPropertyName, "<NULL>", vbTextCompare) = 0) then

					gszPropertyName = CStr(Chr(0)) ' Null char

				end if

			else

				WScript.Echo "ERROR: " & GETPA_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), SETPA_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: setpa"
			g_iMethod = "setpa"

			gszProjectName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				' PropertyName=PropertyValue
				''gszPropertyName = QAStringNew(_tcstok(ArgObj.Item(i), _T("="))
				if (StrComp(gszPropertyName, "<NULL>") =0) then

					gszPropertyName = CStr(Chr(0))

				end if

				''gszPropertyValue = QAStringNew(_tcstok(NULL, _T(""))
				if (StrComp(gszPropertyValue, "<NULL>") = 0) then

					gszPropertyValue = CStr(Chr(0))

				end if

			else

				WScript.Echo "ERROR: " & SETPA_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), LISTEVENTSINKS_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: listeventsinks"
			g_iMethod = "listeventsinks"

		elseif (StrComp(ArgObj.Item(i), LISTSERVERS_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: listservers"
			g_iMethod = "listservers"

		elseif (StrComp(ArgObj.Item(i), LISTVERSION_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: listversion"
			g_iMethod = "listversion"

		elseif (StrComp(ArgObj.Item(i), LISTUSER_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: listuser"
			g_iMethod = "listuser"

			gszProjectName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszProjectName = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & LISTUSER_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), CHECKUSER_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: checkuser"
			g_iMethod = "checkuser"

			' If the next parameter is /server, don't assign project name
			' The project parameter is not required
			if ((i + 1) < ArgObj.Count) then

				if (Not((StrComp(ArgObj.Item(i+1), DEFAULTSERVER_) = 0) Or (StrComp(ArgObj.Item(i+1), DEFAULTSERVER_SHORT_, vbTextCompare) = 0))) then

					i = i + 1

					' Optional parameter on a per-project basis
					if (i < ArgObj.Count) then

						gszProjectName = ArgObj.Item(i)
						g_iMethod = "checkuserproject"

					end if

				end if

			end if

		elseif (StrComp(ArgObj.Item(i), DEFAULTSERVER_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), DEFAULTSERVER_SHORT_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: defaultserver"
			gszDefaultServerName = vbNullChar

			i = i + 1

			if (i < ArgObj.Count) then

				gszDefaultServerName = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & DEFAULTSERVER_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), USERNAME_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), USERNAME_SHORT_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: username"
			gszCRSUserName = vbNullChar

			i = i + 1

			if (i < ArgObj.Count) then

				gszCRSUserName = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & USERNAME_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), PASSWORD_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), PASSWORD_SHORT_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: password"
			gszCRSPassword = vbNullChar

			i = i + 1

			if (i < ArgObj.Count) then

				gszCRSPassword = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & PASSWORD_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), MAPURL2PROJ_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: mapurl2proj"		
			g_iMethod = "mapurl2proj"

			gszURL = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszURL = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & MAPURL2PROJ_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), XLATEEVENT_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: xlateevent"		
			g_iMethod = "xlateevent"

			i = i + 1

			if (i < ArgObj.Count) then

					glEventCode = CLng(ArgObj.Item(i))

			else

				WScript.Echo "ERROR: " & XLATEEVENT_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), CLEAREVENTSINK_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: cleareventsink"
			g_iMethod = "cleareventsink"

			gszEventSink = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszEventSink = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & CLEAREVENTSINK_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)
			end if

		elseif (StrComp(ArgObj.Item(i), SENDFILE_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: sendfile"
			g_iMethod = "sendfile"

			gszFileName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszProjectName = ArgObj.Item(i)

				i = i + 1

				if (i < ArgObj.Count) then

						gszFileName = ArgObj.Item(i)

				else

					WScript.Echo "ERROR: " & SENDFILE_ & " option invalid"
					WScript.Echo
					WScript.Echo
					DisplayHelpMessage
					WScript.Quit (GENERAL_FAILURE)
				end if

			else

				WScript.Echo "ERROR: " & SENDFILE_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)
			end if

		elseif (StrComp(ArgObj.Item(i), SENDFILES_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: sendfiles"
			g_iMethod = "sendfiles"

			gszFileName = vbNullString

			if (i < ArgObj.Count) then

				gszProjectName = ArgObj.Item(i)

				i = i + 1

				if (i < ArgObj.Count) then

					''gpszFileNames = QAParseTokens(ArgObj.Item(i), &gcFileNames

				else

					WScript.Echo "ERROR: " & SENDFILES_ & " option invalid"
					WScript.Echo
					WScript.Echo
					DisplayHelpMessage
					WScript.Quit (GENERAL_FAILURE)
				end if

			else

				WScript.Echo "ERROR: " & SENDFILES_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif (StrComp(ArgObj.Item(i), DELETEFILE_, vbTextCompare) = 0) then
if (fDebug) then WScript.Echo "DEBUG: deletefile"
			g_iMethod = "deletefile"

			gszFileName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszProjectName = ArgObj.Item(i)

				i = i + 1

				if (i < ArgObj.Count) then

						gszFileName = ArgObj.Item(i)

				else

					WScript.Echo "ERROR: " & DELETEFILE_ & " option invalid"
					WScript.Echo
					WScript.Echo
					DisplayHelpMessage
					WScript.Quit (GENERAL_FAILURE)

				end if

			else
			
				WScript.Echo "ERROR: " & DELETEFILE_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		elseif ((StrComp(ArgObj.Item(i), STARTREP_, vbTextCompare) = 0) Or (StrComp(ArgObj.Item(i), DEPLOY_, vbTextCompare) = 0)) then
if (fDebug) then WScript.Echo "DEBUG: startrep"
			g_iMethod = "startrep"

			gszProjectName = vbNullString

			i = i + 1

			if (i < ArgObj.Count) then

				gszProjectName = ArgObj.Item(i)

			else

				WScript.Echo "ERROR: " & STARTREP_ & " option invalid"
				WScript.Echo
				WScript.Echo
				DisplayHelpMessage
				WScript.Quit (GENERAL_FAILURE)

			end if

		else

			WScript.Echo "ERROR: unknown option """ & ArgObj.Item(i) & """ specified"
			WScript.Echo
			WScript.Echo
			DisplayHelpMessage
			WScript.Quit (GENERAL_FAILURE)

		end if

	next

End Sub


''''''''''''''''''''''''''''
'
' Helper routines
'
''''''''''''''''''''''''''''
Sub PrintAPIError(ByVal szClassName, ByVal szMethod, ByVal szProperty, ByVal szLabel, ByVal hr)

if (fDebug) then WScript.Echo "DEBUG: Sub PrintAPIError"
	if (szLabel <> vbNullString) then

		' For Get() and Put() methods
		if (szProperty <> vbNullString) then

   			WScript.Echo "ERROR: " & szClassName & "::" & szMethod & "(""" & szProperty & """) failed with return code 0x" & Hex(hr) & " [" & szLabel & "]"

		else

   			WScript.Echo "ERROR: " & szClassName & "::" & szMethod & " failed with return code 0x" & Hex(hr) & " [" & szLabel & "]"

		end if

	else

		' For Get() and Put() methods
		if (szProperty <> vbNullString) then

   			WScript.Echo "ERROR: " & szClassName & "::" & szMethod & "(""" & szProperty & """) failed with return code 0x" & Hex(hr)

		else

   			WScript.Echo "ERROR: " & szClassName & "::" & szMethod & " failed with return code 0x" & Hex(hr)

		end if

	end if

End Sub


''''''''''''''''''''''''''''
'
' Handler routines
'
''''''''''''''''''''''''''''	

Sub DeleteAllProjects(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub DeleteAllProjects"
	On Error Resume Next

	Dim cProjects
	Dim hr
	Dim pIProject
	Dim vIterator

	cProjects = 0
	hr = NOERROR
	vIterator = CLng(0)

	do while (True)

		Set pIProject = pIServer.EnumProjects(vIterator)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear

			if ((CRS_ERROR_NO_MORE_ITEMS <> hr) And (CRS_ERROR_NO_PROJECTS <> hr)) then

   				call PrintAPIError(g_szIReplicationServer, g_szEnumProjects, vbNullString, vbNullString, hr)

			elseif ((CRS_ERROR_NO_PROJECTS = hr) Or ((0 = cProjects) And (CRS_ERROR_NO_MORE_ITEMS = hr))) then

				WScript.Echo "No projects found."

			end if

			exit do

		end if

		cProjects = cProjects + 1

		Dim szProjectName

		szProjectName = pIProject.Name
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationProject, g_szget_Name, vbNullString, vbNullString, hr)
			exit do

		end if

		WScript.Echo "Deleting project " & szProjectName & "..."

		'
		' Print out any other project info here
		'

		pIServer.DeleteProject(szProjectName)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationServer, g_szDeleteProject, vbNullString, vbNullString, hr)
			exit do

		end if

		Set pIProject = Nothing

	loop

End Sub	


Sub DeleteAllRoutes(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub DeleteAllRoutes"
	On Error Resume Next


	Dim cRoutes
	Dim hr
	Dim pIRoute
	Dim vIterator

	cRoutes = 0
	hr = NOERROR
	vIterator = CLng(0)

	do while (True)

		Set pIRoute = pIServer.EnumRoutes(vIterator)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear

			if ((CRS_ERROR_NO_MORE_ITEMS <> hr) And (CRS_ERROR_NO_ROUTES <> hr)) then

   				call PrintAPIError(g_szIReplicationServer, g_szEnumRoutes, vbNullString, vbNullString, hr)

			elseif ((CRS_ERROR_NO_ROUTES = hr) Or ((0 = cRoutes) And (CRS_ERROR_NO_MORE_ITEMS = hr))) then

				WScript.Echo "No routes found."

			end if

			exit do

		end if

		cRoutes = cRoutes + 1

		Dim szRouteName

		szRouteName = pIRoute.Name
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationRoute, g_szget_Name, vbNullString, vbNullString, hr)
			exit do

		end if

		WScript.Echo "Deleting route " & szRouteName & "..."

		'
		' Print out any other project info here
		'

		pIServer.DeleteRoute(szRouteName)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationServer, g_szDeleteRoute, vbNullString, vbNullString, hr)
			exit do

		end if

		Set pIRoute = Nothing

	loop

End Sub		

Sub QueryRep(pIServer, szProjectName)

if (fDebug) then WScript.Echo "DEBUG: Sub QueryRep"
	On Error Resume Next

	Dim cReplications
	Dim hr
	Dim pIReplicationInstance
	Dim vIterator
	Dim ul64BytesReceived
	Dim ul64BytesSent
	Dim lFilesErrored
	Dim ul64FilesErroredBytes
	Dim lFilesMatched
	Dim ul64FilesMatchedBytes
	Dim lFilesReceived
	Dim lFilesSent
	Dim lFlags
	Dim lReplicationID
	Dim lState
	Dim lStatus
	Dim stStartTime
	Dim stEndTime
	Dim CurrentLine

	cReplications = 0

	hr = NOERROR

	' Iterators must be initially set to zero
	vIterator = CLng(0)

	do while (True)

		set pIReplicationInstance = pIServer.EnumReplications(szProjectName, REPL_STATE_EMPTY, vIterator)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear

			if ((CRS_ERROR_NO_MORE_ITEMS <> hr) And (CRS_ERROR_REPLICATION_NOT_FOUND <> hr)) then

   				call PrintAPIError(g_szIReplicationServer, g_szEnumReplications, vbNullString, vbNullString, hr)

			elseif ((CRS_ERROR_REPLICATION_NOT_FOUND = hr) Or ((0 = cReplications) And (CRS_ERROR_NO_MORE_ITEMS = hr))) then

				WScript.Echo "No replications found."

			end if

			exit do

		end if

		cReplications = cReplications + 1

		'
		' Retrieve replication instance properties
		'
		szProjectName = pIReplicationInstance.Name
		hr = Err.Number
		if (hr <> 0) then
		
			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_Name, vbNullString, vbNullString, hr)
			exit do

		end if

		stStartTime = pIReplicationInstance.StartTime
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_StartTime, vbNullString, vbNullString, hr)
			exit do

		end if

		stEndTime = pIReplicationInstance.EndTime
		hr = Err.Number
		if (E_FAIL = hr) then

			' Replication is still running so we will use the current time for the time delta
			stEndTime = Time
			Err.Clear

		elseif (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_EndTime, vbNullString, vbNullString, hr)
			exit do

		end if

		lState = pIReplicationInstance.State
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_State, vbNullString, vbNullString, hr)
			exit do

		end if

		' Current error status
		lStatus = pIReplicationInstance.Status
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_Status, vbNullString, vbNullString, hr)
			exit do

		end if

		lFlags = pIReplicationInstance.Flags
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_Flags, vbNullString, vbNullString, hr)
			exit do

		end if

		lReplicationID = pIReplicationInstance.ID
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_ID, vbNullString, vbNullString, hr)
			exit do

		end if

		lFilesSent = pIReplicationInstance.FilesSent
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_FilesSent, vbNullString, vbNullString, hr)
			exit do

		end if

		ul64BytesSent = pIReplicationInstance.BytesSent
		hr = Err.Number
		if (hr <> 0) then
		
			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_BytesSent, vbNullString, vbNullString, hr)
			exit do

		end if

		lFilesReceived = pIReplicationInstance.FilesReceived
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_FilesReceived, vbNullString, vbNullString, hr)
			exit do

		end if

		ul64BytesReceived = pIReplicationInstance.BytesReceived
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_BytesReceived, vbNullString, vbNullString, hr)
			exit do

		end if

		lFilesMatched = pIReplicationInstance.FilesMatched
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_FilesMatched, vbNullString, vbNullString, hr)
			exit do

		end if

		ul64FilesMatchedBytes = pIReplicationInstance.FilesMatchedBytes
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_FilesMatchedBytes, vbNullString, vbNullString, hr)
			exit do

		end if

		lFilesErrored = pIReplicationInstance.FilesErrored
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_FilesErrored, vbNullString, vbNullString, hr)
			exit do

		end if

		ul64FilesErroredBytes = pIReplicationInstance.FilesErroredBytes
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
   			call PrintAPIError(g_szIReplicationInstance, g_szget_FilesErroredBytes, vbNullString, vbNullString, hr)
			exit do

		end if

		'
		' Print out any project info here
		'
		WScript.Echo "Project:        " & szProjectName

		WScript.Echo "Time Started:   " & stStartTime

		if ((lState = REPL_STATE_COMPLETE) Or (lState = REPL_STATE_CANCELED) Or (lState = REPL_STATE_ABORTED) Or (lState = REPL_STATE_PARTIAL)) then

			WScript.Echo "Time Finished:  " & stEndTime

		else

			WScript.Echo "Time Finished:  (NA)"
			stEndTime = Time

		end if

		WScript.Echo "Elapsed Time:   " & CDate(stStartTime - stEndTime) & " seconds"

		CurrentLine = "State:          "
		if (lState = REPL_STATE_EMPTY) then
			CurrentLine = CurrentLine & "EMPTY"
		elseif (lState = REPL_STATE_STARTING) then
			CurrentLine = CurrentLine & "STARTING"
		elseif (lState = REPL_STATE_RUNNING) then
			CurrentLine = CurrentLine & "RUNNING"
		elseif (lState = REPL_STATE_COMPLETE) then
			CurrentLine = CurrentLine & "COMPLETE"
		elseif (lState = REPL_STATE_ABORTED) then
			CurrentLine = CurrentLine & "ABORTED"
		elseif (lState = REPL_STATE_CANCELED) then
			CurrentLine = CurrentLine & "CANCELED"
		elseif (lState = REPL_STATE_RECEIVING) then
			CurrentLine = CurrentLine & "RECEIVING"
		elseif (lState = REPL_STATE_PENDING) then
			CurrentLine = CurrentLine & "PENDING"
		elseif (lState = REPL_STATE_PARTIAL) then
			CurrentLine = CurrentLine & "PARTIAL"
		end if

		WScript.Echo CurrentLine

		WScript.Echo "Status:         0x" & Hex(lStatus)

		CurrentLine = "Flags:          0x" & Hex(lFlags) & " ("

		if (lFlags = 0) then

			CurrentLine = CurrentLine & "NONE"

		else

			if ((lFlags And RF_NO_DELETE) <> 0) then
				CurrentLine = CurrentLine & " NODELETE"
			end if
			if ((lFlags And RF_REPLICATE_ACLS) <> 0) then
				CurrentLine = CurrentLine & " ACLS"
			end if
			if ((lFlags And RF_NO_DATA) <> 0) then
				CurrentLine = CurrentLine & " DIRSONLY"
			end if
			if ((lFlags And RF_FORCE_REPL) <> 0) then
				CurrentLine = CurrentLine & " FORCE"
			end if
			if ((lFlags And RF_INCREMENTAL) <> 0) then
				CurrentLine = CurrentLine & " INCREMENTAL"
			end if
			if ((lFlags And RF_FASTMODE) <> 0) then
				CurrentLine = CurrentLine & " FASTMODE"
			end if
			if ((lFlags And RF_ON_DIR_CHANGE) <> 0) then
				CurrentLine = CurrentLine & " AUTOMATIC"
			end if
			if ((lFlags And RF_ON_NOTIFY) <> 0) then
				CurrentLine = CurrentLine & " NOTIFY"
			end if
			if ((lFlags And RF_AUTO_ROUTE) <> 0) then
				CurrentLine = CurrentLine & " ROUTE"
			end if
			if ((lFlags And RF_PERMIT_TREE) <> 0) then
				CurrentLine = CurrentLine & " PERMIT"
			end if
			if ((lFlags  And RF_IN_PROC) <> 0) then
				CurrentLine = CurrentLine & " INPROC"
			end if
			if ((lFlags  And RF_EXCLUDE_ALL) <> 0) then
				CurrentLine = CurrentLine & " EXCLUDEALL"
			end if
			if ((lFlags  And RF_UNINSTALL) <> 0) then
				CurrentLine = CurrentLine & " UNINSTALL"	
			end if
			if ((lFlags And RF_ACLS_ONLY) <> 0) then
				CurrentLine = CurrentLine & " ACLSONLY"	
			end if

		end if

		CurrentLine = CurrentLine & " )"

		WScript.Echo CurrentLine

		WScript.Echo "Replication ID: 0x" & Hex(lReplicationID)

		WScript.Echo "Files Sent:     " & lFilesSent
		WScript.Echo "Bytes Sent:     " & ul64BytesSent
		WScript.Echo "Files Received: " & lFilesReceived
		WScript.Echo "Bytes Received: " & ul64BytesReceived
		WScript.Echo "Files Matched:  " & lFilesMatched
		WScript.Echo "Bytes Matched:  " & ul64FilesMatchedBytes
		WScript.Echo "Files Errored:  " & lFilesErrored
		WScript.Echo "Bytes Errored:  " & ul64FilesErroredBytes
		WScript.Echo

		Set pIReplicationInstance = Nothing

	loop


End Sub		


Sub ListItems(pIServer, szProjectName, szDirectory)

if (fDebug) then WScript.Echo "DEBUG: Sub ListItems"
	On Error Resume Next

	WScript.Echo "Not implemented."

End Sub		


Sub ListPostingAcceptor(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub ListPostingAcceptor"
	On Error Resume Next

	Dim cProperties
	Dim hr
	Dim pIPostingAcceptor
	Dim szParmName
	Dim szParmValue
	Dim vIterator

	cProperties = 0
	hr = 0

	szParmName = vbNullString
	szParmValue = vbNullString

	set pIPostingAcceptor = pIServer.OpenPostingAcceptor
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenPostingAcceptor, vbNullString, vbNullString, hr)
		exit sub

	end if


	' Iterators must be initially set to zero
	vIterator = CLng(0)

	do while (True)
	
		szParmValue = pIPostingAcceptor.Enum(vIterator, szParmName)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear

			if (CRS_ERROR_NO_MORE_ITEMS <> hr) then

   				call PrintAPIError(g_szIReplicationPostingAcceptor, g_szEnum, vbNullString, vbNullString, hr)

			elseif ((0 = cProperties) And (CRS_ERROR_NO_MORE_ITEMS = hr)) then

				WScript.Echo "No properties found."

			end if

			exit do

		end if

		cProperties = cProperties + 1

		WScript.Echo szParmName & ": " & szParmValue

	loop

	Set pIPostingAcceptor = Nothing

End Sub		


Sub SetPostingAcceptor(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub SetPostingAcceptor"
	On Error Resume Next

	WScript.Echo "Not implemented."

End Sub		


Sub GetPostingAcceptor(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub GetPostingAcceptor"
	On Error Resume Next

	Dim pIPostingAcceptor
	Dim hr
	Dim szParmName
	Dim szParmValue

	hr = 0

	szParmName = vbNullString
	szParmValue = vbNullString

	szParmName = gszPropertyName

	set pIPostingAcceptor = pIServer.OpenPostingAcceptor
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenPostingAcceptor, vbNullString, vbNullString, hr)
		exit sub

	end if

	szParmValue = pIPostingAcceptor.Get(szParmName)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationPostingAcceptor, g_szGet, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo szParmName & ": " & szParmValue

	Set pIPostingAcceptor = Nothing

End Sub		


Sub ListEventSinks(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub ListEventSinks"
	On Error Resume Next

	Dim cEventSinks
	Dim pIEventSinkConfig
	Dim hr
	Dim vIterator
	Dim szSinkName
	Dim szSinkCLSID
	Dim szSinkProjectFilter
	Dim szSinkDataSource
	Dim szSinkUserName
	Dim szSinkPassword
	Dim szSinkServer
	Dim fSinkDisabled
	Dim fSinkSynchronous
	Dim szSinkProviderCLSID
	Dim lEventLifetime

	cEventSinks = 0
	hr = NOERROR

	szSinkName = vbNullString
	szSinkCLSID = vbNullString
	szSinkProjectFilter = vbNullString
	szSinkDataSource = vbNullString
	szSinkUserName = vbNullString
	szSinkPassword = vbNullString
	szSinkServer = vbNullString
	szSinkProviderCLSID = vbNullString

	' Iterators must be initially set to zero
	vIterator = CLng(0)

	do while (True)

		set pIEventSinkConfig = pIServer.EnumEventSinks(vIterator)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear

			if (CRS_ERROR_NO_MORE_ITEMS <> hr) then

   				call PrintAPIError(g_szIReplicationServer, g_szEnumEventSinks, vbNullString, vbNullString, hr)

			elseif ((0 = cEventSinks) And (CRS_ERROR_NO_MORE_ITEMS = hr)) then

				WScript.Echo "No servers found."

			end if

			exit do

		end if

		cEventSinks = cEventSinks + 1

		szSinkName = pIEventSinkConfig.Name
		WScript.Echo "Name: " & szSinkName

		szSinkCLSID = pIEventSinkConfig.CLSID
		WScript.Echo vbTab & "CLSID: " & szSinkCLSID

		szSinkProjectFilter = pIEventSinkConfig.ProjectFilter
		WScript.Echo vbTab & "ProjectFilter: " & szSinkProjectFilter

		szSinkDataSource = pIEventSinkConfig.DataSource
		WScript.Echo vbTab & "DataSource: " & SzSinkDataSource

		szSinkUserName = pIEventSinkConfig.UserName
		WScript.Echo vbTab & "UserName: " & szSinkUserName

		szSinkPassword = pIEventSinkConfig.Password
		WScript.Echo vbTab & "Password: " & szSinkPassword

		szSinkServer = pIEventSinkConfig.Server
		WScript.Echo vbTab & "Server: " & szSinkServer

		fSinkDisabled = pIEventSinkConfig.Disabled
		WScript.Echo vbTab & "Disabled: " & fSinkDisabled

		fSinkSynchronous = pIEventSinkConfig.Synchronous
		WScript.Echo vbTab & "Synchronous: " & fSinkSynchronous

		szSinkProviderCLSID = pIEventSinkConfig.ProviderCLSID
		WScript.Echo vbTab & "ProviderCLSID: " & szSinkProviderCLSID

		lEventLifeTime = pIEventSinkConfig.EventLifetime
		WScript.Echo vbTab & "EventLifeTime: " & lEventLifetime
		
		WScript.Echo

		Set pIEventSinkConfig = Nothing

	loop

End Sub		


Sub ListServers(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub ListServers"
	On Error Resume Next

	Dim cServers
	Dim hr
	Dim vIterator
	Dim szServerName
	Dim cstFlag

	cServers = 0
	hr = NOERROR
	szServerName = vbNullString
	cstFlag = ENDPOINT

	' Iterators must be initially set to zero
	vIterator = CLng(0)

	do while (True)

		szServerName = pIServer.EnumServers(vIterator, cstFlag)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			if (CRS_ERROR_NO_MORE_ITEMS <> hr) then

   				call PrintAPIError(g_szIReplicationServer, g_szEnumServers, vbNullString, vbNullString, hr)

			elseif ((0 = cServers) And (CRS_ERROR_NO_MORE_ITEMS = hr)) then

				WScript.Echo "No servers found."

			end if

			exit do

		end if

		cServers = cServers + 1

		WScript.Echo cServers & ": " & szServerName

	loop

End Sub		


Sub ListVersion(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub ListVersion"
	On Error Resume Next

	Dim szVersion

	szVersion = vbNullString

	szVersion = pIServer.Version
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szget_Version, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Version: " & szVersion

End Sub		


Sub ListUser(pIServer, szProjectName)

if (fDebug) then WScript.Echo "DEBUG: Sub ListUser"
	On Error Resume Next

	Dim cUsers
	Dim cMaxLen
	Dim pIProject
	Dim hr
	Dim vIterator
	Dim szUserName
	Dim lAccessMask
	Dim CurrentLine
	Dim i

	cUsers = 0
	cMaxLen = 0
	szUserName = vbNullString
	hr = NOERROR

	set pIProject = pIServer.OpenProject(szProjectName, OPEN_EXISTING_PROJECT)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenProject, vbNullString, vbNullString, hr)
		exit sub

	end if

	cUsers = CountUsers(pIProject, cMaxLen)

	' Must format column past the "UserName" header
	if (cMaxLen < 8) then
		cMaxLen = 8
	end if

	CurrentLine = ""

	CurrentLine = CurrentLine & "UserName"
	for i = 0 to (cMaxLen/8 - 1) - 1
		CurrentLine = CurrentLine & vbTab
	next

	CurrentLine = CurrentLine & vbTab & "Access"
	WScript.Echo CurrentLine

	CurrentLine = ""

	' Iterators must be initially set to zero
	vIterator = CLng(0)
	
	do while (True)

		szUserName = pIProject.EnumAccess(vIterator, lAccessMask)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			if (CRS_ERROR_NO_MORE_ITEMS <> hr) then

   				call PrintAPIError(g_szIReplicationProject, g_szEnumAccess, vbNullString, vbNullString, hr)

			elseif ((0 = cUsers) And (CRS_ERROR_NO_MORE_ITEMS = hr)) then

				WScript.Echo "No users found."

			end if

			exit sub

		end if

		cUsers = cUsers + 1

		CurrentLine = CurrentLine & szUserName

		for i = 0 to (cMaxLen/8 - Len(szUserName)/8) - 1
			CurrentLine = CurrentLine & vbTab
		next
		
		Select case lAccessMask

			case CRS_ADMIN_ACCESS
				CurrentLine = CurrentLine & vbTab & "Administrator"

			case CRS_USER_ACCESS
				CurrentLine = CurrentLine & vbTab & "User"

			case else
				CurrentLine = CurrentLine & vbTab & "WARNING: Unknown user type (" & lAccessMask & ")"

		End Select

		WScript.Echo CurrentLine

		CurrentLine = ""

	Loop

	Set pIProject = Nothing

End Sub		


Function CountUsers(pIProject, iMaxLen)

	On Error Resume Next

	Dim hr
	Dim cUsers
	Dim vIterator
	Dim szUserName
	Dim lAccessMask

	hr = 0
	cUsers = 0
	szUserName = vbNullString

	' Iterators must be initially set to zero
	vIterator = CLng(0)

	do while (True)

		szUserName = pIProject.EnumAccess(vIterator, lAccessMask)
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear

			if (CRS_ERROR_NO_MORE_ITEMS <> hr) then

   				call PrintAPIError(g_szIReplicationProject, g_szEnumAccess, vbNullString, vbNullString, hr)

			elseif ((0 = cUsers) And (CRS_ERROR_NO_MORE_ITEMS = hr)) then

				WScript.Echo "No users found."

			end if

			exit do

		end if

		cUsers = cUsers + 1

		if ((iMaxLen > 0) Or (cUsers < 2)) then

			if (Len(szUserName) > iMaxLen) then

				iMaxLen = Len(szUserName)

			end if

		end if

	loop

	CountUsers = cUsers

End Function


Sub CheckUser(pIServer)

if (fDebug) then WScript.Echo "DEBUG: Sub CheckUser"
	On Error Resume Next

	Dim hr
	Dim lAccessMask

	hr = NOERROR

	lAccessMask = pIServer.CheckAccess
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szCheckAccess, vbNullString, vbNullString, hr)
		exit sub

	end if

	Select Case lAccessMask

		case CRS_ADMIN_ACCESS
			WScript.Echo "    Administrator"

		case CRS_USER_ACCESS
			WScript.Echo "    User"

		case else
			WScript.Echo "    WARNING: Unknown user type (" & lAccessMask & ")"

	End Select

End Sub		


Sub CheckUserProject(pIServer, szProjectName)

if (fDebug) then WScript.Echo "DEBUG: Sub CheckUserProject"
	On Error Resume Next

	Dim pIProject
	Dim hr
	Dim lAccessMask

	hr = NOERROR

	set pIProject = pIServer.OpenProject(szProjectName, OPEN_EXISTING_PROJECT)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenProject, vbNullString, vbNullString, hr)
		exit sub

	end if

	lAccessMask = pIProject.CheckAccess
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationProject, g_szCheckAccess, vbNullString, vbNullString, hr)
		exit sub

	end if

	Select Case lAccessMask

		case CRS_ADMIN_ACCESS
			WScript.Echo "    Administrator"

		case CRS_USER_ACCESS
			WScript.Echo "    User"

		case else
			WScript.Echo "    WARNING: Unknown user type (" & lAccessMask & ")"

	End Select

	Set pIProject = Nothing

End Sub		


Sub MapURL2Proj(pIServer, szURL)

if (fDebug) then WScript.Echo "DEBUG: Sub MapURL2Proj"
	On Error Resume Next

	Dim hr
	Dim pIProject
	Dim szMapURL
	Dim szSuffix
	Dim szProjectName

	hr = NOERROR

	szMapURL = vbNullString
	szSuffix = vbNullString
	szProjectName = vbNullString

	set pIProject = pIServer.MapUrl(szURL, szSuffix)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear

		if (CRS_ERROR_NO_MAPPING = hr) then

			WScript.Echo "No mapping to URL """ & szURL & """."
		else

   			call PrintAPIError(g_szIReplicationServer, g_szMapUrl, vbNullString, vbNullString, hr)

		end if

		exit sub

	end if
	
	szProjectName = pIProject.Name
	hr = Err.Number
	if (hr <> 0) then
	
		Err.Clear
   		call PrintAPIError(g_szIReplicationProject, g_szget_Name, vbNullString, vbNullString, hr)
		exit sub

	end if

	szMapUrl = pIProject.Get("MapUrl")
	hr = Err.Number
	if (hr <> 0) then
	
		Err.Clear
   		call PrintAPIError(g_szIReplicationProject, g_szGet, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Project Name: " & szProjectName

	WScript.Echo "MapUrl      : " & szMapURL

	WScript.Echo "Suffix      : " & szSuffix

	Set pIProject = Nothing

End Sub		


Sub TranslateEvent(pIServer, lEventCode)

if (fDebug) then WScript.Echo "DEBUG: Sub TranslateEvent"

	On Error Resume Next

	Dim hr
	Dim szDescription
	Dim lSeverity
	Dim lCategory

	hr = NOERROR
	szDescription = Space(260)
	lSeverity = CLng(0)
	lCategory = CLng(0)

	call pIServer.TranslateEventCode(lEventCode, szDescription, lSeverity, lCategory)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear

		' All event codes start with 0x8000xxxx, 0xC000xxxx, or 0x4000xxxx, so we'll try those just in case
		call pIServer.TranslateEventCode(CLng(lEventCode Or &h80000000), szDescription, lSeverity, lCategory)
		hr = Err.Number
		if (hr <> 0) then
			Err.Clear

			call pIServer.TranslateEventCode(CLng(lEventCode Or &hC0000000), szDescription, lSeverity, lCategory)
			hr = Err.Number
			if (hr <> 0) then
				
				Err.Clear
				call pIServer.TranslateEventCode(CLng(lEventCode Or &h40000000), szDescription, lSeverity, lCategory)
				hr = Err.Number
				if (hr <> 0) then

					Err.Clear
   					call PrintAPIError(g_szIReplicationServer, g_szTranslateEventCode, vbNullString, vbNullString, hr)
					exit sub

				end if

			end if

		end if

	end if

	WScript.Echo "Description: """ & szDescription & """"
	WScript.Echo "Severity: " & lSeverity
	WScript.Echo "Category: " & lCategory

End Sub


Sub ClearEventSink(pIServer, szEventSink)

if (fDebug) then WScript.Echo "DEBUG: Sub ClearEventSink"
	On Error Resume Next

	Dim hr
	
	hr = NOERROR

	pIServer.ClearEvents(szEventSink)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szClearEvents, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Event sink """ & szEventSink & """ cleared."

End Sub		


Sub SendFile(pIServer, szProjectName, szFileName)

if (fDebug) then WScript.Echo "DEBUG: Sub SendFile"
	On Error Resume Next

	Dim hr
	Dim pIProject
	Dim pIReplicationClient
	Dim vIterator
	Dim fFastMode
	Dim fForce
	Dim fACLs
	Dim lNumDestinations
	Dim fSkipLockedFiles

	hr = NOERROR

	' Iterators must be initially set to zero
	vIterator = CLng(0)

	set pIProject = pIServer.OpenProject(szProjectName, OPEN_EXISTING_PROJECT)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenProject, szProjectName, vbNullString, hr)
		exit sub

	end if

	WScript.Echo
	WScript.Echo "Project:" & vbTab & """" & szProjectName & """"

	set pIReplicationClient = pIProject.StartReplicationClient(0)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
		call PrintAPIError(g_szIReplicationProject, g_szStartReplicationClient, vbNullString, vbNullString, hr)
		exit sub

	end if

	fFastMode = pIReplicationClient.FastMode
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_FastMode, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Fastmode:" & vbTab & vbTab & fFastMode

	fForce = pIReplicationClient.Force
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_Force, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Force:" & vbTab & vbTab & vbTab & fForce

	fACLs = pIReplicationClient.ACLs
	hr = Err.Number
	if (hr <> 0 ) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_ACLs, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "ACLs:" & vbTab & vbTab & vbTab & fACLs

	lNumDestinations = pIReplicationClient.NumDestinations
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_NumDestinations, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "NumDestinations:" & vbTab & lNumDestinations

	fSkipLockedFiles = pIReplicationClient.SkipLockedFiles
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_SkipLockedFiles, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "SkipLockedFiles:" & vbTab & fSkipLockedFiles

	WScript.Echo
	WScript.Echo
	WScript.Echo "Sending file:" & vbTab & """" & szFileName & """"

	pIReplicationClient.SendFile(szFileName)
	hr = Err.Number
	if (hr <> 0) then


		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szSendFile, vbNullString, vbNullString, hr)

		call PrintReplicationClientError(pIReplicationClient)
		exit sub

	end if

	pIReplicationClient.Commit
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szCommit, vbNullString, vbNullString, hr)
		exit sub

	end if

	Set pIProject = Nothing
	Set pIReplicationClient = Nothing

End Sub		


Sub SendFiles(pIServer, szProjectName, szFileNames, cFileNames)

if (fDebug) then WScript.Echo "DEBUG: Sub SendFiles"
	On Error Resume Next

	WScript.Echo "Not implemented."

End Sub		


Sub DeleteFile(pIServer, szProjectName, szFileName)

if (fDebug) then WScript.Echo "DEBUG: Sub DeleteFile"
	On Error Resume Next

	Dim hr
	Dim pIProject
	Dim pIReplicationClient
	Dim vIterator
	Dim fFastMode
	Dim fForce
	Dim fACLs
	Dim lNumDestinations
	Dim fSkipLockedFiles

	hr = NOERROR

	' Iterators must be initially set to zero
	vIterator = CLng(0)
	
	set pIProject = pIServer.OpenProject(szProjectName, OPEN_EXISTING_PROJECT)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenProject, szProjectName, vbNullString, hr)
		exit sub

	end if

	WScript.Echo
	WScript.Echo "Project:" & vbTab & """" & szProjectName & """"

	set pIReplicationClient = pIProject.StartReplicationClient(0)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
		call PrintAPIError(g_szIReplicationProject, g_szStartReplicationClient, vbNullString, vbNullString, hr)
		exit sub

	end if

	fFastMode = pIReplicationClient.FastMode
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_FastMode, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Fastmode:" & vbTab & vbTab & fFastMode

	fForce = pIReplicationClient.Force
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_Force, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Force:" & vbTab & vbTab & vbTab & fForce

	fACLs = pIReplicationClient.ACLs
	hr = Err.Number
	if (hr <> 0 ) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_ACLs, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "ACLs:" & vbTab & vbTab & vbTab & fACLs
	lNumDestinations = pIReplicationClient.NumDestinations
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_NumDestinations, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "NumDestinations:" & vbTab & lNumDestinations

	fSkipLockedFiles = pIReplicationClient.SkipLockedFiles
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szget_SkipLockedFiles, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "SkipLockedFiles:" & vbTab & fSkipLockedFiles

	WScript.Echo
	WScript.Echo
	WScript.Echo "Deleting file:" & vbTab & """" & szFileName & """"

	pIReplicationClient.DeleteFile(szFileName)
	hr = Err.Number
	if (hr <> 0) then


		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szDeleteFile, vbNullString, vbNullString, hr)

		call PrintReplicationClientError(pIReplicationClient)
		exit sub

	end if

	pIReplicationClient.Commit
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szCommit, vbNullString, vbNullString, hr)
		exit sub

	end if

	Set pIProject = Nothing
	Set pIReplicationClient = Nothing

End Sub



Sub PrintReplicationClientError(pIReplicationClient)

if (fDebug) then WScript.Echo "DEBUG: Sub PrintReplicationClientError"
	On Error Resume Next

	Dim pIReplicationClientError
	Dim aReplicationClientErrorArray
	Dim szDescription
	Dim szDestination
	Dim lErrorCode
	Dim szFileName
	Dim szProjectName
	Dim szSource
	Dim hr
	Dim cUBound
	Dim i

	szFileName = vbNullString
	szDescription = vbNullString
	szDestination = vbNullString
	szProjectName = vbNullString
	szSource = vbNullString

	aReplicationClientErrorArray = pIReplicationClient.GetExtendedErrorInfo
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationClient, g_szGetExtendedErrorInfo, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo
	cUBound = UBound(aReplicationClientErrorArray)

	for i = 0 to cUBound

		set pIReplicationClientError = aReplicationClientErrorArray(i)

		szDescription = pIReplicationClientError.Description
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			call PrintAPIError(g_szIReplicationClientError, g_szget_Description, vbNullString, vbNullString, hr)
			exit sub

		end if

		szDestination = pIReplicationClientError.Destination
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			call PrintAPIError(g_szIReplicationClientError, g_szget_Destination, vbNullString, vbNullString, hr)
			exit sub

		end if

		lErrorCode = pIReplicationClientError.ErrorCode
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			call PrintAPIError(g_szIReplicationClientError, g_szget_ErrorCode, vbNullString, vbNullString, hr)
			exit sub

		end if

		szFileName = pIReplicationClientError.FileName
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			call PrintAPIError(g_szIReplicationClientError, g_szget_FileName, vbNullString, vbNullString, hr)
			exit sub

		end if

		szProjectName = pIReplicationClientError.Project
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			call PrintAPIError(g_szIReplicationClientError, g_szget_Project, vbNullString, vbNullString, hr)
			exit sub
		end if
		
		szSource = pIReplicationClientError.Source
		hr = Err.Number
		if (hr <> 0) then

			Err.Clear
			call PrintAPIError(g_szIReplicationClientError, g_szget_Source, vbNullString, vbNullString, hr)
			exit sub

		end if

		WScript.Echo vbTab & "FileName" & vbTab & ": " & """" & szFileName & """"
		WScript.Echo vbTab & "Description" & vbTab & ": " & """" & szDescription & """"

		WScript.Echo vbTab & "Destination" & vbTab & ": " & szDestination
		WScript.Echo vbTab & "ErrorCode" & vbTab & ": " & lErrorCode
		WScript.Echo vbTab & "Project" & vbTab & vbTab & ": " & szProjectName
		WScript.Echo vbTab & "Source" & vbTab & vbTab & ": " & szSource
		WScript.Echo

	next

	WScript.Echo

	Set pIReplicationClientError = Nothing

End Sub



Sub StartRep(pIServer, szProjectName)

if (fDebug) then WScript.Echo "DEBUG: Sub Startrep"
	On Error Resume Next

	Dim hr
	Dim pIProject
	Dim pIReplicationInstance

	hr = NOERROR

	set pIProject = pIServer.OpenProject(szProjectName, OPEN_EXISTING_PROJECT)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
   		call PrintAPIError(g_szIReplicationServer, g_szOpenProject, szProjectName, vbNullString, hr)
		exit sub

	end if

	WScript.Echo
	WScript.Echo "Starting project """ & szProjectName & """..."

	set pIReplicationInstance = pIProject.Start(0)
	hr = Err.Number
	if (hr <> 0) then

		Err.Clear
		call PrintAPIError(g_szIReplicationProject, g_szStart, vbNullString, vbNullString, hr)
		exit sub

	end if

	WScript.Echo "Project """ & szProjectName & """ started."

	Set pIProject = Nothing
	Set pIReplicationInstance = Nothing
End Sub