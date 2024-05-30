Attribute VB_Name = "Startup"
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
' Startup.bas
'
' This will be the first code that executes at startup.
' It will launch the ConnectForm to prompt the user for site
' information.  If they don't cancel the form then it will
' proceed with launching the core code of the application in
' the trayform form.
'
'************************************************************

Option Explicit

Sub Main()
'Launch the ConnectForm and if the user doesn't cancel
' Proceed with connecting to CIMOM and entering the timer
' based update loop.
    
    Dim ConnectForm As New frmConnect
    ConnectForm.Show 1
    If ConnectForm.Canceled = False Then
        Dim NotifyIcon As New trayform
        NotifyIcon.Server = ConnectForm.txtServer
        NotifyIcon.Sitecode = ConnectForm.txtSitecode
        NotifyIcon.User = ConnectForm.txtUser
        NotifyIcon.Password = ConnectForm.txtPassword
        Unload ConnectForm
        NotifyIcon.AddNotifyIcon
        NotifyIcon.Connect
        NotifyIcon.UpdateStatus
    Else
        Unload ConnectForm
    End If

End Sub


