// --edkcfg.c-------------------------------------------------------------------
//
//  Routines to aid in saving and retrieving configuration information for 
//  gateways and other objects to and from the DIT.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "attrname.h"
#include "edkcfg.chk"

static HRESULT HrCfgCountProps(
    IN  int cprop, 
    IN  LPSPropValue rgprop, 
    OUT ULONG FAR *pcb);

static HRESULT HrCfgCopyProps(
    IN  int cprop, 
    IN  LPSPropValue rgprop, 
    OUT LPVOID pvDst, 
    OUT ULONG FAR *pcb);

#define Align(_cb)	(((_cb) + 7) & ~7)

//	Pointer manipulation macros for use in the Reloc functions
#ifdef WIN16
#define SEG(_fp)	HIWORD((DWORD)_fp)
#define OFF(_fp)	LOWORD((DWORD)_fp)

#define PvRelocPv(_p,_baseOld,_baseNew) \
	((LPVOID)MAKELONG(OFF(_p) - OFF(_baseOld) + OFF(_baseNew), SEG(_baseNew)))
#else
#define PvRelocPv(_p,_baseOld,_baseNew)	\
	((LPVOID)((LPBYTE)(_p) - (LPBYTE)(_baseOld) + (LPBYTE)(_baseNew)))
#endif


#define SITE_ADDRESSING_RDN "/cn=Configuration/cn=Site-Addressing"

// Magic number to indicate that this is a valid configuration data structure.
// The value 0x10101010 was chosen because older code used the byte value 0x10 
// to mean "end of record", so any older code reading this structure will 
// ignore the data.
#define EDKCFG_MAGIC_NUMBER		0x10101010

// Version number that determines the format of the data that comes after it 
// in the structure.
#define EDKCFG_VERSION_NUMBER	1

// The routines in this file pack and unpack a set of MAPI properties into a 
// binary data structure which can be stored in a file or the directory 
// information tree.  The binary data structure has the following format:
//
// +---------------------------------------+
// | UNICODE Config Name (null-terminated) |
// +---------------------------------------+
// | DWORD EDKCFG_MAGIC_NUMBER             |
// +---------------------------------------+
// | DWORD EDKCFG_VERSION_NUMBER           |
// +---------------------------------------+
// | DWORD Number of properties            |
// +---------------------------------------+
// | Packed binary array of properties     |
// +---------------------------------------+

//$--HrCfgPackData--------------------------------------------------------------
//  Take a configuration name and a set of MAPI properties and pack them into 
//  a binary buffer suitable to be saved in the directory information tree for 
//  the gateway or other object.
// -----------------------------------------------------------------------------
HRESULT HrCfgPackDataA(                     // RETURN: HRESULT
	IN	LPSTR			lpszOwnerTag,		// name of configuration (or NULL)
	IN	ULONG			cProps,				// number of MAPI properties
	IN	LPSPropValue	lpProps,			// MAPI properties for this config.
	OUT	ULONG *			lpcbConfigData,		// size of resulting binary struct.
	OUT	LPBYTE *		lppbConfigData)		// resulting binary structure
{
	HRESULT		hr					= NOERROR;
    LPWSTR      lpwszOwnerTag       = NULL;

	DEBUGPUBLIC("HrCfgPackDataA()\n");

	hr = CHK_HrCfgPackDataA(
		lpszOwnerTag, 
		cProps, 
		lpProps, 
		lpcbConfigData, 
		lppbConfigData);
	if (FAILED(hr))
		RETURN(hr);

    // Convert config name to word string.

    if (lpszOwnerTag)
    {
        hr = HrStrAToStrW(lpszOwnerTag, &lpwszOwnerTag);
        if (FAILED(hr))
            goto cleanup;
    }

    // Do the packing operation.

    hr = HrCfgPackDataW(
        lpwszOwnerTag, 
        cProps, 
        lpProps, 
        lpcbConfigData, 
        lppbConfigData);
    if (FAILED(hr))
        goto cleanup;

cleanup:
    MAPIFREEBUFFER(lpwszOwnerTag);

    RETURN(hr);
}


HRESULT HrCfgPackDataW(                     // RETURN: HRESULT
	IN	LPWSTR			lpwszOwnerTag,	    // name of configuration (or NULL)
	IN	ULONG			cProps,				// number of MAPI properties
	IN	LPSPropValue	lpProps,			// MAPI properties for this config.
	OUT	ULONG *			lpcbConfigData,		// size of resulting binary struct.
	OUT	LPBYTE *		lppbConfigData)		// resulting binary structure
{
	HRESULT		hr					= NOERROR;

	ULONG		cbConfigData		= 0;
	LPBYTE		pbConfigData		= NULL;

	ULONG		ib					= 0;
	ULONG		ibOwnerTag		    = 0;
	ULONG		cchOwnerTag		    = 0;
	ULONG		ibMagicNumber		= 0;
	ULONG		ibVersionNumber		= 0;
	ULONG		ibPropCount			= 0;
	ULONG		ibPackedProps		= 0;
	ULONG		cbPackedProps		= 0;

	DEBUGPUBLIC("HrCfgPackDataW()\n");

	hr = CHK_HrCfgPackDataW(
		lpwszOwnerTag, 
		cProps, 
		lpProps, 
		lpcbConfigData, 
		lppbConfigData);
	if (FAILED(hr))
		RETURN(hr);

    // If they passed NULL for configuration name then use an empty string.

    if (lpwszOwnerTag == NULL)
    {
        lpwszOwnerTag = L"";
    }

	// Figure out how much memory to allocate, and the offsets of the various 
	// fields within the allocated memory.  Also figure out the size of the 
	// packed property structure.

	ib = 0;

	ibOwnerTag = ib;
	cchOwnerTag = wcslen(lpwszOwnerTag);
	ib += ((cchOwnerTag + 1) * sizeof(WCHAR));

	ibMagicNumber = ib;
	ib += sizeof(DWORD);

	ibVersionNumber = ib;
	ib += sizeof(DWORD);

	ibPropCount = ib;
	ib += sizeof(DWORD);

	if (cProps)
	{
		ibPackedProps = ib;
		hr = HrCfgCountProps(cProps, lpProps, &cbPackedProps);
		if (FAILED(hr))
			goto cleanup;
		ib += cbPackedProps;
	}

	cbConfigData = ib;

	// Allocate the memory.

	hr = MAPIAllocateBuffer(cbConfigData, &pbConfigData);
	if (FAILED(hr))
		goto cleanup;

	// Write the properties (if any) to the buffer.  This must be done first.

	if (cProps)
	{
		ULONG cbSizeRequired = 0;

		// Convert the properties to a packed binary structure AT THE FRONT 
		// of the memory we just allocated.  It will be moved to the back 
		// later.  This makes sure the conversion output buffer is aligned 
		// on an eight-byte boundry.

		hr = HrCfgCopyProps(cProps, lpProps, pbConfigData, &cbSizeRequired);
		if (FAILED(hr))
			goto cleanup;
		if (cbSizeRequired > cbPackedProps)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		// Make all pointers relative to the start of the property array.

		hr = ScRelocProps(cProps, (LPSPropValue)pbConfigData, pbConfigData, 0, 
			&cbSizeRequired);
		if (FAILED(hr))
			goto cleanup;
		if (cbSizeRequired > cbPackedProps)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		// Now copy the packed property array to the back of the buffer.

		MoveMemory(pbConfigData + ibPackedProps, pbConfigData, cbPackedProps);
	}

	// Write the configuration name to the buffer.

	{
        wcscpy((LPWSTR)(pbConfigData + ibOwnerTag), lpwszOwnerTag);
	}

	// Write magic number, version number, and number of properties 
	// to the buffer.

	{
		DWORD	dwMagicNumber		= EDKCFG_MAGIC_NUMBER;
		DWORD	dwVersionNumber		= EDKCFG_VERSION_NUMBER;
		DWORD	dwPropCount			= cProps;

		MoveMemory(pbConfigData + ibMagicNumber, &dwMagicNumber, 
			sizeof(dwMagicNumber));
		MoveMemory(pbConfigData + ibVersionNumber, &dwVersionNumber, 
			sizeof(dwVersionNumber));
		MoveMemory(pbConfigData + ibPropCount, &dwPropCount, 
			sizeof(dwPropCount));
	}

	// Return the address and size of the buffer to the caller.

	*lpcbConfigData = cbConfigData;
	*lppbConfigData = pbConfigData;

cleanup:
	if (FAILED(hr))
	{
		MAPIFREEBUFFER(pbConfigData);
	}

	RETURN(hr);
}


//$--HrCfgUnpackData------------------------------------------------------------
//  Take a packed binary buffer and unpack it to yield a configuration name, 
//  number of properties, and an array of MAPI properties.  If the number of 
//  properties is zero then NULL is returned for the array of properties.
// -----------------------------------------------------------------------------
HRESULT HrCfgUnpackDataA(					// RETURNS: HRESULT
	IN	ULONG			cbConfigData,		// size of of binary structure
	IN	LPBYTE			lpbConfigData,		// pointer to binary structure
	OUT	LPSTR *	    	lppszOwnerTag,	    // name of configuration (or NULL)
	OUT	ULONG *			lpcProps,			// number of MAPI properties
	OUT	LPSPropValue *	lppProps)			// MAPI properties for this config.
{
	HRESULT			hr				= NOERROR;
    LPWSTR          pwszOwnerTag    = NULL;
    LPSTR           pszOwnerTag     = NULL;

	DEBUGPUBLIC("HrCfgUnpackDataA()\n");

	hr = CHK_HrCfgUnpackDataA(
		cbConfigData, 
		lpbConfigData, 
		lppszOwnerTag, 
		lpcProps, 
		lppProps);
	if (FAILED(hr))
		RETURN(hr);

    // If they want the name returned then call the UNICODE version 
    // and then convert the name to a byte string.

    if (lppszOwnerTag)
    {
        hr = HrCfgUnpackDataW(
            cbConfigData, 
            lpbConfigData, 
            &pwszOwnerTag, 
            lpcProps, 
            lppProps);
        if (FAILED(hr))
            goto cleanup;

        hr = HrStrWToStrA(pwszOwnerTag, &pszOwnerTag);
        if (FAILED(hr))
            RETURN(hr);

        *lppszOwnerTag = pszOwnerTag;
    }

    // If they don't care about the name, then just call the UNICODE 
    // version and return.

    else
    {
        hr = HrCfgUnpackDataW(
            cbConfigData, 
            lpbConfigData, 
            NULL, 
            lpcProps, 
            lppProps);
        if (FAILED(hr))
            goto cleanup;
    }

cleanup:
    MAPIFREEBUFFER(pwszOwnerTag);

    RETURN(hr);
}


HRESULT HrCfgUnpackDataW(					// RETURNS: HRESULT
	IN	ULONG			cbConfigData,		// size of of binary structure
	IN	LPBYTE			lpbConfigData,		// pointer to binary structure
	OUT	LPWSTR *		lppwszOwnerTag,	    // name of configuration (or NULL)
	OUT	ULONG *			lpcProps,			// number of MAPI properties
	OUT	LPSPropValue *	lppProps)			// MAPI properties for this config.
{
	HRESULT			hr				= NOERROR;
	LPBYTE			pb				= lpbConfigData;
	ULONG			cb				= cbConfigData;
	LPWSTR			pwszOwnerTag	= NULL;
	ULONG			cProps			= 0;
	LPSPropValue	pProps			= NULL;
    ULONG           cchOwnerTag     = 0;

	DEBUGPUBLIC("HrCfgUnpackDataW()\n");

	hr = CHK_HrCfgUnpackDataW(
		cbConfigData, 
		lpbConfigData, 
		lppwszOwnerTag, 
		lpcProps, 
		lppProps);
	if (FAILED(hr))
		RETURN(hr);

	// If they requested the configuration name then get it.

	if (lppwszOwnerTag)
	{

        hr = HrStrWToStrW((LPWSTR)pb, &pwszOwnerTag);
		if (FAILED(hr))
			goto cleanup;
	}

    cchOwnerTag = wcslen((LPWSTR)pb);
	pb += ((cchOwnerTag + 1) * sizeof(WCHAR));
	cb -= ((cchOwnerTag + 1) * sizeof(WCHAR));

	// Make sure the magic number is correct.

	{
		DWORD dwMagicNumber = 0;

		MoveMemory(&dwMagicNumber, pb, sizeof(dwMagicNumber));
		pb += sizeof(dwMagicNumber);
		cb -= sizeof(dwMagicNumber);

		if (dwMagicNumber != EDKCFG_MAGIC_NUMBER)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
	}

	// Make sure the version number is correct.

	{
		DWORD dwVersionNumber = 0;

		MoveMemory(&dwVersionNumber, pb, sizeof(dwVersionNumber));
		pb += sizeof(dwVersionNumber);
		cb -= sizeof(dwVersionNumber);

		if (dwVersionNumber != EDKCFG_VERSION_NUMBER)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
	}

	// Get the number of properties.

	{
		DWORD dwPropCount = 0;

		MoveMemory(&dwPropCount, pb, sizeof(dwPropCount));
		pb += sizeof(dwPropCount);
		cb -= sizeof(dwPropCount);
		cProps = dwPropCount;
	}

	// Get and unpack the property structure if there are any properties 
    // (otherwise we return NULL for the pointer to the property array).

    if (cProps)
	{
		ULONG cbSizeRequired = 0;

		hr = MAPIAllocateBuffer(cb, &pProps);
		if (FAILED(hr))
			goto cleanup;

		if (cProps)
		{
			MoveMemory(pProps, pb, cb);
			hr = ScRelocProps(cProps, pProps, 0, pProps, &cbSizeRequired);
			if (FAILED(hr))
				goto cleanup;
            if (cbSizeRequired > cb)
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
		}
	}

	// Fill in output parameters.

	if (lppwszOwnerTag)
	{
		*lppwszOwnerTag = pwszOwnerTag;
	}
	*lpcProps = cProps;
	*lppProps = pProps;

cleanup:
	if (FAILED(hr))
	{
		MAPIFREEBUFFER(pwszOwnerTag);
		MAPIFREEBUFFER(pProps);
	}

	RETURN(hr);
}

//$--HrOpenSiteContainer-----------------------------------------------------------------
//  Takes a pointer to a MAPI session and returns an IMAPIProp interface for 
//  the current site object.
// -----------------------------------------------------------------------------
HRESULT HrOpenSiteContainer(							// RETURNS: HRESULT
	IN	LPMAPISESSION	lpSession,			// MAPI session
	OUT	LPMAPIPROP *	lppSite)			// current site
{
	HRESULT			hr						= NOERROR;
	LPMAPIPROP		pCurrentObjectInterface	= NULL;
	LPSPropValue	pEmailAddressProps		= NULL;
	LPSTR			pszDN					= NULL;
	ULONG			cbSiteEntryID			= 0;
	LPENTRYID		pSiteEntryID			= NULL;
	LPMAPIPROP		pSiteInterface			= NULL;

	DEBUGPUBLIC("HrOpenSiteContainer()\n");

	hr = CHK_HrOpenSiteContainer(
		lpSession, 
		lppSite);
	if (FAILED(hr))
		RETURN(hr);

	// Get an IMAPIProp interface for the current object.

	hr = HrOpenSessionObject(lpSession, &pCurrentObjectInterface);
	if (FAILED(hr))
		goto cleanup;

	// Get the PR_EMAIL_ADDRESS property.

	{
		SPropTagArray GetEmailAddress = {1, {PR_EMAIL_ADDRESS_A}};
		ULONG cProps = 0;

		hr = MAPICALL(pCurrentObjectInterface)->GetProps(
			pCurrentObjectInterface, 
			&GetEmailAddress, 
			0L, 
			&cProps, 
			&pEmailAddressProps);
		if (cProps != 1)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
		if (hr == MAPI_W_ERRORS_RETURNED)
		{
			hr = HR_LOG(pEmailAddressProps->Value.err);
			goto cleanup;
		}
		if (FAILED(hr))
			goto cleanup;
	}

	// Create the DN from the PR_EMAIL_ADDRESS property.

	{
		LPSTR pszSrc = pEmailAddressProps->Value.lpszA;
		LPSTR pszSrcLim = pszSrc;
		ULONG cbDN = 0;

		// Find the first '/' after the "/o=" and "/ou=", to extract the 
		// DN from the e-mail address.

		while (*pszSrcLim && (
			*pszSrcLim != '/' || 
			!_strnicmp(pszSrcLim,"/o=",3) || 
			!_strnicmp(pszSrcLim,"/ou=",4)))
		{
			pszSrcLim++;
		}
		cbDN = pszSrcLim - pszSrc;

		// Copy the string into an allocated buffer.

		hr = MAPIAllocateBuffer(cbDN + 1, &pszDN);
		if (FAILED(hr))
			goto cleanup;

		MoveMemory(pszDN, pszSrc, cbDN);
		pszDN[cbDN] = 0;
	}

	// Create a directory entry ID for this site using the DN.

	{
		hr = HrCreateDirEntryId(pszDN, &cbSiteEntryID, &pSiteEntryID);
		if (FAILED(hr))
			goto cleanup;
	}

	// Open the site entry ID and get an IMAPIProp interface.

	{
		ULONG ulObjType = 0;

		hr = MAPICALL(lpSession)->OpenEntry(
			lpSession, 
			cbSiteEntryID, 
			pSiteEntryID, 
			&IID_IMAPIProp, 
			MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
			&ulObjType, 
			(LPUNKNOWN FAR *)&pSiteInterface);
		if (FAILED(hr))
			goto cleanup;
	}

	// Everything was successful, so return the site interface to the caller.

	*lppSite = pSiteInterface;

cleanup:

	ULRELEASE(pCurrentObjectInterface);

	MAPIFREEBUFFER(pEmailAddressProps);
	MAPIFREEBUFFER(pszDN);
	MAPIFREEBUFFER(pSiteEntryID);

	if (FAILED(hr))
	{
		ULRELEASE(pSiteInterface);
		*lppSite = NULL;
	}

	RETURN(hr);
}

//$--HrOpenSiteContainerAddressing-------------------------------------------------------
//  Takes a pointer to a MAPI session and returns an IMAPIProp interface for 
//  the current site addressing object.
// -----------------------------------------------------------------------------
HRESULT HrOpenSiteContainerAddressing(               // RETURNS: HRESULT
	IN	LPMAPISESSION	lpSession,          // MAPI session
	OUT	LPMAPIPROP *	lppSiteAddressing)  // current site addressing
{
	HRESULT			hr						= NOERROR;
	LPMAPIPROP		pCurrentObjectInterface	= NULL;
	LPSPropValue	pEmailAddressProps		= NULL;
	LPSTR			pszDN					= NULL;
	ULONG			cbSiteAddrEntryID       = 0;
	LPENTRYID		pSiteAddrEntryID        = NULL;
	LPMAPIPROP		pSiteAddrInterface      = NULL;

	DEBUGPUBLIC("HrOpenSiteContainerAddressing()\n");

	hr = CHK_HrOpenSiteContainerAddressing(
		lpSession, 
		lppSiteAddressing);
	if (FAILED(hr))
		RETURN(hr);

	// Get an IMAPIProp interface for the current object.

	hr = HrOpenSessionObject(lpSession, &pCurrentObjectInterface);
	if (FAILED(hr))
		goto cleanup;

	// Get the PR_EMAIL_ADDRESS property.

	{
		SPropTagArray GetEmailAddress = {1, {PR_EMAIL_ADDRESS_A}};
		ULONG cProps = 0;

		hr = MAPICALL(pCurrentObjectInterface)->GetProps(
			pCurrentObjectInterface, 
			&GetEmailAddress, 
			0L, 
			&cProps, 
			&pEmailAddressProps);
		if (cProps != 1)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
		if (hr == MAPI_W_ERRORS_RETURNED)
		{
			hr = HR_LOG(pEmailAddressProps->Value.err);
			goto cleanup;
		}
		if (FAILED(hr))
			goto cleanup;
	}

	// Create the DN from the PR_EMAIL_ADDRESS property.

	{
		LPSTR pszSrc    = pEmailAddressProps->Value.lpszA;
		LPSTR pszSrcLim = pszSrc;
		ULONG cbDN      = 0;
		ULONG cbRDN     = 0;

		// Find the first '/' after the "/o=" and "/ou=", to extract the 
		// DN from the e-mail address.

		while (*pszSrcLim && (
			*pszSrcLim != '/' || 
			!_strnicmp(pszSrcLim,"/o=",3) || 
			!_strnicmp(pszSrcLim,"/ou=",4)))
		{
			pszSrcLim++;
		}

		cbDN  = pszSrcLim - pszSrc;

        cbRDN = strlen(SITE_ADDRESSING_RDN);

		// Copy the string into an allocated buffer.

		hr = MAPIAllocateBuffer(cbDN + cbRDN + 1, &pszDN);
		if (FAILED(hr))
			goto cleanup;

		MoveMemory(pszDN, pszSrc, cbDN);
		pszDN[cbDN] = 0;
        strcat(pszDN,SITE_ADDRESSING_RDN);
	}

	// Create a directory entry ID for this site addressing object using the DN.

	{
		hr = HrCreateDirEntryId(
		    pszDN,
		    &cbSiteAddrEntryID,
		    &pSiteAddrEntryID);

		if (FAILED(hr))
			goto cleanup;
	}

	// Open the site addressing entry ID and get an IMAPIProp interface.

	{
		ULONG ulObjType = 0;

		hr = MAPICALL(lpSession)->OpenEntry(
			lpSession, 
			cbSiteAddrEntryID, 
			pSiteAddrEntryID, 
			&IID_IMAPIProp, 
			MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
			&ulObjType, 
			(LPUNKNOWN FAR *)&pSiteAddrInterface);
		if (FAILED(hr))
			goto cleanup;
	}

	// Everything was successful, so return the site addressing interface
	// to the caller.

	*lppSiteAddressing = pSiteAddrInterface;

cleanup:

	ULRELEASE(pCurrentObjectInterface);

	MAPIFREEBUFFER(pEmailAddressProps);
	MAPIFREEBUFFER(pszDN);
	MAPIFREEBUFFER(pSiteAddrEntryID);

	if (FAILED(hr))
	{
		ULRELEASE(pSiteAddrInterface);
		*lppSiteAddressing = NULL;
	}

	RETURN(hr);
}

//$--HrOpenSessionObject--------------------------------------------------------
//  Takes a pointer to a MAPI session and returns an IMAPIProp interface for 
//  the current object that the session is logged in as.
// -----------------------------------------------------------------------------
HRESULT HrOpenSessionObject(				// RETURNS: HRESULT
	IN	LPMAPISESSION	lpSession,			// MAPI session
	OUT	LPMAPIPROP *	lppCurrentObject)	// current object
{
	HRESULT			hr						= NOERROR;
	ULONG			cbSessionEntryID		= 0;
	LPENTRYID		pSessionEntryID			= NULL;
	LPMAPIPROP		pCurrentObjectInterface	= NULL;

	DEBUGPUBLIC("HrOpenSessionObject()\n");

	hr = CHK_HrOpenSessionObject(
		lpSession, 
		lppCurrentObject);
	if (FAILED(hr))
		RETURN(hr);

	// Get the entry ID for the session.

	{
		hr = MAPICALL(lpSession)->QueryIdentity(
			lpSession, 
			&cbSessionEntryID, 
			&pSessionEntryID);
		if (FAILED(hr))
			goto cleanup;
	}

	// Open the entry ID and get an IMAPIProp interface.

	{
		ULONG ulObjType = 0;

		hr = MAPICALL(lpSession)->OpenEntry(
			lpSession, 
			cbSessionEntryID, 
			pSessionEntryID, 
			&IID_IMAPIProp, 
			MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS, 
			&ulObjType, 
			(LPUNKNOWN FAR *)&pCurrentObjectInterface);
		if (FAILED(hr))
			goto cleanup;
	}

	// Everything was successful, so return the site interface to the caller.

	*lppCurrentObject = pCurrentObjectInterface;

cleanup:
    if (FAILED(hr))
    {
        ULRELEASE(pCurrentObjectInterface);
        *lppCurrentObject = NULL;
    }
	MAPIFREEBUFFER(pSessionEntryID);
	RETURN(hr);
}

//$--HrCfgPropertyTagFromNameId----------------------------------------------------
//  Takes a pointer to an IMAPIProp interface and a name ID, and returns the 
//  MAPI property tag that represents the given name ID for that interface.
// -----------------------------------------------------------------------------
HRESULT HrCfgPropertyTagFromNameId(			// RETURNS: HRESULT
	IN	LPMAPIPROP		lpMAPIProp,			// IMAPIProp interface
    IN  LONG            lNameID,            // Name ID
	OUT	ULONG *			lpulPropTag)		// MAPI property tag of name ID
{
	HRESULT			hr				= NOERROR;
	MAPINAMEID		sNameID			= {0};
	LPMAPINAMEID	rglpNameID[1]	= {&sNameID};
	LPSPropTagArray	lpPropTags		= NULL;

	DEBUGPUBLIC("HrCfgPropertyTagFromNameId()\n");

	hr = CHK_HrCfgPropertyTagFromNameId(
		lpMAPIProp, 
		lNameID, 
		lpulPropTag);
	if (FAILED(hr))
		RETURN(hr);

	// Construct the MAPINAMEID.

	sNameID.lpguid = (LPGUID)PS_EXCHANGE_DIRECTORY;
	sNameID.ulKind = MNID_ID;
	sNameID.Kind.lID = lNameID;

	// Get the property tag.

	hr = MAPICALL(lpMAPIProp)->GetIDsFromNames(
		lpMAPIProp, 
		1, 
		rglpNameID, 
		0, 
		&lpPropTags);
	if (FAILED(hr))
		goto cleanup;

	// Extract the property tag from the array.

	*lpulPropTag = lpPropTags->aulPropTag[0];

cleanup:
	MAPIFREEBUFFER(lpPropTags);
	RETURN(hr);
}



//$--HrCfgCountProps------------------------------------------------------------
//  Counts the size of the memory needed to hold a property array.
//  This works like the MAPI routine ScCountProps but always uses 
//  RISC-like 8-byte alignment.
// -----------------------------------------------------------------------------
static HRESULT HrCfgCountProps(             // RETURNS: HRESULT
    IN  int cprop,                          // number of properties
    IN  LPSPropValue rgprop,                // array of properties
    OUT ULONG FAR *pcb)                     // number of bytes needed
{
    HRESULT             hr                  = NOERROR;
	LPSPropValue	    pprop               = NULL;
	ULONG			    cb                  = 0;
	ULONG			    cbMV                = 0;
	int				    iValue              = 0;

    DEBUGPRIVATE("HrCfgCountProps()");

	for (pprop = rgprop; cprop--; ++pprop)
	{
		ULONG	ulID = PROP_ID(pprop->ulPropTag);
		ULONG	ulType = PROP_TYPE(pprop->ulPropTag);

		//	Check for valid PROP_ID.

		if (   (ulID == PROP_ID_INVALID)
			|| ((ulType == PT_NULL) && (ulID != PROP_ID_NULL))
			|| ((ulType != PT_NULL) && (ulID == PROP_ID_NULL)))
        {
            hr = E_INVALIDARG;
            goto cleanup;
        }

		//	Check for valid PROP_TYPE and count memory consumed.

		cb += sizeof(SPropValue);
		switch ( PROP_TYPE(pprop->ulPropTag) )
		{
			case PT_UNSPECIFIED:
			default:
                hr = E_INVALIDARG;
                goto cleanup;

			case PT_I2:
			case PT_LONG:
			case PT_R4:
			case PT_APPTIME:
			case PT_DOUBLE:
			case PT_BOOLEAN:
			case PT_CURRENCY:
			case PT_SYSTIME:
			case PT_I8:
			case PT_ERROR:
			case PT_OBJECT:
			case PT_NULL:
				break;

			case PT_CLSID:
				if (IsBadReadPtr(pprop->Value.lpguid, sizeof(GUID)))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align(sizeof(GUID));
				break;

			case PT_BINARY:
				if (pprop->Value.bin.cb && IsBadReadPtr( pprop->Value.bin.lpb
								, (UINT) (pprop->Value.bin.cb)))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align(pprop->Value.bin.cb);
				break;

			case PT_STRING8:
				if (IsBadStringPtrA(pprop->Value.lpszA, INFINITE))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align((lstrlenA( pprop->Value.lpszA ) + 1) * sizeof(CHAR));
				break;

			case PT_UNICODE:
				if (IsBadStringPtrW(pprop->Value.lpszW, INFINITE))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align((lstrlenW( pprop->Value.lpszW ) + 1) * sizeof(WCHAR));
				break;

			case PT_MV_I2:
				if (   !(cbMV = pprop->Value.MVi.cValues * sizeof(short int))
					|| IsBadReadPtr(pprop->Value.MVi.lpi, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align(cbMV);
				break;

			case PT_MV_LONG:
				if (   !(cbMV = pprop->Value.MVl.cValues * sizeof(LONG))
					|| IsBadReadPtr(pprop->Value.MVl.lpl, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align(cbMV);
				break;

			case PT_MV_R4:
				if (   !(cbMV = pprop->Value.MVflt.cValues * sizeof(float))
					|| IsBadReadPtr(pprop->Value.MVflt.lpflt, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += Align(cbMV);
				break;

			case PT_MV_APPTIME:
				if (   !(cbMV = pprop->Value.MVat.cValues * sizeof(double))
					|| IsBadReadPtr(pprop->Value.MVat.lpat, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += cbMV;
				break;

			case PT_MV_DOUBLE:
				if (   !(cbMV = pprop->Value.MVdbl.cValues * sizeof(double))
					|| IsBadReadPtr(pprop->Value.MVdbl.lpdbl, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += cbMV;
				break;

			case PT_MV_CURRENCY:
				if (   !(cbMV = pprop->Value.MVcur.cValues * sizeof(CURRENCY))
					|| IsBadReadPtr(pprop->Value.MVcur.lpcur, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += cbMV;
				break;

			case PT_MV_SYSTIME:
				if (   !(cbMV = pprop->Value.MVft.cValues * sizeof(FILETIME))
					|| IsBadReadPtr(pprop->Value.MVft.lpft, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += cbMV;
				break;

			case PT_MV_CLSID:
				if (   !(cbMV = pprop->Value.MVguid.cValues * sizeof(GUID))
					|| IsBadReadPtr(pprop->Value.MVguid.lpguid, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += cbMV;
				break;

			case PT_MV_I8:
				if (   !(cbMV = pprop->Value.MVli.cValues * sizeof(LARGE_INTEGER))
					|| IsBadReadPtr(pprop->Value.MVli.lpli, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }
				cb += cbMV;
				break;


			case PT_MV_BINARY:
				if (   !(cbMV = pprop->Value.MVbin.cValues * sizeof(SBinary))
					|| IsBadReadPtr(pprop->Value.MVbin.lpbin, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }

				ASSERTERROR(Align(cbMV) == cbMV, "Align(cbMV) != cbMV");
				cb += cbMV;

				for ( iValue = 0;
				  	(ULONG)iValue < pprop->Value.MVbin.cValues;
					  	iValue++ )
				{
					if (IsBadReadPtr(pprop->Value.MVbin.lpbin[iValue].lpb,
							(UINT)pprop->Value.MVbin.lpbin[iValue].cb))
                    {
                        hr = E_INVALIDARG;
                        goto cleanup;
                    }
					cb += Align(pprop->Value.MVbin.lpbin[iValue].cb);
				}
				break;

			case PT_MV_STRING8:
				if (   !(cbMV = pprop->Value.MVszA.cValues * sizeof(LPVOID))
					|| IsBadReadPtr(pprop->Value.MVszA.lppszA, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }

				cb += cbMV;

				for ( iValue = 0;
				  	(ULONG)iValue < pprop->Value.MVszA.cValues;
					  	iValue++ )
				{
					if (IsBadStringPtrA(pprop->Value.MVszA.lppszA[iValue],
										INFINITE))
                    {
                        hr = E_INVALIDARG;
                        goto cleanup;
                    }
					cb += lstrlenA(pprop->Value.MVszA.lppszA[iValue]) + 1;
				}

				cb = Align(cb);

				break;

			case PT_MV_UNICODE:
				if (   !(cbMV = pprop->Value.MVszW.cValues * sizeof(LPVOID))
					|| IsBadReadPtr(pprop->Value.MVszW.lppszW, (UINT) cbMV))
                {
                    hr = E_INVALIDARG;
                    goto cleanup;
                }

				cb += cbMV;

				for ( iValue = 0;
				  	(ULONG)iValue < pprop->Value.MVszW.cValues;
					  	iValue++ )
				{
					if (IsBadStringPtrW(pprop->Value.MVszW.lppszW[iValue], INFINITE))
                    {
                        hr = E_INVALIDARG;
                        goto cleanup;
                    }
					cb += (lstrlenW(pprop->Value.MVszW.lppszW[iValue]) + 1)
						  * sizeof(WCHAR);
				}

				cb = Align(cb);

				break;
		}
	}

	if (pcb)
	{
		*pcb = cb;
	}

cleanup:
	RETURN(hr);
}



//$--HrCfgCopyProps-------------------------------------------------------------
//  Copies a prop table into a single block of memory.
//  This works like the MAPI routine ScCopyProps but always uses 
//  RISC-like 8-byte alignment.
// -----------------------------------------------------------------------------
static HRESULT HrCfgCopyProps(              // RETURNS: HRESULT
    IN  int cprop,                          // number of properties
    IN  LPSPropValue rgprop,                // array of properties
    OUT LPVOID pvDst,                       // pointer to destination memory
    OUT ULONG FAR *pcb)                     // number of bytes needed
{
    HRESULT             hr                  = NOERROR;
	LPSPropValue	    pprop               = NULL;
	LPSPropValue	    ppropDst            = NULL;
	ULONG			    cb                  = 0;
	ULONG			    cbMV                = 0;
	LPBYTE			    pb                  = NULL;
	UINT			    cbT                 = 0;
	int				    iValue              = 0;

    DEBUGPRIVATE("HrCfgCopyProps()");

	cb = cprop * sizeof(SPropValue);
	CopyMemory(pvDst, rgprop, (UINT)cb);
	pb = (LPBYTE)pvDst + cb;

	for (pprop = rgprop, ppropDst = pvDst; cprop--; ++pprop, ++ppropDst)
	{
		//	Tricky: common code after the switch increments pb and cb
		//	by the amount copied. If no increment is necessary, the case
		//	uses 'continue' rather than 'break' to exit the switch, thus
		//	skipping the increment -- AND any other code which may be
		//	added after the switch.

		switch ( PROP_TYPE(pprop->ulPropTag) )
		{
			default:
                hr = E_INVALIDARG;
                goto cleanup;

			case PT_I2:
			case PT_LONG:
			case PT_R4:
			case PT_APPTIME:
			case PT_DOUBLE:
			case PT_BOOLEAN:
			case PT_CURRENCY:
			case PT_SYSTIME:
			case PT_I8:
			case PT_ERROR:
			case PT_OBJECT:
			case PT_NULL:
				continue;	//	nothing to add

			case PT_CLSID:
				ppropDst->Value.lpguid = (LPGUID) pb;
				cbT = sizeof(GUID);
				CopyMemory(pb, (LPBYTE) pprop->Value.lpguid, cbT);
				break;

			case PT_BINARY:
				ppropDst->Value.bin.lpb = pb;
				cbT = (UINT)pprop->Value.bin.cb;
				CopyMemory(pb, pprop->Value.bin.lpb, cbT);
				break;

			case PT_STRING8:
				ppropDst->Value.lpszA = (LPSTR)pb;
				cbT = lstrlenA( pprop->Value.lpszA ) + 1;
				CopyMemory(pb, pprop->Value.lpszA, cbT);
				break;

			case PT_UNICODE:
				ppropDst->Value.lpszW = (LPWSTR)pb;
				cbT = (lstrlenW( pprop->Value.lpszW ) + 1) * sizeof(WCHAR);
				CopyMemory(pb, pprop->Value.lpszW, cbT);
				break;

			case PT_MV_I2:
				ppropDst->Value.MVi.lpi = (short int FAR *)pb;
				cbT = (UINT)pprop->Value.MVi.cValues * sizeof(short int);
				CopyMemory(pb, pprop->Value.MVi.lpi, cbT);
				break;

			case PT_MV_LONG:
				ppropDst->Value.MVl.lpl = (LONG FAR *)pb;
				cbT = (UINT)pprop->Value.MVl.cValues * sizeof(LONG);
				CopyMemory(pb, pprop->Value.MVl.lpl, cbT);
				break;

			case PT_MV_R4:
				ppropDst->Value.MVflt.lpflt = (float FAR *)pb;
				cbT = (UINT)pprop->Value.MVflt.cValues * sizeof(float);
				CopyMemory(pb, pprop->Value.MVflt.lpflt, cbT);
				break;

			case PT_MV_APPTIME:
				ppropDst->Value.MVat.lpat = (double FAR *)pb;
				cbT = (UINT)pprop->Value.MVat.cValues * sizeof(double);
				CopyMemory(pb, pprop->Value.MVat.lpat, cbT);
				break;

			case PT_MV_DOUBLE:
				ppropDst->Value.MVdbl.lpdbl = (double FAR *)pb;
				cbT = (UINT)pprop->Value.MVdbl.cValues * sizeof(double);
				CopyMemory(pb, pprop->Value.MVdbl.lpdbl, cbT);
				break;

			case PT_MV_CURRENCY:
				ppropDst->Value.MVcur.lpcur = (CURRENCY FAR *)pb;
				cbT = (UINT)pprop->Value.MVcur.cValues * sizeof(CURRENCY);
				CopyMemory(pb, pprop->Value.MVcur.lpcur, cbT);
				break;

			case PT_MV_SYSTIME:
				ppropDst->Value.MVft.lpft = (FILETIME FAR *)pb;
				cbT = (UINT)pprop->Value.MVft.cValues * sizeof(FILETIME);
				CopyMemory(pb, pprop->Value.MVft.lpft, cbT);
				break;

			case PT_MV_CLSID:
				ppropDst->Value.MVguid.lpguid = (GUID FAR *)pb;
				cbT = (UINT)pprop->Value.MVguid.cValues * sizeof(GUID);
				CopyMemory(pb, pprop->Value.MVguid.lpguid, cbT);
				break;

			case PT_MV_I8:
				ppropDst->Value.MVli.lpli = (LARGE_INTEGER FAR *)pb;
				cbT = (UINT)pprop->Value.MVli.cValues * sizeof(LARGE_INTEGER);
				CopyMemory(pb, pprop->Value.MVli.lpli, cbT);
				break;

			case PT_MV_BINARY:
				ppropDst->Value.MVbin.lpbin = (SBinary *) pb;
				cbMV = pprop->Value.MVbin.cValues * sizeof(SBinary);
				pb += cbMV;
				cb += cbMV;
				for (iValue = 0;
				  	(ULONG)iValue < pprop->Value.MVbin.cValues;
					  	iValue++)
				{
					ppropDst->Value.MVbin.lpbin[iValue].lpb = pb;
					cbT = (UINT)pprop->Value.MVbin.lpbin[iValue].cb;
					ppropDst->Value.MVbin.lpbin[iValue].cb = (ULONG)cbT;
					CopyMemory(pb, pprop->Value.MVbin.lpbin[iValue].lpb, cbT);
					cbT = Align(cbT);
					cb += cbT;
					pb += cbT;
				}
				continue;	//	already updated, don't do it again

			case PT_MV_STRING8:
				ppropDst->Value.MVszA.lppszA = (LPSTR *) pb;
				cbMV = pprop->Value.MVszA.cValues * sizeof(LPSTR);
				pb += cbMV;
				cb += cbMV;
				for (iValue = 0;
				  	(ULONG)iValue < pprop->Value.MVszA.cValues;
					  	iValue++)
				{
					ppropDst->Value.MVszA.lppszA[iValue] = (LPSTR)pb;
					cbT = lstrlenA(pprop->Value.MVszA.lppszA[iValue]) + 1;
					CopyMemory(pb, pprop->Value.MVszA.lppszA[iValue], cbT);
					pb += cbT;
					cb += cbT;
				}
				cbT = (UINT)Align(cb);
				pb += cbT - cb;
				cb  = cbT;
				continue;	//	already updated, don't do it again

			case PT_MV_UNICODE:
				ppropDst->Value.MVszW.lppszW = (LPWSTR *) pb;
				cbMV = pprop->Value.MVszW.cValues * sizeof(LPWSTR);
				pb += cbMV;
				cb += cbMV;
				for (iValue = 0;
				  	(ULONG)iValue < pprop->Value.MVszW.cValues;
					  	iValue++)
				{
					ppropDst->Value.MVszW.lppszW[iValue] = (LPWSTR)pb;
					cbT = (lstrlenW(pprop->Value.MVszW.lppszW[iValue]) + 1)
						* sizeof(WCHAR);
					CopyMemory(pb, pprop->Value.MVszW.lppszW[iValue], cbT);
					pb += cbT;
					cb += cbT;
				}
				cbT = (UINT)Align(cb);
				pb += cbT - cb;
				cb  = cbT;
				continue;	//	already updated, don't do it again
		}

		//	Advance pointer and total count by the amount copied
		cbT = Align(cbT);
		pb += cbT;
		cb += cbT;
	}

	if (pcb)
	{
		*pcb = cb;
	}

cleanup:
	RETURN(hr);
}
