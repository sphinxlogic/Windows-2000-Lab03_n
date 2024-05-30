<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ADS.inc"-->
<!--#include file="NTAcct.inc"-->
<%
'<!--Distribution List Maintenance Sample Application-->
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
        ' Verify session
        '
        Select Case strCmd 
            Case gstrCMD_SEL_EXCH_SERVER, gstrCMD_DL_MAINT_NEW
                '
                ' Don't Check session when logging on
                '
            Case Else
                Call App_CheckSession()
        End Select

        Set mfrm = Request.Form
        '
        ' In the DL Properties page, the user may modify certain properties.  If properties
        ' are modified, update them here.  If successful, perform the cmd.
        '
        If bUpdateProperties(strCmd) Then
            Select Case strCmd
                Case gstrCMD_ADD_DL
                    '
                    ' Show the Add DL screen.
                    '
                    Call ShowDLProperties(gstrNONE, giADS_PAGE_FIRST, gstrCMD_ADD_DL)

                Case gstrCMD_ADD_DL_MEMBER
                    '
                    ' Show the select dn screen to provide for dl member selection.
                    '
                    Call ShowSelDN(gstrCMD_DO_ADD_DL_MEMBER, gstrNONE, giADS_PAGE_FIRST)

                Case gstrCMD_DEL_DL
                    '
                    ' Delete the selected DL
                    '
                    Call DelDL()

                Case gstrCMD_DEL_DL_MEMBER
                    '
                    ' Delete DL members
                    '    
                    Call DelDLMember()

                Case gstrCMD_DL_MAINT, gstrCMD_DL_MAINT_CANCEL_ADD
                    '
                    ' Show the DL maintenance screen.
                    '
                    Call ShowDLMaint(CStr(Session(gstrSESS_SEL_CRITERIA_DL)) _
                                        , CInt(Session(gstrSESS_DL_PAGE)))

                Case gstrCMD_DL_MAINT_GO_TO_PAGE
                    '
                    ' Show the DL maintenance screen w/ a new page of dl's.
                    '
                    Call ShowDLMaint(CStr(Session(gstrSESS_SEL_CRITERIA_DL)) _
                                        , CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))

                Case gstrCMD_DL_MAINT_NEW
                    '
                    ' Show the DL maintenance screen for the first time after selecting an 
                    ' Exchange server.
                    '
                    Call ShowDLMaintNew()

                Case gstrCMD_DL_PROPERTIES
                    '
                    ' Show the DL properties screen after selecting a DL & pressing
                    ' modify in the DL maintenance screen.
                    '
                    Call ShowDLProperties(App_strFromHTML(CStr(mfrm(gstrREQUEST_LST_DL))) _
                                            , giADS_PAGE_FIRST, gstrCMD_DL_PROPERTIES)

                Case gstrCMD_DL_PROPERTIES_GO_TO_PAGE
                    '
                    ' Go to member page of dl properties screen.
                    '
                    Call ShowDLProperties(CStr(Session(gstrSESS_DL_ADS_PATH)) _
                                            , CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)), gstrCMD_DL_PROPERTIES)

                Case gstrCMD_DL_PROPERTIES_RETURN
                    '
                    ' Show the DL member maintenance screen after returning from the Add member screen.
                    '
                    Call ShowDLProperties(CStr(Session(gstrSESS_DL_ADS_PATH)) _
                                            , CInt(Session(gstrSESS_DL_MEMBER_PAGE)), gstrCMD_DL_PROPERTIES)

                Case gstrCMD_DO_ADD_DL
                    '
                    ' Add a new DL & then show the DL member maintenance screen.
                    '
                    Call AddDL()

                Case gstrCMD_DO_ADD_DL_MEMBER
                    '
                    ' Add DL members.
                    '
                    Call AddDLMembers()

                Case gstrCMD_DO_MOD_DL_OWNER
                    '
                    ' Mod DL owner
                    '
                    Call ModDLOwner()

                Case gstrCMD_FIND_DLS
                    '
                    ' Show the DL maintenance screen using selection criteria.
                    '
                    Call ShowDLMaint(App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)) _
                                        , CInt(Session(gstrSESS_DL_PAGE)))

                Case gstrCMD_FIND_ENTRIES
                    '
                    ' Show the select alias screen w/ selection criteria.
                    '
                    Call ShowSelDN(CStr(Session(gstrSESS_CMD)) _
                                        , App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)) _
                                        , giADS_PAGE_FIRST)

                Case gstrCMD_MOD_DL_OWNER
                    '
                    ' Show the select alias screen to provide for selection of an owner
                    '
                    Call ShowSelDN(gstrCMD_DO_MOD_DL_OWNER, gstrNONE, giADS_PAGE_FIRST)

                Case gstrCMD_SEL_DN_GO_TO_PAGE
                    '
                    ' Show the DN selection w/ a new page of DN's
                    '
                    Call ShowSelDN(CStr(Session(gstrSESS_CMD)) _
                                        , App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)) _
                                        , CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))

                Case gstrCMD_SEL_EXCH_SERVER
                    '
                    ' Show the exchange server selection screen
                    '
%>
                    <SCRIPT Language="JavaScript">
                        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_SEL_EXCH_SERVER%>"
                    </SCRIPT>
<%
            End Select
        End If
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

Private Function bUpdateProperties(pstrCmd)
    Dim bDirtyProperties

    On Error Resume Next

    bUpdateProperties = False
    '
    ' Properties are updated from the properties page when executing following cmds
    '
    Select Case pstrCmd
        Case gstrCMD_DL_MAINT, gstrCMD_ADD_DL_MEMBER, gstrCMD_DEL_DL_MEMBER, gstrCMD_DL_PROPERTIES_GO_TO_PAGE _
                , gstrCMD_MOD_DL_OWNER
            bDirtyProperties = CStr(mfrm(gstrREQUEST_B_DIRTY_PROPERTIES)) 
            '
            ' Determine whether update flag was passed.
            '
            If Len(bDirtyProperties) > 0 Then
                '
                ' Perform update if change was detected
                '
                If CBool(bDirtyProperties) Then
                    '
                    ' Add or Modify DL 
                    '
                    If Len(mfrm(gstrREQUEST_TXT_ALIAS)) > 0 Then
                        bUpdateProperties = bAddDL()
                    Else
                        bUpdateProperties = bModifyDL()
                    End If

                    If Not bUpdateProperties Then
                        '
                        ' If trying to return to DL Maintenance page, determine whether to
                        ' return w/out completing updates.
                        '
                         If pstrCmd = gstrCMD_DL_MAINT Then
%>
                            <SCRIPT Language="JavaScript">
                                if (window.confirm('<%=gstrMSG_CONFIRM_RETURN_DL_MAINT%>')) {
                                    parent.<%=gstrFRAME_MAIN%>.document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_B_DIRTY_PROPERTIES%>.value = <%=CInt(False)%>
                                    parent.SubmitCommand('<%=pstrCmd%>');
                                }
                            </SCRIPT>
<%
                        End If
                    End If
                Else ' No changes to properties
                    bUpdateProperties = True
                End If
            Else ' No updates
                bUpdateProperties = True
            End If
        Case Else ' Not in property page
            bUpdateProperties = True
    End Select

End Function

Private Function bModifyDL()
'
' bModifyDL modifies a DL & returns a boolean to indicate successful completion.
'
    On Error Resume Next

    bModifyDL = False

    ADS_strDispName = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_DISP_NAME)))
    ADS_strNotes = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_NOTES)))

    Call ADS_ModifyDL(CStr(Session(gstrSESS_DL_ADS_PATH)))

    If Err.Number = gerrNONE Then
        Session(gstrSESS_DL_DISP_NAME) = ADS_strDispName

        bModifyDL = True
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_MOD_DL_PROPS, Err.Number, Err.Description)

        Err.Clear

        bModifyDL = False
    End If
End Function

Private Function bAddDL()
'
' AddDL adds a DL & displays the DL Member Maint page.
'
    Dim strDLDispName
    Dim strDLAlias
    Dim strDLADsPath

    On Error Resume Next

    bAddDL = False

    ADS_strOrganization = CStr(Session(gstrSESS_ADS_O_ENTERPRISE))
    ADS_strOrganizationalUnit = CStr(Session(gstrSESS_ADS_OU_SITE))
    ADS_strServer = CStr(Session(gstrSESS_ADS_SERVER))

    ADS_strAlias = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_ALIAS)))
    ADS_strDispName = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_DISP_NAME)))
    ADS_strNotes = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_NOTES)))

    Call ADS_AddDL(strDLADsPath)

    If (Err.Number = gerrNONE) And (ADS_err = gerrNONE) Then
        Call ShowDLProperties(strDLADsPath, giADS_PAGE_FIRST, gstrCMD_DL_PROPERTIES)

        bAddDL = True
    Else
        If ADS_err <> gerrNONE Then
            '
            ' Error was trapped in ADS include
            '
            Select Case ADS_err
                Case gerrADS_DUPLICATE_DL, gerrADS_DUPLICATE_EMAIL_ADDR
                    Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_EXCH_DL & gchSPACE & gchSPACE & ADS_strErr, gerrNONE, gstrNONE)
                Case Else
                    Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_EXCH_DL, ADS_err, ADS_strErr)
            End Select
        ElseIf Err.Number = gerrADS_DUPLICATE_DL Then
            '
            ' The duplicate dl may be detected in the ads object prior to adding the dl or
            ' during the add.  If it's detected during the add, the add fails & an error is
            ' raised so that we get here.
            '
            Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_EXCH_DL & gchSPACE & gchSPACE & gstrADS_MSG_ALERT_DUPLICATE_DL, gerrNONE, gstrNONE)
        Else
            Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_EXCH_DL, Err.Number, Err.Description)
        End If

        bAddDL = False
        Err.Clear
    End If
End Function

Private Sub ShowDLMaintNew()
'
' ShowDLMaintNew validates the Exchange server, sets session variables &
' shows the DL Maint page.
'
    Dim strErr

    ADS_strServer = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_SERVER)))
    ADS_strOrganization = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_ENTERPRISE)))
    ADS_strOrganizationalUnit = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_SITE)))

    On Error Resume Next

    Call ADS_ValidateServer()
    If Err.Number = gerrNONE Then
        Session(gstrSESS_ADS_SERVER) = ADS_strServer
        Session(gstrSESS_ADS_O_ENTERPRISE) = ADS_strOrganization
        Session(gstrSESS_ADS_OU_SITE) = ADS_strOrganizationalUnit

        Call ShowDLMaint(gstrNONE, giADS_PAGE_FIRST)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_ADSI_EXCH_OBJ, Err.Number, Err.Description)

        Err.Clear
    End If
End Sub

Private Sub ShowDLMaint(pstrSelCriteria, piDLPage)
'
' Show the DL Maintenance page.
'
    Session(gstrSESS_DL_PAGE) = piDLPage
    Session(gstrSESS_SEL_CRITERIA_DL) = pstrSelCriteria
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_DL_MAINTENANCE%>"
    </SCRIPT>
<%
End Sub

Private Sub ShowDLProperties(pstrDLADsPath, piPage, pstrCmd)
'
' Show the DL Properties page
'
    Dim strURLParms
    '
    ' Store ADs path in Session object
    '
    Session(gstrSESS_DL_ADS_PATH) = pstrDLADsPath
    Session(gstrSESS_DL_MEMBER_PAGE) = piPage
    Session(gstrSESS_CMD) = pstrCmd
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_DL_PROPERTIES%>"
    </SCRIPT>
<%
End Sub

Private Sub ShowSelDN(pstrCmd, pstrSelCriteria, piPage)
    Session(gstrSESS_CMD) = pstrCmd
    Session(gstrSESS_SEL_CRITERIA) = pstrSelCriteria
    Session(gstrSESS_SEL_DN_PAGE) = piPage
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_SEL_DN%>"
    </SCRIPT>
<%
End Sub

Private Sub AddDLMembers()

    On Error Resume Next

    ADS_rgstrADsPathMembers = App_RgstrFromRequestForm(mfrm(gstrREQUEST_LST_SEL))

    Call ADS_AddDLMembers(CStr(Session(gstrSESS_DL_ADS_PATH)))

    If Err.Number = gerrNONE Then
        Call App_ShowMsg(gstrMSG_ALERT_DL_MEMBERS_ADDED, gerrNONE, gstrNONE)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_ADD_DL_MEMBERS, Err.Number, Err.Description)

        Err.Clear
    End If
End Sub

Private Sub DelDLMember()

    On Error Resume Next

    ADS_rgstrADsPathMembers = App_RgstrFromRequestForm(mfrm(gstrREQUEST_LST_DL_MEMBERS))

    Call ADS_DelDLMembers(CStr(Session(gstrSESS_DL_ADS_PATH)))

    If Err.Number = gerrNONE Then
        Call ShowDLProperties(CStr(Session(gstrSESS_DL_ADS_PATH)) _
                                , CInt(Session(gstrSESS_DL_MEMBER_PAGE)), gstrCMD_DL_PROPERTIES)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_DEL_DL_MEMBERS, Err.Number, Err.Description)

        Err.Clear
    End If
End Sub

Public Sub ModDLOwner()
    On Error Resume Next

    ADS_strServer = CStr(Session(gstrSESS_ADS_SERVER))

    Call ADS_ModDLOwner(App_strFromHTML(CStr(mfrm(gstrREQUEST_LST_SEL))) _
                        , CStr(Session(gstrSESS_DL_ADS_PATH)))

    If Err.Number = gerrNONE Then
        Call ShowDLProperties(CStr(Session(gstrSESS_DL_ADS_PATH)) _
                                , CInt(Session(gstrSESS_DL_MEMBER_PAGE)), gstrCMD_DL_PROPERTIES)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_MOD_DL_OWNER, Err.Number, Err.Description)

        Err.Clear
    End If
End Sub

Public Sub DelDL()
    On Error Resume Next

    Call ADS_DelDL(App_strFromHTML(CStr(mfrm(gstrREQUEST_LST_DL))))

    If Err.Number = gerrNONE Then
        Call ShowDLMaint(CStr(Session(gstrSESS_SEL_CRITERIA_DL)), CInt(Session(gstrSESS_DL_PAGE)))
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_DEL_DL, Err.Number, Err.Description)

        Err.Clear
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
