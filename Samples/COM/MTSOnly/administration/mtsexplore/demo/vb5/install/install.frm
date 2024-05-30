VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "comdlg32.ocx"
Begin VB.Form frmInstall 
   Caption         =   "SDK Component Install Sample"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog cdlg 
      Left            =   2040
      Top             =   2640
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      DialogTitle     =   "Select the Component you wish to install"
      FileName        =   "*.dll"
      Filter          =   "*.dll"
   End
   Begin VB.CommandButton Command2 
      Cancel          =   -1  'True
      Caption         =   "&Exit"
      Height          =   495
      Left            =   2760
      TabIndex        =   2
      Top             =   2640
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Run Demo"
      Default         =   -1  'True
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   2640
      Width           =   1455
   End
   Begin VB.Label Label1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   4335
   End
End
Attribute VB_Name = "frmInstall"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'/******************************************************************************\
'********************************************************************************
' Install Sample
'
'* This file is provided as part of the Microsoft Transaction Server
'* Software Development Kit
'*
'*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
'*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
'*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
'*PURPOSE.
'*
'* Copyright (C) 1997 Microsoft Corporation, All rights reserved
'********************************************************************************
'\******************************************************************************/

Private Sub Command1_Click()
' create the catalog object
Dim catalog As Object
Set catalog = CreateObject("MTSAdmin.Catalog.1")

' get the packages collection - you can only get the top level collections
' from the catalog object - the packages collection is returned without retrieving any
' data from the catalog data store so the in-memory collection will be empty upon return
' from the GetCollection method
Dim packages As Object
Set packages = catalog.GetCollection("Packages")

' first I want to delete any packages called "SDK Demo" to clean up from previous
' runs - populate the packages collection to read in all packages and search for
' packages named "SDK Demo" - note that I iterate thru the collection starting at the
' highest index so I can call Remove within the loop -
' Remove will release the object, remove it from the in-memory collection and move objects up so that
' object(n+1) becomes object(n) for all n greater then or equal to the index being removed
' the effect of Remove on the in memory collection is immediate so Item and Count methods
' called any time after the Remove will reflect the change - the Remove action is not
' applied to the catalog data store until you call SaveChanges on the collection
packages.Populate
Dim pack As Object
n = packages.Count
For i = n - 1 To 0 Step -1
    If packages.Item(i).Value("Name") = "SDK Demo" Then
        packages.Remove (i)
    End If
Next
' apply the changes to the data store
packages.SaveChanges

' now lets add a new package - Add will assign a package guid for us
Dim newPack As Object
Dim newPackID As Variant
Set newPack = packages.Add
' make note of the ID assigned
newPackID = newPack.Value("ID")
' override a couple properties
newPack.Value("Name") = "SDK Demo"
newPack.Value("SecurityEnabled") = "N"

' now we need to commit the changes so the new package is saved
' the return value is the number of objects changed/added/deleted
' this will be 0 if no changes were pending
n = packages.SaveChanges

' lets go get all the packages so we can see the one we just created
packages.Populate

n = packages.Count

' iterate over the packages until I find the one I just created and
' when I find it I'm going to get the components collection for that
' new package
Dim package As Object
Dim v As Variant
Dim components As Object
For Each package In packages
    v = package.Key
    If v = newPackID Then
        ' found it
        ' lets update some package properties while I'm here
        package.Value("SecurityEnabled") = "Y"
        ' get the components collection for this package - I need to pass in the key
        ' of the package object that I am interested in as parm 2
        Set components = packages.GetCollection("ComponentsInPackage", package.Key)
    End If
   
    ' print the names of all the packages
    Debug.Print package.Value("Name")
Next

' commit the updates I made above
packages.SaveChanges

' now lets install a component - I specify the name of the DLL as parm 1
' if there is an external TLB file or a P/S DLL I can specify them in parms 2 and 3 - otherwise
' pass in empty strings for parms 2 and 3 - there is no need to call SaveChanges after a componentInstall
Dim util As Object
Set util = components.GetUtilInterface
On Error GoTo installFailed
cdlg.filename = ""
cdlg.Filter = "Component (*.Dll)|*.Dll|All Files (*.*)|*.*"
cdlg.FilterIndex = 0
cdlg.ShowOpen

Dim thePath As String
thePath = cdlg.filename
util.InstallComponent thePath, "", ""
On Error GoTo 0

' go get the data in the components collection so I can see the
' component(s) I just installed - all components in the DLL will
' be installed
components.Populate

' iterate thru the components and change transaction attributes
' - use the item and count methods instead of the for each this time
' - find the Bank.CreatTable component so I can delete it by index - note that I
' must iterate thru the collection backwards since I may call Remove during the loop
' (see comments above about removing packages)
Dim component As Object
n = components.Count
For i = n - 1 To 0 Step -1
    Set component = components.Item(i)
    component.Value("Transaction") = "Required"
Next

' get new count and iterate through collection again - Bank.CreateTable will be gone but will
' not be deleted from the data store until I call SaveChanges
n = components.Count
For i = 0 To n - 1
    Set component = components.Item(i)
    Debug.Print component.Value("ProgID")
    Debug.Print component.Value("DLL")
Next

n = components.SaveChanges

MsgBox "SDK Demo package installed and configured."
Exit Sub

installFailed:
    MsgBox "Error code " + Str$(Err.Number) + " installing " & thePath + vbCrLf & _
    "Make sure that " & cdlg.filename _
    & vbCrLf & " is not already installed."


End Sub



Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Form_Load()
Dim sLabel1 As String

    sLabel1 = "Click the 'Run Demo' button below, " & vbCrLf & "then select the component to install." & vbCrLf & " the component will be installed into the SDK Demo Package"
    Label1.Caption = sLabel1
End Sub
