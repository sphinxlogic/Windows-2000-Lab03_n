//
// MAPILogon.h
//

#ifndef MAPI_LOGON_H
#define MAPI_LOGON_H

#include <mapix.h>

struct MailID 
{ 
	ULONG       ulType ; 
	ULONG       cbEntryID  ; 
	LPENTRYID   lpEntryID   ; 
	LPTSTR      lpszDisplayName; 
}; 
 
typedef struct MailID SMailID; 
 
CONST UINT  cxSmallIcon = 16; 
CONST UINT  cySmallIcon = 16; 

// Exchange image list indicies 
enum 
{ 
	iimlExchange, 
	iimlExchangeOpen, 
	iimlMdb, 
	iimlMdbOpen, 
	iimlFolder, 
	iimlFolderOpen, 
	iimlDefaultMdb, 
	iimlDefaultMdbOpen, 
	cimlExchange 
}; 
 

class CMAPILogon
{ 
public: 
	CMAPILogon(); 
	virtual ~CMAPILogon(); 

// Attributes 
public: 
	LPADRBOOK		m_lpAdrBook; 
	LPMAPISESSION	m_lpSession; 
	BOOL			m_fMAPIInitialized; 
	LPMAPIFOLDER	m_lpTempFld; 
	LPMDB *			m_lppMDB; 
	ULONG *			m_pcbeidStore; 
	LPENTRYID *		m_lppeidStore; 
	ULONG			m_nMaxStores; 
 
	LPTSTR			m_lpszProfileName;

	// Summary information 
	CString			m_szFile; 
	CString			m_szFileTitle; 
	CString			m_psTitle ; 
	CString			m_psAuthor;     
	CString			m_psComments;   
	CString			m_psKeywords;   
	CString			m_psSubject;    
 
// Operations 
public: 
	
	HRESULT InitializeProfileName();
	HRESULT HrInitialize(HWND hWnd); 
	HRESULT HrUninitialize(); 
	HRESULT OpenMsgStore(ULONG cbeid, LPENTRYID  peid, LPMDB *lppMDB); 
	void LogoffMessageStore(VOID); 
	
   
}; 
 

#endif // #ifndef MAPI_LOGON_H
 
///////////////////////////////////////////////////////////////////////////// 
 
