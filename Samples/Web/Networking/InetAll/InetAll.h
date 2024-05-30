///////////////////////////////////////////////////////
/*
 *  inetall.h
 *
 *  Written by Microsoft Developer Support
 *
 *  Copyright (C) 1999 Microsoft Corporation. All rights reserved
 *
 *  Header file for inetall.cpp.  
 */
//////////////////////////////////////////////////////

  
//dialog box control id for rc file
///////////////////////////////////////////////////////
#define IDC_STATIC 						-1
#define IDD_INETALL_DIALOG              102
#define IDR_MAINFRAME                   128
#define IDB_BMERR                       130
#define IDB_BMDIR                       131
#define IDB_BMFILE                      132
#define IDC_HTTP                        1000
#define IDC_FTP                         1001
#define IDC_FILE                        1002
#define IDC_URL                         1006
#define IDC_USERNAME                    1007
#define IDC_PASSWORD                    1008
#define IDC_HTML                        1009
#define IDC_GETDATA                     1010
#define IDC_TREE1                       1012
#define IDC_CERN                        1013

///////////////////////////////////////////////////////
#define MAX_STRING_SIZE					1024
#define SERVICE_TYPE_HTTP				1
#define SERVICE_TYPE_FTP				2
#define SERVICE_TYPE_FILE				3

HINSTANCE g_hInst;	//Application Instance
HWND g_hDlg;		//main dialogbox window handle
TCHAR szFullUrl[MAX_STRING_SIZE]; 

//ItemAttrib, and CMyItemArray: data structures for enumerating
//FTP URL and FILE URL
typedef struct _tagItemAttrib 
{
	TCHAR			szObjectPath[MAX_STRING_SIZE];
	int				nObjectType; //0 file object, 1 directory object
} ItemAttrib, *PItemAttrib;

//Implements only the minimal functions needed for maintaining items 
//info in the tree control. 
class CMyItemArray 
{
public:
	CMyItemArray();	// standard constructor
	~CMyItemArray();
	
	int Add(ItemAttrib& item); //return Item index
	void RemoveAll();
	ItemAttrib GetAt(int nIndex);
	int GetSize();

private:
	PItemAttrib m_pItemlist;
	int m_nCount;	
};

typedef struct _tagINETALLBAG
{
	HIMAGELIST	hImgList;
	HWND		hTreeViewCtrl; 
	HTREEITEM	m_curItem;

	HWND		hCheckBoxCern;
	BOOL		m_cern;

	DWORD		m_dwServiceType;

	HWND		hwndUrl;
	TCHAR		m_url[MAX_STRING_SIZE];
	HWND		hwndPassword;
	TCHAR		m_password[MAX_STRING_SIZE];
	HWND		hwndUsername;
	TCHAR		m_username[MAX_STRING_SIZE];
	
	HWND		hwndHTML;	
	LPTSTR		m_phtml;
	DWORD		m_dwSizeHtml;
	CMyItemArray	m_itemArray;

	BOOL		m_bRedrawTree;
	//TRUE delete all items in the tree control and add new items.
	//FALSE add new items as the sub items to the hCurItem

} INETALLBAG, *PINETALLBAG;

INETALLBAG g_Inet;

//Update UI or Collect input from UI
//bDirection FALSE g_Inet to UI
//bDirection TRUE UI to g_Inet
//Helper function similar to MFC UpdateData
BOOL UpdateUI(BOOL bDirection); 

//Enumerate strURL, and populate g_Inet.m_itemArray
BOOL FillFtpOrFileObjArray(HINTERNET InternetSession, LPTSTR strURL);

//Draw the TreeView control using g_Inet.m_itemArray
void FillTreeControl();
