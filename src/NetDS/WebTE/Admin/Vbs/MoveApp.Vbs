''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' (C) 1998 Microsoft Corporation.  All rights reserved.                        '
' This is prerelease software and is provided as is and Microsoft makes no     '
' warranties,  either express or implied. The entire risk of the use or the    '
' results of the use of this prerelease software remains with the user.        '
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' This script moves a phone Address from one application to another
'
' Syntax:
' MoveApp.vbs Address FromApp ToApp
'

Dim admin
Dim applications
Dim Addresses
Dim app1
Dim app2

Function LookForApp(appname)
    Dim app

    On Error Resume Next
    Set app = applications(appname)
    If err.Number <> 0 Then
        LookForApp = False
    Else
        LookForApp = True
    End If
End Function

Function LookForAddress(appname,AddressNumber)
    Set application = applications(appname) ' We don't trap errors because
                                            ' error checking has occured
                                            ' previously
    found = False
    For Each Address in Addresses
        If Address.DialableAddress = AddressNumber And Address.AssignedApplication = appname Then
            found = True
            Exit For
        End If
    Next

    LookForAddress = found
End Function

Sub AddAddress(appname,addphoneAddress)
    Dim temp
    Set app = applications(appname)

    For Each Address in Addresses
        If Address.DialableAddress = addphoneAddress Then
            Address.AssignedApplication = appname
            Exit For
        End If
    Next
    Address.Save
End Sub

Sub RemoveAddress(appname,rmvAddress)
    For Each Address in Addresses
        If Address.DialableAddress = rmvAddress And Address.AssignedApplication = appname Then
            Address.AssignedApplication = ""
            Exit For
        End If
    Next
    Address.Save()
End Sub

Sub MoveApps()
    Set WebTE = CreateObject("WebTE.Root")
    Set admin = WebTE.Arrays.GetContainingArray
    Set Addresses = WebTE.Arrays.GetContainingArray.Servers(1).Addresses
    Set applications = admin.applications
    Set args = Wscript.Arguments

    ' Check parameter count
    If args.Count <> 3 Then
        MsgBox "Syntax:" & vbCrLf & "MoveApp.vbs Address FromApp ToApp"
        Exit Sub
    End If

    ' Check validity of application names
    If (Not (LookForApp(args(1)))) Or (Not (LookForApp(args(2)))) Then
        MsgBox "Error: at least one of the specified applications was not found"
        Exit Sub
    End If

    ' Check for validity of the Address number
    If (Not LookForAddress(args(1),args(0))) Then
        MsgBox "Error: the specified Address number was not found"
        Exit Sub
    End If

    RemoveAddress args(1),args(0)
    AddAddress args(2),args(0)
    MsgBox "Address successfully moved"
End Sub

MoveApps
