<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ADS.inc"-->
<%
'<!--Mailbox Maintenance Sample Application-->
'<!--mbMaintenance.asp : Mailbox Maintenance asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' mbMaintenance.asp lists mailboxes & custom recipients meeting search criteria & provides for
' adding, modifying, & deleting.
'
    Dim strCtlFocus
    Dim mstrSelCriteria

    On Error Resume Next

    Call App_CheckSession()

    strCtlFocus = gstrREQUEST_TXT_SEL_CRITERIA
    mstrSelCriteria = CStr(Session(gstrSESS_SEL_CRITERIA_RECIPIENT))

    Call App_RenderPage(gstrNONE, gstrPAGE_HEADING_MB_MAINT, strCtlFocus)
    
    If UBound(ADS_rgstrADsPath) < 0 And Len(mstrSelCriteria) > 0 Then
        Call App_ShowMsg(Replace(gstrMSG_ALERT_NONE_ON_FILE, gchREPLACE, gstrMSG_REPLACE_MATCHING_RECIPIENTS), gerrNONE, gstrNONE)
    End If

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdMod:  Validates modify command.
    '
    ' bValidCmdDel:  Validates delete command.
    '
    ' bSelected:  Returns true if a recipient was selected;  false otherwise.
%>
    <SCRIPT LANGUAGE="JavaScript">
        function ValidateCmd(pstrCmd) {
            var bValidCmd;

            if (pstrCmd == '<%=gstrCMD_FIND_RECIPIENTS%>') {
                bValidCmd = parent.bValidCmdFind(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SEL_CRITERIA%>);
            }
            else if (pstrCmd == '<%=gstrCMD_PROPERTIES%>') {
                bValidCmd = bValidCmdMod(pstrCmd);
            }
            else if (pstrCmd == '<%=gstrCMD_DEL_RECIPIENTS%>') {
                bValidCmd = bValidCmdDel(pstrCmd);
            }
            else if (pstrCmd == '<%=gstrCMD_MAINTENANCE_GO_TO_PAGE%>') {
                bValidCmd = parent.bValidCmdGoToPage();
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidCmdMod(pstrCmd) {
            if (bSelected(pstrCmd)) {
                return true;    
            }
            else {
                return false;
            }
        }

        function bValidCmdDel(pstrCmd) {
            if (bSelected(pstrCmd)) {  
                if (confirm('<%=gstrMSG_CONFIRM_DEL_RECIPIENTS%>')) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }  
        }

        function bSelected(pstrCmd) {
            var iLST_SEL_NONE = -1;
            var frm = document.<%=gstrFORM_MAIN%>;
            var lstRecipient = frm.<%=gstrREQUEST_LST_RECIPIENTS%>;
            
            if (lstRecipient.length == 0) {
                parent.ShowError('<%=gstrMSG_ALERT_FIND_RECIPIENTS_FOR_MAINT%>',
                    frm.<%=gstrREQUEST_TXT_SEL_CRITERIA%>);
                return false;
            }
            else if (lstRecipient.selectedIndex == iLST_SEL_NONE) {
                parent.ShowError(
                    parent.strMsgReplace('<%=gstrMSG_ALERT_MUST_SEL_RECIPIENT%>', 
                        new Array((pstrCmd == '<%=gstrCMD_DEL_RECIPIENTS%>') ? 
                            '<%=gstrMSG_REPLACE_DEL%>' : '<%=gstrMSG_REPLACE_MOD%>')),
                    lstRecipient);
                return false;
            }
            else {
                return true;
            }
        }

    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()
    Dim strError
    Dim strErrDesc
    Dim errNumber

    On Error Resume Next
    '
    ' Set server fields
    '
    ADS_strServer = CStr(Session(gstrSESS_ADS_SERVER))
    ADS_strOrganization = CStr(Session(gstrSESS_ADS_O_ENTERPRISE))
    ADS_strOrganizationalUnit = CStr(Session(gstrSESS_ADS_OU_SITE))
%>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Enterprise:</TD>
            <TD><%=App_strHTML(ADS_strOrganization)%></TD>
        </TR>
        <TR>
            <TD>Site:</TD>
            <TD><%=App_strHTML(ADS_strOrganizationalUnit)%></TD>
        </TR>
        <TR>
            <TD>Server:</TD>
            <TD><%=App_strHTML(ADS_strServer)%></TD>
        </TR>
    </TABLE><BR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>Display recipients that have the following characters:</DIV>
    <INPUT TYPE="text" NAME=<%=gstrREQUEST_TXT_SEL_CRITERIA%> SIZE=40 MAXLENGTH=40 VALUE='<%=App_strHTML(mstrSelCriteria)%>'  OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SEL_CRITERIA%>)">
    <Input Type=Button Name=cmdFind AccessKey="F" Value="    Find    " OnClick="ValidateCmd('<%=gstrCMD_FIND_RECIPIENTS%>')"><BR><BR>
<%
    If Len(mstrSelCriteria) > 0 Then
        Call ADS_GetRecipients(mstrSelCriteria, CInt(Session(gstrSESS_RECIPIENT_PAGE)))
    End If

    If Err.Number = gerrNONE Then
        Call ShowRecipients()
    Else
        strError = gstrMSG_ALERT_CANT_DISPLAY_RECIPIENTS
        errNumber = Err.Number
        strErrDesc = Err.Description

        Err.Clear
    End If
%>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><A HRef=javascript:ValidateCmd('<%=gstrCMD_SEL_EXCH_SERVER%>')>Return to Microsoft Exchange Server Selection</A></DIV>
<%
    If App_bSupportsIE4DHTML() Then
        '
        ' Use DHTML to size the lst.
        '
%>
        <Script>
            var frm = document.<%=gstrFORM_MAIN%>;

            parent.SetWidth(frm.<%=gstrREQUEST_TXT_SEL_CRITERIA%>, <%=gpxlWIDTH_LST%>)
            parent.SetWidth(frm.<%=gstrREQUEST_LST_RECIPIENTS%>, <%=gpxlWIDTH_LST%>)
        </Script>
<%
    End If
    '
    ' Display a msg if an error was detected
    '
    If Len(strError) > 0 Then
        Call App_ShowMsg(strError, errNumber, strErrDesc)
    End If
End Sub

Private Sub ShowRecipients()
    Const strSTYLE_CMD = "width:105px"

    Dim iADsPath
    '
    ' Save the current page.
    '
    Session(gstrSESS_RECIPIENT_PAGE) = ADS_iPage
%>
    <Font CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>Recipients:</Font>&nbsp;&nbsp;
<%
    '
    ' Display paging controls only if there are multiple pages
    '
    If ADS_cPage > 1 Then
        Call App_RenderPaging(gstrCMD_MAINTENANCE_GO_TO_PAGE, ADS_iPage, ADS_cPage _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_PREV, gstrMSG_REPLACE_RECIPIENTS)) _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_NEXT, gstrMSG_REPLACE_RECIPIENTS)))
    End If
%>
    <TABLE>
        <TR>
            <TD RowSpan=5>
                <SELECT NAME=<%=gstrREQUEST_LST_RECIPIENTS%> SIZE=10>
<%
            For iADsPath = LBound(ADS_rgstrADsPath) To UBound(ADS_rgstrADsPath)
%>
                <OPTION Value='<%=App_strHTML(ADS_rgstrADsPath(iADsPath))%>'><%=App_strHTML(ADS_rgstrDispName(iADsPath))%>
<%
            Next
%>
                </SELECT>
            </TD>
            <TD Align=Left VAlign=Bottom>
                <Input Type=Button Name=cmdAdd AccessKey="A" Value="Add Mailbox..." OnClick="ValidateCmd('<%=gstrCMD_ADD_MB%>')" Style="<%=strSTYLE_CMD%>">
            </TD>
        </TR>
        <TR>
            <TD Align=Left>
                <Input Type=Button Name=cmdAdd AccessKey="C" Value="Add Custom..." OnClick="ValidateCmd('<%=gstrCMD_ADD_CR%>')" Style="<%=strSTYLE_CMD%>">
            </TD>
        </TR>
        <TR>
            <TD Align=Left>
                <Input Type=Button Name=cmdModify AccessKey="M" Value="Modify..." OnClick="ValidateCmd('<%=gstrCMD_PROPERTIES%>')" Style="<%=strSTYLE_CMD%>">
            </TD>
        </TR>
        <TR>
            <TD Align=Left VAlign=Top>
                <Input Type=Button Name=cmdDelete AccessKey="D" Value=" Delete  " OnClick="ValidateCmd('<%=gstrCMD_DEL_RECIPIENTS%>')" Style="<%=strSTYLE_CMD%>">
            </TD>
        </TR>
    </TABLE><BR>
<%
End Sub
%>
