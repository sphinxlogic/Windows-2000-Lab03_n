// ICSDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICSDemo.h"
#include "ICSDemoDlg.h"
#include "ICSDemoCollector.h"

#include "edk.h"
#include "mapiutil.h"

#include "TraceBox.h"

const GUID IID_IExchangeExportChanges = {0xa3ea9cc0,0xd1b2,0x11cd,0x80,0xfc,0x00,0xaa,0x00,0x4b,0xba,0x0b};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CICSDemoApp	theApp;
extern CTraceBox		theTraceBox;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICSDemoDlg dialog

CICSDemoDlg::CICSDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CICSDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CICSDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN_ICON);

	m_lpStore = NULL;
	m_lpFolder = NULL;
	m_lpSynchronizer = NULL;
	m_hMemBlock = NULL;
	m_lpSynchState = NULL;
	m_lpCollectorIUnknown = NULL;
	m_lpCollector = NULL;

	m_fICSStarted = FALSE;
	m_fICSBackupState = FALSE;
}

void CICSDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CICSDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CICSDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CICSDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_SYNCH, OnSynch)
	//ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------

//
// CICSDemoDlg message handlers
//

BOOL CICSDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	// Add "About..." menu item to system menu.
	//
	//	Note: The assertions check that the menu item ID is
	//	divisible by 16, and less that 0xF000. The latter
	//	requirement prevents the menu item from clashing with
	//	system definitions (e.g. SC_SIZE). I don't understand
	//	the first requirement.
	//
	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

		//
		//	Remove unsupported entries from the system menu.
		//
		
		pSysMenu->RemoveMenu(SC_SIZE,MF_BYCOMMAND);
		pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
	}

	//
	//	Set 32x32 icon
	//
	
	SetIcon(AfxGetApp()->LoadIcon(IDI_MAIN_ICON), TRUE);

	//
	//	Set 16x16 icon
	//
	
	SetIcon(AfxGetApp()->LoadIcon(IDI_MAIN_SMALL_ICON), FALSE);
	
	//
	//	Set window class variable to support dragging the minimized 
	//	icon around.
	//
	
	SetClassLong(m_hWnd,GCL_HICON,(long)m_hIcon);
	
	//
	//	Configure the trace object.
	//

	theTraceBox.Config((CListBox *)GetDlgItem(IDC_TRACE_LIST));

	//
	//	Set the state of the UI controls.
	//

	SynchStopped();

	return TRUE;
}

//----------------------------------------------------------------------

//
//	Process system menu commands. Capture the About 
//	menu item and display the About dialog box.
//

void CICSDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//----------------------------------------------------------------------

//
//	About dialog box processing.
//

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	//	Write text onto the Help dialog.
	//

	CString	str;

	str.LoadString(IDS_PRODUCT_NAME);
	SetDlgItemText(IDC_HELP_TEXT_1,str);

	str.LoadString(IDS_AUTHORS);
	SetDlgItemText(IDC_HELP_TEXT_2,str);
	
	str.LoadString(IDS_COPYRIGHT);
	SetDlgItemText(IDC_HELP_TEXT_3,str);
	
	return TRUE;
}

//----------------------------------------------------------------------

//
//	Start button processing.
//

void CICSDemoDlg::OnStart() 
{
	CString		str;
	HRESULT		hResult;

	//
	//	Check whether the system is already running.
	//

	if (m_fICSStarted)
		return;

	//
	//	Sanity check.
	//

	ASSERT(m_lpStore == NULL);
	ASSERT(m_lpFolder == NULL);
	ASSERT(m_lpSynchronizer == NULL);
	ASSERT(m_lpSynchState == NULL);
	ASSERT(m_hMemBlock == NULL);
	ASSERT(m_lpCollectorIUnknown == NULL);
	ASSERT(m_lpCollector == NULL);

	//
	//	Open the public folder store.
	//
	
	hResult = HrOpenExchangePublicStore(theApp.MAPISession(),&m_lpStore);
//	hResult = HrOpenPublicFolderStore(theApp.MAPISession(),&m_lpStore);

	if (HR_FAILED(hResult))
	{
		theApp.ShowErrorMessage("HrOpenPublicFolderStore",hResult);
		m_fICSStarted = FALSE;
		return;
	}

	theTraceBox.Trace("Public folder store opened");
	
	//
	//	Read properties from the public folder store, including
	//	the EntryID for the target public folder.
	//

	ASSERT(m_lpStore != NULL);

	SizedSPropTagArray(3,rgStoreProps) =
	{
		3,
		{
			PR_DISPLAY_NAME,
			PR_HIERARCHY_SERVER,
			PR_NEWSGROUP_ROOT_FOLDER_ENTRYID
		}
	};

	ULONG				uValuesCount;
	LPSPropValue	lpProps;

	hResult = m_lpStore->GetProps(
								(LPSPropTagArray)&rgStoreProps,
								0,
								&uValuesCount,
								&lpProps);

	if (HR_FAILED(hResult))
	{
		OnStop();
		return;
	}
	else
	{
		//
		//	Display some useful information.
		//

		ASSERT(uValuesCount == 3);
		theTraceBox.Trace(str);

		ASSERT(lpProps[0].ulPropTag == PR_DISPLAY_NAME);
		ASSERT(lpProps[1].ulPropTag == PR_HIERARCHY_SERVER);
		ASSERT(lpProps[2].ulPropTag == PR_NEWSGROUP_ROOT_FOLDER_ENTRYID);

		str.Format(" PR_DISPLAY_NAME=%s",lpProps[0].Value.lpszA);
		theTraceBox.Trace(str);
		str.Format(" PR_HIERARCHY_SERVER=%s",lpProps[1].Value.lpszA);
		theTraceBox.Trace(str);
		

		//
		//	Open a public folder.
		//

		ULONG					uObjType;

		hResult = m_lpStore->OpenEntry(
									lpProps[2].Value.bin.cb,
									(LPENTRYID)lpProps[2].Value.bin.lpb,
									NULL,
									MAPI_BEST_ACCESS,
									&uObjType,
									(LPUNKNOWN FAR *)&m_lpFolder);

		//
		//	Free memory allocated in the GetProps call.
		//

		MAPIFreeBuffer(lpProps);

		if (HR_FAILED(hResult))
		{
			theApp.ShowErrorMessage("OpenEntry",hResult);
			OnStop();
			return;
		}

		//
		//	Do a quick sanity check.
		//
		
		ASSERT (uObjType == MAPI_FOLDER);

		theTraceBox.Trace("Public folder opened");
		theTraceBox.TraceFolderName(m_lpFolder);
	}

	//
	//	Create a memory blob with an IStream interface
	//

	m_hMemBlock = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, 0);

	hResult = CreateStreamOnHGlobal(
									m_hMemBlock,
									TRUE,
									&m_lpSynchState);

	if (HR_FAILED(hResult))
	{
		theApp.ShowErrorMessage("CreateStreamOnHGlobal",hResult);
		OnStop();
		return;
	}

	theTraceBox.Trace("Synchronizer state stream opened");

	//
	//	Create a collector object.
	//

	m_lpCollectorIUnknown = (LPUNKNOWN)new CDemoCollector;

	hResult = m_lpCollectorIUnknown->QueryInterface(IID_IExchangeImportContentsChanges,(LPVOID *)&m_lpCollector);
	
	if (HR_FAILED(hResult))
	{
		theApp.ShowErrorMessage("QueryInterface(IID_IExchangeImportContentsChanges)",hResult);
		OnStop();
		return;
	}

	hResult = Load();

	//
	//	Normal A-OK exit.
	//

	SynchStarted();
	m_fICSStarted = TRUE;
	return;
}

//----------------------------------------------------------------------

//
//	Synch button processing.
//

void CICSDemoDlg::OnSynch() 
{
	HRESULT hResult;
	
	if (m_fICSStarted == FALSE)
		return;

	//
	//	Sanity checks
	//

	ASSERT(m_lpStore != NULL);
	ASSERT(m_lpFolder != NULL);
	ASSERT(m_lpSynchState != NULL);
	ASSERT(m_hMemBlock != NULL);
	ASSERT(m_lpCollectorIUnknown != NULL);
	ASSERT(m_lpCollector != NULL);

	//
	//	Get the contents synchronizer interface on the public folder.
	//

	ASSERT(m_lpFolder != NULL);
	hResult = m_lpFolder->OpenProperty(
									PR_CONTENTS_SYNCHRONIZER,
									&IID_IExchangeExportChanges,
									0,
									0,
									(LPUNKNOWN FAR *)&m_lpSynchronizer);

	if (HR_FAILED(hResult))
	{
		theApp.ShowErrorMessage("OpenProperty(PR_CONTENTS_SYNCHRONIZER)",hResult);
		return;
	}

	//
	//	Configure synchronizer.
	//

	SizedSPropTagArray(2,rgSynchronizerProps) =
	{
		2,
		{
			PR_ENTRYID,
			PR_MESSAGE_SIZE
		}
	};

	hResult = m_lpSynchronizer->Config(
									m_lpSynchState,
									SYNC_NORMAL | SYNC_READ_STATE,
									m_lpCollectorIUnknown,
									NULL,
									(LPSPropTagArray)&rgSynchronizerProps,
									NULL,
									0);
	
	if (HR_FAILED(hResult))
	{
		theApp.ShowErrorMessage("Synchronizer::Config",hResult);
		return;
	}

	//
	//	Synchronization steps
	//

	ULONG	uSteps;
	ULONG uProgress;

	do
	{
		hResult = m_lpSynchronizer->Synchronize(&uSteps,&uProgress);
	}
	while (hResult == SYNC_W_PROGRESS);

	if (HR_SUCCEEDED(hResult))
		m_lpSynchronizer->UpdateState(m_lpSynchState);
}

//----------------------------------------------------------------------

//
//	Stop button processing.
//

void CICSDemoDlg::OnStop() 
{
	HRESULT hResult;

	if (!m_fICSStarted)
		return;

	hResult = Save();
	//
	//	Release the collector interfaces and object.
	//

	if (m_lpCollector != NULL)
	{
		m_lpCollector->Release();
		m_lpCollector = NULL;

		delete m_lpCollectorIUnknown;
		m_lpCollectorIUnknown = NULL;

		theTraceBox.Trace("Collector closed");
	}
	
	//	
	//	Release the synchronizer object.
	//
	//	PROBLEM: Release fails.
	//

	if (m_lpSynchronizer != NULL)
	{
//		m_lpSynchronizer->Release();
		m_lpSynchronizer = NULL;
		theTraceBox.Trace("Synchronizer closed");
	}

	//
	//	Release the IStream object.
	//

	if (m_lpSynchState != NULL)
	{
		m_lpSynchState->Release();
		m_lpSynchState = NULL;

		theTraceBox.Trace("Synchronizer state stream closed");
	}

	if (m_hMemBlock != NULL)
	{
		GlobalFree(m_hMemBlock);
		m_hMemBlock = NULL;
	}

	//
	//	Release the folder object.
	//

	if (m_lpFolder != NULL)
	{
		m_lpFolder->Release();
		m_lpFolder = NULL;
		theTraceBox.Trace("Public folder closed");
	}

	//
	//	Close down the public folder store and release
	//	the store object.
	//

	if (m_lpStore != NULL)
	{
		ULONG	fLogoffFlags = LOGOFF_ORDERLY;
		m_lpStore->StoreLogoff(&fLogoffFlags);
		m_lpStore->Release();
		m_lpStore = NULL;

		theTraceBox.Trace("Public folder store closed");
	}

	//
	//	Clear the "started" flag.
	//

	SynchStopped();
	m_fICSStarted = FALSE;
}

//----------------------------------------------------------------------

//
//	Cancel button processing.
//

void CICSDemoDlg::OnCancel() 
{
	OnStop();

	CDialog::OnCancel();
}

//----------------------------------------------------------------------

//
//	OK button processing.
//

void CICSDemoDlg::OnOK() 
{
	OnStop();
	
	CDialog::OnOK();
}

//----------------------------------------------------------------------

//
//	UI state transition control functions
//

void CICSDemoDlg::SynchStopped(void)
{
	((CButton *)GetDlgItem(IDC_START))->EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_SYNCH))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_STOP))->EnableWindow(FALSE);

	GotoDlgCtrl(GetDlgItem(IDC_START));
	SetDefID(IDC_START);
}

void CICSDemoDlg::SynchStarted(void)
{
	((CButton *)GetDlgItem(IDC_START))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_SYNCH))->EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_STOP))->EnableWindow(TRUE);

	GotoDlgCtrl(GetDlgItem(IDC_SYNCH));
	SetDefID(IDC_SYNCH);
}



//----------------------------------------------------------------------

/* THE METHODS BELOW ARE NOT CURRENTLY USED, BUT THEY WILL BE
   USEFUL FOR PERSISTING THE STATE OF THE STREAMS HERE
  */

// Does not check for absence of file, or 
// invalid entryID
HRESULT CICSDemoDlg::Load()
{
	
	ASSERT(m_hMemBlock != NULL);
	ASSERT(m_lpSynchState != NULL);
	
	HANDLE hFile = CreateFile("synch.sav", 
								GENERIC_READ,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}

	DWORD fileSize = GetFileSize(hFile, NULL);
	void * output = new BYTE[fileSize];
	
	LARGE_INTEGER zero;
	zero.HighPart = 0x0000;
	zero.LowPart = 0x0000;
	zero.QuadPart = 0x00000000;

	LPDWORD outRes = new DWORD;
	BOOL bResult = ReadFile(hFile,
							output,
							fileSize,
							outRes,
							NULL);


	CloseHandle(hFile);

	HRESULT hResult = m_lpSynchState->Seek(zero,
										   STREAM_SEEK_SET,
										   NULL);

	hResult = m_lpSynchState->Write(output, 
									fileSize,
									NULL);

  return S_OK;
}

  

  
HRESULT CICSDemoDlg::Save()
{
	HANDLE hFile = CreateFile("synch.sav", 
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}


	STATSTG synchStateStats;
	HRESULT hResult = m_lpSynchState->Stat(&synchStateStats,
										   STATFLAG_DEFAULT);

	void * output = new BYTE[synchStateStats.cbSize.LowPart];
	
	m_lpSynchState->Commit(STGC_DEFAULT);

	ULARGE_INTEGER nextSeek;
	LARGE_INTEGER zero;
	zero.HighPart = 0x0000;
	zero.LowPart = 0x0000;
	zero.QuadPart = 0x00000000;

	hResult = m_lpSynchState->Seek(zero,
								   STREAM_SEEK_SET,
								   &nextSeek);

	hResult = m_lpSynchState->Read(output, 
									synchStateStats.cbSize.LowPart,
									NULL);

	LPDWORD outRes = new DWORD;
	LPCVOID lpBuffer = "test";

	// May have to instantiate IStream ourselves
	BOOL bResult = WriteFile(hFile,
							output,
							synchStateStats.cbSize.LowPart,
							outRes,
							NULL);


	CloseHandle(hFile);
	m_lpSynchState->Revert();

	return S_OK;
}


