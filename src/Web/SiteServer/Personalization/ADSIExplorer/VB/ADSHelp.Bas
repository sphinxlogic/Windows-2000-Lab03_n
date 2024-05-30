Attribute VB_Name = "ADSHelp"
Option Explicit

Private Const ERR_CANT_OPEN_CONTAINER = 438
Dim m_ObjectIcons As New Collection
Dim m_ObjectContainment As New Collection

Const L_EXTERR_UNEXPECTED1 = "An unexpected error occurred."
Const L_EXTERR_UNEXPECTED2 = "Error Code: "
Const L_EXTERR_INVALID_VALUE1 = "The specified object name is not supported by the provider."
Const L_EXTERR_INVALID_VALUE2 = "Valid object names must not include the following characters: ,+=""\<>#;*"
Const L_EXTERR_OBJECT_NOT_FOUND1 = "The requested object could not be found."
Const L_EXTERR_OBJECT_NOT_FOUND2 = "The object name may be mispelled or the object might have been deleted."
Const L_EXTERR_CANT_COMPLETE1 = "Cannot complete the requested operation."
Const L_EXTERR_CANT_COMPLETE2 = "The object might be read-only."

'+------------------------------------------------------------------------------
' Function:     ADSRecursiveDelete
' Contents:     Delete's the specified object and it's children:
' Arguments:    sADsPath
' Returns:      Void
'-------------------------------------------------------------------------------
Sub ADSRecursiveDelete(sADsPath)
On Error Resume Next
    Dim oADS
    Dim oChildren
    Dim oChild
    Dim oParent

    '
    ' Get myself:
    '
    Set oADS = ADSGetObject(sADsPath)
    If Err.Number <> 0 Then Exit Sub

    '
    ' Delete all of my children:
    '
    Set oChildren = oADS.Children
    For Each oChild In oChildren
        '
        ' Delete it's children:
        '
        ADSRecursiveDelete (oChild.ADsPath)
        If Err.Number <> 0 Then Exit Sub
    Next

    '
    ' Get my parent:
    '
    Set oParent = ADSGetContainer(oADS.Parent)
    If Err.Number <> 0 Then Exit Sub

    '
    ' Delete me:
    '
    oParent.Delete oADS.Name, oADS.Class
    If Err.Number <> 0 Then Exit Sub
End Sub
'+------------------------------------------------------------------------------
' Function:     GetNameFromDN
' Contents:     Returns the name of the object based on its DN
' Arguments:    sDN
' Returns:      Name of object
'-------------------------------------------------------------------------------
Private Function GetNameFromDN(ByVal sDN As String) As String
    Dim iEqualsPos As Integer
    Dim iPos As Integer
    Dim sName As String
    Dim sCN

    '
    ' Look for the "ou=members" part:
    '
    iPos = InStr(1, sDN, ",ou=members", vbTextCompare)
    If iPos > 0 Then
        sDN = Left(sDN, iPos - 1)
    End If
    
    '
    ' Stip off the rest of the DN:
    '
    For iPos = Len(sDN) To 1 Step -1
        If Mid(sDN, iPos, 1) = "," Then
            sCN = Mid(sDN, iPos + 1)
            sDN = Left(sDN, iPos - 1)
            iEqualsPos = InStr(sCN, "=")
            If iEqualsPos > 0 Then sCN = Mid(sCN, iEqualsPos + 1)
        
            sName = sName & sCN & "\"
        End If
    Next
    iEqualsPos = InStr(sDN, "=")
    If iEqualsPos > 0 Then sDN = Mid(sDN, iEqualsPos + 1)
    sName = sName & sDN
    
    GetNameFromDN = sName
End Function

Public Function ADSDeleteObject(ByVal sADsPath As String, ByVal bRecursive As Boolean)
On Error Resume Next
    Dim oADS
    Dim oParent
    Dim bResponse
    
    Set oADS = ADSGetObject(sADsPath)
    If Err.Number <> 0 Then
        HandleError "Unable to open """ & sADsPath & """", Err.Number
        bResponse = False
    Else
        Set oParent = ADSGetContainer(oADS.Parent)
        If Err.Number <> 0 Then
            HandleError "Unable to open """ & oADS.Parent & """", Err.Number
            bResponse = False
        Else
            If Left(sADsPath, 7) = "LDAP://" Then
                If bRecursive = True Then
                    ADSRecursiveDelete sADsPath
                Else
                    oParent.Delete oADS.Name, oADS.Class
                End If
                If Err.Number <> 0 Then
                    HandleError "Unable to delete """ & oADS.Name & """", Err.Number
                    bResponse = False
                Else
                    bResponse = True
                End If
            Else
                oParent.Delete oADS.Class, oADS.Name
                If Err.Number <> 0 Then
                    HandleError "Unable to open """ & oADS.Parent & """", Err.Number
                    bResponse = False
                Else
                    bResponse = True
                End If
            End If
        End If
    End If
    
    ADSDeleteObject = bResponse
End Function

Public Function ADSGetObject(ByVal sADsPath)
Dim oObject

    '
    ' Check to see if we should be using FastADS:
    '
    If Left(sADsPath, 7) = "LDAP://" Then
        '
        ' Use FastADS:
        '
        Set oObject = New CADS
        oObject.GetInfo sADsPath
    Else
        '
        ' Use ADSI:
        '
        Set oObject = GetObject(sADsPath)
    End If
    
    Set ADSGetObject = oObject
End Function
Public Function ADSGetClass(ByVal sADsPath)
Dim oObject

    '
    ' Check to see if we should be using FastADS:
    '
    If Left(sADsPath, 7) = "LDAP://" Then
        '
        ' Use FastADS:
        '
        Set oObject = New CADSClass
        oObject.GetInfo sADsPath
    Else
        '
        ' Use ADSI:
        '
        Set oObject = GetObject(sADsPath)
    End If
    
    Set ADSGetClass = oObject
End Function


Public Function ADSGetContainer(ByVal sADsPath)
Dim oObject

    '
    ' Check to see if we should be using FastADS:
    '
    If Left(sADsPath, 7) = "LDAP://" Then
        '
        ' Use FastADS:
        '
        Set oObject = New CADSContainer
        oObject.GetInfo sADsPath, "objectClass=*"
    Else
        '
        ' Use ADSI:
        '
        Set oObject = GetObject(sADsPath)
    End If
    
    Set ADSGetContainer = oObject
End Function



Public Sub PopulateNewMenu(ByVal sADsPath As String, This As Form)
On Error Resume Next
Dim iCount
Dim oADS As New CADS
Dim oClass As CADS
Dim sClass As String
Static oSchema As New CADSContainer
Dim asPossibleSuperiors
Dim sSuperior
Dim lMenuItem As Integer

    '
    ' Make sure the menu bar is there to edit!
    '
    If IsObject(This.mnuEditSearch) = False Then Exit Sub
    If Err.Number <> 0 Then
        Err.Clear
        Exit Sub
    End If
    
    If Left(sADsPath, 7) = "LDAP://" Then
        '
        ' Enable the "Find" menu:
        '
        This.mnuEditSearch.Enabled = True
        
        '
        ' Figure out this object's class:
        '
        oADS.GetInfo sADsPath
        If Err.Number <> 0 Then
            HandleError "Unable to open """ & sADsPath & """", Err.Number
        Else
            sClass = LCase(oADS.Class)
            
            '
            ' Now, find all of the schema elements:
            '
            oSchema.GetInfo PartialPath(sADsPath, 4) & "/ou=admin/cn=schema", "!"
            If Err.Number <> 0 Then
                HandleError "Unable to open """ & PartialPath(sADsPath, 4) & "/ou=admin/cn=schema""", Err.Number
            Else
                For Each oClass In oSchema
                    If oClass.GetEx("objectClass")(0) = "classSchema" Then
                        asPossibleSuperiors = oClass.GetEx("possSuperiors")
                        For Each sSuperior In asPossibleSuperiors
                            If LCase(sSuperior) = sClass Then
                                This.mnuNewDynamic(lMenuItem).Caption = oClass.GetEx("cn")(0)
                                This.mnuNewDynamic(lMenuItem).Tag = oClass.GetEx("cn")(0)
                                This.mnuPopupNewDynamic(lMenuItem).Caption = oClass.GetEx("cn")(0)
                                This.mnuPopupNewDynamic(lMenuItem).Tag = oClass.GetEx("cn")(0)
                                This.mnuNewDynamic(lMenuItem).Enabled = False
                                This.mnuPopupNewDynamic(lMenuItem).Enabled = False
                                lMenuItem = lMenuItem + 1
                                Exit For
                            End If
                        Next
                        If lMenuItem > 24 Then Exit For
                    End If
                Next
            End If
        End If
    Else
        '
        ' Disable the "Find" menu:
        '
        This.mnuEditSearch.Enabled = True
    End If
    
    '
    ' Disable the dynamic new menu if they aren't used:
    '
    For iCount = lMenuItem To 24
        This.mnuNewDynamic(iCount).Visible = False
        This.mnuPopupNewDynamic(iCount).Visible = False
    Next iCount

    If lMenuItem > 0 And lMenuItem > 24 Then
        This.mnuNewDynamic(99).Visible = True
        This.mnuPopupNewDynamic(99).Visible = True
        
        This.mnuNewOther.Visible = True
        This.mnuPopUpNewOther.Visible = True
        This.mnuNewOther.Enabled = False
        This.mnuPopUpNewOther.Enabled = False
    Else
        If lMenuItem = 0 Then
            This.mnuNewDynamic(99).Visible = False
            This.mnuPopupNewDynamic(99).Visible = False
        End If
        
        This.mnuNewOther.Enabled = False
        This.mnuPopUpNewOther.Enabled = False
    End If
End Sub

Public Sub FillContainer(ByVal sADsPath, This As Form) 'This As fExplorer)
Dim oIADs ' As IADsContainer
Dim oIADsObj ' As IADs
Dim oIADsChild ' As IADs
Dim sTypeName As String
Dim sDisplayName As String
Dim sIcon As String
Dim bContainer As Boolean
Dim oListItem As ListItem
Dim sRealPath As String

    This.lvContainer.ListItems.Clear
    
    On Error Resume Next
    Set oIADs = ADSGetContainer(sADsPath)
    If Err.Number <> 0 Then
        HandleError "Unable to open """ & sADsPath & """", Err.Number
        Err.Raise 75
        Exit Sub
    End If
    
    '
    ' Get the path if it is a default container:
    '
    If InStr(InStr(sADsPath, "//") + 2, sADsPath, "/") = 0 Then
        Set oIADsObj = ADSGetObject(sADsPath)
        sRealPath = oIADsObj.ADsPath
    Else
        sRealPath = sADsPath
    End If
    
    '
    ' Add each child:
    '
    On Error Resume Next
    For Each oIADsChild In oIADs
        If Err.Number <> 0 Then
            If Err.Number <> ERR_CANT_OPEN_CONTAINER Then MsgBox Err.Description
        Else
            On Error GoTo 0
            '
            ' Get the configuration for this object:
            '
            GetObjectConfig oIADsChild, sDisplayName, sTypeName, sIcon, bContainer
            
            '
            ' And add it to the list view
            '
            Set oListItem = This.lvContainer.ListItems.Add(, , sDisplayName, sIcon, sIcon)
            oListItem.SubItems(1) = sTypeName
            
            oListItem.Tag = CStr(Abs(CInt(bContainer))) & oIADsChild.ADsPath
        End If
    Next

    '
    ' Populate the new menu:
    '
    PopulateNewMenu sRealPath, This

    '
    ' Set our title:
    '
    This.Caption = sRealPath
End Sub


Public Sub FillSearchContainer(ByVal sADsPath, ByVal sFilter, This As Form) 'This As fExplorer)
Dim oIADs As New CADSContainer
Dim oIADsChild As CADS
Dim oIADsObj
Dim sTypeName As String
Dim sDisplayName As String
Dim sIcon As String
Dim bContainer As Boolean
Dim oListItem As ListItem
Dim sRealPath As String

    This.lvContainer.ListItems.Clear
    
    On Error Resume Next
    oIADs.GetInfo sADsPath, sFilter
    If Err.Number <> 0 Then
        HandleError "Unable to open """ & sADsPath & """", Err.Number
        Err.Raise 75
        Exit Sub
    End If
    
    '
    ' Get the path if it is a default container:
    '
    If InStr(InStr(sADsPath, "//") + 2, sADsPath, "/") = 0 Then
        Set oIADsObj = ADSGetObject(sADsPath)
        sRealPath = oIADsObj.ADsPath
    Else
        sRealPath = sADsPath
    End If
    
    '
    ' Add each child:
    '
    On Error Resume Next
    For Each oIADsChild In oIADs
        If Err.Number <> 0 Then
            If Err.Number <> ERR_CANT_OPEN_CONTAINER Then MsgBox Err.Description
        Else
            On Error GoTo 0
            '
            ' Get the configuration for this object:
            '
            GetObjectConfig oIADsChild, sDisplayName, sTypeName, sIcon, bContainer
            
            '
            ' And add it to the list view
            '
            Set oListItem = This.lvContainer.ListItems.Add(, , sDisplayName, sIcon, sIcon)
            oListItem.SubItems(1) = sTypeName
            
            oListItem.Tag = CStr(Abs(CInt(bContainer))) & oIADsChild.ADsPath
        End If
    Next

    '
    ' Populate the new menu:
    '
    PopulateNewMenu sRealPath, This

    '
    ' Set our title:
    '
    This.Caption = sRealPath
End Sub



Public Sub FillProperties(ByVal sADsPath, oProperties As Form)
Dim oIADs ' As IADs
Dim sDisplayName As String
Dim sTypeName As String
Dim sIconKey As String
Dim bContainer As Boolean
Dim asMustHaves
Dim asMayHaves
Dim sPropertyName
Dim sPropertyValues
Dim sPropertyValue
Dim oItem As ListItem

    Set oIADs = ADSGetObject(sADsPath)
    
    '
    ' Get the object's configuration:
    '
    GetObjectConfigEx oIADs, sDisplayName, sTypeName, _
                      sIconKey, bContainer, asMustHaves, _
                      asMayHaves

    '
    ' Fill in the default properties:
    '
    oProperties.lName.Caption = sDisplayName
    If Abs(bContainer) = False Then
        oProperties.lClass.Caption = "(" & sTypeName & ")"
        oProperties.tsTabs.Tab = 0
    Else
        oProperties.lClass.Caption = "(" & sTypeName & ", container)"
        FillContainer sADsPath, oProperties
        oProperties.tsTabs.Tab = 1
    End If
    
    On Error Resume Next
    For Each sPropertyName In asMustHaves
        Err.Clear
        Set oItem = oProperties.lvProperties.ListItems.Add(, , GetDisplayName(PartialPath(sADsPath, 3) & "/Schema/" & sPropertyName, sPropertyName))
        
        sPropertyValues = oIADs.GetEx(sPropertyName)
        If Err.Number = 0 Then
            For Each sPropertyValue In sPropertyValues
                oItem.SubItems(1) = oItem.SubItems(1) & sPropertyValue & ","
            Next
        End If
        sPropertyValues = ""
    Next
    
    For Each sPropertyName In asMayHaves
        Err.Clear
        sPropertyValues = oIADs.GetEx(sPropertyName)
        If Err.Number = 0 Then
            Set oItem = oProperties.lvProperties.ListItems.Add(, , GetDisplayName(PartialPath(sADsPath, 3) & "/Schema/" & sPropertyName, sPropertyName))
        
            For Each sPropertyValue In sPropertyValues
                oItem.SubItems(1) = oItem.SubItems(1) & sPropertyValue & ", "
            Next
        End If
        sPropertyValues = ""
    Next
    
    oProperties.lvProperties.SelectedItem = oProperties.lvProperties.ListItems(1)
    
    oProperties.Refresh
    DoEvents
    
    Err.Clear
End Sub


Public Function GetDisplayName(ByVal sAttributePath As String, ByVal sAttributeName As String) As String
Dim sDisplayName As String
Dim oClass

    If Left(sAttributePath, 7) = "LDAP://" Then
        Set oClass = ADSGetClass(sAttributePath)
        sDisplayName = oClass.GetEx("displayName")(0)
        If Err.Number <> 0 Then
            sDisplayName = sAttributeName
            Err.Clear
        End If
    Else
        sDisplayName = sAttributeName
    End If
    
    GetDisplayName = sDisplayName
End Function

Private Sub GetObjectConfig(oIADs, sDisplayName, sTypeName, sIconKey, bContainer)
On Error GoTo 0
Dim oClass
Dim sIconPath As String

    '
    ' Attempt to get the display name:
    '
    sDisplayName = ""
    sTypeName = ""
    
    Select Case LCase(Left(oIADs.ADsPath, InStr(oIADs.ADsPath, ":")))
    Case "ldap:"
        sDisplayName = Mid(oIADs.Name, InStr(oIADs.Name, "=") + 1)
        sTypeName = oIADs.Class
        
        '
        ' Special case the LDAP objects for members:
        '
        If LCase(sTypeName) = "memberof" Then
            sDisplayName = GetNameFromDN(oIADs.GetEx("memberObject")(0))
        ElseIf LCase(sTypeName) = "groupmemberof" Then
            sDisplayName = GetNameFromDN(oIADs.GetEx("groupObject")(0))
        End If
    Case "iis:"
        bContainer = True
        sDisplayName = oIADs.Name
        sTypeName = oIADs.Class
    Case Else
        sDisplayName = oIADs.Name
        sTypeName = oIADs.Class
    End Select
    
    '
    ' Attempt to look up the icons in our association collection:
    '
    sIconKey = ""
    sIconPath = LCase(Left(oIADs.ADsPath, InStr(oIADs.ADsPath, ":"))) & LCase(oIADs.Class)
    On Error Resume Next
    sIconKey = m_ObjectIcons(sIconPath)
    bContainer = m_ObjectContainment(sIconPath)
    On Error GoTo 0
    
    '
    ' No icon was specified, so try to figure it out:
    '
    If sIconKey = "" Then
        On Error Resume Next
        Set oClass = ADSGetClass(oIADs.Schema)
        If Err.Number <> 0 Then
            '
            ' We couldn't get the schema, so assume it
            ' is a container:
            '
            sIconKey = "Container"
            bContainer = True
            Err.Clear
        Else
            '
            ' We got the schema, figure out what it is:
            '
            If oClass.Container <> False Then
                '
                ' A Container
                '
                sIconKey = "Container"
                bContainer = True
            Else
                '
                ' A node:
                '
                sIconKey = "Node"
            End If
        End If
    End If
End Sub


Private Sub GetObjectConfigEx(oIADs, sDisplayName As String, sTypeName As String, _
                              sIconKey As String, bContainer As Boolean, _
                              asMustHaves, asMayHaves)
On Error GoTo 0
Dim oClass
Dim sIconPath As String

    '
    ' Attempt to get the display name:
    '
    sDisplayName = ""
    sTypeName = ""
    
    Select Case LCase(Left(oIADs.ADsPath, InStr(oIADs.ADsPath, ":")))
    Case "ldap:"
        sDisplayName = Mid(oIADs.Name, InStr(oIADs.Name, "=") + 1)
        sTypeName = oIADs.Class
    
        '
        ' Special case the LDAP objects for members:
        '
        If LCase(sTypeName) = "memberof" Then
            sDisplayName = GetNameFromDN(oIADs.GetEx("memberObject")(0))
        ElseIf LCase(sTypeName) = "groupmemberof" Then
            sDisplayName = GetNameFromDN(oIADs.GetEx("groupObject")(0))
        End If
    Case Else
        sDisplayName = oIADs.Name
        sTypeName = oIADs.Class
    End Select
    
    '
    ' Attempt to look up the icons in our association collection:
    '
    sIconKey = ""
    sIconPath = LCase(Left(oIADs.ADsPath, InStr(oIADs.ADsPath, ":"))) & LCase(oIADs.Class)
    On Error Resume Next
    sIconKey = m_ObjectIcons(sIconPath)
    bContainer = m_ObjectContainment(sIconPath)
    On Error GoTo 0
    
    On Error Resume Next
    Set oClass = ADSGetClass(oIADs.Schema)
    If Err.Number <> 0 Then
        '
        ' We couldn't get the schema, so assume it
        ' is a container:
        '
        sIconKey = "Container"
        bContainer = True
        Err.Clear
    Else
        '
        ' We got the schema, figure out what it is:
        '
        If oClass.Container <> False Then
            '
            ' A Container
            '
            sIconKey = "Container"
            bContainer = True
        Else
            '
            ' A node:
            '
            sIconKey = "Node"
            bContainer = False
        End If
        asMustHaves = oClass.MandatoryProperties
        asMayHaves = oClass.OptionalProperties
    End If
End Sub



Public Sub HandleError(ByVal sMessage As String, ByVal lErrorNumber As Long)
    Dim sNewMessage

    sNewMessage = sMessage & Chr(10) & Chr(10)
    
    Select Case lErrorNumber
    '
    ' Object Not Found:
    '
    Case 5
        sNewMessage = sNewMessage & L_EXTERR_OBJECT_NOT_FOUND1 & Chr(10) & _
                      L_EXTERR_OBJECT_NOT_FOUND2
    Case -2147024894
        sNewMessage = sNewMessage & L_EXTERR_OBJECT_NOT_FOUND1 & Chr(10) & _
                      L_EXTERR_OBJECT_NOT_FOUND2
    Case -2147024786
        sNewMessage = sNewMessage & L_EXTERR_OBJECT_NOT_FOUND1 & Chr(10) & _
                      L_EXTERR_OBJECT_NOT_FOUND2

    '
    ' Can't complete operation:
    '
    Case -2147023893
        sNewMessage = sNewMessage & L_EXTERR_CANT_COMPLETE1 & Chr(10) & _
                      L_EXTERR_CANT_COMPLETE2

    '
    ' Invalid RDN/Pathname:
    '
    Case 52
        sNewMessage = sNewMessage & L_EXTERR_INVALID_VALUE1 & Chr(10) & _
                      L_EXTERR_INVALID_VALUE2
    '
    ' Unknown:
    '
    Case Else
        sNewMessage = sNewMessage & L_EXTERR_UNEXPECTED1 & Chr(10) & _
                      L_EXTERR_UNEXPECTED2 & "(0x" & Hex(lErrorNumber) & ")"
    End Select

    '
    ' Display the error:
    '
    MsgBox sNewMessage, vbCritical + vbOKOnly, "Unhandled Error"
End Sub

Public Sub Initialize()
    '
    ' Add the icon associations for LDAP: providers:
    '
    m_ObjectIcons.Add "Admin", "ldap:admin"
    m_ObjectContainment.Add True, "ldap:admin"
    m_ObjectIcons.Add "User", "ldap:member"
    m_ObjectContainment.Add False, "ldap:member"
    m_ObjectIcons.Add "User", "ldap:memberof"
    m_ObjectContainment.Add False, "ldap:memberof"
    m_ObjectIcons.Add "Group", "ldap:mgroup"
    m_ObjectContainment.Add True, "ldap:mgroup"
    m_ObjectIcons.Add "Group", "ldap:groupmemberof"
    m_ObjectContainment.Add False, "ldap:groupmemberof"
    
    '
    ' Add the icon associations for WinNT: providers:
    '
    m_ObjectIcons.Add "User", "winnt:user"
    m_ObjectContainment.Add False, "winnt:user"
    m_ObjectIcons.Add "Group", "winnt:group"
    m_ObjectContainment.Add False, "winnt:group"
    m_ObjectIcons.Add "Service", "winnt:service"
    m_ObjectContainment.Add True, "winnt:service"
    m_ObjectIcons.Add "Container", "winnt:fileshare"
    m_ObjectContainment.Add False, "winnt:fileshare"
    m_ObjectIcons.Add "Computer", "winnt:computer"
    m_ObjectContainment.Add True, "winnt:computer"
End Sub


Function PartialPath(ByVal sADsPath As String, iSlashes As Integer)
Dim iCount
Dim iPos
    
    iPos = 1
    For iCount = 1 To iSlashes
        iPos = InStr(iPos + 1, sADsPath, "/")
    Next iCount
    
    If iPos > 0 Then
        PartialPath = Left(sADsPath, iPos - 1)
    Else
        PartialPath = sADsPath
    End If
End Function


