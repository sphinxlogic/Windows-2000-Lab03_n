#include "dactl.h"

void dump_com_error( _com_error &e )
{
    char buf[2048];

    sprintf(buf, _T( "Oops - hit an error!\n\tCode = %08lx\n\tCode meaning = %s\n" ),
            e.Error(), e.ErrorMessage());
    OutputDebugString(buf);
}

// If this is placed in the scope of the smart pointers, they must be
// explicitly Release(d) before CoUninitialize() is called.  If any reference
// count is non-zero, a protection fault will occur.

CDAViewerCtl::CDAViewerCtl() :_vc(NULL)  {
  lpD3DRM = NULL;
  lpD3DRM3 = NULL;
  lpSphere3_builder = NULL;
  try   {
    _vc.CreateInstance(__uuidof(DAViewerControlWindowed));
  } 
  catch( _com_error &e )  {
    dump_com_error( e );
  }
}

void CDAViewerCtl::CreateModel() {
  try {
    // Create the statics object.
    IDA2StaticsPtr e2;
    e2.CreateInstance(__uuidof(DAStatics));
    e2 = _vc->GetMeterLibrary();

    // Import Media (geometries, images and in this case).  
    // The GetCurrentDirectory() is used as a starting
    // point for relative file importing.
    TCHAR szMediaBase[_MAX_PATH];
    TCHAR szImg[_MAX_PATH];
    TCHAR szGeo[_MAX_PATH];
    TCHAR szGlobe[MAX_PATH];

    GetModuleFileName(GetModuleHandle(NULL), szMediaBase,sizeof(szMediaBase));
    char *pos = strrchr( szMediaBase, (int)'\\' );
    int result = pos - szMediaBase + 1;
    szMediaBase[result]= NULL;

    // Find out if your are in the bin directory of the SDK, 
    // and append the path accordingly.
    TCHAR *	bin  = NULL;
    TCHAR * lwszMediaBase = NULL;
    lwszMediaBase = _tcslwr( szMediaBase );
    bin = _tcsstr(lwszMediaBase, "\\bin\\");

    if(bin)
      _tcscat(szMediaBase,_T("../../../media/"));
    else
      _tcscat(szMediaBase,_T("../../../../media/"));

    _tcscpy(szImg,szMediaBase);
    _tcscpy(szGeo,szMediaBase);

    _tcscat(szImg,_T("image/"));
    _tcscat(szGeo,_T("geometry/"));

    // Set path to the Globe.
    _tcscpy(szGlobe,szGeo);
    _tcscat(szGlobe,_T("sphere3.x"));

		// import background.
    IDAImagePtr stillSky = e2->ImportImage(_bstr_t(szImg) + _bstr_t("cldtile.jpg"));

    // Define constants
    SIZE = e2->Scale3Uniform(0.25);
    PICKEVENTL = e2->LeftButtonDown;
    PICKEVENTR = e2->RightButtonDown;
    SPEED = e2->DANumber(0.07);
    PI = 3.14159265359;

		// Create the D3DRM object.
    hr = Direct3DRMCreate(&lpD3DRM);
		if(hr !=D3DRM_OK)  {
		  cleanD3DRM();
		  return;
		}

    // Use the D3DRM Object to QI for a D3DRM3 Object.
    hr = lpD3DRM->QueryInterface (IID_IDirect3DRM3, (void**)&lpD3DRM3);
		if(hr !=D3DRM_OK)  {
	      cleanD3DRM();
		  return;
		}

    // Use the D3DRM OBject to create a mesh builder.
    hr = lpD3DRM3->CreateMeshBuilder(&lpSphere3_builder);
		if(hr !=D3DRM_OK)  {
	      cleanD3DRM();
		  return;
		}

    // Load sphere3
    hr = (lpSphere3_builder)->Load(szGlobe, NULL, 
      D3DRMLOAD_FROMFILE, NULL, NULL);
		if(hr !=D3DRM_OK)  {
		  cleanD3DRM();
		  return;
		}

		IDAGeometryPtr globe = e2->ImportDirect3DRMVisual(lpSphere3_builder);
    globe = globe->Transform(SIZE);
    globeColor = e2->ColorHslAnim(e2->Div(e2->LocalTime,
      e2->DANumber(8)), e2->DANumber(1), e2->DANumber(0.5));
		globe = globe->SpecularColor(e2->Black);

    IDAPoint2Ptr maxSky = stillSky->BoundingBox->Max;
    IDAImagePtr tiledSky = stillSky->Tile();
    IDAImagePtr movingSky = tiledSky->Transform(e2->Translate2Anim(e2->Mul(e2->LocalTime,
      e2->Div(maxSky->X,e2->DANumber(8))), e2->Mul(e2->LocalTime,e2->Div(maxSky->X,e2->DANumber(16)))));

    // Import the geometries.
    IDAGeometryPtr rawCube = 
    e2->ImportGeometry( _bstr_t( szGeo ) +  _bstr_t("cube.x" ) );
    rawCube = rawCube->Transform(SIZE);

    IDAGeometryPtr rawCylinder = 
    e2->ImportGeometry( _bstr_t( szGeo ) +  _bstr_t("cylinder.x") );
    rawCylinder = rawCylinder->Transform(SIZE);

    IDAGeometryPtr rawCone = 
    e2->ImportGeometry( _bstr_t( szGeo ) +  _bstr_t("cone.x") );
    rawCone = rawCone->Transform(SIZE);

    // Make the geometries pickable.
    IDAGeometryPtr cone1 = activate(rawCone, e2->Green, e2);

    IDAGeometryPtr globe1 = activate(globe, e2->Magenta, e2);

    IDAGeometryPtr globe2 = activate(globe, e2->ColorHslAnim(e2->Div(e2->LocalTime,
      e2->DANumber(8)), e2->DANumber(1), e2->DANumber(0.5)), e2);

    IDAGeometryPtr cylinder = activate(rawCylinder, e2->ColorRgb(0.8,0.4,0.4), e2);

    // Construct the final geometry, scale and rotate it.
    IDAGeometryPtr multigeo = e2->UnionGeometry(cone1->Transform(e2->Translate3(0,1,0)),
      e2->UnionGeometry(globe1->Transform(e2->Translate3(0,0,1)),
        e2->UnionGeometry(globe2->Transform(e2->Translate3(0,0,-1)),cylinder)));

    IDAGeometryPtr geo = multigeo->Transform(e2->Scale3Anim(e2->Add(e2->Abs(e2->Sin(e2->Mul(e2->LocalTime,
      e2->DANumber(0.2)))),e2->DANumber(0.5)),e2->Add(e2->Abs(e2->Sin(e2->Mul(e2->LocalTime,
        e2->DANumber(0.26)))),e2->DANumber(0.5)),e2->Add(e2->Abs(e2->Sin(e2->Mul(e2->LocalTime,
          e2->DANumber(0.14)))),e2->DANumber(0.5))));

    IDATransform3Ptr transform1 = e2->Rotate3Anim(e2->ZVector3,
      e2->Mul(e2->DANumber(0.07), e2->Mul(e2->LocalTime, e2->DANumber(1.9))));

    IDATransform3Ptr transform2 = e2->Rotate3Anim(e2->YVector3,
      e2->Mul(e2->DANumber(0.07), e2->Mul(e2->LocalTime, e2->DANumber(PI))));

    IDAImagePtr movingGeoImg = geometryImage(geo->Transform(e2->Compose3(e2->Rotate3Anim(e2->ZVector3,
      e2->Mul(e2->DANumber(0.07),e2->Mul(e2->LocalTime,e2->DANumber(1.9)))), e2->Rotate3Anim(e2->YVector3,
        e2->Mul(e2->DANumber(0.07),e2->Mul(e2->LocalTime,e2->DANumber(PI)))))),e2);

    IDAFontStylePtr fs = e2->DefaultFont->Color(e2->Black);
    IDAImagePtr titleIm = e2->StringImage("Left Click On An Object", 
      fs)->Transform(e2->Translate2(0,0.03));

    IDAImagePtr model = e2->Overlay( titleIm, e2->Overlay( movingGeoImg, movingSky ) );
    
    // And set the model's image to this image.
    _vc->PutImage( model );

    // Set the cap for the frame rate.  If we don't do this, DA
    // will hog the cpu and the mouse and keyboard won't be very
    // responsive.  If you're running in full screen mode, you may
    // want to remove this line to get better frame rate.
    _vc->put_UpdateInterval(0.2);
    
    // Start the model on the view.  The WndProc will
    // generate the frames.
    _vc->Start();
    cleanD3DRM();

    } catch( _com_error &e2 ) {
        cleanD3DRM();
        dump_com_error( e2 );
    }
}

void CDAViewerCtl::cleanD3DRM()  {
	if(lpSphere3_builder != NULL)  {
    lpSphere3_builder->Release();
    lpSphere3_builder = NULL;
	}
	if(lpD3DRM != NULL)  {
    lpD3DRM->Release();
	  lpD3DRM = NULL;
	}
	if(lpD3DRM3 != NULL)  {
    lpD3DRM3->Release();
	  lpD3DRM3 = NULL;
	}
}


IDAGeometryPtr CDAViewerCtl::activate(IDAGeometryPtr unpickedGeo, 
                                      IDAColorPtr col, IDA2StaticsPtr e2)  {
  IDAPickableResultPtr pickGeo = unpickedGeo->Pickable();
  IDAEventPtr pickEvent = e2->AndEvent(PICKEVENTL, pickGeo->PickEvent);

  IDANumberPtr numcyc;
  numcyc.CreateInstance( L"DirectAnimation.DANumber");
  numcyc->Init(e2->Until(e2->DANumber(0),pickEvent,
    e2->Until(e2->DANumber(1), pickEvent, numcyc)));

  IDAColorPtr colcyc;
  colcyc.CreateInstance( L"DirectAnimation.DAColor");
  colcyc->Init(e2->Until(e2->White, pickEvent, e2->Until(col, pickEvent, colcyc)));

  IDATransform3Ptr xf = e2->Rotate3Anim(e2->XVector3, e2->Integral(numcyc));

  return pickGeo->Geometry->DiffuseColor(colcyc)->Transform(xf);

}

IDAImagePtr CDAViewerCtl::geometryImage(IDAGeometryPtr geo, IDA2StaticsPtr e2)  {
  IDANumberPtr scaleFactor = e2->DANumber(0.02);

  IDATransform3Ptr perspTransform;
  perspTransform.CreateInstance( L"DirectAnimation.DATransform3");
  perspTransform->Init(e2->Until(e2->Compose3(e2->Rotate3Anim(e2->XVector3,
    e2->Mul(SPEED,e2->LocalTime)),e2->Translate3(0, 0, 0.2)),PICKEVENTR, 
      e2->Until(e2->Rotate3Anim(e2->XVector3, e2->Mul(SPEED,e2->LocalTime)),
        PICKEVENTR, perspTransform)));

  IDAGeometryPtr myLight = 
    e2->UnionGeometry(e2->DirectionalLight->Transform(perspTransform), e2->DirectionalLight);

  IDACameraPtr perspectiveCam = (e2->PerspectiveCamera(1,0))->Transform(e2->Compose3(e2->Rotate3Anim(e2->XVector3,
    e2->Mul(SPEED,e2->LocalTime)),e2->Translate3(0,0,0.2)));

  IDACameraPtr parallelCam = (e2->ParallelCamera(1))->Transform(e2->Rotate3Anim(e2->XVector3,
    e2->Mul(SPEED,e2->LocalTime)));

  IDACameraPtr camera;
  camera.CreateInstance( L"DirectAnimation.DACamera");
  camera->Init(e2->Until(perspectiveCam, PICKEVENTR,
    e2->Until(parallelCam, PICKEVENTR, camera)));

  // Display text which tells the user what camera is currently being used.
  IDAStringPtr camText;
  camText.CreateInstance( L"DirectAnimation.DAString");
  camText->Init(e2->Until(e2->DAString("Perspective - Right Click to Switch"), PICKEVENTR,
    e2->Until(e2->DAString("Parallel - Right Click to Switch"),PICKEVENTR, camText)));

  IDAFontStylePtr fs = e2->DefaultFont->Color(e2->Red);
  IDAImagePtr camIm  = e2->StringImageAnim(camText, fs);
  camIm = camIm->Transform(e2->Translate2(0, -0.03));

  return e2->Overlay(camIm, e2->UnionGeometry(geo->Transform(e2->Scale3UniformAnim(scaleFactor)),
    myLight)->Render(camera));
}

HRESULT CDAViewerCtl::GetIUnknown(IUnknown **pUnk) {
    if (!pUnk)
        return E_POINTER;

    if (_vc == NULL)
        return E_NOINTERFACE;

    return _vc->QueryInterface(IID_IUnknown, (LPVOID *)pUnk);
}
