''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' (C) 1998 Microsoft Corporation.  All rights reserved.                        '
' This is prerelease software and is provided as is and Microsoft makes no     '
' warranties,  either express or implied. The entire risk of the use or the    '
' results of the use of this prerelease software remains with the user.        '
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' This script shows how to change a property of all the application to a fixed
' predetermined value
'

Sub ChangeAllApps()
    Set WebTE = CreateObject("WebTE.Root")
    Set admin = WebTE.Arrays.GetContainingArray
    Set applications = admin.Applications

    On Error Resume Next
    For Each app in applications
        app.OperatorExtension = "1160"
    Next

    admin.Save
    If err.Number <> 0 Then
        MsgBox err.Description
        Exit Sub
    End If

    MsgBox "All applications' operator extensions were changed"
End Sub

ChangeAllApps
