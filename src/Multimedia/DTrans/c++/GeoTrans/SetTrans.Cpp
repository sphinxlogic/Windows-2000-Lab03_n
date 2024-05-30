///////////////////////////////////////////////////////////////////////////////////
// SetTrans.cpp : module that display the loaded mesh and execute the transform
//- CreateTheTansform() creates the transform factory and associates it with d3drm.  
//  The transform factory is then used to create the transform.
//- LoadTrans() initializes the output mesh and recreates it with CreateMeshBuilder().
//  IDXTransform::Setup() is called to associate the input mesh with the output mesh.
//- Pickatrans() selects between the Ruffle and Explode transforms.
//- RunTrans() executes the actual transform.
//
///////////////////////////////////////////////////////////////////////////////////

#include "globals.h"


///////////////////////////////////////////////////////////////////////////////////
void RunTrans()
///////////////////////////////////////////////////////////////////////////////////
{
    HRESULT hr;
    float i;
    
    if(!g_cpEffect)
        return;
    // run the Execute function with a loop, there's another way to be done,
    // with g_cpEffect->GetDuration...(see the WipeDlg Sample for this method )
    // the loop is used here just for the sake of simplicity .

    for (i=0.0f;i<=1.0;i+=0.05f)
        {
            hr = g_cpEffect->put_Progress( i );
            hr  =g_pSomeTrans->Execute( NULL, NULL, NULL );
            HandleError( hr, "Failed to Execute transform in RunTrans()...\n", HE_NO_EXIT, HE_DEBUG );
            hr = g_viewport->Clear(D3DRMCLEAR_ALL);
            hr = g_viewport->Render(g_scene);
            hr = g_device->Update();
            
        }

     
}

///////////////////////////////////////////////////////////////////////////////////
HRESULT LoadTrans()
///////////////////////////////////////////////////////////////////////////////////
// Setup  the input and output mesh 
//
{

    IUnknown *pMeshInUK=NULL;
    IUnknown *pMeshOutUK=NULL; 
    HRESULT hr;

    // Release the output mesh to be able to recreate it 
    if(g_pOutMesh)
    {
        hr=g_pOutMesh->Empty( 0 );
        hr=g_pOutMesh->Release();
        g_pOutMesh=NULL;
    }
    

    hr=g_d3drm3->CreateMeshBuilder( &g_pOutMesh );
    HandleError( hr, "Failed to create ouput mesh...\n", HE_EXIT, HE_MBOX );
    
    g_pOutMesh->SetQuality( g_meshquality );
    g_pOutMesh->SetPerspective( TRUE );
    g_frame->AddVisual( g_pOutMesh );
    

    pMeshOutUK = (IUnknown *)g_pOutMesh;
    pMeshInUK  = (IUnknown *)g_meshbuilder;
     
    // release effect to recreate it
    g_cpEffect.Release();
  
 
    hr = g_pSomeTrans->QueryInterface( IID_IDXEffect, (void**) &g_cpEffect );
    HandleError( hr, "Failed to QI IDXEffects in LoadTrans()...\n", HE_EXIT, HE_MBOX );
    
    // Setup the output and input meshes
    hr=g_pSomeTrans->Setup( &pMeshInUK, 1, &pMeshOutUK, 1, 0 );
    HandleError( hr, "Failed to Setup transform in LoadTrans()...\n", HE_EXIT, HE_MBOX );

    hr = g_viewport->Clear( D3DRMCLEAR_ALL );
    hr = g_viewport->Render( g_scene );
    hr = g_device->Update();
 

    return hr;
}

/////////////////////////////////////////////////////////////////////////////////// 
void CreateTheTransform()
///////////////////////////////////////////////////////////////////////////////////
// Prepare to initialize the transform by creating the surface factory
//
{
    HRESULT                         hr;
    
    
    // create the transform factory
    hr=CoCreateInstance( CLSID_DXTransformFactory, NULL,
                 CLSCTX_INPROC, IID_IDXTransformFactory,
                 (void **)&g_pTransFact );
    
    HandleError( hr, "Failed to CoCreateInstane() for the transform factory in CreateTheTransform()...\n", HE_EXIT, HE_MBOX );
    
    // create the direct draw factory
    hr = CoCreateInstance( CLSID_DirectDrawFactory, NULL, CLSCTX_INPROC,
                            IID_IDirectDrawFactory, (void **)&g_pDDrawFact );
    
    HandleError( hr, "Failed to CoCreateinstance()  for DDRawFact in CreateTheTransform()...\n", HE_EXIT, HE_MBOX );

    hr = g_pDDrawFact->CreateDirectDraw( NULL, g_hWnd, DDSCL_NORMAL, 0, NULL, &g_pDDraw );
 
    HandleError( hr, "Failed to CreateDirectDraw() in CreateTheTransform()...\n", HE_EXIT, HE_MBOX ); 
      
    // set the ddraw service
    hr = g_pTransFact->SetService( SID_SDirectDraw, g_pDDraw, FALSE );
    HandleError( hr, "Failed to SetService in CreateTheTransform()...\n", HE_EXIT, HE_MBOX );
 
    hr = g_pTransFact->SetService( SID_SDirect3DRM, g_d3drm3, FALSE );
    HandleError(hr, "Failed to SetService() in CreateTheTransform()...\n", HE_EXIT, HE_MBOX );
 

    // Create the default transform 
    hr=g_pTransFact->CreateTransform( NULL, 0, NULL, 0,
                                     NULL, NULL, CLSID_Explode,
                                     IID_IDXTransform, (void **)&g_pSomeTrans );
    HandleError( hr, "Failed to CreateTransform() in CreateTheTransform()...\n", HE_EXIT, HE_MBOX );
    return;
}

///////////////////////////////////////////////////////////////////////////////////
void PickaTrans(int CaseID)
///////////////////////////////////////////////////////////////////////////////////
// allow selection of different 3d transform
//
{
    HRESULT hr;

    if(g_pTransFact)
    {
        switch(CaseID)
        {
            case 1 :
                g_pSomeTrans.Release();
    
                // Create the transform 
                hr=g_pTransFact->CreateTransform( NULL, 0, NULL, 0,
                                                 NULL, NULL, CLSID_Explode,
                                                 IID_IDXTransform, (void **)&g_pSomeTrans );

                HandleError( hr, "Failed to CreateTransform(1) in PickaTrans()...\n", HE_EXIT, HE_MBOX );
                break;
    
            case 2 :
                g_pSomeTrans.Release();
                
                // Create the transform 
                hr=g_pTransFact->CreateTransform( NULL, 0, NULL, 0,
                                                 NULL, NULL, CLSID_Ruffle,
                                                 IID_IDXTransform, (void **)&g_pSomeTrans );

                HandleError(hr, "Failed to CreateTransform(2) in pickaTrans()...\n", HE_EXIT, HE_MBOX );
                break;
        }//end switch case

    }//end if
}
 

