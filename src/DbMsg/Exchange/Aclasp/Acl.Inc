<%
'<!--ACL Sample Application-->
'<!--ACL.inc : ACL routines -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' ACL.inc contains constants, properties, & routines for handling the ACL object.
'
' Role & Rights Constants
'
Const gstrACL_MEMBER_DEFAULT = "Default"
Const gstrACL_MEMBER_ANONYMOUS = "Anonymous"
Const gstrACL_ACE_ID_DEFAULT = "ID_ACL_DEFAULT"
Const gstrACL_ACE_ID_ANONYMOUS = "ID_ACL_ANONYMOUS"

Const gbitACL_RIGHTS_CREATE_ITEMS = &H2
Const gbitACL_RIGHTS_READ_ITEMS = &H1
Const gbitACL_RIGHTS_CREATE_SUBFOLDERS = &H80
Const gbitACL_RIGHTS_FOLDER_OWNER = &H100
Const gbitACL_RIGHTS_FOLDER_CONTACT = &H200
Const gbitACL_RIGHTS_FOLDER_VISIBLE = &H400
Const gbitACL_RIGHTS_EDIT_OWN = &H8
Const gbitACL_RIGHTS_EDIT_ALL = &H28
Const gbitACL_RIGHTS_DEL_OWN = &H10
Const gbitACL_RIGHTS_DEL_ALL = &H50

Const cACL_ROLES = 9
Dim gbitACL_RIGHTS_OWNER
Dim gbitACL_RIGHTS_OWNER_2
Dim gbitACL_RIGHTS_PUB_EDITOR
Dim gbitACL_RIGHTS_EDITOR
Dim gbitACL_RIGHTS_PUB_AUTHOR
Dim gbitACL_RIGHTS_AUTHOR
Dim gbitACL_RIGHTS_NONEDIT_AUTHOR
Dim gbitACL_RIGHTS_REVIEWER
Dim gbitACL_RIGHTS_CONTRIBUTOR
Dim gbitACL_RIGHTS_ROLE_NONE
Dim gbitACL_RIGHTS_ROLE_NONE_2
Dim gbitACL_RIGHTS_ROLE_NONE_3

Const gbitACL_RIGHTS_NONE = 0
    '
    ' Owner role is displayed w/ or w/out contact rights.
    '
    gbitACL_RIGHTS_OWNER_2 = gbitACL_RIGHTS_CREATE_ITEMS Or gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_CREATE_SUBFOLDERS Or gbitACL_RIGHTS_FOLDER_OWNER _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE _
                                    Or gbitACL_RIGHTS_EDIT_ALL Or gbitACL_RIGHTS_DEL_ALL

    gbitACL_RIGHTS_OWNER = gbitACL_RIGHTS_OWNER_2 Or gbitACL_RIGHTS_FOLDER_CONTACT

    gbitACL_RIGHTS_PUB_EDITOR = gbitACL_RIGHTS_CREATE_ITEMS Or gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_CREATE_SUBFOLDERS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE _
                                    Or gbitACL_RIGHTS_EDIT_ALL Or gbitACL_RIGHTS_DEL_ALL

    gbitACL_RIGHTS_EDITOR = gbitACL_RIGHTS_CREATE_ITEMS Or gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE _
                                    Or gbitACL_RIGHTS_EDIT_ALL Or gbitACL_RIGHTS_DEL_ALL

    gbitACL_RIGHTS_PUB_AUTHOR = gbitACL_RIGHTS_CREATE_ITEMS Or gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_CREATE_SUBFOLDERS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE _
                                    Or gbitACL_RIGHTS_EDIT_OWN Or gbitACL_RIGHTS_DEL_OWN

    gbitACL_RIGHTS_AUTHOR = gbitACL_RIGHTS_CREATE_ITEMS Or gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE _
                                    Or gbitACL_RIGHTS_EDIT_OWN Or gbitACL_RIGHTS_DEL_OWN

    gbitACL_RIGHTS_NONEDIT_AUTHOR = gbitACL_RIGHTS_CREATE_ITEMS Or gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE _
                                    Or gbitACL_RIGHTS_DEL_OWN

    gbitACL_RIGHTS_REVIEWER = gbitACL_RIGHTS_READ_ITEMS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE

    gbitACL_RIGHTS_CONTRIBUTOR = gbitACL_RIGHTS_CREATE_ITEMS _
                                    Or gbitACL_RIGHTS_FOLDER_VISIBLE
    '
    ' Role none is also displayed w/ folder visible rights & folder contact rights.
    '
    gbitACL_RIGHTS_ROLE_NONE = gbitACL_RIGHTS_FOLDER_VISIBLE
    gbitACL_RIGHTS_ROLE_NONE_2 = gbitACL_RIGHTS_NONE
    gbitACL_RIGHTS_ROLE_NONE_3 = gbitACL_RIGHTS_FOLDER_CONTACT

Const gstrACL_ROLE_OWNER = "Owner"
Const gstrACL_ROLE_PUB_EDITOR = "Publishing Editor"
Const gstrACL_ROLE_EDITOR = "Editor"
Const gstrACL_ROLE_PUB_AUTHOR = "Publishing Author" 
Const gstrACL_ROLE_AUTHOR = "Author"
Const gstrACL_ROLE_NONEDIT_AUTHOR = "Nonediting Author" 
Const gstrACL_ROLE_REVIEWER = "Reviewer"
Const gstrACL_ROLE_CONTRIBUTOR = "Contributor"
Const gstrACL_ROLE_NONE = "None"
Const gstrACL_ROLE_CUSTOM = "Custom"
'
' Errors
'
Const gerrDUPLICATE_ACL_MEMBER = &H800B0003
Const gerrCANT_DELETE_DEFAULT_ACL_MEMBER = &H800B0010

Const gstrMSG_ALERT_CANT_DELETE_DEFAULT_ACL_MEMBER = "Default and Anonymous entries may not be deleted."
Const gstrMSG_ALERT_DUPLICATE_ACL_MEMBER = "One or more recipients are already members of the access control list."
'
' Properties
'
Public ACL_cMembers
Public ACL_rgstrMemberID
Public ACL_rgstrMember

Public ACL_cRoles
Public ACL_rgstrRoles
Public ACL_rgrightsRoles

Public ACL_bIsOwner

Public ACL_bitRights

Public ACL_cContacts
Public ACL_rgstrContacts

Public ACL_err
Public ACL_strErr
'
' Init counts
'
ACL_cMembers = 0
ACL_cRoles = 0
ACL_cContacts = 0

Private Sub ClearErr()
'
' ClearErr clears the ACL error variables.
'
    ACL_err = gerrNONE
    ACL_strErr = gstrNONE
End Sub

Private Sub SetErr(perr, pstrErr)
'
' SetErr sets the ACL error variables.
'
    ACL_err = perr
    ACL_strErr = pstrErr
End Sub

Public Sub ACL_Open(pstrFolderID)
'
' Open creates an ACL object for passed folder & determines whether the current user
' has role, owner (which gives current user update rights).
'
    Dim acl
    Dim ace
    Dim bCurrentUserFound
    Dim bDefaultFound
    Dim bIsOwner
    Dim bitRightsDefault
    Dim colace
    Dim folder
    Dim strIDAce

    ACL_bIsOwner = False

    If Session(gstrSESS_ACL) Is Nothing Then
        Set acl = CreateObject("MSExchange.ACLObject")

        Set Session(gstrSESS_ACL) = acl
    Else
        Set acl = Session(gstrSESS_ACL)
    End If
    '
    ' Set CDOItem to get the folder's ACL
    '
    bitRightsDefault = gbitACL_RIGHTS_NONE

    Set folder = CDO_folderFromID(pstrFolderID, ACL_bIsOwner, bitRightsDefault)

    acl.CDOItem = folder

    Set colace = acl.ACEs
    '
    ' Search for the default rights
    '
    If colace.Count > 0 Then
        For Each ace In colace
            strIDace = ace.ID

            If strIDace = gstrACL_ACE_ID_DEFAULT Then
                bitRightsDefault = ace.Rights

                Exit For
            End If
        Next
    End If
    '
    ' Save default rights
    '
    Session(gstrSESS_BIT_RIGHTS_DEFAULT) = bitRightsDefault

    Set colace = Nothing
    Set folder = Nothing
    Set acl = Nothing   
End Sub

Public Sub ACL_GetMembers()
'
' GetMembers gets ACL members for the open folder.
'
    Dim ace
    Dim acl
    Dim colace
    Dim iMember
    Dim iMemberMax

    Set acl = Session(gstrSESS_ACL)
    Set colace = acl.ACEs

    ACL_cMembers = colace.Count

    If ACL_cMembers > 0 Then
        iMemberMax = ACL_cMembers - 1
         
        Redim ACL_rgstrMemberID(iMemberMax)

        iMember = 0

        For Each ace In colace
            ACL_rgstrMemberID(iMember) = ace.ID

            iMember = iMember + 1
        Next

        ACL_rgstrMember = rgstrNamesFromAddressEntryIDs(ACL_rgstrMemberID)
    End If
End Sub

Private Function rgstrNamesFromAddressEntryIDs(prgstrID)
'
' rgstrNamesFromAddressEntryIDs returns an array of display names for the passed entry id's.
'
    Dim iID
    Dim rgstrName

    Redim rgstrName(UBound(prgstrID))

    For iID = LBound(prgstrID) To UBound(prgstrID)
        If prgstrID(iID) = gstrACL_ACE_ID_DEFAULT Then
            rgstrName(iID) = gstrACL_MEMBER_DEFAULT
        ElseIf prgstrID(iID) = gstrACL_ACE_ID_ANONYMOUS Then
            rgstrName(iID) = gstrACL_MEMBER_ANONYMOUS
        Else
            rgstrName(iID) = CDO_strNameFromAddressEntryID(prgstrID(iID))
        End If
    Next

    rgstrNamesFromAddressEntryIDs = rgstrName
End Function

Public Sub ACL_GetMemberProperties(pstrACLMemberID, pbIsOwner)
'
' GetMemberProperties sets ACL property variables for the passed acl member.
' When the current user is not an owner, a list of folder contacts is prepared.
'
    Call GetRoles()

    ACL_bitRights = bitRights(pstrACLMemberID)

    If Not pbIsOwner Then
        Call GetContacts()
    End If
End Sub

Private Sub GetContacts()
'
' GetContacts prepares a list of folder contacts.
'
    Dim ace
    Dim acl
    Dim colace
    Dim cContacts
    Dim cMembers
    Dim rgstrContactID

    Set acl = Session(gstrSESS_ACL)
    Set colace = acl.ACEs

    cMembers = colace.Count
    ACL_cContacts = 0   
    
    If cMembers > 0 Then
        Redim rgstrContactID(cMembers - 1)
        '
        ' Search for contacts
        '
        For Each ace In colace
            If ((ace.Rights And gbitACL_RIGHTS_FOLDER_CONTACT) = gbitACL_RIGHTS_FOLDER_CONTACT) Then
                rgstrContactID(ACL_cContacts) = ace.ID
                ACL_cContacts = ACL_cContacts + 1
            End If
        Next

        Redim Preserve rgstrContactID(ACL_cContacts - 1)

        If ACL_cContacts > 0 Then
            ACL_rgstrContacts = rgstrNamesFromAddressEntryIDs(rgstrContactID)
        End If
    End If
End Sub

Private Function bitRights(pstrACLMemberID)
'
' bitRights returns rights for the passed member.
'
    Dim ace
    Dim acl
    Dim bMemberFound
    Dim bitRightsDefault

    Set acl = Session(gstrSESS_ACL)
    '
    ' Search for the passed member
    '
    bMemberFound = False
    bitRightsDefault = CLng(Session(gstrSESS_BIT_RIGHTS_DEFAULT))

    For Each ace In acl.ACEs
        Select Case ace.ID
            Case gstrACL_ACE_ID_DEFAULT
                bitRightsDefault = ace.Rights
            Case pstrACLMemberID
                bMemberFound = True

                bitRights = ace.Rights

                Exit For
        End Select
    Next
    '
    ' Return default rights if current user is not found.
    '
    If Not bMemberFound Then
        bitRights = bitRightsDefault
    End If
End Function

Private Sub GetRoles()
'
' GetRoles returns arrays of roles & their corresponding role rights.
'
    ACL_cRoles = cACL_ROLES

    ACL_rgstrRoles = Array(gstrACL_ROLE_OWNER, gstrACL_ROLE_PUB_EDITOR _
                        , gstrACL_ROLE_EDITOR, gstrACL_ROLE_PUB_AUTHOR _
                        , gstrACL_ROLE_AUTHOR, gstrACL_ROLE_NONEDIT_AUTHOR _
                        , gstrACL_ROLE_REVIEWER, gstrACL_ROLE_CONTRIBUTOR _
                        , gstrACL_ROLE_NONE)
    
    ACL_rgrightsRoles = Array(gbitACL_RIGHTS_OWNER, gbitACL_RIGHTS_PUB_EDITOR _
                                , gbitACL_RIGHTS_EDITOR, gbitACL_RIGHTS_PUB_AUTHOR _
                                , gbitACL_RIGHTS_AUTHOR, gbitACL_RIGHTS_NONEDIT_AUTHOR _
                                , gbitACL_RIGHTS_REVIEWER, gbitACL_RIGHTS_CONTRIBUTOR _
                                , gbitACL_RIGHTS_ROLE_NONE)
End Sub

Public Sub ACL_DeleteMember(pstrACLMemberID)
'
' DeleteMember deletes the passed member from the acl
'
    Dim acl

    Set acl = Session(gstrSESS_ACL)
    '
    ' Under IIS, it is necessary to use CStr even if variant is type string.
    '
    acl.ACEs.Delete CStr(pstrACLMemberID)

    Set acl = Nothing
End Sub

Public Sub ACL_AddMember(prgstrACLMemberID)
'
' AddMember adds the passed members to the acl
'
    Dim ace
    Dim acl
    Dim iace
	Dim bDupMsgShown

	Call ClearErr()
	bDupMsgShown = False

    Set acl = Session(gstrSESS_ACL)

    For iace = LBound(prgstrACLMemberID) To UBound(prgstrACLMemberID)
        Set ace = CreateObject("MSExchange.ACE")

        ace.Rights = CLng(Session(gstrSESS_BIT_RIGHTS_DEFAULT))
        ace.ID = prgstrACLMemberID(iace)

		On Error Resume Next

        acl.ACEs.Add ace

        Select Case Err.Number
            Case gerrNONE
                '
                ' No error, continue
                '
            Case gerrDUPLICATE_ACL_MEMBER
			    '
			    ' Trap for duplicate acl member error & continue.
			    '
			    If Not bDupMsgShown Then
				    Call SetErr(Err.Number, gstrMSG_ALERT_DUPLICATE_ACL_MEMBER)

				    bDupMsgShown = True
			    End If

			    Err.Clear
			    On Error GoTo 0
		    Case Else
			    '
			    ' Exit for all other errors
			    '
			    Exit Sub
		End Select
    Next

    Set ace = Nothing
    Set acl = Nothing

End Sub

Public Sub ACL_ModifyMember(pstrACLMemberID, pbitRights)
'
' ModifyMember modifies the passed acl member's rights
'
    Dim acl

    Set acl = Session(gstrSESS_ACL)
    '
    ' Under IIS, it is necessary to use CStr even if variant is type string.
    '
    acl.ACEs.Item(CStr(pstrACLMemberID)).Rights = pbitRights
    '
    ' Update cached default rights
    '
    If pstrACLMemberID = gstrACL_ACE_ID_DEFAULT Then
        Session(gstrSESS_BIT_RIGHTS_DEFAULT) = pbitRights
    End If
    
    Set acl = Nothing

End Sub

Public Sub ACL_Update()
'
' Update commits changes saved in the acl object to Exchange.
'
    Dim acl

    Set acl = Session(gstrSESS_ACL)

    acl.Update

    Set acl = Nothing
End Sub
%>