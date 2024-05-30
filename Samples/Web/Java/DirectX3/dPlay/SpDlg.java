// 
//  Copyright (c) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File:               SpDlg.java
//  Description:        Lets the user pick a service provider
//

import com.ms.com.*;
import com.ms.directX.*;
import com.ms.ui.resource.*;
import com.ms.ui.*;
import java.awt.*;

class SpInfo {
	_Guid g;
	String name;
}


class SpDlg extends Panel implements IEnumServiceProvidersCallback{

	Label			m_ServiceProviderLabel;
	Choice			m_ServiceProviderList;
	Button			m_OKButton;	
	int				m_nProviders;
	DpChat			m_ChatInfo;
	SpInfo			m_spArray[]= new SpInfo[100];
	
	public	boolean	done=false;

	//=-----------------------------
	// SpDlg
	//=-----------------------------	
	public SpDlg(DpChat chatinfo){
		m_ChatInfo=chatinfo;
		initUI();
		enumSP();
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
	// reset
	//=-----------------------------	
	void reset(){
		done=false;
		m_OKButton.setEnabled(true);
	}
	//=-----------------------------
	// enumSp
	//=-----------------------------	
	int enumSP(){		
		//enum Service Providers		
		m_nProviders=0;
		m_ChatInfo.m_DirectPlay2.enumServiceProviders(this,null);				
		return m_nProviders; 
	}



	//=-----------------------------
	// initUI
	//=-----------------------------	
	void initUI (){

		//create UI objects
		m_ServiceProviderLabel = new Label("Select Service Provider");
		m_ServiceProviderList = new Choice();
		m_OKButton = new Button("Next");
	
		
		//add components
		add (m_ServiceProviderLabel);
		add (m_ServiceProviderList);
		add (m_OKButton);


		//setBounds
		setLayout(null);
		
		m_ServiceProviderLabel.setBounds(20,0,260,20);
		m_ServiceProviderList.setBounds(20,25,260,30);		
		m_OKButton.setBounds(420,25,50,30);
		

	}

	//=-----------------------------
	// callbackEnumServiceProviders
	//=-----------------------------	
	public void callbackEnumServiceProviders(_Guid spGuid, String spName,
        int majorVer, int minorVer, IUnknown context)	
	{		
		
		SpInfo spinfo = new SpInfo();
		spinfo.name=spName;
		spinfo.g=spGuid;
		m_spArray[m_nProviders++]=spinfo;

		m_ServiceProviderList.add(spName);
	
		
	}


	//=-----------------------------
	// handleEvent
	//=-----------------------------	
	public boolean handleEvent(Event evt){
		

		if (evt.target==m_OKButton){
		
			if (evt.id==Event.ACTION_EVENT){
				int i=m_ServiceProviderList.getSelectedIndex();
				if (i>=0){
					SpInfo spinfo=m_spArray[i];
					m_ChatInfo.m_ServiceProviderGuid=spinfo.g;
					m_OKButton.setEnabled(false);
					done=true;
					EndWait();
					return true;
				}
				else{
					m_ServiceProviderLabel.setText("You Must Select Service Provider!");
					return true;	
				}
			

			}
		}		
		return super.handleEvent(evt);
	}

}
