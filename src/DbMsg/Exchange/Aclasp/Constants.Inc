<%
'<!--ACL Sample Application-->
'<!--Constants.inc : Application constants-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Constants.inc contains global constants including request & session properties, 
' message text, special characters, etc.
'
    '
    ' Headings
    '
    Const gstrPAGE_HEADING_ACL_MAINT = "Access Control List Maintenance"
    Const gstrPAGE_HEADING_ACL_MEMBER_PROPERTIES = "Access Control List Member Properties"
    Const gstrPAGE_HEADING_ADD_ACL_MEMBER = "Add Access Control List Members"
    Const gstrPAGE_HEADING_EXCH_SERVER_LOGON = "Microsoft Exchange Server Logon"
    Const gstrPAGE_HEADING_FOLDER_SEL = "Microsoft Exchange Folder Selection"
    Const gstrSECTION_HEADING_PERMISSIONS = "Permissions"
    Const gstrSECTION_HEADING_PERMISSIONS_DISABLED = "Your Permissions"
    '
    ' Frame Names
    '
    Const gstrFRAME_HEADING = "frameHeading"
    Const gstrFRAME_MAIN = "frameMain"
    Const gstrFRAME_HANDLE_CMDS = "frameHandleCmds"
    '
    ' Form Name
    '
    Const gstrFORM_MAIN = "frmMAIN"
    '
    ' ASP Names
    '
    Const gstrASP_ACL_MAINT = "ACLMaintenance.asp"
    Const gstrASP_HANDLE_CMDS = "HandleCmds.asp"
    Const gstrASP_LIST_FOLDERS = "ListFolders.asp"
    Const gstrASP_PROPERTIES = "Properties.asp"
    Const gstrASP_EXCH_LOGON = "ExchLogon.asp"
    Const gstrASP_LOGON = "Logon.asp"
    Const gstrASP_SEL_ADDRESSES = "SelAddresses.asp"
    Const gstrASP_SEL_FOLDER = "SelFolder.asp"
    '
    ' Images
    '
    Const gstrIMG_UP_ONE_LEVEL = "UpOne.gif"
    Const gstrIMG_EXPAND_FOLDER = "Expand.gif"
    Const gstrIMG_FOLDER = "Folder.gif"
    '
    ' Request Parameters
    '
    Const gstrREQUEST_ACL_MEMBER_DISP_NAME = "rqstACLMemberDispName"
    Const gstrREQUEST_ACL_MEMBER_ID = "rqstACLMemberID"
    Const gstrREQUEST_CHK_CREATE_ITEMS = "rqstChkCreateItems"
    Const gstrREQUEST_CHK_READ_ITEMS = "rqstChkReadItems"
    Const gstrREQUEST_CHK_CREATE_SUBFOLDERS = "rqstChkCreateSubfolders"
    Const gstrREQUEST_CHK_FOLDER_OWNER = "rqstChkFolderOwner"
    Const gstrREQUEST_CHK_FOLDER_CONTACT = "rqstChkFolderContact" 
    Const gstrREQUEST_CHK_FOLDER_VISIBLE = "rqstChkFolderVisible"
    Const gstrREQUEST_CMD = "rqstCmd"
    Const gstrREQUEST_HID_BIT_RIGHTS = "rqstHidBitRights"
    Const gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL = "rqstHidIFolderBranchLevel"
    Const gstrREQUEST_HID_STR_FOLDER_ID = "rqstHidStrFolderID"
    Const gstrREQUEST_HID_STR_FOLDER_NAME = "rqstHidStrFolderName"
    Const gstrREQUEST_LST_ACL_MEMBERS = "rqstLstACLMembers"
    Const gstrREQUEST_LST_BRANCH = "rqstLstBranch"
    Const gstrREQUEST_LST_ROLE = "rqstLstRole"
    Const gstrREQUEST_LST_SEL = "rqstLstSel"
    Const gstrREQUEST_OPT_EDIT_ITEMS = "rqstOptEditItems"
        Const OPT_EDIT_ITEMS_NONE = "EditItemsNone" 
        Const OPT_EDIT_ITEMS_OWN = "EditItemsOwn"
        Const OPT_EDIT_ITEMS_ALL = "EditItemsAll"
    Const gstrREQUEST_OPT_DEL_ITEMS = "rqstOptDelItems"
        Const OPT_DEL_ITEMS_NONE = "DelItemsNone" 
        Const OPT_DEL_ITEMS_OWN = "DelItemsOwn"
        Const OPT_DEL_ITEMS_ALL = "DelItemsAll"
    Const gstrREQUEST_TXT_FOLDER = "rqstTxtFolder"
    Const gstrREQUEST_TXT_EXCH_SERVER = "rqstTxtExchServer"
    Const gstrREQUEST_TXT_MAILBOX = "rqstTxtMailbox"
    Const gstrREQUEST_TXT_SEL_CRITERIA = "rqstTxtSelCriteria"
    Const gstrREQUEST_TXT_ACL_MEMBER_RDN = "rqstTxtACLMemberRDN"
    '
    ' Max Field Lengths
    '
    Const giTXT_MAX_LEN_DISP_NAME = 256
    Const giTXT_MAX_LEN_EXCH_SERVER = 256
    Const giTXT_MAX_LEN_FOLDER = 256
    Const giTXT_MAX_LEN_MAILBOX = 256
    Const giTXT_MAX_LEN_STORE = 256
    '
    ' Text Input Sizes
    '
    Const giTXT_SIZE_NORMAL = -1
    '
    ' Application Properties
    '
    Const gstrAPP_RENDER_APPLICATION = "appRenderApplication"
    '
    ' Session Properties
    '
    Const gstrSESS_ACL_MEMBER_DISP_NAME = "sessACLMemberDispName"
    Const gstrSESS_ACL_MEMBER_ID = "sessACLMemberID"
    Const gstrSESS_ACL = "sessACL"
    Const gstrSESS_B_SUPPORTS_IE4_DHTML = "sessBSupportsIE4DHTML"
    Const gstrSESS_BIT_RIGHTS_DEFAULT = "sessbitRightsDefault"
    Const gstrSESS_CDO_SESSION = "sessCDOSession"
    Const gstrSESS_EXCH_SERVER = "sessExchServer"
    Const gstrSESS_FOLDER_ID = "sessFolderID"
    Const gstrSESS_FOLDER_NAME = "sessFolderName"
    Const gstrSESS_HANDLE_IMPERSONATE = "sessHImp"
    Const gstrSESS_IS_OWNER = "sessIsOwner"
    Const gstrSESS_RG_BRANCH_FOLDER_ID = "sessRgBranchFolderID"
    Const gstrSESS_RG_BRANCH_FOLDER_NAME = "sessRgBranchFolderName"
    Const gstrSESS_RG_BRANCH_FOLDER_PAGE = "sessRgBranchFolderPage"
    Const gstrSESS_SEL_ADDRESS_PAGE = "sessSelAddressPage"
    Const gstrSESS_SEL_CRITERIA = "sessSelCriteria"
    Const gstrSESS_MAILBOX = "sessMailbox"
    '
    ' Commands
    '
    Const gstrCMD_ACL_MAINT_NEW = "ACLMaintNew"
    Const gstrCMD_ACL_MAINT = "ACLMaint"
    Const gstrCMD_ADD_ACL_MEMBER = "AddACLMember"
    Const gstrCMD_COMMIT = "Commit"
    Const gstrCMD_DEL_ACL_MEMBER = "DelACLMember"
    Const gstrCMD_EXCH_LOGON = "ExchLogon"
    Const gstrCMD_EXPAND_FOLDER = "ExpandFolder"
    Const gstrCMD_FIND_ADDRESSES = "FindAddresses"
    Const gstrCMD_GO_TO_BRANCH_LEVEL = "GoToBranchLevel"
    Const gstrCMD_MOD_ACL_MEMBER = "ModACLMember"
    Const gstrCMD_NEXT_PAGE = "GoToNextPage"
    Const gstrCMD_PREV_PAGE = "GoToPrevPage"
    Const gstrCMD_SEL_ADDRESSES = "SelAddresses"
    Const gstrCMD_SEL_ADDRESSES_GO_TO_PAGE = "SelAddressesGoToPage"
    Const gstrCMD_SEL_FOLDER = "SelFolder"
    Const gstrCMD_SEL_FOLDER_GO_TO_PAGE = "SelFolderGoToPage"
    Const gstrCMD_SEL_FOLDER_NEW = "SelFolderNew"
    Const gstrCMD_MEMBER_PROPERTIES = "MemberProperties"
    '
    ' Messages
    '
    Const gstrMSG_ALERT_ADD_CONFIRMED = "Access control list member(s) added."
    Const gstrMSG_ALERT_ALREADY_AT_TOP = "You are already at the top level."
    Const gstrMSG_ALERT_CANT_CREATE_ACL_OBJECT = "Unable to create ACL object."
    Const gstrMSG_ALERT_CANT_DISPLAY_ACL = "Unable to display access control list."
    Const gstrMSG_ALERT_CANT_DISPLAY_MEMBER_PROPERTIES = "Unable to display access control list member properties."
    Const gstrMSG_ALERT_CANT_DISPLAY_SEL_FOLDER = "Unable to display Microsoft Exchange Folder Selection."
    Const gstrMSG_ALERT_CANT_DISPLAY_SEARCH_RESULTS = "Unable to search results."
    Const gstrMSG_ALERT_CANT_ADD = "Unable to add access control list members."
    Const gstrMSG_ALERT_CANT_DELETE = "Unable to delete access control list member @."
    Const gstrMSG_ALERT_CANT_MODIFY = "Unable to modify access control list member @."
    Const gstrMSG_ALERT_CANT_GET_RENDER_APP = "Unable to obtain application property: render application."
    Const gstrMSG_ALERT_CANT_IMPERSONATE = "Render application impersonation failed."
    Const gstrMSG_ALERT_CANT_UPD = "Unable to update access control list."
    Const gstrMSG_ALERT_FIND_ITEMS = "Find @."
        Const gstrMSG_REPLACE_ACL_MEMBERS_FOR_ADD = "access control list members for addition"
    Const gstrMSG_ALERT_LOGON_FAILED = "Unable to logon."
    Const gstrMSG_ALERT_MAY_NOT_MOD_RIGHTS = "You do not have the access rights necessary for updating this access control list."
    Const gstrMSG_ALERT_MEMBER_UPD_CONFIRMED = "Access control list member @ was updated."
    Const gstrMSG_ALERT_MUST_BE_ENTERED = "@ must be entered."
        Const gstrMSG_REPLACE_ACL_MEMBER = "Access control list member"
        Const gstrMSG_REPLACE_EXCH_SERVER = "Server"
        Const gstrMSG_REPLACE_FOLDER = "Folder"
        Const gstrMSG_REPLACE_MAILBOX = "Mailbox"
        Const gstrMSG_REPLACE_SEL_CRITERIA = "Selection criteria"
        Const gstrMSG_REPLACE_STORE = "Store"
    Const gstrMSG_ALERT_MUST_SEL_ACL_MEMBERS_ADD = "Select access control list members for addition."
    Const gstrMSG_ALERT_MUST_SEL_ACL_MEMBER = "Select an access control list member for @."
        Const gstrMSG_REPLACE_MOD = "modification"
        Const gstrMSG_REPLACE_DEL = "deletion"
    Const gstrMSG_ALERT_NONE_ON_FILE = "There are no @ on file."
        Const gstrMSG_REPLACE_MATCHING_ITEMS = "matching address entries"
        Const gstrMSG_REPLACE_ACL_MEMBERS = "access control list members"
    Const gstrMSG_ALERT_TXTAREA_MAX_EXCEEDED = "The @ field may contain a maximum of @ characters.  You have entered @ characters."
    Const gstrMSG_ALERT_UPD_CONFIRMED = "Access control list was updated."
    Const gstrMSG_CONFIRM_DEL = "Delete access control list member @?"
    '
    ' Paging constants
    '
    Const gstrMSG_ALERT_PAGE_NO_INVALID = "Page number must be an integer between @ and @."

    Const gstrCMD_GO_TO_PAGE = "GoToPage"
    Const gstrALT_GO_TO_PAGE = "Go to the @ page of @"
        Const gstrMSG_REPLACE_NEXT = "next"
        Const gstrMSG_REPLACE_PREV = "previous"
        Const gstrMSG_REPLACE_ADDRESSES = "addresses"
        Const gstrMSG_REPLACE_FOLDERS = "folders"

    Const gstrHIDDEN_C_PAGE = "hidcPage"
    Const gstrHIDDEN_CMD_GO_TO_PAGE = "hidCmdGoToPage"
    Const gstrHIDDEN_I_PAGE_GO_TO = "hidiPageGoTo"
    Const gstrHIDDEN_I_PAGE = "hidiPage"

    Const gstrTXT_PAGE_GO_TO = "txtPageGoTo"
    '
    ' Special characters
    '
    Const gchAMPERSAND = "&"
    Const gchAPOSTROPHE = "'"
    Const gchCOMMA = ","
    Const gchGREATER_THAN = ">"
    Const gchLESS_THAN = "<"
    Const gchQUOTE = """"
    Const gchREPLACE = "@"
    Const gchSPACE = " "
    Const gchZERO = "0"

    Const gjsNEW_LINE = "\n"
    Const gstrNONE = ""
    Const ghtmlBG_COLOR = "#c0c0c0"

    Const gstrHTML_OPTION_SEL = "Selected"

    Const gstrHTML_BREAK = "<BR>"
    Const gstrHTML_NUMERIC_ENTITY_PREFIX = "&#"
    Const gstrHTML_NUMERIC_ENTITY_SUFFIX = ";"
    Const gcHTML_NUMERIC_ENTITY_CHARACTERS = 3  ' Count of numeric entity characters - used to add leading zeros

    Const gstrANSI_NB_SPACE = 160
    Dim gstrHTML_NB_SPACE
    gstrHTML_NB_SPACE = gstrHTML_NUMERIC_ENTITY_PREFIX & gstrANSI_NB_SPACE & gstrHTML_NUMERIC_ENTITY_SUFFIX
    '
    ' Errors
    '
    Const gerrNONE = 0
    '
    ' CSS Constants
    '
    Const gstrCSS_CLASS_FONT_NORMAL = "cssFontNormal"
    Const gstrCSS_CLASS_FONT_HEADING = "cssFontHeading"
    Const gstrCSS_CLASS_FONT_HEADING_SMALL = "cssFontHeadingSmall"
    '
    ' Folder Selection Constants
    '
    Const gstrBRANCH_ROOT_NAME = "All Stores"
    Const giBRANCH_ROOT = 0
    Const gstrALT_UP_ONE_LEVEL = "Up one level"
    Const gstrALT_EXPAND = "Show subfolders"
    '
    ' Other constants
    '
    Const gpxlWIDTH_LST = 230
%>