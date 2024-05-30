// --convcls.h--------------------------------------------------------------
//
// IPM to 822-style header conversion class header file.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#ifndef _CONVCLS_H
#define _CONVCLS_H

// indices into the tag data member array
const UINT  iMailFrom   =   0;      // "Mail From" data
const UINT  iClass      =   1;      // "X-Message-Class" data
const UINT  iDate       =   2;      // "Date" data
const UINT  iXID        =   3;      // "X-Message-ID" data
const UINT  iSubjectXID =   4;      // "X-Message-Subject-ID" data
const UINT  iFrom       =   5;      // "From" data
const UINT  iSubject    =   6;      // "Subject" data
const UINT  iPriority   =   7;      // "Priority" data
const UINT  iImportance =   8;      // "Importance" data

// read/not read notification data member indices
const UINT  iReadBy     =   9;      // read/not read by address data
const UINT  iNotifyTime =   10;     // read/not read notification time
const UINT  iDiscardCode=   11;     // not read discard code data
const UINT  iNonRcptCode=   12;     // not read non-receipt code data

const UINT  nDataEntries    =   13; // number of entries in data member array

//$--MSG_TYPE-----------------------------------------------
//
// Message type enumeration (based on message class)
//
// -------------------------------------------------------------
enum MSG_TYPE
{
    mtNone,        // no type
    mtIPM,         // interpersonal message
    mtNDR,         // non-delivery report
    mtDR,          // delivery report
    mtNRN,         // non-read notification
    mtRN           // read notification        
};

//$--CIPMConvert------------------------------------------------------------
//
// 822-style header to IPM message stream converter class
//
// ---------------------------------------------------------------------------

class CIPMConvert
{
public:

    CIPMConvert();  // constructor
    ~CIPMConvert(); // destructor

    // Initializes conversion class instance
    HRESULT HrInitialize(           
        IN LPCWSTR lpwszMsgClass,   // message class
        IN BOOL fTNEFEncode,        // TNEF encoding flag
        IN LPCTSTR lpszAddrType,    // address type
        IN LPADRBOOK lpAddrBook,    // address book pointer
        IN LPMESSAGE lpMessage,     // message pointer
        IN LPSTREAM lpStream);      // stream pointer

    // 822-style header to IPM message or report converter
    HRESULT HrConvert();        

private:

    // methods

    // Set message type based on message class.
    HRESULT CIPMConvert::HrSetMessageType(
        IN LPTSTR lpszMessageClass);        // message class

    // Parses envelope and content header, saving data.
    HRESULT HrParseEnvelopeAndContent();

    // Parses IPM-specific tag and data lines
    HRESULT HrParseIPMSpecific();

    // Parses and creates binary file attachments
    HRESULT HrParseAttachments();

    // Parses [non]delivery report-specific tag and data lines
    HRESULT HrParseReportSpecific(
                ULONG * pnRecipients);  // # of [non]delivery recipients

    // sets delivery and non-delivery report properties
    HRESULT HrSetReportProps();

    // Parses read/non-read notification-specific tag and data lines
    HRESULT HrParseNotificationSpecific();

    // sets [non]read notification content properties.
    HRESULT HrSetNotifyCntProps();

    // Parses recipient tag and data lines & saves addresses
    HRESULT HrParseRecipients(
        IN LPCTSTR lpszTag,     // expected tag
        IN ULONG ulType,        // MAPI recipient type
        IN OUT LPADRLIST * lpAdrList, // target address list
        OUT ULONG * pnRecips);  // # recipients found of type

    // Creates content 
    HRESULT HrCreateContent();

    // Sets envelope properties
    HRESULT HrSetEnvelopeProps();

    // Sets content properties
    HRESULT HrSetContentProps();

    // Parses and creates next attachment.
    HRESULT HrCreateNextAttachment();

    // Checks to see if conversion class has been initialized
    inline BOOL fCheckInit()        // RETURNS: BOOL
    {
        return(m_lpwszMsgClass && m_lpEnvelope && m_lpStream && m_lpAB && m_lpszAddrType);
    };

    // "Resets" the class after a conversion is completed.
    VOID Reset();                   // RETURNS: VOID

    // Frees the data string member array memory
    VOID HrFreeData();              // RETURNS: VOID

    // Parses and stores the external trace information.
    HRESULT CIPMConvert::HrParseExternalTraceData(
        OUT ULONG * pnEntries);         // number of trace entries found

    // Parses and stores the internal trace information.
    HRESULT CIPMConvert::HrParseInternalTraceData(
        OUT ULONG * pnEntries);         // number of trace entries found

    // Sets the envelope's PR_TRANSPORT_MESSAGE_HEADER property
    HRESULT HrSetTransHdr();

    // Decodes the TNEFed data into the envelope's content.
    HRESULT HrTnefToContent();

    // data members
    LPCWSTR     m_lpwszMsgClass;      // mesage class
    LPMESSAGE   m_lpEnvelope;         // message's envelope
    LPMESSAGE   m_lpContent;          // message's content (the original message)
    LPSTREAM    m_lpStream;           // stream currently writing to
    LPATTACH    m_lpAttach;           // envelope attachment pointer
    BOOL        m_fTNEFEncode;        // TNEF encoding flag
    LPCTSTR     m_lpszAddrType;       // address type
    LPADRBOOK   m_lpAB;               // address book    

    MSG_TYPE    m_MsgType;            // message type (based on message class)

    // Array of non-recipient tag data for the envelope and its content.
    LPTSTR      m_rgszData[nDataEntries];   // array of data strings for envelope & content

    // Recipient address list for IPM & [N]RN envelopes
    LPADRLIST   m_lpRcptToList;     // "RCPT TO" addresses

    // Recipient address list for IPM & [N]RN contents
    LPADRLIST   m_lpContentRecips;         // "To", "CC" and "BCC" addresses

    // [non]recipient list for [non]delivery reports
    LPADRLIST   m_lpReportToList;   // [N]DR recipient and non-recipient list

    // Trace entry list    
    LPTRACEINFO m_lpTraceInfo;      // Trace entry list

    // Internal Trace entry list    
    PINTTRACEINFO m_lpIntTraceInfo; // Trace entry list

	// Stream marker for end of headers
	ULARGE_INTEGER m_sOffsetHeaders;

};

#endif
