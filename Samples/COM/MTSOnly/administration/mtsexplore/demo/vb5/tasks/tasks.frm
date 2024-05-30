VERSION 5.00
Begin VB.Form Tasks 
   Caption         =   "Task Samples"
   ClientHeight    =   8175
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4980
   LinkTopic       =   "Form1"
   ScaleHeight     =   8175
   ScaleWidth      =   4980
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton RemoteComp 
      Caption         =   "Configure Client to Use Remote Components"
      Height          =   495
      Left            =   360
      TabIndex        =   10
      Top             =   6360
      Width           =   4215
   End
   Begin VB.CommandButton Export 
      Caption         =   "Export Package "
      Height          =   495
      Left            =   360
      TabIndex        =   9
      Top             =   5760
      Width           =   4215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Configuring Security Role "
      Height          =   495
      Left            =   360
      TabIndex        =   8
      Top             =   5160
      Width           =   4215
   End
   Begin VB.CommandButton RemoteUpdate 
      Caption         =   "Update Package on Remote Server"
      Height          =   495
      Left            =   360
      TabIndex        =   7
      Top             =   4560
      Width           =   4215
   End
   Begin VB.CommandButton PropInfo 
      Caption         =   "Access Property Info"
      Height          =   495
      Left            =   360
      TabIndex        =   6
      Top             =   3960
      Width           =   4215
   End
   Begin VB.CommandButton Related 
      Caption         =   "Access Related Collection Names"
      Height          =   495
      Left            =   360
      TabIndex        =   5
      Top             =   3360
      Width           =   4215
   End
   Begin VB.CommandButton PackDelete 
      Caption         =   "Browse for installed package and Delete"
      Height          =   495
      Left            =   360
      TabIndex        =   4
      Top             =   2760
      Width           =   4215
   End
   Begin VB.CommandButton BrowseUpdate 
      Caption         =   "Browse for installed Package and Update Properties"
      Height          =   495
      Left            =   360
      TabIndex        =   3
      Top             =   1560
      Width           =   4215
   End
   Begin VB.CommandButton BrowseDelete 
      Caption         =   "Browse for installed component and Delete"
      Height          =   495
      Left            =   360
      TabIndex        =   2
      Top             =   2160
      Width           =   4215
   End
   Begin VB.CommandButton CreatePackage 
      Caption         =   "Create New Package and Install Components"
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   960
      Width           =   4215
   End
   Begin VB.CommandButton InstallPackage 
      Caption         =   "Install Pre-built Package"
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   4215
   End
End
Attribute VB_Name = "Tasks"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub BrowseDelete_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim pack As Object
    Dim componentsInPack As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    packages.populate
    For Each pack In packages
        If pack.Name = "My Package" Then
            Set componentsInPack = packages.GetCollection("ComponentsInPackage", pack.Key)
            componentsInPack.populate
            For i = 0 To componentsInPack.Count
                Set comp = componentsInPack.Item(i)
                If comp.Name = "Bank.Account" Then
                    componentsInPack.Remove (i)
                    componentsInPack.savechanges
                    Exit For
                End If
            Next
            Exit For
        End If
    Next
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub BrowseUpdate_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim pack As Object
    Dim componentsInNewPack As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    packages.populate
    For Each pack In packages
        If pack.Name = "My Package" Then
            pack.Value("SecurityEnabled") = "Y"
            Exit For
        End If
    Next
    packages.savechanges
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub Command1_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim pack As Object
    Dim comp As Object
    Dim newUser As Object
    Dim newRole As Object
    Dim componentsInPack As Object
    Dim rolesInPack As Object
    Dim usersInRole As Object
    Dim rolesForComponent As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    packages.populate
    For Each pack In packages
        If pack.Name = "My Package" Then
            ' create a new role in the package
            Set rolesInPack = packages.GetCollection("RolesInPackage", pack.Key)
            Set newRole = rolesInPack.Add
            newRole.Value("Name") = "R1"
            rolesInPack.savechanges
            
            ' associate the role with a user
            Set usersInRole = rolesInPack.GetCollection("UsersInRole", newRole.Key)
            Set newUser = usersInRole.Add
            newUser.Value("User") = "administrator"
            usersInRole.savechanges
            
            'associate the role with a component
            Set componentsInPack = packages.GetCollection("ComponentsInPackage", pack.Key)
            componentsInPack.populate
            For Each comp In componentsInPack
                If comp.Name = "Bank.Account" Then
                    Set rolesForComponent = componentsInPack.GetCollection("RolesForPackageComponent", comp.Key)
                    Set util = rolesForComponent.getUtilInterface
                    util.associateRole (newRole.Key)
                    Exit For
                End If
            Next
            Exit For
        End If
    Next
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub CreatePackage_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim newPack As Object
    Dim componentsInNewPack As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    Set newPack = packages.Add
    Dim newPackID As String
    
    newPackID = newPack.Key
    newPack.Value("Name") = "My Package"
    packages.savechanges
    
    Set componentsInNewPack = packages.GetCollection("ComponentsInPackage", newPackID)
    Set util = componentsInNewPack.getUtilInterface
    util.InstallComponent "d:\viper96\bin\x86\rel\samples\packages\vbacct.dll", "", ""
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub Export_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    packages.populate
    For Each pack In packages
        If pack.Name = "My Package" Then
            Set util = packages.getUtilInterface
            util.ExportPackage pack.Key, "c:\test.pak", 0
            Exit For
        End If
    Next
           
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub InstallPackage_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    Set util = packages.getUtilInterface
    util.InstallPackage "c:\test.pak", "", 0
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)
End Sub

Private Sub PackDelete_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim pack As Object
    Dim componentsInPack As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    packages.populate
    For i = 0 To packages.Count
        Set pack = packages.Item(i)
        If pack.Name = "My Package" Then
            packages.Remove (i)
            packages.savechanges
            Exit For
        End If
    Next
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub PropInfo_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim propertyInfo As Object
    Dim property As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    Set propertyInfo = packages.GetCollection("PropertyInfo", "")
    propertyInfo.populate
    For Each property In propertyInfo
        Debug.Print property.Name
    Next
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub Related_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim relatedCollectionNames As Object
    Dim collName As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set packages = catalog.GetCollection("Packages")
    Set relatedCollectionNames = packages.GetCollection("RelatedCollectionInfo", "")
    relatedCollectionNames.populate
    For Each collName In relatedCollectionNames
        Debug.Print collName.Name
    Next
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub RemoteUpdate_Click()
    Dim catalog As Object
    Dim packages As Object
    Dim pack As Object
    Dim root As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set root = catalog.Connect("billdev9")
    Set packages = root.GetCollection("Packages", "")
    packages.populate
    For Each pack In packages
        If pack.Name = "My Package" Then
            pack.Value("SecurityEnabled") = "Y"
            Exit For
        End If
    Next
    packages.savechanges
            
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub RemoteComp_Click()
    Dim catalog As Object
    Dim remoteComps As Object
    Dim util As Object
    
    On Error GoTo failed
    Set catalog = CreateObject("MTSAdmin.CCatalog.1")
    Set remoteComps = catalog.GetCollection("RemoteComponents")
    Set util = remoteComps.getUtilInterface
    util.InstallRemoteComponentByName "billdev9", "New", "Bank.CreateTable"
           
    Exit Sub
    
failed:
    MsgBox "Failure code " + Str$(Err.Number)

End Sub

Private Sub RoleConfig_Click()

End Sub
