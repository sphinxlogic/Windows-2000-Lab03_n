#define UNICODE

#include <windows.h>
#include <tapi3.h>
#include <stdio.h>
//#include <varargs.h>
#include "callnot.h"
#include "resource.h"

//////////////////////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////////////////////
const DWORD MAXTERMINALS    = 5;

//////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////

HINSTANCE               ghInst;
ITTAPI *                gpTapi;
ITBasicCallControl *    gpCall;
ITTAPICallCenter   *    gpCallCentre;
HWND                    ghDlg = NULL, ghDlg1 = NULL;

ITAgent            *    gpAgent;
ITAgentSession     *    gpAgentSession;
ITAgentHandler     *    gpAgentHandler;
ITAddress          *    gpAddress;
ITACDGroup         *    gpACDGroup;
ITQueue            *    gpQueue;


HWND ghAgentHandlerComboBox;
HWND ghAddressComboBox;
HWND ghACDGroupComboBox;
HWND ghQueueComboBox;

WCHAR gszTapi30[] = L"TAPI 3.0 Sample ACD client application";

CTAPIEventNotification      * gpTAPIEventNotification;
ULONG                         gulAdvise;

//////////////////////////////////////////////////////////
// PROTOTYPES
//////////////////////////////////////////////////////////
BOOL
CALLBACK
MainDialogProc(
               HWND ,
               UINT ,
               WPARAM ,
               LPARAM
              );

BOOL
CALLBACK
SecondDialogProc(
                 HWND,
                 UINT,
                 WPARAM,
                 LPARAM
                );

HRESULT
RegisterTapiEventInterface( void );

HRESULT 
AnswerTheCall( void );

HRESULT
DisconnectTheCall( void );

HRESULT
ListenOnThisAddress( ITAddress * );

void
ReleaseTheCall( void );

void
DoMessage( HWND, LPWSTR );

void
SetStatusMessage( HWND, int, LPWSTR );

void
ShowAgentStatus( HWND, LPWSTR );

void
ShowSessionStatus( HWND, LPWSTR );

void
ShowQueueStatus( HWND, LPWSTR );

void
GetAgentStats(HWND);

void
GetSessionStats(HWND);

void
GetQueueStats(HWND);

HRESULT
InitializeTapi( void );

void
ShutdownTapi( void );

void
EnableButton( int, int );

void
DisableButton( int, int );

BOOL
InitAgentHandlerListBox( void );

BOOL
InitHandlerDetailsListBoxes( void );

BOOL
InitQueueListBox( void );

//////////////////////////////////////////////////////////
//
//              FUNCTIONS
//
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// WinMain
//////////////////////////////////////////////////////////
int
WINAPI
WinMain(
        HINSTANCE hInst,
        HINSTANCE hPrevInst,
        LPSTR lpCmdLine,
        int nCmdShow
       )
{
    ghInst = hInst;

    
    // need to coinit
    if (!SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
    {
        return 0;
    }

    // do all tapi initialization
    if (S_OK != InitializeTapi())
    {
        return 0;
    }
    
    // everything is initialized, so
    // start the main dialog box
    DialogBox(
              ghInst,
              MAKEINTRESOURCE(IDD_MAINDLG),
              NULL,
              MainDialogProc
             );


    // clean up
    ShutdownTapi();
    
    CoUninitialize();

    return 1;
}


//////////////////////////////////////////////////////////////
// InitializeTapi
//
// Various initializations
///////////////////////////////////////////////////////////////
HRESULT
InitializeTapi()
{
    HRESULT         hr;
    DWORD           dwCount = 0;

    
    // cocreate the TAPI object
    hr = CoCreateInstance(
                          CLSID_TAPI,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          IID_ITTAPI,
                          (LPVOID *)&gpTapi
                         );

    if (hr != S_OK)
    {
        DoMessage(ghDlg, L"CoCreateInstance on TAPI failed");
        return hr;
    }

    // call initialize.  this must be called before
    // any other tapi functions are called.
    hr = gpTapi->Initialize();

	//Apply filter to receive events of interest

	gpTapi->put_EventFilter(  TE_ADDRESS|TE_CALLNOTIFICATION |
		  TE_CALLSTATE|TE_CALLMEDIA|TE_CALLHUB|TE_CALLINFOCHANGE|
		  TE_AGENT	|TE_AGENTSESSION|TE_AGENTHANDLER|TE_ACDGROUP|
		  TE_QUEUE|TE_GENERATEEVENT);

    if (S_OK != hr)
    {
        DoMessage(ghDlg, L"TAPI failed to initialize");

        gpTapi->Release();
        gpTapi = NULL;
        
        return hr;
    }


    gpTAPIEventNotification = new CTAPIEventNotification;
    
    hr = gpTapi->QueryInterface( IID_ITTAPICallCenter, (void **)&gpCallCentre );

    if (gpCallCentre == NULL)
    {
        DoMessage(ghDlg, L"Couldn't get interface ITTAPICallCentre");
        return hr;
    }

    hr = RegisterTapiEventInterface();

    if( hr != S_OK )
    {
        DoMessage(ghDlg, L"Could'nt register TAPI event interface");
        return hr;
    }
    
    return S_OK;

}


///////////////////////////////////////////////////////////////
// ShutdownTapi
///////////////////////////////////////////////////////////////
void
ShutdownTapi()
{
    // if there is still a call,
    // release it
    if (NULL != gpCall)
    {
        gpCall->Release();
        gpCall = NULL;
    }

    //release CALL Centre object.
    if(NULL != gpCallCentre)
    {
        gpCallCentre->Release();
    }

    // release main object.
    if (NULL != gpTapi)
    {
        gpTapi->Shutdown();
        gpTapi->Release();
    }

    if( NULL != gpAgent )
    {
        gpAgent->Release();
    }

    if( NULL != gpAgentSession )
    {
        gpAgentSession->Release();
    }

    if( NULL != gpAgentHandler )
    {
        gpAgentHandler->Release();
    }

    if( NULL != gpAddress)
    {
        gpAddress->Release();
    }

    if( NULL != gpACDGroup)
    {
        gpACDGroup->Release();
    }

    if( NULL != gpQueue)
    {
        gpQueue->Release();
    }
}


///////////////////////////////////////////////////////////////////////////
// MainDlgProc
//
// The callback procedure for first dialog box
///////////////////////////////////////////////////////////////////////////
BOOL
CALLBACK
MainDialogProc(
               HWND hDlg,
               UINT uMsg,
               WPARAM wParam,
               LPARAM lParam
              )
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            // set up dialog
            ghDlg = hDlg;
            
            DisableButton( 0,IDC_CREATEAGENT );
            EnableButton( 0,IDC_EXIT );
            DisableButton( 0,IDC_CREATESESSION );
            DisableButton ( 0, IDC_OK );

            ghAgentHandlerComboBox = GetDlgItem( ghDlg, IDC_AGENTHANDLERS );
            ghAddressComboBox = GetDlgItem( ghDlg, IDC_ADDRESSES );
            ghACDGroupComboBox = GetDlgItem( ghDlg, IDC_ACDGROUPS );

            gpAgent = NULL;
            gpAgentSession = NULL;

            //Get the list of agent handlers and display them
            BOOL bResult = InitAgentHandlerListBox();
            if( !bResult )
            {
                DoMessage(ghDlg, L"Can not get any Agent Handlers: Hint: Is a proxy running?");
                EndDialog( ghDlg, 0 );
                ShutdownTapi();
                exit(1);
            }

            SetStatusMessage(ghDlg,  0,  L"No agents created.");
            EnableWindow(ghAddressComboBox, false);
            EnableWindow(ghACDGroupComboBox, false);
            return 0;
        }

        case WM_COMMAND:
        {
            if ( LOWORD(wParam) == IDC_CANCEL )
            {
                // quit
                EndDialog( hDlg, 0 );

                return 1;
            }

            switch ( LOWORD(wParam) )
            {
                case IDC_OK:
                {
                    //Agent and session created, user moving on to next dialog
                    EndDialog( hDlg, 0);
                    DialogBox(
                              ghInst,
                              MAKEINTRESOURCE(IDD_DIALOG1),
                              NULL,
                              SecondDialogProc
                              );
                    return 0;
                }

                // create agent request
                case IDC_CREATEAGENT:
                {

                    HRESULT hr;
                        
                    //Get selected agent handler
                    gpAgentHandler = (ITAgentHandler *)SendMessage(
                                                        ghAgentHandlerComboBox,
                                                        CB_GETITEMDATA,
                                                        SendMessage(
                                                          ghAgentHandlerComboBox,
                                                          CB_GETCURSEL,
                                                          0,
                                                          0),
                                                        0);
                    hr = gpAgentHandler->CreateAgent(&gpAgent);
                    //Can also create an agent with ID using the CreateAgentWithID by
                    //providing a PIN and agent ID along with the agent pointer as input.
                    if( hr != S_OK )
                        DoMessage(ghDlg, L"Could not create an agent on handler");
                    else
                    {
                        gpAgentSession = NULL;
                        EnableButton( 0, IDC_CREATESESSION );
                        DisableButton( 0, IDC_CREATEAGENT );
                        EnableWindow(ghAgentHandlerComboBox, false);
                        InitHandlerDetailsListBoxes();
                        SetStatusMessage(ghDlg, 0, L"No session created.");
                    }
                    return 1;
                }

                //session creation request
                case IDC_CREATESESSION:
                {
                    HRESULT hr;

                    ITAgentHandler * pAgentHandler = NULL;

                    //Get selected group and address
                    gpACDGroup = (ITACDGroup *)SendMessage(
                                                  ghACDGroupComboBox,
                                                  CB_GETITEMDATA,
                                                  SendMessage(
                                                     ghACDGroupComboBox,
                                                     CB_GETCURSEL,
                                                     0,
                                                     0),
                                                  0);
                    gpAddress = (ITAddress *)SendMessage(
                                                ghAddressComboBox,
                                                CB_GETITEMDATA,
                                                SendMessage(
                                                    ghAddressComboBox,
                                                    CB_GETCURSEL,
                                                    0,
                                                    0),
                                                0);
                    //try to create session
                    hr = gpAgent->CreateSession(
                                        gpACDGroup,
                                        gpAddress,
                                        &gpAgentSession
                                            );
                    //Can also create a Session with PIN using the CreateAgentWithID by
                    //providing a PIN along with the agent-session , ACD group and
                    //address pointers as input.
                
                    if( hr != S_OK )
                        DoMessage(ghDlg,  L"Could not create a session on agent");
                    else
                    {

                        ListenOnThisAddress(gpAddress);
                        DisableButton( 0, IDC_CREATESESSION );
                        EnableButton( 0, IDC_OK );
                        EnableWindow(ghACDGroupComboBox, false);
                        EnableWindow(ghAddressComboBox, false);
                        SetStatusMessage(ghDlg, 0, L"Agent and session created, press OK to continue, Cancel to exit");
                    }
                    return 1;
                }

                default:
                    return 0;
            }
        }
        default:

            return 0;
    }
}

///////////////////////////////////////////////////////////////////////////
// SecondDlgProc
//
// The callback procedure for second dialog box
///////////////////////////////////////////////////////////////////////////
BOOL
CALLBACK
SecondDialogProc(
               HWND hDlg,
               UINT uMsg,
               WPARAM wParam,
               LPARAM lParam
              )
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            // set up dialog
            ghDlg1 = hDlg;
            
            DisableButton( 1, IDC_ANSWER );
            DisableButton( 1, IDC_DISCONNECT );
            EnableButton( 1, IDC_READY );
            EnableButton( 1, IDC_EXIT );
			GetAgentStats(ghDlg1);
            GetSessionStats(ghDlg1);
			SetStatusMessage(ghDlg1, 1, L"Click Button Agent Ready..");
            ghQueueComboBox = GetDlgItem( ghDlg1, IDC_QUEUES );
            EnableWindow(ghQueueComboBox, false);
            InitQueueListBox();
            return 0;
        }

        case WM_COMMAND:
        {
            if ( LOWORD(wParam) == IDC_EXIT )
            {
                // quit
                EndDialog( hDlg, 0 );

                return 1;
            }

            switch ( LOWORD(wParam) )
            {
                //set agent to ready
                case IDC_READY:
                {
                    //check if there is a call, if so
                    //disconnect it
					DisableButton(1, IDC_READY);
					DisableButton(1, IDC_WRAPUP);
                    if( gpCall != NULL )
                    {
                        SetStatusMessage(ghDlg1, 1, L"Disconnecting...");
                        // disconnect
                        if (S_OK != DisconnectTheCall())
                        {
                            DoMessage(ghDlg1, L"Disconnect failed");
                        }
                        else
                        {
                            if( gpAgent != NULL )
                                gpAgent->put_State(AS_READY);
                            if( gpAgentSession != NULL )
                                gpAgentSession->put_State(ASST_READY);
							
							GetAgentStats(ghDlg1);
							GetSessionStats(ghDlg1);
							
							SetStatusMessage(ghDlg1, 1, L"Waiting for a call..");
							
                        }
                    }
                    else
                    {
                        if( gpAgent != NULL )
                            gpAgent->put_State(AS_READY);
                        if( gpAgentSession != NULL )
                            gpAgentSession->put_State(ASST_READY);
						GetAgentStats(ghDlg1);
						GetSessionStats(ghDlg1);
					
						SetStatusMessage(ghDlg1,  1, L"Waiting for a call..");	
							
                    }
                    return 1;
                }

                // dial request
                case IDC_ANSWER:
                {
                    SetStatusMessage(ghDlg1, 1,   L"Answering...");
                    // answer the call
                    if ( S_OK == AnswerTheCall() )
                    {
                        SetStatusMessage(ghDlg1, 1, L"Connected");

                        EnableButton( 1, IDC_DISCONNECT );
                        DisableButton( 1, IDC_ANSWER );
                        if( gpAgent != NULL )
                            gpAgent->put_State(AS_BUSY_INCOMING);
                        if( gpAgentSession != NULL )
                            gpAgentSession->put_State(ASST_BUSY_ON_CALL);
						GetAgentStats(ghDlg1);
						GetSessionStats(ghDlg1);
						GetQueueStats(ghDlg1);
						
                    }
                    else
                    {
                        DisableButton( 1, IDC_ANSWER );
                        DoMessage(ghDlg1, L"Answer failed");
                        SetStatusMessage(ghDlg1,  1, L"Waiting for a call...");
						GetAgentStats(ghDlg1);
						GetSessionStats(ghDlg1);
						GetQueueStats(ghDlg1);
                    }

                    return 1;
                }

                // disconnect request
                case IDC_DISCONNECT:
                {
                    SetStatusMessage(ghDlg1, 1, L"Disconnecting...");
                    // disconnect
                    if (S_OK != DisconnectTheCall())
                    {
                        DoMessage(ghDlg1, L"Disconnect failed");
                    }
                    else
                    {
                        DisableButton( 1, IDC_DISCONNECT );
                        SetStatusMessage(ghDlg1, 1, L"Waiting for a call...");
                        if( gpAgentSession != NULL )
                            gpAgentSession->put_State(ASST_BUSY_WRAPUP);
						GetAgentStats(ghDlg1);
						GetSessionStats(ghDlg1);
						GetQueueStats(ghDlg1);
                    }
                    return 1;
                }

                // disconnected notification
                case IDC_DISCONNECTED:
                {
                    // release
                    ReleaseTheCall();

                    DisableButton( 1, IDC_DISCONNECT );
					EnableButton( 1, IDC_WRAPUP);
                    if( gpAgentSession != NULL )
                    {
                        AGENT_SESSION_STATE *pSessionState;
                        pSessionState = new AGENT_SESSION_STATE;
                        gpAgentSession->get_State(pSessionState);
                        if( (*pSessionState) == ASST_BUSY_ON_CALL)
                            gpAgentSession->put_State(ASST_BUSY_WRAPUP);
						GetSessionStats(ghDlg1);
                    }
					if ( gpAgent != NULL)
					{
						AGENT_STATE *pAgentState;
                        pAgentState = new AGENT_STATE;
                        gpAgent->get_State(pAgentState);
						if( (*pAgentState) == AS_BUSY_INCOMING)
                            gpAgent->put_State(AS_READY);
						GetAgentStats(ghDlg1);
						GetQueueStats(ghDlg1);	
					}


                    SetStatusMessage(ghDlg1, 1,L"Click Button Agent Wrap Up...");
                    
                    return 1;
                }
				
                case IDC_QUEUES:
                {
                    if( HIWORD(wParam) == CBN_SELCHANGE )
                    {
                        //User has selected a new queue, update stats
                        gpQueue = (ITQueue *)SendMessage(
                                                ghQueueComboBox,
                                                CB_GETITEMDATA,
                                                SendMessage(
                                                    ghQueueComboBox,
                                                    CB_GETCURSEL,
                                                    0,
                                                    0),
                                                0);

                        GetQueueStats(ghDlg1);
                    }
                    return 1;
                }

                case IDC_UPDATEAGENTSTATS:
                {
                    GetAgentStats(ghDlg1);
                    return 1;
                }

                case IDC_UPDATESESSIONSTATS:
                {
                    GetSessionStats(ghDlg1);
                    return 1;
                }

                case IDC_UPDATEQUEUESTATS:
                {
                    GetQueueStats(ghDlg1);
                    return 1;
                }
				case IDC_WRAPUP:
				{       
					    DisableButton( 1, IDC_WRAPUP);
						 if( gpAgentSession != NULL )
						{
							AGENT_SESSION_STATE *pSessionState;
							pSessionState = new AGENT_SESSION_STATE;
							gpAgentSession->get_State(pSessionState);
							if( (*pSessionState) == ASST_BUSY_WRAPUP)
								gpAgentSession->put_State(ASST_READY);
							GetAgentStats(ghDlg1);
							GetSessionStats(ghDlg1);
						 }
						SetStatusMessage(ghDlg1, 1,L"Waiting for a Call...");
                    
                    return 1;
				}


                default:
                    return 0;
            }
        }
        default:

            return 0;
    }
}

/////////////////////////////////////////////////////////////////////
// RegisterTapiEventInterface
/////////////////////////////////////////////////////////////////////
HRESULT
RegisterTapiEventInterface()
{
    HRESULT                       hr = S_OK;
    IConnectionPointContainer   * pCPC;
    IConnectionPoint            * pCP;
   

    hr = gpTapi->QueryInterface(
                                IID_IConnectionPointContainer,
                                (void **)&pCPC
                               );

    if (!SUCCEEDED(hr))
    {
        return hr;
    }

    hr = pCPC->FindConnectionPoint(
                                   IID_ITTAPIEventNotification,
                                   &pCP
                                  );
    pCPC->Release();
        
    if (!SUCCEEDED(hr))
    {
        return hr;
    }
	
    hr = pCP->Advise(
                      gpTAPIEventNotification,
                      &gulAdvise
                     );

    pCP->Release();

    
    return hr;

}


///////////////////////////////////////////////////////////////////
// ListenOnThisAddress
//
// Perform the steps involved in setting up an address to listen
// for calls.  Setting up an application to listen for calls is a two
// step process.
//
// First, the app must call RegisterCallTypes
// on the address that it wants calls on
//
// Second, it must register it's implementation of ITCallNotification
// with the address.  Registration is done via COM's ConnectionPoint
// methods.  See the COM documentation for more informations on
// ConnectionPoints
//    
///////////////////////////////////////////////////////////////////
HRESULT
ListenOnThisAddress(
                    ITAddress * pAddress
                   )
{
    HRESULT                     hr = S_OK;
    long                        lRegister;
    long                        lMediaTypes;
    ITMediaSupport            * pMediaSupport;
    

    //Listen for any type of calls on the address 

    hr = pAddress->QueryInterface(
                                  IID_ITMediaSupport,
                                  (void**)&pMediaSupport
                                 );

    hr = pMediaSupport->get_MediaTypes( &lMediaTypes );

    pMediaSupport->Release();
    
    hr = gpTapi->RegisterCallNotifications(
                                           pAddress,
                                           VARIANT_TRUE,
                                           VARIANT_TRUE,
                                           lMediaTypes,
                                           gulAdvise,
                                           &lRegister
                                          );

    return hr;

}


/////////////////////////////////////////////////////////
// GetTerminal
//
// Creates a Terminal for the bstrMediaType passed
// in, using the default terminal for the bstrMediaType
//
/////////////////////////////////////////////////////////
HRESULT
GetTerminal(
            ITAddress * pAddress,
            long lMediaType,
            TERMINAL_DIRECTION dir,
            ITTerminal ** ppTerminal
           )
{
    HRESULT             hr = S_OK;
    ITTerminalSupport * pTerminalSupport;

    // get the terminal support interface
    pAddress->QueryInterface(IID_ITTerminalSupport,(void **)&pTerminalSupport);

    // get the default terminal for MediaType
   /*hr = pTerminalSupport->GetDefaultTerminal(
                                              lMediaType,
                                              dir,
                                              ppTerminal
                                             );
  
	*/
    pTerminalSupport->Release();

    return hr;

}

/////////////////////////////////////////////////////////
// GetVideoInTerminal
//
// Creates a Terminal for the VideoIn mediatype
// This is a dynamic terminal type.
//
/////////////////////////////////////////////////////////
HRESULT
GetVideoInTerminal(
                 ITAddress * pAddress,
                 ITTerminal ** ppTerminal
                )
{
    HRESULT             hr = S_OK;
    ITTerminalSupport * pTerminalSupport;
    BSTR                bstrTerminalClass;
    LPOLESTR            lpTerminalClass;


    // get the terminal support interface
    pAddress->QueryInterface(IID_ITTerminalSupport,(void **)&pTerminalSupport);

    StringFromIID(
                  CLSID_VideoWindowTerm,
                  &lpTerminalClass
                 );

    bstrTerminalClass = SysAllocString ( lpTerminalClass );

    CoTaskMemFree( lpTerminalClass );

    hr = pTerminalSupport->CreateTerminal(
                                          bstrTerminalClass,
                                          TAPIMEDIATYPE_VIDEO,
                                          TD_RENDER,
                                          ppTerminal
                                         );

    SysFreeString( bstrTerminalClass );

    pTerminalSupport->Release();

    return hr;

}

/////////////////////////////////////////////////////////////////
// CreateTerminals
//
// Create audioin and audioout terminals. Videoin and videoout terminals
// are created only when the address supports them.
//
// This function assumes that ppTerminals has a size no less than four.
/////////////////////////////////////////////////////////////////
HRESULT
CreateTerminals(
                ITAddress *pAddress,
                ITTerminal ** ppTerminals,
                PLONG pNumTerminals
               )
{
    int count = 0;
    HRESULT hr;

    // get the Terminal for audioin
    hr = GetTerminal(
                     pAddress,
                     TAPIMEDIATYPE_AUDIO,
                     TD_RENDER,
                     &ppTerminals[count]
                    );

    if (S_OK != hr)
    {
        return hr;
    }
        count ++;

    // get the Terminal for audioout
    hr = GetTerminal(
                     pAddress,
                     TAPIMEDIATYPE_AUDIO,
                     TD_CAPTURE,
                     &ppTerminals[count]
                    );

    if (S_OK != hr)
    {
        ppTerminals[0]->Release();
        return hr;
    }

    count ++;

    // Find out if the address supports video.
    ITMediaSupport *pMediaSupport;
    VARIANT_BOOL    bSupport;

    pAddress->QueryInterface( IID_ITMediaSupport, (void **)&pMediaSupport );

    // does it support VideoIn?
    pMediaSupport->QueryMediaType(
                                  TAPIMEDIATYPE_VIDEO,
                                  &bSupport
                                 );

    if (bSupport)
    {
        // Assume it's supported in both directions
        hr = GetVideoInTerminal(
                                pAddress,
                                &ppTerminals[count]
                               );

        if (S_OK == hr)
        {
            count ++;
        }

        // get the Terminal for Videoout
        hr = GetTerminal(
                         pAddress,
                         TAPIMEDIATYPE_VIDEO,
                         TD_CAPTURE,
                         &ppTerminals[count]
                        );

        if (S_OK == hr)
        {
            //
            // If we're using the VideoIn terminal we want to use the preview
            //  functionality to make sure we don't look funny.
            //
           /*AV ITPreviewConfig *pPreviewConfig;
            hr = (ppTerminals[count])->QueryInterface(
                                            IID_ITPreviewConfig,
                                            (void**)&pPreviewConfig
                                                     );
            pPreviewConfig->put_EnablePreview(VARIANT_TRUE);
            pPreviewConfig->Release();
			*/
            count ++;
        }
    }
        pMediaSupport->Release();

    *pNumTerminals = count;

    return S_OK;
}

/////////////////////////////////////////////////////////////////
// CreateTerminalSafeArray
//
/////////////////////////////////////////////////////////////////
SAFEARRAY *
CreateTerminalSafeArray(
                        ITTerminal ** ppTerminals,
                        LONG nNumTerminals
                       )
{
    SAFEARRAY *             psa;
    SAFEARRAYBOUND          sabound[1];

    // create a safearray with two elements
    // to pass the Terminals to tapi
    sabound[0].lLbound = 0;
    sabound[0].cElements = nNumTerminals;

    psa = SafeArrayCreate(
                          VT_UNKNOWN,
                          1,
                          sabound
                         );

    if (NULL != psa)
    {
        // save them in the safearray
        for (long i = 0; i < nNumTerminals; i ++)
        {
            SafeArrayPutElement(
                            psa,
                            &i,
                            ppTerminals[i]
                           );
        }
    }
    return psa;
}

/////////////////////////////////////////////////////////////////
// ReleaseTerminals
//
/////////////////////////////////////////////////////////////////
void
ReleaseTerminals(
                      ITTerminal ** ppTerminals,
                      LONG nNumTerminals
                     )
{
    for (long i = 0; i < nNumTerminals; i ++)
    {
        if (ppTerminals[i])
        {
            ppTerminals[i]->Release();
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Answer the call
/////////////////////////////////////////////////////////////////////
HRESULT
AnswerTheCall()
{
    HRESULT                 hr;
    ITCallInfo *            pCallInfo;
    ITAddress *             pAddress;
    ITTerminal *            ppTerminals[MAXTERMINALS];
    long                    nNumTerminals = MAXTERMINALS;
   
   
    
    if (NULL == gpCall)
    {
        return E_UNEXPECTED;
    }


    // get the address object of this call
    gpCall->QueryInterface( IID_ITCallInfo, (void**)&pCallInfo );
    pCallInfo->get_Address( &pAddress );
    pCallInfo->Release();

     // create the media terminals for this call
     hr = CreateTerminals(
        pAddress,
        ppTerminals,
        &nNumTerminals
        );
    

    // release the address
    pAddress->Release();


    if (S_OK != hr)
    {
        gpCall->Release();
        gpCall = NULL;
        return hr;
    }

   /*AV for (lCount = 0; lCount < nNumTerminals; lCount++)
    {
        // call SelectTerminals
        hr = gpCall->SelectTerminal(
                                    ppTerminals[lCount]
                                 );
		
    }


    ReleaseTerminals(ppTerminals, nNumTerminals);*/  

    if (S_OK != hr)
    {
        gpCall->Release();
        gpCall = NULL;
        return hr;
    }
    // answer the call
    hr = gpCall->Answer();
	 if (S_OK != hr)
    {
        gpCall->Release();
        gpCall = NULL;
        return hr;
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////
// DisconnectTheCall
//
// Disconnects the call
//////////////////////////////////////////////////////////////////////
HRESULT
DisconnectTheCall()
{
    HRESULT         hr = S_OK;

    if (NULL != gpCall)
    {
        hr = gpCall->Disconnect( DC_NORMAL );

        
    
        return hr;
    }

    return S_FALSE;
}

//////////////////////////////////////////////////////////////////////
// ReleaseTheCall
//
// Releases the call
//////////////////////////////////////////////////////////////////////
void
ReleaseTheCall()
{
    if (NULL != gpCall)
    {
        gpCall->Release();
        gpCall = NULL;
    }
}


///////////////////////////////////////////////////////////////////
//
// HELPER FUNCTIONS
//
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
// DoMessage
///////////////////////////////////////////////////////////////////
void
DoMessage(
          HWND   hDlg,
          LPWSTR pszMessage
         )
{
    MessageBox(
               hDlg,
               pszMessage,
               gszTapi30,
               MB_OK
              );
}




//////////////////////////////////////////////////////////////////
// SetStatusMessage
//////////////////////////////////////////////////////////////////
void
SetStatusMessage(
                 HWND hDlg,
				 int Dialog,
                 LPWSTR pszMessage
                )
{
		if (Dialog == 0) 
		{

			SendDlgItemMessage(
                       ghDlg,
                       IDC_STATUS,
                       WM_CLEAR,
                       0,
                       0
                      );
			SetFocus( 
				GetDlgItem( 
				  ghDlg, 
				  IDC_STATUS 
				  )
			    );
			SetDlgItemText(
                   ghDlg,
                   IDC_STATUS,
                   pszMessage
                  );
		   
		}
		else
		{
			SendDlgItemMessage(
                       ghDlg1,
                       IDC_STATUS,
                       WM_CLEAR,
                       0,
                       0
                      );
			 SetFocus( 
			   GetDlgItem( 
					ghDlg1, 
					IDC_STATUS 
				)
			 );
			SetDlgItemText(
                   ghDlg1,
                   IDC_STATUS,
                   pszMessage
                  );
		  
		}


		

}

//////////////////////////////////////////////////////////////////
// ShowAgentStatus
//////////////////////////////////////////////////////////////////
void
ShowAgentStatus( HWND hDlg, LPWSTR pszMessage )
{
    SendDlgItemMessage(
                       hDlg,
                       IDC_AGENTSTATUS,
                       WM_CLEAR,
                       0,
                       0
                      );
	SetFocus(
                 GetDlgItem( hDlg, IDC_AGENTSTATUS )
                );
    SetDlgItemText(
                   hDlg,
                   IDC_AGENTSTATUS,
                   pszMessage
                  );
}

//////////////////////////////////////////////////////////////////
// ShowSessionStatus
//////////////////////////////////////////////////////////////////
void
ShowSessionStatus( HWND hDlg, LPWSTR pszMessage )
{
    SendDlgItemMessage(
                       hDlg,
                       IDC_SESSIONSTATUS,
                       WM_CLEAR,
                       0,
                       0
                      );
    SetDlgItemText(
                   hDlg,
                   IDC_SESSIONSTATUS,
                   pszMessage
                  );
}

//////////////////////////////////////////////////////////////////
// ShowQueueStatus
//////////////////////////////////////////////////////////////////
void
ShowQueueStatus( HWND hDlg, LPWSTR pszMessage )
{
    SendDlgItemMessage(
                       hDlg,
                       IDC_QUEUESTATUS,
                       WM_CLEAR,
                       0,
                       0
                      );
    SetDlgItemText(
                   hDlg,
                   IDC_QUEUESTATUS,
                   pszMessage
                  );
}

//////////////////////////////////////////////////////////////////
// GetAgentStats
//
// Get various information related to the agent and display it
//////////////////////////////////////////////////////////////////
void
GetAgentStats(HWND hDlg)
{
    HRESULT hr;
    BSTR bstrUser;
    AGENT_STATE state;
    WCHAR buf[1000];
    
    hr = gpAgent->get_User(&bstrUser);
    if( hr == S_OK )
    {
        wsprintf(buf,L"User\t%ls\r\n", bstrUser);
        SysFreeString(bstrUser);
    }
    else
        wsprintf(buf,L"User\tNot available\r\n");
    //agent state
    hr = gpAgent->get_State(&state);
    if( hr == S_OK )
    {
        wsprintf(&(buf[lstrlenW(buf)]),L"State\t");
        switch(state)
        {
            case AS_READY:
                wsprintf(&(buf[lstrlenW(buf)]),L"Agent ready\r\n");
                break;
            case AS_NOT_READY:
                wsprintf(&(buf[lstrlenW(buf)]),L"Agent not ready\r\n");
                break;
            case AS_BUSY_ACD:
                wsprintf(&(buf[lstrlenW(buf)]),L"Agent busy with ACD call\r\n");
                break;
            case AS_BUSY_INCOMING:
                wsprintf(&(buf[lstrlenW(buf)]),L"Agent has call incoming\r\n");
                break;
            case AS_BUSY_OUTGOING:
                wsprintf(&(buf[lstrlenW(buf)]),L"Agent has call outgoing\r\n");
                break;
            case AS_UNKNOWN:
                wsprintf(&(buf[lstrlenW(buf)]),L"Agent state unknown\r\n");
                break;
        }
    }
    else
        wsprintf(&(buf[lstrlenW(buf)]),L"State\tNot available");
    

    ShowAgentStatus(hDlg, buf);
}

//////////////////////////////////////////////////////////////////
// GetSessionStats
//
// Get various information related to the agent session and display it
//////////////////////////////////////////////////////////////////
void
GetSessionStats(HWND hDlg)
{
    
    BSTR bstrACDGroup, bstrAddress;
    ITACDGroup * pACDGroup;
    HRESULT hr;
    WCHAR buf[1000];


    AGENT_SESSION_STATE state;

    //group
    hr = gpAgentSession->get_ACDGroup( &pACDGroup );
    if( hr == S_OK)
    {
        hr = pACDGroup->get_Name(&bstrACDGroup);
        if( hr == S_OK )
        {
            wsprintf(buf,L"ACDGroup\t%ls\r\n", bstrACDGroup);
            SysFreeString(bstrACDGroup);
        }
    }
    else
        wsprintf(buf,L"ACDGroup\tNot available\r\n");

    //address                        
    ITAddress * pAddress;
    hr = gpAgentSession->get_Address( &pAddress );
    if( hr == S_OK )
    {
        hr = pAddress->get_AddressName(&bstrAddress);
        if( hr == S_OK )
        {
            wsprintf(&(buf[lstrlenW(buf)]),L"Address\t%ls\r\n", bstrAddress);
            SysFreeString(bstrACDGroup);
        }
    }
    else
        wsprintf(&(buf[lstrlenW(buf)]),L"Address\tNot availalbe\r\n");

    //state
    hr = gpAgentSession->get_State(&state);
    if( hr == S_OK )
    {
        wsprintf(&(buf[lstrlenW(buf)]),L"State\t");
        switch(state)
        {
            case ASST_NOT_READY:
                wsprintf(&(buf[lstrlenW(buf)]),L"Session not ready\r\n");
                break;
            case ASST_READY:
                wsprintf(&(buf[lstrlenW(buf)]),L"Session ready\r\n");
                break;
            case ASST_BUSY_ON_CALL:
                wsprintf(&(buf[lstrlenW(buf)]),L"Session handling ACD call\r\n");
                break;
            case ASST_BUSY_WRAPUP:
                wsprintf(
                        &(buf[lstrlenW(buf)]),
                        L"Session handling wrap up of ACD call\r\n"
                        );
                break;
            case ASST_SESSION_ENDED:
                wsprintf(&(buf[lstrlenW(buf)]),L"Session has completed\r\n");
                break;
        }
    }
    else
        wsprintf(&(buf[lstrlenW(buf)]),L"State\tNot available");

    
    ShowSessionStatus(hDlg, buf);
}

//////////////////////////////////////////////////////////////////
// GetQueueStats
//
// Get various information related to the selected queue and display it
//////////////////////////////////////////////////////////////////
void
GetQueueStats(HWND hDlg)
{
    long lMeasurementPeriod, lTotalCallsQueued, lCurrentCallsQueued;
    
    
    HRESULT hr;
    WCHAR buf[1000];

    //measurement period
    hr = gpQueue->get_MeasurementPeriod(&lMeasurementPeriod);
    if( hr == S_OK )
        wsprintf(buf,L"Measurement Period\t%d\r\n", lMeasurementPeriod);
    else
        wsprintf(buf,L"Measurement Period\tNot available\r\n");
    //total calls
    hr = gpQueue->get_TotalCallsQueued(&lTotalCallsQueued);
    if( hr == S_OK )
        wsprintf(
                &(buf[lstrlenW(buf)]),
                L"Total Queued Calls\t%d\r\n", 
                lTotalCallsQueued
                );
    else
        wsprintf(
                &(buf[lstrlenW(buf)]),
                L"Total Queued Calls\tNot available\r\n"
                );
    //current calls
    hr = gpQueue->get_CurrentCallsQueued(&lCurrentCallsQueued);
    if( hr == S_OK )
        wsprintf(
                &(buf[lstrlenW(buf)]),
                L"Current Queued Calls\t%d\r\n", 
                lCurrentCallsQueued
                );
    else
        wsprintf(
                &(buf[lstrlenW(buf)]),
                L"Current Queued Calls\tNot available\r\n"
                );
    
    ShowQueueStatus(hDlg, buf);
}


///////////////////////////////////////////////////////////////
// EnableButton
//
// Enable, make default, and setfocus to a button
///////////////////////////////////////////////////////////////
void
EnableButton(
             int Dialog,
             int ID
            )
{
    if( Dialog == 0 )
    {
        SendDlgItemMessage(
                           ghDlg,
                           ID,
                           BM_SETSTYLE,
                           BS_DEFPUSHBUTTON,
                           0
                          );
        EnableWindow(
                     GetDlgItem( ghDlg, ID ),
                     TRUE
                    );
        SetFocus(
                 GetDlgItem( ghDlg, ID )
                );
    }
    else
    {
        SendDlgItemMessage(
                           ghDlg1,
                           ID,
                           BM_SETSTYLE,
                           BS_DEFPUSHBUTTON,
                           0
                          );
        EnableWindow(
                     GetDlgItem( ghDlg1, ID ),
                     TRUE
                    );
        SetFocus(
                 GetDlgItem( ghDlg1, ID )
                );
    }
}

//////////////////////////////////////////////////////////////
// DisableButton
//
// Disable a button
//////////////////////////////////////////////////////////////
void
DisableButton(
              int Dialog,
              int ID
             )
{
    if( Dialog == 0 )
    {
        SendDlgItemMessage(
                           ghDlg,
                           ID,
                           BM_SETSTYLE,
                           BS_PUSHBUTTON,
                           0
                          );
        EnableWindow(
                     GetDlgItem( ghDlg, ID ),
                     FALSE
                    );
    }
    else
    {
        SendDlgItemMessage(
                           ghDlg1,
                           ID,
                           BM_SETSTYLE,
                           BS_PUSHBUTTON,
                           0
                          );
        EnableWindow(
                     GetDlgItem( ghDlg1, ID ),
                     FALSE
                    );
    }
}

//////////////////////////////////////////////////////////////////
// InitAgentHandlerListBox
//
// Get the agent handlers available and display their names in
// the agent handler list box. If none available, quit
//////////////////////////////////////////////////////////////////
BOOL
InitAgentHandlerListBox( void )
{
    BOOL bHandlers;
    HRESULT hr, hr1;
    IEnumAgentHandler * pEnumAgentHandler;

    hr = gpCallCentre->EnumerateAgentHandlers(&pEnumAgentHandler);

    if( hr != S_OK )
    {
        DoMessage(ghDlg, L"Could not get Agent Handlers");
        PostMessage(ghDlg, WM_COMMAND, IDC_CANCEL, 0);
        return false;
    }

    hr = S_OK;
    LONG lTemp;
    BSTR pName;
    ITAgentHandler * pTempAgentHandler;

    SendMessage(ghAgentHandlerComboBox, CB_RESETCONTENT, 0, 0);
    for (bHandlers = false; (hr == S_OK);)
    {
        hr = pEnumAgentHandler->Next(1, &pTempAgentHandler, NULL);
        if( hr == S_OK )
        {
            hr1 = pTempAgentHandler->get_Name(&pName);
            if( hr1 == S_OK )
            {
                lTemp = SendMessage(
                            ghAgentHandlerComboBox,
                            CB_ADDSTRING,
                            0, 
                            (LPARAM)(pName)
                            );
                SendMessage(
                            ghAgentHandlerComboBox,
                            CB_SETITEMDATA, 
                            (WPARAM)(lTemp),
                            (LPARAM)(pTempAgentHandler)
                            );
                bHandlers = true;
                SysFreeString( pName );
            }
        }
    }

    if( bHandlers )
    {
        EnableButton( 0, IDC_CREATEAGENT );
        SendMessage(ghAgentHandlerComboBox, CB_SETCURSEL, 0, 0);
    }
    return bHandlers;
}

//////////////////////////////////////////////////////////////////
// InitHandlerDetailsListBox
//
// Get the acd groups and addresses available with selected agent
// handler and display them in respective list boxes.
//////////////////////////////////////////////////////////////////
BOOL InitHandlerDetailsListBoxes(void)
{

    BOOL bResult;
    HRESULT hr, hr1;
    LONG lTemp;
    BSTR pName;

    IEnumACDGroup * pEnumACDGroups;
    ITACDGroup  * pTempACDGroup;

    gpAgentHandler->EnumerateACDGroups(&pEnumACDGroups);

    SendMessage(ghACDGroupComboBox, CB_RESETCONTENT, 0, 0);
    hr = S_OK;
    for (bResult = false; (hr == S_OK);)
    {
        hr = pEnumACDGroups->Next(1, &pTempACDGroup, NULL);
        if( hr == S_OK )
        {
            hr1 = pTempACDGroup->get_Name(&pName);
            if( hr1 == S_OK )
            {
                lTemp = SendMessage(
                                ghACDGroupComboBox,
                                CB_ADDSTRING, 
                                0, 
                                (LPARAM)(pName)
                                );
                SendMessage(
                            ghACDGroupComboBox,
                            CB_SETITEMDATA,
                            (WPARAM)(lTemp), 
                            (LPARAM)(pTempACDGroup)
                            );
                bResult = true;
                SysFreeString( pName );
            }
        }
    }

    if( bResult )
    {
        SendMessage(ghACDGroupComboBox, CB_SETCURSEL, 0, 0);
        EnableWindow(ghACDGroupComboBox, true);
    }
    else
    {
        DoMessage(ghDlg, L"No ACD Groups Found");
        DisableButton( 0, IDC_CREATESESSION );
        return bResult;
    }

    IEnumAddress * pEnumAddress;
    gpAgentHandler->EnumerateUsableAddresses(&pEnumAddress);
    hr = S_OK;
    ITAddress * pTempAddress;
	//DWORD count;

    SendMessage(ghAddressComboBox, CB_RESETCONTENT, 0, 0);
    for (bResult = false; (hr == S_OK);)
    {
        hr = pEnumAddress->Next(1, &pTempAddress, NULL);
        if( hr == S_OK )
        {
            pTempAddress->get_AddressName(&pName);
            lTemp = SendMessage(
                            ghAddressComboBox, 
                            CB_ADDSTRING, 
                            0, 
                            (LPARAM)(pName)
                            );
            SendMessage(
                        ghAddressComboBox, 
                        CB_SETITEMDATA, 
                        (WPARAM)(lTemp), 
                        (LPARAM)(pTempAddress)
                        );
            SysFreeString( pName );
            bResult = true;
        }
    }

    if( bResult )
    {
        SendMessage(ghAddressComboBox, CB_SETCURSEL, 0, 0);
        EnableWindow(ghAddressComboBox, true);
    }
    else
    {
        DoMessage(ghDlg, L"No addresses found");
        DisableButton( 0, IDC_CREATESESSION );
    }
    return bResult;
}

//////////////////////////////////////////////////////////////////
// InitQueueListBox
//
// Get the queues available with the acd group selected and display 
// them in the queue list box.
//////////////////////////////////////////////////////////////////
BOOL InitQueueListBox( void )
{
    BOOL bQueues;
    HRESULT hr, hr1;
    LONG lTemp;
    BSTR pName;

    ITQueue * pQueue;
    IEnumQueue * pEnumQueues;

    gpACDGroup->EnumerateQueues(&pEnumQueues);

    hr = S_OK;

    SendMessage(ghQueueComboBox, CB_RESETCONTENT, 0, 0);

     for( bQueues = false; (hr == S_OK);)
    {
        hr = pEnumQueues->Next(1, &pQueue, NULL);
        if( hr == S_OK )
        {
            hr1 = gpACDGroup->get_Name(&pName);
            if( hr1 == S_OK )
            {
                lTemp = SendMessage(
                                ghQueueComboBox, 
                                CB_ADDSTRING, 
                                0, 
                                (LPARAM)(pName)
                                );

                SendMessage(
                            ghQueueComboBox, 
                            CB_SETITEMDATA, 
                            (WPARAM)(lTemp), 
                            (LPARAM)(pQueue)
                            );
                SysFreeString( pName );
                bQueues = true;;
            }
        }
    }

    if( bQueues )
        EnableWindow(ghQueueComboBox, true);
    else
        DoMessage(ghDlg1, L"No queues found");
    return bQueues;
}