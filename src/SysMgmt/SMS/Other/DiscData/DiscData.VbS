' *************************************************************
' Copyright (c)1999, Microsoft Corporation, All Rights Reserved
' *************************************************************
'
' DiscData - Version 1.0
'
' DiscData.vbs
'
' This sample code will prompt the user for the Netbios name of a machine in the SMS hierarchy.
' It will then use that name to look up the machine and retrieve any Discovery Data associated with it. 
'

Option Explicit
On Error Resume Next

' Setup connection information, This could be prompted from the user, but 
'  for simplicity we will hard-code it.
Dim sMachine, sSite, sAdminUser, sAdminPasswd
sAdminUser = "UserAccount"	' user account with appropriate permissions
sAdminpasswd = "MyPassword"     ' the user accounts password 
sMachine = "ProviderMachine"   	' machine name running the SMS Provider 
sSite = "ABC"             	' SMS Site code

' Make sure the default information has been changed
If sAdminUser = "UserAccount" Then 
  MsgBox "You should used notepad to edit the default connection information in this script before running it.", vbCritical, "Oops!"
  WScript.Quit()
End If

' Ask the user to supply a NetBios name to look up.
Dim sNetbiosName
sNetbiosName = InputBox("Enter the NetBios name of the machine you would like to see SMS Discovery data for:","Display Discovery Information")
if sNetbiosName = vbNullString then
  WScript.Quit()
End If

Dim oWBEMLoc, oWBEMServ

' Create WBEM Locator
Set oWBEMLoc = CreateObject("WbemScripting.SWbemLocator")
If Err.Number <> 0 Then 
  MsgBox "Can't create WBEM Locator." & chr(10) & Err.Description & " (" & Err.Number & ") ", vbCritical, "Oops!"
  WScript.Quit()
End If

' Connect to the namespace of the specified server
Set oWBEMServ = oWBEMLoc.ConnectServer(sMachine,"root/sms/site_" & sSite, sAdminUser, sAdminpasswd)
If Err.Number <> 0 Then 
  MsgBox "Could not log in '" & sAdminUser & "' to site '" & sSite & "' on machine '" & sMachine & "'" & chr(10) & Err.Description & " (" & Err.Number & ") ", vbCritical, "Oops!"
  WScript.Quit()
End if 

Dim oSystemSet, oSystem

' Get an ObjectSet of Systems that match the name of the machine supplied. 
Set oSystemSet = oWBEMServ.ExecQuery("Select * from SMS_R_System where NetbiosName='" & sNetbiosName & "' ")

' The object set is empty if the .Count property equals to 0, this would mean that the machine wasn't found.
If oSystemSet.Count = 0 Then
  MsgBox "Could not find a machine with the name: "& sNetbiosName, vbCritical, "Oops!"
  WScript.Quit()
End IF

' oSystem.Properties_ creates a collection of the properties contained within
'  the instance. This allows you to access each of the properties and get the
'  properties name and value from the collection member. This is a cleaner 
'  approach than to hardcode each property a hard-coded property, and 
'  display its value. You would also have to create individual loops for each 
'  array property. 
' While looping through each property add the values to a string for the final 
'  display.
Dim oProp, strProps, i
For Each oSystem in oSystemSet
  strProps = oSystem.Name & chr(10) & chr(10)
  For Each oProp in oSystem.Properties_

	' If the property is an array, walk through the array getting each value and
	'  append it to the output string.
	if VarType(oProp.Value) >= vbArray Then
		strProps = strProps & oProp.Name & " = " 
		For i = Lbound(oProp.Value) To Ubound(oProp.Value)
			If i > 0 then strProps = strProps & ", "
			strProps = strProps & oProp.Value(i) 
		Next 
		strProps = strProps & Chr(10)

        ' Otherwise append the property name and its value to the output string.
        ' Note that the last reference to oProp is used to show you the default 
        ' behavior of the object. In practice, you should use the explicit form,
	' oProp.Value.
	Else 
		strProps = strProps & oProp.Name & " = " & oProp.Value & Chr(10)
	End if
  Next
Next

' Display the string to the screen
MsgBox strProps,,"SMS Discovery Information from SMS_R_System" 

