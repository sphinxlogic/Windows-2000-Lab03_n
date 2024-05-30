// 
//  Copyright (c) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File:			SendBox.java
//  Description:                Broadcasts text data
//
import com.ms.com.*;
import com.ms.directX.*;
import com.ms.ui.*;
import java.awt.*;

class SendBox extends TextArea implements DirectXConstants {

	int				m_FromId=0;
	DirectPlay2		m_dp=null;
	String			m_FromName;
	
	int				SIZE_INCREMENT		= 300;
	int				m_MaxMsgSize		= SIZE_INCREMENT;
	byte			m_Msg[]				= new byte[m_MaxMsgSize];
	int				m_nCount;
	DpChat			m_ChatInfo;


	//=-----------------------------
	// SendBox
	//=-----------------------------		
	SendBox(DirectPlay2 dp, int id, String sName,DpChat chatinfo){
		super();	
		m_FromId=id;
		m_dp=dp;
		m_FromName=sName;
		m_ChatInfo=chatinfo;

	}

	//=-----------------------------
	// cleanup
	//=-----------------------------		
	void cleanup(){
		m_ChatInfo=null;
		m_dp=null;
		System.gc();
	}



	//=-----------------------------
	// SendChatMessage
	//=-----------------------------		
	void SendChatMessage()
		{
			

		String szEditText=this.getText();
		String szOut=m_FromName+": "+szEditText.trim()+"\n";

		m_ChatInfo.setReceiveInfo(szOut);
		int outLength=szOut.length();
	
		//- take care of very long strings
		if (outLength>m_MaxMsgSize){
			m_MaxMsgSize += SIZE_INCREMENT;
			m_Msg= new byte[m_MaxMsgSize];
		}

		//- copy the message into our buffer
		for (int i=0;i<outLength;i++){
			m_Msg[i]=(byte)szOut.charAt(i);
		}

		//- clear our buffer
		this.setText("");

		int dataSize=szOut.length();				
		int flags=0;
		
		
		try {
			m_dp.send(m_FromId,  0,  DPSEND_GUARANTEED, m_Msg, dataSize);						
		}
		catch (ComException e){
			int hr = e.getHResult();
			System.out.println("Send faulted" +hr);
		}
	}

	//=-----------------------------
	// handleEvent
	//=-----------------------------		
	public boolean handleEvent(Event evt){
		if (evt.id==Event.KEY_PRESS){
			char chr=(char)evt.key;
			if (chr=='\n'){			
				SendChatMessage();
			}
			
		}
		return super.handleEvent(evt);
	}
}

