VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Sitectrl"
   ClientHeight    =   1110
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3915
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1110
   ScaleWidth      =   3915
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtProposed 
      Height          =   285
      Left            =   2520
      TabIndex        =   3
      Top             =   360
      Width           =   1335
   End
   Begin VB.TextBox txtExisting 
      Alignment       =   1  'Right Justify
      BackColor       =   &H8000000F&
      ForeColor       =   &H80000012&
      Height          =   285
      Left            =   2520
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   60
      Width           =   1335
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "Close"
      Height          =   315
      Left            =   2040
      TabIndex        =   5
      Top             =   720
      Width           =   975
   End
   Begin VB.CommandButton cmdCommit 
      Caption         =   "Commit"
      Default         =   -1  'True
      Height          =   315
      Left            =   900
      TabIndex        =   4
      Top             =   720
      Width           =   975
   End
   Begin VB.Label lblProposed 
      AutoSize        =   -1  'True
      Caption         =   "Proposed Inter-Poll Delay Time:"
      Height          =   195
      Left            =   120
      TabIndex        =   2
      Top             =   420
      Width           =   2220
   End
   Begin VB.Label lblExisting 
      AutoSize        =   -1  'True
      Caption         =   "Current Inter-Poll Delay Time:"
      Height          =   195
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2055
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
'frmMain.frm from SiteCtrl.vbp
'
'This form retrieves a value from the site control file, displays it, and allows
'the user to specify and commit a new value.
'************************************************************

Option Explicit

Private WbemServices As SWbemServices
Private WbemContext As New SWbemNamedValueSet
Private Sitecode As String
Private Server As String


'Cancel button was pressed
Private Sub cmdClose_Click()
    
    'Unload this form.  Indirectly calling QueryUnload and ReleaseSessionHandle
    Unload Me
    
End Sub

Private Sub Form_Load()
    
    'Spawn a connect form
    Dim ConnectForm As New frmConnect
    ConnectForm.Show 1
    
    'If they did not cancel...
    If Not ConnectForm.Canceled Then
    
        
        'Enable error checking
        On Error Resume Next
        
        'Create a new Wbem Locator
        Dim WbemLocator As New SWbemLocator
        
        'Use the Wbem Locator to connect to the SMS Provider
        Set WbemServices = WbemLocator.ConnectServer(ConnectForm.txtServer.Text, "root\sms\site_" & ConnectForm.txtSitecode.Text, ConnectForm.txtUser.Text, ConnectForm.txtPassword.Text)
        If Err.Number <> 0 Then
            MsgBox "Could not connect.", vbCritical, "Error"
            Unload ConnectForm
            Unload Me
            Exit Sub
        End If
        
        'Store sitecode and server for later usage
        Sitecode = ConnectForm.txtSitecode.Text
        Server = ConnectForm.txtServer.Text
        
        'Get a session handle for Site Control File operations
        GetSessionHandle
        
        'Retrieve existing inter-poll delay time value
        GetInterPollDelay
        
    'If they did cancel...
    Else
    
        'Unload the connectform
        Unload ConnectForm
        
        'Unload this form
        Unload Me
    
    End If
    
    'Unload the connectform
    Unload ConnectForm
    
End Sub

'GetSessionHandle executes the GetSessionHandle method of SMS_SiteControlFile.
'A "SessionHandle" string is returned.  This string is stored in a context object.
'This context object (WbemContext) is used with all WbemServices calls where a
'session handle is needed.
Private Sub GetSessionHandle()

    'Enable Error Checking
    On Error Resume Next
    
    'Execute the SMS_SiteControlFile::GetSessionHandle method.
    'Then, add the SessionHandle out-param to our context object
    'as a new Context string.
    WbemContext.Add "SessionHandle", WbemServices.ExecMethod("SMS_SiteControlFile", "GetSessionHandle").SessionHandle
    If Err.Number <> 0 Then
        MsgBox "Could not retrieve SessionHandle.  Aborting.", vbCritical, "Error"
        Unload Me
    End If
    
End Sub


'ReleaseSessionHandle executes the ReleaseSessionHandle method of SMS_SiteControlFile.
Private Sub ReleaseSessionHandle()
    
    'Ensure we're connected before proceeding
    If Not WbemServices Is Nothing Then
    
        'enable error checking
        On Error Resume Next
        
        'Execute the ReleaseSessionHandle method of "SMS_SiteControlFile",
        'use the SessionHandle stored in the context as an in-param
        WbemServices.Get("SMS_SiteControlFile").ReleaseSessionHandle WbemContext.Item("SessionHandle").Value
        If Err.Number <> 0 Then
            MsgBox "SessionHandle was not released.", vbCritical, "Error"
        End If
        
    End If
    
End Sub

'Commit button was pressed
Private Sub cmdCommit_Click()

    'Enable error checking
    On Error Resume Next
    
    'Wbem Object
    Dim WbemInst As SWbemObject
    Dim PropArray As Variant
    
    'Refresh our copy of the SiteControlFile
    WbemServices.ExecMethod "SMS_SiteControlFile.Filetype=1,Sitecode=""" & Sitecode & """", "Refresh", , , WbemContext

    'Retrieve Site Control Item instance
    Set WbemInst = WbemServices.Get("SMS_SCI_Component.Filetype=1,Itemtype=""Component"",Sitecode=""" & Sitecode & """,ItemName=""SMS_SITE_COMPONENT_MANAGER|" & UCase(Server) & """", , WbemContext)
    
    'Retrieve the 'props' property.  It happens to be an array of embedded objects
    PropArray = WbemInst.props
    
    'Set the Value property of the object in the first array element.
    'In this case, the first array element is the InterPoll Delay Time.
    PropArray(0).Value = Val(txtProposed.Text)
    
    'Put our new PropArray value back into the 'props' property in the instance
    WbemInst.props = PropArray
    
    'Store the instance
    WbemInst.Put_ , WbemContext
    
    'Execute SMS_SiteControlFile::Commit to update the Site Control file with the new InterPoll Delay time
    WbemServices.ExecMethod "SMS_SiteControlFile.Filetype=1,Sitecode=""" & Sitecode & """", "Commit", , , WbemContext
    
    If Err.Number <> 0 Then
        MsgBox "An error occurred.  Proposed value was not stored.", vbCritical, "Error"
    End If
    
    'Refresh the interpoll delay text box
    GetInterPollDelay
    
End Sub


'Retrieve value of InterPoll Delay time
Private Sub GetInterPollDelay()

    'enable error checking
    On Error Resume Next
    
    '  1. Get SMS_SCI_Component Instance,  Using our context object.
    '  2. Get 1st element of Props Array
    '  3. Retrieve 'Value' property
    '  4. Store value in txtExisting
    txtExisting.Text = Val(WbemServices.Get("sms_sci_component.filetype=1,itemtype=""Component"",sitecode=""" & Sitecode & """,ItemName=""SMS_SITE_COMPONENT_MANAGER|" & UCase(Server) & """", , WbemContext).props(0).Value)
    If Err.Number <> 0 Then
        MsgBox "Could not retrieve existing Inter-Poll Delay Time value.", vbCritical, "Error"
    End If
    
End Sub


'An attempt to close the window has occurred
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)

    'Release our session handle
    ReleaseSessionHandle
    
End Sub
