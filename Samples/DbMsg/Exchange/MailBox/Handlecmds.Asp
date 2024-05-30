<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ADS.inc"-->
<%
'<!--Mailbox Maintenance Sample Application-->
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
            Case gstrCMD_SEL_EXCH_SERVER, gstrCMD_MAINTENANCE_NEW
                '
                ' Don't Check session when logging on
                '
            Case Else
                Call App_CheckSession()
        End Select

        Set mfrm = Request.Form

        Select Case strCmd
            Case gstrCMD_ADD_MB, gstrCMD_ADD_CR
                '
                ' Show the properties screen.
                '
                Call ShowProperties(gstrNONE, strCmd)

            Case gstrCMD_DEL_RECIPIENTS
                '
                ' Delete the selected mailbox/custom recipient
                '
                Call DeleteRecipient()

            Case gstrCMD_DO_ADD
                '
                ' Perform Add
                '
                 Call AddRecipient()

            Case gstrCMD_DO_MOD
                '
                ' Perform Modify
                '
                 Call ModifyRecipient()

            Case gstrCMD_FIND_RECIPIENTS
                '
                ' Show the maintenance screen using selection criteria.
                '
                Call ShowMaint(App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)) _
                                    , CInt(Session(gstrSESS_RECIPIENT_PAGE)))

            Case gstrCMD_MAINTENANCE
                '
                ' Show the maintenance screen.
                '
                Call ShowMaint(CStr(Session(gstrSESS_SEL_CRITERIA_RECIPIENT)) _
                                    , CInt(Session(gstrSESS_RECIPIENT_PAGE)))

            Case gstrCMD_MAINTENANCE_GO_TO_PAGE
                '
                ' Show the maintenance screen w/ a new page of recipients.
                '
                Call ShowMaint(CStr(Session(gstrSESS_SEL_CRITERIA_RECIPIENT)) _
                                    , CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))

            Case gstrCMD_MAINTENANCE_NEW
                '
                ' Show the maintenance screen for the first time after selecting an 
                ' Exchange server.
                '
                Call ShowMaintNew()

            Case gstrCMD_PROPERTIES
                '
                ' Show the properties screen after selecting a mailbox/custom recipient
                ' & pressing modify in the maintenance screen.
                '
                Call ShowProperties(App_strFromHTML(CStr(mfrm(gstrREQUEST_LST_RECIPIENTS))) _
                                        , gstrCMD_PROPERTIES)

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

Private Sub ShowMaintNew()
'
' ShowMaintNew validates the Exchange server, sets session variables &
' shows the MB Maint page.
'
    Dim strErr
    '
    ' Set server fields
    '
    ADS_strServer = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_SERVER)))
    ADS_strOrganization = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_ENTERPRISE)))
    ADS_strOrganizationalUnit = App_strFromHTML(CStr(mfrm(gstrREQUEST_TXT_SITE)))

    On Error Resume Next

    Call ADS_ValidateServer()

    If Err.Number = gerrNONE Then
        Session(gstrSESS_ADS_SERVER) = ADS_strServer
        Session(gstrSESS_ADS_O_ENTERPRISE) = ADS_strOrganization
        Session(gstrSESS_ADS_OU_SITE) = ADS_strOrganizationalUnit

        Call ShowMaint(gstrNONE, giADS_PAGE_FIRST)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_ADSI_EXCH_OBJ, Err.Number, Err.Description)

        Err.Clear
    End If
End Sub

Private Sub ShowMaint(pstrSelCriteria, piPage)
'
' Show the Maintenance page.
'
    Session(gstrSESS_RECIPIENT_PAGE) = piPage
    Session(gstrSESS_SEL_CRITERIA_RECIPIENT) = pstrSelCriteria
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_MAINTENANCE%>"
    </SCRIPT>
<%
End Sub

Private Sub ShowProperties(pstrADsPath, pstrCmd)
'
' Show the Properties page
'
    Dim strURLParms
    '
    ' Store ADs path, mailbox boolean, & cmd in Session object
    '
    Session(gstrSESS_ADS_PATH) = pstrADsPath
    Session(gstrSESS_B_IS_MAILBOX) = (pstrCmd = gstrCMD_ADD_MB)
    Session(gstrSESS_CMD) = pstrCmd
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_PROPERTIES%>"
    </SCRIPT>
<%
End Sub

Public Sub AddRecipient()
    Dim bIsMailbox
    Dim strMsg
    Dim errNo
    Dim strErr
    '
    ' Determine whether mailbox or custom recipient
    '
    bIsMailbox = CBool(Session(gstrSESS_B_IS_MAILBOX))
    '
    ' Set server fields
    '
    ADS_strServer = CStr(Session(gstrSESS_ADS_SERVER))
    ADS_strOrganization = CStr(Session(gstrSESS_ADS_O_ENTERPRISE))
    ADS_strOrganizationalUnit = CStr(Session(gstrSESS_ADS_OU_SITE))
    '
    ' Set data fields
    '
    Call PrepUpdate(bIsMailbox)
    '
    ' Add recipient
    '
    On Error Resume Next

    Call ADS_ADD()

    If Err.Number = gerrNONE And ADS_err = gerrNONE Then
        If bIsMailBox Then
            strMsg = gstrMSG_ALERT_ADD_MB_CONFIRMED
        Else
            strMsg = gstrMSG_ALERT_ADD_CR_CONFIRMED
        End If

        Call App_ShowMsg(strMsg, gerrNONE, gstrNONE)

        Call ShowMaint(CStr(Session(gstrSESS_SEL_CRITERIA_RECIPIENT)), CInt(Session(gstrSESS_RECIPIENT_PAGE)))
    Else
        If bIsMailBox Then
            strMsg = gstrMSG_ALERT_CANT_ADD_MB
        Else
            strMsg = gstrMSG_ALERT_CANT_ADD_CR
        End If

        If ADS_err = gerrNONE Then
            errNo = Err.Number
            strErr = Err.Description
        Else
            strMsg = ADS_strErr

            errNo = gerrNONE
            strErr = gstrNONE
        End If

        Call App_ShowMsg(strMsg, errNo, strErr)

        Err.Clear
    End If
End Sub

Public Sub ModifyRecipient()
    Dim bIsMailbox
    Dim strMsg
    Dim errNo
    Dim strErr
    '
    ' Determine whether mailbox or custom recipient
    '
    bIsMailbox = CBool(Session(gstrSESS_B_IS_MAILBOX))
    '
    ' Prepare data fields
    '
    Call PrepUpdate(bIsMailbox)
    '
    ' Modify recipient
    '
    On Error Resume Next

    Call ADS_Modify(CStr(Session(gstrSESS_ADS_PATH)))

    If Err.Number = gerrNONE And ADS_err = gerrNONE Then
        If bIsMailBox Then
            strMsg = gstrMSG_ALERT_MOD_MB_CONFIRMED
        Else
            strMsg = gstrMSG_ALERT_MOD_CR_CONFIRMED
        End If

        Call App_ShowMsg(strMsg, gerrNONE, gstrNONE)

        Call ShowMaint(CStr(Session(gstrSESS_SEL_CRITERIA_RECIPIENT)), CInt(Session(gstrSESS_RECIPIENT_PAGE)))
    Else
        If bIsMailBox Then
            strMsg = gstrMSG_ALERT_CANT_MOD_MB
        Else
            strMsg = gstrMSG_ALERT_CANT_MOD_CR
        End If

        If ADS_err = gerrNONE Then
            errNo = Err.Number
            strErr = Err.Description
        Else
            strMsg = ADS_strErr

            errNo = gerrNONE
            strErr = gstrNONE
        End If

        Call App_ShowMsg(strMsg, errNo, strErr)

        Err.Clear
    End If
End Sub

Public Sub DeleteRecipient()
    On Error Resume Next

    Call ADS_Delete(App_strFromHTML(CStr(mfrm(gstrREQUEST_LST_RECIPIENTS))))

    If Err.Number = gerrNONE Then
        Call ShowMaint(CStr(Session(gstrSESS_SEL_CRITERIA_RECIPIENT)), CInt(Session(gstrSESS_RECIPIENT_PAGE)))
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_DEL, Err.Number, Err.Description)

        Err.Clear
    End If
End Sub

Public Sub PrepUpdate(pbIsMailbox)
'
' PrepUpdate moves data from the Request object to the ADS object in preparation for an update.
'
    Dim strNTAcct
    Dim strNTAcctOld
    
    If pbIsMailbox Then
        ADS_strObjClass = gstrADS_CLASS_MB
        '
        ' Determine whether NTAcct changed
        '
        strNTAcct = App_strFromHTML(mfrm(gstrREQUEST_TXT_NT_ACCT))
        strNTAcctOld = App_strFromHTML(mfrm(gstrREQUEST_HID_NT_ACCT))

        If strNTAcct <> strNTAcctOld Then
            ADS_strNTAcct = strNTAcct
            '
            ' For new accounts, get password
            '
            If CStr(mfrm(gstrREQUEST_OPT_NT_ACCT)) = gstrREQUEST_OPT_NT_ACCT_NEW Then
                ADS_bAddNTAcct = True

                ADS_strNTPassword = App_strFromHTML(mfrm(gstrREQUEST_TXT_NT_PASSWORD))
            Else
                ADS_bAddNTAcct = False
            End If
        Else ' No change.  Assign empty string.  ADS.inc will skip updates.
            ADS_strNTAcct = gstrNONE
            ADS_strNTPassword = gstrNONE
        End If
    Else
        ADS_strObjClass = gstrADS_CLASS_CR_INTERNET
        ADS_strEmailAddr = App_strFromHTML(mfrm(gstrREQUEST_TXT_EMAIL_ADDRESS))
    End If

    ADS_strAlias = App_strFromHTML(mfrm(gstrREQUEST_TXT_ALIAS))
    ADS_strAssistant = App_strFromHTML(mfrm(gstrREQUEST_TXT_ASSISTANT))
    ADS_strCity = App_strFromHTML(mfrm(gstrREQUEST_TXT_CITY))
    ADS_strCompany = App_strFromHTML(mfrm(gstrREQUEST_TXT_COMPANY))
    ADS_strCountry = App_strFromHTML(mfrm(gstrREQUEST_TXT_COUNTRY))
    ADS_strDept = App_strFromHTML(mfrm(gstrREQUEST_TXT_DEPT))
    ADS_strDispName = App_strFromHTML(mfrm(gstrREQUEST_TXT_DISP_NAME))

    ADS_strNameFirst = App_strFromHTML(mfrm(gstrREQUEST_TXT_NAME_FIRST))
    ADS_strNameLast = App_strFromHTML(mfrm(gstrREQUEST_TXT_NAME_LAST))
    ADS_strNameMidInitial = App_strFromHTML(mfrm(gstrREQUEST_TXT_NAME_MID_INITIAL))
    ADS_strNotes = App_strFromHTML(mfrm(gstrREQUEST_TXT_NOTES))

    ADS_strOffice = App_strFromHTML(mfrm(gstrREQUEST_TXT_OFFICE))
    ADS_strPhoneAssistant = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_ASSISTANT))
    ADS_strPhoneBus = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_BUS))
    ADS_strPhone2Bus = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_2_BUS))
    ADS_strPhoneFax = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_FAX))
    ADS_strPhoneHome = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_HOME))
    ADS_strPhone2Home = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_2_HOME))
    ADS_strPhoneMobile = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_MOBILE))
    ADS_strPhonePager = App_strFromHTML(mfrm(gstrREQUEST_TXT_PHONE_PAGER))
    ADS_strPostalAddress = App_strFromHTML(mfrm(gstrREQUEST_TXT_POSTAL_ADDRESS))
    ADS_strPostalCode = App_strFromHTML(mfrm(gstrREQUEST_TXT_POSTAL_CODE))
    ADS_strState = App_strFromHTML(mfrm(gstrREQUEST_TXT_STATE))
    ADS_strTitle = App_strFromHTML(mfrm(gstrREQUEST_TXT_TITLE))
End Sub
%>
<HTML>
<HEAD>
<TITLE></TITLE>
</HEAD>
<BODY>
</BODY>
</HTML>
