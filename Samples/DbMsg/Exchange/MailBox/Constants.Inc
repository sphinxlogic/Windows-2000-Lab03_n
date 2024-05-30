<%
'<!--Mailbox Maintenance Sample Application-->
'<!--Constants.inc : Application constants-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Constants.inc contains global constants including request & session properties, 
' message text, special characters, etc.
'
    '
    ' Page Headings
    '
    Const gstrPAGE_HEADING_MB_MAINT = "Mailbox Maintenance"
    Const gstrHEADING_ADD = "Add @"
        Const gstrREPLACE_CR = "Custom Recipient (Internet)"
        Const gstrREPLACE_MB = "Mailbox"
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
    Const gstrASP_MAINTENANCE = "Maintenance.asp"
    Const gstrASP_PROPERTIES = "Properties.asp"
    Const gstrASP_HANDLE_CMDS = "HandleCmds.asp"
    Const gstrASP_LOGON = "Logon.asp"
    Const gstrASP_SEL_EXCH_SERVER = "SelExchServer.asp"
    '
    ' Image File Names
    '
    Const gstrIMG_CR = "cr.gif"
    Const gstrIMG_MB = "mb.gif"
    '
    ' Request Parameters
    '
    Const gstrREQUEST_CMD = "rqstCmd"
    Const gstrREQUEST_LST_RECIPIENTS = "rqstLstRecipients"
    Const gstrREQUEST_TXT_ENTERPRISE = "rqstTxtEnterprise"
    Const gstrREQUEST_TXT_SEL_CRITERIA = "rqstTxtSelCriteria"
    Const gstrREQUEST_TXT_SERVER = "rqstTxtServer"
    Const gstrREQUEST_TXT_SITE = "rqstTxtSite"

    Const gstrREQUEST_HID_NT_ACCT = "rqstHidNTAcct"
    Const gstrREQUEST_OPT_NT_ACCT = "rqstOptNTAcct"
        Const gstrREQUEST_OPT_NT_ACCT_OLD = "rqstOptNTAcctOld"
        Const gstrREQUEST_OPT_NT_ACCT_NEW = "rqstOptNTAcctNew"
    Const gstrREQUEST_TXT_ALIAS = "rqstTxtAlias"
    Const gstrREQUEST_TXT_ASSISTANT = "rqstTxtAssistant"
    Const gstrREQUEST_TXT_CITY = "rqstTxtCity"
    Const gstrREQUEST_TXT_COMPANY = "rqstTxtCompany"
    Const gstrREQUEST_TXT_COUNTRY = "rqstTxtCountry"
    Const gstrREQUEST_TXT_DEPT = "rqstTxtDept"
    Const gstrREQUEST_TXT_DISP_NAME = "rqstTxtDispName"
    Const gstrREQUEST_TXT_EMAIL_ADDRESS = "rqstTxtEmailAddr"
    Const gstrREQUEST_TXT_EXCH_ENTERPRISE = "rqstTxtExchEnterprise"
    Const gstrREQUEST_TXT_EXCH_SERVER = "rqstTxtExchServer"
    Const gstrREQUEST_TXT_EXCH_SITE = "rqstTxtExchSite"
    Const gstrREQUEST_TXT_NAME_FIRST = "rqstTxtNameFirst"
    Const gstrREQUEST_TXT_NAME_LAST = "rqstTxtNameLast"
    Const gstrREQUEST_TXT_NAME_MID_INITIAL = "rqstTxtNameMidInitial"
    Const gstrREQUEST_TXT_NOTES = "rqstTxtNotes"
    Const gstrREQUEST_TXT_NT_ACCT = "rqstTxtNTAcct"
    Const gstrREQUEST_TXT_NT_PASSWORD = "rqstTxtNTPassword"
    Const gstrREQUEST_TXT_OWNER = "rqstTxtOwner"
    Const gstrREQUEST_TXT_OFFICE = "rqstTxtOffice"
    Const gstrREQUEST_TXT_PHONE_ASSISTANT = "rqstTxtPhoneAssistant"
    Const gstrREQUEST_TXT_PHONE_BUS = "rqstTxtPhoneBus"
    Const gstrREQUEST_TXT_PHONE_2_BUS = "rqstTxtPhone2Bus"
    Const gstrREQUEST_TXT_PHONE_FAX = "rqstTxtPhoneFax"
    Const gstrREQUEST_TXT_PHONE_HOME = "rqstTxtPhoneHome"
    Const gstrREQUEST_TXT_PHONE_2_HOME = "rqstTxtPhone2Home"
    Const gstrREQUEST_TXT_PHONE_MOBILE = "rqstTxtPhoneMobile"
    Const gstrREQUEST_TXT_PHONE_PAGER = "rqstTxtPhonePager"
    Const gstrREQUEST_TXT_POSTAL_ADDRESS = "rqstTxtPostalAddress"
    Const gstrREQUEST_TXT_POSTAL_CODE = "rqstTxtPostalCode"
    Const gstrREQUEST_TXT_STATE = "rqstTxtState"
    Const gstrREQUEST_TXT_TITLE = "rqstTxtTitle"
    '
    ' Max Field Lengths
    '
    Const giTXT_MAX_LEN_ASSISTANT = 256
    Const giTXT_MAX_LEN_CITY = 128
    Const giTXT_MAX_LEN_COUNTRY = 128
    Const giTXT_MAX_LEN_DISP_NAME = 256
    Const giTXT_MAX_LEN_EMAIL_ADDRESS = 254
    Const giTXT_MAX_LEN_NAME_MID_INITIAL = 6
    Const giTXT_MAX_LEN_NORMAL = 64
    Const giTXT_MAX_LEN_NOTES = 1024
    Const giTXT_MAX_LEN_NT_ACCT = 64
    Const giTXT_MAX_LEN_NT_PASSWORD = 14
    Const giTXT_MAX_LEN_OFFICE = 128
    Const giTXT_MAX_LEN_POSTAL_ADDRESS = 1024
    Const giTXT_MAX_LEN_POSTAL_CODE = 40
    Const giTXT_MAX_LEN_STATE = 128
    '
    ' Text Input Sizes
    '
    Const giTXT_SIZE_NORMAL = -1
    Const giTXT_SIZE_NAME_FIRST = 8
    Const giTXT_SIZE_NAME_MID_INITIAL = 3
    Const giTXT_SIZE_EMAIL_ADDRESS = 56
    '
    ' Other Fields
    '
    Const gstrHIDDEN_C_PAGE = "hidcPage"
    Const gstrHIDDEN_CMD_GO_TO_PAGE = "hidCmdGoToPage"
    Const gstrHIDDEN_I_PAGE_GO_TO = "hidiPageGoTo"
    Const gstrHIDDEN_I_PAGE = "hidiPage"

    Const gstrTXT_PAGE_GO_TO = "txtPageGoTo"
    '
    ' Session Properties
    '
    Const gstrSESS_ADS_SERVER = "sessServer"
    Const gstrSESS_ADS_O_ENTERPRISE = "sessO"
    Const gstrSESS_ADS_OU_SITE = "sessOU"
    Const gstrSESS_B_IS_MAILBOX = "sessBIsMailbox"
    Const gstrSESS_B_SUPPORTS_IE4_DHTML = "sessBSupportsIE4DHTML"
    Const gstrSESS_CMD = "sessCmd"
    Const gstrSESS_ADS_PATH = "sessADsPath"
    Const gstrSESS_RECIPIENT_PAGE = "sessRecipientPage"
    Const gstrSESS_SEL_CRITERIA = "sessSelCriteria"
    Const gstrSESS_SEL_CRITERIA_RECIPIENT = "sessSelCriteriaRecipient"
    '
    ' Commands
    '
    Const gstrCMD_ADD_CR = "AddCR"
    Const gstrCMD_ADD_MB = "AddMB"
    Const gstrCMD_MAINTENANCE = "Maintenance"
    Const gstrCMD_MAINTENANCE_GO_TO_PAGE = "MaintenanceGoToPage"
    Const gstrCMD_MAINTENANCE_NEW = "MaintenanceNew"
    Const gstrCMD_PROPERTIES = "Properties"
    Const gstrCMD_DEL_RECIPIENTS = "DelRecipients"
    Const gstrCMD_DO_ADD = "DoAdd"
    Const gstrCMD_DO_MOD = "DoMod"
    Const gstrCMD_FIND_RECIPIENTS = "FindRecipients"
    Const gstrCMD_GO_TO_PAGE = "GoToPage"
    Const gstrCMD_NEXT_PAGE = "GoToNextPage"
    Const gstrCMD_PREV_PAGE = "GoToPrevPage"
    Const gstrCMD_SEL_EXCH_SERVER = "SelExchServer"
    '
    ' Messages
    '
    Const gstrMSG_ALERT_ADD_CR_CONFIRMED = "Custom recipient was added."
    Const gstrMSG_ALERT_ADD_MB_CONFIRMED = "Mailbox was added."
    Const gstrMSG_ALERT_CANT_CREATE_ADSI_EXCH_OBJ = "Unable to create ADSI object for the Microsoft Exchange server."
    Const gstrMSG_ALERT_CANT_ADD_CR = "Unable to add custom recipient."
    Const gstrMSG_ALERT_CANT_ADD_MB = "Unable to add mailbox."
    Const gstrMSG_ALERT_CANT_DEL = "Unable to delete selection."
    Const gstrMSG_ALERT_CANT_DISPLAY_RECIPIENTS = "Unable to display recipients."
    Const gstrMSG_ALERT_CANT_DISPLAY_PROPERTIES = "Unable to display properties."
    Const gstrMSG_ALERT_CANT_MOD_CR = "Unable to modify custom recipient."
    Const gstrMSG_ALERT_CANT_MOD_MB = "Unable to modify mailbox."
    Const gstrMSG_ALERT_FIND_RECIPIENTS_FOR_MAINT = "Find recipients for maintenance."
    Const gstrMSG_ALERT_MOD_CR_CONFIRMED = "Custom recipient was updated."
    Const gstrMSG_ALERT_MOD_MB_CONFIRMED = "Mailbox was updated."
    Const gstrMSG_ALERT_MUST_SEL_RECIPIENT = "Select a recipient for @."
        Const gstrMSG_REPLACE_MOD = "modification"
        Const gstrMSG_REPLACE_DEL = "deletion"
    Const gstrMSG_ALERT_MUST_BE_ENTERED = "@ must be entered."
        Const gstrMSG_REPLACE_ALIAS = "Alias"
        Const gstrMSG_REPLACE_DISP_NAME = "Display name"
        Const gstrMSG_REPLACE_EMAIL_ADDRESS = "E-mail address"
        Const gstrMSG_REPLACE_ENTERPRISE = "Enterprise"
        Const gstrMSG_REPLACE_NT_ACCT = "NT account"
        Const gstrMSG_REPLACE_SEL_CRITERIA = "Selection criteria"
        Const gstrMSG_REPLACE_SERVER = "Server"
        Const gstrMSG_REPLACE_SITE = "Site"
    Const gstrMSG_ALERT_NONE_ON_FILE = "There are no @ on file."
        Const gstrMSG_REPLACE_MATCHING_RECIPIENTS = "recipients matching the selection criteria"
        Const gstrMSG_REPLACE_MATCHING_ITEMS = "items matching the selection criteria"
    Const gstrMSG_ALERT_PAGE_NO_INVALID = "Page number must be an integer between @ and @."
    Const gstrMSG_ALERT_TXTAREA_MAX_EXCEEDED = "The @ field may contain a maximum of @ characters.  You have entered @ characters."
        Const gstrMSG_REPLACE_ADDRESS = "address"
        Const gstrMSG_REPLACE_NOTES = "notes"
    Const gstrMSG_CONFIRM_DEL_RECIPIENTS = "Delete selected recipient(s)?"

    Const gstrALT_GO_TO_PAGE = "Go to the @ page of @"
        Const gstrMSG_REPLACE_NEXT = "next"
        Const gstrMSG_REPLACE_PREV = "previous"
        Const gstrMSG_REPLACE_RECIPIENTS = "recipients"
        Const gstrMSG_REPLACE_SEL_S = "selections"
    '
    ' Booleans
    '
    Const gbDO_ON_CHANGE = True
    Const gbNO_ON_CHANGE = False
    '
    ' Special characters
    '
    Const gchBACK_SLASH = "\"
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
    Const gstrCSS_CLASS_FONT_HEADING_SMALL = "cssFontHeadingSmall"
    '
    ' Other constants
    '
    Const gpxlWIDTH_LST = 260
%>