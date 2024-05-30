' ====================================================================
' FILE:	DistList.VBS
'
' PARAMETERS:
'
'		FUNCTIONS:
'
'		/F1 Remove Non-Existent/Cancelled Users from a DL or from all DLs
'		/F2	Add/Remove a list of users to/from a DL
'		/F3	Remove a user from all DLs
'		/F4	Count number of users in each DL
'		/F5 Diagnose DL (Dump e-mail addresses and GUIDs of members)
'
'
' PARAMETERS COMMON TO ALL FUNCTIONS:
'
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/?	Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'
' ADDITIONAL PARAMETERS FOR EACH FUNCTION:
'
'
'		F1 - REMOVE NON-EXISTENT/CANCELLED USERS FROM A DL OR FROM ALL DLs
'		-------------------------------------------------------------
'
'		/D	DN of the distribution list (e.g. cn=myDL,ou=distributionLists,o=Microsoft)
'			(optional - if not specified, non-existent/cancelled users will be removed 
'			from all DLs)
'		/N	Flag to remove non-existent users only (optional)
'		/C	Flag to remove cancelled users only (optional)
'			(If neither or both /N nor/and /C is/are specified, both non-existent and 
'			 cancelled users will be removed.)
'
'
'		F2 - ADD/REMOVE A LIST OF USERS TO/FROM A DL
'		-------------------------------------------------------------
'
'		/D	DN of the target distribution list (e.g. cn=myDL,ou=distributionLists,o=Microsoft)
'		/I  Input file containing list of DNs of users to be added/removed
'		/+  If specified, the users will be added to the DL
'		/-  If specified, the users will be removed from the DL
'
'		/+ and /- are mutually exclusive.
'
'
'
'		F3 - REMOVE A USER FROM ALL DLs
'		-------------------------------------------------------------
'		
'		/M	DN of user to remove from all DLs (e.g. cn=user1,ou=members,o=microsoft)
'
'
'		F4 - COUNT NUMBER OF USERS IN EACH DL
'		-------------------------------------------------------------
'		
'		No additional parameter for this function.
'
'
'		F5 - DIAGNOSE DL (DUMP E-MAIL ADDRESSES AND GUIDs of MEMBERS)
'		-------------------------------------------------------------
'		
'		/D	DN of the distribution list (e.g. cn=myDL,ou=distributionLists,o=Microsoft)
'
'
' IMPORTANT REMARKS:
'
'		F1 - REMOVE NON-EXISTENT/CANCELLED USERS FROM A DL OR FROM ALL DLs
'		-------------------------------------------------------------
'
'		When removing users from all DLs, this function assumes that all
'		the DLs reside under the ou=distributionLists container, either
'		directly or indirectly.
'
'
'		F2 - ADD/REMOVE A LIST OF USERS TO/FROM A DL
'		-------------------------------------------------------------
'
'		When adding users to a DL, this function does not check for
'		duplicates and does not validate whether the user really exists
'		in the directory.
'
'
'		F3 - REMOVE A USER FROM ALL DLs
'		-------------------------------------------------------------
'		
'		This function assumes that all the DLs reside under the 
'		ou=distributionLists container, either directly or indirectly.
'
'
'		F4 - COUNT NUMBER OF USERS IN EACH DL
'		-------------------------------------------------------------
'		
'		This function does not handle circular inclusions (i.e. DL 1 belongs
'		to DL 2 and DL 2 belongs to DL 1, either directly or indirectly), 
'		the presence of which will cause it to enter an infinite loop.
'
'		The function checks if a member is a DL by searching for
'		"ou=distributionLists" in the DN.  So it will not work if you have
'		user members whose DNs have "ou=distributionLists" in them or if you
'		have DLs who do not. In	that case, you can modify the script to take 
'		the extra step of getting the object of each member and get its objectClass 
'		attribute to determine if it is a user or another DL.
'
'		   
'		F5 - DIAGNOSE DL (DUMP E-MAIL ADDRESSES AND GUIDs of MEMBERS)
'		-------------------------------------------------------------
'
'		This function does not do recursion, i.e. if a member is another DL,
'		the function will NOT expand that DL to diagnose its members,too.
'
'
' (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE. 
' ====================================================================

Option Explicit

'------------------------------------------------------
'
' Localizable Strings
'
'------------------------------------------------------

' *** Please also localize the EchoUsage() procedure. ***

' argument switches
const L_swFunc1						= "/F1"
const L_swFunc2						= "/F2"
const L_swFunc3						= "/F3"
const L_swFunc4						= "/F4"
const L_swFunc5						= "/F5"
const L_swServer					= "/H"
const L_swAccountName				= "/U"
const L_swPassword					= "/P"
const L_swDLDN						= "/D"
const L_swUserDN					= "/M"
const L_swNonExistent				= "/N"
const L_swCancelled					= "/C"
const L_swInputFile					= "/I"
const L_swAddFlag					= "/+"
const L_swRemoveFlag				= "/-"
const L_swHelp						= "/?"

' header information
const L_Title1						= "REMOVE NON-EXISTENT/CANCELLED USERS FROM A DL OR FROM ALL DLs"
const L_Title2						= "ADD/REMOVE A LIST OF USERS TO/FROM A DL"
const L_Title3						= "REMOVE A USER FROM ALL DLs"
const L_Title4						= "COUNT NUMBER OF USERS IN EACH DL"
const L_Title5						= "DIAGNOSE DL (DUMP E-MAIL ADDRESSES AND GUIDs of MEMBERS)"
const L_TimeExecuted				= "Time Executed: "
const L_optServer					= "Server       : "
const L_optAccountName				= "User         : "
const L_optDLDN						= "Target DL    : "
const L_optUserDN					= "Remove User  : "
const L_optInputFile				= "Input File   : "
const L_optOperation				= "Operation    : "
const L_optWhichUsers				= "Which Users  : "

const L_All							= "All"

' operations
const L_operAdd						= "Add"
const L_operRemove					= "Remove"

' which users
const L_usrNonExistent				= "Non-Existent"
const L_usrCancelled				= "Cancelled"
const L_usrBoth						= "Non-Existent/Cancelled"

' status information
const L_Error						= "Error: "
const L_Success						= "Success"
const L_Failure						= "Failure"

' specific messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."
const L_NotAMember					= "Not a member."
const L_MembersRemoved				= "Members successfully removed."
const L_FailedToRemoveMembers		= "Failed to remove the members!!!"
const L_NoMembersToRemove			= "No members to remove."
const L_FailedToBindTo				= "Failed to bind to "
const L_FailedToGetStatusOf			= "Failed to get the accountStatus of "
const L_MembersAdded				= "Members successfully added."
const L_FailedToAddMembers			= "Failed to add the members!!!"
const L_NumDirectUsers			    = "     Number of direct users      : "
const L_NumIndirectUsers			= "     Number of indirect users    : "
const L_TotalUsers				    = "     Total number of users       : "
const L_NumErrors					= "     Number of errors encountered: "
const L_FailedToCountUsers		    = "     Failed to count the users in this DL!"
const L_NoDL						= "User does not belong to any DL."

' Diagnose DL strings
const L_NoEmail						= "No e-mail (or no access)"
const L_NoGUID						= "No GUID (or no access)"
const L_NoMembers					= "Either the DL has no members or the user does not have access to them."


'------------------------------------------------------
' Constants
'------------------------------------------------------

' Default values for the arguments
const def_strAccountName			= ""
const def_strPassword				= ""
const def_strDLDN					= ""

const DN_DELIM = ";"

' Error Codes
const ERROR_OBJECT_NOT_FOUND   = &H80070002
Const ERROR_INVALID_SYNTAX	   = &H800401E4
const ERROR_NOT_A_MEMBER       = &H800704B8	
Const ERROR_PROPERTY_NOT_FOUND = &H8000500D

' ADSI Constants
Const ADS_ATTR_CLEAR = 1
Const ADS_ATTR_UPDATE = 2
Const ADS_ATTR_APPEND = 3
Const ADS_ATTR_DELETE = 4

' Flags for MemberStatus()
Const CHECK_EXISTENCE		= 0
Const CHECK_STATUS			= 1

' Member Status Values
Const STATUS_EXISTS			= 0		' Member exists.
Const STATUS_ACTIVE			= 1		' Member exists and accountStatus is not 4.
Const STATUS_CANCELLED		= 2		' Member exists and accountStatus is 4.
Const STATUS_NO_STATUS		= 3		' Member exists and does not have the accountStatus attribute.
Const STATUS_NOT_FOUND		= 4		' Member does not exist.
Const STATUS_FAIL			= 5		' Failed to get member object or its accountStatus attribute.

' Flags for RemoveDeadMembersFromDL()
Const REMOVE_CANCELLED		= 0
Const REMOVE_NONEXISTENT	= 1
Const REMOVE_BOTH			= 2

' Add/Remove flags
Const OPER_ADD				= 0
Const OPER_REMOVE			= 1

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_nFunction
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_strDLDN
Dim	g_strUserDN
Dim	g_nRemoveWhichUsers
Dim g_strInputFile
Dim g_nOper

Dim g_intNumUsers
Dim	g_intNumSuccess
Dim	g_intNumFailure


'------------------------------------------------------
'
' Main Routine
'
'------------------------------------------------------

if GetArguments then
	EchoHeader

	Select Case g_nFunction
		Case 1
			if g_strDLDN = "" then
				Call RemoveDeadMembersFromAllDLs( g_strServer, g_nRemoveWhichUsers )
			else
				Call RemoveDeadMembersFromDL( g_strServer, FormADsPath( g_strServer, g_strDLDN ), g_nRemoveWhichUsers )
			end if
		Case 2
			Call AddRemoveDLMembers( g_strServer, g_strDLDN, g_strInputFile, g_nOper )
		Case 3
			Call RemoveUserFromAllDLs( g_strServer, g_strUserDN )
		Case 4
			Call CountUsersInAllDLs( g_strServer )
		Case 5
			Call DiagnoseDL( g_strServer, g_strDLDN )
	End Select

end if


'------------------------------------------------------
'
' Function:     GetArguments
' Purpose:      Parses the command-line arguments and
'				saves the arguments into the corresponding
'				variables.
'				Returns TRUE if all arguments are valid.
'				Returns FALSE otherwise or if the HELP
'				switch was explicitly specified.
'
'------------------------------------------------------
Function GetArguments

	GetArguments = false

	' set default values
	g_strAccountName	= def_strAccountName			
	g_strPassword		= def_strPassword				
	g_strDLDN			= def_strDLDN
	g_nRemoveWhichUsers = REMOVE_BOTH

	' initialize mandatory arguments
	g_strServer			= ""
	g_strUserDN			= ""
	g_strInputFile		= ""
	g_nFunction			= 0

	Dim intNumOperSpecified
	intNumOperSpecified = 0

	Dim Arg
	Dim strSwitch

	strSwitch = ""
	for each Arg in wscript.Arguments
		if (strSwitch = "") then

			strSwitch = UCase( Arg )

			'
			'	Switches that do not expect anything after them
			'

			Select Case strSwitch
				Case L_swFunc1
					if g_nFunction > 0 then
						EchoUsage
						exit function
					end if
					g_nFunction = 1
					strSwitch = ""
				Case L_swFunc2
					if g_nFunction > 0 then
						EchoUsage
						exit function
					end if
					g_nFunction = 2
					strSwitch = ""
				Case L_swFunc3
					if g_nFunction > 0 then
						EchoUsage
						exit function
					end if
					g_nFunction = 3
					strSwitch = ""
				Case L_swFunc4
					if g_nFunction > 0 then
						EchoUsage
						exit function
					end if
					g_nFunction = 4
					strSwitch = ""
				Case L_swFunc5
					if g_nFunction > 0 then
						EchoUsage
						exit function
					end if
					g_nFunction = 5
					strSwitch = ""
				Case L_swHelp
					EchoUsage
					exit function
				Case L_swAddFlag
					g_nOper = OPER_ADD
					intNumOperSpecified = intNumOperSpecified + 1
					strSwitch = ""
				Case L_swRemoveFlag
					g_nOper = OPER_REMOVE
					intNumOperSpecified = intNumOperSpecified + 1
					strSwitch = ""
				Case L_swNonExistent
					if g_nRemoveWhichUsers = REMOVE_CANCELLED then
						g_nRemoveWhichUsers = REMOVE_BOTH
					else
						g_nRemoveWhichUsers = REMOVE_NONEXISTENT
					end if
					strSwitch = ""
				Case L_swCancelled
					if g_nRemoveWhichUsers = REMOVE_NONEXISTENT then
						g_nRemoveWhichUsers = REMOVE_BOTH
					else
						g_nRemoveWhichUsers = REMOVE_CANCELLED
					end if
					strSwitch = ""
			End Select

		else

			'
			'	Switches that expect something to come after them
			'

			Select Case strSwitch
				Case L_swServer
					g_strServer			= Arg
				Case L_swAccountName
					g_strAccountName	= Arg
				Case L_swPassword
					g_strPassword		= Arg
				Case L_swDLDN
					g_strDLDN			= Arg
				Case L_swUserDN
					g_strUserDN			= Arg
				Case L_swInputFile
					g_strInputFile		= Arg
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Check validity of arguments
	'					    	
	'

	Dim bAllValid
	bAllValid = True

	if g_strServer = "" then bAllValid = False

	Select Case g_nFunction
		Case 1
			' no other special requirements
		Case 2
			if g_strDLDN = "" or g_strInputFile = "" or intNumOperSpecified <> 1 then bAllValid = False
		Case 3
			if g_strUserDN = "" then bAllValid = False
		Case 4
			' no other special requirements
		Case 5
			if g_strDLDN = "" then bAllValid = False
		Case Else
			bAllValid = False
	End Select

	if NOT bAllValid then EchoUsage
	GetArguments = bAllValid

End Function


'------------------------------------------------------
'
' Function:     EchoUsage (LOCALIZABLE!!!)
' Purpose:      Echoes correct usage of script.
'
'------------------------------------------------------
Sub EchoUsage
	
	wscript.echo "DISTRIBUTION LIST FUNCTIONS"
	wscript.echo "(parameters are case and order insensitive)"
	wscript.echo
	wscript.echo L_swFunc1 & "  " & L_Title1
	wscript.echo L_swFunc2 & "  " & L_Title2
	wscript.echo L_swFunc3 & "  " & L_Title3
	wscript.echo L_swFunc4 & "  " & L_Title4
	wscript.echo L_swFunc5 & "  " & L_Title5
	wscript.echo
	wscript.echo
	wscript.echo "Parameters common to all functions:"
	wscript.echo
	wscript.echo L_swServer      & "  " & "Server:Port"
	wscript.echo L_swAccountName & "  " & "User DN (optional)"
	wscript.echo L_swPassword    & "  " & "User password (optional)"
	wscript.echo L_swHelp		 & "  " & "Displays this help message."
	wscript.echo
	wscript.echo
	wscript.echo "Parameters specific to each function:"
	wscript.echo
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo "F1 - " & L_Title1 & ":"
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo
	wscript.echo L_swDLDN		 & "  " & "DN of the distribution list (optional)"
	wscript.echo L_swNonExistent & "  " & "Flag to remove non-existent users only (optional)"
	wscript.echo L_swCancelled   & "  " & "Flag to remove cancelled users only (optional)"
	wscript.echo
	wscript.echo "If " & L_swDLDN & " is not specified, the non-existent/cancelled users" 
	wscript.echo "will be removed from all DLs."
	wscript.echo
	wscript.echo "If neither " & L_swNonExistent & " nor " & L_swCancelled & " is specified or they are both specified,"
	wscript.echo "both non-existent and cancelled users will be removed."
	wscript.echo
	wscript.echo
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo "F2 - " & L_Title2 & ":"
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo 
	wscript.echo L_swDLDN		 & "  " & "DN of the target distribution list"
	wscript.echo L_swInputFile	 & "  " & "Input file containing list of user DN's"
	wscript.echo L_swAddFlag	 & "  " & "Flag to add members to DL"
	wscript.echo L_swRemoveFlag	 & "  " & "Flag to remove members from DL"
	wscript.echo
	wscript.echo L_swAddFlag & " and " & L_swRemoveFlag & " are mutually-exclusive."
	wscript.echo
	wscript.echo
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo "F3 - " & L_Title3 & ":"
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo 
	wscript.echo L_swUserDN      & "  " & "DN of user to remove from all DLs"
	wscript.echo
	wscript.echo
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo "F4 - " & L_Title4 & ":" 
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo
	wscript.echo "No parameters specific to this function."
	wscript.echo
	wscript.echo
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo "F5 - " & L_Title5 & ":"
	wscript.echo "----------------------------------------------------------------------"
	wscript.echo 
	wscript.echo L_swDLDN		 & "  " & "DN of the distribution list"
	wscript.echo
	wscript.echo
	wscript.echo "Where DNs are required, the assumed format is one where the RDN is"
	wscript.echo "at the beginning.  e.g. cn=RDN,ou=cont,o=myorg"
	wscript.echo
	wscript.echo "Type ""cscript distlist.vbs /? | more"" for screen-by-screen view of" 
	wscript.echo "this help message."

End Sub


'------------------------------------------------------
'
' Function:     EchoHeader
' Purpose:      Echoes script information and
'				options selected.
'
'------------------------------------------------------
Sub EchoHeader
	
	Select Case g_nFunction
		Case 1
			wscript.echo L_Title1
		Case 2
			wscript.echo L_Title2
		Case 3
			wscript.echo L_Title3
		Case 4
			wscript.echo L_Title4
		Case 5
			wscript.echo L_Title5
	End Select

	wscript.echo 
	wscript.echo L_TimeExecuted & Now
	wscript.echo L_optServer & g_strServer
	wscript.echo L_optAccountName & g_strAccountName

	Select Case g_nFunction

		Case 1
			if g_strDLDN = "" then
				wscript.echo L_optDLDN & L_All
			else
				wscript.echo L_optDLDN & g_strDLDN
			end if

			Select Case g_nRemoveWhichUsers
				Case REMOVE_NONEXISTENT
					wscript.echo L_optWhichUsers & L_usrNonExistent
				Case REMOVE_CANCELLED
					wscript.echo L_optWhichUsers & L_usrCancelled
				Case REMOVE_BOTH
					wscript.echo L_optWhichUsers & L_usrBoth
			End Select

		Case 2
			wscript.echo L_optDLDN & g_strDLDN
			wscript.echo L_optInputFile & g_strInputFile
			if g_nOper = OPER_ADD then
				wscript.echo L_optOperation & L_operAdd
			else
				wscript.echo L_optOperation & L_operRemove
			end if

		Case 3
			wscript.echo L_optUserDN & g_strUserDN

		Case 5
			wscript.echo L_optDLDN & g_strDLDN

	End Select

	wscript.echo	

End Sub


'------------------------------------------------------
'
' Function:     RemoveDeadMembersFromAllDLs
' Purpose:      Removes either or both non-existent and
'				cancelled users from all DLs
'
'------------------------------------------------------
Sub RemoveDeadMembersFromAllDLs( strServer, nWhichUsers )
	
	On Error Resume Next

	'	
	'	Get defaultNamingContext
	'

	Dim strDefaultNamingContext
	if NOT GetDefaultNamingContext( strServer, strDefaultNamingContext ) then
		exit sub
	end if


	'
	'	Establish connection
	'

	Dim Connection
	set Connection = CreateObject("ADODB.Connection")
	if EchoError then exit sub

	Connection.Provider = "ADsDSOObject"
	Connection.Open "ADS Provider", g_strAccountName, g_strPassword
	if EchoError then exit sub


	'
	'	Form query string for finding all the DLs in the directory
	'  

	Dim strQueryString, strDistListContainerPath
	strDistListContainerPath = FormADsPath( strServer, "ou=distributionLists," & strDefaultNamingContext )
	strQueryString = "<" & strDistListContainerPath & ">;(objectClass=distributionList);adspath;subtree"

	'
	'	Execute query
	'

	Dim Recordset
	set Recordset = Connection.Execute( strQueryString )
	if EchoError then exit sub


	'
	'	Remove dead members from each DL
	'

	Dim strDLPath
	do until Recordset.EOF

		strDLPath = Recordset.Fields("adspath")
		RemoveDeadMembersFromDL strServer, strDLPath, nWhichUsers
		Recordset.MoveNext

	loop


	'
	'	Clean up
	'

	Set Recordset = Nothing
	Set Connection = Nothing

End Sub


'------------------------------------------------------
'
' Function:     GetDefaultNamingContext
' Purpose:      Gets the default naming context of the
'				directory.  Returns TRUE if successful.
'
'------------------------------------------------------
Function GetDefaultNamingContext( strServer, strDefaultNamingContext )
	
	On Error Resume Next

	GetDefaultNamingContext = False

	Dim objRoot

	' Bind to RootDSE
	if NOT BindToObject(FormADsPath(strServer, "RootDSE"), objRoot, True ) then 
		exit function
	end if

	' get the default naming context attribute
	strDefaultNamingContext = objRoot.Get("defaultNamingContext")
	if EchoError then
		set objRoot = Nothing
		exit function
	end if

	set objRoot = Nothing
	GetDefaultNamingContext = True

End Function


'------------------------------------------------------
'
' Function:     BindToObject
' Purpose:      Binds to object specified by the
'				supplied path.
'
'------------------------------------------------------
Function BindToObject( strPath, obj, bDisplayError )

	On Error Resume Next

	BindToObject = false

	'
	'	If user's credentials are specified, bind using those credentials.
	'	Else, bind anonymously (if under member auth) or bind as the currently logged
	'	on user (if under NT Auth).  This is accomplished by passing the full path
	'	itself to GetObject() below.
	'

	if g_strAccountName <> "" then

		Dim objLDAP
		Dim blnError

		set objLDAP = GetObject("LDAP:")
		if EchoError then exit function

		set obj = objLDAP.OpenDSObject( strPath, g_strAccountName, g_strPassword, 0 )

		if err then
			
			if bDisplayError then
				EchoError
				wscript.echo L_FailedToBindTo & strPath & "!"
			end if
		
			set objLDAP = Nothing
			exit function

		end if

	else

		set obj = GetObject( strPath )

		if err then
			
			if bDisplayError then
				EchoError
				wscript.echo L_FailedToBindTo & strPath & "!"
			end if
		
			exit function

		end if

	end if

	BindToObject = true

End Function


'------------------------------------------------------
'
' Function:     FormADsPath
' Purpose:      Forms the ADsPath given the server
'				and the DN
'
'------------------------------------------------------
Function FormADsPath( strServer, strDN )
	FormADsPath = "LDAP://" & strServer & "/" & strDN
End Function


'------------------------------------------------------
'
' Function:     EchoError
' Purpose:      if there is an error, this function
'				echoes the error and returns true
'
'------------------------------------------------------
Function EchoError

	if err then

		if err = ERROR_OBJECT_NOT_FOUND or err = ERROR_INVALID_SYNTAX then
			wscript.echo L_ObjectNotFound
		else
			wscript.echo L_Error & err.description & " (0x" & hex(err.number) & ")"
		end if

		EchoError = true

	else
		EchoError = false
	end if

End Function


'------------------------------------------------------
'
' Function:     RemoveDeadMembersFromDL
' Purpose:      Removes either or both non-existent and
'				cancelled users from a DL
'
'------------------------------------------------------
Sub RemoveDeadMembersFromDL( strServer, strDLPath, nWhichUsers )

	On Error Resume Next

	wscript.echo strDLPath

	'
	'	Bind to DL object
	'

	Dim objDL
	if NOT BindToObject( strDLPath, objDL, True ) then exit sub

	'
	'	Get its dlMember attribute
	'

	Dim arrOrigMembers, strMemberDN
	arrOrigMembers = objDL.get("dlMember")


	'
	'	If not present, exit procedure
	'

	if err = ERROR_PROPERTY_NOT_FOUND then
		wscript.echo L_NoMembersToRemove
		wscript.echo		
		exit sub
	end if


	'
	'	On other errors, display error and exit procedure
	'

	if EchoError then exit sub


	'
	'	If dlMember has only one value, make it into an array
	'

	if NOT IsArray( arrOrigMembers ) then arrOrigMembers = Array( arrOrigMembers )

	
	'
	'	Check the status of each member, and if
	'	it is cancelled and/or non-existent (depending on what we want),
	'	add it to the list of members to be removed.
	'
	
	Dim strToRemove
	Dim nStatus, bRemove

	strToRemove = ""
	For Each strMemberDN In arrOrigMembers

		Select Case nWhichUsers
			Case REMOVE_CANCELLED:
				nStatus = MemberStatus( strServer, strMemberDN, CHECK_STATUS )
				bRemove = (nStatus = STATUS_CANCELLED)
			Case REMOVE_NONEXISTENT:
				nStatus = MemberStatus( strServer, strMemberDN, CHECK_EXISTENCE )
				bRemove = (nStatus = STATUS_NOT_FOUND)
			Case REMOVE_BOTH:
				nStatus = MemberStatus( strServer, strMemberDN, CHECK_STATUS )
				bRemove = (nStatus = STATUS_CANCELLED or nStatus = STATUS_NOT_FOUND)
		End Select

		If bRemove Then

			wscript.echo "     " & strMemberDN
			strMemberDN = LCase( strMemberDN )

			if strToRemove <> "" then
				' add MemberDN to list of DNs to remove if it's not there yet.
				if Instr( strToRemove, strMemberDN ) = 0 then
					strToRemove = strToRemove & DN_DELIM & strMemberDN
				end if
			else
				strToRemove = strMemberDN
			end if

		End If

	Next

	'
	'	If there are members to remove, remove them now
	'

	Dim bSuccess
	bSuccess = True

	if (strToRemove <> "") then
		objDL.PutEx ADS_ATTR_DELETE, "dlMember", Split(strToRemove, DN_DELIM)
		if EchoError then
			bSuccess = False
		else
			objDL.SetInfo
			if EchoError then bSuccess = False
		end if
	end if

	'
	'	Display appropriate feedback
	'

	if (strToRemove = "") then
		wscript.echo L_NoMembersToRemove
	elseif (bSuccess) then
		wscript.echo L_MembersRemoved
	else
		wscript.echo L_FailedToRemoveMembers
	end if

	wscript.echo

	Set objDL = Nothing
    
End Sub


'------------------------------------------------------
'
' Function:     MemberStatus
' Purpose:      Returns status of a member.
'
'------------------------------------------------------
Function MemberStatus(strServer, strMemberDN, nCheckWhat)
    
	On Error Resume Next

	'
	'	Attempt to bind to object
	'

	Dim objMember
	Call BindToObject( FormADsPath( strServer, strMemberDN ), objMember, False ) 

	if err then

		if err = ERROR_OBJECT_NOT_FOUND or err = ERROR_INVALID_SYNTAX then
			MemberStatus = STATUS_NOT_FOUND
		else
			EchoError
			wscript.echo L_FailedToBindTo & strMemberDN & "!"
			MemberStatus = STATUS_FAIL
		end if

	else

		if nCheckWhat = CHECK_EXISTENCE then
			MemberStatus = STATUS_EXISTS
			set objMember = Nothing
			exit function
		end if

		Dim strAccountStatus

		strAccountStatus = objMember.Get("accountStatus")
		if err then
			if err = ERROR_PROPERTY_NOT_FOUND then
				MemberStatus = STATUS_NO_STATUS
			else
				EchoError
				wscript.echo L_FailedToGetStatusOf & strMemberDN & "!"
				MemberStatus = STATUS_FAIL
			end if
		else	
			if strAccountStatus = "4" then
				MemberStatus = STATUS_CANCELLED
			else
				MemberStatus = STATUS_ACTIVE
			end if
		end if

	end if

	set objMember = Nothing
	err.clear

End Function


'------------------------------------------------------
'
' Function:     AddRemoveDLMembers
' Purpose:      Adds/Removes members (that are listed in a
'				given text file) to/from a DL
'
'------------------------------------------------------
Sub AddRemoveDLMembers( strServer, strDL, strInputFile, nOper )

	On Error Resume Next

	'
	'	Open the input file for reading
	'

	Dim FileSystem
	Dim InStream

	set FileSystem = CreateObject("Scripting.FileSystemObject")
	if EchoError then exit sub

	set InStream = FileSystem.OpenTextFile( strInputFile )
	if EchoError then
		set FileSystem = Nothing
		exit sub
	end if

	'
	'	Bind to DL object
	'

	Dim objDL
	if NOT BindToObject( FormADsPath(strServer, strDL), objDL, True ) then exit sub


	'
	'	Call the appropriate function now
	'

	if nOper = OPER_ADD then
		AddMembersToDL InStream, objDL
	else
		RemoveMembersFromDL InStream, objDL
	end if


	'
	'	Cleanup
	'

	InStream.Close
	set InStream   = Nothing
	set FileSystem = Nothing

End Sub


'------------------------------------------------------
'
' Function:     AddMembersToDL
' Purpose:      Adds members (that are listed in a given
'				text file) to a DL.
'
' NOTE:  This function does not check for duplicates.  Nor
'		 does it check if each member really exists in the
'		 directory.
'
'------------------------------------------------------
Sub AddMembersToDL( InStream, objDL )

	On Error Resume Next
  
	Dim strNewMembers, strMemberDN

	'
	'	Concatenate all DNs.
	'

	strNewMembers = ""
    Do Until InStream.AtEndOfStream

		strMemberDN = InStream.ReadLine
		wscript.echo strMemberDN

		if strNewMembers <> "" then
			strNewMembers = strNewMembers & DN_DELIM & strMemberDN
		else
			strNewMembers = strMemberDN
		end if
	Loop

	'
	'	Add the members now.
	'

	objDL.PutEx ADS_ATTR_APPEND, "dlMember", Split( strNewMembers, DN_DELIM )
	if err then
		EchoError
		wscript.echo L_FailedToAddMembers
	else

		'
		'	Commit change.
		'
		objDL.SetInfo

		if err then
			EchoError
			wscript.echo L_FailedToAddMembers
		else
			wscript.echo 
			wscript.echo L_MembersAdded
		end if
	end if

End Sub


'------------------------------------------------------
'
' Function:     RemoveMembersFromDL
' Purpose:      Removes members (that are listed in a given
'				text file) from a DL.
'
'------------------------------------------------------
Sub RemoveMembersFromDL( InStream, objDL )
  
	On Error Resume Next
  
	Dim strMemberDN
	Do Until InStream.AtEndOfStream

		strMemberDN = InStream.ReadLine

		objDL.PutEx ADS_ATTR_DELETE, "dlMember", Array(strMemberDN)
		if err then
			ProcessStatus strMemberDN 
		else
			objDL.SetInfo
			ProcessStatus strMemberDN 
		end if

	Loop
 
End Sub


'------------------------------------------------------
'
' Function:     ProcessStatus
' Purpose:      Checks and echoes the status of the last 
'				operation.  Clears the error afterwards.
'
'------------------------------------------------------
Sub ProcessStatus( strText )

	Dim strOutput
	strOutPut = strText & " : "

	if err.number = 0 then
		strOutput = strOutput & L_Success
	else

		strOutput = strOutput & L_Failure & " : "

		select case err.number
			case ERROR_OBJECT_NOT_FOUND
				strOutput = strOutput & L_ObjectNotFound
			case ERROR_NOT_A_MEMBER
				strOutput = strOutput & L_NotAMember
			case else
				strOutput = strOutput & err.description & " (0x" & hex(err.number) & ")"
		end select

		err.clear

	end if

	wscript.echo strOutput

End Sub


'------------------------------------------------------
'
' Function:     RemoveUserFromAllDLs
' Purpose:      Removes specified user from all DLs.
'
'------------------------------------------------------
Sub RemoveUserFromAllDLs( strServer, strMemberDN )

	On Error Resume Next

	'	
	'	Get defaultNamingContext
	'

	Dim strDefaultNamingContext
	if NOT GetDefaultNamingContext( strServer, strDefaultNamingContext ) then
		exit sub
	end if


	'
	'	Establish connection
	'

	Dim Connection

	set Connection = CreateObject("ADODB.Connection")
	if EchoError then exit sub

	Connection.Provider = "ADsDSOObject"
	Connection.Open "ADS Provider", g_strAccountName, g_strPassword
	if EchoError then exit sub


	'
	'	Form query string to find all DLs of which the user is a member.
	'  

	Dim strQueryString, strDistListContainerPath
	strDistListContainerPath = FormADsPath( strServer, "ou=distributionLists," & strDefaultNamingContext )
	strQueryString = "<" & strDistListContainerPath & ">;(dlmember=" & strMemberDN & ");adspath,dlmember;subtree"
	
	'
	'	Execute query
	'

	Dim Recordset
	set Recordset = Connection.Execute( strQueryString )
	if EchoError then exit sub


	if NOT Recordset.EOF then

		'
		'	Remove the user from each DL in the result set.
		'

		Dim strDLPath
		do until Recordset.EOF

			strDLPath = Recordset.Fields("adspath")

			RemoveUserFromDL strMemberDN, strDLPath
			ProcessStatus strDLPath
		
			Recordset.MoveNext

		loop

	else

		'
		'	User does not belong to any DL
		'

		wscript.echo L_NoDL	
		wscript.echo

	end if


	'
	'   Clean up
	'

	Set Recordset = Nothing
	Set Connection = Nothing
  
End Sub


'------------------------------------------------------
'
' Function:     RemoveUserFromDL
' Purpose:      Removes specified user from specified DL.
'
'------------------------------------------------------
Sub RemoveUserFromDL( strMemberDN, strDLPath )
  
	On Error Resume Next

	'
	'	Bind to DL object
	'
	
	Dim objDL
	if NOT BindToObject( strDLPath, objDL, False ) then exit sub

	'
	'	Delete the member
	'
	objDL.PutEx ADS_ATTR_DELETE, "dlMember", Array(strMemberDN)
	if err then
		set objDL = Nothing
		exit sub
	end if

	objDL.SetInfo
	set objDL = Nothing

End Sub


'------------------------------------------------------
'
' Function:     CountUsersInAllDLs
' Purpose:      Counts the users in each DL.
'
'------------------------------------------------------
Sub CountUsersInAllDLs( strServer )

	On Error Resume Next

	'	
	'	Get defaultNamingContext
	'

	Dim strDefaultNamingContext
	if NOT GetDefaultNamingContext( strServer, strDefaultNamingContext ) then
		exit sub
	end if


	'
	'	Establish connection
	'

	Dim Connection

	set Connection = CreateObject("ADODB.Connection")
	if EchoError then exit sub

	Connection.Provider = "ADsDSOObject"
	Connection.Open "ADS Provider", g_strAccountName, g_strPassword
	if EchoError then exit sub


	'
	'	Form query string for finding all the DLs in the directory
	'  

	Dim strQueryString, strDistListContainerPath
	strDistListContainerPath = FormADsPath( strServer, "ou=distributionLists," & strDefaultNamingContext )
	strQueryString = "<" & strDistListContainerPath & ">;(objectClass=distributionList);adspath;subtree"
	

	'
	'	Execute query
	'
	Dim Recordset
	set Recordset = Connection.Execute( strQueryString )
	if err then exit sub

	
	Dim nNumDirect, nNumIndirect, nTotal, nNumErr


	'
	'	Count users in each DL in the result set.
	'

	Dim strDLPath
	do until Recordset.EOF
		strDLPath = Recordset.Fields("adspath")

		wscript.echo strDLPath
		nTotal = CountUsersInDL( strServer, strDLPath, nNumDirect, nNumIndirect, nNumErr )
		if nTotal >= 0 then
			wscript.echo L_NumDirectUsers & nNumDirect
			wscript.echo L_NumIndirectUsers & nNumIndirect
			wscript.echo L_TotalUsers & nTotal
			wscript.echo L_NumErrors & nNumErr
		else
			wscript.echo L_FailedToCountUsers
			wscript.echo
		end if

		Recordset.MoveNext
	loop


	'
	'   Clean up
	'

	Set Recordset = Nothing
	Set Connection = Nothing
	
End Sub


'------------------------------------------------------
'
' Function:     CountUsersInDL
' Purpose:      Counts the users in the specified DL.
'
' IMPORTANT NOTE:
'
'   This function uses recursion to handle nested distribution
'   lists and does not verify that there is enough memory to
'   complete the task.  Very large distribution lists or many
'   nested distribution lists may cause this function to fail.
'   This function does not check for or handle cyclical references.
'------------------------------------------------------
Function CountUsersInDL( strServer, strDLPath, nNumDirect, nNumIndirect, nNumErr )
  
	On Error Resume Next


	'
	'	Initialize return value to -1 (which means failure).
	'

	CountUsersInDL = -1


	'
	'	Initialize counters
	'  

	Dim nTotal
	nNumDirect	 = 0
	nNumIndirect = 0
	nTotal		 = 0
	nNumErr		 = 0

	'
	'	Bind to DL object.
	'

	Dim objDL
	if NOT BindToObject( strDLPath, objDL, True ) then exit function
  

	'
	'	Get its dlMember attribute
	'

	Dim arrMembers
	arrMembers = objDL.get("dlMember")


	'
	'	If not present, exit procedure
	'

	if err = ERROR_PROPERTY_NOT_FOUND then 
		CountUsersInDL = 0
		set objDL = Nothing
		exit function
	end if


	'
	'	On other errors, display error and exit procedure
	'

	if EchoError then 
		set objDL = Nothing
		exit function
	end if


	'
	'	If dlMember has only one value, make it into an array
	'

	if NOT IsArray( arrMembers ) then arrMembers = Array( arrMembers )

	

	Dim nDummy, nTempTotal, nTempNumErr
	Dim strMemberDN
  
    For Each strMemberDN In arrMembers

		'
		' If member is another distribution list, count its users, too.
		'

		If InStr( LCase(strMemberDN), "ou=distributionlists" ) > 0 Then

			nTempTotal = CountUsersInDL( strServer, FormADsPath( strServer, strMemberDN ), nDummy, nDummy, nTempNumErr )

			'
			'	if successful, update "indirect users" count.
			'
			If nTempTotal >= 0 Then
				nNumIndirect = nNumIndirect + nTempTotal
				nTotal = nTotal + nTempTotal
				nNumErr = nNumErr + nTempNumErr
			else
				nNumErr = nNumErr + 1
			End If

		'
		'	Else, member is a user.  Update the "direct users" count.
		'

		Else
			nNumDirect = nNumDirect + 1
			nTotal = nTotal + 1
		End If

    Next

	CountUsersInDL = nTotal
  
	'
	'   Clean up
	'

	set objDL = Nothing

End Function


'------------------------------------------------------
'
' Function:     DiagnoseDL
' Purpose:      Dumps the e-mail addresses and GUIDs of
'				a DL's members.
'
'------------------------------------------------------
Sub DiagnoseDL( strServer, strDLDN )
  
	On Error Resume Next


	'
	'	Bind to DL object.
	'

	Dim objDL
	if NOT BindToObject( FormADsPath( strServer, strDLDN ), objDL, True ) then exit sub
  

	'
	'	Get its dlMember attribute
	'

	Dim arrMembers
	arrMembers = objDL.get("dlMember")


	'
	'	If not present, either it has no
	'	members or user has no access to them.
	'

	if err = ERROR_PROPERTY_NOT_FOUND then 
		wscript.echo L_NoMembers
		set objDL = Nothing
		exit sub
	end if


	'
	'	On other errors, display error and exit procedure
	'

	if EchoError then 
		set objDL = Nothing
		exit sub
	end if


	'
	'	If dlMember has only one value, make it into an array
	'

	if NOT IsArray( arrMembers ) then arrMembers = Array( arrMembers )


	'
	'	Bind to each member to get its e-mail address and GUID (if member is a user).
	'
	
	Dim strMemberDN
	Dim objMember
	Dim strObjectClass, strMail, strGUID
	Dim bProceed
  
    For Each strMemberDN In arrMembers

		'
		'	Bind to member object
		'
		
		if BindToObject( FormADsPath( strServer, strMemberDN ), objMember, False ) then

			bProceed = True

			'
			'	Get its objectClass
			'

			strObjectClass = objMember.Get("objectClass")
			if err = 0 then

				'
				'	If no error getting objectClass,
				'	get its mail attribute.
				'

				strMail	= objMember.Get("mail")

				'
				'	If property not found, either
				'	it has no mail, or user has no
				'	access to it
				'
				if err = ERROR_PROPERTY_NOT_FOUND then
					strMail = L_NoEmail

				'
				'	On all other errors, output error
				'	and skip this member.
				'
				elseif err <> 0 then
					ProcessStatus strMemberDN
					bProceed = False
				end if


				'
				'	If no error getting mail (apart from property not found)
				'	and the member is a user, get its GUID attribute
				'
				strGUID = ""
				if bProceed and LCase(strObjectClass) = "member" then

					err.clear
					strGUID = objMember.Get("guid")

					'
					'	If property not found, either it has
					'	no GUID or user has no access to it
					'
					if err = ERROR_PROPERTY_NOT_FOUND then
						strGUID = L_NoGUID

					'
					'	On all other errors, output error
					'	and skip this member.
					'
					elseif err <> 0 then
						ProcessStatus strMemberDN
						bProceed = False
					end if
				end if

				'
				'	If everything went fine,
				'	dump this object's class, DN, e-mail and GUID (if not empty)
				'
				if bProceed then
					Dim strOutput
					strOutput = strObjectClass & " : " & strMemberDN & " : " & strMail
					if strGUID <> "" then strOutput = strOutput & " : " & strGUID
					wscript.echo strOutput
				end if

			'
			'	If we failed to get the objectClass,
			'	output error and skip this member.
			'
			else
				ProcessStatus strMemberDN
			end if

			'
			'	Free member object
			'

			set objMember = Nothing					
			
		'
		'	If we failed to bind to the member object,
		'	output error and skip this member.
		'
		else
			
			ProcessStatus strMemberDN

		end if

		'
		'	Clear error for next iteration
		'
		err.clear

	Next

			 
	'
	'   Clean up
	'

	set objDL = Nothing

End Sub
