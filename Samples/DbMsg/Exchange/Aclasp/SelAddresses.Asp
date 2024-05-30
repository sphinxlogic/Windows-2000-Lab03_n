<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="CDO.inc"-->
<%
'<!--Access Control List Maintenance Sample Application-->
'<!--SelAddresses.asp : Select Addresses asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' SelAddresses.asp prepares UI for selecting & adding members to an acl.
'
    Dim strCtlFocus
    Dim strHeading
    Dim mstrSelCriteria

    On Error Resume Next

    Call App_CheckSession()

    mstrSelCriteria = CStr(Session(gstrSESS_SEL_CRITERIA))

    strHeading = gstrPAGE_HEADING_ADD_ACL_MEMBER

    strCtlFocus = gstrREQUEST_TXT_SEL_CRITERIA

    Call App_RenderPage(strHeading, strCtlFocus)
    '
    ' When selection criteria was entered but no records found, display a msg.
    '
    If CDO_cSel = 0 And len(mstrSelCriteria) > 0 Then
        Call App_ShowMsg(Replace(gstrMSG_ALERT_NONE_ON_FILE, gchREPLACE, gstrMSG_REPLACE_MATCHING_ITEMS), gerrNONE, gstrNONE)
    End If

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdAdd:  Validates the add command.
    '
    ' bSelection:  Returns true is an entry is selected from the list.
    '
    ' bValidCmdFind:  Validates the find command.
%>
    <SCRIPT LANGUAGE="JavaScript">

        function ValidateCmd(pstrCmd) {
            var bValidCmd;

            if (pstrCmd == '<%=gstrCMD_ADD_ACL_MEMBER%>') {
                bValidCmd = bValidCmdAdd();
            }
            else if (pstrCmd == '<%=gstrCMD_FIND_ADDRESSES%>') {
                bValidCmd = bValidCmdFind(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SEL_CRITERIA%>);
            }
            else if (pstrCmd == '<%=gstrCMD_SEL_ADDRESSES_GO_TO_PAGE%>') {
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
            
            if (lst.length == 0) {
                parent.ShowError('<%=Replace(gstrMSG_ALERT_FIND_ITEMS, gchREPLACE, gstrMSG_REPLACE_ACL_MEMBERS_FOR_ADD)%>'
                                , frm.<%=gstrREQUEST_TXT_SEL_CRITERIA%>);
                return false;
            }
            else if (lst.selectedIndex == iLST_SEL_NONE) {
                parent.ShowError('<%=gstrMSG_ALERT_MUST_SEL_ACL_MEMBERS_ADD%>'
                                , lst);
                return false;
            }
            else {
                return true;
            }
        }

        function bValidCmdFind(ptxtFind) {

            if (! parent.bTxtEntered(ptxtFind.value, '<%=gstrMSG_REPLACE_SEL_CRITERIA%>', ptxtFind, true)) {
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
%>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Folder:</TD>
            <TD><%=App_strHTML(Session(gstrSESS_FOLDER_NAME))%></TD>
        </TR>
    </TABLE><BR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>Display entries with the following characters:</DIV>
    <INPUT TYPE="text" NAME=<%=gstrREQUEST_TXT_SEL_CRITERIA%> SIZE=40 MAXLENGTH=40 VALUE='<%=App_strHTML(mstrSelCriteria)%>'  OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SEL_CRITERIA%>)">
    <Input Type=Button Name=cmdFind AccessKey="F" Value="Find" OnClick="ValidateCmd('<%=gstrCMD_FIND_ADDRESSES%>')"><BR><BR>
<%
    If len(mstrSelCriteria) > 0 Then
        Call CDO_FindAddresses(mstrSelCriteria, CInt(Session(gstrSESS_SEL_ADDRESS_PAGE)))
    End If

    If Err.Number = gerrNONE Then
        Call ShowQueryResults()
    Else
        strError = gstrMSG_ALERT_CANT_DISPLAY_SEARCH_RESULTS
        errNumber = Err.Number
        strErrDesc = Err.Description

        Err.Clear
    End If
%>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><A HRef=javascript:ValidateCmd('<%=gstrCMD_ACL_MAINT%>')>Return to Access Control List Maintenance</A></DIV>
<%
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
    Dim iSel

%>
    <Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Selected Entries:</Font>&nbsp;&nbsp;
<%
    '
    ' Display paging controls only if there are multiple pages
    '
    If CDO_cPage > 1 Then
        Call App_RenderPaging(gstrCMD_SEL_ADDRESSES_GO_TO_PAGE, CDO_iPage, CDO_cPage _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_PREV, gstrMSG_REPLACE_ADDRESSES)) _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_NEXT, gstrMSG_REPLACE_ADDRESSES)))
    End If
%>
    <TABLE Cellspacing=0>
        <TR>
            <TD RowSpan=2>
                <SELECT NAME=<%=gstrREQUEST_LST_SEL%> SIZE=10  Multiple>
<%
        If CDO_cSel > 0 Then
            For iSel = LBound(CDO_rgstrAddressID) To UBound(CDO_rgstrAddressID)
%>
                    <OPTION VALUE='<%=App_strHTML(CDO_rgstrAddressID(iSel))%>'><%=App_strHTML(CDO_rgstrAddressDisplayName(iSel))%>
<%
            Next
        End If
%>
                </SELECT>
<%
%>
            </TD>
            <TD Align=Left>
                <Input Type=Button Name=cmdAdd AccessKey="A" Value="Add Member(s)" OnClick="ValidateCmd('<%=gstrCMD_ADD_ACL_MEMBER%>')">
            </TD>
        </TR>
    </TABLE><BR>
<%
End Sub
%>
