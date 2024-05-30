VERSION 5.00
Begin VB.Form frmInstall 
   Caption         =   "Hanson Brothers COM+ Application Installer"
   ClientHeight    =   6195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5850
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6195
   ScaleWidth      =   5850
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   495
      Left            =   3840
      TabIndex        =   13
      Top             =   5520
      Width           =   1815
   End
   Begin VB.ListBox lstStatusList 
      Height          =   1230
      Left            =   360
      TabIndex        =   12
      TabStop         =   0   'False
      Top             =   4560
      Width           =   3255
   End
   Begin VB.Frame Frame3 
      Caption         =   "Installation Status:"
      Height          =   1695
      Left            =   240
      TabIndex        =   16
      Top             =   4320
      Width           =   3495
   End
   Begin VB.CommandButton InstallAllTBut 
      Caption         =   "Install All Components"
      Height          =   1035
      Left            =   3840
      TabIndex        =   0
      Top             =   4440
      Width           =   1815
   End
   Begin VB.Frame Frame2 
      Caption         =   "Application Components:"
      Height          =   4035
      Left            =   120
      TabIndex        =   14
      Top             =   120
      Width           =   2775
      Begin VB.CommandButton HBITBut 
         Caption         =   "Install HBInstitution"
         Height          =   855
         Left            =   120
         TabIndex        =   1
         Top             =   300
         Width           =   2535
      End
      Begin VB.CommandButton HBETBut 
         Caption         =   "Install HBExchange"
         Height          =   855
         Left            =   120
         TabIndex        =   2
         Top             =   1215
         Width           =   2535
      End
      Begin VB.CommandButton HBNTBut 
         Caption         =   "Install HBNotify"
         Height          =   855
         Left            =   120
         TabIndex        =   3
         Top             =   2145
         Width           =   2535
      End
      Begin VB.CommandButton HBWTBut 
         Caption         =   "Install HBNews"
         Height          =   855
         Left            =   120
         TabIndex        =   4
         Top             =   3060
         Width           =   2535
      End
   End
   Begin VB.CheckBox TransientCBut 
      Caption         =   "Subscribe Transient"
      Height          =   255
      Left            =   3120
      TabIndex        =   10
      Top             =   3120
      Width           =   2055
   End
   Begin VB.CheckBox PersistCBut 
      Caption         =   "Subscribe Persistent"
      Height          =   255
      Left            =   3120
      TabIndex        =   9
      Top             =   2820
      Width           =   1815
   End
   Begin VB.TextBox NewsTEd 
      Height          =   375
      Left            =   3120
      TabIndex        =   8
      Text            =   "Hanson Brothers News Headline"
      Top             =   2400
      Width           =   2535
   End
   Begin VB.CommandButton CreateSub 
      Caption         =   "Create HBSubcription"
      Height          =   615
      Left            =   3120
      TabIndex        =   6
      Top             =   1020
      Width           =   2535
   End
   Begin VB.CommandButton InstallEC 
      Caption         =   "Install HBEventClass"
      Height          =   615
      Left            =   3120
      TabIndex        =   5
      Top             =   360
      Width           =   2535
   End
   Begin VB.CommandButton Fire 
      Caption         =   "Publish NewsHeadline"
      Height          =   615
      Left            =   3120
      TabIndex        =   7
      Top             =   1680
      Width           =   2535
   End
   Begin VB.Frame Frame1 
      Caption         =   "Event Components:"
      Height          =   4035
      Left            =   3000
      TabIndex        =   15
      Top             =   120
      Width           =   2775
      Begin VB.CommandButton cmdXML 
         Caption         =   "Install XML Sample"
         Height          =   615
         Left            =   120
         TabIndex        =   11
         Top             =   3300
         Width           =   2535
      End
   End
   Begin VB.Frame Frame4 
      Height          =   1935
      Left            =   120
      TabIndex        =   17
      Top             =   4200
      Width           =   5655
   End
End
Attribute VB_Name = "frmInstall"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  HBInstall.FRM
'*
'*  This file is provided as part of the COM+ Software Development Kit.
'*
'*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
'*  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'*  OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR PURPOSE.
'*
'* Copyright (C) 1999 Microsoft Corporation, All rights reserved
'**************************************************************************************
'\***********************************************************************************/

Implements HBEVENTCLASSLib.INewsService
Implements HBEventClass



Private Sub cmdClose_Click()
    Unload Me
End Sub

Private Sub cmdXML_Click()
    EnableAllButtons (False)
    Call MaintainApp("HBXMLServer", "XML")
    EnableAllButtons (True)
End Sub

Private Sub HBETBut_Click()
    EnableAllButtons (False)
    Call MaintainApp("HBExchange")
    EnableAllButtons (True)
End Sub

Public Sub HBEventClass_NewEvent(ByVal str As String)
    MsgBox ("HBEventClass_NewEvent: " & str)
End Sub

Private Sub HBITBut_Click()
    EnableAllButtons (False)
    Call MaintainApp("HBInstitution")
    EnableAllButtons (True)
End Sub

Private Sub MaintainApp(ByVal sName As String, Optional sDir As String)

    Dim Catalog  As COMAdminCatalog
    Dim Applications As COMAdminCatalogCollection
    Dim AppCatalog As ICatalogObject
    Dim bFound As Boolean
    Dim sDLL As String
        
    On Error GoTo AppError
    
    App.OleServerBusyMsgText = "HBInstall: Catalog Not Responding. If Persists, Please Shutdown HBInstall process with Task Manager and Restart DTC"
    App.OleServerBusyMsgTitle = "HBInstall: Catalog Busy"
    App.OleServerBusyTimeout = 5000
    
    App.OleRequestPendingMsgText = "HBInstall: Catalog Pending... If Persists, Please Shutdown HBInstall process with Task Manager and Restart DTC"
    App.OleRequestPendingMsgTitle = "HBInstall: Catalog Pending"
    App.OleRequestPendingTimeout = 2000
    
    ' Instantiate a COMAdminCatalog object
    Set Catalog = New COMAdminCatalog
     
    ' Get the "Applications" collection from the catalog, and populate it
    Set Applications = Catalog.GetCollection("Applications")
    Applications.Populate
    
    ' Check to see if this is an existing Application, if it is remove it
    ' from the catalog and save the changes to the catalog
    For i = 0 To Applications.Count - 1
        If Applications.Item(i).Name = sName Then
            Applications.Remove i
            Applications.SaveChanges
            Exit For
        End If
    Next
    
    ' Add the new Application to the catalog
    Set AppCatalog = Applications.Add
    AppCatalog.Value("Name") = sName
    
    ' Check to see if the Application contains any queued components, if it does
    ' set up the "Queued" and "Listen" properties on the "Queuing" tab
    If sName = "HBNotify" Or sName = "HBExchange" Or sName = "HBNews" Then
            AppCatalog.Value("QueuingEnabled") = True
            AppCatalog.Value("QueueListenerEnabled") = True
    End If
           
    ' Save changes made to the Applications collection
    Applications.SaveChanges
           
    If Not sDir <> "" Then
        sDLL = "..\Components\" & sName & "\" & sName & ".dll"
    Else
        sDLL = "..\" & sDir & "\" & sName & "\" & sName & ".dll"
    End If
    
    ' Install components into the Application
    Catalog.InstallComponent sName, sDLL, "", ""
           
    ' Check to see if the Application contains any queued components, if it does
    ' set up the "Queued" property on the required interfaces
    If sName = "HBNotify" Or sName = "HBExchange" Or sName = "HBNews" Then
            Call SetUpQueuingOnInterfaces(sName, Catalog)
    End If
           
    ' Clean up
    Set Catalog = Nothing
    
    lstStatusList.AddItem (sName & " COM+ Application Installed.")
    
    Exit Sub
        
AppError:
    MsgBox "" & sName & " COM+ App Error: " & Hex$(Err.Number) & ": " & Err.Description

End Sub

Private Sub SetUpQueuingOnInterfaces(ByVal sName As String, ByRef Catalog As COMAdminCatalog)
    
    Dim Applications As COMAdminCatalogCollection
    Dim AppCatalog As ICatalogObject
    Dim Comp As ICatalogObject
    Dim Inter As ICatalogObject
    Dim Components As COMAdminCatalogCollection
    Dim Interfaces As COMAdminCatalogCollection
    Dim bFound As Boolean
    Dim sDLL As String
    
    On Error GoTo SubError:
    
    Select Case sName
        
        Case "HBNotify"
            ' Get the Application collection, and populate it, then iterate thru
            ' until we find the COM+ Application of interest
            Set Applications = Catalog.GetCollection("Applications")
            Applications.Populate
                        
            For Each AppCatalog In Applications
                If AppCatalog.Name = sName Then Exit For
            Next
            
            ' Get the components collection, and populate it, then iterate thru
            ' until we find the component of interest
            Set Components = Applications.GetCollection("Components", AppCatalog.Key)
            Components.Populate
            
            For Each Comp In Components
                If Comp.Name = "HBNotify.INotify" Then Exit For
            Next
            
            ' Get the interfaces collection, and populate it, then iterate thru
            ' until we find the interface of interest
            Set Interfaces = Components.GetCollection("InterfacesForComponent", Comp.Key)
            Interfaces.Populate
            
            For Each Inter In Interfaces
                If Inter.Name = "_INotify" Then Exit For
            Next
            
            ' Enable this interface to be queued
            Inter.Value("QueuingEnabled") = True
            
            ' Save the changes to the interface collection
            Interfaces.SaveChanges
            
        Case "HBExchange"
            ' Get the Application collection, and populate it
            Set Applications = Catalog.GetCollection("Applications")
            Applications.Populate
            
            For Each AppCatalog In Applications
                If AppCatalog.Name = sName Then Exit For
            Next
            
            ' Get the components collection, and populate it
            Set Components = Applications.GetCollection("Components", AppCatalog.Key)
            Components.Populate
            
            For Each Comp In Components
                If Comp.Name = "HBExchange.IExchangeOrder" Then Exit For
            Next
            
            ' Get the interfaces collection, and populate it
            Set Interfaces = Components.GetCollection("InterfacesForComponent", Comp.Key)
            Interfaces.Populate
            
            For Each Inter In Interfaces
                If Inter.Name = "_IExchangeOrder" Then Exit For
            Next
            
            ' Enable this interface to be queued
            Inter.Value("QueuingEnabled") = True
            
            Interfaces.SaveChanges
        
        Case "HBNews"
            ' Get the Application collection, and populate it
            Set Applications = Catalog.GetCollection("Applications")
            Applications.Populate
            
            For Each AppCatalog In Applications
                If AppCatalog.Name = sName Then Exit For
            Next
            
            ' Get the components collection, and populate it
            Set Components = Applications.GetCollection("Components", AppCatalog.Key)
            Components.Populate
            
            For Each Comp In Components
                If Comp.Name = "HBNews.INews" Then Exit For
            Next
            
            ' Get the interfaces collection, and populate it
            Set Interfaces = Components.GetCollection("InterfacesForComponent", Comp.Key)
            Interfaces.Populate
            
            For Each Inter In Interfaces
                If Inter.Name = "_INews" Then Exit For
            Next
            
            ' Enable this interface to be queued
            Inter.Value("QueuingEnabled") = True
            
            Interfaces.SaveChanges
        
    End Select
    
    Exit Sub
SubError:
    MsgBox "" & sName & " COM+ App Error: " & Hex$(Err.Number) & ": " & Err.Description
End Sub


Private Sub HBNTBut_Click()
    EnableAllButtons (False)
    Call MaintainApp("HBNotify")
    EnableAllButtons (True)
End Sub

Private Sub HBWTBut_Click()
    EnableAllButtons (False)
    Call MaintainApp("HBNews")
    EnableAllButtons (True)
End Sub

Public Sub INewsService_NewsHeadline(ByVal str As String)
    MsgBox ("INewsService_NewsHeadline: " & str)
End Sub

Public Sub INewsService_HotNews(ByVal str As String)
    MsgBox ("INewsService_HotNews: " & str)
End Sub

Private Sub SubscribeTransient()

    Dim TransColl As ICatalogCollection
    Dim Trans As ICatalogObject
    Dim Admin As Object
    
    On Error GoTo SubError

    Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")
    Set TransColl = Admin.GetCollection("TransientSubscriptions")
    
    TransColl.Populate
    
    ' Create subscription object

    Set Trans = TransColl.Add
    Trans.Value("Name") = "HBTransient"
    Trans.Value("EventCLSID") = "HBEventClass.HBEventClass.1"
    Trans.Value("SubscriberInterface") = Me
    TransColl.SaveChanges
    
    lstStatusList.AddItem ("HBEventClass Transient Subscription made.")
    
Exit Sub

SubError:
    MsgBox "HB Transient Subscription Error: " & Hex$(Err.Number) & ": " & Err.Description
End Sub

Private Sub SubscribePersistent()
    Dim Admin As Object
    Dim AppColl, Compcoll, Subcoll As ICatalogCollection
    Dim AppCatalog, Comp, Subscription As ICatalogObject
    Dim bFound As Boolean
    
    On Error GoTo SubError
    
    Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")
     
    ' Create an Application to host EventClass
    Set AppColl = Admin.GetCollection("Applications")
    
    AppColl.Populate
    
    bFound = False
    For i = 0 To AppColl.Count - 1
        If AppColl.Item(i).Name = "HBSubscriber" Then
            bFound = True
        End If
    Next
    
    If bFound Then
        If MsgBox("HBSubscriber COM+ App already Created. Subscribe Again?", vbYesNo) = vbNo Then
            Exit Sub
        End If
    Else
        Set AppCatalog = AppColl.Add
        AppCatalog.Value("Name") = "HBSubscriber"
        AppColl.SaveChanges
    
        ' Install a component under the eventclass
        Admin.InstallComponent "HBSubscriber", "..\HBNewEvents\HBSubscriber\Debug\HBSubscriber.dll", "", ""
    
        '------------------------------------------------
        ' Create a subscription under this component
        '------------------------------------------------
        AppColl.Populate
    End If
    
    ' Get the COMPONENTS collection
    For i = 0 To AppColl.Count - 1
        If AppColl.Item(i).Name = "HBSubscriber" Then
            Set Compcoll = AppColl.GetCollection("Components", AppColl.Item(i).Key)
        End If
    Next
    
    Compcoll.Populate
    
    ' Get the SUBSCRIPTIONS collection
    For i = 0 To Compcoll.Count - 1
        If Compcoll.Item(i).Name = "HBSubscriber.HBSubscriber.1" Then
        
            Set Subcoll = Compcoll.GetCollection("SubscriptionsForComponent", Compcoll.Item(i).Key)
        
            Subcoll.Populate
    
            If PersistCBut.Value = 1 Then
                ' Set the properties on the subscription
                Set Subscription = Subcoll.Add
                Subscription.Value("PublisherID") = "Hanson"
                Subscription.Value("Enabled") = True
                Subscription.Value("Name") = "HB Test Subscription"
    
                Subcoll.SaveChanges
                
                lstStatusList.AddItem ("HB Test Subscription Created.")
            End If
    
            If TransientCBut.Value = 1 Then
                ' Set the properties on the subscription
                Set Subscription = Subcoll.Add
                Subscription.Value("PublisherID") = "Hanson"
                Subscription.Value("Enabled") = True
                Subscription.Value("Name") = "HB Trader Test Subscription"
    
                Subcoll.SaveChanges
                
                lstStatusList.AddItem ("HB Trader Subscription Created.")
            End If
        
        End If
    Next

Exit Sub

SubError:
MsgBox "Error: You probably have a 'HBSubscription COM+ Application already added. Delete it and try again. NOTE: Make sure you refresh (F5) the COM+ Applications First so you can see them." & Hex$(Err.Number) & ": " & Err.Description

End Sub

Private Sub CreateSub_Click()

    EnableAllButtons (False)
    
    If PersistCBut.Value = 0 And TransientCBut.Value = 0 Then
        MsgBox ("No Subscribers are Checked. Select Subscriber Check Boxe(s)")
        Exit Sub
    End If
    
    If TransientCBut.Value = 1 Then
        Call SubscribeTransient
        Exit Sub
    End If
    
    If PersistCBut.Value = 1 Then
        Call SubscribePersistent
        Exit Sub
    End If
    
    EnableAllButtons (True)

End Sub

Private Sub Fire_Click()
    Dim HB As IHB
    Dim NewsService As INewsService
    
    On Error GoTo check
    EnableAllButtons (False)

    Set HB = CreateObject("HBEventClass.HBEventClass.1")
    Set NewsService = HB
    
    'HB.NewEvent ("Dummy")
    'NewsService.HotNews ("HotNews")
    NewsService.NewsHeadline (NewsTEd.Text)
    
    EnableAllButtons (True)
    
Exit Sub
    
check:
    MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub

Private Sub InstallAllTBut_Click()
    EnableAllButtons (False)
    
    lstStatusList.AddItem ("Please wait, installing ...")

    Call MaintainApp("HBInstitution")
    Call MaintainApp("HBExchange")
    Call MaintainApp("HBNotify")
    Call MaintainApp("HBNews")
    Call CreateEventClass
    Call MaintainApp("HBXMLServer", "XML")
    
    EnableAllButtons (True)
End Sub

Private Sub EnableAllButtons(ByVal bEnable As Boolean)
    cmdClose.Enabled = bEnable
    HBITBut.Enabled = bEnable
    HBETBut.Enabled = bEnable
    HBNTBut.Enabled = bEnable
    HBWTBut.Enabled = bEnable
    InstallEC.Enabled = bEnable
    CreateSub.Enabled = bEnable
    Fire.Enabled = bEnable
    PersistCBut.Enabled = bEnable
    TransientCBut.Enabled = bEnable
    InstallAllTBut.Enabled = bEnable
    NewsTEd.Enabled = bEnable
    cmdXML.Enabled = bEnable
End Sub
Private Sub InstallEC_Click()
    EnableAllButtons (False)
    CreateEventClass
    EnableAllButtons (True)
End Sub

Private Sub CreateEventClass()

    Dim Admin As Object
    Dim AppColl, Compcoll As ICatalogCollection
    Dim AppCatalog, Comp, Itrobj, Eventobj As ICatalogObject
    Dim bFound As Boolean
    
    On Error GoTo check
    
    Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")
    
    ' Create an Application to host EventClass
    Set AppColl = Admin.GetCollection("Applications")
    AppColl.Populate
    
    bFound = False
    For i = 0 To AppColl.Count - 1
        If AppColl.Item(i).Name = "HBEventClass" Then
            bFound = True
        End If
    Next
    
    If bFound Then
        MsgBox ("HBEventClassApp COM+ App already Created")
        Exit Sub
    Else
        Set AppCatalog = AppColl.Add
        AppCatalog.Value("Name") = "HBEventClass"
    
        AppColl.SaveChanges
    
        ' Install the eventclass under the created application
        Var = "..\HBNewEvents\HBEventClass\Debug\HBEventClass.dll"
        Admin.InstallEventClass "HBEventClass", Var, "", ""
    
        ' Set other EventClass properties
        AppColl.Populate
    End If
    
    For i = 0 To AppColl.Count - 1
        If AppColl.Item(i).Name = "HBEventClass" Then
        Set Compcoll = AppColl.GetCollection("Components", AppColl.Item(i).Key)
        Compcoll.Populate
        End If
    Next
        
    
    For i = 0 To Compcoll.Count - 1
        If Compcoll.Item(i).Name = "HBEventClass.HBEventClass.1" Then
        Set Eventobj = Compcoll.Item(i)
        Eventobj.Value("FireInParallel") = True
        Eventobj.Value("AllowInprocSubscribers") = True
        Eventobj.Value("PublisherID") = "Hanson"
        'Eventobj.Value("MultiInterfacePublisherFilterCLSID") = "HBFilter.HBFilter.1"
        
        Compcoll.SaveChanges
        
        lstStatusList.AddItem ("HBEventClass COM+ Application Installed.")
        
        End If
    Next
    
    Exit Sub
check:
    MsgBox "Error Creating HBEventClass COM+ App. " & Hex$(Err.Number) & ": " & Err.Description

End Sub

