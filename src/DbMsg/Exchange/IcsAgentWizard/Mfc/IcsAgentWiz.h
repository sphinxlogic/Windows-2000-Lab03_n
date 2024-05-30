#if !defined(AFX_ICSAGENTWIZ_H__8CCE97AC_2B15_11D2_9879_00C04FAE2339__INCLUDED_)
#define AFX_ICSAGENTWIZ_H__8CCE97AC_2B15_11D2_9879_00C04FAE2339__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue);
void UndefMacro(LPCTSTR lpszKey);

void DefineIntMacro(LPCTSTR pszKey, int iValue);
void DefineIntMacro(LPCTSTR pszKey, int iItem, int iValue);
void DefineBoolMacro(LPCTSTR pszKey, BOOL bValue=TRUE);
void DefineBoolMacro(LPCTSTR pszKey, int iItem, BOOL bValue);
void DefineStringMacro(LPCTSTR pszKey, LPCTSTR pszValue);
void DefineStringMacro(LPCTSTR pszKey, int iItem, LPCTSTR pszValue);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICSAGENTWIZ_H__8CCE97AC_2B15_11D2_9879_00C04FAE2339__INCLUDED_)
