<%
'<!--Distribution List Maintenance  Sample Application-->
'<!--Constants.inc : Application constants-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Constants.inc contains global constants including request & session properties, 
' message text, special characters, etc.
'
    '
    ' Page Headings
    '
    Const gstrPAGE_HEADING_DL_MAINT = "Distribution List Maintenance"
    Const gstrPAGE_HEADING_DL_ADD = "Add Distribution List"
    Const gstrPAGE_HEADING_DL_PROPERTIES = "Distribution List Properties"
    Const gstrPAGE_HEADING_DL_MEMBER_ADD = "Add Distribution List Members"
    Const gstrPAGE_HEADING_DL_OWNER_MOD = "Modify Distribution List Owner"
    Const gstrPAGE_HEADING_EXCH_SERVER_SEL = "Microsoft Exchange Server Selection"
    '
    ' Frame Names
    '
    Const gstrFRAME_MAIN = "frameMain"
    Const gstrFRAME_HANDLE_CMDS = "frameHandleCmds"
    '
    ' Form Name
    '
    Const gstrFORM_MAIN = "frmMAIN"
    '
    ' ASP Names
    '
    Const gstrASP_DL_ADD = "dlAdd.asp"
    Const gstrASP_DL_MAINTENANCE = "dlMaintenance.asp"
    Const gstrASP_DL_PROPERTIES = "dlProperties.asp"
    Const gstrASP_HANDLE_CMDS = "HandleCmds.asp"
    Const gstrASP_LOGON = "Logon.asp"
    Const gstrASP_SEL_DN = "SelDN.asp"
    Const gstrASP_SEL_EXCH_SERVER = "SelExchServer.asp"
    '
    ' Image File Names
    '
    Const gstrIMG_DL = "dl.gif"
    '
    ' Request Parameters
    '
    Const gstrREQUEST_B_DIRTY_PROPERTIES = "bDirtyProperties"
    Const gstrREQUEST_CMD = "rqstCMD"
    Const gstrREQUEST_DL_ALIAS = "dlAlias"
    Const gstrREQUEST_DL_DISP_NAME = "dlDispName"
    Const gstrREQUEST_LST_DL = "lstDL"
    Const gstrREQUEST_LST_DL_MEMBERS = "lstDLMembers"
    Const gstrREQUEST_LST_SEL = "lstSel"
    Const gstrREQUEST_TXT_ALIAS = "txtAlias"
    Const gstrREQUEST_TXT_DISP_NAME = "txtDispName"
    Const gstrREQUEST_TXT_ENTERPRISE = "txtEnterprise"
    Const gstrREQUEST_TXT_NOTES = "txtNotes"
    Const gstrREQUEST_TXT_SEL_CRITERIA = "txtSelCriteria"
    Const gstrREQUEST_TXT_SERVER = "txtServer"
    Const gstrREQUEST_TXT_SITE = "txtSite"
    '
    ' Other Fields
    '
    Const gstrHIDDEN_C_PAGE = "hidcPage"
    Const gstrHIDDEN_CMD_GO_TO_PAGE = "hidCmdGoToPage"
    Const gstrHIDDEN_I_PAGE_GO_TO = "hidiPageGoTo"
    Const gstrHIDDEN_I_PAGE = "hidiPage"

    Const gstrTXT_PAGE_GO_TO = "txtPageGoTo"
    '
    ' Field Length Limitations
    '
    Const gcCH_ALIAS = 64
    Const gcCH_DISP_NAME = 256
    Const gcCH_MAX_NOTES = 1024
    '
    ' Session Properties
    '
    Const gstrSESS_ADS_SERVER = "sessServer"
    Const gstrSESS_ADS_O_ENTERPRISE = "sessO"
    Const gstrSESS_ADS_OU_SITE = "sessOU"
    Const gstrSESS_B_SUPPORTS_IE4_DHTML = "sessBSupportsIE4DHTML"
    Const gstrSESS_CMD = "sessCmd"
    Const gstrSESS_DL_ADS_PATH = "sessADsPath"
    Const gstrSESS_DL_ALIAS = "sessAlias"
    Const gstrSESS_DL_DISP_NAME = "sessDispName"
    Const gstrSESS_DL_MEMBER_PAGE = "sessDLMemberPage"
    Const gstrSESS_DL_PAGE = "sessDLPage"
    Const gstrSESS_SEL_CRITERIA = "sessSelCriteria"
    Const gstrSESS_SEL_CRITERIA_DL = "sessSelCriteriaDL"
    Const gstrSESS_SEL_DN_PAGE = "sessSelDNPage"
    '
    ' Commands
    '
    Const gstrCMD_ADD_DL = "AddDL"
    Const gstrCMD_ADD_DL_MEMBER = "AddDLMember"
    Const gstrCMD_DL_MAINT = "DLMaint"
    Const gstrCMD_DL_MAINT_CANCEL_ADD = "DLMaintCancelAdd"
    Const gstrCMD_DL_MAINT_GO_TO_PAGE = "DLMaintGoToPage"
    Const gstrCMD_DL_MAINT_NEW = "DLMaintNew"
    Const gstrCMD_DL_PROPERTIES = "DLProperties"
    Const gstrCMD_DL_PROPERTIES_GO_TO_PAGE = "DLPropertiesGoToPage"
    Const gstrCMD_DL_PROPERTIES_RETURN = "DLPropertiesRet"
    Const gstrCMD_DEL_DL = "DelDL"
    Const gstrCMD_DEL_DL_MEMBER = "DelDLMember"
    Const gstrCMD_DO_ADD_DL = "DoAddDL"
    Const gstrCMD_DO_ADD_DL_MEMBER = "DoAddDLMember"
    Const gstrCMD_DO_MOD_DL_OWNER = "DoModDLOwner"
    Const gstrCMD_FIND_DLS = "FindDLs"
    Const gstrCMD_FIND_ENTRIES = "FindEntries"
    Const gstrCMD_GO_TO_PAGE = "GoToPage"
    Const gstrCMD_MOD_DL_OWNER = "ModDLOwner"
    Const gstrCMD_NEXT_PAGE = "GoToNextPage"
    Const gstrCMD_PREV_PAGE = "GoToPrevPage"
    Const gstrCMD_SEL_DN_GO_TO_PAGE = "SelDNGoToPage"
    Const gstrCMD_SEL_EXCH_SERVER = "SelExchServer"
    '
    ' Messages
    '
    Const gstrMSG_CONFIRM_DEL = "Delete selected @?"
        Const gstrMSG_REPLACE_DL = "distribution list"
        Const gstrMSG_REPLACE_DL_MEMBERS = "distribution list members"
    Const gstrMSG_CONFIRM_RETURN_DL_MAINT = "Do you want to return to the Distribution List Maintenance page without completing updates to the distribution list?"
    Const gstrMSG_CONFIRM_CANCEL_ADD_1 = "The distribution list name and alias must be entered to add a distribution list.  You have not entered one or more of these fields."
    Const gstrMSG_CONFIRM_CANCEL_ADD_2 = "Press ""OK"" to return to the Distribution List Maintenance page without adding this distribution list or ""Cancel"" to remain on this page."
    Const gstrMSG_ALERT_CANT_ADD_DL_MEMBERS = "Unable to add distribution list members."
    Const gstrMSG_ALERT_CANT_CREATE_ADSI_EXCH_OBJ = "Unable to create ADSI object for the Microsoft Exchange server."
    Const gstrMSG_ALERT_CANT_CREATE_EXCH_DL = "Unable to create the distribution list."
    Const gstrMSG_ALERT_CANT_DEL_DL_MEMBERS = "Unable to delete distribution list members."
    Const gstrMSG_ALERT_CANT_DEL_DL = "Unable to delete distribution list."
    Const gstrMSG_ALERT_CANT_DISPLAY_DLS = "Unable to display distribution lists."
    Const gstrMSG_ALERT_CANT_DISPLAY_DL_PROPERTIES = "Unable to display distribution list properties."
    Const gstrMSG_ALERT_CANT_DISPLAY_QUERY_RESULTS = "Unable to display query results."
    Const gstrMSG_ALERT_CANT_MOD_DL_OWNER = "Unable to modify the distribution list owner."
    Const gstrMSG_ALERT_CANT_MOD_DL_PROPS = "Unable to modify distribution list properties."
    Const gstrMSG_ALERT_DL_MEMBERS_ADDED = "Distribution list member(s) were successfully added."
    Const gstrMSG_ALERT_DL_HAS_NO_OWNER = "The distribution list does not have an owner."
    Const gstrMSG_ALERT_FIND_ITEMS = "Find @."
        Const gstrMSG_REPLACE_DL_FOR_MAINT = "distribution lists for maintenance"
        Const gstrMSG_REPLACE_DL_MEMBERS_FOR_ADD = "distribution list members for addition"
        Const gstrMSG_REPLACE_DL_OWNER_FOR_SEL = "distribution list owner for selection"
    Const gstrMSG_ALERT_MUST_SEL_DL = "Select a distribution list for @."
        Const gstrMSG_REPLACE_MOD = "modification"
        Const gstrMSG_REPLACE_DEL = "deletion"
    Const gstrMSG_ALERT_MUST_SEL_DL_MEMBER = "Select distribution list members for @."
        Const gstrMSG_REPLACE_ADD = "addition"
    Const gstrMSG_ALERT_MUST_SEL_DL_OWNER = "Select a distribution list owner."
    Const gstrMSG_ALERT_MUST_BE_ENTERED = "@ must be entered."
        Const gstrMSG_REPLACE_ALIAS = "Alias"
        Const gstrMSG_REPLACE_DISP_NAME = "Display name"
        Const gstrMSG_REPLACE_ENTERPRISE = "Enterprise"
        Const gstrMSG_REPLACE_SEL_CRITERIA = "Selection criteria"
        Const gstrMSG_REPLACE_SERVER = "Server"
        Const gstrMSG_REPLACE_SITE = "Site"
    Const gstrMSG_ALERT_NONE_ON_FILE = "There are no @ on file."
        Const gstrMSG_REPLACE_DLS = "distribution lists matching the selection criteria"
        Const gstrMSG_REPLACE_MATCHING_ITEMS = "items matching the selection criteria"
    Const gstrMSG_ALERT_PAGE_NO_INVALID = "Page number must be an integer between @ and @."
    Const gstrMSG_ALERT_TXTAREA_MAX_EXCEEDED = "The @ field may contain a maximum of @ characters.  You have entered @ characters."
        Const gstrMSG_REPLACE_NOTES = "notes"

    Const gstrALT_GO_TO_PAGE = "Go to the @ page of @"
        Const gstrMSG_REPLACE_NEXT = "next"
        Const gstrMSG_REPLACE_PREV = "previous"
        Const gstrMSG_REPLACE_DL_S = "distribution lists"
        Const gstrMSG_REPLACE_SEL_S = "selections"
    '
    ' Special characters
    '
    Const gchCOMMA = ","
    Const gchQUOTE = """"
    Const gchREPLACE = "@"
    Const gchSPACE = " "
    Const gchZERO = "0"

    Const gjsNEW_LINE = "\n"

    Const gstrNONE = ""
    Const gstrDISP_NAME_OWNER_NONE = "None"

    Const ghtmlBG_COLOR = "#c0c0c0"
	Const grgchHTML_INVALID = "& ' < > """
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
    '
    ' Other constants
    '
    Const gpxlWIDTH_LST = 260
%>