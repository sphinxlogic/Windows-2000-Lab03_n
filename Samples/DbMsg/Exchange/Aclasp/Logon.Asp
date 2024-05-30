<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<%
'<!--ACL Sample Application-->
'<!--Logon.asp : Logon & root asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Logon.asp Establishes two frames for the application:  one frame for displaying the UI 
' & the other for passing messages or commands to HandleCmds.
'
    On Error Resume Next
%>
    <HTML>
    <HEAD>
    <TITLE><%=gstrPAGE_HEADING_ACL_MAINT%></TITLE>

    <SCRIPT LANGUAGE="JavaScript">
<%
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' bTxtEntered:  Returns a boolean indicating whether passed string contains text.
    '
    ' strTrim:  Returns a string w/ leading & following spaces trimmed from passed string.
    '
    ' ilstFindVal:  Searches the passed list for the passed value & returns the index of
    ' the list entry matching the search value or iLST_NONE if not found.
    '
    ' bValidStrLength:  Returns a boolean indicating whether the length of a txtArea exceeds
    ' a max length value.  Unlike text input, txt areas don't have a maxlength property.
    '
    ' strReplace:  Searches the passed string for the passed value & replaces each occurrence
    ' w/ the passed substitution value.
    '
    ' strMsgReplace:  Searches the passed string for gchREPLACE & replaces each occurrence w/
    ' an item from the array of substitution values.
    '
    '
    ' ShowError:  Displays the passed msg & sets focus to the passed control.
    '
    ' SetFocus:  Sets focus to the passed control.
    '
    ' txt_OnFocus:  Selects text in the passed control.
    '
    ' bValidCmdGoToPage:  Verifies the passed page is w/in the paging bounds.
    '
    ' SetWidth:  Sets the width of the passed control to the passed width.
    '
    ' SubmitCommand:  Sets the hidden command value & submits the main form.
    '
%>
        var iLST_NONE = -1;

        function bTxtEntered(pstr, pstrMsgReplace, pctlFocus) {
            var istr;
            var str;

            if (pstr.length == 0) {
                ShowError(strMsgReplace('<%=gstrMSG_ALERT_MUST_BE_ENTERED%>', new Array(pstrMsgReplace)), pctlFocus);
                return false;
            }
            else {
                str = strTrim(pstr);

                if (str.length == 0) {
                    ShowError(strMsgReplace('<%=gstrMSG_ALERT_MUST_BE_ENTERED%>', 
                                new Array(pstrMsgReplace)), pctlFocus);
                    return false;
                }
                else {
                    return true;
                }
            }
        }

        function strTrim(pstr) {
            var bFound = false;
            var str = pstr;
            var istr;

            for (istr = 0; istr < str.length; istr++) {
                if (str.charAt(istr) != ' ') {
                    if (istr > 0) {
                        str = str.substring(istr, str.length)
                    };

                    bFound = true;
                    break;
                }
            };

            if (bFound) {
                for (istr = str.length - 1; istr >= 0; istr--) {
                    if (str.charAt(istr) != ' ') {
                        if (istr < str.length - 1) {
                            str = str.substring(0, istr + 1)
                        };
                        break;
                    }
                }
            }
            else {
                str = ''    
            }


            return str;
        }

        function ilstFindVal(pvalFind, plst) {
            var ilstSav = iLST_NONE;
            var ilst;

            for (ilst = 0; ilst < plst.length; ilst++) {
                if (pvalFind == plst[ilst].value) {
                    ilstSav = ilst;
                    break;
                }
            }

            return ilstSav;
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

        function strReplace(pstr, pstrFind, pstrReplace) {
            var str;
            var istr;
            var istrFind;
            var cchReplace;
            var cchFind;

            str = pstr;
            cchReplace = pstrReplace.length;
            cchFind = psrtFind.length;
            istr = 0;
            istrFind = str.indexOf(pstrFind, istr);

            while (istrFind >= 0) {
                if (istrFind == 0) {
                    str = pstrReplace + str.substring(istrFind + cchFind, str.length);
                }
                else if (istrFind == str.length - 1) {
                    str = str.substring(0, istrFind) + pstrReplace;
                    break;
                }
                else {
                    str = str.substring(0, istrFind) + pstrReplace + str.substring(istrFind + cchFind, str.length);
                }
                
                istr = istrFind + cchReplace;

                istrFind = str.indexOf(pstrFind, istr);
            };

            return str;
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
        function SubmitCommand(pstrCmd) {
            var frm = <%=gstrFRAME_MAIN%>.document.<%=gstrFORM_MAIN%>;

            frm.<%=gstrREQUEST_CMD%>.value = pstrCmd;
            frm.submit();
        }

    </SCRIPT>
    </HEAD>
    <FRAMESET BORDER=0 FRAMEBORDER=0 FRAMESPACING=0 ROWS="100%,*">
        <FRAME NAME="<%=gstrFRAME_MAIN%>" SRC="<%=gstrASP_EXCH_LOGON%>" SCROLLING=yes MARGINHEIGHT=5 MARGINWIDTH=5 NoResize>
        <FRAME NAME="<%=gstrFRAME_HANDLE_CMDS%>" SRC="<%=gstrASP_HANDLE_CMDS%>" SCROLLING=no MARGINHEIGHT=0 MARGINWIDTH=0>
    </FRAMESET>
    <BODY  BGCOLOR="<%=ghtmlBG_COLOR%>">
    <FORM>
    </FORM>
    </BODY>
    </HTML>
