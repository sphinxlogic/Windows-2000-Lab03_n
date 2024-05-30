<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="CDO.inc"-->
<%
'<!--Rule Sample Application-->
'<!--SelFolder.asp : Folder Selection asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' SelFolder.asp prepares UI for selecting a folder for Rule maintenance.
'
    Dim strCtlFocus

    On Error Resume Next
    '
    ' Verify cdo session
    '
    Call App_CheckSession()

    strCtlFocus = gstrREQUEST_LST_BRANCH

    Call App_RenderPage(gstrPAGE_HEADING_FOLDER_SEL, strCtlFocus)

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdGoToBranchLevel:  Validates the GoToBranchLevel command.
    '
    ' ShowRules:  Prepares hidden fields identifying the selected folder & calls ValidateCmd
    ' to show the Rules.
    '
    ' ShowSubFolders:  Prepares hidden fields identifying the selected folder & calls
    ' ValidateCmd to expand the folder.
    '
    ' GoToBranchLevel:  Prepares hidden field identify the branch level to return to & calls
    ' ValidateCmd.
    '
%>
    <SCRIPT LANGUAGE="JavaScript">
        function ValidateCmd(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>;
            var bValidCmd = false;

            if (pstrCmd == '<%=gstrCMD_GO_TO_BRANCH_LEVEL%>') {
                bValidCmd = bValidCmdGoToBranchLevel();
            }
            else if (pstrCmd == '<%=gstrCMD_SEL_FOLDER_GO_TO_PAGE%>') {
                bValidCmd = parent.bValidCmdGoToPage();
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }

        function bValidCmdGoToBranchLevel() {
            if (document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL%>.value 
                        < 0) {
                parent.ShowError('<%=gstrMSG_ALERT_ALREADY_AT_TOP%>');
                return false;
            }
            else {
                return true;
            }
        }

        function ShowRules(pstrFolderName, pstrFolderID) {
            document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_HID_STR_FOLDER_ID%>.value = pstrFolderID;
            document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_HID_STR_FOLDER_NAME%>.value = pstrFolderName;

            ValidateCmd('<%=gstrCMD_RULES_MAINT_NEW%>');
        }

        function ShowSubFolders(pstrFolderName, pstrFolderID) {
            document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_HID_STR_FOLDER_ID%>.value = pstrFolderID;
            document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_HID_STR_FOLDER_NAME%>.value = pstrFolderName;

            ValidateCmd('<%=gstrCMD_EXPAND_FOLDER%>');
        }

        function GoToBranchLevel(piBranchLevel) {
            document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL%>.value = piBranchLevel;

            ValidateCmd('<%=gstrCMD_GO_TO_BRANCH_LEVEL%>');
        }
    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()
    Const pxlWIDTH_LST_BRANCH = 200

    Dim strError
    Dim strErrDesc
    Dim errNumber
    Dim iBranchFolderLast
    Dim rgstrBranchFolderID
    Dim rgstrBranchFolderName
    Dim rgstrBranchFolderPage

    rgstrBranchFolderID = Session(gstrSESS_RG_BRANCH_FOLDER_ID)
    rgstrBranchFolderName = Session(gstrSESS_RG_BRANCH_FOLDER_NAME)
    rgstrBranchFolderPage = Session(gstrSESS_RG_BRANCH_FOLDER_PAGE)

    iBranchFolderLast = UBound(rgstrBranchFolderID)
    '
    ' Display stores when at the branch root.
    '
    If iBranchFolderLast = giBRANCH_ROOT Then
        Call CDO_GetStores(CInt(rgstrBranchFolderPage(iBranchFolderLast)))
    Else
        Call CDO_GetFolders(CStr(rgstrBranchFolderID(iBranchFolderLast)), CInt(rgstrBranchFolderPage(iBranchFolderLast)))
    End If

    If err.Number = gerrNONE Then

        rgstrBranchFolderPage(iBranchFolderLast) = CDO_iPage
        Session(gstrSESS_RG_BRANCH_FOLDER_PAGE) = rgstrBranchFolderPage
%>
        <Table>
            <TR>
                <TD><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Look in:</Font></TD>
                <TD><Select Name=<%=gstrREQUEST_LST_BRANCH%> Class=<%=gstrCSS_CLASS_FONT_NORMAL%> Size=1
                        OnChange="GoToBranchLevel(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_BRANCH%>.selectedIndex)">
<%
                    Call RenderFolderBranch(rgstrBranchFolderName)
%>
                    </Select>
                    <A HRef="JavaScript:GoToBranchLevel(<%=(iBranchFolderLast - 1)%>)"><Img Src="<%=gstrIMG_UP_ONE_LEVEL%>" Height=20 Width=20 Alt="<%=gstrALT_UP_ONE_LEVEL%>" Border=1 Align="top"></A></TD>
            </TR>
            <TR>
                <TD><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Folders:</Font></TD>                
<%
    '
    ' Display paging controls only if there are multiple pages
    '
                If CDO_cPage > 1 Then
%>
                    <TD Align=Right>
<%
                    Call App_RenderPaging(gstrCMD_SEL_FOLDER_GO_TO_PAGE, CDO_iPage, CDO_cPage _
                                            , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_PREV, gstrMSG_REPLACE_FOLDERS)) _
                                            , App_strReplace(gstrALT_GO_TO_PAGE, gchREPLACE, Array(gstrMSG_REPLACE_NEXT, gstrMSG_REPLACE_FOLDERS)))
%>
                    </TD>
<%
                End If
%>
        </Table>

        <Div Class=<%=gstrCSS_CLASS_FONT_NORMAL%> Style="Overflow:auto; Height:150pt; Width:210pt; Background:#FFFFFF; Border:1pt Black Solid">
<%
            Call RenderFolderList()
%>
        </Div>
<%
    Else
        strError = gstrMSG_ALERT_CANT_DISPLAY_SEL_FOLDER
        errNumber = Err.Number
        strErrDesc = Err.Description

        Err.Clear
    End If
%>
    <BR>
    <A HRef=javascript:ValidateCmd('<%=gstrCMD_EXCH_LOGON%>')><Font CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>Return to Microsoft Exchange Server Logon</Font></A>
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_STR_FOLDER_ID%>">
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_STR_FOLDER_NAME%>">
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL%>">
<%
    If App_bSupportsIE4DHTML() Then
        '
        ' Use DHTML to size ctls.
        '
%>
        <Script>
            parent.SetWidth(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_BRANCH%>, <%=pxlWIDTH_LST_BRANCH%>)
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

Private Sub RenderFolderBranch(prgstrBranchFolderName)
'
' RenderFolderBranch displays folder branch levels.  Each level is indented from previous
' levels.
'
    Const cCH_INDENT_SIZE = 2

    Dim iBranchFolder
    Dim iBranchFolderMax
    Dim strSelOption
    Dim strFolderNameIndented
    '
    ' Display each level of the branch.
    '
    iBranchFolderMax = UBound(prgstrBranchFolderName)

    For iBranchFolder = LBound(prgstrBranchFolderName) To iBranchFolderMax
        If iBranchFolder = iBranchFolderMax Then
            strSelOption = gstrHTML_OPTION_SEL
        End If

        strFolderNameIndented = Space((iBranchFolder + 1) * cCH_INDENT_SIZE) & prgstrBranchFolderName(iBranchFolder)
%>
        <Option <%=strSelOption%>><%=App_strHTML(strFolderNameIndented)%>
<%
    Next
End Sub

Private Sub RenderFolderList()
'
' RenderFolderList displays the list of folders for the current position in the folder branch.
'
    Dim iFolder

    If CDO_cFolders > 0 Then
        For iFolder = LBound(CDO_rgstrFolderID) To UBound(CDO_rgstrFolderID)
            '
            ' Display folder entries
            '
            Call RenderFolderEntry(CDO_rgstrFolderID(iFolder), CDO_rgstrFolderName(iFolder)_
                                    , CDO_rgbFolderExpands(iFolder), CDO_rgbFolderOwner(iFolder))
        Next
    End If
End Sub

Private Sub RenderFolderEntry(pstrFolderID, pstrFolderName, pbFolderExpands, pbFolderRuleAvail)
    Dim strFolderID
    Dim strFolderName
    Dim strImgAlt
    Dim strImgSrc
    Dim strLinkRuleMaint
    Dim strLinkRuleMaintEnd
    Dim strLinkImg
    Dim strLinkImgEnd

    strFolderID = App_strHTML(pstrFolderID)
    strFolderName = App_strHTML(pstrFolderName)
    '
    ' Set up link for expanding folder
    '
    If pbFolderExpands Then
        strImgSrc = gstrIMG_EXPAND_FOLDER
        strImgAlt = "Alt='" & gstrALT_EXPAND & "'"
        strLinkImg = "<A HRef=""JavaScript:ShowSubFolders('" & strFolderName & "', '" & strFolderID & "')"">"
        strLinkImgEnd = "</A>"
    Else
        strImgSrc = gstrIMG_FOLDER
        strImgAlt = gstrNONE
        strLinkImg = gstrNONE
        strLinkImgEnd = gstrNONE
    End If
    '
    ' Set up link for maintaining Rule
    '
    If pbFolderRuleAvail Then
        strLinkRuleMaint = "<A HRef=""JavaScript:ShowRules('" & strFolderName & "', '" & strFolderID & "')"">"
        strLinkRuleMaintEnd = "</A>"
    Else
        strLinkRuleMaint = gstrNONE
        strLinkRuleMaintEnd = gstrNONE
    End If
%>
        <%=strLinkImg%>
            <Img Src="<%=strImgSrc%>" Height=20 Width=20 Align=Top <%=strImgAlt%> Border=No Align="top"><%=strLinkImgEnd%>
        <%=strLinkRuleMaint%>
            <Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>><%=strFolderName%></Font>
        <%=strLinkRuleMaintEnd%><BR>
<%
End Sub
%>
