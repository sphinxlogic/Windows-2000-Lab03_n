<%
'----------------------------------------------------------------------
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
' TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' Copyright (C) 1997-1998 Microsoft Corporation.  All rights reserved.
'
' ils_session.asp:
' ASP used for demonstrating Session State management with the Site 
' Server 3.0  Membership directory.
'
' NOTES          : Last updated 08/14/98 Richard Irving
'----------------------------------------------------------------------

Set auoUser = Server.CreateObject("Membership.UserObjects")

'------------- Begin Common Code --------------------------
' This code should be common on every page.  Put in a .inc
' file to avoid duplicating on each page.
'
If Not IsArray(auoUser("SessionState").objectClass) Then
	'User doesn't yet exist so create a dynamic object 
	auoUser("SessionState").objectClass = Array("SessionState", "dynamicObject")
End If

auoUser("SessionState").entryTTL = 600	'Set timeout to 10 minutes.
auoUser("SessionState").SetInfo
'------------- End Common Code --------------------------

auoUser("SessionState").HitCount = auoUser("SessionState").HitCount + 1

Response.Write "auoUser: " & auoUser("SessionState").cn 
Response.Write "Number of Page hits =" & auoUser("SessionState").HitCount

auoUser("SessionState").SetInfo
%>