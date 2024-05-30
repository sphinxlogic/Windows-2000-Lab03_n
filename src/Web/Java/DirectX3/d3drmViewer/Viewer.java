//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.awt.peer.ComponentPeer;
import java.applet.*;
import com.ms.com.*;
import com.ms.awt.*;
import com.ms.awt.peer.*;
import com.ms.ui.*;
import com.ms.directX.*;
import java.net.URL;
import java.net.MalformedURLException;
import java.io.FilenameFilter;
import java.io.File;


class MenuPanel extends AwtUIHost
{
	ViewerCanvas vCanvas;
	UICheckButton light, dither, textureFilter, enableFog;	
	UIMenuList lightMenu, editMenu, objectMenu, renderMenu, shadeMenu, paletteMenu, fogMenu;
	UIMenuButton lightButton, editButton, objectButton, renderButton, shadeButton, paletteButton, fogButton;
	UIPushButton delete;
	UIRadioButton solid, points, wireframe, flat, gouraud, phong, rgb, ramp;
	UIText cut, copy, paste, fogText, directional, parpoint, point, spot, MSLogo, egg, teapot, sphere, castle;

	UISlider fogSlider;
	UIBand menuBand;

	//////////////////////////////////////////////////////////////////////////
	MenuPanel(boolean Standalone)
	{
		setLayout(new UIFlowLayout(0));

		menuBand = new UIBand();

		light = new UICheckButton("Lighting");
		light.setChecked(true);
		menuBand.add(light);

		lightMenu = new UIMenuList();
		directional = new UIText("Directional");
		parpoint = new UIText("Parallel Point");
		point = new UIText("Point");
		spot = new UIText("Spot");

		lightMenu.add(directional);
		lightMenu.add(parpoint);
		lightMenu.add(point);
		lightMenu.add(spot);

		lightButton = new UIMenuButton("Add Light", 0, lightMenu);

		menuBand.add(lightButton);

		objectMenu = new UIMenuList();

		MSLogo = new UIText("MSLogo");
		egg = new UIText("Egg");
		teapot = new UIText("Teapot");
		sphere = new UIText("Sphere");
		castle = new UIText("Castle");

		objectMenu.add(MSLogo);
		objectMenu.add(egg);
		objectMenu.add(teapot);
		objectMenu.add(sphere);
		objectMenu.add(castle);
		objectButton = new UIMenuButton("Add Model", 0, objectMenu);
		menuBand.add(objectButton);
		
		
		delete = new UIPushButton("Delete Model", UIPushButton.RAISED);
		menuBand.add(delete);

		editMenu = new UIMenuList();

		cut = new UIText("Cut", UIText.LEFT);
		copy = new UIText("Copy", UIText.LEFT);
		paste = new UIText("Paste", UIText.LEFT);

		editMenu.add(cut);
		editMenu.add(copy);
		editMenu.add(paste);

		editButton = new UIMenuButton("Edit", 0, editMenu);

		menuBand.add(editButton);

		
		
		renderMenu = new UIMenuList();

		solid = new UIRadioButton("Solid");
		points = new UIRadioButton("Points");
		wireframe = new UIRadioButton("Wireframe");
		solid.setChecked(true);

		renderMenu.add(solid);
		renderMenu.add(points);
		renderMenu.add(wireframe);

		renderButton = new UIMenuButton("Style", 0, renderMenu);
		menuBand.add(renderButton);

		shadeMenu = new UIMenuList();

		flat = new UIRadioButton("Flat");
		gouraud = new UIRadioButton("Gouraud");
		phong = new UIRadioButton("Phong");
		flat.setChecked(true);

		shadeMenu.add(flat);
		shadeMenu.add(gouraud);
		shadeMenu.add(phong);

		shadeButton = new UIMenuButton("Shading", 0, shadeMenu);
		menuBand.add(shadeButton);

		paletteMenu = new UIMenuList();

		rgb = new UIRadioButton("RGB Mode");
		ramp = new UIRadioButton("Ramp Mode");

		paletteMenu.add(rgb);
		paletteMenu.add(ramp);

		paletteButton = new UIMenuButton("Color Mode", 0, paletteMenu);
		menuBand.add(paletteButton);

		fogMenu = new UIMenuList();
		enableFog = new UICheckButton("Enable Fog");
		enableFog.setChecked(false);
		
		fogSlider = new UISlider();
		fogSlider.setEnabled(false);
		fogSlider.setXPosition(6);

		fogMenu.add(enableFog);
		fogMenu.add(new UILine());
		
		fogText = new UIText("Fog Intensity");
		fogText.setEnabled(false);

		fogMenu.add(fogText);
		fogMenu.add(fogSlider);
		
		fogButton = new UIMenuButton("Fog", 0, fogMenu);
		menuBand.add(fogButton);

		dither = new UICheckButton("Dithering");
		menuBand.add(dither);

		textureFilter = new UICheckButton("Texture Filtering");
		menuBand.add(textureFilter);
		
		add(menuBand);
	}

	//////////////////////////////////////////////////////////////////////////
	public void CheckMenuItem(int id, boolean check  )
	{
		if ( id == vCanvas.MENU_QUALITY_LIGHTING )
		{
			light.setChecked(check);
			lightButton.setEnabled(check);
		}
	
		else if ( id == vCanvas.MENU_QUALITY_POINTS )
		{
			points.setChecked(check);
			wireframe.setChecked(!check);
			solid.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_QUALITY_WIREFRAME )
		{
			wireframe.setChecked(check);
			points.setChecked(!check);
			solid.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_QUALITY_SOLID )
		{
			solid.setChecked(check);
			points.setChecked(!check);
			wireframe.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_QUALITY_FLAT )
		{
			flat.setChecked(check);
			gouraud.setChecked(!check);
			phong.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_QUALITY_GOURAUD )
		{
			gouraud.setChecked(check);
			flat.setChecked(!check);
			phong.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_QUALITY_PHONG )
		{
			phong.setChecked(check);
			flat.setChecked(!check);
			gouraud.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_DITHER )
		{
			dither.setChecked(check);
		}
		else if ( id == vCanvas.MENU_TEXTURE_FILTERING )
		{
			textureFilter.setChecked(check);
		}
		else if ( id == vCanvas.MENU_MODEL_MONO )
		{
			ramp.setChecked(check);
			rgb.setChecked(!check);
		}
		else if ( id == vCanvas.MENU_MODEL_RGB )
		{
			rgb.setChecked(check);
			ramp.setChecked(!check);
		}
		else if (id == vCanvas.MENU_FOG_ENABLE)
		{
			enableFog.setChecked(check);
			fogSlider.setEnabled(check);
			fogText.setEnabled(check);
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	public void attachViewer(ViewerCanvas vCanvas)
	{
		this.vCanvas = vCanvas;
		vCanvas.attachMenu(this);
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean action(Event e, Object arg)
	{
		int id = 0;
		if (arg == directional)
			id = vCanvas.MENU_LIGHT_DIRECTIONAL;
		else if ( arg == parpoint )
        	id = vCanvas.MENU_LIGHT_PARALLEL_POINT;
		else if ( arg == point )
        	id = vCanvas.MENU_LIGHT_POINT;
		else if ( arg == spot )
	        id = vCanvas.MENU_LIGHT_SPOT;
		else if (arg == cut)
			id = vCanvas.MENU_EDIT_CUT;
		else if (arg == copy)
			id = vCanvas.MENU_EDIT_COPY;
		else if (arg == paste)
			id = vCanvas.MENU_EDIT_PASTE;
		else if ( arg == delete )
	       	id = vCanvas.MENU_EDIT_DELETE;
		else if ( arg == objectButton )
	       	id = vCanvas.MENU_FILE_OPEN;
		else if ( arg == light )
			id = vCanvas.MENU_QUALITY_LIGHTING;
		else if ( arg == points )
			id = vCanvas.MENU_QUALITY_POINTS;
		else if ( arg == wireframe )
			id = vCanvas.MENU_QUALITY_WIREFRAME; 		
		else if ( arg == solid )
			id = vCanvas.MENU_QUALITY_SOLID;
		else if ( arg == flat )
			id = vCanvas.MENU_QUALITY_FLAT;
		else if ( arg == gouraud )
			id = vCanvas.MENU_QUALITY_GOURAUD; 
		else if ( arg == phong )
			id = vCanvas.MENU_QUALITY_PHONG;
		else if ( arg == dither )
			id = vCanvas.MENU_DITHER;
		else if ( arg == textureFilter )
			id = vCanvas.MENU_TEXTURE_FILTERING;
		else if ( arg == ramp )
			id = vCanvas.MENU_MODEL_MONO;
		else if ( arg == rgb )
			id = vCanvas.MENU_MODEL_RGB;
		else if ( arg == enableFog )
			id = vCanvas.MENU_FOG_ENABLE;
		else if (arg == fogSlider)
		{
			float x = (float)fogSlider.getXPosition();

			vCanvas.setFog(1, 0, 5.0f, 5.0f + (25.0f * (1.0f-(x/10.0f))), 0.0f);
			
			return true;
		}
		else if (arg == MSLogo)
			vCanvas.LoadMesh("mslogo.x");
		else if (arg == egg)
			vCanvas.LoadMesh("egg.x");
		else if (arg == teapot)
			vCanvas.LoadMesh("teapot.x");
		else if (arg == sphere)
			vCanvas.LoadMesh("sphere2.x");
		else if (arg == castle)
			vCanvas.LoadFrameHierarchy("castle.x");

		return vCanvas.MenuAction(id);
	}
}

public class Viewer extends Applet implements Runnable, DirectXConstants
{
	ViewerFrame		frame;
	ViewerCanvas	ViewerCanvas;
	MenuPanel		menu;
	boolean			Standalone = false;
	boolean			running = true;
	Thread			t; 
	boolean			rebuilddevice;
	int				model;
	int				width;
	int				height;

	////////////////////////////////////////////////////////////////////////////
	public static void main(String args[])
	{
		ViewerFrame frame = new ViewerFrame("Direct3D Retained Mode Sample");
		BorderLayout bl   = new BorderLayout();
		Viewer applet	  = new Viewer();

		//-----------------------------------------------------------------------
		// Must show Frame before we size it so insets() will return valid values
		frame.show();
		frame.setVisible(false);
		frame.setResizable(false);
		frame.setLayout(bl);
		frame.add("Center", applet);

		applet.Standalone = true;
		applet.frame = frame;

		applet.init();

		Dimension d = bl.preferredLayoutSize(frame);

		frame.setSize(d.width, d.height);
		frame.show();

		applet.start();
	}

	//////////////////////////////////////////////////////////////////////////
	public void init()
	{
		BorderLayout bl = new BorderLayout();
		setLayout(bl);

		ViewerCanvas = new ViewerCanvas("Direct 3D Retained Mode for Java", this);
		menu = new MenuPanel(Standalone);
		menu.attachViewer(ViewerCanvas);

		add("Center", ViewerCanvas);
		add("North", menu);

		show();

		Dimension d = bl.preferredLayoutSize(this);
		resize(d.width, d.height);

		requestFocus();
	}

	//////////////////////////////////////////////////////////////////////////
	public String getFileName(String rawFileName)
	{
		String file;
		URL url = null;

		if ( Standalone == false )
			url = getCodeBase();

		if ( url != null )	
		{
			file = url.toString();
			file = file.substring(6);
			file = file.replace('/','\\');

			// This is a check for when running under appeletviewer 
			// it put a '.' at the end of path 
			if ( file.endsWith("\\.") )
			{
				int index = file.lastIndexOf('.');
				file = file.substring(0,index);
			}

			file = file.concat(rawFileName);
		}
		else
			file = new String(rawFileName);

		return file;
	}

	//////////////////////////////////////////////////////////////////////////
	public void start()
	{
		if ( ViewerCanvas != null )
			ViewerCanvas.startDirect();

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
		while(running)
		{
			ViewerCanvas.Render();

			if ( rebuilddevice )
			{
				rebuilddevice = false;
				ViewerCanvas.RebuildDevice(model, width, height);
			}
		}

		ViewerCanvas.mat			= null;
		ViewerCanvas.light			= null;
		ViewerCanvas.light2			= null;
		ViewerCanvas.light1			= null;
		ViewerCanvas.camera			= null;
		ViewerCanvas.scene			= null;
		ViewerCanvas.mainframe		= null;
		ViewerCanvas.view			= null;
		ViewerCanvas.dev			= null;
		ViewerCanvas.D3DDevice		= null;
		ViewerCanvas.D3D			= null;
		ViewerCanvas.DDPal			= null;
		ViewerCanvas.ddclipper		= null;
		ViewerCanvas.DDSZBuffer		= null;
		ViewerCanvas.ddsOffscreen	= null;
		ViewerCanvas.ddsPrimary		= null;
		ViewerCanvas.d3drm			= null;
		ViewerCanvas.DD				= null;
		ViewerCanvas.sel.d3drm		= null;
		ViewerCanvas				= null;
	}
}
