//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.net.URL;
import com.ms.com.*;
import com.ms.directX.*;
	
public class DDrawCanvas extends Canvas implements DirectXConstants
{
	DirectDraw			dd;					// DirectDraw object
	DirectDrawSurface	ddsPrimary;			// DirectDraw primary surface
	DirectDrawSurface	ddsOffscreen;				// Offscreen surface 1
	DirectDrawPalette	ddPal;				// DirectDraw palette
	DirectDrawClipper	ddclipper;			// clipper for primary
	String 				szBitmap = "Frntback.bmp";


    boolean	FirstFrame 	= true;
    long 	lastTickCount;
    long	UpdateDelay = 10;
	Rect	toScreen;
	Rect	dest;
	Rect	rc;

	DirectInput	joy;
	JoyInfo		joypos;
	JoyCaps		joycaps;
	int			joyxrange;
	int			joyyrange;

	//////////////////////////////////////////////////////////////////////////
	public Dimension preferredSize() 
	{
		return new Dimension(640,480);
	}

	//////////////////////////////////////////////////////////////////////////
	DirectDrawSurface LoadBitmap(DirectDraw dd, String file, int dx, int dy)
	{
	    DirectDrawSurface	pdds = null;
		DirectDrawBitmap	bm;
		DDSurfaceDesc 		ddsd;	

    	bm = new DirectDrawBitmap();
	    bm.filename (file);	
    	bm.initWidth(dx);
	    bm.initHeight(dy);

		if( bm.loaded() != 0 )
		{
		    //
    		// create a DirectDrawSurface for this bitmap
		    //
			ddsd          = new DDSurfaceDesc();
	    	ddsd.flags    = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	    	ddsd.ddsCaps  = DDSCAPS_OFFSCREENPLAIN;
	    	ddsd.width    = bm.width();
	    	ddsd.height   = bm.height();
    		
    		pdds = dd.createSurface( ddsd );
			pdds.copyBitmap(bm, 0, 0, 0, 0);
		}
		
		return pdds;
	}

	
	//////////////////////////////////////////////////////////////////////////
	void init(URL url)
	{
		Dimension s = size();

		DDSurfaceDesc 		ddsd;		
		
		//
		// create the main DirectDraw object
		//
		dd = new DirectDraw();
		dd.setCooperativeLevel(this, DDSCL_NORMAL);

		//
		// Create the primary surface
		//
		ddsd         = new DDSurfaceDesc();
	    ddsd.flags   = DDSD_CAPS ;
    	ddsd.ddsCaps = DDSCAPS_PRIMARYSURFACE;
		ddsPrimary   = dd.createSurface(ddsd); 

		//
		// create a clipper for the primary surface
		//
		ddclipper = dd.createClipper(0);
		ddclipper.setComponent(this);			
		ddsPrimary.setClipper( ddclipper );

		try
		{
			// Create a default palette
			ddPal = dd.createPalette(DDPCAPS_8BIT);
			if( ddPal != null)
				ddsPrimary.setPalette(ddPal);
       	}
       	catch(Exception e)
       	{
			// Failed palette probably not in 8-bit mode
       	}

		// Deternime the path
		String path;
		if ( url != null )	
		{
			path = url.toString();
			path = path.substring(6);
			path = path.replace('/','\\');

			// This is a check for when running under appeletviewer 
			// it puts a '.' at the end of path 
			if ( path.endsWith("\\.") )
			{
				int index = path.lastIndexOf('.');
				path = path.substring(0,index);
			}
			path = path.concat(szBitmap);
		}
		else
		{
			path = szBitmap;
		}

    	// load our bitmap
    	ddsOffscreen = LoadBitmap(dd, path, 0, 0);

	    rc              = new Rect();
	    toScreen 		= new Rect();

		toScreen.left	= 0;
		toScreen.top	= 0;
		toScreen.right	= s.width;
		toScreen.bottom = s.height;

		joy           = new DirectInput();
		joypos        = new JoyInfo();
		joycaps       = new JoyCaps();

		//
		// Get number of potentially avaible joysticks 
		//
		int numofjoysticks = joy.getNumDevs();

		try
		{
			//
			// Get the Capabilities of the joy stick
			//
			joy.getDevCaps(JOYSTICKID1,joycaps);

			//
			// Set the axis's I'm interested in
			//
			joypos.flags = JOY_RETURNX | JOY_RETURNY;

			//
			// determine the range of useful values 
			//
			joyxrange = (joycaps.xMax - joycaps.xMin)/2;
			joyyrange = (joycaps.yMax - joycaps.yMin)/2;
		}
		catch ( Exception e )
		{
			// DirectInput will throw execptions if a joy stick is not connected
			joypos.flags = 0;
			joyxrange = 0;
			joyyrange = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void updateFrame()
	{
	    long	thisTickCount;
    	int		ddrval;
	    Point	pt;
		int		rcleft;
		int		rctop;
		int		rcright;
		int		rcbottom;
		int		destleft;
		int		desttop;
		int		destright;
		int		destbottom;
		int		done;

	    thisTickCount = dd.tickCount();
    	if((thisTickCount - lastTickCount) > UpdateDelay)
		{
			//
		    // Move to next frame;
		    //
		    lastTickCount = thisTickCount;

			if ( joypos.flags != 0 )
			{
				try
				{
					joy.getPos(0,joypos);
				}
				catch ( Exception e )
				{
					// keep app alive even if joystick is eith missing or offline somehow.
					joypos.xPos = 0;
					joypos.yPos = 0;
				}
			}

			if ( joyxrange != 0 && joyyrange != 0 )
			{
				toScreen.left   += ((joypos.xPos - joyxrange)*10)/joyxrange;
				toScreen.top    += ((joypos.yPos - joyyrange)*10)/joyyrange;
			}

			if ( toScreen.left < 0 || toScreen.left > 640-64 )
			{
				if ( toScreen.left < 0 )	
					toScreen.left = 0;
				else
					toScreen.left = 640-64;

			}
			if ( toScreen.top < 0 || toScreen.top > 480-64 )
			{
				if ( toScreen.top < 0 )
					toScreen.top = 0; 
				else
					toScreen.top = 480-64;
			}

			toScreen.right  = toScreen.left + 64;
			toScreen.bottom = toScreen.top  + 64;

			if(FirstFrame == true)
			{
				// Blit the stuff for the first frame
				//
				rc.left   = 0;
				rc.top    = 0;
				rc.right  = 640;
				rc.bottom = 480;
				FirstFrame = false;
			}
			else
			{
				// Blit the stuff for the first frame
				//
				rc.left   = 0;
				rc.top    = 480;
				rc.right  = 640;
				rc.bottom = 960;
				FirstFrame = true;
			}

	    	ddsPrimary.blt( toScreen, ddsOffscreen, rc, 0);
		}
	}
}
