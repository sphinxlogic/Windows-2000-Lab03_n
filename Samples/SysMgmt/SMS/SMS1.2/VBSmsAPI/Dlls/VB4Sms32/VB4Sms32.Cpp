//****************************************************************************
//
//  Copyright (c) 1995, Microsoft Corporation
//
//  File:  VB4SMS32.CPP
//
//  Implementation file for the 32-bit Visual Basic interface DLL
//  for SMSAPI.DLL (a Win32 dll)
//
//  History:
//
//      Gary F. Fuehrer, SEA     01 Mar 96    Created.
//
//****************************************************************************

/*********************  Header Files **********************/

#define STRICT
#define WIN32_EXTRA_LEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winnls.h>
#include <ole2.h>
#include <time.h>
#include <string.h>

/****************************************************************************/
#include "smsapi.h"
#include "vb4sms32.h"
typedef void* HLSTR;
typedef USHORT		ERR;		// err

// Default selector limit for 32bit char*
#define MAX_VB_STRING  SMS_DATA_BUFF_SIZE+1


/**************************** Globals ***************************************/
static HANDLE  ghInst = NULL;

// An array of open connections.  This is merely a convenience for the user.
// Any connections made beyond MAX_CONNECTIONS won't be disconnected by WEP.
#define MAX_CONNECTIONS  16
static HANDLE     gahConnections[MAX_CONNECTIONS];

// General use buffer of length SMS_DATA_BUFF_SIZE
static char gStrBuff[SMS_DATA_BUFF_SIZE + 1];

// General use buffer of length SMS_DATA_BUFF_SIZE
static char gNameBuff[SMS_DATA_BUFF_SIZE + 1];

// General use TOKEN buffer
static TOKEN gTokenBuff;

/****************************************************************************/


/********************************************************************\
* Function: int FAR PASCAL LibMain( HINSTANCE, WORD, WORD, LPSTR )   *
*                                                                    *
*  Purpose: DLL entry point                                          *
*                                                                    *
* Comments: Loads the Win32 stub application                         *
*                                                                    *
*                                                                    *
\********************************************************************/

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    int nIndex;

    switch( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH:
        ghInst = hModule;
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        // Disconnect any known open connections
        for (nIndex = 0; nIndex < MAX_CONNECTIONS; nIndex++)
            if (gahConnections[nIndex])
                SmsDataSourceDisconnect(gahConnections[nIndex]);
        break;
    }
    return TRUE;
}

/*********************** Utility Routines and Macros ************************/

BYTE gbANSI = FALSE;
#define VBStringLength(String) ((gbANSI) ? SysStringByteLen(String) \
                                         : SysStringLen(String))

// Copy VB string to an ANSI SZ string
inline SMS_STATUS
CopyString2Sms(char *pszDest, BSTR pszSrc, UINT uLimit = MAX_VB_STRING)
{
    if (uLimit <= 0) return SMS_OK;

    UINT uLen = min(VBStringLength(pszSrc), uLimit-1);
    if (gbANSI)
        strncpy(pszDest, (char*)pszSrc, uLen);
    else WideCharToMultiByte(CP_ACP, 0, pszSrc, uLen, pszDest, uLimit,
                             NULL, NULL);
    pszDest[uLen] = '\0';

    return SMS_OK;
}

// Copy ANSI SZ string to a VB string (freeing the old one)
inline SMS_STATUS
CopyString2VB(BSTR* pBStr, const char *pszSrc, UINT uLimit = MAX_VB_STRING)
{
    UINT uLen = min(strlen(pszSrc), uLimit-1);

    // Allocate a VB string of this length
    BSTR pwsz = NULL;
    if (uLen != 0)
        pwsz = SysAllocStringByteLen(NULL, (gbANSI) ? uLen : uLen << 1);

    if (pwsz != NULL || uLen == 0)
    {
        if (*pBStr != NULL) SysFreeString(*pBStr);
        *pBStr = pwsz;

        if (pwsz == NULL) return SMS_OK;

        if (gbANSI)
            strncpy((char*)pwsz, pszSrc, uLen);
        else MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszSrc, uLen,
                                 pwsz, uLen);

        return SMS_OK;
    }

    return SMS_ERROR;
}


///////////////////////////////////////////////////////////////////////
///////////     The APIs     //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


// ====================================================================
//      Version number API.
// ====================================================================
                                                                        /* VB:
  Declare Function SmsAPIVer& Lib "vb4sms32.dll" (pVersion As String)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsAPIVerVB(BSTR* pbstrVersion)
{
    char      *pszVer32;
    SMS_STATUS ret;

    // Call 32bit SMS API routine
    ret = SmsAPIVer(&pszVer32);

    if (ret == SMS_OK)
        ret = CopyString2VB(pbstrVersion, pszVer32);

    return ret;
}


// ====================================================================
//      Connection APIs.
// ====================================================================
                                                                        /* VB:
  Declare Function SmsDataSourceConnect& Lib "vb4sms32.dll" (pDataSource As SQL_CONNECT_PARAMS, phConn As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsDataSourceConnectVB(SQL_CONNECT_PARAMS *pSqlCP, HANDLE *phConn)
{
    int nIndex;
    DATASOURCE ds;
    SMS_STATUS ret = SMS_ERROR;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to SQL_CONNECT_PARAMS is invalid)
    if (IsBadWritePtr(pSqlCP, sizeof(*pSqlCP)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // See if we can find an availiable connection slot.
    for (nIndex = 0; nIndex < MAX_CONNECTIONS; nIndex++)
        if (!gahConnections[nIndex]) break;

    // Call 32bit SMS API routine
    ds.sqlParams = *pSqlCP;
    ret = SmsDataSourceConnect(&ds, phConn);

    if (ret == SMS_OK && nIndex < MAX_CONNECTIONS)
        gahConnections[nIndex] = *phConn;

    return ret;
}

                                                                        /* VB:
  Declare Function SmsDataSourceDisconnect& Lib "vb4sms32.dll" (ByVal hConn As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsDataSourceDisconnectVB(HANDLE hConn)
{
    int        nIndex;
    SMS_STATUS ret = SMS_ERROR;

    // Try to find the connection in the list of known connections
    for (nIndex = 0; nIndex < MAX_CONNECTIONS; nIndex++)
        if (hConn == gahConnections[nIndex]) break;

    // Call 32bit SMS API routine
    ret = SmsDataSourceDisconnect(hConn);

    if (ret == SMS_OK && nIndex < MAX_CONNECTIONS)
        gahConnections[nIndex] = 0;

    return ret;
}


// ====================================================================
//      Engine APIs.
// ====================================================================

HRESULT
AllocVBArray(SAFEARRAY* &pArray, DWORD cArray, UINT uElemSize)
{

    if (pArray != NULL)
    {
        // See if the array is the right kind
        if (SafeArrayGetElemsize(pArray) != uElemSize) return E_INVALIDARG;

        // See if the array is already large enough
        if (cArray <= pArray->rgsabound[0].cElements) return SMS_OK;

        SAFEARRAYBOUND sab = pArray->rgsabound[0];
        sab.cElements = cArray;
        return SafeArrayRedim(pArray, &sab);
    }
    else
    {
        // Allocate an array descriptor for an array of user defined types
        HRESULT ret = SafeArrayAllocDescriptor(1, &pArray);
        if (ret != S_OK) return ret;

        // Set the element size and array bounds
        pArray->cbElements = uElemSize;
        pArray->rgsabound[0].lLbound = 0;
        pArray->rgsabound[0].cElements = cArray;
        return SafeArrayAllocData(pArray);
    }
}

SMS_STATUS
CopyFolderInfo2VB(FOLDER_INFO *pFolderInfoVB, FOLDER_INFO *pFolderInfo)
{
    SMS_STATUS ret;

    // Preserve the BSTR and SAFEARRAY members in the FOLDER_INFO from VB
    char*           pszTagVB = pFolderInfoVB->pszTag;
    DWORD*          pFolderTagsVB = pFolderInfoVB->pFolderTags;
    DWORD*          pFilterTagsVB = pFolderInfoVB->pFilterTags;
    SCALAR_INFOVB*  pScalarsVB = (SCALAR_INFOVB*)pFolderInfoVB->pScalars;

    // Copy the folder info structure into the VB array
    *pFolderInfoVB = *pFolderInfo;

    // Restore members of FOLDER_INFO before possible exit
    pFolderInfoVB->pszTag = pszTagVB;
    pFolderInfoVB->pFolderTags = pFolderTagsVB;
    pFolderInfoVB->pFilterTags = pFilterTagsVB;
    pFolderInfoVB->pScalars = (SCALAR_INFO*)pScalarsVB;

    // Copy the pszTag member
    ret = CopyString2VB((BSTR*)&pFolderInfoVB->pszTag, pFolderInfo->pszTag);
    if (ret != SMS_OK) return ret;

    // Copy the pFolderTags array
    if (pFolderInfo->ctFolders > 0)
    {
        // Create or Redim as necessary
        if (AllocVBArray((SAFEARRAY*&)pFolderInfoVB->pFolderTags,
                         pFolderInfo->ctFolders,
                         sizeof(*pFolderTagsVB)) != S_OK)
            return SMS_ERROR;

        // Lock down the array and obtain pointer to the data
        if (SafeArrayAccessData((SAFEARRAY*)pFolderInfoVB->pFolderTags,
                                (void**)&pFolderTagsVB) != S_OK)
            return SMS_ERROR;

        // Copy the array and unlock it
        memcpy(pFolderTagsVB, pFolderInfo->pFolderTags,
               pFolderInfo->ctFolders * sizeof(*pFolderTagsVB));
        SafeArrayUnaccessData((SAFEARRAY*)pFolderInfoVB->pFolderTags);
    }

    // Copy the pFilterTags array
    if (pFolderInfo->ctFilters > 0)
    {
        // Create or Redim as necessary
        if (AllocVBArray((SAFEARRAY*&)pFolderInfoVB->pFilterTags,
                         pFolderInfo->ctFilters,
                         sizeof(*pFilterTagsVB)) != S_OK)
            return SMS_ERROR;

        // Lock down the array and obtain pointer to the data
        if (SafeArrayAccessData((SAFEARRAY*)pFolderInfoVB->pFilterTags,
                                (void**)&pFilterTagsVB) != S_OK)
            return SMS_ERROR;

        // Copy the array and unlock it
        memcpy(pFilterTagsVB, pFolderInfo->pFilterTags,
               pFolderInfo->ctFilters * sizeof(*pFilterTagsVB));
        SafeArrayUnaccessData((SAFEARRAY*)pFolderInfoVB->pFilterTags);
    }

    // Copy the pScalars array
    if (pFolderInfo->ctScalars > 0)
    {
        // Create or Redim as necessary
        if (AllocVBArray((SAFEARRAY*&)pFolderInfoVB->pScalars,
                         pFolderInfo->ctScalars,
                         sizeof(*pScalarsVB)) != S_OK) return SMS_ERROR;

        // Lock down the array and obtain pointer to the data
        if (SafeArrayAccessData((SAFEARRAY*)pFolderInfoVB->pScalars,
                                (void**)&pScalarsVB) != S_OK) return SMS_ERROR;

        // Copy the array and unlock it
        DWORD dwIndex = pFolderInfo->ctScalars;
        SCALAR_INFO* pScalars = pFolderInfo->pScalars;
        while (dwIndex-- > 0)
        {
            pScalarsVB->scType = pScalars->scType;
            pScalars->fAccess = pScalars->fAccess;
            ret = CopyString2VB(&pScalarsVB->szName, pScalars->szName);
            if (ret != SMS_OK) break;

            // Advance to next scalar
            pScalarsVB++;
            pScalars++;
        }
        SafeArrayUnaccessData((SAFEARRAY*)pFolderInfoVB->pScalars);
    }

    return ret;
}

                                                                        /* VB:
  Declare Function SmsDescribeFolder& Lib "vb4sms32.dll" (tObjectity As BASETYPE, ByVal dwTag As Long, pFolderInfo As FOLDER_INFO)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsDescribeFolderVB(BASETYPE* tObjectity, DWORD dwTag,
                    LPSAFEARRAY* ppArray)
{
    SAFEARRAY* &pArray = *ppArray;
    SMS_STATUS   ret;

    // Create or Redim as necessary
    FOLDER_INFO* pFoldersVB;
    if (AllocVBArray(pArray, 1, sizeof(*pFoldersVB)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pFoldersVB) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Call 32bit SMS API routine
    FOLDER_INFO *pFolderInfo;
    ret = SmsDescribeFolder(*tObjectity, dwTag, &pFolderInfo);
    if (ret == SMS_OK)
        // Copy the FOLDER_INFO struct from 32bit land
        ret = CopyFolderInfo2VB(pFoldersVB, pFolderInfo);

    // Unlock the VB array
    SafeArrayUnaccessData(pArray);
    return ret;
}


typedef SMS_STATUS (*ENUM_FN)(FOLDER_INFO**, DWORD*);

SMS_STATUS
SmsEnumFoldersContainers(LPSAFEARRAY* ppArray, DWORD *pCount, ENUM_FN SmsEnum)
{
    SAFEARRAY* &pArray = *ppArray;
    FOLDER_INFO* pFoldersVB;
    SMS_STATUS  ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (pCount is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    // if (Count is too big)
    if (*pCount >= 0x80000000 / sizeof(*pFoldersVB))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Get the count of FOLDER_INFOs
    *pCount = 0;
    ret = SmsEnum(NULL, pCount);
    if (ret != SMS_MORE_DATA) return ret;

    // Create or Redim as necessary
    if (AllocVBArray(pArray, *pCount, sizeof(*pFoldersVB)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pFoldersVB) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Get an array large enough to accept FOLDER_INFO pointers
    DWORD cFolders = *pCount;
    FOLDER_INFO** ppFolders = new FOLDER_INFO*[cFolders];
    if (ppFolders != NULL)
    {
        // Call 32bit SMS API routine
        ret = SmsEnum(ppFolders, pCount);

        if (ret == SMS_OK)
            for (DWORD dwIndex = 0; dwIndex < cFolders; dwIndex++)
            {
                ret = CopyFolderInfo2VB(&pFoldersVB[dwIndex],
                                        ppFolders[dwIndex]);
                if (ret != SMS_OK) break;
            }

        // Free the array of FOLDER_INFO pointers
        delete[] ppFolders;
        ppFolders = NULL;
    }
    else ret = SMS_ERROR;

    // Unlock the VB array of FOLDER_INFOs
    SafeArrayUnaccessData(pArray);
    return ret;
}

                                                                        /* VB:
  Declare Function SmsEnumContainers& Lib "vb4sms32.dll" (Containers() As FOLDER_INFO, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsEnumContainersVB(LPSAFEARRAY* ppArray, DWORD *pCount)
{
    return SmsEnumFoldersContainers(ppArray, pCount, SmsEnumContainers);
}

                                                                        /* VB:
  Declare Function SmsEnumFolders& Lib "vb4sms32.dll" (Folders() As FOLDER_INFO, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsEnumFoldersVB(LPSAFEARRAY* ppArray, DWORD *pCount)
{
    return SmsEnumFoldersContainers(ppArray, pCount, SmsEnumFolders);
}

SMS_STATUS
CopyFilterInfo2VB(FILTER_INFOVB *pFilterInfoVB, FILTER_INFO *pFilterInfo)
{
    SMS_STATUS ret = SMS_OK;

    // szTag
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szTag,
                            pFilterInfo->szTag,
                            sizeof(pFilterInfo->szTag));

    // filterType
    pFilterInfoVB->filterType = pFilterInfo->filterType;

    // szName
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szName,
                            pFilterInfo->szName,
                            sizeof(pFilterInfo->szName));

    // szValue
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szValue,
                            pFilterInfo->szValue,
                            sizeof(pFilterInfo->szValue));

    // szOperator
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szOperator,
                            pFilterInfo->szOperator,
                            sizeof(pFilterInfo->szOperator));
    
    // szArchitecture
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szArchitecture,
                            pFilterInfo->szArchitecture,
                            sizeof(pFilterInfo->szArchitecture));

    // szGroupClass
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szGroupClass,
                            pFilterInfo->szGroupClass,
                            sizeof(pFilterInfo->szGroupClass));

    // szAttributeName
    if (ret == SMS_OK)
        ret = CopyString2VB(&pFilterInfoVB->szAttributeName,
                            pFilterInfo->szAttributeName,
                            sizeof(pFilterInfo->szAttributeName));

    return ret;
}

                                                                        /* VB:
  Declare Function SmsEnumFilters& Lib "vb4sms32.dll" (Filters() As FILTER_INFO, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsEnumFiltersVB(LPSAFEARRAY* ppArray, DWORD *pCount)
{
    SAFEARRAY* &pArray = *ppArray;
    FILTER_INFOVB* pFiltersVB;
    SMS_STATUS  ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (pCount is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    // if (Count is too big)
    if (*pCount >= 0x80000000 / sizeof(*pFiltersVB))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Get the count of FILTER_INFOs
    *pCount = 0;
    ret = SmsEnumFilters(NULL, pCount);
    if (ret != SMS_MORE_DATA) return ret;

    // Create or Redim as necessary
    if (AllocVBArray(pArray, *pCount, sizeof(*pFiltersVB)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pFiltersVB) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Get an array large enough to accept FILTER_INFO pointers
    DWORD cFilters = *pCount;
    FILTER_INFO* pFilters = new FILTER_INFO[cFilters];
    if (pFilters != NULL)
    {
        // Call 32bit SMS API routine
        ret = SmsEnumFilters(pFilters, pCount);

        if (ret == SMS_OK)
            for (DWORD dwIndex = 0; dwIndex < cFilters; dwIndex++)
            {
                ret = CopyFilterInfo2VB(&pFiltersVB[dwIndex],
                                        &pFilters[dwIndex]);
                if (ret != SMS_OK) break;
            }

        // Unlock the array of FILTER_INFO pointers
        delete[] pFilters;
        pFilters = NULL;
    }
    else ret = SMS_ERROR;

    // Unlock the VB array of FILTER_INFOs
    SafeArrayUnaccessData(pArray);
    return ret;
}


// ====================================================================
//      Container APIS.
// ====================================================================
                                                                        /* VB:
  Declare Function SmsOpenContainer& Lib "vb4sms32.dll" (ByVal cType As Long, ByVal hConnection As Long, phContainer As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsOpenContainerVB(DWORD cType, HANDLE hConnection, HANDLE *phContainer)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Container Handle from VB is invalid)
    if (IsBadWritePtr((void*)phContainer, sizeof(*phContainer)))
        return SMS_INVALID_PARAMETER;
    
    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsOpenContainer(cType, hConnection, phContainer);
}

                                                                        /* VB:
  Declare Function SmsSetFilter& Lib "vb4sms32.dll" (ByVal hContainer As Long, ByVal hFilter As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsSetFilterVB(HANDLE hContainer, HANDLE hFilter)
{
    // Call 32bit SMS API routine
    return SmsSetFilter(hContainer, hFilter);
}

                                                                        /* VB:
  Declare Function SmsPopulate& Lib "vb4sms32.dll" (ByVal hContainer As Long, ByVal dwOptions As Long, pNotify As Any)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsPopulateVB(HANDLE hContainer, DWORD dwOptions, NOTIFY* pNotify)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Folder Handle from VB is invalid)
    if (dwOptions != POP_SYNC 
                           && IsBadWritePtr((void*)pNotify, sizeof(*pNotify)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsPopulate(hContainer, dwOptions, pNotify);
}

                                                                        /* VB:
  Declare Function SmsGetNextFolder& Lib "vb4sms32.dll" (ByVal hParent As Long, ByVal fType As Long, phFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetNextFolderVB(HANDLE hParent, DWORD fType, HANDLE *phFolder)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Folder Handle from VB is invalid)
    if (IsBadWritePtr((void*)phFolder, sizeof(*phFolder)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsGetNextFolder(hParent, fType, phFolder);
}

                                                                        /* VB:
  Declare Function SmsCloseContainer& Lib "vb4sms32.dll" (ByVal hContainer As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCloseContainerVB(HANDLE hContainer)
{
    // Call 32bit SMS API routine
    return SmsCloseContainer(hContainer);
}


// ====================================================================
//  Folder (collection) APIs.
//  A collection contains other things, that is it can have embedded
//  collections and it can also have properties (scalars).
// ====================================================================
                                                                        /* VB:
  Declare Function SmsCreateFolder& Lib "vb4sms32.dll" (ByVal hParent As Long, ByVal fType As Long, ByVal pszFolderID As String, phFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCreateFolderVB(HANDLE hParent, DWORD fType, const char *pszFolderID,
                  HANDLE *phFolder)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to string from VB is invalid)
    if (IsBadStringPtr(pszFolderID, MAX_VB_STRING))
        return SMS_INVALID_PARAMETER;

    // if (Pointer to Folder Handle from VB is invalid)
    if (IsBadWritePtr((void*)phFolder, sizeof(*phFolder)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsCreateFolder(hParent, fType, pszFolderID, phFolder);
}

                                                                        /* VB:
  Declare Function SmsGetFolderID& Lib "vb4sms32.dll" (ByVal hFolder As Long, pszFolderID As String)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFolderIDVB(HANDLE hFolder, BSTR* pszFolderID)
{
    SMS_STATUS ret;

    // Call 32bit SMS API routine
    ret = SmsGetFolderID(hFolder, gStrBuff);
    if (ret == SMS_OK)
        // Copy the string to VB land
        ret = CopyString2VB(pszFolderID, gStrBuff, sizeof(gStrBuff));

    return ret;
}
                                                                        /* VB:
  Declare Function SmsGetFolderType& Lib "vb4sms32.dll" (ByVal hFolder As Long, pfType As Long, pszfType As String)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFolderTypeVB(HANDLE hFolder, DWORD *pfType, BSTR* pszfType)
{
    SMS_STATUS ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Type from VB is invalid)
    if (IsBadWritePtr(pfType, sizeof(*pfType)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    ret = SmsGetFolderType(hFolder, pfType, gStrBuff);
    if (ret == SMS_OK)
        // Copy the string to VB land
        ret = CopyString2VB(pszfType, gStrBuff, sizeof(gStrBuff));

    return ret;
}

                                                                        /* VB:
  Declare Function SmsEnumFolderTypes& Lib "vb4sms32.dll" (ByVal hFolder As Long, pfTypes As Long, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsEnumFolderTypesVB(HANDLE hFolder, LPSAFEARRAY* ppArray, DWORD *pCount)
{
    SAFEARRAY* &pArray = *ppArray;
    DWORD* pfTypes;
    SMS_STATUS  ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Folder Type Count from VB is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    // if (Count is too big)
    if (*pCount >= 0x80000000 / sizeof(*pfTypes))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Get the count of folder types
    *pCount = 0;
    ret = SmsEnumFolderTypes(hFolder, NULL, pCount);
    if (ret != SMS_MORE_DATA) return ret;

    // Create or Redim as necessary
    if (AllocVBArray(pArray, *pCount, sizeof(*pfTypes)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pfTypes) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Call 32bit SMS API routine
    ret = SmsEnumFolderTypes(hFolder, pfTypes, pCount);

    // Unlock the array
    SafeArrayUnaccessData(pArray);

    return ret;
}

                                                                        /* VB:
  Declare Function SmsGetFolderCount& Lib "vb4sms32.dll" (ByVal hFolder As Long, ByVal fType As Long, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFolderCountVB(HANDLE hFolder, DWORD fType, DWORD *pCount)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Folder Type Count from VB is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsGetFolderCount(hFolder, fType, pCount);
}

                                                                        /* VB:
  Declare Function SmsGetFolderByID& Lib "vb4sms32.dll" (ByVal hFolder As Long, ByVal fType As Long, ByVal pszFolderID As String, phSubFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFolderByIDVB(HANDLE hFolder, DWORD fType, const char *pszFolderID,
                   HANDLE *phSubFolder)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to string from VB is invalid)
    if (IsBadStringPtr(pszFolderID, MAX_VB_STRING))
        return SMS_INVALID_PARAMETER;

    // if (Pointer to SubFolder Handle from VB is invalid)
    if (IsBadWritePtr((void*)phSubFolder, sizeof(*phSubFolder)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    char *pTemp = const_cast<char*>(pszFolderID);  // FIX: SMSAPI incorrectly declared 3rd parameter
    return SmsGetFolderByID(hFolder, fType, pTemp, phSubFolder);
}

                                                                        /* VB:
  Declare Function SmsRewind& Lib "vb4sms32.dll" (ByVal hFolder As Long, ByVal dwOptions As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsRewindVB(HANDLE hFolder, DWORD dwOptions)
{
    // Call 32bit SMS API routine
    return SmsRewind(hFolder, dwOptions);
}

                                                                        /* VB:
  Declare Function SmsCloseFolder& Lib "vb4sms32.dll" (ByVal hFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCloseFolderVB(HANDLE hFolder)
{
    // Call 32bit SMS API routine
    return SmsCloseFolder(hFolder);
}

                                                                        /* VB:
  Declare Function SmsLinkFolder& Lib "vb4sms32.dll" (ByVal hFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsLinkFolderVB(HANDLE hFolder)
{
    // Call 32bit SMS API routine
    return SmsLinkFolder(hFolder);
}

                                                                        /* VB:
  Declare Function SmsUnlinkFolder& Lib "vb4sms32.dll" (ByVal hFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsUnlinkFolderVB(HANDLE hFolder)
{
    // Call 32bit SMS API routine
    return SmsUnlinkFolder(hFolder);
}

                                                                        /* VB:
  Declare Function SmsCommitFolder& Lib "vb4sms32.dll" (ByVal hFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCommitFolderVB(HANDLE hFolder)
{
    // Call 32bit SMS API routine
    return SmsCommitFolder(hFolder);
}

                                                                        /* VB:
  Declare Function SmsDupFolder& Lib "vb4sms32.dll" (ByVal hParent As Long, ByVal hFolder As Long, phNewFolder As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsDupFolderVB(HANDLE hParent, HANDLE hFolder, HANDLE* phNewFolder)
{
    // Call 32bit SMS API routine
    return SmsDupFolder(hParent, hFolder, phNewFolder);
}

                                                                        /* VB:
  Declare Function SmsGetScalarCount& Lib "vb4sms32.dll" (ByVal hFolder As Long, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetScalarCountVB(HANDLE hFolder, DWORD *pCount)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Folder Count from VB is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsGetScalarCount(hFolder, pCount);
}

                                                                        /* VB:
  Declare Function SmsGetNextScalar& Lib "vb4sms32.dll" (ByVal hFolder As Long, pScalarStruct As SCALAR)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetNextScalarVB(HANDLE hFolder, LPSAFEARRAY* ppArray)
{
    SMS_STATUS ret;
    char *pszName;
    BSTR pszValue;
    SAFEARRAY* pValue;
    SAFEARRAY* &pArray = *ppArray;

    // Create or Redim as necessary
    SCALAR *pScalar;
    if (AllocVBArray(pArray, 1, sizeof(*pScalar)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pScalar) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Preserve the BSTR members, pszName & pszValue, in the SCALAR from VB
    pszName = pScalar->pszName;
    pszValue = (BSTR)pScalar->pszValue;
    pValue = (SAFEARRAY*)pScalar->pValue;

    // Provide SCALAR with buffers to receive data
    pScalar->pszName = gNameBuff;
    pScalar->pszValue = NULL;
    pScalar->pValue = NULL;
    pScalar->dwLen = 0;

    // Call 32bit SMS API routine to get buffer lengths
    ret = SmsGetNextScalar(hFolder, pScalar);

    // Check for BINARY scalar and wrong return code
    if (ret == SMS_OK && pScalar->scType == SCALAR_BINARY &&
        pScalar->dwLen > 0)
        ret = SMS_MORE_DATA;

    if (ret == SMS_MORE_DATA)
    {
        // Provide SCALAR with buffers to receive data
        if (pScalar->scType == SCALAR_STRING)
        {
            pScalar->pszValue = new char[pScalar->dwLen];
            if (pScalar->pszValue == NULL) ret = SMS_ERROR;
        }
        else if (pScalar->scType == SCALAR_BINARY)
        {
            // Create or Redim as necessary
            if (AllocVBArray(pValue, pScalar->dwLen, 1) != S_OK)
                ret = SMS_INVALID_PARAMETER;

            // Lock down the array and obtain pointer to the data
            else if (SafeArrayAccessData(pValue, &pScalar->pValue) != S_OK)
                ret = SMS_INVALID_PARAMETER;
        }
        else ret = SMS_ERROR;

        if (ret == SMS_MORE_DATA)
        {
            // Call 32bit SMS API routine to get data
            ret = SmsGetScalarByName(hFolder, pScalar->pszName, pScalar);

            // Copy string buffer to pszValue
            if (ret == SMS_OK && pScalar->pszValue != NULL)
            {
                ret = CopyString2VB(&pszValue, pScalar->pszValue);

                // Free the string buffer
                delete[] pScalar->pszValue;
            }

            // Unlock the VB Byte array
            if (pScalar->pValue != NULL)
                SafeArrayUnaccessData(pValue);
        }
    }

    // Restore pszName & pszValue members of SCALAR before possible exit
    pScalar->pszName = pszName;
    pScalar->pszValue = (char*)pszValue;
    pScalar->pValue = pValue;

    // Copy the name from buffer to VB BSTR
    if (ret == SMS_OK)
        ret = CopyString2VB((BSTR*)&pScalar->pszName, gNameBuff);

    // Unlock the VB array
    SafeArrayUnaccessData(pArray);

    return ret;
}

                                                                        /* VB:
  Declare Function SmsGetScalarByName& Lib "vb4sms32.dll" (ByVal hFolder As Long, ByVal pszName As String, pScalarStruct As SCALAR)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetScalarByNameVB(HANDLE hFolder, const char *pszNameVB,
                     LPSAFEARRAY* ppArray)
{
    SMS_STATUS ret;
    char *pszName;
    BSTR pszValue;
    SAFEARRAY* pValue;
    SAFEARRAY* &pArray = *ppArray;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to string from VB is invalid)
    if (IsBadStringPtr(pszNameVB, MAX_VB_STRING))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Create or Redim as necessary
    SCALAR *pScalar;
    if (AllocVBArray(pArray, 1, sizeof(*pScalar)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pScalar) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Preserve the BSTR members, pszName & pszValue, in the SCALAR from VB
    pszName = pScalar->pszName;
    pszValue = (BSTR)pScalar->pszValue;
    pValue = (SAFEARRAY*)pScalar->pValue;

    // Provide SCALAR with buffers to receive data
    pScalar->pszName = gNameBuff;
    pScalar->pszValue = NULL;
    pScalar->pValue = NULL;
    pScalar->dwLen = 0;

    // Call 32bit SMS API routine to get buffer lengths
    ret = SmsGetScalarByName(hFolder, pszNameVB, pScalar);

    // Check for BINARY scalar and wrong return code
    if (ret == SMS_OK && pScalar->scType == SCALAR_BINARY &&
        pScalar->dwLen > 0)
        ret = SMS_MORE_DATA;

    if (ret == SMS_MORE_DATA ||
        (pScalar->scType == SCALAR_BINARY) && pScalar->dwLen > 0)
    {
        // Provide SCALAR with buffers to receive data
        if (pScalar->scType == SCALAR_STRING)
        {
            pScalar->pszValue = new char[pScalar->dwLen];
            if (pScalar->pszValue == NULL) ret = SMS_ERROR;
        }
        else if (pScalar->scType == SCALAR_BINARY)
        {
            // Create or Redim as necessary
            if (AllocVBArray(pValue, pScalar->dwLen, 1) != S_OK)
                ret = SMS_INVALID_PARAMETER;

            // Lock down the array and obtain pointer to the data
            else if (SafeArrayAccessData(pValue, &pScalar->pValue) != S_OK)
                ret = SMS_INVALID_PARAMETER;
        }
        else ret = SMS_ERROR;

        if (ret == SMS_MORE_DATA)
        {
            // Call 32bit SMS API routine to get data
            ret = SmsGetScalarByName(hFolder, pszNameVB, pScalar);

            // Copy string buffer to pszValue
            if (ret == SMS_OK && pScalar->pszValue != NULL)
            {
                ret = CopyString2VB(&pszValue, pScalar->pszValue);

                // Free the string buffer
                delete[] pScalar->pszValue;
            }

            // Unlock the VB Byte array
            if (pScalar->pValue != NULL)
                SafeArrayUnaccessData(pValue);
        }
    }

    // Restore pszTag & pszValue members of SCALAR before possible exit
    pScalar->pszName = pszName;
    pScalar->pszValue = (char*)pszValue;
    pScalar->pValue = pValue;

    // Copy the name from buffer to VB BSTR
    if (ret == SMS_OK)
        ret = CopyString2VB((BSTR*)&pScalar->pszName, gNameBuff);

    // Unlock the VB array
    SafeArrayUnaccessData(pArray);

    return ret;
}

                                                                        /* VB:
  Declare Function SmsSetScalar& Lib "vb4sms32.dll" (ByVal hFolder As Long, pScalarStruct As SCALAR)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsSetScalarVB(HANDLE hFolder, LPSAFEARRAY* ppArray)
{
    BSTR pszName, pszValue;
    SAFEARRAY* pValue;
    SAFEARRAY* &pArray = *ppArray;
    char NullCharBuff = '\0', *pCharBuff = &NullCharBuff;
    BYTE NullByteBuff = NULL, *pByteBuff = &NullByteBuff;

    // Lock down the array and obtain pointer to the data
    SCALAR *pScalar;
    if (SafeArrayAccessData(pArray, (void**)&pScalar) != S_OK)
        return SMS_INVALID_PARAMETER;

    if (pScalar->scType == SCALAR_STRING && pScalar->pszValue == NULL &&
        pScalar->dwLen > 0) return SMS_INVALID_PARAMETER;

    if (pScalar->scType == SCALAR_BINARY && pScalar->pValue == NULL)
        if (pScalar->dwLen > 0) return SMS_INVALID_PARAMETER;

    // Preserve the BSTR members, pszName & pszValue, in the SCALAR from VB
    pszName = (BSTR)pScalar->pszName;
    pszValue = (BSTR)pScalar->pszValue;
    pValue = (SAFEARRAY*)pScalar->pValue;

    // Get a value string buffer
    if (pScalar->scType == SCALAR_STRING && pszValue != NULL &&
        (pCharBuff = new char[VBStringLength(pszValue) + 1]) == NULL)
        return SMS_ERROR;

    // Lock down the array and obtain pointer to the byte data
    if (pScalar->scType == SCALAR_BINARY && pValue != NULL &&
        SafeArrayAccessData(pValue, (void**)&pByteBuff) != S_OK)
        return SMS_ERROR;

    // Copy the strings from VB to SMS
    CopyString2Sms(gNameBuff, pszName);
    if (pCharBuff != NULL) CopyString2Sms(pCharBuff, pszValue);

    // Set SCALAR value to buffers with data
    pScalar->pszName = gNameBuff;
    pScalar->pszValue = pCharBuff;
    pScalar->pValue = pByteBuff;

    // Call 32bit SMS API routine
    SMS_STATUS ret = SmsSetScalar(hFolder, pScalar);

    // Restore pszTag, pszValue, & pValue members of SCALAR before exit
    pScalar->pszName = (char*)pszName;
    pScalar->pszValue = (char*)pszValue;
    pScalar->pValue = pValue;

    // Unlock the array and delete the string value buffer
    if (pByteBuff != &NullByteBuff) SafeArrayUnaccessData(pValue);
    if (pCharBuff != &NullCharBuff) delete[] pCharBuff;

    // Unlock the VB array
    SafeArrayUnaccessData(pArray);

    return ret;
}


// ====================================================================
//  FilterContainer APIs
// ====================================================================
                                                                        /* VB:
  Declare Function SmsOpenFilterContainer& Lib "vb4sms32.dll" (ByVal hConnection As Long, phFContainer As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsOpenFilterContainerVB(HANDLE hConnection, HANDLE *phFContainer)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Container Handle from VB is invalid)
    if (IsBadWritePtr((void*)phFContainer, sizeof(*phFContainer)))
        return SMS_INVALID_PARAMETER;
    
    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsOpenFilterContainer(hConnection, phFContainer);
}

                                                                        /* VB:
  Declare Function SmsCloseFilterContainer& Lib "vb4sms32.dll" (ByVal hFContainer As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCloseFilterContainerVB(HANDLE hFContainer)
{
    // Call 32bit SMS API routine
    return SmsCloseFilterContainer(hFContainer);
}

                                                                        /* VB:
  Declare Function SmsGetNextFilter& Lib "vb4sms32.dll" (ByVal hFContainer As Long, ByVal frType As Long, phFilter As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetNextFilterVB(HANDLE hFContainer, DWORD frType, HANDLE *phFilter)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Filter Handle from VB is invalid)
    if (IsBadWritePtr((void*)phFilter, sizeof(*phFilter)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsGetNextFilter(hFContainer, frType, phFilter);
}

                                                                        /* VB:
  Declare Function SmsGetFilterByID& Lib "vb4sms32.dll" (ByVal hFContainer As Long, ByVal frType As Long, ByVal pszFilterID As String, phFilter As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFilterByIDVB(HANDLE hFContainer, DWORD frType, const char *pszFilterID,
                   HANDLE *phFilter)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to string from VB is invalid)
    if (IsBadStringPtr(pszFilterID, MAX_VB_STRING))
        return SMS_INVALID_PARAMETER;

    // if (Pointer to Filter Handle from VB is invalid)
    if (IsBadWritePtr((void*)phFilter, sizeof(*phFilter)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsGetFilterByID(hFContainer, frType, pszFilterID, phFilter);
}

                                                                        /* VB:
  Declare Function SmsGetFilterID& Lib "vb4sms32.dll" (ByVal hFilter As Long, pszFilterID As String)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFilterIDVB(HANDLE hFilter, BSTR* pszFilterID)
{
    SMS_STATUS ret;

    // Call 32bit SMS API routine
    ret = SmsGetFilterID(hFilter, gStrBuff);
    if (ret == SMS_OK)
        ret = CopyString2VB(pszFilterID, gStrBuff, sizeof(gStrBuff));

    return ret;
}

                                                                        /* VB:
  Declare Function SmsCommitFilter& Lib "vb4sms32.dll" (ByVal hFilter As Long, ByVal hFContainer As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCommitFilterVB(HANDLE hFilter, HANDLE hFContainer)
{
    // Call 32bit SMS API routine
    return SmsCommitFilter(hFilter, hFContainer);
}


// ====================================================================
//  Filter APIs
// ====================================================================
                                                                        /* VB:
  Declare Function SmsCreateFilter& Lib "vb4sms32.dll" (ByVal frType As Long, ByVal hConnection As Long, phFilter As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCreateFilterVB(DWORD frType, HANDLE hConnection, HANDLE *phFilter)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Filter Handle from VB is invalid)
    if (IsBadWritePtr((void*)phFilter, sizeof(*phFilter)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsCreateFilter(frType, hConnection, phFilter);
}

                                                                        /* VB:
  Declare Function SmsCloseFilter& Lib "vb4sms32.dll" (ByVal hFilter As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsCloseFilterVB(HANDLE hFilter)
{
    // Call 32bit SMS API routine
    return SmsCloseFilter(hFilter);
}

                                                                        /* VB:
  Declare Function SmsGetFilterType& Lib "vb4sms32.dll" (ByVal hFilter As Long, pfilterType As Long, pszTag As String)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetFilterTypeVB(HANDLE hFilter, DWORD *pfilterType, BSTR* pszTag)
{
    SMS_STATUS ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Filter Handle from VB is invalid)
    if (IsBadWritePtr(pfilterType, sizeof(*pfilterType)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    ret = SmsGetFilterType(hFilter, pfilterType, gStrBuff);
    if (ret == SMS_OK)
        ret = CopyString2VB(pszTag, gStrBuff, sizeof(gStrBuff));

    return ret;
}

                                                                        /* VB:
  Declare Function SmsGetToken& Lib "vb4sms32.dll" (ByVal hFilter As Long, ByVal iIndex As Long, pTokenInfo As TOKEN)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetTokenVB(HANDLE hFilter, INT iIndex, TOKENVB *pTokenInfoVB)
{
    SMS_STATUS ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to FOLDER_INFO struct from VB is invalid)
    if (IsBadWritePtr(pTokenInfoVB, sizeof(*pTokenInfoVB)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Turn on ANSI string copy
    gbANSI = TRUE;

    // Call 32bit SMS API routine
    ret = SmsGetToken(hFilter, iIndex, &gTokenBuff);

    // tokenType
    pTokenInfoVB->tokenType = gTokenBuff.tokenType;

    // szName
    if (ret == SMS_OK)
        ret = CopyString2VB(&pTokenInfoVB->szName,
                            gTokenBuff.szName,
                            sizeof(gTokenBuff.szName));

    // szValue
    if (ret == SMS_OK)
        ret = CopyString2VB(&pTokenInfoVB->szValue,
                            gTokenBuff.szValue,
                            sizeof(gTokenBuff.szValue));

    // dwOp
    pTokenInfoVB->dwOp = gTokenBuff.dwOp;

    // szArchitecture
    if (ret == SMS_OK)
        ret = CopyString2VB(&pTokenInfoVB->szArchitecture,
                            gTokenBuff.szArchitecture,
                            sizeof(gTokenBuff.szArchitecture));

    // szGroupClass
    if (ret == SMS_OK)
        ret = CopyString2VB(&pTokenInfoVB->szGroupClass,
                            gTokenBuff.szGroupClass,
                            sizeof(gTokenBuff.szGroupClass));

    // szAttributeName
    if (ret == SMS_OK)
        ret = CopyString2VB(&pTokenInfoVB->szAttributeName,
                            gTokenBuff.szAttributeName,
                            sizeof(gTokenBuff.szAttributeName));

    // szTokenString
    if (ret == SMS_OK)
        ret = CopyString2VB(&pTokenInfoVB->szTokenString,
                            gTokenBuff.szTokenString,
                            sizeof(gTokenBuff.szTokenString));

    // bIndent
    pTokenInfoVB->bIndent = gTokenBuff.bIndent;

    gbANSI = FALSE;
    return ret;
}
                                                                        /* VB:
  Declare Function SmsAddToken& Lib "vb4sms32.dll" (ByVal hFilter As Long, opAndOr As ANDOR, pTokenInfo As TOKEN, ByVal iIndex As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsAddTokenVB(HANDLE hFilter, ANDOR* opAndOr, TOKENVB *pTokenInfoVB, INT iIndex)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to TOKENVB struct from VB is invalid)
    if (IsBadReadPtr(pTokenInfoVB, sizeof(*pTokenInfoVB)))
        return SMS_INVALID_PARAMETER;

    if (VBStringLength(pTokenInfoVB->szName) >= sizeof(gTokenBuff.szName))
        return SMS_INVALID_PARAMETER;

    if (VBStringLength(pTokenInfoVB->szValue) >= sizeof(gTokenBuff.szValue))
        return SMS_INVALID_PARAMETER;

    if (VBStringLength(pTokenInfoVB->szArchitecture)
                                         >= sizeof(gTokenBuff.szArchitecture))
        return SMS_INVALID_PARAMETER;

    if (VBStringLength(pTokenInfoVB->szGroupClass)
                                           >= sizeof(gTokenBuff.szGroupClass))
        return SMS_INVALID_PARAMETER;

    if (VBStringLength(pTokenInfoVB->szAttributeName)
                                        >= sizeof(gTokenBuff.szAttributeName))
        return SMS_INVALID_PARAMETER;

    if (VBStringLength(pTokenInfoVB->szTokenString) 
                                          >= sizeof(gTokenBuff.szTokenString))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Turn on ANSI string copy
    gbANSI = TRUE;

    // tokenType
    gTokenBuff.tokenType = pTokenInfoVB->tokenType;

    // szName
    CopyString2Sms(gTokenBuff.szName, pTokenInfoVB->szName,
                   sizeof(gTokenBuff.szName));

    // szValue
    CopyString2Sms(gTokenBuff.szValue, pTokenInfoVB->szValue,
                   sizeof(gTokenBuff.szValue));

    // dwOp
    gTokenBuff.dwOp = pTokenInfoVB->dwOp;

    // szArchitecture
    CopyString2Sms(gTokenBuff.szArchitecture, pTokenInfoVB->szArchitecture,
                   sizeof(gTokenBuff.szArchitecture));

    // szGroupClass
    CopyString2Sms(gTokenBuff.szGroupClass, pTokenInfoVB->szGroupClass,
                   sizeof(gTokenBuff.szGroupClass));

    // szAttributeName
    CopyString2Sms(gTokenBuff.szAttributeName, pTokenInfoVB->szAttributeName,
                   sizeof(gTokenBuff.szAttributeName));

    // szTokenString
    CopyString2Sms(gTokenBuff.szTokenString, pTokenInfoVB->szTokenString,
                   sizeof(gTokenBuff.szTokenString));

    // bIndent
    gTokenBuff.bIndent = pTokenInfoVB->bIndent;

    // Turn back off ANSI copy
    gbANSI = FALSE;

    // Call 32bit SMS API routine
    return SmsAddToken(hFilter, *opAndOr, &gTokenBuff, iIndex);
}

                                                                        /* VB:
  Declare Function SmsGetTokenCount& Lib "vb4sms32.dll" (ByVal hFilter As Long, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetTokenCountVB(HANDLE hFilter, DWORD *pCount)
{
    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Filter Handle from VB is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Call 32bit SMS API routine
    return SmsGetTokenCount(hFilter, pCount);
}

                                                                        /* VB:
  Declare Function SmsManipulateTokens& Lib "vb4sms32.dll" (ByVal hFilter As Long, ByVal dwFlags As Long, ByVal iStart As Long, ByVal iEnd As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsManipulateTokensVB(HANDLE hFilter, DWORD dwFlags, INT iStart, INT iEnd)
{
    // Call 32bit SMS API routine
    return SmsManipulateTokens(hFilter, dwFlags, iStart, iEnd);
}

                                                                        /* VB:
  Declare Function SmsGetAllFilters& Lib "vb4sms32.dll" (ByVal hContainer As Long, pahFilters As Long, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsGetAllFiltersVB(HANDLE hContainer, LPSAFEARRAY* ppArray, DWORD *pCount)
{
    SMS_STATUS ret;
    HANDLE *pahFilters;
    SAFEARRAY* &pArray = *ppArray;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (Pointer to Count from VB is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    // if (Count is too big)
    if (*pCount >= 0x80000000 / sizeof(*pahFilters))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Get the count of FILTER_INFOs
    *pCount = 0;
    ret = SmsGetAllFilters(hContainer, NULL, pCount);
    if (ret != SMS_MORE_DATA) return ret;

    // Create or Redim as necessary
    if (AllocVBArray(pArray, *pCount, sizeof(*pahFilters)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&pahFilters) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Call 32bit SMS API routine
    ret = SmsGetAllFilters(hContainer, pahFilters, pCount);

    // Unlock the VB array of FILTER_INFOs
    SafeArrayUnaccessData(pArray);
    return ret;
}

                                                                        /* VB:
  Declare Function SmsEnumObjectTypes& Lib "vb4sms32.dll" (ByVal hConnection As Long, pObjects() As String, pCount As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsEnumObjectTypesVB(HANDLE hConnection, LPSAFEARRAY* ppArray, DWORD *pCount)
{
    SAFEARRAY* &pArray = *ppArray;
    BSTR* paObjTypesVB;
    SMS_STATUS  ret;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    // if (pCount is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    // if (Count is too big)
    if (*pCount >= 0x80000000 / sizeof(*paObjTypesVB))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Get the count of object types
    *pCount = 0;
    ret = SmsEnumObjectTypes(hConnection, NULL, pCount);
    if (ret != SMS_MORE_DATA) return ret;

    // Create or Redim as necessary
    if (AllocVBArray(pArray, *pCount, sizeof(*paObjTypesVB)) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Lock down the array and obtain pointer to the data
    if (SafeArrayAccessData(pArray, (void**)&paObjTypesVB) != S_OK)
        return SMS_INVALID_PARAMETER;

    // Get an array large enough to accept object types
    DWORD cObjTypes = *pCount;
    SMSBUFF* pObjTypes = new SMSBUFF[cObjTypes];
    if (pObjTypes != NULL)
    {
        // Call 32bit SMS API routine
        ret = SmsEnumObjectTypes(hConnection, pObjTypes, pCount);

        if (ret == SMS_OK)
            for (DWORD dwIndex = 0; dwIndex < cObjTypes; dwIndex++)
            {
                ret = CopyString2VB(&paObjTypesVB[dwIndex],
                                    pObjTypes[dwIndex]);
                if (ret != SMS_OK) break;
            }

        // Unlock the array of object types
        delete[] pObjTypes;
        pObjTypes = NULL;
    }
    else ret = SMS_ERROR;

    // Unlock the VB array of object types
    SafeArrayUnaccessData(pArray);
    return ret;
}


SMS_STATUS CopyObjectDescriptor2VB(OBJDESCRIPTORVB* pObjectVB,
                                   OBJDESCRIPTOR* pObject)
{
    SMS_STATUS ret = SMS_OK;

    // objType
    pObjectVB->objType = pObject->objType;

    // szName
    if (ret == SMS_OK)
        ret = CopyString2VB(&pObjectVB->szName,
                            pObject->szName);

    // szFriendlyName
    if (ret == SMS_OK)
        ret = CopyString2VB(&pObjectVB->szFriendlyName,
                            pObject->szFriendlyName);

    // bGotFriendlyName
    pObjectVB->bGotFriendlyName = pObject->bGotFriendlyName;

    // dwRelopMin
    pObjectVB->dwRelopMin = pObject->dwRelopMin;

    // dwRelopMax
    pObjectVB->dwRelopMax = pObject->dwRelopMax;

    // bGotRelops
    pObjectVB->bGotRelops = pObject->bGotRelops;

    return ret;
}
                                                                        /* VB:
  Declare Function SmsEnumObjects& Lib "vb4sms32.dll" (ByVal hConnection As Long, ByVal pszObjectType As String, pPredecessors() As String, ByVal CtPredecessors As Long, pObjects() As OBJDESCRIPTOR, pCtObjects As Long)
                                                                        '*/
extern "C" SMS_STATUS WINAPI
SmsEnumObjectsVB(HANDLE hConnection, char* pszObjectType, LPSAFEARRAY* ppPredecessorsVB, DWORD CtPredecessors, LPSAFEARRAY* ppArray, DWORD *pCount)
{
    SAFEARRAY* &pArray = *ppArray;
    SAFEARRAY* &pPredecessorsVB = *ppPredecessorsVB;
    BSTR* paPredecessorsVB;
    OBJDESCRIPTORVB* paObjectsVB;
    SMS_STATUS  ret = SMS_OK;

    //////////////////////////////////////////////////////////////////////////
    // Check parameters

    if (ppPredecessorsVB != NULL && CtPredecessors > 0)
    {
        if (pPredecessorsVB->cDims != 1)
            return SMS_INVALID_PARAMETER;

        if (pPredecessorsVB->cbElements	!= 4)
            return SMS_INVALID_PARAMETER;

        if (pPredecessorsVB->rgsabound[0].cElements < CtPredecessors)
            return SMS_INVALID_PARAMETER;
    }

    // if (pCount is invalid)
    if (IsBadWritePtr(pCount, sizeof(*pCount)))
        return SMS_INVALID_PARAMETER;

    // if (Count is too big)
    if (*pCount >= 0x80000000 / sizeof(*paObjectsVB))
        return SMS_INVALID_PARAMETER;

    //////////////////////////////////////////////////////////////////////////

    // Copy Predecessors array
    // Get an array large enough to accept object types
    SMSBUFF* pPredecessors = NULL;
    if (ppPredecessorsVB != NULL && CtPredecessors > 0)
    {
        pPredecessors = new SMSBUFF[CtPredecessors];
        if (pPredecessors == NULL) return SMS_ERROR;

        // Lock down the array and obtain pointer to the data
        if (SafeArrayAccessData(pPredecessorsVB, (void**)&paPredecessorsVB) != S_OK)
            {ret = SMS_INVALID_PARAMETER; goto SmsEnumObjectsVB_Quit;}

        // Turn on ANSI string copy
        gbANSI = TRUE;

        for (DWORD dwIndex = 0; dwIndex < CtPredecessors; dwIndex++)
        {
            ret = CopyString2Sms(pPredecessors[dwIndex],
                                 paPredecessorsVB[dwIndex]);
            if (ret != SMS_OK) break;
        }

        // Turn back off ANSI string copy
        gbANSI = FALSE;

        // Unlock the VB array of object types
        SafeArrayUnaccessData(pPredecessorsVB);
    }

    if (ret == SMS_OK)
    {
        // Get the count of object types
        *pCount = 0;
        ret = SmsEnumObjects(hConnection, pszObjectType, pPredecessors,
                             CtPredecessors, NULL, pCount);
        if (ret != SMS_MORE_DATA) goto SmsEnumObjectsVB_Quit;

        // Create or Redim as necessary
        if (AllocVBArray(pArray, *pCount, sizeof(*paObjectsVB)) != S_OK)
            {ret = SMS_INVALID_PARAMETER; goto SmsEnumObjectsVB_Quit;}

        // Lock down the array and obtain pointer to the data
        if (SafeArrayAccessData(pArray, (void**)&paObjectsVB) != S_OK)
            {ret = SMS_INVALID_PARAMETER; goto SmsEnumObjectsVB_Quit;}

        // Get an array large enough to accept object types
        DWORD cObjects = *pCount;
        OBJDESCRIPTOR* pObjects = new OBJDESCRIPTOR[cObjects];
        if (pObjects != NULL)
        {
            // Call 32bit SMS API routine
            ret = SmsEnumObjects(hConnection, pszObjectType, pPredecessors,
                                 CtPredecessors, pObjects, pCount);

            if (ret == SMS_OK)
                for (DWORD dwIndex = 0; dwIndex < cObjects; dwIndex++)
                {
                    ret = CopyObjectDescriptor2VB(&paObjectsVB[dwIndex],
                                                  &pObjects[dwIndex]);
                    if (ret != SMS_OK) break;
                }

            // Unlock the array of object types
            delete[] pObjects;
            pObjects = NULL;
        }
        else ret = SMS_ERROR;

        // Unlock the VB array of object types
        SafeArrayUnaccessData(pArray);
    }

SmsEnumObjectsVB_Quit:
    // Free the array of predecessors
    if (pPredecessors != NULL) delete[] pPredecessors;
    pPredecessors = NULL;

    return ret;
}
