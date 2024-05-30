<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="CDO.inc"-->
<!--#include file="ACL.inc"-->
<%
'<!--ACL Sample Application-->
'<!--HandleCmds.asp : Handle Commands asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' HandleCmds contains routines for handling all application messages.
'
    
    Dim strCmd
    Dim mfrm

    On Error Resume Next
    ' 
    ' Ensure the user is authenticated
    '
    Call AuthenticateUser()
    '
    ' Process the command
    '
    strCmd = Request(gstrREQUEST_CMD)
    '
    ' On First execution strCmd is empty and no code is executed.
    '
    If len(strCmd) > 0 Then
        '
        ' Verify cdo session
        '
        Select Case strCmd 
            Case gstrCMD_EXCH_LOGON, gstrCMD_SEL_FOLDER_NEW
                '
                ' Don't Check session when logging on
                '
            Case Else
                Call App_CheckSession()
        End Select

        Set mfrm = Request.Form

        Select Case strCmd
            Case gstrCMD_ACL_MAINT
                Call ShowACLMaint()
            Case gstrCMD_ACL_MAINT_NEW
                Call ShowACLMaintNew()
            Case gstrCMD_ADD_ACL_MEMBER
                Call AddACLMember()
            Case gstrCMD_COMMIT
                Call CommitACLChanges()
            Case gstrCMD_DEL_ACL_MEMBER
                Call DelACLMember()
            Case gstrCMD_MOD_ACL_MEMBER
                Call ModACLMember()
            Case gstrCMD_EXCH_LOGON
                Call ShowExchLogon()
            Case gstrCMD_EXPAND_FOLDER
                Call AddToBranch(App_strFromHTML(CStr(mfrm(gstrREQUEST_HID_STR_FOLDER_ID))) _
                                    , App_strFromHTML(CStr(mfrm(gstrREQUEST_HID_STR_FOLDER_NAME))))
            Case gstrCMD_FIND_ADDRESSES
                Call ShowSelAddresses(App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)), CDO_iPAGE_FIRST)
            Case gstrCMD_GO_TO_BRANCH_LEVEL
                Call GoToBranchLevel(CInt(mfrm(gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL)))
            Case gstrCMD_MEMBER_PROPERTIES
                Call ShowACLMemberProperties()
            Case gstrCMD_SEL_ADDRESSES
                Call ShowSelAddresses(gstrNONE, CDO_iPAGE_FIRST)
            Case gstrCMD_SEL_ADDRESSES_GO_TO_PAGE
                Call ShowSelAddresses(App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)), CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))
            Case gstrCMD_SEL_FOLDER
                Call ShowSelFolder()
            Case gstrCMD_SEL_FOLDER_GO_TO_PAGE
                Call ShowSelFolderGoToPage(CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))
            Case gstrCMD_SEL_FOLDER_NEW
                Call Logon()
        End Select

        Set mfrm = Nothing
    End If

Private Sub AuthenticateUser()
'
' AuthenticateUser obtains the userID & password, if the user hasn't logged on.
'
    Dim strAuthType

    strAuthType = Request.ServerVariables("AUTH_TYPE")
    If InStr(1, "_BasicNTLM", strAuthType, 1) < 2 Then
      Response.Buffer = TRUE
      Response.Status = ("401 Unauthorized")
      Response.End
    End IF
End Sub

Private Sub Logon()
'
' Logon creates a cdo session & shows the folder selection page.
'
    Dim errNo
    Dim strErr

    On Error Resume Next

    Call CDO_Logon(cstr(mfrm(gstrREQUEST_TXT_EXCH_SERVER)), cstr(mfrm(gstrREQUEST_TXT_MAILBOX)))

    If Err.Number = gerrNONE And CDO_err = gerrNONE Then
        '
        ' Initialize folder arrays
        '
        Call InitFolderArrays()

        Call ShowSelFolder()
    Else
        If Err.Number <> gerrNone Then
            errNo = Err.Number
            strErr = Err.Description
        Else
            errNo = CDO_err
            strErr = CDO_strErr
        End If

        Select Case errNo
            Case CDO_errINVALID_SERVER_MAILBOX
                Call App_ShowMsg(gstrMSG_ALERT_LOGON_FAILED & gchSPACE & gchSPACE & CDO_strERR_INVALID_SERVER_MAILBOX, gerrNONE, gstrNONE)
            Case Else
                Call App_ShowMsg(gstrMSG_ALERT_LOGON_FAILED, errNo, strErr)
        End Select
    End If

End Sub

Private Sub InitFolderArrays()
'
' Folder arrays are initialized to force the app to show all stores.
'
    Dim rgstrBranchFolderID()
    Dim rgstrBranchFolderName()
    Dim rgstrBranchFolderPage()

    ReDim rgstrBranchFolderID(giBRANCH_ROOT)
    ReDim rgstrBranchFolderName(giBRANCH_ROOT)
    ReDim rgstrBranchFolderPage(giBRANCH_ROOT)

    rgstrBranchFolderID(giBRANCH_ROOT) = Empty
    rgstrBranchFolderName(giBRANCH_ROOT) = gstrBRANCH_ROOT_NAME
    rgstrBranchFolderPage(giBRANCH_ROOT) = CDO_iPAGE_FIRST

    Session(gstrSESS_RG_BRANCH_FOLDER_ID) = rgstrBranchFolderID
    Session(gstrSESS_RG_BRANCH_FOLDER_NAME) = rgstrBranchFolderName
    Session(gstrSESS_RG_BRANCH_FOLDER_PAGE) = rgstrBranchFolderPage
End Sub

Private Sub AddToBranch(pstrFolderID, pstrFolderName)
'
' AddToBranch adds the passed ID & name to the folder branch.
'
    Dim rgstrBranchFolderID
    Dim rgstrBranchFolderName
    Dim rgstrBranchFolderPage
    Dim iFolderMax
    
    rgstrBranchFolderID = Session(gstrSESS_RG_BRANCH_FOLDER_ID)
    rgstrBranchFolderName = Session(gstrSESS_RG_BRANCH_FOLDER_NAME)
    rgstrBranchFolderPage = Session(gstrSESS_RG_BRANCH_FOLDER_PAGE)
    
    iFolderMax = UBound(rgstrBranchFolderID) + 1

    ReDim Preserve rgstrBranchFolderID(iFolderMax)
    ReDim Preserve rgstrBranchFolderName(iFolderMax)
    ReDim Preserve rgstrBranchFolderPage(iFolderMax)

    rgstrBranchFolderID(iFolderMax) = pstrFolderID
    rgstrBranchFolderName(iFolderMax) = pstrFolderName
    rgstrBranchFolderPage(iFolderMax) = CDO_iPAGE_FIRST

    Session(gstrSESS_RG_BRANCH_FOLDER_ID) = rgstrBranchFolderID
    Session(gstrSESS_RG_BRANCH_FOLDER_NAME) = rgstrBranchFolderName
    Session(gstrSESS_RG_BRANCH_FOLDER_PAGE) = rgstrBranchFolderPage

    Call ShowSelFolder()
End Sub

Private Sub GoToBranchLevel(piFolderBranchLevel)
'
' GoToBranchLevel redim's the folder branch arrays for the passed level.
'
    Dim rgstrBranchFolderID
    Dim rgstrBranchFolderName
    Dim rgstrBranchFolderPage
    Dim iFolderMax

    rgstrBranchFolderID = Session(gstrSESS_RG_BRANCH_FOLDER_ID)
    rgstrBranchFolderName = Session(gstrSESS_RG_BRANCH_FOLDER_NAME)
    rgstrBranchFolderPage = Session(gstrSESS_RG_BRANCH_FOLDER_PAGE)

    iFolderMax = piFolderBranchLevel

    ReDim Preserve rgstrBranchFolderID(iFolderMax)
    ReDim Preserve rgstrBranchFolderName(iFolderMax)
    ReDim Preserve rgstrBranchFolderPage(iFolderMax)

    Session(gstrSESS_RG_BRANCH_FOLDER_ID) = rgstrBranchFolderID
    Session(gstrSESS_RG_BRANCH_FOLDER_NAME) = rgstrBranchFolderName
    Session(gstrSESS_RG_BRANCH_FOLDER_Page) = rgstrBranchFolderPage

    Call ShowSelFolder()
End Sub

Private Sub ShowACLMaintNew()
'
' ShowACLMaintNew sets session properties & shows the ACL Maint page
'
    Dim strFolderID
    Dim strErr
    Dim errSav

    On Error Resume Next

    Session(gstrSESS_FOLDER_NAME) = mfrm(gstrREQUEST_HID_STR_FOLDER_NAME)
    strFolderID = mfrm(gstrREQUEST_HID_STR_FOLDER_ID)

    Call ACL_Open(strFolderID)

    If Err.Number = gerrNONE Then
        Session(gstrSESS_FOLDER_ID) = strFolderID
        Session(gstrSESS_IS_OWNER) = ACL_bIsOwner

        If ACL_bIsOwner Then
            Call ShowACLMaint()
        Else
            Call ShowACLMemberProperties()
        End If
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_ACL_OBJECT, Err.Number, Err.Description)
    End If
End Sub

Private Sub ShowACLMaint()
'
' ShowACLMaint shows the ACL Maint page
'
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_ACL_MAINT%>"
    </SCRIPT>
<%
End Sub

Private Sub DelACLMember()
'
' DelACLMember deletes selected ACL members & re-paints the screen.
'
    On Error Resume Next

    Call ACL_DeleteMember(CStr(mfrm(gstrREQUEST_ACL_MEMBER_ID)))

    Select Case Err.Number
        Case gerrNONE
            Call ShowACLMaint()
        Case gerrCANT_DELETE_DEFAULT_ACL_MEMBER
            Call App_ShowMsg(gstrMSG_ALERT_CANT_DELETE_DEFAULT_ACL_MEMBER, gerrNONE, gstrNONE)
        Case Else
            Call App_ShowMsg(Replace(gstrMSG_ALERT_CANT_DELETE, gchREPLACE , CStr(mfrm(gstrREQUEST_ACL_MEMBER_DISP_NAME))) _
                                , Err.Number, Err.Description)
    End Select
End Sub

Private Sub ShowSelAddresses(pstrSelCriteria, piPage)
'
' ShowSelAddresses inits the address page & shows the sel address page.
'
    Session(gstrSESS_SEL_CRITERIA) = pstrSelCriteria
    Session(gstrSESS_SEL_ADDRESS_PAGE) = piPage
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_SEL_ADDRESSES%>"
    </SCRIPT>
<%
End Sub

Private Sub ShowSelFolderGoToPage(piPage)
'
' ShowSelFolderGoToPage updates the folder page & shows the sel folder screen.
'
    Dim rgstrBranchFolderPage

    rgstrBranchFolderPage = Session(gstrSESS_RG_BRANCH_FOLDER_PAGE)

    rgstrBranchFolderPage(UBound(rgstrBranchFolderPage)) = piPage

    Session(gstrSESS_RG_BRANCH_FOLDER_PAGE) = rgstrBranchFolderPage

    Call ShowSelFolder()
End Sub

Private Sub ShowSelFolder()
'
' ShowSelFolder shows the folder selection page
'
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_SEL_FOLDER%>"
    </SCRIPT>
<%
End Sub

Private Sub ShowExchLogon()
'
' ShowExchLogon shows the Exchange Server Logon page
'
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_EXCH_LOGON%>"
    </SCRIPT>
<%
End Sub

Private Sub ShowACLMemberProperties()
'
' ShowACLMemberProperties shows the ACL member property page
'

    Session(gstrSESS_ACL_MEMBER_ID) = mfrm(gstrREQUEST_ACL_MEMBER_ID)
    Session(gstrSESS_ACL_MEMBER_DISP_NAME) = mfrm(gstrREQUEST_ACL_MEMBER_DISP_NAME)
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_PROPERTIES%>"
    </SCRIPT>
<%
End Sub

Private Sub AddACLMember()
    Dim strMsg

    On Error Resume Next

    Call ACL_AddMember(App_RgstrFromRequestForm(mfrm(gstrREQUEST_LST_SEL)))

    If Err.Number = gerrNONE Then

        If ACL_err = gerrNONE Then
            strMsg = gstrMSG_ALERT_ADD_CONFIRMED
        Else
            strMsg = gstrMSG_ALERT_ADD_CONFIRMED & gchSPACE & gchSPACE & ACL_strErr
        End If

        Call App_ShowMsg(strMsg , gerrNONE, gstrNONE)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_ADD, Err.Number, Err.Description)
    End If
End Sub

Private Sub ModACLMember()
    Dim strDispName

    On Error Resume Next

    strDispName = Session(gstrSESS_ACL_MEMBER_DISP_NAME)

    Call ACL_ModifyMember(CStr(Session(gstrSESS_ACL_MEMBER_ID)), cLng(mfrm(gstrREQUEST_HID_BIT_RIGHTS)))

    If Err.Number = gerrNONE Then
        Call App_ShowMsg(Replace(gstrMSG_ALERT_MEMBER_UPD_CONFIRMED, gchREPLACE, strDispName) , gerrNONE, gstrNONE)

        Call ShowACLMaint()
    Else
        Call App_ShowMsg(Replace(gstrMSG_ALERT_CANT_MODIFY, gchREPLACE , strDispName) _
                            , Err.Number, Err.Description)
    End If
End Sub

Private Sub CommitACLChanges()
'
' CommitACLChanges commits changes made to the ACL.
'

    On Error Resume Next

    Call ACL_Update()

    If Err.Number = gerrNONE Then
        Call App_ShowMsg(gstrMSG_ALERT_UPD_CONFIRMED , gerrNONE, gstrNONE)

        Call ShowSelFolder()
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_UPD, Err.Number, Err.Description)
    End If
End Sub
%>
<HTML>
<HEAD>
<TITLE></TITLE>
</HEAD>
<BODY>
</BODY>
</HTML>
