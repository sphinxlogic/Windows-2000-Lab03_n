/*[]---------------------------------------------------------------------[]*/
/*|                                                                       |*/
/*|   This sample program demonstrates how to call, in a Microsoft        |*/
/*|   Foundation Classes application, the Properties, Methods and Events  |*/
/*|   exposed by the new Microsoft MediaPlayer v5.2.                      |*/
/*|                                                                       |*/
/*[]---------------------------------------------------------------------[]*/

// NShowMFCDlg.cpp : implementation file
//
#include "stdafx.h"
#include "NShowMFC.h"
#include "NShowMFCDlg.h"
#include "mediaplayer.h"

#include <commdlg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *OpenStates[] = {   // Player OpenStates. Returned by the OpenState property or passed in via OpenStateChange()
    "Closed",            // 0 - nsClosed
    "Loading ASX",       // 1 - NsLoadingASX
    "Loading NSC",       // 2 - NsLoadingNSC
    "Locating",          // 3 - NsLocating
    "Connecting",        // 4 - nsConnecting
    "Opening",           // 5 - nsOpening
    "Open"               // 6 - nsOpen
};

char *PlayStates[] = {   // Player PlayStates. Returned by the PlayState property or passed in via PlayStateChange() 
    "Stopped",           // 0 - mpStopped   
    "Paused",            // 1 - mpPaused
    "Playing",           // 2 - mpPlaying
    "Waiting",           // 3 - mpWaiting
    "ScanForward",       // 4 - mpScanForward
    "ScanReverse",       // 5 - mpScanReverse
    "SkipForward",       // 6 - mpSkipForward
    "SkipReverse",       // 7 - mpSkipReverse
    "Closed"             // 8 - mpClosed
};

char *ReadyStates[] = {  // Player ReadyStates. Returned by the ReadyState property or passed in via ReadyStateChange()
    "Uninitialized",     // 0 - mpReadyStateUninitialized
    "Loading",           // 1 - mpReadyStateloading
    "",                  // 2 - reserved
    "Interactive",       // 3 - mpReadyStateInteractive
    "Complete"           // 4 - mpReadyStateComplete
};

#define MAX_OPENSTATES  (sizeof(OpenStates) / sizeof(char *))
#define MAX_PLAYSTATES  (sizeof(PlayStates) / sizeof(char *))
#define MAX_READYSTATES (sizeof(ReadyStates) / sizeof(char *))

#define ID_BUFFERING_EVENT  0x18121812
#define ID_PLAYTIME_EVENT   0x21122112

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNShowMFCDlg dialog

CNShowMFCDlg::CNShowMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNShowMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNShowMFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNShowMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNShowMFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::calc_time()

Prototype:      void CNShowMFCDlg::calc_time (double, int, int);

Description:    Convert player duration from seconds to minute seconds.

Entry:          double  - [in]  player duration in seconds
                int *   - [out] time in minutes
                int *   - [out] time in seconds

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::calc_time (double time_seconds, int *minutes, int *seconds)
{
    *minutes = (int)time_seconds / 60;
    *seconds = (int)time_seconds % 60;

}   /*  end CNShowMFCDlg::calc_time() */

/////////////////////////////////////////////////////////////////////////////
// CNShowMFCDlg message handlers

BEGIN_MESSAGE_MAP(CNShowMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CNShowMFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(ID_FILE_OPEN, OnFileOpen)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CNShowMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    m_CurrentTime = 0;

    // Extract ASF file name from app resources
    //
//    CString strAsfFileName;
//    strAsfFileName.LoadString(IDS_ASF_FILENAME);
	
    // Get MediaPlayer object and set initial properties.
    //
    CMediaPlayer *pMediaPlayer = (CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1);

//    pMediaPlayer->SetShowControls(FALSE);
//    pMediaPlayer->SetShowGotoBar(FALSE);
//    pMediaPlayer->SetShowStatusBar(FALSE);
//    pMediaPlayer->SetAllowChangeDisplaySize(TRUE);

//    pMediaPlayer->SetAutoStart(FALSE);
//    pMediaPlayer->SetSendPlayStateChangeEvents(TRUE);
//    pMediaPlayer->SetFileName(strAsfFileName);

char szBuffer[MAX_PATH];
int minutes, seconds;

    // Get the player's duration, breakout time in seconds to minutes and seconds
    //
    calc_time(pMediaPlayer->GetDuration(), &minutes, &seconds);
    wsprintf(szBuffer, "%002.2d:%002.2d (mm:ss)", minutes, seconds);
    GetDlgItem(IDC_TEXTBOX_STATUS_DURATION)->SetWindowText((LPCSTR)szBuffer);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CNShowMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNShowMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNShowMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// NetShow Player functions below, event handlers at end of file.

/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnBtnPlay()

Prototype:      void CNShowMFCDlg::OnBtnPlay ();

Description:    Event handler for IDC_BTN_PLAY.
                Calls MediaPlayer's Play() method to
                start playing loaded media.

Entry:          nothing

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnBtnPlay () 
{
    CMediaPlayer *pMediaPlayer = (CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1);
    pMediaPlayer->Play();

}   /*  end CNShowMFCDlg::OnBtnPlay() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnBtnPause()

Prototype:      void CNShowMFCDlg::OnBtnPause ();

Description:    Event handler for IDC_BTN_PAUSE.
                Calls MediaPlayer's Pause() method to
                suspend playing loaded media.

Entry:          nothing

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnBtnPause() 
{
    CMediaPlayer *pMediaPlayer = (CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1);
    pMediaPlayer->Pause();

}   /*  end CNShowMFCDlg::OnBtnPause() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnBtnStop()

Prototype:      void CNShowMFCDlg::OnBtnStop ();

Description:    Event handler for IDC_BTN_STOP.
                Calls MediaPlayer's Stop() method to
                cease playing loaded media.

Entry:          nothing

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnBtnStop() 
{
    CMediaPlayer *pMediaPlayer = (CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1);
    pMediaPlayer->Stop();
    pMediaPlayer->SetCurrentPosition(0);	// rewind the current selection

}   /* end CNShowMFCDlg::OnBtnStop() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnFileOpen()

Prototype:      void CNShowMFCDlg::OnFileOpen ();

Description:    Event handler for ID_FILE_OPEN.
                used to load a new .ASF, .ASX, .RM or other
                type of media file.

Entry:          nothing

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnFileOpen () 
{
    char szBuffer[MAX_PATH];
    int minutes, seconds;

    CMediaPlayer *pMediaPlayer = (CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1);

    CFileDialog dlg(TRUE, "asf", "", OFN_FILEMUSTEXIST, "Active Streaming Format (*.asf)|*.asf|Active Streaming Redirector (*.asx)|*.asx|RealAudio/RealVideo (*.rm)|*.rm|All Files (*.*)|*.*||");

    if (dlg.DoModal() == IDOK) {
        pMediaPlayer->SetFileName(dlg.GetPathName());                       // set the new filename into the player
        calc_time(pMediaPlayer->GetDuration(), &minutes, &seconds);         // convert stream duration seconds to min and secs.
        wsprintf(szBuffer, "%002.2d:%002.2d (mm:ss)", minutes, seconds);
        GetDlgItem(IDC_TEXTBOX_STATUS_DURATION)->SetWindowText((LPCSTR)szBuffer);
    }

}   /*  end CNShowMFCDlg::OnFileOpen() */


// Adding events fired from the Media Player control are handles below.
// ClassWizard
//
BEGIN_EVENTSINK_MAP(CNShowMFCDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CNShowMFCDlg)
	ON_EVENT(CNShowMFCDlg, IDC_MEDIAPLAYER1, 3001 /* ScriptCommand */, OnScriptCommandMediaplayer1, VTS_BSTR VTS_BSTR)
	ON_EVENT(CNShowMFCDlg, IDC_MEDIAPLAYER1, 3006 /* MarkerHit */, OnMarkerHitMediaplayer1, VTS_I4)
	ON_EVENT(CNShowMFCDlg, IDC_MEDIAPLAYER1, 3011 /* OpenStateChange */, OnOpenStateChangeMediaplayer1, VTS_I4 VTS_I4)
	ON_EVENT(CNShowMFCDlg, IDC_MEDIAPLAYER1, 3012 /* PlayStateChange */, OnPlayStateChangeMediaplayer1, VTS_I4 VTS_I4)
	ON_EVENT(CNShowMFCDlg, IDC_MEDIAPLAYER1, -609 /* ReadyStateChange */, OnReadyStateChangeMediaplayer1, VTS_I4)
	ON_EVENT(CNShowMFCDlg, IDC_MEDIAPLAYER1, 3003 /* Buffering */, OnBufferingMediaplayer1, VTS_BOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnScriptCommandMediaplayer1()

Prototype:      void CNShowMFCDlg::OnScriptCommandMediaplayer1 (LPCTSTR, LPCTSTR);

Description:    MediaPlayer ScriptCommand event handler.
                Called when the MediaPlayer fires the event.

Entry:          LPCTSTR - [in] Script Command Type
                LPCTSTR - [in] Script Command Param

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnScriptCommandMediaplayer1 (LPCTSTR scType, LPCTSTR Param) 
{
    GetDlgItem(IDC_TEXTBOX_SCRIPT_TYPE)->SetWindowText(scType);     // display command type
    GetDlgItem(IDC_TEXTBOX_SCRIPT_CMD)->SetWindowText(Param);       // display command parameter

}   /*  end CNShowMFCDlg::OnScriptCommandMediaplayer1() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnMarkerHitMediaplayer1()

Prototype:      void CNShowMFCDlg::OnMarkerHitMediaplayer1 (long);

Description:    MediaPlayer MarkerHit event handler.
                Called when the MediaPlayer fires the event.

Entry:          long    - [in] Current marker

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnMarkerHitMediaplayer1 (long MarkerNum) 
{
    char szBuffer[MAX_PATH];
    int marker_time_minutes, marker_time_seconds;
    CMediaPlayer *pMediaPlayer = (CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1);

    calc_time(pMediaPlayer->GetMarkerTime(MarkerNum), &marker_time_minutes,
                                                      &marker_time_seconds);

    wsprintf(szBuffer, "%002.2d:%002.2d (mm:ss)", marker_time_minutes, marker_time_seconds);
    GetDlgItem(IDC_TEXTBOX_MARKER_NAME)->SetWindowText((LPCSTR)pMediaPlayer->GetMarkerName(MarkerNum));
    GetDlgItem(IDC_TEXTBOX_MARKER_TIME)->SetWindowText((LPCSTR)szBuffer);

}   /*  end CNShowMFCDlg::OnMarkerHitMediaplayer1() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnOpenStateChangeMediaplayer1()

Prototype:      void CNShowMFCDlg::OnOpenStateChangeMediaplayer1 (long, long);

Description:    MediaPlayer OpenStateChange event handler.
                Called when the MediaPlayer fires the event.

Entry:          long    - [in] old OpenState  (See the SDK documentation
                long    - [in] new OpenState   for more information)

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnOpenStateChangeMediaplayer1 (long OldState, long NewState) 
{
    if ((NewState >= 0) && (NewState < MAX_OPENSTATES))
        GetDlgItem(IDC_TEXTBOX_STATUS_OPENSTATE)->SetWindowText(OpenStates[NewState]);

}   /*  end CNShowMFCDlg::OnOpenStateChangeMediaplayer1() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnPlayStateChangeMediaplayer1()

Prototype:      void CNShowMFCDlg::OnPlayStateChangeMediaplayer1 (long, long);

Description:    MediaPlayer PlayStateChange event handler.
                Called when the MediaPlayer fires the event.

Entry:          long    - [in] old PlayState  (See the SDK documentation
                long    - [in] new PlayState   for more information)

Returns:        void    - nothing
*--------------------------------------------------------------------*/

#define STOPPED 0
#define PAUSED  1
#define PLAYING 2

void CNShowMFCDlg::OnPlayStateChangeMediaplayer1 (long OldState, long NewState) 
{
    if ((NewState >= 0) && (NewState < MAX_PLAYSTATES))
        GetDlgItem(IDC_TEXTBOX_STATUS_PLAYSTATE)->SetWindowText(PlayStates[NewState]);

    switch (NewState) {
        case STOPPED:
            m_CurrentTime = 0;
            GetDlgItem(IDC_TEXTBOX_PLAYTIME)->SetWindowText("00:00 (mm:ss)");
            // NOTE!!  Fall thru to KillTimer() on purpose!
        case PAUSED:
            KillTimer(ID_PLAYTIME_EVENT);
            break;
        case PLAYING:
            SetTimer(ID_PLAYTIME_EVENT, 1000, NULL);
    }

}   /*  end CNShowMFCDlg::OnPlayStateChangeMediaplayer1() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnReadyStateChangeMediaplayer1()

Prototype:      void CNShowMFCDlg::OnReadyStateChangeMediaplayer1 (long);

Description:    MediaPlayer ReadyStateChange event handler.
                Called when the MediaPlayer fires the event.

Entry:          long    - [in] ReadyState  (See the SDK documentation for more information)

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnReadyStateChangeMediaplayer1 (long ReadyState) 
{
    if ((ReadyState >= 0) && (ReadyState < MAX_READYSTATES))
        GetDlgItem(IDC_TEXTBOX_STATUS_READYSTATE)->SetWindowText(ReadyStates[ReadyState]);

}   /*  end CNShowMFCDlg::OnReadyStateChangeMediaplayer1() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnBufferingMediaplayer1()

Prototype:      void CNShowMFCDlg::OnBufferingMediaplayer1 (BOOL);

Description:    MediaPlayer Buffering event handler.
                Called when the MediaPlayer fires the event.

Entry:          BOOL    - [in] Start  (See the SDK documentation for more information)

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnBufferingMediaplayer1 (BOOL Start) 
{
    if (Start) {
        SetTimer(ID_BUFFERING_EVENT, 10, NULL);
        GetDlgItem(IDC_TEXTBOX_BUFFERING)->SetWindowText("Buffering");
    } else {
        KillTimer(ID_BUFFERING_EVENT);
        GetDlgItem(IDC_TEXTBOX_BUFFERING)->SetWindowText("");
        GetDlgItem(IDC_TEXTBOX_BUFFERING_PERCENT)->SetWindowText("");
    }

}   /*  end CNShowMFCDlg::OnBufferingMediaplayer1() */


/*-------------------------------------------------------------------*
Function:       CNShowMFCDlg::OnTimer()

Prototype:      void CNShowMFCDlg::OnTimer (UINT);

Description:    Handles timer events.  Standard Win32 timer.

Entry:          UINT    - [in] timer id.  (See Win32 docs about Timers)

Returns:        void    - nothing
*--------------------------------------------------------------------*/

void CNShowMFCDlg::OnTimer (UINT nIDEvent) 
{
    int minutes, seconds;
    char szBuffer[MAX_PATH];
            
    switch (nIDEvent) {
        case ID_BUFFERING_EVENT:
            wsprintf(szBuffer, "%ld", ((CMediaPlayer *)GetDlgItem(IDC_MEDIAPLAYER1))->GetBufferingProgress());
            GetDlgItem(IDC_TEXTBOX_BUFFERING_PERCENT)->SetWindowText(szBuffer);
            break;
        case ID_PLAYTIME_EVENT:
            calc_time((m_CurrentTime++), &minutes, &seconds);
            wsprintf(szBuffer, "%002.2d:%002.2d (mm:ss)", minutes, seconds);
            GetDlgItem(IDC_TEXTBOX_PLAYTIME)->SetWindowText(szBuffer);
    }

    CDialog::OnTimer(nIDEvent);
            
}   /*  end CNShowMFCDlg::OnTimer() */
