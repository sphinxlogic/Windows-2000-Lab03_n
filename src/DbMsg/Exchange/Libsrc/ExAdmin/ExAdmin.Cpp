// -----------------------------------------------------------------------------
// ExAdmin.CPP: Implements methods which support Exchange Admin Configuration 
//              Extension Dialogs.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#if defined(UNICODE) || defined(_UNICODE)
#error EXADMIN cannot be compiled in UNICODE.
#endif

#include "edkafx.h"
#include "ExAdmin.h"
#include "helpers.h"
#include "ErrCpp.H"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------------------------
// Following is used to determine the languages we support

struct EnumLangParams
{
	WORD langRequested;
	BOOL fFound;
};
typedef EnumLangParams	*PEnumLangParams;

BOOL CALLBACK  EnumResTypesCallback(HANDLE hModule,LPTSTR lpszType,LONG lParam);
BOOL CALLBACK  EnumResNamesCallback(HANDLE hModule, LPCTSTR lpszType,
				   LPTSTR lpszName, LONG lParam);
BOOL CALLBACK  fEnumLangProc(HANDLE hMod, LPCTSTR ptzType, LPCTSTR ptzName, WORD wLang, LONG lParam);

// -----------------------------------------------------------------------------

__inline HRESULT CHK_HrGeneral(
    IN VOID* pvExtensionData,       // Extension data for all sheets
    IN HWND  hDlg)                  // Window handle of the property sheet.
{
    if( !hDlg)
        RETURN( E_INVALIDARG);

    return( NOERROR);
}

// -----------------------------------------------------------------------------

__inline HRESULT CHK_bInitSheet(
    IN  ADMIN_ObjectInfo* poi,              // Server name & other DNs.
    IN  ULONG             fFlags,                       
    OUT ADMIN_SheetInfo** ppSheetInfo,      // Property sheet description array
    OUT UINT*             pcsi,             // Number of property sheets
    OUT VOID**            ppvNotUsed) // Local data (NOT USED)
{
    if( !TEST_READ_PTR( poi, sizeof( ADMIN_ObjectInfo)))
        RETURN( E_INVALIDARG);

    if( !TEST_WRITE_PTR( ppSheetInfo, sizeof( VOID *)))
        RETURN( E_INVALIDARG);

    if( !TEST_WRITE_PTR( pcsi, sizeof( UINT)))
        RETURN( E_INVALIDARG);
    
    if( !TEST_WRITE_PTR( ppvNotUsed, sizeof( VOID *)))
        RETURN( E_INVALIDARG);

    return( NOERROR);
}

// -----------------------------------------------------------------------------

__inline HRESULT CHK_ADMIN_Initialize(
    IN  ADMIN_AdministratorConnections* pAdminConnections,  // Global Administrator Connections
    IN  ADMIN_AdministratorFunction*    pAdminFunctions,    // Global admin function
    OUT ADMIN_ExtensionFunction**       ppExtensionFunction)// Global Extension function
{
    if( !TEST_READ_PTR( pAdminConnections, sizeof( ADMIN_AdministratorConnections)))
        RETURN( E_INVALIDARG);

    if( !TEST_READ_PTR( pAdminFunctions, sizeof( ADMIN_AdministratorFunction)))
        RETURN( E_INVALIDARG);

    if( !TEST_WRITE_PTR( ppExtensionFunction, sizeof( VOID *)))
        RETURN( E_INVALIDARG);

    if( !TEST_FUNCTION_PTR( (FARPROC) pAdminFunctions->pfnGetObjectData))
        RETURN( E_INVALIDARG);

    return( NOERROR);
}

// -----------------------------------------------------------------------------

__inline HRESULT CHK_LoadStringA(
	UINT wID,			// ID of resource
	LPSTR szBuf,		// Buffer to store resource
	int cchBuf)			// Size of buffer in chars
{
    if( wID == 0)
        RETURN( E_INVALIDARG);

    if( !TEST_WRITE_PTR( szBuf, cchBuf))
        RETURN( E_INVALIDARG);

    return( NOERROR);
}   

__inline HRESULT CHK_LoadStringW(
	UINT wID,			// ID of resource
	LPWSTR wzBuf,		// Buffer to store resource
	int cchBuf)			// Size of buffer in chars
{
    if( wID == 0)
        RETURN( E_INVALIDARG);

    if( !TEST_WRITE_PTR( wzBuf, sizeof( WCHAR ) * cchBuf))
        RETURN( E_INVALIDARG);

    return( NOERROR);
}   

//$--CInitDLL::InitInstance()---------------------------------------------------
// MFC initialization for the DLL.  No multi-threaded code allowed.
// -----------------------------------------------------------------------------

BOOL CInitDLL::InitInstance()
{
    // Any DLL initialization goes here.
    TRACE0("InitDLL.DLL initializing\n");
    SetDialogBkColor();     // Grey dialogs in the DLL as well.
    return TRUE;
}

//$--CInitDLL::ExitInstance()---------------------------------------------------
// Exit MFC for the DLL gracefully.  No multi-threaded code allowed.
// -----------------------------------------------------------------------------

int CInitDLL::ExitInstance()
{
    // Any DLL termination goes here (WEP-like code).
    return CWinApp::ExitInstance();
}

//$--CInitDLL::~CInitDLL()------------------------------------------------------
// Detach from property sheet window of Admin program then delete the CWnd we 
// created in AdminDlgProc().  The reason we attach to the property sheet window
// of admin is so that MFC will give us Modal dialog boxes.
// -----------------------------------------------------------------------------

CInitDLL::~CInitDLL()
{
    if( m_pMainWnd)
    {
        m_pMainWnd->Detach();
        delete m_pMainWnd;
        m_pMainWnd = NULL;
    }
}

//$--CAdmin::HrSubclassWindow()-------------------------------------------------
// Make subclassing windows to controls with error checking a little easier.
// -----------------------------------------------------------------------------

HRESULT CADialog::HrSubclassWindow( 
    int   nID,  // Id of a control in this dialog.
    CWnd& Wnd)  // Reference to MFC CWnd object to connect to Windows control.
{
    CWnd* pWnd = GetDlgItem( nID);
    if( !pWnd)
    {   // Could not find id (%d) of control in dialog.
        RETURN( E_FAIL);
    }

    // Connect the windows control to a MFC CWnd derived object.
    Wnd.SubclassWindow( pWnd->GetSafeHwnd());
    return( NOERROR);
}

//$--AdminDlgProc()-------------------------------------------------------------
// Subclasses the dialog the first time in and always calls the MFC dialog proc
// to handle the message. When message == WM_INITDIALOG then lParam is a pointer
// to the CAdminDialog.
// -----------------------------------------------------------------------------

LRESULT CALLBACK AdminDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if( message == WM_INITDIALOG)
    {   // First time using this dialog so subclass its window so that MFC
        // code will work as expected.
        CAdminDialog* pAdminDlg = (CAdminDialog*) lParam;
        pAdminDlg->SubclassWindow( hDlg);

        // We attach to the property sheet window of admin so that MFC will give us 
        // modal dialog boxes.  We don't want to subclass this window because we 
        // would start receiving it's messages and we don't want that.
        if( !AfxGetApp()->m_pMainWnd)
        {   // We only need to do this once.
            AfxGetApp()->m_pMainWnd = new CWnd;
            AfxGetApp()->m_pMainWnd->Attach( GetParent( hDlg));
        }
    }

    // Prepare to call MFC dialog proc to handle the message.
    MSG msg;
    msg.hwnd = hDlg;
    msg.message = message;
    msg.wParam = wParam;
    msg.lParam = lParam;

    return( AfxDlgProc( hDlg, message, wParam, lParam));
}

// -----------------------------------------------------------------------------
// Message map for CAdminDialog.
// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CAdminDialog, CDialog)
    //{{AFX_MSG_MAP(CAdminDialog)
    ON_MESSAGE( WM_CHILDACTIVATE, OnChildActivate)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//$--CAdminDialog::CAdminDialog()-----------------------------------------------
// CONSTRUCTOR -- Records static information to be used later.
// -----------------------------------------------------------------------------

CAdminDialog::CAdminDialog( 
    UINT iddDialog,     // The resource ID of your dialog.
    UINT idsName,       // The resource ID of the string containing the name
                        // used by admin for the tab of your property sheet.
    LPSTR lpszBlobName)// Name of extension data blob.
    : CADialog()        // Construct our ancestor.
{
    // Remember the caller's dialog, property sheet names, and extension blob name.
    m_iddDialog = iddDialog;
    m_idsName = idsName;

    // Remember the blob name as a wide string.  The pointer will 
    // be NULL if the derived class does not have extension data.
    if( !lpszBlobName)
        m_lpwszBlobName = NULL;
    else
    {
        CHRESULT hr = HrStrAToStrW( lpszBlobName, &m_lpwszBlobName);
        if( FAILED( hr));
    }

    // Initialize other member variables.
    m_cExtData = 0;
    m_lpbExtData = NULL;
    m_cExtProps = 0;
    m_lpExtProps = NULL;
    
    // Add the "this" pointer of the dialog to a static list.  We need to know
    // about all dialogs so we can tell admin about them later.
    m_DlgList.AddTail( (void*) this);
}

// -----------------------------------------------------------------------------
// DESTRUCTOR 
// -----------------------------------------------------------------------------

CAdminDialog::~CAdminDialog()
{
    MAPIFREEBUFFER( m_lpbExtData);
    MAPIFREEBUFFER( m_lpExtProps);
    MAPIFREEBUFFER( m_lpwszBlobName);
}

// -----------------------------------------------------------------------------
// If the caller does not pass in the lpszCaption then use the title of the 
// parent window for the default title of our message box.
// -----------------------------------------------------------------------------

int CAdminDialog::MessageBox( LPCSTR lpszText, LPCSTR lpszCaption, UINT nType)
{
    if( lpszCaption == NULL)
        lpszCaption = m_sMsgBoxCaption;
    return( CWnd::MessageBox( lpszText, lpszCaption, nType));
}

int CAdminDialog::MessageBox2( int IDText, int IDCaption, UINT nType)
{
    CString MBText;
    CString MBCaption;
	int nSize = -1;
	int nLen;

	// try buffer size of 256, then larger size until entire string is retrieved
	do
	{
		nSize += 256;
		nLen = LoadStringA(IDText, MBText.GetBuffer(nSize), nSize+1);
	} while (nLen == nSize);
	MBText.ReleaseBuffer();

	if( IDCaption == 0)
        MBCaption = m_sMsgBoxCaption;
	else
	{
		nSize = -1;
		do
		{
			nSize += 256;
			nLen = LoadStringA( IDCaption, MBCaption.GetBuffer(nSize), nSize+1);
		} while (nLen == nSize);
		MBCaption.ReleaseBuffer();
	}
	

    return( CWnd::MessageBox( MBText, MBCaption, nType));
}

//$--CAdminDialog::LoadDialogTemplate()-----------------------------------------
// Use this function to create child dialog box templates.  It will ensure that 
// the correct language and fonts are used.  
//
// To create the dialog use the default constructor (no parameters) and then use
// the CDialog::InitModalIndirect() function to initialize the dialog.  Then you
// can call CDialog::DoModal() to process the dialog.
// -----------------------------------------------------------------------------

const HGLOBAL CAdminDialog::LoadDialogTemplate( UINT iddDialog)
{
    HGLOBAL hDlgTemplate = NULL;

    if( m_pAdminFunctions->pfnLoadDialogResource( AfxGetInstanceHandle(),
                          iddDialog, GetLanguageId(), (LPBYTE*) &hDlgTemplate))
        return( hDlgTemplate);
    else
        return( NULL);
}

//$--CAdminDialog::LoadString()------------------------------------------------
// Loads a string resource by id and language
// and (A version) converts to the current ANSI code page.
// Note that strings are stored in blocks of 16, and the ID gives
// us the number of the block, and the offset into the block.
// -----------------------------------------------------------------------------
int CAdminDialog::LoadStringA(UINT wID, LPSTR szBuf, int cchBuf)
{
    UINT    block, num;
    int     len = 0;	    
    HRSRC   hRC = NULL;
    HGLOBAL hgl = NULL;;
    LPWSTR  str = NULL;
    register UINT i;
    
    DEBUGPUBLIC( "CAdminDialog::LoadStringA()\n");
	CHRESULT hr = CHK_LoadStringA( wID, szBuf, cchBuf);
    if( FAILED( hr))
        return( 0 );

	szBuf[0] = '\0';

    block = (wID >> 4) + 1;	// compute block number
    num = wID & 0xf;		// compute offset into block
    
    hRC = FindResourceEx(AfxGetInstanceHandle(), RT_STRING, MAKEINTRESOURCE(block), GetLanguageId());
    if (!hRC) 
		goto Error;

	hgl = LoadResource(AfxGetInstanceHandle(), hRC);
	if (!hgl)
		goto Error;

    str = (LPWSTR)LockResource(hgl);
    if (!str) 
		goto Error;

	// Move up block to string we want
	for (i = 0; i < num; i++)
	    str += *str + 1;
	
	// convert the string to current code page
	len = WideCharToMultiByte(CP_ACP,
				  WC_COMPOSITECHECK,
				  str + 1, *str,
				  szBuf, cchBuf - 1,
				  NULL, NULL);

	szBuf[min(cchBuf-1, *str)] = '\0';

Error:

	if (hgl)
	{
		UnlockResource(hgl);	// maybe not needed
	    FreeResource(hgl);	    // maybe not needed
	}

    return len;
}

int CAdminDialog::LoadStringW(UINT wID, LPWSTR wzBuf, int cchBuf)
{

    UINT    block, num;
    int     len = 0;	    
    HRSRC   hRC = NULL;
    HGLOBAL hgl = NULL;
    LPWSTR  str = NULL;
    register UINT i;
    
    DEBUGPUBLIC( "CAdminDialog::LoadStringW()\n");
	CHRESULT hr = CHK_LoadStringW( wID, wzBuf, cchBuf);
    if( FAILED( hr))
        return( 0 );

	wzBuf[0] = TEXT('\0');

    block = (wID >> 4) + 1;	// compute block number
    num = wID & 0xf;		// compute offset into block
    
    hRC = FindResourceEx(AfxGetInstanceHandle(), RT_STRING, MAKEINTRESOURCE(block), GetLanguageId());
    if (!hRC) 
		goto Error;

	hgl = LoadResource(AfxGetInstanceHandle(), hRC);
	if (!hgl)
		goto Error;

    str = (LPWSTR)LockResource(hgl);
    if (str) 
    {
		for (i = 0; i < num; i++)
		    str += *str + 1;
		wcsncpy(wzBuf, str + 1, min(cchBuf - 1, *str));
    }

	wzBuf[min(cchBuf-1, *str) ] = '\0';

	len = *str + 1;

Error:

	if (hgl)
	{
		UnlockResource(hgl);	// maybe not needed
	    FreeResource(hgl);	    // maybe not needed
	}

    return len;
}

//$--CAdminDialog::GetExtBin()--------------------------------------------------
// Use this to get a binary extension data property.
// -----------------------------------------------------------------------------

LPSBinary CAdminDialog::GetExtBinary(
    ULONG iProp)        // Index of property.
{
    DEBUGPUBLIC( "CAdminDialog::GetExtBin()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_BINARY);
    if( FAILED( hr))
        return( NULL);
    
    return( &m_lpExtProps[iProp].Value.bin);
}

//$--CAdminDialog::GetExtString()-----------------------------------------------
// Use this to get a string extension data property.
// -----------------------------------------------------------------------------

LPSTR CAdminDialog::GetExtString(
    ULONG iProp)        // Index of property.
{
    DEBUGPUBLIC( "CAdminDialog::GetExtString()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_STRING8);
    if( FAILED( hr))
        return( NULL);

    return( m_lpExtProps[iProp].Value.lpszA);
}

//$--CAdminDialog::GetExtLong()-------------------------------------------------
// Use this to get a long extension data property.
// -----------------------------------------------------------------------------

LONG CAdminDialog::GetExtLong(
    ULONG iProp)        // Index of property.
{
    DEBUGPUBLIC( "CAdminDialog::GetExtLong()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_LONG);
    if( FAILED( hr))
        return( -1);
    
    return( m_lpExtProps[iProp].Value.l);
}

// -----------------------------------------------------------------------------
// Use this to get a boolean extension data property.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::GetExtBool(
    ULONG iProp)        // Index of property.
{
    DEBUGPUBLIC( "CAdminDialog::GetExtBool()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_BOOLEAN);
    if( FAILED( hr))
        return( FALSE);
    
    return( m_lpExtProps[iProp].Value.b);
}

//$--CAdminDialog::GetExtSysTime()----------------------------------------------
// Use this to get a system time extension data property.
// -----------------------------------------------------------------------------

FILETIME CAdminDialog::GetExtSysTime(
    ULONG iProp)        // Index of property.
{
    FILETIME ft = {0};
    
    DEBUGPUBLIC( "CAdminDialog::GetExtSysTime()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_SYSTIME);
    if( FAILED( hr))
        return( ft);
    
    return( m_lpExtProps[iProp].Value.ft);
}

//$--CAdminDialog::HrModExtBin()------------------------------------------------
// Use this to modify a binary extension data property.  It will allocate more
// memory only if the new buffer is larger.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrModExtBinary(
    IN ULONG  iProp,    // Index of property
    IN ULONG  cb,       // Count of new data bytes.
    IN const LPBYTE lpNew)    // New data bytes.
{
    DEBUGPUBLIC( "CAdminDialog::HrModExtBin()\n");
    CHRESULT hr = CHK_HrModExtBin( iProp, cb, lpNew);
    if( FAILED( hr))
        RETURN( hr);

    // New binary data will be copied to this address. 
    LPBYTE lpb = m_lpExtProps[ iProp].Value.bin.lpb;
    
    if( cb > m_lpExtProps[ iProp].Value.bin.cb)
    {   // New binary data is too big so alloacate a new buffer to stick it in.
        CHRESULT hr = MAPIAllocateMore( cb, m_lpExtProps, (LPVOID*) &lpb);
        if( FAILED( hr))
            RETURN( hr);

        // Replace old buffer ptr to new one.
        m_lpExtProps[ iProp].Value.bin.lpb = lpb;            
    }
    
    // Copy new data to MAPI buffer.
    memmove( lpb, lpNew, cb);
    m_lpExtProps[ iProp].Value.bin.cb = cb;
    return( NOERROR);
}

//$--CAdminDialog::HrModExtString()---------------------------------------------
// Use this to modify a string extension data property.  It will allocate more
// memory only if the new string is larger.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrModExtString(
    IN ULONG   iProp,    // Index of property
    IN LPCSTR lpszNew)  // New data string.
{
    DEBUGPUBLIC( "CAdminDialog::HrModExtString()\n");
    CHRESULT hr = CHK_HrModExtString( iProp, lpszNew);
    if( FAILED( hr))
        RETURN( hr);

    // Size of original string.
    ULONG cb = cbStrLenA( m_lpExtProps[ iProp].Value.lpszA);
    
    // Size of new string.
    ULONG cbNew = cbStrLenA( lpszNew);
    
    // New binary data will be copied to this address. 
    LPSTR lpsz = m_lpExtProps[ iProp].Value.lpszA;
    
    if( cbNew > cb)
    {   // New binary data is too big so alloacate a new buffer to stick it in.
        CHRESULT hr = MAPIAllocateMore( cbNew, m_lpExtProps, (LPVOID*) &lpsz);
        if( FAILED( hr))
            RETURN( hr);

        // Replace old buffer ptr to new one.
        m_lpExtProps[ iProp].Value.lpszA = lpsz;
    }
    
    // Copy new data to MAPI buffer.
    memmove( lpsz, lpszNew, cbNew);
    return( NOERROR);
}

//$--CAdminDialog::HrModExtLong()-----------------------------------------------
// Use this to modify a long extension data property.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrModExtLong(
    IN ULONG  iProp,    // Index of property
    IN LONG   lNew)     // New long data value.
{
    DEBUGPUBLIC( "CAdminDialog::HrModExtLong()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_LONG);
    if( FAILED( hr))
        RETURN( hr);

    // Copy new data to MAPI buffer.
    m_lpExtProps[ iProp].Value.l = lNew;
    return( NOERROR);
}

//$--CAdminDialog::HrModExtBool()-----------------------------------------------
// Use this to modify a boolean extension data property.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrModExtBool(
    IN ULONG  iProp,    // Index of property
    IN BOOL   bNew)     // New boolean data value.
{
    DEBUGPUBLIC( "CAdminDialog::HrModExtBool()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_BOOLEAN);
    if( FAILED( hr))
        RETURN( hr);

    // Copy new data to MAPI buffer.
    m_lpExtProps[ iProp].Value.b = bNew;
    return( NOERROR);
}

//$--CAdminDialog::HrModExtSysTime()-----------------------------------------------
// Use this to modify a SysTime extension data property.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrModExtSysTime(
    IN ULONG    iProp,    // Index of property
    IN FILETIME ftNew)    // New boolean data value.
{
    DEBUGPUBLIC( "CAdminDialog::HrModExtSysTime()\n");
    CHRESULT hr = CHK_HrExtData( iProp, PT_SYSTIME);
    if( FAILED( hr))
        RETURN( hr);

    // Copy new data to MAPI buffer.
    m_lpExtProps[ iProp].Value.ft = ftNew;
    return( NOERROR);
}

// -----------------------------------------------------------------------------
// Set the extension data properties to an existing property value array.  This
// can be used to create a blob for the first time.  To do this initialized the
// lpExtProps array with just property types and no real data.  Then use the 
// HrMod...() functions to set the values.
//
// NOTE: Since this MUST be a MAPI allocated buffer, and since it is not as easy
//       to initialize a MAPI allocated buffer as a static one, we copy the 
//       buffer the user passes in.  Therefore the user will need to free their
//       buffer if it is not a static one.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrSetExtProps(
    ULONG        cExtProps,     // Count of extension data properties.
    LPSPropValue lpExtProps)    // Array of properties to set extension data to.
{
    DEBUGPUBLIC( "CAdminDialog::HrSetExtProps()\n");
    CHRESULT hr = CHK_HrSetExtProps( cExtProps, lpExtProps);
    if( FAILED( hr))
        RETURN( hr);

    // Free old extension properties and set to the new ones.  We do not
    // free the old blob pointer here because its existence signifies that
    // we are not creating a new blob.
    MAPIFREEBUFFER( m_lpExtProps);
    m_cExtProps = 0;
    
    // Make sure that all property tags have a non zero property id. This is done 
    // because ScCountProps() does a validation to make sure all properties have a 
    // non zero id.  This should be fixed in some future version of MAPI.
    ULONG iProp = 0;
    for( iProp = 0; iProp < cExtProps; iProp++)
    {
        if( PROP_ID( lpExtProps[ iProp].ulPropTag) == 0)
            lpExtProps[ iProp].ulPropTag = PROP_TAG( PROP_TYPE( lpExtProps[ iProp].ulPropTag), 1);
    }

    // Count the bytes needed for the new property array.
    ULONG cBytes = 0;
    hr = ScCountProps( cExtProps, lpExtProps, &cBytes);
    if( FAILED( hr))
        RETURN( hr);
    
    // Allocate a new buffer to hold the copied properties.
    hr = MAPIAllocateBuffer( cBytes, (LPVOID*) &m_lpExtProps);
    if( FAILED( hr))
        RETURN( hr);
    memset( m_lpExtProps, 0, cBytes);

    // Copy the subscriber properties to the new buffer.
    ULONG cBytesCopied = 0;
    hr = ScCopyProps( cExtProps, lpExtProps, m_lpExtProps, &cBytesCopied);
    if( FAILED( hr))
        RETURN( hr);
    ASSERTERROR( cBytes == cBytesCopied, "ScCountProps & ScCopyProps are inconsistent!");
    
    // We completed this successfuly so set the count.
    m_cExtProps = cExtProps;
    
    DataHasChanged();

    return( NOERROR);
}

// -----------------------------------------------------------------------------
// Loads the extension data into a buffer that is contained in this object.  Use
// GetExtCount() and GetExtData() to get individual items. Use the HrMod...() 
// functions to modify a property value.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrLoadExtData()
{
    MAPIFREEBUFFER( m_lpbExtData);
    m_cExtData = 0;

    MAPIFREEBUFFER( m_lpExtProps);
    m_cExtProps = 0;

    if( m_lpwszBlobName == NULL)
        return( NOERROR);
    
    // Determine the size of the buffer needed to hold the data.
    UINT cTemp;
    RC rc = m_pAdminFunctions->pfnGetObjectDataSize( GetSafeHwnd(), m_lpwszBlobName, &cTemp);
    if(RC_FAILED(rc))
        RETURN( E_FAIL);
    
    // Convert UINT to a ULONG.
    m_cExtData = cTemp;

    // Allocate a buffer to hold the extension data.
    CHRESULT hr = MAPIAllocateBuffer( m_cExtData, (LPVOID*) &m_lpbExtData);
    if( FAILED( hr))
        RETURN( hr);

    // Get the extension data.
    rc = m_pAdminFunctions->pfnGetObjectData( GetSafeHwnd(), m_lpwszBlobName, m_lpbExtData, m_cExtData);
    if( RC_FAILED(rc))
        RETURN( E_FAIL);

    // Unpack the data into a MAPI style property value array.
    hr = HrCfgUnpackData( m_cExtData, m_lpbExtData, NULL, &m_cExtProps, &m_lpExtProps);
    if( FAILED( hr))
        RETURN( hr);

    return( NOERROR);
}

// -----------------------------------------------------------------------------
// Saves the extension data that is held in a buffer contained in this object.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrSaveExtData()
{
    if( m_lpwszBlobName == NULL)
        return( NOERROR);

    if( m_cExtProps == 0 || !TEST_READ_PTR( m_lpExtProps, sizeof( SPropValue) * m_cExtProps))
        return( E_FAIL);

    // If we did not have extension blob data then we are creating a new blob.
    BOOL bNew = (m_lpbExtData == NULL);
    MAPIFREEBUFFER( m_lpbExtData);
    m_cExtData = 0;

    // Pack the configuration data from a MAPI style property value array.
    CHRESULT hr = HrCfgPackDataW( m_lpwszBlobName, m_cExtProps, m_lpExtProps, &m_cExtData, &m_lpbExtData);
    if( FAILED( hr))
        RETURN( hr);

    // Set the extension data.
    RC rc = m_pAdminFunctions->pfnSetObjectData( GetSafeHwnd(), m_lpbExtData, m_cExtData, bNew);
    if( RC_FAILED(rc))
        RETURN( E_FAIL);
    
    return( NOERROR);
}

// -----------------------------------------------------------------------------
// Add service to be tracked by Server Monitor.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrAddService(
    IN LPSTR lpszServiceName)      // SHORT name of the service.
{
    // Not UNICODE, so convert to wide string.
    CMAPIBuffer< LPWSTR> lpwszServiceName;
    CHRESULT hr = HrStrAToStrW( lpszServiceName, &lpwszServiceName);
    if( FAILED( hr))
        return( hr);

    if( !m_pAdminFunctions->pfnAddService( GetSafeHwnd(), lpwszServiceName))
        RETURN( E_FAIL);

    return( NOERROR);
}

// -----------------------------------------------------------------------------
// Remove service to be tracked by Server Monitor.
// -----------------------------------------------------------------------------

HRESULT CAdminDialog::HrRemoveService( 
    IN LPSTR lpszServiceName)      // SHORT name of the service.
{
    // Not UNICODE, so convert to wide string.
    CMAPIBuffer< LPWSTR> lpwszServiceName;
    CHRESULT hr = HrStrAToStrW( lpszServiceName, &lpwszServiceName);
    if( FAILED( hr))
        return( hr);

    if( !m_pAdminFunctions->pfnRemoveService( GetSafeHwnd(), lpwszServiceName))
        RETURN( E_FAIL);

    return( NOERROR);
}

//$--CAdminDialog::GetNameList()------------------------------------------------
// You MUST release the array with FreeNameList.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::GetNameList( 
    OUT int*     lpcNameList,       // Ptr to number of WIDE strings in the array.
    OUT LPWSTR** lppwszNameList)    // Ptr to a ptr of WIDE string array.  
{
    BOOL fRes = m_pAdminFunctions->pfnGetNameList( GetSafeHwnd(), lpcNameList, lppwszNameList);
    if( !fRes)
        RETURN( E_FAIL);

    return( NOERROR);
}

//$--CAdminDialog::SetNameList()------------------------------------------------
// Set the name list.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::SetNameList(
    IN int      cNameList,        // Number of WIDE strings in the array.
    IN LPWSTR*  lpwszNameList)    // Ptr to a WIDE string array.  
{
    BOOL fRes = m_pAdminFunctions->pfnSetNameList( GetSafeHwnd(), cNameList, lpwszNameList);
    if( !fRes )
        RETURN( E_FAIL);

    return( NOERROR);
}

//$--CAdminDialog::fSetLcid()---------------------------------------------------
// Set the LCID we will use.  
// Note that Exchange Admin could ask for any locale, but this dll typically only
// supports a subset.  This function checks to see if the dll has resources of the 
// requested locale, and sets a default if not. 
// -----------------------------------------------------------------------------
void CAdminDialog::SetLcid(LCID lcid)
{
	EnumLangParams ELP;

	// We're just concerned with the primary language
	ELP.langRequested = MAKELANGID(PRIMARYLANGID( LANGIDFROMLCID(lcid) ), SUBLANG_NEUTRAL);
	ELP.fFound = FALSE;

    // Check that we support this language, use default if not
    // This check works by walking the resource tree. It stops as soon as one resource with 
    // a matching language is found.
	if (!EnumResourceTypes(AfxGetInstanceHandle(), (ENUMRESTYPEPROC) EnumResTypesCallback, (LONG) &ELP))
	{
		// Note: EnumResourceTypes returns false if one of the callbacks returns false
		// (indicating that the search can be stopped)
	}

	// Default to English
	if (ELP.fFound)
		m_lcid = ELP.langRequested;
	else
		m_lcid = MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_NEUTRAL),  SORT_DEFAULT);

	return;  // We always succeed
}

// $--CAdminDialog::bInitSheet()------------------------------------------------
// This function initializes the property sheet info and returns it to ADMIN.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::bInitSheet(              // RETURNS: TRUE if initialization OK
    IN  ADMIN_ObjectInfo* poi,              // Server name & other DNs.
    IN  ULONG             fFlags,                       
    OUT ADMIN_SheetInfo** ppSheetInfo,      // Property sheet description array
    OUT UINT*             pcsi,             // Number of property sheets
    OUT VOID**            ppNotUsed)        // Local data (NOT USED)
{
    ASSERT_READ_PTR( poi, sizeof( ADMIN_ObjectInfo), "Admin sent us a bad pointer.");

    // Remember these for later usage.
    m_pAdminObjectInfo = poi;
    m_bReadOnly = (fFlags & fxfReadOnly) > 0;

 
	// Choose the language we will display
	SetLcid( poi->lcid );
	
	
	// Allocate memory for the property sheet info array.
    *pcsi = m_DlgList.GetCount();
    m_pSheetInfo = new ADMIN_SheetInfo[ *pcsi];
    if( !m_pSheetInfo)
    {   // Memory allocation error!
        return( FALSE);
    }

    // Initialize Admin property sheet info array.
    POSITION pos = m_DlgList.GetHeadPosition();
    ADMIN_SheetInfo* pSheetInfo = m_pSheetInfo;
    while( pos)
    {   // Tell admin about all of the CAdminDialog derived objects that
        // have been instantiated.
        CAdminDialog* pAdminDlg = (CAdminDialog*) m_DlgList.GetNext( pos);

        pSheetInfo->hInstance = AfxGetInstanceHandle();
        pSheetInfo->iddDialog = pAdminDlg->m_iddDialog;
        pSheetInfo->lpfnDlgProc = (DLGPROC) AdminDlgProc;
        pSheetInfo->idsName = pAdminDlg->m_idsName;
        pSheetInfo->lParam = (LPARAM) pAdminDlg;
        pSheetInfo->langid = GetLanguageId();
        
        pSheetInfo ++;
    }

    // Set return values.
    *ppSheetInfo = m_pSheetInfo;
    *ppNotUsed = NULL;

    return( TRUE);  // TRUE indicates success.
}

// $--CAdminDialog::DeinitSheet()-----------------------------------------------
// Admin calls this when the property sheet dialog box is about to be removed 
// and after the OnDestroy() functions of the individual property page dialogs
// have been called.
// -----------------------------------------------------------------------------

void CAdminDialog::DeinitSheet(         // Returns nothing
    IN VOID* pNotUsed)           // Extension data. 
{
    delete m_pSheetInfo;
    m_pSheetInfo = NULL;
}

// $--CAdminDialog::FindDlg()---------------------------------------------------
// Finds and returns a pointer to a CAdminDialog object using its dialog handle.
// -----------------------------------------------------------------------------

CAdminDialog* CAdminDialog::FindDlg( HWND hDlg)
{
    POSITION pos = m_DlgList.GetHeadPosition();
    while( pos)
    {   // Get pointer to next CAdminDialog object and see if its window 
        // handle matches the one we are looking for.
        CAdminDialog* pAdminDlg = (CAdminDialog*) m_DlgList.GetNext( pos);
        if( pAdminDlg->m_hWnd == hDlg)
            return( pAdminDlg);             // Found it!
    }
    return( NULL);      // Not found.
}

// $--CAdminDialog::ADMIN_Initialize()------------------------------------------
// Helper function used to access private and protected members.
// -----------------------------------------------------------------------------

VOID CAdminDialog::ADMIN_Initialize(                        // Returns nothing.
    IN  ADMIN_AdministratorConnections* pAdminConnections,  // Global Administrator Connections
    IN  ADMIN_AdministratorFunction*    pAdminFunctions)    // Global admin function
{
    if( m_pMAPISession != pAdminConnections->psesMapi)
    {   // Add a reference to the admin's MAPI session.
        m_pMAPISession = pAdminConnections->psesMapi;
        m_pAddrBook = pAdminConnections->pab;
        m_pABContainer = pAdminConnections->pabContainer;
    }

    m_pAdminFunctions = pAdminFunctions;
}

// $--CAdminDialog::OnInitDialog()----------------------------------------------
// Calls the admin function to set the icon and title for the property sheet.
// Make sure your derived classes OnInitDialog() calls this function.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // Get the title of the parent window to use as the default 
    // caption of our message boxes.
    GetParent()->GetWindowText( m_sMsgBoxCaption);

    // Set the icon and title for this dialog.
    m_pAdminFunctions->pfnSetIcon( m_hWnd, IDC_ADMINICON);
    m_pAdminFunctions->pfnSetTitle( m_hWnd, IDC_TITLE);

    // Load the extension data if there is any.
    CHRESULT hr = HrLoadExtData();
    if( FAILED( hr));

    return TRUE;  // Return TRUE unless you set the focus to a control.
}

//$--CAdminDialog::OnChildActivate()--------------------------------------------
// This gets called when we receive a WM_CHILDACTIVATE message.  This indicates
// that the property sheet has just been brought into focus.
// -----------------------------------------------------------------------------

LONG CAdminDialog::OnChildActivate( UINT, LONG )
{
    // Load the extension data if there is any.
    CHRESULT hr = HrLoadExtData();
    if( FAILED( hr));

    // Call the user's function to refresh their dialog.
    Refresh();

    return( hr);
}

//$--CAdminDialog::Refresh()----------------------------------------------------
// A do nothing function so the user is not required to implement this function
// if they really don't need it.
// -----------------------------------------------------------------------------

void CAdminDialog::Refresh()
{
}

//$--CAdminDialog::InvalidEntry()-----------------------------------------------
// Displays a message box with a resource string for invalid entries.  After
// the user presses OK the appropriate control gets focus.
// -----------------------------------------------------------------------------

void CAdminDialog::InvalidEntry( int nResourceStrID, CWnd& wndCtrl)
{
    CString sResourceString;
    if( sResourceString.LoadString( nResourceStrID))
        MessageBox2( nResourceStrID);
    else
    {   // The nResourceStrID must be bad, display a general 
        // purpose message and log the error.
        HR_LOG( E_FAIL);
        MessageBoxA( "Invalid entry.");
    }
    wndCtrl.SetFocus();
}

// $--CAdminDialog::bSaveData()-------------------------------------------------
// Override this virtual function if you need to validate data when the property 
// sheet changes, or when the Ok or Apply button is pressed.  This is the appropriate
// place to check edit control values, list box selections etc.
// Default behavior is to do nothing but continue.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::bSaveData()
{
    // Save the extension data if there is any.
    CHRESULT hr = HrSaveExtData();
    if( FAILED( hr))
        return( FALSE);

    return( TRUE);
}

// $--CAdminDialog::bCommitData()-----------------------------------------------
// Override this virtual function if you need to save data to permanent storage 
// when the Ok or Apply button is pressed. (You can assume the data is good, because
// you should have checked it in the bSaveData() call.)
// Default behavior is to do nothing but continue.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::bCommitData()
{
    return( TRUE);
}

// $--CAdminDialog::bHasHelp()--------------------------------------------------
// Override this virtual function if you supply help.
// Default behavior is NO help.
// -----------------------------------------------------------------------------

BOOL CAdminDialog::bHasHelp()
{
    MessageBox( "Help is not available for this property sheet.");
    return( FALSE);
}

// $--CAdminDialog::DoHelp()----------------------------------------------------
// Override this virtual function if you supply help.
// Default behavior is to display a message.
// -----------------------------------------------------------------------------

VOID CAdminDialog::DoHelp()
{
    MessageBox( "Help is not available for this property sheet.");
}

// $--bInitSheet()--------------------------------------------------------------
// This function initializes the property sheet info and returns it to admin.
// It uses the static member function since this one can NOT access the static 
// member data.
// -----------------------------------------------------------------------------

BOOL PASCAL bInitSheet(                 // RETURNS: TRUE if initialization OK
    IN  ADMIN_ObjectInfo* poi,              // Computer name & DN.
    IN  ULONG             fFlags,                       
    OUT ADMIN_SheetInfo** ppSheetInfo,      // Property sheet description array
    OUT UINT*             pcsi,             // Number of property sheets
    OUT VOID**            ppNotUsed) // Local data
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    DEBUGPUBLIC( "bInitSheet()\n");
    if( FAILED( CHK_bInitSheet( poi, fFlags, ppSheetInfo, pcsi, ppNotUsed)))
        return( FALSE);

    return( CAdminDialog::bInitSheet( poi, fFlags, ppSheetInfo, pcsi, ppNotUsed));
}

// $--DeinitSheet()-------------------------------------------------------------
// Admin calls this when the property sheet dialog box is about to be removed.
// -----------------------------------------------------------------------------

void PASCAL DeinitSheet(                // Returns nothing
    IN VOID* pNotUsed)           // Extension data. 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CAdminDialog::DeinitSheet( pNotUsed);
}

// $--bInstallExtension()-------------------------------------------------------
// -----------------------------------------------------------------------------

BOOL PASCAL bInstallExtension(ADMIN_ObjectInfo * poi)
{
    return(TRUE);
}

// $--bDeinstallExtension()-----------------------------------------------------
// -----------------------------------------------------------------------------

BOOL PASCAL bDeinstallExtension(ADMIN_ObjectInfo * poi)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return(TRUE);
}

// $--bSaveData()-----------------------------------------------------------
// Called by admin when the property sheet page loses focus.
// -----------------------------------------------------------------------------

BOOL PASCAL bSaveData(   // Returns: TRUE if successful.
    IN VOID* pNotUsed,       // Extension data for all sheets
    IN HWND  hDlg)           // Window handle of the property sheet.
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    DEBUGPUBLIC( "bSaveData()\n");
    if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        return( FALSE);

    CAdminDialog* pAdminDlg = CAdminDialog::FindDlg( hDlg);
    if( !pAdminDlg)
    {
        HR_LOG( E_FAIL);
        return( FALSE);
    }
    return( pAdminDlg->bSaveData());
}

// $--bCommitData()-------------------------------------------------------------
// This function is called by admin when the user presses either the OK or the 
// APPLY buttons.
// -----------------------------------------------------------------------------

BOOL PASCAL bCommitData(            // Returns:  TRUE if successful.
    IN VOID* pNotUsed,       // Extension data.
    IN HWND  hDlg)                  // Handle of the property sheet to be committed.
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    DEBUGPUBLIC( "bCommitData()\n");
    if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        return( FALSE);

    CAdminDialog* pAdminDlg = CAdminDialog::FindDlg( hDlg);
    if( !pAdminDlg)
    {
        HR_LOG( E_FAIL);
        return( FALSE);
    }
    return( pAdminDlg->bCommitData());
}

// $--bHasHelp()----------------------------------------------------------------
// Called by admin to find out if we support help.
// -----------------------------------------------------------------------------

BOOL PASCAL bHasHelp(               // RETURNS: true if help is available.
    IN VOID* pNotUsed,       // Ext dll managed data area.
    IN HWND  hDlg)                  // Window handle of the property sheet.
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    DEBUGPUBLIC( "bHasHelp()\n");
    if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        return( FALSE);

    CAdminDialog* pAdminDlg = CAdminDialog::FindDlg( hDlg);
    if( !pAdminDlg)
    {
        HR_LOG( E_FAIL);
        return( FALSE);
    }
    return( pAdminDlg->bHasHelp());
}

// $--DoHelp()------------------------------------------------------------------
// Called by admin to displays help for the user.
// -----------------------------------------------------------------------------

VOID PASCAL DoHelp(                 // RETURNS: Nothing
    IN VOID* pNotUsed,       // Ext dll managed data area.
    IN HWND  hDlg)                  // Window handle of the property sheet.
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    DEBUGPUBLIC( "DoHelp()\n");
    if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        return;
    
    CAdminDialog* pAdminDlg = CAdminDialog::FindDlg( hDlg);
    if( !pAdminDlg)
    {
        HR_LOG( E_FAIL);
        return;
    }
    pAdminDlg->DoHelp();
}

// -----------------------------------------------------------------------------
// NOTE: The admin program will keep a pointer to this.  These are pointers to
//       the functions that admin will want to access.
// -----------------------------------------------------------------------------

ADMIN_ExtensionFunction extensionFunctions =
{
    ADMIN_ExtensionAPIVersion,
    bInstallExtension,
    bDeinstallExtension,
    bInitSheet,
    bShowPage,  // This one can be defined in your dll code, otherwise it will come from ShowPage.CPP.
    iStartPage, // This one can be defined in your dll code, otherwise it will come from StrtPage.CPP.
    bHasHelp,
    DoHelp,
    bSaveData,
    bCommitData,
    DeinitSheet
};

// $--ADMIN_Initialize()--------------------------------------------------------
// Exported function. This is the first function called by admin after the DLL 
// has been initialized.
// -----------------------------------------------------------------------------

extern "C" VOID PASCAL ADMIN_Initialize(                    // Returns nothing.
    IN  ADMIN_AdministratorConnections* pAdminConnections,  // Global Administrator Connections
    IN  ADMIN_AdministratorFunction*    pAdminFunctions,    // Global admin function
    OUT ADMIN_ExtensionFunction**       ppExtensionFunction)// Global Extension function
{
    DEBUGPUBLIC( "ADMIN_Initialize()\n");
    if( FAILED( CHK_ADMIN_Initialize( pAdminConnections, pAdminFunctions, ppExtensionFunction)))
        return;

    CAdminDialog::ADMIN_Initialize( pAdminConnections, pAdminFunctions);
    
    // Tell admin where it can find the rest of our functions that it needs.
    *ppExtensionFunction = &extensionFunctions;  
}

// -----------------------------------------------------------------------------
// Detemine what languages this dll supports

BOOL CALLBACK EnumResTypesCallback(HANDLE hModule,LPTSTR lpszType,LONG lParam)
{
	PEnumLangParams pELP = (PEnumLangParams) lParam;

    EnumResourceNames((HINSTANCE) hModule, lpszType, (ENUMRESNAMEPROC) EnumResNamesCallback, lParam);

	if (pELP->fFound)
		return FALSE;	// terminates search
	else
		return TRUE;
}

BOOL CALLBACK EnumResNamesCallback(HANDLE hModule, LPCTSTR lpszType,
				   LPTSTR lpszName, LONG lParam)
{
	PEnumLangParams pELP = (PEnumLangParams) lParam;

    EnumResourceLanguages((HINSTANCE)hModule, lpszType, lpszName, (ENUMRESLANGPROC) fEnumLangProc,
			  lParam);

	if (pELP->fFound)
		return FALSE;	// terminates search
	else
		return TRUE;
}

BOOL CALLBACK fEnumLangProc(HANDLE hMod, LPCTSTR ptzType, LPCTSTR ptzName, WORD wLang, LONG lParam)
{
	PEnumLangParams pELP = (PEnumLangParams) lParam;

	if (wLang == pELP->langRequested)
		pELP->fFound = TRUE;

	if (pELP->fFound)
		return FALSE;	// terminates search
	else
		return TRUE;
}

