// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__CBFE257B_B030_11D0_B188_00AA00BA3258__INCLUDED_)
#define AFX_STDAFX_H__CBFE257B_B030_11D0_B188_00AA00BA3258__INCLUDED_

#if _MSC_VER >= 1000
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
#define STRICT


#define _WIN32_WINNT 0x0500
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
};
extern CExeModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <atlwin.h>
#define SafeRelease(pUnk) {if (pUnk){pUnk -> Release();pUnk = NULL; }}

#endif // _MSC_VER >= 1000
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CBFE257B_B030_11D0_B188_00AA00BA3258__INCLUDED)
