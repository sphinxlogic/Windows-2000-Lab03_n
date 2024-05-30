<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="CDO.inc"-->
<!--#include file="Rule.inc"-->

<%
'<!--Rules Sample Application-->
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
    Call AuthenticateUser
    '
    ' Process the command
    '
    strCmd = Request(gstrREQUEST_CMD)
    '
    ' On First execution strCmd is empty and no code is executed.
    '
    If Len(strCmd) > 0 Then
        '
        ' Verify cdo session
        '
        Select Case strCmd
            Case gstrCMD_EXCH_LOGON, gstrCMD_SEL_FOLDER_NEW
                '
                ' Don't Check session when logging on
                '
            Case Else
                Call App_CheckSession
        End Select

        Set mfrm = Request.Form
		
        Select Case strCmd
            Case gstrCMD_ADD_RULE
                Call ShowRulePropertiesNew(strCmd, giruleNONE)
            Case gstrCMD_ADD_SEL_ADDRESSES
                Call AddSelAddresses
            Case gstrCMD_UPD_RULE
                Call UpdateRule
            Case gstrCMD_COMMIT
                Call CommitRuleChanges
            Case gstrCMD_DEL_RULE
                Call DelRule(CLng(mfrm(gstrREQUEST_HID_I_RULE)))
            Case gstrCMD_EXCH_LOGON
                Call ShowExchLogon
            Case gstrCMD_EXPAND_FOLDER
                Call AddToBranch(App_strFromHTML(CStr(mfrm(gstrREQUEST_HID_STR_FOLDER_ID))) _
                                    , App_strFromHTML(CStr(mfrm(gstrREQUEST_HID_STR_FOLDER_NAME))))
            Case gstrCMD_FIND_ADDRESSES
                Call ShowSelAddresses(App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)), CDO_iPAGE_FIRST)
            Case gstrCMD_GO_TO_BRANCH_LEVEL
                Call GoToBranchLevel(CInt(mfrm(gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL)))
            Case gstrCMD_MOD_RULE
                Call ShowRulePropertiesNew(strCmd, CLng(mfrm(gstrREQUEST_HID_I_RULE)))
            Case gstrCMD_RULES_MAINT_NEW
                Call ShowRuleMaintenanceNew
            Case gstrCMD_RULES_MAINT
                Call ShowRuleMaintenance
            Case gstrCMD_RULE_PROPERTIES
                Call ShowRuleProperties
            Case gstrCMD_SEL_ADDRESSES_GO_TO_PAGE
                Call ShowSelAddresses(App_strFromHTML(mfrm(gstrREQUEST_TXT_SEL_CRITERIA)), CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))
            Case gstrCMD_SEL_FOLDER
                Call ShowSelFolder
            Case gstrCMD_SEL_FOLDER_GO_TO_PAGE
                Call ShowSelFolderGoToPage(CInt(mfrm(gstrHIDDEN_I_PAGE_GO_TO)))
            Case gstrCMD_SEL_FOLDER_NEW
                Call Logon
            Case gstrCMD_SEL_ADDRESSES_FORWARD_TO, gstrCMD_SEL_ADDRESSES_FROM, gstrCMD_SEL_ADDRESSES_SENT_TO
                Call ShowSelAddressesNew(strCmd)
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
      Response.Buffer = True
      Response.Status = ("401 Unauthorized")
      Response.End
    End If
End Sub

Private Sub Logon()
'
' Logon creates a cdo session & shows the folder selection page.
'
    Dim errNo
    Dim strErr

    On Error Resume Next
	
    Call CDO_Logon(CStr(mfrm(gstrREQUEST_TXT_EXCH_SERVER)), CStr(mfrm(gstrREQUEST_TXT_MAILBOX)))

    If Err.Number = gerrNONE And CDO_err = gerrNONE Then
        '
        ' Initialize folder arrays
        '
        Call InitFolderArrays

        Call ShowSelFolder
    Else
        If Err.Number <> gerrNONE Then
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

    Call ShowSelFolder
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
    Session(gstrSESS_RG_BRANCH_FOLDER_PAGE) = rgstrBranchFolderPage

    Call ShowSelFolder
End Sub

Private Sub ShowSelAddressesNew(pstrCmd)
    '
    ' Save properties that have changed
    '
    If bSetProperties() Then
        Session(gstrSESS_CMD_SEL_ADDRESS) = pstrCmd

        Call ShowSelAddresses(gstrNONE, CDO_iPAGE_FIRST)
    End If

End Sub

Private Function bSetProperties()
    
    On Error Resume Next
    '
    ' Condition Properties
    '
    Rule_Cond_rgaeFrom = Split(CStr(mfrm(gstrREQUEST_HID_RG_ADDRESS_ID_FROM)), gchCOMMA)
    Rule_Cond_rgaeTo = Split(CStr(mfrm(gstrREQUEST_HID_RG_ADDRESS_ID_SENT_TO)), gchCOMMA)
    Rule_Cond_bSentTo = CBool(mfrm(gstrREQUEST_CHK_COND_SENT_TO))
    Rule_Cond_bCopiedTo = CBool(mfrm(gstrREQUEST_CHK_COND_COPIED_TO))
    Rule_Cond_strSubject = App_strFromHTML(mfrm(gstrREQUEST_TXT_COND_SUBJECT))
    Rule_Cond_strMsgBody = App_strFromHTML(mfrm(gstrREQUEST_TXT_COND_MSG_BODY))
    '
    ' Action Properties
    '
    Rule_Act_bSkipSubsequentRules = CBool(mfrm(gstrREQUEST_CHK_ACT_SKIP_RULES))
    Rule_Act_bReturn = CBool(mfrm(gstrREQUEST_CHK_ACT_RETURN))
    Rule_Act_bDelete = CBool(mfrm(gstrREQUEST_CHK_ACT_DELETE))
    Rule_Act_rgaeForward = Split(CStr(mfrm(gstrREQUEST_HID_RG_ADDRESS_ID_FORWARD)))

    Call Rule_SetProperties

    If Err.Number = gerrNONE Then
        bSetProperties = True
    Else
        bSetProperties = False

        Call App_ShowMsg(gstrMSG_ALERT_CANT_SET_RULE_PROPERTIES, Err.Number, Err.Description)
    End If

End Function

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

Private Sub AddSelAddresses()
'
' AddSelAddresses adds addresses to recipient condition, sender condition, or forward action.
'
    Dim strErr
    Dim rgstrAddressID

    On Error Resume Next
    '
    ' Get addresses
    '
    rgstrAddressID = App_RgstrFromRequestForm(mfrm(gstrREQUEST_LST_SEL))
    '
    ' Establish error messages & add the addresses
    '
    Select Case CStr(Session(gstrSESS_CMD_SEL_ADDRESS))
        Case gstrCMD_SEL_ADDRESSES_FORWARD_TO
            strErr = gstrMSG_ALERT_CANT_ADD_FORWARD_TO_ADDRESS
            Call Rule_Act_AddForwardToAddress(rgstrAddressID)

        Case gstrCMD_SEL_ADDRESSES_FROM
            strErr = gstrMSG_ALERT_CANT_ADD_FROM_ADDRESS
            Call Rule_Cond_AddFromAddress(rgstrAddressID)

        Case Else ' gstrCMD_SEL_ADDRESSES_SENT_TO
            strErr = gstrMSG_ALERT_CANT_ADD_SENT_TO_ADDRESS
            Call Rule_Cond_AddSentToAddress(rgstrAddressID)

    End Select

    If Err.Number = gerrNONE Then
        Call App_ShowMsg(gstrMSG_ALERT_SEL_ADD_CONFIRMED, gerrNONE, gstrNONE)
    Else
        Call App_ShowMsg(strErr, Err.Number, Err.Description)
    End If
End Sub

Private Sub ShowSelFolderGoToPage(piPage)
'
' ShowSelFolderGoToPage updates the folder page & shows the sel folder screen.
'
    Dim rgstrBranchFolderPage

    rgstrBranchFolderPage = Session(gstrSESS_RG_BRANCH_FOLDER_PAGE)

    rgstrBranchFolderPage(UBound(rgstrBranchFolderPage)) = piPage

    Session(gstrSESS_RG_BRANCH_FOLDER_PAGE) = rgstrBranchFolderPage

    Call ShowSelFolder
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
                
Private Sub ShowRuleMaintenanceNew()
'
' ShowRuleMaintenanceNew sets session properties before showing the rule maintenance screen.
'
    Dim strFolderID

    On Error Resume Next

    Session(gstrSESS_FOLDER_NAME) = mfrm(gstrREQUEST_HID_STR_FOLDER_NAME)
    strFolderID = mfrm(gstrREQUEST_HID_STR_FOLDER_ID)

    Call Rule_Col_Initialize(strFolderID)

    If Err.Number = gerrNONE Then
        Session(gstrSESS_FOLDER_ID) = strFolderID

        Call ShowRuleMaintenance
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_CREATE_RULES_OBJECT, Err.Number, Err.Description)
    End If
End Sub

Private Sub ShowRuleMaintenance()
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_RULE_MAINTENANCE%>"
    </SCRIPT>
<%
End Sub

Private Sub DelRule(piRule)

    On Error Resume Next

    If bSetRuleSequence(piRule) Then

        Call Rule_Delete(piRule)

        If Err.Number = gerrNONE Then
            Call ShowRuleMaintenance
        Else
            Call App_ShowMsg(gstrMSG_ALERT_CANT_DEL_RULE, Err.Number, Err.Description)
        End If
    End If
End Sub

Private Sub UpdateRule()
    Dim bAdd

    On Error Resume Next
    '
    ' Save properties that have changed
    '
    If bSetProperties() Then
        bAdd = (Session(gstrSESS_CMD) = gstrCMD_ADD_RULE)

        If bAdd Then
            Call Rule_Add
        Else
            Call Rule_Modify(CLng(Session(gstrSESS_I_RULE)))
        End If

        If Err.Number = gerrNONE Then
            If bAdd Then
                Call App_ShowMsg(gstrMSG_ALERT_ADD_CONFIRMED, gerrNONE, gstrNONE)
            Else
                Call App_ShowMsg(gstrMSG_ALERT_MOD_CONFIRMED, gerrNONE, gstrNONE)
            End If

            Call ShowRuleMaintenance
        Else
            If bAdd Then
                Call App_ShowMsg(gstrMSG_ALERT_CANT_ADD_RULE, Err.Number, Err.Description)
            Else
                Call App_ShowMsg(gstrMSG_ALERT_CANT_MOD_RULE, Err.Number, Err.Description)
            End If
        End If
    End If
End Sub

Private Sub CommitRuleChanges()
'
' CommitRuleChanges commits changes made to the Rules.
'

    On Error Resume Next

    If bSetRuleSequence(giruleNONE) Then
        Call Rule_Update

        If Err.Number = gerrNONE Then
            Call App_ShowMsg(gstrMSG_ALERT_UPD_CONFIRMED, gerrNONE, gstrNONE)

            Call ShowSelFolder
        Else
            Call App_ShowMsg(gstrMSG_ALERT_CANT_UPD, Err.Number, Err.Description)
        End If
    End If
End Sub

Private Sub ShowRulePropertiesNew(pstrCmd, piRule)
'
' ShowRulePropertiesNew stores the current cmd in a session property before showing properties.
'
    Dim strErr

    On Error Resume Next

    If bSetRuleSequence(piRule) Then
        Call Rule_Get(piRule)

        If Err.Number = gerrNONE Then
            Session(gstrSESS_CMD) = pstrCmd
            Session(gstrSESS_I_RULE) = piRule

            Call ShowRuleProperties
        Else
            If pstrCmd = gstrCMD_ADD_RULE Then
                strErr = gstrMSG_ALERT_CANT_CREATE_RULE_OBJECT
            Else
                strErr = gstrMSG_ALERT_CANT_GET_RULE_OBJECT
            End If

            Call App_ShowMsg(strErr, Err.Number, Err.Description)
        End If
    End If
End Sub

Private Sub ShowRuleProperties()
%>
    <SCRIPT Language="JavaScript">
        parent.<%=gstrFRAME_MAIN%>.location="<%=gstrASP_RULE_PROPERTIES%>"
    </SCRIPT>
<%
End Sub

Private Function bSetRuleSequence(piRule)
'
' bSetRuleSequence retrieves an array of rule indices, sets the rule sequence accordingly,
' and returns a boolean indicating successful completion.  If piRule <> giruleNONE,
' bSetRuleSequence updates piRule to indicate the new index of the rule after the reorder.
'
    Dim strRgiRule
    Dim rgiRule

    On Error Resume Next
    '
    ' Retrieve comma delimited list of rules indices
    '
    strRgiRule = CStr(mfrm(gstrREQUEST_HID_RG_I_RULE))

    If Len(strRgiRule) > 0 Then
        rgiRule = Split(strRgiRule, gchCOMMA)
        '
        ' Set new indices & keep track of index of piRule
        '
        Call Rule_SetNewIndex(rgiRule, piRule)

        If Err.Number = gerrNONE Then
            bSetRuleSequence = True
        Else
            Call App_ShowMsg(gstrMSG_ALERT_CANT_REORDER_RULES, Err.Number, Err.Description)

            bSetRuleSequence = False
        End If
    Else    ' No rules to sequence
        bSetRuleSequence = True
    End If

End Function
%>
<HTML>
<HEAD>
<TITLE></TITLE>
</HEAD>
<BODY>
</BODY>
</HTML>
