<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<%
'<!--Mailbox Maintenance Sample Application-->
'<!--Logon.asp : Logon & root asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Logon.asp Establishes two frames for the application:  one frame for displaying the UI 
' & the other for passing messages or commands to HandleCmds.
'
    On Error Resume Next
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' bTxtEntered:  Returns a boolean indicating whether passed string contains text.
    '
    ' bValidStrLength:  Returns a boolean indicating whether the length of a txtArea exceeds
    ' a max length value.  Unlike text input, txt areas don't have a maxlength property.
    '
    ' strMsgReplace:  Searches the passed string for gchREPLACE & replaces each occurrence w/
    ' an item from the array of substitution values.
    '
    ' ShowError:  Displays the passed msg & sets focus to the passed control.
    '
    ' SetFocus:  Sets focus to the passed control.
    '
    ' txt_OnFocus:  Selects text in the passed control.
    '
    ' txt_OnChange:  Sets the forms dirty flag.
    '
    ' SetWidth:  Sets the width of the passed control to the passed width.
    '
    ' bValidCmdGoToPage:  Verifies the passed page is w/in the paging bounds.
    '
    ' bValidCmdFind:  Verifies entry of selection criteria.
    '
    ' SubmitCommand:  Sets the hidden command value & submits the main form.
    '
%>
    <HTML>
    <HEAD>
    <TITLE><%=gstrPAGE_HEADING_MB_MAINT%></TITLE>

    <SCRIPT LANGUAGE="JavaScript">

        function bTxtEntered(pstr, pstrReplace, pctlFocus, pbSpacesPermitted) {
            var bTxtFound;
            var istr;
            var ch;
            var cstr = pstr.length;
            var bSpacesPermitted = (pbSpacesPermitted == null ? false : pbSpacesPermitted)

            if (cstr == 0) {
                if (pstrReplace != null) {
                    ShowError(strMsgReplace('<%=gstrMSG_ALERT_MUST_BE_ENTERED%>', new Array(pstrReplace)), pctlFocus);
                }

                return false;
            }
            else if (bSpacesPermitted) {
                return true;
            }
            else {
                bTxtFound = false;

                for (istr = 0; istr < cstr; istr++) {
                    ch = pstr.charAt(istr);

                    if ((ch != ' ') && (escape(ch) != '%<%=Hex(gstrANSI_NB_SPACE)%>')) {
                        bTxtFound = true;
                        break;
                    }
                };

                if ((! bTxtFound) && (pstrReplace != null)) {
                    ShowError(strMsgReplace('<%=gstrMSG_ALERT_MUST_BE_ENTERED%>', new Array(pstrReplace)), pctlFocus);
                }

                return bTxtFound;
            }
        }


        function bValidStrLength(pctlFocus, pcchMax, pstrMsgReplace) {
            var cchCtlFocus = pctlFocus.value.length;

            if (cchCtlFocus > pcchMax) {
                ShowError(strMsgReplace('<%=gstrMSG_ALERT_TXTAREA_MAX_EXCEEDED%>', 
                            new Array(pstrMsgReplace, pcchMax.toString(), cchCtlFocus.toString())), pctlFocus);
                return false;
            }
            else {
                return true;
            }
        }

        function strMsgReplace(pstr, prgstrSubstitute) {
            var rgstrSplit;
            var iSplit;
            var istrSubstitute;
            var strMsg;
            var str;

            str = pstr;

            for (istrSubstitute = 0; istrSubstitute < prgstrSubstitute.length; istrSubstitute++) {
                iSplit = str.indexOf("<%=gchREPLACE%>");

                if (iSplit == 0) {
                    str = prgstrSubstitute[istrSubstitute] + str.substring(iSplit + 1, str.length);
                }
                else if (iSplit == str.length - 1) {
                    str = str.substring(0, iSplit) + prgstrSubstitute[istrSubstitute];
                }
                else if (iSplit > 0) {
                    str = str.substring(0, iSplit) + prgstrSubstitute[istrSubstitute] + str.substring(iSplit + 1, str.length);
                }
                else {
                    break;
                }
            }

            return str;
        }

        function ShowError(pstrError, pctlFocus) {
            alert(pstrError);

            if (pctlFocus != null) {
                SetFocus(pctlFocus);
            }
        }
        
        function SetFocus(pctlFocus) {
            if (pctlFocus != null) {
                var strCtlType = pctlFocus.type;

                pctlFocus.focus();

                if ((strCtlType == "text") | (strCtlType == "textarea")) {
                    pctlFocus.select();
                }
            }
        }

        function txt_OnFocus(pctl) {
            pctl.select();
        }


        function txt_OnChange() {
            <%=gstrFRAME_MAIN%>.mbDirty = true;
        }
<%
    '
    ' Use DHTML to size controls.
    '
    If App_bSupportsIE4DHTML() Then
%>

        function SetWidth(pctl, ppxlWidth) {
            if (pctl != null) {
                pctl.style.setAttribute("pixelWidth", ppxlWidth)
            }
        }
<%
    End If
%>

        function bValidCmdGoToPage() {
            var frm = <%=gstrFRAME_MAIN%>.document.<%=gstrFORM_MAIN%>;
            var bValidCmd = false;
            var strCmd = frm.<%=gstrHIDDEN_CMD_GO_TO_PAGE%>.value;
            var cPage = parseInt(frm.<%=gstrHIDDEN_C_PAGE%>.value);
            var iPage = parseInt(frm.<%=gstrHIDDEN_I_PAGE%>.value);
            var varPageGoTo;
            var iPageGoTo;

            if (strCmd == '<%=gstrCMD_GO_TO_PAGE%>') {
                varPageGoTo = frm.<%=gstrTXT_PAGE_GO_TO%>.value;
                iPageGoTo = parseInt(varPageGoTo);

                if (iPageGoTo == varPageGoTo) {
                    bValidCmd = ((iPageGoTo > 0) && (iPageGoTo <= cPage));
                }
                else {
                    bValidCmd = false
                };

                if (bValidCmd) {
                    if (iPage == iPageGoTo) {
                        bValidCmd = false;
                    }
                    else { 
                        iPage = iPageGoTo;
                    }
                }
                else {
                    ShowError(strMsgReplace('<%=gstrMSG_ALERT_PAGE_NO_INVALID%>', new Array('1', cPage))
                                , frm.<%=gstrTXT_PAGE_GO_TO%>);
                };
            }
            else {
                bValidCmd = true;

                iPage = parseInt(frm.<%=gstrHIDDEN_I_PAGE_GO_TO%>.value) 
                        + parseInt((strCmd == '<%=gstrCMD_PREV_PAGE%>' ? -1: 1));

                if (iPage < 1) {
                    iPage = cPage;
                }
                else if (iPage > cPage) {
                    iPage = 1;
                } 
            }

            if (bValidCmd) {
                frm.<%=gstrHIDDEN_I_PAGE_GO_TO%>.value = iPage;
            }

            return bValidCmd;
        }

        function bValidCmdFind(ptxtFind) {

            if (! parent.bTxtEntered(ptxtFind.value, '<%=gstrMSG_REPLACE_SEL_CRITERIA%>', ptxtFind, true)) {
                return false;
            }
            else {
                return true;
            }
        }

        function SubmitCommand(pstrCmd) {
            var frm = <%=gstrFRAME_MAIN%>.document.<%=gstrFORM_MAIN%>;

            frm.<%=gstrREQUEST_CMD%>.value = pstrCmd;
            frm.submit();
        }
    </SCRIPT>
    </HEAD>
    <FRAMESET BORDER=0 FRAMEBORDER=0 FRAMESPACING=0 ROWS="100%,*">
        <FRAME NAME="<%=gstrFRAME_MAIN%>" SRC="<%=gstrASP_SEL_EXCH_SERVER%>" SCROLLING=yes MARGINHEIGHT=5 MARGINWIDTH=5 NoResize>
        <FRAME NAME="<%=gstrFRAME_HANDLE_CMDS%>" SRC="<%=gstrASP_HANDLE_CMDS%>" SCROLLING=no MARGINHEIGHT=0 MARGINWIDTH=0>
    </FRAMESET>
    <BODY  BGCOLOR="<%=ghtmlBG_COLOR%>">
    <FORM>
    </FORM>
    </BODY>
    </HTML>
