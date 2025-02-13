/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
        jt3conf.java
Abstract:

Author:

Notes:
Revision History:
--*/

import java.awt.*;
import java.applet.*;
import java.util.*;
import com.ms.com.*;
import com.ms.ui.*;
import quartz.*;
import rend.*;
import appctrls3;
import newdlg;
import infodlg;
import confinfo;
import confmsp.*;
import tapi3.ITTAPI;
import tapi3.TapiConstants;
import tapi3.ITTAPIEventNotification;
import tapi3.TAPI_EVENT;
import tapi3.ITMediaSupport;
import tapi3.ITCollection;
import tapi3.ITStreamControl;
import tapi3.ITAddressCapabilities;
import tapi3.ITTerminalSupport;
import tapi3.ITCallNotificationEvent;
import tapi3.ITCallStateEvent;
import tapi3.ITCallMediaEvent;
import tapi3.CALL_MEDIA_EVENT;

/////////////////////////////////////////////////////////////////////////
//  CLASS: jt3conf
//
//  PURPOSE: TAPI 3.0 test program
//  DATE:    July 22, 1997 - Mrch 30, 1998
//
//  DESCRIPTION:
//      Applet/application that allows the user to join, create, and
//      delete conferences using TAPI 3.0.  Conference listings are
//      retrieved using the Rendezvous Controls.
//
/////////////////////////////////////////////////////////////////////////
public class jt3conf extends Applet
	implements TapiConstants,   // misc. constants
	tapi3.TAPI_EVENT,	
	tapi3.TERMINAL_DIRECTION,
	tapi3.DISCONNECT_CODE,  // DC_xxx constants
	DIRECTORY_TYPE,
	DIRECTORY_OBJECT_TYPE
	//PARTICIPANT_TYPED_INFO waiting for Mu's fix
{
	// Application name.
	public static final String APP_NAME = "Java TAPI 3.0 Conferencer";

	// the frame
	AppFrame3 frame;
	
	// Default number of video window terminals.
	private static final int MIN_VIDEOWNDS = 0;
	private static final int DEF_VIDEOWNDS = 5;
	private static final int MAX_VIDEOWNDS = 10;

	// the maximum number of available conferences
	// a real life situation may exceeds it
	// but here it is helpful to do caching of data for
	// fast retreival of info in order to have responsive UI
	private static final int MAX_CONF = 500;

	// True if running as stand alone app.
	public boolean m_fStandAlone = false;

	// Parent frame of the app.
	private Frame m_ParentFrame = null;
	
	// Resource Wizard generated UI.
	public final appctrls3 ctrls = new appctrls3(this);

	// Main interface to the TAPI component.
	public tapi3.ITTAPI m_Tapi = null;

	// the rendezvous control
	public ITRendezvous m_Rend = null;

	// The directory component.
	public ITDirectory m_Directory = null;

	// an array of ITDirectoryObjects 
	// used to cache the interfaces of an ILS conference
	public ITDirectoryObject[] m_Conferences = new ITDirectoryObject[MAX_CONF];
	// conference blob strings
	public String[] confblobname = new String[MAX_CONF];
	// conference info
	public confinfo[] cinfo = new confinfo[MAX_CONF];

	// media terminals
	private ITTerminal[] m_mediaTerms;							
	
	// The current call or null if there isn't one.
	public tapi3.ITBasicCallControl m_Call = null;

	// scratch
	public ITDirectoryObjectConference  dobjconf;

	// Stores ITStream interfaces for the current call
	private ITStream m_Streams[];
	
	// index of selected conference
	private int m_iSelConf;
	
	// address
	private tapi3.ITAddress m_ITSrcAddress;
	// number of video windows;
	private int m_iNumVideoWnds;
	       // the call notification class, which is used
       // to receive tapi events
   CallNot callnot;

       // the ConnectionPointCookie is Java mechanism used
       // to implement COM callback
       // since IConnectionPointContainer and IConnectionPoint
       // are not available from Java (SDK ver. 2.01)
       ConnectionPointCookie cookie;
	/////////////////////////////////////////////////////////////////////
	// init
	//
	// Performs applet initialization.
	/////////////////////////////////////////////////////////////////////
	public void initmain()
	{
		// select a font to use (ctrls needs this)
		Font font = new Font("Dialog", Font.PLAIN, 8);
		this.setFont(font);

		// setup the UI generated by the Resource Wizard
		ctrls.CreateControls();
		ctrls.tfStatusBox.setEditable(false);
		ctrls.tfVideoWnds.setText(DEF_VIDEOWNDS + "");
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
		InitializeTAPI();
}

private void InitializeTAPI()
{

		// create and initialize TAPI component
		SetStatusMessage("Initializing TAPI 3.0...");
		try 
		{
			m_Tapi =(tapi3.ITTAPI) new tapi3.TAPI();
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

		// initialize the rendezvous control
		SetStatusMessage("Initializing the rendezvous control...");
		try 
		{
			m_Rend = new Rendezvous();
		}
		catch (ComException e) 
		{
			DoMessage("Fatal Error: Could not initialize conference directory");
			m_Tapi.Shutdown();
			m_Tapi = null;
			if (m_fStandAlone) 
			{
				System.exit(0);
			}
			else 
			{
				SetStatusMessage("Could not initialize conference directory");
				return;
			}
		}

		// get initial data and display it
		SetStatusMessage("Enumerating conferences...");
		if (!EnumerateConferences()) 
		{
			DoMessage("Fatal Error: Could not enumerate conferences");
			m_Tapi.Shutdown();
			m_Tapi = null;
			if (m_fStandAlone) 
			{
				System.exit(0);
			}
			else 
			{
				SetStatusMessage("Could not enumerate conferences");
				return;
			}
		}
		SetStatusMessage("Ready");

		// app initialized... enable controls
		ctrls.lstConferences.enable();
		ctrls.btnInfo.enable();
		ctrls.btnRefresh.enable();
		ctrls.btnNew.enable();
		ctrls.btnDelete.enable();
		ctrls.btnJoin.enable();
	}

	/////////////////////////////////////////////////////////////////////
	// CleanUp
	//
	// Release All the interfaces
	/////////////////////////////////////////////////////////////////////
	public void CleanUp()
	{
		int i;




		
		if(m_Rend!=null)
		{
			ComLib.release(m_Rend);
			m_Rend=null;
		}

		if(m_Tapi!=null)
		{
			ComLib.release(m_Tapi);
			m_Tapi=null;
		}

		if(m_Call!=null)
		{
			ComLib.release(m_Call);
			m_Call=null;
		}
		
		if(m_Streams!=null)
		{
			for(i=0;i<m_Streams.length;i++)
			{
				if(m_Streams[i]!=null)
				{
					ComLib.release(m_Streams[i]);
					m_Streams[i]=null;
				}
			}
		}

		if(m_mediaTerms!=null)
			for(i=0;i<m_mediaTerms.length;i++)
				m_mediaTerms[i]=null;
		
	}
	
	public void init()
	{
		frame = new AppFrame3(APP_NAME);
		frame.show();
		frame.hide();
		frame.resize(frame.insets().left + frame.insets().right  + 320,
					 frame.insets().top  + frame.insets().bottom + 240);
		frame.m_App = this;
		frame.add("Center", this);
		m_fStandAlone = true;
		frame.show();
		init();
	}
	/////////////////////////////////////////////////////////////////////
	// stop
	//
	// Called when the user leaves the applet's webpage.
	/////////////////////////////////////////////////////////////////////
	public void stop()
	{
		if (m_Call != null) 
		{
			DisconnectTheCall(DC_NORMAL);
		}

		ctrls.btnJoin.enable();
		ctrls.btnHangup.disable();
		ctrls.btnDelete.enable();
		ctrls.lstConferences.enable();
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
			if (m_Tapi != null) 
			{
				m_Tapi.Shutdown();
			}
		}
		catch (ComException e) 
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
		if (arg.equals("Join")) 
		{
			// join button pressed
			if (JoinTheConference()) 
			{
				ctrls.btnJoin.disable();
				ctrls.btnHangup.enable();
				ctrls.btnDelete.disable();
				ctrls.lstConferences.disable();
				SetStatusMessage("Connected"); // + GetSelectedConfName());
			}
			else 
			{
				DoMessage("You were unable to join the conference");
				SetStatusMessage("Ready");
			}
		}
		else if (arg.equals("New...")) 
		{
			// new button pressed
			newdlg newdlg = new newdlg(m_ParentFrame, m_Rend); //, m_Directory);
			newdlg.show();
			if (newdlg.GetButtonId() == newdlg.CREATE) 
			{
				try
				{
					ITDirectoryObject conf = newdlg.GetConference();
					if (conf != null) 
					{
						Variant var = m_Rend.getDefaultDirectories();
						ITCollection itc = (ITCollection) var.toDispatch();

						// Walk through the collection.  Note that collections start
						// at index 1 and end at index itc.getCount().
						for (int n=1; n <= itc.getCount(); n++) 
						{
							// get the next address
							var = itc.getItem(n);

							// get the conference from the variant
							ITDirectory direc = (ITDirectory) var.toObject();
							int dtype=direc.getDirectoryType();

							
							if (dtype == DT_ILS)
							{
								direc.Connect(false);
								m_Directory = direc;
								m_Directory.AddDirectoryObject(conf);
							}
						}

						// as if refresh button pressed
						EnumerateConferences();
						SetStatusMessage("Ready");


					}
				}
				catch (Exception e)
				{
					e.printStackTrace();
					DoMessage("Exception creating conference");
				}
			}
		}
		else if (arg.equals("Delete")) 
		{
			// delete button pressed
			int index = ctrls.lstConferences.getSelectedIndex();
			if (index == -1) 
			{
				DoMessage("You must select a conference first");
			}
			else 
			{
				String name = GetSelectedConfName();
				try 
				{
					// workaround last interface loss
					EnumerateConferences();
					m_Directory.DeleteDirectoryObject(m_Conferences[index]);
					// as if refresh button pressed
					EnumerateConferences();
					SetStatusMessage("Ready");
					SetStatusMessage("Conference Deleted...");
				}
				catch (ComException e) 
				{
					DoMessage("Could not delete " + name);
				}
			}
		}
		else if (arg.equals("Hangup")) 
		{
			// hangup button pressed
			if (!DisconnectTheCall(DC_NORMAL)) 
			{
				DoMessage("An error occurred while disconnecting, " +
						  "but it will be ignored");
			}
			ctrls.btnJoin.enable();
			ctrls.btnHangup.disable();
			ctrls.btnDelete.enable();
			ctrls.lstConferences.enable();
			CleanUp();
			InitializeTAPI();					
			SetStatusMessage("Disconnected");
		}
		else if (arg.equals("Info...")) 
		{
			// info button pressed
			int index = ctrls.lstConferences.getSelectedIndex();
			if (index == -1) 
			{
				DoMessage("You must select a conference first");
			}
			else 
			{
				try 
				{
					infodlg infoDlg = new infodlg(
												  m_ParentFrame,
												  cinfo[index]										
												  );
					infoDlg.show();
				}
				catch (Exception e)
				{
					e.printStackTrace();
				}
			}
		}
		else if (arg.equals("Refresh")) 
		{
			// refresh button pressed
			EnumerateConferences();
			SetStatusMessage("Ready");
		}
		else if (arg.equals("Close")) 
		{
			// close button pressed.  This button is enabled only when
			// running as an application.  Since a browser would close
			// the applet by calling stop and destroy, we should also.
			this.stop();
			this.destroy();
			System.exit(0);
		}
		else 
		{
			return super.action(evt, arg);
		}
		return true;
	}


	/////////////////////////////////////////////////////////////////////
	// EnumerateConferences
	//
	// Finds all conferences on and adds their names to the conferences
	// listbox.  Returns true on success and false if there was an error.
	/////////////////////////////////////////////////////////////////////
	private boolean EnumerateConferences()
	{
		Variant  var;
		ITCollection itc;
		ITDirectory  direc;
		int dtype;
		Variant  avar;
		ITCollection anitc;
		ITDirectoryObject  direcobj;
		ITDirectoryObjectConference conf;
		String st;
		Variant advar;
		String  daddress;
		ITCollection dadc;

		ctrls.lstConferences.clear();

		try 
		{           
			// get the enumeration interface for conferences
			// as a collection in a variant
			var = m_Rend.getDefaultDirectories();
			itc = (ITCollection) var.toDispatch();

			// global conference count
			int gccount = -1;
			// Walk through the collection.  Note that collections start
			// at index 1 and end at index itc.getCount().
			for (int n=1; n <= itc.getCount(); n++) 
			{
				// get the next address
				var = itc.getItem(n);

				// get the conference from the variant
				direc = (ITDirectory) var.toObject();
				dtype=direc.getDirectoryType();

				// add its name to the listbox
				//ctrls.lstConferences.addItem(direc.getDisplayName());

				if (dtype == DT_ILS)
				{
					direc.Connect(false);
					// direc.Bind("ntdev", null, null, true);
					m_Directory = direc;
					avar = direc.getDirectoryObjects(OT_CONFERENCE,"*");
					anitc = (ITCollection) avar.toDispatch();

					// Walk through the collection.  
					for (int i=1; i <= anitc.getCount(); i++) 
					{
						// get the next address
						avar = anitc.getItem(i);

						// increment the global reference count
						gccount++;

						// initialize conf info array
						cinfo[gccount]=null;
						cinfo[gccount]=new confinfo();
						
						// get the conference from the variant
						m_Conferences[gccount] = (ITDirectoryObject) avar.toObject();
						cinfo[gccount].cnfName=m_Conferences[gccount].getName();
						
						// Find out the dialabe addresses of this object.
						advar = m_Conferences[gccount ].getDialableAddrs(LINEADDRESSTYPE_SDP);
						dadc = (ITCollection) advar.toDispatch();


						// Walk through the collection.  Note that collections start
						// at index 1 and end at index itc.getCount().
						for (int m=1; m <= dadc.getCount(); m++) 
						{
							// get the next address
							advar = dadc.getItem(m);

							// get the address from the variant
							daddress = (String) advar.toString();
							confblobname[gccount]=daddress;
							cinfo[gccount].cnfdaddr=daddress;
						}

						conf = (ITDirectoryObjectConference) m_Conferences[gccount ];
						
						st = conf.getDescription();
						cinfo[gccount ].cnfDesc=conf.getDescription();

						st = conf.getProtocol();
						cinfo[gccount ].cnfProtocol=conf.getProtocol();

						st=conf.getUrl();
						cinfo[gccount ].cnfUrl=conf.getUrl();

						st = conf.getOriginator();
						cinfo[gccount ].cnfOriginator=conf.getOriginator();
						
						double d = conf.getStartTime();
						cinfo[gccount ].cnfStart= conf.getStartTime();
						d= conf.getStopTime();
						cinfo[gccount ].cnfEnd= conf.getStopTime();
						
						// add its name to the listbox
						ctrls.lstConferences.addItem(m_Conferences[gccount ].getName());
					}								
				}
			}
			return true;
		}
		catch (Exception e) 
		{
			e.printStackTrace();
			return false;
		} 
	}

	/***
	 Associates the terminals with the streams
	 ****/
	private void SelectTerminals()
	{

		try 
		{
		int iSelected[];
		int iCaptureStream=-1;
		int  StrmTermDirec;
		int lStreamMedia;
		int iStream=0;

		iSelected = new int[m_mediaTerms.length];
		for (int i=0;i<m_mediaTerms.length;i++)
			iSelected[i]=0;
	
		for (int iTerm=0; iTerm < m_mediaTerms.length-1; iTerm++) 
		{
			if(m_mediaTerms[iTerm]!=null)
			{
				int termDirec;
				int lMedia;
				termDirec = m_mediaTerms[iTerm].getDirection();	
				lMedia	  = m_mediaTerms[iTerm].getMediaType();
				for( iStream=0;iStream<m_Streams.length;iStream++)
				{

					if((iSelected[iStream]==0)&&(m_Streams[iStream]!=null)) //take only streams that dont have terminals
					{
						StrmTermDirec = m_Streams[iStream].getDirection();
						lStreamMedia  = m_Streams[iStream].getMediaType();
					
						
						if((lMedia==lStreamMedia)&&(termDirec==StrmTermDirec))
						{
							m_Streams[iStream].SelectTerminal(m_mediaTerms[iTerm]);
							if(!((lStreamMedia==TAPIMEDIATYPE_VIDEO)&&((StrmTermDirec==TERMINAL_DIRECTION.TD_RENDER)||(StrmTermDirec==TERMINAL_DIRECTION.TD_CAPTURE))))
								//set the selected bit on only for streams w/o video render terminals
								iSelected[iStream]=1;							
							break;
						}
						
					}//if
					
					
				}//for

			}//if
			else
				DoMessage("null media terminal");
		}//for
		//now enable preview by selecting the capture stream 
		// and a video render terminal
		for( iStream=0;iStream<m_Streams.length;iStream++)
		{
			System.out.println(iStream);
			if((m_Streams[iStream].getMediaType()==TAPIMEDIATYPE_VIDEO)&&
			   (m_Streams[iStream].getDirection()==TERMINAL_DIRECTION.TD_CAPTURE)
			   )
			  {
			 		m_Streams[iStream].SelectTerminal(m_mediaTerms[m_mediaTerms.length-1]);
			 		break;
			 }
			 
		}

		
		}
		catch (NullPointerException e) 
		{
			e.printStackTrace();
			return ;
		}
			
	}

	/////////////////////////////////////////////////////////////////////
	// EnumerateStreams
	//
	//  Enumerates all the streams in the call
	/////////////////////////////////////////////////////////////////////

	private boolean EnumerateStreams()
	{

		ITStreamControl pITStreamControl;
		ITStream 	pITStream;
		ITCollection 	itcStream;
		Variant var;

		pITStreamControl = (ITStreamControl)m_Call;
		try
		{
			var = pITStreamControl.getStreams();
			itcStream=(ITCollection) var.toDispatch();
			m_Streams= new ITStream[itcStream.getCount()];
			for(int n=1;n<=itcStream.getCount();n++)
			{
				var=itcStream.getItem(n);
				pITStream=(ITStream)var.toDispatch();
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
	// JoinTheConference
	//
	// Joins the selected conference.  The steps required to join a
	// conference are the same as those for making a one-to-one call.
	/////////////////////////////////////////////////////////////////////
	private boolean JoinTheConference()
	{
		tapi3.ITAddress        srcAddr;
		String					destAddr;
		ITTerminal[]     staticTerms, dynamicTerms, temp;
		int							nVideoWnds;
		ITTerminal[]	 mediaTerms;
		SafeArray         sa;
		Variant				  var;

		Variant						  avar;
		ITCollection			  itc;
		tapi3.ITCallInfo					 pCallInfo;
		IVideoWindow		VideoWindow;		
		ITTerminal				  aterm;
		int 								astr;

		Variant					pvar;
		ITCollection	   pitc;
		ITParticipant      part;
		String					  pname;
		int         ulRegister, ulAdvise;
		
         // create an instance of the callback class        
         callnot = new CallNot(this);

                      // hook it to TAPI
                      cookie = new ConnectionPointCookie(
                                              m_Tapi, callnot,
                                              ITTAPIEventNotification.class
                                              );

		// get the destination address
		destAddr = GetSelectedConfName();
		if (destAddr == null) 
		{
			DoMessage("You must select a conference first");
			return false;
		}
		
		// get the source address (an interface)
		
		if (GetAddress(LINEADDRESSTYPE_SDP)== 0) 
		{
			DoMessage("No local address supports conferencing");
			return false;
		}
		// get the number of video windows
		m_iNumVideoWnds = GetNumVideoWnds()+1; //including the preview window
		if (m_iNumVideoWnds < MIN_VIDEOWNDS || m_iNumVideoWnds > MAX_VIDEOWNDS) 
		{
			DoMessage("Please enter a number from " + MIN_VIDEOWNDS +
					  " to " + MAX_VIDEOWNDS +
					  " for the number of video windows");
			return false;
		}
		
		// get static terminals
		GetDefaultTerminals();
		

		// get Video Window Terminals (dynamic terminals)
		if (GetVideoWndTerms()==0) 
		{
			DoMessage("No video window terminals could be created");
			nVideoWnds = 0;
			//return false;
		}
		

		if (m_mediaTerms.length==0) 
		{
			DoMessage("Can not create terminals at all");
			return false;
		}



		try 
		{

			// create a call between srcAddr and destAddr
			m_Call = m_ITSrcAddress.CreateCall(destAddr, LINEADDRESSTYPE_SDP,TAPIMEDIATYPE_AUDIO|TAPIMEDIATYPE_VIDEO);

			//Enumerate the streams
			if(!EnumerateStreams())
			{
				DoMessage("Failed to get Streams ");
				return false;
			}
			//Select the terminals
			// attach the media-terminals to the call
			SelectTerminals();

			// make the call (true = synchronous)
			m_Call.Connect(true);
			// start the streams
			for(int iCnt=0;iCnt<m_Streams.length;iCnt++)
			{
				if(m_Streams[iCnt]!=null)
				{
				m_Streams[iCnt].StartStream();
				if(m_Streams[iCnt].getMediaType()==TAPIMEDIATYPE_VIDEO)				{   
					var=m_Streams[iCnt].getTerminals();
					pitc=(ITCollection)var.toDispatch();
					for(int tCnt=1;tCnt<=pitc.getCount();tCnt++)
					{
						var=pitc.getItem(tCnt);
						if(((ITTerminal)(var.toObject())).getDirection()==TERMINAL_DIRECTION.TD_RENDER)
						{
						
							VideoWindow=(IVideoWindow)((ITTerminal)(var.toObject()));
							VideoWindow.putAutoShow(-1);
						}
					}				
				}
				}
			}


			return true;
		}
		catch (ComException e) 
		{
			e.printStackTrace();
			m_Call = null;
			return false;
		}
	}

	/////////////////////////////////////////////////////////////////////
	// DisconnectTheCall
	//
	// Disconnects the call using the given disconnect code.  Disconnect
	// codes are defined in the DisconnectCode interface.
	/////////////////////////////////////////////////////////////////////
	public boolean DisconnectTheCall(int code)
	{
		Variant var;
		IVideoWindow         VideoWindow;
		ITCollection pitc;

		if (m_Call == null)
			return true;

		try 
		{
			for(int i=0;i<m_Streams.length;i++)
			{
				m_Streams[i].StopStream();

				// only if it is the video render terminal 	
				if(m_Streams[i].getMediaType()==TAPIMEDIATYPE_VIDEO)
				{					
					
					var=m_Streams[i].getTerminals();
					pitc=(ITCollection)var.toDispatch();
					for(int tCnt=1;tCnt<=pitc.getCount();tCnt++)
					{					
						var=pitc.getItem(tCnt);
						if(((ITTerminal)(var.toObject())).getDirection()==TERMINAL_DIRECTION.TD_RENDER)
						{
							System.out.println("Disabling " +tCnt);

							VideoWindow=(IVideoWindow)((ITTerminal)(var.toObject()));
							VideoWindow.putVisible(0);
						}
					}
					
				}
			
			}
		
			m_Call.Disconnect(code);
			return true;
		}
		catch (ComException e) 
		{
			e.printStackTrace();
			return false;
		}
		finally 
		{
			m_Call = null;

			// force a garbage collect.  This will ensure that terminals
			// get released (unless you have references to them!), etc.
			// If you do not do this you may have effects such as video
			// windows lingering after a call has disconnected.
			System.gc();
		}
	}

	/////////////////////////////////////////////////////////////////////
	// GetDefaultTerminals
	//
	// Returns an array of default terminals for the given address, an
	// array of length 0 is returned if there is an error or if the
	// address does not have any default terminals.  Default terminals
	// are always static terminals.
	/////////////////////////////////////////////////////////////////////
	private int GetDefaultTerminals()
	{
		ITTerminalSupport	   termSupp;
		Variant								var;
		ITCollection					itc;
		ITTerminal						terminal;
		String								  termClass;
		int										  n;
		ITTerminal[]				   terminals;
		ITTerminal[]				   empty = new ITTerminal[0];


		if (m_ITSrcAddress== null)
			return 0;

		try 
		{
			// get the terminal support interface on the address
			termSupp = (ITTerminalSupport) m_ITSrcAddress;

			// get the collection interface for static terminals
			var = termSupp.getStaticTerminals();
			itc = (ITCollection) var.toDispatch();

			m_mediaTerms = new ITTerminal[itc.getCount()+m_iNumVideoWnds];
			for (n=1; n <= itc.getCount(); n++) 
			{
				// get the next static terminal
				var = itc.getItem(n);
				terminal = (ITTerminal) var.toObject();

				// display the terminal name and store its interface
				m_mediaTerms[n-1]= terminal;
			}
			return 1;
		}
		catch (Exception e) 
		{
			e.printStackTrace();
			return 0;
		}
	}

	
	
	/////////////////////////////////////////////////////////////////////
	// GetVideoWndTerms
	//
	// Returns an array of Video Window Terminals on the given address,
	// an array of length 0 is returned if there was an error.  count is
	// the number of Video Window Terminals that should be returned.
	//
	// Video Window Terminals are dynamic terminals.  Dynamic terminals
	// are different from static terminals in that there is no set
	// number that may exist at any particular time.
	//
	// Static terminals are (usually) tied to hardware devices (eg,
	// microphones, speakers, etc) and, therefore, have a specific count.
	// There is no specific maximum to the number of dynamic terminals
	// (eg, video windows, files, etc) that may be created.
	/////////////////////////////////////////////////////////////////////
	private int GetVideoWndTerms()
	{
		ITTerminalSupport termSupp;

		if (m_ITSrcAddress == null)
			return 0;

		
		try 
		{
			// get the terminal support interface on the address
			termSupp = (ITTerminalSupport) m_ITSrcAddress;

			if(m_mediaTerms==null)
				m_mediaTerms=new ITTerminal[m_iNumVideoWnds];
			
			// create the video window terminals
			for (int i=m_mediaTerms.length-m_iNumVideoWnds; i <m_mediaTerms.length; i++) 
				m_mediaTerms[i] =(ITTerminal) termSupp.CreateTerminal(CLSID_String_VideoWindowTerm, TAPIMEDIATYPE_VIDEO, TD_RENDER);
			return 1;
		}
		catch (ComException e) 
		{
			e.printStackTrace();
			return 0;
		}
	}


	/////////////////////////////////////////////////////////////////////
	// CreateMediaTerminals
	//
	// Takes an array of terminals and creates media-terminals from them.
	// Returns an array of media-terminals, an array of length 0 is
	// returned if there was an error.
	//
	// Media-terminals are the association of a terminal object and the
	// mediatype that it will use.  In this case, the first mediatype
	// supported by each terminal is used.
	/////////////////////////////////////////////////////////////////////
	private ITTerminal[] CreateMediaTerminals(ITTerminal[] terminals)
	{
		ITTerminal[] mediaTerms;
		ITMediaSupport    mediaSupp;
		Variant           var;
		ITCollection      itc;
		String            mediaType;
		ITTerminal[] empty = new ITTerminal[0];

		if (terminals == null || terminals.length == 0)
			return empty;

		mediaTerms = new ITTerminal[terminals.length];

		try 
		{
			for (int i=0; i < terminals.length; i++) 
			{
				mediaTerms[i] = terminals[i];
			}
			return mediaTerms;
		}
		catch (Exception e) 
		{
			e.printStackTrace();
			return empty;
		}
	}

	/////////////////////////////////////////////////////////////////////
	// GetAddress
	//
	// Returns an interface to the first local address that supports the
	// given address type.  If an error occurs or the given address type
	// is not supported by any local addresses, null is returned.
	// Address type constants are defined in the TapiConstants interface.
	/////////////////////////////////////////////////////////////////////
	private int  GetAddress(int addressType)
	{
		Variant      var;
		ITCollection itcAddr, itcType;
		ITAddressCapabilities iAddressCapa;
		int          type;

		try 
		{
			// get the collection interface for addresses
			var = m_Tapi.getAddresses();
			itcAddr = (ITCollection) var.toDispatch();
			for (int i=1; i <=itcAddr.getCount(); i++) 
			{
				
				// get the next address
				var = itcAddr.getItem(i);

				//getthe address interface
				m_ITSrcAddress = (tapi3.ITAddress) var.toObject();

				// get the IAddressCapabilities interface
				iAddressCapa=(ITAddressCapabilities)var.toObject();

				type = iAddressCapa.getAddressCapability(tapi3.ADDRESS_CAPABILITY.AC_ADDRESSTYPES);

				if (type == addressType)
					return 1;

			}

			// no address supports the type we're looking for
			return 0;
		}
		catch (ComException e) 
		{
			DoMessage("ComException");
			e.printStackTrace();
			return 0;
		}
		catch (Exception e) 
		{
			DoMessage("ComException");
			e.printStackTrace();
			return 0;
		}
	}

	/////////////////////////////////////////////////////////////////////
	// GetNumVideoWnds
	//
	// Returns the number entered into the tfVideoWnds text field, or
	// -1 if there was an error.
	/////////////////////////////////////////////////////////////////////
	private int GetNumVideoWnds()
	{
		try 
		{
			return Integer.parseInt(ctrls.tfVideoWnds.getText());
		}
		catch (NumberFormatException e) 
		{
			e.printStackTrace();
			return -1;
		}
	}

	/////////////////////////////////////////////////////////////////////
	// GetSelectedConfName
	//
	// Returns the name of the currently selected conference.
	/////////////////////////////////////////////////////////////////////
	private String GetSelectedConfName()
	{
		//return ctrls.lstConferences.getSelectedItem();
		int index;
		index = ctrls.lstConferences.getSelectedIndex();

		if (index < 0)
			return null;

		return confblobname[index];
	}


	/////////////////////////////////////////////////////////////////////
	// DisableControls
	//
	// Disables all of the app's controls.
	/////////////////////////////////////////////////////////////////////
	private void DisableControls()
	{
		ctrls.lstConferences.disable();
		ctrls.btnNew.disable();
		ctrls.btnDelete.disable();
		ctrls.btnInfo.disable();
		ctrls.btnRefresh.disable();
		ctrls.btnJoin.disable();
		ctrls.btnHangup.disable();
		ctrls.btnClose.disable();
	}

	/////////////////////////////////////////////////////////////////////
	// SetStatusMessage
	//
	// Displays messages in the status box.
	/////////////////////////////////////////////////////////////////////
	public void SetStatusMessage(String msg)
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
													 APP_NAME,
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
		AppFrame3 frame = new AppFrame3(APP_NAME);
		frame.show();
		frame.hide();
		frame.resize(frame.insets().left + frame.insets().right  + 320,
					 frame.insets().top  + frame.insets().bottom + 240);
		jt3conf applet = new jt3conf();
		frame.m_App = applet;
		frame.add("Center", applet);
		applet.m_fStandAlone = true;
		frame.show();
		applet.initmain();
		//frame.show();
	}
}


/////////////////////////////////////////////////////////////////////////
//  CLASS: AppFrame3
//
//  DESCRIPTION:
//      Frame for standalone application.
//
/////////////////////////////////////////////////////////////////////////

class AppFrame3 extends Frame
{
	public Applet m_App = null;

	public AppFrame3(String title) 
	{
		super(title);
		setBackground(Color.cyan);
	}
	
	public boolean handleEvent(Event evt)
	{
		if (evt.id == Event.WINDOW_DESTROY) {
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
                 TAPI_EVENT,				// CET_xxx constants
                 tapi3.CALL_STATE,				// CS_xxx constants
				 tapi3.CALL_PRIVILEGE,			// CP_xxx constants
				 TapiConstants,				// misc. constants
				 TERMINAL_DIRECTION,
				 PARTICIPANT_EVENT				 
{
    // Reference to main program object.
    private jt3conf m_App = null;

    
    /////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////
    public CallNot(jt3conf app)
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

		ITCallNotificationEvent pCallNotificationEvent;
		int					CallEventType;
        Variant				avar;
        ITCollection		itc;
		tapi3.ITCallInfo			pCallInfo;
		IVideoWindow		VideoWindow;
        ITTerminal			aterm;
        ITTerminal			pITTerminal;
		int					astr;
		int					vis;
		ITSubStream 		pSubStream;
		ITParticipantSubStreamControl pParticipantControl;
		try
		{
		switch(eventType)
		{
		case TE_CALLNOTIFICATION:
                pCallNotificationEvent = (ITCallNotificationEvent) event; 
				int cp;
				tapi3.ITCallInfo		pCall;
				pCall=(tapi3.ITCallInfo)pCallNotificationEvent.getCall();
				cp=pCall.getPrivilege();
                if (cp==CP_MONITOR)
				{
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
                    // CP_OWNER means that the application is being notified
                    // of a call, and the application has owner privileges on
                    // that call.  event is the Call object.
                    // Note that we don't answer the call at this point.  The
                    // application should wait for a CS_OFFERING CallState
                    // message before answering the call.
					m_App.m_Call = (tapi3.ITBasicCallControl) pCall;
                    m_App.SetStatusMessage("Incoming owner call");
				}
			break;
		case TE_CALLSTATE:
				// CET_CALLSTATEEVENT is a call state event.  
				// event is an ITCallStateEvent object.
				int cs;
	            ITCallStateEvent callStateEvent = (ITCallStateEvent) event;
				cs = callStateEvent.getState();
		        switch (cs)
			    {
					case CS_DISCONNECTED:
						System.out.println("EVENT5 call state disconnect");
                    break;
					case CS_CONNECTED:
						System.out.println("EVENT7 call state connect");
						// make the in dynamic videos visible
                   break;   
				}			// of cs    
					break;
					
			case TE_CALLMEDIA:
				int evt;
	            ITCallMediaEvent callMediaEvent = (ITCallMediaEvent) event;
				evt = callMediaEvent.getEvent();
		        switch (evt)
		        {
		        	case CALL_MEDIA_EVENT.CME_STREAM_ACTIVE:
						tapi3.ITStream Strm=callMediaEvent.getStream();
						if(Strm.getMediaType()==TAPIMEDIATYPE_VIDEO)
						{
							try
							{
							avar = Strm.getTerminals();
							itc=(ITCollection) avar.toDispatch();
							for(int n=1;n<=itc.getCount();n++)
								{
									avar=itc.getItem(n);
									pITTerminal=(ITTerminal)avar.toDispatch();
									if (pITTerminal.getDirection() == TD_RENDER)
									{
										VideoWindow = (IVideoWindow) pITTerminal;
										VideoWindow.putVisible(-1);							
									}
								}
							}
							catch (ComException e) 
							{
				        	    e.printStackTrace();
					        }
				
						} 
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
}   // of class             

