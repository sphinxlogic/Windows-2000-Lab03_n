//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.applet.*;
import java.net.URL;
import com.ms.com.*;
import com.ms.directX.*;

public class Castle extends Applet implements Runnable, DirectXConstants
{
	private Thread t; 
	private boolean running;
	private boolean	StandAlone;

	URL	url;
	CastleCanvas castlecanvas;
	D3dVector dir    = new D3dVector();
	D3dVector up     = new D3dVector();
	D3dVector right  = new D3dVector();

	////////////////////////////////////////////////////////////////////////////
	public static void main(String args[])
	{
		Castle applet = new Castle();
		applet.StandAlone = true;

		CastleFrame frame = new CastleFrame("Direct3D Retained Mode Demo");

		frame.show();
		frame.resize(frame.insets().left + frame.insets().right  + 512,
					 frame.insets().top  + frame.insets().bottom + 384);
		frame.add("Center", applet);

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
		setBackground(Color.white);

		castlecanvas = new CastleCanvas();
		add("Center",castlecanvas);

		show();

		Dimension d = bl.preferredLayoutSize(this);
		resize(d.width, d.height);
	}

	//////////////////////////////////////////////////////////////////////////
	public void start()
	{
		if ( castlecanvas != null )
			castlecanvas.init(url);

		requestFocus();

		running = true;
		t = new Thread(this);
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
			castlecanvas.renderScene();

		//
		// Clear out the d3drm objects 
		//
		castlecanvas.scene			= null;
		castlecanvas.camera			= null;
		castlecanvas.mainframe		= null;
		castlecanvas.builder		= null;
		castlecanvas.d3drmviewport	= null;
		castlecanvas.d3drmdevice	= null;
		castlecanvas.d3ddevice		= null;
		castlecanvas.d3d			= null;
		castlecanvas.d3drm			= null;
		castlecanvas.ddpal			= null;
		castlecanvas.ddszbuffer		= null;
		castlecanvas.ddsoffscreen	= null;	
		castlecanvas.ddsprimary		= null;
		castlecanvas.ddclipper		= null;
		castlecanvas.dd				= null;					
		castlecanvas				= null;

		System.gc();
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean keyUp(Event e, int key)
	{
		if ( castlecanvas == null )
			return false;

		switch(key)
		{
            case Event.UP:
				castlecanvas.keydown &= ~0x1;
				break;

            case Event.DOWN:
				castlecanvas.keydown &= ~0x2;
				break;

            case Event.LEFT:
				castlecanvas.keydown &= ~0x10;
                break;

            case Event.RIGHT:
				castlecanvas.keydown &= ~0x20;
                break;

            case 'a':
            case 'A':
				castlecanvas.keydown &= ~0x4;
				castlecanvas.keydir.x = 0;
				castlecanvas.keydir.z = 0;
				break;

			case 'z':
			case 'Z':
				castlecanvas.keydown &= ~0x8;
				castlecanvas.keydir.x = 0;
				castlecanvas.keydir.z = 0;
				break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean keyDown(Event e, int key)
	{
		if ( castlecanvas == null )
			return false;

		castlecanvas.camera.getOrientation(castlecanvas.scene, dir, up);
		castlecanvas.d3drm.vectorCrossProduct(right, up, dir);

		switch(key)
		{
            case Event.UP:
				castlecanvas.keydown |= 0x1;
				castlecanvas.rtheta = 0.1F;
				castlecanvas.rx     = right.x;
				castlecanvas.rz     = right.z;
				break;

            case Event.DOWN:
				castlecanvas.keydown |= 0x2;
				castlecanvas.rtheta = 0.1F;
				castlecanvas.rx     = -right.x;
				castlecanvas.rz     = -right.z;
                break;
                 
            case Event.LEFT:
				castlecanvas.keydown |= 0x10;
				castlecanvas.rtheta = 0.2F;
				castlecanvas.ry     = -up.y;
                break;

            case Event.RIGHT:
				castlecanvas.keydown |= 0x20;
				castlecanvas.rtheta = 0.2F;
				castlecanvas.ry     = up.y;
                break;

            case 'a':
            case 'A':
				castlecanvas.keydown |= 0x4;
				castlecanvas.keydir.x = dir.x * 1.3F;
				castlecanvas.keydir.z = dir.z * 1.3F;
                break;

			case 'z':
			case 'Z':
				castlecanvas.keydown |= 0x8;
				castlecanvas.keydir.x = dir.x * -1.3F;
				castlecanvas.keydir.z = dir.z * -1.3F;
                break;
		}
		return true;
	}
}
