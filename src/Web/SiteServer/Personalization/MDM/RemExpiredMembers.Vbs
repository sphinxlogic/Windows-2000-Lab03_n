' ====================================================================
' FILE:	RemoveExpiredMembers.VBS
'
' PARAMETERS:
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/C	DN of container or group
'		/S  Silent mode (will not display status of each operation)
'		/?  Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'		If the DN following /C is that of a group, the script will
'		remove the members of that group whose memberships have expired
'		or are expiring today.  If the DN is that of a container, it
'		will remove the expiring members of all the groups underneath
'		the container.
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This script removes the members of a group or of all the groups under
'		a container whose memberships have expired or are expiring today.
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
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "REMOVE EXPIRED MEMBERSHIPS"
const L_TimeExecuted				= "Time Executed     : "
const L_optServer					= "Server            : "
const L_optAccountName				= "User              : "
const L_optPassword					= "Password          : "
const L_optBaseDN					= "Container/Group DN: "
const L_optSilent					= "Silent            : "

' status information
const L_Error						= "Error: "
const L_Success						= "Success"
const L_Failure						= "Failure"

' specific error messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."

' statistics
const L_Statistics					= "STATISTICS"
const L_NumUsers					= "User count   : "
const L_NumSuccess					= "Success count: "
const L_NumFailure					= "Failure count: "

'------------------------------------------------------
' Constants
'------------------------------------------------------

const OBJECT_NOT_FOUND = &H80070002

' Default values for the arguments
const def_strAccountName			= ""
const def_strPassword				= ""
const def_strBaseDN					= "ou=groups,"			'the o=<org> part is appended later in the code
const def_blnSilent					= false

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_strBaseDN
Dim g_blnSilent

Dim g_strBasePath

Dim g_strQueryString
Dim g_intNumUsers
Dim	g_intNumSuccess
Dim	g_intNumFailure

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
	wscript.echo L_NumUsers   & g_intNumUsers
	wscript.echo L_NumSuccess & g_intNumSuccess
	wscript.echo L_NumFailure & g_intNumFailure
	
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

	wscript.echo L_swServer      & " " & "Server:Port"
	wscript.echo L_swAccountName & " " & "User DN (optional)"
	wscript.echo L_swPassword    & " " & "User password (optional)"
	wscript.echo

	wscript.echo L_swBaseDN	     & " " & "DN of container or group"
	wscript.echo

	wscript.echo L_swSilent		 & " " & "Silent mode (will not display status of each operation)"
	wscript.echo L_swHelp		 & " " & "Displays this help message"

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
	g_strAccountName = def_strAccountName			
	g_strPassword	 = def_strPassword				
	g_strBaseDN		 = def_strBaseDN
	g_blnSilent		 = def_blnSilent

	g_strServer		 = ""

	Dim Arg
	Dim strSwitch

	strSwitch = ""
	for each Arg in wscript.Arguments
		if (strSwitch = "") then

			strSwitch = UCase( Arg )

			if (strSwitch = L_swHelp) then
				EchoUsage
				exit function
			end if

			if (strSwitch = L_swSilent) then
				g_blnSilent = true
				strSwitch = ""
			end if

		else
			Select Case strSwitch
				Case L_swServer
					g_strServer					= Arg
				Case L_swAccountName
					g_strAccountName			= Arg
				Case L_swPassword
					g_strPassword				= Arg
				Case L_swBaseDN
					g_strBaseDN					= Arg
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory Argument:  server
	'
	if g_strServer = "" then
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
' Function:     GetZeroPaddedString
' Purpose:      Accepts a number and returns its
'				string representation that is zero-padded
'				such that its length equals the
'				specified target length
'
'------------------------------------------------------

Function GetZeroPaddedString( nNumber, nTargetLen )

	Dim strZeroPaddedString
	
	strZeroPaddedString = nNumber
	do while (Len( strZeroPaddedString ) < nTargetLen)
		strZeroPaddedString = "0" & strZeroPaddedString
	loop

	GetZeroPaddedString = strZeroPaddedString

End Function


'------------------------------------------------------
'
' Function:     TodayInGeneralizedTimeFormat
' Purpose:      Returns today's date 
'				in GeneralizedTime format
'				(i.e. YYYYMMDD2359Z)
'				It actually returns the last second
'				(23:59) of today so that all memberships
'				expiring today (no matter what time) will
'				be deleted.  Group membership expiration
'				is not time-sensitive.
'
'------------------------------------------------------

Function TodayInGeneralizedTimeFormat()

	TodayInGeneralizedTimeFormat = _
				GetZeroPaddedString( Year( Date ), 4 ) & _
				GetZeroPaddedString( Month( Date ), 2 ) & _
				GetZeroPaddedString( Day( Date ), 2 ) & _
				"2359Z"
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
' Function:     ProcessStatus
' Purpose:      Checks status of last operation.  Updates
'				the appropriate counter and if not in silent 
'				mode, echoes the status.  Clears the
'				error afterwards.
'				(This assumes that the format of the
'				strMemberOfPath is: 
'				LDAP://host:port/cn=<guid>,ou=groupname,...,ou=groups,o=<org>)
'
'------------------------------------------------------
Sub ProcessStatus( strMemberOfPath, strMemberDN, strExpirationDate )

	'
	' update appropriate counter
	'
	if err.number = 0 then
		g_intNumSuccess = g_intNumSuccess + 1
	else
		g_intNumFailure = g_intNumFailure + 1
	end if

	'
	' if not in silent mode, echo status
	'
	if not g_blnSilent then

		'
		'	Extract the group DN from the strMemberOfPath
		'	e.g. LDAP://localhost:1003/cn=<guid>,cn=groupname,ou=groups,o=microsoft
		'	The group DN would be:  cn=groupname,ou=groups,o=microsoft
		'
		Dim strGroupDN
		Dim nCommaPos

		nCommaPos = InStr( strMemberOfPath, "," )
		strGroupDN = Right( strMemberOfPath, Len( strMemberOfPath ) - nCommaPos )


		Dim strOutput
		strOutPut = strGroupDN & " : " & strMemberDN & " : " & FormatGeneralizedTime( strExpirationDate ) & " : "

		if err.number = 0 then
			strOutput = strOutput & L_Success
		else

			strOutput = strOutput & L_Failure & " : "

			select case err.number
				case OBJECT_NOT_FOUND
					strOutput = strOutput & L_ObjectNotFound
				case else
					strOutput = strOutput & err.description & " (0x" & hex(err.number) & ")"
			end select

			err.clear

		end if

		wscript.echo strOutput

	end if 

End Sub

'------------------------------------------------------
'
' Function:     FormQueryString
' Purpose:      Forms the query string for the search
'
'------------------------------------------------------

Sub FormQueryString

	On Error Resume Next

	g_strQueryString = ""

	Dim strRootDSEPath
	Dim strDefaultNamingContext
	Dim objRootDSE

	'
	'	Get default naming context (o=<organization>)
	'
    strRootDSEPath = "LDAP://" & g_strServer & "/rootDSE"   
    Set objRootDSE = GetObject( strRootDSEPath )
	if EchoError then exit sub
    
    strDefaultNamingContext = objRootDSE.Get("defaultNamingContext")
	if EchoError then exit sub

	set objRootDSE = Nothing

	'
	'	If no base DN is specified, then append the default naming context to g_strBaseDN
	'
	if (g_strBaseDN = def_strBaseDN) then
		g_strBaseDN = g_strBaseDN & strDefaultNamingContext
	end if

	'
	'	Form the Base Path
	'
	g_strBasePath = "LDAP://" & g_strServer & "/" & g_strBaseDN

	'
	'	Form the filter string
	'
	Dim strFilter 
	strFilter = "(&(objectclass=memberof)(expiration<=" & TodayInGeneralizedTimeFormat & "))"

	'
	'	Attributes - list of attributes we want returned
	'
	Dim strAttributes
	strAttributes = "adspath,expiration,memberObject"

	'
	'	Scope - allows us to either do a subtree or a one-level search
	'
	Dim strScope
	strScope = "subtree"

	'	
	'	Form the query string now
	'	(Format:  <ADsPath>;filter;attribute-list;scope)
	'
	g_strQueryString = "<" & g_strBasePath & ">" & ";" & strFilter & ";" & strAttributes & ";" & strScope

End Sub


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
' Function:     GetRelativePath
' Purpose:      Given a full ADsPath, this extracts the
'				path relative to the base DN.
'
'				This assumes that the format of the
'				ADSPath is: 
'				LDAP://host:port/cn=memberofguid,...,<baseDN>
'
'				e.g. Given the following full path:
'				LDAP://localhost:1003/cn=<guid>,...,<baseDN>
'				Relative path would be:  "cn=<guid>,.."
'
'------------------------------------------------------

Function GetRelativePath( strFullPath )

	Dim nPos
	Dim strRelativePath

	' Remove the "LDAP://host:port/" part
	strRelativePath = GetDN( LCase(strFullPath) )

	' Remove the base DN part
	nPos = InstrRev( strRelativePath, LCase(g_strBaseDN) )
	GetRelativePath = Left( strRelativePath, nPos - 2 )

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
' Function:     RemoveExpiredMembers
' Purpose:      Main function that does the search
'				and deletion of expired group memberships
'
'------------------------------------------------------
Sub RemoveExpiredMembers

	On Error Resume Next

	if (g_strQueryString = "") then exit sub

	g_intNumUsers	= 0
	g_intNumSuccess = 0
	g_intNumFailure = 0

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
	'	Execute query
	'
	Dim Recordset
	set Recordset = Connection.Execute( g_strQueryString )
	if EchoError then exit sub


	'
	'	Bind to the base object
	'

	Dim objBase
	if NOT BindToObject( g_strBasePath, objBase ) then exit sub


	'
	'	Delete each object in the result set
	'	

	Dim strMemberOfPath, strMemberDN, strRelativePath
	Dim dtExpiration

	do until Recordset.EOF 

		g_intNumUsers = g_intNumUsers + 1

		' Get DN of member and expiration date of the memberOf object
		strMemberDN = Recordset.Fields("memberObject")
		dtExpiration = Recordset.Fields("expiration")

		' Get path of memberOf object relative to that of the base object
		strMemberOfPath = Recordset.Fields("adspath")
		wscript.echo strMemberOfPath
		strRelativePath = GetRelativePath( strMemberOfPath )

		' Delete member
		objBase.Delete "memberOf", strRelativePath

		ProcessStatus strMemberOfPath, strMemberDN, dtExpiration

		Recordset.MoveNext	

	loop

	set objBase = Nothing

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
	FormQueryString
	RemoveExpiredMembers
	EchoStatistics
end if


