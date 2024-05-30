' ====================================================================
' FILE:	AddRemGroupMembers.VBS
'
' PARAMETERS:
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/G	DN of group that you want to add to or remove from
'		/I  Input file containing list of DNs of users to be added/removed
'		/E	Expiration date for new members (optional)
'		/+  If specified, the users will be added to the group
'		/-  If specified, the users will removed from the group
'		/S  Silent mode (will not display status of each operation)
'		/?  Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'		The input file must be of the right format, i.e. one DN to a line.
'		Blank or empty lines are ignored.
'
'		/+ and /- are mutually exclusive.
'
'		The expiration date is meaningful only if /+ is specified.  If not
'		specified, the new members will have no expiration.
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This script adds/removes user members to/from a group.
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
const L_swInputFile					= "/I"
const L_swExpiration				= "/E"
const L_swAddFlag					= "/+"
const L_swRemoveFlag				= "/-"
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "ADD/REMOVE GROUP MEMBERS"
const L_TimeExecuted				= "Time Executed: "
const L_optServer					= "Server       : "
const L_optAccountName				= "User         : "
const L_optPassword					= "Password     : "
const L_optGroupDN					= "Group DN     : "
const L_optInputFile				= "Input File   : "
const L_optExpiration				= "Expiration   : "
const L_optOperation				= "Operation    : "
const L_optSilent					= "Silent       : "

' operations
const L_operAdd						= "Add"
const L_operRemove					= "Remove"

' status information
const L_Error						= "Error: "
const L_Success						= "Success"
const L_Failure						= "Failure"

' specific error messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."
const L_AlreadyAMember				= "Already a member."
const L_FailedToGetGuidGenObject	= "Failed to get GuidGen object."
const L_NotAMember					= "Not a member."

' statistics
const L_Statistics					= "STATISTICS"
const L_NumUsers					= "User count   : "
const L_NumSuccess					= "Success count: "
const L_NumFailure					= "Failure count: "

'------------------------------------------------------
' Constants
'------------------------------------------------------

const OBJECT_NOT_FOUND = &H80070002
const ALREADY_EXISTS   = &H800700B7	

' Default values for the arguments
const def_strAccountName			= ""
const def_strPassword				= ""
const def_strExpiration				= Null
const def_blnSilent					= false

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_strGroupDN
Dim g_strInputFile
Dim g_strExpiration
Dim g_blnAdd
Dim g_blnSilent

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
	wscript.echo L_optGroupDN & g_strGroupDN
	wscript.echo L_optInputFile & g_strInputFile

	Dim strExpiration
	strExpiration = L_optExpiration
	if not IsNull( g_strExpiration ) then
		strExpiration = strExpiration & FormatGeneralizedTime( g_strExpiration )
	end if

	wscript.echo strExpiration

	if g_blnAdd then
		wscript.echo L_optOperation & L_operAdd
	else
		wscript.echo L_optOperation & L_operRemove
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

	wscript.echo L_swGroupDN	 & " " & "DN of group that you want to add to or remove from"
	wscript.echo L_swInputFile	 & " " & "Input file containing list of user DN's"
	wscript.echo

	wscript.echo L_swAddFlag	 & " " & "Flag to add members to group"
	wscript.echo L_swExpiration  & " " & "Expiration date for new members (no expiration by default)"
	wscript.echo

	wscript.echo L_swRemoveFlag  & " " & "Flag to remove members from group"
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
	g_strAccountName	= def_strAccountName			
	g_strPassword		= def_strPassword				
	g_blnSilent			= def_blnSilent

	g_strServer			= ""
	g_strGroupDN		= ""
	g_strInputFile		= ""
	g_strExpiration		= def_strExpiration

	Dim intNumOperSpecified
	intNumOperSpecified = 0

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
				Case L_swAddFlag
					g_blnAdd = true
					intNumOperSpecified = intNumOperSpecified + 1
					strSwitch = ""
				Case L_swRemoveFlag
					g_blnAdd = false
					intNumOperSpecified = intNumOperSpecified + 1
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
				Case L_swGroupDN
					g_strGroupDN		= Arg
				Case L_swInputFile
					g_strInputFile		= Arg
				Case L_swExpiration
					if IsDate( Arg ) then
						g_strExpiration = ConvertToGeneralizedTime( Arg )
					else
						EchoUsage
						exit function
					end if
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory arguments:
	'	server, group DN, input file, and operation (number of operation specified should
	'					    					     be exactly one)
	'
	if g_strServer = "" or g_strGroupDN = "" or g_strInputFile = "" or intNumOperSpecified <> 1 then
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
' Function:     ConvertToGeneralizedTime
' Purpose:      Accepts a Date expression and returns
'				it in GeneralizedTime format
'				(i.e. YYYYMMDD0000Z)
'
'------------------------------------------------------

Function ConvertToGeneralizedTime( dtDate )

	ConvertToGeneralizedTime = _
				GetZeroPaddedString( Year( dtDate ), 4 ) & _
				GetZeroPaddedString( Month( dtDate ), 2 ) & _
				GetZeroPaddedString( Day( dtDate ), 2 ) & _
				"0000Z"
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
'
'------------------------------------------------------
Sub ProcessStatus( strMemberDN, blnNotAMember )

	'
	'	if attempting to remove a non-existent
	'	member, echo appropriate message
	'

	if blnNotAMember then

		g_intNumFailure = g_intNumFailure + 1

		if not g_blnSilent then
			wscript.echo strMemberDN & " : " & L_Failure & " : " & L_NotAMember
		end if
		
		exit sub

	end if

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


		Dim strOutput
		strOutPut = strMemberDN & " : "

		if err.number = 0 then
			strOutput = strOutput & L_Success
		else

			strOutput = strOutput & L_Failure & " : "

			select case err.number
				case OBJECT_NOT_FOUND
					strOutput = strOutput & L_ObjectNotFound
				case ALREADY_EXISTS
					strOutput = strOutput & L_AlreadyAMember
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
' Function:     AddMembers
' Purpose:      Adds the members to the group.
'
'------------------------------------------------------
Sub AddMembers( InStream, objGroup )

	On Error Resume Next

	'
	'	Create GuidGen object
	'

	Dim GuidGen

	set GuidGen = CreateObject( "Membership.GuidGen.1" )
	if err then
		wscript.echo L_FailedToGetGuidGenObject & " (0x" & hex(err) & ")"
		exit sub
	end if

	Dim strMemberDN
	Dim objMemberOf
	Dim strRDN

    Do Until InStream.AtEndOfStream

		'
		'	Read next member DN
		'

		strMemberDN = InStream.ReadLine
		if EchoError then
			set GuidGen = Nothing
			exit sub
		end if

		strMemberDN = Trim( strMemberDN )

		'
		'	Ignore blank/empty lines
		'

		if Len( strMemberDN ) > 0 then
		

			g_intNumUsers = g_intNumUsers + 1

			'
			'	Generate GUID and form RDN of new memberof object
			'

			strRDN = "cn=" & GuidGen.GenerateGuid

			'
			'	Create new memberof object
			'

			set objMemberOf = objGroup.Create( "memberOf", strRDN )

			if err = 0 then
					
				'
				'	set its memberObject to strMemberDN
				'					
					
				objMemberOf.Put "memberObject", Array(strMemberDN)

				'
				'	if expiration date is specified,
				'	set its expiration to it
				'

				if NOT IsNull( g_strExpiration ) then
					objMemberOf.Put "expiration", Array(g_strExpiration)
				end if

				'
				'	commit changes to new memberof object
				'

				objMemberOf.SetInfo

			end if

			ProcessStatus strMemberDN, false

			set objMemberOf = Nothing

		end if	' if Len() > 0

	Loop

	set GuidGen = Nothing

End Sub


'------------------------------------------------------
'
' Function:     RemoveMembers
' Purpose:      Removes the members from the group.
'
'------------------------------------------------------
Sub RemoveMembers( InStream, objGroup, strGroupPath )

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


	Dim strMemberDN
	Dim strQueryString
	Dim Recordset
	Dim arrayCN
	Dim strCN

    Do Until InStream.AtEndOfStream

		'
		'	Read next member DN
		'

		strMemberDN = InStream.ReadLine
		if EchoError then
			Connection.Close
			set Connection = Nothing			
			exit sub
		end if

		strMemberDN = Trim( strMemberDN )

		'
		'	Ignore blank/empty lines
		'

		if Len( strMemberDN ) > 0 then

			g_intNumUsers = g_intNumUsers + 1

			'
			'	Form query string to look up Member DN under the group
			'
			
			strQueryString = "<" & strGroupPath & ">" & ";(memberObject=" & strMemberDN & ");cn;onelevel"

			
			'
			'	Execute query
			'
			set Recordset = Connection.Execute( strQueryString )

			'
			'	error executing query
			'
			if err then
				ProcessStatus strMemberDN, false

			'
			'	no memberOf found,
			'	which means, the member is not a member of the group
			'
			elseif Recordset.EOF then
				ProcessStatus strMemberDN, true
				set Recordset = Nothing

			'
			'	memberOf found, delete it.
			'
			else

				arrayCN = Recordset.Fields("cn")
				if IsNull( arrayCN ) then
					arrayCN = Array()
				end if

				'
				'	cn is returned as an array
				'	get the first (and only) element
				'
				for each strCN in arrayCN
					exit for
				next

				objGroup.Delete "memberOf", "cn=" & strCN

				ProcessStatus strMemberDN, false
				
				set Recordset = Nothing

			end if

		end if	' if Len() > 0

	Loop

	'
	'	Close connection
	'

	Connection.Close
	set Connection = Nothing

End Sub


'------------------------------------------------------
'
' Function:     AddRemoveMembers
' Purpose:      Main function that calls either
'				AddMembers or RemoveMembers as 
'				appropriate
'
'------------------------------------------------------
Sub AddRemoveMembers

	On Error Resume Next

	'
	'	Initialize counters
	'

	g_intNumUsers	= 0
	g_intNumSuccess = 0
	g_intNumFailure = 0

	'
	'	Open the input file for reading
	'

	Dim FileSystem
	Dim InStream

	set FileSystem = CreateObject("Scripting.FileSystemObject")
	if EchoError then exit sub

	set InStream = FileSystem.OpenTextFile( g_strInputFile )
	if EchoError then
		set FileSystem = Nothing
		exit sub
	end if

	'
	'	Bind to group object
	'

	Dim strGroupPath	
	Dim objGroup

	strGroupPath = "LDAP://" & g_strServer & "/" & g_strGroupDN
	if NOT BindToObject( strGroupPath, objGroup ) then exit sub
		

	'
	'	Call the appropriate function now
	'

	if g_blnAdd then
		AddMembers InStream, objGroup
	else
		RemoveMembers InStream, objGroup, strGroupPath
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
' Main routine
'
'------------------------------------------------------

if GetArguments then
	EchoHeader
	AddRemoveMembers
	EchoStatistics
end if


