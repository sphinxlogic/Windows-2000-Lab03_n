///////////////////////////////////////////////////////////////////////////////////
//PrepStage.cpp : Module that set the D3DRM environement variables
//Sets the global parameters and framework for the transform.  (These modules largely consist 
//of D3DRM-specific setup code.)
//- CreateTheD3DRM() initializes d3drm and d3drm3
//- CreateDevice() sets parameters according to the display configuration 
//- CreateScene() creates the frame, camera, light, and viewport
//
///////////////////////////////////////////////////////////////////////////////////
#include "globals.h"

/////////////////////////////////////////////////////////////////////////////////// 
void InitGlobalvars()
///////////////////////////////////////////////////////////////////////////////////
//  
{
    g_colormodel=D3DCOLOR_MONO;
    g_pOutMesh  =NULL;
 
}

///////////////////////////////////////////////////////////////////////////////////
bool CreateTheD3DRM()
///////////////////////////////////////////////////////////////////////////////////
{
    
    HRESULT	hr;
    DWORD	dwOptions;

    // Create the D3DRM object
    hr = Direct3DRMCreate( &g_d3drm );
    HandleError( hr, "Failed to Create D3drm in CreateTheD3DRM()...\n", HE_EXIT, HE_MBOX );
    
	// QI for D3dRM3 you need D3DRM6 to make this works
    hr= g_d3drm->QueryInterface( IID_IDirect3DRM3, (LPVOID*)&g_d3drm3 );
	HandleError( hr ,"Unable to use 3D transforms.  You don't have a required version of D3D-RM installed (version 6). \n Consult the DirectTransform release notes for details.\n"
				, HE_EXIT, HE_MBOX );
	
	// Setting right handed option
    dwOptions &= ~D3DRMOPTIONS_LEFTHANDED;  
    dwOptions |= D3DRMOPTIONS_RIGHTHANDED;
    if(SUCCEEDED(hr))
	{
		g_d3drm3->SetOptions( dwOptions );
		return true;
	}else{return false;}
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////////
void CreateDevice(void)
///////////////////////////////////////////////////////////////////////////////////
{
    HRESULT     hr;
    RECT        rect;
    HDC         hDC; 
    int         iBpp;

    // Release clipper to be able to recreate it
    g_clipper.Release();
 
    hr = DirectDrawCreateClipper( 0, &g_clipper, 0 );
    HandleError( hr,"Failed to Create Clipper in CreateDevice()...\n", HE_EXIT, HE_MBOX );
     
    hr = g_clipper->SetHWnd( 0, g_hWnd );
    HandleError( hr, "Failed to SetHWnd() in CreateDevice()...\n", HE_EXIT, HE_MBOX );
   
    GetClientRect( g_hWnd, &rect );
    
    // Release device to be able to recreate it
     g_device.Release();
     hr = g_d3drm3->CreateDeviceFromClipper( g_clipper, NULL, 
            rect.right, rect.bottom, 
            &g_device );
    HandleError( hr, "Failed to Create device in CreateDevice()...\n", HE_EXIT, HE_MBOX );
    
	g_device->SetQuality( D3DRMRENDER_GOURAUD );
	
	// get the pixel depth of the screen
    hDC = GetDC( g_hWnd );
    iBpp = GetDeviceCaps( hDC, BITSPIXEL );
    ReleaseDC( g_hWnd, hDC );
    
    // set the device properties according to the screen bit depth .
    switch ( iBpp )
    {
    case 8:
        // add handler here if you need to
        break;
    case 16:
        g_device->SetShades( 32 );
        g_d3drm3->SetDefaultTextureColors( 64 );
        g_d3drm3->SetDefaultTextureShades( 32 );
        g_device->SetDither( FALSE );
        break;
    case 24:
    case 32:
        g_device->SetShades( 256 );
        g_d3drm3->SetDefaultTextureColors( 64 );
        g_d3drm3->SetDefaultTextureShades( 256 );
        g_device->SetDither( FALSE );
        break;
    }
    
    // release scene to be able to recreate it
    g_scene.Release();
 
   // Create a scene and add it to the frame
    hr= g_d3drm3->CreateFrame( 0, &g_scene );
    HandleError( hr, "Failed to Create scene in CreateDevice()...\n", HE_EXIT, HE_MBOX );

}

/////////////////////////////////////////////////////////////////////////////////// 
COLORREF D3DCOLOR_2_COLORREF(D3DCOLOR d3dclr)
///////////////////////////////////////////////////////////////////////////////////
//
//convert d3d color to a window colorref format
//
{
    D3DVALUE red=D3DVALUE(255)*D3DRMColorGetRed(d3dclr);
    D3DVALUE green=D3DVALUE(255)*D3DRMColorGetGreen( d3dclr );
    D3DVALUE blue=D3DVALUE(255)*D3DRMColorGetBlue( d3dclr );
    return RGB((int)red,(int)green,(int)blue);
}

///////////////////////////////////////////////////////////////////////////////////
void InitSceneVars()
///////////////////////////////////////////////////////////////////////////////////
{

    g_meshquality   =D3DRMRENDER_GOURAUD;
    g_meshcolor     =D3DRGB(1,1,1);
    g_meshscale     =D3DVALUE(1);
    g_iLast_x       =g_iLast_y=0;
     
     
}

/////////////////////////////////////////////////////////////////////////////////// 
void CreateScene()
///////////////////////////////////////////////////////////////////////////////////
//
//create the 3D scene 
//
{
    CComPtr<IDirect3DRMFrame3> lightframe;
    CComPtr<IDirect3DRMLight>  light;
     
    HRESULT hr;

    hr=g_scene->SetSceneBackgroundRGB( D3DVALUE(.2), D3DVALUE(.2), D3DVALUE(.2) );  
    HandleError( hr, "Failed to SetSceneBackGround in CreateScene()...\n", HE_EXIT, HE_MBOX );
    
    // create the frame that we will attach the mesh to
    g_frame.Release();
     
    // create the frame 
    hr=g_d3drm3->CreateFrame( g_scene, &g_frame );
    HandleError( hr, "Failed to CreateFrame() in CreateScene()...\n", HE_EXIT, HE_MBOX );

    hr= g_frame->AddMoveCallback( UpdateFrame, NULL, NULL );
    HandleError( hr, "Failed to update frame in CreateScene()...\n", HE_EXIT, HE_MBOX );
 
    // create a light and position it
 
    hr=g_d3drm3->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, D3DVALUE(0.9),D3DVALUE(0.9), 
                                D3DVALUE(0.9), &light);
    HandleError( hr, "Failed to CreateLightRGB in CreateScene()...\n", HE_EXIT, HE_MBOX );

    hr=g_d3drm3->CreateFrame( g_scene, &lightframe );
    HandleError( hr, "Failed to CreateFrame() in CreateScene()...\n", HE_EXIT, HE_MBOX );

    hr=lightframe->SetOrientation(g_scene, 
            D3DVALUE(0), D3DVALUE(-1), D3DVALUE(1),
            D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
    HandleError( hr, "Failed to SetOrientation in CreateScene()...\n", HE_EXIT, HE_MBOX );

    hr=lightframe->SetPosition( g_scene, D3DVALUE(0), D3DVALUE(10), D3DVALUE(-30) );
    HandleError( hr, "Failed to SetPosition in CreateScene()...\n", HE_EXIT, HE_MBOX );
    
    // add light to th scene
    hr=lightframe->AddLight( light );
    HandleError( hr,"Failed to AddLight in CreateScene()...\n", HE_EXIT, HE_MBOX );
 
     
    // create a camera and position it
    g_camera.Release();
         
    hr= g_d3drm3->CreateFrame( g_scene, &g_camera );
    HandleError( hr,"Failed to create camera in CreateScene()...\n", HE_EXIT, HE_MBOX );
    
    hr=g_camera->SetPosition( g_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(-50) );
    HandleError( hr, "Failed to set position in CreateScene()...\n", HE_EXIT, HE_MBOX); 

    // create the viewport
     g_viewport.Release();
     
    if(g_device)
    {   hr= g_d3drm3->CreateViewport( g_device, g_camera, 0, 0,  g_device->GetWidth(), 
                                g_device->GetHeight(), &g_viewport );
    HandleError( hr, "Failed to create viewport in CreateScene()...\n", HE_EXIT, HE_MBOX );
    }
     
     
}

