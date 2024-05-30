
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
#if !defined(AFX_LOGPARSE_H__F7BCDEE3_DE91_11D0_BB1C_00C04FB66F63__INCLUDED_)
#define AFX_LOGPARSE_H__F7BCDEE3_DE91_11D0_BB1C_00C04FB66F63__INCLUDED_

// LOGPARSE.H - Header file for your Internet Server
//    LogParse Extension

#include "resource.h"

const GUID CLSID_StdEncodingFilterFac = {0x54c37cd0,0xd944,0x11d0,{0xa9,0xf4,0x00,0x60,0x97,0x94,0x23,0x11}};
const GUID IID_IEncodingFilterFactory = {0x70bdde00,0xc18e,0x11d0,{0xa9,0xce,0x00,0x60,0x97,0x94,0x23,0x11}};

static const TCHAR c_szEncodingType[] = _T("HTTP_CONTENT_TRANSFER_ENCODING");

static const TCHAR g_szRegW3SVC[] 
          = _T("SYSTEM\\CurrentControlSet\\Services\\W3SVC\\Parameters");
static const TCHAR g_szRegLogFileDirectory[]
          = _T("LogFileDirectory");
static const TCHAR g_szLogFilePath[]
          = _T("\\ie4\\");

static const TCHAR g_szFields[]    = _T("#Fields: ");
static const TCHAR g_szURIFields[] = _T("#Fields: s-URI ");
static const TCHAR g_szURI[]       = _T("s-URI ");
static const TCHAR g_szContext[]   = _T("x-context ");
static const TCHAR g_szCache[]     = _T("x-cache ");
static const TCHAR g_szDate[]      = _T("x-date ");
static const TCHAR g_szTime[]      = _T("x-time ");
static const TCHAR g_szDuration[]  = _T("x-duration ");
static const TCHAR g_szMeta[]      = _T("x-meta ");

#define interselog_cookiename "INTERSE"

#define sizeof_header   4096
/*
 * The "name" of the cookie assigned to each user. We strongly recommend that
 * the default value (INTERSE) be used. This value can be set to anything, but
 * once set, should never be changed. If you have used previous versions of
 * this Intersé ISAPI extension and have used a different cookie name before,
 * you will need to edit the cookie name to specify the name that you had used
 * with the previous release.
 *
 */

class CLogParseExtension : public CHttpServer
{
public:
	CLogParseExtension();
	~CLogParseExtension();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CLogParseExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL

	// TODO: Add handlers for your commands here.
	// For example:

    void    LogParse(CHttpServerContext* pCtxt, LPTSTR pszString);

    DECLARE_PARSE_MAP()

    protected:
    BOOL    OpenLogFile(CHttpServerContext* pCtxt);
    DWORD   AppendContentToLogfile(CHttpServerContext* pCtxt, LPCTSTR pszContent, DWORD ContentLen, BOOL fEncoded);
    BOOL    DecodeContent(CHttpServerContext* pCtxt, LPCTSTR pszEncodedString, DWORD cbEncode, 
                            LPTSTR pszDecString, DWORD cbDecode);
    DWORD   ConvertToW3CFlexible(CHttpServerContext* pCtxt, LPTSTR pszClientLog);
    DWORD   ProcessFixedLogFields(CHttpServerContext* pCtxt);
    BOOL    GetUserCookie(CHttpServerContext* pCtxt, LPTSTR pszCookie, LPDWORD pcb);
    DWORD   ProcessClientLog(CHttpServerContext* pCtxt, LPTSTR pszClientLog, LPDWORD pMove);

    private:
    HANDLE  m_hFile;
    DWORD   m_ContentLen;
    LPTSTR  m_szEncoding;
    TCHAR   m_szLogFile[MAX_PATH*2];

    DWORD   m_cbURILen;
    DWORD   m_cbLogLen;
    BOOL    m_fInLog;
    //{{AFX_MSG(CLogParseExtension)
	//}}AFX_MSG
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGPARSE_H__F7BCDEE3_DE91_11D0_BB1C_00C04FB66F63__INCLUDED)
