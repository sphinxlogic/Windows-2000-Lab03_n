// 
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import com.ms.com.*;
import com.ms.directX.*;

public class FlipCubeCanvas extends Canvas implements DirectXConstants
{
	// Private members 
    Rect src = new Rect();			
	Rect dst = new Rect();

	// Direct Draw Objects
	DirectDraw				DD;					// DirectDraw object
	DirectDrawSurface		DDSPrimary;			// DirectDraw primary surface
	DirectDrawClipper		DDClipper;			// Clipper for primary surface
	DirectDrawSurface		DDSOffscreen;		// Offscreen rendering surface 
	DirectDrawPalette		DDPal;				// DirectDraw palette


	// Direct 3D Objects
	Direct3d				D3D;
	Direct3dDevice			D3DDevice;
	Direct3dExecuteBuffer	D3DExBuf;
	Direct3dViewport		D3DView;
	Direct3dMaterial		BackgroundMaterial;
	D3dExecuteData			d3dExData;
	D3dRect					clearrect = new D3dRect();
	
	boolean					bScreenDirty;
	int						model;
	int						hardware;

	float D[] = new float[16];

	//////////////////////////////////////////////////////////////////////////
	public void paint(Graphics g)
	{
		bScreenDirty = true;
	}

	//////////////////////////////////////////////////////////////////////////
	public Dimension minimumSize() 
	{
		return new Dimension(256,256);
	}

	//////////////////////////////////////////////////////////////////////////
	public Dimension maximumSize() 
	{
		return new Dimension(256,256);
	}

	//////////////////////////////////////////////////////////////////////////
	public Dimension preferredSize() 
	{
		return new Dimension(256,256);
	}

	//////////////////////////////////////////////////////////////////////////
	public FlipCubeCanvas()
	{
		super();

	    src        = new Rect();
	    dst		   = new Rect();

		dst.left   = 0;
		dst.top    = 0;
		dst.right  = 256;
		dst.bottom = 256;

		src.left   = 0;
		src.top    = 0;
		src.right  = 256;
		src.bottom = 256;
	}

	int NumVertices = 24;
	D3dLVertex CubeVertices[] = {
		new D3dLVertex (-1.0f, 1.0f, 1.0f, 0x0000ff00, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f, 1.0f, 1.0f, 0x0000ff00, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f, 1.0f,-1.0f, 0x0000ff00, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f, 1.0f,-1.0f, 0x0000ff00, 0, 0.0f, 0.0f),

		new D3dLVertex ( 1.0f, 1.0f,-1.0f, 0x000000ff, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f,-1.0f,-1.0f, 0x000000ff, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f,-1.0f,-1.0f, 0x000000ff, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f, 1.0f,-1.0f, 0x000000ff, 0, 0.0f, 0.0f),
			   
		new D3dLVertex ( 1.0f, 1.0f, 1.0f, 0x00ff0000, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f,-1.0f, 1.0f, 0x00ff0000, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f,-1.0f,-1.0f, 0x00ff0000, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f, 1.0f,-1.0f, 0x00ff0000, 0, 0.0f, 0.0f),

		new D3dLVertex (-1.0f, 1.0f, 1.0f, 0x00ff00ff, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f,-1.0f, 1.0f, 0x00ff00ff, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f,-1.0f, 1.0f, 0x00ff00ff, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f, 1.0f, 1.0f, 0x00ff00ff, 0, 0.0f, 0.0f),

		new D3dLVertex (-1.0f,-1.0f,-1.0f, 0x0000ffff, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f,-1.0f, 1.0f, 0x0000ffff, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f, 1.0f, 1.0f, 0x0000ffff, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f, 1.0f,-1.0f, 0x0000ffff, 0, 0.0f, 0.0f),
  
		new D3dLVertex ( 1.0f,-1.0f,-1.0f, 0x00ffff00, 0, 0.0f, 0.0f),
		new D3dLVertex ( 1.0f,-1.0f, 1.0f, 0x00ffff00, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f,-1.0f, 1.0f, 0x00ffff00, 0, 0.0f, 0.0f),
		new D3dLVertex (-1.0f,-1.0f,-1.0f, 0x00ffff00, 0, 0.0f, 0.0f)
	};

	//
	// Defines an array of triangle objects
	//
	int NumTri = 12;
	D3dTriangle CubeTri[] = {
		new D3dTriangle ((short)0,  (short)1,  (short)2,  D3DTRIFLAG_EDGEENABLETRIANGLE),
		new D3dTriangle ((short)0,  (short)2,  (short)3,  D3DTRIFLAG_EDGEENABLETRIANGLE),
   		new D3dTriangle ((short)4,  (short)5,  (short)6,  D3DTRIFLAG_EDGEENABLETRIANGLE),  
		new D3dTriangle ((short)4,  (short)6,  (short)7,  D3DTRIFLAG_EDGEENABLETRIANGLE),
   		new D3dTriangle ((short)8,  (short)9,  (short)10, D3DTRIFLAG_EDGEENABLETRIANGLE), 
		new D3dTriangle ((short)8,  (short)10, (short)11, D3DTRIFLAG_EDGEENABLETRIANGLE),
  		new D3dTriangle ((short)12, (short)13, (short)14, D3DTRIFLAG_EDGEENABLETRIANGLE), 
		new D3dTriangle ((short)12, (short)14, (short)15, D3DTRIFLAG_EDGEENABLETRIANGLE),
  		new D3dTriangle ((short)16, (short)17, (short)18, D3DTRIFLAG_EDGEENABLETRIANGLE),
		new D3dTriangle ((short)16, (short)18, (short)19, D3DTRIFLAG_EDGEENABLETRIANGLE),
  		new D3dTriangle ((short)20, (short)21, (short)22, D3DTRIFLAG_EDGEENABLETRIANGLE),
		new D3dTriangle ((short)20, (short)22, (short)23, D3DTRIFLAG_EDGEENABLETRIANGLE),
	};

	int ViewHandle;
	int ProjHandle;
	int WorldHandle;

	float World[] = { 1.0f, 0.0f, 0.0f, 0.0f, 
				  					 0.0f, 1.0f, 0.0f, 0.0f, 
									 0.0f, 0.0f, 1.0f, 0.0f, 
									 0.0f, 0.0f, 0.0f, 1.0f };

	float Proj[] = { 2.0f, 0.0f, 0.0f, 0.0f, 
						    	     0.0f, 2.0f, 0.0f, 0.0f, 
									 0.0f, 0.0f, 1.0f, 1.0f, 
									 0.0f, 0.0f,-1.0f, 0.0f };

	float View[] = { 1.0f, 0.0f, 0.0f,  0.0f, 
									 0.0f, 1.0f, 0.0f,  0.0f, 
									 0.0f, 0.0f, 1.0f,  0.0f, 
									 0.0f, 0.0f, 10.0f, 1.0f };

	float Spin[] = { 0.994139f, -0.0283309f, 0.104333f, 0.0f, 
				     0.0348344f, 0.997527f, -0.0610485f,0.0f, 
				    -0.102346f,  0.0643251f, 0.992667f, 0.0f, 
				     0.0f,       0.0f,       0.0f,      1.0f };

	void InitDDraw()
	{
		Guid g;

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
		// Create the primary surface
		//
		DDSurfaceDesc ddsd = new DDSurfaceDesc();
	    ddsd.flags = DDSD_CAPS;
    	ddsd.ddsCaps = DDSCAPS_PRIMARYSURFACE;
		DDSPrimary = DD.createSurface(ddsd);

		//
		// Create and Set the clipper for the primary surface
		//
		DDClipper = DD.createClipper(0);
		// since we are not using any other components just clip to 
		// the windows, and offest it from the upper left hand 
		// cornet of the display
		DDClipper.setComponent(DDCOOPERATIVE_OFFSETTOCOMPONENT,this);	
		DDSPrimary.setClipper( DDClipper );

		//
		// Create a blank palette, then fill it with 
		// system palette color entries
		//
		DDPal = DD.createPalette(DDPCAPS_8BIT, (byte[])null);
		if( DDPal != null)
		{
    		// It will throw an execption if running in a 
			// non-paletized video mode.
           	try
           	{
	        	DDSPrimary.setPalette(DDPal);
           	}
           	catch(Exception e)
           	{
          	}
		}
	}

	void InitD3D()
	{
		//
		// Setup application info object
		//
		model = D3DCOLOR_RGB;

		// NOTE:
		// If you have 3D hardware uncomment the next line and 
		// make sure you uncomment the create surface line bellow
		// to create the surface in hardware
		//
//		hardware = 1;
		hardware = 0;

		//
		// Create a Direct 3D Object 
		//
		D3D = DD.createD3D();

		//
		// Create an offscreen rendering surface
		//
		DDSurfaceDesc ddsd = new DDSurfaceDesc();


	    ddsd.flags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
//    	ddsd.ddsCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
    	ddsd.ddsCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    	ddsd.width   = 256;	
    	ddsd.height  = 256; 
		DDSOffscreen = DD.createSurface(ddsd);
		if( DDPal != null)
		{
			try
			{
        		DDSOffscreen.setPalette(DDPal);
           	}
           	catch(Exception e)
           	{
          	}
		}

		//
		// Clear the surface
		//
	   	DDSOffscreen.bltColorFill(dst, 0);

		//
		// Find the Device's Guid for a device type specified by 
		// application info object
		//
		_Guid g = D3D.findDeviceForColorModel(model, hardware );

		// 
		// Create the D3D Device object associated 
		// with the offscreen surface
		//
	    D3DDevice = DDSOffscreen.create3DDevice(g);

		//
	    // Create the D3D viewport object and 
		// attach it to the device
		//
		D3DView = D3D.createViewport();	
	    D3DDevice.addViewport(D3DView);

		//
		// Descirbe to Veiwport parameters and 
		// set it into the Viewport
		//

		D3dViewportDesc viewData = new D3dViewportDesc();
	    viewData.x		= 0;
		viewData.y		= 0;
	    viewData.width	= 256;
	    viewData.height	= 256;
	    viewData.scaleX	= viewData.width  / 2.0f;
	    viewData.scaleY	= viewData.height / 2.0f;
	    viewData.maxX   = viewData.width  / (2.0f * viewData.scaleX);
		viewData.maxY   = viewData.height / (2.0f * viewData.scaleY);
	    viewData.minZ	= 0.0f;	
	    viewData.maxZ	= 0.0f;

	    D3DView.setViewport(viewData);

		//
		// Set a background Material 
		//
		BackgroundMaterial = D3D.createMaterial();
		D3dMaterialDesc MaterialDesc = new D3dMaterialDesc();
	    MaterialDesc.rampSize = 1;
		BackgroundMaterial.setMaterial(MaterialDesc);


		int BackgroundHandle; 
		BackgroundHandle = BackgroundMaterial.getHandle(D3DDevice);
		D3DView.setBackground(BackgroundHandle);
	}

	void InitExecuteBuffer()
	{					   
		int bufferindex;
		int vertexoffset;
		int instructionoffset;

		D3dExecuteBufferDesc debDesc = new D3dExecuteBufferDesc();
		debDesc.flags = D3DDEB_BUFSIZE;
		debDesc.bufferSize = 64000;	

	    D3DExBuf = D3DDevice.createExecuteBuffer(debDesc);
		d3dExData = new D3dExecuteData();

		ViewHandle  = D3DDevice.createMatrix();
		ProjHandle  = D3DDevice.createMatrix();
		WorldHandle = D3DDevice.createMatrix();

		D3DDevice.setMatrix(ViewHandle,  View);
		D3DDevice.setMatrix(ProjHandle,  Proj);
		D3DDevice.setMatrix(WorldHandle, World);

		D3DExBuf.lock(debDesc);
										
		bufferindex = 0;
 		bufferindex += D3DExBuf.stateTransForm(3,bufferindex);
		bufferindex += D3DExBuf.stateTransFormData(D3DTRANSFORMSTATE_PROJECTION,  ProjHandle,  bufferindex);
		bufferindex += D3DExBuf.stateTransFormData(D3DTRANSFORMSTATE_VIEW,		  ViewHandle,  bufferindex);
		bufferindex += D3DExBuf.stateTransFormData(D3DTRANSFORMSTATE_WORLD,       WorldHandle, bufferindex);
		bufferindex += D3DExBuf.stateRender(1,bufferindex);
		bufferindex += D3DExBuf.stateRenderData(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT,bufferindex);
		bufferindex += D3DExBuf.exit(bufferindex);

		D3DExBuf.unlock();

	    d3dExData.vertexOffset      = 0;
		d3dExData.vertexCount       = 0;
		d3dExData.instructionOffset = 0;
		d3dExData.instructionLength = bufferindex*4;
		D3DExBuf.setExecuteData(d3dExData);

	    D3DDevice.beginScene();
	    D3DDevice.execute(D3DExBuf,D3DView,D3DEXECUTE_UNCLIPPED);
	    D3DDevice.endScene();

		D3DExBuf.lock(debDesc);

		bufferindex = 0;
		vertexoffset = bufferindex;	
		for ( int i = 0; i < NumVertices; i++)
			bufferindex += D3DExBuf.addLVertexData(CubeVertices[i], bufferindex);

		instructionoffset = bufferindex;

		bufferindex += D3DExBuf.setStatus(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 256, 256, 0, 0, bufferindex);

 		bufferindex += D3DExBuf.stateRender(2,bufferindex);
		bufferindex += D3DExBuf.stateRenderData(D3DRENDERSTATE_FILLMODE,  D3DFILL_SOLID, bufferindex);
		bufferindex += D3DExBuf.stateRenderData(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, bufferindex);

		bufferindex += D3DExBuf.processVertices(6,bufferindex);
	    for ( int i = 0; i < 6; i++) 
	      bufferindex += D3DExBuf.processVerticesData(D3DPROCESSVERTICES_TRANSFORM, i*4, i*4, 4, bufferindex);

	    bufferindex += D3DExBuf.triangleList(NumTri, bufferindex);
		for ( int i = 0; i < NumTri; i++) 
	       bufferindex += D3DExBuf.triangleListData(CubeTri[i], bufferindex);

		bufferindex += D3DExBuf.exit(bufferindex);

		D3DExBuf.unlock();

	    d3dExData.vertexOffset      = vertexoffset*4;
		d3dExData.vertexCount       = NumVertices;
		d3dExData.instructionOffset = instructionoffset*4;
		d3dExData.instructionLength = (bufferindex - instructionoffset)*4;

		D3DExBuf.setExecuteData(d3dExData);
	}

	//////////////////////////////////////////////////////////////////////////
	public void updateframe()
	{
		try 
		{
			//
			// Set the new rotation matrix
			//
			MultiplyD3dMatrix(World, Spin, World);
			D3DDevice.setMatrix(WorldHandle, World);
			
			//
			// Render the object 
			// 
			D3DDevice.beginScene();
			D3DDevice.execute(D3DExBuf,D3DView,D3DEXECUTE_CLIPPED);
			D3DDevice.endScene();

			//
			// Retreive how much of the screen is dirty
			//
			D3DExBuf.getExecuteData(d3dExData);

			//
			// Determine how much of the screen has
			// been invaidated by the render or a repaint
			//
			if ( bScreenDirty == false )
			{
				//
				// Check if the last src rect has
				// grown any larger than the 
				// extents returned by Direct3d
				//
				if ( src.left > d3dExData.x1 )
					src.left   = d3dExData.x1;
				if ( src.top > d3dExData.y1 )
					src.top    = d3dExData.y1;
				if ( src.right < d3dExData.x2 )
			    	src.right  = d3dExData.x2;
				if ( src.bottom < d3dExData.y2 )
					src.bottom = d3dExData.y2;
			}
			else
			{
				src.left   = 0;
				src.top    = 0;
				src.right  = 255;
				src.bottom = 255;
			}

			dst.left   = src.left;
			dst.top    = src.top;
		    dst.right  = src.right;
			dst.bottom = src.bottom;

			//
			// Blit the Offscreen surface attached to
			// the Viewport to the screen 
			// 
	   		DDSPrimary.blt(dst, DDSOffscreen, src, DDBLT_WAIT);

			//
			// Blt has been complete this will be set to true
			// only during init or when a paint is nessary 
			//
			bScreenDirty = false;		

			//
			// Clear the viewport
			//
			clearrect.x1 = d3dExData.x1;
			clearrect.y1 = d3dExData.y1;
		    clearrect.x2 = d3dExData.x2;
			clearrect.y2 = d3dExData.y2;

			D3DView.clear( clearrect, D3DCLEAR_TARGET);
		} 
		catch (java.awt.IllegalComponentStateException e) {
			// this can happen when the applet is being shutdown and the windows
			// has been destroyed, yet my thread may be still running.
		}
		catch(Exception e) 
		{
			System.out.println("D3D Rendering Exception: "+e);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void MultiplyD3dMatrix(float Dst[], float Src1[], float Src2[])
	{
		int i, r, c;

	    for (r = 0; r < 4; r++) 
		{
		    for (c = 0; c < 4; c++) 
			{
			    D[(r*4)+c] = 0.0f;
				for (i = 0; i < 4; i++)
					D[(r*4)+c] += Src1[(r*4)+i] * Src2[(i*4)+c];
	        }
		}

		for (i = 0; i < 16; i++ )
			Dst[i] = D[i];
	}
}