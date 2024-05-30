' ====================================================================
' FILE:	RemoveObject.VBS
'
' PARAMETERS:
'		/H	Server:Port
'		/U	User DN (optional)
'		/P	User password (optional)
'		/O	DN of object to remove
'		/S  Silent mode (will not display status of each operation)
'		/?  Display help message
'
'		When /U and /P are not specified, it will bind anonymously when
'		/H points to a Membership Authenticated DS or as the currently
'		logged on NT user when /H points to an NT Authenticated DS.
'
' AUTHENTICATION TYPE:
'		Applies to both Membership and NT Authentications.
'
' DESCRIPTION:
'		This removes the specified object from the DS, including all the
'		objects underneath it, if any.
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
const L_swObjectDN					= "/O"
const L_swSilent					= "/S"
const L_swHelp						= "/?"

' header information
const L_Title						= "REMOVE AN OBJECT"
const L_TimeExecuted				= "Time Executed: "
const L_optServer					= "Server       : "
const L_optAccountName				= "User         : "
const L_optPassword					= "Password     : "
const L_optObjectDN					= "Object DN    : "
const L_optSilent					= "Silent       : "

' status information
const L_Error						= "Error: "
const L_Success						= "Success"
const L_Failure						= "Failure"

' specific error messages
const L_ObjectNotFound				= "Object not found.  It may have been deleted."

' status
const L_Result						= "RESULT: "
const L_ObjectDeleted				= "The object has been successfully deleted."
const L_ObjectNotDeleted			= "Failed to delete object.  If it is a container, it could be because not all of its children were successfuly deleted."

'------------------------------------------------------
' Constants
'------------------------------------------------------

const OBJECT_NOT_FOUND = &H80070002

' Default values for the arguments
const def_strAccountName			= ""
const def_strPassword				= ""
const def_blnSilent					= false

'------------------------------------------------------
' Global Variables
'------------------------------------------------------

' Arguments
Dim g_strServer					
Dim g_strAccountName				
Dim g_strPassword					
Dim g_strObjectDN
Dim g_blnSilent

Dim g_strParentDN
Dim	g_objParent
Dim	g_Connection


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
	wscript.echo L_optObjectDN & g_strObjectDN
	wscript.echo L_optSilent & g_blnSilent
	wscript.echo

End Sub


'------------------------------------------------------
'
' Function:     EchoResult
' Purpose:      Echoes result of deletion
'
'------------------------------------------------------
Sub EchoResult( blnSuccess )

	wscript.echo 
	wscript.echo L_Result

	if blnSuccess then
		wscript.echo L_ObjectDeleted
	else
		wscript.echo L_ObjectNotDeleted
	end if

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

	wscript.echo L_swObjectDN	 & " " & "DN of object to remove"
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
	g_strObjectDN		= ""

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
					g_strServer			= Arg
				Case L_swAccountName
					g_strAccountName	= Arg
				Case L_swPassword
					g_strPassword		= Arg
				Case L_swObjectDN
					g_strObjectDN		= Arg
				Case Else
					EchoUsage
					exit function
			End Select

			strSwitch = ""
		end if
	next

	'
	'	Mandatory arguments:
	'	server and object DN
	' 
	if g_strServer = "" or g_strObjectDN = "" then
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
' Purpose:      Checks status of last operation.  If not 
'				in silent mode, it echoes the status.  
'				Clears the error afterwards.
'
'------------------------------------------------------
Sub ProcessStatus( strObjectPath )

	'
	' if not in silent mode, echo status
	'
	if not g_blnSilent then

		Dim strOutput
		strOutPut = strObjectPath & " : "

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
'				path relative to the parent DN.
'
'				This assumes that the format of the
'				ADSPath is: 
'				LDAP://host:port/<rdn>=objname,...,<parentDN>
'
'				e.g. Given the following full path:
'				LDAP://localhost:1003/cn=user1,<parentDN>
'				Relative path would be:  cn=user1
'
'------------------------------------------------------

Function GetRelativePath( strFullPath )

	Dim nPos
	Dim strRelativePath

	' Remove the "LDAP://host:port/" part
	strRelativePath = GetDN( LCase(strFullPath) )

	' Remove the base DN part
	nPos = InstrRev( strRelativePath, LCase(g_strParentDN) )
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
' Function:     GetObjectClass
' Purpose:      Obtains the objectClass of a given object.
'				(given its full ADsPath)
'
'------------------------------------------------------
Function GetObjectClass( strPath, strObjectClass )

	On Error Resume Next

	GetObjectClass = false

	Dim obj
	Dim blnError

	'
	'	Bind to object
	'

	if not BindToObject( strPath, obj ) then exit function

	'
	'	Get value of objectClass attribute
	'
	
	strObjectClass = obj.Get( "objectClass" )
	blnError = EchoError

	set obj = Nothing

	GetObjectClass = not blnError

End Function


'------------------------------------------------------
'
' Function:     RecursiveRemove
' Purpose:      Accepting an ADsPath, it deletes the
'				object pointed to by the path and all
'				its children, if any.
'				Returns TRUE if object was deleted
'				successfully.
'
'------------------------------------------------------
Function RecursiveRemove( strObjectPath, strObjectClass )

	On Error Resume Next

	RecursiveRemove = false

	Dim blnHasChildren
	blnHasChildren = true

	'
	' Form query string
	'
	Dim strQueryString
	strQueryString = "<" & strObjectPath & ">" & ";(objectclass=*);adspath,objectClass;onelevel"

	'
	'	Execute query
	'
	Dim Recordset
	set Recordset = g_Connection.Execute( strQueryString )

	if err.number = OBJECT_NOT_FOUND then
		blnHasChildren = false
		err.clear
	elseif EchoError then 
		exit function
	end if


	Dim blnAllDeleted
	blnAllDeleted = true

	if blnHasChildren then

		'
		'	Call RecursiveRemove on each child
		'	
		
		Dim strChildPath
		Dim collChildClass, strChildClass

		do until Recordset.EOF 

			strChildPath  = Recordset.Fields("adspath")
			collChildClass = Recordset.Fields("objectClass")

			'
			'	objectClass is returned as a collection,
			'	get its first element.
			'
			for each strChildClass in collChildClass
				exit for
			next

			if not RecursiveRemove( (strChildPath), (strChildClass) ) then blnAllDeleted = false

			Recordset.MoveNext	

		loop

	end if

	'
	'	if all children were deleted successfully
	'	or the object has no children, attempt to delete
	'	the object itself now
	'

	if blnAllDeleted or Not blnHasChildren then

		Dim strRelativePath

		strRelativePath = GetRelativePath( strObjectPath )
		g_objParent.Delete strObjectClass, strRelativePath

		if err.number = 0 then RecursiveRemove = true

		ProcessStatus GetDN( strObjectPath )
	
	end if

End Function


'------------------------------------------------------
'
' Function:     RemoveObject
' Purpose:      Main routine that does the deletion
'				of the object (and its children, if any)
'
'------------------------------------------------------
Function RemoveObject

	On Error Resume Next

	RemoveObject = false

	'
	'	Get parent's DN and ADsPath
	'	(assumes that object DN is of format: <rdn>=objname,....,o=<org>)
	'

	Dim strParentPath
	Dim nCommaPos

	nCommaPos = Instr( g_strObjectDN, "," )
	g_strParentDN = Right( g_strObjectDN, Len( g_strObjectDN ) - nCommaPos )
	strParentPath = "LDAP://" & g_strServer & "/" & g_strParentDN
	
	'
	'	Bind to object's parent
	'

	if not BindToObject( strParentPath, g_objParent ) then exit function


	'
	'	Establish connection (to be used during the search in RecursiveRemove)
	'

	set g_Connection = CreateObject("ADODB.Connection")
	if EchoError then exit function

	g_Connection.Provider = "ADsDSOObject"
	g_Connection.Open "ADS Provider", g_strAccountName, g_strPassword
	if EchoError then exit function

	'
	'	Determine object's objectClass
	'
	Dim strObjectPath, strObjectClass
	strObjectPath = "LDAP://" & g_strServer & "/" & g_strObjectDN

	if not GetObjectClass( strObjectPath, strObjectClass ) then exit function


	'
	'	Call RecursiveRemove on the object now.
	'

	RemoveObject = RecursiveRemove( strObjectPath, strObjectClass )

	'
	'	Cleanup
	'

	g_Connection.Close
	set g_Connection  = Nothing
	set g_objToDelete = Nothing

End Function


'------------------------------------------------------
'
' Main routine
'
'------------------------------------------------------

if GetArguments then

	EchoHeader

	Dim blnSuccess
	blnSuccess = RemoveObject

	EchoResult blnSuccess

end if


