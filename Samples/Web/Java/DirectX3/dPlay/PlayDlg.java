// 
//  Copyright (C) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File:			PlayDlg.java
//  Description:                Panel for user id entry
//

import com.ms.com.*;
import com.ms.directX.*;
import com.ms.ui.resource.*;
import com.ms.ui.*;
import java.awt.*;


class PlayDlg extends Panel implements DirectXConstants {
	
	Label			m_MemberLabel;
	Label			m_SessionLabel;
	TextField		m_MemberName;
	TextField		m_SessionName;
	Button			m_OKButton;	
	DpChat			m_ChatInfo;

	public boolean	done=false;

	//=-----------------------------
	// PlayDlg
	//=-----------------------------		
	PlayDlg(DpChat chatinfo){
		m_ChatInfo=chatinfo;
		initUI();
	}
	
	//=-----------------------------
	// cleanup
	//=-----------------------------		
	void cleanup(){
		m_ChatInfo=null;
		System.gc();
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
	// initUI
	//=-----------------------------		
	void initUI(){
		
		setLayout(null);
		
		m_MemberLabel = new Label("Your Name");
		m_MemberName= new TextField();
		m_SessionLabel = new Label("Session Name");
		m_SessionName= new TextField();
		m_OKButton = new Button("Next");

		add (m_MemberLabel);
		add (m_MemberName);
		add (m_SessionLabel);
		add (m_SessionName);
		add (m_OKButton);

		
		m_MemberLabel.setBounds(20,0,110,20);
		m_MemberName.setBounds(140,0,160,20);

		m_SessionLabel.setBounds(20,30,110,20);
		m_SessionName.setBounds(140,30,160,20);
		
		m_OKButton.setBounds(420,40,50,30);	

		if (m_ChatInfo.m_SessionName!=null){
			m_SessionName.setText(m_ChatInfo.m_SessionName);
			m_SessionName.setEnabled(false);
		}

		if (m_ChatInfo.m_SessionName!=null)
			m_SessionName.setText(m_ChatInfo.m_SessionName);		

	}


	
	//=-----------------------------
	// handleEvent
	//=-----------------------------		
	public boolean handleEvent(Event evt){
		if (evt.id==Event.ACTION_EVENT){
			if (evt.target==m_OKButton){
				
				//Save off info..
				m_ChatInfo.m_SessionName= m_SessionName.getText();
				m_ChatInfo.m_UserShortName = m_MemberName.getText();
				m_ChatInfo.m_UserLongName  = m_MemberName.getText();
				
				//we are done!
				done=true;
				EndWait();				
				return true;
			}
		}
		return super.handleEvent(evt);
	}

	
}
