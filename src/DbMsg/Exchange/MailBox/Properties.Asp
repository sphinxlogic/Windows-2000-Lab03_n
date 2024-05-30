<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ADS.inc"-->
<%
'<!--Mailbox Maintenance Sample Application-->
'<!--Properties.asp : Properties asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Properties.asp provides UI for adding\modifying mailbox\custom recipient properties.
'
    Const miTD_COL_1_WIDTH = 75
    Const miTD_COL_2_WIDTH = 170
    Const miTD_COL_3_WIDTH = 75

    Const miTXT_POSTAL_ADDRESS_COL = 22
    Const miTXT_NOTES_COL = 78

    Dim mbIsMailbox
    Dim mbCmdAdd
    Dim mstrCmdSubmit
    Dim miTabIndex

    Dim strAddressType
    Dim strImg
    Dim strHeading
    Dim strCmd
    Dim strCtlFocus

    On Error Resume Next

    mbCmdAdd = Not (CStr(Session(gstrSESS_CMD)) = gstrCMD_PROPERTIES)
    '
    ' Get property values if modifying
    '
    If Not mbCmdAdd Then
        Call ADS_Get(CStr(Session(gstrSESS_ADS_PATH)))
    End If
    '
    ' Check for errors retrieving property data.
    '
    If Err.Number = gErrNone Then
        '
        ' Set module level variables & heading.
        '
        If mbCmdAdd Then
            mbIsMailbox = CBool(Session(gstrSESS_B_IS_MAILBOX))
            mstrCmdSubmit = gstrCMD_DO_ADD

            If mbIsMailbox Then
                strAddressType = gstrREPLACE_MB
            Else
                strAddressType = gstrREPLACE_CR
            End If

            strHeading = Replace(gstrHEADING_ADD, gchREPLACE, strAddressType)
        Else
            mbIsMailbox = (ADS_strObjClass = gstrADS_CLASS_MB)
            Session(gstrSESS_B_IS_MAILBOX) = mbIsMailbox
            mstrCmdSubmit = gstrCMD_DO_MOD

            strHeading = ADS_strDispName
        End If

        If mbIsMailbox Then
            strImg = gstrIMG_MB
        Else
            strImg = gstrIMG_CR
        End If

        strCtlFocus = gstrREQUEST_TXT_NAME_FIRST

        Call App_RenderPage(strImg, strHeading, strCtlFocus)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_DISPLAY_PROPERTIES, Err.Number, Err.Description)
    End If

Public Sub Page_RenderJavaScript()
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' bValidCmdSubmit:  Validates the submit command.
    '
    ' gstrREQUEST_TXT_DISP_NAME_OnChange:  Sets dirty flag for disp name fld.
    '
    ' gstrREQUEST_TXT_NAME_FIRST_OnChange:  Updates disp name fld unless dirty flag is set.
    '
    ' gstrREQUEST_TXT_NAME_LAST_OnChange:  Updates disp name fld unless dirty flag is set.
    '
    ' UpdateDispName:  Updates disp name w/ first & last name values.
    '
%>
    <SCRIPT LANGUAGE="JavaScript">
        var mbDirty = false;
        var mbDispNameDirty = false;

        function ValidateCmd(pstrCmd) {
            var bValidCmd;
            var strlstExchObjSel;
            var strCmd = pstrCmd;

            if (strCmd == '<%=mstrCmdSubmit%>') {
                bValidCmd = bValidCmdSubmit();

                if (bValidCmd && ! mbDirty) {
                    strCmd = '<%=gstrCMD_MAINTENANCE%>';
                }
            }
            else {
                bValidCmd = true;
            }

            if (bValidCmd) {
                parent.SubmitCommand(strCmd);
            }
        }

        function bValidCmdSubmit() {
            var frm = document.<%=gstrFORM_MAIN%>;
            var iOPT_NT_ACCT_NEW = 1;

            if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_DISP_NAME%>.value,
                                        '<%=gstrMSG_REPLACE_DISP_NAME%>',
                                        frm.<%=gstrREQUEST_TXT_DISP_NAME%>)) {
                return false;
            }
<%
        If mbCmdAdd Then
            '
            ' Alias is only displayed in an input fld for adds
            '
%>
            else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_ALIAS%>.value,
                                        '<%=gstrMSG_REPLACE_ALIAS%>',
                                        frm.<%=gstrREQUEST_TXT_ALIAS%>)) {
                return false;
            }
<%
        End If

        If mbIsMailbox Then
            '
            ' Validations for mailbox object
            '
            If mbCmdAdd Then
                '
                ' For adds require entry of nt account.
                '
%>
                else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_NT_ACCT%>.value,
                                            '<%=gstrMSG_REPLACE_NT_ACCT%>',
                                            frm.<%=gstrREQUEST_TXT_NT_ACCT%>)) {
                    return false;
                }
<%
            Else
                '
                ' For mods, nt account is only required when an account is added.
                '
%>
                else if ((frm.<%=gstrREQUEST_OPT_NT_ACCT%>[iOPT_NT_ACCT_NEW].checked) 
                                ? (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_NT_ACCT%>.value,
                                            '<%=gstrMSG_REPLACE_NT_ACCT%>',
                                            frm.<%=gstrREQUEST_TXT_NT_ACCT%>))
                                : false) {
                    return false;
                }
<%
            End If
        Else ' Custom Recipient
            '
            ' Validations for internet custom recipient object
            '
%>
            else if (! parent.bTxtEntered(frm.<%=gstrREQUEST_TXT_EMAIL_ADDRESS%>.value,
                                        '<%=gstrMSG_REPLACE_EMAIL_ADDRESS%>',
                                        frm.<%=gstrREQUEST_TXT_EMAIL_ADDRESS%>)) {
                return false;
            }
<%
        End If
%>
            else if (! parent.bValidStrLength(frm.<%=gstrREQUEST_TXT_POSTAL_ADDRESS%>, <%=giTXT_MAX_LEN_POSTAL_ADDRESS%>, '<%=gstrMSG_REPLACE_ADDRESS%>')) {
                return false;
            }
            else if (! parent.bValidStrLength(frm.<%=gstrREQUEST_TXT_NOTES%>, <%=giTXT_MAX_LEN_NOTES%>, '<%=gstrMSG_REPLACE_NOTES%>')) {
                return false;
            }
            else {
                return true;
            }
        }

        function <%=gstrREQUEST_TXT_DISP_NAME%>_OnChange() {
            mbDispNameDirty = true;

            parent.txt_OnChange();
        }

        function <%=gstrREQUEST_TXT_NAME_FIRST%>_OnChange() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if (! mbDispNameDirty) {
                UpdateDispName();
            }

            parent.txt_OnChange();
        }

        function <%=gstrREQUEST_TXT_NAME_LAST%>_OnChange() {
            var frm = document.<%=gstrFORM_MAIN%>;

            if (! mbDispNameDirty) {
                UpdateDispName();
            }

            parent.txt_OnChange();
        }

        function UpdateDispName() {
            var frm = document.<%=gstrFORM_MAIN%>;

            frm.<%=gstrREQUEST_TXT_DISP_NAME%>.value = frm.<%=gstrREQUEST_TXT_NAME_FIRST%>.value 
                                                        + ' '
                                                        + frm.<%=gstrREQUEST_TXT_NAME_LAST%>.value                   
        }
    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()
    Call RenderNameProps()

    If mbIsMailbox Then
        '
        ' Render NT Account info for mailbox
        '
        Call RenderNTProps()
    End If

    Call RenderGeneralProps()
    Call RenderPhoneNumberProps()
    '
    ' Notes are used by all object types
    '
    Call RenderNotes()

    Call RenderCmds()
End Sub

Private Sub RenderNameProps()
%>
    <DIV Class=<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>>Name</DIV>
    <Table Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
<%
    '
    ' Render user name
    '
%>
    <TR>
        <TD ALIGN=Left Width=<%=miTD_COL_1_WIDTH%>>First:</TD>
        <TD Width=<%=miTD_COL_2_WIDTH%>><% Call App_ShowInputText(gstrREQUEST_TXT_NAME_FIRST, _
                                                                    App_strHTML(ADS_strNameFirst), _
                                                                    giTXT_MAX_LEN_NORMAL, _
                                                                    giTXT_SIZE_NAME_FIRST, _
                                                                    iTabIndexIncrement(), _
                                                                    gbDO_ON_CHANGE)%>
            Initials:
            <% Call App_ShowInputText(gstrREQUEST_TXT_NAME_MID_INITIAL, _
                                        App_strHTML(ADS_strNameMidInitial), _
                                        giTXT_MAX_LEN_NAME_MID_INITIAL, _
                                        giTXT_SIZE_NAME_MID_INITIAL, _
                                        iTabIndexIncrement(), _
                                        gbNO_ON_CHANGE)%>
        </TD>
        <TD ALIGN=Left Width=<%=miTD_COL_3_WIDTH%>>Last:</TD>
        <TD><% Call App_ShowInputText(gstrREQUEST_TXT_NAME_LAST, _
                                        App_strHTML(ADS_strNameLast), _
                                        giTXT_MAX_LEN_NORMAL, _
                                        giTXT_SIZE_NORMAL, _
                                        iTabIndexIncrement(), _
                                        gbDO_ON_CHANGE)%></TD>
    </TR>
<%
    '
    ' Display Name & Alias
    '
%>
    <TR>
        <TD ALIGN=Left Width=<%=miTD_COL_1_WIDTH%>>Display:</TD>
        <TD Width=<%=miTD_COL_2_WIDTH%>><% Call App_ShowInputText(gstrREQUEST_TXT_DISP_NAME, _
                                                                    App_strHTML(ADS_strDispName), _
                                                                    giTXT_MAX_LEN_DISP_NAME, _
                                                                    giTXT_SIZE_NORMAL, _
                                                                    iTabIndexIncrement(), _
                                                                    gbDO_ON_CHANGE)%></TD>
        <TD ALIGN=Left Width=<%=miTD_COL_3_WIDTH%>>Alias:</TD>
        <TD>
<%
        If mbCmdAdd Then
            Call App_ShowInputText(gstrREQUEST_TXT_ALIAS, _
                                        App_strHTML(ADS_strAlias), _
                                        giTXT_MAX_LEN_NORMAL, giTXT_SIZE_NORMAL, _
                                        iTabIndexIncrement(), gbNO_ON_CHANGE)
        Else
            '
            ' For mods, alias - which is actually the common-name, may not be modified.
            '
%>
            <%=App_strHTML(ADS_strAlias)%>
<%
        End If
%>
        </TD>
    </TR>
<%
    If Not mbIsMailbox Then
        '
        ' Render Internet info for internet custom recipient
        '
%>
        <TR>
            <TD ALIGN=Left>E-mail:</TD>
            <TD ColSpan=3><% Call App_ShowInputText(gstrREQUEST_TXT_EMAIL_ADDRESS, _
                                                    App_strHTML(ADS_strEmailAddr), _
                                                    giTXT_MAX_LEN_EMAIL_ADDRESS, _
                                                    giTXT_SIZE_EMAIL_ADDRESS, _
                                                    iTabIndexIncrement(), _
                                                    gbNO_ON_CHANGE)%></TD>
        </TR>
<%
    End If
%>
    </TABLE>
<%
End Sub

Private Sub RenderNTProps()
    Dim strNTAcct

    strNTAcct = App_strHTML(ADS_strNTAcct)
%>
    <HR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>><NoBR>
        <Font CLASS=<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>>Windows NT Account:  </Font>
        <Input Type=Radio Name=<%=gstrREQUEST_OPT_NT_ACCT%> Value=<%=gstrREQUEST_OPT_NT_ACCT_OLD%> Checked Class=<%=gstrCSS_CLASS_FONT_NORMAL%> TabIndex=<%=iTabIndexIncrement()%>>Use existing account
        <Input Type=Radio Name=<%=gstrREQUEST_OPT_NT_ACCT%> Value=<%=gstrREQUEST_OPT_NT_ACCT_NEW%> TabIndex=<%=iTabIndexIncrement()%>>Create new account
    </NoBr></DIV>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD ALIGN=Left Width=<%=miTD_COL_1_WIDTH%>>Account:</TD>
            <TD Width=<%=miTD_COL_2_WIDTH%>><% Call App_ShowInputText(gstrREQUEST_TXT_NT_ACCT, _
                                                                        strNTAcct, _
                                                                        giTXT_MAX_LEN_NT_ACCT, _
                                                                        giTXT_SIZE_NORMAL, _
                                                                        iTabIndexIncrement(), _
                                                                        gbNO_ON_CHANGE)%>
                <INPUT TYPE=Hidden NAME=<%=gstrREQUEST_HID_NT_ACCT%> Value="<%=strNTAcct%>"></TD>
            <TD ALIGN=Left Width=<%=miTD_COL_3_WIDTH%>>Password:</TD>
            <TD><Input Type='Password' Name='<%=gstrREQUEST_TXT_NT_PASSWORD%>' 
                    Id='id<%=gstrREQUEST_TXT_NT_PASSWORD%>' 
                    MaxLength=<%=giTXT_MAX_LEN_NT_PASSWORD%> 
                    TabIndex=<%=iTabIndexIncrement()%> 
                    OnFocus='parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_NT_PASSWORD%>)'></TD>
        </TR>
    </TABLE>
<%
End Sub

Private Sub RenderGeneralProps()
'
' In RenderGeneralProps, the taborder is manipulated so that tabbing occurs down columns.
'
%>
    <HR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>>General Information</DIV>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD ALIGN=Left VAlign=Top Width=<%=miTD_COL_1_WIDTH%> RowSpan=2>Address:</TD>
            <TD  Width=<%=miTD_COL_2_WIDTH%> RowSpan=2>
                <TextArea Name=<%=gstrREQUEST_TXT_POSTAL_ADDRESS%> 
                    Rows=3 Cols=<%=miTXT_POSTAL_ADDRESS_COL%>  Class=<%=gstrCSS_CLASS_FONT_NORMAL%>
                    TabIndex=<%=miTabIndex + 1%> OnChange='parent.txt_OnChange()'
                    OnFocus='parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_POSTAL_ADDRESS%>)'
                    ><%=ADS_strPostalAddress%></TextArea></TD>
            <TD ALIGN=Left VAlign=Top  Width=<%=miTD_COL_3_WIDTH%>>Title:</TD>
            <TD VAlign=Top><% Call App_ShowInputText(gstrREQUEST_TXT_TITLE, _
                                                        App_strHTML(ADS_strTitle), _
                                                        giTXT_MAX_LEN_NORMAL, _
                                                        giTXT_SIZE_NORMAL, _
                                                        (miTabIndex + 6), _
                                                        gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>Company:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_COMPANY, _
                                            App_strHTML(ADS_strCompany), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 7), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>City:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_CITY, _
                                            App_strHTML(ADS_strCity), _
                                            giTXT_MAX_LEN_CITY, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 2), _
                                            gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left>Department:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_DEPT, _
                                            App_strHTML(ADS_strDept), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 8), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>State:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_STATE, _
                                            App_strHTML(ADS_strState), _
                                            giTXT_MAX_LEN_STATE, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 3), _
                                            gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left>Office:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_OFFICE, _
                                            App_strHTML(ADS_strOffice), _
                                            giTXT_MAX_LEN_OFFICE, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 9), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>Zip Code:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_POSTAL_CODE, _
                                            App_strHTML(ADS_strPostalCode), _
                                            giTXT_MAX_LEN_POSTAL_CODE, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 4), _
                                            gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left>Assistant:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_ASSISTANT, _
                                            App_strHTML(ADS_strAssistant), _
                                            giTXT_MAX_LEN_ASSISTANT, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 10), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>Country:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_COUNTRY, _
                                            App_strHTML(ADS_strCountry), _
                                            giTXT_MAX_LEN_COUNTRY, _
                                            giTXT_SIZE_NORMAL, _
                                            (miTabIndex + 5), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
    </TABLE>
<%
    miTabIndex = miTabIndex + 10
End Sub

Private Sub RenderPhoneNumberProps()
%>
    <HR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>>Phone Numbers</DIV>
    <TABLE Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD ALIGN=Left Width=<%=miTD_COL_1_WIDTH%> >Business:</TD>
            <TD Width=<%=miTD_COL_2_WIDTH%> ><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_BUS, _
                                                                        App_strHTML(ADS_strPhoneBus), _
                                                                        giTXT_MAX_LEN_NORMAL, _
                                                                        giTXT_SIZE_NORMAL, _
                                                                        iTabIndexIncrement(), _
                                                                        gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left Width=<%=miTD_COL_3_WIDTH%> >Home:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_HOME, _
                                            App_strHTML(ADS_strPhoneHome), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>Business 2:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_2_BUS, _
                                            App_strHTML(ADS_strPhone2Bus), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left>Home 2:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_2_HOME, _
                                            App_strHTML(ADS_strPhone2Home), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>Fax:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_FAX, _
                                            App_strHTML(ADS_strPhoneFax), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left>Mobile:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_MOBILE, _
                                            App_strHTML(ADS_strPhoneMobile), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
        <TR>
            <TD ALIGN=Left>Assistant:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_ASSISTANT, _
                                            App_strHTML(ADS_strPhoneAssistant), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
            <TD ALIGN=Left>Pager:</TD>
            <TD><% Call App_ShowInputText(gstrREQUEST_TXT_PHONE_PAGER, _
                                            App_strHTML(ADS_strPhonePager), _
                                            giTXT_MAX_LEN_NORMAL, _
                                            giTXT_SIZE_NORMAL, _
                                            iTabIndexIncrement(), _
                                            gbNO_ON_CHANGE)%></TD>
        </TR>
    </Table>
<%
End Sub

Private Sub RenderNotes()
%>
    <HR>
    <DIV CLASS=<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>>Notes</DIV>
    <TextArea Name=<%=gstrREQUEST_TXT_NOTES%> Rows=6 Cols=<%=miTXT_NOTES_COL%>  Class=<%=gstrCSS_CLASS_FONT_NORMAL%> 
        TabIndex=<%=iTabIndexIncrement()%>  OnChange='parent.txt_OnChange()'
        OnFocus='parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_TXT_NOTES%>)'
        ><%=ADS_strNotes%></TextArea>
<%
End Sub

Private Sub RenderCmds()
%>
    <HR>
    <Table>
    <TR>
        <TD Width=<%=miTD_COL_1_WIDTH + miTD_COL_2_WIDTH%> Align=Right><INPUT TYPE="button" VALUE="Submit" TabIndex=<%=iTabIndexIncrement()%> OnClick="ValidateCmd('<%=mstrCmdSubmit%>')"></TD>
        <TD><INPUT TYPE="button" VALUE="Cancel" TabIndex=<%=iTabIndexIncrement()%> OnClick="ValidateCmd('<%=gstrCMD_MAINTENANCE%>')"></TD>
    </TR>
    </Table>
<%
End Sub

Private Function iTabIndexIncrement()

    If IsEmpty(miTabIndex) Then
        miTabIndex = 1
    Else
        miTabIndex = miTabIndex + 1
    End If

    iTabIndexIncrement = miTabIndex

End Function
%>