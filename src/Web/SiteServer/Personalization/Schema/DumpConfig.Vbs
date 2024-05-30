' ====================================================================
' FILE:			dumpConfig.vbs
'
' DESCRIPTION:	This file dumps the configuration object (RootDSE)
'			for an LDAP server.
'
' Configuration Functions
' -----------------------
'	GetRootDSEObject - Returns the RootDSE configuration object.
'	GetDefaultContainerPath - Returns the path to the default container.
'	GetSchemaPath - Returns the path to the schema.
'
' Generic Object Functions
' ------------------------
'	ADsOpenObject - Connects to the DS an gets an object as the
'						specified user.
'	DeleteObject - Removes any object from the DS.
'	DisplayObject - Displays the attributes and values for any object.
'	DisplayContainer - Displays the ADsPath to each child in the
'					   container.
' Misc. Functions
' ---------------
'	ConvertDNToADSPath - Converts a server name and DN to an object
'						 to a fully qualified DN.
'	GetServerNameFromADsPath - Returns the server name and port portion
'						 of the specified ADsPath.
'
' (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE. 
' ====================================================================

'**********************************************************************
'
' Constants used by ADSI:
'
'**********************************************************************
const ADS_ATTR_CLEAR = 1
const ADS_ATTR_UPDATE = 2
const ADS_ATTR_APPEND = 3
const ADS_ATTR_DELETE = 4

'**********************************************************************
'
' Get command line settings:
'
'**********************************************************************
On Error Resume Next
Dim sServerName: sServerName = wScript.Arguments(0)

If Err.Number <> 0 Then
	'**********************************************************************
	'
	' Show the usage:
	'
	'**********************************************************************
	wScript.Echo "Usage: cscript dumpConfig.vbs ServerName"
Else
	'**********************************************************************
	'
	' Dump the Schema:
	'
	'**********************************************************************
	On Error Goto 0
	Dim oConfig: Set oConfig = GetRootDSEObject(sServerName)
	Dim oClass: Set oClass = ADsOpenObject("LDAP://" & sServerName & "/Schema/rootDseInfo", "", "", 16)

	DisplayObject oConfig, oClass
End If

'**********************************************************************
'
' Configuration Functions
'
'**********************************************************************


'======================================================================
' Function:		GetRootDSEObject
'
' Description:	Returns the root DSE object for a server.
'
' Parameters:	The server to connect to.
'
' Returns:		The ADS object that is the root DSE.
'======================================================================
Function GetRootDSEObject (sServer)
	'
	' Note: The RootDSE object is a special configuration object
	'		that can not be secured.  In order to get this object,
	'		a special flag (ADS_NO_AUTHENTICATION [16]) needs to
	'		be passed to ADSI so ADSI will not attempt to bind to
	'		the DS.
	'
	Set GetRootDSEObject = ADsOpenObject("LDAP://" & sServer & "/RootDSE", "", "", 16)
End Function

'======================================================================
' Function:		GetDefaultContainerPath
'
' Description:	Returns the ADsPath to the default container for the
'				specified server.
'
' Parameters:	The server to connect to.
'
' Returns:		The resulting ADsPath to the default container.
'======================================================================
Function GetDefaultContainerPath (sServer)
	Dim oRootDSE
	Set oRootDSE = GetRootDSEObject(sServer)

	GetDefaultContainerPath = ConvertDNToADsPath(sServer, oRootDSE.Get("defaultNamingContext"))
End Function

'======================================================================
' Function:		GetSchemaPath
'
' Description:	Returns the ADsPath to the schema for the specified
'				server.
'
' Parameters:	The server to connect to.
'
' Returns:		The resulting ADsPath to the schema.
'======================================================================
Function GetSchemaPath (sServer)
	Dim oRootDSE
	Set oRootDSE = GetRootDSEObject(sServer)

	GetSchemaPath = ConvertDNToADsPath(sServer, oRootDSE.Get("subSchemaSubEntry"))
End Function

'**********************************************************************
'
' Generic Object Functions
'
'**********************************************************************

'======================================================================
' Function:		ADsOpenObject
' 
' Description:	Gets the specified object from the DS using the
'				supplied credentials.
'
' Parameters:	Path to object to get.
'				Username to bind with.
'				Password to bind with.
'				Flags to pass to ADSI.
'
' Returns:		Nothing
'======================================================================
Function ADsOpenObject(sADsPath, sUsername, sPassword, fFlags)
	Dim oSecureCreator

	Set oSecureCreator = GetObject("LDAP:")

	Set ADsOpenObject = oSecureCreator.OpenDSObject(sADsPath, sUsername, sPassword, fFlags)
End Function

'======================================================================
' Function:		DeleteObject
' 
' Description:	Delete any object from the DS
'
' Parameters:	Path to object to delete.
'
' Returns:		Nothing
'======================================================================
Sub DeleteObject (sADsPath)
	Dim oObject
	Dim oParent

	Set oObject = ADsOpenObject(sADsPath, "", "", 0)
	Set oParent = ADsOpenObject(oObject.Parent, "", "", 0)

	oParent.Delete oObject.Class, oObject.Name
End Sub

'======================================================================
' Function:		DisplayObject
'
' Description:	Displays all of the attributes and values for the
'				specified object.
'
' Parameters:	The object to display.
'
' Returns:		The resulting ADsPath
'======================================================================
Sub DisplayObject (oObject, oClass)
	On Error Resume Next
	Dim Properties
	Dim Property
	Dim Values
	Dim Value

	'
	' Display the basic object information:
	'
	WScript.Echo oObject.ADsPath

	'
	' Loop through the properties:
	'
	Properties = oClass.MandatoryProperties
	For Each Property In Properties
		WScript.Echo "[" & Property & "]"
		Values = oObject.GetEx(Property)
		For Each Value In Values
			WScript.Echo vbTab & Value
		Next
		Values = ""
	Next

	'
	' Loop through the optional properties:
	'
	Properties = oClass.OptionalProperties
	For Each Property In Properties
		WScript.Echo "[" & Property & "]"
		Values = oObject.GetEx(Property)
		For Each Value In Values
			WScript.Echo vbTab & Value
		Next
		Values = ""
	Next

End Sub

'======================================================================
' Function:		DisplayContainer
' 
' Description:	Displays the ADsPath to each child in the container.
'
' Parameters:	Path to container to display.
'
' Returns:		Nothing
'======================================================================
Sub DisplayContainer (sADsPath)
	Dim oContainer: Set oContainer = ADsOpenObject(sADsPath, "", "", 0)
	Dim oChild

	'
	' Enumerate through each object in the container:
	'
	For Each oChild In oContainer
		'
		' Display the object's ADsPath:
		'
		WScript.Echo oChild.ADsPath

		'
		' Note: Uncomment the following line to display all of the
		'		attributes of each child:
		'
		'DisplayObject oChild.ADsPath
	Next
End Sub

'**********************************************************************
'
' Misc. Functions
'
'**********************************************************************

'======================================================================
' Function:		ConvertDNToADSPath
'
' Description:	Converts the specified DN and server name to an
'				ADsPath
'
' Parameters:	Server part of the ADsPath
'				DN to append to the server part in ADsPath format.
'
' Returns:		The resulting ADsPath
'======================================================================
Function ConvertDNToADsPath(sServer, sDN)
	Dim asDNs: asDNs = Split(sDN, ",")
	Dim iIndex
	Dim sADsPath

	sADSPath = "LDAP://" & sServer
	For iIndex = UBound(asDNs) To LBound(asDNs) Step - 1
		sADSPath = sADSPath & "/" + asDNs(iIndex)
	Next
	
	ConvertDNToADSPath = sADSPath
End Function

'======================================================================
' Function:		GetServerNameFromADsPath
'
' Description:	Returns the name of the LDAP server in a valid ADsPath.
'
' Parameters:	Server part of the ADsPath
'				DN to append to the server part in ADsPath format.
'
' Returns:		The resulting server name, or nothing if the result
'				is invalid.
'======================================================================
Function GetServerNameFromADsPath(sADsPath)
	Dim sServer
	Dim iEndOfServer

	'
	' Is this a valid LDAP:// ADsPath?
	'
	If Left(sADsPath, 6) <> "LDAP://" Then
		'
		' Where does the Server name end?
		'
		iEndOfServer = Instr(8, sADsPath, "/")
		If iEndOfServer > 0 Then
			sServer = Mid(sADsPath, 8, iEndOfServer - 8)
		Else
			sServer = Mid(sADsPath, 8)
		End If
	End If

	GetServerNameFromADsPath = sServer
End Function
