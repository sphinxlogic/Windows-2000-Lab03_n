<%

' (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.

    ' This sample shows how to use AUO to create dynamic users in the DS

    ' For the sample to work, you should create an AUO provider named "dynamic"
    ' and with the following properties:
    ' ADS path: LDAP://<machine name>:<port>/o=<realm>/ou=dynamic
    ' Path Suffix: User name
    ' Schema Path: LDAP://<machine name>:<port>/o=<realm>/ou=admin/cn=schema/cn=member
    ' Log on with: <your choice>

    ' Now this script will create members that expire after 10 minutes

    set user = Server.CreateObject("Membership.UserObjects")

    If Not IsArray(user("dynamic").objectClass) Then
        ' User doesn't yet exist, so make sure it's dynamic
        user("dynamic").objectClass = Array("member","DynamicObject")
    End If

    ' Set time to live in any case, to 10 minutes

    ' Move the next two lines immediately after the objectClass line above if
    ' you don't want users that come back to extend the lifetime of the
    ' object
    user("dynamic").entryTTL = 600
    user("dynamic").SetInfo   ' entryTTL must always have a SetInfo of its own

    ' set any other properties
    user("dynamic").userComment = "Hi!"

    ' Write the changes
    user("dynamic").SetInfo

    Response.Write "Success"
%>