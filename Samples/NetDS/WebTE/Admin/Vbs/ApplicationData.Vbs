''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' (C) 1998 Microsoft Corporation.  All rights reserved.                        '
' This is prerelease software and is provided as is and Microsoft makes no     '
' warranties,  either express or implied. The entire risk of the use or the    '
' results of the use of this prerelease software remains with the user.        '
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' This script lists basic data about all installed IVR applications
'

Sub ListApps()
    Set WebTE = CreateObject("WebTE.Root")
    Set Admin = WebTE.Arrays.GetContainingArray
    Set Addresses = WebTE.Arrays.GetContainingArray.Servers(1).Addresses
    Set applications = admin.applications
    output = ""

    For Each application In applications
        phones = ""
        output = output & "Application name: " & application.Name & vbCrLf & _
                 "Application description: " & application.Description & vbCrLf & _
                 "Initial page: " & application.HomePage & vbCrLf & _
                 "Associated phone numbers: "
        For Each Address in Addresses
            If Address.AssignedApplication = application.Name Then
                phones  = phones & Address.DialableAddress & " "
            End If
        Next
        If phones = "" Then
            output = output & "none"
        Else
            output = output & phones
        End If
        output = output & vbCrLf & vbCrLf
    Next
    MsgBox output
End Sub

ListApps