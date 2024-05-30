' Localizable strings

L_Usage_Message         = "This script will create a dynamic object in the ou=Members container."
L_Usage_Message_2       = "  "
L_Usage_Message_3       = "  Usage: cscript ilsadd.vbs Server:Port UserName"
L_ServerUsage_Message   = "     Server:    LDAP server and port (389 by default)"
L_UserNameUsage_Message = "     UserName:  CommonName of user to add"

L_ContactServer_ErrorMessage = "Cannot contact server"

dim bstrRootPath

' ///////////////////////////////////////////////////////////////////////////
'	Function:	Usage
' 
' ///////////////////////////////////////////////////////////////////////////
Function Usage()

	wscript.Echo 
    wScript.Echo L_Usage_Message
    wScript.Echo L_Usage_Message_2
    wScript.Echo L_Usage_Message_3
    wScript.Echo L_ServerUsage_Message
	wScript.Echo L_UserNameUsage_Message
	wscript.Echo
	wscript.Quit(-1)

end Function


Function CreateDynamicObject ( UserName, GUID )

	On Error goto 0
	
	bstrPath = bstrRootPath & "/OU=Members"

	wscript.Echo "Creating ILS User " & bstrPath & "/cn=" & UserName

	set Container = GetObject(bstrPath)
	errnum = Err.Number
	If errnum <> 0 Then
		wscript.Echo "Error opening ou=Members" & bstPath
		CreateDynamicObject = errnum
		exit Function
	End If

	set UserObject = Container.Create("member", "cn=" & UserName)
	errnum = Err.Number
	If errnum <> 0 Then
		wscript.Echo "User Already exists" & UserName
	else

		' Add the GUID
		UserObject.Put "Guid", (GUID)
		errnum = Err.Number
		If errnum <> 0 Then
			wscript.Echo "Error setting GUID " & UserName
			CreateDynamicObject = errnum
			exit function
		End If

		' Now make it a dynamic object.
		UserObject.Put "objectClass", (ARRAY("member", "DynamicObject"))
		errnum = Err.Number
		If errnum <> 0 Then
			wscript.Echo "Put objectClass error " & UserName
			CreateDynamicObject = errnum
			exit function
		End If

		UserObject.SetInfo
		errnum = Err.Number
		If errnum <> 0 Then
			wscript.Echo "SetInfo error " & UserName
			CreateDynamicObject = errnum
			exit function
		End If

	End If

	set Container = Nothing
	set UserObject = Nothing
	CreateDynamicObject = 0
End Function


Function UpdateTTL( UserName, TTLValue )

	On Error goto 0
	
	bstrPath = bstrRootPath & "/OU=Members"

	wscript.Echo "Updating the TTL to " & TTLValue

	set UserObject = GetObject(bstrPath & "/cn=" & UserName)
	errnum = Err.Number
	If errnum <> 0 Then
		wscript.Echo "Error getting user (may not exist) " & bstPath & "/cn=" & UserName
		UpdateTTL = errnum
		exit Function
	End If

	' Set the TTL
	UserObject.Put "entryTTL", (TTLValue)
	errnum = Err.Number
	If errnum <> 0 Then
		wscript.Echo "Error setting TTL " & UserName
		UpdateTTL = errnum
		exit function
	End If

	UserObject.SetInfo
	errnum = Err.Number
	If errnum <> 0 Then
		wscript.Echo "SetInfo error " & UserName
		UpdateTTL = errnum
		exit function
	End If

	UpdateTTL = 0
End Function


' ***************************************************************
' MAIN
' ***************************************************************
'
	On Error goto 0

	Set objArgs = WScript.Arguments
	if (objArgs.count <> 2)  then
		Call Usage
		wscript.Quit(-1)
	end if

	ServerName = objArgs(0)
	If Len(ServerName) = 0 Then
		Call Usage
		wscript.Quit(-1)
	end if

	UserName = objArgs(1)
	if (Len(UserName) = 0) Then
		Call Usage
		wscript.Quit(-1)
	end if

	' Connect to the DS
	set Container = GetObject("LDAP://" & ServerName)
	errnum = Err.Number
	If errnum <> 0 Then
		wscript.Echo L_ContactServer_ErrorMessage&errnum&ServerName
	else
		bstrRootPath = Container.ADsPath
		set Container = nothing
		
		Call CreateDynamicObject(UserName, "1234")
		' Set the TTL to 10 minutes
		Call UpdateTTL( UserName, 600)
	end if


