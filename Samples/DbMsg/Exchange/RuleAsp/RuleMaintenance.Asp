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
'<!--RuleMaintenance.asp : Rule Maintenance asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' RuleMaintenance.asp lists rules for the selected folder & provides
' for adding, modifying, deleting, & sequencing.
'
    Dim strCtlFocus

    On Error Resume Next
    '
    ' Verify cdo session
    '
    Call App_CheckSession()

    strCtlFocus = gstrNONE

    Call App_RenderPage(gstrPAGE_HEADING_RULE_MAINT, strCtlFocus)

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdMod:  Validates the modify command.
    '
    ' bValidCmdDel:  Validates the delete command.
    '
    ' bRuleSelected:  Determines whether a rule is selected & saves the index of the selection.
    '
    ' LstRuleSequence:  Constructor for the lstRanking object, consisting of a list (plst),
    ' a move up command button (pcmdMoveUp), a move down command button (pcmdMoveDown),
    ' and a hidden field (hidRuleSequence) for submitting the rankings.
    '
    ' SetSelection:  Method of the lstRanking object.  Sets the selected index property,
    ' ilstSel.
    '
    ' Enabled:  Method of the lstRanking object.  Sets the enablement of the object's controls.
    '
    ' MoveRule:  Method of the lstRanking object.  Moves the selected option in the direction 
    ' indicated by srcElement.
    '
%>
    <Script Language="JavaScript">
        var miLST_SEL_NONE = -1;
        var miLST_FIRST = 0;

        function ValidateCmd(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>;
            var bValidCmd;

            if (pstrCmd == '<%=gstrCMD_MOD_RULE%>') {
                bValidCmd = bValidCmdMod(pstrCmd);
            }
            else if (pstrCmd == '<%=gstrCMD_DEL_RULE%>') {
                bValidCmd = bValidCmdDel(pstrCmd);
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                if (pstrCmd != '<%=gstrCMD_SEL_FOLDER%>') {
                    parent.SaveLstToCtl(frm.<%=gstrREQUEST_LST_RULES%>, frm.<%=gstrREQUEST_HID_RG_I_RULE%>);
                };

                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidCmdMod(pstrCmd) {
             return bRuleSelected(pstrCmd);
        }

        function bValidCmdDel(pstrCmd) {
            if (bRuleSelected(pstrCmd)) {  
                var lst = document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_RULES%>;

                var ilstSel = lst.selectedIndex;

                return confirm('<%=gstrMSG_CONFIRM_DEL%>');
            }
            else {
                return false;
            }  
        }

        function bRuleSelected(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>
            var lst = frm.<%=gstrREQUEST_LST_RULES%>;
            var ilstSel = lst.selectedIndex
            
            if (ilstSel == miLST_SEL_NONE) {
                parent.ShowError((pstrCmd == '<%=gstrCMD_DEL_RULE%>') ? 
                            '<%=gstrMSG_ALERT_MUST_SEL_RULE_DEL%>' : '<%=gstrMSG_ALERT_MUST_SEL_RULE_MOD%>');
                return false;
            }
            else {
                frm.<%=gstrREQUEST_HID_I_RULE%>.value = lst.options[ilstSel].value;

                return true;
            }
        }

        function LstRuleSequence (plst, pcmdMoveUp, pcmdMoveDown, phidRuleSequence) {

            this.lst = plst;
            this.cmdMoveUp = pcmdMoveUp;
            this.cmdMoveDown = pcmdMoveDown;
            this.hidRuleSequence = phidRuleSequence;

            this.ilstLast = plst.length - 1 

            this.MoveRule = MoveRule;
            this.Enabled = Enabled;
            this.SetSelection = SetSelection;

            this.SetSelection((plst.length > 0 ? miLST_FIRST : miLST_SEL_NONE));
        }

        function SetSelection(pilstSel) {
            if (pilstSel == null) {
                this.ilstSel = this.lst.selectedIndex;
            }
            else {
                this.lst.selectedIndex = pilstSel;
                this.ilstSel = pilstSel;
            }
            this.Enabled();
        }

        function Enabled() {
<%
        If App_bSupportsIE4DHTML() Then
            '
            ' Disabled not available under NN.
            ' 
%>
            if (this.lst.length == 0) {
                this.lst.disabled = true;
                this.cmdMoveUp.disabled = true;
                this.cmdMoveDown.disabled = true;
            }
            else if(this.ilstSel == miLST_SEL_NONE) {
                this.cmdMoveUp.disabled = true;
                this.cmdMoveDown.disabled = true;
            }
            else {
                this.cmdMoveUp.disabled = (this.ilstSel == 0)
                this.cmdMoveDown.disabled = (this.ilstSel == this.ilstLast)
            }
<%
        End If
%>
        }

        function MoveRule(pbMoveUp){
            var ilstSwap;
            var iOptValSav;
            var strOptSav;
            var bMoveUp

            if (pbMoveUp == null) {
                bMoveUp = (event.srcElement == this.cmdMoveUp)
            }
            else {
                bMoveUp = pbMoveUp
            }

            if ((this.ilstSel != miLST_SEL_NONE) && 
                (bMoveUp ? this.ilstSel != miLST_FIRST : this.ilstSel != this.ilstLast)) {

                ilstSwap = this.ilstSel + (bMoveUp ? -1 : 1);

                iOptValSav =  this.lst.options[ilstSwap].value;
                strOptSav = this.lst.options[ilstSwap].text;

                this.lst.options[ilstSwap].text = this.lst.options[this.ilstSel].text;
                this.lst.options[ilstSwap].value = this.lst.options[this.ilstSel].value;

                this.lst.options[this.ilstSel].text = strOptSav;
                this.lst.options[this.ilstSel].value = iOptValSav;

                this.SetSelection(ilstSwap);
            }
        }

    </Script>
<%
End Sub

Public Sub Page_RenderContent()
    Const bjsDO_MOVE_UP = "true"
    Const bjsNO_MOVE_UP = "false"

    Dim strbjsMoveUp
    Dim strbjsMoveDown
    '
    ' When DHTML is supported, use the event object to determine move direction.
    ' When not supported, pass a parameter.
    '
    If App_bSupportsIE4DHTML() Then 
        strbjsMoveUp = gstrNONE
        strbjsMoveDown = gstrNONE
    Else
        strbjsMoveUp = bjsDO_MOVE_UP
        strbjsMoveDown = bjsNO_MOVE_UP
    End If

%>
    <Table>
        <TR>
            <TD><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Folder:&nbsp;&nbsp;</Font></TD>
            <TD><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>><%=Session(gstrSESS_FOLDER_NAME)%></Font></TD>
        </TR>
    </Table>
    <BR>
    <Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Conditions:</Font>
    <Table Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD RowSpan=2 ColSpan=3><%Call RenderLstRules()%></TD>
            <TD><Input Type=Button Name=cmdMoveUp Value="  Move Up   " 
                OnClick="lstRuleSequence.MoveRule(<%=strbjsMoveUp%>)" 
                OnDblClick="lstRuleSequence.MoveRule(<%=strbjsMoveUp%>)"></TD>
        </TR>
        <TR>
            <TD VAlign=Top><Input Type=Button Name=cmdMoveDown Value="Move Down" 
                OnClick="lstRuleSequence.MoveRule(<%=strbjsMoveDown%>)" 
                OnDblClick="lstRuleSequence.MoveRule(<%=strbjsMoveDown%>)"></TD>
        </TR>
        <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_RG_I_RULE%>" VALUE="">
        <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_I_RULE%>" VALUE="">
        <TR>
            <TD><Input Type=Button Value=" Add... " OnClick="ValidateCmd('<%=gstrCMD_ADD_RULE%>')"></TD>
            <TD><Input Type=Button Value="Modify..." OnClick="ValidateCmd('<%=gstrCMD_MOD_RULE%>')"></TD>
            <TD><Input Type=Button Value=" Delete " OnClick="ValidateCmd('<%=gstrCMD_DEL_RULE%>')"></TD>
        </TR>
    </Table>
    <HR>
    <Table>
        <TR>
            <TD Width=100 Align=Right><INPUT TYPE="button" VALUE="Submit" OnClick="ValidateCmd('<%=gstrCMD_COMMIT%>')"></TD>
            <TD><INPUT TYPE="button" VALUE="Cancel" OnClick="ValidateCmd('<%=gstrCMD_SEL_FOLDER%>')"></TD>
        </TR>
    </Table>
    <Script>
        var frm = document.<%=gstrFORM_MAIN%>;

        lstRuleSequence = new LstRuleSequence(frm.<%=gstrREQUEST_LST_RULES%>, frm.cmdMoveUp,
                                             frm.cmdMoveDown, frm.<%=gstrREQUEST_HID_RG_I_RULE%>);
    </Script>
<%
End Sub

Private Sub RenderLstRules()
    Dim strOptions
    Dim iRule

    On Error Resume Next
%>
    <Select Name=<%=gstrREQUEST_LST_RULES%> Class=<%=gstrCSS_CLASS_FONT_NORMAL%> 
             OnChange="lstRuleSequence.SetSelection()" Size=10 Style="width:<%=gpxlWIDTH_LST%>px">
<%
    strOptions = gstrNONE

    Call Rule_GetRuleList()

    If Err.Number = gerrNONE Then
        For iRule = LBound(Rule_rgstrCondition) To UBound(Rule_rgstrCondition)
            strOptions = strOptions & "<Option Value='" & Rule_rgiRule(iRule) & "'>" & Rule_rgstrCondition(iRule)
        Next
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_DISPLAY_RULE_LIST, Err.Number, Err.Description)

        Err.Clear
    End If

    Response.Write strOptions
%>
    </Select>
<%
End Sub
%>
