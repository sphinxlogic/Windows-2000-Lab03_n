' ====================================================================
' FILE:	ListChildren.VBS
'
' PARAMETERS:
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/C	DN of container whose children you want to be listed
'		/F  Filter string to limit the search (optional)
'		/OL If specified, it will do a one-level search under the container
'		/ST If specified, it will do a subtree search under the container
'		/S	Silent mode (useful if you only want the count)
'		/?  Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'		/F allows listing of only those objects that satisfy certain
'		criteria.
'
'		/OL and /ST are mutually exclusive.
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This script lists the (grand)children of the specified container.
'		The output may be redirected to a file that may then be used as
'		input to other scripts that require an input file containing a 
'		list of DNs.
'
' SAMPLE USES
'
'		Here are some samples uses of the script.  The arguments below
'		can of course be changed to tailor to what you really need.  For
'		example, you can restrict the search to only those under a 
'		particular organizational unit by specifying the DN of that
'		unit after /C.  You can narrow down the search to only those
'		satisfying certain criteria by adding those criteria to the filter
'		string.  You can specify /S if you only want the count. 
'
'		LISTING/COUNTING THE USERS IN THE DS
'
'		cscript ListChildren.vbs /H <server:port> /C ou=members,o=myorg 
'								 /F objectClass=member /ST [/S]
'
'		LISTING/COUNTING THE GROUPS IN THE DS
'
'		cscript ListChildren.vbs /H <server:port> /C ou=groups,o=myorg
'								 /F objectClass=mgroup /ST [/S]
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
const L_swBaseDN					= "/C"
const L_swFilter					= "/F"
const L_swOneLevel					= "/OL"
const L_swSubtree					= "/ST"
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "LIST CHILDREN"
const L_TimeExecuted				= "Time Executed: "
const L_optServer					= "Server       : "
const L_optAccountName				= "User         : "
const L_optPassword					= "Password     : "
const L_optBaseDN					= "Container    : "
const L_optFilter					= "Filter       : "
const L_optScope					= "Search Scope : "
const L_optSilent					= "Silent       : "

' search scopes
const L_scopeOneLevel				= "One-level"
const L_scopeSubtree				= "Subtree"

' status information
const L_Error						= "Error: "

' specific error messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."

' statistics
const L_Statistics					= "STATISTICS"
const L_NumChildren					= "Child count: "

'------------------------------------------------------
' Constants
'------------------------------------------------------

const OBJECT_NOT_FOUND = &H80070002

' Default values for the arguments
const def_strAccountName	= ""
const def_strPassword		= ""
const def_strFilter			= "(objectClass=*)"
const def_blnSilent					= false

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_strBaseDN
Dim	g_strFilter
Dim g_blnOneLevel
Dim g_blnSilent

Dim g_intNumChildren

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
	wscript.echo L_optBaseDN & g_strBaseDN
	wscript.echo L_optFilter & g_strFilter
	
	if g_blnOneLevel then
		wscript.echo L_optScope & L_scopeOneLevel
	else
		wscript.echo L_optScope & L_scopeSubtree
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
	wscript.echo L_NumChildren   & g_intNumChildren
	
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

	wscript.echo L_swServer      & "  " & "Server:Port"
	wscript.echo L_swAccountName & "  " & "User DN (optional)"
	wscript.echo L_swPassword    & "  " & "User password (optional)"
	wscript.echo

	wscript.echo L_swBaseDN		 & "  " & "DN of container"
	wscript.echo L_swFilter	     & "  " & "Filter to limit search (optional)"
	wscript.echo

	wscript.echo L_swOneLevel	 & " "  & "Flag to do one-level search"
	wscript.echo L_swSubtree     & " "  & "Flag to do subtree search"
	wscript.echo

	wscript.echo L_swSilent		 & "  " & "Silent mode (useful if you only want the count)"
	wscript.echo L_swHelp		 & "  " & "Displays this help message"

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
	g_strFilter			= def_strFilter
	g_blnSilent					= def_blnSilent

	g_strServer			= ""
	g_strBaseDN			= ""

	Dim intNumScopeSpecified
	intNumScopeSpecified = 0

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
				Case L_swOneLevel
					g_blnOneLevel = true
					intNumScopeSpecified = intNumScopeSpecified + 1
					strSwitch = ""
				Case L_swSubtree
					g_blnOneLevel = false
					intNumScopeSpecified = intNumScopeSpecified + 1
					strSwitch = ""
			End Select

		else
			Select Case strSwitch
				Case L_swServer
					g_strServer			= Arg
				Case L_swAccountName
					g_strAccountName	= Arg
				Case L_swPassword
					g_strPassword		= Arg
				Case L_swBaseDN
					g_strBaseDN			= Arg
				Case L_swFilter			
					g_strFilter			= Arg
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory arguments:
	'	server, base DN and search scope (number of search scope specified should
	'							          be exactly one)
	'
	if g_strServer = "" or g_strBaseDN = "" or intNumScopeSpecified <> 1 then
		EchoUsage
		exit function
	end if

	'	
	'	Enclose filter string in parentheses, if not yet
	'

	if (Left( g_strFilter, 1 ) <> "(") then
		g_strFilter = "(" & g_strFilter & ")"
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
' Function:     GetDN
' Purpose:      Given a full ADsPath, this extracts the	DN part.
'
'				This assumes that the format of the
'				ADSPath is: LDAP://host:port/<rdn>=objname,...,o=<org>
'
'				e.g. Given the following full path:
'				LDAP://localhost:1003/cn=user1,ou=members,o=microsoft
'				The DN would be:  cn=user1,ou=members,o=microsoft
'
'				It also assumes that object names do not have any embedded
'				forward slashes ("/").
'
'------------------------------------------------------

Function GetDN( strFullPath )

	Dim nForwardSlashPos

	nForwardSlashPos = InstrRev( strFullPath, "/" )
	GetDN = Right( strFullPath, Len( strFullPath ) - nForwardSlashPos )

End Function


'------------------------------------------------------
'
' Function:     ListChildren
' Purpose:      Main function that lists/counts the 
'				(grand)children of the container.
'
'------------------------------------------------------
Sub ListChildren

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
	'	Setup appropriate search scope
	'

	Dim strScope

	if g_blnOneLevel then
		strScope = "onelevel"
	else 
		strScope = "subtree"
	end if


	'
	'	Form query string
	'

	Dim strBasePath, strQueryString

	strBasePath   = "LDAP://" & g_strServer & "/" & g_strBaseDN
	strQueryString = "<" & strBasePath & ">" & ";" & g_strFilter & ";adspath;" & strScope


	'
	'	Execute query
	'

	Dim Recordset
	set Recordset = Connection.Execute( strQueryString )
	if EchoError then exit sub

	g_intNumChildren = 0


	'
	'	List each object in result set
	'

	do until Recordset.EOF 
		g_intNumChildren = g_intNumChildren + 1
		if NOT g_blnSilent then wscript.echo GetDN( Recordset.Fields( "adspath" ) )	
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
	ListChildren
	EchoStatistics
end if


