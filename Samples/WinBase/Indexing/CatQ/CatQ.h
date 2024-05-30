//
// catq.h - common defines and function prototypes for the catq sample.
//


//
// function prototypes for the window procedures.
//

LRESULT CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);


//
// forward declare other helper functions
//

int catqReportError ( int );
int catqLogComment ( PTCHAR );
void _cdecl catqLogCommentVariable ( PTCH, ... );
void _cdecl catqReportResultsVariable( PTCH, ... );
int catqInitializeSDKPath ( HWND, LPTSTR );
int catqInitializeCatalogs ( HWND, LPTSTR );

int catqStartCIService ( HWND );

int catqCreateStatusBar ( HWND );
int catqPartitionStatusBar ( HWND );
int catqUpdateProgress( HWND, int, LONG, LONG );
int catqUpdateStatusComment(HWND hwndStatusBar, LPTSTR lpszStatusString);

int catqPDHQueryProgress ( LPLONG, LPLONG  );

HRESULT DoQuery(
    WCHAR const * pwcQueryCatalog,
    WCHAR const * pwcQueryMachine,
    WCHAR const * pwcQueryScope,
    WCHAR const * pwcQueryRestriction);


//
// Possible return value from catqPDHQueryProgress()
//

#define CATQ_PROGRESS_ERROR -1


//
// IDs for the controls on the main dialog
//

#define DID_MACHINE      1001
#define DID_CATALOG      1002
#define DID_CONTAIN      1003
#define DID_SCOPE        1004
#define DID_OUTRESULTS   1020
#define DID_FINDNOW      1030
#define DID_STATUSBAR    1040
#define DID_PROGRESSBAR  1041


//
// Timer ID
//

#define TID_PROGRESS     2057


//
// Application defined window messages for "message based" communication
//  to/from the main window.
//

#define WMAPP_ADDRESULT         WM_APP + 10


#define SZ_APP_TITLE TEXT("Content Index Query Tool")


//
// The following string is the formal name of the content indexing service.
//  It is defined here for use in starting the service if necessary.
//

#define SZ_CISERVICE_NAME  TEXT("CISVC")
