/* --------------------------------------------------------------------------

The header file for defining constants and macros used throughout the
files

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */

#ifndef _ACLCOMMON_H_
#define _ACLCOMMON_H_

#pragma warning(disable:4200)

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

EXTERN_C const IID IID_IExchangeModifyTable;
EXTERN_C const IID IID_IMAPIFolder;

#define EDK_USES_IID

#include <edkguid.h>
#include <mapiguid.h>
#include <edkcode.h>

#define EDK_E_ACCESSDENIED \
    MAKE_SCODE(SEVERITY_ERROR, FACILITY_EDK, EC_EDK_E_ACCESSDENIED)

#define USES_IID_IMAPIFolder
#define USES_IID_IMAPIProp
#define USES_IID_IAddrBook
#define USES_IID_IMAPISession
#define USES_IID_IMAPITable

#define	CbNewROWLIST(_centries)	(offsetof(ROWLIST,aEntries) + \
								(_centries)*sizeof(ROWENTRY))

#define ULRELEASE(x) \
{                    \
	UlRelease((x));  \
	(x) = NULL;      \
}
 
#define MAPIFREEBUFFER(x) \
{                         \
    MAPIFreeBuffer((x));  \
	(x) = NULL;           \
}

#ifdef _DEBUG
#define DEBUGPRINT(x)                   \
{                                       \
            bstr_t b = x;               \
           ATLTRACE( "%s\n", (char*)b); \
}
#endif

enum ACL_MEMBERS
{
	I_MEMBER_ENTRYID = 0,	 // index for entry id   
    I_MEMBER_RIGHTS,		 // index for rights
    I_MEMBER_ID,			 // index for member id used for default and anonymous entries	
    C_ACLPROPS               // number of ACL properties in an entry
};
const DWORD	ID_DEFAULT =		0x00000000;				// ID used for the default entry
const DWORD ID_ANONYMOUS =		0xFFFFFFFF;				// ID used for the anonymous entry
const DWORD ID_NEWACE =			0xFFFFFFFE;				// ID used for a new entry

const int EDK_MAX_QUERY_ROWS =	1024;					// max number of entries in an ACL table
#define ID_ACL_DEFAULT			"ID_ACL_DEFAULT"		// ID used as a key to the ACE Map,
														// since there is no entry id for the Default
#define ID_ACL_ANONYMOUS		"ID_ACL_ANONYMOUS"		// ID used as a key to the ACE Map
														// since there is no entry id for the Anonymous

enum ADDRBOOK_DISPLAYNAME
{
    I_PR_DISPLAYNAME = 0,    // index for display name
    C_DISPLAYNAMEPROPS       // number of properties retrieved from address book for display name
};

#endif // _ACLCOMMON_H_
