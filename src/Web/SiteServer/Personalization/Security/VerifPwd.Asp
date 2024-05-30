<%@ LANGUAGE="VBScript" %>
<% Option Explicit %>
<% Response.Buffer = true %>
<%
    ' (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
    ' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    ' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    ' PARTICULAR PURPOSE.
%>
<%
'
' *************************************************************************
' Function name	:	GetServerADsPath
' Sypnosis		:	Gets the ADsPath of the server
' Parameters	:	oAUO : User Object
'					strServername : name of the server
' Returns		:	String containing the ADsPath
' *************************************************************************
Function GetServerADsPath(oAUO, strServername)
	Dim oLDAP
	set oLDAP = oAUO.GetObjectAsUser("LDAP://" + strServername)
	GetServerADsPath = oLDAP.ADsPath
End Function

'
' *************************************************************************
' Function name	:	GetMappedServerName
' Sypnosis		:	Gets the mapped membership server name
' Parameters	:	oAUO : User Object
' Returns		:	Server name
' *************************************************************************
Function GetMappedServerName(oAUO)
	Dim strUserADsPath
	Dim strServerName
	Dim iStart, iEnd
	'
	' Get ADsPath and parse out the server name
	strUserADsPath = oAUO.ADsPath
	iStart = InStr(strUserADsPath, "LDAP://")
	strServerName = Mid(strUserADsPath, iStart + Len("LDAP://"))
	iEnd = InStr(strServerName, "/")
	GetMappedServerName = Mid(strServerName, 1, iEnd - 1)
End Function
	'
	' Make sure that the correct ScriptID and Password are entered here
	Dim oAUO
	Dim oVerifusr
	Dim oCheckNTUser
	Dim iPassed
	Dim strVerify
	Dim strUserADsPath
	Dim strDomainUsername
	Dim strDelimiter
	Dim aDomainUsername
	Dim strDomain
	Dim strUsername
	Dim strGUIDValue
	Dim strServerADs
	Dim strScriptID
	Dim strPassword

	strScriptID = "cn=Administrator,ou=members,o=microsoft"
	strPassword = "password"
	'
	' Scan if there is a \ or / delimiter
	strDomainUsername = Request("username")
	if InStr(strDomainUsername, "\") then strDelimiter = "\"
	if InStr(strDomainUsername, "/") then strDelimiter = "/"
	'
	' If delimiter present, then domain is present
	' otherwise just use entire string as the username
	if strDelimiter <> "" then
		'
		' Parse out the domain and username
		aDomainUsername = Split(Request("username"), strDelimiter)
		strDomain = Trim(aDomainUsername(0))
		strUsername = Trim(aDomainUsername(1))
	else
		strUsername = strDomainUsername
	end if
	'
	' Initialize AUO for use
	set oAUO = Server.CreateObject("Membership.UserObjects")
	oAUO.SetUserName(strDomainUsername)
	oAUO.BindAs "", strScriptID, strPassword
	'
	' create cookie object
	Set oVerifusr = Server.CreateObject("Membership.verifusr")
	'
	' Get server ADsPath
	strServerADs = GetServerADsPath(oAUO, GetMappedServerName(oAUO))
	'
	' Compute User ADsPath
	if strDelimiter = "" then
		strUserADsPath = strServerADs & "/ou=members/cn=" & strUsername
	else
		strUserADsPath = strServerADs & "/ou=members/ou=" & strDomain & "/cn=" & strUsername
	end if
	'
	' Check if user exists
	On Error Resume Next
	oAUO.GetObjectAsUser(strUserADsPath)
	if Err = 0 then
		'
		' If user already exists, verify credentials
		strVerify = oVerifusr.VerifyCredentials(strDomainUsername, Request("password"), Request("URL"))
		if strVerify = "" then
			%>
			Authentication failed. Please try logging in again.<br>
			The URL <% = Request("URL") %> cannot be accessed.<br>
			Use the back button on your browser to try again.
			<%
			Response.End
		else
			Response.Redirect strVerify
		end if
	end if
        err.clear
	On Error Goto 0


	'
	' Verify user's NT domain username and password......
	set oCheckNTUser = Server.CreateObject("Membership.CheckNTUser.1")
	iPassed = oCheckNTUser.CheckNTUser(strUsername, strDomain, Request("password"))
	if iPassed = 0 then
		%>
		Authentication failed. Please try logging in again.<br>
		The URL <% = Request("URL") %> cannot be accessed.<br>
		Use the back button on your browser to try again.
		<%
		Response.End
	end if
	'
	' Store the password
	oAUO.Put "userPassword", cstr(Request("password"))
	'
	' if memuser cookie is present, then create a new guid
	if Request("MEMUSER") <> "" then
		'
		' Generate the GUID and store it in the user object
		strGUIDValue = oVerifusr.IssueCookiesToNewUser(strDomainUsername)
		oAUO.Put "GUID", cstr(strGUIDValue)
	else
		'
		' Get the guid from the user object and store it in the browser cookie
		strGUIDValue = oAUO.Get("GUID")
		oVerifusr.IssueOldCookiesToNewUser strDomainUsername, strGUIDValue
	End if
	'
	' Commit information into DS
	oAUO.SetInfo
	'
	' Re-verify credentials, so that the forms auth cookie is stuffed into user's browser
	strVerify = oVerifusr.VerifyCredentials(strDomainUsername, Request("password"), Request("URL"))
	if strVerify = "" then
		%>
		Authentication failed. Please try logging in again.<br>
		The URL <% = Request("URL") %> cannot be accessed.<br>
		Use the back button on your browser to try again.
		<%
		Response.End
	end if
	Response.redirect strVerify
%>