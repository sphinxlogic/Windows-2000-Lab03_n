//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.net.URL;
import java.util.Vector;
import com.ms.com.*;
import com.ms.directX.*;

public class CastleCanvas extends Canvas implements DirectXConstants, ILoadTextureCallback
{
	//////////////////////////////////////////////////////////////////////////
	public URL						url;
	public DirectDraw				dd;					
    public DirectDrawClipper		ddclipper;
	public DirectDrawSurface		ddsprimary;
	public DirectDrawSurface		ddsoffscreen;	
	public DirectDrawSurface		ddszbuffer;
	public DirectDrawPalette		ddpal;
	public Direct3d					d3d;
	public Direct3dDevice			d3ddevice;
    public Direct3dRM				d3drm;
	public Direct3dRMDevice			d3drmdevice;
	public Direct3dRMViewport		d3drmviewport;
   	public Direct3dRMFrame			mainframe;
	public Direct3dRMMeshBuilder	builder;
	public Direct3dRMFrame			scene;
	public Direct3dRMFrame			camera;

	public float rx,ry,rz,rtheta;
	public float px,py,pz;
	public int keydown;

	private boolean running = true;

	public DirectInput	joy;
	public JoyInfo		joypos;
	public JoyCaps		joycaps;
	public int			joyxrange;
	public int			joyyrange;

	D3dVector			pos;
	D3dVector			dir;
	D3dVector			keydir;
	D3dVector			up;
	D3dVector			right;
	D3dVector			zaxis;

	Rect				src;
	
	String				path;
	String				xfile = "castle.x";

	//////////////////////////////////////////////////////////////////////////
	public Dimension preferredSize() 
	{
		return new Dimension(518,384);
	}

	//////////////////////////////////////////////////////////////////////////
	public void init(URL url)
	{
		this.url = url;

	    src = new Rect();
		Dimension s = size();
		src.top		= 0;
		src.left    = 0;
		src.right   = s.width;
		src.bottom  = s.height;

		createDevice();

		pos   = new D3dVector();
		dir   = new D3dVector();
		keydir= new D3dVector();
		up    = new D3dVector();
 		right = new D3dVector();

		joy      = new DirectInput();
		joypos   = new JoyInfo();
		joycaps  = new JoyCaps();

		//
		// Get the Capabilities of the joy stick
		//
		try 
		{
			joy.getDevCaps(JOYSTICKID1,joycaps);

			//
			// Set the axis's I'm interested in
			//
			joypos.flags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNBUTTONS;

			//
			// determine the range of useful values 
			//
			joyxrange = (joycaps.xMax - joycaps.xMin)/2;
			joyyrange = (joycaps.yMax - joycaps.yMin)/2;

		}
		catch( Exception e )
		{
			joypos.flags = 0;
			joyxrange = (joycaps.xMax - joycaps.xMin)/2;
			joyyrange = (joycaps.yMax - joycaps.yMin)/2;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	private void createDevice()
	{
		Dimension s = size();

		dd    = new DirectDraw();
		d3drm = new Direct3dRM();

		dd.setCooperativeLevel(this, DDSCL_NORMAL);

		ddclipper = dd.createClipper(0);
		ddclipper.setComponent(this);

		//
		// Create the primary surface
		//
		DDSurfaceDesc ddsd = new DDSurfaceDesc();
	    ddsd.flags   = DDSD_CAPS;
    	ddsd.ddsCaps = DDSCAPS_PRIMARYSURFACE;
		ddsprimary	 = dd.createSurface(ddsd);

		//
		// Create and Set the clipper for the primary surface
		//
		ddsprimary.setClipper( ddclipper );

		//
		// Create an offscreen rendering surface
		//
	    ddsd.flags   = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    	ddsd.ddsCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = s.width;
    	ddsd.height  = s.height;
		ddsoffscreen = dd.createSurface(ddsd);

	    ddsd.flags   = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_ZBUFFERBITDEPTH;
    	ddsd.ddsCaps = DDSCAPS_ZBUFFER |  DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = s.width;
    	ddsd.height  = s.height;
        ddsd.zbufferBitDepth = 16;
		ddszbuffer	 = dd.createSurface(ddsd);

		ddsoffscreen.addAttachedSurface(ddszbuffer);

		//
		// This will attach the system palette to the offscreen surface
		//
		try
		{
			ddpal = dd.createPalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, (byte[])null);
			if( ddpal != null)
			{
				ddsprimary.setPalette(ddpal);
				ddsoffscreen.setPalette(ddpal);
			}
       	}
       	catch(Exception e)
       	{
			// Failed palette probably not in 8-bit mode
       	}


		d3d = dd.createD3D();

		_Guid g;
		try
		{
			g = d3d.findDeviceForColorModel(D3DCOLOR_MONO, 0);
		}
       	catch(Exception e)
       	{
			// Try again just in case we are running on Minidrivers that 
			// don't support MOMO modes 
			g = d3d.findDeviceForColorModel(D3DCOLOR_RGB, 0);
       	}

		// 
		// Create the D3D Device object associated 
		// with the offscreen surface
		//
	    d3ddevice = ddsoffscreen.create3DDevice(g);

		d3drmdevice = d3drm.createDeviceFromD3D(d3d,d3ddevice);

		switch (d3d.systemBpp())
		{
			case 1:
				d3drmdevice.setShades(4);
				d3drm.setDefaultTextureShades(4);
				break;
				
			case 16:
				d3drmdevice.setShades(32);
				d3drm.setDefaultTextureColors(64);
				d3drm.setDefaultTextureShades(32);
				d3drmdevice.setDither(0);
				break;
				
			case 24:
			case 32:
				d3drmdevice.setShades(256);
				d3drm.setDefaultTextureColors(64);
				d3drm.setDefaultTextureShades(256);
				d3drmdevice.setDither(0);
				break;
				
			default:
				d3drmdevice.setShades(1);
				d3drmdevice.setDither(0);
				d3drm.setDefaultTextureShades(1);
				break;
		}

		d3drmdevice.setQuality(D3DRMRENDER_UNLITFLAT);
		d3drmdevice.setTextureQuality( D3DRMTEXTURE_NEAREST );
		
    	createScene();
		d3drmviewport = d3drm.createViewport(d3drmdevice, camera, 0, 0, d3drmdevice.getWidth(), d3drmdevice.getHeight());
		d3drmviewport.setBack(5000.0F);
	}

	//////////////////////////////////////////////////////////////////////////
	public Direct3dRMTexture callbackLoadTexture(String name, IUnknown args)
	{
		int ext = name.lastIndexOf(".");

		if (ext != -1) 
		{
			String fileExtension = name.substring(ext);
			fileExtension.toLowerCase();
			if( fileExtension.equals(".ppm") == true || fileExtension.equals(".bmp") == true)
			{
				if ( path != null )
					name = path.concat(name);

				return d3drm.loadTexture(name);
			}
		}
		
		return null;
	}
	
	//////////////////////////////////////////////////////////////////////////
	private void createScene()
	{
		String file;

		if ( url != null )	
		{

			path  = url.toString();
			path  = path.substring(6);
			path  = path.replace('/','\\');

			// This is a check for when running under appeletviewer 
			// it puts a '.' at the end of path 
			if ( path.endsWith("\\.") )
			{
				int index = path.lastIndexOf('.');
				path = path.substring(0,index);
			}
		
			file = path.concat(xfile);
		}
		else
		{
			file = xfile.toString();
		}

		scene = d3drm.createFrame(null);
		scene.setSceneBackgroundRGB(1.0f,1.0f,1.0f);

		mainframe = d3drm.createFrame(null);
		mainframe.setRotation(scene, 0.0F, 1.0F, 0.0F, 0.0F);
		mainframe.setPosition(scene, 0.0F, 0.0F, -10.0F);
		mainframe.setSortMode(D3DRMSORT_BACKTOFRONT); 
		mainframe.loadFromFileByPos(file, 0, 0, (ILoadTextureCallback)this, null);

		builder = d3drm.createMeshBuilder();
		builder.setPerspective(1);
		builder.setQuality(D3DRMRENDER_UNLITFLAT);
		builder.setColorSource(D3DRMCOLOR_FROMFACE);
		builder.addFrame(mainframe);
		builder.setColor(-1);

		scene.addVisualMeshBuilder(builder);

		camera = d3drm.createFrame(scene);
		camera.setPosition(scene, 0.0F, 0.0F, 0.0F);
	}

	//////////////////////////////////////////////////////////////////////////
	public void renderScene() 
	{
		scene.move(1.0F);
		d3drmviewport.clear();
		d3drmviewport.render(scene);

		//
		// Blit the Offscreen surface 
		// 
	   	ddsprimary.blt(src, ddsoffscreen, src, DDBLT_WAIT);


		if ( joypos.flags != 0 )	// only check joystick if it's connected 
		{
			try
			{
				joy.getPos(0,joypos);
			}
			catch( Exception e )
			{
				// ... just in case joystick is not working continue to run 
				// keep app alive even if joystick is eith missing or offline somehow.
				joypos.xPos = 0;
				joypos.yPos = 0;
			}
		}

		int xpos = (joypos.xPos - joyxrange)/10;
		int ypos = (joypos.yPos - joyyrange)/10;

		camera.getOrientation(scene, dir, up);
		camera.getPosition(scene, pos);
		d3drm.vectorCrossProduct(right, up, dir);

		//
		// Handle rotation 
		//
		if ( xpos < -150 )
		{
			rtheta = 0.2F;
			ry     = -up.y;
		}
		else if ( xpos > 150 )
		{
			rtheta = 0.2F;
			ry     = up.y;
		}
		else if ( (keydown & 0x33) == 0 )
		{
			rtheta = 0.0F;
			ry     = 0.0F;
		}

		if ( ypos < -150 )
		{
			rtheta = 0.1F;
			rx     = right.x;
			rz     = right.z;
		}
		else if ( ypos > 150 )
		{
			rtheta = 0.1F;
			rx     = -right.x;
			rz     = -right.z;
		}
		else if ( (keydown & 0x33) == 0 )
		{
			rx     = 0.0F;
			rz     = 0.0F;
		}

		camera.setRotation(scene, rx, ry, rz, rtheta);

		// 
		// level off joystick 
		//
		if ( rx == 0.0 && ry == 0.0 )
			camera.setOrientation(scene, dir.x, dir.y, dir.z, 0,1,0 );

		if ( joypos.buttons > 0 )
		{
			if ( (joypos.buttons & JOY_BUTTON1) > 0 )
			{
				pos.x += (dir.x * 1.3F);
				pos.z += (dir.z * 1.3F);
			}
			else
			{
				pos.x += (dir.x * -1.3F);
				pos.z += (dir.z * -1.3F);
			}
		}
		else if ( (keydown  & 0xc) > 0)
		{
			pos.x += keydir.x;
			pos.z += keydir.z;
		}

		if (pos.x < -28)
			pos.x = -28;
		else if ( pos.x > 21 )
			pos.x = 21;

		if (pos.z < -17)
			pos.z = -17;
		else if ( pos.z > 23 )
			pos.z = 23;
		
		camera.setPosition(scene, pos.x,pos.y,pos.z);
	}
}

