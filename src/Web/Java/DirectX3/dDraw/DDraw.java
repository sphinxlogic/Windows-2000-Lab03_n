//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.awt.peer.ComponentPeer;
import java.applet.*;
import java.net.URL;
import com.ms.com.*;
import com.ms.awt.*;
import com.ms.awt.peer.*;
import com.ms.directX.*;

public class DDraw extends Applet implements Runnable, DirectXConstants
{
	boolean	StandAlone = false;
	boolean	running = true;
	URL url;
	Thread t; 
	DDrawCanvas ddrawcanvas;
	
	////////////////////////////////////////////////////////////////////////////
	public static void main(String args[])
	{
		DDrawFrame frame = new DDrawFrame("DirectDraw for Java");

		// Must show Frame before we size it so insets() will return valid values
		frame.show();
		frame.hide();
		frame.resize(frame.insets().left + frame.insets().right  + 640,
					 frame.insets().top  + frame.insets().bottom + 480);

		DDraw applet = new DDraw();
		frame.add("Center", applet);

		applet.StandAlone = true;
		applet.init();
		frame.show();
		applet.start();
	}

	//////////////////////////////////////////////////////////////////////////
	public void init()
	{
		if ( StandAlone == false )
			url = getCodeBase();

		BorderLayout bl = new BorderLayout();
		setLayout(bl);

		ddrawcanvas = new DDrawCanvas();
		add("Center", ddrawcanvas);
		show();

		Dimension d = bl.preferredLayoutSize(this);
		resize(d.width, d.height);
	}

	//////////////////////////////////////////////////////////////////////////
	public void start()
	{
		if ( ddrawcanvas != null )
			ddrawcanvas.init(url);

		requestFocus();

		t = new Thread(this);
		running = true;
		t.start();
	}

	//////////////////////////////////////////////////////////////////////////
	public void stop()
	{
		running = false;
		t.stop();
	}

	//////////////////////////////////////////////////////////////////////////
	public void run()
	{
		while (running)
			ddrawcanvas.updateFrame();

		ddrawcanvas.ddPal			= null;				
		ddrawcanvas.ddclipper		= null;			
		ddrawcanvas.ddsOffscreen	= null;		
		ddrawcanvas.ddsPrimary		= null;			
		ddrawcanvas.dd				= null;					
		ddrawcanvas					= null;

		System.gc();
	}
}
