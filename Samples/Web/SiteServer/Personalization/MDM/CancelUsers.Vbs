' ====================================================================
' FILE:	CancelUsers.VBS
'
' PARAMETERS:
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/N	Number of days since user's last visit
'		/F	Filter string to limit search (optional)
'		/S  Silent mode (will not display status of each operation)
'		/?  Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'		/F allows cancelling of only those users who satisfy certain
'		criteria.
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This script looks for users under the ou=members container who have  
'		not visited the site for the a specified number of days and who satisfy 
'		some filter	criteria (if any) and sets their accountStatus to 4.
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
const L_swNumDaysSinceLastVisit		= "/N"
const L_swFilter					= "/F"
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "CANCEL USERS"
const L_TimeExecuted				= "Time Executed                  : "
const L_optServer					= "Server                         : "
const L_optAccountName				= "User                           : "
const L_optPassword					= "Password                       : "
const L_optNumDaysSinceLastVisit	= "Number of Days Since Last Visit: "
const L_optFilter					= "Filter                         : "
const L_optSilent					= "Silent                         : "

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
const def_strFilter					= ""
const def_blnSilent					= false

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_intNumDaysSinceLastVisit
Dim g_strFilter
Dim g_blnSilent

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
	wscript.echo L_optNumDaysSinceLastVisit & g_intNumDaysSinceLastVisit
	wscript.echo L_optFilter & g_strFilter
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

	wscript.echo L_swNumDaysSinceLastVisit & " " & "Number of days since user's last visit"
	wscript.echo L_swFilter 	           & " " & "Filter string to limit search (optional)"
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
	g_strAccountName			= def_strAccountName			
	g_strPassword				= def_strPassword				
	g_strFilter					= def_strFilter					
	g_blnSilent					= def_blnSilent

	g_strServer					= ""
	g_intNumDaysSinceLastVisit	= 0

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
				Case L_swNumDaysSinceLastVisit
					g_intNumDaysSinceLastVisit	= Arg
				Case L_swFilter
					g_strFilter					= Arg
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory Arguments:  
	'	server and number of days since last visit
	'
	if g_strServer = "" or g_intNumDaysSinceLastVisit = 0 then
		EchoUsage
		exit function
	end if

	'
	'	if filter is specified, enclose it
	'	in parentheses, if not yet
	'
	if (g_strFilter <> "") then
		if (Left( g_strFilter, 1 ) <> "(") then
			g_strFilter = "(" & g_strFilter & ")"
		end if
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
' Function:     ProcessStatus
' Purpose:      Checks status of last operation.  Updates
'				the appropriate counter and if not in silent 
'				mode, echoes the status.  Clears the
'				error afterwards.
'
'------------------------------------------------------
Sub ProcessStatus( strMemberPath, strLastVisit )

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
		strOutPut = strMemberPath & " : " & FormatGeneralizedTime(strLastVisit) & " : "

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
	'	Compute the "last visit date" by subtracting the "number of days since last visit"
	'	plus one from today's date
	'
	Dim dtLastVisitDate
	dtLastVisitDate = Date - (g_intNumDaysSinceLastVisit + 1)

	'
	'	Form the ADsPath - path of the container under which we want to do the search
	'
	Dim strAdsPath
	strAdsPath = "LDAP://" & g_strServer & "/ou=members," & strDefaultNamingContext

	'
	'	Form the filter string (if user specified a filter, 'AND' it with our own basic filter)
	'
	Dim strFilter
	if g_strFilter <> "" then
		strFilter = "(&" & g_strFilter 
	else
		strFilter = "(&"
	end if
	strFilter = strFilter & "(objectClass=member)(lastVisit<=" & ConvertToGeneralizedTime(dtLastVisitDate) & "))"


	'
	'	Attributes - list of attributes we want returned
	'
	Dim strAttributes
	strAttributes = "adspath,lastVisit"

	'
	'	Scope - allows us to either do a subtree or a one-level search
	'
	Dim strScope
	strScope = "subtree"

	'	
	'	Form the query string now
	'	(Format:  <ADsPath>;filter;attribute-list;scope)
	'
	g_strQueryString = "<" & strAdsPath & ">" & ";" & strFilter & ";" & strAttributes & ";" & strScope

End Sub


'------------------------------------------------------
'
' Function:     CancelUsers
' Purpose:      Main function that does the search
'				and the setting of account status to 4
'
'------------------------------------------------------
Sub CancelUsers

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

	Dim strMemberPath
	Dim	strLastVisit
	Dim objLDAP, objMember
	Dim blnAcctSpecified

	blnAcctSpecified = (g_strAccountName <> "")

	if (blnAcctSpecified) then
		set objLDAP = GetObject("LDAP:")
		if EchoError then exit sub
	end if

	'
	'	For each object in result set, 
	'	update its accountStatus
	'
	do until Recordset.EOF 

		g_intNumUsers = g_intNumUsers + 1

		strMemberPath    = Recordset.Fields("adspath")
		strLastVisit     = Recordset.Fields("lastVisit")

		'
		'	Bind to object.
		'	If user's credentials are specified, bind to the object using those credentials
		'	Else, bind anonymously (if under member auth) or bind as the currently logged
		'	on user (if under NT Auth).  This is accomplished by caling GetObject() below.
		'

		if blnAcctSpecified then
			set objMember = objLDAP.OpenDSObject(strMemberPath, g_strAccountName, g_strPassword, 0)
		else
			set objMember = GetObject(strMemberPath)
		end if

		if err.number = 0 then

			' Update its accountStatus
			objMember.Put "accountStatus", "4"

			if err.number = 0 then

				' Commit update
				objMember.SetInfo

			end if

		end if 

		ProcessStatus GetDN( strMemberPath ), strLastVisit

		set objMember = Nothing
		
		Recordset.MoveNext	

	loop

	set objLDAP = Nothing

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
	CancelUsers
	EchoStatistics
end if


