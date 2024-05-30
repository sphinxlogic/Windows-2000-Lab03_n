<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ADS.inc"-->
<%
'<!--Distribution List Maintenance Sample Application-->
'<!--SelDN.asp : Select Distinguished Name asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' SelDN.asp provides UI for selecting & adding dl members.
'
    Dim strCtlFocus
    Dim strHeading
    Dim mstrCmd
    Dim mbAddDLMember
    Dim mstrSelCriteria

    On Error Resume Next

    Call App_CheckSession()

    mstrCmd = Session(gstrSESS_CMD)
    mbAddDLMember = (mstrCmd = gstrCMD_DO_ADD_DL_MEMBER)
    mstrSelCriteria = CStr(Session(gstrSESS_SEL_CRITERIA))

    If mbAddDLMember Then
        strHeading = gstrPAGE_HEADING_DL_MEMBER_ADD
    Else
        strHeading = gstrPAGE_HEADING_DL_OWNER_MOD
    End If

    strCtlFocus = gstrREQUEST_TXT_SEL_CRITERIA

    Call App_RenderPage(gstrNONE, strHeading, strCtlFocus)
    '
    ' When selection criteria was entered but no records found, display a msg.
    '
    If UBound(ADS_rgstrADsPathSel) < 0 And len(mstrSelCriteria) > 0 Then
        Call App_ShowMsg(Replace(gstrMSG_ALERT_NONE_ON_FILE, gchREPLACE, gstrMSG_REPLACE_MATCHING_ITEMS), gerrNONE, gstrNONE)
    End If

Public Sub Page_RenderJavaScript()
    Dim strMsgFind
    Dim strMsgSel
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdAdd:  Validates the add command.
    '
    ' bSelection:  Returns true is an entry is selected from the list.
%>
    <SCRIPT LANGUAGE="JavaScript">

        function ValidateCmd(pstrCmd) {
            var bValidCmd;

            if (pstrCmd == '<%=mstrCmd%>') {
                bValidCmd = bValidCmdAdd();
            }
            else if (pstrCmd == '<%=gstrCMD_FIND_ENTRIES%>') {
                bValidCmd = parent.bValidCmdFind(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SEL_CRITERIA%>);
            }
            else if (pstrCmd == '<%=gstrCMD_SEL_DN_GO_TO_PAGE%>') {
                bValidCmd = parent.bValidCmdGoToPage();
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidCmdAdd() {
            return bSelection(); 
        }

        function bSelection(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>;
            var lst = frm.<%=gstrREQUEST_LST_SEL%>;
            var iLST_SEL_NONE = -1;
<%
    '
    ' Create error msgs for finding entries & for selecting entries.
    '
    If mbAddDLMember Then
        strMsgFind = Replace(gstrMSG_ALERT_FIND_ITEMS, gchREPLACE, gstrMSG_REPLACE_DL_MEMBERS_FOR_ADD)
        strMsgSel = "parent.strMsgReplace('" & gstrMSG_ALERT_MUST_SEL_DL_MEMBER & "', new Array('" & gstrMSG_REPLACE_ADD & "'))"
    Else
        strMsgFind = Replace(gstrMSG_ALERT_FIND_ITEMS, gchREPLACE, gstrMSG_REPLACE_DL_OWNER_FOR_SEL)
        strMsgSel = "'" & gstrMSG_ALERT_MUST_SEL_DL_OWNER & "'"
    End If
%>
            
            if (lst.length == 0) {
                parent.ShowError('<%=strMsgFind%>', frm.<%=gstrREQUEST_TXT_SEL_CRITERIA%>);
                return false;
            }
            else if (lst.selectedIndex == iLST_SEL_NONE) {
                parent.ShowError(<%=strMsgSel%>, lst);
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
    Dim bIncludeDLs

    On Error Resume Next

    '
    ' Include DL's if selecting to add members; don't when selecting for the DL owner
    '
    bIncludeDLs = mbAddDLMember
%>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Display Name:</TD>
            <TD><%=App_strHTML(Session(gstrSESS_DL_DISP_NAME))%></TD>
        </TR>
        <TR>
            <TD>Alias:</TD>
            <TD><%=App_strHTML(Session(gstrSESS_DL_ALIAS))%></TD>
        </TR>
    </TABLE><BR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>Display entries starting with the following characters:</DIV>
    <INPUT TYPE="text" NAME=<%=gstrREQUEST_TXT_SEL_CRITERIA%> SIZE=40 MAXLENGTH=40 VALUE='<%=App_strHTML(mstrSelCriteria)%>'  OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SEL_CRITERIA%>)">
    <Input Type=Button Name=cmdFind AccessKey="F" Value="Find" OnClick="ValidateCmd('<%=gstrCMD_FIND_ENTRIES%>')"><BR><BR>
<%
    If len(mstrSelCriteria) > 0 Then
        ADS_strOrganization = CStr(Session(gstrSESS_ADS_O_ENTERPRISE))
        ADS_strOrganizationalUnit = CStr(Session(gstrSESS_ADS_OU_SITE))
        ADS_strServer = CStr(Session(gstrSESS_ADS_SERVER))

        Call ADS_GetQueryResults(mstrSelCriteria _
                                    , CStr(Session(gstrSESS_DL_ADS_PATH)) _
                                    , CInt(Session(gstrSESS_SEL_DN_PAGE)) _
                                    , bIncludeDLs)
    End If

    If Err.Number = gerrNONE Then
        Call ShowQueryResults()
    Else
        strError = gstrMSG_ALERT_CANT_DISPLAY_QUERY_RESULTS
        errNumber = Err.Number
        strErrDesc = Err.Description

        Err.Clear
    End If

    If mbAddDLMember Then
        '
        ' Display return link to properties if we're adding DL members.
        '
%>
        <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><A HRef=javascript:ValidateCmd('<%=gstrCMD_DL_PROPERTIES_RETURN%>')>Return to Distribution List Member Maintenance</A></DIV>
<%
    Else
        '
        ' Display OK & Cancel if we're modifying the DL owner.
        '
%>
        <Table>
        <TR>
            <TD Width=160 Align=Right><INPUT TYPE="button" VALUE="   OK   " OnClick="ValidateCmd('<%=mstrCmd%>')"></TD>
            <TD><INPUT TYPE="button" VALUE="Cancel" OnClick="ValidateCmd('<%=gstrCMD_DL_PROPERTIES_RETURN%>')"></TD>
        </TR>
        </Table>
<%
    End If
    '
    ' Use DHTML to size the txt & lst.
    '
    If App_bSupportsIE4DHTML() Then
%>
        <Script>
            var frm = document.<%=gstrFORM_MAIN%>;

            parent.SetWidth(frm.<%=gstrREQUEST_TXT_SEL_CRITERIA%>, <%=gpxlWIDTH_LST%>);
            parent.SetWidth(frm.<%=gstrREQUEST_LST_SEL%>, <%=gpxlWIDTH_LST%>);
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

Private Sub ShowQueryResults()
    Dim strMultipleSel
    Dim iSel
    '
    ' Depending on whether we're adding dl members or modifying the dl owner,
    ' set the multiple selection property.
    '
    If mbAddDLMember Then
        strMultipleSel = " Multiple"
    Else
        strMultipleSel = gstrNONE
    End If
%>
    <Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Selected Entries:</Font>&nbsp;&nbsp;
<%
    '
    ' Display paging controls only if there are multiple pages
    '
    If ADS_cPage > 1 Then
        Call App_RenderPaging(gstrCMD_SEL_DN_GO_TO_PAGE, ADS_iPage, ADS_cPage _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_PREV, gstrMSG_REPLACE_SEL_S)) _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_NEXT, gstrMSG_REPLACE_SEL_S)))
    End If
%>
    <TABLE Cellspacing=0>
        <TR>
            <TD RowSpan=2>
                <SELECT NAME=<%=gstrREQUEST_LST_SEL%> SIZE=10 <%=strMultipleSel%>>
<%
            For iSel = LBound(ADS_rgstrADsPathSel) To UBound(ADS_rgstrADsPathSel)
%>
                    <OPTION VALUE='<%=App_strHTML(ADS_rgstrADsPathSel(iSel))%>'><%=App_strHTML(ADS_rgstrDispNameSel(iSel))%>
<%
            Next
%>
                </SELECT>
<%
%>
            </TD>
<%
    If mbAddDLMember Then
        '
        ' Display the Add Members command button if we're adding DL members.
        '
%>
            <TD Align=Left>
                <Input Type=Button Name=cmdAdd AccessKey="A" Value="Add Member(s)" OnClick="ValidateCmd('<%=mstrCmd%>')">
            </TD>
<%
    End If
%>
        </TR>
    </TABLE><BR>
<%
End Sub
%>
