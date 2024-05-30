// --convcls.h--------------------------------------------------------------
//
// IPM to 822 conversion class header file.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#ifndef _CONVCLS_H
#define _CONVCLS_H

// $--MESSAGE_TYPE-----------------------------------------------
//
// Report type enumeration
//
// -------------------------------------------------------------
enum MESSAGE_TYPE
{
    mtNone,        // no type
    mtIPM,         // IPM message
    mtNDR,         // non-delivery report
    mtDR,          // delivery report
    mtNRN,         // non-read notification
    mtRN           // read notification        
};

// $--CIPMConvert------------------------------------------------------------
//
// IPM message to 822-style stream converter class
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
        IN BOOL bTNEFEnc,           // TNEF encode attachments flag
        IN LPADRBOOK lpAddrBook,    // address book pointer
        IN LPMESSAGE lpMessage,     // message to convert
        IN LPSTREAM lpStream);      // stream to write output to

    // IPM message or report to 822-style converter
    HRESULT HrConvert();        

private:

    // methods

    // TNEF encodes everything below the envelope.  Only
    // converts the envelope to the "822-style" header.
    HRESULT HrContentToTnef();

    // converts an ENVELOPE.IPM message
    HRESULT HrIPMTo822Format();    

    // converts a REPORT.IPM message
    HRESULT HrReportTo822Format();  
            
    // Converts the message's or notification's envelope
    // IPM.NOTE or REPORT.IPM.IPN[N]RN
    HRESULT HrConvertEnvelope();    

    // Retrieves and stores envelope's properties.
    HRESULT HrEnvelopeGetProps();   

    // Converts the message's  content 
    HRESULT HrConvertContent();      

    // Converts the message's attachments
    HRESULT HrConvertAttachments();  

    // Converts REPORT.[N]DR delivery/non-delivery report envelope
    HRESULT HrConvertReport();       

    // Opens the envelope's content.
    HRESULT HrOpenContent();

    // Retrieves and stores properties requested
    HRESULT HrRetrieveProps(          
        IN LPMAPIPROP lpObj,            // MAPI object to retrieve properties from
        IN LPSPropTagArray lpPropTags,  // pointer to property tags
        OUT LPSPropValue * lppPropVals);// pointer to property value array

    // Determines and sets the report type
    HRESULT HrSetMsgType(            
        IN LPCWSTR lpwszMessageClass);  // message class

    // Handles NDR non-recipient table
    HRESULT HrConvertNonRecipients(); 

    // Handle DR recipient table       
    HRESULT HrConvertRecipients(); 

    // Handle RN & NRN report content
    HRESULT HrConvertNotifyContent();

    // Checks to see if conversion class has been initialized
    BOOL fCheckInit();               // RETURNS: BOOL

    // "Resets" the class after a conversion is completed.
    VOID Reset();                   // RETURNS: VOID

    // data members
    // Currently, converter only supports one conversion per thread.
    LPCWSTR     m_lpwszMsgClass;      // mesage class
    LPMESSAGE   m_lpEnvelope;         // message's envelope
    LPMESSAGE   m_lpContent;          // message's content (the original message)
    LPSTREAM    m_lpStream;           // stream currently writing to
    BOOL        m_fTNEFEncode;        // TNEF encoding flag
    LPADRBOOK   m_lpAB;               // address book pointer
    LPATTACH    m_lpAttach;           // envelope attachment pointer

    LPSPropValue    m_lpEnvProps;     // message envelope properties pointer
    LPSPropValue    m_lpCntProps;     // message content properties pointer

    MESSAGE_TYPE     m_MsgType;       // message type
};

#endif
