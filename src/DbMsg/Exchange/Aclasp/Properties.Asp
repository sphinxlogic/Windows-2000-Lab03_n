<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<%
Option Explicit
%>
<!--#include file="Constants.inc"-->
<!--#include file="App.inc"-->
<!--#include file="ACL.inc"-->
<!--#include file="CDO.inc"-->
<%
'<!--ACL Sample Application-->
'<!--Properties.asp : ACL Member Properties asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Properties.asp prepares UI for modifying rights of an acl member.
'
    Const miOPT_NONE = 0
    Const miOPT_OWN = 1
    Const miOPT_ALL = 2
    Const mstrLST_CONTACTS = "lstContacts"

    Dim strCtlFocus
    Dim strHeading
    Dim strIDAclMember

    Dim mbContactRightsDisabled
    Dim mbIsOwner
    Dim mrgstrChk

    On Error Resume Next
    '
    ' Verify cdo session
    '
    Call App_CheckSession()
    '
    ' Set module level variables
    '
    strIDAclMember = CStr(Session(gstrSESS_ACL_MEMBER_ID))

    mbContactRightsDisabled = (strIDAclMember = gstrACL_ACE_ID_DEFAULT) _
                                Or (strIDAclMember = gstrACL_ACE_ID_ANONYMOUS)
    mbIsOwner = CBool(Session(gstrSESS_IS_OWNER))
    mrgstrChk = Array(gstrREQUEST_CHK_CREATE_ITEMS, gstrREQUEST_CHK_FOLDER_OWNER _
                        , gstrREQUEST_CHK_READ_ITEMS, gstrREQUEST_CHK_FOLDER_CONTACT _
                        , gstrREQUEST_CHK_CREATE_SUBFOLDERS, gstrREQUEST_CHK_FOLDER_VISIBLE)
    '
    ' Get properties
    '
    Call ACL_GetMemberProperties(strIDAclMember, mbIsOwner)

    If Err.Number = gerrNONE Then

        strHeading = gstrPAGE_HEADING_ACL_MEMBER_PROPERTIES

        If mbIsOwner Then
            strCtlFocus = gstrREQUEST_LST_ROLE
        Else
            strCtlFocus = mstrLST_CONTACTS
        End If

        Call App_RenderPage(strHeading, strCtlFocus)
    Else
        Call App_ShowMsg(gstrMSG_ALERT_CANT_DISPLAY_MEMBER_PROPERTIES, Err.Number, Err.Description)
    End If

Public Sub Page_RenderJavaScript()
    Dim rgbitRights
    Dim iChk

    rgbitRights = Array(gbitACL_RIGHTS_CREATE_ITEMS, gbitACL_RIGHTS_FOLDER_OWNER _
                        , gbitACL_RIGHTS_READ_ITEMS, gbitACL_RIGHTS_FOLDER_CONTACT _
                        , gbitACL_RIGHTS_CREATE_SUBFOLDERS, gbitACL_RIGHTS_FOLDER_VISIBLE)
    '
    ' To minimize data transmitted to client, comments for javascript are entered here.
    '
    ' ValidateCmd:  Validates & submits the passed command.
    '
    ' lstRole_OnChange:  Executed on change event of the role list.  If the user has owner 
    ' rights for the current folder, this routine updates the rights controls;
    ' else this routine displays an error msg & resets the rights controls.  
    ' Under IE4,DHTML is used to disable the controls, but under NN the error is displayed.
    '
    ' Rights_OnClick:  Executed on click event for rights checkboxes & option buttons.  See
    ' description of lstRole_OnChange.
    '
    ' InitRights:  Sets rights controls to initial value.
    '
    ' SetRights:  Sets rights controls to match passed rights bits.
    '
    ' SetRole:  Determines rights from rights controls & sets role to match.
    '
    ' RemoveCustomRole:  Removes custom role entry from role list.
    ' Custom role is added when selected rights don't match any roles & removed otherwise.
    '
    ' bBitSet:  Determines whether a bit has been set.
    '
    ' bitSetRights:  Returns the bits w/ the passed bit set if bChecked is true.
    '
    ' SaveRights:  Saves bitRights to a hidden fld.

%>
    <SCRIPT LANGUAGE="JavaScript">
        var iOPT_NONE = <%=miOPT_NONE%>;
        var iOPT_OWN = <%=miOPT_OWN%>;
        var iOPT_ALL = <%=miOPT_ALL%>;
        var valLST_CUSTOM = -1;

        function ValidateCmd(pstrCmd) {
            var frm = document.<%=gstrFORM_MAIN%>;
            var bValidCmd;

            bValidCmd = true;

            if (bValidCmd) {
                parent.SubmitCommand(pstrCmd);
            }
        }

        function <%=gstrREQUEST_LST_ROLE%>_OnChange() {
<%
    If mbIsOwner Then
%>
            var lst = document.<%=gstrFORM_MAIN%>.<%=gstrREQUEST_LST_ROLE%>;
            var ilstSel = lst.selectedIndex;

            if (ilstSel != parent.iLST_NONE) {
<%
            If Not App_bSupportsIE4DHTML() Then
                '
                ' Under NN, clicking on the window or on the current selection fires the onchange
                ' event.  This can result in selection of a null value if "Custom" is in
                ' the role combo.  To prevent this behavior, exit if null is selected.
                '
%>
                if (lst.options[ilstSel].value == 'null') {
                    return;
                }
<%
            End If
%>
                SetRights(lst.options[ilstSel].value);

                RemoveCustomRole(lst.options);
            }
<%
    Else
%>
            InitRights();
<%
    End If
%>
        }

        function Rights_OnClick(prgstrCtlName) {
<%
    If mbIsOwner Then
%>
            var frm = document.<%=gstrFORM_MAIN%>;

            if ((prgstrCtlName == '<%=gstrREQUEST_CHK_FOLDER_OWNER%>') 
                    || (prgstrCtlName == '<%=gstrREQUEST_CHK_READ_ITEMS%>')){
                if ((frm.<%=gstrREQUEST_CHK_FOLDER_OWNER%>.checked) 
                        || (frm.<%=gstrREQUEST_CHK_READ_ITEMS%>.checked)) {
                    frm.<%=gstrREQUEST_CHK_FOLDER_VISIBLE%>.checked = true;
                }                
            }
            else if (prgstrCtlName == '<%=gstrREQUEST_CHK_FOLDER_VISIBLE%>') {
                if (! frm.<%=gstrREQUEST_CHK_FOLDER_VISIBLE%>.checked) {
                    frm.<%=gstrREQUEST_CHK_READ_ITEMS%>.checked = false;
                }
            }
<%
        '
        ' For NN, prevent setting of contact rights.
        '
        If mbContactRightsDisabled And Not App_bSupportsIE4DHTML() Then
%>
            else if (prgstrCtlName == '<%=gstrREQUEST_CHK_FOLDER_CONTACT%>') {
                frm.<%=gstrREQUEST_CHK_FOLDER_CONTACT%>.checked = false;
            }
<%
        End If
%>

            SetRole();
<%
    Else
%>
            InitRights();
<%
    End If
%>
        }

        function InitRights() {
            SetRights(<%=ACL_bitRights%>);
            SetRole(<%=ACL_bitRights%>);
<%
    If Not mbIsOwner Then
%>
            parent.ShowError('<%=gstrMSG_ALERT_MAY_NOT_MOD_RIGHTS%>');
<%
        End If
%>
        }

        function SetRights(pbitRights) {
            var frm = document.<%=gstrFORM_MAIN%>;
<%
    For ichk = LBound(mrgstrChk) To UBound(mrgstrChk)
        If mbContactRightsDisabled _
            And (mrgstrChk(ichk) = gstrREQUEST_CHK_FOLDER_CONTACT) Then
            '
            ' When contact rights are disabled, prevent checking.
            '
        Else
%>
            frm.<%=mrgstrChk(ichk)%>.checked = bBitSet(pbitRights, <%=rgbitRights(ichk)%>)
<%
        End If
    Next
%>
            if (bBitSet(pbitRights, <%=gbitACL_RIGHTS_EDIT_ALL%>)) {
                iOpt = iOPT_ALL
            }
            else if (bBitSet(pbitRights, <%=gbitACL_RIGHTS_EDIT_OWN%>)) {
                iOpt = iOPT_OWN
            }
            else {
                iOpt = iOPT_NONE
            }
            frm.<%=gstrREQUEST_OPT_EDIT_ITEMS%>[iOpt].checked = true;

            if (bBitSet(pbitRights, <%=gbitACL_RIGHTS_DEL_ALL%>)) {
                iOpt = iOPT_ALL
            }
            else if (bBitSet(pbitRights, <%=gbitACL_RIGHTS_DEL_OWN%>)) {
                iOpt = iOPT_OWN
            }
            else {
                iOpt = iOPT_NONE
            }
            frm.<%=gstrREQUEST_OPT_DEL_ITEMS%>[iOpt].checked = true;

            SaveRights(pbitRights);
        }

        function SetRole(pbitRights) {
            var bitRights = <%=gbitACL_RIGHTS_NONE%>;
            var bitRightsFind;
            var frm = document.<%=gstrFORM_MAIN%>;
            var lst = frm.<%=gstrREQUEST_LST_ROLE%>.options;
            var ilst;

            if (pbitRights == null) {
<%
            For ichk = LBound(mrgstrChk) To UBound(mrgstrChk)
%>
                bitRights = bitSetRights(frm.<%=mrgstrChk(ichk)%>.checked
                                                    , <%=rgbitRights(ichk)%>
                                                    , bitRights)
<%
            Next
%>
                bitRights = bitSetRights(frm.<%=gstrREQUEST_OPT_EDIT_ITEMS%>[iOPT_OWN].checked 
                                                    , <%=gbitACL_RIGHTS_EDIT_OWN%>
                                                    , bitRights)
                bitRights = bitSetRights(frm.<%=gstrREQUEST_OPT_EDIT_ITEMS%>[iOPT_ALL].checked 
                                                    , <%=gbitACL_RIGHTS_EDIT_ALL%>
                                                    , bitRights)
                bitRights = bitSetRights(frm.<%=gstrREQUEST_OPT_DEL_ITEMS%>[iOPT_OWN].checked 
                                                    , <%=gbitACL_RIGHTS_DEL_OWN%>
                                                    , bitRights)
                bitRights = bitSetRights(frm.<%=gstrREQUEST_OPT_DEL_ITEMS%>[iOPT_ALL].checked 
                                                    , <%=gbitACL_RIGHTS_DEL_ALL%>
                                                    , bitRights)
            }
            else {
                bitRights = pbitRights;
            }

            if (bitRights == <%=gbitACL_RIGHTS_OWNER_2%>) {
                bitRightsFind = <%=gbitACL_RIGHTS_OWNER%>;
            }
            else if (bitRights == <%=gbitACL_RIGHTS_ROLE_NONE_2%>) {
                bitRightsFind = <%=gbitACL_RIGHTS_ROLE_NONE%>;
            }
            else if (bitRights == <%=gbitACL_RIGHTS_ROLE_NONE_3%>) {
                bitRightsFind = <%=gbitACL_RIGHTS_ROLE_NONE%>;
            }
            else if (bitRights == <%=gbitACL_RIGHTS_ROLE_NONE Or gbitACL_RIGHTS_ROLE_NONE_3%>) {
                bitRightsFind = <%=gbitACL_RIGHTS_ROLE_NONE%>;
            }
            else {
                bitRightsFind = bitRights;
            }

            ilst = parent.ilstFindVal(bitRightsFind, lst);

            if (ilst != parent.iLST_NONE) {
                lst[ilst].selected = true;

                RemoveCustomRole(lst);
            }
            else {
                if (lst[lst.length - 1].value != 'null') {
                    lst[lst.length] = new Option('<%=gstrACL_ROLE_CUSTOM%>', null, false, true);
                }
            }

            SaveRights(bitRights);
        }

        function SaveRights(pbitRights) {
            var frm = document.<%=gstrFORM_MAIN%>;

            frm.<%=gstrREQUEST_HID_BIT_RIGHTS%>.value = pbitRights;
        }

        function RemoveCustomRole(plst) {
            var ilstLast = plst.length - 1;

            if (plst[ilstLast].value == 'null') {
                plst[ilstLast] = null;
            }
        }

        function bBitSet(pbit, pbitCheck) {
            return (pbitCheck == (pbit & pbitCheck));
        }

        function bitSetRights(pbChecked, pbitRight, pbitRights) {
            return (pbChecked ? (pbitRight | pbitRights) : pbitRights) 
        }
    </SCRIPT>
<%
End Sub

Public Sub Page_RenderContent()
    Const pxlWIDTH_LST_CONTACTS = 170

    Dim iContacts
    Dim strHeadingSection
%>
    <TABLE CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD>Folder:</TD>
            <TD><%=App_strHTML(CStr(Session(gstrSESS_FOLDER_NAME)))%></TD>
        </TR>
        <TR>
<%
        If mbIsOwner Then
%>
            <TD>Member:</TD>
            <TD><%=App_strHTML(Session(gstrSESS_ACL_MEMBER_DISP_NAME))%></TD>
<%
        Else
%>
            <TD VAlign=Top>Contacts:</TD>
            <TD><Select Name=<%=mstrLST_CONTACTS%> Size=2>
<%
            If ACL_cContacts > 0 Then
                For iContacts = LBound(ACL_rgstrContacts) To UBound(ACL_rgstrContacts)
%>
                    <OPTION><%=App_strHTML(ACL_rgstrContacts(iContacts))%>
<%
                Next
            End If
%>
                </Select>
            </TD>
<%
        End If
%>
        </TR>
    </TABLE>
    <HR>
<%
    If mbIsOwner Then
        strHeadingSection = gstrSECTION_HEADING_PERMISSIONS
    Else
        strHeadingSection = gstrSECTION_HEADING_PERMISSIONS_DISABLED
    End If
%>
    <Font Class=<%=gstrCSS_CLASS_FONT_HEADING_SMALL%>><%=strHeadingSection%></Font><BR><BR>
<%
    Call RenderRoles()

    Call RenderRights()
%>
    <HR>
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_HID_BIT_RIGHTS%>">
<%
    If mbIsOwner Then
%>
        <Table>
            <TR>
                <TD Width=100 Align=Right><INPUT TYPE="button" VALUE="   OK   " OnClick="ValidateCmd('<%=gstrCMD_MOD_ACL_MEMBER%>')"></TD>
                <TD><INPUT TYPE="button" VALUE="Cancel" OnClick="ValidateCmd('<%=gstrCMD_ACL_MAINT%>')"></TD>
            </TR>
        </Table>
<%
    Else
%>
        <BR>
        <A HRef=javascript:ValidateCmd('<%=gstrCMD_SEL_FOLDER%>')><Font CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>Return to Microsoft Exchange Folder Selection</Font></A>
<%
    End If
%>
    <Script>
<%
    If App_bSupportsIE4DHTML() Then
        '
        ' Use DHTML to size & disable controls.
        '
%>
        var frm = document.<%=gstrFORM_MAIN%>;

        parent.SetWidth(frm.<%=mstrLST_CONTACTS%>, <%=pxlWIDTH_LST_CONTACTS%>);
<%
        If Not mbIsOwner Then
            Call SetCtlDisabled(Array(gstrREQUEST_LST_ROLE _
                                        , gstrREQUEST_OPT_EDIT_ITEMS & "[" & CStr(miOPT_NONE) & "]" _
                                        , gstrREQUEST_OPT_EDIT_ITEMS & "[" & CStr(miOPT_OWN) & "]" _
                                        , gstrREQUEST_OPT_EDIT_ITEMS & "[" & CStr(miOPT_ALL) & "]" _
                                        , gstrREQUEST_OPT_DEL_ITEMS & "[" & CStr(miOPT_NONE) & "]" _
                                        , gstrREQUEST_OPT_DEL_ITEMS & "[" & CStr(miOPT_OWN) & "]" _
                                        , gstrREQUEST_OPT_DEL_ITEMS & "[" & CStr(miOPT_ALL) & "]"))
            Call SetCtlDisabled(mrgstrChk)
        ElseIf mbContactRightsDisabled Then
            Call SetCtlDisabled(Array(gstrREQUEST_CHK_FOLDER_CONTACT))
        End If
    End If
%>
        InitRights();
    </Script>
<%
End Sub

Private Sub SetCtlDisabled(prgstrCtl)
    Dim ictl

    For ictl = LBound(prgstrCtl) To UBound(prgstrCtl)
%>
        frm.<%=prgstrCtl(ictl)%>.disabled = true;
<%
    Next
End Sub

Private Sub RenderRoles()
'
' RenderRoles displays the roles dropdown.
'
    Const pxlCOL_WIDTH_CAPTION = 55

    Dim iRoles
%>
    <Table Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR>
            <TD Width=<%=pxlCOL_WIDTH_CAPTION%>>Role:</TD>
            <TD>
                <SELECT NAME=<%=gstrREQUEST_LST_ROLE%> SIZE=1 OnChange="<%=gstrREQUEST_LST_ROLE%>_OnChange()">
<%
                If ACL_cRoles > 0 Then
                    For iRoles = LBound(ACL_rgrightsRoles) To UBound(ACL_rgrightsRoles)
%>
                        <OPTION VALUE=<%=ACL_rgrightsRoles(iRoles)%>><%=App_strHTML(ACL_rgstrRoles(iRoles))%>
<%
                    Next
                End If
%>
                </SELECT>
            </TD>
        </TR>
    </Table><BR>
<%
End Sub

Private Sub RenderRights()
'
' RenderRights displays the rights checkboxes & option buttons.
'
    Const strCHK_CAP_CREATE_ITEMS = "Create items"
    Const strCHK_CAP_FOLDER_OWNER = "Folder Owner"
    Const strCHK_CAP_READ_ITEMS = "Read items"
    Const strCHK_CAP_FOLDER_CONTACT = "Folder Contact"
    Const strCHK_CAP_CREATE_SUBFOLDERS = "Create subfolders"
    Const strCHK_CAP_FOLDER_VISIBLE = "Folder Visible"
    Const strOPT_CAP_NONE = "None"
    Const strOPT_CAP_OWN = "Own"
    Const strOPT_CAP_ALL = "All"

    Dim rgstrOptCap

    rgstrOptCap = Array(strOPT_CAP_NONE, strOPT_CAP_OWN, strOPT_CAP_ALL)

%>
    <Table CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>
<%
            Call RenderChk(mrgstrChk _
                            , Array(strCHK_CAP_CREATE_ITEMS, strCHK_CAP_FOLDER_OWNER _
                                    , strCHK_CAP_READ_ITEMS, strCHK_CAP_FOLDER_CONTACT _
                                    , strCHK_CAP_CREATE_SUBFOLDERS, strCHK_CAP_FOLDER_VISIBLE))
%>
    </Table>
    <Table CLASS=<%=gstrCSS_CLASS_FONT_NORMAL%>>
        <TR ColSpan=4>
            <HR Align=Left>
        </TR>
        <TR>
            <TD>Edit items:</TD>
<%
            Call RenderOpt(gstrREQUEST_OPT_EDIT_ITEMS _
                            , Array(OPT_EDIT_ITEMS_NONE, OPT_EDIT_ITEMS_OWN, OPT_EDIT_ITEMS_ALL) _
                            , rgstrOptCap)
%>            
        </TR>
        <TR><TD> </TD></TR>
        <TR><TD> </TD></TR>
        <TR>
            <TD>Delete items:</TD>
<%
            Call RenderOpt(gstrREQUEST_OPT_DEL_ITEMS _
                            , Array(OPT_DEL_ITEMS_NONE, OPT_DEL_ITEMS_OWN, OPT_DEL_ITEMS_ALL) _
                            , rgstrOptCap)
%>            
        </TR>
    </Table>
<%
End Sub

Private Sub RenderChk(prgstrChkName, prgstrChkCaption)
    Dim ichk

    For ichk = LBound(prgstrChkName) To UBound(prgstrChkName) Step 2
%>
        <TR>
            <TD>
                <Input Type=Checkbox Name=<%=prgstrChkName(ichk)%> OnClick="Rights_OnClick('<%=prgstrChkName(ichk)%>')"><%=prgstrChkCaption(ichk)%> 
            </TD>
            <TD>
                <Input Type=Checkbox Name=<%=prgstrChkName(ichk + 1)%> OnClick="Rights_OnClick('<%=prgstrChkName(ichk + 1)%>')"><%=prgstrChkCaption(ichk + 1)%> 
            </TD>
        </TR>
<%
    Next
End Sub

Private Sub RenderOpt(pstrOptName, prgstrOptValue, prgstrOptCap)
    Dim iOpt

    For iOpt = LBound(prgstrOptValue) To UBound(prgstrOptValue)
%>            
        <TD>
            <Input Type=Radio Name=<%=pstrOptName%> Value='<%=prgstrOptValue(iOpt)%>' OnClick="Rights_OnClick()"><%=prgstrOptCap(iOpt)%> 
        </TD>
<%
    Next
End Sub
%>