<%
'<!--ACL Sample Application-->
'<!--CDO.inc : CDO constants, properties, & methods-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' CDO.inc contains constants, properties, & routines for handling CDO.
'
Const CDO_PR_ACCESS = &H0FF40003
Const CDO_PR_RIGHTS = &H66390003 
Const CDO_PR_STORE_SUPPORT_MASK = &H340D0003
Const CDO_PR_IPM_PUBLIC_FOLDERS_ENTRYID = &H66310102

Const bitCDO_ACCESS_OWNER = &H5
Const bitCDO_STORE_SUPPORT_PUBLIC_STORE = &H4000

Const CdoAddressListGAL = 0

Const CDO_errINVALID_SERVER_MAILBOX = &H80040111

Const CDO_strERR_INVALID_SERVER_MAILBOX = "Server or mailbox may not be valid."

Const CDO_cPAGE_SIZE = 100
Const CDO_iPAGE_FIRST = 1 

Const CDO_iFOLDER_PUBLIC_STORE_NONE = -1

Public CDO_cFolders
Public CDO_rgstrFolderID
Public CDO_rgstrFolderName
Public CDO_rgbFolderExpands
Public CDO_iFolderPublicStore
    CDO_iFolderPublicStore = CDO_iFOLDER_PUBLIC_STORE_NONE

Public CDO_cSel
Public CDO_rgstrAddressDisplayName
Public CDO_rgstrAddressID

Public CDO_iPage
Public CDO_cPage

Public CDO_err
Public CDO_strErr

    Call CDO_ClearErr()

Public Sub CDO_ClearErr()
    CDO_err = gerrNONE
    CDO_strErr = gstrNONE
End Sub

Public Sub CDO_Logon(pstrServer, pstrMailbox)
    Dim sessCDO
    Dim folder
    Dim strProfileInfo
    Dim strProfileName
    Dim strProfilePassword
    Dim bShowDialog
    Dim bNewSession
    Dim lngParentWindow
    Dim bNoMail
    Dim objRenderApp
    '
    ' Logoff if already logged on
    '
    Call CDO_Logoff()

    Set sessCDO = CreateObject("MAPI.Session")

    If Not sessCDO is Nothing Then
        Set objRenderApp = Application(gstrAPP_RENDER_APPLICATION)

        strProfileInfo = pstrServer & vbLf & pstrMailbox
        '
        ' Logon
        ' 
        strProfileName =  gstrNONE
        strProfilePassword = gstrNONE
        bShowDialog = False
        bNewSession = True
        lngParentWindow = 0
        bNoMail = True

        sessCDO.Logon strProfileName, strProfilePassword, bShowDialog, bNewSession _
                        , lngParentWindow, bNoMail, strProfileInfo
        If Err.Number = gerrNone Then
            '
            ' Access inbox to verify logon was successful
            '
            Set folder = sessCDO.Inbox

            If Err.Number = gerrNone Then
                Set Session(gstrSESS_CDO_SESSION) = sessCDO
                Session(gstrSESS_HANDLE_IMPERSONATE) = objRenderApp.ImpID
                Session(gstrSESS_EXCH_SERVER) = pstrServer
                Session(gstrSESS_MAILBOX) = pstrMailbox
            End If
        End If
    End If
End Sub

Public Sub CDO_Logoff()
'
' CDO_Logoff logs off the passed CDO Session.
'
    Dim sessCDO
    Dim hImp
    Dim objRenderApp

    On Error Resume Next

    If CDO_bValidSession() Then
        '
        ' Release ACL object
        '
        If Not Session(gstrSESS_ACL) Is Nothing Then
            Set Session(gstrSESS_ACL) = Nothing
        End If
        '
        ' Logoff & release cdo session
        '
        Set sessCDO = Session(gstrSESS_CDO_SESSION)

        Set Session(gstrSESS_CDO_SESSION) = Nothing

        sessCDO.Logoff
        Set sessCDO = Nothing
        '
        ' Release impersonation handle
        '
        Set objRenderApp = Application(gstrAPP_RENDER_APPLICATION)
        hImp = Session(gstrSESS_HANDLE_IMPERSONATE)

        Session(gstrSESS_HANDLE_IMPERSONATE) = Empty
        objRenderApp.CloseSysHandle(hImp)
        Set objRenderApp = Nothing
    End If

    Err.Clear
End Sub

Public Function CDO_bValidSession()
    Dim hImp
    Dim fImp
    Dim objRenderApplication

    On Error Resume Next

    If IsEmpty(Session(gstrSESS_CDO_SESSION)) Or (Session(gstrSESS_CDO_SESSION) Is Nothing) Then
        CDO_bValidSession = False
    Else
        hImp = Session(gstrSESS_HANDLE_IMPERSONATE)

        Set objRenderApplication = Application(gstrAPP_RENDER_APPLICATION)
        If objRenderApplication Is Nothing Then
            Call App_ShowMsg(gstrMSG_ALERT_CANT_GET_RENDER_APP, Err.Number, Err.Description)
            Response.End
        Else
            fImp = objRenderApplication.Impersonate(hImp)
            If fImp <> 1 Then
                Call App_ShowMsg(gstrMSG_ALERT_CANT_IMPERSONATE, Err.Number, Err.Description)
                Response.End
            End If
        End If

        CDO_bValidSession = True
    End If
End Function

Public Function CDO_strExchServer()
    Dim objRenderApp
    Dim strExchServer

    On Error Resume Next

    Set objRenderApp = Application(gstrAPP_RENDER_APPLICATION)
    strExchServer = objRenderApp.ConfigParameter("Server")

    If IsEmpty(strExchServer) then    
        strExchServer = Request.ServerVariables("SERVER_NAME")
    End If

    CDO_strExchServer = strExchServer

    Set objRenderApp = Nothing
End Function

Public Function CDO_folderFromID(pstrFolderID, pbIsOwner, pbitRightsDefault)
'
' folderFromID returns a folder object for the passed ID, a boolean indicating whether the
' current user has update access, & the default rights for the folder.
'
    Dim sessCDO
    Dim folder

    Set sessCDO = Session(gstrSESS_CDO_SESSION)

    Set folder = sessCDO.GetFolder(pstrFolderID, Null)
    pbIsOwner = ((folder.Fields.Item(CDO_PR_ACCESS) And bitCDO_ACCESS_OWNER) = bitCDO_ACCESS_OWNER)

    pbitRightsDefault = folder.Fields.Item(CDO_PR_RIGHTS)

    Set CDO_folderFromID = folder

    Set folder = Nothing
    Set sessCDO = Nothing
End Function

Public Sub CDO_GetStores(piPage)
'
' GetStores creates an array of store names & ids.
'
    Dim sessCDO
    Dim colStores
    Dim ifolder
    Dim iFolderMax
    Dim istore
    Dim istoreFirst
    Dim istoreLast
    Dim store
    Dim bPublicFolderStore
    Dim folderRoot

    On Error Resume Next

    Set sessCDO = Session(gstrSESS_CDO_SESSION)

    Set colStores = sessCDO.InfoStores

    CDO_cFolders = colStores.Count
    CDO_iPage = piPage

    Call App_PrepPaging(CDO_cFolders, CDO_cPAGE_SIZE, CDO_iPAGE_FIRST, CDO_iPage, CDO_cPage _
                        , istoreFirst, istoreLast)

    If CDO_cFolders > 0 Then
        iFolderMax = istoreLast - istoreFirst

        ReDim CDO_rgstrFolderID(iFolderMax)
        ReDim CDO_rgstrFolderName(iFolderMax)
        ReDim CDO_rgbFolderExpands(iFolderMax)

        For istore = istoreFirst To istoreLast
            Set store = colStores(istore)

            ifolder = istore - istoreFirst
            CDO_rgstrFolderName(ifolder) = store.Name
            '
            ' Determine whether current store is public folder store
            '
            bPublicFolderStore = (store.Fields(CDO_PR_STORE_SUPPORT_MASK) _
                                    And bitCDO_STORE_SUPPORT_PUBLIC_STORE)
            '
            ' Get folder ID
            '
            If bPublicFolderStore Then
                '
                ' For the public folder store, you cannot obtain the folder from the rootfolder
                ' property under IIS.  Get the root folder via GetFolder call.
                '
                CDO_rgstrFolderID(ifolder) = store.Fields(CDO_PR_IPM_PUBLIC_FOLDERS_ENTRYID)
                CDO_iFolderPublicStore = ifolder

                Set folderRoot = sessCDO.GetFolder(CDO_rgstrFolderID(ifolder), Null)
            Else 
                Set folderRoot = store.RootFolder
               
                CDO_rgstrFolderID(ifolder) = folderRoot.ID
            End If

            CDO_rgbFolderExpands(ifolder) = (folderRoot.Folders.Count > 0)
        Next
    End If

    Set folderRoot = Nothing
    Set colStores = Nothing
    Set sessCDO = Nothing
End Sub

Public Sub CDO_GetFolders(pstrFolderID, piPage)
'
' GetFolders creates an array of folder names & ids.
'
    Dim colFolders
    Dim folder
    Dim folderParent
    Dim ifolder
    Dim ifolderMax
    Dim ifolderFirst
    Dim ifolderLast
    Dim ifolderSav
    Dim sessCDO

    On Error Resume Next

    Set sessCDO = Session(gstrSESS_CDO_SESSION)

    Set folderParent = sessCDO.GetFolder(pstrFolderID, Null)

    Set colFolders = folderParent.Folders
    '
    ' Save the count.  For large collections, the count is not accurate.  See CDO help for details.
    '
    CDO_cFolders = colFolders.Count
    CDO_iPage = piPage

    Call App_PrepPaging(CDO_cFolders, CDO_cPAGE_SIZE, CDO_iPAGE_FIRST, CDO_iPage, CDO_cPage _
                        , ifolderFirst, ifolderLast)

    If CDO_cFolders > 0 Then
        iFolderMax = ifolderLast - ifolderFirst

        ReDim CDO_rgstrFolderID(iFolderMax)
        ReDim CDO_rgstrFolderName(iFolderMax)
        ReDim CDO_rgbFolderExpands(iFolderMax)
        '
        ' Loop through the folders collection
        '
        For ifolder = ifolderFirst To ifolderLast
            Set folder = colFolders(ifolder)

            ifolderSav = ifolder - ifolderFirst

            CDO_rgstrFolderID(ifolderSav) = folder.ID
            CDO_rgstrFolderName(ifolderSav) = folder.Name
            CDO_rgbFolderExpands(ifolderSav) = (folder.Folders.Count > 0)
        Next
    End If
End Sub

Public Sub CDO_FindAddresses(pstrSelCriteria, piPage)
'
' FindAddresses prepares arrays of display name and address id for the passed selection criteria
' & page.
'
    Dim aeFilter        ' Address Entries Filter
    Dim ae              ' Address Entry object
    Dim al              ' Address List object
    Dim colae           ' Address Entries Collection
    Dim iAddress
    Dim iAddressSav
    Dim iAddressFirst
    Dim iAddressLast
    Dim iAddressMax
    Dim sessCDO

    On Error Resume Next

    Set sessCDO = Session(gstrSESS_CDO_SESSION)
    '
    ' Get the global address list & it's address entries collection & filter.
    '
    Set al = sessCDO.GetAddressList(CdoAddressListGAL)
    Set colae = al.AddressEntries
    Set aeFilter = colae.Filter
    '
    ' Set the filter to use display name
    '
    aeFilter.Name = pstrSelCriteria
    '
    ' Save disp name & id
    '
    CDO_cSel = colae.Count
    CDO_iPage = piPage

    Call App_PrepPaging(CDO_cSel, CDO_cPAGE_SIZE, CDO_iPAGE_FIRST, CDO_iPage, CDO_cPage _
                        , iAddressFirst, iAddressLast)

    If CDO_cSel > 0 Then
        iAddressMax = iAddressLast - iAddressFirst

        ReDim CDO_rgstrAddressDisplayName(iAddressMax)
        ReDim CDO_rgstrAddressID(iAddressMax)

        For iAddress = iAddressFirst To iAddressLast
            Set ae = colae.Item(iAddress)

            iAddressSav = iAddress - iAddressFirst

            CDO_rgstrAddressDisplayName(iAddressSav) = ae.Name
            CDO_rgstrAddressID(iAddressSav) = ae.ID
        Next
    End If
    
    Set colae.Filter = Nothing
    
    Set ae = Nothing
    Set aeFilter = Nothing
    Set colae = Nothing
    Set sessCDO = Nothing        
End Sub

Public Function CDO_strNameFromAddressEntryID(pstrIDae)
'
' strNameFromAddressEntryID returns the display name for the passed address entry id.
'
    Dim sessCDO
    Dim ae

    Set sessCDO = Session(gstrSESS_CDO_SESSION)

    Set ae = sessCDO.GetAddressEntry(pstrIDae)

    CDO_strNameFromAddressEntryID = ae.Name
    
    Set ae = Nothing
    Set sessCDO = Nothing
End Function
%>