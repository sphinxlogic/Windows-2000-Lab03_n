VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "ProgEdit"
   ClientHeight    =   5775
   ClientLeft      =   1920
   ClientTop       =   645
   ClientWidth     =   7815
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5775
   ScaleWidth      =   7815
   Begin VB.CommandButton cmdNew 
      Caption         =   "New Program"
      Enabled         =   0   'False
      Height          =   315
      Left            =   3840
      TabIndex        =   30
      Top             =   60
      Width           =   1275
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "Delete Program"
      Enabled         =   0   'False
      Height          =   315
      Left            =   6480
      TabIndex        =   4
      Top             =   60
      Width           =   1275
   End
   Begin VB.CommandButton cmdSave 
      Caption         =   "Save Program"
      Enabled         =   0   'False
      Height          =   315
      Left            =   5160
      TabIndex        =   3
      Top             =   60
      Width           =   1275
   End
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "Refresh"
      Enabled         =   0   'False
      Height          =   315
      Left            =   1200
      TabIndex        =   1
      Top             =   60
      Width           =   1095
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   315
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   1095
   End
   Begin VB.ListBox lstFlags 
      Enabled         =   0   'False
      Height          =   1635
      ItemData        =   "frmMain.frx":0442
      Left            =   5460
      List            =   "frmMain.frx":047C
      Style           =   1  'Checkbox
      TabIndex        =   28
      Top             =   4080
      Width           =   2295
   End
   Begin VB.ListBox lstPlatforms 
      Enabled         =   0   'False
      Height          =   1635
      ItemData        =   "frmMain.frx":056B
      Left            =   2400
      List            =   "frmMain.frx":056D
      Style           =   1  'Checkbox
      TabIndex        =   26
      Top             =   4080
      Width           =   3015
   End
   Begin VB.TextBox txtDuration 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   24
      Top             =   3480
      Width           =   3435
   End
   Begin VB.TextBox txtDiskSpaceReq 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   22
      Top             =   3180
      Width           =   3435
   End
   Begin VB.TextBox txtDependentProgram 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   20
      Top             =   2880
      Width           =   3435
   End
   Begin VB.TextBox txtRequirements 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   18
      Top             =   2580
      Width           =   3435
   End
   Begin VB.TextBox txtComment 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   16
      Top             =   2280
      Width           =   3435
   End
   Begin VB.TextBox txtDescription 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   14
      Top             =   1980
      Width           =   3435
   End
   Begin VB.TextBox txtDriveLetter 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      MaxLength       =   1
      TabIndex        =   12
      Top             =   1680
      Width           =   3435
   End
   Begin VB.TextBox txtWorkingDirectory 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   10
      Top             =   1380
      Width           =   3435
   End
   Begin VB.TextBox txtCommandLine 
      Enabled         =   0   'False
      Height          =   285
      Left            =   4320
      TabIndex        =   8
      Top             =   1080
      Width           =   3435
   End
   Begin VB.TextBox txtProgramName 
      Height          =   285
      Left            =   4320
      Locked          =   -1  'True
      TabIndex        =   6
      Top             =   540
      Width           =   3435
   End
   Begin ComctlLib.TreeView tvwMain 
      Height          =   5235
      Left            =   60
      TabIndex        =   2
      Top             =   480
      Width           =   2235
      _ExtentX        =   3942
      _ExtentY        =   9234
      _Version        =   327682
      HideSelection   =   0   'False
      Indentation     =   423
      LabelEdit       =   1
      Style           =   7
      ImageList       =   "ImageList1"
      Appearance      =   1
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   2580
      Top             =   60
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   3
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":056F
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0889
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0BA3
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000010&
      X1              =   2340
      X2              =   7740
      Y1              =   900
      Y2              =   900
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Icon:"
      Height          =   195
      Index           =   12
      Left            =   3300
      TabIndex        =   29
      Top             =   3540
      Visible         =   0   'False
      Width           =   360
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Duration:"
      Height          =   195
      Index           =   11
      Left            =   2400
      TabIndex        =   23
      Top             =   3540
      Width           =   645
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Disk Space Required:"
      Height          =   195
      Index           =   10
      Left            =   2400
      TabIndex        =   21
      Top             =   3240
      Width           =   1560
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Flags:"
      Height          =   195
      Index           =   9
      Left            =   5460
      TabIndex        =   27
      Top             =   3840
      Width           =   420
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Platforms:"
      Height          =   195
      Index           =   8
      Left            =   2400
      TabIndex        =   25
      Top             =   3840
      Width           =   690
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Dependent Program:"
      Height          =   195
      Index           =   7
      Left            =   2400
      TabIndex        =   19
      Top             =   2940
      Width           =   1470
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Requirements:"
      Height          =   195
      Index           =   6
      Left            =   2400
      TabIndex        =   17
      Top             =   2640
      Width           =   1020
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Comment:"
      Height          =   195
      Index           =   5
      Left            =   2400
      TabIndex        =   15
      Top             =   2340
      Width           =   705
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Description:"
      Height          =   195
      Index           =   4
      Left            =   2400
      TabIndex        =   13
      Top             =   2040
      Width           =   840
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Drive Letter:"
      Height          =   195
      Index           =   3
      Left            =   2400
      TabIndex        =   11
      Top             =   1740
      Width           =   870
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Working Directory:"
      Height          =   195
      Index           =   2
      Left            =   2400
      TabIndex        =   9
      Top             =   1440
      Width           =   1320
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Command Line:"
      Height          =   195
      Index           =   1
      Left            =   2400
      TabIndex        =   7
      Top             =   1140
      Width           =   1095
   End
   Begin VB.Label lblArray 
      AutoSize        =   -1  'True
      Caption         =   "Program Name:"
      Height          =   195
      Index           =   0
      Left            =   2400
      TabIndex        =   5
      Top             =   600
      Width           =   1095
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
' frmMain.frm  (STARTUP FORM)
'
' After a connection is made, this form allows the user to create, modify
' and delete instances of SMS_Program.
'
'************************************************************

Option Explicit

Private SupportedPlatforms As New Collection    'Collection for supported platforms list

Private WbemServices As SWbemServices  'Common ISWbemServices Object

'Most recent connection parameters
Private LastServer As String
Private LastSitecode As String
Private LastUser As String
Private LastPassword As String

'ClearSupportedPlatforms: Empty the SupportedPlatforms Collection
Private Sub ClearSupportedPlatforms()
    Dim i As Integer
    For i = 1 To SupportedPlatforms.Count
        SupportedPlatforms.Remove 1
    Next i
End Sub


'AfterConnect: Called immediately after a connection has been successfully established
Public Sub AfterConnect()
    
    'Enumerate and process supported platforms
    If EnumSupportedPlatforms = False Then FatalError "Could not enumerate supported platforms.  This could be indicative of major site failures."
    
    'Populate the tree with packages and programs
    EnumPackagesAndPrograms
    
    'Allow refresh
    cmdRefresh.Enabled = True
    
    
    'Select first entry in the tree
    If tvwMain.Nodes.Count > 0 Then
        Set tvwMain.SelectedItem = tvwMain.Nodes(1)
        cmdNew.Enabled = True
    End If
      
End Sub


'EnumSupportedPlatforms: Enumerates Supported Platforms, fills listbox / collection.  return true for success
Private Function EnumSupportedPlatforms() As Boolean
    
    'Enable error trapping
    On Error Resume Next
    
    Dim woPlatform As SWbemObject
    Dim TempPlatform As SupportedPlatform
    
    'Default return value
    EnumSupportedPlatforms = True
    
    'Clear the SupportedPlatforms collection, if necessary
    If SupportedPlatforms.Count > 0 Then ClearSupportedPlatforms
    
    'Clear the "Supported Platforms" listbox
    lstPlatforms.Clear
    
    'Use a For loop to cycle through all the instances returned from
    'Enumerating the SMS_SupportedPlatforms class
    For Each woPlatform In WbemServices.InstancesOf("SMS_SupportedPlatforms")
        
        'Check for error
        If CheckError(Err.Number, "enumerate instances of SMS_SupportedPlatforms") Then
            EnumSupportedPlatforms = False
            Exit Function
        End If
        
        'Generate a new SupportedPlatform Object
        Set TempPlatform = New SupportedPlatform
        
        'Fill the TempPlatform structure with properties from woPlatform
        TempPlatform.OSPlatform = woPlatform.OSPlatform
        TempPlatform.OSName = woPlatform.OSName
        TempPlatform.OSMinVersion = woPlatform.OSMinVersion
        TempPlatform.OSMaxVersion = woPlatform.OSMaxVersion
        TempPlatform.DisplayText = woPlatform.DisplayText
        TempPlatform.StringId = woPlatform.StringId
               
        'Add an entry into the lstPlatforms listbox
        lstPlatforms.AddItem TempPlatform.DisplayText
        
        'Set the platform listindex
        TempPlatform.ListIndex = lstPlatforms.NewIndex
                
        'Add TempPlatform to the SupportedPlatforms Collection
        SupportedPlatforms.Add TempPlatform, CStr(TempPlatform.ListIndex)
        
    Next woPlatform
    
End Function


'Prepare the treeview
Private Sub EnumPackagesAndPrograms()

    'Clear the tree
    tvwMain.Nodes.Clear
    
    'Enumerate package instances
    If EnumPackages = False Then FatalError "Could not enumerate packages.  This should not happen on a well-functioning site"
    
    'Enumerate program instances
    If EnumPrograms = False Then FatalError "Could not enumerate programs.  This should not happen on a well-functioning site."
    
End Sub


'Enumerate Packages, return true for success
Private Function EnumPackages() As Boolean
    
    'enable error trapping
    On Error Resume Next
    
    'default return value
    EnumPackages = True

    Dim woPackage As SWbemObject   'Object for our packages
    
    'Use a For loop to cycle through all the instancea returned from
    'Enumerating the SMS_Package class
    For Each woPackage In WbemServices.InstancesOf("SMS_Package")
    
        If CheckError(Err.Number, "enumerate instances of SMS_Package") Then
            EnumPackages = False
            Exit Function
        End If
        
        'Add a tree node for the package
        tvwMain.Nodes.Add , , UCase(woPackage.packageid), woPackage.Name, 2
            
    Next woPackage
    
End Function


'Enumerate Programs
Private Function EnumPrograms() As Boolean

    'enable error trapping
    On Error Resume Next
    
    'default return value
    EnumPrograms = True
    
    Dim woProgram As SWbemObject   'Object for our programs
    
    'Use a For loop to cycle through all the instances returned from
    'Enumerating the SMS_Program class
    For Each woProgram In WbemServices.InstancesOf("SMS_Program")
    
        If CheckError(Err.Number, "enumerate instances of SMS_Program") Then
            EnumPrograms = False
            Exit Function
        End If
        
        'Add a tree node for the program, make sure it's visible
        tvwMain.Nodes.Add(UCase(woProgram.packageid), tvwChild, woProgram.packageid & woProgram.programname, woProgram.programname, 1).Tag = woProgram.programname
        tvwMain.Nodes(woProgram.packageid & woProgram.programname).EnsureVisible
        
    Next woProgram

End Function


'Connect button was pressed
Private Sub cmdConnect_Click()
    
    Dim ConnectForm As New frmConnect       'Generate new frmConnect
    
    'Display Connect Form
    ConnectForm.Show 1
    
    
    'Ensure the operation wasn't canceled before attempting to connect
    If Not ConnectForm.Canceled Then
        
        'Set hourglass cursor
        Screen.MousePointer = vbHourglass
        
        'Store values from the form
        LastServer = ConnectForm.txtServer.Text
        LastSitecode = ConnectForm.txtSitecode.Text
        LastUser = ConnectForm.txtUser.Text
        LastPassword = ConnectForm.txtPassword.Text
        
        
        'Enable error trapping
        On Error Resume Next
        
        'Create an SWbemLocator instance
        Dim WbemLocator As New SWbemLocator
        
        'Use the WbemLocator object to connect to the SMS Provider
        Set WbemServices = WbemLocator.ConnectServer(ConnectForm.txtServer.Text, "root\sms\site_" & ConnectForm.txtSitecode.Text, ConnectForm.txtUser.Text, ConnectForm.txtPassword.Text)
        CheckError Err.Number, "connect to \\" & ConnectForm.txtServer.Text & "\root\sms\site_" & ConnectForm.txtSitecode.Text & " as " & ConnectForm.txtUser.Text
        
        'Restore default cursor
        Screen.MousePointer = vbDefault
        
    End If
    
    'Unload the form
    Unload ConnectForm
    
    'If WbemServices is valid, call AfterConnect
    If Not WbemServices Is Nothing Then AfterConnect
    
End Sub


'Delete program button was pressed
Private Sub cmdDelete_Click()
    
    'Enable error trapping
    On Error Resume Next
    
    'Save the key properties, so we can remove it from the tree
    Dim packageid As String
    Dim programname As String
    packageid = tvwMain.SelectedItem.Parent.Key
    programname = tvwMain.SelectedItem.Tag
    
    'Use SWbemServices.Delete to delete a program
    WbemServices.Delete "SMS_Program.PackageId=""" & packageid & """,ProgramName=""" & programname & """"
    If CheckError(Err.Number, "Delete SMS_Program.PackageID=""" & packageid & """,ProgramName=""" & programname & """") Then
        MsgBox "Selected program was not deleted.", vbCritical, "Error"
    
    Else
    
        'remove the treeview node
        tvwMain.Nodes.Remove (packageid & programname)
    
    End If

    tvwMain_NodeClick tvwMain.SelectedItem
    
End Sub


'New button was pressed
Private Sub cmdNew_Click()
    
    'enable error checking
    On Error Resume Next

    Dim packageid As String
    Dim programname As String
    Dim commandline As String
    Dim NewProgram As SWbemObject
    
    If tvwMain.SelectedItem.Tag <> "" Then
        'we have a program
        packageid = tvwMain.SelectedItem.Parent.Key
    Else
        'we have a package
        packageid = tvwMain.SelectedItem.Key
    End If
    
    programname = InputBox("Enter a unique program name", "Program Name needed", "< New Program >")
            
    'If they didn't cancel...
    If programname <> "" Then
    
        'Create a new instance of SMS_Program and store it in NewProgram
        Set NewProgram = WbemServices.Get("SMS_Program").SpawnInstance_
        If CheckError(Err.Number, "Spawn new Instance") Then Exit Sub
                
        'Populate the PackageID and ProgramName properties of the instance
        NewProgram.packageid = packageid
        NewProgram.programname = programname
        
        'Prompt for commandline and populate the property in the instance
        While commandline = ""
            commandline = InputBox("Enter a Command Line", "Command Line needed")
        Wend
        NewProgram.commandline = commandline
        
        'Store the newly created instance
        NewProgram.Put_ wbemChangeFlagCreateOnly
        If CheckError(Err.Number, "Store new Instance.  Perhaps you need a unique program name") Then Exit Sub
        
        tvwMain.Nodes.Add(packageid, tvwChild, packageid & programname, programname, 1).Tag = programname
        
        tvwMain.Nodes(packageid & programname).EnsureVisible
    
    End If
    
        
End Sub

'Refresh button was pressed
Private Sub cmdRefresh_Click()
    
    'Set hourglass cursor
    Screen.MousePointer = vbHourglass
    
    'Clear fields
    cmdRefresh.Enabled = False
    cmdSave.Enabled = False
    cmdDelete.Enabled = False
    cmdNew.Enabled = False
    tvwMain.Nodes.Clear
    ClearFields
    SetPropertyEnabled False
    
    'Destroy WbemServices
    Set WbemServices = Nothing
    
    'Enable error trapping
    On Error Resume Next
    
    Dim WbemLocator As New SWbemLocator     'Create WbemLocator
     
    Set WbemServices = WbemLocator.ConnectServer(LastServer, "root\sms\site_" & LastSitecode, LastUser, LastPassword)
    CheckError Err.Number, "connect to \\" & LastServer & "\root\sms\site_" & LastSitecode & " as " & LastUser
    
    'restore mouse pointer
    Screen.MousePointer = vbDefault
     
    'If the connect succeeded, proceed to the AfterConnect sub.
    If Not WbemServices Is Nothing Then AfterConnect
End Sub


'Save button was pressed
Private Sub cmdSave_Click()
    
    'Set hourglass cursor
    Screen.MousePointer = vbHourglass
    
    'call SaveProgramProperties
    SaveProgramProperties tvwMain.SelectedItem.Parent.Key, tvwMain.SelectedItem.Tag
    
    'restore cursor
    Screen.MousePointer = vbDefault
    
End Sub


Private Sub Form_Load()
    Me.Show
    cmdConnect_Click
End Sub

'If a package is collapsed, change it's icon to a closed folder
Private Sub tvwMain_Collapse(ByVal Node As ComctlLib.Node)
    If Node.Image = 3 Then Node.Image = 2
End Sub


'If a package is expanded, change it's icon to an open folder
Private Sub tvwMain_Expand(ByVal Node As ComctlLib.Node)
    If Node.Image = 2 Then Node.Image = 3
End Sub


'Set the enabled property of all the program fields, clear if false
Private Sub SetPropertyEnabled(boolval As Boolean)

    Dim iLoop As Integer     'loop iterator
    
    'set the properties
    txtCommandLine.Enabled = boolval
    txtWorkingDirectory.Enabled = boolval
    txtDriveLetter.Enabled = boolval
    txtDescription.Enabled = boolval
    txtComment.Enabled = boolval
    txtRequirements.Enabled = boolval
    txtDependentProgram.Enabled = boolval
    txtDiskSpaceReq.Enabled = boolval
    txtDuration.Enabled = boolval
    lstPlatforms.Enabled = boolval
    lstFlags.Enabled = boolval
    
    'If we're setting to false, go ahead and clear them too.
    If boolval = False Then ClearFields
    
End Sub


'Clear the property fields
Private Sub ClearFields()

    Dim iLoop As Integer

    txtProgramName.Text = ""
    txtCommandLine.Text = ""
    txtWorkingDirectory.Text = ""
    txtDriveLetter.Text = ""
    txtDescription.Text = ""
    txtComment.Text = ""
    txtRequirements.Text = ""
    txtDependentProgram.Text = ""
    txtDiskSpaceReq.Text = ""
    txtDuration.Text = ""
    
    'Deselect any checks in the listboxes
    For iLoop = 0 To lstPlatforms.ListCount - 1
        lstPlatforms.Selected(iLoop) = False
    Next iLoop
    For iLoop = 0 To lstFlags.ListCount - 1
        lstFlags.Selected(iLoop) = False
    Next iLoop
    
End Sub


'Tree node was clicked
Private Sub tvwMain_NodeClick(ByVal Node As ComctlLib.Node)

    'If it's a package they've selected...
    If Node.Tag = "" Then
    
        'disable the save and delete buttons, enable the 'new'
        cmdSave.Enabled = False
        cmdDelete.Enabled = False
        cmdNew.Enabled = True
        
        'disable the field controls
        SetPropertyEnabled False
    
    'Else it's a program
    Else
        
        'enable all the program control buttons
        cmdSave.Enabled = True
        cmdDelete.Enabled = True
        cmdNew.Enabled = True
        
        'enable the field controls
        SetPropertyEnabled True
        
        'clear the fields
        ClearFields
        
        'Call LoadProgramProperties.  PackageID will be this node's parent's key.  ProgramName is stored in the tag.
        LoadProgramProperties Node.Parent.Key, Node.Tag
        
    End If
 
End Sub


'Load program properties into the form fields
Private Sub LoadProgramProperties(packageid As String, programname As String)

    'Enable error checking
    On Error Resume Next

    Dim woProgram As SWbemObject 'Program Object
    Dim iLoop As Integer  'loop counter
    Dim Platform As SupportedPlatform  'platform foreach iterator
    Dim sOSPlatform As String
    Dim sOSName As String
    Dim sOSMaxVersion As String
    Dim sOSMinVersion As String
    
    'Get an instance of SMS_Program
    Set woProgram = WbemServices.Get("SMS_Program.PackageID=""" & packageid & """,ProgramName=""" & programname & """")
    If CheckError(Err.Number, "perform ISWbemServices.Get(""SMS_Program.PackageID=""""" & packageid & """"",ProgramName=""""" & programname & """""") Then
        Set tvwMain.SelectedItem = tvwMain.SelectedItem.Parent
        tvwMain_NodeClick tvwMain.SelectedItem
        Exit Sub
    End If
    
    
    'Fill the fields
    txtProgramName.Text = programname
    txtCommandLine.Text = woProgram.commandline
    txtWorkingDirectory.Text = woProgram.WorkingDirectory
    txtDriveLetter.Text = woProgram.DriveLetter
    txtDescription.Text = woProgram.Description
    txtComment.Text = woProgram.Comment
    txtRequirements.Text = woProgram.Requirements
    txtDependentProgram.Text = woProgram.DependentProgram
    txtDiskSpaceReq.Text = woProgram.DiskSpaceReq
    txtDuration.Text = woProgram.Duration
    
    'Walk the flags bitfield
    For iLoop = 12 To 29
        If (woProgram.programflags And (2 ^ iLoop)) > 0 Then lstFlags.Selected(iLoop - 12) = True Else lstFlags.Selected(iLoop - 12) = False
    Next iLoop
    
    lstFlags.ListIndex = -1
    
    'Check necessary SupportedPlatforms boxes, using SupportedOperatingSystems array property
    'This uses a For loop to cycle through all the embedded instances in the
    'SupportedOperatingSystems property
    For iLoop = LBound(woProgram.supportedoperatingsystems) To UBound(woProgram.supportedoperatingsystems)
        
        'An error will occur when attempting to access an empty array.  This is a known bug and it has been addressed.
        If Err.Number <> 0 Then Exit Sub
        
        sOSPlatform = woProgram.supportedoperatingsystems(iLoop).Platform
        sOSName = woProgram.supportedoperatingsystems(iLoop).Name
        sOSMinVersion = woProgram.supportedoperatingsystems(iLoop).MinVersion
        sOSMaxVersion = woProgram.supportedoperatingsystems(iLoop).MaxVersion
        
        For Each Platform In SupportedPlatforms
            If Not lstPlatforms.Selected(Platform.ListIndex) Then
                If (sOSPlatform = Platform.OSPlatform) And (sOSName = Platform.OSName) And (sOSMinVersion = Platform.OSMinVersion) And (sOSMaxVersion = Platform.OSMaxVersion) Then
                    lstPlatforms.Selected(Platform.ListIndex) = True
                    Exit For
                End If
            End If
        Next Platform
        
    Next iLoop
    
    lstPlatforms.ListIndex = -1
    
End Sub

'Save the form fields to a program instance
Private Sub SaveProgramProperties(packageid As String, programname As String)
    
    Dim woProgram As SWbemObject   'program object
    Dim iLoop As Integer    'Loop counter
    Dim var As Variant      'general purpose variant.  stores supportedoperatingsystems object array
    Dim chkcount As Integer     'supported platform count
    Dim programflags As Long    'programflags temp variable
    Dim Platform As SWbemObject    'platform iterator
    
    'Enable error trapping
    On Error Resume Next
    
    'retrieve the instance
    Set woProgram = WbemServices.Get("SMS_Program.Packageid=""" & packageid & """,ProgramName=""" & programname & """")
    If CheckError(Err.Number, "update selected program") Then
        MsgBox "The selected program could not be retreived, thus it could not be updated.", vbCritical, "Error"
        Exit Sub
    End If
    
    woProgram.commandline = txtCommandLine.Text
    woProgram.WorkingDirectory = txtWorkingDirectory.Text
    woProgram.DriveLetter = txtDriveLetter.Text
    woProgram.Description = txtDescription.Text
    woProgram.Comment = txtComment.Text
    woProgram.Requirements = txtRequirements.Text
    woProgram.DependentProgram = txtDependentProgram.Text
    woProgram.DiskSpaceReq = Val(txtDiskSpaceReq.Text)
    woProgram.Duration = Val(txtDuration.Text)
    
    'count the number of checks in the lstPlatforms box
    chkcount = 0
    For iLoop = 0 To lstPlatforms.ListCount - 1
        If lstPlatforms.Selected(iLoop) Then chkcount = chkcount + 1
    Next iLoop
    
    If chkcount > 0 Then
        
        'Set up a variant array for the SMS_Program.SupportedOperatingSystems object array
        ReDim var(0 To chkcount - 1)
        
        chkcount = 0
        
        'Add checked platforms to the array
        For iLoop = 0 To lstPlatforms.ListCount - 1
        
            If lstPlatforms.Selected(iLoop) Then
                
                'Get a SMS_OS_Details object
                Set Platform = WbemServices.Get("SMS_OS_Details")
                
                'Fill in properties from the supported platforms collection
                Platform.Platform = SupportedPlatforms(CStr(iLoop)).OSPlatform
                Platform.Name = SupportedPlatforms(CStr(iLoop)).OSName
                Platform.MaxVersion = SupportedPlatforms(CStr(iLoop)).OSMaxVersion
                Platform.MinVersion = SupportedPlatforms(CStr(iLoop)).OSMinVersion
                
                'Add it to the array
                Set var(chkcount) = Platform
                chkcount = chkcount + 1
                
            End If
        
        Next iLoop
        
        'Store the variant array in the SupportedOperatingSystems property
        woProgram.supportedoperatingsystems = var
    
    End If
    
    
    'Calculate programflags
    
    'Walk the flags bitfield
    programflags = 0
    For iLoop = 12 To 29
        If lstFlags.Selected(iLoop - 12) Then programflags = programflags + (2 ^ iLoop)
    Next iLoop
    woProgram.programflags = programflags
    
    'update the instance
    woProgram.Put_ (wbemChangeFlagUpdateOnly)
    If CheckError(Err.Number, "update selected program instance") Then
         MsgBox "Changes to the selected program were not saved.", vbCritical, "Error"
        Exit Sub
    End If
   
End Sub
