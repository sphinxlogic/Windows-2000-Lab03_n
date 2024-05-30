<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="CDO.inc"-->
<%
'<!--Rules Sample Application-->
'<!--SelFolder.asp : Folder Selection asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' ExchLogon.asp prepares UI for selecting a server and mailbox.
'
    Dim strCtlFocus

    On Error Resume Next

    strCtlFocus = gstrREQUEST_TXT_EXCH_SERVER

    Call App_RenderPage(gstrPAGE_HEADING_EXCH_SERVER_LOGON, strCtlFocus)

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
%>
    <SCRIPT LANGUAGE="JavaScript">
        function ValidateCmd(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>;
            var bValidCmd;

            if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_EXCH_SERVER%>.value, 
                                    '<%=gstrMSG_REPLACE_EXCH_SERVER%>',
                                    frm.<%=gstrREQUEST_TXT_EXCH_SERVER%>)) {
                bValidCmd = false;
            }
            else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_MAILBOX%>.value, 
                                    '<%=gstrMSG_REPLACE_MAILBOX%>',
                                    frm.<%=gstrREQUEST_TXT_MAILBOX%>)) {
                bValidCmd = false;
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }
    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()
    Dim strServer
    Dim objRenderApp

    strServer = Session(gstrSESS_EXCH_SERVER)

    If Len(strServer) = 0 Then
        strServer = CDO_strExchServer()
    End If

%>
    <TABLE CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Server:</TD>
            <TD><%Call App_ShowInputText(gstrREQUEST_TXT_EXCH_SERVER, App_strHTML(strServer), giTXT_MAX_LEN_EXCH_SERVER, giTXT_SIZE_NORMAL)%></TD>
        </TR>
        <TR>
            <TD>Mailbox:</TD>
            <TD><%Call App_ShowInputText(gstrREQUEST_TXT_MAILBOX, App_strHTML(Session(gstrSESS_MAILBOX)), giTXT_MAX_LEN_MAILBOX, giTXT_SIZE_NORMAL)%></TD>
        </TR>
    </TABLE>
    <BR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><A HRef=javascript:ValidateCmd('<%=gstrCMD_SEL_FOLDER_NEW%>')>Continue to Microsoft Exchange Folder Selection</A></DIV>
<%
End Sub
%>
