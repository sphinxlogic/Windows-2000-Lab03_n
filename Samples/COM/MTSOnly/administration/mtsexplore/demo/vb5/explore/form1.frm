VERSION 5.00
Begin VB.Form Explorer 
   Caption         =   "MTS Admin SDK Sample"
   ClientHeight    =   6360
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7950
   LinkTopic       =   "Form1"
   ScaleHeight     =   6360
   ScaleWidth      =   7950
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Connect 
      Caption         =   "Connect..."
      Height          =   375
      Left            =   5520
      TabIndex        =   18
      Top             =   240
      Width           =   1575
   End
   Begin VB.CommandButton ExportBtn 
      Caption         =   "Export..."
      Height          =   375
      Left            =   1440
      TabIndex        =   17
      Top             =   2640
      Width           =   1455
   End
   Begin VB.CommandButton Install 
      Caption         =   "Install..."
      Height          =   375
      Left            =   120
      TabIndex        =   16
      Top             =   2640
      Width           =   1095
   End
   Begin VB.ListBox CollList 
      Height          =   1230
      Left            =   120
      TabIndex        =   10
      Top             =   3840
      Width           =   2295
   End
   Begin VB.ListBox ObjList 
      Height          =   2985
      Left            =   3480
      TabIndex        =   9
      Top             =   1320
      Width           =   2055
   End
   Begin VB.CommandButton Back 
      Caption         =   "Back"
      Height          =   495
      Left            =   120
      TabIndex        =   8
      Top             =   5160
      Width           =   855
   End
   Begin VB.ListBox PropList 
      Height          =   2985
      Left            =   5880
      TabIndex        =   7
      Top             =   1320
      Width           =   1935
   End
   Begin VB.TextBox Value 
      Height          =   375
      Left            =   3480
      TabIndex        =   6
      Text            =   "Text1"
      Top             =   5160
      Width           =   3495
   End
   Begin VB.CommandButton SetBtn 
      Caption         =   "Set"
      Height          =   375
      Left            =   7080
      TabIndex        =   5
      Top             =   5160
      Width           =   735
   End
   Begin VB.CommandButton SaveBtn 
      Caption         =   "SaveChanges"
      Height          =   495
      Left            =   1440
      TabIndex        =   4
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton AddBtn 
      Caption         =   "Add"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   2160
      Width           =   1095
   End
   Begin VB.CommandButton RemoveBtn 
      Caption         =   "Remove"
      Height          =   375
      Left            =   1440
      TabIndex        =   2
      Top             =   2160
      Width           =   1455
   End
   Begin VB.CommandButton Populate 
      Caption         =   "Populate"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   1560
      Width           =   1095
   End
   Begin VB.CommandButton GoToBtn 
      Caption         =   "GetCollection"
      Height          =   495
      Left            =   1200
      TabIndex        =   0
      Top             =   5160
      Width           =   1695
   End
   Begin VB.Frame Frame1 
      Caption         =   "Collection"
      Height          =   4935
      Left            =   0
      TabIndex        =   19
      Top             =   840
      Width           =   3015
      Begin VB.CommandButton Associate 
         Caption         =   "Associate Role..."
         Height          =   375
         Left            =   1440
         TabIndex        =   28
         Top             =   2280
         Width           =   1455
      End
      Begin VB.Label Label7 
         Caption         =   "Related collections:"
         Height          =   255
         Left            =   120
         TabIndex        =   22
         Top             =   2760
         Width           =   2295
      End
      Begin VB.Label CurCollName 
         BorderStyle     =   1  'Fixed Single
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   20
         Top             =   360
         Width           =   2775
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Objects"
      Height          =   4935
      Left            =   3240
      TabIndex        =   21
      Top             =   840
      Width           =   4695
      Begin VB.Label Label9 
         Caption         =   "Property value:"
         Height          =   255
         Left            =   240
         TabIndex        =   24
         Top             =   3960
         Width           =   2295
      End
      Begin VB.Label Label8 
         Caption         =   "Propeties:"
         Height          =   255
         Left            =   2640
         TabIndex        =   23
         Top             =   240
         Width           =   1335
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Catalog"
      Height          =   735
      Left            =   0
      TabIndex        =   25
      Top             =   0
      Width           =   7935
      Begin VB.Label Label6 
         Caption         =   "Computer:"
         Height          =   255
         Left            =   240
         TabIndex        =   27
         Top             =   360
         Width           =   975
      End
      Begin VB.Label ServerName 
         BorderStyle     =   1  'Fixed Single
         Height          =   255
         Left            =   1200
         TabIndex        =   26
         Top             =   360
         Width           =   3975
      End
   End
   Begin VB.Label Label2 
      Caption         =   "Related collections:"
      Height          =   255
      Left            =   120
      TabIndex        =   15
      Top             =   3360
      Width           =   1935
   End
   Begin VB.Label Label3 
      Caption         =   "Objects:"
      Height          =   255
      Left            =   3480
      TabIndex        =   14
      Top             =   960
      Width           =   1095
   End
   Begin VB.Label Label4 
      Caption         =   "Properties"
      Height          =   255
      Left            =   6000
      TabIndex        =   13
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label Label5 
      Caption         =   "Property Value:"
      Height          =   255
      Left            =   3480
      TabIndex        =   12
      Top             =   4920
      Width           =   1095
   End
   Begin VB.Label status 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   0
      TabIndex        =   11
      Top             =   5880
      Width           =   7935
   End
End
Attribute VB_Name = "Explorer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'/******************************************************************************\
'********************************************************************************
' Explore Sample
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

Public catalog As Object
Public currentColl As Object
Public related As Object
Public propNames As Object
Private stack(10) As Object
Private stackTop As Integer
Public Server As String


Private Sub AddBtn_Click()
    currentColl.Add
    displayObjects currentColl
End Sub

Private Sub Associate_Click()
    AssociateRole.Show 1, Me

End Sub

Private Sub CollList_Click()
    If CollList.ListIndex = -1 Then
        GoToBtn.Enabled = False
    Else
        GoToBtn.Enabled = True
    End If
        
End Sub

Private Sub Connect_Click()
    ServerDlg.Show 1, Me
   
End Sub

Private Sub ExportBtn_Click()
    PackageExport.Show 1, Me

End Sub

Private Sub GoToBtn_Click()
    status.Caption = ""
    nColl = CollList.ListIndex
    nObj = ObjList.ListIndex
    If nColl > -1 Then
    
        MousePointer = 11

        ' if navigating from the root then apply the
        ' current server to the catalog and re-get the
        ' root
        If currentColl.Name = "Root" Then
            Set currentColl = catalog.GetCollection("Root")
        End If
        Dim key As String
        key = ""
        If nObj > -1 Then
            key = currentColl.Item(nObj).key
        End If
        Dim coll As Object
        Set coll = currentColl.GetCollection(CollList.List(nColl), (key))
        push currentColl
        Set currentColl = coll
        navigateTo currentColl
        MousePointer = 0
        
    End If
   
            
End Sub

Private Sub Form_Load()
    Set catalog = CreateObject("MTSAdmin.Catalog.1")
    stackTop = -1
    
    status.Caption = ""
    Set currentColl = catalog.GetCollection("Root")
    push currentColl
    navigateTo currentColl
    ServerName.Caption = "local"
    
End Sub

Public Sub navigateTo(coll As Object)

    MousePointer = 11
    CurCollName.Caption = coll.Name
    ' populate related collections list
    CollList.Clear
    PropList.Clear
    GoToBtn.Enabled = False
    
    Set related = coll.GetCollection("RelatedCollectionInfo", "")
    related.Populate
    Dim relColl As Object

    For Each relColl In related
        CollList.AddItem (relColl.Name)
    Next


    ' populate property names
    Set propNames = coll.GetCollection("PropertyInfo", "")
    Dim propName As Object
    propNames.Populate
    For Each propName In propNames
       PropList.AddItem (propName.Name)
    Next
    
    ' populate objects
    On Error GoTo err
    coll.Populate
    On Error GoTo 0
    displayObjects coll
    
    MousePointer = 0
    AddBtn.Enabled = coll.AddEnabled
    RemoveBtn.Enabled = coll.RemoveEnabled
    SaveBtn.Enabled = False
    If coll.Name = "Root" Then
        Back.Enabled = False
    Else
        Back.Enabled = True
    End If
    If coll.Name = "Packages" Or coll.Name = "ComponentsInPackage" Or coll.Name = "RemoteComponents" Then
        Install.Enabled = True
    Else
        Install.Enabled = False
    End If
    If coll.Name = "Packages" Then
        ExportBtn.Enabled = True
    Else
        ExportBtn.Enabled = False
    End If
    If coll.Name = "RolesForPackageComponent" Or coll.Name = "RolesForPackageComponentInterface" Then
        Associate.Enabled = True
    Else
        Associate.Enabled = False
    End If
    Exit Sub
err:
    MsgBox "Collection populate failed with error code " + mapError(err.Number)
    Resume Next

End Sub

Private Sub displayObjects(coll As Object)
    Dim obj As Object
    ObjList.Clear
    For Each obj In coll
        ObjList.AddItem (obj.Name)
    Next
    Value.Text = ""

    ' display property value if possible
    If PropList.ListCount > 0 Then
        PropList.Selected(0) = True
    End If
    If ObjList.ListCount > 0 Then
        ObjList.Selected(0) = True
        PropList_Click
    End If

End Sub

Private Sub Install_Click()
    If currentColl.Name = "Packages" Then
        PackInstall.Show 1, Me
    End If
    If currentColl.Name = "ComponentsInPackage" Then
        MainCompInstall.Show 1, Me
    End If
    If currentColl.Name = "RemoteComponents" Then
        RemoteComp.Show 1, Me
    End If
        
End Sub



Private Sub ObjList_Click()
    status.Caption = ""
    DisplayValue
End Sub

Private Sub Populate_Click()
    MousePointer = 11
    status.Caption = ""
    navigateTo currentColl
    MousePointer = 0
End Sub

Private Sub DisplayValue()
    ' display property value and disable control if readOnly
    Dim val As Variant
    nObj = ObjList.ListIndex
    If nObj > -1 Then
        nProp = PropList.ListIndex
        If nProp = -1 Then
            Value.Text = ""
            Value.Locked = True
        Else
            ' check for write-only property
            If currentColl.Item(nObj).IsPropertyWriteOnly(PropList.List(nProp)) Then
                Value.Text = ""
            Else
                s = PropList.List(nProp)
                ' get property value
                val = currentColl.Item(nObj).Value(PropList.List(nProp))
                ' if this is an error code then map to a string form
                If currentColl.Name = "ErrorInfo" And nProp = 1 Then
                    Value.Text = Explorer.mapError((val))
                Else
                    Value.Text = val
                End If
            End If
    
            If currentColl.Item(nObj).IsPropertyReadOnly(PropList.List(nProp)) Then
                Value.Locked = True
            Else
                Value.Locked = False
            End If
        End If
        SetBtn.Enabled = Not Value.Locked
            
    End If

End Sub

Private Sub PropList_Click()
    status.Caption = ""
    DisplayValue
End Sub

Private Sub RemoveBtn_Click()
    nObj = ObjList.ListIndex
    If nObj > -1 Then
        currentColl.Remove nObj
        displayObjects currentColl
        SaveBtn.Enabled = True
        
    End If

End Sub

Private Sub Back_Click()
    status.Caption = ""
    MousePointer = 11
    Set currentColl = pop
    
    navigateTo currentColl
    If currentColl.Name = "Root" Then
        Connect.Enabled = True
    End If
    MousePointer = 0
End Sub

Private Sub SaveBtn_Click()
    status.Caption = ""
    MousePointer = 11
    On Error GoTo err
    currentColl.SaveChanges
    MousePointer = 0
    Exit Sub
err:
    MsgBox "Save changes failed with error code " + mapError(err.Number)
    MousePointer = 0
End Sub

Private Sub SetBtn_Click()
    status.Caption = ""
    On Error GoTo errorHandler
    nObj = ObjList.ListIndex
    If nObj > -1 Then
        nProp = PropList.ListIndex
        If nProp > -1 Then
            currentColl.Item(nObj).Value(PropList.List(nProp)) = Value.Text
            SaveBtn.Enabled = True
        End If
    End If
    Exit Sub
errorHandler:
    Beep
    status.Caption = "Invalid value"
    ' reset the value box contents
    DisplayValue
    

End Sub


Private Sub push(obj As Object)
    ' live on the edge - no overflow check
    stackTop = stackTop + 1
    Set stack(stackTop) = obj
End Sub

Function pop() As Object
    Set pop = Nothing
    If stackTop < 0 Then Return
    Set pop = stack(stackTop)
    Set stack(stackTop) = Nothing
    stackTop = stackTop - 1
End Function

Public Function mapError(errorCode As Long) As String
    Select Case errorCode
    
    Case mtsErrObjectErrors
        mapError = "mtsErrObjectErrors - see ErrorInfo collection"
        
    Case mtsErrObjectErrors
        mapError = "mtsErrObjectErrors"

    Case mtsErrObjectInvalid
        mapError = "mtsErrObjectInvalid"

    Case mtsErrKeyMissing
        mapError = "mtsErrKeyMissing"

    Case mtsErrAlreadyInstalled
        mapError = "mtsErrAlreadyInstalled"

    Case mtsErrCoReqCompInstalled
        mapError = "mtsErrCoReqCompInstalled"

    Case mtsErrBadPath
        mapError = "mtsErrBadPath"

    Case mtsErrPackageExists
        mapError = "mtsErrPackageExists"

    Case mtsErrRemoteInterface
        mapError = "mtsErrRemoteInterface"

    Case mtsErrCantCopyFile
        mapError = "mtsErrCantCopyFile"

    Case mtsErrNoTypeLib
        mapError = "mtsErrNoTypeLib"
    
    Case mtsErrNoUser
        mapError = "mtsErrNoUser"

    Case mtsErrInvalidUserids
        mapError = "mtsErrInvalidUserids"

    Case mtsErrUserPasswdNotValid
        mapError = "mtsErrUserPasswdNotValid"
    
    Case mtsErrNoServerShare
        mapError = "mtsErrNoServerShare"

    Case mtsErrPackDirNotFound
        mapError = "mtsErrPackDirNotFound"
        
    Case mtsErrCompFileNotInstallable
        mapError = "mtsCompFileNotInstallable"
        
    Case mtsErrCompFileNoRegistrar
        mapError = "mtsErrCompFileNoRegistrar"
        
        
    Case Else
        mapError = errorCode
    End Select
  
End Function
