//+--------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1994 - 1999.
//
//  File:       objsel.h
//
//  Contents:   Object Picker Dialog public header
//
//---------------------------------------------------------------------------

#ifndef __OBJSEL_H_
#define __OBJSEL_H_

#if _MSC_VER > 1000
#pragma once
#endif

extern "C" const GUID __declspec(selectany) CLSID_DsObjectPicker =
    {0x17d6ccd8,0x3b7b,0x11d2,{0xb9, 0xe0, 0x00, 0xc0, 0x4f, 0xd8, 0xdb, 0xf7}};

extern "C" const GUID __declspec(selectany) IID_IDsObjectPicker =
    {0x0c87e64e,0x3b7a,0x11d2,{0xb9,0xe0,0x00,0xc0,0x4f,0xd8,0xdb,0xf7}};

/*
CLIPBOARD FORMATS
=================

CFSTR_DSOP_DS_SELECTION_LIST
    Returns an HGLOBAL for global memory containing a DS_SELECTION_LIST
    variable length structure.
*/

#define CFSTR_DSOP_DS_SELECTION_LIST    TEXT("CFSTR_DSOP_DS_SELECTION_LIST")


/*
SCOPE TYPES
===========

A scope is an entry in the "Look In" dropdown list of the Object Picker
dialog.

When initializing the DS Object Picker, DSOP_SCOPE_TYPEs are used with
DSOP_SCOPE_INIT_INFO.flType member to specify which types of scopes the
DS Object Picker should put in the "Look In" list.

DSOP_SCOPE_TYPE_TARGET_COMPUTER
    Computer specified by DSOP_INIT_INFO.pwzTargetComputer, NULL is
    local computer.

DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN
    Uplevel domain to which target computer is joined.

DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN
    Downlevel domain to which target computer is joined.

DSOP_SCOPE_TYPE_ENTERPRISE_DOMAIN
    All domains in the enterprise to which the target computer belongs
    other than the JOINED_DOMAIN or USER_SPECIFIED_*_SCOPEs.

DSOP_SCOPE_TYPE_GLOBAL_CATALOG
    The Entire Directory scope.

DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN
    All uplevel domains external to the enterprise but trusted by the
    domain to which the target computer is joined.

DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN
    All downlevel domains external to the enterprise but trusted by the
    domain to which the target computer is joined.

DSOP_SCOPE_TYPE_WORKGROUP
    The workgroup of which TARGET_COMPUTER is a member.  Applies only if the
    TARGET_COMPUTER is not joined to a domain.

DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE
DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE
    Any uplevel or downlevel scope generated by processing user input.  If
    neither of these types is specified, user entries that do not refer to
    one of the scopes in the "Look In" control will be rejected.

*/

#define DSOP_SCOPE_TYPE_TARGET_COMPUTER                 0x00000001
#define DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN           0x00000002
#define DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN         0x00000004
#define DSOP_SCOPE_TYPE_ENTERPRISE_DOMAIN               0x00000008
#define DSOP_SCOPE_TYPE_GLOBAL_CATALOG                  0x00000010
#define DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN         0x00000020
#define DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN       0x00000040
#define DSOP_SCOPE_TYPE_WORKGROUP                       0x00000080
#define DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE      0x00000100
#define DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE    0x00000200


/*
DSOP_SCOPE_INIT_INFO flags
==========================

The flScope member can contain zero or more of the following flags:

DSOP_SCOPE_FLAG_STARTING_SCOPE
    The scope should be the first one selected in the Look In control after
    dialog initialization.  If more than one scope specifies this flag,
    the one which is chosen to be the starting scope is implementation
    dependant.

DSOP_SCOPE_FLAG_WANT_PROVIDER_WINNT
    ADs paths for objects selected from this scope should be converted to use
    the WinNT provider.

DSOP_SCOPE_FLAG_WANT_PROVIDER_LDAP
    ADs paths for objects selected from this scope should be converted to use
    the LDAP provider.

DSOP_SCOPE_FLAG_WANT_PROVIDER_GC
    ADs paths for objects selected from this scope should be converted to use
    the GC provider.

DSOP_SCOPE_FLAG_WANT_SID_PATH
    ADs paths for objects selected from this scope having an objectSid
    attribute should be converted to the form LDAP://<SID=x>, where x
    represents the hexidecimal digits of the objectSid attribute value.

DSOP_SCOPE_FLAG_WANT_DOWNLEVEL_BUILTIN_PATH
    ADs paths for downlevel well-known SID objects (for example,
    DSOP_DOWNLEVEL_FILTER_INTERACTIVE) are an empty string unless this flag is
    specified.  If it is, the paths will be of the form
    WinNT://NT AUTHORITY/Interactive or WinNT://Creator owner.
*/

#define DSOP_SCOPE_FLAG_STARTING_SCOPE              0x00000001
#define DSOP_SCOPE_FLAG_WANT_PROVIDER_WINNT         0x00000002
#define DSOP_SCOPE_FLAG_WANT_PROVIDER_LDAP          0x00000004
#define DSOP_SCOPE_FLAG_WANT_PROVIDER_GC            0x00000008
#define DSOP_SCOPE_FLAG_WANT_SID_PATH               0x00000010
#define DSOP_SCOPE_FLAG_WANT_DOWNLEVEL_BUILTIN_PATH 0x00000020


/*
The flMixedModeOnly/flNativeModeOnly member of an uplevel scope can
contain one or more of the following flags (at least one must be specified):

DSOP_FILTER_INCLUDE_ADVANCED_VIEW
    Include objects which have the attribute showInAdvancedViewOnly set to
    true.

DSOP_FILTER_USERS
    Include user objects.

DSOP_FILTER_BUILTIN_GROUPS
    Include group objects with a groupType value having the flag
    GROUP_TYPE_BUILTIN_LOCAL_GROUP.

DSOP_FILTER_WELL_KNOWN_PRINCIPALS
    Include the contents of the WellKnown Security Principals container.

DSOP_FILTER_UNIVERSAL_GROUPS_DL
    Include distribution list universal groups.

DSOP_FILTER_UNIVERSAL_GROUPS_SE
    Include security enabled universal groups.

DSOP_FILTER_GLOBAL_GROUPS_DL
    Include distribution list global groups.

DSOP_FILTER_GLOBAL_GROUPS_SE
    Include security enabled global groups.

DSOP_FILTER_DOMAIN_LOCAL_GROUPS_DL
    Include distribution list domain global groups.

DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE
    Include security enabled domain local groups.

DSOP_FILTER_CONTACTS
    Include contact objects.

DSOP_FILTER_COMPUTERS
    Include computer objects.
*/

#define DSOP_FILTER_INCLUDE_ADVANCED_VIEW   0x00000001
#define DSOP_FILTER_USERS                   0x00000002
#define DSOP_FILTER_BUILTIN_GROUPS          0x00000004
#define DSOP_FILTER_WELL_KNOWN_PRINCIPALS   0x00000008
#define DSOP_FILTER_UNIVERSAL_GROUPS_DL     0x00000010
#define DSOP_FILTER_UNIVERSAL_GROUPS_SE     0x00000020
#define DSOP_FILTER_GLOBAL_GROUPS_DL        0x00000040
#define DSOP_FILTER_GLOBAL_GROUPS_SE        0x00000080
#define DSOP_FILTER_DOMAIN_LOCAL_GROUPS_DL  0x00000100
#define DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE  0x00000200
#define DSOP_FILTER_CONTACTS                0x00000400
#define DSOP_FILTER_COMPUTERS               0x00000800


/*
The flFilter member of a downlevel scope can contain one or more of the
following flags:

DSOP_DOWNLEVEL_FILTER_USERS
    Include user objects.

DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS
    Include all local groups.

DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS
    Include all global groups.

DSOP_DOWNLEVEL_FILTER_COMPUTERS
    Include computer objects

DSOP_DOWNLEVEL_FILTER_WORLD
    Include builtin security principal World (Everyone).

DSOP_DOWNLEVEL_FILTER_AUTHENTICATED_USER
    Include builtin security principal Authenticated User.

DSOP_DOWNLEVEL_FILTER_ANONYMOUS
    Include builtin security principal Anonymous.

DSOP_DOWNLEVEL_FILTER_BATCH
    Include builtin security principal Batch.

DSOP_DOWNLEVEL_FILTER_CREATOR_OWNER
    Include builtin security principal Creator Owner.

DSOP_DOWNLEVEL_FILTER_CREATOR_GROUP
    Include builtin security principal Creator Group.

DSOP_DOWNLEVEL_FILTER_DIALUP
    Include builtin security principal Dialup.

DSOP_DOWNLEVEL_FILTER_INTERACTIVE
    Include builtin security principal Interactive.

DSOP_DOWNLEVEL_FILTER_NETWORK
    Include builtin security principal Network.

DSOP_DOWNLEVEL_FILTER_SERVICE
    Include builtin security principal Service.

DSOP_DOWNLEVEL_FILTER_SYSTEM
    Include builtin security principal System.

DSOP_DOWNLEVEL_FILTER_EXCLUDE_BUILTIN_GROUPS
    Exclude local builtin groups returned by groups enumeration.

DSOP_DOWNLEVEL_FILTER_TERMINAL_SERVER
    Include builtin security principal Terminal Server.

DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS
    Include all builtin security principals.
*/

#define DSOP_DOWNLEVEL_FILTER_USERS                   0x80000001
#define DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS            0x80000002
#define DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS           0x80000004
#define DSOP_DOWNLEVEL_FILTER_COMPUTERS               0x80000008
#define DSOP_DOWNLEVEL_FILTER_WORLD                   0x80000010
#define DSOP_DOWNLEVEL_FILTER_AUTHENTICATED_USER      0x80000020
#define DSOP_DOWNLEVEL_FILTER_ANONYMOUS               0x80000040
#define DSOP_DOWNLEVEL_FILTER_BATCH                   0x80000080
#define DSOP_DOWNLEVEL_FILTER_CREATOR_OWNER           0x80000100
#define DSOP_DOWNLEVEL_FILTER_CREATOR_GROUP           0x80000200
#define DSOP_DOWNLEVEL_FILTER_DIALUP                  0x80000400
#define DSOP_DOWNLEVEL_FILTER_INTERACTIVE             0x80000800
#define DSOP_DOWNLEVEL_FILTER_NETWORK                 0x80001000
#define DSOP_DOWNLEVEL_FILTER_SERVICE                 0x80002000
#define DSOP_DOWNLEVEL_FILTER_SYSTEM                  0x80004000
#define DSOP_DOWNLEVEL_FILTER_EXCLUDE_BUILTIN_GROUPS  0x80008000
#define DSOP_DOWNLEVEL_FILTER_TERMINAL_SERVER         0x80010000
#define DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS      0x80020000


/*
DSOP_UPLEVEL_FILTER_FLAGS
=========================

Contains the DSOP_FILTER_* flags for use with a DSOP_SCOPE_INIT_INFO
structure when the scope is uplevel (DS-aware).

flBothModes
    Flags to use for an uplevel scope, regardless of whether it is a
    mixed or native mode domain.

flMixedModeOnly
    Flags to use when an uplevel domain is in mixed mode.

flNativeModeOnly
    Flags to use when an uplevel domain is in native mode.


DSOP_FILTER_FLAGS
=================

Uplevel
    Contains flags to use for an uplevel scope.

flDownlevel
    Flags to use for a downlevel scope.
*/

typedef struct _DSOP_UPLEVEL_FILTER_FLAGS
{
    ULONG       flBothModes;
    ULONG       flMixedModeOnly;
    ULONG       flNativeModeOnly;
} DSOP_UPLEVEL_FILTER_FLAGS;

typedef struct _DSOP_FILTER_FLAGS
{
    DSOP_UPLEVEL_FILTER_FLAGS   Uplevel;
    ULONG                       flDownlevel;
} DSOP_FILTER_FLAGS;


/*
DSOP_SCOPE_INIT_INFO
====================

Each DSOP_SCOPE_INIT_INFO structure in the array DSOP_INIT_INFO.aDsScopeInfos
describes a single scope or a group of scopes with the same settings.

cbSize
    Size, in bytes, of the entire structure.

flType
    DSOP_SCOPE_TYPE_* flags.  It is legal to combine multiple values via
    bitwise OR if all of the types of scopes combined in this way require
    the same settings.

flScope
    DSOP_SCOPE_ * flags.

FilterFlags
    DSOP_FILTER_* flags that indicate which types of objects should be
    presented to the user in this scope.

pwzDcName
    Name of the DC of a domain.  This member is used only if the flType
    member contains the flag DSOP_SCOPE_TYPE_JOINED_DOMAIN.  If that flag is
    not set, this member must be NULL.

pwzADsPath
    Currently not supported, must be NULL.

hr
    Filled with S_OK if the scope represented by this structure could be
    created, or an error message indicating why it could not.  If
    IDsObjectPicker::SetScopes returns a success code, this value will
    also be a success code.
*/

typedef struct _DSOP_SCOPE_INIT_INFO
{
    ULONG               cbSize;
    ULONG               flType;
    ULONG               flScope;
    DSOP_FILTER_FLAGS   FilterFlags;
    PCWSTR              pwzDcName;      // OPTIONAL
    PCWSTR              pwzADsPath;     // OPTIONAL
    HRESULT             hr;
} DSOP_SCOPE_INIT_INFO, *PDSOP_SCOPE_INIT_INFO;

typedef const DSOP_SCOPE_INIT_INFO *PCDSOP_SCOPE_INIT_INFO;

/*
DSOP_INIT_INFO flags
====================

The following flags may be set in DSOP_INIT_INFO.flOptions:

DSOP_FLAG_MULTISELECT
    Allow multiple selections.  If this flag is not set, the dialog will
    return zero or one objects.

DSOP_FLAG_SKIP_TARGET_COMPUTER_DC_CHECK
    If this flag is NOT set, then the DSOP_SCOPE_TYPE_TARGET_COMPUTER flag
    will be ignored if the target computer is a DC.  This flag has no effect
    unless DSOP_SCOPE_TYPE_TARGET_COMPUTER is specified.

*/

#define DSOP_FLAG_MULTISELECT                    0x00000001
#define DSOP_FLAG_SKIP_TARGET_COMPUTER_DC_CHECK  0x00000002

/*
DSOP_INIT_INFO
==============

Used to configure the DS Object Picker dialog.

cbSize
    Size, in bytes, of entire structure.

pwzTargetComputer
    Sets the computer associated with DSOP_SCOPE_TARGET_COMPUTER, and
    which is used to determine the joined domain and enterprise.
    If this value is NULL, the target computer is the local machine.

cDsScopeInfos
    Count of elements in aDsScopeInfos.  Must be at least 1, since
    the object picker cannot operate without at least one scope.

aDsScopeInfos
    Array of scope initialization structures.  Must be present and
    contain at least one element.

flOptions
    Various DS Object Picker flags (DSOP_FLAG_MULTISELECT).

cAttributesToFetch
    Count of elements in apwzAttributeNames.  Can be 0.

apwzAttributeNames
    Array of names of attributes to fetch for each object.  Ignored
    if cAttributesToFetch is 0.
*/

typedef struct _DSOP_INIT_INFO
{
    ULONG                       cbSize;
    PCWSTR                      pwzTargetComputer;
    ULONG                       cDsScopeInfos;
    PDSOP_SCOPE_INIT_INFO       aDsScopeInfos;
    ULONG                       flOptions;
    ULONG                       cAttributesToFetch;
    PCWSTR                     *apwzAttributeNames;
} DSOP_INIT_INFO, *PDSOP_INIT_INFO;

typedef const DSOP_INIT_INFO *PCDSOP_INIT_INFO;

/*
DS_SELECTION
============
Describes an object selected by the user.

pwzName
    The object's RDN.

pwzADsPath
    The object's ADsPath.

pwzClass
    The object's class attribute value.

pwzUPN
    The object's userPrincipalName attribute value.

pvarFetchedAttributes
    An array of VARIANTs, one for each attribute fetched.

flScopeType
    A single DSOP_SCOPE_TYPE_* flag describing the type of the scope
    from which this object was selected.


DS_SELECTION_LIST
=================
Available as a clipboard format from the data object returned by
IDsObjectPicker::InvokeDialog.  Contains a list of objects that the user
selected.

cItems
    Number of elements in the aDsSelection array.

cFetchedAttributes
    Number of elements in each DSSELECTION.avarFetchedAttributes member.

aDsSelection
    Array of cItems DSSELECTION structures.
*/


typedef struct _DS_SELECTION
{
    PWSTR      pwzName;
    PWSTR      pwzADsPath;
    PWSTR      pwzClass;
    PWSTR      pwzUPN;
    VARIANT   *pvarFetchedAttributes;
    ULONG      flScopeType;
} DS_SELECTION, *PDS_SELECTION;


typedef struct _DS_SELECTION_LIST
{
    ULONG           cItems;
    ULONG           cFetchedAttributes;
    DS_SELECTION    aDsSelection[ANYSIZE_ARRAY];
} DS_SELECTION_LIST, *PDS_SELECTION_LIST;

//
// Object Picker Interfaces
//

//
// The main interface to the DS Object Picker, used to initialize it,
// invoke the dialog, and return the user's selections.
//

#undef INTERFACE
#define INTERFACE IDsObjectPicker

DECLARE_INTERFACE_(IDsObjectPicker, IUnknown)
{
    // *** IUnknown methods ***

    STDMETHOD(QueryInterface)(
        THIS_
        REFIID riid,
        PVOID *ppv) PURE;

    STDMETHOD_(ULONG,AddRef)(THIS) PURE;

    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // *** IDsObjectPicker methods ***

    // Sets scope, filter, etc. for use with next invocation of dialog
    STDMETHOD(Initialize)(
        THIS_
        PDSOP_INIT_INFO pInitInfo) PURE;

    // Creates the modal DS Object Picker dialog.
    STDMETHOD(InvokeDialog)(
         THIS_
         HWND               hwndParent,
         IDataObject      **ppdoSelections) PURE;
};


#endif // __OBJSEL_H_

