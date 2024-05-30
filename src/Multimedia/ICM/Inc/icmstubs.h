/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
	icmstubs.h

Abstract:
	
	Stubs for ICM functions

--*/

#ifndef ICMSTUBS_H
#define ICMSTUBS_H

#include "icm.h"

extern BOOL       g_bICMFunctionalityPresent;

extern HPROFILE   (WINAPI *g_pfnOpenColorProfileA)(PPROFILE, DWORD, DWORD, DWORD);
extern HPROFILE   (WINAPI *g_pfnOpenColorProfileW)(PPROFILE, DWORD, DWORD, DWORD);
extern BOOL       (WINAPI *g_pfnCloseColorProfile)(HPROFILE);
extern BOOL       (WINAPI *g_pfnGetColorProfileFromHandle)(HPROFILE, PBYTE, PDWORD);
extern BOOL       (WINAPI *g_pfnIsColorProfileValid)(HPROFILE, PBOOL);
extern BOOL       (WINAPI *g_pfnCreateProfileFromLogColorSpaceA)(LPLOGCOLORSPACEA, PBYTE*);
extern BOOL       (WINAPI *g_pfnCreateProfileFromLogColorSpaceW)(LPLOGCOLORSPACEW, PBYTE*);
extern BOOL       (WINAPI *g_pfnGetCountColorProfileElements)(HPROFILE, PDWORD);
extern BOOL       (WINAPI *g_pfnGetColorProfileHeader)(HPROFILE, PPROFILEHEADER);
extern BOOL       (WINAPI *g_pfnGetColorProfileElementTag)(HPROFILE, DWORD, PTAGTYPE);
extern BOOL       (WINAPI *g_pfnIsColorProfileTagPresent)(HPROFILE, TAGTYPE, PBOOL);
extern BOOL       (WINAPI *g_pfnGetColorProfileElement)(HPROFILE, TAGTYPE, DWORD, PDWORD, PVOID, PBOOL);
extern BOOL       (WINAPI *g_pfnSetColorProfileHeader)(HPROFILE, PPROFILEHEADER);
extern BOOL       (WINAPI *g_pfnSetColorProfileElementSize)(HPROFILE, TAGTYPE, DWORD);
extern BOOL       (WINAPI *g_pfnSetColorProfileElement)(HPROFILE, TAGTYPE, DWORD, PDWORD, PVOID);
extern BOOL       (WINAPI *g_pfnSetColorProfileElementReference)(HPROFILE, TAGTYPE, TAGTYPE);
extern BOOL       (WINAPI *g_pfnGetPS2ColorSpaceArray)(HPROFILE, DWORD, DWORD, PBYTE, PDWORD, PBOOL);
extern BOOL       (WINAPI *g_pfnGetPS2ColorRenderingIntent)(HPROFILE, DWORD, PBYTE, PDWORD);
extern BOOL       (WINAPI *g_pfnGetPS2ColorRenderingDictionary)(HPROFILE, DWORD, PBYTE, PDWORD, PBOOL);
extern BOOL       (WINAPI *g_pfnGetNamedProfileInfo)(HPROFILE, PNAMED_PROFILE_INFO);
extern BOOL       (WINAPI *g_pfnConvertColorNameToIndex)(HPROFILE, PCOLOR_NAME, PDWORD, DWORD);
extern BOOL       (WINAPI *g_pfnConvertIndexToColorName)(HPROFILE, PDWORD, PCOLOR_NAME, DWORD);
extern BOOL       (WINAPI *g_pfnCreateDeviceLinkProfile)(PHPROFILE, DWORD, PDWORD, DWORD, DWORD, PBYTE*, DWORD);
extern HTRANSFORM (WINAPI *g_pfnCreateColorTransformA)(LPLOGCOLORSPACEA, HPROFILE, HPROFILE, DWORD);
extern HTRANSFORM (WINAPI *g_pfnCreateColorTransformW)(LPLOGCOLORSPACEW, HPROFILE, HPROFILE, DWORD);
extern HTRANSFORM (WINAPI *g_pfnCreateMultiProfileTransform)(PHPROFILE, DWORD, PDWORD, DWORD, DWORD, DWORD);
extern BOOL       (WINAPI *g_pfnDeleteColorTransform)(HTRANSFORM);
extern BOOL       (WINAPI *g_pfnTranslateBitmapBits)(HTRANSFORM, PVOID, BMFORMAT, DWORD, DWORD, DWORD, PVOID, BMFORMAT, DWORD, PBMCALLBACKFN, LPARAM);
extern BOOL       (WINAPI *g_pfnCheckBitmapBits)(HTRANSFORM , PVOID, BMFORMAT, DWORD, DWORD, DWORD, PBYTE, PBMCALLBACKFN, LPARAM);
extern BOOL       (WINAPI *g_pfnTranslateColors)(HTRANSFORM, PCOLOR, DWORD, COLORTYPE, PCOLOR, COLORTYPE);
extern BOOL       (WINAPI *g_pfnCheckColors)(HTRANSFORM, PCOLOR, DWORD, COLORTYPE, PBYTE);
extern DWORD      (WINAPI *g_pfnGetCMMInfo)(HTRANSFORM, DWORD);
extern BOOL       (WINAPI *g_pfnRegisterCMMA)(PCSTR, DWORD, PCSTR);
extern BOOL       (WINAPI *g_pfnRegisterCMMW)(PCWSTR, DWORD, PCWSTR);
extern BOOL       (WINAPI *g_pfnUnregisterCMMA)(PCSTR, DWORD);
extern BOOL       (WINAPI *g_pfnUnregisterCMMW)(PCWSTR, DWORD);
extern BOOL       (WINAPI *g_pfnSelectCMM)(DWORD);
extern BOOL       (WINAPI *g_pfnGetColorDirectoryA)(PCSTR, PSTR, PDWORD);
extern BOOL       (WINAPI *g_pfnGetColorDirectoryW)(PCWSTR, PWSTR, PDWORD);
extern BOOL       (WINAPI *g_pfnInstallColorProfileA)(PCSTR, PCSTR);
extern BOOL       (WINAPI *g_pfnInstallColorProfileW)(PCWSTR, PCWSTR);
extern BOOL       (WINAPI *g_pfnUninstallColorProfileA)(PCSTR, PCSTR, BOOL);
extern BOOL       (WINAPI *g_pfnUninstallColorProfileW)(PCWSTR, PCWSTR, BOOL);
extern BOOL       (WINAPI *g_pfnEnumColorProfilesA)(PCSTR, PENUMTYPEA, PBYTE, PDWORD, PDWORD);
extern BOOL       (WINAPI *g_pfnEnumColorProfilesW)(PCWSTR, PENUMTYPEW, PBYTE, PDWORD, PDWORD);
extern BOOL       (WINAPI *g_pfnSetStandardColorSpaceProfileA)(PCSTR, DWORD, PCSTR);
extern BOOL       (WINAPI *g_pfnSetStandardColorSpaceProfileW)(PCWSTR, DWORD, PCWSTR);
extern BOOL       (WINAPI *g_pfnGetStandardColorSpaceProfileA)(PCSTR, DWORD, PSTR, PDWORD);
extern BOOL       (WINAPI *g_pfnGetStandardColorSpaceProfileW)(PCWSTR, DWORD, PWSTR, PDWORD);
extern BOOL       (WINAPI *g_pfnAssociateColorProfileWithDeviceA)(PCSTR, PCSTR, PCSTR);
extern BOOL       (WINAPI *g_pfnAssociateColorProfileWithDeviceW)(PCWSTR, PCWSTR, PCWSTR);
extern BOOL       (WINAPI *g_pfnDisassociateColorProfileFromDeviceA)(PCSTR, PCSTR, PCSTR);
extern BOOL       (WINAPI *g_pfnDisassociateColorProfileFromDeviceW)(PCWSTR, PCWSTR, PCWSTR);
extern BOOL       (WINAPI *g_pfnSetupColorMatchingW)(PCOLORMATCHSETUPW pcms);
extern BOOL       (WINAPI *g_pfnSetupColorMatchingA)(PCOLORMATCHSETUPA pcms);
extern BOOL       (WINAPI *g_pfnColorCorrectPalette)(HDC, HPALETTE, DWORD, DWORD);

#define OpenColorProfileA						(*g_pfnOpenColorProfileA)
#define OpenColorProfileW						(*g_pfnOpenColorProfileW)
#define CloseColorProfile						(*g_pfnCloseColorProfile)
#define GetColorProfileFromHandle				(*g_pfnGetColorProfileFromHandle)
#define IsColorProfileValid						(*g_pfnIsColorProfileValid)
#define CreateProfileFromLogColorSpaceA			(*g_pfnCreateProfileFromLogColorSpaceA)
#define CreateProfileFromLogColorSpaceW			(*g_pfnCreateProfileFromLogColorSpaceW)
#define GetCountColorProfileElements			(*g_pfnGetCountColorProfileElements)
#define GetColorProfileHeader					(*g_pfnGetColorProfileHeader)
#define GetColorProfileElementTag				(*g_pfnGetColorProfileElementTag)
#define IsColorProfileTagPresent				(*g_pfnIsColorProfileTagPresent)
#define GetColorProfileElement					(*g_pfnGetColorProfileElement)
#define SetColorProfileHeader					(*g_pfnSetColorProfileHeader)
#define SetColorProfileElementSize				(*g_pfnSetColorProfileElementSize)
#define SetColorProfileElement					(*g_pfnSetColorProfileElement)
#define SetColorProfileElementReference			(*g_pfnSetColorProfileElementReference)
#define GetPS2ColorSpaceArray					(*g_pfnGetPS2ColorSpaceArray)
#define GetPS2ColorRenderingIntent				(*g_pfnGetPS2ColorRenderingIntent)
#define GetPS2ColorRenderingDictionary			(*g_pfnGetPS2ColorRenderingDictionary)
#define GetNamedProfileInfo						(*g_pfnGetNamedProfileInfo)
#define ConvertColorNameToIndex					(*g_pfnConvertColorNameToIndex)
#define ConvertIndexToColorName					(*g_pfnConvertIndexToColorName)
#define CreateDeviceLinkProfile					(*g_pfnCreateDeviceLinkProfile)
#define CreateColorTransformA					(*g_pfnCreateColorTransformA)
#define CreateColorTransformW					(*g_pfnCreateColorTransformW)
#define CreateMultiProfileTransform				(*g_pfnCreateMultiProfileTransform)
#define DeleteColorTransform					(*g_pfnDeleteColorTransform)
#define TranslateBitmapBits						(*g_pfnTranslateBitmapBits)
#define CheckBitmapBits							(*g_pfnCheckBitmapBits)
#define TranslateColors							(*g_pfnTranslateColors)
#define CheckColors								(*g_pfnCheckColors)
#define GetCMMInfo								(*g_pfnGetCMMInfo)
#define RegisterCMMA							(*g_pfnRegisterCMMA)
#define RegisterCMMW							(*g_pfnRegisterCMMW)
#define UnregisterCMMA							(*g_pfnUnregisterCMMA)
#define UnregisterCMMW							(*g_pfnUnregisterCMMW)
#define SelectCMM								(*g_pfnSelectCMM)
#define GetColorDirectoryA						(*g_pfnGetColorDirectoryA)
#define GetColorDirectoryW						(*g_pfnGetColorDirectoryW)
#define InstallColorProfileA					(*g_pfnInstallColorProfileA)
#define InstallColorProfileW					(*g_pfnInstallColorProfileW)
#define UninstallColorProfileA					(*g_pfnUninstallColorProfileA)
#define UninstallColorProfileW					(*g_pfnUninstallColorProfileW)
#define EnumColorProfilesA						(*g_pfnEnumColorProfilesA)
#define EnumColorProfilesW						(*g_pfnEnumColorProfilesW)
#define SetStandardColorSpaceProfileA			(*g_pfnSetStandardColorSpaceProfileA)
#define SetStandardColorSpaceProfileW			(*g_pfnSetStandardColorSpaceProfileW)
#define GetStandardColorSpaceProfileA			(*g_pfnGetStandardColorSpaceProfileA)
#define GetStandardColorSpaceProfileW			(*g_pfnGetStandardColorSpaceProfileW)
#define AssociateColorProfileWithDeviceA		(*g_pfnAssociateColorProfileWithDeviceA)
#define AssociateColorProfileWithDeviceW		(*g_pfnAssociateColorProfileWithDeviceW)
#define DisassociateColorProfileFromDeviceA		(*g_pfnDisassociateColorProfileFromDeviceA)
#define DisassociateColorProfileFromDeviceW		(*g_pfnDisassociateColorProfileFromDeviceW)
#define SetupColorMatchingW						(*g_pfnSetupColorMatchingW)
#define SetupColorMatchingA						(*g_pfnSetupColorMatchingA)
#define ColorCorrectPalette						(*g_pfnColorCorrectPalette)

VOID InitICMStubs();
VOID FreeICMStubs();

#endif //ICMSTUBS_H


#ifdef IMPLEMENT_ICM_STUBS

HPROFILE   WINAPI xOpenColorProfileA(PPROFILE pProfile, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationMode) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
HPROFILE   WINAPI xOpenColorProfileW(PPROFILE pProfile, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationMode) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
BOOL       WINAPI xCloseColorProfile(HPROFILE hProfile) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetColorProfileFromHandle(HPROFILE hProfile, PBYTE pBuffer, PDWORD pcbSize) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xIsColorProfileValid(HPROFILE hProfile,  PBOOL pbValid) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xCreateProfileFromLogColorSpaceA(LPLOGCOLORSPACEA pLogColorSpace,   PBYTE *pBuffer) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xCreateProfileFromLogColorSpaceW(LPLOGCOLORSPACEW pLogColorSpace,   PBYTE *pBuffer) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetCountColorProfileElements(HPROFILE hProfile,  PDWORD pnCount) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetColorProfileHeader(HPROFILE hProfile,  PPROFILEHEADER pHeader) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetColorProfileElementTag(HPROFILE hProfile,  DWORD dwIndex,  PTAGTYPE pTag) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xIsColorProfileTagPresent(HPROFILE hProfile,  TAGTYPE tag,  PBOOL pbPresent) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetColorProfileElement(HPROFILE hProfile,  TAGTYPE tag,  DWORD dwOffset,  PDWORD pcbSize, PVOID pBuffer,  PBOOL pbReference) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetColorProfileHeader(HPROFILE hProfile,    PPROFILEHEADER pHeader) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetColorProfileElementSize(HPROFILE hProfile,  TAGTYPE tag,  DWORD cbSize) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetColorProfileElement(HPROFILE hProfile,  TAGTYPE tag,  DWORD dwOffset,   PDWORD pcbSize,  PVOID pBuffer) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetColorProfileElementReference(HPROFILE hProfile,  TAGTYPE newTag,  TAGTYPE refTag) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetPS2ColorSpaceArray(HPROFILE hProfile,  DWORD dwIntent,  DWORD dwCSAType,  PBYTE pBuffer, PDWORD pcbSize,  PBOOL pbBinary) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetPS2ColorRenderingIntent(HPROFILE hProfile,  DWORD dwIntent,  PBYTE pBuffer,  PDWORD pcbSize) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetPS2ColorRenderingDictionary(HPROFILE hProfile,  DWORD dwIntent,  PBYTE pBuffer,  PDWORD pcbSize,  PBOOL pbBinary) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetNamedProfileInfo(HPROFILE hProfile,  PNAMED_PROFILE_INFO pNamedProfileInfo) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xConvertColorNameToIndex(HPROFILE hProfile,   PCOLOR_NAME paColorName,  PDWORD paIndex,  DWORD dwCount) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xConvertIndexToColorName(HPROFILE hProfile,  PDWORD paIndex,  PCOLOR_NAME paColorName,  DWORD dwCount) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xCreateDeviceLinkProfile(PHPROFILE pahProfiles,  DWORD nProfiles,  PDWORD padwIntent,  DWORD nIntents,  DWORD dwFlags,  PBYTE *pProfileData,  DWORD indexPreferredCMM) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
HTRANSFORM WINAPI xCreateColorTransformA(LPLOGCOLORSPACEA pLogColorSpace,  HPROFILE hDestProfile,  HPROFILE hTargetProfile,  DWORD dwFlags) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
HTRANSFORM WINAPI xCreateColorTransformW(LPLOGCOLORSPACEW pLogColorSpace,  HPROFILE hDestProfile,  HPROFILE hTargetProfile,  DWORD dwFlags) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
HTRANSFORM WINAPI xCreateMultiProfileTransform(PHPROFILE pahProfiles,  DWORD nProfiles,  PDWORD padwIntent,  DWORD nIntents,  DWORD dwFlags,  DWORD indexPreferredCMM) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
BOOL       WINAPI xDeleteColorTransform(HTRANSFORM hColorTransform) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xTranslateBitmapBits(HTRANSFORM hColorTransform,  PVOID pSrcBits,  BMFORMAT bmInput,  DWORD dwWidth,  DWORD dwHeight,  DWORD dwInputStride,  PVOID pDestBits,  BMFORMAT bmOutput,  DWORD dwOutputStride,  PBMCALLBACKFN pfnCallback,  LPARAM ulCallbackData) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xCheckBitmapBits(HTRANSFORM hColorTransform,  PVOID pSrcBits,  BMFORMAT bmInput,   DWORD dwWidth,  DWORD dwHeight,   DWORD dwStride,   PBYTE paResult,  PBMCALLBACKFN pfnCallback,   LPARAM lpCallbackData) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xTranslateColors(HTRANSFORM hColorTransform,  PCOLOR paInputColors,  DWORD nColors,   COLORTYPE ctInput,  PCOLOR paOutputColors,  COLORTYPE ctOutput) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xCheckColors(HTRANSFORM hColorTransform,  PCOLOR paInputColors,   DWORD nColors,  COLORTYPE ctInput,  PBYTE paResult) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
DWORD      WINAPI xGetCMMInfo(HTRANSFORM hColorTransform,  DWORD dwInfo) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return 0; }
BOOL       WINAPI xRegisterCMMA(PCSTR pMachineName,  DWORD cmmID,  PCSTR pCMMdll) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xRegisterCMMW(PCWSTR pMachineName,  DWORD cmmID,  PCWSTR pCMMdll) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xUnregisterCMMA(PCSTR pMachineName,  DWORD cmmID) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xUnregisterCMMW(PCWSTR pMachineName,  DWORD cmmID) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSelectCMM(DWORD cmmID) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetColorDirectoryA(PCSTR pMachineName,  PSTR pBuffer,   PDWORD pdwSize) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetColorDirectoryW(PCWSTR pMachineName,  PWSTR pBuffer,   PDWORD pdwSize ) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xInstallColorProfileA(PCSTR pMachineName,  PCSTR pProfileName) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xInstallColorProfileW(PCWSTR pMachineName,  PCWSTR pProfileName) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xUninstallColorProfileA(PCSTR pMachineName,  PCSTR  pProfileName,  BOOL bDelete) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xUninstallColorProfileW(PCWSTR pMachineName,  PCWSTR  pProfileName,  BOOL bDelete) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xEnumColorProfilesA(PCSTR pMachineName,  PENUMTYPEA pEnumRecord,  PBYTE pBuffer,  PDWORD pdwSize,  PDWORD pnProfiles) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xEnumColorProfilesW(PCWSTR pMachineName,  PENUMTYPEW pEnumRecord,  PBYTE pBuffer,  PDWORD pdwSize,  PDWORD pnProfiles) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetStandardColorSpaceProfileA(PCSTR pMachineName,  DWORD dwProfileID,  PCSTR pProfilename) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetStandardColorSpaceProfileW(PCWSTR pMachineName,  DWORD dwProfileID,  PCWSTR pProfilename) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetStandardColorSpaceProfileA(PCSTR pMachineName,  DWORD dwProfileID,  PSTR pProfileName,  PDWORD pdwSize) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xGetStandardColorSpaceProfileW(PCWSTR pMachineName,  DWORD dwProfileID,  PWSTR pProfileName,  PDWORD pdwSize) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xAssociateColorProfileWithDeviceA(PCSTR pMachineName,  PCSTR pProfileName,  PCSTR pDeviceName) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xAssociateColorProfileWithDeviceW(PCWSTR pMachineName,  PCWSTR pProfileName,  PCWSTR pDeviceName) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xDisassociateColorProfileFromDeviceA(PCSTR pMachineName,  PCSTR pProfileName,  PCSTR pDeviceName) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xDisassociateColorProfileFromDeviceW(PCWSTR pMachineName,  PCWSTR pProfileName,  PCWSTR pDeviceName) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetupColorMatchingW(PCOLORMATCHSETUPW pcms) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xSetupColorMatchingA(PCOLORMATCHSETUPA pcms) { SetLastError(ERROR_CALL_NOT_IMPLEMENTED); return FALSE; }
BOOL       WINAPI xColorCorrectPalette(HDC hDC,  HPALETTE hPalette,   DWORD dwFirstEntry,  DWORD dwNumOfEntries) { return FALSE; }

HPROFILE   (WINAPI *g_pfnOpenColorProfileA)(PPROFILE, DWORD, DWORD, DWORD) = xOpenColorProfileA;
HPROFILE   (WINAPI *g_pfnOpenColorProfileW)(PPROFILE, DWORD, DWORD, DWORD) = xOpenColorProfileW;
BOOL       (WINAPI *g_pfnCloseColorProfile)(HPROFILE) = xCloseColorProfile;
BOOL       (WINAPI *g_pfnGetColorProfileFromHandle)(HPROFILE, PBYTE, PDWORD) = xGetColorProfileFromHandle;
BOOL       (WINAPI *g_pfnIsColorProfileValid)(HPROFILE, PBOOL) = xIsColorProfileValid;
BOOL       (WINAPI *g_pfnCreateProfileFromLogColorSpaceA)(LPLOGCOLORSPACEA, PBYTE*) = xCreateProfileFromLogColorSpaceA;
BOOL       (WINAPI *g_pfnCreateProfileFromLogColorSpaceW)(LPLOGCOLORSPACEW, PBYTE*) = xCreateProfileFromLogColorSpaceW;
BOOL       (WINAPI *g_pfnGetCountColorProfileElements)(HPROFILE, PDWORD) = xGetCountColorProfileElements;
BOOL       (WINAPI *g_pfnGetColorProfileHeader)(HPROFILE, PPROFILEHEADER) = xGetColorProfileHeader;
BOOL       (WINAPI *g_pfnGetColorProfileElementTag)(HPROFILE, DWORD, PTAGTYPE) = xGetColorProfileElementTag;
BOOL       (WINAPI *g_pfnIsColorProfileTagPresent)(HPROFILE, TAGTYPE, PBOOL) = xIsColorProfileTagPresent;
BOOL       (WINAPI *g_pfnGetColorProfileElement)(HPROFILE, TAGTYPE, DWORD, PDWORD, PVOID, PBOOL) = xGetColorProfileElement;
BOOL       (WINAPI *g_pfnSetColorProfileHeader)(HPROFILE, PPROFILEHEADER) = xSetColorProfileHeader;
BOOL       (WINAPI *g_pfnSetColorProfileElementSize)(HPROFILE, TAGTYPE, DWORD) = xSetColorProfileElementSize;
BOOL       (WINAPI *g_pfnSetColorProfileElement)(HPROFILE, TAGTYPE, DWORD, PDWORD, PVOID) = xSetColorProfileElement;
BOOL       (WINAPI *g_pfnSetColorProfileElementReference)(HPROFILE, TAGTYPE, TAGTYPE) = xSetColorProfileElementReference;
BOOL       (WINAPI *g_pfnGetPS2ColorSpaceArray)(HPROFILE, DWORD, DWORD, PBYTE, PDWORD, PBOOL) = xGetPS2ColorSpaceArray;
BOOL       (WINAPI *g_pfnGetPS2ColorRenderingIntent)(HPROFILE, DWORD, PBYTE, PDWORD) = xGetPS2ColorRenderingIntent;
BOOL       (WINAPI *g_pfnGetPS2ColorRenderingDictionary)(HPROFILE, DWORD, PBYTE, PDWORD, PBOOL) = xGetPS2ColorRenderingDictionary;
BOOL       (WINAPI *g_pfnGetNamedProfileInfo)(HPROFILE, PNAMED_PROFILE_INFO) = xGetNamedProfileInfo;
BOOL       (WINAPI *g_pfnConvertColorNameToIndex)(HPROFILE, PCOLOR_NAME, PDWORD, DWORD) = xConvertColorNameToIndex;
BOOL       (WINAPI *g_pfnConvertIndexToColorName)(HPROFILE, PDWORD, PCOLOR_NAME, DWORD) = xConvertIndexToColorName;
BOOL       (WINAPI *g_pfnCreateDeviceLinkProfile)(PHPROFILE, DWORD, PDWORD, DWORD, DWORD, PBYTE*, DWORD) = xCreateDeviceLinkProfile;
HTRANSFORM (WINAPI *g_pfnCreateColorTransformA)(LPLOGCOLORSPACEA, HPROFILE, HPROFILE, DWORD) = xCreateColorTransformA;
HTRANSFORM (WINAPI *g_pfnCreateColorTransformW)(LPLOGCOLORSPACEW, HPROFILE, HPROFILE, DWORD) = xCreateColorTransformW;
HTRANSFORM (WINAPI *g_pfnCreateMultiProfileTransform)(PHPROFILE, DWORD, PDWORD, DWORD, DWORD, DWORD) = xCreateMultiProfileTransform;
BOOL       (WINAPI *g_pfnDeleteColorTransform)(HTRANSFORM) = xDeleteColorTransform;
BOOL       (WINAPI *g_pfnTranslateBitmapBits)(HTRANSFORM, PVOID, BMFORMAT, DWORD, DWORD, DWORD, PVOID, BMFORMAT, DWORD, PBMCALLBACKFN, LPARAM) = xTranslateBitmapBits;
BOOL       (WINAPI *g_pfnCheckBitmapBits)(HTRANSFORM , PVOID, BMFORMAT, DWORD, DWORD, DWORD, PBYTE, PBMCALLBACKFN, LPARAM) = xCheckBitmapBits;
BOOL       (WINAPI *g_pfnTranslateColors)(HTRANSFORM, PCOLOR, DWORD, COLORTYPE, PCOLOR, COLORTYPE) = xTranslateColors;
BOOL       (WINAPI *g_pfnCheckColors)(HTRANSFORM, PCOLOR, DWORD, COLORTYPE, PBYTE) = xCheckColors;
DWORD      (WINAPI *g_pfnGetCMMInfo)(HTRANSFORM, DWORD) = xGetCMMInfo;
BOOL       (WINAPI *g_pfnRegisterCMMA)(PCSTR, DWORD, PCSTR) = xRegisterCMMA;
BOOL       (WINAPI *g_pfnRegisterCMMW)(PCWSTR, DWORD, PCWSTR) = xRegisterCMMW;
BOOL       (WINAPI *g_pfnUnregisterCMMA)(PCSTR, DWORD) = xUnregisterCMMA;
BOOL       (WINAPI *g_pfnUnregisterCMMW)(PCWSTR, DWORD) = xUnregisterCMMW;
BOOL       (WINAPI *g_pfnSelectCMM)(DWORD) = xSelectCMM;
BOOL       (WINAPI *g_pfnGetColorDirectoryA)(PCSTR, PSTR, PDWORD) = xGetColorDirectoryA;
BOOL       (WINAPI *g_pfnGetColorDirectoryW)(PCWSTR, PWSTR, PDWORD) = xGetColorDirectoryW;
BOOL       (WINAPI *g_pfnInstallColorProfileA)(PCSTR, PCSTR) = xInstallColorProfileA;
BOOL       (WINAPI *g_pfnInstallColorProfileW)(PCWSTR, PCWSTR) = xInstallColorProfileW;
BOOL       (WINAPI *g_pfnUninstallColorProfileA)(PCSTR, PCSTR, BOOL) = xUninstallColorProfileA;
BOOL       (WINAPI *g_pfnUninstallColorProfileW)(PCWSTR, PCWSTR, BOOL) = xUninstallColorProfileW;
BOOL       (WINAPI *g_pfnEnumColorProfilesA)(PCSTR, PENUMTYPEA, PBYTE, PDWORD, PDWORD) = xEnumColorProfilesA;
BOOL       (WINAPI *g_pfnEnumColorProfilesW)(PCWSTR, PENUMTYPEW, PBYTE, PDWORD, PDWORD) = xEnumColorProfilesW;
BOOL       (WINAPI *g_pfnSetStandardColorSpaceProfileA)(PCSTR, DWORD, PCSTR) = xSetStandardColorSpaceProfileA;
BOOL       (WINAPI *g_pfnSetStandardColorSpaceProfileW)(PCWSTR, DWORD, PCWSTR) = xSetStandardColorSpaceProfileW;
BOOL       (WINAPI *g_pfnGetStandardColorSpaceProfileA)(PCSTR, DWORD, PSTR, PDWORD) = xGetStandardColorSpaceProfileA;
BOOL       (WINAPI *g_pfnGetStandardColorSpaceProfileW)(PCWSTR, DWORD, PWSTR, PDWORD) = xGetStandardColorSpaceProfileW;
BOOL       (WINAPI *g_pfnAssociateColorProfileWithDeviceA)(PCSTR, PCSTR, PCSTR) = xAssociateColorProfileWithDeviceA;
BOOL       (WINAPI *g_pfnAssociateColorProfileWithDeviceW)(PCWSTR, PCWSTR, PCWSTR) = xAssociateColorProfileWithDeviceW;
BOOL       (WINAPI *g_pfnDisassociateColorProfileFromDeviceA)(PCSTR, PCSTR, PCSTR) = xDisassociateColorProfileFromDeviceA;
BOOL       (WINAPI *g_pfnDisassociateColorProfileFromDeviceW)(PCWSTR, PCWSTR, PCWSTR) = xDisassociateColorProfileFromDeviceW;
BOOL       (WINAPI *g_pfnSetupColorMatchingW)(PCOLORMATCHSETUPW pcms) = xSetupColorMatchingW;
BOOL       (WINAPI *g_pfnSetupColorMatchingA)(PCOLORMATCHSETUPA pcms) = xSetupColorMatchingA;
BOOL       (WINAPI *g_pfnColorCorrectPalette)(HDC, HPALETTE, DWORD, DWORD) = xColorCorrectPalette;

BOOL       g_bICMFunctionalityPresent = FALSE;

HMODULE    hMSCMS = 0;
HMODULE    hICMUI = 0;

#define StoreProcAddress(hModule, ProcName, Proc) \
	(pfn = GetProcAddress(hModule, ProcName), pfn ? *(FARPROC*) Proc = pfn : 0)

VOID InitICMStubs()
{
	HMODULE hGDI32;
	FARPROC pfn;

    g_bICMFunctionalityPresent = 
		(hMSCMS = LoadLibrary(_T("MSCMS.DLL"))) &&
		(hICMUI = LoadLibrary(_T("ICMUI.DLL"))) &&
		(hGDI32 = GetModuleHandle(_T("GDI32"))) &&
        StoreProcAddress(hMSCMS, "OpenColorProfileA",					&g_pfnOpenColorProfileA) &&
        StoreProcAddress(hMSCMS, "OpenColorProfileW",					&g_pfnOpenColorProfileW) &&
        StoreProcAddress(hMSCMS, "CloseColorProfile",					&g_pfnCloseColorProfile) &&
        StoreProcAddress(hMSCMS, "GetColorProfileFromHandle",			&g_pfnGetColorProfileFromHandle) &&
        StoreProcAddress(hMSCMS, "IsColorProfileValid",					&g_pfnIsColorProfileValid) &&
        StoreProcAddress(hMSCMS, "CreateProfileFromLogColorSpaceA",		&g_pfnCreateProfileFromLogColorSpaceA) &&
        StoreProcAddress(hMSCMS, "CreateProfileFromLogColorSpaceW",		&g_pfnCreateProfileFromLogColorSpaceW) &&
        StoreProcAddress(hMSCMS, "GetCountColorProfileElements",		&g_pfnGetCountColorProfileElements) &&
        StoreProcAddress(hMSCMS, "GetColorProfileHeader",				&g_pfnGetColorProfileHeader) &&
        StoreProcAddress(hMSCMS, "GetColorProfileElementTag",			&g_pfnGetColorProfileElementTag) &&
        StoreProcAddress(hMSCMS, "IsColorProfileTagPresent",			&g_pfnIsColorProfileTagPresent) &&
        StoreProcAddress(hMSCMS, "GetColorProfileElement",				&g_pfnGetColorProfileElement) &&
        StoreProcAddress(hMSCMS, "SetColorProfileHeader",				&g_pfnSetColorProfileHeader) &&
        StoreProcAddress(hMSCMS, "SetColorProfileElementSize",			&g_pfnSetColorProfileElementSize) &&
        StoreProcAddress(hMSCMS, "SetColorProfileElement",				&g_pfnSetColorProfileElement) &&
        StoreProcAddress(hMSCMS, "SetColorProfileElementReference",		&g_pfnSetColorProfileElementReference) &&
        StoreProcAddress(hMSCMS, "GetPS2ColorSpaceArray",				&g_pfnGetPS2ColorSpaceArray) &&
        StoreProcAddress(hMSCMS, "GetPS2ColorRenderingIntent",			&g_pfnGetPS2ColorRenderingIntent) &&
        StoreProcAddress(hMSCMS, "GetPS2ColorRenderingDictionary",		&g_pfnGetPS2ColorRenderingDictionary) &&
        StoreProcAddress(hMSCMS, "GetNamedProfileInfo",					&g_pfnGetNamedProfileInfo) &&
        StoreProcAddress(hMSCMS, "ConvertColorNameToIndex",				&g_pfnConvertColorNameToIndex) &&
        StoreProcAddress(hMSCMS, "ConvertIndexToColorName",				&g_pfnConvertIndexToColorName) &&
        StoreProcAddress(hMSCMS, "CreateDeviceLinkProfile",				&g_pfnCreateDeviceLinkProfile) &&
        StoreProcAddress(hMSCMS, "CreateColorTransformA",				&g_pfnCreateColorTransformA) &&
        StoreProcAddress(hMSCMS, "CreateColorTransformW",				&g_pfnCreateColorTransformW) &&
        StoreProcAddress(hMSCMS, "CreateMultiProfileTransform",			&g_pfnCreateMultiProfileTransform) &&
        StoreProcAddress(hMSCMS, "DeleteColorTransform",				&g_pfnDeleteColorTransform) &&
        StoreProcAddress(hMSCMS, "TranslateBitmapBits",					&g_pfnTranslateBitmapBits) &&
        StoreProcAddress(hMSCMS, "CheckBitmapBits",						&g_pfnCheckBitmapBits) &&
        StoreProcAddress(hMSCMS, "TranslateColors",						&g_pfnTranslateColors) &&
        StoreProcAddress(hMSCMS, "CheckColors",							&g_pfnCheckColors) &&
        StoreProcAddress(hMSCMS, "GetCMMInfo",							&g_pfnGetCMMInfo) &&
        StoreProcAddress(hMSCMS, "RegisterCMMA",						&g_pfnRegisterCMMA) &&
        StoreProcAddress(hMSCMS, "RegisterCMMW",						&g_pfnRegisterCMMW) &&
        StoreProcAddress(hMSCMS, "UnregisterCMMA",						&g_pfnUnregisterCMMA) &&
        StoreProcAddress(hMSCMS, "UnregisterCMMW",						&g_pfnUnregisterCMMW) &&
        StoreProcAddress(hMSCMS, "SelectCMM",							&g_pfnSelectCMM) &&
        StoreProcAddress(hMSCMS, "GetColorDirectoryA",					&g_pfnGetColorDirectoryA) &&
        StoreProcAddress(hMSCMS, "GetColorDirectoryW",					&g_pfnGetColorDirectoryW) &&
        StoreProcAddress(hMSCMS, "InstallColorProfileA",				&g_pfnInstallColorProfileA) &&
        StoreProcAddress(hMSCMS, "InstallColorProfileW",				&g_pfnInstallColorProfileW) &&
        StoreProcAddress(hMSCMS, "UninstallColorProfileA",				&g_pfnUninstallColorProfileA) &&
        StoreProcAddress(hMSCMS, "UninstallColorProfileW",				&g_pfnUninstallColorProfileW) &&
        StoreProcAddress(hMSCMS, "EnumColorProfilesA",					&g_pfnEnumColorProfilesA) &&
        StoreProcAddress(hMSCMS, "EnumColorProfilesW",					&g_pfnEnumColorProfilesW) &&
        StoreProcAddress(hMSCMS, "SetStandardColorSpaceProfileA",		&g_pfnSetStandardColorSpaceProfileA) &&
        StoreProcAddress(hMSCMS, "SetStandardColorSpaceProfileW",		&g_pfnSetStandardColorSpaceProfileW) &&
        StoreProcAddress(hMSCMS, "GetStandardColorSpaceProfileA",		&g_pfnGetStandardColorSpaceProfileA) &&
        StoreProcAddress(hMSCMS, "GetStandardColorSpaceProfileW",		&g_pfnGetStandardColorSpaceProfileW) &&
        StoreProcAddress(hMSCMS, "AssociateColorProfileWithDeviceA",	&g_pfnAssociateColorProfileWithDeviceA) &&
        StoreProcAddress(hMSCMS, "AssociateColorProfileWithDeviceW",	&g_pfnAssociateColorProfileWithDeviceW) &&
        StoreProcAddress(hMSCMS, "DisassociateColorProfileFromDeviceA", &g_pfnDisassociateColorProfileFromDeviceA) &&
        StoreProcAddress(hMSCMS, "DisassociateColorProfileFromDeviceW", &g_pfnDisassociateColorProfileFromDeviceW) &&
        StoreProcAddress(hICMUI, "SetupColorMatchingA",					&g_pfnSetupColorMatchingA) &&
        StoreProcAddress(hICMUI, "SetupColorMatchingW",					&g_pfnSetupColorMatchingW) &&
        StoreProcAddress(hGDI32, "ColorCorrectPalette",					&g_pfnColorCorrectPalette);
}

VOID FreeICMStubs()
{
	if (hMSCMS) {
	
		FreeLibrary(hMSCMS);
	}

	if (hICMUI) {
	
		FreeLibrary(hICMUI);
	}
}

#ifdef __cplusplus

static struct CICMStubs
{
	CICMStubs()
    {
        InitICMStubs();
    }

	~CICMStubs()
    {
        FreeICMStubs();
    }

} ICMStubs;

#endif //__cplusplus

#endif //IMPLEMENT_ICM_STUBS

