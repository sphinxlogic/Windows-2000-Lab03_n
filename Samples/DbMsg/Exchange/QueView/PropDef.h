// -----------------------------------------------------------------------------
// PropDef.h:  This defines an array of mapi property ids and types.
//             Include this file only once in your code for the entire project.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _PROPDEF_H_
#define _PROPDEF_H_

// -----------------------------------------------------------------------------

static IDList PropIDs[] = 
{
    PROP_ID( PR_ARRIVAL_TIME),    "PR_ARRIVAL_TIME",
    PROP_ID( PR_GW_ADMIN_OPERATIONS), "PR_GW_ADMIN_OPERATIONS",
    PROP_ID( PR_IMPORTANCE),  "PR_IMPORTANCE",
    PROP_ID( PR_ORIGINATOR_ADDR), "PR_ORIGINATOR_ADDR",
    PROP_ID( PR_ORIGINATOR_ADDRTYPE), "PR_ORIGINATOR_ADDRTYPE",
    PROP_ID( PR_ORIGINATOR_NAME), "PR_ORIGINATOR_NAME",
    PROP_ID( PR_SENSITIVITY), "PR_SENSITIVITY",
    PROP_ID( PR_DISPLAY_TO),  "PR_DISPLAY_TO",
    PROP_ID( PR_HASATTACH),   "PR_HASATTACH",
    PROP_ID( PR_MESSAGE_CLASS),   "PR_MESSAGE_CLASS",
    PROP_ID( PR_MESSAGE_SIZE),    "PR_MESSAGE_SIZE",
    PROP_ID( PR_PRIORITY),    "PR_PRIORITY",
    PROP_ID( PR_SUBJECT), "PR_SUBJECT",
    PROP_ID( PR_ACKNOWLEDGEMENT_MODE),    "PR_ACKNOWLEDGEMENT_MODE",
    PROP_ID( PR_ALTERNATE_RECIPIENT_ALLOWED), "PR_ALTERNATE_RECIPIENT_ALLOWED",
    PROP_ID( PR_AUTHORIZING_USERS),   "PR_AUTHORIZING_USERS",
    PROP_ID( PR_AUTO_FORWARD_COMMENT),    "PR_AUTO_FORWARD_COMMENT",
    PROP_ID( PR_AUTO_FORWARDED),  "PR_AUTO_FORWARDED",
    PROP_ID( PR_CONTENT_CONFIDENTIALITY_ALGORITHM_ID),    "PR_CONTENT_CONFIDENTIALITY_ALGORITHM_ID",
    PROP_ID( PR_CONTENT_CORRELATOR),  "PR_CONTENT_CORRELATOR",
    PROP_ID( PR_CONTENT_IDENTIFIER),  "PR_CONTENT_IDENTIFIER",
    PROP_ID( PR_CONTENT_LENGTH),  "PR_CONTENT_LENGTH",
    PROP_ID( PR_CONTENT_RETURN_REQUESTED),    "PR_CONTENT_RETURN_REQUESTED",
    PROP_ID( PR_CONVERSATION_KEY),    "PR_CONVERSATION_KEY",
    PROP_ID( PR_CONVERSION_EITS), "PR_CONVERSION_EITS",
    PROP_ID( PR_CONVERSION_WITH_LOSS_PROHIBITED), "PR_CONVERSION_WITH_LOSS_PROHIBITED",
    PROP_ID( PR_CONVERTED_EITS),  "PR_CONVERTED_EITS",
    PROP_ID( PR_DEFERRED_DELIVERY_TIME),  "PR_DEFERRED_DELIVERY_TIME",
    PROP_ID( PR_DELIVER_TIME),    "PR_DELIVER_TIME",
    PROP_ID( PR_DISCARD_REASON),  "PR_DISCARD_REASON",
    PROP_ID( PR_DISCLOSURE_OF_RECIPIENTS),    "PR_DISCLOSURE_OF_RECIPIENTS",
    PROP_ID( PR_DL_EXPANSION_HISTORY),    "PR_DL_EXPANSION_HISTORY",
    PROP_ID( PR_DL_EXPANSION_PROHIBITED), "PR_DL_EXPANSION_PROHIBITED",
    PROP_ID( PR_EXPIRY_TIME), "PR_EXPIRY_TIME",
    PROP_ID( PR_IMPLICIT_CONVERSION_PROHIBITED),  "PR_IMPLICIT_CONVERSION_PROHIBITED",
    PROP_ID( PR_IMPORTANCE),  "PR_IMPORTANCE",
    PROP_ID( PR_IPM_ID),  "PR_IPM_ID",
    PROP_ID( PR_LATEST_DELIVERY_TIME),    "PR_LATEST_DELIVERY_TIME",
    PROP_ID( PR_MESSAGE_DELIVERY_ID), "PR_MESSAGE_DELIVERY_ID",
    PROP_ID( PR_MESSAGE_SECURITY_LABEL),  "PR_MESSAGE_SECURITY_LABEL",
    PROP_ID( PR_OBSOLETED_IPMS),  "PR_OBSOLETED_IPMS",
    PROP_ID( PR_ORIGINALLY_INTENDED_RECIPIENT_NAME),  "PR_ORIGINALLY_INTENDED_RECIPIENT_NAME",
    PROP_ID( PR_ORIGINAL_EITS),   "PR_ORIGINAL_EITS",
    PROP_ID( PR_ORIGINATOR_CERTIFICATE),  "PR_ORIGINATOR_CERTIFICATE",
    PROP_ID( PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED),    "PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED",
    PROP_ID( PR_ORIGINATOR_RETURN_ADDRESS),   "PR_ORIGINATOR_RETURN_ADDRESS",
    PROP_ID( PR_PARENT_KEY),  "PR_PARENT_KEY",
    PROP_ID( PR_PROOF_OF_SUBMISSION_REQUESTED),   "PR_PROOF_OF_SUBMISSION_REQUESTED",
    PROP_ID( PR_READ_RECEIPT_REQUESTED),  "PR_READ_RECEIPT_REQUESTED",
    PROP_ID( PR_RECEIPT_TIME),    "PR_RECEIPT_TIME",
    PROP_ID( PR_RECIPIENT_REASSIGNMENT_PROHIBITED),   "PR_RECIPIENT_REASSIGNMENT_PROHIBITED",
    PROP_ID( PR_REDIRECTION_HISTORY), "PR_REDIRECTION_HISTORY",
    PROP_ID( PR_RELATED_IPMS),    "PR_RELATED_IPMS",
    PROP_ID( PR_LANGUAGES),   "PR_LANGUAGES",
    PROP_ID( PR_REPLY_TIME),  "PR_REPLY_TIME",
    PROP_ID( PR_REPORT_TAG),  "PR_REPORT_TAG",
    PROP_ID( PR_REPORT_TIME), "PR_REPORT_TIME",
    PROP_ID( PR_RETURNED_IPM),    "PR_RETURNED_IPM",
    PROP_ID( PR_SECURITY),    "PR_SECURITY",
    PROP_ID( PR_INCOMPLETE_COPY), "PR_INCOMPLETE_COPY",
    PROP_ID( PR_SENSITIVITY), "PR_SENSITIVITY",
    PROP_ID( PR_SUBJECT_IPM), "PR_SUBJECT_IPM",
    PROP_ID( PR_CLIENT_SUBMIT_TIME),  "PR_CLIENT_SUBMIT_TIME",
    PROP_ID( PR_REPORT_NAME), "PR_REPORT_NAME",
    PROP_ID( PR_SENT_REPRESENTING_SEARCH_KEY),    "PR_SENT_REPRESENTING_SEARCH_KEY",
    PROP_ID( PR_X400_CONTENT_TYPE),   "PR_X400_CONTENT_TYPE",
    PROP_ID( PR_NON_RECEIPT_REASON),  "PR_NON_RECEIPT_REASON",
    PROP_ID( PR_RECEIVED_BY_ENTRYID), "PR_RECEIVED_BY_ENTRYID",
    PROP_ID( PR_RECEIVED_BY_NAME),    "PR_RECEIVED_BY_NAME",
    PROP_ID( PR_SENT_REPRESENTING_ENTRYID),   "PR_SENT_REPRESENTING_ENTRYID",
    PROP_ID( PR_SENT_REPRESENTING_NAME),  "PR_SENT_REPRESENTING_NAME",
    PROP_ID( PR_RCVD_REPRESENTING_ENTRYID),   "PR_RCVD_REPRESENTING_ENTRYID",
    PROP_ID( PR_RCVD_REPRESENTING_NAME),  "PR_RCVD_REPRESENTING_NAME",
    PROP_ID( PR_REPORT_ENTRYID),  "PR_REPORT_ENTRYID",
    PROP_ID( PR_READ_RECEIPT_ENTRYID),    "PR_READ_RECEIPT_ENTRYID",
    PROP_ID( PR_MESSAGE_SUBMISSION_ID),   "PR_MESSAGE_SUBMISSION_ID",
    PROP_ID( PR_PROVIDER_SUBMIT_TIME),    "PR_PROVIDER_SUBMIT_TIME",
    PROP_ID( PR_ORIGINAL_SUBJECT),    "PR_ORIGINAL_SUBJECT",
    PROP_ID( PR_DISC_VAL),    "PR_DISC_VAL",
    PROP_ID( PR_ORIG_MESSAGE_CLASS),  "PR_ORIG_MESSAGE_CLASS",
    PROP_ID( PR_ORIGINAL_AUTHOR_ENTRYID), "PR_ORIGINAL_AUTHOR_ENTRYID",
    PROP_ID( PR_ORIGINAL_AUTHOR_NAME),    "PR_ORIGINAL_AUTHOR_NAME",
    PROP_ID( PR_ORIGINAL_SUBMIT_TIME),    "PR_ORIGINAL_SUBMIT_TIME",
    PROP_ID( PR_REPLY_RECIPIENT_ENTRIES), "PR_REPLY_RECIPIENT_ENTRIES",
    PROP_ID( PR_REPLY_RECIPIENT_NAMES),   "PR_REPLY_RECIPIENT_NAMES",
    PROP_ID( PR_RECEIVED_BY_SEARCH_KEY),  "PR_RECEIVED_BY_SEARCH_KEY",
    PROP_ID( PR_RCVD_REPRESENTING_SEARCH_KEY),    "PR_RCVD_REPRESENTING_SEARCH_KEY",
    PROP_ID( PR_READ_RECEIPT_SEARCH_KEY), "PR_READ_RECEIPT_SEARCH_KEY",
    PROP_ID( PR_REPORT_SEARCH_KEY),   "PR_REPORT_SEARCH_KEY",
    PROP_ID( PR_ORIGINAL_DELIVERY_TIME),  "PR_ORIGINAL_DELIVERY_TIME",
    PROP_ID( PR_ORIGINAL_AUTHOR_SEARCH_KEY),  "PR_ORIGINAL_AUTHOR_SEARCH_KEY",
    PROP_ID( PR_MESSAGE_TO_ME),   "PR_MESSAGE_TO_ME",
    PROP_ID( PR_MESSAGE_CC_ME),   "PR_MESSAGE_CC_ME",
    PROP_ID( PR_MESSAGE_RECIP_ME),    "PR_MESSAGE_RECIP_ME",
    PROP_ID( PR_ORIGINAL_SENDER_NAME),    "PR_ORIGINAL_SENDER_NAME",
    PROP_ID( PR_ORIGINAL_SENDER_ENTRYID), "PR_ORIGINAL_SENDER_ENTRYID",
    PROP_ID( PR_ORIGINAL_SENDER_SEARCH_KEY),  "PR_ORIGINAL_SENDER_SEARCH_KEY",
    PROP_ID( PR_ORIGINAL_SENT_REPRESENTING_NAME), "PR_ORIGINAL_SENT_REPRESENTING_NAME",
    PROP_ID( PR_ORIGINAL_SENT_REPRESENTING_ENTRYID),  "PR_ORIGINAL_SENT_REPRESENTING_ENTRYID",
    PROP_ID( PR_ORIGINAL_SENT_REPRESENTING_SEARCH_KEY),   "PR_ORIGINAL_SENT_REPRESENTING_SEARCH_KEY",
    PROP_ID( PR_START_DATE),  "PR_START_DATE",
    PROP_ID( PR_END_DATE),    "PR_END_DATE",
    PROP_ID( PR_OWNER_APPT_ID),   "PR_OWNER_APPT_ID",
    PROP_ID( PR_RESPONSE_REQUESTED),  "PR_RESPONSE_REQUESTED",
    PROP_ID( PR_SENT_REPRESENTING_ADDRTYPE),  "PR_SENT_REPRESENTING_ADDRTYPE",
    PROP_ID( PR_SENT_REPRESENTING_EMAIL_ADDRESS), "PR_SENT_REPRESENTING_EMAIL_ADDRESS",
    PROP_ID( PR_ORIGINAL_SENDER_ADDRTYPE),    "PR_ORIGINAL_SENDER_ADDRTYPE",
    PROP_ID( PR_ORIGINAL_SENDER_EMAIL_ADDRESS),   "PR_ORIGINAL_SENDER_EMAIL_ADDRESS",
    PROP_ID( PR_ORIGINAL_SENT_REPRESENTING_ADDRTYPE), "PR_ORIGINAL_SENT_REPRESENTING_ADDRTYPE",
    PROP_ID( PR_ORIGINAL_SENT_REPRESENTING_EMAIL_ADDRESS),    "PR_ORIGINAL_SENT_REPRESENTING_EMAIL_ADDRESS",
    PROP_ID( PR_CONVERSATION_TOPIC),  "PR_CONVERSATION_TOPIC",
    PROP_ID( PR_CONVERSATION_INDEX),  "PR_CONVERSATION_INDEX",
    PROP_ID( PR_BODY),    "PR_BODY",
    PROP_ID( PR_REPORT_TEXT), "PR_REPORT_TEXT",
    PROP_ID( PR_ORIGINATOR_AND_DL_EXPANSION_HISTORY), "PR_ORIGINATOR_AND_DL_EXPANSION_HISTORY",
    PROP_ID( PR_REPORTING_DL_NAME),   "PR_REPORTING_DL_NAME",
    PROP_ID( PR_REPORTING_MTA_CERTIFICATE),   "PR_REPORTING_MTA_CERTIFICATE",
    PROP_ID( PR_RTF_SYNC_BODY_CRC),   "PR_RTF_SYNC_BODY_CRC",
    PROP_ID( PR_RTF_SYNC_BODY_COUNT), "PR_RTF_SYNC_BODY_COUNT",
    PROP_ID( PR_RTF_SYNC_BODY_TAG),   "PR_RTF_SYNC_BODY_TAG",
    PROP_ID( PR_RTF_COMPRESSED),  "PR_RTF_COMPRESSED",
    PROP_ID( PR_RTF_SYNC_PREFIX_COUNT),   "PR_RTF_SYNC_PREFIX_COUNT",
    PROP_ID( PR_RTF_SYNC_TRAILING_COUNT), "PR_RTF_SYNC_TRAILING_COUNT",
    PROP_ID( PR_ORIGINALLY_INTENDED_RECIP_ENTRYID),   "PR_ORIGINALLY_INTENDED_RECIP_ENTRYID",
    PROP_ID( PR_PREPROCESS),  "PR_PREPROCESS",
    PROP_ID( PR_CONTENT_INTEGRITY_CHECK), "PR_CONTENT_INTEGRITY_CHECK",
    PROP_ID( PR_EXPLICIT_CONVERSION), "PR_EXPLICIT_CONVERSION",
    PROP_ID( PR_IPM_RETURN_REQUESTED),    "PR_IPM_RETURN_REQUESTED",
    PROP_ID( PR_MESSAGE_TOKEN),   "PR_MESSAGE_TOKEN",
    PROP_ID( PR_NDR_REASON_CODE), "PR_NDR_REASON_CODE",
    PROP_ID( PR_NDR_DIAG_CODE),   "PR_NDR_DIAG_CODE",
    PROP_ID( PR_NON_RECEIPT_NOTIFICATION_REQUESTED),  "PR_NON_RECEIPT_NOTIFICATION_REQUESTED",
    PROP_ID( PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED),    "PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED",
    PROP_ID( PR_ORIGINATOR_REQUESTED_ALTERNATE_RECIPIENT),    "PR_ORIGINATOR_REQUESTED_ALTERNATE_RECIPIENT",
    PROP_ID( PR_PHYSICAL_DELIVERY_BUREAU_FAX_DELIVERY),   "PR_PHYSICAL_DELIVERY_BUREAU_FAX_DELIVERY",
    PROP_ID( PR_PHYSICAL_DELIVERY_MODE),  "PR_PHYSICAL_DELIVERY_MODE",
    PROP_ID( PR_PHYSICAL_DELIVERY_REPORT_REQUEST),    "PR_PHYSICAL_DELIVERY_REPORT_REQUEST",
    PROP_ID( PR_PHYSICAL_FORWARDING_ADDRESS), "PR_PHYSICAL_FORWARDING_ADDRESS",
    PROP_ID( PR_PHYSICAL_FORWARDING_ADDRESS_REQUESTED),   "PR_PHYSICAL_FORWARDING_ADDRESS_REQUESTED",
    PROP_ID( PR_PHYSICAL_FORWARDING_PROHIBITED),  "PR_PHYSICAL_FORWARDING_PROHIBITED",
    PROP_ID( PR_PHYSICAL_RENDITION_ATTRIBUTES),   "PR_PHYSICAL_RENDITION_ATTRIBUTES",
    PROP_ID( PR_PROOF_OF_DELIVERY),   "PR_PROOF_OF_DELIVERY",
    PROP_ID( PR_PROOF_OF_DELIVERY_REQUESTED), "PR_PROOF_OF_DELIVERY_REQUESTED",
    PROP_ID( PR_RECIPIENT_CERTIFICATE),   "PR_RECIPIENT_CERTIFICATE",
    PROP_ID( PR_RECIPIENT_NUMBER_FOR_ADVICE), "PR_RECIPIENT_NUMBER_FOR_ADVICE",
    PROP_ID( PR_RECIPIENT_TYPE),  "PR_RECIPIENT_TYPE",
    PROP_ID( PR_REGISTERED_MAIL_TYPE),    "PR_REGISTERED_MAIL_TYPE",
    PROP_ID( PR_REPLY_REQUESTED), "PR_REPLY_REQUESTED",
    PROP_ID( PR_REQUESTED_DELIVERY_METHOD),   "PR_REQUESTED_DELIVERY_METHOD",
    PROP_ID( PR_SENDER_ENTRYID),  "PR_SENDER_ENTRYID",
    PROP_ID( PR_SENDER_NAME), "PR_SENDER_NAME",
    PROP_ID( PR_TYPE_OF_MTS_USER),    "PR_TYPE_OF_MTS_USER",
    PROP_ID( PR_SENDER_SEARCH_KEY),   "PR_SENDER_SEARCH_KEY",
    PROP_ID( PR_SENDER_ADDRTYPE), "PR_SENDER_ADDRTYPE",
    PROP_ID( PR_SENDER_EMAIL_ADDRESS),    "PR_SENDER_EMAIL_ADDRESS",
    PROP_ID( PR_CURRENT_VERSION), "PR_CURRENT_VERSION",
    PROP_ID( PR_DELETE_AFTER_SUBMIT), "PR_DELETE_AFTER_SUBMIT",
    PROP_ID( PR_DISPLAY_BCC), "PR_DISPLAY_BCC",
    PROP_ID( PR_DISPLAY_CC),  "PR_DISPLAY_CC",
    PROP_ID( PR_PARENT_DISPLAY),  "PR_PARENT_DISPLAY",
    PROP_ID( PR_MESSAGE_DELIVERY_TIME),   "PR_MESSAGE_DELIVERY_TIME",
    PROP_ID( PR_MESSAGE_FLAGS),   "PR_MESSAGE_FLAGS",
    PROP_ID( PR_PARENT_ENTRYID),  "PR_PARENT_ENTRYID",
    PROP_ID( PR_SENTMAIL_ENTRYID),    "PR_SENTMAIL_ENTRYID",
    PROP_ID( PR_CORRELATE),   "PR_CORRELATE",
    PROP_ID( PR_CORRELATE_MTSID), "PR_CORRELATE_MTSID",
    PROP_ID( PR_DISCRETE_VALUES), "PR_DISCRETE_VALUES",
    PROP_ID( PR_RESPONSIBILITY),  "PR_RESPONSIBILITY",
    PROP_ID( PR_SPOOLER_STATUS),  "PR_SPOOLER_STATUS",
    PROP_ID( PR_TRANSPORT_STATUS),    "PR_TRANSPORT_STATUS",
    PROP_ID( PR_MESSAGE_RECIPIENTS),  "PR_MESSAGE_RECIPIENTS",
    PROP_ID( PR_MESSAGE_ATTACHMENTS), "PR_MESSAGE_ATTACHMENTS",
    PROP_ID( PR_SUBMIT_FLAGS),    "PR_SUBMIT_FLAGS",
    PROP_ID( PR_TRANSPORT_KEY),   "PR_TRANSPORT_KEY",
    PROP_ID( PR_MSG_STATUS),  "PR_MSG_STATUS",
    PROP_ID( PR_MESSAGE_DOWNLOAD_TIME),   "PR_MESSAGE_DOWNLOAD_TIME",
    PROP_ID( PR_CREATION_VERSION),    "PR_CREATION_VERSION",
    PROP_ID( PR_MODIFY_VERSION),  "PR_MODIFY_VERSION",
    PROP_ID( PR_BODY_CRC),    "PR_BODY_CRC",
    PROP_ID( PR_NORMALIZED_SUBJECT),  "PR_NORMALIZED_SUBJECT",
    PROP_ID( PR_RTF_IN_SYNC), "PR_RTF_IN_SYNC",
    PROP_ID( PR_ATTACH_SIZE), "PR_ATTACH_SIZE",
    PROP_ID( PR_ATTACH_NUM),  "PR_ATTACH_NUM",
    PROP_ID( PR_ORIGINAL_DISPLAY_BCC),    "PR_ORIGINAL_DISPLAY_BCC",
    PROP_ID( PR_ORIGINAL_DISPLAY_CC), "PR_ORIGINAL_DISPLAY_CC",
    PROP_ID( PR_ORIGINAL_DISPLAY_TO), "PR_ORIGINAL_DISPLAY_TO",
    PROP_ID( PR_ENTRYID), "PR_ENTRYID",
    PROP_ID( PR_OBJECT_TYPE), "PR_OBJECT_TYPE",
    PROP_ID( PR_ICON),    "PR_ICON",
    PROP_ID( PR_MINI_ICON),   "PR_MINI_ICON",
    PROP_ID( PR_STORE_ENTRYID),   "PR_STORE_ENTRYID",
    PROP_ID( PR_STORE_RECORD_KEY),    "PR_STORE_RECORD_KEY",
    PROP_ID( PR_RECORD_KEY),  "PR_RECORD_KEY",
    PROP_ID( PR_MAPPING_SIGNATURE),   "PR_MAPPING_SIGNATURE",
    PROP_ID( PR_ACCESS_LEVEL),    "PR_ACCESS_LEVEL",
    PROP_ID( PR_INSTANCE_KEY),    "PR_INSTANCE_KEY",
    PROP_ID( PR_ROW_TYPE),    "PR_ROW_TYPE",
    PROP_ID( PR_ACCESS),  "PR_ACCESS",
    PROP_ID( PR_ROWID),   "PR_ROWID",
    PROP_ID( PR_DISPLAY_NAME),    "PR_DISPLAY_NAME",
    PROP_ID( PR_ADDRTYPE),    "PR_ADDRTYPE",
    PROP_ID( PR_EMAIL_ADDRESS),   "PR_EMAIL_ADDRESS",
    PROP_ID( PR_COMMENT), "PR_COMMENT",
    PROP_ID( PR_DEPTH),   "PR_DEPTH",
    PROP_ID( PR_PROVIDER_DISPLAY),    "PR_PROVIDER_DISPLAY",
    PROP_ID( PR_CREATION_TIME),   "PR_CREATION_TIME",
    PROP_ID( PR_LAST_MODIFICATION_TIME),  "PR_LAST_MODIFICATION_TIME",
    PROP_ID( PR_RESOURCE_FLAGS),  "PR_RESOURCE_FLAGS",
    PROP_ID( PR_PROVIDER_DLL_NAME),   "PR_PROVIDER_DLL_NAME",
    PROP_ID( PR_SEARCH_KEY),  "PR_SEARCH_KEY",
    PROP_ID( PR_PROVIDER_UID),    "PR_PROVIDER_UID",
    PROP_ID( PR_PROVIDER_ORDINAL),    "PR_PROVIDER_ORDINAL",
//    PR_FORM_VERSION,    "PR_FORM_VERSION",
//    PR_FORM_CLSID,  "PR_FORM_CLSID",
//    PR_FORM_CONTACT_NAME,   "PR_FORM_CONTACT_NAME",
//    PR_FORM_CATEGORY,   "PR_FORM_CATEGORY",
//    PR_FORM_CATEGORY_SUB,   "PR_FORM_CATEGORY_SUB",
//    PR_FORM_HOST_MAP,   "PR_FORM_HOST_MAP",
//    PR_FORM_HIDDEN, "PR_FORM_HIDDEN",
//    PR_FORM_DESIGNER_NAME,  "PR_FORM_DESIGNER_NAME",
//    PR_FORM_DESIGNER_GUID,  "PR_FORM_DESIGNER_GUID",
//    PR_FORM_MESSAGE_BEHAVIOR,   "PR_FORM_MESSAGE_BEHAVIOR",
    PROP_ID( PR_DEFAULT_STORE),   "PR_DEFAULT_STORE",
    PROP_ID( PR_STORE_SUPPORT_MASK),  "PR_STORE_SUPPORT_MASK",
    PROP_ID( PR_IPM_SUBTREE_SEARCH_KEY),  "PR_IPM_SUBTREE_SEARCH_KEY",
    PROP_ID( PR_IPM_OUTBOX_SEARCH_KEY),   "PR_IPM_OUTBOX_SEARCH_KEY",
    PROP_ID( PR_IPM_WASTEBASKET_SEARCH_KEY),  "PR_IPM_WASTEBASKET_SEARCH_KEY",
    PROP_ID( PR_IPM_SENTMAIL_SEARCH_KEY), "PR_IPM_SENTMAIL_SEARCH_KEY",
    PROP_ID( PR_MDB_PROVIDER),    "PR_MDB_PROVIDER",
    PROP_ID( PR_RECEIVE_FOLDER_SETTINGS), "PR_RECEIVE_FOLDER_SETTINGS",
    PROP_ID( PR_VALID_FOLDER_MASK),   "PR_VALID_FOLDER_MASK",
    PROP_ID( PR_IPM_SUBTREE_ENTRYID), "PR_IPM_SUBTREE_ENTRYID",
    PROP_ID( PR_IPM_OUTBOX_ENTRYID),  "PR_IPM_OUTBOX_ENTRYID",
    PROP_ID( PR_IPM_WASTEBASKET_ENTRYID), "PR_IPM_WASTEBASKET_ENTRYID",
    PROP_ID( PR_IPM_SENTMAIL_ENTRYID),    "PR_IPM_SENTMAIL_ENTRYID",
    PROP_ID( PR_VIEWS_ENTRYID),   "PR_VIEWS_ENTRYID",
    PROP_ID( PR_COMMON_VIEWS_ENTRYID),    "PR_COMMON_VIEWS_ENTRYID",
    PROP_ID( PR_FINDER_ENTRYID),  "PR_FINDER_ENTRYID",
    PROP_ID( PR_CONTAINER_FLAGS), "PR_CONTAINER_FLAGS",
    PROP_ID( PR_FOLDER_TYPE), "PR_FOLDER_TYPE",
    PROP_ID( PR_CONTENT_COUNT),   "PR_CONTENT_COUNT",
    PROP_ID( PR_CONTENT_UNREAD),  "PR_CONTENT_UNREAD",
    PROP_ID( PR_CREATE_TEMPLATES),    "PR_CREATE_TEMPLATES",
    PROP_ID( PR_DETAILS_TABLE),   "PR_DETAILS_TABLE",
    PROP_ID( PR_SEARCH),  "PR_SEARCH",
    PROP_ID( PR_SELECTABLE),  "PR_SELECTABLE",
    PROP_ID( PR_SUBFOLDERS),  "PR_SUBFOLDERS",
    PROP_ID( PR_STATUS),  "PR_STATUS",
    PROP_ID( PR_ANR), "PR_ANR",
    PROP_ID( PR_CONTENTS_SORT_ORDER), "PR_CONTENTS_SORT_ORDER",
    PROP_ID( PR_CONTAINER_HIERARCHY), "PR_CONTAINER_HIERARCHY",
    PROP_ID( PR_CONTAINER_CONTENTS),  "PR_CONTAINER_CONTENTS",
    PROP_ID( PR_FOLDER_ASSOCIATED_CONTENTS),  "PR_FOLDER_ASSOCIATED_CONTENTS",
    PROP_ID( PR_DEF_CREATE_DL),   "PR_DEF_CREATE_DL",
    PROP_ID( PR_DEF_CREATE_MAILUSER), "PR_DEF_CREATE_MAILUSER",
    PROP_ID( PR_CONTAINER_CLASS), "PR_CONTAINER_CLASS",
    PROP_ID( PR_CONTAINER_MODIFY_VERSION),    "PR_CONTAINER_MODIFY_VERSION",
    PROP_ID( PR_AB_PROVIDER_ID),  "PR_AB_PROVIDER_ID",
    PROP_ID( PR_ATTACHMENT_X400_PARAMETERS),  "PR_ATTACHMENT_X400_PARAMETERS",
    PROP_ID( PR_ATTACH_DATA_BIN), "PR_ATTACH_DATA_BIN",
    PROP_ID( PR_ATTACH_DATA_OBJ), "PR_ATTACH_DATA_OBJ",
    PROP_ID( PR_ATTACH_ENCODING), "PR_ATTACH_ENCODING",
    PROP_ID( PR_ATTACH_EXTENSION),    "PR_ATTACH_EXTENSION",
    PROP_ID( PR_ATTACH_FILENAME), "PR_ATTACH_FILENAME",
    PROP_ID( PR_ATTACH_METHOD),   "PR_ATTACH_METHOD",
    PROP_ID( PR_ATTACH_LONG_FILENAME),    "PR_ATTACH_LONG_FILENAME",
    PROP_ID( PR_ATTACH_PATHNAME), "PR_ATTACH_PATHNAME",
    PROP_ID( PR_ATTACH_RENDERING),    "PR_ATTACH_RENDERING",
    PROP_ID( PR_ATTACH_TAG),  "PR_ATTACH_TAG",
    PROP_ID( PR_RENDERING_POSITION),  "PR_RENDERING_POSITION",
    PROP_ID( PR_ATTACH_TRANSPORT_NAME),   "PR_ATTACH_TRANSPORT_NAME",
    PROP_ID( PR_DISPLAY_TYPE),    "PR_DISPLAY_TYPE",
    PROP_ID( PR_TEMPLATEID),  "PR_TEMPLATEID",
//    PROP_ID( PR_CAPABILITIES_TABLE),  "PR_CAPABILITIES_TABLE",
    PROP_ID( PR_PRIMARY_CAPABILITY),  "PR_PRIMARY_CAPABILITY",
    PROP_ID( PR_ACCOUNT), "PR_ACCOUNT",
    PROP_ID( PR_ALTERNATE_RECIPIENT), "PR_ALTERNATE_RECIPIENT",
    PROP_ID( PR_CALLBACK_TELEPHONE_NUMBER),   "PR_CALLBACK_TELEPHONE_NUMBER",
    PROP_ID( PR_CONVERSION_PROHIBITED),   "PR_CONVERSION_PROHIBITED",
    PROP_ID( PR_DISCLOSE_RECIPIENTS), "PR_DISCLOSE_RECIPIENTS",
    PROP_ID( PR_GENERATION),  "PR_GENERATION",
    PROP_ID( PR_GIVEN_NAME),  "PR_GIVEN_NAME",
    PROP_ID( PR_GOVERNMENT_ID_NUMBER),    "PR_GOVERNMENT_ID_NUMBER",
    PROP_ID( PR_OFFICE_TELEPHONE_NUMBER), "PR_OFFICE_TELEPHONE_NUMBER",
    PROP_ID( PR_HOME_TELEPHONE_NUMBER),   "PR_HOME_TELEPHONE_NUMBER",
    PROP_ID( PR_INITIALS),    "PR_INITIALS",
    PROP_ID( PR_KEYWORD), "PR_KEYWORD",
    PROP_ID( PR_LANGUAGE),    "PR_LANGUAGE",
    PROP_ID( PR_LOCATION),    "PR_LOCATION",
    PROP_ID( PR_MAIL_PERMISSION), "PR_MAIL_PERMISSION",
    PROP_ID( PR_MHS_COMMON_NAME), "PR_MHS_COMMON_NAME",
    PROP_ID( PR_ORGANIZATIONAL_ID_NUMBER),    "PR_ORGANIZATIONAL_ID_NUMBER",
    PROP_ID( PR_SURNAME), "PR_SURNAME",
    PROP_ID( PR_ORIGINAL_ENTRYID),    "PR_ORIGINAL_ENTRYID",
    PROP_ID( PR_ORIGINAL_DISPLAY_NAME),   "PR_ORIGINAL_DISPLAY_NAME",
    PROP_ID( PR_ORIGINAL_SEARCH_KEY), "PR_ORIGINAL_SEARCH_KEY",
    PROP_ID( PR_POSTAL_ADDRESS),  "PR_POSTAL_ADDRESS",
    PROP_ID( PR_COMPANY_NAME),    "PR_COMPANY_NAME",
    PROP_ID( PR_TITLE),   "PR_TITLE",
    PROP_ID( PR_DEPARTMENT_NAME), "PR_DEPARTMENT_NAME",
    PROP_ID( PR_OFFICE_LOCATION), "PR_OFFICE_LOCATION",
    PROP_ID( PR_PRIMARY_TELEPHONE_NUMBER),    "PR_PRIMARY_TELEPHONE_NUMBER",
    PROP_ID( PR_OFFICE2_TELEPHONE_NUMBER),    "PR_OFFICE2_TELEPHONE_NUMBER",
    PROP_ID( PR_CELLULAR_TELEPHONE_NUMBER),   "PR_CELLULAR_TELEPHONE_NUMBER",
    PROP_ID( PR_RADIO_TELEPHONE_NUMBER),  "PR_RADIO_TELEPHONE_NUMBER",
    PROP_ID( PR_CAR_TELEPHONE_NUMBER),    "PR_CAR_TELEPHONE_NUMBER",
    PROP_ID( PR_OTHER_TELEPHONE_NUMBER),  "PR_OTHER_TELEPHONE_NUMBER",
    PROP_ID( PR_TRANSMITABLE_DISPLAY_NAME),   "PR_TRANSMITABLE_DISPLAY_NAME",
    PROP_ID( PR_STORE_PROVIDERS), "PR_STORE_PROVIDERS",
    PROP_ID( PR_AB_PROVIDERS),    "PR_AB_PROVIDERS",
    PROP_ID( PR_TRANSPORT_PROVIDERS), "PR_TRANSPORT_PROVIDERS",
    PROP_ID( PR_DEFAULT_PROFILE), "PR_DEFAULT_PROFILE",
    PROP_ID( PR_AB_SEARCH_PATH),  "PR_AB_SEARCH_PATH",
    PROP_ID( PR_AB_DEFAULT_DIR),  "PR_AB_DEFAULT_DIR",
    PROP_ID( PR_AB_DEFAULT_PAB),  "PR_AB_DEFAULT_PAB",
    PROP_ID( PR_FILTERING_HOOKS), "PR_FILTERING_HOOKS",
    PROP_ID( PR_SERVICE_NAME),    "PR_SERVICE_NAME",
    PROP_ID( PR_SERVICE_DLL_NAME),    "PR_SERVICE_DLL_NAME",
    PROP_ID( PR_SERVICE_ENTRY_NAME),  "PR_SERVICE_ENTRY_NAME",
    PROP_ID( PR_SERVICE_UID), "PR_SERVICE_UID",
    PROP_ID( PR_SERVICE_EXTRA_UIDS),  "PR_SERVICE_EXTRA_UIDS",
    PROP_ID( PR_SERVICES),    "PR_SERVICES",
    PROP_ID( PR_SERVICE_SUPPORT_FILES),   "PR_SERVICE_SUPPORT_FILES",
    PROP_ID( PR_SERVICE_DELETE_FILES),    "PR_SERVICE_DELETE_FILES",
    PROP_ID( PR_IDENTITY_DISPLAY),    "PR_IDENTITY_DISPLAY",
    PROP_ID( PR_IDENTITY_ENTRYID),    "PR_IDENTITY_ENTRYID",
    PROP_ID( PR_RESOURCE_METHODS),    "PR_RESOURCE_METHODS",
    PROP_ID( PR_RESOURCE_TYPE),   "PR_RESOURCE_TYPE",
    PROP_ID( PR_STATUS_CODE), "PR_STATUS_CODE",
    PROP_ID( PR_IDENTITY_SEARCH_KEY), "PR_IDENTITY_SEARCH_KEY",
    PROP_ID( PR_OWN_STORE_ENTRYID),   "PR_OWN_STORE_ENTRYID",
    PROP_ID( PR_RESOURCE_PATH),   "PR_RESOURCE_PATH",
    PROP_ID( PR_STATUS_STRING),   "PR_STATUS_STRING",
    PROP_ID( PR_X400_DEFERRED_DELIVERY_CANCEL),   "PR_X400_DEFERRED_DELIVERY_CANCEL",
    PROP_ID( PR_HEADER_FOLDER_ENTRYID),   "PR_HEADER_FOLDER_ENTRYID",
    PROP_ID( PR_REMOTE_PROGRESS), "PR_REMOTE_PROGRESS",
    PROP_ID( PR_REMOTE_PROGRESS_TEXT),    "PR_REMOTE_PROGRESS_TEXT",
    PROP_ID( PR_CONTROL_FLAGS),   "PR_CONTROL_FLAGS",
    PROP_ID( PR_CONTROL_STRUCTURE),   "PR_CONTROL_STRUCTURE",
    PROP_ID( PR_CONTROL_TYPE),    "PR_CONTROL_TYPE",
    PROP_ID( PR_DELTAX),  "PR_DELTAX",
    PROP_ID( PR_DELTAY),  "PR_DELTAY",
    PROP_ID( PR_XPOS),    "PR_XPOS",
    PROP_ID( PR_YPOS),    "PR_YPOS",
    PROP_ID( PR_CONTROL_ID),  "PR_CONTROL_ID",
    PROP_ID( PR_INITIAL_DETAILS_PANE),    "PR_INITIAL_DETAILS_PANE"
};

static IDList PropTypes[] = 
{
    PT_UNSPECIFIED, "PT_UNSPECIFIED",
    PT_NULL,    "PT_NULL",
    PT_I2,  "PT_I2",
    PT_LONG,    "PT_LONG",
    PT_R4,  "PT_R4",
    PT_DOUBLE,  "PT_DOUBLE",
    PT_CURRENCY,    "PT_CURRENCY",
    PT_APPTIME, "PT_APPTIME",
    PT_ERROR,   "PT_ERROR",
    PT_BOOLEAN, "PT_BOOLEAN",
    PT_OBJECT,  "PT_OBJECT",
    PT_I8,  "PT_I8",
    PT_SYSTIME, "PT_SYSTIME",
    PT_STRING8, "PT_STRING8",
    PT_UNICODE, "PT_UNICODE",
    PT_CLSID,   "PT_CLSID",
    PT_BINARY,  "PT_BINARY",
    PT_MV_I2,   "PT_MV_I2",
    PT_MV_LONG, "PT_MV_LONG",
    PT_MV_R4,   "PT_MV_R4",
    PT_MV_DOUBLE,   "PT_MV_DOUBLE",
    PT_MV_CURRENCY, "PT_MV_CURRENCY",
    PT_MV_APPTIME,  "PT_MV_APPTIME",
    PT_MV_SYSTIME,  "PT_MV_SYSTIME",
    PT_MV_STRING8,  "PT_MV_STRING8",
    PT_MV_BINARY,   "PT_MV_BINARY",
    PT_MV_UNICODE,  "PT_MV_UNICODE",
    PT_MV_CLSID,    "PT_MV_CLSID",
    PT_MV_I8,   "PT_MV_I8",
    PT_MV_TSTRING,  "PT_MV_TSTRING"
};

// -----------------------------------------------------------------------------

#endif  //_PROPDEF_H_