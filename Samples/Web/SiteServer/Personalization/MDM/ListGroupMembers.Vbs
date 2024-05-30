' ====================================================================
' FILE:	ListGroupMembers.VBS
'
' PARAMETERS:
'		/H		Server:Port
'		/U		User DN (optional)
'		/P		User password (optional)
'		/G		DN of group whose members you want to be listed
'		/USR	If specified, will list the USER members of the group
'		/GRP	If specified, will list the GROUP members of the group
'		/S		Silent mode (useful if you only want the count)
'		/?		Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'		/USR and /GRP are mutually exclusive.
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This lists the USER or GROUP members of a group, depending on
'		which option is specified.
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
const L_swServer					= "/H"
const L_swAccountName				= "/U"
const L_swPassword					= "/P"
const L_swGroupDN					= "/G"
const L_swUserFlag					= "/USR"
const L_swGroupFlag					= "/GRP"
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "LIST GROUP MEMBERS"
const L_TimeExecuted				= "Time Executed: "
const L_optServer					= "Server       : "
const L_optAccountName				= "User         : "
const L_optPassword					= "Password     : "
const L_optGroupDN					= "Group DN     : "
const L_optMemberType				= "Which Members: "
const L_optSilent					= "Silent       : "

' member types
const L_memberUsers					= "Users"
const L_memberGroups				= "Groups"

' status information
const L_Error						= "Error: "

' specific error messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."

' statistics
const L_Statistics					= "STATISTICS"
const L_NumMembers					= "Member count: "

'------------------------------------------------------
' Constants
'------------------------------------------------------

const OBJECT_NOT_FOUND = &H80070002

' Default values for the arguments
const def_strAccountName	= ""
const def_strPassword		= ""
const def_blnSilent			= false

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_strGroupDN
Dim g_blnListUsers
Dim g_blnSilent

Dim g_intNumMembers

'------------------------------------------------------
'
' Function:     EchoHeader
' Purpose:      Echoes script information and
'				options selected (whether or not
'				we are in silent mode)
'
'------------------------------------------------------
Sub EchoHeader
	
	wscript.echo L_Title
	wscript.echo 
	wscript.echo L_TimeExecuted & Now
	wscript.echo L_optServer & g_strServer
	wscript.echo L_optAccountName & g_strAccountName
	wscript.echo L_optGroupDN & g_strGroupDN
	
	if g_blnListUsers then
		wscript.echo L_optMemberType & L_memberUsers
	else
		wscript.echo L_optMemberType & L_memberGroups
	end if

	wscript.echo L_optSilent & g_blnSilent
	wscript.echo

End Sub


'------------------------------------------------------
'
' Function:     EchoStatistics
' Purpose:      Echoes some statistics at the end of
'				the script
'
'------------------------------------------------------
Sub EchoStatistics

	wscript.echo
	wscript.echo L_Statistics	
	wscript.echo L_NumMembers   & g_intNumMembers
	
End Sub


'------------------------------------------------------
'
' Function:     EchoUsage (LOCALIZABLE!!!)
' Purpose:      Echoes correct usage of script.
'
'------------------------------------------------------
Sub EchoUsage
	
	wscript.echo L_Title
	wscript.echo

	wscript.echo "Recognized Arguments (case-insensitive):"
	wscript.echo

	wscript.echo L_swServer      & "   " & "Server:Port"
	wscript.echo L_swAccountName & "   " & "User DN (optional)"
	wscript.echo L_swPassword    & "   " & "User password (optional)"
	wscript.echo

	wscript.echo L_swGroupDN	 & "   " & "DN of group whose members you want to be listed"
	wscript.echo L_swUserFlag	 & " "   & "Flag to list the user members of the group"
	wscript.echo L_swGroupFlag   & " "   & "Flag to list the group members of the group"
	wscript.echo

	wscript.echo L_swSilent		 & "   " & "Silent mode (useful if you only want the count)"
	wscript.echo L_swHelp		 & "   " & "Displays this help message"

End Sub


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
	g_blnSilent			= def_blnSilent

	g_strServer			= ""
	g_strGroupDN		= ""

	Dim intNumTypeSpecified
	intNumTypeSpecified = 0

	Dim Arg
	Dim strSwitch

	strSwitch = ""
	for each Arg in wscript.Arguments
		if (strSwitch = "") then

			strSwitch = UCase( Arg )

			Select Case strSwitch
				Case L_swHelp
					EchoUsage
					exit function
				Case L_swSilent
					g_blnSilent = true
					strSwitch = ""
				Case L_swUserFlag
					g_blnListUsers = true
					intNumTypeSpecified = intNumTypeSpecified + 1
					strSwitch = ""
				Case L_swGroupFlag
					g_blnListUsers = false
					intNumTypeSpecified = intNumTypeSpecified + 1
					strSwitch = ""
			End Select

		else
			Select Case strSwitch
				Case L_swServer
					g_strServer					= Arg
				Case L_swAccountName
					g_strAccountName			= Arg
				Case L_swPassword
					g_strPassword				= Arg
				Case L_swGroupDN
					g_strGroupDN				= Arg
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory arguments:
	'	server, group DN and member type (number of member type specified should
	'			   				          be exactly one)
	'
	if g_strServer = "" or g_strGroupDN = "" or intNumTypeSpecified <> 1 then
		EchoUsage
		exit function
	end if

	GetArguments = true

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
		wscript.echo L_Error & err.description & " (0x" & hex(err.number) & ")"
		EchoError = true
	else
		EchoError = false
	end if

End Function


'------------------------------------------------------
'
' Function:     FormatGeneralizedTime
' Purpose:      Formats a GeneralizedTime expression
'				for display.
'				
'------------------------------------------------------

Function FormatGeneralizedTime( strGenTime )

	Dim dtDate

	dtDate = DateSerial( CInt( Left( strGenTime, 4 ) ), _
						 CInt( Mid ( strGenTime, 5, 2 ) ), _
						 CInt( Mid ( strGenTime, 7, 2 ) ) )

	FormatGeneralizedTime = FormatDateTime( dtDate, 2 )

End Function


'------------------------------------------------------
'
' Function:     BindToObject
' Purpose:      Binds to object specified by the
'				supplied path.
'
'------------------------------------------------------
Function BindToObject( strPath, obj )

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
		blnError = EchoError

		set objLDAP = Nothing

		if blnError then exit function

	else

		set obj = GetObject( strPath )
		if EchoError then exit function

	end if

	BindToObject = true

End Function


'------------------------------------------------------
'
' Function:     ListMembers
' Purpose:      Main function that lists/counts the 
'				members of the group.
'
'------------------------------------------------------
Sub ListMembers

	On Error Resume Next

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
	'	Setup appropriate objectClass and referencing DN to look up.
	'

	Dim strObjectClass, strReferenceDN

	if g_blnListUsers then
		strObjectClass = "memberOf"
		strReferenceDN = "memberObject"
	else 
		strObjectClass = "groupMemberOf"
		strReferenceDN = "groupObject"
	end if


	'
	'	Form query string
	'

	Dim strGroupPath, strFilter, strAttributes, strQueryString

	strGroupPath  = "LDAP://" & g_strServer & "/" & g_strGroupDN
	strFilter     = "(objectClass=" & strObjectClass & ")"
	strAttributes = strReferenceDN	' we only want to get the memberObject or groupObject attribute

	strQueryString = "<" & strGroupPath & ">" & ";" & strFilter & ";" & strAttributes & ";onelevel"


	'
	'	Execute query
	'

	Dim Recordset
	set Recordset = Connection.Execute( strQueryString )
	if EchoError then exit sub

	g_intNumMembers = 0


	'
	'	List each member in result set
	'

	do until Recordset.EOF 
		g_intNumMembers = g_intNumMembers + 1
		if NOT g_blnSilent then wscript.echo Recordset.Fields( strReferenceDN )	
		Recordset.MoveNext	
	loop

	Connection.Close
	set Connection = Nothing

End Sub


'------------------------------------------------------
'
' Main routine
'
'------------------------------------------------------

if GetArguments then
	EchoHeader
	ListMembers
	EchoStatistics
end if


