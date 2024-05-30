// 
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.awt.peer.ComponentPeer;
import java.applet.*;
import com.ms.com.*;
import com.ms.awt.*;
import com.ms.awt.peer.*;
import com.ms.directX.*;

public class FlipCube extends Applet implements Runnable, DirectXConstants
{
	boolean	running = true;
	Thread t; 
	FlipCubeCanvas cube;

	////////////////////////////////////////////////////////////////////////////

	public static void main(String args[])
	{
		FlipCubeFrame frame = new FlipCubeFrame("Direct3D Imediate Mode Sample");

		frame.setResizable(false);
		frame.show();
		frame.hide();

		frame.resize(frame.insets().left + frame.insets().right  + 256,
					 frame.insets().top  + frame.insets().bottom + 256);


		FlipCube applet = new FlipCube();
		frame.add("Center", applet);

		frame.show();
		applet.init();
		applet.start();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	// init
	//
	public void init()
	{
		BorderLayout bl = new BorderLayout();
		setLayout(bl);

		cube = new FlipCubeCanvas();
		add("Center",cube);

		show();

		Dimension d = bl.preferredLayoutSize(this);
		resize(d.width, d.height);
	}

	public void start()
	{
		try 
		{
			cube.InitDDraw();
			cube.InitD3D();
			cube.InitExecuteBuffer();
		} 
		catch(Exception e) 
		{
			System.out.println("Direct3D Initialization Exception:"+e);
		}

		requestFocus();

		t = new Thread(this);
		running = true;
		t.start();
	}

	public void stop()
	{
		running = false;
		t.stop();
	}

	//////////////////////////////////////////////////////////////////////////
	public void run()
	{
		while (running)
			cube.updateframe();

		cube.BackgroundMaterial	= null;
		cube.D3DView			= null;
		cube.D3DExBuf			= null;
		cube.D3DDevice			= null;
		cube.D3D				= null;
		cube.DDPal				= null;			
		cube.DDClipper			= null;		
		cube.DDSPrimary			= null;		
		cube.DDSOffscreen		= null;	
		cube.DD					= null;				

		System.gc();
	}
}
