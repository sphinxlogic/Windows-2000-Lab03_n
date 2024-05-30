//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       UTIL.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"
#include "shlobj.h"


//****************************************************************************
//
// BOOL GetIniBool(LPTSTR pszEntry, BOOL fDefault)
//
// Get the boolean data for an entry
//
//****************************************************************************

BOOL GetIniBool(LPTSTR pszEntry, BOOL fDefault)
{
	return GetPrivateProfileInt(gszAppName, pszEntry, fDefault, gszIniName) != 0;
}

//****************************************************************************
//
// DWORD GetIniInt(LPTSTR pszEntry, DWORD dwDefault)
//
// Get the numeric data for an entry
//
//****************************************************************************

DWORD GetIniInt(LPTSTR pszEntry, DWORD dwDefault)
{
	return GetPrivateProfileInt(gszAppName, pszEntry, dwDefault, gszIniName);
}

//****************************************************************************
//
// LPTSTR GetIniStr(LPTSTR pszEntry, LPTSTR pszDefault)
//
// Get the string data for an entry
//
//****************************************************************************

LPTSTR GetIniStr(LPTSTR pszEntry, LPTSTR pszDefault)
{
	int     cch;
	LPTSTR  pszRet;
	TCHAR   sz[MAX_PATH];

	cch = GetPrivateProfileString(gszAppName, pszEntry, pszDefault, sz, MAX_PATH, gszIniName);
	if (cch == 0)
	{
		if (NULL == pszDefault)
			return NULL;

		cch = lstrlen(pszDefault);
		lstrcpy(sz, pszDefault);
	}
	pszRet = PszAlloc(cch);
	if (pszRet == NULL)
		return NULL;

	lstrcpy(pszRet, sz);

	return pszRet;
}


//****************************************************************************
//
// VOID GetIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
//
// Convert the hex data into binary.
// If no entry is found, lpv isn't modified
//
//****************************************************************************
	
VOID GetIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
{
	TCHAR sz[MAX_PATH];

	if (GetPrivateProfileString(gszAppName, pszEntry, "", sz, MAX_PATH, gszIniName) != 0)
	{
		HexToData(sz, lpv, cb);
	}
}


//****************************************************************************
//
// VOID WriteIniStr(LPTSTR pszEntry, LPTSTR pszData)
//
// Write the data to an entry in the ini file
//
//****************************************************************************

VOID WriteIniStr(LPTSTR pszEntry, LPTSTR pszData)
{
	WritePrivateProfileString(gszAppName, pszEntry, pszData, gszIniName);
}


//****************************************************************************
//
// VOID WriteIniInt(LPTSTR pszEntry, DWORD dw)
//
// Write the numeric data to an entry in the ini file
//
//****************************************************************************

VOID WriteIniInt(LPTSTR pszEntry, DWORD dw)
{
	TCHAR szData[MAX_PATH];

	wsprintf(szData, TEXT("%d"), dw);
	WritePrivateProfileString(gszAppName, pszEntry, szData, gszIniName);
}


//****************************************************************************
//
// VOID WriteIniBool(LPTSTR pszEntry, BOOL f)
//
// Write the boolean value to an entry in the registery
//
//****************************************************************************

VOID WriteIniBool(LPTSTR pszEntry, BOOL f)
{
	WritePrivateProfileString(gszAppName, pszEntry, f ? TEXT("1") : TEXT("0"), gszIniName);
}


//****************************************************************************
//
// VOID WriteIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
//
//****************************************************************************
VOID WriteIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
{
	TCHAR sz[MAX_PATH];

	DataToHex((LPTSTR) lpv, sz, cb);

	WriteIniStr(pszEntry, sz);
}


//****************************************************************************
//
// VOID CenterWindow(HWND hwndChild, HWND hwndParent)
//
// Center a window over another window.
//
//****************************************************************************

VOID CenterWindow(HWND hwndChild, HWND hwndParent)
{
	int   xNew, yNew;
	int   cxChild, cyChild;
	int   cxParent, cyParent;
	int   cxScreen, cyScreen;
	RECT  rcChild, rcParent;
	HDC   hdc;

	// Get the Height and Width of the child window
	GetWindowRect(hwndChild, &rcChild);
	cxChild = rcChild.right - rcChild.left;
	cyChild = rcChild.bottom - rcChild.top;

	// Get the Height and Width of the parent window
	GetWindowRect(hwndParent, &rcParent);
	cxParent = rcParent.right - rcParent.left;
	cyParent = rcParent.bottom - rcParent.top;

	// Get the display limits
	hdc = GetDC(hwndChild);
	if (hdc == NULL) {
		// major problems - move window to 0,0
		xNew = yNew = 0;
	} else {
		cxScreen = GetDeviceCaps(hdc, HORZRES);
		cyScreen = GetDeviceCaps(hdc, VERTRES);
		ReleaseDC(hwndChild, hdc);

		if (hwndParent == hwndNil) {
			cxParent = cxScreen;
			cyParent = cyScreen;
			SetRect(&rcParent, 0, 0, cxScreen, cyScreen);
		}

		// Calculate new X position, then adjust for screen
		xNew = rcParent.left + ((cxParent - cxChild) / 2);
		if (xNew < 0) {
			xNew = 0;
		} else if ((xNew + cxChild) > cxScreen) {
			xNew = cxScreen - cxChild;
		}

		// Calculate new Y position, then adjust for screen
		yNew = rcParent.top  + ((cyParent - cyChild) / 2);
		if (yNew < 0) {
			yNew = 0;
		} else if ((yNew + cyChild) > cyScreen) {
			yNew = cyScreen - cyChild;
		}

	}

	SetWindowPos(hwndChild, NULL, xNew, yNew,	0, 0,
		SWP_NOSIZE | SWP_NOZORDER);
}


//****************************************************************************
//
// LPVOID LpvAlloc(int cb)
//
// Return a pointer to an allocated array of bytes
//
//****************************************************************************

LPVOID LpvAlloc(int cb)
{
	return LocalAlloc(LMEM_FIXED, cb);
}


//****************************************************************************
//
// LPTSTR PszAlloc(int cch)
//
//****************************************************************************

LPTSTR PszAlloc(int cch)
{
	return (LPTSTR) LocalAlloc(LMEM_FIXED, sizeof(TCHAR) * (cch+1));
}


//****************************************************************************
//
// VOID FreePlpv(LPVOID plpv)
//
// Free the data pointed to by plpv and set *plpv to NULL
//
//****************************************************************************

VOID FreePlpv(LPVOID plpv)
{
	if ((plpv == NULL) || (*(VOID FAR * FAR *)plpv == NULL)) {
		return;
	}

	LocalFree(*(VOID FAR * FAR *)plpv);
	*(VOID FAR * FAR *)plpv = NULL;
}


//****************************************************************************
//
// TCHAR ChFromHex(LPTSTR lpch)
//
// Convert from Hex data to ascii character
//
//****************************************************************************

TCHAR ChFromHex(LPTSTR lpch)
{
	int i = 0;
	int cch = 2;
	char ch;

	while (cch-- > 0) {
		ch = *lpch++;
		if (ch >= 'A') {
			i = (i*16) + (ch - ('A'-10));
		} else {
			i = (i*16) + (ch - '0');
		}
	}

	return (TCHAR) i;
}


//****************************************************************************
//
// VOID HexToData(LPTSTR lpchSrc, LPVOID lpvDest, int cb)
//
// Convert from Hex data to ascii character
//
//****************************************************************************

VOID HexToData(LPTSTR lpchSrc, LPVOID lpvDest, int cb)
{
	PTCHAR lpchDest = (PTCHAR) lpvDest;

	CharUpperBuff(lpchSrc, cb*2);

	while (cb-- > 0)
	{
		*lpchDest++ = ChFromHex(lpchSrc);
		lpchSrc += 2;
	}
}


//****************************************************************************
//
// LPSTR HexToBin(LPSTR lpchSrc, LPVOID lpvDest, int cb)
//
// Convert from Hex data to ascii character
//
//****************************************************************************

LPSTR HexToBin(LPSTR lpchSrc, LPVOID lpvDest, int cb)
{
	PTCHAR lpchDest = ((CHAR *) lpvDest) + cb;

	CharUpperBuff(lpchSrc, cb);

	while (cb-- > 0)
	{
		lpchDest--;
		*lpchDest = ChFromHex(lpchSrc);
		lpchSrc += 2;
	}
	return lpchSrc;
}

//****************************************************************************
//
// VOID DataToHex(LPTSTR lpchSrc, LPTSTR lpchDest, int cb)
//
//****************************************************************************

VOID DataToHex(LPTSTR lpchSrc, LPTSTR lpchDest, int cb)
{
	TCHAR ch;

	if (lpchSrc == lpNil)
	{
		SetEmptySz(lpchDest);
		return;
	}

	while (cb-- > 0) {
		ch = 0x00FF & (unsigned char) (*lpchSrc++);
		wsprintf(lpchDest, "%02X", ch);
		lpchDest += 2;
	}
}


//****************************************************************************
//
// VOID SetMenuCheck(UINT idm, BOOL fCheck)
//
// Set the menu item's check mark.
//
//****************************************************************************

VOID SetMenuCheck(UINT idm, BOOL fCheck)
{
	CheckMenuItem(ghMenu, idm,
		fCheck ? (MF_CHECKED  | MF_BYCOMMAND) : (MF_UNCHECKED | MF_BYCOMMAND));
}


//****************************************************************************
//
// VOID MaybeDeleteObject(HGDIOBJ * phgdi)
//
// Check usage count, delete if we can
//
//****************************************************************************

VOID MaybeDeleteObject(HGDIOBJ * phgdi)
{
	if (*phgdi == hgdiNil)
		return;

	DeleteObject(*phgdi);
	*phgdi = hgdiNil;	
}


static TCHAR _szFilter[] = TEXT("All Files\0*.*\0Text Files (*.txt)\0*.TXT\0");
static TCHAR _szPickMsg[] = TEXT("Pick a file to send");
static TCHAR _szPickDir[] = TEXT("Select a Directory");


//****************************************************************************
//
// BOOL FGetFileName(LPTSTR szFileName)
//
//****************************************************************************

BOOL FGetFileName(LPTSTR szFileName)
{
	OPENFILENAME ofn;

	SetEmptySz(szFileName);
	ClearStruct(&ofn);

	ofn.lStructSize   = sizeof(OPENFILENAME);
	ofn.hwndOwner     = ghwndMain;
	ofn.hInstance     = (HINSTANCE) ghInst;
	ofn.lpstrFilter   = _szFilter;
	ofn.nFilterIndex  = 1L;
	ofn.lpstrFile     = (LPSTR) szFileName;
	ofn.nMaxFile      = MAX_PATH; // really CCHMAX(szFileName)
	ofn.lpstrTitle    = _szPickMsg;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	if (!GetOpenFileName(&ofn))
		return FALSE;

	return TRUE;
}


//****************************************************************************
//
// BOOL FGetDirectory(LPTSTR szDir)
//
//****************************************************************************

BOOL FGetDirectory(LPTSTR szDir)
{
	BOOL  fRet;
	TCHAR  szPath[MAX_PATH];
	LPITEMIDLIST pidl;
	LPITEMIDLIST pidlRoot;
	LPMALLOC lpMalloc;

	BROWSEINFO bi = {
		ghwndMain,
		NULL,
		szPath,
		_szPickDir,
		BIF_RETURNONLYFSDIRS,
		NULL, 0L, 0	};

	if (0 != SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DRIVES, &pidlRoot))
		return FALSE;
	if (NULL == pidlRoot)
		return FALSE;

	bi.pidlRoot = pidlRoot;
	pidl = SHBrowseForFolder(&bi);

	if (NULL != pidl)
		fRet = SHGetPathFromIDList(pidl, szDir);
	else
		fRet = FALSE;

	// Get the shell's allocator to free PIDLs
	if (!SHGetMalloc(&lpMalloc) && (NULL != lpMalloc))
	{
		if (NULL != pidlRoot)
		{
			lpMalloc->Free(pidlRoot);
		}

		if (NULL != pidl)
		{
			lpMalloc->Free(pidl);
		}

		lpMalloc->Release();
	}

	return fRet;
}


//****************************************************************************
//
// VOID GetDlgItemPsz(HWND hdlg, UINT id, LPTSTR *ppsz)
//
// Get the text in the dialog item and retun a pointer to it in *ppsz.
// Note: Any previous data in ppsz is released.
//
//****************************************************************************

VOID GetDlgItemPsz(HWND hdlg, UINT id, LPTSTR *ppsz)
{
	UINT cch;
	TCHAR sz[MAX_PATH];

	FreePlpv(ppsz);
	cch = GetDlgItemText(hdlg, id, sz, CCHMAX(sz));
	if (0 == cch)
		return;
	*ppsz = (LPTSTR) PszAlloc(cch);
	if (NULL == *ppsz)
		return;

	lstrcpy(*ppsz, sz);
}


//****************************************************************************
//
// int GetRadioButton(HWND hdlg, int idrFirst, int idrLast)
//
//****************************************************************************

int GetRadioButton(HWND hdlg, int idrFirst, int idrLast)
{
	int id;

	for (id = idrFirst; id <= idrLast; id++)
	{
		if (IsDlgButtonChecked(hdlg, id))
			return id;
	}
	return idrFirst;
}

//****************************************************************************
//
// VOID GuidToSz(GUID * pguid, LPTSTR lpchDest)
//
// Convert the guid to a special hex string.
// Assumes lpchDest has space for at least sizeof(GUID)*2 +6 chars.
// LENGTH_SZGUID_FORMATTED is 30 and includes space for the null terminator.
//
// Note the difference between this and UuidToString (or StringFromGUID2)
//
// GUID Format: {12345678-1234-1234-1234-567890123456}
//
//****************************************************************************

VOID GuidToSz(GUID * pguid, LPTSTR lpchDest)
{
	ASSERT(NULL != pguid);
	ASSERT(NULL != lpchDest);

	wsprintf(lpchDest, TEXT("{%08X-%04X-%04X-%02X%02X-"),
		pguid->Data1, pguid->Data2, pguid->Data3, pguid->Data4[0], pguid->Data4[1]);
	lpchDest += 1+8+1+4+1+4+1+2+2+1;

	for (int i = 2; i < 8; i++)
	{
		wsprintf(lpchDest, TEXT("%02X"), pguid->Data4[i]);
		lpchDest += 2;
	}
	lstrcpy(lpchDest, TEXT("}") );
}


//****************************************************************************
//
// VOID SzToGuid(LPTSTR lpchSrc, GUID * pguid)
//
//****************************************************************************

VOID SzToGuid(LPTSTR lpchSrc, GUID * pguid)
{
	if (FEmptySz(lpchSrc) || (lstrlen(lpchSrc) < sizeof(GUID)*2))
	{
		ClearStruct(pguid);
		return;
	}

	ClearStruct(pguid);

	if (_T('{') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data1, sizeof(pguid->Data1));
	if (_T('-') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data2, sizeof(pguid->Data2));
	if (_T('-') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data3, sizeof(pguid->Data3));
	if (_T('-') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data4[0], sizeof(BYTE));
	lpchSrc = HexToBin(lpchSrc, &pguid->Data4[1], sizeof(BYTE));
	if (_T('-') != *lpchSrc++)
		return;
	HexToData(lpchSrc, &pguid->Data4[2], sizeof(pguid->Data4) - 2*sizeof(BYTE));
}
	

//****************************************************************************
//
// LPTSTR SzFindLastCh(LPTSTR lpsz, TCHAR ch)
//
// Returns a pointer to the ch within the lpsz or NULL if not found
//
//****************************************************************************

LPTSTR SzFindLastCh(LPTSTR lpsz, TCHAR ch)
{
	LPTSTR lpchRet;

	for (lpchRet = NULL; *lpsz; lpsz = CharNext(lpsz))
	{
		if (ch == *lpsz)
			lpchRet = lpsz;
	}

	return lpchRet;
}

