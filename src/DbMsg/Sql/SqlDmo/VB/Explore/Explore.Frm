VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "SQL-DMO Explorer"
   ClientHeight    =   6705
   ClientLeft      =   3285
   ClientTop       =   2280
   ClientWidth     =   11175
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6705
   ScaleWidth      =   11175
   Begin VB.TextBox txtProperties 
      Height          =   2535
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   13
      Top             =   4080
      Width           =   10935
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   8520
      TabIndex        =   4
      Top             =   120
      Width           =   615
   End
   Begin VB.ComboBox cboFour 
      Enabled         =   0   'False
      Height          =   315
      Left            =   7680
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   600
      Width           =   3375
   End
   Begin VB.ListBox lstFour 
      Enabled         =   0   'False
      Height          =   2985
      Left            =   7680
      TabIndex        =   12
      Top             =   960
      Width           =   3375
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "&Connect"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   7200
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   5640
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   120
      Width           =   1455
   End
   Begin VB.TextBox txtLogin 
      Height          =   285
      Left            =   3120
      TabIndex        =   1
      Top             =   120
      Width           =   1455
   End
   Begin VB.TextBox txtServer 
      Height          =   285
      Left            =   960
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin VB.ListBox lstThree 
      Enabled         =   0   'False
      Height          =   2985
      Left            =   5160
      TabIndex        =   10
      Top             =   960
      Width           =   2415
   End
   Begin VB.ListBox lstTwo 
      Enabled         =   0   'False
      Height          =   2985
      Left            =   2640
      TabIndex        =   8
      Top             =   960
      Width           =   2415
   End
   Begin VB.ListBox lstOne 
      Enabled         =   0   'False
      Height          =   2985
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   6
      Top             =   960
      Width           =   2415
   End
   Begin VB.ComboBox cboThree 
      Enabled         =   0   'False
      Height          =   315
      Left            =   5160
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   600
      Width           =   2415
   End
   Begin VB.ComboBox cboTwo 
      Enabled         =   0   'False
      Height          =   315
      Left            =   2640
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   600
      Width           =   2415
   End
   Begin VB.ComboBox cboOne 
      Enabled         =   0   'False
      Height          =   315
      Left            =   120
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   5
      Top             =   600
      Width           =   2415
   End
   Begin VB.Label lblPassword 
      Caption         =   "&Password"
      Height          =   255
      Left            =   4680
      TabIndex        =   16
      Top             =   150
      Width           =   855
   End
   Begin VB.Label lblLogin 
      Caption         =   "&Login"
      Height          =   255
      Left            =   2520
      TabIndex        =   15
      Top             =   150
      Width           =   615
   End
   Begin VB.Label lblServer 
      Caption         =   "&Server"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   150
      Width           =   735
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private WithEvents oSQLServer As SQLDMO.SQLServer
Attribute oSQLServer.VB_VarHelpID = -1

' SQLServer objects.
Private oJobServer As SQLDMO.JobServer
Private oReplication As SQLDMO.Replication
Private oConfiguration As SQLDMO.Configuration

' Objects selectable at level one.
Private oCurDB As SQLDMO.Database
Private oCurLnkServer As SQLDMO.LinkedServer
Private oCurRemServer As SQLDMO.RemoteServer

Private oDistributor As SQLDMO.Distributor
Private oPublisher As SQLDMO.Publisher
Private oSubscriber As SQLDMO.Subscriber
Private oDistributionPublisher As SQLDMO.DistributionPublisher
Private oDistributionPublication As SQLDMO.DistributionPublication
Private oDistributionPublishers As SQLDMO.DistributionPublishers
Private oDistributionPublications As SQLDMO.DistributionPublications
Private oDistributionSubscriptions As SQLDMO.DistributionSubscriptions

' Objects selectable at level two.
Private oCurFileGroup As SQLDMO.FileGroup
Private oCurTable As SQLDMO.Table
Private oCurIndex As SQLDMO.Index

Private oCurJob As SQLDMO.Job

Private oCurRepDB As SQLDMO.ReplicationDatabase

' Objects selectable at level three.
Private oCurMrgPub As SQLDMO.MergePublication
Private oCurRepTable As SQLDMO.ReplicationTable
Private oCurTranPub As SQLDMO.TransPublication

Private bConnected As Boolean
Private StartTime As String

Private Sub cboFour_Click()
    On Error GoTo HandleError
    
    Dim oQR As SQLDMO.QueryResults
    Dim num As Integer
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    'Indexed columns or replication details
    If cboFour.ListIndex = -1 Then
        Exit Sub
    End If
    
    Select Case cboFour.Text
    Case "Columns"
        Select Case cboThree
        Case "Indexes"
            ' Fill list and text box using the Columns collection of the selected
            ' Index object.
            FillPropsColl oCurIndex.ListIndexedColumns, "Columns"
            FillListFromCollection oCurIndex.ListIndexedColumns, lstFour
            
        Case "ReplicationTables"
            ' Fill list and text box using the Columns collection of the selected
            ' ReplicationTable object.
            FillPropsColl oCurRepTable.Columns, "Columns"
            FillListFromCollection oCurRepTable.Columns, lstFour
        
        End Select
    
    Case "MergeArticles"
        ' Fill list and text box using the MergeArticles collection of the
        ' selected MergePublication object.
        FillPropsColl oCurMrgPub.MergeArticles, "MergeArticles"
        FillListFromCollection oCurMrgPub.MergeArticles, lstFour
        
    Case "MergeSubscriptions"
        ' Fill list and text box using the MergeSubscriptions collection of the
        ' selected MergePublication object.
        FillPropsColl oCurMrgPub.MergeSubscriptions, "MergeSubscriptions"
        FillListFromCollection oCurMrgPub.MergeSubscriptions, lstFour
    
    Case "TransArticles"
        ' Fill list and text box using the TransArticles collection of the
        ' selected TransPublication object.
        FillPropsColl oCurTranPub.TransArticles, "TransArticles"
        FillListFromCollection oCurTranPub.TransArticles, lstFour
    
    Case "TransSubscriptions"
        ' Fill list and text box using the TransSubscriptions collection of the
        ' selected TransPublication object.
        FillPropsColl oCurTranPub.TransSubscriptions, "TransSubscriptions"
        FillListFromCollection oCurTranPub.TransSubscriptions, lstFour
    
'Each of the following Case statements gets a result set that contains
'history information about one of the Agents. The result set contains
'13 columns but we are only interested in 2 of them. To see the other
'columns and what they contain set a watch on the appropriate value.
    
    Case "Dist Agent"
        ' Fill list box with Agent History
        ' selected TransPublication object.
    
        Set oQR = oDistributionPublisher.EnumDistributionAgentSessions(oDistributionPublication.DistributionSubscriptions.Item(1).DistributionAgent, SQLDMOSession_All, 72)
        'Set the array size to the number of rows returned in the result set.
        ReDim strTimes(oQR.Rows)
        
        lstFour.Clear
        For num = 1 To oQR.Rows
            lstFour.AddItem oQR.GetColumnString(num, 4)
            'Add the start times from the result set to the array.
            strTimes(num) = Left(oQR.GetColumnString(num, 3), 22)
        Next
    
    Case "Snap Agent"
        ' Fill list box with Agent History
        ' selected TransPublication object.
    
        Set oQR = oDistributionPublisher.EnumSnapshotAgentSessions(oDistributionPublication.SnapshotAgent, SQLDMOSession_All, 72)
        'Set the array size to the number of rows returned in the result set.
        ReDim strTimes(oQR.Rows)
     
        lstFour.Clear
        For num = 1 To oQR.Rows
            lstFour.AddItem oQR.GetColumnString(num, 4)
            'Add the start times from the result set to the array.
            strTimes(num) = Left(oQR.GetColumnString(num, 3), 22)
        Next
     
    Case "Log Agent"
        ' Fill list box with Agent History
        ' selected TransPublication object.
    
       Set oQR = oDistributionPublisher.EnumLogReaderAgentSessions(oDistributionPublication.LogReaderAgent, SQLDMOSession_All, 72)
        'Set the array size to the number of rows returned in the result set.
        ReDim strTimes(oQR.Rows)
     
        lstFour.Clear
        For num = 1 To oQR.Rows
            lstFour.AddItem oQR.GetColumnString(num, 4)
            'Add the start times from the result set to the array.
            strTimes(num) = Left(oQR.GetColumnString(num, 3), 22)
        Next
    
    End Select

    If lstFour.ListCount Then
        lstFour.Enabled = True
    End If
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
    
HandleError:
    PrintError
    Resume Next
End Sub
Private Sub cboOne_Click()
    On Error GoTo HandleError
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    'Clear dependent combos and lists
    DisableList lstFour, cboFour
    DisableList lstThree, cboThree
    DisableList lstTwo, cboTwo
    lstOne.Clear
    
    Set oDistributor = Nothing
    Set oPublisher = Nothing
    Set oSubscriber = Nothing
    
    Select Case cboOne.Text
    Case "Application"
        ' The Application object exposes collections. Fill the lower level
        ' combobox with the collection names and enable the combobox.
        FillPropsObj oSQLServer.Application
        
        With cboTwo
            .AddItem "ServerGroups"
            .AddItem "SQLServers"
            .Enabled = True
        End With
        
    Case "BackupDevices"
        ' Fill the list allowing the user to explore individual BackupDevice
        ' objects.
        FillPropsColl oSQLServer.BackupDevices, "BackupDevices"
        FillListFromCollection oSQLServer.BackupDevices, lstOne
        
    Case "Configuration"
        ' The Configuration object exposes the ConfigValues. Fill the lower
        ' level combobox with the collection name and enable the combobox.
        FillPropsColl oSQLServer.Configuration.ConfigValues, "ConfigValues"
        
        With cboTwo
            .AddItem "ConfigValues"
            .Enabled = True
        End With
        
    Case "Databases"
        ' Get the properties of the Databases collection. Fill the list with
        ' the name property from Database objects in the collection. Add
        ' Database object collections to the lower level combobox. Selecting
        ' a database from the list control enables the combobox.
        FillPropsColl oSQLServer.Databases, "Databases"
        FillListFromCollection oSQLServer.Databases, lstOne
        
        With cboTwo
            .AddItem "DatabaseRoles"
            .AddItem "Defaults"
            .AddItem "FileGroups"
            .AddItem "FullTextCatalogs"
            .AddItem "Rules"
            .AddItem "StoredProcedures"
            .AddItem "SystemDataTypes"
            .AddItem "Tables"
            .AddItem "TransactionLog"
            .AddItem "UserDefinedDataTypes"
            .AddItem "Users"
            .AddItem "Views"
        End With
    
    Case "FullTextService"
        ' Display the properties of the FullTextService object.
        FillPropsObj oSQLServer.FullTextService
    
    Case "JobServer"
        ' The JobServer object exposes collections. Fill the lower level
        ' combobox with the collection names and enable the combobox.
        FillPropsObj oJobServer
        
        With cboTwo
            .AddItem "AlertCategories"
            .AddItem "Alerts"
            .AddItem "AlertSystem"
            .AddItem "JobCategories"
            .AddItem "JobFilter"
            .AddItem "JobHistoryFilter"
            .AddItem "Jobs"
            .AddItem "OperatorCategories"
            .AddItem "Operators"
            .AddItem "TargetServerGroups"
            .AddItem "TargetServers"
            .Enabled = True
        End With
        
    Case "IntegratedSecurity"
        ' Simply enumerate the properties of the object.
        FillPropsObj oSQLServer.IntegratedSecurity
    
    Case "Languages"
        ' Fill the list allowing the user to explore individual Language
        ' objects.
        FillPropsColl oSQLServer.Languages, "Languages"
        FillListFromCollection oSQLServer.Languages, lstOne
        
    Case "LinkedServers"
        ' Get the properties of the LinkedServers collection. Fill the list
        ' with enumerated LinkedServer objects in the collection. Add
        ' LinkedServer object collection to the lower level combobox. Selecting
        ' a linked server from the list control enables the combobox.
        FillPropsColl oSQLServer.LinkedServers, "LinkedServers"
        FillListFromCollection oSQLServer.LinkedServers, lstOne
        
        cboTwo.AddItem "LinkedServerLogins"
    
    Case "Logins"
        ' Fill the list allowing the user to explore individual Login
        ' objects.
        FillPropsColl oSQLServer.Logins, "Logins"
        FillListFromCollection oSQLServer.Logins, lstOne
    
    Case "Registry"
        ' Simply enumerate the properties of the object.
        FillPropsObj oSQLServer.Registry
    
    Case "RemoteServers"
        ' Get the properties of the RemoteServers collection. Fill the list
        ' with enumerated RemoteServer objects in the collection. Add
        ' RemoteServer object collection to the lower level combobox. Selecting
        ' a remote server from the list control enables the combobox.
        FillPropsColl oSQLServer.RemoteServers, "RemoteServers"
        FillListFromCollection oSQLServer.RemoteServers, lstOne
        
        cboTwo.AddItem "RemoteLogins"
    
    Case "Replication"
        ' The Replication object exposes collections. Fill the lower level
        ' combobox with the collection names and enable the combobox.
        FillPropsObj oReplication
        
        Set oDistributor = oReplication.Distributor
        Set oPublisher = oReplication.Publisher
        Set oSubscriber = oReplication.Subscriber
        
        With cboTwo
            .AddItem "Distributor"
            .AddItem "Publisher"
            .AddItem "ReplicationDatabases"
            .AddItem "Subscriber"
            .Enabled = True
        End With
        
    Case "ServerRoles"
        ' Fill the list allowing the user to explore individual ServerRole
        ' objects.
        FillPropsColl oSQLServer.ServerRoles, "ServerRoles"
        FillListFromCollection oSQLServer.ServerRoles, lstOne
    
    End Select
    
    If lstOne.ListCount Then
        lstOne.Enabled = True
    Else
        lstOne.Enabled = False
    End If

    frmMain.MousePointer = vbArrowPointer
    Exit Sub

HandleError:
    frmMain.MousePointer = vbArrowPointer
    PrintError
    Resume Next
End Sub
Private Sub cboThree_Click()
    On Error GoTo HandleError
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    'Clear dependent combos and lists.
    DisableList lstFour, cboFour
    
    Select Case cboThree.Text
    ' Table object collections.
    Case "Columns"
        FillPropsColl oCurTable.Columns, "Columns"
        FillListFromCollection oCurTable.Columns, lstThree
        
    Case "Indexes"
        FillPropsColl oCurTable.Indexes, "Indexes"
        FillListFromCollection oCurTable.Indexes, lstThree
        
        cboFour.AddItem "Columns"
        
    Case "Triggers"
        FillPropsColl oCurTable.Triggers, "Triggers"
        FillListFromCollection oCurTable.Triggers, lstThree
        
    Case "Keys"
        FillPropsColl oCurTable.Keys, "Keys"
        FillListFromCollection oCurTable.Keys, lstThree
        
    Case "Checks"
        FillPropsColl oCurTable.Checks, "Checks"
        FillListFromCollection oCurTable.Checks, lstThree
        
    ' FileGroup object collections.
    Case "DBFiles"
        FillPropsColl oCurFileGroup.DBFiles, "DBFiles"
        FillListFromCollection oCurFileGroup.DBFiles, lstThree
            
    ' TransactionLog object collections.
    Case "LogFiles"
        FillPropsColl oCurDB.TransactionLog.LogFiles, "LogFiles"
        FillListFromCollection oCurDB.TransactionLog.LogFiles, lstThree
        
    ' Job object collections.
    Case "JobSchedules"
        FillPropsColl oCurJob.JobSchedules, "JobSchedules"
        FillListFromCollection oCurJob.JobSchedules, lstThree
        
    Case "JobSteps"
        FillPropsColl oCurJob.JobSteps, "JobSteps"
        FillListFromCollection oCurJob.JobSteps, lstThree
    
    ' Distributor object collections.
    Case "DistributionDatabases"
        FillPropsColl oDistributor.DistributionDatabases, "DistributionDatabases"
        FillListFromCollection oDistributor.DistributionDatabases, lstThree
        
    Case "DistributionPublishers"
        FillPropsColl oDistributor.DistributionPublishers, "DistributionPublishers"
        FillListFromCollection oDistributor.DistributionPublishers, lstThree
        
    ' Publisher object collections.
    Case "RegisteredSubscribers"
        FillPropsColl oPublisher.RegisteredSubscribers, "RegisteredSubscribers"
        FillListFromCollection oPublisher.RegisteredSubscribers, lstThree

    ' ReplicationDatabase object collections.
    Case "MergePublications"
        FillPropsColl oCurRepDB.MergePublications, "MergePublications"
        FillListFromCollection oCurRepDB.MergePublications, lstThree
        
        With cboFour
            .AddItem "MergeArticles"
            .AddItem "MergeSubscriptions"
        End With
        
    Case "MergePullSubscriptions"
        FillPropsColl oCurRepDB.MergePullSubscriptions, "MergePullSubscriptions"
        FillListFromCollection oCurRepDB.MergePullSubscriptions, lstThree
        
    Case "ReplicationStoredProcedures"
        FillPropsColl oCurRepDB.ReplicationStoredProcedures, "ReplicationStoredProcedures"
        FillListFromCollection oCurRepDB.ReplicationStoredProcedures, lstThree
        
    Case "ReplicationTables"
        FillPropsColl oCurRepDB.ReplicationTables, "ReplicationTables"
        FillListFromCollection oCurRepDB.ReplicationTables, lstThree
        
        cboFour.AddItem "Columns"
        
    Case "TransPublications"
        FillPropsColl oCurRepDB.TransPublications, "TransPublications"
        FillListFromCollection oCurRepDB.TransPublications, lstThree
        
        With cboFour
            .AddItem "TransArticles"
            .AddItem "TransSubscriptions"
        End With
        
    Case "TransPullSubscriptions"
        FillPropsColl oCurRepDB.TransPullSubscriptions, "TransPullSubscriptions"
        FillListFromCollection oCurRepDB.TransPullSubscriptions, lstThree
        
    End Select
    
    If lstThree.ListCount Then
        lstThree.Enabled = True
    Else
        lstThree.Enabled = False
    End If
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
    
HandleError:
    frmMain.MousePointer = vbArrowPointer
    PrintError
    Resume Next
End Sub
Private Sub cboTwo_Click()
    ' This could take awhile
    frmMain.MousePointer = vbWaitPointer
    
    'Clear dependent combos and lists
    DisableList lstFour, cboFour
    DisableList lstThree, cboThree
    lstTwo.Clear

    Select Case cboTwo.Text
    ' Application object collections.
    Case "ServerGroups"
        FillListFromCollection oSQLServer.Application.ServerGroups, lstTwo
    
    Case "SQLServers"
        FillListFromCollection oSQLServer.Application.SQLServers, lstTwo
    
    ' Configuration object collections.
    Case "ConfigValues"
        FillListFromCollection oSQLServer.Configuration.ConfigValues, lstTwo
    
    ' Database object collections.
    Case "DatabaseRoles"
        FillPropsColl oCurDB.DatabaseRoles, "DatabaseRoles"
        FillListFromCollection oCurDB.DatabaseRoles, lstTwo
        
    Case "Defaults"
        FillPropsColl oCurDB.Defaults, "Defaults"
        FillListFromCollection oCurDB.Defaults, lstTwo
            
    Case "FileGroups"
        FillPropsColl oCurDB.FileGroups, "FileGroups"
        FillListFromCollection oCurDB.FileGroups, lstTwo
        
        cboThree.AddItem "DBFiles"
        
    Case "FullTextCatalogs"
        FillPropsColl oCurDB.FullTextCatalogs, "FullTextCatalogs"
        FillListFromCollection oCurDB.FullTextCatalogs, lstTwo
        
    Case "Rules"
        FillPropsColl oCurDB.Rules, "Rules"
        FillListFromCollection oCurDB.Rules, lstTwo
    
    Case "StoredProcedures"
        FillPropsColl oCurDB.StoredProcedures, "StoredProcedures"
        FillListFromCollection oCurDB.StoredProcedures, lstTwo
    
    Case "SystemDataTypes"
        FillPropsColl oCurDB.SystemDatatypes, "SystemDatatypes"
        FillListFromCollection oCurDB.SystemDatatypes, lstTwo
        
    Case "Tables"
        FillPropsColl oCurDB.Tables, "Tables"
        FillListFromCollection oCurDB.Tables, lstTwo
        
        With cboThree
            .AddItem "Checks"
            .AddItem "Columns"
            .AddItem "Indexes"
            .AddItem "Keys"
            .AddItem "Triggers"
        End With
        
    Case "TransactionLog"
        FillPropsObj oCurDB.TransactionLog
        
        With cboThree
            .AddItem "LogFiles"
            .Enabled = True
        End With
        
    Case "UserDefinedDataTypes"
        FillPropsColl oCurDB.UserDefinedDatatypes, "UserDefinedDatatypes"
        FillListFromCollection oCurDB.UserDefinedDatatypes, lstTwo
        
    Case "Users"
        FillPropsColl oCurDB.Users, "Users"
        FillListFromCollection oCurDB.Users, lstTwo
        
    Case "Views"
        FillPropsColl oCurDB.Views, "Views"
        FillListFromCollection oCurDB.Views, lstTwo
        
    ' JobServer object collections.
    Case "AlertCategories"
        FillPropsColl oJobServer.AlertCategories, "AlertCategories"
        FillListFromCollection oJobServer.AlertCategories, lstTwo
    
    Case "Alerts"
        FillPropsColl oJobServer.Alerts, "Alerts"
        FillListFromCollection oJobServer.Alerts, lstTwo
        
    Case "AlertSystem"
        FillPropsObj oJobServer.AlertSystem
    
    Case "JobCategories"
        FillPropsColl oJobServer.JobCategories, "JobCategories"
        FillListFromCollection oJobServer.JobCategories, lstTwo
    
    Case "JobFilter"
        FillPropsObj oJobServer.JobFilter
    
    Case "JobHistoryFilter"
        FillPropsObj oJobServer.JobHistoryFilter
        
    Case "Jobs"
        FillPropsColl oJobServer.Jobs, "Jobs"
        FillListFromCollection oJobServer.Jobs, lstTwo
        
        With cboThree
            .AddItem "JobSchedules"
            .AddItem "JobSteps"
        End With
        
    Case "OperatorCategories"
        FillPropsColl oJobServer.OperatorCategories, "OperatorCategories"
        FillListFromCollection oJobServer.OperatorCategories, lstTwo
        
    Case "Operators"
        FillPropsColl oJobServer.Operators, "Operators"
        FillListFromCollection oJobServer.Operators, lstTwo
    
    Case "TargetServerGroups"
        FillPropsColl oJobServer.TargetServerGroups, "TargetServerGroups"
        FillListFromCollection oJobServer.TargetServerGroups, lstTwo
    
    Case "TargetServers"
        FillPropsColl oJobServer.TargetServers, "TargetServers"
        FillListFromCollection oJobServer.TargetServers, lstTwo
    
    ' LinkedServer object collections.
    Case "LinkedServerLogins"
        FillPropsColl oCurLnkServer.LinkedServerLogins, "LinkedServerLogins"
        FillListFromCollection oCurLnkServer.LinkedServerLogins, lstTwo
        
    ' RemoteServer object collections.
    Case "RemoteLogins"
        FillPropsColl oCurRemServer.RemoteLogins, "RemoteLogins"
        FillListFromCollection oCurRemServer.RemoteLogins, lstTwo
    
    ' Replication object collections.
    Case "Distributor"
        FillPropsObj oReplication.Distributor
        
        With cboThree
            .AddItem "DistributionDatabases"
            .AddItem "DistributionPublishers"
            .Enabled = True
        End With
                
    Case "Publisher"
        FillPropsObj oReplication.Publisher
        
        With cboThree
            .AddItem "RegisteredSubscribers"
            .Enabled = True
        End With
                
    Case "ReplicationDatabases"
        FillPropsColl oReplication.ReplicationDatabases, "ReplicationDatabases"
        FillListFromCollection oReplication.ReplicationDatabases, lstTwo
        
        With cboThree
            .AddItem "MergePublications"
            .AddItem "MergePullSubscriptions"
            .AddItem "ReplicationStoredProcedures"
            .AddItem "ReplicationTables"
            .AddItem "TransPublications"
            .AddItem "TransPullSubscriptions"
        End With
        
    Case "Subscriber"
        FillPropsObj oReplication.Distributor
        
        With cboThree
            .AddItem "RegisteredPublishers"
            .Enabled = True
        End With
    
    End Select
    
    If lstTwo.ListCount Then
        lstTwo.Enabled = True
    Else
        lstTwo.Enabled = False
    End If
    
    frmMain.MousePointer = vbArrowPointer
End Sub
Private Sub cmdConnect_Click()
    On Error GoTo HandleError
        
    'If we're connected, then disconnect and clear lists
    If bConnected = True Then
        With lstOne
            .Clear
            .Enabled = False
        End With
        
        With cboOne
            .ListIndex = -1
            .Enabled = False
        End With
        
        DisableList lstTwo, cboTwo
        DisableList lstThree, cboThree
        DisableList lstFour, cboFour
        
        txtProperties.Text = "" & NL
        
        lblServer.Enabled = True
        txtServer.Enabled = True
        lblLogin.Enabled = True
        txtLogin.Enabled = True
        lblPassword.Enabled = True
        txtPassword.Enabled = True
        
        cmdConnect.Caption = "&Connect"
        cmdConnect.Default = True
        
        bConnected = False
        
        oSQLServer.DisConnect
        Set oJobServer = Nothing
        Set oReplication = Nothing
        Set oConfiguration = Nothing

        Exit Sub
    End If
    
    'Set mouse pointer to "Wait" cursor
    frmMain.MousePointer = vbWaitPointer
    
    'Attempt a connection, then fill the properties stuff
    oSQLServer.ApplicationName = "SQL-DMO Explorer"
    oSQLServer.Connect txtServer.Text, txtLogin.Text, txtPassword.Text
    oSQLServer.Application.GroupRegistrationServer = ""
    
    lblServer.Enabled = False
    txtServer.Enabled = False
    lblLogin.Enabled = False
    txtLogin.Enabled = False
    lblPassword.Enabled = False
    txtPassword.Enabled = False
    
    cmdConnect.Caption = "&Disconnect"
    cmdConnect.Default = False
    bConnected = True
        
    cboOne.Enabled = True
    lstOne.Enabled = True
        
    oSQLServer.Configuration.ShowAdvancedOptions = True
    
    Set oJobServer = oSQLServer.JobServer
    Set oReplication = oSQLServer.Replication
    Set oConfiguration = oSQLServer.Configuration
    
    FillPropsObj oSQLServer
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
        
HandleError:
    frmMain.MousePointer = vbArrowPointer
    
    PrintError
    Exit Sub
End Sub
Private Sub cmdExit_Click()
    Unload frmMain
End Sub
Private Sub Form_Load()
    On Error Resume Next
    
    NL = Chr$(13) & Chr$(10)
    bConnected = False
    
    Set oSQLServer = New SQLDMO.SQLServer
    oSQLServer.LoginTimeout = 10
    oSQLServer.ODBCPrefix = False
    
    With cboOne
        .Clear
        .AddItem "Application"
        .AddItem "BackupDevices"
        .AddItem "Configuration"
        .AddItem "Databases"
        .AddItem "IntegratedSecurity"
        .AddItem "FullTextService"
        .AddItem "JobServer"
        .AddItem "Languages"
        .AddItem "LinkedServers"
        .AddItem "Logins"
        .AddItem "Registry"
        .AddItem "RemoteServers"
        .AddItem "Replication"
        .AddItem "ServerRoles"
    End With

End Sub
Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    
    If bConnected = True Then
        oSQLServer.DisConnect
    End If
    
    oSQLServer.Close
End Sub

Private Sub lstFour_Click()
    On Error GoTo HandleError
    Dim oQR As SQLDMO.QueryResults
    Dim strExec As String
    Dim strMessage As String
    Dim nProc, num As Integer
    Dim strSProc As String
    Dim strSProcs As String
    Dim strParams As String
    Dim oDBObj As SQLDMO.DBObject
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    Select Case cboFour.Text
        Case "Columns"
            Select Case cboThree.Text
            Case "Indexes"
                FillPropsObj oCurTable.Columns(lstFour.Text)
                
            Case "ReplicationTables"
                FillPropsObj oCurRepTable.Columns(lstFour.Text)
            
            End Select
            
        Case "MergeArticles"
            FillPropsObj oCurMrgPub.MergeArticles(lstFour.Text)
            
        Case "MergeSubscriptions"
            FillPropsObj oCurMrgPub.MergeSubscriptions(lstFour.Text)
            
        Case "TransArticles"
            FillPropsObj oCurTranPub.TransArticles(lstFour.ListIndex + 1)
        
        Case "TransSubscriptions"
            FillPropsObj oCurTranPub.TransSubscriptions(lstFour.ListIndex + 1)
            
        Case "Dist Agent"
            Set oQR = oDistributionPublisher.EnumDistributionAgentSessionDetails(oDistributionPublication.DistributionSubscriptions.Item(1).DistributionAgent, strTimes(lstFour.ListIndex + 1))
            With frmMain.txtProperties
                .Text = ""
                For num = 1 To oQR.Rows
                    .Text = .Text & oQR.GetColumnString(num, 3) & ": "
                    .Text = .Text & NL
               Next
            End With
          
        Case "Snap Agent"
            Set oQR = oDistributionPublisher.EnumSnapshotAgentSessionDetails(oDistributionPublication.SnapshotAgent, strTimes(lstFour.ListIndex + 1))
            With frmMain.txtProperties
                .Text = ""
                For num = 1 To oQR.Rows
                    .Text = .Text & oQR.GetColumnString(num, 3) & ": "
                    .Text = .Text & NL
               Next
            End With
          
        Case "Log Agent"
            Set oQR = oDistributionPublisher.EnumLogReaderAgentSessionDetails(oDistributionPublication.LogReaderAgent, strTimes(lstFour.ListIndex + 1))
            With frmMain.txtProperties
                .Text = ""
                For num = 1 To oQR.Rows
                    .Text = .Text & oQR.GetColumnString(num, 3) & ": "
                    .Text = .Text & NL
               Next
            End With
            
            
    End Select
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
    
HandleError:
    frmMain.MousePointer = vbArrowPointer
    PrintError
End Sub
Private Sub lstOne_Click()
    On Error GoTo HandleError
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    Set oCurDB = Nothing
    Set oCurLnkServer = Nothing
    Set oCurRemServer = Nothing
    
    Select Case cboOne.Text
    Case "BackupDevices"
        ' Get the properties of the selected BackupDevice object.
        FillPropsObj oSQLServer.BackupDevices(lstOne.Text)
        
    Case "Databases"
        ' Get the properties of the selected Database object. Record
        ' the selection for exploration of Database collections and objects.
        Set oCurDB = oSQLServer.Databases(lstOne.Text)
        FillPropsObj oCurDB
        
    Case "Languages"
        ' Get the properties of the selected Language object.
        FillPropsObj oSQLServer.Languages(lstOne.Text)
        
    Case "LinkedServers"
        ' Get the properties of the selected LinkedServer object. Record
        ' the selection for exploration of database objects.
        Set oCurLnkServer = oSQLServer.LinkedServers(lstOne.Text)
        FillPropsObj oCurLnkServer
        
    Case "Logins"
        ' Get the properties of the selected Login object.
        FillPropsObj oSQLServer.Logins(lstOne.Text)
        
    Case "RemoteServers"
        ' Get the properties of the selected RemoteServer object. Record
        ' the selection for exploration of RemoteServer collections.
        Set oCurRemServer = oSQLServer.RemoteServers(lstOne.Text)
        FillPropsObj oCurRemServer
        
    Case "ServerRoles"
        ' Get the properties of the selected ServerRole object.
        FillPropsObj oSQLServer.ServerRoles(lstOne.Text)
        
    End Select

    If cboTwo.ListCount Then
        cboTwo.Enabled = True
    End If

    cboTwo_Click
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
    
HandleError:
    frmMain.MousePointer = vbArrowPointer
    PrintError
End Sub
Private Sub lstThree_Click()
    On Error GoTo HandleError
    
    Dim oQR As SQLDMO.QueryResults
    Dim oDBObj As SQLDMO.DBObject
    Dim ret As Integer
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    Set oCurMrgPub = Nothing
    Set oCurTranPub = Nothing
    Set oCurRepTable = Nothing
    
    Select Case cboThree.Text
    ' Table object collections.
    Case "Columns"
        FillPropsObj oCurTable.Columns(lstThree.Text)
    
    Case "Indexes"
        Set oCurIndex = oCurTable.Indexes(lstThree.Text)
        FillPropsObj oCurIndex
        
        cboFour_Click
        
    Case "Triggers"
        FillPropsObj oCurTable.Triggers(lstThree.Text)
        
    Case "Keys"
        FillPropsObj oCurTable.Keys(lstThree.Text)
        
    Case "Checks"
        FillPropsObj oCurTable.Checks(lstThree.Text)
    
    ' DBFile object.
    Case "DBFiles"
        FillPropsObj oCurFileGroup.DBFiles(lstThree.ListIndex + 1)
    
    ' Job object collections.
    Case "JobSchedules"
        FillPropsObj oCurJob.JobSchedules(lstThree.ListIndex + 1)
    
    Case "JobSteps"
        FillPropsObj oCurJob.JobSteps(lstThree.List(lstThree.ListIndex))
            
    Case "LogFiles"
        FillPropsObj oCurDB.TransactionLog.LogFiles(lstThree.ListIndex + 1)
    
    Case "DistributionDatabases"
        FillPropsObj oReplication.Distributor.DistributionDatabases(lstThree.Text)
    
    Case "DistributionPublishers"
    
        'Get information for the selected Publisher
        FillPropsObj oReplication.Distributor.DistributionPublishers(lstThree.Text)
        Set oDistributionPublisher = oReplication.Distributor.DistributionPublishers(lstThree.Text)
        
        Set oDistributionPublication = oDistributionPublisher.DistributionPublications.Item(1)
     
        lstFour.Clear
        cboFour.Clear
        With cboFour
                .AddItem "Dist Agent"
                .AddItem "Snap Agent"
                .AddItem "Log Agent"
        End With
        cboFour_Click
     
    Case "MergePublications"
        Set oCurMrgPub = oCurRepDB.MergePublications(lstThree.ListIndex + 1)
        FillPropsObj oCurMrgPub
                
    Case "MergePullSubscriptions"
        FillPropsObj oCurRepDB.MergePullSubscriptions(lstThree.ListIndex + 1)
    
    Case "ReplicationStoredProcedures"
        FillPropsObj oCurRepDB.ReplicationStoredProcedures(lstThree.ListIndex + 1)
    
    Case "ReplicationTables"
        Set oCurRepTable = oCurRepDB.ReplicationTables(lstThree.Text)
        FillPropsObj oCurRepTable
    
    Case "TransPublications"
        Set oCurTranPub = oCurRepDB.TransPublications(lstThree.ListIndex + 1)
        FillPropsObj oCurTranPub
                
    Case "TransPullSubscriptions"
        FillPropsObj oCurRepDB.TransPullSubscriptions(lstThree.ListIndex + 1)
    
    End Select
    
    If cboFour.ListCount Then
        cboFour.Enabled = True
    End If
    
    cboFour_Click
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
    
HandleError:
    frmMain.MousePointer = vbArrowPointer
    PrintError
End Sub
Private Sub lstTwo_Click()
    On Error GoTo HandleError
    
    Set oCurFileGroup = Nothing
    Set oCurTable = Nothing
    Set oCurJob = Nothing
    Set oCurRepDB = Nothing
    
    ' Any SQL Server access involves time. Set the MousePointer to "wait"
    ' to provide feedback.
    frmMain.MousePointer = vbWaitPointer
    
    Select Case cboTwo.Text
    ' Configuration object ConfigValues collection.
    Case "ConfigValues"
        ' Display the properties of the selected ConfigValue object.
        FillPropsObj oConfiguration.ConfigValues(lstTwo.Text)
    
    ' Database object collections.
    Case "Defaults"
        ' Display the properties of the selected Default object.
        FillPropsObj oCurDB.Defaults(lstTwo.Text)
        
    Case "DatabaseRoles"
        ' Display the properties of the selected DatabaseRole object.
        FillPropsObj oCurDB.DatabaseRoles(lstTwo.Text)
        
    Case "FileGroups"
        ' Display the properties of the selected FileGroup object.
        Set oCurFileGroup = oCurDB.FileGroups(lstTwo.Text)
        FillPropsObj oCurDB.FileGroups(lstTwo.Text)
        
    Case "FullTextCatalogs"
        ' Display the properties of the selected FullTextCatalog object.
        FillPropsObj oCurDB.FullTextCatalogs(lstTwo.Text)
        
    Case "Rules"
        ' Display the properties of the selected Rule object.
        FillPropsObj oCurDB.Rules(lstTwo.Text)
        
    Case "StoredProcedures"
        ' Display the properties of the selected StoredProcedure object.
        FillPropsObj oCurDB.StoredProcedures(lstTwo.Text)
        
    Case "SystemDataTypes"
        ' Display the properties of the selected SystemDataType object.
        FillPropsObj oCurDB.SystemDatatypes(lstTwo.Text)
        
    Case "Tables"
        ' Display the properties of the selected Table object.
        Set oCurTable = oCurDB.Tables(lstTwo.Text)
        FillPropsObj oCurTable
        
    Case "UserDefinedDataTypes"
        ' Display the properties of the selected UserDefinedDataType object.
        FillPropsObj oCurDB.UserDefinedDatatypes(lstTwo.Text)
        
    Case "Users"
        ' Display the properties of the selected User object.
        FillPropsObj oCurDB.Users(lstTwo.Text)
        
    Case "Views"
        ' Display the properties of the selected View object.
        FillPropsObj oCurDB.Views(lstTwo.Text)
        
    ' JobServer object collections.
    Case "AlertCategories"
        ' Display the properties of the selected AlertCategory object.
        FillPropsObj oJobServer.AlertCategories(lstTwo.Text)
        
    Case "Alerts"
        ' Display the properties of the selected Alert object.
        FillPropsObj oJobServer.Alerts(lstTwo.Text)
        
    Case "JobCategories"
        ' Display the properties of the selected JobCategory object.
        FillPropsObj oJobServer.JobCategories(lstTwo.Text)
        
    Case "Jobs"
        ' Display the properties of the selected Job object.
        Set oCurJob = oJobServer.Jobs(lstTwo.Text)
        FillPropsObj oCurJob
        
    Case "OperatorCategories"
        ' Display the properties of the selected OperatorCategory object.
        FillPropsObj oJobServer.OperatorCategories(lstTwo.Text)
        
    Case "Operators"
        ' Display the properties of the selected Operator object.
        FillPropsObj oJobServer.Operators(lstTwo.Text)
        
    Case "TargetServerGroups"
        ' Display the properties of the selected TargetServerGroup object.
        FillPropsObj oJobServer.TargetServerGroups(lstTwo.Text)
        
    Case "TargetServers"
        ' Display the properties of the selected TargetServer object.
        FillPropsObj oJobServer.TargetServers(lstTwo.Text)
    
    ' LinkedServer object, LinkedServerLogins collection.
    Case "LinkedServerLogins"
        ' Display the properties of the selected LinkedServerLogin object.
        FillPropsObj oCurLnkServer.LinkedServerLogins(lstTwo.Text)
    
    ' RemoteServer object, RemoteLogins collection.
    Case "RemoteLogins"
        ' Display the properties of the selected RemoteLogin object.
        FillPropsObj oCurRemServer.RemoteLogins(lstTwo.Text)
    
    ' Replication object, ReplicationDatabases collection.
    Case "ReplicationDatabases"
        ' Display the properties of the selected ReplicationDatabase object.
        Set oCurRepDB = oReplication.ReplicationDatabases(lstTwo.Text)
        FillPropsObj oCurRepDB
        
    End Select
    
    If cboThree.ListCount Then
        cboThree.Enabled = True
    End If
    
    cboThree_Click
    
    frmMain.MousePointer = vbArrowPointer
    Exit Sub
    
HandleError:
    frmMain.MousePointer = vbArrowPointer
    PrintError
End Sub
Private Sub oSQLServer_CommandSent(ByVal SQLCommand As String)
'    MsgBox SQLCommand$, vbInformation, "SQL Server Command Sent"
    Exit Sub
End Sub
Private Function oSQLServer_ConnectionBroken(ByVal Message As String) As Boolean
    cmdConnect.Caption = "&Connect"
    bConnected = False
End Function
Private Function oSQLServer_QueryTimeout(ByVal Message As String) As Boolean
    MsgBox Message$
End Function
Private Sub oSQLServer_RemoteLoginFailed(ByVal Severity As Long, ByVal MessageNumber As Long, ByVal MessageState As Long, ByVal Message As String)
    If MessageNumber <> 0 Then
        Dim strMsg As String
    
        strMsg$ = "Number: " & MessageNumber & NL & "Text: " & Message
        MsgBox strMsg$, vbExclamation, "SQL Server Remote Login Failure"
    End If
End Sub
Private Sub oSQLServer_ServerMessage(ByVal Severity As Long, ByVal MessageNumber As Long, ByVal MessageState As Long, ByVal Message As String)
'    If MessageNumber <> 0 Then
'        Dim strMsg As String
    
'        strMsg$ = "Number: " & MessageNumber & NL & "Text: " & Message
'        MsgBox strMsg$, vbInformation, "SQL Server Information"
'    End If
End Sub
Sub DisableList(lst As ListBox, cbo As ComboBox)
    With cbo
        .Clear
        .Enabled = False
    End With
    
    With lst
        .Clear
        .Enabled = False
    End With
End Sub
Sub FillListFromCollection(oCollection As Object, lst As ListBox)
    On Error GoTo HandleError
    lst.Clear
    
    Dim oObject As Object
    For Each oObject In oCollection
        Select Case oObject.TypeOf
        Case SQLDMOObj_TargetServer
            lst.AddItem oObject.ServerName
            
        Case SQLDMOObj_RemoteLogin
            lst.AddItem oObject.LocalName
            
        Case SQLDMOObj_LinkedServerLogin
            lst.AddItem oObject.LocalLogin
            
        Case Else
            lst.AddItem oObject.Name
        End Select
NoValue:
    Next oObject
    
    Exit Sub
    
HandleError:
    PrintError
    Resume NoValue
End Sub
Sub FillPropsColl(oCollection As Object, strName As String)
    On Error GoTo HandleError

    With frmMain.txtProperties
        .Text = "Properties for: " & strName
        .Text = .Text & NL
        
        .Text = .Text & "Count: " & oCollection.Count
        .Text = .Text & NL
    End With
    Exit Sub

HandleError:
    PrintError
    Exit Sub
End Sub
Sub FillPropsObj(oObject As Object)
    On Error GoTo HandleError

    Dim oProperty As Object
    With frmMain.txtProperties
        .Text = ""
        For Each oProperty In oObject.Properties
            .Text = .Text & oProperty.Name & ": "
            .Text = .Text & oProperty.Value
NoValue:
            .Text = .Text & NL
        Next
    End With
    
    Exit Sub

HandleError:
    If Err.Number = 438 Then
        With frmMain.txtProperties
            .Text = .Text & "Value is write-only"
        End With
        Resume Next
    Else
        PrintError
        Resume NoValue
    End If
End Sub
Sub PrintError()
    Dim errString As String
    
    If Err.Number <> 0 Then
        errString$ = Err.Source & " Error " & Err.Number & ": " & Err.Description
        MsgBox errString$
    End If
End Sub
Private Sub txtServer_Change()
    If Len(txtServer.Text) Then
        cmdConnect.Enabled = True
    Else
        cmdConnect.Enabled = False
    End If
End Sub
