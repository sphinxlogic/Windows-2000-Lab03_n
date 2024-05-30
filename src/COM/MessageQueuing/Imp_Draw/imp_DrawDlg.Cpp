// Imp_DrawDlg.cpp : implementation file
//
//=--------------------------------------------------------------------------=
// Copyright  1997-1998  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#include "stdafx.h"
#include <afxdisp.h>
#include "Imp_Draw.h"
#include "Imp_DrawDlg.h"
#include "logindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImp_DrawDlg dialog

CImp_DrawDlg::CImp_DrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImp_DrawDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImp_DrawDlg)
	m_csFriendName = _T("");
	m_iRadio = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Initialize my data members	
	m_vtguidDraw = "{151ceac0-acb5-11cf-8b51-0020af929546}";
	m_vtFriendName = "";
	m_pHandler = NULL;
}

CImp_DrawDlg::~CImp_DrawDlg()
{
	if (m_pHandler)
		delete m_pHandler;	// Handler's destructor will release event object
};

void CImp_DrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImp_DrawDlg)
	DDX_Control(pDX, IDC_DRAWAREA_SCRIBLLE, m_drawScribble);
	DDX_Text(pDX, IDC_EDIT_FRIEND, m_csFriendName);
	DDX_Radio(pDX, IDC_RADIO_EXPRESS, m_iRadio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImp_DrawDlg, CDialog)
	//{{AFX_MSG_MAP(CImp_DrawDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ATTACH, OnButtonAttach)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//=--------------------------------------------------------------------------=
// CImp_DrawDlg::GetUserName
// CImp_DrawDlg::GetComputerName
//=--------------------------------------------------------------------------=
// Purpose: These functions wrap the GetUserName and GetComputerName Win32 APIs
//  
// Parameters:
//    none
//
// Output:
//    CString	-	the user name of the currently logged in user, or the
//					or the computer name of this computer.
//

CString CImp_DrawDlg::GetUserName()
{
	DWORD dwsize = 255;
	char username[255];
	if (::GetUserName(&username[0], &dwsize))
		return username;
	return "";
};

CString CImp_DrawDlg::GetComputerName()
{
	DWORD dwsize = 255;
	char username[255];
	if (::GetComputerName(&username[0], &dwsize))
		return username;
	return "";
}

//=--------------------------------------------------------------------------=
// CImp_DrawDlg::LoginPrompt
//=--------------------------------------------------------------------------=
// Purpose: This function pops up a login dialog and returns the name given
//  
//
// Parameters:
//    CString	-	This name will be given as a default name in the dialog
//
// Output:
//    CString	-	This is the name given by the user.
//
// 
CString CImp_DrawDlg::LoginPrompt(CString DefaultName)
{
	CLoginDlg	dialog;
	dialog.m_strLogin = DefaultName;
	dialog.DoModal();
	return dialog.m_strLogin;
};

//=--------------------------------------------------------------------------=
// CImp_DrawDlg::SendMouseMovement
//=--------------------------------------------------------------------------=
// Purpose: This function sends my mouse movement information to the m_qFriend queue
//  
//
// Parameters:
//    LINE		-	this is a custom type defined in Drawarea.h
//
// Output:
//    none
//
// Notes:
//    This function encodes line data into a string, and passes that string
//		as the body of an MSMQ message.  This function is called by the 
//		CDrawArea class, which was ported from the MSMQ C_Draw sample.
// 
void CImp_DrawDlg::SendMouseMovement(LINE line)
{
	try
	{
		if (m_qFriend != NULL && m_qFriend->IsOpen)
		{
			m_msgOut->Priority = 3;

			/* Pack the data into one line (twice) */
			WCHAR wcsBody[MAX_MSG_BODY_LEN];
			swprintf(wcsBody, L"%07ld%07ld%07ld%07ld", 
					 line.ptStart.x, line.ptStart.y, line.ptEnd.x, line.ptEnd.y);

			WCHAR wcsLabel[MQ_MAX_MSG_LABEL_LEN];
			swprintf(wcsLabel, L"%ld,%ld To %ld,%ld", 
					 line.ptStart.x, line.ptStart.y, line.ptEnd.x, line.ptEnd.y);

			/* Initialize a variant with the wcsbody data */
			_variant_t	vtBody(wcsBody);
			
			// Setup the message properties
			m_msgOut->Body = vtBody;
			m_msgOut->Label = wcsLabel;
			m_msgOut->Delivery = m_iRadio;

			// Send the message
			m_msgOut->Send(m_qFriend);
		};
	}
	catch(_com_error comerr)
	{
		HandleErrors(comerr);
	};
};

//=--------------------------------------------------------------------------=
// CImp_DrawDlg::SendKeystroke
//=--------------------------------------------------------------------------=
// Purpose: This function sends my mouse movement information to the m_qFriend 
//			queue
//  
//
// Parameters:
//    uChar		-	Character value of keystroke to send.
//
// Output:
//    none
//
// Notes:
//    This function is a pretty straightforward way to send an MSMQ message.
//    This function is called by the CDrawArea class, which was ported from 
//	  the MSMQ C_Draw sample.
//
// 
void CImp_DrawDlg::SendKeystroke(UINT uChar)
{
	try
	{
		// First, the friend queue must be defined, and open
		if (m_qFriend != NULL && m_qFriend->IsOpen)
		{
			// Next, I push the character into a variant
			_variant_t vtChar((char*)&uChar);

			// Now I set up the message properties
			m_msgOut->Priority = 4;
			m_msgOut->Body = &vtChar;
			m_msgOut->Label = "Key: " + uChar;
			m_msgOut->Delivery = m_iRadio;

			// Lastly, I send the message
			m_msgOut->Send(m_qFriend);
		};
	}
	catch(_com_error comerr)
	{
		HandleErrors(comerr);
	};
};

//=--------------------------------------------------------------------------=
// CImp_DrawDlg::Arrived
//=--------------------------------------------------------------------------=
// Purpose: This function handles events received from the opened queue.
//  
//
// Parameters:
//    IDispatch*		-	The queue sending the event
//	  lErrorCode		-	S_OK if no error, otherwise the error code sent
//							along with the queue event.
//	  lCursor			-	Cursor value sent with the event.  Unused in
//							this function.
//
// Output:
//    none
//
// Notes:
//    The queue is opened in the OnInitDialog() function.  An error event will
//	  popup a dialog and return from the function.  For a normal event I retrieve
//	  the message body, and interpret it either as a keystroke or as line data.
//	  Once you are finished handling an event you must signal your queue that you
//	  are ready to receive another event.
//
void CImp_DrawDlg::Arrived(IDispatch* pdispQueue, long lErrorCode, long lCursor)
{
	if (lErrorCode != S_OK)
	{
		// This code is what will run if the _DMSMQEventEvents->ArrivedError() Event is called
		char* szErr = "";
		itoa(lErrorCode, szErr, 16);
		CString tempString = "Method returned HRESULT: ";
		tempString += szErr;
		MessageBox(tempString, NULL, MB_ICONSTOP | MB_OK);
		return;
	};

	IMSMQMessagePtr msgIn;
	LINE			line;
	char*			strTextIn = "";
	_variant_t		vtTimeout((short) 100);
	_bstr_t			btBody;


	try
	{
		IMSMQQueuePtr	q(pdispQueue);		// Creates a Queue smart pointer pointing to pdispQueue
		msgIn = q->Receive(&vtMissing, &vtMissing, &vtMissing, &vtTimeout);	// Any messages?
		btBody = msgIn->Body;				// copy message body to my own bstr
		strTextIn = (char*) btBody;			// convert to char*
		if (strlen(strTextIn) == 1)		
			m_drawScribble.AddKeystroke(strTextIn);
		else
		{
       		sscanf(strTextIn, "%07ld%07ld%07ld%07ld", 
				&line.ptStart.x, &line.ptStart.y, 
				&line.ptEnd.x, &line.ptEnd.y);
			m_drawScribble.AddLine(line);
		};
	}
	catch(_com_error comerr)
	{
		HandleErrors(comerr);
	};

	m_queue->EnableNotification(m_qevent);		// IMPORTANT: Once you receive an event you must re-enable 
												// event notification
};


//=--------------------------------------------------------------------------=
// CImp_DrawDlg::HandleErrors
//=--------------------------------------------------------------------------=
// Purpose: This pops up an error dialog and aborts further execution
//  
//
// Parameters:
//    _com_error
//
// Output:
//    none
//
// Notes:
//    This demonstrates how to pull and HRESULT from the _com_error class.
//
void CImp_DrawDlg::HandleErrors(_com_error comerr)
{
	HRESULT hr = comerr.Error();
	char* szErr = "";
	itoa(hr, szErr, 16);
	CString tempString = "Method returned HRESULT: ";
	tempString += szErr;
	tempString += ".  Exiting.";
	MessageBox(tempString, NULL, MB_ICONSTOP | MB_OK);
	AfxAbort();
};

/////////////////////////////////////////////////////////////////////////////
// CImp_DrawDlg message handlers

//=--------------------------------------------------------------------------=
// CImp_DrawDlg::OnInitDialog
//=--------------------------------------------------------------------------=
// Purpose: This handles the WM_INITDIALOG message by getting a login name 
//			from the user, opening their queue (creating it if need be) and
//			registering for events from that queue.
//  
//
// Parameters:
//    none
//
// Output:
//    BOOL	- to indicate success or failure to initialize the dialog.
//
// Notes:
//		This is the dialog initialization code.  The algorithm used in the try-catch 
//		block is taken from the MSMQ VB_Draw sample, in many cases on a 
//		line-for-line basis.
//

BOOL CImp_DrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	// First, we have to initialize COM
	HRESULT hr = AfxOleInit();

	try
	{
		CString	csDefaultQueueName;
		CString	csComputerName;

		IMSMQQueryPtr		query("MSMQ.MSMQQuery");
		IMSMQQueueInfoPtr	qinfo;
		IMSMQQueueInfosPtr	qinfos;

		// Note:  You can instantiate a smart pointer from a ProgID using either of
		// two methods.  As above (the query object) you can pass the ProgID during
		// construction or as below (m_msgOut) you can call the CreateInstance() 
		// member function.

		m_msgOut.CreateInstance("MSMQ.MSMQMessage");
		csDefaultQueueName = GetUserName();
		m_csLogin = LoginPrompt(csDefaultQueueName);	// Present login dialog
		if (m_csLogin == "")
			return FALSE;
		m_csLogin.MakeUpper();
		SetWindowText(m_csLogin);

		m_vtLogin = m_csLogin;
		qinfos = query->LookupQueue(&vtMissing,&m_vtguidDraw, &m_vtLogin);  // Look for user's queue
		qinfos->Reset();
		qinfo = qinfos->Next();

		if (qinfo == NULL)				// if it doesn't exist, we'll create it
		{
			qinfo.CreateInstance("MSMQ.MSMQQueueInfo");
			csComputerName = GetComputerName();
			if (csComputerName == "")
				csComputerName = ".";
			qinfo->PathName = (_bstr_t) LPCTSTR(csComputerName + "\\" + m_csLogin);
			qinfo->Label = (_bstr_t) LPCTSTR(m_csLogin);
			qinfo->ServiceTypeGuid = (_bstr_t) m_vtguidDraw;
			qinfo->Create();			// Create this queue
		};
		for (int i = 0; i < 5; i++)
		{
			// We'll try to open it five times in case the creation takes time to replicate
			try
			{
				m_queue = NULL;
				m_queue = qinfo->Open(MQ_RECEIVE_ACCESS, MQ_DENY_NONE);
				if (m_queue != NULL)
					i=5;
			}
			catch (_com_error comerr)
			{
				hr = comerr.Error();
				if (hr != MQ_ERROR_QUEUE_NOT_FOUND)
					throw comerr;
			};
		};

		if (m_queue == NULL)
		{
			MessageBox("Could not open your queue after five tries", MB_OK);
			return FALSE;
		};

		// Now we'll link up with the event source
		// the first five lines below imitate the VB lines

		// Dim WithEvents m_qevent as MSMQ.MSMQEvent
		// Set m_qevent = new MSMQ.MSMQEvent

		m_qevent.CreateInstance("MSMQ.MSMQEvent");
		if (m_pHandler)
			delete m_pHandler;
		m_pHandler = new CMSMQEventHandler();
		hr = m_pHandler->AdviseSource(m_qevent);

		if (SUCCEEDED(hr))
			hr = m_queue->EnableNotification(m_qevent);		// if we connected in Advise Source, 
															// tell MSMQ that we want events.

	}
	catch (_com_error comerr)
	{
		HandleErrors(comerr);
	};

	m_iRadio = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//=--------------------------------------------------------------------------=
// CImp_DrawDlg::OnButtonAttach
//=--------------------------------------------------------------------------=
// Purpose: This handles the Attach button by looking for the friend queue the
//			user has indicated, then opening that queue if possible.
//			
//
// Parameters:
//    none
//
// Output:
//    none
//
// Notes:
//		This is a straightforward way to look for a queue, then open it.
//		This is the last function modified for this project.  The next two
//		below were generated by MFC.
//

void CImp_DrawDlg::OnButtonAttach() 
{

	try
	{
		IMSMQQueryPtr		queryFriend("MSMQ.MSMQQuery");	// Creates a Query object
		IMSMQQueueInfoPtr	qinfoFriend;
		IMSMQQueueInfosPtr	qinfos;

		UpdateData(TRUE);
		m_csFriendName.MakeUpper();
		m_vtFriendName = m_csFriendName;

		qinfos = queryFriend->LookupQueue(&vtMissing,&m_vtguidDraw, &m_vtFriendName);
		qinfos->Reset();
		qinfoFriend = qinfos->Next();
		if (qinfoFriend == NULL)
		{
			MessageBox("No such friend, sorry...");
		}
		else
		{
			// If we have another friend queue open, close it.
			if (m_qFriend != NULL && m_qFriend->IsOpen)
				m_qFriend->Close();

			m_qFriend = qinfoFriend->Open(MQ_SEND_ACCESS, MQ_DENY_NONE);
			SetWindowText(m_csLogin + " - Connected to " + m_csFriendName);
		};
	}
	catch (_com_error comerr)
	{
		HandleErrors(comerr);
	};
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImp_DrawDlg::OnPaint() 
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
HCURSOR CImp_DrawDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

