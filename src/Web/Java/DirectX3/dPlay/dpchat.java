// 
//  Copyright (c) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File:               dpchat.java
//  Description:        DPlay Sample
//

import com.ms.com.*;
import com.ms.directX.*;
import com.ms.ui.resource.*;
import com.ms.ui.*;
import java.awt.*;
import SpDlg;
import PlayDlg;
import SessDlg;
import SendBox;

class DpChat extends Panel implements  DirectXConstants {

	public static int	APPMSG_CHATSTRING=0x48;

	SendBox				m_SendBox;							//Edit box for sending
	TextArea			m_ReceiveBox;						//Edit box to read coversation	
	boolean				m_End=false;

	byte				m_MsgBuffer[] = {1};
	int					m_MsgBufferSize[]=new int[1];

	
	public	DirectPlay2	m_DirectPlay2=null;			//DirectPlay variables
	public	int			m_Dpid=-1;					//
	public _Guid		m_ApplicationGuid =null;	//
	public _Guid		m_SessionGuid =null;		//
	public _Guid		m_ServiceProviderGuid=null;	//
	String				m_SessionName;
	String				m_UserShortName;
	String				m_UserLongName;
	
	SpDlg				spdlg;
	SessDlg				sessdlg;
	PlayDlg				playdlg;
	//=-----------------------------
	// DoChat
	//=-----------------------------	
	void DoChat(){
		
		initChatVars();

		boolean bInitDplay=false;
		
		spdlg=new SpDlg(this);
		add(spdlg);		
		spdlg.setBounds(0,30,500,80);		

		while (bInitDplay==false){
			//-	Select Service Provider
			//	fills m_ServiceProviderGuid							
			spdlg.reset();
			spdlg.setEnabled(true);
			spdlg.show();		
			if ( spdlg.DoWait()<0){
				DoCloseAll();
				return;
			}
			spdlg.setEnabled(false);
			
			//- exit here if we are being closed down			
			if (m_End!=false) {
				DoCloseAll();
				return;
			}
			
			//- Create DirectPlay2
			bInitDplay=true;
			try {
				m_DirectPlay2=m_DirectPlay2.create(m_ServiceProviderGuid);
			}
			catch (ComException e){
				bInitDplay=false;
			}
			if (m_DirectPlay2==null){
				bInitDplay=false;
			}
		}
	
		
		//- exit here if we are being closed down			
		if (m_End!=false) {			
			DoCloseAll();			
			return;
		}

		//- Have user Pick Session to join or
		//  ask to create one.
		//	fills m_SessionGuid
		SessDlg sessdlg =new SessDlg(this);	
		add(sessdlg);
		sessdlg.setBounds(0,120,500,130);
		sessdlg.show();
		if ( sessdlg.DoWait()<0)	{
			DoCloseAll();			
			return;
		}
		sessdlg.setEnabled(false);
		
		//- exit here if we are being closed down			
		if (m_End!=false) {
			DoCloseAll();
			return;
		}
		
		//- Have use enter name
		//  fills m_SessionName
		//  fills m_UserShortName
		//  fills m_UserLongName
		PlayDlg playdlg =new PlayDlg(this);
		add(playdlg);
		playdlg.setBounds(0,300,500,100);		
		playdlg.show();

		if ( playdlg.DoWait()<0){
			DoCloseAll();
			return;
		}

		playdlg.setEnabled(false);

		//- exit here if we are being closed down			
		if (m_End!=false) {
			DoCloseAll();
			return;
		}

		//- call dplay2.open
		//  call dplay2.createPlayer
		DoOpenSessionAndCreateMember();

		this.remove(playdlg);
		this.remove(sessdlg);
		this.remove(spdlg);

		//- cleanup
		DoDestroyForms();


		//- exit here if we are being closed down			
		if (m_End!=false) {
			DoCloseAll();
			return;
		}

		//- init the chat boxes
		initChatUI();		

		//- notify people that we have joined
		m_SendBox.setText("new member joining the conversation");
		m_SendBox.SendChatMessage();

		//- show our stuff
		this.show();

		//- loop for messages
		while (m_End==false){
			DoReceive();
			Thread.yield();			
		}	


		//- cleanup
		DoCloseAll();
		this.notify();
	}


	//=---------------------------------
	// DoOpenSessionAndCreateMember
	//=---------------------------------
	// Open a new session with username
	int	DoOpenSessionAndCreateMember(){		

		DPSessionDesc dpsess= new DPSessionDesc();		
		String  password = null;
		int		flags=0;

		if (m_SessionGuid==null){			
			dpsess.flags=DPSESSION_MIGRATEHOST;// | DPSESSION_KEEPALIVE;	
			dpsess.maxPlayers=100;
			m_SessionGuid=new _Guid();
			flags=DPOPEN_CREATE;
		}
		else{			
			flags=DPOPEN_JOIN;
		}
	
		//- open the session		
		m_DirectPlay2.open(dpsess,m_SessionGuid,m_ApplicationGuid,m_SessionName, password, flags);
				
		//- add us as a new member to that session				
		m_Dpid=m_DirectPlay2.createPlayer(m_UserShortName,m_UserLongName, null,0);		

		return m_Dpid;
	}


	//=---------------------------------
	// StopAll()
	//=---------------------------------
	synchronized void StopAll(){

		m_End=true;

		try{	spdlg.notify();	}
		catch (Exception e){}

		try{	sessdlg.notify();}
		catch (Exception e){}

		try{	playdlg.notify();}
		catch (Exception e){}

			
		//wait for cleanup to happen
		try {
			this.wait();
		}
		catch (Exception e){
			//do nothing;
		}
	}
	
	//=---------------------------------
	// DoCloseAll
	//=---------------------------------	
	synchronized int DoCloseAll(){
		//make sure recieve loop falls through		
		m_End=false;

		DoDestroyForms();

		
			//- cleanup sendbox
		if (m_SendBox!=null)
			m_SendBox.cleanup();

		//- clean up dplay
		if (m_DirectPlay2!=null){
			if (m_Dpid!=-1){
				m_DirectPlay2.destroyPlayer(m_Dpid);
			}
			m_Dpid=-1;
			
			try {
				m_DirectPlay2.close();
			}
			catch (ComException e){
				System.out.println("Session close failed");
			}

		}
		m_DirectPlay2=null;
		System.gc();
		
		this.notify();
		return 0;	
	}


	//=---------------------------------
	// DoDestroyForms
	//=---------------------------------	
	void DoDestroyForms(){


		if (spdlg!=null){
			spdlg.setVisible(false);
			spdlg.cleanup();
		}

		if (sessdlg!=null){
			sessdlg.setVisible(false);	
			sessdlg.cleanup();
		}
			
		
		if (playdlg!=null){
			playdlg.setVisible(false);
			playdlg.cleanup();
		}

		try{	this.remove(spdlg);	}
		catch (Exception e){}

		try{	this.remove(sessdlg);}
		catch (Exception e){}

		try{	this.remove(playdlg);}
		catch (Exception e){}

		spdlg=null;
		sessdlg=null;
		playdlg=null;

		System.gc();

	}
	//=---------------------------------
	// handleEvent
	//=---------------------------------
	public boolean handleEvent(Event evt){
		if (evt.id==Event.WINDOW_DESTROY){
			m_End=true;			
		}
		return super.handleEvent(evt);
	}


	//=---------------------------------
	// initChatVars
	//=---------------------------------
	void initChatVars(){

		m_DirectPlay2= new DirectPlay2();
		m_ApplicationGuid= new _Guid();		
		m_ApplicationGuid.set(0xba542a0,	(short)0xe1ff,	(short)0x11cf,
			(byte)0x9c,	(byte)0x4e,	(byte)0x0, (byte)0xa0,	(byte)0xc9,	(byte)0x5,(byte)0x42, (byte)0x5e);
	}

	//=---------------------------------
	// initChatUI
	//=---------------------------------
	void initChatUI(){	
		
		setLayout(null);
		
		m_SendBox= new SendBox(m_DirectPlay2,m_Dpid,m_UserShortName,this);
		m_ReceiveBox = new TextArea();
		
		add(m_SendBox);
		add(m_ReceiveBox);
		
		m_SendBox.setBounds(10,20,500,60);
		m_ReceiveBox.setBounds(10,100,500,240);

	}

	//=---------------------------------
	// setReceiveInfo
	//=---------------------------------
	synchronized public void setReceiveInfo(String s){
		m_ReceiveBox.append(s);
	}

	//=---------------------------------
	// DoReceive
	//=---------------------------------
	int DoReceive()
	{
		
		if (m_DirectPlay2==null) return 0;

		int					idFrom=0;
		int					idTo=0;
		int					hr=0;						
		int[] fromPlayerId= new int[1];
		int[] toPlayerId= new int[1];

		hr=0;
		try {
			boolean buffsizeloop = true;
			while ( buffsizeloop )
			{
				hr = m_DirectPlay2.receive(
					fromPlayerId,toPlayerId, 
					DPRECEIVE_ALL,	m_MsgBuffer,
					m_MsgBufferSize);



				if ( hr == DPERR_BUFFERTOOSMALL )
				{					
					m_MsgBuffer= new byte[m_MsgBufferSize[0]];					

					try {
						int recievesize = m_DirectPlay2.receiveSize(fromPlayerId,toPlayerId,DPRECEIVE_ALL);						
					}
					catch (ComException e){
						System.out.println("recisveSize Exeception hr ="+ e.getHResult());
					}
					
				}
				else
					buffsizeloop = false;
			}
		}
		catch (ComException e){
			hr = e.getHResult();			
		}

		idFrom=fromPlayerId[0];
		idTo=toPlayerId[0];


		if (hr>=0){
			
			//if we have a valid message do something
			if (m_MsgBufferSize[0]>0){				
				if (idFrom == 0) //DPID_SYSMSG)
					DoSystemMessage(m_MsgBuffer, m_MsgBufferSize[0], fromPlayerId[0], toPlayerId[0]);
				else
					DoApplicationMessage(m_MsgBuffer, m_MsgBufferSize[0], fromPlayerId[0], toPlayerId[0]);
			}
		}
		
		return 0;
	}


	//=---------------------------------
	// DoApplicationMessage
	//=---------------------------------
	void DoApplicationMessage(byte [] Msg, int msgSize, int idFrom, int idTo)
	{		
		String szStr="";
	
		for (int i=0;i<msgSize;i++){
			char c=(char)Msg[i];
			szStr=szStr+String.valueOf(c);
		}
		

		if (szStr!=null)
			setReceiveInfo(szStr);
		else
			System.out.println("our string is null");
							
		
	}

	//=---------------------------------
	// DoSystemMessage
	//=---------------------------------
	void DoSystemMessage(byte[] MsgBuff,int MsgSize, int idFrom, int idTo)
	{	
		//System.out.println("got SysMessage");		
	}



}
