// ICSAgentWiz.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "ICSAgentWiz.h"
#include "ICSAgentWizaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE ICSAgentWizDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("ICSAGENTWIZ.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(ICSAgentWizDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(ICSAgentWizDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&ICSAgentWizaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("ICSAGENTWIZ.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(ICSAgentWizDLL);
	}
	return 1;   // ok
}

//
// The following utility functions are used to add MACROs
// to this project by modifying the m_Dictionary 
// (See MSDN documentation)
//
void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	ICSAgentWizaw.m_Dictionary[lpszKey] = lpszValue;
}

void UndefMacro(LPCTSTR lpszKey)
{
	ICSAgentWizaw.m_Dictionary.RemoveKey(lpszKey);
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
