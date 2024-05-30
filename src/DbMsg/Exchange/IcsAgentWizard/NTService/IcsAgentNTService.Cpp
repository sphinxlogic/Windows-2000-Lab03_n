// ICSAgentNTService.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "ICSAgentNTService.h"
#include "ICSAgentNTServiceaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE ICSAgentNTServiceDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("ICSAGENTNTSERVICE.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(ICSAgentNTServiceDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(ICSAgentNTServiceDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&ICSAgentNTServiceaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("ICSAGENTNTSERVICE.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(ICSAgentNTServiceDLL);
	}
	return 1;   // ok
}

void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	ICSAgentNTServiceaw.m_Dictionary[lpszKey] = lpszValue;
}

void UndefMacro(LPCTSTR lpszKey)
{
	ICSAgentNTServiceaw.m_Dictionary.RemoveKey(lpszKey);
}

// These are more specific macro-setting functions.  They set macros
//  depending on the "type", and work correctly in $$BEGINLOOP/$$ENDLOOP
//  blocks.

static void MakeKey(CString& strKey, int iItem)
{
	CString strOriginal = strKey;
	strKey.Format(_T("%s_%d"), (LPCTSTR) strKey, iItem);
}

void DefineIntMacro(LPCTSTR pszKey, int iValue)
{
	CString strValue;
	strValue.Format(_T("%d"), iValue);
	DefineMacro(pszKey, strValue);
}

void DefineIntMacro(LPCTSTR pszKey, int iItem, int iValue)
{
	CString strKey(pszKey);
	MakeKey(strKey, iItem);
	DefineIntMacro(strKey, iValue);
}

void DefineBoolMacro(LPCTSTR pszKey, BOOL bValue)
{
	if (bValue)
		DefineMacro(pszKey, _T("1"));
	else
		UndefMacro(pszKey);
}

void DefineBoolMacro(LPCTSTR pszKey, int iItem, BOOL bValue)
{
	CString strKey(pszKey);
	MakeKey(strKey, iItem);
	DefineBoolMacro(strKey, bValue);
}

void DefineStringMacro(LPCTSTR pszKey, LPCTSTR pszValue)
{
	DefineMacro(pszKey, pszValue);
}

void DefineStringMacro(LPCTSTR pszKey, int iItem, LPCTSTR pszValue)
{
	CString strKey(pszKey);
	MakeKey(strKey, iItem);
	DefineStringMacro(strKey, pszValue);
}
