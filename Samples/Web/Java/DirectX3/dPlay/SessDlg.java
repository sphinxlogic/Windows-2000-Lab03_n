// 
//  Copyright (c) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File:			SessDlg.java
//  Description:                Lets the user pick from existing sessions

import com.ms.com.*;
import com.ms.directX.*;
import com.ms.ui.resource.*;
import com.ms.ui.*;
import java.awt.*;

class SessInfo extends UIText{
	_Guid	g;
	String	name;
}


//=-----------------------------
// SessDlg
//=-----------------------------	

class SessDlg extends Panel implements IEnumPlayersCallback2,IEnumSessionsCallback2, DirectXConstants{
	
	Label			m_SessionsLabel;
	Label			m_MembersLabel;
	List			m_SessionsList;
	List			m_MembersList;
	Button			m_JoinButton;
	Button			m_CreateButton;	
	int				m_nSessions;	
	DpChat			m_ChatInfo;

	SessInfo		m_sessArray[]= new SessInfo[100];

	public	boolean	done;

	//=-----------------------------
	// constructor
	//=-----------------------------	
	SessDlg(DpChat chatinfo){
		m_ChatInfo=chatinfo;		
		initAll();		
	}

	//=-----------------------------
	// DoWait
	//=-----------------------------		
	synchronized int DoWait(){
		try {
			this.wait();
		}
		catch (InterruptedException e){
			return -1;
		}
		return 0;
	}

	//=-----------------------------
	// EndWait
	//=-----------------------------		
	synchronized void EndWait(){
		this.notify();
	}


	//=-----------------------------
	// cleanup
	//=-----------------------------		
	void cleanup(){
		m_ChatInfo=null;
		System.gc();
	}

	//=-----------------------------
	// initAll
	//=-----------------------------	
	void initAll(){		
		initUI();
		if (enumSess()==0){
			m_JoinButton.setEnabled(false);
		}
		show();
	}


	//=-----------------------------
	// initUI
	//=-----------------------------	
	void initUI (){
		//create UI objects
		
		m_SessionsLabel = new Label("Open Chat Sessions");
		m_MembersLabel = new Label("People In Session");
		m_SessionsList = new List();
		m_MembersList = new List();
		m_JoinButton = new Button("Join");
		m_CreateButton = new Button("Create");
				
		add(m_SessionsLabel);
		add(m_MembersLabel);		
		
		add(m_SessionsList);
		add(m_MembersList);

		add(m_CreateButton);
		add(m_JoinButton);

		//setBounds
		setLayout(null);
		
		m_SessionsList.setBounds (20,30,180,100);
		m_MembersList.setBounds(210,30,180,100);		

		m_SessionsLabel.setBounds(20 ,0,180,20);
		m_MembersLabel.setBounds (210,0,180,20);
		
		m_JoinButton.setBounds(420,30,50,30);
		m_CreateButton.setBounds(420,80,50,30);
	}
	
	
	//=-----------------------------
	// enumSess
	//=-----------------------------	
	int enumSess(){
		DPSessionDesc desc= new DPSessionDesc();
		_Guid sessguid=null;
		String sessName=null;
		String sessPassword=null;
		m_nSessions		=0;

		m_ChatInfo.m_DirectPlay2.enumSessions(desc,  sessguid, m_ChatInfo.m_ApplicationGuid,
				sessName, sessPassword,	0,
				this, null, DPENUMSESSIONS_AVAILABLE);

		return m_nSessions;
	}

	//=-----------------------------
	// callbackEnumSessions
	//=-----------------------------	
	public void callbackEnumSessions(DPSessionDesc sessionDesc,
        _Guid instanceGuid, _Guid applicationGuid, String sessionName,
        String password, int[] timeOut, int flags, IUnknown context)
	{		

		// see if enum has timed out
		if ((flags & DPESC_TIMEDOUT)!=0){
			// don't try again
			m_ChatInfo.m_DirectPlay2.stopEnumSessions();
			return; //false
		}

		SessInfo si = new SessInfo();
		si.g =instanceGuid;		
		si.name=sessionName;
		
		m_SessionsList.add(sessionName);
		m_sessArray[m_nSessions++]=si;
		

		return; //true
	}

	void DoEnumMembers(_Guid guidInstance){		
		m_MembersList.clear();
		m_ChatInfo.m_DirectPlay2.enumPlayers( guidInstance,
						(IEnumPlayersCallback2 )this, null, DPENUMPLAYERS_SESSION);
		
	}

	public void callbackEnumPlayers(int playerId, int playerType, String playerShortName, String playerLongName, int flags, IUnknown context){
		m_MembersList.add(playerShortName);
	}




	//=-----------------------------
	// handleEvent
	//=-----------------------------	
	public boolean handleEvent(Event evt){
		if (evt.id==Event.ACTION_EVENT){
			if (evt.target==m_JoinButton){
				
				int i=m_SessionsList.getSelectedIndex();
				if (i<0){					
					return true;	
				}

				m_CreateButton.setEnabled(false);
				m_JoinButton.setEnabled(false);

				SessInfo sessinfo = m_sessArray[i];
				m_ChatInfo.m_SessionGuid=sessinfo.g;
				m_ChatInfo.m_SessionName=sessinfo.name;
				done=true;
				EndWait();				
			}

			if (evt.target==m_CreateButton){
				m_CreateButton.setEnabled(false);
				m_JoinButton.setEnabled(false);
				done=true;
				EndWait();				
				return true;
			}							
		}
		else if (evt.id==Event.LIST_SELECT){
			if (evt.target==m_SessionsList){
				int i=m_SessionsList.getSelectedIndex();				
				if (i<0)	return true;	
		
				SessInfo sessinfo = m_sessArray[i];					
				DoEnumMembers(sessinfo.g);						
			}

		}
		return super.handleEvent(evt);
	}

}
