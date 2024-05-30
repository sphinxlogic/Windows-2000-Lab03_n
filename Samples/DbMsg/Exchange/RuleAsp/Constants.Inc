<%
'<!--Rules Sample Application-->
'<!--Constants.inc : Application constants-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Constants.inc contains global constants including request & session properties,
' message text, special characters, etc..
'
    '
    ' Headings
    '
    Const gstrPAGE_HEADING_ADD_RULE = "Add Rule"
    Const gstrPAGE_HEADING_CHOOSE_FORWARD_TO = "Choose Forwarding Recipients"
    Const gstrPAGE_HEADING_CHOOSE_SENT_TO = "Choose Recipients"
    Const gstrPAGE_HEADING_CHOOSE_FROM = "Choose Senders"
    Const gstrPAGE_HEADING_EXCH_SERVER_LOGON = "Microsoft Exchange Server Logon"
    Const gstrPAGE_HEADING_FOLDER_SEL = "Microsoft Exchange Folder Selection"
    Const gstrPAGE_HEADING_RULE_MAINT = "Rule Maintenance"
    Const gstrPAGE_HEADING_RULE_PROPERTIES = "Rule Properties"
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
    Const gstrASP_HANDLE_CMDS = "HandleCmds.asp"
    Const gstrASP_EXCH_LOGON = "ExchLogon.asp"
    Const gstrASP_LOGON = "Logon.asp"
    Const gstrASP_SEL_ADDRESSES = "SelAddresses.asp"
    Const gstrASP_SEL_FOLDER = "SelFolder.asp"
    Const gstrASP_RULE_MAINTENANCE = "RuleMaintenance.asp"
    Const gstrASP_RULE_PROPERTIES = "RuleProperties.asp"
    '
    ' Images
    '
    Const gstrIMG_UP_ONE_LEVEL = "UpOne.gif"
    Const gstrIMG_DELETE = "Delete.gif"
    Const gstrIMG_EXPAND_FOLDER = "Expand.gif"
    Const gstrIMG_FOLDER = "Folder.gif"
    Const gstrIMG_FORWARD = "Forward.gif"
    Const gstrIMG_REPLY = "Reply.gif"
    Const gstrIMG_RETURN = "Return.gif"
    '
    ' Request Parameters
    '
    Const gstrREQUEST_CHK_ACT_DELETE = "rqstChkActDelete"
    Const gstrREQUEST_CHK_ACT_FORWARD = "rqstChkActForward"
    Const gstrREQUEST_CHK_ACT_REPLY = "rqstChkActReply"
    Const gstrREQUEST_CHK_ACT_RETURN = "rqstChkActReturn"
    Const gstrREQUEST_CHK_ACT_SKIP_RULES = "rqstChkActSkipRules"
    Const gstrREQUEST_CHK_COND_COPIED_TO = "rqstChkCondCopiedTo"
    Const gstrREQUEST_CHK_COND_SENT_TO = "rqstChkCondSentTo"
    Const gstrREQUEST_CMD = "rqstCmd"
    Const gstrREQUEST_HID_RG_ADDRESS_ID_FROM = "rqstHidRgAddressIDFrom"
    Const gstrREQUEST_HID_RG_ADDRESS_ID_FORWARD = "rqstHidRgAddressIDForward"
    Const gstrREQUEST_HID_RG_ADDRESS_ID_SENT_TO = "rqstHidRgAddressIDSentTo"
    Const gstrREQUEST_HID_I_FOLDER_BRANCH_LEVEL = "rqstHidIFolderBranchLevel"
    Const gstrREQUEST_HID_I_RULE = "rqstHidIRule"
    Const gstrREQUEST_HID_RG_I_RULE = "rqstHidRgIRule"
    Const gstrREQUEST_HID_STR_FOLDER_ID = "rqstHidStrFolderID"
    Const gstrREQUEST_HID_STR_FOLDER_NAME = "rqstHidStrFolderName"
    Const gstrREQUEST_LST_BRANCH = "rqstLstBranch"
    Const gstrREQUEST_LST_RULES = "rqstLstRules"
    Const gstrREQUEST_LST_SEL = "rqstLstSel"
    Const gstrREQUEST_TXT_COND_MSG_BODY = "rqstTxtCondMsgBody"
    Const gstrREQUEST_TXT_COND_SUBJECT = "rqstTxtCondSubject"
    Const gstrREQUEST_TXT_EXCH_SERVER = "rqstTxtExchServer"
    Const gstrREQUEST_TXT_MAILBOX = "rqstTxtMailbox"
    Const gstrREQUEST_TXT_SEL_CRITERIA = "rqstTxtSelCriteria"
    '
    ' Max Field Lengths
    '
    Const giTXT_MAX_LEN_EXCH_SERVER = 256
    Const giTXT_MAX_LEN_MAILBOX = 256
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
    Const gstrSESS_B_SUPPORTS_IE4_DHTML = "sessBSupportsIE4DHTML"
    Const gstrSESS_CDO_SESSION = "sessCDOSession"
    Const gstrSESS_CMD = "sessCmd"
    Const gstrSESS_CMD_SEL_ADDRESS = "sessCmdSelAddress"
    Const gstrSESS_COL_RULE = "sessColRule"
    Const gstrSESS_EXCH_SERVER = "sessExchServer"
    Const gstrSESS_FOLDER_ID = "sessFolderID"
    Const gstrSESS_FOLDER_NAME = "sessFolderName"
    Const gstrSESS_HANDLE_IMPERSONATE = "sessHImp"
    Const gstrSESS_I_RULE = "sessIRule"
    Const gstrSESS_MAILBOX = "sessMailbox"
    Const gstrSESS_RG_BRANCH_FOLDER_ID = "sessRgBranchFolderID"
    Const gstrSESS_RG_BRANCH_FOLDER_NAME = "sessRgBranchFolderName"
    Const gstrSESS_RG_BRANCH_FOLDER_PAGE = "sessRgBranchFolderPage"
    Const gstrSESS_RG_I_RULE = "sessRgIRule"
    Const gstrSESS_RULE = "sessRule"
    Const gstrSESS_SEL_ADDRESS_PAGE = "sessSelAddressPage"
    Const gstrSESS_SEL_CRITERIA = "sessSelCriteria"
    '
    ' Commands
    '
    Const gstrCMD_ADD_SEL_ADDRESSES = "AddSelAddresses"
    Const gstrCMD_ADD_FORWARD_TO = "AddForwardTo"
    Const gstrCMD_ADD_FROM = "AddFrom"
    Const gstrCMD_ADD_RULE = "AddRule"
    Const gstrCMD_ADD_SENT_TO = "AddSentTo"
    Const gstrCMD_COMMIT = "Commit"
    Const gstrCMD_DEL_RULE = "DelRule"
    Const gstrCMD_EXCH_LOGON = "ExchLogon"
    Const gstrCMD_EXPAND_FOLDER = "ExpandFolder"
    Const gstrCMD_FIND_ADDRESSES = "FindAddresses"
    Const gstrCMD_GO_TO_BRANCH_LEVEL = "GoToBranchLevel"
    Const gstrCMD_MOD_RULE = "ModRule"
    Const gstrCMD_NEXT_PAGE = "GoToNextPage"
    Const gstrCMD_PREV_PAGE = "GoToPrevPage"
    Const gstrCMD_RULES_MAINT = "RulesMaint"
    Const gstrCMD_RULES_MAINT_NEW = "RulesMaintNew"
    Const gstrCMD_RULE_PROPERTIES = "RuleProperties"
    Const gstrCMD_SEL_ADDRESSES = "SelAddresses"
    Const gstrCMD_SEL_ADDRESSES_GO_TO_PAGE = "SelAddressesGoToPage"
    Const gstrCMD_SEL_FOLDER = "SelFolder"
    Const gstrCMD_SEL_FOLDER_GO_TO_PAGE = "SelFolderGoToPage"
    Const gstrCMD_SEL_FOLDER_NEW = "SelFolderNew"
    Const gstrCMD_SEL_ADDRESSES_FORWARD_TO = "ShowAddForwardTo"
    Const gstrCMD_SEL_ADDRESSES_FROM = "ShowAddFrom"
    Const gstrCMD_SEL_ADDRESSES_SENT_TO = "ShowAddSentTo"
    Const gstrCMD_UPD_RULE = "UpdRule"
    '
    ' Messages
    '
    Const gstrMSG_ALERT_ADD_CONFIRMED = "Rule was added."
    Const gstrMSG_ALERT_ALREADY_AT_TOP = "You are already at the top level."
    Const gstrMSG_ALERT_CANT_ADD_FORWARD_TO_ADDRESS = "Unable to add selected recipient(s)."
    Const gstrMSG_ALERT_CANT_ADD_FROM_ADDRESS = "Unable to add selected sender(s)."
    Const gstrMSG_ALERT_CANT_ADD_RULE = "Unable to add rule."
    Const gstrMSG_ALERT_CANT_ADD_SENT_TO_ADDRESS = "Unable to add selected recipient(s)."
    Const gstrMSG_ALERT_CANT_CREATE_RULE_OBJECT = "Unable to create a rule object."
    Const gstrMSG_ALERT_CANT_CREATE_RULES_OBJECT = "Unable to create the rules collection object."
    Const gstrMSG_ALERT_CANT_DEL_RULE = "Unable to delete rule."
    Const gstrMSG_ALERT_CANT_DISPLAY_RULE_LIST = "Unable to display the rules list."
    Const gstrMSG_ALERT_CANT_DISPLAY_SEL_FOLDER = "Unable to display Microsoft Exchange Folder Selection."
    Const gstrMSG_ALERT_CANT_DISPLAY_SEARCH_RESULTS = "Unable to search results."
    Const gstrMSG_ALERT_CANT_GET_RULE_OBJECT = "Unable to obtain rule object."
    Const gstrMSG_ALERT_CANT_GET_PROPERTIES = "Unable to obtain rule properties."
    Const gstrMSG_ALERT_CANT_GET_RENDER_APP = "Unable to obtain application property: render application."
    Const gstrMSG_ALERT_CANT_IMPERSONATE = "Render application impersonation failed."
    Const gstrMSG_ALERT_CANT_MOD_RULE = "Unable to modify rule."
    Const gstrMSG_ALERT_CANT_REORDER_RULES = "Unable to reorder rules."
    Const gstrMSG_ALERT_CANT_SET_RULE_PROPERTIES = "Unable to set rule properties."
    Const gstrMSG_ALERT_CANT_UPD = "Unable to update rules."
    Const gstrMSG_ALERT_FIND_ITEMS = "Find @."
        Const gstrMSG_REPLACE_ADDRESSES_FOR_ADD = "address entries for addition"
    Const gstrMSG_ALERT_LOGON_FAILED = "Unable to logon."
    Const gstrMSG_ALERT_MAY_NOT_MOD_PERMISSIONS = "Your permissions may not be modified."
    Const gstrMSG_ALERT_MOD_CONFIRMED = "Rule was modified."
    Const gstrMSG_ALERT_MUST_BE_ENTERED = "@ must be entered."
        Const gstrMSG_REPLACE_EXCH_SERVER = "server"
        Const gstrMSG_REPLACE_FOLDER = "Folder"
        Const gstrMSG_REPLACE_MAILBOX = "Mailbox"
        Const gstrMSG_REPLACE_SEL_CRITERIA = "Selection criteria"
        Const gstrMSG_REPLACE_STORE = "Store"
    Const gstrMSG_ALERT_MUST_ENTER_FWD_TO = "Recipients must be entered if ""Forward To"" is selected."
    Const gstrMSG_ALERT_MUST_SEL_ADDRESSES_ADD = "Select address entries for addition."
    Const gstrMSG_ALERT_MUST_SEL_ENTRY = "Select an entry for deletion."
    Const gstrMSG_ALERT_MUST_SEL_RULE_ACT = "Select one or more rule actions."
    Const gstrMSG_ALERT_MUST_SEL_RULE_DEL = "Select a rule for deletion."
    Const gstrMSG_ALERT_MUST_SEL_RULE_MOD = "Select a rule for modification."
    Const gstrMSG_ALERT_NONE_ON_FILE = "There are no @ on file."
        Const gstrMSG_REPLACE_MATCHING_ADDRESSES = "addresses matching the selection criteria"
    Const gstrMSG_ALERT_SEL_ADD_CONFIRMED = "Selected entries were added."
    Const gstrMSG_ALERT_TXTAREA_MAX_EXCEEDED = "The @ field may contain a maximum of @ characters.  You have entered @ characters."
    Const gstrMSG_ALERT_UPD_CONFIRMED = "Rules were updated."
    Const gstrMSG_CONFIRM_DEL = "Delete selected rule?"
    Const gstrMSG_CONFIRM_NO_CONDITIONS = "This rule will fire all incoming messages.  Is this what you want?"
    '
    ' Captions
    '
    Const gstrCAP_CHK_ACT_SKIP_RULES = "Do not process subsequent rules"
    Const gstrCAP_CHK_ACT_RETURN = "Return to Sender"
    Const gstrCAP_CHK_ACT_DELETE = "Delete"
    Const gstrCAP_CHK_ACT_REPLY = "Reply with"
    Const gstrCAP_CHK_ACT_FORWARD = "Forward"
    Const gstrCAP_CHK_COND_COPIED_TO = "Copied (Cc) to"
    Const gstrCAP_CHK_COND_SENT_TO = "Sent directly to"
    Const gstrCAP_CMD_ADD = "   Add...   "
    Const gstrCAP_CMD_ADD_FORWARD_TO = "Add Recipient(s)"
    Const gstrCAP_CMD_ADD_FROM = "Add Sender(s)"
    Const gstrCAP_CMD_ADD_SENT_TO = "Add Recipient(s)"
    Const gstrCAP_CMD_REMOVE = "Remove"
    Const gstrCAP_LST_FROM = "From:"
    Const gstrCAP_LST_FWD_TO = "To:"
    Const gstrCAP_LST_TO = "Sent To:"
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
    Const gstrHTML_CHECKBOX_CHECK = "Checked"

    Const gstrHTML_BREAK = "<BR>"
    Const gstrHTML_NUMERIC_ENTITY_PREFIX = "&#"
    Const gstrHTML_NUMERIC_ENTITY_SUFFIX = ";"
    Const gcHTML_NUMERIC_ENTITY_CHARACTERS = 3  ' Count of numeric entity characters - used to add leading zeros

    Const gstrANSI_NB_SPACE = 160
    Dim gstrHTML_NB_SPACE
    gstrHTML_NB_SPACE = gstrHTML_NUMERIC_ENTITY_PREFIX & gstrANSI_NB_SPACE & gstrHTML_NUMERIC_ENTITY_SUFFIX
    
    Const giruleNONE = -1
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