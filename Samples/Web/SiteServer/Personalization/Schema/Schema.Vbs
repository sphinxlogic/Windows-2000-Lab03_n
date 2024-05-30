<%
' ====================================================================
' FILE:			Schema.vbs
'
' DESCRIPTION:	This file contains a library of utility functions for
'				managing the U2 schema.
'
' Schema Functions
' ----------------
'	CreateAttribute - Creates a new attribute in the schema
'	ModifyAttribute - Modifies an existing attribute in the schema
'	CreateClass - Creates a new class in the schema
'	ModifyClass - Modifies an existing class in the schema
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
' Schema Functions
'
'**********************************************************************

'======================================================================
' Function:		CreateAttribute
' 
' Description:	Create an attribute in the DS
'
' Parameters:	Server to connect to
'				Common-name (for scripting, e.g. "cn=myAttribute")
'				Display name (for localization, e.g. "My Attribute")
'				Description of object
'				Attribute syntax (string, integer, etc.)
'				Unenforced syntax constraints
'				True if object is multivalued, False otherwise
'				True if object is searchable, False otherwise
'
' Returns:		Nothing
'======================================================================
Sub CreateAttribute (sServer, sCN, sDisplayName, sDescription, _
					 sSyntax, sConstraint, fMultivalued, fSearchable)
	Dim sSchema
	Dim oSchema
	Dim oAttribute

	'
	' Get the schema container:
	'
	sSchema = GetSchemaPath(sServer)
	Set oSchema = ADsOpenObject(sSchema, "", "", 0)

	'
	' Create the object:
	'
	Set oAttribute = oSchema.Create ("attributeSchema", sCN)
	
	'
	' Write out the mandatory properties:
	'
	oAttribute.Put "attributeSyntax", (sSyntax)
	oAttribute.Put "isSingleValued", Abs(Not(fMultivalued))
	oAttribute.Put "isSearchable", Abs(fSearchable)

	'
	' Write out the optional properties, if needed:
	'
	If Len(sDisplayName) > 0 Then oAttribute.Put "displayName", (sDisplayName)
	If Len(sDescription) > 0 Then oAttribute.Put "description", (sDescription)
	If Len(sConstraint) > 0 Then oAttribute.Put "syntaxConstraints", (sConstraint)

	'
	' Save the attribute:
	'
	oAttribute.SetInfo
End Sub

'======================================================================
' Function:		ModifyAttribute
' 
' Description:	Modify an attribute in the DS.
'				Note: The type of the attribute (including multivalued
'					  and searchable) should not be modified after
'					  creation.
'
' Parameters:	Server to connect to
'				Common-name (for scripting, e.g. "cn=myAttribute")
'				Display name (for localization, e.g. "My Attribute")
'				Description of object
'				Unenforced syntax constraints
'
' Returns:		Nothing
'======================================================================
Sub ModifyAttribute (sServer, sCN, sDisplayName, sDescription, _
					sConstraint)
	Dim sAttribute
	Dim oAttribute

	'
	' Get the schema container:
	'
	sAttribute = GetSchemaPath(sServer) & "/" & sCN
	Response.Write sAttribute
	Set oAttribute = ADsOpenObject(sAttribute, "", "", 0)

	'
	' Write out the optional properties or clear them, if needed:
	'
	If Len(sDisplayName) > 0 Then
		oAttribute.Put "displayName", (sDisplayName)
	Else
		oAttribute.PutEx ADS_ATTR_CLEAR, "displayName", (sDisplayName)
	End If

	If Len(sDescription) > 0 Then
		oAttribute.Put "description", (sDescription)
	Else
		oAttribute.PutEx ADS_ATTR_CLEAR, "description", (sDescription)
	End If

	If Len(sConstraint) > 0 Then
		oAttribute.Put "syntaxConstraints", (sConstraint)
	Else
		oAttribute.PutEx ADS_ATTR_CLEAR, "syntaxConstraints", (sConstraint)
	End If

	'
	' Save the attribute:
	'
	oAttribute.SetInfo
End Sub

'======================================================================
' Function:		CreateClass
' 
' Description:	Create a class object in the DS
'
' Parameters:	Server to connect to
'				Common-name (for scripting, e.g. "cn=myAttribute")
'				Display name (for localization, e.g. "My Attribute")
'				Description of object
'				Array of mandatory attributes (by name)
'				Array of optional attributes (by name)
'				The RDN attribute id (normally "cn")
'				Array of parent classes (by name, normally "organizationalUnit")
'				True if the class is a container (normally false)
'				Flags to specify the type of container (normally 0)
'				True if the class is a security principal (normally false)
'
' Returns:		Nothing
'======================================================================
Sub CreateClass (sServer, sCN, sDisplayName, sDescription, _
					 asMustContain, asMayContain, sRDNAttributeId, _
					 asPossibleSuperiors, fContainer, fContainerType, _
					 fSecurityPrincipal)
	Dim sSchema
	Dim oSchema
	Dim oClass

	'
	' Get the schema container:
	'
	sSchema = GetSchemaPath(sServer)
	Set oSchema = ADsOpenObject(sSchema, "", "", 0)

	'
	' Create the object:
	'
	Set oClass = oSchema.Create ("classSchema", sCN)
	
	'
	' Make sure our arrays are really arrays:
	'
	If IsArray(asMustContain) = False Then asMustContain = Array(asMustContain)
	If IsArray(asPossibleSuperiors) = False Then asPossibleSuperiors = Array(asPossibleSuperiors)
	If (IsArray(asMayContain) = False) And (Len(asMayContain) > 0) Then
		asMayContain = Array(asMayContain)
	End If

	'
	' Write out the mandatory properties:
	'
	oClass.Put "mustContain", (asMustContain)
	oClass.Put "rdnAttId", (sRDNAttributeId)
	oClass.Put "possSuperiors", (asPossibleSuperiors)
	oClass.Put "isContainer", Abs(fContainer)
	oClass.Put "containerType", CInt(fContainerType)
	oClass.Put "isSecurityPrincipal", Abs(fSecurityPrincipal)

	'
	' Write out the optional properties, if needed:
	'
	If Len(sDisplayName) > 0 Then oClass.Put "displayName", (sDisplayName)
	If Len(sDescription) > 0 Then oClass.Put "description", (sDescription)
	If IsArray(asMayContain) = True Then oClass.Put "mayContain", (asMayContain)

	'
	' Save the class:
	'
	oClass.SetInfo
End Sub

'======================================================================
' Function:		ModifyClass
' 
' Description:	Modifies a class object in the DS
'
' Parameters:	Server to connect to
'				Common-name (for scripting, e.g. "cn=myAttribute")
'				Display name (for localization, e.g. "My Attribute")
'				Description of object
'				Array of mandatory attributes (by name)
'				Array of optional attributes (by name)
'				Array of parent classes (by name, normally "organizationalUnit")
'				True if the class is a container (normally false)
'				Flags to specify the type of container (normally 0)
'				True if the class is a security principal (normally false)
'
' Returns:		Nothing
'======================================================================
Sub ModifyClass (sServer, sCN, sDisplayName, sDescription, _
					 asMustContain, asMayContain, asPossibleSuperiors, _
					 fContainer, fContainerType, fSecurityPrincipal)
	Dim sClass
	Dim oClass

	'
	' Get the class object:
	'
	sClass = GetSchemaPath(sServer) & "/" & sCN
	Set oClass = ADsOpenObject(sClass, "", "", 0)
	
	'
	' Make sure our arrays are really arrays:
	'
	If IsArray(asMustContain) = False Then asMustContain = Array(asMustContain)
	If IsArray(asPossibleSuperiors) = False Then asPossibleSuperiors = Array(asPossibleSuperiors)
	If (IsArray(asMayContain) = False) And (Len(asMayContain) > 0) Then
		asMayContain = Array(asMayContain)
	End If

	'
	' Write out the mandatory properties:
	'
	oClass.Put "mustContain", (asMustContain)
	oClass.Put "possSuperiors", (asPossibleSuperiors)
	oClass.Put "isContainer", Abs(fContainer)
	oClass.Put "containerType", CInt(fContainerType)
	oClass.Put "isSecurityPrincipal", Abs(fSecurityPrincipal)

	'
	' Write out the optional properties, if needed:
	'
	If Len(sDisplayName) > 0 Then oClass.Put "displayName", (sDisplayName)
	If Len(sDescription) > 0 Then oClass.Put "description", (sDescription)
	If IsArray(asMayContain) = True Then oClass.Put "mayContain", (asMayContain)

	'
	' Save the class:
	'
	oClass.SetInfo
End Sub

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
' Parameters:	ADsPath to the object to display.
'
' Returns:		The resulting ADsPath
'======================================================================
Sub DisplayObject (sObjectPath)
	On Error Resume Next
	Dim oObject
	Dim oClass
	DIm Properties
	Dim Property
	Dim Values
	Dim Value

	'
	' Get the object and it's schema:
	'
	Set oObject = ADsOpenObject(sObjectPath, "", "", 0)
	Set oClass = ADsOpenObject(oObject.Schema, "", "", 0)

	'
	' Display the basic object information:
	'
	Response.Write oObject.ADsPath

	'
	' Loop through the mandatory properties:
	'
	Properties = oClass.MandatoryProperties
	For Each Property In Properties
		Response.Write "[" & Property & "]"
		Values = oObject.GetEx(Property)
		For Each Value In Values
			Response.Write vbTab & Value
		Next
		Values = ""
	Next

	'
	' Loop through the optional properties:
	'
	Properties = oClass.OptionalProperties
	For Each Property In Properties
		Response.Write "[" & Property & "]"
		Values = oObject.GetEx(Property)
		For Each Value In Values
			Response.Write vbTab & Value
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
		Response.Write oChild.ADsPath

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
%>
