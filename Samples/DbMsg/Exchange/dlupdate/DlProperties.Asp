<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ADS.inc"-->
<%
'<!--Distribution List Maintenance Sample Application-->
'<!--dlProperties.asp : Distribution List Properties asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' dlProperties.asp provides UI for modifying selected dl's properties.
'
    
    Dim strHeading
    Dim strCtlFocus
    Dim mbAddDL

    On Error Resume Next

    Call App_CheckSession()
    '
    ' Determine whether adding or modifying a dl
    '
    mbAddDL = (Session(gstrSESS_CMD) = gstrCMD_ADD_DL)

    If mbAddDL Then
        strHeading = gstrPAGE_HEADING_DL_ADD
    Else
        strHeading = gstrPAGE_HEADING_DL_PROPERTIES
    End If

    strCtlFocus = gstrREQUEST_TXT_DISP_NAME

    Call App_RenderPage(gstrIMG_DL, strHeading, strCtlFocus)
    '
    ' Display msg if no members are on file.
    '
    If UBound(ADS_rgstrADsPathMembers) < 0 And Not mbAddDL Then
        Call App_ShowMsg(Replace(gstrMSG_ALERT_NONE_ON_FILE, gchREPLACE, gstrMSG_REPLACE_DL_MEMBERS), gerrNONE, gstrNONE)
    End If

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidEntries:  Verifies entry of required flds.
    '
    ' bValidCmdDel:  Validates delete command.
    '
    ' bDLMembersSelected:  Verifies selection of dl members.
    '
    ' ValidateReturn:  Executed if the return link is selected, verifies entry of required flds.
%>
    <SCRIPT LANGUAGE="JavaScript">
        var mbDirty = false;

        function ValidateCmd(pstrCmd) {
            var bValidCmd = false;

<%
        If mbAddDL Then
            '
            ' For adds, if the user chooses to return to DL Maintenance, we need to allow them
            ' to return w/out adding.
            '
%>
            if (pstrCmd == '<%=gstrCMD_DL_MAINT_CANCEL_ADD%>') {
                bValidCmd = true;
            }
            else 
<%
        End If
%>
            if (bValidEntries()) {
                if (pstrCmd == '<%=gstrCMD_DEL_DL_MEMBER%>') {
                    bValidCmd = bValidCmdDel();
                }
                else if (pstrCmd == '<%=gstrCMD_DL_PROPERTIES_GO_TO_PAGE%>') {
                    bValidCmd = parent.bValidCmdGoToPage();
                }
                else {
                    bValidCmd = true;
                }
            }

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidEntries() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_DISP_NAME%>.value,
                                        '<%=gstrMSG_REPLACE_DISP_NAME%>',
                                        frm.<%=gstrREQUEST_TXT_DISP_NAME%>)) {
                return false;
            }
<%
        If mbAddDL Then
            '
            ' For adds, verify entry of the alias.
            '
%>
            else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_ALIAS%>.value,
                                    '<%=gstrMSG_REPLACE_ALIAS%>',
                                    frm.<%=gstrREQUEST_TXT_ALIAS%>)) {
                return false;
            }
<%
        End If
%>
            else if (! parent.bValidStrLength(frm.<%=gstrREQUEST_TXT_NOTES%>, <%=gcCH_MAX_NOTES%>, '<%=gstrMSG_REPLACE_NOTES%>')) {
                return false;
            }
            else {
                return true;
            }
        }

        function bValidCmdDel() {
            if (bDLMembersSelected()) {  
                if (confirm(parent.strMsgReplace('<%=gstrMSG_CONFIRM_DEL%>', new Array('<%=gstrMSG_REPLACE_DL_MEMBERS%>')))) {
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

        function bDLMembersSelected() {
            var ctl = document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_DL_MEMBERS%>;
            var iLST_SEL_NONE = -1;
            
            if (ctl.selectedIndex == iLST_SEL_NONE) {
                parent.ShowError(parent.strMsgReplace('<%=gstrMSG_ALERT_MUST_SEL_DL_MEMBER%>', new Array('<%=gstrMSG_REPLACE_DEL%>')),
                                ctl);
                return false;
            }
            else {
                return true;
            }
        }

<%
    If mbAddDL Then
        '
        ' For adds, this routine provides for returning to the DL Maintenance page w/out adding
        ' the dl.
        '
%>
        function ValidateReturn() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if ((! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_DISP_NAME%>.value)) 
                    && (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_ALIAS%>.value))
                    && (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_NOTES%>.value))) {
                ValidateCmd('<%=gstrCMD_DL_MAINT_CANCEL_ADD%>');
            }
            else if ((! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_DISP_NAME%>.value)) 
                    || (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_ALIAS%>.value))) {
                if (confirm('<%=gstrMSG_CONFIRM_CANCEL_ADD_1 & gjsNEW_LINE & gjsNEW_LINE & gstrMSG_CONFIRM_CANCEL_ADD_2%>')) {
                    ValidateCmd('<%=gstrCMD_DL_MAINT_CANCEL_ADD%>');
                }
                else {
                    if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_DISP_NAME%>.value)) {
                        parent.SetFocus(frm.<%=gstrREQUEST_TXT_DISP_NAME%>)
                    }
                    else {
                        parent.SetFocus(frm.<%=gstrREQUEST_TXT_ALIAS%>)
                    }
                }
            }
            else {
                ValidateCmd('<%=gstrCMD_DL_MAINT%>');
            }
        }
<%
    End If
%>
    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()
    Dim strError
    Dim strErrDesc
    Dim errNumber
    Dim strLinkReturnClick

    On Error Resume Next

    If mbAddDL Then
        '
        ' For adds, show page w/out getting properties.
        '
        Call ShowDLProperties()
        '
        ' For adds, when the return link is selected but required flds are not entered,
        ' determine whether to return w/out adding the dl.
        '
        strLinkReturnClick = "ValidateReturn()"
    Else
        '
        ' For mods, get properties before showing page.
        '
        ADS_strOrganization = CStr(Session(gstrSESS_ADS_O_ENTERPRISE))
        ADS_strOrganizationalUnit = CStr(Session(gstrSESS_ADS_OU_SITE))
        ADS_strServer = CStr(Session(gstrSESS_ADS_SERVER))

        Call ADS_GetDLProperties(CStr(Session(gstrSESS_DL_ADS_PATH)) _
                                    , CInt(Session(gstrSESS_DL_MEMBER_PAGE)))
        If Err.Number = gerrNONE Then
            Call ShowDLProperties()
        Else
            strError = gstrMSG_ALERT_CANT_DISPLAY_DL_PROPERTIES
            errNumber = Err.Number
            strErrDesc = Err.Description

            Err.Clear
        End If
        '
        ' For mods, when the return link is selected perform normal validation.
        '
        strLinkReturnClick = "ValidateCmd('" & gstrCMD_DL_MAINT & "')"
    End If

%>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><A HRef=javascript:<%=strLinkReturnClick%>>Return to Distribution List Maintenance</A></DIV>
<%
    '
    ' Display a msg if an error was detected
    '
    If Len(strError) > 0 Then
        Call App_ShowMsg(strError, errNumber, strErrDesc)
    End If
End Sub

Private Sub ShowDLProperties()
    Dim bDirtyProperties
    Dim strDLOwner
    Dim iMember
    '
    ' Save alias, display name, & page session properties & show heading info
    '
    Session(gstrSESS_DL_ALIAS) = ADS_strAlias
    Session(gstrSESS_DL_DISP_NAME) = ADS_strDispName
    Session(gstrSESS_DL_MEMBER_PAGE) = ADS_iPage
    '
    ' Set DL owner & cmdClearOnClick handling
    '
    If len(ADS_strDispNameOwner) = 0 Then
        strDLOwner = gstrDISP_NAME_OWNER_NONE
    Else
        strDLOwner = ADS_strDispNameOwner
    End If
    '
    ' Set initial value of dirty flag.  For adds, initial value is always true.  For mods,
    ' initial value is false & flag is updated during change event of disp name & notes.
    '
    bDirtyProperties = mbAddDL
%>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Display Name:</TD>
            <TD><INPUT TYPE="text" NAME="<%=gstrREQUEST_TXT_DISP_NAME%>" 
                    MaxLength=<%=gcCH_DISP_NAME%> 
                    OnChange='parent.txt_OnChange()'
                    OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_DISP_NAME%>)" 
                    Value=<%=App_strHTML(ADS_strDispName)%>></TD>
        </TR>
        <TR>
            <TD>Alias:</TD>
<%
        If mbAddDL Then
%>
            <TD><INPUT TYPE="text" NAME="<%=gstrREQUEST_TXT_ALIAS%>" 
                    MaxLength=<%=gcCH_ALIAS%> 
                    OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_ALIAS%>)"></TD>
<%
        Else
%>
            <TD><%=App_strHTML(ADS_strAlias)%></TD>
<%
        End If
%>
        </TR>
    </TABLE><BR>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD Width=85>Owner:</TD>
            <TD><%=App_strHTML(strDLOwner)%></TD>
        </TR>
    </TABLE>
    <Input Type=Button Name=cmdModifyOwner AccessKey="M" Value="Modify..." 
            OnClick="ValidateCmd('<%=gstrCMD_MOD_DL_OWNER%>')">
    <BR><BR>

    <Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Members:</Font>&nbsp;&nbsp;
<%
    '
    ' Display paging controls only if there are multiple pages
    '
    If ADS_cPage > 1 Then
        Call App_RenderPaging(gstrCMD_DL_PROPERTIES_GO_TO_PAGE, ADS_iPage, ADS_cPage _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_PREV, gstrMSG_REPLACE_DL_MEMBERS)) _
                                , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_NEXT, gstrMSG_REPLACE_DL_MEMBERS)))
    End If
%>
    <TABLE>
        <TR>
            <TD RowSpan=5>
            <SELECT NAME='<%=gstrREQUEST_LST_DL_MEMBERS%>' SIZE=10 MULTIPLE>
<%
        For iMember = LBound(ADS_rgstrADsPathMembers) To UBound(ADS_rgstrADsPathMembers)
%>
            <OPTION Value='<%=App_strHTML(ADS_rgstrADsPathMembers(iMember))%>'><%=App_strHTML(ADS_rgstrDispNameMembers(iMember))%>
<%
        Next
%>
            </SELECT>
            </TD>
            <TD Align=Left>
                <Input Type=Button Name=cmdAdd AccessKey="A" Value=" Add... " 
                    OnClick="ValidateCmd('<%=gstrCMD_ADD_DL_MEMBER%>')">
            </TD>
        </TR>
        <TR>
            <TD Align=Left VAlign=Top>
                <Input Type=Button Name=cmdDelete AccessKey="D" Value="Delete" 
                    OnClick="ValidateCmd('<%=gstrCMD_DEL_DL_MEMBER%>')">
            </TD>
        </TR>
    </TABLE><BR>
    <Font Class=<%=gstrCSS_CLASS_FONT_Normal%>>Notes:</Font><BR>
    <TextArea Name=<%=gstrREQUEST_TXT_NOTES%> Class=<%=gstrCSS_CLASS_FONT_Normal%> Rows=6
        OnChange='parent.txt_OnChange()' 
        OnFocus='parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_NOTES%>)'><%=ADS_strNotes%></TextArea>
    <BR><BR>
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_B_DIRTY_PROPERTIES%>" 
            Value=<%=CInt(bDirtyProperties)%>>
    <Script>
        var frm = document.<%=gstrFORM_MAIN%>;
<%
    If App_bSupportsIE4DHTML() Then
        '
        ' Use DHTML to size the lst.
        '
        If mbAddDL Then
%>
            parent.SetWidth(frm.<%=gstrREQUEST_TXT_ALIAS%>, <%=gpxlWIDTH_LST - 90%>);
<%
        End If
%>
        parent.SetWidth(frm.<%=gstrREQUEST_TXT_DISP_NAME%>, <%=gpxlWIDTH_LST - 90%>);
        parent.SetWidth(frm.<%=gstrREQUEST_LST_DL_MEMBERS%>, <%=gpxlWIDTH_LST%>);
        parent.SetWidth(frm.<%=gstrREQUEST_TXT_NOTES%>, <%=gpxlWIDTH_LST%>);
<%
    End If
%>
    </Script>
<%
End Sub
%>