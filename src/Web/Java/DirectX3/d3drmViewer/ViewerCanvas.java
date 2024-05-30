//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.net.URL;
import java.io.File;
import java.io.FilenameFilter;
import com.ms.com.*;
import com.ms.awt.*;
import com.ms.directX.*;
import com.ms.ui.*;

/////////////////////////////////////////////////////////////////////////////////////////////////////
class FrameMoveData implements IUnknown
{
	float time;
	Direct3dRMAnimationSet anim;
}

//////////////////////////////////////////////////////////////////////////
class FileName implements FilenameFilter 
{
	public String path;
    public String fileName;
    
    FileName(String p, String n) 
    {
    	path = p;
		fileName = n;
    }

    public boolean accept(File dir, String name) 
    {
		if(path.equals(dir.getPath()) && name.equals(fileName)) 
		{
		    return true;
		}
		return false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
public class ViewerCanvas extends Canvas implements DirectXConstants, MenuXConstants, IFrameMoveCallback, 
		ILoadTextureCallback
{
	//////////////////////////////////////////////////////////////////////////
	public void callbackFrameMove(Direct3dRMFrame obj, IUnknown punk, float delta)
	{
		FrameMoveData fmd = (FrameMoveData)punk;
		fmd.anim.setTime(fmd.time);
		fmd.time += delta;
	}

	//////////////////////////////////////////////////////////////////////////
	void setAnimationCallback(Direct3dRMFrame f, Direct3dRMAnimationSet animset)
	{
		FrameMoveData fmd = new FrameMoveData();
		fmd.time = 0;
		fmd.anim = animset;

		f.addMoveCallback((IFrameMoveCallback)this, fmd);
	}

	public Direct3dRM				d3drm;
	public DirectDrawClipper		ddclipper;
	public DirectDraw				DD;					// DirectDraw object
	public DirectDrawSurface		DDSZBuffer;
	public Direct3dDevice			D3DDevice;			
	public Direct3d					D3D; 
	public DirectDrawPalette		DDPal;				// DirectDraw palette
	public Direct3dRMFrame			scene;
	public Direct3dRMFrame			camera;
   	public Direct3dRMFrame			mainframe;
	public Direct3dRMDevice			dev;
	public Direct3dRMViewport		view;
	public DirectDrawSurface		ddsPrimary;			// DirectDraw primary surface
	public DirectDrawSurface		ddsOffscreen;		// Offscreen rendering surface 
   	public Direct3dRMFrame			light;
	public Direct3dRMLight			light1;
	public Direct3dRMLight			light2;
	public Direct3dRMMaterial		mat;
	public int						model;

	private boolean					inblit;
	private Rect					bltrect;

	ViewerSelection	sel;
	int 			last_x, last_y;		// mouse positions
	Viewer			tg;

	public final int MENU_FILE_ABOUT            = 1 ;
	public final int MENU_FILE_OPEN             = 2 ;
	public final int MENU_FILE_OPEN_ANIMSET     = 3 ; 
	public final int MENU_FILE_OPEN_FRAME       = 4 ;
	public final int MENU_FILE_EXIT             = 5 ;
	public final int MENU_EDIT_CUT              = 6 ;
	public final int MENU_EDIT_COPY             = 7 ;
	public final int MENU_EDIT_PASTE            = 8 ;
	public final int MENU_EDIT_DELETE           = 9 ;
	public final int MENU_EDIT_COLOR            = 10;
	public final int MENU_EDIT_BOXES            = 11;
	public final int MENU_QUALITY_LIGHTING      = 12; // first in menu
	public final int MENU_QUALITY_POINTS        = 13;
	public final int MENU_QUALITY_WIREFRAME     = 14;
	public final int MENU_QUALITY_SOLID         = 15;
	public final int MENU_QUALITY_FLAT          = 16;
	public final int MENU_QUALITY_GOURAUD       = 17;
	public final int MENU_QUALITY_PHONG         = 18;
	public final int MENU_MODEL_MONO            = 19;
	public final int MENU_MODEL_RGB             = 20;
	public final int MENU_DITHER                = 21;
	public final int MENU_TEXTURE_FILTERING     = 22;
	public final int MENU_LIGHT_DIRECTIONAL     = 23; 
	public final int MENU_LIGHT_PARALLEL_POINT  = 24;
	public final int MENU_LIGHT_POINT           = 25;
	public final int MENU_LIGHT_SPOT            = 26;
	public final int MENU_FOG_ENABLE			= 27;

	MenuPanel menu;

	public void attachMenu(MenuPanel menu)
	{
		this.menu = menu;
	}

	public Dimension preferredSize() 
	{
		return new Dimension(640,480);
	}

	//////////////////////////////////////////////////////////////////////////
	public void paint(Graphics g)
	{
	}

	public void update(Graphics g)
	{
	}
  
	//////////////////////////////////////////////////////////////////////////
	ViewerCanvas(String s, Viewer t)
	{
		tg  = t;
		setBackground(Color.black);
	}
	
	//////////////////////////////////////////////////////////////////////////
	// Initialize everyting, cant do anything in the constructor, 
	// no window created yet!
	//
	public void startDirect()
	{
		menu.CheckMenuItem(MENU_QUALITY_LIGHTING, true);
		menu.CheckMenuItem(MENU_QUALITY_FLAT, true);
		menu.CheckMenuItem(MENU_QUALITY_SOLID, true);
		menu.CheckMenuItem(MENU_MODEL_MONO, true);

		model 	= D3DCOLOR_MONO;

		d3drm		= new Direct3dRM();
		sel	        = new ViewerSelection(d3drm);

		CreateDevice();

		Dimension s = size();
	    bltrect			= new Rect();
		bltrect.left    = 0;
		bltrect.top     = 0;
		bltrect.right   = s.width;
		bltrect.bottom  = s.height;
	}

	//////////////////////////////////////////////////////////////////////////
	int ShadeModeToMenuItem(int sm)
	{
    	switch (sm) 
		{
    		case D3DRMSHADE_FLAT:
				return MENU_QUALITY_FLAT;

    		case D3DRMSHADE_GOURAUD:
				return MENU_QUALITY_GOURAUD;

    		case D3DRMSHADE_PHONG:
				return MENU_QUALITY_PHONG;
    	}
    	return -1;
	}

	//////////////////////////////////////////////////////////////////////////
	void SetShadeMode(int sm)
	{
    	int quality = dev.getQuality();
	    int oldsm = (int)(quality & D3DRMSHADE_MASK);

    	menu.CheckMenuItem(ShadeModeToMenuItem(oldsm),  false );
    	menu.CheckMenuItem(ShadeModeToMenuItem(sm),		true );

    	quality = (quality & ~D3DRMSHADE_MASK) | sm;
    	dev.setQuality(quality);
	}

	//////////////////////////////////////////////////////////////////////////
	String OpenNewFile(String title)
	{
		FileDialog fileDialog = new FileDialog(tg.frame, title, FileDialog.LOAD);
		
		// set the fileNameFilter in this FileDialog object
		FileName fileName = new FileName("~/", "*.x");
		fileDialog.setFilenameFilter(fileName);
		
		// set the directory in the FileDialog object
		fileDialog.setDirectory("C:\\dxsdk\\sdk\\media");
		
		// set the file in the FileDialog object
		fileDialog.setFile("*.x");
                
		// show this fileDialog to the screen
		fileDialog.show();
		return fileDialog.getFile();
	}
	
	//////////////////////////////////////////////////////////////////////////
	int FillModeToMenuItem(int fm)
	{
    	switch (fm) 
		{
			case D3DRMFILL_POINTS:
				return MENU_QUALITY_POINTS;

			case D3DRMFILL_WIREFRAME:
				return MENU_QUALITY_WIREFRAME;

			case D3DRMFILL_SOLID:
				return MENU_QUALITY_SOLID;
	    }
    	return -1;
	}

	//////////////////////////////////////////////////////////////////////////
	void SetFillMode(int fm)
	{
    	int quality = dev.getQuality();
    	int oldfm = (int)(quality & D3DRMFILL_MASK);

		menu.CheckMenuItem(FillModeToMenuItem(oldfm), false);
		menu.CheckMenuItem(FillModeToMenuItem(fm),	  true);

     	quality = (quality & ~D3DRMFILL_MASK) | fm;
    	dev.setQuality(quality);
	}

	//////////////////////////////////////////////////////////////////////////
	void SetModel(int newmodel)
	{
    	if (model != newmodel) 
		{
			try 
			{
				tg.rebuilddevice = true;
				tg.model	= model;
				tg.width	= dev.getWidth();
				tg.height	= dev.getHeight();

				model = newmodel;
			}
			catch( ComException ce)
			{
				// Device failed to build exception 
			}
		}
		menu.CheckMenuItem((model==D3DCOLOR_MONO)?MENU_MODEL_MONO:MENU_MODEL_RGB, true);
	}

	//////////////////////////////////////////////////////////////////////////
	void ToggleDither()
	{
    	int dither = dev.getDither();
    	boolean checked;
    	
		dither = (dither == 0) ?1 :0;
    	dev.setDither(dither);

		if (dither != 0) 
			checked = true;
    	else 
			checked = false;

    	menu.CheckMenuItem(MENU_DITHER, checked);
	}

	void ToggleFog()
	{
    	int fog = scene.getSceneFogEnable();
    	boolean checked;
    	
		fog = (fog == 0) ?1 :0;
		
		if (fog != 0) 
		{
			checked = true;
			setFog(1, 0, 5, 15, 0);
		}
    	else 
		{
			checked = false;
			setFog(0,0,0,0,0);
		}
    	menu.CheckMenuItem(MENU_FOG_ENABLE, checked);
	}

	void ToggleTextureFiltering()
	{
    	int tq = dev.getTextureQuality();
    	boolean checked;

    	if (tq == D3DRMTEXTURE_NEAREST)
        	tq = D3DRMTEXTURE_LINEAR;
    	else
        	tq = D3DRMTEXTURE_NEAREST;

    	dev.setTextureQuality(tq);

    	if (tq == D3DRMTEXTURE_LINEAR) 
			checked = true;
    	else 
			checked = false;

    	menu.CheckMenuItem(MENU_TEXTURE_FILTERING, checked);
	}

	void ToggleLighting()
	{
		int quality = dev.getQuality();
		int mode = (int)(quality & D3DRMLIGHT_MASK);

		if (mode == D3DRMLIGHT_ON)
        	mode = D3DRMLIGHT_OFF;
    	else
        	mode = D3DRMLIGHT_ON;

		menu.CheckMenuItem(MENU_QUALITY_LIGHTING, (mode == D3DRMLIGHT_ON ?true:false));

	    quality = (quality & ~D3DRMLIGHT_MASK) | mode;
    	dev.setQuality(quality);
	}

	//////////////////////////////////////////////////////////////////////////
	void CreateLight(int wparam)
	{
    	Direct3dRMMeshBuilder builder = null;
		Direct3dRMLight light = null;
    	Direct3dRMFrame f = null;

    	builder = d3drm.createMeshBuilder();

    	if (wparam == MENU_LIGHT_DIRECTIONAL) 
		{
        	builder.loadFromFileByPos(tg.getFileName("camera.x"), 0, 0, null, null);

			builder.setQuality(D3DRMRENDER_UNLITFLAT);
			
			light = d3drm.createLightRGB(D3DRMLIGHT_DIRECTIONAL, 1.0F, 1.0F, 1.0F);
    	} 
		else if (wparam == MENU_LIGHT_PARALLEL_POINT) 
		{
        	builder.loadFromFileByPos(tg.getFileName("sphere2.x"), 0, 0, null, null);

			builder.setQuality(D3DRMRENDER_UNLITFLAT);
			builder.scale(0.2F, 0.2F, 0.2F);
			light = d3drm.createLightRGB (D3DRMLIGHT_PARALLELPOINT, 
						1.0F, 1.0F, 1.0F);
    	} 
		else if (wparam == MENU_LIGHT_POINT) 
		{
        	builder.loadFromFileByPos(tg.getFileName("sphere2.x"), 0, 0, null, null);

			builder.setQuality(D3DRMRENDER_UNLITFLAT);

			builder.scale( 0.2F, 0.2F, 0.2F);

			light = d3drm.createLightRGB (D3DRMLIGHT_POINT, 
											1.0F, 1.0F, 1.0F);

    	} else if (wparam == MENU_LIGHT_SPOT) 
		{
        	builder.loadFromFileByPos(tg.getFileName("camera.x"), 0, 0, null, null);

			builder.setQuality(D3DRMRENDER_UNLITFLAT);

			light = d3drm.createLightRGB( D3DRMLIGHT_SPOT, 1.0F,1.0F,1.0F);
    	}

		f = d3drm.createFrame(scene);
    	f.setPosition(camera,0.0F,0.0F,10.0F);
    	f.addVisualMeshBuilder(builder);
    	f.addLight(light);
	}

	//////////////////////////////////////////////////////////////////////////
	public void LoadMesh(String file)
   	{
    	Direct3dRMMeshBuilder builder;

		builder = d3drm.createMeshBuilder();
		builder.loadFromFileByPos(tg.getFileName(file), 0, 0, (ILoadTextureCallback)this, null);

		PlaceMesh(builder);
	}

	void LoadFrameHierarchy(String filename)
	{
    	Direct3dRMMeshBuilder builder;
		Direct3dRMFrame f;

		if ( filename == "castle.x" )
		{
			D3dRMBox box = new D3dRMBox();

			f = d3drm.createFrame(scene);
			f.loadFromFileByPos(tg.getFileName(filename), 0, 0, (ILoadTextureCallback)this, null);

			builder = d3drm.createMeshBuilder();
			builder.setPerspective(1);
			builder.addFrame(f);
			builder.getBox(box);

			float maxDim = 0.0F;

			maxDim = box.xMax - box.xMin;
			if (box.yMax - box.yMin > maxDim) 
				maxDim = box.yMax - box.yMin;

			if (box.zMax - box.zMin > maxDim)
				maxDim = box.zMax - box.zMin;

			f.addScale(D3DRMCOMBINE_BEFORE, 16.0F/maxDim, 16.0F/maxDim, 16.0F/maxDim);
			f.setPosition(scene, 0.0F, -1.0F, 5.0F);
		}
		else 
		{
			f = d3drm.createFrame(scene);
			f.loadFromFileByPos(tg.getFileName(filename), 0, 0, (ILoadTextureCallback)this, null);
			ScaleScene(f, false );
		}
	}

	void LoadAnimationSet(String filename)
	{
		Direct3dRMAnimationSet lpAnimSet;
		Direct3dRMFrame f;

		//
		// Create a new parent frame for the animation, load it, and set up 
		// the callback 
		//
		f = d3drm.createFrame(scene);
		lpAnimSet = d3drm.createAnimationSet();

		lpAnimSet.loadFromFileByPos(tg.getFileName(filename), 0, 0, (ILoadTextureCallback)this, null, f);

		ScaleScene(f, false);

		setAnimationCallback(f, lpAnimSet);
	}

	//////////////////////////////////////////////////////////////////////////
	void ScaleScene(Direct3dRMFrame f, boolean castlespecialcase )
	{
  		Direct3dRMMeshBuilder  builder;
		D3dRMBox box = new D3dRMBox();

		float maxDim = 0.0F;

		builder = d3drm.createMeshBuilder();
		builder.addFrame(f);
		builder.getBox(box);

		maxDim = box.xMax - box.xMin;
		if (box.yMax - box.yMin > maxDim) 
			maxDim = box.yMax - box.yMin;

		if (box.zMax - box.zMin > maxDim)
			maxDim = box.zMax - box.zMin;

		if ( castlespecialcase )
		{
			f.addScale(D3DRMCOMBINE_BEFORE, 16.0F/maxDim, 16.0F/maxDim, 16.0F/maxDim);
			f.setPosition(scene, 0.0F, -1.0F, 5.0F);
		}
		else
		{
			f.addScale(D3DRMCOMBINE_BEFORE, 8.0F/maxDim, 8.0F/maxDim, 8.0F/maxDim);
			f.setPosition(scene, 0.0F, 0.0F, 15.0F);
		}
	}

	void setFog( int enable, int mode, float start, float end, float desity )
	{
		scene.setSceneFogEnable(enable);
		if ( enable > 0 )
		{
			scene.setSceneFogMode(mode);
//			scene.setSceneFogParams(start,end,desity);
			scene.setSceneFogParams(start,end,1);
			scene.setSceneFogColor(-1);
			scene.setSceneBackgroundRGB(1.0f,1.0f,1.0f);
		}
		else
		{
			scene.setSceneBackgroundRGB(0.0f,0.0f,0.0f);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	// Place an object in front of the camera.
	//
	void PlaceMesh( Direct3dRMMeshBuilder mesh)
	{
    	Direct3dRMFrame f;

		f = d3drm.createFrame(scene);
		f.addVisualMeshBuilder(mesh);
		f.setPosition(camera, 0.0F, 0.0F, 15.0F);
	}


	//////////////////////////////////////////////////////////////////////////

	static final int DDBD_1 = 0x00004000;
	static final int DDBD_2 = 0x00002000;
	static final int DDBD_4 = 0x00001000;
	static final int DDBD_8 = 0x00000800;
	static final int DDBD_16 = 0x00000400;
	static final int DDBD_24 = 0x00000200;
	static final int DDBD_32 = 0x00000100;
	
	int bppToddbd(int bpp)
	{
    	switch(bpp) 
    	{	
    		case 1:		return DDBD_1;
			case 2:		return DDBD_2;
			case 4:		return DDBD_4;
			case 8:		return DDBD_8;
			case 16:	return DDBD_16;
			case 24:	return DDBD_24;
			case 32:	return DDBD_32;
	    }
    	return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	//
	// Create the device and viewport.
	//
	// uses global this and info
	//
	void CreateDevice()
	{
		_Guid g;

		Dimension s = size();

		//
		// Create a DirectDraw object
		//
		DD = new DirectDraw();

		//
		// The level is used to direct Direct Draw what 
		// window behaviors are allowed, this is used
		// primarly to allow Direct Draw applications
		// to take over the whole screen.  Since 
		// we are security bound in Java this value
		// must allways be set to DDSCL_NORMAL
		//
		DD.setCooperativeLevel(this, DDSCL_NORMAL);

		//
		// Create the D3d device interface associtated with the DD draw object
		//
		D3D = DD.createD3D();

		//
		// Create the primary surface
		//
		DDSurfaceDesc ddsd = new DDSurfaceDesc();
	    ddsd.flags   = DDSD_CAPS;
    	ddsd.ddsCaps = DDSCAPS_PRIMARYSURFACE;
		ddsPrimary	 = DD.createSurface(ddsd);

		//
		// Create and Set the clipper for the primary surface
		//
		ddclipper = DD.createClipper(0);
		ddclipper.setComponent(this);	
		ddsPrimary.setClipper( ddclipper );

		//
		// Create an offscreen rendering surface
		//
	    ddsd.flags   = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    	ddsd.ddsCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = s.width;	
    	ddsd.height  = s.height; 
		ddsOffscreen = DD.createSurface(ddsd);

	    ddsd.flags   = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_ZBUFFERBITDEPTH;
    	ddsd.ddsCaps = DDSCAPS_ZBUFFER | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = s.width;	
    	ddsd.height  = s.height; 
        ddsd.zbufferBitDepth = 16;
		DDSZBuffer	 = DD.createSurface(ddsd);

		ddsOffscreen.addAttachedSurface(DDSZBuffer);

		//
		// This will attach the system palette to the offscreen surface
		//
		try
		{
			DDPal = DD.createPalette(DDPCAPS_8BIT);
			if( DDPal != null)
			{
				ddsPrimary.setPalette(DDPal);
				ddsOffscreen.setPalette(DDPal);
			}
       	}
       	catch(Exception e)
       	{
			// Failed palette probably not in 8-bit mode
       	}

		try
		{
			g = D3D.findDeviceForColorModel(model, 0);
		}
       	catch(Exception e)
       	{
			// Try again just in case we are running on Minidrivers that 
			// don't support MOMO modes 
			g = D3D.findDeviceForColorModel(D3DCOLOR_RGB, 0);
			model = D3DCOLOR_RGB;
       	}

		// 
		// Create the D3D Device object associated 
		// with the offscreen surface
		//
	    D3DDevice = ddsOffscreen.create3DDevice(g);

		dev = d3drm.createDeviceFromD3D(D3D,D3DDevice);

		switch (D3D.systemBpp())
		{
			case 1:
				dev.setShades(4);
				d3drm.setDefaultTextureShades(4);
				break;
				
			case 16:
				dev.setShades(32);
				d3drm.setDefaultTextureColors(64);
				d3drm.setDefaultTextureShades(32);
				dev.setDither(0);
				break;
				
			case 24:
			case 32:
				dev.setShades(256);
				d3drm.setDefaultTextureColors(64);
				d3drm.setDefaultTextureShades(256);
				dev.setDither(0);
				break;
				
			default:
				dev.setDither(0);
		}

		dev.setQuality(D3DRMRENDER_FLAT);
		dev.setTextureQuality( D3DRMTEXTURE_NEAREST );
		
    	CreateScene();

		view = d3drm.createViewport(dev, camera, 0, 0, dev.getWidth(), dev.getHeight());
		view.setBack(5000.0F);
	}

	//////////////////////////////////////////////////////////////////////////
	// Regenerate the device if the color model changes or the window 
	// size changes.
	//
	void RebuildDevice(int model, int width, int height)
	{
		_Guid g;

		//
		// Save off previous device data 
		//
    	int old_dither  = dev.getDither();
	    int old_quality = dev.getQuality();
	   	int old_shades  = dev.getShades();
		int old_texturequailty = dev.getTextureQuality();

		//
		// Make sure we release old devices 
		//
		view = null;
		dev = null;
		DDSZBuffer = null;
		ddsOffscreen = null;
		D3DDevice = null;
		System.gc();

		//
		// Create an offscreen rendering surface
		//
		DDSurfaceDesc ddsd = new DDSurfaceDesc();
	    ddsd.flags   = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    	ddsd.ddsCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = width;	
    	ddsd.height  = height; 
		ddsOffscreen = DD.createSurface(ddsd);

	    ddsd.flags   = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_ZBUFFERBITDEPTH;
    	ddsd.ddsCaps = DDSCAPS_ZBUFFER | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = width;	
    	ddsd.height  = height; 
        ddsd.zbufferBitDepth = 16;
		DDSZBuffer	 = DD.createSurface(ddsd);

		ddsOffscreen.addAttachedSurface(DDSZBuffer);

		try
		{
			ddsOffscreen.setPalette(DDPal);
       	}
       	catch(Exception e)
       	{
			// setpalette failed normal cause display not in 8-bit mode
       	}

		try
		{
			g = D3D.findDeviceForColorModel(model, 0);
		}
       	catch(Exception e)
       	{
			// Try again just in case we are running on DirectX Minidrivers that 
			// dose not support MONO lighting model
			g = D3D.findDeviceForColorModel(D3DCOLOR_RGB, 0);
			model = D3DCOLOR_RGB;
       	}

		// 
		// Create the D3D Device object associated 
		// with the offscreen surface
		//
	    D3DDevice = ddsOffscreen.create3DDevice(g);
		dev = d3drm.createDeviceFromD3D(D3D,D3DDevice);

		//
		// Restore the previous devices values 
		//
    	dev.setDither(old_dither);
	    dev.setQuality(old_quality);
    	dev.setShades(old_shades);
		dev.setTextureQuality( old_texturequailty );

		//
		// Create the new viewport 
		//
	    view = d3drm.createViewport(dev,camera,0,0,width,height);
	    view.setBack(5000.0F);

		//
		// Reset the blt rects in case the view size has changed
		// then start rendering again.
		bltrect.left   = 0;
		bltrect.top    = 0;
		bltrect.right  = width;
		bltrect.bottom = height;
	}

	//////////////////////////////////////////////////////////////////////////
	public Direct3dRMTexture callbackLoadTexture(String name, IUnknown args)
	{
		int ext = name.lastIndexOf(".");

		if (ext != -1) 
		{
			String fileExtension = name.substring(ext);
			fileExtension.toLowerCase();
			if( fileExtension.equals(".ppm") == true || fileExtension.equals(".bmp") == true )
			{
				return d3drm.loadTexture(tg.getFileName(name));
			}
		}
		return null;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void CreateScene()
	{
		Direct3dRMMeshBuilder	builder;

		scene = d3drm.createFrame(null);
		light1     = d3drm.createLightRGB(D3DRMLIGHT_DIRECTIONAL, 1.0F, 1.0F, 1.0F);
		light2     = d3drm.createLightRGB(D3DRMLIGHT_AMBIENT, 0.1F, 0.1F, 0.1F);
		light      = d3drm.createFrame(scene);

		light.setPosition(scene, 2.0F, 2.0F, 5.0F);
		light.setOrientation(scene, -1.0F, -1.0F, 1.0F, 0.0F, 1.0F, 0.0F);
		light.addLight(light1);

    	scene.addLight(light2);

    	builder = d3drm.createMeshBuilder();
		builder.loadFromFileByPos(tg.getFileName("camera.x"), 0, 0, null, null);
		builder.setQuality(D3DRMRENDER_UNLITFLAT);
		light.addVisualMeshBuilder(builder);

		mainframe = d3drm.createFrame(scene);
		mainframe.setRotation(scene, 0.0F, 1.0F, 0.0F, -0.02F);
		mainframe.setPosition(scene, 0.0F, 0.0F, 10.0F);

		builder = d3drm.createMeshBuilder();
		builder.loadFromFileByPos(tg.getFileName("mslogo.x"), 0, 0, (ILoadTextureCallback)this, null);

		builder.setColorRGB(0.8F, 0.8F, 0.8F);
		
		mat = d3drm.createMaterial(10.0F);
		builder.setMaterial(mat);
		
		mainframe.addVisualMeshBuilder(builder);

		camera = d3drm.createFrame(scene);
		camera.setPosition(scene, 0.0F, 0.0F, 0.0F);
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean mouseDown(Event e, int x, int y)
	{
		//
		// Find which object was selected 
		//
       	sel.FindAndSelectVisual(view, x, y);
		last_x = x;
	   	last_y = y;

		//
		// Stop obecjt if it is a left click
		if( (e.modifiers & 4) == 0 )
		{
			//
			// Stop the rotation
			//
			Direct3dRMFrame sFrame = sel.SelectedFrame();
			
			if ( sFrame != null )
	     		sFrame.setRotation(scene, 0.0F, 1.0F, 0.0F, 0.0F);

			return true;
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean mouseDrag(Event e, int x, int y)
	{
		float delta_x, delta_y;
		
		Direct3dRMFrame	sFrame = sel.SelectedFrame();
		if( sFrame != null )
		{
			if( ((e.modifiers & 4) != 0) )
			{
				// right mouse button
    	        D3dVector p1 = new D3dVector();
	            D3dRMVector4d p2 = new D3dRMVector4d();

        	    delta_x = x - last_x;
    	        delta_y = y - last_y;
	            last_x  = x;
            	last_y  = y;
        	    sFrame.getPosition(scene, p1);
    	        view.transform(p2, p1);
	            p2.x += delta_x*p2.w;
            	p2.y += delta_y*p2.w;
        	    view.inverseTransform(p1, p2);
    	        sFrame.setPosition(scene, p1.x, p1.y, p1.z);
			}
			else if( ((e.modifiers & 4)==0) )
			{
				delta_x = x - last_x;
            	delta_y = -(y - last_y);
	            last_x = x;
    	        last_y = y;

        	    double radius = 50;
				double delta_r = Math.sqrt(delta_x * delta_x + delta_y * delta_y);
	            double denom = Math.sqrt(radius * radius + delta_r * delta_r);

    	        if (delta_r != 0 && denom != 0) 
    	        {
					sFrame.setRotation(	camera,  
						(float)(delta_y/delta_r),
            	        (float)(-delta_x/delta_r), 
						0.0F, 
						(float)(delta_r/denom) );
				}
			}
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean keyUp(Event e, int key)
	{
        switch (key)
        {
			case Event.DELETE:
            	sel.DeleteVisual();
				break;
			case Event.PGUP:
			case Event.PGDN:
		    case Event.UP:
			case Event.DOWN:
	        case Event.LEFT:
			case Event.RIGHT:
				camera.setVelocity(scene, 0.0F, 0.0F, 0.0F, 0);
            break;

            case '+':
		    case '-':
				Direct3dRMFrame sFrame = sel.SelectedFrame();
				if (sFrame != null)
					sFrame.setVelocity(scene, 0.0F, 0.0F, 0.0F, 0);
            break;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean keyDown(Event e, int key)
	{
		Direct3dRMFrame       sFrame  = sel.SelectedFrame();
		Direct3dRMMeshBuilder sVisual = sel.SelectedVisual();

		D3dVector dir   = new D3dVector();
		D3dVector up    = new D3dVector();
 		D3dVector right = new D3dVector();

		camera.getOrientation(scene, dir, up);
		d3drm.vectorCrossProduct(right, up, dir);

        up.x    /= 4.0F;
        up.y    /= 4.0F;
        up.z    /= 4.0F;
        right.x /= 4.0F;
        right.y /= 4.0F;
        right.z /= 4.0F;

		switch(key)
		{
			case Event.PGUP:
				camera.setVelocity(scene, dir.x, dir.y, dir.z, 0); 
				break;

			case Event.PGDN:
                camera.setVelocity(scene, -dir.x, -dir.y, -dir.z, 0);
                break;
                 
            case Event.UP:
                camera.setVelocity(scene, up.x, up.y, up.z, 0);
                break;

            case Event.DOWN:
                camera.setVelocity(scene, -up.x, -up.y, -up.z, 0);
                break;

            case Event.RIGHT:
                camera.setVelocity(scene, right.x, right.y, right.z, 0);
                break;

            case Event.LEFT:
                camera.setVelocity(scene, -right.x, -right.y, -right.z, 0);
                break;

            case '+':
				if ( sFrame != null )
	                sFrame.setVelocity(scene, dir.x, dir.y, dir.z, 0);
                break;

            case '-':
				if ( sFrame != null )
	                sFrame.setVelocity(scene, -dir.x, -dir.y, -dir.z, 0);
                break;

            case '/':
				if ( sVisual != null )
				{
					sVisual.scale(0.9F, 0.9F, 0.9F);
		            sel.SelectVisual(sVisual, sFrame);
				}
                break;

            case '*':
				if ( sVisual != null )
				{
					sVisual.scale(1.1F, 1.1F, 1.1F);
		            sel.SelectVisual(sVisual, sFrame);
				}
			    break;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean MenuAction(int key)
	{
		String file;
		switch(key)
		{
			case MENU_LIGHT_DIRECTIONAL:
        	case MENU_LIGHT_PARALLEL_POINT:
        	case MENU_LIGHT_POINT:
	        case MENU_LIGHT_SPOT:
    	        CreateLight(key);
        	    break;
			
	        case MENU_FILE_OPEN:
            	file = OpenNewFile("Open a Mesh file");
             	if (file != null)
              		LoadMesh(file);
             	break;

	        case MENU_FILE_OPEN_ANIMSET:
        	    file = OpenNewFile("Open Animation ...");
            	if (file != null) 
              		LoadAnimationSet(file);
				break;

	        case MENU_FILE_OPEN_FRAME:
        	    file = OpenNewFile("Open Frame ...");
            	if (file != null) 
                	LoadFrameHierarchy(file);
              	break;

	        case MENU_EDIT_CUT:
    	        sel.CutVisual();
        	    break;

        	case MENU_EDIT_COPY:
            	sel.CopyVisual();
            	break;

	        case MENU_EDIT_PASTE:
    	        sel.PasteVisual(scene);
        	    break;

        	case MENU_EDIT_DELETE:
            	sel.DeleteVisual();
            	break;

	        case MENU_QUALITY_LIGHTING:
    	        ToggleLighting();
        	    break;

	        case MENU_QUALITY_POINTS:
    	        SetFillMode(D3DRMFILL_POINTS);
        	    break;

        	case MENU_QUALITY_WIREFRAME:
            	SetFillMode(D3DRMFILL_WIREFRAME);
            	break;

	        case MENU_QUALITY_SOLID:
    	        SetFillMode(D3DRMFILL_SOLID);
        	    break;

        	case MENU_QUALITY_FLAT:
            	SetShadeMode(D3DRMSHADE_FLAT);
            	break;

	        case MENU_QUALITY_GOURAUD:
    	        SetShadeMode(D3DRMSHADE_GOURAUD);
        	    break;

        	case MENU_QUALITY_PHONG:
            	SetShadeMode(D3DRMSHADE_PHONG);
            	break;

	        case MENU_MODEL_MONO:
    	        SetModel(D3DCOLOR_MONO);
        	    break;

        	case MENU_MODEL_RGB:
            	SetModel(D3DCOLOR_RGB);
            	break;

	        case MENU_DITHER:
    	        ToggleDither();
        	    break;

			case MENU_FOG_ENABLE:
				ToggleFog();
				break;

        	case MENU_TEXTURE_FILTERING:
            	ToggleTextureFiltering();
            	break;

			default:
				return false;
        }
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean isbliting()
	{
		return inblit;
	}

	//////////////////////////////////////////////////////////////////////////
	void Render() 
	{
		inblit = true;

		//
		// Actually do the render, 
		// move the scene one tick
		// clear the viewport
		// then render the view
		//
	    scene.move(1.0F);
		view.clear();
		view.render(scene);

		//
		// Blit the Offscreen surface attached to
		// the Viewport to the screen 
		// 
	   	ddsPrimary.blt(bltrect, ddsOffscreen, bltrect, DDBLT_WAIT);

		inblit = false;
	}
}

