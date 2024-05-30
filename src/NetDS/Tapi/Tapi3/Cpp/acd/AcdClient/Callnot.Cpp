//////////////////////////////////////////////////////////////////////
// callnot.cpp
//
// Implementation of the ITTAPIEventNotification interface.
//
// This is an outgoing interface that is defined by TAPI 3.0.  This
// is basically a callback function that TAPI 3.0 calls to inform
// the application of events related to calls (on a specific address)
//
// Please refer to COM documentation for information on outgoing
// interfaces.
// 
// An application must implement and register this interface in order
// to receive calls and events related to calls
//
//////////////////////////////////////////////////////////////////////


#include "windows.h"
#include "tapi3.h"
#include "callnot.h"
#include "resource.h"
#include "control.h"
#include "strmif.h"

extern ITBasicCallControl * gpCall;
extern HWND ghDlg1;
extern BSTR gbstrVideo;
extern ITAgent * gpAgent;
extern ITAgentSession * gpAgentSession;
extern ITQueue * gpQueue;

void
DoMessage(
          HWND hDlg,
          LPWSTR pszMessage
         );

void
SetStatusMessage(
                 HWND hDlg,
				 int Dialog,
                 LPWSTR pszMessage
                );

void
EnableButton(
             int Dialog,
             int ID
            );
void
DisableButton(
              int Dialog,
              int ID
             );

enum {
    VWP_LEFT = 20,
    VWP_TOP = 100
};

///////////////////////////////////////////////////////////////////
// HostWindow
//
// This method takes a pVideoWindow interface pointer and puts
//  the window in our dialog.
//
// The location depends on the iWhere parameter.
//
///////////////////////////////////////////////////////////////////

void
HostWindow(
           IVideoWindow *pVideoWindow,
           int iWhere
          )
{
    
    pVideoWindow->put_Owner( (long)ghDlg1 );
    pVideoWindow->put_WindowStyle( WS_CHILDWINDOW | WS_BORDER );

    long lWidth, lHeight;
    pVideoWindow->get_Width( &lWidth );
    pVideoWindow->get_Height( &lHeight );

    pVideoWindow->SetWindowPosition( VWP_LEFT + (iWhere * (VWP_LEFT + lWidth)),
                                     VWP_TOP,
                                     lWidth,
                                     lHeight );

    pVideoWindow->put_Visible(-1L);
}

///////////////////////////////////////////////////////////////////
// CallEventNotification
//
// The only method in the ITCallEventNotification interface.  This gets
// called by TAPI 3.0 when there is a call event to report
//
///////////////////////////////////////////////////////////////////
HRESULT
STDMETHODCALLTYPE
CTAPIEventNotification::Event(
                              TAPI_EVENT TapiEvent,
                              IDispatch * pEvent
                             )
{
    HRESULT hr;

    switch ( TapiEvent )
    {
        case TE_CALLNOTIFICATION:
        {
            // CET_CALLNOTIFICATION means that the application is being notified
            // of a new call.
            //
            // Note that we don't answer to call at this point.  The application
            // should wait for a CS_OFFERING CallState message before answering
            // the call.

            ITCallNotificationEvent         * pNotify;
            

            hr = pEvent->QueryInterface( IID_ITCallNotificationEvent, (void **)&pNotify );

            if (S_OK != hr)
            {
                DoMessage(ghDlg1, L"Incoming call, but failed to get the interface");
            }
            else
            {
                CALL_PRIVILEGE          cp;
                ITCallInfo *            pCall;

                // get the call
                //
                pNotify->get_Call( &pCall );

                // check to see if we own the call
                pCall->get_Privilege( &cp );

                if (cp != CP_OWNER)
                {
                    // just ignore it if we have not registered for it
                    pCall->Release();
                    return S_OK;
                }
				
                pCall->QueryInterface( IID_ITBasicCallControl, (void**)&gpCall );

                pCall->Release();
                
                //
                // release the event object
                //
                pNotify->Release();

                //
                // update UI
                //
                EnableButton( 1, IDC_ANSWER );
                DisableButton( 1, IDC_DISCONNECT );
				
                SetStatusMessage( ghDlg1, 1, L"Incoming Owner Call");
            }
            
            break;
        }
        
        case TE_CALLSTATE:
        {
            // TE_CALLSTATE is a call state event.  pEvent is
            // an ITCallStateEvent

            CALL_STATE         cs;
            ITCallStateEvent * pCallStateEvent;

            // Get the interface
            pEvent->QueryInterface( IID_ITCallStateEvent, (void **)&pCallStateEvent );

            // get the CallState that we are being notified of.
            pCallStateEvent->get_State( &cs );

            // if it's offering, update our UI
            if (CS_OFFERING == cs)

            {
				EnableButton( 1, IDC_ANSWER );
                SetStatusMessage( ghDlg1,1, L"Click the Answer button");
            }
            else if (CS_DISCONNECTED == cs)
            {
                PostMessage(ghDlg1, WM_COMMAND, IDC_DISCONNECTED, 0);
            }
                
            // Release the interface
            pCallStateEvent->Release();
            break;
        }
        case TE_AGENT:
        {
            ITAgentEvent * pAgentEvent;

            pEvent->QueryInterface( IID_ITAgentEvent, (void **)&pAgentEvent );

            ITAgent * pAgent;

            HRESULT hr = pAgentEvent->get_Agent(&pAgent);

            if( hr != S_OK )
                break;

            if( pAgent == gpAgent )
                PostMessage(ghDlg1, WM_COMMAND, IDC_UPDATEAGENTSTATS, 0);

            break;
        }
        case TE_AGENTSESSION:
        {
            ITAgentSessionEvent * pSessionEvent;

            pEvent->QueryInterface( IID_ITAgentSessionEvent, (void **)&pSessionEvent );

            ITAgentSession * pSession;

            HRESULT hr = pSessionEvent->get_Session(&pSession);

            if( hr != S_OK )
                break;

            if( pSession == gpAgentSession )
                PostMessage(ghDlg1, WM_COMMAND, IDC_UPDATESESSIONSTATS, 0);

            break;
        }
        case TE_QUEUE:
        {
            ITQueueEvent * pQueueEvent;

            pEvent->QueryInterface( IID_ITQueueEvent, (void **)&pQueueEvent );

            ITQueue * pQueue;

            HRESULT hr = pQueueEvent->get_Queue(&pQueue);

            if( hr != S_OK )
                break;

            if( pQueue == gpQueue )
                PostMessage(ghDlg1, WM_COMMAND, IDC_UPDATEQUEUESTATS, 0);

            break;
        }

    }

    
    return S_OK;
}

