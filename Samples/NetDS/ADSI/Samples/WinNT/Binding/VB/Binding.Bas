Attribute VB_Name = "Binding"
Sub Main()

'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       bind.bas
'
'  Contents:   Show how to bind to an ADSI object
'
'----------------------------------------------------------------------------

Dim dso As IADsOpenDSObject

userName = "Administrator"
password = "waldoishere"

'-----------------------------------------------------
'--- BINDING TO A DOMAIN -----------------------------
'------------------------------------------------------
domainName = "INDEPENDENCE"

'--- Binding to a domain as currently logged on user
Set dom = GetObject("WinNT://" & domainName)


'--- Binding to a domain with supplied credential
Set dso = GetObject("WinNT:")
Set dom = dso.OpenDSObject("WinNT://" & domainName, userName, password, 0)


'-----------------------------------------------------
'--- BINDING TO A REMOTE MACHINE  --------------------
'------------------------------------------------------
computerName = "adsi"

'--- Binding to a computer as currently logged on user
Set comp = GetObject("WinNT://" & computerName & ",computer")


'--- Binding to a computer with supplied credential
Set dso = GetObject("WinNT:")
Set comp = dso.OpenDSObject("WinNT://" & computerName & ",computer", userName, password, 0)

'-- and you can find out which domain this computer is joined to
Debug.Print "Domain Name for this computer is " & comp.Parent



'-----------------------------------------------------
'--- BINDING TO A USER IN A DOMAIN  --------------------
'------------------------------------------------------
ADsPath = "WinNT://" & domainName & "/" & userName
'-- adsPath == WinNT://INDEPENDENCE/Administrator

Set dom = GetObject(ADsPath)




End Sub
