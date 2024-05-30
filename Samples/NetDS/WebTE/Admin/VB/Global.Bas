Attribute VB_Name = "VBAdm"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' (C) 1998 Microsoft Corporation.  All rights reserved.                        '
' This is prerelease software and is provided as is and Microsoft makes no     '
' warranties,  either express or implied. The entire risk of the use or the    '
' results of the use of this prerelease software remains with the user.        '
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Public Const AddEntry = 1
Public Const ChangeEntry = 2

Public AddOrChange As Integer
Public AppName As String
Public AppPage As String
Public AppLineAddr As String
Public AppDescription As String

Public admin As New MsIvrAdmin
Public apps As MsIvrApplications

Public Sub InitAdmin()
    admin.Init ""
    Set apps = admin.Applications
End Sub
