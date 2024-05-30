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
'<!--ACLMaintenance.asp : Access Control List Maintenance asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' ACLMaintenance.asp lists ACL members & provides for adding, modifying, & deleting.
'
    Dim strCtlFocus

    On Error Resume Next
    '
    ' Verify cdo session
    '
    Call App_CheckSession()

    strCtlFocus = gstrREQUEST_LST_ACL_MEMBERS

    Call App_RenderPage(gstrPAGE_HEADING_ACL_MAINT, strCtlFocus)
    
    If ACL_cMembers = 0 Then
        Call App_ShowMsg(Replace(gstrMSG_ALERT_NONE_ON_FILE, gchREPLACE, gstrMSG_REPLACE_ACL_MEMBERS), gerrNONE, gstrNONE)
    End If

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' ValidCmdMod:  Validates the modify command.
    '
    ' ValidCmdDel:  Validates the delete command.
    '
    ' bMemberSelected:  Returns a boolean indicating whether a member is selected.
    '
%>
    <SCRIPT LANGUAGE="JavaScript">
        function ValidateCmd(pstrCmd) {
            var bValidCmd;

            if (pstrCmd == '<%=gstrCMD_MEMBER_PROPERTIES%>') {
                bValidCmd = bValidCmdMod(pstrCmd);
            }
            else if (pstrCmd == '<%=gstrCMD_DEL_ACL_MEMBER%>') {
                bValidCmd = bValidCmdDel(pstrCmd);
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidCmdMod(pstrCmd) {
            if (bMemberSelected(pstrCmd)) {
                var frm = document.<%=gstrFORM_MAIN%>;
                var lst = frm.<%=gstrREQUEST_LST_ACL_MEMBERS%>;

                var ilstSel = lst.selectedIndex;

                frm.<%=gstrREQUEST_ACL_MEMBER_DISP_NAME%>.value = 
                        lst.options[ilstSel].text;
                frm.<%=gstrREQUEST_ACL_MEMBER_ID%>.value = 
                        lst.options[ilstSel].value;
                return true;    
            }
            else {
                return false;
            }
        }

        function bValidCmdDel(pstrCmd) {
            if (bMemberSelected(pstrCmd)) {  
                var frm = document.<%=gstrFORM_MAIN%>;
                var lst = frm.<%=gstrREQUEST_LST_ACL_MEMBERS%>;

                var ilstSel = lst.selectedIndex;

                if (confirm(parent.strMsgReplace('<%=gstrMSG_CONFIRM_DEL%>', new Array(lst.options[ilstSel].text)))) {
                    frm.<%=gstrREQUEST_ACL_MEMBER_ID%>.value = lst.options[ilstSel].value;
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

        function bMemberSelected(pstrCmd) {
            var iLST_SEL_NONE = -1;
            var lst = document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_ACL_MEMBERS%>;
            
            if (lst.selectedIndex == iLST_SEL_NONE) {
                parent.ShowError(
                    parent.strMsgReplace('<%=gstrMSG_ALERT_MUST_SEL_ACL_MEMBER%>', 
                        new Array((pstrCmd == '<%=gstrCMD_DEL_ACL_MEMBER%>') ? 
                            '<%=gstrMSG_REPLACE_DEL%>' : '<%=gstrMSG_REPLACE_MOD%>')),
                    lst);
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
    Dim strFolder
    Dim strError
    Dim strErrDesc
    Dim errNumber
    Dim cDL

    On Error Resume Next

    strFolder = Session(gstrSESS_FOLDER_NAME)
%>
    <Table Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Folder:</TD>
            <TD><%=App_strHTML(strFolder)%></TD>
        </TR>
    </Table>
    <BR>
    <DIV Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Members:</DIV>
    <Table>
        <TR>
            <TD RowSpan=5>
<%
    Call ACL_GetMembers()

    If Err.Number = gerrNONE Then
        Call RenderACLMembers()
    Else
        strError = gstrMSG_ALERT_CANT_DISPLAY_ACL
        errNumber = Err.Number
        strErrDesc = Err.Description

        Err.Clear
    End If
%>
            </TD>
            <TD Align=Left VAlign=Bottom>
                <Input Type=Button Name=cmdAdd AccessKey="A" Value="  Add...   " OnClick="ValidateCmd('<%=gstrCMD_SEL_ADDRESSES%>')">
            </TD>
        </TR>
        <TR>
            <TD Align=Left>
                <Input Type=Button Name=cmdModify AccessKey="M" Value="Modify..." OnClick="ValidateCmd('<%=gstrCMD_MEMBER_PROPERTIES%>')">
            </TD>
        </TR>
        <TR>
            <TD Align=Left VAlign=Top>
                <Input Type=Button Name=cmdDelete AccessKey="D" Value=" Delete  " OnClick="ValidateCmd('<%=gstrCMD_DEL_ACL_MEMBER%>')">
            </TD>
        </TR>
    </Table><BR>
    <Table>
        <TR>
            <TD Width=100 Align=Right><INPUT TYPE="button" VALUE="Submit" OnClick="ValidateCmd('<%=gstrCMD_COMMIT%>')"></TD>
            <TD><INPUT TYPE="button" VALUE="Cancel" OnClick="ValidateCmd('<%=gstrCMD_SEL_FOLDER%>')"></TD>
        </TR>
    </Table>
    <Input Type=Hidden Name="<%=gstrREQUEST_ACL_MEMBER_DISP_NAME%>">
    <Input Type=Hidden Name="<%=gstrREQUEST_ACL_MEMBER_ID%>">
<%
    If App_bSupportsIE4DHTML() Then
        '
        ' Use DHTML to size the lst.
        '
%>
        <Script>
            parent.SetWidth(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_ACL_MEMBERS%>, <%=gpxlWIDTH_LST%>)
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

Private Sub RenderACLMembers()
    Dim iACLMembers
%>
    <Select Name=<%=gstrREQUEST_LST_ACL_MEMBERS%> Size=10>
<%
        If ACL_cMembers > 0 Then
            For iACLMembers = LBound(ACL_rgstrMemberID) To UBound(ACL_rgstrMemberID)
%>
                <Option Value='<%=App_strHTML(ACL_rgstrMemberID(iACLMembers))%>'><%=App_strHTML(ACL_rgstrMember(iACLMembers))%>
<%
            Next
        End If
%>
    </Select>
<%
End Sub
%>
