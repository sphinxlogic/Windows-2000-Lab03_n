// --gwobjcls.h---------------------------------------------------------------
//
// Class header file for the GWCLEAN class object.
//
// Copyright (C) Microsoft Corporation 1986-1996,  All Rights Reserved

#ifndef _GWOBJCLS_H
#define _GWOBJCLS_H

// $--CGWClean---------------------------------------------------------------
//
// GWCLEAN class defintion.  Main purpose is to avoid lots of global variables
// and to make memory de-allocation at program termination simple.
//
// ---------------------------------------------------------------------------

class CGWClean
{
public:
    // class methods
    CGWClean();                     // constructor
    ~CGWClean();                    // destructor

    // initializes class members
    HRESULT CGWClean::HrInitialize(
             IN LPTSTR lpProfileName,       // gateway profile name
             IN LPTSTR lpPSTName,           // New PST name
             IN LPTSTR lpFolderName,        // gateway folder name
             IN LPFILETIME lpBeforeTime);   // date/time before which to move messages

    HRESULT HrMoveMsgs();               // Moves messages before date/time from GW out folder to new PST out folder

private:    
    // Additional, helper functions
    HRESULT HrCreatePSTFolder();        // Creates new folder in new PST
    HRESULT HrCopyGWMessageProps(IN LPENTRYLIST, IN LPENTRYLIST);   // Copies gateway message properties not copied by CopyMessages
    HRESULT HrCopyGWAttachProps(IN LPMESSAGE, IN LPMESSAGE);    // Copies gateway attachment properties not copied by CopyMessages
    HRESULT HrCreateNewProps(IN LPMESSAGE, IN LPMESSAGE);   // created uncopied properties on new message

    // class members
    LPTSTR     m_lpPSTName;            // PST to copy to
    LPTSTR     m_lpProfileName;        // gateway profile to copy from
    LPFILETIME  m_lpBeforeDateTime;     // Remove messages before date and time
    LPTSTR     m_lpFolderName;         // Gateway folder to move messages from

    // MAPI session variables
    LPMAPISESSION m_lpSessGW;           // Session for gateway profile
    LPMAPISESSION m_lpSessNew;          // Session for temporary profile
    LPMDB         m_lpMDBGateway;       // Gateway message store pointer
    LPMDB         m_lpMDBNew;           // PST message store pointer
    LPMAPIFOLDER  m_lpFolderFrom;       // Gateway folder
    LPMAPIFOLDER  m_lpFolderTo;         // PST folder

    // variables for temporary profile created by CreateNewPST()
    LPTSTR   m_lpTempProfilePW;         // temporary profile's password
    LPTSTR   m_lpTempProfName;          // temporary profile's name

    // state variables
    BOOL    m_fNewPST;                  // TRUE if PST is created
    BOOL    m_fNoMessages;              // TRUE if there were no messages to move

};

#endif
