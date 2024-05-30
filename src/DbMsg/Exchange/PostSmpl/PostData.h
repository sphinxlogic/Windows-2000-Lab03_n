//=========================================================================
// PostData.H
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    interface of the CPostData class
//=========================================================================



/////////////////////////////////////////////////////////////////////////////
// CPostData window

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


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPostData window

class CPostData : public CWnd
{
// Construction
public:
	CPostData();

// Attributes
public:
 	LPADRBOOK m_lpAdrBook;
	LPMAPISESSION m_lpSession;
	BOOL fMAPIInitialized;
	
	LPMAPIFOLDER m_lpTempFld;
	CImageList m_obImageListExchange;
	LPMDB		*m_lppMDB;	
	ULONG		*m_pcbeidStore;
	LPENTRYID	*m_lppeidStore;
	ULONG		nMaxStores;

	// Summary information
	CString	szFile;
	CString	szFileTitle;
	CString m_psTitle ;
	CString m_psAuthor;    
	CString m_psComments;  
	CString m_psKeywords;  
	CString m_psSubject;   
	
	

// Operations
public:
 	HRESULT HrInitialize();
	HRESULT HrUninitialize();
	HRESULT OpenMsgStore(ULONG cbeid, LPENTRYID  peid, LPMDB *lppMDB);
	void LogoffMessageStore(VOID);
	BOOL CreateImageListExchange();
	BOOL FilePost(LPSTORAGE pstg);
	void CreateAndPostMessage();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostData)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPostData();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPostData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CPostData	PostData;

/////////////////////////////////////////////////////////////////////////////
