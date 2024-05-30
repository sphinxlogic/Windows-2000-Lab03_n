' ====================================================================
' FILE:	SetAttribute.VBS
'
' PARAMETERS:
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/I	Input file containing list of DNs of objects to modify
'		/A	Attribute to set
'		/V  New value to set the attribute to
'		/S	Silent mode (will not display status of each operation)
'		/?  Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
'		The input file must be of the right format, i.e. one DN to a line.
'		Blank or empty lines are ignored.
'
'		The attribute must be the cn, not the display name. e.g. use
'		givenName, instead of "first name".		
'
'		The attribute can be of any syntax except binary.  For dates,
'		it has to be in GeneralizedTime format, i.e. YYYYMMDDhhmmZ.
'
'		No validity checking is done on the value.  For example, it will
'		not check if the length is greater than the maximum allowed for
'		the attribute.
'
'		No special processing is done for multi-valued attributes, i.e.
'		specifying a multi-valued attribute will cause the single value
'		you specify to replace all of its current values (as opposed
'		to being added to them).
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This script sets the value of an attribute of all the objects 
'		whose DNs are listed in an input file.
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
const L_swInputFile					= "/I"
const L_swAttribute					= "/A"
const L_swValue						= "/V"
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "SET AN ATTRIBUTE ON A LIST OF OBJECTS"
const L_TimeExecuted				= "Time Executed: "
const L_optServer					= "Server       : "
const L_optAccountName				= "User         : "
const L_optPassword					= "Password     : "
const L_optInputFile				= "Input File   : "
const L_optAttribute				= "Attribute    : "
const L_optValue					= "Value        : "
const L_optSilent					= "Silent       : "

' status information
const L_Error						= "Error: "
const L_Success						= "Success"
const L_Failure						= "Failure"

' specific error messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."
const L_InvalidSyntax				= "Value has invalid syntax."

' statistics
const L_Statistics					= "STATISTICS"
const L_NumObjects					= "Object count : "
const L_NumSuccess					= "Success count: "
const L_NumFailure					= "Failure count: "

'------------------------------------------------------
' Constants
'------------------------------------------------------

const OBJECT_NOT_FOUND = &H80070002
const INVALID_SYNTAX   = &H8007007B

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
Dim g_strInputFile
Dim	g_strAttribute
Dim	g_strValue
Dim g_blnSilent

Dim g_intNumObjects
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
	wscript.echo L_optInputFile & g_strInputFile
	wscript.echo L_optAttribute & g_strAttribute
	wscript.echo L_optValue	& g_strValue
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
	wscript.echo L_NumObjects & g_intNumObjects
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

	wscript.echo L_swInputFile	 & " " & "Input file containing the DNs of objects to modify"
	wscript.echo L_swAttribute	 & " " & "Attribute to modify"
	wscript.echo L_swValue       & " " & "New value to set the attribute to"
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
	g_strInputFile		= ""
	g_strAttribute		= ""
	g_strValue			= ""

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
			End Select

		else
			Select Case strSwitch
				Case L_swServer
					g_strServer			= Arg
				Case L_swAccountName
					g_strAccountName	= Arg
				Case L_swPassword
					g_strPassword		= Arg
				Case L_swInputFile
					g_strInputFile		= Arg
				Case L_swAttribute
					g_strAttribute		= Arg
				Case L_swValue
					g_strValue			= Arg		
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory arguments:
	'	server input file, attribute, and value 
	'
	if g_strServer = "" or g_strInputFile = "" or g_strAttribute = "" or g_strValue = "" then
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
' Function:     ProcessStatus
' Purpose:      Checks status of last operation.  Updates
'				the appropriate counter and if not in silent 
'				mode, echoes the status.  Clears the
'				error afterwards.
'
'------------------------------------------------------
Sub ProcessStatus( strMemberDN )

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
Sub BindToObject( strPath, obj )

	On Error Resume Next

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
		if err then exit sub

		set obj = objLDAP.OpenDSObject( strPath, g_strAccountName, g_strPassword, 0 )
		set objLDAP = Nothing

	else

		set obj = GetObject( strPath )

	end if

End Sub


'------------------------------------------------------
'
' Function:     SetAttributeOnListedObjects
' Purpose:      Main function that reads the file and
'				sets the attribute on each of the 
'				listed objects.
'
'------------------------------------------------------
Sub SetAttributeOnListedObjects

	On Error Resume Next

	'
	'	Initialize counters
	'

	g_intNumObjects	= 0
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
	'	Form ADsPath prefix that will be appended to each DN
	'

	Dim strPathPrefix
	strPathPrefix = "LDAP://" & g_strServer & "/"

	'
	'	Main loop
	'

	Dim strObjectDN
	Dim obj

    Do Until InStream.AtEndOfStream

		'
		'	Read next member DN
		'

		strObjectDN = InStream.ReadLine
		if EchoError then exit sub

		strObjectDN = Trim( strObjectDN )

		'
		'	Ignore blank/empty lines
		'

		if Len( strObjectDN ) > 0 then

			'
			'	Increment object count
			'
			g_intNumObjects = g_intNumObjects + 1

			'
			'	Bind to object
			'
			
			BindToObject strPathPrefix & strObjectDN, obj

			if err = 0 then
		
				'
				'	Set the attribute now
				'
				obj.Put g_strAttribute, Array(g_strValue)

				if err = 0 then

					'
					' Commit update
					'
					obj.SetInfo

				end if

			end if 

			'
			'	If value has invalid syntax, echo error
			'	and exit loop (there's no point in proceeding).
			'

			if err = INVALID_SYNTAX then
				wscript.echo L_Error & L_InvalidSyntax
				set obj = Nothing
				exit do
			end if

			ProcessStatus strObjectDN

			set obj = Nothing

		end if	' if Len() > 0

	Loop


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
	SetAttributeOnListedObjects
	EchoStatistics
end if


