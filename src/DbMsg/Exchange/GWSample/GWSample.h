// --gwsample.h-----------------------------------------------------------------
//
// Sample gateway application.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _GWSAMPLE_H
#define _GWSAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SYSTEM_ADMINISTRATOR    TEXT("System Administrator")
#define SYSTEM                  TEXT("SYSTEM")

extern LPTSTR  lpszSysAdminName;
extern LPTSTR  lpszSysAdminAddr;

#define IDISPNAME  0
#define IADDRTYPE  1
#define IEMAILADDR 2
#define ISEARCHKEY 3
#define IENTRYID   4
#define IMAPIRECIP 5
#define IRESP      6
#define IRECIPNUM  7
#define IORIGDISP  8
#define IORIGENTRY 9
#define IPROXYADDR 10

#define IRECIPSTAT 10

#define MIN_CRECIPPROPS 11

#define PR_RECIPSTAT PROP_TAG(PT_LONG, 0x65FF)


//$--HrMapRecipProxyToAddr------------------------------------------------------
// Map recipient proxy addresses to addresses.
// -----------------------------------------------------------------------------
HRESULT HrMapRecipProxyToAddr(          // RETURNS: return code
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN BOOL fDefaultRespValue,          // default responsibility value
    IN BOOL fIgnoreRespValue,           // ignore  responsibility value
    IN LPABCONT lpGalABCont,            // pointer to GAL container
    IN LPTSTR lpszAddrType,             // pointer to address type
    IN LPADRLIST lpOriginalAdrList,     // pointer to unmodified address list
    IN LPADRLIST lpMappedAdrList,       // pointer to unmodified address list
    IN OUT LPADRLIST lpEnvelopeAdrList, // pointer to envelope address list
    IN OUT LPADRLIST lpEnvelopeNDRAdrList,// pointer to envelope NDR address list
    IN OUT LPMESSAGE lpMessage,         // pointer to message
    OUT LPADRLIST *lppAdrList,          // pointer to address list
    OUT LPADRLIST *lppNDRAdrList);      // pointer to NDR address list

//$--HrCreateEmailAddress-------------------------------------------------------
// Create email address.
// -----------------------------------------------------------------------------
HRESULT HrCreateEmailAddress(               // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,                // pointer to address book
    IN LPVOID     lpObject,                 // pointer to object
    IN LPTSTR     lpszDisplayName,          // pointer to display name
    IN LPTSTR     lpszAddressType,          // pointer to address type
    IN LPTSTR     lpszAddress,              // pointer to address
    IN ULONG      cbeid,                    // count of bytes in entry ID
    IN LPENTRYID  lpeid,                    // pointer to entry ID
    OUT LPTSTR    *lppszEmailDisplayName,   // email display name
    OUT LPTSTR    *lppszEmailAddressType,   // email address type
    OUT LPTSTR    *lppszEmailAddress,       // email address
    OUT LPTSTR    *lppszEmailSearchKey,     // email search key
    OUT ULONG     *lpcbEmailEid,            // count of bytes in email entry ID
    OUT LPENTRYID *lppEmailEid);            // pointer to email entry ID

//$--HrDeleteAddressListProperty------------------------------------------------
// Delete a property from an address list given its property tag.
// -----------------------------------------------------------------------------
HRESULT HrDeleteAddressListProperty(    // RETURNS: return code
    IN ULONG ulPropTag,                 // property tag
    IN OUT LPADRLIST lpAdrList);        // pointer to address list

//$--HrMapRecipAddrToProxy------------------------------------------------------
// Map recipient addresses to proxy addresses.
// -----------------------------------------------------------------------------
HRESULT HrMapRecipAddrToProxy(          // RETURNS: return code
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN BOOL fDefaultRespValue,          // default responsibility value
    IN BOOL fIgnoreRespValue,           // ignore  responsibility value
    IN LPTSTR lpszAddrType,             // pointer to address type
    IN LPADRLIST lpOriginalEnvelopeAdrList,// pointer to unmodified address list
    IN LPADRLIST lpOriginalAdrList,     // pointer to unmodified address list
    IN LPADRLIST lpMappedAdrList,       // pointer to unmodified address list
    IN OUT LPADRLIST lpEnvelopeAdrList, // pointer to envelope address list
    IN OUT LPADRLIST lpEnvelopeNDRAdrList,// pointer to envelope NDR address list
    IN OUT LPMESSAGE lpMessage,         // pointer to message
    OUT LPADRLIST *lppAdrList,          // pointer to address list
    OUT LPADRLIST *lppNDRAdrList);      // pointer to NDR address list

//$--HrDeleteAddressProps--------------------------------------------------------
// Delete address properties from the message.
// -----------------------------------------------------------------------------
HRESULT HrDeleteAddressProps(           // RETURNS: return code
    IN LPMESSAGE  lpMessage,            // pointer to message
    IN ULONG ulDisplayName,             // display name property tag
    IN ULONG ulAddressType,             // address type property tag
    IN ULONG ulAddress,                 // address property tag
    IN ULONG ulSearchKey,               // search key property tag
    IN ULONG ulEntryId);                // entry ID property tag

//$--HrCreateProxyAddress-------------------------------------------------------
// Create proxy address.
// -----------------------------------------------------------------------------
HRESULT HrCreateProxyAddress(               // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,                // pointer to address book
    IN LPVOID     lpObject,                 // pointer to object
    IN BOOL       fMapiRecip,               // MAPI recipient
    IN LPTSTR     lpszDisplayName,          // pointer to display name
    IN LPTSTR     lpszAddressType,          // pointer to address type
    IN LPTSTR     lpszAddress,              // pointer to address
    OUT LPTSTR    *lppszProxyDisplayName,   // proxy display name
    OUT LPTSTR    *lppszProxyAddressType,   // proxy address type
    OUT LPTSTR    *lppszProxyAddress,       // proxy address
    OUT LPTSTR    *lppszProxySearchKey,     // proxy search key
    OUT ULONG     *lpcbProxyEid,            // count of bytes in proxy entry ID
    OUT LPENTRYID *lppProxyEid);            // pointer to proxy entry ID

//$--HrSetUlongPropertyValue----------------------------------------------------
// Set a ULONG property value.
// -----------------------------------------------------------------------------
HRESULT HrSetUlongPropertyValue(        // RETURNS: return code
    IN BOOL  fOverwrite,                // overwrite value if it exists
    IN ULONG ulPropTag,                 // property tag
    IN ULONG ulValue,                   // property value
    IN ULONG cValues,                   // count of property values
    IN LPSPropValue lpProps,            // pointer to property values
    OUT ULONG* lpcValues,               // new count of property values
    OUT LPSPropValue* lppProps);        // new pointer to property values

//$--HrNonDeliverRecipient------------------------------------------------------
// Non-deliver a recipient.
// -----------------------------------------------------------------------------
HRESULT HrNonDeliverRecipient(          // RETURNS: return code
    IN ULONG ulReasonCode,              // NDR reason code
    IN ULONG ulDiagnosticCode,          // NDR diagnostic code
    IN LPFILETIME lpftReportTime,       // report time
    IN ULONG ulRecipientNumber,         // recipient number
    IN ULONG ulOffset,                  // offset in NDR address list
    IN ULONG cValues,                   // count of property values
    IN LPSPropValue lpProps,            // pointer to property values
    IN OUT LPADRLIST lpAdrList);        // pointer to NDR address list

//$--HrExpandMessageAddressList-------------------------------------------------
// Expand a list of addresses on the message.
// -----------------------------------------------------------------------------
HRESULT HrExpandMessageAddressList(     // RETURNS: return code
    IN LPMESSAGE  lpMessage,            // pointer to message
    OUT ULONG*    lpcMesgAddr,          // count of message addresses
    OUT ULONG*    lpcReplyAddr,         // count of reply recipient addresses
    OUT ULONG*    lpcRecipAddr,         // count of recipient addresses
    OUT LPADRLIST *lppRecipList,        // pointer to recipient address list
    OUT LPADRLIST *lppAdrList);         // pointer to address list

//$--HrMapAddrToProxy-----------------------------------------------------------
// Map all email addresses to proxy addresses in a given address list.
// -----------------------------------------------------------------------------
HRESULT HrMapAddrToProxy(               // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPTSTR       lpszAddrType,      // pointer to the address type
    IN OUT LPADRLIST lpAdrList);        // pointer to address list

//$--HrCollapseMessageAddressList-----------------------------------------------
// Collapse a list of addresses on the message.
// -----------------------------------------------------------------------------
HRESULT HrCollapseMessageAddressList(   // RETURNS: return code
    IN LPMESSAGE     lpMessage,         // pointer to message
    IN ULONG         cMesgAddr,         // count of message addresses
    IN ULONG         cReplyAddr,        // count of reply recipient addresses
    IN ULONG         cRecipAddr,        // count of recipient addresses
    IN LPADRLIST     lpAdrList,         // message address list
    OUT ULONG        *lpcValues,        // count of message address properties
    OUT LPSPropValue *lppProps,         // message address properties
    OUT LPADRLIST    *lppAdrList);      // recipient address list

//$--HrMapProxyToAddr-----------------------------------------------------------
// Map all proxy addresses to email addresses in a given address list. Always
// call HrMapAddrToProxy() before calling this function.
// -----------------------------------------------------------------------------
HRESULT HrMapProxyToAddr(               // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPABCONT     lpGalABCont,       // pointer to GAL container
    IN OUT LPADRLIST lpAdrList);        // pointer to address list

//$--HrMapGatewayAddrToProxy----------------------------------------------------
// Map all gateway specific email addresses to proxy addresses
// in a given address list.
// -----------------------------------------------------------------------------
HRESULT HrMapGatewayAddrToProxy(        // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPTSTR       lpszAddrType,      // pointer to the address type
    IN OUT LPADRLIST lpAdrList);        // pointer to address list

//$--HrMapGatewayProxyToAddr----------------------------------------------------
// Map all gateway specific email addresses to proxy addresses
// in a given address list.
// -----------------------------------------------------------------------------
HRESULT HrMapGatewayProxyToAddr(        // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPTSTR       lpszAddrType,      // pointer to the address type
    IN OUT LPADRLIST lpAdrList);        // pointer to address list

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
