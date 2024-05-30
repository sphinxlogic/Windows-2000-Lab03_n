//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       ilstest.h
//  Content:    The main header file.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <olectl.h>
#include "ils.h"
#include "resource.h"
#include <commctrl.h>
#include "oblist.h"
#include "notify.h"
#include <mapidefs.h>

//****************************************************************************
// General Constants
//****************************************************************************
//
#define SERVER_MENU_POS 1
#define SERVER_LIST_POS 2

#define MAX_NAME 260
#define MAX_SERVER_COUNT 20
#define MAX_USER_COUNT 20


#define WM_ILSTEST                  (WM_USER+100)
#define WM_IT_ENUM_NAMES_RESULT     (WM_ILSTEST+0)
#define WM_IT_ENUM_USERS_RESULT     (WM_ILSTEST+1)
#define WM_IT_RESOLVE_USER_RESULT   (WM_ILSTEST+2)
#define WM_IT_RESOLVE_PROT_RESULT   (WM_ILSTEST+3)

//****************************************************************************
// Macros
//****************************************************************************
//
#define ARRAYSIZE(array)    (sizeof(array)/sizeof(array[0]))

//****************************************************************************
// Global Parameters
//****************************************************************************
//
extern HINSTANCE         ghInstance;
extern HWND              g_hwndMain;
extern LPILS_MAIN        g_pIls;
extern IConnectionPoint  *g_pcnp;

extern IIlsFilter        *g_pProtFilter;
extern IIlsFilter        *g_pUserFilter;

extern CHAR              g_szServer[];
extern LPTSTR            g_pszServer;
extern IIlsServer        *g_pServer;
extern COBLIST           *g_pServerList;
extern COBLIST           *g_pUserList;

extern GUID g_GUID;

extern const TCHAR g_szAppID[];
extern const TCHAR g_szProtID[];

enum OBJECT_TYPE {PROTOCOL, USER};
enum FILTER_USAGE {USERFILTER, PROTFILTER};

#define NM_IN_A_CALL   400
#define NM_SEND_AUDIO  501
#define NM_SEND_VIDEO  503
#define NM_RESTRICTION 600


//****************************************************************************
// Useful data structures
//****************************************************************************
//

typedef struct tagServerNode
{
	char        szName[MAX_NAME];
	IIlsServer  *pSrv;
} SERVERNODE, *PSERVERNODE;

typedef struct tagUserInfo
{
	char        szFirstName[MAX_NAME];
	char        szLastName[MAX_NAME];
	char        szEmailName[MAX_NAME];
	char        szCity[MAX_NAME];
	char        szCountry[MAX_NAME];
	char        szComment[MAX_NAME*2];
	char        szIPAddress[MAX_NAME];
	BOOL		fModify;
} USERINFO, *PUSERINFO;

typedef struct  tagILSUser {
	IIlsUser        *pu;
	CIlsUserNotify  *puNotify;
	COBLIST         *pProtList;
}   USERNODE, *PUSERNODE;

typedef struct  tagServerInfo {
	LPTSTR      szServerName;
	LPTSTR      szLogonName;
	LPTSTR      szPassword;
	ILS_ENUM_AUTH_METHOD eam;
	LPTSTR      szDomain;
	LPTSTR      szCredential;
	LPTSTR      szBaseDN;
	DWORD       dwTimeout;
}   SERVERINFO, *PSERVERINFO;

typedef struct  tagFilterInfo {

	ILS_STD_ATTR_NAME attName1;
	LPTSTR            szValue1;
	ILS_FILTER_OP     fOp1;
	
	ILS_STD_ATTR_NAME attName2;
	LPTSTR            szValue2;
	ILS_FILTER_OP     fOp2;
	
	ILS_FILTER_OP     fOpComp;
	FILTER_USAGE      fUsage;     // usage: USER, PROTOCOL
	ILS_FILTER_TYPE   fType;      // type:  SIMPLE, COMPOSITE
	
}   FILTERINFO, *PFILTERINFO;

typedef struct  tagProtocolInfo {

	LPTSTR     szProtName;
	LPTSTR     szProtMime;
	ULONG      uPortNumber;       
	
}   PROTOCOLINFO, *PPROTOCOLINFO;


typedef struct  tagEnumProtocol {

	USERNODE  *pun;
	IIlsProtocol *ppSelected;
	
}   ENUMPROTINFO, *PENUMPROTINFO;


//****************************************************************************
// Function prototypes
//****************************************************************************
//
// ****  from utils.cpp
void      _cdecl MyTextOut (LPCTSTR szFmt, ...);
void      ErrorMessage(HWND hwnd, LPCTSTR szPrefix, HRESULT hr);
LPTSTR    AllocLPTSTR (ULONG cb);
HRESULT   FreeLPTSTR (LPTSTR pszName);
HRESULT   SetLPTSTR (LPTSTR *ppszName, LPCTSTR pszUserName);
HRESULT   LPTSTR_to_BSTR (BSTR *pbstr, LPCTSTR psz);
HRESULT   BSTR_to_LPTSTR (LPTSTR *ppsz, BSTR bstr);
LPCTSTR   GetErrorString(HRESULT hr);
void      DisplayStdAtt(void *pobj, ILS_STD_ATTR_NAME stdAttr, LPTSTR szDesc, OBJECT_TYPE ot);
void      DisplayExtAtt(void *pobj, DWORD dwExtAttr, LPTSTR szDesc, OBJECT_TYPE ot);
BOOL      InitTreeViewImageLists(HWND hwndTV); 
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, int nLevel);
VOID      DisplayAboutBox(HWND hwnd);
HRESULT   DisplayIlsNames(HWND hwnd, IEnumIlsNames *pEnum, LPTSTR szNames);
int       StringFromGuid (REFIID riid, LPTSTR pszBuf);
int       GetRadioButton(HWND hdlg, int idrFirst, int idrLast);
BOOL      MyIsGoodString(LPTSTR psz);
HRESULT   GetNMAttributesObject( IIlsMain *pIls, IIlsAttributes **ppa );




// ****  from users.cpp
HRESULT DisplayIlsUsers(HWND hwnd, IEnumIlsUsers *pEnum);
HRESULT RegisterUser(HWND hwnd, IIlsUser *pu, IIlsServer *ps, LPTSTR szServerName);
HRESULT UnregisterUser(HWND hwnd, IIlsUser *pu, BOOL fSilent);
HRESULT EnumUsers(HWND hwnd, BOOL fShort);
HRESULT OnILSUserAdviseUnadvise(HWND hwnd, PUSERNODE pUserNode, BOOL fAdvise);
HRESULT DisplayIlsUserDialog(HWND hwnd, IIlsUser *pu);
 


// ****  from svrinfo.cpp
int     ServerDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT NewServerDialog(HWND hwnd);
HRESULT RemoveServerDialog(HWND hwnd);
void    NewServerNode(IIlsServer *pServer, LPTSTR szName);
int     ServerListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void    SetServerInfo(HWND hwnd, IIlsServer *ps, PSERVERINFO psi);


// ****  from usrinfo.cpp
HRESULT NewUserDialog(HWND hwnd);
HRESULT ModifyUserDialog(HWND hwnd);
HRESULT CloneUserDialog(HWND hwnd);
HRESULT RemoveUserDialog(HWND hwnd);
HRESULT RegUnregUserDialog(HWND hwnd, BOOL fRegister);
int     UserNameDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT GetUserInfoDialog(HWND hwnd);
HRESULT GetUserInfoDialog(HWND hwnd, IIlsUser *pu);
int     UserDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void    InitIlsUser(HWND hwnd, IIlsUser *pu);
void    NewUserNode(PUSERNODE pUser);
void    SetUserInfo(HWND hwnd, IIlsUser *pu, USERINFO *pUserInfo);
void    GetUserInfo(HWND hwnd, IIlsUser *pu, USERINFO *pUserInfo);
void    SaveUserInfo(HWND hwnd, PUSERINFO pui);
int     UserListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void    UnregisterAllUsers(HWND hwnd);
HRESULT ChangeAttribute(IIlsUser *pu, ILS_STD_ATTR_NAME attr, LPTSTR psz);



// ****  from proto.cpp
HRESULT EnumUserProtocols(HWND hwnd, IIlsUser *pu);
int     ProtocolDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void    CreateProtocolDialog(HWND hwnd);
void    SaveProtInfo(HWND hwnd, PPROTOCOLINFO ppi);
void    DestroyProtocolDialog(HWND hwnd);
int     ProtoListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT DisplayProtocolInfo(HWND hwnd, IIlsProtocol *pp);
HRESULT DisplayProtocol(HWND hwnd, IIlsUser *pu);
int     ProtoNameDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);






// ****  from attrib.cpp
HRESULT EnumUserExAttributes(HWND hwnd, IIlsUser *pu);


// ****  from filter.cpp
HRESULT CreateFilterDialog(HWND hwnd, FILTER_USAGE fUsage);
int     FilterDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT DestroyFilter(HWND hwnd, FILTER_USAGE fUsage);

