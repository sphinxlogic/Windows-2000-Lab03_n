// 
//  Copyright (c) 1997 Microsoft Corporation. All Rights Reserved.
//
//  File:               DpChatApplet.java
//  Description:        Allows DPChat to be run from an applet
//

import java.applet.*;
import java.awt.*;
import com.ms.ui.*;
import com.ms.com.*;
import com.ms.directX.*;
import DpChat;

public class DpChatApplet extends Applet implements Runnable
{

	private	DpChat	m_dpc;
	private Thread	m_dpcThread = null;

	//=-------------------------------------------------------------------------
	// DpChatApplet Class Constructor
	//=-------------------------------------------------------------------------
	public DpChatApplet()
	{	
	}

	//=--------------------------------------------------------------------------
	// getAppletInfo
	//=--------------------------------------------------------------------------
	//	The getAppletInfo() method returns a string describing the applet's
	// author, copyright date, or miscellaneous information.
    
	public String getAppletInfo()
	{
		return "Name: DpChatApplet\r\n";
	}


	
	//=-------------------------------------------------------------------------
	// init
	//=--------------------------------------------------------------------------
	// The init() method is called by the AWT when an applet is first loaded or
	// reloaded.  Override this method to perform whatever initialization your
	// applet needs, such as initializing data structures, loading images or
	// fonts, creating frame windows, setting the layout manager, or adding UI
	// components.
    public void init()
	{       
		//close down our prev instance if we 
		//are being reloaded
		CloseDPC();
	}

	//=-------------------------------------------------------------------------
	// destroy
	//=--------------------------------------------------------------------------
	// Place additional applet clean up code here.  destroy() is called when
	// when you applet is terminating and being unloaded.
	public void destroy()
	{
		//cleanup code in stop
	}
	
	//=-------------------------------------------------------------------------
	// paint
	//=--------------------------------------------------------------------------	
	public void paint(Graphics g)
	{
		g.drawString("Direct Play Chat for Java", 10, 15);
	}
	
	
	//= -------------------------------------------------------------------------
	// start
	//=--------------------------------------------------------------------------	
	// The start() method is called when the page containing the applet
	// first appears on the screen. The AppletWizard's initial implementation
	// of this method starts execution of the applet's thread.
	public void start()
	{
		if (m_dpcThread== null)
		{
			m_dpcThread= new Thread(this);
			m_dpcThread.start();
		}
	}
	
	//=-------------------------------------------------------------------------
	// stop
	//=--------------------------------------------------------------------------	
	// called when browser is terminated
	public void stop()
	{
		CloseDPC();
	}


	//=-------------------------------------------------------------------------
	// run
	//=--------------------------------------------------------------------------	
	// called from start
	//
	public void run()
	{
		try {
			m_dpc = new DpChat();
			add(m_dpc);		
			m_dpc.setBounds(0,30,550,430);
			m_dpc.setVisible(true);	
			m_dpc.show();
			m_dpc.DoChat();	
		}
		catch (Exception e){
			//do nothing
		}
	}

	//=-------------------------------------------------------------------------
	// closeDPC 
	//=--------------------------------------------------------------------------	
	// if dpchat class exits
	// close it down
	//
	void CloseDPC(){
		if (m_dpc!=null){
			m_dpc.StopAll();
			m_dpc.DoCloseAll();
		}

		if (m_dpcThread!=null)
			m_dpcThread.stop();

		m_dpcThread=null;
		m_dpc=null;
		System.gc();
	}


}
