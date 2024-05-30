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
'<!--RuleProperties.asp : Rule Properties asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' RuleProperties.asp provides UI for modifying the selected rule's properties.
'
    Const mstrLST_FROM = "lstFrom"
    Const mstrLST_SENT_TO = "lstTo"

    Dim mbAdd

    Dim strCtlFocus
    Dim strPageHeading

    On Error Resume Next
    '
    ' Verify cdo session
    '
    Call App_CheckSession()
    '
    ' Get properties
    '
    Call Rule_GetProperties()

    If Err.Number = gerrNONE Then
        mbAdd = (Session(gstrSESS_CMD) = gstrCMD_ADD_RULE)

        If mbAdd Then
            strPageHeading = gstrPAGE_HEADING_ADD_RULE
        Else
            strPageHeading = gstrPAGE_HEADING_RULE_PROPERTIES
        End If

        strCtlFocus = mstrLST_FROM

        Call App_RenderPage(strPageHeading, strCtlFocus)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_GET_PROPERTIES, Err.Number, Err.Description)
    End If

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdOK:  Validates the OK command.
    '
    ' cmdAddAddress_OnClick:  Event handler for all cmdAddAddress click events.
    '
    ' cmdRemoveAddress_OnClick:  Event handler for all cmdRemoveAddress click events.  If fired
    ' for forwarding list, unchecks forward checkbox when last entry is removed.
    '
    ' gstrREQUEST_CHK_ACT_SKIP_RULES_OnClick:  Event handler for "skip subsequent rules" checkbox.
    ' When unchecked, delete action checkbox is unchecked.
    '
    ' gstrREQUEST_CHK_ACT_RETURN_OnClick:  Event handler for return checkbox.  When checked, 
    ' delete & forward checkboxes are unchecked.
    '
    ' gstrREQUEST_CHK_ACT_DELETE_OnClick:  Event handler for delete checkbox.  When checked, 
    ' return checkbox is unchecked & "skip subsequent rules" checkbox is checked.
    '
    ' lstRemove:  Removes the selected entry from the passed list.
    '
%>
    <SCRIPT LANGUAGE="JavaScript">
        function ValidateCmd(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>;
            var bValidCmd;

            if (pstrCmd == '<%=gstrCMD_UPD_RULE%>') {
                bValidCmd = bValidCmdOK();
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                if (pstrCmd != '<%=gstrCMD_RULES_MAINT%>') {
                    parent.SaveLstToCtl(frm.<%=mstrLST_FROM%>, frm.<%=gstrREQUEST_HID_RG_ADDRESS_ID_FROM%>);
                    parent.SaveLstToCtl(frm.<%=mstrLST_SENT_TO%>, frm.<%=gstrREQUEST_HID_RG_ADDRESS_ID_SENT_TO%>);
                };

                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidCmdOK() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if ((! frm.<%=gstrREQUEST_CHK_ACT_RETURN%>.checked)
                && (! frm.<%=gstrREQUEST_CHK_ACT_DELETE%>.checked)
                ) {
                parent.ShowError('<%=gstrMSG_ALERT_MUST_SEL_RULE_ACT%>', frm.<%=gstrREQUEST_CHK_ACT_SKIP_RULES%>);

                return false;
            }
            else if ((frm.<%=mstrLST_FROM%>.length == 0)
                && (frm.<%=mstrLST_SENT_TO%>.length == 0)
                && (! frm.<%=gstrREQUEST_CHK_COND_SENT_TO%>.checked)
                && (! frm.<%=gstrREQUEST_CHK_COND_COPIED_TO%>.checked)
                && (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_COND_SUBJECT%>.value))
                && (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_COND_MSG_BODY%>.value))
                ) {
                return confirm('<%=gstrMSG_CONFIRM_NO_CONDITIONS%>');
            }
            else {
                return true;
            }
        }

        function cmdAddAddress_OnClick(pstrCmd) {
            ValidateCmd(pstrCmd);
        }

        function cmdRemoveAddress_OnClick(pctl) {
            var frm=document.<%=gstrFORM_MAIN%>;

            lstRemove(pctl);

        }

        function <%=gstrREQUEST_CHK_ACT_SKIP_RULES%>_OnClick() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if (! frm.<%=gstrREQUEST_CHK_ACT_SKIP_RULES%>.checked) {
                frm.<%=gstrREQUEST_CHK_ACT_DELETE%>.checked = false;
            } 
        }

        function <%=gstrREQUEST_CHK_ACT_RETURN%>_OnClick() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if (frm.<%=gstrREQUEST_CHK_ACT_RETURN%>.checked) {
                frm.<%=gstrREQUEST_CHK_ACT_DELETE%>.checked = false;
            } 
        }

        function <%=gstrREQUEST_CHK_ACT_DELETE%>_OnClick() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if (frm.<%=gstrREQUEST_CHK_ACT_DELETE%>.checked) {
                frm.<%=gstrREQUEST_CHK_ACT_RETURN%>.checked = false;
                frm.<%=gstrREQUEST_CHK_ACT_SKIP_RULES%>.checked = true;
            }
            else {
                frm.<%=gstrREQUEST_CHK_ACT_SKIP_RULES%>.checked = false;
            }
        }

        function lstRemove(plst) {
            var ilstSel = plst.selectedIndex;
            var clst;
            
            if (ilstSel != parent.iLST_NONE) {
                plst.options[ilstSel] = null;

                plst.selectedIndex = parent.iLST_NONE;
                clst = plst.length;

                if (ilstSel <= clst - 1) {
                    plst.selectedIndex = ilstSel;
                }
                else if (ilstSel > 0) {
                    plst.selectedIndex = ilstSel - 1;
                }
            }
            else {
                parent.ShowError('<%=gstrMSG_ALERT_MUST_SEL_ENTRY%>', plst);
            }
        }
    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()

    Call RenderConditions()
    Call RenderActions()
%>
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_RG_ADDRESS_ID_FROM%>" VALUE="">
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_RG_ADDRESS_ID_SENT_TO%>" VALUE="">
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_RG_ADDRESS_ID_FORWARD%>" VALUE="">
    <HR>
    <Table>
        <TR>
            <TD Width=200 Align=Right><Input Type="button" Value="   OK   " OnClick="ValidateCmd('<%=gstrCMD_UPD_RULE%>')"></TD>
            <TD><Input Type="button" Value="Cancel" OnClick="ValidateCmd('<%=gstrCMD_RULES_MAINT%>')"></TD>
        </TR>
    </Table>
<%
End Sub 

Private Sub RenderConditions()
    Const iSIZE_LST_FROM = 3
    Const iSIZE_LST_TO = 3
%>
    <Font Class="<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>">When a message arrives that meets the following conditions:</Font>
    <Table>
<%
        Call RenderLst(mstrLST_FROM, Rule_Cond_rgaeFrom, Rule_Cond_rgaeFromName _
                        , iSIZE_LST_FROM, gstrCAP_LST_FROM _
                        , gstrCAP_CMD_ADD, gstrCMD_SEL_ADDRESSES_FROM, gstrCAP_CMD_REMOVE)
%>
        <TR></TR>
        <TR></TR>
<%
        Call RenderLst(mstrLST_SENT_TO, Rule_Cond_rgaeTo, Rule_Cond_rgaeToName _
                        , iSIZE_LST_TO, gstrCAP_LST_TO _
                        , gstrCAP_CMD_ADD, gstrCMD_SEL_ADDRESSES_SENT_TO, gstrCAP_CMD_REMOVE)
%>
        <TR>
            <TD></TD>
            <TD>
<%
            Call RenderChk(gstrREQUEST_CHK_COND_SENT_TO, gstrNONE _
                            , gstrCAP_CHK_COND_SENT_TO, Rule_Cond_bSentTo)
            Call RenderChk(gstrREQUEST_CHK_COND_COPIED_TO, gstrNONE _
                            , gstrCAP_CHK_COND_COPIED_TO, Rule_Cond_bCopiedTo)
%>
            </TD>
        </TR>
        <TR></TR>
        <TR></TR>
        <TR>
            <TD><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Subject:</FONT></TD>
            <TD><Input Type=Text Name=<%=gstrREQUEST_TXT_COND_SUBJECT%> 
                        Value='<%=App_strHTML(Rule_Cond_strSubject)%>' Style="width:<%=gpxlWIDTH_LST%>px"></TD>
        </TR>
        <TR>
            <TD><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Message Body:</FONT></TD>
            <TD><Input Type=Text Name=<%=gstrREQUEST_TXT_COND_MSG_BODY%> 
                        Value='<%=App_strHTML(Rule_Cond_strMsgBody)%>' Style="width:<%=gpxlWIDTH_LST%>px"></TD>
        </TR>
    </Table>
    <HR>
<%
End Sub

Private Sub RenderActions()

    Const iSIZE_LST_FWD_TO = 3
    Const iSIZE_LST_METHOD = 1
    Const cMETHODS = 3
%>
    <Table>
        <TR>
            <TD Width=250px>
                <Font Class="<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>">Perform these actions:</Font>
            </TD>
            <TD>
<%
            Call RenderChk(gstrREQUEST_CHK_ACT_SKIP_RULES, gstrNONE _
                            , gstrCAP_CHK_ACT_SKIP_RULES, Rule_Act_bSkipSubsequentRules)
%>
            </TD>
        </TR>
    </Table>
    <Table>
        <TR>
            <HR>
        </TR>
        <TR>
            <TD ColSpan=2>
<%
            Call RenderChk(gstrREQUEST_CHK_ACT_RETURN, gstrIMG_RETURN _
                            , gstrCAP_CHK_ACT_RETURN, Rule_Act_bReturn)
%>
            </TD>
        </TR>
        <TR>
            <TD ColSpan=2>
            &nbsp;&nbsp;&nbsp;<Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Or</Font>
            </TD>
        </TR>
        <TR>
            <TD>
<%
            Call RenderChk(gstrREQUEST_CHK_ACT_DELETE, gstrIMG_DELETE _
                            , gstrCAP_CHK_ACT_DELETE, Rule_Act_bDelete)
%>
            </TD>
        </TR>
    </Table>
<%
End Sub

Private Sub RenderChk(pstrChk, pstrImg, pstrCapChk, pbChecked)
'
' RenderChk displays a checkbox.  Input parms are as follows:
'
'   pstrChk     Checkbox name
'   pstrImg     Name of image file to display in front of checkbox.
'   pstrCapChk  Checkbox caption
'   pbChecked   Checked boolean
'
    Dim strHTMLChecked
    Dim strHTMLImg
    Dim strHTMLOnCheck
    '
    ' Set checked
    '
    If pbChecked Then
        strHTMLChecked = gstrHTML_CHECKBOX_CHECK
    Else
        strHTMLChecked = gstrNONE
    End If
    '
    ' Set checkbox image
    '
    If Len(pstrImg) > 0 Then
        strHTMLImg = "<Img src=" & pstrImg & ">"
    Else
        strHTMLImg = gstrNONE
    End If
    '
    ' For action checkboxes, add event handling
    '
    Select Case pstrChk
        Case gstrREQUEST_CHK_ACT_SKIP_RULES, gstrREQUEST_CHK_ACT_RETURN _
                , gstrREQUEST_CHK_ACT_DELETE, gstrREQUEST_CHK_ACT_FORWARD
            strHTMLOnCheck = "OnClick=""" & pstrChk & "_OnClick()"""
        Case Else
            strHTMLOnCheck = gstrNONE
    End Select
%>
    <%=strHTMLImg%><Input Type=Checkbox Name="<%=pstrChk%>" Value="True" 
                        <%=strHTMLOnCheck & gchSPACE & strHTMLChecked%>>
    <Font Class="<%=gstrCSS_CLASS_FONT_NORMAL%>"><%=pstrCapChk%></Font>
<%
End Sub

Private Sub RenderLst(pstrlstName, prgstrVal, prgstr, piSizeLst _
                        , pstrCapLst, pstrCapCmdAdd, pstrCmdAddCmd, pstrCapCmdDel)
'
' RenderLst displays a listbox or dropdown.  Input parms are as follows:
'
'   pstrlstName     Name of list
'   prgstrVal       Array of list entry values
'   prgstr          Array of list entry text
'   piSizeLst       List size.  A size of 1 creates a combo.
'   pstrCapLst      List caption.
'   pstrCapCmdAdd   Caption of add command button.
'   pstrCmdAddCmd   Cmd dispatched in cmdAdd click event.
'   pstrCapCmdDel   Caption of remove command button.
'
    Dim ilst
    Dim strHTMLCmds
    Dim strOptions

    strHTMLCmds = gstrNONE
    strOptions = gstrNONE

    If Len(pstrCapCmdAdd) > 0 Then
        strHTMLCmds = "<TD VAlign=Top>" _
                        & "<Input Type=Button Value=""" & pstrCapCmdAdd _
                            & """ OnClick=""cmdAddAddress_OnClick('" & pstrCmdAddCmd & "')"">" _
                    & "</TD>" _
                & "</TR>"
        strHTMLCmds = strHTMLCmds _
                & "<TR>" _
                    & "<TD></TD>" _
                    & "<TD VAlign=Top>" _
                        & "<Input Type=Button Value=""" & pstrCapCmdDel _
                            & """ OnClick='cmdRemoveAddress_OnClick(document. " & gstrFORM_MAIN & "." & pstrlstName & ")'" _
                            & """ OnDblClick='cmdRemoveAddress_OnClick(document. " & gstrFORM_MAIN & "." & pstrlstName & ")'>" _
                    & "</TD>" _
                & "</TR>"
    End If

    For ilst = LBound(prgstr) To UBound(prgstr)
        strOptions = strOptions & "<Option Value='" & prgstrVal(ilst) & "'>" & prgstr(ilst)
    Next
%>
    <TR>
        <TD VAlign=Top>
            <Font Class="<%=gstrCSS_CLASS_FONT_NORMAL%>"><%=pstrCapLst%></Font>
        </TD>
        <TD RowSpan=2 Valign=Top>
            <Select Name=<%=pstrlstName%> Size=<%=piSizeLst%> Style="width:<%=gpxlWIDTH_LST%>px">
            <%=strOptions%>
            </Select>
        </TD>
        <%=strHTMLCmds%>
<%
End Sub
%>
