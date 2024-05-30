<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<%
'<!--Distribution List Maintenance Sample Application-->
'<!--SelExchServer.asp : Exchange Server Selection asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' SelExchServer contains UI for selecting an Exchange Server.
'
    Dim strCtlFocus

    On Error Resume Next

    strCtlFocus = gstrREQUEST_TXT_ENTERPRISE

    Call App_RenderPage(gstrNONE, gstrPAGE_HEADING_EXCH_SERVER_SEL, strCtlFocus)

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

            if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_ENTERPRISE%>.value, 
                                    '<%=gstrMSG_REPLACE_ENTERPRISE%>',
                                    frm.<%=gstrREQUEST_TXT_ENTERPRISE%>)) {
                bValidCmd = false;
            }
            else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_SITE%>.value, 
                                    '<%=gstrMSG_REPLACE_SITE%>',
                                    frm.<%=gstrREQUEST_TXT_SITE%>)) {
                bValidCmd = false;
            }
            else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_SERVER%>.value, 
                                    '<%=gstrMSG_REPLACE_SERVER%>',
                                    frm.<%=gstrREQUEST_TXT_SERVER%>)) {
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
    Dim strEnterprise
    Dim strSite
    Dim strServer
    Dim objRenderApp

    On Error Resume Next
    '
    ' If OWA is installed, get the Server settings from the registry.
    '
    Set objRenderApp = Server.CreateObject("AMHTML.Application")

    If Err = 0 Then
        '
        ' Get server data from the registry.
        '
        objRenderApp.LoadConfiguration 1, "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\MSExchangeWeb\Parameters"

        If Err.Number = gerrNONE Then
            strEnterprise    = objRenderApp.ConfigParameter("Enterprise")
            strSite   = objRenderApp.ConfigParameter("Site")
            strServer = objRenderApp.ConfigParameter("Server")
        End If
    End If
    Err.Clear
%>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Enterprise:</TD>
            <TD><INPUT NAME="<%=gstrREQUEST_TXT_ENTERPRISE%>" TYPE="text" SIZE=15 VALUE="<%=App_strHTML(strEnterprise)%>" OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_ENTERPRISE%>)"></TD>
        </TR>
        <TR>
            <TD>Site:</TD>
            <TD><INPUT NAME="<%=gstrREQUEST_TXT_SITE%>" TYPE="text" SIZE=15 VALUE="<%=App_strHTML(strSite)%>" OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SITE%>)"></TD>
        </TR>
        <TR>
            <TD>Server:</TD>
            <TD><INPUT NAME="<%=gstrREQUEST_TXT_SERVER%>" TYPE="text" SIZE=15 VALUE="<%=App_strHTML(strServer)%>" OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_SERVER%>)"></TD>
        </TR>
    </TABLE>
    <BR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><A HRef=javascript:ValidateCmd('<%=gstrCMD_DL_MAINT_NEW%>')>Continue to Distribution List Maintenance</A></DIV>
    <SCRIPT LANGUAGE="JavaScript">
        parent.SetFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_ENTERPRISE%>)
    </SCRIPT>
<%
End Sub
%>
