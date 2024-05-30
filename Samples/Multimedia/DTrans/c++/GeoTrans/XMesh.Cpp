///////////////////////////////////////////////////////////////////////////////////
//XMesh.cpp :Module that load the mesh file and initialize it
///////////////////////////////////////////////////////////////////////////////////
#include "globals.h" 


///////////////////////////////////////////////////////////////////////////////////
BOOL OnFileOpen()
/////////////////////////////////////////////////////////////////////////////////// 
{

    static char     szFileName[MAX_STRING_SIZE];
    OPENFILENAME    ofn;

    memset( szFileName, 0, sizeof( szFileName ) );

                           // Initialize the OPENFILENAME structure.
                           memset( &ofn, 0, sizeof( OPENFILENAME ) );
                           ofn.lStructSize      = sizeof( OPENFILENAME );
                           ofn.hwndOwner        = g_hWnd;
                           ofn.lpstrFilter      = "X files {*.x}\0*.x\0All files {*.*}\0*.*\0\0";
                           ofn.lpstrFile        = szFileName;
                           ofn.lpstrInitialDir  = "..\\..\\media\\geometry";
                           ofn.nMaxFile         =  MAX_STRING_SIZE;
                           ofn.Flags            = OFN_FILEMUSTEXIST;
                           ofn.lpstrDefExt      = "x";

                           // Create the open file dialog.
                           if ( GetOpenFileName( &ofn ) )

                           {
                               InitMesh( szFileName );
                           }
                           else {return false;}

	return true;
}


///////////////////////////////////////////////////////////////////////////////////
void InitMesh(LPCTSTR filename)
///////////////////////////////////////////////////////////////////////////////////
{
     
    HRESULT hr;

    // release mesh to be able to create a new one
    g_meshbuilder.Release();
 
    
    hr=g_d3drm3->CreateMeshBuilder( &g_meshbuilder );
    HandleError( hr, "Failed to CreateMeshBuilder in InitMesh()...\n", HE_EXIT, HE_MBOX );

    hr = g_meshbuilder->Load( (void*)filename, NULL, D3DRMLOAD_FROMFILE, NULL, NULL );
    HandleError( hr, "Failed to load x file() in InitMesh()...\n", HE_EXIT, HE_MBOX );

    g_meshscale=ScaleMesh( g_meshbuilder, D3DVALUE(25) );
    g_meshbuilder->SetQuality( g_meshquality );
    g_meshbuilder->SetPerspective( TRUE );
 
 
    // set default environment values
    RestoreDefaults();
 
    strcpy( g_szXFileName, filename );
}

///////////////////////////////////////////////////////////////////////////////////
D3DVALUE ScaleMesh( IDirect3DRMMeshBuilder3*  mesh, D3DVALUE dim)
///////////////////////////////////////////////////////////////////////////////////
//allow scaling the mesh when resizing the window or loading a new mesh
{
    D3DRMBOX    box;

    mesh->GetBox( &box );
    D3DVALUE sizex = box.max.x - box.min.x;
    D3DVALUE sizey = box.max.y - box.min.y;
    D3DVALUE sizez = box.max.z - box.min.z;
    D3DVALUE largedim=D3DVALUE(0);
    if (sizex>largedim)
        largedim=sizex;
    if (sizey>largedim)
        largedim=sizey;
    if (sizez>largedim)
        largedim=sizez;
    D3DVALUE scalefactor = dim/largedim;
    mesh->Scale( scalefactor, scalefactor, scalefactor );
    
    return scalefactor;
}

/////////////////////////////////////////////////////////////////////////////////// 
void RestoreDefaults()
///////////////////////////////////////////////////////////////////////////////////
{
    g_frame->SetOrientation( g_scene,
            D3DVALUE(0), D3DVALUE(0), D3DVALUE(1),
            D3DVALUE(1), D3DVALUE(0), D3DVALUE(0) );
    g_frame->SetRotation( g_scene, 
            D3DVALUE(1), D3DVALUE(0), D3DVALUE(0), 
            D3DVALUE(.1) );
}

///////////////////////////////////////////////////////////////////////////////////
void UpdateFrame(IDirect3DRMFrame3* someframe, void*, D3DVALUE)
///////////////////////////////////////////////////////////////////////////////////
{
    double dlDeltaX;
    double dlDeltaY;
    double dlDeltaR;
    double dlRadius;
    double dlDenom;
    int     iX;
    int     iY;

    if (g_bDrag)
    {   
        
        iX=g_lgMousex;
        iY=g_lgMousey;
        dlDeltaX = iX - g_iLast_x;
        dlDeltaY = iY - g_iLast_y;
        g_iLast_x = iX;
        g_iLast_y = iY;
        
        // calculate rotation angle
        dlDeltaR = sqrt( dlDeltaX * dlDeltaX + dlDeltaY * dlDeltaY );
        dlRadius = 50;
         
        
        dlDenom = sqrt( dlRadius * dlRadius + dlDeltaR * dlDeltaR );

        if (!(dlDeltaR == 0 || dlDenom == 0))
        {
            // rotate the mesh according to the mouse move
            someframe->SetRotation( g_scene,
                    D3DDivide(D3DVAL((float)-dlDeltaY), D3DVAL((float)dlDeltaR)),
                    D3DDivide(D3DVAL((float)-dlDeltaX), D3DVAL((float)dlDeltaR)),
                    D3DVAL(0.0),
                    D3DDivide(D3DVAL((float)dlDeltaR), D3DVAL((float)dlDenom)));
        }
    }

    if (g_bEndDrag)
    {
        g_bDrag    =FALSE;
        g_bEndDrag =FALSE;
    }
}

///////////////////////////////////////////////////////////////////////////////////
void OnMouseMove( UINT state, POINT point )
///////////////////////////////////////////////////////////////////////////////////
{
    g_uiMousestate = state;
    g_lgMousex = point.x;
    g_lgMousey = point.y;
}

///////////////////////////////////////////////////////////////////////////////////
void OnLButtonDown() 
///////////////////////////////////////////////////////////////////////////////////
{
    if (!g_bDrag)
    {
        g_bDrag=TRUE;
        g_iLast_x = g_lgMousex;
        g_iLast_y = g_lgMousey;
        SetCapture( g_hWnd );
        ShowCursor( FALSE );
    }   
     
}
///////////////////////////////////////////////////////////////////////////////////
void OnLButtonUp() 
///////////////////////////////////////////////////////////////////////////////////
{
    if (g_bDrag)
    {
        g_bEndDrag=TRUE;
        ReleaseCapture();
        ShowCursor(TRUE);
    }
    if((g_d3drm3)&&(g_meshbuilder))
    {
		g_d3drm3->Tick( D3DVALUE(1) ); 
	}
     
}



 