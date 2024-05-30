/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
       jt3rec.java
Abstract:

Author:

Notes:
Revision History:
--*/
import java.awt.*;
import java.applet.*;
import java.util.*;
import com.ms.com.*;
import com.ms.com.Variant;
import com.ms.com.Dispatch;
import com.ms.ui.*;
import tapi3.*;
import quartz.*;
//import confmsp.*;
import h323msp.*;
import appctrls2;


/////////////////////////////////////////////////////////////////////////
//  CLASS: JT3Rec
//
//  PURPOSE: TAPI 3.0 test program
//  DATE:    July 17, 1997
//
//  DESCRIPTION:
//      Applet/application that allow the user to answer incoming calls
//      using TAPI 3.0.
//
/////////////////////////////////////////////////////////////////////////
class EventType
{
	public Object m_Event;
	public int m_EventType;

	public EventType()
	{
	}
	
}
class EventPoll extends Thread implements
                 TAPI_EVENT,				// CET_xxx constants
                 CALL_STATE,				// CS_xxx constants
				 CALL_PRIVILEGE,			// CP_xxx constants
				 DISCONNECT_CODE
{

    // Reference to main program object.
    private jt3rec m_App = null;
	private boolean bFlag;
    
    /////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////
    public EventPoll(jt3rec app)
    {
        m_App = app;
    }

	public void interrupt()
	{
		System.out.println("Interrupt");
		bFlag=false;
		while(!m_App.m_Events.isEmpty())
		{
			EventType event;
			// get the last event fired
			event= (EventType)(m_App.m_Events.firstElement());
			m_App.m_Events.removeElementAt(0);
			HandleEvents(event.m_EventType,event.m_Event);							
	
		};
	}
	
	public void run()
	{
	try
	{
		System.out.println("Entering run");
		bFlag=true;
		while(bFlag)
		{
			sleep(1000);
			if(!m_App.m_Events.isEmpty())
			{
			// events have been fired;
				EventType event;
				// get the last event fired
				event= (EventType)(m_App.m_Events.firstElement());
				m_App.m_Events.removeElementAt(0);
				HandleEvents(event.m_EventType,event.m_Event);
				
			}
		
		}
	}
	catch(InterruptedException e)
	{
			e.printStackTrace();
	}
		
	}


	public void HandleEvents(int eventType,Object event)
	{
		ITCallNotificationEvent pCallNotificationEvent;
		int					CallEventType;
        Variant				avar;
        ITCollection		itc;
		ITCallInfo			pCallInfo;
		IVideoWindow		VideoWindow;
        ITTerminal			aterm;
        ITTerminal			pITTerminal;
		int					astr;
		int					vis;
		confmsp.ITSubStream 		pSubStream;

		try
		{
		switch(eventType)
		{
		case TE_CALLNOTIFICATION:
				System.out.println("EVENT1 call notification");
                pCallNotificationEvent = (ITCallNotificationEvent) event; 
				int cp;
				ITCallInfo		pCall;
				pCall=pCallNotificationEvent.getCall();
				cp=pCall.getPrivilege();
                if (cp==CP_MONITOR)
				{
					System.out.println("EVENT2 call notification monitor");
                    // CP_MONITOR means that the application is being
                    // notified of a new call, and the application has monitor
                    // priveleges on that call.  event is the Call object.
                    // We should not get any CET_CALLMONITOR notifications in
                    // this application, since we only registered for owner in
                    // RegisterCallTypes.
				}
				else
				if (cp==CP_OWNER)
				{
					System.out.println("EVENT3 call notification owner");
                    // CP_OWNER means that the application is being notified
                    // of a call, and the application has owner privileges on
                    // that call.  event is the Call object.
                    // Note that we don't answer the call at this point.  The
                    // application should wait for a CS_OFFERING CallState
                    // message before answering the call.
					m_App.m_Call = (ITBasicCallControl) pCall;
                    System.out.println("Incoming owner call");
                    m_App.SetStatusMessage("Incoming owner call");
				}
			break;
		case TE_CALLSTATE:
				// CET_CALLSTATEEVENT is a call state event.  
				// event is an ITCallStateEvent object.
				System.out.println("EVENT4 call state");
				int cs;
	            ITCallStateEvent callStateEvent = (ITCallStateEvent) event;
				cs = callStateEvent.getState();
		        switch (cs)
			    {
					case CS_DISCONNECTED:
						System.out.println("EVENT5 call state disconnect");
						if (m_App.m_Call != null) 
						{
						/*	Event evt = new Event(
                                         m_App.ctrls.btnHangup,
                                         Event.ACTION_EVENT,
                                         "Hangup"
                                         );
							m_App.action(evt, "Hangup");*/
				            // hangup button pressed
				            if (m_App.DisconnectTheCall(DC_NORMAL)) 
							{
				                m_App.DoMessage("The call has been disconnected");
				            }
				            else 
							{
				                m_App.DoMessage("An error occurred while disconnecting, " +
				                          "but it will be ignored");
				            }							
							System.out.println("Calling Stop");
							m_App.stop();
							m_App.destroy();							
							m_App.ctrls.btnHangup.disable();
							m_App.init();
							m_App.ctrls.btnListen.enable();

						}
                    break;

					case CS_OFFERING: // this tells us it's okay to answer
						System.out.println("EVENT6 call state offering");            
						if (m_App.AnswerTheCall()) 
						{
							m_App.ctrls.btnHangup.enable();
							m_App.SetStatusMessage("Connected");
						}
						else 
						{
							m_App.ctrls.btnHangup.disable();
							m_App.DoMessage("The call could not be answered");
							m_App.SetStatusMessage("Listening for incoming calls");
						}
                    break;


					case CS_CONNECTED:
						System.out.println("EVENT7 call state connect");
						pCallInfo=callStateEvent.getCall();
						// make the in dynamic videos visible
                   break;   
				}			// of cs    
					break;
					
			case TE_CALLMEDIA:
				System.out.println("EVENT call media");
				int evt;
	            ITCallMediaEvent callMediaEvent = (ITCallMediaEvent) event;
				evt = callMediaEvent.getEvent();
		        switch (evt)
		        {
		        	case CALL_MEDIA_EVENT.CME_STREAM_ACTIVE:
		        		System.out.println("Stream active");
		        		break;
		        }
				break;

			case TE_PRIVATE:
				break;
			} //main switch
		}
		catch(Exception e)
		{
			e.printStackTrace();
			System.out.println("keep going");
		}
	}
}

		


public class jt3rec extends Applet
    implements TapiConstants,    // misc. constants
    	tapi3.TAPI_EVENT,
              TERMINAL_DIRECTION,
               DISCONNECT_CODE
{
    // Application name.
    public static final String s_strAppName = "Java TAPI 3.0 Receiver";

    // True if running as stand alone app.
    public boolean m_fStandAlone = false;

    public boolean m_Disconnect=true;

    // Parent frame of the app.
    private Frame m_ParentFrame = null;

    // Resource Wizard generated UI.
    public final appctrls2 ctrls = new appctrls2(this);

    // Main interface to the TAPI component.
    private ITTAPI m_Tapi = null;

    // The currently connected call or null if there isn't one.
    public ITBasicCallControl m_Call = null;

	// Stores ITTerminal interfaces for all the terminals
	private tapi3.ITTerminal m_mediaTerms[];

	// the call notification class, which is used
	// to receive tapi events
    CallNot callnot;

	// the ConnectionPointCookie is Java mechanism used 
	// to implement COM callback 
	// since IConnectionPointContainer and IConnectionPoint
	// are not available from Java (SDK ver. 2.01)
	ConnectionPointCookie cookie;

	// Stores ITStream interfaces for the current call
	private tapi3.ITStream m_Streams[];

	public Vector m_Events= new Vector();

	private EventPoll m_EventPoll;
    /////////////////////////////////////////////////////////////////////
    // init
    //
    // Performs applet initialization.
    /////////////////////////////////////////////////////////////////////
    public void init()
    {
        // select a font to use (ctrls needs this)
        Font font = new Font("Dialog", Font.PLAIN, 8);
        this.setFont(font);

        // setup the UI generated by the Resource Wizard
        ctrls.CreateControls();
        ctrls.tfStatusBox.setEditable(false);
        DisableControls();
        if (m_fStandAlone) 
		{
            ctrls.btnClose.enable();
        }

        // get parent frame to use for message boxes
        Container parent = getParent();
        while ((parent != null) && (!(parent instanceof Frame))) 
		{
            parent = parent.getParent();
        }
        m_ParentFrame = (Frame) parent;

        // resize the frame if running as standalone app
        if (m_fStandAlone) 
		{
            m_ParentFrame.pack();
            m_ParentFrame.setResizable(false);
        }

        // initialize TAPI component
        SetStatusMessage("Initializing TAPI 3.0...");
        try 
		{
            m_Tapi = new TAPI();
            m_Tapi.Initialize();
			m_Tapi.putEventFilter(
			 TE_TAPIOBJECT |
			 TE_ADDRESS |
			 TE_CALLNOTIFICATION |
			 TE_CALLSTATE |
			 TE_CALLMEDIA |
			 TE_CALLHUB |
			 TE_CALLINFOCHANGE |
			 TE_PRIVATE |
			 TE_REQUEST |
			 TE_AGENT |
			 TE_AGENTSESSION |
			 TE_QOSEVENT |
			 TE_AGENTHANDLER |
			 TE_ACDGROUP |
			 TE_QUEUE |
			 TE_DIGITEVENT |
			 TE_GENERATEEVENT); 
			    
        }
        catch (ComException e) 
		{
            DoMessage("Fatal Error: Could not initialize TAPI 3.0");
            m_Tapi = null;
            if (m_fStandAlone) 
			{
                System.exit(0);
            }
            else 
			{
                SetStatusMessage("Could not initialize TAPI 3.0");
                return;
            }
        }

        SetStatusMessage("Ready");

        // app initialized... enable controls
        ctrls.btnListen.enable();
    }

    /////////////////////////////////////////////////////////////////////
    // stop
    //
    // Called when the user leaves the applet's webpage.
    /////////////////////////////////////////////////////////////////////
    public void stop()
    {
        StopListeningForCalls();

        if (m_Call != null) 
		{
            DisconnectTheCall(DC_NORMAL);
        }

        ctrls.btnHangup.disable();
        ctrls.btnListen.enable();
        SetStatusMessage("Ready");
    }


	
    /////////////////////////////////////////////////////////////////////
    // destroy
    //
    // Called when the applet is destroyed by the browser.
    /////////////////////////////////////////////////////////////////////
    public void destroy()
    {
        try
		{
		SetStatusMessage("Destroy start");

            if (m_Tapi != null) 
			{
				SetStatusMessage("Shutting tapi");
                m_Tapi.Shutdown();
                m_EventPoll.interrupt();
            }
           
			SetStatusMessage("Destroy done");
            
        }
        catch (Exception e) 
		{
            e.printStackTrace();
            DoMessage("An error occurred while trying to shutdown TAPI");
        }
    }

    /////////////////////////////////////////////////////////////////////
    // action
    //
    // Event.ACTION_EVENT event handler.
    /////////////////////////////////////////////////////////////////////
    public boolean action(Event evt, Object arg)
    {
        if (arg.equals("Listen")) 
		{
            // listen button pressed
            if (StartListeningForCalls()) 
			{
                ctrls.btnListen.disable();
                SetStatusMessage("Listening for incoming calls");
                m_EventPoll= new EventPoll(this);
                m_EventPoll.start();
                SetStatusMessage("Listening");
            }
            else 
			{
                DoMessage("Could not start listening");
                SetStatusMessage("Calls are not being monitored");
            }
        }
        else if (arg.equals("Hangup")) 
		{
            // hangup button pressed
            if (DisconnectTheCall(DC_NORMAL)) 
			{
                DoMessage("The call has been disconnected");
            }
            else 
			{
                DoMessage("An error occurred while disconnecting, " +
                          "but it will be ignored");
            }
			stop();
			destroy();							
			ctrls.btnHangup.disable();
			init();
			ctrls.btnListen.enable();            
        }
        else if (arg.equals("Close")) 
		{
            // close button pressed.  This button is enabled only when
            // running as an application.  Since a browser would close
            // the applet by calling stop and destroy, we should also.
			SetStatusMessage("Stop Any Calls...");
            this.stop();
			SetStatusMessage("Shutting Down TAPI...");
            this.destroy();
			SetStatusMessage("Exiting...");
            System.exit(0);
        }
        else
		{
            return super.action(evt, arg);
		}
		
        return true;
    }


	/***
		Associates the terminals with the streams
	****/
	private void SelectTerminals(String strServiceProviderName)
	{
	  int iSelected[];
	  IVideoWindow VideoWindow    	;

	  iSelected = new int[m_mediaTerms.length];
	  for (int i=0;i<m_mediaTerms.length;i++)
	  	iSelected[i]=0;
		 System.out.println("num of streams"+ m_Streams.length);

		System.out.println("get call info");


      for (int iTerm=0; iTerm < m_mediaTerms.length; iTerm++) 
		{
			if(m_mediaTerms[iTerm]!=null)
			{
			int termDirec;
			int lMedia;
			termDirec = m_mediaTerms[iTerm].getDirection();	
			lMedia	  = m_mediaTerms[iTerm].getMediaType();
			if((lMedia==TAPIMEDIATYPE_VIDEO)&&(strServiceProviderName.equals("unimdm.tsp")))
			{
				continue;
			}

			if((lMedia==TAPIMEDIATYPE_VIDEO)&&(termDirec==TERMINAL_DIRECTION.TD_RENDER))
			{
				VideoWindow = (IVideoWindow) m_mediaTerms[iTerm];
				  VideoWindow.putAutoShow(-1);
				System.out.println("Enable");

			}
			for(int iStream=0;iStream<m_Streams.length;iStream++)
			{
				if((m_Streams[iStream].getMediaType()==TAPIMEDIATYPE_VIDEO)&&(strServiceProviderName.equals("unimdm.tsp")))
				{
					continue;
				}
				
				if(iSelected[iStream]==0) //take only streams that dont have terminals
				{
					int  StrmTermDirec;
					int lStreamMedia;
					StrmTermDirec = m_Streams[iStream].getDirection();
					lStreamMedia  = m_Streams[iStream].getMediaType();
				
					if((lMedia==lStreamMedia)&&(termDirec==StrmTermDirec))
					{
						System.out.println("Name1 =" + m_mediaTerms[iTerm].getName()+" State = "+m_mediaTerms[iTerm].getState());

						m_Streams[iStream].SelectTerminal(m_mediaTerms[iTerm]);

						if((lStreamMedia==TAPIMEDIATYPE_VIDEO)&&(StrmTermDirec==TERMINAL_DIRECTION.TD_CAPTURE))													
								break;
						//set the selected bit on only for streams w/o video render terminals						
						iSelected[iStream]=1;							
							
						break;
					}
					else
					{
						if((lMedia==TAPIMEDIATYPE_VIDEO)&&
						(lStreamMedia==TAPIMEDIATYPE_VIDEO)&&
						(StrmTermDirec==TERMINAL_DIRECTION.TD_CAPTURE)&&
						(termDirec==TERMINAL_DIRECTION.TD_RENDER)
						) 						
						{
						// for the preview window. You can connect a video window
						// to the video capture stream to show the local preview
						
							m_Streams[iStream].SelectTerminal(m_mediaTerms[iTerm]);
							iSelected[iStream]=1;
							break;
						}
					}						
		


				}//if
				
			}//for


			}//if
			else
				System.out.println ("null media terminal");
		System.out.println("Name =" + m_mediaTerms[iTerm].getName()+" State = "+m_mediaTerms[iTerm].getState());

		}//for
		System.out.println("Finished selecting terminals");
	}

	private boolean EnumerateStreams()
	{

		ITStreamControl pITStreamControl;
		tapi3.ITStream 	pITStream;
		ITCollection 	itcStream;
		Variant var;

		pITStreamControl = (ITStreamControl)m_Call;
		try
		{
			var = pITStreamControl.getStreams();
			itcStream=(ITCollection) var.toDispatch();
			m_Streams= new tapi3.ITStream[itcStream.getCount()];
			for(int n=1;n<=itcStream.getCount();n++)
			{
				var=itcStream.getItem(n);
				pITStream=(tapi3.ITStream)var.toDispatch();
				m_Streams[n-1]=pITStream;	
			}
			return true;
		}
		catch (ComException e) 
		{
            e.printStackTrace();
            return false;
        }
		
	}

    /////////////////////////////////////////////////////////////////////
    // StartListeningForCalls
    //
    // Takes the selected mediatypes and sets all addresses to listen
    // for incoming calls using those mediatypes.  If at least one
    // address succeeds to start listening then true is returned,
    // otherwise, false is returned.
    /////////////////////////////////////////////////////////////////////
    public boolean StartListeningForCalls()
    {
        boolean			isListening = true;
		ITAddress     address;
		ITCollection  itc;
		Variant			var;
		String				addrname;


        try 
		{                       
			// create an instance of the callback class
            callnot = new CallNot(this);

			// hook it to TAPI
			cookie = new ConnectionPointCookie(
						m_Tapi, callnot, 
						ITTAPIEventNotification.class
						);
           
            // get the collection interface for addresses
            var = m_Tapi.getAddresses();
            itc = (ITCollection) var.toDispatch();
            
            for (int i=1; i <= itc.getCount(); i++) 
			{
                // get the next address
                var = itc.getItem(i);
                address = (ITAddress) var.toObject();

				addrname=address.getAddressName();
				if (!addrname.regionMatches(true, 0, "RAS", 0, 3))
				{
						if (!ListenOnThisAddress(address)) 
							isListening = false;
                }
            }
            return isListening;
        }
        catch (ComException e) 
		{
            e.printStackTrace();
            return isListening;
        }
    }


    /////////////////////////////////////////////////////////////////////
    // ListenOnThisAddress
    //
    // Performs the steps involved in setting up an address to listen
    // for calls. Setting up an application to listen for calls is a
    // two step process.
    //
    // First, the app must call RegisterCallNotification on the address that
    // it wants calls on.  This will tell the address which mediatypes
    // it should listen for.
    //
    // Second, it must register it's implementation of the
    // ITCallNotification interface with the address.  This interface
    // specifies only one method, CallEventNotification, which is called
    // by TAPI whenever a call event occurs.
    /////////////////////////////////////////////////////////////////////
    public boolean ListenOnThisAddress(ITAddress address)
    {
		int         ulRegister, ulAdvise;
		String      strServiceProviderName;
		int         dwMediaMode;
    
    
        if (address == null)
			return false;

		ulAdvise = 0;
        
		try 
		{  
			// initialize listening only on ipconference and h323 service providers
			strServiceProviderName = address.getServiceProviderName();
			if ((strServiceProviderName.equals("h323.tsp"))||(strServiceProviderName.equals("unimdm.tsp"))) 
			{
				// dwMediaMode = TAPIMEDIATYPE_AUDIO; 				
				if (strServiceProviderName.equals("unimdm.tsp"))
					dwMediaMode = TAPIMEDIATYPE_AUDIO;					
				else				
					dwMediaMode = TAPIMEDIATYPE_VIDEO | TAPIMEDIATYPE_AUDIO;
				ulRegister = m_Tapi.RegisterCallNotifications(
                                           address,
                                           true,
										   true,
                                           dwMediaMode,
                                           ulAdvise                                           
                                          );
				
			}                				
            return true;
        }
        catch (Exception e) 
		{
            e.printStackTrace();
            return false;
        }
    }



    /////////////////////////////////////////////////////////////////////
    // StopListeningForCalls
    //
    // Sets all addresses to ignore incoming calls.  To ignore incoming
    // calls we release the call notification objects for each address.
    /////////////////////////////////////////////////////////////////////
    public void StopListeningForCalls()
    {
        // force a garbage collect.  This will ensure that the
        // notification objects are released.
    	System.gc();
    }

    /////////////////////////////////////////////////////////////////////
    // AnswerTheCall
    //
    // Answers the incoming call.
    /////////////////////////////////////////////////////////////////////
    public boolean AnswerTheCall()
    {
        ITAddress			address;
        SafeArray			sa;
        Variant				var;
        ITCollection itc;
        Variant avar;
		IVideoWindow VideoWindow;	
		ITCallInfo CallInfo;
		String strServiceProviderName;
		System.out.println("Answering the cal");
        if (m_Call == null)
            return false;

        try 
		{
		
			GetMediaTerminals();
            System.out.println("Got terminals");

			CallInfo = (ITCallInfo) m_Call;
			address = CallInfo.getAddress();
			CallInfo=null;
			strServiceProviderName=address.getServiceProviderName();	
			
			//Enumerate the streams
			if(!EnumerateStreams())
			{
				DoMessage("Failed to get Streams ");
				return false;
			}
            System.out.println("Enumerated the streams");

            //Select the terminals
            // attach the media-terminals to the call
            SelectTerminals(strServiceProviderName);
            System.out.println("Selected the terminals");
			
            m_Call.Answer();
            System.out.println("Answered the call");
      			// start the streams
			for(int i=0;i<m_Streams.length;i++)
			{
				System.out.println("Starting stream "+i);
				if((m_Streams[i].getMediaType()==TAPIMEDIATYPE_VIDEO)&&(strServiceProviderName.equals("unimdm.tsp")))
					continue;
				m_Streams[i].StartStream();


			}
      
            return true;
        }
        catch (Exception e) 
		{
            e.printStackTrace();
            return false;
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DisconnectTheCall
    //
    // Disconnects the call using the given disconnect code.
    /////////////////////////////////////////////////////////////////////
    public boolean DisconnectTheCall(int code)
    {
        ITBasicCallControl call;
        ITCollection itc;
        Variant avar;
        IVideoWindow VideoWindow;

        if (m_Call == null)
            return true;

        call = m_Call;

        try 
		{
            // during the call to Disconnect, the call notifier will
            // receive a CS_DISCONNECTED state.  To indicate that
            // Disconnect has already been called on the local side we
            // set m_Call to null (see CallNot for details).
            m_Call = null;
            
		    System.out.println("Disconnect");
            call.Disconnect(code);
            // release all the terminals;
            for (int iTerm=0; iTerm < m_mediaTerms.length; iTerm++) 
            	m_mediaTerms[iTerm]=null;
 
            return true;
        }
        catch (ComException e) 
		{
            e.printStackTrace();
            return false;
        }
        finally 
		{
            call = null;
            // force a garbage collect.  This will ensure that terminals
            // get released (unless you have references to them!), etc.
            // If you do not do this you may have effects such as video
            // windows lingering after a call has disconnected.
            System.gc();
        }
    }


    /////////////////////////////////////////////////////////////////////
    // GetMediaTerminals
    //
    // Returns a media-terminal for the given mediatype on the specified
    // address.  Media-terminals are the association of a terminal
    // (static or dynamic) and the mediatype that it will use.
    //
    // The only dynamic terminal supported by this method is the video
    // window terminal.
    /////////////////////////////////////////////////////////////////////
    public void  GetMediaTerminals()
    {
        ITAddress		address;
		ITCallInfo 		    CallInfo;
		ITTerminalSupport termSupp;
		ITCollection itc;
		Variant avar;
        int             nVideoWnds;
		int 	nStaticTerms;
   	    int i;

		nVideoWnds = 2;

        try 
		{
		     // get local address participating in the call
			System.out.println("get call info");

			CallInfo = (ITCallInfo) m_Call;
            address = CallInfo.getAddress();
            CallInfo=null;
            System.out.println("Got address and provider name = "+address.getServiceProviderName());

			// create the static terminals
						// get the media support interface on the address
			termSupp = (ITTerminalSupport) address;
			avar = termSupp.getStaticTerminals();
			itc = (ITCollection) avar.toDispatch();                        
			nStaticTerms=itc.getCount();
			
			if(!(address.getServiceProviderName().equals("unimdm.tsp")))
				m_mediaTerms= new ITTerminal[nStaticTerms+nVideoWnds];
			else	
				m_mediaTerms= new ITTerminal[nStaticTerms];

			// add the static terms
			for ( i=1; i <= nStaticTerms; i++) 
				m_mediaTerms[i-1] = (ITTerminal) (itc.getItem(i).toObject());

			avar=null;
			itc=null;
				
			// now the dynamic terminals
			

			// get Video Window Terminals (dynamic terminals)
			if(!(address.getServiceProviderName().equals("unimdm.tsp")))
			{
            // create the video window terminals
		        for ( i=nStaticTerms; i <nStaticTerms+nVideoWnds ; i++) 
				{
		            m_mediaTerms[i] = termSupp.CreateTerminal(CLSID_String_VideoWindowTerm, TAPIMEDIATYPE_VIDEO, TD_RENDER);
		        }
			
        	}
        
		}
        catch (ComException e) 
		{
            e.printStackTrace();
			return ;
        }
    }
			

	
 


	

    /////////////////////////////////////////////////////////////////////
    // DisableControls
    //
    // Disables all of the app's controls.
    /////////////////////////////////////////////////////////////////////
    private void DisableControls()
    {
        ctrls.btnListen.disable();
        ctrls.btnHangup.disable();
        ctrls.btnClose.disable();
    }

    /////////////////////////////////////////////////////////////////////
    // SetStatusMessage
    //
    // Displays messages in the status box.
    /////////////////////////////////////////////////////////////////////
    public synchronized void SetStatusMessage(String msg)
    {
        ctrls.tfStatusBox.setText(msg);
    }

    /////////////////////////////////////////////////////////////////////
    // DoMessage
    //
    // Displays messages in a message box.
    /////////////////////////////////////////////////////////////////////
    public void DoMessage(String msg)
    {
        AwtUIMessageBox msgbox = new AwtUIMessageBox(
                                            m_ParentFrame,
                                            s_strAppName,
                                            msg,
                                            AwtUIMessageBox.EXCLAMATION,
                                            UIButtonBar.OK
                                            );
        msgbox.doModal();
    }

    /////////////////////////////////////////////////////////////////////
    // main
    //
    // Standalone application entry point.  Not called for applets.
    /////////////////////////////////////////////////////////////////////
    public static void main(String[] args)
    {
        AppFrame frame = new AppFrame(s_strAppName);

		// Must show Frame before we size it so insets() will return valid values
		//----------------------------------------------------------------------
		frame.show();
        frame.hide();
		frame.resize(frame.insets().left + frame.insets().right  + 320,
					 frame.insets().top  + frame.insets().bottom + 240);

		// The following code starts the applet running within the frame window.
		// It also calls GetParameters() to retrieve parameter values from the
		// command line, and sets m_fStandAlone to true to prevent init() from
		// trying to get them from the HTML page.
		//----------------------------------------------------------------------

        jt3rec applet = new jt3rec();
		frame.m_App = applet;
		frame.add("Center", applet);
		applet.m_fStandAlone = true;
        frame.show();
		applet.init();
    }
}


////////////////////////////////////////////////////////////////////////////////
//  CLASS: AppFrame
//
//  DESCRIPTION:
//      Frame for standalone application.
//
////////////////////////////////////////////////////////////////////////////////

class AppFrame extends Frame
{
    public Applet m_App = null;

    public AppFrame(String title)
    {
        super(title);
    }

    public boolean handleEvent(Event evt)
    {
        if (evt.id == Event.WINDOW_DESTROY) 
		{
            // since a browser would close the applet by calling stop and
            // destroy, we should also.
            m_App.stop();
            m_App.destroy();
            System.exit(0);
        }

        return super.handleEvent(evt);
    }
}





/////////////////////////////////////////////////////////////////////////
//  CLASS: CallNot
//
//  PURPOSE: Supporting class to JT3Rec
//  DATE:    July 17, 1997 - March 30, 1998
//
//  DESCRIPTION:
//      Implements the ITCallNotification interface which is called
//      by TAPI 3.0 when incoming calls arrive.
//
/////////////////////////////////////////////////////////////////////////

class CallNot extends Object
      implements ITTAPIEventNotification,	// notification interface
				 TapiConstants,				// misc. constants
				 TERMINAL_DIRECTION
{
    // Reference to main program object.
    private jt3rec m_App = null;

    
    /////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////
    public CallNot(jt3rec app)
    {
        m_App = app;
    }

    /////////////////////////////////////////////////////////////////////
    // Event 
    //
    // The only method in the ITCallNotification interface.  This gets
    // called by TAPI 3.0 when there is a call event to report.
    //
    // It is important that you use the /X:m- switch when importing the
    // TAPI 3.0 typelib to Java using JActiveX.  This will turn off
    // auto-marshalling of variables passed from CallNot to JT3Rec.  If
    // you do not, the program will freeze whenever JT3Rec tries to use
    // a variable given to it by CallNot.
    /////////////////////////////////////////////////////////////////////
    public void Event( 
						int eventType,
						Object event
					 )
	{
		EventType evt = new EventType();
		evt.m_Event=event;
		evt.m_EventType=eventType;
		m_App.m_Events.addElement(evt);

	}
}   // of class             


